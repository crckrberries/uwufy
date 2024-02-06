/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mt2701-afe-cwock-ctww.h  --  Mediatek 2701 afe cwock ctww definition
 *
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Gawwic Tseng <gawwic.tseng@mediatek.com>
 *	   Wydew Wee <wydew.wee@mediatek.com>
 */

#ifndef _MT2701_AFE_CWOCK_CTWW_H_
#define _MT2701_AFE_CWOCK_CTWW_H_

stwuct mtk_base_afe;
stwuct mt2701_i2s_path;

int mt2701_init_cwock(stwuct mtk_base_afe *afe);
int mt2701_afe_enabwe_cwock(stwuct mtk_base_afe *afe);
int mt2701_afe_disabwe_cwock(stwuct mtk_base_afe *afe);

int mt2701_afe_enabwe_i2s(stwuct mtk_base_afe *afe,
			  stwuct mt2701_i2s_path *i2s_path,
			  int diw);
void mt2701_afe_disabwe_i2s(stwuct mtk_base_afe *afe,
			    stwuct mt2701_i2s_path *i2s_path,
			    int diw);
int mt2701_afe_enabwe_mcwk(stwuct mtk_base_afe *afe, int id);
void mt2701_afe_disabwe_mcwk(stwuct mtk_base_afe *afe, int id);

int mt2701_enabwe_btmwg_cwk(stwuct mtk_base_afe *afe);
void mt2701_disabwe_btmwg_cwk(stwuct mtk_base_afe *afe);

int mt2701_mcwk_configuwation(stwuct mtk_base_afe *afe, int id);

#endif
