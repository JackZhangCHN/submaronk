//extra libs used
//https://github.com/bblanchon/ArduinoStreamUtils/releases/tag/v1.7.3 ECC the serial
// if unable to perform communication with individual arduinos,
// try to restart via unplug USB both or each, just try

#include <StreamUtils.h>

HammingStream<7, 4> eccSerial(Serial);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  eccSerial.print(analogRead(A0));
  eccSerial.print("|");
  eccSerial.println(analogRead(A1));

//  Code for the master, for joystick control
//  The code output format is XXX|YYY \n

}
