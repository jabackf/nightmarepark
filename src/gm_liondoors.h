#ifndef LIONDOORS_H
#define LIONDOORS_H

#include "include_all.h"

void liondoors_open_door(u16 dx, u16 data)
{
	//62x86 (43x41) y=48
	//data= 0 with 1 without
	u16 x, y, c;
	if (dx==0) dx=6;
	if (dx==1) dx=44;
	if (dx==2) dx=83;
	for (y=0; y<86; y++)
	{
		for (x=0; x<31; x++)
		{
			if (data==0) c=door_with_lionData[x+(y*31)];
			else c=door_without_lionData[x+(y*31)];
			VideoBuffer[x+dx+( (y+48)*120 )] = c;
		}
	}
}

void update_liondoors(void)
{
	u16 counter=0, x=32, frame=0, sel=0, new_sel=1, win=0;
	s16 move=0;
	bool a_down=true, done=false;
	
	DMA_Copy(3,(void*)bg_liondoorsData, (void*)VideoBuffer,19200, DMA_16NOW);
	DMA_Copy(3,(void*)bg_liondoorsPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	sprites[5].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | 138;
	sprites[5].attribute1 = SIZE_16 | x;
	sprites[5].attribute2 = 544;
	CopyOAM();
	mosaic_out(-1);
	
	while (done==false)
	{
		a_down=true;
		
		counter++;
		if (counter>=10)
		{
			if (frame==0) frame=8;
			else frame=0;
			counter=0;
		}
		
		if(!(*KEYS & KEY_LEFT) && move==0) 
		{
			if (sel!=0)
			{
				move=-3;
				new_sel=sel-1;
			}
			a_down=false;
		}
		if(!(*KEYS & KEY_RIGHT) && move==0) 
		{
			if (sel!=2)
			{
				move=3;
				new_sel=sel+1;
			}
			a_down=false;
		}
		
		if (move==0)  sprites[5].attribute2 = 544;
		else sprites[5].attribute2 = 512+frame;
		
		x+=move;
		if (move>=0) sprites[5].attribute1 = SIZE_16 | x;
		if (move<0) sprites[5].attribute1 = SIZE_16 | HORIZONTAL_FLIP | x;

		if ( (new_sel==0 && difference(x,32)<=3 ) || (new_sel==1 && difference(x,112)<=3 ) || (new_sel==2 && difference(x,192)<=3 ) )
		{
			move=0;
			sel=new_sel;
			new_sel=3;
		}
		
		if(!(*KEYS & KEY_A) && move==0 && a_down==true) 
		{
			if (RAND(3)!=sel) win=1;
			
			liondoors_open_door(sel,win);
			WaitTime(1,200);
			done=true;
		}
		
		WaitForVsync();
		CopyOAM();
	}
	
	sprites[5].attribute1=260;
	CopyOAM();
	
	if (win==0)
	{
		mosaic_in(-1);
		FillScreen(0x0101);
		DMA_Copy(3,(void*)bg_questionPalette,(void*)BGPaletteMem,256,DMA_16NOW);
		draw_text(8,38,44,"THE LION THANKS#YOU FOR HIS MEAL.");
		mosaic_out(-1);
		WaitTime(3,0);
		mosaic_in(mode_gameover);
	}
	else
	{
		mosaic_in(-1);
		resume_gameboard();
	}
}	

#endif
