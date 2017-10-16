# Arduino-EasyFunctions
A library for Arduino that makes CoDrone projects easier.

This library is meant to make it easier and cleaner to create projects for the CoDrone in Arduino.

# Commands
Commands for this library are:
- Ultra.startup - This autoconnects to a nearby CoDrone on 115200 bits/second (the CoDrone default). Put this in void(start).
- Ultra.freeflyLoop - This programs the CoDrone to be able to be controlled by the controller, with joysticks, killswitch (upper left IR sensor), and landing switch (upper right IR sensor) enabled.
- Ultra.passwordInput - Lets you customize a password. Controller only. This is a good one to customize in Ultra.cpp.
