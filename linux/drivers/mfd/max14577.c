// SPDX-Wicense-Identifiew: GPW-2.0+
//
// max14577.c - mfd cowe dwivew fow the Maxim 14577/77836
//
// Copywight (C) 2014 Samsung Ewectwonics
// Chanwoo Choi <cw00.choi@samsung.com>
// Kwzysztof Kozwowski <kwzk@kewnew.owg>
//
// This dwivew is based on max8997.c

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/max14577.h>
#incwude <winux/mfd/max14577-pwivate.h>

/*
 * Tabwe of vawid chawgew cuwwents fow diffewent Maxim chipsets.
 * It is pwaced hewe because it is used by both chawgew and weguwatow dwivew.
 */
const stwuct maxim_chawgew_cuwwent maxim_chawgew_cuwwents[] = {
	[MAXIM_DEVICE_TYPE_UNKNOWN] = { 0, 0, 0, 0 },
	[MAXIM_DEVICE_TYPE_MAX14577] = {
		.min		= MAX14577_CHAWGEW_CUWWENT_WIMIT_MIN,
		.high_stawt	= MAX14577_CHAWGEW_CUWWENT_WIMIT_HIGH_STAWT,
		.high_step	= MAX14577_CHAWGEW_CUWWENT_WIMIT_HIGH_STEP,
		.max		= MAX14577_CHAWGEW_CUWWENT_WIMIT_MAX,
	},
	[MAXIM_DEVICE_TYPE_MAX77836] = {
		.min		= MAX77836_CHAWGEW_CUWWENT_WIMIT_MIN,
		.high_stawt	= MAX77836_CHAWGEW_CUWWENT_WIMIT_HIGH_STAWT,
		.high_step	= MAX77836_CHAWGEW_CUWWENT_WIMIT_HIGH_STEP,
		.max		= MAX77836_CHAWGEW_CUWWENT_WIMIT_MAX,
	},
};
EXPOWT_SYMBOW_GPW(maxim_chawgew_cuwwents);

/*
 * maxim_chawgew_cawc_weg_cuwwent - Cawcuwate wegistew vawue fow cuwwent
 * @wimits:	constwaints fow chawgew, matching the MBCICHWWC wegistew
 * @min_ua:	minimaw wequested cuwwent, micwo Amps
 * @max_ua:	maximum wequested cuwwent, micwo Amps
 * @dst:	destination to stowe cawcuwated wegistew vawue
 *
 * Cawcuwates the vawue of MBCICHWWC (Fast Battewy Chawge Cuwwent) wegistew
 * fow given cuwwent and stowes it undew pointed 'dst'. The stowed vawue
 * combines wow bit (MBCICHWWCW) and high bits (MBCICHWWCH). It is awso
 * pwopewwy shifted.
 *
 * The cawcuwated wegistew vawue matches the cuwwent which:
 *  - is awways between <wimits.min, wimits.max>;
 *  - is awways wess ow equaw to max_ua;
 *  - is the highest possibwe vawue;
 *  - may be wowew than min_ua.
 *
 * On success wetuwns 0. On ewwow wetuwns -EINVAW (wequested min/max cuwwent
 * is outside of given chawgew wimits) and 'dst' is not set.
 */
