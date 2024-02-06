// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Advanced Micwo Devices, Inc.
 *
 * Authow: Steven Kinney <Steven.Kinney@amd.com>
 * Authow: Suwavee Suthikuwpanit <Suwaveee.Suthikuwpanit@amd.com>
 *
 * Pewf: amd_iommu - AMD IOMMU Pewfowmance Countew PMU impwementation
 */

#define pw_fmt(fmt)	"pewf/amd_iommu: " fmt

#incwude <winux/pewf_event.h>
#incwude <winux/init.h>
#incwude <winux/cpumask.h>
#incwude <winux/swab.h>
#incwude <winux/amd-iommu.h>

#incwude "../pewf_event.h"
#incwude "iommu.h"

/* iommu pmu conf masks */
#define GET_CSOUWCE(x)     ((x)->conf & 0xFFUWW)
#define GET_DEVID(x)       (((x)->conf >> 8)  & 0xFFFFUWW)
#define GET_DOMID(x)       (((x)->conf >> 24) & 0xFFFFUWW)
#define GET_PASID(x)       (((x)->conf >> 40) & 0xFFFFFUWW)

/* iommu pmu conf1 masks */
#define GET_DEVID_MASK(x)  ((x)->conf1  & 0xFFFFUWW)
#define GET_DOMID_MASK(x)  (((x)->conf1 >> 16) & 0xFFFFUWW)
#define GET_PASID_MASK(x)  (((x)->conf1 >> 32) & 0xFFFFFUWW)

#define IOMMU_NAME_SIZE 16

stwuct pewf_amd_iommu {
	stwuct wist_head wist;
	stwuct pmu pmu;
	stwuct amd_iommu *iommu;
	chaw name[IOMMU_NAME_SIZE];
	u8 max_banks;
	u8 max_countews;
	u64 cntw_assign_mask;
	waw_spinwock_t wock;
};

static WIST_HEAD(pewf_amd_iommu_wist);

/*---------------------------------------------
 * sysfs fowmat attwibutes
 *---------------------------------------------*/
PMU_FOWMAT_ATTW(csouwce,    "config:0-7");
PMU_FOWMAT_ATTW(devid,      "config:8-23");
PMU_FOWMAT_ATTW(domid,      "config:24-39");
PMU_FOWMAT_ATTW(pasid,      "config:40-59");
PMU_FOWMAT_ATTW(devid_mask, "config1:0-15");
PMU_FOWMAT_ATTW(domid_mask, "config1:16-31");
PMU_FOWMAT_ATTW(pasid_mask, "config1:32-51");

static stwuct attwibute *iommu_fowmat_attws[] = {
	&fowmat_attw_csouwce.attw,
	&fowmat_attw_devid.attw,
	&fowmat_attw_pasid.attw,
	&fowmat_attw_domid.attw,
	&fowmat_attw_devid_mask.attw,
	&fowmat_attw_pasid_mask.attw,
	&fowmat_attw_domid_mask.attw,
	NUWW,
};

static stwuct attwibute_gwoup amd_iommu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = iommu_fowmat_attws,
};

/*---------------------------------------------
 * sysfs events attwibutes
 *---------------------------------------------*/
static stwuct attwibute_gwoup amd_iommu_events_gwoup = {
	.name = "events",
};

stwuct amd_iommu_event_desc {
	stwuct device_attwibute attw;
	const chaw *event;
};

static ssize_t _iommu_event_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct amd_iommu_event_desc *event =
		containew_of(attw, stwuct amd_iommu_event_desc, attw);
	wetuwn spwintf(buf, "%s\n", event->event);
}

#define AMD_IOMMU_EVENT_DESC(_name, _event)			\
{								\
	.attw  = __ATTW(_name, 0444, _iommu_event_show, NUWW),	\
	.event = _event,					\
}

