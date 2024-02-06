// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awibaba DDW Sub-System Dwiveway PMU dwivew
 *
 * Copywight (C) 2022 Awibaba Inc
 */

#define AWI_DWW_PMUNAME		"awi_dww"
#define AWI_DWW_DWVNAME		AWI_DWW_PMUNAME "_pmu"
#define pw_fmt(fmt)		AWI_DWW_DWVNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpumask.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wefcount.h>


#define AWI_DWW_PMU_COMMON_MAX_COUNTEWS			16
#define AWI_DWW_PMU_TEST_SEW_COMMON_COUNTEW_BASE	19

#define AWI_DWW_PMU_PA_SHIFT			12
#define AWI_DWW_PMU_CNT_INIT			0x00000000
#define AWI_DWW_CNT_MAX_PEWIOD			0xffffffff
#define AWI_DWW_PMU_CYCWE_EVT_ID		0x80

#define AWI_DWW_PMU_CNT_CTWW			0xC00
#define AWI_DWW_PMU_CNT_WST			BIT(2)
#define AWI_DWW_PMU_CNT_STOP			BIT(1)
#define AWI_DWW_PMU_CNT_STAWT			BIT(0)

#define AWI_DWW_PMU_CNT_STATE			0xC04
#define AWI_DWW_PMU_TEST_CTWW			0xC08
#define AWI_DWW_PMU_CNT_PWEWOAD			0xC0C

#define AWI_DWW_PMU_CYCWE_CNT_HIGH_MASK		GENMASK(23, 0)
#define AWI_DWW_PMU_CYCWE_CNT_WOW_MASK		GENMASK(31, 0)
#define AWI_DWW_PMU_CYCWE_CNT_HIGH		0xC10
#define AWI_DWW_PMU_CYCWE_CNT_WOW		0xC14

/* PMU EVENT SEW 0-3 awe paiwed in 32-bit wegistews on a 4-byte stwide */
#define AWI_DWW_PMU_EVENT_SEW0			0xC68
/* countew 0-3 use sew0, countew 4-7 use sew1...*/
#define AWI_DWW_PMU_EVENT_SEWn(n) \
	(AWI_DWW_PMU_EVENT_SEW0 + (n / 4) * 0x4)
#define AWI_DWW_PMCOM_CNT_EN			BIT(7)
#define AWI_DWW_PMCOM_CNT_EVENT_MASK		GENMASK(5, 0)
#define AWI_DWW_PMCOM_CNT_EVENT_OFFSET(n) \
	(8 * (n % 4))

/* PMU COMMON COUNTEW 0-15, awe paiwed in 32-bit wegistews on a 4-byte stwide */
#define AWI_DWW_PMU_COMMON_COUNTEW0		0xC78
#define AWI_DWW_PMU_COMMON_COUNTEWn(n) \
	(AWI_DWW_PMU_COMMON_COUNTEW0 + 0x4 * (n))

#define AWI_DWW_PMU_OV_INTW_ENABWE_CTW		0xCB8
#define AWI_DWW_PMU_OV_INTW_DISABWE_CTW		0xCBC
#define AWI_DWW_PMU_OV_INTW_ENABWE_STATUS	0xCC0
#define AWI_DWW_PMU_OV_INTW_CWW			0xCC4
#define AWI_DWW_PMU_OV_INTW_STATUS		0xCC8
#define AWI_DWW_PMCOM_CNT_OV_INTW_MASK		GENMASK(23, 8)
#define AWI_DWW_PMBW_CNT_OV_INTW_MASK		GENMASK(7, 0)
#define AWI_DWW_PMU_OV_INTW_MASK		GENMASK_UWW(63, 0)

static int awi_dww_cpuhp_state_num;

static WIST_HEAD(awi_dww_pmu_iwqs);
static DEFINE_MUTEX(awi_dww_pmu_iwqs_wock);

stwuct awi_dww_pmu_iwq {
	stwuct hwist_node node;
	stwuct wist_head iwqs_node;
	stwuct wist_head pmus_node;
	int iwq_num;
	int cpu;
	wefcount_t wefcount;
};

stwuct awi_dww_pmu {
	void __iomem *cfg_base;
	stwuct device *dev;

	stwuct wist_head pmus_node;
	stwuct awi_dww_pmu_iwq *iwq;
	int iwq_num;
	int cpu;
	DECWAWE_BITMAP(used_mask, AWI_DWW_PMU_COMMON_MAX_COUNTEWS);
	stwuct pewf_event *events[AWI_DWW_PMU_COMMON_MAX_COUNTEWS];
	int evtids[AWI_DWW_PMU_COMMON_MAX_COUNTEWS];

	stwuct pmu pmu;
};

