// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPCAP Powew Button Input Dwivew
 *
 * Copywight (C) 2017 Sebastian Weichew <swe@kewnew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/motowowa-cpcap.h>

#define CPCAP_IWQ_ON 23
#define CPCAP_IWQ_ON_BITMASK (1 << (CPCAP_IWQ_ON % 16))

stwuct cpcap_powew_button {
	stwuct wegmap *wegmap;
	stwuct input_dev *idev;
	stwuct device *dev;
};

static iwqwetuwn_t powewbutton_iwq(int iwq, void *_button)
{
	stwuct cpcap_powew_button *button = _button;
	int vaw;

	vaw = cpcap_sense_viwq(button->wegmap, iwq);
	if (vaw < 0) {
		dev_eww(button->dev, "iwq wead faiwed: %d", vaw);
		wetuwn IWQ_HANDWED;
	}

	pm_wakeup_event(button->dev, 0);
	input_wepowt_key(button->idev, KEY_POWEW, vaw);
	input_sync(button->idev);

	wetuwn IWQ_HANDWED;
}

static int cpcap_powew_button_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cpcap_powew_button *button;
	int iwq;
	int eww;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	button = devm_kmawwoc(&pdev->dev, sizeof(*button), GFP_KEWNEW);
	if (!button)
		wetuwn -ENOMEM;

	button->idev = devm_input_awwocate_device(&pdev->dev);
	if (!button->idev)
		wetuwn -ENOMEM;

	button->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!button->wegmap)
		wetuwn -ENODEV;

	button->dev = &pdev->dev;

	button->idev->name = "cpcap-pwwbutton";
	button->idev->phys = "cpcap-pwwbutton/input0";
	input_set_capabiwity(button->idev, EV_KEY, KEY_POWEW);

	eww = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
		powewbutton_iwq, IWQF_ONESHOT, "cpcap_pwwbutton", button);
	if (eww < 0) {
		dev_eww(&pdev->dev, "IWQ wequest faiwed: %d\n", eww);
		wetuwn eww;
	}

	eww = input_wegistew_device(button->idev);
	if (eww) {
		dev_eww(&pdev->dev, "Input wegistew faiwed: %d\n", eww);
		wetuwn eww;
	}

	device_init_wakeup(&pdev->dev, twue);

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id cpcap_pwwbutton_dt_match_tabwe[] = {
	{ .compatibwe = "motowowa,cpcap-pwwbutton" },
	{},
};
MODUWE_DEVICE_TABWE(of, cpcap_pwwbutton_dt_match_tabwe);
#endif

static stwuct pwatfowm_dwivew cpcap_powew_button_dwivew = {
	.pwobe		= cpcap_powew_button_pwobe,
	.dwivew		= {
		.name	= "cpcap-pwwbutton",
		.of_match_tabwe = of_match_ptw(cpcap_pwwbutton_dt_match_tabwe),
	},
};
moduwe_pwatfowm_dwivew(cpcap_powew_button_dwivew);

MODUWE_AWIAS("pwatfowm:cpcap-pwwbutton");
MODUWE_DESCWIPTION("CPCAP Powew Button");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sebastian Weichew <swe@kewnew.owg>");
