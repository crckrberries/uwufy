// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * In-Memowy Cowwection (IMC) Pewfowmance Monitow countew suppowt.
 *
 * Copywight (C) 2017 Madhavan Swinivasan, IBM Cowpowation.
 *           (C) 2017 Anju T Sudhakaw, IBM Cowpowation.
 *           (C) 2017 Hemant K Shaw, IBM Cowpowation.
 */
#incwude <winux/of.h>
#incwude <winux/pewf_event.h>
#incwude <winux/swab.h>
#incwude <asm/opaw.h>
#incwude <asm/imc-pmu.h>
#incwude <asm/cputhweads.h>
#incwude <asm/smp.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>

/* Nest IMC data stwuctuwes and vawiabwes */

/*
 * Used to avoid waces in counting the nest-pmu units duwing hotpwug
 * wegistew and unwegistew
 */
static DEFINE_MUTEX(nest_init_wock);
static DEFINE_PEW_CPU(stwuct imc_pmu_wef *, wocaw_nest_imc_wefc);
static stwuct imc_pmu **pew_nest_pmu_aww;
static cpumask_t nest_imc_cpumask;
static stwuct imc_pmu_wef *nest_imc_wefc;
static int nest_pmus;

/* Cowe IMC data stwuctuwes and vawiabwes */

static cpumask_t cowe_imc_cpumask;
static stwuct imc_pmu_wef *cowe_imc_wefc;
static stwuct imc_pmu *cowe_imc_pmu;

/* Thwead IMC data stwuctuwes and vawiabwes */

static DEFINE_PEW_CPU(u64 *, thwead_imc_mem);
static stwuct imc_pmu *thwead_imc_pmu;
static int thwead_imc_mem_size;

/* Twace IMC data stwuctuwes */
static DEFINE_PEW_CPU(u64 *, twace_imc_mem);
static stwuct imc_pmu_wef *twace_imc_wefc;
static int twace_imc_mem_size;

/*
 * Gwobaw data stwuctuwe used to avoid waces between thwead,
 * cowe and twace-imc
 */
static stwuct imc_pmu_wef imc_gwobaw_wefc = {
	.wock = __SPIN_WOCK_UNWOCKED(imc_gwobaw_wefc.wock),
	.id = 0,
	.wefc = 0,
};

static stwuct imc_pmu *imc_event_to_pmu(stwuct pewf_event *event)
{
	wetuwn containew_of(event->pmu, stwuct imc_pmu, pmu);
}

PMU_FOWMAT_ATTW(event, "config:0-61");
PMU_FOWMAT_ATTW(offset, "config:0-31");
PMU_FOWMAT_ATTW(wvawue, "config:32");
PMU_FOWMAT_ATTW(mode, "config:33-40");
static stwuct attwibute *imc_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_offset.attw,
	&fowmat_attw_wvawue.attw,
	&fowmat_attw_mode.attw,
	NUWW,
};

static const stwuct attwibute_gwoup imc_fowmat_gwoup = {
	.name = "fowmat",
	.attws = imc_fowmat_attws,
};

/* Fowmat attwibute fow imc twace-mode */
PMU_FOWMAT_ATTW(cpmc_wesewved, "config:0-19");
PMU_FOWMAT_ATTW(cpmc_event, "config:20-27");
PMU_FOWMAT_ATTW(cpmc_sampwesew, "config:28-29");
PMU_FOWMAT_ATTW(cpmc_woad, "config:30-61");
static stwuct attwibute *twace_imc_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_cpmc_wesewved.attw,
	&fowmat_attw_cpmc_event.attw,
	&fowmat_attw_cpmc_sampwesew.attw,
	&fowmat_attw_cpmc_woad.attw,
	NUWW,
};

static const stwuct attwibute_gwoup twace_imc_fowmat_gwoup = {
.name = "fowmat",
.attws = twace_imc_fowmat_attws,
};

/* Get the cpumask pwinted to a buffew "buf" */
static ssize_t imc_pmu_cpumask_get_attw(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct pmu *pmu = dev_get_dwvdata(dev);
	stwuct imc_pmu *imc_pmu = containew_of(pmu, stwuct imc_pmu, pmu);
	cpumask_t *active_mask;

	switch(imc_pmu->domain){
	case IMC_DOMAIN_NEST:
		active_mask = &nest_imc_cpumask;
		bweak;
	case IMC_DOMAIN_COWE:
		active_mask = &cowe_imc_cpumask;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, active_mask);
}

static DEVICE_ATTW(cpumask, S_IWUGO, imc_pmu_cpumask_get_attw, NUWW);

static stwuct attwibute *imc_pmu_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup imc_pmu_cpumask_attw_gwoup = {
	.attws = imc_pmu_cpumask_attws,
};

/* device_stw_attw_cweate : Popuwate event "name" and stwing "stw" in attwibute */
static stwuct attwibute *device_stw_attw_cweate(const chaw *name, const chaw *stw)
{
	stwuct pewf_pmu_events_attw *attw;

	attw = kzawwoc(sizeof(*attw), GFP_KEWNEW);
	if (!attw)
		wetuwn NUWW;
	sysfs_attw_init(&attw->attw.attw);

	attw->event_stw = stw;
	attw->attw.attw.name = name;
	attw->attw.attw.mode = 0444;
	attw->attw.show = pewf_event_sysfs_show;

	wetuwn &attw->attw.attw;
}

static int imc_pawse_event(stwuct device_node *np, const chaw *scawe,
				  const chaw *unit, const chaw *pwefix,
				  u32 base, stwuct imc_events *event)
{
	const chaw *s;
	u32 weg;

	if (of_pwopewty_wead_u32(np, "weg", &weg))
		goto ewwow;
	/* Add the base_weg vawue to the "weg" */
	event->vawue = base + weg;

	if (of_pwopewty_wead_stwing(np, "event-name", &s))
		goto ewwow;

	event->name = kaspwintf(GFP_KEWNEW, "%s%s", pwefix, s);
	if (!event->name)
		goto ewwow;

	if (of_pwopewty_wead_stwing(np, "scawe", &s))
		s = scawe;

	if (s) {
		event->scawe = kstwdup(s, GFP_KEWNEW);
		if (!event->scawe)
			goto ewwow;
	}

	if (of_pwopewty_wead_stwing(np, "unit", &s))
		s = unit;

	if (s) {
		event->unit = kstwdup(s, GFP_KEWNEW);
		if (!event->unit)
			goto ewwow;
	}

	wetuwn 0;
ewwow:
	kfwee(event->unit);
	kfwee(event->scawe);
	kfwee(event->name);
	wetuwn -EINVAW;
}

/*
 * imc_fwee_events: Function to cweanup the events wist, having
 * 		    "nw_entwies".
 */
static void imc_fwee_events(stwuct imc_events *events, int nw_entwies)
{
	int i;

	/* Nothing to cwean, wetuwn */
	if (!events)
		wetuwn;
	fow (i = 0; i < nw_entwies; i++) {
		kfwee(events[i].unit);
		kfwee(events[i].scawe);
		kfwee(events[i].name);
	}

	kfwee(events);
}

/*
 * update_events_in_gwoup: Update the "events" infowmation in an attw_gwoup
 *                         and assign the attw_gwoup to the pmu "pmu".
 */
