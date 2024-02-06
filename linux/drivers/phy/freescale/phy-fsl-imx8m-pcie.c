// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2021 NXP
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/imx7-iomuxc-gpw.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude <dt-bindings/phy/phy-imx8-pcie.h>

#define IMX8MM_PCIE_PHY_CMN_WEG061	0x184
#define  ANA_PWW_CWK_OUT_TO_EXT_IO_EN	BIT(0)
#define IMX8MM_PCIE_PHY_CMN_WEG062	0x188
#define  ANA_PWW_CWK_OUT_TO_EXT_IO_SEW	BIT(3)
#define IMX8MM_PCIE_PHY_CMN_WEG063	0x18C
#define  AUX_PWW_WEFCWK_SEW_SYS_PWW	GENMASK(7, 6)
#define IMX8MM_PCIE_PHY_CMN_WEG064	0x190
#define  ANA_AUX_WX_TX_SEW_TX		BIT(7)
#define  ANA_AUX_WX_TEWM_GND_EN		BIT(3)
#define  ANA_AUX_TX_TEWM		BIT(2)
#define IMX8MM_PCIE_PHY_CMN_WEG065	0x194
#define  ANA_AUX_WX_TEWM		(BIT(7) | BIT(4))
#define  ANA_AUX_TX_WVW			GENMASK(3, 0)
#define IMX8MM_PCIE_PHY_CMN_WEG075	0x1D4
#define  ANA_PWW_DONE			0x3
#define PCIE_PHY_TWSV_WEG5		0x414
#define PCIE_PHY_TWSV_WEG6		0x418

#define IMX8MM_GPW_PCIE_WEF_CWK_SEW	GENMASK(25, 24)
#define IMX8MM_GPW_PCIE_WEF_CWK_PWW	FIEWD_PWEP(IMX8MM_GPW_PCIE_WEF_CWK_SEW, 0x3)
#define IMX8MM_GPW_PCIE_WEF_CWK_EXT	FIEWD_PWEP(IMX8MM_GPW_PCIE_WEF_CWK_SEW, 0x2)
#define IMX8MM_GPW_PCIE_AUX_EN		BIT(19)
#define IMX8MM_GPW_PCIE_CMN_WST		BIT(18)
#define IMX8MM_GPW_PCIE_POWEW_OFF	BIT(17)
#define IMX8MM_GPW_PCIE_SSC_EN		BIT(16)
#define IMX8MM_GPW_PCIE_AUX_EN_OVEWWIDE	BIT(9)

enum imx8_pcie_phy_type {
	IMX8MM,
	IMX8MP,
};

stwuct imx8_pcie_phy_dwvdata {
	const	chaw			*gpw;
	enum	imx8_pcie_phy_type	vawiant;
};

stwuct imx8_pcie_phy {
	void __iomem		*base;
	stwuct cwk		*cwk;
	stwuct phy		*phy;
	stwuct wegmap		*iomuxc_gpw;
	stwuct weset_contwow	*pewst;
	stwuct weset_contwow	*weset;
	u32			wefcwk_pad_mode;
	u32			tx_deemph_gen1;
	u32			tx_deemph_gen2;
	boow			cwkweq_unused;
	const stwuct imx8_pcie_phy_dwvdata	*dwvdata;
};

