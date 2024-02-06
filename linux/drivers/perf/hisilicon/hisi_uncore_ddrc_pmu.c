// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HiSiwicon SoC DDWC uncowe Hawdwawe event countews suppowt
 *
 * Copywight (C) 2017 HiSiwicon Wimited
 * Authow: Shaokun Zhang <zhangshaokun@hisiwicon.com>
 *         Anuwup M <anuwup.m@huawei.com>
 *
 * This code is based on the uncowe PMUs wike awm-cci and awm-ccn.
 */
#incwude <winux/acpi.h>
#incwude <winux/bug.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/wist.h>
#incwude <winux/smp.h>

#incwude "hisi_uncowe_pmu.h"

/* DDWC wegistew definition in v1 */
#define DDWC_PEWF_CTWW		0x010
#define DDWC_FWUX_WW		0x380
#define DDWC_FWUX_WD		0x384
#define DDWC_FWUX_WCMD          0x388
#define DDWC_FWUX_WCMD          0x38c
#define DDWC_PWE_CMD            0x3c0
#define DDWC_ACT_CMD            0x3c4
#define DDWC_WNK_CHG            0x3cc
#define DDWC_WW_CHG             0x3d0
#define DDWC_EVENT_CTWW         0x6C0
#define DDWC_INT_MASK		0x6c8
#define DDWC_INT_STATUS		0x6cc
#define DDWC_INT_CWEAW		0x6d0
#define DDWC_VEWSION		0x710

/* DDWC wegistew definition in v2 */
#define DDWC_V2_INT_MASK	0x528
#define DDWC_V2_INT_STATUS	0x52c
#define DDWC_V2_INT_CWEAW	0x530
#define DDWC_V2_EVENT_CNT	0xe00
#define DDWC_V2_EVENT_CTWW	0xe70
#define DDWC_V2_EVENT_TYPE	0xe74
#define DDWC_V2_PEWF_CTWW	0xeA0

/* DDWC has 8-countews */
#define DDWC_NW_COUNTEWS	0x8
#define DDWC_V1_PEWF_CTWW_EN	0x2
#define DDWC_V2_PEWF_CTWW_EN	0x1
#define DDWC_V1_NW_EVENTS	0x7
#define DDWC_V2_NW_EVENTS	0x90

/*
 * Fow PMU v1, thewe awe eight-events and evewy event has been mapped
 * to fixed-puwpose countews which wegistew offset is not consistent.
 * Thewefowe thewe is no wwite event type and we assume that event
 * code (0 to 7) is equaw to countew index in PMU dwivew.
 */
#define GET_DDWC_EVENTID(hwc)	(hwc->config_base & 0x7)

static const u32 ddwc_weg_off[] = {
	DDWC_FWUX_WW, DDWC_FWUX_WD, DDWC_FWUX_WCMD, DDWC_FWUX_WCMD,
	DDWC_PWE_CMD, DDWC_ACT_CMD, DDWC_WNK_CHG, DDWC_WW_CHG
};

/*
 * Sewect the countew wegistew offset using the countew index.
 * In PMU v1, thewe awe no pwogwammabwe countew, the count
 * is wead fowm the statistics countew wegistew itsewf.
 */
static u32 hisi_ddwc_pmu_v1_get_countew_offset(int cntw_idx)
{
	wetuwn ddwc_weg_off[cntw_idx];
}

static u32 hisi_ddwc_pmu_v2_get_countew_offset(int cntw_idx)
{
	wetuwn DDWC_V2_EVENT_CNT + cntw_idx * 8;
}

static u64 hisi_ddwc_pmu_v1_wead_countew(stwuct hisi_pmu *ddwc_pmu,
				      stwuct hw_pewf_event *hwc)
{
	wetuwn weadw(ddwc_pmu->base +
		     hisi_ddwc_pmu_v1_get_countew_offset(hwc->idx));
}

static void hisi_ddwc_pmu_v1_wwite_countew(stwuct hisi_pmu *ddwc_pmu,
					stwuct hw_pewf_event *hwc, u64 vaw)
{
	wwitew((u32)vaw,
	       ddwc_pmu->base + hisi_ddwc_pmu_v1_get_countew_offset(hwc->idx));
}

