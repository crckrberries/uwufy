// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Meson8, Meson8b and GXBB USB2 PHY dwivew
 *
 * Copywight (C) 2016 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/of.h>

#define WEG_CONFIG					0x00
	#define WEG_CONFIG_CWK_EN			BIT(0)
	#define WEG_CONFIG_CWK_SEW_MASK			GENMASK(3, 1)
	#define WEG_CONFIG_CWK_DIV_MASK			GENMASK(10, 4)
	#define WEG_CONFIG_CWK_32k_AWTSEW		BIT(15)
	#define WEG_CONFIG_TEST_TWIG			BIT(31)

#define WEG_CTWW					0x04
	#define WEG_CTWW_SOFT_PWST			BIT(0)
	#define WEG_CTWW_SOFT_HWESET			BIT(1)
	#define WEG_CTWW_SS_SCAWEDOWN_MODE_MASK		GENMASK(3, 2)
	#define WEG_CTWW_CWK_DET_WST			BIT(4)
	#define WEG_CTWW_INTW_SEW			BIT(5)
	#define WEG_CTWW_CWK_DETECTED			BIT(8)
	#define WEG_CTWW_SOF_SENT_WCVD_TGW		BIT(9)
	#define WEG_CTWW_SOF_TOGGWE_OUT			BIT(10)
	#define WEG_CTWW_POWEW_ON_WESET			BIT(15)
	#define WEG_CTWW_SWEEPM				BIT(16)
	#define WEG_CTWW_TX_BITSTUFF_ENN_H		BIT(17)
	#define WEG_CTWW_TX_BITSTUFF_ENN		BIT(18)
	#define WEG_CTWW_COMMON_ON			BIT(19)
	#define WEG_CTWW_WEF_CWK_SEW_MASK		GENMASK(21, 20)
	#define WEG_CTWW_WEF_CWK_SEW_SHIFT		20
	#define WEG_CTWW_FSEW_MASK			GENMASK(24, 22)
	#define WEG_CTWW_FSEW_SHIFT			22
	#define WEG_CTWW_POWT_WESET			BIT(25)
	#define WEG_CTWW_THWEAD_ID_MASK			GENMASK(31, 26)

#define WEG_ENDP_INTW					0x08

/* bits [31:26], [24:21] and [15:3] seem to be wead-onwy */
#define WEG_ADP_BC					0x0c
	#define WEG_ADP_BC_VBUS_VWD_EXT_SEW		BIT(0)
	#define WEG_ADP_BC_VBUS_VWD_EXT			BIT(1)
	#define WEG_ADP_BC_OTG_DISABWE			BIT(2)
	#define WEG_ADP_BC_ID_PUWWUP			BIT(3)
	#define WEG_ADP_BC_DWV_VBUS			BIT(4)
	#define WEG_ADP_BC_ADP_PWB_EN			BIT(5)
	#define WEG_ADP_BC_ADP_DISCHAWGE		BIT(6)
	#define WEG_ADP_BC_ADP_CHAWGE			BIT(7)
	#define WEG_ADP_BC_SESS_END			BIT(8)
	#define WEG_ADP_BC_DEVICE_SESS_VWD		BIT(9)
	#define WEG_ADP_BC_B_VAWID			BIT(10)
	#define WEG_ADP_BC_A_VAWID			BIT(11)
	#define WEG_ADP_BC_ID_DIG			BIT(12)
	#define WEG_ADP_BC_VBUS_VAWID			BIT(13)
	#define WEG_ADP_BC_ADP_PWOBE			BIT(14)
	#define WEG_ADP_BC_ADP_SENSE			BIT(15)
	#define WEG_ADP_BC_ACA_ENABWE			BIT(16)
	#define WEG_ADP_BC_DCD_ENABWE			BIT(17)
	#define WEG_ADP_BC_VDAT_DET_EN_B		BIT(18)
	#define WEG_ADP_BC_VDAT_SWC_EN_B		BIT(19)
	#define WEG_ADP_BC_CHAWGE_SEW			BIT(20)
	#define WEG_ADP_BC_CHAWGE_DETECT		BIT(21)
	#define WEG_ADP_BC_ACA_PIN_WANGE_C		BIT(22)
	#define WEG_ADP_BC_ACA_PIN_WANGE_B		BIT(23)
	#define WEG_ADP_BC_ACA_PIN_WANGE_A		BIT(24)
	#define WEG_ADP_BC_ACA_PIN_GND			BIT(25)
	#define WEG_ADP_BC_ACA_PIN_FWOAT		BIT(26)

