//////////////////////////////////////////////////////////////////////
//LIBRARIES
#include <sensor1.h>
#include <sensor2.h>
#include <sensor3.h>
#include <sensor4.h>
#include <sensor5.h>
#include <PulsedTrigger.h>
#include <Trigger1.h>
#include <Trigger2.h>
#include <Pulses1.h>
#include <Pulses2.h>
#include <detect_event.h>
// #include <parameters_for_synchronization_with_ephys.h>

///////////////////////////////////////////////////////////////
// SENSORS
#define pinOdorPortSensor 31
#define pinWaterPortSensorLeft 32 
#define pinWaterPortSensorRight 33 

#define odorPortSensor (int)pinOdorPortSensor
#define waterSensorLeft (int)pinWaterPortSensorLeft
#define waterSensorRight (int)pinWaterPortSensorRight

/////////////////////////////////////////////////////////////////
//CONTROLS
#define pinAirValve 52 
#define pinOdor1Valve 51 
#define pinOdor2Valve 50 
#define pinOdor3Valve 49 
#define pinOdor4Valve 48
#define pinFinalValve 44
#define pinWaterDeliveryLeft 46 
#define pinWaterDeliveryRight 47
#define pinBeep 34 
#define pinBuzz 35
#define pinLaser 36 

#define air (int)pinAirValve
#define odor1 (int)pinOdor1Valve
#define odor2 (int)pinOdor2Valve
#define odor3 (int)pinOdor3Valve
#define odor4 (int)pinOdor4Valve
#define finalValve (int)pinFinalValve
#define waterDeliveryLeft (int)pinWaterDeliveryLeft
#define waterDeliveryRight (int)pinWaterDeliveryRight
#define beep (int)pinBeep
#define buzz (int)pinBuzz

volatile int _pulsePin;
volatile int _pulseCount;
volatile int _nPulses;
volatile int _triggerPin11;
volatile int _triggerPin12;
volatile int _triggerPin13;
volatile int _triggerPin21;
volatile int _triggerPin22;
volatile int _triggerPin23;

/////////////////////////////////////////////////////////////////////
///EVENT CODES
#define nTrial 0
#define trialSelect 1
#define correctResp 2
#define incorrectResp 3
#define noEntry 4
#define earlyResp 5
#define trialStart 6
#define odorPortPoke 7 
#define odorPortExit 8
#define odorOnset 9  
#define odorOffset 10
#define leftWaterPoke 11 
#define leftWaterExit 12 
#define leftWaterOnset 13 
#define leftWaterOffset 14
#define rightWaterPoke 15 
#define rightWaterExit 16 
#define rightWaterOnset 17 
#define rightWaterOffset 18
#define feedbackOnset 19 
#define feedbackOffset 20 
#define laserOnset 21
#define trialEnd 22
#define numCodes (int)53

/////////////////////////////////////////////////////////////////////////////
//VARIABLES
volatile double sensorData[2000][3];  // first column is trialNumber, second is eventCode, third is the time
volatile double trialData[numCodes+1];  
volatile int eventCode=0;
volatile int eventFlag=0;
volatile int eventStatus=0;
volatile int trialNumber=0;
volatile int eventNumber=1;
volatile double eventTime;
volatile double eventDuration;
volatile int onsetind=1;
volatile int offsetind=1;
volatile int correctStim;  //0: no stim, 1:laser stim
volatile int incorrectStim;  //0: no stim, 1:laser stim
volatile int Go; //0: no-go, 1: go
volatile int correctSound; //0: no sound, 1: beep, 2: buzz, 3: sound file
volatile int incorrectSound; //0: no sound, 1: beep, 2: buzz, 3: sound file
volatile int odor;

/////////////////////////////////////////////////////////////////////////////
//PARAMETERS
#define allowedRepNum 3
volatile int trialType=1;
volatile int numRepeat=1;
volatile int lastTrialNum=0;
volatile int trainingPhase=1; 
volatile int numOdors=4;
volatile int odor1cond=0; 
volatile int odor2cond=10; 
volatile int odor3cond=1; 
volatile int odor4cond=11;  //First digit indicates stimcond in correct (0: nostim, 1 stim), second (least significant) in incorrect
volatile int soundcond=12;      //first digit is correct trials, second incorrect. 0: no sound; 1:beep; 2:buzz; 3:sound. For example 33: sound for all trials; 30:sound for correct, nothing for incoorect
volatile float waitforEntry=200; 
volatile double iti=1000; 
volatile float settleTime=300; 
volatile float odorSettleTime=700;
volatile float minWait=100;
volatile float maxWait=1000; 
volatile float stepWait=50;
volatile double cueDuration=200; 
volatile double getOutTime=2200;  
volatile double maxRespTime=1500; 
volatile float minLickDuration=1000; 
volatile double rewardDuration=100; 
volatile double feedbackDuration=200;
volatile double punishment=2500; 
volatile double beepShort=30; 
volatile float freqLaser=20; 
volatile float durPulses=25; 
volatile double durLaser=1000;  
volatile double dtBlank=200;
volatile double dt4Video=2000;
volatile int stim_config=0;

volatile int incrementInBlocksOf=10;  // in number of trials
volatile int correctSoFar=0; // number of correct trials
volatile int extraWaitTime=100;



