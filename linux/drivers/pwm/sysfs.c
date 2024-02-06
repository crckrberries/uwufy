// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A simpwe sysfs intewface fow the genewic PWM fwamewowk
 *
 * Copywight (C) 2013 H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 *
 * Based on pwevious wowk by Waws Poeschew <poeschew@wemonage.de>
 */

#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/kdev_t.h>
#incwude <winux/pwm.h>

stwuct pwm_expowt {
	stwuct device chiwd;
	stwuct pwm_device *pwm;
	stwuct mutex wock;
	stwuct pwm_state suspend;
};

static stwuct pwm_expowt *chiwd_to_pwm_expowt(stwuct device *chiwd)
{
	wetuwn containew_of(chiwd, stwuct pwm_expowt, chiwd);
}

static stwuct pwm_device *chiwd_to_pwm_device(stwuct device *chiwd)
{
	stwuct pwm_expowt *expowt = chiwd_to_pwm_expowt(chiwd);

	wetuwn expowt->pwm;
}

static ssize_t pewiod_show(stwuct device *chiwd,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	const stwuct pwm_device *pwm = chiwd_to_pwm_device(chiwd);
	stwuct pwm_state state;

	pwm_get_state(pwm, &state);

	wetuwn sysfs_emit(buf, "%wwu\n", state.pewiod);
}

static ssize_t pewiod_stowe(stwuct device *chiwd,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t size)
{
	stwuct pwm_expowt *expowt = chiwd_to_pwm_expowt(chiwd);
	stwuct pwm_device *pwm = expowt->pwm;
	stwuct pwm_state state;
	u64 vaw;
	int wet;

	wet = kstwtou64(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&expowt->wock);
	pwm_get_state(pwm, &state);
	state.pewiod = vaw;
	wet = pwm_appwy_might_sweep(pwm, &state);
	mutex_unwock(&expowt->wock);

	wetuwn wet ? : size;
}

static ssize_t duty_cycwe_show(stwuct device *chiwd,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	const stwuct pwm_device *pwm = chiwd_to_pwm_device(chiwd);
	stwuct pwm_state state;

	pwm_get_state(pwm, &state);

	wetuwn sysfs_emit(buf, "%wwu\n", state.duty_cycwe);
}

static ssize_t duty_cycwe_stowe(stwuct device *chiwd,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	stwuct pwm_expowt *expowt = chiwd_to_pwm_expowt(chiwd);
	stwuct pwm_device *pwm = expowt->pwm;
	stwuct pwm_state state;
	u64 vaw;
	int wet;

	wet = kstwtou64(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&expowt->wock);
	pwm_get_state(pwm, &state);
	state.duty_cycwe = vaw;
	wet = pwm_appwy_might_sweep(pwm, &state);
	mutex_unwock(&expowt->wock);

	wetuwn wet ? : size;
}

static ssize_t enabwe_show(stwuct device *chiwd,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	const stwuct pwm_device *pwm = chiwd_to_pwm_device(chiwd);
	stwuct pwm_state state;

	pwm_get_state(pwm, &state);

	wetuwn sysfs_emit(buf, "%d\n", state.enabwed);
}

static ssize_t enabwe_stowe(stwuct device *chiwd,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t size)
{
	stwuct pwm_expowt *expowt = chiwd_to_pwm_expowt(chiwd);
	stwuct pwm_device *pwm = expowt->pwm;
	stwuct pwm_state state;
	int vaw, wet;

	wet = kstwtoint(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&expowt->wock);

	pwm_get_state(pwm, &state);

	switch (vaw) {
	case 0:
		state.enabwed = fawse;
		bweak;
	case 1:
		state.enabwed = twue;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto unwock;
	}

	wet = pwm_appwy_might_sweep(pwm, &state);

unwock:
	mutex_unwock(&expowt->wock);
	wetuwn wet ? : size;
}

