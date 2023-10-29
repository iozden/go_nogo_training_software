//LIBRARIES
#include <parameters.h>
#include <functions.h>

// Sensors
sensor1 waterPortLeft(waterSensorLeft,leftWaterPoke,leftWaterExit);
sensor2 odorPort(odorPortSensor,odorPortPoke,odorPortExit);

// Ephys synch
int odor1synch=819;
int odor2synch=1638;
int odor3synch=2457;
int odor4synch=3276;
int noOdorsynch=4095;

int idleSynch=0;
int odorPortPokeSynch=372;
int odorOnsetSynch=838;
int odorPortExitSynch=1303;
int notUsed1Synch=1769;
int notUsed2Synch=2234;
int feedbackBadSynch=2700;
int feedbackGoodSynch=3165;
int rewardSynch=3631;
int laserSynch=4095;

void setup() 
{  
  Serial.begin(115200); 
  randomSeed(analogRead(0));
  set_all();
  waterPortLeft.activate();
  odorPort.activate();
  pinMode (DAC0,OUTPUT);
  pinMode (DAC1,OUTPUT);
  analogWriteResolution(12);
}

void loop() 
{ 
  switch (trainingPhase)
  {
      case 1:
        startTrial();
        detect.start(leftWaterPoke,waitforEntry);
        if (eventFlag==leftWaterPoke)
        {
          deliverFeedback(waterDeliveryLeft,rewardDuration,beep,feedbackDuration);
          endTrial(correctResp,iti+random(0,maxWait));
          //endTrial(correctResp,500);     
        }
        else {endTrial(noEntry);}
        break;
      
      case 2:
        extraWaitTime=floor(correctSoFar/incrementInBlocksOf)*stepWait+minWait;
        if (extraWaitTime>1000) {extraWaitTime=1000;}
        startTrial();
        detect.start(odorPortPoke,waitforEntry);
        if (eventFlag==0){endTrial(noEntry);}
        else
        {
          detect.start(odorPortExit,settleTime);   
          if (eventFlag==odorPortExit){endTrial(earlyResp);}
          else
          {
            set_pins(air,odor1); 
            detect.start(odorPortExit,extraWaitTime); 
            if (eventFlag==odorPortExit){clear_pins(air,odor1);endTrial(earlyResp);}
            else
            {
              clear_pins(air,odor1); 
              trigger(beep,beepShort);      
              detect.start(leftWaterPoke,maxRespTime);
              if (eventFlag==0) {endTrial(incorrectResp);}
              else
              {
                deliverFeedback(waterDeliveryLeft,rewardDuration,beep,feedbackDuration);
                endTrial(correctResp);
                correctSoFar=correctSoFar+1; 
                delay(iti);
              }
            }
          }
        }
        break;

      case 3:
         extraWaitTime=floor(correctSoFar/incrementInBlocksOf)*stepWait+minWait;
        if (extraWaitTime>1000) {extraWaitTime=1000;}
        startTrial();
        detect.start(odorPortPoke,waitforEntry); 
        if (eventFlag==0){endTrial(noEntry); break;}
       
        detect.start(odorPortExit,settleTime);   
        if (eventFlag==odorPortExit){endTrial(earlyResp);break;}
  
        set_pins(finalValve,air,odor1); 
        detect.start(odorPortExit,odorSettleTime);   
        if (eventFlag==odorPortExit){endTrial(earlyResp);clear_pins(odor1,air,finalValve);break;}
  
        clear_pins(finalValve);
        detect.start(odorPortExit,extraWaitTime); 
        if (eventFlag==odorPortExit){clear_pins(odor1,air);endTrial(earlyResp);break;}
       
        detect.start(odorPortExit,getOutTime); 
        if (eventFlag==0){clear_pins(air,odor1);endTrial(incorrectResp);break;}
  
        clear_pins(air,odor1,finalValve);       
        detect.start(leftWaterPoke,maxRespTime);
        if (eventFlag==0) {endTrial(incorrectResp);break;}
  
        deliverFeedback(waterDeliveryLeft,rewardDuration,beep,feedbackDuration);
        endTrial(correctResp);
        correctSoFar=correctSoFar+1; 
        delay(iti);
        break;  
      
      case 4:
        startTrial(); analogWrite(DAC0,odor1synch*trialType); analogWrite(DAC1,0);
        detect.start(odorPortPoke,waitforEntry); 
        if (eventFlag==0){analogWrite(DAC0,0); endTrial(noEntry,500); break;}
        
        analogWrite(DAC1,odorPortPokeSynch);
        detect.start(odorPortExit,settleTime);   
        if (eventFlag==odorPortExit){analogWrite(DAC0,0);analogWrite(DAC1,0);endTrial(earlyResp,punishment);break;}
  
        set_pins(finalValve,air,odor); 
        detect.start(odorPortExit,odorSettleTime);   
        if (eventFlag==odorPortExit){clear_pins(odor,air,finalValve);analogWrite(DAC0,0);analogWrite(DAC1,0);endTrial(earlyResp,punishment);break;}
  
        clear_pins(finalValve); analogWrite(DAC1,odorOnsetSynch);
        detect.start(odorPortExit,cueDuration); 
        if (eventFlag==odorPortExit){clear_pins(odor,air,finalValve); analogWrite(DAC0,0);analogWrite(DAC1,0);endTrial(earlyResp,punishment);break;}
        if (correctStim==1) {laser.start(20,25);analogWrite(DAC1,laserSynch);}
        detect.start(odorPortExit,getOutTime); 
        clear_pins(odor,air,finalValve);
        
        if (eventFlag==0) 
        {
          if (Go==0)
          {
            laser.stop2();
            analogWrite(DAC1,feedbackGoodSynch);deliverSound(correctSound,feedbackDuration); analogWrite(DAC0,0); analogWrite(DAC1,0); endTrial(correctResp,iti); 
            break;                   
          }
          else 
          {
            laser.stop2();       
            analogWrite(DAC1,feedbackBadSynch);deliverSound(incorrectSound,feedbackDuration); analogWrite(DAC0,0); analogWrite(DAC1,0); endTrial(incorrectResp,iti);
            break;
          }   
        }
              
        analogWrite(DAC1,odorPortExitSynch); detect.start(leftWaterPoke,maxRespTime);        
        
        if (eventFlag==0) 
        {      
          if (Go==0)
          {
            laser.stop2();         
            analogWrite(DAC1,feedbackGoodSynch);deliverSound(correctSound,feedbackDuration); analogWrite(DAC0,0); analogWrite(DAC1,0); endTrial(correctResp,iti);
            break;
          }
          else 
          {
            laser.stop2();             
            analogWrite(DAC1,feedbackBadSynch);deliverSound(incorrectSound,feedbackDuration); analogWrite(DAC0,0); analogWrite(DAC1,0); endTrial(incorrectResp,iti);
            break;
          }    
        }
  
        if (Go==0)
        {
          laser.stop2();           
          analogWrite(DAC1,feedbackBadSynch);deliverSound(incorrectSound,feedbackDuration); analogWrite(DAC0,0); analogWrite(DAC1,0); endTrial(incorrectResp,iti);
          break;
        }
        laser.stop2();
        analogWrite(DAC1,feedbackGoodSynch);deliverFeedback(beep,feedbackDuration);
        analogWrite(DAC1,rewardSynch);deliverFeedback(waterDeliveryLeft,rewardDuration);
        analogWrite(DAC0,0); analogWrite(DAC1,0); 
        endTrial(correctResp, iti);
        break; 
  }
}

  
