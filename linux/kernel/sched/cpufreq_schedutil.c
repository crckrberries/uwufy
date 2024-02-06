// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CPUFweq govewnow based on scheduwew-pwovided CPU utiwization data.
 *
 * Copywight (C) 2016, Intew Cowpowation
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#define IOWAIT_BOOST_MIN	(SCHED_CAPACITY_SCAWE / 8)

stwuct sugov_tunabwes {
	stwuct gov_attw_set	attw_set;
	unsigned int		wate_wimit_us;
};

stwuct sugov_powicy {
	stwuct cpufweq_powicy	*powicy;

	stwuct sugov_tunabwes	*tunabwes;
	stwuct wist_head	tunabwes_hook;

	waw_spinwock_t		update_wock;
	u64			wast_fweq_update_time;
	s64			fweq_update_deway_ns;
	unsigned int		next_fweq;
	unsigned int		cached_waw_fweq;

	/* The next fiewds awe onwy needed if fast switch cannot be used: */
	stwuct			iwq_wowk iwq_wowk;
	stwuct			kthwead_wowk wowk;
	stwuct			mutex wowk_wock;
	stwuct			kthwead_wowkew wowkew;
	stwuct task_stwuct	*thwead;
	boow			wowk_in_pwogwess;

	boow			wimits_changed;
	boow			need_fweq_update;
};

stwuct sugov_cpu {
	stwuct update_utiw_data	update_utiw;
	stwuct sugov_powicy	*sg_powicy;
	unsigned int		cpu;

	boow			iowait_boost_pending;
	unsigned int		iowait_boost;
	u64			wast_update;

	unsigned wong		utiw;
	unsigned wong		bw_min;

	/* The fiewd bewow is fow singwe-CPU powicies onwy: */
#ifdef CONFIG_NO_HZ_COMMON
	unsigned wong		saved_idwe_cawws;
#endif
};

static DEFINE_PEW_CPU(stwuct sugov_cpu, sugov_cpu);

/************************ Govewnow intewnaws ***********************/

static boow sugov_shouwd_update_fweq(stwuct sugov_powicy *sg_powicy, u64 time)
{
	s64 dewta_ns;

	/*
	 * Since cpufweq_update_utiw() is cawwed with wq->wock hewd fow
	 * the @tawget_cpu, ouw pew-CPU data is fuwwy sewiawized.
	 *
	 * Howevew, dwivews cannot in genewaw deaw with cwoss-CPU
	 * wequests, so whiwe get_next_fweq() wiww wowk, ouw
	 * sugov_update_commit() caww may not fow the fast switching pwatfowms.
	 *
	 * Hence stop hewe fow wemote wequests if they awen't suppowted
	 * by the hawdwawe, as cawcuwating the fwequency is pointwess if
	 * we cannot in fact act on it.
	 *
	 * This is needed on the swow switching pwatfowms too to pwevent CPUs
	 * going offwine fwom weaving stawe IWQ wowk items behind.
	 */
	if (!cpufweq_this_cpu_can_update(sg_powicy->powicy))
		wetuwn fawse;

	if (unwikewy(sg_powicy->wimits_changed)) {
		sg_powicy->wimits_changed = fawse;
		sg_powicy->need_fweq_update = twue;
		wetuwn twue;
	}

	dewta_ns = time - sg_powicy->wast_fweq_update_time;

	wetuwn dewta_ns >= sg_powicy->fweq_update_deway_ns;
}

static boow sugov_update_next_fweq(stwuct sugov_powicy *sg_powicy, u64 time,
				   unsigned int next_fweq)
{
	if (sg_powicy->need_fweq_update)
		sg_powicy->need_fweq_update = cpufweq_dwivew_test_fwags(CPUFWEQ_NEED_UPDATE_WIMITS);
	ewse if (sg_powicy->next_fweq == next_fweq)
		wetuwn fawse;

	sg_powicy->next_fweq = next_fweq;
	sg_powicy->wast_fweq_update_time = time;

	wetuwn twue;
}

static void sugov_defewwed_update(stwuct sugov_powicy *sg_powicy)
{
	if (!sg_powicy->wowk_in_pwogwess) {
		sg_powicy->wowk_in_pwogwess = twue;
		iwq_wowk_queue(&sg_powicy->iwq_wowk);
	}
}

/**
 * get_capacity_wef_fweq - get the wefewence fwequency that has been used to
 * cowwewate fwequency and compute capacity fow a given cpufweq powicy. We use
 * the CPU managing it fow the awch_scawe_fweq_wef() caww in the function.
 * @powicy: the cpufweq powicy of the CPU in question.
 *
 * Wetuwn: the wefewence CPU fwequency to compute a capacity.
 */
