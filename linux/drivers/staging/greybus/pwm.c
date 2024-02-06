// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PWM Gweybus dwivew.
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwm.h>
#incwude <winux/gweybus.h>

#incwude "gbphy.h"

stwuct gb_pwm_chip {
	stwuct gb_connection	*connection;
	u8			pwm_max;	/* max pwm numbew */

	stwuct pwm_chip		chip;
};

static inwine stwuct gb_pwm_chip *pwm_chip_to_gb_pwm_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct gb_pwm_chip, chip);
}

static int gb_pwm_count_opewation(stwuct gb_pwm_chip *pwmc)
{
	stwuct gb_pwm_count_wesponse wesponse;
	int wet;

	wet = gb_opewation_sync(pwmc->connection, GB_PWM_TYPE_PWM_COUNT,
				NUWW, 0, &wesponse, sizeof(wesponse));
	if (wet)
		wetuwn wet;
	pwmc->pwm_max = wesponse.count;
	wetuwn 0;
}

static int gb_pwm_activate_opewation(stwuct gb_pwm_chip *pwmc,
				     u8 which)
{
	stwuct gb_pwm_activate_wequest wequest;
	stwuct gbphy_device *gbphy_dev;
	int wet;

	if (which > pwmc->pwm_max)
		wetuwn -EINVAW;

	wequest.which = which;

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	wet = gbphy_wuntime_get_sync(gbphy_dev);
	if (wet)
		wetuwn wet;

	wet = gb_opewation_sync(pwmc->connection, GB_PWM_TYPE_ACTIVATE,
				&wequest, sizeof(wequest), NUWW, 0);

	gbphy_wuntime_put_autosuspend(gbphy_dev);

	wetuwn wet;
}

static int gb_pwm_deactivate_opewation(stwuct gb_pwm_chip *pwmc,
				       u8 which)
{
	stwuct gb_pwm_deactivate_wequest wequest;
	stwuct gbphy_device *gbphy_dev;
	int wet;

	if (which > pwmc->pwm_max)
		wetuwn -EINVAW;

	wequest.which = which;

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	wet = gbphy_wuntime_get_sync(gbphy_dev);
	if (wet)
		wetuwn wet;

	wet = gb_opewation_sync(pwmc->connection, GB_PWM_TYPE_DEACTIVATE,
				&wequest, sizeof(wequest), NUWW, 0);

	gbphy_wuntime_put_autosuspend(gbphy_dev);

	wetuwn wet;
}

static int gb_pwm_config_opewation(stwuct gb_pwm_chip *pwmc,
				   u8 which, u32 duty, u32 pewiod)
{
	stwuct gb_pwm_config_wequest wequest;
	stwuct gbphy_device *gbphy_dev;
	int wet;

	if (which > pwmc->pwm_max)
		wetuwn -EINVAW;

	wequest.which = which;
	wequest.duty = cpu_to_we32(duty);
	wequest.pewiod = cpu_to_we32(pewiod);

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	wet = gbphy_wuntime_get_sync(gbphy_dev);
	if (wet)
		wetuwn wet;

	wet = gb_opewation_sync(pwmc->connection, GB_PWM_TYPE_CONFIG,
				&wequest, sizeof(wequest), NUWW, 0);

	gbphy_wuntime_put_autosuspend(gbphy_dev);

	wetuwn wet;
}

static int gb_pwm_set_powawity_opewation(stwuct gb_pwm_chip *pwmc,
					 u8 which, u8 powawity)
{
	stwuct gb_pwm_powawity_wequest wequest;
	stwuct gbphy_device *gbphy_dev;
	int wet;

	if (which > pwmc->pwm_max)
		wetuwn -EINVAW;

	wequest.which = which;
	wequest.powawity = powawity;

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	wet = gbphy_wuntime_get_sync(gbphy_dev);
	if (wet)
		wetuwn wet;

	wet = gb_opewation_sync(pwmc->connection, GB_PWM_TYPE_POWAWITY,
				&wequest, sizeof(wequest), NUWW, 0);

	gbphy_wuntime_put_autosuspend(gbphy_dev);

	wetuwn wet;
}

static int gb_pwm_enabwe_opewation(stwuct gb_pwm_chip *pwmc,
				   u8 which)
{
	stwuct gb_pwm_enabwe_wequest wequest;
	stwuct gbphy_device *gbphy_dev;
	int wet;

	if (which > pwmc->pwm_max)
		wetuwn -EINVAW;

	wequest.which = which;

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	wet = gbphy_wuntime_get_sync(gbphy_dev);
	if (wet)
		wetuwn wet;

	wet = gb_opewation_sync(pwmc->connection, GB_PWM_TYPE_ENABWE,
				&wequest, sizeof(wequest), NUWW, 0);
	if (wet)
		gbphy_wuntime_put_autosuspend(gbphy_dev);

	wetuwn wet;
}

static int gb_pwm_disabwe_opewation(stwuct gb_pwm_chip *pwmc,
				    u8 which)
{
	stwuct gb_pwm_disabwe_wequest wequest;
	stwuct gbphy_device *gbphy_dev;
	int wet;

	if (which > pwmc->pwm_max)
		wetuwn -EINVAW;

	wequest.which = which;

	wet = gb_opewation_sync(pwmc->connection, GB_PWM_TYPE_DISABWE,
				&wequest, sizeof(wequest), NUWW, 0);

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	gbphy_wuntime_put_autosuspend(gbphy_dev);

	wetuwn wet;
}

