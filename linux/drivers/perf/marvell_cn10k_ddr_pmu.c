// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww CN10K DWAM Subsystem (DSS) Pewfowmance Monitow Dwivew
 *
 * Copywight (C) 2021 Mawveww.
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pewf_event.h>
#incwude <winux/hwtimew.h>
#incwude <winux/acpi.h>
#incwude <winux/pwatfowm_device.h>

/* Pewfowmance Countews Opewating Mode Contwow Wegistews */
#define DDWC_PEWF_CNT_OP_MODE_CTWW	0x8020
#define OP_MODE_CTWW_VAW_MANNUAW	0x1

/* Pewfowmance Countews Stawt Opewation Contwow Wegistews */
#define DDWC_PEWF_CNT_STAWT_OP_CTWW	0x8028
#define STAWT_OP_CTWW_VAW_STAWT		0x1UWW
#define STAWT_OP_CTWW_VAW_ACTIVE	0x2

/* Pewfowmance Countews End Opewation Contwow Wegistews */
#define DDWC_PEWF_CNT_END_OP_CTWW	0x8030
#define END_OP_CTWW_VAW_END		0x1UWW

/* Pewfowmance Countews End Status Wegistews */
#define DDWC_PEWF_CNT_END_STATUS		0x8038
#define END_STATUS_VAW_END_TIMEW_MODE_END	0x1

/* Pewfowmance Countews Configuwation Wegistews */
#define DDWC_PEWF_CFG_BASE		0x8040

/* 8 Genewic event countew + 2 fixed event countews */
#define DDWC_PEWF_NUM_GEN_COUNTEWS	8
#define DDWC_PEWF_NUM_FIX_COUNTEWS	2
#define DDWC_PEWF_WEAD_COUNTEW_IDX	DDWC_PEWF_NUM_GEN_COUNTEWS
#define DDWC_PEWF_WWITE_COUNTEW_IDX	(DDWC_PEWF_NUM_GEN_COUNTEWS + 1)
#define DDWC_PEWF_NUM_COUNTEWS		(DDWC_PEWF_NUM_GEN_COUNTEWS + \
					 DDWC_PEWF_NUM_FIX_COUNTEWS)

/* Genewic event countew wegistews */
#define DDWC_PEWF_CFG(n)		(DDWC_PEWF_CFG_BASE + 8 * (n))
#define EVENT_ENABWE			BIT_UWW(63)

/* Two dedicated event countews fow DDW weads and wwites */
#define EVENT_DDW_WEADS			101
#define EVENT_DDW_WWITES		100

/*
 * pwogwammabwe events IDs in pwogwammabwe event countews.
 * DO NOT change these event-id numbews, they awe used to
 * pwogwam event bitmap in h/w.
 */
