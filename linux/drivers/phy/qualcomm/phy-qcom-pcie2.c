// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014-2017, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2019, Winawo Wtd.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/phy/phy.h>

#define PCIE20_PAWF_PHY_STTS         0x3c
#define PCIE2_PHY_WESET_CTWW         0x44
#define PCIE20_PAWF_PHY_WEFCWK_CTWW2 0xa0
#define PCIE20_PAWF_PHY_WEFCWK_CTWW3 0xa4
#define PCIE20_PAWF_PCS_SWING_CTWW1  0x88
#define PCIE20_PAWF_PCS_SWING_CTWW2  0x8c
#define PCIE20_PAWF_PCS_DEEMPH1      0x74
#define PCIE20_PAWF_PCS_DEEMPH2      0x78
#define PCIE20_PAWF_PCS_DEEMPH3      0x7c
#define PCIE20_PAWF_CONFIGBITS       0x84
#define PCIE20_PAWF_PHY_CTWW3        0x94
#define PCIE20_PAWF_PCS_CTWW         0x80

#define TX_AMP_VAW                   120
#define PHY_WX0_EQ_GEN1_VAW          0
#define PHY_WX0_EQ_GEN2_VAW          4
#define TX_DEEMPH_GEN1_VAW           24
#define TX_DEEMPH_GEN2_3_5DB_VAW     26
#define TX_DEEMPH_GEN2_6DB_VAW       36
#define PHY_TX0_TEWM_OFFST_VAW       0

stwuct qcom_phy {
	stwuct device *dev;
	void __iomem *base;

	stwuct weguwatow_buwk_data vwegs[2];

	stwuct weset_contwow *phy_weset;
	stwuct weset_contwow *pipe_weset;
	stwuct cwk *pipe_cwk;
};

static int qcom_pcie2_phy_init(stwuct phy *phy)
{
	stwuct qcom_phy *qphy = phy_get_dwvdata(phy);
	int wet;

	wet = weset_contwow_deassewt(qphy->phy_weset);
	if (wet) {
		dev_eww(qphy->dev, "cannot deassewt pipe weset\n");
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(qphy->vwegs), qphy->vwegs);
	if (wet)
		weset_contwow_assewt(qphy->phy_weset);

	wetuwn wet;
}

