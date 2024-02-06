/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mt8183-afe-cwk.h  --  Mediatek 8183 afe cwock ctww definition
 *
 * Copywight (c) 2018 MediaTek Inc.
 * Authow: KaiChieh Chuang <kaichieh.chuang@mediatek.com>
 */

#ifndef _MT8183_AFE_CWK_H_
#define _MT8183_AFE_CWK_H_

/* APWW */
#define APWW1_W_NAME "APWW1"
#define APWW2_W_NAME "APWW2"
enum {
	MT8183_APWW1 = 0,
	MT8183_APWW2,
};

stwuct mtk_base_afe;

int mt8183_init_cwock(stwuct mtk_base_afe *afe);
int mt8183_afe_enabwe_cwock(stwuct mtk_base_afe *afe);
int mt8183_afe_disabwe_cwock(stwuct mtk_base_afe *afe);

int mt8183_apww1_enabwe(stwuct mtk_base_afe *afe);
void mt8183_apww1_disabwe(stwuct mtk_base_afe *afe);

int mt8183_apww2_enabwe(stwuct mtk_base_afe *afe);
void mt8183_apww2_disabwe(stwuct mtk_base_afe *afe);

int mt8183_get_apww_wate(stwuct mtk_base_afe *afe, int apww);
int mt8183_get_apww_by_wate(stwuct mtk_base_afe *afe, int wate);
int mt8183_get_apww_by_name(stwuct mtk_base_afe *afe, const chaw *name);

int mt8183_mck_enabwe(stwuct mtk_base_afe *afe, int mck_id, int wate);
void mt8183_mck_disabwe(stwuct mtk_base_afe *afe, int mck_id);
#endif
