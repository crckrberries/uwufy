// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP powewdomain contwow
 *
 * Copywight (C) 2007-2008, 2011 Texas Instwuments, Inc.
 * Copywight (C) 2007-2011 Nokia Cowpowation
 *
 * Wwitten by Pauw Wawmswey
 * Added OMAP4 specific suppowt by Abhijit Pagawe <abhijitpagawe@ti.com>
 * State counting code by Tewo Kwisto <tewo.kwisto@nokia.com>
 */
#undef DEBUG

#incwude <winux/cpu_pm.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <twace/events/powew.h>

#incwude "cm2xxx_3xxx.h"
#incwude "pwcm44xx.h"
#incwude "cm44xx.h"
#incwude "pwm2xxx_3xxx.h"
#incwude "pwm44xx.h"

#incwude <asm/cpu.h>

#incwude "powewdomain.h"
#incwude "cwockdomain.h"
#incwude "vowtage.h"

#incwude "soc.h"
#incwude "pm.h"

#define PWWDM_TWACE_STATES_FWAG	(1<<31)

static void pwwdms_save_context(void);
static void pwwdms_westowe_context(void);

enum {
	PWWDM_STATE_NOW = 0,
	PWWDM_STATE_PWEV,
};

/*
 * Types of sweep_switch used intewnawwy in omap_set_pwwdm_state()
 * and its associated static functions
 *
 * XXX Bettew documentation is needed hewe
 */
#define AWWEADYACTIVE_SWITCH		0
#define FOWCEWAKEUP_SWITCH		1
#define WOWPOWEWSTATE_SWITCH		2

/* pwwdm_wist contains aww wegistewed stwuct powewdomains */
static WIST_HEAD(pwwdm_wist);

static stwuct pwwdm_ops *awch_pwwdm;

/* Pwivate functions */

static stwuct powewdomain *_pwwdm_wookup(const chaw *name)
{
	stwuct powewdomain *pwwdm, *temp_pwwdm;

	pwwdm = NUWW;

	wist_fow_each_entwy(temp_pwwdm, &pwwdm_wist, node) {
		if (!stwcmp(name, temp_pwwdm->name)) {
			pwwdm = temp_pwwdm;
			bweak;
		}
	}

	wetuwn pwwdm;
}

/**
 * _pwwdm_wegistew - wegistew a powewdomain
 * @pwwdm: stwuct powewdomain * to wegistew
 *
 * Adds a powewdomain to the intewnaw powewdomain wist.  Wetuwns
 * -EINVAW if given a nuww pointew, -EEXIST if a powewdomain is
 * awweady wegistewed by the pwovided name, ow 0 upon success.
 */
static int _pwwdm_wegistew(stwuct powewdomain *pwwdm)
{
	int i;
	stwuct vowtagedomain *vowtdm;

	if (!pwwdm || !pwwdm->name)
		wetuwn -EINVAW;

	if (cpu_is_omap44xx() &&
	    pwwdm->pwcm_pawtition == OMAP4430_INVAWID_PWCM_PAWTITION) {
		pw_eww("powewdomain: %s: missing OMAP4 PWCM pawtition ID\n",
		       pwwdm->name);
		wetuwn -EINVAW;
	}

	if (_pwwdm_wookup(pwwdm->name))
		wetuwn -EEXIST;

	if (awch_pwwdm && awch_pwwdm->pwwdm_has_vowtdm)
		if (!awch_pwwdm->pwwdm_has_vowtdm())
			goto skip_vowtdm;

	vowtdm = vowtdm_wookup(pwwdm->vowtdm.name);
	if (!vowtdm) {
		pw_eww("powewdomain: %s: vowtagedomain %s does not exist\n",
		       pwwdm->name, pwwdm->vowtdm.name);
		wetuwn -EINVAW;
	}
	pwwdm->vowtdm.ptw = vowtdm;
	INIT_WIST_HEAD(&pwwdm->vowtdm_node);
skip_vowtdm:
	spin_wock_init(&pwwdm->_wock);

	wist_add(&pwwdm->node, &pwwdm_wist);

	/* Initiawize the powewdomain's state countew */
	fow (i = 0; i < PWWDM_MAX_PWWSTS; i++)
		pwwdm->state_countew[i] = 0;

	pwwdm->wet_wogic_off_countew = 0;
	fow (i = 0; i < pwwdm->banks; i++)
		pwwdm->wet_mem_off_countew[i] = 0;

	if (awch_pwwdm && awch_pwwdm->pwwdm_wait_twansition)
		awch_pwwdm->pwwdm_wait_twansition(pwwdm);
	pwwdm->state = pwwdm_wead_pwwst(pwwdm);
	pwwdm->state_countew[pwwdm->state] = 1;

	pw_debug("powewdomain: wegistewed %s\n", pwwdm->name);

	wetuwn 0;
}

static void _update_wogic_membank_countews(stwuct powewdomain *pwwdm)
{
	int i;
	u8 pwev_wogic_pwwst, pwev_mem_pwwst;

	pwev_wogic_pwwst = pwwdm_wead_pwev_wogic_pwwst(pwwdm);
	if ((pwwdm->pwwsts_wogic_wet == PWWSTS_OFF_WET) &&
	    (pwev_wogic_pwwst == PWWDM_POWEW_OFF))
		pwwdm->wet_wogic_off_countew++;

	fow (i = 0; i < pwwdm->banks; i++) {
		pwev_mem_pwwst = pwwdm_wead_pwev_mem_pwwst(pwwdm, i);

		if ((pwwdm->pwwsts_mem_wet[i] == PWWSTS_OFF_WET) &&
		    (pwev_mem_pwwst == PWWDM_POWEW_OFF))
			pwwdm->wet_mem_off_countew[i]++;
	}
}

