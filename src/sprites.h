//Sprite map
//0 = GameBoard character
//1 = GameBoard lock
//2 = GameBoard key

#ifndef SPRITES_H
#define SPRITES_H

#include "include_all.h"

//attribute0 #defines
#define ROTATION_FLAG		0x100
#define SIZE_DOUBLE		0x200
#define MODE_NORMAL		0x0
#define MODE_TRANSPARENT	0x400
#define MODE_WINDOWED		0x800
#define MOSAIC			0x1000
#define COLOR_16		0x0000
#define COLOR_256		0x2000
#define SQUARE			0x0
#define TALL			0x4000
#define WIDE			0x8000

//attribute1 #defines
#define ROTDATA(n)		((n)<<9)
#define HORIZONTAL_FLIP		0x1000
#define VERTICAL_FLIP		0x2000
#define SIZE_8			0x0
#define SIZE_16			0x4000
#define SIZE_32			0x8000
#define SIZE_64			0xC000

//atrribute2 #defines
#define PRIORITY(n)	        ((n)<<10)
#define PALETTE(n)		((n)<<12)

//sprite structure definitions
typedef struct tagOAMEntry
{
	u16 attribute0;
	u16 attribute1;
	u16 attribute2;
	u16 attribute3;
}OAMEntry, *pOAMEntry;

//sprite rotation information
typedef struct tagRotData
{
	u16 filler1[3];
	u16 pa;
	u16 filler2[3];
	u16 pb;
	u16 filler3[3];
	u16 pc;
	u16 filler4[3];
	u16 pd;
}RotData, *pRotData;

u16* OAM = (u16*)0x7000000;
OAMEntry sprites[128];
pRotData rotData = (pRotData)sprites;

//Copy our sprite array to OAM
void CopyOAM()
{
	u16 loop;
	u16* temp;
	temp = (u16*)sprites;
	for(loop = 0; loop < 128*4; loop++)
	{
		OAM[loop] = temp[loop];
	}
}

void InitializeSprites()
{
	u16 loop;
	for(loop = 0; loop < 128; loop++)
	{
		sprites[loop].attribute0 = 160;  //y
		sprites[loop].attribute1 = 240;  //x
	}
	DMA_Copy(3,(void*)SpritePalette,(void*)OBJPaletteMem,256,DMA_16NOW);
}

void SpritesOff(u16 min, u16 max)
{
	u16 loop;
	for(loop = min; loop <= max; loop++)
	{
		sprites[loop].attribute2 |= PRIORITY(3);
	}
	CopyOAM();
}
void SpritesOn(u16 min, u16 max)
{
	u16 loop;
	for(loop = min; loop <= max; loop++)
	{
		sprites[loop].attribute2 |= PRIORITY(0);
	}
	CopyOAM();
}

void RotateSprite(int rotDataIndex, s32 angle, s32 x_scale,s32 y_scale)
{

	s32 pa,pb,pc,pd;

	pa = ((x_scale) * (s32)COS[angle])>>8;    //(do my fixed point multiplies and shift back down)
	pb = ((y_scale) * (s32)SIN[angle])>>8;
	pc = ((x_scale) * (s32)-SIN[angle])>>8;
	pd = ((y_scale) * (s32)COS[angle])>>8;


	rotData[rotDataIndex].pa = pa;  //put them in my data struct
	rotData[rotDataIndex].pb = pb;
	rotData[rotDataIndex].pc = pc;
	rotData[rotDataIndex].pd = pd;
}

#endif
