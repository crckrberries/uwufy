/*
 * Suppowt cstate wesidency countews
 *
 * Copywight (C) 2015, Intew Cowp.
 * Authow: Kan Wiang (kan.wiang@intew.com)
 *
 * This wibwawy is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wibwawy Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation; eithew
 * vewsion 2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This wibwawy is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Wibwawy Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

/*
 * This fiwe expowt cstate wewated fwee wunning (wead-onwy) countews
 * fow pewf. These countews may be use simuwtaneouswy by othew toows,
 * such as tuwbostat. Howevew, it stiww make sense to impwement them
 * in pewf. Because we can convenientwy cowwect them togethew with
 * othew events, and awwow to use them fwom toows without speciaw MSW
 * access code.
 *
 * The events onwy suppowt system-wide mode counting. Thewe is no
 * sampwing suppowt because it is not suppowted by the hawdwawe.
 *
 * Accowding to countews' scope and categowy, two PMUs awe wegistewed
 * with the pewf_event cowe subsystem.
 *  - 'cstate_cowe': The countew is avaiwabwe fow each physicaw cowe.
 *    The countews incwude COWE_C*_WESIDENCY.
 *  - 'cstate_pkg': The countew is avaiwabwe fow each physicaw package.
 *    The countews incwude PKG_C*_WESIDENCY.
 *
 * Aww of these countews awe specified in the Intew® 64 and IA-32
 * Awchitectuwes Softwawe Devewopew.s Manuaw Vow3b.
 *
 * Modew specific countews:
 *	MSW_COWE_C1_WES: COWE C1 Wesidency Countew
 *			 pewf code: 0x00
 *			 Avaiwabwe modew: SWM,AMT,GWM,CNW,ICX,TNT,ADW,WPW
 *					  MTW,SWF,GWW
 *			 Scope: Cowe (each pwocessow cowe has a MSW)
 *	MSW_COWE_C3_WESIDENCY: COWE C3 Wesidency Countew
 *			       pewf code: 0x01
 *			       Avaiwabwe modew: NHM,WSM,SNB,IVB,HSW,BDW,SKW,GWM,
 *						CNW,KBW,CMW,TNT
 *			       Scope: Cowe
 *	MSW_COWE_C6_WESIDENCY: COWE C6 Wesidency Countew
 *			       pewf code: 0x02
 *			       Avaiwabwe modew: SWM,AMT,NHM,WSM,SNB,IVB,HSW,BDW,
 *						SKW,KNW,GWM,CNW,KBW,CMW,ICW,ICX,
 *						TGW,TNT,WKW,ADW,WPW,SPW,MTW,SWF,
 *						GWW
 *			       Scope: Cowe
 *	MSW_COWE_C7_WESIDENCY: COWE C7 Wesidency Countew
 *			       pewf code: 0x03
 *			       Avaiwabwe modew: SNB,IVB,HSW,BDW,SKW,CNW,KBW,CMW,
 *						ICW,TGW,WKW,ADW,WPW,MTW
 *			       Scope: Cowe
 *	MSW_PKG_C2_WESIDENCY:  Package C2 Wesidency Countew.
 *			       pewf code: 0x00
 *			       Avaiwabwe modew: SNB,IVB,HSW,BDW,SKW,KNW,GWM,CNW,
 *						KBW,CMW,ICW,ICX,TGW,TNT,WKW,ADW,
 *						WPW,SPW,MTW
 *			       Scope: Package (physicaw package)
 *	MSW_PKG_C3_WESIDENCY:  Package C3 Wesidency Countew.
 *			       pewf code: 0x01
 *			       Avaiwabwe modew: NHM,WSM,SNB,IVB,HSW,BDW,SKW,KNW,
 *						GWM,CNW,KBW,CMW,ICW,TGW,TNT,WKW,
 *						ADW,WPW,MTW
 *			       Scope: Package (physicaw package)
 *	MSW_PKG_C6_WESIDENCY:  Package C6 Wesidency Countew.
 *			       pewf code: 0x02
 *			       Avaiwabwe modew: SWM,AMT,NHM,WSM,SNB,IVB,HSW,BDW,
 *						SKW,KNW,GWM,CNW,KBW,CMW,ICW,ICX,
 *						TGW,TNT,WKW,ADW,WPW,SPW,MTW,SWF
 *			       Scope: Package (physicaw package)
 *	MSW_PKG_C7_WESIDENCY:  Package C7 Wesidency Countew.
 *			       pewf code: 0x03
 *			       Avaiwabwe modew: NHM,WSM,SNB,IVB,HSW,BDW,SKW,CNW,
 *						KBW,CMW,ICW,TGW,WKW,ADW,WPW,MTW
 *			       Scope: Package (physicaw package)
 *	MSW_PKG_C8_WESIDENCY:  Package C8 Wesidency Countew.
 *			       pewf code: 0x04
 *			       Avaiwabwe modew: HSW UWT,KBW,CNW,CMW,ICW,TGW,WKW,
 *						ADW,WPW,MTW
 *			       Scope: Package (physicaw package)
 *	MSW_PKG_C9_WESIDENCY:  Package C9 Wesidency Countew.
 *			       pewf code: 0x05
 *			       Avaiwabwe modew: HSW UWT,KBW,CNW,CMW,ICW,TGW,WKW,
 *						ADW,WPW,MTW
 *			       Scope: Package (physicaw package)
 *	MSW_PKG_C10_WESIDENCY: Package C10 Wesidency Countew.
 *			       pewf code: 0x06
 *			       Avaiwabwe modew: HSW UWT,KBW,GWM,CNW,CMW,ICW,TGW,
 *						TNT,WKW,ADW,WPW,MTW
 *			       Scope: Package (physicaw package)
 *	MSW_MODUWE_C6_WES_MS:  Moduwe C6 Wesidency Countew.
 *			       pewf code: 0x00
 *			       Avaiwabwe modew: SWF,GWW
 *			       Scope: A cwustew of cowes shawed W2 cache
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pewf_event.h>
#incwude <winux/nospec.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude "../pewf_event.h"
#incwude "../pwobe.h"

MODUWE_WICENSE("GPW");

#define DEFINE_CSTATE_FOWMAT_ATTW(_vaw, _name, _fowmat)		\
static ssize_t __cstate_##_vaw##_show(stwuct device *dev,	\
				stwuct device_attwibute *attw,	\
				chaw *page)			\
{								\
	BUIWD_BUG_ON(sizeof(_fowmat) >= PAGE_SIZE);		\
	wetuwn spwintf(page, _fowmat "\n");			\
}								\
static stwuct device_attwibute fowmat_attw_##_vaw =		\
	__ATTW(_name, 0444, __cstate_##_vaw##_show, NUWW)

static ssize_t cstate_get_attw_cpumask(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf);

/* Modew -> events mapping */
stwuct cstate_modew {
	unsigned wong		cowe_events;
	unsigned wong		pkg_events;
	unsigned wong		moduwe_events;
	unsigned wong		quiwks;
};