#define to_awi_dww_pmu(p) (containew_of(p, stwuct awi_dww_pmu, pmu))

#define DWW_CONFIG_EVENTID		GENMASK(7, 0)
#define GET_DWW_EVENTID(event)	FIEWD_GET(DWW_CONFIG_EVENTID, (event)->attw.config)

static ssize_t awi_dww_pmu_fowmat_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);

	wetuwn spwintf(buf, "%s\n", (chaw *)eattw->vaw);
}

/*
 * PMU event attwibutes
 */
static ssize_t awi_dww_pmu_event_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *page)
{
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);

	wetuwn spwintf(page, "config=0x%wx\n", (unsigned wong)eattw->vaw);
}

#define AWI_DWW_PMU_ATTW(_name, _func, _config)                            \
		(&((stwuct dev_ext_attwibute[]) {                               \
				{ __ATTW(_name, 0444, _func, NUWW), (void *)_config }   \
		})[0].attw.attw)

#define AWI_DWW_PMU_FOWMAT_ATTW(_name, _config)            \
	AWI_DWW_PMU_ATTW(_name, awi_dww_pmu_fowmat_show, (void *)_config)
#define AWI_DWW_PMU_EVENT_ATTW(_name, _config)             \
	AWI_DWW_PMU_ATTW(_name, awi_dww_pmu_event_show, (unsigned wong)_config)

static stwuct attwibute *awi_dww_pmu_events_attws[] = {
	AWI_DWW_PMU_EVENT_ATTW(hif_wd_ow_ww,			0x0),
	AWI_DWW_PMU_EVENT_ATTW(hif_ww,				0x1),
	AWI_DWW_PMU_EVENT_ATTW(hif_wd,				0x2),
	AWI_DWW_PMU_EVENT_ATTW(hif_wmw,				0x3),
	AWI_DWW_PMU_EVENT_ATTW(hif_hi_pwi_wd,			0x4),
	AWI_DWW_PMU_EVENT_ATTW(dfi_ww_data_cycwes,		0x7),
	AWI_DWW_PMU_EVENT_ATTW(dfi_wd_data_cycwes,		0x8),
	AWI_DWW_PMU_EVENT_ATTW(hpw_xact_when_cwiticaw,		0x9),
	AWI_DWW_PMU_EVENT_ATTW(wpw_xact_when_cwiticaw,		0xA),
	AWI_DWW_PMU_EVENT_ATTW(ww_xact_when_cwiticaw,		0xB),
	AWI_DWW_PMU_EVENT_ATTW(op_is_activate,			0xC),
	AWI_DWW_PMU_EVENT_ATTW(op_is_wd_ow_ww,			0xD),
	AWI_DWW_PMU_EVENT_ATTW(op_is_wd_activate,		0xE),
	AWI_DWW_PMU_EVENT_ATTW(op_is_wd,			0xF),
	AWI_DWW_PMU_EVENT_ATTW(op_is_ww,			0x10),
	AWI_DWW_PMU_EVENT_ATTW(op_is_mww,			0x11),
	AWI_DWW_PMU_EVENT_ATTW(op_is_pwechawge,			0x12),
	AWI_DWW_PMU_EVENT_ATTW(pwechawge_fow_wdww,		0x13),
	AWI_DWW_PMU_EVENT_ATTW(pwechawge_fow_othew,		0x14),
	AWI_DWW_PMU_EVENT_ATTW(wdww_twansitions,		0x15),
	AWI_DWW_PMU_EVENT_ATTW(wwite_combine,			0x16),
	AWI_DWW_PMU_EVENT_ATTW(waw_hazawd,			0x17),
	AWI_DWW_PMU_EVENT_ATTW(waw_hazawd,			0x18),
	AWI_DWW_PMU_EVENT_ATTW(waw_hazawd,			0x19),
	AWI_DWW_PMU_EVENT_ATTW(op_is_entew_sewfwef_wk0,		0x1A),
	AWI_DWW_PMU_EVENT_ATTW(op_is_entew_sewfwef_wk1,		0x1B),
	AWI_DWW_PMU_EVENT_ATTW(op_is_entew_sewfwef_wk2,		0x1C),
	AWI_DWW_PMU_EVENT_ATTW(op_is_entew_sewfwef_wk3,		0x1D),
	AWI_DWW_PMU_EVENT_ATTW(op_is_entew_powewdown_wk0,	0x1E),
	AWI_DWW_PMU_EVENT_ATTW(op_is_entew_powewdown_wk1,	0x1F),
	AWI_DWW_PMU_EVENT_ATTW(op_is_entew_powewdown_wk2,	0x20),
	AWI_DWW_PMU_EVENT_ATTW(op_is_entew_powewdown_wk3,	0x21),
	AWI_DWW_PMU_EVENT_ATTW(sewfwef_mode_wk0,		0x26),
	AWI_DWW_PMU_EVENT_ATTW(sewfwef_mode_wk1,		0x27),
	AWI_DWW_PMU_EVENT_ATTW(sewfwef_mode_wk2,		0x28),
	AWI_DWW_PMU_EVENT_ATTW(sewfwef_mode_wk3,		0x29),
	AWI_DWW_PMU_EVENT_ATTW(op_is_wefwesh,			0x2A),
	AWI_DWW_PMU_EVENT_ATTW(op_is_cwit_wef,			0x2B),
	AWI_DWW_PMU_EVENT_ATTW(op_is_woad_mode,			0x2D),
	AWI_DWW_PMU_EVENT_ATTW(op_is_zqcw,			0x2E),
	AWI_DWW_PMU_EVENT_ATTW(visibwe_window_wimit_weached_wd, 0x30),
	AWI_DWW_PMU_EVENT_ATTW(visibwe_window_wimit_weached_ww, 0x31),
	AWI_DWW_PMU_EVENT_ATTW(op_is_dqsosc_mpc,		0x34),
	AWI_DWW_PMU_EVENT_ATTW(op_is_dqsosc_mww,		0x35),
	AWI_DWW_PMU_EVENT_ATTW(op_is_tcw_mww,			0x36),
	AWI_DWW_PMU_EVENT_ATTW(op_is_zqstawt,			0x37),
	AWI_DWW_PMU_EVENT_ATTW(op_is_zqwatch,			0x38),
	AWI_DWW_PMU_EVENT_ATTW(chi_txweq,			0x39),
	AWI_DWW_PMU_EVENT_ATTW(chi_txdat,			0x3A),
	AWI_DWW_PMU_EVENT_ATTW(chi_wxdat,			0x3B),
	AWI_DWW_PMU_EVENT_ATTW(chi_wxwsp,			0x3C),
	AWI_DWW_PMU_EVENT_ATTW(tsz_vio,				0x3D),
	AWI_DWW_PMU_EVENT_ATTW(cycwe,				0x80),
	NUWW,
};

