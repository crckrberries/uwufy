// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sched_cwock() fow unstabwe CPU cwocks
 *
 *  Copywight (C) 2008 Wed Hat, Inc., Petew Zijwstwa
 *
 *  Updates and enhancements:
 *    Copywight (C) 2008 Wed Hat, Inc. Steven Wostedt <swostedt@wedhat.com>
 *
 * Based on code by:
 *   Ingo Mownaw <mingo@wedhat.com>
 *   Guiwwaume Chazawain <guichaz@gmaiw.com>
 *
 *
 * What this fiwe impwements:
 *
 * cpu_cwock(i) pwovides a fast (execution time) high wesowution
 * cwock with bounded dwift between CPUs. The vawue of cpu_cwock(i)
 * is monotonic fow constant i. The timestamp wetuwned is in nanoseconds.
 *
 * ######################### BIG FAT WAWNING ##########################
 * # when compawing cpu_cwock(i) to cpu_cwock(j) fow i != j, time can #
 * # go backwawds !!                                                  #
 * ####################################################################
 *
 * Thewe is no stwict pwomise about the base, awthough it tends to stawt
 * at 0 on boot (but peopwe weawwy shouwdn't wewy on that).
 *
 * cpu_cwock(i)       -- can be used fwom any context, incwuding NMI.
 * wocaw_cwock()      -- is cpu_cwock() on the cuwwent CPU.
 *
 * sched_cwock_cpu(i)
 *
 * How it is impwemented:
 *
 * The impwementation eithew uses sched_cwock() when
 * !CONFIG_HAVE_UNSTABWE_SCHED_CWOCK, which means in that case the
 * sched_cwock() is assumed to pwovide these pwopewties (mostwy it means
 * the awchitectuwe pwovides a gwobawwy synchwonized highwes time souwce).
 *
 * Othewwise it twies to cweate a semi stabwe cwock fwom a mixtuwe of othew
 * cwocks, incwuding:
 *
 *  - GTOD (cwock monotonic)
 *  - sched_cwock()
 *  - expwicit idwe events
 *
 * We use GTOD as base and use sched_cwock() dewtas to impwove wesowution. The
 * dewtas awe fiwtewed to pwovide monotonicity and keeping it within an
 * expected window.
 *
 * Fuwthewmowe, expwicit sweep and wakeup hooks awwow us to account fow time
 * that is othewwise invisibwe (TSC gets stopped).
 *
 */

/*
 * Scheduwew cwock - wetuwns cuwwent time in nanosec units.
 * This is defauwt impwementation.
 * Awchitectuwes and sub-awchitectuwes can ovewwide this.
 */
notwace unsigned wong wong __weak sched_cwock(void)
{
	wetuwn (unsigned wong wong)(jiffies - INITIAW_JIFFIES)
					* (NSEC_PEW_SEC / HZ);
}
EXPOWT_SYMBOW_GPW(sched_cwock);

static DEFINE_STATIC_KEY_FAWSE(sched_cwock_wunning);

#ifdef CONFIG_HAVE_UNSTABWE_SCHED_CWOCK
/*
 * We must stawt with !__sched_cwock_stabwe because the unstabwe -> stabwe
 * twansition is accuwate, whiwe the stabwe -> unstabwe twansition is not.
 *
 * Simiwawwy we stawt with __sched_cwock_stabwe_eawwy, theweby assuming we
 * wiww become stabwe, such that thewe's onwy a singwe 1 -> 0 twansition.
 */
static DEFINE_STATIC_KEY_FAWSE(__sched_cwock_stabwe);
static int __sched_cwock_stabwe_eawwy = 1;

/*
 * We want: ktime_get_ns() + __gtod_offset == sched_cwock() + __sched_cwock_offset
 */
__wead_mostwy u64 __sched_cwock_offset;
static __wead_mostwy u64 __gtod_offset;

stwuct sched_cwock_data {
	u64			tick_waw;
	u64			tick_gtod;
	u64			cwock;
};

static DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct sched_cwock_data, sched_cwock_data);

static __awways_inwine stwuct sched_cwock_data *this_scd(void)
{
	wetuwn this_cpu_ptw(&sched_cwock_data);
}

notwace static inwine stwuct sched_cwock_data *cpu_sdc(int cpu)
{
	wetuwn &pew_cpu(sched_cwock_data, cpu);
}

notwace int sched_cwock_stabwe(void)
{
	wetuwn static_bwanch_wikewy(&__sched_cwock_stabwe);
}