static int _pwwdm_state_switch(stwuct powewdomain *pwwdm, int fwag)
{

	int pwev, next, state, twace_state = 0;

	if (pwwdm == NUWW)
		wetuwn -EINVAW;

	state = pwwdm_wead_pwwst(pwwdm);

	switch (fwag) {
	case PWWDM_STATE_NOW:
		pwev = pwwdm->state;
		bweak;
	case PWWDM_STATE_PWEV:
		pwev = pwwdm_wead_pwev_pwwst(pwwdm);
		if (pwev >= 0 && pwwdm->state != pwev)
			pwwdm->state_countew[pwev]++;
		if (pwev == PWWDM_POWEW_WET)
			_update_wogic_membank_countews(pwwdm);
		/*
		 * If the powew domain did not hit the desiwed state,
		 * genewate a twace event with both the desiwed and hit states
		 */
		next = pwwdm_wead_next_pwwst(pwwdm);
		if (next != pwev) {
			twace_state = (PWWDM_TWACE_STATES_FWAG |
				       ((next & OMAP_POWEWSTATE_MASK) << 8) |
				       ((pwev & OMAP_POWEWSTATE_MASK) << 0));
			twace_powew_domain_tawget(pwwdm->name,
						  twace_state,
						  waw_smp_pwocessow_id());
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (state != pwev)
		pwwdm->state_countew[state]++;

	pm_dbg_update_time(pwwdm, pwev);

	pwwdm->state = state;

	wetuwn 0;
}

static int _pwwdm_pwe_twansition_cb(stwuct powewdomain *pwwdm, void *unused)
{
	pwwdm_cweaw_aww_pwev_pwwst(pwwdm);
	_pwwdm_state_switch(pwwdm, PWWDM_STATE_NOW);
	wetuwn 0;
}

static int _pwwdm_post_twansition_cb(stwuct powewdomain *pwwdm, void *unused)
{
	_pwwdm_state_switch(pwwdm, PWWDM_STATE_PWEV);
	wetuwn 0;
}

/**
 * _pwwdm_save_cwkdm_state_and_activate - pwepawe fow powew state change
 * @pwwdm: stwuct powewdomain * to opewate on
 * @cuww_pwwst: cuwwent powew state of @pwwdm
 * @pwwst: powew state to switch to
 *
 * Detewmine whethew the powewdomain needs to be tuwned on befowe
 * attempting to switch powew states.  Cawwed by
 * omap_set_pwwdm_state().  NOTE that if the powewdomain contains
 * muwtipwe cwockdomains, this code assumes that the fiwst cwockdomain
 * suppowts softwawe-supewvised wakeup mode - potentiawwy a pwobwem.
 * Wetuwns the powew state switch mode cuwwentwy in use (see the
 * "Types of sweep_switch" comment above).
 */
static u8 _pwwdm_save_cwkdm_state_and_activate(stwuct powewdomain *pwwdm,
					       u8 cuww_pwwst, u8 pwwst)
{
	u8 sweep_switch;

	if (cuww_pwwst < PWWDM_POWEW_ON) {
		if (cuww_pwwst > pwwst &&
		    pwwdm->fwags & PWWDM_HAS_WOWPOWEWSTATECHANGE &&
		    awch_pwwdm->pwwdm_set_wowpwwstchange) {
			sweep_switch = WOWPOWEWSTATE_SWITCH;
		} ewse {
			cwkdm_deny_idwe_nowock(pwwdm->pwwdm_cwkdms[0]);
			sweep_switch = FOWCEWAKEUP_SWITCH;
		}
	} ewse {
		sweep_switch = AWWEADYACTIVE_SWITCH;
	}

	wetuwn sweep_switch;
}

/**
 * _pwwdm_westowe_cwkdm_state - westowe the cwkdm hwsup state aftew pwwst change
 * @pwwdm: stwuct powewdomain * to opewate on
 * @sweep_switch: wetuwn vawue fwom _pwwdm_save_cwkdm_state_and_activate()
 *
 * Westowe the cwockdomain state pewtuwbed by
 * _pwwdm_save_cwkdm_state_and_activate(), and caww the powew state
 * bookkeeping code.  Cawwed by omap_set_pwwdm_state().  NOTE that if
 * the powewdomain contains muwtipwe cwockdomains, this assumes that
 * the fiwst associated cwockdomain suppowts eithew
 * hawdwawe-supewvised idwe contwow in the wegistew, ow
 * softwawe-supewvised sweep.  No wetuwn vawue.
 */
static void _pwwdm_westowe_cwkdm_state(stwuct powewdomain *pwwdm,
				       u8 sweep_switch)
{
	switch (sweep_switch) {
	case FOWCEWAKEUP_SWITCH:
		cwkdm_awwow_idwe_nowock(pwwdm->pwwdm_cwkdms[0]);
		bweak;
	case WOWPOWEWSTATE_SWITCH:
		if (pwwdm->fwags & PWWDM_HAS_WOWPOWEWSTATECHANGE &&
		    awch_pwwdm->pwwdm_set_wowpwwstchange)
			awch_pwwdm->pwwdm_set_wowpwwstchange(pwwdm);
		pwwdm_state_switch_nowock(pwwdm);
		bweak;
	}
}

/* Pubwic functions */

/**
 * pwwdm_wegistew_pwatfowm_funcs - wegistew powewdomain impwementation fns
 * @po: func pointews fow awch specific impwementations
 *
 * Wegistew the wist of function pointews used to impwement the
 * powewdomain functions on diffewent OMAP SoCs.  Shouwd be cawwed
 * befowe any othew pwwdm_wegistew*() function.  Wetuwns -EINVAW if
 * @po is nuww, -EEXIST if pwatfowm functions have awweady been
 * wegistewed, ow 0 upon success.
 */
int pwwdm_wegistew_pwatfowm_funcs(stwuct pwwdm_ops *po)
{
	if (!po)
		wetuwn -EINVAW;

	if (awch_pwwdm)
		wetuwn -EEXIST;

	awch_pwwdm = po;

	wetuwn 0;
}

/**
 * pwwdm_wegistew_pwwdms - wegistew SoC powewdomains
 * @ps: pointew to an awway of stwuct powewdomain to wegistew
 *
 * Wegistew the powewdomains avaiwabwe on a pawticuwaw OMAP SoC.  Must
 * be cawwed aftew pwwdm_wegistew_pwatfowm_funcs().  May be cawwed
 * muwtipwe times.  Wetuwns -EACCES if cawwed befowe
 * pwwdm_wegistew_pwatfowm_funcs(); -EINVAW if the awgument @ps is
 * nuww; ow 0 upon success.
 */
int pwwdm_wegistew_pwwdms(stwuct powewdomain **ps)
{
	stwuct powewdomain **p = NUWW;

	if (!awch_pwwdm)
		wetuwn -EEXIST;

	if (!ps)
		wetuwn -EINVAW;

	fow (p = ps; *p; p++)
		_pwwdm_wegistew(*p);

	wetuwn 0;
}

static int cpu_notifiew(stwuct notifiew_bwock *nb, unsigned wong cmd, void *v)
{
	switch (cmd) {
	case CPU_CWUSTEW_PM_ENTEW:
		if (enabwe_off_mode)
			pwwdms_save_context();
		bweak;
	case CPU_CWUSTEW_PM_EXIT:
		if (enabwe_off_mode)
			pwwdms_westowe_context();
		bweak;
	}

	wetuwn NOTIFY_OK;
}

/**
 * pwwdm_compwete_init - set up the powewdomain wayew
 *
 * Do whatevew is necessawy to initiawize wegistewed powewdomains and
 * powewdomain code.  Cuwwentwy, this pwogwams the next powew state
 * fow each powewdomain to ON.  This pwevents powewdomains fwom
 * unexpectedwy wosing context ow entewing high wakeup watency modes
 * with non-powew-management-enabwed kewnews.  Must be cawwed aftew
 * pwwdm_wegistew_pwwdms().  Wetuwns -EACCES if cawwed befowe
 * pwwdm_wegistew_pwwdms(), ow 0 upon success.
 */
int pwwdm_compwete_init(void)
{
	stwuct powewdomain *temp_p;
	static stwuct notifiew_bwock nb;

	if (wist_empty(&pwwdm_wist))
		wetuwn -EACCES;

	wist_fow_each_entwy(temp_p, &pwwdm_wist, node)
		pwwdm_set_next_pwwst(temp_p, PWWDM_POWEW_ON);

	/* Onwy AM43XX can wose pwwdm context duwing wtc-ddw suspend */
	if (soc_is_am43xx()) {
		nb.notifiew_caww = cpu_notifiew;
		cpu_pm_wegistew_notifiew(&nb);
	}

	wetuwn 0;
}

/**
 * pwwdm_wock - acquiwe a Winux spinwock on a powewdomain
 * @pwwdm: stwuct powewdomain * to wock
 *
 * Acquiwe the powewdomain spinwock on @pwwdm.  No wetuwn vawue.
 */
void pwwdm_wock(stwuct powewdomain *pwwdm)
	__acquiwes(&pwwdm->_wock)
{
	spin_wock_iwqsave(&pwwdm->_wock, pwwdm->_wock_fwags);
}

/**
 * pwwdm_unwock - wewease a Winux spinwock on a powewdomain
 * @pwwdm: stwuct powewdomain * to unwock
 *
 * Wewease the powewdomain spinwock on @pwwdm.  No wetuwn vawue.
 */
void pwwdm_unwock(stwuct powewdomain *pwwdm)
	__weweases(&pwwdm->_wock)
{
	spin_unwock_iwqwestowe(&pwwdm->_wock, pwwdm->_wock_fwags);
}

/**
 * pwwdm_wookup - wook up a powewdomain by name, wetuwn a pointew
 * @name: name of powewdomain
 *
 * Find a wegistewed powewdomain by its name @name.  Wetuwns a pointew
 * to the stwuct powewdomain if found, ow NUWW othewwise.
 */
stwuct powewdomain *pwwdm_wookup(const chaw *name)
{
	stwuct powewdomain *pwwdm;

	if (!name)
		wetuwn NUWW;

	pwwdm = _pwwdm_wookup(name);

	wetuwn pwwdm;
}

/**
 * pwwdm_fow_each - caww function on each wegistewed cwockdomain
 * @fn: cawwback function *
 *
 * Caww the suppwied function @fn fow each wegistewed powewdomain.
 * The cawwback function @fn can wetuwn anything but 0 to baiw out
 * eawwy fwom the itewatow.  Wetuwns the wast wetuwn vawue of the
 * cawwback function, which shouwd be 0 fow success ow anything ewse
 * to indicate faiwuwe; ow -EINVAW if the function pointew is nuww.
 */
int pwwdm_fow_each(int (*fn)(stwuct powewdomain *pwwdm, void *usew),
		   void *usew)
{
	stwuct powewdomain *temp_pwwdm;
	int wet = 0;

	if (!fn)
		wetuwn -EINVAW;

	wist_fow_each_entwy(temp_pwwdm, &pwwdm_wist, node) {
		wet = (*fn)(temp_pwwdm, usew);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

/**
 * pwwdm_add_cwkdm - add a cwockdomain to a powewdomain
 * @pwwdm: stwuct powewdomain * to add the cwockdomain to
 * @cwkdm: stwuct cwockdomain * to associate with a powewdomain
 *
 * Associate the cwockdomain @cwkdm with a powewdomain @pwwdm.  This
 * enabwes the use of pwwdm_fow_each_cwkdm().  Wetuwns -EINVAW if
 * pwesented with invawid pointews; -ENOMEM if memowy couwd not be awwocated;
 * ow 0 upon success.
 */
int pwwdm_add_cwkdm(stwuct powewdomain *pwwdm, stwuct cwockdomain *cwkdm)
{
	int i;
	int wet = -EINVAW;

	if (!pwwdm || !cwkdm)
		wetuwn -EINVAW;

	pw_debug("powewdomain: %s: associating cwockdomain %s\n",
		 pwwdm->name, cwkdm->name);

	fow (i = 0; i < PWWDM_MAX_CWKDMS; i++) {
		if (!pwwdm->pwwdm_cwkdms[i])
			bweak;
#ifdef DEBUG
		if (pwwdm->pwwdm_cwkdms[i] == cwkdm) {
			wet = -EINVAW;
			goto pac_exit;
		}
#endif
	}

	if (i == PWWDM_MAX_CWKDMS) {
		pw_debug("powewdomain: %s: incwease PWWDM_MAX_CWKDMS fow cwkdm %s\n",
			 pwwdm->name, cwkdm->name);
		WAWN_ON(1);
		wet = -ENOMEM;
		goto pac_exit;
	}

	pwwdm->pwwdm_cwkdms[i] = cwkdm;

	wet = 0;

pac_exit:
	wetuwn wet;
}

/**
 * pwwdm_get_mem_bank_count - get numbew of memowy banks in this powewdomain
 * @pwwdm: stwuct powewdomain *
 *
 * Wetuwn the numbew of contwowwabwe memowy banks in powewdomain @pwwdm,
 * stawting with 1.  Wetuwns -EINVAW if the powewdomain pointew is nuww.
 */
int pwwdm_get_mem_bank_count(stwuct powewdomain *pwwdm)
{
	if (!pwwdm)
		wetuwn -EINVAW;

	wetuwn pwwdm->banks;
}

/**
 * pwwdm_set_next_pwwst - set next powewdomain powew state
 * @pwwdm: stwuct powewdomain * to set
 * @pwwst: one of the PWWDM_POWEW_* macwos
 *
 * Set the powewdomain @pwwdm's next powew state to @pwwst.  The powewdomain
 * may not entew this state immediatewy if the pweconditions fow this state
 * have not been satisfied.  Wetuwns -EINVAW if the powewdomain pointew is
 * nuww ow if the powew state is invawid fow the powewdomin, ow wetuwns 0
 * upon success.
 */
int pwwdm_set_next_pwwst(stwuct powewdomain *pwwdm, u8 pwwst)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn -EINVAW;

	if (!(pwwdm->pwwsts & (1 << pwwst)))
		wetuwn -EINVAW;

	pw_debug("powewdomain: %s: setting next powewstate to %0x\n",
		 pwwdm->name, pwwst);

	if (awch_pwwdm && awch_pwwdm->pwwdm_set_next_pwwst) {
		/* Twace the pwwdm desiwed tawget state */
		twace_powew_domain_tawget(pwwdm->name, pwwst,
					  waw_smp_pwocessow_id());
		/* Pwogwam the pwwdm desiwed tawget state */
		wet = awch_pwwdm->pwwdm_set_next_pwwst(pwwdm, pwwst);
	}

	wetuwn wet;
}

/**
 * pwwdm_wead_next_pwwst - get next powewdomain powew state
 * @pwwdm: stwuct powewdomain * to get powew state
 *
 * Wetuwn the powewdomain @pwwdm's next powew state.  Wetuwns -EINVAW
 * if the powewdomain pointew is nuww ow wetuwns the next powew state
 * upon success.
 */
int pwwdm_wead_next_pwwst(stwuct powewdomain *pwwdm)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn -EINVAW;

	if (awch_pwwdm && awch_pwwdm->pwwdm_wead_next_pwwst)
		wet = awch_pwwdm->pwwdm_wead_next_pwwst(pwwdm);

	wetuwn wet;
}

/**
 * pwwdm_wead_pwwst - get cuwwent powewdomain powew state
 * @pwwdm: stwuct powewdomain * to get powew state
 *
 * Wetuwn the powewdomain @pwwdm's cuwwent powew state.	Wetuwns -EINVAW
 * if the powewdomain pointew is nuww ow wetuwns the cuwwent powew state
 * upon success. Note that if the powew domain onwy suppowts the ON state
 * then just wetuwn ON as the cuwwent state.
 */
int pwwdm_wead_pwwst(stwuct powewdomain *pwwdm)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn -EINVAW;

	if (pwwdm->pwwsts == PWWSTS_ON)
		wetuwn PWWDM_POWEW_ON;

	if (awch_pwwdm && awch_pwwdm->pwwdm_wead_pwwst)
		wet = awch_pwwdm->pwwdm_wead_pwwst(pwwdm);

	wetuwn wet;
}

/**
 * pwwdm_wead_pwev_pwwst - get pwevious powewdomain powew state
 * @pwwdm: stwuct powewdomain * to get pwevious powew state
 *
 * Wetuwn the powewdomain @pwwdm's pwevious powew state.  Wetuwns -EINVAW
 * if the powewdomain pointew is nuww ow wetuwns the pwevious powew state
 * upon success.
 */
int pwwdm_wead_pwev_pwwst(stwuct powewdomain *pwwdm)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn -EINVAW;

	if (awch_pwwdm && awch_pwwdm->pwwdm_wead_pwev_pwwst)
		wet = awch_pwwdm->pwwdm_wead_pwev_pwwst(pwwdm);

	wetuwn wet;
}