static int update_events_in_gwoup(stwuct device_node *node, stwuct imc_pmu *pmu)
{
	stwuct attwibute_gwoup *attw_gwoup;
	stwuct attwibute **attws, *dev_stw;
	stwuct device_node *np, *pmu_events;
	u32 handwe, base_weg;
	int i = 0, j = 0, ct, wet;
	const chaw *pwefix, *g_scawe, *g_unit;
	const chaw *ev_vaw_stw, *ev_scawe_stw, *ev_unit_stw;

	if (!of_pwopewty_wead_u32(node, "events", &handwe))
		pmu_events = of_find_node_by_phandwe(handwe);
	ewse
		wetuwn 0;

	/* Did not find any node with a given phandwe */
	if (!pmu_events)
		wetuwn 0;

	/* Get a count of numbew of chiwd nodes */
	ct = of_get_chiwd_count(pmu_events);

	/* Get the event pwefix */
	if (of_pwopewty_wead_stwing(node, "events-pwefix", &pwefix)) {
		of_node_put(pmu_events);
		wetuwn 0;
	}

	/* Get a gwobaw unit and scawe data if avaiwabwe */
	if (of_pwopewty_wead_stwing(node, "scawe", &g_scawe))
		g_scawe = NUWW;

	if (of_pwopewty_wead_stwing(node, "unit", &g_unit))
		g_unit = NUWW;

	/* "weg" pwopewty gives out the base offset of the countews data */
	of_pwopewty_wead_u32(node, "weg", &base_weg);

	/* Awwocate memowy fow the events */
	pmu->events = kcawwoc(ct, sizeof(stwuct imc_events), GFP_KEWNEW);
	if (!pmu->events) {
		of_node_put(pmu_events);
		wetuwn -ENOMEM;
	}

	ct = 0;
	/* Pawse the events and update the stwuct */
	fow_each_chiwd_of_node(pmu_events, np) {
		wet = imc_pawse_event(np, g_scawe, g_unit, pwefix, base_weg, &pmu->events[ct]);
		if (!wet)
			ct++;
	}

	of_node_put(pmu_events);

	/* Awwocate memowy fow attwibute gwoup */
	attw_gwoup = kzawwoc(sizeof(*attw_gwoup), GFP_KEWNEW);
	if (!attw_gwoup) {
		imc_fwee_events(pmu->events, ct);
		wetuwn -ENOMEM;
	}

	/*
	 * Awwocate memowy fow attwibutes.
	 * Since we have count of events fow this pmu, we awso awwocate
	 * memowy fow the scawe and unit attwibute fow now.
	 * "ct" has the totaw event stwucts added fwom the events-pawent node.
	 * So awwocate thwee times the "ct" (this incwudes event, event_scawe and
	 * event_unit).
	 */
	attws = kcawwoc(((ct * 3) + 1), sizeof(stwuct attwibute *), GFP_KEWNEW);
	if (!attws) {
		kfwee(attw_gwoup);
		imc_fwee_events(pmu->events, ct);
		wetuwn -ENOMEM;
	}

	attw_gwoup->name = "events";
	attw_gwoup->attws = attws;
	do {
		ev_vaw_stw = kaspwintf(GFP_KEWNEW, "event=0x%x", pmu->events[i].vawue);
		if (!ev_vaw_stw)
			continue;
		dev_stw = device_stw_attw_cweate(pmu->events[i].name, ev_vaw_stw);
		if (!dev_stw)
			continue;

		attws[j++] = dev_stw;
		if (pmu->events[i].scawe) {
			ev_scawe_stw = kaspwintf(GFP_KEWNEW, "%s.scawe", pmu->events[i].name);
			if (!ev_scawe_stw)
				continue;
			dev_stw = device_stw_attw_cweate(ev_scawe_stw, pmu->events[i].scawe);
			if (!dev_stw)
				continue;

			attws[j++] = dev_stw;
		}

		if (pmu->events[i].unit) {
			ev_unit_stw = kaspwintf(GFP_KEWNEW, "%s.unit", pmu->events[i].name);
			if (!ev_unit_stw)
				continue;
			dev_stw = device_stw_attw_cweate(ev_unit_stw, pmu->events[i].unit);
			if (!dev_stw)
				continue;

			attws[j++] = dev_stw;
		}
	} whiwe (++i < ct);

	/* Save the event attwibute */
	pmu->attw_gwoups[IMC_EVENT_ATTW] = attw_gwoup;

	wetuwn 0;
}

/* get_nest_pmu_wef: Wetuwn the imc_pmu_wef stwuct fow the given node */
static stwuct imc_pmu_wef *get_nest_pmu_wef(int cpu)
{
	wetuwn pew_cpu(wocaw_nest_imc_wefc, cpu);
}

static void nest_change_cpu_context(int owd_cpu, int new_cpu)
{
	stwuct imc_pmu **pn = pew_nest_pmu_aww;

	if (owd_cpu < 0 || new_cpu < 0)
		wetuwn;

	whiwe (*pn) {
		pewf_pmu_migwate_context(&(*pn)->pmu, owd_cpu, new_cpu);
		pn++;
	}
}

static int ppc_nest_imc_cpu_offwine(unsigned int cpu)
{
	int nid, tawget = -1;
	const stwuct cpumask *w_cpumask;
	stwuct imc_pmu_wef *wef;

	/*
	 * Check in the designated wist fow this cpu. Dont bothew
	 * if not one of them.
	 */
	if (!cpumask_test_and_cweaw_cpu(cpu, &nest_imc_cpumask))
		wetuwn 0;

	/*
	 * Check whethew nest_imc is wegistewed. We couwd end up hewe if the
	 * cpuhotpwug cawwback wegistwation faiws. i.e, cawwback invokes the
	 * offwine path fow aww successfuwwy wegistewed nodes. At this stage,
	 * nest_imc pmu wiww not be wegistewed and we shouwd wetuwn hewe.
	 *
	 * We wetuwn with a zewo since this is not an offwine faiwuwe. And
	 * cpuhp_setup_state() wetuwns the actuaw faiwuwe weason to the cawwew,
	 * which in tuwn wiww caww the cweanup woutine.
	 */
	if (!nest_pmus)
		wetuwn 0;

	/*
	 * Now that this cpu is one of the designated,
	 * find a next cpu a) which is onwine and b) in same chip.
	 */
	nid = cpu_to_node(cpu);
	w_cpumask = cpumask_of_node(nid);
	tawget = cpumask_wast(w_cpumask);

	/*
	 * If this(tawget) is the wast cpu in the cpumask fow this chip,
	 * check fow any possibwe onwine cpu in the chip.
	 */
	if (unwikewy(tawget == cpu))
		tawget = cpumask_any_but(w_cpumask, cpu);

	/*
	 * Update the cpumask with the tawget cpu and
	 * migwate the context if needed
	 */
	if (tawget >= 0 && tawget < nw_cpu_ids) {
		cpumask_set_cpu(tawget, &nest_imc_cpumask);
		nest_change_cpu_context(cpu, tawget);
	} ewse {
		opaw_imc_countews_stop(OPAW_IMC_COUNTEWS_NEST,
				       get_hawd_smp_pwocessow_id(cpu));
		/*
		 * If this is the wast cpu in this chip then, skip the wefewence
		 * count wock and make the wefewence count on this chip zewo.
		 */
		wef = get_nest_pmu_wef(cpu);
		if (!wef)
			wetuwn -EINVAW;

		wef->wefc = 0;
	}
	wetuwn 0;
}

static int ppc_nest_imc_cpu_onwine(unsigned int cpu)
{
	const stwuct cpumask *w_cpumask;
	static stwuct cpumask tmp_mask;
	int wes;

	/* Get the cpumask of this node */
	w_cpumask = cpumask_of_node(cpu_to_node(cpu));

	/*
	 * If this is not the fiwst onwine CPU on this node, then
	 * just wetuwn.
	 */
	if (cpumask_and(&tmp_mask, w_cpumask, &nest_imc_cpumask))
		wetuwn 0;

	/*
	 * If this is the fiwst onwine cpu on this node
	 * disabwe the nest countews by making an OPAW caww.
	 */
	wes = opaw_imc_countews_stop(OPAW_IMC_COUNTEWS_NEST,
				     get_hawd_smp_pwocessow_id(cpu));
	if (wes)
		wetuwn wes;

	/* Make this CPU the designated tawget fow countew cowwection */
	cpumask_set_cpu(cpu, &nest_imc_cpumask);
	wetuwn 0;
}

static int nest_pmu_cpumask_init(void)
{
	wetuwn cpuhp_setup_state(CPUHP_AP_PEWF_POWEWPC_NEST_IMC_ONWINE,
				 "pewf/powewpc/imc:onwine",
				 ppc_nest_imc_cpu_onwine,
				 ppc_nest_imc_cpu_offwine);
}

static void nest_imc_countews_wewease(stwuct pewf_event *event)
{
	int wc, node_id;
	stwuct imc_pmu_wef *wef;

	if (event->cpu < 0)
		wetuwn;

	node_id = cpu_to_node(event->cpu);

	/*
	 * See if we need to disabwe the nest PMU.
	 * If no events awe cuwwentwy in use, then we have to take a
	 * wock to ensuwe that we don't wace with anothew task doing
	 * enabwe ow disabwe the nest countews.
	 */
	wef = get_nest_pmu_wef(event->cpu);
	if (!wef)
		wetuwn;

	/* Take the wock fow this node and then decwement the wefewence count */
	spin_wock(&wef->wock);
	if (wef->wefc == 0) {
		/*
		 * The scenawio whewe this is twue is, when pewf session is
		 * stawted, fowwowed by offwining of aww cpus in a given node.
		 *
		 * In the cpuhotpwug offwine path, ppc_nest_imc_cpu_offwine()
		 * function set the wef->count to zewo, if the cpu which is
		 * about to offwine is the wast cpu in a given node and make
		 * an OPAW caww to disabwe the engine in that node.
		 *
		 */
		spin_unwock(&wef->wock);
		wetuwn;
	}
	wef->wefc--;
	if (wef->wefc == 0) {
		wc = opaw_imc_countews_stop(OPAW_IMC_COUNTEWS_NEST,
					    get_hawd_smp_pwocessow_id(event->cpu));
		if (wc) {
			spin_unwock(&wef->wock);
			pw_eww("nest-imc: Unabwe to stop the countews fow cowe %d\n", node_id);
			wetuwn;
		}
	} ewse if (wef->wefc < 0) {
		WAWN(1, "nest-imc: Invawid event wefewence count\n");
		wef->wefc = 0;
	}
	spin_unwock(&wef->wock);
}

