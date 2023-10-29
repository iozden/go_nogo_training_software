#ifndef Pulses1_h
#define Pulses1_h
#endif

#include "Arduino.h"

class Pulses1
{
  private:
    friend void TC7_Handler(void);
    friend void TC8_Handler(void);
    float _frequency;
    float _pulsedur;
    float _duration;
    int _eventInd;
    int _pulsesOn;
    static Pulses1* pntr;  
    
  public:
    Pulses1(void);
    void set(float,float,float);
    void set(float,float,float,int);
    void start();
    void start(float,float,float);
    void start(float,float);
    void stop(); 
    void stop2(); 
};

extern volatile double trialData[54];


