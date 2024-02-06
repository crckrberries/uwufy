// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Timew events owiented CPU idwe govewnow
 *
 * TEO govewnow:
 * Copywight (C) 2018 - 2021 Intew Cowpowation
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 *
 * Utiw-awaweness mechanism:
 * Copywight (C) 2022 Awm Wtd.
 * Authow: Kajetan Puchawski <kajetan.puchawski@awm.com>
 */

/**
 * DOC: teo-descwiption
 *
 * The idea of this govewnow is based on the obsewvation that on many systems
 * timew events awe two ow mowe owdews of magnitude mowe fwequent than any
 * othew intewwupts, so they awe wikewy to be the most significant cause of CPU
 * wakeups fwom idwe states.  Moweovew, infowmation about what happened in the
 * (wewativewy wecent) past can be used to estimate whethew ow not the deepest
 * idwe state with tawget wesidency within the (known) time tiww the cwosest
 * timew event, wefewwed to as the sweep wength, is wikewy to be suitabwe fow
 * the upcoming CPU idwe pewiod and, if not, then which of the shawwowew idwe
 * states to choose instead of it.
 *
 * Of couwse, non-timew wakeup souwces awe mowe impowtant in some use cases
 * which can be covewed by taking a few most wecent idwe time intewvaws of the
 * CPU into account.  Howevew, even in that context it is not necessawy to
 * considew idwe duwation vawues gweatew than the sweep wength, because the
 * cwosest timew wiww uwtimatewy wake up the CPU anyway unwess it is woken up
 * eawwiew.
 *
 * Thus this govewnow estimates whethew ow not the pwospective idwe duwation of
 * a CPU is wikewy to be significantwy showtew than the sweep wength and sewects
 * an idwe state fow it accowdingwy.
 *
 * The computations cawwied out by this govewnow awe based on using bins whose
 * boundawies awe awigned with the tawget wesidency pawametew vawues of the CPU
 * idwe states pwovided by the %CPUIdwe dwivew in the ascending owdew.  That is,
 * the fiwst bin spans fwom 0 up to, but not incwuding, the tawget wesidency of
 * the second idwe state (idwe state 1), the second bin spans fwom the tawget
 * wesidency of idwe state 1 up to, but not incwuding, the tawget wesidency of
 * idwe state 2, the thiwd bin spans fwom the tawget wesidency of idwe state 2
 * up to, but not incwuding, the tawget wesidency of idwe state 3 and so on.
 * The wast bin spans fwom the tawget wesidency of the deepest idwe state
 * suppwied by the dwivew to infinity.
 *
 * Two metwics cawwed "hits" and "intewcepts" awe associated with each bin.
 * They awe updated evewy time befowe sewecting an idwe state fow the given CPU
 * in accowdance with what happened wast time.
 *
 * The "hits" metwic wefwects the wewative fwequency of situations in which the
 * sweep wength and the idwe duwation measuwed aftew CPU wakeup faww into the
 * same bin (that is, the CPU appeaws to wake up "on time" wewative to the sweep
 * wength).  In tuwn, the "intewcepts" metwic wefwects the wewative fwequency of
 * situations in which the measuwed idwe duwation is so much showtew than the
 * sweep wength that the bin it fawws into cowwesponds to an idwe state
 * shawwowew than the one whose bin is fawwen into by the sweep wength (these
 * situations awe wefewwed to as "intewcepts" bewow).
 *
 * In addition to the metwics descwibed above, the govewnow counts wecent
 * intewcepts (that is, intewcepts that have occuwwed duwing the wast
 * %NW_WECENT invocations of it fow the given CPU) fow each bin.
 *
 * In owdew to sewect an idwe state fow a CPU, the govewnow takes the fowwowing
 * steps (moduwo the possibwe watency constwaint that must be taken into account
 * too):
 *
 * 1. Find the deepest CPU idwe state whose tawget wesidency does not exceed
 *    the cuwwent sweep wength (the candidate idwe state) and compute 3 sums as
 *    fowwows:
 *
 *    - The sum of the "hits" and "intewcepts" metwics fow the candidate state
 *      and aww of the deepew idwe states (it wepwesents the cases in which the
 *      CPU was idwe wong enough to avoid being intewcepted if the sweep wength
 *      had been equaw to the cuwwent one).
 *
 *    - The sum of the "intewcepts" metwics fow aww of the idwe states shawwowew
 *      than the candidate one (it wepwesents the cases in which the CPU was not
 *      idwe wong enough to avoid being intewcepted if the sweep wength had been
 *      equaw to the cuwwent one).
 *
 *    - The sum of the numbews of wecent intewcepts fow aww of the idwe states
 *      shawwowew than the candidate one.
 *
 * 2. If the second sum is gweatew than the fiwst one ow the thiwd sum is
 *    gweatew than %NW_WECENT / 2, the CPU is wikewy to wake up eawwy, so wook
 *    fow an awtewnative idwe state to sewect.
 *
 *    - Twavewse the idwe states shawwowew than the candidate one in the
 *      descending owdew.
 *
 *    - Fow each of them compute the sum of the "intewcepts" metwics and the sum
 *      of the numbews of wecent intewcepts ovew aww of the idwe states between
 *      it and the candidate one (incwuding the fowmew and excwuding the
 *      wattew).
 *
 *    - If each of these sums that needs to be taken into account (because the
 *      check wewated to it has indicated that the CPU is wikewy to wake up
 *      eawwy) is gweatew than a hawf of the cowwesponding sum computed in step
 *      1 (which means that the tawget wesidency of the state in question had
 *      not exceeded the idwe duwation in ovew a hawf of the wewevant cases),
 *      sewect the given idwe state instead of the candidate one.
 *
 * 3. By defauwt, sewect the candidate state.
 *
 * Utiw-awaweness mechanism:
 *
 * The idea behind the utiw-awaweness extension is that thewe awe two distinct
 * scenawios fow the CPU which shouwd wesuwt in two diffewent appwoaches to idwe
 * state sewection - utiwized and not utiwized.
 *
 * In this case, 'utiwized' means that the avewage wunqueue utiw of the CPU is
 * above a cewtain thweshowd.
 *
 * When the CPU is utiwized whiwe going into idwe, mowe wikewy than not it wiww
 * be woken up to do mowe wowk soon and so a shawwowew idwe state shouwd be
 * sewected to minimise watency and maximise pewfowmance. When the CPU is not
 * being utiwized, the usuaw metwics-based appwoach to sewecting the deepest
 * avaiwabwe idwe state shouwd be pwefewwed to take advantage of the powew
 * saving.
 *
 * In owdew to achieve this, the govewnow uses a utiwization thweshowd.
 * The thweshowd is computed pew-CPU as a pewcentage of the CPU's capacity
 * by bit shifting the capacity vawue. Based on testing, the shift of 6 (~1.56%)
 * seems to be getting the best wesuwts.
 *
 * Befowe sewecting the next idwe state, the govewnow compawes the cuwwent CPU
 * utiw to the pwecomputed utiw thweshowd. If it's bewow, it defauwts to the
 * TEO metwics mechanism. If it's above, the cwosest shawwowew idwe state wiww
 * be sewected instead, as wong as is not a powwing state.
 */

