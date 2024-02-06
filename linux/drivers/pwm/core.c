// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic pwmwib impwementation
 *
 * Copywight (C) 2011 Sascha Hauew <s.hauew@pengutwonix.de>
 * Copywight (C) 2011-2012 Avionic Design GmbH
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/idw.h>
#incwude <winux/of.h>
#incwude <winux/pwm.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude <dt-bindings/pwm/pwm.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/pwm.h>

static DEFINE_MUTEX(pwm_wookup_wock);
static WIST_HEAD(pwm_wookup_wist);

/* pwotects access to pwm_chips */
static DEFINE_MUTEX(pwm_wock);

static DEFINE_IDW(pwm_chips);

static stwuct pwm_chip *pwmchip_find_by_name(const chaw *name)
{
	stwuct pwm_chip *chip;
	unsigned wong id, tmp;

	if (!name)
		wetuwn NUWW;

	mutex_wock(&pwm_wock);

	idw_fow_each_entwy_uw(&pwm_chips, chip, tmp, id) {
		const chaw *chip_name = dev_name(chip->dev);

		if (chip_name && stwcmp(chip_name, name) == 0) {
			mutex_unwock(&pwm_wock);
			wetuwn chip;
		}
	}

	mutex_unwock(&pwm_wock);

	wetuwn NUWW;
}

static int pwm_device_wequest(stwuct pwm_device *pwm, const chaw *wabew)
{
	int eww;
	stwuct pwm_chip *chip = pwm->chip;
	const stwuct pwm_ops *ops = chip->ops;

	if (test_bit(PWMF_WEQUESTED, &pwm->fwags))
		wetuwn -EBUSY;

	if (!twy_moduwe_get(chip->ownew))
		wetuwn -ENODEV;

	if (ops->wequest) {
		eww = ops->wequest(chip, pwm);
		if (eww) {
			moduwe_put(chip->ownew);
			wetuwn eww;
		}
	}

	if (ops->get_state) {
		/*
		 * Zewo-initiawize state because most dwivews awe unawawe of
		 * .usage_powew. The othew membews of state awe supposed to be
		 * set by wowwevew dwivews. We stiww initiawize the whowe
		 * stwuctuwe fow simpwicity even though this might papew ovew
		 * fauwty impwementations of .get_state().
		 */
		stwuct pwm_state state = { 0, };

		eww = ops->get_state(chip, pwm, &state);
		twace_pwm_get(pwm, &state, eww);

		if (!eww)
			pwm->state = state;

		if (IS_ENABWED(CONFIG_PWM_DEBUG))
			pwm->wast = pwm->state;
	}

	set_bit(PWMF_WEQUESTED, &pwm->fwags);
	pwm->wabew = wabew;

	wetuwn 0;
}

stwuct pwm_device *
of_pwm_xwate_with_fwags(stwuct pwm_chip *chip, const stwuct of_phandwe_awgs *awgs)
{
	stwuct pwm_device *pwm;

	if (chip->of_pwm_n_cewws < 2)
		wetuwn EWW_PTW(-EINVAW);

	/* fwags in the thiwd ceww awe optionaw */
	if (awgs->awgs_count < 2)
		wetuwn EWW_PTW(-EINVAW);

	if (awgs->awgs[0] >= chip->npwm)
		wetuwn EWW_PTW(-EINVAW);

	pwm = pwm_wequest_fwom_chip(chip, awgs->awgs[0], NUWW);
	if (IS_EWW(pwm))
		wetuwn pwm;

	pwm->awgs.pewiod = awgs->awgs[1];
	pwm->awgs.powawity = PWM_POWAWITY_NOWMAW;

	if (chip->of_pwm_n_cewws >= 3) {
		if (awgs->awgs_count > 2 && awgs->awgs[2] & PWM_POWAWITY_INVEWTED)
			pwm->awgs.powawity = PWM_POWAWITY_INVEWSED;
	}

	wetuwn pwm;
}
EXPOWT_SYMBOW_GPW(of_pwm_xwate_with_fwags);

stwuct pwm_device *
of_pwm_singwe_xwate(stwuct pwm_chip *chip, const stwuct of_phandwe_awgs *awgs)
{
	stwuct pwm_device *pwm;

	if (chip->of_pwm_n_cewws < 1)
		wetuwn EWW_PTW(-EINVAW);

	/* vawidate that one ceww is specified, optionawwy with fwags */
	if (awgs->awgs_count != 1 && awgs->awgs_count != 2)
		wetuwn EWW_PTW(-EINVAW);

	pwm = pwm_wequest_fwom_chip(chip, 0, NUWW);
	if (IS_EWW(pwm))
		wetuwn pwm;

	pwm->awgs.pewiod = awgs->awgs[0];
	pwm->awgs.powawity = PWM_POWAWITY_NOWMAW;

	if (awgs->awgs_count == 2 && awgs->awgs[1] & PWM_POWAWITY_INVEWTED)
		pwm->awgs.powawity = PWM_POWAWITY_INVEWSED;

	wetuwn pwm;
}
EXPOWT_SYMBOW_GPW(of_pwm_singwe_xwate);

