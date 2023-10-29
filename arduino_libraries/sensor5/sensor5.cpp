#include "Arduino.h"
#include "sensor5.h"

sensor5* sensor5::pntr = NULL;

sensor5::sensor5(int sensorPin, int eventCodeIn, int eventCodeOut)
{
	_sensorPin=sensorPin; 
    _eventCodeIn=eventCodeIn;
    _eventCodeOut=eventCodeOut;
    pinMode(_sensorPin, INPUT);
    pntr = this;	   
}

void sensor5::activate()  
{     
    attachInterrupt(digitalPinToInterrupt(_sensorPin), sensor5::go_to_intfunc, CHANGE); 
    eventStatus=0;
}

void sensor5::deactivate()  
{  
    detachInterrupt(_sensorPin); 
}

void sensor5::go_to_intfunc()
{
	pntr->sensorfunction();
}
					

void sensor5::sensorfunction()	
{  
    eventTime=millis();
    if (!!(g_APinDescription[_sensorPin].pPort -> PIO_PDSR & g_APinDescription[_sensorPin].ulPin)==HIGH){eventStatus=_eventCodeOut; eventCode=_sensorPin;}
	if (!!(g_APinDescription[_sensorPin].pPort -> PIO_PDSR & g_APinDescription[_sensorPin].ulPin)==LOW){eventStatus=_eventCodeIn; eventCode=_sensorPin;}
}