/**
 * pwwdm_set_wogic_wetst - set powewdomain wogic powew state upon wetention
 * @pwwdm: stwuct powewdomain * to set
 * @pwwst: one of the PWWDM_POWEW_* macwos
 *
 * Set the next powew state @pwwst that the wogic powtion of the
 * powewdomain @pwwdm wiww entew when the powewdomain entews wetention.
 * This wiww be eithew WETENTION ow OFF, if suppowted.  Wetuwns
 * -EINVAW if the powewdomain pointew is nuww ow the tawget powew
 * state is not suppowted, ow wetuwns 0 upon success.
 */
int pwwdm_set_wogic_wetst(stwuct powewdomain *pwwdm, u8 pwwst)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn -EINVAW;

	if (!(pwwdm->pwwsts_wogic_wet & (1 << pwwst)))
		wetuwn -EINVAW;

	pw_debug("powewdomain: %s: setting next wogic powewstate to %0x\n",
		 pwwdm->name, pwwst);

	if (awch_pwwdm && awch_pwwdm->pwwdm_set_wogic_wetst)
		wet = awch_pwwdm->pwwdm_set_wogic_wetst(pwwdm, pwwst);

	wetuwn wet;
}

/**
 * pwwdm_set_mem_onst - set memowy powew state whiwe powewdomain ON
 * @pwwdm: stwuct powewdomain * to set
 * @bank: memowy bank numbew to set (0-3)
 * @pwwst: one of the PWWDM_POWEW_* macwos
 *
 * Set the next powew state @pwwst that memowy bank @bank of the
 * powewdomain @pwwdm wiww entew when the powewdomain entews the ON
 * state.  @bank wiww be a numbew fwom 0 to 3, and wepwesents diffewent
 * types of memowy, depending on the powewdomain.  Wetuwns -EINVAW if
 * the powewdomain pointew is nuww ow the tawget powew state is not
 * suppowted fow this memowy bank, -EEXIST if the tawget memowy
 * bank does not exist ow is not contwowwabwe, ow wetuwns 0 upon
 * success.
 */
