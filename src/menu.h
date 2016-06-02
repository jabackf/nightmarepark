#ifndef MENU_H
#define MENU_H

#include "include_all.h"

//If the optional timer is up, the funtion returns 90
u16 make_menu(u16 x, u16 y, s16 time, u16 timex, u16 timey, u16 arg_count, ...)
{
	u16 sel=0, counter=0, menu_count=0, i;
	bool u=false, d=false, b=false, done=false;
	const char* menu_list[16];
	va_list ap;
	
	if(!(*KEYS & KEY_A) || !(*KEYS & KEY_START)) b=true;
	
	if (arg_count>=15) return 0;
	
	va_start(ap,arg_count);
	for (i=0; i<arg_count;i++)
	{
		menu_count+=1;
		menu_list[i]=va_arg(ap,const char*);
	}
	va_end(ap);
	
	for (i=0; i<menu_count; i++)
		draw_text(8,x+4,y+(i*8),menu_list[i]);
	
	sprites[5].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | y;
	sprites[5].attribute1 = SIZE_8 | x*2;
	sprites[5].attribute2 = 582;
	CopyOAM();

	if (time!=-1) { draw_text(16,timex,timey,"~~~",time); draw_text(16,timex,timey,"%d",time); }
	
	while(done==false)
	{
		if(!(*KEYS & KEY_UP) )
		{
			if (u==false)
			{
				u=true;
				if (sel==0) sel=menu_count-1;
				else sel--;
				sprites[5].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | y+( sel*8 );
				CopyOAM();
			}
		}
		else u=false;
			
		if(!(*KEYS & KEY_DOWN) )
		{
			if (d==false)
			{
				d=true;
				if (sel==menu_count-1) sel=0;
				else sel++;
				sprites[5].attribute0 = COLOR_256 | MOSAIC | MODE_TRANSPARENT | SQUARE | y+( sel*8 );
				CopyOAM();
			}
		}
		else d=false;
		
		if(!(*KEYS & KEY_A) || !(*KEYS & KEY_START))
		{
			if (b==false)
			{
				b=true;
				done=true;
			}
		}
		else b=false;
		
		if (time!=-1)
		{
			counter++;
			if (counter==411)
			{
				if (time==0)
				{
					sel=90;
					done=true;
				}
				else
					time--;
				counter=0;
				draw_text(16,timex,timey,"~~~",time);
				draw_text(16,timex,timey,"%d",time);
			}
		}
		
		WaitForVsync();
	}
	
	sprites[5].attribute1=260;
	CopyOAM();
	DMA_Copy(3,(void*)SpritePalette,(void*)OBJPaletteMem,256,DMA_16NOW);
	return sel;
}

#endif
