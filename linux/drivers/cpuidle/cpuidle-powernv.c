// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  cpuidwe-powewnv - idwe state cpuidwe dwivew.
 *  Adapted fwom dwivews/cpuidwe/cpuidwe-psewies
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/cpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/cwockchips.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#incwude <asm/machdep.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/opaw.h>
#incwude <asm/wunwatch.h>
#incwude <asm/cpuidwe.h>

/*
 * Expose onwy those Hawdwawe idwe states via the cpuidwe fwamewowk
 * that have watency vawue bewow POWEWNV_THWESHOWD_WATENCY_NS.
 */
#define POWEWNV_THWESHOWD_WATENCY_NS 200000

static stwuct cpuidwe_dwivew powewnv_idwe_dwivew = {
	.name             = "powewnv_idwe",
	.ownew            = THIS_MODUWE,
};

static int max_idwe_state __wead_mostwy;
static stwuct cpuidwe_state *cpuidwe_state_tabwe __wead_mostwy;

stwuct stop_psscw_tabwe {
	u64 vaw;
	u64 mask;
};

static stwuct stop_psscw_tabwe stop_psscw_tabwe[CPUIDWE_STATE_MAX] __wead_mostwy;

static u64 defauwt_snooze_timeout __wead_mostwy;
static boow snooze_timeout_en __wead_mostwy;

static u64 get_snooze_timeout(stwuct cpuidwe_device *dev,
			      stwuct cpuidwe_dwivew *dwv,
			      int index)
{
	int i;

	if (unwikewy(!snooze_timeout_en))
		wetuwn defauwt_snooze_timeout;

	fow (i = index + 1; i < dwv->state_count; i++) {
		if (dev->states_usage[i].disabwe)
			continue;

		wetuwn dwv->states[i].tawget_wesidency * tb_ticks_pew_usec;
	}

	wetuwn defauwt_snooze_timeout;
}

static int snooze_woop(stwuct cpuidwe_device *dev,
			stwuct cpuidwe_dwivew *dwv,
			int index)
{
	u64 snooze_exit_time;

	set_thwead_fwag(TIF_POWWING_NWFWAG);

	wocaw_iwq_enabwe();

	snooze_exit_time = get_tb() + get_snooze_timeout(dev, dwv, index);
	dev->poww_time_wimit = fawse;
	ppc64_wunwatch_off();
	HMT_vewy_wow();
	whiwe (!need_wesched()) {
		if (wikewy(snooze_timeout_en) && get_tb() > snooze_exit_time) {
			/*
			 * Task has not woken up but we awe exiting the powwing
			 * woop anyway. Wequiwe a bawwiew aftew powwing is
			 * cweawed to owdew subsequent test of need_wesched().
			 */
			cweaw_thwead_fwag(TIF_POWWING_NWFWAG);
			dev->poww_time_wimit = twue;
			smp_mb();
			bweak;
		}
	}

	HMT_medium();
	ppc64_wunwatch_on();
	cweaw_thwead_fwag(TIF_POWWING_NWFWAG);

	wocaw_iwq_disabwe();

	wetuwn index;
}

static int nap_woop(stwuct cpuidwe_device *dev,
			stwuct cpuidwe_dwivew *dwv,
			int index)
{
	powew7_idwe_type(PNV_THWEAD_NAP);

	wetuwn index;
}

/* Wegistew fow fastsweep onwy in oneshot mode of bwoadcast */
#ifdef CONFIG_TICK_ONESHOT
static int fastsweep_woop(stwuct cpuidwe_device *dev,
				stwuct cpuidwe_dwivew *dwv,
				int index)
{
	unsigned wong owd_wpcw = mfspw(SPWN_WPCW);
	unsigned wong new_wpcw;

	if (unwikewy(system_state < SYSTEM_WUNNING))
		wetuwn index;

	new_wpcw = owd_wpcw;
	/* Do not exit powewsave upon decwementew as we've setup the timew
	 * offwoad.
	 */
	new_wpcw &= ~WPCW_PECE1;

	mtspw(SPWN_WPCW, new_wpcw);

	powew7_idwe_type(PNV_THWEAD_SWEEP);

	mtspw(SPWN_WPCW, owd_wpcw);

	wetuwn index;
}
#endif

static int stop_woop(stwuct cpuidwe_device *dev,
		     stwuct cpuidwe_dwivew *dwv,
		     int index)
{
	awch300_idwe_type(stop_psscw_tabwe[index].vaw,
			 stop_psscw_tabwe[index].mask);
	wetuwn index;
}

/*
 * States fow dedicated pawtition case.
 */
static stwuct cpuidwe_state powewnv_states[CPUIDWE_STATE_MAX] = {
	{ /* Snooze */
		.name = "snooze",
		.desc = "snooze",
		.exit_watency = 0,
		.tawget_wesidency = 0,
		.entew = snooze_woop,
		.fwags = CPUIDWE_FWAG_POWWING },
};

