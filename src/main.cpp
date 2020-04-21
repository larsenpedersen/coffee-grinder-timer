/*
  Arduino Nano

  Display (1.8" TFT ST7735):
  - VCC     --> 5V
  - GND     --> GND
  - CS      --> D10
  - RESET   --> D8
  - A0 / DC --> D9
  - SDA     --> D11
  - SCK     --> D13
  - LED     --> 3V3

  Encoder (https://www.elextra.dk/details/H35684/rotary-encoder-18-trin-m-trykknap-funktion):
  -         --> GND
  -         --> GND
  -         --> A0
  -         --> A1
  -         --> A2
/**/

#include <Arduino.h>
#include <ClickEncoder.h>
#include <EEPROM.h>
#include <TimerOne.h>
#include "display.h"

// Relay settings
#define RELAY 2
#define RELAY_ON LOW
#define RELAY_OFF HIGH

// EEPROM Locations
#define EEPROM_LOC_SINGLESHOT 20
#define EEPROM_LOC_DOUBLESHOT 40

// Default grind times
uint16_t SINGLESHOT = 8000; // Max 65,535 milliseconds because of datatype
uint16_t SINGLESHOT_TEMP; // Max 65,535 milliseconds because of datatype
uint16_t DOUBLESHOT = 15000; // Max 65,535 millisecond because of datatype
uint16_t DOUBLESHOT_TEMP; // Max 65,535 milliseconds because of datatype

// States
uint8_t prevMenu = 255; // High number to ensure that start screen gets drawn
uint8_t realPrevMenu = 0;
uint8_t currentMenu = 0;
uint8_t inQuickSettings = 0; // Bool
uint8_t inGrindMode = 0; // Bool
uint8_t showValue = 0; // Bool

uint8_t grindActive = false; // Bool -> Is grinder currently grinding?
uint32_t grindUntil = 0;

ClickEncoder *encoder;

int8_t encoderValue = 0;
uint8_t encoderButton = 0;

void timerIsr () {
  encoder->service ();
}

void renderDisplay () {
  if ( prevMenu != currentMenu ) {
    prevMenu = currentMenu;
    switch ( currentMenu ) {
      case 0:
        screenDefault ();
      break;

      case 1:
        screenManualGrind ();
      break;

      case 2:
        screenSingleShot ();
      break;

      case 3:
        screenDoubleShot ();
      break;

      case 4:
        screenQuickSettings (); 
      break;

      case 5:
        screenQuickSettingsSaved ();
      break;

      case 6:
        screenQuickSettingsCancelled ();
      break;

      default:
        screenDefault ();
      break;
    }
  }
}

void writeToEEPROM ( uint8_t location ) {
  uint16_t tempEEPROMVal;
  // check if value at location is different from original
  EEPROM.get ( location, tempEEPROMVal );
  if ( location == EEPROM_LOC_SINGLESHOT && tempEEPROMVal != SINGLESHOT ) {
    EEPROM.put ( location, SINGLESHOT );
  } else if ( location == EEPROM_LOC_DOUBLESHOT && tempEEPROMVal != DOUBLESHOT ) {
    EEPROM.put ( location, DOUBLESHOT );
  }
}

void relayOn () {
  digitalWrite(RELAY, RELAY_ON);
}

void relayOff () {
  digitalWrite(RELAY, RELAY_OFF);
}

void setGrindState () {
  ucg.setColor( 0, 0, 0 );
  ucg.drawBox( 0, 120, 128, 40);

  if (grindActive) {
    ucg.setColor( 255, 0, 0 );
    ucg.setPrintPos( 41, 130 );
    ucg.print( "GRINDING" );
  } else if (!grindActive) {
    ucg.setColor( 70, 70, 70 );
    if ( currentMenu == 1) {
      ucg.setPrintPos( 27, 150 );
      ucg.print( "Hold to grind" );
    } else {
      ucg.setPrintPos( 25, 150 );
      ucg.print( "Press to start" );
    }
  }
}

void startGrind ( uint16_t grindTime ) {
  if ( !grindActive ) { // Start GRINDING
    grindUntil = millis () + grindTime;
    grindActive = true;
    setGrindState ();
    relayOn ();
  } else if ( grindActive && millis () < grindUntil ) { // While grinding
    if (encoderButton == 5) {
      grindUntil = 0; // Cancel grinding while grinding
      relayOff ();
    }
    uint16_t timePassed = grindTime - (grindUntil -  millis () );
    timePassed = map ( timePassed, 0, grindTime, 0, 128 );
    drawProgress ( timePassed );
  } else {
    if ( millis () > grindUntil ) { // Grinding ended
      relayOff();
      grindUntil = 0;
      grindActive = false;
      inGrindMode = false;
      setGrindState ();
      clearProgress ();
    }
  }
}

void setup ( void ) {
  Serial.begin ( 115200 );
  Serial.println ( "System: Running" );
  delay ( 1000 );
  ucg.begin ( UCG_FONT_MODE_SOLID );
  ucg.clearScreen ();

  // Initialise the ClickEndoder
  encoder = new ClickEncoder ( A1, A0, A2 );

  // Initialise the Arduino data pins for OUTPUT
  pinMode(RELAY, OUTPUT);
  relayOff();

  // Read EEPROM
  EEPROM.get ( EEPROM_LOC_SINGLESHOT, SINGLESHOT );
  EEPROM.get ( EEPROM_LOC_DOUBLESHOT, DOUBLESHOT );
  SINGLESHOT_TEMP = SINGLESHOT;
  DOUBLESHOT_TEMP = DOUBLESHOT;

  Timer1.initialize ( 1000 );
  Timer1.attachInterrupt ( timerIsr );
}

