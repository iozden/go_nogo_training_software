#include "Arduino.h"

Pulses1 laser;

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void update_parameters()

    {
        Serial.find('p');
        if (trialNumber==1)
        {
            trainingPhase=Serial.parseInt();
            numOdors=Serial.parseInt(); 
            odor1cond=Serial.parseInt(); 
            odor2cond=Serial.parseInt(); 
            odor3cond=Serial.parseInt(); 
            odor4cond=Serial.parseInt();
            soundcond=Serial.parseInt();
            waitforEntry=Serial.parseInt();
            iti=Serial.parseInt();  
            settleTime=Serial.parseInt(); 
            odorSettleTime=Serial.parseInt(); 
            minWait=Serial.parseInt();
            maxWait=Serial.parseInt(); 
            stepWait=Serial.parseInt(); 
            cueDuration=Serial.parseInt();
            getOutTime=Serial.parseInt(); 
            maxRespTime=Serial.parseInt(); 
            minLickDuration=Serial.parseInt(); 
            rewardDuration=Serial.parseInt();
            feedbackDuration=Serial.parseInt();
            punishment=Serial.parseInt();  
            beepShort=Serial.parseInt();
            freqLaser=Serial.parseInt();
            durPulses=Serial.parseInt();  
            durLaser=Serial.parseInt();     
            dtBlank=Serial.parseInt(); 
            dt4Video=Serial.parseInt(); 

            trialData[26]=trainingPhase; trialData[27]=numOdors; trialData[28]=odor1cond; trialData[29]=odor2cond; trialData[30]=odor3cond; trialData[31]=odor4cond;
            trialData[32]=soundcond; trialData[33]=waitforEntry; trialData[34]=iti; trialData[35]=settleTime; trialData[36]=odorSettleTime; 
            trialData[37]=minWait; trialData[38]=maxWait; trialData[39]=stepWait; trialData[40]=cueDuration; trialData[41]=getOutTime; 
            trialData[42]=maxRespTime; trialData[43]=minLickDuration; trialData[44]=rewardDuration; trialData[45]=feedbackDuration; trialData[46]=punishment; 
            trialData[47]=beepShort; trialData[48]=freqLaser; trialData[49]=durLaser; trialData[50]=durPulses;
            trialData[51]=dtBlank; trialData[52]=dt4Video;
            
            laser.set(freqLaser,durPulses,durLaser,laserOnset);

            incorrectSound=(soundcond % 10);
            correctSound=int(soundcond/10);
        }
    }

/////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void setTrialType()
{  

    if (trialType==1)
    {
        odor=odor1;
        Go=1;
        stim_config=int(odor1cond/100);
        odor1cond=odor1cond-stim_config*100;
        correctStim=int(odor1cond/10);
        incorrectStim=(odor1cond % 10);
    }         
    else if (trialType==2)
    {
        odor=odor2;
        Go=0;
        stim_config=int(odor2cond/100);
        odor2cond=odor2cond-stim_config*100;
        correctStim=int(odor2cond/10);
        incorrectStim=(odor2cond % 10); 
    }
    else if (trialType==3)
    {
        odor=odor3;
        Go=1;
        stim_config=int(odor3cond/100);
        odor3cond=odor3cond-stim_config*100;
        correctStim=int(odor3cond/10);
        incorrectStim=(odor3cond % 10);
    }
    else 
    {
        odor=odor4;
        Go=0;
        stim_config=int(odor4cond/100);
        odor4cond=odor4cond-stim_config*100;
        correctStim=int(odor4cond/10);
        incorrectStim=(odor4cond % 10); 
    }
}

//void (*pntrSetTrialType)()=setTrialType;

////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void startTrial()
{
    if (Serial.available()>0) {update_parameters();}
    eventNumber=1;
    if (trialNumber<=1)
    {
        trialData[numCodes]=random(1,numOdors+1);
        lastTrialNum=trialData[numCodes];
        numRepeat=1;
    }

    //Serial.print(trialData[numCodes]);
    //Serial.print("\n");
    
    trialType=(int)trialData[numCodes];
    lastTrialNum=trialData[numCodes];
    
    for (int i=0; i<25; ++i) {trialData[i]=0;}
    trialData[nTrial]=trialNumber;
    trialData[trialSelect]=trialType;
    
    trialData[numCodes]=random(1,numOdors+1);
    if (trialData[numCodes]==lastTrialNum)
    {
        numRepeat=numRepeat+1;
        if (numRepeat>allowedRepNum)
        {
            while (trialData[numCodes]~=lastTrialNum)
            {
                trialData[numCodes]=random(1,numOdors+1);
            }
           numRepeat=1;
        }
    }

    trialData[trialStart]=millis();

    //Serial.print(trialData[numCodes]);
    //Serial.print("\n");

    setTrialType ();  
    //(*pntrSetTrialType)();
    //Serial.print(trialData[numCodes]);
    //Serial.print("\n");

    // // sensorData[2000][3]={0};
    // sensorData[0][0]=trialNumber; 
    // sensorData[0][1]=10*trainingPhase+trialType;   
    // sensorData[0][2]=millis();
}

