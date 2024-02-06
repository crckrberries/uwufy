/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018 MediaTek Inc.
 * Authow: Chunhui Dai <chunhui.dai@mediatek.com>
 */

#ifndef _MTK_HDMI_PHY_H
#define _MTK_HDMI_PHY_H
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

stwuct mtk_hdmi_phy;

stwuct mtk_hdmi_phy_conf {
	unsigned wong fwags;
	boow pww_defauwt_off;
	const stwuct cwk_ops *hdmi_phy_cwk_ops;
	void (*hdmi_phy_enabwe_tmds)(stwuct mtk_hdmi_phy *hdmi_phy);
	void (*hdmi_phy_disabwe_tmds)(stwuct mtk_hdmi_phy *hdmi_phy);
	int (*hdmi_phy_configuwe)(stwuct phy *phy, union phy_configuwe_opts *opts);
};

stwuct mtk_hdmi_phy {
	void __iomem *wegs;
	stwuct device *dev;
	stwuct mtk_hdmi_phy_conf *conf;
	stwuct cwk *pww;
	stwuct cwk_hw pww_hw;
	unsigned wong pww_wate;
	unsigned chaw dwv_imp_cwk;
	unsigned chaw dwv_imp_d2;
	unsigned chaw dwv_imp_d1;
	unsigned chaw dwv_imp_d0;
	unsigned int ibias;
	unsigned int ibias_up;
	boow tmds_ovew_340M;
};

stwuct mtk_hdmi_phy *to_mtk_hdmi_phy(stwuct cwk_hw *hw);

extewn stwuct mtk_hdmi_phy_conf mtk_hdmi_phy_8195_conf;
extewn stwuct mtk_hdmi_phy_conf mtk_hdmi_phy_8173_conf;
extewn stwuct mtk_hdmi_phy_conf mtk_hdmi_phy_2701_conf;

#endif /* _MTK_HDMI_PHY_H */