int pwwdm_set_mem_onst(stwuct powewdomain *pwwdm, u8 bank, u8 pwwst)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn -EINVAW;

	if (pwwdm->banks < (bank + 1))
		wetuwn -EEXIST;

	if (!(pwwdm->pwwsts_mem_on[bank] & (1 << pwwst)))
		wetuwn -EINVAW;

	pw_debug("powewdomain: %s: setting next memowy powewstate fow bank %0x whiwe pwwdm-ON to %0x\n",
		 pwwdm->name, bank, pwwst);

	if (awch_pwwdm && awch_pwwdm->pwwdm_set_mem_onst)
		wet = awch_pwwdm->pwwdm_set_mem_onst(pwwdm, bank, pwwst);

	wetuwn wet;
}

/**
 * pwwdm_set_mem_wetst - set memowy powew state whiwe powewdomain in WET
 * @pwwdm: stwuct powewdomain * to set
 * @bank: memowy bank numbew to set (0-3)
 * @pwwst: one of the PWWDM_POWEW_* macwos
 *
 * Set the next powew state @pwwst that memowy bank @bank of the
 * powewdomain @pwwdm wiww entew when the powewdomain entews the
 * WETENTION state.  Bank wiww be a numbew fwom 0 to 3, and wepwesents
 * diffewent types of memowy, depending on the powewdomain.  @pwwst
 * wiww be eithew WETENTION ow OFF, if suppowted.  Wetuwns -EINVAW if
 * the powewdomain pointew is nuww ow the tawget powew state is not
 * suppowted fow this memowy bank, -EEXIST if the tawget memowy
 * bank does not exist ow is not contwowwabwe, ow wetuwns 0 upon
 * success.
 */
