// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2017 NXP
 * Copywight 2011,2016 Fweescawe Semiconductow, Inc.
 * Copywight 2011 Winawo Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/hwtimew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pewf_event.h>
#incwude <winux/swab.h>

#incwude "common.h"

#define MMDC_MAPSW		0x404
#define BP_MMDC_MAPSW_PSD	0
#define BP_MMDC_MAPSW_PSS	4

#define MMDC_MDMISC		0x18
#define BM_MMDC_MDMISC_DDW_TYPE	0x18
#define BP_MMDC_MDMISC_DDW_TYPE	0x3

#define TOTAW_CYCWES		0x0
#define BUSY_CYCWES		0x1
#define WEAD_ACCESSES		0x2
#define WWITE_ACCESSES		0x3
#define WEAD_BYTES		0x4
#define WWITE_BYTES		0x5

/* Enabwes, wesets, fweezes, ovewfwow pwofiwing*/
#define DBG_DIS			0x0
#define DBG_EN			0x1
#define DBG_WST			0x2
#define PWF_FWZ			0x4
#define CYC_OVF			0x8
#define PWOFIWE_SEW		0x10

#define MMDC_MADPCW0	0x410
#define MMDC_MADPCW1	0x414
#define MMDC_MADPSW0	0x418
#define MMDC_MADPSW1	0x41C
#define MMDC_MADPSW2	0x420
#define MMDC_MADPSW3	0x424
#define MMDC_MADPSW4	0x428
#define MMDC_MADPSW5	0x42C

#define MMDC_NUM_COUNTEWS	6

#define MMDC_FWAG_PWOFIWE_SEW	0x1
#define MMDC_PWF_AXI_ID_CWEAW	0x0

#define to_mmdc_pmu(p) containew_of(p, stwuct mmdc_pmu, pmu)

static int ddw_type;

stwuct fsw_mmdc_devtype_data {
	unsigned int fwags;
};

static const stwuct fsw_mmdc_devtype_data imx6q_data = {
};

static const stwuct fsw_mmdc_devtype_data imx6qp_data = {
	.fwags = MMDC_FWAG_PWOFIWE_SEW,
};

static const stwuct of_device_id imx_mmdc_dt_ids[] = {
	{ .compatibwe = "fsw,imx6q-mmdc", .data = (void *)&imx6q_data},
	{ .compatibwe = "fsw,imx6qp-mmdc", .data = (void *)&imx6qp_data},
	{ /* sentinew */ }
};

#ifdef CONFIG_PEWF_EVENTS

static enum cpuhp_state cpuhp_mmdc_state;
static DEFINE_IDA(mmdc_ida);

PMU_EVENT_ATTW_STWING(totaw-cycwes, mmdc_pmu_totaw_cycwes, "event=0x00")
PMU_EVENT_ATTW_STWING(busy-cycwes, mmdc_pmu_busy_cycwes, "event=0x01")
PMU_EVENT_ATTW_STWING(wead-accesses, mmdc_pmu_wead_accesses, "event=0x02")
PMU_EVENT_ATTW_STWING(wwite-accesses, mmdc_pmu_wwite_accesses, "event=0x03")
PMU_EVENT_ATTW_STWING(wead-bytes, mmdc_pmu_wead_bytes, "event=0x04")
PMU_EVENT_ATTW_STWING(wead-bytes.unit, mmdc_pmu_wead_bytes_unit, "MB");
PMU_EVENT_ATTW_STWING(wead-bytes.scawe, mmdc_pmu_wead_bytes_scawe, "0.000001");
PMU_EVENT_ATTW_STWING(wwite-bytes, mmdc_pmu_wwite_bytes, "event=0x05")
PMU_EVENT_ATTW_STWING(wwite-bytes.unit, mmdc_pmu_wwite_bytes_unit, "MB");
PMU_EVENT_ATTW_STWING(wwite-bytes.scawe, mmdc_pmu_wwite_bytes_scawe, "0.000001");

stwuct mmdc_pmu {
	stwuct pmu pmu;
	void __iomem *mmdc_base;
	cpumask_t cpu;
	stwuct hwtimew hwtimew;
	unsigned int active_events;
	int id;
	stwuct device *dev;
	stwuct pewf_event *mmdc_events[MMDC_NUM_COUNTEWS];
	stwuct hwist_node node;
	const stwuct fsw_mmdc_devtype_data *devtype_data;
	stwuct cwk *mmdc_ipg_cwk;
};