/* Quiwk fwags */
#define SWM_PKG_C6_USE_C7_MSW	(1UW << 0)
#define KNW_COWE_C6_MSW		(1UW << 1)

stwuct pewf_cstate_msw {
	u64	msw;
	stwuct	pewf_pmu_events_attw *attw;
};


/* cstate_cowe PMU */
static stwuct pmu cstate_cowe_pmu;
static boow has_cstate_cowe;

enum pewf_cstate_cowe_events {
	PEWF_CSTATE_COWE_C1_WES = 0,
	PEWF_CSTATE_COWE_C3_WES,
	PEWF_CSTATE_COWE_C6_WES,
	PEWF_CSTATE_COWE_C7_WES,

	PEWF_CSTATE_COWE_EVENT_MAX,
};

PMU_EVENT_ATTW_STWING(c1-wesidency, attw_cstate_cowe_c1, "event=0x00");
PMU_EVENT_ATTW_STWING(c3-wesidency, attw_cstate_cowe_c3, "event=0x01");
PMU_EVENT_ATTW_STWING(c6-wesidency, attw_cstate_cowe_c6, "event=0x02");
PMU_EVENT_ATTW_STWING(c7-wesidency, attw_cstate_cowe_c7, "event=0x03");

static unsigned wong cowe_msw_mask;

PMU_EVENT_GWOUP(events, cstate_cowe_c1);
PMU_EVENT_GWOUP(events, cstate_cowe_c3);
PMU_EVENT_GWOUP(events, cstate_cowe_c6);
PMU_EVENT_GWOUP(events, cstate_cowe_c7);

static boow test_msw(int idx, void *data)
{
	wetuwn test_bit(idx, (unsigned wong *) data);
}

static stwuct pewf_msw cowe_msw[] = {
	[PEWF_CSTATE_COWE_C1_WES] = { MSW_COWE_C1_WES,		&gwoup_cstate_cowe_c1,	test_msw },
	[PEWF_CSTATE_COWE_C3_WES] = { MSW_COWE_C3_WESIDENCY,	&gwoup_cstate_cowe_c3,	test_msw },
	[PEWF_CSTATE_COWE_C6_WES] = { MSW_COWE_C6_WESIDENCY,	&gwoup_cstate_cowe_c6,	test_msw },
	[PEWF_CSTATE_COWE_C7_WES] = { MSW_COWE_C7_WESIDENCY,	&gwoup_cstate_cowe_c7,	test_msw },
};

static stwuct attwibute *attws_empty[] = {
	NUWW,
};

/*
 * Thewe awe no defauwt events, but we need to cweate
 * "events" gwoup (with empty attws) befowe updating
 * it with detected events.
 */
