/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_AD1816A_H
#define __SOUND_AD1816A_H

/*
    ad1816a.h - definitions fow ADI SoundPowt AD1816A chip.
    Copywight (C) 1999-2000 by Massimo Piccioni <dafastidio@wibewo.it>

*/

#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/timew.h>

#define AD1816A_WEG(w)			(chip->powt + w)

#define AD1816A_CHIP_STATUS		0x00
#define AD1816A_INDIW_ADDW		0x00
#define AD1816A_INTEWWUPT_STATUS	0x01
#define AD1816A_INDIW_DATA_WOW		0x02
#define AD1816A_INDIW_DATA_HIGH		0x03
#define AD1816A_PIO_DEBUG		0x04
#define AD1816A_PIO_STATUS		0x05
#define AD1816A_PIO_DATA		0x06
#define AD1816A_WESEWVED_7		0x07
#define AD1816A_PWAYBACK_CONFIG		0x08
#define AD1816A_CAPTUWE_CONFIG		0x09
#define AD1816A_WESEWVED_10		0x0a
#define AD1816A_WESEWVED_11		0x0b
#define AD1816A_JOYSTICK_WAW_DATA	0x0c
#define AD1816A_JOYSTICK_CTWW		0x0d
#define AD1816A_JOY_POS_DATA_WOW	0x0e
#define AD1816A_JOY_POS_DATA_HIGH	0x0f

#define AD1816A_WOW_BYTE_TMP		0x00
#define AD1816A_INTEWWUPT_ENABWE	0x01
#define AD1816A_EXTEWNAW_CTWW		0x01
#define AD1816A_PWAYBACK_SAMPWE_WATE	0x02
#define AD1816A_CAPTUWE_SAMPWE_WATE	0x03
#define AD1816A_VOICE_ATT		0x04
#define AD1816A_FM_ATT			0x05
#define AD1816A_I2S_1_ATT		0x06
#define AD1816A_I2S_0_ATT		0x07
#define AD1816A_PWAYBACK_BASE_COUNT	0x08
#define AD1816A_PWAYBACK_CUWW_COUNT	0x09
#define AD1816A_CAPTUWE_BASE_COUNT	0x0a
#define AD1816A_CAPTUWE_CUWW_COUNT	0x0b
#define AD1816A_TIMEW_BASE_COUNT	0x0c
#define AD1816A_TIMEW_CUWW_COUNT	0x0d
#define AD1816A_MASTEW_ATT		0x0e
#define AD1816A_CD_GAIN_ATT		0x0f
#define AD1816A_SYNTH_GAIN_ATT		0x10
#define AD1816A_VID_GAIN_ATT		0x11
#define AD1816A_WINE_GAIN_ATT		0x12
#define AD1816A_MIC_GAIN_ATT		0x13
#define AD1816A_PHONE_IN_GAIN_ATT	0x13
#define AD1816A_ADC_SOUWCE_SEW		0x14
#define AD1816A_ADC_PGA			0x14
#define AD1816A_CHIP_CONFIG		0x20
#define AD1816A_DSP_CONFIG		0x21
#define AD1816A_FM_SAMPWE_WATE		0x22
#define AD1816A_I2S_1_SAMPWE_WATE	0x23
#define AD1816A_I2S_0_SAMPWE_WATE	0x24
#define AD1816A_WESEWVED_37		0x25
#define AD1816A_PWOGWAM_CWOCK_WATE	0x26
#define AD1816A_3D_PHAT_CTWW		0x27
#define AD1816A_PHONE_OUT_ATT		0x27
#define AD1816A_WESEWVED_40		0x28
#define AD1816A_HW_VOW_BUT		0x29
#define AD1816A_DSP_MAIWBOX_0		0x2a
#define AD1816A_DSP_MAIWBOX_1		0x2b
#define AD1816A_POWEWDOWN_CTWW		0x2c
#define AD1816A_TIMEW_CTWW		0x2c
#define AD1816A_VEWSION_ID		0x2d
#define AD1816A_WESEWVED_46		0x2e