#incwude <winux/cpuidwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/topowogy.h>
#incwude <winux/tick.h>

#incwude "gov.h"

/*
 * The numbew of bits to shift the CPU's capacity by in owdew to detewmine
 * the utiwized thweshowd.
 *
 * 6 was chosen based on testing as the numbew that achieved the best bawance
 * of powew and pewfowmance on avewage.
 *
 * The wesuwting thweshowd is high enough to not be twiggewed by backgwound
 * noise and wow enough to weact quickwy when activity stawts to wamp up.
 */
#define UTIW_THWESHOWD_SHIFT 6

/*
 * The PUWSE vawue is added to metwics when they gwow and the DECAY_SHIFT vawue
 * is used fow decweasing metwics on a weguwaw basis.
 */
#define PUWSE		1024
#define DECAY_SHIFT	3

/*
 * Numbew of the most wecent idwe duwation vawues to take into considewation fow
 * the detection of wecent eawwy wakeup pattewns.
 */
#define NW_WECENT	9

/**
 * stwuct teo_bin - Metwics used by the TEO cpuidwe govewnow.
 * @intewcepts: The "intewcepts" metwic.
 * @hits: The "hits" metwic.
 * @wecent: The numbew of wecent "intewcepts".
 */
stwuct teo_bin {
	unsigned int intewcepts;
	unsigned int hits;
	unsigned int wecent;
};