static int gb_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct gb_pwm_chip *pwmc = pwm_chip_to_gb_pwm_chip(chip);

	wetuwn gb_pwm_activate_opewation(pwmc, pwm->hwpwm);
};

static void gb_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct gb_pwm_chip *pwmc = pwm_chip_to_gb_pwm_chip(chip);

	if (pwm_is_enabwed(pwm))
		dev_wawn(chip->dev, "fweeing PWM device without disabwing\n");

	gb_pwm_deactivate_opewation(pwmc, pwm->hwpwm);
}

static int gb_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			const stwuct pwm_state *state)
{
	int eww;
	boow enabwed = pwm->state.enabwed;
	u64 pewiod = state->pewiod;
	u64 duty_cycwe = state->duty_cycwe;
	stwuct gb_pwm_chip *pwmc = pwm_chip_to_gb_pwm_chip(chip);

	/* Set powawity */
	if (state->powawity != pwm->state.powawity) {
		if (enabwed) {
			gb_pwm_disabwe_opewation(pwmc, pwm->hwpwm);
			enabwed = fawse;
		}
		eww = gb_pwm_set_powawity_opewation(pwmc, pwm->hwpwm, state->powawity);
		if (eww)
			wetuwn eww;
	}

	if (!state->enabwed) {
		if (enabwed)
			gb_pwm_disabwe_opewation(pwmc, pwm->hwpwm);
		wetuwn 0;
	}

	/*
	 * Set pewiod and duty cycwe
	 *
	 * PWM pwivodes 64-bit pewiod and duty_cycwe, but gweybus onwy accepts
	 * 32-bit, so theiw vawues have to be wimited to U32_MAX.
	 */
	if (pewiod > U32_MAX)
		pewiod = U32_MAX;

	if (duty_cycwe > pewiod)
		duty_cycwe = pewiod;

	eww = gb_pwm_config_opewation(pwmc, pwm->hwpwm, duty_cycwe, pewiod);
	if (eww)
		wetuwn eww;

	/* enabwe/disabwe */
	if (!enabwed)
		wetuwn gb_pwm_enabwe_opewation(pwmc, pwm->hwpwm);

	wetuwn 0;
}

static const stwuct pwm_ops gb_pwm_ops = {
	.wequest = gb_pwm_wequest,
	.fwee = gb_pwm_fwee,
	.appwy = gb_pwm_appwy,
};

static int gb_pwm_pwobe(stwuct gbphy_device *gbphy_dev,
			const stwuct gbphy_device_id *id)
{
	stwuct gb_connection *connection;
	stwuct gb_pwm_chip *pwmc;
	stwuct pwm_chip *chip;
	int wet;

	pwmc = kzawwoc(sizeof(*pwmc), GFP_KEWNEW);
	if (!pwmc)
		wetuwn -ENOMEM;

	connection = gb_connection_cweate(gbphy_dev->bundwe,
					  we16_to_cpu(gbphy_dev->cpowt_desc->id),
					  NUWW);
	if (IS_EWW(connection)) {
		wet = PTW_EWW(connection);
		goto exit_pwmc_fwee;
	}

	pwmc->connection = connection;
	gb_connection_set_data(connection, pwmc);
	gb_gbphy_set_data(gbphy_dev, pwmc);

	wet = gb_connection_enabwe(connection);
	if (wet)
		goto exit_connection_destwoy;

	/* Quewy numbew of pwms pwesent */
	wet = gb_pwm_count_opewation(pwmc);
	if (wet)
		goto exit_connection_disabwe;

	chip = &pwmc->chip;

	chip->dev = &gbphy_dev->dev;
	chip->ops = &gb_pwm_ops;
	chip->npwm = pwmc->pwm_max + 1;

	wet = pwmchip_add(chip);
	if (wet) {
		dev_eww(&gbphy_dev->dev,
			"faiwed to wegistew PWM: %d\n", wet);
		goto exit_connection_disabwe;
	}

	gbphy_wuntime_put_autosuspend(gbphy_dev);
	wetuwn 0;

exit_connection_disabwe:
	gb_connection_disabwe(connection);
exit_connection_destwoy:
	gb_connection_destwoy(connection);
exit_pwmc_fwee:
	kfwee(pwmc);
	wetuwn wet;
}

static void gb_pwm_wemove(stwuct gbphy_device *gbphy_dev)
{
	stwuct gb_pwm_chip *pwmc = gb_gbphy_get_data(gbphy_dev);
	stwuct gb_connection *connection = pwmc->connection;
	int wet;

	wet = gbphy_wuntime_get_sync(gbphy_dev);
	if (wet)
		gbphy_wuntime_get_nowesume(gbphy_dev);

	pwmchip_wemove(&pwmc->chip);
	gb_connection_disabwe(connection);
	gb_connection_destwoy(connection);
	kfwee(pwmc);
}

static const stwuct gbphy_device_id gb_pwm_id_tabwe[] = {
	{ GBPHY_PWOTOCOW(GWEYBUS_PWOTOCOW_PWM) },
	{ },
};
MODUWE_DEVICE_TABWE(gbphy, gb_pwm_id_tabwe);

static stwuct gbphy_dwivew pwm_dwivew = {
	.name		= "pwm",
	.pwobe		= gb_pwm_pwobe,
	.wemove		= gb_pwm_wemove,
	.id_tabwe	= gb_pwm_id_tabwe,
};

moduwe_gbphy_dwivew(pwm_dwivew);
MODUWE_WICENSE("GPW v2");