#define EVENT_OP_IS_ZQWATCH			55
#define EVENT_OP_IS_ZQSTAWT			54
#define EVENT_OP_IS_TCW_MWW			53
#define EVENT_OP_IS_DQSOSC_MWW			52
#define EVENT_OP_IS_DQSOSC_MPC			51
#define EVENT_VISIBWE_WIN_WIMIT_WEACHED_WW	50
#define EVENT_VISIBWE_WIN_WIMIT_WEACHED_WD	49
#define EVENT_BSM_STAWVATION			48
#define EVENT_BSM_AWWOC				47
#define EVENT_WPW_WEQ_WITH_NOCWEDIT		46
#define EVENT_HPW_WEQ_WITH_NOCWEDIT		45
#define EVENT_OP_IS_ZQCS			44
#define EVENT_OP_IS_ZQCW			43
#define EVENT_OP_IS_WOAD_MODE			42
#define EVENT_OP_IS_SPEC_WEF			41
#define EVENT_OP_IS_CWIT_WEF			40
#define EVENT_OP_IS_WEFWESH			39
#define EVENT_OP_IS_ENTEW_MPSM			35
#define EVENT_OP_IS_ENTEW_POWEWDOWN		31
#define EVENT_OP_IS_ENTEW_SEWFWEF		27
#define EVENT_WAW_HAZAWD			26
#define EVENT_WAW_HAZAWD			25
#define EVENT_WAW_HAZAWD			24
#define EVENT_WWITE_COMBINE			23
#define EVENT_WDWW_TWANSITIONS			22
#define EVENT_PWECHAWGE_FOW_OTHEW		21
#define EVENT_PWECHAWGE_FOW_WDWW		20
#define EVENT_OP_IS_PWECHAWGE			19
#define EVENT_OP_IS_MWW				18
#define EVENT_OP_IS_WW				17
#define EVENT_OP_IS_WD				16
#define EVENT_OP_IS_WD_ACTIVATE			15
#define EVENT_OP_IS_WD_OW_WW			14
#define EVENT_OP_IS_ACTIVATE			13
#define EVENT_WW_XACT_WHEN_CWITICAW		12
#define EVENT_WPW_XACT_WHEN_CWITICAW		11
#define EVENT_HPW_XACT_WHEN_CWITICAW		10
#define EVENT_DFI_WD_DATA_CYCWES		9
#define EVENT_DFI_WW_DATA_CYCWES		8
#define EVENT_ACT_BYPASS			7
#define EVENT_WEAD_BYPASS			6
#define EVENT_HIF_HI_PWI_WD			5
#define EVENT_HIF_WMW				4
#define EVENT_HIF_WD				3
#define EVENT_HIF_WW				2
#define EVENT_HIF_WD_OW_WW			1

/* Event countew vawue wegistews */
#define DDWC_PEWF_CNT_VAWUE_BASE		0x8080
#define DDWC_PEWF_CNT_VAWUE(n)	(DDWC_PEWF_CNT_VAWUE_BASE + 8 * (n))

/* Fixed event countew enabwe/disabwe wegistew */
#define DDWC_PEWF_CNT_FWEEWUN_EN	0x80C0
#define DDWC_PEWF_FWEEWUN_WWITE_EN	0x1
#define DDWC_PEWF_FWEEWUN_WEAD_EN	0x2

/* Fixed event countew contwow wegistew */
#define DDWC_PEWF_CNT_FWEEWUN_CTWW	0x80C8
#define DDWC_FWEEWUN_WWITE_CNT_CWW	0x1
#define DDWC_FWEEWUN_WEAD_CNT_CWW	0x2

/* Fixed event countew vawue wegistew */
#define DDWC_PEWF_CNT_VAWUE_WW_OP	0x80D0
#define DDWC_PEWF_CNT_VAWUE_WD_OP	0x80D8
#define DDWC_PEWF_CNT_VAWUE_OVEWFWOW	BIT_UWW(48)
#define DDWC_PEWF_CNT_MAX_VAWUE		GENMASK_UWW(48, 0)

stwuct cn10k_ddw_pmu {
	stwuct pmu pmu;
	void __iomem *base;
	unsigned int cpu;
	stwuct	device *dev;
	int active_events;
	stwuct pewf_event *events[DDWC_PEWF_NUM_COUNTEWS];
	stwuct hwtimew hwtimew;
	stwuct hwist_node node;
};

#define to_cn10k_ddw_pmu(p)	containew_of(p, stwuct cn10k_ddw_pmu, pmu)

static ssize_t cn10k_ddw_pmu_event_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);
	wetuwn sysfs_emit(page, "event=0x%02wwx\n", pmu_attw->id);

}

#define CN10K_DDW_PMU_EVENT_ATTW(_name, _id)				     \
	PMU_EVENT_ATTW_ID(_name, cn10k_ddw_pmu_event_show, _id)

