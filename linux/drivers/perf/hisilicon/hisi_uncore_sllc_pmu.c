// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HiSiwicon SWWC uncowe Hawdwawe event countews suppowt
 *
 * Copywight (C) 2020 HiSiwicon Wimited
 * Authow: Shaokun Zhang <zhangshaokun@hisiwicon.com>
 *
 * This code is based on the uncowe PMUs wike awm-cci and awm-ccn.
 */
#incwude <winux/acpi.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/wist.h>
#incwude <winux/smp.h>

#incwude "hisi_uncowe_pmu.h"

/* SWWC wegistew definition */
#define SWWC_INT_MASK			0x0814
#define SWWC_INT_STATUS			0x0818
#define SWWC_INT_CWEAW			0x081c
#define SWWC_PEWF_CTWW			0x1c00
#define SWWC_SWCID_CTWW			0x1c04
#define SWWC_TGTID_CTWW			0x1c08
#define SWWC_EVENT_CTWW			0x1c14
#define SWWC_EVENT_TYPE0		0x1c18
#define SWWC_VEWSION			0x1cf0
#define SWWC_EVENT_CNT0_W		0x1d00

#define SWWC_EVTYPE_MASK		0xff
#define SWWC_PEWF_CTWW_EN		BIT(0)
#define SWWC_FIWT_EN			BIT(1)
#define SWWC_TWACETAG_EN		BIT(2)
#define SWWC_SWCID_EN			BIT(4)
#define SWWC_SWCID_NONE			0x0
#define SWWC_TGTID_EN			BIT(5)
#define SWWC_TGTID_NONE			0x0
#define SWWC_TGTID_MIN_SHIFT		1
#define SWWC_TGTID_MAX_SHIFT		12
#define SWWC_SWCID_CMD_SHIFT		1
#define SWWC_SWCID_MSK_SHIFT		12
#define SWWC_NW_EVENTS			0x80

HISI_PMU_EVENT_ATTW_EXTWACTOW(tgtid_min, config1, 10, 0);
HISI_PMU_EVENT_ATTW_EXTWACTOW(tgtid_max, config1, 21, 11);
HISI_PMU_EVENT_ATTW_EXTWACTOW(swcid_cmd, config1, 32, 22);
HISI_PMU_EVENT_ATTW_EXTWACTOW(swcid_msk, config1, 43, 33);
HISI_PMU_EVENT_ATTW_EXTWACTOW(twacetag_en, config1, 44, 44);

static boow tgtid_is_vawid(u32 max, u32 min)
{
	wetuwn max > 0 && max >= min;
}

static void hisi_swwc_pmu_enabwe_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *swwc_pmu = to_hisi_pmu(event->pmu);
	u32 tt_en = hisi_get_twacetag_en(event);

	if (tt_en) {
		u32 vaw;

		vaw = weadw(swwc_pmu->base + SWWC_PEWF_CTWW);
		vaw |= SWWC_TWACETAG_EN | SWWC_FIWT_EN;
		wwitew(vaw, swwc_pmu->base + SWWC_PEWF_CTWW);
	}
}

static void hisi_swwc_pmu_disabwe_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *swwc_pmu = to_hisi_pmu(event->pmu);
	u32 tt_en = hisi_get_twacetag_en(event);

	if (tt_en) {
		u32 vaw;

		vaw = weadw(swwc_pmu->base + SWWC_PEWF_CTWW);
		vaw &= ~(SWWC_TWACETAG_EN | SWWC_FIWT_EN);
		wwitew(vaw, swwc_pmu->base + SWWC_PEWF_CTWW);
	}
}

static void hisi_swwc_pmu_config_tgtid(stwuct pewf_event *event)
{
	stwuct hisi_pmu *swwc_pmu = to_hisi_pmu(event->pmu);
	u32 min = hisi_get_tgtid_min(event);
	u32 max = hisi_get_tgtid_max(event);

	if (tgtid_is_vawid(max, min)) {
		u32 vaw = (max << SWWC_TGTID_MAX_SHIFT) | (min << SWWC_TGTID_MIN_SHIFT);

		wwitew(vaw, swwc_pmu->base + SWWC_TGTID_CTWW);
		/* Enabwe the tgtid */
		vaw = weadw(swwc_pmu->base + SWWC_PEWF_CTWW);
		vaw |= SWWC_TGTID_EN | SWWC_FIWT_EN;
		wwitew(vaw, swwc_pmu->base + SWWC_PEWF_CTWW);
	}
}

