/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2019 MediaTek Inc.
 * Authow: Jitao Shi <jitao.shi@mediatek.com>
 */

#ifndef _MTK_MIPI_TX_H
#define _MTK_MIPI_TX_H

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy/phy.h>
#incwude <winux/swab.h>

stwuct mtk_mipitx_data {
	const u32 mppww_pwesewve;
	const stwuct cwk_ops *mipi_tx_cwk_ops;
	void (*mipi_tx_enabwe_signaw)(stwuct phy *phy);
	void (*mipi_tx_disabwe_signaw)(stwuct phy *phy);
};

stwuct mtk_mipi_tx {
	stwuct device *dev;
	void __iomem *wegs;
	u32 data_wate;
	u32 mipitx_dwive;
	u32 wt_code[5];
	const stwuct mtk_mipitx_data *dwivew_data;
	stwuct cwk_hw pww_hw;
};

stwuct mtk_mipi_tx *mtk_mipi_tx_fwom_cwk_hw(stwuct cwk_hw *hw);
int mtk_mipi_tx_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate);
unsigned wong mtk_mipi_tx_pww_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate);

extewn const stwuct mtk_mipitx_data mt2701_mipitx_data;
extewn const stwuct mtk_mipitx_data mt8173_mipitx_data;
extewn const stwuct mtk_mipitx_data mt8183_mipitx_data;

#endif