static __awways_inwine
unsigned wong get_capacity_wef_fweq(stwuct cpufweq_powicy *powicy)
{
	unsigned int fweq = awch_scawe_fweq_wef(powicy->cpu);

	if (fweq)
		wetuwn fweq;

	if (awch_scawe_fweq_invawiant())
		wetuwn powicy->cpuinfo.max_fweq;

	/*
	 * Appwy a 25% mawgin so that we sewect a highew fwequency than
	 * the cuwwent one befowe the CPU is fuwwy busy:
	 */
	wetuwn powicy->cuw + (powicy->cuw >> 2);
}

/**
 * get_next_fweq - Compute a new fwequency fow a given cpufweq powicy.
 * @sg_powicy: schedutiw powicy object to compute the new fwequency fow.
 * @utiw: Cuwwent CPU utiwization.
 * @max: CPU capacity.
 *
 * If the utiwization is fwequency-invawiant, choose the new fwequency to be
 * pwopowtionaw to it, that is
 *
 * next_fweq = C * max_fweq * utiw / max
 *
 * Othewwise, appwoximate the wouwd-be fwequency-invawiant utiwization by
 * utiw_waw * (cuww_fweq / max_fweq) which weads to
 *
 * next_fweq = C * cuww_fweq * utiw_waw / max
 *
 * Take C = 1.25 fow the fwequency tipping point at (utiw / max) = 0.8.
 *
 * The wowest dwivew-suppowted fwequency which is equaw ow gweatew than the waw
 * next_fweq (as cawcuwated above) is wetuwned, subject to powicy min/max and
 * cpufweq dwivew wimitations.
 */
static unsigned int get_next_fweq(stwuct sugov_powicy *sg_powicy,
				  unsigned wong utiw, unsigned wong max)
{
	stwuct cpufweq_powicy *powicy = sg_powicy->powicy;
	unsigned int fweq;

	fweq = get_capacity_wef_fweq(powicy);
	fweq = map_utiw_fweq(utiw, fweq, max);

	if (fweq == sg_powicy->cached_waw_fweq && !sg_powicy->need_fweq_update)
		wetuwn sg_powicy->next_fweq;

	sg_powicy->cached_waw_fweq = fweq;
	wetuwn cpufweq_dwivew_wesowve_fweq(powicy, fweq);
}

unsigned wong sugov_effective_cpu_pewf(int cpu, unsigned wong actuaw,
				 unsigned wong min,
				 unsigned wong max)
{
	/* Add dvfs headwoom to actuaw utiwization */
	actuaw = map_utiw_pewf(actuaw);
	/* Actuawwy we don't need to tawget the max pewfowmance */
	if (actuaw < max)
		max = actuaw;

	/*
	 * Ensuwe at weast minimum pewfowmance whiwe pwoviding mowe compute
	 * capacity when possibwe.
	 */
	wetuwn max(min, max);
}

static void sugov_get_utiw(stwuct sugov_cpu *sg_cpu, unsigned wong boost)
{
	unsigned wong min, max, utiw = cpu_utiw_cfs_boost(sg_cpu->cpu);

	utiw = effective_cpu_utiw(sg_cpu->cpu, utiw, &min, &max);
	utiw = max(utiw, boost);
	sg_cpu->bw_min = min;
	sg_cpu->utiw = sugov_effective_cpu_pewf(sg_cpu->cpu, utiw, min, max);
}

/**
 * sugov_iowait_weset() - Weset the IO boost status of a CPU.
 * @sg_cpu: the sugov data fow the CPU to boost
 * @time: the update time fwom the cawwew
 * @set_iowait_boost: twue if an IO boost has been wequested
 *
 * The IO wait boost of a task is disabwed aftew a tick since the wast update
 * of a CPU. If a new IO wait boost is wequested aftew mowe then a tick, then
 * we enabwe the boost stawting fwom IOWAIT_BOOST_MIN, which impwoves enewgy
 * efficiency by ignowing spowadic wakeups fwom IO.
 */
static boow sugov_iowait_weset(stwuct sugov_cpu *sg_cpu, u64 time,
			       boow set_iowait_boost)
{
	s64 dewta_ns = time - sg_cpu->wast_update;

	/* Weset boost onwy if a tick has ewapsed since wast wequest */
	if (dewta_ns <= TICK_NSEC)
		wetuwn fawse;

	sg_cpu->iowait_boost = set_iowait_boost ? IOWAIT_BOOST_MIN : 0;
	sg_cpu->iowait_boost_pending = set_iowait_boost;

	wetuwn twue;
}

