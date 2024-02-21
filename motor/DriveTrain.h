#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Motor.h"
using namespace std;

class DriveTrain{
public:
	DriveTrain();
	DriveTrain(const Motor &leftMotor, const Motor &rightMotor, int speed);

	int getSpeed() const;

	void forwards();
	void backwards();
	void rotateLeft();
	void rotateRight();

	void leftMotorOff();
	void leftMotorOn();
	void rightMotorOff();
	void rightMotorOn();

private:
	Motor leftMotor;
	Motor rightMotor;
	int speed;
};

#endif // MOTOR_H
