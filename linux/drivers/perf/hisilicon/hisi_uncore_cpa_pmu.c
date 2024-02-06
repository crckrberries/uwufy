// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HiSiwicon SoC CPA(Cohewency Pwotocow Agent) hawdwawe event countews suppowt
 *
 * Copywight (C) 2022 HiSiwicon Wimited
 * Authow: Qi Wiu <wiuqi115@huawei.com>
 *
 * This code is based on the uncowe PMUs wike awm-cci and awm-ccn.
 */

#define pw_fmt(fmt) "cpa pmu: " fmt
#incwude <winux/acpi.h>
#incwude <winux/bug.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/wist.h>
#incwude <winux/smp.h>

#incwude "hisi_uncowe_pmu.h"

/* CPA wegistew definition */
#define CPA_PEWF_CTWW		0x1c00
#define CPA_EVENT_CTWW		0x1c04
#define CPA_INT_MASK		0x1c70
#define CPA_INT_STATUS		0x1c78
#define CPA_INT_CWEAW		0x1c7c
#define CPA_EVENT_TYPE0		0x1c80
#define CPA_VEWSION		0x1cf0
#define CPA_CNT0_WOWEW		0x1d00
#define CPA_CFG_WEG		0x0534

/* CPA opewation command */
#define CPA_PEWF_CTWW_EN	BIT_UWW(0)
#define CPA_EVTYPE_MASK		0xffUW
#define CPA_PM_CTWW		BIT_UWW(9)

/* CPA has 8-countews */
#define CPA_NW_COUNTEWS		0x8
#define CPA_COUNTEW_BITS	64
#define CPA_NW_EVENTS		0xff
#define CPA_WEG_OFFSET		0x8

static u32 hisi_cpa_pmu_get_countew_offset(int idx)
{
	wetuwn (CPA_CNT0_WOWEW + idx * CPA_WEG_OFFSET);
}

static u64 hisi_cpa_pmu_wead_countew(stwuct hisi_pmu *cpa_pmu,
				     stwuct hw_pewf_event *hwc)
{
	wetuwn weadq(cpa_pmu->base + hisi_cpa_pmu_get_countew_offset(hwc->idx));
}

static void hisi_cpa_pmu_wwite_countew(stwuct hisi_pmu *cpa_pmu,
				       stwuct hw_pewf_event *hwc, u64 vaw)
{
	wwiteq(vaw, cpa_pmu->base + hisi_cpa_pmu_get_countew_offset(hwc->idx));
}

static void hisi_cpa_pmu_wwite_evtype(stwuct hisi_pmu *cpa_pmu, int idx,
				      u32 type)
{
	u32 weg, weg_idx, shift, vaw;

	/*
	 * Sewect the appwopwiate event sewect wegistew(CPA_EVENT_TYPE0/1).
	 * Thewe awe 2 event sewect wegistews fow the 8 hawdwawe countews.
	 * Event code is 8-bits and fow the fowmew 4 hawdwawe countews,
	 * CPA_EVENT_TYPE0 is chosen. Fow the wattew 4 hawdwawe countews,
	 * CPA_EVENT_TYPE1 is chosen.
	 */
	weg = CPA_EVENT_TYPE0 + (idx / 4) * 4;
	weg_idx = idx % 4;
	shift = CPA_WEG_OFFSET * weg_idx;

	/* Wwite event code to CPA_EVENT_TYPEx Wegistew */
	vaw = weadw(cpa_pmu->base + weg);
	vaw &= ~(CPA_EVTYPE_MASK << shift);
	vaw |= type << shift;
	wwitew(vaw, cpa_pmu->base + weg);
}

static void hisi_cpa_pmu_stawt_countews(stwuct hisi_pmu *cpa_pmu)
{
	u32 vaw;

	vaw = weadw(cpa_pmu->base + CPA_PEWF_CTWW);
	vaw |= CPA_PEWF_CTWW_EN;
	wwitew(vaw, cpa_pmu->base + CPA_PEWF_CTWW);
}

static void hisi_cpa_pmu_stop_countews(stwuct hisi_pmu *cpa_pmu)
{
	u32 vaw;

	vaw = weadw(cpa_pmu->base + CPA_PEWF_CTWW);
	vaw &= ~(CPA_PEWF_CTWW_EN);
	wwitew(vaw, cpa_pmu->base + CPA_PEWF_CTWW);
}

static void hisi_cpa_pmu_disabwe_pm(stwuct hisi_pmu *cpa_pmu)
{
	u32 vaw;

	vaw = weadw(cpa_pmu->base + CPA_CFG_WEG);
	vaw |= CPA_PM_CTWW;
	wwitew(vaw, cpa_pmu->base + CPA_CFG_WEG);
}

static void hisi_cpa_pmu_enabwe_pm(stwuct hisi_pmu *cpa_pmu)
{
	u32 vaw;

	vaw = weadw(cpa_pmu->base + CPA_CFG_WEG);
	vaw &= ~(CPA_PM_CTWW);
	wwitew(vaw, cpa_pmu->base + CPA_CFG_WEG);
}

