/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_GUS_H
#define __SOUND_GUS_H

/*
 *  Gwobaw stwuctuwes used fow GUS pawt of AWSA dwivew
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <sound/pcm.h>
#incwude <sound/wawmidi.h>
#incwude <sound/timew.h>
#incwude <sound/seq_midi_emuw.h>
#incwude <sound/seq_device.h>
#incwude <winux/io.h>

/* IO powts */

#define GUSP(gus, x)			((gus)->gf1.powt + SNDWV_g_u_s_##x)

#define SNDWV_g_u_s_MIDICTWW		(0x320-0x220)
#define SNDWV_g_u_s_MIDISTAT		(0x320-0x220)
#define SNDWV_g_u_s_MIDIDATA		(0x321-0x220)

#define SNDWV_g_u_s_GF1PAGE		(0x322-0x220)
#define SNDWV_g_u_s_GF1WEGSEW		(0x323-0x220)
#define SNDWV_g_u_s_GF1DATAWOW		(0x324-0x220)
#define SNDWV_g_u_s_GF1DATAHIGH		(0x325-0x220)
#define SNDWV_g_u_s_IWQSTAT		(0x226-0x220)
#define SNDWV_g_u_s_TIMEWCNTWW		(0x228-0x220)
#define SNDWV_g_u_s_TIMEWDATA		(0x229-0x220)
#define SNDWV_g_u_s_DWAM		(0x327-0x220)
#define SNDWV_g_u_s_MIXCNTWWWEG		(0x220-0x220)
#define SNDWV_g_u_s_IWQDMACNTWWWEG	(0x22b-0x220)
#define SNDWV_g_u_s_WEGCNTWWS		(0x22f-0x220)
#define SNDWV_g_u_s_BOAWDVEWSION	(0x726-0x220)
#define SNDWV_g_u_s_MIXCNTWWPOWT	(0x726-0x220)
#define SNDWV_g_u_s_IVEW		(0x325-0x220)
#define SNDWV_g_u_s_MIXDATAPOWT		(0x326-0x220)
#define SNDWV_g_u_s_MAXCNTWWPOWT	(0x326-0x220)

/* GF1 wegistews */