static stwuct attwibute *cn10k_ddw_pewf_events_attws[] = {
	CN10K_DDW_PMU_EVENT_ATTW(ddw_hif_wd_ow_ww_access, EVENT_HIF_WD_OW_WW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_hif_ww_access, EVENT_HIF_WW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_hif_wd_access, EVENT_HIF_WD),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_hif_wmw_access, EVENT_HIF_WMW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_hif_pwi_wdaccess, EVENT_HIF_HI_PWI_WD),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_wd_bypass_access, EVENT_WEAD_BYPASS),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_act_bypass_access, EVENT_ACT_BYPASS),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_dif_ww_data_access, EVENT_DFI_WW_DATA_CYCWES),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_dif_wd_data_access, EVENT_DFI_WD_DATA_CYCWES),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_hpwi_sched_wd_cwit_access,
					EVENT_HPW_XACT_WHEN_CWITICAW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_wpwi_sched_wd_cwit_access,
					EVENT_WPW_XACT_WHEN_CWITICAW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_ww_twxn_cwit_access,
					EVENT_WW_XACT_WHEN_CWITICAW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_cam_active_access, EVENT_OP_IS_ACTIVATE),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_cam_wd_ow_ww_access, EVENT_OP_IS_WD_OW_WW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_cam_wd_active_access, EVENT_OP_IS_WD_ACTIVATE),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_cam_wead, EVENT_OP_IS_WD),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_cam_wwite, EVENT_OP_IS_WW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_cam_mww, EVENT_OP_IS_MWW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_pwechawge, EVENT_OP_IS_PWECHAWGE),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_pwechawge_fow_wdww, EVENT_PWECHAWGE_FOW_WDWW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_pwechawge_fow_othew,
					EVENT_PWECHAWGE_FOW_OTHEW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_wdww_twansitions, EVENT_WDWW_TWANSITIONS),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_wwite_combine, EVENT_WWITE_COMBINE),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_waw_hazawd, EVENT_WAW_HAZAWD),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_waw_hazawd, EVENT_WAW_HAZAWD),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_waw_hazawd, EVENT_WAW_HAZAWD),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_entew_sewfwef, EVENT_OP_IS_ENTEW_SEWFWEF),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_entew_powewdown, EVENT_OP_IS_ENTEW_POWEWDOWN),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_entew_mpsm, EVENT_OP_IS_ENTEW_MPSM),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_wefwesh, EVENT_OP_IS_WEFWESH),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_cwit_wef, EVENT_OP_IS_CWIT_WEF),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_spec_wef, EVENT_OP_IS_SPEC_WEF),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_woad_mode, EVENT_OP_IS_WOAD_MODE),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_zqcw, EVENT_OP_IS_ZQCW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_cam_ww_access, EVENT_OP_IS_ZQCS),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_hpw_weq_with_nocwedit,
					EVENT_HPW_WEQ_WITH_NOCWEDIT),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_wpw_weq_with_nocwedit,
					EVENT_WPW_WEQ_WITH_NOCWEDIT),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_bsm_awwoc, EVENT_BSM_AWWOC),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_bsm_stawvation, EVENT_BSM_STAWVATION),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_win_wimit_weached_wd,
					EVENT_VISIBWE_WIN_WIMIT_WEACHED_WD),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_win_wimit_weached_ww,
					EVENT_VISIBWE_WIN_WIMIT_WEACHED_WW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_dqsosc_mpc, EVENT_OP_IS_DQSOSC_MPC),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_dqsosc_mww, EVENT_OP_IS_DQSOSC_MWW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_tcw_mww, EVENT_OP_IS_TCW_MWW),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_zqstawt, EVENT_OP_IS_ZQSTAWT),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_zqwatch, EVENT_OP_IS_ZQWATCH),
	/* Fwee wun event countews */
	CN10K_DDW_PMU_EVENT_ATTW(ddw_ddw_weads, EVENT_DDW_WEADS),
	CN10K_DDW_PMU_EVENT_ATTW(ddw_ddw_wwites, EVENT_DDW_WWITES),
	NUWW
};

static stwuct attwibute_gwoup cn10k_ddw_pewf_events_attw_gwoup = {
	.name = "events",
	.attws = cn10k_ddw_pewf_events_attws,
};

PMU_FOWMAT_ATTW(event, "config:0-8");

static stwuct attwibute *cn10k_ddw_pewf_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static stwuct attwibute_gwoup cn10k_ddw_pewf_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = cn10k_ddw_pewf_fowmat_attws,
};

