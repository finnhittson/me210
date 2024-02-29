#ifndef FINDLINE_H
#define FINDLINE_H

#include "DriveTrain.h"
#include "LimitSwitch.h"
#include "LineSensor.h"

class FindLine {
public:
	enum State {
		DRIVE, 
		ROTATE90,
		ROTATELEFT,
		ROTATERIGHT,
		LINEFOLLOWING
	};
	State state = DRIVE;
	int sensor = -1;
	int delayTime = 70;

	FindLine(
		const DriveTrain &driveTrain, 
		const LineSensor &leftSensor, 
		const LineSensor &rightSensor, 
		const LimitSwitch &topLeft, 
		const LimitSwitch &front, 
		const LimitSwitch &topRight);

	bool detectedBarrier();
	void driveState();
	void rotate90State();
	void rotateLeftState();
	void rotateRightState();
	void findLine();

private:
	DriveTrain driveTrain;
	LineSensor leftSensor;
	LineSensor rightSensor;
	LimitSwitch topLeft;
	LimitSwitch front;
	LimitSwitch topRight;
};

#endif // FINDLINE_H
