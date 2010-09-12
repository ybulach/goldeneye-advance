#ifndef COMMON_H
#define COMMON_H

////////////////
// Inclusions //
////////////////
#include <stdlib.h>
#include <string.h>

//#include <AAS.h>
//#include <AAS_Mixer.h>

#include "../Main.h"
#include "../Intro/Intro.h"
#include "../Jeu/Jeu.h"
#include "../Menu/Menu.h"

///////////
// Types //
///////////
typedef void (*IntrFunction)(void*);

// Types non signés
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Types signés
typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

// La structure d'une entité OAM
typedef struct
{
	u16 attribute0;
	u16 attribute1;
	u16 attribute2;
	u16 attribute3;
} OAMEntry;

////////////
// Macros //
////////////
// DMA
#define REG_DMA0CNT_H	*(volatile u16*) 0x40000BA
#define REG_DMA1CNT_H	*(volatile u16*) 0x40000C6
#define REG_DMA2CNT_H	*(volatile u16*) 0x40000D2
#define REG_DMA3CNT_H	*(volatile u16*) 0x40000DE
#define REG_DMA3SAD		*(volatile u32*) 0x40000D4
#define REG_DMA3DAD		*(volatile u32*) 0x40000D8
#define REG_DMA3CNT_L	*(volatile u16*) 0x40000DC
#define DMA_SRC_FIXED	0x0100
#define DMA_ENABLE		0x8000
#define DMA_16			0x0000
#define DMA_32			0x0400
#define DMA_16NOW		(DMA_ENABLE | DMA_16)
#define DMA_32NOW		(DMA_ENABLE | DMA_32)

// Ecran
#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	160

#define BACKBUFFER			0x10
#define videoFrontBuffer	(u16*) 0x6000000
#define videoBackBuffer		(u16*) 0x600A000

#define FORCE_BLANK	0x80

#define BG0_ENABLE	0x100
#define BG1_ENABLE	0x200
#define BG2_ENABLE	0x400
#define BG3_ENABLE	0x800

#define MODE_0	0x0
#define MODE_1	0x1
#define MODE_2	0x2
#define MODE_3	0x3
#define MODE_4	0x4
#define MODE_5	0x5

#define BG_MOSAIC_ENABLE      0x40

#define SetMosaic(bh, bv, oh, ov)	(bh + (bv << 4) + (oh << 8) + (ov << 12))

#define BG_COLORS_16	0x0
#define BG_COLORS_256	0x80

#define REG_MOSAIC	*(u32*) 0x400004C
#define REG_BLDMOD	*(u16*) 0x4000050
#define REG_BLD_AB	*(u16*) 0x4000052
#define REG_BLD_FAD	*(u16*) 0x4000054
#define BLEND_BG0	0x01
#define BLEND_BG1	0x02
#define BLEND_BG2	0x04
#define BLEND_BG3	0x08
#define BLEND_OBJ	0x10
#define BLEND_BD	0x20
#define BLEND_NO	0x00
#define BLEND_ALPHA	0x40
#define BLEND_WHITE	0x80
#define BLEND_BLACK	0xC0

#define REG_DISPCNT		*(volatile u32*) 0x4000000
#define REG_DISPSTAT	*(volatile u16*) 0x4000004
#define REG_DISPVCNT	*(volatile u16*) 0x4000006

#define REG_BG0CNT	*(volatile u16*) 0x4000008
#define REG_BG1CNT	*(volatile u16*) 0x400000A
#define REG_BG2CNT	*(volatile u16*) 0x400000C
#define REG_BG3CNT	*(volatile u16*) 0x400000E

#define TXTBG_SIZE_256x256	0x0
#define TXTBG_SIZE_512x256	0x4000
#define TXTBG_SIZE_256x512	0x8000
#define TXTBG_SIZE_512x512	0xC000

#define ROTBG_SIZE_128x128		0x0
#define ROTBG_SIZE_256x256		0x4000
#define ROTBG_SIZE_512x512		0x8000
#define ROTBG_SIZE_1024x1024	0xc000

#define REG_BG0HOFS	*(volatile u16*) 0x4000010
#define REG_BG0VOFS	*(volatile u16*) 0x4000012
#define REG_BG1HOFS	*(volatile u16*) 0x4000014
#define REG_BG1VOFS	*(volatile u16*) 0x4000016
#define REG_BG2HOFS	*(volatile u16*) 0x4000018
#define REG_BG2VOFS	*(volatile u16*) 0x400001A
#define REG_BG3HOFS	*(volatile u16*) 0x400001C
#define REG_BG3VOFS	*(volatile u16*) 0x400001E

#define REG_BG2PA	*(volatile u16*) 0x4000020
#define REG_BG2PB	*(volatile u16*) 0x4000022
#define REG_BG2PC	*(volatile u16*) 0x4000024
#define REG_BG2PD	*(volatile u16*) 0x4000026
#define REG_BG2X	*(volatile u32*) 0x4000028
#define REG_BG2Y	*(volatile u32*) 0x400002C

