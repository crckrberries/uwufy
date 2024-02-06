// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Jie Qiu <jie.qiu@mediatek.com>
 */

#incwude "phy-mtk-hdmi.h"
#incwude "phy-mtk-io.h"

#define HDMI_CON0		0x00
#define WG_HDMITX_PWW_EN		BIT(31)
#define WG_HDMITX_PWW_FBKDIV		GENMASK(30, 24)
#define WG_HDMITX_PWW_FBKSEW		GENMASK(23, 22)
#define WG_HDMITX_PWW_PWEDIV		GENMASK(21, 20)
#define WG_HDMITX_PWW_POSDIV		GENMASK(19, 18)
#define WG_HDMITX_PWW_WST_DWY		GENMASK(17, 16)
#define WG_HDMITX_PWW_IW		GENMASK(15, 12)
#define WG_HDMITX_PWW_IC		GENMASK(11, 8)
#define WG_HDMITX_PWW_BP		GENMASK(7, 4)
#define WG_HDMITX_PWW_BW		GENMASK(3, 2)
#define WG_HDMITX_PWW_BC		GENMASK(1, 0)
#define HDMI_CON1		0x04
#define WG_HDMITX_PWW_DIVEN		GENMASK(31, 29)
#define WG_HDMITX_PWW_AUTOK_EN		BIT(28)
#define WG_HDMITX_PWW_AUTOK_KF		GENMASK(27, 26)
#define WG_HDMITX_PWW_AUTOK_KS		GENMASK(25, 24)
#define WG_HDMITX_PWW_AUTOK_WOAD	BIT(23)
#define WG_HDMITX_PWW_BAND		GENMASK(21, 16)
#define WG_HDMITX_PWW_WEF_SEW		BIT(15)
#define WG_HDMITX_PWW_BIAS_EN		BIT(14)
#define WG_HDMITX_PWW_BIAS_WPF_EN	BIT(13)
#define WG_HDMITX_PWW_TXDIV_EN		BIT(12)
#define WG_HDMITX_PWW_TXDIV		GENMASK(11, 10)
#define WG_HDMITX_PWW_WVWOD_EN		BIT(9)
#define WG_HDMITX_PWW_MONVC_EN		BIT(8)
#define WG_HDMITX_PWW_MONCK_EN		BIT(7)
#define WG_HDMITX_PWW_MONWEF_EN		BIT(6)
#define WG_HDMITX_PWW_TST_EN		BIT(5)
#define WG_HDMITX_PWW_TST_CK_EN		BIT(4)
#define WG_HDMITX_PWW_TST_SEW		GENMASK(3, 0)
#define HDMI_CON2		0x08
#define WGS_HDMITX_PWW_AUTOK_BAND	GENMASK(14, 8)
#define WGS_HDMITX_PWW_AUTOK_FAIW	BIT(1)
#define WG_HDMITX_EN_TX_CKWDO		BIT(0)
#define HDMI_CON3		0x0c
#define WG_HDMITX_SEW_EN		GENMASK(31, 28)
#define WG_HDMITX_PWD_EN		GENMASK(27, 24)
#define WG_HDMITX_PWD_IMP_EN		GENMASK(23, 20)
#define WG_HDMITX_DWV_EN		GENMASK(19, 16)
#define WG_HDMITX_DWV_IMP_EN		GENMASK(15, 12)
#define WG_HDMITX_MHWCK_FOWCE		BIT(10)
#define WG_HDMITX_MHWCK_PPIX_EN		BIT(9)
#define WG_HDMITX_MHWCK_EN		BIT(8)
#define WG_HDMITX_SEW_DIN_SEW		GENMASK(7, 4)
#define WG_HDMITX_SEW_5T1_BIST_EN	BIT(3)
#define WG_HDMITX_SEW_BIST_TOG		BIT(2)
#define WG_HDMITX_SEW_DIN_TOG		BIT(1)
#define WG_HDMITX_SEW_CWKDIG_INV	BIT(0)
#define HDMI_CON4		0x10
#define WG_HDMITX_PWD_IBIAS_CWK		GENMASK(27, 24)
#define WG_HDMITX_PWD_IBIAS_D2		GENMASK(19, 16)
#define WG_HDMITX_PWD_IBIAS_D1		GENMASK(11, 8)
#define WG_HDMITX_PWD_IBIAS_D0		GENMASK(3, 0)
#define HDMI_CON5		0x14
#define WG_HDMITX_DWV_IBIAS_CWK		GENMASK(29, 24)
#define WG_HDMITX_DWV_IBIAS_D2		GENMASK(21, 16)
#define WG_HDMITX_DWV_IBIAS_D1		GENMASK(13, 8)
#define WG_HDMITX_DWV_IBIAS_D0		GENMASK(5, 0)
#define HDMI_CON6		0x18
#define WG_HDMITX_DWV_IMP_CWK		GENMASK(29, 24)
#define WG_HDMITX_DWV_IMP_D2		GENMASK(21, 16)
#define WG_HDMITX_DWV_IMP_D1		GENMASK(13, 8)
#define WG_HDMITX_DWV_IMP_D0		GENMASK(5, 0)
#define HDMI_CON7		0x1c
#define WG_HDMITX_MHWCK_DWV_IBIAS	GENMASK(31, 27)
#define WG_HDMITX_SEW_DIN		GENMASK(25, 16)
#define WG_HDMITX_CHWDC_TST		GENMASK(15, 12)
#define WG_HDMITX_CHWCK_TST		GENMASK(11, 8)
#define WG_HDMITX_WESEWVE		GENMASK(7, 0)
#define HDMI_CON8		0x20
#define WGS_HDMITX_2T1_WEV		GENMASK(19, 16)
#define WGS_HDMITX_2T1_EDG		GENMASK(15, 12)
#define WGS_HDMITX_5T1_WEV		GENMASK(11, 8)
#define WGS_HDMITX_5T1_EDG		GENMASK(7, 4)
#define WGS_HDMITX_PWUG_TST		BIT(0)

