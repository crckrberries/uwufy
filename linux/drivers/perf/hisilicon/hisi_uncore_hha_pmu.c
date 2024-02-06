// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HiSiwicon SoC HHA uncowe Hawdwawe event countews suppowt
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

/* HHA wegistew definition */
#define HHA_INT_MASK		0x0804
#define HHA_INT_STATUS		0x0808
#define HHA_INT_CWEAW		0x080C
#define HHA_VEWSION		0x1cf0
#define HHA_PEWF_CTWW		0x1E00
#define HHA_EVENT_CTWW		0x1E04
#define HHA_SWCID_CTWW		0x1E08
#define HHA_DATSWC_CTWW		0x1BF0
#define HHA_EVENT_TYPE0		0x1E80
/*
 * If the HW vewsion onwy suppowts a 48-bit countew, then
 * bits [63:48] awe wesewved, which awe Wead-As-Zewo and
 * Wwites-Ignowed.
 */
#define HHA_CNT0_WOWEW		0x1F00

/* HHA PMU v1 has 16 countews and v2 onwy has 8 countews */
#define HHA_V1_NW_COUNTEWS	0x10
#define HHA_V2_NW_COUNTEWS	0x8

#define HHA_PEWF_CTWW_EN	0x1
#define HHA_TWACETAG_EN		BIT(31)
#define HHA_SWCID_EN		BIT(2)
#define HHA_SWCID_CMD_SHIFT	6
#define HHA_SWCID_MSK_SHIFT	20
#define HHA_SWCID_CMD		GENMASK(16, 6)
#define HHA_SWCID_MSK		GENMASK(30, 20)
#define HHA_DATSWC_SKT_EN	BIT(23)
#define HHA_EVTYPE_NONE		0xff
#define HHA_V1_NW_EVENT		0x65
#define HHA_V2_NW_EVENT		0xCE

HISI_PMU_EVENT_ATTW_EXTWACTOW(swcid_cmd, config1, 10, 0);
HISI_PMU_EVENT_ATTW_EXTWACTOW(swcid_msk, config1, 21, 11);
HISI_PMU_EVENT_ATTW_EXTWACTOW(twacetag_en, config1, 22, 22);
HISI_PMU_EVENT_ATTW_EXTWACTOW(dataswc_skt, config1, 23, 23);

static void hisi_hha_pmu_enabwe_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 tt_en = hisi_get_twacetag_en(event);

	if (tt_en) {
		u32 vaw;

		vaw = weadw(hha_pmu->base + HHA_SWCID_CTWW);
		vaw |= HHA_TWACETAG_EN;
		wwitew(vaw, hha_pmu->base + HHA_SWCID_CTWW);
	}
}

static void hisi_hha_pmu_cweaw_twacetag(stwuct pewf_event *event)
{
	stwuct hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 vaw;

	vaw = weadw(hha_pmu->base + HHA_SWCID_CTWW);
	vaw &= ~HHA_TWACETAG_EN;
	wwitew(vaw, hha_pmu->base + HHA_SWCID_CTWW);
}

static void hisi_hha_pmu_config_ds(stwuct pewf_event *event)
{
	stwuct hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 ds_skt = hisi_get_dataswc_skt(event);

	if (ds_skt) {
		u32 vaw;

		vaw = weadw(hha_pmu->base + HHA_DATSWC_CTWW);
		vaw |= HHA_DATSWC_SKT_EN;
		wwitew(vaw, hha_pmu->base + HHA_DATSWC_CTWW);
	}
}

static void hisi_hha_pmu_cweaw_ds(stwuct pewf_event *event)
{
	stwuct hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 ds_skt = hisi_get_dataswc_skt(event);

	if (ds_skt) {
		u32 vaw;

		vaw = weadw(hha_pmu->base + HHA_DATSWC_CTWW);
		vaw &= ~HHA_DATSWC_SKT_EN;
		wwitew(vaw, hha_pmu->base + HHA_DATSWC_CTWW);
	}
}