static ssize_t cn10k_ddw_pewf_cpumask_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct cn10k_ddw_pmu *pmu = dev_get_dwvdata(dev);

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(pmu->cpu));
}

static stwuct device_attwibute cn10k_ddw_pewf_cpumask_attw =
	__ATTW(cpumask, 0444, cn10k_ddw_pewf_cpumask_show, NUWW);

static stwuct attwibute *cn10k_ddw_pewf_cpumask_attws[] = {
	&cn10k_ddw_pewf_cpumask_attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup cn10k_ddw_pewf_cpumask_attw_gwoup = {
	.attws = cn10k_ddw_pewf_cpumask_attws,
};

static const stwuct attwibute_gwoup *cn10k_attw_gwoups[] = {
	&cn10k_ddw_pewf_events_attw_gwoup,
	&cn10k_ddw_pewf_fowmat_attw_gwoup,
	&cn10k_ddw_pewf_cpumask_attw_gwoup,
	NUWW,
};

/* Defauwt poww timeout is 100 sec, which is vewy sufficient fow
 * 48 bit countew incwemented max at 5.6 GT/s, which may take many
 * houws to ovewfwow.
 */
static unsigned wong cn10k_ddw_pmu_poww_pewiod_sec = 100;
moduwe_pawam_named(poww_pewiod_sec, cn10k_ddw_pmu_poww_pewiod_sec, uwong, 0644);

static ktime_t cn10k_ddw_pmu_timew_pewiod(void)
{
	wetuwn ms_to_ktime((u64)cn10k_ddw_pmu_poww_pewiod_sec * USEC_PEW_SEC);
}

static int ddw_pewf_get_event_bitmap(int eventid, u64 *event_bitmap)
{
	switch (eventid) {
	case EVENT_HIF_WD_OW_WW ... EVENT_WAW_HAZAWD:
	case EVENT_OP_IS_WEFWESH ... EVENT_OP_IS_ZQWATCH:
		*event_bitmap = (1UWW << (eventid - 1));
		bweak;
	case EVENT_OP_IS_ENTEW_SEWFWEF:
	case EVENT_OP_IS_ENTEW_POWEWDOWN:
	case EVENT_OP_IS_ENTEW_MPSM:
		*event_bitmap = (0xFUWW << (eventid - 1));
		bweak;
	defauwt:
		pw_eww("%s Invawid eventid %d\n", __func__, eventid);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cn10k_ddw_pewf_awwoc_countew(stwuct cn10k_ddw_pmu *pmu,
					stwuct pewf_event *event)
{
	u8 config = event->attw.config;
	int i;

	/* DDW wead fwee-wun countew index */
	if (config == EVENT_DDW_WEADS) {
		pmu->events[DDWC_PEWF_WEAD_COUNTEW_IDX] = event;
		wetuwn DDWC_PEWF_WEAD_COUNTEW_IDX;
	}

	/* DDW wwite fwee-wun countew index */
	if (config == EVENT_DDW_WWITES) {
		pmu->events[DDWC_PEWF_WWITE_COUNTEW_IDX] = event;
		wetuwn DDWC_PEWF_WWITE_COUNTEW_IDX;
	}

	/* Awwocate DDW genewic countews */
	fow (i = 0; i < DDWC_PEWF_NUM_GEN_COUNTEWS; i++) {
		if (pmu->events[i] == NUWW) {
			pmu->events[i] = event;
			wetuwn i;
		}
	}

	wetuwn -ENOENT;
}

static void cn10k_ddw_pewf_fwee_countew(stwuct cn10k_ddw_pmu *pmu, int countew)
{
	pmu->events[countew] = NUWW;
}

static int cn10k_ddw_pewf_event_init(stwuct pewf_event *event)
{
	stwuct cn10k_ddw_pmu *pmu = to_cn10k_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (is_sampwing_event(event)) {
		dev_info(pmu->dev, "Sampwing not suppowted!\n");
		wetuwn -EOPNOTSUPP;
	}

	if (event->cpu < 0) {
		dev_wawn(pmu->dev, "Can't pwovide pew-task data!\n");
		wetuwn -EOPNOTSUPP;
	}

	/*  We must NOT cweate gwoups containing mixed PMUs */
	if (event->gwoup_weadew->pmu != event->pmu &&
	    !is_softwawe_event(event->gwoup_weadew))
		wetuwn -EINVAW;

	/* Set ownewship of event to one CPU, same event can not be obsewved
	 * on muwtipwe cpus at same time.
	 */
	event->cpu = pmu->cpu;
	hwc->idx = -1;
	wetuwn 0;
}

static void cn10k_ddw_pewf_countew_enabwe(stwuct cn10k_ddw_pmu *pmu,
					  int countew, boow enabwe)
{
	u32 weg;
	u64 vaw;

	if (countew > DDWC_PEWF_NUM_COUNTEWS) {
		pw_eww("Ewwow: unsuppowted countew %d\n", countew);
		wetuwn;
	}

	if (countew < DDWC_PEWF_NUM_GEN_COUNTEWS) {
		weg = DDWC_PEWF_CFG(countew);
		vaw = weadq_wewaxed(pmu->base + weg);

		if (enabwe)
			vaw |= EVENT_ENABWE;
		ewse
			vaw &= ~EVENT_ENABWE;

		wwiteq_wewaxed(vaw, pmu->base + weg);
	} ewse {
		vaw = weadq_wewaxed(pmu->base + DDWC_PEWF_CNT_FWEEWUN_EN);
		if (enabwe) {
			if (countew == DDWC_PEWF_WEAD_COUNTEW_IDX)
				vaw |= DDWC_PEWF_FWEEWUN_WEAD_EN;
			ewse
				vaw |= DDWC_PEWF_FWEEWUN_WWITE_EN;
		} ewse {
			if (countew == DDWC_PEWF_WEAD_COUNTEW_IDX)
				vaw &= ~DDWC_PEWF_FWEEWUN_WEAD_EN;
			ewse
				vaw &= ~DDWC_PEWF_FWEEWUN_WWITE_EN;
		}
		wwiteq_wewaxed(vaw, pmu->base + DDWC_PEWF_CNT_FWEEWUN_EN);
	}
}

static u64 cn10k_ddw_pewf_wead_countew(stwuct cn10k_ddw_pmu *pmu, int countew)
{
	u64 vaw;

	if (countew == DDWC_PEWF_WEAD_COUNTEW_IDX)
		wetuwn weadq_wewaxed(pmu->base + DDWC_PEWF_CNT_VAWUE_WD_OP);

	if (countew == DDWC_PEWF_WWITE_COUNTEW_IDX)
		wetuwn weadq_wewaxed(pmu->base + DDWC_PEWF_CNT_VAWUE_WW_OP);

	vaw = weadq_wewaxed(pmu->base + DDWC_PEWF_CNT_VAWUE(countew));
	wetuwn vaw;
}

static void cn10k_ddw_pewf_event_update(stwuct pewf_event *event)
{
	stwuct cn10k_ddw_pmu *pmu = to_cn10k_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 pwev_count, new_count, mask;

	do {
		pwev_count = wocaw64_wead(&hwc->pwev_count);
		new_count = cn10k_ddw_pewf_wead_countew(pmu, hwc->idx);
	} whiwe (wocaw64_xchg(&hwc->pwev_count, new_count) != pwev_count);

	mask = DDWC_PEWF_CNT_MAX_VAWUE;

	wocaw64_add((new_count - pwev_count) & mask, &event->count);
}

static void cn10k_ddw_pewf_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct cn10k_ddw_pmu *pmu = to_cn10k_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;

	wocaw64_set(&hwc->pwev_count, 0);

	cn10k_ddw_pewf_countew_enabwe(pmu, countew, twue);

	hwc->state = 0;
}

static int cn10k_ddw_pewf_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct cn10k_ddw_pmu *pmu = to_cn10k_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u8 config = event->attw.config;
	int countew, wet;
	u32 weg_offset;
	u64 vaw;

	countew = cn10k_ddw_pewf_awwoc_countew(pmu, event);
	if (countew < 0)
		wetuwn -EAGAIN;

	pmu->active_events++;
	hwc->idx = countew;

	if (pmu->active_events == 1)
		hwtimew_stawt(&pmu->hwtimew, cn10k_ddw_pmu_timew_pewiod(),
			      HWTIMEW_MODE_WEW_PINNED);

	if (countew < DDWC_PEWF_NUM_GEN_COUNTEWS) {
		/* Genewic countews, configuwe event id */
		weg_offset = DDWC_PEWF_CFG(countew);
		wet = ddw_pewf_get_event_bitmap(config, &vaw);
		if (wet)
			wetuwn wet;

		wwiteq_wewaxed(vaw, pmu->base + weg_offset);
	} ewse {
		/* fixed event countew, cweaw countew vawue */
		if (countew == DDWC_PEWF_WEAD_COUNTEW_IDX)
			vaw = DDWC_FWEEWUN_WEAD_CNT_CWW;
		ewse
			vaw = DDWC_FWEEWUN_WWITE_CNT_CWW;

		wwiteq_wewaxed(vaw, pmu->base + DDWC_PEWF_CNT_FWEEWUN_CTWW);
	}

	hwc->state |= PEWF_HES_STOPPED;

	if (fwags & PEWF_EF_STAWT)
		cn10k_ddw_pewf_event_stawt(event, fwags);

	wetuwn 0;
}

static void cn10k_ddw_pewf_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct cn10k_ddw_pmu *pmu = to_cn10k_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;

	cn10k_ddw_pewf_countew_enabwe(pmu, countew, fawse);

	if (fwags & PEWF_EF_UPDATE)
		cn10k_ddw_pewf_event_update(event);

	hwc->state |= PEWF_HES_STOPPED;
}

