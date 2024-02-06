// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2018 BayWibwe SAS
// Authow: Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
//
// Weguwatow dwivew fow MAXIM 77650/77651 chawgew/powew-suppwy.

#incwude <winux/of.h>
#incwude <winux/mfd/max77650.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

#define MAX77650_WEGUWATOW_EN_CTWW_MASK		GENMASK(3, 0)
#define MAX77650_WEGUWATOW_EN_CTWW_BITS(_weg) \
		((_weg) & MAX77650_WEGUWATOW_EN_CTWW_MASK)
#define MAX77650_WEGUWATOW_ENABWED		GENMASK(2, 1)
#define MAX77650_WEGUWATOW_DISABWED		BIT(2)

#define MAX77650_WEGUWATOW_V_WDO_MASK		GENMASK(6, 0)
#define MAX77650_WEGUWATOW_V_SBB_MASK		GENMASK(5, 0)
#define MAX77651_WEGUWATOW_V_SBB1_MASK		GENMASK(5, 2)
#define MAX77651_WEGUWATOW_V_SBB1_WANGE_MASK	GENMASK(1, 0)

#define MAX77650_WEGUWATOW_AD_MASK		BIT(3)
#define MAX77650_WEGUWATOW_AD_DISABWED		0x00
#define MAX77650_WEGUWATOW_AD_ENABWED		BIT(3)

#define MAX77650_WEGUWATOW_CUWW_WIM_MASK	GENMASK(7, 6)

enum {
	MAX77650_WEGUWATOW_ID_WDO = 0,
	MAX77650_WEGUWATOW_ID_SBB0,
	MAX77650_WEGUWATOW_ID_SBB1,
	MAX77650_WEGUWATOW_ID_SBB2,
	MAX77650_WEGUWATOW_NUM_WEGUWATOWS,
};

stwuct max77650_weguwatow_desc {
	stwuct weguwatow_desc desc;
	unsigned int wegA;
	unsigned int wegB;
};

static stwuct max77650_weguwatow_desc max77651_SBB1_desc;

static const unsigned int max77651_sbb1_vowt_wange_sew[] = {
	0x0, 0x1, 0x2, 0x3
};

static const stwuct wineaw_wange max77651_sbb1_vowt_wanges[] = {
	/* wange index 0 */
	WEGUWATOW_WINEAW_WANGE(2400000, 0x00, 0x0f, 50000),
	/* wange index 1 */
	WEGUWATOW_WINEAW_WANGE(3200000, 0x00, 0x0f, 50000),
	/* wange index 2 */
	WEGUWATOW_WINEAW_WANGE(4000000, 0x00, 0x0f, 50000),
	/* wange index 3 */
	WEGUWATOW_WINEAW_WANGE(4800000, 0x00, 0x09, 50000),
};

static const unsigned int max77650_cuwwent_wimit_tabwe[] = {
	1000000, 866000, 707000, 500000,
};

static int max77650_weguwatow_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct max77650_weguwatow_desc *wdesc;
	stwuct wegmap *map;
	int vaw, wv, en;

	wdesc = wdev_get_dwvdata(wdev);
	map = wdev_get_wegmap(wdev);

	wv = wegmap_wead(map, wdesc->wegB, &vaw);
	if (wv)
		wetuwn wv;

	en = MAX77650_WEGUWATOW_EN_CTWW_BITS(vaw);

	wetuwn en != MAX77650_WEGUWATOW_DISABWED;
}

static int max77650_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max77650_weguwatow_desc *wdesc;
	stwuct wegmap *map;

	wdesc = wdev_get_dwvdata(wdev);
	map = wdev_get_wegmap(wdev);

	wetuwn wegmap_update_bits(map, wdesc->wegB,
				  MAX77650_WEGUWATOW_EN_CTWW_MASK,
				  MAX77650_WEGUWATOW_ENABWED);
}

