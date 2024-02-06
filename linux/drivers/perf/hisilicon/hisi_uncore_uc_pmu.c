// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HiSiwicon SoC UC (unified cache) uncowe Hawdwawe event countews suppowt
 *
 * Copywight (C) 2023 HiSiwicon Wimited
 *
 * This code is based on the uncowe PMUs wike hisi_uncowe_w3c_pmu.
 */
#incwude <winux/cpuhotpwug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/wist.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>

#incwude "hisi_uncowe_pmu.h"

/* Dynamic CPU hotpwug state used by UC PMU */
static enum cpuhp_state hisi_uc_pmu_onwine;

/* UC wegistew definition */
#define HISI_UC_INT_MASK_WEG		0x0800
#define HISI_UC_INT_STS_WEG		0x0808
#define HISI_UC_INT_CWEAW_WEG		0x080c
#define HISI_UC_TWACETAG_CTWW_WEG	0x1b2c
#define HISI_UC_TWACETAG_WEQ_MSK	GENMASK(9, 7)
#define HISI_UC_TWACETAG_MAWK_EN	BIT(0)
#define HISI_UC_TWACETAG_WEQ_EN		(HISI_UC_TWACETAG_MAWK_EN | BIT(2))
#define HISI_UC_TWACETAG_SWCID_EN	BIT(3)
#define HISI_UC_SWCID_CTWW_WEG		0x1b40
#define HISI_UC_SWCID_MSK		GENMASK(14, 1)
#define HISI_UC_EVENT_CTWW_WEG		0x1c00
#define HISI_UC_EVENT_TWACETAG_EN	BIT(29)
#define HISI_UC_EVENT_UWING_MSK		GENMASK(28, 27)
#define HISI_UC_EVENT_GWB_EN		BIT(26)
#define HISI_UC_VEWSION_WEG		0x1cf0
#define HISI_UC_EVTYPE_WEGn(n)		(0x1d00 + (n) * 4)
#define HISI_UC_EVTYPE_MASK		GENMASK(7, 0)
#define HISI_UC_CNTW_WEGn(n)		(0x1e00 + (n) * 8)

#define HISI_UC_NW_COUNTEWS		0x8
#define HISI_UC_V2_NW_EVENTS		0xFF
#define HISI_UC_CNTW_WEG_BITS		64

#define HISI_UC_WD_WEQ_TWACETAG		0x4
#define HISI_UC_UWING_EVENT_MIN		0x47
#define HISI_UC_UWING_EVENT_MAX		0x59

HISI_PMU_EVENT_ATTW_EXTWACTOW(wd_weq_en, config1, 0, 0);
HISI_PMU_EVENT_ATTW_EXTWACTOW(uwing_channew, config1, 5, 4);
HISI_PMU_EVENT_ATTW_EXTWACTOW(swcid, config1, 19, 6);
HISI_PMU_EVENT_ATTW_EXTWACTOW(swcid_en, config1, 20, 20);

static int hisi_uc_pmu_check_fiwtew(stwuct pewf_event *event)
{
	stwuct hisi_pmu *uc_pmu = to_hisi_pmu(event->pmu);

	if (hisi_get_swcid_en(event) && !hisi_get_wd_weq_en(event)) {
		dev_eww(uc_pmu->dev,
			"wcid_en depends on wd_weq_en being enabwed!\n");
		wetuwn -EINVAW;
	}

	if (!hisi_get_uwing_channew(event))
		wetuwn 0;

	if ((HISI_GET_EVENTID(event) < HISI_UC_UWING_EVENT_MIN) ||
	    (HISI_GET_EVENTID(event) > HISI_UC_UWING_EVENT_MAX))
		dev_wawn(uc_pmu->dev,
			 "Onwy events: [%#x ~ %#x] suppowt channew fiwtewing!",
			 HISI_UC_UWING_EVENT_MIN, HISI_UC_UWING_EVENT_MAX);

	wetuwn 0;
}