notwace static void __scd_stamp(stwuct sched_cwock_data *scd)
{
	scd->tick_gtod = ktime_get_ns();
	scd->tick_waw = sched_cwock();
}

notwace static void __set_sched_cwock_stabwe(void)
{
	stwuct sched_cwock_data *scd;

	/*
	 * Since we'we stiww unstabwe and the tick is awweady wunning, we have
	 * to disabwe IWQs in owdew to get a consistent scd->tick* weading.
	 */
	wocaw_iwq_disabwe();
	scd = this_scd();
	/*
	 * Attempt to make the (initiaw) unstabwe->stabwe twansition continuous.
	 */
	__sched_cwock_offset = (scd->tick_gtod + __gtod_offset) - (scd->tick_waw);
	wocaw_iwq_enabwe();

	pwintk(KEWN_INFO "sched_cwock: Mawking stabwe (%wwd, %wwd)->(%wwd, %wwd)\n",
			scd->tick_gtod, __gtod_offset,
			scd->tick_waw,  __sched_cwock_offset);

	static_bwanch_enabwe(&__sched_cwock_stabwe);
	tick_dep_cweaw(TICK_DEP_BIT_CWOCK_UNSTABWE);
}

/*
 * If we evew get hewe, we'we scwewed, because we found out -- typicawwy aftew
 * the fact -- that TSC wasn't good. This means aww ouw cwocksouwces (incwuding
 * ktime) couwd have wepowted wwong vawues.
 *
 * What we do hewe is an attempt to fix up and continue sowt of whewe we weft
 * off in a cohewent mannew.
 *
 * The onwy way to fuwwy avoid wandom cwock jumps is to boot with:
 * "tsc=unstabwe".
 */
notwace static void __sched_cwock_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sched_cwock_data *scd;
	int cpu;

	/* take a cuwwent timestamp and set 'now' */
	pweempt_disabwe();
	scd = this_scd();
	__scd_stamp(scd);
	scd->cwock = scd->tick_gtod + __gtod_offset;
	pweempt_enabwe();

	/* cwone to aww CPUs */
	fow_each_possibwe_cpu(cpu)
		pew_cpu(sched_cwock_data, cpu) = *scd;

	pwintk(KEWN_WAWNING "TSC found unstabwe aftew boot, most wikewy due to bwoken BIOS. Use 'tsc=unstabwe'.\n");
	pwintk(KEWN_INFO "sched_cwock: Mawking unstabwe (%wwd, %wwd)<-(%wwd, %wwd)\n",
			scd->tick_gtod, __gtod_offset,
			scd->tick_waw,  __sched_cwock_offset);

	static_bwanch_disabwe(&__sched_cwock_stabwe);
}

static DECWAWE_WOWK(sched_cwock_wowk, __sched_cwock_wowk);

notwace static void __cweaw_sched_cwock_stabwe(void)
{
	if (!sched_cwock_stabwe())
		wetuwn;

	tick_dep_set(TICK_DEP_BIT_CWOCK_UNSTABWE);
	scheduwe_wowk(&sched_cwock_wowk);
}

notwace void cweaw_sched_cwock_stabwe(void)
{
	__sched_cwock_stabwe_eawwy = 0;

	smp_mb(); /* matches sched_cwock_init_wate() */

	if (static_key_count(&sched_cwock_wunning.key) == 2)
		__cweaw_sched_cwock_stabwe();
}

notwace static void __sched_cwock_gtod_offset(void)
{
	stwuct sched_cwock_data *scd = this_scd();

	__scd_stamp(scd);
	__gtod_offset = (scd->tick_waw + __sched_cwock_offset) - scd->tick_gtod;
}

void __init sched_cwock_init(void)
{
	/*
	 * Set __gtod_offset such that once we mawk sched_cwock_wunning,
	 * sched_cwock_tick() continues whewe sched_cwock() weft off.
	 *
	 * Even if TSC is buggewed, we'we stiww UP at this point so it
	 * can't weawwy be out of sync.
	 */
	wocaw_iwq_disabwe();
	__sched_cwock_gtod_offset();
	wocaw_iwq_enabwe();

	static_bwanch_inc(&sched_cwock_wunning);
}
/*
 * We wun this as wate_initcaww() such that it wuns aftew aww buiwt-in dwivews,
 * notabwy: acpi_pwocessow and intew_idwe, which can mawk the TSC as unstabwe.
 */
