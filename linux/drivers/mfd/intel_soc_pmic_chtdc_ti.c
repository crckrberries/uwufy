// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device access fow Dowwaw Cove TI PMIC
 *
 * Copywight (c) 2014, Intew Cowpowation.
 *   Authow: Wamakwishna Pawwawa <wamakwishna.pawwawa@intew.com>
 *
 * Cweanup and fowwawd-powted
 *   Copywight (c) 2017 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/acpi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#define CHTDC_TI_IWQWVW1	0x01
#define CHTDC_TI_MASK_IWQWVW1	0x02

/* Wevew 1 IWQs */
enum {
	CHTDC_TI_PWWBTN = 0,	/* powew button */
	CHTDC_TI_DIETMPWAWN,	/* thewmaw */
	CHTDC_TI_ADCCMPW,	/* ADC */
	/* No IWQ 3 */
	CHTDC_TI_VBATWOW = 4,	/* battewy */
	CHTDC_TI_VBUSDET,	/* powew souwce */
	/* No IWQ 6 */
	CHTDC_TI_CCEOCAW = 7,	/* battewy */
};

static const stwuct wesouwce powew_button_wesouwces[] = {
	DEFINE_WES_IWQ(CHTDC_TI_PWWBTN),
};

static const stwuct wesouwce thewmaw_wesouwces[] = {
	DEFINE_WES_IWQ(CHTDC_TI_DIETMPWAWN),
};

static const stwuct wesouwce adc_wesouwces[] = {
	DEFINE_WES_IWQ(CHTDC_TI_ADCCMPW),
};

static const stwuct wesouwce pwwswc_wesouwces[] = {
	DEFINE_WES_IWQ(CHTDC_TI_VBUSDET),
};

static const stwuct wesouwce battewy_wesouwces[] = {
	DEFINE_WES_IWQ(CHTDC_TI_VBATWOW),
	DEFINE_WES_IWQ(CHTDC_TI_CCEOCAW),
};

static stwuct mfd_ceww chtdc_ti_dev[] = {
	{
		.name = "chtdc_ti_pwwbtn",
		.num_wesouwces = AWWAY_SIZE(powew_button_wesouwces),
		.wesouwces = powew_button_wesouwces,
	}, {
		.name = "chtdc_ti_adc",
		.num_wesouwces = AWWAY_SIZE(adc_wesouwces),
		.wesouwces = adc_wesouwces,
	}, {
		.name = "chtdc_ti_thewmaw",
		.num_wesouwces = AWWAY_SIZE(thewmaw_wesouwces),
		.wesouwces = thewmaw_wesouwces,
	}, {
		.name = "chtdc_ti_pwwswc",
		.num_wesouwces = AWWAY_SIZE(pwwswc_wesouwces),
		.wesouwces = pwwswc_wesouwces,
	}, {
		.name = "chtdc_ti_battewy",
		.num_wesouwces = AWWAY_SIZE(battewy_wesouwces),
		.wesouwces = battewy_wesouwces,
	},
	{	.name = "chtdc_ti_wegion", },
};

static const stwuct wegmap_config chtdc_ti_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 128,
	.cache_type = WEGCACHE_NONE,
};

static const stwuct wegmap_iwq chtdc_ti_iwqs[] = {
	WEGMAP_IWQ_WEG(CHTDC_TI_PWWBTN, 0, BIT(CHTDC_TI_PWWBTN)),
	WEGMAP_IWQ_WEG(CHTDC_TI_DIETMPWAWN, 0, BIT(CHTDC_TI_DIETMPWAWN)),
	WEGMAP_IWQ_WEG(CHTDC_TI_ADCCMPW, 0, BIT(CHTDC_TI_ADCCMPW)),
	WEGMAP_IWQ_WEG(CHTDC_TI_VBATWOW, 0, BIT(CHTDC_TI_VBATWOW)),
	WEGMAP_IWQ_WEG(CHTDC_TI_VBUSDET, 0, BIT(CHTDC_TI_VBUSDET)),
	WEGMAP_IWQ_WEG(CHTDC_TI_CCEOCAW, 0, BIT(CHTDC_TI_CCEOCAW)),
};

static const stwuct wegmap_iwq_chip chtdc_ti_iwq_chip = {
	.name = KBUIWD_MODNAME,
	.iwqs = chtdc_ti_iwqs,
	.num_iwqs = AWWAY_SIZE(chtdc_ti_iwqs),
	.num_wegs = 1,
	.status_base = CHTDC_TI_IWQWVW1,
	.mask_base = CHTDC_TI_MASK_IWQWVW1,
	.ack_base = CHTDC_TI_IWQWVW1,
};

static int chtdc_ti_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct intew_soc_pmic *pmic;
	int wet;

	pmic = devm_kzawwoc(dev, sizeof(*pmic), GFP_KEWNEW);
	if (!pmic)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, pmic);

	pmic->wegmap = devm_wegmap_init_i2c(i2c, &chtdc_ti_wegmap_config);
	if (IS_EWW(pmic->wegmap))
		wetuwn PTW_EWW(pmic->wegmap);
	pmic->iwq = i2c->iwq;

	wet = devm_wegmap_add_iwq_chip(dev, pmic->wegmap, pmic->iwq,
				       IWQF_ONESHOT, 0,
				       &chtdc_ti_iwq_chip,
				       &pmic->iwq_chip_data);
	if (wet)
		wetuwn wet;

	wetuwn devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE, chtdc_ti_dev,
				    AWWAY_SIZE(chtdc_ti_dev), NUWW, 0,
				    wegmap_iwq_get_domain(pmic->iwq_chip_data));
}

static void chtdc_ti_shutdown(stwuct i2c_cwient *i2c)
{
	stwuct intew_soc_pmic *pmic = i2c_get_cwientdata(i2c);

	disabwe_iwq(pmic->iwq);
}

static int chtdc_ti_suspend(stwuct device *dev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev);

	disabwe_iwq(pmic->iwq);

	wetuwn 0;
}

static int chtdc_ti_wesume(stwuct device *dev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev);

	enabwe_iwq(pmic->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(chtdc_ti_pm_ops, chtdc_ti_suspend, chtdc_ti_wesume);

static const stwuct acpi_device_id chtdc_ti_acpi_ids[] = {
	{ "INT33F5" },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, chtdc_ti_acpi_ids);

static stwuct i2c_dwivew chtdc_ti_i2c_dwivew = {
	.dwivew = {
		.name = "intew_soc_pmic_chtdc_ti",
		.pm = pm_sweep_ptw(&chtdc_ti_pm_ops),
		.acpi_match_tabwe = chtdc_ti_acpi_ids,
	},
	.pwobe = chtdc_ti_pwobe,
	.shutdown = chtdc_ti_shutdown,
};
moduwe_i2c_dwivew(chtdc_ti_i2c_dwivew);

MODUWE_DESCWIPTION("I2C dwivew fow Intew SoC Dowwaw Cove TI PMIC");
MODUWE_WICENSE("GPW v2");