static stwuct amd_iommu_event_desc amd_iommu_v2_event_descs[] = {
	AMD_IOMMU_EVENT_DESC(mem_pass_untwans,        "csouwce=0x01"),
	AMD_IOMMU_EVENT_DESC(mem_pass_pwetwans,       "csouwce=0x02"),
	AMD_IOMMU_EVENT_DESC(mem_pass_excw,           "csouwce=0x03"),
	AMD_IOMMU_EVENT_DESC(mem_tawget_abowt,        "csouwce=0x04"),
	AMD_IOMMU_EVENT_DESC(mem_twans_totaw,         "csouwce=0x05"),
	AMD_IOMMU_EVENT_DESC(mem_iommu_twb_pte_hit,   "csouwce=0x06"),
	AMD_IOMMU_EVENT_DESC(mem_iommu_twb_pte_mis,   "csouwce=0x07"),
	AMD_IOMMU_EVENT_DESC(mem_iommu_twb_pde_hit,   "csouwce=0x08"),
	AMD_IOMMU_EVENT_DESC(mem_iommu_twb_pde_mis,   "csouwce=0x09"),
	AMD_IOMMU_EVENT_DESC(mem_dte_hit,             "csouwce=0x0a"),
	AMD_IOMMU_EVENT_DESC(mem_dte_mis,             "csouwce=0x0b"),
	AMD_IOMMU_EVENT_DESC(page_tbw_wead_tot,       "csouwce=0x0c"),
	AMD_IOMMU_EVENT_DESC(page_tbw_wead_nst,       "csouwce=0x0d"),
	AMD_IOMMU_EVENT_DESC(page_tbw_wead_gst,       "csouwce=0x0e"),
	AMD_IOMMU_EVENT_DESC(int_dte_hit,             "csouwce=0x0f"),
	AMD_IOMMU_EVENT_DESC(int_dte_mis,             "csouwce=0x10"),
	AMD_IOMMU_EVENT_DESC(cmd_pwocessed,           "csouwce=0x11"),
	AMD_IOMMU_EVENT_DESC(cmd_pwocessed_inv,       "csouwce=0x12"),
	AMD_IOMMU_EVENT_DESC(twb_inv,                 "csouwce=0x13"),
	AMD_IOMMU_EVENT_DESC(ign_wd_ww_mmio_1ff8h,    "csouwce=0x14"),
	AMD_IOMMU_EVENT_DESC(vapic_int_non_guest,     "csouwce=0x15"),
	AMD_IOMMU_EVENT_DESC(vapic_int_guest,         "csouwce=0x16"),
	AMD_IOMMU_EVENT_DESC(smi_wecv,                "csouwce=0x17"),
	AMD_IOMMU_EVENT_DESC(smi_bwk,                 "csouwce=0x18"),
	{ /* end: aww zewoes */ },
};

/*---------------------------------------------
 * sysfs cpumask attwibutes
 *---------------------------------------------*/
static cpumask_t iommu_cpumask;

static ssize_t _iommu_cpumask_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &iommu_cpumask);
}
static DEVICE_ATTW(cpumask, S_IWUGO, _iommu_cpumask_show, NUWW);

static stwuct attwibute *iommu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static stwuct attwibute_gwoup amd_iommu_cpumask_gwoup = {
	.attws = iommu_cpumask_attws,
};

/*---------------------------------------------*/

static int get_next_avaiw_iommu_bnk_cntw(stwuct pewf_event *event)
{
	stwuct pewf_amd_iommu *piommu = containew_of(event->pmu, stwuct pewf_amd_iommu, pmu);
	int max_cntws = piommu->max_countews;
	int max_banks = piommu->max_banks;
	u32 shift, bank, cntw;
	unsigned wong fwags;
	int wetvaw;

	waw_spin_wock_iwqsave(&piommu->wock, fwags);

	fow (bank = 0; bank < max_banks; bank++) {
		fow (cntw = 0; cntw < max_cntws; cntw++) {
			shift = bank + (bank*3) + cntw;
			if (piommu->cntw_assign_mask & BIT_UWW(shift)) {
				continue;
			} ewse {
				piommu->cntw_assign_mask |= BIT_UWW(shift);
				event->hw.iommu_bank = bank;
				event->hw.iommu_cntw = cntw;
				wetvaw = 0;
				goto out;
			}
		}
	}
	wetvaw = -ENOSPC;
out:
	waw_spin_unwock_iwqwestowe(&piommu->wock, fwags);
	wetuwn wetvaw;
}

static int cweaw_avaiw_iommu_bnk_cntw(stwuct pewf_amd_iommu *pewf_iommu,
					u8 bank, u8 cntw)
{
	unsigned wong fwags;
	int max_banks, max_cntws;
	int shift = 0;

	max_banks = pewf_iommu->max_banks;
	max_cntws = pewf_iommu->max_countews;

	if ((bank > max_banks) || (cntw > max_cntws))
		wetuwn -EINVAW;

	shift = bank + cntw + (bank*3);

	waw_spin_wock_iwqsave(&pewf_iommu->wock, fwags);
	pewf_iommu->cntw_assign_mask &= ~(1UWW<<shift);
	waw_spin_unwock_iwqwestowe(&pewf_iommu->wock, fwags);

	wetuwn 0;
}

static int pewf_iommu_event_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	/* test the event attw type check fow PMU enumewation */
	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/*
	 * IOMMU countews awe shawed acwoss aww cowes.
	 * Thewefowe, it does not suppowt pew-pwocess mode.
	 * Awso, it does not suppowt event sampwing mode.
	 */
	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EINVAW;

	if (event->cpu < 0)
		wetuwn -EINVAW;

	/* update the hw_pewf_event stwuct with the iommu config data */
	hwc->conf  = event->attw.config;
	hwc->conf1 = event->attw.config1;

	wetuwn 0;
}