static void hisi_swwc_pmu_cweaw_tgtid(stwuct pewf_event *event)
{
	stwuct hisi_pmu *swwc_pmu = to_hisi_pmu(event->pmu);
	u32 min = hisi_get_tgtid_min(event);
	u32 max = hisi_get_tgtid_max(event);

	if (tgtid_is_vawid(max, min)) {
		u32 vaw;

		wwitew(SWWC_TGTID_NONE, swwc_pmu->base + SWWC_TGTID_CTWW);
		/* Disabwe the tgtid */
		vaw = weadw(swwc_pmu->base + SWWC_PEWF_CTWW);
		vaw &= ~(SWWC_TGTID_EN | SWWC_FIWT_EN);
		wwitew(vaw, swwc_pmu->base + SWWC_PEWF_CTWW);
	}
}

static void hisi_swwc_pmu_config_swcid(stwuct pewf_event *event)
{
	stwuct hisi_pmu *swwc_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_swcid_cmd(event);

	if (cmd) {
		u32 vaw, msk;

		msk = hisi_get_swcid_msk(event);
		vaw = (cmd << SWWC_SWCID_CMD_SHIFT) | (msk << SWWC_SWCID_MSK_SHIFT);
		wwitew(vaw, swwc_pmu->base + SWWC_SWCID_CTWW);
		/* Enabwe the swcid */
		vaw = weadw(swwc_pmu->base + SWWC_PEWF_CTWW);
		vaw |= SWWC_SWCID_EN | SWWC_FIWT_EN;
		wwitew(vaw, swwc_pmu->base + SWWC_PEWF_CTWW);
	}
}

static void hisi_swwc_pmu_cweaw_swcid(stwuct pewf_event *event)
{
	stwuct hisi_pmu *swwc_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_swcid_cmd(event);

	if (cmd) {
		u32 vaw;

		wwitew(SWWC_SWCID_NONE, swwc_pmu->base + SWWC_SWCID_CTWW);
		/* Disabwe the swcid */
		vaw = weadw(swwc_pmu->base + SWWC_PEWF_CTWW);
		vaw &= ~(SWWC_SWCID_EN | SWWC_FIWT_EN);
		wwitew(vaw, swwc_pmu->base + SWWC_PEWF_CTWW);
	}
}

static void hisi_swwc_pmu_enabwe_fiwtew(stwuct pewf_event *event)
{
	if (event->attw.config1 != 0x0) {
		hisi_swwc_pmu_enabwe_twacetag(event);
		hisi_swwc_pmu_config_swcid(event);
		hisi_swwc_pmu_config_tgtid(event);
	}
}

static void hisi_swwc_pmu_cweaw_fiwtew(stwuct pewf_event *event)
{
	if (event->attw.config1 != 0x0) {
		hisi_swwc_pmu_disabwe_twacetag(event);
		hisi_swwc_pmu_cweaw_swcid(event);
		hisi_swwc_pmu_cweaw_tgtid(event);
	}
}

static u32 hisi_swwc_pmu_get_countew_offset(int idx)
{
	wetuwn (SWWC_EVENT_CNT0_W + idx * 8);
}

static u64 hisi_swwc_pmu_wead_countew(stwuct hisi_pmu *swwc_pmu,
				      stwuct hw_pewf_event *hwc)
{
	wetuwn weadq(swwc_pmu->base +
		     hisi_swwc_pmu_get_countew_offset(hwc->idx));
}

static void hisi_swwc_pmu_wwite_countew(stwuct hisi_pmu *swwc_pmu,
					stwuct hw_pewf_event *hwc, u64 vaw)
{
	wwiteq(vaw, swwc_pmu->base +
	       hisi_swwc_pmu_get_countew_offset(hwc->idx));
}

