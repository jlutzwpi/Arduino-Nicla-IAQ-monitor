
/* 
 * This sketch shows how an arduino board can act as a host for nicla. 
 * An host board can configure the sensors of nicla and then read their values.
 * The host board should be connected to nicla through the eslov connector.
 * 
 * In this example, the temperature sensor is enabled and its
 * values are periodically read and then printed to the serial channel
 * 
 * NOTE: if Nicla is used as a Shield on top of a MKR board,
 * please use BHY2Host.begin(false, NICLA_AS_SHIELD)
*/

#include "Arduino.h"
#include <ArduinoBLE.h>
#include <Arduino_BHY2.h>
#include "Nicla_System.h"


Sensor temp(SENSOR_ID_TEMP);
//Sensor gas(SENSOR_ID_GAS);
SensorBSEC bsec(SENSOR_ID_BSEC_LEGACY);

BLEService dataService("07e1f0e2-b68f-4f71-8bfc-19b3b0427b68"); 
BLEShortCharacteristic tempCharacteristic("5d75d722-fce9-471b-93e2-6c625ef6d634", BLERead | BLENotify);
BLEShortCharacteristic co2Characteristic("5d75d723-fce9-471b-93e2-6c625ef6d634", BLERead | BLENotify);
BLEShortCharacteristic iaqCharacteristic("5d75d724-fce9-471b-93e2-6c625ef6d634", BLERead | BLENotify);

void setup()
{

  nicla::begin();
  nicla::leds.begin();
  nicla::leds.setColor(off);
  BHY2.begin();
  //gas.begin();
  temp.begin();
  bsec.begin();
  
  Serial.begin(9600);
  while(!Serial);

   // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  // set the local name peripheral advertises
  BLE.setLocalName("Nicla2");
  // set the UUID for the service this peripheral advertises:
  BLE.setAdvertisedService(dataService);

  // add the characteristics to the service
  dataService.addCharacteristic(tempCharacteristic);
  dataService.addCharacteristic(co2Characteristic);
  dataService.addCharacteristic(iaqCharacteristic);

  tempCharacteristic.writeValue(22.0);
  co2Characteristic.writeValue(22.0);
  iaqCharacteristic.writeValue(22.0);
  
  // add the service
  BLE.addService(dataService);


  // start advertising
  //BLE.setAdvertisingInterval(80);
  BLE.advertise();

  Serial.println("Bluetooth device active, waiting for connections...");
  
  
}

void loop()
{
  BLEDevice central = BLE.central();
  // if a central is connected to the peripheral:
  if (central.discoverAttributes()) {
    // turn on the LED to indicate the connection:
    nicla::leds.setColor(green);
    Serial.print("Connected to central: ");
    Serial.println(central.address());
  }
  
  static auto printTime = millis();
  BHY2.update();
  
  if (millis() - printTime >= 1000) {
    printTime = millis();
    //Serial.println(String("Gas: ") + String(gas.value(), 3));
    if(central.connected()) {
      float tempF = 1.8 * temp.value() + 32.0;
      Serial.println(String("Temp F: ") + String(tempF));
      tempCharacteristic.writeValue(tempF);
      float co2 = bsec.co2_eq();
      co2Characteristic.writeValue(co2);
      float iaq = bsec.iaq();
      iaqCharacteristic.writeValue(iaq);
      Serial.println(String("IAQ: ") + String(iaq));
      Serial.println(String("CO2: ") + String(co2));
    }
    else
    {
      nicla::leds.setColor(red);
    }
  }
}