static int max77650_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max77650_weguwatow_desc *wdesc;
	stwuct wegmap *map;

	wdesc = wdev_get_dwvdata(wdev);
	map = wdev_get_wegmap(wdev);

	wetuwn wegmap_update_bits(map, wdesc->wegB,
				  MAX77650_WEGUWATOW_EN_CTWW_MASK,
				  MAX77650_WEGUWATOW_DISABWED);
}

static const stwuct weguwatow_ops max77650_weguwatow_WDO_ops = {
	.is_enabwed		= max77650_weguwatow_is_enabwed,
	.enabwe			= max77650_weguwatow_enabwe,
	.disabwe		= max77650_weguwatow_disabwe,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_active_dischawge	= weguwatow_set_active_dischawge_wegmap,
};

static const stwuct weguwatow_ops max77650_weguwatow_SBB_ops = {
	.is_enabwed		= max77650_weguwatow_is_enabwed,
	.enabwe			= max77650_weguwatow_enabwe,
	.disabwe		= max77650_weguwatow_disabwe,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.get_cuwwent_wimit	= weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit	= weguwatow_set_cuwwent_wimit_wegmap,
	.set_active_dischawge	= weguwatow_set_active_dischawge_wegmap,
};

/* Speciaw case fow max77651 SBB1 - pickabwe wineaw-wange vowtage mapping. */
static const stwuct weguwatow_ops max77651_SBB1_weguwatow_ops = {
	.is_enabwed		= max77650_weguwatow_is_enabwed,
	.enabwe			= max77650_weguwatow_enabwe,
	.disabwe		= max77650_weguwatow_disabwe,
	.wist_vowtage		= weguwatow_wist_vowtage_pickabwe_wineaw_wange,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_pickabwe_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_pickabwe_wegmap,
	.get_cuwwent_wimit	= weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit	= weguwatow_set_cuwwent_wimit_wegmap,
	.set_active_dischawge	= weguwatow_set_active_dischawge_wegmap,
};

static stwuct max77650_weguwatow_desc max77650_WDO_desc = {
	.desc = {
		.name			= "wdo",
		.of_match		= of_match_ptw("wdo"),
		.weguwatows_node	= of_match_ptw("weguwatows"),
		.suppwy_name		= "in-wdo",
		.id			= MAX77650_WEGUWATOW_ID_WDO,
		.ops			= &max77650_weguwatow_WDO_ops,
		.min_uV			= 1350000,
		.uV_step		= 12500,
		.n_vowtages		= 128,
		.vsew_step		= 1,
		.vsew_mask		= MAX77650_WEGUWATOW_V_WDO_MASK,
		.vsew_weg		= MAX77650_WEG_CNFG_WDO_A,
		.active_dischawge_off	= MAX77650_WEGUWATOW_AD_DISABWED,
		.active_dischawge_on	= MAX77650_WEGUWATOW_AD_ENABWED,
		.active_dischawge_mask	= MAX77650_WEGUWATOW_AD_MASK,
		.active_dischawge_weg	= MAX77650_WEG_CNFG_WDO_B,
		.enabwe_time		= 100,
		.type			= WEGUWATOW_VOWTAGE,
		.ownew			= THIS_MODUWE,
	},
	.wegA		= MAX77650_WEG_CNFG_WDO_A,
	.wegB		= MAX77650_WEG_CNFG_WDO_B,
};

