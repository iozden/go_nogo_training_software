#include "Arduino.h"
#include "PulsedTrigger.h"

PulsedTrigger pulsedTrigger;
PulsedTrigger::PulsedTrigger() : timer(){}

PulsedTrigger& PulsedTrigger::start(int pulsePin,float duration)
{    
    pmc_set_writeprotect(false);
    pmc_enable_periph_clk(TC5_IRQn);           
    TC_Configure(TC1,2,TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
    TC_SetRC(TC1,2,VARIANT_MCK/2*duration/1000);
    TC1->TC_CHANNEL[2].TC_IER=TC_IER_CPCS;
    TC1->TC_CHANNEL[2].TC_IDR=~TC_IER_CPCS;
    NVIC_EnableIRQ(TC5_IRQn);
	NVIC_ClearPendingIRQ(TC5_IRQn);
    TC1->TC_CHANNEL[2].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
    g_APinDescription[pulsePin].pPort -> PIO_SODR = g_APinDescription[pulsePin].ulPin;  
    _pulsePin=pulsePin;
    _pulseCount=1;
    _nPulses=0;
    return *this;
}

PulsedTrigger& PulsedTrigger::start(int pulsePin,float freq, float duration)
{    
    pmc_set_writeprotect(false);
    pmc_enable_periph_clk(TC5_IRQn);           
    TC_Configure(TC1,2,TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
    TC_SetRC(TC1,2,VARIANT_MCK/2/(2*freq));   
    TC1->TC_CHANNEL[2].TC_IER=TC_IER_CPCS;
    TC1->TC_CHANNEL[2].TC_IDR=~TC_IER_CPCS;
    NVIC_EnableIRQ(TC5_IRQn);
	NVIC_ClearPendingIRQ(TC5_IRQn);
    TC1->TC_CHANNEL[2].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
    g_APinDescription[pulsePin].pPort -> PIO_SODR = g_APinDescription[pulsePin].ulPin;  
    _pulsePin=pulsePin; 
    _pulseCount=0;
    _nPulses=2*freq*duration/1000;
    return *this;
}

PulsedTrigger& PulsedTrigger::stop()
{
    g_APinDescription[_pulsePin].pPort -> PIO_CODR = g_APinDescription[_pulsePin].ulPin;
    TC1->TC_CHANNEL[2].TC_CCR = TC_CCR_CLKDIS;
    NVIC_DisableIRQ(TC5_IRQn);
    TC1->TC_CHANNEL[2].TC_IDR=TC_IER_CPCS;  // disable interrupt
    TC_GetStatus(TC1,2);
    return *this;
}

void TC5_Handler(void)
{
    if (_pulseCount<=_nPulses)
    {
        if (!!(g_APinDescription[_pulsePin].pPort -> PIO_PDSR & g_APinDescription[_pulsePin].ulPin)) 
            {g_APinDescription[_pulsePin].pPort -> PIO_CODR = g_APinDescription[_pulsePin].ulPin;}
        else    
            {g_APinDescription[_pulsePin].pPort -> PIO_SODR = g_APinDescription[_pulsePin].ulPin;}
        TC_GetStatus(TC1, 2);
        _pulseCount++;
    }
    else
    {
        TC_Stop(TC1, 2);
        NVIC_DisableIRQ(TC5_IRQn);
        TC1->TC_CHANNEL[2].TC_IDR=TC_IER_CPCS;  // disable interrupt
        TC_GetStatus(TC1, 2);
        g_APinDescription[_pulsePin].pPort -> PIO_CODR = g_APinDescription[_pulsePin].ulPin;
    }
}

