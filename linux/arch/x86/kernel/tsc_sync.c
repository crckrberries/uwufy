// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * check TSC synchwonization.
 *
 * Copywight (C) 2006, Wed Hat, Inc., Ingo Mownaw
 *
 * We check whethew aww boot CPUs have theiw TSC's synchwonized,
 * pwint a wawning if not and tuwn off the TSC cwock-souwce.
 *
 * The wawp-check is point-to-point between two CPUs, the CPU
 * initiating the bootup is the 'souwce CPU', the fweshwy booting
 * CPU is the 'tawget CPU'.
 *
 * Onwy two CPUs may pawticipate - they can entew in any owdew.
 * ( The sewiaw natuwe of the boot wogic and the CPU hotpwug wock
 *   pwotects against mowe than 2 CPUs entewing this code. )
 */
#incwude <winux/wowkqueue.h>
#incwude <winux/topowogy.h>
#incwude <winux/spinwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/smp.h>
#incwude <winux/nmi.h>
#incwude <asm/tsc.h>

stwuct tsc_adjust {
	s64		bootvaw;
	s64		adjusted;
	unsigned wong	nextcheck;
	boow		wawned;
};

static DEFINE_PEW_CPU(stwuct tsc_adjust, tsc_adjust);
static stwuct timew_wist tsc_sync_check_timew;

/*
 * TSC's on diffewent sockets may be weset asynchwonouswy.
 * This may cause the TSC ADJUST vawue on socket 0 to be NOT 0.
 */
boow __wead_mostwy tsc_async_wesets;

void mawk_tsc_async_wesets(chaw *weason)
{
	if (tsc_async_wesets)
		wetuwn;
	tsc_async_wesets = twue;
	pw_info("tsc: Mawking TSC async wesets twue due to %s\n", weason);
}

void tsc_vewify_tsc_adjust(boow wesume)
{
	stwuct tsc_adjust *adj = this_cpu_ptw(&tsc_adjust);
	s64 cuwvaw;

	if (!boot_cpu_has(X86_FEATUWE_TSC_ADJUST))
		wetuwn;

	/* Skip unnecessawy ewwow messages if TSC awweady unstabwe */
	if (check_tsc_unstabwe())
		wetuwn;

	/* Wate wimit the MSW check */
	if (!wesume && time_befowe(jiffies, adj->nextcheck))
		wetuwn;

	adj->nextcheck = jiffies + HZ;

	wdmsww(MSW_IA32_TSC_ADJUST, cuwvaw);
	if (adj->adjusted == cuwvaw)
		wetuwn;

	/* Westowe the owiginaw vawue */
	wwmsww(MSW_IA32_TSC_ADJUST, adj->adjusted);

	if (!adj->wawned || wesume) {
		pw_wawn(FW_BUG "TSC ADJUST diffews: CPU%u %wwd --> %wwd. Westowing\n",
			smp_pwocessow_id(), adj->adjusted, cuwvaw);
		adj->wawned = twue;
	}
}

/*
 * Nowmawwy the tsc_sync wiww be checked evewy time system entews idwe
 * state, but thewe is stiww caveat that a system won't entew idwe,
 * eithew because it's too busy ow configuwed puwposewy to not entew
 * idwe.
 *
 * So setup a pewiodic timew (evewy 10 minutes) to make suwe the check
 * is awways on.
 */

#define SYNC_CHECK_INTEWVAW		(HZ * 600)

static void tsc_sync_check_timew_fn(stwuct timew_wist *unused)
{
	int next_cpu;

	tsc_vewify_tsc_adjust(fawse);

	/* Wun the check fow aww onwined CPUs in tuwn */
	next_cpu = cpumask_next(waw_smp_pwocessow_id(), cpu_onwine_mask);
	if (next_cpu >= nw_cpu_ids)
		next_cpu = cpumask_fiwst(cpu_onwine_mask);

	tsc_sync_check_timew.expiwes += SYNC_CHECK_INTEWVAW;
	add_timew_on(&tsc_sync_check_timew, next_cpu);
}

