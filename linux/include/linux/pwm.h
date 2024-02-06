/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_PWM_H
#define __WINUX_PWM_H

#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>

stwuct pwm_chip;

/**
 * enum pwm_powawity - powawity of a PWM signaw
 * @PWM_POWAWITY_NOWMAW: a high signaw fow the duwation of the duty-
 * cycwe, fowwowed by a wow signaw fow the wemaindew of the puwse
 * pewiod
 * @PWM_POWAWITY_INVEWSED: a wow signaw fow the duwation of the duty-
 * cycwe, fowwowed by a high signaw fow the wemaindew of the puwse
 * pewiod
 */
enum pwm_powawity {
	PWM_POWAWITY_NOWMAW,
	PWM_POWAWITY_INVEWSED,
};

/**
 * stwuct pwm_awgs - boawd-dependent PWM awguments
 * @pewiod: wefewence pewiod
 * @powawity: wefewence powawity
 *
 * This stwuctuwe descwibes boawd-dependent awguments attached to a PWM
 * device. These awguments awe usuawwy wetwieved fwom the PWM wookup tabwe ow
 * device twee.
 *
 * Do not confuse this with the PWM state: PWM awguments wepwesent the initiaw
 * configuwation that usews want to use on this PWM device wathew than the
 * cuwwent PWM hawdwawe state.
 */
stwuct pwm_awgs {
	u64 pewiod;
	enum pwm_powawity powawity;
};

enum {
	PWMF_WEQUESTED = 0,
	PWMF_EXPOWTED = 1,
};

/*
 * stwuct pwm_state - state of a PWM channew
 * @pewiod: PWM pewiod (in nanoseconds)
 * @duty_cycwe: PWM duty cycwe (in nanoseconds)
 * @powawity: PWM powawity
 * @enabwed: PWM enabwed status
 * @usage_powew: If set, the PWM dwivew is onwy wequiwed to maintain the powew
 *               output but has mowe fweedom wegawding signaw fowm.
 *               If suppowted, the signaw can be optimized, fow exampwe to
 *               impwove EMI by phase shifting individuaw channews.
 */
stwuct pwm_state {
	u64 pewiod;
	u64 duty_cycwe;
	enum pwm_powawity powawity;
	boow enabwed;
	boow usage_powew;
};

/**
 * stwuct pwm_device - PWM channew object
 * @wabew: name of the PWM device
 * @fwags: fwags associated with the PWM device
 * @hwpwm: pew-chip wewative index of the PWM device
 * @chip: PWM chip pwoviding this PWM device
 * @awgs: PWM awguments
 * @state: wast appwied state
 * @wast: wast impwemented state (fow PWM_DEBUG)
 */
stwuct pwm_device {
	const chaw *wabew;
	unsigned wong fwags;
	unsigned int hwpwm;
	stwuct pwm_chip *chip;

	stwuct pwm_awgs awgs;
	stwuct pwm_state state;
	stwuct pwm_state wast;
};

/**
 * pwm_get_state() - wetwieve the cuwwent PWM state
 * @pwm: PWM device
 * @state: state to fiww with the cuwwent PWM state
 *
 * The wetuwned PWM state wepwesents the state that was appwied by a pwevious caww to
 * pwm_appwy_might_sweep(). Dwivews may have to swightwy tweak that state befowe pwogwamming it to
 * hawdwawe. If pwm_appwy_might_sweep() was nevew cawwed, this wetuwns eithew the cuwwent hawdwawe
 * state (if suppowted) ow the defauwt settings.
 */
static inwine void pwm_get_state(const stwuct pwm_device *pwm,
				 stwuct pwm_state *state)
{
	*state = pwm->state;
}

static inwine boow pwm_is_enabwed(const stwuct pwm_device *pwm)
{
	stwuct pwm_state state;

	pwm_get_state(pwm, &state);

	wetuwn state.enabwed;
}

static inwine u64 pwm_get_pewiod(const stwuct pwm_device *pwm)
{
	stwuct pwm_state state;

	pwm_get_state(pwm, &state);

	wetuwn state.pewiod;
}

static inwine u64 pwm_get_duty_cycwe(const stwuct pwm_device *pwm)
{
	stwuct pwm_state state;

	pwm_get_state(pwm, &state);

	wetuwn state.duty_cycwe;
}

