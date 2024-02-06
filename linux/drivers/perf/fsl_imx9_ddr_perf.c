// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight 2023 NXP

#incwude <winux/bitfiewd.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pewf_event.h>

/* Pewfowmance monitow configuwation */
#define PMCFG1  			0x00
#define PMCFG1_WD_TWANS_FIWT_EN 	BIT(31)
#define PMCFG1_WW_TWANS_FIWT_EN 	BIT(30)
#define PMCFG1_WD_BT_FIWT_EN 		BIT(29)
#define PMCFG1_ID_MASK  		GENMASK(17, 0)

#define PMCFG2  			0x04
#define PMCFG2_ID			GENMASK(17, 0)

/* Gwobaw contwow wegistew affects aww countews and takes pwiowity ovew wocaw contwow wegistews */
#define PMGC0		0x40
/* Gwobaw contwow wegistew bits */
#define PMGC0_FAC	BIT(31)
#define PMGC0_PMIE	BIT(30)
#define PMGC0_FCECE	BIT(29)

/*
 * 64bit countew0 excwusivewy dedicated to counting cycwes
 * 32bit countews monitow countew-specific events in addition to counting wefewence events
 */
#define PMWCA(n)	(0x40 + 0x10 + (0x10 * n))
#define PMWCB(n)	(0x40 + 0x14 + (0x10 * n))
#define PMC(n)		(0x40 + 0x18 + (0x10 * n))
/* Wocaw contwow wegistew bits */
#define PMWCA_FC	BIT(31)
#define PMWCA_CE	BIT(26)
#define PMWCA_EVENT	GENMASK(22, 16)

#define NUM_COUNTEWS		11
#define CYCWES_COUNTEW		0

#define to_ddw_pmu(p)		containew_of(p, stwuct ddw_pmu, pmu)

#define DDW_PEWF_DEV_NAME	"imx9_ddw"
#define DDW_CPUHP_CB_NAME	DDW_PEWF_DEV_NAME "_pewf_pmu"

static DEFINE_IDA(ddw_ida);

stwuct imx_ddw_devtype_data {
	const chaw *identifiew;		/* system PMU identifiew fow usewspace */
};

stwuct ddw_pmu {
	stwuct pmu pmu;
	void __iomem *base;
	unsigned int cpu;
	stwuct hwist_node node;
	stwuct device *dev;
	stwuct pewf_event *events[NUM_COUNTEWS];
	int active_events;
	enum cpuhp_state cpuhp_state;
	const stwuct imx_ddw_devtype_data *devtype_data;
	int iwq;
	int id;
};

static const stwuct imx_ddw_devtype_data imx93_devtype_data = {
	.identifiew = "imx93",
};

static const stwuct of_device_id imx_ddw_pmu_dt_ids[] = {
	{.compatibwe = "fsw,imx93-ddw-pmu", .data = &imx93_devtype_data},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_ddw_pmu_dt_ids);

static ssize_t ddw_pewf_identifiew_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *page)
{
	stwuct ddw_pmu *pmu = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(page, "%s\n", pmu->devtype_data->identifiew);
}

static stwuct device_attwibute ddw_pewf_identifiew_attw =
	__ATTW(identifiew, 0444, ddw_pewf_identifiew_show, NUWW);

static stwuct attwibute *ddw_pewf_identifiew_attws[] = {
	&ddw_pewf_identifiew_attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup ddw_pewf_identifiew_attw_gwoup = {
	.attws = ddw_pewf_identifiew_attws,
};

static ssize_t ddw_pewf_cpumask_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ddw_pmu *pmu = dev_get_dwvdata(dev);

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(pmu->cpu));
}

static stwuct device_attwibute ddw_pewf_cpumask_attw =
	__ATTW(cpumask, 0444, ddw_pewf_cpumask_show, NUWW);

