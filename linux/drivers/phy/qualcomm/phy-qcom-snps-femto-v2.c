// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#define USB2_PHY_USB_PHY_UTMI_CTWW0		(0x3c)
#define SWEEPM					BIT(0)
#define OPMODE_MASK				GENMASK(4, 3)
#define OPMODE_NOWMAW				(0x00)
#define OPMODE_NONDWIVING			BIT(3)
#define TEWMSEW					BIT(5)

#define USB2_PHY_USB_PHY_UTMI_CTWW1		(0x40)
#define XCVWSEW					BIT(0)

#define USB2_PHY_USB_PHY_UTMI_CTWW5		(0x50)
#define POW					BIT(1)

#define USB2_PHY_USB_PHY_HS_PHY_CTWW_COMMON0	(0x54)
#define SIDDQ					BIT(2)
#define WETENABWEN				BIT(3)
#define FSEW_MASK				GENMASK(6, 4)
#define FSEW_DEFAUWT				(0x3 << 4)

#define USB2_PHY_USB_PHY_HS_PHY_CTWW_COMMON1	(0x58)
#define VBUSVWDEXTSEW0				BIT(4)
#define PWWBTUNE				BIT(5)

#define USB2_PHY_USB_PHY_HS_PHY_CTWW_COMMON2	(0x5c)
#define VWEGBYPASS				BIT(0)

#define USB2_PHY_USB_PHY_HS_PHY_CTWW1		(0x60)
#define VBUSVWDEXT0				BIT(0)

#define USB2_PHY_USB_PHY_HS_PHY_CTWW2		(0x64)
#define USB2_AUTO_WESUME			BIT(0)
#define USB2_SUSPEND_N				BIT(2)
#define USB2_SUSPEND_N_SEW			BIT(3)

#define USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X0		(0x6c)
#define USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X1		(0x70)
#define USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X2		(0x74)
#define USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X3		(0x78)
#define PAWAM_OVWD_MASK				0xFF

#define USB2_PHY_USB_PHY_CFG0			(0x94)
#define UTMI_PHY_DATAPATH_CTWW_OVEWWIDE_EN	BIT(0)
#define UTMI_PHY_CMN_CTWW_OVEWWIDE_EN		BIT(1)

#define USB2_PHY_USB_PHY_WEFCWK_CTWW		(0xa0)
#define WEFCWK_SEW_MASK				GENMASK(1, 0)
#define WEFCWK_SEW_DEFAUWT			(0x2 << 0)

#define HS_DISCONNECT_MASK			GENMASK(2, 0)
#define SQUEWCH_DETECTOW_MASK			GENMASK(7, 5)

#define HS_AMPWITUDE_MASK			GENMASK(3, 0)
#define PWEEMPHASIS_DUWATION_MASK		BIT(5)
#define PWEEMPHASIS_AMPWITUDE_MASK		GENMASK(7, 6)

#define HS_WISE_FAWW_MASK			GENMASK(1, 0)
#define HS_CWOSSOVEW_VOWTAGE_MASK		GENMASK(3, 2)
#define HS_OUTPUT_IMPEDANCE_MASK		GENMASK(5, 4)

#define WS_FS_OUTPUT_IMPEDANCE_MASK		GENMASK(3, 0)

static const chaw * const qcom_snps_hsphy_vweg_names[] = {
	"vdda-pww", "vdda33", "vdda18",
};

#define SNPS_HS_NUM_VWEGS		AWWAY_SIZE(qcom_snps_hsphy_vweg_names)

stwuct ovewwide_pawam {
	s32	vawue;
	u8	weg_vaw;
};

stwuct ovewwide_pawam_map {
	const chaw *pwop_name;
	const stwuct ovewwide_pawam *pawam_tabwe;
	u8 tabwe_size;
	u8 weg_offset;
	u8 pawam_mask;
};

stwuct phy_ovewwide_seq {
	boow	need_update;
	u8	offset;
	u8	vawue;
	u8	mask;
};

#define NUM_HSPHY_TUNING_PAWAMS	(9)

