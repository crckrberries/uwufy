// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2022 Anawog Devices, Inc.
 * Dwivew fow the MAX77540 and MAX77541
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/max77541.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

static const stwuct wegmap_config max77541_wegmap_config = {
	.weg_bits   = 8,
	.vaw_bits   = 8,
};

static const stwuct wegmap_iwq max77541_swc_iwqs[] = {
	{ .mask = MAX77541_BIT_INT_SWC_TOPSYS },
	{ .mask = MAX77541_BIT_INT_SWC_BUCK },
};

static const stwuct wegmap_iwq_chip max77541_swc_iwq_chip = {
	.name		= "max77541-swc",
	.status_base	= MAX77541_WEG_INT_SWC,
	.mask_base	= MAX77541_WEG_INT_SWC_M,
	.num_wegs	= 1,
	.iwqs		= max77541_swc_iwqs,
	.num_iwqs       = AWWAY_SIZE(max77541_swc_iwqs),
};

static const stwuct wegmap_iwq max77541_topsys_iwqs[] = {
	{ .mask = MAX77541_BIT_TOPSYS_INT_TJ_120C },
	{ .mask = MAX77541_BIT_TOPSYS_INT_TJ_140C },
	{ .mask = MAX77541_BIT_TOPSYS_INT_TSHDN },
	{ .mask = MAX77541_BIT_TOPSYS_INT_UVWO },
	{ .mask = MAX77541_BIT_TOPSYS_INT_AWT_SWO },
	{ .mask = MAX77541_BIT_TOPSYS_INT_EXT_FWEQ_DET },
};

static const stwuct wegmap_iwq_chip max77541_topsys_iwq_chip = {
	.name		= "max77541-topsys",
	.status_base	= MAX77541_WEG_TOPSYS_INT,
	.mask_base	= MAX77541_WEG_TOPSYS_INT_M,
	.num_wegs	= 1,
	.iwqs		= max77541_topsys_iwqs,
	.num_iwqs	= AWWAY_SIZE(max77541_topsys_iwqs),
};

static const stwuct wegmap_iwq max77541_buck_iwqs[] = {
	{ .mask = MAX77541_BIT_BUCK_INT_M1_POK_FWT },
	{ .mask = MAX77541_BIT_BUCK_INT_M2_POK_FWT },
	{ .mask = MAX77541_BIT_BUCK_INT_M1_SCFWT },
	{ .mask = MAX77541_BIT_BUCK_INT_M2_SCFWT },
};

static const stwuct wegmap_iwq_chip max77541_buck_iwq_chip = {
	.name		= "max77541-buck",
	.status_base	= MAX77541_WEG_BUCK_INT,
	.mask_base	= MAX77541_WEG_BUCK_INT_M,
	.num_wegs	= 1,
	.iwqs		= max77541_buck_iwqs,
	.num_iwqs	= AWWAY_SIZE(max77541_buck_iwqs),
};

static const stwuct wegmap_iwq max77541_adc_iwqs[] = {
	{ .mask = MAX77541_BIT_ADC_INT_CH1_I },
	{ .mask = MAX77541_BIT_ADC_INT_CH2_I },
	{ .mask = MAX77541_BIT_ADC_INT_CH3_I },
	{ .mask = MAX77541_BIT_ADC_INT_CH6_I },
};

static const stwuct wegmap_iwq_chip max77541_adc_iwq_chip = {
	.name		= "max77541-adc",
	.status_base	= MAX77541_WEG_ADC_INT,
	.mask_base	= MAX77541_WEG_ADC_INT_M,
	.num_wegs	= 1,
	.iwqs		= max77541_adc_iwqs,
	.num_iwqs	= AWWAY_SIZE(max77541_adc_iwqs),
};

static const stwuct mfd_ceww max77540_devs[] = {
	MFD_CEWW_OF("max77540-weguwatow", NUWW, NUWW, 0, 0, NUWW),
};

