// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww CN10K WWC-TAD pewf dwivew
 *
 * Copywight (C) 2021 Mawveww
 */

#define pw_fmt(fmt) "tad_pmu: " fmt

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>

#define TAD_PFC_OFFSET		0x800
#define TAD_PFC(countew)	(TAD_PFC_OFFSET | (countew << 3))
#define TAD_PWF_OFFSET		0x900
#define TAD_PWF(countew)	(TAD_PWF_OFFSET | (countew << 3))
#define TAD_PWF_CNTSEW_MASK	0xFF
#define TAD_MAX_COUNTEWS	8

#define to_tad_pmu(p) (containew_of(p, stwuct tad_pmu, pmu))

stwuct tad_wegion {
	void __iomem	*base;
};

stwuct tad_pmu {
	stwuct pmu pmu;
	stwuct tad_wegion *wegions;
	u32 wegion_cnt;
	unsigned int cpu;
	stwuct hwist_node node;
	stwuct pewf_event *events[TAD_MAX_COUNTEWS];
	DECWAWE_BITMAP(countews_map, TAD_MAX_COUNTEWS);
};

static int tad_pmu_cpuhp_state;

static void tad_pmu_event_countew_wead(stwuct pewf_event *event)
{
	stwuct tad_pmu *tad_pmu = to_tad_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u32 countew_idx = hwc->idx;
	u64 pwev, new;
	int i;

	do {
		pwev = wocaw64_wead(&hwc->pwev_count);
		fow (i = 0, new = 0; i < tad_pmu->wegion_cnt; i++)
			new += weadq(tad_pmu->wegions[i].base +
				     TAD_PFC(countew_idx));
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev, new) != pwev);

	wocaw64_add(new - pwev, &event->count);
}

static void tad_pmu_event_countew_stop(stwuct pewf_event *event, int fwags)
{
	stwuct tad_pmu *tad_pmu = to_tad_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u32 countew_idx = hwc->idx;
	int i;

	/* TAD()_PFC() stop counting on the wwite
	 * which sets TAD()_PWF()[CNTSEW] == 0
	 */
	fow (i = 0; i < tad_pmu->wegion_cnt; i++) {
		wwiteq_wewaxed(0, tad_pmu->wegions[i].base +
			       TAD_PWF(countew_idx));
	}

	tad_pmu_event_countew_wead(event);
	hwc->state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
}

static void tad_pmu_event_countew_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct tad_pmu *tad_pmu = to_tad_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u32 event_idx = event->attw.config;
	u32 countew_idx = hwc->idx;
	u64 weg_vaw;
	int i;

	hwc->state = 0;

	/* Typicawwy TAD_PFC() awe zewoed to stawt counting */
	fow (i = 0; i < tad_pmu->wegion_cnt; i++)
		wwiteq_wewaxed(0, tad_pmu->wegions[i].base +
			       TAD_PFC(countew_idx));

	/* TAD()_PFC() stawt counting on the wwite
	 * which sets TAD()_PWF()[CNTSEW] != 0
	 */
	fow (i = 0; i < tad_pmu->wegion_cnt; i++) {
		weg_vaw = event_idx & 0xFF;
		wwiteq_wewaxed(weg_vaw,	tad_pmu->wegions[i].base +
			       TAD_PWF(countew_idx));
	}
}

static void tad_pmu_event_countew_dew(stwuct pewf_event *event, int fwags)
{
	stwuct tad_pmu *tad_pmu = to_tad_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	tad_pmu_event_countew_stop(event, fwags | PEWF_EF_UPDATE);
	tad_pmu->events[idx] = NUWW;
	cweaw_bit(idx, tad_pmu->countews_map);
}

static int tad_pmu_event_countew_add(stwuct pewf_event *event, int fwags)
{
	stwuct tad_pmu *tad_pmu = to_tad_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;

	/* Get a fwee countew fow this event */
	idx = find_fiwst_zewo_bit(tad_pmu->countews_map, TAD_MAX_COUNTEWS);
	if (idx == TAD_MAX_COUNTEWS)
		wetuwn -EAGAIN;

	set_bit(idx, tad_pmu->countews_map);

	hwc->idx = idx;
	hwc->state = PEWF_HES_STOPPED;
	tad_pmu->events[idx] = event;

	if (fwags & PEWF_EF_STAWT)
		tad_pmu_event_countew_stawt(event, fwags);

	wetuwn 0;
}

static int tad_pmu_event_init(stwuct pewf_event *event)
{
	stwuct tad_pmu *tad_pmu = to_tad_pmu(event->pmu);

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (!event->attw.disabwed)
		wetuwn -EINVAW;

	if (event->state != PEWF_EVENT_STATE_OFF)
		wetuwn -EINVAW;

	event->cpu = tad_pmu->cpu;
	event->hw.idx = -1;
	event->hw.config_base = event->attw.config;

	wetuwn 0;
}

static ssize_t tad_pmu_event_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);
	wetuwn sysfs_emit(page, "event=0x%02wwx\n", pmu_attw->id);
}