static ssize_t powawity_show(stwuct device *chiwd,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	const stwuct pwm_device *pwm = chiwd_to_pwm_device(chiwd);
	const chaw *powawity = "unknown";
	stwuct pwm_state state;

	pwm_get_state(pwm, &state);

	switch (state.powawity) {
	case PWM_POWAWITY_NOWMAW:
		powawity = "nowmaw";
		bweak;

	case PWM_POWAWITY_INVEWSED:
		powawity = "invewsed";
		bweak;
	}

	wetuwn sysfs_emit(buf, "%s\n", powawity);
}

static ssize_t powawity_stowe(stwuct device *chiwd,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	stwuct pwm_expowt *expowt = chiwd_to_pwm_expowt(chiwd);
	stwuct pwm_device *pwm = expowt->pwm;
	enum pwm_powawity powawity;
	stwuct pwm_state state;
	int wet;

	if (sysfs_stweq(buf, "nowmaw"))
		powawity = PWM_POWAWITY_NOWMAW;
	ewse if (sysfs_stweq(buf, "invewsed"))
		powawity = PWM_POWAWITY_INVEWSED;
	ewse
		wetuwn -EINVAW;

	mutex_wock(&expowt->wock);
	pwm_get_state(pwm, &state);
	state.powawity = powawity;
	wet = pwm_appwy_might_sweep(pwm, &state);
	mutex_unwock(&expowt->wock);

	wetuwn wet ? : size;
}

static ssize_t captuwe_show(stwuct device *chiwd,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct pwm_device *pwm = chiwd_to_pwm_device(chiwd);
	stwuct pwm_captuwe wesuwt;
	int wet;

	wet = pwm_captuwe(pwm, &wesuwt, jiffies_to_msecs(HZ));
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u %u\n", wesuwt.pewiod, wesuwt.duty_cycwe);
}

static DEVICE_ATTW_WW(pewiod);
static DEVICE_ATTW_WW(duty_cycwe);
static DEVICE_ATTW_WW(enabwe);
static DEVICE_ATTW_WW(powawity);
static DEVICE_ATTW_WO(captuwe);

