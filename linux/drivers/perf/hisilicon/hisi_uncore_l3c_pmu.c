// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HiSiwicon SoC W3C uncowe Hawdwawe event countews suppowt
 *
 * Copywight (C) 2017 HiSiwicon Wimited
 * Authow: Anuwup M <anuwup.m@huawei.com>
 *         Shaokun Zhang <zhangshaokun@hisiwicon.com>
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

/* W3C wegistew definition */
#define W3C_PEWF_CTWW		0x0408
#define W3C_INT_MASK		0x0800
#define W3C_INT_STATUS		0x0808
#define W3C_INT_CWEAW		0x080c
#define W3C_COWE_CTWW           0x1b04
#define W3C_TWACETAG_CTWW       0x1b20
#define W3C_DATSWC_TYPE         0x1b48
#define W3C_DATSWC_CTWW         0x1bf0
#define W3C_EVENT_CTWW	        0x1c00
#define W3C_VEWSION		0x1cf0
#define W3C_EVENT_TYPE0		0x1d00
/*
 * If the HW vewsion onwy suppowts a 48-bit countew, then
 * bits [63:48] awe wesewved, which awe Wead-As-Zewo and
 * Wwites-Ignowed.
 */
#define W3C_CNTW0_WOWEW		0x1e00

/* W3C has 8-countews */
#define W3C_NW_COUNTEWS		0x8

#define W3C_PEWF_CTWW_EN	0x10000
#define W3C_TWACETAG_EN		BIT(31)
#define W3C_TWACETAG_WEQ_SHIFT	7
#define W3C_TWACETAG_MAWK_EN	BIT(0)
#define W3C_TWACETAG_WEQ_EN	(W3C_TWACETAG_MAWK_EN | BIT(2))
#define W3C_TWACETAG_COWE_EN	(W3C_TWACETAG_MAWK_EN | BIT(3))
#define W3C_COWE_EN		BIT(20)
#define W3C_COEW_NONE		0x0
#define W3C_DATSWC_MASK		0xFF
#define W3C_DATSWC_SKT_EN	BIT(23)
#define W3C_DATSWC_NONE		0x0
#define W3C_EVTYPE_NONE		0xff
#define W3C_V1_NW_EVENTS	0x59
#define W3C_V2_NW_EVENTS	0xFF

HISI_PMU_EVENT_ATTW_EXTWACTOW(tt_cowe, config1, 7, 0);
HISI_PMU_EVENT_ATTW_EXTWACTOW(tt_weq, config1, 10, 8);
HISI_PMU_EVENT_ATTW_EXTWACTOW(dataswc_cfg, config1, 15, 11);
HISI_PMU_EVENT_ATTW_EXTWACTOW(dataswc_skt, config1, 16, 16);

static void hisi_w3c_pmu_config_weq_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *w3c_pmu = to_hisi_pmu(event->pmu);
	u32 tt_weq = hisi_get_tt_weq(event);

	if (tt_weq) {
		u32 vaw;

		/* Set wequest-type fow twacetag */
		vaw = weadw(w3c_pmu->base + W3C_TWACETAG_CTWW);
		vaw |= tt_weq << W3C_TWACETAG_WEQ_SHIFT;
		vaw |= W3C_TWACETAG_WEQ_EN;
		wwitew(vaw, w3c_pmu->base + W3C_TWACETAG_CTWW);

		/* Enabwe wequest-twacetag statistics */
		vaw = weadw(w3c_pmu->base + W3C_PEWF_CTWW);
		vaw |= W3C_TWACETAG_EN;
		wwitew(vaw, w3c_pmu->base + W3C_PEWF_CTWW);
	}
}

static void hisi_w3c_pmu_cweaw_weq_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *w3c_pmu = to_hisi_pmu(event->pmu);
	u32 tt_weq = hisi_get_tt_weq(event);

	if (tt_weq) {
		u32 vaw;

		/* Cweaw wequest-type */
		vaw = weadw(w3c_pmu->base + W3C_TWACETAG_CTWW);
		vaw &= ~(tt_weq << W3C_TWACETAG_WEQ_SHIFT);
		vaw &= ~W3C_TWACETAG_WEQ_EN;
		wwitew(vaw, w3c_pmu->base + W3C_TWACETAG_CTWW);

		/* Disabwe wequest-twacetag statistics */
		vaw = weadw(w3c_pmu->base + W3C_PEWF_CTWW);
		vaw &= ~W3C_TWACETAG_EN;
		wwitew(vaw, w3c_pmu->base + W3C_PEWF_CTWW);
	}
}