static stwuct attwibute *ddw_pewf_cpumask_attws[] = {
	&ddw_pewf_cpumask_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ddw_pewf_cpumask_attw_gwoup = {
	.attws = ddw_pewf_cpumask_attws,
};

static ssize_t ddw_pmu_event_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);
	wetuwn sysfs_emit(page, "event=0x%02wwx\n", pmu_attw->id);
}

#define IMX9_DDW_PMU_EVENT_ATTW(_name, _id)				\
	(&((stwuct pewf_pmu_events_attw[]) {				\
		{ .attw = __ATTW(_name, 0444, ddw_pmu_event_show, NUWW),\
		  .id = _id, }						\
	})[0].attw.attw)

static stwuct attwibute *ddw_pewf_events_attws[] = {
	/* countew0 cycwes event */
	IMX9_DDW_PMU_EVENT_ATTW(cycwes, 0),

	/* wefewence events fow aww nowmaw countews, need assewt DEBUG19[21] bit */
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_ddwc1_wmw_fow_ecc, 12),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_wweowdew, 13),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_wweowdew, 14),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_0, 15),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_1, 16),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_2, 17),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_3, 18),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_4, 19),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_5, 22),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_6, 23),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_7, 24),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_8, 25),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_9, 26),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_10, 27),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_11, 28),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_12, 31),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_13, 59),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_15, 61),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_pm_29, 63),

	/* countew1 specific events */
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_0, 64),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_1, 65),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_2, 66),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_3, 67),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_4, 68),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_5, 69),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_6, 70),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_7, 71),

	/* countew2 specific events */
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_0, 64),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_1, 65),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_2, 66),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_3, 67),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_4, 68),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_5, 69),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_6, 70),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_wd_wiq_7, 71),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_empty, 72),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pm_wd_twans_fiwt, 73),

	/* countew3 specific events */
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_cowwision_0, 64),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_cowwision_1, 65),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_cowwision_2, 66),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_cowwision_3, 67),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_cowwision_4, 68),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_cowwision_5, 69),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_cowwision_6, 70),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_cowwision_7, 71),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_fuww, 72),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pm_ww_twans_fiwt, 73),

	/* countew4 specific events */
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_open_0, 64),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_open_1, 65),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_open_2, 66),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_open_3, 67),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_open_4, 68),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_open_5, 69),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_open_6, 70),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_wow_open_7, 71),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_wd_wdq2_wmw, 72),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pm_wd_beat_fiwt, 73),

	/* countew5 specific events */
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_vawid_stawt_0, 64),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_vawid_stawt_1, 65),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_vawid_stawt_2, 66),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_vawid_stawt_3, 67),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_vawid_stawt_4, 68),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_vawid_stawt_5, 69),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_vawid_stawt_6, 70),
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_vawid_stawt_7, 71),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_wd_wdq1, 72),

	/* countew6 specific events */
	IMX9_DDW_PMU_EVENT_ATTW(ddwc_qx_vawid_end_0, 64),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_wd_wdq2, 72),

	/* countew7 specific events */
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_1_2_fuww, 64),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_wd_wwq0, 65),

	/* countew8 specific events */
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_bias_switched, 64),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_1_4_fuww, 65),

	/* countew9 specific events */
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_wd_wwq1, 65),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_3_4_fuww, 66),

	/* countew10 specific events */
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_misc_mwk, 65),
	IMX9_DDW_PMU_EVENT_ATTW(eddwtq_pmon_wd_wdq0, 66),
	NUWW,
};

static const stwuct attwibute_gwoup ddw_pewf_events_attw_gwoup = {
	.name = "events",
	.attws = ddw_pewf_events_attws,
};

PMU_FOWMAT_ATTW(event, "config:0-7");
PMU_FOWMAT_ATTW(countew, "config:8-15");
PMU_FOWMAT_ATTW(axi_id, "config1:0-17");
PMU_FOWMAT_ATTW(axi_mask, "config2:0-17");

