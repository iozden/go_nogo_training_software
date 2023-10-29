#include "Arduino.h"
#include "Pulses2.h"

Pulses2* Pulses2::pntr = NULL;

Pulses2::Pulses2(void)
{
   pntr = this;	
}

void Pulses2::set(float frequency, float pulsedur, float duration)
{
    pmc_set_writeprotect(false);  
    pmc_enable_periph_clk(TC6_IRQn);           
    TC_Configure(TC2,0,TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
    TC_SetRC(TC2,0,VARIANT_MCK/2*duration/1000);
  
    pmc_enable_periph_clk(27); //pin 2, XC0: 22
    pmc_enable_periph_clk(TC0_IRQn);
    REG_PMC_PCER0 |= PMC_PCER0_PID27;                 
    REG_PIOB_ABSR |= PIO_ABSR_P25;     
    REG_PIOB_PDR |= PIO_PDR_P25;         
    TC_Configure(TC0,0,TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET | TC_CMR_ASWTRG_SET | TC_CMR_TCCLKS_TIMER_CLOCK1);  
    TC_SetRC(TC0,0, VARIANT_MCK/2/frequency);
    _pulsedur=VARIANT_MCK/2*pulsedur/1000;
    TC_SetRA(TC0,0,_pulsedur);  
}

void Pulses2::start()
{    
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
    TC2->TC_CHANNEL[0].TC_IER=TC_IER_CPCS;
    TC2->TC_CHANNEL[0].TC_IDR=~TC_IER_CPCS;
    NVIC_EnableIRQ(TC6_IRQn);
	NVIC_ClearPendingIRQ(TC6_IRQn);
    TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}

void Pulses2::stop()
{
    while (TC0->TC_CHANNEL[0].TC_CV<=_pulsedur) {}     
    TC_Stop(TC2,0); 
    TC_Stop(TC0,0);
    //NVIC_DisableIRQ(TC6_IRQn);
    TC2->TC_CHANNEL[0].TC_IDR=TC_IER_CPCS;  // disable interrupt   
    TC_GetStatus(TC2, 0);
}



void TC6_Handler() 
{   
    TC_GetStatus(TC2, 0);
    Pulses2::pntr->stop();
}


void TC0_Handler() {TC_GetStatus(TC0, 0);}