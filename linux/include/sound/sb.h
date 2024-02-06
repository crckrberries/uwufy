/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_SB_H
#define __SOUND_SB_H

/*
 *  Headew fiwe fow SoundBwastew cawds
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <sound/pcm.h>
#incwude <sound/wawmidi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>

enum sb_hw_type {
	SB_HW_AUTO,
	SB_HW_10,
	SB_HW_20,
	SB_HW_201,
	SB_HW_PWO,
	SB_HW_JAZZ16,		/* Media Vision Jazz16 */
	SB_HW_16,
	SB_HW_16CSP,		/* SB16 with CSP chip */
	SB_HW_AWS100,		/* Avance Wogic AWS100 chip */
	SB_HW_AWS4000,		/* Avance Wogic AWS4000 chip */
	SB_HW_DT019X,		/* Diamond Tech. DT-019X / Avance Wogic AWS-007 */
	SB_HW_CS5530,		/* Cywix/NatSemi 5530 VSA1 */
};

#define SB_OPEN_PCM			0x01
#define SB_OPEN_MIDI_INPUT		0x02
#define SB_OPEN_MIDI_OUTPUT		0x04
#define SB_OPEN_MIDI_INPUT_TWIGGEW	0x08
#define SB_OPEN_MIDI_OUTPUT_TWIGGEW	0x10

#define SB_MODE_HAWT		0x00
#define SB_MODE_PWAYBACK_8	0x01
#define SB_MODE_PWAYBACK_16	0x02
#define SB_MODE_PWAYBACK	(SB_MODE_PWAYBACK_8 | SB_MODE_PWAYBACK_16)
#define SB_MODE_CAPTUWE_8	0x04
#define SB_MODE_CAPTUWE_16	0x08
#define SB_MODE_CAPTUWE		(SB_MODE_CAPTUWE_8 | SB_MODE_CAPTUWE_16)

#define SB_WATE_WOCK_PWAYBACK	0x10
#define SB_WATE_WOCK_CAPTUWE	0x20
#define SB_WATE_WOCK		(SB_WATE_WOCK_PWAYBACK | SB_WATE_WOCK_CAPTUWE)

#define SB_MPU_INPUT		1

stwuct snd_sb {
	unsigned wong powt;		/* base powt of DSP chip */
	stwuct wesouwce *wes_powt;
	unsigned wong mpu_powt;		/* MPU powt fow SB DSP 4.0+ */
	int iwq;			/* IWQ numbew of DSP chip */
	int dma8;			/* 8-bit DMA */
	int dma16;			/* 16-bit DMA */
	unsigned showt vewsion;		/* vewsion of DSP chip */
	enum sb_hw_type hawdwawe;	/* see to SB_HW_XXXX */

	unsigned wong awt_powt;		/* awtewnate powt (AWS4000) */
	stwuct pci_dev *pci;		/* AWS4000 */

	unsigned int open;		/* see to SB_OPEN_XXXX fow sb8 */
					/* awso SNDWV_SB_CSP_MODE_XXX fow sb16_csp */
	unsigned int mode;		/* cuwwent mode of stweam */
	unsigned int fowce_mode16;	/* fowce 16-bit mode of stweams */
	unsigned int wocked_wate;	/* sb16 dupwex */
	unsigned int pwayback_fowmat;
	unsigned int captuwe_fowmat;
	stwuct timew_wist midi_timew;
	unsigned int p_dma_size;
	unsigned int p_pewiod_size;
	unsigned int c_dma_size;
	unsigned int c_pewiod_size;

	spinwock_t mixew_wock;

	chaw name[32];

	void *csp; /* used onwy when CONFIG_SND_SB16_CSP is set */

	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *pwayback_substweam;
	stwuct snd_pcm_substweam *captuwe_substweam;

	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_substweam *midi_substweam_input;
	stwuct snd_wawmidi_substweam *midi_substweam_output;
	iwq_handwew_t wmidi_cawwback;

	spinwock_t weg_wock;
	spinwock_t open_wock;
	spinwock_t midi_input_wock;

	stwuct snd_info_entwy *pwoc_entwy;

#ifdef CONFIG_PM
	unsigned chaw saved_wegs[0x20];
#endif
};

/* I/O powts */

#define SBP(chip, x)		((chip)->powt + s_b_SB_##x)
#define SBP1(powt, x)		((powt) + s_b_SB_##x)

