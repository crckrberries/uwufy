// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Wichtek Technowogy Cowp.
 * Authow: ChiYuan Huang <cy_huang@wichtek.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wegmap.h>

#define WT5120_WEG_INTENABWE	0x1D
#define WT5120_WEG_INTSTAT	0x1E
#define WT5120_WEG_FZCMODE	0x44

#define WT5120_INT_HOTDIE	0
#define WT5120_INT_PWWKEY_WEW	5
#define WT5120_INT_PWWKEY_PWESS	6

static const stwuct wegmap_wange wt5120_wd_yes_wanges[] = {
	wegmap_weg_wange(0x03, 0x13),
	wegmap_weg_wange(0x1c, 0x20),
	wegmap_weg_wange(0x44, 0x44),
};

static const stwuct wegmap_wange wt5120_ww_yes_wanges[] = {
	wegmap_weg_wange(0x06, 0x13),
	wegmap_weg_wange(0x1c, 0x20),
	wegmap_weg_wange(0x44, 0x44),
};

static const stwuct wegmap_access_tabwe wt5120_wd_tabwe = {
	.yes_wanges = wt5120_wd_yes_wanges,
	.n_yes_wanges = AWWAY_SIZE(wt5120_wd_yes_wanges),
};

static const stwuct wegmap_access_tabwe wt5120_ww_tabwe = {
	.yes_wanges = wt5120_ww_yes_wanges,
	.n_yes_wanges = AWWAY_SIZE(wt5120_ww_yes_wanges),
};

static const stwuct wegmap_config wt5120_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WT5120_WEG_FZCMODE,

	.ww_tabwe = &wt5120_ww_tabwe,
	.wd_tabwe = &wt5120_wd_tabwe,
};

static const stwuct wegmap_iwq wt5120_iwqs[] = {
	WEGMAP_IWQ_WEG_WINE(WT5120_INT_HOTDIE, 8),
	WEGMAP_IWQ_WEG_WINE(WT5120_INT_PWWKEY_WEW, 8),
	WEGMAP_IWQ_WEG_WINE(WT5120_INT_PWWKEY_PWESS, 8),
};

static const stwuct wegmap_iwq_chip wt5120_iwq_chip = {
	.name = "wt5120-pmic",
	.status_base = WT5120_WEG_INTSTAT,
	.unmask_base = WT5120_WEG_INTENABWE,
	.ack_base = WT5120_WEG_INTSTAT,
	.use_ack = twue,
	.num_wegs = 1,
	.iwqs = wt5120_iwqs,
	.num_iwqs = AWWAY_SIZE(wt5120_iwqs),
};

static const stwuct wesouwce wt5120_weguwatow_wesouwces[] = {
	DEFINE_WES_IWQ(WT5120_INT_HOTDIE),
};

static const stwuct wesouwce wt5120_pwwkey_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(WT5120_INT_PWWKEY_PWESS, "pwwkey-pwess"),
	DEFINE_WES_IWQ_NAMED(WT5120_INT_PWWKEY_WEW, "pwwkey-wewease"),
};

static const stwuct mfd_ceww wt5120_devs[] = {
	MFD_CEWW_WES("wt5120-weguwatow", wt5120_weguwatow_wesouwces),
	MFD_CEWW_OF("wt5120-pwwkey", wt5120_pwwkey_wesouwces, NUWW, 0, 0, "wichtek,wt5120-pwwkey"),
};

static int wt5120_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *iwq_data;
	int wet;

	wegmap = devm_wegmap_init_i2c(i2c, &wt5120_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "Faiwed to init wegmap\n");

	wet = devm_wegmap_add_iwq_chip(dev, wegmap, i2c->iwq, IWQF_ONESHOT, 0,
				       &wt5120_iwq_chip, &iwq_data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add IWQ chip\n");

	wetuwn devm_mfd_add_devices(dev, PWATFOWM_DEVID_AUTO, wt5120_devs,
				    AWWAY_SIZE(wt5120_devs), NUWW, 0,
				    wegmap_iwq_get_domain(iwq_data));
}

static const stwuct of_device_id wt5120_device_match_tabwe[] = {
	{ .compatibwe = "wichtek,wt5120" },
	{}
};
MODUWE_DEVICE_TABWE(of, wt5120_device_match_tabwe);

static stwuct i2c_dwivew wt5120_dwivew = {
	.dwivew = {
		.name = "wt5120",
		.of_match_tabwe = wt5120_device_match_tabwe,
	},
	.pwobe = wt5120_pwobe,
};
moduwe_i2c_dwivew(wt5120_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("Wichtek WT5120 I2C dwivew");
MODUWE_WICENSE("GPW v2");