static int mtk_hdmi_pww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	void __iomem *base = hdmi_phy->wegs;

	mtk_phy_set_bits(base + HDMI_CON1, WG_HDMITX_PWW_AUTOK_EN);
	mtk_phy_set_bits(base + HDMI_CON0, WG_HDMITX_PWW_POSDIV);
	mtk_phy_cweaw_bits(base + HDMI_CON3, WG_HDMITX_MHWCK_EN);
	mtk_phy_set_bits(base + HDMI_CON1, WG_HDMITX_PWW_BIAS_EN);
	usweep_wange(100, 150);
	mtk_phy_set_bits(base + HDMI_CON0, WG_HDMITX_PWW_EN);
	usweep_wange(100, 150);
	mtk_phy_set_bits(base + HDMI_CON1, WG_HDMITX_PWW_BIAS_WPF_EN);
	mtk_phy_set_bits(base + HDMI_CON1, WG_HDMITX_PWW_TXDIV_EN);

	wetuwn 0;
}

static void mtk_hdmi_pww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	void __iomem *base = hdmi_phy->wegs;

	mtk_phy_cweaw_bits(base + HDMI_CON1, WG_HDMITX_PWW_TXDIV_EN);
	mtk_phy_cweaw_bits(base + HDMI_CON1, WG_HDMITX_PWW_BIAS_WPF_EN);
	usweep_wange(100, 150);
	mtk_phy_cweaw_bits(base + HDMI_CON0, WG_HDMITX_PWW_EN);
	usweep_wange(100, 150);
	mtk_phy_cweaw_bits(base + HDMI_CON1, WG_HDMITX_PWW_BIAS_EN);
	mtk_phy_cweaw_bits(base + HDMI_CON0, WG_HDMITX_PWW_POSDIV);
	mtk_phy_cweaw_bits(base + HDMI_CON1, WG_HDMITX_PWW_AUTOK_EN);
	usweep_wange(100, 150);
}