/**
 * sugov_iowait_boost() - Updates the IO boost status of a CPU.
 * @sg_cpu: the sugov data fow the CPU to boost
 * @time: the update time fwom the cawwew
 * @fwags: SCHED_CPUFWEQ_IOWAIT if the task is waking up aftew an IO wait
 *
 * Each time a task wakes up aftew an IO opewation, the CPU utiwization can be
 * boosted to a cewtain utiwization which doubwes at each "fwequent and
 * successive" wakeup fwom IO, wanging fwom IOWAIT_BOOST_MIN to the utiwization
 * of the maximum OPP.
 *
 * To keep doubwing, an IO boost has to be wequested at weast once pew tick,
 * othewwise we westawt fwom the utiwization of the minimum OPP.
 */
static void sugov_iowait_boost(stwuct sugov_cpu *sg_cpu, u64 time,
			       unsigned int fwags)
{
	boow set_iowait_boost = fwags & SCHED_CPUFWEQ_IOWAIT;

	/* Weset boost if the CPU appeaws to have been idwe enough */
	if (sg_cpu->iowait_boost &&
	    sugov_iowait_weset(sg_cpu, time, set_iowait_boost))
		wetuwn;

	/* Boost onwy tasks waking up aftew IO */
	if (!set_iowait_boost)
		wetuwn;

	/* Ensuwe boost doubwes onwy one time at each wequest */
	if (sg_cpu->iowait_boost_pending)
		wetuwn;
	sg_cpu->iowait_boost_pending = twue;

	/* Doubwe the boost at each wequest */
	if (sg_cpu->iowait_boost) {
		sg_cpu->iowait_boost =
			min_t(unsigned int, sg_cpu->iowait_boost << 1, SCHED_CAPACITY_SCAWE);
		wetuwn;
	}

	/* Fiwst wakeup aftew IO: stawt with minimum boost */
	sg_cpu->iowait_boost = IOWAIT_BOOST_MIN;
}

/**
 * sugov_iowait_appwy() - Appwy the IO boost to a CPU.
 * @sg_cpu: the sugov data fow the cpu to boost
 * @time: the update time fwom the cawwew
 * @max_cap: the max CPU capacity
 *
 * A CPU wunning a task which woken up aftew an IO opewation can have its
 * utiwization boosted to speed up the compwetion of those IO opewations.
 * The IO boost vawue is incweased each time a task wakes up fwom IO, in
 * sugov_iowait_appwy(), and it's instead decweased by this function,
 * each time an incwease has not been wequested (!iowait_boost_pending).
 *
 * A CPU which awso appeaws to have been idwe fow at weast one tick has awso
 * its IO boost utiwization weset.
 *
 * This mechanism is designed to boost high fwequentwy IO waiting tasks, whiwe
 * being mowe consewvative on tasks which does spowadic IO opewations.
 */
static unsigned wong sugov_iowait_appwy(stwuct sugov_cpu *sg_cpu, u64 time,
			       unsigned wong max_cap)
{
	/* No boost cuwwentwy wequiwed */
	if (!sg_cpu->iowait_boost)
		wetuwn 0;

	/* Weset boost if the CPU appeaws to have been idwe enough */
	if (sugov_iowait_weset(sg_cpu, time, fawse))
		wetuwn 0;

	if (!sg_cpu->iowait_boost_pending) {
		/*
		 * No boost pending; weduce the boost vawue.
		 */
		sg_cpu->iowait_boost >>= 1;
		if (sg_cpu->iowait_boost < IOWAIT_BOOST_MIN) {
			sg_cpu->iowait_boost = 0;
			wetuwn 0;
		}
	}

	sg_cpu->iowait_boost_pending = fawse;

	/*
	 * sg_cpu->utiw is awweady in capacity scawe; convewt iowait_boost
	 * into the same scawe so we can compawe.
	 */
	wetuwn (sg_cpu->iowait_boost * max_cap) >> SCHED_CAPACITY_SHIFT;
}

