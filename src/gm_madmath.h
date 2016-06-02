#ifndef MADMATH_H
#define MADMATH_H

#include "include_all.h"

void update_madmath(void)
{
	u16 v1, v2, v3, v4, v5, res, mm_max=0, sel;
	s16 a1=0, a2=0, a3=0, a4=0, correct=-1;	
	if (skill==0) mm_max=5;
	if (skill==1) mm_max=10;
	if (skill==2) mm_max=50;
	v1=RAND(mm_max)+1;
	v2=RAND(mm_max)+1;
	v3=RAND(mm_max)+1;
	v4=RAND(mm_max)+1;
	v5=RAND(mm_max)+1;
	res=v1+v2+v3+v4+v5;
	
	a1=RAND(7)-3;
	if (a1==0) correct=0;
	
	a2=RAND(7)-3;
	while (a2==a1)
		a2=RAND(7)-3;
	if (a2==0) correct=1;
	
	a3=RAND(7)-3;
	while (a3==a2 || a3==a1)
		a3=RAND(7)-3;
	if (a3==0) correct=2;
	
	a4=RAND(7)-3;
	while (a4==a1 || a4==a2 || a4==a3)
		a4=RAND(7)-3;
	if (a4==0) correct=3;
		
	if (correct==-1) { a3=0; correct=2; }
	
	
	DMA_Copy(3,(void*)bg_madmathData, (void*)VideoBuffer,19200, DMA_16NOW);
	draw_text(8,28,75,"%d+%d+%d+%d+%d",v1,v2,v3,v4,v5);
	draw_text(8,1,152,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	draw_text(8,10,152,"YOU HAVE 8 SECONDS TO ANSWER");
	DMA_Copy(3,(void*)bg_madmathPalette,(void*)BGPaletteMem,256,DMA_16NOW);
	mosaic_out(-1);
	draw_text(8,32,95,"%d #%d #%d #%d\0",res+a1,res+a2,res+a3,res+a4);
	sel=make_menu(28,95,8,100,10,4,"","","");
	mosaic_in(-1);
	if (sel==correct)
		resume_gameboard();
	else
		GameMode=mode_gameover;
}	

#endif