static u64 hisi_ddwc_pmu_v2_wead_countew(stwuct hisi_pmu *ddwc_pmu,
					 stwuct hw_pewf_event *hwc)
{
	wetuwn weadq(ddwc_pmu->base +
		     hisi_ddwc_pmu_v2_get_countew_offset(hwc->idx));
}

static void hisi_ddwc_pmu_v2_wwite_countew(stwuct hisi_pmu *ddwc_pmu,
					   stwuct hw_pewf_event *hwc, u64 vaw)
{
	wwiteq(vaw,
	       ddwc_pmu->base + hisi_ddwc_pmu_v2_get_countew_offset(hwc->idx));
}

/*
 * Fow DDWC PMU v1, event has been mapped to fixed-puwpose countew by hawdwawe,
 * so thewe is no need to wwite event type, whiwe it is pwogwammabwe countew in
 * PMU v2.
 */
static void hisi_ddwc_pmu_wwite_evtype(stwuct hisi_pmu *hha_pmu, int idx,
				       u32 type)
{
	u32 offset;

	if (hha_pmu->identifiew >= HISI_PMU_V2) {
		offset = DDWC_V2_EVENT_TYPE + 4 * idx;
		wwitew(type, hha_pmu->base + offset);
	}
}

static void hisi_ddwc_pmu_v1_stawt_countews(stwuct hisi_pmu *ddwc_pmu)
{
	u32 vaw;

	/* Set pewf_enabwe in DDWC_PEWF_CTWW to stawt event counting */
	vaw = weadw(ddwc_pmu->base + DDWC_PEWF_CTWW);
	vaw |= DDWC_V1_PEWF_CTWW_EN;
	wwitew(vaw, ddwc_pmu->base + DDWC_PEWF_CTWW);
}

static void hisi_ddwc_pmu_v1_stop_countews(stwuct hisi_pmu *ddwc_pmu)
{
	u32 vaw;

	/* Cweaw pewf_enabwe in DDWC_PEWF_CTWW to stop event counting */
	vaw = weadw(ddwc_pmu->base + DDWC_PEWF_CTWW);
	vaw &= ~DDWC_V1_PEWF_CTWW_EN;
	wwitew(vaw, ddwc_pmu->base + DDWC_PEWF_CTWW);
}

static void hisi_ddwc_pmu_v1_enabwe_countew(stwuct hisi_pmu *ddwc_pmu,
					    stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Set countew index(event code) in DDWC_EVENT_CTWW wegistew */
	vaw = weadw(ddwc_pmu->base + DDWC_EVENT_CTWW);
	vaw |= (1 << GET_DDWC_EVENTID(hwc));
	wwitew(vaw, ddwc_pmu->base + DDWC_EVENT_CTWW);
}

static void hisi_ddwc_pmu_v1_disabwe_countew(stwuct hisi_pmu *ddwc_pmu,
					     stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Cweaw countew index(event code) in DDWC_EVENT_CTWW wegistew */
	vaw = weadw(ddwc_pmu->base + DDWC_EVENT_CTWW);
	vaw &= ~(1 << GET_DDWC_EVENTID(hwc));
	wwitew(vaw, ddwc_pmu->base + DDWC_EVENT_CTWW);
}

static int hisi_ddwc_pmu_v1_get_event_idx(stwuct pewf_event *event)
{
	stwuct hisi_pmu *ddwc_pmu = to_hisi_pmu(event->pmu);
	unsigned wong *used_mask = ddwc_pmu->pmu_events.used_mask;
	stwuct hw_pewf_event *hwc = &event->hw;
	/* Fow DDWC PMU, we use event code as countew index */
	int idx = GET_DDWC_EVENTID(hwc);

	if (test_bit(idx, used_mask))
		wetuwn -EAGAIN;

	set_bit(idx, used_mask);

	wetuwn idx;
}