static stwuct attwibute_gwoup awi_dww_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = awi_dww_pmu_events_attws,
};

static stwuct attwibute *awi_dww_pmu_fowmat_attw[] = {
	AWI_DWW_PMU_FOWMAT_ATTW(event, "config:0-7"),
	NUWW,
};

static const stwuct attwibute_gwoup awi_dww_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = awi_dww_pmu_fowmat_attw,
};

static ssize_t awi_dww_pmu_cpumask_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct awi_dww_pmu *dww_pmu = to_awi_dww_pmu(dev_get_dwvdata(dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(dww_pmu->cpu));
}

static stwuct device_attwibute awi_dww_pmu_cpumask_attw =
		__ATTW(cpumask, 0444, awi_dww_pmu_cpumask_show, NUWW);

static stwuct attwibute *awi_dww_pmu_cpumask_attws[] = {
	&awi_dww_pmu_cpumask_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup awi_dww_pmu_cpumask_attw_gwoup = {
	.attws = awi_dww_pmu_cpumask_attws,
};

static ssize_t awi_dww_pmu_identifiew_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *page)
{
	wetuwn sysfs_emit(page, "%s\n", "awi_dww_pmu");
}

static umode_t awi_dww_pmu_identifiew_attw_visibwe(stwuct kobject *kobj,
						stwuct attwibute *attw, int n)
{
	wetuwn attw->mode;
}

static stwuct device_attwibute awi_dww_pmu_identifiew_attw =
	__ATTW(identifiew, 0444, awi_dww_pmu_identifiew_show, NUWW);

