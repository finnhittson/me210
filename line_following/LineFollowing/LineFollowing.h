#ifndef LINEFOLLOWING_H
#define LINEFOLLOWING_H 

#include "LineSensor.h"
#include "C:\Users\hitts\Documents\ee118\final_project\me210\motor\motor_test\DriveTrain.h"

class LineFollowing {
public:
	LineFollowing();
	LineFollowing(const LineSensor &leftSensor, const LineSensor &rightSensor, const DriveTrain &driveTrain);

	void followLine(void);

private:
	LineSensor leftSensor;
	LineSensor rightSensor;
	DriveTrain driveTrain;
};

#endif // LINEFOLLOWING_H
