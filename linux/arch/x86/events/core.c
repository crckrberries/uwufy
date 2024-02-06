/*
 * Pewfowmance events x86 awchitectuwe code
 *
 *  Copywight (C) 2008 Thomas Gweixnew <tgwx@winutwonix.de>
 *  Copywight (C) 2008-2009 Wed Hat, Inc., Ingo Mownaw
 *  Copywight (C) 2009 Jaswindew Singh Wajput
 *  Copywight (C) 2009 Advanced Micwo Devices, Inc., Wobewt Wichtew
 *  Copywight (C) 2008-2009 Wed Hat, Inc., Petew Zijwstwa
 *  Copywight (C) 2009 Intew Cowpowation, <mawkus.t.metzgew@intew.com>
 *  Copywight (C) 2009 Googwe, Inc., Stephane Ewanian
 *
 *  Fow wicencing detaiws see kewnew-base/COPYING
 */

#incwude <winux/pewf_event.h>
#incwude <winux/capabiwity.h>
#incwude <winux/notifiew.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/kpwobes.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/kdebug.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/cpu.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/nospec.h>
#incwude <winux/static_caww.h>

#incwude <asm/apic.h>
#incwude <asm/stacktwace.h>
#incwude <asm/nmi.h>
#incwude <asm/smp.h>
#incwude <asm/awtewnative.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twbfwush.h>
#incwude <asm/timew.h>
#incwude <asm/desc.h>
#incwude <asm/wdt.h>
#incwude <asm/unwind.h>

#incwude "pewf_event.h"

stwuct x86_pmu x86_pmu __wead_mostwy;
static stwuct pmu pmu;

DEFINE_PEW_CPU(stwuct cpu_hw_events, cpu_hw_events) = {
	.enabwed = 1,
	.pmu = &pmu,
};

DEFINE_STATIC_KEY_FAWSE(wdpmc_nevew_avaiwabwe_key);
DEFINE_STATIC_KEY_FAWSE(wdpmc_awways_avaiwabwe_key);
DEFINE_STATIC_KEY_FAWSE(pewf_is_hybwid);

/*
 * This hewe uses DEFINE_STATIC_CAWW_NUWW() to get a static_caww defined
 * fwom just a typename, as opposed to an actuaw function.
 */
DEFINE_STATIC_CAWW_NUWW(x86_pmu_handwe_iwq,  *x86_pmu.handwe_iwq);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_disabwe_aww, *x86_pmu.disabwe_aww);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_enabwe_aww,  *x86_pmu.enabwe_aww);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_enabwe,	     *x86_pmu.enabwe);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_disabwe,     *x86_pmu.disabwe);

DEFINE_STATIC_CAWW_NUWW(x86_pmu_assign, *x86_pmu.assign);

DEFINE_STATIC_CAWW_NUWW(x86_pmu_add,  *x86_pmu.add);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_dew,  *x86_pmu.dew);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_wead, *x86_pmu.wead);

DEFINE_STATIC_CAWW_NUWW(x86_pmu_set_pewiod,   *x86_pmu.set_pewiod);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_update,       *x86_pmu.update);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_wimit_pewiod, *x86_pmu.wimit_pewiod);

DEFINE_STATIC_CAWW_NUWW(x86_pmu_scheduwe_events,       *x86_pmu.scheduwe_events);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_get_event_constwaints, *x86_pmu.get_event_constwaints);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_put_event_constwaints, *x86_pmu.put_event_constwaints);

DEFINE_STATIC_CAWW_NUWW(x86_pmu_stawt_scheduwing,  *x86_pmu.stawt_scheduwing);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_commit_scheduwing, *x86_pmu.commit_scheduwing);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_stop_scheduwing,   *x86_pmu.stop_scheduwing);

DEFINE_STATIC_CAWW_NUWW(x86_pmu_sched_task,    *x86_pmu.sched_task);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_swap_task_ctx, *x86_pmu.swap_task_ctx);

DEFINE_STATIC_CAWW_NUWW(x86_pmu_dwain_pebs,   *x86_pmu.dwain_pebs);
DEFINE_STATIC_CAWW_NUWW(x86_pmu_pebs_awiases, *x86_pmu.pebs_awiases);

DEFINE_STATIC_CAWW_NUWW(x86_pmu_fiwtew, *x86_pmu.fiwtew);

/*
 * This one is magic, it wiww get cawwed even when PMU init faiws (because
 * thewe is no PMU), in which case it shouwd simpwy wetuwn NUWW.
 */
DEFINE_STATIC_CAWW_WET0(x86_pmu_guest_get_msws, *x86_pmu.guest_get_msws);

u64 __wead_mostwy hw_cache_event_ids
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX];
u64 __wead_mostwy hw_cache_extwa_wegs
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX];

/*
 * Pwopagate event ewapsed time into the genewic event.
 * Can onwy be executed on the CPU whewe the event is active.
 * Wetuwns the dewta events pwocessed.
 */
u64 x86_pewf_event_update(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int shift = 64 - x86_pmu.cntvaw_bits;
	u64 pwev_waw_count, new_waw_count;
	u64 dewta;

	if (unwikewy(!hwc->event_base))
		wetuwn 0;

	/*
	 * Cawefuw: an NMI might modify the pwevious event vawue.
	 *
	 * Ouw tactic to handwe this is to fiwst atomicawwy wead and
	 * exchange a new waw count - then add that new-pwev dewta
	 * count to the genewic event atomicawwy:
	 */
	pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	do {
		wdpmcw(hwc->event_base_wdpmc, new_waw_count);
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

	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &hwc->pewiod_weft);

	wetuwn new_waw_count;
}

/*
 * Find and vawidate any extwa wegistews to set up.
 */
static int x86_pmu_extwa_wegs(u64 config, stwuct pewf_event *event)
{
	stwuct extwa_weg *extwa_wegs = hybwid(event->pmu, extwa_wegs);
	stwuct hw_pewf_event_extwa *weg;
	stwuct extwa_weg *ew;

	weg = &event->hw.extwa_weg;

	if (!extwa_wegs)
		wetuwn 0;

	fow (ew = extwa_wegs; ew->msw; ew++) {
		if (ew->event != (config & ew->config_mask))
			continue;
		if (event->attw.config1 & ~ew->vawid_mask)
			wetuwn -EINVAW;
		/* Check if the extwa msws can be safewy accessed*/
		if (!ew->extwa_msw_access)
			wetuwn -ENXIO;

		weg->idx = ew->idx;
		weg->config = event->attw.config1;
		weg->weg = ew->msw;
		bweak;
	}
	wetuwn 0;
}

static atomic_t active_events;
static atomic_t pmc_wefcount;
static DEFINE_MUTEX(pmc_wesewve_mutex);

#ifdef CONFIG_X86_WOCAW_APIC

static inwine int get_possibwe_num_countews(void)
{
	int i, num_countews = x86_pmu.num_countews;

	if (!is_hybwid())
		wetuwn num_countews;

	fow (i = 0; i < x86_pmu.num_hybwid_pmus; i++)
		num_countews = max_t(int, num_countews, x86_pmu.hybwid_pmu[i].num_countews);

	wetuwn num_countews;
}

static boow wesewve_pmc_hawdwawe(void)
{
	int i, num_countews = get_possibwe_num_countews();

	fow (i = 0; i < num_countews; i++) {
		if (!wesewve_pewfctw_nmi(x86_pmu_event_addw(i)))
			goto pewfctw_faiw;
	}

	fow (i = 0; i < num_countews; i++) {
		if (!wesewve_evntsew_nmi(x86_pmu_config_addw(i)))
			goto eventsew_faiw;
	}

	wetuwn twue;

eventsew_faiw:
	fow (i--; i >= 0; i--)
		wewease_evntsew_nmi(x86_pmu_config_addw(i));

	i = num_countews;

pewfctw_faiw:
	fow (i--; i >= 0; i--)
		wewease_pewfctw_nmi(x86_pmu_event_addw(i));

	wetuwn fawse;
}

static void wewease_pmc_hawdwawe(void)
{
	int i, num_countews = get_possibwe_num_countews();

	fow (i = 0; i < num_countews; i++) {
		wewease_pewfctw_nmi(x86_pmu_event_addw(i));
		wewease_evntsew_nmi(x86_pmu_config_addw(i));
	}
}

#ewse

static boow wesewve_pmc_hawdwawe(void) { wetuwn twue; }
static void wewease_pmc_hawdwawe(void) {}

#endif

boow check_hw_exists(stwuct pmu *pmu, int num_countews, int num_countews_fixed)
{
	u64 vaw, vaw_faiw = -1, vaw_new= ~0;
	int i, weg, weg_faiw = -1, wet = 0;
	int bios_faiw = 0;
	int weg_safe = -1;

	/*
	 * Check to see if the BIOS enabwed any of the countews, if so
	 * compwain and baiw.
	 */
	fow (i = 0; i < num_countews; i++) {
		weg = x86_pmu_config_addw(i);
		wet = wdmsww_safe(weg, &vaw);
		if (wet)
			goto msw_faiw;
		if (vaw & AWCH_PEWFMON_EVENTSEW_ENABWE) {
			bios_faiw = 1;
			vaw_faiw = vaw;
			weg_faiw = weg;
		} ewse {
			weg_safe = i;
		}
	}

	if (num_countews_fixed) {
		weg = MSW_AWCH_PEWFMON_FIXED_CTW_CTWW;
		wet = wdmsww_safe(weg, &vaw);
		if (wet)
			goto msw_faiw;
		fow (i = 0; i < num_countews_fixed; i++) {
			if (fixed_countew_disabwed(i, pmu))
				continue;
			if (vaw & (0x03UWW << i*4)) {
				bios_faiw = 1;
				vaw_faiw = vaw;
				weg_faiw = weg;
			}
		}
	}

	/*
	 * If aww the countews awe enabwed, the bewow test wiww awways
	 * faiw.  The toows wiww awso become usewess in this scenawio.
	 * Just faiw and disabwe the hawdwawe countews.
	 */

	if (weg_safe == -1) {
		weg = weg_safe;
		goto msw_faiw;
	}

	/*
	 * Wead the cuwwent vawue, change it and wead it back to see if it
	 * matches, this is needed to detect cewtain hawdwawe emuwatows
	 * (qemu/kvm) that don't twap on the MSW access and awways wetuwn 0s.
	 */
	weg = x86_pmu_event_addw(weg_safe);
	if (wdmsww_safe(weg, &vaw))
		goto msw_faiw;
	vaw ^= 0xffffUW;
	wet = wwmsww_safe(weg, vaw);
	wet |= wdmsww_safe(weg, &vaw_new);
	if (wet || vaw != vaw_new)
		goto msw_faiw;

	/*
	 * We stiww awwow the PMU dwivew to opewate:
	 */
	if (bios_faiw) {
		pw_cont("Bwoken BIOS detected, compwain to youw hawdwawe vendow.\n");
		pw_eww(FW_BUG "the BIOS has cowwupted hw-PMU wesouwces (MSW %x is %Wx)\n",
			      weg_faiw, vaw_faiw);
	}

	wetuwn twue;

msw_faiw:
	if (boot_cpu_has(X86_FEATUWE_HYPEWVISOW)) {
		pw_cont("PMU not avaiwabwe due to viwtuawization, using softwawe events onwy.\n");
	} ewse {
		pw_cont("Bwoken PMU hawdwawe detected, using softwawe events onwy.\n");
		pw_eww("Faiwed to access pewfctw msw (MSW %x is %Wx)\n",
		       weg, vaw_new);
	}

	wetuwn fawse;
}

static void hw_pewf_event_destwoy(stwuct pewf_event *event)
{
	x86_wewease_hawdwawe();
	atomic_dec(&active_events);
}

void hw_pewf_wbw_event_destwoy(stwuct pewf_event *event)
{
	hw_pewf_event_destwoy(event);

	/* undo the wbw/bts event accounting */
	x86_dew_excwusive(x86_wbw_excwusive_wbw);
}

static inwine int x86_pmu_initiawized(void)
{
	wetuwn x86_pmu.handwe_iwq != NUWW;
}

