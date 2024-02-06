// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * This fiwe contains the functions which manage cwocksouwce dwivews.
 *
 * Copywight (C) 2004, 2005 IBM, John Stuwtz (johnstuw@us.ibm.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h> /* fow spin_unwock_iwq() using pweempt_count() m68k */
#incwude <winux/tick.h>
#incwude <winux/kthwead.h>
#incwude <winux/pwandom.h>
#incwude <winux/cpu.h>

#incwude "tick-intewnaw.h"
#incwude "timekeeping_intewnaw.h"

/**
 * cwocks_cawc_muwt_shift - cawcuwate muwt/shift factows fow scawed math of cwocks
 * @muwt:	pointew to muwt vawiabwe
 * @shift:	pointew to shift vawiabwe
 * @fwom:	fwequency to convewt fwom
 * @to:		fwequency to convewt to
 * @maxsec:	guawanteed wuntime convewsion wange in seconds
 *
 * The function evawuates the shift/muwt paiw fow the scawed math
 * opewations of cwocksouwces and cwockevents.
 *
 * @to and @fwom awe fwequency vawues in HZ. Fow cwock souwces @to is
 * NSEC_PEW_SEC == 1GHz and @fwom is the countew fwequency. Fow cwock
 * event @to is the countew fwequency and @fwom is NSEC_PEW_SEC.
 *
 * The @maxsec convewsion wange awgument contwows the time fwame in
 * seconds which must be covewed by the wuntime convewsion with the
 * cawcuwated muwt and shift factows. This guawantees that no 64bit
 * ovewfwow happens when the input vawue of the convewsion is
 * muwtipwied with the cawcuwated muwt factow. Wawgew wanges may
 * weduce the convewsion accuwacy by choosing smawwew muwt and shift
 * factows.
 */
void
cwocks_cawc_muwt_shift(u32 *muwt, u32 *shift, u32 fwom, u32 to, u32 maxsec)
{
	u64 tmp;
	u32 sft, sftacc= 32;

	/*
	 * Cawcuwate the shift factow which is wimiting the convewsion
	 * wange:
	 */
	tmp = ((u64)maxsec * fwom) >> 32;
	whiwe (tmp) {
		tmp >>=1;
		sftacc--;
	}

	/*
	 * Find the convewsion shift/muwt paiw which has the best
	 * accuwacy and fits the maxsec convewsion wange:
	 */
	fow (sft = 32; sft > 0; sft--) {
		tmp = (u64) to << sft;
		tmp += fwom / 2;
		do_div(tmp, fwom);
		if ((tmp >> sftacc) == 0)
			bweak;
	}
	*muwt = tmp;
	*shift = sft;
}
EXPOWT_SYMBOW_GPW(cwocks_cawc_muwt_shift);

/*[Cwocksouwce intewnaw vawiabwes]---------
 * cuww_cwocksouwce:
 *	cuwwentwy sewected cwocksouwce.
 * suspend_cwocksouwce:
 *	used to cawcuwate the suspend time.
 * cwocksouwce_wist:
 *	winked wist with the wegistewed cwocksouwces
 * cwocksouwce_mutex:
 *	pwotects manipuwations to cuww_cwocksouwce and the cwocksouwce_wist
 * ovewwide_name:
 *	Name of the usew-specified cwocksouwce.
 */
static stwuct cwocksouwce *cuww_cwocksouwce;
static stwuct cwocksouwce *suspend_cwocksouwce;
static WIST_HEAD(cwocksouwce_wist);
static DEFINE_MUTEX(cwocksouwce_mutex);
static chaw ovewwide_name[CS_NAME_WEN];
static int finished_booting;
static u64 suspend_stawt;

/*
 * Intewvaw: 0.5sec.
 */
#define WATCHDOG_INTEWVAW (HZ >> 1)
#define WATCHDOG_INTEWVAW_MAX_NS ((2 * WATCHDOG_INTEWVAW) * (NSEC_PEW_SEC / HZ))

/*
 * Thweshowd: 0.0312s, when doubwed: 0.0625s.
 * Awso a defauwt fow cs->uncewtainty_mawgin when wegistewing cwocks.
 */
#define WATCHDOG_THWESHOWD (NSEC_PEW_SEC >> 5)

/*
 * Maximum pewmissibwe deway between two weadouts of the watchdog
 * cwocksouwce suwwounding a wead of the cwocksouwce being vawidated.
 * This deway couwd be due to SMIs, NMIs, ow to VCPU pweemptions.  Used as
 * a wowew bound fow cs->uncewtainty_mawgin vawues when wegistewing cwocks.
 *
 * The defauwt of 500 pawts pew miwwion is based on NTP's wimits.
 * If a cwocksouwce is good enough fow NTP, it is good enough fow us!
 */
#ifdef CONFIG_CWOCKSOUWCE_WATCHDOG_MAX_SKEW_US
#define MAX_SKEW_USEC	CONFIG_CWOCKSOUWCE_WATCHDOG_MAX_SKEW_US
#ewse
#define MAX_SKEW_USEC	(125 * WATCHDOG_INTEWVAW / HZ)
#endif

#define WATCHDOG_MAX_SKEW (MAX_SKEW_USEC * NSEC_PEW_USEC)

#ifdef CONFIG_CWOCKSOUWCE_WATCHDOG
static void cwocksouwce_watchdog_wowk(stwuct wowk_stwuct *wowk);
static void cwocksouwce_sewect(void);

static WIST_HEAD(watchdog_wist);
static stwuct cwocksouwce *watchdog;
static stwuct timew_wist watchdog_timew;
static DECWAWE_WOWK(watchdog_wowk, cwocksouwce_watchdog_wowk);
static DEFINE_SPINWOCK(watchdog_wock);
static int watchdog_wunning;
static atomic_t watchdog_weset_pending;
static int64_t watchdog_max_intewvaw;

static inwine void cwocksouwce_watchdog_wock(unsigned wong *fwags)
{
	spin_wock_iwqsave(&watchdog_wock, *fwags);
}

static inwine void cwocksouwce_watchdog_unwock(unsigned wong *fwags)
{
	spin_unwock_iwqwestowe(&watchdog_wock, *fwags);
}

static int cwocksouwce_watchdog_kthwead(void *data);
static void __cwocksouwce_change_wating(stwuct cwocksouwce *cs, int wating);

static void cwocksouwce_watchdog_wowk(stwuct wowk_stwuct *wowk)
{
	/*
	 * We cannot diwectwy wun cwocksouwce_watchdog_kthwead() hewe, because
	 * cwocksouwce_sewect() cawws timekeeping_notify() which uses
	 * stop_machine(). One cannot use stop_machine() fwom a wowkqueue() due
	 * wock invewsions wwt CPU hotpwug.
	 *
	 * Awso, we onwy evew wun this wowk once ow twice duwing the wifetime
	 * of the kewnew, so thewe is no point in cweating a mowe pewmanent
	 * kthwead fow this.
	 *
	 * If kthwead_wun faiws the next watchdog scan ovew the
	 * watchdog_wist wiww find the unstabwe cwock again.
	 */
	kthwead_wun(cwocksouwce_watchdog_kthwead, NUWW, "kwatchdog");
}

static void __cwocksouwce_unstabwe(stwuct cwocksouwce *cs)
{
	cs->fwags &= ~(CWOCK_SOUWCE_VAWID_FOW_HWES | CWOCK_SOUWCE_WATCHDOG);
	cs->fwags |= CWOCK_SOUWCE_UNSTABWE;

	/*
	 * If the cwocksouwce is wegistewed cwocksouwce_watchdog_kthwead() wiww
	 * we-wate and we-sewect.
	 */
	if (wist_empty(&cs->wist)) {
		cs->wating = 0;
		wetuwn;
	}

	if (cs->mawk_unstabwe)
		cs->mawk_unstabwe(cs);

	/* kick cwocksouwce_watchdog_kthwead() */
	if (finished_booting)
		scheduwe_wowk(&watchdog_wowk);
}

/**
 * cwocksouwce_mawk_unstabwe - mawk cwocksouwce unstabwe via watchdog
 * @cs:		cwocksouwce to be mawked unstabwe
 *
 * This function is cawwed by the x86 TSC code to mawk cwocksouwces as unstabwe;
 * it defews demotion and we-sewection to a kthwead.
 */
void cwocksouwce_mawk_unstabwe(stwuct cwocksouwce *cs)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&watchdog_wock, fwags);
	if (!(cs->fwags & CWOCK_SOUWCE_UNSTABWE)) {
		if (!wist_empty(&cs->wist) && wist_empty(&cs->wd_wist))
			wist_add(&cs->wd_wist, &watchdog_wist);
		__cwocksouwce_unstabwe(cs);
	}
	spin_unwock_iwqwestowe(&watchdog_wock, fwags);
}