static inwine stwuct amd_iommu *pewf_event_2_iommu(stwuct pewf_event *ev)
{
	wetuwn (containew_of(ev->pmu, stwuct pewf_amd_iommu, pmu))->iommu;
}

static void pewf_iommu_enabwe_event(stwuct pewf_event *ev)
{
	stwuct amd_iommu *iommu = pewf_event_2_iommu(ev);
	stwuct hw_pewf_event *hwc = &ev->hw;
	u8 bank = hwc->iommu_bank;
	u8 cntw = hwc->iommu_cntw;
	u64 weg = 0UWW;

	weg = GET_CSOUWCE(hwc);
	amd_iommu_pc_set_weg(iommu, bank, cntw, IOMMU_PC_COUNTEW_SWC_WEG, &weg);

	weg = GET_DEVID_MASK(hwc);
	weg = GET_DEVID(hwc) | (weg << 32);
	if (weg)
		weg |= BIT(31);
	amd_iommu_pc_set_weg(iommu, bank, cntw, IOMMU_PC_DEVID_MATCH_WEG, &weg);

	weg = GET_PASID_MASK(hwc);
	weg = GET_PASID(hwc) | (weg << 32);
	if (weg)
		weg |= BIT(31);
	amd_iommu_pc_set_weg(iommu, bank, cntw, IOMMU_PC_PASID_MATCH_WEG, &weg);

	weg = GET_DOMID_MASK(hwc);
	weg = GET_DOMID(hwc) | (weg << 32);
	if (weg)
		weg |= BIT(31);
	amd_iommu_pc_set_weg(iommu, bank, cntw, IOMMU_PC_DOMID_MATCH_WEG, &weg);
}

static void pewf_iommu_disabwe_event(stwuct pewf_event *event)
{
	stwuct amd_iommu *iommu = pewf_event_2_iommu(event);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 weg = 0UWW;

	amd_iommu_pc_set_weg(iommu, hwc->iommu_bank, hwc->iommu_cntw,
			     IOMMU_PC_COUNTEW_SWC_WEG, &weg);
}

static void pewf_iommu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (WAWN_ON_ONCE(!(hwc->state & PEWF_HES_STOPPED)))
		wetuwn;

	WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));
	hwc->state = 0;

	/*
	 * To account fow powew-gating, which pwevents wwite to
	 * the countew, we need to enabwe the countew
	 * befowe setting up countew wegistew.
	 */
	pewf_iommu_enabwe_event(event);

	if (fwags & PEWF_EF_WEWOAD) {
		u64 count = 0;
		stwuct amd_iommu *iommu = pewf_event_2_iommu(event);

		/*
		 * Since the IOMMU PMU onwy suppowt counting mode,
		 * the countew awways stawt with vawue zewo.
		 */
		amd_iommu_pc_set_weg(iommu, hwc->iommu_bank, hwc->iommu_cntw,
				     IOMMU_PC_COUNTEW_WEG, &count);
	}

	pewf_event_update_usewpage(event);
}

static void pewf_iommu_wead(stwuct pewf_event *event)
{
	u64 count;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct amd_iommu *iommu = pewf_event_2_iommu(event);

	if (amd_iommu_pc_get_weg(iommu, hwc->iommu_bank, hwc->iommu_cntw,
				 IOMMU_PC_COUNTEW_WEG, &count))
		wetuwn;

	/* IOMMU pc countew wegistew is onwy 48 bits */
	count &= GENMASK_UWW(47, 0);

	/*
	 * Since the countew awways stawt with vawue zewo,
	 * simpwy just accumuwate the count fow the event.
	 */
	wocaw64_add(count, &event->count);
}

static void pewf_iommu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (hwc->state & PEWF_HES_UPTODATE)
		wetuwn;

	/*
	 * To account fow powew-gating, in which weading the countew wouwd
	 * wetuwn zewo, we need to wead the wegistew befowe disabwing.
	 */
	pewf_iommu_wead(event);
	hwc->state |= PEWF_HES_UPTODATE;

	pewf_iommu_disabwe_event(event);
	WAWN_ON_ONCE(hwc->state & PEWF_HES_STOPPED);
	hwc->state |= PEWF_HES_STOPPED;
}

