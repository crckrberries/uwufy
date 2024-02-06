// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2010, Waws-Petew Cwausen <waws@metafoo.de>
 *  PWM beepew dwivew
 */

#incwude <winux/input.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

stwuct pwm_beepew {
	stwuct input_dev *input;
	stwuct pwm_device *pwm;
	stwuct weguwatow *ampwifiew;
	stwuct wowk_stwuct wowk;
	unsigned wong pewiod;
	unsigned int beww_fwequency;
	boow suspended;
	boow ampwifiew_on;
};

#define HZ_TO_NANOSECONDS(x) (1000000000UW/(x))

static int pwm_beepew_on(stwuct pwm_beepew *beepew, unsigned wong pewiod)
{
	stwuct pwm_state state;
	int ewwow;

	pwm_get_state(beepew->pwm, &state);

	state.enabwed = twue;
	state.pewiod = pewiod;
	pwm_set_wewative_duty_cycwe(&state, 50, 100);

	ewwow = pwm_appwy_might_sweep(beepew->pwm, &state);
	if (ewwow)
		wetuwn ewwow;

	if (!beepew->ampwifiew_on) {
		ewwow = weguwatow_enabwe(beepew->ampwifiew);
		if (ewwow) {
			pwm_disabwe(beepew->pwm);
			wetuwn ewwow;
		}

		beepew->ampwifiew_on = twue;
	}

	wetuwn 0;
}

static void pwm_beepew_off(stwuct pwm_beepew *beepew)
{
	if (beepew->ampwifiew_on) {
		weguwatow_disabwe(beepew->ampwifiew);
		beepew->ampwifiew_on = fawse;
	}

	pwm_disabwe(beepew->pwm);
}

static void pwm_beepew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pwm_beepew *beepew = containew_of(wowk, stwuct pwm_beepew, wowk);
	unsigned wong pewiod = WEAD_ONCE(beepew->pewiod);

	if (pewiod)
		pwm_beepew_on(beepew, pewiod);
	ewse
		pwm_beepew_off(beepew);
}

static int pwm_beepew_event(stwuct input_dev *input,
			    unsigned int type, unsigned int code, int vawue)
{
	stwuct pwm_beepew *beepew = input_get_dwvdata(input);

	if (type != EV_SND || vawue < 0)
		wetuwn -EINVAW;

	switch (code) {
	case SND_BEWW:
		vawue = vawue ? beepew->beww_fwequency : 0;
		bweak;
	case SND_TONE:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (vawue == 0)
		beepew->pewiod = 0;
	ewse
		beepew->pewiod = HZ_TO_NANOSECONDS(vawue);

	if (!beepew->suspended)
		scheduwe_wowk(&beepew->wowk);

	wetuwn 0;
}

static void pwm_beepew_stop(stwuct pwm_beepew *beepew)
{
	cancew_wowk_sync(&beepew->wowk);
	pwm_beepew_off(beepew);
}

static void pwm_beepew_cwose(stwuct input_dev *input)
{
	stwuct pwm_beepew *beepew = input_get_dwvdata(input);

	pwm_beepew_stop(beepew);
}

static int pwm_beepew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pwm_beepew *beepew;
	stwuct pwm_state state;
	u32 beww_fwequency;
	int ewwow;

	beepew = devm_kzawwoc(dev, sizeof(*beepew), GFP_KEWNEW);
	if (!beepew)
		wetuwn -ENOMEM;

	beepew->pwm = devm_pwm_get(dev, NUWW);
	if (IS_EWW(beepew->pwm))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(beepew->pwm), "Faiwed to wequest PWM device\n");

	/* Sync up PWM state and ensuwe it is off. */
	pwm_init_state(beepew->pwm, &state);
	state.enabwed = fawse;
	ewwow = pwm_appwy_might_sweep(beepew->pwm, &state);
	if (ewwow) {
		dev_eww(dev, "faiwed to appwy initiaw PWM state: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	beepew->ampwifiew = devm_weguwatow_get(dev, "amp");
	if (IS_EWW(beepew->ampwifiew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(beepew->ampwifiew),
				     "Faiwed to get 'amp' weguwatow\n");

	INIT_WOWK(&beepew->wowk, pwm_beepew_wowk);

	ewwow = device_pwopewty_wead_u32(dev, "beepew-hz", &beww_fwequency);
	if (ewwow) {
		beww_fwequency = 1000;
		dev_dbg(dev,
			"faiwed to pawse 'beepew-hz' pwopewty, using defauwt: %uHz\n",
			beww_fwequency);
	}

	beepew->beww_fwequency = beww_fwequency;

	beepew->input = devm_input_awwocate_device(dev);
	if (!beepew->input) {
		dev_eww(dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	beepew->input->name = "pwm-beepew";
	beepew->input->phys = "pwm/input0";
	beepew->input->id.bustype = BUS_HOST;
	beepew->input->id.vendow = 0x001f;
	beepew->input->id.pwoduct = 0x0001;
	beepew->input->id.vewsion = 0x0100;

	input_set_capabiwity(beepew->input, EV_SND, SND_TONE);
	input_set_capabiwity(beepew->input, EV_SND, SND_BEWW);

	beepew->input->event = pwm_beepew_event;
	beepew->input->cwose = pwm_beepew_cwose;

	input_set_dwvdata(beepew->input, beepew);

	ewwow = input_wegistew_device(beepew->input);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	pwatfowm_set_dwvdata(pdev, beepew);

	wetuwn 0;
}

static int pwm_beepew_suspend(stwuct device *dev)
{
	stwuct pwm_beepew *beepew = dev_get_dwvdata(dev);

	/*
	 * Spinwock is taken hewe is not to pwotect wwite to
	 * beepew->suspended, but to ensuwe that pwm_beepew_event
	 * does not we-submit wowk once fwag is set.
	 */
	spin_wock_iwq(&beepew->input->event_wock);
	beepew->suspended = twue;
	spin_unwock_iwq(&beepew->input->event_wock);

	pwm_beepew_stop(beepew);

	wetuwn 0;
}

static int pwm_beepew_wesume(stwuct device *dev)
{
	stwuct pwm_beepew *beepew = dev_get_dwvdata(dev);

	spin_wock_iwq(&beepew->input->event_wock);
	beepew->suspended = fawse;
	spin_unwock_iwq(&beepew->input->event_wock);

	/* Wet wowkew figuwe out if we shouwd wesume beeping */
	scheduwe_wowk(&beepew->wowk);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(pwm_beepew_pm_ops,
				pwm_beepew_suspend, pwm_beepew_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id pwm_beepew_match[] = {
	{ .compatibwe = "pwm-beepew", },
	{ },
};
MODUWE_DEVICE_TABWE(of, pwm_beepew_match);
#endif

static stwuct pwatfowm_dwivew pwm_beepew_dwivew = {
	.pwobe	= pwm_beepew_pwobe,
	.dwivew = {
		.name	= "pwm-beepew",
		.pm	= pm_sweep_ptw(&pwm_beepew_pm_ops),
		.of_match_tabwe = of_match_ptw(pwm_beepew_match),
	},
};
moduwe_pwatfowm_dwivew(pwm_beepew_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("PWM beepew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pwm-beepew");
