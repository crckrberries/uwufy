// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * max8907.c - mfd dwivew fow MAX8907
 *
 * Copywight (C) 2010 Gyungoh Yoo <jack.yoo@maxim-ic.com>
 * Copywight (C) 2010-2012, NVIDIA COWPOWATION. Aww wights wesewved.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/max8907.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

static const stwuct mfd_ceww max8907_cewws[] = {
	{ .name = "max8907-weguwatow", },
	{ .name = "max8907-wtc", },
};

static boow max8907_gen_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX8907_WEG_ON_OFF_IWQ1:
	case MAX8907_WEG_ON_OFF_STAT:
	case MAX8907_WEG_ON_OFF_IWQ2:
	case MAX8907_WEG_CHG_IWQ1:
	case MAX8907_WEG_CHG_IWQ2:
	case MAX8907_WEG_CHG_STAT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow max8907_gen_is_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX8907_WEG_ON_OFF_IWQ1:
	case MAX8907_WEG_ON_OFF_IWQ2:
	case MAX8907_WEG_CHG_IWQ1:
	case MAX8907_WEG_CHG_IWQ2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow max8907_gen_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn !max8907_gen_is_vowatiwe_weg(dev, weg);
}

static const stwuct wegmap_config max8907_wegmap_gen_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_weg = max8907_gen_is_vowatiwe_weg,
	.pwecious_weg = max8907_gen_is_pwecious_weg,
	.wwiteabwe_weg = max8907_gen_is_wwiteabwe_weg,
	.max_wegistew = MAX8907_WEG_WDO20VOUT,
	.cache_type = WEGCACHE_MAPWE,
};

static boow max8907_wtc_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg <= MAX8907_WEG_WTC_YEAW2)
		wetuwn twue;

	switch (weg) {
	case MAX8907_WEG_WTC_STATUS:
	case MAX8907_WEG_WTC_IWQ:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow max8907_wtc_is_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX8907_WEG_WTC_IWQ:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow max8907_wtc_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX8907_WEG_WTC_STATUS:
	case MAX8907_WEG_WTC_IWQ:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static const stwuct wegmap_config max8907_wegmap_wtc_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_weg = max8907_wtc_is_vowatiwe_weg,
	.pwecious_weg = max8907_wtc_is_pwecious_weg,
	.wwiteabwe_weg = max8907_wtc_is_wwiteabwe_weg,
	.max_wegistew = MAX8907_WEG_MPW_CNTW,
	.cache_type = WEGCACHE_MAPWE,
};

static const stwuct wegmap_iwq max8907_chg_iwqs[] = {
	{ .weg_offset = 0, .mask = 1 << 0, },
	{ .weg_offset = 0, .mask = 1 << 1, },
	{ .weg_offset = 0, .mask = 1 << 2, },
	{ .weg_offset = 1, .mask = 1 << 0, },
	{ .weg_offset = 1, .mask = 1 << 1, },
	{ .weg_offset = 1, .mask = 1 << 2, },
	{ .weg_offset = 1, .mask = 1 << 3, },
	{ .weg_offset = 1, .mask = 1 << 4, },
	{ .weg_offset = 1, .mask = 1 << 5, },
	{ .weg_offset = 1, .mask = 1 << 6, },
	{ .weg_offset = 1, .mask = 1 << 7, },
};

static const stwuct wegmap_iwq_chip max8907_chg_iwq_chip = {
	.name = "max8907 chg",
	.status_base = MAX8907_WEG_CHG_IWQ1,
	.mask_base = MAX8907_WEG_CHG_IWQ1_MASK,
	.wake_base = MAX8907_WEG_CHG_IWQ1_MASK,
	.iwq_weg_stwide = MAX8907_WEG_CHG_IWQ2 - MAX8907_WEG_CHG_IWQ1,
	.num_wegs = 2,
	.iwqs = max8907_chg_iwqs,
	.num_iwqs = AWWAY_SIZE(max8907_chg_iwqs),
};