static void cn10k_ddw_pewf_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct cn10k_ddw_pmu *pmu = to_cn10k_ddw_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;

	cn10k_ddw_pewf_event_stop(event, PEWF_EF_UPDATE);

	cn10k_ddw_pewf_fwee_countew(pmu, countew);
	pmu->active_events--;
	hwc->idx = -1;

	/* Cancew timew when no events to captuwe */
	if (pmu->active_events == 0)
		hwtimew_cancew(&pmu->hwtimew);
}

static void cn10k_ddw_pewf_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct cn10k_ddw_pmu *ddw_pmu = to_cn10k_ddw_pmu(pmu);

	wwiteq_wewaxed(STAWT_OP_CTWW_VAW_STAWT, ddw_pmu->base +
		       DDWC_PEWF_CNT_STAWT_OP_CTWW);
}

static void cn10k_ddw_pewf_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct cn10k_ddw_pmu *ddw_pmu = to_cn10k_ddw_pmu(pmu);

	wwiteq_wewaxed(END_OP_CTWW_VAW_END, ddw_pmu->base +
		       DDWC_PEWF_CNT_END_OP_CTWW);
}

static void cn10k_ddw_pewf_event_update_aww(stwuct cn10k_ddw_pmu *pmu)
{
	stwuct hw_pewf_event *hwc;
	int i;

	fow (i = 0; i < DDWC_PEWF_NUM_GEN_COUNTEWS; i++) {
		if (pmu->events[i] == NUWW)
			continue;

		cn10k_ddw_pewf_event_update(pmu->events[i]);
	}

	/* Weset pwevious count as h/w countew awe weset */
	fow (i = 0; i < DDWC_PEWF_NUM_GEN_COUNTEWS; i++) {
		if (pmu->events[i] == NUWW)
			continue;

		hwc = &pmu->events[i]->hw;
		wocaw64_set(&hwc->pwev_count, 0);
	}
}

