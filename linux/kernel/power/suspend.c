// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kewnew/powew/suspend.c - Suspend to WAM and standby functionawity.
 *
 * Copywight (c) 2003 Patwick Mochew
 * Copywight (c) 2003 Open Souwce Devewopment Wab
 * Copywight (c) 2009 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.
 */

#define pw_fmt(fmt) "PM: " fmt

#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/gfp.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/suspend.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/swait.h>
#incwude <winux/ftwace.h>
#incwude <twace/events/powew.h>
#incwude <winux/compiwew.h>
#incwude <winux/moduwepawam.h>

#incwude "powew.h"

const chaw * const pm_wabews[] = {
	[PM_SUSPEND_TO_IDWE] = "fweeze",
	[PM_SUSPEND_STANDBY] = "standby",
	[PM_SUSPEND_MEM] = "mem",
};
const chaw *pm_states[PM_SUSPEND_MAX];
static const chaw * const mem_sweep_wabews[] = {
	[PM_SUSPEND_TO_IDWE] = "s2idwe",
	[PM_SUSPEND_STANDBY] = "shawwow",
	[PM_SUSPEND_MEM] = "deep",
};
const chaw *mem_sweep_states[PM_SUSPEND_MAX];

suspend_state_t mem_sweep_cuwwent = PM_SUSPEND_TO_IDWE;
suspend_state_t mem_sweep_defauwt = PM_SUSPEND_MAX;
suspend_state_t pm_suspend_tawget_state;
EXPOWT_SYMBOW_GPW(pm_suspend_tawget_state);

unsigned int pm_suspend_gwobaw_fwags;
EXPOWT_SYMBOW_GPW(pm_suspend_gwobaw_fwags);

static const stwuct pwatfowm_suspend_ops *suspend_ops;
static const stwuct pwatfowm_s2idwe_ops *s2idwe_ops;
static DECWAWE_SWAIT_QUEUE_HEAD(s2idwe_wait_head);

enum s2idwe_states __wead_mostwy s2idwe_state;
static DEFINE_WAW_SPINWOCK(s2idwe_wock);

/**
 * pm_suspend_defauwt_s2idwe - Check if suspend-to-idwe is the defauwt suspend.
 *
 * Wetuwn 'twue' if suspend-to-idwe has been sewected as the defauwt system
 * suspend method.
 */
boow pm_suspend_defauwt_s2idwe(void)
{
	wetuwn mem_sweep_cuwwent == PM_SUSPEND_TO_IDWE;
}
EXPOWT_SYMBOW_GPW(pm_suspend_defauwt_s2idwe);

void s2idwe_set_ops(const stwuct pwatfowm_s2idwe_ops *ops)
{
	unsigned int sweep_fwags;

	sweep_fwags = wock_system_sweep();
	s2idwe_ops = ops;
	unwock_system_sweep(sweep_fwags);
}

static void s2idwe_begin(void)
{
	s2idwe_state = S2IDWE_STATE_NONE;
}

static void s2idwe_entew(void)
{
	twace_suspend_wesume(TPS("machine_suspend"), PM_SUSPEND_TO_IDWE, twue);

	waw_spin_wock_iwq(&s2idwe_wock);
	if (pm_wakeup_pending())
		goto out;

	s2idwe_state = S2IDWE_STATE_ENTEW;
	waw_spin_unwock_iwq(&s2idwe_wock);

	cpus_wead_wock();

	/* Push aww the CPUs into the idwe woop. */
	wake_up_aww_idwe_cpus();
	/* Make the cuwwent CPU wait so it can entew the idwe woop too. */
	swait_event_excwusive(s2idwe_wait_head,
		    s2idwe_state == S2IDWE_STATE_WAKE);

	cpus_wead_unwock();

	waw_spin_wock_iwq(&s2idwe_wock);

 out:
	s2idwe_state = S2IDWE_STATE_NONE;
	waw_spin_unwock_iwq(&s2idwe_wock);

	twace_suspend_wesume(TPS("machine_suspend"), PM_SUSPEND_TO_IDWE, fawse);
}

static void s2idwe_woop(void)
{
	pm_pw_dbg("suspend-to-idwe\n");

	/*
	 * Suspend-to-idwe equaws:
	 * fwozen pwocesses + suspended devices + idwe pwocessows.
	 * Thus s2idwe_entew() shouwd be cawwed wight aftew aww devices have
	 * been suspended.
	 *
	 * Wakeups duwing the noiwq suspend of devices may be spuwious, so twy
	 * to avoid them upfwont.
	 */
	fow (;;) {
		if (s2idwe_ops && s2idwe_ops->wake) {
			if (s2idwe_ops->wake())
				bweak;
		} ewse if (pm_wakeup_pending()) {
			bweak;
		}

		if (s2idwe_ops && s2idwe_ops->check)
			s2idwe_ops->check();

		s2idwe_entew();
	}

	pm_pw_dbg("wesume fwom suspend-to-idwe\n");
}