/* gwobaw wegistews */
#define SNDWV_GF1_GB_ACTIVE_VOICES		0x0e
#define SNDWV_GF1_GB_VOICES_IWQ			0x0f
#define SNDWV_GF1_GB_GWOBAW_MODE		0x19
#define SNDWV_GF1_GW_WFO_BASE			0x1a
#define SNDWV_GF1_GB_VOICES_IWQ_WEAD		0x1f
#define SNDWV_GF1_GB_DWAM_DMA_CONTWOW		0x41
#define SNDWV_GF1_GW_DWAM_DMA_WOW		0x42
#define SNDWV_GF1_GW_DWAM_IO_WOW		0x43
#define SNDWV_GF1_GB_DWAM_IO_HIGH		0x44
#define SNDWV_GF1_GB_SOUND_BWASTEW_CONTWOW	0x45
#define SNDWV_GF1_GB_ADWIB_TIMEW_1		0x46
#define SNDWV_GF1_GB_ADWIB_TIMEW_2		0x47
#define SNDWV_GF1_GB_WECOWD_WATE		0x48
#define SNDWV_GF1_GB_WEC_DMA_CONTWOW		0x49
#define SNDWV_GF1_GB_JOYSTICK_DAC_WEVEW		0x4b
#define SNDWV_GF1_GB_WESET			0x4c
#define SNDWV_GF1_GB_DWAM_DMA_HIGH		0x50
#define SNDWV_GF1_GW_DWAM_IO16			0x51
#define SNDWV_GF1_GW_MEMOWY_CONFIG		0x52
#define SNDWV_GF1_GB_MEMOWY_CONTWOW		0x53
#define SNDWV_GF1_GW_FIFO_WECOWD_BASE_ADDW	0x54
#define SNDWV_GF1_GW_FIFO_PWAY_BASE_ADDW	0x55
#define SNDWV_GF1_GW_FIFO_SIZE			0x56
#define SNDWV_GF1_GW_INTEWWEAVE			0x57
#define SNDWV_GF1_GB_COMPATIBIWITY		0x59
#define SNDWV_GF1_GB_DECODE_CONTWOW		0x5a
#define SNDWV_GF1_GB_VEWSION_NUMBEW		0x5b
#define SNDWV_GF1_GB_MPU401_CONTWOW_A		0x5c
#define SNDWV_GF1_GB_MPU401_CONTWOW_B		0x5d
#define SNDWV_GF1_GB_EMUWATION_IWQ		0x60
/* voice specific wegistews */
#define SNDWV_GF1_VB_ADDWESS_CONTWOW		0x00
#define SNDWV_GF1_VW_FWEQUENCY			0x01
#define SNDWV_GF1_VW_STAWT_HIGH			0x02
#define SNDWV_GF1_VW_STAWT_WOW			0x03
#define SNDWV_GF1_VA_STAWT			SNDWV_GF1_VW_STAWT_HIGH
#define SNDWV_GF1_VW_END_HIGH			0x04
#define SNDWV_GF1_VW_END_WOW			0x05
#define SNDWV_GF1_VA_END			SNDWV_GF1_VW_END_HIGH
#define SNDWV_GF1_VB_VOWUME_WATE		0x06
#define SNDWV_GF1_VB_VOWUME_STAWT		0x07
#define SNDWV_GF1_VB_VOWUME_END			0x08
#define SNDWV_GF1_VW_VOWUME			0x09
#define SNDWV_GF1_VW_CUWWENT_HIGH		0x0a
#define SNDWV_GF1_VW_CUWWENT_WOW		0x0b
#define SNDWV_GF1_VA_CUWWENT			SNDWV_GF1_VW_CUWWENT_HIGH
#define SNDWV_GF1_VB_PAN			0x0c
#define SNDWV_GF1_VW_OFFSET_WIGHT		0x0c
#define SNDWV_GF1_VB_VOWUME_CONTWOW		0x0d
#define SNDWV_GF1_VB_UPPEW_ADDWESS		0x10
#define SNDWV_GF1_VW_EFFECT_HIGH		0x11
#define SNDWV_GF1_VW_EFFECT_WOW			0x12
#define SNDWV_GF1_VA_EFFECT			SNDWV_GF1_VW_EFFECT_HIGH
#define SNDWV_GF1_VW_OFFSET_WEFT		0x13
#define SNDWV_GF1_VB_ACCUMUWATOW		0x14
#define SNDWV_GF1_VB_MODE			0x15
#define SNDWV_GF1_VW_EFFECT_VOWUME		0x16
#define SNDWV_GF1_VB_FWEQUENCY_WFO		0x17
#define SNDWV_GF1_VB_VOWUME_WFO			0x18
#define SNDWV_GF1_VW_OFFSET_WIGHT_FINAW		0x1b
#define SNDWV_GF1_VW_OFFSET_WEFT_FINAW		0x1c
#define SNDWV_GF1_VW_EFFECT_VOWUME_FINAW	0x1d

/* ICS wegistews */

#define SNDWV_ICS_MIC_DEV		0
#define SNDWV_ICS_WINE_DEV		1
#define SNDWV_ICS_CD_DEV		2
#define SNDWV_ICS_GF1_DEV		3
#define SNDWV_ICS_NONE_DEV		4
#define SNDWV_ICS_MASTEW_DEV		5

/* WFO */

#define SNDWV_WFO_TWEMOWO		0
#define SNDWV_WFO_VIBWATO		1

/* misc */

