#include "Ultrasonic.h"

//Ultrasonic *Ultrasonic::_instance=NULL;
Ultrasonic *Ultrasonic::_instance(NULL);

Ultrasonic::Ultrasonic(int trigger, int echo, int interrupt, int max_dist)
    : _trigger(trigger), _echo(echo), _int(interrupt), _max(max_dist), _finished(false)
{
  if(_instance==0) _instance=this;    
}

void Ultrasonic::begin(){
  pinMode(_trigger, OUTPUT);
  digitalWrite(_trigger, LOW);
  pinMode(_echo, INPUT);  
  attachInterrupt(_int, _echo_isr, CHANGE);
}

void Ultrasonic::start(){
  _finished=false;
  digitalWrite(_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigger, LOW);  
}

unsigned int Ultrasonic::getRange(bool units){
  return (_end-_start)/((units)?58:148);
}

void Ultrasonic::_echo_isr(){
  Ultrasonic* _this=Ultrasonic::instance();
  
  switch(digitalRead(_this->_echo)){
    case HIGH:
      _this->_start=micros();
      break;
    case LOW:
      _this->_end=micros();
      _this->_finished=true;
      break;
  }   
}
