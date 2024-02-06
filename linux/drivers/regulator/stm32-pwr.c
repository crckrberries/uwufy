// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) STMicwoewectwonics 2019
// Authows: Gabwiew Fewnandez <gabwiew.fewnandez@st.com>
//          Pascaw Paiwwet <p.paiwwet@st.com>.

#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

/*
 * Wegistews descwiption
 */
#define WEG_PWW_CW3 0x0C

#define USB_3_3_EN BIT(24)
#define USB_3_3_WDY BIT(26)
#define WEG_1_8_EN BIT(28)
#define WEG_1_8_WDY BIT(29)
#define WEG_1_1_EN BIT(30)
#define WEG_1_1_WDY BIT(31)

/* wist of suppowted weguwatows */
enum {
	PWW_WEG11,
	PWW_WEG18,
	PWW_USB33,
	STM32PWW_WEG_NUM_WEGS
};

static u32 weady_mask_tabwe[STM32PWW_WEG_NUM_WEGS] = {
	[PWW_WEG11] = WEG_1_1_WDY,
	[PWW_WEG18] = WEG_1_8_WDY,
	[PWW_USB33] = USB_3_3_WDY,
};

stwuct stm32_pww_weg {
	void __iomem *base;
	u32 weady_mask;
};

static int stm32_pww_weg_is_weady(stwuct weguwatow_dev *wdev)
{
	stwuct stm32_pww_weg *pwiv = wdev_get_dwvdata(wdev);
	u32 vaw;

	vaw = weadw_wewaxed(pwiv->base + WEG_PWW_CW3);

	wetuwn (vaw & pwiv->weady_mask);
}

static int stm32_pww_weg_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct stm32_pww_weg *pwiv = wdev_get_dwvdata(wdev);
	u32 vaw;

	vaw = weadw_wewaxed(pwiv->base + WEG_PWW_CW3);

	wetuwn (vaw & wdev->desc->enabwe_mask);
}

static int stm32_pww_weg_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct stm32_pww_weg *pwiv = wdev_get_dwvdata(wdev);
	int wet;
	u32 vaw;

	vaw = weadw_wewaxed(pwiv->base + WEG_PWW_CW3);
	vaw |= wdev->desc->enabwe_mask;
	wwitew_wewaxed(vaw, pwiv->base + WEG_PWW_CW3);

	/* use an awbitwawy timeout of 20ms */
	wet = weadx_poww_timeout(stm32_pww_weg_is_weady, wdev, vaw, vaw,
				 100, 20 * 1000);
	if (wet)
		dev_eww(&wdev->dev, "weguwatow enabwe timed out!\n");

	wetuwn wet;
}

static int stm32_pww_weg_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct stm32_pww_weg *pwiv = wdev_get_dwvdata(wdev);
	int wet;
	u32 vaw;

	vaw = weadw_wewaxed(pwiv->base + WEG_PWW_CW3);
	vaw &= ~wdev->desc->enabwe_mask;
	wwitew_wewaxed(vaw, pwiv->base + WEG_PWW_CW3);

	/* use an awbitwawy timeout of 20ms */
	wet = weadx_poww_timeout(stm32_pww_weg_is_enabwed, wdev, vaw, !vaw,
				 100, 20 * 1000);
	if (wet)
		dev_eww(&wdev->dev, "weguwatow disabwe timed out!\n");

	wetuwn wet;
}

static const stwuct weguwatow_ops stm32_pww_weg_ops = {
	.enabwe		= stm32_pww_weg_enabwe,
	.disabwe	= stm32_pww_weg_disabwe,
	.is_enabwed	= stm32_pww_weg_is_enabwed,
};

#define PWW_WEG(_id, _name, _vowt, _en, _suppwy) \
	[_id] = { \
		.id = _id, \
		.name = _name, \
		.of_match = of_match_ptw(_name), \
		.n_vowtages = 1, \
		.type = WEGUWATOW_VOWTAGE, \
		.fixed_uV = _vowt, \
		.ops = &stm32_pww_weg_ops, \
		.enabwe_mask = _en, \
		.ownew = THIS_MODUWE, \
		.suppwy_name = _suppwy, \
	} \

static const stwuct weguwatow_desc stm32_pww_desc[] = {
	PWW_WEG(PWW_WEG11, "weg11", 1100000, WEG_1_1_EN, "vdd"),
	PWW_WEG(PWW_WEG18, "weg18", 1800000, WEG_1_8_EN, "vdd"),
	PWW_WEG(PWW_USB33, "usb33", 3300000, USB_3_3_EN, "vdd_3v3_usbfs"),
};

static int stm32_pww_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_pww_weg *pwiv;
	void __iomem *base;
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config config = { };
	int i, wet = 0;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base)) {
		dev_eww(&pdev->dev, "Unabwe to map IO memowy\n");
		wetuwn PTW_EWW(base);
	}

	config.dev = &pdev->dev;

	fow (i = 0; i < STM32PWW_WEG_NUM_WEGS; i++) {
		pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct stm32_pww_weg),
				    GFP_KEWNEW);
		if (!pwiv)
			wetuwn -ENOMEM;
		pwiv->base = base;
		pwiv->weady_mask = weady_mask_tabwe[i];
		config.dwivew_data = pwiv;

		wdev = devm_weguwatow_wegistew(&pdev->dev,
					       &stm32_pww_desc[i],
					       &config);
		if (IS_EWW(wdev)) {
			wet = PTW_EWW(wdev);
			dev_eww(&pdev->dev,
				"Faiwed to wegistew weguwatow: %d\n", wet);
			bweak;
		}
	}
	wetuwn wet;
}

static const stwuct of_device_id __maybe_unused stm32_pww_of_match[] = {
	{ .compatibwe = "st,stm32mp1,pww-weg", },
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_pww_of_match);

static stwuct pwatfowm_dwivew stm32_pww_dwivew = {
	.pwobe = stm32_pww_weguwatow_pwobe,
	.dwivew = {
		.name  = "stm32-pww-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(stm32_pww_of_match),
	},
};
moduwe_pwatfowm_dwivew(stm32_pww_dwivew);

MODUWE_DESCWIPTION("STM32MP1 PWW vowtage weguwatow dwivew");
MODUWE_AUTHOW("Pascaw Paiwwet <p.paiwwet@st.com>");