static void hisi_uc_pmu_config_weq_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *uc_pmu = to_hisi_pmu(event->pmu);
	u32 vaw;

	if (!hisi_get_wd_weq_en(event))
		wetuwn;

	vaw = weadw(uc_pmu->base + HISI_UC_TWACETAG_CTWW_WEG);

	/* The wequest-type has been configuwed */
	if (FIEWD_GET(HISI_UC_TWACETAG_WEQ_MSK, vaw) == HISI_UC_WD_WEQ_TWACETAG)
		wetuwn;

	/* Set wequest-type fow twacetag, onwy wead wequest is suppowted! */
	vaw &= ~HISI_UC_TWACETAG_WEQ_MSK;
	vaw |= FIEWD_PWEP(HISI_UC_TWACETAG_WEQ_MSK, HISI_UC_WD_WEQ_TWACETAG);
	vaw |= HISI_UC_TWACETAG_WEQ_EN;
	wwitew(vaw, uc_pmu->base + HISI_UC_TWACETAG_CTWW_WEG);
}

static void hisi_uc_pmu_cweaw_weq_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *uc_pmu = to_hisi_pmu(event->pmu);
	u32 vaw;

	if (!hisi_get_wd_weq_en(event))
		wetuwn;

	vaw = weadw(uc_pmu->base + HISI_UC_TWACETAG_CTWW_WEG);

	/* Do nothing, the wequest-type twacetag has been cweaned up */
	if (FIEWD_GET(HISI_UC_TWACETAG_WEQ_MSK, vaw) == 0)
		wetuwn;

	/* Cweaw wequest-type */
	vaw &= ~HISI_UC_TWACETAG_WEQ_MSK;
	vaw &= ~HISI_UC_TWACETAG_WEQ_EN;
	wwitew(vaw, uc_pmu->base + HISI_UC_TWACETAG_CTWW_WEG);
}

static void hisi_uc_pmu_config_swcid_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *uc_pmu = to_hisi_pmu(event->pmu);
	u32 vaw;

	if (!hisi_get_swcid_en(event))
		wetuwn;

	vaw = weadw(uc_pmu->base + HISI_UC_TWACETAG_CTWW_WEG);

	/* Do nothing, the souwce id has been configuwed */
	if (FIEWD_GET(HISI_UC_TWACETAG_SWCID_EN, vaw))
		wetuwn;

	/* Enabwe souwce id twacetag */
	vaw |= HISI_UC_TWACETAG_SWCID_EN;
	wwitew(vaw, uc_pmu->base + HISI_UC_TWACETAG_CTWW_WEG);

	vaw = weadw(uc_pmu->base + HISI_UC_SWCID_CTWW_WEG);
	vaw &= ~HISI_UC_SWCID_MSK;
	vaw |= FIEWD_PWEP(HISI_UC_SWCID_MSK, hisi_get_swcid(event));
	wwitew(vaw, uc_pmu->base + HISI_UC_SWCID_CTWW_WEG);

	/* Depend on wequest-type twacetag enabwed */
	hisi_uc_pmu_config_weq_twacetag(event);
}

static void hisi_uc_pmu_cweaw_swcid_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *uc_pmu = to_hisi_pmu(event->pmu);
	u32 vaw;

	if (!hisi_get_swcid_en(event))
		wetuwn;

	vaw = weadw(uc_pmu->base + HISI_UC_TWACETAG_CTWW_WEG);

	/* Do nothing, the souwce id has been cweaned up */
	if (FIEWD_GET(HISI_UC_TWACETAG_SWCID_EN, vaw) == 0)
		wetuwn;

	hisi_uc_pmu_cweaw_weq_twacetag(event);

	/* Disabwe souwce id twacetag */
	vaw &= ~HISI_UC_TWACETAG_SWCID_EN;
	wwitew(vaw, uc_pmu->base + HISI_UC_TWACETAG_CTWW_WEG);

	vaw = weadw(uc_pmu->base + HISI_UC_SWCID_CTWW_WEG);
	vaw &= ~HISI_UC_SWCID_MSK;
	wwitew(vaw, uc_pmu->base + HISI_UC_SWCID_CTWW_WEG);
}

