# Coffee Grinder Timer ☕️

<a href="http://www.youtube.com/watch?feature=player_embedded&v=_ijmQUTWak0
" target="_blank"><img src="http://img.youtube.com/vi/_ijmQUTWak0/0.jpg" 
alt="Watch demo on YouTube" width="240" height="180" border="10" /></a>

## Parts list
- Arduino Nano
- Rotary encoder
- ST7735 1.8" TFT

## Pins
*Connection between ST7735 and Arduino Nano*
- VCC     --> 5V
- GND     --> GND
- CS      --> D10
- RESET   --> D8
- A0 / DC --> D9
- SDA     --> D11
- SCK     --> D13
- LED     --> 3V3

## Interface
- Turn rotary encoder to pick grinding option:

- **Manual grinding**
  - Hold down rotary encoder to grind

- **Single grinding**
  - Click rotary encoder to grind
  - Hold rotary encoder to enter settings:
    - Turn rotary encoder to change time
    - Click rotary encoder to save settings
    - Hold rotary encoder to exit settings without saving

- **Double grinding**
  - Hold rotary encoder to enter settings:
    - Turn rotary encoder to change time
    - Click rotary encoder to save settings
    - Hold rotary encoder to exit settings without saving