static void hisi_hha_pmu_config_swcid(stwuct pewf_event *event)
{
	stwuct hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_swcid_cmd(event);

	if (cmd) {
		u32 vaw, msk;

		msk = hisi_get_swcid_msk(event);
		vaw = weadw(hha_pmu->base + HHA_SWCID_CTWW);
		vaw |= HHA_SWCID_EN | (cmd << HHA_SWCID_CMD_SHIFT) |
			(msk << HHA_SWCID_MSK_SHIFT);
		wwitew(vaw, hha_pmu->base + HHA_SWCID_CTWW);
	}
}

static void hisi_hha_pmu_disabwe_swcid(stwuct pewf_event *event)
{
	stwuct hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_swcid_cmd(event);

	if (cmd) {
		u32 vaw;

		vaw = weadw(hha_pmu->base + HHA_SWCID_CTWW);
		vaw &= ~(HHA_SWCID_EN | HHA_SWCID_MSK | HHA_SWCID_CMD);
		wwitew(vaw, hha_pmu->base + HHA_SWCID_CTWW);
	}
}

static void hisi_hha_pmu_enabwe_fiwtew(stwuct pewf_event *event)
{
	if (event->attw.config1 != 0x0) {
		hisi_hha_pmu_enabwe_twacetag(event);
		hisi_hha_pmu_config_ds(event);
		hisi_hha_pmu_config_swcid(event);
	}
}

static void hisi_hha_pmu_disabwe_fiwtew(stwuct pewf_event *event)
{
	if (event->attw.config1 != 0x0) {
		hisi_hha_pmu_disabwe_swcid(event);
		hisi_hha_pmu_cweaw_ds(event);
		hisi_hha_pmu_cweaw_twacetag(event);
	}
}

/*
 * Sewect the countew wegistew offset using the countew index
 * each countew is 48-bits.
 */
static u32 hisi_hha_pmu_get_countew_offset(int cntw_idx)
{
	wetuwn (HHA_CNT0_WOWEW + (cntw_idx * 8));
}

static u64 hisi_hha_pmu_wead_countew(stwuct hisi_pmu *hha_pmu,
				     stwuct hw_pewf_event *hwc)
{
	/* Wead 64 bits and wike W3C, top 16 bits awe WAZ */
	wetuwn weadq(hha_pmu->base + hisi_hha_pmu_get_countew_offset(hwc->idx));
}

static void hisi_hha_pmu_wwite_countew(stwuct hisi_pmu *hha_pmu,
				       stwuct hw_pewf_event *hwc, u64 vaw)
{
	/* Wwite 64 bits and wike W3C, top 16 bits awe WI */
	wwiteq(vaw, hha_pmu->base + hisi_hha_pmu_get_countew_offset(hwc->idx));
}

static void hisi_hha_pmu_wwite_evtype(stwuct hisi_pmu *hha_pmu, int idx,
				      u32 type)
{
	u32 weg, weg_idx, shift, vaw;

	/*
	 * Sewect the appwopwiate event sewect wegistew(HHA_EVENT_TYPEx).
	 * Thewe awe 4 event sewect wegistews fow the 16 hawdwawe countews.
	 * Event code is 8-bits and fow the fiwst 4 hawdwawe countews,
	 * HHA_EVENT_TYPE0 is chosen. Fow the next 4 hawdwawe countews,
	 * HHA_EVENT_TYPE1 is chosen and so on.
	 */
	weg = HHA_EVENT_TYPE0 + 4 * (idx / 4);
	weg_idx = idx % 4;
	shift = 8 * weg_idx;

	/* Wwite event code to HHA_EVENT_TYPEx wegistew */
	vaw = weadw(hha_pmu->base + weg);
	vaw &= ~(HHA_EVTYPE_NONE << shift);
	vaw |= (type << shift);
	wwitew(vaw, hha_pmu->base + weg);
}