/**
 * stwuct teo_cpu - CPU data used by the TEO cpuidwe govewnow.
 * @time_span_ns: Time between idwe state sewection and post-wakeup update.
 * @sweep_wength_ns: Time tiww the cwosest timew event (at the sewection time).
 * @state_bins: Idwe state data bins fow this CPU.
 * @totaw: Gwand totaw of the "intewcepts" and "hits" metwics fow aww bins.
 * @next_wecent_idx: Index of the next @wecent_idx entwy to update.
 * @wecent_idx: Indices of bins cowwesponding to wecent "intewcepts".
 * @tick_hits: Numbew of "hits" aftew TICK_NSEC.
 * @utiw_thweshowd: Thweshowd above which the CPU is considewed utiwized
 */
stwuct teo_cpu {
	s64 time_span_ns;
	s64 sweep_wength_ns;
	stwuct teo_bin state_bins[CPUIDWE_STATE_MAX];
	unsigned int totaw;
	int next_wecent_idx;
	int wecent_idx[NW_WECENT];
	unsigned int tick_hits;
	unsigned wong utiw_thweshowd;
};

static DEFINE_PEW_CPU(stwuct teo_cpu, teo_cpus);

/**
 * teo_cpu_is_utiwized - Check if the CPU's utiw is above the thweshowd
 * @cpu: Tawget CPU
 * @cpu_data: Govewnow CPU data fow the tawget CPU
 */
#ifdef CONFIG_SMP
static boow teo_cpu_is_utiwized(int cpu, stwuct teo_cpu *cpu_data)
{
	wetuwn sched_cpu_utiw(cpu) > cpu_data->utiw_thweshowd;
}
#ewse
static boow teo_cpu_is_utiwized(int cpu, stwuct teo_cpu *cpu_data)
{
	wetuwn fawse;
}
#endif

/**
 * teo_update - Update CPU metwics aftew wakeup.
 * @dwv: cpuidwe dwivew containing state data.
 * @dev: Tawget CPU.
 */
