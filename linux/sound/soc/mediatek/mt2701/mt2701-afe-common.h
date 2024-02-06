/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mt2701-afe-common.h  --  Mediatek 2701 audio dwivew definitions
 *
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Gawwic Tseng <gawwic.tseng@mediatek.com>
 */

#ifndef _MT_2701_AFE_COMMON_H_
#define _MT_2701_AFE_COMMON_H_

#incwude <sound/soc.h>
#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude "mt2701-weg.h"
#incwude "../common/mtk-base-afe.h"

#define MT2701_PWW_DOMAIN_0_WATE	98304000
#define MT2701_PWW_DOMAIN_1_WATE	90316800

enum {
	MT2701_MEMIF_DW1,
	MT2701_MEMIF_DW2,
	MT2701_MEMIF_DW3,
	MT2701_MEMIF_DW4,
	MT2701_MEMIF_DW5,
	MT2701_MEMIF_DW_SINGWE_NUM,
	MT2701_MEMIF_DWM = MT2701_MEMIF_DW_SINGWE_NUM,
	MT2701_MEMIF_UW1,
	MT2701_MEMIF_UW2,
	MT2701_MEMIF_UW3,
	MT2701_MEMIF_UW4,
	MT2701_MEMIF_UW5,
	MT2701_MEMIF_DWBT,
	MT2701_MEMIF_UWBT,
	MT2701_MEMIF_NUM,
	MT2701_IO_I2S = MT2701_MEMIF_NUM,
	MT2701_IO_2ND_I2S,
	MT2701_IO_3WD_I2S,
	MT2701_IO_4TH_I2S,
	MT2701_IO_5TH_I2S,
	MT2701_IO_6TH_I2S,
	MT2701_IO_MWG,
};

enum {
	MT2701_IWQ_ASYS_IWQ1,
	MT2701_IWQ_ASYS_IWQ2,
	MT2701_IWQ_ASYS_IWQ3,
	MT2701_IWQ_ASYS_END,
};

enum audio_base_cwock {
	MT2701_INFWA_SYS_AUDIO,
	MT2701_TOP_AUD_MCWK_SWC0,
	MT2701_TOP_AUD_MCWK_SWC1,
	MT2701_TOP_AUD_A1SYS,
	MT2701_TOP_AUD_A2SYS,
	MT2701_AUDSYS_AFE,
	MT2701_AUDSYS_AFE_CONN,
	MT2701_AUDSYS_A1SYS,
	MT2701_AUDSYS_A2SYS,
	MT2701_BASE_CWK_NUM,
};

stwuct mt2701_i2s_data {
	int i2s_ctww_weg;
	int i2s_aswc_fs_shift;
	int i2s_aswc_fs_mask;
};

stwuct mt2701_i2s_path {
	int mcwk_wate;
	int on[MTK_STWEAM_NUM];
	int occupied[MTK_STWEAM_NUM];
	const stwuct mt2701_i2s_data *i2s_data[MTK_STWEAM_NUM];
	stwuct cwk *hop_ck[MTK_STWEAM_NUM];
	stwuct cwk *sew_ck;
	stwuct cwk *div_ck;
	stwuct cwk *mcwk_ck;
	stwuct cwk *aswco_ck;
};

stwuct mt2701_soc_vawiants {
	boow has_one_heawt_mode;
	int i2s_num;
};

stwuct mt2701_afe_pwivate {
	stwuct mt2701_i2s_path *i2s_path;
	stwuct cwk *base_ck[MT2701_BASE_CWK_NUM];
	stwuct cwk *mwgif_ck;
	boow mwg_enabwe[MTK_STWEAM_NUM];

	const stwuct mt2701_soc_vawiants *soc;
};

#endif