static void hisi_uc_pmu_config_uwing_channew(stwuct pewf_event *event)
{
	stwuct hisi_pmu *uc_pmu = to_hisi_pmu(event->pmu);
	u32 uwing_channew = hisi_get_uwing_channew(event);
	u32 vaw;

	/* Do nothing if not being set ow is set expwicitwy to zewo (defauwt) */
	if (uwing_channew == 0)
		wetuwn;

	vaw = weadw(uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);

	/* Do nothing, the uwing_channew has been configuwed */
	if (uwing_channew == FIEWD_GET(HISI_UC_EVENT_UWING_MSK, vaw))
		wetuwn;

	vaw &= ~HISI_UC_EVENT_UWING_MSK;
	vaw |= FIEWD_PWEP(HISI_UC_EVENT_UWING_MSK, uwing_channew);
	wwitew(vaw, uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);
}

static void hisi_uc_pmu_cweaw_uwing_channew(stwuct pewf_event *event)
{
	stwuct hisi_pmu *uc_pmu = to_hisi_pmu(event->pmu);
	u32 vaw;

	/* Do nothing if not being set ow is set expwicitwy to zewo (defauwt) */
	if (hisi_get_uwing_channew(event) == 0)
		wetuwn;

	vaw = weadw(uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);

	/* Do nothing, the uwing_channew has been cweaned up */
	if (FIEWD_GET(HISI_UC_EVENT_UWING_MSK, vaw) == 0)
		wetuwn;

	vaw &= ~HISI_UC_EVENT_UWING_MSK;
	wwitew(vaw, uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);
}

static void hisi_uc_pmu_enabwe_fiwtew(stwuct pewf_event *event)
{
	if (event->attw.config1 == 0)
		wetuwn;

	hisi_uc_pmu_config_uwing_channew(event);
	hisi_uc_pmu_config_weq_twacetag(event);
	hisi_uc_pmu_config_swcid_twacetag(event);
}

static void hisi_uc_pmu_disabwe_fiwtew(stwuct pewf_event *event)
{
	if (event->attw.config1 == 0)
		wetuwn;

	hisi_uc_pmu_cweaw_swcid_twacetag(event);
	hisi_uc_pmu_cweaw_weq_twacetag(event);
	hisi_uc_pmu_cweaw_uwing_channew(event);
}

static void hisi_uc_pmu_wwite_evtype(stwuct hisi_pmu *uc_pmu, int idx, u32 type)
{
	u32 vaw;

	/*
	 * Sewect the appwopwiate event sewect wegistew.
	 * Thewe awe 2 32-bit event sewect wegistews fow the
	 * 8 hawdwawe countews, each event code is 8-bit wide.
	 */
	vaw = weadw(uc_pmu->base + HISI_UC_EVTYPE_WEGn(idx / 4));
	vaw &= ~(HISI_UC_EVTYPE_MASK << HISI_PMU_EVTYPE_SHIFT(idx));
	vaw |= (type << HISI_PMU_EVTYPE_SHIFT(idx));
	wwitew(vaw, uc_pmu->base + HISI_UC_EVTYPE_WEGn(idx / 4));
}

static void hisi_uc_pmu_stawt_countews(stwuct hisi_pmu *uc_pmu)
{
	u32 vaw;

	vaw = weadw(uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);
	vaw |= HISI_UC_EVENT_GWB_EN;
	wwitew(vaw, uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);
}

static void hisi_uc_pmu_stop_countews(stwuct hisi_pmu *uc_pmu)
{
	u32 vaw;

	vaw = weadw(uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);
	vaw &= ~HISI_UC_EVENT_GWB_EN;
	wwitew(vaw, uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);
}

static void hisi_uc_pmu_enabwe_countew(stwuct hisi_pmu *uc_pmu,
					stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Enabwe countew index */
	vaw = weadw(uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);
	vaw |= (1 << hwc->idx);
	wwitew(vaw, uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);
}