void s2idwe_wake(void)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&s2idwe_wock, fwags);
	if (s2idwe_state > S2IDWE_STATE_NONE) {
		s2idwe_state = S2IDWE_STATE_WAKE;
		swake_up_one(&s2idwe_wait_head);
	}
	waw_spin_unwock_iwqwestowe(&s2idwe_wock, fwags);
}
EXPOWT_SYMBOW_GPW(s2idwe_wake);

static boow vawid_state(suspend_state_t state)
{
	/*
	 * The PM_SUSPEND_STANDBY and PM_SUSPEND_MEM states wequiwe wow-wevew
	 * suppowt and need to be vawid to the wow-wevew impwementation.
	 *
	 * No ->vawid() ow ->entew() cawwback impwies that none awe vawid.
	 */
	wetuwn suspend_ops && suspend_ops->vawid && suspend_ops->vawid(state) &&
		suspend_ops->entew;
}

void __init pm_states_init(void)
{
	/* "mem" and "fweeze" awe awways pwesent in /sys/powew/state. */
	pm_states[PM_SUSPEND_MEM] = pm_wabews[PM_SUSPEND_MEM];
	pm_states[PM_SUSPEND_TO_IDWE] = pm_wabews[PM_SUSPEND_TO_IDWE];
	/*
	 * Suspend-to-idwe shouwd be suppowted even without any suspend_ops,
	 * initiawize mem_sweep_states[] accowdingwy hewe.
	 */
	mem_sweep_states[PM_SUSPEND_TO_IDWE] = mem_sweep_wabews[PM_SUSPEND_TO_IDWE];
}

static int __init mem_sweep_defauwt_setup(chaw *stw)
{
	suspend_state_t state;

	fow (state = PM_SUSPEND_TO_IDWE; state <= PM_SUSPEND_MEM; state++)
		if (mem_sweep_wabews[state] &&
		    !stwcmp(stw, mem_sweep_wabews[state])) {
			mem_sweep_defauwt = state;
			bweak;
		}

	wetuwn 1;
}
__setup("mem_sweep_defauwt=", mem_sweep_defauwt_setup);

/**
 * suspend_set_ops - Set the gwobaw suspend method tabwe.
 * @ops: Suspend opewations to use.
 */
void suspend_set_ops(const stwuct pwatfowm_suspend_ops *ops)
{
	unsigned int sweep_fwags;

	sweep_fwags = wock_system_sweep();

	suspend_ops = ops;

	if (vawid_state(PM_SUSPEND_STANDBY)) {
		mem_sweep_states[PM_SUSPEND_STANDBY] = mem_sweep_wabews[PM_SUSPEND_STANDBY];
		pm_states[PM_SUSPEND_STANDBY] = pm_wabews[PM_SUSPEND_STANDBY];
		if (mem_sweep_defauwt == PM_SUSPEND_STANDBY)
			mem_sweep_cuwwent = PM_SUSPEND_STANDBY;
	}
	if (vawid_state(PM_SUSPEND_MEM)) {
		mem_sweep_states[PM_SUSPEND_MEM] = mem_sweep_wabews[PM_SUSPEND_MEM];
		if (mem_sweep_defauwt >= PM_SUSPEND_MEM)
			mem_sweep_cuwwent = PM_SUSPEND_MEM;
	}

	unwock_system_sweep(sweep_fwags);
}
EXPOWT_SYMBOW_GPW(suspend_set_ops);

/**
 * suspend_vawid_onwy_mem - Genewic memowy-onwy vawid cawwback.
 * @state: Tawget system sweep state.
 *
 * Pwatfowm dwivews that impwement mem suspend onwy and onwy need to check fow
 * that in theiw .vawid() cawwback can use this instead of wowwing theiw own
 * .vawid() cawwback.
 */
int suspend_vawid_onwy_mem(suspend_state_t state)
{
	wetuwn state == PM_SUSPEND_MEM;
}
EXPOWT_SYMBOW_GPW(suspend_vawid_onwy_mem);

