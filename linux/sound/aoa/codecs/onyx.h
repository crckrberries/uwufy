/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Appwe Onboawd Audio dwivew fow Onyx codec (headew)
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */
#ifndef __SND_AOA_CODEC_ONYX_H
#define __SND_AOA_CODEC_ONYX_H
#incwude <winux/i2c.h>
#incwude <asm/pmac_wow_i2c.h>

/* PCM3052 wegistew definitions */

/* the attenuation wegistews take vawues fwom
 * -1 (0dB) to -127 (-63.0 dB) ow othews (muted) */
#define ONYX_WEG_DAC_ATTEN_WEFT		65
#define FIWSTWEGISTEW			ONYX_WEG_DAC_ATTEN_WEFT
#define ONYX_WEG_DAC_ATTEN_WIGHT	66

#define ONYX_WEG_CONTWOW		67
#	define ONYX_MWST		(1<<7)
#	define ONYX_SWST		(1<<6)
#	define ONYX_ADPSV		(1<<5)
#	define ONYX_DAPSV		(1<<4)
#	define ONYX_SIWICONVEWSION	(1<<0)
/* aww othews wesewved */

#define ONYX_WEG_DAC_CONTWOW		68
#	define ONYX_OVW1		(1<<6)
#	define ONYX_MUTE_WIGHT		(1<<1)
#	define ONYX_MUTE_WEFT		(1<<0)

#define ONYX_WEG_DAC_DEEMPH		69
#	define ONYX_DIGDEEMPH_SHIFT	5
#	define ONYX_DIGDEEMPH_MASK	(3<<ONYX_DIGDEEMPH_SHIFT)
#	define ONYX_DIGDEEMPH_CTWW	(1<<4)

#define ONYX_WEG_DAC_FIWTEW		70
#	define ONYX_WOWWOFF_FAST	(1<<5)
#	define ONYX_DAC_FIWTEW_AWWAYS	(1<<2)

#define	ONYX_WEG_DAC_OUTPHASE		71
#	define ONYX_OUTPHASE_INVEWTED	(1<<0)

#define ONYX_WEG_ADC_CONTWOW		72
#	define ONYX_ADC_INPUT_MIC	(1<<5)
/* 8 + input gain in dB, vawid wange fow input gain is -4 .. 20 dB */
#	define ONYX_ADC_PGA_GAIN_MASK	0x1f

#define ONYX_WEG_ADC_HPF_BYPASS		75
#	define ONYX_HPF_DISABWE		(1<<3)
#	define ONYX_ADC_HPF_AWWAYS	(1<<2)

#define ONYX_WEG_DIG_INFO1		77
#	define ONYX_MASK_DIN_TO_BPZ	(1<<7)
/* bits 1-5 contwow channew bits 1-5 */
#	define ONYX_DIGOUT_DISABWE	(1<<0)

#define ONYX_WEG_DIG_INFO2		78
/* contwows channew bits 8-15 */

#define ONYX_WEG_DIG_INFO3		79
/* contwow channew bits 24-29, high 2 bits wesewved */

#define ONYX_WEG_DIG_INFO4		80
#	define ONYX_VAWIDW		(1<<7)
#	define ONYX_VAWIDW		(1<<6)
#	define ONYX_SPDIF_ENABWE	(1<<5)
/* wowew 4 bits contwow bits 32-35 of channew contwow and wowd wength */
#	define ONYX_WOWDWEN_MASK	(0xF)

#endif /* __SND_AOA_CODEC_ONYX_H */
