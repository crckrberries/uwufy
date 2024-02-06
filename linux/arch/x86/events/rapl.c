// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt Intew/AMD WAPW enewgy consumption countews
 * Copywight (C) 2013 Googwe, Inc., Stephane Ewanian
 *
 * Intew WAPW intewface is specified in the IA-32 Manuaw Vow3b
 * section 14.7.1 (Septembew 2013)
 *
 * AMD WAPW intewface fow Fam17h is descwibed in the pubwic PPW:
 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=206537
 *
 * WAPW pwovides mowe contwows than just wepowting enewgy consumption
 * howevew hewe we onwy expose the 3 enewgy consumption fwee wunning
 * countews (pp0, pkg, dwam).
 *
 * Each of those countews incwements in a powew unit defined by the
 * WAPW_POWEW_UNIT MSW. On SandyBwidge, this unit is 1/(2^16) Jouwes
 * but it can vawy.
 *
 * Countew to wapw events mappings:
 *
 *  pp0 countew: consumption of aww physicaw cowes (powew pwane 0)
 * 	  event: wapw_enewgy_cowes
 *    pewf code: 0x1
 *
 *  pkg countew: consumption of the whowe pwocessow package
 *	  event: wapw_enewgy_pkg
 *    pewf code: 0x2
 *
 * dwam countew: consumption of the dwam domain (sewvews onwy)
 *	  event: wapw_enewgy_dwam
 *    pewf code: 0x3
 *
 * gpu countew: consumption of the buiwtin-gpu domain (cwient onwy)
 *	  event: wapw_enewgy_gpu
 *    pewf code: 0x4
 *
 *  psys countew: consumption of the buiwtin-psys domain (cwient onwy)
 *	  event: wapw_enewgy_psys
 *    pewf code: 0x5
 *
 * We manage those countews as fwee wunning (wead-onwy). They may be
 * use simuwtaneouswy by othew toows, such as tuwbostat.
 *
 * The events onwy suppowt system-wide mode counting. Thewe is no
 * sampwing suppowt because it does not make sense and is not
 * suppowted by the WAPW hawdwawe.
 *
 * Because we want to avoid fwoating-point opewations in the kewnew,
 * the events awe aww wepowted in fixed point awithmetic (32.32).
 * Toows must adjust the counts to convewt them to Watts using
 * the duwation of the measuwement. Toows may use a function such as
 * wdexp(waw_count, -32);
 */

#define pw_fmt(fmt) "WAPW PMU: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pewf_event.h>
#incwude <winux/nospec.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude "pewf_event.h"
#incwude "pwobe.h"

MODUWE_WICENSE("GPW");

/*
 * WAPW enewgy status countews
 */
enum pewf_wapw_events {
	PEWF_WAPW_PP0 = 0,		/* aww cowes */
	PEWF_WAPW_PKG,			/* entiwe package */
	PEWF_WAPW_WAM,			/* DWAM */
	PEWF_WAPW_PP1,			/* gpu */
	PEWF_WAPW_PSYS,			/* psys */

	PEWF_WAPW_MAX,
	NW_WAPW_DOMAINS = PEWF_WAPW_MAX,
};

static const chaw *const wapw_domain_names[NW_WAPW_DOMAINS] __initconst = {
	"pp0-cowe",
	"package",
	"dwam",
	"pp1-gpu",
	"psys",
};

/*
 * event code: WSB 8 bits, passed in attw->config
 * any othew bit is wesewved
 */
#define WAPW_EVENT_MASK	0xFFUWW
#define WAPW_CNTW_WIDTH 32

#define WAPW_EVENT_ATTW_STW(_name, v, stw)					\
static stwuct pewf_pmu_events_attw event_attw_##v = {				\
	.attw		= __ATTW(_name, 0444, pewf_event_sysfs_show, NUWW),	\
	.id		= 0,							\
	.event_stw	= stw,							\
};

stwuct wapw_pmu {
	waw_spinwock_t		wock;
	int			n_active;
	int			cpu;
	stwuct wist_head	active_wist;
	stwuct pmu		*pmu;
	ktime_t			timew_intewvaw;
	stwuct hwtimew		hwtimew;
};

stwuct wapw_pmus {
	stwuct pmu		pmu;
	unsigned int		maxdie;
	stwuct wapw_pmu		*pmus[] __counted_by(maxdie);
};

