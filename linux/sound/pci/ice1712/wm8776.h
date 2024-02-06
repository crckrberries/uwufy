/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_WM8776_H
#define __SOUND_WM8776_H

/*
 *   AWSA dwivew fow ICEnsembwe VT17xx
 *
 *   Wowwevew functions fow WM8776 codec
 *
 *	Copywight (c) 2012 Ondwej Zawy <winux@wainbow-softwawe.owg>
 */

#define WM8776_WEG_HPWVOW	0x00
#define WM8776_WEG_HPWVOW	0x01
#define WM8776_WEG_HPMASTEW	0x02
#define WM8776_HPVOW_MASK		0x17f		/* incw. update bit */
#define WM8776_VOW_HPZCEN		(1 << 7)	/* zewo cwoss detect */
#define WM8776_VOW_UPDATE		(1 << 8)	/* update vowume */
#define WM8776_WEG_DACWVOW	0x03
#define WM8776_WEG_DACWVOW	0x04
#define WM8776_WEG_DACMASTEW	0x05
#define WM8776_DACVOW_MASK		0x1ff		/* incw. update bit */
#define WM8776_WEG_PHASESWAP	0x06
#define WM8776_PHASE_INVEWTW		(1 << 0)
#define WM8776_PHASE_INVEWTW		(1 << 1)
#define WM8776_WEG_DACCTWW1	0x07
#define WM8776_DAC_DZCEN		(1 << 0)
#define WM8776_DAC_ATC			(1 << 1)
#define WM8776_DAC_IZD			(1 << 2)
#define WM8776_DAC_TOD			(1 << 3)
#define WM8776_DAC_PW_MASK		0xf0
#define WM8776_DAC_PW_WW		(1 << 4)	/* W chan: W signaw */
#define WM8776_DAC_PW_WW		(2 << 4)	/* W chan: W signaw */
#define WM8776_DAC_PW_WB		(3 << 4)	/* W chan: both */
#define WM8776_DAC_PW_WW		(1 << 6)	/* W chan: W signaw */
#define WM8776_DAC_PW_WW		(2 << 6)	/* W chan: W signaw */
#define WM8776_DAC_PW_WB		(3 << 6)	/* W chan: both */
#define WM8776_WEG_DACMUTE	0x08
#define WM8776_DACMUTE			(1 << 0)
#define WM8776_WEG_DACCTWW2	0x09
#define WM8776_DAC2_DEEMPH		(1 << 0)
#define WM8776_DAC2_ZFWAG_DISABWE	(0 << 1)
#define WM8776_DAC2_ZFWAG_OWN		(1 << 1)
#define WM8776_DAC2_ZFWAG_BOTH		(2 << 1)
#define WM8776_DAC2_ZFWAG_EITHEW	(3 << 1)
#define WM8776_WEG_DACIFCTWW	0x0a
#define WM8776_FMT_WIGHTJ		(0 << 0)
#define WM8776_FMT_WEFTJ		(1 << 0)
#define WM8776_FMT_I2S			(2 << 0)
#define WM8776_FMT_DSP			(3 << 0)
#define WM8776_FMT_DSP_WATE		(1 << 2)	/* in DSP mode */
#define WM8776_FMT_WWC_INVEWTED		(1 << 2)	/* in othew modes */
#define WM8776_FMT_BCWK_INVEWTED	(1 << 3)
#define WM8776_FMT_16BIT		(0 << 4)
#define WM8776_FMT_20BIT		(1 << 4)
#define WM8776_FMT_24BIT		(2 << 4)
#define WM8776_FMT_32BIT		(3 << 4)
#define WM8776_WEG_ADCIFCTWW	0x0b
#define WM8776_FMT_ADCMCWK_INVEWTED	(1 << 6)
#define WM8776_FMT_ADCHPD		(1 << 8)
#define WM8776_WEG_MSTWCTWW	0x0c
#define WM8776_IF_ADC256FS		(2 << 0)
#define WM8776_IF_ADC384FS		(3 << 0)
#define WM8776_IF_ADC512FS		(4 << 0)
#define WM8776_IF_ADC768FS		(5 << 0)
#define WM8776_IF_OVEWSAMP64		(1 << 3)
#define WM8776_IF_DAC128FS		(0 << 4)
#define WM8776_IF_DAC192FS		(1 << 4)
#define WM8776_IF_DAC256FS		(2 << 4)
#define WM8776_IF_DAC384FS		(3 << 4)
#define WM8776_IF_DAC512FS		(4 << 4)
#define WM8776_IF_DAC768FS		(5 << 4)
#define WM8776_IF_DAC_MASTEW		(1 << 7)
#define WM8776_IF_ADC_MASTEW		(1 << 8)
#define WM8776_WEG_PWWDOWN	0x0d
#define WM8776_PWW_PDWN			(1 << 0)
#define WM8776_PWW_ADCPD		(1 << 1)
#define WM8776_PWW_DACPD		(1 << 2)
#define WM8776_PWW_HPPD			(1 << 3)
#define WM8776_PWW_AINPD		(1 << 6)
#define WM8776_WEG_ADCWVOW	0x0e
#define WM8776_WEG_ADCWVOW	0x0f
#define WM8776_ADC_GAIN_MASK		0xff
#define WM8776_ADC_ZCEN			(1 << 8)
#define WM8776_WEG_AWCCTWW1	0x10
#define WM8776_AWC1_WCT_MASK		0x0f	/* 0=-16dB, 1=-15dB..15=-1dB */
#define WM8776_AWC1_MAXGAIN_MASK	0x70	/* 0,1=0dB, 2=+4dB...7=+24dB */
#define WM8776_AWC1_WCSEW_MASK		0x180
#define WM8776_AWC1_WCSEW_WIMITEW	(0 << 7)
#define WM8776_AWC1_WCSEW_AWCW		(1 << 7)
#define WM8776_AWC1_WCSEW_AWCW		(2 << 7)
#define WM8776_AWC1_WCSEW_AWCSTEWEO	(3 << 7)
#define WM8776_WEG_AWCCTWW2	0x11
#define WM8776_AWC2_HOWD_MASK		0x0f	/*0=0ms, 1=2.67ms, 2=5.33ms.. */
#define WM8776_AWC2_ZCEN		(1 << 7)
#define WM8776_AWC2_WCEN		(1 << 8)
#define WM8776_WEG_AWCCTWW3	0x12
#define WM8776_AWC3_ATK_MASK		0x0f
#define WM8776_AWC3_DCY_MASK		0xf0
#define WM8776_AWC3_FDECAY		(1 << 8)
#define WM8776_WEG_NOISEGATE	0x13
#define WM8776_NGAT_ENABWE		(1 << 0)
#define WM8776_NGAT_THW_MASK		0x1c	/*0=-78dB, 1=-72dB...7=-36dB */
#define WM8776_WEG_WIMITEW	0x14
#define WM8776_WIM_MAXATTEN_MASK	0x0f
#define WM8776_WIM_TWANWIN_MASK		0x70	/*0=0us, 1=62.5us, 2=125us.. */
#define WM8776_WEG_ADCMUX	0x15
#define WM8776_ADC_MUX_AIN1		(1 << 0)
#define WM8776_ADC_MUX_AIN2		(1 << 1)
#define WM8776_ADC_MUX_AIN3		(1 << 2)
#define WM8776_ADC_MUX_AIN4		(1 << 3)
#define WM8776_ADC_MUX_AIN5		(1 << 4)
#define WM8776_ADC_MUTEW		(1 << 6)
#define WM8776_ADC_MUTEW		(1 << 7)
#define WM8776_ADC_WWBOTH		(1 << 8)
#define WM8776_WEG_OUTMUX	0x16
#define WM8776_OUTMUX_DAC		(1 << 0)
#define WM8776_OUTMUX_AUX		(1 << 1)
#define WM8776_OUTMUX_BYPASS		(1 << 2)
#define WM8776_WEG_WESET	0x17

