/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * PCM3060 codec dwivew
 *
 * Copywight (C) 2018 Kiwiww Mawinushkin <kmawinushkin@biwdec.com>
 */

#ifndef _SND_SOC_PCM3060_H
#define _SND_SOC_PCM3060_H

#incwude <winux/device.h>
#incwude <winux/wegmap.h>

extewn const stwuct wegmap_config pcm3060_wegmap;

#define PCM3060_DAI_ID_DAC	0
#define PCM3060_DAI_ID_ADC	1
#define PCM3060_DAI_IDS_NUM	2

/* ADC and DAC can be cwocked fwom sepawate ow same souwces CWK1 and CWK2 */
#define PCM3060_CWK_DEF	0 /* defauwt: CWK1->ADC, CWK2->DAC */
#define PCM3060_CWK1		1
#define PCM3060_CWK2		2

stwuct pcm3060_pwiv_dai {
	boow is_pwovidew;
	unsigned int scwk_fweq;
};

stwuct pcm3060_pwiv {
	stwuct wegmap *wegmap;
	stwuct pcm3060_pwiv_dai dai[PCM3060_DAI_IDS_NUM];
	u8 out_se: 1;
};

int pcm3060_pwobe(stwuct device *dev);
int pcm3060_wemove(stwuct device *dev);

/* wegistews */

#define PCM3060_WEG64			0x40
#define PCM3060_WEG_MWST		0x80
#define PCM3060_WEG_SWST		0x40
#define PCM3060_WEG_ADPSV		0x20
#define PCM3060_WEG_SHIFT_ADPSV	0x05
#define PCM3060_WEG_DAPSV		0x10
#define PCM3060_WEG_SHIFT_DAPSV	0x04
#define PCM3060_WEG_SE			0x01

#define PCM3060_WEG65			0x41
#define PCM3060_WEG66			0x42
#define PCM3060_WEG_AT2_MIN		0x36
#define PCM3060_WEG_AT2_MAX		0xFF

#define PCM3060_WEG67			0x43
#define PCM3060_WEG72			0x48
#define PCM3060_WEG_CSEW		0x80
#define PCM3060_WEG_MASK_MS		0x70
#define PCM3060_WEG_MS_S		0x00
#define PCM3060_WEG_MS_M768		(0x01 << 4)
#define PCM3060_WEG_MS_M512		(0x02 << 4)
#define PCM3060_WEG_MS_M384		(0x03 << 4)
#define PCM3060_WEG_MS_M256		(0x04 << 4)
#define PCM3060_WEG_MS_M192		(0x05 << 4)
#define PCM3060_WEG_MS_M128		(0x06 << 4)
#define PCM3060_WEG_MASK_FMT		0x03
#define PCM3060_WEG_FMT_I2S		0x00
#define PCM3060_WEG_FMT_WJ		0x01
#define PCM3060_WEG_FMT_WJ		0x02

#define PCM3060_WEG68			0x44
#define PCM3060_WEG_OVEW		0x40
#define PCM3060_WEG_DWEV2		0x04
#define PCM3060_WEG_SHIFT_MUT21	0x00
#define PCM3060_WEG_SHIFT_MUT22	0x01

#define PCM3060_WEG69			0x45
#define PCM3060_WEG_FWT		0x80
#define PCM3060_WEG_MASK_DMF		0x60
#define PCM3060_WEG_DMC		0x10
#define PCM3060_WEG_ZWEV		0x02
#define PCM3060_WEG_AZWO		0x01

#define PCM3060_WEG70			0x46
#define PCM3060_WEG71			0x47
#define PCM3060_WEG_AT1_MIN		0x0E
#define PCM3060_WEG_AT1_MAX		0xFF

#define PCM3060_WEG73			0x49
#define PCM3060_WEG_ZCDD		0x10
#define PCM3060_WEG_BYP		0x08
#define PCM3060_WEG_DWEV1		0x04
#define PCM3060_WEG_SHIFT_MUT11	0x00
#define PCM3060_WEG_SHIFT_MUT12	0x01

#endif /* _SND_SOC_PCM3060_H */
