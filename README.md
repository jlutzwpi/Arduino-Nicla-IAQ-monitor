# Arduino-Nicla-IAQ-monitor

This was my first foray into app developement using the MIT App Inventor II.  It's fairly straightforward using block programming.  It just took me a bit to get used to the functionality and interface.

This was also my first application using the [Arduino Nicla Sense ME board](https://docs.arduino.cc/hardware/nicla-sense-me).  I decided that my first application would be an Indoor Air Quality (IAQ) sensor to measure air quality and also eCO2 (estimated Carbon Dioxide) and send the data via BLE to a phone app.  There was a little bit of learning here because some changes to the Nicla library are required to get readings from the Bosch BSEC sensor:

1. Despite what the documentation says, you need to use the `SENSOR_ID_BSEC_LEGACY` ID when you call SensorBsec in the Arduino sketch.
2. You need to go into Arduino_BHY2 > src > sensors > SensorTypes.h and change `SENSOR_DATA_FIXED_LENGTH` to 30.

This documentation assumes that you know how to load libraries in Arduino (you need the Arduino_BHY2 library, and the Arduino_BHY2_Host if you are doing a host/slave setup).  It also assumes basic knowledge of how to use MIT App Inventor II.  I've included both the Arduino and MIT App Inventor source files in this project.

Steps to get this running:

1. Upload the Arduino sketch to your Nicla Sense ME board.  When the sketch is uploaded and running, the LED light on the board will be red because it is not connected to a BLE device.
2. Open the .aia file in [MIT App Inventor](http://ai2.appinventor.mit.edu/).  I just ran the application in Emulator mode on my phone (this is really cool by the way).  You will need the MIT AI 2 app on your Android phone as well.  I believe there is now an iOS app as well.
3. Once the app is running on your phone, connect to "Nicla2".  The LED on the Nicla will turn green indicating that you have connected.  You can also bring up a Serial console to see that you are connected and data is being collected.
4. I noticed that it takes about 2-3 minutes for the Nicla to start transmitting accurate eCO2 and IAQ values.  For those first couple minutes, there are default values of 500 for eCO2 and 25 for IAQ.
5. You can see the historical values on the chart.
6. **FUTURE CAPABILITY** I'm also working on the ability to save the data to your phone so you can do further data analysis on it.
