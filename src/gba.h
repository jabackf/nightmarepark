//////////////////////////////////////////////////////////////////////////
// File: 	gba.h                                             	//
// Description: Contains all the GBA register definitions	 	//
// Author:	Eloist						  	//
// Date: 	9th January 2002                                      	//
//////////////////////////////////////////////////////////////////////////
#ifndef GBA_HEADER
#define GBA_HEADER

typedef unsigned char 	u8;
typedef unsigned short 	u16;
typedef unsigned long 	u32;

typedef signed char 	s8;
typedef signed short 	s16;
typedef signed long 	s32;

typedef unsigned char 	byte;
typedef unsigned short 	hword;
typedef unsigned long 	word;

#define FIXED s32
#define PI 3.14159

u32* OAMmem  		=(u32*)0x7000000;
u16* VideoBuffer 	=(u16*)0x6000000;
u16* OAMData		=(u16*)0x6010000;
u16* OAMData_bmp	=(u16*)0x06014000;
u16* BGPaletteMem 	=(u16*)0x5000000;
u16* OBJPaletteMem 	=(u16*)0x5000200;

/////////////////Bits////////////////
#define BIT00 1
#define BIT01 2
#define BIT02 4
#define BIT03 8
#define BIT04 16
#define BIT05 32
#define BIT06 64
#define BIT07 128
#define BIT08 256
#define BIT09 512
#define BIT10 1024
#define BIT11 2048
#define BIT12 4096
#define BIT13 8192
#define BIT14 16384
#define BIT15 32768

//Input Definitions
#define KEY_A 1
#define KEY_B 2
#define KEY_SELECT 4
#define KEY_START 8
#define KEY_RIGHT 16
#define KEY_LEFT 32
#define KEY_UP 64
#define KEY_DOWN 128
#define KEY_R 256
#define KEY_L 512
int* KEYS = (int*)0x04000130;

//Background control

#define BG_MOSAIC_ENABLE		0x40

//Mosaic

#define MOS_BG_HOR(n) (n)
#define MOS_BG_VER(n) (n<<4)
#define MOS_OBJ_HOR(n) (n<<8)
#define MOS_OBJ_VER(n) (n<<12)

#define SetMosaic(bh,bv,oh,ov) ((bh)+(bv<<4)+(oh<<8)+(ov<<12))

