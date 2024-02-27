#ifndef MOTOR_H
#define MOTOR_H

class Motor {
public:
	Motor();
	Motor(const int in, const int out, const int enable);
	Motor(const int in, const int out, const int enable, const int speed);

	void setSpeed(int speed);
	int getSpeed(void) const;

	void stop();
	void forwards();
	void backwards();

private:
	int in;
	int out;
	int enable;
	int speed = 0;
};

#endif // MOTOR_H