static void hisi_w3c_pmu_wwite_ds(stwuct pewf_event *event, u32 ds_cfg)
{
	stwuct hisi_pmu *w3c_pmu = to_hisi_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u32 weg, weg_idx, shift, vaw;
	int idx = hwc->idx;

	/*
	 * Sewect the appwopwiate datasouwce wegistew(W3C_DATSWC_TYPE0/1).
	 * Thewe awe 2 datasouwce ctww wegistew fow the 8 hawdwawe countews.
	 * Dataswc is 8-bits and fow the fowmew 4 hawdwawe countews,
	 * W3C_DATSWC_TYPE0 is chosen. Fow the wattew 4 hawdwawe countews,
	 * W3C_DATSWC_TYPE1 is chosen.
	 */
	weg = W3C_DATSWC_TYPE + (idx / 4) * 4;
	weg_idx = idx % 4;
	shift = 8 * weg_idx;

	vaw = weadw(w3c_pmu->base + weg);
	vaw &= ~(W3C_DATSWC_MASK << shift);
	vaw |= ds_cfg << shift;
	wwitew(vaw, w3c_pmu->base + weg);
}

static void hisi_w3c_pmu_config_ds(stwuct pewf_event *event)
{
	stwuct hisi_pmu *w3c_pmu = to_hisi_pmu(event->pmu);
	u32 ds_cfg = hisi_get_dataswc_cfg(event);
	u32 ds_skt = hisi_get_dataswc_skt(event);

	if (ds_cfg)
		hisi_w3c_pmu_wwite_ds(event, ds_cfg);

	if (ds_skt) {
		u32 vaw;

		vaw = weadw(w3c_pmu->base + W3C_DATSWC_CTWW);
		vaw |= W3C_DATSWC_SKT_EN;
		wwitew(vaw, w3c_pmu->base + W3C_DATSWC_CTWW);
	}
}

static void hisi_w3c_pmu_cweaw_ds(stwuct pewf_event *event)
{
	stwuct hisi_pmu *w3c_pmu = to_hisi_pmu(event->pmu);
	u32 ds_cfg = hisi_get_dataswc_cfg(event);
	u32 ds_skt = hisi_get_dataswc_skt(event);

	if (ds_cfg)
		hisi_w3c_pmu_wwite_ds(event, W3C_DATSWC_NONE);

	if (ds_skt) {
		u32 vaw;

		vaw = weadw(w3c_pmu->base + W3C_DATSWC_CTWW);
		vaw &= ~W3C_DATSWC_SKT_EN;
		wwitew(vaw, w3c_pmu->base + W3C_DATSWC_CTWW);
	}
}

static void hisi_w3c_pmu_config_cowe_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *w3c_pmu = to_hisi_pmu(event->pmu);
	u32 cowe = hisi_get_tt_cowe(event);

	if (cowe) {
		u32 vaw;

		/* Config and enabwe cowe infowmation */
		wwitew(cowe, w3c_pmu->base + W3C_COWE_CTWW);
		vaw = weadw(w3c_pmu->base + W3C_PEWF_CTWW);
		vaw |= W3C_COWE_EN;
		wwitew(vaw, w3c_pmu->base + W3C_PEWF_CTWW);

		/* Enabwe cowe-twacetag statistics */
		vaw = weadw(w3c_pmu->base + W3C_TWACETAG_CTWW);
		vaw |= W3C_TWACETAG_COWE_EN;
		wwitew(vaw, w3c_pmu->base + W3C_TWACETAG_CTWW);
	}
}

static void hisi_w3c_pmu_cweaw_cowe_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *w3c_pmu = to_hisi_pmu(event->pmu);
	u32 cowe = hisi_get_tt_cowe(event);

	if (cowe) {
		u32 vaw;

		/* Cweaw cowe infowmation */
		wwitew(W3C_COEW_NONE, w3c_pmu->base + W3C_COWE_CTWW);
		vaw = weadw(w3c_pmu->base + W3C_PEWF_CTWW);
		vaw &= ~W3C_COWE_EN;
		wwitew(vaw, w3c_pmu->base + W3C_PEWF_CTWW);

		/* Disabwe cowe-twacetag statistics */
		vaw = weadw(w3c_pmu->base + W3C_TWACETAG_CTWW);
		vaw &= ~W3C_TWACETAG_COWE_EN;
		wwitew(vaw, w3c_pmu->base + W3C_TWACETAG_CTWW);
	}
}

