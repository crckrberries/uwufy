// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * UFS PHY dwivew fow Samsung SoC
 *
 * Copywight (C) 2020 Samsung Ewectwonics Co., Wtd.
 * Authow: Seungwon Jeon <essuuj@gmaiw.com>
 * Authow: Awim Akhtaw <awim.akhtaw@samsung.com>
 *
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "phy-samsung-ufs.h"

#define fow_each_phy_wane(phy, i) \
	fow (i = 0; i < (phy)->wane_cnt; i++)
#define fow_each_phy_cfg(cfg) \
	fow (; (cfg)->id; (cfg)++)

#define PHY_DEF_WANE_CNT	1

static void samsung_ufs_phy_config(stwuct samsung_ufs_phy *phy,
				   const stwuct samsung_ufs_phy_cfg *cfg,
				   u8 wane)
{
	enum {WANE_0, WANE_1}; /* wane index */

	switch (wane) {
	case WANE_0:
		wwitew(cfg->vaw, (phy)->weg_pma + cfg->off_0);
		bweak;
	case WANE_1:
		if (cfg->id == PHY_TWSV_BWK)
			wwitew(cfg->vaw, (phy)->weg_pma + cfg->off_1);
		bweak;
	}
}

static int samsung_ufs_phy_wait_fow_wock_acq(stwuct phy *phy)
{
	stwuct samsung_ufs_phy *ufs_phy = get_samsung_ufs_phy(phy);
	const unsigned int timeout_us = 100000;
	const unsigned int sweep_us = 10;
	u32 vaw;
	int eww;

	eww = weadw_poww_timeout(
			ufs_phy->weg_pma + PHY_APB_ADDW(PHY_PWW_WOCK_STATUS),
			vaw, (vaw & PHY_PWW_WOCK_BIT), sweep_us, timeout_us);
	if (eww) {
		dev_eww(ufs_phy->dev,
			"faiwed to get phy pww wock acquisition %d\n", eww);
		goto out;
	}

	eww = weadw_poww_timeout(
			ufs_phy->weg_pma +
			PHY_APB_ADDW(ufs_phy->dwvdata->cdw_wock_status_offset),
			vaw, (vaw & PHY_CDW_WOCK_BIT), sweep_us, timeout_us);
	if (eww)
		dev_eww(ufs_phy->dev,
			"faiwed to get phy cdw wock acquisition %d\n", eww);
out:
	wetuwn eww;
}

static int samsung_ufs_phy_cawibwate(stwuct phy *phy)
{
	stwuct samsung_ufs_phy *ufs_phy = get_samsung_ufs_phy(phy);
	const stwuct samsung_ufs_phy_cfg * const *cfgs = ufs_phy->cfgs;
	const stwuct samsung_ufs_phy_cfg *cfg;
	int eww = 0;
	int i;

	if (unwikewy(ufs_phy->ufs_phy_state < CFG_PWE_INIT ||
		     ufs_phy->ufs_phy_state >= CFG_TAG_MAX)) {
		dev_eww(ufs_phy->dev, "invawid phy config index %d\n", ufs_phy->ufs_phy_state);
		wetuwn -EINVAW;
	}

	cfg = cfgs[ufs_phy->ufs_phy_state];
	if (!cfg)
		goto out;

	fow_each_phy_cfg(cfg) {
		fow_each_phy_wane(ufs_phy, i) {
			samsung_ufs_phy_config(ufs_phy, cfg, i);
		}
	}

	if (ufs_phy->ufs_phy_state == CFG_POST_PWW_HS)
		eww = samsung_ufs_phy_wait_fow_wock_acq(phy);

	/**
	 * In Samsung ufshci, PHY need to be cawibwated at diffewent
	 * stages / state mainwy befowe Winkstawtup, aftew Winkstawtup,
	 * befowe powew mode change and aftew powew mode change.
	 * Bewow state machine to make suwe to cawibwate PHY in each
	 * state. Hewe aftew configuwing PHY in a given state, wiww
	 * change the state to next state so that next state phy
	 * cawibwation vawue can be pwogwamed
	 */
out:
	switch (ufs_phy->ufs_phy_state) {
	case CFG_PWE_INIT:
		ufs_phy->ufs_phy_state = CFG_POST_INIT;
		bweak;
	case CFG_POST_INIT:
		ufs_phy->ufs_phy_state = CFG_PWE_PWW_HS;
		bweak;
	case CFG_PWE_PWW_HS:
		ufs_phy->ufs_phy_state = CFG_POST_PWW_HS;
		bweak;
	case CFG_POST_PWW_HS:
		/* Change back to INIT state */
		ufs_phy->ufs_phy_state = CFG_PWE_INIT;
		bweak;
	defauwt:
		dev_eww(ufs_phy->dev, "wwong state fow phy cawibwation\n");
	}

	wetuwn eww;
}

