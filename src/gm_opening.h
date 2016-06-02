
#ifndef GMOPENING_H
#define GMOPENING_H

#include "include_all.h"

u16 skill=0, quiz_on=0, math_on=0, luck_on=0;

void update_opening(void)
{
	InitializeSprites();
	CopyOAM();
	REG_MOSAIC = SetMosaic(0,0,0,0);
	
	bool done=false;
	DMA_Copy(3,(void*)bg_titlePalette,(void*)BGPaletteMem,256,DMA_16NOW);
	DMA_Copy(3,(void*)bg_titleData, (void*)VideoBuffer,19200, DMA_16NOW);
	while( (!(*KEYS & KEY_START)) || (!(*KEYS & KEY_A)) || (!(*KEYS & KEY_B))  || (!(*KEYS & KEY_SELECT)) ) {}
	while (done==false)
	{
		DMA_Copy(3,(void*)bg_titlePalette,(void*)BGPaletteMem,256,DMA_16NOW);
		DMA_Copy(3,(void*)bg_titleData, (void*)VideoBuffer,19200, DMA_16NOW);
		SeedRandom();
		if( (!(*KEYS & KEY_START)) || (!(*KEYS & KEY_A)) || (!(*KEYS & KEY_B))  || (!(*KEYS & KEY_SELECT)) ) 
			done=true;
	}

	mosaic_in(-1);
	FillScreenRGB(0,0,0);
	mosaic_out(-1);
	
	draw_text(8,24,44,"PICK A SKILL LEVEL");
	draw_text(8,35,148,"GAME SETTINGS");
	skill=make_menu(38,64,-1,0,0,3,"WIMP","AVERAGE","MANIAC");
	FillScreenRGB(0,0,0);
	draw_text(8,24,44,"ARE YOU FEELING LUCKY?");
	draw_text(8,35,148,"GAME SETTINGS");
	luck_on=make_menu(47,64,-1,0,0,2,"YES","NO");
	FillScreenRGB(0,0,0);
	draw_text(8,30,44,"DO YOU LIKE QUIZZES?");
	draw_text(8,35,148,"GAME SETTINGS");
	quiz_on=make_menu(47,64,-1,0,0,2,"YES","NO");
	FillScreenRGB(0,0,0);
	draw_text(8,48,44,"2+2?");
	draw_text(8,35,148,"GAME SETTINGS");
	math_on=make_menu(47,64,-1,0,0,2,"4","22");
	
	mosaic_in(-1);
	reset_gameboard();
	GameMode=mode_gameboard;
}

void update_gameover(void)
{
	if (key1_x!=250) gameboard_map[key1_y][key1_x]=1;
	if (key2_x!=250) gameboard_map[key2_y][key2_x]=1;
	gameboard_map[7][20]=0;
	gameboard_map[7][21]=0;
	DMA_Copy(3,(void*)bg_gameoverPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	DMA_Copy(3,(void*)bg_gameoverData, (void*)VideoBuffer,19200, DMA_16NOW);
	mosaic_out(-1);
	WaitInput();
	mosaic_in(mode_opening);
}

void update_win(void)
{
	if (key1_x!=250) gameboard_map[key1_y][key1_x]=1;
	if (key2_x!=250) gameboard_map[key2_y][key2_x]=1;
	gameboard_map[7][20]=0;
	gameboard_map[7][21]=0;
	DMA_Copy(3,(void*)bg_winPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	DMA_Copy(3,(void*)bg_winData, (void*)VideoBuffer,19200, DMA_16NOW);
	mosaic_out(-1);
	WaitInput();
	mosaic_in(mode_opening);
}

#endif
