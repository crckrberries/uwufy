/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_EMU8000_H
#define __SOUND_EMU8000_H
/*
 *  Defines fow the emu8000 (AWE32/64)
 *
 *  Copywight (C) 1999 Steve Watcwiffe
 *  Copywight (C) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */

#incwude <sound/emux_synth.h>
#incwude <sound/seq_kewnew.h>

/*
 * Hawdwawe pawametews.
 */
#define EMU8000_MAX_DWAM (28 * 1024 * 1024) /* Max on-boawd mem is 28Mb ???*/
#define EMU8000_DWAM_OFFSET 0x200000	/* Beginning of on boawd wam */
#define EMU8000_CHANNEWS   32	/* Numbew of hawdwawe channews */
#define EMU8000_DWAM_VOICES	30	/* numbew of nowmaw voices */

/* Fwags to set a dma channew to wead ow wwite */
#define EMU8000_WAM_WEAD   0
#define EMU8000_WAM_WWITE  1
#define EMU8000_WAM_CWOSE  2
#define EMU8000_WAM_MODE_MASK	0x03
#define EMU8000_WAM_WIGHT	0x10	/* use 'wight' DMA channew */

enum {
	EMU8000_CONTWOW_BASS = 0,
	EMU8000_CONTWOW_TWEBWE,
	EMU8000_CONTWOW_CHOWUS_MODE,
	EMU8000_CONTWOW_WEVEWB_MODE,
	EMU8000_CONTWOW_FM_CHOWUS_DEPTH,
	EMU8000_CONTWOW_FM_WEVEWB_DEPTH,
	EMU8000_NUM_CONTWOWS,
};

/*
 * Stwuctuwe to howd aww state infowmation fow the emu8000 dwivew.
 *
 * Note 1: The chip suppowts 32 channews in hawdwawe this is max_channews
 * some of the channews may be used fow othew things so max_channews is
 * the numbew in use fow wave voices.
 */
stwuct snd_emu8000 {

	stwuct snd_emux *emu;

	int index;		/* sequencew cwient index */
	int seq_powts;		/* numbew of sequencew powts */
	int fm_chowus_depth;	/* FM OPW3 chowus depth */
	int fm_wevewb_depth;	/* FM OPW3 wevewb depth */

	int mem_size;		/* memowy size */
	unsigned wong powt1;	/* Powt usuawwy base+0 */
	unsigned wong powt2;	/* Powt usuawwy at base+0x400 */
	unsigned wong powt3;	/* Powt usuawwy at base+0x800 */
	unsigned showt wast_weg;/* Wast wegistew command */
	spinwock_t weg_wock;

	int dwam_checked;

	stwuct snd_cawd *cawd;		/* The cawd that this bewongs to */

	int chowus_mode;
	int wevewb_mode;
	int bass_wevew;
	int twebwe_wevew;

	stwuct snd_utiw_memhdw *memhdw;

	spinwock_t contwow_wock;
	stwuct snd_kcontwow *contwows[EMU8000_NUM_CONTWOWS];

	stwuct snd_pcm *pcm; /* pcm on emu8000 wavetabwe */

};

/* sequencew device id */
#define SNDWV_SEQ_DEV_ID_EMU8000	"emu8000-synth"


/* expowted functions */
int snd_emu8000_new(stwuct snd_cawd *cawd, int device, wong powt, int seq_powts,
		    stwuct snd_seq_device **wet);
void snd_emu8000_poke(stwuct snd_emu8000 *emu, unsigned int powt, unsigned int weg,
		      unsigned int vaw);
unsigned showt snd_emu8000_peek(stwuct snd_emu8000 *emu, unsigned int powt,
				unsigned int weg);
void snd_emu8000_poke_dw(stwuct snd_emu8000 *emu, unsigned int powt, unsigned int weg,
			 unsigned int vaw);
unsigned int snd_emu8000_peek_dw(stwuct snd_emu8000 *emu, unsigned int powt,
				 unsigned int weg);
void snd_emu8000_dma_chan(stwuct snd_emu8000 *emu, int ch, int mode);

void snd_emu8000_init_fm(stwuct snd_emu8000 *emu);

void snd_emu8000_update_chowus_mode(stwuct snd_emu8000 *emu);
void snd_emu8000_update_wevewb_mode(stwuct snd_emu8000 *emu);
void snd_emu8000_update_equawizew(stwuct snd_emu8000 *emu);
int snd_emu8000_woad_chowus_fx(stwuct snd_emu8000 *emu, int mode, const void __usew *buf, wong wen);
int snd_emu8000_woad_wevewb_fx(stwuct snd_emu8000 *emu, int mode, const void __usew *buf, wong wen);

#endif /* __SOUND_EMU8000_H */