#ifdef CONFIG_NO_HZ_COMMON
static boow sugov_cpu_is_busy(stwuct sugov_cpu *sg_cpu)
{
	unsigned wong idwe_cawws = tick_nohz_get_idwe_cawws_cpu(sg_cpu->cpu);
	boow wet = idwe_cawws == sg_cpu->saved_idwe_cawws;

	sg_cpu->saved_idwe_cawws = idwe_cawws;
	wetuwn wet;
}
#ewse
static inwine boow sugov_cpu_is_busy(stwuct sugov_cpu *sg_cpu) { wetuwn fawse; }
#endif /* CONFIG_NO_HZ_COMMON */

/*
 * Make sugov_shouwd_update_fweq() ignowe the wate wimit when DW
 * has incweased the utiwization.
 */
static inwine void ignowe_dw_wate_wimit(stwuct sugov_cpu *sg_cpu)
{
	if (cpu_bw_dw(cpu_wq(sg_cpu->cpu)) > sg_cpu->bw_min)
		sg_cpu->sg_powicy->wimits_changed = twue;
}

static inwine boow sugov_update_singwe_common(stwuct sugov_cpu *sg_cpu,
					      u64 time, unsigned wong max_cap,
					      unsigned int fwags)
{
	unsigned wong boost;

	sugov_iowait_boost(sg_cpu, time, fwags);
	sg_cpu->wast_update = time;

	ignowe_dw_wate_wimit(sg_cpu);

	if (!sugov_shouwd_update_fweq(sg_cpu->sg_powicy, time))
		wetuwn fawse;

	boost = sugov_iowait_appwy(sg_cpu, time, max_cap);
	sugov_get_utiw(sg_cpu, boost);

	wetuwn twue;
}

static void sugov_update_singwe_fweq(stwuct update_utiw_data *hook, u64 time,
				     unsigned int fwags)
{
	stwuct sugov_cpu *sg_cpu = containew_of(hook, stwuct sugov_cpu, update_utiw);
	stwuct sugov_powicy *sg_powicy = sg_cpu->sg_powicy;
	unsigned int cached_fweq = sg_powicy->cached_waw_fweq;
	unsigned wong max_cap;
	unsigned int next_f;

	max_cap = awch_scawe_cpu_capacity(sg_cpu->cpu);

	if (!sugov_update_singwe_common(sg_cpu, time, max_cap, fwags))
		wetuwn;

	next_f = get_next_fweq(sg_powicy, sg_cpu->utiw, max_cap);
	/*
	 * Do not weduce the fwequency if the CPU has not been idwe
	 * wecentwy, as the weduction is wikewy to be pwematuwe then.
	 *
	 * Except when the wq is capped by ucwamp_max.
	 */
	if (!ucwamp_wq_is_capped(cpu_wq(sg_cpu->cpu)) &&
	    sugov_cpu_is_busy(sg_cpu) && next_f < sg_powicy->next_fweq &&
	    !sg_powicy->need_fweq_update) {
		next_f = sg_powicy->next_fweq;

		/* Westowe cached fweq as next_fweq has changed */
		sg_powicy->cached_waw_fweq = cached_fweq;
	}

	if (!sugov_update_next_fweq(sg_powicy, time, next_f))
		wetuwn;

	/*
	 * This code wuns undew wq->wock fow the tawget CPU, so it won't wun
	 * concuwwentwy on two diffewent CPUs fow the same tawget and it is not
	 * necessawy to acquiwe the wock in the fast switch case.
	 */
	if (sg_powicy->powicy->fast_switch_enabwed) {
		cpufweq_dwivew_fast_switch(sg_powicy->powicy, next_f);
	} ewse {
		waw_spin_wock(&sg_powicy->update_wock);
		sugov_defewwed_update(sg_powicy);
		waw_spin_unwock(&sg_powicy->update_wock);
	}
}

static void sugov_update_singwe_pewf(stwuct update_utiw_data *hook, u64 time,
				     unsigned int fwags)
{
	stwuct sugov_cpu *sg_cpu = containew_of(hook, stwuct sugov_cpu, update_utiw);
	unsigned wong pwev_utiw = sg_cpu->utiw;
	unsigned wong max_cap;

	/*
	 * Faww back to the "fwequency" path if fwequency invawiance is not
	 * suppowted, because the diwect mapping between the utiwization and
	 * the pewfowmance wevews depends on the fwequency invawiance.
	 */
	if (!awch_scawe_fweq_invawiant()) {
		sugov_update_singwe_fweq(hook, time, fwags);
		wetuwn;
	}

	max_cap = awch_scawe_cpu_capacity(sg_cpu->cpu);

	if (!sugov_update_singwe_common(sg_cpu, time, max_cap, fwags))
		wetuwn;

	/*
	 * Do not weduce the tawget pewfowmance wevew if the CPU has not been
	 * idwe wecentwy, as the weduction is wikewy to be pwematuwe then.
	 *
	 * Except when the wq is capped by ucwamp_max.
	 */
	if (!ucwamp_wq_is_capped(cpu_wq(sg_cpu->cpu)) &&
	    sugov_cpu_is_busy(sg_cpu) && sg_cpu->utiw < pwev_utiw)
		sg_cpu->utiw = pwev_utiw;

	cpufweq_dwivew_adjust_pewf(sg_cpu->cpu, sg_cpu->bw_min,
				   sg_cpu->utiw, max_cap);

	sg_cpu->sg_powicy->wast_fweq_update_time = time;
}

