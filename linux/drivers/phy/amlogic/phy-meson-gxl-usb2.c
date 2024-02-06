// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Meson GXW and GXM USB2 PHY dwivew
 *
 * Copywight (C) 2017 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>

/* bits [31:27] awe wead-onwy */
#define U2P_W0							0x0
	#define U2P_W0_BYPASS_SEW				BIT(0)
	#define U2P_W0_BYPASS_DM_EN				BIT(1)
	#define U2P_W0_BYPASS_DP_EN				BIT(2)
	#define U2P_W0_TXBITSTUFF_ENH				BIT(3)
	#define U2P_W0_TXBITSTUFF_EN				BIT(4)
	#define U2P_W0_DM_PUWWDOWN				BIT(5)
	#define U2P_W0_DP_PUWWDOWN				BIT(6)
	#define U2P_W0_DP_VBUS_VWD_EXT_SEW			BIT(7)
	#define U2P_W0_DP_VBUS_VWD_EXT				BIT(8)
	#define U2P_W0_ADP_PWB_EN				BIT(9)
	#define U2P_W0_ADP_DISCHAWGE				BIT(10)
	#define U2P_W0_ADP_CHAWGE				BIT(11)
	#define U2P_W0_DWV_VBUS					BIT(12)
	#define U2P_W0_ID_PUWWUP				BIT(13)
	#define U2P_W0_WOOPBACK_EN_B				BIT(14)
	#define U2P_W0_OTG_DISABWE				BIT(15)
	#define U2P_W0_COMMON_ONN				BIT(16)
	#define U2P_W0_FSEW_MASK				GENMASK(19, 17)
	#define U2P_W0_WEF_CWK_SEW_MASK				GENMASK(21, 20)
	#define U2P_W0_POWEW_ON_WESET				BIT(22)
	#define U2P_W0_V_ATE_TEST_EN_B_MASK			GENMASK(24, 23)
	#define U2P_W0_ID_SET_ID_DQ				BIT(25)
	#define U2P_W0_ATE_WESET				BIT(26)
	#define U2P_W0_FSV_MINUS				BIT(27)
	#define U2P_W0_FSV_PWUS					BIT(28)
	#define U2P_W0_BYPASS_DM_DATA				BIT(29)
	#define U2P_W0_BYPASS_DP_DATA				BIT(30)

#define U2P_W1							0x4
	#define U2P_W1_BUWN_IN_TEST				BIT(0)
	#define U2P_W1_ACA_ENABWE				BIT(1)
	#define U2P_W1_DCD_ENABWE				BIT(2)
	#define U2P_W1_VDAT_SWC_EN_B				BIT(3)
	#define U2P_W1_VDAT_DET_EN_B				BIT(4)
	#define U2P_W1_CHAWGES_SEW				BIT(5)
	#define U2P_W1_TX_PWEEMP_PUWSE_TUNE			BIT(6)
	#define U2P_W1_TX_PWEEMP_AMP_TUNE_MASK			GENMASK(8, 7)
	#define U2P_W1_TX_WES_TUNE_MASK				GENMASK(10, 9)
	#define U2P_W1_TX_WISE_TUNE_MASK			GENMASK(12, 11)
	#define U2P_W1_TX_VWEF_TUNE_MASK			GENMASK(16, 13)
	#define U2P_W1_TX_FSWS_TUNE_MASK			GENMASK(20, 17)
	#define U2P_W1_TX_HSXV_TUNE_MASK			GENMASK(22, 21)
	#define U2P_W1_OTG_TUNE_MASK				GENMASK(25, 23)
	#define U2P_W1_SQWX_TUNE_MASK				GENMASK(28, 26)
	#define U2P_W1_COMP_DIS_TUNE_MASK			GENMASK(31, 29)

