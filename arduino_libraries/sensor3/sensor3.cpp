#include "Arduino.h"
#include "sensor3.h"

sensor3* sensor3::pntr = NULL;

sensor3::sensor3(int sensorPin, int eventCodeIn, int eventCodeOut)
{
	_sensorPin=sensorPin; 
    _eventCodeIn=eventCodeIn;
    _eventCodeOut=eventCodeOut;
    pinMode(_sensorPin, INPUT);
    pntr = this;	   
}

void sensor3::activate()  
{     
    attachInterrupt(digitalPinToInterrupt(_sensorPin), sensor3::go_to_intfunc, CHANGE); 
    eventStatus=0;
}

void sensor3::deactivate()  
{  
    detachInterrupt(_sensorPin); 
}

void sensor3::go_to_intfunc()
{
	pntr->sensorfunction();
}
					

void sensor3::sensorfunction()	
{  
    eventTime=millis();
    if (!!(g_APinDescription[_sensorPin].pPort -> PIO_PDSR & g_APinDescription[_sensorPin].ulPin)==HIGH){eventStatus=_eventCodeOut; eventCode=_sensorPin;}
	if (!!(g_APinDescription[_sensorPin].pPort -> PIO_PDSR & g_APinDescription[_sensorPin].ulPin)==LOW){eventStatus=_eventCodeIn; eventCode=_sensorPin;}
}