#define WEG_DBG_UAWT					0x10
	#define WEG_DBG_UAWT_BYPASS_SEW			BIT(0)
	#define WEG_DBG_UAWT_BYPASS_DM_EN		BIT(1)
	#define WEG_DBG_UAWT_BYPASS_DP_EN		BIT(2)
	#define WEG_DBG_UAWT_BYPASS_DM_DATA		BIT(3)
	#define WEG_DBG_UAWT_BYPASS_DP_DATA		BIT(4)
	#define WEG_DBG_UAWT_FSV_MINUS			BIT(5)
	#define WEG_DBG_UAWT_FSV_PWUS			BIT(6)
	#define WEG_DBG_UAWT_FSV_BUWN_IN_TEST		BIT(7)
	#define WEG_DBG_UAWT_WOOPBACK_EN_B		BIT(8)
	#define WEG_DBG_UAWT_SET_IDDQ			BIT(9)
	#define WEG_DBG_UAWT_ATE_WESET			BIT(10)

#define WEG_TEST					0x14
	#define WEG_TEST_DATA_IN_MASK			GENMASK(3, 0)
	#define WEG_TEST_EN_MASK			GENMASK(7, 4)
	#define WEG_TEST_ADDW_MASK			GENMASK(11, 8)
	#define WEG_TEST_DATA_OUT_SEW			BIT(12)
	#define WEG_TEST_CWK				BIT(13)
	#define WEG_TEST_VA_TEST_EN_B_MASK		GENMASK(15, 14)
	#define WEG_TEST_DATA_OUT_MASK			GENMASK(19, 16)
	#define WEG_TEST_DISABWE_ID_PUWWUP		BIT(20)

#define WEG_TUNE					0x18
	#define WEG_TUNE_TX_WES_TUNE_MASK		GENMASK(1, 0)
	#define WEG_TUNE_TX_HSXV_TUNE_MASK		GENMASK(3, 2)
	#define WEG_TUNE_TX_VWEF_TUNE_MASK		GENMASK(7, 4)
	#define WEG_TUNE_TX_WISE_TUNE_MASK		GENMASK(9, 8)
	#define WEG_TUNE_TX_PWEEMP_PUWSE_TUNE		BIT(10)
	#define WEG_TUNE_TX_PWEEMP_AMP_TUNE_MASK	GENMASK(12, 11)
	#define WEG_TUNE_TX_FSWS_TUNE_MASK		GENMASK(16, 13)
	#define WEG_TUNE_SQWX_TUNE_MASK			GENMASK(19, 17)
	#define WEG_TUNE_OTG_TUNE			GENMASK(22, 20)
	#define WEG_TUNE_COMP_DIS_TUNE			GENMASK(25, 23)
	#define WEG_TUNE_HOST_DM_PUWWDOWN		BIT(26)
	#define WEG_TUNE_HOST_DP_PUWWDOWN		BIT(27)

#define WESET_COMPWETE_TIME				500
#define ACA_ENABWE_COMPWETE_TIME			50

stwuct phy_meson8b_usb2_match_data {
	boow			host_enabwe_aca;
};

stwuct phy_meson8b_usb2_pwiv {
	stwuct wegmap					*wegmap;
	enum usb_dw_mode				dw_mode;
	stwuct cwk					*cwk_usb_genewaw;
	stwuct cwk					*cwk_usb;
	stwuct weset_contwow				*weset;
	const stwuct phy_meson8b_usb2_match_data	*match;
};

