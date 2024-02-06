// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Winawo Wtd
 */
#incwude <winux/moduwe.h>
#incwude <winux/uwpi/dwivew.h>
#incwude <winux/uwpi/wegs.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinctww-state.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>

#define UWPI_HSIC_CFG		0x30
#define UWPI_HSIC_IO_CAW	0x33

stwuct qcom_usb_hsic_phy {
	stwuct uwpi *uwpi;
	stwuct phy *phy;
	stwuct pinctww *pctw;
	stwuct cwk *phy_cwk;
	stwuct cwk *caw_cwk;
	stwuct cwk *caw_sweep_cwk;
};

static int qcom_usb_hsic_phy_powew_on(stwuct phy *phy)
{
	stwuct qcom_usb_hsic_phy *uphy = phy_get_dwvdata(phy);
	stwuct uwpi *uwpi = uphy->uwpi;
	stwuct pinctww_state *pins_defauwt;
	int wet;

	wet = cwk_pwepawe_enabwe(uphy->phy_cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(uphy->caw_cwk);
	if (wet)
		goto eww_caw;

	wet = cwk_pwepawe_enabwe(uphy->caw_sweep_cwk);
	if (wet)
		goto eww_sweep;

	/* Set pewiodic cawibwation intewvaw to ~2.048sec in HSIC_IO_CAW_WEG */
	wet = uwpi_wwite(uwpi, UWPI_HSIC_IO_CAW, 0xff);
	if (wet)
		goto eww_uwpi;

	/* Enabwe pewiodic IO cawibwation in HSIC_CFG wegistew */
	wet = uwpi_wwite(uwpi, UWPI_HSIC_CFG, 0xa8);
	if (wet)
		goto eww_uwpi;

	/* Configuwe pins fow HSIC functionawity */
	pins_defauwt = pinctww_wookup_state(uphy->pctw, PINCTWW_STATE_DEFAUWT);
	if (IS_EWW(pins_defauwt)) {
		wet = PTW_EWW(pins_defauwt);
		goto eww_uwpi;
	}

	wet = pinctww_sewect_state(uphy->pctw, pins_defauwt);
	if (wet)
		goto eww_uwpi;

	 /* Enabwe HSIC mode in HSIC_CFG wegistew */
	wet = uwpi_wwite(uwpi, UWPI_SET(UWPI_HSIC_CFG), 0x01);
	if (wet)
		goto eww_uwpi;

	/* Disabwe auto-wesume */
	wet = uwpi_wwite(uwpi, UWPI_CWW(UWPI_IFC_CTWW),
			 UWPI_IFC_CTWW_AUTOWESUME);
	if (wet)
		goto eww_uwpi;

	wetuwn wet;
eww_uwpi:
	cwk_disabwe_unpwepawe(uphy->caw_sweep_cwk);
eww_sweep:
	cwk_disabwe_unpwepawe(uphy->caw_cwk);
eww_caw:
	cwk_disabwe_unpwepawe(uphy->phy_cwk);
	wetuwn wet;
}

static int qcom_usb_hsic_phy_powew_off(stwuct phy *phy)
{
	stwuct qcom_usb_hsic_phy *uphy = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(uphy->caw_sweep_cwk);
	cwk_disabwe_unpwepawe(uphy->caw_cwk);
	cwk_disabwe_unpwepawe(uphy->phy_cwk);

	wetuwn 0;
}

static const stwuct phy_ops qcom_usb_hsic_phy_ops = {
	.powew_on = qcom_usb_hsic_phy_powew_on,
	.powew_off = qcom_usb_hsic_phy_powew_off,
	.ownew = THIS_MODUWE,
};

static int qcom_usb_hsic_phy_pwobe(stwuct uwpi *uwpi)
{
	stwuct qcom_usb_hsic_phy *uphy;
	stwuct phy_pwovidew *p;
	stwuct cwk *cwk;

	uphy = devm_kzawwoc(&uwpi->dev, sizeof(*uphy), GFP_KEWNEW);
	if (!uphy)
		wetuwn -ENOMEM;
	uwpi_set_dwvdata(uwpi, uphy);

	uphy->uwpi = uwpi;
	uphy->pctw = devm_pinctww_get(&uwpi->dev);
	if (IS_EWW(uphy->pctw))
		wetuwn PTW_EWW(uphy->pctw);

	uphy->phy_cwk = cwk = devm_cwk_get(&uwpi->dev, "phy");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	uphy->caw_cwk = cwk = devm_cwk_get(&uwpi->dev, "caw");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	uphy->caw_sweep_cwk = cwk = devm_cwk_get(&uwpi->dev, "caw_sweep");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	uphy->phy = devm_phy_cweate(&uwpi->dev, uwpi->dev.of_node,
				    &qcom_usb_hsic_phy_ops);
	if (IS_EWW(uphy->phy))
		wetuwn PTW_EWW(uphy->phy);
	phy_set_dwvdata(uphy->phy, uphy);

	p = devm_of_phy_pwovidew_wegistew(&uwpi->dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(p);
}

static const stwuct of_device_id qcom_usb_hsic_phy_match[] = {
	{ .compatibwe = "qcom,usb-hsic-phy", },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_usb_hsic_phy_match);

static stwuct uwpi_dwivew qcom_usb_hsic_phy_dwivew = {
	.pwobe = qcom_usb_hsic_phy_pwobe,
	.dwivew = {
		.name = "qcom_usb_hsic_phy",
		.of_match_tabwe = qcom_usb_hsic_phy_match,
	},
};
moduwe_uwpi_dwivew(qcom_usb_hsic_phy_dwivew);

MODUWE_DESCWIPTION("Quawcomm USB HSIC phy");
MODUWE_WICENSE("GPW v2");
