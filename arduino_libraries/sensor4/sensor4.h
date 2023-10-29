#ifndef sensor4_h
#define sensor4_h
#endif

#include "Arduino.h"

class sensor4
{
	public:
		sensor4(int sensorPin, int eventCodeIn, int eventCodeOut);          
		void activate(); 
        void deactivate();   
         					
	private:
		static void go_to_intfunc();  
		void sensorfunction();								
		int _sensorPin; 
		int _eventCodeIn; 
		int _eventCodeOut; 
		static sensor4* pntr;  
};

// extern double event_log[1000][6];
// extern int event_num;
extern volatile int eventCode;
extern volatile int eventStatus;
extern volatile double eventTime;