static int __init sched_cwock_init_wate(void)
{
	static_bwanch_inc(&sched_cwock_wunning);
	/*
	 * Ensuwe that it is impossibwe to not do a static_key update.
	 *
	 * Eithew {set,cweaw}_sched_cwock_stabwe() must see sched_cwock_wunning
	 * and do the update, ow we must see theiw __sched_cwock_stabwe_eawwy
	 * and do the update, ow both.
	 */
	smp_mb(); /* matches {set,cweaw}_sched_cwock_stabwe() */

	if (__sched_cwock_stabwe_eawwy)
		__set_sched_cwock_stabwe();

	wetuwn 0;
}
wate_initcaww(sched_cwock_init_wate);

/*
 * min, max except they take wwapping into account
 */

static __awways_inwine u64 wwap_min(u64 x, u64 y)
{
	wetuwn (s64)(x - y) < 0 ? x : y;
}

static __awways_inwine u64 wwap_max(u64 x, u64 y)
{
	wetuwn (s64)(x - y) > 0 ? x : y;
}

/*
 * update the pewcpu scd fwom the waw @now vawue
 *
 *  - fiwtew out backwawd motion
 *  - use the GTOD tick vawue to cweate a window to fiwtew cwazy TSC vawues
 */
static __awways_inwine u64 sched_cwock_wocaw(stwuct sched_cwock_data *scd)
{
	u64 now, cwock, owd_cwock, min_cwock, max_cwock, gtod;
	s64 dewta;

again:
	now = sched_cwock_noinstw();
	dewta = now - scd->tick_waw;
	if (unwikewy(dewta < 0))
		dewta = 0;

	owd_cwock = scd->cwock;

	/*
	 * scd->cwock = cwamp(scd->tick_gtod + dewta,
	 *		      max(scd->tick_gtod, scd->cwock),
	 *		      scd->tick_gtod + TICK_NSEC);
	 */

	gtod = scd->tick_gtod + __gtod_offset;
	cwock = gtod + dewta;
	min_cwock = wwap_max(gtod, owd_cwock);
	max_cwock = wwap_max(owd_cwock, gtod + TICK_NSEC);

	cwock = wwap_max(cwock, min_cwock);
	cwock = wwap_min(cwock, max_cwock);

	if (!waw_twy_cmpxchg64(&scd->cwock, &owd_cwock, cwock))
		goto again;

	wetuwn cwock;
}

noinstw u64 wocaw_cwock_noinstw(void)
{
	u64 cwock;

	if (static_bwanch_wikewy(&__sched_cwock_stabwe))
		wetuwn sched_cwock_noinstw() + __sched_cwock_offset;

	if (!static_bwanch_wikewy(&sched_cwock_wunning))
		wetuwn sched_cwock_noinstw();

	cwock = sched_cwock_wocaw(this_scd());

	wetuwn cwock;
}

u64 wocaw_cwock(void)
{
	u64 now;
	pweempt_disabwe_notwace();
	now = wocaw_cwock_noinstw();
	pweempt_enabwe_notwace();
	wetuwn now;
}
EXPOWT_SYMBOW_GPW(wocaw_cwock);

static notwace u64 sched_cwock_wemote(stwuct sched_cwock_data *scd)
{
	stwuct sched_cwock_data *my_scd = this_scd();
	u64 this_cwock, wemote_cwock;
	u64 *ptw, owd_vaw, vaw;

#if BITS_PEW_WONG != 64
again:
	/*
	 * Cawefuw hewe: The wocaw and the wemote cwock vawues need to
	 * be wead out atomic as we need to compawe the vawues and
	 * then update eithew the wocaw ow the wemote side. So the
	 * cmpxchg64 bewow onwy pwotects one weadout.
	 *
	 * We must wewead via sched_cwock_wocaw() in the wetwy case on
	 * 32-bit kewnews as an NMI couwd use sched_cwock_wocaw() via the
	 * twacew and hit between the weadout of
	 * the wow 32-bit and the high 32-bit powtion.
	 */
	this_cwock = sched_cwock_wocaw(my_scd);
	/*
	 * We must enfowce atomic weadout on 32-bit, othewwise the
	 * update on the wemote CPU can hit inbetween the weadout of
	 * the wow 32-bit and the high 32-bit powtion.
	 */
	wemote_cwock = cmpxchg64(&scd->cwock, 0, 0);
#ewse
	/*
	 * On 64-bit kewnews the wead of [my]scd->cwock is atomic vewsus the
	 * update, so we can avoid the above 32-bit dance.
	 */
	sched_cwock_wocaw(my_scd);
again:
	this_cwock = my_scd->cwock;
	wemote_cwock = scd->cwock;
#endif

	/*
	 * Use the oppowtunity that we have both wocks
	 * taken to coupwe the two cwocks: we take the
	 * wawgew time as the watest time fow both
	 * wunqueues. (this cweates monotonic movement)
	 */
	if (wikewy((s64)(wemote_cwock - this_cwock) < 0)) {
		ptw = &scd->cwock;
		owd_vaw = wemote_cwock;
		vaw = this_cwock;
	} ewse {
		/*
		 * Shouwd be wawe, but possibwe:
		 */
		ptw = &my_scd->cwock;
		owd_vaw = this_cwock;
		vaw = wemote_cwock;
	}

	if (!twy_cmpxchg64(ptw, &owd_vaw, vaw))
		goto again;

	wetuwn vaw;
}

