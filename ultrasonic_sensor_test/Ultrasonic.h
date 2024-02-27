#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

#define CM true
#define INCH false

class Ultrasonic {
  public:
    Ultrasonic(int trigger, int echo, int interrupt, int max_dist=200);
    
    void begin();
    void start();
    bool isFinished(){ return _finished; }
    unsigned int getRange(bool units=CM);
    static Ultrasonic* instance(){ return _instance; }
    
  private:
    static void _echo_isr();
    
    int _trigger, _echo, _int, _max;
    volatile unsigned long _start, _end;
    volatile bool _finished;
    static Ultrasonic* _instance;
};

#endif