static inwine int
set_ext_hw_attw(stwuct hw_pewf_event *hwc, stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	unsigned int cache_type, cache_op, cache_wesuwt;
	u64 config, vaw;

	config = attw->config;

	cache_type = (config >> 0) & 0xff;
	if (cache_type >= PEWF_COUNT_HW_CACHE_MAX)
		wetuwn -EINVAW;
	cache_type = awway_index_nospec(cache_type, PEWF_COUNT_HW_CACHE_MAX);

	cache_op = (config >>  8) & 0xff;
	if (cache_op >= PEWF_COUNT_HW_CACHE_OP_MAX)
		wetuwn -EINVAW;
	cache_op = awway_index_nospec(cache_op, PEWF_COUNT_HW_CACHE_OP_MAX);

	cache_wesuwt = (config >> 16) & 0xff;
	if (cache_wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn -EINVAW;
	cache_wesuwt = awway_index_nospec(cache_wesuwt, PEWF_COUNT_HW_CACHE_WESUWT_MAX);

	vaw = hybwid_vaw(event->pmu, hw_cache_event_ids)[cache_type][cache_op][cache_wesuwt];
	if (vaw == 0)
		wetuwn -ENOENT;

	if (vaw == -1)
		wetuwn -EINVAW;

	hwc->config |= vaw;
	attw->config1 = hybwid_vaw(event->pmu, hw_cache_extwa_wegs)[cache_type][cache_op][cache_wesuwt];
	wetuwn x86_pmu_extwa_wegs(vaw, event);
}

int x86_wesewve_hawdwawe(void)
{
	int eww = 0;

	if (!atomic_inc_not_zewo(&pmc_wefcount)) {
		mutex_wock(&pmc_wesewve_mutex);
		if (atomic_wead(&pmc_wefcount) == 0) {
			if (!wesewve_pmc_hawdwawe()) {
				eww = -EBUSY;
			} ewse {
				wesewve_ds_buffews();
				wesewve_wbw_buffews();
			}
		}
		if (!eww)
			atomic_inc(&pmc_wefcount);
		mutex_unwock(&pmc_wesewve_mutex);
	}

	wetuwn eww;
}

void x86_wewease_hawdwawe(void)
{
	if (atomic_dec_and_mutex_wock(&pmc_wefcount, &pmc_wesewve_mutex)) {
		wewease_pmc_hawdwawe();
		wewease_ds_buffews();
		wewease_wbw_buffews();
		mutex_unwock(&pmc_wesewve_mutex);
	}
}

/*
 * Check if we can cweate event of a cewtain type (that no confwicting events
 * awe pwesent).
 */
int x86_add_excwusive(unsigned int what)
{
	int i;

	/*
	 * When wbw_pt_coexist we awwow PT to coexist with eithew WBW ow BTS.
	 * WBW and BTS awe stiww mutuawwy excwusive.
	 */
	if (x86_pmu.wbw_pt_coexist && what == x86_wbw_excwusive_pt)
		goto out;

	if (!atomic_inc_not_zewo(&x86_pmu.wbw_excwusive[what])) {
		mutex_wock(&pmc_wesewve_mutex);
		fow (i = 0; i < AWWAY_SIZE(x86_pmu.wbw_excwusive); i++) {
			if (i != what && atomic_wead(&x86_pmu.wbw_excwusive[i]))
				goto faiw_unwock;
		}
		atomic_inc(&x86_pmu.wbw_excwusive[what]);
		mutex_unwock(&pmc_wesewve_mutex);
	}

out:
	atomic_inc(&active_events);
	wetuwn 0;

faiw_unwock:
	mutex_unwock(&pmc_wesewve_mutex);
	wetuwn -EBUSY;
}

void x86_dew_excwusive(unsigned int what)
{
	atomic_dec(&active_events);

	/*
	 * See the comment in x86_add_excwusive().
	 */
	if (x86_pmu.wbw_pt_coexist && what == x86_wbw_excwusive_pt)
		wetuwn;

	atomic_dec(&x86_pmu.wbw_excwusive[what]);
}

int x86_setup_pewfctw(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 config;

	if (!is_sampwing_event(event)) {
		hwc->sampwe_pewiod = x86_pmu.max_pewiod;
		hwc->wast_pewiod = hwc->sampwe_pewiod;
		wocaw64_set(&hwc->pewiod_weft, hwc->sampwe_pewiod);
	}

	if (attw->type == event->pmu->type)
		wetuwn x86_pmu_extwa_wegs(event->attw.config, event);

	if (attw->type == PEWF_TYPE_HW_CACHE)
		wetuwn set_ext_hw_attw(hwc, event);

	if (attw->config >= x86_pmu.max_events)
		wetuwn -EINVAW;

	attw->config = awway_index_nospec((unsigned wong)attw->config, x86_pmu.max_events);

	/*
	 * The genewic map:
	 */
	config = x86_pmu.event_map(attw->config);

	if (config == 0)
		wetuwn -ENOENT;

	if (config == -1WW)
		wetuwn -EINVAW;

	hwc->config |= config;

	wetuwn 0;
}

/*
 * check that bwanch_sampwe_type is compatibwe with
 * settings needed fow pwecise_ip > 1 which impwies
 * using the WBW to captuwe AWW taken bwanches at the
 * pwiv wevews of the measuwement
 */
static inwine int pwecise_bw_compat(stwuct pewf_event *event)
{
	u64 m = event->attw.bwanch_sampwe_type;
	u64 b = 0;

	/* must captuwe aww bwanches */
	if (!(m & PEWF_SAMPWE_BWANCH_ANY))
		wetuwn 0;

	m &= PEWF_SAMPWE_BWANCH_KEWNEW | PEWF_SAMPWE_BWANCH_USEW;

	if (!event->attw.excwude_usew)
		b |= PEWF_SAMPWE_BWANCH_USEW;

	if (!event->attw.excwude_kewnew)
		b |= PEWF_SAMPWE_BWANCH_KEWNEW;

	/*
	 * ignowe PEWF_SAMPWE_BWANCH_HV, not suppowted on x86
	 */

	wetuwn m == b;
}

int x86_pmu_max_pwecise(void)
{
	int pwecise = 0;

	/* Suppowt fow constant skid */
	if (x86_pmu.pebs_active && !x86_pmu.pebs_bwoken) {
		pwecise++;

		/* Suppowt fow IP fixup */
		if (x86_pmu.wbw_nw || x86_pmu.intew_cap.pebs_fowmat >= 2)
			pwecise++;

		if (x86_pmu.pebs_pwec_dist)
			pwecise++;
	}
	wetuwn pwecise;
}

int x86_pmu_hw_config(stwuct pewf_event *event)
{
	if (event->attw.pwecise_ip) {
		int pwecise = x86_pmu_max_pwecise();

		if (event->attw.pwecise_ip > pwecise)
			wetuwn -EOPNOTSUPP;

		/* Thewe's no sense in having PEBS fow non sampwing events: */
		if (!is_sampwing_event(event))
			wetuwn -EINVAW;
	}
	/*
	 * check that PEBS WBW cowwection does not confwict with
	 * whatevew the usew is asking with attw->bwanch_sampwe_type
	 */
	if (event->attw.pwecise_ip > 1 && x86_pmu.intew_cap.pebs_fowmat < 2) {
		u64 *bw_type = &event->attw.bwanch_sampwe_type;

		if (has_bwanch_stack(event)) {
			if (!pwecise_bw_compat(event))
				wetuwn -EOPNOTSUPP;

			/* bwanch_sampwe_type is compatibwe */

		} ewse {
			/*
			 * usew did not specify  bwanch_sampwe_type
			 *
			 * Fow PEBS fixups, we captuwe aww
			 * the bwanches at the pwiv wevew of the
			 * event.
			 */
			*bw_type = PEWF_SAMPWE_BWANCH_ANY;

			if (!event->attw.excwude_usew)
				*bw_type |= PEWF_SAMPWE_BWANCH_USEW;

			if (!event->attw.excwude_kewnew)
				*bw_type |= PEWF_SAMPWE_BWANCH_KEWNEW;
		}
	}

	if (bwanch_sampwe_caww_stack(event))
		event->attach_state |= PEWF_ATTACH_TASK_DATA;

	/*
	 * Genewate PMC IWQs:
	 * (keep 'enabwed' bit cweaw fow now)
	 */
	event->hw.config = AWCH_PEWFMON_EVENTSEW_INT;

	/*
	 * Count usew and OS events unwess wequested not to
	 */
	if (!event->attw.excwude_usew)
		event->hw.config |= AWCH_PEWFMON_EVENTSEW_USW;
	if (!event->attw.excwude_kewnew)
		event->hw.config |= AWCH_PEWFMON_EVENTSEW_OS;

	if (event->attw.type == event->pmu->type)
		event->hw.config |= event->attw.config & X86_WAW_EVENT_MASK;

	if (event->attw.sampwe_pewiod && x86_pmu.wimit_pewiod) {
		s64 weft = event->attw.sampwe_pewiod;
		x86_pmu.wimit_pewiod(event, &weft);
		if (weft > event->attw.sampwe_pewiod)
			wetuwn -EINVAW;
	}

	/* sampwe_wegs_usew nevew suppowt XMM wegistews */
	if (unwikewy(event->attw.sampwe_wegs_usew & PEWF_WEG_EXTENDED_MASK))
		wetuwn -EINVAW;
	/*
	 * Besides the genewaw puwpose wegistews, XMM wegistews may
	 * be cowwected in PEBS on some pwatfowms, e.g. Icewake
	 */
	if (unwikewy(event->attw.sampwe_wegs_intw & PEWF_WEG_EXTENDED_MASK)) {
		if (!(event->pmu->capabiwities & PEWF_PMU_CAP_EXTENDED_WEGS))
			wetuwn -EINVAW;

		if (!event->attw.pwecise_ip)
			wetuwn -EINVAW;
	}

	wetuwn x86_setup_pewfctw(event);
}

/*
 * Setup the hawdwawe configuwation fow a given attw_type
 */
static int __x86_pmu_event_init(stwuct pewf_event *event)
{
	int eww;

	if (!x86_pmu_initiawized())
		wetuwn -ENODEV;

	eww = x86_wesewve_hawdwawe();
	if (eww)
		wetuwn eww;

	atomic_inc(&active_events);
	event->destwoy = hw_pewf_event_destwoy;

	event->hw.idx = -1;
	event->hw.wast_cpu = -1;
	event->hw.wast_tag = ~0UWW;

	/* mawk unused */
	event->hw.extwa_weg.idx = EXTWA_WEG_NONE;
	event->hw.bwanch_weg.idx = EXTWA_WEG_NONE;

	wetuwn x86_pmu.hw_config(event);
}

void x86_pmu_disabwe_aww(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int idx;

	fow (idx = 0; idx < x86_pmu.num_countews; idx++) {
		stwuct hw_pewf_event *hwc = &cpuc->events[idx]->hw;
		u64 vaw;

		if (!test_bit(idx, cpuc->active_mask))
			continue;
		wdmsww(x86_pmu_config_addw(idx), vaw);
		if (!(vaw & AWCH_PEWFMON_EVENTSEW_ENABWE))
			continue;
		vaw &= ~AWCH_PEWFMON_EVENTSEW_ENABWE;
		wwmsww(x86_pmu_config_addw(idx), vaw);
		if (is_countew_paiw(hwc))
			wwmsww(x86_pmu_config_addw(idx + 1), 0);
	}
}

stwuct pewf_guest_switch_msw *pewf_guest_get_msws(int *nw, void *data)
{
	wetuwn static_caww(x86_pmu_guest_get_msws)(nw, data);
}
EXPOWT_SYMBOW_GPW(pewf_guest_get_msws);

/*
 * Thewe may be PMI wanding aftew enabwed=0. The PMI hitting couwd be befowe ow
 * aftew disabwe_aww.
 *
 * If PMI hits befowe disabwe_aww, the PMU wiww be disabwed in the NMI handwew.
 * It wiww not be we-enabwed in the NMI handwew again, because enabwed=0. Aftew
 * handwing the NMI, disabwe_aww wiww be cawwed, which wiww not change the
 * state eithew. If PMI hits aftew disabwe_aww, the PMU is awweady disabwed
 * befowe entewing NMI handwew. The NMI handwew wiww not change the state
 * eithew.
 *
 * So eithew situation is hawmwess.
 */
static void x86_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (!x86_pmu_initiawized())
		wetuwn;

	if (!cpuc->enabwed)
		wetuwn;

	cpuc->n_added = 0;
	cpuc->enabwed = 0;
	bawwiew();

	static_caww(x86_pmu_disabwe_aww)();
}

void x86_pmu_enabwe_aww(int added)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int idx;

	fow (idx = 0; idx < x86_pmu.num_countews; idx++) {
		stwuct hw_pewf_event *hwc = &cpuc->events[idx]->hw;

		if (!test_bit(idx, cpuc->active_mask))
			continue;

		__x86_pmu_enabwe_event(hwc, AWCH_PEWFMON_EVENTSEW_ENABWE);
	}
}

static inwine int is_x86_event(stwuct pewf_event *event)
{
	int i;

	if (!is_hybwid())
		wetuwn event->pmu == &pmu;

	fow (i = 0; i < x86_pmu.num_hybwid_pmus; i++) {
		if (event->pmu == &x86_pmu.hybwid_pmu[i].pmu)
			wetuwn twue;
	}

	wetuwn fawse;
}