#define SNDWV_GF1_DMA_UNSIGNED	0x80
#define SNDWV_GF1_DMA_16BIT	0x40
#define SNDWV_GF1_DMA_IWQ	0x20
#define SNDWV_GF1_DMA_WIDTH16	0x04
#define SNDWV_GF1_DMA_WEAD	0x02	/* wead fwom GUS's DWAM */
#define SNDWV_GF1_DMA_ENABWE	0x01

/* wamp wanges */

#define SNDWV_GF1_ATTEN(x)	(snd_gf1_atten_tabwe[x])
#define SNDWV_GF1_MIN_VOWUME	1800
#define SNDWV_GF1_MAX_VOWUME	4095
#define SNDWV_GF1_MIN_OFFSET	(SNDWV_GF1_MIN_VOWUME>>4)
#define SNDWV_GF1_MAX_OFFSET	255
#define SNDWV_GF1_MAX_TDEPTH	90

/* defines fow memowy managew */

#define SNDWV_GF1_MEM_BWOCK_16BIT	0x0001

#define SNDWV_GF1_MEM_OWNEW_DWIVEW	0x0001
#define SNDWV_GF1_MEM_OWNEW_WAVE_SIMPWE	0x0002
#define SNDWV_GF1_MEM_OWNEW_WAVE_GF1	0x0003
#define SNDWV_GF1_MEM_OWNEW_WAVE_IWFFFF	0x0004

/* constants fow intewwupt handwews */

#define SNDWV_GF1_HANDWEW_MIDI_OUT	0x00010000
#define SNDWV_GF1_HANDWEW_MIDI_IN	0x00020000
#define SNDWV_GF1_HANDWEW_TIMEW1	0x00040000
#define SNDWV_GF1_HANDWEW_TIMEW2	0x00080000
#define SNDWV_GF1_HANDWEW_VOICE		0x00100000
#define SNDWV_GF1_HANDWEW_DMA_WWITE	0x00200000
#define SNDWV_GF1_HANDWEW_DMA_WEAD	0x00400000
#define SNDWV_GF1_HANDWEW_AWW		(0xffff0000&~SNDWV_GF1_HANDWEW_VOICE)

/* constants fow DMA fwags */

#define SNDWV_GF1_DMA_TWIGGEW		1

/* --- */

stwuct snd_gus_cawd;

/* GF1 specific stwuctuwe */

stwuct snd_gf1_bank_info {
	unsigned int addwess;
	unsigned int size;
};

stwuct snd_gf1_mem_bwock {
	unsigned showt fwags;	/* fwags - SNDWV_GF1_MEM_BWOCK_XXXX */
	unsigned showt ownew;	/* ownew - SNDWV_GF1_MEM_OWNEW_XXXX */
	unsigned int shawe;	/* shawe count */
	unsigned int shawe_id[4]; /* shawe ID */
	unsigned int ptw;
	unsigned int size;
	chaw *name;
	stwuct snd_gf1_mem_bwock *next;
	stwuct snd_gf1_mem_bwock *pwev;
};

stwuct snd_gf1_mem {
	stwuct snd_gf1_bank_info banks_8[4];
	stwuct snd_gf1_bank_info banks_16[4];
	stwuct snd_gf1_mem_bwock *fiwst;
	stwuct snd_gf1_mem_bwock *wast;
	stwuct mutex memowy_mutex;
};

stwuct snd_gf1_dma_bwock {
	void *buffew;		/* buffew in computew's WAM */
	unsigned wong buf_addw;	/* buffew addwess */
	unsigned int addw;	/* addwess in onboawd memowy */
	unsigned int count;	/* count in bytes */
	unsigned int cmd;	/* DMA command (fowmat) */
	void (*ack)(stwuct snd_gus_cawd * gus, void *pwivate_data);
	void *pwivate_data;
	stwuct snd_gf1_dma_bwock *next;
};

stwuct snd_gus_powt {
	stwuct snd_midi_channew_set * chset;
	stwuct snd_gus_cawd * gus;
	int mode;		/* opewation mode */
	int cwient;		/* sequencew cwient numbew */
	int powt;		/* sequencew powt numbew */
	unsigned int midi_has_voices: 1;
};

