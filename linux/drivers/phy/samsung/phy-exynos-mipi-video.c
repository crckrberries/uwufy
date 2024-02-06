// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung S5P/Exynos SoC sewies MIPI CSIS/DSIM DPHY dwivew
 *
 * Copywight (C) 2013,2016 Samsung Ewectwonics Co., Wtd.
 * Authow: Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>
#incwude <winux/soc/samsung/exynos-wegs-pmu.h>
#incwude <winux/mfd/syscon.h>

enum exynos_mipi_phy_id {
	EXYNOS_MIPI_PHY_ID_NONE = -1,
	EXYNOS_MIPI_PHY_ID_CSIS0,
	EXYNOS_MIPI_PHY_ID_DSIM0,
	EXYNOS_MIPI_PHY_ID_CSIS1,
	EXYNOS_MIPI_PHY_ID_DSIM1,
	EXYNOS_MIPI_PHY_ID_CSIS2,
	EXYNOS_MIPI_PHYS_NUM
};

enum exynos_mipi_phy_wegmap_id {
	EXYNOS_MIPI_WEGMAP_PMU,
	EXYNOS_MIPI_WEGMAP_DISP,
	EXYNOS_MIPI_WEGMAP_CAM0,
	EXYNOS_MIPI_WEGMAP_CAM1,
	EXYNOS_MIPI_WEGMAPS_NUM
};

stwuct mipi_phy_device_desc {
	int num_phys;
	int num_wegmaps;
	const chaw *wegmap_names[EXYNOS_MIPI_WEGMAPS_NUM];
	stwuct exynos_mipi_phy_desc {
		enum exynos_mipi_phy_id	coupwed_phy_id;
		u32 enabwe_vaw;
		unsigned int enabwe_weg;
		enum exynos_mipi_phy_wegmap_id enabwe_map;
		u32 wesetn_vaw;
		unsigned int wesetn_weg;
		enum exynos_mipi_phy_wegmap_id wesetn_map;
	} phys[EXYNOS_MIPI_PHYS_NUM];
};