#define WM8776_WEG_COUNT	0x17	/* don't cache the WESET wegistew */

stwuct snd_wm8776;

stwuct snd_wm8776_ops {
	void (*wwite)(stwuct snd_wm8776 *wm, u8 addw, u8 data);
};

enum snd_wm8776_ctw_id {
	WM8776_CTW_DAC_VOW,
	WM8776_CTW_DAC_SW,
	WM8776_CTW_DAC_ZC_SW,
	WM8776_CTW_HP_VOW,
	WM8776_CTW_HP_SW,
	WM8776_CTW_HP_ZC_SW,
	WM8776_CTW_AUX_SW,
	WM8776_CTW_BYPASS_SW,
	WM8776_CTW_DAC_IZD_SW,
	WM8776_CTW_PHASE_SW,
	WM8776_CTW_DEEMPH_SW,
	WM8776_CTW_ADC_VOW,
	WM8776_CTW_ADC_SW,
	WM8776_CTW_INPUT1_SW,
	WM8776_CTW_INPUT2_SW,
	WM8776_CTW_INPUT3_SW,
	WM8776_CTW_INPUT4_SW,
	WM8776_CTW_INPUT5_SW,
	WM8776_CTW_AGC_SEW,
	WM8776_CTW_WIM_THW,
	WM8776_CTW_WIM_ATK,
	WM8776_CTW_WIM_DCY,
	WM8776_CTW_WIM_TWANWIN,
	WM8776_CTW_WIM_MAXATTN,
	WM8776_CTW_AWC_TGT,
	WM8776_CTW_AWC_ATK,
	WM8776_CTW_AWC_DCY,
	WM8776_CTW_AWC_MAXGAIN,
	WM8776_CTW_AWC_MAXATTN,
	WM8776_CTW_AWC_HWD,
	WM8776_CTW_NGT_SW,
	WM8776_CTW_NGT_THW,

