#include "Motor.h"
#include "Arduino.h"
using namespace std;

Motor::Motor() {
	// empty constructor
}

Motor::Motor(const int mp1, const int mp2, const int enable) {
	motorPin1 = mp1;
	motorPin2 = mp2;
	enablePin = enable;
}

void Motor::setSpeed(int speed) {
	analogWrite(enablePin, speed);
}

void Motor::spinForwards(void) {
	digitalWrite(motorPin1, HIGH);
	digitalWrite(motorPin2, LOW);
}

void Motor::spinBackwards(void) {
	digitalWrite(motorPin1, LOW);
	digitalWrite(motorPin2, HIGH);
}