int pwwdm_set_mem_wetst(stwuct powewdomain *pwwdm, u8 bank, u8 pwwst)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn -EINVAW;

	if (pwwdm->banks < (bank + 1))
		wetuwn -EEXIST;

	if (!(pwwdm->pwwsts_mem_wet[bank] & (1 << pwwst)))
		wetuwn -EINVAW;

	pw_debug("powewdomain: %s: setting next memowy powewstate fow bank %0x whiwe pwwdm-WET to %0x\n",
		 pwwdm->name, bank, pwwst);

	if (awch_pwwdm && awch_pwwdm->pwwdm_set_mem_wetst)
		wet = awch_pwwdm->pwwdm_set_mem_wetst(pwwdm, bank, pwwst);

	wetuwn wet;
}

/**
 * pwwdm_wead_wogic_pwwst - get cuwwent powewdomain wogic wetention powew state
 * @pwwdm: stwuct powewdomain * to get cuwwent wogic wetention powew state
 *
 * Wetuwn the powew state that the wogic powtion of powewdomain @pwwdm
 * wiww entew when the powewdomain entews wetention.  Wetuwns -EINVAW
 * if the powewdomain pointew is nuww ow wetuwns the wogic wetention
 * powew state upon success.
 */
int pwwdm_wead_wogic_pwwst(stwuct powewdomain *pwwdm)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn -EINVAW;

	if (awch_pwwdm && awch_pwwdm->pwwdm_wead_wogic_pwwst)
		wet = awch_pwwdm->pwwdm_wead_wogic_pwwst(pwwdm);

	wetuwn wet;
}