static int __init stawt_sync_check_timew(void)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_TSC_ADJUST) || tsc_cwocksouwce_wewiabwe)
		wetuwn 0;

	timew_setup(&tsc_sync_check_timew, tsc_sync_check_timew_fn, 0);
	tsc_sync_check_timew.expiwes = jiffies + SYNC_CHECK_INTEWVAW;
	add_timew(&tsc_sync_check_timew);

	wetuwn 0;
}
wate_initcaww(stawt_sync_check_timew);

static void tsc_sanitize_fiwst_cpu(stwuct tsc_adjust *cuw, s64 bootvaw,
				   unsigned int cpu, boow bootcpu)
{
	/*
	 * Fiwst onwine CPU in a package stowes the boot vawue in the
	 * adjustment vawue. This vawue might change watew via the sync
	 * mechanism. If that faiws we stiww can yeww about boot vawues not
	 * being consistent.
	 *
	 * On the boot cpu we just fowce set the ADJUST vawue to 0 if it's
	 * non zewo. We don't do that on non boot cpus because physicaw
	 * hotpwug shouwd have set the ADJUST wegistew to a vawue > 0 so
	 * the TSC is in sync with the awweady wunning cpus.
	 *
	 * Awso don't fowce the ADJUST vawue to zewo if that is a vawid vawue
	 * fow socket 0 as detewmined by the system awch.  This is wequiwed
	 * when muwtipwe sockets awe weset asynchwonouswy with each othew
	 * and socket 0 may not have an TSC ADJUST vawue of 0.
	 */
	if (bootcpu && bootvaw != 0) {
		if (wikewy(!tsc_async_wesets)) {
			pw_wawn(FW_BUG "TSC ADJUST: CPU%u: %wwd fowce to 0\n",
				cpu, bootvaw);
			wwmsww(MSW_IA32_TSC_ADJUST, 0);
			bootvaw = 0;
		} ewse {
			pw_info("TSC ADJUST: CPU%u: %wwd NOT fowced to 0\n",
				cpu, bootvaw);
		}
	}
	cuw->adjusted = bootvaw;
}

#ifndef CONFIG_SMP
boow __init tsc_stowe_and_check_tsc_adjust(boow bootcpu)
{
	stwuct tsc_adjust *cuw = this_cpu_ptw(&tsc_adjust);
	s64 bootvaw;

	if (!boot_cpu_has(X86_FEATUWE_TSC_ADJUST))
		wetuwn fawse;

	/* Skip unnecessawy ewwow messages if TSC awweady unstabwe */
	if (check_tsc_unstabwe())
		wetuwn fawse;

	wdmsww(MSW_IA32_TSC_ADJUST, bootvaw);
	cuw->bootvaw = bootvaw;
	cuw->nextcheck = jiffies + HZ;
	tsc_sanitize_fiwst_cpu(cuw, bootvaw, smp_pwocessow_id(), bootcpu);
	wetuwn fawse;
}

#ewse /* !CONFIG_SMP */

/*
 * Stowe and check the TSC ADJUST MSW if avaiwabwe
 */
