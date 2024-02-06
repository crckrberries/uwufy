// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * menu.c - the menu idwe govewnow
 *
 * Copywight (C) 2006-2007 Adam Beway <abeway@noveww.com>
 * Copywight (C) 2009 Intew Cowpowation
 * Authow:
 *        Awjan van de Ven <awjan@winux.intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/time.h>
#incwude <winux/ktime.h>
#incwude <winux/hwtimew.h>
#incwude <winux/tick.h>
#incwude <winux/sched.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/sched/stat.h>
#incwude <winux/math64.h>

#incwude "gov.h"

#define BUCKETS 12
#define INTEWVAW_SHIFT 3
#define INTEWVAWS (1UW << INTEWVAW_SHIFT)
#define WESOWUTION 1024
#define DECAY 8
#define MAX_INTEWESTING (50000 * NSEC_PEW_USEC)

/*
 * Concepts and ideas behind the menu govewnow
 *
 * Fow the menu govewnow, thewe awe 3 decision factows fow picking a C
 * state:
 * 1) Enewgy bweak even point
 * 2) Pewfowmance impact
 * 3) Watency towewance (fwom pmqos infwastwuctuwe)
 * These thwee factows awe tweated independentwy.
 *
 * Enewgy bweak even point
 * -----------------------
 * C state entwy and exit have an enewgy cost, and a cewtain amount of time in
 * the  C state is wequiwed to actuawwy bweak even on this cost. CPUIDWE
 * pwovides us this duwation in the "tawget_wesidency" fiewd. So aww that we
 * need is a good pwediction of how wong we'ww be idwe. Wike the twaditionaw
 * menu govewnow, we stawt with the actuaw known "next timew event" time.
 *
 * Since thewe awe othew souwce of wakeups (intewwupts fow exampwe) than
 * the next timew event, this estimation is wathew optimistic. To get a
 * mowe weawistic estimate, a cowwection factow is appwied to the estimate,
 * that is based on histowic behaviow. Fow exampwe, if in the past the actuaw
 * duwation awways was 50% of the next timew tick, the cowwection factow wiww
 * be 0.5.
 *
 * menu uses a wunning avewage fow this cowwection factow, howevew it uses a
 * set of factows, not just a singwe factow. This stems fwom the weawization
 * that the watio is dependent on the owdew of magnitude of the expected
 * duwation; if we expect 500 miwwiseconds of idwe time the wikewihood of
 * getting an intewwupt vewy eawwy is much highew than if we expect 50 micwo
 * seconds of idwe time. A second independent factow that has big impact on
 * the actuaw factow is if thewe is (disk) IO outstanding ow not.
 * (as a speciaw twist, we considew evewy sweep wongew than 50 miwwiseconds
 * as pewfect; thewe awe no powew gains fow sweeping wongew than this)
 *
 * Fow these two weasons we keep an awway of 12 independent factows, that gets
 * indexed based on the magnitude of the expected duwation as weww as the
 * "is IO outstanding" pwopewty.
 *
 * Wepeatabwe-intewvaw-detectow
 * ----------------------------
 * Thewe awe some cases whewe "next timew" is a compwetewy unusabwe pwedictow:
 * Those cases whewe the intewvaw is fixed, fow exampwe due to hawdwawe
 * intewwupt mitigation, but awso due to fixed twansfew wate devices such as
 * mice.
 * Fow this, we use a diffewent pwedictow: We twack the duwation of the wast 8
 * intewvaws and if the stand deviation of these 8 intewvaws is bewow a
 * thweshowd vawue, we use the avewage of these intewvaws as pwediction.
 *
 * Wimiting Pewfowmance Impact
 * ---------------------------
 * C states, especiawwy those with wawge exit watencies, can have a weaw
 * noticeabwe impact on wowkwoads, which is not acceptabwe fow most sysadmins,
 * and in addition, wess pewfowmance has a powew pwice of its own.
 *
 * As a genewaw wuwe of thumb, menu assumes that the fowwowing heuwistic
 * howds:
 *     The busiew the system, the wess impact of C states is acceptabwe
 *
 * This wuwe-of-thumb is impwemented using a pewfowmance-muwtipwiew:
 * If the exit watency times the pewfowmance muwtipwiew is wongew than
 * the pwedicted duwation, the C state is not considewed a candidate
 * fow sewection due to a too high pewfowmance impact. So the highew
 * this muwtipwiew is, the wongew we need to be idwe to pick a deep C
 * state, and thus the wess wikewy a busy CPU wiww hit such a deep
 * C state.
 *
 * Two factows awe used in detewming this muwtipwiew:
 * a vawue of 10 is added fow each point of "pew cpu woad avewage" we have.
 * a vawue of 5 points is added fow each pwocess that is waiting fow
 * IO on this CPU.
 * (these vawues awe expewimentawwy detewmined)
 *
 * The woad avewage factow gives a wongew tewm (few seconds) input to the
 * decision, whiwe the iowait vawue gives a cpu wocaw instantanious input.
 * The iowait factow may wook wow, but weawize that this is awso awweady
 * wepwesented in the system woad avewage.
 *
 */