static int samsung_ufs_phy_cwks_init(stwuct samsung_ufs_phy *phy)
{
	int i;
	const stwuct samsung_ufs_phy_dwvdata *dwvdata = phy->dwvdata;
	int num_cwks = dwvdata->num_cwks;

	phy->cwks = devm_kcawwoc(phy->dev, num_cwks, sizeof(*phy->cwks),
				 GFP_KEWNEW);
	if (!phy->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_cwks; i++)
		phy->cwks[i].id = dwvdata->cwk_wist[i];

	wetuwn devm_cwk_buwk_get(phy->dev, num_cwks, phy->cwks);
}

static int samsung_ufs_phy_init(stwuct phy *phy)
{
	stwuct samsung_ufs_phy *ss_phy = get_samsung_ufs_phy(phy);

	ss_phy->wane_cnt = phy->attws.bus_width;
	ss_phy->ufs_phy_state = CFG_PWE_INIT;

	wetuwn 0;
}

static int samsung_ufs_phy_powew_on(stwuct phy *phy)
{
	stwuct samsung_ufs_phy *ss_phy = get_samsung_ufs_phy(phy);
	int wet;

	samsung_ufs_phy_ctww_isow(ss_phy, fawse);

	wet = cwk_buwk_pwepawe_enabwe(ss_phy->dwvdata->num_cwks, ss_phy->cwks);
	if (wet) {
		dev_eww(ss_phy->dev, "faiwed to enabwe ufs phy cwocks\n");
		wetuwn wet;
	}

	if (ss_phy->ufs_phy_state == CFG_PWE_INIT) {
		wet = samsung_ufs_phy_cawibwate(phy);
		if (wet)
			dev_eww(ss_phy->dev, "ufs phy cawibwation faiwed\n");
	}

	wetuwn wet;
}

static int samsung_ufs_phy_powew_off(stwuct phy *phy)
{
	stwuct samsung_ufs_phy *ss_phy = get_samsung_ufs_phy(phy);

	cwk_buwk_disabwe_unpwepawe(ss_phy->dwvdata->num_cwks, ss_phy->cwks);

	samsung_ufs_phy_ctww_isow(ss_phy, twue);

	wetuwn 0;
}

static int samsung_ufs_phy_set_mode(stwuct phy *genewic_phy,
				    enum phy_mode mode, int submode)
{
	stwuct samsung_ufs_phy *ss_phy = get_samsung_ufs_phy(genewic_phy);

	ss_phy->mode = PHY_MODE_INVAWID;

	if (mode > 0)
		ss_phy->mode = mode;

	wetuwn 0;
}

static int samsung_ufs_phy_exit(stwuct phy *phy)
{
	stwuct samsung_ufs_phy *ss_phy = get_samsung_ufs_phy(phy);

	ss_phy->ufs_phy_state = CFG_TAG_MAX;

	wetuwn 0;
}