void loop ( void ) {
  if ( !grindActive ) {
    encoderValue = encoder->getValue ();
  }
  encoderButton = encoder->getButton ();

  switch ( currentMenu ) {
    case 0: // START SCREEN
      if ( !inQuickSettings ) {
        if ( encoderValue > 0 ) {
          currentMenu = 1;
        } else if ( encoderValue < 0 ) {
          currentMenu = 3;
        }
      }
      renderDisplay();
    break;

    case 1: // MANUAL GRIND
      if ( !inQuickSettings ) {
        if ( encoderButton == 3 ) {
          relayOn ();
          grindActive = true;
          setGrindState ();
        } else if ( encoderButton == 4) {
          relayOff ();
          grindActive = false;
          setGrindState ();
        }

        if ( encoderValue > 0 ) {
          currentMenu = 2;
        } else if ( encoderValue < 0 ) {
          currentMenu = 0;
        }
      }
      renderDisplay();
    break;

    case 2: // SINGLE SHOT
      realPrevMenu = 2;
      if ( !inQuickSettings ) {
        if ( encoderValue > 0 ) {
          currentMenu = 3;
        } else if ( encoderValue < 0 ) {
          currentMenu = 1;
        }

        if ( encoderButton == 5 ) {
          inGrindMode = true;
        }

        if ( inGrindMode == true ) {
          startGrind(SINGLESHOT);
        }

        if ( encoderButton == 4 ) { // Settings
          inQuickSettings = true;
          currentMenu = 4;
        }
      }
      renderDisplay();
    break;

    case 3: // DOUBLE SHOT
      realPrevMenu = 3;
      if ( !inQuickSettings ) {
        if ( encoderValue > 0 ) {
          currentMenu = 0;
        } else if ( encoderValue < 0 ) {
          currentMenu = 2;
        }

        if ( encoderButton == 5  ) {
          inGrindMode = true;
        }

        if ( inGrindMode == true ) {
          startGrind(DOUBLESHOT);
        }

        if ( encoderButton == 4 ) { // Settings
          inQuickSettings = true;
          currentMenu = 4;
        }
      }
      renderDisplay();
    break;

    case 4: // QUICK SETTINGS
      if ( realPrevMenu == 2 ) {
        if ( !showValue ) {
          screenQuickSettingsValue ( SINGLESHOT_TEMP );
          encoder->setAccelerationEnabled ( true );
          showValue = true;
        }

        if ( encoderValue > 0 ) {
          if ( SINGLESHOT_TEMP < 65500 ) {
            SINGLESHOT_TEMP += ( encoderValue * 100 );
          } else {
            SINGLESHOT_TEMP = 65500;
          }
          screenQuickSettingsValue ( SINGLESHOT_TEMP );
        } else if ( encoderValue < 0 ) {
          if ( SINGLESHOT_TEMP > 0) {
            SINGLESHOT_TEMP += ( encoderValue * 100 );
          } else {
            SINGLESHOT_TEMP = 0;
          }
          screenQuickSettingsValue ( SINGLESHOT_TEMP );
        }

        if ( encoderButton == 5  ) { // Save settings on click
          SINGLESHOT = SINGLESHOT_TEMP;
          writeToEEPROM ( EEPROM_LOC_SINGLESHOT );
          inQuickSettings = false;
          currentMenu = 5; // !!! Change to 2, if you don't want save confirmation anymore
          showValue = false;
          encoder->setAccelerationEnabled ( false );
        }

        if ( encoderButton == 4 ) { // Cancel settings on hold
          SINGLESHOT_TEMP = SINGLESHOT;
          inQuickSettings = false;
          currentMenu = 6;
          showValue = false;
          encoder->setAccelerationEnabled ( false );
        }
      } else if ( realPrevMenu == 3 ) {
        if ( !showValue ) {
          screenQuickSettingsValue ( DOUBLESHOT_TEMP );
          encoder->setAccelerationEnabled ( true );
          showValue = true;
        }

        if ( encoderValue > 0 ) {
          if ( DOUBLESHOT_TEMP < 65500 ) {
            DOUBLESHOT_TEMP += ( encoderValue * 100 );
          } else {
            DOUBLESHOT_TEMP = 65500;
          }
          screenQuickSettingsValue ( DOUBLESHOT_TEMP );
        } else if ( encoderValue < 0 ) {
          if ( DOUBLESHOT_TEMP > 0 ) {
            DOUBLESHOT_TEMP += ( encoderValue * 100 );
          } else {
            DOUBLESHOT_TEMP = 0;
          }
          screenQuickSettingsValue ( DOUBLESHOT_TEMP );
        }

        if ( encoderButton == 5  ) { // Save settings on click
          DOUBLESHOT = DOUBLESHOT_TEMP;
          writeToEEPROM ( EEPROM_LOC_DOUBLESHOT );
          inQuickSettings = false;
          currentMenu = 5; // !!! Change to 3, if you don't want save confirmation anymore
          showValue = false;
          encoder->setAccelerationEnabled ( false );
        }

        if ( encoderButton == 4 ) { // Cancel settings on hold
          DOUBLESHOT_TEMP = DOUBLESHOT;
          inQuickSettings = false;
          currentMenu = 6;
          showValue = false;
          encoder->setAccelerationEnabled ( false );
        }
      }
      renderDisplay ();
    break;

    case 5: // QUICK SETTINGS SAVED
      renderDisplay ();
      delay (1500);
      currentMenu = realPrevMenu;
    break;

    case 6: // QUICK SETTINGS CANCELLED
      renderDisplay ();
      delay (1500);
      currentMenu = realPrevMenu;
    break;

    default:
    break;
  }
}