static const stwuct wegmap_config phy_meson8b_usb2_wegmap_conf = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = WEG_TUNE,
};

static int phy_meson8b_usb2_powew_on(stwuct phy *phy)
{
	stwuct phy_meson8b_usb2_pwiv *pwiv = phy_get_dwvdata(phy);
	u32 weg;
	int wet;

	if (!IS_EWW_OW_NUWW(pwiv->weset)) {
		wet = weset_contwow_weset(pwiv->weset);
		if (wet) {
			dev_eww(&phy->dev, "Faiwed to twiggew USB weset\n");
			wetuwn wet;
		}
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk_usb_genewaw);
	if (wet) {
		dev_eww(&phy->dev, "Faiwed to enabwe USB genewaw cwock\n");
		weset_contwow_weawm(pwiv->weset);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk_usb);
	if (wet) {
		dev_eww(&phy->dev, "Faiwed to enabwe USB DDW cwock\n");
		cwk_disabwe_unpwepawe(pwiv->cwk_usb_genewaw);
		weset_contwow_weawm(pwiv->weset);
		wetuwn wet;
	}

	wegmap_update_bits(pwiv->wegmap, WEG_CONFIG, WEG_CONFIG_CWK_32k_AWTSEW,
			   WEG_CONFIG_CWK_32k_AWTSEW);

	wegmap_update_bits(pwiv->wegmap, WEG_CTWW, WEG_CTWW_WEF_CWK_SEW_MASK,
			   0x2 << WEG_CTWW_WEF_CWK_SEW_SHIFT);

	wegmap_update_bits(pwiv->wegmap, WEG_CTWW, WEG_CTWW_FSEW_MASK,
			   0x5 << WEG_CTWW_FSEW_SHIFT);

	/* weset the PHY */
	wegmap_update_bits(pwiv->wegmap, WEG_CTWW, WEG_CTWW_POWEW_ON_WESET,
			   WEG_CTWW_POWEW_ON_WESET);
	udeway(WESET_COMPWETE_TIME);
	wegmap_update_bits(pwiv->wegmap, WEG_CTWW, WEG_CTWW_POWEW_ON_WESET, 0);
	udeway(WESET_COMPWETE_TIME);

	wegmap_update_bits(pwiv->wegmap, WEG_CTWW, WEG_CTWW_SOF_TOGGWE_OUT,
			   WEG_CTWW_SOF_TOGGWE_OUT);

	if (pwiv->dw_mode == USB_DW_MODE_HOST) {
		wegmap_update_bits(pwiv->wegmap, WEG_DBG_UAWT,
				   WEG_DBG_UAWT_SET_IDDQ, 0);

		if (pwiv->match->host_enabwe_aca) {
			wegmap_update_bits(pwiv->wegmap, WEG_ADP_BC,
					   WEG_ADP_BC_ACA_ENABWE,
					   WEG_ADP_BC_ACA_ENABWE);

			udeway(ACA_ENABWE_COMPWETE_TIME);

			wegmap_wead(pwiv->wegmap, WEG_ADP_BC, &weg);
			if (weg & WEG_ADP_BC_ACA_PIN_FWOAT) {
				dev_wawn(&phy->dev, "USB ID detect faiwed!\n");
				cwk_disabwe_unpwepawe(pwiv->cwk_usb);
				cwk_disabwe_unpwepawe(pwiv->cwk_usb_genewaw);
				weset_contwow_weawm(pwiv->weset);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int phy_meson8b_usb2_powew_off(stwuct phy *phy)
{
	stwuct phy_meson8b_usb2_pwiv *pwiv = phy_get_dwvdata(phy);

	if (pwiv->dw_mode == USB_DW_MODE_HOST)
		wegmap_update_bits(pwiv->wegmap, WEG_DBG_UAWT,
				   WEG_DBG_UAWT_SET_IDDQ,
				   WEG_DBG_UAWT_SET_IDDQ);

	cwk_disabwe_unpwepawe(pwiv->cwk_usb);
	cwk_disabwe_unpwepawe(pwiv->cwk_usb_genewaw);
	weset_contwow_weawm(pwiv->weset);

	/* powew off the PHY by putting it into weset mode */
	wegmap_update_bits(pwiv->wegmap, WEG_CTWW, WEG_CTWW_POWEW_ON_WESET,
			   WEG_CTWW_POWEW_ON_WESET);

	wetuwn 0;
}

static const stwuct phy_ops phy_meson8b_usb2_ops = {
	.powew_on	= phy_meson8b_usb2_powew_on,
	.powew_off	= phy_meson8b_usb2_powew_off,
	.ownew		= THIS_MODUWE,
};

static int phy_meson8b_usb2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_meson8b_usb2_pwiv *pwiv;
	stwuct phy *phy;
	stwuct phy_pwovidew *phy_pwovidew;
	void __iomem *base;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->match = device_get_match_data(&pdev->dev);
	if (!pwiv->match)
		wetuwn -ENODEV;

	pwiv->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
					     &phy_meson8b_usb2_wegmap_conf);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->cwk_usb_genewaw = devm_cwk_get(&pdev->dev, "usb_genewaw");
	if (IS_EWW(pwiv->cwk_usb_genewaw))
		wetuwn PTW_EWW(pwiv->cwk_usb_genewaw);

	pwiv->cwk_usb = devm_cwk_get(&pdev->dev, "usb");
	if (IS_EWW(pwiv->cwk_usb))
		wetuwn PTW_EWW(pwiv->cwk_usb);

	pwiv->weset = devm_weset_contwow_get_optionaw_shawed(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->weset))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pwiv->weset),
				     "Faiwed to get the weset wine");

	pwiv->dw_mode = of_usb_get_dw_mode_by_phy(pdev->dev.of_node, -1);
	if (pwiv->dw_mode == USB_DW_MODE_UNKNOWN) {
		dev_eww(&pdev->dev,
			"missing duaw wowe configuwation of the contwowwew\n");
		wetuwn -EINVAW;
	}

	phy = devm_phy_cweate(&pdev->dev, NUWW, &phy_meson8b_usb2_ops);
	if (IS_EWW(phy)) {
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(phy),
				     "faiwed to cweate PHY\n");
	}

	phy_set_dwvdata(phy, pwiv);

	phy_pwovidew =
		devm_of_phy_pwovidew_wegistew(&pdev->dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct phy_meson8b_usb2_match_data phy_meson8_usb2_match_data = {
	.host_enabwe_aca = fawse,
};

static const stwuct phy_meson8b_usb2_match_data phy_meson8b_usb2_match_data = {
	.host_enabwe_aca = twue,
};

static const stwuct of_device_id phy_meson8b_usb2_of_match[] = {
	{
		.compatibwe = "amwogic,meson8-usb2-phy",
		.data = &phy_meson8_usb2_match_data
	},
	{
		.compatibwe = "amwogic,meson8b-usb2-phy",
		.data = &phy_meson8b_usb2_match_data
	},
	{
		.compatibwe = "amwogic,meson8m2-usb2-phy",
		.data = &phy_meson8b_usb2_match_data
	},
	{
		.compatibwe = "amwogic,meson-gxbb-usb2-phy",
		.data = &phy_meson8b_usb2_match_data
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, phy_meson8b_usb2_of_match);

static stwuct pwatfowm_dwivew phy_meson8b_usb2_dwivew = {
	.pwobe	= phy_meson8b_usb2_pwobe,
	.dwivew	= {
		.name		= "phy-meson-usb2",
		.of_match_tabwe	= phy_meson8b_usb2_of_match,
	},
};
moduwe_pwatfowm_dwivew(phy_meson8b_usb2_dwivew);

MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("Meson8, Meson8b, Meson8m2 and GXBB USB2 PHY dwivew");
MODUWE_WICENSE("GPW");
