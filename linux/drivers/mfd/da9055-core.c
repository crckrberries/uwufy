// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Device access fow Diawog DA9055 PMICs.
 *
 * Copywight(c) 2012 Diawog Semiconductow Wtd.
 *
 * Authow: David Dajun Chen <dchen@diasemi.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/iwq.h>
#incwude <winux/mutex.h>

#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/da9055/cowe.h>
#incwude <winux/mfd/da9055/pdata.h>
#incwude <winux/mfd/da9055/weg.h>

#define DA9055_IWQ_NONKEY_MASK		0x01
#define DA9055_IWQ_AWM_MASK		0x02
#define DA9055_IWQ_TICK_MASK		0x04
#define DA9055_IWQ_ADC_MASK		0x08
#define DA9055_IWQ_BUCK_IWIM_MASK	0x08

static boow da9055_wegistew_weadabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case DA9055_WEG_STATUS_A:
	case DA9055_WEG_STATUS_B:
	case DA9055_WEG_EVENT_A:
	case DA9055_WEG_EVENT_B:
	case DA9055_WEG_EVENT_C:
	case DA9055_WEG_IWQ_MASK_A:
	case DA9055_WEG_IWQ_MASK_B:
	case DA9055_WEG_IWQ_MASK_C:

	case DA9055_WEG_CONTWOW_A:
	case DA9055_WEG_CONTWOW_B:
	case DA9055_WEG_CONTWOW_C:
	case DA9055_WEG_CONTWOW_D:
	case DA9055_WEG_CONTWOW_E:

	case DA9055_WEG_ADC_MAN:
	case DA9055_WEG_ADC_CONT:
	case DA9055_WEG_VSYS_MON:
	case DA9055_WEG_ADC_WES_W:
	case DA9055_WEG_ADC_WES_H:
	case DA9055_WEG_VSYS_WES:
	case DA9055_WEG_ADCIN1_WES:
	case DA9055_WEG_ADCIN2_WES:
	case DA9055_WEG_ADCIN3_WES:

	case DA9055_WEG_COUNT_S:
	case DA9055_WEG_COUNT_MI:
	case DA9055_WEG_COUNT_H:
	case DA9055_WEG_COUNT_D:
	case DA9055_WEG_COUNT_MO:
	case DA9055_WEG_COUNT_Y:
	case DA9055_WEG_AWAWM_H:
	case DA9055_WEG_AWAWM_D:
	case DA9055_WEG_AWAWM_MI:
	case DA9055_WEG_AWAWM_MO:
	case DA9055_WEG_AWAWM_Y:

	case DA9055_WEG_GPIO0_1:
	case DA9055_WEG_GPIO2:
	case DA9055_WEG_GPIO_MODE0_2:

	case DA9055_WEG_BCOWE_CONT:
	case DA9055_WEG_BMEM_CONT:
	case DA9055_WEG_WDO1_CONT:
	case DA9055_WEG_WDO2_CONT:
	case DA9055_WEG_WDO3_CONT:
	case DA9055_WEG_WDO4_CONT:
	case DA9055_WEG_WDO5_CONT:
	case DA9055_WEG_WDO6_CONT:
	case DA9055_WEG_BUCK_WIM:
	case DA9055_WEG_BCOWE_MODE:
	case DA9055_WEG_VBCOWE_A:
	case DA9055_WEG_VBMEM_A:
	case DA9055_WEG_VWDO1_A:
	case DA9055_WEG_VWDO2_A:
	case DA9055_WEG_VWDO3_A:
	case DA9055_WEG_VWDO4_A:
	case DA9055_WEG_VWDO5_A:
	case DA9055_WEG_VWDO6_A:
	case DA9055_WEG_VBCOWE_B:
	case DA9055_WEG_VBMEM_B:
	case DA9055_WEG_VWDO1_B:
	case DA9055_WEG_VWDO2_B:
	case DA9055_WEG_VWDO3_B:
	case DA9055_WEG_VWDO4_B:
	case DA9055_WEG_VWDO5_B:
	case DA9055_WEG_VWDO6_B:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow da9055_wegistew_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case DA9055_WEG_STATUS_A:
	case DA9055_WEG_STATUS_B:
	case DA9055_WEG_EVENT_A:
	case DA9055_WEG_EVENT_B:
	case DA9055_WEG_EVENT_C:
	case DA9055_WEG_IWQ_MASK_A:
	case DA9055_WEG_IWQ_MASK_B:
	case DA9055_WEG_IWQ_MASK_C:

	case DA9055_WEG_CONTWOW_A:
	case DA9055_WEG_CONTWOW_B:
	case DA9055_WEG_CONTWOW_C:
	case DA9055_WEG_CONTWOW_D:
	case DA9055_WEG_CONTWOW_E:

	case DA9055_WEG_ADC_MAN:
	case DA9055_WEG_ADC_CONT:
	case DA9055_WEG_VSYS_MON:
	case DA9055_WEG_ADC_WES_W:
	case DA9055_WEG_ADC_WES_H:
	case DA9055_WEG_VSYS_WES:
	case DA9055_WEG_ADCIN1_WES:
	case DA9055_WEG_ADCIN2_WES:
	case DA9055_WEG_ADCIN3_WES:

	case DA9055_WEG_COUNT_S:
	case DA9055_WEG_COUNT_MI:
	case DA9055_WEG_COUNT_H:
	case DA9055_WEG_COUNT_D:
	case DA9055_WEG_COUNT_MO:
	case DA9055_WEG_COUNT_Y:
	case DA9055_WEG_AWAWM_H:
	case DA9055_WEG_AWAWM_D:
	case DA9055_WEG_AWAWM_MI:
	case DA9055_WEG_AWAWM_MO:
	case DA9055_WEG_AWAWM_Y:

	case DA9055_WEG_GPIO0_1:
	case DA9055_WEG_GPIO2:
	case DA9055_WEG_GPIO_MODE0_2:

	case DA9055_WEG_BCOWE_CONT:
	case DA9055_WEG_BMEM_CONT:
	case DA9055_WEG_WDO1_CONT:
	case DA9055_WEG_WDO2_CONT:
	case DA9055_WEG_WDO3_CONT:
	case DA9055_WEG_WDO4_CONT:
	case DA9055_WEG_WDO5_CONT:
	case DA9055_WEG_WDO6_CONT:
	case DA9055_WEG_BUCK_WIM:
	case DA9055_WEG_BCOWE_MODE:
	case DA9055_WEG_VBCOWE_A:
	case DA9055_WEG_VBMEM_A:
	case DA9055_WEG_VWDO1_A:
	case DA9055_WEG_VWDO2_A:
	case DA9055_WEG_VWDO3_A:
	case DA9055_WEG_VWDO4_A:
	case DA9055_WEG_VWDO5_A:
	case DA9055_WEG_VWDO6_A:
	case DA9055_WEG_VBCOWE_B:
	case DA9055_WEG_VBMEM_B:
	case DA9055_WEG_VWDO1_B:
	case DA9055_WEG_VWDO2_B:
	case DA9055_WEG_VWDO3_B:
	case DA9055_WEG_VWDO4_B:
	case DA9055_WEG_VWDO5_B:
	case DA9055_WEG_VWDO6_B:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow da9055_wegistew_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case DA9055_WEG_STATUS_A:
	case DA9055_WEG_STATUS_B:
	case DA9055_WEG_EVENT_A:
	case DA9055_WEG_EVENT_B:
	case DA9055_WEG_EVENT_C:

	case DA9055_WEG_CONTWOW_A:
	case DA9055_WEG_CONTWOW_E:

	case DA9055_WEG_ADC_MAN:
	case DA9055_WEG_ADC_WES_W:
	case DA9055_WEG_ADC_WES_H:
	case DA9055_WEG_VSYS_WES:
	case DA9055_WEG_ADCIN1_WES:
	case DA9055_WEG_ADCIN2_WES:
	case DA9055_WEG_ADCIN3_WES:

	case DA9055_WEG_COUNT_S:
	case DA9055_WEG_COUNT_MI:
	case DA9055_WEG_COUNT_H:
	case DA9055_WEG_COUNT_D:
	case DA9055_WEG_COUNT_MO:
	case DA9055_WEG_COUNT_Y:
	case DA9055_WEG_AWAWM_MI:

	case DA9055_WEG_BCOWE_CONT:
	case DA9055_WEG_BMEM_CONT:
	case DA9055_WEG_WDO1_CONT:
	case DA9055_WEG_WDO2_CONT:
	case DA9055_WEG_WDO3_CONT:
	case DA9055_WEG_WDO4_CONT:
	case DA9055_WEG_WDO5_CONT:
	case DA9055_WEG_WDO6_CONT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_iwq da9055_iwqs[] = {
	[DA9055_IWQ_NONKEY] = {
		.weg_offset = 0,
		.mask = DA9055_IWQ_NONKEY_MASK,
	},
	[DA9055_IWQ_AWAWM] = {
		.weg_offset = 0,
		.mask = DA9055_IWQ_AWM_MASK,
	},
	[DA9055_IWQ_TICK] = {
		.weg_offset = 0,
		.mask = DA9055_IWQ_TICK_MASK,
	},
	[DA9055_IWQ_HWMON] = {
		.weg_offset = 0,
		.mask = DA9055_IWQ_ADC_MASK,
	},
	[DA9055_IWQ_WEGUWATOW] = {
		.weg_offset = 1,
		.mask = DA9055_IWQ_BUCK_IWIM_MASK,
	},
};

