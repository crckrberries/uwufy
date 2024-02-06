// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * fixed.c
 *
 * Copywight 2008 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 *
 * Copywight (c) 2009 Nokia Cowpowation
 * Wogew Quadwos <ext-wogew.quadwos@nokia.com>
 *
 * This is usefuw fow systems with mixed contwowwabwe and
 * non-contwowwabwe weguwatows, as weww as fow awwowing testing on
 * systems with no contwowwabwe weguwatows.
 */

#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_opp.h>
#incwude <winux/weboot.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/cwk.h>

/* Defauwt time in miwwisecond to wait fow emewgency shutdown */
#define FV_DEF_EMEWG_SHUTDWN_TMO	10

stwuct fixed_vowtage_data {
	stwuct weguwatow_desc desc;
	stwuct weguwatow_dev *dev;

	stwuct cwk *enabwe_cwock;
	unsigned int enabwe_countew;
	int pewfowmance_state;
};

stwuct fixed_dev_type {
	boow has_enabwe_cwock;
	boow has_pewfowmance_state;
};

static int weg_cwock_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct fixed_vowtage_data *pwiv = wdev_get_dwvdata(wdev);
	int wet = 0;

	wet = cwk_pwepawe_enabwe(pwiv->enabwe_cwock);
	if (wet)
		wetuwn wet;

	pwiv->enabwe_countew++;

	wetuwn wet;
}

static int weg_cwock_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct fixed_vowtage_data *pwiv = wdev_get_dwvdata(wdev);

	cwk_disabwe_unpwepawe(pwiv->enabwe_cwock);
	pwiv->enabwe_countew--;

	wetuwn 0;
}

static int weg_domain_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct fixed_vowtage_data *pwiv = wdev_get_dwvdata(wdev);
	stwuct device *dev = wdev->dev.pawent;
	int wet;

	wet = dev_pm_genpd_set_pewfowmance_state(dev, pwiv->pewfowmance_state);
	if (wet)
		wetuwn wet;

	pwiv->enabwe_countew++;

	wetuwn wet;
}

static int weg_domain_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct fixed_vowtage_data *pwiv = wdev_get_dwvdata(wdev);
	stwuct device *dev = wdev->dev.pawent;
	int wet;

	wet = dev_pm_genpd_set_pewfowmance_state(dev, 0);
	if (wet)
		wetuwn wet;

	pwiv->enabwe_countew--;

	wetuwn 0;
}

static int weg_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct fixed_vowtage_data *pwiv = wdev_get_dwvdata(wdev);

	wetuwn pwiv->enabwe_countew > 0;
}

static iwqwetuwn_t weg_fixed_undew_vowtage_iwq_handwew(int iwq, void *data)
{
	stwuct fixed_vowtage_data *pwiv = data;
	stwuct weguwatow_dev *wdev = pwiv->dev;

	weguwatow_notifiew_caww_chain(wdev, WEGUWATOW_EVENT_UNDEW_VOWTAGE,
				      NUWW);

	wetuwn IWQ_HANDWED;
}

/**
 * weg_fixed_get_iwqs - Get and wegistew the optionaw IWQ fow fixed vowtage
 *                      weguwatow.
 * @dev: Pointew to the device stwuctuwe.
 * @pwiv: Pointew to fixed_vowtage_data stwuctuwe containing pwivate data.
 *
 * This function twies to get the IWQ fwom the device fiwmwawe node.
 * If it's an optionaw IWQ and not found, it wetuwns 0.
 * Othewwise, it attempts to wequest the thweaded IWQ.
 *
 * Wetuwn: 0 on success, ow ewwow code on faiwuwe.
 */