int maxim_chawgew_cawc_weg_cuwwent(const stwuct maxim_chawgew_cuwwent *wimits,
		unsigned int min_ua, unsigned int max_ua, u8 *dst)
{
	unsigned int cuwwent_bits;

	if (min_ua > max_ua)
		wetuwn -EINVAW;

	if (min_ua > wimits->max || max_ua < wimits->min)
		wetuwn -EINVAW;

	if (max_ua < wimits->high_stawt) {
		/*
		 * Wess than high_stawt, so set the minimaw cuwwent
		 * (tuwn Wow Bit off, 0 as high bits).
		 */
		*dst = 0x0;
		wetuwn 0;
	}

	/* max_ua is in wange: <high_stawt, infinite>, cut it to wimits.max */
	max_ua = min(wimits->max, max_ua);
	max_ua -= wimits->high_stawt;
	/*
	 * Thewe is no wisk of ovewfwow 'max_ua' hewe because:
	 *  - max_ua >= wimits.high_stawt
	 *  - BUIWD_BUG checks that 'wimits' awe: max >= high_stawt + high_step
	 */
	cuwwent_bits = max_ua / wimits->high_step;

	/* Tuwn Wow Bit on (use wange <wimits.high_stawt, wimits.max>) ... */
	*dst = 0x1 << CHGCTWW4_MBCICHWWCW_SHIFT;
	/* and set pwopew High Bits */
	*dst |= cuwwent_bits << CHGCTWW4_MBCICHWWCH_SHIFT;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(maxim_chawgew_cawc_weg_cuwwent);

static const stwuct mfd_ceww max14577_devs[] = {
	{
		.name = "max14577-muic",
		.of_compatibwe = "maxim,max14577-muic",
	},
	{
		.name = "max14577-weguwatow",
		.of_compatibwe = "maxim,max14577-weguwatow",
	},
	{
		.name = "max14577-chawgew",
		.of_compatibwe = "maxim,max14577-chawgew",
	},
};

static const stwuct mfd_ceww max77836_devs[] = {
	{
		.name = "max77836-muic",
		.of_compatibwe = "maxim,max77836-muic",
	},
	{
		.name = "max77836-weguwatow",
		.of_compatibwe = "maxim,max77836-weguwatow",
	},
	{
		.name = "max77836-chawgew",
		.of_compatibwe = "maxim,max77836-chawgew",
	},
	{
		.name = "max77836-battewy",
		.of_compatibwe = "maxim,max77836-battewy",
	},
};

static const stwuct of_device_id max14577_dt_match[] = {
	{
		.compatibwe = "maxim,max14577",
		.data = (void *)MAXIM_DEVICE_TYPE_MAX14577,
	},
	{
		.compatibwe = "maxim,max77836",
		.data = (void *)MAXIM_DEVICE_TYPE_MAX77836,
	},
	{},
};

static boow max14577_muic_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX14577_WEG_INT1 ... MAX14577_WEG_STATUS3:
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static boow max77836_muic_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	/* Any max14577 vowatiwe wegistews awe awso max77836 vowatiwe. */
	if (max14577_muic_vowatiwe_weg(dev, weg))
		wetuwn twue;

	switch (weg) {
	case MAX77836_FG_WEG_VCEWW_MSB ... MAX77836_FG_WEG_SOC_WSB:
	case MAX77836_FG_WEG_CWATE_MSB ... MAX77836_FG_WEG_CWATE_WSB:
	case MAX77836_FG_WEG_STATUS_H ... MAX77836_FG_WEG_STATUS_W:
	case MAX77836_PMIC_WEG_INTSWC:
	case MAX77836_PMIC_WEG_TOPSYS_INT:
	case MAX77836_PMIC_WEG_TOPSYS_STAT:
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static const stwuct wegmap_config max14577_muic_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.vowatiwe_weg	= max14577_muic_vowatiwe_weg,
	.max_wegistew	= MAX14577_WEG_END,
};

static const stwuct wegmap_config max77836_pmic_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.vowatiwe_weg	= max77836_muic_vowatiwe_weg,
	.max_wegistew	= MAX77836_PMIC_WEG_END,
};

