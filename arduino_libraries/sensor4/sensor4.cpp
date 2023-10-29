#include "Arduino.h"
#include "sensor4.h"

sensor4* sensor4::pntr = NULL;

sensor4::sensor4(int sensorPin, int eventCodeIn, int eventCodeOut)
{
	_sensorPin=sensorPin; 
    _eventCodeIn=eventCodeIn;
    _eventCodeOut=eventCodeOut;
    pinMode(_sensorPin, INPUT);
    pntr = this;	   
}

void sensor4::activate()  
{     
    attachInterrupt(digitalPinToInterrupt(_sensorPin), sensor4::go_to_intfunc, CHANGE); 
    eventStatus=0;
}

void sensor4::deactivate()  
{  
    detachInterrupt(_sensorPin); 
}

void sensor4::go_to_intfunc()
{
	pntr->sensorfunction();
}
					

void sensor4::sensorfunction()	
{  
    eventTime=millis();
    if (!!(g_APinDescription[_sensorPin].pPort -> PIO_PDSR & g_APinDescription[_sensorPin].ulPin)==HIGH){eventStatus=_eventCodeOut; eventCode=_sensorPin;}
	if (!!(g_APinDescription[_sensorPin].pPort -> PIO_PDSR & g_APinDescription[_sensorPin].ulPin)==LOW){eventStatus=_eventCodeIn; eventCode=_sensorPin;}
}

