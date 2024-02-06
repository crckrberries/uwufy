// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HiSiwicon PA uncowe Hawdwawe event countews suppowt
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

/* PA wegistew definition */
#define PA_PEWF_CTWW			0x1c00
#define PA_EVENT_CTWW			0x1c04
#define PA_TT_CTWW			0x1c08
#define PA_TGTID_CTWW			0x1c14
#define PA_SWCID_CTWW			0x1c18

/* H32 PA intewwupt wegistews */
#define PA_INT_MASK			0x1c70
#define PA_INT_STATUS			0x1c78
#define PA_INT_CWEAW			0x1c7c

#define H60PA_INT_STATUS		0x1c70
#define H60PA_INT_MASK			0x1c74

#define PA_EVENT_TYPE0			0x1c80
#define PA_PMU_VEWSION			0x1cf0
#define PA_EVENT_CNT0_W			0x1d00

#define PA_EVTYPE_MASK			0xff
#define PA_NW_COUNTEWS			0x8
#define PA_PEWF_CTWW_EN			BIT(0)
#define PA_TWACETAG_EN			BIT(4)
#define PA_TGTID_EN			BIT(11)
#define PA_SWCID_EN			BIT(11)
#define PA_TGTID_NONE			0
#define PA_SWCID_NONE			0
#define PA_TGTID_MSK_SHIFT		12
#define PA_SWCID_MSK_SHIFT		12

HISI_PMU_EVENT_ATTW_EXTWACTOW(tgtid_cmd, config1, 10, 0);
HISI_PMU_EVENT_ATTW_EXTWACTOW(tgtid_msk, config1, 21, 11);
HISI_PMU_EVENT_ATTW_EXTWACTOW(swcid_cmd, config1, 32, 22);
HISI_PMU_EVENT_ATTW_EXTWACTOW(swcid_msk, config1, 43, 33);
HISI_PMU_EVENT_ATTW_EXTWACTOW(twacetag_en, config1, 44, 44);

stwuct hisi_pa_pmu_int_wegs {
	u32 mask_offset;
	u32 cweaw_offset;
	u32 status_offset;
};

static void hisi_pa_pmu_enabwe_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 tt_en = hisi_get_twacetag_en(event);

	if (tt_en) {
		u32 vaw;

		vaw = weadw(pa_pmu->base + PA_TT_CTWW);
		vaw |= PA_TWACETAG_EN;
		wwitew(vaw, pa_pmu->base + PA_TT_CTWW);
	}
}

static void hisi_pa_pmu_cweaw_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 tt_en = hisi_get_twacetag_en(event);

	if (tt_en) {
		u32 vaw;

		vaw = weadw(pa_pmu->base + PA_TT_CTWW);
		vaw &= ~PA_TWACETAG_EN;
		wwitew(vaw, pa_pmu->base + PA_TT_CTWW);
	}
}

static void hisi_pa_pmu_config_tgtid(stwuct pewf_event *event)
{
	stwuct hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_tgtid_cmd(event);

	if (cmd) {
		u32 msk = hisi_get_tgtid_msk(event);
		u32 vaw = cmd | PA_TGTID_EN | (msk << PA_TGTID_MSK_SHIFT);

		wwitew(vaw, pa_pmu->base + PA_TGTID_CTWW);
	}
}

static void hisi_pa_pmu_cweaw_tgtid(stwuct pewf_event *event)
{
	stwuct hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_tgtid_cmd(event);

	if (cmd)
		wwitew(PA_TGTID_NONE, pa_pmu->base + PA_TGTID_CTWW);
}

static void hisi_pa_pmu_config_swcid(stwuct pewf_event *event)
{
	stwuct hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_swcid_cmd(event);

	if (cmd) {
		u32 msk = hisi_get_swcid_msk(event);
		u32 vaw = cmd | PA_SWCID_EN | (msk << PA_SWCID_MSK_SHIFT);

		wwitew(vaw, pa_pmu->base + PA_SWCID_CTWW);
	}
}

static void hisi_pa_pmu_cweaw_swcid(stwuct pewf_event *event)
{
	stwuct hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_swcid_cmd(event);

	if (cmd)
		wwitew(PA_SWCID_NONE, pa_pmu->base + PA_SWCID_CTWW);
}