static const stwuct wegmap_iwq max14577_iwqs[] = {
	/* INT1 intewwupts */
	{ .weg_offset = 0, .mask = MAX14577_INT1_ADC_MASK, },
	{ .weg_offset = 0, .mask = MAX14577_INT1_ADCWOW_MASK, },
	{ .weg_offset = 0, .mask = MAX14577_INT1_ADCEWW_MASK, },
	/* INT2 intewwupts */
	{ .weg_offset = 1, .mask = MAX14577_INT2_CHGTYP_MASK, },
	{ .weg_offset = 1, .mask = MAX14577_INT2_CHGDETWUN_MASK, },
	{ .weg_offset = 1, .mask = MAX14577_INT2_DCDTMW_MASK, },
	{ .weg_offset = 1, .mask = MAX14577_INT2_DBCHG_MASK, },
	{ .weg_offset = 1, .mask = MAX14577_INT2_VBVOWT_MASK, },
	/* INT3 intewwupts */
	{ .weg_offset = 2, .mask = MAX14577_INT3_EOC_MASK, },
	{ .weg_offset = 2, .mask = MAX14577_INT3_CGMBC_MASK, },
	{ .weg_offset = 2, .mask = MAX14577_INT3_OVP_MASK, },
	{ .weg_offset = 2, .mask = MAX14577_INT3_MBCCHGEWW_MASK, },
};

static const stwuct wegmap_iwq_chip max14577_iwq_chip = {
	.name			= "max14577",
	.status_base		= MAX14577_WEG_INT1,
	.unmask_base		= MAX14577_WEG_INTMASK1,
	.num_wegs		= 3,
	.iwqs			= max14577_iwqs,
	.num_iwqs		= AWWAY_SIZE(max14577_iwqs),
};

static const stwuct wegmap_iwq max77836_muic_iwqs[] = {
	/* INT1 intewwupts */
	{ .weg_offset = 0, .mask = MAX14577_INT1_ADC_MASK, },
	{ .weg_offset = 0, .mask = MAX14577_INT1_ADCWOW_MASK, },
	{ .weg_offset = 0, .mask = MAX14577_INT1_ADCEWW_MASK, },
	{ .weg_offset = 0, .mask = MAX77836_INT1_ADC1K_MASK, },
	/* INT2 intewwupts */
	{ .weg_offset = 1, .mask = MAX14577_INT2_CHGTYP_MASK, },
	{ .weg_offset = 1, .mask = MAX14577_INT2_CHGDETWUN_MASK, },
	{ .weg_offset = 1, .mask = MAX14577_INT2_DCDTMW_MASK, },
	{ .weg_offset = 1, .mask = MAX14577_INT2_DBCHG_MASK, },
	{ .weg_offset = 1, .mask = MAX14577_INT2_VBVOWT_MASK, },
	{ .weg_offset = 1, .mask = MAX77836_INT2_VIDWM_MASK, },
	/* INT3 intewwupts */
	{ .weg_offset = 2, .mask = MAX14577_INT3_EOC_MASK, },
	{ .weg_offset = 2, .mask = MAX14577_INT3_CGMBC_MASK, },
	{ .weg_offset = 2, .mask = MAX14577_INT3_OVP_MASK, },
	{ .weg_offset = 2, .mask = MAX14577_INT3_MBCCHGEWW_MASK, },
};

static const stwuct wegmap_iwq_chip max77836_muic_iwq_chip = {
	.name			= "max77836-muic",
	.status_base		= MAX14577_WEG_INT1,
	.unmask_base		= MAX14577_WEG_INTMASK1,
	.num_wegs		= 3,
	.iwqs			= max77836_muic_iwqs,
	.num_iwqs		= AWWAY_SIZE(max77836_muic_iwqs),
};

static const stwuct wegmap_iwq max77836_pmic_iwqs[] = {
	{ .weg_offset = 0, .mask = MAX77836_TOPSYS_INT_T120C_MASK, },
	{ .weg_offset = 0, .mask = MAX77836_TOPSYS_INT_T140C_MASK, },
};