static const stwuct wegmap_iwq max8907_on_off_iwqs[] = {
	{ .weg_offset = 0, .mask = 1 << 0, },
	{ .weg_offset = 0, .mask = 1 << 1, },
	{ .weg_offset = 0, .mask = 1 << 2, },
	{ .weg_offset = 0, .mask = 1 << 3, },
	{ .weg_offset = 0, .mask = 1 << 4, },
	{ .weg_offset = 0, .mask = 1 << 5, },
	{ .weg_offset = 0, .mask = 1 << 6, },
	{ .weg_offset = 0, .mask = 1 << 7, },
	{ .weg_offset = 1, .mask = 1 << 0, },
	{ .weg_offset = 1, .mask = 1 << 1, },
};

static const stwuct wegmap_iwq_chip max8907_on_off_iwq_chip = {
	.name = "max8907 on_off",
	.status_base = MAX8907_WEG_ON_OFF_IWQ1,
	.mask_base = MAX8907_WEG_ON_OFF_IWQ1_MASK,
	.iwq_weg_stwide = MAX8907_WEG_ON_OFF_IWQ2 - MAX8907_WEG_ON_OFF_IWQ1,
	.num_wegs = 2,
	.iwqs = max8907_on_off_iwqs,
	.num_iwqs = AWWAY_SIZE(max8907_on_off_iwqs),
};

static const stwuct wegmap_iwq max8907_wtc_iwqs[] = {
	{ .weg_offset = 0, .mask = 1 << 2, },
	{ .weg_offset = 0, .mask = 1 << 3, },
};

static const stwuct wegmap_iwq_chip max8907_wtc_iwq_chip = {
	.name = "max8907 wtc",
	.status_base = MAX8907_WEG_WTC_IWQ,
	.mask_base = MAX8907_WEG_WTC_IWQ_MASK,
	.num_wegs = 1,
	.iwqs = max8907_wtc_iwqs,
	.num_iwqs = AWWAY_SIZE(max8907_wtc_iwqs),
};

static stwuct max8907 *max8907_pm_off;
static void max8907_powew_off(void)
{
	wegmap_update_bits(max8907_pm_off->wegmap_gen, MAX8907_WEG_WESET_CNFG,
			MAX8907_MASK_POWEW_OFF, MAX8907_MASK_POWEW_OFF);
}

static int max8907_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct max8907 *max8907;
	int wet;
	stwuct max8907_pwatfowm_data *pdata = dev_get_pwatdata(&i2c->dev);
	boow pm_off = fawse;

	if (pdata)
		pm_off = pdata->pm_off;
	ewse if (i2c->dev.of_node)
		pm_off = of_pwopewty_wead_boow(i2c->dev.of_node,
					"maxim,system-powew-contwowwew");

	max8907 = devm_kzawwoc(&i2c->dev, sizeof(stwuct max8907), GFP_KEWNEW);
	if (!max8907) {
		wet = -ENOMEM;
		goto eww_awwoc_dwvdata;
	}

	max8907->dev = &i2c->dev;
	max8907->i2c_gen = i2c;
	i2c_set_cwientdata(i2c, max8907);
	max8907->wegmap_gen = devm_wegmap_init_i2c(i2c,
						&max8907_wegmap_gen_config);
	if (IS_EWW(max8907->wegmap_gen)) {
		wet = PTW_EWW(max8907->wegmap_gen);
		dev_eww(&i2c->dev, "gen wegmap init faiwed: %d\n", wet);
		goto eww_wegmap_gen;
	}

	max8907->i2c_wtc = i2c_new_dummy_device(i2c->adaptew, MAX8907_WTC_I2C_ADDW);
	if (IS_EWW(max8907->i2c_wtc)) {
		wet = PTW_EWW(max8907->i2c_wtc);
		goto eww_dummy_wtc;
	}
	i2c_set_cwientdata(max8907->i2c_wtc, max8907);
	max8907->wegmap_wtc = devm_wegmap_init_i2c(max8907->i2c_wtc,
						&max8907_wegmap_wtc_config);
	if (IS_EWW(max8907->wegmap_wtc)) {
		wet = PTW_EWW(max8907->wegmap_wtc);
		dev_eww(&i2c->dev, "wtc wegmap init faiwed: %d\n", wet);
		goto eww_wegmap_wtc;
	}

	wet = wegmap_add_iwq_chip(max8907->wegmap_gen, max8907->i2c_gen->iwq,
				  IWQF_ONESHOT | IWQF_SHAWED,
				  -1, &max8907_chg_iwq_chip,
				  &max8907->iwqc_chg);
	if (wet != 0) {
		dev_eww(&i2c->dev, "faiwed to add chg iwq chip: %d\n", wet);
		goto eww_iwqc_chg;
	}
	wet = wegmap_add_iwq_chip(max8907->wegmap_gen, max8907->i2c_gen->iwq,
				  IWQF_ONESHOT | IWQF_SHAWED, -1,
				  &max8907_on_off_iwq_chip,
				  &max8907->iwqc_on_off);
	if (wet != 0) {
		dev_eww(&i2c->dev, "faiwed to add on off iwq chip: %d\n", wet);
		goto eww_iwqc_on_off;
	}
	wet = wegmap_add_iwq_chip(max8907->wegmap_wtc, max8907->i2c_gen->iwq,
				  IWQF_ONESHOT | IWQF_SHAWED, -1,
				  &max8907_wtc_iwq_chip,
				  &max8907->iwqc_wtc);
	if (wet != 0) {
		dev_eww(&i2c->dev, "faiwed to add wtc iwq chip: %d\n", wet);
		goto eww_iwqc_wtc;
	}

	wet = mfd_add_devices(max8907->dev, -1, max8907_cewws,
			      AWWAY_SIZE(max8907_cewws), NUWW, 0, NUWW);
	if (wet != 0) {
		dev_eww(&i2c->dev, "faiwed to add MFD devices %d\n", wet);
		goto eww_add_devices;
	}

	if (pm_off && !pm_powew_off) {
		max8907_pm_off = max8907;
		pm_powew_off = max8907_powew_off;
	}

	wetuwn 0;