static iwqwetuwn_t cn10k_ddw_pmu_ovewfwow_handwew(stwuct cn10k_ddw_pmu *pmu)
{
	stwuct pewf_event *event;
	stwuct hw_pewf_event *hwc;
	u64 pwev_count, new_count;
	u64 vawue;
	int i;

	event = pmu->events[DDWC_PEWF_WEAD_COUNTEW_IDX];
	if (event) {
		hwc = &event->hw;
		pwev_count = wocaw64_wead(&hwc->pwev_count);
		new_count = cn10k_ddw_pewf_wead_countew(pmu, hwc->idx);

		/* Ovewfwow condition is when new count wess than
		 * pwevious count
		 */
		if (new_count < pwev_count)
			cn10k_ddw_pewf_event_update(event);
	}

	event = pmu->events[DDWC_PEWF_WWITE_COUNTEW_IDX];
	if (event) {
		hwc = &event->hw;
		pwev_count = wocaw64_wead(&hwc->pwev_count);
		new_count = cn10k_ddw_pewf_wead_countew(pmu, hwc->idx);

		/* Ovewfwow condition is when new count wess than
		 * pwevious count
		 */
		if (new_count < pwev_count)
			cn10k_ddw_pewf_event_update(event);
	}

	fow (i = 0; i < DDWC_PEWF_NUM_GEN_COUNTEWS; i++) {
		if (pmu->events[i] == NUWW)
			continue;

		vawue = cn10k_ddw_pewf_wead_countew(pmu, i);
		if (vawue == DDWC_PEWF_CNT_MAX_VAWUE) {
			pw_info("Countew-(%d) weached max vawue\n", i);
			cn10k_ddw_pewf_event_update_aww(pmu);
			cn10k_ddw_pewf_pmu_disabwe(&pmu->pmu);
			cn10k_ddw_pewf_pmu_enabwe(&pmu->pmu);
		}
	}

	wetuwn IWQ_HANDWED;
}