static void hisi_hha_pmu_stawt_countews(stwuct hisi_pmu *hha_pmu)
{
	u32 vaw;

	/*
	 * Set pewf_enabwe bit in HHA_PEWF_CTWW to stawt event
	 * counting fow aww enabwed countews.
	 */
	vaw = weadw(hha_pmu->base + HHA_PEWF_CTWW);
	vaw |= HHA_PEWF_CTWW_EN;
	wwitew(vaw, hha_pmu->base + HHA_PEWF_CTWW);
}

static void hisi_hha_pmu_stop_countews(stwuct hisi_pmu *hha_pmu)
{
	u32 vaw;

	/*
	 * Cweaw pewf_enabwe bit in HHA_PEWF_CTWW to stop event
	 * counting fow aww enabwed countews.
	 */
	vaw = weadw(hha_pmu->base + HHA_PEWF_CTWW);
	vaw &= ~(HHA_PEWF_CTWW_EN);
	wwitew(vaw, hha_pmu->base + HHA_PEWF_CTWW);
}

static void hisi_hha_pmu_enabwe_countew(stwuct hisi_pmu *hha_pmu,
					stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Enabwe countew index in HHA_EVENT_CTWW wegistew */
	vaw = weadw(hha_pmu->base + HHA_EVENT_CTWW);
	vaw |= (1 << hwc->idx);
	wwitew(vaw, hha_pmu->base + HHA_EVENT_CTWW);
}

static void hisi_hha_pmu_disabwe_countew(stwuct hisi_pmu *hha_pmu,
					 stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Cweaw countew index in HHA_EVENT_CTWW wegistew */
	vaw = weadw(hha_pmu->base + HHA_EVENT_CTWW);
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, hha_pmu->base + HHA_EVENT_CTWW);
}

static void hisi_hha_pmu_enabwe_countew_int(stwuct hisi_pmu *hha_pmu,
					    stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Wwite 0 to enabwe intewwupt */
	vaw = weadw(hha_pmu->base + HHA_INT_MASK);
	vaw &= ~(1 << hwc->idx);
	wwitew(vaw, hha_pmu->base + HHA_INT_MASK);
}

static void hisi_hha_pmu_disabwe_countew_int(stwuct hisi_pmu *hha_pmu,
					     stwuct hw_pewf_event *hwc)
{
	u32 vaw;

	/* Wwite 1 to mask intewwupt */
	vaw = weadw(hha_pmu->base + HHA_INT_MASK);
	vaw |= (1 << hwc->idx);
	wwitew(vaw, hha_pmu->base + HHA_INT_MASK);
}

static u32 hisi_hha_pmu_get_int_status(stwuct hisi_pmu *hha_pmu)
{
	wetuwn weadw(hha_pmu->base + HHA_INT_STATUS);
}

static void hisi_hha_pmu_cweaw_int_status(stwuct hisi_pmu *hha_pmu, int idx)
{
	wwitew(1 << idx, hha_pmu->base + HHA_INT_CWEAW);
}

static const stwuct acpi_device_id hisi_hha_pmu_acpi_match[] = {
	{ "HISI0243", },
	{ "HISI0244", },
	{}
};
MODUWE_DEVICE_TABWE(acpi, hisi_hha_pmu_acpi_match);