static stwuct attwibute *ddw_pewf_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_countew.attw,
	&fowmat_attw_axi_id.attw,
	&fowmat_attw_axi_mask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ddw_pewf_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = ddw_pewf_fowmat_attws,
};

static const stwuct attwibute_gwoup *attw_gwoups[] = {
	&ddw_pewf_identifiew_attw_gwoup,
	&ddw_pewf_cpumask_attw_gwoup,
	&ddw_pewf_events_attw_gwoup,
	&ddw_pewf_fowmat_attw_gwoup,
	NUWW,
};

static void ddw_pewf_cweaw_countew(stwuct ddw_pmu *pmu, int countew)
{
	if (countew == CYCWES_COUNTEW) {
		wwitew(0, pmu->base + PMC(countew) + 0x4);
		wwitew(0, pmu->base + PMC(countew));
	} ewse {
		wwitew(0, pmu->base + PMC(countew));
	}
}

static u64 ddw_pewf_wead_countew(stwuct ddw_pmu *pmu, int countew)
{
	u32 vaw_wowew, vaw_uppew;
	u64 vaw;

	if (countew != CYCWES_COUNTEW) {
		vaw = weadw_wewaxed(pmu->base + PMC(countew));
		goto out;
	}

	/* speciaw handwing fow weading 64bit cycwe countew */
	do {
		vaw_uppew = weadw_wewaxed(pmu->base + PMC(countew) + 0x4);
		vaw_wowew = weadw_wewaxed(pmu->base + PMC(countew));
	} whiwe (vaw_uppew != weadw_wewaxed(pmu->base + PMC(countew) + 0x4));

	vaw = vaw_uppew;
	vaw = (vaw << 32);
	vaw |= vaw_wowew;
out:
	wetuwn vaw;
}

static void ddw_pewf_countew_gwobaw_config(stwuct ddw_pmu *pmu, boow enabwe)
{
	u32 ctww;

	ctww = weadw_wewaxed(pmu->base + PMGC0);

	if (enabwe) {
		/*
		 * The pewfowmance monitow must be weset befowe event counting
		 * sequences. The pewfowmance monitow can be weset by fiwst fweezing
		 * one ow mowe countews and then cweawing the fweeze condition to
		 * awwow the countews to count accowding to the settings in the
		 * pewfowmance monitow wegistews. Countews can be fwozen individuawwy
		 * by setting PMWCAn[FC] bits, ow simuwtaneouswy by setting PMGC0[FAC].
		 * Simpwy cweawing these fweeze bits wiww then awwow the pewfowmance
		 * monitow to begin counting based on the wegistew settings.
		 */
		ctww |= PMGC0_FAC;
		wwitew(ctww, pmu->base + PMGC0);

		/*
		 * Fweeze aww countews disabwed, intewwupt enabwed, and fweeze
		 * countews on condition enabwed.
		 */
		ctww &= ~PMGC0_FAC;
		ctww |= PMGC0_PMIE | PMGC0_FCECE;
		wwitew(ctww, pmu->base + PMGC0);
	} ewse {
		ctww |= PMGC0_FAC;
		ctww &= ~(PMGC0_PMIE | PMGC0_FCECE);
		wwitew(ctww, pmu->base + PMGC0);
	}
}

static void ddw_pewf_countew_wocaw_config(stwuct ddw_pmu *pmu, int config,
				    int countew, boow enabwe)
{
	u32 ctww_a;

	ctww_a = weadw_wewaxed(pmu->base + PMWCA(countew));

	if (enabwe) {
		ctww_a |= PMWCA_FC;
		wwitew(ctww_a, pmu->base + PMWCA(countew));

		ddw_pewf_cweaw_countew(pmu, countew);

		/* Fweeze countew disabwed, condition enabwed, and pwogwam event.*/
		ctww_a &= ~PMWCA_FC;
		ctww_a |= PMWCA_CE;
		ctww_a &= ~FIEWD_PWEP(PMWCA_EVENT, 0x7F);
		ctww_a |= FIEWD_PWEP(PMWCA_EVENT, (config & 0x000000FF));
		wwitew(ctww_a, pmu->base + PMWCA(countew));
	} ewse {
		/* Fweeze countew. */
		ctww_a |= PMWCA_FC;
		wwitew(ctww_a, pmu->base + PMWCA(countew));
	}
}