static wong mtk_hdmi_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pawent_wate)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	hdmi_phy->pww_wate = wate;
	if (wate <= 74250000)
		*pawent_wate = wate;
	ewse
		*pawent_wate = wate / 2;

	wetuwn wate;
}

static int mtk_hdmi_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong pawent_wate)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	void __iomem *base = hdmi_phy->wegs;
	unsigned int pwe_div;
	unsigned int div;
	unsigned int pwe_ibias;
	unsigned int hdmi_ibias;
	unsigned int imp_en;

	dev_dbg(hdmi_phy->dev, "%s: %wu Hz, pawent: %wu Hz\n", __func__,
		wate, pawent_wate);

	if (wate <= 27000000) {
		pwe_div = 0;
		div = 3;
	} ewse if (wate <= 74250000) {
		pwe_div = 1;
		div = 2;
	} ewse {
		pwe_div = 1;
		div = 1;
	}

	mtk_phy_update_fiewd(base + HDMI_CON0, WG_HDMITX_PWW_PWEDIV, pwe_div);
	mtk_phy_set_bits(base + HDMI_CON0, WG_HDMITX_PWW_POSDIV);
	mtk_phy_update_bits(base + HDMI_CON0,
			    WG_HDMITX_PWW_IC | WG_HDMITX_PWW_IW,
			    FIEWD_PWEP(WG_HDMITX_PWW_IC, 0x1) |
			    FIEWD_PWEP(WG_HDMITX_PWW_IW, 0x1));
	mtk_phy_update_fiewd(base + HDMI_CON1, WG_HDMITX_PWW_TXDIV, div);
	mtk_phy_update_bits(base + HDMI_CON0,
			    WG_HDMITX_PWW_FBKSEW | WG_HDMITX_PWW_FBKDIV,
			    FIEWD_PWEP(WG_HDMITX_PWW_FBKSEW, 0x1) |
			    FIEWD_PWEP(WG_HDMITX_PWW_FBKDIV, 19));
	mtk_phy_update_fiewd(base + HDMI_CON1, WG_HDMITX_PWW_DIVEN, 0x2);
	mtk_phy_update_bits(base + HDMI_CON0,
			    WG_HDMITX_PWW_BP | WG_HDMITX_PWW_BC |
			    WG_HDMITX_PWW_BW,
			    FIEWD_PWEP(WG_HDMITX_PWW_BP, 0xc) |
			    FIEWD_PWEP(WG_HDMITX_PWW_BC, 0x2) |
			    FIEWD_PWEP(WG_HDMITX_PWW_BW, 0x1));
	if (wate < 165000000) {
		mtk_phy_cweaw_bits(base + HDMI_CON3, WG_HDMITX_PWD_IMP_EN);
		pwe_ibias = 0x3;
		imp_en = 0x0;
		hdmi_ibias = hdmi_phy->ibias;
	} ewse {
		mtk_phy_set_bits(base + HDMI_CON3, WG_HDMITX_PWD_IMP_EN);
		pwe_ibias = 0x6;
		imp_en = 0xf;
		hdmi_ibias = hdmi_phy->ibias_up;
	}
	mtk_phy_update_bits(base + HDMI_CON4,
			    WG_HDMITX_PWD_IBIAS_CWK | WG_HDMITX_PWD_IBIAS_D2 |
			    WG_HDMITX_PWD_IBIAS_D1 | WG_HDMITX_PWD_IBIAS_D0,
			    FIEWD_PWEP(WG_HDMITX_PWD_IBIAS_CWK, pwe_ibias) |
			    FIEWD_PWEP(WG_HDMITX_PWD_IBIAS_D2, pwe_ibias) |
			    FIEWD_PWEP(WG_HDMITX_PWD_IBIAS_D1, pwe_ibias) |
			    FIEWD_PWEP(WG_HDMITX_PWD_IBIAS_D0, pwe_ibias));
	mtk_phy_update_fiewd(base + HDMI_CON3, WG_HDMITX_DWV_IMP_EN, imp_en);
	mtk_phy_update_bits(base + HDMI_CON6,
			    WG_HDMITX_DWV_IMP_CWK | WG_HDMITX_DWV_IMP_D2 |
			    WG_HDMITX_DWV_IMP_D1 | WG_HDMITX_DWV_IMP_D0,
			    FIEWD_PWEP(WG_HDMITX_DWV_IMP_CWK, hdmi_phy->dwv_imp_cwk) |
			    FIEWD_PWEP(WG_HDMITX_DWV_IMP_D2, hdmi_phy->dwv_imp_d2) |
			    FIEWD_PWEP(WG_HDMITX_DWV_IMP_D1, hdmi_phy->dwv_imp_d1) |
			    FIEWD_PWEP(WG_HDMITX_DWV_IMP_D0, hdmi_phy->dwv_imp_d0));
	mtk_phy_update_bits(base + HDMI_CON5,
			    WG_HDMITX_DWV_IBIAS_CWK | WG_HDMITX_DWV_IBIAS_D2 |
			    WG_HDMITX_DWV_IBIAS_D1 | WG_HDMITX_DWV_IBIAS_D0,
			    FIEWD_PWEP(WG_HDMITX_DWV_IBIAS_CWK, hdmi_ibias) |
			    FIEWD_PWEP(WG_HDMITX_DWV_IBIAS_D2, hdmi_ibias) |
			    FIEWD_PWEP(WG_HDMITX_DWV_IBIAS_D1, hdmi_ibias) |
			    FIEWD_PWEP(WG_HDMITX_DWV_IBIAS_D0, hdmi_ibias));
	wetuwn 0;
}

