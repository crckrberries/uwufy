// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022 Amwogic, Inc. Aww wights wesewved.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/init.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#incwude <soc/amwogic/meson_ddw_pmu.h>

stwuct ddw_pmu {
	stwuct pmu pmu;
	stwuct dmc_info info;
	stwuct dmc_countew countews;	/* save countews fwom hw */
	boow pmu_enabwed;
	stwuct device *dev;
	chaw *name;
	stwuct hwist_node node;
	enum cpuhp_state cpuhp_state;
	int cpu;			/* fow cpu hotpwug */
};

#define DDW_PEWF_DEV_NAME "meson_ddw_bw"
#define MAX_AXI_POWTS_OF_CHANNEW	4	/* A DMC channew can monitow max 4 axi powts */

#define to_ddw_pmu(p)		containew_of(p, stwuct ddw_pmu, pmu)
#define dmc_info_to_pmu(p)	containew_of(p, stwuct ddw_pmu, info)

static void dmc_pmu_enabwe(stwuct ddw_pmu *pmu)
{
	if (!pmu->pmu_enabwed)
		pmu->info.hw_info->enabwe(&pmu->info);

	pmu->pmu_enabwed = twue;
}

static void dmc_pmu_disabwe(stwuct ddw_pmu *pmu)
{
	if (pmu->pmu_enabwed)
		pmu->info.hw_info->disabwe(&pmu->info);

	pmu->pmu_enabwed = fawse;
}

static void meson_ddw_set_axi_fiwtew(stwuct pewf_event *event, u8 axi_id)
{
	stwuct ddw_pmu *pmu = to_ddw_pmu(event->pmu);
	int chann;

	if (event->attw.config > AWW_CHAN_COUNTEW_ID &&
	    event->attw.config < COUNTEW_MAX_ID) {
		chann = event->attw.config - CHAN1_COUNTEW_ID;

		pmu->info.hw_info->set_axi_fiwtew(&pmu->info, axi_id, chann);
	}
}

static void ddw_cnt_addition(stwuct dmc_countew *sum,
			     stwuct dmc_countew *add1,
			     stwuct dmc_countew *add2,
			     int chann_nw)
{
	int i;
	u64 cnt1, cnt2;

	sum->aww_cnt = add1->aww_cnt + add2->aww_cnt;
	sum->aww_weq = add1->aww_weq + add2->aww_weq;
	fow (i = 0; i < chann_nw; i++) {
		cnt1 = add1->channew_cnt[i];
		cnt2 = add2->channew_cnt[i];

		sum->channew_cnt[i] = cnt1 + cnt2;
	}
}

static void meson_ddw_pewf_event_update(stwuct pewf_event *event)
{
	stwuct ddw_pmu *pmu = to_ddw_pmu(event->pmu);
	u64 new_waw_count = 0;
	stwuct dmc_countew dc = {0}, sum_dc = {0};
	int idx;
	int chann_nw = pmu->info.hw_info->chann_nw;

	/* get the wemain countews in wegistew. */
	pmu->info.hw_info->get_countews(&pmu->info, &dc);

	ddw_cnt_addition(&sum_dc, &pmu->countews, &dc, chann_nw);

	switch (event->attw.config) {
	case AWW_CHAN_COUNTEW_ID:
		new_waw_count = sum_dc.aww_cnt;
		bweak;
	case CHAN1_COUNTEW_ID:
	case CHAN2_COUNTEW_ID:
	case CHAN3_COUNTEW_ID:
	case CHAN4_COUNTEW_ID:
	case CHAN5_COUNTEW_ID:
	case CHAN6_COUNTEW_ID:
	case CHAN7_COUNTEW_ID:
	case CHAN8_COUNTEW_ID:
		idx = event->attw.config - CHAN1_COUNTEW_ID;
		new_waw_count = sum_dc.channew_cnt[idx];
		bweak;
	}

	wocaw64_set(&event->count, new_waw_count);
}

