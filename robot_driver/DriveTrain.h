#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Motor.h"
using namespace std;

class DriveTrain{
public:
	DriveTrain();
	DriveTrain(const Motor &leftMotor, const Motor &rightMotor, int dutyLeft, int dutyRight);

	void setLeftDuty(int newLeftDuty);
	void setRightDuty(int newRightDuty);

	void forwards();
	void backwards();
	void rotateLeft();
  void rotateLeftPivot();
  void rotateRightPivot();
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
	int dutyLeft;
	int dutyRight;
};

#endif // MOTOR_H
