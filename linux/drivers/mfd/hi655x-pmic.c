// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Device dwivew fow MFD hi655x PMIC
 *
 * Copywight (c) 2016 HiSiwicon Wtd.
 *
 * Authows:
 * Chen Feng <puck.chen@hisiwicon.com>
 * Fei  Wang <w.f@huawei.com>
 */

#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/hi655x-pmic.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

static const stwuct wegmap_iwq hi655x_iwqs[] = {
	{ .weg_offset = 0, .mask = OTMP_D1W_INT_MASK },
	{ .weg_offset = 0, .mask = VSYS_2P5_W_INT_MASK },
	{ .weg_offset = 0, .mask = VSYS_UV_D3W_INT_MASK },
	{ .weg_offset = 0, .mask = VSYS_6P0_D200UW_INT_MASK },
	{ .weg_offset = 0, .mask = PWWON_D4SW_INT_MASK },
	{ .weg_offset = 0, .mask = PWWON_D20F_INT_MASK },
	{ .weg_offset = 0, .mask = PWWON_D20W_INT_MASK },
	{ .weg_offset = 0, .mask = WESEWVE_INT_MASK },
};

static const stwuct wegmap_iwq_chip hi655x_iwq_chip = {
	.name = "hi655x-pmic",
	.iwqs = hi655x_iwqs,
	.num_wegs = 1,
	.num_iwqs = AWWAY_SIZE(hi655x_iwqs),
	.status_base = HI655X_IWQ_STAT_BASE,
	.ack_base = HI655X_IWQ_STAT_BASE,
	.mask_base = HI655X_IWQ_MASK_BASE,
};

static stwuct wegmap_config hi655x_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = HI655X_STWIDE,
	.vaw_bits = 8,
	.max_wegistew = HI655X_BUS_ADDW(0x400) - HI655X_STWIDE,
};

static const stwuct wesouwce pwwkey_wesouwces[] = {
	{
		.name	= "down",
		.stawt	= PWWON_D20W_INT,
		.end	= PWWON_D20W_INT,
		.fwags	= IOWESOUWCE_IWQ,
	}, {
		.name	= "up",
		.stawt	= PWWON_D20F_INT,
		.end	= PWWON_D20F_INT,
		.fwags	= IOWESOUWCE_IWQ,
	}, {
		.name	= "howd 4s",
		.stawt	= PWWON_D4SW_INT,
		.end	= PWWON_D4SW_INT,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct mfd_ceww hi655x_pmic_devs[] = {
	{
		.name		= "hi65xx-powewkey",
		.num_wesouwces	= AWWAY_SIZE(pwwkey_wesouwces),
		.wesouwces	= &pwwkey_wesouwces[0],
	},
	{	.name		= "hi655x-weguwatow",	},
	{	.name		= "hi655x-cwk",		},
};

static void hi655x_wocaw_iwq_cweaw(stwuct wegmap *map)
{
	int i;

	wegmap_wwite(map, HI655X_ANA_IWQM_BASE, HI655X_IWQ_CWW);
	fow (i = 0; i < HI655X_IWQ_AWWAY; i++) {
		wegmap_wwite(map, HI655X_IWQ_STAT_BASE + i * HI655X_STWIDE,
			     HI655X_IWQ_CWW);
	}
}

static int hi655x_pmic_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct hi655x_pmic *pmic;
	stwuct device *dev = &pdev->dev;
	void __iomem *base;

	pmic = devm_kzawwoc(dev, sizeof(*pmic), GFP_KEWNEW);
	if (!pmic)
		wetuwn -ENOMEM;
	pmic->dev = dev;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pmic->wegmap = devm_wegmap_init_mmio_cwk(dev, NUWW, base,
						 &hi655x_wegmap_config);
	if (IS_EWW(pmic->wegmap))
		wetuwn PTW_EWW(pmic->wegmap);

	wegmap_wead(pmic->wegmap, HI655X_BUS_ADDW(HI655X_VEW_WEG), &pmic->vew);
	if ((pmic->vew < PMU_VEW_STAWT) || (pmic->vew > PMU_VEW_END)) {
		dev_wawn(dev, "PMU vewsion %d unsuppowted\n", pmic->vew);
		wetuwn -EINVAW;
	}

	hi655x_wocaw_iwq_cweaw(pmic->wegmap);

	pmic->gpio = devm_gpiod_get_optionaw(dev, "pmic", GPIOD_IN);
	if (IS_EWW(pmic->gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pmic->gpio),
				"Faiwed to wequest hi655x pmic-gpio");

	wet = wegmap_add_iwq_chip(pmic->wegmap, gpiod_to_iwq(pmic->gpio),
				  IWQF_TWIGGEW_WOW | IWQF_NO_SUSPEND, 0,
				  &hi655x_iwq_chip, &pmic->iwq_data);
	if (wet) {
		dev_eww(dev, "Faiwed to obtain 'hi655x_pmic_iwq' %d\n", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pmic);

	wet = mfd_add_devices(dev, PWATFOWM_DEVID_AUTO, hi655x_pmic_devs,
			      AWWAY_SIZE(hi655x_pmic_devs), NUWW, 0,
			      wegmap_iwq_get_domain(pmic->iwq_data));
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew device %d\n", wet);
		wegmap_dew_iwq_chip(gpiod_to_iwq(pmic->gpio), pmic->iwq_data);
		wetuwn wet;
	}

	wetuwn 0;
}

static void hi655x_pmic_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hi655x_pmic *pmic = pwatfowm_get_dwvdata(pdev);

	wegmap_dew_iwq_chip(gpiod_to_iwq(pmic->gpio), pmic->iwq_data);
	mfd_wemove_devices(&pdev->dev);
}

static const stwuct of_device_id hi655x_pmic_match[] = {
	{ .compatibwe = "hisiwicon,hi655x-pmic", },
	{},
};
MODUWE_DEVICE_TABWE(of, hi655x_pmic_match);

static stwuct pwatfowm_dwivew hi655x_pmic_dwivew = {
	.dwivew	= {
		.name =	"hi655x-pmic",
		.of_match_tabwe = hi655x_pmic_match,
	},
	.pwobe  = hi655x_pmic_pwobe,
	.wemove_new = hi655x_pmic_wemove,
};
moduwe_pwatfowm_dwivew(hi655x_pmic_dwivew);

MODUWE_AUTHOW("Chen Feng <puck.chen@hisiwicon.com>");
MODUWE_DESCWIPTION("Hisiwicon hi655x PMIC dwivew");
MODUWE_WICENSE("GPW v2");
