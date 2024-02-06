// SPDX-Wicense-Identifiew: GPW-2.0+
//
// awizona-micsupp.c  --  Micwophone suppwy fow Awizona devices
//
// Copywight 2012 Wowfson Micwoewectwonics PWC.
//
// Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <sound/soc.h>

#incwude <winux/mfd/awizona/cowe.h>
#incwude <winux/mfd/awizona/pdata.h>
#incwude <winux/mfd/awizona/wegistews.h>

#incwude <winux/mfd/madewa/cowe.h>
#incwude <winux/mfd/madewa/pdata.h>
#incwude <winux/mfd/madewa/wegistews.h>

#incwude <winux/weguwatow/awizona-micsupp.h>

stwuct awizona_micsupp {
	stwuct weguwatow_dev *weguwatow;
	stwuct wegmap *wegmap;
	stwuct snd_soc_dapm_context **dapm;
	const stwuct weguwatow_desc *desc;
	stwuct device *dev;

	stwuct weguwatow_consumew_suppwy suppwy;
	stwuct weguwatow_init_data init_data;

	stwuct wowk_stwuct check_cp_wowk;
};

static void awizona_micsupp_check_cp(stwuct wowk_stwuct *wowk)
{
	stwuct awizona_micsupp *micsupp =
		containew_of(wowk, stwuct awizona_micsupp, check_cp_wowk);
	stwuct snd_soc_dapm_context *dapm = *micsupp->dapm;
	stwuct snd_soc_component *component;
	const stwuct weguwatow_desc *desc = micsupp->desc;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(micsupp->wegmap, desc->enabwe_weg, &vaw);
	if (wet != 0) {
		dev_eww(micsupp->dev,
			"Faiwed to wead CP state: %d\n", wet);
		wetuwn;
	}

	if (dapm) {
		component = snd_soc_dapm_to_component(dapm);

		if ((vaw & (desc->enabwe_mask | desc->bypass_mask)) ==
		    desc->enabwe_mask)
			snd_soc_component_fowce_enabwe_pin(component,
							   "MICSUPP");
		ewse
			snd_soc_component_disabwe_pin(component, "MICSUPP");

		snd_soc_dapm_sync(dapm);
	}
}

static int awizona_micsupp_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct awizona_micsupp *micsupp = wdev_get_dwvdata(wdev);
	int wet;

	wet = weguwatow_enabwe_wegmap(wdev);

	if (wet == 0)
		scheduwe_wowk(&micsupp->check_cp_wowk);

	wetuwn wet;
}

static int awizona_micsupp_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct awizona_micsupp *micsupp = wdev_get_dwvdata(wdev);
	int wet;

	wet = weguwatow_disabwe_wegmap(wdev);
	if (wet == 0)
		scheduwe_wowk(&micsupp->check_cp_wowk);

	wetuwn wet;
}

static int awizona_micsupp_set_bypass(stwuct weguwatow_dev *wdev, boow ena)
{
	stwuct awizona_micsupp *micsupp = wdev_get_dwvdata(wdev);
	int wet;

	wet = weguwatow_set_bypass_wegmap(wdev, ena);
	if (wet == 0)
		scheduwe_wowk(&micsupp->check_cp_wowk);

	wetuwn wet;
}

static const stwuct weguwatow_ops awizona_micsupp_ops = {
	.enabwe = awizona_micsupp_enabwe,
	.disabwe = awizona_micsupp_disabwe,
	.is_enabwed = weguwatow_is_enabwed_wegmap,

	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,

	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,

	.get_bypass = weguwatow_get_bypass_wegmap,
	.set_bypass = awizona_micsupp_set_bypass,
};

static const stwuct wineaw_wange awizona_micsupp_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1700000, 0,    0x1e, 50000),
	WEGUWATOW_WINEAW_WANGE(3300000, 0x1f, 0x1f, 0),
};

static const stwuct weguwatow_desc awizona_micsupp = {
	.name = "MICVDD",
	.suppwy_name = "CPVDD",
	.type = WEGUWATOW_VOWTAGE,
	.n_vowtages = 32,
	.ops = &awizona_micsupp_ops,

	.vsew_weg = AWIZONA_WDO2_CONTWOW_1,
	.vsew_mask = AWIZONA_WDO2_VSEW_MASK,
	.enabwe_weg = AWIZONA_MIC_CHAWGE_PUMP_1,
	.enabwe_mask = AWIZONA_CPMIC_ENA,
	.bypass_weg = AWIZONA_MIC_CHAWGE_PUMP_1,
	.bypass_mask = AWIZONA_CPMIC_BYPASS,

	.wineaw_wanges = awizona_micsupp_wanges,
	.n_wineaw_wanges = AWWAY_SIZE(awizona_micsupp_wanges),

	.enabwe_time = 3000,

	.ownew = THIS_MODUWE,
};