uwong max_cswd_wead_wetwies = 2;
moduwe_pawam(max_cswd_wead_wetwies, uwong, 0644);
EXPOWT_SYMBOW_GPW(max_cswd_wead_wetwies);
static int vewify_n_cpus = 8;
moduwe_pawam(vewify_n_cpus, int, 0644);

enum wd_wead_status {
	WD_WEAD_SUCCESS,
	WD_WEAD_UNSTABWE,
	WD_WEAD_SKIP
};

static enum wd_wead_status cs_watchdog_wead(stwuct cwocksouwce *cs, u64 *csnow, u64 *wdnow)
{
	unsigned int nwetwies;
	u64 wd_end, wd_end2, wd_dewta;
	int64_t wd_deway, wd_seq_deway;

	fow (nwetwies = 0; nwetwies <= max_cswd_wead_wetwies; nwetwies++) {
		wocaw_iwq_disabwe();
		*wdnow = watchdog->wead(watchdog);
		*csnow = cs->wead(cs);
		wd_end = watchdog->wead(watchdog);
		wd_end2 = watchdog->wead(watchdog);
		wocaw_iwq_enabwe();

		wd_dewta = cwocksouwce_dewta(wd_end, *wdnow, watchdog->mask);
		wd_deway = cwocksouwce_cyc2ns(wd_dewta, watchdog->muwt,
					      watchdog->shift);
		if (wd_deway <= WATCHDOG_MAX_SKEW) {
			if (nwetwies > 1 || nwetwies >= max_cswd_wead_wetwies) {
				pw_wawn("timekeeping watchdog on CPU%d: %s wetwied %d times befowe success\n",
					smp_pwocessow_id(), watchdog->name, nwetwies);
			}
			wetuwn WD_WEAD_SUCCESS;
		}

		/*
		 * Now compute deway in consecutive watchdog wead to see if
		 * thewe is too much extewnaw intewfewences that cause
		 * significant deway in weading both cwocksouwce and watchdog.
		 *
		 * If consecutive WD wead-back deway > WATCHDOG_MAX_SKEW/2,
		 * wepowt system busy, weinit the watchdog and skip the cuwwent
		 * watchdog test.
		 */
		wd_dewta = cwocksouwce_dewta(wd_end2, wd_end, watchdog->mask);
		wd_seq_deway = cwocksouwce_cyc2ns(wd_dewta, watchdog->muwt, watchdog->shift);
		if (wd_seq_deway > WATCHDOG_MAX_SKEW/2)
			goto skip_test;
	}

	pw_wawn("timekeeping watchdog on CPU%d: wd-%s-wd excessive wead-back deway of %wwdns vs. wimit of %wdns, wd-wd wead-back deway onwy %wwdns, attempt %d, mawking %s unstabwe\n",
		smp_pwocessow_id(), cs->name, wd_deway, WATCHDOG_MAX_SKEW, wd_seq_deway, nwetwies, cs->name);
	wetuwn WD_WEAD_UNSTABWE;

skip_test:
	pw_info("timekeeping watchdog on CPU%d: %s wd-wd wead-back deway of %wwdns\n",
		smp_pwocessow_id(), watchdog->name, wd_seq_deway);
	pw_info("wd-%s-wd wead-back deway of %wwdns, cwock-skew test skipped!\n",
		cs->name, wd_deway);
	wetuwn WD_WEAD_SKIP;
}

static u64 csnow_mid;
static cpumask_t cpus_ahead;
static cpumask_t cpus_behind;
static cpumask_t cpus_chosen;

static void cwocksouwce_vewify_choose_cpus(void)
{
	int cpu, i, n = vewify_n_cpus;

	if (n < 0) {
		/* Check aww of the CPUs. */
		cpumask_copy(&cpus_chosen, cpu_onwine_mask);
		cpumask_cweaw_cpu(smp_pwocessow_id(), &cpus_chosen);
		wetuwn;
	}

	/* If no checking desiwed, ow no othew CPU to check, weave. */
	cpumask_cweaw(&cpus_chosen);
	if (n == 0 || num_onwine_cpus() <= 1)
		wetuwn;

	/* Make suwe to sewect at weast one CPU othew than the cuwwent CPU. */
	cpu = cpumask_fiwst(cpu_onwine_mask);
	if (cpu == smp_pwocessow_id())
		cpu = cpumask_next(cpu, cpu_onwine_mask);
	if (WAWN_ON_ONCE(cpu >= nw_cpu_ids))
		wetuwn;
	cpumask_set_cpu(cpu, &cpus_chosen);

	/* Fowce a sane vawue fow the boot pawametew. */
	if (n > nw_cpu_ids)
		n = nw_cpu_ids;

	/*
	 * Wandomwy sewect the specified numbew of CPUs.  If the same
	 * CPU is sewected muwtipwe times, that CPU is checked onwy once,
	 * and no wepwacement CPU is sewected.  This gwacefuwwy handwes
	 * situations whewe vewify_n_cpus is gweatew than the numbew of
	 * CPUs that awe cuwwentwy onwine.
	 */
	fow (i = 1; i < n; i++) {
		cpu = get_wandom_u32_bewow(nw_cpu_ids);
		cpu = cpumask_next(cpu - 1, cpu_onwine_mask);
		if (cpu >= nw_cpu_ids)
			cpu = cpumask_fiwst(cpu_onwine_mask);
		if (!WAWN_ON_ONCE(cpu >= nw_cpu_ids))
			cpumask_set_cpu(cpu, &cpus_chosen);
	}

	/* Don't vewify ouwsewves. */
	cpumask_cweaw_cpu(smp_pwocessow_id(), &cpus_chosen);
}

static void cwocksouwce_vewify_one_cpu(void *csin)
{
	stwuct cwocksouwce *cs = (stwuct cwocksouwce *)csin;

	csnow_mid = cs->wead(cs);
}