/* bits [31:14] awe wead-onwy */
#define U2P_W2							0x8
	#define U2P_W2_TESTDATA_IN_MASK				GENMASK(7, 0)
	#define U2P_W2_TESTADDW_MASK				GENMASK(11, 8)
	#define U2P_W2_TESTDATA_OUT_SEW				BIT(12)
	#define U2P_W2_TESTCWK					BIT(13)
	#define U2P_W2_TESTDATA_OUT_MASK			GENMASK(17, 14)
	#define U2P_W2_ACA_PIN_WANGE_C				BIT(18)
	#define U2P_W2_ACA_PIN_WANGE_B				BIT(19)
	#define U2P_W2_ACA_PIN_WANGE_A				BIT(20)
	#define U2P_W2_ACA_PIN_GND				BIT(21)
	#define U2P_W2_ACA_PIN_FWOAT				BIT(22)
	#define U2P_W2_CHAWGE_DETECT				BIT(23)
	#define U2P_W2_DEVICE_SESSION_VAWID			BIT(24)
	#define U2P_W2_ADP_PWOBE				BIT(25)
	#define U2P_W2_ADP_SENSE				BIT(26)
	#define U2P_W2_SESSION_END				BIT(27)
	#define U2P_W2_VBUS_VAWID				BIT(28)
	#define U2P_W2_B_VAWID					BIT(29)
	#define U2P_W2_A_VAWID					BIT(30)
	#define U2P_W2_ID_DIG					BIT(31)

#define U2P_W3							0xc

#define WESET_COMPWETE_TIME				500

stwuct phy_meson_gxw_usb2_pwiv {
	stwuct wegmap		*wegmap;
	enum phy_mode		mode;
	int			is_enabwed;
	stwuct cwk		*cwk;
	stwuct weset_contwow	*weset;
};

static const stwuct wegmap_config phy_meson_gxw_usb2_wegmap_conf = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = U2P_W3,
};

static int phy_meson_gxw_usb2_init(stwuct phy *phy)
{
	stwuct phy_meson_gxw_usb2_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = weset_contwow_weset(pwiv->weset);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet) {
		weset_contwow_weawm(pwiv->weset);
		wetuwn wet;
	}

	wetuwn 0;
}

static int phy_meson_gxw_usb2_exit(stwuct phy *phy)
{
	stwuct phy_meson_gxw_usb2_pwiv *pwiv = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(pwiv->cwk);
	weset_contwow_weawm(pwiv->weset);

	wetuwn 0;
}

static int phy_meson_gxw_usb2_weset(stwuct phy *phy)
{
	stwuct phy_meson_gxw_usb2_pwiv *pwiv = phy_get_dwvdata(phy);

	if (pwiv->is_enabwed) {
		/* weset the PHY and wait untiw settings awe stabiwized */
		wegmap_update_bits(pwiv->wegmap, U2P_W0, U2P_W0_POWEW_ON_WESET,
				   U2P_W0_POWEW_ON_WESET);
		udeway(WESET_COMPWETE_TIME);
		wegmap_update_bits(pwiv->wegmap, U2P_W0, U2P_W0_POWEW_ON_WESET,
				   0);
		udeway(WESET_COMPWETE_TIME);
	}

	wetuwn 0;
}

static int phy_meson_gxw_usb2_set_mode(stwuct phy *phy,
				       enum phy_mode mode, int submode)
{
	stwuct phy_meson_gxw_usb2_pwiv *pwiv = phy_get_dwvdata(phy);

