
#ifndef TEXT_H
#define TEXT_H

#include "include_all.h"


//pass in a character, get the font bmp number
u16 font_number(char c)
{
	switch(c)
	{
		case 'A': return 0; break;
		case 'B': return 1; break;
		case 'C': return 2; break;
		case 'D': return 3; break;
		case 'E': return 4; break;
		case 'F': return 5; break;
		case 'G': return 6; break;
		case 'H': return 7; break;
		case 'I': return 8; break;
		case 'J': return 9; break;
		case 'K': return 10; break;
		case 'L': return 11; break;
		case 'M': return 12; break;
		case 'N': return 13; break;
		case 'O': return 14; break;
		case 'P': return 15; break;
		case 'Q': return 16; break;
		case 'R': return 17; break;
		case 'S': return 18; break;
		case 'T': return 19; break;
		case 'U': return 20; break;
		case 'V': return 21; break;
		case 'W': return 22; break;
		case 'X': return 23; break;
		case 'Y': return 24; break;
		case 'Z': return 25; break;
			
		case '0': return 26; break;
		case '1': return 27; break;
		case '2': return 28; break;
		case '3': return 29; break;
		case '4': return 30; break;
		case '5': return 31; break;
		case '6': return 32; break;
		case '7': return 33; break;
		case '8': return 34; break;
		case '9': return 35; break;
			
		case '+': return 36; break;
		case '-': return 37; break;
		case '?': return 38; break;
		case '.': return 39; break;
			
		case ' ': return 40; break;
		case '#': return 41; break; //NEW LINE
		case '~': return 42; break; //BLACK SPACE
			
		default: return 43;
	}
}

u16 draw_8char(u16 x, u16 y, u16 char_num)
{
	u16 h=0, v=0, sub=0, width=0, c=0;
	for (v=0; v<=7; v++)
	{
		width=0;
		for (h=0; h<=3; h++)
		{
			if (char_num!=42) c=font8Data[(h+(v*4))+(char_num*32)];
			else c=0x0101;
				
			if (c!=0x0505)
			{
				width+=1;
				VideoBuffer[x+h-sub+((y+v)*120)] = c;
			}
			else
				sub+=1;
		
		}
		sub=0;
	}
	return width;
}

u16 draw_16char(u16 x, u16 y, u16 char_num)
{
	u16 h=0, v=0, sub=0, width=0, c=0;
	for (v=0; v<=15; v++)
	{
		width=0;
		for (h=0; h<=7; h++)
		{
			if (char_num!=42) c=font16Data[(h+(v*8))+(char_num*128)];
			else c=0x0101;
				
			if (c!=0x0505)
			{
				width+=1;
				VideoBuffer[x+h-sub+((y+v)*120)] = c;
			}
			else
				sub+=1;
		
		}
		sub=0;
	}
	return width;
}

void draw_text(u16 font_size, u16 x, u16 y, const char *str, ...)
{
	u16 i, length, offx, offy;
	char char_num=0;
	offx=0;
	offy=0;
	
	char	text[500];
	va_list ap;
	va_start(ap, str);
	vsprintf(text, str, ap);
	va_end(ap);
	
	length=strlen(text);
	
	for (i=0; i<length; i++)
	{
		char_num=font_number(text[i]);
		
		if (char_num==40)
		{
			if (font_size==16) offx+=4;
			else offx+=2;
		}
		if (char_num==41)
		{ 
			offx=0;
			if (font_size==16) offy+=16;
			else offy+=8; 
		}
		
		if (char_num!=40 && char_num!=41 && char_num!=43)
		{
			if (font_size==16)
				offx+=draw_16char(offx+x,offy+y,char_num);
			if (font_size==8)
				offx+=draw_8char(offx+x,offy+y,char_num);
		}
	}
	DMA_Copy(3,(void*)SpritePalette,(void*)OBJPaletteMem,256,DMA_16NOW);
}

#endif
