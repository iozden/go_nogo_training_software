
#ifndef Trigger1_h
#define Trigger1_h
#endif

#include "Arduino.h"

class Trigger1
{
  private:
    const unsigned short timer;
    friend void TC3_Handler(void);
    float _duration1;
    
  public:
    Trigger1(void);
    Trigger1& set();
    Trigger1& start(int, float);
    Trigger1& start(int, int, float);
    Trigger1& start(int, int, int, float);
    Trigger1& stop(); 
};

extern Trigger1 trigger1;
extern volatile int _triggerPin11;
extern volatile int _triggerPin12;
extern volatile int _triggerPin13;