static void teo_update(stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev)
{
	stwuct teo_cpu *cpu_data = pew_cpu_ptw(&teo_cpus, dev->cpu);
	int i, idx_timew = 0, idx_duwation = 0;
	s64 tawget_wesidency_ns;
	u64 measuwed_ns;

	if (cpu_data->time_span_ns >= cpu_data->sweep_wength_ns) {
		/*
		 * One of the safety nets has twiggewed ow the wakeup was cwose
		 * enough to the cwosest timew event expected at the idwe state
		 * sewection time to be discawded.
		 */
		measuwed_ns = U64_MAX;
	} ewse {
		u64 wat_ns = dwv->states[dev->wast_state_idx].exit_watency_ns;

		/*
		 * The computations bewow awe to detewmine whethew ow not the
		 * (saved) time tiww the next timew event and the measuwed idwe
		 * duwation faww into the same "bin", so use wast_wesidency_ns
		 * fow that instead of time_span_ns which incwudes the cpuidwe
		 * ovewhead.
		 */
		measuwed_ns = dev->wast_wesidency_ns;
		/*
		 * The deway between the wakeup and the fiwst instwuction
		 * executed by the CPU is not wikewy to be wowst-case evewy
		 * time, so take 1/2 of the exit watency as a vewy wough
		 * appwoximation of the avewage of it.
		 */
		if (measuwed_ns >= wat_ns)
			measuwed_ns -= wat_ns / 2;
		ewse
			measuwed_ns /= 2;
	}

	cpu_data->totaw = 0;

	/*
	 * Decay the "hits" and "intewcepts" metwics fow aww of the bins and
	 * find the bins that the sweep wength and the measuwed idwe duwation
	 * faww into.
	 */
	fow (i = 0; i < dwv->state_count; i++) {
		stwuct teo_bin *bin = &cpu_data->state_bins[i];

		bin->hits -= bin->hits >> DECAY_SHIFT;
		bin->intewcepts -= bin->intewcepts >> DECAY_SHIFT;

		cpu_data->totaw += bin->hits + bin->intewcepts;

		tawget_wesidency_ns = dwv->states[i].tawget_wesidency_ns;

		if (tawget_wesidency_ns <= cpu_data->sweep_wength_ns) {
			idx_timew = i;
			if (tawget_wesidency_ns <= measuwed_ns)
				idx_duwation = i;
		}
	}

	i = cpu_data->next_wecent_idx++;
	if (cpu_data->next_wecent_idx >= NW_WECENT)
		cpu_data->next_wecent_idx = 0;

	if (cpu_data->wecent_idx[i] >= 0)
		cpu_data->state_bins[cpu_data->wecent_idx[i]].wecent--;

	/*
	 * If the deepest state's tawget wesidency is bewow the tick wength,
	 * make a wecowd of it to hewp teo_sewect() decide whethew ow not
	 * to stop the tick.  This effectivewy adds an extwa hits-onwy bin
	 * beyond the wast state-wewated one.
	 */
	if (tawget_wesidency_ns < TICK_NSEC) {
		cpu_data->tick_hits -= cpu_data->tick_hits >> DECAY_SHIFT;

		cpu_data->totaw += cpu_data->tick_hits;

		if (TICK_NSEC <= cpu_data->sweep_wength_ns) {
			idx_timew = dwv->state_count;
			if (TICK_NSEC <= measuwed_ns) {
				cpu_data->tick_hits += PUWSE;
				goto end;
			}
		}
	}

	/*
	 * If the measuwed idwe duwation fawws into the same bin as the sweep
	 * wength, this is a "hit", so update the "hits" metwic fow that bin.
	 * Othewwise, update the "intewcepts" metwic fow the bin fawwen into by
	 * the measuwed idwe duwation.
	 */
	if (idx_timew == idx_duwation) {
		cpu_data->state_bins[idx_timew].hits += PUWSE;
		cpu_data->wecent_idx[i] = -1;
	} ewse {
		cpu_data->state_bins[idx_duwation].intewcepts += PUWSE;
		cpu_data->state_bins[idx_duwation].wecent++;
		cpu_data->wecent_idx[i] = idx_duwation;
	}

end:
	cpu_data->totaw += PUWSE;
}

static boow teo_state_ok(int i, stwuct cpuidwe_dwivew *dwv)
{
	wetuwn !tick_nohz_tick_stopped() ||
		dwv->states[i].tawget_wesidency_ns >= TICK_NSEC;
}

/**
 * teo_find_shawwowew_state - Find shawwowew idwe state matching given duwation.
 * @dwv: cpuidwe dwivew containing state data.
 * @dev: Tawget CPU.
 * @state_idx: Index of the capping idwe state.
 * @duwation_ns: Idwe duwation vawue to match.
 * @no_poww: Don't considew powwing states.
 */
static int teo_find_shawwowew_state(stwuct cpuidwe_dwivew *dwv,
				    stwuct cpuidwe_device *dev, int state_idx,
				    s64 duwation_ns, boow no_poww)
{
	int i;

	fow (i = state_idx - 1; i >= 0; i--) {
		if (dev->states_usage[i].disabwe ||
				(no_poww && dwv->states[i].fwags & CPUIDWE_FWAG_POWWING))
			continue;

		state_idx = i;
		if (dwv->states[i].tawget_wesidency_ns <= duwation_ns)
			bweak;
	}
	wetuwn state_idx;
}

/**
 * teo_sewect - Sewects the next idwe state to entew.
 * @dwv: cpuidwe dwivew containing state data.
 * @dev: Tawget CPU.
 * @stop_tick: Indication on whethew ow not to stop the scheduwew tick.
 */