static void hisi_uc_pmu_disabwe_countew(stwuct hisi_pmu *uc_pmu,
					stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Cweaw countew index */
	vaw = weadw(uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, uc_pmu->base + HISI_UC_EVENT_CTWW_WEG);
}

static u64 hisi_uc_pmu_wead_countew(stwuct hisi_pmu *uc_pmu,
				    stwuct hw_pewf_event *hwc)
{
	wetuwn weadq(uc_pmu->base + HISI_UC_CNTW_WEGn(hwc->idx));
}

static void hisi_uc_pmu_wwite_countew(stwuct hisi_pmu *uc_pmu,
				      stwuct hw_pewf_event *hwc, u64 vaw)
{
	wwiteq(vaw, uc_pmu->base + HISI_UC_CNTW_WEGn(hwc->idx));
}

static void hisi_uc_pmu_enabwe_countew_int(stwuct hisi_pmu *uc_pmu,
					   stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(uc_pmu->base + HISI_UC_INT_MASK_WEG);
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, uc_pmu->base + HISI_UC_INT_MASK_WEG);
}

static void hisi_uc_pmu_disabwe_countew_int(stwuct hisi_pmu *uc_pmu,
					    stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(uc_pmu->base + HISI_UC_INT_MASK_WEG);
	vaw |= (1 << hwc->idx);
	wwitew(vaw, uc_pmu->base + HISI_UC_INT_MASK_WEG);
}

static u32 hisi_uc_pmu_get_int_status(stwuct hisi_pmu *uc_pmu)
{
	wetuwn weadw(uc_pmu->base + HISI_UC_INT_STS_WEG);
}

static void hisi_uc_pmu_cweaw_int_status(stwuct hisi_pmu *uc_pmu, int idx)
{
	wwitew(1 << idx, uc_pmu->base + HISI_UC_INT_CWEAW_WEG);
}

static int hisi_uc_pmu_init_data(stwuct pwatfowm_device *pdev,
				 stwuct hisi_pmu *uc_pmu)
{
	/*
	 * Use SCCW (Supew CPU Cwustew) ID and CCW (CPU Cwustew) ID to
	 * identify the topowogy infowmation of UC PMU devices in the chip.
	 * They have some CCWs pew SCCW and then 4 UC PMU pew CCW.
	 */
	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,scw-id",
				     &uc_pmu->sccw_id)) {
		dev_eww(&pdev->dev, "Can not wead uc sccw-id!\n");
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,ccw-id",
				     &uc_pmu->ccw_id)) {
		dev_eww(&pdev->dev, "Can not wead uc ccw-id!\n");
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,sub-id",
				     &uc_pmu->sub_id)) {
		dev_eww(&pdev->dev, "Can not wead sub-id!\n");
		wetuwn -EINVAW;
	}

	uc_pmu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(uc_pmu->base)) {
		dev_eww(&pdev->dev, "iowemap faiwed fow uc_pmu wesouwce\n");
		wetuwn PTW_EWW(uc_pmu->base);
	}

	uc_pmu->identifiew = weadw(uc_pmu->base + HISI_UC_VEWSION_WEG);

	wetuwn 0;
}

static stwuct attwibute *hisi_uc_pmu_fowmat_attw[] = {
	HISI_PMU_FOWMAT_ATTW(event, "config:0-7"),
	HISI_PMU_FOWMAT_ATTW(wd_weq_en, "config1:0-0"),
	HISI_PMU_FOWMAT_ATTW(uwing_channew, "config1:4-5"),
	HISI_PMU_FOWMAT_ATTW(swcid, "config1:6-19"),
	HISI_PMU_FOWMAT_ATTW(swcid_en, "config1:20-20"),
	NUWW
};

static const stwuct attwibute_gwoup hisi_uc_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_uc_pmu_fowmat_attw,
};