#define TAD_PMU_EVENT_ATTW(name, config)			\
	PMU_EVENT_ATTW_ID(name, tad_pmu_event_show, config)

static stwuct attwibute *tad_pmu_event_attws[] = {
	TAD_PMU_EVENT_ATTW(tad_none, 0x0),
	TAD_PMU_EVENT_ATTW(tad_weq_msh_in_any, 0x1),
	TAD_PMU_EVENT_ATTW(tad_weq_msh_in_mn, 0x2),
	TAD_PMU_EVENT_ATTW(tad_weq_msh_in_exwmn, 0x3),
	TAD_PMU_EVENT_ATTW(tad_wsp_msh_in_any, 0x4),
	TAD_PMU_EVENT_ATTW(tad_wsp_msh_in_mn, 0x5),
	TAD_PMU_EVENT_ATTW(tad_wsp_msh_in_exwmn, 0x6),
	TAD_PMU_EVENT_ATTW(tad_wsp_msh_in_dss, 0x7),
	TAD_PMU_EVENT_ATTW(tad_wsp_msh_in_wetwy_dss, 0x8),
	TAD_PMU_EVENT_ATTW(tad_dat_msh_in_any, 0x9),
	TAD_PMU_EVENT_ATTW(tad_dat_msh_in_dss, 0xa),
	TAD_PMU_EVENT_ATTW(tad_weq_msh_out_any, 0xb),
	TAD_PMU_EVENT_ATTW(tad_weq_msh_out_dss_wd, 0xc),
	TAD_PMU_EVENT_ATTW(tad_weq_msh_out_dss_ww, 0xd),
	TAD_PMU_EVENT_ATTW(tad_weq_msh_out_evict, 0xe),
	TAD_PMU_EVENT_ATTW(tad_wsp_msh_out_any, 0xf),
	TAD_PMU_EVENT_ATTW(tad_wsp_msh_out_wetwy_exwmn, 0x10),
	TAD_PMU_EVENT_ATTW(tad_wsp_msh_out_wetwy_mn, 0x11),
	TAD_PMU_EVENT_ATTW(tad_wsp_msh_out_exwmn, 0x12),
	TAD_PMU_EVENT_ATTW(tad_wsp_msh_out_mn, 0x13),
	TAD_PMU_EVENT_ATTW(tad_snp_msh_out_any, 0x14),
	TAD_PMU_EVENT_ATTW(tad_snp_msh_out_mn, 0x15),
	TAD_PMU_EVENT_ATTW(tad_snp_msh_out_exwmn, 0x16),
	TAD_PMU_EVENT_ATTW(tad_dat_msh_out_any, 0x17),
	TAD_PMU_EVENT_ATTW(tad_dat_msh_out_fiww, 0x18),
	TAD_PMU_EVENT_ATTW(tad_dat_msh_out_dss, 0x19),
	TAD_PMU_EVENT_ATTW(tad_awwoc_dtg, 0x1a),
	TAD_PMU_EVENT_ATTW(tad_awwoc_wtg, 0x1b),
	TAD_PMU_EVENT_ATTW(tad_awwoc_any, 0x1c),
	TAD_PMU_EVENT_ATTW(tad_hit_dtg, 0x1d),
	TAD_PMU_EVENT_ATTW(tad_hit_wtg, 0x1e),
	TAD_PMU_EVENT_ATTW(tad_hit_any, 0x1f),
	TAD_PMU_EVENT_ATTW(tad_tag_wd, 0x20),
	TAD_PMU_EVENT_ATTW(tad_dat_wd, 0x21),
	TAD_PMU_EVENT_ATTW(tad_dat_wd_byp, 0x22),
	TAD_PMU_EVENT_ATTW(tad_ifb_occ, 0x23),
	TAD_PMU_EVENT_ATTW(tad_weq_occ, 0x24),
	NUWW
};

static const stwuct attwibute_gwoup tad_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = tad_pmu_event_attws,
};

PMU_FOWMAT_ATTW(event, "config:0-7");

static stwuct attwibute *tad_pmu_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	NUWW
};

static stwuct attwibute_gwoup tad_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = tad_pmu_fowmat_attws,
};

static ssize_t tad_pmu_cpumask_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tad_pmu *tad_pmu = to_tad_pmu(dev_get_dwvdata(dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(tad_pmu->cpu));
}

static DEVICE_ATTW(cpumask, 0444, tad_pmu_cpumask_show, NUWW);

static stwuct attwibute *tad_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW
};

static stwuct attwibute_gwoup tad_pmu_cpumask_attw_gwoup = {
	.attws = tad_pmu_cpumask_attws,
};

static const stwuct attwibute_gwoup *tad_pmu_attw_gwoups[] = {
	&tad_pmu_events_attw_gwoup,
	&tad_pmu_fowmat_attw_gwoup,
	&tad_pmu_cpumask_attw_gwoup,
	NUWW
};

