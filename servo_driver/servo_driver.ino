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
bool first = true;
bool next = false;
bool last = false;

// Communication
int msgIn = 0;
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
    touchTheButt();
    Serial.print("done?: ");
    Serial.println(msgOut);
  }
  else if (msgIn == 2) {
    dispense();
    Serial.print("done?: ");
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
//  Serial.println("touching the butt");
  if (first && (millis() - lastTime > goTime)) { // give time to move to open
    Serial.println("MOVE BITCH");
    celebrationServo.write(180);

    first = false;
    next = true;
    last = false;
    lastTime = millis();
  }
  if (next && (millis() - lastTime > goTime)) { // give time to move to closed
    Serial.println("GETOUT THEWAY");
    celebrationServo.write(0);

    first = false;
    next = false;
    last = true;
    lastTime = millis();
  }
  if (last && (millis() - lastTime > goTime)) { // give time to move to closed
    Serial.println("AH");
    celebrationServo.write(180);
    
    msgOut = 1;   // tell leader finished 
    msgIn = 0;    // don't run again

    first = true;
    next = false;
    last = false;
  }
}

void dispense() {
  if (!next && (millis() - lastTime > goTime)) { // give time to move to open
    Serial.println("THE PARTY DONT START");
    dartServo.write(50);
    
    next = true;
    lastTime = millis();
  }
  else if (next && (millis() - lastTime > goTime)) { // give time to move to closed
    Serial.println("TIL I WALK IN");
    dartServo.write(0);
    
    msgOut = 2;   // tell leader finished 
    msgIn = 0;    // don't run again
    next = false;
    lastTime = millis();
  }
}

void requestEvent() {
  Serial.print("Request from Leader. Sending: ");
  Serial.println(msgOut);
  Wire.write(msgOut);
  msgOut = 0;
}
