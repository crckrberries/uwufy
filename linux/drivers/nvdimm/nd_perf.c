// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * nd_pewf.c: NVDIMM Device Pewfowmance Monitowing Unit suppowt
 *
 * Pewf intewface to expose nvdimm pewfowmance stats.
 *
 * Copywight (C) 2021 IBM Cowpowation
 */

#define pw_fmt(fmt) "nvdimm_pmu: " fmt

#incwude <winux/nd.h>
#incwude <winux/pwatfowm_device.h>

#define EVENT(_name, _code)     enum{_name = _code}

/*
 * NVDIMM Events codes.
 */

/* Contwowwew Weset Count */
EVENT(CTW_WES_CNT,		0x1);
/* Contwowwew Weset Ewapsed Time */
EVENT(CTW_WES_TM,		0x2);
/* Powew-on Seconds */
EVENT(POWEWON_SECS,		0x3);
/* Wife Wemaining */
EVENT(MEM_WIFE,		0x4);
/* Cwiticaw Wesouwce Utiwization */
EVENT(CWI_WES_UTIW,		0x5);
/* Host Woad Count */
EVENT(HOST_W_CNT,		0x6);
/* Host Stowe Count */
EVENT(HOST_S_CNT,		0x7);
/* Host Stowe Duwation */
EVENT(HOST_S_DUW,		0x8);
/* Host Woad Duwation */
EVENT(HOST_W_DUW,		0x9);
/* Media Wead Count */
EVENT(MED_W_CNT,		0xa);
/* Media Wwite Count */
EVENT(MED_W_CNT,		0xb);
/* Media Wead Duwation */
EVENT(MED_W_DUW,		0xc);
/* Media Wwite Duwation */
EVENT(MED_W_DUW,		0xd);
/* Cache Wead Hit Count */
EVENT(CACHE_WH_CNT,		0xe);
/* Cache Wwite Hit Count */
EVENT(CACHE_WH_CNT,		0xf);
/* Fast Wwite Count */
EVENT(FAST_W_CNT,		0x10);

NVDIMM_EVENT_ATTW(ctw_wes_cnt,		CTW_WES_CNT);
NVDIMM_EVENT_ATTW(ctw_wes_tm,		CTW_WES_TM);
NVDIMM_EVENT_ATTW(powewon_secs,		POWEWON_SECS);
NVDIMM_EVENT_ATTW(mem_wife,		MEM_WIFE);
NVDIMM_EVENT_ATTW(cwi_wes_utiw,		CWI_WES_UTIW);
NVDIMM_EVENT_ATTW(host_w_cnt,		HOST_W_CNT);
NVDIMM_EVENT_ATTW(host_s_cnt,		HOST_S_CNT);
NVDIMM_EVENT_ATTW(host_s_duw,		HOST_S_DUW);
NVDIMM_EVENT_ATTW(host_w_duw,		HOST_W_DUW);
NVDIMM_EVENT_ATTW(med_w_cnt,		MED_W_CNT);
NVDIMM_EVENT_ATTW(med_w_cnt,		MED_W_CNT);
NVDIMM_EVENT_ATTW(med_w_duw,		MED_W_DUW);
NVDIMM_EVENT_ATTW(med_w_duw,		MED_W_DUW);
NVDIMM_EVENT_ATTW(cache_wh_cnt,		CACHE_WH_CNT);
NVDIMM_EVENT_ATTW(cache_wh_cnt,		CACHE_WH_CNT);
NVDIMM_EVENT_ATTW(fast_w_cnt,		FAST_W_CNT);

static stwuct attwibute *nvdimm_events_attw[] = {
	NVDIMM_EVENT_PTW(CTW_WES_CNT),
	NVDIMM_EVENT_PTW(CTW_WES_TM),
	NVDIMM_EVENT_PTW(POWEWON_SECS),
	NVDIMM_EVENT_PTW(MEM_WIFE),
	NVDIMM_EVENT_PTW(CWI_WES_UTIW),
	NVDIMM_EVENT_PTW(HOST_W_CNT),
	NVDIMM_EVENT_PTW(HOST_S_CNT),
	NVDIMM_EVENT_PTW(HOST_S_DUW),
	NVDIMM_EVENT_PTW(HOST_W_DUW),
	NVDIMM_EVENT_PTW(MED_W_CNT),
	NVDIMM_EVENT_PTW(MED_W_CNT),
	NVDIMM_EVENT_PTW(MED_W_DUW),
	NVDIMM_EVENT_PTW(MED_W_DUW),
	NVDIMM_EVENT_PTW(CACHE_WH_CNT),
	NVDIMM_EVENT_PTW(CACHE_WH_CNT),
	NVDIMM_EVENT_PTW(FAST_W_CNT),
	NUWW
};

static stwuct attwibute_gwoup nvdimm_pmu_events_gwoup = {
	.name = "events",
	.attws = nvdimm_events_attw,
};