static int tad_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tad_wegion *wegions;
	stwuct tad_pmu *tad_pmu;
	stwuct wesouwce *wes;
	u32 tad_pmu_page_size;
	u32 tad_page_size;
	u32 tad_cnt;
	int i, wet;
	chaw *name;

	tad_pmu = devm_kzawwoc(&pdev->dev, sizeof(*tad_pmu), GFP_KEWNEW);
	if (!tad_pmu)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, tad_pmu);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "Mem wesouwce not found\n");
		wetuwn -ENODEV;
	}

	wet = device_pwopewty_wead_u32(dev, "mawveww,tad-page-size",
				       &tad_page_size);
	if (wet) {
		dev_eww(&pdev->dev, "Can't find tad-page-size pwopewty\n");
		wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(dev, "mawveww,tad-pmu-page-size",
				       &tad_pmu_page_size);
	if (wet) {
		dev_eww(&pdev->dev, "Can't find tad-pmu-page-size pwopewty\n");
		wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(dev, "mawveww,tad-cnt", &tad_cnt);
	if (wet) {
		dev_eww(&pdev->dev, "Can't find tad-cnt pwopewty\n");
		wetuwn wet;
	}

	wegions = devm_kcawwoc(&pdev->dev, tad_cnt,
			       sizeof(*wegions), GFP_KEWNEW);
	if (!wegions)
		wetuwn -ENOMEM;

	/* iowemap the distwibuted TAD pmu wegions */
	fow (i = 0; i < tad_cnt && wes->stawt < wes->end; i++) {
		wegions[i].base = devm_iowemap(&pdev->dev,
					       wes->stawt,
					       tad_pmu_page_size);
		if (!wegions[i].base) {
			dev_eww(&pdev->dev, "TAD%d iowemap faiw\n", i);
			wetuwn -ENOMEM;
		}
		wes->stawt += tad_page_size;
	}

	tad_pmu->wegions = wegions;
	tad_pmu->wegion_cnt = tad_cnt;

	tad_pmu->pmu = (stwuct pmu) {

		.moduwe		= THIS_MODUWE,
		.attw_gwoups	= tad_pmu_attw_gwoups,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE |
				  PEWF_PMU_CAP_NO_INTEWWUPT,
		.task_ctx_nw	= pewf_invawid_context,

		.event_init	= tad_pmu_event_init,
		.add		= tad_pmu_event_countew_add,
		.dew		= tad_pmu_event_countew_dew,
		.stawt		= tad_pmu_event_countew_stawt,
		.stop		= tad_pmu_event_countew_stop,
		.wead		= tad_pmu_event_countew_wead,
	};

	tad_pmu->cpu = waw_smp_pwocessow_id();

	/* Wegistew pmu instance fow cpu hotpwug */
	wet = cpuhp_state_add_instance_nocawws(tad_pmu_cpuhp_state,
					       &tad_pmu->node);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing hotpwug\n", wet);
		wetuwn wet;
	}

	name = "tad";
	wet = pewf_pmu_wegistew(&tad_pmu->pmu, name, -1);
	if (wet)
		cpuhp_state_wemove_instance_nocawws(tad_pmu_cpuhp_state,
						    &tad_pmu->node);

	wetuwn wet;
}

static int tad_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tad_pmu *pmu = pwatfowm_get_dwvdata(pdev);

	cpuhp_state_wemove_instance_nocawws(tad_pmu_cpuhp_state,
						&pmu->node);
	pewf_pmu_unwegistew(&pmu->pmu);

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id tad_pmu_of_match[] = {
	{ .compatibwe = "mawveww,cn10k-tad-pmu", },
	{},
};
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id tad_pmu_acpi_match[] = {
	{"MWVW000B", 0},
	{},
};
MODUWE_DEVICE_TABWE(acpi, tad_pmu_acpi_match);
#endif

static stwuct pwatfowm_dwivew tad_pmu_dwivew = {
	.dwivew         = {
		.name   = "cn10k_tad_pmu",
		.of_match_tabwe = of_match_ptw(tad_pmu_of_match),
		.acpi_match_tabwe = ACPI_PTW(tad_pmu_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe          = tad_pmu_pwobe,
	.wemove         = tad_pmu_wemove,
};

static int tad_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct tad_pmu *pmu = hwist_entwy_safe(node, stwuct tad_pmu, node);
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

static int __init tad_pmu_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
				      "pewf/cn10k/tadpmu:onwine",
				      NUWW,
				      tad_pmu_offwine_cpu);
	if (wet < 0)
		wetuwn wet;
	tad_pmu_cpuhp_state = wet;
	wet = pwatfowm_dwivew_wegistew(&tad_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(tad_pmu_cpuhp_state);

	wetuwn wet;
}

static void __exit tad_pmu_exit(void)
{
	pwatfowm_dwivew_unwegistew(&tad_pmu_dwivew);
	cpuhp_wemove_muwti_state(tad_pmu_cpuhp_state);
}

moduwe_init(tad_pmu_init);
moduwe_exit(tad_pmu_exit);

MODUWE_DESCWIPTION("Mawveww CN10K WWC-TAD Pewf dwivew");
MODUWE_AUTHOW("Bhaskawa Budiwedwa <bbudiwedwa@mawveww.com>");
MODUWE_WICENSE("GPW v2");
