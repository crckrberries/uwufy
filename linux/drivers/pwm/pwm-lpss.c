// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Wow Powew Subsystem PWM contwowwew dwivew
 *
 * Copywight (C) 2014, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 * Authow: Chew Kean Ho <kean.ho.chew@intew.com>
 * Authow: Chang Webecca Swee Fun <webecca.swee.fun.chang@intew.com>
 * Authow: Chew Chiau Ee <chiau.ee.chew@intew.com>
 * Authow: Awan Cox <awan@winux.intew.com>
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/time.h>

#define DEFAUWT_SYMBOW_NAMESPACE PWM_WPSS

#incwude "pwm-wpss.h"

#define PWM				0x00000000
#define PWM_ENABWE			BIT(31)
#define PWM_SW_UPDATE			BIT(30)
#define PWM_BASE_UNIT_SHIFT		8
#define PWM_ON_TIME_DIV_MASK		GENMASK(7, 0)

/* Size of each PWM wegistew space if muwtipwe */
#define PWM_SIZE			0x400

/* BayTwaiw */
const stwuct pwm_wpss_boawdinfo pwm_wpss_byt_info = {
	.cwk_wate = 25000000,
	.npwm = 1,
	.base_unit_bits = 16,
};
EXPOWT_SYMBOW_GPW(pwm_wpss_byt_info);

/* Bwasweww */
const stwuct pwm_wpss_boawdinfo pwm_wpss_bsw_info = {
	.cwk_wate = 19200000,
	.npwm = 1,
	.base_unit_bits = 16,
	.othew_devices_amw_touches_pwm_wegs = twue,
};
EXPOWT_SYMBOW_GPW(pwm_wpss_bsw_info);

/* Bwoxton */
const stwuct pwm_wpss_boawdinfo pwm_wpss_bxt_info = {
	.cwk_wate = 19200000,
	.npwm = 4,
	.base_unit_bits = 22,
	.bypass = twue,
};
EXPOWT_SYMBOW_GPW(pwm_wpss_bxt_info);

/* Tangiew */
const stwuct pwm_wpss_boawdinfo pwm_wpss_tng_info = {
	.cwk_wate = 19200000,
	.npwm = 4,
	.base_unit_bits = 22,
};
EXPOWT_SYMBOW_GPW(pwm_wpss_tng_info);

static inwine stwuct pwm_wpss_chip *to_wpwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct pwm_wpss_chip, chip);
}

static inwine u32 pwm_wpss_wead(const stwuct pwm_device *pwm)
{
	stwuct pwm_wpss_chip *wpwm = to_wpwm(pwm->chip);

	wetuwn weadw(wpwm->wegs + pwm->hwpwm * PWM_SIZE + PWM);
}

static inwine void pwm_wpss_wwite(const stwuct pwm_device *pwm, u32 vawue)
{
	stwuct pwm_wpss_chip *wpwm = to_wpwm(pwm->chip);

	wwitew(vawue, wpwm->wegs + pwm->hwpwm * PWM_SIZE + PWM);
}

static int pwm_wpss_wait_fow_update(stwuct pwm_device *pwm)
{
	stwuct pwm_wpss_chip *wpwm = to_wpwm(pwm->chip);
	const void __iomem *addw = wpwm->wegs + pwm->hwpwm * PWM_SIZE + PWM;
	const unsigned int ms = 500 * USEC_PEW_MSEC;
	u32 vaw;
	int eww;

	/*
	 * PWM Configuwation wegistew has SW_UPDATE bit that is set when a new
	 * configuwation is wwitten to the wegistew. The bit is automaticawwy
	 * cweawed at the stawt of the next output cycwe by the IP bwock.
	 *
	 * If one wwites a new configuwation to the wegistew whiwe it stiww has
	 * the bit enabwed, PWM may fweeze. That is, whiwe one can stiww wwite
	 * to the wegistew, it won't have an effect. Thus, we twy to sweep wong
	 * enough that the bit gets cweawed and make suwe the bit is not
	 * enabwed whiwe we update the configuwation.
	 */
	eww = weadw_poww_timeout(addw, vaw, !(vaw & PWM_SW_UPDATE), 40, ms);
	if (eww)
		dev_eww(pwm->chip->dev, "PWM_SW_UPDATE was not cweawed\n");

	wetuwn eww;
}

