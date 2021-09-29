#ifndef __PLL_DRIVER_H
#define __PLL_DRIVER_H

#include "TM4C123.h"                    // Device header
#include <stdint.h>

#define	SYSTEM_CLOCK_MHZ	80000000UL
#define PWM  80000
#define SPEEDSTEP	8000
#define	MAXPWM	72000

void InitPLL(void);
void InitSysTick(uint32_t Ticks);
void SysTick_Wait(uint32_t delay);
void SysTick_Wait1ms(uint32_t delay);

#endif
