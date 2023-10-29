#ifndef sensor2_h
#define sensor2_h
#endif

#include "Arduino.h"

class sensor2
{
	public:
		sensor2(int sensorPin, int eventCodeIn, int eventCodeOut);          
		void activate(); 
        void deactivate();   
         					
	private:
		static void go_to_intfunc();  
		void sensorfunction();								
		int _sensorPin; 
		int _eventCodeIn; 
		int _eventCodeOut; 
		static sensor2* pntr;  
};

extern volatile double sensorData[2000][3];
extern volatile int eventCode;
extern volatile int eventStatus;
extern volatile int trialNumber;
extern volatile int eventNumber;
extern volatile double eventTime;
