#include "LimitSwitch.h"

const int pin = 8;
LimitSwitch limitSwitch(pin);

void setup() {
	Serial.begin(9600);
	pinMode(pin, INPUT_PULLUP);
}

void loop() {
	if (limitSwitch.status())
		Serial.println("engaged");
	else
		Serial.println("disengaged");
	delay(1000);
}