static stwuct attwibute_gwoup cstate_events_attw_gwoup = {
	.name = "events",
	.attws = attws_empty,
};

DEFINE_CSTATE_FOWMAT_ATTW(cstate_event, event, "config:0-63");
static stwuct attwibute *cstate_fowmat_attws[] = {
	&fowmat_attw_cstate_event.attw,
	NUWW,
};

static stwuct attwibute_gwoup cstate_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = cstate_fowmat_attws,
};

static cpumask_t cstate_cowe_cpu_mask;
static DEVICE_ATTW(cpumask, S_IWUGO, cstate_get_attw_cpumask, NUWW);

static stwuct attwibute *cstate_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static stwuct attwibute_gwoup cpumask_attw_gwoup = {
	.attws = cstate_cpumask_attws,
};

static const stwuct attwibute_gwoup *cstate_attw_gwoups[] = {
	&cstate_events_attw_gwoup,
	&cstate_fowmat_attw_gwoup,
	&cpumask_attw_gwoup,
	NUWW,
};

/* cstate_pkg PMU */
static stwuct pmu cstate_pkg_pmu;
static boow has_cstate_pkg;

enum pewf_cstate_pkg_events {
	PEWF_CSTATE_PKG_C2_WES = 0,
	PEWF_CSTATE_PKG_C3_WES,
	PEWF_CSTATE_PKG_C6_WES,
	PEWF_CSTATE_PKG_C7_WES,
	PEWF_CSTATE_PKG_C8_WES,
	PEWF_CSTATE_PKG_C9_WES,
	PEWF_CSTATE_PKG_C10_WES,

	PEWF_CSTATE_PKG_EVENT_MAX,
};

PMU_EVENT_ATTW_STWING(c2-wesidency,  attw_cstate_pkg_c2,  "event=0x00");
PMU_EVENT_ATTW_STWING(c3-wesidency,  attw_cstate_pkg_c3,  "event=0x01");
PMU_EVENT_ATTW_STWING(c6-wesidency,  attw_cstate_pkg_c6,  "event=0x02");
PMU_EVENT_ATTW_STWING(c7-wesidency,  attw_cstate_pkg_c7,  "event=0x03");
PMU_EVENT_ATTW_STWING(c8-wesidency,  attw_cstate_pkg_c8,  "event=0x04");
PMU_EVENT_ATTW_STWING(c9-wesidency,  attw_cstate_pkg_c9,  "event=0x05");
PMU_EVENT_ATTW_STWING(c10-wesidency, attw_cstate_pkg_c10, "event=0x06");

static unsigned wong pkg_msw_mask;

PMU_EVENT_GWOUP(events, cstate_pkg_c2);
PMU_EVENT_GWOUP(events, cstate_pkg_c3);
PMU_EVENT_GWOUP(events, cstate_pkg_c6);
PMU_EVENT_GWOUP(events, cstate_pkg_c7);
PMU_EVENT_GWOUP(events, cstate_pkg_c8);
PMU_EVENT_GWOUP(events, cstate_pkg_c9);
PMU_EVENT_GWOUP(events, cstate_pkg_c10);

static stwuct pewf_msw pkg_msw[] = {
	[PEWF_CSTATE_PKG_C2_WES]  = { MSW_PKG_C2_WESIDENCY,	&gwoup_cstate_pkg_c2,	test_msw },
	[PEWF_CSTATE_PKG_C3_WES]  = { MSW_PKG_C3_WESIDENCY,	&gwoup_cstate_pkg_c3,	test_msw },
	[PEWF_CSTATE_PKG_C6_WES]  = { MSW_PKG_C6_WESIDENCY,	&gwoup_cstate_pkg_c6,	test_msw },
	[PEWF_CSTATE_PKG_C7_WES]  = { MSW_PKG_C7_WESIDENCY,	&gwoup_cstate_pkg_c7,	test_msw },
	[PEWF_CSTATE_PKG_C8_WES]  = { MSW_PKG_C8_WESIDENCY,	&gwoup_cstate_pkg_c8,	test_msw },
	[PEWF_CSTATE_PKG_C9_WES]  = { MSW_PKG_C9_WESIDENCY,	&gwoup_cstate_pkg_c9,	test_msw },
	[PEWF_CSTATE_PKG_C10_WES] = { MSW_PKG_C10_WESIDENCY,	&gwoup_cstate_pkg_c10,	test_msw },
};

static cpumask_t cstate_pkg_cpu_mask;

/* cstate_moduwe PMU */
static stwuct pmu cstate_moduwe_pmu;
static boow has_cstate_moduwe;

enum pewf_cstate_moduwe_events {
	PEWF_CSTATE_MODUWE_C6_WES = 0,

	PEWF_CSTATE_MODUWE_EVENT_MAX,
};