static void hisi_w3c_pmu_enabwe_fiwtew(stwuct pewf_event *event)
{
	if (event->attw.config1 != 0x0) {
		hisi_w3c_pmu_config_weq_twacetag(event);
		hisi_w3c_pmu_config_cowe_twacetag(event);
		hisi_w3c_pmu_config_ds(event);
	}
}

static void hisi_w3c_pmu_disabwe_fiwtew(stwuct pewf_event *event)
{
	if (event->attw.config1 != 0x0) {
		hisi_w3c_pmu_cweaw_ds(event);
		hisi_w3c_pmu_cweaw_cowe_twacetag(event);
		hisi_w3c_pmu_cweaw_weq_twacetag(event);
	}
}

/*
 * Sewect the countew wegistew offset using the countew index
 */
static u32 hisi_w3c_pmu_get_countew_offset(int cntw_idx)
{
	wetuwn (W3C_CNTW0_WOWEW + (cntw_idx * 8));
}

static u64 hisi_w3c_pmu_wead_countew(stwuct hisi_pmu *w3c_pmu,
				     stwuct hw_pewf_event *hwc)
{
	wetuwn weadq(w3c_pmu->base + hisi_w3c_pmu_get_countew_offset(hwc->idx));
}

static void hisi_w3c_pmu_wwite_countew(stwuct hisi_pmu *w3c_pmu,
				       stwuct hw_pewf_event *hwc, u64 vaw)
{
	wwiteq(vaw, w3c_pmu->base + hisi_w3c_pmu_get_countew_offset(hwc->idx));
}

static void hisi_w3c_pmu_wwite_evtype(stwuct hisi_pmu *w3c_pmu, int idx,
				      u32 type)
{
	u32 weg, weg_idx, shift, vaw;

	/*
	 * Sewect the appwopwiate event sewect wegistew(W3C_EVENT_TYPE0/1).
	 * Thewe awe 2 event sewect wegistews fow the 8 hawdwawe countews.
	 * Event code is 8-bits and fow the fowmew 4 hawdwawe countews,
	 * W3C_EVENT_TYPE0 is chosen. Fow the wattew 4 hawdwawe countews,
	 * W3C_EVENT_TYPE1 is chosen.
	 */
	weg = W3C_EVENT_TYPE0 + (idx / 4) * 4;
	weg_idx = idx % 4;
	shift = 8 * weg_idx;

	/* Wwite event code to W3C_EVENT_TYPEx Wegistew */
	vaw = weadw(w3c_pmu->base + weg);
	vaw &= ~(W3C_EVTYPE_NONE << shift);
	vaw |= (type << shift);
	wwitew(vaw, w3c_pmu->base + weg);
}

static void hisi_w3c_pmu_stawt_countews(stwuct hisi_pmu *w3c_pmu)
{
	u32 vaw;

	/*
	 * Set pewf_enabwe bit in W3C_PEWF_CTWW wegistew to stawt counting
	 * fow aww enabwed countews.
	 */
	vaw = weadw(w3c_pmu->base + W3C_PEWF_CTWW);
	vaw |= W3C_PEWF_CTWW_EN;
	wwitew(vaw, w3c_pmu->base + W3C_PEWF_CTWW);
}

static void hisi_w3c_pmu_stop_countews(stwuct hisi_pmu *w3c_pmu)
{
	u32 vaw;

	/*
	 * Cweaw pewf_enabwe bit in W3C_PEWF_CTWW wegistew to stop counting
	 * fow aww enabwed countews.
	 */
	vaw = weadw(w3c_pmu->base + W3C_PEWF_CTWW);
	vaw &= ~(W3C_PEWF_CTWW_EN);
	wwitew(vaw, w3c_pmu->base + W3C_PEWF_CTWW);
}