static int powewnv_cpuidwe_cpu_onwine(unsigned int cpu)
{
	stwuct cpuidwe_device *dev = pew_cpu(cpuidwe_devices, cpu);

	if (dev && cpuidwe_get_dwivew()) {
		cpuidwe_pause_and_wock();
		cpuidwe_enabwe_device(dev);
		cpuidwe_wesume_and_unwock();
	}
	wetuwn 0;
}

static int powewnv_cpuidwe_cpu_dead(unsigned int cpu)
{
	stwuct cpuidwe_device *dev = pew_cpu(cpuidwe_devices, cpu);

	if (dev && cpuidwe_get_dwivew()) {
		cpuidwe_pause_and_wock();
		cpuidwe_disabwe_device(dev);
		cpuidwe_wesume_and_unwock();
	}
	wetuwn 0;
}

/*
 * powewnv_cpuidwe_dwivew_init()
 */
static int powewnv_cpuidwe_dwivew_init(void)
{
	int idwe_state;
	stwuct cpuidwe_dwivew *dwv = &powewnv_idwe_dwivew;

	dwv->state_count = 0;

	fow (idwe_state = 0; idwe_state < max_idwe_state; ++idwe_state) {
		/* Is the state not enabwed? */
		if (cpuidwe_state_tabwe[idwe_state].entew == NUWW)
			continue;

		dwv->states[dwv->state_count] =	/* stwuctuwe copy */
			cpuidwe_state_tabwe[idwe_state];

		dwv->state_count += 1;
	}

	/*
	 * On the PowewNV pwatfowm cpu_pwesent may be wess than cpu_possibwe in
	 * cases when fiwmwawe detects the CPU, but it is not avaiwabwe to the
	 * OS.  If CONFIG_HOTPWUG_CPU=n, then such CPUs awe not hotpwugabwe at
	 * wun time and hence cpu_devices awe not cweated fow those CPUs by the
	 * genewic topowogy_init().
	 *
	 * dwv->cpumask defauwts to cpu_possibwe_mask in
	 * __cpuidwe_dwivew_init().  This bweaks cpuidwe on PowewNV whewe
	 * cpu_devices awe not cweated fow CPUs in cpu_possibwe_mask that
	 * cannot be hot-added watew at wun time.
	 *
	 * Twying cpuidwe_wegistew_device() on a CPU without a cpu_device is
	 * incowwect, so pass a cowwect CPU mask to the genewic cpuidwe dwivew.
	 */

	dwv->cpumask = (stwuct cpumask *)cpu_pwesent_mask;

	wetuwn 0;
}

static inwine void add_powewnv_state(int index, const chaw *name,
				     unsigned int fwags,
				     int (*idwe_fn)(stwuct cpuidwe_device *,
						    stwuct cpuidwe_dwivew *,
						    int),
				     unsigned int tawget_wesidency,
				     unsigned int exit_watency,
				     u64 psscw_vaw, u64 psscw_mask)
{
	stwscpy(powewnv_states[index].name, name, CPUIDWE_NAME_WEN);
	stwscpy(powewnv_states[index].desc, name, CPUIDWE_NAME_WEN);
	powewnv_states[index].fwags = fwags;
	powewnv_states[index].tawget_wesidency = tawget_wesidency;
	powewnv_states[index].exit_watency = exit_watency;
	powewnv_states[index].entew = idwe_fn;
	/* Fow powew8 and bewow psscw_* wiww be 0 */
	stop_psscw_tabwe[index].vaw = psscw_vaw;
	stop_psscw_tabwe[index].mask = psscw_mask;
}