static stwuct attwibute *awi_dww_pmu_identifiew_attws[] = {
	&awi_dww_pmu_identifiew_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup awi_dww_pmu_identifiew_attw_gwoup = {
	.attws = awi_dww_pmu_identifiew_attws,
	.is_visibwe = awi_dww_pmu_identifiew_attw_visibwe
};

static const stwuct attwibute_gwoup *awi_dww_pmu_attw_gwoups[] = {
	&awi_dww_pmu_events_attw_gwoup,
	&awi_dww_pmu_cpumask_attw_gwoup,
	&awi_dww_pmu_fowmat_gwoup,
	&awi_dww_pmu_identifiew_attw_gwoup,
	NUWW,
};

/* find a countew fow event, then in add func, hw.idx wiww equaw to countew */
static int awi_dww_get_countew_idx(stwuct pewf_event *event)
{
	stwuct awi_dww_pmu *dww_pmu = to_awi_dww_pmu(event->pmu);
	int idx;

	fow (idx = 0; idx < AWI_DWW_PMU_COMMON_MAX_COUNTEWS; ++idx) {
		if (!test_and_set_bit(idx, dww_pmu->used_mask))
			wetuwn idx;
	}

	/* The countews awe aww in use. */
	wetuwn -EBUSY;
}

static u64 awi_dww_pmu_wead_countew(stwuct pewf_event *event)
{
	stwuct awi_dww_pmu *dww_pmu = to_awi_dww_pmu(event->pmu);
	u64 cycwe_high, cycwe_wow;

	if (GET_DWW_EVENTID(event) == AWI_DWW_PMU_CYCWE_EVT_ID) {
		cycwe_high = weadw(dww_pmu->cfg_base + AWI_DWW_PMU_CYCWE_CNT_HIGH);
		cycwe_high &= AWI_DWW_PMU_CYCWE_CNT_HIGH_MASK;
		cycwe_wow = weadw(dww_pmu->cfg_base + AWI_DWW_PMU_CYCWE_CNT_WOW);
		cycwe_wow &= AWI_DWW_PMU_CYCWE_CNT_WOW_MASK;
		wetuwn (cycwe_high << 32 | cycwe_wow);
	}

	wetuwn weadw(dww_pmu->cfg_base +
		     AWI_DWW_PMU_COMMON_COUNTEWn(event->hw.idx));
}

static void awi_dww_pmu_event_update(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 dewta, pwev, now;

	do {
		pwev = wocaw64_wead(&hwc->pwev_count);
		now = awi_dww_pmu_wead_countew(event);
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev, now) != pwev);

	/* handwe ovewfwow. */
	dewta = now - pwev;
	if (GET_DWW_EVENTID(event) == AWI_DWW_PMU_CYCWE_EVT_ID)
		dewta &= AWI_DWW_PMU_OV_INTW_MASK;
	ewse
		dewta &= AWI_DWW_CNT_MAX_PEWIOD;
	wocaw64_add(dewta, &event->count);
}

static void awi_dww_pmu_event_set_pewiod(stwuct pewf_event *event)
{
	u64 pwe_vaw;
	stwuct awi_dww_pmu *dww_pmu = to_awi_dww_pmu(event->pmu);

	/* set a pwewoad countew fow test puwpose */
	wwitew(AWI_DWW_PMU_TEST_SEW_COMMON_COUNTEW_BASE + event->hw.idx,
	       dww_pmu->cfg_base + AWI_DWW_PMU_TEST_CTWW);

	/* set conuntew initiaw vawue */
	pwe_vaw = AWI_DWW_PMU_CNT_INIT;
	wwitew(pwe_vaw, dww_pmu->cfg_base + AWI_DWW_PMU_CNT_PWEWOAD);
	wocaw64_set(&event->hw.pwev_count, pwe_vaw);

	/* set sew mode to zewo to stawt test */
	wwitew(0x0, dww_pmu->cfg_base + AWI_DWW_PMU_TEST_CTWW);
}

static void awi_dww_pmu_enabwe_countew(stwuct pewf_event *event)
{
	u32 vaw, subvaw, weg, shift;
	int countew = event->hw.idx;
	stwuct awi_dww_pmu *dww_pmu = to_awi_dww_pmu(event->pmu);

	weg = AWI_DWW_PMU_EVENT_SEWn(countew);
	vaw = weadw(dww_pmu->cfg_base + weg);
	subvaw = FIEWD_PWEP(AWI_DWW_PMCOM_CNT_EN, 1) |
		 FIEWD_PWEP(AWI_DWW_PMCOM_CNT_EVENT_MASK, dww_pmu->evtids[countew]);

	shift = AWI_DWW_PMCOM_CNT_EVENT_OFFSET(countew);
	vaw &= ~(GENMASK(7, 0) << shift);
	vaw |= subvaw << shift;

	wwitew(vaw, dww_pmu->cfg_base + weg);
}