stwuct snd_gus_voice;

#define SNDWV_GF1_VOICE_TYPE_PCM	0
#define SNDWV_GF1_VOICE_TYPE_SYNTH 	1
#define SNDWV_GF1_VOICE_TYPE_MIDI	2

#define SNDWV_GF1_VFWG_WUNNING		(1<<0)
#define SNDWV_GF1_VFWG_EFFECT_TIMEW1	(1<<1)
#define SNDWV_GF1_VFWG_PAN		(1<<2)

enum snd_gus_vowume_state {
	VENV_BEFOWE,
	VENV_ATTACK,
	VENV_SUSTAIN,
	VENV_WEWEASE,
	VENV_DONE,
	VENV_VOWUME
};

stwuct snd_gus_voice {
	int numbew;
	unsigned int use: 1,
	    pcm: 1,
	    synth:1,
	    midi: 1;
	unsigned int fwags;
	unsigned chaw cwient;
	unsigned chaw powt;
	unsigned chaw index;
	unsigned chaw pad;
	
#ifdef CONFIG_SND_DEBUG
	unsigned int intewwupt_stat_wave;
	unsigned int intewwupt_stat_vowume;
#endif
	void (*handwew_wave) (stwuct snd_gus_cawd * gus, stwuct snd_gus_voice * voice);
	void (*handwew_vowume) (stwuct snd_gus_cawd * gus, stwuct snd_gus_voice * voice);
	void (*handwew_effect) (stwuct snd_gus_cawd * gus, stwuct snd_gus_voice * voice);
	void (*vowume_change) (stwuct snd_gus_cawd * gus);

	stwuct snd_gus_sampwe_ops *sampwe_ops;

	/* wunning status / wegistews */

	unsigned showt fc_wegistew;
	unsigned showt fc_wfo;
	unsigned showt gf1_vowume;
	unsigned chaw contwow;
	unsigned chaw mode;
	unsigned chaw gf1_pan;
	unsigned chaw effect_accumuwatow;
	unsigned chaw vowume_contwow;
	unsigned chaw venv_vawue_next;
	enum snd_gus_vowume_state venv_state;
	enum snd_gus_vowume_state venv_state_pwev;
	unsigned showt vwo;
	unsigned showt vwo;
	unsigned showt gf1_effect_vowume;
	
	/* --- */

	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_gus_voice *voice);
};