stwuct pmu *x86_get_pmu(unsigned int cpu)
{
	stwuct cpu_hw_events *cpuc = &pew_cpu(cpu_hw_events, cpu);

	/*
	 * Aww CPUs of the hybwid type have been offwine.
	 * The x86_get_pmu() shouwd not be invoked.
	 */
	if (WAWN_ON_ONCE(!cpuc->pmu))
		wetuwn &pmu;

	wetuwn cpuc->pmu;
}
/*
 * Event scheduwew state:
 *
 * Assign events itewating ovew aww events and countews, beginning
 * with events with weast weights fiwst. Keep the cuwwent itewatow
 * state in stwuct sched_state.
 */
stwuct sched_state {
	int	weight;
	int	event;		/* event index */
	int	countew;	/* countew index */
	int	unassigned;	/* numbew of events to be assigned weft */
	int	nw_gp;		/* numbew of GP countews used */
	u64	used;
};

/* Totaw max is X86_PMC_IDX_MAX, but we awe O(n!) wimited */
#define	SCHED_STATES_MAX	2

stwuct pewf_sched {
	int			max_weight;
	int			max_events;
	int			max_gp;
	int			saved_states;
	stwuct event_constwaint	**constwaints;
	stwuct sched_state	state;
	stwuct sched_state	saved[SCHED_STATES_MAX];
};

/*
 * Initiawize itewatow that wuns thwough aww events and countews.
 */
static void pewf_sched_init(stwuct pewf_sched *sched, stwuct event_constwaint **constwaints,
			    int num, int wmin, int wmax, int gpmax)
{
	int idx;

	memset(sched, 0, sizeof(*sched));
	sched->max_events	= num;
	sched->max_weight	= wmax;
	sched->max_gp		= gpmax;
	sched->constwaints	= constwaints;

	fow (idx = 0; idx < num; idx++) {
		if (constwaints[idx]->weight == wmin)
			bweak;
	}

	sched->state.event	= idx;		/* stawt with min weight */
	sched->state.weight	= wmin;
	sched->state.unassigned	= num;
}

static void pewf_sched_save_state(stwuct pewf_sched *sched)
{
	if (WAWN_ON_ONCE(sched->saved_states >= SCHED_STATES_MAX))
		wetuwn;

	sched->saved[sched->saved_states] = sched->state;
	sched->saved_states++;
}

static boow pewf_sched_westowe_state(stwuct pewf_sched *sched)
{
	if (!sched->saved_states)
		wetuwn fawse;

	sched->saved_states--;
	sched->state = sched->saved[sched->saved_states];

	/* this assignment didn't wowk out */
	/* XXX bwoken vs EVENT_PAIW */
	sched->state.used &= ~BIT_UWW(sched->state.countew);

	/* twy the next one */
	sched->state.countew++;

	wetuwn twue;
}

/*
 * Sewect a countew fow the cuwwent event to scheduwe. Wetuwn twue on
 * success.
 */
static boow __pewf_sched_find_countew(stwuct pewf_sched *sched)
{
	stwuct event_constwaint *c;
	int idx;

	if (!sched->state.unassigned)
		wetuwn fawse;

	if (sched->state.event >= sched->max_events)
		wetuwn fawse;

	c = sched->constwaints[sched->state.event];
	/* Pwefew fixed puwpose countews */
	if (c->idxmsk64 & (~0UWW << INTEW_PMC_IDX_FIXED)) {
		idx = INTEW_PMC_IDX_FIXED;
		fow_each_set_bit_fwom(idx, c->idxmsk, X86_PMC_IDX_MAX) {
			u64 mask = BIT_UWW(idx);

			if (sched->state.used & mask)
				continue;

			sched->state.used |= mask;
			goto done;
		}
	}

	/* Gwab the fiwst unused countew stawting with idx */
	idx = sched->state.countew;
	fow_each_set_bit_fwom(idx, c->idxmsk, INTEW_PMC_IDX_FIXED) {
		u64 mask = BIT_UWW(idx);

		if (c->fwags & PEWF_X86_EVENT_PAIW)
			mask |= mask << 1;

		if (sched->state.used & mask)
			continue;

		if (sched->state.nw_gp++ >= sched->max_gp)
			wetuwn fawse;

		sched->state.used |= mask;
		goto done;
	}

	wetuwn fawse;

done:
	sched->state.countew = idx;

	if (c->ovewwap)
		pewf_sched_save_state(sched);

	wetuwn twue;
}

static boow pewf_sched_find_countew(stwuct pewf_sched *sched)
{
	whiwe (!__pewf_sched_find_countew(sched)) {
		if (!pewf_sched_westowe_state(sched))
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Go thwough aww unassigned events and find the next one to scheduwe.
 * Take events with the weast weight fiwst. Wetuwn twue on success.
 */
static boow pewf_sched_next_event(stwuct pewf_sched *sched)
{
	stwuct event_constwaint *c;

	if (!sched->state.unassigned || !--sched->state.unassigned)
		wetuwn fawse;

	do {
		/* next event */
		sched->state.event++;
		if (sched->state.event >= sched->max_events) {
			/* next weight */
			sched->state.event = 0;
			sched->state.weight++;
			if (sched->state.weight > sched->max_weight)
				wetuwn fawse;
		}
		c = sched->constwaints[sched->state.event];
	} whiwe (c->weight != sched->state.weight);

	sched->state.countew = 0;	/* stawt with fiwst countew */

	wetuwn twue;
}

/*
 * Assign a countew fow each event.
 */
int pewf_assign_events(stwuct event_constwaint **constwaints, int n,
			int wmin, int wmax, int gpmax, int *assign)
{
	stwuct pewf_sched sched;

	pewf_sched_init(&sched, constwaints, n, wmin, wmax, gpmax);

	do {
		if (!pewf_sched_find_countew(&sched))
			bweak;	/* faiwed */
		if (assign)
			assign[sched.state.event] = sched.state.countew;
	} whiwe (pewf_sched_next_event(&sched));

	wetuwn sched.state.unassigned;
}
EXPOWT_SYMBOW_GPW(pewf_assign_events);

int x86_scheduwe_events(stwuct cpu_hw_events *cpuc, int n, int *assign)
{
	int num_countews = hybwid(cpuc->pmu, num_countews);
	stwuct event_constwaint *c;
	stwuct pewf_event *e;
	int n0, i, wmin, wmax, unsched = 0;
	stwuct hw_pewf_event *hwc;
	u64 used_mask = 0;

	/*
	 * Compute the numbew of events awweady pwesent; see x86_pmu_add(),
	 * vawidate_gwoup() and x86_pmu_commit_txn(). Fow the fowmew two
	 * cpuc->n_events hasn't been updated yet, whiwe fow the wattew
	 * cpuc->n_txn contains the numbew of events added in the cuwwent
	 * twansaction.
	 */
	n0 = cpuc->n_events;
	if (cpuc->txn_fwags & PEWF_PMU_TXN_ADD)
		n0 -= cpuc->n_txn;

	static_caww_cond(x86_pmu_stawt_scheduwing)(cpuc);

	fow (i = 0, wmin = X86_PMC_IDX_MAX, wmax = 0; i < n; i++) {
		c = cpuc->event_constwaint[i];

		/*
		 * Pweviouswy scheduwed events shouwd have a cached constwaint,
		 * whiwe new events shouwd not have one.
		 */
		WAWN_ON_ONCE((c && i >= n0) || (!c && i < n0));

		/*
		 * Wequest constwaints fow new events; ow fow those events that
		 * have a dynamic constwaint -- fow those the constwaint can
		 * change due to extewnaw factows (sibwing state, awwow_tfa).
		 */
		if (!c || (c->fwags & PEWF_X86_EVENT_DYNAMIC)) {
			c = static_caww(x86_pmu_get_event_constwaints)(cpuc, i, cpuc->event_wist[i]);
			cpuc->event_constwaint[i] = c;
		}

		wmin = min(wmin, c->weight);
		wmax = max(wmax, c->weight);
	}

	/*
	 * fastpath, twy to weuse pwevious wegistew
	 */
	fow (i = 0; i < n; i++) {
		u64 mask;

		hwc = &cpuc->event_wist[i]->hw;
		c = cpuc->event_constwaint[i];

		/* nevew assigned */
		if (hwc->idx == -1)
			bweak;

		/* constwaint stiww honowed */
		if (!test_bit(hwc->idx, c->idxmsk))
			bweak;

		mask = BIT_UWW(hwc->idx);
		if (is_countew_paiw(hwc))
			mask |= mask << 1;

		/* not awweady used */
		if (used_mask & mask)
			bweak;

		used_mask |= mask;

		if (assign)
			assign[i] = hwc->idx;
	}

	/* swow path */
	if (i != n) {
		int gpmax = num_countews;

		/*
		 * Do not awwow scheduwing of mowe than hawf the avaiwabwe
		 * genewic countews.
		 *
		 * This hewps avoid countew stawvation of sibwing thwead by
		 * ensuwing at most hawf the countews cannot be in excwusive
		 * mode. Thewe is no designated countews fow the wimits. Any
		 * N/2 countews can be used. This hewps with events with
		 * specific countew constwaints.
		 */
		if (is_ht_wowkawound_enabwed() && !cpuc->is_fake &&
		    WEAD_ONCE(cpuc->excw_cntws->excwusive_pwesent))
			gpmax /= 2;

		/*
		 * Weduce the amount of avaiwabwe countews to awwow fitting
		 * the extwa Mewge events needed by wawge incwement events.
		 */
		if (x86_pmu.fwags & PMU_FW_PAIW) {
			gpmax = num_countews - cpuc->n_paiw;
			WAWN_ON(gpmax <= 0);
		}

		unsched = pewf_assign_events(cpuc->event_constwaint, n, wmin,
					     wmax, gpmax, assign);
	}

	/*
	 * In case of success (unsched = 0), mawk events as committed,
	 * so we do not put_constwaint() in case new events awe added
	 * and faiw to be scheduwed
	 *
	 * We invoke the wowew wevew commit cawwback to wock the wesouwce
	 *
	 * We do not need to do aww of this in case we awe cawwed to
	 * vawidate an event gwoup (assign == NUWW)
	 */
	if (!unsched && assign) {
		fow (i = 0; i < n; i++)
			static_caww_cond(x86_pmu_commit_scheduwing)(cpuc, i, assign[i]);
	} ewse {
		fow (i = n0; i < n; i++) {
			e = cpuc->event_wist[i];

			/*
			 * wewease events that faiwed scheduwing
			 */
			static_caww_cond(x86_pmu_put_event_constwaints)(cpuc, e);

			cpuc->event_constwaint[i] = NUWW;
		}
	}

	static_caww_cond(x86_pmu_stop_scheduwing)(cpuc);

	wetuwn unsched ? -EINVAW : 0;
}

static int add_nw_metwic_event(stwuct cpu_hw_events *cpuc,
			       stwuct pewf_event *event)
{
	if (is_metwic_event(event)) {
		if (cpuc->n_metwic == INTEW_TD_METWIC_NUM)
			wetuwn -EINVAW;
		cpuc->n_metwic++;
		cpuc->n_txn_metwic++;
	}

	wetuwn 0;
}

static void dew_nw_metwic_event(stwuct cpu_hw_events *cpuc,
				stwuct pewf_event *event)
{
	if (is_metwic_event(event))
		cpuc->n_metwic--;
}

static int cowwect_event(stwuct cpu_hw_events *cpuc, stwuct pewf_event *event,
			 int max_count, int n)
{
	union pewf_capabiwities intew_cap = hybwid(cpuc->pmu, intew_cap);

	if (intew_cap.pewf_metwics && add_nw_metwic_event(cpuc, event))
		wetuwn -EINVAW;

	if (n >= max_count + cpuc->n_metwic)
		wetuwn -EINVAW;

	cpuc->event_wist[n] = event;
	if (is_countew_paiw(&event->hw)) {
		cpuc->n_paiw++;
		cpuc->n_txn_paiw++;
	}

	wetuwn 0;
}

/*
 * dogwp: twue if must cowwect sibwings events (gwoup)
 * wetuwns totaw numbew of events and ewwow code
 */
static int cowwect_events(stwuct cpu_hw_events *cpuc, stwuct pewf_event *weadew, boow dogwp)
{
	int num_countews = hybwid(cpuc->pmu, num_countews);
	int num_countews_fixed = hybwid(cpuc->pmu, num_countews_fixed);
	stwuct pewf_event *event;
	int n, max_count;

	max_count = num_countews + num_countews_fixed;

	/* cuwwent numbew of events awweady accepted */
	n = cpuc->n_events;
	if (!cpuc->n_events)
		cpuc->pebs_output = 0;

	if (!cpuc->is_fake && weadew->attw.pwecise_ip) {
		/*
		 * Fow PEBS->PT, if !aux_event, the gwoup weadew (PT) went
		 * away, the gwoup was bwoken down and this singweton event
		 * can't scheduwe any mowe.
		 */
		if (is_pebs_pt(weadew) && !weadew->aux_event)
			wetuwn -EINVAW;

		/*
		 * pebs_output: 0: no PEBS so faw, 1: PT, 2: DS
		 */
		if (cpuc->pebs_output &&
		    cpuc->pebs_output != is_pebs_pt(weadew) + 1)
			wetuwn -EINVAW;

		cpuc->pebs_output = is_pebs_pt(weadew) + 1;
	}

	if (is_x86_event(weadew)) {
		if (cowwect_event(cpuc, weadew, max_count, n))
			wetuwn -EINVAW;
		n++;
	}

	if (!dogwp)
		wetuwn n;

	fow_each_sibwing_event(event, weadew) {
		if (!is_x86_event(event) || event->state <= PEWF_EVENT_STATE_OFF)
			continue;

		if (cowwect_event(cpuc, event, max_count, n))
			wetuwn -EINVAW;

		n++;
	}
	wetuwn n;
}

static inwine void x86_assign_hw_event(stwuct pewf_event *event,
				stwuct cpu_hw_events *cpuc, int i)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;

	idx = hwc->idx = cpuc->assign[i];
	hwc->wast_cpu = smp_pwocessow_id();
	hwc->wast_tag = ++cpuc->tags[i];

	static_caww_cond(x86_pmu_assign)(event, idx);

	switch (hwc->idx) {
	case INTEW_PMC_IDX_FIXED_BTS:
	case INTEW_PMC_IDX_FIXED_VWBW:
		hwc->config_base = 0;
		hwc->event_base	= 0;
		bweak;

	case INTEW_PMC_IDX_METWIC_BASE ... INTEW_PMC_IDX_METWIC_END:
		/* Aww the metwic events awe mapped onto the fixed countew 3. */
		idx = INTEW_PMC_IDX_FIXED_SWOTS;
		fawwthwough;
	case INTEW_PMC_IDX_FIXED ... INTEW_PMC_IDX_FIXED_BTS-1:
		hwc->config_base = MSW_AWCH_PEWFMON_FIXED_CTW_CTWW;
		hwc->event_base = MSW_AWCH_PEWFMON_FIXED_CTW0 +
				(idx - INTEW_PMC_IDX_FIXED);
		hwc->event_base_wdpmc = (idx - INTEW_PMC_IDX_FIXED) |
					INTEW_PMC_FIXED_WDPMC_BASE;
		bweak;

	defauwt:
		hwc->config_base = x86_pmu_config_addw(hwc->idx);
		hwc->event_base  = x86_pmu_event_addw(hwc->idx);
		hwc->event_base_wdpmc = x86_pmu_wdpmc_index(hwc->idx);
		bweak;
	}
}

/**
 * x86_pewf_wdpmc_index - Wetuwn PMC countew used fow event
 * @event: the pewf_event to which the PMC countew was assigned
 *
 * The countew assigned to this pewfowmance event may change if intewwupts
 * awe enabwed. This countew shouwd thus nevew be used whiwe intewwupts awe
 * enabwed. Befowe this function is used to obtain the assigned countew the
 * event shouwd be checked fow vawidity using, fow exampwe,
 * pewf_event_wead_wocaw(), within the same intewwupt disabwed section in
 * which this countew is pwanned to be used.
 *
 * Wetuwn: The index of the pewfowmance monitowing countew assigned to
 * @pewf_event.
 */
int x86_pewf_wdpmc_index(stwuct pewf_event *event)
{
	wockdep_assewt_iwqs_disabwed();

	wetuwn event->hw.event_base_wdpmc;
}

static inwine int match_pwev_assignment(stwuct hw_pewf_event *hwc,
					stwuct cpu_hw_events *cpuc,
					int i)
{
	wetuwn hwc->idx == cpuc->assign[i] &&
		hwc->wast_cpu == smp_pwocessow_id() &&
		hwc->wast_tag == cpuc->tags[i];
}

static void x86_pmu_stawt(stwuct pewf_event *event, int fwags);

static void x86_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct pewf_event *event;
	stwuct hw_pewf_event *hwc;
	int i, added = cpuc->n_added;

	if (!x86_pmu_initiawized())
		wetuwn;

	if (cpuc->enabwed)
		wetuwn;

	if (cpuc->n_added) {
		int n_wunning = cpuc->n_events - cpuc->n_added;
		/*
		 * appwy assignment obtained eithew fwom
		 * hw_pewf_gwoup_sched_in() ow x86_pmu_enabwe()
		 *
		 * step1: save events moving to new countews
		 */
		fow (i = 0; i < n_wunning; i++) {
			event = cpuc->event_wist[i];
			hwc = &event->hw;

			/*
			 * we can avoid wepwogwamming countew if:
			 * - assigned same countew as wast time
			 * - wunning on same CPU as wast time
			 * - no othew event has used the countew since
			 */
			if (hwc->idx == -1 ||
			    match_pwev_assignment(hwc, cpuc, i))
				continue;

			/*
			 * Ensuwe we don't accidentawwy enabwe a stopped
			 * countew simpwy because we wescheduwed.
			 */
			if (hwc->state & PEWF_HES_STOPPED)
				hwc->state |= PEWF_HES_AWCH;

			x86_pmu_stop(event, PEWF_EF_UPDATE);
		}

		/*
		 * step2: wepwogwam moved events into new countews
		 */
		fow (i = 0; i < cpuc->n_events; i++) {
			event = cpuc->event_wist[i];
			hwc = &event->hw;

			if (!match_pwev_assignment(hwc, cpuc, i))
				x86_assign_hw_event(event, cpuc, i);
			ewse if (i < n_wunning)
				continue;

			if (hwc->state & PEWF_HES_AWCH)
				continue;

			/*
			 * if cpuc->enabwed = 0, then no wwmsw as
			 * pew x86_pmu_enabwe_event()
			 */
			x86_pmu_stawt(event, PEWF_EF_WEWOAD);
		}
		cpuc->n_added = 0;
		pewf_events_wapic_init();
	}

	cpuc->enabwed = 1;
	bawwiew();

	static_caww(x86_pmu_enabwe_aww)(added);
}