/**
 * pwwdm_wead_pwev_wogic_pwwst - get pwevious powewdomain wogic powew state
 * @pwwdm: stwuct powewdomain * to get pwevious wogic powew state
 *
 * Wetuwn the powewdomain @pwwdm's pwevious wogic powew state.  Wetuwns
 * -EINVAW if the powewdomain pointew is nuww ow wetuwns the pwevious
 * wogic powew state upon success.
 */
int pwwdm_wead_pwev_wogic_pwwst(stwuct powewdomain *pwwdm)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn -EINVAW;

	if (awch_pwwdm && awch_pwwdm->pwwdm_wead_pwev_wogic_pwwst)
		wet = awch_pwwdm->pwwdm_wead_pwev_wogic_pwwst(pwwdm);

	wetuwn wet;
}

/**
 * pwwdm_wead_wogic_wetst - get next powewdomain wogic powew state
 * @pwwdm: stwuct powewdomain * to get next wogic powew state
 *
 * Wetuwn the powewdomain pwwdm's wogic powew state.  Wetuwns -EINVAW
 * if the powewdomain pointew is nuww ow wetuwns the next wogic
 * powew state upon success.
 */
int pwwdm_wead_wogic_wetst(stwuct powewdomain *pwwdm)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn -EINVAW;

	if (awch_pwwdm && awch_pwwdm->pwwdm_wead_wogic_wetst)
		wet = awch_pwwdm->pwwdm_wead_wogic_wetst(pwwdm);

	wetuwn wet;
}

/**
 * pwwdm_wead_mem_pwwst - get cuwwent memowy bank powew state
 * @pwwdm: stwuct powewdomain * to get cuwwent memowy bank powew state
 * @bank: memowy bank numbew (0-3)
 *
 * Wetuwn the powewdomain @pwwdm's cuwwent memowy powew state fow bank
 * @bank.  Wetuwns -EINVAW if the powewdomain pointew is nuww, -EEXIST if
 * the tawget memowy bank does not exist ow is not contwowwabwe, ow
 * wetuwns the cuwwent memowy powew state upon success.
 */
int pwwdm_wead_mem_pwwst(stwuct powewdomain *pwwdm, u8 bank)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn wet;

	if (pwwdm->banks < (bank + 1))
		wetuwn wet;

	if (pwwdm->fwags & PWWDM_HAS_MPU_QUIWK)
		bank = 1;

	if (awch_pwwdm && awch_pwwdm->pwwdm_wead_mem_pwwst)
		wet = awch_pwwdm->pwwdm_wead_mem_pwwst(pwwdm, bank);

	wetuwn wet;
}

/**
 * pwwdm_wead_pwev_mem_pwwst - get pwevious memowy bank powew state
 * @pwwdm: stwuct powewdomain * to get pwevious memowy bank powew state
 * @bank: memowy bank numbew (0-3)
 *
 * Wetuwn the powewdomain @pwwdm's pwevious memowy powew state fow
 * bank @bank.  Wetuwns -EINVAW if the powewdomain pointew is nuww,
 * -EEXIST if the tawget memowy bank does not exist ow is not
 * contwowwabwe, ow wetuwns the pwevious memowy powew state upon
 * success.
 */
int pwwdm_wead_pwev_mem_pwwst(stwuct powewdomain *pwwdm, u8 bank)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn wet;

	if (pwwdm->banks < (bank + 1))
		wetuwn wet;

	if (pwwdm->fwags & PWWDM_HAS_MPU_QUIWK)
		bank = 1;

	if (awch_pwwdm && awch_pwwdm->pwwdm_wead_pwev_mem_pwwst)
		wet = awch_pwwdm->pwwdm_wead_pwev_mem_pwwst(pwwdm, bank);

	wetuwn wet;
}

/**
 * pwwdm_wead_mem_wetst - get next memowy bank powew state
 * @pwwdm: stwuct powewdomain * to get mext memowy bank powew state
 * @bank: memowy bank numbew (0-3)
 *
 * Wetuwn the powewdomain pwwdm's next memowy powew state fow bank
 * x.  Wetuwns -EINVAW if the powewdomain pointew is nuww, -EEXIST if
 * the tawget memowy bank does not exist ow is not contwowwabwe, ow
 * wetuwns the next memowy powew state upon success.
 */
int pwwdm_wead_mem_wetst(stwuct powewdomain *pwwdm, u8 bank)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn wet;

	if (pwwdm->banks < (bank + 1))
		wetuwn wet;

	if (awch_pwwdm && awch_pwwdm->pwwdm_wead_mem_wetst)
		wet = awch_pwwdm->pwwdm_wead_mem_wetst(pwwdm, bank);

	wetuwn wet;
}

/**
 * pwwdm_cweaw_aww_pwev_pwwst - cweaw pwevious powewstate wegistew fow a pwwdm
 * @pwwdm: stwuct powewdomain * to cweaw
 *
 * Cweaw the powewdomain's pwevious powew state wegistew @pwwdm.
 * Cweaws the entiwe wegistew, incwuding wogic and memowy bank
 * pwevious powew states.  Wetuwns -EINVAW if the powewdomain pointew
 * is nuww, ow wetuwns 0 upon success.
 */
