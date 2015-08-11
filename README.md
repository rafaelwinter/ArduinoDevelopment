ArduinoDevelopment
===========

Arduino development study projects.

1. LedControl
----

This project has a blinking LED that can be activated with a push button. 
The blinking speed is controlled by a potentiometer. 

A [Fritzing diagram](http://fritzing.org/download/) can be found with the code.

2. LedAnalogVoltage
----

This project lights up a row of LEDs according to the position of a potentiometer. It is a contribution of [@VitorRodrigues](https://github.com/VitorRodrigues).

A [Fritzing diagram](http://fritzing.org/download/) can be found with the code.

3. KEYES 5050 module test 
----

This sketch shows how to control a KEYES 5050 Full-color LED Module for Arduino. It lights up one LED at time sequentially, moving it forward and backwards. The colors are changed in the sequence, in each step of the sequence an interpolation is done between colors of the rainbow.

Parts used:

* 1x Arduino. I used a DCCduino Nano (a clone), but any Arduino with sufficient pins would work.
* 1x KEYES 5050 Full-color LED Module for Arduino.
* Protoboard 
* Lots of jumpers...

4. KEYES 5050 color selector 
----

This sketch shows how to select a color for the KEYES 5050 Full-color LED Module using a potentiometer. It lights up the entire LED row using one of the predefined colors. The position of the potentiometer determines which color will be taken from the palette to colorize the LEDs.

Parts used:

* 1x Arduino. I used a DCCduino Nano (a clone), but any Arduino with sufficient pins would work.
* 1x KEYES 5050 Full-color LED Module for Arduino.
* 1x 10k Ohm potentiometer
* Protoboard 
* Lots of jumpers...