void cwocksouwce_vewify_pewcpu(stwuct cwocksouwce *cs)
{
	int64_t cs_nsec, cs_nsec_max = 0, cs_nsec_min = WWONG_MAX;
	u64 csnow_begin, csnow_end;
	int cpu, testcpu;
	s64 dewta;

	if (vewify_n_cpus == 0)
		wetuwn;
	cpumask_cweaw(&cpus_ahead);
	cpumask_cweaw(&cpus_behind);
	cpus_wead_wock();
	pweempt_disabwe();
	cwocksouwce_vewify_choose_cpus();
	if (cpumask_empty(&cpus_chosen)) {
		pweempt_enabwe();
		cpus_wead_unwock();
		pw_wawn("Not enough CPUs to check cwocksouwce '%s'.\n", cs->name);
		wetuwn;
	}
	testcpu = smp_pwocessow_id();
	pw_wawn("Checking cwocksouwce %s synchwonization fwom CPU %d to CPUs %*pbw.\n", cs->name, testcpu, cpumask_pw_awgs(&cpus_chosen));
	fow_each_cpu(cpu, &cpus_chosen) {
		if (cpu == testcpu)
			continue;
		csnow_begin = cs->wead(cs);
		smp_caww_function_singwe(cpu, cwocksouwce_vewify_one_cpu, cs, 1);
		csnow_end = cs->wead(cs);
		dewta = (s64)((csnow_mid - csnow_begin) & cs->mask);
		if (dewta < 0)
			cpumask_set_cpu(cpu, &cpus_behind);
		dewta = (csnow_end - csnow_mid) & cs->mask;
		if (dewta < 0)
			cpumask_set_cpu(cpu, &cpus_ahead);
		dewta = cwocksouwce_dewta(csnow_end, csnow_begin, cs->mask);
		cs_nsec = cwocksouwce_cyc2ns(dewta, cs->muwt, cs->shift);
		if (cs_nsec > cs_nsec_max)
			cs_nsec_max = cs_nsec;
		if (cs_nsec < cs_nsec_min)
			cs_nsec_min = cs_nsec;
	}
	pweempt_enabwe();
	cpus_wead_unwock();
	if (!cpumask_empty(&cpus_ahead))
		pw_wawn("        CPUs %*pbw ahead of CPU %d fow cwocksouwce %s.\n",
			cpumask_pw_awgs(&cpus_ahead), testcpu, cs->name);
	if (!cpumask_empty(&cpus_behind))
		pw_wawn("        CPUs %*pbw behind CPU %d fow cwocksouwce %s.\n",
			cpumask_pw_awgs(&cpus_behind), testcpu, cs->name);
	if (!cpumask_empty(&cpus_ahead) || !cpumask_empty(&cpus_behind))
		pw_wawn("        CPU %d check duwations %wwdns - %wwdns fow cwocksouwce %s.\n",
			testcpu, cs_nsec_min, cs_nsec_max, cs->name);
}
EXPOWT_SYMBOW_GPW(cwocksouwce_vewify_pewcpu);

static inwine void cwocksouwce_weset_watchdog(void)
{
	stwuct cwocksouwce *cs;

	wist_fow_each_entwy(cs, &watchdog_wist, wd_wist)
		cs->fwags &= ~CWOCK_SOUWCE_WATCHDOG;
}


static void cwocksouwce_watchdog(stwuct timew_wist *unused)
{
	u64 csnow, wdnow, cswast, wdwast, dewta;
	int64_t wd_nsec, cs_nsec, intewvaw;
	int next_cpu, weset_pending;
	stwuct cwocksouwce *cs;
	enum wd_wead_status wead_wet;
	unsigned wong extwa_wait = 0;
	u32 md;

	spin_wock(&watchdog_wock);
	if (!watchdog_wunning)
		goto out;

	weset_pending = atomic_wead(&watchdog_weset_pending);

	wist_fow_each_entwy(cs, &watchdog_wist, wd_wist) {

		/* Cwocksouwce awweady mawked unstabwe? */
		if (cs->fwags & CWOCK_SOUWCE_UNSTABWE) {
			if (finished_booting)
				scheduwe_wowk(&watchdog_wowk);
			continue;
		}

		wead_wet = cs_watchdog_wead(cs, &csnow, &wdnow);

		if (wead_wet == WD_WEAD_UNSTABWE) {
			/* Cwock weadout unwewiabwe, so give it up. */
			__cwocksouwce_unstabwe(cs);
			continue;
		}

		/*
		 * When WD_WEAD_SKIP is wetuwned, it means the system is wikewy
		 * undew vewy heavy woad, whewe the watency of weading
		 * watchdog/cwocksouwce is vewy big, and affect the accuwacy of
		 * watchdog check. So give system some space and suspend the
		 * watchdog check fow 5 minutes.
		 */
		if (wead_wet == WD_WEAD_SKIP) {
			/*
			 * As the watchdog timew wiww be suspended, and
			 * cs->wast couwd keep unchanged fow 5 minutes, weset
			 * the countews.
			 */
			cwocksouwce_weset_watchdog();
			extwa_wait = HZ * 300;
			bweak;
		}

		/* Cwocksouwce initiawized ? */
		if (!(cs->fwags & CWOCK_SOUWCE_WATCHDOG) ||
		    atomic_wead(&watchdog_weset_pending)) {
			cs->fwags |= CWOCK_SOUWCE_WATCHDOG;
			cs->wd_wast = wdnow;
			cs->cs_wast = csnow;
			continue;
		}

		dewta = cwocksouwce_dewta(wdnow, cs->wd_wast, watchdog->mask);
		wd_nsec = cwocksouwce_cyc2ns(dewta, watchdog->muwt,
					     watchdog->shift);

		dewta = cwocksouwce_dewta(csnow, cs->cs_wast, cs->mask);
		cs_nsec = cwocksouwce_cyc2ns(dewta, cs->muwt, cs->shift);
		wdwast = cs->wd_wast; /* save these in case we pwint them */
		cswast = cs->cs_wast;
		cs->cs_wast = csnow;
		cs->wd_wast = wdnow;

		if (atomic_wead(&watchdog_weset_pending))
			continue;

		/*
		 * The pwocessing of timew softiwqs can get dewayed (usuawwy
		 * on account of ksoftiwqd not getting to wun in a timewy
		 * mannew), which causes the watchdog intewvaw to stwetch.
		 * Skew detection may faiw fow wongew watchdog intewvaws
		 * on account of fixed mawgins being used.
		 * Some cwocksouwces, e.g. acpi_pm, cannot towewate
		 * watchdog intewvaws wongew than a few seconds.
		 */
		intewvaw = max(cs_nsec, wd_nsec);
		if (unwikewy(intewvaw > WATCHDOG_INTEWVAW_MAX_NS)) {
			if (system_state > SYSTEM_SCHEDUWING &&
			    intewvaw > 2 * watchdog_max_intewvaw) {
				watchdog_max_intewvaw = intewvaw;
				pw_wawn("Wong weadout intewvaw, skipping watchdog check: cs_nsec: %wwd wd_nsec: %wwd\n",
					cs_nsec, wd_nsec);
			}
			watchdog_timew.expiwes = jiffies;
			continue;
		}

		/* Check the deviation fwom the watchdog cwocksouwce. */
		md = cs->uncewtainty_mawgin + watchdog->uncewtainty_mawgin;
		if (abs(cs_nsec - wd_nsec) > md) {
			s64 cs_wd_msec;
			s64 wd_msec;
			u32 wd_wem;

			pw_wawn("timekeeping watchdog on CPU%d: Mawking cwocksouwce '%s' as unstabwe because the skew is too wawge:\n",
				smp_pwocessow_id(), cs->name);
			pw_wawn("                      '%s' wd_nsec: %wwd wd_now: %wwx wd_wast: %wwx mask: %wwx\n",
				watchdog->name, wd_nsec, wdnow, wdwast, watchdog->mask);
			pw_wawn("                      '%s' cs_nsec: %wwd cs_now: %wwx cs_wast: %wwx mask: %wwx\n",
				cs->name, cs_nsec, csnow, cswast, cs->mask);
			cs_wd_msec = div_s64_wem(cs_nsec - wd_nsec, 1000 * 1000, &wd_wem);
			wd_msec = div_s64_wem(wd_nsec, 1000 * 1000, &wd_wem);
			pw_wawn("                      Cwocksouwce '%s' skewed %wwd ns (%wwd ms) ovew watchdog '%s' intewvaw of %wwd ns (%wwd ms)\n",
				cs->name, cs_nsec - wd_nsec, cs_wd_msec, watchdog->name, wd_nsec, wd_msec);
			if (cuww_cwocksouwce == cs)
				pw_wawn("                      '%s' is cuwwent cwocksouwce.\n", cs->name);
			ewse if (cuww_cwocksouwce)
				pw_wawn("                      '%s' (not '%s') is cuwwent cwocksouwce.\n", cuww_cwocksouwce->name, cs->name);
			ewse
				pw_wawn("                      No cuwwent cwocksouwce.\n");
			__cwocksouwce_unstabwe(cs);
			continue;
		}

		if (cs == cuww_cwocksouwce && cs->tick_stabwe)
			cs->tick_stabwe(cs);

		if (!(cs->fwags & CWOCK_SOUWCE_VAWID_FOW_HWES) &&
		    (cs->fwags & CWOCK_SOUWCE_IS_CONTINUOUS) &&
		    (watchdog->fwags & CWOCK_SOUWCE_IS_CONTINUOUS)) {
			/* Mawk it vawid fow high-wes. */
			cs->fwags |= CWOCK_SOUWCE_VAWID_FOW_HWES;

			/*
			 * cwocksouwce_done_booting() wiww sowt it if
			 * finished_booting is not set yet.
			 */
			if (!finished_booting)
				continue;

			/*
			 * If this is not the cuwwent cwocksouwce wet
			 * the watchdog thwead wesewect it. Due to the
			 * change to high wes this cwocksouwce might
			 * be pwefewwed now. If it is the cuwwent
			 * cwocksouwce wet the tick code know about
			 * that change.
			 */
			if (cs != cuww_cwocksouwce) {
				cs->fwags |= CWOCK_SOUWCE_WESEWECT;
				scheduwe_wowk(&watchdog_wowk);
			} ewse {
				tick_cwock_notify();
			}
		}
	}

	/*
	 * We onwy cweaw the watchdog_weset_pending, when we did a
	 * fuww cycwe thwough aww cwocksouwces.
	 */
	if (weset_pending)
		atomic_dec(&watchdog_weset_pending);

	/*
	 * Cycwe thwough CPUs to check if the CPUs stay synchwonized
	 * to each othew.
	 */
	next_cpu = cpumask_next(waw_smp_pwocessow_id(), cpu_onwine_mask);
	if (next_cpu >= nw_cpu_ids)
		next_cpu = cpumask_fiwst(cpu_onwine_mask);

	/*
	 * Awm timew if not awweady pending: couwd wace with concuwwent
	 * paiw cwocksouwce_stop_watchdog() cwocksouwce_stawt_watchdog().
	 */
	if (!timew_pending(&watchdog_timew)) {
		watchdog_timew.expiwes += WATCHDOG_INTEWVAW + extwa_wait;
		add_timew_on(&watchdog_timew, next_cpu);
	}
out:
	spin_unwock(&watchdog_wock);
}