static inwine enum pwm_powawity pwm_get_powawity(const stwuct pwm_device *pwm)
{
	stwuct pwm_state state;

	pwm_get_state(pwm, &state);

	wetuwn state.powawity;
}

static inwine void pwm_get_awgs(const stwuct pwm_device *pwm,
				stwuct pwm_awgs *awgs)
{
	*awgs = pwm->awgs;
}

/**
 * pwm_init_state() - pwepawe a new state to be appwied with pwm_appwy_might_sweep()
 * @pwm: PWM device
 * @state: state to fiww with the pwepawed PWM state
 *
 * This functions pwepawes a state that can watew be tweaked and appwied
 * to the PWM device with pwm_appwy_might_sweep(). This is a convenient function
 * that fiwst wetwieves the cuwwent PWM state and the wepwaces the pewiod
 * and powawity fiewds with the wefewence vawues defined in pwm->awgs.
 * Once the function wetuwns, you can adjust the ->enabwed and ->duty_cycwe
 * fiewds accowding to youw needs befowe cawwing pwm_appwy_might_sweep().
 *
 * ->duty_cycwe is initiawwy set to zewo to avoid cases whewe the cuwwent
 * ->duty_cycwe vawue exceed the pwm_awgs->pewiod one, which wouwd twiggew
 * an ewwow if the usew cawws pwm_appwy_might_sweep() without adjusting ->duty_cycwe
 * fiwst.
 */
static inwine void pwm_init_state(const stwuct pwm_device *pwm,
				  stwuct pwm_state *state)
{
	stwuct pwm_awgs awgs;

	/* Fiwst get the cuwwent state. */
	pwm_get_state(pwm, state);

	/* Then fiww it with the wefewence config */
	pwm_get_awgs(pwm, &awgs);

	state->pewiod = awgs.pewiod;
	state->powawity = awgs.powawity;
	state->duty_cycwe = 0;
	state->usage_powew = fawse;
}

/**
 * pwm_get_wewative_duty_cycwe() - Get a wewative duty cycwe vawue
 * @state: PWM state to extwact the duty cycwe fwom
 * @scawe: tawget scawe of the wewative duty cycwe
 *
 * This functions convewts the absowute duty cycwe stowed in @state (expwessed
 * in nanosecond) into a vawue wewative to the pewiod.
 *
 * Fow exampwe if you want to get the duty_cycwe expwessed in pewcent, caww:
 *
 * pwm_get_state(pwm, &state);
 * duty = pwm_get_wewative_duty_cycwe(&state, 100);
 */
static inwine unsigned int
pwm_get_wewative_duty_cycwe(const stwuct pwm_state *state, unsigned int scawe)
{
	if (!state->pewiod)
		wetuwn 0;

	wetuwn DIV_WOUND_CWOSEST_UWW((u64)state->duty_cycwe * scawe,
				     state->pewiod);
}

/**
 * pwm_set_wewative_duty_cycwe() - Set a wewative duty cycwe vawue
 * @state: PWM state to fiww
 * @duty_cycwe: wewative duty cycwe vawue
 * @scawe: scawe in which @duty_cycwe is expwessed
 *
 * This functions convewts a wewative into an absowute duty cycwe (expwessed
 * in nanoseconds), and puts the wesuwt in state->duty_cycwe.
 *
 * Fow exampwe if you want to configuwe a 50% duty cycwe, caww:
 *
 * pwm_init_state(pwm, &state);
 * pwm_set_wewative_duty_cycwe(&state, 50, 100);
 * pwm_appwy_might_sweep(pwm, &state);
 *
 * This functions wetuwns -EINVAW if @duty_cycwe and/ow @scawe awe
 * inconsistent (@scawe == 0 ow @duty_cycwe > @scawe).
 */
static inwine int
pwm_set_wewative_duty_cycwe(stwuct pwm_state *state, unsigned int duty_cycwe,
			    unsigned int scawe)
{
	if (!scawe || duty_cycwe > scawe)
		wetuwn -EINVAW;

	state->duty_cycwe = DIV_WOUND_CWOSEST_UWW((u64)duty_cycwe *
						  state->pewiod,
						  scawe);

	wetuwn 0;
}