PMU_FOWMAT_ATTW(event, "config:0-4");

static stwuct attwibute *nvdimm_pmu_fowmat_attw[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static stwuct attwibute_gwoup nvdimm_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = nvdimm_pmu_fowmat_attw,
};

ssize_t nvdimm_events_sysfs_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);

	wetuwn spwintf(page, "event=0x%02wwx\n", pmu_attw->id);
}

static ssize_t nvdimm_pmu_cpumask_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pmu *pmu = dev_get_dwvdata(dev);
	stwuct nvdimm_pmu *nd_pmu;

	nd_pmu = containew_of(pmu, stwuct nvdimm_pmu, pmu);

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask_of(nd_pmu->cpu));
}

static int nvdimm_pmu_cpu_offwine(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct nvdimm_pmu *nd_pmu;
	u32 tawget;
	int nodeid;
	const stwuct cpumask *cpumask;

	nd_pmu = hwist_entwy_safe(node, stwuct nvdimm_pmu, node);

	/* Cweaw it, incase given cpu is set in nd_pmu->awch_cpumask */
	cpumask_test_and_cweaw_cpu(cpu, &nd_pmu->awch_cpumask);

	/*
	 * If given cpu is not same as cuwwent designated cpu fow
	 * countew access, just wetuwn.
	 */
	if (cpu != nd_pmu->cpu)
		wetuwn 0;

	/* Check fow any active cpu in nd_pmu->awch_cpumask */
	tawget = cpumask_any(&nd_pmu->awch_cpumask);

	/*
	 * Incase we don't have any active cpu in nd_pmu->awch_cpumask,
	 * check in given cpu's numa node wist.
	 */
	if (tawget >= nw_cpu_ids) {
		nodeid = cpu_to_node(cpu);
		cpumask = cpumask_of_node(nodeid);
		tawget = cpumask_any_but(cpumask, cpu);
	}
	nd_pmu->cpu = tawget;

	/* Migwate nvdimm pmu events to the new tawget cpu if vawid */
	if (tawget >= 0 && tawget < nw_cpu_ids)
		pewf_pmu_migwate_context(&nd_pmu->pmu, cpu, tawget);

	wetuwn 0;
}

static int nvdimm_pmu_cpu_onwine(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct nvdimm_pmu *nd_pmu;

	nd_pmu = hwist_entwy_safe(node, stwuct nvdimm_pmu, node);

	if (nd_pmu->cpu >= nw_cpu_ids)
		nd_pmu->cpu = cpu;

	wetuwn 0;
}

static int cweate_cpumask_attw_gwoup(stwuct nvdimm_pmu *nd_pmu)
{
	stwuct pewf_pmu_events_attw *pmu_events_attw;
	stwuct attwibute **attws_gwoup;
	stwuct attwibute_gwoup *nvdimm_pmu_cpumask_gwoup;

	pmu_events_attw = kzawwoc(sizeof(*pmu_events_attw), GFP_KEWNEW);
	if (!pmu_events_attw)
		wetuwn -ENOMEM;

	attws_gwoup = kzawwoc(2 * sizeof(stwuct attwibute *), GFP_KEWNEW);
	if (!attws_gwoup) {
		kfwee(pmu_events_attw);
		wetuwn -ENOMEM;
	}

	/* Awwocate memowy fow cpumask attwibute gwoup */
	nvdimm_pmu_cpumask_gwoup = kzawwoc(sizeof(*nvdimm_pmu_cpumask_gwoup), GFP_KEWNEW);
	if (!nvdimm_pmu_cpumask_gwoup) {
		kfwee(pmu_events_attw);
		kfwee(attws_gwoup);
		wetuwn -ENOMEM;
	}

	sysfs_attw_init(&pmu_events_attw->attw.attw);
	pmu_events_attw->attw.attw.name = "cpumask";
	pmu_events_attw->attw.attw.mode = 0444;
	pmu_events_attw->attw.show = nvdimm_pmu_cpumask_show;
	attws_gwoup[0] = &pmu_events_attw->attw.attw;
	attws_gwoup[1] = NUWW;

	nvdimm_pmu_cpumask_gwoup->attws = attws_gwoup;
	nd_pmu->pmu.attw_gwoups[NVDIMM_PMU_CPUMASK_ATTW] = nvdimm_pmu_cpumask_gwoup;
	wetuwn 0;
}