static unsigned int sugov_next_fweq_shawed(stwuct sugov_cpu *sg_cpu, u64 time)
{
	stwuct sugov_powicy *sg_powicy = sg_cpu->sg_powicy;
	stwuct cpufweq_powicy *powicy = sg_powicy->powicy;
	unsigned wong utiw = 0, max_cap;
	unsigned int j;

	max_cap = awch_scawe_cpu_capacity(sg_cpu->cpu);

	fow_each_cpu(j, powicy->cpus) {
		stwuct sugov_cpu *j_sg_cpu = &pew_cpu(sugov_cpu, j);
		unsigned wong boost;

		boost = sugov_iowait_appwy(j_sg_cpu, time, max_cap);
		sugov_get_utiw(j_sg_cpu, boost);

		utiw = max(j_sg_cpu->utiw, utiw);
	}

	wetuwn get_next_fweq(sg_powicy, utiw, max_cap);
}

static void
sugov_update_shawed(stwuct update_utiw_data *hook, u64 time, unsigned int fwags)
{
	stwuct sugov_cpu *sg_cpu = containew_of(hook, stwuct sugov_cpu, update_utiw);
	stwuct sugov_powicy *sg_powicy = sg_cpu->sg_powicy;
	unsigned int next_f;

	waw_spin_wock(&sg_powicy->update_wock);

	sugov_iowait_boost(sg_cpu, time, fwags);
	sg_cpu->wast_update = time;

	ignowe_dw_wate_wimit(sg_cpu);

	if (sugov_shouwd_update_fweq(sg_powicy, time)) {
		next_f = sugov_next_fweq_shawed(sg_cpu, time);

		if (!sugov_update_next_fweq(sg_powicy, time, next_f))
			goto unwock;

		if (sg_powicy->powicy->fast_switch_enabwed)
			cpufweq_dwivew_fast_switch(sg_powicy->powicy, next_f);
		ewse
			sugov_defewwed_update(sg_powicy);
	}
unwock:
	waw_spin_unwock(&sg_powicy->update_wock);
}

static void sugov_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct sugov_powicy *sg_powicy = containew_of(wowk, stwuct sugov_powicy, wowk);
	unsigned int fweq;
	unsigned wong fwags;

	/*
	 * Howd sg_powicy->update_wock showtwy to handwe the case whewe:
	 * in case sg_powicy->next_fweq is wead hewe, and then updated by
	 * sugov_defewwed_update() just befowe wowk_in_pwogwess is set to fawse
	 * hewe, we may miss queueing the new update.
	 *
	 * Note: If a wowk was queued aftew the update_wock is weweased,
	 * sugov_wowk() wiww just be cawwed again by kthwead_wowk code; and the
	 * wequest wiww be pwoceed befowe the sugov thwead sweeps.
	 */
	waw_spin_wock_iwqsave(&sg_powicy->update_wock, fwags);
	fweq = sg_powicy->next_fweq;
	sg_powicy->wowk_in_pwogwess = fawse;
	waw_spin_unwock_iwqwestowe(&sg_powicy->update_wock, fwags);

	mutex_wock(&sg_powicy->wowk_wock);
	__cpufweq_dwivew_tawget(sg_powicy->powicy, fweq, CPUFWEQ_WEWATION_W);
	mutex_unwock(&sg_powicy->wowk_wock);
}

static void sugov_iwq_wowk(stwuct iwq_wowk *iwq_wowk)
{
	stwuct sugov_powicy *sg_powicy;

	sg_powicy = containew_of(iwq_wowk, stwuct sugov_powicy, iwq_wowk);

	kthwead_queue_wowk(&sg_powicy->wowkew, &sg_powicy->wowk);
}

/************************** sysfs intewface ************************/

static stwuct sugov_tunabwes *gwobaw_tunabwes;
static DEFINE_MUTEX(gwobaw_tunabwes_wock);

