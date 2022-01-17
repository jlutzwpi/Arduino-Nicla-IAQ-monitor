# Arduino-Nicla-IAQ-monitor

This was my first foray into app developement using the MIT App Inventor II.  It's fairly straightforward using block programming.  It just took me a bit to get used to the fucntionality and interface.

This was also my first application using the [Arduino Nicla Sense ME board](https://docs.arduino.cc/hardware/nicla-sense-me).  There was a little bit of learning here because some changes to the library are required to get readings from the BSEC sensor.

1. Despite what the documentation says, you need to use the `SENSOR_ID_BSEC_LEGACY` ID when you call SensorBsec in the Arduino sketch.
2. You need to go into Arduino_BHY2 > src > sensors > SensorTypes.h and change `SENSOR_DATA_FIXED_LENGTH` to 30.

This documentation assumes that you know how to load libraries in Arduino (you need the Arduino_BHY2 library, and the Arduino_BHY2_Host if you are doing a host/slave setup).  It also assumes basic knowledge of how to use MIT App Inventor II.  I've included both the Arduino and MIT App Inventor source files.