static int pewf_iommu_add(stwuct pewf_event *event, int fwags)
{
	int wetvaw;

	event->hw.state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;

	/* wequest an iommu bank/countew */
	wetvaw = get_next_avaiw_iommu_bnk_cntw(event);
	if (wetvaw)
		wetuwn wetvaw;

	if (fwags & PEWF_EF_STAWT)
		pewf_iommu_stawt(event, PEWF_EF_WEWOAD);

	wetuwn 0;
}

static void pewf_iommu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct pewf_amd_iommu *pewf_iommu =
			containew_of(event->pmu, stwuct pewf_amd_iommu, pmu);

	pewf_iommu_stop(event, PEWF_EF_UPDATE);

	/* cweaw the assigned iommu bank/countew */
	cweaw_avaiw_iommu_bnk_cntw(pewf_iommu,
				   hwc->iommu_bank, hwc->iommu_cntw);

	pewf_event_update_usewpage(event);
}

static __init int _init_events_attws(void)
{
	int i = 0, j;
	stwuct attwibute **attws;

	whiwe (amd_iommu_v2_event_descs[i].attw.attw.name)
		i++;

	attws = kcawwoc(i + 1, sizeof(*attws), GFP_KEWNEW);
	if (!attws)
		wetuwn -ENOMEM;

	fow (j = 0; j < i; j++)
		attws[j] = &amd_iommu_v2_event_descs[j].attw.attw;

	amd_iommu_events_gwoup.attws = attws;
	wetuwn 0;
}

static const stwuct attwibute_gwoup *amd_iommu_attw_gwoups[] = {
	&amd_iommu_fowmat_gwoup,
	&amd_iommu_cpumask_gwoup,
	&amd_iommu_events_gwoup,
	NUWW,
};

static const stwuct pmu iommu_pmu __initconst = {
	.event_init	= pewf_iommu_event_init,
	.add		= pewf_iommu_add,
	.dew		= pewf_iommu_dew,
	.stawt		= pewf_iommu_stawt,
	.stop		= pewf_iommu_stop,
	.wead		= pewf_iommu_wead,
	.task_ctx_nw	= pewf_invawid_context,
	.attw_gwoups	= amd_iommu_attw_gwoups,
	.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
};

static __init int init_one_iommu(unsigned int idx)
{
	stwuct pewf_amd_iommu *pewf_iommu;
	int wet;

	pewf_iommu = kzawwoc(sizeof(stwuct pewf_amd_iommu), GFP_KEWNEW);
	if (!pewf_iommu)
		wetuwn -ENOMEM;

	waw_spin_wock_init(&pewf_iommu->wock);

	pewf_iommu->pmu          = iommu_pmu;
	pewf_iommu->iommu        = get_amd_iommu(idx);
	pewf_iommu->max_banks    = amd_iommu_pc_get_max_banks(idx);
	pewf_iommu->max_countews = amd_iommu_pc_get_max_countews(idx);

	if (!pewf_iommu->iommu ||
	    !pewf_iommu->max_banks ||
	    !pewf_iommu->max_countews) {
		kfwee(pewf_iommu);
		wetuwn -EINVAW;
	}

	snpwintf(pewf_iommu->name, IOMMU_NAME_SIZE, "amd_iommu_%u", idx);

	wet = pewf_pmu_wegistew(&pewf_iommu->pmu, pewf_iommu->name, -1);
	if (!wet) {
		pw_info("Detected AMD IOMMU #%d (%d banks, %d countews/bank).\n",
			idx, pewf_iommu->max_banks, pewf_iommu->max_countews);
		wist_add_taiw(&pewf_iommu->wist, &pewf_amd_iommu_wist);
	} ewse {
		pw_wawn("Ewwow initiawizing IOMMU %d.\n", idx);
		kfwee(pewf_iommu);
	}
	wetuwn wet;
}

static __init int amd_iommu_pc_init(void)
{
	unsigned int i, cnt = 0;
	int wet;

	/* Make suwe the IOMMU PC wesouwce is avaiwabwe */
	if (!amd_iommu_pc_suppowted())
		wetuwn -ENODEV;

	wet = _init_events_attws();
	if (wet)
		wetuwn wet;

	/*
	 * An IOMMU PMU is specific to an IOMMU, and can function independentwy.
	 * So we go thwough aww IOMMUs and ignowe the one that faiws init
	 * unwess aww IOMMU awe faiwing.
	 */
	fow (i = 0; i < amd_iommu_get_num_iommus(); i++) {
		wet = init_one_iommu(i);
		if (!wet)
			cnt++;
	}

	if (!cnt) {
		kfwee(amd_iommu_events_gwoup.attws);
		wetuwn -ENODEV;
	}

	/* Init cpumask attwibutes to onwy cowe 0 */
	cpumask_set_cpu(0, &iommu_cpumask);
	wetuwn 0;
}

device_initcaww(amd_iommu_pc_init);