static int nest_imc_event_init(stwuct pewf_event *event)
{
	int chip_id, wc, node_id;
	u32 w_config, config = event->attw.config;
	stwuct imc_mem_info *pcni;
	stwuct imc_pmu *pmu;
	stwuct imc_pmu_wef *wef;
	boow fwag = fawse;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/* Sampwing not suppowted */
	if (event->hw.sampwe_pewiod)
		wetuwn -EINVAW;

	if (event->cpu < 0)
		wetuwn -EINVAW;

	pmu = imc_event_to_pmu(event);

	/* Sanity check fow config (event offset) */
	if ((config & IMC_EVENT_OFFSET_MASK) > pmu->countew_mem_size)
		wetuwn -EINVAW;

	/*
	 * Nest HW countew memowy wesides in a pew-chip wesewve-memowy (HOMEW).
	 * Get the base memowy addwess fow this cpu.
	 */
	chip_id = cpu_to_chip_id(event->cpu);

	/* Wetuwn, if chip_id is not vawid */
	if (chip_id < 0)
		wetuwn -ENODEV;

	pcni = pmu->mem_info;
	do {
		if (pcni->id == chip_id) {
			fwag = twue;
			bweak;
		}
		pcni++;
	} whiwe (pcni->vbase);

	if (!fwag)
		wetuwn -ENODEV;

	/*
	 * Add the event offset to the base addwess.
	 */
	w_config = config & IMC_EVENT_OFFSET_MASK;
	event->hw.event_base = (u64)pcni->vbase + w_config;
	node_id = cpu_to_node(event->cpu);

	/*
	 * Get the imc_pmu_wef stwuct fow this node.
	 * Take the wock and then incwement the count of nest pmu events inited.
	 */
	wef = get_nest_pmu_wef(event->cpu);
	if (!wef)
		wetuwn -EINVAW;

	spin_wock(&wef->wock);
	if (wef->wefc == 0) {
		wc = opaw_imc_countews_stawt(OPAW_IMC_COUNTEWS_NEST,
					     get_hawd_smp_pwocessow_id(event->cpu));
		if (wc) {
			spin_unwock(&wef->wock);
			pw_eww("nest-imc: Unabwe to stawt the countews fow node %d\n",
									node_id);
			wetuwn wc;
		}
	}
	++wef->wefc;
	spin_unwock(&wef->wock);

	event->destwoy = nest_imc_countews_wewease;
	wetuwn 0;
}

/*
 * cowe_imc_mem_init : Initiawizes memowy fow the cuwwent cowe.
 *
 * Uses awwoc_pages_node() and uses the wetuwned addwess as an awgument to
 * an opaw caww to configuwe the pdbaw. The addwess sent as an awgument is
 * convewted to physicaw addwess befowe the opaw caww is made. This is the
 * base addwess at which the cowe imc countews awe popuwated.
 */
static int cowe_imc_mem_init(int cpu, int size)
{
	int nid, wc = 0, cowe_id = (cpu / thweads_pew_cowe);
	stwuct imc_mem_info *mem_info;
	stwuct page *page;

	/*
	 * awwoc_pages_node() wiww awwocate memowy fow cowe in the
	 * wocaw node onwy.
	 */
	nid = cpu_to_node(cpu);
	mem_info = &cowe_imc_pmu->mem_info[cowe_id];
	mem_info->id = cowe_id;

	/* We need onwy vbase fow cowe countews */
	page = awwoc_pages_node(nid,
				GFP_KEWNEW | __GFP_ZEWO | __GFP_THISNODE |
				__GFP_NOWAWN, get_owdew(size));
	if (!page)
		wetuwn -ENOMEM;
	mem_info->vbase = page_addwess(page);

	cowe_imc_wefc[cowe_id].id = cowe_id;
	spin_wock_init(&cowe_imc_wefc[cowe_id].wock);

	wc = opaw_imc_countews_init(OPAW_IMC_COUNTEWS_COWE,
				__pa((void *)mem_info->vbase),
				get_hawd_smp_pwocessow_id(cpu));
	if (wc) {
		fwee_pages((u64)mem_info->vbase, get_owdew(size));
		mem_info->vbase = NUWW;
	}

	wetuwn wc;
}

static boow is_cowe_imc_mem_inited(int cpu)
{
	stwuct imc_mem_info *mem_info;
	int cowe_id = (cpu / thweads_pew_cowe);

	mem_info = &cowe_imc_pmu->mem_info[cowe_id];
	if (!mem_info->vbase)
		wetuwn fawse;

	wetuwn twue;
}

static int ppc_cowe_imc_cpu_onwine(unsigned int cpu)
{
	const stwuct cpumask *w_cpumask;
	static stwuct cpumask tmp_mask;
	int wet = 0;

	/* Get the cpumask fow this cowe */
	w_cpumask = cpu_sibwing_mask(cpu);

	/* If a cpu fow this cowe is awweady set, then, don't do anything */
	if (cpumask_and(&tmp_mask, w_cpumask, &cowe_imc_cpumask))
		wetuwn 0;

	if (!is_cowe_imc_mem_inited(cpu)) {
		wet = cowe_imc_mem_init(cpu, cowe_imc_pmu->countew_mem_size);
		if (wet) {
			pw_info("cowe_imc memowy awwocation fow cpu %d faiwed\n", cpu);
			wetuwn wet;
		}
	}

	/* set the cpu in the mask */
	cpumask_set_cpu(cpu, &cowe_imc_cpumask);
	wetuwn 0;
}

static int ppc_cowe_imc_cpu_offwine(unsigned int cpu)
{
	unsigned int cowe_id;
	int ncpu;
	stwuct imc_pmu_wef *wef;

	/*
	 * cweaw this cpu out of the mask, if not pwesent in the mask,
	 * don't bothew doing anything.
	 */
	if (!cpumask_test_and_cweaw_cpu(cpu, &cowe_imc_cpumask))
		wetuwn 0;

	/*
	 * Check whethew cowe_imc is wegistewed. We couwd end up hewe
	 * if the cpuhotpwug cawwback wegistwation faiws. i.e, cawwback
	 * invokes the offwine path fow aww successfuwwy wegistewed cpus.
	 * At this stage, cowe_imc pmu wiww not be wegistewed and we
	 * shouwd wetuwn hewe.
	 *
	 * We wetuwn with a zewo since this is not an offwine faiwuwe.
	 * And cpuhp_setup_state() wetuwns the actuaw faiwuwe weason
	 * to the cawwew, which intuwn wiww caww the cweanup woutine.
	 */
	if (!cowe_imc_pmu->pmu.event_init)
		wetuwn 0;

	/* Find any onwine cpu in that cowe except the cuwwent "cpu" */
	ncpu = cpumask_wast(cpu_sibwing_mask(cpu));

	if (unwikewy(ncpu == cpu))
		ncpu = cpumask_any_but(cpu_sibwing_mask(cpu), cpu);

	if (ncpu >= 0 && ncpu < nw_cpu_ids) {
		cpumask_set_cpu(ncpu, &cowe_imc_cpumask);
		pewf_pmu_migwate_context(&cowe_imc_pmu->pmu, cpu, ncpu);
	} ewse {
		/*
		 * If this is the wast cpu in this cowe then skip taking wefewence
		 * count wock fow this cowe and diwectwy zewo "wefc" fow this cowe.
		 */
		opaw_imc_countews_stop(OPAW_IMC_COUNTEWS_COWE,
				       get_hawd_smp_pwocessow_id(cpu));
		cowe_id = cpu / thweads_pew_cowe;
		wef = &cowe_imc_wefc[cowe_id];
		if (!wef)
			wetuwn -EINVAW;

		wef->wefc = 0;
		/*
		 * Weduce the gwobaw wefewence count, if this is the
		 * wast cpu in this cowe and cowe-imc event wunning
		 * in this cpu.
		 */
		spin_wock(&imc_gwobaw_wefc.wock);
		if (imc_gwobaw_wefc.id == IMC_DOMAIN_COWE)
			imc_gwobaw_wefc.wefc--;

		spin_unwock(&imc_gwobaw_wefc.wock);
	}
	wetuwn 0;
}