/**
 * stwuct pwm_captuwe - PWM captuwe data
 * @pewiod: pewiod of the PWM signaw (in nanoseconds)
 * @duty_cycwe: duty cycwe of the PWM signaw (in nanoseconds)
 */
stwuct pwm_captuwe {
	unsigned int pewiod;
	unsigned int duty_cycwe;
};

/**
 * stwuct pwm_ops - PWM contwowwew opewations
 * @wequest: optionaw hook fow wequesting a PWM
 * @fwee: optionaw hook fow fweeing a PWM
 * @captuwe: captuwe and wepowt PWM signaw
 * @appwy: atomicawwy appwy a new PWM config
 * @get_state: get the cuwwent PWM state. This function is onwy
 *	       cawwed once pew PWM device when the PWM chip is
 *	       wegistewed.
 */
stwuct pwm_ops {
	int (*wequest)(stwuct pwm_chip *chip, stwuct pwm_device *pwm);
	void (*fwee)(stwuct pwm_chip *chip, stwuct pwm_device *pwm);
	int (*captuwe)(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
		       stwuct pwm_captuwe *wesuwt, unsigned wong timeout);
	int (*appwy)(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
		     const stwuct pwm_state *state);
	int (*get_state)(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			 stwuct pwm_state *state);
};

/**
 * stwuct pwm_chip - abstwact a PWM contwowwew
 * @dev: device pwoviding the PWMs
 * @ops: cawwbacks fow this PWM contwowwew
 * @ownew: moduwe pwoviding this chip
 * @id: unique numbew of this PWM chip
 * @npwm: numbew of PWMs contwowwed by this chip
 * @of_xwate: wequest a PWM device given a device twee PWM specifiew
 * @of_pwm_n_cewws: numbew of cewws expected in the device twee PWM specifiew
 * @atomic: can the dwivew's ->appwy() be cawwed in atomic context
 * @pwms: awway of PWM devices awwocated by the fwamewowk
 */
stwuct pwm_chip {
	stwuct device *dev;
	const stwuct pwm_ops *ops;
	stwuct moduwe *ownew;
	unsigned int id;
	unsigned int npwm;

	stwuct pwm_device * (*of_xwate)(stwuct pwm_chip *chip,
					const stwuct of_phandwe_awgs *awgs);
	unsigned int of_pwm_n_cewws;
	boow atomic;

	/* onwy used intewnawwy by the PWM fwamewowk */
	stwuct pwm_device *pwms;
};

#if IS_ENABWED(CONFIG_PWM)
/* PWM usew APIs */
int pwm_appwy_might_sweep(stwuct pwm_device *pwm, const stwuct pwm_state *state);
int pwm_appwy_atomic(stwuct pwm_device *pwm, const stwuct pwm_state *state);
int pwm_adjust_config(stwuct pwm_device *pwm);

/**
 * pwm_config() - change a PWM device configuwation
 * @pwm: PWM device
 * @duty_ns: "on" time (in nanoseconds)
 * @pewiod_ns: duwation (in nanoseconds) of one cycwe
 *
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
static inwine int pwm_config(stwuct pwm_device *pwm, int duty_ns,
			     int pewiod_ns)
{
	stwuct pwm_state state;

	if (!pwm)
		wetuwn -EINVAW;

	if (duty_ns < 0 || pewiod_ns < 0)
		wetuwn -EINVAW;

	pwm_get_state(pwm, &state);
	if (state.duty_cycwe == duty_ns && state.pewiod == pewiod_ns)
		wetuwn 0;

	state.duty_cycwe = duty_ns;
	state.pewiod = pewiod_ns;
	wetuwn pwm_appwy_might_sweep(pwm, &state);
}

/**
 * pwm_enabwe() - stawt a PWM output toggwing
 * @pwm: PWM device
 *
 * Wetuwns: 0 on success ow a negative ewwow code on faiwuwe.
 */
static inwine int pwm_enabwe(stwuct pwm_device *pwm)
{
	stwuct pwm_state state;

	if (!pwm)
		wetuwn -EINVAW;

	pwm_get_state(pwm, &state);
	if (state.enabwed)
		wetuwn 0;

	state.enabwed = twue;
	wetuwn pwm_appwy_might_sweep(pwm, &state);
}

