#ifndef detect_event_h
#define detect_event_h
#endif

#include "Arduino.h"

class detect_event
{
  private:
    const unsigned short timer;
    friend void TC2_Handler(void);
    static float _duration;
  
  public:
    detect_event(void);
    int start(float);
    int start(int, float);
    int start(int, int, float);
    detect_event& stop();
    int _eventCode;
};

extern detect_event detect;
extern volatile double trialData[54];
extern volatile int eventFlag;
extern volatile int eventCode;
extern volatile int eventStatus;
extern volatile int trialNumber;
extern volatile int eventNumber;
extern volatile double eventTime;
extern volatile double eventDuration;