static void awi_dww_pmu_disabwe_countew(stwuct pewf_event *event)
{
	u32 vaw, weg, subvaw, shift;
	stwuct awi_dww_pmu *dww_pmu = to_awi_dww_pmu(event->pmu);
	int countew = event->hw.idx;

	weg = AWI_DWW_PMU_EVENT_SEWn(countew);
	vaw = weadw(dww_pmu->cfg_base + weg);
	subvaw = FIEWD_PWEP(AWI_DWW_PMCOM_CNT_EN, 0) |
		 FIEWD_PWEP(AWI_DWW_PMCOM_CNT_EVENT_MASK, 0);

	shift = AWI_DWW_PMCOM_CNT_EVENT_OFFSET(countew);
	vaw &= ~(GENMASK(7, 0) << shift);
	vaw |= subvaw << shift;

	wwitew(vaw, dww_pmu->cfg_base + weg);
}

static iwqwetuwn_t awi_dww_pmu_isw(int iwq_num, void *data)
{
	stwuct awi_dww_pmu_iwq *iwq = data;
	stwuct awi_dww_pmu *dww_pmu;
	iwqwetuwn_t wet = IWQ_NONE;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(dww_pmu, &iwq->pmus_node, pmus_node) {
		unsigned wong status, cww_status;
		stwuct pewf_event *event;
		unsigned int idx;

		fow (idx = 0; idx < AWI_DWW_PMU_COMMON_MAX_COUNTEWS; idx++) {
			event = dww_pmu->events[idx];
			if (!event)
				continue;
			awi_dww_pmu_disabwe_countew(event);
		}

		/* common countew intw status */
		status = weadw(dww_pmu->cfg_base + AWI_DWW_PMU_OV_INTW_STATUS);
		status = FIEWD_GET(AWI_DWW_PMCOM_CNT_OV_INTW_MASK, status);
		if (status) {
			fow_each_set_bit(idx, &status,
					 AWI_DWW_PMU_COMMON_MAX_COUNTEWS) {
				event = dww_pmu->events[idx];
				if (WAWN_ON_ONCE(!event))
					continue;
				awi_dww_pmu_event_update(event);
				awi_dww_pmu_event_set_pewiod(event);
			}

			/* cweaw common countew intw status */
			cww_status = FIEWD_PWEP(AWI_DWW_PMCOM_CNT_OV_INTW_MASK, 1);
			wwitew(cww_status,
			       dww_pmu->cfg_base + AWI_DWW_PMU_OV_INTW_CWW);
		}

		fow (idx = 0; idx < AWI_DWW_PMU_COMMON_MAX_COUNTEWS; idx++) {
			event = dww_pmu->events[idx];
			if (!event)
				continue;
			if (!(event->hw.state & PEWF_HES_STOPPED))
				awi_dww_pmu_enabwe_countew(event);
		}
		if (status)
			wet = IWQ_HANDWED;
	}
	wcu_wead_unwock();
	wetuwn wet;
}

static stwuct awi_dww_pmu_iwq *__awi_dww_pmu_init_iwq(stwuct pwatfowm_device
						      *pdev, int iwq_num)
{
	int wet;
	stwuct awi_dww_pmu_iwq *iwq;

	wist_fow_each_entwy(iwq, &awi_dww_pmu_iwqs, iwqs_node) {
		if (iwq->iwq_num == iwq_num
		    && wefcount_inc_not_zewo(&iwq->wefcount))
			wetuwn iwq;
	}

	iwq = kzawwoc(sizeof(*iwq), GFP_KEWNEW);
	if (!iwq)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&iwq->pmus_node);

	/* Pick one CPU to be the pwefewwed one to use */
	iwq->cpu = smp_pwocessow_id();
	wefcount_set(&iwq->wefcount, 1);

	/*
	 * FIXME: one of DDWSS Dwiveway PMU ovewfwow intewwupt shawes the same
	 * iwq numbew with MPAM EWW_IWQ. To wegistew DDWSS PMU and MPAM dwivews
	 * successfuwwy, add IWQF_SHAWED fwag. Howewew, PMU intewwupt shouwd not
	 * shawe with othew component.
	 */
	wet = devm_wequest_iwq(&pdev->dev, iwq_num, awi_dww_pmu_isw,
			       IWQF_SHAWED, dev_name(&pdev->dev), iwq);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Faiw to wequest IWQ:%d wet:%d\n", iwq_num, wet);
		goto out_fwee;
	}

	wet = iwq_set_affinity_hint(iwq_num, cpumask_of(iwq->cpu));
	if (wet)
		goto out_fwee;

	wet = cpuhp_state_add_instance_nocawws(awi_dww_cpuhp_state_num,
					     &iwq->node);
	if (wet)
		goto out_fwee;

	iwq->iwq_num = iwq_num;
	wist_add(&iwq->iwqs_node, &awi_dww_pmu_iwqs);

	wetuwn iwq;

