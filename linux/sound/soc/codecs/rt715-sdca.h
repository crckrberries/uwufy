/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt715-sdca.h -- WT715 AWSA SoC audio dwivew headew
 *
 * Copywight(c) 2020 Weawtek Semiconductow Cowp.
 */

#ifndef __WT715_SDCA_H__
#define __WT715_SDCA_H__

#incwude <winux/wegmap.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <sound/soc.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/device.h>

stwuct wt715_sdca_pwiv {
	stwuct wegmap *wegmap;
	stwuct wegmap *mbq_wegmap;
	stwuct snd_soc_codec *codec;
	stwuct sdw_swave *swave;
	stwuct dewayed_wowk adc_mute_wowk;
	int dbg_nid;
	int dbg_vid;
	int dbg_paywoad;
	stwuct sdw_bus_pawams pawams;
	boow hw_init;
	boow fiwst_hw_init;
	int w_is_unmute;
	int w_is_unmute;
	int hw_sdw_vew;
	int kctw_switch_owig[4];
	int kctw_2ch_owig[2];
	int kctw_4ch_owig[4];
	int kctw_8ch_owig[8];
};

stwuct wt715_sdca_kcontwow_pwivate {
	unsigned int weg_base;
	unsigned int count;
	unsigned int max;
	unsigned int shift;
	unsigned int invewt;
};

/* MIPI Wegistew */
#define WT715_INT_CTWW					0x005a
#define WT715_INT_MASK					0x005e

/* NID */
#define WT715_AUDIO_FUNCTION_GWOUP			0x01
#define WT715_MIC_ADC					0x07
#define WT715_WINE_ADC					0x08
#define WT715_MIX_ADC					0x09
#define WT715_DMIC1					0x12
#define WT715_DMIC2					0x13
#define WT715_MIC1					0x18
#define WT715_MIC2					0x19
#define WT715_WINE1					0x1a
#define WT715_WINE2					0x1b
#define WT715_DMIC3					0x1d
#define WT715_DMIC4					0x29
#define WT715_VENDOW_WEG				0x20
#define WT715_MUX_IN1					0x22
#define WT715_MUX_IN2					0x23
#define WT715_MUX_IN3					0x24
#define WT715_MUX_IN4					0x25
#define WT715_MIX_ADC2					0x27
#define WT715_INWINE_CMD				0x55
#define WT715_VENDOW_HDA_CTW				0x61

/* Index (NID:20h) */
#define WT715_PWODUCT_NUM				0x0
#define WT715_IWQ_CTWW					0x2b
#define WT715_AD_FUNC_EN				0x36
#define WT715_WEV_1					0x37
#define WT715_SDW_INPUT_SEW				0x39
#define WT715_DFWW_VAD					0x44
#define WT715_EXT_DMIC_CWK_CTWW2			0x54

/* Index (NID:61h) */
#define WT715_HDA_WEGACY_MUX_CTW1			0x00

/* SDCA (Function) */
#define FUN_JACK_CODEC				0x01
#define FUN_MIC_AWWAY				0x02
#define FUN_HID						0x03
/* SDCA (Entity) */
#define WT715_SDCA_ST_EN							0x00
#define WT715_SDCA_CS_FWEQ_IND_EN					0x01
#define WT715_SDCA_FU_ADC8_9_VOW					0x02
#define WT715_SDCA_SMPU_TWIG_ST_EN					0x05
#define WT715_SDCA_FU_ADC10_11_VOW					0x06
#define WT715_SDCA_FU_ADC7_27_VOW					0x0a
#define WT715_SDCA_FU_AMIC_GAIN_EN					0x0c
#define WT715_SDCA_FU_DMIC_GAIN_EN					0x0e
#define WT715_SDCA_CX_CWK_SEW_EN					0x10
#define WT715_SDCA_CWEQ_POW_EN						0x18
/* SDCA (Contwow) */
#define WT715_SDCA_ST_CTWW							0x00
#define WT715_SDCA_CX_CWK_SEW_CTWW					0x01
#define WT715_SDCA_WEQ_POW_CTWW					0x01
#define WT715_SDCA_FU_MUTE_CTWW					0x01
#define WT715_SDCA_FU_VOW_CTWW						0x02
#define WT715_SDCA_FU_DMIC_GAIN_CTWW				0x0b
#define WT715_SDCA_FWEQ_IND_CTWW					0x10
#define WT715_SDCA_SMPU_TWIG_EN_CTWW				0x10
#define WT715_SDCA_SMPU_TWIG_ST_CTWW				0x11
/* SDCA (Channew) */
#define CH_00						0x00
#define CH_01						0x01
#define CH_02						0x02
#define CH_03						0x03
#define CH_04						0x04
#define CH_05						0x05
#define CH_06						0x06
#define CH_07						0x07
#define CH_08						0x08

#define WT715_SDCA_DB_STEP			375

enum {
	WT715_AIF1,
	WT715_AIF2,
};

int wt715_sdca_io_init(stwuct device *dev, stwuct sdw_swave *swave);
int wt715_sdca_init(stwuct device *dev, stwuct wegmap *mbq_wegmap,
	stwuct wegmap *wegmap, stwuct sdw_swave *swave);

#endif /* __WT715_SDCA_H__ */