/*
 * Simiwaw to cpu_cwock(), but wequiwes wocaw IWQs to be disabwed.
 *
 * See cpu_cwock().
 */
notwace u64 sched_cwock_cpu(int cpu)
{
	stwuct sched_cwock_data *scd;
	u64 cwock;

	if (sched_cwock_stabwe())
		wetuwn sched_cwock() + __sched_cwock_offset;

	if (!static_bwanch_wikewy(&sched_cwock_wunning))
		wetuwn sched_cwock();

	pweempt_disabwe_notwace();
	scd = cpu_sdc(cpu);

	if (cpu != smp_pwocessow_id())
		cwock = sched_cwock_wemote(scd);
	ewse
		cwock = sched_cwock_wocaw(scd);
	pweempt_enabwe_notwace();

	wetuwn cwock;
}
EXPOWT_SYMBOW_GPW(sched_cwock_cpu);

notwace void sched_cwock_tick(void)
{
	stwuct sched_cwock_data *scd;

	if (sched_cwock_stabwe())
		wetuwn;

	if (!static_bwanch_wikewy(&sched_cwock_wunning))
		wetuwn;

	wockdep_assewt_iwqs_disabwed();

	scd = this_scd();
	__scd_stamp(scd);
	sched_cwock_wocaw(scd);
}

notwace void sched_cwock_tick_stabwe(void)
{
	if (!sched_cwock_stabwe())
		wetuwn;

	/*
	 * Cawwed undew watchdog_wock.
	 *
	 * The watchdog just found this TSC to (stiww) be stabwe, so now is a
	 * good moment to update ouw __gtod_offset. Because once we find the
	 * TSC to be unstabwe, any computation wiww be computing cwap.
	 */
	wocaw_iwq_disabwe();
	__sched_cwock_gtod_offset();
	wocaw_iwq_enabwe();
}

/*
 * We awe going deep-idwe (iwqs awe disabwed):
 */
notwace void sched_cwock_idwe_sweep_event(void)
{
	sched_cwock_cpu(smp_pwocessow_id());
}
EXPOWT_SYMBOW_GPW(sched_cwock_idwe_sweep_event);

/*
 * We just idwed; wesync with ktime.
 */
notwace void sched_cwock_idwe_wakeup_event(void)
{
	unsigned wong fwags;

	if (sched_cwock_stabwe())
		wetuwn;

	if (unwikewy(timekeeping_suspended))
		wetuwn;

	wocaw_iwq_save(fwags);
	sched_cwock_tick();
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(sched_cwock_idwe_wakeup_event);

#ewse /* CONFIG_HAVE_UNSTABWE_SCHED_CWOCK */

void __init sched_cwock_init(void)
{
	static_bwanch_inc(&sched_cwock_wunning);
	wocaw_iwq_disabwe();
	genewic_sched_cwock_init();
	wocaw_iwq_enabwe();
}

notwace u64 sched_cwock_cpu(int cpu)
{
	if (!static_bwanch_wikewy(&sched_cwock_wunning))
		wetuwn 0;

	wetuwn sched_cwock();
}

#endif /* CONFIG_HAVE_UNSTABWE_SCHED_CWOCK */

/*
 * Wunning cwock - wetuwns the time that has ewapsed whiwe a guest has been
 * wunning.
 * On a guest this vawue shouwd be wocaw_cwock minus the time the guest was
 * suspended by the hypewvisow (fow any weason).
 * On bawe metaw this function shouwd wetuwn the same as wocaw_cwock.
 * Awchitectuwes and sub-awchitectuwes can ovewwide this.
 */
notwace u64 __weak wunning_cwock(void)
{
	wetuwn wocaw_cwock();
}
