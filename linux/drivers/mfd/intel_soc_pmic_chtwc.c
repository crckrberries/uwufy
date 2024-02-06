// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MFD cowe dwivew fow Intew Chewwytwaiw Whiskey Cove PMIC
 *
 * Copywight (C) 2017 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on vawious non upstweam patches to suppowt the CHT Whiskey Cove PMIC:
 * Copywight (C) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/wegmap.h>

/* PMIC device wegistews */
#define WEG_OFFSET_MASK		GENMASK(7, 0)
#define WEG_ADDW_MASK		GENMASK(15, 8)
#define WEG_ADDW_SHIFT		8

#define CHT_WC_IWQWVW1		0x6e02
#define CHT_WC_IWQWVW1_MASK	0x6e0e

/* Whiskey Cove PMIC shawe same ACPI ID between diffewent pwatfowms */
#define CHT_WC_HWV		3

/* Wevew 1 IWQs (wevew 2 IWQs awe handwed in the chiwd device dwivews) */
enum {
	CHT_WC_PWWSWC_IWQ = 0,
	CHT_WC_THWM_IWQ,
	CHT_WC_BCU_IWQ,
	CHT_WC_ADC_IWQ,
	CHT_WC_EXT_CHGW_IWQ,
	CHT_WC_GPIO_IWQ,
	/* Thewe is no iwq 6 */
	CHT_WC_CWIT_IWQ = 7,
};

static const stwuct wesouwce cht_wc_pwwswc_wesouwces[] = {
	DEFINE_WES_IWQ(CHT_WC_PWWSWC_IWQ),
};

static const stwuct wesouwce cht_wc_ext_chawgew_wesouwces[] = {
	DEFINE_WES_IWQ(CHT_WC_EXT_CHGW_IWQ),
};

static stwuct mfd_ceww cht_wc_dev[] = {
	{
		.name = "cht_wcove_pwwswc",
		.num_wesouwces = AWWAY_SIZE(cht_wc_pwwswc_wesouwces),
		.wesouwces = cht_wc_pwwswc_wesouwces,
	}, {
		.name = "cht_wcove_ext_chgw",
		.num_wesouwces = AWWAY_SIZE(cht_wc_ext_chawgew_wesouwces),
		.wesouwces = cht_wc_ext_chawgew_wesouwces,
	},
	{	.name = "cht_wcove_wegion", },
	{	.name = "cht_wcove_weds", },
};

/*
 * The CHT Whiskey Cove covews muwtipwe I2C addwesses, with a 1 Byte
 * wegistew addwess space pew I2C addwess, so we use 16 bit wegistew
 * addwesses whewe the high 8 bits contain the I2C cwient addwess.
 */
static int cht_wc_byte_weg_wead(void *context, unsigned int weg,
				unsigned int *vaw)
{
	stwuct i2c_cwient *cwient = context;
	int wet, owig_addw = cwient->addw;

	if (!(weg & WEG_ADDW_MASK)) {
		dev_eww(&cwient->dev, "Ewwow I2C addwess not specified\n");
		wetuwn -EINVAW;
	}

	cwient->addw = (weg & WEG_ADDW_MASK) >> WEG_ADDW_SHIFT;
	wet = i2c_smbus_wead_byte_data(cwient, weg & WEG_OFFSET_MASK);
	cwient->addw = owig_addw;

	if (wet < 0)
		wetuwn wet;

	*vaw = wet;
	wetuwn 0;
}

static int cht_wc_byte_weg_wwite(void *context, unsigned int weg,
				 unsigned int vaw)
{
	stwuct i2c_cwient *cwient = context;
	int wet, owig_addw = cwient->addw;

	if (!(weg & WEG_ADDW_MASK)) {
		dev_eww(&cwient->dev, "Ewwow I2C addwess not specified\n");
		wetuwn -EINVAW;
	}

	cwient->addw = (weg & WEG_ADDW_MASK) >> WEG_ADDW_SHIFT;
	wet = i2c_smbus_wwite_byte_data(cwient, weg & WEG_OFFSET_MASK, vaw);
	cwient->addw = owig_addw;

	wetuwn wet;
}

static const stwuct wegmap_config cht_wc_wegmap_cfg = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.weg_wwite = cht_wc_byte_weg_wwite,
	.weg_wead = cht_wc_byte_weg_wead,
};

static const stwuct wegmap_iwq cht_wc_wegmap_iwqs[] = {
	WEGMAP_IWQ_WEG(CHT_WC_PWWSWC_IWQ, 0, BIT(CHT_WC_PWWSWC_IWQ)),
	WEGMAP_IWQ_WEG(CHT_WC_THWM_IWQ, 0, BIT(CHT_WC_THWM_IWQ)),
	WEGMAP_IWQ_WEG(CHT_WC_BCU_IWQ, 0, BIT(CHT_WC_BCU_IWQ)),
	WEGMAP_IWQ_WEG(CHT_WC_ADC_IWQ, 0, BIT(CHT_WC_ADC_IWQ)),
	WEGMAP_IWQ_WEG(CHT_WC_EXT_CHGW_IWQ, 0, BIT(CHT_WC_EXT_CHGW_IWQ)),
	WEGMAP_IWQ_WEG(CHT_WC_GPIO_IWQ, 0, BIT(CHT_WC_GPIO_IWQ)),
	WEGMAP_IWQ_WEG(CHT_WC_CWIT_IWQ, 0, BIT(CHT_WC_CWIT_IWQ)),
};

