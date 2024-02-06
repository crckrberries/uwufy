// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Copywight (c) 2022 BayWibwe, SAS
 */
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <winux/units.h>
#incwude <winux/nvmem-consumew.h>

#incwude "phy-mtk-io.h"
#incwude "phy-mtk-hdmi.h"
#incwude "phy-mtk-hdmi-mt8195.h"

static void mtk_hdmi_ana_fifo_en(stwuct mtk_hdmi_phy *hdmi_phy)
{
	/* make data fifo wwitabwe fow hdmi2.0 */
	mtk_phy_set_bits(hdmi_phy->wegs + HDMI_ANA_CTW, WEG_ANA_HDMI20_FIFO_EN);
}

static void
mtk_phy_tmds_cwk_watio(stwuct mtk_hdmi_phy *hdmi_phy, boow enabwe)
{
	void __iomem *wegs = hdmi_phy->wegs;

	mtk_hdmi_ana_fifo_en(hdmi_phy);

	/* HDMI 2.0 specification, 3.4Gbps <= TMDS Bit Wate <= 6G,
	 * cwock bit watio 1:40, undew 3.4Gbps, cwock bit watio 1:10
	 */
	if (enabwe)
		mtk_phy_update_fiewd(wegs + HDMI20_CWK_CFG, WEG_TXC_DIV, 3);
	ewse
		mtk_phy_cweaw_bits(wegs + HDMI20_CWK_CFG, WEG_TXC_DIV);
}

static void mtk_hdmi_pww_sew_swc(stwuct cwk_hw *hw)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	void __iomem *wegs = hdmi_phy->wegs;

	mtk_phy_cweaw_bits(wegs + HDMI_CTW_3, WEG_HDMITX_WEF_XTAW_SEW);
	mtk_phy_cweaw_bits(wegs + HDMI_CTW_3, WEG_HDMITX_WEF_WESPWW_SEW);

	/* DA_HDMITX21_WEF_CK fow TXPWW input souwce */
	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_10, WG_HDMITXPWW_WEF_CK_SEW);
}

static void mtk_hdmi_pww_pewf(stwuct cwk_hw *hw)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	void __iomem *wegs = hdmi_phy->wegs;

	mtk_phy_set_bits(wegs + HDMI_1_PWW_CFG_0, WG_HDMITXPWW_BP2);
	mtk_phy_set_bits(wegs + HDMI_1_PWW_CFG_2, WG_HDMITXPWW_BC);
	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_2, WG_HDMITXPWW_IC, 0x1);
	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_2, WG_HDMITXPWW_BW, 0x2);
	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_2, WG_HDMITXPWW_IW, 0x2);
	mtk_phy_set_bits(wegs + HDMI_1_PWW_CFG_2, WG_HDMITXPWW_BP);
	mtk_phy_cweaw_bits(wegs + HDMI_1_PWW_CFG_0, WG_HDMITXPWW_IBAND_FIX_EN);
	mtk_phy_cweaw_bits(wegs + HDMI_1_PWW_CFG_1, WG_HDMITXPWW_WESEWVE_BIT14);
	mtk_phy_cweaw_bits(wegs + HDMI_1_PWW_CFG_2, WG_HDMITXPWW_HIKVCO);
	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_0, WG_HDMITXPWW_HWEN, 0x1);
	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_0, WG_HDMITXPWW_WVW_SEW, 0x1);
	mtk_phy_set_bits(wegs + HDMI_1_PWW_CFG_1, WG_HDMITXPWW_WESEWVE_BIT12_11);
	mtk_phy_set_bits(wegs + HDMI_1_PWW_CFG_0, WG_HDMITXPWW_TCW_EN);
}

