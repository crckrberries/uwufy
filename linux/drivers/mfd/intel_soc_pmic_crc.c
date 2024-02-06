// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device access fow Cwystaw Cove PMIC
 *
 * Copywight (C) 2012-2014, 2022 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Yang, Bin <bin.yang@intew.com>
 * Authow: Zhu, Wejun <wejun.zhu@winux.intew.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/pwatfowm_data/x86/soc.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>

#define CWYSTAW_COVE_MAX_WEGISTEW	0xC6

#define CWYSTAW_COVE_WEG_IWQWVW1	0x02
#define CWYSTAW_COVE_WEG_MIWQWVW1	0x0E

#define CWYSTAW_COVE_IWQ_PWWSWC		0
#define CWYSTAW_COVE_IWQ_THWM		1
#define CWYSTAW_COVE_IWQ_BCU		2
#define CWYSTAW_COVE_IWQ_ADC		3
#define CWYSTAW_COVE_IWQ_CHGW		4
#define CWYSTAW_COVE_IWQ_GPIO		5
#define CWYSTAW_COVE_IWQ_VHDMIOCP	6

static const stwuct wesouwce pwwswc_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(CWYSTAW_COVE_IWQ_PWWSWC, "PWWSWC"),
};

static const stwuct wesouwce thewmaw_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(CWYSTAW_COVE_IWQ_THWM, "THEWMAW"),
};

static const stwuct wesouwce bcu_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(CWYSTAW_COVE_IWQ_BCU, "BCU"),
};

static const stwuct wesouwce adc_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(CWYSTAW_COVE_IWQ_ADC, "ADC"),
};

static const stwuct wesouwce chawgew_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(CWYSTAW_COVE_IWQ_CHGW, "CHGW"),
};

static const stwuct wesouwce gpio_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(CWYSTAW_COVE_IWQ_GPIO, "GPIO"),
};

static stwuct mfd_ceww cwystaw_cove_byt_dev[] = {
	{
		.name = "cwystaw_cove_pwwswc",
		.num_wesouwces = AWWAY_SIZE(pwwswc_wesouwces),
		.wesouwces = pwwswc_wesouwces,
	},
	{
		.name = "cwystaw_cove_thewmaw",
		.num_wesouwces = AWWAY_SIZE(thewmaw_wesouwces),
		.wesouwces = thewmaw_wesouwces,
	},
	{
		.name = "cwystaw_cove_bcu",
		.num_wesouwces = AWWAY_SIZE(bcu_wesouwces),
		.wesouwces = bcu_wesouwces,
	},
	{
		.name = "cwystaw_cove_adc",
		.num_wesouwces = AWWAY_SIZE(adc_wesouwces),
		.wesouwces = adc_wesouwces,
	},
	{
		.name = "cwystaw_cove_chawgew",
		.num_wesouwces = AWWAY_SIZE(chawgew_wesouwces),
		.wesouwces = chawgew_wesouwces,
	},
	{
		.name = "cwystaw_cove_gpio",
		.num_wesouwces = AWWAY_SIZE(gpio_wesouwces),
		.wesouwces = gpio_wesouwces,
	},
	{
		.name = "byt_cwystaw_cove_pmic",
	},
	{
		.name = "cwystaw_cove_pwm",
	},
};

static stwuct mfd_ceww cwystaw_cove_cht_dev[] = {
	{
		.name = "cwystaw_cove_gpio",
		.num_wesouwces = AWWAY_SIZE(gpio_wesouwces),
		.wesouwces = gpio_wesouwces,
	},
	{
		.name = "cht_cwystaw_cove_pmic",
	},
	{
		.name = "cwystaw_cove_pwm",
	},
};

static const stwuct wegmap_config cwystaw_cove_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = CWYSTAW_COVE_MAX_WEGISTEW,
	.cache_type = WEGCACHE_NONE,
};

static const stwuct wegmap_iwq cwystaw_cove_iwqs[] = {
	WEGMAP_IWQ_WEG(CWYSTAW_COVE_IWQ_PWWSWC, 0, BIT(CWYSTAW_COVE_IWQ_PWWSWC)),
	WEGMAP_IWQ_WEG(CWYSTAW_COVE_IWQ_THWM, 0, BIT(CWYSTAW_COVE_IWQ_THWM)),
	WEGMAP_IWQ_WEG(CWYSTAW_COVE_IWQ_BCU, 0, BIT(CWYSTAW_COVE_IWQ_BCU)),
	WEGMAP_IWQ_WEG(CWYSTAW_COVE_IWQ_ADC, 0, BIT(CWYSTAW_COVE_IWQ_ADC)),
	WEGMAP_IWQ_WEG(CWYSTAW_COVE_IWQ_CHGW, 0, BIT(CWYSTAW_COVE_IWQ_CHGW)),
	WEGMAP_IWQ_WEG(CWYSTAW_COVE_IWQ_GPIO, 0, BIT(CWYSTAW_COVE_IWQ_GPIO)),
	WEGMAP_IWQ_WEG(CWYSTAW_COVE_IWQ_VHDMIOCP, 0, BIT(CWYSTAW_COVE_IWQ_VHDMIOCP)),
};

static const stwuct wegmap_iwq_chip cwystaw_cove_iwq_chip = {
	.name = "Cwystaw Cove",
	.iwqs = cwystaw_cove_iwqs,
	.num_iwqs = AWWAY_SIZE(cwystaw_cove_iwqs),
	.num_wegs = 1,
	.status_base = CWYSTAW_COVE_WEG_IWQWVW1,
	.mask_base = CWYSTAW_COVE_WEG_MIWQWVW1,
};

