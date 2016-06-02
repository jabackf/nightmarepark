#ifndef LURGIS_H
#define LURGIS_H

#include "include_all.h"

#define lurgis_count 100

void update_lurgis(void)
{
	u16 x=224, y=80, counter=0, frame=0, speed=0;
	bool done=false, die=false, lurgis_slow=false;
	
	if (skill==0) speed=2;
	if (skill==2 || skill==1) speed=1;
	
	DMA_Copy(3,(void*)bg_fountainPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	DMA_Copy(3,(void*)bg_fountainData, (void*)VideoBuffer,19200, DMA_16NOW);
	
	DMA_Copy(3,(void*)bg_questionPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	FillScreen(0x0101);
	mosaic_out(-1);
	draw_text(8,31,60,"BREEDING LURGIS#HURRY TO THE EXIT");
	WaitTime(2,100);
	mosaic_in(-1);
	
	int lurgis_x[lurgis_count];
	int lurgis_y[lurgis_count];
	int lurgis_time[lurgis_count];
	
	sprites[5].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | y;
	sprites[5].attribute1 = SIZE_16 | x;
	sprites[5].attribute2 = 544;
	
	for (int i=6; i<=lurgis_count+6; i+=1)
	{
		sprites[i].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | 100;
		sprites[i].attribute1 = SIZE_16 | 250;
		sprites[i].attribute2 = 600;
		lurgis_x[i-6]=250;
		lurgis_y[i-6]=100;
		lurgis_time[i-6]=RAND(1200)+10;
	}

	CopyOAM();
	DMA_Copy(3,(void*)bg_lurgisPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	DMA_Copy(3,(void*)bg_lurgisData, (void*)VideoBuffer,19200, DMA_16NOW);
	mosaic_out(-1);

	while(done!=true)
	{
		counter++;
		if (counter>=10)
		{
			if (frame==0) frame=8;
			else frame=0;
			counter=0;
		}
		
		if(!(*KEYS & KEY_LEFT)) 
		{
			if (x>=speed) x-=speed;
			sprites[5].attribute1 = SIZE_16 | HORIZONTAL_FLIP | x;
			sprites[5].attribute2 = 512+frame;
		}
		if(!(*KEYS & KEY_RIGHT)) 
		{
			if (x<=(240-speed-16)) x+=speed;
			sprites[5].attribute1 = SIZE_16 | x;
			sprites[5].attribute2 = 512+frame;
		}
		if(!(*KEYS & KEY_UP)) 
		{
			if (y>=speed) y-=speed;
			sprites[5].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | y;
			sprites[5].attribute2 = 528+frame;
		}
		if(!(*KEYS & KEY_DOWN)) 
		{
			if (y<=(160-speed-16)) y+=speed;
			sprites[5].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | y;
			sprites[5].attribute2 = 544+frame;
		}
		
		for (int i=6; i<=lurgis_count+6; i+=1)
		{
			if (lurgis_time[i-6]>0)
			{
				if (lurgis_slow==false) lurgis_time[i-6]-=1;
				if (lurgis_time[i-6]==0)
				{
					lurgis_x[i-6]=(RAND(13)+1)*16;
					lurgis_y[i-6]=RAND(11)*16;
					sprites[i].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | lurgis_y[i-6];
					sprites[i].attribute1 = SIZE_16 | lurgis_x[i-6];
				}
				lurgis_slow=!lurgis_slow;
			}
			else
			{
				if (x+15>lurgis_x[i-6] && x<lurgis_x[i-6]+15)
				{
					if (y+15>lurgis_y[i-6] && y<lurgis_y[i-6]+15)
					{
						die=true;
						done=true;
						WaitTime(1,0);
					}
				}
			}
		}
		
		if (x<=5)
		{
			done=true;
			die=false;
		}

		CopyOAM();
		WaitForVsync();
	}

	for (int i=6; i<=lurgis_count+6; i+=1) sprites[i].attribute1 = 260;
	sprites[5].attribute1=260;
	CopyOAM();
	if (die==false)
	{
		mosaic_in(-1);
		resume_gameboard();
	}
	else  mosaic_in(mode_gameover);
}

#endif