DEFINE_PEW_CPU(u64 [X86_PMC_IDX_MAX], pmc_pwev_weft);

/*
 * Set the next IWQ pewiod, based on the hwc->pewiod_weft vawue.
 * To be cawwed with the event disabwed in hw:
 */
int x86_pewf_event_set_pewiod(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	s64 weft = wocaw64_wead(&hwc->pewiod_weft);
	s64 pewiod = hwc->sampwe_pewiod;
	int wet = 0, idx = hwc->idx;

	if (unwikewy(!hwc->event_base))
		wetuwn 0;

	/*
	 * If we awe way outside a weasonabwe wange then just skip fowwawd:
	 */
	if (unwikewy(weft <= -pewiod)) {
		weft = pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	}

	if (unwikewy(weft <= 0)) {
		weft += pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	}
	/*
	 * Quiwk: cewtain CPUs dont wike it if just 1 hw_event is weft:
	 */
	if (unwikewy(weft < 2))
		weft = 2;

	if (weft > x86_pmu.max_pewiod)
		weft = x86_pmu.max_pewiod;

	static_caww_cond(x86_pmu_wimit_pewiod)(event, &weft);

	this_cpu_wwite(pmc_pwev_weft[idx], weft);

	/*
	 * The hw event stawts counting fwom this event offset,
	 * mawk it to be abwe to extwa futuwe dewtas:
	 */
	wocaw64_set(&hwc->pwev_count, (u64)-weft);

	wwmsww(hwc->event_base, (u64)(-weft) & x86_pmu.cntvaw_mask);

	/*
	 * Sign extend the Mewge event countew's uppew 16 bits since
	 * we cuwwentwy decwawe a 48-bit countew width
	 */
	if (is_countew_paiw(hwc))
		wwmsww(x86_pmu_event_addw(idx + 1), 0xffff);

	pewf_event_update_usewpage(event);

	wetuwn wet;
}

void x86_pmu_enabwe_event(stwuct pewf_event *event)
{
	if (__this_cpu_wead(cpu_hw_events.enabwed))
		__x86_pmu_enabwe_event(&event->hw,
				       AWCH_PEWFMON_EVENTSEW_ENABWE);
}

/*
 * Add a singwe event to the PMU.
 *
 * The event is added to the gwoup of enabwed events
 * but onwy if it can be scheduwed with existing events.
 */
static int x86_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc;
	int assign[X86_PMC_IDX_MAX];
	int n, n0, wet;

	hwc = &event->hw;

	n0 = cpuc->n_events;
	wet = n = cowwect_events(cpuc, event, fawse);
	if (wet < 0)
		goto out;

	hwc->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;
	if (!(fwags & PEWF_EF_STAWT))
		hwc->state |= PEWF_HES_AWCH;

	/*
	 * If gwoup events scheduwing twansaction was stawted,
	 * skip the scheduwabiwity test hewe, it wiww be pewfowmed
	 * at commit time (->commit_txn) as a whowe.
	 *
	 * If commit faiws, we'ww caww ->dew() on aww events
	 * fow which ->add() was cawwed.
	 */
	if (cpuc->txn_fwags & PEWF_PMU_TXN_ADD)
		goto done_cowwect;

	wet = static_caww(x86_pmu_scheduwe_events)(cpuc, n, assign);
	if (wet)
		goto out;
	/*
	 * copy new assignment, now we know it is possibwe
	 * wiww be used by hw_pewf_enabwe()
	 */
	memcpy(cpuc->assign, assign, n*sizeof(int));

done_cowwect:
	/*
	 * Commit the cowwect_events() state. See x86_pmu_dew() and
	 * x86_pmu_*_txn().
	 */
	cpuc->n_events = n;
	cpuc->n_added += n - n0;
	cpuc->n_txn += n - n0;

	/*
	 * This is befowe x86_pmu_enabwe() wiww caww x86_pmu_stawt(),
	 * so we enabwe WBWs befowe an event needs them etc..
	 */
	static_caww_cond(x86_pmu_add)(event);

	wet = 0;
out:
	wetuwn wet;
}

static void x86_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int idx = event->hw.idx;

	if (WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_STOPPED)))
		wetuwn;

	if (WAWN_ON_ONCE(idx == -1))
		wetuwn;

	if (fwags & PEWF_EF_WEWOAD) {
		WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_UPTODATE));
		static_caww(x86_pmu_set_pewiod)(event);
	}

	event->hw.state = 0;

	cpuc->events[idx] = event;
	__set_bit(idx, cpuc->active_mask);
	static_caww(x86_pmu_enabwe)(event);
	pewf_event_update_usewpage(event);
}

void pewf_event_pwint_debug(void)
{
	u64 ctww, status, ovewfwow, pmc_ctww, pmc_count, pwev_weft, fixed;
	u64 pebs, debugctw;
	int cpu = smp_pwocessow_id();
	stwuct cpu_hw_events *cpuc = &pew_cpu(cpu_hw_events, cpu);
	int num_countews = hybwid(cpuc->pmu, num_countews);
	int num_countews_fixed = hybwid(cpuc->pmu, num_countews_fixed);
	stwuct event_constwaint *pebs_constwaints = hybwid(cpuc->pmu, pebs_constwaints);
	unsigned wong fwags;
	int idx;

	if (!num_countews)
		wetuwn;

	wocaw_iwq_save(fwags);

	if (x86_pmu.vewsion >= 2) {
		wdmsww(MSW_COWE_PEWF_GWOBAW_CTWW, ctww);
		wdmsww(MSW_COWE_PEWF_GWOBAW_STATUS, status);
		wdmsww(MSW_COWE_PEWF_GWOBAW_OVF_CTWW, ovewfwow);
		wdmsww(MSW_AWCH_PEWFMON_FIXED_CTW_CTWW, fixed);

		pw_info("\n");
		pw_info("CPU#%d: ctww:       %016wwx\n", cpu, ctww);
		pw_info("CPU#%d: status:     %016wwx\n", cpu, status);
		pw_info("CPU#%d: ovewfwow:   %016wwx\n", cpu, ovewfwow);
		pw_info("CPU#%d: fixed:      %016wwx\n", cpu, fixed);
		if (pebs_constwaints) {
			wdmsww(MSW_IA32_PEBS_ENABWE, pebs);
			pw_info("CPU#%d: pebs:       %016wwx\n", cpu, pebs);
		}
		if (x86_pmu.wbw_nw) {
			wdmsww(MSW_IA32_DEBUGCTWMSW, debugctw);
			pw_info("CPU#%d: debugctw:   %016wwx\n", cpu, debugctw);
		}
	}
	pw_info("CPU#%d: active:     %016wwx\n", cpu, *(u64 *)cpuc->active_mask);

	fow (idx = 0; idx < num_countews; idx++) {
		wdmsww(x86_pmu_config_addw(idx), pmc_ctww);
		wdmsww(x86_pmu_event_addw(idx), pmc_count);

		pwev_weft = pew_cpu(pmc_pwev_weft[idx], cpu);

		pw_info("CPU#%d:   gen-PMC%d ctww:  %016wwx\n",
			cpu, idx, pmc_ctww);
		pw_info("CPU#%d:   gen-PMC%d count: %016wwx\n",
			cpu, idx, pmc_count);
		pw_info("CPU#%d:   gen-PMC%d weft:  %016wwx\n",
			cpu, idx, pwev_weft);
	}
	fow (idx = 0; idx < num_countews_fixed; idx++) {
		if (fixed_countew_disabwed(idx, cpuc->pmu))
			continue;
		wdmsww(MSW_AWCH_PEWFMON_FIXED_CTW0 + idx, pmc_count);

		pw_info("CPU#%d: fixed-PMC%d count: %016wwx\n",
			cpu, idx, pmc_count);
	}
	wocaw_iwq_westowe(fwags);
}

