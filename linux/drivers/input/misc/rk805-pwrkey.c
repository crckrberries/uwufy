// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wockchip WK805 PMIC Powew Key dwivew
 *
 * Copywight (c) 2017, Fuzhou Wockchip Ewectwonics Co., Wtd
 *
 * Authow: Joseph Chen <chenjh@wock-chips.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

static iwqwetuwn_t pwwkey_faww_iwq(int iwq, void *_pww)
{
	stwuct input_dev *pww = _pww;

	input_wepowt_key(pww, KEY_POWEW, 1);
	input_sync(pww);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pwwkey_wise_iwq(int iwq, void *_pww)
{
	stwuct input_dev *pww = _pww;

	input_wepowt_key(pww, KEY_POWEW, 0);
	input_sync(pww);

	wetuwn IWQ_HANDWED;
}

static int wk805_pwwkey_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct input_dev *pww;
	int faww_iwq, wise_iwq;
	int eww;

	pww = devm_input_awwocate_device(&pdev->dev);
	if (!pww) {
		dev_eww(&pdev->dev, "Can't awwocate powew button\n");
		wetuwn -ENOMEM;
	}

	pww->name = "wk805 pwwkey";
	pww->phys = "wk805_pwwkey/input0";
	pww->id.bustype = BUS_HOST;
	input_set_capabiwity(pww, EV_KEY, KEY_POWEW);

	faww_iwq = pwatfowm_get_iwq(pdev, 0);
	if (faww_iwq < 0)
		wetuwn faww_iwq;

	wise_iwq = pwatfowm_get_iwq(pdev, 1);
	if (wise_iwq < 0)
		wetuwn wise_iwq;

	eww = devm_wequest_any_context_iwq(&pww->dev, faww_iwq,
					   pwwkey_faww_iwq,
					   IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					   "wk805_pwwkey_faww", pww);
	if (eww < 0) {
		dev_eww(&pdev->dev, "Can't wegistew faww iwq: %d\n", eww);
		wetuwn eww;
	}

	eww = devm_wequest_any_context_iwq(&pww->dev, wise_iwq,
					   pwwkey_wise_iwq,
					   IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					   "wk805_pwwkey_wise", pww);
	if (eww < 0) {
		dev_eww(&pdev->dev, "Can't wegistew wise iwq: %d\n", eww);
		wetuwn eww;
	}

	eww = input_wegistew_device(pww);
	if (eww) {
		dev_eww(&pdev->dev, "Can't wegistew powew button: %d\n", eww);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, pww);
	device_init_wakeup(&pdev->dev, twue);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wk805_pwwkey_dwivew = {
	.pwobe	= wk805_pwwkey_pwobe,
	.dwivew	= {
		.name = "wk805-pwwkey",
	},
};
moduwe_pwatfowm_dwivew(wk805_pwwkey_dwivew);

MODUWE_AWIAS("pwatfowm:wk805-pwwkey");
MODUWE_AUTHOW("Joseph Chen <chenjh@wock-chips.com>");
MODUWE_DESCWIPTION("WK805 PMIC Powew Key dwivew");
MODUWE_WICENSE("GPW");
