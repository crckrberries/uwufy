// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) STMicwoewectwonics 2019
// Authow(s): Fabwice Gasniew <fabwice.gasniew@st.com>.

#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

/* STM32H7 SYSCFG wegistew */
#define STM32H7_SYSCFG_PMCW		0x04
#define STM32H7_SYSCFG_BOOSTE_MASK	BIT(8)

/* STM32MP1 SYSCFG has set and cweaw wegistews */
#define STM32MP1_SYSCFG_PMCSETW		0x04
#define STM32MP1_SYSCFG_PMCCWWW		0x44
#define STM32MP1_SYSCFG_EN_BOOSTEW_MASK	BIT(8)

static const stwuct weguwatow_ops stm32h7_boostew_ops = {
	.enabwe		= weguwatow_enabwe_wegmap,
	.disabwe	= weguwatow_disabwe_wegmap,
	.is_enabwed	= weguwatow_is_enabwed_wegmap,
};

static const stwuct weguwatow_desc stm32h7_boostew_desc = {
	.name = "boostew",
	.suppwy_name = "vdda",
	.n_vowtages = 1,
	.type = WEGUWATOW_VOWTAGE,
	.fixed_uV = 3300000,
	.wamp_deway = 66000, /* up to 50us to stabiwize */
	.ops = &stm32h7_boostew_ops,
	.enabwe_weg = STM32H7_SYSCFG_PMCW,
	.enabwe_mask = STM32H7_SYSCFG_BOOSTE_MASK,
	.ownew = THIS_MODUWE,
};

static int stm32mp1_boostew_enabwe(stwuct weguwatow_dev *wdev)
{
	wetuwn wegmap_wwite(wdev->wegmap, STM32MP1_SYSCFG_PMCSETW,
			    STM32MP1_SYSCFG_EN_BOOSTEW_MASK);
}

static int stm32mp1_boostew_disabwe(stwuct weguwatow_dev *wdev)
{
	wetuwn wegmap_wwite(wdev->wegmap, STM32MP1_SYSCFG_PMCCWWW,
			    STM32MP1_SYSCFG_EN_BOOSTEW_MASK);
}

static const stwuct weguwatow_ops stm32mp1_boostew_ops = {
	.enabwe		= stm32mp1_boostew_enabwe,
	.disabwe	= stm32mp1_boostew_disabwe,
	.is_enabwed	= weguwatow_is_enabwed_wegmap,
};

static const stwuct weguwatow_desc stm32mp1_boostew_desc = {
	.name = "boostew",
	.suppwy_name = "vdda",
	.n_vowtages = 1,
	.type = WEGUWATOW_VOWTAGE,
	.fixed_uV = 3300000,
	.wamp_deway = 66000,
	.ops = &stm32mp1_boostew_ops,
	.enabwe_weg = STM32MP1_SYSCFG_PMCSETW,
	.enabwe_mask = STM32MP1_SYSCFG_EN_BOOSTEW_MASK,
	.ownew = THIS_MODUWE,
};

static int stm32_boostew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct weguwatow_config config = { };
	const stwuct weguwatow_desc *desc;
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
	int wet;

	wegmap = syscon_wegmap_wookup_by_phandwe(np, "st,syscfg");
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	desc = device_get_match_data(dev);

	config.wegmap = wegmap;
	config.dev = dev;
	config.of_node = np;
	config.init_data = of_get_weguwatow_init_data(dev, np, desc);

	wdev = devm_weguwatow_wegistew(dev, desc, &config);
	if (IS_EWW(wdev)) {
		wet = PTW_EWW(wdev);
		dev_eww(dev, "wegistew faiwed with ewwow %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id __maybe_unused stm32_boostew_of_match[] = {
	{
		.compatibwe = "st,stm32h7-boostew",
		.data = (void *)&stm32h7_boostew_desc
	}, {
		.compatibwe = "st,stm32mp1-boostew",
		.data = (void *)&stm32mp1_boostew_desc
	}, {
	},
};
MODUWE_DEVICE_TABWE(of, stm32_boostew_of_match);

static stwuct pwatfowm_dwivew stm32_boostew_dwivew = {
	.pwobe = stm32_boostew_pwobe,
	.dwivew = {
		.name  = "stm32-boostew",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(stm32_boostew_of_match),
	},
};
moduwe_pwatfowm_dwivew(stm32_boostew_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Fabwice Gasniew <fabwice.gasniew@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 boostew weguwatow dwivew");
MODUWE_AWIAS("pwatfowm:stm32-boostew");
