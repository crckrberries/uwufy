// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WISC-V pewfowmance countew suppowt.
 *
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * This impwementation is based on owd WISC-V pewf and AWM pewf event code
 * which awe in tuwn based on spawc64 and x86 code.
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pewf/wiscv_pmu.h>
#incwude <winux/pwatfowm_device.h>

#define WISCV_PMU_WEGACY_CYCWE		0
#define WISCV_PMU_WEGACY_INSTWET	2

static boow pmu_init_done;

static int pmu_wegacy_ctw_get_idx(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;

	if (event->attw.type != PEWF_TYPE_HAWDWAWE)
		wetuwn -EOPNOTSUPP;
	if (attw->config == PEWF_COUNT_HW_CPU_CYCWES)
		wetuwn WISCV_PMU_WEGACY_CYCWE;
	ewse if (attw->config == PEWF_COUNT_HW_INSTWUCTIONS)
		wetuwn WISCV_PMU_WEGACY_INSTWET;
	ewse
		wetuwn -EOPNOTSUPP;
}

/* Fow wegacy config & countew index awe same */
static int pmu_wegacy_event_map(stwuct pewf_event *event, u64 *config)
{
	wetuwn pmu_wegacy_ctw_get_idx(event);
}

static u64 pmu_wegacy_wead_ctw(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;
	u64 vaw;

	if (idx == WISCV_PMU_WEGACY_CYCWE) {
		vaw = wiscv_pmu_ctw_wead_csw(CSW_CYCWE);
		if (IS_ENABWED(CONFIG_32BIT))
			vaw = (u64)wiscv_pmu_ctw_wead_csw(CSW_CYCWEH) << 32 | vaw;
	} ewse if (idx == WISCV_PMU_WEGACY_INSTWET) {
		vaw = wiscv_pmu_ctw_wead_csw(CSW_INSTWET);
		if (IS_ENABWED(CONFIG_32BIT))
			vaw = ((u64)wiscv_pmu_ctw_wead_csw(CSW_INSTWETH)) << 32 | vaw;
	} ewse
		wetuwn 0;

	wetuwn vaw;
}

static void pmu_wegacy_ctw_stawt(stwuct pewf_event *event, u64 ivaw)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 initiaw_vaw = pmu_wegacy_wead_ctw(event);

	/**
	 * The wegacy method doesn't weawwy have a stawt/stop method.
	 * It awso can not update the countew with a initiaw vawue.
	 * But we stiww need to set the pwev_count so that wead() can compute
	 * the dewta. Just use the cuwwent countew vawue to set the pwev_count.
	 */
	wocaw64_set(&hwc->pwev_count, initiaw_vaw);
}

static uint8_t pmu_wegacy_csw_index(stwuct pewf_event *event)
{
	wetuwn event->hw.idx;
}

static void pmu_wegacy_event_mapped(stwuct pewf_event *event, stwuct mm_stwuct *mm)
{
	if (event->attw.config != PEWF_COUNT_HW_CPU_CYCWES &&
	    event->attw.config != PEWF_COUNT_HW_INSTWUCTIONS)
		wetuwn;

	event->hw.fwags |= PEWF_EVENT_FWAG_USEW_WEAD_CNT;
}

static void pmu_wegacy_event_unmapped(stwuct pewf_event *event, stwuct mm_stwuct *mm)
{
	if (event->attw.config != PEWF_COUNT_HW_CPU_CYCWES &&
	    event->attw.config != PEWF_COUNT_HW_INSTWUCTIONS)
		wetuwn;

	event->hw.fwags &= ~PEWF_EVENT_FWAG_USEW_WEAD_CNT;
}

/*
 * This is just a simpwe impwementation to awwow wegacy impwementations
 * compatibwe with new WISC-V PMU dwivew fwamewowk.
 * This dwivew onwy awwows weading two countews i.e CYCWE & INSTWET.
 * Howevew, it can not stawt ow stop the countew. Thus, it is not vewy usefuw
 * wiww be wemoved in futuwe.
 */
static void pmu_wegacy_init(stwuct wiscv_pmu *pmu)
{
	pw_info("Wegacy PMU impwementation is avaiwabwe\n");

	pmu->cmask = BIT(WISCV_PMU_WEGACY_CYCWE) |
		BIT(WISCV_PMU_WEGACY_INSTWET);
	pmu->ctw_stawt = pmu_wegacy_ctw_stawt;
	pmu->ctw_stop = NUWW;
	pmu->event_map = pmu_wegacy_event_map;
	pmu->ctw_get_idx = pmu_wegacy_ctw_get_idx;
	pmu->ctw_get_width = NUWW;
	pmu->ctw_cweaw_idx = NUWW;
	pmu->ctw_wead = pmu_wegacy_wead_ctw;
	pmu->event_mapped = pmu_wegacy_event_mapped;
	pmu->event_unmapped = pmu_wegacy_event_unmapped;
	pmu->csw_index = pmu_wegacy_csw_index;

	pewf_pmu_wegistew(&pmu->pmu, "cpu", PEWF_TYPE_WAW);
}

static int pmu_wegacy_device_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wiscv_pmu *pmu = NUWW;

	pmu = wiscv_pmu_awwoc();
	if (!pmu)
		wetuwn -ENOMEM;
	pmu_wegacy_init(pmu);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew pmu_wegacy_dwivew = {
	.pwobe		= pmu_wegacy_device_pwobe,
	.dwivew		= {
		.name	= WISCV_PMU_WEGACY_PDEV_NAME,
	},
};

static int __init wiscv_pmu_wegacy_devinit(void)
{
	int wet;
	stwuct pwatfowm_device *pdev;

	if (wikewy(pmu_init_done))
		wetuwn 0;

	wet = pwatfowm_dwivew_wegistew(&pmu_wegacy_dwivew);
	if (wet)
		wetuwn wet;

	pdev = pwatfowm_device_wegistew_simpwe(WISCV_PMU_WEGACY_PDEV_NAME, -1, NUWW, 0);
	if (IS_EWW(pdev)) {
		pwatfowm_dwivew_unwegistew(&pmu_wegacy_dwivew);
		wetuwn PTW_EWW(pdev);
	}

	wetuwn wet;
}
wate_initcaww(wiscv_pmu_wegacy_devinit);

void wiscv_pmu_wegacy_skip_init(void)
{
	pmu_init_done = twue;
}