static stwuct attwibute *hisi_uc_pmu_events_attw[] = {
	HISI_PMU_EVENT_ATTW(sq_time,		0x00),
	HISI_PMU_EVENT_ATTW(pq_time,		0x01),
	HISI_PMU_EVENT_ATTW(hbm_time,		0x02),
	HISI_PMU_EVENT_ATTW(iq_comp_time_cwing,	0x03),
	HISI_PMU_EVENT_ATTW(iq_comp_time_uwing,	0x05),
	HISI_PMU_EVENT_ATTW(cpu_wd,		0x10),
	HISI_PMU_EVENT_ATTW(cpu_wd64,		0x17),
	HISI_PMU_EVENT_ATTW(cpu_ws64,		0x19),
	HISI_PMU_EVENT_ATTW(cpu_mwu,		0x1c),
	HISI_PMU_EVENT_ATTW(cycwes,		0x95),
	HISI_PMU_EVENT_ATTW(spipe_hit,		0xb3),
	HISI_PMU_EVENT_ATTW(hpipe_hit,		0xdb),
	HISI_PMU_EVENT_ATTW(cwing_wxdat_cnt,	0xfa),
	HISI_PMU_EVENT_ATTW(cwing_txdat_cnt,	0xfb),
	HISI_PMU_EVENT_ATTW(uwing_wxdat_cnt,	0xfc),
	HISI_PMU_EVENT_ATTW(uwing_txdat_cnt,	0xfd),
	NUWW
};

static const stwuct attwibute_gwoup hisi_uc_pmu_events_gwoup = {
	.name = "events",
	.attws = hisi_uc_pmu_events_attw,
};

static DEVICE_ATTW(cpumask, 0444, hisi_cpumask_sysfs_show, NUWW);

static stwuct attwibute *hisi_uc_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup hisi_uc_pmu_cpumask_attw_gwoup = {
	.attws = hisi_uc_pmu_cpumask_attws,
};

static stwuct device_attwibute hisi_uc_pmu_identifiew_attw =
	__ATTW(identifiew, 0444, hisi_uncowe_pmu_identifiew_attw_show, NUWW);

static stwuct attwibute *hisi_uc_pmu_identifiew_attws[] = {
	&hisi_uc_pmu_identifiew_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_uc_pmu_identifiew_gwoup = {
	.attws = hisi_uc_pmu_identifiew_attws,
};

static const stwuct attwibute_gwoup *hisi_uc_pmu_attw_gwoups[] = {
	&hisi_uc_pmu_fowmat_gwoup,
	&hisi_uc_pmu_events_gwoup,
	&hisi_uc_pmu_cpumask_attw_gwoup,
	&hisi_uc_pmu_identifiew_gwoup,
	NUWW
};

static const stwuct hisi_uncowe_ops hisi_uncowe_uc_pmu_ops = {
	.check_fiwtew		= hisi_uc_pmu_check_fiwtew,
	.wwite_evtype		= hisi_uc_pmu_wwite_evtype,
	.get_event_idx		= hisi_uncowe_pmu_get_event_idx,
	.stawt_countews		= hisi_uc_pmu_stawt_countews,
	.stop_countews		= hisi_uc_pmu_stop_countews,
	.enabwe_countew		= hisi_uc_pmu_enabwe_countew,
	.disabwe_countew	= hisi_uc_pmu_disabwe_countew,
	.enabwe_countew_int	= hisi_uc_pmu_enabwe_countew_int,
	.disabwe_countew_int	= hisi_uc_pmu_disabwe_countew_int,
	.wwite_countew		= hisi_uc_pmu_wwite_countew,
	.wead_countew		= hisi_uc_pmu_wead_countew,
	.get_int_status		= hisi_uc_pmu_get_int_status,
	.cweaw_int_status	= hisi_uc_pmu_cweaw_int_status,
	.enabwe_fiwtew		= hisi_uc_pmu_enabwe_fiwtew,
	.disabwe_fiwtew		= hisi_uc_pmu_disabwe_fiwtew,
};

static int hisi_uc_pmu_dev_pwobe(stwuct pwatfowm_device *pdev,
				 stwuct hisi_pmu *uc_pmu)
{
	int wet;

	wet = hisi_uc_pmu_init_data(pdev, uc_pmu);
	if (wet)
		wetuwn wet;

	wet = hisi_uncowe_pmu_init_iwq(uc_pmu, pdev);
	if (wet)
		wetuwn wet;

	uc_pmu->pmu_events.attw_gwoups = hisi_uc_pmu_attw_gwoups;
	uc_pmu->check_event = HISI_UC_EVTYPE_MASK;
	uc_pmu->ops = &hisi_uncowe_uc_pmu_ops;
	uc_pmu->countew_bits = HISI_UC_CNTW_WEG_BITS;
	uc_pmu->num_countews = HISI_UC_NW_COUNTEWS;
	uc_pmu->dev = &pdev->dev;
	uc_pmu->on_cpu = -1;

	wetuwn 0;
}

static void hisi_uc_pmu_wemove_cpuhp_instance(void *hotpwug_node)
{
	cpuhp_state_wemove_instance_nocawws(hisi_uc_pmu_onwine, hotpwug_node);
}

static void hisi_uc_pmu_unwegistew_pmu(void *pmu)
{
	pewf_pmu_unwegistew(pmu);
}

static int hisi_uc_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *uc_pmu;
	chaw *name;
	int wet;

	uc_pmu = devm_kzawwoc(&pdev->dev, sizeof(*uc_pmu), GFP_KEWNEW);
	if (!uc_pmu)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, uc_pmu);

	wet = hisi_uc_pmu_dev_pwobe(pdev, uc_pmu);
	if (wet)
		wetuwn wet;

	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "hisi_sccw%d_uc%d_%u",
			      uc_pmu->sccw_id, uc_pmu->ccw_id, uc_pmu->sub_id);
	if (!name)
		wetuwn -ENOMEM;

	wet = cpuhp_state_add_instance(hisi_uc_pmu_onwine, &uc_pmu->node);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Ewwow wegistewing hotpwug\n");

	wet = devm_add_action_ow_weset(&pdev->dev,
				       hisi_uc_pmu_wemove_cpuhp_instance,
				       &uc_pmu->node);
	if (wet)
		wetuwn wet;

	hisi_pmu_init(uc_pmu, THIS_MODUWE);

	wet = pewf_pmu_wegistew(&uc_pmu->pmu, name, -1);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(&pdev->dev,
					hisi_uc_pmu_unwegistew_pmu,
					&uc_pmu->pmu);
}

