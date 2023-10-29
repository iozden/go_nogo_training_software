#include "Arduino.h"
#include "Pulses1.h"

Pulses1* Pulses1::pntr = NULL;

Pulses1::Pulses1(void)
{
   pntr = this;	
}

void Pulses1::set(float frequency, float pulsedur, float duration)
{
    _pulsesOn=0;
    pmc_set_writeprotect(false);
    pmc_enable_periph_clk(TC7_IRQn);  // enable clock 7        
    TC_Configure(TC2,1,TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
    _duration=VARIANT_MCK/2*duration/1000;
    TC_SetRC(TC2,1,_duration);
  
    pmc_enable_periph_clk(TC8_IRQn);  //enable clock 8
    REG_PMC_PCER1 |= PMC_PCER1_PID35;                
    REG_PIOD_ABSR |= PIO_ABSR_P7;     
    REG_PIOD_PDR |= PIO_PDR_P7;          
    TC_Configure(TC2,2,TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET | TC_CMR_ASWTRG_SET | TC_CMR_TCCLKS_TIMER_CLOCK1);  
    TC_SetRC(TC2,2, VARIANT_MCK/2/frequency);
    _pulsedur=VARIANT_MCK/2*pulsedur/1000;
    TC_SetRA(TC2,2,_pulsedur);   
    
}

void Pulses1::set(float frequency, float pulsedur, float duration, int eventInd)
{
    _pulsesOn=0;
    _eventInd=eventInd;
    pmc_set_writeprotect(false);
    pmc_enable_periph_clk(TC7_IRQn);     //enable TC7   
    TC_Configure(TC2,1,TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);   
    // waveform generation | clears counter at RC | uses timer clock 1
    _duration=VARIANT_MCK/2*duration/1000;
    TC_SetRC(TC2,1,_duration);
  
    pmc_enable_periph_clk(35); // enable TC8
    pmc_enable_periph_clk(TC8_IRQn);  //enable TC8
    REG_PMC_PCER1 |= PMC_PCER1_PID35;    // peripheral clock enalble register = TC8 (35)        
    REG_PIOD_ABSR |= PIO_ABSR_P7;  //put TIOA8 to PD7 which is pin 11 
    REG_PIOD_PDR |= PIO_PDR_P7;    // disable this pin11 as a general pupose pin.    
    TC_Configure(TC2,2,TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET | TC_CMR_ASWTRG_SET | TC_CMR_TCCLKS_TIMER_CLOCK1);  
    // waveform generation | clears counter at RC | clears TIOA at RA | sets TIOA at RC | Software trigger sets TIOA | uses timer clock 1
    TC_SetRC(TC2,2, VARIANT_MCK/2/frequency);
    _pulsedur=VARIANT_MCK/2*pulsedur/1000;
    TC_SetRA(TC2,2,_pulsedur);   
}

void Pulses1::start()
{    
    if (_pulsesOn==0)
    {
        TC2->TC_CHANNEL[1].TC_IER=TC_IER_CPCS; // enable RC trigger interrupt
        TC2->TC_CHANNEL[1].TC_IDR=~TC_IER_CPCS;  // //remove disable interrupt
        // nested vector interrupt controller enable interrupt
        trialData[_eventInd]=millis();
        NVIC_ClearPendingIRQ(TC7_IRQn);
        NVIC_EnableIRQ(TC7_IRQn);
        TC2->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
        TC2->TC_CHANNEL[2].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG; 
        _pulsesOn=1;
        // enable the clock | a software trigger is issued, the counter is reset and clock is started 
    }
}

void Pulses1::start(float frequency, float pulsedur)
{    
    if (_pulsesOn==0)
    {
        TC_SetRC(TC2,2, VARIANT_MCK/2/frequency);
        _pulsedur=VARIANT_MCK/2*pulsedur/1000;
        TC_SetRA(TC2,2,_pulsedur);  
        trialData[_eventInd]=millis();
        TC2->TC_CHANNEL[2].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
        _pulsesOn=1;  
    }
}

void Pulses1::start(float frequency, float pulsedur, float duration)
{    
    if (_pulsesOn==0)
    {
        _duration=VARIANT_MCK/2*duration/1000;
        TC_SetRC(TC2,1,_duration);
        TC_SetRC(TC2,2, VARIANT_MCK/2/frequency);
        _pulsedur=VARIANT_MCK/2*pulsedur/1000;
        TC_SetRA(TC2,2,_pulsedur);  

        TC2->TC_CHANNEL[1].TC_IER=TC_IER_CPCS; // enable RC trigger interrupt
        TC2->TC_CHANNEL[1].TC_IDR=~TC_IER_CPCS;  // //remove disable interrupt
        // nested vector interrupt controller enable interrupt
        trialData[_eventInd]=millis();
        NVIC_ClearPendingIRQ(TC7_IRQn);
        NVIC_EnableIRQ(TC7_IRQn);
        TC2->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
        TC2->TC_CHANNEL[2].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;  
        _pulsesOn=1;
    }
}

void Pulses1::stop()
{
    if (_pulsesOn==1)
    {
        TC_Stop(TC2,1);
        NVIC_DisableIRQ(TC7_IRQn);
        NVIC_ClearPendingIRQ(TC7_IRQn);
        TC_GetStatus(TC2, 1);
        while (TC2->TC_CHANNEL[2].TC_CV<=_pulsedur) {}     
        TC_Stop(TC2,2);
        //TC2->TC_CHANNEL[1].TC_IDR=TC_IER_CPCS;  // disable interrupt 
        _pulsesOn=0;
    }
}

void Pulses1::stop2()
{
    if (_pulsesOn==1)
    {
        while (TC2->TC_CHANNEL[2].TC_CV<=_pulsedur) {}     
        TC_Stop(TC2,2);
        TC_GetStatus(TC2, 2);
        //TC2->TC_CHANNEL[1].TC_IDR=TC_IER_CPCS;  // disable interrupt  
        _pulsesOn=0;
    } 
}

void TC7_Handler() 
{   
    TC_GetStatus(TC2, 1);
    Pulses1::pntr->stop();
}


void TC8_Handler() {TC_GetStatus(TC2, 2);}