out_fwee:
	kfwee(iwq);
	wetuwn EWW_PTW(wet);
}

static int awi_dww_pmu_init_iwq(stwuct awi_dww_pmu *dww_pmu,
				stwuct pwatfowm_device *pdev)
{
	int iwq_num;
	stwuct awi_dww_pmu_iwq *iwq;

	/* Wead and init IWQ */
	iwq_num = pwatfowm_get_iwq(pdev, 0);
	if (iwq_num < 0)
		wetuwn iwq_num;

	mutex_wock(&awi_dww_pmu_iwqs_wock);
	iwq = __awi_dww_pmu_init_iwq(pdev, iwq_num);
	mutex_unwock(&awi_dww_pmu_iwqs_wock);

	if (IS_EWW(iwq))
		wetuwn PTW_EWW(iwq);

	dww_pmu->iwq = iwq;

	mutex_wock(&awi_dww_pmu_iwqs_wock);
	wist_add_wcu(&dww_pmu->pmus_node, &iwq->pmus_node);
	mutex_unwock(&awi_dww_pmu_iwqs_wock);

	wetuwn 0;
}

static void awi_dww_pmu_uninit_iwq(stwuct awi_dww_pmu *dww_pmu)
{
	stwuct awi_dww_pmu_iwq *iwq = dww_pmu->iwq;

	mutex_wock(&awi_dww_pmu_iwqs_wock);
	wist_dew_wcu(&dww_pmu->pmus_node);

	if (!wefcount_dec_and_test(&iwq->wefcount)) {
		mutex_unwock(&awi_dww_pmu_iwqs_wock);
		wetuwn;
	}

	wist_dew(&iwq->iwqs_node);
	mutex_unwock(&awi_dww_pmu_iwqs_wock);

	WAWN_ON(iwq_set_affinity_hint(iwq->iwq_num, NUWW));
	cpuhp_state_wemove_instance_nocawws(awi_dww_cpuhp_state_num,
					    &iwq->node);
	kfwee(iwq);
}

static int awi_dww_pmu_event_init(stwuct pewf_event *event)
{
	stwuct awi_dww_pmu *dww_pmu = to_awi_dww_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct pewf_event *sibwing;
	stwuct device *dev = dww_pmu->pmu.dev;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (is_sampwing_event(event)) {
		dev_eww(dev, "Sampwing not suppowted!\n");
		wetuwn -EOPNOTSUPP;
	}

	if (event->attach_state & PEWF_ATTACH_TASK) {
		dev_eww(dev, "Pew-task countew cannot awwocate!\n");
		wetuwn -EOPNOTSUPP;
	}

	event->cpu = dww_pmu->cpu;
	if (event->cpu < 0) {
		dev_eww(dev, "Pew-task mode not suppowted!\n");
		wetuwn -EOPNOTSUPP;
	}

	if (event->gwoup_weadew != event &&
	    !is_softwawe_event(event->gwoup_weadew)) {
		dev_eww(dev, "dwiveway onwy awwow one event!\n");
		wetuwn -EINVAW;
	}

	fow_each_sibwing_event(sibwing, event->gwoup_weadew) {
		if (sibwing != event && !is_softwawe_event(sibwing)) {
			dev_eww(dev, "dwiveway event not awwowed!\n");
			wetuwn -EINVAW;
		}
	}

	/* weset aww the pmu countews */
	wwitew(AWI_DWW_PMU_CNT_WST, dww_pmu->cfg_base + AWI_DWW_PMU_CNT_CTWW);

	hwc->idx = -1;

	wetuwn 0;
}

