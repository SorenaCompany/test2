/*
  DS18B20 Temperature Sensor
  modified on 08 Sep 2020
  by Mohammad Reza Akbari @ Electropeak
  Home<iframe class="wp-embedded-content" sandbox="allow-scripts" security="restricted" style="position: absolute; clip: rect(1px, 1px, 1px, 1px);" title="&#8220;Home&#8221; &#8212; Electropeak | Ultimate Robotics Solutions" src="https://electropeak.com/learn/embed/#?secret=x7L5RMaDPS" data-secret="x7L5RMaDPS" width="600" height="338" frameborder="0" marginwidth="0" marginheight="0" scrolling="no"></iframe>
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include "SevSeg.h"


// Connect Sensor output to pin2
#define ONE_WIRE_BUS 18

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SevSeg sevseg; //Instantiate a seven segment controller object

/*
   The setup function. We only start the sensors here
*/
void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  byte numDigits = 2;
  byte digitPins[] = {2, 3};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}

void loop(void)
{
  sensors.requestTemperatures(); // Send the command to get temperatures

  int temp = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if (temp != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature of Sensor 0 is: ");
    Serial.println(temp);
  }
  else
  {
    Serial.println("Error to reading data");
  }
  static int deciSeconds = temp;
  sevseg.setNumber(deciSeconds, 0);
  delay(5000);
}