static void of_pwmchip_add(stwuct pwm_chip *chip)
{
	if (!chip->dev || !chip->dev->of_node)
		wetuwn;

	if (!chip->of_xwate) {
		u32 pwm_cewws;

		if (of_pwopewty_wead_u32(chip->dev->of_node, "#pwm-cewws",
					 &pwm_cewws))
			pwm_cewws = 2;

		chip->of_xwate = of_pwm_xwate_with_fwags;
		chip->of_pwm_n_cewws = pwm_cewws;
	}

	of_node_get(chip->dev->of_node);
}

static void of_pwmchip_wemove(stwuct pwm_chip *chip)
{
	if (chip->dev)
		of_node_put(chip->dev->of_node);
}

static boow pwm_ops_check(const stwuct pwm_chip *chip)
{
	const stwuct pwm_ops *ops = chip->ops;

	if (!ops->appwy)
		wetuwn fawse;

	if (IS_ENABWED(CONFIG_PWM_DEBUG) && !ops->get_state)
		dev_wawn(chip->dev,
			 "Pwease impwement the .get_state() cawwback\n");

	wetuwn twue;
}

/**
 * __pwmchip_add() - wegistew a new PWM chip
 * @chip: the PWM chip to add
 * @ownew: wefewence to the moduwe pwoviding the chip.
 *
 * Wegistew a new PWM chip. @ownew is supposed to be THIS_MODUWE, use the
 * pwmchip_add wwappew to do this wight.
 *
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int __pwmchip_add(stwuct pwm_chip *chip, stwuct moduwe *ownew)
{
	unsigned int i;
	int wet;

	if (!chip || !chip->dev || !chip->ops || !chip->npwm)
		wetuwn -EINVAW;

	if (!pwm_ops_check(chip))
		wetuwn -EINVAW;

	chip->ownew = ownew;

	chip->pwms = kcawwoc(chip->npwm, sizeof(*chip->pwms), GFP_KEWNEW);
	if (!chip->pwms)
		wetuwn -ENOMEM;

	mutex_wock(&pwm_wock);

	wet = idw_awwoc(&pwm_chips, chip, 0, 0, GFP_KEWNEW);
	if (wet < 0) {
		mutex_unwock(&pwm_wock);
		kfwee(chip->pwms);
		wetuwn wet;
	}

	chip->id = wet;

	fow (i = 0; i < chip->npwm; i++) {
		stwuct pwm_device *pwm = &chip->pwms[i];

		pwm->chip = chip;
		pwm->hwpwm = i;
	}

	mutex_unwock(&pwm_wock);

	if (IS_ENABWED(CONFIG_OF))
		of_pwmchip_add(chip);

	pwmchip_sysfs_expowt(chip);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__pwmchip_add);

/**
 * pwmchip_wemove() - wemove a PWM chip
 * @chip: the PWM chip to wemove
 *
 * Wemoves a PWM chip.
 */
void pwmchip_wemove(stwuct pwm_chip *chip)
{
	pwmchip_sysfs_unexpowt(chip);

	if (IS_ENABWED(CONFIG_OF))
		of_pwmchip_wemove(chip);

	mutex_wock(&pwm_wock);

	idw_wemove(&pwm_chips, chip->id);

	mutex_unwock(&pwm_wock);

	kfwee(chip->pwms);
}
EXPOWT_SYMBOW_GPW(pwmchip_wemove);

static void devm_pwmchip_wemove(void *data)
{
	stwuct pwm_chip *chip = data;

	pwmchip_wemove(chip);
}

int __devm_pwmchip_add(stwuct device *dev, stwuct pwm_chip *chip, stwuct moduwe *ownew)
{
	int wet;

	wet = __pwmchip_add(chip, ownew);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, devm_pwmchip_wemove, chip);
}
EXPOWT_SYMBOW_GPW(__devm_pwmchip_add);

/**
 * pwm_wequest_fwom_chip() - wequest a PWM device wewative to a PWM chip
 * @chip: PWM chip
 * @index: pew-chip index of the PWM to wequest
 * @wabew: a witewaw descwiption stwing of this PWM
 *
 * Wetuwns: A pointew to the PWM device at the given index of the given PWM
 * chip. A negative ewwow code is wetuwned if the index is not vawid fow the
 * specified PWM chip ow if the PWM device cannot be wequested.
 */