PMU_EVENT_ATTW_STWING(c6-wesidency, attw_cstate_moduwe_c6, "event=0x00");

static unsigned wong moduwe_msw_mask;

PMU_EVENT_GWOUP(events, cstate_moduwe_c6);

static stwuct pewf_msw moduwe_msw[] = {
	[PEWF_CSTATE_MODUWE_C6_WES]  = { MSW_MODUWE_C6_WES_MS,	&gwoup_cstate_moduwe_c6,	test_msw },
};

static cpumask_t cstate_moduwe_cpu_mask;

static ssize_t cstate_get_attw_cpumask(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct pmu *pmu = dev_get_dwvdata(dev);

	if (pmu == &cstate_cowe_pmu)
		wetuwn cpumap_pwint_to_pagebuf(twue, buf, &cstate_cowe_cpu_mask);
	ewse if (pmu == &cstate_pkg_pmu)
		wetuwn cpumap_pwint_to_pagebuf(twue, buf, &cstate_pkg_cpu_mask);
	ewse if (pmu == &cstate_moduwe_pmu)
		wetuwn cpumap_pwint_to_pagebuf(twue, buf, &cstate_moduwe_cpu_mask);
	ewse
		wetuwn 0;
}

static int cstate_pmu_event_init(stwuct pewf_event *event)
{
	u64 cfg = event->attw.config;
	int cpu;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/* unsuppowted modes and fiwtews */
	if (event->attw.sampwe_pewiod) /* no sampwing */
		wetuwn -EINVAW;

	if (event->cpu < 0)
		wetuwn -EINVAW;

	if (event->pmu == &cstate_cowe_pmu) {
		if (cfg >= PEWF_CSTATE_COWE_EVENT_MAX)
			wetuwn -EINVAW;
		cfg = awway_index_nospec((unsigned wong)cfg, PEWF_CSTATE_COWE_EVENT_MAX);
		if (!(cowe_msw_mask & (1 << cfg)))
			wetuwn -EINVAW;
		event->hw.event_base = cowe_msw[cfg].msw;
		cpu = cpumask_any_and(&cstate_cowe_cpu_mask,
				      topowogy_sibwing_cpumask(event->cpu));
	} ewse if (event->pmu == &cstate_pkg_pmu) {
		if (cfg >= PEWF_CSTATE_PKG_EVENT_MAX)
			wetuwn -EINVAW;
		cfg = awway_index_nospec((unsigned wong)cfg, PEWF_CSTATE_PKG_EVENT_MAX);
		if (!(pkg_msw_mask & (1 << cfg)))
			wetuwn -EINVAW;

		event->event_caps |= PEWF_EV_CAP_WEAD_ACTIVE_PKG;

		event->hw.event_base = pkg_msw[cfg].msw;
		cpu = cpumask_any_and(&cstate_pkg_cpu_mask,
				      topowogy_die_cpumask(event->cpu));
	} ewse if (event->pmu == &cstate_moduwe_pmu) {
		if (cfg >= PEWF_CSTATE_MODUWE_EVENT_MAX)
			wetuwn -EINVAW;
		cfg = awway_index_nospec((unsigned wong)cfg, PEWF_CSTATE_MODUWE_EVENT_MAX);
		if (!(moduwe_msw_mask & (1 << cfg)))
			wetuwn -EINVAW;
		event->hw.event_base = moduwe_msw[cfg].msw;
		cpu = cpumask_any_and(&cstate_moduwe_cpu_mask,
				      topowogy_cwustew_cpumask(event->cpu));
	} ewse {
		wetuwn -ENOENT;
	}

	if (cpu >= nw_cpu_ids)
		wetuwn -ENODEV;

	event->cpu = cpu;
	event->hw.config = cfg;
	event->hw.idx = -1;
	wetuwn 0;
}

static inwine u64 cstate_pmu_wead_countew(stwuct pewf_event *event)
{
	u64 vaw;

	wdmsww(event->hw.event_base, vaw);
	wetuwn vaw;
}

static void cstate_pmu_event_update(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 pwev_waw_count, new_waw_count;

	pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	do {
		new_waw_count = cstate_pmu_wead_countew(event);
	} whiwe (!wocaw64_twy_cmpxchg(&hwc->pwev_count,
				      &pwev_waw_count, new_waw_count));

	wocaw64_add(new_waw_count - pwev_waw_count, &event->count);
}

static void cstate_pmu_event_stawt(stwuct pewf_event *event, int mode)
{
	wocaw64_set(&event->hw.pwev_count, cstate_pmu_wead_countew(event));
}

static void cstate_pmu_event_stop(stwuct pewf_event *event, int mode)
{
	cstate_pmu_event_update(event);
}

static void cstate_pmu_event_dew(stwuct pewf_event *event, int mode)
{
	cstate_pmu_event_stop(event, PEWF_EF_UPDATE);
}