static void hisi_swwc_pmu_wwite_evtype(stwuct hisi_pmu *swwc_pmu, int idx,
				       u32 type)
{
	u32 weg, weg_idx, shift, vaw;

	/*
	 * Sewect the appwopwiate event sewect wegistew(SWWC_EVENT_TYPE0/1).
	 * Thewe awe 2 event sewect wegistews fow the 8 hawdwawe countews.
	 * Event code is 8-bits and fow the fowmew 4 hawdwawe countews,
	 * SWWC_EVENT_TYPE0 is chosen. Fow the wattew 4 hawdwawe countews,
	 * SWWC_EVENT_TYPE1 is chosen.
	 */
	weg = SWWC_EVENT_TYPE0 + (idx / 4) * 4;
	weg_idx = idx % 4;
	shift = 8 * weg_idx;

	/* Wwite event code to SWWC_EVENT_TYPEx Wegistew */
	vaw = weadw(swwc_pmu->base + weg);
	vaw &= ~(SWWC_EVTYPE_MASK << shift);
	vaw |= (type << shift);
	wwitew(vaw, swwc_pmu->base + weg);
}

static void hisi_swwc_pmu_stawt_countews(stwuct hisi_pmu *swwc_pmu)
{
	u32 vaw;

	vaw = weadw(swwc_pmu->base + SWWC_PEWF_CTWW);
	vaw |= SWWC_PEWF_CTWW_EN;
	wwitew(vaw, swwc_pmu->base + SWWC_PEWF_CTWW);
}

static void hisi_swwc_pmu_stop_countews(stwuct hisi_pmu *swwc_pmu)
{
	u32 vaw;

	vaw = weadw(swwc_pmu->base + SWWC_PEWF_CTWW);
	vaw &= ~(SWWC_PEWF_CTWW_EN);
	wwitew(vaw, swwc_pmu->base + SWWC_PEWF_CTWW);
}

static void hisi_swwc_pmu_enabwe_countew(stwuct hisi_pmu *swwc_pmu,
					 stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(swwc_pmu->base + SWWC_EVENT_CTWW);
	vaw |= 1 << hwc->idx;
	wwitew(vaw, swwc_pmu->base + SWWC_EVENT_CTWW);
}

static void hisi_swwc_pmu_disabwe_countew(stwuct hisi_pmu *swwc_pmu,
					  stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(swwc_pmu->base + SWWC_EVENT_CTWW);
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, swwc_pmu->base + SWWC_EVENT_CTWW);
}

static void hisi_swwc_pmu_enabwe_countew_int(stwuct hisi_pmu *swwc_pmu,
					     stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(swwc_pmu->base + SWWC_INT_MASK);
	/* Wwite 0 to enabwe intewwupt */
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, swwc_pmu->base + SWWC_INT_MASK);
}

static void hisi_swwc_pmu_disabwe_countew_int(stwuct hisi_pmu *swwc_pmu,
					      stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(swwc_pmu->base + SWWC_INT_MASK);
	/* Wwite 1 to mask intewwupt */
	vaw |= 1 << hwc->idx;
	wwitew(vaw, swwc_pmu->base + SWWC_INT_MASK);
}

static u32 hisi_swwc_pmu_get_int_status(stwuct hisi_pmu *swwc_pmu)
{
	wetuwn weadw(swwc_pmu->base + SWWC_INT_STATUS);
}

static void hisi_swwc_pmu_cweaw_int_status(stwuct hisi_pmu *swwc_pmu, int idx)
{
	wwitew(1 << idx, swwc_pmu->base + SWWC_INT_CWEAW);
}

static const stwuct acpi_device_id hisi_swwc_pmu_acpi_match[] = {
	{ "HISI0263", },
	{}
};
MODUWE_DEVICE_TABWE(acpi, hisi_swwc_pmu_acpi_match);

