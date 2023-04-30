//extra libs used
//https://github.com/bblanchon/ArduinoStreamUtils/releases/tag/v1.7.3 ECC the serial
// if unable to perform communication with individual arduinos,
// try to restart via unplug USB both or each, just try

#include <Servo.h>
#include <SoftwareSerial.h>
#include <StreamUtils.h>

HammingStream<7, 4> eccSerial(Serial);


int motor1 = 8; //motor for x
int motor2 = 9; //motor for y

int anglex = 0; // servo position in degrees
int angley = 0; // servo position in degrees

int x[10];
int y[10];
Servo servox;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); //serial baud rate to 9600
  pinMode(motor1, OUTPUT); // motor 1 pin set to 5
  pinMode(motor2,OUTPUT); // motor 2 pin set to 6
  analogWrite(motor1, 0);
  
 // servox.attach(motor1);
}

// the loop routine runs over and over again forever:
int filter(int currentX,int currentY){
  if (abs(currentX) > 680){
    currentX = x[5];
//    Serial.println("aaaaaaaa");
//    Serial.print(currentX);
//    Serial.println(x[4]);
//    Serial.println(x[3]);

  }
  int avgX = (x[3] + x[4] + x[5]) / 3;
  int returnX;
  if ((avgX - 40 <= currentX) && (currentX <= avgX + 40)) {
    returnX = currentX;
  }else returnX = int(avgX*0.3 + x[5] * 0.7);


//  pass x iteration, move on

  for (int i = 0; i < 5; i++){
    x[i] = x[i+1];
  }
  x[5] = currentX;

  for (int i = 0; i < 5; i++){
    y[i] = y[i+1];
  }
  y[5] = currentY;

  int returnY = currentY;
  
  return returnX;
}



void loop() {

  if(eccSerial.available()){
  String inString = eccSerial.readStringUntil('\n');
  int x = eccSerial.readStringUntil('|').toFloat();     
  int y = eccSerial.readStringUntil('\n').toFloat();

  anglex = x / 15; // Analogue output of joy stick is 10bit int, so just divided them to 6 to match 180-ish
  anglex = anglex*10;
  angley = y / 2; // same as x axis

//  anglex = filter(anglex, angley); //used to filter out the abnormal values.
  Serial.print("anglex:");
  Serial.print(anglex);
  Serial.print("  ");
  Serial.print("angley:");
  Serial.println(angley);
  
 }

  analogWrite(motor1,anglex/2.7);

delay(10);


}