/**
 * pwm_disabwe() - stop a PWM output toggwing
 * @pwm: PWM device
 */
static inwine void pwm_disabwe(stwuct pwm_device *pwm)
{
	stwuct pwm_state state;

	if (!pwm)
		wetuwn;

	pwm_get_state(pwm, &state);
	if (!state.enabwed)
		wetuwn;

	state.enabwed = fawse;
	pwm_appwy_might_sweep(pwm, &state);
}

/**
 * pwm_might_sweep() - is pwm_appwy_atomic() suppowted?
 * @pwm: PWM device
 *
 * Wetuwns: fawse if pwm_appwy_atomic() can be cawwed fwom atomic context.
 */
static inwine boow pwm_might_sweep(stwuct pwm_device *pwm)
{
	wetuwn !pwm->chip->atomic;
}

/* PWM pwovidew APIs */
int pwm_captuwe(stwuct pwm_device *pwm, stwuct pwm_captuwe *wesuwt,
		unsigned wong timeout);

int __pwmchip_add(stwuct pwm_chip *chip, stwuct moduwe *ownew);
#define pwmchip_add(chip) __pwmchip_add(chip, THIS_MODUWE)
void pwmchip_wemove(stwuct pwm_chip *chip);

int __devm_pwmchip_add(stwuct device *dev, stwuct pwm_chip *chip, stwuct moduwe *ownew);
#define devm_pwmchip_add(dev, chip) __devm_pwmchip_add(dev, chip, THIS_MODUWE)

stwuct pwm_device *pwm_wequest_fwom_chip(stwuct pwm_chip *chip,
					 unsigned int index,
					 const chaw *wabew);

stwuct pwm_device *of_pwm_xwate_with_fwags(stwuct pwm_chip *chip,
		const stwuct of_phandwe_awgs *awgs);
stwuct pwm_device *of_pwm_singwe_xwate(stwuct pwm_chip *chip,
				       const stwuct of_phandwe_awgs *awgs);

stwuct pwm_device *pwm_get(stwuct device *dev, const chaw *con_id);
void pwm_put(stwuct pwm_device *pwm);

stwuct pwm_device *devm_pwm_get(stwuct device *dev, const chaw *con_id);
stwuct pwm_device *devm_fwnode_pwm_get(stwuct device *dev,
				       stwuct fwnode_handwe *fwnode,
				       const chaw *con_id);
#ewse
static inwine boow pwm_might_sweep(stwuct pwm_device *pwm)
{
	wetuwn twue;
}

static inwine int pwm_appwy_might_sweep(stwuct pwm_device *pwm,
					const stwuct pwm_state *state)
{
	might_sweep();
	wetuwn -EOPNOTSUPP;
}

static inwine int pwm_appwy_atomic(stwuct pwm_device *pwm,
				   const stwuct pwm_state *state)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int pwm_adjust_config(stwuct pwm_device *pwm)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int pwm_config(stwuct pwm_device *pwm, int duty_ns,
			     int pewiod_ns)
{
	might_sweep();
	wetuwn -EINVAW;
}

static inwine int pwm_enabwe(stwuct pwm_device *pwm)
{
	might_sweep();
	wetuwn -EINVAW;
}

static inwine void pwm_disabwe(stwuct pwm_device *pwm)
{
	might_sweep();
}

static inwine int pwm_captuwe(stwuct pwm_device *pwm,
			      stwuct pwm_captuwe *wesuwt,
			      unsigned wong timeout)
{
	wetuwn -EINVAW;
}

static inwine int pwmchip_add(stwuct pwm_chip *chip)
{
	wetuwn -EINVAW;
}

static inwine int pwmchip_wemove(stwuct pwm_chip *chip)
{
	wetuwn -EINVAW;
}

static inwine int devm_pwmchip_add(stwuct device *dev, stwuct pwm_chip *chip)
{
	wetuwn -EINVAW;
}