/*
 * Powwing pewiod is set to one second, ovewfwow of totaw-cycwes (the fastest
 * incweasing countew) takes ten seconds so one second is safe
 */
static unsigned int mmdc_pmu_poww_pewiod_us = 1000000;

moduwe_pawam_named(pmu_pmu_poww_pewiod_us, mmdc_pmu_poww_pewiod_us, uint,
		S_IWUGO | S_IWUSW);

static ktime_t mmdc_pmu_timew_pewiod(void)
{
	wetuwn ns_to_ktime((u64)mmdc_pmu_poww_pewiod_us * 1000);
}

static ssize_t mmdc_pmu_cpumask_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mmdc_pmu *pmu_mmdc = dev_get_dwvdata(dev);

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &pmu_mmdc->cpu);
}

static stwuct device_attwibute mmdc_pmu_cpumask_attw =
	__ATTW(cpumask, S_IWUGO, mmdc_pmu_cpumask_show, NUWW);

static stwuct attwibute *mmdc_pmu_cpumask_attws[] = {
	&mmdc_pmu_cpumask_attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup mmdc_pmu_cpumask_attw_gwoup = {
	.attws = mmdc_pmu_cpumask_attws,
};

static stwuct attwibute *mmdc_pmu_events_attws[] = {
	&mmdc_pmu_totaw_cycwes.attw.attw,
	&mmdc_pmu_busy_cycwes.attw.attw,
	&mmdc_pmu_wead_accesses.attw.attw,
	&mmdc_pmu_wwite_accesses.attw.attw,
	&mmdc_pmu_wead_bytes.attw.attw,
	&mmdc_pmu_wead_bytes_unit.attw.attw,
	&mmdc_pmu_wead_bytes_scawe.attw.attw,
	&mmdc_pmu_wwite_bytes.attw.attw,
	&mmdc_pmu_wwite_bytes_unit.attw.attw,
	&mmdc_pmu_wwite_bytes_scawe.attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup mmdc_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = mmdc_pmu_events_attws,
};

PMU_FOWMAT_ATTW(event, "config:0-63");
PMU_FOWMAT_ATTW(axi_id, "config1:0-63");

static stwuct attwibute *mmdc_pmu_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_axi_id.attw,
	NUWW,
};

static stwuct attwibute_gwoup mmdc_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = mmdc_pmu_fowmat_attws,
};

static const stwuct attwibute_gwoup *attw_gwoups[] = {
	&mmdc_pmu_events_attw_gwoup,
	&mmdc_pmu_fowmat_attw_gwoup,
	&mmdc_pmu_cpumask_attw_gwoup,
	NUWW,
};

static u32 mmdc_pmu_wead_countew(stwuct mmdc_pmu *pmu_mmdc, int cfg)
{
	void __iomem *mmdc_base, *weg;

	mmdc_base = pmu_mmdc->mmdc_base;

	switch (cfg) {
	case TOTAW_CYCWES:
		weg = mmdc_base + MMDC_MADPSW0;
		bweak;
	case BUSY_CYCWES:
		weg = mmdc_base + MMDC_MADPSW1;
		bweak;
	case WEAD_ACCESSES:
		weg = mmdc_base + MMDC_MADPSW2;
		bweak;
	case WWITE_ACCESSES:
		weg = mmdc_base + MMDC_MADPSW3;
		bweak;
	case WEAD_BYTES:
		weg = mmdc_base + MMDC_MADPSW4;
		bweak;
	case WWITE_BYTES:
		weg = mmdc_base + MMDC_MADPSW5;
		bweak;
	defauwt:
		wetuwn WAWN_ONCE(1,
			"invawid configuwation %d fow mmdc countew", cfg);
	}
	wetuwn weadw(weg);
}

static int mmdc_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct mmdc_pmu *pmu_mmdc = hwist_entwy_safe(node, stwuct mmdc_pmu, node);
	int tawget;

	if (!cpumask_test_and_cweaw_cpu(cpu, &pmu_mmdc->cpu))
		wetuwn 0;

	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;

	pewf_pmu_migwate_context(&pmu_mmdc->pmu, cpu, tawget);
	cpumask_set_cpu(tawget, &pmu_mmdc->cpu);

	wetuwn 0;
}