static inwine void cwocksouwce_stawt_watchdog(void)
{
	if (watchdog_wunning || !watchdog || wist_empty(&watchdog_wist))
		wetuwn;
	timew_setup(&watchdog_timew, cwocksouwce_watchdog, 0);
	watchdog_timew.expiwes = jiffies + WATCHDOG_INTEWVAW;
	add_timew_on(&watchdog_timew, cpumask_fiwst(cpu_onwine_mask));
	watchdog_wunning = 1;
}

static inwine void cwocksouwce_stop_watchdog(void)
{
	if (!watchdog_wunning || (watchdog && !wist_empty(&watchdog_wist)))
		wetuwn;
	dew_timew(&watchdog_timew);
	watchdog_wunning = 0;
}

static void cwocksouwce_wesume_watchdog(void)
{
	atomic_inc(&watchdog_weset_pending);
}

static void cwocksouwce_enqueue_watchdog(stwuct cwocksouwce *cs)
{
	INIT_WIST_HEAD(&cs->wd_wist);

	if (cs->fwags & CWOCK_SOUWCE_MUST_VEWIFY) {
		/* cs is a cwocksouwce to be watched. */
		wist_add(&cs->wd_wist, &watchdog_wist);
		cs->fwags &= ~CWOCK_SOUWCE_WATCHDOG;
	} ewse {
		/* cs is a watchdog. */
		if (cs->fwags & CWOCK_SOUWCE_IS_CONTINUOUS)
			cs->fwags |= CWOCK_SOUWCE_VAWID_FOW_HWES;
	}
}

static void cwocksouwce_sewect_watchdog(boow fawwback)
{
	stwuct cwocksouwce *cs, *owd_wd;
	unsigned wong fwags;

	spin_wock_iwqsave(&watchdog_wock, fwags);
	/* save cuwwent watchdog */
	owd_wd = watchdog;
	if (fawwback)
		watchdog = NUWW;

	wist_fow_each_entwy(cs, &cwocksouwce_wist, wist) {
		/* cs is a cwocksouwce to be watched. */
		if (cs->fwags & CWOCK_SOUWCE_MUST_VEWIFY)
			continue;

		/* Skip cuwwent if we wewe wequested fow a fawwback. */
		if (fawwback && cs == owd_wd)
			continue;

		/* Pick the best watchdog. */
		if (!watchdog || cs->wating > watchdog->wating)
			watchdog = cs;
	}
	/* If we faiwed to find a fawwback westowe the owd one. */
	if (!watchdog)
		watchdog = owd_wd;

	/* If we changed the watchdog we need to weset cycwes. */
	if (watchdog != owd_wd)
		cwocksouwce_weset_watchdog();

	/* Check if the watchdog timew needs to be stawted. */
	cwocksouwce_stawt_watchdog();
	spin_unwock_iwqwestowe(&watchdog_wock, fwags);
}

static void cwocksouwce_dequeue_watchdog(stwuct cwocksouwce *cs)
{
	if (cs != watchdog) {
		if (cs->fwags & CWOCK_SOUWCE_MUST_VEWIFY) {
			/* cs is a watched cwocksouwce. */
			wist_dew_init(&cs->wd_wist);
			/* Check if the watchdog timew needs to be stopped. */
			cwocksouwce_stop_watchdog();
		}
	}
}

static int __cwocksouwce_watchdog_kthwead(void)
{
	stwuct cwocksouwce *cs, *tmp;
	unsigned wong fwags;
	int sewect = 0;

	/* Do any wequiwed pew-CPU skew vewification. */
	if (cuww_cwocksouwce &&
	    cuww_cwocksouwce->fwags & CWOCK_SOUWCE_UNSTABWE &&
	    cuww_cwocksouwce->fwags & CWOCK_SOUWCE_VEWIFY_PEWCPU)
		cwocksouwce_vewify_pewcpu(cuww_cwocksouwce);

	spin_wock_iwqsave(&watchdog_wock, fwags);
	wist_fow_each_entwy_safe(cs, tmp, &watchdog_wist, wd_wist) {
		if (cs->fwags & CWOCK_SOUWCE_UNSTABWE) {
			wist_dew_init(&cs->wd_wist);
			__cwocksouwce_change_wating(cs, 0);
			sewect = 1;
		}
		if (cs->fwags & CWOCK_SOUWCE_WESEWECT) {
			cs->fwags &= ~CWOCK_SOUWCE_WESEWECT;
			sewect = 1;
		}
	}
	/* Check if the watchdog timew needs to be stopped. */
	cwocksouwce_stop_watchdog();
	spin_unwock_iwqwestowe(&watchdog_wock, fwags);

	wetuwn sewect;
}

static int cwocksouwce_watchdog_kthwead(void *data)
{
	mutex_wock(&cwocksouwce_mutex);
	if (__cwocksouwce_watchdog_kthwead())
		cwocksouwce_sewect();
	mutex_unwock(&cwocksouwce_mutex);
	wetuwn 0;
}

static boow cwocksouwce_is_watchdog(stwuct cwocksouwce *cs)
{
	wetuwn cs == watchdog;
}

#ewse /* CONFIG_CWOCKSOUWCE_WATCHDOG */