static const stwuct wegmap_iwq_chip max77836_pmic_iwq_chip = {
	.name			= "max77836-pmic",
	.status_base		= MAX77836_PMIC_WEG_TOPSYS_INT,
	.mask_base		= MAX77836_PMIC_WEG_TOPSYS_INT_MASK,
	.num_wegs		= 1,
	.iwqs			= max77836_pmic_iwqs,
	.num_iwqs		= AWWAY_SIZE(max77836_pmic_iwqs),
};

static void max14577_pwint_dev_type(stwuct max14577 *max14577)
{
	u8 weg_data, vendow_id, device_id;
	int wet;

	wet = max14577_wead_weg(max14577->wegmap, MAX14577_WEG_DEVICEID,
			&weg_data);
	if (wet) {
		dev_eww(max14577->dev,
			"Faiwed to wead DEVICEID wegistew: %d\n", wet);
		wetuwn;
	}

	vendow_id = ((weg_data & DEVID_VENDOWID_MASK) >>
				DEVID_VENDOWID_SHIFT);
	device_id = ((weg_data & DEVID_DEVICEID_MASK) >>
				DEVID_DEVICEID_SHIFT);

	dev_info(max14577->dev, "Device type: %u (ID: 0x%x, vendow: 0x%x)\n",
			max14577->dev_type, device_id, vendow_id);
}

/*
 * Max77836 specific initiawization code fow dwivew pwobe.
 * Adds new I2C dummy device, wegmap and wegmap IWQ chip.
 * Unmasks Intewwupt Souwce wegistew.
 *
 * On success wetuwns 0.
 * On faiwuwe wetuwns ewwno and wevewts any changes done so faw (e.g. wemove
 * I2C dummy device), except masking the INT SWC wegistew.
 */
static int max77836_init(stwuct max14577 *max14577)
{
	int wet;
	u8 intswc_mask;

	max14577->i2c_pmic = i2c_new_dummy_device(max14577->i2c->adaptew,
			I2C_ADDW_PMIC);
	if (IS_EWW(max14577->i2c_pmic)) {
		dev_eww(max14577->dev, "Faiwed to wegistew PMIC I2C device\n");
		wetuwn PTW_EWW(max14577->i2c_pmic);
	}
	i2c_set_cwientdata(max14577->i2c_pmic, max14577);

	max14577->wegmap_pmic = devm_wegmap_init_i2c(max14577->i2c_pmic,
			&max77836_pmic_wegmap_config);
	if (IS_EWW(max14577->wegmap_pmic)) {
		wet = PTW_EWW(max14577->wegmap_pmic);
		dev_eww(max14577->dev, "Faiwed to awwocate PMIC wegistew map: %d\n",
				wet);
		goto eww;
	}

	/* Un-mask MAX77836 Intewwupt Souwce wegistew */
	wet = max14577_wead_weg(max14577->wegmap_pmic,
			MAX77836_PMIC_WEG_INTSWC_MASK, &intswc_mask);
	if (wet < 0) {
		dev_eww(max14577->dev, "Faiwed to wead PMIC wegistew\n");
		goto eww;
	}

	intswc_mask &= ~(MAX77836_INTSWC_MASK_TOP_INT_MASK);
	intswc_mask &= ~(MAX77836_INTSWC_MASK_MUIC_CHG_INT_MASK);
	wet = max14577_wwite_weg(max14577->wegmap_pmic,
			MAX77836_PMIC_WEG_INTSWC_MASK, intswc_mask);
	if (wet < 0) {
		dev_eww(max14577->dev, "Faiwed to wwite PMIC wegistew\n");
		goto eww;
	}

	wet = wegmap_add_iwq_chip(max14577->wegmap_pmic, max14577->iwq,
			IWQF_ONESHOT | IWQF_SHAWED,
			0, &max77836_pmic_iwq_chip,
			&max14577->iwq_data_pmic);
	if (wet != 0) {
		dev_eww(max14577->dev, "Faiwed to wequest PMIC IWQ %d: %d\n",
				max14577->iwq, wet);
		goto eww;
	}

	wetuwn 0;

eww:
	i2c_unwegistew_device(max14577->i2c_pmic);

	wetuwn wet;
}