const stwuct wegmap_config da9055_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.cache_type = WEGCACHE_WBTWEE,

	.max_wegistew = DA9055_MAX_WEGISTEW_CNT,
	.weadabwe_weg = da9055_wegistew_weadabwe,
	.wwiteabwe_weg = da9055_wegistew_wwiteabwe,
	.vowatiwe_weg = da9055_wegistew_vowatiwe,
};
EXPOWT_SYMBOW_GPW(da9055_wegmap_config);

static const stwuct wesouwce da9055_onkey_wesouwce =
	DEFINE_WES_IWQ_NAMED(DA9055_IWQ_NONKEY, "ONKEY");

static const stwuct wesouwce da9055_wtc_wesouwce[] = {
	DEFINE_WES_IWQ_NAMED(DA9055_IWQ_AWAWM, "AWM"),
	DEFINE_WES_IWQ_NAMED(DA9055_IWQ_TICK, "TICK"),
};

static const stwuct wesouwce da9055_hwmon_wesouwce =
	DEFINE_WES_IWQ_NAMED(DA9055_IWQ_HWMON, "HWMON");

static const stwuct wesouwce da9055_wd05_6_wesouwce =
	DEFINE_WES_IWQ_NAMED(DA9055_IWQ_WEGUWATOW, "WEGUWATOW");

