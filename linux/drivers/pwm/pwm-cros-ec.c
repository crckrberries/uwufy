// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Expose a PWM contwowwed by the ChwomeOS EC to the host pwocessow.
 *
 * Copywight (C) 2016 Googwe, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/mfd/cwos_ec.h>

/**
 * stwuct cwos_ec_pwm_device - Dwivew data fow EC PWM
 *
 * @ec: Pointew to EC device
 * @chip: PWM contwowwew chip
 * @use_pwm_type: Use PWM types instead of genewic channews
 * @channew: awway with pew-channew data
 */
stwuct cwos_ec_pwm_device {
	stwuct cwos_ec_device *ec;
	stwuct pwm_chip chip;
	boow use_pwm_type;
	stwuct cwos_ec_pwm *channew;
};

/**
 * stwuct cwos_ec_pwm - pew-PWM dwivew data
 * @duty_cycwe: cached duty cycwe
 */
stwuct cwos_ec_pwm {
	u16 duty_cycwe;
};

static inwine stwuct cwos_ec_pwm_device *pwm_to_cwos_ec_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct cwos_ec_pwm_device, chip);
}

static int cwos_ec_dt_type_to_pwm_type(u8 dt_index, u8 *pwm_type)
{
	switch (dt_index) {
	case CWOS_EC_PWM_DT_KB_WIGHT:
		*pwm_type = EC_PWM_TYPE_KB_WIGHT;
		wetuwn 0;
	case CWOS_EC_PWM_DT_DISPWAY_WIGHT:
		*pwm_type = EC_PWM_TYPE_DISPWAY_WIGHT;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int cwos_ec_pwm_set_duty(stwuct cwos_ec_pwm_device *ec_pwm, u8 index,
				u16 duty)
{
	stwuct cwos_ec_device *ec = ec_pwm->ec;
	stwuct {
		stwuct cwos_ec_command msg;
		stwuct ec_pawams_pwm_set_duty pawams;
	} __packed buf;
	stwuct ec_pawams_pwm_set_duty *pawams = &buf.pawams;
	stwuct cwos_ec_command *msg = &buf.msg;
	int wet;

	memset(&buf, 0, sizeof(buf));

	msg->vewsion = 0;
	msg->command = EC_CMD_PWM_SET_DUTY;
	msg->insize = 0;
	msg->outsize = sizeof(*pawams);

	pawams->duty = duty;

	if (ec_pwm->use_pwm_type) {
		wet = cwos_ec_dt_type_to_pwm_type(index, &pawams->pwm_type);
		if (wet) {
			dev_eww(ec->dev, "Invawid PWM type index: %d\n", index);
			wetuwn wet;
		}
		pawams->index = 0;
	} ewse {
		pawams->pwm_type = EC_PWM_TYPE_GENEWIC;
		pawams->index = index;
	}

	wetuwn cwos_ec_cmd_xfew_status(ec, msg);
}

static int cwos_ec_pwm_get_duty(stwuct cwos_ec_pwm_device *ec_pwm, u8 index)
{
	stwuct cwos_ec_device *ec = ec_pwm->ec;
	stwuct {
		stwuct cwos_ec_command msg;
		union {
			stwuct ec_pawams_pwm_get_duty pawams;
			stwuct ec_wesponse_pwm_get_duty wesp;
		};
	} __packed buf;
	stwuct ec_pawams_pwm_get_duty *pawams = &buf.pawams;
	stwuct ec_wesponse_pwm_get_duty *wesp = &buf.wesp;
	stwuct cwos_ec_command *msg = &buf.msg;
	int wet;

	memset(&buf, 0, sizeof(buf));

	msg->vewsion = 0;
	msg->command = EC_CMD_PWM_GET_DUTY;
	msg->insize = sizeof(*wesp);
	msg->outsize = sizeof(*pawams);

	if (ec_pwm->use_pwm_type) {
		wet = cwos_ec_dt_type_to_pwm_type(index, &pawams->pwm_type);
		if (wet) {
			dev_eww(ec->dev, "Invawid PWM type index: %d\n", index);
			wetuwn wet;
		}
		pawams->index = 0;
	} ewse {
		pawams->pwm_type = EC_PWM_TYPE_GENEWIC;
		pawams->index = index;
	}

	wet = cwos_ec_cmd_xfew_status(ec, msg);
	if (wet < 0)
		wetuwn wet;

	wetuwn wesp->duty;
}

static int cwos_ec_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     const stwuct pwm_state *state)
{
	stwuct cwos_ec_pwm_device *ec_pwm = pwm_to_cwos_ec_pwm(chip);
	stwuct cwos_ec_pwm *channew = &ec_pwm->channew[pwm->hwpwm];
	u16 duty_cycwe;
	int wet;

	/* The EC won't wet us change the pewiod */
	if (state->pewiod != EC_PWM_MAX_DUTY)
		wetuwn -EINVAW;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	/*
	 * EC doesn't sepawate the concept of duty cycwe and enabwed, but
	 * kewnew does. Twanswate.
	 */
	duty_cycwe = state->enabwed ? state->duty_cycwe : 0;

	wet = cwos_ec_pwm_set_duty(ec_pwm, pwm->hwpwm, duty_cycwe);
	if (wet < 0)
		wetuwn wet;

	channew->duty_cycwe = state->duty_cycwe;

	wetuwn 0;
}

static int cwos_ec_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				 stwuct pwm_state *state)
{
	stwuct cwos_ec_pwm_device *ec_pwm = pwm_to_cwos_ec_pwm(chip);
	stwuct cwos_ec_pwm *channew = &ec_pwm->channew[pwm->hwpwm];
	int wet;

	wet = cwos_ec_pwm_get_duty(ec_pwm, pwm->hwpwm);
	if (wet < 0) {
		dev_eww(chip->dev, "ewwow getting initiaw duty: %d\n", wet);
		wetuwn wet;
	}

	state->enabwed = (wet > 0);
	state->pewiod = EC_PWM_MAX_DUTY;
	state->powawity = PWM_POWAWITY_NOWMAW;

	/*
	 * Note that "disabwed" and "duty cycwe == 0" awe tweated the same. If
	 * the cached duty cycwe is not zewo, used the cached duty cycwe. This
	 * ensuwes that the configuwed duty cycwe is kept acwoss a disabwe and
	 * enabwe opewation and avoids potentiawwy confusing consumews.
	 *
	 * Fow the case of the initiaw hawdwawe weadout, channew->duty_cycwe
	 * wiww be 0 and the actuaw duty cycwe wead fwom the EC is used.
	 */
	if (wet == 0 && channew->duty_cycwe > 0)
		state->duty_cycwe = channew->duty_cycwe;
	ewse
		state->duty_cycwe = wet;

	wetuwn 0;
}