#define REG_BG3PA	*(volatile u16*) 0x4000030
#define REG_BG3PB	*(volatile u16*) 0x4000032
#define REG_BG3PC	*(volatile u16*) 0x4000034
#define REG_BG3PD	*(volatile u16*) 0x4000036
#define REG_BG3X	*(volatile u32*) 0x4000038
#define REG_BG3Y	*(volatile u32*) 0x400003C

#define REG_WIN0H	*(volatile u16*) 0x4000040
#define REG_WIN1H	*(volatile u16*) 0x4000042
#define REG_WIN0V	*(volatile u16*) 0x4000044
#define REG_WIN1V	*(volatile u16*) 0x4000046
#define REG_WININ	*(volatile u16*) 0x4000048
#define REG_WINOUT	*(volatile u16*) 0x400004A
#define WIN0_ENABLE	0x2000
#define WIN1_ENABLE	0x4000

#define CHAR_BASE_BLOCK(n)		(0x6000000 | ((n)*0x4000))
#define SCREEN_BASE_BLOCK(n)	(0x6000000 | ((n)*0x800))
#define CHAR_SHIFT				2
#define SCREEN_SHIFT			8

#define RGB(r,g,b)	(r | (g << 5) | (b << 10))

#define XM4	240
#define YM4	160
#define XO4	(XM4 / 2)
#define YO4	(YM4 / 2)

#define XM5	160
#define YM5	128
#define XO5	(XM5 / 2)
#define YO5	(YM5 / 2)

// Sprites
#define MAX_SPRITES	128

#define OBJ_ENABLE		0x1000
#define OBJ_WIN_ENABLE	0x8000
#define OBJ_MAP_1D		0x40
#define OBJ_MAP_2D		0x00

#define ROTATION_FLAG         0x100
#define SIZE_DOUBLE           0x200
#define MODE_NORMAL           0x0
#define MODE_ALPHA            0x400
#define MODE_WINDOWED         0x800
#define MOSAIC                0x1000
#define COLOR_16              0x0000
#define COLOR_256             0x2000
#define SQUARE                0x0
#define WIDE                  0x4000
#define TALL                  0x8000

#define ROTDATA(n)            (n << 9)
#define HORIZONTAL_FLIP       0x1000
#define VERTICAL_FLIP         0x2000
#define SIZE_8                0x0
#define SIZE_16               0x4000
#define SIZE_32               0x8000
#define SIZE_64               0xC000

// Memoire
#define MULTIBOOT	volatile const short __gba_multiboot = 1;

#define EWRAM	(volatile u8*) 0x02000000	// 256Ko
#define IWRAM	(volatile u8*) 0x03000000	// 32Ko (rapide)
#define IORAM	(volatile u8*) 0x04000000	// 1Ko
#define PALRAM	(volatile u16*) 0x05000000	// 0x200 mots
#define VRAM	(volatile u16*) 0x06000000	// 0xC000 mots
#define OAM		(volatile u16*) 0x07000000	//
#define ROM		(volatile u8*) 0x08000000	// 32Mo
#define SRAM	(volatile u8*) 0x0E000000	// 64Ko

#define DATA_IN_EWRAM	__attribute__ ((section(".ewram")))
#define DATA_IN_IWRAM	__attribute__ ((section(".iwram")))
#define CODE_IN_IWRAM	__attribute__ ((section(".iwram"), long_call))

// Math
#define FIXED_POINT_SHIFT	8 // Doit etre a 8 (valeur interne a la GBA)
#define FIXED_POINT			(1 << FIXED_POINT_SHIFT)

#define SINNB_SHIFT	8
#define SINNB		(1 << SINNB_SHIFT)
#define PI			3.14159265359
//#define SIN(a)		SINE_TABLE[(a) & (SINNB - 1)]
//#define COS(a)		SINE_TABLE[((a) + (SINNB/4)) & (SINNB - 1)]
#define SQRT2		1.41421356237

#define INVNB					(4 * FIXED_POINT)
#define INV(n)					((n)>0?INVERSE_TABLE[(n)]:-INVERSE_TABLE[-(n)])
#define FIXED_POINT_INV_SHIFT	15
#define FIXED_POINT_INV			(1 << FIXED_POINT_INV_SHIFT)

// Touches
#define REG_KEYS	*(volatile u16*) 0x4000130
#define KEY_A		1
#define KEY_B		2
#define KEY_SELECT	4
#define KEY_START	8
#define KEY_RIGHT	16
#define KEY_LEFT	32
#define KEY_UP		64
#define KEY_DOWN	128
#define KEY_R		256
#define KEY_L		512

