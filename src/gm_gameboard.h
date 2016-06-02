#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "include_all.h"

//24 x 16 map, 10 x 10 tiles
//0=nothing, 1=walkway, 2=key1, 3=key2

u16 gameboard_map[16][24] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0},
	{0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0},
	{0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0},
	{0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,0},
	{0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0},
	{0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0},
	{0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	

extern u16 math_on, quiz_on, luck_on, skill;
		
const u16 key_randx[]={10,10, 7,13, 1,19, 1,19, 4,16};
const u16 key_randy[]={ 7,14, 7,  7, 3, 3,11,11,14,14};
u16 key1_x=0;
u16 key1_y=0;
u16 key2_x=0;
u16 key2_y=0;
u16 steps_to_minigame=4;

class c_gb_player
{
	public:
	u16 posx, posy, dir, frame, anim_timer, oam_data_start, steps;
	s16 move_cnty, move_cntx;
	bool abs_move;
	void update(void);
	void handle_input(void);
	
} gb_player;

void gb_moved_square(void)
{
	gb_player.steps-=1;
	DMA_Copy(3,(void*)bg_gameboardData, (void*)VideoBuffer,19200, DMA_16NOW);
	draw_text(16,1,140,"%d",gb_player.steps);
	DMA_Copy(3,(void*)bg_gameboardPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	
	if (gb_player.posx==22 && gb_player.posy==7)
	{
		sprites[0].attribute1 = 250;
		CopyOAM();
		mosaic_in(mode_win);
	}
	else
	{
		if (gb_player.steps==0)
		{
			bool done=false;
			u16 r;
			gb_player.steps=steps_to_minigame;
			SpritesOff(0,4);
			while (done==false)
			{
				done=true;
				r=RAND(minigame_count)+minigame_add;
				if (r==mode_madmath) 
				{ 
					if (math_on==1) done=false; 
					else 			done=true; 
				}
				if (r==mode_question) 
				{ 
					if (quiz_on==1) done=false; 
					else 			done=true; 
				}
				if (r==mode_liondoors) 
				{ 
					if (luck_on==1) done=false; 
					else 			done=true; 
				}
			}
			mosaic_in(r);
		}
	}
}

void c_gb_player::update(void)
{
	int px=0, py=0;

	handle_input();
	
	if  (abs_move==true)
	{
		anim_timer+=1;
		if (anim_timer>=15)
		{
			anim_timer=0;
			if (frame==0) frame=1;
			else		    frame=0;
		}
	}
	else
	{
		anim_timer=13;
		frame=1;
	}
	
	if (abs_move==true)
	{
		if (dir==0)
		{
			move_cntx+=1;
			px=((posx*10)-3)+move_cntx;
			py=((posy*10)-7);
			if (move_cntx>=10) { posx+=1; move_cntx=0; abs_move=false; gb_moved_square(); }
		}
		if (dir==1)
		{
			move_cnty-=1;
			py=((posy*10)-6)+move_cnty;
			px=((posx*10)-7);
			if (move_cnty<=-10) { posy-=1; move_cnty=0; abs_move=false; gb_moved_square(); }
		}
		if (dir==2)
		{
			move_cntx-=1;
			px=((posx*10)-3)+move_cntx;
			py=((posy*10)-7);
			if (move_cntx<=-10) { posx-=1; move_cntx=0; abs_move=false; gb_moved_square(); }
		}
		if (dir==3)
		{
			move_cnty+=1;
			py=((posy*10)-6)+move_cnty;
			px=((posx*10)-3);
			if (move_cnty>=10) { posy+=1; move_cnty=0; abs_move=false; gb_moved_square(); }
		}
	}
	else
	{
		px=((posx*10)-3);
		py=((posy*10)-7);
	}
	if (GameMode!=mode_gameboard) return;

	if (dir==0 || dir==2)
	{
		if (frame==0) oam_data_start=512;
		else		    oam_data_start=520;
	}
	if (dir==1)
	{
		if (frame==0) oam_data_start=528;
		else		    oam_data_start=536;
	}
	if (dir==3)
	{
		if (frame==0) oam_data_start=544;
		else		    oam_data_start=552;
	}
	
	sprites[0].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | py;
	if (dir==0) sprites[0].attribute1 = SIZE_16 | px;
	if (dir==2) sprites[0].attribute1 = SIZE_16 | HORIZONTAL_FLIP | px;
        sprites[0].attribute2 = oam_data_start;
}

void gb_grab_key(u16 key)
{
	if (key==1)
	{
		sprites[3].attribute1=250;
		sprites[1].attribute1=250;
		gameboard_map[key1_y][key1_x]=1;
		gameboard_map[7][20]=1;
		key1_x=250;
	}
	if (key==2)
	{
		sprites[4].attribute1=250;
		sprites[2].attribute1=250;
		gameboard_map[key2_y][key2_x]=1;
		gameboard_map[7][21]=1;
		key2_x=250;
	}
}

void c_gb_player::handle_input(void)
{
	if (abs_move==true) return;
		
	if(!(*KEYS & KEY_RIGHT)) 
	{
		dir=0;
		if (gameboard_map[posy][posx+1]!=0)
		{
			abs_move=true;
			move_cntx=0;
			move_cnty=0;
			if (gameboard_map[posy][posx+1]==2) gb_grab_key(1);
			if (gameboard_map[posy][posx+1]==3) gb_grab_key(2);
		}
	}
	if (abs_move==true) return;
	if(!(*KEYS & KEY_UP))
	{
		dir=1;
		if (gameboard_map[posy-1][posx]!=0)
		{
			abs_move=true;
			move_cnty=0;
			move_cntx=0;
			if (gameboard_map[posy-1][posx]==2) gb_grab_key(1);
			if (gameboard_map[posy-1][posx]==3) gb_grab_key(2);
		}
	}
	if (abs_move==true) return;
	if(!(*KEYS & KEY_LEFT))
	{
		dir=2;
		if (gameboard_map[posy][posx-1]!=0)
		{
			abs_move=true;
			move_cntx=0;
			move_cnty=0;
			if (gameboard_map[posy][posx-1]==2) gb_grab_key(1);
			if (gameboard_map[posy][posx-1]==3) gb_grab_key(2);
		}
	}
	if (abs_move==true) return;
	if(!(*KEYS & KEY_DOWN))
	{
		dir=3;
		if (gameboard_map[posy+1][posx]!=0)
		{
			abs_move=true;
			move_cnty=0;
			move_cntx=0;
			if (gameboard_map[posy+1][posx]==2) gb_grab_key(1);
			if (gameboard_map[posy+1][posx]==3) gb_grab_key(2);
		}
	}
}
	
void gameboard_sprite_init(void)
{
	sprites[1].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | 70;
	sprites[1].attribute1 = SIZE_16 | 200;
        sprites[1].attribute2 = 568;
	sprites[2].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | 70;
	sprites[2].attribute1 = SIZE_16 | 210;
        sprites[2].attribute2 = 568;
	sprites[3].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | (key1_y*10)-7;
	sprites[3].attribute1 = SIZE_16 | (key1_x*10)-3;
        sprites[3].attribute2 = 560;
	sprites[4].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | (key2_y*10)-7;
	sprites[4].attribute1 = SIZE_16 | (key2_x*10)-3;
        sprites[4].attribute2 = 560;
}
	
void reset_gameboard(void)
{
	if (skill==0) steps_to_minigame=6;
	if (skill==1||skill==2) steps_to_minigame=4;

	gb_player.posx=1;
	gb_player.posy=7;
	gb_player.dir=0;
	gb_player.frame=0;
	gb_player.anim_timer=0;
	gb_player.abs_move=false;
	gb_player.move_cnty=0;
	gb_player.move_cntx=0;
	gb_player.steps=steps_to_minigame;
	gb_player.oam_data_start=544;

	s32 ra=RAND(10); ra=RAND(10);
	key1_x=key_randx[ra];
	key1_y=key_randy[ra];
	gameboard_map[key1_y][key1_x]=2;

	s32 rb=RAND(10);
	while (rb==ra) rb=RAND(10);
	key2_x=key_randx[rb];
	key2_y=key_randy[rb];
	gameboard_map[key2_y][key2_x]=3;

	DMA_Copy(3,(void*)bg_gameboardData, (void*)VideoBuffer,19200, DMA_16NOW);
	draw_text(16,1,140,"%d",gb_player.steps);
	DMA_Copy(3,(void*)bg_gameboardData, (void*)VideoBuffer,19200, DMA_16NOW);
	draw_text(16,1,140,"%d",gb_player.steps);
	DMA_Copy(3,(void*)bg_gameboardPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	
	gameboard_sprite_init();
	mosaic_out(-1);
}

void resume_gameboard()
{
	DMA_Copy(3,(void*)bg_gameboardData, (void*)VideoBuffer,19200, DMA_16NOW);
	draw_text(16,1,140,"%d",gb_player.steps);
	DMA_Copy(3,(void*)bg_gameboardData, (void*)VideoBuffer,19200, DMA_16NOW);
	draw_text(16,1,140,"%d",gb_player.steps);
	DMA_Copy(3,(void*)bg_gameboardPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	
	SpritesOn(0,4);
	if (key1_x!=250)
	{
		sprites[3].attribute0 = COLOR_256 | MODE_TRANSPARENT | SQUARE | (key1_y*10)-7;
		sprites[3].attribute1 = SIZE_16 | (key1_x*10)-3;
		sprites[3].attribute2 = 560;
		sprites[1].attribute0 = COLOR_256 | MODE_TRANSPARENT | SQUARE | 70;
		sprites[1].attribute1 = SIZE_16 | 200;
		sprites[1].attribute2 = 568;
	}
	if (key2_x!=250)
	{
		sprites[4].attribute0 = COLOR_256 | MODE_TRANSPARENT | SQUARE | (key2_y*10)-7;
		sprites[4].attribute1 = SIZE_16 | (key2_x*10)-3;
		sprites[4].attribute2 = 560;
		sprites[2].attribute0 = COLOR_256 | MODE_TRANSPARENT | SQUARE | 70;
		sprites[2].attribute1 = SIZE_16 | 210;
		sprites[2].attribute2 = 568;
	}
	
	mosaic_out(mode_gameboard);
}
	
void update_gameboard(void)
{
	gb_player.update();
}

#endif