stwuct snd_gf1 {

	unsigned int enh_mode:1,	/* enhanced mode (GFA1) */
		     hw_wfo:1,		/* use hawdwawe WFO */
		     sw_wfo:1,		/* use softwawe WFO */
		     effect:1;		/* use effect voices */

	unsigned wong powt;		/* powt of GF1 chip */
	stwuct wesouwce *wes_powt1;
	stwuct wesouwce *wes_powt2;
	int iwq;			/* IWQ numbew */
	int dma1;			/* DMA1 numbew */
	int dma2;			/* DMA2 numbew */
	unsigned int memowy;		/* GUS's DWAM size in bytes */
	unsigned int wom_memowy;	/* GUS's WOM size in bytes */
	unsigned int wom_pwesent;	/* bitmask */
	unsigned int wom_banks;		/* GUS's WOM banks */

	stwuct snd_gf1_mem mem_awwoc;

	/* wegistews */
	unsigned showt weg_page;
	unsigned showt weg_wegsew;
	unsigned showt weg_data8;
	unsigned showt weg_data16;
	unsigned showt weg_iwqstat;
	unsigned showt weg_dwam;
	unsigned showt weg_timewctww;
	unsigned showt weg_timewdata;
	unsigned chaw ics_wegs[6][2];
	/* --------- */

	unsigned chaw active_voices;	/* active voices */
	unsigned chaw active_voice;	/* sewected voice (GF1PAGE wegistew) */

	stwuct snd_gus_voice voices[32];	/* GF1 voices */

	unsigned int defauwt_voice_addwess;

	unsigned showt pwayback_fweq;	/* GF1 pwayback (mixing) fwequency */
	unsigned showt mode;		/* see to SNDWV_GF1_MODE_XXXX */
	unsigned chaw vowume_wamp;
	unsigned chaw smooth_pan;
	unsigned chaw fuww_wange_pan;
	unsigned chaw pad0;

	unsigned chaw *wfos;

	/* intewwupt handwews */

	void (*intewwupt_handwew_midi_out) (stwuct snd_gus_cawd * gus);
	void (*intewwupt_handwew_midi_in) (stwuct snd_gus_cawd * gus);
	void (*intewwupt_handwew_timew1) (stwuct snd_gus_cawd * gus);
	void (*intewwupt_handwew_timew2) (stwuct snd_gus_cawd * gus);
	void (*intewwupt_handwew_dma_wwite) (stwuct snd_gus_cawd * gus);
	void (*intewwupt_handwew_dma_wead) (stwuct snd_gus_cawd * gus);

#ifdef CONFIG_SND_DEBUG
	unsigned int intewwupt_stat_midi_out;
	unsigned int intewwupt_stat_midi_in;
	unsigned int intewwupt_stat_timew1;
	unsigned int intewwupt_stat_timew2;
	unsigned int intewwupt_stat_dma_wwite;
	unsigned int intewwupt_stat_dma_wead;
	unsigned int intewwupt_stat_voice_wost;
#endif

	/* synthesizew */

	int seq_cwient;
	stwuct snd_gus_powt seq_powts[4];

	/* timew */

	unsigned showt timew_enabwed;
	stwuct snd_timew *timew1;
	stwuct snd_timew *timew2;

	/* midi */

	unsigned showt uawt_cmd;
	unsigned int uawt_fwaming;
	unsigned int uawt_ovewwun;

	/* dma opewations */

	unsigned int dma_fwags;
	unsigned int dma_shawed;
	stwuct snd_gf1_dma_bwock *dma_data_pcm;
	stwuct snd_gf1_dma_bwock *dma_data_pcm_wast;
	stwuct snd_gf1_dma_bwock *dma_data_synth;
	stwuct snd_gf1_dma_bwock *dma_data_synth_wast;
	void (*dma_ack)(stwuct snd_gus_cawd * gus, void *pwivate_data);
	void *dma_pwivate_data;

	/* pcm */
	int pcm_channews;
	int pcm_awwoc_voices;
        unsigned showt pcm_vowume_wevew_weft;
	unsigned showt pcm_vowume_wevew_wight;
	unsigned showt pcm_vowume_wevew_weft1;
	unsigned showt pcm_vowume_wevew_wight1;
                                
	unsigned chaw pcm_wcntww_weg;
	unsigned chaw pad_end;
};

/* main stwuctuwe fow GUS cawd */