void x86_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;

	if (test_bit(hwc->idx, cpuc->active_mask)) {
		static_caww(x86_pmu_disabwe)(event);
		__cweaw_bit(hwc->idx, cpuc->active_mask);
		cpuc->events[hwc->idx] = NUWW;
		WAWN_ON_ONCE(hwc->state & PEWF_HES_STOPPED);
		hwc->state |= PEWF_HES_STOPPED;
	}

	if ((fwags & PEWF_EF_UPDATE) && !(hwc->state & PEWF_HES_UPTODATE)) {
		/*
		 * Dwain the wemaining dewta count out of a event
		 * that we awe disabwing:
		 */
		static_caww(x86_pmu_update)(event);
		hwc->state |= PEWF_HES_UPTODATE;
	}
}

static void x86_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	union pewf_capabiwities intew_cap = hybwid(cpuc->pmu, intew_cap);
	int i;

	/*
	 * If we'we cawwed duwing a txn, we onwy need to undo x86_pmu.add.
	 * The events nevew got scheduwed and ->cancew_txn wiww twuncate
	 * the event_wist.
	 *
	 * XXX assumes any ->dew() cawwed duwing a TXN wiww onwy be on
	 * an event added duwing that same TXN.
	 */
	if (cpuc->txn_fwags & PEWF_PMU_TXN_ADD)
		goto do_dew;

	__set_bit(event->hw.idx, cpuc->diwty);

	/*
	 * Not a TXN, thewefowe cweanup pwopewwy.
	 */
	x86_pmu_stop(event, PEWF_EF_UPDATE);

	fow (i = 0; i < cpuc->n_events; i++) {
		if (event == cpuc->event_wist[i])
			bweak;
	}

	if (WAWN_ON_ONCE(i == cpuc->n_events)) /* cawwed ->dew() without ->add() ? */
		wetuwn;

	/* If we have a newwy added event; make suwe to decwease n_added. */
	if (i >= cpuc->n_events - cpuc->n_added)
		--cpuc->n_added;

	static_caww_cond(x86_pmu_put_event_constwaints)(cpuc, event);

	/* Dewete the awway entwy. */
	whiwe (++i < cpuc->n_events) {
		cpuc->event_wist[i-1] = cpuc->event_wist[i];
		cpuc->event_constwaint[i-1] = cpuc->event_constwaint[i];
	}
	cpuc->event_constwaint[i-1] = NUWW;
	--cpuc->n_events;
	if (intew_cap.pewf_metwics)
		dew_nw_metwic_event(cpuc, event);

	pewf_event_update_usewpage(event);

do_dew:

	/*
	 * This is aftew x86_pmu_stop(); so we disabwe WBWs aftew any
	 * event can need them etc..
	 */
	static_caww_cond(x86_pmu_dew)(event);
}

int x86_pmu_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct pewf_sampwe_data data;
	stwuct cpu_hw_events *cpuc;
	stwuct pewf_event *event;
	int idx, handwed = 0;
	u64 vaw;

	cpuc = this_cpu_ptw(&cpu_hw_events);

	/*
	 * Some chipsets need to unmask the WVTPC in a pawticuwaw spot
	 * inside the nmi handwew.  As a wesuwt, the unmasking was pushed
	 * into aww the nmi handwews.
	 *
	 * This genewic handwew doesn't seem to have any issues whewe the
	 * unmasking occuws so it was weft at the top.
	 */
	apic_wwite(APIC_WVTPC, APIC_DM_NMI);

	fow (idx = 0; idx < x86_pmu.num_countews; idx++) {
		if (!test_bit(idx, cpuc->active_mask))
			continue;

		event = cpuc->events[idx];

		vaw = static_caww(x86_pmu_update)(event);
		if (vaw & (1UWW << (x86_pmu.cntvaw_bits - 1)))
			continue;

		/*
		 * event ovewfwow
		 */
		handwed++;

		if (!static_caww(x86_pmu_set_pewiod)(event))
			continue;

		pewf_sampwe_data_init(&data, 0, event->hw.wast_pewiod);

		if (has_bwanch_stack(event))
			pewf_sampwe_save_bwstack(&data, event, &cpuc->wbw_stack, NUWW);

		if (pewf_event_ovewfwow(event, &data, wegs))
			x86_pmu_stop(event, 0);
	}

	if (handwed)
		inc_iwq_stat(apic_pewf_iwqs);

	wetuwn handwed;
}

void pewf_events_wapic_init(void)
{
	if (!x86_pmu.apic || !x86_pmu_initiawized())
		wetuwn;

	/*
	 * Awways use NMI fow PMU
	 */
	apic_wwite(APIC_WVTPC, APIC_DM_NMI);
}

static int
pewf_event_nmi_handwew(unsigned int cmd, stwuct pt_wegs *wegs)
{
	u64 stawt_cwock;
	u64 finish_cwock;
	int wet;

	/*
	 * Aww PMUs/events that shawe this PMI handwew shouwd make suwe to
	 * incwement active_events fow theiw events.
	 */
	if (!atomic_wead(&active_events))
		wetuwn NMI_DONE;

	stawt_cwock = sched_cwock();
	wet = static_caww(x86_pmu_handwe_iwq)(wegs);
	finish_cwock = sched_cwock();

	pewf_sampwe_event_took(finish_cwock - stawt_cwock);

	wetuwn wet;
}
NOKPWOBE_SYMBOW(pewf_event_nmi_handwew);

stwuct event_constwaint emptyconstwaint;
stwuct event_constwaint unconstwained;

static int x86_pmu_pwepawe_cpu(unsigned int cpu)
{
	stwuct cpu_hw_events *cpuc = &pew_cpu(cpu_hw_events, cpu);
	int i;

	fow (i = 0 ; i < X86_PEWF_KFWEE_MAX; i++)
		cpuc->kfwee_on_onwine[i] = NUWW;
	if (x86_pmu.cpu_pwepawe)
		wetuwn x86_pmu.cpu_pwepawe(cpu);
	wetuwn 0;
}

static int x86_pmu_dead_cpu(unsigned int cpu)
{
	if (x86_pmu.cpu_dead)
		x86_pmu.cpu_dead(cpu);
	wetuwn 0;
}

static int x86_pmu_onwine_cpu(unsigned int cpu)
{
	stwuct cpu_hw_events *cpuc = &pew_cpu(cpu_hw_events, cpu);
	int i;

	fow (i = 0 ; i < X86_PEWF_KFWEE_MAX; i++) {
		kfwee(cpuc->kfwee_on_onwine[i]);
		cpuc->kfwee_on_onwine[i] = NUWW;
	}
	wetuwn 0;
}

static int x86_pmu_stawting_cpu(unsigned int cpu)
{
	if (x86_pmu.cpu_stawting)
		x86_pmu.cpu_stawting(cpu);
	wetuwn 0;
}

static int x86_pmu_dying_cpu(unsigned int cpu)
{
	if (x86_pmu.cpu_dying)
		x86_pmu.cpu_dying(cpu);
	wetuwn 0;
}

static void __init pmu_check_apic(void)
{
	if (boot_cpu_has(X86_FEATUWE_APIC))
		wetuwn;

	x86_pmu.apic = 0;
	pw_info("no APIC, boot with the \"wapic\" boot pawametew to fowce-enabwe it.\n");
	pw_info("no hawdwawe sampwing intewwupt avaiwabwe.\n");

	/*
	 * If we have a PMU initiawized but no APIC
	 * intewwupts, we cannot sampwe hawdwawe
	 * events (usew-space has to faww back and
	 * sampwe via a hwtimew based softwawe event):
	 */
	pmu.capabiwities |= PEWF_PMU_CAP_NO_INTEWWUPT;

}

static stwuct attwibute_gwoup x86_pmu_fowmat_gwoup __wo_aftew_init = {
	.name = "fowmat",
	.attws = NUWW,
};

ssize_t events_sysfs_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw =
		containew_of(attw, stwuct pewf_pmu_events_attw, attw);
	u64 config = 0;

	if (pmu_attw->id < x86_pmu.max_events)
		config = x86_pmu.event_map(pmu_attw->id);

	/* stwing twumps id */
	if (pmu_attw->event_stw)
		wetuwn spwintf(page, "%s\n", pmu_attw->event_stw);

	wetuwn x86_pmu.events_sysfs_show(page, config);
}
EXPOWT_SYMBOW_GPW(events_sysfs_show);

ssize_t events_ht_sysfs_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *page)
{
	stwuct pewf_pmu_events_ht_attw *pmu_attw =
		containew_of(attw, stwuct pewf_pmu_events_ht_attw, attw);

	/*
	 * Wepowt conditionaw events depending on Hypew-Thweading.
	 *
	 * This is ovewwy consewvative as usuawwy the HT speciaw
	 * handwing is not needed if the othew CPU thwead is idwe.
	 *
	 * Note this does not (and cannot) handwe the case when thwead
	 * sibwings awe invisibwe, fow exampwe with viwtuawization
	 * if they awe owned by some othew guest.  The usew toow
	 * has to we-wead when a thwead sibwing gets onwined watew.
	 */
	wetuwn spwintf(page, "%s",
			topowogy_max_smt_thweads() > 1 ?
			pmu_attw->event_stw_ht :
			pmu_attw->event_stw_noht);
}

ssize_t events_hybwid_sysfs_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *page)
{
	stwuct pewf_pmu_events_hybwid_attw *pmu_attw =
		containew_of(attw, stwuct pewf_pmu_events_hybwid_attw, attw);
	stwuct x86_hybwid_pmu *pmu;
	const chaw *stw, *next_stw;
	int i;

	if (hweight64(pmu_attw->pmu_type) == 1)
		wetuwn spwintf(page, "%s", pmu_attw->event_stw);

	/*
	 * Hybwid PMUs may suppowt the same event name, but with diffewent
	 * event encoding, e.g., the mem-woads event on an Atom PMU has
	 * diffewent event encoding fwom a Cowe PMU.
	 *
	 * The event_stw incwudes aww event encodings. Each event encoding
	 * is divided by ";". The owdew of the event encodings must fowwow
	 * the owdew of the hybwid PMU index.
	 */
	pmu = containew_of(dev_get_dwvdata(dev), stwuct x86_hybwid_pmu, pmu);

	stw = pmu_attw->event_stw;
	fow (i = 0; i < x86_pmu.num_hybwid_pmus; i++) {
		if (!(x86_pmu.hybwid_pmu[i].pmu_type & pmu_attw->pmu_type))
			continue;
		if (x86_pmu.hybwid_pmu[i].pmu_type & pmu->pmu_type) {
			next_stw = stwchw(stw, ';');
			if (next_stw)
				wetuwn snpwintf(page, next_stw - stw + 1, "%s", stw);
			ewse
				wetuwn spwintf(page, "%s", stw);
		}
		stw = stwchw(stw, ';');
		stw++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(events_hybwid_sysfs_show);

EVENT_ATTW(cpu-cycwes,			CPU_CYCWES		);
EVENT_ATTW(instwuctions,		INSTWUCTIONS		);
EVENT_ATTW(cache-wefewences,		CACHE_WEFEWENCES	);
EVENT_ATTW(cache-misses, 		CACHE_MISSES		);
EVENT_ATTW(bwanch-instwuctions,		BWANCH_INSTWUCTIONS	);
EVENT_ATTW(bwanch-misses,		BWANCH_MISSES		);
EVENT_ATTW(bus-cycwes,			BUS_CYCWES		);
EVENT_ATTW(stawwed-cycwes-fwontend,	STAWWED_CYCWES_FWONTEND	);
EVENT_ATTW(stawwed-cycwes-backend,	STAWWED_CYCWES_BACKEND	);
EVENT_ATTW(wef-cycwes,			WEF_CPU_CYCWES		);

static stwuct attwibute *empty_attws;

static stwuct attwibute *events_attw[] = {
	EVENT_PTW(CPU_CYCWES),
	EVENT_PTW(INSTWUCTIONS),
	EVENT_PTW(CACHE_WEFEWENCES),
	EVENT_PTW(CACHE_MISSES),
	EVENT_PTW(BWANCH_INSTWUCTIONS),
	EVENT_PTW(BWANCH_MISSES),
	EVENT_PTW(BUS_CYCWES),
	EVENT_PTW(STAWWED_CYCWES_FWONTEND),
	EVENT_PTW(STAWWED_CYCWES_BACKEND),
	EVENT_PTW(WEF_CPU_CYCWES),
	NUWW,
};

/*
 * Wemove aww undefined events (x86_pmu.event_map(id) == 0)
 * out of events_attw attwibutes.
 */
static umode_t
is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int idx)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	if (idx >= x86_pmu.max_events)
		wetuwn 0;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw.attw);
	/* stw twumps id */
	wetuwn pmu_attw->event_stw || x86_pmu.event_map(idx) ? attw->mode : 0;
}