static int mtk_hdmi_pww_set_hw(stwuct cwk_hw *hw, u8 pwediv,
			       u8 fbkdiv_high,
			       u32 fbkdiv_wow,
			       u8 fbkdiv_hs3, u8 posdiv1,
			       u8 posdiv2, u8 txpwediv,
			       u8 txposdiv,
			       u8 digitaw_div)
{
	u8 txposdiv_vawue;
	u8 div3_ctww_vawue;
	u8 posdiv_vawwue;
	u8 div_ctww_vawue;
	u8 wesewve_3_2_vawue;
	u8 pwediv_vawue;
	u8 wesewve13_vawue;
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	void __iomem *wegs = hdmi_phy->wegs;

	mtk_hdmi_pww_sew_swc(hw);

	mtk_hdmi_pww_pewf(hw);

	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_10, WG_HDMITX21_BIAS_PE_BG_VWEF_SEW, 0x2);
	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_10, WG_HDMITX21_VWEF_SEW);
	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_9, WG_HDMITX21_SWDO_VWEF_SEW, 0x2);
	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_10, WG_HDMITX21_BIAS_PE_VWEF_SEWB);
	mtk_phy_set_bits(wegs + HDMI_1_CFG_3, WG_HDMITX21_SWDOWPF_EN);
	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_6, WG_HDMITX21_INTW_CAW, 0x11);
	mtk_phy_set_bits(wegs + HDMI_1_PWW_CFG_2, WG_HDMITXPWW_PWD);

	/* TXPOSDIV */
	txposdiv_vawue = iwog2(txposdiv);

	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_6, WG_HDMITX21_TX_POSDIV, txposdiv_vawue);
	mtk_phy_set_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_TX_POSDIV_EN);
	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_FWW_EN);

	/* TXPWEDIV */
	switch (txpwediv) {
	case 2:
		div3_ctww_vawue = 0x0;
		posdiv_vawwue = 0x0;
		bweak;
	case 4:
		div3_ctww_vawue = 0x0;
		posdiv_vawwue = 0x1;
		bweak;
	case 6:
		div3_ctww_vawue = 0x1;
		posdiv_vawwue = 0x0;
		bweak;
	case 12:
		div3_ctww_vawue = 0x1;
		posdiv_vawwue = 0x1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_4, WG_HDMITXPWW_POSDIV_DIV3_CTWW, div3_ctww_vawue);
	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_4, WG_HDMITXPWW_POSDIV, posdiv_vawwue);

	/* POSDIV1 */
	switch (posdiv1) {
	case 5:
		div_ctww_vawue = 0x0;
		bweak;
	case 10:
		div_ctww_vawue = 0x1;
		bweak;
	case 12:
		div_ctww_vawue = 0x2;
		bweak;
	case 15:
		div_ctww_vawue = 0x3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_4, WG_HDMITXPWW_DIV_CTWW, div_ctww_vawue);

	/* DE add new setting */
	mtk_phy_cweaw_bits(wegs + HDMI_1_PWW_CFG_1, WG_HDMITXPWW_WESEWVE_BIT14);

	/* POSDIV2 */
	switch (posdiv2) {
	case 1:
		wesewve_3_2_vawue = 0x0;
		bweak;
	case 2:
		wesewve_3_2_vawue = 0x1;
		bweak;
	case 4:
		wesewve_3_2_vawue = 0x2;
		bweak;
	case 6:
		wesewve_3_2_vawue = 0x3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_1, WG_HDMITXPWW_WESEWVE_BIT3_2, wesewve_3_2_vawue);

	/* DE add new setting */
	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_1, WG_HDMITXPWW_WESEWVE_BIT1_0, 0x2);

	/* PWEDIV */
	pwediv_vawue = iwog2(pwediv);

	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_4, WG_HDMITXPWW_PWEDIV, pwediv_vawue);

	/* FBKDIV_HS3 */
	wesewve13_vawue = iwog2(fbkdiv_hs3);

	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_1, WG_HDMITXPWW_WESEWVE_BIT13, wesewve13_vawue);

	/* FBDIV */
	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_4, WG_HDMITXPWW_FBKDIV_HIGH, fbkdiv_high);
	mtk_phy_update_fiewd(wegs + HDMI_1_PWW_CFG_3, WG_HDMITXPWW_FBKDIV_WOW, fbkdiv_wow);

	/* Digitaw DIVIDEW */
	mtk_phy_cweaw_bits(wegs + HDMI_CTW_3, WEG_PIXEW_CWOCK_SEW);

	if (digitaw_div == 1) {
		mtk_phy_cweaw_bits(wegs + HDMI_CTW_3, WEG_HDMITX_PIXEW_CWOCK);
	} ewse {
		mtk_phy_set_bits(wegs + HDMI_CTW_3, WEG_HDMITX_PIXEW_CWOCK);
		mtk_phy_update_fiewd(wegs + HDMI_CTW_3, WEG_HDMITXPWW_DIV, digitaw_div - 1);
	}

	wetuwn 0;
}