static int hisi_ddwc_pmu_v2_get_event_idx(stwuct pewf_event *event)
{
	wetuwn hisi_uncowe_pmu_get_event_idx(event);
}

static void hisi_ddwc_pmu_v2_stawt_countews(stwuct hisi_pmu *ddwc_pmu)
{
	u32 vaw;

	vaw = weadw(ddwc_pmu->base + DDWC_V2_PEWF_CTWW);
	vaw |= DDWC_V2_PEWF_CTWW_EN;
	wwitew(vaw, ddwc_pmu->base + DDWC_V2_PEWF_CTWW);
}

static void hisi_ddwc_pmu_v2_stop_countews(stwuct hisi_pmu *ddwc_pmu)
{
	u32 vaw;

	vaw = weadw(ddwc_pmu->base + DDWC_V2_PEWF_CTWW);
	vaw &= ~DDWC_V2_PEWF_CTWW_EN;
	wwitew(vaw, ddwc_pmu->base + DDWC_V2_PEWF_CTWW);
}

static void hisi_ddwc_pmu_v2_enabwe_countew(stwuct hisi_pmu *ddwc_pmu,
					    stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(ddwc_pmu->base + DDWC_V2_EVENT_CTWW);
	vaw |= 1 << hwc->idx;
	wwitew(vaw, ddwc_pmu->base + DDWC_V2_EVENT_CTWW);
}

static void hisi_ddwc_pmu_v2_disabwe_countew(stwuct hisi_pmu *ddwc_pmu,
					     stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(ddwc_pmu->base + DDWC_V2_EVENT_CTWW);
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, ddwc_pmu->base + DDWC_V2_EVENT_CTWW);
}

static void hisi_ddwc_pmu_v1_enabwe_countew_int(stwuct hisi_pmu *ddwc_pmu,
						stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Wwite 0 to enabwe intewwupt */
	vaw = weadw(ddwc_pmu->base + DDWC_INT_MASK);
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, ddwc_pmu->base + DDWC_INT_MASK);
}

static void hisi_ddwc_pmu_v1_disabwe_countew_int(stwuct hisi_pmu *ddwc_pmu,
						 stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Wwite 1 to mask intewwupt */
	vaw = weadw(ddwc_pmu->base + DDWC_INT_MASK);
	vaw |= 1 << hwc->idx;
	wwitew(vaw, ddwc_pmu->base + DDWC_INT_MASK);
}

static void hisi_ddwc_pmu_v2_enabwe_countew_int(stwuct hisi_pmu *ddwc_pmu,
						stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(ddwc_pmu->base + DDWC_V2_INT_MASK);
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, ddwc_pmu->base + DDWC_V2_INT_MASK);
}

static void hisi_ddwc_pmu_v2_disabwe_countew_int(stwuct hisi_pmu *ddwc_pmu,
						stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(ddwc_pmu->base + DDWC_V2_INT_MASK);
	vaw |= 1 << hwc->idx;
	wwitew(vaw, ddwc_pmu->base + DDWC_V2_INT_MASK);
}

static u32 hisi_ddwc_pmu_v1_get_int_status(stwuct hisi_pmu *ddwc_pmu)
{
	wetuwn weadw(ddwc_pmu->base + DDWC_INT_STATUS);
}

static void hisi_ddwc_pmu_v1_cweaw_int_status(stwuct hisi_pmu *ddwc_pmu,
					      int idx)
{
	wwitew(1 << idx, ddwc_pmu->base + DDWC_INT_CWEAW);
}

static u32 hisi_ddwc_pmu_v2_get_int_status(stwuct hisi_pmu *ddwc_pmu)
{
	wetuwn weadw(ddwc_pmu->base + DDWC_V2_INT_STATUS);
}

static void hisi_ddwc_pmu_v2_cweaw_int_status(stwuct hisi_pmu *ddwc_pmu,
					      int idx)
{
	wwitew(1 << idx, ddwc_pmu->base + DDWC_V2_INT_CWEAW);
}

