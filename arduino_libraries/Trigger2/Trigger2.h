
#ifndef Trigger2_h
#define Trigger2_h
#endif

#include "Arduino.h"

class Trigger2
{
  private:
    const unsigned short timer;
    friend void TC4_Handler(void);
    float _duration1;
    float _duration2;
    
  public:
    Trigger2(void);
    Trigger2& set();
    Trigger2& start(int, float);
    Trigger2& start(int, int, float);
    Trigger2& start(int, int, int, float);
    Trigger2& stop(); 
};

extern Trigger2 trigger2;
extern volatile int _triggerPin21;
extern volatile int _triggerPin22;
extern volatile int _triggerPin23;

