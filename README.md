# Coffee Grinder Timer ☕️

<a href="http://www.youtube.com/watch?feature=player_embedded&v=_ijmQUTWak0" target="_blank"><img src="http://img.youtube.com/vi/_ijmQUTWak0/0.jpg" alt="Watch demo on YouTube" width="240" height="180" border="10" /></a>

## Parts list
- Arduino Nano
- ST7735 1.8" TFT
- Rotary encoder w. click (Something like https://www.elextra.dk/details/H35684/rotary-encoder-18-trin-m-trykknap-funktion)
- Relay(s) (*I don't really know much about relays and am still experimenting with this. When I originally started this project I did [this drawing for my Mazzer Super Jolly](http://coffee.larsenpedersen.com/mazzersuperjolly/wiringdiagram-relay.png), so perhaps two relays are needed.*)

## Pins
**Connection between ST7735 and Arduino Nano**
- <kbd>VCC</kbd> ⟶ <kbd>5V</kbd>
- <kbd>GND</kbd> ⟶ <kbd>GND</kbd>
- <kbd>CS</kbd> ⟶ <kbd>D10</kbd>
- <kbd>RESET</kbd> ⟶ <kbd>D8</kbd>
- <kbd>A0 / DC</kbd> ⟶ <kbd>D9</kbd>
- <kbd>SDA</kbd> ⟶ <kbd>D11</kbd>
- <kbd>SCK</kbd> ⟶ <kbd>D13</kbd>
- <kbd>LED</kbd> ⟶ <kbd>3V3</kbd>

**Connection between rotary encoder and Arduino Nano**
- <kbd>Rotary envoder pin 1</kbd> ⟶ <kbd>A0</kbd>
- <kbd>Rotary envoder pin 2</kbd> ⟶ <kbd>GND</kbd>
- <kbd>Rotary envoder pin 3</kbd> ⟶ <kbd>A1</kbd>

- <kbd>Button pin 1</kbd> ⟶ <kbd>A2</kbd>
- <kbd>Button pin 2</kbd> ⟶ <kbd>GND</kbd>

**Connection between relay and Arduino Nano**
*I don't have any specifications for this, as mine is currently not hooked up.*

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