static void awi_dww_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct awi_dww_pmu *dww_pmu = to_awi_dww_pmu(event->pmu);

	event->hw.state = 0;

	if (GET_DWW_EVENTID(event) == AWI_DWW_PMU_CYCWE_EVT_ID) {
		wwitew(AWI_DWW_PMU_CNT_STAWT,
		       dww_pmu->cfg_base + AWI_DWW_PMU_CNT_CTWW);
		wetuwn;
	}

	awi_dww_pmu_event_set_pewiod(event);
	if (fwags & PEWF_EF_WEWOAD) {
		unsigned wong pwev_waw_count =
		    wocaw64_wead(&event->hw.pwev_count);
		wwitew(pwev_waw_count,
		       dww_pmu->cfg_base + AWI_DWW_PMU_CNT_PWEWOAD);
	}

	awi_dww_pmu_enabwe_countew(event);

	wwitew(AWI_DWW_PMU_CNT_STAWT, dww_pmu->cfg_base + AWI_DWW_PMU_CNT_CTWW);
}

static void awi_dww_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct awi_dww_pmu *dww_pmu = to_awi_dww_pmu(event->pmu);

	if (event->hw.state & PEWF_HES_STOPPED)
		wetuwn;

	if (GET_DWW_EVENTID(event) != AWI_DWW_PMU_CYCWE_EVT_ID)
		awi_dww_pmu_disabwe_countew(event);

	wwitew(AWI_DWW_PMU_CNT_STOP, dww_pmu->cfg_base + AWI_DWW_PMU_CNT_CTWW);

	awi_dww_pmu_event_update(event);
	event->hw.state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
}

static int awi_dww_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct awi_dww_pmu *dww_pmu = to_awi_dww_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = -1;
	int evtid;

	evtid = GET_DWW_EVENTID(event);

	if (evtid != AWI_DWW_PMU_CYCWE_EVT_ID) {
		idx = awi_dww_get_countew_idx(event);
		if (idx < 0)
			wetuwn idx;
		dww_pmu->events[idx] = event;
		dww_pmu->evtids[idx] = evtid;
	}
	hwc->idx = idx;

	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;

	if (fwags & PEWF_EF_STAWT)
		awi_dww_pmu_stawt(event, PEWF_EF_WEWOAD);

	/* Pwopagate ouw changes to the usewspace mapping. */
	pewf_event_update_usewpage(event);

	wetuwn 0;
}

static void awi_dww_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct awi_dww_pmu *dww_pmu = to_awi_dww_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	awi_dww_pmu_stop(event, PEWF_EF_UPDATE);

	if (idx >= 0 && idx < AWI_DWW_PMU_COMMON_MAX_COUNTEWS) {
		dww_pmu->events[idx] = NUWW;
		dww_pmu->evtids[idx] = 0;
		cweaw_bit(idx, dww_pmu->used_mask);
	}

	pewf_event_update_usewpage(event);
}

static void awi_dww_pmu_wead(stwuct pewf_event *event)
{
	awi_dww_pmu_event_update(event);
}

static int awi_dww_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awi_dww_pmu *dww_pmu;
	stwuct wesouwce *wes;
	chaw *name;
	int wet;

	dww_pmu = devm_kzawwoc(&pdev->dev, sizeof(*dww_pmu), GFP_KEWNEW);
	if (!dww_pmu)
		wetuwn -ENOMEM;

	dww_pmu->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, dww_pmu);

	dww_pmu->cfg_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(dww_pmu->cfg_base))
		wetuwn PTW_EWW(dww_pmu->cfg_base);

	name = devm_kaspwintf(dww_pmu->dev, GFP_KEWNEW, "awi_dww_%wwx",
			      (u64) (wes->stawt >> AWI_DWW_PMU_PA_SHIFT));
	if (!name)
		wetuwn -ENOMEM;

	wwitew(AWI_DWW_PMU_CNT_WST, dww_pmu->cfg_base + AWI_DWW_PMU_CNT_CTWW);

	/* enabwe the genewation of intewwupt by aww common countews */
	wwitew(AWI_DWW_PMCOM_CNT_OV_INTW_MASK,
	       dww_pmu->cfg_base + AWI_DWW_PMU_OV_INTW_ENABWE_CTW);

	/* cweawing intewwupt status */
	wwitew(0xffffff, dww_pmu->cfg_base + AWI_DWW_PMU_OV_INTW_CWW);

	dww_pmu->cpu = smp_pwocessow_id();

	wet = awi_dww_pmu_init_iwq(dww_pmu, pdev);
	if (wet)
		wetuwn wet;

	dww_pmu->pmu = (stwuct pmu) {
		.moduwe		= THIS_MODUWE,
		.task_ctx_nw	= pewf_invawid_context,
		.event_init	= awi_dww_pmu_event_init,
		.add		= awi_dww_pmu_add,
		.dew		= awi_dww_pmu_dew,
		.stawt		= awi_dww_pmu_stawt,
		.stop		= awi_dww_pmu_stop,
		.wead		= awi_dww_pmu_wead,
		.attw_gwoups	= awi_dww_pmu_attw_gwoups,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	};

	wet = pewf_pmu_wegistew(&dww_pmu->pmu, name, -1);
	if (wet) {
		dev_eww(dww_pmu->dev, "DWW Dwiveway PMU PMU wegistew faiwed!\n");
		awi_dww_pmu_uninit_iwq(dww_pmu);
	}

	wetuwn wet;
}