/////////////////Registers/////////////////		
#define REG_INTERUPT   *(u32*)0x3007FFC		//Interrupt Register
#define REG_DISPCNT    *(u32*)0x4000000		//Display Control (Mode)
#define REG_DISPCNT_L  *(u16*)0x4000000		//???
#define REG_DISPCNT_H  *(u16*)0x4000002		//???
#define REG_DISPSTAT   *(u16*)0x4000004		//???
#define REG_VCOUNT     *(u16*)0x4000006		//Vertical Control (Sync)
#define REG_BG0CNT     *(u16*)0x4000008		//Background 0
#define REG_BG1CNT     *(u16*)0x400000A		//Background 1
#define REG_BG2CNT     *(u16*)0x400000C		//Background 2
#define REG_BG3CNT     *(u16*)0x400000E		//Background 3
#define REG_BG0HOFS    *(u16*)0x4000010		//Background 0 Horizontal Offset
#define REG_BG0VOFS    *(u16*)0x4000012		//Background 0 Vertical Offset
#define REG_BG1HOFS    *(u16*)0x4000014		//Background 1 Horizontal Offset
#define REG_BG1VOFS    *(u16*)0x4000016		//Background 1 Vertical Offset
#define REG_BG2HOFS    *(u16*)0x4000018		//Background 2 Horizontal Offset
#define REG_BG2VOFS    *(u16*)0x400001A		//Background 2 Vertical Offset
#define REG_BG3HOFS    *(u16*)0x400001C		//Background 3 Horizontal Offset
#define REG_BG3VOFS    *(u16*)0x400001E		//Background 3 Vertical Offset
#define REG_BG2PA      *(u16*)0x4000020		//Background 2 PA Rotation (pa = x_scale * cos(angle);)
#define REG_BG2PB      *(u16*)0x4000022		//Background 2 PB Rotation (pb = y_scale * sin(angle);)
#define REG_BG2PC      *(u16*)0x4000024		//Background 2 PC Rotation (pc = x_scale * -sin(angle);)
#define REG_BG2PD      *(u16*)0x4000026		//Background 2 PD Rotation (pd = y_scale * cos(angle);)
#define REG_BG2X       *(u32*)0x4000028		//Background 2 X Location
#define REG_BG2X_L     *(u16*)0x4000028		//???
#define REG_BG2X_H     *(u16*)0x400002A		//???
#define REG_BG2Y       *(u32*)0x400002C		//Background 2 Y Location
#define REG_BG2Y_L     *(u16*)0x400002C		//???
#define REG_BG2Y_H     *(u16*)0x400002E		//???
#define REG_BG3PA      *(u16*)0x4000030		//Background 3 PA Rotation (pa = x_scale * cos(angle);)
#define REG_BG3PB      *(u16*)0x4000032		//Background 3 PB Rotation (pb = y_scale * sin(angle);)
#define REG_BG3PC      *(u16*)0x4000034		//Background 3 PC Rotation (pc = x_scale * -sin(angle);)
#define REG_BG3PD      *(u16*)0x4000036		//Background 3 PD Rotation (pd = y_scale * cos(angle);)
#define REG_BG3X       *(u32*)0x4000038		//Background 3 X Location
#define REG_BG3X_L     *(u16*)0x4000038		//???
#define REG_BG3X_H     *(u16*)0x400003A		//???
#define REG_BG3Y       *(u32*)0x400003C		//Background 3 Y Location
#define REG_BG3Y_L     *(u16*)0x400003C		//???
#define REG_BG3Y_H     *(u16*)0x400003E		//???
#define REG_WIN0H      *(u16*)0x4000040		//Window 0 X coords (bits 0-7 right, bits 8-16 left)
#define REG_WIN1H      *(u16*)0x4000042		//Window 1 X coords (bits 0-7 right, bits 8-16 left)
#define REG_WIN0V      *(u16*)0x4000044		//Window 0 Y coords (bits 0-7 bottom, bits 8-16 top)
#define REG_WIN1V      *(u16*)0x4000046		//Window 1 Y coords (bits 0-7 bottom, bits 8-16 top)
#define REG_WININ      *(u16*)0x4000048		//Inside Window Settings
#define REG_WINOUT     *(u16*)0x400004A		//Outside Window Settings
#define REG_MOSAIC     *(u32*)0x400004C		//Mosaic Mode
#define REG_MOSAIC_L   *(u32*)0x400004C		//???
#define REG_MOSAIC_H   *(u32*)0x400004E		//???
#define REG_BLDMOD     *(u16*)0x4000050		//Blend Mode
#define REG_COLEV      *(u16*)0x4000052		//???
#define REG_COLEY      *(u16*)0x4000054		//???
#define REG_SG10       *(u32*)0x4000060		//???
#define REG_SG10_L     *(u16*)0x4000060		//???
#define REG_SG10_H     *(u16*)0x4000062		//???
#define REG_SG11       *(u16*)0x4000064		//???
#define REG_SG20       *(u16*)0x4000068		//???
#define REG_SG21       *(u16*)0x400006C		//???
#define REG_SG30       *(u32*)0x4000070		//???
#define REG_SG30_L     *(u16*)0x4000070		//???
#define REG_SG30_H     *(u16*)0x4000072		//???
#define REG_SG31       *(u16*)0x4000074		//???
#define REG_SG40       *(u16*)0x4000078		//???
#define REG_SG41       *(u16*)0x400007C		//???
#define REG_SGCNT0     *(u32*)0x4000080		//???
#define REG_SGCNT0_L   *(u16*)0x4000080		//???
#define REG_SGCNT0_H   *(u16*)0x4000082		//???
#define REG_SGCNT1     *(u16*)0x4000084		//???
#define REG_SGBIAS     *(u16*)0x4000088		//???
#define REG_SGWR0      *(u32*)0x4000090		//???
#define REG_SGWR0_L    *(u16*)0x4000090		//???
#define REG_SGWR0_H    *(u16*)0x4000092		//???
#define REG_SGWR1      *(u32*)0x4000094		//???
#define REG_SGWR1_L    *(u16*)0x4000094		//???
#define REG_SGWR1_H    *(u16*)0x4000096		//???
#define REG_SGWR2      *(u32*)0x4000098		//???
#define REG_SGWR2_L    *(u16*)0x4000098		//???
#define REG_SGWR2_H    *(u16*)0x400009A		//???
#define REG_SGWR3      *(u32*)0x400009C		//???
#define REG_SGWR3_L    *(u16*)0x400009C		//???
#define REG_SGWR3_H    *(u16*)0x400009E		//???
#define REG_SGFIF0A    *(u32*)0x40000A0		//???
#define REG_SGFIFOA_L  *(u16*)0x40000A0		//???
#define REG_SGFIFOA_H  *(u16*)0x40000A2		//???
#define REG_SGFIFOB    *(u32*)0x40000A4		//???
#define REG_SGFIFOB_L  *(u16*)0x40000A4		//???
#define REG_SGFIFOB_H  *(u16*)0x40000A6		//???
#define REG_DMA0SAD     *(u32*)0x40000B0	//DMA0 Source Address
#define REG_DMA0SAD_L   *(u16*)0x40000B0	//DMA0 Source Address Low Value
#define REG_DMA0SAD_H   *(u16*)0x40000B2	//DMA0 Source Address High Value
#define REG_DMA0DAD     *(u32*)0x40000B4	//DMA0 Destination Address
#define REG_DMA0DAD_L   *(u16*)0x40000B4	//DMA0 Destination Address Low Value
#define REG_DMA0DAD_H   *(u16*)0x40000B6	//DMA0 Destination Address High Value
#define REG_DMA0CNT     *(u32*)0x40000B8	//DMA0 Control (Amount)
#define REG_DMA0CNT_L   *(u16*)0x40000B8	//DMA0 Control Low Value
#define REG_DMA0CNT_H   *(u16*)0x40000BA	//DMA0 Control High Value
#define REG_DMA1SAD     *(u32*)0x40000BC	//DMA1 Source Address
#define REG_DMA1SAD_L   *(u16*)0x40000BC	//DMA1 Source Address Low Value
#define REG_DMA1SAD_H   *(u16*)0x40000BE	//DMA1 Source Address High Value
#define REG_DMA1DAD     *(u32*)0x40000C0	//DMA1 Desination Address
#define REG_DMA1DAD_L   *(u16*)0x40000C0	//DMA1 Destination Address Low Value
#define REG_DMA1DAD_H   *(u16*)0x40000C2	//DMA1 Destination Address High Value
#define REG_DMA1CNT     *(u32*)0x40000C4	//DMA1 Control (Amount)
#define REG_DMA1CNT_L   *(u16*)0x40000C4	//DMA1 Control Low Value
#define REG_DMA1CNT_H   *(u16*)0x40000C6	//DMA1 Control High Value
#define REG_DMA2SAD     *(u32*)0x40000C8	//DMA2 Source Address
#define REG_DMA2SAD_L   *(u16*)0x40000C8	//DMA2 Source Address Low Value
#define REG_DMA2SAD_H   *(u16*)0x40000CA	//DMA2 Source Address High Value
#define REG_DMA2DAD     *(u32*)0x40000CC	//DMA2 Destination Address
#define REG_DMA2DAD_L   *(u16*)0x40000CC	//DMA2 Destination Address Low Value
#define REG_DMA2DAD_H   *(u16*)0x40000CE	//DMA2 Destination Address High Value
#define REG_DMA2CNT     *(u32*)0x40000D0	//DMA2 Control (Amount)
#define REG_DMA2CNT_L   *(u16*)0x40000D0	//DMA2 Control Low Value
#define REG_DMA2CNT_H   *(u16*)0x40000D2	//DMA2 Control High Value
#define REG_DMA3SAD     *(u32*)0x40000D4	//DMA3 Source Address
#define REG_DMA3SAD_L   *(u16*)0x40000D4	//DMA3 Source Address Low Value
#define REG_DMA3SAD_H   *(u16*)0x40000D6	//DMA3 Source Address High Value
#define REG_DMA3DAD     *(u32*)0x40000D8	//DMA3 Destination Address
#define REG_DMA3DAD_L   *(u16*)0x40000D8	//DMA3 Destination Address Low Value
#define REG_DMA3DAD_H   *(u16*)0x40000DA	//DMA3 Destination Address High Value
#define REG_DMA3CNT     *(u32*)0x40000DC	//DMA3 Control (Amount)
#define REG_DMA3CNT_L   *(u16*)0x40000DC	//DMA3 Control Low Value
#define REG_DMA3CNT_H   *(u16*)0x40000DE	//DMA3 Control High Value
#define REG_TM0D       *(u16*)0x4000100		//Timer 1?
#define REG_TM0CNT     *(u16*)0x4000102		//Timer 1 Control
#define REG_TM1D       *(u16*)0x4000104		//Timer 2?
#define REG_TM1CNT     *(u16*)0x4000106		//Timer 2 Control
#define REG_TM2D       *(u16*)0x4000108		//Timer 3?
#define REG_TM2CNT     *(u16*)0x400010A		//Timer 3 Control
#define REG_TM3D       *(u16*)0x400010C		//Timer 4?
#define REG_TM3CNT     *(u16*)0x400010E		//Timer 4 Control
#define REG_SCD0       *(u16*)0x4000120		//32-bit Normal Serial Communication Data 0 / Multi-play
#define REG_SCD1       *(u16*)0x4000122		//32-bit Normal Serial Communication Data 1 /Multi-play
#define REG_SCD2       *(u16*)0x4000124		//Multi-play Communication Data 2
#define REG_SCD3       *(u16*)0x4000126		//Multi-play Communication Data 3
#define REG_SCCNT      *(u32*)0x4000128		//???
#define REG_SCCNT_L    *(u16*)0x4000128		//???
#define REG_SCCNT_H    *(u16*)0x400012A		//???
#define REG_P1         *(u16*)0x4000130		//Player 1 Input
#define REG_P1CNT      *(u16*)0x4000132		//Player 1 Input Interrupt Status
#define REG_R          *(u16*)0x4000134		//???
#define REG_HS_CTRL    *(u16*)0x4000140		//???
#define REG_JOYRE      *(u32*)0x4000150		//???
#define REG_JOYRE_L    *(u16*)0x4000150		//???
#define REG_JOYRE_H    *(u16*)0x4000152		//???
#define REG_JOYTR      *(u32*)0x4000154		//???
#define REG_JOYTR_L    *(u16*)0x4000154		//???
#define REG_JOYTR_H    *(u16*)0x4000156		//???
#define REG_JSTAT      *(u32*)0x4000158		//???
#define REG_JSTAT_L    *(u16*)0x4000158		//???
#define REG_JSTAT_H    *(u16*)0x400015A		//???
#define REG_IE         *(u16*)0x4000200		//Master Interrupt Enable
#define REG_IF         *(u16*)0x4000202		//Interrupt Flags
#define REG_WSCNT      *(u16*)0x4000204		//???
#define REG_IME        *(u16*)0x4000208		//Interrupt Master Enable
#define REG_PAUSE      *(u16*)0x4000300		//Pause

//wait for the screen to stop drawing
#define WaitForVsync() while(REG_VCOUNT != 160);

void WaitInput(void)
{
	bool done=false;
	while (done==false)
	{
		if( (!(*KEYS & KEY_START)) || (!(*KEYS & KEY_A)) || (!(*KEYS & KEY_B))  || (!(*KEYS & KEY_SELECT)) ) 
			done=true;
	}
}

#define mode_opening 0
#define mode_gameboard 1
#define mode_gameover 2
#define mode_madmath 3
#define mode_question 4
#define mode_avoidghosts 5
#define mode_liondoors 6
#define mode_jumper 7
#define mode_fountain 8
#define mode_lurgis 9
#define mode_win 10

#define minigame_count 7
#define minigame_add 3

u16 GameMode=mode_opening;

#endif
