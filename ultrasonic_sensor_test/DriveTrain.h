#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Motor.h"
using namespace std;

class DriveTrain{
public:
	DriveTrain();
	DriveTrain(const Motor &leftMotor, const Motor &rightMotor, int speed);

	void setSpeed(int newSpeed);
	int getSpeed() const;

	void forwards();
	void backwards();
	void rotateLeft();
	void rotateRight();
	void rotate90Right();
	void rotate90Left();
	void rotate180();
	void stop();

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