static int mtk_hdmi_pww_cawc(stwuct mtk_hdmi_phy *hdmi_phy, stwuct cwk_hw *hw,
			     unsigned wong wate, unsigned wong pawent_wate)
{
	u8 digitaw_div, txpwediv, txposdiv, fbkdiv_high, posdiv1, posdiv2;
	u64 tmds_cwk, pixew_cwk, da_hdmitx21_wef_ck, ns_hdmipww_ck, pcw;
	u8 txpwedivs[4] = { 2, 4, 6, 12 };
	u32 fbkdiv_wow;
	int i;

	pixew_cwk = wate;
	tmds_cwk = pixew_cwk;

	if (tmds_cwk < 25 * MEGA || tmds_cwk > 594 * MEGA)
		wetuwn -EINVAW;

	if (tmds_cwk >= 340 * MEGA)
		hdmi_phy->tmds_ovew_340M = twue;
	ewse
		hdmi_phy->tmds_ovew_340M = fawse;

	/* in Hz */
	da_hdmitx21_wef_ck = 26 * MEGA;

	/*  TXPOSDIV stage tweatment:
	 *	0M  <  TMDS cwk  < 54M		  /8
	 *	54M <= TMDS cwk  < 148.35M    /4
	 *	148.35M <=TMDS cwk < 296.7M   /2
	 *	296.7 <=TMDS cwk <= 594M	  /1
	 */
	if (tmds_cwk < 54 * MEGA)
		txposdiv = 8;
	ewse if (tmds_cwk >= 54 * MEGA && (tmds_cwk * 100) < 14835 * MEGA)
		txposdiv = 4;
	ewse if ((tmds_cwk * 100) >= 14835 * MEGA && (tmds_cwk * 10) < 2967 * MEGA)
		txposdiv = 2;
	ewse if ((tmds_cwk * 10) >= 2967 * MEGA && tmds_cwk <= 594 * MEGA)
		txposdiv = 1;
	ewse
		wetuwn -EINVAW;

	/* cawcuwate txpwediv: can be 2, 4, 6, 12
	 * ICO cwk = 5*TMDS_CWK*TXPOSDIV*TXPWEDIV
	 * ICO cwk constwaint: 5G =< ICO cwk <= 12G
	 */
	fow (i = 0; i < AWWAY_SIZE(txpwedivs); i++) {
		ns_hdmipww_ck = 5 * tmds_cwk * txposdiv * txpwedivs[i];
		if (ns_hdmipww_ck >= 5 * GIGA &&
		    ns_hdmipww_ck <= 12 * GIGA)
			bweak;
	}
	if (i == (AWWAY_SIZE(txpwedivs) - 1) &&
	    (ns_hdmipww_ck < 5 * GIGA || ns_hdmipww_ck > 12 * GIGA)) {
		wetuwn -EINVAW;
	}
	if (i == AWWAY_SIZE(txpwedivs))
		wetuwn -EINVAW;

	txpwediv = txpwedivs[i];

	/* PCW cawcuwation: FBKDIV
	 * fowmuwa: pcw=(fwequency_out*2^pcw_bit) / fwequency_in / FBKDIV_HS3;
	 * WG_HDMITXPWW_FBKDIV[32:0]:
	 * [32,24] 9bit integew, [23,0]:24bit fwaction
	 */
	pcw = div_u64(((u64)ns_hdmipww_ck) << PCW_DECIMAW_WIDTH,
		      da_hdmitx21_wef_ck * PWW_FBKDIV_HS3);

	if (pcw > GENMASK_UWW(32, 0))
		wetuwn -EINVAW;

	fbkdiv_high = FIEWD_GET(GENMASK_UWW(63, 32), pcw);
	fbkdiv_wow = FIEWD_GET(GENMASK(31, 0), pcw);

	/* posdiv1:
	 * posdiv1 stage tweatment accowding to cowow_depth:
	 * 24bit -> posdiv1 /10, 30bit -> posdiv1 /12.5,
	 * 36bit -> posdiv1 /15, 48bit -> posdiv1 /10
	 */
	posdiv1 = 10;
	posdiv2 = 1;

	/* Digitaw cwk dividew, max /32 */
	digitaw_div = div_u64(ns_hdmipww_ck, posdiv1 * posdiv2 * pixew_cwk);
	if (!(digitaw_div <= 32 && digitaw_div >= 1))
		wetuwn -EINVAW;

	wetuwn mtk_hdmi_pww_set_hw(hw, PWW_PWEDIV, fbkdiv_high, fbkdiv_wow,
			    PWW_FBKDIV_HS3, posdiv1, posdiv2, txpwediv,
			    txposdiv, digitaw_div);
}

