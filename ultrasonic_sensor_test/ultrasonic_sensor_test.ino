//#include "C:\Users\hkwon\Documents\Stanford\ME 210\finalproject\Repo\me210\robot_driver\Drivetrain.h"
#include "Drivetrain.h"

// ultrasonic definitions
const int triggerPin = 3;
const int echoPin = 2;

// ultrasonic variables
unsigned long duration;
float distance;
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
float loThresh = 2.0;     // [in]
float hiThresh = 800.0;     // [in] when <1" away from sensor

void setup() {
	Serial.begin(9600);
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin, INPUT);
  pinMode(inLeft, OUTPUT);
  pinMode(outLeft, OUTPUT);
  pinMode(enable, OUTPUT);

  lastTime = micros();
  digitalWrite(triggerPin, LOW);  // no trigger signal
}

void loop() {

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
//    Serial.print("Distance: ");
//    Serial.print(distance);
//    Serial.println(" in");

    if ((distance <= loThresh) || distance >= hiThresh) {
      keepDriving = false;
      Serial.println("sense stop");
    }
    else {
      keepDriving = true;
      Serial.println("sense drive");
    }

    needRead = false;
    needCycle = true;
    lastTime = micros();
  }

  if (keepDriving) {
    driveTrain.forwards();
  }
  else {
    driveTrain.stop();
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

void BlockingExample() {
  // basic example using blocking code
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