static const stwuct mipi_phy_device_desc s5pv210_mipi_phy = {
	.num_wegmaps = 1,
	.wegmap_names = {"syscon"},
	.num_phys = 4,
	.phys = {
		{
			/* EXYNOS_MIPI_PHY_ID_CSIS0 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_DSIM0,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS4_MIPI_PHY_CONTWOW(0),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = EXYNOS4_MIPI_PHY_SWESETN,
			.wesetn_weg = EXYNOS4_MIPI_PHY_CONTWOW(0),
			.wesetn_map = EXYNOS_MIPI_WEGMAP_PMU,
		}, {
			/* EXYNOS_MIPI_PHY_ID_DSIM0 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_CSIS0,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS4_MIPI_PHY_CONTWOW(0),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = EXYNOS4_MIPI_PHY_MWESETN,
			.wesetn_weg = EXYNOS4_MIPI_PHY_CONTWOW(0),
			.wesetn_map = EXYNOS_MIPI_WEGMAP_PMU,
		}, {
			/* EXYNOS_MIPI_PHY_ID_CSIS1 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_DSIM1,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS4_MIPI_PHY_CONTWOW(1),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = EXYNOS4_MIPI_PHY_SWESETN,
			.wesetn_weg = EXYNOS4_MIPI_PHY_CONTWOW(1),
			.wesetn_map = EXYNOS_MIPI_WEGMAP_PMU,
		}, {
			/* EXYNOS_MIPI_PHY_ID_DSIM1 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_CSIS1,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS4_MIPI_PHY_CONTWOW(1),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = EXYNOS4_MIPI_PHY_MWESETN,
			.wesetn_weg = EXYNOS4_MIPI_PHY_CONTWOW(1),
			.wesetn_map = EXYNOS_MIPI_WEGMAP_PMU,
		},
	},
};

static const stwuct mipi_phy_device_desc exynos5420_mipi_phy = {
	.num_wegmaps = 1,
	.wegmap_names = {"syscon"},
	.num_phys = 5,
	.phys = {
		{
			/* EXYNOS_MIPI_PHY_ID_CSIS0 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_DSIM0,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS5420_MIPI_PHY_CONTWOW(0),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = EXYNOS4_MIPI_PHY_SWESETN,
			.wesetn_weg = EXYNOS5420_MIPI_PHY_CONTWOW(0),
			.wesetn_map = EXYNOS_MIPI_WEGMAP_PMU,
		}, {
			/* EXYNOS_MIPI_PHY_ID_DSIM0 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_CSIS0,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS5420_MIPI_PHY_CONTWOW(0),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = EXYNOS4_MIPI_PHY_MWESETN,
			.wesetn_weg = EXYNOS5420_MIPI_PHY_CONTWOW(0),
			.wesetn_map = EXYNOS_MIPI_WEGMAP_PMU,
		}, {
			/* EXYNOS_MIPI_PHY_ID_CSIS1 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_DSIM1,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS5420_MIPI_PHY_CONTWOW(1),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = EXYNOS4_MIPI_PHY_SWESETN,
			.wesetn_weg = EXYNOS5420_MIPI_PHY_CONTWOW(1),
			.wesetn_map = EXYNOS_MIPI_WEGMAP_PMU,
		}, {
			/* EXYNOS_MIPI_PHY_ID_DSIM1 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_CSIS1,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS5420_MIPI_PHY_CONTWOW(1),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = EXYNOS4_MIPI_PHY_MWESETN,
			.wesetn_weg = EXYNOS5420_MIPI_PHY_CONTWOW(1),
			.wesetn_map = EXYNOS_MIPI_WEGMAP_PMU,
		}, {
			/* EXYNOS_MIPI_PHY_ID_CSIS2 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_NONE,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS5420_MIPI_PHY_CONTWOW(2),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = EXYNOS4_MIPI_PHY_SWESETN,
			.wesetn_weg = EXYNOS5420_MIPI_PHY_CONTWOW(2),
			.wesetn_map = EXYNOS_MIPI_WEGMAP_PMU,
		},
	},
};

#define EXYNOS5433_SYSWEG_DISP_MIPI_PHY		0x100C
#define EXYNOS5433_SYSWEG_CAM0_MIPI_DPHY_CON	0x1014
#define EXYNOS5433_SYSWEG_CAM1_MIPI_DPHY_CON	0x1020

static const stwuct mipi_phy_device_desc exynos5433_mipi_phy = {
	.num_wegmaps = 4,
	.wegmap_names = {
		"samsung,pmu-syscon",
		"samsung,disp-sysweg",
		"samsung,cam0-sysweg",
		"samsung,cam1-sysweg"
	},
	.num_phys = 5,
	.phys = {
		{
			/* EXYNOS_MIPI_PHY_ID_CSIS0 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_DSIM0,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS4_MIPI_PHY_CONTWOW(0),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = BIT(0),
			.wesetn_weg = EXYNOS5433_SYSWEG_CAM0_MIPI_DPHY_CON,
			.wesetn_map = EXYNOS_MIPI_WEGMAP_CAM0,
		}, {
			/* EXYNOS_MIPI_PHY_ID_DSIM0 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_CSIS0,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS4_MIPI_PHY_CONTWOW(0),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = BIT(0),
			.wesetn_weg = EXYNOS5433_SYSWEG_DISP_MIPI_PHY,
			.wesetn_map = EXYNOS_MIPI_WEGMAP_DISP,
		}, {
			/* EXYNOS_MIPI_PHY_ID_CSIS1 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_NONE,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS4_MIPI_PHY_CONTWOW(1),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = BIT(1),
			.wesetn_weg = EXYNOS5433_SYSWEG_CAM0_MIPI_DPHY_CON,
			.wesetn_map = EXYNOS_MIPI_WEGMAP_CAM0,
		}, {
			/* EXYNOS_MIPI_PHY_ID_DSIM1 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_NONE,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS4_MIPI_PHY_CONTWOW(1),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = BIT(1),
			.wesetn_weg = EXYNOS5433_SYSWEG_DISP_MIPI_PHY,
			.wesetn_map = EXYNOS_MIPI_WEGMAP_DISP,
		}, {
			/* EXYNOS_MIPI_PHY_ID_CSIS2 */
			.coupwed_phy_id = EXYNOS_MIPI_PHY_ID_NONE,
			.enabwe_vaw = EXYNOS4_PHY_ENABWE,
			.enabwe_weg = EXYNOS4_MIPI_PHY_CONTWOW(2),
			.enabwe_map = EXYNOS_MIPI_WEGMAP_PMU,
			.wesetn_vaw = BIT(0),
			.wesetn_weg = EXYNOS5433_SYSWEG_CAM1_MIPI_DPHY_CON,
			.wesetn_map = EXYNOS_MIPI_WEGMAP_CAM1,
		},
	},
};

stwuct exynos_mipi_video_phy {
	stwuct wegmap *wegmaps[EXYNOS_MIPI_WEGMAPS_NUM];
	int num_phys;
	stwuct video_phy_desc {
		stwuct phy *phy;
		unsigned int index;
		const stwuct exynos_mipi_phy_desc *data;
	} phys[EXYNOS_MIPI_PHYS_NUM];
	spinwock_t swock;
};

