#include "Motor.h"
#include "Arduino.h"
using namespace std;

Motor::Motor() {
	// empty constructor
}

Motor::Motor(const int in, const int out, const int enable) : in(in), out(out), enable(enable){
	// empty
}

Motor::Motor(const int in, const int out, const int enable, const int speed) : in(in), out(out), enable(enable), speed(speed){
	// empty
}

void Motor::setSpeed(int speed) {
	this->speed = speed;
}

int Motor::getSpeed(void) const {
	return speed;
}

void Motor::stop(void) {
	digitalWrite(in, LOW);
	digitalWrite(out, LOW);
	kickStart = true;
}

void Motor::forwards(void) {
	analogWrite(enable, speed);
	digitalWrite(in, HIGH);
	digitalWrite(out, LOW);
}

void Motor::backwards(void) {
	analogWrite(enable, speed);
	digitalWrite(in, LOW);
	digitalWrite(out, HIGH);
}
