```
                          (                           
   (           (          )\ )                        
   )\    (     )\ )   (  (()/(   (     (   (  (       
((((_)(  )(   (()/(  ))\  /(_)) ))\   ))\  )\))(  (   
 )\ _ )\(()\   ((_))/((_)(_))_|/((_) /((_)((_))\  )\  
 (_)_\(_)((_)  _| |(_))( | |_ (_))( (_))   (()(_)((_) 
  / _ \ | '_|/ _` || || || __|| || |/ -_) / _` |/ _ \ 
 /_/ \_\|_|  \__,_| \_,_||_|   \_,_|\___| \__, |\___/ 
                                          |___/       
```
# Ardufuego
##### An Arduino RF controller that emulates Heat N Glo fireplace remotes
###### *Broken links subject to "you'll have that."*

## Purpose
- Control the fireplace via Google Home or Amazon Alexa
- End reliance on poorly designed, battery hogging remote
- Automate start and end patterns (fan speed, flame height)

## Introduction
This project emulates the protocol for an RC300 Heat & Glo fireplace remote.  Functionality is currently limited to controlling the on / off state of the fireplace, the flame height, and the fan speed.  Convenience functions have been added to provide optimal start up and shut down procedures.

## Hardware Setup
- RF 433 Mhz Transmitter and Receiver: Ex. Gowoops via Amazon
<img src="/images/RF.png" width="500">

- Arduino: Ex. Keyestudio Mega via Amazon
<img src="/images/mega.jpg" width="500">

- Breadboard and jumpers
- 5v Power supply

## Software Setup
The following files are significant to this project:
- FireplaceRF
  - Library to include in Arduino sketches for controlling a fireplace via RF

- Ardufuego.ino
  - An example Arduino sketch that imports and utilizes FireplaceRF

- RF_Tester.ino
  - An example Arduino sketch that reads an RF signal and prints the timings to the serial monitor

- RF_Transmitter.ino
  - An example Arduino sketch that transmits an RF signal

- [UPnP.groovy](../../../STUPNP)
  - Smartthings UPnP manager (external repo)
  - Used to discover Ardufuego device via SSDP

- [COMING SOON] Smartthings Ardufuego device controller
  - A Smartthings controller for adding the Ardufuego as a smart device

- [COMING SOON] Smartthings Ardufuego device manager
  - A Smartthings device manager for automating an Ardufuego controlled fireplace

- [COMING SOON] Smartthings Arduino sketch
  - An Arduino sketch that combines FireplaceRF and Smartthings

## Getting Started
1. Connect ground pin of the RF TX board to Arduino ground
2. Connect VCC pin of the RF TX board to Arduino 5V
3. Connect data pin of the RF TX board to Arduino TX pin (3 in test sketch)
4. Import the FireplaceRF library into Arduino sketch editor
5. Open the Ardufuego test sketch in the Arduino sketch editor
6. Load the sketch onto an Arduino

## FireplaceRF API
```
FireplaceRF fireplace(x);
```
Creates a FireplaceRF to transmit on pin x where x is an int that cooresponds to an Arduino interrupt pin.
```
fireplace.on();
```
Turns the fireplace on.
```
fireplace.off();
```
Turns the fireplace off.
```
fireplace.setFan(x);
```
Sets the fan speed to x where x is an int from 0 to 3
```
fireplace.setFlame(x);
```
Sets the flame height to x where x is an int from 1 to 5
```
fireplace.start();
```
Turns the fireplace on, sets the flame height to 1, and turns the fan off.
```
fireplace.stop();
```
Turns the fireplace off, and turns the fan to speed 3.

## Credits
### Authors
* Matthew Nichols

### License
Apache License, Version 2.0 Apache License Version 2.0, January 2004 http://www.apache.org/licenses/