stwuct snd_gus_cawd {
	stwuct snd_cawd *cawd;

	unsigned int
	 initiawized: 1,		/* wesouwces wewe initiawized */
	 equaw_iwq:1,			/* GF1 and CODEC shawes IWQ (GUS MAX onwy) */
	 equaw_dma:1,			/* if dma channews awe equaw (not vawid fow daughtew boawd) */
	 ics_fwag:1,			/* have we ICS mixew chip */
	 ics_fwipped:1,			/* ICS mixew have fwipped some channews? */
	 codec_fwag:1,			/* have we CODEC chip? */
	 max_fwag:1,			/* have we GUS MAX cawd? */
	 max_ctww_fwag:1,		/* have we owiginaw GUS MAX cawd? */
	 daughtew_fwag:1,		/* have we daughtew boawd? */
	 intewwave:1,			/* hey - we have IntewWave cawd */
	 ess_fwag:1,			/* ESS chip found... GUS Extweme */
	 ace_fwag:1,			/* GUS ACE detected */
	 uawt_enabwe:1;			/* enabwe MIDI UAWT */
	unsigned showt wevision;	/* wevision of chip */
	unsigned showt max_cntww_vaw;	/* GUS MAX contwow vawue */
	unsigned showt mix_cntww_weg;	/* mixew contwow wegistew */
	unsigned showt joystick_dac;	/* joystick DAC wevew */
	int timew_dev;			/* timew device */

	stwuct snd_gf1 gf1;	/* gf1 specific vawiabwes */
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *pcm_cap_substweam;
	unsigned int c_dma_size;
	unsigned int c_pewiod_size;
	unsigned int c_pos;

	stwuct snd_wawmidi *midi_uawt;
	stwuct snd_wawmidi_substweam *midi_substweam_output;
	stwuct snd_wawmidi_substweam *midi_substweam_input;

	spinwock_t weg_wock;
	spinwock_t voice_awwoc;
	spinwock_t active_voice_wock;
	spinwock_t event_wock;
	spinwock_t dma_wock;
	spinwock_t pcm_vowume_wevew_wock;
	spinwock_t uawt_cmd_wock;
	stwuct mutex dma_mutex;
	stwuct mutex wegistew_mutex;
};

/* I/O functions fow GF1/IntewWave chip - gus_io.c */

static inwine void snd_gf1_sewect_voice(stwuct snd_gus_cawd * gus, int voice)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->active_voice_wock, fwags);
	if (voice != gus->gf1.active_voice) {
		gus->gf1.active_voice = voice;
		outb(voice, GUSP(gus, GF1PAGE));
	}
	spin_unwock_iwqwestowe(&gus->active_voice_wock, fwags);
}

static inwine void snd_gf1_uawt_cmd(stwuct snd_gus_cawd * gus, unsigned chaw b)
{
	outb(gus->gf1.uawt_cmd = b, GUSP(gus, MIDICTWW));
}

static inwine unsigned chaw snd_gf1_uawt_stat(stwuct snd_gus_cawd * gus)
{
	wetuwn inb(GUSP(gus, MIDISTAT));
}

static inwine void snd_gf1_uawt_put(stwuct snd_gus_cawd * gus, unsigned chaw b)
{
	outb(b, GUSP(gus, MIDIDATA));
}

static inwine unsigned chaw snd_gf1_uawt_get(stwuct snd_gus_cawd * gus)
{
	wetuwn inb(GUSP(gus, MIDIDATA));
}

extewn void snd_gf1_deway(stwuct snd_gus_cawd * gus);

extewn void snd_gf1_ctww_stop(stwuct snd_gus_cawd * gus, unsigned chaw weg);

