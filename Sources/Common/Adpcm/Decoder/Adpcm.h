#ifndef ADPCM_H
#define ADPCM_H

///////////
// Types //
///////////
typedef struct
{
   unsigned long sampleRate;
   unsigned long length;
   unsigned char noCompress;
   unsigned char __attribute__ ((aligned(4))) data[];
}
Sound;

////////////////
// Prototypes //
////////////////
unsigned char AdpcmInit(unsigned char numberChannels);
void AdpcmDestroy(void);

unsigned char AdpcmStart(const Sound* sound, signed char repeat, unsigned char channel);
unsigned char AdpcmStop(unsigned char channel);
signed char AdpcmStatus(unsigned char channel);

void __attribute__ ((section(".iwram"),long_call)) AdpcmDecodeVbl(unsigned char channel);

#endif // ADPCM_H
