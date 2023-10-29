
#include "Arduino.h"
#include "Trigger2.h"

Trigger2 trigger2;
Trigger2::Trigger2() : timer(){}

Trigger2& Trigger2::set()
{
    pmc_set_writeprotect(false);
    pmc_enable_periph_clk(TC4_IRQn);           
    TC_Configure(TC1,1,TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
    return *this;
}

Trigger2& Trigger2::start(int triggerPin21,float duration1)
{    
    TC_SetRC(TC1,1,VARIANT_MCK/2*duration1);
    TC1->TC_CHANNEL[1].TC_IER=TC_IER_CPCS;
    TC1->TC_CHANNEL[1].TC_IDR=~TC_IER_CPCS;
    NVIC_EnableIRQ(TC4_IRQn);
	NVIC_ClearPendingIRQ(TC4_IRQn);
    TC1->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
    g_APinDescription[triggerPin21].pPort -> PIO_SODR = g_APinDescription[triggerPin21].ulPin;  
    _triggerPin21=triggerPin21; 
    _triggerPin22=triggerPin21; 
    _triggerPin23=triggerPin21; 
    return *this;
}

Trigger2& Trigger2::start(int triggerPin21,int triggerPin22, float duration1)
{
    TC_SetRC(TC1,1,VARIANT_MCK/2*duration1);
    TC1->TC_CHANNEL[1].TC_IER=TC_IER_CPCS;
    TC1->TC_CHANNEL[1].TC_IDR=~TC_IER_CPCS;
    NVIC_EnableIRQ(TC4_IRQn);
	NVIC_ClearPendingIRQ(TC4_IRQn);  
    g_APinDescription[triggerPin21].pPort -> PIO_SODR = g_APinDescription[triggerPin21].ulPin;  
    g_APinDescription[triggerPin22].pPort -> PIO_SODR = g_APinDescription[triggerPin22].ulPin;  
    TC1->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
    _triggerPin21=triggerPin21; 
    _triggerPin22=triggerPin22;  
    _triggerPin23=triggerPin22;   
    return *this;
}

Trigger2& Trigger2::start(int triggerPin21,int triggerPin22, int triggerPin23, float duration1)
{
    TC_SetRC(TC1,1,VARIANT_MCK/2*duration1);
    TC1->TC_CHANNEL[1].TC_IER=TC_IER_CPCS;
    TC1->TC_CHANNEL[1].TC_IDR=~TC_IER_CPCS;
    NVIC_EnableIRQ(TC4_IRQn);
	NVIC_ClearPendingIRQ(TC4_IRQn);  
    g_APinDescription[triggerPin21].pPort -> PIO_SODR = g_APinDescription[triggerPin21].ulPin;  
    g_APinDescription[triggerPin22].pPort -> PIO_SODR = g_APinDescription[triggerPin22].ulPin;  
    g_APinDescription[triggerPin23].pPort -> PIO_SODR = g_APinDescription[triggerPin23].ulPin;  
    TC1->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
    _triggerPin21=triggerPin21; 
    _triggerPin22=triggerPin22;
    _triggerPin23=triggerPin23;     
    return *this;
}

Trigger2& Trigger2::stop()
{
    g_APinDescription[_triggerPin21].pPort -> PIO_CODR = g_APinDescription[_triggerPin21].ulPin;
    g_APinDescription[_triggerPin22].pPort -> PIO_CODR = g_APinDescription[_triggerPin22].ulPin;
    g_APinDescription[_triggerPin23].pPort -> PIO_CODR = g_APinDescription[_triggerPin23].ulPin;
    TC1->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKDIS;
    NVIC_DisableIRQ(TC4_IRQn);
    TC1->TC_CHANNEL[1].TC_IDR=TC_IER_CPCS;  // disable interrupt
    TC_GetStatus(TC1,1);
    return *this;
}

void TC4_Handler(void)
{
    g_APinDescription[_triggerPin21].pPort -> PIO_CODR = g_APinDescription[_triggerPin21].ulPin;
    g_APinDescription[_triggerPin22].pPort -> PIO_CODR = g_APinDescription[_triggerPin22].ulPin;
    g_APinDescription[_triggerPin23].pPort -> PIO_CODR = g_APinDescription[_triggerPin23].ulPin;
    TC_Stop(TC1, 1);
    NVIC_DisableIRQ(TC4_IRQn);
    TC1->TC_CHANNEL[1].TC_IDR=TC_IER_CPCS;  // disable interrupt
    TC_GetStatus(TC1, 1);
}