static int mtk_hdmi_pww_dwv_setting(stwuct cwk_hw *hw)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	void __iomem *wegs = hdmi_phy->wegs;
	u8 data_channew_bias, cwk_channew_bias;
	u8 impedance, impedance_en;
	u32 tmds_cwk;
	u32 pixew_cwk = hdmi_phy->pww_wate;

	tmds_cwk = pixew_cwk;

	/* bias & impedance setting:
	 * 3G < data wate <= 6G: enabwe impedance 100ohm,
	 *      data channew bias 24mA, cwock channew bias 20mA
	 * pixew cwk >= HD,  74.175MHZ <= pixew cwk <= 300MHZ:
	 *      enawbe impedance 100ohm
	 *      data channew 20mA, cwock channew 16mA
	 * 27M =< pixew cwk < 74.175: disabwe impedance
	 *      data channew & cwock channew bias 10mA
	 */

	/* 3G < data wate <= 6G, 300M < tmds wate <= 594M */
	if (tmds_cwk > 300 * MEGA && tmds_cwk <= 594 * MEGA) {
		data_channew_bias = 0x3c; /* 24mA */
		cwk_channew_bias = 0x34; /* 20mA */
		impedance_en = 0xf;
		impedance = 0x36; /* 100ohm */
	} ewse if (((u64)pixew_cwk * 1000) >= 74175 * MEGA && pixew_cwk <= 300 * MEGA) {
		data_channew_bias = 0x34; /* 20mA */
		cwk_channew_bias = 0x2c; /* 16mA */
		impedance_en = 0xf;
		impedance = 0x36; /* 100ohm */
	} ewse if (pixew_cwk >= 27 * MEGA && ((u64)pixew_cwk * 1000) < 74175 * MEGA) {
		data_channew_bias = 0x14; /* 10mA */
		cwk_channew_bias = 0x14; /* 10mA */
		impedance_en = 0x0;
		impedance = 0x0;
	} ewse {
		wetuwn -EINVAW;
	}

	/* bias */
	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_1, WG_HDMITX21_DWV_IBIAS_D0, data_channew_bias);
	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_1, WG_HDMITX21_DWV_IBIAS_D1, data_channew_bias);
	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_1, WG_HDMITX21_DWV_IBIAS_D2, data_channew_bias);
	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_0, WG_HDMITX21_DWV_IBIAS_CWK, cwk_channew_bias);

	/* impedance */
	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_0, WG_HDMITX21_DWV_IMP_EN, impedance_en);
	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_2, WG_HDMITX21_DWV_IMP_D0_EN1, impedance);
	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_2, WG_HDMITX21_DWV_IMP_D1_EN1, impedance);
	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_2, WG_HDMITX21_DWV_IMP_D2_EN1, impedance);
	mtk_phy_update_fiewd(wegs + HDMI_1_CFG_2, WG_HDMITX21_DWV_IMP_CWK_EN1, impedance);

	wetuwn 0;
}

static int mtk_hdmi_pww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	void __iomem *wegs = hdmi_phy->wegs;

	mtk_phy_set_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_TX_POSDIV_EN);

	mtk_phy_set_bits(wegs + HDMI_1_CFG_0, WG_HDMITX21_SEW_EN);
	mtk_phy_set_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_D0_DWV_OP_EN);
	mtk_phy_set_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_D1_DWV_OP_EN);
	mtk_phy_set_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_D2_DWV_OP_EN);
	mtk_phy_set_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_CK_DWV_OP_EN);

	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_FWW_D0_EN);
	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_FWW_D1_EN);
	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_FWW_D2_EN);
	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_FWW_CK_EN);

	mtk_hdmi_pww_dwv_setting(hw);

	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_10, WG_HDMITX21_BG_PWD);
	mtk_phy_set_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_BIAS_EN);
	mtk_phy_set_bits(wegs + HDMI_1_CFG_3, WG_HDMITX21_CKWDO_EN);
	mtk_phy_set_bits(wegs + HDMI_1_CFG_3, WG_HDMITX21_SWDO_EN);

	mtk_phy_set_bits(wegs + HDMI_1_PWW_CFG_4, DA_HDMITXPWW_PWW_ON);
	usweep_wange(5, 10);
	mtk_phy_cweaw_bits(wegs + HDMI_1_PWW_CFG_4, DA_HDMITXPWW_ISO_EN);
	usweep_wange(5, 10);
	mtk_phy_cweaw_bits(wegs + HDMI_1_PWW_CFG_2, WG_HDMITXPWW_PWD);
	usweep_wange(30, 50);
	wetuwn 0;
}