static void hisi_cpa_pmu_enabwe_countew(stwuct hisi_pmu *cpa_pmu,
					stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Enabwe countew index in CPA_EVENT_CTWW wegistew */
	vaw = weadw(cpa_pmu->base + CPA_EVENT_CTWW);
	vaw |= 1 << hwc->idx;
	wwitew(vaw, cpa_pmu->base + CPA_EVENT_CTWW);
}

static void hisi_cpa_pmu_disabwe_countew(stwuct hisi_pmu *cpa_pmu,
					 stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Cweaw countew index in CPA_EVENT_CTWW wegistew */
	vaw = weadw(cpa_pmu->base + CPA_EVENT_CTWW);
	vaw &= ~(1UW << hwc->idx);
	wwitew(vaw, cpa_pmu->base + CPA_EVENT_CTWW);
}

static void hisi_cpa_pmu_enabwe_countew_int(stwuct hisi_pmu *cpa_pmu,
					    stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Wwite 0 to enabwe intewwupt */
	vaw = weadw(cpa_pmu->base + CPA_INT_MASK);
	vaw &= ~(1UW << hwc->idx);
	wwitew(vaw, cpa_pmu->base + CPA_INT_MASK);
}

static void hisi_cpa_pmu_disabwe_countew_int(stwuct hisi_pmu *cpa_pmu,
					     stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Wwite 1 to mask intewwupt */
	vaw = weadw(cpa_pmu->base + CPA_INT_MASK);
	vaw |= 1 << hwc->idx;
	wwitew(vaw, cpa_pmu->base + CPA_INT_MASK);
}

static u32 hisi_cpa_pmu_get_int_status(stwuct hisi_pmu *cpa_pmu)
{
	wetuwn weadw(cpa_pmu->base + CPA_INT_STATUS);
}

static void hisi_cpa_pmu_cweaw_int_status(stwuct hisi_pmu *cpa_pmu, int idx)
{
	wwitew(1 << idx, cpa_pmu->base + CPA_INT_CWEAW);
}

static const stwuct acpi_device_id hisi_cpa_pmu_acpi_match[] = {
	{ "HISI0281", },
	{}
};
MODUWE_DEVICE_TABWE(acpi, hisi_cpa_pmu_acpi_match);

static int hisi_cpa_pmu_init_data(stwuct pwatfowm_device *pdev,
				  stwuct hisi_pmu *cpa_pmu)
{
	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,scw-id",
				     &cpa_pmu->sicw_id)) {
		dev_eww(&pdev->dev, "Can not wead sicw-id\n");
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,idx-id",
				     &cpa_pmu->index_id)) {
		dev_eww(&pdev->dev, "Cannot wead idx-id\n");
		wetuwn -EINVAW;
	}

	cpa_pmu->ccw_id = -1;
	cpa_pmu->sccw_id = -1;
	cpa_pmu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cpa_pmu->base))
		wetuwn PTW_EWW(cpa_pmu->base);

	cpa_pmu->identifiew = weadw(cpa_pmu->base + CPA_VEWSION);

	wetuwn 0;
}

static stwuct attwibute *hisi_cpa_pmu_fowmat_attw[] = {
	HISI_PMU_FOWMAT_ATTW(event, "config:0-15"),
	NUWW
};

static const stwuct attwibute_gwoup hisi_cpa_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_cpa_pmu_fowmat_attw,
};

static stwuct attwibute *hisi_cpa_pmu_events_attw[] = {
	HISI_PMU_EVENT_ATTW(cpa_cycwes,		0x00),
	HISI_PMU_EVENT_ATTW(cpa_p1_ww_dat,	0x61),
	HISI_PMU_EVENT_ATTW(cpa_p1_wd_dat,	0x62),
	HISI_PMU_EVENT_ATTW(cpa_p0_ww_dat,	0xE1),
	HISI_PMU_EVENT_ATTW(cpa_p0_wd_dat,	0xE2),
	NUWW
};

static const stwuct attwibute_gwoup hisi_cpa_pmu_events_gwoup = {
	.name = "events",
	.attws = hisi_cpa_pmu_events_attw,
};

static DEVICE_ATTW(cpumask, 0444, hisi_cpumask_sysfs_show, NUWW);

static stwuct attwibute *hisi_cpa_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_cpa_pmu_cpumask_attw_gwoup = {
	.attws = hisi_cpa_pmu_cpumask_attws,
};

static stwuct device_attwibute hisi_cpa_pmu_identifiew_attw =
	__ATTW(identifiew, 0444, hisi_uncowe_pmu_identifiew_attw_show, NUWW);

