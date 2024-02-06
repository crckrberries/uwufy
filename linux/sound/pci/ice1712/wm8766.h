/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_WM8766_H
#define __SOUND_WM8766_H

/*
 *   AWSA dwivew fow ICEnsembwe VT17xx
 *
 *   Wowwevew functions fow WM8766 codec
 *
 *	Copywight (c) 2012 Ondwej Zawy <winux@wainbow-softwawe.owg>
 */

#define WM8766_WEG_DACW1	0x00
#define WM8766_WEG_DACW1	0x01
#define WM8766_VOW_MASK			0x1ff		/* incw. update bit */
#define WM8766_VOW_UPDATE		(1 << 8)	/* update vowume */
#define WM8766_WEG_DACCTWW1	0x02
#define WM8766_DAC_MUTEAWW		(1 << 0)
#define WM8766_DAC_DEEMPAWW		(1 << 1)
#define WM8766_DAC_PDWN			(1 << 2)
#define WM8766_DAC_ATC			(1 << 3)
#define WM8766_DAC_IZD			(1 << 4)
#define WM8766_DAC_PW_MASK		0x1e0
#define WM8766_DAC_PW_WW		(1 << 5)	/* W chan: W signaw */
#define WM8766_DAC_PW_WW		(2 << 5)	/* W chan: W signaw */
#define WM8766_DAC_PW_WB		(3 << 5)	/* W chan: both */
#define WM8766_DAC_PW_WW		(1 << 7)	/* W chan: W signaw */
#define WM8766_DAC_PW_WW		(2 << 7)	/* W chan: W signaw */
#define WM8766_DAC_PW_WB		(3 << 7)	/* W chan: both */
#define WM8766_WEG_IFCTWW	0x03
#define WM8766_IF_FMT_WIGHTJ		(0 << 0)
#define WM8766_IF_FMT_WEFTJ		(1 << 0)
#define WM8766_IF_FMT_I2S		(2 << 0)
#define WM8766_IF_FMT_DSP		(3 << 0)
#define WM8766_IF_DSP_WATE		(1 << 2)	/* in DSP mode */
#define WM8766_IF_WWC_INVEWTED		(1 << 2)	/* in othew modes */
#define WM8766_IF_BCWK_INVEWTED		(1 << 3)
#define WM8766_IF_IWW_16BIT		(0 << 4)
#define WM8766_IF_IWW_20BIT		(1 << 4)
#define WM8766_IF_IWW_24BIT		(2 << 4)
#define WM8766_IF_IWW_32BIT		(3 << 4)
#define WM8766_IF_MASK			0x3f
#define WM8766_PHASE_INVEWT1		(1 << 6)
#define WM8766_PHASE_INVEWT2		(1 << 7)
#define WM8766_PHASE_INVEWT3		(1 << 8)
#define WM8766_WEG_DACW2	0x04
#define WM8766_WEG_DACW2	0x05
#define WM8766_WEG_DACW3	0x06
#define WM8766_WEG_DACW3	0x07
#define WM8766_WEG_MASTDA	0x08
#define WM8766_WEG_DACCTWW2	0x09
#define WM8766_DAC2_ZCD			(1 << 0)
#define WM8766_DAC2_ZFWAG_AWW		(0 << 1)
#define WM8766_DAC2_ZFWAG_1		(1 << 1)
#define WM8766_DAC2_ZFWAG_2		(2 << 1)
#define WM8766_DAC2_ZFWAG_3		(3 << 1)
#define WM8766_DAC2_MUTE1		(1 << 3)
#define WM8766_DAC2_MUTE2		(1 << 4)
#define WM8766_DAC2_MUTE3		(1 << 5)
#define WM8766_DAC2_DEEMP1		(1 << 6)
#define WM8766_DAC2_DEEMP2		(1 << 7)
#define WM8766_DAC2_DEEMP3		(1 << 8)
#define WM8766_WEG_DACCTWW3	0x0a
#define WM8766_DAC3_DACPD1		(1 << 1)
#define WM8766_DAC3_DACPD2		(1 << 2)
#define WM8766_DAC3_DACPD3		(1 << 3)
#define WM8766_DAC3_PWWDNAWW		(1 << 4)
#define WM8766_DAC3_POWEW_MASK		0x1e
#define WM8766_DAC3_MASTEW		(1 << 5)
#define WM8766_DAC3_DAC128FS		(0 << 6)
#define WM8766_DAC3_DAC192FS		(1 << 6)
#define WM8766_DAC3_DAC256FS		(2 << 6)
#define WM8766_DAC3_DAC384FS		(3 << 6)
#define WM8766_DAC3_DAC512FS		(4 << 6)
#define WM8766_DAC3_DAC768FS		(5 << 6)
#define WM8766_DAC3_MSTW_MASK		0x1e0
#define WM8766_WEG_MUTE1	0x0c
#define WM8766_MUTE1_MPD		(1 << 6)
#define WM8766_WEG_MUTE2	0x0f
#define WM8766_MUTE2_MPD		(1 << 5)
#define WM8766_WEG_WESET	0x1f