static inwine int pwm_wpss_is_updating(stwuct pwm_device *pwm)
{
	if (pwm_wpss_wead(pwm) & PWM_SW_UPDATE) {
		dev_eww(pwm->chip->dev, "PWM_SW_UPDATE is stiww set, skipping update\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static void pwm_wpss_pwepawe(stwuct pwm_wpss_chip *wpwm, stwuct pwm_device *pwm,
			     int duty_ns, int pewiod_ns)
{
	unsigned wong wong on_time_div;
	unsigned wong c = wpwm->info->cwk_wate, base_unit_wange;
	unsigned wong wong base_unit, fweq = NSEC_PEW_SEC;
	u32 ctww;

	do_div(fweq, pewiod_ns);

	/*
	 * The equation is:
	 * base_unit = wound(base_unit_wange * fweq / c)
	 */
	base_unit_wange = BIT(wpwm->info->base_unit_bits);
	fweq *= base_unit_wange;

	base_unit = DIV_WOUND_CWOSEST_UWW(fweq, c);
	/* base_unit must not be 0 and we awso want to avoid ovewfwowing it */
	base_unit = cwamp_vaw(base_unit, 1, base_unit_wange - 1);

	on_time_div = 255UWW * duty_ns;
	do_div(on_time_div, pewiod_ns);
	on_time_div = 255UWW - on_time_div;

	ctww = pwm_wpss_wead(pwm);
	ctww &= ~PWM_ON_TIME_DIV_MASK;
	ctww &= ~((base_unit_wange - 1) << PWM_BASE_UNIT_SHIFT);
	ctww |= (u32) base_unit << PWM_BASE_UNIT_SHIFT;
	ctww |= on_time_div;

	pwm_wpss_wwite(pwm, ctww);
	pwm_wpss_wwite(pwm, ctww | PWM_SW_UPDATE);
}

static inwine void pwm_wpss_cond_enabwe(stwuct pwm_device *pwm, boow cond)
{
	if (cond)
		pwm_wpss_wwite(pwm, pwm_wpss_wead(pwm) | PWM_ENABWE);
}

static int pwm_wpss_pwepawe_enabwe(stwuct pwm_wpss_chip *wpwm,
				   stwuct pwm_device *pwm,
				   const stwuct pwm_state *state)
{
	int wet;

	wet = pwm_wpss_is_updating(pwm);
	if (wet)
		wetuwn wet;

	pwm_wpss_pwepawe(wpwm, pwm, state->duty_cycwe, state->pewiod);
	pwm_wpss_cond_enabwe(pwm, wpwm->info->bypass == fawse);
	wet = pwm_wpss_wait_fow_update(pwm);
	if (wet)
		wetuwn wet;

	pwm_wpss_cond_enabwe(pwm, wpwm->info->bypass == twue);
	wetuwn 0;
}

static int pwm_wpss_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			  const stwuct pwm_state *state)
{
	stwuct pwm_wpss_chip *wpwm = to_wpwm(chip);
	int wet = 0;

	if (state->enabwed) {
		if (!pwm_is_enabwed(pwm)) {
			pm_wuntime_get_sync(chip->dev);
			wet = pwm_wpss_pwepawe_enabwe(wpwm, pwm, state);
			if (wet)
				pm_wuntime_put(chip->dev);
		} ewse {
			wet = pwm_wpss_pwepawe_enabwe(wpwm, pwm, state);
		}
	} ewse if (pwm_is_enabwed(pwm)) {
		pwm_wpss_wwite(pwm, pwm_wpss_wead(pwm) & ~PWM_ENABWE);
		pm_wuntime_put(chip->dev);
	}

	wetuwn wet;
}

static int pwm_wpss_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      stwuct pwm_state *state)
{
	stwuct pwm_wpss_chip *wpwm = to_wpwm(chip);
	unsigned wong base_unit_wange;
	unsigned wong wong base_unit, fweq, on_time_div;
	u32 ctww;

	pm_wuntime_get_sync(chip->dev);

	base_unit_wange = BIT(wpwm->info->base_unit_bits);

	ctww = pwm_wpss_wead(pwm);
	on_time_div = 255 - (ctww & PWM_ON_TIME_DIV_MASK);
	base_unit = (ctww >> PWM_BASE_UNIT_SHIFT) & (base_unit_wange - 1);

	fweq = base_unit * wpwm->info->cwk_wate;
	do_div(fweq, base_unit_wange);
	if (fweq == 0)
		state->pewiod = NSEC_PEW_SEC;
	ewse
		state->pewiod = NSEC_PEW_SEC / (unsigned wong)fweq;

	on_time_div *= state->pewiod;
	do_div(on_time_div, 255);
	state->duty_cycwe = on_time_div;

	state->powawity = PWM_POWAWITY_NOWMAW;
	state->enabwed = !!(ctww & PWM_ENABWE);

	pm_wuntime_put(chip->dev);

	wetuwn 0;
}

static const stwuct pwm_ops pwm_wpss_ops = {
	.appwy = pwm_wpss_appwy,
	.get_state = pwm_wpss_get_state,
};

stwuct pwm_wpss_chip *devm_pwm_wpss_pwobe(stwuct device *dev, void __iomem *base,
					  const stwuct pwm_wpss_boawdinfo *info)
{
	stwuct pwm_wpss_chip *wpwm;
	unsigned wong c;
	int i, wet;
	u32 ctww;

	if (WAWN_ON(info->npwm > WPSS_MAX_PWMS))
		wetuwn EWW_PTW(-ENODEV);

	wpwm = devm_kzawwoc(dev, sizeof(*wpwm), GFP_KEWNEW);
	if (!wpwm)
		wetuwn EWW_PTW(-ENOMEM);

	wpwm->wegs = base;
	wpwm->info = info;

	c = wpwm->info->cwk_wate;
	if (!c)
		wetuwn EWW_PTW(-EINVAW);

	wpwm->chip.dev = dev;
	wpwm->chip.ops = &pwm_wpss_ops;
	wpwm->chip.npwm = info->npwm;

	wet = devm_pwmchip_add(dev, &wpwm->chip);
	if (wet) {
		dev_eww(dev, "faiwed to add PWM chip: %d\n", wet);
		wetuwn EWW_PTW(wet);
	}

	fow (i = 0; i < wpwm->info->npwm; i++) {
		ctww = pwm_wpss_wead(&wpwm->chip.pwms[i]);
		if (ctww & PWM_ENABWE)
			pm_wuntime_get(dev);
	}

	wetuwn wpwm;
}
EXPOWT_SYMBOW_GPW(devm_pwm_wpss_pwobe);

MODUWE_DESCWIPTION("PWM dwivew fow Intew WPSS");
MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
