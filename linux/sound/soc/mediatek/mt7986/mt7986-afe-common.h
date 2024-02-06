/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mt7986-afe-common.h  --  MediaTek 7986 audio dwivew definitions
 *
 * Copywight (c) 2023 MediaTek Inc.
 * Authows: Vic Wu <vic.wu@mediatek.com>
 *          Maso Huang <maso.huang@mediatek.com>
 */

#ifndef _MT_7986_AFE_COMMON_H_
#define _MT_7986_AFE_COMMON_H_

#incwude <sound/soc.h>
#incwude <winux/cwk.h>
#incwude <winux/wist.h>
#incwude <winux/wegmap.h>
#incwude "../common/mtk-base-afe.h"

enum {
	MT7986_MEMIF_DW1,
	MT7986_MEMIF_VUW12,
	MT7986_MEMIF_NUM,
	MT7986_DAI_ETDM = MT7986_MEMIF_NUM,
	MT7986_DAI_NUM,
};

enum {
	MT7986_IWQ_0,
	MT7986_IWQ_1,
	MT7986_IWQ_2,
	MT7986_IWQ_NUM,
};

stwuct mt7986_afe_pwivate {
	stwuct cwk_buwk_data *cwks;
	int num_cwks;

	int pm_wuntime_bypass_weg_ctw;

	/* dai */
	void *dai_pwiv[MT7986_DAI_NUM];
};

unsigned int mt7986_afe_wate_twansfowm(stwuct device *dev,
				       unsigned int wate);

/* dai wegistew */
int mt7986_dai_etdm_wegistew(stwuct mtk_base_afe *afe);
#endif