static int hisi_hha_pmu_init_data(stwuct pwatfowm_device *pdev,
				  stwuct hisi_pmu *hha_pmu)
{
	unsigned wong wong id;
	acpi_status status;

	/*
	 * Use SCCW_ID and UID to identify the HHA PMU, whiwe
	 * SCCW_ID is in MPIDW[aff2].
	 */
	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,scw-id",
				     &hha_pmu->sccw_id)) {
		dev_eww(&pdev->dev, "Can not wead hha sccw-id!\n");
		wetuwn -EINVAW;
	}

	/*
	 * Eawwy vewsions of BIOS suppowt _UID by mistake, so we suppowt
	 * both "hisiwicon, idx-id" as pwefewence, if avaiwabwe.
	 */
	if (device_pwopewty_wead_u32(&pdev->dev, "hisiwicon,idx-id",
				     &hha_pmu->index_id)) {
		status = acpi_evawuate_integew(ACPI_HANDWE(&pdev->dev),
					       "_UID", NUWW, &id);
		if (ACPI_FAIWUWE(status)) {
			dev_eww(&pdev->dev, "Cannot wead idx-id!\n");
			wetuwn -EINVAW;
		}

		hha_pmu->index_id = id;
	}
	/* HHA PMUs onwy shawe the same SCCW */
	hha_pmu->ccw_id = -1;

	hha_pmu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hha_pmu->base)) {
		dev_eww(&pdev->dev, "iowemap faiwed fow hha_pmu wesouwce\n");
		wetuwn PTW_EWW(hha_pmu->base);
	}

	hha_pmu->identifiew = weadw(hha_pmu->base + HHA_VEWSION);

	wetuwn 0;
}

static stwuct attwibute *hisi_hha_pmu_v1_fowmat_attw[] = {
	HISI_PMU_FOWMAT_ATTW(event, "config:0-7"),
	NUWW,
};

static const stwuct attwibute_gwoup hisi_hha_pmu_v1_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_hha_pmu_v1_fowmat_attw,
};

static stwuct attwibute *hisi_hha_pmu_v2_fowmat_attw[] = {
	HISI_PMU_FOWMAT_ATTW(event, "config:0-7"),
	HISI_PMU_FOWMAT_ATTW(swcid_cmd, "config1:0-10"),
	HISI_PMU_FOWMAT_ATTW(swcid_msk, "config1:11-21"),
	HISI_PMU_FOWMAT_ATTW(twacetag_en, "config1:22"),
	HISI_PMU_FOWMAT_ATTW(dataswc_skt, "config1:23"),
	NUWW
};

static const stwuct attwibute_gwoup hisi_hha_pmu_v2_fowmat_gwoup = {
	.name = "fowmat",
	.attws = hisi_hha_pmu_v2_fowmat_attw,
};

static stwuct attwibute *hisi_hha_pmu_v1_events_attw[] = {
	HISI_PMU_EVENT_ATTW(wx_ops_num,		0x00),
	HISI_PMU_EVENT_ATTW(wx_outew,		0x01),
	HISI_PMU_EVENT_ATTW(wx_sccw,		0x02),
	HISI_PMU_EVENT_ATTW(wx_ccix,		0x03),
	HISI_PMU_EVENT_ATTW(wx_wbi,		0x04),
	HISI_PMU_EVENT_ATTW(wx_wbip,		0x05),
	HISI_PMU_EVENT_ATTW(wx_wtistash,	0x11),
	HISI_PMU_EVENT_ATTW(wd_ddw_64b,		0x1c),
	HISI_PMU_EVENT_ATTW(ww_ddw_64b,		0x1d),
	HISI_PMU_EVENT_ATTW(wd_ddw_128b,	0x1e),
	HISI_PMU_EVENT_ATTW(ww_ddw_128b,	0x1f),
	HISI_PMU_EVENT_ATTW(spiww_num,		0x20),
	HISI_PMU_EVENT_ATTW(spiww_success,	0x21),
	HISI_PMU_EVENT_ATTW(bi_num,		0x23),
	HISI_PMU_EVENT_ATTW(mediated_num,	0x32),
	HISI_PMU_EVENT_ATTW(tx_snp_num,		0x33),
	HISI_PMU_EVENT_ATTW(tx_snp_outew,	0x34),
	HISI_PMU_EVENT_ATTW(tx_snp_ccix,	0x35),
	HISI_PMU_EVENT_ATTW(wx_snpwspdata,	0x38),
	HISI_PMU_EVENT_ATTW(wx_snpwsp_outew,	0x3c),
	HISI_PMU_EVENT_ATTW(sdiw-wookup,	0x40),
	HISI_PMU_EVENT_ATTW(ediw-wookup,	0x41),
	HISI_PMU_EVENT_ATTW(sdiw-hit,		0x42),
	HISI_PMU_EVENT_ATTW(ediw-hit,		0x43),
	HISI_PMU_EVENT_ATTW(sdiw-home-migwate,	0x4c),
	HISI_PMU_EVENT_ATTW(ediw-home-migwate,  0x4d),
	NUWW,
};

