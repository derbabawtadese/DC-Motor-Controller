/*
; 1. This program controls a DC motor through PWM modification using user switches.
;    User switch 1 increase the speed by %10.
;    User switch 2 decrease the speed by %10 

; 2. Hardware connections:
;    2.1 User switch 1 connected to PF4; User switch 2 connected to PF0
;	 2.2 PA5 connected to either IA/IB on the L9110 ASIC motor control

; 3. CPU clock source Freq. 80.00MHz using internal PLL
; Author:
;    Derbabaw Tadese
; Date: 
;    09/14/2021
*/

#include "gpio_driver.h"
#include "pll_driver.h" 

// initial values 50% PWM dutty cycle ~ 0.5ms
uint32_t l = 40000;
uint32_t h = 40000;

int main(void)
{	
	__disable_irq();			// disable interrupts while initializing

	InitPLL();					// 80MHz clock
	InitSysTick(80000);			// SysTick will tick every ~ 1ms
	InitGPIO();

	__enable_irq();				// enable after all initialization are done

	while(1)
	{
		__WFE();				// wait for event
	}
}

// **************GPIOF_Handler*********************
// Dummy exception handlers
// Input: None
// Output: none
void GPIOF_Handler(void)
{
	if((GPIOF->RIS & 0x01))
	{	
		if(l < MAXPWM)
		{
			l = l + SPEEDSTEP;	// increase the speed by %10 
		}
		GPIOF->ICR = 0x01;		// clear interrupts flag
		GPIOF->DATA |= 0x1;
	}
	else if((GPIOF->RIS & 0x10))
	{
		if(l > SPEEDSTEP)
		{
			l = l - SPEEDSTEP;	// decrease the speed by %10 
		}
		GPIOF->ICR = 0x10;		// clear interrupts flag
		GPIOF->DATA |= 0x10;
	}
	h = PWM - l;				// update variable duty cycle - Ton
}

// **************SysTick_Handler*********************
// Dummy exception handlers
// Input: None
// Output: none
void SysTick_Handler(void)
{
	if((GPIOA->DATA & 0x20))
	{
		GPIOA->DATA &= ~0x20;
		GPIOF->DATA &= ~0x8;
		SysTick->LOAD = l - 1;	// reload systick with new value Toff
	}
	else if (!(GPIOA->DATA & 0x20))
	{
		GPIOA->DATA |= 0x20;
		GPIOF->DATA |= 0x8;
		SysTick->LOAD = h - 1;	// reload systick with new value Ton
	}
}