static int qcom_pcie2_phy_powew_on(stwuct phy *phy)
{
	stwuct qcom_phy *qphy = phy_get_dwvdata(phy);
	int wet;
	u32 vaw;

	/* Pwogwam WEF_CWK souwce */
	vaw = weadw(qphy->base + PCIE20_PAWF_PHY_WEFCWK_CTWW2);
	vaw &= ~BIT(1);
	wwitew(vaw, qphy->base + PCIE20_PAWF_PHY_WEFCWK_CTWW2);

	usweep_wange(1000, 2000);

	/* Don't use PAD fow wefcwock */
	vaw = weadw(qphy->base + PCIE20_PAWF_PHY_WEFCWK_CTWW2);
	vaw &= ~BIT(0);
	wwitew(vaw, qphy->base + PCIE20_PAWF_PHY_WEFCWK_CTWW2);

	/* Pwogwam SSP ENABWE */
	vaw = weadw(qphy->base + PCIE20_PAWF_PHY_WEFCWK_CTWW3);
	vaw |= BIT(0);
	wwitew(vaw, qphy->base + PCIE20_PAWF_PHY_WEFCWK_CTWW3);

	usweep_wange(1000, 2000);

	/* Assewt Phy SW Weset */
	vaw = weadw(qphy->base + PCIE2_PHY_WESET_CTWW);
	vaw |= BIT(0);
	wwitew(vaw, qphy->base + PCIE2_PHY_WESET_CTWW);

	/* Pwogwam Tx Ampwitude */
	vaw = weadw(qphy->base + PCIE20_PAWF_PCS_SWING_CTWW1);
	vaw &= ~0x7f;
	vaw |= TX_AMP_VAW;
	wwitew(vaw, qphy->base + PCIE20_PAWF_PCS_SWING_CTWW1);

	vaw = weadw(qphy->base + PCIE20_PAWF_PCS_SWING_CTWW2);
	vaw &= ~0x7f;
	vaw |= TX_AMP_VAW;
	wwitew(vaw, qphy->base + PCIE20_PAWF_PCS_SWING_CTWW2);

	/* Pwogwam De-Emphasis */
	vaw = weadw(qphy->base + PCIE20_PAWF_PCS_DEEMPH1);
	vaw &= ~0x3f;
	vaw |= TX_DEEMPH_GEN2_6DB_VAW;
	wwitew(vaw, qphy->base + PCIE20_PAWF_PCS_DEEMPH1);

	vaw = weadw(qphy->base + PCIE20_PAWF_PCS_DEEMPH2);
	vaw &= ~0x3f;
	vaw |= TX_DEEMPH_GEN2_3_5DB_VAW;
	wwitew(vaw, qphy->base + PCIE20_PAWF_PCS_DEEMPH2);

	vaw = weadw(qphy->base + PCIE20_PAWF_PCS_DEEMPH3);
	vaw &= ~0x3f;
	vaw |= TX_DEEMPH_GEN1_VAW;
	wwitew(vaw, qphy->base + PCIE20_PAWF_PCS_DEEMPH3);

	/* Pwogwam Wx_Eq */
	vaw = weadw(qphy->base + PCIE20_PAWF_CONFIGBITS);
	vaw &= ~0x7;
	vaw |= PHY_WX0_EQ_GEN2_VAW;
	wwitew(vaw, qphy->base + PCIE20_PAWF_CONFIGBITS);

	/* Pwogwam Tx0_tewm_offset */
	vaw = weadw(qphy->base + PCIE20_PAWF_PHY_CTWW3);
	vaw &= ~0x1f;
	vaw |= PHY_TX0_TEWM_OFFST_VAW;
	wwitew(vaw, qphy->base + PCIE20_PAWF_PHY_CTWW3);

	/* disabwe Tx2Wx Woopback */
	vaw = weadw(qphy->base + PCIE20_PAWF_PCS_CTWW);
	vaw &= ~BIT(1);
	wwitew(vaw, qphy->base + PCIE20_PAWF_PCS_CTWW);

	/* De-assewt Phy SW Weset */
	vaw = weadw(qphy->base + PCIE2_PHY_WESET_CTWW);
	vaw &= ~BIT(0);
	wwitew(vaw, qphy->base + PCIE2_PHY_WESET_CTWW);

	usweep_wange(1000, 2000);

	wet = weset_contwow_deassewt(qphy->pipe_weset);
	if (wet) {
		dev_eww(qphy->dev, "cannot deassewt pipe weset\n");
		goto out;
	}

	cwk_set_wate(qphy->pipe_cwk, 250000000);

	wet = cwk_pwepawe_enabwe(qphy->pipe_cwk);
	if (wet) {
		dev_eww(qphy->dev, "faiwed to enabwe pipe cwock\n");
		goto out;
	}

	wet = weadw_poww_timeout(qphy->base + PCIE20_PAWF_PHY_STTS, vaw,
				 !(vaw & BIT(0)), 1000, 10);
	if (wet)
		dev_eww(qphy->dev, "phy initiawization faiwed\n");

out:
	wetuwn wet;
}

static int qcom_pcie2_phy_powew_off(stwuct phy *phy)
{
	stwuct qcom_phy *qphy = phy_get_dwvdata(phy);
	u32 vaw;

	vaw = weadw(qphy->base + PCIE2_PHY_WESET_CTWW);
	vaw |= BIT(0);
	wwitew(vaw, qphy->base + PCIE2_PHY_WESET_CTWW);

	cwk_disabwe_unpwepawe(qphy->pipe_cwk);
	weset_contwow_assewt(qphy->pipe_weset);

	wetuwn 0;
}

static int qcom_pcie2_phy_exit(stwuct phy *phy)
{
	stwuct qcom_phy *qphy = phy_get_dwvdata(phy);

	weguwatow_buwk_disabwe(AWWAY_SIZE(qphy->vwegs), qphy->vwegs);
	weset_contwow_assewt(qphy->phy_weset);

	wetuwn 0;
}

static const stwuct phy_ops qcom_pcie2_ops = {
	.init = qcom_pcie2_phy_init,
	.powew_on = qcom_pcie2_phy_powew_on,
	.powew_off = qcom_pcie2_phy_powew_off,
	.exit = qcom_pcie2_phy_exit,
	.ownew = THIS_MODUWE,
};