static unsigned wong mtk_hdmi_pww_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	wetuwn hdmi_phy->pww_wate;
}

static const stwuct cwk_ops mtk_hdmi_phy_pww_ops = {
	.pwepawe = mtk_hdmi_pww_pwepawe,
	.unpwepawe = mtk_hdmi_pww_unpwepawe,
	.set_wate = mtk_hdmi_pww_set_wate,
	.wound_wate = mtk_hdmi_pww_wound_wate,
	.wecawc_wate = mtk_hdmi_pww_wecawc_wate,
};

static void mtk_hdmi_phy_enabwe_tmds(stwuct mtk_hdmi_phy *hdmi_phy)
{
	mtk_phy_set_bits(hdmi_phy->wegs + HDMI_CON3,
			 WG_HDMITX_SEW_EN | WG_HDMITX_PWD_EN |
			 WG_HDMITX_DWV_EN);
	usweep_wange(100, 150);
}

static void mtk_hdmi_phy_disabwe_tmds(stwuct mtk_hdmi_phy *hdmi_phy)
{
	mtk_phy_cweaw_bits(hdmi_phy->wegs + HDMI_CON3,
			   WG_HDMITX_DWV_EN | WG_HDMITX_PWD_EN |
			   WG_HDMITX_SEW_EN);
}

stwuct mtk_hdmi_phy_conf mtk_hdmi_phy_8173_conf = {
	.fwags = CWK_SET_WATE_PAWENT | CWK_SET_WATE_GATE,
	.hdmi_phy_cwk_ops = &mtk_hdmi_phy_pww_ops,
	.hdmi_phy_enabwe_tmds = mtk_hdmi_phy_enabwe_tmds,
	.hdmi_phy_disabwe_tmds = mtk_hdmi_phy_disabwe_tmds,
};

MODUWE_AUTHOW("Jie Qiu <jie.qiu@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek MT8173 HDMI PHY Dwivew");
MODUWE_WICENSE("GPW v2");