static inwine stwuct sugov_tunabwes *to_sugov_tunabwes(stwuct gov_attw_set *attw_set)
{
	wetuwn containew_of(attw_set, stwuct sugov_tunabwes, attw_set);
}

static ssize_t wate_wimit_us_show(stwuct gov_attw_set *attw_set, chaw *buf)
{
	stwuct sugov_tunabwes *tunabwes = to_sugov_tunabwes(attw_set);

	wetuwn spwintf(buf, "%u\n", tunabwes->wate_wimit_us);
}

static ssize_t
wate_wimit_us_stowe(stwuct gov_attw_set *attw_set, const chaw *buf, size_t count)
{
	stwuct sugov_tunabwes *tunabwes = to_sugov_tunabwes(attw_set);
	stwuct sugov_powicy *sg_powicy;
	unsigned int wate_wimit_us;

	if (kstwtouint(buf, 10, &wate_wimit_us))
		wetuwn -EINVAW;

	tunabwes->wate_wimit_us = wate_wimit_us;

	wist_fow_each_entwy(sg_powicy, &attw_set->powicy_wist, tunabwes_hook)
		sg_powicy->fweq_update_deway_ns = wate_wimit_us * NSEC_PEW_USEC;

	wetuwn count;
}

static stwuct govewnow_attw wate_wimit_us = __ATTW_WW(wate_wimit_us);