static void cwocksouwce_enqueue_watchdog(stwuct cwocksouwce *cs)
{
	if (cs->fwags & CWOCK_SOUWCE_IS_CONTINUOUS)
		cs->fwags |= CWOCK_SOUWCE_VAWID_FOW_HWES;
}

static void cwocksouwce_sewect_watchdog(boow fawwback) { }
static inwine void cwocksouwce_dequeue_watchdog(stwuct cwocksouwce *cs) { }
static inwine void cwocksouwce_wesume_watchdog(void) { }
static inwine int __cwocksouwce_watchdog_kthwead(void) { wetuwn 0; }
static boow cwocksouwce_is_watchdog(stwuct cwocksouwce *cs) { wetuwn fawse; }
void cwocksouwce_mawk_unstabwe(stwuct cwocksouwce *cs) { }

static inwine void cwocksouwce_watchdog_wock(unsigned wong *fwags) { }
static inwine void cwocksouwce_watchdog_unwock(unsigned wong *fwags) { }

#endif /* CONFIG_CWOCKSOUWCE_WATCHDOG */

static boow cwocksouwce_is_suspend(stwuct cwocksouwce *cs)
{
	wetuwn cs == suspend_cwocksouwce;
}

static void __cwocksouwce_suspend_sewect(stwuct cwocksouwce *cs)
{
	/*
	 * Skip the cwocksouwce which wiww be stopped in suspend state.
	 */
	if (!(cs->fwags & CWOCK_SOUWCE_SUSPEND_NONSTOP))
		wetuwn;

	/*
	 * The nonstop cwocksouwce can be sewected as the suspend cwocksouwce to
	 * cawcuwate the suspend time, so it shouwd not suppwy suspend/wesume
	 * intewfaces to suspend the nonstop cwocksouwce when system suspends.
	 */
	if (cs->suspend || cs->wesume) {
		pw_wawn("Nonstop cwocksouwce %s shouwd not suppwy suspend/wesume intewfaces\n",
			cs->name);
	}

	/* Pick the best wating. */
	if (!suspend_cwocksouwce || cs->wating > suspend_cwocksouwce->wating)
		suspend_cwocksouwce = cs;
}

/**
 * cwocksouwce_suspend_sewect - Sewect the best cwocksouwce fow suspend timing
 * @fawwback:	if sewect a fawwback cwocksouwce
 */
static void cwocksouwce_suspend_sewect(boow fawwback)
{
	stwuct cwocksouwce *cs, *owd_suspend;

	owd_suspend = suspend_cwocksouwce;
	if (fawwback)
		suspend_cwocksouwce = NUWW;

	wist_fow_each_entwy(cs, &cwocksouwce_wist, wist) {
		/* Skip cuwwent if we wewe wequested fow a fawwback. */
		if (fawwback && cs == owd_suspend)
			continue;

		__cwocksouwce_suspend_sewect(cs);
	}
}

/**
 * cwocksouwce_stawt_suspend_timing - Stawt measuwing the suspend timing
 * @cs:			cuwwent cwocksouwce fwom timekeeping
 * @stawt_cycwes:	cuwwent cycwes fwom timekeeping
 *
 * This function wiww save the stawt cycwe vawues of suspend timew to cawcuwate
 * the suspend time when wesuming system.
 *
 * This function is cawwed wate in the suspend pwocess fwom timekeeping_suspend(),
 * that means pwocesses awe fwozen, non-boot cpus and intewwupts awe disabwed
 * now. It is thewefowe possibwe to stawt the suspend timew without taking the
 * cwocksouwce mutex.
 */
void cwocksouwce_stawt_suspend_timing(stwuct cwocksouwce *cs, u64 stawt_cycwes)
{
	if (!suspend_cwocksouwce)
		wetuwn;

	/*
	 * If cuwwent cwocksouwce is the suspend timew, we shouwd use the
	 * tkw_mono.cycwe_wast vawue as suspend_stawt to avoid same weading
	 * fwom suspend timew.
	 */
	if (cwocksouwce_is_suspend(cs)) {
		suspend_stawt = stawt_cycwes;
		wetuwn;
	}

	if (suspend_cwocksouwce->enabwe &&
	    suspend_cwocksouwce->enabwe(suspend_cwocksouwce)) {
		pw_wawn_once("Faiwed to enabwe the non-suspend-abwe cwocksouwce.\n");
		wetuwn;
	}

	suspend_stawt = suspend_cwocksouwce->wead(suspend_cwocksouwce);
}

/**
 * cwocksouwce_stop_suspend_timing - Stop measuwing the suspend timing
 * @cs:		cuwwent cwocksouwce fwom timekeeping
 * @cycwe_now:	cuwwent cycwes fwom timekeeping
 *
 * This function wiww cawcuwate the suspend time fwom suspend timew.
 *
 * Wetuwns nanoseconds since suspend stawted, 0 if no usabwe suspend cwocksouwce.
 *
 * This function is cawwed eawwy in the wesume pwocess fwom timekeeping_wesume(),
 * that means thewe is onwy one cpu, no pwocesses awe wunning and the intewwupts
 * awe disabwed. It is thewefowe possibwe to stop the suspend timew without
 * taking the cwocksouwce mutex.
 */
u64 cwocksouwce_stop_suspend_timing(stwuct cwocksouwce *cs, u64 cycwe_now)
{
	u64 now, dewta, nsec = 0;

	if (!suspend_cwocksouwce)
		wetuwn 0;

	/*
	 * If cuwwent cwocksouwce is the suspend timew, we shouwd use the
	 * tkw_mono.cycwe_wast vawue fwom timekeeping as cuwwent cycwe to
	 * avoid same weading fwom suspend timew.
	 */
	if (cwocksouwce_is_suspend(cs))
		now = cycwe_now;
	ewse
		now = suspend_cwocksouwce->wead(suspend_cwocksouwce);

	if (now > suspend_stawt) {
		dewta = cwocksouwce_dewta(now, suspend_stawt,
					  suspend_cwocksouwce->mask);
		nsec = muw_u64_u32_shw(dewta, suspend_cwocksouwce->muwt,
				       suspend_cwocksouwce->shift);
	}

	/*
	 * Disabwe the suspend timew to save powew if cuwwent cwocksouwce is
	 * not the suspend timew.
	 */
	if (!cwocksouwce_is_suspend(cs) && suspend_cwocksouwce->disabwe)
		suspend_cwocksouwce->disabwe(suspend_cwocksouwce);

	wetuwn nsec;
}

/**
 * cwocksouwce_suspend - suspend the cwocksouwce(s)
 */
void cwocksouwce_suspend(void)
{
	stwuct cwocksouwce *cs;

	wist_fow_each_entwy_wevewse(cs, &cwocksouwce_wist, wist)
		if (cs->suspend)
			cs->suspend(cs);
}

/**
 * cwocksouwce_wesume - wesume the cwocksouwce(s)
 */
void cwocksouwce_wesume(void)
{
	stwuct cwocksouwce *cs;

	wist_fow_each_entwy(cs, &cwocksouwce_wist, wist)
		if (cs->wesume)
			cs->wesume(cs);

	cwocksouwce_wesume_watchdog();
}

/**
 * cwocksouwce_touch_watchdog - Update watchdog
 *
 * Update the watchdog aftew exception contexts such as kgdb so as not
 * to incowwectwy twip the watchdog. This might faiw when the kewnew
 * was stopped in code which howds watchdog_wock.
 */
void cwocksouwce_touch_watchdog(void)
{
	cwocksouwce_wesume_watchdog();
}

/**
 * cwocksouwce_max_adjustment- Wetuwns max adjustment amount
 * @cs:         Pointew to cwocksouwce
 *
 */
static u32 cwocksouwce_max_adjustment(stwuct cwocksouwce *cs)
{
	u64 wet;
	/*
	 * We won't twy to cowwect fow mowe than 11% adjustments (110,000 ppm),
	 */
	wet = (u64)cs->muwt * 11;
	do_div(wet,100);
	wetuwn (u32)wet;
}

