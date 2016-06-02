#ifndef FOUNTAIN_H
#define FOUNTAIN_H

#include "include_all.h"

#define hspeed 2

void update_fountain(void)
{
	u16 x=120, y=140, counter=0, frame=0, part_counter=0, part_max_counter=5, part_time=0, part_num=30;
	bool done=false, face_front=true, die=false;
	
	DMA_Copy(3,(void*)bg_fountainPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	DMA_Copy(3,(void*)bg_fountainData, (void*)VideoBuffer,19200, DMA_16NOW);
	
	sprites[5].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | y;
	sprites[5].attribute1 = SIZE_16 | x;
	sprites[5].attribute2 = 544;
	
	if (skill==0) {part_num=12; part_max_counter=4;}
	if (skill==1) {part_num=18; part_max_counter=5;}
	if (skill==2) {part_num=25; part_max_counter=6;}
	
	part_init( 116, 66, 1, 6, 586, 584, part_num, 80, 20, 30, -20, 20, false);
	
	CopyOAM();
	
	mosaic_out(-1);

	while(done!=true)
	{
		if (part_time==0)
		{
			if (part_update()==true) 
			{
				part_time=1;
				part_counter++;
				if (part_counter==part_max_counter)
				{
					done=true;
					die=false;
					part_kill();
				}
			}
		}
		else
		{
			part_time++;
			if (part_time>=100)
			{
				part_init( 116, 66, 1, 6, 586, 584, part_num, 80, 20, 30, -20, 20, false);
				part_time=0;
			}
		}
		
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
		
		for (int i=0; i<part_num; i++)
		{
			if ( (particles[i].y>>3)+8>y && (particles[i].y>>3)<y+16 )
			{
				if ( (particles[i].x>>3)+8>x && (particles[i].x>>3)<x+16 )
				{
					part_init(x+8, y, 1, 6+part_num, 580, 578, 70, 80, -10, 30, -20, 20, false);
					while (done==false)
					{
						done=part_update();
						CopyOAM();
						WaitForVsync();
					}
					part_kill();
					CopyOAM();
					i=part_num;
					done=true;
					die=true;
				}
			}
		}
		CopyOAM();
		WaitForVsync();
	}

	for (int l=0; l<part_num; l++)
	{
		particles[l].x=1926;
		particles[l].y=6;
		particles[l].dead=true;
		particles[l].move=false;
		sprites[l+6].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | particles[l].y>>3;
		sprites[l+6].attribute1 = SIZE_8 | particles[l].x>>3;
	}
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