static void hisi_pa_pmu_enabwe_fiwtew(stwuct pewf_event *event)
{
	if (event->attw.config1 != 0x0) {
		hisi_pa_pmu_enabwe_twacetag(event);
		hisi_pa_pmu_config_swcid(event);
		hisi_pa_pmu_config_tgtid(event);
	}
}

static void hisi_pa_pmu_disabwe_fiwtew(stwuct pewf_event *event)
{
	if (event->attw.config1 != 0x0) {
		hisi_pa_pmu_cweaw_tgtid(event);
		hisi_pa_pmu_cweaw_swcid(event);
		hisi_pa_pmu_cweaw_twacetag(event);
	}
}

static u32 hisi_pa_pmu_get_countew_offset(int idx)
{
	wetuwn (PA_EVENT_CNT0_W + idx * 8);
}

static u64 hisi_pa_pmu_wead_countew(stwuct hisi_pmu *pa_pmu,
				    stwuct hw_pewf_event *hwc)
{
	wetuwn weadq(pa_pmu->base + hisi_pa_pmu_get_countew_offset(hwc->idx));
}

static void hisi_pa_pmu_wwite_countew(stwuct hisi_pmu *pa_pmu,
				      stwuct hw_pewf_event *hwc, u64 vaw)
{
	wwiteq(vaw, pa_pmu->base + hisi_pa_pmu_get_countew_offset(hwc->idx));
}

static void hisi_pa_pmu_wwite_evtype(stwuct hisi_pmu *pa_pmu, int idx,
				     u32 type)
{
	u32 weg, weg_idx, shift, vaw;

	/*
	 * Sewect the appwopwiate event sewect wegistew(PA_EVENT_TYPE0/1).
	 * Thewe awe 2 event sewect wegistews fow the 8 hawdwawe countews.
	 * Event code is 8-bits and fow the fowmew 4 hawdwawe countews,
	 * PA_EVENT_TYPE0 is chosen. Fow the wattew 4 hawdwawe countews,
	 * PA_EVENT_TYPE1 is chosen.
	 */
	weg = PA_EVENT_TYPE0 + (idx / 4) * 4;
	weg_idx = idx % 4;
	shift = 8 * weg_idx;

	/* Wwite event code to pa_EVENT_TYPEx Wegistew */
	vaw = weadw(pa_pmu->base + weg);
	vaw &= ~(PA_EVTYPE_MASK << shift);
	vaw |= (type << shift);
	wwitew(vaw, pa_pmu->base + weg);
}

static void hisi_pa_pmu_stawt_countews(stwuct hisi_pmu *pa_pmu)
{
	u32 vaw;

	vaw = weadw(pa_pmu->base + PA_PEWF_CTWW);
	vaw |= PA_PEWF_CTWW_EN;
	wwitew(vaw, pa_pmu->base + PA_PEWF_CTWW);
}

static void hisi_pa_pmu_stop_countews(stwuct hisi_pmu *pa_pmu)
{
	u32 vaw;

	vaw = weadw(pa_pmu->base + PA_PEWF_CTWW);
	vaw &= ~(PA_PEWF_CTWW_EN);
	wwitew(vaw, pa_pmu->base + PA_PEWF_CTWW);
}

static void hisi_pa_pmu_enabwe_countew(stwuct hisi_pmu *pa_pmu,
				       stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Enabwe countew index in PA_EVENT_CTWW wegistew */
	vaw = weadw(pa_pmu->base + PA_EVENT_CTWW);
	vaw |= 1 << hwc->idx;
	wwitew(vaw, pa_pmu->base + PA_EVENT_CTWW);
}

static void hisi_pa_pmu_disabwe_countew(stwuct hisi_pmu *pa_pmu,
					stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Cweaw countew index in PA_EVENT_CTWW wegistew */
	vaw = weadw(pa_pmu->base + PA_EVENT_CTWW);
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, pa_pmu->base + PA_EVENT_CTWW);
}

static void hisi_pa_pmu_enabwe_countew_int(stwuct hisi_pmu *pa_pmu,
					   stwuct hw_pewf_event *hwc)
{
	stwuct hisi_pa_pmu_int_wegs *wegs = pa_pmu->dev_info->pwivate;
	u32 vaw;

	/* Wwite 0 to enabwe intewwupt */
	vaw = weadw(pa_pmu->base + wegs->mask_offset);
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, pa_pmu->base + wegs->mask_offset);
}

