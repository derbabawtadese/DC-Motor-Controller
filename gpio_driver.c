#include "gpio_driver.h"

// **************InitGPIO*********************
// Initialize GPIO PortF Pins(0,4); PortA Pins(5) as PWM wave output
// Input: None
// Output: None
void InitGPIO(void)
{
	SYSCTL->RCGCGPIO |= 0x21;
	while((SYSCTL->RCGCGPIO & 0x21) == 0);
	GPIOF->LOCK = 0x4C4F434B;
	GPIOF->CR = 0x11;
	GPIOF->DIR = 0xE;
	GPIOF->DEN = 0x1F;
	GPIOF->PUR = 0x11;
	GPIOF->IS &= ~0x11;		// set PF4,PF0 is edge-sensitive
	GPIOF->IBE &= ~0x11;
	GPIOF->IEV &= 0x11;		// set PF4,PF0 falling edge event
	GPIOF->ICR = 0x11;
	GPIOF->IM = 0x11;
		
	GPIOA->DIR = 0x20;
	GPIOA->DEN = 0x20;
	GPIOA->DR8R = 0x20;
	GPIOA->IS = 0x0;
	GPIOA->IBE = 0x0;
	GPIOA->IEV = 0x20;
	GPIOA->ICR = 0x20;
	GPIOA->IM = 0x20;
	
	NVIC_EnableIRQ(GPIOF_IRQn);		// enable systick exception
	NVIC_SetPriority(GPIOF_IRQn,0);		// set to highest priority	
}