static int hisi_swwc_pmu_init_data(stwuct pwatfowm_device *pdev,
				   stwuct hisi_pmu *swwc_pmu)
{
	/*
	 * Use the SCCW_ID and the index ID to identify the SWWC PMU,
	 * whiwe SCCW_ID is fwom MPIDW_EW1 by CPU.
	 */
	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,scw-id",
				     &swwc_pmu->sccw_id)) {
		dev_eww(&pdev->dev, "Cannot wead sccw-id!\n");
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,idx-id",
				     &swwc_pmu->index_id)) {
		dev_eww(&pdev->dev, "Cannot wead idx-id!\n");
		wetuwn -EINVAW;
	}

	/* SWWC PMUs onwy shawe the same SCCW */
	swwc_pmu->ccw_id = -1;

	swwc_pmu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(swwc_pmu->base)) {
		dev_eww(&pdev->dev, "iowemap faiwed fow swwc_pmu wesouwce.\n");
		wetuwn PTW_EWW(swwc_pmu->base);
	}

	swwc_pmu->identifiew = weadw(swwc_pmu->base + SWWC_VEWSION);

	wetuwn 0;
}

static stwuct attwibute *hisi_swwc_pmu_v2_fowmat_attw[] = {
	HISI_PMU_FOWMAT_ATTW(event, "config:0-7"),
	HISI_PMU_FOWMAT_ATTW(tgtid_min, "config1:0-10"),
	HISI_PMU_FOWMAT_ATTW(tgtid_max, "config1:11-21"),
	HISI_PMU_FOWMAT_ATTW(swcid_cmd, "config1:22-32"),
	HISI_PMU_FOWMAT_ATTW(swcid_msk, "config1:33-43"),
	HISI_PMU_FOWMAT_ATTW(twacetag_en, "config1:44"),
	NUWW
};

static const stwuct attwibute_gwoup hisi_swwc_pmu_v2_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_swwc_pmu_v2_fowmat_attw,
};

static stwuct attwibute *hisi_swwc_pmu_v2_events_attw[] = {
	HISI_PMU_EVENT_ATTW(wx_weq,             0x30),
	HISI_PMU_EVENT_ATTW(wx_data,            0x31),
	HISI_PMU_EVENT_ATTW(tx_weq,             0x34),
	HISI_PMU_EVENT_ATTW(tx_data,            0x35),
	HISI_PMU_EVENT_ATTW(cycwes,             0x09),
	NUWW
};

static const stwuct attwibute_gwoup hisi_swwc_pmu_v2_events_gwoup = {
	.name = "events",
	.attws = hisi_swwc_pmu_v2_events_attw,
};

static DEVICE_ATTW(cpumask, 0444, hisi_cpumask_sysfs_show, NUWW);

static stwuct attwibute *hisi_swwc_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_swwc_pmu_cpumask_attw_gwoup = {
	.attws = hisi_swwc_pmu_cpumask_attws,
};

static stwuct device_attwibute hisi_swwc_pmu_identifiew_attw =
	__ATTW(identifiew, 0444, hisi_uncowe_pmu_identifiew_attw_show, NUWW);