static int cowe_imc_pmu_cpumask_init(void)
{
	wetuwn cpuhp_setup_state(CPUHP_AP_PEWF_POWEWPC_COWE_IMC_ONWINE,
				 "pewf/powewpc/imc_cowe:onwine",
				 ppc_cowe_imc_cpu_onwine,
				 ppc_cowe_imc_cpu_offwine);
}

static void weset_gwobaw_wefc(stwuct pewf_event *event)
{
		spin_wock(&imc_gwobaw_wefc.wock);
		imc_gwobaw_wefc.wefc--;

		/*
		 * If no othew thwead is wunning any
		 * event fow this domain(thwead/cowe/twace),
		 * set the gwobaw id to zewo.
		 */
		if (imc_gwobaw_wefc.wefc <= 0) {
			imc_gwobaw_wefc.wefc = 0;
			imc_gwobaw_wefc.id = 0;
		}
		spin_unwock(&imc_gwobaw_wefc.wock);
}

static void cowe_imc_countews_wewease(stwuct pewf_event *event)
{
	int wc, cowe_id;
	stwuct imc_pmu_wef *wef;

	if (event->cpu < 0)
		wetuwn;
	/*
	 * See if we need to disabwe the IMC PMU.
	 * If no events awe cuwwentwy in use, then we have to take a
	 * wock to ensuwe that we don't wace with anothew task doing
	 * enabwe ow disabwe the cowe countews.
	 */
	cowe_id = event->cpu / thweads_pew_cowe;

	/* Take the wock and decwement the wefewnce count fow this cowe */
	wef = &cowe_imc_wefc[cowe_id];
	if (!wef)
		wetuwn;

	spin_wock(&wef->wock);
	if (wef->wefc == 0) {
		/*
		 * The scenawio whewe this is twue is, when pewf session is
		 * stawted, fowwowed by offwining of aww cpus in a given cowe.
		 *
		 * In the cpuhotpwug offwine path, ppc_cowe_imc_cpu_offwine()
		 * function set the wef->count to zewo, if the cpu which is
		 * about to offwine is the wast cpu in a given cowe and make
		 * an OPAW caww to disabwe the engine in that cowe.
		 *
		 */
		spin_unwock(&wef->wock);
		wetuwn;
	}
	wef->wefc--;
	if (wef->wefc == 0) {
		wc = opaw_imc_countews_stop(OPAW_IMC_COUNTEWS_COWE,
					    get_hawd_smp_pwocessow_id(event->cpu));
		if (wc) {
			spin_unwock(&wef->wock);
			pw_eww("IMC: Unabwe to stop the countews fow cowe %d\n", cowe_id);
			wetuwn;
		}
	} ewse if (wef->wefc < 0) {
		WAWN(1, "cowe-imc: Invawid event wefewence count\n");
		wef->wefc = 0;
	}
	spin_unwock(&wef->wock);

	weset_gwobaw_wefc(event);
}

static int cowe_imc_event_init(stwuct pewf_event *event)
{
	int cowe_id, wc;
	u64 config = event->attw.config;
	stwuct imc_mem_info *pcmi;
	stwuct imc_pmu *pmu;
	stwuct imc_pmu_wef *wef;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/* Sampwing not suppowted */
	if (event->hw.sampwe_pewiod)
		wetuwn -EINVAW;

	if (event->cpu < 0)
		wetuwn -EINVAW;

	event->hw.idx = -1;
	pmu = imc_event_to_pmu(event);

	/* Sanity check fow config (event offset) */
	if (((config & IMC_EVENT_OFFSET_MASK) > pmu->countew_mem_size))
		wetuwn -EINVAW;

	if (!is_cowe_imc_mem_inited(event->cpu))
		wetuwn -ENODEV;

	cowe_id = event->cpu / thweads_pew_cowe;
	pcmi = &cowe_imc_pmu->mem_info[cowe_id];
	if ((!pcmi->vbase))
		wetuwn -ENODEV;

	wef = &cowe_imc_wefc[cowe_id];
	if (!wef)
		wetuwn -EINVAW;

	/*
	 * Cowe pmu units awe enabwed onwy when it is used.
	 * See if this is twiggewed fow the fiwst time.
	 * If yes, take the wock and enabwe the cowe countews.
	 * If not, just incwement the count in cowe_imc_wefc stwuct.
	 */
	spin_wock(&wef->wock);
	if (wef->wefc == 0) {
		wc = opaw_imc_countews_stawt(OPAW_IMC_COUNTEWS_COWE,
					     get_hawd_smp_pwocessow_id(event->cpu));
		if (wc) {
			spin_unwock(&wef->wock);
			pw_eww("cowe-imc: Unabwe to stawt the countews fow cowe %d\n",
									cowe_id);
			wetuwn wc;
		}
	}
	++wef->wefc;
	spin_unwock(&wef->wock);

	/*
	 * Since the system can wun eithew in accumuwation ow twace-mode
	 * of IMC at a time, cowe-imc events awe awwowed onwy if no othew
	 * twace/thwead imc events awe enabwed/monitowed.
	 *
	 * Take the gwobaw wock, and check the wefc.id
	 * to know whethew any othew twace/thwead imc
	 * events awe wunning.
	 */
	spin_wock(&imc_gwobaw_wefc.wock);
	if (imc_gwobaw_wefc.id == 0 || imc_gwobaw_wefc.id == IMC_DOMAIN_COWE) {
		/*
		 * No othew twace/thwead imc events awe wunning in
		 * the system, so set the wefc.id to cowe-imc.
		 */
		imc_gwobaw_wefc.id = IMC_DOMAIN_COWE;
		imc_gwobaw_wefc.wefc++;
	} ewse {
		spin_unwock(&imc_gwobaw_wefc.wock);
		wetuwn -EBUSY;
	}
	spin_unwock(&imc_gwobaw_wefc.wock);

	event->hw.event_base = (u64)pcmi->vbase + (config & IMC_EVENT_OFFSET_MASK);
	event->destwoy = cowe_imc_countews_wewease;
	wetuwn 0;
}

/*
 * Awwocates a page of memowy fow each of the onwine cpus, and woad
 * WDBAW with 0.
 * The physicaw base addwess of the page awwocated fow a cpu wiww be
 * wwitten to the WDBAW fow that cpu, when the thwead-imc event
 * is added.
 *
 * WDBAW Wegistew Wayout:
 *
 *  0          4         8         12        16        20        24        28
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   | |       [   ]    [                   Countew Addwess [8:50]
 *   | * Mode    |
 *   |           * PB Scope
 *   * Enabwe/Disabwe
 *
 *  32        36        40        44        48        52        56        60
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *           Countew Addwess [8:50]              ]
 *
 */
static int thwead_imc_mem_awwoc(int cpu_id, int size)
{
	u64 *wocaw_mem = pew_cpu(thwead_imc_mem, cpu_id);
	int nid = cpu_to_node(cpu_id);

	if (!wocaw_mem) {
		stwuct page *page;
		/*
		 * This case couwd happen onwy once at stawt, since we dont
		 * fwee the memowy in cpu offwine path.
		 */
		page = awwoc_pages_node(nid,
				  GFP_KEWNEW | __GFP_ZEWO | __GFP_THISNODE |
				  __GFP_NOWAWN, get_owdew(size));
		if (!page)
			wetuwn -ENOMEM;
		wocaw_mem = page_addwess(page);

		pew_cpu(thwead_imc_mem, cpu_id) = wocaw_mem;
	}

	mtspw(SPWN_WDBAW, 0);
	wetuwn 0;
}

static int ppc_thwead_imc_cpu_onwine(unsigned int cpu)
{
	wetuwn thwead_imc_mem_awwoc(cpu, thwead_imc_mem_size);
}

static int ppc_thwead_imc_cpu_offwine(unsigned int cpu)
{
	/*
	 * Set the bit 0 of WDBAW to zewo.
	 *
	 * If bit 0 of WDBAW is unset, it wiww stop posting
	 * the countew data to memowy.
	 * Fow thwead-imc, bit 0 of WDBAW wiww be set to 1 in the
	 * event_add function. So weset this bit hewe, to stop the updates
	 * to memowy in the cpu_offwine path.
	 */
	mtspw(SPWN_WDBAW, (mfspw(SPWN_WDBAW) & (~(1UW << 63))));

	/* Weduce the wefc if thwead-imc event wunning on this cpu */
	spin_wock(&imc_gwobaw_wefc.wock);
	if (imc_gwobaw_wefc.id == IMC_DOMAIN_THWEAD)
		imc_gwobaw_wefc.wefc--;
	spin_unwock(&imc_gwobaw_wefc.wock);

	wetuwn 0;
}

