//#include "C:\Users\hkwon\Documents\Stanford\ME 210\finalproject\Repo\me210\robot_driver\Drivetrain.h"
#include "Drivetrain.h"
//#include "Ultrasonic.h"
#include <HCSR04.h>

// ultrasonic definitions
const int trigPin1 = 2;   // LEFT
const int echoPin1 = 3;
const int trigPin2 = 4;   // RIGHT
const int echoPin2 = 5;
const int trigPinF = 10;  // FRONT
const int echoPinF = 11;
const int triggerPin = trigPin1;
const int echoPin = echoPin1;

HCSR04 uL(2, 3); //initialisation class HCSR04 (trig pin , echo pin, number of sensor)
HCSR04 uR(4, 5);
HCSR04 uF(10, 11);

// ultrasonic variables
unsigned long dur1;
unsigned long dur2;
unsigned long durF;
unsigned long duration = dur1;
float dist1;
float dist2;
float distF; 
float distance = dist1;
unsigned long lastTime;
unsigned long trigDur = 10;        // [micros] trigger on for 10 microseconds
unsigned long pulseDur = 200;      // [micros] wait to read after 8 cycles ot 40kHz sonic burst
unsigned long cycleDur = 60000;    // [micros] sensing cycle >60ms
bool needTrig = true;
bool needPulse = false;
bool needRead = false;
bool needCycle = false;


// motor definitions
const int inLeft = 8;
const int outLeft = 7;
const int enable = 9;
const int inRight = 13;
const int outRight = 12;
int duty = 200;  // 0 - 255
Motor leftMotor(inLeft, outLeft, enable, duty);
Motor rightMotor(inRight, outRight, enable, duty);
DriveTrain driveTrain(leftMotor, rightMotor, duty);

// motor + ultrasonic vars
bool keepDriving = true;
bool findCorner = false;
float loThresh = 3.0;       // [cm]
float hiThresh = 800.0;     // [in] when <1" away from sensor
float farThresh = 40.0;     // [cm]
unsigned int countGood = 0;

void setup() {
	Serial.begin(9600);
	pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPinF, OUTPUT);
	pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPinF, INPUT);
  
  pinMode(inLeft, OUTPUT);
  pinMode(outLeft, OUTPUT);
  pinMode(enable, OUTPUT);

  lastTime = micros();
  digitalWrite(trigPin1, LOW);  // no trigger signal
  digitalWrite(trigPin2, LOW);  // no trigger signal
}

void loop() {
//  Serial.println(ultrasonic.dist(2)); 
 
//  Working();
//  BlockingExample();
//  driveTrain.forwards();
  TestStartZone();
}

void TestStartZone() {
  lastTime = millis();
//  dist1 = BlockingExample(trigPin1, echoPin1, dur1);
//  dist2 = BlockingExample(trigPin1, echoPin2, dur2);
//  distF = BlockingExample(trigPin1, echoPinF, durF);
//  Serial.println(dist1);
//  Serial.println(dist2);
//  Serial.println(distF);

  dist1 = uL.dist();
  dist2 = uR.dist();
  distF = uF.dist();
  Serial.println(dist1);
  Serial.println(dist2);
  Serial.println(distF);

  if (!keepDriving) {
    driveTrain.stop();
    countGood = 0;
  }
  else {
    if (distF > farThresh) {
        findCorner = true;
        Serial.println("good");
      }
    else {
      findCorner = false;
    }
      
    if (!findCorner) {
  
      if (dist1 > farThresh) {
        driveTrain.rotateLeft();
        Serial.println("left");
      }
      if (dist2 > farThresh) {
        driveTrain.rotateRight();
        Serial.println("right");
      }
      if (dist1 <= farThresh && dist2 <= farThresh && distF <= farThresh)
      {
        driveTrain.rotateLeft();
        Serial.println("left");
      }
      
    }
    else {
      if (dist1 - dist2 > 5) {
        driveTrain.rotateLeft();
        Serial.println("good left");
      }
      else if (dist2 - dist1 > 5) {
        driveTrain.rotateRight();
        Serial.println("good right");
      }
      else {
        driveTrain.stop();
        Serial.println("good stop");
        countGood++;
        if (countGood > 2) {
          keepDriving = false;
        }
      }
    }
  
    if (millis() - lastTime < 60) {
      delay(millis() - lastTime);
    }
  }
}

