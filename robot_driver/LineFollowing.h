#ifndef LINEFOLLOWING_H
#define LINEFOLLOWING_H 

#include "LineSensor.h"
#include "DriveTrain.h"
#include <HCSR04.h>
#include <Arduino.h>

class LineFollowing {
public:
	long double prevSwitchTime;
	int rapidSwitchCount = 0;
	int prevSensor = -1;
	int currentSensor = -1;
  unsigned long cycleDur = 60000;    // [micros] sensing cycle >60ms
  unsigned long lastTime = micros();
	LineFollowing(const LineSensor &leftSensor, const LineSensor &rightSensor, const DriveTrain &driveTrain, const HCSR04 &uF);

	bool rapidSwitching();
	int followLine();
	int findLine(int mode);
  bool AtFrontWall(const HCSR04 &uF, float thresh = 3.0);

private:
	LineSensor leftSensor;
	LineSensor rightSensor;
	DriveTrain driveTrain;
  HCSR04 uF;
};

#endif // LINEFOLLOWING_H