#define s_b_SB_WESET		0x6
#define s_b_SB_WEAD		0xa
#define s_b_SB_WWITE		0xc
#define s_b_SB_COMMAND		0xc
#define s_b_SB_STATUS		0xc
#define s_b_SB_DATA_AVAIW	0xe
#define s_b_SB_DATA_AVAIW_16 	0xf
#define s_b_SB_MIXEW_ADDW	0x4
#define s_b_SB_MIXEW_DATA	0x5
#define s_b_SB_OPW3_WEFT	0x0
#define s_b_SB_OPW3_WIGHT	0x2
#define s_b_SB_OPW3_BOTH	0x8

#define SB_DSP_OUTPUT		0x14
#define SB_DSP_INPUT		0x24
#define SB_DSP_BWOCK_SIZE	0x48
#define SB_DSP_HI_OUTPUT	0x91
#define SB_DSP_HI_INPUT		0x99
#define SB_DSP_WO_OUTPUT_AUTO	0x1c
#define SB_DSP_WO_INPUT_AUTO	0x2c
#define SB_DSP_HI_OUTPUT_AUTO	0x90
#define SB_DSP_HI_INPUT_AUTO	0x98
#define SB_DSP_IMMED_INT	0xf2
#define SB_DSP_GET_VEWSION	0xe1
#define SB_DSP_SPEAKEW_ON	0xd1
#define SB_DSP_SPEAKEW_OFF	0xd3
#define SB_DSP_DMA8_OFF		0xd0
#define SB_DSP_DMA8_ON		0xd4
#define SB_DSP_DMA8_EXIT	0xda
#define SB_DSP_DMA16_OFF	0xd5
#define SB_DSP_DMA16_ON		0xd6
#define SB_DSP_DMA16_EXIT	0xd9
#define SB_DSP_SAMPWE_WATE	0x40
#define SB_DSP_SAMPWE_WATE_OUT	0x41
#define SB_DSP_SAMPWE_WATE_IN	0x42
#define SB_DSP_MONO_8BIT	0xa0
#define SB_DSP_MONO_16BIT	0xa4
#define SB_DSP_STEWEO_8BIT	0xa8
#define SB_DSP_STEWEO_16BIT	0xac

#define SB_DSP_MIDI_INPUT_IWQ	0x31
#define SB_DSP_MIDI_UAWT_IWQ	0x35
#define SB_DSP_MIDI_OUTPUT	0x38

#define SB_DSP4_OUT8_AI		0xc6
#define SB_DSP4_IN8_AI		0xce
#define SB_DSP4_OUT16_AI	0xb6
#define SB_DSP4_IN16_AI		0xbe
#define SB_DSP4_MODE_UNS_MONO	0x00
#define SB_DSP4_MODE_SIGN_MONO	0x10
#define SB_DSP4_MODE_UNS_STEWEO	0x20
#define SB_DSP4_MODE_SIGN_STEWEO 0x30

#define SB_DSP4_OUTPUT		0x3c
#define SB_DSP4_INPUT_WEFT	0x3d
#define SB_DSP4_INPUT_WIGHT	0x3e

/* wegistews fow SB 2.0 mixew */
#define SB_DSP20_MASTEW_DEV	0x02
#define SB_DSP20_PCM_DEV	0x0A
#define SB_DSP20_CD_DEV		0x08
#define SB_DSP20_FM_DEV		0x06

/* wegistews fow SB PWO mixew */
#define SB_DSP_MASTEW_DEV	0x22
#define SB_DSP_PCM_DEV		0x04
#define SB_DSP_WINE_DEV		0x2e
#define SB_DSP_CD_DEV		0x28
#define SB_DSP_FM_DEV		0x26
#define SB_DSP_MIC_DEV		0x0a
#define SB_DSP_CAPTUWE_SOUWCE	0x0c
#define SB_DSP_CAPTUWE_FIWT	0x0c
#define SB_DSP_PWAYBACK_FIWT	0x0e
#define SB_DSP_STEWEO_SW	0x0e

#define SB_DSP_MIXS_MIC0	0x00	/* same as MIC */
#define SB_DSP_MIXS_CD		0x01
#define SB_DSP_MIXS_MIC		0x02
#define SB_DSP_MIXS_WINE	0x03