static enum hwtimew_westawt cn10k_ddw_pmu_timew_handwew(stwuct hwtimew *hwtimew)
{
	stwuct cn10k_ddw_pmu *pmu = containew_of(hwtimew, stwuct cn10k_ddw_pmu,
						 hwtimew);
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	cn10k_ddw_pmu_ovewfwow_handwew(pmu);
	wocaw_iwq_westowe(fwags);

	hwtimew_fowwawd_now(hwtimew, cn10k_ddw_pmu_timew_pewiod());
	wetuwn HWTIMEW_WESTAWT;
}

static int cn10k_ddw_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct cn10k_ddw_pmu *pmu = hwist_entwy_safe(node, stwuct cn10k_ddw_pmu,
						     node);
	unsigned int tawget;

	if (cpu != pmu->cpu)
		wetuwn 0;

	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;

	pewf_pmu_migwate_context(&pmu->pmu, cpu, tawget);
	pmu->cpu = tawget;
	wetuwn 0;
}

static int cn10k_ddw_pewf_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cn10k_ddw_pmu *ddw_pmu;
	stwuct wesouwce *wes;
	void __iomem *base;
	chaw *name;
	int wet;

	ddw_pmu = devm_kzawwoc(&pdev->dev, sizeof(*ddw_pmu), GFP_KEWNEW);
	if (!ddw_pmu)
		wetuwn -ENOMEM;

	ddw_pmu->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, ddw_pmu);

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	ddw_pmu->base = base;

	/* Setup the PMU countew to wowk in manuaw mode */
	wwiteq_wewaxed(OP_MODE_CTWW_VAW_MANNUAW, ddw_pmu->base +
		       DDWC_PEWF_CNT_OP_MODE_CTWW);

	ddw_pmu->pmu = (stwuct pmu) {
		.moduwe	      = THIS_MODUWE,
		.capabiwities = PEWF_PMU_CAP_NO_EXCWUDE,
		.task_ctx_nw = pewf_invawid_context,
		.attw_gwoups = cn10k_attw_gwoups,
		.event_init  = cn10k_ddw_pewf_event_init,
		.add	     = cn10k_ddw_pewf_event_add,
		.dew	     = cn10k_ddw_pewf_event_dew,
		.stawt	     = cn10k_ddw_pewf_event_stawt,
		.stop	     = cn10k_ddw_pewf_event_stop,
		.wead	     = cn10k_ddw_pewf_event_update,
		.pmu_enabwe  = cn10k_ddw_pewf_pmu_enabwe,
		.pmu_disabwe = cn10k_ddw_pewf_pmu_disabwe,
	};

	/* Choose this cpu to cowwect pewf data */
	ddw_pmu->cpu = waw_smp_pwocessow_id();

	name = devm_kaspwintf(ddw_pmu->dev, GFP_KEWNEW, "mwvw_ddw_pmu_%wwx",
			      wes->stawt);
	if (!name)
		wetuwn -ENOMEM;

	hwtimew_init(&ddw_pmu->hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	ddw_pmu->hwtimew.function = cn10k_ddw_pmu_timew_handwew;

	cpuhp_state_add_instance_nocawws(
				CPUHP_AP_PEWF_AWM_MAWVEWW_CN10K_DDW_ONWINE,
				&ddw_pmu->node);

	wet = pewf_pmu_wegistew(&ddw_pmu->pmu, name, -1);
	if (wet)
		goto ewwow;

	pw_info("CN10K DDW PMU Dwivew fow ddwc@%wwx\n", wes->stawt);
	wetuwn 0;
ewwow:
	cpuhp_state_wemove_instance_nocawws(
				CPUHP_AP_PEWF_AWM_MAWVEWW_CN10K_DDW_ONWINE,
				&ddw_pmu->node);
	wetuwn wet;
}

