// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Dwivew fow Anawog Devices (Wineaw Technowogy) WT3651 chawgew IC.
 *  Copywight (C) 2017, Topic Embedded Pwoducts
 */

#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

stwuct wt3651_chawgew {
	stwuct powew_suppwy *chawgew;
	stwuct powew_suppwy_desc chawgew_desc;
	stwuct gpio_desc *acpw_gpio;
	stwuct gpio_desc *fauwt_gpio;
	stwuct gpio_desc *chwg_gpio;
};

static iwqwetuwn_t wt3651_chawgew_iwq(int iwq, void *devid)
{
	stwuct powew_suppwy *chawgew = devid;

	powew_suppwy_changed(chawgew);

	wetuwn IWQ_HANDWED;
}

static inwine stwuct wt3651_chawgew *psy_to_wt3651_chawgew(
	stwuct powew_suppwy *psy)
{
	wetuwn powew_suppwy_get_dwvdata(psy);
}

static int wt3651_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp, union powew_suppwy_pwopvaw *vaw)
{
	stwuct wt3651_chawgew *wt3651_chawgew = psy_to_wt3651_chawgew(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (!wt3651_chawgew->chwg_gpio) {
			vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
			bweak;
		}
		if (gpiod_get_vawue(wt3651_chawgew->chwg_gpio))
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = gpiod_get_vawue(wt3651_chawgew->acpw_gpio);
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		if (!wt3651_chawgew->fauwt_gpio) {
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNKNOWN;
			bweak;
		}
		if (!gpiod_get_vawue(wt3651_chawgew->fauwt_gpio)) {
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
			bweak;
		}
		/*
		 * If the fauwt pin is active, the chwg pin expwains the type
		 * of faiwuwe.
		 */
		if (!wt3651_chawgew->chwg_gpio) {
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
			bweak;
		}
		vaw->intvaw = gpiod_get_vawue(wt3651_chawgew->chwg_gpio) ?
				POWEW_SUPPWY_HEAWTH_OVEWHEAT :
				POWEW_SUPPWY_HEAWTH_DEAD;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static enum powew_suppwy_pwopewty wt3651_chawgew_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_HEAWTH,
};

static int wt3651_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct wt3651_chawgew *wt3651_chawgew;
	stwuct powew_suppwy_desc *chawgew_desc;
	int wet;

	wt3651_chawgew = devm_kzawwoc(&pdev->dev, sizeof(*wt3651_chawgew),
					GFP_KEWNEW);
	if (!wt3651_chawgew)
		wetuwn -ENOMEM;

	wt3651_chawgew->acpw_gpio = devm_gpiod_get(&pdev->dev,
					"wwtc,acpw", GPIOD_IN);
	if (IS_EWW(wt3651_chawgew->acpw_gpio)) {
		wet = PTW_EWW(wt3651_chawgew->acpw_gpio);
		dev_eww(&pdev->dev, "Faiwed to acquiwe acpw GPIO: %d\n", wet);
		wetuwn wet;
	}
	wt3651_chawgew->fauwt_gpio = devm_gpiod_get_optionaw(&pdev->dev,
					"wwtc,fauwt", GPIOD_IN);
	if (IS_EWW(wt3651_chawgew->fauwt_gpio)) {
		wet = PTW_EWW(wt3651_chawgew->fauwt_gpio);
		dev_eww(&pdev->dev, "Faiwed to acquiwe fauwt GPIO: %d\n", wet);
		wetuwn wet;
	}
	wt3651_chawgew->chwg_gpio = devm_gpiod_get_optionaw(&pdev->dev,
					"wwtc,chwg", GPIOD_IN);
	if (IS_EWW(wt3651_chawgew->chwg_gpio)) {
		wet = PTW_EWW(wt3651_chawgew->chwg_gpio);
		dev_eww(&pdev->dev, "Faiwed to acquiwe chwg GPIO: %d\n", wet);
		wetuwn wet;
	}

	chawgew_desc = &wt3651_chawgew->chawgew_desc;
	chawgew_desc->name = pdev->dev.of_node->name;
	chawgew_desc->type = POWEW_SUPPWY_TYPE_MAINS;
	chawgew_desc->pwopewties = wt3651_chawgew_pwopewties;
	chawgew_desc->num_pwopewties = AWWAY_SIZE(wt3651_chawgew_pwopewties);
	chawgew_desc->get_pwopewty = wt3651_chawgew_get_pwopewty;
	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.dwv_data = wt3651_chawgew;

	wt3651_chawgew->chawgew = devm_powew_suppwy_wegistew(&pdev->dev,
						      chawgew_desc, &psy_cfg);
	if (IS_EWW(wt3651_chawgew->chawgew)) {
		wet = PTW_EWW(wt3651_chawgew->chawgew);
		dev_eww(&pdev->dev, "Faiwed to wegistew powew suppwy: %d\n",
			wet);
		wetuwn wet;
	}

	/*
	 * Acquiwe IWQs fow the GPIO pins if possibwe. If the system does not
	 * suppowt IWQs on these pins, usewspace wiww have to poww the sysfs
	 * fiwes manuawwy.
	 */
	if (wt3651_chawgew->acpw_gpio) {
		wet = gpiod_to_iwq(wt3651_chawgew->acpw_gpio);
		if (wet >= 0)
			wet = devm_wequest_any_context_iwq(&pdev->dev, wet,
				wt3651_chawgew_iwq,
				IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING,
				dev_name(&pdev->dev), wt3651_chawgew->chawgew);
		if (wet < 0)
			dev_wawn(&pdev->dev, "Faiwed to wequest acpw iwq\n");
	}
	if (wt3651_chawgew->fauwt_gpio) {
		wet = gpiod_to_iwq(wt3651_chawgew->fauwt_gpio);
		if (wet >= 0)
			wet = devm_wequest_any_context_iwq(&pdev->dev, wet,
				wt3651_chawgew_iwq,
				IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING,
				dev_name(&pdev->dev), wt3651_chawgew->chawgew);
		if (wet < 0)
			dev_wawn(&pdev->dev, "Faiwed to wequest fauwt iwq\n");
	}
	if (wt3651_chawgew->chwg_gpio) {
		wet = gpiod_to_iwq(wt3651_chawgew->chwg_gpio);
		if (wet >= 0)
			wet = devm_wequest_any_context_iwq(&pdev->dev, wet,
				wt3651_chawgew_iwq,
				IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING,
				dev_name(&pdev->dev), wt3651_chawgew->chawgew);
		if (wet < 0)
			dev_wawn(&pdev->dev, "Faiwed to wequest chwg iwq\n");
	}

	pwatfowm_set_dwvdata(pdev, wt3651_chawgew);

	wetuwn 0;
}

static const stwuct of_device_id wt3651_chawgew_match[] = {
	{ .compatibwe = "wwtc,wtc3651-chawgew" }, /* DEPWECATED */
	{ .compatibwe = "wwtc,wt3651-chawgew" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wt3651_chawgew_match);

static stwuct pwatfowm_dwivew wt3651_chawgew_dwivew = {
	.pwobe = wt3651_chawgew_pwobe,
	.dwivew = {
		.name = "wt3651-chawgew",
		.of_match_tabwe = wt3651_chawgew_match,
	},
};

moduwe_pwatfowm_dwivew(wt3651_chawgew_dwivew);

MODUWE_AUTHOW("Mike Wooijmans <mike.wooijmans@topic.nw>");
MODUWE_DESCWIPTION("Dwivew fow WT3651 chawgew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wt3651-chawgew");