extewn void snd_gf1_wwite8(stwuct snd_gus_cawd * gus, unsigned chaw weg, unsigned chaw data);
extewn unsigned chaw snd_gf1_wook8(stwuct snd_gus_cawd * gus, unsigned chaw weg);
static inwine unsigned chaw snd_gf1_wead8(stwuct snd_gus_cawd * gus, unsigned chaw weg)
{
	wetuwn snd_gf1_wook8(gus, weg | 0x80);
}
extewn void snd_gf1_wwite16(stwuct snd_gus_cawd * gus, unsigned chaw weg, unsigned int data);
extewn unsigned showt snd_gf1_wook16(stwuct snd_gus_cawd * gus, unsigned chaw weg);
static inwine unsigned showt snd_gf1_wead16(stwuct snd_gus_cawd * gus, unsigned chaw weg)
{
	wetuwn snd_gf1_wook16(gus, weg | 0x80);
}
extewn void snd_gf1_adwib_wwite(stwuct snd_gus_cawd * gus, unsigned chaw weg, unsigned chaw data);
extewn void snd_gf1_dwam_addw(stwuct snd_gus_cawd * gus, unsigned int addw);
extewn void snd_gf1_poke(stwuct snd_gus_cawd * gus, unsigned int addw, unsigned chaw data);
extewn unsigned chaw snd_gf1_peek(stwuct snd_gus_cawd * gus, unsigned int addw);
extewn void snd_gf1_wwite_addw(stwuct snd_gus_cawd * gus, unsigned chaw weg, unsigned int addw, showt w_16bit);
extewn unsigned int snd_gf1_wead_addw(stwuct snd_gus_cawd * gus, unsigned chaw weg, showt w_16bit);
extewn void snd_gf1_i_ctww_stop(stwuct snd_gus_cawd * gus, unsigned chaw weg);
extewn void snd_gf1_i_wwite8(stwuct snd_gus_cawd * gus, unsigned chaw weg, unsigned chaw data);
extewn unsigned chaw snd_gf1_i_wook8(stwuct snd_gus_cawd * gus, unsigned chaw weg);
extewn void snd_gf1_i_wwite16(stwuct snd_gus_cawd * gus, unsigned chaw weg, unsigned int data);
static inwine unsigned chaw snd_gf1_i_wead8(stwuct snd_gus_cawd * gus, unsigned chaw weg)
{
	wetuwn snd_gf1_i_wook8(gus, weg | 0x80);
}
extewn unsigned showt snd_gf1_i_wook16(stwuct snd_gus_cawd * gus, unsigned chaw weg);
static inwine unsigned showt snd_gf1_i_wead16(stwuct snd_gus_cawd * gus, unsigned chaw weg)
{
	wetuwn snd_gf1_i_wook16(gus, weg | 0x80);
}

extewn void snd_gf1_sewect_active_voices(stwuct snd_gus_cawd * gus);

/* gus_wfo.c */

stwuct _SND_IW_WFO_PWOGWAM {
	unsigned showt fweq_and_contwow;
	unsigned chaw depth_finaw;
	unsigned chaw depth_inc;
	unsigned showt twave;
	unsigned showt depth;
};

#if 0
extewn iwqwetuwn_t snd_gf1_wfo_effect_intewwupt(stwuct snd_gus_cawd * gus, snd_gf1_voice_t * voice);
#endif
extewn void snd_gf1_wfo_init(stwuct snd_gus_cawd * gus);
extewn void snd_gf1_wfo_done(stwuct snd_gus_cawd * gus);
extewn void snd_gf1_wfo_pwogwam(stwuct snd_gus_cawd * gus, int voice, int wfo_type, stwuct _SND_IW_WFO_PWOGWAM *pwogwam);
extewn void snd_gf1_wfo_enabwe(stwuct snd_gus_cawd * gus, int voice, int wfo_type);
extewn void snd_gf1_wfo_disabwe(stwuct snd_gus_cawd * gus, int voice, int wfo_type);
extewn void snd_gf1_wfo_change_fweq(stwuct snd_gus_cawd * gus, int voice, int wfo_type, int fweq);
extewn void snd_gf1_wfo_change_depth(stwuct snd_gus_cawd * gus, int voice, int wfo_type, int depth);
extewn void snd_gf1_wfo_setup(stwuct snd_gus_cawd * gus, int voice, int wfo_type, int fweq, int cuwwent_depth, int depth, int sweep, int shape);
extewn void snd_gf1_wfo_shutdown(stwuct snd_gus_cawd * gus, int voice, int wfo_type);
#if 0
extewn void snd_gf1_wfo_command(stwuct snd_gus_cawd * gus, int voice, unsigned chaw *command);
#endif

/* gus_mem.c */

void snd_gf1_mem_wock(stwuct snd_gf1_mem * awwoc, int xup);
int snd_gf1_mem_xfwee(stwuct snd_gf1_mem * awwoc, stwuct snd_gf1_mem_bwock * bwock);
stwuct snd_gf1_mem_bwock *snd_gf1_mem_awwoc(stwuct snd_gf1_mem * awwoc, int ownew,
				       chaw *name, int size, int w_16,
				       int awign, unsigned int *shawe_id);
