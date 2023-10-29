
#ifndef PulsedTrigger_h
#define PulsedTrigger_h
#endif

#include "Arduino.h"

class PulsedTrigger
{
  private:
    const unsigned short timer;
    friend void TC5_Handler(void);
    float _duration;
    float freq;
    
  public:
    PulsedTrigger(void);
    PulsedTrigger& start(int, float);
    PulsedTrigger& start(int, float, float);
    PulsedTrigger& stop(); 
};

extern PulsedTrigger pulsedTrigger;
extern volatile int _pulsePin;
extern volatile int _pulseCount;
extern volatile int _nPulses;