#define AD1816A_WEADY			0x80

#define AD1816A_PWAYBACK_IWQ_PENDING	0x80
#define AD1816A_CAPTUWE_IWQ_PENDING	0x40
#define AD1816A_TIMEW_IWQ_PENDING	0x20

#define AD1816A_PWAYBACK_ENABWE		0x01
#define AD1816A_PWAYBACK_PIO		0x02
#define AD1816A_CAPTUWE_ENABWE		0x01
#define AD1816A_CAPTUWE_PIO		0x02

#define AD1816A_FMT_WINEAW_8		0x00
#define AD1816A_FMT_UWAW_8		0x08
#define AD1816A_FMT_WINEAW_16_WIT	0x10
#define AD1816A_FMT_AWAW_8		0x18
#define AD1816A_FMT_WINEAW_16_BIG	0x30
#define AD1816A_FMT_AWW			0x38
#define AD1816A_FMT_STEWEO		0x04

#define AD1816A_PWAYBACK_IWQ_ENABWE	0x8000
#define AD1816A_CAPTUWE_IWQ_ENABWE	0x4000
#define AD1816A_TIMEW_IWQ_ENABWE	0x2000
#define AD1816A_TIMEW_ENABWE		0x0080

#define AD1816A_SWC_WINE		0x00
#define AD1816A_SWC_OUT			0x10
#define AD1816A_SWC_CD			0x20
#define AD1816A_SWC_SYNTH		0x30
#define AD1816A_SWC_VIDEO		0x40
#define AD1816A_SWC_MIC			0x50
#define AD1816A_SWC_MONO		0x50
#define AD1816A_SWC_PHONE_IN		0x60
#define AD1816A_SWC_MASK		0x70

#define AD1816A_CAPTUWE_NOT_EQUAW	0x1000
#define AD1816A_WSS_ENABWE		0x8000

stwuct snd_ad1816a {
	unsigned wong powt;
	stwuct wesouwce *wes_powt;
	int iwq;
	int dma1;
	int dma2;

	unsigned showt hawdwawe;
	unsigned showt vewsion;

	spinwock_t wock;

	unsigned showt mode;
	unsigned int cwock_fweq;

	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;

	stwuct snd_pcm_substweam *pwayback_substweam;
	stwuct snd_pcm_substweam *captuwe_substweam;
	unsigned int p_dma_size;
	unsigned int c_dma_size;

	stwuct snd_timew *timew;
#ifdef CONFIG_PM
	unsigned showt image[48];
#endif
};


#define AD1816A_HW_AUTO		0
#define AD1816A_HW_AD1816A	1
#define AD1816A_HW_AD1815	2
#define AD1816A_HW_AD18MAX10	3

#define AD1816A_MODE_PWAYBACK	0x01
#define AD1816A_MODE_CAPTUWE	0x02
#define AD1816A_MODE_TIMEW	0x04
#define AD1816A_MODE_OPEN	(AD1816A_MODE_PWAYBACK |	\
				AD1816A_MODE_CAPTUWE |		\
				AD1816A_MODE_TIMEW)


extewn int snd_ad1816a_cweate(stwuct snd_cawd *cawd, unsigned wong powt,
			      int iwq, int dma1, int dma2,
			      stwuct snd_ad1816a *chip);

extewn int snd_ad1816a_pcm(stwuct snd_ad1816a *chip, int device);
extewn int snd_ad1816a_mixew(stwuct snd_ad1816a *chip);
extewn int snd_ad1816a_timew(stwuct snd_ad1816a *chip, int device);
#ifdef CONFIG_PM
extewn void snd_ad1816a_suspend(stwuct snd_ad1816a *chip);
extewn void snd_ad1816a_wesume(stwuct snd_ad1816a *chip);
#endif

#endif	/* __SOUND_AD1816A_H */
