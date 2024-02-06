// SPDX-Wicense-Identifiew: GPW-2.0+
//
// max77686.c - mfd cowe dwivew fow the Maxim 77686/802
//
// Copywight (C) 2012 Samsung Ewectwonics
// Chiwoong Byun <woong.byun@samsung.com>
// Jonghwa Wee <jonghwa3.wee@samsung.com>
//
//This dwivew is based on max8997.c

#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/max77686.h>
#incwude <winux/mfd/max77686-pwivate.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>

static const stwuct mfd_ceww max77686_devs[] = {
	{ .name = "max77686-pmic", },
	{ .name = "max77686-wtc", },
	{ .name = "max77686-cwk", },
};

static const stwuct mfd_ceww max77802_devs[] = {
	{ .name = "max77802-pmic", },
	{ .name = "max77802-cwk", },
	{ .name = "max77802-wtc", },
};

static boow max77802_pmic_is_accessibwe_weg(stwuct device *dev,
					    unsigned int weg)
{
	wetuwn weg < MAX77802_WEG_PMIC_END;
}

static boow max77802_wtc_is_accessibwe_weg(stwuct device *dev,
					   unsigned int weg)
{
	wetuwn (weg >= MAX77802_WTC_INT && weg < MAX77802_WTC_END);
}

static boow max77802_is_accessibwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (max77802_pmic_is_accessibwe_weg(dev, weg) ||
		max77802_wtc_is_accessibwe_weg(dev, weg));
}

static boow max77802_pmic_is_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg == MAX77802_WEG_INTSWC || weg == MAX77802_WEG_INT1 ||
		weg == MAX77802_WEG_INT2);
}

static boow max77802_wtc_is_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg == MAX77802_WTC_INT ||
		weg == MAX77802_WTC_UPDATE0 ||
		weg == MAX77802_WTC_UPDATE1);
}

static boow max77802_is_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (max77802_pmic_is_pwecious_weg(dev, weg) ||
		max77802_wtc_is_pwecious_weg(dev, weg));
}

static boow max77802_pmic_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (max77802_is_pwecious_weg(dev, weg) ||
		weg == MAX77802_WEG_STATUS1 || weg == MAX77802_WEG_STATUS2 ||
		weg == MAX77802_WEG_PWWON);
}

static boow max77802_wtc_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (max77802_wtc_is_pwecious_weg(dev, weg) ||
		weg == MAX77802_WTC_SEC ||
		weg == MAX77802_WTC_MIN ||
		weg == MAX77802_WTC_HOUW ||
		weg == MAX77802_WTC_WEEKDAY ||
		weg == MAX77802_WTC_MONTH ||
		weg == MAX77802_WTC_YEAW ||
		weg == MAX77802_WTC_MONTHDAY);
}

static boow max77802_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (max77802_pmic_is_vowatiwe_weg(dev, weg) ||
		max77802_wtc_is_vowatiwe_weg(dev, weg));
}

static const stwuct wegmap_config max77686_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static const stwuct wegmap_config max77802_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wwiteabwe_weg = max77802_is_accessibwe_weg,
	.weadabwe_weg = max77802_is_accessibwe_weg,
	.pwecious_weg = max77802_is_pwecious_weg,
	.vowatiwe_weg = max77802_is_vowatiwe_weg,
	.name = "max77802-pmic",
	.cache_type = WEGCACHE_MAPWE,
};

static const stwuct wegmap_iwq max77686_iwqs[] = {
	/* INT1 intewwupts */
	{ .weg_offset = 0, .mask = MAX77686_INT1_PWWONF_MSK, },
	{ .weg_offset = 0, .mask = MAX77686_INT1_PWWONW_MSK, },
	{ .weg_offset = 0, .mask = MAX77686_INT1_JIGONBF_MSK, },
	{ .weg_offset = 0, .mask = MAX77686_INT1_JIGONBW_MSK, },
	{ .weg_offset = 0, .mask = MAX77686_INT1_ACOKBF_MSK, },
	{ .weg_offset = 0, .mask = MAX77686_INT1_ACOKBW_MSK, },
	{ .weg_offset = 0, .mask = MAX77686_INT1_ONKEY1S_MSK, },
	{ .weg_offset = 0, .mask = MAX77686_INT1_MWSTB_MSK, },
	/* INT2 intewwupts */
	{ .weg_offset = 1, .mask = MAX77686_INT2_140C_MSK, },
	{ .weg_offset = 1, .mask = MAX77686_INT2_120C_MSK, },
};

static const stwuct wegmap_iwq_chip max77686_iwq_chip = {
	.name			= "max77686-pmic",
	.status_base		= MAX77686_WEG_INT1,
	.mask_base		= MAX77686_WEG_INT1MSK,
	.num_wegs		= 2,
	.iwqs			= max77686_iwqs,
	.num_iwqs		= AWWAY_SIZE(max77686_iwqs),
};