////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void sendData()
{
    Serial.print("A");
    Serial.print("\n");
    
    for (int i=0; i<(numCodes); i++)
      {
        Serial.print(trialData[i]);
        Serial.print("\t");
      }
    Serial.print(trialData[numCodes]);
    Serial.print("\n"); 
    
    // Serial.print("A");
    // Serial.print("\n");
    
    // for (int i=0; i<(eventNumber+1); i++)
    //   {
    //     Serial.print(sensorData[i][0]);
    //     Serial.print("\t");
    //     Serial.print(sensorData[i][1]);
    //     Serial.print("\t");
    //     Serial.print(sensorData[i][2]);
    //     Serial.print("\n");
    //   }
    // Serial.print("E");
    // Serial.print("\n");
}

//void (*pntrSendData)()=sendData;

////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void sendSensorData()
{   
    Serial.print("A");
    Serial.print("\n");
    
    for (int i=0; i<(eventNumber+1); i++)
      {
        Serial.print(sensorData[i][0]);
        Serial.print("\t");
        Serial.print(sensorData[i][1]);
        Serial.print("\t");
        Serial.print(sensorData[i][2]);
        Serial.print("\n");
      }
    Serial.print("E");
    Serial.print("\n");
}

//void (*pntrSendSensorData)()=sendSensorData;

////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void endTrial(int trialOutcome)
{
    trialData[trialEnd]=millis();
    trialData[trialOutcome]=1;
    sensorData[eventNumber][0]=trialEnd;
    sensorData[eventNumber][1]=trialOutcome;
    sensorData[eventNumber][2]=millis();  
    trialNumber++;
    //(*pntrSendData)();
    sendData();
}

void endTrial(int trialOutcome, float time2wait)
{
    int cnt=0;
    double t=millis();
    while ((millis()-t)<time2wait)
    {
        if (cnt==0)
        {
            cnt=1;
            trialData[trialEnd]=t;
            trialData[trialOutcome]=1;
            // sensorData[eventNumber][0]=trialEnd;
            // sensorData[eventNumber][1]=trialOutcome;
            // sensorData[eventNumber][2]=millis();  
            trialNumber++;
            //(*pntrSendData)();
            sendData();
        }
    }
}

////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void wait(double time2wait)
{
    double t=millis();
    while ((millis()-t)<time2wait){}
}

////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void toggle(int pin)
{
    if(!!(g_APinDescription[pin].pPort -> PIO_PDSR & g_APinDescription[pin].ulPin)) g_APinDescription[pin].pPort -> PIO_CODR = g_APinDescription[pin].ulPin;
    else    g_APinDescription[pin].pPort -> PIO_SODR = g_APinDescription[pin].ulPin;
}


void toggle(int pin1,int pin2)
{
    if (!!(g_APinDescription[pin1].pPort -> PIO_PDSR & g_APinDescription[pin1].ulPin)) {g_APinDescription[pin1].pPort -> PIO_CODR = g_APinDescription[pin1].ulPin;}
    else    {g_APinDescription[pin1].pPort -> PIO_SODR = g_APinDescription[pin1].ulPin;}

    if (!!(g_APinDescription[pin2].pPort -> PIO_PDSR & g_APinDescription[pin2].ulPin)) {g_APinDescription[pin2].pPort -> PIO_CODR = g_APinDescription[pin2].ulPin;}
    else    {g_APinDescription[pin2].pPort -> PIO_SODR = g_APinDescription[pin2].ulPin;}
}


void toggle(int pin1,int pin2, int pin3)
{
    if (!!(g_APinDescription[pin1].pPort -> PIO_PDSR & g_APinDescription[pin1].ulPin)) {g_APinDescription[pin1].pPort -> PIO_CODR = g_APinDescription[pin1].ulPin;}
    else  {g_APinDescription[pin1].pPort -> PIO_SODR = g_APinDescription[pin1].ulPin;}

    if (!!(g_APinDescription[pin2].pPort -> PIO_PDSR & g_APinDescription[pin2].ulPin)) {g_APinDescription[pin2].pPort -> PIO_CODR = g_APinDescription[pin2].ulPin;}
    else  {g_APinDescription[pin2].pPort -> PIO_SODR = g_APinDescription[pin2].ulPin;}
    
    if (!!(g_APinDescription[pin3].pPort -> PIO_PDSR & g_APinDescription[pin3].ulPin)) {g_APinDescription[pin3].pPort -> PIO_CODR = g_APinDescription[pin3].ulPin;}
    else  {g_APinDescription[pin3].pPort -> PIO_SODR = g_APinDescription[pin3].ulPin;}
}

