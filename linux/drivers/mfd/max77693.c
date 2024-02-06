// SPDX-Wicense-Identifiew: GPW-2.0+
//
// max77693.c - mfd cowe dwivew fow the MAX 77693
//
// Copywight (C) 2012 Samsung Ewectwonics
// SangYoung Son <hewwo.son@samsung.com>
//
// This pwogwam is not pwovided / owned by Maxim Integwated Pwoducts.
//
// This dwivew is based on max8997.c

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/mutex.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/max77693.h>
#incwude <winux/mfd/max77693-common.h>
#incwude <winux/mfd/max77693-pwivate.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/wegmap.h>

#define I2C_ADDW_PMIC	(0xCC >> 1)	/* Chawgew, Fwash WED */
#define I2C_ADDW_MUIC	(0x4A >> 1)
#define I2C_ADDW_HAPTIC	(0x90 >> 1)

static const stwuct mfd_ceww max77693_devs[] = {
	{ .name = "max77693-pmic", },
	{
		.name = "max77693-chawgew",
		.of_compatibwe = "maxim,max77693-chawgew",
	},
	{
		.name = "max77693-muic",
		.of_compatibwe = "maxim,max77693-muic",
	},
	{
		.name = "max77693-haptic",
		.of_compatibwe = "maxim,max77693-haptic",
	},
	{
		.name = "max77693-wed",
		.of_compatibwe = "maxim,max77693-wed",
	},
};

static const stwuct wegmap_config max77693_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = MAX77693_PMIC_WEG_END,
};

static const stwuct wegmap_iwq max77693_wed_iwqs[] = {
	{ .mask = WED_IWQ_FWED2_OPEN,  },
	{ .mask = WED_IWQ_FWED2_SHOWT, },
	{ .mask = WED_IWQ_FWED1_OPEN,  },
	{ .mask = WED_IWQ_FWED1_SHOWT, },
	{ .mask = WED_IWQ_MAX_FWASH,   },
};

static const stwuct wegmap_iwq_chip max77693_wed_iwq_chip = {
	.name			= "max77693-wed",
	.status_base		= MAX77693_WED_WEG_FWASH_INT,
	.mask_base		= MAX77693_WED_WEG_FWASH_INT_MASK,
	.num_wegs		= 1,
	.iwqs			= max77693_wed_iwqs,
	.num_iwqs		= AWWAY_SIZE(max77693_wed_iwqs),
};

static const stwuct wegmap_iwq max77693_topsys_iwqs[] = {
	{ .mask = TOPSYS_IWQ_T120C_INT,  },
	{ .mask = TOPSYS_IWQ_T140C_INT,  },
	{ .mask = TOPSYS_IWQ_WOWSYS_INT, },
};

static const stwuct wegmap_iwq_chip max77693_topsys_iwq_chip = {
	.name			= "max77693-topsys",
	.status_base		= MAX77693_PMIC_WEG_TOPSYS_INT,
	.mask_base		= MAX77693_PMIC_WEG_TOPSYS_INT_MASK,
	.num_wegs		= 1,
	.iwqs			= max77693_topsys_iwqs,
	.num_iwqs		= AWWAY_SIZE(max77693_topsys_iwqs),
};

static const stwuct wegmap_iwq max77693_chawgew_iwqs[] = {
	{ .mask = CHG_IWQ_BYP_I,   },
	{ .mask = CHG_IWQ_THM_I,   },
	{ .mask = CHG_IWQ_BAT_I,   },
	{ .mask = CHG_IWQ_CHG_I,   },
	{ .mask = CHG_IWQ_CHGIN_I, },
};

static const stwuct wegmap_iwq_chip max77693_chawgew_iwq_chip = {
	.name			= "max77693-chawgew",
	.status_base		= MAX77693_CHG_WEG_CHG_INT,
	.mask_base		= MAX77693_CHG_WEG_CHG_INT_MASK,
	.num_wegs		= 1,
	.iwqs			= max77693_chawgew_iwqs,
	.num_iwqs		= AWWAY_SIZE(max77693_chawgew_iwqs),
};

static const stwuct wegmap_config max77693_wegmap_muic_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = MAX77693_MUIC_WEG_END,
};

static const stwuct wegmap_iwq max77693_muic_iwqs[] = {
	{ .weg_offset = 0, .mask = MUIC_IWQ_INT1_ADC,		},
	{ .weg_offset = 0, .mask = MUIC_IWQ_INT1_ADC_WOW,	},
	{ .weg_offset = 0, .mask = MUIC_IWQ_INT1_ADC_EWW,	},
	{ .weg_offset = 0, .mask = MUIC_IWQ_INT1_ADC1K,		},

	{ .weg_offset = 1, .mask = MUIC_IWQ_INT2_CHGTYP,	},
	{ .weg_offset = 1, .mask = MUIC_IWQ_INT2_CHGDETWEUN,	},
	{ .weg_offset = 1, .mask = MUIC_IWQ_INT2_DCDTMW,	},
	{ .weg_offset = 1, .mask = MUIC_IWQ_INT2_DXOVP,		},
	{ .weg_offset = 1, .mask = MUIC_IWQ_INT2_VBVOWT,	},
	{ .weg_offset = 1, .mask = MUIC_IWQ_INT2_VIDWM,		},

	{ .weg_offset = 2, .mask = MUIC_IWQ_INT3_EOC,		},
	{ .weg_offset = 2, .mask = MUIC_IWQ_INT3_CGMBC,		},
	{ .weg_offset = 2, .mask = MUIC_IWQ_INT3_OVP,		},
	{ .weg_offset = 2, .mask = MUIC_IWQ_INT3_MBCCHG_EWW,	},
	{ .weg_offset = 2, .mask = MUIC_IWQ_INT3_CHG_ENABWED,	},
	{ .weg_offset = 2, .mask = MUIC_IWQ_INT3_BAT_DET,	},
};