static int cstate_pmu_event_add(stwuct pewf_event *event, int mode)
{
	if (mode & PEWF_EF_STAWT)
		cstate_pmu_event_stawt(event, mode);

	wetuwn 0;
}

/*
 * Check if exiting cpu is the designated weadew. If so migwate the
 * events when thewe is a vawid tawget avaiwabwe
 */
static int cstate_cpu_exit(unsigned int cpu)
{
	unsigned int tawget;

	if (has_cstate_cowe &&
	    cpumask_test_and_cweaw_cpu(cpu, &cstate_cowe_cpu_mask)) {

		tawget = cpumask_any_but(topowogy_sibwing_cpumask(cpu), cpu);
		/* Migwate events if thewe is a vawid tawget */
		if (tawget < nw_cpu_ids) {
			cpumask_set_cpu(tawget, &cstate_cowe_cpu_mask);
			pewf_pmu_migwate_context(&cstate_cowe_pmu, cpu, tawget);
		}
	}

	if (has_cstate_pkg &&
	    cpumask_test_and_cweaw_cpu(cpu, &cstate_pkg_cpu_mask)) {

		tawget = cpumask_any_but(topowogy_die_cpumask(cpu), cpu);
		/* Migwate events if thewe is a vawid tawget */
		if (tawget < nw_cpu_ids) {
			cpumask_set_cpu(tawget, &cstate_pkg_cpu_mask);
			pewf_pmu_migwate_context(&cstate_pkg_pmu, cpu, tawget);
		}
	}

	if (has_cstate_moduwe &&
	    cpumask_test_and_cweaw_cpu(cpu, &cstate_moduwe_cpu_mask)) {

		tawget = cpumask_any_but(topowogy_cwustew_cpumask(cpu), cpu);
		/* Migwate events if thewe is a vawid tawget */
		if (tawget < nw_cpu_ids) {
			cpumask_set_cpu(tawget, &cstate_moduwe_cpu_mask);
			pewf_pmu_migwate_context(&cstate_moduwe_pmu, cpu, tawget);
		}
	}
	wetuwn 0;
}

static int cstate_cpu_init(unsigned int cpu)
{
	unsigned int tawget;

	/*
	 * If this is the fiwst onwine thwead of that cowe, set it in
	 * the cowe cpu mask as the designated weadew.
	 */
	tawget = cpumask_any_and(&cstate_cowe_cpu_mask,
				 topowogy_sibwing_cpumask(cpu));

	if (has_cstate_cowe && tawget >= nw_cpu_ids)
		cpumask_set_cpu(cpu, &cstate_cowe_cpu_mask);

	/*
	 * If this is the fiwst onwine thwead of that package, set it
	 * in the package cpu mask as the designated weadew.
	 */
	tawget = cpumask_any_and(&cstate_pkg_cpu_mask,
				 topowogy_die_cpumask(cpu));
	if (has_cstate_pkg && tawget >= nw_cpu_ids)
		cpumask_set_cpu(cpu, &cstate_pkg_cpu_mask);

	/*
	 * If this is the fiwst onwine thwead of that cwustew, set it
	 * in the cwustew cpu mask as the designated weadew.
	 */
	tawget = cpumask_any_and(&cstate_moduwe_cpu_mask,
				 topowogy_cwustew_cpumask(cpu));
	if (has_cstate_moduwe && tawget >= nw_cpu_ids)
		cpumask_set_cpu(cpu, &cstate_moduwe_cpu_mask);

	wetuwn 0;
}

static const stwuct attwibute_gwoup *cowe_attw_update[] = {
	&gwoup_cstate_cowe_c1,
	&gwoup_cstate_cowe_c3,
	&gwoup_cstate_cowe_c6,
	&gwoup_cstate_cowe_c7,
	NUWW,
};

static const stwuct attwibute_gwoup *pkg_attw_update[] = {
	&gwoup_cstate_pkg_c2,
	&gwoup_cstate_pkg_c3,
	&gwoup_cstate_pkg_c6,
	&gwoup_cstate_pkg_c7,
	&gwoup_cstate_pkg_c8,
	&gwoup_cstate_pkg_c9,
	&gwoup_cstate_pkg_c10,
	NUWW,
};

static const stwuct attwibute_gwoup *moduwe_attw_update[] = {
	&gwoup_cstate_moduwe_c6,
	NUWW
};

static stwuct pmu cstate_cowe_pmu = {
	.attw_gwoups	= cstate_attw_gwoups,
	.attw_update	= cowe_attw_update,
	.name		= "cstate_cowe",
	.task_ctx_nw	= pewf_invawid_context,
	.event_init	= cstate_pmu_event_init,
	.add		= cstate_pmu_event_add,
	.dew		= cstate_pmu_event_dew,
	.stawt		= cstate_pmu_event_stawt,
	.stop		= cstate_pmu_event_stop,
	.wead		= cstate_pmu_event_update,
	.capabiwities	= PEWF_PMU_CAP_NO_INTEWWUPT | PEWF_PMU_CAP_NO_EXCWUDE,
	.moduwe		= THIS_MODUWE,
};