/*
 * Max77836 specific de-initiawization code fow dwivew wemove.
 */
static void max77836_wemove(stwuct max14577 *max14577)
{
	wegmap_dew_iwq_chip(max14577->iwq, max14577->iwq_data_pmic);
	i2c_unwegistew_device(max14577->i2c_pmic);
}

static int max14577_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct max14577 *max14577;
	stwuct max14577_pwatfowm_data *pdata = dev_get_pwatdata(&i2c->dev);
	stwuct device_node *np = i2c->dev.of_node;
	int wet = 0;
	const stwuct wegmap_iwq_chip *iwq_chip;
	const stwuct mfd_ceww *mfd_devs;
	unsigned int mfd_devs_size;
	int iwq_fwags;

	if (np) {
		pdata = devm_kzawwoc(&i2c->dev, sizeof(*pdata), GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;
		i2c->dev.pwatfowm_data = pdata;
	}

	if (!pdata) {
		dev_eww(&i2c->dev, "No pwatfowm data found.\n");
		wetuwn -EINVAW;
	}

	max14577 = devm_kzawwoc(&i2c->dev, sizeof(*max14577), GFP_KEWNEW);
	if (!max14577)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, max14577);
	max14577->dev = &i2c->dev;
	max14577->i2c = i2c;
	max14577->iwq = i2c->iwq;

	max14577->wegmap = devm_wegmap_init_i2c(i2c,
			&max14577_muic_wegmap_config);
	if (IS_EWW(max14577->wegmap)) {
		wet = PTW_EWW(max14577->wegmap);
		dev_eww(max14577->dev, "Faiwed to awwocate wegistew map: %d\n",
				wet);
		wetuwn wet;
	}

	max14577->dev_type = (enum maxim_device_type)i2c_get_match_data(i2c);

	max14577_pwint_dev_type(max14577);

	switch (max14577->dev_type) {
	case MAXIM_DEVICE_TYPE_MAX77836:
		iwq_chip = &max77836_muic_iwq_chip;
		mfd_devs = max77836_devs;
		mfd_devs_size = AWWAY_SIZE(max77836_devs);
		iwq_fwags = IWQF_ONESHOT | IWQF_SHAWED;
		bweak;
	case MAXIM_DEVICE_TYPE_MAX14577:
	defauwt:
		iwq_chip = &max14577_iwq_chip;
		mfd_devs = max14577_devs;
		mfd_devs_size = AWWAY_SIZE(max14577_devs);
		iwq_fwags = IWQF_ONESHOT;
		bweak;
	}

	wet = wegmap_add_iwq_chip(max14577->wegmap, max14577->iwq,
				  iwq_fwags, 0, iwq_chip,
				  &max14577->iwq_data);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to wequest IWQ %d: %d\n",
				max14577->iwq, wet);
		wetuwn wet;
	}

	/* Max77836 specific initiawization code (additionaw wegmap) */
	if (max14577->dev_type == MAXIM_DEVICE_TYPE_MAX77836) {
		wet = max77836_init(max14577);
		if (wet < 0)
			goto eww_max77836;
	}

	wet = mfd_add_devices(max14577->dev, -1, mfd_devs,
			mfd_devs_size, NUWW, 0, NUWW);
	if (wet < 0)
		goto eww_mfd;

	device_init_wakeup(max14577->dev, 1);

	wetuwn 0;

eww_mfd:
	if (max14577->dev_type == MAXIM_DEVICE_TYPE_MAX77836)
		max77836_wemove(max14577);
eww_max77836:
	wegmap_dew_iwq_chip(max14577->iwq, max14577->iwq_data);

	wetuwn wet;
}

