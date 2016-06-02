#include "gba.h"
/******************************************\
*                          DMA.h by dovoto			
\******************************************/

#ifndef DMA_H
#define DMA_H

//these defines let you control individual bit in the control register

#define DMA_ENABLE					0x80000000
#define DMA_INTERUPT_ENABLE			0x40000000
#define DMA_TIMEING_IMMEDIATE			0x00000000
#define DMA_TIMEING_VBLANK			0x10000000
#define DMA_TIMEING_HBLANK			0x20000000
#define DMA_TIMEING_SYNC_TO_DISPLAY	0x30000000
#define DMA_16						0x00000000
#define DMA_32						0x04000000
#define DMA_REPEATE					0x02000000
#define DMA_SOURCE_INCREMENT			0x00000000
#define DMA_SOURCE_DECREMENT			0x00800000
#define DMA_SOURCE_FIXED				0x01000000
#define DMA_DEST_INCREMENT			0x00000000
#define DMA_DEST_DECREMENT			0x00200000
#define DMA_DEST_FIXED				0x00400000
#define DMA_DEST_RELOAD				0x00600000

//these defines group common options to save typing. You may notice that I don’t have to include the option to increment the source and address register as that is the default.

#define DMA_32NOW              DMA_ENABLE | DMA_TIMEING_IMMEDIATE |DMA_32 
#define DMA_16NOW	   	  DMA_ENABLE | DMA_TIMEING_IMMEDIATE |DMA_16 

void DMA_Copy(u8 channel, void* source, void* dest, u32 WordCount, u32 mode)
{
	switch (channel)
	{
		case 0: 
			REG_DMA0SAD = (u32)source;
			REG_DMA0DAD = (u32)dest;			
			REG_DMA0CNT = WordCount | mode;
			break;
		case 1:
			REG_DMA1SAD = (u32)source;
			REG_DMA1DAD = (u32)dest;
			REG_DMA1CNT = WordCount | mode;
			break;
		case 2:
			REG_DMA2SAD = (u32)source;
			REG_DMA2DAD = (u32)dest;
			REG_DMA2CNT = WordCount | mode;
			break;

		case 3:
			REG_DMA3SAD = (u32)source;
			REG_DMA3DAD = (u32)dest;
			REG_DMA3CNT = WordCount | mode;
			break;

	}
}

#endif