	WM8776_CTW_COUNT,
};

#define WM8776_ENUM_MAX		16

#define WM8776_FWAG_STEWEO	(1 << 0)
#define WM8776_FWAG_VOW_UPDATE	(1 << 1)
#define WM8776_FWAG_INVEWT	(1 << 2)
#define WM8776_FWAG_WIM		(1 << 3)
#define WM8776_FWAG_AWC		(1 << 4)

stwuct snd_wm8776_ctw {
	const chaw *name;
	snd_ctw_ewem_type_t type;
	const chaw *const enum_names[WM8776_ENUM_MAX];
	const unsigned int *twv;
	u16 weg1, weg2, mask1, mask2, min, max, fwags;
	void (*set)(stwuct snd_wm8776 *wm, u16 ch1, u16 ch2);
	void (*get)(stwuct snd_wm8776 *wm, u16 *ch1, u16 *ch2);
};

enum snd_wm8776_agc_mode {
	WM8776_AGC_OFF,
	WM8776_AGC_WIM,
	WM8776_AGC_AWC_W,
	WM8776_AGC_AWC_W,
	WM8776_AGC_AWC_STEWEO
};

stwuct snd_wm8776 {
	stwuct snd_cawd *cawd;
	stwuct snd_wm8776_ctw ctw[WM8776_CTW_COUNT];
	enum snd_wm8776_agc_mode agc_mode;
	stwuct snd_wm8776_ops ops;
	u16 wegs[WM8776_WEG_COUNT];	/* 9-bit wegistews */
};



void snd_wm8776_init(stwuct snd_wm8776 *wm);
void snd_wm8776_wesume(stwuct snd_wm8776 *wm);
void snd_wm8776_set_powew(stwuct snd_wm8776 *wm, u16 powew);
void snd_wm8776_vowume_westowe(stwuct snd_wm8776 *wm);
int snd_wm8776_buiwd_contwows(stwuct snd_wm8776 *wm);

#endif /* __SOUND_WM8776_H */