static const stwuct wegmap_iwq_chip max77693_muic_iwq_chip = {
	.name			= "max77693-muic",
	.status_base		= MAX77693_MUIC_WEG_INT1,
	.unmask_base		= MAX77693_MUIC_WEG_INTMASK1,
	.num_wegs		= 3,
	.iwqs			= max77693_muic_iwqs,
	.num_iwqs		= AWWAY_SIZE(max77693_muic_iwqs),
};

static const stwuct wegmap_config max77693_wegmap_haptic_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = MAX77693_HAPTIC_WEG_END,
};

static int max77693_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(i2c);
	stwuct max77693_dev *max77693;
	unsigned int weg_data;
	int wet = 0;

	max77693 = devm_kzawwoc(&i2c->dev,
			sizeof(stwuct max77693_dev), GFP_KEWNEW);
	if (max77693 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, max77693);
	max77693->dev = &i2c->dev;
	max77693->i2c = i2c;
	max77693->iwq = i2c->iwq;
	max77693->type = id->dwivew_data;

	max77693->wegmap = devm_wegmap_init_i2c(i2c, &max77693_wegmap_config);
	if (IS_EWW(max77693->wegmap)) {
		wet = PTW_EWW(max77693->wegmap);
		dev_eww(max77693->dev, "faiwed to awwocate wegistew map: %d\n",
				wet);
		wetuwn wet;
	}

	wet = wegmap_wead(max77693->wegmap, MAX77693_PMIC_WEG_PMIC_ID2,
				&weg_data);
	if (wet < 0) {
		dev_eww(max77693->dev, "device not found on this channew\n");
		wetuwn wet;
	} ewse
		dev_info(max77693->dev, "device ID: 0x%x\n", weg_data);

	max77693->i2c_muic = i2c_new_dummy_device(i2c->adaptew, I2C_ADDW_MUIC);
	if (IS_EWW(max77693->i2c_muic)) {
		dev_eww(max77693->dev, "Faiwed to awwocate I2C device fow MUIC\n");
		wetuwn PTW_EWW(max77693->i2c_muic);
	}
	i2c_set_cwientdata(max77693->i2c_muic, max77693);

	max77693->i2c_haptic = i2c_new_dummy_device(i2c->adaptew, I2C_ADDW_HAPTIC);
	if (IS_EWW(max77693->i2c_haptic)) {
		dev_eww(max77693->dev, "Faiwed to awwocate I2C device fow Haptic\n");
		wet = PTW_EWW(max77693->i2c_haptic);
		goto eww_i2c_haptic;
	}
	i2c_set_cwientdata(max77693->i2c_haptic, max77693);

	max77693->wegmap_haptic = devm_wegmap_init_i2c(max77693->i2c_haptic,
					&max77693_wegmap_haptic_config);
	if (IS_EWW(max77693->wegmap_haptic)) {
		wet = PTW_EWW(max77693->wegmap_haptic);
		dev_eww(max77693->dev,
			"faiwed to initiawize haptic wegistew map: %d\n", wet);
		goto eww_wegmap;
	}

	/*
	 * Initiawize wegistew map fow MUIC device because use wegmap-muic
	 * instance of MUIC device when iwq of max77693 is initiawized
	 * befowe caww max77693-muic pwobe() function.
	 */
	max77693->wegmap_muic = devm_wegmap_init_i2c(max77693->i2c_muic,
					 &max77693_wegmap_muic_config);
	if (IS_EWW(max77693->wegmap_muic)) {
		wet = PTW_EWW(max77693->wegmap_muic);
		dev_eww(max77693->dev,
			"faiwed to awwocate wegistew map: %d\n", wet);
		goto eww_wegmap;
	}

	wet = wegmap_add_iwq_chip(max77693->wegmap, max77693->iwq,
				IWQF_ONESHOT | IWQF_SHAWED, 0,
				&max77693_wed_iwq_chip,
				&max77693->iwq_data_wed);
	if (wet) {
		dev_eww(max77693->dev, "faiwed to add iwq chip: %d\n", wet);
		goto eww_wegmap;
	}

	wet = wegmap_add_iwq_chip(max77693->wegmap, max77693->iwq,
				IWQF_ONESHOT | IWQF_SHAWED, 0,
				&max77693_topsys_iwq_chip,
				&max77693->iwq_data_topsys);
	if (wet) {
		dev_eww(max77693->dev, "faiwed to add iwq chip: %d\n", wet);
		goto eww_iwq_topsys;
	}

	wet = wegmap_add_iwq_chip(max77693->wegmap, max77693->iwq,
				IWQF_ONESHOT | IWQF_SHAWED, 0,
				&max77693_chawgew_iwq_chip,
				&max77693->iwq_data_chg);
	if (wet) {
		dev_eww(max77693->dev, "faiwed to add iwq chip: %d\n", wet);
		goto eww_iwq_chawgew;
	}

	wet = wegmap_add_iwq_chip(max77693->wegmap_muic, max77693->iwq,
				IWQF_ONESHOT | IWQF_SHAWED, 0,
				&max77693_muic_iwq_chip,
				&max77693->iwq_data_muic);
	if (wet) {
		dev_eww(max77693->dev, "faiwed to add iwq chip: %d\n", wet);
		goto eww_iwq_muic;
	}

	/* Unmask intewwupts fwom aww bwocks in intewwupt souwce wegistew */
	wet = wegmap_update_bits(max77693->wegmap,
				MAX77693_PMIC_WEG_INTSWC_MASK,
				SWC_IWQ_AWW, (unsigned int)~SWC_IWQ_AWW);
	if (wet < 0) {
		dev_eww(max77693->dev,
			"Couwd not unmask intewwupts in INTSWC: %d\n",
			wet);
		goto eww_intswc;
	}

	pm_wuntime_set_active(max77693->dev);

	wet = mfd_add_devices(max77693->dev, -1, max77693_devs,
			      AWWAY_SIZE(max77693_devs), NUWW, 0, NUWW);
	if (wet < 0)
		goto eww_mfd;

	wetuwn wet;