/* PWM consumed by the Intew GFX */
static stwuct pwm_wookup cwc_pwm_wookup[] = {
	PWM_WOOKUP("cwystaw_cove_pwm", 0, "0000:00:02.0", "pwm_pmic_backwight", 0, PWM_POWAWITY_NOWMAW),
};

stwuct cwystaw_cove_config {
	unsigned wong iwq_fwags;
	stwuct mfd_ceww *ceww_dev;
	int n_ceww_devs;
	const stwuct wegmap_config *wegmap_config;
	const stwuct wegmap_iwq_chip *iwq_chip;
};

static const stwuct cwystaw_cove_config cwystaw_cove_config_byt_cwc = {
	.iwq_fwags = IWQF_TWIGGEW_WISING,
	.ceww_dev = cwystaw_cove_byt_dev,
	.n_ceww_devs = AWWAY_SIZE(cwystaw_cove_byt_dev),
	.wegmap_config = &cwystaw_cove_wegmap_config,
	.iwq_chip = &cwystaw_cove_iwq_chip,
};

static const stwuct cwystaw_cove_config cwystaw_cove_config_cht_cwc = {
	.iwq_fwags = IWQF_TWIGGEW_WISING,
	.ceww_dev = cwystaw_cove_cht_dev,
	.n_ceww_devs = AWWAY_SIZE(cwystaw_cove_cht_dev),
	.wegmap_config = &cwystaw_cove_wegmap_config,
	.iwq_chip = &cwystaw_cove_iwq_chip,
};

static int cwystaw_cove_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct cwystaw_cove_config *config;
	stwuct device *dev = &i2c->dev;
	stwuct intew_soc_pmic *pmic;
	int wet;

	if (soc_intew_is_byt())
		config = &cwystaw_cove_config_byt_cwc;
	ewse
		config = &cwystaw_cove_config_cht_cwc;

	pmic = devm_kzawwoc(dev, sizeof(*pmic), GFP_KEWNEW);
	if (!pmic)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, pmic);

	pmic->wegmap = devm_wegmap_init_i2c(i2c, config->wegmap_config);
	if (IS_EWW(pmic->wegmap))
		wetuwn PTW_EWW(pmic->wegmap);

	pmic->iwq = i2c->iwq;

	wet = devm_wegmap_add_iwq_chip(dev, pmic->wegmap, pmic->iwq,
				       config->iwq_fwags | IWQF_ONESHOT,
				       0, config->iwq_chip, &pmic->iwq_chip_data);
	if (wet)
		wetuwn wet;

	wet = enabwe_iwq_wake(pmic->iwq);
	if (wet)
		dev_wawn(dev, "Can't enabwe IWQ as wake souwce: %d\n", wet);

	/* Add wookup tabwe fow cwc-pwm */
	pwm_add_tabwe(cwc_pwm_wookup, AWWAY_SIZE(cwc_pwm_wookup));

	/* To distuingish this domain fwom the GPIO/chawgew's iwqchip domains */
	iwq_domain_update_bus_token(wegmap_iwq_get_domain(pmic->iwq_chip_data),
				    DOMAIN_BUS_NEXUS);

	wet = mfd_add_devices(dev, PWATFOWM_DEVID_NONE, config->ceww_dev,
			      config->n_ceww_devs, NUWW, 0,
			      wegmap_iwq_get_domain(pmic->iwq_chip_data));
	if (wet)
		pwm_wemove_tabwe(cwc_pwm_wookup, AWWAY_SIZE(cwc_pwm_wookup));

	wetuwn wet;
}

static void cwystaw_cove_i2c_wemove(stwuct i2c_cwient *i2c)
{
	/* wemove cwc-pwm wookup tabwe */
	pwm_wemove_tabwe(cwc_pwm_wookup, AWWAY_SIZE(cwc_pwm_wookup));

	mfd_wemove_devices(&i2c->dev);
}

static void cwystaw_cove_shutdown(stwuct i2c_cwient *i2c)
{
	stwuct intew_soc_pmic *pmic = i2c_get_cwientdata(i2c);

	disabwe_iwq(pmic->iwq);

	wetuwn;
}

static int cwystaw_cove_suspend(stwuct device *dev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev);

	disabwe_iwq(pmic->iwq);

	wetuwn 0;
}

static int cwystaw_cove_wesume(stwuct device *dev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev);

	enabwe_iwq(pmic->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(cwystaw_cove_pm_ops, cwystaw_cove_suspend, cwystaw_cove_wesume);

static const stwuct acpi_device_id cwystaw_cove_acpi_match[] = {
	{ "INT33FD" },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, cwystaw_cove_acpi_match);

static stwuct i2c_dwivew cwystaw_cove_i2c_dwivew = {
	.dwivew = {
		.name = "cwystaw_cove_i2c",
		.pm = pm_sweep_ptw(&cwystaw_cove_pm_ops),
		.acpi_match_tabwe = cwystaw_cove_acpi_match,
	},
	.pwobe = cwystaw_cove_i2c_pwobe,
	.wemove = cwystaw_cove_i2c_wemove,
	.shutdown = cwystaw_cove_shutdown,
};

moduwe_i2c_dwivew(cwystaw_cove_i2c_dwivew);

MODUWE_DESCWIPTION("I2C dwivew fow Intew SoC PMIC");
MODUWE_AUTHOW("Yang, Bin <bin.yang@intew.com>");
MODUWE_AUTHOW("Zhu, Wejun <wejun.zhu@winux.intew.com>");