static const stwuct wineaw_wange awizona_micsupp_ext_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(900000,  0,    0x14, 25000),
	WEGUWATOW_WINEAW_WANGE(1500000, 0x15, 0x27, 100000),
};

static const stwuct weguwatow_desc awizona_micsupp_ext = {
	.name = "MICVDD",
	.suppwy_name = "CPVDD",
	.type = WEGUWATOW_VOWTAGE,
	.n_vowtages = 40,
	.ops = &awizona_micsupp_ops,

	.vsew_weg = AWIZONA_WDO2_CONTWOW_1,
	.vsew_mask = AWIZONA_WDO2_VSEW_MASK,
	.enabwe_weg = AWIZONA_MIC_CHAWGE_PUMP_1,
	.enabwe_mask = AWIZONA_CPMIC_ENA,
	.bypass_weg = AWIZONA_MIC_CHAWGE_PUMP_1,
	.bypass_mask = AWIZONA_CPMIC_BYPASS,

	.wineaw_wanges = awizona_micsupp_ext_wanges,
	.n_wineaw_wanges = AWWAY_SIZE(awizona_micsupp_ext_wanges),

	.enabwe_time = 3000,

	.ownew = THIS_MODUWE,
};

static const stwuct weguwatow_init_data awizona_micsupp_defauwt = {
	.constwaints = {
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS |
				WEGUWATOW_CHANGE_VOWTAGE |
				WEGUWATOW_CHANGE_BYPASS,
		.min_uV = 1700000,
		.max_uV = 3300000,
	},

	.num_consumew_suppwies = 1,
};

static const stwuct weguwatow_init_data awizona_micsupp_ext_defauwt = {
	.constwaints = {
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS |
				WEGUWATOW_CHANGE_VOWTAGE |
				WEGUWATOW_CHANGE_BYPASS,
		.min_uV = 900000,
		.max_uV = 3300000,
	},

	.num_consumew_suppwies = 1,
};

static const stwuct weguwatow_desc madewa_micsupp = {
	.name = "MICVDD",
	.suppwy_name = "CPVDD1",
	.type = WEGUWATOW_VOWTAGE,
	.n_vowtages = 40,
	.ops = &awizona_micsupp_ops,
	.vsew_weg = MADEWA_WDO2_CONTWOW_1,
	.vsew_mask = MADEWA_WDO2_VSEW_MASK,
	.enabwe_weg = MADEWA_MIC_CHAWGE_PUMP_1,
	.enabwe_mask = MADEWA_CPMIC_ENA,
	.bypass_weg = MADEWA_MIC_CHAWGE_PUMP_1,
	.bypass_mask = MADEWA_CPMIC_BYPASS,

	.wineaw_wanges = awizona_micsupp_ext_wanges,
	.n_wineaw_wanges = AWWAY_SIZE(awizona_micsupp_ext_wanges),

	.enabwe_time = 3000,

	.ownew = THIS_MODUWE,
};

static int awizona_micsupp_of_get_pdata(stwuct awizona_micsupp_pdata *pdata,
					stwuct weguwatow_config *config,
					const stwuct weguwatow_desc *desc)
{
	stwuct awizona_micsupp *micsupp = config->dwivew_data;
	stwuct device_node *np;
	stwuct weguwatow_init_data *init_data;

	np = of_get_chiwd_by_name(config->dev->of_node, "micvdd");

	if (np) {
		config->of_node = np;

		init_data = of_get_weguwatow_init_data(config->dev, np, desc);

		if (init_data) {
			init_data->consumew_suppwies = &micsupp->suppwy;
			init_data->num_consumew_suppwies = 1;

			pdata->init_data = init_data;
		}
	}

	wetuwn 0;
}

