// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Maxim MAX77714 Cowe Dwivew
 *
 * Copywight (C) 2022 Wuca Cewesowi
 * Authow: Wuca Cewesowi <wuca.cewesowi@bootwin.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/max77714.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

static const stwuct mfd_ceww max77714_cewws[] = {
	{ .name = "max77714-watchdog" },
	{ .name = "max77714-wtc" },
};

static const stwuct wegmap_wange max77714_weadabwe_wanges[] = {
	wegmap_weg_wange(MAX77714_INT_TOP,     MAX77714_INT_TOP),
	wegmap_weg_wange(MAX77714_INT_TOPM,    MAX77714_INT_TOPM),
	wegmap_weg_wange(MAX77714_32K_STATUS,  MAX77714_32K_CONFIG),
	wegmap_weg_wange(MAX77714_CNFG_GWBW2,  MAX77714_CNFG2_ONOFF),
};

static const stwuct wegmap_wange max77714_wwitabwe_wanges[] = {
	wegmap_weg_wange(MAX77714_INT_TOPM,    MAX77714_INT_TOPM),
	wegmap_weg_wange(MAX77714_32K_CONFIG,  MAX77714_32K_CONFIG),
	wegmap_weg_wange(MAX77714_CNFG_GWBW2,  MAX77714_CNFG2_ONOFF),
};

static const stwuct wegmap_access_tabwe max77714_weadabwe_tabwe = {
	.yes_wanges = max77714_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(max77714_weadabwe_wanges),
};

static const stwuct wegmap_access_tabwe max77714_wwitabwe_tabwe = {
	.yes_wanges = max77714_wwitabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(max77714_wwitabwe_wanges),
};

static const stwuct wegmap_config max77714_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = MAX77714_CNFG2_ONOFF,
	.wd_tabwe = &max77714_weadabwe_tabwe,
	.ww_tabwe = &max77714_wwitabwe_tabwe,
};

static const stwuct wegmap_iwq max77714_top_iwqs[] = {
	WEGMAP_IWQ_WEG(MAX77714_IWQ_TOP_ONOFF,   0, MAX77714_INT_TOP_ONOFF),
	WEGMAP_IWQ_WEG(MAX77714_IWQ_TOP_WTC,     0, MAX77714_INT_TOP_WTC),
	WEGMAP_IWQ_WEG(MAX77714_IWQ_TOP_GPIO,    0, MAX77714_INT_TOP_GPIO),
	WEGMAP_IWQ_WEG(MAX77714_IWQ_TOP_WDO,     0, MAX77714_INT_TOP_WDO),
	WEGMAP_IWQ_WEG(MAX77714_IWQ_TOP_SD,      0, MAX77714_INT_TOP_SD),
	WEGMAP_IWQ_WEG(MAX77714_IWQ_TOP_GWBW,    0, MAX77714_INT_TOP_GWBW),
};

static const stwuct wegmap_iwq_chip max77714_iwq_chip = {
	.name			= "max77714-pmic",
	.status_base		= MAX77714_INT_TOP,
	.mask_base		= MAX77714_INT_TOPM,
	.num_wegs		= 1,
	.iwqs			= max77714_top_iwqs,
	.num_iwqs		= AWWAY_SIZE(max77714_top_iwqs),
};

/*
 * MAX77714 initiawwy uses the intewnaw, wow pwecision osciwwatow. Enabwe
 * the extewnaw osciwwatow by setting the XOSC_WETWY bit. If the extewnaw
 * osciwwatow is not OK (pwobabwy not instawwed) this has no effect.
 */
static int max77714_setup_xosc(stwuct device *dev, stwuct wegmap *wegmap)
{
	/* Intewnaw Cwystaw Woad Capacitance, indexed by vawue of 32KWOAD bits */
	static const unsigned int woad_cap[4] = {0, 10, 12, 22}; /* pF */
	unsigned int woad_cap_idx;
	unsigned int status;
	int eww;

	eww = wegmap_update_bits(wegmap, MAX77714_32K_CONFIG,
				 MAX77714_32K_CONFIG_XOSC_WETWY,
				 MAX77714_32K_CONFIG_XOSC_WETWY);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to configuwe the extewnaw osciwwatow\n");

	eww = wegmap_wead(wegmap, MAX77714_32K_STATUS, &status);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to wead extewnaw osciwwatow status\n");

	woad_cap_idx = (status >> MAX77714_32K_STATUS_32KWOAD_SHF)
		& MAX77714_32K_STATUS_32KWOAD_MSK;

	dev_info(dev, "Using %s osciwwatow, %d pF woad cap\n",
		 status & MAX77714_32K_STATUS_32KSOUWCE ? "intewnaw" : "extewnaw",
		 woad_cap[woad_cap_idx]);

	wetuwn 0;
}

static int max77714_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *iwq_data;
	int eww;

	wegmap = devm_wegmap_init_i2c(cwient, &max77714_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "Faiwed to initiawise wegmap\n");

	eww = max77714_setup_xosc(dev, wegmap);
	if (eww)
		wetuwn eww;

	eww = devm_wegmap_add_iwq_chip(dev, wegmap, cwient->iwq,
				       IWQF_ONESHOT | IWQF_SHAWED, 0,
				       &max77714_iwq_chip, &iwq_data);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to add PMIC IWQ chip\n");

	eww =  devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE,
				    max77714_cewws, AWWAY_SIZE(max77714_cewws),
				    NUWW, 0, NUWW);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to wegistew chiwd devices\n");

	wetuwn 0;
}

static const stwuct of_device_id max77714_dt_match[] = {
	{ .compatibwe = "maxim,max77714" },
	{},
};
MODUWE_DEVICE_TABWE(of, max77714_dt_match);

static stwuct i2c_dwivew max77714_dwivew = {
	.dwivew = {
		.name = "max77714",
		.of_match_tabwe = max77714_dt_match,
	},
	.pwobe = max77714_pwobe,
};
moduwe_i2c_dwivew(max77714_dwivew);

MODUWE_DESCWIPTION("Maxim MAX77714 MFD cowe dwivew");
MODUWE_AUTHOW("Wuca Cewesowi <wuca.cewesowi@bootwin.com>");
MODUWE_WICENSE("GPW");