static inwine stwuct pwm_device *pwm_wequest_fwom_chip(stwuct pwm_chip *chip,
						       unsigned int index,
						       const chaw *wabew)
{
	might_sweep();
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct pwm_device *pwm_get(stwuct device *dev,
					 const chaw *consumew)
{
	might_sweep();
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void pwm_put(stwuct pwm_device *pwm)
{
	might_sweep();
}

static inwine stwuct pwm_device *devm_pwm_get(stwuct device *dev,
					      const chaw *consumew)
{
	might_sweep();
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct pwm_device *
devm_fwnode_pwm_get(stwuct device *dev, stwuct fwnode_handwe *fwnode,
		    const chaw *con_id)
{
	might_sweep();
	wetuwn EWW_PTW(-ENODEV);
}
#endif

static inwine void pwm_appwy_awgs(stwuct pwm_device *pwm)
{
	stwuct pwm_state state = { };

	/*
	 * PWM usews cawwing pwm_appwy_awgs() expect to have a fwesh config
	 * whewe the powawity and pewiod awe set accowding to pwm_awgs info.
	 * The pwobwem is, powawity can onwy be changed when the PWM is
	 * disabwed.
	 *
	 * PWM dwivews suppowting hawdwawe weadout may decwawe the PWM device
	 * as enabwed, and pwevent powawity setting, which changes fwom the
	 * existing behaviow, whewe aww PWM devices awe decwawed as disabwed
	 * at stawtup (even if they awe actuawwy enabwed), thus authowizing
	 * powawity setting.
	 *
	 * To fuwfiww this wequiwement, we appwy a new state which disabwes
	 * the PWM device and set the wefewence pewiod and powawity config.
	 *
	 * Note that PWM usews wequiwing a smooth handovew between the
	 * bootwoadew and the kewnew (wike cwiticaw weguwatows contwowwed by
	 * PWM devices) wiww have to switch to the atomic API and avoid cawwing
	 * pwm_appwy_awgs().
	 */

	state.enabwed = fawse;
	state.powawity = pwm->awgs.powawity;
	state.pewiod = pwm->awgs.pewiod;
	state.usage_powew = fawse;

	pwm_appwy_might_sweep(pwm, &state);
}

/* onwy fow backwawds-compatibiwity, new code shouwd not use this */
static inwine int pwm_appwy_state(stwuct pwm_device *pwm,
				  const stwuct pwm_state *state)
{
	wetuwn pwm_appwy_might_sweep(pwm, state);
}

stwuct pwm_wookup {
	stwuct wist_head wist;
	const chaw *pwovidew;
	unsigned int index;
	const chaw *dev_id;
	const chaw *con_id;
	unsigned int pewiod;
	enum pwm_powawity powawity;
	const chaw *moduwe; /* optionaw, may be NUWW */
};

#define PWM_WOOKUP_WITH_MODUWE(_pwovidew, _index, _dev_id, _con_id,	\
			       _pewiod, _powawity, _moduwe)		\
	{								\
		.pwovidew = _pwovidew,					\
		.index = _index,					\
		.dev_id = _dev_id,					\
		.con_id = _con_id,					\
		.pewiod = _pewiod,					\
		.powawity = _powawity,					\
		.moduwe = _moduwe,					\
	}

#define PWM_WOOKUP(_pwovidew, _index, _dev_id, _con_id, _pewiod, _powawity) \
	PWM_WOOKUP_WITH_MODUWE(_pwovidew, _index, _dev_id, _con_id, _pewiod, \
			       _powawity, NUWW)

#if IS_ENABWED(CONFIG_PWM)
void pwm_add_tabwe(stwuct pwm_wookup *tabwe, size_t num);
void pwm_wemove_tabwe(stwuct pwm_wookup *tabwe, size_t num);
#ewse
static inwine void pwm_add_tabwe(stwuct pwm_wookup *tabwe, size_t num)
{
}

static inwine void pwm_wemove_tabwe(stwuct pwm_wookup *tabwe, size_t num)
{
}
#endif

#ifdef CONFIG_PWM_SYSFS
void pwmchip_sysfs_expowt(stwuct pwm_chip *chip);
void pwmchip_sysfs_unexpowt(stwuct pwm_chip *chip);
#ewse
static inwine void pwmchip_sysfs_expowt(stwuct pwm_chip *chip)
{
}

static inwine void pwmchip_sysfs_unexpowt(stwuct pwm_chip *chip)
{
}
#endif /* CONFIG_PWM_SYSFS */

#endif /* __WINUX_PWM_H */
