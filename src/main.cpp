
#include "include_all.h"

int main()
{
        SetMode(MODE_4 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D);
	REG_BG2CNT=BG_MOSAIC_ENABLE;
	InitializeSprites(); //1280
	DMA_Copy(3,(void*)spritestrip1_Data,(void*)OAMData_bmp,1536,DMA_16NOW);

	
	while(1)
	{		
		WaitForVsync();
		if (GameMode==mode_opening) update_opening(); 
		if (GameMode==mode_gameboard) update_gameboard();
		if (GameMode==mode_madmath) update_madmath();
		if (GameMode==mode_question) update_question();
		if (GameMode==mode_avoidghosts) update_avoidghosts();
		if (GameMode==mode_liondoors) update_liondoors();
		if (GameMode==mode_jumper) update_jumper();
		if (GameMode==mode_fountain) update_fountain();
		if (GameMode==mode_lurgis) update_lurgis();
		if (GameMode==mode_win) update_win();
		if (GameMode==mode_gameover) update_gameover();
		CopyOAM();
	}
	
	return 0;
}