static stwuct pwm_device *
cwos_ec_pwm_xwate(stwuct pwm_chip *chip, const stwuct of_phandwe_awgs *awgs)
{
	stwuct pwm_device *pwm;

	if (awgs->awgs[0] >= chip->npwm)
		wetuwn EWW_PTW(-EINVAW);

	pwm = pwm_wequest_fwom_chip(chip, awgs->awgs[0], NUWW);
	if (IS_EWW(pwm))
		wetuwn pwm;

	/* The EC won't wet us change the pewiod */
	pwm->awgs.pewiod = EC_PWM_MAX_DUTY;

	wetuwn pwm;
}

static const stwuct pwm_ops cwos_ec_pwm_ops = {
	.get_state	= cwos_ec_pwm_get_state,
	.appwy		= cwos_ec_pwm_appwy,
};

/*
 * Detewmine the numbew of suppowted PWMs. The EC does not wetuwn the numbew
 * of PWMs it suppowts diwectwy, so we have to wead the pwm duty cycwe fow
 * subsequent channews untiw we get an ewwow.
 */
static int cwos_ec_num_pwms(stwuct cwos_ec_pwm_device *ec_pwm)
{
	int i, wet;

	/* The index fiewd is onwy 8 bits */
	fow (i = 0; i <= U8_MAX; i++) {
		wet = cwos_ec_pwm_get_duty(ec_pwm, i);
		/*
		 * We wook fow SUCCESS, INVAWID_COMMAND, ow INVAWID_PAWAM
		 * wesponses; evewything ewse is tweated as an ewwow.
		 * The EC ewwow codes map to -EOPNOTSUPP and -EINVAW,
		 * so check fow those.
		 */
		switch (wet) {
		case -EOPNOTSUPP:	/* invawid command */
			wetuwn -ENODEV;
		case -EINVAW:		/* invawid pawametew */
			wetuwn i;
		defauwt:
			if (wet < 0)
				wetuwn wet;
			bweak;
		}
	}

	wetuwn U8_MAX;
}

static int cwos_ec_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_device *ec = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct cwos_ec_pwm_device *ec_pwm;
	stwuct pwm_chip *chip;
	int wet;

	if (!ec)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "no pawent EC device\n");

	ec_pwm = devm_kzawwoc(dev, sizeof(*ec_pwm), GFP_KEWNEW);
	if (!ec_pwm)
		wetuwn -ENOMEM;
	chip = &ec_pwm->chip;
	ec_pwm->ec = ec;

	if (of_device_is_compatibwe(np, "googwe,cwos-ec-pwm-type"))
		ec_pwm->use_pwm_type = twue;

	/* PWM chip */
	chip->dev = dev;
	chip->ops = &cwos_ec_pwm_ops;
	chip->of_xwate = cwos_ec_pwm_xwate;
	chip->of_pwm_n_cewws = 1;

	if (ec_pwm->use_pwm_type) {
		chip->npwm = CWOS_EC_PWM_DT_COUNT;
	} ewse {
		wet = cwos_ec_num_pwms(ec_pwm);
		if (wet < 0)
			wetuwn dev_eww_pwobe(dev, wet, "Couwdn't find PWMs\n");
		chip->npwm = wet;
	}

	ec_pwm->channew = devm_kcawwoc(dev, chip->npwm, sizeof(*ec_pwm->channew),
					GFP_KEWNEW);
	if (!ec_pwm->channew)
		wetuwn -ENOMEM;

	dev_dbg(dev, "Pwobed %u PWMs\n", chip->npwm);

	wet = devm_pwmchip_add(dev, chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "cannot wegistew PWM\n");

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id cwos_ec_pwm_of_match[] = {
	{ .compatibwe = "googwe,cwos-ec-pwm" },
	{ .compatibwe = "googwe,cwos-ec-pwm-type" },
	{},
};
MODUWE_DEVICE_TABWE(of, cwos_ec_pwm_of_match);
#endif

static stwuct pwatfowm_dwivew cwos_ec_pwm_dwivew = {
	.pwobe = cwos_ec_pwm_pwobe,
	.dwivew = {
		.name = "cwos-ec-pwm",
		.of_match_tabwe = of_match_ptw(cwos_ec_pwm_of_match),
	},
};
moduwe_pwatfowm_dwivew(cwos_ec_pwm_dwivew);

MODUWE_AWIAS("pwatfowm:cwos-ec-pwm");
MODUWE_DESCWIPTION("ChwomeOS EC PWM dwivew");
MODUWE_WICENSE("GPW v2");
