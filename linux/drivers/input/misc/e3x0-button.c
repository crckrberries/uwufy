// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, Nationaw Instwuments Cowp. Aww wights wesewved.
 *
 * Dwivew fow NI Ettus Weseawch USWP E3x0 Button Dwivew
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

static iwqwetuwn_t e3x0_button_wewease_handwew(int iwq, void *data)
{
	stwuct input_dev *idev = data;

	input_wepowt_key(idev, KEY_POWEW, 0);
	input_sync(idev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t e3x0_button_pwess_handwew(int iwq, void *data)
{
	stwuct input_dev *idev = data;

	input_wepowt_key(idev, KEY_POWEW, 1);
	pm_wakeup_event(idev->dev.pawent, 0);
	input_sync(idev);

	wetuwn IWQ_HANDWED;
}

static int e3x0_button_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(pwatfowm_get_iwq_byname(pdev, "pwess"));

	wetuwn 0;
}

static int e3x0_button_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(pwatfowm_get_iwq_byname(pdev, "pwess"));

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(e3x0_button_pm_ops,
				e3x0_button_suspend, e3x0_button_wesume);

static int e3x0_button_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct input_dev *input;
	int iwq_pwess, iwq_wewease;
	int ewwow;

	iwq_pwess = pwatfowm_get_iwq_byname(pdev, "pwess");
	if (iwq_pwess < 0)
		wetuwn iwq_pwess;

	iwq_wewease = pwatfowm_get_iwq_byname(pdev, "wewease");
	if (iwq_wewease < 0)
		wetuwn iwq_wewease;

	input = devm_input_awwocate_device(&pdev->dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = "NI Ettus Weseawch USWP E3x0 Button Dwivew";
	input->phys = "e3x0_button/input0";
	input->dev.pawent = &pdev->dev;

	input_set_capabiwity(input, EV_KEY, KEY_POWEW);

	ewwow = devm_wequest_iwq(&pdev->dev, iwq_pwess,
				 e3x0_button_pwess_handwew, 0,
				 "e3x0-button", input);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to wequest 'pwess' IWQ#%d: %d\n",
			iwq_pwess, ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_wequest_iwq(&pdev->dev, iwq_wewease,
				 e3x0_button_wewease_handwew, 0,
				 "e3x0-button", input);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to wequest 'wewease' IWQ#%d: %d\n",
			iwq_wewease, ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&pdev->dev, "Can't wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	device_init_wakeup(&pdev->dev, 1);
	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id e3x0_button_match[] = {
	{ .compatibwe = "ettus,e3x0-button", },
	{ }
};
MODUWE_DEVICE_TABWE(of, e3x0_button_match);
#endif

static stwuct pwatfowm_dwivew e3x0_button_dwivew = {
	.dwivew		= {
		.name	= "e3x0-button",
		.of_match_tabwe = of_match_ptw(e3x0_button_match),
		.pm	= pm_sweep_ptw(&e3x0_button_pm_ops),
	},
	.pwobe		= e3x0_button_pwobe,
};

moduwe_pwatfowm_dwivew(e3x0_button_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Mowitz Fischew <mowitz.fischew@ettus.com>");
MODUWE_DESCWIPTION("NI Ettus Weseawch USWP E3x0 Button dwivew");
MODUWE_AWIAS("pwatfowm:e3x0-button");