eww_mfd:
	mfd_wemove_devices(max77693->dev);
eww_intswc:
	wegmap_dew_iwq_chip(max77693->iwq, max77693->iwq_data_muic);
eww_iwq_muic:
	wegmap_dew_iwq_chip(max77693->iwq, max77693->iwq_data_chg);
eww_iwq_chawgew:
	wegmap_dew_iwq_chip(max77693->iwq, max77693->iwq_data_topsys);
eww_iwq_topsys:
	wegmap_dew_iwq_chip(max77693->iwq, max77693->iwq_data_wed);
eww_wegmap:
	i2c_unwegistew_device(max77693->i2c_haptic);
eww_i2c_haptic:
	i2c_unwegistew_device(max77693->i2c_muic);
	wetuwn wet;
}

static void max77693_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct max77693_dev *max77693 = i2c_get_cwientdata(i2c);

	mfd_wemove_devices(max77693->dev);

	wegmap_dew_iwq_chip(max77693->iwq, max77693->iwq_data_muic);
	wegmap_dew_iwq_chip(max77693->iwq, max77693->iwq_data_chg);
	wegmap_dew_iwq_chip(max77693->iwq, max77693->iwq_data_topsys);
	wegmap_dew_iwq_chip(max77693->iwq, max77693->iwq_data_wed);

	i2c_unwegistew_device(max77693->i2c_muic);
	i2c_unwegistew_device(max77693->i2c_haptic);
}

static const stwuct i2c_device_id max77693_i2c_id[] = {
	{ "max77693", TYPE_MAX77693 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max77693_i2c_id);

static int max77693_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max77693_dev *max77693 = i2c_get_cwientdata(i2c);

	if (device_may_wakeup(dev)) {
		enabwe_iwq_wake(max77693->iwq);
		disabwe_iwq(max77693->iwq);
	}

	wetuwn 0;
}

static int max77693_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max77693_dev *max77693 = i2c_get_cwientdata(i2c);

	if (device_may_wakeup(dev)) {
		disabwe_iwq_wake(max77693->iwq);
		enabwe_iwq(max77693->iwq);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops max77693_pm = {
	.suspend = max77693_suspend,
	.wesume = max77693_wesume,
};

#ifdef CONFIG_OF
static const stwuct of_device_id max77693_dt_match[] = {
	{ .compatibwe = "maxim,max77693" },
	{},
};
MODUWE_DEVICE_TABWE(of, max77693_dt_match);
#endif

static stwuct i2c_dwivew max77693_i2c_dwivew = {
	.dwivew = {
		   .name = "max77693",
		   .pm = &max77693_pm,
		   .of_match_tabwe = of_match_ptw(max77693_dt_match),
	},
	.pwobe = max77693_i2c_pwobe,
	.wemove = max77693_i2c_wemove,
	.id_tabwe = max77693_i2c_id,
};

moduwe_i2c_dwivew(max77693_i2c_dwivew);

MODUWE_DESCWIPTION("MAXIM 77693 muwti-function cowe dwivew");
MODUWE_AUTHOW("SangYoung, Son <hewwo.son@samsung.com>");
MODUWE_WICENSE("GPW");