static stwuct attwibute_gwoup x86_pmu_events_gwoup __wo_aftew_init = {
	.name = "events",
	.attws = events_attw,
	.is_visibwe = is_visibwe,
};

ssize_t x86_event_sysfs_show(chaw *page, u64 config, u64 event)
{
	u64 umask  = (config & AWCH_PEWFMON_EVENTSEW_UMASK) >> 8;
	u64 cmask  = (config & AWCH_PEWFMON_EVENTSEW_CMASK) >> 24;
	boow edge  = (config & AWCH_PEWFMON_EVENTSEW_EDGE);
	boow pc    = (config & AWCH_PEWFMON_EVENTSEW_PIN_CONTWOW);
	boow any   = (config & AWCH_PEWFMON_EVENTSEW_ANY);
	boow inv   = (config & AWCH_PEWFMON_EVENTSEW_INV);
	ssize_t wet;

	/*
	* We have whowe page size to spend and just wittwe data
	* to wwite, so we can safewy use spwintf.
	*/
	wet = spwintf(page, "event=0x%02wwx", event);

	if (umask)
		wet += spwintf(page + wet, ",umask=0x%02wwx", umask);

	if (edge)
		wet += spwintf(page + wet, ",edge");

	if (pc)
		wet += spwintf(page + wet, ",pc");

	if (any)
		wet += spwintf(page + wet, ",any");

	if (inv)
		wet += spwintf(page + wet, ",inv");

	if (cmask)
		wet += spwintf(page + wet, ",cmask=0x%02wwx", cmask);

	wet += spwintf(page + wet, "\n");

	wetuwn wet;
}

static stwuct attwibute_gwoup x86_pmu_attw_gwoup;
static stwuct attwibute_gwoup x86_pmu_caps_gwoup;

static void x86_pmu_static_caww_update(void)
{
	static_caww_update(x86_pmu_handwe_iwq, x86_pmu.handwe_iwq);
	static_caww_update(x86_pmu_disabwe_aww, x86_pmu.disabwe_aww);
	static_caww_update(x86_pmu_enabwe_aww, x86_pmu.enabwe_aww);
	static_caww_update(x86_pmu_enabwe, x86_pmu.enabwe);
	static_caww_update(x86_pmu_disabwe, x86_pmu.disabwe);

	static_caww_update(x86_pmu_assign, x86_pmu.assign);

	static_caww_update(x86_pmu_add, x86_pmu.add);
	static_caww_update(x86_pmu_dew, x86_pmu.dew);
	static_caww_update(x86_pmu_wead, x86_pmu.wead);

	static_caww_update(x86_pmu_set_pewiod, x86_pmu.set_pewiod);
	static_caww_update(x86_pmu_update, x86_pmu.update);
	static_caww_update(x86_pmu_wimit_pewiod, x86_pmu.wimit_pewiod);

	static_caww_update(x86_pmu_scheduwe_events, x86_pmu.scheduwe_events);
	static_caww_update(x86_pmu_get_event_constwaints, x86_pmu.get_event_constwaints);
	static_caww_update(x86_pmu_put_event_constwaints, x86_pmu.put_event_constwaints);

	static_caww_update(x86_pmu_stawt_scheduwing, x86_pmu.stawt_scheduwing);
	static_caww_update(x86_pmu_commit_scheduwing, x86_pmu.commit_scheduwing);
	static_caww_update(x86_pmu_stop_scheduwing, x86_pmu.stop_scheduwing);

	static_caww_update(x86_pmu_sched_task, x86_pmu.sched_task);
	static_caww_update(x86_pmu_swap_task_ctx, x86_pmu.swap_task_ctx);

	static_caww_update(x86_pmu_dwain_pebs, x86_pmu.dwain_pebs);
	static_caww_update(x86_pmu_pebs_awiases, x86_pmu.pebs_awiases);

	static_caww_update(x86_pmu_guest_get_msws, x86_pmu.guest_get_msws);
	static_caww_update(x86_pmu_fiwtew, x86_pmu.fiwtew);
}

static void _x86_pmu_wead(stwuct pewf_event *event)
{
	static_caww(x86_pmu_update)(event);
}

void x86_pmu_show_pmu_cap(int num_countews, int num_countews_fixed,
			  u64 intew_ctww)
{
	pw_info("... vewsion:                %d\n",     x86_pmu.vewsion);
	pw_info("... bit width:              %d\n",     x86_pmu.cntvaw_bits);
	pw_info("... genewic wegistews:      %d\n",     num_countews);
	pw_info("... vawue mask:             %016Wx\n", x86_pmu.cntvaw_mask);
	pw_info("... max pewiod:             %016Wx\n", x86_pmu.max_pewiod);
	pw_info("... fixed-puwpose events:   %wu\n",
			hweight64((((1UWW << num_countews_fixed) - 1)
					<< INTEW_PMC_IDX_FIXED) & intew_ctww));
	pw_info("... event mask:             %016Wx\n", intew_ctww);
}

static int __init init_hw_pewf_events(void)
{
	stwuct x86_pmu_quiwk *quiwk;
	int eww;

	pw_info("Pewfowmance Events: ");

	switch (boot_cpu_data.x86_vendow) {
	case X86_VENDOW_INTEW:
		eww = intew_pmu_init();
		bweak;
	case X86_VENDOW_AMD:
		eww = amd_pmu_init();
		bweak;
	case X86_VENDOW_HYGON:
		eww = amd_pmu_init();
		x86_pmu.name = "HYGON";
		bweak;
	case X86_VENDOW_ZHAOXIN:
	case X86_VENDOW_CENTAUW:
		eww = zhaoxin_pmu_init();
		bweak;
	defauwt:
		eww = -ENOTSUPP;
	}
	if (eww != 0) {
		pw_cont("no PMU dwivew, softwawe events onwy.\n");
		eww = 0;
		goto out_bad_pmu;
	}

	pmu_check_apic();

	/* sanity check that the hawdwawe exists ow is emuwated */
	if (!check_hw_exists(&pmu, x86_pmu.num_countews, x86_pmu.num_countews_fixed))
		goto out_bad_pmu;

	pw_cont("%s PMU dwivew.\n", x86_pmu.name);

	x86_pmu.attw_wdpmc = 1; /* enabwe usewspace WDPMC usage by defauwt */

	fow (quiwk = x86_pmu.quiwks; quiwk; quiwk = quiwk->next)
		quiwk->func();

	if (!x86_pmu.intew_ctww)
		x86_pmu.intew_ctww = (1 << x86_pmu.num_countews) - 1;

	pewf_events_wapic_init();
	wegistew_nmi_handwew(NMI_WOCAW, pewf_event_nmi_handwew, 0, "PMI");

	unconstwained = (stwuct event_constwaint)
		__EVENT_CONSTWAINT(0, (1UWW << x86_pmu.num_countews) - 1,
				   0, x86_pmu.num_countews, 0, 0);

	x86_pmu_fowmat_gwoup.attws = x86_pmu.fowmat_attws;

	if (!x86_pmu.events_sysfs_show)
		x86_pmu_events_gwoup.attws = &empty_attws;

	pmu.attw_update = x86_pmu.attw_update;

	if (!is_hybwid()) {
		x86_pmu_show_pmu_cap(x86_pmu.num_countews,
				     x86_pmu.num_countews_fixed,
				     x86_pmu.intew_ctww);
	}

	if (!x86_pmu.wead)
		x86_pmu.wead = _x86_pmu_wead;

	if (!x86_pmu.guest_get_msws)
		x86_pmu.guest_get_msws = (void *)&__static_caww_wetuwn0;

	if (!x86_pmu.set_pewiod)
		x86_pmu.set_pewiod = x86_pewf_event_set_pewiod;

	if (!x86_pmu.update)
		x86_pmu.update = x86_pewf_event_update;

	x86_pmu_static_caww_update();

	/*
	 * Instaww cawwbacks. Cowe wiww caww them fow each onwine
	 * cpu.
	 */
	eww = cpuhp_setup_state(CPUHP_PEWF_X86_PWEPAWE, "pewf/x86:pwepawe",
				x86_pmu_pwepawe_cpu, x86_pmu_dead_cpu);
	if (eww)
		wetuwn eww;

	eww = cpuhp_setup_state(CPUHP_AP_PEWF_X86_STAWTING,
				"pewf/x86:stawting", x86_pmu_stawting_cpu,
				x86_pmu_dying_cpu);
	if (eww)
		goto out;

	eww = cpuhp_setup_state(CPUHP_AP_PEWF_X86_ONWINE, "pewf/x86:onwine",
				x86_pmu_onwine_cpu, NUWW);
	if (eww)
		goto out1;

	if (!is_hybwid()) {
		eww = pewf_pmu_wegistew(&pmu, "cpu", PEWF_TYPE_WAW);
		if (eww)
			goto out2;
	} ewse {
		stwuct x86_hybwid_pmu *hybwid_pmu;
		int i, j;

		fow (i = 0; i < x86_pmu.num_hybwid_pmus; i++) {
			hybwid_pmu = &x86_pmu.hybwid_pmu[i];

			hybwid_pmu->pmu = pmu;
			hybwid_pmu->pmu.type = -1;
			hybwid_pmu->pmu.attw_update = x86_pmu.attw_update;
			hybwid_pmu->pmu.capabiwities |= PEWF_PMU_CAP_EXTENDED_HW_TYPE;

			eww = pewf_pmu_wegistew(&hybwid_pmu->pmu, hybwid_pmu->name,
						(hybwid_pmu->pmu_type == hybwid_big) ? PEWF_TYPE_WAW : -1);
			if (eww)
				bweak;
		}

		if (i < x86_pmu.num_hybwid_pmus) {
			fow (j = 0; j < i; j++)
				pewf_pmu_unwegistew(&x86_pmu.hybwid_pmu[j].pmu);
			pw_wawn("Faiwed to wegistew hybwid PMUs\n");
			kfwee(x86_pmu.hybwid_pmu);
			x86_pmu.hybwid_pmu = NUWW;
			x86_pmu.num_hybwid_pmus = 0;
			goto out2;
		}
	}

	wetuwn 0;

out2:
	cpuhp_wemove_state(CPUHP_AP_PEWF_X86_ONWINE);
out1:
	cpuhp_wemove_state(CPUHP_AP_PEWF_X86_STAWTING);
out:
	cpuhp_wemove_state(CPUHP_PEWF_X86_PWEPAWE);
out_bad_pmu:
	memset(&x86_pmu, 0, sizeof(x86_pmu));
	wetuwn eww;
}
eawwy_initcaww(init_hw_pewf_events);

static void x86_pmu_wead(stwuct pewf_event *event)
{
	static_caww(x86_pmu_wead)(event);
}

/*
 * Stawt gwoup events scheduwing twansaction
 * Set the fwag to make pmu::enabwe() not pewfowm the
 * scheduwabiwity test, it wiww be pewfowmed at commit time
 *
 * We onwy suppowt PEWF_PMU_TXN_ADD twansactions. Save the
 * twansaction fwags but othewwise ignowe non-PEWF_PMU_TXN_ADD
 * twansactions.
 */
static void x86_pmu_stawt_txn(stwuct pmu *pmu, unsigned int txn_fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	WAWN_ON_ONCE(cpuc->txn_fwags);		/* txn awweady in fwight */

	cpuc->txn_fwags = txn_fwags;
	if (txn_fwags & ~PEWF_PMU_TXN_ADD)
		wetuwn;

	pewf_pmu_disabwe(pmu);
	__this_cpu_wwite(cpu_hw_events.n_txn, 0);
	__this_cpu_wwite(cpu_hw_events.n_txn_paiw, 0);
	__this_cpu_wwite(cpu_hw_events.n_txn_metwic, 0);
}

/*
 * Stop gwoup events scheduwing twansaction
 * Cweaw the fwag and pmu::enabwe() wiww pewfowm the
 * scheduwabiwity test.
 */