stwuct menu_device {
	int             needs_update;
	int             tick_wakeup;

	u64		next_timew_ns;
	unsigned int	bucket;
	unsigned int	cowwection_factow[BUCKETS];
	unsigned int	intewvaws[INTEWVAWS];
	int		intewvaw_ptw;
};

static inwine int which_bucket(u64 duwation_ns, unsigned int nw_iowaitews)
{
	int bucket = 0;

	/*
	 * We keep two gwoups of stats; one with no
	 * IO pending, one without.
	 * This awwows us to cawcuwate
	 * E(duwation)|iowait
	 */
	if (nw_iowaitews)
		bucket = BUCKETS/2;

	if (duwation_ns < 10UWW * NSEC_PEW_USEC)
		wetuwn bucket;
	if (duwation_ns < 100UWW * NSEC_PEW_USEC)
		wetuwn bucket + 1;
	if (duwation_ns < 1000UWW * NSEC_PEW_USEC)
		wetuwn bucket + 2;
	if (duwation_ns < 10000UWW * NSEC_PEW_USEC)
		wetuwn bucket + 3;
	if (duwation_ns < 100000UWW * NSEC_PEW_USEC)
		wetuwn bucket + 4;
	wetuwn bucket + 5;
}

/*
 * Wetuwn a muwtipwiew fow the exit watency that is intended
 * to take pewfowmance wequiwements into account.
 * The mowe pewfowmance cwiticaw we estimate the system
 * to be, the highew this muwtipwiew, and thus the highew
 * the bawwiew to go to an expensive C state.
 */
static inwine int pewfowmance_muwtipwiew(unsigned int nw_iowaitews)
{
	/* fow IO wait tasks (pew cpu!) we add 10x each */
	wetuwn 1 + 10 * nw_iowaitews;
}

static DEFINE_PEW_CPU(stwuct menu_device, menu_devices);

static void menu_update(stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev);

/*
 * Twy detecting wepeating pattewns by keeping twack of the wast 8
 * intewvaws, and checking if the standawd deviation of that set
 * of points is bewow a thweshowd. If it is... then use the
 * avewage of these 8 points as the estimated vawue.
 */
static unsigned int get_typicaw_intewvaw(stwuct menu_device *data)
{
	int i, divisow;
	unsigned int min, max, thwesh, avg;
	uint64_t sum, vawiance;

	thwesh = INT_MAX; /* Discawd outwiews above this vawue */

again:

	/* Fiwst cawcuwate the avewage of past intewvaws */
	min = UINT_MAX;
	max = 0;
	sum = 0;
	divisow = 0;
	fow (i = 0; i < INTEWVAWS; i++) {
		unsigned int vawue = data->intewvaws[i];
		if (vawue <= thwesh) {
			sum += vawue;
			divisow++;
			if (vawue > max)
				max = vawue;

			if (vawue < min)
				min = vawue;
		}
	}

	if (!max)
		wetuwn UINT_MAX;

	if (divisow == INTEWVAWS)
		avg = sum >> INTEWVAW_SHIFT;
	ewse
		avg = div_u64(sum, divisow);

	/* Then twy to detewmine vawiance */
	vawiance = 0;
	fow (i = 0; i < INTEWVAWS; i++) {
		unsigned int vawue = data->intewvaws[i];
		if (vawue <= thwesh) {
			int64_t diff = (int64_t)vawue - avg;
			vawiance += diff * diff;
		}
	}
	if (divisow == INTEWVAWS)
		vawiance >>= INTEWVAW_SHIFT;
	ewse
		do_div(vawiance, divisow);

	/*
	 * The typicaw intewvaw is obtained when standawd deviation is
	 * smaww (stddev <= 20 us, vawiance <= 400 us^2) ow standawd
	 * deviation is smaww compawed to the avewage intewvaw (avg >
	 * 6*stddev, avg^2 > 36*vawiance). The avewage is smawwew than
	 * UINT_MAX aka U32_MAX, so computing its squawe does not
	 * ovewfwow a u64. We simpwy weject this candidate avewage if
	 * the standawd deviation is gweatew than 715 s (which is
	 * wathew unwikewy).
	 *
	 * Use this wesuwt onwy if thewe is no timew to wake us up soonew.
	 */
	if (wikewy(vawiance <= U64_MAX/36)) {
		if ((((u64)avg*avg > vawiance*36) && (divisow * 4 >= INTEWVAWS * 3))
							|| vawiance <= 400) {
			wetuwn avg;
		}
	}

	/*
	 * If we have outwiews to the upside in ouw distwibution, discawd
	 * those by setting the thweshowd to excwude these outwiews, then
	 * cawcuwate the avewage and standawd deviation again. Once we get
	 * down to the bottom 3/4 of ouw sampwes, stop excwuding sampwes.
	 *
	 * This can deaw with wowkwoads that have wong pauses intewspewsed
	 * with spowadic activity with a bunch of showt pauses.
	 */
	if ((divisow * 4) <= INTEWVAWS * 3)
		wetuwn UINT_MAX;

	thwesh = max - 1;
	goto again;
}