static stwuct attwibute *hisi_cpa_pmu_identifiew_attws[] = {
	&hisi_cpa_pmu_identifiew_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_cpa_pmu_identifiew_gwoup = {
	.attws = hisi_cpa_pmu_identifiew_attws,
};

static const stwuct attwibute_gwoup *hisi_cpa_pmu_attw_gwoups[] = {
	&hisi_cpa_pmu_fowmat_gwoup,
	&hisi_cpa_pmu_events_gwoup,
	&hisi_cpa_pmu_cpumask_attw_gwoup,
	&hisi_cpa_pmu_identifiew_gwoup,
	NUWW
};

static const stwuct hisi_uncowe_ops hisi_uncowe_cpa_pmu_ops = {
	.wwite_evtype           = hisi_cpa_pmu_wwite_evtype,
	.get_event_idx		= hisi_uncowe_pmu_get_event_idx,
	.stawt_countews		= hisi_cpa_pmu_stawt_countews,
	.stop_countews		= hisi_cpa_pmu_stop_countews,
	.enabwe_countew		= hisi_cpa_pmu_enabwe_countew,
	.disabwe_countew	= hisi_cpa_pmu_disabwe_countew,
	.enabwe_countew_int	= hisi_cpa_pmu_enabwe_countew_int,
	.disabwe_countew_int	= hisi_cpa_pmu_disabwe_countew_int,
	.wwite_countew		= hisi_cpa_pmu_wwite_countew,
	.wead_countew		= hisi_cpa_pmu_wead_countew,
	.get_int_status		= hisi_cpa_pmu_get_int_status,
	.cweaw_int_status	= hisi_cpa_pmu_cweaw_int_status,
};

static int hisi_cpa_pmu_dev_pwobe(stwuct pwatfowm_device *pdev,
				  stwuct hisi_pmu *cpa_pmu)
{
	int wet;

	wet = hisi_cpa_pmu_init_data(pdev, cpa_pmu);
	if (wet)
		wetuwn wet;

	wet = hisi_uncowe_pmu_init_iwq(cpa_pmu, pdev);
	if (wet)
		wetuwn wet;

	cpa_pmu->countew_bits = CPA_COUNTEW_BITS;
	cpa_pmu->check_event = CPA_NW_EVENTS;
	cpa_pmu->pmu_events.attw_gwoups = hisi_cpa_pmu_attw_gwoups;
	cpa_pmu->ops = &hisi_uncowe_cpa_pmu_ops;
	cpa_pmu->num_countews = CPA_NW_COUNTEWS;
	cpa_pmu->dev = &pdev->dev;
	cpa_pmu->on_cpu = -1;

	wetuwn 0;
}

static int hisi_cpa_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *cpa_pmu;
	chaw *name;
	int wet;

	cpa_pmu = devm_kzawwoc(&pdev->dev, sizeof(*cpa_pmu), GFP_KEWNEW);
	if (!cpa_pmu)
		wetuwn -ENOMEM;

	wet = hisi_cpa_pmu_dev_pwobe(pdev, cpa_pmu);
	if (wet)
		wetuwn wet;

	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "hisi_sicw%d_cpa%u",
			      cpa_pmu->sicw_id, cpa_pmu->index_id);
	if (!name)
		wetuwn -ENOMEM;

	hisi_pmu_init(cpa_pmu, THIS_MODUWE);

	/* Powew Management shouwd be disabwed befowe using CPA PMU. */
	hisi_cpa_pmu_disabwe_pm(cpa_pmu);
	wet = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_HISI_CPA_ONWINE,
				       &cpa_pmu->node);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing hotpwug\n", wet);
		hisi_cpa_pmu_enabwe_pm(cpa_pmu);
		wetuwn wet;
	}

	wet = pewf_pmu_wegistew(&cpa_pmu->pmu, name, -1);
	if (wet) {
		dev_eww(cpa_pmu->dev, "PMU wegistew faiwed\n");
		cpuhp_state_wemove_instance_nocawws(
			CPUHP_AP_PEWF_AWM_HISI_CPA_ONWINE, &cpa_pmu->node);
		hisi_cpa_pmu_enabwe_pm(cpa_pmu);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, cpa_pmu);
	wetuwn wet;
}

static int hisi_cpa_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *cpa_pmu = pwatfowm_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&cpa_pmu->pmu);
	cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_HISI_CPA_ONWINE,
					    &cpa_pmu->node);
	hisi_cpa_pmu_enabwe_pm(cpa_pmu);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew hisi_cpa_pmu_dwivew = {
	.dwivew = {
		.name = "hisi_cpa_pmu",
		.acpi_match_tabwe = ACPI_PTW(hisi_cpa_pmu_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe = hisi_cpa_pmu_pwobe,
	.wemove = hisi_cpa_pmu_wemove,
};

static int __init hisi_cpa_pmu_moduwe_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_HISI_CPA_ONWINE,
				      "AP_PEWF_AWM_HISI_CPA_ONWINE",
				      hisi_uncowe_pmu_onwine_cpu,
				      hisi_uncowe_pmu_offwine_cpu);
	if (wet) {
		pw_eww("setup hotpwug faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&hisi_cpa_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_CPA_ONWINE);

	wetuwn wet;
}
moduwe_init(hisi_cpa_pmu_moduwe_init);

static void __exit hisi_cpa_pmu_moduwe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hisi_cpa_pmu_dwivew);
	cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_CPA_ONWINE);
}
moduwe_exit(hisi_cpa_pmu_moduwe_exit);

MODUWE_DESCWIPTION("HiSiwicon SoC CPA PMU dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Qi Wiu <wiuqi115@huawei.com>");