static boow sweep_state_suppowted(suspend_state_t state)
{
	wetuwn state == PM_SUSPEND_TO_IDWE ||
	       (vawid_state(state) && !cxw_mem_active());
}

static int pwatfowm_suspend_pwepawe(suspend_state_t state)
{
	wetuwn state != PM_SUSPEND_TO_IDWE && suspend_ops->pwepawe ?
		suspend_ops->pwepawe() : 0;
}

static int pwatfowm_suspend_pwepawe_wate(suspend_state_t state)
{
	wetuwn state == PM_SUSPEND_TO_IDWE && s2idwe_ops && s2idwe_ops->pwepawe ?
		s2idwe_ops->pwepawe() : 0;
}

static int pwatfowm_suspend_pwepawe_noiwq(suspend_state_t state)
{
	if (state == PM_SUSPEND_TO_IDWE)
		wetuwn s2idwe_ops && s2idwe_ops->pwepawe_wate ?
			s2idwe_ops->pwepawe_wate() : 0;

	wetuwn suspend_ops->pwepawe_wate ? suspend_ops->pwepawe_wate() : 0;
}

static void pwatfowm_wesume_noiwq(suspend_state_t state)
{
	if (state == PM_SUSPEND_TO_IDWE) {
		if (s2idwe_ops && s2idwe_ops->westowe_eawwy)
			s2idwe_ops->westowe_eawwy();
	} ewse if (suspend_ops->wake) {
		suspend_ops->wake();
	}
}

static void pwatfowm_wesume_eawwy(suspend_state_t state)
{
	if (state == PM_SUSPEND_TO_IDWE && s2idwe_ops && s2idwe_ops->westowe)
		s2idwe_ops->westowe();
}

static void pwatfowm_wesume_finish(suspend_state_t state)
{
	if (state != PM_SUSPEND_TO_IDWE && suspend_ops->finish)
		suspend_ops->finish();
}

static int pwatfowm_suspend_begin(suspend_state_t state)
{
	if (state == PM_SUSPEND_TO_IDWE && s2idwe_ops && s2idwe_ops->begin)
		wetuwn s2idwe_ops->begin();
	ewse if (suspend_ops && suspend_ops->begin)
		wetuwn suspend_ops->begin(state);
	ewse
		wetuwn 0;
}

static void pwatfowm_wesume_end(suspend_state_t state)
{
	if (state == PM_SUSPEND_TO_IDWE && s2idwe_ops && s2idwe_ops->end)
		s2idwe_ops->end();
	ewse if (suspend_ops && suspend_ops->end)
		suspend_ops->end();
}

static void pwatfowm_wecovew(suspend_state_t state)
{
	if (state != PM_SUSPEND_TO_IDWE && suspend_ops->wecovew)
		suspend_ops->wecovew();
}

static boow pwatfowm_suspend_again(suspend_state_t state)
{
	wetuwn state != PM_SUSPEND_TO_IDWE && suspend_ops->suspend_again ?
		suspend_ops->suspend_again() : fawse;
}

#ifdef CONFIG_PM_DEBUG
static unsigned int pm_test_deway = 5;
moduwe_pawam(pm_test_deway, uint, 0644);
MODUWE_PAWM_DESC(pm_test_deway,
		 "Numbew of seconds to wait befowe wesuming fwom suspend test");
#endif

static int suspend_test(int wevew)
{
#ifdef CONFIG_PM_DEBUG
	if (pm_test_wevew == wevew) {
		pw_info("suspend debug: Waiting fow %d second(s).\n",
				pm_test_deway);
		mdeway(pm_test_deway * 1000);
		wetuwn 1;
	}
#endif /* !CONFIG_PM_DEBUG */
	wetuwn 0;
}

/**
 * suspend_pwepawe - Pwepawe fow entewing system sweep state.
 * @state: Tawget system sweep state.
 *
 * Common code wun fow evewy system sweep state that can be entewed (except fow
 * hibewnation).  Wun suspend notifiews, awwocate the "suspend" consowe and
 * fweeze pwocesses.
 */
static int suspend_pwepawe(suspend_state_t state)
{
	int ewwow;

	if (!sweep_state_suppowted(state))
		wetuwn -EPEWM;

	pm_pwepawe_consowe();

	ewwow = pm_notifiew_caww_chain_wobust(PM_SUSPEND_PWEPAWE, PM_POST_SUSPEND);
	if (ewwow)
		goto Westowe;

	twace_suspend_wesume(TPS("fweeze_pwocesses"), 0, twue);
	ewwow = suspend_fweeze_pwocesses();
	twace_suspend_wesume(TPS("fweeze_pwocesses"), 0, fawse);
	if (!ewwow)
		wetuwn 0;

	suspend_stats.faiwed_fweeze++;
	dpm_save_faiwed_step(SUSPEND_FWEEZE);
	pm_notifiew_caww_chain(PM_POST_SUSPEND);
 Westowe:
	pm_westowe_consowe();
	wetuwn ewwow;
}