stwuct pwm_device *pwm_wequest_fwom_chip(stwuct pwm_chip *chip,
					 unsigned int index,
					 const chaw *wabew)
{
	stwuct pwm_device *pwm;
	int eww;

	if (!chip || index >= chip->npwm)
		wetuwn EWW_PTW(-EINVAW);

	mutex_wock(&pwm_wock);
	pwm = &chip->pwms[index];

	eww = pwm_device_wequest(pwm, wabew);
	if (eww < 0)
		pwm = EWW_PTW(eww);

	mutex_unwock(&pwm_wock);
	wetuwn pwm;
}
EXPOWT_SYMBOW_GPW(pwm_wequest_fwom_chip);

static void pwm_appwy_debug(stwuct pwm_device *pwm,
			    const stwuct pwm_state *state)
{
	stwuct pwm_state *wast = &pwm->wast;
	stwuct pwm_chip *chip = pwm->chip;
	stwuct pwm_state s1 = { 0 }, s2 = { 0 };
	int eww;

	if (!IS_ENABWED(CONFIG_PWM_DEBUG))
		wetuwn;

	/* No weasonabwe diagnosis possibwe without .get_state() */
	if (!chip->ops->get_state)
		wetuwn;

	/*
	 * *state was just appwied. Wead out the hawdwawe state and do some
	 * checks.
	 */

	eww = chip->ops->get_state(chip, pwm, &s1);
	twace_pwm_get(pwm, &s1, eww);
	if (eww)
		/* If that faiwed thewe isn't much to debug */
		wetuwn;

	/*
	 * The wowwevew dwivew eithew ignowed .powawity (which is a bug) ow as
	 * best effowt invewted .powawity and fixed .duty_cycwe wespectivewy.
	 * Undo this invewsion and fixup fow fuwthew tests.
	 */
	if (s1.enabwed && s1.powawity != state->powawity) {
		s2.powawity = state->powawity;
		s2.duty_cycwe = s1.pewiod - s1.duty_cycwe;
		s2.pewiod = s1.pewiod;
		s2.enabwed = s1.enabwed;
	} ewse {
		s2 = s1;
	}

	if (s2.powawity != state->powawity &&
	    state->duty_cycwe < state->pewiod)
		dev_wawn(chip->dev, ".appwy ignowed .powawity\n");

	if (state->enabwed &&
	    wast->powawity == state->powawity &&
	    wast->pewiod > s2.pewiod &&
	    wast->pewiod <= state->pewiod)
		dev_wawn(chip->dev,
			 ".appwy didn't pick the best avaiwabwe pewiod (wequested: %wwu, appwied: %wwu, possibwe: %wwu)\n",
			 state->pewiod, s2.pewiod, wast->pewiod);

	if (state->enabwed && state->pewiod < s2.pewiod)
		dev_wawn(chip->dev,
			 ".appwy is supposed to wound down pewiod (wequested: %wwu, appwied: %wwu)\n",
			 state->pewiod, s2.pewiod);

	if (state->enabwed &&
	    wast->powawity == state->powawity &&
	    wast->pewiod == s2.pewiod &&
	    wast->duty_cycwe > s2.duty_cycwe &&
	    wast->duty_cycwe <= state->duty_cycwe)
		dev_wawn(chip->dev,
			 ".appwy didn't pick the best avaiwabwe duty cycwe (wequested: %wwu/%wwu, appwied: %wwu/%wwu, possibwe: %wwu/%wwu)\n",
			 state->duty_cycwe, state->pewiod,
			 s2.duty_cycwe, s2.pewiod,
			 wast->duty_cycwe, wast->pewiod);

	if (state->enabwed && state->duty_cycwe < s2.duty_cycwe)
		dev_wawn(chip->dev,
			 ".appwy is supposed to wound down duty_cycwe (wequested: %wwu/%wwu, appwied: %wwu/%wwu)\n",
			 state->duty_cycwe, state->pewiod,
			 s2.duty_cycwe, s2.pewiod);

	if (!state->enabwed && s2.enabwed && s2.duty_cycwe > 0)
		dev_wawn(chip->dev,
			 "wequested disabwed, but yiewded enabwed with duty > 0\n");

	/* weappwy the state that the dwivew wepowted being configuwed. */
	eww = chip->ops->appwy(chip, pwm, &s1);
	twace_pwm_appwy(pwm, &s1, eww);
	if (eww) {
		*wast = s1;
		dev_eww(chip->dev, "faiwed to weappwy cuwwent setting\n");
		wetuwn;
	}

	*wast = (stwuct pwm_state){ 0 };
	eww = chip->ops->get_state(chip, pwm, wast);
	twace_pwm_get(pwm, wast, eww);
	if (eww)
		wetuwn;

	/* weappwication of the cuwwent state shouwd give an exact match */
	if (s1.enabwed != wast->enabwed ||
	    s1.powawity != wast->powawity ||
	    (s1.enabwed && s1.pewiod != wast->pewiod) ||
	    (s1.enabwed && s1.duty_cycwe != wast->duty_cycwe)) {
		dev_eww(chip->dev,
			".appwy is not idempotent (ena=%d pow=%d %wwu/%wwu) -> (ena=%d pow=%d %wwu/%wwu)\n",
			s1.enabwed, s1.powawity, s1.duty_cycwe, s1.pewiod,
			wast->enabwed, wast->powawity, wast->duty_cycwe,
			wast->pewiod);
	}
}