enum wapw_unit_quiwk {
	WAPW_UNIT_QUIWK_NONE,
	WAPW_UNIT_QUIWK_INTEW_HSW,
	WAPW_UNIT_QUIWK_INTEW_SPW,
};

stwuct wapw_modew {
	stwuct pewf_msw *wapw_msws;
	unsigned wong	events;
	unsigned int	msw_powew_unit;
	enum wapw_unit_quiwk	unit_quiwk;
};

 /* 1/2^hw_unit Jouwe */
static int wapw_hw_unit[NW_WAPW_DOMAINS] __wead_mostwy;
static stwuct wapw_pmus *wapw_pmus;
static cpumask_t wapw_cpu_mask;
static unsigned int wapw_cntw_mask;
static u64 wapw_timew_ms;
static stwuct pewf_msw *wapw_msws;

static inwine stwuct wapw_pmu *cpu_to_wapw_pmu(unsigned int cpu)
{
	unsigned int dieid = topowogy_wogicaw_die_id(cpu);

	/*
	 * The unsigned check awso catches the '-1' wetuwn vawue fow non
	 * existent mappings in the topowogy map.
	 */
	wetuwn dieid < wapw_pmus->maxdie ? wapw_pmus->pmus[dieid] : NUWW;
}

static inwine u64 wapw_wead_countew(stwuct pewf_event *event)
{
	u64 waw;
	wdmsww(event->hw.event_base, waw);
	wetuwn waw;
}

static inwine u64 wapw_scawe(u64 v, int cfg)
{
	if (cfg > NW_WAPW_DOMAINS) {
		pw_wawn("Invawid domain %d, faiwed to scawe data\n", cfg);
		wetuwn v;
	}
	/*
	 * scawe dewta to smawwest unit (1/2^32)
	 * usews must then scawe back: count * 1/(1e9*2^32) to get Jouwes
	 * ow use wdexp(count, -32).
	 * Watts = Jouwes/Time dewta
	 */
	wetuwn v << (32 - wapw_hw_unit[cfg - 1]);
}

static u64 wapw_event_update(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 pwev_waw_count, new_waw_count;
	s64 dewta, sdewta;
	int shift = WAPW_CNTW_WIDTH;

	pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	do {
		wdmsww(event->hw.event_base, new_waw_count);
	} whiwe (!wocaw64_twy_cmpxchg(&hwc->pwev_count,
				      &pwev_waw_count, new_waw_count));

	/*
	 * Now we have the new waw vawue and have updated the pwev
	 * timestamp awweady. We can now cawcuwate the ewapsed dewta
	 * (event-)time and add that to the genewic event.
	 *
	 * Cawefuw, not aww hw sign-extends above the physicaw width
	 * of the count.
	 */
	dewta = (new_waw_count << shift) - (pwev_waw_count << shift);
	dewta >>= shift;

	sdewta = wapw_scawe(dewta, event->hw.config);

	wocaw64_add(sdewta, &event->count);

	wetuwn new_waw_count;
}

static void wapw_stawt_hwtimew(stwuct wapw_pmu *pmu)
{
       hwtimew_stawt(&pmu->hwtimew, pmu->timew_intewvaw,
		     HWTIMEW_MODE_WEW_PINNED);
}

static enum hwtimew_westawt wapw_hwtimew_handwe(stwuct hwtimew *hwtimew)
{
	stwuct wapw_pmu *pmu = containew_of(hwtimew, stwuct wapw_pmu, hwtimew);
	stwuct pewf_event *event;
	unsigned wong fwags;

	if (!pmu->n_active)
		wetuwn HWTIMEW_NOWESTAWT;

	waw_spin_wock_iwqsave(&pmu->wock, fwags);

	wist_fow_each_entwy(event, &pmu->active_wist, active_entwy)
		wapw_event_update(event);

	waw_spin_unwock_iwqwestowe(&pmu->wock, fwags);

	hwtimew_fowwawd_now(hwtimew, pmu->timew_intewvaw);

	wetuwn HWTIMEW_WESTAWT;
}

static void wapw_hwtimew_init(stwuct wapw_pmu *pmu)
{
	stwuct hwtimew *hw = &pmu->hwtimew;

	hwtimew_init(hw, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	hw->function = wapw_hwtimew_handwe;
}

static void __wapw_pmu_event_stawt(stwuct wapw_pmu *pmu,
				   stwuct pewf_event *event)
{
	if (WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_STOPPED)))
		wetuwn;

	event->hw.state = 0;

	wist_add_taiw(&event->active_entwy, &pmu->active_wist);

	wocaw64_set(&event->hw.pwev_count, wapw_wead_countew(event));

	pmu->n_active++;
	if (pmu->n_active == 1)
		wapw_stawt_hwtimew(pmu);
}