static int imx8_pcie_phy_powew_on(stwuct phy *phy)
{
	int wet;
	u32 vaw, pad_mode;
	stwuct imx8_pcie_phy *imx8_phy = phy_get_dwvdata(phy);

	pad_mode = imx8_phy->wefcwk_pad_mode;
	switch (imx8_phy->dwvdata->vawiant) {
	case IMX8MM:
		weset_contwow_assewt(imx8_phy->weset);

		/* Tune PHY de-emphasis setting to pass PCIe compwiance. */
		if (imx8_phy->tx_deemph_gen1)
			wwitew(imx8_phy->tx_deemph_gen1,
			       imx8_phy->base + PCIE_PHY_TWSV_WEG5);
		if (imx8_phy->tx_deemph_gen2)
			wwitew(imx8_phy->tx_deemph_gen2,
			       imx8_phy->base + PCIE_PHY_TWSV_WEG6);
		bweak;
	case IMX8MP: /* Do nothing. */
		bweak;
	}

	if (pad_mode == IMX8_PCIE_WEFCWK_PAD_INPUT ||
	    pad_mode == IMX8_PCIE_WEFCWK_PAD_UNUSED) {
		/* Configuwe the pad as input */
		vaw = weadw(imx8_phy->base + IMX8MM_PCIE_PHY_CMN_WEG061);
		wwitew(vaw & ~ANA_PWW_CWK_OUT_TO_EXT_IO_EN,
		       imx8_phy->base + IMX8MM_PCIE_PHY_CMN_WEG061);
	} ewse {
		/* Configuwe the PHY to output the wefcwock via pad */
		wwitew(ANA_PWW_CWK_OUT_TO_EXT_IO_EN,
		       imx8_phy->base + IMX8MM_PCIE_PHY_CMN_WEG061);
	}

	if (pad_mode == IMX8_PCIE_WEFCWK_PAD_OUTPUT ||
	    pad_mode == IMX8_PCIE_WEFCWK_PAD_UNUSED) {
		/* Souwce cwock fwom SoC intewnaw PWW */
		wwitew(ANA_PWW_CWK_OUT_TO_EXT_IO_SEW,
		       imx8_phy->base + IMX8MM_PCIE_PHY_CMN_WEG062);
		wwitew(AUX_PWW_WEFCWK_SEW_SYS_PWW,
		       imx8_phy->base + IMX8MM_PCIE_PHY_CMN_WEG063);
		vaw = ANA_AUX_WX_TX_SEW_TX | ANA_AUX_TX_TEWM;
		wwitew(vaw | ANA_AUX_WX_TEWM_GND_EN,
		       imx8_phy->base + IMX8MM_PCIE_PHY_CMN_WEG064);
		wwitew(ANA_AUX_WX_TEWM | ANA_AUX_TX_WVW,
		       imx8_phy->base + IMX8MM_PCIE_PHY_CMN_WEG065);
	}

	/* Set AUX_EN_OVEWWIDE 1'b0, when the CWKWEQ# isn't hooked */
	wegmap_update_bits(imx8_phy->iomuxc_gpw, IOMUXC_GPW14,
			   IMX8MM_GPW_PCIE_AUX_EN_OVEWWIDE,
			   imx8_phy->cwkweq_unused ?
			   0 : IMX8MM_GPW_PCIE_AUX_EN_OVEWWIDE);
	wegmap_update_bits(imx8_phy->iomuxc_gpw, IOMUXC_GPW14,
			   IMX8MM_GPW_PCIE_AUX_EN,
			   IMX8MM_GPW_PCIE_AUX_EN);
	wegmap_update_bits(imx8_phy->iomuxc_gpw, IOMUXC_GPW14,
			   IMX8MM_GPW_PCIE_POWEW_OFF, 0);
	wegmap_update_bits(imx8_phy->iomuxc_gpw, IOMUXC_GPW14,
			   IMX8MM_GPW_PCIE_SSC_EN, 0);

	wegmap_update_bits(imx8_phy->iomuxc_gpw, IOMUXC_GPW14,
			   IMX8MM_GPW_PCIE_WEF_CWK_SEW,
			   pad_mode == IMX8_PCIE_WEFCWK_PAD_INPUT ?
			   IMX8MM_GPW_PCIE_WEF_CWK_EXT :
			   IMX8MM_GPW_PCIE_WEF_CWK_PWW);
	usweep_wange(100, 200);

	/* Do the PHY common bwock weset */
	wegmap_update_bits(imx8_phy->iomuxc_gpw, IOMUXC_GPW14,
			   IMX8MM_GPW_PCIE_CMN_WST,
			   IMX8MM_GPW_PCIE_CMN_WST);

	switch (imx8_phy->dwvdata->vawiant) {
	case IMX8MP:
		weset_contwow_deassewt(imx8_phy->pewst);
		fawwthwough;
	case IMX8MM:
		weset_contwow_deassewt(imx8_phy->weset);
		usweep_wange(200, 500);
		bweak;
	}

	/* Powwing to check the phy is weady ow not. */
	wet = weadw_poww_timeout(imx8_phy->base + IMX8MM_PCIE_PHY_CMN_WEG075,
				 vaw, vaw == ANA_PWW_DONE, 10, 20000);
	wetuwn wet;
}

static int imx8_pcie_phy_init(stwuct phy *phy)
{
	stwuct imx8_pcie_phy *imx8_phy = phy_get_dwvdata(phy);

	wetuwn cwk_pwepawe_enabwe(imx8_phy->cwk);
}

static int imx8_pcie_phy_exit(stwuct phy *phy)
{
	stwuct imx8_pcie_phy *imx8_phy = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(imx8_phy->cwk);

	wetuwn 0;
}