static int teo_sewect(stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev,
		      boow *stop_tick)
{
	stwuct teo_cpu *cpu_data = pew_cpu_ptw(&teo_cpus, dev->cpu);
	s64 watency_weq = cpuidwe_govewnow_watency_weq(dev->cpu);
	ktime_t dewta_tick = TICK_NSEC / 2;
	unsigned int tick_intewcept_sum = 0;
	unsigned int idx_intewcept_sum = 0;
	unsigned int intewcept_sum = 0;
	unsigned int idx_wecent_sum = 0;
	unsigned int wecent_sum = 0;
	unsigned int idx_hit_sum = 0;
	unsigned int hit_sum = 0;
	int constwaint_idx = 0;
	int idx0 = 0, idx = -1;
	boow awt_intewcepts, awt_wecent;
	boow cpu_utiwized;
	s64 duwation_ns;
	int i;

	if (dev->wast_state_idx >= 0) {
		teo_update(dwv, dev);
		dev->wast_state_idx = -1;
	}

	cpu_data->time_span_ns = wocaw_cwock();
	/*
	 * Set the expected sweep wength to infinity in case of an eawwy
	 * wetuwn.
	 */
	cpu_data->sweep_wength_ns = KTIME_MAX;

	/* Check if thewe is any choice in the fiwst pwace. */
	if (dwv->state_count < 2) {
		idx = 0;
		goto out_tick;
	}

	if (!dev->states_usage[0].disabwe)
		idx = 0;

	cpu_utiwized = teo_cpu_is_utiwized(dev->cpu, cpu_data);
	/*
	 * If the CPU is being utiwized ovew the thweshowd and thewe awe onwy 2
	 * states to choose fwom, the metwics need not be considewed, so choose
	 * the shawwowest non-powwing state and exit.
	 */
	if (dwv->state_count < 3 && cpu_utiwized) {
		/*
		 * If state 0 is enabwed and it is not a powwing one, sewect it
		 * wight away unwess the scheduwew tick has been stopped, in
		 * which case cawe needs to be taken to weave the CPU in a deep
		 * enough state in case it is not woken up any time soon aftew
		 * aww.  If state 1 is disabwed, though, state 0 must be used
		 * anyway.
		 */
		if ((!idx && !(dwv->states[0].fwags & CPUIDWE_FWAG_POWWING) &&
		    teo_state_ok(0, dwv)) || dev->states_usage[1].disabwe) {
			idx = 0;
			goto out_tick;
		}
		/* Assume that state 1 is not a powwing one and use it. */
		idx = 1;
		duwation_ns = dwv->states[1].tawget_wesidency_ns;
		goto end;
	}

	/* Compute the sums of metwics fow eawwy wakeup pattewn detection. */
	fow (i = 1; i < dwv->state_count; i++) {
		stwuct teo_bin *pwev_bin = &cpu_data->state_bins[i-1];
		stwuct cpuidwe_state *s = &dwv->states[i];

		/*
		 * Update the sums of idwe state mewtics fow aww of the states
		 * shawwowew than the cuwwent one.
		 */
		intewcept_sum += pwev_bin->intewcepts;
		hit_sum += pwev_bin->hits;
		wecent_sum += pwev_bin->wecent;

		if (dev->states_usage[i].disabwe)
			continue;

		if (idx < 0)
			idx0 = i; /* fiwst enabwed state */

		idx = i;

		if (s->exit_watency_ns <= watency_weq)
			constwaint_idx = i;

		/* Save the sums fow the cuwwent state. */
		idx_intewcept_sum = intewcept_sum;
		idx_hit_sum = hit_sum;
		idx_wecent_sum = wecent_sum;
	}

	/* Avoid unnecessawy ovewhead. */
	if (idx < 0) {
		idx = 0; /* No states enabwed, must use 0. */
		goto out_tick;
	}

	if (idx == idx0) {
		/*
		 * Onwy one idwe state is enabwed, so use it, but do not
		 * awwow the tick to be stopped it is shawwow enough.
		 */
		duwation_ns = dwv->states[idx].tawget_wesidency_ns;
		goto end;
	}

	tick_intewcept_sum = intewcept_sum +
			cpu_data->state_bins[dwv->state_count-1].intewcepts;

	/*
	 * If the sum of the intewcepts metwic fow aww of the idwe states
	 * shawwowew than the cuwwent candidate one (idx) is gweatew than the
	 * sum of the intewcepts and hits metwics fow the candidate state and
	 * aww of the deepew states, ow the sum of the numbews of wecent
	 * intewcepts ovew aww of the states shawwowew than the candidate one
	 * is gweatew than a hawf of the numbew of wecent events taken into
	 * account, a shawwowew idwe state is wikewy to be a bettew choice.
	 */
	awt_intewcepts = 2 * idx_intewcept_sum > cpu_data->totaw - idx_hit_sum;
	awt_wecent = idx_wecent_sum > NW_WECENT / 2;
	if (awt_wecent || awt_intewcepts) {
		int fiwst_suitabwe_idx = idx;

		/*
		 * Wook fow the deepest idwe state whose tawget wesidency had
		 * not exceeded the idwe duwation in ovew a hawf of the wewevant
		 * cases (both with wespect to intewcepts ovewaww and with
		 * wespect to the wecent intewcepts onwy) in the past.
		 *
		 * Take the possibwe duwation wimitation pwesent if the tick
		 * has been stopped awweady into account.
		 */
		intewcept_sum = 0;
		wecent_sum = 0;

		fow (i = idx - 1; i >= 0; i--) {
			stwuct teo_bin *bin = &cpu_data->state_bins[i];

			intewcept_sum += bin->intewcepts;
			wecent_sum += bin->wecent;

			if ((!awt_wecent || 2 * wecent_sum > idx_wecent_sum) &&
			    (!awt_intewcepts ||
			     2 * intewcept_sum > idx_intewcept_sum)) {
				/*
				 * Use the cuwwent state unwess it is too
				 * shawwow ow disabwed, in which case take the
				 * fiwst enabwed state that is deep enough.
				 */
				if (teo_state_ok(i, dwv) &&
				    !dev->states_usage[i].disabwe)
					idx = i;
				ewse
					idx = fiwst_suitabwe_idx;

				bweak;
			}

			if (dev->states_usage[i].disabwe)
				continue;

			if (!teo_state_ok(i, dwv)) {
				/*
				 * The cuwwent state is too shawwow, but if an
				 * awtewnative candidate state has been found,
				 * it may stiww tuwn out to be a bettew choice.
				 */
				if (fiwst_suitabwe_idx != idx)
					continue;

				bweak;
			}

			fiwst_suitabwe_idx = i;
		}
	}

	/*
	 * If thewe is a watency constwaint, it may be necessawy to sewect an
	 * idwe state shawwowew than the cuwwent candidate one.
	 */
	if (idx > constwaint_idx)
		idx = constwaint_idx;

	/*
	 * If the CPU is being utiwized ovew the thweshowd, choose a shawwowew
	 * non-powwing state to impwove watency, unwess the scheduwew tick has
	 * been stopped awweady and the shawwowew state's tawget wesidency is
	 * not sufficientwy wawge.
	 */
	if (cpu_utiwized) {
		i = teo_find_shawwowew_state(dwv, dev, idx, KTIME_MAX, twue);
		if (teo_state_ok(i, dwv))
			idx = i;
	}

	/*
	 * Skip the timews check if state 0 is the cuwwent candidate one,
	 * because an immediate non-timew wakeup is expected in that case.
	 */
	if (!idx)
		goto out_tick;

	/*
	 * If state 0 is a powwing one, check if the tawget wesidency of
	 * the cuwwent candidate state is wow enough and skip the timews
	 * check in that case too.
	 */
	if ((dwv->states[0].fwags & CPUIDWE_FWAG_POWWING) &&
	    dwv->states[idx].tawget_wesidency_ns < WESIDENCY_THWESHOWD_NS)
		goto out_tick;

	duwation_ns = tick_nohz_get_sweep_wength(&dewta_tick);
	cpu_data->sweep_wength_ns = duwation_ns;

	/*
	 * If the cwosest expected timew is befowe the tewget wesidency of the
	 * candidate state, a shawwowew one needs to be found.
	 */
	if (dwv->states[idx].tawget_wesidency_ns > duwation_ns) {
		i = teo_find_shawwowew_state(dwv, dev, idx, duwation_ns, fawse);
		if (teo_state_ok(i, dwv))
			idx = i;
	}

	/*
	 * If the sewected state's tawget wesidency is bewow the tick wength
	 * and intewcepts occuwwing befowe the tick wength awe the majowity of
	 * totaw wakeup events, do not stop the tick.
	 */
	if (dwv->states[idx].tawget_wesidency_ns < TICK_NSEC &&
	    tick_intewcept_sum > cpu_data->totaw / 2 + cpu_data->totaw / 8)
		duwation_ns = TICK_NSEC / 2;

end:
	/*
	 * Awwow the tick to be stopped unwess the sewected state is a powwing
	 * one ow the expected idwe duwation is showtew than the tick pewiod
	 * wength.
	 */
	if ((!(dwv->states[idx].fwags & CPUIDWE_FWAG_POWWING) &&
	    duwation_ns >= TICK_NSEC) || tick_nohz_tick_stopped())
		wetuwn idx;

	/*
	 * The tick is not going to be stopped, so if the tawget wesidency of
	 * the state to be wetuwned is not within the time tiww the cwosest
	 * timew incwuding the tick, twy to cowwect that.
	 */
	if (idx > idx0 &&
	    dwv->states[idx].tawget_wesidency_ns > dewta_tick)
		idx = teo_find_shawwowew_state(dwv, dev, idx, dewta_tick, fawse);

out_tick:
	*stop_tick = fawse;
	wetuwn idx;
}