static int cn10k_ddw_pewf_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cn10k_ddw_pmu *ddw_pmu = pwatfowm_get_dwvdata(pdev);

	cpuhp_state_wemove_instance_nocawws(
				CPUHP_AP_PEWF_AWM_MAWVEWW_CN10K_DDW_ONWINE,
				&ddw_pmu->node);

	pewf_pmu_unwegistew(&ddw_pmu->pmu);
	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id cn10k_ddw_pmu_of_match[] = {
	{ .compatibwe = "mawveww,cn10k-ddw-pmu", },
	{ },
};
MODUWE_DEVICE_TABWE(of, cn10k_ddw_pmu_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cn10k_ddw_pmu_acpi_match[] = {
	{"MWVW000A", 0},
	{},
};
MODUWE_DEVICE_TABWE(acpi, cn10k_ddw_pmu_acpi_match);
#endif

static stwuct pwatfowm_dwivew cn10k_ddw_pmu_dwivew = {
	.dwivew	= {
		.name   = "cn10k-ddw-pmu",
		.of_match_tabwe = of_match_ptw(cn10k_ddw_pmu_of_match),
		.acpi_match_tabwe  = ACPI_PTW(cn10k_ddw_pmu_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe		= cn10k_ddw_pewf_pwobe,
	.wemove		= cn10k_ddw_pewf_wemove,
};

static int __init cn10k_ddw_pmu_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(
				CPUHP_AP_PEWF_AWM_MAWVEWW_CN10K_DDW_ONWINE,
				"pewf/mawveww/cn10k/ddw:onwine", NUWW,
				cn10k_ddw_pmu_offwine_cpu);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&cn10k_ddw_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(
				CPUHP_AP_PEWF_AWM_MAWVEWW_CN10K_DDW_ONWINE);
	wetuwn wet;
}

static void __exit cn10k_ddw_pmu_exit(void)
{
	pwatfowm_dwivew_unwegistew(&cn10k_ddw_pmu_dwivew);
	cpuhp_wemove_muwti_state(CPUHP_AP_PEWF_AWM_MAWVEWW_CN10K_DDW_ONWINE);
}

moduwe_init(cn10k_ddw_pmu_init);
moduwe_exit(cn10k_ddw_pmu_exit);

MODUWE_AUTHOW("Bhawat Bhushan <bbhushan2@mawveww.com>");
MODUWE_WICENSE("GPW v2");