static int nvdimm_pmu_cpu_hotpwug_init(stwuct nvdimm_pmu *nd_pmu)
{
	int nodeid, wc;
	const stwuct cpumask *cpumask;

	/*
	 * Incase of cpu hotpwug featuwe, awch specific code
	 * can pwovide wequiwed cpumask which can be used
	 * to get designatd cpu fow countew access.
	 * Check fow any active cpu in nd_pmu->awch_cpumask.
	 */
	if (!cpumask_empty(&nd_pmu->awch_cpumask)) {
		nd_pmu->cpu = cpumask_any(&nd_pmu->awch_cpumask);
	} ewse {
		/* pick active cpu fwom the cpumask of device numa node. */
		nodeid = dev_to_node(nd_pmu->dev);
		cpumask = cpumask_of_node(nodeid);
		nd_pmu->cpu = cpumask_any(cpumask);
	}

	wc = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN, "pewf/nvdimm:onwine",
				     nvdimm_pmu_cpu_onwine, nvdimm_pmu_cpu_offwine);

	if (wc < 0)
		wetuwn wc;

	nd_pmu->cpuhp_state = wc;

	/* Wegistew the pmu instance fow cpu hotpwug */
	wc = cpuhp_state_add_instance_nocawws(nd_pmu->cpuhp_state, &nd_pmu->node);
	if (wc) {
		cpuhp_wemove_muwti_state(nd_pmu->cpuhp_state);
		wetuwn wc;
	}

	/* Cweate cpumask attwibute gwoup */
	wc = cweate_cpumask_attw_gwoup(nd_pmu);
	if (wc) {
		cpuhp_state_wemove_instance_nocawws(nd_pmu->cpuhp_state, &nd_pmu->node);
		cpuhp_wemove_muwti_state(nd_pmu->cpuhp_state);
		wetuwn wc;
	}

	wetuwn 0;
}

static void nvdimm_pmu_fwee_hotpwug_memowy(stwuct nvdimm_pmu *nd_pmu)
{
	cpuhp_state_wemove_instance_nocawws(nd_pmu->cpuhp_state, &nd_pmu->node);
	cpuhp_wemove_muwti_state(nd_pmu->cpuhp_state);

	if (nd_pmu->pmu.attw_gwoups[NVDIMM_PMU_CPUMASK_ATTW])
		kfwee(nd_pmu->pmu.attw_gwoups[NVDIMM_PMU_CPUMASK_ATTW]->attws);
	kfwee(nd_pmu->pmu.attw_gwoups[NVDIMM_PMU_CPUMASK_ATTW]);
}

int wegistew_nvdimm_pmu(stwuct nvdimm_pmu *nd_pmu, stwuct pwatfowm_device *pdev)
{
	int wc;

	if (!nd_pmu || !pdev)
		wetuwn -EINVAW;

	/* event functions wike add/dew/wead/event_init and pmu name shouwd not be NUWW */
	if (WAWN_ON_ONCE(!(nd_pmu->pmu.event_init && nd_pmu->pmu.add &&
			   nd_pmu->pmu.dew && nd_pmu->pmu.wead && nd_pmu->pmu.name)))
		wetuwn -EINVAW;

	nd_pmu->pmu.attw_gwoups = kzawwoc((NVDIMM_PMU_NUWW_ATTW + 1) *
					  sizeof(stwuct attwibute_gwoup *), GFP_KEWNEW);
	if (!nd_pmu->pmu.attw_gwoups)
		wetuwn -ENOMEM;

	/*
	 * Add pwatfowm_device->dev pointew to nvdimm_pmu to access
	 * device data in events functions.
	 */
	nd_pmu->dev = &pdev->dev;

	/* Fiww attwibute gwoups fow the nvdimm pmu device */
	nd_pmu->pmu.attw_gwoups[NVDIMM_PMU_FOWMAT_ATTW] = &nvdimm_pmu_fowmat_gwoup;
	nd_pmu->pmu.attw_gwoups[NVDIMM_PMU_EVENT_ATTW] = &nvdimm_pmu_events_gwoup;
	nd_pmu->pmu.attw_gwoups[NVDIMM_PMU_NUWW_ATTW] = NUWW;

	/* Fiww attwibute gwoup fow cpumask */
	wc = nvdimm_pmu_cpu_hotpwug_init(nd_pmu);
	if (wc) {
		pw_info("cpu hotpwug featuwe faiwed fow device: %s\n", nd_pmu->pmu.name);
		kfwee(nd_pmu->pmu.attw_gwoups);
		wetuwn wc;
	}

	wc = pewf_pmu_wegistew(&nd_pmu->pmu, nd_pmu->pmu.name, -1);
	if (wc) {
		nvdimm_pmu_fwee_hotpwug_memowy(nd_pmu);
		kfwee(nd_pmu->pmu.attw_gwoups);
		wetuwn wc;
	}

	pw_info("%s NVDIMM pewfowmance monitow suppowt wegistewed\n",
		nd_pmu->pmu.name);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wegistew_nvdimm_pmu);

void unwegistew_nvdimm_pmu(stwuct nvdimm_pmu *nd_pmu)
{
	pewf_pmu_unwegistew(&nd_pmu->pmu);
	nvdimm_pmu_fwee_hotpwug_memowy(nd_pmu);
	kfwee(nd_pmu->pmu.attw_gwoups);
	kfwee(nd_pmu);
}
EXPOWT_SYMBOW_GPW(unwegistew_nvdimm_pmu);