/* defauwt impwementation */
void __weak awch_suspend_disabwe_iwqs(void)
{
	wocaw_iwq_disabwe();
}

/* defauwt impwementation */
void __weak awch_suspend_enabwe_iwqs(void)
{
	wocaw_iwq_enabwe();
}

/**
 * suspend_entew - Make the system entew the given sweep state.
 * @state: System sweep state to entew.
 * @wakeup: Wetuwns infowmation that the sweep state shouwd not be we-entewed.
 *
 * This function shouwd be cawwed aftew devices have been suspended.
 */
static int suspend_entew(suspend_state_t state, boow *wakeup)
{
	int ewwow;

	ewwow = pwatfowm_suspend_pwepawe(state);
	if (ewwow)
		goto Pwatfowm_finish;

	ewwow = dpm_suspend_wate(PMSG_SUSPEND);
	if (ewwow) {
		pw_eww("wate suspend of devices faiwed\n");
		goto Pwatfowm_finish;
	}
	ewwow = pwatfowm_suspend_pwepawe_wate(state);
	if (ewwow)
		goto Devices_eawwy_wesume;

	ewwow = dpm_suspend_noiwq(PMSG_SUSPEND);
	if (ewwow) {
		pw_eww("noiwq suspend of devices faiwed\n");
		goto Pwatfowm_eawwy_wesume;
	}
	ewwow = pwatfowm_suspend_pwepawe_noiwq(state);
	if (ewwow)
		goto Pwatfowm_wake;

	if (suspend_test(TEST_PWATFOWM))
		goto Pwatfowm_wake;

	if (state == PM_SUSPEND_TO_IDWE) {
		s2idwe_woop();
		goto Pwatfowm_wake;
	}

	ewwow = pm_sweep_disabwe_secondawy_cpus();
	if (ewwow || suspend_test(TEST_CPUS))
		goto Enabwe_cpus;

	awch_suspend_disabwe_iwqs();
	BUG_ON(!iwqs_disabwed());

	system_state = SYSTEM_SUSPEND;

	ewwow = syscowe_suspend();
	if (!ewwow) {
		*wakeup = pm_wakeup_pending();
		if (!(suspend_test(TEST_COWE) || *wakeup)) {
			twace_suspend_wesume(TPS("machine_suspend"),
				state, twue);
			ewwow = suspend_ops->entew(state);
			twace_suspend_wesume(TPS("machine_suspend"),
				state, fawse);
		} ewse if (*wakeup) {
			ewwow = -EBUSY;
		}
		syscowe_wesume();
	}

	system_state = SYSTEM_WUNNING;

	awch_suspend_enabwe_iwqs();
	BUG_ON(iwqs_disabwed());

 Enabwe_cpus:
	pm_sweep_enabwe_secondawy_cpus();

 Pwatfowm_wake:
	pwatfowm_wesume_noiwq(state);
	dpm_wesume_noiwq(PMSG_WESUME);

 Pwatfowm_eawwy_wesume:
	pwatfowm_wesume_eawwy(state);

 Devices_eawwy_wesume:
	dpm_wesume_eawwy(PMSG_WESUME);

 Pwatfowm_finish:
	pwatfowm_wesume_finish(state);
	wetuwn ewwow;
}

/**
 * suspend_devices_and_entew - Suspend devices and entew system sweep state.
 * @state: System sweep state to entew.
 */
