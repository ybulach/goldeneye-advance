////////////////
// Inclusions //
////////////////
#include "Common.h"

////////////////////////
// Variables globales //
////////////////////////
// Ecran
u16* videoBuffer = (u16*) 0x6000000;
u16* palette = (u16*) 0x5000000;

// Sprites
OAMEntry OAMBuffer[MAX_SPRITES];
u16* OAMData = (u16*) 0x6010000;
u16* spritePalette = (u16*) 0x05000200;

void* IntrTable[14]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

///////////////////////
// commonFlipBuffers //
///////////////////////
void commonFlipBuffers()
{
	if(REG_DISPCNT & BACKBUFFER)
	{
		REG_DISPCNT &= ~BACKBUFFER;
		videoBuffer = videoBackBuffer;
	}
	else
	{
		REG_DISPCNT |= BACKBUFFER;
		videoBuffer = videoFrontBuffer;
	}
}

/////////////////////
// commonWaitVSync //
/////////////////////
void commonWaitVSync()
{
	volatile u16* vreg = (volatile u16*) 0x4000004;
	while(*vreg & (1 << 0));
	while(!(*vreg & (1 << 0)));
}

///////////////////
// commonWaitKey //
///////////////////
void commonWaitKey(int key)
{
	while(1)
		if(!(REG_KEYS & key)) break;
}

/////////////////////////
// commonCopyOAMBuffer //
/////////////////////////
void commonCopyOAMBuffer()
{
	commonDMACopy((void*)OAMBuffer, (void*)OAM, MAX_SPRITES * 4, DMA_16NOW);
}

///////////////////
// commonDMACopy //
///////////////////
void commonDMACopy(void* source, void* dest, u16 size, u16 type)
{
	REG_DMA3SAD = (u32) source;
	REG_DMA3DAD = (u32) dest;
	REG_DMA3CNT_L = size;
	REG_DMA3CNT_H = type;
	
	//AAS_DoDMA3((u32) source, (u32) dest, size | type);
}

////////////////////
// commonWaitTime //
////////////////////
void commonWaitTime(int seconds, int milliSeconds)
{
	REG_TM2CNT = FREQUENCY_256 | TIMER_ENABLE;
	REG_TM3CNT = TIMER_CASCADE | TIMER_ENABLE;
	REG_TM2D = 0;
	REG_TM3D = 0;
	
	while(REG_TM3D < seconds);
	
	REG_TM2D = 0;
	while(REG_TM2D / (65536 / 1000) < milliSeconds);
	
	REG_TM2CNT = 0;
	REG_TM3CNT = 0;
	REG_TM2D = 0;
	REG_TM3D = 0;
}

///////////////////
// commonFadeOut //
///////////////////
void commonFadeOut()
{
	u16 r, g, b;
	
	int i, j;
	
	for(i = 0; i < 32; i++)
	{
		for(j = 0; j < 256; j++)
		{
			r = (palette[j]) & 0x1F;
			g = (palette[j] >> 5) & 0x1F;
			b = (palette[j] >> 10) & 0x1F;
			
			if(r > 0) r--;
			if(g > 0) g--;
			if(b > 0) b--;
			
			palette[j] = RGB(r, g, b);
		}
		
		commonWaitTime(0, 1000 / 32);
	}
}

//////////////////
// commonFadeIn //
//////////////////
void commonFadeIn(const u16 picture[], const u16 pictpal[])
{
	// Copie de la palette
	commonDMACopy((void*)NULL, (void*)palette, 256, DMA_16NOW);
	
	// Copie de l'image
	commonDMACopy((void*)picture, (void*)videoBuffer, SCREEN_HEIGHT * SCREEN_WIDTH / 2, DMA_16NOW);
	
	u16 r, g, b;
	int i, j;
	for(i = 0; i < 32; i++)
	{
		for(j = 0; j < 256; j++)
		{
			r = (palette[j]) & 0x1F;
			g = (palette[j] >> 5) & 0x1F;
			b = (palette[j] >> 10) & 0x1F;
			
			if(r < ((pictpal[j]) & 0x1F)) r++;
			if(g < ((pictpal[j] >> 5) & 0x1F)) g++;
			if(b < ((pictpal[j] >> 10) & 0x1F)) b++;
			
			palette[j] = RGB(r, g, b);
		}
		
		commonWaitTime(0, 1000 / 32);
	}
}