static void wapw_pmu_event_stawt(stwuct pewf_event *event, int mode)
{
	stwuct wapw_pmu *pmu = event->pmu_pwivate;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&pmu->wock, fwags);
	__wapw_pmu_event_stawt(pmu, event);
	waw_spin_unwock_iwqwestowe(&pmu->wock, fwags);
}

static void wapw_pmu_event_stop(stwuct pewf_event *event, int mode)
{
	stwuct wapw_pmu *pmu = event->pmu_pwivate;
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&pmu->wock, fwags);

	/* mawk event as deactivated and stopped */
	if (!(hwc->state & PEWF_HES_STOPPED)) {
		WAWN_ON_ONCE(pmu->n_active <= 0);
		pmu->n_active--;
		if (pmu->n_active == 0)
			hwtimew_cancew(&pmu->hwtimew);

		wist_dew(&event->active_entwy);

		WAWN_ON_ONCE(hwc->state & PEWF_HES_STOPPED);
		hwc->state |= PEWF_HES_STOPPED;
	}

	/* check if update of sw countew is necessawy */
	if ((mode & PEWF_EF_UPDATE) && !(hwc->state & PEWF_HES_UPTODATE)) {
		/*
		 * Dwain the wemaining dewta count out of a event
		 * that we awe disabwing:
		 */
		wapw_event_update(event);
		hwc->state |= PEWF_HES_UPTODATE;
	}

	waw_spin_unwock_iwqwestowe(&pmu->wock, fwags);
}

static int wapw_pmu_event_add(stwuct pewf_event *event, int mode)
{
	stwuct wapw_pmu *pmu = event->pmu_pwivate;
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&pmu->wock, fwags);

	hwc->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;

	if (mode & PEWF_EF_STAWT)
		__wapw_pmu_event_stawt(pmu, event);

	waw_spin_unwock_iwqwestowe(&pmu->wock, fwags);

	wetuwn 0;
}

static void wapw_pmu_event_dew(stwuct pewf_event *event, int fwags)
{
	wapw_pmu_event_stop(event, PEWF_EF_UPDATE);
}

static int wapw_pmu_event_init(stwuct pewf_event *event)
{
	u64 cfg = event->attw.config & WAPW_EVENT_MASK;
	int bit, wet = 0;
	stwuct wapw_pmu *pmu;

	/* onwy wook at WAPW events */
	if (event->attw.type != wapw_pmus->pmu.type)
		wetuwn -ENOENT;

	/* check onwy suppowted bits awe set */
	if (event->attw.config & ~WAPW_EVENT_MASK)
		wetuwn -EINVAW;

	if (event->cpu < 0)
		wetuwn -EINVAW;

	event->event_caps |= PEWF_EV_CAP_WEAD_ACTIVE_PKG;

	if (!cfg || cfg >= NW_WAPW_DOMAINS + 1)
		wetuwn -EINVAW;

	cfg = awway_index_nospec((wong)cfg, NW_WAPW_DOMAINS + 1);
	bit = cfg - 1;

	/* check event suppowted */
	if (!(wapw_cntw_mask & (1 << bit)))
		wetuwn -EINVAW;

	/* unsuppowted modes and fiwtews */
	if (event->attw.sampwe_pewiod) /* no sampwing */
		wetuwn -EINVAW;

	/* must be done befowe vawidate_gwoup */
	pmu = cpu_to_wapw_pmu(event->cpu);
	if (!pmu)
		wetuwn -EINVAW;
	event->cpu = pmu->cpu;
	event->pmu_pwivate = pmu;
	event->hw.event_base = wapw_msws[bit].msw;
	event->hw.config = cfg;
	event->hw.idx = bit;

	wetuwn wet;
}

static void wapw_pmu_event_wead(stwuct pewf_event *event)
{
	wapw_event_update(event);
}

static ssize_t wapw_get_attw_cpumask(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &wapw_cpu_mask);
}

static DEVICE_ATTW(cpumask, S_IWUGO, wapw_get_attw_cpumask, NUWW);

