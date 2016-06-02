#ifndef JUMPER_H
#define JUMPER_H

#include "include_all.h"

#define jumper_ground_y 1180
#define jumper_player_x 48
#define jumper_gravity 1
#define jumper_jumpspeed -30
#define jumper_rotspeed 7
#define jumper_cannon_speed 3
#define jumper_timer_max 80
#define jumper_timer_half 40

void update_jumper(void)
{
	u16 y=jumper_ground_y-128, angle=0, timer=0, time=0, cannon_1x=260, cannon_2x=260, cannon_1y=0, cannon_2y=0, last_cy=2, c=0;
	s16 vspeed=0;
	bool done=false, die=false;
	u16 cannon_y[]={135,110,86};
	
	DMA_Copy(3,(void*)bg_questionPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	FillScreen(0x0101);
	mosaic_out(-1);
	draw_text(8,12,44,"THE PIRATES ARE ATTACKING");
	draw_text(8,9,60,"JUMP THE CANNON BALLS OR DIE");
	WaitTime(3,200);
	mosaic_in(-1);
	sprites[5].attribute0 = COLOR_256 | MOSAIC | ROTATION_FLAG | MODE_TRANSPARENT | SIZE_DOUBLE | SQUARE | (y >> 3)-8;
	sprites[5].attribute1 = SIZE_16 | ROTDATA(5) | jumper_player_x-8;
	sprites[5].attribute2 = 520;
	cannon_1y=cannon_y[RAND(3)];
	sprites[6].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | cannon_1y;
	sprites[6].attribute1 = SIZE_8 | 260;
	sprites[6].attribute2 = 576;
	cannon_2y=cannon_y[RAND(3)];
	sprites[7].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | cannon_2y;
	sprites[7].attribute1 = SIZE_8 | 260;
	sprites[7].attribute2 = 576;
	
	RotateSprite(5,0,250,250);
	CopyOAM();
	FillScreenRGB(10,10,10);
	DMA_Copy(3,(void*)bg_jumperData, (void*)VideoBuffer,19200, DMA_16NOW);
	DMA_Copy(3,(void*)bg_jumperPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	mosaic_out(-1);
	
	while(done!=true)
	{
		if (y<=(jumper_ground_y-128)) { vspeed+=jumper_gravity; }
		else { y=jumper_ground_y-128; vspeed=0; }
		if (!(*KEYS & KEY_A))
		{
			if (y==(jumper_ground_y-128)) 
			{
				vspeed=jumper_jumpspeed;
				angle=360;
			}
		}
		
		if (angle!=0)
		{
			angle-=jumper_rotspeed;
			if (angle<=5) angle=0;
		}
		
		y+=vspeed;
		RotateSprite(5,angle,250,250);
		sprites[5].attribute0 = COLOR_256 | MOSAIC | ROTATION_FLAG | MODE_TRANSPARENT | SIZE_DOUBLE | SQUARE | (y >> 3)-8;
		if (angle==0) sprites[5].attribute2 = 520;
		else sprites[5].attribute2 = 512;
		
		timer++;
		if (timer==jumper_timer_half) 
		{
			last_cy=c;
			c=RAND(3);
			while (c==last_cy) c=RAND(3);
			cannon_1y=cannon_y[c];
			sprites[6].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | cannon_1y;
			cannon_1x=245;
		}
		if (timer==jumper_timer_max) 
		{
			last_cy=c;
			c=RAND(3);
			while (c==last_cy) c=RAND(3);
			cannon_2y=cannon_y[c];
			sprites[7].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | cannon_2y;
			cannon_2x=245;
			timer=0;
		}
		
		if (cannon_1x>jumper_cannon_speed && cannon_1x<250) cannon_1x-=jumper_cannon_speed;
		else cannon_1x=250;
		if (cannon_2x>jumper_cannon_speed && cannon_2x<250) cannon_2x-=jumper_cannon_speed;
		else cannon_2x=250;
		
		sprites[6].attribute1 = SIZE_8 | cannon_1x;
		sprites[7].attribute1 = SIZE_8 | cannon_2x;
		
		time++;
		if (time>=1000)
		{
			done=true;
			die=false;
		}
		
		if ( (cannon_1x+8)>=jumper_player_x && cannon_1x<=(jumper_player_x+16) )
		{
			if ( (cannon_1y+8)>(y>>3)  && cannon_1y<((y>>3)+16) )
			{
				die=true;
				sprites[5].attribute1=260;
				part_init( jumper_player_x+16, (y>>3)+8, 1, 10, 580, 578, 80, 80, -10, 30, -20, 20, false);
				while (done==false)
				{
					done=part_update();
					CopyOAM();
					WaitForVsync();
				}
				part_kill();
			}
		}
		if ( (cannon_2x+8)>=jumper_player_x && cannon_2x<=(jumper_player_x+16) )
		{
			if ( (cannon_2y+8)>(y>>3)  && cannon_2y<((y>>3)+16) )
			{
				die=true;
				part_init( jumper_player_x+16, (y>>3)+8, 1, 10, 580, 578, 80, 80, -10, 30, -20, 20, false);
				while (done==false)
				{
					done=part_update();
					CopyOAM();
					WaitForVsync();
				}
				part_kill();
			}
		}
		
		CopyOAM();
		WaitForVsync();
	}
	
	sprites[5].attribute1=260;
	sprites[6].attribute1=264;
	sprites[7].attribute1=262;
	CopyOAM();
	if (die==false)
	{
		mosaic_in(-1);
		resume_gameboard();
	}
	else  mosaic_in(mode_gameover);
}

#endif