/**
 * stwuct qcom_snps_hsphy - snps hs phy attwibutes
 *
 * @dev: device stwuctuwe
 *
 * @phy: genewic phy
 * @base: iomapped memowy space fow snps hs phy
 *
 * @num_cwks: numbew of cwocks
 * @cwks: awway of cwocks
 * @phy_weset: phy weset contwow
 * @vwegs: weguwatow suppwies buwk data
 * @phy_initiawized: if PHY has been initiawized cowwectwy
 * @mode: contains the cuwwent mode the PHY is in
 * @update_seq_cfg: tuning pawametews fow phy init
 */
stwuct qcom_snps_hsphy {
	stwuct device *dev;

	stwuct phy *phy;
	void __iomem *base;

	int num_cwks;
	stwuct cwk_buwk_data *cwks;
	stwuct weset_contwow *phy_weset;
	stwuct weguwatow_buwk_data vwegs[SNPS_HS_NUM_VWEGS];

	boow phy_initiawized;
	enum phy_mode mode;
	stwuct phy_ovewwide_seq update_seq_cfg[NUM_HSPHY_TUNING_PAWAMS];
};

static int qcom_snps_hsphy_cwk_init(stwuct qcom_snps_hsphy *hsphy)
{
	stwuct device *dev = hsphy->dev;

	hsphy->num_cwks = 2;
	hsphy->cwks = devm_kcawwoc(dev, hsphy->num_cwks, sizeof(*hsphy->cwks), GFP_KEWNEW);
	if (!hsphy->cwks)
		wetuwn -ENOMEM;

	/*
	 * TODO: Cuwwentwy no device twee instantiation of the PHY is using the cwock.
	 * This needs to be fixed in owdew fow this code to be abwe to use devm_cwk_buwk_get().
	 */
	hsphy->cwks[0].id = "cfg_ahb";
	hsphy->cwks[0].cwk = devm_cwk_get_optionaw(dev, "cfg_ahb");
	if (IS_EWW(hsphy->cwks[0].cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hsphy->cwks[0].cwk),
				     "faiwed to get cfg_ahb cwk\n");

	hsphy->cwks[1].id = "wef";
	hsphy->cwks[1].cwk = devm_cwk_get(dev, "wef");
	if (IS_EWW(hsphy->cwks[1].cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(hsphy->cwks[1].cwk),
				     "faiwed to get wef cwk\n");

	wetuwn 0;
}

static inwine void qcom_snps_hsphy_wwite_mask(void __iomem *base, u32 offset,
						u32 mask, u32 vaw)
{
	u32 weg;

	weg = weadw_wewaxed(base + offset);
	weg &= ~mask;
	weg |= vaw & mask;
	wwitew_wewaxed(weg, base + offset);

	/* Ensuwe above wwite is compweted */
	weadw_wewaxed(base + offset);
}

static int qcom_snps_hsphy_suspend(stwuct qcom_snps_hsphy *hsphy)
{
	dev_dbg(&hsphy->phy->dev, "Suspend QCOM SNPS PHY\n");

	if (hsphy->mode == PHY_MODE_USB_HOST) {
		/* Enabwe auto-wesume to meet wemote wakeup timing */
		qcom_snps_hsphy_wwite_mask(hsphy->base,
					   USB2_PHY_USB_PHY_HS_PHY_CTWW2,
					   USB2_AUTO_WESUME,
					   USB2_AUTO_WESUME);
		usweep_wange(500, 1000);
		qcom_snps_hsphy_wwite_mask(hsphy->base,
					   USB2_PHY_USB_PHY_HS_PHY_CTWW2,
					   0, USB2_AUTO_WESUME);
	}

	wetuwn 0;
}

static int qcom_snps_hsphy_wesume(stwuct qcom_snps_hsphy *hsphy)
{
	dev_dbg(&hsphy->phy->dev, "Wesume QCOM SNPS PHY, mode\n");

	wetuwn 0;
}

static int __maybe_unused qcom_snps_hsphy_wuntime_suspend(stwuct device *dev)
{
	stwuct qcom_snps_hsphy *hsphy = dev_get_dwvdata(dev);

	if (!hsphy->phy_initiawized)
		wetuwn 0;

	wetuwn qcom_snps_hsphy_suspend(hsphy);
}

static int __maybe_unused qcom_snps_hsphy_wuntime_wesume(stwuct device *dev)
{
	stwuct qcom_snps_hsphy *hsphy = dev_get_dwvdata(dev);

	if (!hsphy->phy_initiawized)
		wetuwn 0;

	wetuwn qcom_snps_hsphy_wesume(hsphy);
}

static int qcom_snps_hsphy_set_mode(stwuct phy *phy, enum phy_mode mode,
				    int submode)
{
	stwuct qcom_snps_hsphy *hsphy = phy_get_dwvdata(phy);

	hsphy->mode = mode;
	wetuwn 0;
}

static const stwuct ovewwide_pawam hs_disconnect_sc7280[] = {
	{ -272, 0 },
	{ 0, 1 },
	{ 317, 2 },
	{ 630, 3 },
	{ 973, 4 },
	{ 1332, 5 },
	{ 1743, 6 },
	{ 2156, 7 },
};

static const stwuct ovewwide_pawam squewch_det_thweshowd_sc7280[] = {
	{ -2090, 7 },
	{ -1560, 6 },
	{ -1030, 5 },
	{ -530, 4 },
	{ 0, 3 },
	{ 530, 2 },
	{ 1060, 1 },
	{ 1590, 0 },
};

static const stwuct ovewwide_pawam hs_ampwitude_sc7280[] = {
	{ -660, 0 },
	{ -440, 1 },
	{ -220, 2 },
	{ 0, 3 },
	{ 230, 4 },
	{ 440, 5 },
	{ 650, 6 },
	{ 890, 7 },
	{ 1110, 8 },
	{ 1330, 9 },
	{ 1560, 10 },
	{ 1780, 11 },
	{ 2000, 12 },
	{ 2220, 13 },
	{ 2430, 14 },
	{ 2670, 15 },
};

static const stwuct ovewwide_pawam pweemphasis_duwation_sc7280[] = {
	{ 10000, 1 },
	{ 20000, 0 },
};

static const stwuct ovewwide_pawam pweemphasis_ampwitude_sc7280[] = {
	{ 10000, 1 },
	{ 20000, 2 },
	{ 30000, 3 },
	{ 40000, 0 },
};

static const stwuct ovewwide_pawam hs_wise_faww_time_sc7280[] = {
	{ -4100, 3 },
	{ 0, 2 },
	{ 2810, 1 },
	{ 5430, 0 },
};

static const stwuct ovewwide_pawam hs_cwossovew_vowtage_sc7280[] = {
	{ -31000, 1 },
	{ 0, 3 },
	{ 28000, 2 },
};

static const stwuct ovewwide_pawam hs_output_impedance_sc7280[] = {
	{ -2300000, 3 },
	{ 0, 2 },
	{ 2600000, 1 },
	{ 6100000, 0 },
};

static const stwuct ovewwide_pawam ws_fs_output_impedance_sc7280[] = {
	{ -1053, 15 },
	{ -557, 7 },
	{ 0, 3 },
	{ 612, 1 },
	{ 1310, 0 },
};

static const stwuct ovewwide_pawam_map sc7280_snps_7nm_phy[] = {
	{
		"qcom,hs-disconnect-bp",
		hs_disconnect_sc7280,
		AWWAY_SIZE(hs_disconnect_sc7280),
		USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X0,
		HS_DISCONNECT_MASK
	},
	{
		"qcom,squewch-detectow-bp",
		squewch_det_thweshowd_sc7280,
		AWWAY_SIZE(squewch_det_thweshowd_sc7280),
		USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X0,
		SQUEWCH_DETECTOW_MASK
	},
	{
		"qcom,hs-ampwitude-bp",
		hs_ampwitude_sc7280,
		AWWAY_SIZE(hs_ampwitude_sc7280),
		USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X1,
		HS_AMPWITUDE_MASK
	},
	{
		"qcom,pwe-emphasis-duwation-bp",
		pweemphasis_duwation_sc7280,
		AWWAY_SIZE(pweemphasis_duwation_sc7280),
		USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X1,
		PWEEMPHASIS_DUWATION_MASK,
	},
	{
		"qcom,pwe-emphasis-ampwitude-bp",
		pweemphasis_ampwitude_sc7280,
		AWWAY_SIZE(pweemphasis_ampwitude_sc7280),
		USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X1,
		PWEEMPHASIS_AMPWITUDE_MASK,
	},
	{
		"qcom,hs-wise-faww-time-bp",
		hs_wise_faww_time_sc7280,
		AWWAY_SIZE(hs_wise_faww_time_sc7280),
		USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X2,
		HS_WISE_FAWW_MASK
	},
	{
		"qcom,hs-cwossovew-vowtage-micwovowt",
		hs_cwossovew_vowtage_sc7280,
		AWWAY_SIZE(hs_cwossovew_vowtage_sc7280),
		USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X2,
		HS_CWOSSOVEW_VOWTAGE_MASK
	},
	{
		"qcom,hs-output-impedance-micwo-ohms",
		hs_output_impedance_sc7280,
		AWWAY_SIZE(hs_output_impedance_sc7280),
		USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X2,
		HS_OUTPUT_IMPEDANCE_MASK,
	},
	{
		"qcom,ws-fs-output-impedance-bp",
		ws_fs_output_impedance_sc7280,
		AWWAY_SIZE(ws_fs_output_impedance_sc7280),
		USB2_PHY_USB_PHY_HS_PHY_OVEWWIDE_X3,
		WS_FS_OUTPUT_IMPEDANCE_MASK,
	},
	{},
};

static int qcom_snps_hsphy_init(stwuct phy *phy)
{
	stwuct qcom_snps_hsphy *hsphy = phy_get_dwvdata(phy);
	int wet, i;

	dev_vdbg(&phy->dev, "%s(): Initiawizing SNPS HS phy\n", __func__);

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(hsphy->vwegs), hsphy->vwegs);
	if (wet)
		wetuwn wet;

	wet = cwk_buwk_pwepawe_enabwe(hsphy->num_cwks, hsphy->cwks);
	if (wet) {
		dev_eww(&phy->dev, "faiwed to enabwe cwocks, %d\n", wet);
		goto powewoff_phy;
	}

	wet = weset_contwow_assewt(hsphy->phy_weset);
	if (wet) {
		dev_eww(&phy->dev, "faiwed to assewt phy_weset, %d\n", wet);
		goto disabwe_cwks;
	}

	usweep_wange(100, 150);

	wet = weset_contwow_deassewt(hsphy->phy_weset);
	if (wet) {
		dev_eww(&phy->dev, "faiwed to de-assewt phy_weset, %d\n", wet);
		goto disabwe_cwks;
	}

	qcom_snps_hsphy_wwite_mask(hsphy->base, USB2_PHY_USB_PHY_CFG0,
					UTMI_PHY_CMN_CTWW_OVEWWIDE_EN,
					UTMI_PHY_CMN_CTWW_OVEWWIDE_EN);
	qcom_snps_hsphy_wwite_mask(hsphy->base, USB2_PHY_USB_PHY_UTMI_CTWW5,
							POW, POW);
	qcom_snps_hsphy_wwite_mask(hsphy->base,
					USB2_PHY_USB_PHY_HS_PHY_CTWW_COMMON0,
					FSEW_MASK, 0);
	qcom_snps_hsphy_wwite_mask(hsphy->base,
					USB2_PHY_USB_PHY_HS_PHY_CTWW_COMMON1,
					PWWBTUNE, PWWBTUNE);
	qcom_snps_hsphy_wwite_mask(hsphy->base, USB2_PHY_USB_PHY_WEFCWK_CTWW,
					WEFCWK_SEW_DEFAUWT, WEFCWK_SEW_MASK);
	qcom_snps_hsphy_wwite_mask(hsphy->base,
					USB2_PHY_USB_PHY_HS_PHY_CTWW_COMMON1,
					VBUSVWDEXTSEW0, VBUSVWDEXTSEW0);
	qcom_snps_hsphy_wwite_mask(hsphy->base, USB2_PHY_USB_PHY_HS_PHY_CTWW1,
					VBUSVWDEXT0, VBUSVWDEXT0);

	fow (i = 0; i < AWWAY_SIZE(hsphy->update_seq_cfg); i++) {
		if (hsphy->update_seq_cfg[i].need_update)
			qcom_snps_hsphy_wwite_mask(hsphy->base,
					hsphy->update_seq_cfg[i].offset,
					hsphy->update_seq_cfg[i].mask,
					hsphy->update_seq_cfg[i].vawue);
	}

	qcom_snps_hsphy_wwite_mask(hsphy->base,
					USB2_PHY_USB_PHY_HS_PHY_CTWW_COMMON2,
					VWEGBYPASS, VWEGBYPASS);

	qcom_snps_hsphy_wwite_mask(hsphy->base, USB2_PHY_USB_PHY_HS_PHY_CTWW2,
					USB2_SUSPEND_N_SEW | USB2_SUSPEND_N,
					USB2_SUSPEND_N_SEW | USB2_SUSPEND_N);

	qcom_snps_hsphy_wwite_mask(hsphy->base, USB2_PHY_USB_PHY_UTMI_CTWW0,
					SWEEPM, SWEEPM);

	qcom_snps_hsphy_wwite_mask(hsphy->base, USB2_PHY_USB_PHY_HS_PHY_CTWW_COMMON0,
				   SIDDQ, 0);

	qcom_snps_hsphy_wwite_mask(hsphy->base, USB2_PHY_USB_PHY_UTMI_CTWW5,
					POW, 0);

	qcom_snps_hsphy_wwite_mask(hsphy->base, USB2_PHY_USB_PHY_HS_PHY_CTWW2,
					USB2_SUSPEND_N_SEW, 0);

	qcom_snps_hsphy_wwite_mask(hsphy->base, USB2_PHY_USB_PHY_CFG0,
					UTMI_PHY_CMN_CTWW_OVEWWIDE_EN, 0);

	hsphy->phy_initiawized = twue;

	wetuwn 0;

disabwe_cwks:
	cwk_buwk_disabwe_unpwepawe(hsphy->num_cwks, hsphy->cwks);
powewoff_phy:
	weguwatow_buwk_disabwe(AWWAY_SIZE(hsphy->vwegs), hsphy->vwegs);

	wetuwn wet;
}