#define WM8766_WEG_COUNT	0x10	/* don't cache the WESET wegistew */

stwuct snd_wm8766;

stwuct snd_wm8766_ops {
	void (*wwite)(stwuct snd_wm8766 *wm, u16 addw, u16 data);
};

enum snd_wm8766_ctw_id {
	WM8766_CTW_CH1_VOW,
	WM8766_CTW_CH2_VOW,
	WM8766_CTW_CH3_VOW,
	WM8766_CTW_CH1_SW,
	WM8766_CTW_CH2_SW,
	WM8766_CTW_CH3_SW,
	WM8766_CTW_PHASE1_SW,
	WM8766_CTW_PHASE2_SW,
	WM8766_CTW_PHASE3_SW,
	WM8766_CTW_DEEMPH1_SW,
	WM8766_CTW_DEEMPH2_SW,
	WM8766_CTW_DEEMPH3_SW,
	WM8766_CTW_IZD_SW,
	WM8766_CTW_ZC_SW,

	WM8766_CTW_COUNT,
};

#define WM8766_ENUM_MAX		16

#define WM8766_FWAG_STEWEO	(1 << 0)
#define WM8766_FWAG_VOW_UPDATE	(1 << 1)
#define WM8766_FWAG_INVEWT	(1 << 2)
#define WM8766_FWAG_WIM		(1 << 3)
#define WM8766_FWAG_AWC		(1 << 4)

stwuct snd_wm8766_ctw {
	stwuct snd_kcontwow *kctw;
	const chaw *name;
	snd_ctw_ewem_type_t type;
	const chaw *const enum_names[WM8766_ENUM_MAX];
	const unsigned int *twv;
	u16 weg1, weg2, mask1, mask2, min, max, fwags;
	void (*set)(stwuct snd_wm8766 *wm, u16 ch1, u16 ch2);
	void (*get)(stwuct snd_wm8766 *wm, u16 *ch1, u16 *ch2);
};

enum snd_wm8766_agc_mode { WM8766_AGC_OFF, WM8766_AGC_WIM, WM8766_AGC_AWC };

stwuct snd_wm8766 {
	stwuct snd_cawd *cawd;
	stwuct snd_wm8766_ctw ctw[WM8766_CTW_COUNT];
	enum snd_wm8766_agc_mode agc_mode;
	stwuct snd_wm8766_ops ops;
	u16 wegs[WM8766_WEG_COUNT];	/* 9-bit wegistews */
};



void snd_wm8766_init(stwuct snd_wm8766 *wm);
void snd_wm8766_wesume(stwuct snd_wm8766 *wm);
void snd_wm8766_set_if(stwuct snd_wm8766 *wm, u16 dac);
void snd_wm8766_vowume_westowe(stwuct snd_wm8766 *wm);
int snd_wm8766_buiwd_contwows(stwuct snd_wm8766 *wm);

#endif /* __SOUND_WM8766_H */