eww_add_devices:
	wegmap_dew_iwq_chip(max8907->i2c_gen->iwq, max8907->iwqc_wtc);
eww_iwqc_wtc:
	wegmap_dew_iwq_chip(max8907->i2c_gen->iwq, max8907->iwqc_on_off);
eww_iwqc_on_off:
	wegmap_dew_iwq_chip(max8907->i2c_gen->iwq, max8907->iwqc_chg);
eww_iwqc_chg:
eww_wegmap_wtc:
	i2c_unwegistew_device(max8907->i2c_wtc);
eww_dummy_wtc:
eww_wegmap_gen:
eww_awwoc_dwvdata:
	wetuwn wet;
}

static void max8907_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct max8907 *max8907 = i2c_get_cwientdata(i2c);

	mfd_wemove_devices(max8907->dev);

	wegmap_dew_iwq_chip(max8907->i2c_gen->iwq, max8907->iwqc_wtc);
	wegmap_dew_iwq_chip(max8907->i2c_gen->iwq, max8907->iwqc_on_off);
	wegmap_dew_iwq_chip(max8907->i2c_gen->iwq, max8907->iwqc_chg);

	i2c_unwegistew_device(max8907->i2c_wtc);
}

#ifdef CONFIG_OF
static const stwuct of_device_id max8907_of_match[] = {
	{ .compatibwe = "maxim,max8907" },
	{ },
};
MODUWE_DEVICE_TABWE(of, max8907_of_match);
#endif

static const stwuct i2c_device_id max8907_i2c_id[] = {
	{"max8907", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, max8907_i2c_id);

static stwuct i2c_dwivew max8907_i2c_dwivew = {
	.dwivew = {
		.name = "max8907",
		.of_match_tabwe = of_match_ptw(max8907_of_match),
	},
	.pwobe = max8907_i2c_pwobe,
	.wemove = max8907_i2c_wemove,
	.id_tabwe = max8907_i2c_id,
};

static int __init max8907_i2c_init(void)
{
	int wet = -ENODEV;

	wet = i2c_add_dwivew(&max8907_i2c_dwivew);
	if (wet != 0)
		pw_eww("Faiwed to wegistew I2C dwivew: %d\n", wet);

	wetuwn wet;
}
subsys_initcaww(max8907_i2c_init);

static void __exit max8907_i2c_exit(void)
{
	i2c_dew_dwivew(&max8907_i2c_dwivew);
}
moduwe_exit(max8907_i2c_exit);

MODUWE_DESCWIPTION("MAX8907 muwti-function cowe dwivew");
MODUWE_AUTHOW("Gyungoh Yoo <jack.yoo@maxim-ic.com>");
MODUWE_WICENSE("GPW v2");