///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void clear_pins(int pin1)
{
    g_APinDescription[pin1].pPort -> PIO_CODR = g_APinDescription[pin1].ulPin;
}

void clear_pins(int pin1,int pin2)
{
    g_APinDescription[pin1].pPort -> PIO_CODR = g_APinDescription[pin1].ulPin;
    g_APinDescription[pin2].pPort -> PIO_CODR = g_APinDescription[pin2].ulPin;
}

void clear_pins(int pin1,int pin2, int pin3)
{
    g_APinDescription[pin1].pPort -> PIO_CODR = g_APinDescription[pin1].ulPin;
    g_APinDescription[pin2].pPort -> PIO_CODR = g_APinDescription[pin2].ulPin;
    g_APinDescription[pin3].pPort -> PIO_CODR = g_APinDescription[pin3].ulPin;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void set_pins(int pin1)
{
    g_APinDescription[pin1].pPort -> PIO_SODR = g_APinDescription[pin1].ulPin;
}

void set_pins(int pin1,int pin2)
{
    g_APinDescription[pin1].pPort -> PIO_SODR = g_APinDescription[pin1].ulPin;
    g_APinDescription[pin2].pPort -> PIO_SODR = g_APinDescription[pin2].ulPin;
}

void set_pins(int pin1,int pin2, int pin3)
{
    g_APinDescription[pin1].pPort -> PIO_SODR = g_APinDescription[pin1].ulPin;
    g_APinDescription[pin2].pPort -> PIO_SODR = g_APinDescription[pin2].ulPin;
    g_APinDescription[pin3].pPort -> PIO_SODR = g_APinDescription[pin3].ulPin;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void trigger(int pin1, float dur1)
{
    toggle(pin1);
    delayMicroseconds(dur1*1000);
    toggle(pin1);
}


void trigger(int pin1, float dur1, int pin2, float dur2)
{
    if (dur1==dur2)
    {
        toggle(pin1); toggle(pin2);
        delayMicroseconds(dur1*1000);
        toggle(pin1); toggle(pin2);
    }
    else if(dur1<dur2)
    {
        toggle(pin1); toggle(pin2);
        delayMicroseconds(dur1*1000);
        toggle(pin1); 
        delayMicroseconds((dur2-dur1)*1000);
        toggle(pin2);
    }

    else
    {
        toggle(pin2); toggle(pin1);
        delayMicroseconds(dur2*1000);
        toggle(pin2); 
        delayMicroseconds((dur1-dur2)*1000);
        toggle(pin1);
    }
}

void trigger(int pin1, float dur1, int pin2, float dur2, int pin3, float dur3)
{
    if (dur1==dur2 && dur1==dur3)
    {
        toggle(pin1); toggle(pin2); toggle(pin3);
        delayMicroseconds(dur1*1000);
        toggle(pin1); toggle(pin2); toggle(pin3);
    }
    else if(dur1==dur2 && dur1<dur3)
    {
        toggle(pin1); toggle(pin2); toggle(pin3);
        delayMicroseconds(dur1*1000);
        toggle(pin1); toggle(pin2);
        delayMicroseconds((dur3-dur1)*1000);
        toggle(pin3);
    }

    else if(dur1<dur2 && dur2==dur3)
    {
        toggle(pin1); toggle(pin2); toggle(pin3);
        delayMicroseconds(dur1*1000);
        toggle(pin1); 
        delayMicroseconds((dur2-dur1)*1000);
        toggle(pin2); toggle(pin3);
    }

    else
    {
        toggle(pin1); toggle(pin2); toggle(pin3);
        delayMicroseconds(dur1*1000);
        toggle(pin1); 
        delayMicroseconds((dur2-dur1)*1000);
        toggle(pin2);
        delayMicroseconds((dur3-dur2)*1000);
        toggle(pin3);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void set_all()
    {
        pinMode(air, INPUT);
        pinMode(odor1, INPUT);
        pinMode(odor2, INPUT);
        pinMode(odor3, INPUT);
        pinMode(odor4, INPUT);
        pinMode(finalValve, INPUT);
        pinMode(waterDeliveryRight, INPUT);
        pinMode(waterDeliveryLeft, INPUT);
        pinMode(beep, INPUT);
        pinMode(buzz, INPUT);
        
        pinMode(air, OUTPUT);
        pinMode(odor1, OUTPUT);
        pinMode(odor2, OUTPUT);
        pinMode(odor3, OUTPUT);
        pinMode(odor4, OUTPUT);
        pinMode(finalValve, OUTPUT);
        pinMode(waterDeliveryRight, OUTPUT);
        pinMode(waterDeliveryLeft, OUTPUT);
        pinMode(beep, OUTPUT);
        pinMode(buzz, OUTPUT);
        laser.set(freqLaser,durPulses,durLaser,laserOnset);
    }

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void trigger_codes(int pin)
    {
        switch (pin)
        {
            case waterDeliveryLeft:
                onsetind=leftWaterOnset;
                offsetind=leftWaterOffset;
                break;
            
            case waterDeliveryRight:
                onsetind=rightWaterOnset;
                offsetind=rightWaterOffset;
                break;

            case beep:
                onsetind=feedbackOnset;
                offsetind=feedbackOffset;
                break;

            case buzz:
                onsetind=feedbackOnset;
                offsetind=feedbackOffset;
                break; 

            case odor1:
                onsetind=odorOnset;
                offsetind=odorOffset;
                break; 

            case odor2:
                onsetind=odorOnset;
                offsetind=odorOffset;
                break; 

            case odor3:
                onsetind=odorOnset;
                offsetind=odorOffset;
                break; 

            case odor4:
                onsetind=odorOnset;
                offsetind=odorOffset;
                break;                                                 
        }     
    }

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void update_sensorData(int event)
{
    sensorData[eventNumber][0]=trialNumber;
    sensorData[eventNumber][1]=event;
    sensorData[eventNumber][2]=millis();
    eventNumber++;
}

void update_sensorData(int event1, int event2)
{
    sensorData[eventNumber][0]=trialNumber;
    sensorData[eventNumber][1]=event1;
    sensorData[eventNumber][2]=millis();
    eventNumber++;
    sensorData[eventNumber][0]=trialNumber;
    sensorData[eventNumber][1]=event2;
    sensorData[eventNumber][2]=millis();
    eventNumber++;
}

void update_sensorData(int event1, int event2, int event3)
{
    sensorData[eventNumber][0]=trialNumber;
    sensorData[eventNumber][1]=event1;
    sensorData[eventNumber][2]=millis();
    eventNumber++;
    sensorData[eventNumber][0]=trialNumber;
    sensorData[eventNumber][1]=event2;
    sensorData[eventNumber][2]=millis();
    eventNumber++;
    sensorData[eventNumber][0]=trialNumber;
    sensorData[eventNumber][1]=event3;
    sensorData[eventNumber][2]=millis();
    eventNumber++;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void deliverFeedback(int pin1, float dur1)
{
    trigger_codes(pin1);
    trialData[onsetind]=millis();
    //update_sensorData(onsetind);
    
    toggle(pin1);
    while ((millis()-trialData[onsetind])<dur1) {}
    toggle(pin1);
    trialData[offsetind]=millis();
    //update_sensorData(offsetind);
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void deliverFeedback(int pin1, float dur1, int pin2, float dur2)
{
    trigger_codes(pin1);
    int onset1=onsetind;
    int offset1=offsetind;
    trigger_codes(pin2);
    
    if (dur1==dur2)
    {
        toggle(pin1); toggle(pin2); 
        trialData[onset1]=millis();
        trialData[onsetind]=millis();
        //update_sensorData(onset1, onsetind);
               
        while ((millis()-trialData[onset1])<dur1) {}
        
        toggle(pin1); toggle(pin2);
        trialData[offset1]=millis();
        trialData[offsetind]=millis();
        //update_sensorData(offset1, offsetind);
    }
    
    else if(dur1<dur2)
    {
        toggle(pin1); toggle(pin2);
        trialData[onset1]=millis();
        trialData[onsetind]=millis();
        //update_sensorData(onset1, onsetind);
        
        while ((millis()-trialData[onset1])<dur1) {}
        toggle(pin1); 
        trialData[offset1]=millis();
        //update_sensorData(offset1);
        
        while ((millis()-trialData[onsetind])<dur2) {}
        toggle(pin2);
        trialData[offsetind]=millis();
        //update_sensorData(offsetind);
    }

    else
    {
        toggle(pin2); toggle(pin1);
        trialData[onset1]=millis();
        trialData[onsetind]=millis();
        //update_sensorData(onset1, onsetind);

        while ((millis()-trialData[onset1])<dur2) {}
        toggle(pin2); 
        trialData[offsetind]=millis();
        //update_sensorData(offsetind);

        while ((millis()-trialData[onsetind])<dur1) {}
        toggle(pin1);
        trialData[offset1]=millis();
        //update_sensorData(offset1);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void deliverSound(int soundCode, float duration)
{        
    switch (soundCode)
    {
        case 0: break;
        case 1: pulsedTrigger.start(beep,feedbackDuration); trialData[feedbackOnset]=millis(); break;
        case 2: pulsedTrigger.start(buzz,500,feedbackDuration); trialData[feedbackOnset]=millis(); break;
    }
}