/////////////////////
// commonMosaicOut //
/////////////////////
void commonMosaicOut()
{
	s16 mosaic;
	for(mosaic = 0; mosaic < 16; mosaic++)
	{
		REG_MOSAIC = SetMosaic(mosaic, mosaic, 0, 0);
		commonWaitTime(0, 1000 / 16);
	}
}

////////////////////
// commonMosaicIn //
////////////////////
void commonMosaicIn()
{
	s16 mosaic;
	for(mosaic = 15; mosaic >= 0; mosaic--)
	{
		REG_MOSAIC = SetMosaic(mosaic, mosaic, 0, 0);
		commonWaitTime(0, 1000 / 16);
	}
}

///////////////////////
// commonInitSprites //
///////////////////////
void commonInitSprites()
{
	commonResetSprites();
}

////////////////////////
// commonResetSprites //
////////////////////////
void commonResetSprites()
{
	int i;
	for(i = 0; i < MAX_SPRITES; i++)
	{
		OAMBuffer[i].attribute0 = 160;
		OAMBuffer[i].attribute1 = 240;
		OAMBuffer[i].attribute2 = SPRITE_VIDE;
	}
	
	// Copie des sprites dans la mémoire OAM
	commonCopyOAMBuffer();
}

///////////////////////
// commonResetSprite //
///////////////////////
void commonResetSprite(u8 sprite)
{
	OAMBuffer[sprite].attribute0 = 160;
	OAMBuffer[sprite].attribute1 = 240;
	OAMBuffer[sprite].attribute2 = SPRITE_VIDE;
	
	// Copie des sprites dans la mémoire OAM
	commonCopyOAMBuffer();
}

///////////////////////
// commonWriteString //
///////////////////////
u16 commonWriteString(u16 pointer, u16 x, u16 y, const char* string)
{
	//u8 length;
	int bloc = 0;
	int	i = 0;
	
	// Affichage de la chaine de caracteres
	while(string[i] != '\0')
	{
		// Positionne le sprite (sauf pour les espaces ou caracteres inconnus)
		if(string[i] != ' ')
		{
			OAMBuffer[pointer].attribute0 = COLOR_256 | SQUARE | y;
			OAMBuffer[pointer].attribute1 = SIZE_8 | x;
			
			// On choisi le bon caractère parmis les sprites
			if(string[i] == 'A')
				bloc = 0;
			else if(string[i] == 'B')
				bloc = 1;
			else if(string[i] == 'C')
				bloc = 2;
			else if(string[i] == 'D')
				bloc = 3;
			else if(string[i] == 'E')
				bloc = 4;
			else if(string[i] == 'F')
				bloc = 5;
			else if(string[i] == 'G')
				bloc = 6;
			else if(string[i] == 'H')
				bloc = 7;
			else if(string[i] == 'I')
				bloc = 8;
			else if(string[i] == 'J')
				bloc = 9;
			else if(string[i] == 'K')
				bloc = 10;
			else if(string[i] == 'L')
				bloc = 11;
			else if(string[i] == 'M')
				bloc = 12;
			else if(string[i] == 'N')
				bloc = 13;
			else if(string[i] == 'O')
				bloc = 14;
			else if(string[i] == 'P')
				bloc = 15;
			else if(string[i] == 'Q')
				bloc = 16;
			else if(string[i] == 'R')
				bloc = 17;
			else if(string[i] == 'S')
				bloc = 18;
			else if(string[i] == 'T')
				bloc = 19;
			else if(string[i] == 'U')
				bloc = 20;
			else if(string[i] == 'V')
				bloc = 21;
			else if(string[i] == 'W')
				bloc = 22;
			else if(string[i] == 'X')
				bloc = 23;
			else if(string[i] == 'Y')
				bloc = 24;
			else if(string[i] == 'Z')
				bloc = 25;
			else if(string[i] == '0')
				bloc = 26;
			else if(string[i] == '1')
				bloc = 27;
			else if(string[i] == '2')
				bloc = 28;
			else if(string[i] == '3')
				bloc = 29;
			else if(string[i] == '4')
				bloc = 30;
			else if(string[i] == '5')
				bloc = 31;
			else if(string[i] == '6')
				bloc = 32;
			else if(string[i] == '7')
				bloc = 33;
			else if(string[i] == '8')
				bloc = 34;
			else if(string[i] == '9')
				bloc = 35;
			else if(string[i] == '!')
				bloc = 36;
			else if(string[i] == '?')
				bloc = 37;
			else if(string[i] == '\'')
				bloc = 38;
			else if(string[i] == '(')
				bloc = 39;
			else if(string[i] == ')')
				bloc = 40;
			else if(string[i] == ',')
				bloc = 41;
			else if(string[i] == '-')
				bloc = 42;
			else if(string[i] == ':')
				bloc = 43;
			else if(string[i] == 'x')
				bloc = 44;
			else if(string[i] == '&')
				bloc = 45;
			else if(string[i] == '.')
				bloc = 46;
			else
				bloc = 47;
			
			commonSpriteChangeGfx(pointer, SPRITE_FONT + SPRITE_CALC_BLOC(bloc), 0);
			++pointer;
		}
		
		// Caractere suivant...
		i++;
		x += 8;
	}
	
	// Retourne le pointeur sur le prochain sprite libre
	return pointer;
}