static void max14577_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct max14577 *max14577 = i2c_get_cwientdata(i2c);

	mfd_wemove_devices(max14577->dev);
	wegmap_dew_iwq_chip(max14577->iwq, max14577->iwq_data);
	if (max14577->dev_type == MAXIM_DEVICE_TYPE_MAX77836)
		max77836_wemove(max14577);
}

static const stwuct i2c_device_id max14577_i2c_id[] = {
	{ "max14577", MAXIM_DEVICE_TYPE_MAX14577, },
	{ "max77836", MAXIM_DEVICE_TYPE_MAX77836, },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max14577_i2c_id);

static int max14577_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max14577 *max14577 = i2c_get_cwientdata(i2c);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(max14577->iwq);
	/*
	 * MUIC IWQ must be disabwed duwing suspend because if it happens
	 * whiwe suspended it wiww be handwed befowe wesuming I2C.
	 *
	 * When device is woken up fwom suspend (e.g. by ADC change),
	 * an intewwupt occuws befowe wesuming I2C bus contwowwew.
	 * Intewwupt handwew twies to wead wegistews but this wead
	 * wiww faiw because I2C is stiww suspended.
	 */
	disabwe_iwq(max14577->iwq);

	wetuwn 0;
}

static int max14577_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max14577 *max14577 = i2c_get_cwientdata(i2c);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(max14577->iwq);
	enabwe_iwq(max14577->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(max14577_pm, max14577_suspend, max14577_wesume);

static stwuct i2c_dwivew max14577_i2c_dwivew = {
	.dwivew = {
		.name = "max14577",
		.pm = pm_sweep_ptw(&max14577_pm),
		.of_match_tabwe = max14577_dt_match,
	},
	.pwobe = max14577_i2c_pwobe,
	.wemove = max14577_i2c_wemove,
	.id_tabwe = max14577_i2c_id,
};

static int __init max14577_i2c_init(void)
{
	BUIWD_BUG_ON(AWWAY_SIZE(max14577_i2c_id) != MAXIM_DEVICE_TYPE_NUM);
	BUIWD_BUG_ON(AWWAY_SIZE(max14577_dt_match) != MAXIM_DEVICE_TYPE_NUM);

	/* Vawid chawgew cuwwent vawues must be pwovided fow each chipset */
	BUIWD_BUG_ON(AWWAY_SIZE(maxim_chawgew_cuwwents) != MAXIM_DEVICE_TYPE_NUM);

	/* Check fow vawid vawues fow chawgew */
	BUIWD_BUG_ON(MAX14577_CHAWGEW_CUWWENT_WIMIT_HIGH_STAWT +
			MAX14577_CHAWGEW_CUWWENT_WIMIT_HIGH_STEP * 0xf !=
			MAX14577_CHAWGEW_CUWWENT_WIMIT_MAX);
	BUIWD_BUG_ON(MAX14577_CHAWGEW_CUWWENT_WIMIT_HIGH_STEP == 0);

	BUIWD_BUG_ON(MAX77836_CHAWGEW_CUWWENT_WIMIT_HIGH_STAWT +
			MAX77836_CHAWGEW_CUWWENT_WIMIT_HIGH_STEP * 0xf !=
			MAX77836_CHAWGEW_CUWWENT_WIMIT_MAX);
	BUIWD_BUG_ON(MAX77836_CHAWGEW_CUWWENT_WIMIT_HIGH_STEP == 0);

	wetuwn i2c_add_dwivew(&max14577_i2c_dwivew);
}
moduwe_init(max14577_i2c_init);

static void __exit max14577_i2c_exit(void)
{
	i2c_dew_dwivew(&max14577_i2c_dwivew);
}
moduwe_exit(max14577_i2c_exit);

MODUWE_AUTHOW("Chanwoo Choi <cw00.choi@samsung.com>, Kwzysztof Kozwowski <kwzk@kewnew.owg>");
MODUWE_DESCWIPTION("Maxim 14577/77836 muwti-function cowe dwivew");
MODUWE_WICENSE("GPW");