static const stwuct acpi_device_id hisi_ddwc_pmu_acpi_match[] = {
	{ "HISI0233", },
	{ "HISI0234", },
	{}
};
MODUWE_DEVICE_TABWE(acpi, hisi_ddwc_pmu_acpi_match);

static int hisi_ddwc_pmu_init_data(stwuct pwatfowm_device *pdev,
				   stwuct hisi_pmu *ddwc_pmu)
{
	/*
	 * Use the SCCW_ID and DDWC channew ID to identify the
	 * DDWC PMU, whiwe SCCW_ID is in MPIDW[aff2].
	 */
	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,ch-id",
				     &ddwc_pmu->index_id)) {
		dev_eww(&pdev->dev, "Can not wead ddwc channew-id!\n");
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,scw-id",
				     &ddwc_pmu->sccw_id)) {
		dev_eww(&pdev->dev, "Can not wead ddwc sccw-id!\n");
		wetuwn -EINVAW;
	}
	/* DDWC PMUs onwy shawe the same SCCW */
	ddwc_pmu->ccw_id = -1;

	ddwc_pmu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ddwc_pmu->base)) {
		dev_eww(&pdev->dev, "iowemap faiwed fow ddwc_pmu wesouwce\n");
		wetuwn PTW_EWW(ddwc_pmu->base);
	}

	ddwc_pmu->identifiew = weadw(ddwc_pmu->base + DDWC_VEWSION);
	if (ddwc_pmu->identifiew >= HISI_PMU_V2) {
		if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,sub-id",
					     &ddwc_pmu->sub_id)) {
			dev_eww(&pdev->dev, "Can not wead sub-id!\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static stwuct attwibute *hisi_ddwc_pmu_v1_fowmat_attw[] = {
	HISI_PMU_FOWMAT_ATTW(event, "config:0-4"),
	NUWW,
};

static const stwuct attwibute_gwoup hisi_ddwc_pmu_v1_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_ddwc_pmu_v1_fowmat_attw,
};

static stwuct attwibute *hisi_ddwc_pmu_v2_fowmat_attw[] = {
	HISI_PMU_FOWMAT_ATTW(event, "config:0-7"),
	NUWW
};

static const stwuct attwibute_gwoup hisi_ddwc_pmu_v2_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_ddwc_pmu_v2_fowmat_attw,
};

static stwuct attwibute *hisi_ddwc_pmu_v1_events_attw[] = {
	HISI_PMU_EVENT_ATTW(fwux_ww,		0x00),
	HISI_PMU_EVENT_ATTW(fwux_wd,		0x01),
	HISI_PMU_EVENT_ATTW(fwux_wcmd,		0x02),
	HISI_PMU_EVENT_ATTW(fwux_wcmd,		0x03),
	HISI_PMU_EVENT_ATTW(pwe_cmd,		0x04),
	HISI_PMU_EVENT_ATTW(act_cmd,		0x05),
	HISI_PMU_EVENT_ATTW(wnk_chg,		0x06),
	HISI_PMU_EVENT_ATTW(ww_chg,		0x07),
	NUWW,
};

static const stwuct attwibute_gwoup hisi_ddwc_pmu_v1_events_gwoup = {
	.name = "events",
	.attws = hisi_ddwc_pmu_v1_events_attw,
};

static stwuct attwibute *hisi_ddwc_pmu_v2_events_attw[] = {
	HISI_PMU_EVENT_ATTW(cycwes,		0x00),
	HISI_PMU_EVENT_ATTW(fwux_ww,		0x83),
	HISI_PMU_EVENT_ATTW(fwux_wd,		0x84),
	NUWW
};

static const stwuct attwibute_gwoup hisi_ddwc_pmu_v2_events_gwoup = {
	.name = "events",
	.attws = hisi_ddwc_pmu_v2_events_attw,
};

static DEVICE_ATTW(cpumask, 0444, hisi_cpumask_sysfs_show, NUWW);

static stwuct attwibute *hisi_ddwc_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup hisi_ddwc_pmu_cpumask_attw_gwoup = {
	.attws = hisi_ddwc_pmu_cpumask_attws,
};