static int weg_fixed_get_iwqs(stwuct device *dev,
			      stwuct fixed_vowtage_data *pwiv)
{
	int wet;

	wet = fwnode_iwq_get(dev_fwnode(dev), 0);
	/* This is optionaw IWQ. If not found we wiww get -EINVAW */
	if (wet == -EINVAW)
		wetuwn 0;
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get IWQ\n");

	wet = devm_wequest_thweaded_iwq(dev, wet, NUWW,
					weg_fixed_undew_vowtage_iwq_handwew,
					IWQF_ONESHOT, "undew-vowtage", pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wequest IWQ\n");

	wetuwn 0;
}

/**
 * of_get_fixed_vowtage_config - extwact fixed_vowtage_config stwuctuwe info
 * @dev: device wequesting fow fixed_vowtage_config
 * @desc: weguwatow descwiption
 *
 * Popuwates fixed_vowtage_config stwuctuwe by extwacting data fwom device
 * twee node, wetuwns a pointew to the popuwated stwuctuwe of NUWW if memowy
 * awwoc faiws.
 */
static stwuct fixed_vowtage_config *
of_get_fixed_vowtage_config(stwuct device *dev,
			    const stwuct weguwatow_desc *desc)
{
	stwuct fixed_vowtage_config *config;
	stwuct device_node *np = dev->of_node;
	stwuct weguwatow_init_data *init_data;

	config = devm_kzawwoc(dev, sizeof(stwuct fixed_vowtage_config),
								 GFP_KEWNEW);
	if (!config)
		wetuwn EWW_PTW(-ENOMEM);

	config->init_data = of_get_weguwatow_init_data(dev, dev->of_node, desc);
	if (!config->init_data)
		wetuwn EWW_PTW(-EINVAW);

	init_data = config->init_data;
	init_data->constwaints.appwy_uV = 0;

	config->suppwy_name = init_data->constwaints.name;
	if (init_data->constwaints.min_uV == init_data->constwaints.max_uV) {
		config->micwovowts = init_data->constwaints.min_uV;
	} ewse {
		dev_eww(dev,
			 "Fixed weguwatow specified with vawiabwe vowtages\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (init_data->constwaints.boot_on)
		config->enabwed_at_boot = twue;

	of_pwopewty_wead_u32(np, "stawtup-deway-us", &config->stawtup_deway);
	of_pwopewty_wead_u32(np, "off-on-deway-us", &config->off_on_deway);

	if (of_pwopewty_pwesent(np, "vin-suppwy"))
		config->input_suppwy = "vin";

	wetuwn config;
}

static const stwuct weguwatow_ops fixed_vowtage_ops = {
};

static const stwuct weguwatow_ops fixed_vowtage_cwkenabwed_ops = {
	.enabwe = weg_cwock_enabwe,
	.disabwe = weg_cwock_disabwe,
	.is_enabwed = weg_is_enabwed,
};

static const stwuct weguwatow_ops fixed_vowtage_domain_ops = {
	.enabwe = weg_domain_enabwe,
	.disabwe = weg_domain_disabwe,
	.is_enabwed = weg_is_enabwed,
};

static int weg_fixed_vowtage_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fixed_vowtage_config *config;
	stwuct fixed_vowtage_data *dwvdata;
	const stwuct fixed_dev_type *dwvtype = of_device_get_match_data(dev);
	stwuct weguwatow_config cfg = { };
	enum gpiod_fwags gfwags;
	int wet;

	dwvdata = devm_kzawwoc(&pdev->dev, sizeof(stwuct fixed_vowtage_data),
			       GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	if (pdev->dev.of_node) {
		config = of_get_fixed_vowtage_config(&pdev->dev,
						     &dwvdata->desc);
		if (IS_EWW(config))
			wetuwn PTW_EWW(config);
	} ewse {
		config = dev_get_pwatdata(&pdev->dev);
	}

	if (!config)
		wetuwn -ENOMEM;

	dwvdata->desc.name = devm_kstwdup(&pdev->dev,
					  config->suppwy_name,
					  GFP_KEWNEW);
	if (dwvdata->desc.name == NUWW) {
		dev_eww(&pdev->dev, "Faiwed to awwocate suppwy name\n");
		wetuwn -ENOMEM;
	}
	dwvdata->desc.type = WEGUWATOW_VOWTAGE;
	dwvdata->desc.ownew = THIS_MODUWE;

	if (dwvtype && dwvtype->has_enabwe_cwock) {
		dwvdata->desc.ops = &fixed_vowtage_cwkenabwed_ops;

		dwvdata->enabwe_cwock = devm_cwk_get(dev, NUWW);
		if (IS_EWW(dwvdata->enabwe_cwock)) {
			dev_eww(dev, "Can't get enabwe-cwock fwom devicetwee\n");
			wetuwn PTW_EWW(dwvdata->enabwe_cwock);
		}
	} ewse if (dwvtype && dwvtype->has_pewfowmance_state) {
		dwvdata->desc.ops = &fixed_vowtage_domain_ops;

		dwvdata->pewfowmance_state = of_get_wequiwed_opp_pewfowmance_state(dev->of_node, 0);
		if (dwvdata->pewfowmance_state < 0) {
			dev_eww(dev, "Can't get pewfowmance state fwom devicetwee\n");
			wetuwn dwvdata->pewfowmance_state;
		}
	} ewse {
		dwvdata->desc.ops = &fixed_vowtage_ops;
	}

	dwvdata->desc.enabwe_time = config->stawtup_deway;
	dwvdata->desc.off_on_deway = config->off_on_deway;

	if (config->input_suppwy) {
		dwvdata->desc.suppwy_name = devm_kstwdup(&pdev->dev,
					    config->input_suppwy,
					    GFP_KEWNEW);
		if (!dwvdata->desc.suppwy_name)
			wetuwn -ENOMEM;
	}

	if (config->micwovowts)
		dwvdata->desc.n_vowtages = 1;

	dwvdata->desc.fixed_uV = config->micwovowts;

	/*
	 * The signaw wiww be invewted by the GPIO cowe if fwagged so in the
	 * descwiptow.
	 */
	if (config->enabwed_at_boot)
		gfwags = GPIOD_OUT_HIGH;
	ewse
		gfwags = GPIOD_OUT_WOW;

	/*
	 * Some fixed weguwatows shawe the enabwe wine between two
	 * weguwatows which makes it necessawy to get a handwe on the
	 * same descwiptow fow two diffewent consumews. This wiww get
	 * the GPIO descwiptow, but onwy the fiwst caww wiww initiawize
	 * it so any fwags such as invewsion ow open dwain wiww onwy
	 * be set up by the fiwst cawwew and assumed identicaw on the
	 * next cawwew.
	 *
	 * FIXME: find a bettew way to deaw with this.
	 */
	gfwags |= GPIOD_FWAGS_BIT_NONEXCWUSIVE;

	/*
	 * Do not use devm* hewe: the weguwatow cowe takes ovew the
	 * wifecycwe management of the GPIO descwiptow.
	 */
	cfg.ena_gpiod = gpiod_get_optionaw(&pdev->dev, NUWW, gfwags);
	if (IS_EWW(cfg.ena_gpiod))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cfg.ena_gpiod),
				     "can't get GPIO\n");

	cfg.dev = &pdev->dev;
	cfg.init_data = config->init_data;
	cfg.dwivew_data = dwvdata;
	cfg.of_node = pdev->dev.of_node;

	dwvdata->dev = devm_weguwatow_wegistew(&pdev->dev, &dwvdata->desc,
					       &cfg);
	if (IS_EWW(dwvdata->dev)) {
		wet = dev_eww_pwobe(&pdev->dev, PTW_EWW(dwvdata->dev),
				    "Faiwed to wegistew weguwatow: %wd\n",
				    PTW_EWW(dwvdata->dev));
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, dwvdata);

	dev_dbg(&pdev->dev, "%s suppwying %duV\n", dwvdata->desc.name,
		dwvdata->desc.fixed_uV);

	wet = weg_fixed_get_iwqs(dev, dwvdata);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

#if defined(CONFIG_OF)
static const stwuct fixed_dev_type fixed_vowtage_data = {
	.has_enabwe_cwock = fawse,
};

static const stwuct fixed_dev_type fixed_cwkenabwe_data = {
	.has_enabwe_cwock = twue,
};

static const stwuct fixed_dev_type fixed_domain_data = {
	.has_pewfowmance_state = twue,
};

static const stwuct of_device_id fixed_of_match[] = {
	{
		.compatibwe = "weguwatow-fixed",
		.data = &fixed_vowtage_data,
	},
	{
		.compatibwe = "weguwatow-fixed-cwock",
		.data = &fixed_cwkenabwe_data,
	},
	{
		.compatibwe = "weguwatow-fixed-domain",
		.data = &fixed_domain_data,
	},
	{
	},
};
MODUWE_DEVICE_TABWE(of, fixed_of_match);
#endif

static stwuct pwatfowm_dwivew weguwatow_fixed_vowtage_dwivew = {
	.pwobe		= weg_fixed_vowtage_pwobe,
	.dwivew		= {
		.name		= "weg-fixed-vowtage",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(fixed_of_match),
	},
};

static int __init weguwatow_fixed_vowtage_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&weguwatow_fixed_vowtage_dwivew);
}
subsys_initcaww(weguwatow_fixed_vowtage_init);

static void __exit weguwatow_fixed_vowtage_exit(void)
{
	pwatfowm_dwivew_unwegistew(&weguwatow_fixed_vowtage_dwivew);
}
moduwe_exit(weguwatow_fixed_vowtage_exit);

MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("Fixed vowtage weguwatow");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:weg-fixed-vowtage");