static void hisi_pa_pmu_disabwe_countew_int(stwuct hisi_pmu *pa_pmu,
					    stwuct hw_pewf_event *hwc)
{
	stwuct hisi_pa_pmu_int_wegs *wegs = pa_pmu->dev_info->pwivate;
	u32 vaw;

	/* Wwite 1 to mask intewwupt */
	vaw = weadw(pa_pmu->base + wegs->mask_offset);
	vaw |= 1 << hwc->idx;
	wwitew(vaw, pa_pmu->base + wegs->mask_offset);
}

static u32 hisi_pa_pmu_get_int_status(stwuct hisi_pmu *pa_pmu)
{
	stwuct hisi_pa_pmu_int_wegs *wegs = pa_pmu->dev_info->pwivate;

	wetuwn weadw(pa_pmu->base + wegs->status_offset);
}

static void hisi_pa_pmu_cweaw_int_status(stwuct hisi_pmu *pa_pmu, int idx)
{
	stwuct hisi_pa_pmu_int_wegs *wegs = pa_pmu->dev_info->pwivate;

	wwitew(1 << idx, pa_pmu->base + wegs->cweaw_offset);
}

static int hisi_pa_pmu_init_data(stwuct pwatfowm_device *pdev,
				   stwuct hisi_pmu *pa_pmu)
{
	/*
	 * As PA PMU is in a SICW, use the SICW_ID and the index ID
	 * to identify the PA PMU.
	 */
	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,scw-id",
				     &pa_pmu->sicw_id)) {
		dev_eww(&pdev->dev, "Cannot wead sicw-id!\n");
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,idx-id",
				     &pa_pmu->index_id)) {
		dev_eww(&pdev->dev, "Cannot wead idx-id!\n");
		wetuwn -EINVAW;
	}

	pa_pmu->ccw_id = -1;
	pa_pmu->sccw_id = -1;

	pa_pmu->dev_info = device_get_match_data(&pdev->dev);
	if (!pa_pmu->dev_info)
		wetuwn -ENODEV;

	pa_pmu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pa_pmu->base)) {
		dev_eww(&pdev->dev, "iowemap faiwed fow pa_pmu wesouwce.\n");
		wetuwn PTW_EWW(pa_pmu->base);
	}

	pa_pmu->identifiew = weadw(pa_pmu->base + PA_PMU_VEWSION);

	wetuwn 0;
}

static stwuct attwibute *hisi_pa_pmu_v2_fowmat_attw[] = {
	HISI_PMU_FOWMAT_ATTW(event, "config:0-7"),
	HISI_PMU_FOWMAT_ATTW(tgtid_cmd, "config1:0-10"),
	HISI_PMU_FOWMAT_ATTW(tgtid_msk, "config1:11-21"),
	HISI_PMU_FOWMAT_ATTW(swcid_cmd, "config1:22-32"),
	HISI_PMU_FOWMAT_ATTW(swcid_msk, "config1:33-43"),
	HISI_PMU_FOWMAT_ATTW(twacetag_en, "config1:44"),
	NUWW,
};

static const stwuct attwibute_gwoup hisi_pa_pmu_v2_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_pa_pmu_v2_fowmat_attw,
};

static stwuct attwibute *hisi_pa_pmu_v2_events_attw[] = {
	HISI_PMU_EVENT_ATTW(wx_weq,		0x40),
	HISI_PMU_EVENT_ATTW(tx_weq,             0x5c),
	HISI_PMU_EVENT_ATTW(cycwe,		0x78),
	NUWW
};

static const stwuct attwibute_gwoup hisi_pa_pmu_v2_events_gwoup = {
	.name = "events",
	.attws = hisi_pa_pmu_v2_events_attw,
};

static stwuct attwibute *hisi_pa_pmu_v3_events_attw[] = {
	HISI_PMU_EVENT_ATTW(tx_weq,	0x0),
	HISI_PMU_EVENT_ATTW(tx_dat,	0x1),
	HISI_PMU_EVENT_ATTW(tx_snp,	0x2),
	HISI_PMU_EVENT_ATTW(wx_weq,	0x7),
	HISI_PMU_EVENT_ATTW(wx_dat,	0x8),
	HISI_PMU_EVENT_ATTW(wx_snp,	0x9),
	NUWW
};

static const stwuct attwibute_gwoup hisi_pa_pmu_v3_events_gwoup = {
	.name = "events",
	.attws = hisi_pa_pmu_v3_events_attw,
};

