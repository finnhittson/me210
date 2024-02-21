#ifndef MOTOR_H
#define MOTOR_H

class Motor {
public:
    int motorPin1;
    int motorPin2;
    int enablePin;

    Motor();
    Motor(const int mp1, const int mp2, const int enable);

    void setSpeed(int speed);
    void spinForwards();
    void spinBackwards();
};

#endif // MOTOR_H