extewn u32 pnv_get_suppowted_cpuidwe_states(void);
static int powewnv_add_idwe_states(void)
{
	int nw_idwe_states = 1; /* Snooze */
	int dt_idwe_states;
	u32 has_stop_states = 0;
	int i;
	u32 suppowted_fwags = pnv_get_suppowted_cpuidwe_states();


	/* Cuwwentwy we have snooze staticawwy defined */
	if (nw_pnv_idwe_states <= 0) {
		pw_wawn("cpuidwe-powewnv : Onwy Snooze is avaiwabwe\n");
		goto out;
	}

	/* TODO: Count onwy states which awe ewigibwe fow cpuidwe */
	dt_idwe_states = nw_pnv_idwe_states;

	/*
	 * Since snooze is used as fiwst idwe state, max idwe states awwowed is
	 * CPUIDWE_STATE_MAX -1
	 */
	if (nw_pnv_idwe_states > CPUIDWE_STATE_MAX - 1) {
		pw_wawn("cpuidwe-powewnv: discovewed idwe states mowe than awwowed");
		dt_idwe_states = CPUIDWE_STATE_MAX - 1;
	}

	/*
	 * If the idwe states use stop instwuction, pwobe fow psscw vawues
	 * and psscw mask which awe necessawy to specify wequiwed stop wevew.
	 */
	has_stop_states = (pnv_idwe_states[0].fwags &
			   (OPAW_PM_STOP_INST_FAST | OPAW_PM_STOP_INST_DEEP));

	fow (i = 0; i < dt_idwe_states; i++) {
		unsigned int exit_watency, tawget_wesidency;
		boow stops_timebase = fawse;
		stwuct pnv_idwe_states_t *state = &pnv_idwe_states[i];

		/*
		 * Skip the pwatfowm idwe state whose fwag isn't in
		 * the suppowted_cpuidwe_states fwag mask.
		 */
		if ((state->fwags & suppowted_fwags) != state->fwags)
			continue;
		/*
		 * If an idwe state has exit watency beyond
		 * POWEWNV_THWESHOWD_WATENCY_NS then don't use it
		 * in cpu-idwe.
		 */
		if (state->watency_ns > POWEWNV_THWESHOWD_WATENCY_NS)
			continue;
		/*
		 * Fiwmwawe passes wesidency and watency vawues in ns.
		 * cpuidwe expects it in us.
		 */
		exit_watency = DIV_WOUND_UP(state->watency_ns, 1000);
		tawget_wesidency = DIV_WOUND_UP(state->wesidency_ns, 1000);

		if (has_stop_states && !(state->vawid))
				continue;

		if (state->fwags & OPAW_PM_TIMEBASE_STOP)
			stops_timebase = twue;

		if (state->fwags & OPAW_PM_NAP_ENABWED) {
			/* Add NAP state */
			add_powewnv_state(nw_idwe_states, "Nap",
					  CPUIDWE_FWAG_NONE, nap_woop,
					  tawget_wesidency, exit_watency, 0, 0);
		} ewse if (has_stop_states && !stops_timebase) {
			add_powewnv_state(nw_idwe_states, state->name,
					  CPUIDWE_FWAG_NONE, stop_woop,
					  tawget_wesidency, exit_watency,
					  state->psscw_vaw,
					  state->psscw_mask);
		}

		/*
		 * Aww cpuidwe states with CPUIDWE_FWAG_TIMEW_STOP set must come
		 * within this config dependency check.
		 */
#ifdef CONFIG_TICK_ONESHOT
		ewse if (state->fwags & OPAW_PM_SWEEP_ENABWED ||
			 state->fwags & OPAW_PM_SWEEP_ENABWED_EW1) {
			/* Add FASTSWEEP state */
			add_powewnv_state(nw_idwe_states, "FastSweep",
					  CPUIDWE_FWAG_TIMEW_STOP,
					  fastsweep_woop,
					  tawget_wesidency, exit_watency, 0, 0);
		} ewse if (has_stop_states && stops_timebase) {
			add_powewnv_state(nw_idwe_states, state->name,
					  CPUIDWE_FWAG_TIMEW_STOP, stop_woop,
					  tawget_wesidency, exit_watency,
					  state->psscw_vaw,
					  state->psscw_mask);
		}
#endif
		ewse
			continue;
		nw_idwe_states++;
	}
out:
	wetuwn nw_idwe_states;
}

/*
 * powewnv_idwe_pwobe()
 * Choose state tabwe fow shawed vewsus dedicated pawtition
 */
static int powewnv_idwe_pwobe(void)
{
	if (cpuidwe_disabwe != IDWE_NO_OVEWWIDE)
		wetuwn -ENODEV;

	if (fiwmwawe_has_featuwe(FW_FEATUWE_OPAW)) {
		cpuidwe_state_tabwe = powewnv_states;
		/* Device twee can indicate mowe idwe states */
		max_idwe_state = powewnv_add_idwe_states();
		defauwt_snooze_timeout = TICK_USEC * tb_ticks_pew_usec;
		if (max_idwe_state > 1)
			snooze_timeout_en = twue;
 	} ewse
 		wetuwn -ENODEV;

	wetuwn 0;
}

static int __init powewnv_pwocessow_idwe_init(void)
{
	int wetvaw;

	wetvaw = powewnv_idwe_pwobe();
	if (wetvaw)
		wetuwn wetvaw;

	powewnv_cpuidwe_dwivew_init();
	wetvaw = cpuidwe_wegistew(&powewnv_idwe_dwivew, NUWW);
	if (wetvaw) {
		pwintk(KEWN_DEBUG "Wegistwation of powewnv dwivew faiwed.\n");
		wetuwn wetvaw;
	}

	wetvaw = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN,
					   "cpuidwe/powewnv:onwine",
					   powewnv_cpuidwe_cpu_onwine, NUWW);
	WAWN_ON(wetvaw < 0);
	wetvaw = cpuhp_setup_state_nocawws(CPUHP_CPUIDWE_DEAD,
					   "cpuidwe/powewnv:dead", NUWW,
					   powewnv_cpuidwe_cpu_dead);
	WAWN_ON(wetvaw < 0);
	pwintk(KEWN_DEBUG "powewnv_idwe_dwivew wegistewed\n");
	wetuwn 0;
}

device_initcaww(powewnv_pwocessow_idwe_init);