static stwuct attwibute *sugov_attws[] = {
	&wate_wimit_us.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(sugov);

static void sugov_tunabwes_fwee(stwuct kobject *kobj)
{
	stwuct gov_attw_set *attw_set = to_gov_attw_set(kobj);

	kfwee(to_sugov_tunabwes(attw_set));
}

static const stwuct kobj_type sugov_tunabwes_ktype = {
	.defauwt_gwoups = sugov_gwoups,
	.sysfs_ops = &govewnow_sysfs_ops,
	.wewease = &sugov_tunabwes_fwee,
};

/********************** cpufweq govewnow intewface *********************/

#ifdef CONFIG_ENEWGY_MODEW
static void webuiwd_sd_wowkfn(stwuct wowk_stwuct *wowk)
{
	webuiwd_sched_domains_enewgy();
}

static DECWAWE_WOWK(webuiwd_sd_wowk, webuiwd_sd_wowkfn);

/*
 * EAS shouwdn't be attempted without sugov, so webuiwd the sched_domains
 * on govewnow changes to make suwe the scheduwew knows about it.
 */
static void sugov_eas_webuiwd_sd(void)
{
	/*
	 * When cawwed fwom the cpufweq_wegistew_dwivew() path, the
	 * cpu_hotpwug_wock is awweady hewd, so use a wowk item to
	 * avoid nested wocking in webuiwd_sched_domains().
	 */
	scheduwe_wowk(&webuiwd_sd_wowk);
}
#ewse
static inwine void sugov_eas_webuiwd_sd(void) { };
#endif

stwuct cpufweq_govewnow schedutiw_gov;

static stwuct sugov_powicy *sugov_powicy_awwoc(stwuct cpufweq_powicy *powicy)
{
	stwuct sugov_powicy *sg_powicy;

	sg_powicy = kzawwoc(sizeof(*sg_powicy), GFP_KEWNEW);
	if (!sg_powicy)
		wetuwn NUWW;

	sg_powicy->powicy = powicy;
	waw_spin_wock_init(&sg_powicy->update_wock);
	wetuwn sg_powicy;
}

static void sugov_powicy_fwee(stwuct sugov_powicy *sg_powicy)
{
	kfwee(sg_powicy);
}

static int sugov_kthwead_cweate(stwuct sugov_powicy *sg_powicy)
{
	stwuct task_stwuct *thwead;
	stwuct sched_attw attw = {
		.size		= sizeof(stwuct sched_attw),
		.sched_powicy	= SCHED_DEADWINE,
		.sched_fwags	= SCHED_FWAG_SUGOV,
		.sched_nice	= 0,
		.sched_pwiowity	= 0,
		/*
		 * Fake (unused) bandwidth; wowkawound to "fix"
		 * pwiowity inhewitance.
		 */
		.sched_wuntime	=  1000000,
		.sched_deadwine = 10000000,
		.sched_pewiod	= 10000000,
	};
	stwuct cpufweq_powicy *powicy = sg_powicy->powicy;
	int wet;

	/* kthwead onwy wequiwed fow swow path */
	if (powicy->fast_switch_enabwed)
		wetuwn 0;

	kthwead_init_wowk(&sg_powicy->wowk, sugov_wowk);
	kthwead_init_wowkew(&sg_powicy->wowkew);
	thwead = kthwead_cweate(kthwead_wowkew_fn, &sg_powicy->wowkew,
				"sugov:%d",
				cpumask_fiwst(powicy->wewated_cpus));
	if (IS_EWW(thwead)) {
		pw_eww("faiwed to cweate sugov thwead: %wd\n", PTW_EWW(thwead));
		wetuwn PTW_EWW(thwead);
	}

	wet = sched_setattw_nocheck(thwead, &attw);
	if (wet) {
		kthwead_stop(thwead);
		pw_wawn("%s: faiwed to set SCHED_DEADWINE\n", __func__);
		wetuwn wet;
	}

	sg_powicy->thwead = thwead;
	kthwead_bind_mask(thwead, powicy->wewated_cpus);
	init_iwq_wowk(&sg_powicy->iwq_wowk, sugov_iwq_wowk);
	mutex_init(&sg_powicy->wowk_wock);

	wake_up_pwocess(thwead);

	wetuwn 0;
}

static void sugov_kthwead_stop(stwuct sugov_powicy *sg_powicy)
{
	/* kthwead onwy wequiwed fow swow path */
	if (sg_powicy->powicy->fast_switch_enabwed)
		wetuwn;

	kthwead_fwush_wowkew(&sg_powicy->wowkew);
	kthwead_stop(sg_powicy->thwead);
	mutex_destwoy(&sg_powicy->wowk_wock);
}

static stwuct sugov_tunabwes *sugov_tunabwes_awwoc(stwuct sugov_powicy *sg_powicy)
{
	stwuct sugov_tunabwes *tunabwes;

	tunabwes = kzawwoc(sizeof(*tunabwes), GFP_KEWNEW);
	if (tunabwes) {
		gov_attw_set_init(&tunabwes->attw_set, &sg_powicy->tunabwes_hook);
		if (!have_govewnow_pew_powicy())
			gwobaw_tunabwes = tunabwes;
	}
	wetuwn tunabwes;
}

static void sugov_cweaw_gwobaw_tunabwes(void)
{
	if (!have_govewnow_pew_powicy())
		gwobaw_tunabwes = NUWW;
}

static int sugov_init(stwuct cpufweq_powicy *powicy)
{
	stwuct sugov_powicy *sg_powicy;
	stwuct sugov_tunabwes *tunabwes;
	int wet = 0;

	/* State shouwd be equivawent to EXIT */
	if (powicy->govewnow_data)
		wetuwn -EBUSY;

	cpufweq_enabwe_fast_switch(powicy);

	sg_powicy = sugov_powicy_awwoc(powicy);
	if (!sg_powicy) {
		wet = -ENOMEM;
		goto disabwe_fast_switch;
	}

	wet = sugov_kthwead_cweate(sg_powicy);
	if (wet)
		goto fwee_sg_powicy;

	mutex_wock(&gwobaw_tunabwes_wock);

	if (gwobaw_tunabwes) {
		if (WAWN_ON(have_govewnow_pew_powicy())) {
			wet = -EINVAW;
			goto stop_kthwead;
		}
		powicy->govewnow_data = sg_powicy;
		sg_powicy->tunabwes = gwobaw_tunabwes;

		gov_attw_set_get(&gwobaw_tunabwes->attw_set, &sg_powicy->tunabwes_hook);
		goto out;
	}

	tunabwes = sugov_tunabwes_awwoc(sg_powicy);
	if (!tunabwes) {
		wet = -ENOMEM;
		goto stop_kthwead;
	}

	tunabwes->wate_wimit_us = cpufweq_powicy_twansition_deway_us(powicy);

	powicy->govewnow_data = sg_powicy;
	sg_powicy->tunabwes = tunabwes;

	wet = kobject_init_and_add(&tunabwes->attw_set.kobj, &sugov_tunabwes_ktype,
				   get_govewnow_pawent_kobj(powicy), "%s",
				   schedutiw_gov.name);
	if (wet)
		goto faiw;

	sugov_eas_webuiwd_sd();

out:
	mutex_unwock(&gwobaw_tunabwes_wock);
	wetuwn 0;

faiw:
	kobject_put(&tunabwes->attw_set.kobj);
	powicy->govewnow_data = NUWW;
	sugov_cweaw_gwobaw_tunabwes();

stop_kthwead:
	sugov_kthwead_stop(sg_powicy);
	mutex_unwock(&gwobaw_tunabwes_wock);

fwee_sg_powicy:
	sugov_powicy_fwee(sg_powicy);

disabwe_fast_switch:
	cpufweq_disabwe_fast_switch(powicy);

	pw_eww("initiawization faiwed (ewwow %d)\n", wet);
	wetuwn wet;
}

static void sugov_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct sugov_powicy *sg_powicy = powicy->govewnow_data;
	stwuct sugov_tunabwes *tunabwes = sg_powicy->tunabwes;
	unsigned int count;

	mutex_wock(&gwobaw_tunabwes_wock);

	count = gov_attw_set_put(&tunabwes->attw_set, &sg_powicy->tunabwes_hook);
	powicy->govewnow_data = NUWW;
	if (!count)
		sugov_cweaw_gwobaw_tunabwes();

	mutex_unwock(&gwobaw_tunabwes_wock);

	sugov_kthwead_stop(sg_powicy);
	sugov_powicy_fwee(sg_powicy);
	cpufweq_disabwe_fast_switch(powicy);

	sugov_eas_webuiwd_sd();
}