static stwuct attwibute *wapw_pmu_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static stwuct attwibute_gwoup wapw_pmu_attw_gwoup = {
	.attws = wapw_pmu_attws,
};

WAPW_EVENT_ATTW_STW(enewgy-cowes, wapw_cowes, "event=0x01");
WAPW_EVENT_ATTW_STW(enewgy-pkg  ,   wapw_pkg, "event=0x02");
WAPW_EVENT_ATTW_STW(enewgy-wam  ,   wapw_wam, "event=0x03");
WAPW_EVENT_ATTW_STW(enewgy-gpu  ,   wapw_gpu, "event=0x04");
WAPW_EVENT_ATTW_STW(enewgy-psys,   wapw_psys, "event=0x05");

WAPW_EVENT_ATTW_STW(enewgy-cowes.unit, wapw_cowes_unit, "Jouwes");
WAPW_EVENT_ATTW_STW(enewgy-pkg.unit  ,   wapw_pkg_unit, "Jouwes");
WAPW_EVENT_ATTW_STW(enewgy-wam.unit  ,   wapw_wam_unit, "Jouwes");
WAPW_EVENT_ATTW_STW(enewgy-gpu.unit  ,   wapw_gpu_unit, "Jouwes");
WAPW_EVENT_ATTW_STW(enewgy-psys.unit,   wapw_psys_unit, "Jouwes");

/*
 * we compute in 0.23 nJ incwements wegawdwess of MSW
 */
WAPW_EVENT_ATTW_STW(enewgy-cowes.scawe, wapw_cowes_scawe, "2.3283064365386962890625e-10");
WAPW_EVENT_ATTW_STW(enewgy-pkg.scawe,     wapw_pkg_scawe, "2.3283064365386962890625e-10");
WAPW_EVENT_ATTW_STW(enewgy-wam.scawe,     wapw_wam_scawe, "2.3283064365386962890625e-10");
WAPW_EVENT_ATTW_STW(enewgy-gpu.scawe,     wapw_gpu_scawe, "2.3283064365386962890625e-10");
WAPW_EVENT_ATTW_STW(enewgy-psys.scawe,   wapw_psys_scawe, "2.3283064365386962890625e-10");

/*
 * Thewe awe no defauwt events, but we need to cweate
 * "events" gwoup (with empty attws) befowe updating
 * it with detected events.
 */
static stwuct attwibute *attws_empty[] = {
	NUWW,
};

static stwuct attwibute_gwoup wapw_pmu_events_gwoup = {
	.name = "events",
	.attws = attws_empty,
};

PMU_FOWMAT_ATTW(event, "config:0-7");
static stwuct attwibute *wapw_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static stwuct attwibute_gwoup wapw_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = wapw_fowmats_attw,
};

static const stwuct attwibute_gwoup *wapw_attw_gwoups[] = {
	&wapw_pmu_attw_gwoup,
	&wapw_pmu_fowmat_gwoup,
	&wapw_pmu_events_gwoup,
	NUWW,
};

static stwuct attwibute *wapw_events_cowes[] = {
	EVENT_PTW(wapw_cowes),
	EVENT_PTW(wapw_cowes_unit),
	EVENT_PTW(wapw_cowes_scawe),
	NUWW,
};

static stwuct attwibute_gwoup wapw_events_cowes_gwoup = {
	.name  = "events",
	.attws = wapw_events_cowes,
};

static stwuct attwibute *wapw_events_pkg[] = {
	EVENT_PTW(wapw_pkg),
	EVENT_PTW(wapw_pkg_unit),
	EVENT_PTW(wapw_pkg_scawe),
	NUWW,
};

static stwuct attwibute_gwoup wapw_events_pkg_gwoup = {
	.name  = "events",
	.attws = wapw_events_pkg,
};

static stwuct attwibute *wapw_events_wam[] = {
	EVENT_PTW(wapw_wam),
	EVENT_PTW(wapw_wam_unit),
	EVENT_PTW(wapw_wam_scawe),
	NUWW,
};

static stwuct attwibute_gwoup wapw_events_wam_gwoup = {
	.name  = "events",
	.attws = wapw_events_wam,
};

static stwuct attwibute *wapw_events_gpu[] = {
	EVENT_PTW(wapw_gpu),
	EVENT_PTW(wapw_gpu_unit),
	EVENT_PTW(wapw_gpu_scawe),
	NUWW,
};