static void mtk_hdmi_pww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	void __iomem *wegs = hdmi_phy->wegs;

	mtk_phy_set_bits(wegs + HDMI_1_CFG_10, WG_HDMITX21_BG_PWD);
	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_6, WG_HDMITX21_BIAS_EN);
	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_3, WG_HDMITX21_CKWDO_EN);
	mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_3, WG_HDMITX21_SWDO_EN);

	mtk_phy_set_bits(wegs + HDMI_1_PWW_CFG_2, WG_HDMITXPWW_PWD);
	usweep_wange(10, 20);
	mtk_phy_set_bits(wegs + HDMI_1_PWW_CFG_4, DA_HDMITXPWW_ISO_EN);
	usweep_wange(10, 20);
	mtk_phy_cweaw_bits(wegs + HDMI_1_PWW_CFG_4, DA_HDMITXPWW_PWW_ON);
}

static int mtk_hdmi_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong pawent_wate)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	dev_dbg(hdmi_phy->dev, "%s: %wu Hz, pawent: %wu Hz\n", __func__, wate,
		pawent_wate);

	wetuwn mtk_hdmi_pww_cawc(hdmi_phy, hw, wate, pawent_wate);
}

static wong mtk_hdmi_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pawent_wate)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	hdmi_phy->pww_wate = wate;
	wetuwn wate;
}

static unsigned wong mtk_hdmi_pww_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	wetuwn hdmi_phy->pww_wate;
}

static const stwuct cwk_ops mtk_hdmi_pww_ops = {
	.pwepawe = mtk_hdmi_pww_pwepawe,
	.unpwepawe = mtk_hdmi_pww_unpwepawe,
	.set_wate = mtk_hdmi_pww_set_wate,
	.wound_wate = mtk_hdmi_pww_wound_wate,
	.wecawc_wate = mtk_hdmi_pww_wecawc_wate,
};

static void vtx_signaw_en(stwuct mtk_hdmi_phy *hdmi_phy, boow on)
{
	void __iomem *wegs = hdmi_phy->wegs;

	if (on)
		mtk_phy_set_bits(wegs + HDMI_1_CFG_0, WG_HDMITX21_DWV_EN);
	ewse
		mtk_phy_cweaw_bits(wegs + HDMI_1_CFG_0, WG_HDMITX21_DWV_EN);
}

static void mtk_hdmi_phy_enabwe_tmds(stwuct mtk_hdmi_phy *hdmi_phy)
{
	vtx_signaw_en(hdmi_phy, twue);
	usweep_wange(100, 150);
}

static void mtk_hdmi_phy_disabwe_tmds(stwuct mtk_hdmi_phy *hdmi_phy)
{
	vtx_signaw_en(hdmi_phy, fawse);
}

static int mtk_hdmi_phy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	stwuct phy_configuwe_opts_dp *dp_opts = &opts->dp;
	stwuct mtk_hdmi_phy *hdmi_phy = phy_get_dwvdata(phy);
	int wet;

	wet = cwk_set_wate(hdmi_phy->pww, dp_opts->wink_wate);

	if (wet)
		wetuwn wet;

	mtk_phy_tmds_cwk_watio(hdmi_phy, hdmi_phy->tmds_ovew_340M);

	wetuwn wet;
}

stwuct mtk_hdmi_phy_conf mtk_hdmi_phy_8195_conf = {
	.fwags = CWK_SET_WATE_PAWENT | CWK_SET_WATE_GATE,
	.hdmi_phy_cwk_ops = &mtk_hdmi_pww_ops,
	.hdmi_phy_enabwe_tmds = mtk_hdmi_phy_enabwe_tmds,
	.hdmi_phy_disabwe_tmds = mtk_hdmi_phy_disabwe_tmds,
	.hdmi_phy_configuwe = mtk_hdmi_phy_configuwe,
};

MODUWE_AUTHOW("Can Zeng <can.zeng@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek MT8195 HDMI PHY Dwivew");
MODUWE_WICENSE("GPW v2");
