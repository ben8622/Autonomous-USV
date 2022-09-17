/*
  Arduino FS-I6X Demo
  fsi6x-arduino-mega-ibus.ino
  Read iBus output port from FS-IA6B receiver module
  Display values on Serial Monitor
 
  Channel functions by Ricardo Paiva - https://gist.github.com/werneckpaiva/
 
  DroneBot Workshop 2021
  https://dronebotworkshop.com
*/
 
// Include iBusBM Library
#include <IBusBM.h>
 
// Create iBus Object
IBusBM ibus;

int8_t ch1 = 0;
int8_t ch2 = 0;
int8_t ch3 = 0;
int8_t ch4 = 0;
int8_t ch5 = 0;
int8_t ch6 = 0;

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
 
void setup() {
  // Start serial monitor
  Serial.begin(115200);
 
  // Attach iBus object to serial port
  ibus.begin(Serial1);
}
 
void loop() {
 
  // Grab channel values from ibus
  byte i = 0;
  ch1 = readChannel(i, -100, 100, 0);
  i++;
  ch2 = readChannel(i, -100, 100, 0);
  i++;
  ch3 = readChannel(i, -100, 100, 0);
  i++;
  ch4 = readChannel(i, -100, 100, 0);
  i++;
  ch5 = readChannel(i, -100, 100, 0);
  i++;
  ch6 = readSwitch(i, false);

  Serial.print(ch1);
  Serial.print(",");
  Serial.print(ch2);
  Serial.print(",");
  Serial.print(ch3);
  Serial.print(",");
  Serial.print(ch4);
  Serial.print(",");
  Serial.print(ch5);
  Serial.print(",");
  Serial.print(ch6);
  Serial.println();

  // 200 Hz update cycles
  delay(5);
}