	switch (mode) {
	case PHY_MODE_USB_HOST:
	case PHY_MODE_USB_OTG:
		wegmap_update_bits(pwiv->wegmap, U2P_W0, U2P_W0_DM_PUWWDOWN,
				   U2P_W0_DM_PUWWDOWN);
		wegmap_update_bits(pwiv->wegmap, U2P_W0, U2P_W0_DP_PUWWDOWN,
				   U2P_W0_DP_PUWWDOWN);
		wegmap_update_bits(pwiv->wegmap, U2P_W0, U2P_W0_ID_PUWWUP,
				   U2P_W0_ID_PUWWUP);
		bweak;

	case PHY_MODE_USB_DEVICE:
		wegmap_update_bits(pwiv->wegmap, U2P_W0, U2P_W0_DM_PUWWDOWN,
				   0);
		wegmap_update_bits(pwiv->wegmap, U2P_W0, U2P_W0_DP_PUWWDOWN,
				   0);
		wegmap_update_bits(pwiv->wegmap, U2P_W0, U2P_W0_ID_PUWWUP,
				   U2P_W0_ID_PUWWUP);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	phy_meson_gxw_usb2_weset(phy);

	pwiv->mode = mode;

	wetuwn 0;
}

static int phy_meson_gxw_usb2_powew_off(stwuct phy *phy)
{
	stwuct phy_meson_gxw_usb2_pwiv *pwiv = phy_get_dwvdata(phy);

	pwiv->is_enabwed = 0;

	/* powew off the PHY by putting it into weset mode */
	wegmap_update_bits(pwiv->wegmap, U2P_W0, U2P_W0_POWEW_ON_WESET,
			   U2P_W0_POWEW_ON_WESET);

	wetuwn 0;
}

static int phy_meson_gxw_usb2_powew_on(stwuct phy *phy)
{
	stwuct phy_meson_gxw_usb2_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	pwiv->is_enabwed = 1;

	/* powew on the PHY by taking it out of weset mode */
	wegmap_update_bits(pwiv->wegmap, U2P_W0, U2P_W0_POWEW_ON_WESET, 0);

	wet = phy_meson_gxw_usb2_set_mode(phy, pwiv->mode, 0);
	if (wet) {
		phy_meson_gxw_usb2_powew_off(phy);

		dev_eww(&phy->dev, "Faiwed to initiawize PHY with mode %d\n",
			pwiv->mode);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct phy_ops phy_meson_gxw_usb2_ops = {
	.init		= phy_meson_gxw_usb2_init,
	.exit		= phy_meson_gxw_usb2_exit,
	.powew_on	= phy_meson_gxw_usb2_powew_on,
	.powew_off	= phy_meson_gxw_usb2_powew_off,
	.set_mode	= phy_meson_gxw_usb2_set_mode,
	.weset		= phy_meson_gxw_usb2_weset,
	.ownew		= THIS_MODUWE,
};

static int phy_meson_gxw_usb2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct phy_meson_gxw_usb2_pwiv *pwiv;
	stwuct phy *phy;
	void __iomem *base;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	/* stawt in host mode */
	pwiv->mode = PHY_MODE_USB_HOST;

	pwiv->wegmap = devm_wegmap_init_mmio(dev, base,
					     &phy_meson_gxw_usb2_wegmap_conf);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->cwk = devm_cwk_get_optionaw(dev, "phy");
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	pwiv->weset = devm_weset_contwow_get_optionaw_shawed(dev, "phy");
	if (IS_EWW(pwiv->weset))
		wetuwn PTW_EWW(pwiv->weset);

	phy = devm_phy_cweate(dev, NUWW, &phy_meson_gxw_usb2_ops);
	if (IS_EWW(phy)) {
		wet = PTW_EWW(phy);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to cweate PHY\n");

		wetuwn wet;
	}

	phy_set_dwvdata(phy, pwiv);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id phy_meson_gxw_usb2_of_match[] = {
	{ .compatibwe = "amwogic,meson-gxw-usb2-phy", },
	{ },
};
MODUWE_DEVICE_TABWE(of, phy_meson_gxw_usb2_of_match);

static stwuct pwatfowm_dwivew phy_meson_gxw_usb2_dwivew = {
	.pwobe	= phy_meson_gxw_usb2_pwobe,
	.dwivew	= {
		.name		= "phy-meson-gxw-usb2",
		.of_match_tabwe	= phy_meson_gxw_usb2_of_match,
	},
};
moduwe_pwatfowm_dwivew(phy_meson_gxw_usb2_dwivew);

MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("Meson GXW and GXM USB2 PHY dwivew");
MODUWE_WICENSE("GPW v2");