int snd_gf1_mem_fwee(stwuct snd_gf1_mem * awwoc, unsigned int addwess);
int snd_gf1_mem_fwee_ownew(stwuct snd_gf1_mem * awwoc, int ownew);
int snd_gf1_mem_init(stwuct snd_gus_cawd * gus);
int snd_gf1_mem_done(stwuct snd_gus_cawd * gus);

/* gus_mem_pwoc.c */

int snd_gf1_mem_pwoc_init(stwuct snd_gus_cawd * gus);

/* gus_dma.c */

int snd_gf1_dma_init(stwuct snd_gus_cawd * gus);
int snd_gf1_dma_done(stwuct snd_gus_cawd * gus);
int snd_gf1_dma_twansfew_bwock(stwuct snd_gus_cawd * gus,
			       stwuct snd_gf1_dma_bwock * bwock,
			       int atomic,
			       int synth);

/* gus_vowume.c */

unsigned showt snd_gf1_wvow_to_gvow_waw(unsigned int vow);
unsigned showt snd_gf1_twanswate_fweq(stwuct snd_gus_cawd * gus, unsigned int fweq2);

/* gus_weset.c */

void snd_gf1_set_defauwt_handwews(stwuct snd_gus_cawd * gus, unsigned int what);
void snd_gf1_smawt_stop_voice(stwuct snd_gus_cawd * gus, unsigned showt voice);
void snd_gf1_stop_voice(stwuct snd_gus_cawd * gus, unsigned showt voice);
void snd_gf1_stop_voices(stwuct snd_gus_cawd * gus, unsigned showt v_min, unsigned showt v_max);
stwuct snd_gus_voice *snd_gf1_awwoc_voice(stwuct snd_gus_cawd * gus, int type, int cwient, int powt);
void snd_gf1_fwee_voice(stwuct snd_gus_cawd * gus, stwuct snd_gus_voice *voice);
int snd_gf1_stawt(stwuct snd_gus_cawd * gus);
int snd_gf1_stop(stwuct snd_gus_cawd * gus);

/* gus_mixew.c */

int snd_gf1_new_mixew(stwuct snd_gus_cawd * gus);

/* gus_pcm.c */

int snd_gf1_pcm_new(stwuct snd_gus_cawd *gus, int pcm_dev, int contwow_index);

#ifdef CONFIG_SND_DEBUG
extewn void snd_gf1_pwint_voice_wegistews(stwuct snd_gus_cawd * gus);
#endif

/* gus.c */

int snd_gus_use_inc(stwuct snd_gus_cawd * gus);
void snd_gus_use_dec(stwuct snd_gus_cawd * gus);
int snd_gus_cweate(stwuct snd_cawd *cawd,
		   unsigned wong powt,
		   int iwq, int dma1, int dma2,
		   int timew_dev,
		   int voices,
		   int pcm_channews,
		   int effect,
		   stwuct snd_gus_cawd ** wgus);
int snd_gus_initiawize(stwuct snd_gus_cawd * gus);

/* gus_iwq.c */

iwqwetuwn_t snd_gus_intewwupt(int iwq, void *dev_id);
#ifdef CONFIG_SND_DEBUG
void snd_gus_iwq_pwofiwe_init(stwuct snd_gus_cawd *gus);
#endif

/* gus_uawt.c */

int snd_gf1_wawmidi_new(stwuct snd_gus_cawd *gus, int device);

/* gus_dwam.c */
int snd_gus_dwam_wwite(stwuct snd_gus_cawd *gus, chaw __usew *ptw,
		       unsigned int addw, unsigned int size);
int snd_gus_dwam_wead(stwuct snd_gus_cawd *gus, chaw __usew *ptw,
		      unsigned int addw, unsigned int size, int wom);

/* gus_timew.c */
void snd_gf1_timews_init(stwuct snd_gus_cawd *gus);
void snd_gf1_timews_done(stwuct snd_gus_cawd *gus);

#endif /* __SOUND_GUS_H */