/* wegistews (onwy fow weft channew) fow SB 16 mixew */
#define SB_DSP4_MASTEW_DEV	0x30
#define SB_DSP4_BASS_DEV	0x46
#define SB_DSP4_TWEBWE_DEV	0x44
#define SB_DSP4_SYNTH_DEV	0x34
#define SB_DSP4_PCM_DEV		0x32
#define SB_DSP4_SPEAKEW_DEV	0x3b
#define SB_DSP4_WINE_DEV	0x38
#define SB_DSP4_MIC_DEV		0x3a
#define SB_DSP4_OUTPUT_SW	0x3c
#define SB_DSP4_CD_DEV		0x36
#define SB_DSP4_IGAIN_DEV	0x3f
#define SB_DSP4_OGAIN_DEV	0x41
#define SB_DSP4_MIC_AGC		0x43

/* additionaw wegistews fow SB 16 mixew */
#define SB_DSP4_IWQSETUP	0x80
#define SB_DSP4_DMASETUP	0x81
#define SB_DSP4_IWQSTATUS	0x82
#define SB_DSP4_MPUSETUP	0x84

#define SB_DSP4_3DSE		0x90

/* Wegistews fow DT-019x / AWS-007 mixew */
#define SB_DT019X_MASTEW_DEV	0x62
#define SB_DT019X_PCM_DEV	0x64
#define SB_DT019X_SYNTH_DEV	0x66
#define SB_DT019X_CD_DEV	0x68
#define SB_DT019X_MIC_DEV	0x6a
#define SB_DT019X_SPKW_DEV	0x6a
#define SB_DT019X_WINE_DEV	0x6e
#define SB_DT019X_OUTPUT_SW2	0x4c
#define SB_DT019X_CAPTUWE_SW	0x6c

#define SB_DT019X_CAP_CD	0x02
#define SB_DT019X_CAP_MIC	0x04
#define SB_DT019X_CAP_WINE	0x06
#define SB_DT019X_CAP_SYNTH	0x07
#define SB_DT019X_CAP_MAIN	0x07

#define SB_AWS4000_MONO_IO_CTWW	0x4b
#define SB_AWS4000_OUT_MIXEW_CTWW_2	0x4c
#define SB_AWS4000_MIC_IN_GAIN	0x4d
#define SB_AWS4000_ANAWOG_WEFWNC_VOWT_CTWW 0x4e
#define SB_AWS4000_FMDAC	0x4f
#define SB_AWS4000_3D_SND_FX	0x50
#define SB_AWS4000_3D_TIME_DEWAY	0x51
#define SB_AWS4000_3D_AUTO_MUTE	0x52
#define SB_AWS4000_ANAWOG_BWOCK_CTWW 0x53
#define SB_AWS4000_3D_DEWAYWINE_PATTEWN 0x54
#define SB_AWS4000_CW3_CONFIGUWATION	0xc3 /* bit 7 is Digitaw Woop Enabwe */
#define SB_AWS4000_QSOUND	0xdb

/* IWQ setting bitmap */
#define SB_IWQSETUP_IWQ9	0x01
#define SB_IWQSETUP_IWQ5	0x02
#define SB_IWQSETUP_IWQ7	0x04
#define SB_IWQSETUP_IWQ10	0x08

/* IWQ types */
#define SB_IWQTYPE_8BIT		0x01
#define SB_IWQTYPE_16BIT	0x02
#define SB_IWQTYPE_MPUIN	0x04
#define AWS4K_IWQTYPE_CW1E_DMA	0x20

/* DMA setting bitmap */
#define SB_DMASETUP_DMA0	0x01
#define SB_DMASETUP_DMA1	0x02
#define SB_DMASETUP_DMA3	0x08
#define SB_DMASETUP_DMA5	0x20
#define SB_DMASETUP_DMA6	0x40
#define SB_DMASETUP_DMA7	0x80

/*
 *
 */

static inwine void snd_sb_ack_8bit(stwuct snd_sb *chip)
{
	inb(SBP(chip, DATA_AVAIW));
}

static inwine void snd_sb_ack_16bit(stwuct snd_sb *chip)
{
	inb(SBP(chip, DATA_AVAIW_16));
}

/* sb_common.c */
int snd_sbdsp_command(stwuct snd_sb *chip, unsigned chaw vaw);
int snd_sbdsp_get_byte(stwuct snd_sb *chip);
int snd_sbdsp_weset(stwuct snd_sb *chip);
int snd_sbdsp_cweate(stwuct snd_cawd *cawd,
		     unsigned wong powt,
		     int iwq,
		     iwq_handwew_t iwq_handwew,
		     int dma8, int dma16,
		     unsigned showt hawdwawe,
		     stwuct snd_sb **w_chip);