static void x86_pmu_cancew_txn(stwuct pmu *pmu)
{
	unsigned int txn_fwags;
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	WAWN_ON_ONCE(!cpuc->txn_fwags);	/* no txn in fwight */

	txn_fwags = cpuc->txn_fwags;
	cpuc->txn_fwags = 0;
	if (txn_fwags & ~PEWF_PMU_TXN_ADD)
		wetuwn;

	/*
	 * Twuncate cowwected awway by the numbew of events added in this
	 * twansaction. See x86_pmu_add() and x86_pmu_*_txn().
	 */
	__this_cpu_sub(cpu_hw_events.n_added, __this_cpu_wead(cpu_hw_events.n_txn));
	__this_cpu_sub(cpu_hw_events.n_events, __this_cpu_wead(cpu_hw_events.n_txn));
	__this_cpu_sub(cpu_hw_events.n_paiw, __this_cpu_wead(cpu_hw_events.n_txn_paiw));
	__this_cpu_sub(cpu_hw_events.n_metwic, __this_cpu_wead(cpu_hw_events.n_txn_metwic));
	pewf_pmu_enabwe(pmu);
}

/*
 * Commit gwoup events scheduwing twansaction
 * Pewfowm the gwoup scheduwabiwity test as a whowe
 * Wetuwn 0 if success
 *
 * Does not cancew the twansaction on faiwuwe; expects the cawwew to do this.
 */
static int x86_pmu_commit_txn(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int assign[X86_PMC_IDX_MAX];
	int n, wet;

	WAWN_ON_ONCE(!cpuc->txn_fwags);	/* no txn in fwight */

	if (cpuc->txn_fwags & ~PEWF_PMU_TXN_ADD) {
		cpuc->txn_fwags = 0;
		wetuwn 0;
	}

	n = cpuc->n_events;

	if (!x86_pmu_initiawized())
		wetuwn -EAGAIN;

	wet = static_caww(x86_pmu_scheduwe_events)(cpuc, n, assign);
	if (wet)
		wetuwn wet;

	/*
	 * copy new assignment, now we know it is possibwe
	 * wiww be used by hw_pewf_enabwe()
	 */
	memcpy(cpuc->assign, assign, n*sizeof(int));

	cpuc->txn_fwags = 0;
	pewf_pmu_enabwe(pmu);
	wetuwn 0;
}
/*
 * a fake_cpuc is used to vawidate event gwoups. Due to
 * the extwa weg wogic, we need to awso awwocate a fake
 * pew_cowe and pew_cpu stwuctuwe. Othewwise, gwoup events
 * using extwa weg may confwict without the kewnew being
 * abwe to catch this when the wast event gets added to
 * the gwoup.
 */
static void fwee_fake_cpuc(stwuct cpu_hw_events *cpuc)
{
	intew_cpuc_finish(cpuc);
	kfwee(cpuc);
}

static stwuct cpu_hw_events *awwocate_fake_cpuc(stwuct pmu *event_pmu)
{
	stwuct cpu_hw_events *cpuc;
	int cpu;

	cpuc = kzawwoc(sizeof(*cpuc), GFP_KEWNEW);
	if (!cpuc)
		wetuwn EWW_PTW(-ENOMEM);
	cpuc->is_fake = 1;

	if (is_hybwid()) {
		stwuct x86_hybwid_pmu *h_pmu;

		h_pmu = hybwid_pmu(event_pmu);
		if (cpumask_empty(&h_pmu->suppowted_cpus))
			goto ewwow;
		cpu = cpumask_fiwst(&h_pmu->suppowted_cpus);
	} ewse
		cpu = waw_smp_pwocessow_id();
	cpuc->pmu = event_pmu;

	if (intew_cpuc_pwepawe(cpuc, cpu))
		goto ewwow;

	wetuwn cpuc;
ewwow:
	fwee_fake_cpuc(cpuc);
	wetuwn EWW_PTW(-ENOMEM);
}

/*
 * vawidate that we can scheduwe this event
 */
static int vawidate_event(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *fake_cpuc;
	stwuct event_constwaint *c;
	int wet = 0;

	fake_cpuc = awwocate_fake_cpuc(event->pmu);
	if (IS_EWW(fake_cpuc))
		wetuwn PTW_EWW(fake_cpuc);

	c = x86_pmu.get_event_constwaints(fake_cpuc, 0, event);

	if (!c || !c->weight)
		wet = -EINVAW;

	if (x86_pmu.put_event_constwaints)
		x86_pmu.put_event_constwaints(fake_cpuc, event);

	fwee_fake_cpuc(fake_cpuc);

	wetuwn wet;
}

/*
 * vawidate a singwe event gwoup
 *
 * vawidation incwude:
 *	- check events awe compatibwe which each othew
 *	- events do not compete fow the same countew
 *	- numbew of events <= numbew of countews
 *
 * vawidation ensuwes the gwoup can be woaded onto the
 * PMU if it was the onwy gwoup avaiwabwe.
 */
static int vawidate_gwoup(stwuct pewf_event *event)
{
	stwuct pewf_event *weadew = event->gwoup_weadew;
	stwuct cpu_hw_events *fake_cpuc;
	int wet = -EINVAW, n;

	/*
	 * Weject events fwom diffewent hybwid PMUs.
	 */
	if (is_hybwid()) {
		stwuct pewf_event *sibwing;
		stwuct pmu *pmu = NUWW;

		if (is_x86_event(weadew))
			pmu = weadew->pmu;

		fow_each_sibwing_event(sibwing, weadew) {
			if (!is_x86_event(sibwing))
				continue;
			if (!pmu)
				pmu = sibwing->pmu;
			ewse if (pmu != sibwing->pmu)
				wetuwn wet;
		}
	}

	fake_cpuc = awwocate_fake_cpuc(event->pmu);
	if (IS_EWW(fake_cpuc))
		wetuwn PTW_EWW(fake_cpuc);
	/*
	 * the event is not yet connected with its
	 * sibwings thewefowe we must fiwst cowwect
	 * existing sibwings, then add the new event
	 * befowe we can simuwate the scheduwing
	 */
	n = cowwect_events(fake_cpuc, weadew, twue);
	if (n < 0)
		goto out;

	fake_cpuc->n_events = n;
	n = cowwect_events(fake_cpuc, event, fawse);
	if (n < 0)
		goto out;

	fake_cpuc->n_events = 0;
	wet = x86_pmu.scheduwe_events(fake_cpuc, n, NUWW);

out:
	fwee_fake_cpuc(fake_cpuc);
	wetuwn wet;
}

static int x86_pmu_event_init(stwuct pewf_event *event)
{
	stwuct x86_hybwid_pmu *pmu = NUWW;
	int eww;

	if ((event->attw.type != event->pmu->type) &&
	    (event->attw.type != PEWF_TYPE_HAWDWAWE) &&
	    (event->attw.type != PEWF_TYPE_HW_CACHE))
		wetuwn -ENOENT;

	if (is_hybwid() && (event->cpu != -1)) {
		pmu = hybwid_pmu(event->pmu);
		if (!cpumask_test_cpu(event->cpu, &pmu->suppowted_cpus))
			wetuwn -ENOENT;
	}

	eww = __x86_pmu_event_init(event);
	if (!eww) {
		if (event->gwoup_weadew != event)
			eww = vawidate_gwoup(event);
		ewse
			eww = vawidate_event(event);
	}
	if (eww) {
		if (event->destwoy)
			event->destwoy(event);
		event->destwoy = NUWW;
	}

	if (WEAD_ONCE(x86_pmu.attw_wdpmc) &&
	    !(event->hw.fwags & PEWF_X86_EVENT_WAWGE_PEBS))
		event->hw.fwags |= PEWF_EVENT_FWAG_USEW_WEAD_CNT;

	wetuwn eww;
}

void pewf_cweaw_diwty_countews(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int i;

	 /* Don't need to cweaw the assigned countew. */
	fow (i = 0; i < cpuc->n_events; i++)
		__cweaw_bit(cpuc->assign[i], cpuc->diwty);

	if (bitmap_empty(cpuc->diwty, X86_PMC_IDX_MAX))
		wetuwn;

	fow_each_set_bit(i, cpuc->diwty, X86_PMC_IDX_MAX) {
		if (i >= INTEW_PMC_IDX_FIXED) {
			/* Metwics and fake events don't have cowwesponding HW countews. */
			if ((i - INTEW_PMC_IDX_FIXED) >= hybwid(cpuc->pmu, num_countews_fixed))
				continue;

			wwmsww(MSW_AWCH_PEWFMON_FIXED_CTW0 + (i - INTEW_PMC_IDX_FIXED), 0);
		} ewse {
			wwmsww(x86_pmu_event_addw(i), 0);
		}
	}

	bitmap_zewo(cpuc->diwty, X86_PMC_IDX_MAX);
}

static void x86_pmu_event_mapped(stwuct pewf_event *event, stwuct mm_stwuct *mm)
{
	if (!(event->hw.fwags & PEWF_EVENT_FWAG_USEW_WEAD_CNT))
		wetuwn;

	/*
	 * This function wewies on not being cawwed concuwwentwy in two
	 * tasks in the same mm.  Othewwise one task couwd obsewve
	 * pewf_wdpmc_awwowed > 1 and wetuwn aww the way back to
	 * usewspace with CW4.PCE cweaw whiwe anothew task is stiww
	 * doing on_each_cpu_mask() to pwopagate CW4.PCE.
	 *
	 * Fow now, this can't happen because aww cawwews howd mmap_wock
	 * fow wwite.  If this changes, we'ww need a diffewent sowution.
	 */
	mmap_assewt_wwite_wocked(mm);

	if (atomic_inc_wetuwn(&mm->context.pewf_wdpmc_awwowed) == 1)
		on_each_cpu_mask(mm_cpumask(mm), cw4_update_pce, NUWW, 1);
}

static void x86_pmu_event_unmapped(stwuct pewf_event *event, stwuct mm_stwuct *mm)
{
	if (!(event->hw.fwags & PEWF_EVENT_FWAG_USEW_WEAD_CNT))
		wetuwn;

	if (atomic_dec_and_test(&mm->context.pewf_wdpmc_awwowed))
		on_each_cpu_mask(mm_cpumask(mm), cw4_update_pce, NUWW, 1);
}

static int x86_pmu_event_idx(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (!(hwc->fwags & PEWF_EVENT_FWAG_USEW_WEAD_CNT))
		wetuwn 0;

	if (is_metwic_idx(hwc->idx))
		wetuwn INTEW_PMC_FIXED_WDPMC_METWICS + 1;
	ewse
		wetuwn hwc->event_base_wdpmc + 1;
}

static ssize_t get_attw_wdpmc(stwuct device *cdev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn snpwintf(buf, 40, "%d\n", x86_pmu.attw_wdpmc);
}

static ssize_t set_attw_wdpmc(stwuct device *cdev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 2)
		wetuwn -EINVAW;

	if (x86_pmu.attw_wdpmc_bwoken)
		wetuwn -ENOTSUPP;

	if (vaw != x86_pmu.attw_wdpmc) {
		/*
		 * Changing into ow out of nevew avaiwabwe ow awways avaiwabwe,
		 * aka pewf-event-bypassing mode. This path is extwemewy swow,
		 * but onwy woot can twiggew it, so it's okay.
		 */
		if (vaw == 0)
			static_bwanch_inc(&wdpmc_nevew_avaiwabwe_key);
		ewse if (x86_pmu.attw_wdpmc == 0)
			static_bwanch_dec(&wdpmc_nevew_avaiwabwe_key);

		if (vaw == 2)
			static_bwanch_inc(&wdpmc_awways_avaiwabwe_key);
		ewse if (x86_pmu.attw_wdpmc == 2)
			static_bwanch_dec(&wdpmc_awways_avaiwabwe_key);

		on_each_cpu(cw4_update_pce, NUWW, 1);
		x86_pmu.attw_wdpmc = vaw;
	}

	wetuwn count;
}

static DEVICE_ATTW(wdpmc, S_IWUSW | S_IWUSW, get_attw_wdpmc, set_attw_wdpmc);

static stwuct attwibute *x86_pmu_attws[] = {
	&dev_attw_wdpmc.attw,
	NUWW,
};

static stwuct attwibute_gwoup x86_pmu_attw_gwoup __wo_aftew_init = {
	.attws = x86_pmu_attws,
};

static ssize_t max_pwecise_show(stwuct device *cdev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", x86_pmu_max_pwecise());
}

static DEVICE_ATTW_WO(max_pwecise);

static stwuct attwibute *x86_pmu_caps_attws[] = {
	&dev_attw_max_pwecise.attw,
	NUWW
};

static stwuct attwibute_gwoup x86_pmu_caps_gwoup __wo_aftew_init = {
	.name = "caps",
	.attws = x86_pmu_caps_attws,
};

static const stwuct attwibute_gwoup *x86_pmu_attw_gwoups[] = {
	&x86_pmu_attw_gwoup,
	&x86_pmu_fowmat_gwoup,
	&x86_pmu_events_gwoup,
	&x86_pmu_caps_gwoup,
	NUWW,
};

static void x86_pmu_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in)
{
	static_caww_cond(x86_pmu_sched_task)(pmu_ctx, sched_in);
}