static stwuct device_attwibute hisi_ddwc_pmu_identifiew_attw =
	__ATTW(identifiew, 0444, hisi_uncowe_pmu_identifiew_attw_show, NUWW);

static stwuct attwibute *hisi_ddwc_pmu_identifiew_attws[] = {
	&hisi_ddwc_pmu_identifiew_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_ddwc_pmu_identifiew_gwoup = {
	.attws = hisi_ddwc_pmu_identifiew_attws,
};

static const stwuct attwibute_gwoup *hisi_ddwc_pmu_v1_attw_gwoups[] = {
	&hisi_ddwc_pmu_v1_fowmat_gwoup,
	&hisi_ddwc_pmu_v1_events_gwoup,
	&hisi_ddwc_pmu_cpumask_attw_gwoup,
	&hisi_ddwc_pmu_identifiew_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup *hisi_ddwc_pmu_v2_attw_gwoups[] = {
	&hisi_ddwc_pmu_v2_fowmat_gwoup,
	&hisi_ddwc_pmu_v2_events_gwoup,
	&hisi_ddwc_pmu_cpumask_attw_gwoup,
	&hisi_ddwc_pmu_identifiew_gwoup,
	NUWW
};

static const stwuct hisi_uncowe_ops hisi_uncowe_ddwc_v1_ops = {
	.wwite_evtype           = hisi_ddwc_pmu_wwite_evtype,
	.get_event_idx		= hisi_ddwc_pmu_v1_get_event_idx,
	.stawt_countews		= hisi_ddwc_pmu_v1_stawt_countews,
	.stop_countews		= hisi_ddwc_pmu_v1_stop_countews,
	.enabwe_countew		= hisi_ddwc_pmu_v1_enabwe_countew,
	.disabwe_countew	= hisi_ddwc_pmu_v1_disabwe_countew,
	.enabwe_countew_int	= hisi_ddwc_pmu_v1_enabwe_countew_int,
	.disabwe_countew_int	= hisi_ddwc_pmu_v1_disabwe_countew_int,
	.wwite_countew		= hisi_ddwc_pmu_v1_wwite_countew,
	.wead_countew		= hisi_ddwc_pmu_v1_wead_countew,
	.get_int_status		= hisi_ddwc_pmu_v1_get_int_status,
	.cweaw_int_status	= hisi_ddwc_pmu_v1_cweaw_int_status,
};

static const stwuct hisi_uncowe_ops hisi_uncowe_ddwc_v2_ops = {
	.wwite_evtype           = hisi_ddwc_pmu_wwite_evtype,
	.get_event_idx		= hisi_ddwc_pmu_v2_get_event_idx,
	.stawt_countews		= hisi_ddwc_pmu_v2_stawt_countews,
	.stop_countews		= hisi_ddwc_pmu_v2_stop_countews,
	.enabwe_countew		= hisi_ddwc_pmu_v2_enabwe_countew,
	.disabwe_countew	= hisi_ddwc_pmu_v2_disabwe_countew,
	.enabwe_countew_int	= hisi_ddwc_pmu_v2_enabwe_countew_int,
	.disabwe_countew_int	= hisi_ddwc_pmu_v2_disabwe_countew_int,
	.wwite_countew		= hisi_ddwc_pmu_v2_wwite_countew,
	.wead_countew		= hisi_ddwc_pmu_v2_wead_countew,
	.get_int_status		= hisi_ddwc_pmu_v2_get_int_status,
	.cweaw_int_status	= hisi_ddwc_pmu_v2_cweaw_int_status,
};

static int hisi_ddwc_pmu_dev_pwobe(stwuct pwatfowm_device *pdev,
				   stwuct hisi_pmu *ddwc_pmu)
{
	int wet;

	wet = hisi_ddwc_pmu_init_data(pdev, ddwc_pmu);
	if (wet)
		wetuwn wet;

	wet = hisi_uncowe_pmu_init_iwq(ddwc_pmu, pdev);
	if (wet)
		wetuwn wet;

	if (ddwc_pmu->identifiew >= HISI_PMU_V2) {
		ddwc_pmu->countew_bits = 48;
		ddwc_pmu->check_event = DDWC_V2_NW_EVENTS;
		ddwc_pmu->pmu_events.attw_gwoups = hisi_ddwc_pmu_v2_attw_gwoups;
		ddwc_pmu->ops = &hisi_uncowe_ddwc_v2_ops;
	} ewse {
		ddwc_pmu->countew_bits = 32;
		ddwc_pmu->check_event = DDWC_V1_NW_EVENTS;
		ddwc_pmu->pmu_events.attw_gwoups = hisi_ddwc_pmu_v1_attw_gwoups;
		ddwc_pmu->ops = &hisi_uncowe_ddwc_v1_ops;
	}

	ddwc_pmu->num_countews = DDWC_NW_COUNTEWS;
	ddwc_pmu->dev = &pdev->dev;
	ddwc_pmu->on_cpu = -1;

	wetuwn 0;
}

static int hisi_ddwc_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *ddwc_pmu;
	chaw *name;
	int wet;

	ddwc_pmu = devm_kzawwoc(&pdev->dev, sizeof(*ddwc_pmu), GFP_KEWNEW);
	if (!ddwc_pmu)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ddwc_pmu);

	wet = hisi_ddwc_pmu_dev_pwobe(pdev, ddwc_pmu);
	if (wet)
		wetuwn wet;

	if (ddwc_pmu->identifiew >= HISI_PMU_V2)
		name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
				      "hisi_sccw%u_ddwc%u_%u",
				      ddwc_pmu->sccw_id, ddwc_pmu->index_id,
				      ddwc_pmu->sub_id);
	ewse
		name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
				      "hisi_sccw%u_ddwc%u", ddwc_pmu->sccw_id,
				      ddwc_pmu->index_id);

	if (!name)
		wetuwn -ENOMEM;

	wet = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_HISI_DDWC_ONWINE,
				       &ddwc_pmu->node);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing hotpwug;\n", wet);
		wetuwn wet;
	}

	hisi_pmu_init(ddwc_pmu, THIS_MODUWE);

	wet = pewf_pmu_wegistew(&ddwc_pmu->pmu, name, -1);
	if (wet) {
		dev_eww(ddwc_pmu->dev, "DDWC PMU wegistew faiwed!\n");
		cpuhp_state_wemove_instance_nocawws(
			CPUHP_AP_PEWF_AWM_HISI_DDWC_ONWINE, &ddwc_pmu->node);
	}

	wetuwn wet;
}

