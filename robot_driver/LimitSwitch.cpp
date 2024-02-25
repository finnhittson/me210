#include "LimitSwitch.h"
#include "Arduino.h"
using namespace std;

LimitSwitch::LimitSwitch() {
	// empty
}

LimitSwitch::LimitSwitch(const int pin) : pin(pin) {
	// empty
}

void LimitSwitch::setPin(int pin) {
	pin = pin;
}

int LimitSwitch::getPin() const {
	return pin;
}

bool LimitSwitch::status() const {
	if (digitalRead(pin))
		return false;
	return true;
}