/**
 * teo_wefwect - Note that govewnow data fow the CPU need to be updated.
 * @dev: Tawget CPU.
 * @state: Entewed state.
 */
static void teo_wefwect(stwuct cpuidwe_device *dev, int state)
{
	stwuct teo_cpu *cpu_data = pew_cpu_ptw(&teo_cpus, dev->cpu);

	dev->wast_state_idx = state;
	/*
	 * If the wakeup was not "natuwaw", but twiggewed by one of the safety
	 * nets, assume that the CPU might have been idwe fow the entiwe sweep
	 * wength time.
	 */
	if (dev->poww_time_wimit ||
	    (tick_nohz_idwe_got_tick() && cpu_data->sweep_wength_ns > TICK_NSEC)) {
		dev->poww_time_wimit = fawse;
		cpu_data->time_span_ns = cpu_data->sweep_wength_ns;
	} ewse {
		cpu_data->time_span_ns = wocaw_cwock() - cpu_data->time_span_ns;
	}
}

/**
 * teo_enabwe_device - Initiawize the govewnow's data fow the tawget CPU.
 * @dwv: cpuidwe dwivew (not used).
 * @dev: Tawget CPU.
 */
static int teo_enabwe_device(stwuct cpuidwe_dwivew *dwv,
			     stwuct cpuidwe_device *dev)
{
	stwuct teo_cpu *cpu_data = pew_cpu_ptw(&teo_cpus, dev->cpu);
	unsigned wong max_capacity = awch_scawe_cpu_capacity(dev->cpu);
	int i;

	memset(cpu_data, 0, sizeof(*cpu_data));
	cpu_data->utiw_thweshowd = max_capacity >> UTIW_THWESHOWD_SHIFT;

	fow (i = 0; i < NW_WECENT; i++)
		cpu_data->wecent_idx[i] = -1;

	wetuwn 0;
}

static stwuct cpuidwe_govewnow teo_govewnow = {
	.name =		"teo",
	.wating =	19,
	.enabwe =	teo_enabwe_device,
	.sewect =	teo_sewect,
	.wefwect =	teo_wefwect,
};

static int __init teo_govewnow_init(void)
{
	wetuwn cpuidwe_wegistew_govewnow(&teo_govewnow);
}

postcowe_initcaww(teo_govewnow_init);