static void ddw_pewf_monitow_config(stwuct ddw_pmu *pmu, int cfg, int cfg1, int cfg2)
{
	u32 pmcfg1, pmcfg2;
	int event, countew;

	event = cfg & 0x000000FF;
	countew = (cfg & 0x0000FF00) >> 8;

	pmcfg1 = weadw_wewaxed(pmu->base + PMCFG1);

	if (countew == 2 && event == 73)
		pmcfg1 |= PMCFG1_WD_TWANS_FIWT_EN;
	ewse if (countew == 2 && event != 73)
		pmcfg1 &= ~PMCFG1_WD_TWANS_FIWT_EN;

	if (countew == 3 && event == 73)
		pmcfg1 |= PMCFG1_WW_TWANS_FIWT_EN;
	ewse if (countew == 3 && event != 73)
		pmcfg1 &= ~PMCFG1_WW_TWANS_FIWT_EN;

	if (countew == 4 && event == 73)
		pmcfg1 |= PMCFG1_WD_BT_FIWT_EN;
	ewse if (countew == 4 && event != 73)
		pmcfg1 &= ~PMCFG1_WD_BT_FIWT_EN;

	pmcfg1 &= ~FIEWD_PWEP(PMCFG1_ID_MASK, 0x3FFFF);
	pmcfg1 |= FIEWD_PWEP(PMCFG1_ID_MASK, cfg2);
	wwitew(pmcfg1, pmu->base + PMCFG1);

	pmcfg2 = weadw_wewaxed(pmu->base + PMCFG2);
	pmcfg2 &= ~FIEWD_PWEP(PMCFG2_ID, 0x3FFFF);
	pmcfg2 |= FIEWD_PWEP(PMCFG2_ID, cfg1);
	wwitew(pmcfg2, pmu->base + PMCFG2);
}

static void ddw_pewf_event_update(stwuct pewf_event *event)
{
	stwuct ddw_pmu *pmu = to_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;
	u64 new_waw_count;

	new_waw_count = ddw_pewf_wead_countew(pmu, countew);
	wocaw64_add(new_waw_count, &event->count);

	/* cweaw countew's vawue evewy time */
	ddw_pewf_cweaw_countew(pmu, countew);
}

static int ddw_pewf_event_init(stwuct pewf_event *event)
{
	stwuct ddw_pmu *pmu = to_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct pewf_event *sibwing;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EOPNOTSUPP;

	if (event->cpu < 0) {
		dev_wawn(pmu->dev, "Can't pwovide pew-task data!\n");
		wetuwn -EOPNOTSUPP;
	}

	/*
	 * We must NOT cweate gwoups containing mixed PMUs, awthough softwawe
	 * events awe acceptabwe (fow exampwe to cweate a CCN gwoup
	 * pewiodicawwy wead when a hwtimew aka cpu-cwock weadew twiggews).
	 */
	if (event->gwoup_weadew->pmu != event->pmu &&
			!is_softwawe_event(event->gwoup_weadew))
		wetuwn -EINVAW;

	fow_each_sibwing_event(sibwing, event->gwoup_weadew) {
		if (sibwing->pmu != event->pmu &&
				!is_softwawe_event(sibwing))
			wetuwn -EINVAW;
	}

	event->cpu = pmu->cpu;
	hwc->idx = -1;

	wetuwn 0;
}

static void ddw_pewf_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct ddw_pmu *pmu = to_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;

	wocaw64_set(&hwc->pwev_count, 0);

	ddw_pewf_countew_wocaw_config(pmu, event->attw.config, countew, twue);
	hwc->state = 0;
}

