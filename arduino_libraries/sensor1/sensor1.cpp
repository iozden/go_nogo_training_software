#include "Arduino.h"
#include "sensor1.h"

sensor1* sensor1::pntr = NULL;

sensor1::sensor1(int sensorPin, int eventCodeIn, int eventCodeOut)
{
	_sensorPin=sensorPin; 
    _eventCodeIn=eventCodeIn;
    _eventCodeOut=eventCodeOut;
    pinMode(_sensorPin, INPUT);
    pntr = this;	   
}

void sensor1::activate()  
{     
    attachInterrupt(digitalPinToInterrupt(_sensorPin), sensor1::go_to_intfunc, CHANGE); 
    //eventStatus=0;
}

void sensor1::deactivate()  
{  
    detachInterrupt(_sensorPin); 
}

void sensor1::go_to_intfunc()
{
	pntr->sensorfunction();
}
					

void sensor1::sensorfunction()	
{  
    eventTime=millis();
    if (!!(g_APinDescription[_sensorPin].pPort -> PIO_PDSR & g_APinDescription[_sensorPin].ulPin)==HIGH){eventCode=_eventCodeOut; eventStatus=_sensorPin;}
	if (!!(g_APinDescription[_sensorPin].pPort -> PIO_PDSR & g_APinDescription[_sensorPin].ulPin)==LOW){eventCode=_eventCodeIn; eventStatus=_sensorPin;}
    sensorData[eventNumber][0]=trialNumber;
    sensorData[eventNumber][1]=eventCode;
    sensorData[eventNumber][2]=eventTime;
    eventNumber++;
}

