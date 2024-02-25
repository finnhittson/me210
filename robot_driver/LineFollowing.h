#ifndef LINEFOLLOWING_H
#define LINEFOLLOWING_H 

#include "LineSensor.h"
#include "DriveTrain.h"

class LineFollowing {
public:
	LineFollowing(const LineSensor &leftSensor, const LineSensor &rightSensor, const DriveTrain &driveTrain);

	void followLine(void);

private:
	LineSensor leftSensor;
	LineSensor rightSensor;
	DriveTrain driveTrain;
};

#endif // LINEFOLLOWING_H
