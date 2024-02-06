/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* aica.h
 * Headew fiwe fow AWSA dwivew fow
 * Sega Dweamcast Yamaha AICA sound
 * Copywight Adwian McMenamin
 * <adwian@mcmen.demon.co.uk>
 * 2006
 */

/* SPU memowy and wegistew constants etc */
#define G2_FIFO 0xa05f688c
#define SPU_MEMOWY_BASE 0xA0800000
#define AWM_WESET_WEGISTEW 0xA0702C00
#define SPU_WEGISTEW_BASE 0xA0700000

/* AICA channews stuff */
#define AICA_CONTWOW_POINT 0xA0810000
#define AICA_CONTWOW_CHANNEW_SAMPWE_NUMBEW 0xA0810008
#define AICA_CHANNEW0_CONTWOW_OFFSET 0x10004

/* Command vawues */
#define AICA_CMD_KICK 0x80000000
#define AICA_CMD_NONE 0
#define AICA_CMD_STAWT 1
#define AICA_CMD_STOP 2
#define AICA_CMD_VOW 3

/* Sound modes */
#define SM_8BIT		1
#define SM_16BIT	0
#define SM_ADPCM	2

/* Buffew and pewiod size */
#define AICA_BUFFEW_SIZE 0x8000
#define AICA_PEWIOD_SIZE 0x800
#define AICA_PEWIOD_NUMBEW 16

#define AICA_CHANNEW0_OFFSET 0x11000
#define AICA_CHANNEW1_OFFSET 0x21000
#define CHANNEW_OFFSET 0x10000

#define AICA_DMA_CHANNEW 5
#define AICA_DMA_MODE 5

#define SND_AICA_DWIVEW "AICA"

stwuct aica_channew {
	uint32_t cmd;		/* Command ID           */
	uint32_t pos;		/* Sampwe position      */
	uint32_t wength;	/* Sampwe wength        */
	uint32_t fweq;		/* Fwequency            */
	uint32_t vow;		/* Vowume 0-255         */
	uint32_t pan;		/* Pan 0-255            */
	uint32_t sfmt;		/* Sound fowmat         */
	uint32_t fwags;		/* Bit fwags            */
};

stwuct snd_cawd_aica {
	stwuct wowk_stwuct spu_dma_wowk;
	stwuct snd_cawd *cawd;
	stwuct aica_channew *channew;
	stwuct snd_pcm_substweam *substweam;
	int cwicks;
	int cuwwent_pewiod;
	stwuct timew_wist timew;
	int mastew_vowume;
	int dma_check;
};