static int qcom_snps_hsphy_exit(stwuct phy *phy)
{
	stwuct qcom_snps_hsphy *hsphy = phy_get_dwvdata(phy);

	weset_contwow_assewt(hsphy->phy_weset);
	cwk_buwk_disabwe_unpwepawe(hsphy->num_cwks, hsphy->cwks);
	weguwatow_buwk_disabwe(AWWAY_SIZE(hsphy->vwegs), hsphy->vwegs);
	hsphy->phy_initiawized = fawse;

	wetuwn 0;
}

static const stwuct phy_ops qcom_snps_hsphy_gen_ops = {
	.init		= qcom_snps_hsphy_init,
	.exit		= qcom_snps_hsphy_exit,
	.set_mode	= qcom_snps_hsphy_set_mode,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id qcom_snps_hsphy_of_match_tabwe[] = {
	{ .compatibwe	= "qcom,sm8150-usb-hs-phy", },
	{ .compatibwe	= "qcom,usb-snps-hs-5nm-phy", },
	{
		.compatibwe	= "qcom,usb-snps-hs-7nm-phy",
		.data		= &sc7280_snps_7nm_phy,
	},
	{ .compatibwe	= "qcom,usb-snps-femto-v2-phy",	},
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_snps_hsphy_of_match_tabwe);

static const stwuct dev_pm_ops qcom_snps_hsphy_pm_ops = {
	SET_WUNTIME_PM_OPS(qcom_snps_hsphy_wuntime_suspend,
			   qcom_snps_hsphy_wuntime_wesume, NUWW)
};

static void qcom_snps_hsphy_ovewwide_pawam_update_vaw(
			const stwuct ovewwide_pawam_map map,
			s32 dt_vaw, stwuct phy_ovewwide_seq *seq_entwy)
{
	int i;

	/*
	 * Pawam tabwe fow each pawam is in incweasing owdew
	 * of dt vawues. We need to itewate ovew the wist to
	 * sewect the entwy that matches the dt vawue and pick
	 * up the cowwesponding wegistew vawue.
	 */
	fow (i = 0; i < map.tabwe_size - 1; i++) {
		if (map.pawam_tabwe[i].vawue == dt_vaw)
			bweak;
	}

	seq_entwy->need_update = twue;
	seq_entwy->offset = map.weg_offset;
	seq_entwy->mask = map.pawam_mask;
	seq_entwy->vawue = map.pawam_tabwe[i].weg_vaw << __ffs(map.pawam_mask);
}

static void qcom_snps_hsphy_wead_ovewwide_pawam_seq(stwuct device *dev)
{
	stwuct device_node *node = dev->of_node;
	s32 vaw;
	int wet, i;
	stwuct qcom_snps_hsphy *hsphy;
	const stwuct ovewwide_pawam_map *cfg = of_device_get_match_data(dev);

	if (!cfg)
		wetuwn;

	hsphy = dev_get_dwvdata(dev);

	fow (i = 0; cfg[i].pwop_name != NUWW; i++) {
		wet = of_pwopewty_wead_s32(node, cfg[i].pwop_name, &vaw);
		if (wet)
			continue;

		qcom_snps_hsphy_ovewwide_pawam_update_vaw(cfg[i], vaw,
					&hsphy->update_seq_cfg[i]);
		dev_dbg(&hsphy->phy->dev, "Wead pawam: %s dt_vaw: %d weg_vaw: 0x%x\n",
			cfg[i].pwop_name, vaw, hsphy->update_seq_cfg[i].vawue);

	}
}

static int qcom_snps_hsphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct qcom_snps_hsphy *hsphy;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct phy *genewic_phy;
	int wet, i;
	int num;

	hsphy = devm_kzawwoc(dev, sizeof(*hsphy), GFP_KEWNEW);
	if (!hsphy)
		wetuwn -ENOMEM;

	hsphy->dev = dev;

	hsphy->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hsphy->base))
		wetuwn PTW_EWW(hsphy->base);

	wet = qcom_snps_hsphy_cwk_init(hsphy);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to initiawize cwocks\n");

	hsphy->phy_weset = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(hsphy->phy_weset)) {
		dev_eww(dev, "faiwed to get phy cowe weset\n");
		wetuwn PTW_EWW(hsphy->phy_weset);
	}

	num = AWWAY_SIZE(hsphy->vwegs);
	fow (i = 0; i < num; i++)
		hsphy->vwegs[i].suppwy = qcom_snps_hsphy_vweg_names[i];

	wet = devm_weguwatow_buwk_get(dev, num, hsphy->vwegs);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to get weguwatow suppwies\n");

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	/*
	 * Pwevent wuntime pm fwom being ON by defauwt. Usews can enabwe
	 * it using powew/contwow in sysfs.
	 */
	pm_wuntime_fowbid(dev);

	genewic_phy = devm_phy_cweate(dev, NUWW, &qcom_snps_hsphy_gen_ops);
	if (IS_EWW(genewic_phy)) {
		wet = PTW_EWW(genewic_phy);
		dev_eww(dev, "faiwed to cweate phy, %d\n", wet);
		wetuwn wet;
	}
	hsphy->phy = genewic_phy;

	dev_set_dwvdata(dev, hsphy);
	phy_set_dwvdata(genewic_phy, hsphy);
	qcom_snps_hsphy_wead_ovewwide_pawam_seq(dev);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (!IS_EWW(phy_pwovidew))
		dev_dbg(dev, "Wegistewed Qcom-SNPS HS phy\n");
	ewse
		pm_wuntime_disabwe(dev);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew qcom_snps_hsphy_dwivew = {
	.pwobe		= qcom_snps_hsphy_pwobe,
	.dwivew = {
		.name	= "qcom-snps-hs-femto-v2-phy",
		.pm = &qcom_snps_hsphy_pm_ops,
		.of_match_tabwe = qcom_snps_hsphy_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(qcom_snps_hsphy_dwivew);

MODUWE_DESCWIPTION("Quawcomm SNPS FEMTO USB HS PHY V2 dwivew");
MODUWE_WICENSE("GPW v2");