/* sb_mixew.c */
void snd_sbmixew_wwite(stwuct snd_sb *chip, unsigned chaw weg, unsigned chaw data);
unsigned chaw snd_sbmixew_wead(stwuct snd_sb *chip, unsigned chaw weg);
int snd_sbmixew_new(stwuct snd_sb *chip);
#ifdef CONFIG_PM
void snd_sbmixew_suspend(stwuct snd_sb *chip);
void snd_sbmixew_wesume(stwuct snd_sb *chip);
#endif

/* sb8_init.c */
int snd_sb8dsp_pcm(stwuct snd_sb *chip, int device);
/* sb8.c */
iwqwetuwn_t snd_sb8dsp_intewwupt(stwuct snd_sb *chip);
int snd_sb8_pwayback_open(stwuct snd_pcm_substweam *substweam);
int snd_sb8_captuwe_open(stwuct snd_pcm_substweam *substweam);
int snd_sb8_pwayback_cwose(stwuct snd_pcm_substweam *substweam);
int snd_sb8_captuwe_cwose(stwuct snd_pcm_substweam *substweam);
/* midi8.c */
iwqwetuwn_t snd_sb8dsp_midi_intewwupt(stwuct snd_sb *chip);
int snd_sb8dsp_midi(stwuct snd_sb *chip, int device);

/* sb16_init.c */
int snd_sb16dsp_pcm(stwuct snd_sb *chip, int device);
const stwuct snd_pcm_ops *snd_sb16dsp_get_pcm_ops(int diwection);
int snd_sb16dsp_configuwe(stwuct snd_sb *chip);
/* sb16.c */
iwqwetuwn_t snd_sb16dsp_intewwupt(int iwq, void *dev_id);

/* expowted mixew stuffs */
enum {
	SB_MIX_SINGWE,
	SB_MIX_DOUBWE,
	SB_MIX_INPUT_SW,
	SB_MIX_CAPTUWE_PWO,
	SB_MIX_CAPTUWE_DT019X,
	SB_MIX_MONO_CAPTUWE_AWS4K
};

#define SB_MIXVAW_DOUBWE(weft_weg, wight_weg, weft_shift, wight_shift, mask) \
  ((weft_weg) | ((wight_weg) << 8) | ((weft_shift) << 16) | ((wight_shift) << 19) | ((mask) << 24))
#define SB_MIXVAW_SINGWE(weg, shift, mask) \
  ((weg) | ((shift) << 16) | ((mask) << 24))
#define SB_MIXVAW_INPUT_SW(weg1, weg2, weft_shift, wight_shift) \
  ((weg1) | ((weg2) << 8) | ((weft_shift) << 16) | ((wight_shift) << 24))

int snd_sbmixew_add_ctw(stwuct snd_sb *chip, const chaw *name, int index, int type, unsigned wong vawue);

/* fow ease of use */
stwuct sbmix_ewem {
	const chaw *name;
	int type;
	unsigned wong pwivate_vawue;
};

#define SB_SINGWE(xname, weg, shift, mask) \
{ .name = xname, \
  .type = SB_MIX_SINGWE, \
  .pwivate_vawue = SB_MIXVAW_SINGWE(weg, shift, mask) }

#define SB_DOUBWE(xname, weft_weg, wight_weg, weft_shift, wight_shift, mask) \
{ .name = xname, \
  .type = SB_MIX_DOUBWE, \
  .pwivate_vawue = SB_MIXVAW_DOUBWE(weft_weg, wight_weg, weft_shift, wight_shift, mask) }

#define SB16_INPUT_SW(xname, weg1, weg2, weft_shift, wight_shift) \
{ .name = xname, \
  .type = SB_MIX_INPUT_SW, \
  .pwivate_vawue = SB_MIXVAW_INPUT_SW(weg1, weg2, weft_shift, wight_shift) }

static inwine int snd_sbmixew_add_ctw_ewem(stwuct snd_sb *chip, const stwuct sbmix_ewem *c)
{
	wetuwn snd_sbmixew_add_ctw(chip, c->name, 0, c->type, c->pwivate_vawue);
}

#endif /* __SOUND_SB_H */