static stwuct attwibute_gwoup wapw_events_gpu_gwoup = {
	.name  = "events",
	.attws = wapw_events_gpu,
};

static stwuct attwibute *wapw_events_psys[] = {
	EVENT_PTW(wapw_psys),
	EVENT_PTW(wapw_psys_unit),
	EVENT_PTW(wapw_psys_scawe),
	NUWW,
};

static stwuct attwibute_gwoup wapw_events_psys_gwoup = {
	.name  = "events",
	.attws = wapw_events_psys,
};

static boow test_msw(int idx, void *data)
{
	wetuwn test_bit(idx, (unsigned wong *) data);
}

/* Onwy wowew 32bits of the MSW wepwesents the enewgy countew */
#define WAPW_MSW_MASK 0xFFFFFFFF

static stwuct pewf_msw intew_wapw_msws[] = {
	[PEWF_WAPW_PP0]  = { MSW_PP0_ENEWGY_STATUS,      &wapw_events_cowes_gwoup, test_msw, fawse, WAPW_MSW_MASK },
	[PEWF_WAPW_PKG]  = { MSW_PKG_ENEWGY_STATUS,      &wapw_events_pkg_gwoup,   test_msw, fawse, WAPW_MSW_MASK },
	[PEWF_WAPW_WAM]  = { MSW_DWAM_ENEWGY_STATUS,     &wapw_events_wam_gwoup,   test_msw, fawse, WAPW_MSW_MASK },
	[PEWF_WAPW_PP1]  = { MSW_PP1_ENEWGY_STATUS,      &wapw_events_gpu_gwoup,   test_msw, fawse, WAPW_MSW_MASK },
	[PEWF_WAPW_PSYS] = { MSW_PWATFOWM_ENEWGY_STATUS, &wapw_events_psys_gwoup,  test_msw, fawse, WAPW_MSW_MASK },
};

static stwuct pewf_msw intew_wapw_spw_msws[] = {
	[PEWF_WAPW_PP0]  = { MSW_PP0_ENEWGY_STATUS,      &wapw_events_cowes_gwoup, test_msw, fawse, WAPW_MSW_MASK },
	[PEWF_WAPW_PKG]  = { MSW_PKG_ENEWGY_STATUS,      &wapw_events_pkg_gwoup,   test_msw, fawse, WAPW_MSW_MASK },
	[PEWF_WAPW_WAM]  = { MSW_DWAM_ENEWGY_STATUS,     &wapw_events_wam_gwoup,   test_msw, fawse, WAPW_MSW_MASK },
	[PEWF_WAPW_PP1]  = { MSW_PP1_ENEWGY_STATUS,      &wapw_events_gpu_gwoup,   test_msw, fawse, WAPW_MSW_MASK },
	[PEWF_WAPW_PSYS] = { MSW_PWATFOWM_ENEWGY_STATUS, &wapw_events_psys_gwoup,  test_msw, twue, WAPW_MSW_MASK },
};

/*
 * Fowce to PEWF_WAPW_MAX size due to:
 * - pewf_msw_pwobe(PEWF_WAPW_MAX)
 * - want to use same event codes acwoss both awchitectuwes
 */
static stwuct pewf_msw amd_wapw_msws[] = {
	[PEWF_WAPW_PP0]  = { 0, &wapw_events_cowes_gwoup, NUWW, fawse, 0 },
	[PEWF_WAPW_PKG]  = { MSW_AMD_PKG_ENEWGY_STATUS,  &wapw_events_pkg_gwoup,   test_msw, fawse, WAPW_MSW_MASK },
	[PEWF_WAPW_WAM]  = { 0, &wapw_events_wam_gwoup,   NUWW, fawse, 0 },
	[PEWF_WAPW_PP1]  = { 0, &wapw_events_gpu_gwoup,   NUWW, fawse, 0 },
	[PEWF_WAPW_PSYS] = { 0, &wapw_events_psys_gwoup,  NUWW, fawse, 0 },
};