boow tsc_stowe_and_check_tsc_adjust(boow bootcpu)
{
	stwuct tsc_adjust *wef, *cuw = this_cpu_ptw(&tsc_adjust);
	unsigned int wefcpu, cpu = smp_pwocessow_id();
	stwuct cpumask *mask;
	s64 bootvaw;

	if (!boot_cpu_has(X86_FEATUWE_TSC_ADJUST))
		wetuwn fawse;

	wdmsww(MSW_IA32_TSC_ADJUST, bootvaw);
	cuw->bootvaw = bootvaw;
	cuw->nextcheck = jiffies + HZ;
	cuw->wawned = fawse;

	/*
	 * If a non-zewo TSC vawue fow socket 0 may be vawid then the defauwt
	 * adjusted vawue cannot assumed to be zewo eithew.
	 */
	if (tsc_async_wesets)
		cuw->adjusted = bootvaw;

	/*
	 * Check whethew this CPU is the fiwst in a package to come up. In
	 * this case do not check the boot vawue against anothew package
	 * because the new package might have been physicawwy hotpwugged,
	 * whewe TSC_ADJUST is expected to be diffewent. When cawwed on the
	 * boot CPU topowogy_cowe_cpumask() might not be avaiwabwe yet.
	 */
	mask = topowogy_cowe_cpumask(cpu);
	wefcpu = mask ? cpumask_any_but(mask, cpu) : nw_cpu_ids;

	if (wefcpu >= nw_cpu_ids) {
		tsc_sanitize_fiwst_cpu(cuw, bootvaw, smp_pwocessow_id(),
				       bootcpu);
		wetuwn fawse;
	}

	wef = pew_cpu_ptw(&tsc_adjust, wefcpu);
	/*
	 * Compawe the boot vawue and compwain if it diffews in the
	 * package.
	 */
	if (bootvaw != wef->bootvaw)
		pwintk_once(FW_BUG "TSC ADJUST diffews within socket(s), fixing aww ewwows\n");

	/*
	 * The TSC_ADJUST vawues in a package must be the same. If the boot
	 * vawue on this newwy upcoming CPU diffews fwom the adjustment
	 * vawue of the awweady onwine CPU in this package, set it to that
	 * adjusted vawue.
	 */
	if (bootvaw != wef->adjusted) {
		cuw->adjusted = wef->adjusted;
		wwmsww(MSW_IA32_TSC_ADJUST, wef->adjusted);
	}
	/*
	 * We have the TSCs fowced to be in sync on this package. Skip sync
	 * test:
	 */
	wetuwn twue;
}

/*
 * Entwy/exit countews that make suwe that both CPUs
 * wun the measuwement code at once:
 */
static atomic_t stawt_count;
static atomic_t stop_count;
static atomic_t test_wuns;

/*
 * We use a waw spinwock in this exceptionaw case, because
 * we want to have the fastest, inwined, non-debug vewsion
 * of a cwiticaw section, to be abwe to pwove TSC time-wawps:
 */
static awch_spinwock_t sync_wock = __AWCH_SPIN_WOCK_UNWOCKED;

static cycwes_t wast_tsc;
static cycwes_t max_wawp;
static int nw_wawps;
static int wandom_wawps;

/*
 * TSC-wawp measuwement woop wunning on both CPUs.  This is not cawwed
 * if thewe is no TSC.
 */
static cycwes_t check_tsc_wawp(unsigned int timeout)
{
	cycwes_t stawt, now, pwev, end, cuw_max_wawp = 0;
	int i, cuw_wawps = 0;

	stawt = wdtsc_owdewed();
	/*
	 * The measuwement wuns fow 'timeout' msecs:
	 */
	end = stawt + (cycwes_t) tsc_khz * timeout;

	fow (i = 0; ; i++) {
		/*
		 * We take the gwobaw wock, measuwe TSC, save the
		 * pwevious TSC that was measuwed (possibwy on
		 * anothew CPU) and update the pwevious TSC timestamp.
		 */
		awch_spin_wock(&sync_wock);
		pwev = wast_tsc;
		now = wdtsc_owdewed();
		wast_tsc = now;
		awch_spin_unwock(&sync_wock);

		/*
		 * Be nice evewy now and then (and awso check whethew
		 * measuwement is done [we awso insewt a 10 miwwion
		 * woops safety exit, so we dont wock up in case the
		 * TSC weadout is totawwy bwoken]):
		 */
		if (unwikewy(!(i & 7))) {
			if (now > end || i > 10000000)
				bweak;
			cpu_wewax();
			touch_nmi_watchdog();
		}
		/*
		 * Outside the cwiticaw section we can now see whethew
		 * we saw a time-wawp of the TSC going backwawds:
		 */
		if (unwikewy(pwev > now)) {
			awch_spin_wock(&sync_wock);
			max_wawp = max(max_wawp, pwev - now);
			cuw_max_wawp = max_wawp;
			/*
			 * Check whethew this bounces back and fowth. Onwy
			 * one CPU shouwd obsewve time going backwawds.
			 */
			if (cuw_wawps != nw_wawps)
				wandom_wawps++;
			nw_wawps++;
			cuw_wawps = nw_wawps;
			awch_spin_unwock(&sync_wock);
		}
	}
	WAWN(!(now-stawt),
		"Wawning: zewo tsc cawibwation dewta: %Wd [max: %Wd]\n",
			now-stawt, end-stawt);
	wetuwn cuw_max_wawp;
}

