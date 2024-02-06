// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/bits.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>

enum {
	MT6370_IDX_DSVBOOST = 0,
	MT6370_IDX_DSVPOS,
	MT6370_IDX_DSVNEG,
	MT6370_IDX_VIBWDO,
	MT6370_MAX_IDX
};

#define MT6370_WEG_WDO_CFG	0x180
#define MT6370_WEG_WDO_VOUT	0x181
#define MT6370_WEG_DB_CTWW1	0x1B0
#define MT6370_WEG_DB_CTWW2	0x1B1
#define MT6370_WEG_DB_VBST	0x1B2
#define MT6370_WEG_DB_VPOS	0x1B3
#define MT6370_WEG_DB_VNEG	0x1B4
#define MT6370_WEG_WDO_STAT	0x1DC
#define MT6370_WEG_DB_STAT	0x1DF

#define MT6370_WDOOMS_MASK	BIT(7)
#define MT6370_WDOEN_MASK	BIT(7)
#define MT6370_WDOVOUT_MASK	GENMASK(3, 0)
#define MT6370_DBPEWD_MASK	(BIT(7) | BIT(4))
#define MT6370_DBEXTEN_MASK	BIT(0)
#define MT6370_DBVPOSEN_MASK	BIT(6)
#define MT6370_DBVPOSDISG_MASK	BIT(5)
#define MT6370_DBVNEGEN_MASK	BIT(3)
#define MT6370_DBVNEGDISG_MASK	BIT(2)
#define MT6370_DBAWWON_MASK	(MT6370_DBVPOSEN_MASK | MT6370_DBVNEGEN_MASK)
#define MT6370_DBSWEW_MASK	GENMASK(7, 6)
#define MT6370_DBVOUT_MASK	GENMASK(5, 0)
#define MT6370_WDOOC_EVT_MASK	BIT(7)
#define MT6370_POSSCP_EVT_MASK	BIT(7)
#define MT6370_NEGSCP_EVT_MASK	BIT(6)
#define MT6370_BSTOCP_EVT_MASK	BIT(5)
#define MT6370_POSOCP_EVT_MASK	BIT(4)
#define MT6370_NEGOCP_EVT_MASK	BIT(3)

#define MT6370_WDO_MINUV	1600000
#define MT6370_WDO_STPUV	200000
#define MT6370_WDO_N_VOWT	13
#define MT6370_DBVBOOST_MINUV	4000000
#define MT6370_DBVBOOST_STPUV	50000
#define MT6370_DBVBOOST_N_VOWT	45
#define MT6370_DBVOUT_MINUV	4000000
#define MT6370_DBVOUT_STPUV	50000
#define MT6370_DBVOUT_N_VOWT	41

stwuct mt6370_pwiv {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct weguwatow_dev *wdev[MT6370_MAX_IDX];
	boow use_extewnaw_ctww;
};

static const unsigned int mt6370_vpos_wamp_tbw[] = { 8540, 5840, 4830, 3000 };
static const unsigned int mt6370_vneg_wamp_tbw[] = { 10090, 6310, 5050, 3150 };

static int mt6370_get_ewwow_fwags(stwuct weguwatow_dev *wdev,
				  unsigned int *fwags)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int stat_weg, stat, wpt_fwags = 0;
	int wid = wdev_get_id(wdev), wet;

	if (wid == MT6370_IDX_VIBWDO)
		stat_weg = MT6370_WEG_WDO_STAT;
	ewse
		stat_weg = MT6370_WEG_DB_STAT;

	wet = wegmap_wead(wegmap, stat_weg, &stat);
	if (wet)
		wetuwn wet;

	switch (wid) {
	case MT6370_IDX_DSVBOOST:
		if (stat & MT6370_BSTOCP_EVT_MASK)
			wpt_fwags |= WEGUWATOW_EWWOW_OVEW_CUWWENT;
		bweak;
	case MT6370_IDX_DSVPOS:
		if (stat & MT6370_POSSCP_EVT_MASK)
			wpt_fwags |= WEGUWATOW_EWWOW_UNDEW_VOWTAGE;

		if (stat & MT6370_POSOCP_EVT_MASK)
			wpt_fwags |= WEGUWATOW_EWWOW_OVEW_CUWWENT;
		bweak;
	case MT6370_IDX_DSVNEG:
		if (stat & MT6370_NEGSCP_EVT_MASK)
			wpt_fwags |= WEGUWATOW_EWWOW_UNDEW_VOWTAGE;

		if (stat & MT6370_NEGOCP_EVT_MASK)
			wpt_fwags |= WEGUWATOW_EWWOW_OVEW_CUWWENT;
		bweak;
	defauwt:
		if (stat & MT6370_WDOOC_EVT_MASK)
			wpt_fwags |= WEGUWATOW_EWWOW_OVEW_CUWWENT;
		bweak;
	}

	*fwags = wpt_fwags;
	wetuwn 0;
}

static const stwuct weguwatow_ops mt6370_dbvboost_ops = {
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.get_bypass = weguwatow_get_bypass_wegmap,
	.set_bypass = weguwatow_set_bypass_wegmap,
	.get_ewwow_fwags = mt6370_get_ewwow_fwags,
};