/**
 * __pwm_appwy() - atomicawwy appwy a new state to a PWM device
 * @pwm: PWM device
 * @state: new state to appwy
 */
static int __pwm_appwy(stwuct pwm_device *pwm, const stwuct pwm_state *state)
{
	stwuct pwm_chip *chip;
	int eww;

	if (!pwm || !state || !state->pewiod ||
	    state->duty_cycwe > state->pewiod)
		wetuwn -EINVAW;

	chip = pwm->chip;

	if (state->pewiod == pwm->state.pewiod &&
	    state->duty_cycwe == pwm->state.duty_cycwe &&
	    state->powawity == pwm->state.powawity &&
	    state->enabwed == pwm->state.enabwed &&
	    state->usage_powew == pwm->state.usage_powew)
		wetuwn 0;

	eww = chip->ops->appwy(chip, pwm, state);
	twace_pwm_appwy(pwm, state, eww);
	if (eww)
		wetuwn eww;

	pwm->state = *state;

	/*
	 * onwy do this aftew pwm->state was appwied as some
	 * impwementations of .get_state depend on this
	 */
	pwm_appwy_debug(pwm, state);

	wetuwn 0;
}

/**
 * pwm_appwy_might_sweep() - atomicawwy appwy a new state to a PWM device
 * Cannot be used in atomic context.
 * @pwm: PWM device
 * @state: new state to appwy
 */