//////////////////////////
// commonDisplayPicture //
//////////////////////////
void commonDisplayPicture(const u16 picture[], const u16 pictpal[])
{
	// Copie de la palette
	commonDMACopy((void*)pictpal, (void*)palette, 256, DMA_16NOW);
	
	// Copie de l'image
	commonDMACopy((void*)picture, (void*)videoBuffer, SCREEN_HEIGHT * SCREEN_WIDTH / 2, DMA_16NOW);
}

////////////////////////
// commonSRAMSaveByte //
////////////////////////
void commonSRAMSaveByte(u16 offset, u8 value)
{
	*(u8*) (SRAM + offset) = value;
}

///////////////////////
// commonSRAMSaveInt //
///////////////////////
void commonSRAMSaveInt(u16 offset, int value)
{
	u8 b1 = (u8) ((value) & 0xFF);
	u8 b2 = (u8) ((value >> 8) & 0xFF);
	u8 b3 = (u8) ((value >> 16) & 0xFF);
	u8 b4 = (u8) ((value >> 24));
	
	commonSRAMSaveByte(offset + 0, b1);
	commonSRAMSaveByte(offset + 1, b2);
	commonSRAMSaveByte(offset + 2, b3);
	commonSRAMSaveByte(offset + 3, b4);
}

//////////////////////////
// commonSRAMSaveString //
//////////////////////////
void commonSRAMSaveString(u16 offset, char* value)
{
	int i = 0;
	while (value[i] != '\0')
	{
		*(u8 *) (SRAM + offset + i) = value[i];
		i++;
	}
	*(u8 *) (SRAM + offset + i) = '\0';
}

////////////////////////
// commonSRAMLoadByte //
////////////////////////
u8 commonSRAMLoadByte(u16 offset)
{
	return *(u8*) (SRAM + offset);
}

///////////////////////
// commonSRAMLoadInt //
///////////////////////
int commonSRAMLoadInt(u16 offset)
{
	u8 b1 = commonSRAMLoadByte(offset + 0);
	u8 b2 = commonSRAMLoadByte(offset + 1);
	u8 b3 = commonSRAMLoadByte(offset + 2);
	u8 b4 = commonSRAMLoadByte(offset + 3);
	
	return (int) ((b1 & 0xFF) | ((b2 << 8) & 0xFF00) | ((b3 << 16) & 0xFF0000) | (b4 << 24));
}

//////////////////////////
// commonSRAMLoadString //
//////////////////////////
char* commonSRAMLoadString(u16 offset, int size)
{
	char* texte;
	int i;
	
	for (i = 0; i != size; i++)
		texte[i] = *(u8 *) (SRAM + offset + i);//commonSRAMLoadByte(offset + i);
	
	return texte;
}

////////////////////////
// commonSetInterrupt //
////////////////////////
s16 commonSetInterrupt(u16 interruption, IntrFunction* fonction)
{
	s16 numero;
	
	// Desactive toutes les interruptions...
	REG_IME = 0;
	
	// Certains registres doivent etre modifies
	switch(interruption)
	{
		case IT_VBLANK:
			REG_DISPSTAT |= E_VBLANK; // Met a 1 le "V-Blank Interrupt Request Enable Flag"
			numero = 0;
			break;
		case IT_HBLANK:
			REG_DISPSTAT |= E_HBLANK; // Met a 1 le "H-Blank Interrupt Request Enable Flag"
			numero = 1;
			break;
		case IT_TIMER0:
			REG_TM0CNT |= 0x40; // Met a 1 le "Interrupt Request Enable Flag" (timers 0 a 3)
			numero = 3;
			break;
		case IT_TIMER1:
			REG_TM1CNT |= 0x40;
			numero = 4;
			break;
		case IT_TIMER2:
			REG_TM2CNT |= 0x40;
			numero = 5;
			break;
		case IT_TIMER3:
			REG_TM3CNT |= 0x40;
			numero = 6;
			break;
		case IT_DMA0:
			REG_DMA0CNT_H |= 0x4000; // Met a 1 le "Interrupt Request Enable Flag" (DMA 0 a 3)
			numero = 8;
			break;
		case IT_DMA1:
			REG_DMA1CNT_H |= 0x4000;
			numero = 9;
			break;
		case IT_DMA2:
			REG_DMA1CNT_H |= 0x4000;
			numero = 10;
			break;
		case IT_DMA3:
			REG_DMA1CNT_H |= 0x4000;
			numero = 11;
			break;
		default:
			numero = -1;
		break;
	}
	
	// Active l'interruption demandee et memorise l'adresse de la fonction a appeler
	if(numero >= 0)
	{
		REG_IE |= interruption;
		if(fonction)
			IntrTable[numero] = fonction;
	}
	
	// Reactive les interruptions !
	REG_IME = 1;
	return numero;
}