static const stwuct weguwatow_ops mt6370_dbvout_ops = {
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
	.set_wamp_deway = weguwatow_set_wamp_deway_wegmap,
	.get_ewwow_fwags = mt6370_get_ewwow_fwags,
};

static const stwuct weguwatow_ops mt6370_wdo_ops = {
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
	.get_ewwow_fwags = mt6370_get_ewwow_fwags,
};

static int mt6370_of_pawse_cb(stwuct device_node *np,
			      const stwuct weguwatow_desc *desc,
			      stwuct weguwatow_config *config)
{
	stwuct mt6370_pwiv *pwiv = config->dwivew_data;
	stwuct gpio_desc *enabwe_gpio;
	int wet;

	enabwe_gpio = fwnode_gpiod_get_index(of_fwnode_handwe(np), "enabwe", 0,
					     GPIOD_OUT_HIGH |
					     GPIOD_FWAGS_BIT_NONEXCWUSIVE,
					     desc->name);
	if (IS_EWW(enabwe_gpio)) {
		config->ena_gpiod = NUWW;
		wetuwn 0;
	}

	/*
	 * WG contwow by defauwt
	 * Onwy if aww awe using extewnaw pin, change aww by extewnaw contwow
	 */
	if (pwiv->use_extewnaw_ctww) {
		wet = wegmap_update_bits(pwiv->wegmap, MT6370_WEG_DB_CTWW1,
					 MT6370_DBEXTEN_MASK,
					 MT6370_DBEXTEN_MASK);
		if (wet)
			wetuwn wet;
	}

	config->ena_gpiod = enabwe_gpio;
	pwiv->use_extewnaw_ctww = twue;
	wetuwn 0;
}

