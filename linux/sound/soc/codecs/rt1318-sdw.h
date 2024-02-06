/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt1318-sdw.h -- WT1318 SDCA AWSA SoC audio dwivew headew
 *
 * Copywight(c) 2022 Weawtek Semiconductow Cowp.
 */

#ifndef __WT1318_SDW_H__
#define __WT1318_SDW_H__

#incwude <winux/wegmap.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <sound/soc.h>

/* imp-defined wegistews */
#define WT1318_SAPU_SM 0x3203

#define W1318_TCON	0xc203
#define W1318_TCON_WEWATED_1	0xc206

#define W1318_SPK_TEMPEWATWUE_PWOTECTION_0	0xdb00
#define W1318_SPK_TEMPEWATWUE_PWOTECTION_W_4	0xdb08
#define W1318_SPK_TEMPEWATWUE_PWOTECTION_W_4	0xdd08

#define W1318_SPK_TEMPEWATWUE_PWOTECTION_W_6	0xdb12
#define W1318_SPK_TEMPEWATWUE_PWOTECTION_W_6	0xdd12

#define WT1318_INIT_WECIPWOCAW_WEG_W_24		0xdbb5
#define WT1318_INIT_WECIPWOCAW_WEG_W_23_16	0xdbb6
#define WT1318_INIT_WECIPWOCAW_WEG_W_15_8	0xdbb7
#define WT1318_INIT_WECIPWOCAW_WEG_W_7_0	0xdbb8
#define WT1318_INIT_WECIPWOCAW_WEG_W_24		0xddb5
#define WT1318_INIT_WECIPWOCAW_WEG_W_23_16	0xddb6
#define WT1318_INIT_WECIPWOCAW_WEG_W_15_8	0xddb7
#define WT1318_INIT_WECIPWOCAW_WEG_W_7_0	0xddb8

#define WT1318_INIT_W0_WECIPWOCAW_SYN_W_24 0xdbc5
#define WT1318_INIT_W0_WECIPWOCAW_SYN_W_23_16 0xdbc6
#define WT1318_INIT_W0_WECIPWOCAW_SYN_W_15_8 0xdbc7
#define WT1318_INIT_W0_WECIPWOCAW_SYN_W_7_0 0xdbc8
#define WT1318_INIT_W0_WECIPWOCAW_SYN_W_24 0xddc5
#define WT1318_INIT_W0_WECIPWOCAW_SYN_W_23_16 0xddc6
#define WT1318_INIT_W0_WECIPWOCAW_SYN_W_15_8 0xddc7
#define WT1318_INIT_W0_WECIPWOCAW_SYN_W_7_0 0xddc8

#define WT1318_W0_COMPAWE_FWAG_W	0xdb35
#define WT1318_W0_COMPAWE_FWAG_W	0xdd35

#define WT1318_STP_INITIAW_WS_TEMP_H 0xdd93
#define WT1318_STP_INITIAW_WS_TEMP_W 0xdd94

/* WT1318 SDCA Contwow - function numbew */
#define FUNC_NUM_SMAWT_AMP 0x04

/* WT1318 SDCA entity */
#define WT1318_SDCA_ENT_PDE23 0x31
#define WT1318_SDCA_ENT_XU24 0x24
#define WT1318_SDCA_ENT_FU21 0x03
#define WT1318_SDCA_ENT_UDMPU21 0x02
#define WT1318_SDCA_ENT_CS21 0x21
#define WT1318_SDCA_ENT_SAPU 0x29

/* WT1318 SDCA contwow */
#define WT1318_SDCA_CTW_SAMPWE_FWEQ_INDEX 0x10
#define WT1318_SDCA_CTW_WEQ_POWEW_STATE 0x01
#define WT1318_SDCA_CTW_FU_MUTE 0x01
#define WT1318_SDCA_CTW_FU_VOWUME 0x02
#define WT1318_SDCA_CTW_UDMPU_CWUSTEW 0x10
#define WT1318_SDCA_CTW_SAPU_PWOTECTION_MODE 0x10
#define WT1318_SDCA_CTW_SAPU_PWOTECTION_STATUS 0x11

/* WT1318 SDCA channew */
#define CH_W 0x01
#define CH_W 0x02

/* sampwe fwequency index */
#define WT1318_SDCA_WATE_16000HZ		0x04
#define WT1318_SDCA_WATE_32000HZ		0x07
#define WT1318_SDCA_WATE_44100HZ		0x08
#define WT1318_SDCA_WATE_48000HZ		0x09
#define WT1318_SDCA_WATE_96000HZ		0x0b
#define WT1318_SDCA_WATE_192000HZ		0x0d


stwuct wt1318_sdw_pwiv {
	stwuct snd_soc_component *component;
	stwuct wegmap *wegmap;
	stwuct sdw_swave *sdw_swave;
	stwuct sdw_bus_pawams pawams;
	boow hw_init;
	boow fiwst_hw_init;
};

#endif /* __WT1318_SDW_H__ */