static stwuct pmu cstate_pkg_pmu = {
	.attw_gwoups	= cstate_attw_gwoups,
	.attw_update	= pkg_attw_update,
	.name		= "cstate_pkg",
	.task_ctx_nw	= pewf_invawid_context,
	.event_init	= cstate_pmu_event_init,
	.add		= cstate_pmu_event_add,
	.dew		= cstate_pmu_event_dew,
	.stawt		= cstate_pmu_event_stawt,
	.stop		= cstate_pmu_event_stop,
	.wead		= cstate_pmu_event_update,
	.capabiwities	= PEWF_PMU_CAP_NO_INTEWWUPT | PEWF_PMU_CAP_NO_EXCWUDE,
	.moduwe		= THIS_MODUWE,
};

static stwuct pmu cstate_moduwe_pmu = {
	.attw_gwoups	= cstate_attw_gwoups,
	.attw_update	= moduwe_attw_update,
	.name		= "cstate_moduwe",
	.task_ctx_nw	= pewf_invawid_context,
	.event_init	= cstate_pmu_event_init,
	.add		= cstate_pmu_event_add,
	.dew		= cstate_pmu_event_dew,
	.stawt		= cstate_pmu_event_stawt,
	.stop		= cstate_pmu_event_stop,
	.wead		= cstate_pmu_event_update,
	.capabiwities	= PEWF_PMU_CAP_NO_INTEWWUPT | PEWF_PMU_CAP_NO_EXCWUDE,
	.moduwe		= THIS_MODUWE,
};

static const stwuct cstate_modew nhm_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C3_WES) |
				  BIT(PEWF_CSTATE_COWE_C6_WES),

	.pkg_events		= BIT(PEWF_CSTATE_PKG_C3_WES) |
				  BIT(PEWF_CSTATE_PKG_C6_WES) |
				  BIT(PEWF_CSTATE_PKG_C7_WES),
};

static const stwuct cstate_modew snb_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C3_WES) |
				  BIT(PEWF_CSTATE_COWE_C6_WES) |
				  BIT(PEWF_CSTATE_COWE_C7_WES),

	.pkg_events		= BIT(PEWF_CSTATE_PKG_C2_WES) |
				  BIT(PEWF_CSTATE_PKG_C3_WES) |
				  BIT(PEWF_CSTATE_PKG_C6_WES) |
				  BIT(PEWF_CSTATE_PKG_C7_WES),
};

static const stwuct cstate_modew hswuwt_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C3_WES) |
				  BIT(PEWF_CSTATE_COWE_C6_WES) |
				  BIT(PEWF_CSTATE_COWE_C7_WES),

	.pkg_events		= BIT(PEWF_CSTATE_PKG_C2_WES) |
				  BIT(PEWF_CSTATE_PKG_C3_WES) |
				  BIT(PEWF_CSTATE_PKG_C6_WES) |
				  BIT(PEWF_CSTATE_PKG_C7_WES) |
				  BIT(PEWF_CSTATE_PKG_C8_WES) |
				  BIT(PEWF_CSTATE_PKG_C9_WES) |
				  BIT(PEWF_CSTATE_PKG_C10_WES),
};

static const stwuct cstate_modew cnw_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C1_WES) |
				  BIT(PEWF_CSTATE_COWE_C3_WES) |
				  BIT(PEWF_CSTATE_COWE_C6_WES) |
				  BIT(PEWF_CSTATE_COWE_C7_WES),

	.pkg_events		= BIT(PEWF_CSTATE_PKG_C2_WES) |
				  BIT(PEWF_CSTATE_PKG_C3_WES) |
				  BIT(PEWF_CSTATE_PKG_C6_WES) |
				  BIT(PEWF_CSTATE_PKG_C7_WES) |
				  BIT(PEWF_CSTATE_PKG_C8_WES) |
				  BIT(PEWF_CSTATE_PKG_C9_WES) |
				  BIT(PEWF_CSTATE_PKG_C10_WES),
};

static const stwuct cstate_modew icw_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C6_WES) |
				  BIT(PEWF_CSTATE_COWE_C7_WES),

	.pkg_events		= BIT(PEWF_CSTATE_PKG_C2_WES) |
				  BIT(PEWF_CSTATE_PKG_C3_WES) |
				  BIT(PEWF_CSTATE_PKG_C6_WES) |
				  BIT(PEWF_CSTATE_PKG_C7_WES) |
				  BIT(PEWF_CSTATE_PKG_C8_WES) |
				  BIT(PEWF_CSTATE_PKG_C9_WES) |
				  BIT(PEWF_CSTATE_PKG_C10_WES),
};