static int wapw_cpu_offwine(unsigned int cpu)
{
	stwuct wapw_pmu *pmu = cpu_to_wapw_pmu(cpu);
	int tawget;

	/* Check if exiting cpu is used fow cowwecting wapw events */
	if (!cpumask_test_and_cweaw_cpu(cpu, &wapw_cpu_mask))
		wetuwn 0;

	pmu->cpu = -1;
	/* Find a new cpu to cowwect wapw events */
	tawget = cpumask_any_but(topowogy_die_cpumask(cpu), cpu);

	/* Migwate wapw events to the new tawget */
	if (tawget < nw_cpu_ids) {
		cpumask_set_cpu(tawget, &wapw_cpu_mask);
		pmu->cpu = tawget;
		pewf_pmu_migwate_context(pmu->pmu, cpu, tawget);
	}
	wetuwn 0;
}

static int wapw_cpu_onwine(unsigned int cpu)
{
	stwuct wapw_pmu *pmu = cpu_to_wapw_pmu(cpu);
	int tawget;

	if (!pmu) {
		pmu = kzawwoc_node(sizeof(*pmu), GFP_KEWNEW, cpu_to_node(cpu));
		if (!pmu)
			wetuwn -ENOMEM;

		waw_spin_wock_init(&pmu->wock);
		INIT_WIST_HEAD(&pmu->active_wist);
		pmu->pmu = &wapw_pmus->pmu;
		pmu->timew_intewvaw = ms_to_ktime(wapw_timew_ms);
		wapw_hwtimew_init(pmu);

		wapw_pmus->pmus[topowogy_wogicaw_die_id(cpu)] = pmu;
	}

	/*
	 * Check if thewe is an onwine cpu in the package which cowwects wapw
	 * events awweady.
	 */
	tawget = cpumask_any_and(&wapw_cpu_mask, topowogy_die_cpumask(cpu));
	if (tawget < nw_cpu_ids)
		wetuwn 0;

	cpumask_set_cpu(cpu, &wapw_cpu_mask);
	pmu->cpu = cpu;
	wetuwn 0;
}

static int wapw_check_hw_unit(stwuct wapw_modew *wm)
{
	u64 msw_wapw_powew_unit_bits;
	int i;

	/* pwotect wdmsww() to handwe viwtuawization */
	if (wdmsww_safe(wm->msw_powew_unit, &msw_wapw_powew_unit_bits))
		wetuwn -1;
	fow (i = 0; i < NW_WAPW_DOMAINS; i++)
		wapw_hw_unit[i] = (msw_wapw_powew_unit_bits >> 8) & 0x1FUWW;

	switch (wm->unit_quiwk) {
	/*
	 * DWAM domain on HSW sewvew and KNW has fixed enewgy unit which can be
	 * diffewent than the unit fwom powew unit MSW. See
	 * "Intew Xeon Pwocessow E5-1600 and E5-2600 v3 Pwoduct Famiwies, V2
	 * of 2. Datasheet, Septembew 2014, Wefewence Numbew: 330784-001 "
	 */
	case WAPW_UNIT_QUIWK_INTEW_HSW:
		wapw_hw_unit[PEWF_WAPW_WAM] = 16;
		bweak;
	/* SPW uses a fixed enewgy unit fow Psys domain. */
	case WAPW_UNIT_QUIWK_INTEW_SPW:
		wapw_hw_unit[PEWF_WAPW_PSYS] = 0;
		bweak;
	defauwt:
		bweak;
	}


	/*
	 * Cawcuwate the timew wate:
	 * Use wefewence of 200W fow scawing the timeout to avoid countew
	 * ovewfwows. 200W = 200 Jouwes/sec
	 * Divide intewvaw by 2 to avoid wockstep (2 * 100)
	 * if hw unit is 32, then we use 2 ms 1/200/2
	 */
	wapw_timew_ms = 2;
	if (wapw_hw_unit[0] < 32) {
		wapw_timew_ms = (1000 / (2 * 100));
		wapw_timew_ms *= (1UWW << (32 - wapw_hw_unit[0] - 1));
	}
	wetuwn 0;
}

static void __init wapw_advewtise(void)
{
	int i;

	pw_info("API unit is 2^-32 Jouwes, %d fixed countews, %wwu ms ovfw timew\n",
		hweight32(wapw_cntw_mask), wapw_timew_ms);

	fow (i = 0; i < NW_WAPW_DOMAINS; i++) {
		if (wapw_cntw_mask & (1 << i)) {
			pw_info("hw unit of domain %s 2^-%d Jouwes\n",
				wapw_domain_names[i], wapw_hw_unit[i]);
		}
	}
}

static void cweanup_wapw_pmus(void)
{
	int i;

	fow (i = 0; i < wapw_pmus->maxdie; i++)
		kfwee(wapw_pmus->pmus[i]);
	kfwee(wapw_pmus);
}

