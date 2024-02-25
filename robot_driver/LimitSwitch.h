#ifndef LIMITSWITCH_H
#define LIMITSWITCH_H

class LimitSwitch {
public:
	LimitSwitch();
	LimitSwitch(const int pin);

	void setPin(int pin);
	int getPin() const;

	bool status() const;

private:
	int pin;
};

#endif // MOTOR_H