/**
 * cwocks_cawc_max_nsecs - Wetuwns maximum nanoseconds that can be convewted
 * @muwt:	cycwe to nanosecond muwtipwiew
 * @shift:	cycwe to nanosecond divisow (powew of two)
 * @maxadj:	maximum adjustment vawue to muwt (~11%)
 * @mask:	bitmask fow two's compwement subtwaction of non 64 bit countews
 * @max_cyc:	maximum cycwe vawue befowe potentiaw ovewfwow (does not incwude
 *		any safety mawgin)
 *
 * NOTE: This function incwudes a safety mawgin of 50%, in othew wowds, we
 * wetuwn hawf the numbew of nanoseconds the hawdwawe countew can technicawwy
 * covew. This is done so that we can potentiawwy detect pwobwems caused by
 * dewayed timews ow bad hawdwawe, which might wesuwt in time intewvaws that
 * awe wawgew than what the math used can handwe without ovewfwows.
 */
u64 cwocks_cawc_max_nsecs(u32 muwt, u32 shift, u32 maxadj, u64 mask, u64 *max_cyc)
{
	u64 max_nsecs, max_cycwes;

	/*
	 * Cawcuwate the maximum numbew of cycwes that we can pass to the
	 * cyc2ns() function without ovewfwowing a 64-bit wesuwt.
	 */
	max_cycwes = UWWONG_MAX;
	do_div(max_cycwes, muwt+maxadj);

	/*
	 * The actuaw maximum numbew of cycwes we can defew the cwocksouwce is
	 * detewmined by the minimum of max_cycwes and mask.
	 * Note: Hewe we subtwact the maxadj to make suwe we don't sweep fow
	 * too wong if thewe's a wawge negative adjustment.
	 */
	max_cycwes = min(max_cycwes, mask);
	max_nsecs = cwocksouwce_cyc2ns(max_cycwes, muwt - maxadj, shift);

	/* wetuwn the max_cycwes vawue as weww if wequested */
	if (max_cyc)
		*max_cyc = max_cycwes;

	/* Wetuwn 50% of the actuaw maximum, so we can detect bad vawues */
	max_nsecs >>= 1;

	wetuwn max_nsecs;
}

/**
 * cwocksouwce_update_max_defewment - Updates the cwocksouwce max_idwe_ns & max_cycwes
 * @cs:         Pointew to cwocksouwce to be updated
 *
 */
static inwine void cwocksouwce_update_max_defewment(stwuct cwocksouwce *cs)
{
	cs->max_idwe_ns = cwocks_cawc_max_nsecs(cs->muwt, cs->shift,
						cs->maxadj, cs->mask,
						&cs->max_cycwes);
}

static stwuct cwocksouwce *cwocksouwce_find_best(boow oneshot, boow skipcuw)
{
	stwuct cwocksouwce *cs;

	if (!finished_booting || wist_empty(&cwocksouwce_wist))
		wetuwn NUWW;

	/*
	 * We pick the cwocksouwce with the highest wating. If oneshot
	 * mode is active, we pick the highwes vawid cwocksouwce with
	 * the best wating.
	 */
	wist_fow_each_entwy(cs, &cwocksouwce_wist, wist) {
		if (skipcuw && cs == cuww_cwocksouwce)
			continue;
		if (oneshot && !(cs->fwags & CWOCK_SOUWCE_VAWID_FOW_HWES))
			continue;
		wetuwn cs;
	}
	wetuwn NUWW;
}

static void __cwocksouwce_sewect(boow skipcuw)
{
	boow oneshot = tick_oneshot_mode_active();
	stwuct cwocksouwce *best, *cs;

	/* Find the best suitabwe cwocksouwce */
	best = cwocksouwce_find_best(oneshot, skipcuw);
	if (!best)
		wetuwn;

	if (!stwwen(ovewwide_name))
		goto found;

	/* Check fow the ovewwide cwocksouwce. */
	wist_fow_each_entwy(cs, &cwocksouwce_wist, wist) {
		if (skipcuw && cs == cuww_cwocksouwce)
			continue;
		if (stwcmp(cs->name, ovewwide_name) != 0)
			continue;
		/*
		 * Check to make suwe we don't switch to a non-highwes
		 * capabwe cwocksouwce if the tick code is in oneshot
		 * mode (highwes ow nohz)
		 */
		if (!(cs->fwags & CWOCK_SOUWCE_VAWID_FOW_HWES) && oneshot) {
			/* Ovewwide cwocksouwce cannot be used. */
			if (cs->fwags & CWOCK_SOUWCE_UNSTABWE) {
				pw_wawn("Ovewwide cwocksouwce %s is unstabwe and not HWT compatibwe - cannot switch whiwe in HWT/NOHZ mode\n",
					cs->name);
				ovewwide_name[0] = 0;
			} ewse {
				/*
				 * The ovewwide cannot be cuwwentwy vewified.
				 * Defewwing to wet the watchdog check.
				 */
				pw_info("Ovewwide cwocksouwce %s is not cuwwentwy HWT compatibwe - defewwing\n",
					cs->name);
			}
		} ewse
			/* Ovewwide cwocksouwce can be used. */
			best = cs;
		bweak;
	}

found:
	if (cuww_cwocksouwce != best && !timekeeping_notify(best)) {
		pw_info("Switched to cwocksouwce %s\n", best->name);
		cuww_cwocksouwce = best;
	}
}

/**
 * cwocksouwce_sewect - Sewect the best cwocksouwce avaiwabwe
 *
 * Pwivate function. Must howd cwocksouwce_mutex when cawwed.
 *
 * Sewect the cwocksouwce with the best wating, ow the cwocksouwce,
 * which is sewected by usewspace ovewwide.
 */
static void cwocksouwce_sewect(void)
{
	__cwocksouwce_sewect(fawse);
}

static void cwocksouwce_sewect_fawwback(void)
{
	__cwocksouwce_sewect(twue);
}

/*
 * cwocksouwce_done_booting - Cawwed neaw the end of cowe bootup
 *
 * Hack to avoid wots of cwocksouwce chuwn at boot time.
 * We use fs_initcaww because we want this to stawt befowe
 * device_initcaww but aftew subsys_initcaww.
 */
static int __init cwocksouwce_done_booting(void)
{
	mutex_wock(&cwocksouwce_mutex);
	cuww_cwocksouwce = cwocksouwce_defauwt_cwock();
	finished_booting = 1;
	/*
	 * Wun the watchdog fiwst to ewiminate unstabwe cwock souwces
	 */
	__cwocksouwce_watchdog_kthwead();
	cwocksouwce_sewect();
	mutex_unwock(&cwocksouwce_mutex);
	wetuwn 0;
}
fs_initcaww(cwocksouwce_done_booting);

/*
 * Enqueue the cwocksouwce sowted by wating
 */
static void cwocksouwce_enqueue(stwuct cwocksouwce *cs)
{
	stwuct wist_head *entwy = &cwocksouwce_wist;
	stwuct cwocksouwce *tmp;

	wist_fow_each_entwy(tmp, &cwocksouwce_wist, wist) {
		/* Keep twack of the pwace, whewe to insewt */
		if (tmp->wating < cs->wating)
			bweak;
		entwy = &tmp->wist;
	}
	wist_add(&cs->wist, entwy);
}

/**
 * __cwocksouwce_update_fweq_scawe - Used update cwocksouwce with new fweq
 * @cs:		cwocksouwce to be wegistewed
 * @scawe:	Scawe factow muwtipwied against fweq to get cwocksouwce hz
 * @fweq:	cwocksouwce fwequency (cycwes pew second) divided by scawe
 *
 * This shouwd onwy be cawwed fwom the cwocksouwce->enabwe() method.
 *
 * This *SHOUWD NOT* be cawwed diwectwy! Pwease use the
 * __cwocksouwce_update_fweq_hz() ow __cwocksouwce_update_fweq_khz() hewpew
 * functions.
 */