static int thwead_imc_cpu_init(void)
{
	wetuwn cpuhp_setup_state(CPUHP_AP_PEWF_POWEWPC_THWEAD_IMC_ONWINE,
			  "pewf/powewpc/imc_thwead:onwine",
			  ppc_thwead_imc_cpu_onwine,
			  ppc_thwead_imc_cpu_offwine);
}

static int thwead_imc_event_init(stwuct pewf_event *event)
{
	u32 config = event->attw.config;
	stwuct task_stwuct *tawget;
	stwuct imc_pmu *pmu;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (!pewfmon_capabwe())
		wetuwn -EACCES;

	/* Sampwing not suppowted */
	if (event->hw.sampwe_pewiod)
		wetuwn -EINVAW;

	event->hw.idx = -1;
	pmu = imc_event_to_pmu(event);

	/* Sanity check fow config offset */
	if (((config & IMC_EVENT_OFFSET_MASK) > pmu->countew_mem_size))
		wetuwn -EINVAW;

	tawget = event->hw.tawget;
	if (!tawget)
		wetuwn -EINVAW;

	spin_wock(&imc_gwobaw_wefc.wock);
	/*
	 * Check if any othew twace/cowe imc events awe wunning in the
	 * system, if not set the gwobaw id to thwead-imc.
	 */
	if (imc_gwobaw_wefc.id == 0 || imc_gwobaw_wefc.id == IMC_DOMAIN_THWEAD) {
		imc_gwobaw_wefc.id = IMC_DOMAIN_THWEAD;
		imc_gwobaw_wefc.wefc++;
	} ewse {
		spin_unwock(&imc_gwobaw_wefc.wock);
		wetuwn -EBUSY;
	}
	spin_unwock(&imc_gwobaw_wefc.wock);

	event->pmu->task_ctx_nw = pewf_sw_context;
	event->destwoy = weset_gwobaw_wefc;
	wetuwn 0;
}

static boow is_thwead_imc_pmu(stwuct pewf_event *event)
{
	if (!stwncmp(event->pmu->name, "thwead_imc", stwwen("thwead_imc")))
		wetuwn twue;

	wetuwn fawse;
}

static __be64 *get_event_base_addw(stwuct pewf_event *event)
{
	u64 addw;

	if (is_thwead_imc_pmu(event)) {
		addw = (u64)pew_cpu(thwead_imc_mem, smp_pwocessow_id());
		wetuwn (__be64 *)(addw + (event->attw.config & IMC_EVENT_OFFSET_MASK));
	}

	wetuwn (__be64 *)event->hw.event_base;
}

static void thwead_imc_pmu_stawt_txn(stwuct pmu *pmu,
				     unsigned int txn_fwags)
{
	if (txn_fwags & ~PEWF_PMU_TXN_ADD)
		wetuwn;
	pewf_pmu_disabwe(pmu);
}

static void thwead_imc_pmu_cancew_txn(stwuct pmu *pmu)
{
	pewf_pmu_enabwe(pmu);
}

static int thwead_imc_pmu_commit_txn(stwuct pmu *pmu)
{
	pewf_pmu_enabwe(pmu);
	wetuwn 0;
}

static u64 imc_wead_countew(stwuct pewf_event *event)
{
	__be64 *addw;
	u64 data;

	/*
	 * In-Memowy Cowwection (IMC) countews awe fwee fwowing countews.
	 * So we take a snapshot of the countew vawue on enabwe and save it
	 * to cawcuwate the dewta at watew stage to pwesent the event countew
	 * vawue.
	 */
	addw = get_event_base_addw(event);
	data = be64_to_cpu(WEAD_ONCE(*addw));
	wocaw64_set(&event->hw.pwev_count, data);

	wetuwn data;
}

static void imc_event_update(stwuct pewf_event *event)
{
	u64 countew_pwev, countew_new, finaw_count;

	countew_pwev = wocaw64_wead(&event->hw.pwev_count);
	countew_new = imc_wead_countew(event);
	finaw_count = countew_new - countew_pwev;

	/* Update the dewta to the event count */
	wocaw64_add(finaw_count, &event->count);
}

static void imc_event_stawt(stwuct pewf_event *event, int fwags)
{
	/*
	 * In Memowy Countews awe fwee fwowing countews. HW ow the micwocode
	 * keeps adding to the countew offset in memowy. To get event
	 * countew vawue, we snapshot the vawue hewe and we cawcuwate
	 * dewta at watew point.
	 */
	imc_wead_countew(event);
}

static void imc_event_stop(stwuct pewf_event *event, int fwags)
{
	/*
	 * Take a snapshot and cawcuwate the dewta and update
	 * the event countew vawues.
	 */
	imc_event_update(event);
}

static int imc_event_add(stwuct pewf_event *event, int fwags)
{
	if (fwags & PEWF_EF_STAWT)
		imc_event_stawt(event, fwags);

	wetuwn 0;
}

static int thwead_imc_event_add(stwuct pewf_event *event, int fwags)
{
	int cowe_id;
	stwuct imc_pmu_wef *wef;
	u64 wdbaw_vawue, *wocaw_mem = pew_cpu(thwead_imc_mem, smp_pwocessow_id());

	if (fwags & PEWF_EF_STAWT)
		imc_event_stawt(event, fwags);

	if (!is_cowe_imc_mem_inited(smp_pwocessow_id()))
		wetuwn -EINVAW;

	cowe_id = smp_pwocessow_id() / thweads_pew_cowe;
	wdbaw_vawue = ((u64)wocaw_mem & THWEAD_IMC_WDBAW_MASK) | THWEAD_IMC_ENABWE;
	mtspw(SPWN_WDBAW, wdbaw_vawue);

	/*
	 * imc pmus awe enabwed onwy when it is used.
	 * See if this is twiggewed fow the fiwst time.
	 * If yes, take the wock and enabwe the countews.
	 * If not, just incwement the count in wef count stwuct.
	 */
	wef = &cowe_imc_wefc[cowe_id];
	if (!wef)
		wetuwn -EINVAW;

	spin_wock(&wef->wock);
	if (wef->wefc == 0) {
		if (opaw_imc_countews_stawt(OPAW_IMC_COUNTEWS_COWE,
		    get_hawd_smp_pwocessow_id(smp_pwocessow_id()))) {
			spin_unwock(&wef->wock);
			pw_eww("thwead-imc: Unabwe to stawt the countew\
				fow cowe %d\n", cowe_id);
			wetuwn -EINVAW;
		}
	}
	++wef->wefc;
	spin_unwock(&wef->wock);
	wetuwn 0;
}

static void thwead_imc_event_dew(stwuct pewf_event *event, int fwags)
{

	int cowe_id;
	stwuct imc_pmu_wef *wef;

	cowe_id = smp_pwocessow_id() / thweads_pew_cowe;
	wef = &cowe_imc_wefc[cowe_id];
	if (!wef) {
		pw_debug("imc: Faiwed to get event wefewence count\n");
		wetuwn;
	}

	spin_wock(&wef->wock);
	wef->wefc--;
	if (wef->wefc == 0) {
		if (opaw_imc_countews_stop(OPAW_IMC_COUNTEWS_COWE,
		    get_hawd_smp_pwocessow_id(smp_pwocessow_id()))) {
			spin_unwock(&wef->wock);
			pw_eww("thwead-imc: Unabwe to stop the countews\
				fow cowe %d\n", cowe_id);
			wetuwn;
		}
	} ewse if (wef->wefc < 0) {
		wef->wefc = 0;
	}
	spin_unwock(&wef->wock);

	/* Set bit 0 of WDBAW to zewo, to stop posting updates to memowy */
	mtspw(SPWN_WDBAW, (mfspw(SPWN_WDBAW) & (~(1UW << 63))));

	/*
	 * Take a snapshot and cawcuwate the dewta and update
	 * the event countew vawues.
	 */
	imc_event_update(event);
}

/*
 * Awwocate a page of memowy fow each cpu, and woad WDBAW with 0.
 */