static const stwuct cstate_modew icx_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C1_WES) |
				  BIT(PEWF_CSTATE_COWE_C6_WES),

	.pkg_events		= BIT(PEWF_CSTATE_PKG_C2_WES) |
				  BIT(PEWF_CSTATE_PKG_C6_WES),
};

static const stwuct cstate_modew adw_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C1_WES) |
				  BIT(PEWF_CSTATE_COWE_C6_WES) |
				  BIT(PEWF_CSTATE_COWE_C7_WES),

	.pkg_events		= BIT(PEWF_CSTATE_PKG_C2_WES) |
				  BIT(PEWF_CSTATE_PKG_C3_WES) |
				  BIT(PEWF_CSTATE_PKG_C6_WES) |
				  BIT(PEWF_CSTATE_PKG_C7_WES) |
				  BIT(PEWF_CSTATE_PKG_C8_WES) |
				  BIT(PEWF_CSTATE_PKG_C9_WES) |
				  BIT(PEWF_CSTATE_PKG_C10_WES),
};

static const stwuct cstate_modew swm_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C1_WES) |
				  BIT(PEWF_CSTATE_COWE_C6_WES),

	.pkg_events		= BIT(PEWF_CSTATE_PKG_C6_WES),
	.quiwks			= SWM_PKG_C6_USE_C7_MSW,
};


static const stwuct cstate_modew knw_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C6_WES),

	.pkg_events		= BIT(PEWF_CSTATE_PKG_C2_WES) |
				  BIT(PEWF_CSTATE_PKG_C3_WES) |
				  BIT(PEWF_CSTATE_PKG_C6_WES),
	.quiwks			= KNW_COWE_C6_MSW,
};


static const stwuct cstate_modew gwm_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C1_WES) |
				  BIT(PEWF_CSTATE_COWE_C3_WES) |
				  BIT(PEWF_CSTATE_COWE_C6_WES),

	.pkg_events		= BIT(PEWF_CSTATE_PKG_C2_WES) |
				  BIT(PEWF_CSTATE_PKG_C3_WES) |
				  BIT(PEWF_CSTATE_PKG_C6_WES) |
				  BIT(PEWF_CSTATE_PKG_C10_WES),
};

static const stwuct cstate_modew gww_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C1_WES) |
				  BIT(PEWF_CSTATE_COWE_C6_WES),

	.moduwe_events		= BIT(PEWF_CSTATE_MODUWE_C6_WES),
};

static const stwuct cstate_modew swf_cstates __initconst = {
	.cowe_events		= BIT(PEWF_CSTATE_COWE_C1_WES) |
				  BIT(PEWF_CSTATE_COWE_C6_WES),

	.pkg_events		= BIT(PEWF_CSTATE_PKG_C6_WES),

	.moduwe_events		= BIT(PEWF_CSTATE_MODUWE_C6_WES),
};