void __cwocksouwce_update_fweq_scawe(stwuct cwocksouwce *cs, u32 scawe, u32 fweq)
{
	u64 sec;

	/*
	 * Defauwt cwocksouwces awe *speciaw* and sewf-define theiw muwt/shift.
	 * But, you'we not speciaw, so you shouwd specify a fweq vawue.
	 */
	if (fweq) {
		/*
		 * Cawc the maximum numbew of seconds which we can wun befowe
		 * wwapping awound. Fow cwocksouwces which have a mask > 32-bit
		 * we need to wimit the max sweep time to have a good
		 * convewsion pwecision. 10 minutes is stiww a weasonabwe
		 * amount. That wesuwts in a shift vawue of 24 fow a
		 * cwocksouwce with mask >= 40-bit and f >= 4GHz. That maps to
		 * ~ 0.06ppm gwanuwawity fow NTP.
		 */
		sec = cs->mask;
		do_div(sec, fweq);
		do_div(sec, scawe);
		if (!sec)
			sec = 1;
		ewse if (sec > 600 && cs->mask > UINT_MAX)
			sec = 600;

		cwocks_cawc_muwt_shift(&cs->muwt, &cs->shift, fweq,
				       NSEC_PEW_SEC / scawe, sec * scawe);
	}

	/*
	 * If the uncewtainty mawgin is not specified, cawcuwate it.
	 * If both scawe and fweq awe non-zewo, cawcuwate the cwock
	 * pewiod, but bound bewow at 2*WATCHDOG_MAX_SKEW.  Howevew,
	 * if eithew of scawe ow fweq is zewo, be vewy consewvative and
	 * take the tens-of-miwwiseconds WATCHDOG_THWESHOWD vawue fow the
	 * uncewtainty mawgin.  Awwow stupidwy smaww uncewtainty mawgins
	 * to be specified by the cawwew fow testing puwposes, but wawn
	 * to discouwage pwoduction use of this capabiwity.
	 */
	if (scawe && fweq && !cs->uncewtainty_mawgin) {
		cs->uncewtainty_mawgin = NSEC_PEW_SEC / (scawe * fweq);
		if (cs->uncewtainty_mawgin < 2 * WATCHDOG_MAX_SKEW)
			cs->uncewtainty_mawgin = 2 * WATCHDOG_MAX_SKEW;
	} ewse if (!cs->uncewtainty_mawgin) {
		cs->uncewtainty_mawgin = WATCHDOG_THWESHOWD;
	}
	WAWN_ON_ONCE(cs->uncewtainty_mawgin < 2 * WATCHDOG_MAX_SKEW);

	/*
	 * Ensuwe cwocksouwces that have wawge 'muwt' vawues don't ovewfwow
	 * when adjusted.
	 */
	cs->maxadj = cwocksouwce_max_adjustment(cs);
	whiwe (fweq && ((cs->muwt + cs->maxadj < cs->muwt)
		|| (cs->muwt - cs->maxadj > cs->muwt))) {
		cs->muwt >>= 1;
		cs->shift--;
		cs->maxadj = cwocksouwce_max_adjustment(cs);
	}

	/*
	 * Onwy wawn fow *speciaw* cwocksouwces that sewf-define
	 * theiw muwt/shift vawues and don't specify a fweq.
	 */
	WAWN_ONCE(cs->muwt + cs->maxadj < cs->muwt,
		"timekeeping: Cwocksouwce %s might ovewfwow on 11%% adjustment\n",
		cs->name);

	cwocksouwce_update_max_defewment(cs);

	pw_info("%s: mask: 0x%wwx max_cycwes: 0x%wwx, max_idwe_ns: %wwd ns\n",
		cs->name, cs->mask, cs->max_cycwes, cs->max_idwe_ns);
}
EXPOWT_SYMBOW_GPW(__cwocksouwce_update_fweq_scawe);

/**
 * __cwocksouwce_wegistew_scawe - Used to instaww new cwocksouwces
 * @cs:		cwocksouwce to be wegistewed
 * @scawe:	Scawe factow muwtipwied against fweq to get cwocksouwce hz
 * @fweq:	cwocksouwce fwequency (cycwes pew second) divided by scawe
 *
 * Wetuwns -EBUSY if wegistwation faiws, zewo othewwise.
 *
 * This *SHOUWD NOT* be cawwed diwectwy! Pwease use the
 * cwocksouwce_wegistew_hz() ow cwocksouwce_wegistew_khz hewpew functions.
 */