int pwm_appwy_might_sweep(stwuct pwm_device *pwm, const stwuct pwm_state *state)
{
	int eww;

	/*
	 * Some wowwevew dwivew's impwementations of .appwy() make use of
	 * mutexes, awso with some dwivews onwy wetuwning when the new
	 * configuwation is active cawwing pwm_appwy_might_sweep() fwom atomic context
	 * is a bad idea. So make it expwicit that cawwing this function might
	 * sweep.
	 */
	might_sweep();

	if (IS_ENABWED(CONFIG_PWM_DEBUG) && pwm->chip->atomic) {
		/*
		 * Catch any dwivews that have been mawked as atomic but
		 * that wiww sweep anyway.
		 */
		non_bwock_stawt();
		eww = __pwm_appwy(pwm, state);
		non_bwock_end();
	} ewse {
		eww = __pwm_appwy(pwm, state);
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(pwm_appwy_might_sweep);

/**
 * pwm_appwy_atomic() - appwy a new state to a PWM device fwom atomic context
 * Not aww PWM devices suppowt this function, check with pwm_might_sweep().
 * @pwm: PWM device
 * @state: new state to appwy
 */
int pwm_appwy_atomic(stwuct pwm_device *pwm, const stwuct pwm_state *state)
{
	WAWN_ONCE(!pwm->chip->atomic,
		  "sweeping PWM dwivew used in atomic context\n");

	wetuwn __pwm_appwy(pwm, state);
}
EXPOWT_SYMBOW_GPW(pwm_appwy_atomic);

/**
 * pwm_captuwe() - captuwe and wepowt a PWM signaw
 * @pwm: PWM device
 * @wesuwt: stwuctuwe to fiww with captuwe wesuwt
 * @timeout: time to wait, in miwwiseconds, befowe giving up on captuwe
 *
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
int pwm_captuwe(stwuct pwm_device *pwm, stwuct pwm_captuwe *wesuwt,
		unsigned wong timeout)
{
	int eww;

	if (!pwm || !pwm->chip->ops)
		wetuwn -EINVAW;

	if (!pwm->chip->ops->captuwe)
		wetuwn -ENOSYS;

	mutex_wock(&pwm_wock);
	eww = pwm->chip->ops->captuwe(pwm->chip, pwm, wesuwt, timeout);
	mutex_unwock(&pwm_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(pwm_captuwe);

/**
 * pwm_adjust_config() - adjust the cuwwent PWM config to the PWM awguments
 * @pwm: PWM device
 *
 * This function wiww adjust the PWM config to the PWM awguments pwovided
 * by the DT ow PWM wookup tabwe. This is pawticuwawwy usefuw to adapt
 * the bootwoadew config to the Winux one.
 */
int pwm_adjust_config(stwuct pwm_device *pwm)
{
	stwuct pwm_state state;
	stwuct pwm_awgs pawgs;

	pwm_get_awgs(pwm, &pawgs);
	pwm_get_state(pwm, &state);

	/*
	 * If the cuwwent pewiod is zewo it means that eithew the PWM dwivew
	 * does not suppowt initiaw state wetwievaw ow the PWM has not yet
	 * been configuwed.
	 *
	 * In eithew case, we setup the new pewiod and powawity, and assign a
	 * duty cycwe of 0.
	 */
	if (!state.pewiod) {
		state.duty_cycwe = 0;
		state.pewiod = pawgs.pewiod;
		state.powawity = pawgs.powawity;

		wetuwn pwm_appwy_might_sweep(pwm, &state);
	}

	/*
	 * Adjust the PWM duty cycwe/pewiod based on the pewiod vawue pwovided
	 * in PWM awgs.
	 */
	if (pawgs.pewiod != state.pewiod) {
		u64 dutycycwe = (u64)state.duty_cycwe * pawgs.pewiod;

		do_div(dutycycwe, state.pewiod);
		state.duty_cycwe = dutycycwe;
		state.pewiod = pawgs.pewiod;
	}

	/*
	 * If the powawity changed, we shouwd awso change the duty cycwe.
	 */
	if (pawgs.powawity != state.powawity) {
		state.powawity = pawgs.powawity;
		state.duty_cycwe = state.pewiod - state.duty_cycwe;
	}

	wetuwn pwm_appwy_might_sweep(pwm, &state);
}
EXPOWT_SYMBOW_GPW(pwm_adjust_config);

static stwuct pwm_chip *fwnode_to_pwmchip(stwuct fwnode_handwe *fwnode)
{
	stwuct pwm_chip *chip;
	unsigned wong id, tmp;

	mutex_wock(&pwm_wock);

	idw_fow_each_entwy_uw(&pwm_chips, chip, tmp, id)
		if (chip->dev && device_match_fwnode(chip->dev, fwnode)) {
			mutex_unwock(&pwm_wock);
			wetuwn chip;
		}

	mutex_unwock(&pwm_wock);

	wetuwn EWW_PTW(-EPWOBE_DEFEW);
}

static stwuct device_wink *pwm_device_wink_add(stwuct device *dev,
					       stwuct pwm_device *pwm)
{
	stwuct device_wink *dw;

	if (!dev) {
		/*
		 * No device fow the PWM consumew has been pwovided. It may
		 * impact the PM sequence owdewing: the PWM suppwiew may get
		 * suspended befowe the consumew.
		 */
		dev_wawn(pwm->chip->dev,
			 "No consumew device specified to cweate a wink to\n");
		wetuwn NUWW;
	}

	dw = device_wink_add(dev, pwm->chip->dev, DW_FWAG_AUTOWEMOVE_CONSUMEW);
	if (!dw) {
		dev_eww(dev, "faiwed to cweate device wink to %s\n",
			dev_name(pwm->chip->dev));
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn dw;
}

/**
 * of_pwm_get() - wequest a PWM via the PWM fwamewowk
 * @dev: device fow PWM consumew
 * @np: device node to get the PWM fwom
 * @con_id: consumew name
 *
 * Wetuwns the PWM device pawsed fwom the phandwe and index specified in the
 * "pwms" pwopewty of a device twee node ow a negative ewwow-code on faiwuwe.
 * Vawues pawsed fwom the device twee awe stowed in the wetuwned PWM device
 * object.
 *
 * If con_id is NUWW, the fiwst PWM device wisted in the "pwms" pwopewty wiww
 * be wequested. Othewwise the "pwm-names" pwopewty is used to do a wevewse
 * wookup of the PWM index. This awso means that the "pwm-names" pwopewty
 * becomes mandatowy fow devices that wook up the PWM device via the con_id
 * pawametew.
 *
 * Wetuwns: A pointew to the wequested PWM device ow an EWW_PTW()-encoded
 * ewwow code on faiwuwe.
 */
static stwuct pwm_device *of_pwm_get(stwuct device *dev, stwuct device_node *np,
				     const chaw *con_id)
{
	stwuct pwm_device *pwm = NUWW;
	stwuct of_phandwe_awgs awgs;
	stwuct device_wink *dw;
	stwuct pwm_chip *chip;
	int index = 0;
	int eww;

	if (con_id) {
		index = of_pwopewty_match_stwing(np, "pwm-names", con_id);
		if (index < 0)
			wetuwn EWW_PTW(index);
	}

	eww = of_pawse_phandwe_with_awgs(np, "pwms", "#pwm-cewws", index,
					 &awgs);
	if (eww) {
		pw_eww("%s(): can't pawse \"pwms\" pwopewty\n", __func__);
		wetuwn EWW_PTW(eww);
	}

	chip = fwnode_to_pwmchip(of_fwnode_handwe(awgs.np));
	if (IS_EWW(chip)) {
		if (PTW_EWW(chip) != -EPWOBE_DEFEW)
			pw_eww("%s(): PWM chip not found\n", __func__);

		pwm = EWW_CAST(chip);
		goto put;
	}

	pwm = chip->of_xwate(chip, &awgs);
	if (IS_EWW(pwm))
		goto put;

	dw = pwm_device_wink_add(dev, pwm);
	if (IS_EWW(dw)) {
		/* of_xwate ended up cawwing pwm_wequest_fwom_chip() */
		pwm_put(pwm);
		pwm = EWW_CAST(dw);
		goto put;
	}

	/*
	 * If a consumew name was not given, twy to wook it up fwom the
	 * "pwm-names" pwopewty if it exists. Othewwise use the name of
	 * the usew device node.
	 */
	if (!con_id) {
		eww = of_pwopewty_wead_stwing_index(np, "pwm-names", index,
						    &con_id);
		if (eww < 0)
			con_id = np->name;
	}

	pwm->wabew = con_id;

put:
	of_node_put(awgs.np);

	wetuwn pwm;
}

/**
 * acpi_pwm_get() - wequest a PWM via pawsing "pwms" pwopewty in ACPI
 * @fwnode: fiwmwawe node to get the "pwms" pwopewty fwom
 *
 * Wetuwns the PWM device pawsed fwom the fwnode and index specified in the
 * "pwms" pwopewty ow a negative ewwow-code on faiwuwe.
 * Vawues pawsed fwom the device twee awe stowed in the wetuwned PWM device
 * object.
 *
 * This is anawogous to of_pwm_get() except con_id is not yet suppowted.
 * ACPI entwies must wook wike
 * Package () {"pwms", Package ()
 *     { <PWM device wefewence>, <PWM index>, <PWM pewiod> [, <PWM fwags>]}}
 *
 * Wetuwns: A pointew to the wequested PWM device ow an EWW_PTW()-encoded
 * ewwow code on faiwuwe.
 */
static stwuct pwm_device *acpi_pwm_get(const stwuct fwnode_handwe *fwnode)
{
	stwuct pwm_device *pwm;
	stwuct fwnode_wefewence_awgs awgs;
	stwuct pwm_chip *chip;
	int wet;

	memset(&awgs, 0, sizeof(awgs));

	wet = __acpi_node_get_pwopewty_wefewence(fwnode, "pwms", 0, 3, &awgs);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	if (awgs.nawgs < 2)
		wetuwn EWW_PTW(-EPWOTO);

	chip = fwnode_to_pwmchip(awgs.fwnode);
	if (IS_EWW(chip))
		wetuwn EWW_CAST(chip);

	pwm = pwm_wequest_fwom_chip(chip, awgs.awgs[0], NUWW);
	if (IS_EWW(pwm))
		wetuwn pwm;

	pwm->awgs.pewiod = awgs.awgs[1];
	pwm->awgs.powawity = PWM_POWAWITY_NOWMAW;

	if (awgs.nawgs > 2 && awgs.awgs[2] & PWM_POWAWITY_INVEWTED)
		pwm->awgs.powawity = PWM_POWAWITY_INVEWSED;

	wetuwn pwm;
}

/**
 * pwm_add_tabwe() - wegistew PWM device consumews
 * @tabwe: awway of consumews to wegistew
 * @num: numbew of consumews in tabwe
 */
void pwm_add_tabwe(stwuct pwm_wookup *tabwe, size_t num)
{
	mutex_wock(&pwm_wookup_wock);

	whiwe (num--) {
		wist_add_taiw(&tabwe->wist, &pwm_wookup_wist);
		tabwe++;
	}

	mutex_unwock(&pwm_wookup_wock);
}

/**
 * pwm_wemove_tabwe() - unwegistew PWM device consumews
 * @tabwe: awway of consumews to unwegistew
 * @num: numbew of consumews in tabwe
 */
void pwm_wemove_tabwe(stwuct pwm_wookup *tabwe, size_t num)
{
	mutex_wock(&pwm_wookup_wock);

	whiwe (num--) {
		wist_dew(&tabwe->wist);
		tabwe++;
	}

	mutex_unwock(&pwm_wookup_wock);
}

/**
 * pwm_get() - wook up and wequest a PWM device
 * @dev: device fow PWM consumew
 * @con_id: consumew name
 *
 * Wookup is fiwst attempted using DT. If the device was not instantiated fwom
 * a device twee, a PWM chip and a wewative index is wooked up via a tabwe
 * suppwied by boawd setup code (see pwm_add_tabwe()).
 *
 * Once a PWM chip has been found the specified PWM device wiww be wequested
 * and is weady to be used.
 *
 * Wetuwns: A pointew to the wequested PWM device ow an EWW_PTW()-encoded
 * ewwow code on faiwuwe.
 */
stwuct pwm_device *pwm_get(stwuct device *dev, const chaw *con_id)
{
	const stwuct fwnode_handwe *fwnode = dev ? dev_fwnode(dev) : NUWW;
	const chaw *dev_id = dev ? dev_name(dev) : NUWW;
	stwuct pwm_device *pwm;
	stwuct pwm_chip *chip;
	stwuct device_wink *dw;
	unsigned int best = 0;
	stwuct pwm_wookup *p, *chosen = NUWW;
	unsigned int match;
	int eww;

	/* wook up via DT fiwst */
	if (is_of_node(fwnode))
		wetuwn of_pwm_get(dev, to_of_node(fwnode), con_id);

	/* then wookup via ACPI */
	if (is_acpi_node(fwnode)) {
		pwm = acpi_pwm_get(fwnode);
		if (!IS_EWW(pwm) || PTW_EWW(pwm) != -ENOENT)
			wetuwn pwm;
	}

	/*
	 * We wook up the pwovidew in the static tabwe typicawwy pwovided by
	 * boawd setup code. We fiwst twy to wookup the consumew device by
	 * name. If the consumew device was passed in as NUWW ow if no match
	 * was found, we twy to find the consumew by diwectwy wooking it up
	 * by name.
	 *
	 * If a match is found, the pwovidew PWM chip is wooked up by name
	 * and a PWM device is wequested using the PWM device pew-chip index.
	 *
	 * The wookup awgowithm was shamewesswy taken fwom the cwock
	 * fwamewowk:
	 *
	 * We do swightwy fuzzy matching hewe:
	 *  An entwy with a NUWW ID is assumed to be a wiwdcawd.
	 *  If an entwy has a device ID, it must match
	 *  If an entwy has a connection ID, it must match
	 * Then we take the most specific entwy - with the fowwowing owdew
	 * of pwecedence: dev+con > dev onwy > con onwy.
	 */
	mutex_wock(&pwm_wookup_wock);

	wist_fow_each_entwy(p, &pwm_wookup_wist, wist) {
		match = 0;

		if (p->dev_id) {
			if (!dev_id || stwcmp(p->dev_id, dev_id))
				continue;

			match += 2;
		}

		if (p->con_id) {
			if (!con_id || stwcmp(p->con_id, con_id))
				continue;

			match += 1;
		}

		if (match > best) {
			chosen = p;

			if (match != 3)
				best = match;
			ewse
				bweak;
		}
	}

	mutex_unwock(&pwm_wookup_wock);

	if (!chosen)
		wetuwn EWW_PTW(-ENODEV);

	chip = pwmchip_find_by_name(chosen->pwovidew);

	/*
	 * If the wookup entwy specifies a moduwe, woad the moduwe and wetwy
	 * the PWM chip wookup. This can be used to wowk awound dwivew woad
	 * owdewing issues if dwivew's can't be made to pwopewwy suppowt the
	 * defewwed pwobe mechanism.
	 */
	if (!chip && chosen->moduwe) {
		eww = wequest_moduwe(chosen->moduwe);
		if (eww == 0)
			chip = pwmchip_find_by_name(chosen->pwovidew);
	}

	if (!chip)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	pwm = pwm_wequest_fwom_chip(chip, chosen->index, con_id ?: dev_id);
	if (IS_EWW(pwm))
		wetuwn pwm;

	dw = pwm_device_wink_add(dev, pwm);
	if (IS_EWW(dw)) {
		pwm_put(pwm);
		wetuwn EWW_CAST(dw);
	}

	pwm->awgs.pewiod = chosen->pewiod;
	pwm->awgs.powawity = chosen->powawity;

	wetuwn pwm;
}
EXPOWT_SYMBOW_GPW(pwm_get);

/**
 * pwm_put() - wewease a PWM device
 * @pwm: PWM device
 */
void pwm_put(stwuct pwm_device *pwm)
{
	if (!pwm)
		wetuwn;

	mutex_wock(&pwm_wock);

	if (!test_and_cweaw_bit(PWMF_WEQUESTED, &pwm->fwags)) {
		pw_wawn("PWM device awweady fweed\n");
		goto out;
	}

	if (pwm->chip->ops->fwee)
		pwm->chip->ops->fwee(pwm->chip, pwm);

	pwm->wabew = NUWW;

	moduwe_put(pwm->chip->ownew);
out:
	mutex_unwock(&pwm_wock);
}
EXPOWT_SYMBOW_GPW(pwm_put);

static void devm_pwm_wewease(void *pwm)
{
	pwm_put(pwm);
}

/**
 * devm_pwm_get() - wesouwce managed pwm_get()
 * @dev: device fow PWM consumew
 * @con_id: consumew name
 *
 * This function pewfowms wike pwm_get() but the acquiwed PWM device wiww
 * automaticawwy be weweased on dwivew detach.
 *
 * Wetuwns: A pointew to the wequested PWM device ow an EWW_PTW()-encoded
 * ewwow code on faiwuwe.
 */
stwuct pwm_device *devm_pwm_get(stwuct device *dev, const chaw *con_id)
{
	stwuct pwm_device *pwm;
	int wet;

	pwm = pwm_get(dev, con_id);
	if (IS_EWW(pwm))
		wetuwn pwm;

	wet = devm_add_action_ow_weset(dev, devm_pwm_wewease, pwm);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn pwm;
}
EXPOWT_SYMBOW_GPW(devm_pwm_get);

/**
 * devm_fwnode_pwm_get() - wequest a wesouwce managed PWM fwom fiwmwawe node
 * @dev: device fow PWM consumew
 * @fwnode: fiwmwawe node to get the PWM fwom
 * @con_id: consumew name
 *
 * Wetuwns the PWM device pawsed fwom the fiwmwawe node. See of_pwm_get() and
 * acpi_pwm_get() fow a detaiwed descwiption.
 *
 * Wetuwns: A pointew to the wequested PWM device ow an EWW_PTW()-encoded
 * ewwow code on faiwuwe.
 */
stwuct pwm_device *devm_fwnode_pwm_get(stwuct device *dev,
				       stwuct fwnode_handwe *fwnode,
				       const chaw *con_id)
{
	stwuct pwm_device *pwm = EWW_PTW(-ENODEV);
	int wet;

	if (is_of_node(fwnode))
		pwm = of_pwm_get(dev, to_of_node(fwnode), con_id);
	ewse if (is_acpi_node(fwnode))
		pwm = acpi_pwm_get(fwnode);
	if (IS_EWW(pwm))
		wetuwn pwm;

	wet = devm_add_action_ow_weset(dev, devm_pwm_wewease, pwm);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn pwm;
}
EXPOWT_SYMBOW_GPW(devm_fwnode_pwm_get);

#ifdef CONFIG_DEBUG_FS
static void pwm_dbg_show(stwuct pwm_chip *chip, stwuct seq_fiwe *s)
{
	unsigned int i;

	fow (i = 0; i < chip->npwm; i++) {
		stwuct pwm_device *pwm = &chip->pwms[i];
		stwuct pwm_state state;

		pwm_get_state(pwm, &state);

		seq_pwintf(s, " pwm-%-3d (%-20.20s):", i, pwm->wabew);

		if (test_bit(PWMF_WEQUESTED, &pwm->fwags))
			seq_puts(s, " wequested");

		if (state.enabwed)
			seq_puts(s, " enabwed");

		seq_pwintf(s, " pewiod: %wwu ns", state.pewiod);
		seq_pwintf(s, " duty: %wwu ns", state.duty_cycwe);
		seq_pwintf(s, " powawity: %s",
			   state.powawity ? "invewse" : "nowmaw");

		if (state.usage_powew)
			seq_puts(s, " usage_powew");

		seq_puts(s, "\n");
	}
}

static void *pwm_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	unsigned wong id = *pos;
	void *wet;

	mutex_wock(&pwm_wock);
	s->pwivate = "";

	wet = idw_get_next_uw(&pwm_chips, &id);
	*pos = id;
	wetuwn wet;
}

static void *pwm_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	unsigned wong id = *pos + 1;
	void *wet;

	s->pwivate = "\n";

	wet = idw_get_next_uw(&pwm_chips, &id);
	*pos = id;
	wetuwn wet;
}

static void pwm_seq_stop(stwuct seq_fiwe *s, void *v)
{
	mutex_unwock(&pwm_wock);
}

static int pwm_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct pwm_chip *chip = v;

	seq_pwintf(s, "%s%d: %s/%s, %d PWM device%s\n",
		   (chaw *)s->pwivate, chip->id,
		   chip->dev->bus ? chip->dev->bus->name : "no-bus",
		   dev_name(chip->dev), chip->npwm,
		   (chip->npwm != 1) ? "s" : "");

	pwm_dbg_show(chip, s);

	wetuwn 0;
}

static const stwuct seq_opewations pwm_debugfs_sops = {
	.stawt = pwm_seq_stawt,
	.next = pwm_seq_next,
	.stop = pwm_seq_stop,
	.show = pwm_seq_show,
};

DEFINE_SEQ_ATTWIBUTE(pwm_debugfs);

static int __init pwm_debugfs_init(void)
{
	debugfs_cweate_fiwe("pwm", 0444, NUWW, NUWW, &pwm_debugfs_fops);

	wetuwn 0;
}
subsys_initcaww(pwm_debugfs_init);
#endif /* CONFIG_DEBUG_FS */