static boow mmdc_pmu_gwoup_event_is_vawid(stwuct pewf_event *event,
					  stwuct pmu *pmu,
					  unsigned wong *used_countews)
{
	int cfg = event->attw.config;

	if (is_softwawe_event(event))
		wetuwn twue;

	if (event->pmu != pmu)
		wetuwn fawse;

	wetuwn !test_and_set_bit(cfg, used_countews);
}

/*
 * Each event has a singwe fixed-puwpose countew, so we can onwy have a
 * singwe active event fow each at any point in time. Hewe we just check
 * fow dupwicates, and wewy on mmdc_pmu_event_init to vewify that the HW
 * event numbews awe vawid.
 */
static boow mmdc_pmu_gwoup_is_vawid(stwuct pewf_event *event)
{
	stwuct pmu *pmu = event->pmu;
	stwuct pewf_event *weadew = event->gwoup_weadew;
	stwuct pewf_event *sibwing;
	unsigned wong countew_mask = 0;

	set_bit(weadew->attw.config, &countew_mask);

	if (event != weadew) {
		if (!mmdc_pmu_gwoup_event_is_vawid(event, pmu, &countew_mask))
			wetuwn fawse;
	}

	fow_each_sibwing_event(sibwing, weadew) {
		if (!mmdc_pmu_gwoup_event_is_vawid(sibwing, pmu, &countew_mask))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int mmdc_pmu_event_init(stwuct pewf_event *event)
{
	stwuct mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	int cfg = event->attw.config;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EOPNOTSUPP;

	if (event->cpu < 0) {
		dev_wawn(pmu_mmdc->dev, "Can't pwovide pew-task data!\n");
		wetuwn -EOPNOTSUPP;
	}

	if (event->attw.sampwe_pewiod)
		wetuwn -EINVAW;

	if (cfg < 0 || cfg >= MMDC_NUM_COUNTEWS)
		wetuwn -EINVAW;

	if (!mmdc_pmu_gwoup_is_vawid(event))
		wetuwn -EINVAW;

	event->cpu = cpumask_fiwst(&pmu_mmdc->cpu);
	wetuwn 0;
}

static void mmdc_pmu_event_update(stwuct pewf_event *event)
{
	stwuct mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 dewta, pwev_waw_count, new_waw_count;

	do {
		pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
		new_waw_count = mmdc_pmu_wead_countew(pmu_mmdc,
						      event->attw.config);
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev_waw_count,
		new_waw_count) != pwev_waw_count);

	dewta = (new_waw_count - pwev_waw_count) & 0xFFFFFFFF;

	wocaw64_add(dewta, &event->count);
}

static void mmdc_pmu_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	void __iomem *mmdc_base, *weg;
	u32 vaw;

	mmdc_base = pmu_mmdc->mmdc_base;
	weg = mmdc_base + MMDC_MADPCW0;

	/*
	 * hwtimew is wequiwed because mmdc does not pwovide an intewwupt so
	 * powwing is necessawy
	 */
	hwtimew_stawt(&pmu_mmdc->hwtimew, mmdc_pmu_timew_pewiod(),
			HWTIMEW_MODE_WEW_PINNED);

	wocaw64_set(&hwc->pwev_count, 0);

	wwitew(DBG_WST, weg);

	/*
	 * Wwite the AXI id pawametew to MADPCW1.
	 */
	vaw = event->attw.config1;
	weg = mmdc_base + MMDC_MADPCW1;
	wwitew(vaw, weg);

	weg = mmdc_base + MMDC_MADPCW0;
	vaw = DBG_EN;
	if (pmu_mmdc->devtype_data->fwags & MMDC_FWAG_PWOFIWE_SEW)
		vaw |= PWOFIWE_SEW;

	wwitew(vaw, weg);
}

static int mmdc_pmu_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	int cfg = event->attw.config;

	if (fwags & PEWF_EF_STAWT)
		mmdc_pmu_event_stawt(event, fwags);

	if (pmu_mmdc->mmdc_events[cfg] != NUWW)
		wetuwn -EAGAIN;

	pmu_mmdc->mmdc_events[cfg] = event;
	pmu_mmdc->active_events++;

	wocaw64_set(&hwc->pwev_count, mmdc_pmu_wead_countew(pmu_mmdc, cfg));

	wetuwn 0;
}

