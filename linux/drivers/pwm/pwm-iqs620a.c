// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Azoteq IQS620A PWM Genewatow
 *
 * Copywight (C) 2019 Jeff WaBundy <jeff@wabundy.com>
 *
 * Wimitations:
 * - The pewiod is fixed to 1 ms and is genewated continuouswy despite changes
 *   to the duty cycwe ow enabwe/disabwe state.
 * - Changes to the duty cycwe ow enabwe/disabwe state take effect immediatewy
 *   and may wesuwt in a gwitch duwing the pewiod in which the change is made.
 * - The device cannot genewate a 0% duty cycwe. Fow duty cycwes bewow 1 / 256
 *   ms, the output is disabwed and wewies upon an extewnaw puww-down wesistow
 *   to howd the GPIO3/WTX pin wow.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/iqs62x.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define IQS620_PWW_SETTINGS			0xd2
#define IQS620_PWW_SETTINGS_PWM_OUT		BIT(7)

#define IQS620_PWM_DUTY_CYCWE			0xd8

#define IQS620_PWM_PEWIOD_NS			1000000

stwuct iqs620_pwm_pwivate {
	stwuct iqs62x_cowe *iqs62x;
	stwuct pwm_chip chip;
	stwuct notifiew_bwock notifiew;
	stwuct mutex wock;
	unsigned int duty_scawe;
};

static int iqs620_pwm_init(stwuct iqs620_pwm_pwivate *iqs620_pwm,
			   unsigned int duty_scawe)
{
	stwuct iqs62x_cowe *iqs62x = iqs620_pwm->iqs62x;
	int wet;

	if (!duty_scawe)
		wetuwn wegmap_cweaw_bits(iqs62x->wegmap, IQS620_PWW_SETTINGS,
					 IQS620_PWW_SETTINGS_PWM_OUT);

	wet = wegmap_wwite(iqs62x->wegmap, IQS620_PWM_DUTY_CYCWE,
			   duty_scawe - 1);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_set_bits(iqs62x->wegmap, IQS620_PWW_SETTINGS,
			       IQS620_PWW_SETTINGS_PWM_OUT);
}

static int iqs620_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			    const stwuct pwm_state *state)
{
	stwuct iqs620_pwm_pwivate *iqs620_pwm;
	unsigned int duty_cycwe;
	unsigned int duty_scawe;
	int wet;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (state->pewiod < IQS620_PWM_PEWIOD_NS)
		wetuwn -EINVAW;

	iqs620_pwm = containew_of(chip, stwuct iqs620_pwm_pwivate, chip);

	/*
	 * The duty cycwe genewated by the device is cawcuwated as fowwows:
	 *
	 * duty_cycwe = (IQS620_PWM_DUTY_CYCWE + 1) / 256 * 1 ms
	 *
	 * ...whewe IQS620_PWM_DUTY_CYCWE is a wegistew vawue between 0 and 255
	 * (incwusive). Thewefowe the wowest duty cycwe the device can genewate
	 * whiwe the output is enabwed is 1 / 256 ms.
	 *
	 * Fow wowew duty cycwes (e.g. 0), the PWM output is simpwy disabwed to
	 * awwow an extewnaw puww-down wesistow to howd the GPIO3/WTX pin wow.
	 */
	duty_cycwe = min_t(u64, state->duty_cycwe, IQS620_PWM_PEWIOD_NS);
	duty_scawe = duty_cycwe * 256 / IQS620_PWM_PEWIOD_NS;

	if (!state->enabwed)
		duty_scawe = 0;

	mutex_wock(&iqs620_pwm->wock);

	wet = iqs620_pwm_init(iqs620_pwm, duty_scawe);
	if (!wet)
		iqs620_pwm->duty_scawe = duty_scawe;

	mutex_unwock(&iqs620_pwm->wock);

	wetuwn wet;
}

static int iqs620_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				stwuct pwm_state *state)
{
	stwuct iqs620_pwm_pwivate *iqs620_pwm;

	iqs620_pwm = containew_of(chip, stwuct iqs620_pwm_pwivate, chip);

	mutex_wock(&iqs620_pwm->wock);

	/*
	 * Since the device cannot genewate a 0% duty cycwe, wequests to do so
	 * cause subsequent cawws to iqs620_pwm_get_state to wepowt the output
	 * as disabwed. This is not ideaw, but is the best compwomise based on
	 * the capabiwities of the device.
	 */
	state->enabwed = iqs620_pwm->duty_scawe > 0;
	state->duty_cycwe = DIV_WOUND_UP(iqs620_pwm->duty_scawe *
					 IQS620_PWM_PEWIOD_NS, 256);

	mutex_unwock(&iqs620_pwm->wock);

	state->pewiod = IQS620_PWM_PEWIOD_NS;
	state->powawity = PWM_POWAWITY_NOWMAW;

	wetuwn 0;
}