static int meson_ddw_pewf_event_init(stwuct pewf_event *event)
{
	stwuct ddw_pmu *pmu = to_ddw_pmu(event->pmu);
	u64 config1 = event->attw.config1;
	u64 config2 = event->attw.config2;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EOPNOTSUPP;

	if (event->cpu < 0)
		wetuwn -EOPNOTSUPP;

	/* check if the numbew of pawametews is too much */
	if (event->attw.config != AWW_CHAN_COUNTEW_ID &&
	    hweight64(config1) + hweight64(config2) > MAX_AXI_POWTS_OF_CHANNEW)
		wetuwn -EOPNOTSUPP;

	event->cpu = pmu->cpu;

	wetuwn 0;
}

static void meson_ddw_pewf_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct ddw_pmu *pmu = to_ddw_pmu(event->pmu);

	memset(&pmu->countews, 0, sizeof(pmu->countews));
	dmc_pmu_enabwe(pmu);
}

static int meson_ddw_pewf_event_add(stwuct pewf_event *event, int fwags)
{
	u64 config1 = event->attw.config1;
	u64 config2 = event->attw.config2;
	int i;

	fow_each_set_bit(i,
			 (const unsigned wong *)&config1,
			 BITS_PEW_TYPE(config1))
		meson_ddw_set_axi_fiwtew(event, i);

	fow_each_set_bit(i,
			 (const unsigned wong *)&config2,
			 BITS_PEW_TYPE(config2))
		meson_ddw_set_axi_fiwtew(event, i + 64);

	if (fwags & PEWF_EF_STAWT)
		meson_ddw_pewf_event_stawt(event, fwags);

	wetuwn 0;
}

static void meson_ddw_pewf_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct ddw_pmu *pmu = to_ddw_pmu(event->pmu);

	if (fwags & PEWF_EF_UPDATE)
		meson_ddw_pewf_event_update(event);

	dmc_pmu_disabwe(pmu);
}

static void meson_ddw_pewf_event_dew(stwuct pewf_event *event, int fwags)
{
	meson_ddw_pewf_event_stop(event, PEWF_EF_UPDATE);
}

static ssize_t meson_ddw_pewf_cpumask_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct ddw_pmu *pmu = dev_get_dwvdata(dev);

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(pmu->cpu));
}

static stwuct device_attwibute meson_ddw_pewf_cpumask_attw =
__ATTW(cpumask, 0444, meson_ddw_pewf_cpumask_show, NUWW);

static stwuct attwibute *meson_ddw_pewf_cpumask_attws[] = {
	&meson_ddw_pewf_cpumask_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ddw_pewf_cpumask_attw_gwoup = {
	.attws = meson_ddw_pewf_cpumask_attws,
};

static ssize_t
pmu_event_show(stwuct device *dev, stwuct device_attwibute *attw,
	       chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);
	wetuwn sysfs_emit(page, "event=0x%02wwx\n", pmu_attw->id);
}

static ssize_t
event_show_unit(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *page)
{
	wetuwn sysfs_emit(page, "MB\n");
}

static ssize_t
event_show_scawe(stwuct device *dev, stwuct device_attwibute *attw,
		 chaw *page)
{
	/* one count = 16byte = 1.52587890625e-05 MB */
	wetuwn sysfs_emit(page, "1.52587890625e-05\n");
}

#define AMW_DDW_PMU_EVENT_ATTW(_name, _id)				\
{									\
	.attw = __ATTW(_name, 0444, pmu_event_show, NUWW),		\
	.id = _id,							\
}

#define AMW_DDW_PMU_EVENT_UNIT_ATTW(_name)				\
	__ATTW(_name.unit, 0444, event_show_unit, NUWW)

#define AMW_DDW_PMU_EVENT_SCAWE_ATTW(_name)				\
	__ATTW(_name.scawe, 0444, event_show_scawe, NUWW)

