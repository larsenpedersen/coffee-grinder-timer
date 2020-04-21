# Coffee Grinder Timer ☕️

<a href="http://www.youtube.com/watch?feature=player_embedded&v=_ijmQUTWak0" target="_blank"><img src="http://img.youtube.com/vi/_ijmQUTWak0/0.jpg" alt="Watch demo on YouTube" width="240" height="180" border="10" /></a>

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
Everything is controls by either turning, clicking or holding the rotary encoder:

- <kbd>Turn</kbd>: Pick grinding option:

- **Manual grinding**
  - <kbd>Hold (∞)</kbd> to grind

- **Single grinding**
  - <kbd>Click</kbd> to start grinding
    - <kbd>Click</kbd> to cancel grinding 
  - <kbd>Hold (2s)</kbd> to enter settings:
    - <kbd>Turn</kbd> to change time
    - <kbd>Click</kbd> to save settings
    - <kbd>Hold (2s)</kbd> to exit settings without saving

- **Double grinding**
  - <kbd>Click</kbd> to start grinding
    - <kbd>Click</kbd> to cancel grinding 
  - <kbd>Hold (2s)</kbd> to enter settings:
    - <kbd>Turn</kbd> to change time
    - <kbd>Click</kbd> to save settings
    - <kbd>Hold (2s)</kbd> to exit settings without saving