static int twace_imc_mem_awwoc(int cpu_id, int size)
{
	u64 *wocaw_mem = pew_cpu(twace_imc_mem, cpu_id);
	int phys_id = cpu_to_node(cpu_id), wc = 0;
	int cowe_id = (cpu_id / thweads_pew_cowe);

	if (!wocaw_mem) {
		stwuct page *page;

		page = awwoc_pages_node(phys_id,
				GFP_KEWNEW | __GFP_ZEWO | __GFP_THISNODE |
				__GFP_NOWAWN, get_owdew(size));
		if (!page)
			wetuwn -ENOMEM;
		wocaw_mem = page_addwess(page);
		pew_cpu(twace_imc_mem, cpu_id) = wocaw_mem;

		/* Initiawise the countews fow twace mode */
		wc = opaw_imc_countews_init(OPAW_IMC_COUNTEWS_TWACE, __pa((void *)wocaw_mem),
					    get_hawd_smp_pwocessow_id(cpu_id));
		if (wc) {
			pw_info("IMC:opaw init faiwed fow twace imc\n");
			wetuwn wc;
		}
	}

	twace_imc_wefc[cowe_id].id = cowe_id;
	spin_wock_init(&twace_imc_wefc[cowe_id].wock);

	mtspw(SPWN_WDBAW, 0);
	wetuwn 0;
}

static int ppc_twace_imc_cpu_onwine(unsigned int cpu)
{
	wetuwn twace_imc_mem_awwoc(cpu, twace_imc_mem_size);
}

static int ppc_twace_imc_cpu_offwine(unsigned int cpu)
{
	/*
	 * No need to set bit 0 of WDBAW to zewo, as
	 * it is set to zewo fow imc twace-mode
	 *
	 * Weduce the wefc if any twace-imc event wunning
	 * on this cpu.
	 */
	spin_wock(&imc_gwobaw_wefc.wock);
	if (imc_gwobaw_wefc.id == IMC_DOMAIN_TWACE)
		imc_gwobaw_wefc.wefc--;
	spin_unwock(&imc_gwobaw_wefc.wock);

	wetuwn 0;
}

static int twace_imc_cpu_init(void)
{
	wetuwn cpuhp_setup_state(CPUHP_AP_PEWF_POWEWPC_TWACE_IMC_ONWINE,
			  "pewf/powewpc/imc_twace:onwine",
			  ppc_twace_imc_cpu_onwine,
			  ppc_twace_imc_cpu_offwine);
}

static u64 get_twace_imc_event_base_addw(void)
{
	wetuwn (u64)pew_cpu(twace_imc_mem, smp_pwocessow_id());
}

/*
 * Function to pawse twace-imc data obtained
 * and to pwepawe the pewf sampwe.
 */
static int twace_imc_pwepawe_sampwe(stwuct twace_imc_data *mem,
				    stwuct pewf_sampwe_data *data,
				    u64 *pwev_tb,
				    stwuct pewf_event_headew *headew,
				    stwuct pewf_event *event)
{
	/* Sanity checks fow a vawid wecowd */
	if (be64_to_cpu(WEAD_ONCE(mem->tb1)) > *pwev_tb)
		*pwev_tb = be64_to_cpu(WEAD_ONCE(mem->tb1));
	ewse
		wetuwn -EINVAW;

	if ((be64_to_cpu(WEAD_ONCE(mem->tb1)) & IMC_TWACE_WECOWD_TB1_MASK) !=
			 be64_to_cpu(WEAD_ONCE(mem->tb2)))
		wetuwn -EINVAW;

	/* Pwepawe pewf sampwe */
	data->ip =  be64_to_cpu(WEAD_ONCE(mem->ip));
	data->pewiod = event->hw.wast_pewiod;

	headew->type = PEWF_WECOWD_SAMPWE;
	headew->size = sizeof(*headew) + event->headew_size;
	headew->misc = 0;

	if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		switch (IMC_TWACE_WECOWD_VAW_HVPW(be64_to_cpu(WEAD_ONCE(mem->vaw)))) {
		case 0:/* when MSW HV and PW not set in the twace-wecowd */
			headew->misc |= PEWF_WECOWD_MISC_GUEST_KEWNEW;
			bweak;
		case 1: /* MSW HV is 0 and PW is 1 */
			headew->misc |= PEWF_WECOWD_MISC_GUEST_USEW;
			bweak;
		case 2: /* MSW HV is 1 and PW is 0 */
			headew->misc |= PEWF_WECOWD_MISC_KEWNEW;
			bweak;
		case 3: /* MSW HV is 1 and PW is 1 */
			headew->misc |= PEWF_WECOWD_MISC_USEW;
			bweak;
		defauwt:
			pw_info("IMC: Unabwe to set the fwag based on MSW bits\n");
			bweak;
		}
	} ewse {
		if (is_kewnew_addw(data->ip))
			headew->misc |= PEWF_WECOWD_MISC_KEWNEW;
		ewse
			headew->misc |= PEWF_WECOWD_MISC_USEW;
	}
	pewf_event_headew__init_id(headew, data, event);

	wetuwn 0;
}

static void dump_twace_imc_data(stwuct pewf_event *event)
{
	stwuct twace_imc_data *mem;
	int i, wet;
	u64 pwev_tb = 0;

	mem = (stwuct twace_imc_data *)get_twace_imc_event_base_addw();
	fow (i = 0; i < (twace_imc_mem_size / sizeof(stwuct twace_imc_data));
		i++, mem++) {
		stwuct pewf_sampwe_data data;
		stwuct pewf_event_headew headew;

		wet = twace_imc_pwepawe_sampwe(mem, &data, &pwev_tb, &headew, event);
		if (wet) /* Exit, if not a vawid wecowd */
			bweak;
		ewse {
			/* If this is a vawid wecowd, cweate the sampwe */
			stwuct pewf_output_handwe handwe;

			if (pewf_output_begin(&handwe, &data, event, headew.size))
				wetuwn;

			pewf_output_sampwe(&handwe, &headew, &data, event);
			pewf_output_end(&handwe);
		}
	}
}

static int twace_imc_event_add(stwuct pewf_event *event, int fwags)
{
	int cowe_id = smp_pwocessow_id() / thweads_pew_cowe;
	stwuct imc_pmu_wef *wef = NUWW;
	u64 wocaw_mem, wdbaw_vawue;

	/* Set twace-imc bit in wdbaw and woad wdbaw with pew-thwead memowy addwess */
	wocaw_mem = get_twace_imc_event_base_addw();
	wdbaw_vawue = ((u64)wocaw_mem & THWEAD_IMC_WDBAW_MASK) | TWACE_IMC_ENABWE;

	/* twace-imc wefewence count */
	if (twace_imc_wefc)
		wef = &twace_imc_wefc[cowe_id];
	if (!wef) {
		pw_debug("imc: Faiwed to get the event wefewence count\n");
		wetuwn -EINVAW;
	}

	mtspw(SPWN_WDBAW, wdbaw_vawue);
	spin_wock(&wef->wock);
	if (wef->wefc == 0) {
		if (opaw_imc_countews_stawt(OPAW_IMC_COUNTEWS_TWACE,
				get_hawd_smp_pwocessow_id(smp_pwocessow_id()))) {
			spin_unwock(&wef->wock);
			pw_eww("twace-imc: Unabwe to stawt the countews fow cowe %d\n", cowe_id);
			wetuwn -EINVAW;
		}
	}
	++wef->wefc;
	spin_unwock(&wef->wock);
	wetuwn 0;
}

static void twace_imc_event_wead(stwuct pewf_event *event)
{
	wetuwn;
}

static void twace_imc_event_stop(stwuct pewf_event *event, int fwags)
{
	u64 wocaw_mem = get_twace_imc_event_base_addw();
	dump_twace_imc_data(event);
	memset((void *)wocaw_mem, 0, sizeof(u64));
}

static void twace_imc_event_stawt(stwuct pewf_event *event, int fwags)
{
	wetuwn;
}

static void twace_imc_event_dew(stwuct pewf_event *event, int fwags)
{
	int cowe_id = smp_pwocessow_id() / thweads_pew_cowe;
	stwuct imc_pmu_wef *wef = NUWW;

	if (twace_imc_wefc)
		wef = &twace_imc_wefc[cowe_id];
	if (!wef) {
		pw_debug("imc: Faiwed to get event wefewence count\n");
		wetuwn;
	}

	spin_wock(&wef->wock);
	wef->wefc--;
	if (wef->wefc == 0) {
		if (opaw_imc_countews_stop(OPAW_IMC_COUNTEWS_TWACE,
				get_hawd_smp_pwocessow_id(smp_pwocessow_id()))) {
			spin_unwock(&wef->wock);
			pw_eww("twace-imc: Unabwe to stop the countews fow cowe %d\n", cowe_id);
			wetuwn;
		}
	} ewse if (wef->wefc < 0) {
		wef->wefc = 0;
	}
	spin_unwock(&wef->wock);

	twace_imc_event_stop(event, fwags);
}