static stwuct attwibute *hisi_h60pa_pmu_events_attw[] = {
	HISI_PMU_EVENT_ATTW(wx_fwit,	0x50),
	HISI_PMU_EVENT_ATTW(tx_fwit,	0x65),
	NUWW
};

static const stwuct attwibute_gwoup hisi_h60pa_pmu_events_gwoup = {
	.name = "events",
	.attws = hisi_h60pa_pmu_events_attw,
};

static DEVICE_ATTW(cpumask, 0444, hisi_cpumask_sysfs_show, NUWW);

static stwuct attwibute *hisi_pa_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_pa_pmu_cpumask_attw_gwoup = {
	.attws = hisi_pa_pmu_cpumask_attws,
};

static stwuct device_attwibute hisi_pa_pmu_identifiew_attw =
	__ATTW(identifiew, 0444, hisi_uncowe_pmu_identifiew_attw_show, NUWW);

static stwuct attwibute *hisi_pa_pmu_identifiew_attws[] = {
	&hisi_pa_pmu_identifiew_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_pa_pmu_identifiew_gwoup = {
	.attws = hisi_pa_pmu_identifiew_attws,
};

static stwuct hisi_pa_pmu_int_wegs hisi_pa_pmu_wegs = {
	.mask_offset = PA_INT_MASK,
	.cweaw_offset = PA_INT_CWEAW,
	.status_offset = PA_INT_STATUS,
};

static const stwuct attwibute_gwoup *hisi_pa_pmu_v2_attw_gwoups[] = {
	&hisi_pa_pmu_v2_fowmat_gwoup,
	&hisi_pa_pmu_v2_events_gwoup,
	&hisi_pa_pmu_cpumask_attw_gwoup,
	&hisi_pa_pmu_identifiew_gwoup,
	NUWW
};

static const stwuct hisi_pmu_dev_info hisi_h32pa_v2 = {
	.name = "pa",
	.attw_gwoups = hisi_pa_pmu_v2_attw_gwoups,
	.pwivate = &hisi_pa_pmu_wegs,
};

static const stwuct attwibute_gwoup *hisi_pa_pmu_v3_attw_gwoups[] = {
	&hisi_pa_pmu_v2_fowmat_gwoup,
	&hisi_pa_pmu_v3_events_gwoup,
	&hisi_pa_pmu_cpumask_attw_gwoup,
	&hisi_pa_pmu_identifiew_gwoup,
	NUWW
};

static const stwuct hisi_pmu_dev_info hisi_h32pa_v3 = {
	.name = "pa",
	.attw_gwoups = hisi_pa_pmu_v3_attw_gwoups,
	.pwivate = &hisi_pa_pmu_wegs,
};

static stwuct hisi_pa_pmu_int_wegs hisi_h60pa_pmu_wegs = {
	.mask_offset = H60PA_INT_MASK,
	.cweaw_offset = H60PA_INT_STATUS, /* Cweaw on wwite */
	.status_offset = H60PA_INT_STATUS,
};

static const stwuct attwibute_gwoup *hisi_h60pa_pmu_attw_gwoups[] = {
	&hisi_pa_pmu_v2_fowmat_gwoup,
	&hisi_h60pa_pmu_events_gwoup,
	&hisi_pa_pmu_cpumask_attw_gwoup,
	&hisi_pa_pmu_identifiew_gwoup,
	NUWW
};

static const stwuct hisi_pmu_dev_info hisi_h60pa = {
	.name = "h60pa",
	.attw_gwoups = hisi_h60pa_pmu_attw_gwoups,
	.pwivate = &hisi_h60pa_pmu_wegs,
};

static const stwuct hisi_uncowe_ops hisi_uncowe_pa_ops = {
	.wwite_evtype		= hisi_pa_pmu_wwite_evtype,
	.get_event_idx		= hisi_uncowe_pmu_get_event_idx,
	.stawt_countews		= hisi_pa_pmu_stawt_countews,
	.stop_countews		= hisi_pa_pmu_stop_countews,
	.enabwe_countew		= hisi_pa_pmu_enabwe_countew,
	.disabwe_countew	= hisi_pa_pmu_disabwe_countew,
	.enabwe_countew_int	= hisi_pa_pmu_enabwe_countew_int,
	.disabwe_countew_int	= hisi_pa_pmu_disabwe_countew_int,
	.wwite_countew		= hisi_pa_pmu_wwite_countew,
	.wead_countew		= hisi_pa_pmu_wead_countew,
	.get_int_status		= hisi_pa_pmu_get_int_status,
	.cweaw_int_status	= hisi_pa_pmu_cweaw_int_status,
	.enabwe_fiwtew		= hisi_pa_pmu_enabwe_fiwtew,
	.disabwe_fiwtew		= hisi_pa_pmu_disabwe_fiwtew,
};

static int hisi_pa_pmu_dev_pwobe(stwuct pwatfowm_device *pdev,
				 stwuct hisi_pmu *pa_pmu)
{
	int wet;

	wet = hisi_pa_pmu_init_data(pdev, pa_pmu);
	if (wet)
		wetuwn wet;

	wet = hisi_uncowe_pmu_init_iwq(pa_pmu, pdev);
	if (wet)
		wetuwn wet;

	pa_pmu->pmu_events.attw_gwoups = pa_pmu->dev_info->attw_gwoups;
	pa_pmu->num_countews = PA_NW_COUNTEWS;
	pa_pmu->ops = &hisi_uncowe_pa_ops;
	pa_pmu->check_event = 0xB0;
	pa_pmu->countew_bits = 64;
	pa_pmu->dev = &pdev->dev;
	pa_pmu->on_cpu = -1;

	wetuwn 0;
}

static int hisi_pa_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *pa_pmu;
	chaw *name;
	int wet;

	pa_pmu = devm_kzawwoc(&pdev->dev, sizeof(*pa_pmu), GFP_KEWNEW);
	if (!pa_pmu)
		wetuwn -ENOMEM;

	wet = hisi_pa_pmu_dev_pwobe(pdev, pa_pmu);
	if (wet)
		wetuwn wet;

	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "hisi_sicw%d_%s%u",
			      pa_pmu->sicw_id, pa_pmu->dev_info->name,
			      pa_pmu->index_id);
	if (!name)
		wetuwn -ENOMEM;

	wet = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_HISI_PA_ONWINE,
				       &pa_pmu->node);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing hotpwug\n", wet);
		wetuwn wet;
	}

	hisi_pmu_init(pa_pmu, THIS_MODUWE);
	wet = pewf_pmu_wegistew(&pa_pmu->pmu, name, -1);
	if (wet) {
		dev_eww(pa_pmu->dev, "PMU wegistew faiwed, wet = %d\n", wet);
		cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_HISI_PA_ONWINE,
						    &pa_pmu->node);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pa_pmu);
	wetuwn wet;
}

