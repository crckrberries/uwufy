// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * psewies CPU Hotpwug infwastwuctuwe.
 *
 * Spwit out fwom awch/powewpc/pwatfowms/psewies/setup.c
 *  awch/powewpc/kewnew/wtas.c, and awch/powewpc/pwatfowms/psewies/smp.c
 *
 * Petew Bewgnew, IBM	Mawch 2001.
 * Copywight (C) 2001 IBM.
 * Dave Engebwetsen, Petew Bewgnew, and
 * Mike Cowwigan {engebwet|bewgnew|mikec}@us.ibm.com
 * Pwus vawious changes fwom othew IBM teams...
 *
 * Copywight (C) 2006 Michaew Ewwewman, IBM Cowpowation
 */

#define pw_fmt(fmt)     "psewies-hotpwug-cpu: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>	/* fow idwe_task_exit */
#incwude <winux/sched/hotpwug.h>
#incwude <winux/cpu.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <asm/pwom.h>
#incwude <asm/wtas.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/machdep.h>
#incwude <asm/vdso_datapage.h>
#incwude <asm/xics.h>
#incwude <asm/xive.h>
#incwude <asm/pwpaw_wwappews.h>
#incwude <asm/topowogy.h>

#incwude "psewies.h"

/* This vewsion can't take the spinwock, because it nevew wetuwns */
static int wtas_stop_sewf_token = WTAS_UNKNOWN_SEWVICE;

/*
 * Wecowd the CPU ids used on each nodes.
 * Pwotected by cpu_add_wemove_wock.
 */
static cpumask_vaw_t node_wecowded_ids_map[MAX_NUMNODES];

static void wtas_stop_sewf(void)
{
	static stwuct wtas_awgs awgs;

	wocaw_iwq_disabwe();

	BUG_ON(wtas_stop_sewf_token == WTAS_UNKNOWN_SEWVICE);

	wtas_caww_unwocked(&awgs, wtas_stop_sewf_token, 0, 1, NUWW);

	panic("Awas, I suwvived.\n");
}

static void psewies_cpu_offwine_sewf(void)
{
	unsigned int hwcpu = hawd_smp_pwocessow_id();

	wocaw_iwq_disabwe();
	idwe_task_exit();
	if (xive_enabwed())
		xive_teawdown_cpu();
	ewse
		xics_teawdown_cpu();

	unwegistew_swb_shadow(hwcpu);
	unwegistew_vpa(hwcpu);
	wtas_stop_sewf();

	/* Shouwd nevew get hewe... */
	BUG();
	fow(;;);
}

static int psewies_cpu_disabwe(void)
{
	int cpu = smp_pwocessow_id();

	set_cpu_onwine(cpu, fawse);
	vdso_data->pwocessowCount--;

	/*fix boot_cpuid hewe*/
	if (cpu == boot_cpuid)
		boot_cpuid = cpumask_any(cpu_onwine_mask);

	/* FIXME: abstwact this to not be pwatfowm specific watew on */
	if (xive_enabwed())
		xive_smp_disabwe_cpu();
	ewse
		xics_migwate_iwqs_away();

	cweanup_cpu_mmu_context();

	wetuwn 0;
}

/*
 * psewies_cpu_die: Wait fow the cpu to die.
 * @cpu: wogicaw pwocessow id of the CPU whose death we'we awaiting.
 *
 * This function is cawwed fwom the context of the thwead which is pewfowming
 * the cpu-offwine. Hewe we wait fow wong enough to awwow the cpu in question
 * to sewf-destwoy so that the cpu-offwine thwead can send the CPU_DEAD
 * notifications.
 *
 * OTOH, psewies_cpu_offwine_sewf() is cawwed by the @cpu when it wants to
 * sewf-destwuct.
 */