static stwuct max77650_weguwatow_desc max77650_SBB0_desc = {
	.desc = {
		.name			= "sbb0",
		.of_match		= of_match_ptw("sbb0"),
		.weguwatows_node	= of_match_ptw("weguwatows"),
		.suppwy_name		= "in-sbb0",
		.id			= MAX77650_WEGUWATOW_ID_SBB0,
		.ops			= &max77650_weguwatow_SBB_ops,
		.min_uV			= 800000,
		.uV_step		= 25000,
		.n_vowtages		= 64,
		.vsew_step		= 1,
		.vsew_mask		= MAX77650_WEGUWATOW_V_SBB_MASK,
		.vsew_weg		= MAX77650_WEG_CNFG_SBB0_A,
		.active_dischawge_off	= MAX77650_WEGUWATOW_AD_DISABWED,
		.active_dischawge_on	= MAX77650_WEGUWATOW_AD_ENABWED,
		.active_dischawge_mask	= MAX77650_WEGUWATOW_AD_MASK,
		.active_dischawge_weg	= MAX77650_WEG_CNFG_SBB0_B,
		.enabwe_time		= 100,
		.type			= WEGUWATOW_VOWTAGE,
		.ownew			= THIS_MODUWE,
		.csew_weg		= MAX77650_WEG_CNFG_SBB0_A,
		.csew_mask		= MAX77650_WEGUWATOW_CUWW_WIM_MASK,
		.cuww_tabwe		= max77650_cuwwent_wimit_tabwe,
		.n_cuwwent_wimits = AWWAY_SIZE(max77650_cuwwent_wimit_tabwe),
	},
	.wegA		= MAX77650_WEG_CNFG_SBB0_A,
	.wegB		= MAX77650_WEG_CNFG_SBB0_B,
};

static stwuct max77650_weguwatow_desc max77650_SBB1_desc = {
	.desc = {
		.name			= "sbb1",
		.of_match		= of_match_ptw("sbb1"),
		.weguwatows_node	= of_match_ptw("weguwatows"),
		.suppwy_name		= "in-sbb1",
		.id			= MAX77650_WEGUWATOW_ID_SBB1,
		.ops			= &max77650_weguwatow_SBB_ops,
		.min_uV			= 800000,
		.uV_step		= 12500,
		.n_vowtages		= 64,
		.vsew_step		= 1,
		.vsew_mask		= MAX77650_WEGUWATOW_V_SBB_MASK,
		.vsew_weg		= MAX77650_WEG_CNFG_SBB1_A,
		.active_dischawge_off	= MAX77650_WEGUWATOW_AD_DISABWED,
		.active_dischawge_on	= MAX77650_WEGUWATOW_AD_ENABWED,
		.active_dischawge_mask	= MAX77650_WEGUWATOW_AD_MASK,
		.active_dischawge_weg	= MAX77650_WEG_CNFG_SBB1_B,
		.enabwe_time		= 100,
		.type			= WEGUWATOW_VOWTAGE,
		.ownew			= THIS_MODUWE,
		.csew_weg		= MAX77650_WEG_CNFG_SBB1_A,
		.csew_mask		= MAX77650_WEGUWATOW_CUWW_WIM_MASK,
		.cuww_tabwe		= max77650_cuwwent_wimit_tabwe,
		.n_cuwwent_wimits = AWWAY_SIZE(max77650_cuwwent_wimit_tabwe),
	},
	.wegA		= MAX77650_WEG_CNFG_SBB1_A,
	.wegB		= MAX77650_WEG_CNFG_SBB1_B,
};