// Interruptions
#define REG_IE			*(u16*) 0x4000200
#define REG_IF			*(u16*) 0x4000202
#define REG_WSCNT		*(u16*) 0x4000204
#define REG_IME			*(u16*) 0x4000208
#define REG_INTERUPT	*(u32*) 0x3007FFC

#define IT_VBLANK	0x1
#define IT_HBLANK	0x2
#define IT_YTRIG	0x4
#define IT_TIMER0	0x8
#define IT_TIMER1	0x10
#define IT_TIMER2	0x20
#define IT_TIMER3	0x40
#define IT_COMMS	0x80
#define IT_DMA0		0x100
#define IT_DMA1		0x200
#define IT_DMA2		0x400
#define IT_DMA3		0x800
#define IT_KEYPAD	0x1000
#define IT_CART		0x2000

#define E_VBLANK	0x8
#define E_HBLANK	0x10
#define E_YTRIG		0x20
#define YTRIG_VAL	0xFF00

#define BEST_WSCNT	0x4317

// Timers
#define REG_TM0D	*(volatile u16*) 0x4000100
#define REG_TM0CNT	*(volatile u16*) 0x4000102
#define REG_TM1D	*(volatile u16*) 0x4000104
#define REG_TM1CNT	*(volatile u16*) 0x4000106
#define REG_TM2D	*(volatile u16*) 0x4000108
#define REG_TM2CNT	*(volatile u16*) 0x400010A
#define REG_TM3D	*(volatile u16*) 0x400010C
#define REG_TM3CNT	*(volatile u16*) 0x400010E

#define FREQUENCY_0      0
#define FREQUENCY_64     1
#define FREQUENCY_256    2
#define FREQUENCY_1024   3

#define TIMER_CASCADE    4
#define TIMER_ENABLE     128

///////////////
// Variables //
///////////////
volatile unsigned short compteVBL;

// Ecran
extern u16* videoBuffer;
extern u16* palette;

// Sprites
extern OAMEntry OAMBuffer[MAX_SPRITES];
extern u16* OAMData;
extern u16* spritePalette;

///////////////
// Fonctions //
///////////////
// Changement de buffer (double buffering)
extern void commonFlipBuffers();

// Attente de la fin du balayage de l'écran
extern void commonWaitVSync();

// Attente de l'appuie sur une touche
extern void commonWaitKey(int key);

// Copie des sprites dans la mémoire OAM
extern void commonCopyOAMBuffer();

// Copie de données avec la DMA
extern void commonDMACopy(void* source, void* dest, u16 size, u16 type);

// Attente d'un certain temps
extern void commonWaitTime(int seconds, int milliSeconds);

// Effet de fondu de la palette vers le noir
extern void commonFadeOut();

// Effet de fondu du noir vers la palette
extern void commonFadeIn(const u16 picture[], const u16 pictpal[]);

// Effet de mosaic "Out"
extern void commonMosaicOut();

// Effet de mosaic "In"
extern void commonMosaicIn();

// Initialisation des sprites
extern void commonInitSprites();

// Remise à zéro des sprites
extern void commonResetSprites();

// Remise à zéro d'un seul sprite
extern void commonResetSprite(u8 sprite);

// Affiche du texte avec des sprites
extern u16 commonWriteString(u16 pointer, u16 x, u16 y, const char* string);

// Affiche une image en mode 4
extern void commonDisplayPicture(const u16 picture[], const u16 pictpal[]);

// Enregistrement dans la SRAM
extern void commonSRAMSaveByte(u16 offset, u8 value);
extern void commonSRAMSaveInt(u16 offset, int value);
extern void commonSRAMSaveString(u16 offset, char* value);

// Lecture depuis la SRAM
extern u8 commonSRAMLoadByte(u16 offset);
extern int commonSRAMLoadInt(u16 offset);
extern char* commonSRAMLoadString(u16 offset, int size);

// Fonction des interruptions
extern s16 commonSetInterrupt(u16 interruption,IntrFunction* fonction);
extern void commonSetYtrigInterrupt(u8 ligne,IntrFunction* fonction);
extern inline s16 commonEnableInterrupt(u16 interruption);
extern void commonDisableInterrupt(u16 interruption);
extern void commonBasicVblInterrupt(void);

// Converti un 'int' en 'char*' (valeur max: 99 / valeur mini: 0)
extern void commonIntToString(int value, char* string);

// Change la position d'un sprite
extern void commonSpriteChangePos(int s, int x, int y);

// Change le gfx d'un sprite
extern void commonSpriteChangeGfx(int s, int gfx, int priority);

// Renversement horizontal et vertical d'un sprite
extern void commonSpriteFlip(int s, int horizontal, int vertical);

// Renvoi l'état de la touche (0 = non appuyée, 1 = appuyée)
extern int commonCheckKey(int key);

#endif // COMMON_H