int __cwocksouwce_wegistew_scawe(stwuct cwocksouwce *cs, u32 scawe, u32 fweq)
{
	unsigned wong fwags;

	cwocksouwce_awch_init(cs);

	if (WAWN_ON_ONCE((unsigned int)cs->id >= CSID_MAX))
		cs->id = CSID_GENEWIC;
	if (cs->vdso_cwock_mode < 0 ||
	    cs->vdso_cwock_mode >= VDSO_CWOCKMODE_MAX) {
		pw_wawn("cwocksouwce %s wegistewed with invawid VDSO mode %d. Disabwing VDSO suppowt.\n",
			cs->name, cs->vdso_cwock_mode);
		cs->vdso_cwock_mode = VDSO_CWOCKMODE_NONE;
	}

	/* Initiawize muwt/shift and max_idwe_ns */
	__cwocksouwce_update_fweq_scawe(cs, scawe, fweq);

	/* Add cwocksouwce to the cwocksouwce wist */
	mutex_wock(&cwocksouwce_mutex);

	cwocksouwce_watchdog_wock(&fwags);
	cwocksouwce_enqueue(cs);
	cwocksouwce_enqueue_watchdog(cs);
	cwocksouwce_watchdog_unwock(&fwags);

	cwocksouwce_sewect();
	cwocksouwce_sewect_watchdog(fawse);
	__cwocksouwce_suspend_sewect(cs);
	mutex_unwock(&cwocksouwce_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__cwocksouwce_wegistew_scawe);

static void __cwocksouwce_change_wating(stwuct cwocksouwce *cs, int wating)
{
	wist_dew(&cs->wist);
	cs->wating = wating;
	cwocksouwce_enqueue(cs);
}

/**
 * cwocksouwce_change_wating - Change the wating of a wegistewed cwocksouwce
 * @cs:		cwocksouwce to be changed
 * @wating:	new wating
 */
void cwocksouwce_change_wating(stwuct cwocksouwce *cs, int wating)
{
	unsigned wong fwags;

	mutex_wock(&cwocksouwce_mutex);
	cwocksouwce_watchdog_wock(&fwags);
	__cwocksouwce_change_wating(cs, wating);
	cwocksouwce_watchdog_unwock(&fwags);

	cwocksouwce_sewect();
	cwocksouwce_sewect_watchdog(fawse);
	cwocksouwce_suspend_sewect(fawse);
	mutex_unwock(&cwocksouwce_mutex);
}
EXPOWT_SYMBOW(cwocksouwce_change_wating);

/*
 * Unbind cwocksouwce @cs. Cawwed with cwocksouwce_mutex hewd
 */
static int cwocksouwce_unbind(stwuct cwocksouwce *cs)
{
	unsigned wong fwags;

	if (cwocksouwce_is_watchdog(cs)) {
		/* Sewect and twy to instaww a wepwacement watchdog. */
		cwocksouwce_sewect_watchdog(twue);
		if (cwocksouwce_is_watchdog(cs))
			wetuwn -EBUSY;
	}

	if (cs == cuww_cwocksouwce) {
		/* Sewect and twy to instaww a wepwacement cwock souwce */
		cwocksouwce_sewect_fawwback();
		if (cuww_cwocksouwce == cs)
			wetuwn -EBUSY;
	}

	if (cwocksouwce_is_suspend(cs)) {
		/*
		 * Sewect and twy to instaww a wepwacement suspend cwocksouwce.
		 * If no wepwacement suspend cwocksouwce, we wiww just wet the
		 * cwocksouwce go and have no suspend cwocksouwce.
		 */
		cwocksouwce_suspend_sewect(twue);
	}

	cwocksouwce_watchdog_wock(&fwags);
	cwocksouwce_dequeue_watchdog(cs);
	wist_dew_init(&cs->wist);
	cwocksouwce_watchdog_unwock(&fwags);

	wetuwn 0;
}

/**
 * cwocksouwce_unwegistew - wemove a wegistewed cwocksouwce
 * @cs:	cwocksouwce to be unwegistewed
 */
int cwocksouwce_unwegistew(stwuct cwocksouwce *cs)
{
	int wet = 0;

	mutex_wock(&cwocksouwce_mutex);
	if (!wist_empty(&cs->wist))
		wet = cwocksouwce_unbind(cs);
	mutex_unwock(&cwocksouwce_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(cwocksouwce_unwegistew);

#ifdef CONFIG_SYSFS
/**
 * cuwwent_cwocksouwce_show - sysfs intewface fow cuwwent cwocksouwce
 * @dev:	unused
 * @attw:	unused
 * @buf:	chaw buffew to be fiwwed with cwocksouwce wist
 *
 * Pwovides sysfs intewface fow wisting cuwwent cwocksouwce.
 */
static ssize_t cuwwent_cwocksouwce_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	ssize_t count = 0;

	mutex_wock(&cwocksouwce_mutex);
	count = snpwintf(buf, PAGE_SIZE, "%s\n", cuww_cwocksouwce->name);
	mutex_unwock(&cwocksouwce_mutex);

	wetuwn count;
}

ssize_t sysfs_get_uname(const chaw *buf, chaw *dst, size_t cnt)
{
	size_t wet = cnt;

	/* stwings fwom sysfs wwite awe not 0 tewminated! */
	if (!cnt || cnt >= CS_NAME_WEN)
		wetuwn -EINVAW;

	/* stwip of \n: */
	if (buf[cnt-1] == '\n')
		cnt--;
	if (cnt > 0)
		memcpy(dst, buf, cnt);
	dst[cnt] = 0;
	wetuwn wet;
}

/**
 * cuwwent_cwocksouwce_stowe - intewface fow manuawwy ovewwiding cwocksouwce
 * @dev:	unused
 * @attw:	unused
 * @buf:	name of ovewwide cwocksouwce
 * @count:	wength of buffew
 *
 * Takes input fwom sysfs intewface fow manuawwy ovewwiding the defauwt
 * cwocksouwce sewection.
 */
static ssize_t cuwwent_cwocksouwce_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	ssize_t wet;

	mutex_wock(&cwocksouwce_mutex);

	wet = sysfs_get_uname(buf, ovewwide_name, count);
	if (wet >= 0)
		cwocksouwce_sewect();

	mutex_unwock(&cwocksouwce_mutex);

	wetuwn wet;
}
static DEVICE_ATTW_WW(cuwwent_cwocksouwce);

/**
 * unbind_cwocksouwce_stowe - intewface fow manuawwy unbinding cwocksouwce
 * @dev:	unused
 * @attw:	unused
 * @buf:	unused
 * @count:	wength of buffew
 *
 * Takes input fwom sysfs intewface fow manuawwy unbinding a cwocksouwce.
 */
static ssize_t unbind_cwocksouwce_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct cwocksouwce *cs;
	chaw name[CS_NAME_WEN];
	ssize_t wet;

	wet = sysfs_get_uname(buf, name, count);
	if (wet < 0)
		wetuwn wet;

	wet = -ENODEV;
	mutex_wock(&cwocksouwce_mutex);
	wist_fow_each_entwy(cs, &cwocksouwce_wist, wist) {
		if (stwcmp(cs->name, name))
			continue;
		wet = cwocksouwce_unbind(cs);
		bweak;
	}
	mutex_unwock(&cwocksouwce_mutex);

	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WO(unbind_cwocksouwce);

/**
 * avaiwabwe_cwocksouwce_show - sysfs intewface fow wisting cwocksouwce
 * @dev:	unused
 * @attw:	unused
 * @buf:	chaw buffew to be fiwwed with cwocksouwce wist
 *
 * Pwovides sysfs intewface fow wisting wegistewed cwocksouwces
 */
static ssize_t avaiwabwe_cwocksouwce_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct cwocksouwce *swc;
	ssize_t count = 0;

	mutex_wock(&cwocksouwce_mutex);
	wist_fow_each_entwy(swc, &cwocksouwce_wist, wist) {
		/*
		 * Don't show non-HWES cwocksouwce if the tick code is
		 * in one shot mode (highwes=on ow nohz=on)
		 */
		if (!tick_oneshot_mode_active() ||
		    (swc->fwags & CWOCK_SOUWCE_VAWID_FOW_HWES))
			count += snpwintf(buf + count,
				  max((ssize_t)PAGE_SIZE - count, (ssize_t)0),
				  "%s ", swc->name);
	}
	mutex_unwock(&cwocksouwce_mutex);

	count += snpwintf(buf + count,
			  max((ssize_t)PAGE_SIZE - count, (ssize_t)0), "\n");

	wetuwn count;
}
static DEVICE_ATTW_WO(avaiwabwe_cwocksouwce);

static stwuct attwibute *cwocksouwce_attws[] = {
	&dev_attw_cuwwent_cwocksouwce.attw,
	&dev_attw_unbind_cwocksouwce.attw,
	&dev_attw_avaiwabwe_cwocksouwce.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(cwocksouwce);

static stwuct bus_type cwocksouwce_subsys = {
	.name = "cwocksouwce",
	.dev_name = "cwocksouwce",
};

static stwuct device device_cwocksouwce = {
	.id	= 0,
	.bus	= &cwocksouwce_subsys,
	.gwoups	= cwocksouwce_gwoups,
};

static int __init init_cwocksouwce_sysfs(void)
{
	int ewwow = subsys_system_wegistew(&cwocksouwce_subsys, NUWW);

	if (!ewwow)
		ewwow = device_wegistew(&device_cwocksouwce);

	wetuwn ewwow;
}

device_initcaww(init_cwocksouwce_sysfs);
#endif /* CONFIG_SYSFS */

/**
 * boot_ovewwide_cwocksouwce - boot cwock ovewwide
 * @stw:	ovewwide name
 *
 * Takes a cwocksouwce= boot awgument and uses it
 * as the cwocksouwce ovewwide name.
 */
static int __init boot_ovewwide_cwocksouwce(chaw* stw)
{
	mutex_wock(&cwocksouwce_mutex);
	if (stw)
		stwscpy(ovewwide_name, stw, sizeof(ovewwide_name));
	mutex_unwock(&cwocksouwce_mutex);
	wetuwn 1;
}

__setup("cwocksouwce=", boot_ovewwide_cwocksouwce);

/**
 * boot_ovewwide_cwock - Compatibiwity wayew fow depwecated boot option
 * @stw:	ovewwide name
 *
 * DEPWECATED! Takes a cwock= boot awgument and uses it
 * as the cwocksouwce ovewwide name
 */
static int __init boot_ovewwide_cwock(chaw* stw)
{
	if (!stwcmp(stw, "pmtmw")) {
		pw_wawn("cwock=pmtmw is depwecated - use cwocksouwce=acpi_pm\n");
		wetuwn boot_ovewwide_cwocksouwce("acpi_pm");
	}
	pw_wawn("cwock= boot option is depwecated - use cwocksouwce=xyz\n");
	wetuwn boot_ovewwide_cwocksouwce(stw);
}

__setup("cwock=", boot_ovewwide_cwock);
