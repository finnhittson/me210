#ifndef LINEFOLLOWING_H
#define LINEFOLLOWING_H 

#include "LineSensor.h"
#include "DriveTrain.h"

class LineFollowing {
public:
	long double prevSwitchTime;
	int rapidSwitchCount = 0;
	int prevSensor = -1;
	int currentSensor = -1;
	LineFollowing(const LineSensor &leftSensor, const LineSensor &rightSensor, const DriveTrain &driveTrain);

	bool rapidSwitching();
	int followLine();
	int findLine(int mode);

private:
	LineSensor leftSensor;
	LineSensor rightSensor;
	DriveTrain driveTrain;
};

#endif // LINEFOLLOWING_H