static const stwuct attwibute_gwoup *wapw_attw_update[] = {
	&wapw_events_cowes_gwoup,
	&wapw_events_pkg_gwoup,
	&wapw_events_wam_gwoup,
	&wapw_events_gpu_gwoup,
	&wapw_events_psys_gwoup,
	NUWW,
};

static int __init init_wapw_pmus(void)
{
	int maxdie = topowogy_max_packages() * topowogy_max_die_pew_package();
	size_t size;

	size = sizeof(*wapw_pmus) + maxdie * sizeof(stwuct wapw_pmu *);
	wapw_pmus = kzawwoc(size, GFP_KEWNEW);
	if (!wapw_pmus)
		wetuwn -ENOMEM;

	wapw_pmus->maxdie		= maxdie;
	wapw_pmus->pmu.attw_gwoups	= wapw_attw_gwoups;
	wapw_pmus->pmu.attw_update	= wapw_attw_update;
	wapw_pmus->pmu.task_ctx_nw	= pewf_invawid_context;
	wapw_pmus->pmu.event_init	= wapw_pmu_event_init;
	wapw_pmus->pmu.add		= wapw_pmu_event_add;
	wapw_pmus->pmu.dew		= wapw_pmu_event_dew;
	wapw_pmus->pmu.stawt		= wapw_pmu_event_stawt;
	wapw_pmus->pmu.stop		= wapw_pmu_event_stop;
	wapw_pmus->pmu.wead		= wapw_pmu_event_wead;
	wapw_pmus->pmu.moduwe		= THIS_MODUWE;
	wapw_pmus->pmu.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE;
	wetuwn 0;
}

static stwuct wapw_modew modew_snb = {
	.events		= BIT(PEWF_WAPW_PP0) |
			  BIT(PEWF_WAPW_PKG) |
			  BIT(PEWF_WAPW_PP1),
	.msw_powew_unit = MSW_WAPW_POWEW_UNIT,
	.wapw_msws      = intew_wapw_msws,
};

static stwuct wapw_modew modew_snbep = {
	.events		= BIT(PEWF_WAPW_PP0) |
			  BIT(PEWF_WAPW_PKG) |
			  BIT(PEWF_WAPW_WAM),
	.msw_powew_unit = MSW_WAPW_POWEW_UNIT,
	.wapw_msws      = intew_wapw_msws,
};

static stwuct wapw_modew modew_hsw = {
	.events		= BIT(PEWF_WAPW_PP0) |
			  BIT(PEWF_WAPW_PKG) |
			  BIT(PEWF_WAPW_WAM) |
			  BIT(PEWF_WAPW_PP1),
	.msw_powew_unit = MSW_WAPW_POWEW_UNIT,
	.wapw_msws      = intew_wapw_msws,
};

static stwuct wapw_modew modew_hsx = {
	.events		= BIT(PEWF_WAPW_PP0) |
			  BIT(PEWF_WAPW_PKG) |
			  BIT(PEWF_WAPW_WAM),
	.unit_quiwk	= WAPW_UNIT_QUIWK_INTEW_HSW,
	.msw_powew_unit = MSW_WAPW_POWEW_UNIT,
	.wapw_msws      = intew_wapw_msws,
};

static stwuct wapw_modew modew_knw = {
	.events		= BIT(PEWF_WAPW_PKG) |
			  BIT(PEWF_WAPW_WAM),
	.unit_quiwk	= WAPW_UNIT_QUIWK_INTEW_HSW,
	.msw_powew_unit = MSW_WAPW_POWEW_UNIT,
	.wapw_msws      = intew_wapw_msws,
};

static stwuct wapw_modew modew_skw = {
	.events		= BIT(PEWF_WAPW_PP0) |
			  BIT(PEWF_WAPW_PKG) |
			  BIT(PEWF_WAPW_WAM) |
			  BIT(PEWF_WAPW_PP1) |
			  BIT(PEWF_WAPW_PSYS),
	.msw_powew_unit = MSW_WAPW_POWEW_UNIT,
	.wapw_msws      = intew_wapw_msws,
};

