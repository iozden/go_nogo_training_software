#ifndef sensor3_h
#define sensor3_h
#endif

#include "Arduino.h"

class sensor3
{
	public:
		sensor3(int sensorPin, int eventCodeIn, int eventCodeOut);          
		void activate(); 
        void deactivate();   
         					
	private:
		static void go_to_intfunc();  
		void sensorfunction();								
		int _sensorPin; 
		int _eventCodeIn; 
		int _eventCodeOut; 
		static sensor3* pntr;  
};

// extern double event_log[1000][6];
// extern int event_num;
extern volatile int eventCode;
extern volatile int eventStatus;
extern volatile double eventTime;