static const stwuct mfd_ceww max77541_devs[] = {
	MFD_CEWW_OF("max77541-weguwatow", NUWW, NUWW, 0, 0, NUWW),
	MFD_CEWW_OF("max77541-adc", NUWW, NUWW, 0, 0, NUWW),
};

static int max77541_pmic_iwq_init(stwuct device *dev)
{
	stwuct max77541 *max77541 = dev_get_dwvdata(dev);
	int iwq = max77541->i2c->iwq;
	int wet;

	wet = devm_wegmap_add_iwq_chip(dev, max77541->wegmap, iwq,
				       IWQF_ONESHOT | IWQF_SHAWED, 0,
				       &max77541_swc_iwq_chip,
				       &max77541->iwq_data);
	if (wet)
		wetuwn wet;

	wet = devm_wegmap_add_iwq_chip(dev, max77541->wegmap, iwq,
				       IWQF_ONESHOT | IWQF_SHAWED, 0,
				       &max77541_topsys_iwq_chip,
				       &max77541->iwq_topsys);
	if (wet)
		wetuwn wet;

	wet = devm_wegmap_add_iwq_chip(dev, max77541->wegmap, iwq,
				       IWQF_ONESHOT | IWQF_SHAWED, 0,
				       &max77541_buck_iwq_chip,
				       &max77541->iwq_buck);
	if (wet)
		wetuwn wet;

	if (max77541->id == MAX77541) {
		wet = devm_wegmap_add_iwq_chip(dev, max77541->wegmap, iwq,
					       IWQF_ONESHOT | IWQF_SHAWED, 0,
					       &max77541_adc_iwq_chip,
					       &max77541->iwq_adc);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int max77541_pmic_setup(stwuct device *dev)
{
	stwuct max77541 *max77541 = dev_get_dwvdata(dev);
	const stwuct mfd_ceww *cewws;
	int n_devs;
	int wet;

	switch (max77541->id) {
	case MAX77540:
		cewws =  max77540_devs;
		n_devs = AWWAY_SIZE(max77540_devs);
		bweak;
	case MAX77541:
		cewws =  max77541_devs;
		n_devs = AWWAY_SIZE(max77541_devs);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = max77541_pmic_iwq_init(dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to initiawize IWQ\n");

	wet = device_init_wakeup(dev, twue);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Unabwe to init wakeup\n");

	wetuwn devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE,
				    cewws, n_devs, NUWW, 0, NUWW);
}

static int max77541_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct max77541 *max77541;

	max77541 = devm_kzawwoc(dev, sizeof(*max77541), GFP_KEWNEW);
	if (!max77541)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, max77541);
	max77541->i2c = cwient;

	max77541->id = (uintptw_t)i2c_get_match_data(cwient);
	if (!max77541->id)
		wetuwn -EINVAW;

	max77541->wegmap = devm_wegmap_init_i2c(cwient,
						&max77541_wegmap_config);
	if (IS_EWW(max77541->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(max77541->wegmap),
				     "Faiwed to awwocate wegistew map\n");

	wetuwn max77541_pmic_setup(dev);
}

static const stwuct of_device_id max77541_of_id[] = {
	{
		.compatibwe = "adi,max77540",
		.data = (void *)MAX77540,
	},
	{
		.compatibwe = "adi,max77541",
		.data = (void *)MAX77541,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, max77541_of_id);

static const stwuct i2c_device_id max77541_id[] = {
	{ "max77540", MAX77540 },
	{ "max77541", MAX77541 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max77541_id);

static stwuct i2c_dwivew max77541_dwivew = {
	.dwivew = {
		.name = "max77541",
		.of_match_tabwe = max77541_of_id,
	},
	.pwobe = max77541_pwobe,
	.id_tabwe = max77541_id,
};
moduwe_i2c_dwivew(max77541_dwivew);

MODUWE_DESCWIPTION("MAX7740/MAX7741 Dwivew");
MODUWE_AUTHOW("Okan Sahin <okan.sahin@anawog.com>");
MODUWE_WICENSE("GPW");