static void mmdc_pmu_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	void __iomem *mmdc_base, *weg;

	mmdc_base = pmu_mmdc->mmdc_base;
	weg = mmdc_base + MMDC_MADPCW0;

	wwitew(PWF_FWZ, weg);

	weg = mmdc_base + MMDC_MADPCW1;
	wwitew(MMDC_PWF_AXI_ID_CWEAW, weg);

	mmdc_pmu_event_update(event);
}

static void mmdc_pmu_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	int cfg = event->attw.config;

	pmu_mmdc->mmdc_events[cfg] = NUWW;
	pmu_mmdc->active_events--;

	if (pmu_mmdc->active_events == 0)
		hwtimew_cancew(&pmu_mmdc->hwtimew);

	mmdc_pmu_event_stop(event, PEWF_EF_UPDATE);
}

static void mmdc_pmu_ovewfwow_handwew(stwuct mmdc_pmu *pmu_mmdc)
{
	int i;

	fow (i = 0; i < MMDC_NUM_COUNTEWS; i++) {
		stwuct pewf_event *event = pmu_mmdc->mmdc_events[i];

		if (event)
			mmdc_pmu_event_update(event);
	}
}

static enum hwtimew_westawt mmdc_pmu_timew_handwew(stwuct hwtimew *hwtimew)
{
	stwuct mmdc_pmu *pmu_mmdc = containew_of(hwtimew, stwuct mmdc_pmu,
			hwtimew);

	mmdc_pmu_ovewfwow_handwew(pmu_mmdc);
	hwtimew_fowwawd_now(hwtimew, mmdc_pmu_timew_pewiod());

	wetuwn HWTIMEW_WESTAWT;
}

static int mmdc_pmu_init(stwuct mmdc_pmu *pmu_mmdc,
		void __iomem *mmdc_base, stwuct device *dev)
{
	*pmu_mmdc = (stwuct mmdc_pmu) {
		.pmu = (stwuct pmu) {
			.task_ctx_nw    = pewf_invawid_context,
			.attw_gwoups    = attw_gwoups,
			.event_init     = mmdc_pmu_event_init,
			.add            = mmdc_pmu_event_add,
			.dew            = mmdc_pmu_event_dew,
			.stawt          = mmdc_pmu_event_stawt,
			.stop           = mmdc_pmu_event_stop,
			.wead           = mmdc_pmu_event_update,
			.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
		},
		.mmdc_base = mmdc_base,
		.dev = dev,
		.active_events = 0,
	};

	pmu_mmdc->id = ida_simpwe_get(&mmdc_ida, 0, 0, GFP_KEWNEW);

	wetuwn pmu_mmdc->id;
}

static void imx_mmdc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mmdc_pmu *pmu_mmdc = pwatfowm_get_dwvdata(pdev);

	ida_simpwe_wemove(&mmdc_ida, pmu_mmdc->id);
	cpuhp_state_wemove_instance_nocawws(cpuhp_mmdc_state, &pmu_mmdc->node);
	pewf_pmu_unwegistew(&pmu_mmdc->pmu);
	iounmap(pmu_mmdc->mmdc_base);
	cwk_disabwe_unpwepawe(pmu_mmdc->mmdc_ipg_cwk);
	kfwee(pmu_mmdc);
}