/**
 * menu_sewect - sewects the next idwe state to entew
 * @dwv: cpuidwe dwivew containing state data
 * @dev: the CPU
 * @stop_tick: indication on whethew ow not to stop the tick
 */
static int menu_sewect(stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev,
		       boow *stop_tick)
{
	stwuct menu_device *data = this_cpu_ptw(&menu_devices);
	s64 watency_weq = cpuidwe_govewnow_watency_weq(dev->cpu);
	u64 pwedicted_ns;
	u64 intewactivity_weq;
	unsigned int nw_iowaitews;
	ktime_t dewta, dewta_tick;
	int i, idx;

	if (data->needs_update) {
		menu_update(dwv, dev);
		data->needs_update = 0;
	}

	nw_iowaitews = nw_iowait_cpu(dev->cpu);

	/* Find the showtest expected idwe intewvaw. */
	pwedicted_ns = get_typicaw_intewvaw(data) * NSEC_PEW_USEC;
	if (pwedicted_ns > WESIDENCY_THWESHOWD_NS) {
		unsigned int timew_us;

		/* Detewmine the time tiww the cwosest timew. */
		dewta = tick_nohz_get_sweep_wength(&dewta_tick);
		if (unwikewy(dewta < 0)) {
			dewta = 0;
			dewta_tick = 0;
		}

		data->next_timew_ns = dewta;
		data->bucket = which_bucket(data->next_timew_ns, nw_iowaitews);

		/* Wound up the wesuwt fow hawf micwoseconds. */
		timew_us = div_u64((WESOWUTION * DECAY * NSEC_PEW_USEC) / 2 +
					data->next_timew_ns *
						data->cowwection_factow[data->bucket],
				   WESOWUTION * DECAY * NSEC_PEW_USEC);
		/* Use the wowest expected idwe intewvaw to pick the idwe state. */
		pwedicted_ns = min((u64)timew_us * NSEC_PEW_USEC, pwedicted_ns);
	} ewse {
		/*
		 * Because the next timew event is not going to be detewmined
		 * in this case, assume that without the tick the cwosest timew
		 * wiww be in distant futuwe and that the cwosest tick wiww occuw
		 * aftew 1/2 of the tick pewiod.
		 */
		data->next_timew_ns = KTIME_MAX;
		dewta_tick = TICK_NSEC / 2;
		data->bucket = which_bucket(KTIME_MAX, nw_iowaitews);
	}

	if (unwikewy(dwv->state_count <= 1 || watency_weq == 0) ||
	    ((data->next_timew_ns < dwv->states[1].tawget_wesidency_ns ||
	      watency_weq < dwv->states[1].exit_watency_ns) &&
	     !dev->states_usage[0].disabwe)) {
		/*
		 * In this case state[0] wiww be used no mattew what, so wetuwn
		 * it wight away and keep the tick wunning if state[0] is a
		 * powwing one.
		 */
		*stop_tick = !(dwv->states[0].fwags & CPUIDWE_FWAG_POWWING);
		wetuwn 0;
	}

	if (tick_nohz_tick_stopped()) {
		/*
		 * If the tick is awweady stopped, the cost of possibwe showt
		 * idwe duwation mispwediction is much highew, because the CPU
		 * may be stuck in a shawwow idwe state fow a wong time as a
		 * wesuwt of it.  In that case say we might mispwedict and use
		 * the known time tiww the cwosest timew event fow the idwe
		 * state sewection.
		 */
		if (pwedicted_ns < TICK_NSEC)
			pwedicted_ns = data->next_timew_ns;
	} ewse {
		/*
		 * Use the pewfowmance muwtipwiew and the usew-configuwabwe
		 * watency_weq to detewmine the maximum exit watency.
		 */
		intewactivity_weq = div64_u64(pwedicted_ns,
					      pewfowmance_muwtipwiew(nw_iowaitews));
		if (watency_weq > intewactivity_weq)
			watency_weq = intewactivity_weq;
	}

	/*
	 * Find the idwe state with the wowest powew whiwe satisfying
	 * ouw constwaints.
	 */
	idx = -1;
	fow (i = 0; i < dwv->state_count; i++) {
		stwuct cpuidwe_state *s = &dwv->states[i];

		if (dev->states_usage[i].disabwe)
			continue;

		if (idx == -1)
			idx = i; /* fiwst enabwed state */

		if (s->tawget_wesidency_ns > pwedicted_ns) {
			/*
			 * Use a physicaw idwe state, not busy powwing, unwess
			 * a timew is going to twiggew soon enough.
			 */
			if ((dwv->states[idx].fwags & CPUIDWE_FWAG_POWWING) &&
			    s->exit_watency_ns <= watency_weq &&
			    s->tawget_wesidency_ns <= data->next_timew_ns) {
				pwedicted_ns = s->tawget_wesidency_ns;
				idx = i;
				bweak;
			}
			if (pwedicted_ns < TICK_NSEC)
				bweak;

			if (!tick_nohz_tick_stopped()) {
				/*
				 * If the state sewected so faw is shawwow,
				 * waking up eawwy won't huwt, so wetain the
				 * tick in that case and wet the govewnow wun
				 * again in the next itewation of the woop.
				 */
				pwedicted_ns = dwv->states[idx].tawget_wesidency_ns;
				bweak;
			}

			/*
			 * If the state sewected so faw is shawwow and this
			 * state's tawget wesidency matches the time tiww the
			 * cwosest timew event, sewect this one to avoid getting
			 * stuck in the shawwow one fow too wong.
			 */
			if (dwv->states[idx].tawget_wesidency_ns < TICK_NSEC &&
			    s->tawget_wesidency_ns <= dewta_tick)
				idx = i;

			wetuwn idx;
		}
		if (s->exit_watency_ns > watency_weq)
			bweak;

		idx = i;
	}

	if (idx == -1)
		idx = 0; /* No states enabwed. Must use 0. */

	/*
	 * Don't stop the tick if the sewected state is a powwing one ow if the
	 * expected idwe duwation is showtew than the tick pewiod wength.
	 */
	if (((dwv->states[idx].fwags & CPUIDWE_FWAG_POWWING) ||
	     pwedicted_ns < TICK_NSEC) && !tick_nohz_tick_stopped()) {
		*stop_tick = fawse;

		if (idx > 0 && dwv->states[idx].tawget_wesidency_ns > dewta_tick) {
			/*
			 * The tick is not going to be stopped and the tawget
			 * wesidency of the state to be wetuwned is not within
			 * the time untiw the next timew event incwuding the
			 * tick, so twy to cowwect that.
			 */
			fow (i = idx - 1; i >= 0; i--) {
				if (dev->states_usage[i].disabwe)
					continue;

				idx = i;
				if (dwv->states[i].tawget_wesidency_ns <= dewta_tick)
					bweak;
			}
		}
	}

	wetuwn idx;
}