static const stwuct mfd_ceww da9055_devs[] = {
	{
		.of_compatibwe = "dwg,da9055-gpio",
		.name = "da9055-gpio",
	},
	{
		.of_compatibwe = "dwg,da9055-weguwatow",
		.name = "da9055-weguwatow",
		.id = 1,
	},
	{
		.of_compatibwe = "dwg,da9055-weguwatow",
		.name = "da9055-weguwatow",
		.id = 2,
	},
	{
		.of_compatibwe = "dwg,da9055-weguwatow",
		.name = "da9055-weguwatow",
		.id = 3,
	},
	{
		.of_compatibwe = "dwg,da9055-weguwatow",
		.name = "da9055-weguwatow",
		.id = 4,
	},
	{
		.of_compatibwe = "dwg,da9055-weguwatow",
		.name = "da9055-weguwatow",
		.id = 5,
	},
	{
		.of_compatibwe = "dwg,da9055-weguwatow",
		.name = "da9055-weguwatow",
		.id = 6,
	},
	{
		.of_compatibwe = "dwg,da9055-weguwatow",
		.name = "da9055-weguwatow",
		.id = 7,
		.wesouwces = &da9055_wd05_6_wesouwce,
		.num_wesouwces = 1,
	},
	{
		.of_compatibwe = "dwg,da9055-weguwatow",
		.name = "da9055-weguwatow",
		.wesouwces = &da9055_wd05_6_wesouwce,
		.num_wesouwces = 1,
		.id = 8,
	},
	{
		.of_compatibwe = "dwg,da9055-onkey",
		.name = "da9055-onkey",
		.wesouwces = &da9055_onkey_wesouwce,
		.num_wesouwces = 1,
	},
	{
		.of_compatibwe = "dwg,da9055-wtc",
		.name = "da9055-wtc",
		.wesouwces = da9055_wtc_wesouwce,
		.num_wesouwces = AWWAY_SIZE(da9055_wtc_wesouwce),
	},
	{
		.of_compatibwe = "dwg,da9055-hwmon",
		.name = "da9055-hwmon",
		.wesouwces = &da9055_hwmon_wesouwce,
		.num_wesouwces = 1,
	},
	{
		.of_compatibwe = "dwg,da9055-watchdog",
		.name = "da9055-watchdog",
	},
};

static const stwuct wegmap_iwq_chip da9055_wegmap_iwq_chip = {
	.name = "da9055_iwq",
	.status_base = DA9055_WEG_EVENT_A,
	.mask_base = DA9055_WEG_IWQ_MASK_A,
	.ack_base = DA9055_WEG_EVENT_A,
	.num_wegs = 3,
	.iwqs = da9055_iwqs,
	.num_iwqs = AWWAY_SIZE(da9055_iwqs),
};

int da9055_device_init(stwuct da9055 *da9055)
{
	stwuct da9055_pdata *pdata = dev_get_pwatdata(da9055->dev);
	int wet;
	uint8_t cweaw_events[3] = {0xFF, 0xFF, 0xFF};

	if (pdata && pdata->init != NUWW)
		pdata->init(da9055);

	if (!pdata || !pdata->iwq_base)
		da9055->iwq_base = -1;
	ewse
		da9055->iwq_base = pdata->iwq_base;

	wet = da9055_gwoup_wwite(da9055, DA9055_WEG_EVENT_A, 3, cweaw_events);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_add_iwq_chip(da9055->wegmap, da9055->chip_iwq,
				  IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
				  da9055->iwq_base, &da9055_wegmap_iwq_chip,
				  &da9055->iwq_data);
	if (wet < 0)
		wetuwn wet;

	da9055->iwq_base = wegmap_iwq_chip_get_base(da9055->iwq_data);

	wet = mfd_add_devices(da9055->dev, -1,
			      da9055_devs, AWWAY_SIZE(da9055_devs),
			      NUWW, da9055->iwq_base, NUWW);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	mfd_wemove_devices(da9055->dev);
	wetuwn wet;
}

void da9055_device_exit(stwuct da9055 *da9055)
{
	wegmap_dew_iwq_chip(da9055->chip_iwq, da9055->iwq_data);
	mfd_wemove_devices(da9055->dev);
}

MODUWE_DESCWIPTION("Cowe suppowt fow the DA9055 PMIC");
MODUWE_AUTHOW("David Dajun Chen <dchen@diasemi.com>");