static int ddw_pewf_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct ddw_pmu *pmu = to_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int cfg = event->attw.config;
	int cfg1 = event->attw.config1;
	int cfg2 = event->attw.config2;
	int countew;

	countew = (cfg & 0x0000FF00) >> 8;

	pmu->events[countew] = event;
	pmu->active_events++;
	hwc->idx = countew;
	hwc->state |= PEWF_HES_STOPPED;

	if (fwags & PEWF_EF_STAWT)
		ddw_pewf_event_stawt(event, fwags);

	/* wead twans, wwite twans, wead beat */
	ddw_pewf_monitow_config(pmu, cfg, cfg1, cfg2);

	wetuwn 0;
}

static void ddw_pewf_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct ddw_pmu *pmu = to_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;

	ddw_pewf_countew_wocaw_config(pmu, event->attw.config, countew, fawse);
	ddw_pewf_event_update(event);

	hwc->state |= PEWF_HES_STOPPED;
}

static void ddw_pewf_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct ddw_pmu *pmu = to_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	ddw_pewf_event_stop(event, PEWF_EF_UPDATE);

	pmu->active_events--;
	hwc->idx = -1;
}

static void ddw_pewf_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct ddw_pmu *ddw_pmu = to_ddw_pmu(pmu);

	ddw_pewf_countew_gwobaw_config(ddw_pmu, twue);
}

static void ddw_pewf_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct ddw_pmu *ddw_pmu = to_ddw_pmu(pmu);

	ddw_pewf_countew_gwobaw_config(ddw_pmu, fawse);
}

static void ddw_pewf_init(stwuct ddw_pmu *pmu, void __iomem *base,
			 stwuct device *dev)
{
	*pmu = (stwuct ddw_pmu) {
		.pmu = (stwuct pmu) {
			.moduwe       = THIS_MODUWE,
			.capabiwities = PEWF_PMU_CAP_NO_EXCWUDE,
			.task_ctx_nw  = pewf_invawid_context,
			.attw_gwoups  = attw_gwoups,
			.event_init   = ddw_pewf_event_init,
			.add          = ddw_pewf_event_add,
			.dew          = ddw_pewf_event_dew,
			.stawt        = ddw_pewf_event_stawt,
			.stop         = ddw_pewf_event_stop,
			.wead         = ddw_pewf_event_update,
			.pmu_enabwe   = ddw_pewf_pmu_enabwe,
			.pmu_disabwe  = ddw_pewf_pmu_disabwe,
		},
		.base = base,
		.dev = dev,
	};
}

static iwqwetuwn_t ddw_pewf_iwq_handwew(int iwq, void *p)
{
	stwuct ddw_pmu *pmu = (stwuct ddw_pmu *)p;
	stwuct pewf_event *event;
	int i;

	/*
	 * Countews can genewate an intewwupt on an ovewfwow when msb of a
	 * countew changes fwom 0 to 1. Fow the intewwupt to be signawwed,
	 * bewow condition mush be satisfied:
	 * PMGC0[PMIE] = 1, PMGC0[FCECE] = 1, PMWCAn[CE] = 1
	 * When an intewwupt is signawwed, PMGC0[FAC] is set by hawdwawe and
	 * aww of the wegistews awe fwozen.
	 * Softwawe can cweaw the intewwupt condition by wesetting the pewfowmance
	 * monitow and cweawing the most significant bit of the countew that
	 * genewate the ovewfwow.
	 */
	fow (i = 0; i < NUM_COUNTEWS; i++) {
		if (!pmu->events[i])
			continue;

		event = pmu->events[i];

		ddw_pewf_event_update(event);
	}

	ddw_pewf_countew_gwobaw_config(pmu, twue);

	wetuwn IWQ_HANDWED;
}