void TwoSense() {
  if (needTrig) {
    if (micros() - lastTime < trigDur) {    // trigger hasn't been on long enough
      digitalWrite(trigPin1, HIGH); 
      digitalWrite(trigPin2, HIGH);
    }
    else {  // do pulse next
      needTrig = false;
      needPulse = true;
      lastTime = micros();
    }
  }
  
  if (needPulse) {
    if (micros() - lastTime < pulseDur) {    // hasn't waited long enough for pulse to send
      digitalWrite(trigPin1, LOW);    // trigger off
      digitalWrite(trigPin2, LOW);    // trigger off
    }
    else {  // read signal next
      needPulse = false;
      needRead = true;
      lastTime = micros();
    }
  }

  if (needRead) {   // read the signal
    dur1 = pulseIn(echoPin1, HIGH);
    dur2 = pulseIn(echoPin2, HIGH);
    dist1 =  dur1 * (1125.33*12/1000000) / 2;   // duration * 0.0343 / 2; for cm
    dist2 =  dur2 * (1125.33*12/1000000) / 2;   // duration * 0.0343 / 2; for cm
//    Serial.print("Distance: ");
    Serial.print(dist1);
    Serial.println(" in");
    Serial.print(dist2);
    Serial.println(" in");
    Serial.println();

    // Stop at walls
    if (dist1 <= loThresh || dist1 >= hiThresh || dist2 <= loThresh || dist2 >= hiThresh) {// ((dist1 <= loThresh) || (dist1 >= hiThresh)) || dist2 <= loThresh || dist2 >= hiThresh) {
//      Serial.println("here");
      keepDriving = false;
    }
    else {
//      Serial.println("bleh");
      keepDriving = true;
    }

    needRead = false;
    needCycle = true;
    lastTime = micros();
  }
//  Serial.println(dist1);
//  Serial.println(dist2);

  // Turn away from walls
//  if (dist1 - dist2 > 0.5) {
////    driveTrain.rotateLeft();
//    Serial.println("left");
//  }
//  else if (dist2 - dist1 > 0.5) {
////    driveTrain.rotateRight();
//    Serial.println("right");
//  }
//  else 
  if (keepDriving) {
    driveTrain.forwards();
//    Serial.println("fwd");
  }
  else {
    driveTrain.stop();
//    Serial.println("stop");
  }

  if (needCycle) {
    if (micros() - lastTime < cycleDur) {  // wait for recommended measurement cycle
    }
    else {  // send trigger next
      needCycle = false;
      needTrig = true;
      lastTime = micros();
    }
  }
 
}

void Working() {
   if (needTrig) {
    if (micros() - lastTime < trigDur) {    // trigger hasn't been on long enough
      digitalWrite(triggerPin, HIGH); 
    }
    else {  // do pulse next
      needTrig = false;
      needPulse = true;
      lastTime = micros();
    }
  }
  
  if (needPulse) {
    if (micros() - lastTime < pulseDur) {    // hasn't waited long enough for pulse to send
      digitalWrite(triggerPin, LOW);    // trigger off
    }
    else {  // read signal next
      needPulse = false;
      needRead = true;
      lastTime = micros();
    }
  }

  if (needRead) {   // read the signal
    duration = pulseIn(echoPin, HIGH);
    distance =  duration * (1125.33*12/1000000) / 2;   // duration * 0.0343 / 2; for cm
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" in");
    needRead = false;
    needCycle = true;
    lastTime = micros();
  }

  if (needCycle) {
    if (micros() - lastTime < cycleDur) {  // wait for recommended measurement cycle
    }
    else {  // send trigger next
      needCycle = false;
      needTrig = true;
      lastTime = micros();
    }
  }
}

float BlockingExample(const int trigPin, const int echoPin, unsigned long dur) {
  // basic example using blocking code
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  dur = pulseIn(echoPin, HIGH);
  return (dur*.0343)/2;
//  Serial.print("Distance: ");
//  Serial.println(dist);
//  delay(100);
}