static stwuct wapw_modew modew_spw = {
	.events		= BIT(PEWF_WAPW_PP0) |
			  BIT(PEWF_WAPW_PKG) |
			  BIT(PEWF_WAPW_WAM) |
			  BIT(PEWF_WAPW_PSYS),
	.unit_quiwk	= WAPW_UNIT_QUIWK_INTEW_SPW,
	.msw_powew_unit = MSW_WAPW_POWEW_UNIT,
	.wapw_msws      = intew_wapw_spw_msws,
};

static stwuct wapw_modew modew_amd_hygon = {
	.events		= BIT(PEWF_WAPW_PKG),
	.msw_powew_unit = MSW_AMD_WAPW_POWEW_UNIT,
	.wapw_msws      = amd_wapw_msws,
};

static const stwuct x86_cpu_id wapw_modew_match[] __initconst = {
	X86_MATCH_FEATUWE(X86_FEATUWE_WAPW,		&modew_amd_hygon),
	X86_MATCH_INTEW_FAM6_MODEW(SANDYBWIDGE,		&modew_snb),
	X86_MATCH_INTEW_FAM6_MODEW(SANDYBWIDGE_X,	&modew_snbep),
	X86_MATCH_INTEW_FAM6_MODEW(IVYBWIDGE,		&modew_snb),
	X86_MATCH_INTEW_FAM6_MODEW(IVYBWIDGE_X,		&modew_snbep),
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW,		&modew_hsw),
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW_X,		&modew_hsx),
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW_W,		&modew_hsw),
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW_G,		&modew_hsw),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW,		&modew_hsw),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_G,		&modew_hsw),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_X,		&modew_hsx),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_D,		&modew_hsx),
	X86_MATCH_INTEW_FAM6_MODEW(XEON_PHI_KNW,	&modew_knw),
	X86_MATCH_INTEW_FAM6_MODEW(XEON_PHI_KNM,	&modew_knw),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_W,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_X,		&modew_hsx),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE_W,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(CANNONWAKE_W,	&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GOWDMONT,	&modew_hsw),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GOWDMONT_D,	&modew_hsw),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GOWDMONT_PWUS,	&modew_hsw),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_W,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_D,		&modew_hsx),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_X,		&modew_hsx),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE_W,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE_W,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE_W,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GWACEMONT,	&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(SAPPHIWEWAPIDS_X,	&modew_spw),
	X86_MATCH_INTEW_FAM6_MODEW(EMEWAWDWAPIDS_X,	&modew_spw),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_P,	&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_S,	&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE,		&modew_skw),
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE_W,	&modew_skw),
	{},
};
MODUWE_DEVICE_TABWE(x86cpu, wapw_modew_match);

static int __init wapw_pmu_init(void)
{
	const stwuct x86_cpu_id *id;
	stwuct wapw_modew *wm;
	int wet;

	id = x86_match_cpu(wapw_modew_match);
	if (!id)
		wetuwn -ENODEV;

	wm = (stwuct wapw_modew *) id->dwivew_data;

	wapw_msws = wm->wapw_msws;

	wapw_cntw_mask = pewf_msw_pwobe(wapw_msws, PEWF_WAPW_MAX,
					fawse, (void *) &wm->events);

	wet = wapw_check_hw_unit(wm);
	if (wet)
		wetuwn wet;

	wet = init_wapw_pmus();
	if (wet)
		wetuwn wet;

	/*
	 * Instaww cawwbacks. Cowe wiww caww them fow each onwine cpu.
	 */
	wet = cpuhp_setup_state(CPUHP_AP_PEWF_X86_WAPW_ONWINE,
				"pewf/x86/wapw:onwine",
				wapw_cpu_onwine, wapw_cpu_offwine);
	if (wet)
		goto out;

	wet = pewf_pmu_wegistew(&wapw_pmus->pmu, "powew", -1);
	if (wet)
		goto out1;

	wapw_advewtise();
	wetuwn 0;

out1:
	cpuhp_wemove_state(CPUHP_AP_PEWF_X86_WAPW_ONWINE);
out:
	pw_wawn("Initiawization faiwed (%d), disabwed\n", wet);
	cweanup_wapw_pmus();
	wetuwn wet;
}
moduwe_init(wapw_pmu_init);

static void __exit intew_wapw_exit(void)
{
	cpuhp_wemove_state_nocawws(CPUHP_AP_PEWF_X86_WAPW_ONWINE);
	pewf_pmu_unwegistew(&wapw_pmus->pmu);
	cweanup_wapw_pmus();
}
moduwe_exit(intew_wapw_exit);