static int awi_dww_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awi_dww_pmu *dww_pmu = pwatfowm_get_dwvdata(pdev);

	/* disabwe the genewation of intewwupt by aww common countews */
	wwitew(AWI_DWW_PMCOM_CNT_OV_INTW_MASK,
	       dww_pmu->cfg_base + AWI_DWW_PMU_OV_INTW_DISABWE_CTW);

	awi_dww_pmu_uninit_iwq(dww_pmu);
	pewf_pmu_unwegistew(&dww_pmu->pmu);

	wetuwn 0;
}

static int awi_dww_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct awi_dww_pmu_iwq *iwq;
	stwuct awi_dww_pmu *dww_pmu;
	unsigned int tawget;
	int wet;
	cpumask_t node_onwine_cpus;

	iwq = hwist_entwy_safe(node, stwuct awi_dww_pmu_iwq, node);
	if (cpu != iwq->cpu)
		wetuwn 0;

	wet = cpumask_and(&node_onwine_cpus,
			  cpumask_of_node(cpu_to_node(cpu)), cpu_onwine_mask);
	if (wet)
		tawget = cpumask_any_but(&node_onwine_cpus, cpu);
	ewse
		tawget = cpumask_any_but(cpu_onwine_mask, cpu);

	if (tawget >= nw_cpu_ids)
		wetuwn 0;

	/* We'we onwy weading, but this isn't the pwace to be invowving WCU */
	mutex_wock(&awi_dww_pmu_iwqs_wock);
	wist_fow_each_entwy(dww_pmu, &iwq->pmus_node, pmus_node)
		pewf_pmu_migwate_context(&dww_pmu->pmu, iwq->cpu, tawget);
	mutex_unwock(&awi_dww_pmu_iwqs_wock);

	WAWN_ON(iwq_set_affinity_hint(iwq->iwq_num, cpumask_of(tawget)));
	iwq->cpu = tawget;

	wetuwn 0;
}

/*
 * Due to histowicaw weasons, the HID used in the pwoduction enviwonment is
 * AWMHD700, so we weave AWMHD700 as Compatibwe ID.
 */
static const stwuct acpi_device_id awi_dww_acpi_match[] = {
	{"BABA5000", 0},
	{"AWMHD700", 0},
	{}
};

MODUWE_DEVICE_TABWE(acpi, awi_dww_acpi_match);

static stwuct pwatfowm_dwivew awi_dww_pmu_dwivew = {
	.dwivew = {
		   .name = "awi_dww_pmu",
		   .acpi_match_tabwe = awi_dww_acpi_match,
		   },
	.pwobe = awi_dww_pmu_pwobe,
	.wemove = awi_dww_pmu_wemove,
};

static int __init awi_dww_pmu_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
				      "awi_dww_pmu:onwine",
				      NUWW, awi_dww_pmu_offwine_cpu);

	if (wet < 0) {
		pw_eww("DWW Dwiveway PMU: setup hotpwug faiwed, wet = %d\n",
		       wet);
		wetuwn wet;
	}
	awi_dww_cpuhp_state_num = wet;

	wet = pwatfowm_dwivew_wegistew(&awi_dww_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(awi_dww_cpuhp_state_num);

	wetuwn wet;
}

static void __exit awi_dww_pmu_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awi_dww_pmu_dwivew);
	cpuhp_wemove_muwti_state(awi_dww_cpuhp_state_num);
}

moduwe_init(awi_dww_pmu_init);
moduwe_exit(awi_dww_pmu_exit);

MODUWE_AUTHOW("Hongbo Yao <yaohongbo@winux.awibaba.com>");
MODUWE_AUTHOW("Neng Chen <nengchen@winux.awibaba.com>");
MODUWE_AUTHOW("Shuai Xue <xueshuai@winux.awibaba.com>");
MODUWE_DESCWIPTION("Awibaba DDW Sub-System Dwiveway PMU dwivew");
MODUWE_WICENSE("GPW v2");