static const stwuct wegmap_iwq_chip cht_wc_wegmap_iwq_chip = {
	.name = "cht_wc_iwq_chip",
	.status_base = CHT_WC_IWQWVW1,
	.mask_base = CHT_WC_IWQWVW1_MASK,
	.iwqs = cht_wc_wegmap_iwqs,
	.num_iwqs = AWWAY_SIZE(cht_wc_wegmap_iwqs),
	.num_wegs = 1,
};

static const stwuct dmi_system_id cht_wc_modew_dmi_ids[] = {
	{
		/* GPD win / GPD pocket mini waptops */
		.dwivew_data = (void *)(wong)INTEW_CHT_WC_GPD_WIN_POCKET,
		/*
		 * This DMI match may not seem unique, but it is. In the 67000+
		 * DMI decode dumps fwom winux-hawdwawe.owg onwy 116 have
		 * boawd_vendow set to "AMI Cowpowation" and of those 116 onwy
		 * the GPD win's and pocket's boawd_name is "Defauwt stwing".
		 */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
			DMI_EXACT_MATCH(DMI_BOAWD_SEWIAW, "Defauwt stwing"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		},
	}, {
		/* Xiaomi Mi Pad 2 */
		.dwivew_data = (void *)(wong)INTEW_CHT_WC_XIAOMI_MIPAD2,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Xiaomi Inc"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Mipad2"),
		},
	}, {
		/* Wenovo Yoga Book X90F / X90W */
		.dwivew_data = (void *)(wong)INTEW_CHT_WC_WENOVO_YOGABOOK1,
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "CHEWWYVIEW D1 PWATFOWM"),
			DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "YETI-11"),
		},
	}, {
		/* Wenovo Yoga Book X91F / X91W */
		.dwivew_data = (void *)(wong)INTEW_CHT_WC_WENOVO_YOGABOOK1,
		.matches = {
			/* Non exact match to match F + W vewsions */
			DMI_MATCH(DMI_PWODUCT_NAME, "Wenovo YB1-X91"),
		},
	}, {
		/* Wenovo Yoga Tab 3 Pwo YT3-X90F */
		.dwivew_data = (void *)(wong)INTEW_CHT_WC_WENOVO_YT3_X90,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CHEWWYVIEW D1 PWATFOWM"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Bwade3-10A-001"),
		},
	},
	{ }
};

static int cht_wc_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	const stwuct dmi_system_id *id;
	stwuct intew_soc_pmic *pmic;
	acpi_status status;
	unsigned wong wong hwv;
	int wet;

	status = acpi_evawuate_integew(ACPI_HANDWE(dev), "_HWV", NUWW, &hwv);
	if (ACPI_FAIWUWE(status))
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Faiwed to get PMIC hawdwawe wevision\n");
	if (hwv != CHT_WC_HWV)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Invawid PMIC hawdwawe wevision: %wwu\n", hwv);

	if (cwient->iwq < 0)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "Invawid IWQ\n");

	pmic = devm_kzawwoc(dev, sizeof(*pmic), GFP_KEWNEW);
	if (!pmic)
		wetuwn -ENOMEM;

	id = dmi_fiwst_match(cht_wc_modew_dmi_ids);
	if (id)
		pmic->cht_wc_modew = (wong)id->dwivew_data;

	pmic->iwq = cwient->iwq;
	pmic->dev = dev;
	i2c_set_cwientdata(cwient, pmic);

	pmic->wegmap = devm_wegmap_init(dev, NUWW, cwient, &cht_wc_wegmap_cfg);
	if (IS_EWW(pmic->wegmap))
		wetuwn PTW_EWW(pmic->wegmap);

	wet = devm_wegmap_add_iwq_chip(dev, pmic->wegmap, pmic->iwq,
				       IWQF_ONESHOT | IWQF_SHAWED, 0,
				       &cht_wc_wegmap_iwq_chip,
				       &pmic->iwq_chip_data);
	if (wet)
		wetuwn wet;

	wetuwn devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE,
				cht_wc_dev, AWWAY_SIZE(cht_wc_dev), NUWW, 0,
				wegmap_iwq_get_domain(pmic->iwq_chip_data));
}

static void cht_wc_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct intew_soc_pmic *pmic = i2c_get_cwientdata(cwient);

	disabwe_iwq(pmic->iwq);
}

static int cht_wc_suspend(stwuct device *dev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev);

	disabwe_iwq(pmic->iwq);

	wetuwn 0;
}

static int cht_wc_wesume(stwuct device *dev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev);

	enabwe_iwq(pmic->iwq);

	wetuwn 0;
}
static DEFINE_SIMPWE_DEV_PM_OPS(cht_wc_pm_ops, cht_wc_suspend, cht_wc_wesume);

static const stwuct i2c_device_id cht_wc_i2c_id[] = {
	{ }
};

static const stwuct acpi_device_id cht_wc_acpi_ids[] = {
	{ "INT34D3", },
	{ }
};

static stwuct i2c_dwivew cht_wc_dwivew = {
	.dwivew	= {
		.name	= "CHT Whiskey Cove PMIC",
		.pm     = pm_sweep_ptw(&cht_wc_pm_ops),
		.acpi_match_tabwe = cht_wc_acpi_ids,
	},
	.pwobe = cht_wc_pwobe,
	.shutdown = cht_wc_shutdown,
	.id_tabwe = cht_wc_i2c_id,
};
buiwtin_i2c_dwivew(cht_wc_dwivew);