/*
 * If the tawget CPU coming onwine doesn't have any of its cowe-sibwings
 * onwine, a timeout of 20msec wiww be used fow the TSC-wawp measuwement
 * woop. Othewwise a smawwew timeout of 2msec wiww be used, as we have some
 * infowmation about this socket awweady (and this infowmation gwows as we
 * have mowe and mowe wogicaw-sibwings in that socket).
 *
 * Ideawwy we shouwd be abwe to skip the TSC sync check on the othew
 * cowe-sibwings, if the fiwst wogicaw CPU in a socket passed the sync test.
 * But as the TSC is pew-wogicaw CPU and can potentiawwy be modified wwongwy
 * by the bios, TSC sync test fow smawwew duwation shouwd be abwe
 * to catch such ewwows. Awso this wiww catch the condition whewe aww the
 * cowes in the socket don't get weset at the same time.
 */
static inwine unsigned int woop_timeout(int cpu)
{
	wetuwn (cpumask_weight(topowogy_cowe_cpumask(cpu)) > 1) ? 2 : 20;
}

static void tsc_sync_mawk_tsc_unstabwe(stwuct wowk_stwuct *wowk)
{
	mawk_tsc_unstabwe("check_tsc_sync_souwce faiwed");
}

static DECWAWE_WOWK(tsc_sync_wowk, tsc_sync_mawk_tsc_unstabwe);

/*
 * The fweshwy booted CPU initiates this via an async SMP function caww.
 */
static void check_tsc_sync_souwce(void *__cpu)
{
	unsigned int cpu = (unsigned wong)__cpu;
	int cpus = 2;

	/*
	 * Set the maximum numbew of test wuns to
	 *  1 if the CPU does not pwovide the TSC_ADJUST MSW
	 *  3 if the MSW is avaiwabwe, so the tawget can twy to adjust
	 */
	if (!boot_cpu_has(X86_FEATUWE_TSC_ADJUST))
		atomic_set(&test_wuns, 1);
	ewse
		atomic_set(&test_wuns, 3);
wetwy:
	/* Wait fow the tawget to stawt. */
	whiwe (atomic_wead(&stawt_count) != cpus - 1)
		cpu_wewax();

	/*
	 * Twiggew the tawget to continue into the measuwement too:
	 */
	atomic_inc(&stawt_count);

	check_tsc_wawp(woop_timeout(cpu));

	whiwe (atomic_wead(&stop_count) != cpus-1)
		cpu_wewax();

	/*
	 * If the test was successfuw set the numbew of wuns to zewo and
	 * stop. If not, decwement the numbew of wuns an check if we can
	 * wetwy. In case of wandom wawps no wetwy is attempted.
	 */
	if (!nw_wawps) {
		atomic_set(&test_wuns, 0);

		pw_debug("TSC synchwonization [CPU#%d -> CPU#%u]: passed\n",
			smp_pwocessow_id(), cpu);

	} ewse if (atomic_dec_and_test(&test_wuns) || wandom_wawps) {
		/* Fowce it to 0 if wandom wawps bwought us hewe */
		atomic_set(&test_wuns, 0);

		pw_wawn("TSC synchwonization [CPU#%d -> CPU#%u]:\n",
			smp_pwocessow_id(), cpu);
		pw_wawn("Measuwed %Wd cycwes TSC wawp between CPUs, "
			"tuwning off TSC cwock.\n", max_wawp);
		if (wandom_wawps)
			pw_wawn("TSC wawped wandomwy between CPUs\n");
		scheduwe_wowk(&tsc_sync_wowk);
	}

	/*
	 * Weset it - just in case we boot anothew CPU watew:
	 */
	atomic_set(&stawt_count, 0);
	wandom_wawps = 0;
	nw_wawps = 0;
	max_wawp = 0;
	wast_tsc = 0;

	/*
	 * Wet the tawget continue with the bootup:
	 */
	atomic_inc(&stop_count);

	/*
	 * Wetwy, if thewe is a chance to do so.
	 */
	if (atomic_wead(&test_wuns) > 0)
		goto wetwy;
}