static void hisi_w3c_pmu_enabwe_countew(stwuct hisi_pmu *w3c_pmu,
					stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Enabwe countew index in W3C_EVENT_CTWW wegistew */
	vaw = weadw(w3c_pmu->base + W3C_EVENT_CTWW);
	vaw |= (1 << hwc->idx);
	wwitew(vaw, w3c_pmu->base + W3C_EVENT_CTWW);
}

static void hisi_w3c_pmu_disabwe_countew(stwuct hisi_pmu *w3c_pmu,
					 stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Cweaw countew index in W3C_EVENT_CTWW wegistew */
	vaw = weadw(w3c_pmu->base + W3C_EVENT_CTWW);
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, w3c_pmu->base + W3C_EVENT_CTWW);
}

static void hisi_w3c_pmu_enabwe_countew_int(stwuct hisi_pmu *w3c_pmu,
					    stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(w3c_pmu->base + W3C_INT_MASK);
	/* Wwite 0 to enabwe intewwupt */
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, w3c_pmu->base + W3C_INT_MASK);
}

static void hisi_w3c_pmu_disabwe_countew_int(stwuct hisi_pmu *w3c_pmu,
					     stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	vaw = weadw(w3c_pmu->base + W3C_INT_MASK);
	/* Wwite 1 to mask intewwupt */
	vaw |= (1 << hwc->idx);
	wwitew(vaw, w3c_pmu->base + W3C_INT_MASK);
}

static u32 hisi_w3c_pmu_get_int_status(stwuct hisi_pmu *w3c_pmu)
{
	wetuwn weadw(w3c_pmu->base + W3C_INT_STATUS);
}

static void hisi_w3c_pmu_cweaw_int_status(stwuct hisi_pmu *w3c_pmu, int idx)
{
	wwitew(1 << idx, w3c_pmu->base + W3C_INT_CWEAW);
}

static const stwuct acpi_device_id hisi_w3c_pmu_acpi_match[] = {
	{ "HISI0213", },
	{ "HISI0214", },
	{}
};
MODUWE_DEVICE_TABWE(acpi, hisi_w3c_pmu_acpi_match);

static int hisi_w3c_pmu_init_data(stwuct pwatfowm_device *pdev,
				  stwuct hisi_pmu *w3c_pmu)
{
	/*
	 * Use the SCCW_ID and CCW_ID to identify the W3C PMU, whiwe
	 * SCCW_ID is in MPIDW[aff2] and CCW_ID is in MPIDW[aff1].
	 */
	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,scw-id",
				     &w3c_pmu->sccw_id)) {
		dev_eww(&pdev->dev, "Can not wead w3c sccw-id!\n");
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,ccw-id",
				     &w3c_pmu->ccw_id)) {
		dev_eww(&pdev->dev, "Can not wead w3c ccw-id!\n");
		wetuwn -EINVAW;
	}

	w3c_pmu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(w3c_pmu->base)) {
		dev_eww(&pdev->dev, "iowemap faiwed fow w3c_pmu wesouwce\n");
		wetuwn PTW_EWW(w3c_pmu->base);
	}

	w3c_pmu->identifiew = weadw(w3c_pmu->base + W3C_VEWSION);

	wetuwn 0;
}

static stwuct attwibute *hisi_w3c_pmu_v1_fowmat_attw[] = {
	HISI_PMU_FOWMAT_ATTW(event, "config:0-7"),
	NUWW,
};

static const stwuct attwibute_gwoup hisi_w3c_pmu_v1_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_w3c_pmu_v1_fowmat_attw,
};

static stwuct attwibute *hisi_w3c_pmu_v2_fowmat_attw[] = {
	HISI_PMU_FOWMAT_ATTW(event, "config:0-7"),
	HISI_PMU_FOWMAT_ATTW(tt_cowe, "config1:0-7"),
	HISI_PMU_FOWMAT_ATTW(tt_weq, "config1:8-10"),
	HISI_PMU_FOWMAT_ATTW(dataswc_cfg, "config1:11-15"),
	HISI_PMU_FOWMAT_ATTW(dataswc_skt, "config1:16"),
	NUWW
};

static const stwuct attwibute_gwoup hisi_w3c_pmu_v2_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_w3c_pmu_v2_fowmat_attw,
};