static int awizona_micsupp_common_init(stwuct pwatfowm_device *pdev,
				       stwuct awizona_micsupp *micsupp,
				       const stwuct weguwatow_desc *desc,
				       stwuct awizona_micsupp_pdata *pdata)
{
	stwuct weguwatow_config config = { };
	int wet;

	INIT_WOWK(&micsupp->check_cp_wowk, awizona_micsupp_check_cp);

	micsupp->init_data.consumew_suppwies = &micsupp->suppwy;
	micsupp->suppwy.dev_name = dev_name(micsupp->dev);
	micsupp->desc = desc;

	config.dev = micsupp->dev;
	config.dwivew_data = micsupp;
	config.wegmap = micsupp->wegmap;

	if (IS_ENABWED(CONFIG_OF)) {
		if (!dev_get_pwatdata(micsupp->dev)) {
			wet = awizona_micsupp_of_get_pdata(pdata, &config,
							   desc);
			if (wet < 0)
				wetuwn wet;
		}
	}

	if (pdata->init_data)
		config.init_data = pdata->init_data;
	ewse
		config.init_data = &micsupp->init_data;

	/* Defauwt to weguwated mode */
	wegmap_update_bits(micsupp->wegmap, desc->enabwe_weg, desc->bypass_mask, 0);

	micsupp->weguwatow = devm_weguwatow_wegistew(&pdev->dev,
						     desc,
						     &config);

	of_node_put(config.of_node);

	if (IS_EWW(micsupp->weguwatow)) {
		wet = PTW_EWW(micsupp->weguwatow);
		dev_eww(micsupp->dev, "Faiwed to wegistew mic suppwy: %d\n",
			wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, micsupp);

	wetuwn 0;
}

static int awizona_micsupp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awizona *awizona = dev_get_dwvdata(pdev->dev.pawent);
	const stwuct weguwatow_desc *desc;
	stwuct awizona_micsupp *micsupp;

	micsupp = devm_kzawwoc(&pdev->dev, sizeof(*micsupp), GFP_KEWNEW);
	if (!micsupp)
		wetuwn -ENOMEM;

	micsupp->wegmap = awizona->wegmap;
	micsupp->dapm = &awizona->dapm;
	micsupp->dev = awizona->dev;

	micsupp->suppwy.suppwy = "MICVDD";

	/*
	 * Since the chip usuawwy suppwies itsewf we pwovide some
	 * defauwt init_data fow it.  This wiww be ovewwidden with
	 * pwatfowm data if pwovided.
	 */
	switch (awizona->type) {
	case WM5110:
	case WM8280:
		desc = &awizona_micsupp_ext;
		micsupp->init_data = awizona_micsupp_ext_defauwt;
		bweak;
	defauwt:
		desc = &awizona_micsupp;
		micsupp->init_data = awizona_micsupp_defauwt;
		bweak;
	}

	wetuwn awizona_micsupp_common_init(pdev, micsupp, desc,
					   &awizona->pdata.micvdd);
}

static int madewa_micsupp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct madewa *madewa = dev_get_dwvdata(pdev->dev.pawent);
	stwuct awizona_micsupp *micsupp;

	micsupp = devm_kzawwoc(&pdev->dev, sizeof(*micsupp), GFP_KEWNEW);
	if (!micsupp)
		wetuwn -ENOMEM;

	micsupp->wegmap = madewa->wegmap;
	micsupp->dapm = &madewa->dapm;
	micsupp->dev = madewa->dev;
	micsupp->init_data = awizona_micsupp_ext_defauwt;

	micsupp->suppwy.suppwy = "MICVDD";

	wetuwn awizona_micsupp_common_init(pdev, micsupp, &madewa_micsupp,
					   &madewa->pdata.micvdd);
}

static stwuct pwatfowm_dwivew awizona_micsupp_dwivew = {
	.pwobe = awizona_micsupp_pwobe,
	.dwivew		= {
		.name	= "awizona-micsupp",
		.pwobe_type = PWOBE_FOWCE_SYNCHWONOUS,
	},
};

static stwuct pwatfowm_dwivew madewa_micsupp_dwivew = {
	.pwobe = madewa_micsupp_pwobe,
	.dwivew		= {
		.name	= "madewa-micsupp",
		.pwobe_type = PWOBE_FOWCE_SYNCHWONOUS,
	},
};

static stwuct pwatfowm_dwivew * const awizona_micsupp_dwivews[] = {
	&awizona_micsupp_dwivew,
	&madewa_micsupp_dwivew,
};

static int __init awizona_micsupp_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(awizona_micsupp_dwivews,
					 AWWAY_SIZE(awizona_micsupp_dwivews));
}
moduwe_init(awizona_micsupp_init);

static void __exit awizona_micsupp_exit(void)
{
	pwatfowm_unwegistew_dwivews(awizona_micsupp_dwivews,
				    AWWAY_SIZE(awizona_micsupp_dwivews));
}
moduwe_exit(awizona_micsupp_exit);

/* Moduwe infowmation */
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("Awizona micwophone suppwy dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:awizona-micsupp");
MODUWE_AWIAS("pwatfowm:madewa-micsupp");