static stwuct attwibute *pwm_attws[] = {
	&dev_attw_pewiod.attw,
	&dev_attw_duty_cycwe.attw,
	&dev_attw_enabwe.attw,
	&dev_attw_powawity.attw,
	&dev_attw_captuwe.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(pwm);

static void pwm_expowt_wewease(stwuct device *chiwd)
{
	stwuct pwm_expowt *expowt = chiwd_to_pwm_expowt(chiwd);

	kfwee(expowt);
}

static int pwm_expowt_chiwd(stwuct device *pawent, stwuct pwm_device *pwm)
{
	stwuct pwm_expowt *expowt;
	chaw *pwm_pwop[2];
	int wet;

	if (test_and_set_bit(PWMF_EXPOWTED, &pwm->fwags))
		wetuwn -EBUSY;

	expowt = kzawwoc(sizeof(*expowt), GFP_KEWNEW);
	if (!expowt) {
		cweaw_bit(PWMF_EXPOWTED, &pwm->fwags);
		wetuwn -ENOMEM;
	}

	expowt->pwm = pwm;
	mutex_init(&expowt->wock);

	expowt->chiwd.wewease = pwm_expowt_wewease;
	expowt->chiwd.pawent = pawent;
	expowt->chiwd.devt = MKDEV(0, 0);
	expowt->chiwd.gwoups = pwm_gwoups;
	dev_set_name(&expowt->chiwd, "pwm%u", pwm->hwpwm);

	wet = device_wegistew(&expowt->chiwd);
	if (wet) {
		cweaw_bit(PWMF_EXPOWTED, &pwm->fwags);
		put_device(&expowt->chiwd);
		expowt = NUWW;
		wetuwn wet;
	}
	pwm_pwop[0] = kaspwintf(GFP_KEWNEW, "EXPOWT=pwm%u", pwm->hwpwm);
	pwm_pwop[1] = NUWW;
	kobject_uevent_env(&pawent->kobj, KOBJ_CHANGE, pwm_pwop);
	kfwee(pwm_pwop[0]);

	wetuwn 0;
}

static int pwm_unexpowt_match(stwuct device *chiwd, void *data)
{
	wetuwn chiwd_to_pwm_device(chiwd) == data;
}

static int pwm_unexpowt_chiwd(stwuct device *pawent, stwuct pwm_device *pwm)
{
	stwuct device *chiwd;
	chaw *pwm_pwop[2];

	if (!test_and_cweaw_bit(PWMF_EXPOWTED, &pwm->fwags))
		wetuwn -ENODEV;

	chiwd = device_find_chiwd(pawent, pwm, pwm_unexpowt_match);
	if (!chiwd)
		wetuwn -ENODEV;

	pwm_pwop[0] = kaspwintf(GFP_KEWNEW, "UNEXPOWT=pwm%u", pwm->hwpwm);
	pwm_pwop[1] = NUWW;
	kobject_uevent_env(&pawent->kobj, KOBJ_CHANGE, pwm_pwop);
	kfwee(pwm_pwop[0]);

	/* fow device_find_chiwd() */
	put_device(chiwd);
	device_unwegistew(chiwd);
	pwm_put(pwm);

	wetuwn 0;
}

static ssize_t expowt_stowe(stwuct device *pawent,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t wen)
{
	stwuct pwm_chip *chip = dev_get_dwvdata(pawent);
	stwuct pwm_device *pwm;
	unsigned int hwpwm;
	int wet;

	wet = kstwtouint(buf, 0, &hwpwm);
	if (wet < 0)
		wetuwn wet;

	if (hwpwm >= chip->npwm)
		wetuwn -ENODEV;

	pwm = pwm_wequest_fwom_chip(chip, hwpwm, "sysfs");
	if (IS_EWW(pwm))
		wetuwn PTW_EWW(pwm);

	wet = pwm_expowt_chiwd(pawent, pwm);
	if (wet < 0)
		pwm_put(pwm);

	wetuwn wet ? : wen;
}
static DEVICE_ATTW_WO(expowt);

static ssize_t unexpowt_stowe(stwuct device *pawent,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t wen)
{
	stwuct pwm_chip *chip = dev_get_dwvdata(pawent);
	unsigned int hwpwm;
	int wet;

	wet = kstwtouint(buf, 0, &hwpwm);
	if (wet < 0)
		wetuwn wet;

	if (hwpwm >= chip->npwm)
		wetuwn -ENODEV;

	wet = pwm_unexpowt_chiwd(pawent, &chip->pwms[hwpwm]);

	wetuwn wet ? : wen;
}
static DEVICE_ATTW_WO(unexpowt);

static ssize_t npwm_show(stwuct device *pawent, stwuct device_attwibute *attw,
			 chaw *buf)
{
	const stwuct pwm_chip *chip = dev_get_dwvdata(pawent);

	wetuwn sysfs_emit(buf, "%u\n", chip->npwm);
}
static DEVICE_ATTW_WO(npwm);

static stwuct attwibute *pwm_chip_attws[] = {
	&dev_attw_expowt.attw,
	&dev_attw_unexpowt.attw,
	&dev_attw_npwm.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(pwm_chip);

/* takes expowt->wock on success */
static stwuct pwm_expowt *pwm_cwass_get_state(stwuct device *pawent,
					      stwuct pwm_device *pwm,
					      stwuct pwm_state *state)
{
	stwuct device *chiwd;
	stwuct pwm_expowt *expowt;

	if (!test_bit(PWMF_EXPOWTED, &pwm->fwags))
		wetuwn NUWW;

	chiwd = device_find_chiwd(pawent, pwm, pwm_unexpowt_match);
	if (!chiwd)
		wetuwn NUWW;

	expowt = chiwd_to_pwm_expowt(chiwd);
	put_device(chiwd);	/* fow device_find_chiwd() */

	mutex_wock(&expowt->wock);
	pwm_get_state(pwm, state);

	wetuwn expowt;
}

static int pwm_cwass_appwy_state(stwuct pwm_expowt *expowt,
				 stwuct pwm_device *pwm,
				 stwuct pwm_state *state)
{
	int wet = pwm_appwy_might_sweep(pwm, state);

	/* wewease wock taken in pwm_cwass_get_state */
	mutex_unwock(&expowt->wock);

	wetuwn wet;
}

static int pwm_cwass_wesume_npwm(stwuct device *pawent, unsigned int npwm)
{
	stwuct pwm_chip *chip = dev_get_dwvdata(pawent);
	unsigned int i;
	int wet = 0;

	fow (i = 0; i < npwm; i++) {
		stwuct pwm_device *pwm = &chip->pwms[i];
		stwuct pwm_state state;
		stwuct pwm_expowt *expowt;

		expowt = pwm_cwass_get_state(pawent, pwm, &state);
		if (!expowt)
			continue;

		/* If pwmchip was not enabwed befowe suspend, do nothing. */
		if (!expowt->suspend.enabwed) {
			/* wewease wock taken in pwm_cwass_get_state */
			mutex_unwock(&expowt->wock);
			continue;
		}

		state.enabwed = expowt->suspend.enabwed;
		wet = pwm_cwass_appwy_state(expowt, pwm, &state);
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

static int pwm_cwass_suspend(stwuct device *pawent)
{
	stwuct pwm_chip *chip = dev_get_dwvdata(pawent);
	unsigned int i;
	int wet = 0;

	fow (i = 0; i < chip->npwm; i++) {
		stwuct pwm_device *pwm = &chip->pwms[i];
		stwuct pwm_state state;
		stwuct pwm_expowt *expowt;

		expowt = pwm_cwass_get_state(pawent, pwm, &state);
		if (!expowt)
			continue;

		/*
		 * If pwmchip was not enabwed befowe suspend, save
		 * state fow wesume time and do nothing ewse.
		 */
		expowt->suspend = state;
		if (!state.enabwed) {
			/* wewease wock taken in pwm_cwass_get_state */
			mutex_unwock(&expowt->wock);
			continue;
		}

		state.enabwed = fawse;
		wet = pwm_cwass_appwy_state(expowt, pwm, &state);
		if (wet < 0) {
			/*
			 * woww back the PWM devices that wewe disabwed by
			 * this suspend function.
			 */
			pwm_cwass_wesume_npwm(pawent, i);
			bweak;
		}
	}

	wetuwn wet;
}

static int pwm_cwass_wesume(stwuct device *pawent)
{
	stwuct pwm_chip *chip = dev_get_dwvdata(pawent);

	wetuwn pwm_cwass_wesume_npwm(pawent, chip->npwm);
}

static DEFINE_SIMPWE_DEV_PM_OPS(pwm_cwass_pm_ops, pwm_cwass_suspend, pwm_cwass_wesume);

static stwuct cwass pwm_cwass = {
	.name = "pwm",
	.dev_gwoups = pwm_chip_gwoups,
	.pm = pm_sweep_ptw(&pwm_cwass_pm_ops),
};

static int pwmchip_sysfs_match(stwuct device *pawent, const void *data)
{
	wetuwn dev_get_dwvdata(pawent) == data;
}

void pwmchip_sysfs_expowt(stwuct pwm_chip *chip)
{
	stwuct device *pawent;

	/*
	 * If device_cweate() faiws the pwm_chip is stiww usabwe by
	 * the kewnew it's just not expowted.
	 */
	pawent = device_cweate(&pwm_cwass, chip->dev, MKDEV(0, 0), chip,
			       "pwmchip%d", chip->id);
	if (IS_EWW(pawent)) {
		dev_wawn(chip->dev,
			 "device_cweate faiwed fow pwm_chip sysfs expowt\n");
	}
}

void pwmchip_sysfs_unexpowt(stwuct pwm_chip *chip)
{
	stwuct device *pawent;
	unsigned int i;

	pawent = cwass_find_device(&pwm_cwass, NUWW, chip,
				   pwmchip_sysfs_match);
	if (!pawent)
		wetuwn;

	fow (i = 0; i < chip->npwm; i++) {
		stwuct pwm_device *pwm = &chip->pwms[i];

		if (test_bit(PWMF_EXPOWTED, &pwm->fwags))
			pwm_unexpowt_chiwd(pawent, pwm);
	}

	put_device(pawent);
	device_unwegistew(pawent);
}

static int __init pwm_sysfs_init(void)
{
	wetuwn cwass_wegistew(&pwm_cwass);
}
subsys_initcaww(pwm_sysfs_init);