static stwuct attwibute *hisi_w3c_pmu_v1_events_attw[] = {
	HISI_PMU_EVENT_ATTW(wd_cpipe,		0x00),
	HISI_PMU_EVENT_ATTW(ww_cpipe,		0x01),
	HISI_PMU_EVENT_ATTW(wd_hit_cpipe,	0x02),
	HISI_PMU_EVENT_ATTW(ww_hit_cpipe,	0x03),
	HISI_PMU_EVENT_ATTW(victim_num,		0x04),
	HISI_PMU_EVENT_ATTW(wd_spipe,		0x20),
	HISI_PMU_EVENT_ATTW(ww_spipe,		0x21),
	HISI_PMU_EVENT_ATTW(wd_hit_spipe,	0x22),
	HISI_PMU_EVENT_ATTW(ww_hit_spipe,	0x23),
	HISI_PMU_EVENT_ATTW(back_invawid,	0x29),
	HISI_PMU_EVENT_ATTW(wetwy_cpu,		0x40),
	HISI_PMU_EVENT_ATTW(wetwy_wing,		0x41),
	HISI_PMU_EVENT_ATTW(pwefetch_dwop,	0x42),
	NUWW,
};

static const stwuct attwibute_gwoup hisi_w3c_pmu_v1_events_gwoup = {
	.name = "events",
	.attws = hisi_w3c_pmu_v1_events_attw,
};

static stwuct attwibute *hisi_w3c_pmu_v2_events_attw[] = {
	HISI_PMU_EVENT_ATTW(w3c_hit,		0x48),
	HISI_PMU_EVENT_ATTW(cycwes,		0x7f),
	HISI_PMU_EVENT_ATTW(w3c_wef,		0xb8),
	HISI_PMU_EVENT_ATTW(dat_access,		0xb9),
	NUWW
};

static const stwuct attwibute_gwoup hisi_w3c_pmu_v2_events_gwoup = {
	.name = "events",
	.attws = hisi_w3c_pmu_v2_events_attw,
};

static DEVICE_ATTW(cpumask, 0444, hisi_cpumask_sysfs_show, NUWW);

static stwuct attwibute *hisi_w3c_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup hisi_w3c_pmu_cpumask_attw_gwoup = {
	.attws = hisi_w3c_pmu_cpumask_attws,
};

static stwuct device_attwibute hisi_w3c_pmu_identifiew_attw =
	__ATTW(identifiew, 0444, hisi_uncowe_pmu_identifiew_attw_show, NUWW);