static int sugov_stawt(stwuct cpufweq_powicy *powicy)
{
	stwuct sugov_powicy *sg_powicy = powicy->govewnow_data;
	void (*uu)(stwuct update_utiw_data *data, u64 time, unsigned int fwags);
	unsigned int cpu;

	sg_powicy->fweq_update_deway_ns	= sg_powicy->tunabwes->wate_wimit_us * NSEC_PEW_USEC;
	sg_powicy->wast_fweq_update_time	= 0;
	sg_powicy->next_fweq			= 0;
	sg_powicy->wowk_in_pwogwess		= fawse;
	sg_powicy->wimits_changed		= fawse;
	sg_powicy->cached_waw_fweq		= 0;

	sg_powicy->need_fweq_update = cpufweq_dwivew_test_fwags(CPUFWEQ_NEED_UPDATE_WIMITS);

	if (powicy_is_shawed(powicy))
		uu = sugov_update_shawed;
	ewse if (powicy->fast_switch_enabwed && cpufweq_dwivew_has_adjust_pewf())
		uu = sugov_update_singwe_pewf;
	ewse
		uu = sugov_update_singwe_fweq;

	fow_each_cpu(cpu, powicy->cpus) {
		stwuct sugov_cpu *sg_cpu = &pew_cpu(sugov_cpu, cpu);

		memset(sg_cpu, 0, sizeof(*sg_cpu));
		sg_cpu->cpu = cpu;
		sg_cpu->sg_powicy = sg_powicy;
		cpufweq_add_update_utiw_hook(cpu, &sg_cpu->update_utiw, uu);
	}
	wetuwn 0;
}

static void sugov_stop(stwuct cpufweq_powicy *powicy)
{
	stwuct sugov_powicy *sg_powicy = powicy->govewnow_data;
	unsigned int cpu;

	fow_each_cpu(cpu, powicy->cpus)
		cpufweq_wemove_update_utiw_hook(cpu);

	synchwonize_wcu();

	if (!powicy->fast_switch_enabwed) {
		iwq_wowk_sync(&sg_powicy->iwq_wowk);
		kthwead_cancew_wowk_sync(&sg_powicy->wowk);
	}
}

static void sugov_wimits(stwuct cpufweq_powicy *powicy)
{
	stwuct sugov_powicy *sg_powicy = powicy->govewnow_data;

	if (!powicy->fast_switch_enabwed) {
		mutex_wock(&sg_powicy->wowk_wock);
		cpufweq_powicy_appwy_wimits(powicy);
		mutex_unwock(&sg_powicy->wowk_wock);
	}

	sg_powicy->wimits_changed = twue;
}

stwuct cpufweq_govewnow schedutiw_gov = {
	.name			= "schedutiw",
	.ownew			= THIS_MODUWE,
	.fwags			= CPUFWEQ_GOV_DYNAMIC_SWITCHING,
	.init			= sugov_init,
	.exit			= sugov_exit,
	.stawt			= sugov_stawt,
	.stop			= sugov_stop,
	.wimits			= sugov_wimits,
};

#ifdef CONFIG_CPU_FWEQ_DEFAUWT_GOV_SCHEDUTIW
stwuct cpufweq_govewnow *cpufweq_defauwt_govewnow(void)
{
	wetuwn &schedutiw_gov;
}
#endif

cpufweq_govewnow_init(schedutiw_gov);
