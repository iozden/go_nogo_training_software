#include "Arduino.h"
#include "Trigger1.h"

Trigger1 trigger1;
Trigger1::Trigger1() : timer(){}

Trigger1& Trigger1::set()
{
    pmc_set_writeprotect(false);
    pmc_enable_periph_clk(TC3_IRQn);           
    TC_Configure(TC1,0,TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
    return *this;
}

Trigger1& Trigger1::start(int triggerPin11,float duration1)
{    
    TC_SetRC(TC1,0,VARIANT_MCK/2*duration1);
    TC1->TC_CHANNEL[0].TC_IER=TC_IER_CPCS;
    TC1->TC_CHANNEL[0].TC_IDR=~TC_IER_CPCS;
    NVIC_EnableIRQ(TC3_IRQn);
	NVIC_ClearPendingIRQ(TC3_IRQn);
    TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
    g_APinDescription[triggerPin11].pPort -> PIO_SODR = g_APinDescription[triggerPin11].ulPin;  
    _triggerPin11=triggerPin11; 
    _triggerPin12=triggerPin11; 
    _triggerPin13=triggerPin11; 
    return *this;
}

Trigger1& Trigger1::start(int triggerPin11,int triggerPin12, float duration1)
{
    TC_SetRC(TC1,0,VARIANT_MCK/2*duration1);
    TC1->TC_CHANNEL[0].TC_IER=TC_IER_CPCS;
    TC1->TC_CHANNEL[0].TC_IDR=~TC_IER_CPCS;
    NVIC_EnableIRQ(TC3_IRQn);
	NVIC_ClearPendingIRQ(TC3_IRQn);  
    g_APinDescription[triggerPin11].pPort -> PIO_SODR = g_APinDescription[triggerPin11].ulPin;  
    g_APinDescription[triggerPin12].pPort -> PIO_SODR = g_APinDescription[triggerPin12].ulPin;  
    TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
    _triggerPin11=triggerPin11; 
    _triggerPin12=triggerPin12;  
    _triggerPin13=triggerPin12;   
    return *this;
}

Trigger1& Trigger1::start(int triggerPin11,int triggerPin12, int triggerPin13, float duration1)
{
    TC_SetRC(TC1,0,VARIANT_MCK/2*duration1);
    TC1->TC_CHANNEL[0].TC_IER=TC_IER_CPCS;
    TC1->TC_CHANNEL[0].TC_IDR=~TC_IER_CPCS;
    NVIC_EnableIRQ(TC3_IRQn);
	NVIC_ClearPendingIRQ(TC3_IRQn);  
    g_APinDescription[triggerPin11].pPort -> PIO_SODR = g_APinDescription[triggerPin11].ulPin;  
    g_APinDescription[triggerPin12].pPort -> PIO_SODR = g_APinDescription[triggerPin12].ulPin;  
    g_APinDescription[triggerPin13].pPort -> PIO_SODR = g_APinDescription[triggerPin13].ulPin;  
    TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
    _triggerPin11=triggerPin11; 
    _triggerPin12=triggerPin12;
    _triggerPin13=triggerPin13;     
    return *this;
}

Trigger1& Trigger1::stop()
{
    g_APinDescription[_triggerPin11].pPort -> PIO_CODR = g_APinDescription[_triggerPin11].ulPin;
    g_APinDescription[_triggerPin12].pPort -> PIO_CODR = g_APinDescription[_triggerPin12].ulPin;
    g_APinDescription[_triggerPin13].pPort -> PIO_CODR = g_APinDescription[_triggerPin13].ulPin;
    TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS;
    NVIC_DisableIRQ(TC3_IRQn);
    TC1->TC_CHANNEL[0].TC_IDR=TC_IER_CPCS;  // disable interrupt
    TC_GetStatus(TC1,0);
    return *this;
}

void TC3_Handler(void)
{
    g_APinDescription[_triggerPin11].pPort -> PIO_CODR = g_APinDescription[_triggerPin11].ulPin;
    g_APinDescription[_triggerPin12].pPort -> PIO_CODR = g_APinDescription[_triggerPin12].ulPin;
    g_APinDescription[_triggerPin13].pPort -> PIO_CODR = g_APinDescription[_triggerPin13].ulPin;
    TC_Stop(TC1, 0);
    NVIC_DisableIRQ(TC3_IRQn);
    TC1->TC_CHANNEL[0].TC_IDR=TC_IER_CPCS;  // disable interrupt
    TC_GetStatus(TC1, 0);
}