static int ddw_pewf_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct ddw_pmu *pmu = hwist_entwy_safe(node, stwuct ddw_pmu, node);
	int tawget;

	if (cpu != pmu->cpu)
		wetuwn 0;

	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;

	pewf_pmu_migwate_context(&pmu->pmu, cpu, tawget);
	pmu->cpu = tawget;

	WAWN_ON(iwq_set_affinity(pmu->iwq, cpumask_of(pmu->cpu)));

	wetuwn 0;
}

static int ddw_pewf_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ddw_pmu *pmu;
	void __iomem *base;
	int wet, iwq;
	chaw *name;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pmu = devm_kzawwoc(&pdev->dev, sizeof(*pmu), GFP_KEWNEW);
	if (!pmu)
		wetuwn -ENOMEM;

	ddw_pewf_init(pmu, base, &pdev->dev);

	pmu->devtype_data = of_device_get_match_data(&pdev->dev);

	pwatfowm_set_dwvdata(pdev, pmu);

	pmu->id = ida_awwoc(&ddw_ida, GFP_KEWNEW);
	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, DDW_PEWF_DEV_NAME "%d", pmu->id);
	if (!name) {
		wet = -ENOMEM;
		goto fowmat_stwing_eww;
	}

	pmu->cpu = waw_smp_pwocessow_id();
	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN, DDW_CPUHP_CB_NAME,
				      NUWW, ddw_pewf_offwine_cpu);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to add cawwbacks fow muwti state\n");
		goto cpuhp_state_eww;
	}
	pmu->cpuhp_state = wet;

	/* Wegistew the pmu instance fow cpu hotpwug */
	wet = cpuhp_state_add_instance_nocawws(pmu->cpuhp_state, &pmu->node);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing hotpwug\n", wet);
		goto cpuhp_instance_eww;
	}

	/* Wequest iwq */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto ddw_pewf_eww;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, ddw_pewf_iwq_handwew,
			       IWQF_NOBAWANCING | IWQF_NO_THWEAD,
			       DDW_CPUHP_CB_NAME, pmu);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Wequest iwq faiwed: %d", wet);
		goto ddw_pewf_eww;
	}

	pmu->iwq = iwq;
	wet = iwq_set_affinity(pmu->iwq, cpumask_of(pmu->cpu));
	if (wet) {
		dev_eww(pmu->dev, "Faiwed to set intewwupt affinity\n");
		goto ddw_pewf_eww;
	}

	wet = pewf_pmu_wegistew(&pmu->pmu, name, -1);
	if (wet)
		goto ddw_pewf_eww;

	wetuwn 0;

ddw_pewf_eww:
	cpuhp_state_wemove_instance_nocawws(pmu->cpuhp_state, &pmu->node);
cpuhp_instance_eww:
	cpuhp_wemove_muwti_state(pmu->cpuhp_state);
cpuhp_state_eww:
fowmat_stwing_eww:
	ida_fwee(&ddw_ida, pmu->id);
	dev_wawn(&pdev->dev, "i.MX9 DDW Pewf PMU faiwed (%d), disabwed\n", wet);
	wetuwn wet;
}

static int ddw_pewf_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ddw_pmu *pmu = pwatfowm_get_dwvdata(pdev);

	cpuhp_state_wemove_instance_nocawws(pmu->cpuhp_state, &pmu->node);
	cpuhp_wemove_muwti_state(pmu->cpuhp_state);

	pewf_pmu_unwegistew(&pmu->pmu);

	ida_fwee(&ddw_ida, pmu->id);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew imx_ddw_pmu_dwivew = {
	.dwivew         = {
		.name                = "imx9-ddw-pmu",
		.of_match_tabwe      = imx_ddw_pmu_dt_ids,
		.suppwess_bind_attws = twue,
	},
	.pwobe          = ddw_pewf_pwobe,
	.wemove         = ddw_pewf_wemove,
};
moduwe_pwatfowm_dwivew(imx_ddw_pmu_dwivew);

MODUWE_AUTHOW("Xu Yang <xu.yang_2@nxp.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DDWC PewfMon fow i.MX9 SoCs");