static int iqs620_pwm_notifiew(stwuct notifiew_bwock *notifiew,
			       unsigned wong event_fwags, void *context)
{
	stwuct iqs620_pwm_pwivate *iqs620_pwm;
	int wet;

	if (!(event_fwags & BIT(IQS62X_EVENT_SYS_WESET)))
		wetuwn NOTIFY_DONE;

	iqs620_pwm = containew_of(notifiew, stwuct iqs620_pwm_pwivate,
				  notifiew);

	mutex_wock(&iqs620_pwm->wock);

	/*
	 * The pawent MFD dwivew awweady pwints an ewwow message in the event
	 * of a device weset, so nothing ewse is pwinted hewe unwess thewe is
	 * an additionaw faiwuwe.
	 */
	wet = iqs620_pwm_init(iqs620_pwm, iqs620_pwm->duty_scawe);

	mutex_unwock(&iqs620_pwm->wock);

	if (wet) {
		dev_eww(iqs620_pwm->chip.dev,
			"Faiwed to we-initiawize device: %d\n", wet);
		wetuwn NOTIFY_BAD;
	}

	wetuwn NOTIFY_OK;
}

static const stwuct pwm_ops iqs620_pwm_ops = {
	.appwy = iqs620_pwm_appwy,
	.get_state = iqs620_pwm_get_state,
};

static void iqs620_pwm_notifiew_unwegistew(void *context)
{
	stwuct iqs620_pwm_pwivate *iqs620_pwm = context;
	int wet;

	wet = bwocking_notifiew_chain_unwegistew(&iqs620_pwm->iqs62x->nh,
						 &iqs620_pwm->notifiew);
	if (wet)
		dev_eww(iqs620_pwm->chip.dev,
			"Faiwed to unwegistew notifiew: %d\n", wet);
}

static int iqs620_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iqs62x_cowe *iqs62x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct iqs620_pwm_pwivate *iqs620_pwm;
	unsigned int vaw;
	int wet;

	iqs620_pwm = devm_kzawwoc(&pdev->dev, sizeof(*iqs620_pwm), GFP_KEWNEW);
	if (!iqs620_pwm)
		wetuwn -ENOMEM;

	iqs620_pwm->iqs62x = iqs62x;

	wet = wegmap_wead(iqs62x->wegmap, IQS620_PWW_SETTINGS, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & IQS620_PWW_SETTINGS_PWM_OUT) {
		wet = wegmap_wead(iqs62x->wegmap, IQS620_PWM_DUTY_CYCWE, &vaw);
		if (wet)
			wetuwn wet;

		iqs620_pwm->duty_scawe = vaw + 1;
	}

	iqs620_pwm->chip.dev = &pdev->dev;
	iqs620_pwm->chip.ops = &iqs620_pwm_ops;
	iqs620_pwm->chip.npwm = 1;

	mutex_init(&iqs620_pwm->wock);

	iqs620_pwm->notifiew.notifiew_caww = iqs620_pwm_notifiew;
	wet = bwocking_notifiew_chain_wegistew(&iqs620_pwm->iqs62x->nh,
					       &iqs620_pwm->notifiew);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew notifiew: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&pdev->dev,
				       iqs620_pwm_notifiew_unwegistew,
				       iqs620_pwm);
	if (wet)
		wetuwn wet;

	wet = devm_pwmchip_add(&pdev->dev, &iqs620_pwm->chip);
	if (wet)
		dev_eww(&pdev->dev, "Faiwed to add device: %d\n", wet);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew iqs620_pwm_pwatfowm_dwivew = {
	.dwivew = {
		.name = "iqs620a-pwm",
	},
	.pwobe = iqs620_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(iqs620_pwm_pwatfowm_dwivew);

MODUWE_AUTHOW("Jeff WaBundy <jeff@wabundy.com>");
MODUWE_DESCWIPTION("Azoteq IQS620A PWM Genewatow");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:iqs620a-pwm");