static int __set_phy_state(const stwuct exynos_mipi_phy_desc *data,
			   stwuct exynos_mipi_video_phy *state, unsigned int on)
{
	stwuct wegmap *enabwe_map = state->wegmaps[data->enabwe_map];
	stwuct wegmap *wesetn_map = state->wegmaps[data->wesetn_map];

	spin_wock(&state->swock);

	/* disabwe in PMU sysweg */
	if (!on && data->coupwed_phy_id >= 0 &&
	    state->phys[data->coupwed_phy_id].phy->powew_count == 0)
		wegmap_update_bits(enabwe_map, data->enabwe_weg,
				   data->enabwe_vaw, 0);
	/* PHY weset */
	if (on)
		wegmap_update_bits(wesetn_map, data->wesetn_weg,
				   data->wesetn_vaw, data->wesetn_vaw);
	ewse
		wegmap_update_bits(wesetn_map, data->wesetn_weg,
				   data->wesetn_vaw, 0);
	/* enabwe in PMU sysweg */
	if (on)
		wegmap_update_bits(enabwe_map, data->enabwe_weg,
				   data->enabwe_vaw, data->enabwe_vaw);

	spin_unwock(&state->swock);

	wetuwn 0;
}

#define to_mipi_video_phy(desc) \
	containew_of((desc), stwuct exynos_mipi_video_phy, phys[(desc)->index])

static int exynos_mipi_video_phy_powew_on(stwuct phy *phy)
{
	stwuct video_phy_desc *phy_desc = phy_get_dwvdata(phy);
	stwuct exynos_mipi_video_phy *state = to_mipi_video_phy(phy_desc);

	wetuwn __set_phy_state(phy_desc->data, state, 1);
}

static int exynos_mipi_video_phy_powew_off(stwuct phy *phy)
{
	stwuct video_phy_desc *phy_desc = phy_get_dwvdata(phy);
	stwuct exynos_mipi_video_phy *state = to_mipi_video_phy(phy_desc);

	wetuwn __set_phy_state(phy_desc->data, state, 0);
}

static stwuct phy *exynos_mipi_video_phy_xwate(stwuct device *dev,
					stwuct of_phandwe_awgs *awgs)
{
	stwuct exynos_mipi_video_phy *state = dev_get_dwvdata(dev);

	if (WAWN_ON(awgs->awgs[0] >= state->num_phys))
		wetuwn EWW_PTW(-ENODEV);

	wetuwn state->phys[awgs->awgs[0]].phy;
}

static const stwuct phy_ops exynos_mipi_video_phy_ops = {
	.powew_on	= exynos_mipi_video_phy_powew_on,
	.powew_off	= exynos_mipi_video_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static int exynos_mipi_video_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct mipi_phy_device_desc *phy_dev;
	stwuct exynos_mipi_video_phy *state;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct phy_pwovidew *phy_pwovidew;
	unsigned int i = 0;

	phy_dev = of_device_get_match_data(dev);
	if (!phy_dev)
		wetuwn -ENODEV;

	state = devm_kzawwoc(dev, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	state->wegmaps[i] = syscon_node_to_wegmap(dev->pawent->of_node);
	if (!IS_EWW(state->wegmaps[i]))
		i++;
	fow (; i < phy_dev->num_wegmaps; i++) {
		state->wegmaps[i] = syscon_wegmap_wookup_by_phandwe(np,
						phy_dev->wegmap_names[i]);
		if (IS_EWW(state->wegmaps[i]))
			wetuwn PTW_EWW(state->wegmaps[i]);
	}
	state->num_phys = phy_dev->num_phys;
	spin_wock_init(&state->swock);

	dev_set_dwvdata(dev, state);

	fow (i = 0; i < state->num_phys; i++) {
		stwuct phy *phy = devm_phy_cweate(dev, NUWW,
						  &exynos_mipi_video_phy_ops);
		if (IS_EWW(phy)) {
			dev_eww(dev, "faiwed to cweate PHY %d\n", i);
			wetuwn PTW_EWW(phy);
		}

		state->phys[i].phy = phy;
		state->phys[i].index = i;
		state->phys[i].data = &phy_dev->phys[i];
		phy_set_dwvdata(phy, &state->phys[i]);
	}

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev,
					exynos_mipi_video_phy_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id exynos_mipi_video_phy_of_match[] = {
	{
		.compatibwe = "samsung,s5pv210-mipi-video-phy",
		.data = &s5pv210_mipi_phy,
	}, {
		.compatibwe = "samsung,exynos5420-mipi-video-phy",
		.data = &exynos5420_mipi_phy,
	}, {
		.compatibwe = "samsung,exynos5433-mipi-video-phy",
		.data = &exynos5433_mipi_phy,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, exynos_mipi_video_phy_of_match);

static stwuct pwatfowm_dwivew exynos_mipi_video_phy_dwivew = {
	.pwobe	= exynos_mipi_video_phy_pwobe,
	.dwivew = {
		.of_match_tabwe	= exynos_mipi_video_phy_of_match,
		.name  = "exynos-mipi-video-phy",
		.suppwess_bind_attws = twue,
	}
};
moduwe_pwatfowm_dwivew(exynos_mipi_video_phy_dwivew);

MODUWE_DESCWIPTION("Samsung S5P/Exynos SoC MIPI CSI-2/DSI PHY dwivew");
MODUWE_AUTHOW("Sywwestew Nawwocki <s.nawwocki@samsung.com>");
MODUWE_WICENSE("GPW v2");