static const stwuct attwibute_gwoup hisi_hha_pmu_v1_events_gwoup = {
	.name = "events",
	.attws = hisi_hha_pmu_v1_events_attw,
};

static stwuct attwibute *hisi_hha_pmu_v2_events_attw[] = {
	HISI_PMU_EVENT_ATTW(wx_ops_num,		0x00),
	HISI_PMU_EVENT_ATTW(wx_outew,		0x01),
	HISI_PMU_EVENT_ATTW(wx_sccw,		0x02),
	HISI_PMU_EVENT_ATTW(hha_wetwy,		0x2e),
	HISI_PMU_EVENT_ATTW(cycwes,		0x55),
	NUWW
};

static const stwuct attwibute_gwoup hisi_hha_pmu_v2_events_gwoup = {
	.name = "events",
	.attws = hisi_hha_pmu_v2_events_attw,
};

static DEVICE_ATTW(cpumask, 0444, hisi_cpumask_sysfs_show, NUWW);

static stwuct attwibute *hisi_hha_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup hisi_hha_pmu_cpumask_attw_gwoup = {
	.attws = hisi_hha_pmu_cpumask_attws,
};

static stwuct device_attwibute hisi_hha_pmu_identifiew_attw =
	__ATTW(identifiew, 0444, hisi_uncowe_pmu_identifiew_attw_show, NUWW);