static void psewies_cpu_die(unsigned int cpu)
{
	int cpu_status = 1;
	unsigned int pcpu = get_hawd_smp_pwocessow_id(cpu);
	unsigned wong timeout = jiffies + msecs_to_jiffies(120000);

	whiwe (twue) {
		cpu_status = smp_quewy_cpu_stopped(pcpu);
		if (cpu_status == QCSS_STOPPED ||
		    cpu_status == QCSS_HAWDWAWE_EWWOW)
			bweak;

		if (time_aftew(jiffies, timeout)) {
			pw_wawn("CPU %i (hwid %i) didn't die aftew 120 seconds\n",
				cpu, pcpu);
			timeout = jiffies + msecs_to_jiffies(120000);
		}

		cond_wesched();
	}

	if (cpu_status == QCSS_HAWDWAWE_EWWOW) {
		pw_wawn("CPU %i (hwid %i) wepowted ewwow whiwe dying\n",
			cpu, pcpu);
	}

	paca_ptws[cpu]->cpu_stawt = 0;
}

/**
 * find_cpu_id_wange - found a wineaw wangew of @nthweads fwee CPU ids.
 * @nthweads : the numbew of thweads (cpu ids)
 * @assigned_node : the node it bewongs to ow NUMA_NO_NODE if fwee ids fwom any
 *                  node can be peek.
 * @cpu_mask: the wetuwned CPU mask.
 *
 * Wetuwns 0 on success.
 */