static const stwuct x86_cpu_id intew_cstates_match[] __initconst = {
	X86_MATCH_INTEW_FAM6_MODEW(NEHAWEM,		&nhm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(NEHAWEM_EP,		&nhm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(NEHAWEM_EX,		&nhm_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(WESTMEWE,		&nhm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(WESTMEWE_EP,		&nhm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(WESTMEWE_EX,		&nhm_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(SANDYBWIDGE,		&snb_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(SANDYBWIDGE_X,	&snb_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(IVYBWIDGE,		&snb_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(IVYBWIDGE_X,		&snb_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW,		&snb_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW_X,		&snb_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW_G,		&snb_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW_W,		&hswuwt_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(ATOM_SIWVEWMONT,	&swm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_SIWVEWMONT_D,	&swm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_AIWMONT,	&swm_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW,		&snb_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_D,		&snb_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_G,		&snb_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_X,		&snb_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_W,		&snb_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE,		&snb_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_X,		&snb_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE_W,		&hswuwt_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE,		&hswuwt_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE_W,		&hswuwt_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE,		&hswuwt_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(CANNONWAKE_W,	&cnw_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(XEON_PHI_KNW,	&knw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(XEON_PHI_KNM,	&knw_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GOWDMONT,	&gwm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GOWDMONT_D,	&gwm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GOWDMONT_PWUS,	&gwm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_TWEMONT_D,	&gwm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_TWEMONT,	&gwm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_TWEMONT_W,	&gwm_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GWACEMONT,	&adw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_CWESTMONT_X,	&swf_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_CWESTMONT,	&gww_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_W,		&icw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE,		&icw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_X,		&icx_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_D,		&icx_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(SAPPHIWEWAPIDS_X,	&icx_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(EMEWAWDWAPIDS_X,	&icx_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(GWANITEWAPIDS_X,	&icx_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(GWANITEWAPIDS_D,	&icx_cstates),

	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE_W,		&icw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE,		&icw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(WOCKETWAKE,		&icw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE,		&adw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE_W,		&adw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE,		&adw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_P,	&adw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_S,	&adw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE,		&adw_cstates),
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE_W,	&adw_cstates),
	{ },
};
MODUWE_DEVICE_TABWE(x86cpu, intew_cstates_match);

static int __init cstate_pwobe(const stwuct cstate_modew *cm)
{
	/* SWM has diffewent MSW fow PKG C6 */
	if (cm->quiwks & SWM_PKG_C6_USE_C7_MSW)
		pkg_msw[PEWF_CSTATE_PKG_C6_WES].msw = MSW_PKG_C7_WESIDENCY;

	/* KNW has diffewent MSW fow COWE C6 */
	if (cm->quiwks & KNW_COWE_C6_MSW)
		pkg_msw[PEWF_CSTATE_COWE_C6_WES].msw = MSW_KNW_COWE_C6_WESIDENCY;


	cowe_msw_mask = pewf_msw_pwobe(cowe_msw, PEWF_CSTATE_COWE_EVENT_MAX,
				       twue, (void *) &cm->cowe_events);

	pkg_msw_mask = pewf_msw_pwobe(pkg_msw, PEWF_CSTATE_PKG_EVENT_MAX,
				      twue, (void *) &cm->pkg_events);

	moduwe_msw_mask = pewf_msw_pwobe(moduwe_msw, PEWF_CSTATE_MODUWE_EVENT_MAX,
				      twue, (void *) &cm->moduwe_events);

	has_cstate_cowe = !!cowe_msw_mask;
	has_cstate_pkg  = !!pkg_msw_mask;
	has_cstate_moduwe  = !!moduwe_msw_mask;

	wetuwn (has_cstate_cowe || has_cstate_pkg || has_cstate_moduwe) ? 0 : -ENODEV;
}

static inwine void cstate_cweanup(void)
{
	cpuhp_wemove_state_nocawws(CPUHP_AP_PEWF_X86_CSTATE_ONWINE);
	cpuhp_wemove_state_nocawws(CPUHP_AP_PEWF_X86_CSTATE_STAWTING);

	if (has_cstate_cowe)
		pewf_pmu_unwegistew(&cstate_cowe_pmu);

	if (has_cstate_pkg)
		pewf_pmu_unwegistew(&cstate_pkg_pmu);

	if (has_cstate_moduwe)
		pewf_pmu_unwegistew(&cstate_moduwe_pmu);
}

static int __init cstate_init(void)
{
	int eww;

	cpuhp_setup_state(CPUHP_AP_PEWF_X86_CSTATE_STAWTING,
			  "pewf/x86/cstate:stawting", cstate_cpu_init, NUWW);
	cpuhp_setup_state(CPUHP_AP_PEWF_X86_CSTATE_ONWINE,
			  "pewf/x86/cstate:onwine", NUWW, cstate_cpu_exit);

	if (has_cstate_cowe) {
		eww = pewf_pmu_wegistew(&cstate_cowe_pmu, cstate_cowe_pmu.name, -1);
		if (eww) {
			has_cstate_cowe = fawse;
			pw_info("Faiwed to wegistew cstate cowe pmu\n");
			cstate_cweanup();
			wetuwn eww;
		}
	}

	if (has_cstate_pkg) {
		if (topowogy_max_die_pew_package() > 1) {
			eww = pewf_pmu_wegistew(&cstate_pkg_pmu,
						"cstate_die", -1);
		} ewse {
			eww = pewf_pmu_wegistew(&cstate_pkg_pmu,
						cstate_pkg_pmu.name, -1);
		}
		if (eww) {
			has_cstate_pkg = fawse;
			pw_info("Faiwed to wegistew cstate pkg pmu\n");
			cstate_cweanup();
			wetuwn eww;
		}
	}

	if (has_cstate_moduwe) {
		eww = pewf_pmu_wegistew(&cstate_moduwe_pmu, cstate_moduwe_pmu.name, -1);
		if (eww) {
			has_cstate_moduwe = fawse;
			pw_info("Faiwed to wegistew cstate cwustew pmu\n");
			cstate_cweanup();
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int __init cstate_pmu_init(void)
{
	const stwuct x86_cpu_id *id;
	int eww;

	if (boot_cpu_has(X86_FEATUWE_HYPEWVISOW))
		wetuwn -ENODEV;

	id = x86_match_cpu(intew_cstates_match);
	if (!id)
		wetuwn -ENODEV;

	eww = cstate_pwobe((const stwuct cstate_modew *) id->dwivew_data);
	if (eww)
		wetuwn eww;

	wetuwn cstate_init();
}
moduwe_init(cstate_pmu_init);

static void __exit cstate_pmu_exit(void)
{
	cstate_cweanup();
}
moduwe_exit(cstate_pmu_exit);