/////////////////////////////
// commonSetYtrigInterrupt //
/////////////////////////////
void commonSetYtrigInterrupt(u8 ligne, IntrFunction* fonction)
{
	// Desactive toutes les interruptions...
	REG_IME = 0;
	
	// Certains registres doivent etre modifies
	REG_DISPSTAT &= 255; // Nettoie le "V count setting" (on le renseigne a la ligne suivante)
	REG_DISPSTAT |= E_YTRIG | (ligne << 8); // Met a 1 le "V Counter Match Interrupt Request Enable Flag"
	REG_IE |= IT_YTRIG;
	
	// Memorise l'adresse de la fonction a appeler
	if(fonction)
		IntrTable[2] = fonction;
	
	// Reactive les interruptions !
	REG_IME = 1;
}

///////////////////////////
// commonEnableInterrupt //
///////////////////////////
inline s16 commonEnableInterrupt(u16 interruption)
{
	return commonSetInterrupt(interruption, NULL);
}

////////////////////////////
// commonDisableInterrupt //
////////////////////////////
void commonDisableInterrupt(u16 interruption)
{
	REG_IME = 0;
	REG_IE &= ~interruption;
	REG_IME = 1;
}

/////////////////////////////
// commonBasicVblInterrupt //
/////////////////////////////
void commonBasicVblInterrupt(void)
{
	//AAS_DoWork();
	
	++compteVBL;
}

///////////////////////
// commonIntToString //
///////////////////////
void commonIntToString(int value, char* string)
{
	int nb[2];
	
	// Les dizaines
	nb[0] = value / 10;
	// Les unités
	nb[1] = value - (nb[0] * 10);
	
	int i;
	for(i = 0; i < 2; i++)
	{
		if(nb[i] == 0)
			string[i] = '0';
		else if(nb[i] == 1)
			string[i] = '1';
		else if(nb[i] == 2)
			string[i] = '2';
		else if(nb[i] == 3)
			string[i] = '3';
		else if(nb[i] == 4)
			string[i] = '4';
		else if(nb[i] == 5)
			string[i] = '5';
		else if(nb[i] == 6)
			string[i] = '6';
		else if(nb[i] == 7)
			string[i] = '7';
		else if(nb[i] == 8)
			string[i] = '8';
		else if(nb[i] == 9)
			string[i] = '9';
		else
			string[i] = '0';
	}
}

///////////////////////////
// commonSpriteChangePos //
///////////////////////////
void commonSpriteChangePos(int s, int x, int y)
{
	OAMBuffer[s].attribute0 &= 0xFF00;
	OAMBuffer[s].attribute0 |= y;
	OAMBuffer[s].attribute1 &= 0xFE00;
	OAMBuffer[s].attribute1 |= x;
}

///////////////////////////
// commonSpriteChangeGfx //
///////////////////////////
void commonSpriteChangeGfx(int s, int gfx, int priority)
{
	OAMBuffer[s].attribute2 = gfx | (priority << 10);
}

//////////////////////
// commonSpriteFlip //
//////////////////////
void commonSpriteFlip(int s, int horizontal, int vertical)
{
	if(horizontal)
		OAMBuffer[s].attribute1 |= 0x1000;
	else
		OAMBuffer[s].attribute1 &= ~0x1000;
		
	if(vertical)
		OAMBuffer[s].attribute1 ^= 0x2000;
	else
		OAMBuffer[s].attribute1 &= ~0x2000;
}

////////////////////
// commonCheckKey //
////////////////////
int commonCheckKey(int key)
{
	return !(REG_KEYS & key);
}
