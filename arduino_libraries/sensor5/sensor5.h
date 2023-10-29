#ifndef sensor5_h
#define sensor5_h
#endif

#include "Arduino.h"

class sensor5
{
	public:
		sensor5(int sensorPin, int eventCodeIn, int eventCodeOut);          
		void activate(); 
        void deactivate();   
         					
	private:
		static void go_to_intfunc();  
		void sensorfunction();								
		int _sensorPin; 
		int _eventCodeIn; 
		int _eventCodeOut; 
		static sensor5* pntr;  
};

// extern double event_log[1000][6];
// extern int event_num;
extern volatile int eventCode;
extern volatile int eventStatus;
extern volatile double eventTime;