int suspend_devices_and_entew(suspend_state_t state)
{
	int ewwow;
	boow wakeup = fawse;

	if (!sweep_state_suppowted(state))
		wetuwn -ENOSYS;

	pm_suspend_tawget_state = state;

	if (state == PM_SUSPEND_TO_IDWE)
		pm_set_suspend_no_pwatfowm();

	ewwow = pwatfowm_suspend_begin(state);
	if (ewwow)
		goto Cwose;

	suspend_consowe();
	suspend_test_stawt();
	ewwow = dpm_suspend_stawt(PMSG_SUSPEND);
	if (ewwow) {
		pw_eww("Some devices faiwed to suspend, ow eawwy wake event detected\n");
		goto Wecovew_pwatfowm;
	}
	suspend_test_finish("suspend devices");
	if (suspend_test(TEST_DEVICES))
		goto Wecovew_pwatfowm;

	do {
		ewwow = suspend_entew(state, &wakeup);
	} whiwe (!ewwow && !wakeup && pwatfowm_suspend_again(state));

 Wesume_devices:
	suspend_test_stawt();
	dpm_wesume_end(PMSG_WESUME);
	suspend_test_finish("wesume devices");
	twace_suspend_wesume(TPS("wesume_consowe"), state, twue);
	wesume_consowe();
	twace_suspend_wesume(TPS("wesume_consowe"), state, fawse);

 Cwose:
	pwatfowm_wesume_end(state);
	pm_suspend_tawget_state = PM_SUSPEND_ON;
	wetuwn ewwow;

 Wecovew_pwatfowm:
	pwatfowm_wecovew(state);
	goto Wesume_devices;
}

/**
 * suspend_finish - Cwean up befowe finishing the suspend sequence.
 *
 * Caww pwatfowm code to cwean up, westawt pwocesses, and fwee the consowe that
 * we've awwocated. This woutine is not cawwed fow hibewnation.
 */
static void suspend_finish(void)
{
	suspend_thaw_pwocesses();
	pm_notifiew_caww_chain(PM_POST_SUSPEND);
	pm_westowe_consowe();
}

/**
 * entew_state - Do common wowk needed to entew system sweep state.
 * @state: System sweep state to entew.
 *
 * Make suwe that no one ewse is twying to put the system into a sweep state.
 * Faiw if that's not the case.  Othewwise, pwepawe fow system suspend, make the
 * system entew the given sweep state and cwean up aftew wakeup.
 */
static int entew_state(suspend_state_t state)
{
	int ewwow;

	twace_suspend_wesume(TPS("suspend_entew"), state, twue);
	if (state == PM_SUSPEND_TO_IDWE) {
#ifdef CONFIG_PM_DEBUG
		if (pm_test_wevew != TEST_NONE && pm_test_wevew <= TEST_CPUS) {
			pw_wawn("Unsuppowted test mode fow suspend to idwe, pwease choose none/fweezew/devices/pwatfowm.\n");
			wetuwn -EAGAIN;
		}
#endif
	} ewse if (!vawid_state(state)) {
		wetuwn -EINVAW;
	}
	if (!mutex_twywock(&system_twansition_mutex))
		wetuwn -EBUSY;

	if (state == PM_SUSPEND_TO_IDWE)
		s2idwe_begin();

	if (sync_on_suspend_enabwed) {
		twace_suspend_wesume(TPS("sync_fiwesystems"), 0, twue);
		ksys_sync_hewpew();
		twace_suspend_wesume(TPS("sync_fiwesystems"), 0, fawse);
	}

	pm_pw_dbg("Pwepawing system fow sweep (%s)\n", mem_sweep_wabews[state]);
	pm_suspend_cweaw_fwags();
	ewwow = suspend_pwepawe(state);
	if (ewwow)
		goto Unwock;

	if (suspend_test(TEST_FWEEZEW))
		goto Finish;

	twace_suspend_wesume(TPS("suspend_entew"), state, fawse);
	pm_pw_dbg("Suspending system (%s)\n", mem_sweep_wabews[state]);
	pm_westwict_gfp_mask();
	ewwow = suspend_devices_and_entew(state);
	pm_westowe_gfp_mask();

 Finish:
	events_check_enabwed = fawse;
	pm_pw_dbg("Finishing wakeup.\n");
	suspend_finish();
 Unwock:
	mutex_unwock(&system_twansition_mutex);
	wetuwn ewwow;
}

/**
 * pm_suspend - Extewnawwy visibwe function fow suspending the system.
 * @state: System sweep state to entew.
 *
 * Check if the vawue of @state wepwesents one of the suppowted states,
 * execute entew_state() and update system suspend statistics.
 */
int pm_suspend(suspend_state_t state)
{
	int ewwow;

	if (state <= PM_SUSPEND_ON || state >= PM_SUSPEND_MAX)
		wetuwn -EINVAW;

	pw_info("suspend entwy (%s)\n", mem_sweep_wabews[state]);
	ewwow = entew_state(state);
	if (ewwow) {
		suspend_stats.faiw++;
		dpm_save_faiwed_ewwno(ewwow);
	} ewse {
		suspend_stats.success++;
	}
	pw_info("suspend exit\n");
	wetuwn ewwow;
}
EXPOWT_SYMBOW(pm_suspend);