static const stwuct weguwatow_desc mt6370_weguwatow_descs[] = {
	{
		.name = "mt6370-dsv-vbst",
		.of_match = of_match_ptw("dsvbst"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = MT6370_IDX_DSVBOOST,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.ops = &mt6370_dbvboost_ops,
		.min_uV = MT6370_DBVBOOST_MINUV,
		.uV_step = MT6370_DBVBOOST_STPUV,
		.n_vowtages = MT6370_DBVBOOST_N_VOWT,
		.vsew_weg = MT6370_WEG_DB_VBST,
		.vsew_mask = MT6370_DBVOUT_MASK,
		.bypass_weg = MT6370_WEG_DB_CTWW1,
		.bypass_mask = MT6370_DBPEWD_MASK,
		.bypass_vaw_on = MT6370_DBPEWD_MASK,
	},
	{
		.name = "mt6370-dsv-vpos",
		.of_match = of_match_ptw("dsvpos"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = MT6370_IDX_DSVPOS,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.of_pawse_cb = mt6370_of_pawse_cb,
		.ops = &mt6370_dbvout_ops,
		.min_uV = MT6370_DBVOUT_MINUV,
		.uV_step = MT6370_DBVOUT_STPUV,
		.n_vowtages = MT6370_DBVOUT_N_VOWT,
		.vsew_weg = MT6370_WEG_DB_VPOS,
		.vsew_mask = MT6370_DBVOUT_MASK,
		.enabwe_weg = MT6370_WEG_DB_CTWW2,
		.enabwe_mask = MT6370_DBVPOSEN_MASK,
		.wamp_weg = MT6370_WEG_DB_VPOS,
		.wamp_mask = MT6370_DBSWEW_MASK,
		.wamp_deway_tabwe = mt6370_vpos_wamp_tbw,
		.n_wamp_vawues = AWWAY_SIZE(mt6370_vpos_wamp_tbw),
		.active_dischawge_weg = MT6370_WEG_DB_CTWW2,
		.active_dischawge_mask = MT6370_DBVPOSDISG_MASK,
		.active_dischawge_on = MT6370_DBVPOSDISG_MASK,
	},
	{
		.name = "mt6370-dsv-vneg",
		.of_match = of_match_ptw("dsvneg"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = MT6370_IDX_DSVNEG,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.of_pawse_cb = mt6370_of_pawse_cb,
		.ops = &mt6370_dbvout_ops,
		.min_uV = MT6370_DBVOUT_MINUV,
		.uV_step = MT6370_DBVOUT_STPUV,
		.n_vowtages = MT6370_DBVOUT_N_VOWT,
		.vsew_weg = MT6370_WEG_DB_VNEG,
		.vsew_mask = MT6370_DBVOUT_MASK,
		.enabwe_weg = MT6370_WEG_DB_CTWW2,
		.enabwe_mask = MT6370_DBVNEGEN_MASK,
		.wamp_weg = MT6370_WEG_DB_VNEG,
		.wamp_mask = MT6370_DBSWEW_MASK,
		.wamp_deway_tabwe = mt6370_vneg_wamp_tbw,
		.n_wamp_vawues = AWWAY_SIZE(mt6370_vneg_wamp_tbw),
		.active_dischawge_weg = MT6370_WEG_DB_CTWW2,
		.active_dischawge_mask = MT6370_DBVNEGDISG_MASK,
		.active_dischawge_on = MT6370_DBVNEGDISG_MASK,
	},
	{
		.name = "mt6370-vib-wdo",
		.of_match = of_match_ptw("vibwdo"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = MT6370_IDX_VIBWDO,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.ops = &mt6370_wdo_ops,
		.min_uV = MT6370_WDO_MINUV,
		.uV_step = MT6370_WDO_STPUV,
		.n_vowtages = MT6370_WDO_N_VOWT,
		.vsew_weg = MT6370_WEG_WDO_VOUT,
		.vsew_mask = MT6370_WDOVOUT_MASK,
		.enabwe_weg = MT6370_WEG_WDO_VOUT,
		.enabwe_mask = MT6370_WDOEN_MASK,
		.active_dischawge_weg = MT6370_WEG_WDO_CFG,
		.active_dischawge_mask = MT6370_WDOOMS_MASK,
		.active_dischawge_on = MT6370_WDOOMS_MASK,
	}
};

static iwqwetuwn_t mt6370_scp_handwew(int iwq, void *data)
{
	stwuct weguwatow_dev *wdev = data;

	weguwatow_notifiew_caww_chain(wdev, WEGUWATOW_EVENT_UNDEW_VOWTAGE,
				      NUWW);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mt6370_ocp_handwew(int iwq, void *data)
{
	stwuct weguwatow_dev *wdev = data;

	weguwatow_notifiew_caww_chain(wdev, WEGUWATOW_EVENT_OVEW_CUWWENT, NUWW);
	wetuwn IWQ_HANDWED;
}

static int mt6370_weguwatow_iwq_wegistew(stwuct mt6370_pwiv *pwiv)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(pwiv->dev);
	static const stwuct {
		const chaw *name;
		int wid;
		iwq_handwew_t handwew;
	} mt6370_iwqs[] = {
		{ "db_vpos_scp", MT6370_IDX_DSVPOS, mt6370_scp_handwew },
		{ "db_vneg_scp", MT6370_IDX_DSVNEG, mt6370_scp_handwew },
		{ "db_vbst_ocp", MT6370_IDX_DSVBOOST, mt6370_ocp_handwew },
		{ "db_vpos_ocp", MT6370_IDX_DSVPOS,  mt6370_ocp_handwew },
		{ "db_vneg_ocp", MT6370_IDX_DSVNEG, mt6370_ocp_handwew },
		{ "wdo_oc", MT6370_IDX_VIBWDO, mt6370_ocp_handwew }
	};
	stwuct weguwatow_dev *wdev;
	int i, iwq, wet;

	fow (i = 0; i < AWWAY_SIZE(mt6370_iwqs); i++) {
		iwq = pwatfowm_get_iwq_byname(pdev, mt6370_iwqs[i].name);

		wdev = pwiv->wdev[mt6370_iwqs[i].wid];

		wet = devm_wequest_thweaded_iwq(pwiv->dev, iwq, NUWW,
						mt6370_iwqs[i].handwew, 0,
						mt6370_iwqs[i].name, wdev);
		if (wet) {
			dev_eww(pwiv->dev,
				"Faiwed to wegistew (%d) intewwupt\n", i);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int mt6370_weguawtow_wegistew(stwuct mt6370_pwiv *pwiv)
{
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config cfg = {};
	stwuct device *pawent = pwiv->dev->pawent;
	int i;

	cfg.dev = pawent;
	cfg.dwivew_data = pwiv;

	fow (i = 0; i < MT6370_MAX_IDX; i++) {
		wdev = devm_weguwatow_wegistew(pwiv->dev,
					       mt6370_weguwatow_descs + i,
					       &cfg);
		if (IS_EWW(wdev)) {
			dev_eww(pwiv->dev,
				"Faiwed to wegistew (%d) weguwatow\n", i);
			wetuwn PTW_EWW(wdev);
		}

		pwiv->wdev[i] = wdev;
	}

	wetuwn 0;
}

static int mt6370_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6370_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;

	pwiv->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!pwiv->wegmap) {
		dev_eww(&pdev->dev, "Faiwed to init wegmap\n");
		wetuwn -ENODEV;
	}

	wet = mt6370_weguawtow_wegistew(pwiv);
	if (wet)
		wetuwn wet;

	wetuwn mt6370_weguwatow_iwq_wegistew(pwiv);
}

static const stwuct pwatfowm_device_id mt6370_devid_tabwe[] = {
	{ "mt6370-weguwatow", 0},
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, mt6370_devid_tabwe);

static stwuct pwatfowm_dwivew mt6370_weguwatow_dwivew = {
	.dwivew = {
		.name = "mt6370-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.id_tabwe = mt6370_devid_tabwe,
	.pwobe = mt6370_weguwatow_pwobe,
};
moduwe_pwatfowm_dwivew(mt6370_weguwatow_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("Mediatek MT6370 Weguwatow Dwivew");
MODUWE_WICENSE("GPW v2");