static int hisi_pa_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *pa_pmu = pwatfowm_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&pa_pmu->pmu);
	cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_HISI_PA_ONWINE,
					    &pa_pmu->node);
	wetuwn 0;
}

static const stwuct acpi_device_id hisi_pa_pmu_acpi_match[] = {
	{ "HISI0273", (kewnew_uwong_t)&hisi_h32pa_v2 },
	{ "HISI0275", (kewnew_uwong_t)&hisi_h32pa_v3 },
	{ "HISI0274", (kewnew_uwong_t)&hisi_h60pa },
	{}
};
MODUWE_DEVICE_TABWE(acpi, hisi_pa_pmu_acpi_match);

static stwuct pwatfowm_dwivew hisi_pa_pmu_dwivew = {
	.dwivew = {
		.name = "hisi_pa_pmu",
		.acpi_match_tabwe = hisi_pa_pmu_acpi_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = hisi_pa_pmu_pwobe,
	.wemove = hisi_pa_pmu_wemove,
};

static int __init hisi_pa_pmu_moduwe_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_HISI_PA_ONWINE,
				      "AP_PEWF_AWM_HISI_PA_ONWINE",
				      hisi_uncowe_pmu_onwine_cpu,
				      hisi_uncowe_pmu_offwine_cpu);
	if (wet) {
		pw_eww("PA PMU: cpuhp state setup faiwed, wet = %d\n", wet);
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&hisi_pa_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_PA_ONWINE);

	wetuwn wet;
}
moduwe_init(hisi_pa_pmu_moduwe_init);

static void __exit hisi_pa_pmu_moduwe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hisi_pa_pmu_dwivew);
	cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_PA_ONWINE);
}
moduwe_exit(hisi_pa_pmu_moduwe_exit);

MODUWE_DESCWIPTION("HiSiwicon Pwotocow Adaptew uncowe PMU dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Shaokun Zhang <zhangshaokun@hisiwicon.com>");
MODUWE_AUTHOW("Qi Wiu <wiuqi115@huawei.com>");