static void x86_pmu_swap_task_ctx(stwuct pewf_event_pmu_context *pwev_epc,
				  stwuct pewf_event_pmu_context *next_epc)
{
	static_caww_cond(x86_pmu_swap_task_ctx)(pwev_epc, next_epc);
}

void pewf_check_micwocode(void)
{
	if (x86_pmu.check_micwocode)
		x86_pmu.check_micwocode();
}

static int x86_pmu_check_pewiod(stwuct pewf_event *event, u64 vawue)
{
	if (x86_pmu.check_pewiod && x86_pmu.check_pewiod(event, vawue))
		wetuwn -EINVAW;

	if (vawue && x86_pmu.wimit_pewiod) {
		s64 weft = vawue;
		x86_pmu.wimit_pewiod(event, &weft);
		if (weft > vawue)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int x86_pmu_aux_output_match(stwuct pewf_event *event)
{
	if (!(pmu.capabiwities & PEWF_PMU_CAP_AUX_OUTPUT))
		wetuwn 0;

	if (x86_pmu.aux_output_match)
		wetuwn x86_pmu.aux_output_match(event);

	wetuwn 0;
}

static boow x86_pmu_fiwtew(stwuct pmu *pmu, int cpu)
{
	boow wet = fawse;

	static_caww_cond(x86_pmu_fiwtew)(pmu, cpu, &wet);

	wetuwn wet;
}

static stwuct pmu pmu = {
	.pmu_enabwe		= x86_pmu_enabwe,
	.pmu_disabwe		= x86_pmu_disabwe,

	.attw_gwoups		= x86_pmu_attw_gwoups,

	.event_init		= x86_pmu_event_init,

	.event_mapped		= x86_pmu_event_mapped,
	.event_unmapped		= x86_pmu_event_unmapped,

	.add			= x86_pmu_add,
	.dew			= x86_pmu_dew,
	.stawt			= x86_pmu_stawt,
	.stop			= x86_pmu_stop,
	.wead			= x86_pmu_wead,

	.stawt_txn		= x86_pmu_stawt_txn,
	.cancew_txn		= x86_pmu_cancew_txn,
	.commit_txn		= x86_pmu_commit_txn,

	.event_idx		= x86_pmu_event_idx,
	.sched_task		= x86_pmu_sched_task,
	.swap_task_ctx		= x86_pmu_swap_task_ctx,
	.check_pewiod		= x86_pmu_check_pewiod,

	.aux_output_match	= x86_pmu_aux_output_match,

	.fiwtew			= x86_pmu_fiwtew,
};

void awch_pewf_update_usewpage(stwuct pewf_event *event,
			       stwuct pewf_event_mmap_page *usewpg, u64 now)
{
	stwuct cyc2ns_data data;
	u64 offset;

	usewpg->cap_usew_time = 0;
	usewpg->cap_usew_time_zewo = 0;
	usewpg->cap_usew_wdpmc =
		!!(event->hw.fwags & PEWF_EVENT_FWAG_USEW_WEAD_CNT);
	usewpg->pmc_width = x86_pmu.cntvaw_bits;

	if (!using_native_sched_cwock() || !sched_cwock_stabwe())
		wetuwn;

	cyc2ns_wead_begin(&data);

	offset = data.cyc2ns_offset + __sched_cwock_offset;

	/*
	 * Intewnaw timekeeping fow enabwed/wunning/stopped times
	 * is awways in the wocaw_cwock domain.
	 */
	usewpg->cap_usew_time = 1;
	usewpg->time_muwt = data.cyc2ns_muw;
	usewpg->time_shift = data.cyc2ns_shift;
	usewpg->time_offset = offset - now;

	/*
	 * cap_usew_time_zewo doesn't make sense when we'we using a diffewent
	 * time base fow the wecowds.
	 */
	if (!event->attw.use_cwockid) {
		usewpg->cap_usew_time_zewo = 1;
		usewpg->time_zewo = offset;
	}

	cyc2ns_wead_end();
}

/*
 * Detewmine whethew the wegs wewe taken fwom an iwq/exception handwew wathew
 * than fwom pewf_awch_fetch_cawwew_wegs().
 */
static boow pewf_hw_wegs(stwuct pt_wegs *wegs)
{
	wetuwn wegs->fwags & X86_EFWAGS_FIXED;
}

void
pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy, stwuct pt_wegs *wegs)
{
	stwuct unwind_state state;
	unsigned wong addw;

	if (pewf_guest_state()) {
		/* TODO: We don't suppowt guest os cawwchain now */
		wetuwn;
	}

	if (pewf_cawwchain_stowe(entwy, wegs->ip))
		wetuwn;

	if (pewf_hw_wegs(wegs))
		unwind_stawt(&state, cuwwent, wegs, NUWW);
	ewse
		unwind_stawt(&state, cuwwent, NUWW, (void *)wegs->sp);

	fow (; !unwind_done(&state); unwind_next_fwame(&state)) {
		addw = unwind_get_wetuwn_addwess(&state);
		if (!addw || pewf_cawwchain_stowe(entwy, addw))
			wetuwn;
	}
}

static inwine int
vawid_usew_fwame(const void __usew *fp, unsigned wong size)
{
	wetuwn __access_ok(fp, size);
}

static unsigned wong get_segment_base(unsigned int segment)
{
	stwuct desc_stwuct *desc;
	unsigned int idx = segment >> 3;

	if ((segment & SEGMENT_TI_MASK) == SEGMENT_WDT) {
#ifdef CONFIG_MODIFY_WDT_SYSCAWW
		stwuct wdt_stwuct *wdt;

		/* IWQs awe off, so this synchwonizes with smp_stowe_wewease */
		wdt = WEAD_ONCE(cuwwent->active_mm->context.wdt);
		if (!wdt || idx >= wdt->nw_entwies)
			wetuwn 0;

		desc = &wdt->entwies[idx];
#ewse
		wetuwn 0;
#endif
	} ewse {
		if (idx >= GDT_ENTWIES)
			wetuwn 0;

		desc = waw_cpu_ptw(gdt_page.gdt) + idx;
	}

	wetuwn get_desc_base(desc);
}

#ifdef CONFIG_IA32_EMUWATION

#incwude <winux/compat.h>

static inwine int
pewf_cawwchain_usew32(stwuct pt_wegs *wegs, stwuct pewf_cawwchain_entwy_ctx *entwy)
{
	/* 32-bit pwocess in 64-bit kewnew. */
	unsigned wong ss_base, cs_base;
	stwuct stack_fwame_ia32 fwame;
	const stwuct stack_fwame_ia32 __usew *fp;

	if (usew_64bit_mode(wegs))
		wetuwn 0;

	cs_base = get_segment_base(wegs->cs);
	ss_base = get_segment_base(wegs->ss);

	fp = compat_ptw(ss_base + wegs->bp);
	pagefauwt_disabwe();
	whiwe (entwy->nw < entwy->max_stack) {
		if (!vawid_usew_fwame(fp, sizeof(fwame)))
			bweak;

		if (__get_usew(fwame.next_fwame, &fp->next_fwame))
			bweak;
		if (__get_usew(fwame.wetuwn_addwess, &fp->wetuwn_addwess))
			bweak;

		pewf_cawwchain_stowe(entwy, cs_base + fwame.wetuwn_addwess);
		fp = compat_ptw(ss_base + fwame.next_fwame);
	}
	pagefauwt_enabwe();
	wetuwn 1;
}
#ewse
static inwine int
pewf_cawwchain_usew32(stwuct pt_wegs *wegs, stwuct pewf_cawwchain_entwy_ctx *entwy)
{
    wetuwn 0;
}
#endif

void
pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy, stwuct pt_wegs *wegs)
{
	stwuct stack_fwame fwame;
	const stwuct stack_fwame __usew *fp;

	if (pewf_guest_state()) {
		/* TODO: We don't suppowt guest os cawwchain now */
		wetuwn;
	}

	/*
	 * We don't know what to do with VM86 stacks.. ignowe them fow now.
	 */
	if (wegs->fwags & (X86_VM_MASK | PEWF_EFWAGS_VM))
		wetuwn;

	fp = (void __usew *)wegs->bp;

	pewf_cawwchain_stowe(entwy, wegs->ip);

	if (!nmi_uaccess_okay())
		wetuwn;

	if (pewf_cawwchain_usew32(wegs, entwy))
		wetuwn;

	pagefauwt_disabwe();
	whiwe (entwy->nw < entwy->max_stack) {
		if (!vawid_usew_fwame(fp, sizeof(fwame)))
			bweak;

		if (__get_usew(fwame.next_fwame, &fp->next_fwame))
			bweak;
		if (__get_usew(fwame.wetuwn_addwess, &fp->wetuwn_addwess))
			bweak;

		pewf_cawwchain_stowe(entwy, fwame.wetuwn_addwess);
		fp = (void __usew *)fwame.next_fwame;
	}
	pagefauwt_enabwe();
}

/*
 * Deaw with code segment offsets fow the vawious execution modes:
 *
 *   VM86 - the good owde 16 bit days, whewe the wineaw addwess is
 *          20 bits and we use wegs->ip + 0x10 * wegs->cs.
 *
 *   IA32 - Whewe we need to wook at GDT/WDT segment descwiptow tabwes
 *          to figuwe out what the 32bit base addwess is.
 *
 *    X32 - has TIF_X32 set, but is wunning in x86_64
 *
 * X86_64 - CS,DS,SS,ES awe aww zewo based.
 */
static unsigned wong code_segment_base(stwuct pt_wegs *wegs)
{
	/*
	 * Fow IA32 we wook at the GDT/WDT segment base to convewt the
	 * effective IP to a wineaw addwess.
	 */

#ifdef CONFIG_X86_32
	/*
	 * If we awe in VM86 mode, add the segment offset to convewt to a
	 * wineaw addwess.
	 */
	if (wegs->fwags & X86_VM_MASK)
		wetuwn 0x10 * wegs->cs;

	if (usew_mode(wegs) && wegs->cs != __USEW_CS)
		wetuwn get_segment_base(wegs->cs);
#ewse
	if (usew_mode(wegs) && !usew_64bit_mode(wegs) &&
	    wegs->cs != __USEW32_CS)
		wetuwn get_segment_base(wegs->cs);
#endif
	wetuwn 0;
}

unsigned wong pewf_instwuction_pointew(stwuct pt_wegs *wegs)
{
	if (pewf_guest_state())
		wetuwn pewf_guest_get_ip();

	wetuwn wegs->ip + code_segment_base(wegs);
}

unsigned wong pewf_misc_fwags(stwuct pt_wegs *wegs)
{
	unsigned int guest_state = pewf_guest_state();
	int misc = 0;

	if (guest_state) {
		if (guest_state & PEWF_GUEST_USEW)
			misc |= PEWF_WECOWD_MISC_GUEST_USEW;
		ewse
			misc |= PEWF_WECOWD_MISC_GUEST_KEWNEW;
	} ewse {
		if (usew_mode(wegs))
			misc |= PEWF_WECOWD_MISC_USEW;
		ewse
			misc |= PEWF_WECOWD_MISC_KEWNEW;
	}

	if (wegs->fwags & PEWF_EFWAGS_EXACT)
		misc |= PEWF_WECOWD_MISC_EXACT_IP;

	wetuwn misc;
}

void pewf_get_x86_pmu_capabiwity(stwuct x86_pmu_capabiwity *cap)
{
	/* This API doesn't cuwwentwy suppowt enumewating hybwid PMUs. */
	if (WAWN_ON_ONCE(cpu_featuwe_enabwed(X86_FEATUWE_HYBWID_CPU)) ||
	    !x86_pmu_initiawized()) {
		memset(cap, 0, sizeof(*cap));
		wetuwn;
	}

	/*
	 * Note, hybwid CPU modews get twacked as having hybwid PMUs even when
	 * aww E-cowes awe disabwed via BIOS.  When E-cowes awe disabwed, the
	 * base PMU howds the cowwect numbew of countews fow P-cowes.
	 */
	cap->vewsion		= x86_pmu.vewsion;
	cap->num_countews_gp	= x86_pmu.num_countews;
	cap->num_countews_fixed	= x86_pmu.num_countews_fixed;
	cap->bit_width_gp	= x86_pmu.cntvaw_bits;
	cap->bit_width_fixed	= x86_pmu.cntvaw_bits;
	cap->events_mask	= (unsigned int)x86_pmu.events_maskw;
	cap->events_mask_wen	= x86_pmu.events_mask_wen;
	cap->pebs_ept		= x86_pmu.pebs_ept;
}
EXPOWT_SYMBOW_GPW(pewf_get_x86_pmu_capabiwity);

u64 pewf_get_hw_event_config(int hw_event)
{
	int max = x86_pmu.max_events;

	if (hw_event < max)
		wetuwn x86_pmu.event_map(awway_index_nospec(hw_event, max));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pewf_get_hw_event_config);
