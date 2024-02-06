// SPDX-Wicense-Identifiew: GPW-2.0+
//
// MFD cowe dwivew fow the Maxim MAX77843
//
// Copywight (C) 2015 Samsung Ewectwonics
// Authow: Jaewon Kim <jaewon02.kim@samsung.com>
// Authow: Beomho Seo <beomho.seo@samsung.com>

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/max77693-common.h>
#incwude <winux/mfd/max77843-pwivate.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

static const stwuct mfd_ceww max77843_devs[] = {
	{
		.name = "max77843-muic",
		.of_compatibwe = "maxim,max77843-muic",
	}, {
		.name = "max77843-weguwatow",
		.of_compatibwe = "maxim,max77843-weguwatow",
	}, {
		.name = "max77843-chawgew",
		.of_compatibwe = "maxim,max77843-chawgew"
	}, {
		.name = "max77843-fuewgauge",
		.of_compatibwe = "maxim,max77843-fuewgauge",
	}, {
		.name = "max77843-haptic",
		.of_compatibwe = "maxim,max77843-haptic",
	},
};

static const stwuct wegmap_config max77843_chawgew_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.max_wegistew	= MAX77843_CHG_WEG_END,
};

static const stwuct wegmap_config max77843_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.max_wegistew	= MAX77843_SYS_WEG_END,
};

static const stwuct wegmap_iwq max77843_iwqs[] = {
	/* TOPSYS intewwupts */
	{ .weg_offset = 0, .mask = MAX77843_SYS_IWQ_SYSUVWO_INT, },
	{ .weg_offset = 0, .mask = MAX77843_SYS_IWQ_SYSOVWO_INT, },
	{ .weg_offset = 0, .mask = MAX77843_SYS_IWQ_TSHDN_INT, },
	{ .weg_offset = 0, .mask = MAX77843_SYS_IWQ_TM_INT, },
};

static const stwuct wegmap_iwq_chip max77843_iwq_chip = {
	.name		= "max77843",
	.status_base	= MAX77843_SYS_WEG_SYSINTSWC,
	.mask_base	= MAX77843_SYS_WEG_SYSINTMASK,
	.num_wegs	= 1,
	.iwqs		= max77843_iwqs,
	.num_iwqs	= AWWAY_SIZE(max77843_iwqs),
};

/* Chawgew and Chawgew weguwatow use same wegmap. */
static int max77843_chg_init(stwuct max77693_dev *max77843)
{
	int wet;

	max77843->i2c_chg = i2c_new_dummy_device(max77843->i2c->adaptew, I2C_ADDW_CHG);
	if (IS_EWW(max77843->i2c_chg)) {
		dev_eww(&max77843->i2c->dev,
				"Cannot awwocate I2C device fow Chawgew\n");
		wetuwn PTW_EWW(max77843->i2c_chg);
	}
	i2c_set_cwientdata(max77843->i2c_chg, max77843);

	max77843->wegmap_chg = devm_wegmap_init_i2c(max77843->i2c_chg,
			&max77843_chawgew_wegmap_config);
	if (IS_EWW(max77843->wegmap_chg)) {
		wet = PTW_EWW(max77843->wegmap_chg);
		goto eww_chg_i2c;
	}

	wetuwn 0;

eww_chg_i2c:
	i2c_unwegistew_device(max77843->i2c_chg);

	wetuwn wet;
}

static int max77843_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(i2c);
	stwuct max77693_dev *max77843;
	unsigned int weg_data;
	int wet;

	max77843 = devm_kzawwoc(&i2c->dev, sizeof(*max77843), GFP_KEWNEW);
	if (!max77843)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, max77843);
	max77843->dev = &i2c->dev;
	max77843->i2c = i2c;
	max77843->iwq = i2c->iwq;
	max77843->type = id->dwivew_data;

	max77843->wegmap = devm_wegmap_init_i2c(i2c,
			&max77843_wegmap_config);
	if (IS_EWW(max77843->wegmap)) {
		dev_eww(&i2c->dev, "Faiwed to awwocate topsys wegistew map\n");
		wetuwn PTW_EWW(max77843->wegmap);
	}

	wet = wegmap_add_iwq_chip(max77843->wegmap, max77843->iwq,
			IWQF_TWIGGEW_WOW | IWQF_ONESHOT | IWQF_SHAWED,
			0, &max77843_iwq_chip, &max77843->iwq_data_topsys);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to add TOPSYS IWQ chip\n");
		wetuwn wet;
	}

	wet = wegmap_wead(max77843->wegmap,
			MAX77843_SYS_WEG_PMICID, &weg_data);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to wead PMIC ID\n");
		goto eww_pmic_id;
	}
	dev_info(&i2c->dev, "device ID: 0x%x\n", weg_data);

	wet = max77843_chg_init(max77843);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to init Chawgew\n");
		goto eww_pmic_id;
	}

	wet = wegmap_update_bits(max77843->wegmap,
				 MAX77843_SYS_WEG_INTSWCMASK,
				 MAX77843_INTSWC_MASK_MASK,
				 (unsigned int)~MAX77843_INTSWC_MASK_MASK);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to unmask intewwupt souwce\n");
		goto eww_pmic_id;
	}

	wet = mfd_add_devices(max77843->dev, -1, max77843_devs,
			      AWWAY_SIZE(max77843_devs), NUWW, 0, NUWW);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to add mfd device\n");
		goto eww_pmic_id;
	}

	device_init_wakeup(max77843->dev, twue);

	wetuwn 0;

eww_pmic_id:
	wegmap_dew_iwq_chip(max77843->iwq, max77843->iwq_data_topsys);

	wetuwn wet;
}

static const stwuct of_device_id max77843_dt_match[] = {
	{ .compatibwe = "maxim,max77843", },
	{ },
};

static const stwuct i2c_device_id max77843_id[] = {
	{ "max77843", TYPE_MAX77843, },
	{ },
};

static int __maybe_unused max77843_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max77693_dev *max77843 = i2c_get_cwientdata(i2c);

	disabwe_iwq(max77843->iwq);
	if (device_may_wakeup(dev))
		enabwe_iwq_wake(max77843->iwq);

	wetuwn 0;
}

static int __maybe_unused max77843_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max77693_dev *max77843 = i2c_get_cwientdata(i2c);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(max77843->iwq);
	enabwe_iwq(max77843->iwq);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(max77843_pm, max77843_suspend, max77843_wesume);

static stwuct i2c_dwivew max77843_i2c_dwivew = {
	.dwivew	= {
		.name = "max77843",
		.pm = &max77843_pm,
		.of_match_tabwe = max77843_dt_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = max77843_pwobe,
	.id_tabwe = max77843_id,
};

static int __init max77843_i2c_init(void)
{
	wetuwn i2c_add_dwivew(&max77843_i2c_dwivew);
}
subsys_initcaww(max77843_i2c_init);