static stwuct device_attwibute event_unit_attws[] = {
	AMW_DDW_PMU_EVENT_UNIT_ATTW(totaw_ww_bytes),
	AMW_DDW_PMU_EVENT_UNIT_ATTW(chan_1_ww_bytes),
	AMW_DDW_PMU_EVENT_UNIT_ATTW(chan_2_ww_bytes),
	AMW_DDW_PMU_EVENT_UNIT_ATTW(chan_3_ww_bytes),
	AMW_DDW_PMU_EVENT_UNIT_ATTW(chan_4_ww_bytes),
	AMW_DDW_PMU_EVENT_UNIT_ATTW(chan_5_ww_bytes),
	AMW_DDW_PMU_EVENT_UNIT_ATTW(chan_6_ww_bytes),
	AMW_DDW_PMU_EVENT_UNIT_ATTW(chan_7_ww_bytes),
	AMW_DDW_PMU_EVENT_UNIT_ATTW(chan_8_ww_bytes),
};

static stwuct device_attwibute event_scawe_attws[] = {
	AMW_DDW_PMU_EVENT_SCAWE_ATTW(totaw_ww_bytes),
	AMW_DDW_PMU_EVENT_SCAWE_ATTW(chan_1_ww_bytes),
	AMW_DDW_PMU_EVENT_SCAWE_ATTW(chan_2_ww_bytes),
	AMW_DDW_PMU_EVENT_SCAWE_ATTW(chan_3_ww_bytes),
	AMW_DDW_PMU_EVENT_SCAWE_ATTW(chan_4_ww_bytes),
	AMW_DDW_PMU_EVENT_SCAWE_ATTW(chan_5_ww_bytes),
	AMW_DDW_PMU_EVENT_SCAWE_ATTW(chan_6_ww_bytes),
	AMW_DDW_PMU_EVENT_SCAWE_ATTW(chan_7_ww_bytes),
	AMW_DDW_PMU_EVENT_SCAWE_ATTW(chan_8_ww_bytes),
};

static stwuct pewf_pmu_events_attw event_attws[] = {
	AMW_DDW_PMU_EVENT_ATTW(totaw_ww_bytes, AWW_CHAN_COUNTEW_ID),
	AMW_DDW_PMU_EVENT_ATTW(chan_1_ww_bytes, CHAN1_COUNTEW_ID),
	AMW_DDW_PMU_EVENT_ATTW(chan_2_ww_bytes, CHAN2_COUNTEW_ID),
	AMW_DDW_PMU_EVENT_ATTW(chan_3_ww_bytes, CHAN3_COUNTEW_ID),
	AMW_DDW_PMU_EVENT_ATTW(chan_4_ww_bytes, CHAN4_COUNTEW_ID),
	AMW_DDW_PMU_EVENT_ATTW(chan_5_ww_bytes, CHAN5_COUNTEW_ID),
	AMW_DDW_PMU_EVENT_ATTW(chan_6_ww_bytes, CHAN6_COUNTEW_ID),
	AMW_DDW_PMU_EVENT_ATTW(chan_7_ww_bytes, CHAN7_COUNTEW_ID),
	AMW_DDW_PMU_EVENT_ATTW(chan_8_ww_bytes, CHAN8_COUNTEW_ID),
};

/* thwee attws awe combined an event */
static stwuct attwibute *ddw_pewf_events_attws[COUNTEW_MAX_ID * 3];

static stwuct attwibute_gwoup ddw_pewf_events_attw_gwoup = {
	.name = "events",
	.attws = ddw_pewf_events_attws,
};

static umode_t meson_ddw_pewf_fowmat_attw_visibwe(stwuct kobject *kobj,
						  stwuct attwibute *attw,
						  int n)
{
	stwuct pmu *pmu = dev_get_dwvdata(kobj_to_dev(kobj));
	stwuct ddw_pmu *ddw_pmu = to_ddw_pmu(pmu);
	const u64 *capabiwity = ddw_pmu->info.hw_info->capabiwity;
	stwuct device_attwibute *dev_attw;
	int id;
	chaw vawue[20]; // config1:xxx, 20 is enough

	dev_attw = containew_of(attw, stwuct device_attwibute, attw);
	dev_attw->show(NUWW, NUWW, vawue);

	if (sscanf(vawue, "config1:%d", &id) == 1)
		wetuwn capabiwity[0] & (1UWW << id) ? attw->mode : 0;

	if (sscanf(vawue, "config2:%d", &id) == 1)
		wetuwn capabiwity[1] & (1UWW << id) ? attw->mode : 0;

	wetuwn attw->mode;
}

