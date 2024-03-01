#ifndef HUGWALL_H
#define HUGWALL_H

#include "DriveTrain.h"
#include "LineFollowing.h"
#include <HCSR04.h>
#include "Arduino.h"

class HugWall {
public:
	HugWall(const DriveTrain& driveTrain, const HCSR04& uFront, const HCSR04& uLeft, const HCSR04& uRight, const LineFollowing& lineFollower);
	void DoHugWalling(int mode);

private:
	DriveTrain driveTrain;
	HCSR04 uFront;
	HCSR04 uLeft;
	HCSR04 uRight;
	LineFollowing lineFollower;
};

#endif // MOTOR_H