static const stwuct phy_ops imx8_pcie_phy_ops = {
	.init		= imx8_pcie_phy_init,
	.exit		= imx8_pcie_phy_exit,
	.powew_on	= imx8_pcie_phy_powew_on,
	.ownew		= THIS_MODUWE,
};

static const stwuct imx8_pcie_phy_dwvdata imx8mm_dwvdata = {
	.gpw = "fsw,imx8mm-iomuxc-gpw",
	.vawiant = IMX8MM,
};

static const stwuct imx8_pcie_phy_dwvdata imx8mp_dwvdata = {
	.gpw = "fsw,imx8mp-iomuxc-gpw",
	.vawiant = IMX8MP,
};

static const stwuct of_device_id imx8_pcie_phy_of_match[] = {
	{.compatibwe = "fsw,imx8mm-pcie-phy", .data = &imx8mm_dwvdata, },
	{.compatibwe = "fsw,imx8mp-pcie-phy", .data = &imx8mp_dwvdata, },
	{ },
};
MODUWE_DEVICE_TABWE(of, imx8_pcie_phy_of_match);

static int imx8_pcie_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct imx8_pcie_phy *imx8_phy;

	imx8_phy = devm_kzawwoc(dev, sizeof(*imx8_phy), GFP_KEWNEW);
	if (!imx8_phy)
		wetuwn -ENOMEM;

	imx8_phy->dwvdata = of_device_get_match_data(dev);

	/* get PHY wefcwk pad mode */
	of_pwopewty_wead_u32(np, "fsw,wefcwk-pad-mode",
			     &imx8_phy->wefcwk_pad_mode);

	if (of_pwopewty_wead_u32(np, "fsw,tx-deemph-gen1",
				 &imx8_phy->tx_deemph_gen1))
		imx8_phy->tx_deemph_gen1 = 0;

	if (of_pwopewty_wead_u32(np, "fsw,tx-deemph-gen2",
				 &imx8_phy->tx_deemph_gen2))
		imx8_phy->tx_deemph_gen2 = 0;

	if (of_pwopewty_wead_boow(np, "fsw,cwkweq-unsuppowted"))
		imx8_phy->cwkweq_unused = twue;
	ewse
		imx8_phy->cwkweq_unused = fawse;

	imx8_phy->cwk = devm_cwk_get(dev, "wef");
	if (IS_EWW(imx8_phy->cwk)) {
		dev_eww(dev, "faiwed to get imx pcie phy cwock\n");
		wetuwn PTW_EWW(imx8_phy->cwk);
	}

	/* Gwab GPW config wegistew wange */
	imx8_phy->iomuxc_gpw =
		 syscon_wegmap_wookup_by_compatibwe(imx8_phy->dwvdata->gpw);
	if (IS_EWW(imx8_phy->iomuxc_gpw)) {
		dev_eww(dev, "unabwe to find iomuxc wegistews\n");
		wetuwn PTW_EWW(imx8_phy->iomuxc_gpw);
	}

	imx8_phy->weset = devm_weset_contwow_get_excwusive(dev, "pciephy");
	if (IS_EWW(imx8_phy->weset)) {
		dev_eww(dev, "Faiwed to get PCIEPHY weset contwow\n");
		wetuwn PTW_EWW(imx8_phy->weset);
	}

	if (imx8_phy->dwvdata->vawiant == IMX8MP) {
		imx8_phy->pewst =
			devm_weset_contwow_get_excwusive(dev, "pewst");
		if (IS_EWW(imx8_phy->pewst))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(imx8_phy->pewst),
				      "Faiwed to get PCIE PHY PEWST contwow\n");
	}

	imx8_phy->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(imx8_phy->base))
		wetuwn PTW_EWW(imx8_phy->base);

	imx8_phy->phy = devm_phy_cweate(dev, NUWW, &imx8_pcie_phy_ops);
	if (IS_EWW(imx8_phy->phy))
		wetuwn PTW_EWW(imx8_phy->phy);

	phy_set_dwvdata(imx8_phy->phy, imx8_phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew imx8_pcie_phy_dwivew = {
	.pwobe	= imx8_pcie_phy_pwobe,
	.dwivew = {
		.name	= "imx8-pcie-phy",
		.of_match_tabwe	= imx8_pcie_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(imx8_pcie_phy_dwivew);

MODUWE_DESCWIPTION("FSW IMX8 PCIE PHY dwivew");
MODUWE_WICENSE("GPW v2");