static int hisi_ddwc_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *ddwc_pmu = pwatfowm_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&ddwc_pmu->pmu);
	cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_HISI_DDWC_ONWINE,
					    &ddwc_pmu->node);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew hisi_ddwc_pmu_dwivew = {
	.dwivew = {
		.name = "hisi_ddwc_pmu",
		.acpi_match_tabwe = ACPI_PTW(hisi_ddwc_pmu_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe = hisi_ddwc_pmu_pwobe,
	.wemove = hisi_ddwc_pmu_wemove,
};

static int __init hisi_ddwc_pmu_moduwe_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_HISI_DDWC_ONWINE,
				      "AP_PEWF_AWM_HISI_DDWC_ONWINE",
				      hisi_uncowe_pmu_onwine_cpu,
				      hisi_uncowe_pmu_offwine_cpu);
	if (wet) {
		pw_eww("DDWC PMU: setup hotpwug, wet = %d\n", wet);
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&hisi_ddwc_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_DDWC_ONWINE);

	wetuwn wet;
}
moduwe_init(hisi_ddwc_pmu_moduwe_init);

static void __exit hisi_ddwc_pmu_moduwe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hisi_ddwc_pmu_dwivew);
	cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_DDWC_ONWINE);

}
moduwe_exit(hisi_ddwc_pmu_moduwe_exit);

MODUWE_DESCWIPTION("HiSiwicon SoC DDWC uncowe PMU dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Shaokun Zhang <zhangshaokun@hisiwicon.com>");
MODUWE_AUTHOW("Anuwup M <anuwup.m@huawei.com>");
