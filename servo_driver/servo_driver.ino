#include <Wire.h>
#include <Servo.h>
#define FOLLOWER_ADDRESS 0x60

/* 
This is the follower code for executing servo dart deployment and celebration. 
Requires the leader code found in robot_driver.ino
*/

// Servo
const int dartServoPin = 9;
const int celebrationServoPin = 10;
Servo dartServo;
Servo celebrationServo;
const int goTime = 1000;
unsigned long lastTime;
bool next = false;

// Communication
int msgIn = 1;
int msgOut = 0;

void setup() {
  Serial.begin(9600);
  dartServo.attach(dartServoPin);
  celebrationServo.attach(celebrationServoPin);

  // Start the I2C Bus as follower on address 9
  Wire.begin(FOLLOWER_ADDRESS); 
  // Attach a function to trigger when info is received from leader
  Wire.onReceive(receiveEvent);
  // Attach a function to signal when leader requests info from follower
  Wire.onRequest(requestEvent);

  dartServo.write(0);
  celebrationServo.write(0);
}

void loop() {
  if (msgIn == 1) {
//    Serial.println("gonna touche da butte ");
    touchTheButt();
    Serial.println(msgOut);
  }
  else if (msgIn == 2) {
    Serial.print("going to dispense ");
    dispense();
    Serial.println(msgOut);
  }
}

void receiveEvent(int input) {
  Serial.print("received ");
  if(Wire.available() != 0) {
    msgIn = Wire.read();    // read one character from the I2C
    Serial.println(msgIn);
    lastTime = millis();
  }
}

void touchTheButt() {
  Serial.println("touching the butt");
  celebrationServo.write(180);
  if (millis() - lastTime > goTime) { // give time to move to 180
    celebrationServo.write(0);
    msgOut = 1;   // tell leader finished 
    msgIn = 0;    // don't run again
  }
}

void dispense() {
  dartServo.write(50);
  if (millis() - lastTime > goTime) { // give time to move to open
    dartServo.write(0);
    next = true;
    lastTime = millis();
  }
  else if (next && (millis() - lastTime > goTime)) { // give time to move to closed
    msgOut = 2;   // tell leader finished 
    msgIn = 0;    // don't run again
    next = false;
  }
}

void requestEvent() {
  Serial.print("Request from Leader. Sending: ");
  Serial.println(msgOut);
  Wire.write(msgOut);
  msgOut = 0;
}
