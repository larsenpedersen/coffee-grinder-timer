# Coffee Grinder Timer ☕️

<a href="http://www.youtube.com/watch?feature=player_embedded&v=_ijmQUTWak0" target="_blank"><img src="http://img.youtube.com/vi/_ijmQUTWak0/0.jpg" alt="Watch demo on YouTube" width="240" height="180" border="10" /></a>

## Parts list
- Arduino Nano
- Rotary encoder w. click (Something like https://www.elextra.dk/details/H35684/rotary-encoder-18-trin-m-trykknap-funktion)
- ST7735 1.8" TFT

## Pins
*Connection between ST7735 and Arduino Nano*
- <kbd>VCC</kbd> ⟶ <kbd>5V</kbd>
- <kbd>GND</kbd> ⟶ <kbd>GND</kbd>
- <kbd>CS</kbd> ⟶ <kbd>D10</kbd>
- <kbd>RESET</kbd> ⟶ <kbd>D8</kbd>
- <kbd>A0 / DC</kbd> ⟶ <kbd>D9</kbd>
- <kbd>SDA</kbd> ⟶ <kbd>D11</kbd>
- <kbd>SCK</kbd> ⟶ <kbd>D13</kbd>
- <kbd>LED</kbd> ⟶ <kbd>3V3</kbd>

## Interface
Everything is controls by either turning, clicking or holding the rotary encoder:

**General**
- <kbd>Turn</kbd> to pick one of the following grinding options:

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