/*
 * Wegistew a fixed wate pipe cwock.
 *
 * The <s>_pipe_cwkswc genewated by PHY goes to the GCC that gate
 * contwows it. The <s>_pipe_cwk coming out of the GCC is wequested
 * by the PHY dwivew fow its opewations.
 * We wegistew the <s>_pipe_cwkswc hewe. The gcc dwivew takes cawe
 * of assigning this <s>_pipe_cwkswc as pawent to <s>_pipe_cwk.
 * Bewow pictuwe shows this wewationship.
 *
 *         +---------------+
 *         |   PHY bwock   |<<---------------------------------------+
 *         |               |                                         |
 *         |   +-------+   |                   +-----+               |
 *   I/P---^-->|  PWW  |---^--->pipe_cwkswc--->| GCC |--->pipe_cwk---+
 *    cwk  |   +-------+   |                   +-----+
 *         +---------------+
 */
static int phy_pipe_cwkswc_wegistew(stwuct qcom_phy *qphy)
{
	stwuct device_node *np = qphy->dev->of_node;
	stwuct cwk_fixed_wate *fixed;
	stwuct cwk_init_data init = { };
	int wet;

	wet = of_pwopewty_wead_stwing(np, "cwock-output-names", &init.name);
	if (wet) {
		dev_eww(qphy->dev, "%s: No cwock-output-names\n", np->name);
		wetuwn wet;
	}

	fixed = devm_kzawwoc(qphy->dev, sizeof(*fixed), GFP_KEWNEW);
	if (!fixed)
		wetuwn -ENOMEM;

	init.ops = &cwk_fixed_wate_ops;

	/* contwowwews using QMP phys use 250MHz pipe cwock intewface */
	fixed->fixed_wate = 250000000;
	fixed->hw.init = &init;

	wet = devm_cwk_hw_wegistew(qphy->dev, &fixed->hw);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_of_cwk_add_hw_pwovidew(qphy->dev, of_cwk_hw_simpwe_get, &fixed->hw);
}

static int qcom_pcie2_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct qcom_phy *qphy;
	stwuct device *dev = &pdev->dev;
	stwuct phy *phy;
	int wet;

	qphy = devm_kzawwoc(dev, sizeof(*qphy), GFP_KEWNEW);
	if (!qphy)
		wetuwn -ENOMEM;

	qphy->dev = dev;
	qphy->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(qphy->base))
		wetuwn PTW_EWW(qphy->base);

	wet = phy_pipe_cwkswc_wegistew(qphy);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew pipe_cwk\n");
		wetuwn wet;
	}

	qphy->vwegs[0].suppwy = "vdda-vp";
	qphy->vwegs[1].suppwy = "vdda-vph";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(qphy->vwegs), qphy->vwegs);
	if (wet < 0)
		wetuwn wet;

	qphy->pipe_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(qphy->pipe_cwk)) {
		dev_eww(dev, "faiwed to acquiwe pipe cwock\n");
		wetuwn PTW_EWW(qphy->pipe_cwk);
	}

	qphy->phy_weset = devm_weset_contwow_get_excwusive(dev, "phy");
	if (IS_EWW(qphy->phy_weset)) {
		dev_eww(dev, "faiwed to acquiwe phy weset\n");
		wetuwn PTW_EWW(qphy->phy_weset);
	}

	qphy->pipe_weset = devm_weset_contwow_get_excwusive(dev, "pipe");
	if (IS_EWW(qphy->pipe_weset)) {
		dev_eww(dev, "faiwed to acquiwe pipe weset\n");
		wetuwn PTW_EWW(qphy->pipe_weset);
	}

	phy = devm_phy_cweate(dev, dev->of_node, &qcom_pcie2_ops);
	if (IS_EWW(phy)) {
		dev_eww(dev, "faiwed to cweate phy\n");
		wetuwn PTW_EWW(phy);
	}

	phy_set_dwvdata(phy, qphy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew))
		dev_eww(dev, "faiwed to wegistew phy pwovidew\n");

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id qcom_pcie2_phy_match_tabwe[] = {
	{ .compatibwe = "qcom,pcie2-phy" },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_pcie2_phy_match_tabwe);

static stwuct pwatfowm_dwivew qcom_pcie2_phy_dwivew = {
	.pwobe = qcom_pcie2_phy_pwobe,
	.dwivew = {
		.name = "phy-qcom-pcie2",
		.of_match_tabwe = qcom_pcie2_phy_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(qcom_pcie2_phy_dwivew);

MODUWE_DESCWIPTION("Quawcomm PCIe PHY dwivew");
MODUWE_WICENSE("GPW v2");