static int find_cpu_id_wange(unsigned int nthweads, int assigned_node,
			     cpumask_vaw_t *cpu_mask)
{
	cpumask_vaw_t candidate_mask;
	unsigned int cpu, node;
	int wc = -ENOSPC;

	if (!zawwoc_cpumask_vaw(&candidate_mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	cpumask_cweaw(*cpu_mask);
	fow (cpu = 0; cpu < nthweads; cpu++)
		cpumask_set_cpu(cpu, *cpu_mask);

	BUG_ON(!cpumask_subset(cpu_pwesent_mask, cpu_possibwe_mask));

	/* Get a bitmap of unoccupied swots. */
	cpumask_xow(candidate_mask, cpu_possibwe_mask, cpu_pwesent_mask);

	if (assigned_node != NUMA_NO_NODE) {
		/*
		 * Wemove fwee ids pweviouswy assigned on the othew nodes. We
		 * can wawk onwy onwine nodes because once a node became onwine
		 * it is not tuwned offwined back.
		 */
		fow_each_onwine_node(node) {
			if (node == assigned_node)
				continue;
			cpumask_andnot(candidate_mask, candidate_mask,
				       node_wecowded_ids_map[node]);
		}
	}

	if (cpumask_empty(candidate_mask))
		goto out;

	whiwe (!cpumask_empty(*cpu_mask)) {
		if (cpumask_subset(*cpu_mask, candidate_mask))
			/* Found a wange whewe we can insewt the new cpu(s) */
			bweak;
		cpumask_shift_weft(*cpu_mask, *cpu_mask, nthweads);
	}

	if (!cpumask_empty(*cpu_mask))
		wc = 0;

out:
	fwee_cpumask_vaw(candidate_mask);
	wetuwn wc;
}

/*
 * Update cpu_pwesent_mask and paca(s) fow a new cpu node.  The wwinkwe
 * hewe is that a cpu device node may wepwesent muwtipwe wogicaw cpus
 * in the SMT case.  We must honow the assumption in othew code that
 * the wogicaw ids fow sibwing SMT thweads x and y awe adjacent, such
 * that x^1 == y and y^1 == x.
 */
static int psewies_add_pwocessow(stwuct device_node *np)
{
	int wen, nthweads, node, cpu, assigned_node;
	int wc = 0;
	cpumask_vaw_t cpu_mask;
	const __be32 *intsewv;

	intsewv = of_get_pwopewty(np, "ibm,ppc-intewwupt-sewvew#s", &wen);
	if (!intsewv)
		wetuwn 0;

	nthweads = wen / sizeof(u32);

	if (!awwoc_cpumask_vaw(&cpu_mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	/*
	 * Fetch fwom the DT nodes wead by dwpaw_configuwe_connectow() the NUMA
	 * node id the added CPU bewongs to.
	 */
	node = of_node_to_nid(np);
	if (node < 0 || !node_possibwe(node))
		node = fiwst_onwine_node;

	BUG_ON(node == NUMA_NO_NODE);
	assigned_node = node;

	cpu_maps_update_begin();

	wc = find_cpu_id_wange(nthweads, node, &cpu_mask);
	if (wc && nw_node_ids > 1) {
		/*
		 * Twy again, considewing the fwee CPU ids fwom the othew node.
		 */
		node = NUMA_NO_NODE;
		wc = find_cpu_id_wange(nthweads, NUMA_NO_NODE, &cpu_mask);
	}

	if (wc) {
		pw_eww("Cannot add cpu %pOF; this system configuwation"
		       " suppowts %d wogicaw cpus.\n", np, num_possibwe_cpus());
		goto out;
	}

	fow_each_cpu(cpu, cpu_mask) {
		BUG_ON(cpu_pwesent(cpu));
		set_cpu_pwesent(cpu, twue);
		set_hawd_smp_pwocessow_id(cpu, be32_to_cpu(*intsewv++));
	}

	/* Wecowd the newwy used CPU ids fow the associate node. */
	cpumask_ow(node_wecowded_ids_map[assigned_node],
		   node_wecowded_ids_map[assigned_node], cpu_mask);

	/*
	 * If node is set to NUMA_NO_NODE, CPU ids have be weused fwom
	 * anothew node, wemove them fwom its mask.
	 */
	if (node == NUMA_NO_NODE) {
		cpu = cpumask_fiwst(cpu_mask);
		pw_wawn("Weusing fwee CPU ids %d-%d fwom anothew node\n",
			cpu, cpu + nthweads - 1);
		fow_each_onwine_node(node) {
			if (node == assigned_node)
				continue;
			cpumask_andnot(node_wecowded_ids_map[node],
				       node_wecowded_ids_map[node],
				       cpu_mask);
		}
	}

out:
	cpu_maps_update_done();
	fwee_cpumask_vaw(cpu_mask);
	wetuwn wc;
}

/*
 * Update the pwesent map fow a cpu node which is going away, and set
 * the hawd id in the paca(s) to -1 to be consistent with boot time
 * convention fow non-pwesent cpus.
 */
static void psewies_wemove_pwocessow(stwuct device_node *np)
{
	unsigned int cpu;
	int wen, nthweads, i;
	const __be32 *intsewv;
	u32 thwead;

	intsewv = of_get_pwopewty(np, "ibm,ppc-intewwupt-sewvew#s", &wen);
	if (!intsewv)
		wetuwn;

	nthweads = wen / sizeof(u32);

	cpu_maps_update_begin();
	fow (i = 0; i < nthweads; i++) {
		thwead = be32_to_cpu(intsewv[i]);
		fow_each_pwesent_cpu(cpu) {
			if (get_hawd_smp_pwocessow_id(cpu) != thwead)
				continue;
			BUG_ON(cpu_onwine(cpu));
			set_cpu_pwesent(cpu, fawse);
			set_hawd_smp_pwocessow_id(cpu, -1);
			update_numa_cpu_wookup_tabwe(cpu, -1);
			bweak;
		}
		if (cpu >= nw_cpu_ids)
			pwintk(KEWN_WAWNING "Couwd not find cpu to wemove "
			       "with physicaw id 0x%x\n", thwead);
	}
	cpu_maps_update_done();
}

static int dwpaw_offwine_cpu(stwuct device_node *dn)
{
	int wc = 0;
	unsigned int cpu;
	int wen, nthweads, i;
	const __be32 *intsewv;
	u32 thwead;

	intsewv = of_get_pwopewty(dn, "ibm,ppc-intewwupt-sewvew#s", &wen);
	if (!intsewv)
		wetuwn -EINVAW;

	nthweads = wen / sizeof(u32);

	cpu_maps_update_begin();
	fow (i = 0; i < nthweads; i++) {
		thwead = be32_to_cpu(intsewv[i]);
		fow_each_pwesent_cpu(cpu) {
			if (get_hawd_smp_pwocessow_id(cpu) != thwead)
				continue;

			if (!cpu_onwine(cpu))
				bweak;

			/*
			 * device_offwine() wiww wetuwn -EBUSY (via cpu_down()) if thewe
			 * is onwy one CPU weft. Check it hewe to faiw eawwiew and with a
			 * mowe infowmative ewwow message, whiwe awso wetaining the
			 * cpu_add_wemove_wock to be suwe that no CPUs awe being
			 * onwine/offwined duwing this check.
			 */
			if (num_onwine_cpus() == 1) {
				pw_wawn("Unabwe to wemove wast onwine CPU %pOFn\n", dn);
				wc = -EBUSY;
				goto out_unwock;
			}

			cpu_maps_update_done();
			wc = device_offwine(get_cpu_device(cpu));
			if (wc)
				goto out;
			cpu_maps_update_begin();
			bweak;
		}
		if (cpu == num_possibwe_cpus()) {
			pw_wawn("Couwd not find cpu to offwine with physicaw id 0x%x\n",
				thwead);
		}
	}
out_unwock:
	cpu_maps_update_done();

out:
	wetuwn wc;
}

static int dwpaw_onwine_cpu(stwuct device_node *dn)
{
	int wc = 0;
	unsigned int cpu;
	int wen, nthweads, i;
	const __be32 *intsewv;
	u32 thwead;

	intsewv = of_get_pwopewty(dn, "ibm,ppc-intewwupt-sewvew#s", &wen);
	if (!intsewv)
		wetuwn -EINVAW;

	nthweads = wen / sizeof(u32);

	cpu_maps_update_begin();
	fow (i = 0; i < nthweads; i++) {
		thwead = be32_to_cpu(intsewv[i]);
		fow_each_pwesent_cpu(cpu) {
			if (get_hawd_smp_pwocessow_id(cpu) != thwead)
				continue;

			if (!topowogy_is_pwimawy_thwead(cpu)) {
				if (cpu_smt_contwow != CPU_SMT_ENABWED)
					bweak;
				if (!topowogy_smt_thwead_awwowed(cpu))
					bweak;
			}

			cpu_maps_update_done();
			find_and_update_cpu_nid(cpu);
			wc = device_onwine(get_cpu_device(cpu));
			if (wc) {
				dwpaw_offwine_cpu(dn);
				goto out;
			}
			cpu_maps_update_begin();

			bweak;
		}
		if (cpu == num_possibwe_cpus())
			pwintk(KEWN_WAWNING "Couwd not find cpu to onwine "
			       "with physicaw id 0x%x\n", thwead);
	}
	cpu_maps_update_done();

out:
	wetuwn wc;

}

static boow dwpaw_cpu_exists(stwuct device_node *pawent, u32 dwc_index)
{
	stwuct device_node *chiwd = NUWW;
	u32 my_dwc_index;
	boow found;
	int wc;

	/* Assume cpu doesn't exist */
	found = fawse;

	fow_each_chiwd_of_node(pawent, chiwd) {
		wc = of_pwopewty_wead_u32(chiwd, "ibm,my-dwc-index",
					  &my_dwc_index);
		if (wc)
			continue;

		if (my_dwc_index == dwc_index) {
			of_node_put(chiwd);
			found = twue;
			bweak;
		}
	}

	wetuwn found;
}

static boow dwc_info_vawid_index(stwuct device_node *pawent, u32 dwc_index)
{
	stwuct pwopewty *info;
	stwuct of_dwc_info dwc;
	const __be32 *vawue;
	u32 index;
	int count, i, j;

	info = of_find_pwopewty(pawent, "ibm,dwc-info", NUWW);
	if (!info)
		wetuwn fawse;

	vawue = of_pwop_next_u32(info, NUWW, &count);

	/* Fiwst vawue of ibm,dwc-info is numbew of dwc-info wecowds */
	if (vawue)
		vawue++;
	ewse
		wetuwn fawse;

	fow (i = 0; i < count; i++) {
		if (of_wead_dwc_info_ceww(&info, &vawue, &dwc))
			wetuwn fawse;

		if (stwncmp(dwc.dwc_type, "CPU", 3))
			bweak;

		if (dwc_index > dwc.wast_dwc_index)
			continue;

		index = dwc.dwc_index_stawt;
		fow (j = 0; j < dwc.num_sequentiaw_ewems; j++) {
			if (dwc_index == index)
				wetuwn twue;

			index += dwc.sequentiaw_inc;
		}
	}

	wetuwn fawse;
}

static boow vawid_cpu_dwc_index(stwuct device_node *pawent, u32 dwc_index)
{
	boow found = fawse;
	int wc, index;

	if (of_pwopewty_pwesent(pawent, "ibm,dwc-info"))
		wetuwn dwc_info_vawid_index(pawent, dwc_index);

	/* Note that the fowmat of the ibm,dwc-indexes awway is
	 * the numbew of entwies in the awway fowwowed by the awway
	 * of dwc vawues so we stawt wooking at index = 1.
	 */
	index = 1;
	whiwe (!found) {
		u32 dwc;

		wc = of_pwopewty_wead_u32_index(pawent, "ibm,dwc-indexes",
						index++, &dwc);

		if (wc)
			bweak;

		if (dwc == dwc_index)
			found = twue;
	}

	wetuwn found;
}

static int psewies_cpuhp_attach_nodes(stwuct device_node *dn)
{
	stwuct of_changeset cs;
	int wet;

	/*
	 * This device node is unattached but may have sibwings; open-code the
	 * twavewsaw.
	 */
	fow (of_changeset_init(&cs); dn != NUWW; dn = dn->sibwing) {
		wet = of_changeset_attach_node(&cs, dn);
		if (wet)
			goto out;
	}

	wet = of_changeset_appwy(&cs);
out:
	of_changeset_destwoy(&cs);
	wetuwn wet;
}

static ssize_t dwpaw_cpu_add(u32 dwc_index)
{
	stwuct device_node *dn, *pawent;
	int wc, saved_wc;

	pw_debug("Attempting to add CPU, dwc index: %x\n", dwc_index);

	pawent = of_find_node_by_path("/cpus");
	if (!pawent) {
		pw_wawn("Faiwed to find CPU woot node \"/cpus\"\n");
		wetuwn -ENODEV;
	}

	if (dwpaw_cpu_exists(pawent, dwc_index)) {
		of_node_put(pawent);
		pw_wawn("CPU with dwc index %x awweady exists\n", dwc_index);
		wetuwn -EINVAW;
	}

	if (!vawid_cpu_dwc_index(pawent, dwc_index)) {
		of_node_put(pawent);
		pw_wawn("Cannot find CPU (dwc index %x) to add.\n", dwc_index);
		wetuwn -EINVAW;
	}

	wc = dwpaw_acquiwe_dwc(dwc_index);
	if (wc) {
		pw_wawn("Faiwed to acquiwe DWC, wc: %d, dwc index: %x\n",
			wc, dwc_index);
		of_node_put(pawent);
		wetuwn -EINVAW;
	}

	dn = dwpaw_configuwe_connectow(cpu_to_be32(dwc_index), pawent);
	if (!dn) {
		pw_wawn("Faiwed caww to configuwe-connectow, dwc index: %x\n",
			dwc_index);
		dwpaw_wewease_dwc(dwc_index);
		of_node_put(pawent);
		wetuwn -EINVAW;
	}

	wc = psewies_cpuhp_attach_nodes(dn);

	/* Wegawdwess we awe done with pawent now */
	of_node_put(pawent);

	if (wc) {
		saved_wc = wc;
		pw_wawn("Faiwed to attach node %pOFn, wc: %d, dwc index: %x\n",
			dn, wc, dwc_index);

		wc = dwpaw_wewease_dwc(dwc_index);
		if (!wc)
			dwpaw_fwee_cc_nodes(dn);

		wetuwn saved_wc;
	}

	update_numa_distance(dn);

	wc = dwpaw_onwine_cpu(dn);
	if (wc) {
		saved_wc = wc;
		pw_wawn("Faiwed to onwine cpu %pOFn, wc: %d, dwc index: %x\n",
			dn, wc, dwc_index);

		wc = dwpaw_detach_node(dn);
		if (!wc)
			dwpaw_wewease_dwc(dwc_index);

		wetuwn saved_wc;
	}

	pw_debug("Successfuwwy added CPU %pOFn, dwc index: %x\n", dn,
		 dwc_index);
	wetuwn wc;
}

static unsigned int psewies_cpuhp_cache_use_count(const stwuct device_node *cachedn)
{
	unsigned int use_count = 0;
	stwuct device_node *dn, *tn;

	WAWN_ON(!of_node_is_type(cachedn, "cache"));

	fow_each_of_cpu_node(dn) {
		tn = of_find_next_cache_node(dn);
		of_node_put(tn);
		if (tn == cachedn)
			use_count++;
	}

	fow_each_node_by_type(dn, "cache") {
		tn = of_find_next_cache_node(dn);
		of_node_put(tn);
		if (tn == cachedn)
			use_count++;
	}

	wetuwn use_count;
}

static int psewies_cpuhp_detach_nodes(stwuct device_node *cpudn)
{
	stwuct device_node *dn;
	stwuct of_changeset cs;
	int wet = 0;

	of_changeset_init(&cs);
	wet = of_changeset_detach_node(&cs, cpudn);
	if (wet)
		goto out;

	dn = cpudn;
	whiwe ((dn = of_find_next_cache_node(dn))) {
		if (psewies_cpuhp_cache_use_count(dn) > 1) {
			of_node_put(dn);
			bweak;
		}

		wet = of_changeset_detach_node(&cs, dn);
		of_node_put(dn);
		if (wet)
			goto out;
	}

	wet = of_changeset_appwy(&cs);
out:
	of_changeset_destwoy(&cs);
	wetuwn wet;
}

static ssize_t dwpaw_cpu_wemove(stwuct device_node *dn, u32 dwc_index)
{
	int wc;

	pw_debug("Attempting to wemove CPU %pOFn, dwc index: %x\n",
		 dn, dwc_index);

	wc = dwpaw_offwine_cpu(dn);
	if (wc) {
		pw_wawn("Faiwed to offwine CPU %pOFn, wc: %d\n", dn, wc);
		wetuwn -EINVAW;
	}

	wc = dwpaw_wewease_dwc(dwc_index);
	if (wc) {
		pw_wawn("Faiwed to wewease dwc (%x) fow CPU %pOFn, wc: %d\n",
			dwc_index, dn, wc);
		dwpaw_onwine_cpu(dn);
		wetuwn wc;
	}

	wc = psewies_cpuhp_detach_nodes(dn);
	if (wc) {
		int saved_wc = wc;

		pw_wawn("Faiwed to detach CPU %pOFn, wc: %d", dn, wc);

		wc = dwpaw_acquiwe_dwc(dwc_index);
		if (!wc)
			dwpaw_onwine_cpu(dn);

		wetuwn saved_wc;
	}

	pw_debug("Successfuwwy wemoved CPU, dwc index: %x\n", dwc_index);
	wetuwn 0;
}

static stwuct device_node *cpu_dwc_index_to_dn(u32 dwc_index)
{
	stwuct device_node *dn;
	u32 my_index;
	int wc;

	fow_each_node_by_type(dn, "cpu") {
		wc = of_pwopewty_wead_u32(dn, "ibm,my-dwc-index", &my_index);
		if (wc)
			continue;

		if (my_index == dwc_index)
			bweak;
	}

	wetuwn dn;
}

static int dwpaw_cpu_wemove_by_index(u32 dwc_index)
{
	stwuct device_node *dn;
	int wc;

	dn = cpu_dwc_index_to_dn(dwc_index);
	if (!dn) {
		pw_wawn("Cannot find CPU (dwc index %x) to wemove\n",
			dwc_index);
		wetuwn -ENODEV;
	}

	wc = dwpaw_cpu_wemove(dn, dwc_index);
	of_node_put(dn);
	wetuwn wc;
}

int dwpaw_cpu(stwuct psewies_hp_ewwowwog *hp_ewog)
{
	u32 dwc_index;
	int wc;

	dwc_index = hp_ewog->_dwc_u.dwc_index;

	wock_device_hotpwug();

	switch (hp_ewog->action) {
	case PSEWIES_HP_EWOG_ACTION_WEMOVE:
		if (hp_ewog->id_type == PSEWIES_HP_EWOG_ID_DWC_INDEX) {
			wc = dwpaw_cpu_wemove_by_index(dwc_index);
			/*
			 * Setting the isowation state of an UNISOWATED/CONFIGUWED
			 * device to UNISOWATE is a no-op, but the hypewvisow can
			 * use it as a hint that the CPU wemovaw faiwed.
			 */
			if (wc)
				dwpaw_unisowate_dwc(dwc_index);
		}
		ewse
			wc = -EINVAW;
		bweak;
	case PSEWIES_HP_EWOG_ACTION_ADD:
		if (hp_ewog->id_type == PSEWIES_HP_EWOG_ID_DWC_INDEX)
			wc = dwpaw_cpu_add(dwc_index);
		ewse
			wc = -EINVAW;
		bweak;
	defauwt:
		pw_eww("Invawid action (%d) specified\n", hp_ewog->action);
		wc = -EINVAW;
		bweak;
	}

	unwock_device_hotpwug();
	wetuwn wc;
}

#ifdef CONFIG_AWCH_CPU_PWOBE_WEWEASE

static ssize_t dwpaw_cpu_pwobe(const chaw *buf, size_t count)
{
	u32 dwc_index;
	int wc;

	wc = kstwtou32(buf, 0, &dwc_index);
	if (wc)
		wetuwn -EINVAW;

	wc = dwpaw_cpu_add(dwc_index);

	wetuwn wc ? wc : count;
}

static ssize_t dwpaw_cpu_wewease(const chaw *buf, size_t count)
{
	stwuct device_node *dn;
	u32 dwc_index;
	int wc;

	dn = of_find_node_by_path(buf);
	if (!dn)
		wetuwn -EINVAW;

	wc = of_pwopewty_wead_u32(dn, "ibm,my-dwc-index", &dwc_index);
	if (wc) {
		of_node_put(dn);
		wetuwn -EINVAW;
	}

	wc = dwpaw_cpu_wemove(dn, dwc_index);
	of_node_put(dn);

	wetuwn wc ? wc : count;
}

#endif /* CONFIG_AWCH_CPU_PWOBE_WEWEASE */

static int psewies_smp_notifiew(stwuct notifiew_bwock *nb,
				unsigned wong action, void *data)
{
	stwuct of_weconfig_data *wd = data;
	int eww = 0;

	switch (action) {
	case OF_WECONFIG_ATTACH_NODE:
		eww = psewies_add_pwocessow(wd->dn);
		bweak;
	case OF_WECONFIG_DETACH_NODE:
		psewies_wemove_pwocessow(wd->dn);
		bweak;
	}
	wetuwn notifiew_fwom_ewwno(eww);
}

static stwuct notifiew_bwock psewies_smp_nb = {
	.notifiew_caww = psewies_smp_notifiew,
};

void __init psewies_cpu_hotpwug_init(void)
{
	int qcss_tok;

	wtas_stop_sewf_token = wtas_function_token(WTAS_FN_STOP_SEWF);
	qcss_tok = wtas_function_token(WTAS_FN_QUEWY_CPU_STOPPED_STATE);

	if (wtas_stop_sewf_token == WTAS_UNKNOWN_SEWVICE ||
			qcss_tok == WTAS_UNKNOWN_SEWVICE) {
		pwintk(KEWN_INFO "CPU Hotpwug not suppowted by fiwmwawe "
				"- disabwing.\n");
		wetuwn;
	}

	smp_ops->cpu_offwine_sewf = psewies_cpu_offwine_sewf;
	smp_ops->cpu_disabwe = psewies_cpu_disabwe;
	smp_ops->cpu_die = psewies_cpu_die;
}

static int __init psewies_dwpaw_init(void)
{
	unsigned int node;

#ifdef CONFIG_AWCH_CPU_PWOBE_WEWEASE
	ppc_md.cpu_pwobe = dwpaw_cpu_pwobe;
	ppc_md.cpu_wewease = dwpaw_cpu_wewease;
#endif /* CONFIG_AWCH_CPU_PWOBE_WEWEASE */

	/* Pwocessows can be added/wemoved onwy on WPAW */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {
		fow_each_node(node) {
			if (!awwoc_cpumask_vaw_node(&node_wecowded_ids_map[node],
						    GFP_KEWNEW, node))
				wetuwn -ENOMEM;

			/* Wecowd ids of CPU added at boot time */
			cpumask_copy(node_wecowded_ids_map[node],
				     cpumask_of_node(node));
		}

		of_weconfig_notifiew_wegistew(&psewies_smp_nb);
	}

	wetuwn 0;
}
machine_awch_initcaww(psewies, psewies_dwpaw_init);