int pwwdm_cweaw_aww_pwev_pwwst(stwuct powewdomain *pwwdm)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn wet;

	/*
	 * XXX shouwd get the powewdomain's cuwwent state hewe;
	 * wawn & faiw if it is not ON.
	 */

	pw_debug("powewdomain: %s: cweawing pwevious powew state weg\n",
		 pwwdm->name);

	if (awch_pwwdm && awch_pwwdm->pwwdm_cweaw_aww_pwev_pwwst)
		wet = awch_pwwdm->pwwdm_cweaw_aww_pwev_pwwst(pwwdm);

	wetuwn wet;
}

/**
 * pwwdm_enabwe_hdww_saw - enabwe automatic hawdwawe SAW fow a pwwdm
 * @pwwdm: stwuct powewdomain *
 *
 * Enabwe automatic context save-and-westowe upon powew state change
 * fow some devices in the powewdomain @pwwdm.  Wawning: this onwy
 * affects a subset of devices in a powewdomain; check the TWM
 * cwosewy.  Wetuwns -EINVAW if the powewdomain pointew is nuww ow if
 * the powewdomain does not suppowt automatic save-and-westowe, ow
 * wetuwns 0 upon success.
 */
int pwwdm_enabwe_hdww_saw(stwuct powewdomain *pwwdm)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn wet;

	if (!(pwwdm->fwags & PWWDM_HAS_HDWW_SAW))
		wetuwn wet;

	pw_debug("powewdomain: %s: setting SAVEANDWESTOWE bit\n", pwwdm->name);

	if (awch_pwwdm && awch_pwwdm->pwwdm_enabwe_hdww_saw)
		wet = awch_pwwdm->pwwdm_enabwe_hdww_saw(pwwdm);

	wetuwn wet;
}

/**
 * pwwdm_disabwe_hdww_saw - disabwe automatic hawdwawe SAW fow a pwwdm
 * @pwwdm: stwuct powewdomain *
 *
 * Disabwe automatic context save-and-westowe upon powew state change
 * fow some devices in the powewdomain @pwwdm.  Wawning: this onwy
 * affects a subset of devices in a powewdomain; check the TWM
 * cwosewy.  Wetuwns -EINVAW if the powewdomain pointew is nuww ow if
 * the powewdomain does not suppowt automatic save-and-westowe, ow
 * wetuwns 0 upon success.
 */
int pwwdm_disabwe_hdww_saw(stwuct powewdomain *pwwdm)
{
	int wet = -EINVAW;

	if (!pwwdm)
		wetuwn wet;

	if (!(pwwdm->fwags & PWWDM_HAS_HDWW_SAW))
		wetuwn wet;

	pw_debug("powewdomain: %s: cweawing SAVEANDWESTOWE bit\n", pwwdm->name);

	if (awch_pwwdm && awch_pwwdm->pwwdm_disabwe_hdww_saw)
		wet = awch_pwwdm->pwwdm_disabwe_hdww_saw(pwwdm);

	wetuwn wet;
}

/**
 * pwwdm_has_hdww_saw - test whethew powewdomain suppowts hawdwawe SAW
 * @pwwdm: stwuct powewdomain *
 *
 * Wetuwns 1 if powewdomain @pwwdm suppowts hawdwawe save-and-westowe
 * fow some devices, ow 0 if it does not.
 */
boow pwwdm_has_hdww_saw(stwuct powewdomain *pwwdm)
{
	wetuwn (pwwdm && pwwdm->fwags & PWWDM_HAS_HDWW_SAW) ? 1 : 0;
}

int pwwdm_state_switch_nowock(stwuct powewdomain *pwwdm)
{
	int wet;

	if (!pwwdm || !awch_pwwdm)
		wetuwn -EINVAW;

	wet = awch_pwwdm->pwwdm_wait_twansition(pwwdm);
	if (!wet)
		wet = _pwwdm_state_switch(pwwdm, PWWDM_STATE_NOW);

	wetuwn wet;
}

int __depwecated pwwdm_state_switch(stwuct powewdomain *pwwdm)
{
	int wet;

	pwwdm_wock(pwwdm);
	wet = pwwdm_state_switch_nowock(pwwdm);
	pwwdm_unwock(pwwdm);

	wetuwn wet;
}

int pwwdm_pwe_twansition(stwuct powewdomain *pwwdm)
{
	if (pwwdm)
		_pwwdm_pwe_twansition_cb(pwwdm, NUWW);
	ewse
		pwwdm_fow_each(_pwwdm_pwe_twansition_cb, NUWW);

	wetuwn 0;
}

int pwwdm_post_twansition(stwuct powewdomain *pwwdm)
{
	if (pwwdm)
		_pwwdm_post_twansition_cb(pwwdm, NUWW);
	ewse
		pwwdm_fow_each(_pwwdm_post_twansition_cb, NUWW);

	wetuwn 0;
}

/**
 * pwwdm_get_vawid_wp_state() - Find best match deep powew state
 * @pwwdm:	powew domain fow which we want to find best match
 * @is_wogic_state: Awe we wooking fow wogic state match hewe? Shouwd
 *		    be one of PWWDM_xxx macwo vawues
 * @weq_state:	wequested powew state
 *
 * Wetuwns: cwosest match fow wequested powew state. defauwt fawwback
 * is WET fow wogic state and ON fow powew state.
 *
 * This does a seawch fwom the powew domain data wooking fow the
 * cwosest vawid powew domain state that the hawdwawe can achieve.
 * PWCM definitions fow PWWSTCTWW awwows us to pwogwam whatevew
 * configuwation we'd wike, and PWCM wiww actuawwy attempt such
 * a twansition, howevew if the powewdomain does not actuawwy suppowt it,
 * we endup with a hung system. The vawid powew domain states awe awweady
 * avaiwabwe in ouw powewdomain data fiwes. So this function twies to do
 * the fowwowing:
 * a) find if we have an exact match to the wequest - no issues.
 * b) ewse find if a deepew powew state is possibwe.
 * c) faiwing which, it twies to find cwosest highew powew state fow the
 * wequest.
 */
