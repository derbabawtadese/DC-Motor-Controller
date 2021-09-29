#include "pll_driver.h" 

//************InitPLL********************
// Initialize PLL to 80MHz
// Input: None
// Output: None      
void InitPLL(void)
{
	SYSCTL->RCC2 = 0x80000000;				// Use RCC2
	SYSCTL->RCC &= ~(0x1<<22 | 0x0<<11);	// Setting the BYPASS bit and clearing the USESYS bit
	SYSCTL->RCC &= ~(0x8<<4 | 0x2<<8);		// Select the crystal value (XTAL - 10101 = 0x15 -> 16MHz) and oscillator source (OSCSRC - Main Osc)			
	SYSCTL->RCC2 |= 0x40000000;  			// Set DIV400
	SYSCTL->RCC2 &= ~(0xC<<20 | 0xE<<24);	// Select the desired system divider (SYSDIV)
	SYSCTL->RCC &= ~(0<<22);				// Set the USESYS bit
	while((SYSCTL->RIS & 0x40) == 0){}		// Wait for the PLL to lock by polling the PLLLRIS bit
	SYSCTL->RCC &= ~(0x1<<11);				// Clearing the BYPASS bit
}

//************InitSysTick********************
// Initialize Systick 
// Input:  Numbe of interrupts ticks; 1 period ~ 12.5ns
// Output: None
void InitSysTick(uint32_t Ticks)
{
	SysTick->LOAD = Ticks-1;  				// number of interrupts ticks 
	SysTick->VAL = 0;						// 
	SysTick->CTRL = 0x07;					// enable SysTick with core clock & interrupts	
	NVIC_EnableIRQ(SysTick_IRQn);			// enable systick exception
	NVIC_SetPriority(SysTick_IRQn,0);		// set to highest priority	
}