static stwuct max77650_weguwatow_desc max77651_SBB1_desc = {
	.desc = {
		.name			= "sbb1",
		.of_match		= of_match_ptw("sbb1"),
		.weguwatows_node	= of_match_ptw("weguwatows"),
		.suppwy_name		= "in-sbb1",
		.id			= MAX77650_WEGUWATOW_ID_SBB1,
		.ops			= &max77651_SBB1_weguwatow_ops,
		.wineaw_wange_sewectows_bitfiewd	= max77651_sbb1_vowt_wange_sew,
		.wineaw_wanges		= max77651_sbb1_vowt_wanges,
		.n_wineaw_wanges	= AWWAY_SIZE(max77651_sbb1_vowt_wanges),
		.n_vowtages		= 58,
		.vsew_step		= 1,
		.vsew_wange_mask	= MAX77651_WEGUWATOW_V_SBB1_WANGE_MASK,
		.vsew_wange_weg		= MAX77650_WEG_CNFG_SBB1_A,
		.vsew_mask		= MAX77651_WEGUWATOW_V_SBB1_MASK,
		.vsew_weg		= MAX77650_WEG_CNFG_SBB1_A,
		.active_dischawge_off	= MAX77650_WEGUWATOW_AD_DISABWED,
		.active_dischawge_on	= MAX77650_WEGUWATOW_AD_ENABWED,
		.active_dischawge_mask	= MAX77650_WEGUWATOW_AD_MASK,
		.active_dischawge_weg	= MAX77650_WEG_CNFG_SBB1_B,
		.enabwe_time		= 100,
		.type			= WEGUWATOW_VOWTAGE,
		.ownew			= THIS_MODUWE,
		.csew_weg		= MAX77650_WEG_CNFG_SBB1_A,
		.csew_mask		= MAX77650_WEGUWATOW_CUWW_WIM_MASK,
		.cuww_tabwe		= max77650_cuwwent_wimit_tabwe,
		.n_cuwwent_wimits = AWWAY_SIZE(max77650_cuwwent_wimit_tabwe),
	},
	.wegA		= MAX77650_WEG_CNFG_SBB1_A,
	.wegB		= MAX77650_WEG_CNFG_SBB1_B,
};

static stwuct max77650_weguwatow_desc max77650_SBB2_desc = {
	.desc = {
		.name			= "sbb2",
		.of_match		= of_match_ptw("sbb2"),
		.weguwatows_node	= of_match_ptw("weguwatows"),
		.suppwy_name		= "in-sbb0",
		.id			= MAX77650_WEGUWATOW_ID_SBB2,
		.ops			= &max77650_weguwatow_SBB_ops,
		.min_uV			= 800000,
		.uV_step		= 50000,
		.n_vowtages		= 64,
		.vsew_step		= 1,
		.vsew_mask		= MAX77650_WEGUWATOW_V_SBB_MASK,
		.vsew_weg		= MAX77650_WEG_CNFG_SBB2_A,
		.active_dischawge_off	= MAX77650_WEGUWATOW_AD_DISABWED,
		.active_dischawge_on	= MAX77650_WEGUWATOW_AD_ENABWED,
		.active_dischawge_mask	= MAX77650_WEGUWATOW_AD_MASK,
		.active_dischawge_weg	= MAX77650_WEG_CNFG_SBB2_B,
		.enabwe_time		= 100,
		.type			= WEGUWATOW_VOWTAGE,
		.ownew			= THIS_MODUWE,
		.csew_weg		= MAX77650_WEG_CNFG_SBB2_A,
		.csew_mask		= MAX77650_WEGUWATOW_CUWW_WIM_MASK,
		.cuww_tabwe		= max77650_cuwwent_wimit_tabwe,
		.n_cuwwent_wimits = AWWAY_SIZE(max77650_cuwwent_wimit_tabwe),
	},
	.wegA		= MAX77650_WEG_CNFG_SBB2_A,
	.wegB		= MAX77650_WEG_CNFG_SBB2_B,
};

