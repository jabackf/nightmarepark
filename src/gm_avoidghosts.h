#ifndef AVOIDGHOSTS_H
#define AVOIDGHOSTS_H

#include "include_all.h"

#define hspeed 2

void ghosts_off(u16 c)
{
	u16 i;
	for (i=6; i<=6+c; i++) sprites[i].attribute1 = SIZE_8 | 264;
}

void update_avoidghosts(void)
{
	u16 x=120, y=140, counter=0, frame=0, ghost_count=10, i, ghost_speed=2, gtype, time=0, time_max=RAND(200)+900;
	if (skill==0) ghost_count=5;
	if (skill==1) ghost_count=12;
	if (skill==2) ghost_count=18;
	u16 ghost_y[25];
	u16 ghost_x[25];
	gtype=RAND(4);
	bool done=false, face_front=true, die=false;
	DMA_Copy(3,(void*)bg_questionPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	FillScreen(0x0101);
	mosaic_out(-1);
	if (gtype==0 || gtype==3) draw_text(8,34,44,"GANG OF GHOSTS");
	if (gtype==1) draw_text(8,35,44,"GANG OF SKULLS");
	if (gtype==2) draw_text(8,38,44,"FALLING STARS");
	draw_text(8,31,60,"AVOID THEM OR DIE");
	WaitTime(2,100);
	mosaic_in(-1);
	sprites[5].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | y;
	sprites[5].attribute1 = SIZE_16 | x;
	sprites[5].attribute2 = 544;
	
	for (i=6; i<=6+ghost_count; i++) 
	{ 
		ghost_y[i]=162;
		if (RAND(100)<=5) ghost_y[i]=0;
		ghost_x[i]=RAND(260-16);
		sprites[i].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | ghost_y[i];
		sprites[i].attribute1 = SIZE_8 | ghost_x[i];
		if (gtype==0) sprites[i].attribute2 = 584;
		if (gtype==1) sprites[i].attribute2 = 586;
		if (gtype==2) sprites[i].attribute2 = 588;
		if (gtype==3) sprites[i].attribute2 = 590;
	}
	
	CopyOAM();
	FillScreenRGB(10,10,10);
	mosaic_out(-1);
	FillScreen(0x0101);
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
			if (x>=hspeed) x-=hspeed;
			sprites[5].attribute1 = SIZE_16 | HORIZONTAL_FLIP | x;
			sprites[5].attribute2 = 512+frame;
			face_front=false;
		}
		if(!(*KEYS & KEY_RIGHT)) 
		{
			if (x<=(240-hspeed-16)) x+=hspeed;
			sprites[5].attribute1 = SIZE_16 | x;
			sprites[5].attribute2 = 512+frame;
			face_front=false;
		}
		if (face_front==true)  sprites[5].attribute2 = 544;
		face_front=true;
		
		time++;
		if (time>=time_max)
		{
			done=true;
			die=false;
		}
		
		for (i=6; i<=6+ghost_count; i++)
		{
			if (ghost_y[i]<=160) ghost_y[i]+=ghost_speed;
			else 
			{ 
				if (RAND(100)<=5) 
				{
					ghost_y[i]=0; 
					ghost_x[i]=RAND(260-16); 
					sprites[i].attribute1 = SIZE_8 | ghost_x[i]; 
				}
			}
			
			sprites[i].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | ghost_y[i];

			if ( (ghost_y[i]+8)>y+2 && ghost_y[i]<=158)
			{
				if ( (ghost_x[i]+8)>x && ghost_x[i]<(x+16) )
				{
					die=true;
					part_init(x+8, y, 1, 30, 580, 578, 70, 80, -10, 30, -20, 20, false);
					while (done==false)
					{
						done=part_update();
						CopyOAM();
						WaitForVsync();
					}
					part_kill();
				}
			}
		}

		CopyOAM();
		WaitForVsync();
	}
	
	ghosts_off(ghost_count);
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
