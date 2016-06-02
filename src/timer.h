/*****************************\
* 	timer.h
*	by staringmonkey
*	Last modified on 10/31/01
\*****************************/

#ifndef TIMERS_H
#define TIMERS_H

#include "include_all.h"

/*///////////////////Definitions////////////////////
#define FREQUENCY_0		0x0
#define FREQUENCY_64		0x1
#define FREQUENCY_256	0x2
#define FREQUENCY_1024	0x3

#define TIMER_CASCADE	0x4
#define TIMER_IRQ		0x40
#define TIMER_ENABLE		0x80

////////////////Function Prototypes/////////////////
void WaitTime(int seconds, int milliSeconds);

///////////////////WaitTime////////////////////
void WaitTime(int seconds, int milliSeconds)
{
	//Enable timers
	REG_TM2CNT = FREQUENCY_256 | TIMER_ENABLE;
	REG_TM3CNT = TIMER_CASCADE | TIMER_ENABLE;

	//Zero out timer values
	REG_TM2D = 0;
	REG_TM3D = 0;

	//Wait until ? seconds have passed
	while(REG_TM3D < seconds)
	{
	}

	//Zero out base/millisecond timer
	REG_TM2D = 0;

	//1 millisecond = max register value (65536) divided by the # milliseconds in a second (1000)	
	//Wait until ? milliseconds have passed
	while(REG_TM2D / (65536/1000) < milliSeconds)
	{
	}

	//Disable timers
	REG_TM2CNT = 0;
	REG_TM3CNT = 0;
	
	//Zero out timer values
	REG_TM2D = 0;
	REG_TM3D = 0;
}*/

void WaitTime(u16 sec, u16 mil)
{
	u16 i;
	for (i=0; i<=(sec*900)+mil; i++) WaitForVsync();
}

#endif