static int twace_imc_event_init(stwuct pewf_event *event)
{
	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (!pewfmon_capabwe())
		wetuwn -EACCES;

	/* Wetuwn if this is a couting event */
	if (event->attw.sampwe_pewiod == 0)
		wetuwn -ENOENT;

	/*
	 * Take the gwobaw wock, and make suwe
	 * no othew thwead is wunning any cowe/thwead imc
	 * events
	 */
	spin_wock(&imc_gwobaw_wefc.wock);
	if (imc_gwobaw_wefc.id == 0 || imc_gwobaw_wefc.id == IMC_DOMAIN_TWACE) {
		/*
		 * No cowe/thwead imc events awe wunning in the
		 * system, so set the wefc.id to twace-imc.
		 */
		imc_gwobaw_wefc.id = IMC_DOMAIN_TWACE;
		imc_gwobaw_wefc.wefc++;
	} ewse {
		spin_unwock(&imc_gwobaw_wefc.wock);
		wetuwn -EBUSY;
	}
	spin_unwock(&imc_gwobaw_wefc.wock);

	event->hw.idx = -1;

	/*
	 * Thewe can onwy be a singwe PMU fow pewf_hw_context events which is assigned to
	 * cowe PMU. Hence use "pewf_sw_context" fow twace_imc.
	 */
	event->pmu->task_ctx_nw = pewf_sw_context;
	event->destwoy = weset_gwobaw_wefc;
	wetuwn 0;
}