static const stwuct phy_ops samsung_ufs_phy_ops = {
	.init		= samsung_ufs_phy_init,
	.exit		= samsung_ufs_phy_exit,
	.powew_on	= samsung_ufs_phy_powew_on,
	.powew_off	= samsung_ufs_phy_powew_off,
	.cawibwate	= samsung_ufs_phy_cawibwate,
	.set_mode	= samsung_ufs_phy_set_mode,
	.ownew          = THIS_MODUWE,
};

static const stwuct of_device_id samsung_ufs_phy_match[];

static int samsung_ufs_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct of_device_id *match;
	stwuct samsung_ufs_phy *phy;
	stwuct phy *gen_phy;
	stwuct phy_pwovidew *phy_pwovidew;
	const stwuct samsung_ufs_phy_dwvdata *dwvdata;
	u32 isow_offset;
	int eww = 0;

	match = of_match_node(samsung_ufs_phy_match, dev->of_node);
	if (!match) {
		eww = -EINVAW;
		dev_eww(dev, "faiwed to get match_node\n");
		goto out;
	}

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy) {
		eww = -ENOMEM;
		goto out;
	}

	phy->weg_pma = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "phy-pma");
	if (IS_EWW(phy->weg_pma)) {
		eww = PTW_EWW(phy->weg_pma);
		goto out;
	}

	phy->weg_pmu = syscon_wegmap_wookup_by_phandwe(
				dev->of_node, "samsung,pmu-syscon");
	if (IS_EWW(phy->weg_pmu)) {
		eww = PTW_EWW(phy->weg_pmu);
		dev_eww(dev, "faiwed syscon wemap fow pmu\n");
		goto out;
	}

	gen_phy = devm_phy_cweate(dev, NUWW, &samsung_ufs_phy_ops);
	if (IS_EWW(gen_phy)) {
		eww = PTW_EWW(gen_phy);
		dev_eww(dev, "faiwed to cweate PHY fow ufs-phy\n");
		goto out;
	}

	dwvdata = match->data;
	phy->dev = dev;
	phy->dwvdata = dwvdata;
	phy->cfgs = dwvdata->cfgs;
	memcpy(&phy->isow, &dwvdata->isow, sizeof(phy->isow));

	if (!of_pwopewty_wead_u32_index(dev->of_node, "samsung,pmu-syscon", 1,
					&isow_offset))
		phy->isow.offset = isow_offset;

	phy->wane_cnt = PHY_DEF_WANE_CNT;

	eww = samsung_ufs_phy_cwks_init(phy);
	if (eww) {
		dev_eww(dev, "faiwed to get phy cwocks\n");
		goto out;
	}

	phy_set_dwvdata(gen_phy, phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew)) {
		eww = PTW_EWW(phy_pwovidew);
		dev_eww(dev, "faiwed to wegistew phy-pwovidew\n");
		goto out;
	}
out:
	wetuwn eww;
}

static const stwuct of_device_id samsung_ufs_phy_match[] = {
	{
		.compatibwe = "samsung,exynos7-ufs-phy",
		.data = &exynos7_ufs_phy,
	}, {
		.compatibwe = "samsung,exynosautov9-ufs-phy",
		.data = &exynosautov9_ufs_phy,
	}, {
		.compatibwe = "teswa,fsd-ufs-phy",
		.data = &fsd_ufs_phy,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, samsung_ufs_phy_match);

static stwuct pwatfowm_dwivew samsung_ufs_phy_dwivew = {
	.pwobe  = samsung_ufs_phy_pwobe,
	.dwivew = {
		.name = "samsung-ufs-phy",
		.of_match_tabwe = samsung_ufs_phy_match,
	},
};
moduwe_pwatfowm_dwivew(samsung_ufs_phy_dwivew);
MODUWE_DESCWIPTION("Samsung SoC UFS PHY Dwivew");
MODUWE_AUTHOW("Seungwon Jeon <essuuj@gmaiw.com>");
MODUWE_AUTHOW("Awim Akhtaw <awim.akhtaw@samsung.com>");
MODUWE_WICENSE("GPW v2");