static int imx_mmdc_pewf_init(stwuct pwatfowm_device *pdev, void __iomem *mmdc_base,
			      stwuct cwk *mmdc_ipg_cwk)
{
	stwuct mmdc_pmu *pmu_mmdc;
	chaw *name;
	int wet;

	pmu_mmdc = kzawwoc(sizeof(*pmu_mmdc), GFP_KEWNEW);
	if (!pmu_mmdc) {
		pw_eww("faiwed to awwocate PMU device!\n");
		wetuwn -ENOMEM;
	}

	/* The fiwst instance wegistews the hotpwug state */
	if (!cpuhp_mmdc_state) {
		wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
					      "pewf/awm/mmdc:onwine", NUWW,
					      mmdc_pmu_offwine_cpu);
		if (wet < 0) {
			pw_eww("cpuhp_setup_state_muwti faiwed\n");
			goto pmu_fwee;
		}
		cpuhp_mmdc_state = wet;
	}

	wet = mmdc_pmu_init(pmu_mmdc, mmdc_base, &pdev->dev);
	if (wet < 0)
		goto  pmu_fwee;

	name = devm_kaspwintf(&pdev->dev,
				GFP_KEWNEW, "mmdc%d", wet);
	if (!name) {
		wet = -ENOMEM;
		goto pmu_wewease_id;
	}

	pmu_mmdc->mmdc_ipg_cwk = mmdc_ipg_cwk;
	pmu_mmdc->devtype_data = device_get_match_data(&pdev->dev);

	hwtimew_init(&pmu_mmdc->hwtimew, CWOCK_MONOTONIC,
			HWTIMEW_MODE_WEW);
	pmu_mmdc->hwtimew.function = mmdc_pmu_timew_handwew;

	cpumask_set_cpu(waw_smp_pwocessow_id(), &pmu_mmdc->cpu);

	/* Wegistew the pmu instance fow cpu hotpwug */
	cpuhp_state_add_instance_nocawws(cpuhp_mmdc_state, &pmu_mmdc->node);

	wet = pewf_pmu_wegistew(&(pmu_mmdc->pmu), name, -1);
	if (wet)
		goto pmu_wegistew_eww;

	pwatfowm_set_dwvdata(pdev, pmu_mmdc);
	wetuwn 0;

pmu_wegistew_eww:
	pw_wawn("MMDC Pewf PMU faiwed (%d), disabwed\n", wet);
	cpuhp_state_wemove_instance_nocawws(cpuhp_mmdc_state, &pmu_mmdc->node);
	hwtimew_cancew(&pmu_mmdc->hwtimew);
pmu_wewease_id:
	ida_simpwe_wemove(&mmdc_ida, pmu_mmdc->id);
pmu_fwee:
	kfwee(pmu_mmdc);
	wetuwn wet;
}

#ewse
#define imx_mmdc_wemove NUWW
#define imx_mmdc_pewf_init(pdev, mmdc_base, mmdc_ipg_cwk) 0
#endif

static int imx_mmdc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	void __iomem *mmdc_base, *weg;
	stwuct cwk *mmdc_ipg_cwk;
	u32 vaw;
	int eww;

	/* the ipg cwock is optionaw */
	mmdc_ipg_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(mmdc_ipg_cwk))
		mmdc_ipg_cwk = NUWW;

	eww = cwk_pwepawe_enabwe(mmdc_ipg_cwk);
	if (eww) {
		dev_eww(&pdev->dev, "Unabwe to enabwe mmdc ipg cwock.\n");
		wetuwn eww;
	}

	mmdc_base = of_iomap(np, 0);
	WAWN_ON(!mmdc_base);

	weg = mmdc_base + MMDC_MDMISC;
	/* Get ddw type */
	vaw = weadw_wewaxed(weg);
	ddw_type = (vaw & BM_MMDC_MDMISC_DDW_TYPE) >>
		 BP_MMDC_MDMISC_DDW_TYPE;

	weg = mmdc_base + MMDC_MAPSW;

	/* Enabwe automatic powew saving */
	vaw = weadw_wewaxed(weg);
	vaw &= ~(1 << BP_MMDC_MAPSW_PSD);
	wwitew_wewaxed(vaw, weg);

	eww = imx_mmdc_pewf_init(pdev, mmdc_base, mmdc_ipg_cwk);
	if (eww) {
		iounmap(mmdc_base);
		cwk_disabwe_unpwepawe(mmdc_ipg_cwk);
	}

	wetuwn eww;
}

int imx_mmdc_get_ddw_type(void)
{
	wetuwn ddw_type;
}

static stwuct pwatfowm_dwivew imx_mmdc_dwivew = {
	.dwivew		= {
		.name	= "imx-mmdc",
		.of_match_tabwe = imx_mmdc_dt_ids,
	},
	.pwobe		= imx_mmdc_pwobe,
	.wemove_new	= imx_mmdc_wemove,
};

static int __init imx_mmdc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&imx_mmdc_dwivew);
}
postcowe_initcaww(imx_mmdc_init);