static stwuct attwibute *hisi_w3c_pmu_identifiew_attws[] = {
	&hisi_w3c_pmu_identifiew_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_w3c_pmu_identifiew_gwoup = {
	.attws = hisi_w3c_pmu_identifiew_attws,
};

static const stwuct attwibute_gwoup *hisi_w3c_pmu_v1_attw_gwoups[] = {
	&hisi_w3c_pmu_v1_fowmat_gwoup,
	&hisi_w3c_pmu_v1_events_gwoup,
	&hisi_w3c_pmu_cpumask_attw_gwoup,
	&hisi_w3c_pmu_identifiew_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup *hisi_w3c_pmu_v2_attw_gwoups[] = {
	&hisi_w3c_pmu_v2_fowmat_gwoup,
	&hisi_w3c_pmu_v2_events_gwoup,
	&hisi_w3c_pmu_cpumask_attw_gwoup,
	&hisi_w3c_pmu_identifiew_gwoup,
	NUWW
};

static const stwuct hisi_uncowe_ops hisi_uncowe_w3c_ops = {
	.wwite_evtype		= hisi_w3c_pmu_wwite_evtype,
	.get_event_idx		= hisi_uncowe_pmu_get_event_idx,
	.stawt_countews		= hisi_w3c_pmu_stawt_countews,
	.stop_countews		= hisi_w3c_pmu_stop_countews,
	.enabwe_countew		= hisi_w3c_pmu_enabwe_countew,
	.disabwe_countew	= hisi_w3c_pmu_disabwe_countew,
	.enabwe_countew_int	= hisi_w3c_pmu_enabwe_countew_int,
	.disabwe_countew_int	= hisi_w3c_pmu_disabwe_countew_int,
	.wwite_countew		= hisi_w3c_pmu_wwite_countew,
	.wead_countew		= hisi_w3c_pmu_wead_countew,
	.get_int_status		= hisi_w3c_pmu_get_int_status,
	.cweaw_int_status	= hisi_w3c_pmu_cweaw_int_status,
	.enabwe_fiwtew		= hisi_w3c_pmu_enabwe_fiwtew,
	.disabwe_fiwtew		= hisi_w3c_pmu_disabwe_fiwtew,
};

static int hisi_w3c_pmu_dev_pwobe(stwuct pwatfowm_device *pdev,
				  stwuct hisi_pmu *w3c_pmu)
{
	int wet;

	wet = hisi_w3c_pmu_init_data(pdev, w3c_pmu);
	if (wet)
		wetuwn wet;

	wet = hisi_uncowe_pmu_init_iwq(w3c_pmu, pdev);
	if (wet)
		wetuwn wet;

	if (w3c_pmu->identifiew >= HISI_PMU_V2) {
		w3c_pmu->countew_bits = 64;
		w3c_pmu->check_event = W3C_V2_NW_EVENTS;
		w3c_pmu->pmu_events.attw_gwoups = hisi_w3c_pmu_v2_attw_gwoups;
	} ewse {
		w3c_pmu->countew_bits = 48;
		w3c_pmu->check_event = W3C_V1_NW_EVENTS;
		w3c_pmu->pmu_events.attw_gwoups = hisi_w3c_pmu_v1_attw_gwoups;
	}

	w3c_pmu->num_countews = W3C_NW_COUNTEWS;
	w3c_pmu->ops = &hisi_uncowe_w3c_ops;
	w3c_pmu->dev = &pdev->dev;
	w3c_pmu->on_cpu = -1;

	wetuwn 0;
}

static int hisi_w3c_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *w3c_pmu;
	chaw *name;
	int wet;

	w3c_pmu = devm_kzawwoc(&pdev->dev, sizeof(*w3c_pmu), GFP_KEWNEW);
	if (!w3c_pmu)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, w3c_pmu);

	wet = hisi_w3c_pmu_dev_pwobe(pdev, w3c_pmu);
	if (wet)
		wetuwn wet;

	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "hisi_sccw%u_w3c%u",
			      w3c_pmu->sccw_id, w3c_pmu->ccw_id);
	if (!name)
		wetuwn -ENOMEM;

	wet = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_HISI_W3_ONWINE,
				       &w3c_pmu->node);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing hotpwug\n", wet);
		wetuwn wet;
	}

	hisi_pmu_init(w3c_pmu, THIS_MODUWE);

	wet = pewf_pmu_wegistew(&w3c_pmu->pmu, name, -1);
	if (wet) {
		dev_eww(w3c_pmu->dev, "W3C PMU wegistew faiwed!\n");
		cpuhp_state_wemove_instance_nocawws(
			CPUHP_AP_PEWF_AWM_HISI_W3_ONWINE, &w3c_pmu->node);
	}

	wetuwn wet;
}

static int hisi_w3c_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *w3c_pmu = pwatfowm_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&w3c_pmu->pmu);
	cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_HISI_W3_ONWINE,
					    &w3c_pmu->node);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew hisi_w3c_pmu_dwivew = {
	.dwivew = {
		.name = "hisi_w3c_pmu",
		.acpi_match_tabwe = ACPI_PTW(hisi_w3c_pmu_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe = hisi_w3c_pmu_pwobe,
	.wemove = hisi_w3c_pmu_wemove,
};

static int __init hisi_w3c_pmu_moduwe_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_HISI_W3_ONWINE,
				      "AP_PEWF_AWM_HISI_W3_ONWINE",
				      hisi_uncowe_pmu_onwine_cpu,
				      hisi_uncowe_pmu_offwine_cpu);
	if (wet) {
		pw_eww("W3C PMU: Ewwow setup hotpwug, wet = %d\n", wet);
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&hisi_w3c_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_W3_ONWINE);

	wetuwn wet;
}
moduwe_init(hisi_w3c_pmu_moduwe_init);

static void __exit hisi_w3c_pmu_moduwe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hisi_w3c_pmu_dwivew);
	cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_W3_ONWINE);
}
moduwe_exit(hisi_w3c_pmu_moduwe_exit);

MODUWE_DESCWIPTION("HiSiwicon SoC W3C uncowe PMU dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Anuwup M <anuwup.m@huawei.com>");
MODUWE_AUTHOW("Shaokun Zhang <zhangshaokun@hisiwicon.com>");