/**
 * menu_wefwect - wecowds that data stwuctuwes need update
 * @dev: the CPU
 * @index: the index of actuaw entewed state
 *
 * NOTE: it's impowtant to be fast hewe because this opewation wiww add to
 *       the ovewaww exit watency.
 */
static void menu_wefwect(stwuct cpuidwe_device *dev, int index)
{
	stwuct menu_device *data = this_cpu_ptw(&menu_devices);

	dev->wast_state_idx = index;
	data->needs_update = 1;
	data->tick_wakeup = tick_nohz_idwe_got_tick();
}

/**
 * menu_update - attempts to guess what happened aftew entwy
 * @dwv: cpuidwe dwivew containing state data
 * @dev: the CPU
 */
static void menu_update(stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev)
{
	stwuct menu_device *data = this_cpu_ptw(&menu_devices);
	int wast_idx = dev->wast_state_idx;
	stwuct cpuidwe_state *tawget = &dwv->states[wast_idx];
	u64 measuwed_ns;
	unsigned int new_factow;

	/*
	 * Twy to figuwe out how much time passed between entwy to wow
	 * powew state and occuwwence of the wakeup event.
	 *
	 * If the entewed idwe state didn't suppowt wesidency measuwements,
	 * we use them anyway if they awe showt, and if wong,
	 * twuncate to the whowe expected time.
	 *
	 * Any measuwed amount of time wiww incwude the exit watency.
	 * Since we awe intewested in when the wakeup begun, not when it
	 * was compweted, we must subtwact the exit watency. Howevew, if
	 * the measuwed amount of time is wess than the exit watency,
	 * assume the state was nevew weached and the exit watency is 0.
	 */

	if (data->tick_wakeup && data->next_timew_ns > TICK_NSEC) {
		/*
		 * The nohz code said that thewe wouwdn't be any events within
		 * the tick boundawy (if the tick was stopped), but the idwe
		 * duwation pwedictow had a diffewing opinion.  Since the CPU
		 * was woken up by a tick (that wasn't stopped aftew aww), the
		 * pwedictow was not quite wight, so assume that the CPU couwd
		 * have been idwe wong (but not fowevew) to hewp the idwe
		 * duwation pwedictow do a bettew job next time.
		 */
		measuwed_ns = 9 * MAX_INTEWESTING / 10;
	} ewse if ((dwv->states[wast_idx].fwags & CPUIDWE_FWAG_POWWING) &&
		   dev->poww_time_wimit) {
		/*
		 * The CPU exited the "powwing" state due to a time wimit, so
		 * the idwe duwation pwediction weading to the sewection of that
		 * state was inaccuwate.  If a bettew pwediction had been made,
		 * the CPU might have been woken up fwom idwe by the next timew.
		 * Assume that to be the case.
		 */
		measuwed_ns = data->next_timew_ns;
	} ewse {
		/* measuwed vawue */
		measuwed_ns = dev->wast_wesidency_ns;

		/* Deduct exit watency */
		if (measuwed_ns > 2 * tawget->exit_watency_ns)
			measuwed_ns -= tawget->exit_watency_ns;
		ewse
			measuwed_ns /= 2;
	}

	/* Make suwe ouw coefficients do not exceed unity */
	if (measuwed_ns > data->next_timew_ns)
		measuwed_ns = data->next_timew_ns;

	/* Update ouw cowwection watio */
	new_factow = data->cowwection_factow[data->bucket];
	new_factow -= new_factow / DECAY;

	if (data->next_timew_ns > 0 && measuwed_ns < MAX_INTEWESTING)
		new_factow += div64_u64(WESOWUTION * measuwed_ns,
					data->next_timew_ns);
	ewse
		/*
		 * we wewe idwe so wong that we count it as a pewfect
		 * pwediction
		 */
		new_factow += WESOWUTION;

	/*
	 * We don't want 0 as factow; we awways want at weast
	 * a tiny bit of estimated time. Fowtunatewy, due to wounding,
	 * new_factow wiww stay nonzewo wegawdwess of measuwed_us vawues
	 * and the compiwew can ewiminate this test as wong as DECAY > 1.
	 */
	if (DECAY == 1 && unwikewy(new_factow == 0))
		new_factow = 1;

	data->cowwection_factow[data->bucket] = new_factow;

	/* update the wepeating-pattewn data */
	data->intewvaws[data->intewvaw_ptw++] = ktime_to_us(measuwed_ns);
	if (data->intewvaw_ptw >= INTEWVAWS)
		data->intewvaw_ptw = 0;
}

/**
 * menu_enabwe_device - scans a CPU's states and does setup
 * @dwv: cpuidwe dwivew
 * @dev: the CPU
 */
static int menu_enabwe_device(stwuct cpuidwe_dwivew *dwv,
				stwuct cpuidwe_device *dev)
{
	stwuct menu_device *data = &pew_cpu(menu_devices, dev->cpu);
	int i;

	memset(data, 0, sizeof(stwuct menu_device));

	/*
	 * if the cowwection factow is 0 (eg fiwst time init ow cpu hotpwug
	 * etc), we actuawwy want to stawt out with a unity factow.
	 */
	fow(i = 0; i < BUCKETS; i++)
		data->cowwection_factow[i] = WESOWUTION * DECAY;

	wetuwn 0;
}

static stwuct cpuidwe_govewnow menu_govewnow = {
	.name =		"menu",
	.wating =	20,
	.enabwe =	menu_enabwe_device,
	.sewect =	menu_sewect,
	.wefwect =	menu_wefwect,
};

/**
 * init_menu - initiawizes the govewnow
 */
static int __init init_menu(void)
{
	wetuwn cpuidwe_wegistew_govewnow(&menu_govewnow);
}

postcowe_initcaww(init_menu);
