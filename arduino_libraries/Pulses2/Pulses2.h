#ifndef Pulses2_h
#define Pulses2_h
#endif

#include "Arduino.h"

class Pulses2
{
  private:
    friend void TC0_Handler(void);
    friend void TC6_Handler(void);
    float _frequency;
    float _pulsedur;
    float _duration;
    static Pulses2* pntr;  
    
  public:
    Pulses2(void);
    void set(float,float,float);
    void start();
    void stop(); 
};