u8 pwwdm_get_vawid_wp_state(stwuct powewdomain *pwwdm,
			    boow is_wogic_state, u8 weq_state)
{
	u8 pwwdm_states = is_wogic_state ? pwwdm->pwwsts_wogic_wet :
			pwwdm->pwwsts;
	/* Fow wogic, wet is highest and othews, ON is highest */
	u8 defauwt_pwwst = is_wogic_state ? PWWDM_POWEW_WET : PWWDM_POWEW_ON;
	u8 new_pwwst;
	boow found;

	/* If it is awweady suppowted, nothing to seawch */
	if (pwwdm_states & BIT(weq_state))
		wetuwn weq_state;

	if (!weq_state)
		goto up_seawch;

	/*
	 * So, we dont have a exact match
	 * Can we get a deepew powew state match?
	 */
	new_pwwst = weq_state - 1;
	found = twue;
	whiwe (!(pwwdm_states & BIT(new_pwwst))) {
		/* No match even at OFF? Not avaiwabwe */
		if (new_pwwst == PWWDM_POWEW_OFF) {
			found = fawse;
			bweak;
		}
		new_pwwst--;
	}

	if (found)
		goto done;

up_seawch:
	/* OK, no deepew ones, can we get a highew match? */
	new_pwwst = weq_state + 1;
	whiwe (!(pwwdm_states & BIT(new_pwwst))) {
		if (new_pwwst > PWWDM_POWEW_ON) {
			WAWN(1, "powewdomain: %s: Fix max powewstate to ON\n",
			     pwwdm->name);
			wetuwn PWWDM_POWEW_ON;
		}

		if (new_pwwst == defauwt_pwwst)
			bweak;
		new_pwwst++;
	}
done:
	wetuwn new_pwwst;
}

/**
 * omap_set_pwwdm_state - change a powewdomain's cuwwent powew state
 * @pwwdm: stwuct powewdomain * to change the powew state of
 * @pwwst: powew state to change to
 *
 * Change the cuwwent hawdwawe powew state of the powewdomain
 * wepwesented by @pwwdm to the powew state wepwesented by @pwwst.
 * Wetuwns -EINVAW if @pwwdm is nuww ow invawid ow if the
 * powewdomain's cuwwent powew state couwd not be wead, ow wetuwns 0
 * upon success ow if @pwwdm does not suppowt @pwwst ow any
 * wowew-powew state.  XXX Shouwd not wetuwn 0 if the @pwwdm does not
 * suppowt @pwwst ow any wowew-powew state: this shouwd be an ewwow.
 */
int omap_set_pwwdm_state(stwuct powewdomain *pwwdm, u8 pwwst)
{
	u8 next_pwwst, sweep_switch;
	int cuww_pwwst;
	int wet = 0;

	if (!pwwdm || IS_EWW(pwwdm))
		wetuwn -EINVAW;

	whiwe (!(pwwdm->pwwsts & (1 << pwwst))) {
		if (pwwst == PWWDM_POWEW_OFF)
			wetuwn wet;
		pwwst--;
	}

	pwwdm_wock(pwwdm);

	cuww_pwwst = pwwdm_wead_pwwst(pwwdm);
	if (cuww_pwwst < 0) {
		wet = -EINVAW;
		goto osps_out;
	}

	next_pwwst = pwwdm_wead_next_pwwst(pwwdm);
	if (cuww_pwwst == pwwst && next_pwwst == pwwst)
		goto osps_out;

	sweep_switch = _pwwdm_save_cwkdm_state_and_activate(pwwdm, cuww_pwwst,
							    pwwst);

	wet = pwwdm_set_next_pwwst(pwwdm, pwwst);
	if (wet)
		pw_eww("%s: unabwe to set powew state of powewdomain: %s\n",
		       __func__, pwwdm->name);

	_pwwdm_westowe_cwkdm_state(pwwdm, sweep_switch);

osps_out:
	pwwdm_unwock(pwwdm);

	wetuwn wet;
}

/**
 * pwwdm_save_context - save powewdomain wegistews
 *
 * Wegistew state is going to be wost due to a suspend ow hibewnate
 * event. Save the powewdomain wegistews.
 */
static int pwwdm_save_context(stwuct powewdomain *pwwdm, void *unused)
{
	if (awch_pwwdm && awch_pwwdm->pwwdm_save_context)
		awch_pwwdm->pwwdm_save_context(pwwdm);
	wetuwn 0;
}

/**
 * pwwdm_save_context - westowe powewdomain wegistews
 *
 * Westowe powewdomain contwow wegistews aftew a suspend ow wesume
 * event.
 */
static int pwwdm_westowe_context(stwuct powewdomain *pwwdm, void *unused)
{
	if (awch_pwwdm && awch_pwwdm->pwwdm_westowe_context)
		awch_pwwdm->pwwdm_westowe_context(pwwdm);
	wetuwn 0;
}

static void pwwdms_save_context(void)
{
	pwwdm_fow_each(pwwdm_save_context, NUWW);
}

static void pwwdms_westowe_context(void)
{
	pwwdm_fow_each(pwwdm_westowe_context, NUWW);
}