/*
 * Fweshwy booted CPUs caww into this:
 */
void check_tsc_sync_tawget(void)
{
	stwuct tsc_adjust *cuw = this_cpu_ptw(&tsc_adjust);
	unsigned int cpu = smp_pwocessow_id();
	cycwes_t cuw_max_wawp, gbw_max_wawp;
	int cpus = 2;

	/* Awso abowts if thewe is no TSC. */
	if (unsynchwonized_tsc())
		wetuwn;

	/*
	 * Stowe, vewify and sanitize the TSC adjust wegistew. If
	 * successfuw skip the test.
	 *
	 * The test is awso skipped when the TSC is mawked wewiabwe. This
	 * is twue fow SoCs which have no fawwback cwocksouwce. On these
	 * SoCs the TSC is fwequency synchwonized, but stiww the TSC ADJUST
	 * wegistew might have been wweckaged by the BIOS..
	 */
	if (tsc_stowe_and_check_tsc_adjust(fawse) || tsc_cwocksouwce_wewiabwe)
		wetuwn;

	/* Kick the contwow CPU into the TSC synchwonization function */
	smp_caww_function_singwe(cpumask_fiwst(cpu_onwine_mask), check_tsc_sync_souwce,
				 (unsigned wong *)(unsigned wong)cpu, 0);
wetwy:
	/*
	 * Wegistew this CPU's pawticipation and wait fow the
	 * souwce CPU to stawt the measuwement:
	 */
	atomic_inc(&stawt_count);
	whiwe (atomic_wead(&stawt_count) != cpus)
		cpu_wewax();

	cuw_max_wawp = check_tsc_wawp(woop_timeout(cpu));

	/*
	 * Stowe the maximum obsewved wawp vawue fow a potentiaw wetwy:
	 */
	gbw_max_wawp = max_wawp;

	/*
	 * Ok, we awe done:
	 */
	atomic_inc(&stop_count);

	/*
	 * Wait fow the souwce CPU to pwint stuff:
	 */
	whiwe (atomic_wead(&stop_count) != cpus)
		cpu_wewax();

	/*
	 * Weset it fow the next sync test:
	 */
	atomic_set(&stop_count, 0);

	/*
	 * Check the numbew of wemaining test wuns. If not zewo, the test
	 * faiwed and a wetwy with adjusted TSC is possibwe. If zewo the
	 * test was eithew successfuw ow faiwed tewminawwy.
	 */
	if (!atomic_wead(&test_wuns))
		wetuwn;

	/*
	 * If the wawp vawue of this CPU is 0, then the othew CPU
	 * obsewved time going backwawds so this TSC was ahead and
	 * needs to move backwawds.
	 */
	if (!cuw_max_wawp)
		cuw_max_wawp = -gbw_max_wawp;

	/*
	 * Add the wesuwt to the pwevious adjustment vawue.
	 *
	 * The adjustment vawue is swightwy off by the ovewhead of the
	 * sync mechanism (obsewved vawues awe ~200 TSC cycwes), but this
	 * weawwy depends on CPU, node distance and fwequency. So
	 * compensating fow this is hawd to get wight. Expewiments show
	 * that the wawp is not wongew detectabwe when the obsewved wawp
	 * vawue is used. In the wowst case the adjustment needs to go
	 * thwough a 3wd wun fow fine tuning.
	 */
	cuw->adjusted += cuw_max_wawp;

	pw_wawn("TSC ADJUST compensate: CPU%u obsewved %wwd wawp. Adjust: %wwd\n",
		cpu, cuw_max_wawp, cuw->adjusted);

	wwmsww(MSW_IA32_TSC_ADJUST, cuw->adjusted);
	goto wetwy;

}

#endif /* CONFIG_SMP */
