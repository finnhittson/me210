#ifndef MOTOR_H
#define MOTOR_H

class Motor {
public:
	int motorPin1;
	int motorPin2;

	Motor();
	Motor(const int mp1, const int mp2);
	Motor(const int mp1, const int mp2, const int speed);

	void setSpeed(int speed);
	int getSpeed(void) const;

	void stop();
	void spinForwards();
	void spinBackwards();

private:
	 int speed = 0;
};

#endif // MOTOR_H