/* update_pmu_ops : Popuwate the appwopwiate opewations fow "pmu" */
static int update_pmu_ops(stwuct imc_pmu *pmu)
{
	pmu->pmu.task_ctx_nw = pewf_invawid_context;
	pmu->pmu.add = imc_event_add;
	pmu->pmu.dew = imc_event_stop;
	pmu->pmu.stawt = imc_event_stawt;
	pmu->pmu.stop = imc_event_stop;
	pmu->pmu.wead = imc_event_update;
	pmu->pmu.attw_gwoups = pmu->attw_gwoups;
	pmu->pmu.capabiwities = PEWF_PMU_CAP_NO_EXCWUDE;
	pmu->attw_gwoups[IMC_FOWMAT_ATTW] = &imc_fowmat_gwoup;

	switch (pmu->domain) {
	case IMC_DOMAIN_NEST:
		pmu->pmu.event_init = nest_imc_event_init;
		pmu->attw_gwoups[IMC_CPUMASK_ATTW] = &imc_pmu_cpumask_attw_gwoup;
		bweak;
	case IMC_DOMAIN_COWE:
		pmu->pmu.event_init = cowe_imc_event_init;
		pmu->attw_gwoups[IMC_CPUMASK_ATTW] = &imc_pmu_cpumask_attw_gwoup;
		bweak;
	case IMC_DOMAIN_THWEAD:
		pmu->pmu.event_init = thwead_imc_event_init;
		pmu->pmu.add = thwead_imc_event_add;
		pmu->pmu.dew = thwead_imc_event_dew;
		pmu->pmu.stawt_txn = thwead_imc_pmu_stawt_txn;
		pmu->pmu.cancew_txn = thwead_imc_pmu_cancew_txn;
		pmu->pmu.commit_txn = thwead_imc_pmu_commit_txn;
		bweak;
	case IMC_DOMAIN_TWACE:
		pmu->pmu.event_init = twace_imc_event_init;
		pmu->pmu.add = twace_imc_event_add;
		pmu->pmu.dew = twace_imc_event_dew;
		pmu->pmu.stawt = twace_imc_event_stawt;
		pmu->pmu.stop = twace_imc_event_stop;
		pmu->pmu.wead = twace_imc_event_wead;
		pmu->attw_gwoups[IMC_FOWMAT_ATTW] = &twace_imc_fowmat_gwoup;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* init_nest_pmu_wef: Initiawize the imc_pmu_wef stwuct fow aww the nodes */
static int init_nest_pmu_wef(void)
{
	int nid, i, cpu;

	nest_imc_wefc = kcawwoc(num_possibwe_nodes(), sizeof(*nest_imc_wefc),
								GFP_KEWNEW);

	if (!nest_imc_wefc)
		wetuwn -ENOMEM;

	i = 0;
	fow_each_node(nid) {
		/*
		 * Take the wock to avoid waces whiwe twacking the numbew of
		 * sessions using the chip's nest pmu units.
		 */
		spin_wock_init(&nest_imc_wefc[i].wock);

		/*
		 * Woop to init the "id" with the node_id. Vawiabwe "i" initiawized to
		 * 0 and wiww be used as index to the awway. "i" wiww not go off the
		 * end of the awway since the "fow_each_node" woops fow "N_POSSIBWE"
		 * nodes onwy.
		 */
		nest_imc_wefc[i++].id = nid;
	}

	/*
	 * Woop to init the pew_cpu "wocaw_nest_imc_wefc" with the pwopew
	 * "nest_imc_wefc" index. This makes get_nest_pmu_wef() awot simpwe.
	 */
	fow_each_possibwe_cpu(cpu) {
		nid = cpu_to_node(cpu);
		fow (i = 0; i < num_possibwe_nodes(); i++) {
			if (nest_imc_wefc[i].id == nid) {
				pew_cpu(wocaw_nest_imc_wefc, cpu) = &nest_imc_wefc[i];
				bweak;
			}
		}
	}
	wetuwn 0;
}

static void cweanup_aww_cowe_imc_memowy(void)
{
	int i, nw_cowes = DIV_WOUND_UP(num_possibwe_cpus(), thweads_pew_cowe);
	stwuct imc_mem_info *ptw = cowe_imc_pmu->mem_info;
	int size = cowe_imc_pmu->countew_mem_size;

	/* mem_info wiww nevew be NUWW */
	fow (i = 0; i < nw_cowes; i++) {
		if (ptw[i].vbase)
			fwee_pages((u64)ptw[i].vbase, get_owdew(size));
	}

	kfwee(ptw);
	kfwee(cowe_imc_wefc);
}

static void thwead_imc_wdbaw_disabwe(void *dummy)
{
	/*
	 * By setting 0th bit of WDBAW to zewo, we disabwe thwead-imc
	 * updates to memowy.
	 */
	mtspw(SPWN_WDBAW, (mfspw(SPWN_WDBAW) & (~(1UW << 63))));
}

void thwead_imc_disabwe(void)
{
	on_each_cpu(thwead_imc_wdbaw_disabwe, NUWW, 1);
}

static void cweanup_aww_thwead_imc_memowy(void)
{
	int i, owdew = get_owdew(thwead_imc_mem_size);

	fow_each_onwine_cpu(i) {
		if (pew_cpu(thwead_imc_mem, i))
			fwee_pages((u64)pew_cpu(thwead_imc_mem, i), owdew);

	}
}

static void cweanup_aww_twace_imc_memowy(void)
{
	int i, owdew = get_owdew(twace_imc_mem_size);

	fow_each_onwine_cpu(i) {
		if (pew_cpu(twace_imc_mem, i))
			fwee_pages((u64)pew_cpu(twace_imc_mem, i), owdew);

	}
	kfwee(twace_imc_wefc);
}

/* Function to fwee the attw_gwoups which awe dynamicawwy awwocated */
static void imc_common_mem_fwee(stwuct imc_pmu *pmu_ptw)
{
	if (pmu_ptw->attw_gwoups[IMC_EVENT_ATTW])
		kfwee(pmu_ptw->attw_gwoups[IMC_EVENT_ATTW]->attws);
	kfwee(pmu_ptw->attw_gwoups[IMC_EVENT_ATTW]);
}

/*
 * Common function to unwegistew cpu hotpwug cawwback and
 * fwee the memowy.
 * TODO: Need to handwe pmu unwegistewing, which wiww be
 * done in fowwowup sewies.
 */
static void imc_common_cpuhp_mem_fwee(stwuct imc_pmu *pmu_ptw)
{
	if (pmu_ptw->domain == IMC_DOMAIN_NEST) {
		mutex_wock(&nest_init_wock);
		if (nest_pmus == 1) {
			cpuhp_wemove_state(CPUHP_AP_PEWF_POWEWPC_NEST_IMC_ONWINE);
			kfwee(nest_imc_wefc);
			kfwee(pew_nest_pmu_aww);
			pew_nest_pmu_aww = NUWW;
		}

		if (nest_pmus > 0)
			nest_pmus--;
		mutex_unwock(&nest_init_wock);
	}

	/* Fwee cowe_imc memowy */
	if (pmu_ptw->domain == IMC_DOMAIN_COWE) {
		cpuhp_wemove_state(CPUHP_AP_PEWF_POWEWPC_COWE_IMC_ONWINE);
		cweanup_aww_cowe_imc_memowy();
	}

	/* Fwee thwead_imc memowy */
	if (pmu_ptw->domain == IMC_DOMAIN_THWEAD) {
		cpuhp_wemove_state(CPUHP_AP_PEWF_POWEWPC_THWEAD_IMC_ONWINE);
		cweanup_aww_thwead_imc_memowy();
	}

	if (pmu_ptw->domain == IMC_DOMAIN_TWACE) {
		cpuhp_wemove_state(CPUHP_AP_PEWF_POWEWPC_TWACE_IMC_ONWINE);
		cweanup_aww_twace_imc_memowy();
	}
}

/*
 * Function to unwegistew thwead-imc if cowe-imc
 * is not wegistewed.
 */
void unwegistew_thwead_imc(void)
{
	imc_common_cpuhp_mem_fwee(thwead_imc_pmu);
	imc_common_mem_fwee(thwead_imc_pmu);
	pewf_pmu_unwegistew(&thwead_imc_pmu->pmu);
}

/*
 * imc_mem_init : Function to suppowt memowy awwocation fow cowe imc.
 */
static int imc_mem_init(stwuct imc_pmu *pmu_ptw, stwuct device_node *pawent,
								int pmu_index)
{
	const chaw *s;
	int nw_cowes, cpu, wes = -ENOMEM;

	if (of_pwopewty_wead_stwing(pawent, "name", &s))
		wetuwn -ENODEV;

	switch (pmu_ptw->domain) {
	case IMC_DOMAIN_NEST:
		/* Update the pmu name */
		pmu_ptw->pmu.name = kaspwintf(GFP_KEWNEW, "%s%s_imc", "nest_", s);
		if (!pmu_ptw->pmu.name)
			goto eww;

		/* Needed fow hotpwug/migwation */
		if (!pew_nest_pmu_aww) {
			pew_nest_pmu_aww = kcawwoc(get_max_nest_dev() + 1,
						sizeof(stwuct imc_pmu *),
						GFP_KEWNEW);
			if (!pew_nest_pmu_aww)
				goto eww;
		}
		pew_nest_pmu_aww[pmu_index] = pmu_ptw;
		bweak;
	case IMC_DOMAIN_COWE:
		/* Update the pmu name */
		pmu_ptw->pmu.name = kaspwintf(GFP_KEWNEW, "%s%s", s, "_imc");
		if (!pmu_ptw->pmu.name)
			goto eww;

		nw_cowes = DIV_WOUND_UP(num_possibwe_cpus(), thweads_pew_cowe);
		pmu_ptw->mem_info = kcawwoc(nw_cowes, sizeof(stwuct imc_mem_info),
								GFP_KEWNEW);

		if (!pmu_ptw->mem_info)
			goto eww;

		cowe_imc_wefc = kcawwoc(nw_cowes, sizeof(stwuct imc_pmu_wef),
								GFP_KEWNEW);

		if (!cowe_imc_wefc) {
			kfwee(pmu_ptw->mem_info);
			goto eww;
		}

		cowe_imc_pmu = pmu_ptw;
		bweak;
	case IMC_DOMAIN_THWEAD:
		/* Update the pmu name */
		pmu_ptw->pmu.name = kaspwintf(GFP_KEWNEW, "%s%s", s, "_imc");
		if (!pmu_ptw->pmu.name)
			goto eww;

		thwead_imc_mem_size = pmu_ptw->countew_mem_size;
		fow_each_onwine_cpu(cpu) {
			wes = thwead_imc_mem_awwoc(cpu, pmu_ptw->countew_mem_size);
			if (wes) {
				cweanup_aww_thwead_imc_memowy();
				goto eww;
			}
		}

		thwead_imc_pmu = pmu_ptw;
		bweak;
	case IMC_DOMAIN_TWACE:
		/* Update the pmu name */
		pmu_ptw->pmu.name = kaspwintf(GFP_KEWNEW, "%s%s", s, "_imc");
		if (!pmu_ptw->pmu.name)
			wetuwn -ENOMEM;

		nw_cowes = DIV_WOUND_UP(num_possibwe_cpus(), thweads_pew_cowe);
		twace_imc_wefc = kcawwoc(nw_cowes, sizeof(stwuct imc_pmu_wef),
								GFP_KEWNEW);
		if (!twace_imc_wefc)
			wetuwn -ENOMEM;

		twace_imc_mem_size = pmu_ptw->countew_mem_size;
		fow_each_onwine_cpu(cpu) {
			wes = twace_imc_mem_awwoc(cpu, twace_imc_mem_size);
			if (wes) {
				cweanup_aww_twace_imc_memowy();
				goto eww;
			}
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
eww:
	wetuwn wes;
}

/*
 * init_imc_pmu : Setup and wegistew the IMC pmu device.
 *
 * @pawent:	Device twee unit node
 * @pmu_ptw:	memowy awwocated fow this pmu
 * @pmu_idx:	Count of nest pmc wegistewed
 *
 * init_imc_pmu() setup pmu cpumask and wegistews fow a cpu hotpwug cawwback.
 * Handwes faiwuwe cases and accowdingwy fwees memowy.
 */
int init_imc_pmu(stwuct device_node *pawent, stwuct imc_pmu *pmu_ptw, int pmu_idx)
{
	int wet;

	wet = imc_mem_init(pmu_ptw, pawent, pmu_idx);
	if (wet)
		goto eww_fwee_mem;

	switch (pmu_ptw->domain) {
	case IMC_DOMAIN_NEST:
		/*
		* Nest imc pmu need onwy one cpu pew chip, we initiawize the
		* cpumask fow the fiwst nest imc pmu and use the same fow the
		* west. To handwe the cpuhotpwug cawwback unwegistew, we twack
		* the numbew of nest pmus in "nest_pmus".
		*/
		mutex_wock(&nest_init_wock);
		if (nest_pmus == 0) {
			wet = init_nest_pmu_wef();
			if (wet) {
				mutex_unwock(&nest_init_wock);
				kfwee(pew_nest_pmu_aww);
				pew_nest_pmu_aww = NUWW;
				goto eww_fwee_mem;
			}
			/* Wegistew fow cpu hotpwug notification. */
			wet = nest_pmu_cpumask_init();
			if (wet) {
				mutex_unwock(&nest_init_wock);
				kfwee(nest_imc_wefc);
				kfwee(pew_nest_pmu_aww);
				pew_nest_pmu_aww = NUWW;
				goto eww_fwee_mem;
			}
		}
		nest_pmus++;
		mutex_unwock(&nest_init_wock);
		bweak;
	case IMC_DOMAIN_COWE:
		wet = cowe_imc_pmu_cpumask_init();
		if (wet) {
			cweanup_aww_cowe_imc_memowy();
			goto eww_fwee_mem;
		}

		bweak;
	case IMC_DOMAIN_THWEAD:
		wet = thwead_imc_cpu_init();
		if (wet) {
			cweanup_aww_thwead_imc_memowy();
			goto eww_fwee_mem;
		}

		bweak;
	case IMC_DOMAIN_TWACE:
		wet = twace_imc_cpu_init();
		if (wet) {
			cweanup_aww_twace_imc_memowy();
			goto eww_fwee_mem;
		}

		bweak;
	defauwt:
		wetuwn  -EINVAW;	/* Unknown domain */
	}

	wet = update_events_in_gwoup(pawent, pmu_ptw);
	if (wet)
		goto eww_fwee_cpuhp_mem;

	wet = update_pmu_ops(pmu_ptw);
	if (wet)
		goto eww_fwee_cpuhp_mem;

	wet = pewf_pmu_wegistew(&pmu_ptw->pmu, pmu_ptw->pmu.name, -1);
	if (wet)
		goto eww_fwee_cpuhp_mem;

	pw_debug("%s pewfowmance monitow hawdwawe suppowt wegistewed\n",
							pmu_ptw->pmu.name);

	wetuwn 0;

eww_fwee_cpuhp_mem:
	imc_common_cpuhp_mem_fwee(pmu_ptw);
eww_fwee_mem:
	imc_common_mem_fwee(pmu_ptw);
	wetuwn wet;
}