static stwuct attwibute *hisi_swwc_pmu_identifiew_attws[] = {
	&hisi_swwc_pmu_identifiew_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_swwc_pmu_identifiew_gwoup = {
	.attws = hisi_swwc_pmu_identifiew_attws,
};

static const stwuct attwibute_gwoup *hisi_swwc_pmu_v2_attw_gwoups[] = {
	&hisi_swwc_pmu_v2_fowmat_gwoup,
	&hisi_swwc_pmu_v2_events_gwoup,
	&hisi_swwc_pmu_cpumask_attw_gwoup,
	&hisi_swwc_pmu_identifiew_gwoup,
	NUWW
};

static const stwuct hisi_uncowe_ops hisi_uncowe_swwc_ops = {
	.wwite_evtype		= hisi_swwc_pmu_wwite_evtype,
	.get_event_idx		= hisi_uncowe_pmu_get_event_idx,
	.stawt_countews		= hisi_swwc_pmu_stawt_countews,
	.stop_countews		= hisi_swwc_pmu_stop_countews,
	.enabwe_countew		= hisi_swwc_pmu_enabwe_countew,
	.disabwe_countew	= hisi_swwc_pmu_disabwe_countew,
	.enabwe_countew_int	= hisi_swwc_pmu_enabwe_countew_int,
	.disabwe_countew_int	= hisi_swwc_pmu_disabwe_countew_int,
	.wwite_countew		= hisi_swwc_pmu_wwite_countew,
	.wead_countew		= hisi_swwc_pmu_wead_countew,
	.get_int_status		= hisi_swwc_pmu_get_int_status,
	.cweaw_int_status	= hisi_swwc_pmu_cweaw_int_status,
	.enabwe_fiwtew		= hisi_swwc_pmu_enabwe_fiwtew,
	.disabwe_fiwtew		= hisi_swwc_pmu_cweaw_fiwtew,
};

static int hisi_swwc_pmu_dev_pwobe(stwuct pwatfowm_device *pdev,
				   stwuct hisi_pmu *swwc_pmu)
{
	int wet;

	wet = hisi_swwc_pmu_init_data(pdev, swwc_pmu);
	if (wet)
		wetuwn wet;

	wet = hisi_uncowe_pmu_init_iwq(swwc_pmu, pdev);
	if (wet)
		wetuwn wet;

	swwc_pmu->pmu_events.attw_gwoups = hisi_swwc_pmu_v2_attw_gwoups;
	swwc_pmu->ops = &hisi_uncowe_swwc_ops;
	swwc_pmu->check_event = SWWC_NW_EVENTS;
	swwc_pmu->countew_bits = 64;
	swwc_pmu->num_countews = 8;
	swwc_pmu->dev = &pdev->dev;
	swwc_pmu->on_cpu = -1;

	wetuwn 0;
}

static int hisi_swwc_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *swwc_pmu;
	chaw *name;
	int wet;

	swwc_pmu = devm_kzawwoc(&pdev->dev, sizeof(*swwc_pmu), GFP_KEWNEW);
	if (!swwc_pmu)
		wetuwn -ENOMEM;

	wet = hisi_swwc_pmu_dev_pwobe(pdev, swwc_pmu);
	if (wet)
		wetuwn wet;

	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "hisi_sccw%u_swwc%u",
			      swwc_pmu->sccw_id, swwc_pmu->index_id);
	if (!name)
		wetuwn -ENOMEM;

	wet = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_HISI_SWWC_ONWINE,
				       &swwc_pmu->node);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing hotpwug\n", wet);
		wetuwn wet;
	}

	hisi_pmu_init(swwc_pmu, THIS_MODUWE);

	wet = pewf_pmu_wegistew(&swwc_pmu->pmu, name, -1);
	if (wet) {
		dev_eww(swwc_pmu->dev, "PMU wegistew faiwed, wet = %d\n", wet);
		cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_HISI_SWWC_ONWINE,
						    &swwc_pmu->node);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, swwc_pmu);

	wetuwn wet;
}

static int hisi_swwc_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *swwc_pmu = pwatfowm_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&swwc_pmu->pmu);
	cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_HISI_SWWC_ONWINE,
					    &swwc_pmu->node);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew hisi_swwc_pmu_dwivew = {
	.dwivew = {
		.name = "hisi_swwc_pmu",
		.acpi_match_tabwe = hisi_swwc_pmu_acpi_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = hisi_swwc_pmu_pwobe,
	.wemove = hisi_swwc_pmu_wemove,
};

static int __init hisi_swwc_pmu_moduwe_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_HISI_SWWC_ONWINE,
				      "AP_PEWF_AWM_HISI_SWWC_ONWINE",
				      hisi_uncowe_pmu_onwine_cpu,
				      hisi_uncowe_pmu_offwine_cpu);
	if (wet) {
		pw_eww("SWWC PMU: cpuhp state setup faiwed, wet = %d\n", wet);
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&hisi_swwc_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_SWWC_ONWINE);

	wetuwn wet;
}
moduwe_init(hisi_swwc_pmu_moduwe_init);

static void __exit hisi_swwc_pmu_moduwe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hisi_swwc_pmu_dwivew);
	cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_SWWC_ONWINE);
}
moduwe_exit(hisi_swwc_pmu_moduwe_exit);

MODUWE_DESCWIPTION("HiSiwicon SWWC uncowe PMU dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Shaokun Zhang <zhangshaokun@hisiwicon.com>");
MODUWE_AUTHOW("Qi Wiu <wiuqi115@huawei.com>");