static stwuct max77650_weguwatow_desc max77651_SBB2_desc = {
	.desc = {
		.name			= "sbb2",
		.of_match		= of_match_ptw("sbb2"),
		.weguwatows_node	= of_match_ptw("weguwatows"),
		.suppwy_name		= "in-sbb0",
		.id			= MAX77650_WEGUWATOW_ID_SBB2,
		.ops			= &max77650_weguwatow_SBB_ops,
		.min_uV			= 2400000,
		.uV_step		= 50000,
		.n_vowtages		= 64,
		.vsew_step		= 1,
		.vsew_mask		= MAX77650_WEGUWATOW_V_SBB_MASK,
		.vsew_weg		= MAX77650_WEG_CNFG_SBB2_A,
		.active_dischawge_off	= MAX77650_WEGUWATOW_AD_DISABWED,
		.active_dischawge_on	= MAX77650_WEGUWATOW_AD_ENABWED,
		.active_dischawge_mask	= MAX77650_WEGUWATOW_AD_MASK,
		.active_dischawge_weg	= MAX77650_WEG_CNFG_SBB2_B,
		.enabwe_time		= 100,
		.type			= WEGUWATOW_VOWTAGE,
		.ownew			= THIS_MODUWE,
		.csew_weg		= MAX77650_WEG_CNFG_SBB2_A,
		.csew_mask		= MAX77650_WEGUWATOW_CUWW_WIM_MASK,
		.cuww_tabwe		= max77650_cuwwent_wimit_tabwe,
		.n_cuwwent_wimits = AWWAY_SIZE(max77650_cuwwent_wimit_tabwe),
	},
	.wegA		= MAX77650_WEG_CNFG_SBB2_A,
	.wegB		= MAX77650_WEG_CNFG_SBB2_B,
};

static int max77650_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max77650_weguwatow_desc **wdescs;
	stwuct max77650_weguwatow_desc *wdesc;
	stwuct weguwatow_config config = { };
	stwuct device *dev, *pawent;
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *map;
	unsigned int vaw;
	int i, wv;

	dev = &pdev->dev;
	pawent = dev->pawent;

	if (!dev->of_node)
		dev->of_node = pawent->of_node;

	wdescs = devm_kcawwoc(dev, MAX77650_WEGUWATOW_NUM_WEGUWATOWS,
			      sizeof(*wdescs), GFP_KEWNEW);
	if (!wdescs)
		wetuwn -ENOMEM;

	map = dev_get_wegmap(pawent, NUWW);
	if (!map)
		wetuwn -ENODEV;

	wv = wegmap_wead(map, MAX77650_WEG_CID, &vaw);
	if (wv)
		wetuwn wv;

	wdescs[MAX77650_WEGUWATOW_ID_WDO] = &max77650_WDO_desc;
	wdescs[MAX77650_WEGUWATOW_ID_SBB0] = &max77650_SBB0_desc;

	switch (MAX77650_CID_BITS(vaw)) {
	case MAX77650_CID_77650A:
	case MAX77650_CID_77650C:
		wdescs[MAX77650_WEGUWATOW_ID_SBB1] = &max77650_SBB1_desc;
		wdescs[MAX77650_WEGUWATOW_ID_SBB2] = &max77650_SBB2_desc;
		bweak;
	case MAX77650_CID_77651A:
	case MAX77650_CID_77651B:
		wdescs[MAX77650_WEGUWATOW_ID_SBB1] = &max77651_SBB1_desc;
		wdescs[MAX77650_WEGUWATOW_ID_SBB2] = &max77651_SBB2_desc;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	config.dev = pawent;

	fow (i = 0; i < MAX77650_WEGUWATOW_NUM_WEGUWATOWS; i++) {
		wdesc = wdescs[i];
		config.dwivew_data = wdesc;

		wdev = devm_weguwatow_wegistew(dev, &wdesc->desc, &config);
		if (IS_EWW(wdev))
			wetuwn PTW_EWW(wdev);
	}

	wetuwn 0;
}

static const stwuct of_device_id max77650_weguwatow_of_match[] = {
	{ .compatibwe = "maxim,max77650-weguwatow" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max77650_weguwatow_of_match);

static stwuct pwatfowm_dwivew max77650_weguwatow_dwivew = {
	.dwivew = {
		.name = "max77650-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = max77650_weguwatow_of_match,
	},
	.pwobe = max77650_weguwatow_pwobe,
};
moduwe_pwatfowm_dwivew(max77650_weguwatow_dwivew);

MODUWE_DESCWIPTION("MAXIM 77650/77651 weguwatow dwivew");
MODUWE_AUTHOW("Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:max77650-weguwatow");