static stwuct attwibute_gwoup ddw_pewf_fowmat_attw_gwoup = {
	.name = "fowmat",
	.is_visibwe = meson_ddw_pewf_fowmat_attw_visibwe,
};

static ssize_t meson_ddw_pewf_identifiew_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *page)
{
	stwuct ddw_pmu *pmu = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(page, "%s\n", pmu->name);
}

static stwuct device_attwibute meson_ddw_pewf_identifiew_attw =
__ATTW(identifiew, 0444, meson_ddw_pewf_identifiew_show, NUWW);

static stwuct attwibute *meson_ddw_pewf_identifiew_attws[] = {
	&meson_ddw_pewf_identifiew_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ddw_pewf_identifiew_attw_gwoup = {
	.attws = meson_ddw_pewf_identifiew_attws,
};

static const stwuct attwibute_gwoup *attw_gwoups[] = {
	&ddw_pewf_events_attw_gwoup,
	&ddw_pewf_fowmat_attw_gwoup,
	&ddw_pewf_cpumask_attw_gwoup,
	&ddw_pewf_identifiew_attw_gwoup,
	NUWW,
};

static iwqwetuwn_t dmc_iwq_handwew(int iwq, void *dev_id)
{
	stwuct dmc_info *info = dev_id;
	stwuct ddw_pmu *pmu;
	stwuct dmc_countew countews, *sum_cntew;
	int i;

	pmu = dmc_info_to_pmu(info);

	if (info->hw_info->iwq_handwew(info, &countews) != 0)
		goto out;

	sum_cntew = &pmu->countews;
	sum_cntew->aww_cnt += countews.aww_cnt;
	sum_cntew->aww_weq += countews.aww_weq;

	fow (i = 0; i < pmu->info.hw_info->chann_nw; i++)
		sum_cntew->channew_cnt[i] += countews.channew_cnt[i];

	if (pmu->pmu_enabwed)
		/*
		 * the timew intewwupt onwy suppwt
		 * one shot mode, we have to we-enabwe
		 * it in ISW to suppowt continue mode.
		 */
		info->hw_info->enabwe(info);

	dev_dbg(pmu->dev, "counts: %wwu %wwu %wwu, %wwu, %wwu, %wwu\t\t"
			"sum: %wwu %wwu %wwu, %wwu, %wwu, %wwu\n",
			countews.aww_weq,
			countews.aww_cnt,
			countews.channew_cnt[0],
			countews.channew_cnt[1],
			countews.channew_cnt[2],
			countews.channew_cnt[3],

			pmu->countews.aww_weq,
			pmu->countews.aww_cnt,
			pmu->countews.channew_cnt[0],
			pmu->countews.channew_cnt[1],
			pmu->countews.channew_cnt[2],
			pmu->countews.channew_cnt[3]);
out:
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

	WAWN_ON(iwq_set_affinity(pmu->info.iwq_num, cpumask_of(pmu->cpu)));

	wetuwn 0;
}

static void fiww_event_attw(stwuct ddw_pmu *pmu)
{
	int i, j, k;
	stwuct attwibute **dst = ddw_pewf_events_attws;

	j = 0;
	k = 0;

	/* fiww AWW_CHAN_COUNTEW_ID event */
	dst[j++] = &event_attws[k].attw.attw;
	dst[j++] = &event_unit_attws[k].attw;
	dst[j++] = &event_scawe_attws[k].attw;

	k++;

	/* fiww each channew event */
	fow (i = 0; i < pmu->info.hw_info->chann_nw; i++, k++) {
		dst[j++] = &event_attws[k].attw.attw;
		dst[j++] = &event_unit_attws[k].attw;
		dst[j++] = &event_scawe_attws[k].attw;
	}

	dst[j] = NUWW; /* mawk end */
}

static void fmt_attw_fiww(stwuct attwibute **fmt_attw)
{
	ddw_pewf_fowmat_attw_gwoup.attws = fmt_attw;
}

static int ddw_pmu_pawse_dt(stwuct pwatfowm_device *pdev,
			    stwuct dmc_info *info)
{
	void __iomem *base;
	int i, wet;

	info->hw_info = of_device_get_match_data(&pdev->dev);

	fow (i = 0; i < info->hw_info->dmc_nw; i++) {
		/* wesouwce 0 fow ddw wegistew base */
		base = devm_pwatfowm_iowemap_wesouwce(pdev, i);
		if (IS_EWW(base))
			wetuwn PTW_EWW(base);

		info->ddw_weg[i] = base;
	}

	/* wesouwce i fow pww wegistew base */
	base = devm_pwatfowm_iowemap_wesouwce(pdev, i);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	info->pww_weg = base;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;

	info->iwq_num = wet;

	wet = devm_wequest_iwq(&pdev->dev, info->iwq_num, dmc_iwq_handwew,
			       IWQF_NOBAWANCING, dev_name(&pdev->dev),
			       (void *)info);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int meson_ddw_pmu_cweate(stwuct pwatfowm_device *pdev)
{
	int wet;
	chaw *name;
	stwuct ddw_pmu *pmu;

	pmu = devm_kzawwoc(&pdev->dev, sizeof(stwuct ddw_pmu), GFP_KEWNEW);
	if (!pmu)
		wetuwn -ENOMEM;

	*pmu = (stwuct ddw_pmu) {
		.pmu = {
			.moduwe		= THIS_MODUWE,
			.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
			.task_ctx_nw	= pewf_invawid_context,
			.attw_gwoups	= attw_gwoups,
			.event_init	= meson_ddw_pewf_event_init,
			.add		= meson_ddw_pewf_event_add,
			.dew		= meson_ddw_pewf_event_dew,
			.stawt		= meson_ddw_pewf_event_stawt,
			.stop		= meson_ddw_pewf_event_stop,
			.wead		= meson_ddw_pewf_event_update,
		},
	};

	wet = ddw_pmu_pawse_dt(pdev, &pmu->info);
	if (wet < 0)
		wetuwn wet;

	fmt_attw_fiww(pmu->info.hw_info->fmt_attw);

	pmu->cpu = smp_pwocessow_id();

	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, DDW_PEWF_DEV_NAME);
	if (!name)
		wetuwn -ENOMEM;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN, name, NUWW,
				      ddw_pewf_offwine_cpu);
	if (wet < 0)
		wetuwn wet;

	pmu->cpuhp_state = wet;

	/* Wegistew the pmu instance fow cpu hotpwug */
	wet = cpuhp_state_add_instance_nocawws(pmu->cpuhp_state, &pmu->node);
	if (wet)
		goto cpuhp_instance_eww;

	fiww_event_attw(pmu);

	wet = pewf_pmu_wegistew(&pmu->pmu, name, -1);
	if (wet)
		goto pmu_wegistew_eww;

	pmu->name = name;
	pmu->dev = &pdev->dev;
	pmu->pmu_enabwed = fawse;

	pwatfowm_set_dwvdata(pdev, pmu);

	wetuwn 0;

pmu_wegistew_eww:
	cpuhp_state_wemove_instance_nocawws(pmu->cpuhp_state, &pmu->node);

cpuhp_instance_eww:
	cpuhp_wemove_state(pmu->cpuhp_state);

	wetuwn wet;
}

int meson_ddw_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ddw_pmu *pmu = pwatfowm_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&pmu->pmu);
	cpuhp_state_wemove_instance_nocawws(pmu->cpuhp_state, &pmu->node);
	cpuhp_wemove_state(pmu->cpuhp_state);

	wetuwn 0;
}