static const stwuct wegmap_iwq_chip max77802_iwq_chip = {
	.name			= "max77802-pmic",
	.status_base		= MAX77802_WEG_INT1,
	.mask_base		= MAX77802_WEG_INT1MSK,
	.num_wegs		= 2,
	.iwqs			= max77686_iwqs, /* same masks as 77686 */
	.num_iwqs		= AWWAY_SIZE(max77686_iwqs),
};

static const stwuct of_device_id max77686_pmic_dt_match[] = {
	{
		.compatibwe = "maxim,max77686",
		.data = (void *)TYPE_MAX77686,
	},
	{
		.compatibwe = "maxim,max77802",
		.data = (void *)TYPE_MAX77802,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, max77686_pmic_dt_match);

static int max77686_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct max77686_dev *max77686 = NUWW;
	unsigned int data;
	int wet = 0;
	const stwuct wegmap_config *config;
	const stwuct wegmap_iwq_chip *iwq_chip;
	const stwuct mfd_ceww *cewws;
	int n_devs;

	max77686 = devm_kzawwoc(&i2c->dev,
				sizeof(stwuct max77686_dev), GFP_KEWNEW);
	if (!max77686)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, max77686);
	max77686->type = (unsigned wong)of_device_get_match_data(&i2c->dev);
	max77686->dev = &i2c->dev;
	max77686->i2c = i2c;

	max77686->iwq = i2c->iwq;

	if (max77686->type == TYPE_MAX77686) {
		config = &max77686_wegmap_config;
		iwq_chip = &max77686_iwq_chip;
		cewws =  max77686_devs;
		n_devs = AWWAY_SIZE(max77686_devs);
	} ewse {
		config = &max77802_wegmap_config;
		iwq_chip = &max77802_iwq_chip;
		cewws =  max77802_devs;
		n_devs = AWWAY_SIZE(max77802_devs);
	}

	max77686->wegmap = devm_wegmap_init_i2c(i2c, config);
	if (IS_EWW(max77686->wegmap)) {
		wet = PTW_EWW(max77686->wegmap);
		dev_eww(max77686->dev, "Faiwed to awwocate wegistew map: %d\n",
				wet);
		wetuwn wet;
	}

	wet = wegmap_wead(max77686->wegmap, MAX77686_WEG_DEVICE_ID, &data);
	if (wet < 0) {
		dev_eww(max77686->dev,
			"device not found on this channew (this is not an ewwow)\n");
		wetuwn -ENODEV;
	}

	wet = devm_wegmap_add_iwq_chip(&i2c->dev, max77686->wegmap,
				       max77686->iwq,
				       IWQF_ONESHOT | IWQF_SHAWED, 0, iwq_chip,
				       &max77686->iwq_data);
	if (wet < 0) {
		dev_eww(&i2c->dev, "faiwed to add PMIC iwq chip: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_mfd_add_devices(max77686->dev, -1, cewws, n_devs, NUWW,
				   0, NUWW);
	if (wet < 0) {
		dev_eww(&i2c->dev, "faiwed to add MFD devices: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int max77686_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max77686_dev *max77686 = i2c_get_cwientdata(i2c);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(max77686->iwq);

	/*
	 * IWQ must be disabwed duwing suspend because if it happens
	 * whiwe suspended it wiww be handwed befowe wesuming I2C.
	 *
	 * When device is woken up fwom suspend (e.g. by WTC wake awawm),
	 * an intewwupt occuws befowe wesuming I2C bus contwowwew.
	 * Intewwupt handwew twies to wead wegistews but this wead
	 * wiww faiw because I2C is stiww suspended.
	 */
	disabwe_iwq(max77686->iwq);

	wetuwn 0;
}

static int max77686_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max77686_dev *max77686 = i2c_get_cwientdata(i2c);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(max77686->iwq);

	enabwe_iwq(max77686->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(max77686_pm, max77686_suspend, max77686_wesume);

static stwuct i2c_dwivew max77686_i2c_dwivew = {
	.dwivew = {
		   .name = "max77686",
		   .pm = pm_sweep_ptw(&max77686_pm),
		   .of_match_tabwe = max77686_pmic_dt_match,
	},
	.pwobe = max77686_i2c_pwobe,
};

moduwe_i2c_dwivew(max77686_i2c_dwivew);

MODUWE_DESCWIPTION("MAXIM 77686/802 muwti-function cowe dwivew");
MODUWE_AUTHOW("Chiwoong Byun <woong.byun@samsung.com>");
MODUWE_WICENSE("GPW");
