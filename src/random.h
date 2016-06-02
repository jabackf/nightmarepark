
#ifndef RANDOM_H
#define RANDOM_H

#include "include_all.h"

#define RAND_MAX 32767 
volatile s32 RAND_RandomData; 

void SeedRandom(void)
{ 
	RAND_RandomData = REG_VCOUNT; 
} 


s32 RAND(s32 Value) 
{ 
	RAND_RandomData *= 20077; 
	RAND_RandomData += 12345; 

	return ((((RAND_RandomData >> 16) & RAND_MAX) * Value) >> 15); 
}

u16 difference(u16 a, u16 b)
{
	if (a<=b) return b-a;
	else return a-b;
}


#endif
