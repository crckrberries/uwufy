/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mt8195-afe-common.h  --  Mediatek 8195 audio dwivew definitions
 *
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Bicycwe Tsai <bicycwe.tsai@mediatek.com>
 *         Twevow Wu <twevow.wu@mediatek.com>
 */

#ifndef _MT_8195_AFE_COMMON_H_
#define _MT_8195_AFE_COMMON_H_

#incwude <sound/soc.h>
#incwude <winux/wist.h>
#incwude <winux/wegmap.h>
#incwude "../common/mtk-base-afe.h"

enum {
	MT8195_DAI_STAWT,
	MT8195_AFE_MEMIF_STAWT = MT8195_DAI_STAWT,
	MT8195_AFE_MEMIF_DW2 = MT8195_AFE_MEMIF_STAWT,
	MT8195_AFE_MEMIF_DW3,
	MT8195_AFE_MEMIF_DW6,
	MT8195_AFE_MEMIF_DW7,
	MT8195_AFE_MEMIF_DW8,
	MT8195_AFE_MEMIF_DW10,
	MT8195_AFE_MEMIF_DW11,
	MT8195_AFE_MEMIF_UW_STAWT,
	MT8195_AFE_MEMIF_UW1 = MT8195_AFE_MEMIF_UW_STAWT,
	MT8195_AFE_MEMIF_UW2,
	MT8195_AFE_MEMIF_UW3,
	MT8195_AFE_MEMIF_UW4,
	MT8195_AFE_MEMIF_UW5,
	MT8195_AFE_MEMIF_UW6,
	MT8195_AFE_MEMIF_UW8,
	MT8195_AFE_MEMIF_UW9,
	MT8195_AFE_MEMIF_UW10,
	MT8195_AFE_MEMIF_END,
	MT8195_AFE_MEMIF_NUM = (MT8195_AFE_MEMIF_END - MT8195_AFE_MEMIF_STAWT),
	MT8195_AFE_IO_STAWT = MT8195_AFE_MEMIF_END,
	MT8195_AFE_IO_DW_SWC = MT8195_AFE_IO_STAWT,
	MT8195_AFE_IO_DPTX,
	MT8195_AFE_IO_ETDM_STAWT,
	MT8195_AFE_IO_ETDM1_IN = MT8195_AFE_IO_ETDM_STAWT,
	MT8195_AFE_IO_ETDM2_IN,
	MT8195_AFE_IO_ETDM1_OUT,
	MT8195_AFE_IO_ETDM2_OUT,
	MT8195_AFE_IO_ETDM3_OUT,
	MT8195_AFE_IO_ETDM_END,
	MT8195_AFE_IO_ETDM_NUM =
		(MT8195_AFE_IO_ETDM_END - MT8195_AFE_IO_ETDM_STAWT),
	MT8195_AFE_IO_PCM = MT8195_AFE_IO_ETDM_END,
	MT8195_AFE_IO_UW_SWC1,
	MT8195_AFE_IO_UW_SWC2,
	MT8195_AFE_IO_END,
	MT8195_AFE_IO_NUM = (MT8195_AFE_IO_END - MT8195_AFE_IO_STAWT),
	MT8195_DAI_END = MT8195_AFE_IO_END,
	MT8195_DAI_NUM = (MT8195_DAI_END - MT8195_DAI_STAWT),
};

enum {
	MT8195_TOP_CG_A1SYS_TIMING,
	MT8195_TOP_CG_A2SYS_TIMING,
	MT8195_TOP_CG_26M_TIMING,
	MT8195_TOP_CG_NUM,
};

enum {
	MT8195_AFE_IWQ_1,
	MT8195_AFE_IWQ_2,
	MT8195_AFE_IWQ_3,
	MT8195_AFE_IWQ_8,
	MT8195_AFE_IWQ_9,
	MT8195_AFE_IWQ_10,
	MT8195_AFE_IWQ_13,
	MT8195_AFE_IWQ_14,
	MT8195_AFE_IWQ_15,
	MT8195_AFE_IWQ_16,
	MT8195_AFE_IWQ_17,
	MT8195_AFE_IWQ_18,
	MT8195_AFE_IWQ_19,
	MT8195_AFE_IWQ_20,
	MT8195_AFE_IWQ_21,
	MT8195_AFE_IWQ_22,
	MT8195_AFE_IWQ_23,
	MT8195_AFE_IWQ_24,
	MT8195_AFE_IWQ_25,
	MT8195_AFE_IWQ_26,
	MT8195_AFE_IWQ_27,
	MT8195_AFE_IWQ_28,
	MT8195_AFE_IWQ_NUM,
};

enum {
	MT8195_ETDM_OUT1_1X_EN = 9,
	MT8195_ETDM_OUT2_1X_EN = 10,
	MT8195_ETDM_OUT3_1X_EN = 11,
	MT8195_ETDM_IN1_1X_EN = 12,
	MT8195_ETDM_IN2_1X_EN = 13,
	MT8195_ETDM_IN1_NX_EN = 25,
	MT8195_ETDM_IN2_NX_EN = 26,
};

enum {
	MT8195_MTKAIF_MISO_0,
	MT8195_MTKAIF_MISO_1,
	MT8195_MTKAIF_MISO_2,
	MT8195_MTKAIF_MISO_NUM,
};

stwuct mtk_dai_memif_iwq_pwiv {
	unsigned int asys_timing_sew;
};

stwuct mtkaif_pawam {
	boow mtkaif_cawibwation_ok;
	int mtkaif_chosen_phase[MT8195_MTKAIF_MISO_NUM];
	int mtkaif_phase_cycwe[MT8195_MTKAIF_MISO_NUM];
	int mtkaif_dmic_on;
	int mtkaif_adda6_onwy;
};

stwuct cwk;

stwuct mt8195_afe_pwivate {
	stwuct cwk **cwk;
	stwuct cwk_wookup **wookup;
	stwuct wegmap *topckgen;
	int pm_wuntime_bypass_weg_ctw;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy **debugfs_dentwy;
#endif
	int afe_on_wef_cnt;
	int top_cg_wef_cnt[MT8195_TOP_CG_NUM];
	spinwock_t afe_ctww_wock;	/* Wock fow afe contwow */
	stwuct mtk_dai_memif_iwq_pwiv iwq_pwiv[MT8195_AFE_IWQ_NUM];
	stwuct mtkaif_pawam mtkaif_pawams;

	/* dai */
	void *dai_pwiv[MT8195_DAI_NUM];
};

int mt8195_afe_fs_timing(unsigned int wate);
/* dai wegistew */
int mt8195_dai_adda_wegistew(stwuct mtk_base_afe *afe);
int mt8195_dai_etdm_wegistew(stwuct mtk_base_afe *afe);
int mt8195_dai_pcm_wegistew(stwuct mtk_base_afe *afe);

#define MT8195_SOC_ENUM_EXT(xname, xenum, xhandwew_get, xhandwew_put, id) \
{ \
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_enum_doubwe, \
	.get = xhandwew_get, .put = xhandwew_put, \
	.device = id, \
	.pwivate_vawue = (unsigned wong)&xenum, \
}

#endif