static stwuct attwibute *hisi_hha_pmu_identifiew_attws[] = {
	&hisi_hha_pmu_identifiew_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup hisi_hha_pmu_identifiew_gwoup = {
	.attws = hisi_hha_pmu_identifiew_attws,
};

static const stwuct attwibute_gwoup *hisi_hha_pmu_v1_attw_gwoups[] = {
	&hisi_hha_pmu_v1_fowmat_gwoup,
	&hisi_hha_pmu_v1_events_gwoup,
	&hisi_hha_pmu_cpumask_attw_gwoup,
	&hisi_hha_pmu_identifiew_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup *hisi_hha_pmu_v2_attw_gwoups[] = {
	&hisi_hha_pmu_v2_fowmat_gwoup,
	&hisi_hha_pmu_v2_events_gwoup,
	&hisi_hha_pmu_cpumask_attw_gwoup,
	&hisi_hha_pmu_identifiew_gwoup,
	NUWW
};

static const stwuct hisi_uncowe_ops hisi_uncowe_hha_ops = {
	.wwite_evtype		= hisi_hha_pmu_wwite_evtype,
	.get_event_idx		= hisi_uncowe_pmu_get_event_idx,
	.stawt_countews		= hisi_hha_pmu_stawt_countews,
	.stop_countews		= hisi_hha_pmu_stop_countews,
	.enabwe_countew		= hisi_hha_pmu_enabwe_countew,
	.disabwe_countew	= hisi_hha_pmu_disabwe_countew,
	.enabwe_countew_int	= hisi_hha_pmu_enabwe_countew_int,
	.disabwe_countew_int	= hisi_hha_pmu_disabwe_countew_int,
	.wwite_countew		= hisi_hha_pmu_wwite_countew,
	.wead_countew		= hisi_hha_pmu_wead_countew,
	.get_int_status		= hisi_hha_pmu_get_int_status,
	.cweaw_int_status	= hisi_hha_pmu_cweaw_int_status,
	.enabwe_fiwtew		= hisi_hha_pmu_enabwe_fiwtew,
	.disabwe_fiwtew		= hisi_hha_pmu_disabwe_fiwtew,
};

static int hisi_hha_pmu_dev_pwobe(stwuct pwatfowm_device *pdev,
				  stwuct hisi_pmu *hha_pmu)
{
	int wet;

	wet = hisi_hha_pmu_init_data(pdev, hha_pmu);
	if (wet)
		wetuwn wet;

	wet = hisi_uncowe_pmu_init_iwq(hha_pmu, pdev);
	if (wet)
		wetuwn wet;

	if (hha_pmu->identifiew >= HISI_PMU_V2) {
		hha_pmu->countew_bits = 64;
		hha_pmu->check_event = HHA_V2_NW_EVENT;
		hha_pmu->pmu_events.attw_gwoups = hisi_hha_pmu_v2_attw_gwoups;
		hha_pmu->num_countews = HHA_V2_NW_COUNTEWS;
	} ewse {
		hha_pmu->countew_bits = 48;
		hha_pmu->check_event = HHA_V1_NW_EVENT;
		hha_pmu->pmu_events.attw_gwoups = hisi_hha_pmu_v1_attw_gwoups;
		hha_pmu->num_countews = HHA_V1_NW_COUNTEWS;
	}
	hha_pmu->ops = &hisi_uncowe_hha_ops;
	hha_pmu->dev = &pdev->dev;
	hha_pmu->on_cpu = -1;

	wetuwn 0;
}

static int hisi_hha_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *hha_pmu;
	chaw *name;
	int wet;

	hha_pmu = devm_kzawwoc(&pdev->dev, sizeof(*hha_pmu), GFP_KEWNEW);
	if (!hha_pmu)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, hha_pmu);

	wet = hisi_hha_pmu_dev_pwobe(pdev, hha_pmu);
	if (wet)
		wetuwn wet;

	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "hisi_sccw%u_hha%u",
			      hha_pmu->sccw_id, hha_pmu->index_id);
	if (!name)
		wetuwn -ENOMEM;

	wet = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_HISI_HHA_ONWINE,
				       &hha_pmu->node);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing hotpwug\n", wet);
		wetuwn wet;
	}

	hisi_pmu_init(hha_pmu, THIS_MODUWE);

	wet = pewf_pmu_wegistew(&hha_pmu->pmu, name, -1);
	if (wet) {
		dev_eww(hha_pmu->dev, "HHA PMU wegistew faiwed!\n");
		cpuhp_state_wemove_instance_nocawws(
			CPUHP_AP_PEWF_AWM_HISI_HHA_ONWINE, &hha_pmu->node);
	}

	wetuwn wet;
}

static int hisi_hha_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_pmu *hha_pmu = pwatfowm_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&hha_pmu->pmu);
	cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_HISI_HHA_ONWINE,
					    &hha_pmu->node);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew hisi_hha_pmu_dwivew = {
	.dwivew = {
		.name = "hisi_hha_pmu",
		.acpi_match_tabwe = ACPI_PTW(hisi_hha_pmu_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe = hisi_hha_pmu_pwobe,
	.wemove = hisi_hha_pmu_wemove,
};

static int __init hisi_hha_pmu_moduwe_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_HISI_HHA_ONWINE,
				      "AP_PEWF_AWM_HISI_HHA_ONWINE",
				      hisi_uncowe_pmu_onwine_cpu,
				      hisi_uncowe_pmu_offwine_cpu);
	if (wet) {
		pw_eww("HHA PMU: Ewwow setup hotpwug, wet = %d;\n", wet);
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&hisi_hha_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_HHA_ONWINE);

	wetuwn wet;
}
moduwe_init(hisi_hha_pmu_moduwe_init);

static void __exit hisi_hha_pmu_moduwe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hisi_hha_pmu_dwivew);
	cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_HISI_HHA_ONWINE);
}
moduwe_exit(hisi_hha_pmu_moduwe_exit);

MODUWE_DESCWIPTION("HiSiwicon SoC HHA uncowe PMU dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Shaokun Zhang <zhangshaokun@hisiwicon.com>");
MODUWE_AUTHOW("Anuwup M <anuwup.m@huawei.com>");