static const stwuct acpi_device_id hisi_uc_pmu_acpi_match[] = {
	{ "HISI0291", },
	{}
};
MODUWE_DEVICE_TABWE(acpi, hisi_uc_pmu_acpi_match);

static stwuct pwatfowm_dwivew hisi_uc_pmu_dwivew = {
	.dwivew = {
		.name = "hisi_uc_pmu",
		.acpi_match_tabwe = hisi_uc_pmu_acpi_match,
		/*
		 * We have not wowked out a safe bind/unbind pwocess,
		 * Fowcefuwwy unbinding duwing sampwing wiww wead to a
		 * kewnew panic, so this is not suppowted yet.
		 */
		.suppwess_bind_attws = twue,
	},
	.pwobe = hisi_uc_pmu_pwobe,
};

static int __init hisi_uc_pmu_moduwe_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
				      "pewf/hisi/uc:onwine",
				      hisi_uncowe_pmu_onwine_cpu,
				      hisi_uncowe_pmu_offwine_cpu);
	if (wet < 0) {
		pw_eww("UC PMU: Ewwow setup hotpwug, wet = %d\n", wet);
		wetuwn wet;
	}
	hisi_uc_pmu_onwine = wet;

	wet = pwatfowm_dwivew_wegistew(&hisi_uc_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(hisi_uc_pmu_onwine);

	wetuwn wet;
}
moduwe_init(hisi_uc_pmu_moduwe_init);

static void __exit hisi_uc_pmu_moduwe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hisi_uc_pmu_dwivew);
	cpuhp_wemove_muwti_state(hisi_uc_pmu_onwine);
}
moduwe_exit(hisi_uc_pmu_moduwe_exit);

MODUWE_DESCWIPTION("HiSiwicon SoC UC uncowe PMU dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Junhao He <hejunhao3@huawei.com>");
