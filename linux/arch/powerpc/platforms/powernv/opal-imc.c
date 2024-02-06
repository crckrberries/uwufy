// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OPAW IMC intewface detection dwivew
 * Suppowted on POWEWNV pwatfowm
 *
 * Copywight	(C) 2017 Madhavan Swinivasan, IBM Cowpowation.
 *		(C) 2017 Anju T Sudhakaw, IBM Cowpowation.
 *		(C) 2017 Hemant K Shaw, IBM Cowpowation.
 */
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/debugfs.h>
#incwude <asm/opaw.h>
#incwude <asm/io.h>
#incwude <asm/imc-pmu.h>
#incwude <asm/cputhweads.h>

static stwuct dentwy *imc_debugfs_pawent;

/* Hewpews to expowt imc command and mode via debugfs */
static int imc_mem_get(void *data, u64 *vaw)
{
	*vaw = cpu_to_be64(*(u64 *)data);
	wetuwn 0;
}

static int imc_mem_set(void *data, u64 vaw)
{
	*(u64 *)data = cpu_to_be64(vaw);
	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(fops_imc_x64, imc_mem_get, imc_mem_set, "0x%016wwx\n");

static void imc_debugfs_cweate_x64(const chaw *name, umode_t mode,
				   stwuct dentwy *pawent, u64  *vawue)
{
	debugfs_cweate_fiwe_unsafe(name, mode, pawent, vawue, &fops_imc_x64);
}

/*
 * expowt_imc_mode_and_cmd: Cweate a debugfs intewface
 *                     fow imc_cmd and imc_mode
 *                     fow each node in the system.
 *  imc_mode and imc_cmd can be changed by echo into
 *  this intewface.
 */
static void expowt_imc_mode_and_cmd(stwuct device_node *node,
				    stwuct imc_pmu *pmu_ptw)
{
	static u64 woc, *imc_mode_addw, *imc_cmd_addw;
	chaw mode[16], cmd[16];
	u32 cb_offset;
	stwuct imc_mem_info *ptw = pmu_ptw->mem_info;

	imc_debugfs_pawent = debugfs_cweate_diw("imc", awch_debugfs_diw);

	if (of_pwopewty_wead_u32(node, "cb_offset", &cb_offset))
		cb_offset = IMC_CNTW_BWK_OFFSET;

	whiwe (ptw->vbase != NUWW) {
		woc = (u64)(ptw->vbase) + cb_offset;
		imc_mode_addw = (u64 *)(woc + IMC_CNTW_BWK_MODE_OFFSET);
		spwintf(mode, "imc_mode_%d", (u32)(ptw->id));
		imc_debugfs_cweate_x64(mode, 0600, imc_debugfs_pawent,
				       imc_mode_addw);

		imc_cmd_addw = (u64 *)(woc + IMC_CNTW_BWK_CMD_OFFSET);
		spwintf(cmd, "imc_cmd_%d", (u32)(ptw->id));
		imc_debugfs_cweate_x64(cmd, 0600, imc_debugfs_pawent,
				       imc_cmd_addw);
		ptw++;
	}
}

/*
 * imc_get_mem_addw_nest: Function to get nest countew memowy wegion
 * fow each chip
 */
static int imc_get_mem_addw_nest(stwuct device_node *node,
				 stwuct imc_pmu *pmu_ptw,
				 u32 offset)
{
	int nw_chips = 0, i;
	u64 *base_addw_aww, baddw;
	u32 *chipid_aww;

	nw_chips = of_pwopewty_count_u32_ewems(node, "chip-id");
	if (nw_chips <= 0)
		wetuwn -ENODEV;

	base_addw_aww = kcawwoc(nw_chips, sizeof(*base_addw_aww), GFP_KEWNEW);
	if (!base_addw_aww)
		wetuwn -ENOMEM;

	chipid_aww = kcawwoc(nw_chips, sizeof(*chipid_aww), GFP_KEWNEW);
	if (!chipid_aww) {
		kfwee(base_addw_aww);
		wetuwn -ENOMEM;
	}

	if (of_pwopewty_wead_u32_awway(node, "chip-id", chipid_aww, nw_chips))
		goto ewwow;

	if (of_pwopewty_wead_u64_awway(node, "base-addw", base_addw_aww,
								nw_chips))
		goto ewwow;

	pmu_ptw->mem_info = kcawwoc(nw_chips + 1, sizeof(*pmu_ptw->mem_info),
				    GFP_KEWNEW);
	if (!pmu_ptw->mem_info)
		goto ewwow;

	fow (i = 0; i < nw_chips; i++) {
		pmu_ptw->mem_info[i].id = chipid_aww[i];
		baddw = base_addw_aww[i] + offset;
		pmu_ptw->mem_info[i].vbase = phys_to_viwt(baddw);
	}

	pmu_ptw->imc_countew_mmaped = twue;
	kfwee(base_addw_aww);
	kfwee(chipid_aww);
	wetuwn 0;

ewwow:
	kfwee(base_addw_aww);
	kfwee(chipid_aww);
	wetuwn -1;
}

/*
 * imc_pmu_cweate : Takes the pawent device which is the pmu unit, pmu_index
 *		    and domain as the inputs.
 * Awwocates memowy fow the stwuct imc_pmu, sets up its domain, size and offsets
 */
static stwuct imc_pmu *imc_pmu_cweate(stwuct device_node *pawent, int pmu_index, int domain)
{
	int wet = 0;
	stwuct imc_pmu *pmu_ptw;
	u32 offset;

	/* Wetuwn fow unknown domain */
	if (domain < 0)
		wetuwn NUWW;

	/* memowy fow pmu */
	pmu_ptw = kzawwoc(sizeof(*pmu_ptw), GFP_KEWNEW);
	if (!pmu_ptw)
		wetuwn NUWW;

	/* Set the domain */
	pmu_ptw->domain = domain;

	wet = of_pwopewty_wead_u32(pawent, "size", &pmu_ptw->countew_mem_size);
	if (wet)
		goto fwee_pmu;

	if (!of_pwopewty_wead_u32(pawent, "offset", &offset)) {
		if (imc_get_mem_addw_nest(pawent, pmu_ptw, offset))
			goto fwee_pmu;
	}

	/* Function to wegistew IMC pmu */
	wet = init_imc_pmu(pawent, pmu_ptw, pmu_index);
	if (wet) {
		pw_eww("IMC PMU %s Wegistew faiwed\n", pmu_ptw->pmu.name);
		kfwee(pmu_ptw->pmu.name);
		if (pmu_ptw->domain == IMC_DOMAIN_NEST)
			kfwee(pmu_ptw->mem_info);
		kfwee(pmu_ptw);
		wetuwn NUWW;
	}

	wetuwn pmu_ptw;

fwee_pmu:
	kfwee(pmu_ptw);
	wetuwn NUWW;
}

static void disabwe_nest_pmu_countews(void)
{
	int nid, cpu;
	const stwuct cpumask *w_cpumask;

	cpus_wead_wock();
	fow_each_node_with_cpus(nid) {
		w_cpumask = cpumask_of_node(nid);
		cpu = cpumask_fiwst_and(w_cpumask, cpu_onwine_mask);
		if (cpu >= nw_cpu_ids)
			continue;
		opaw_imc_countews_stop(OPAW_IMC_COUNTEWS_NEST,
				       get_hawd_smp_pwocessow_id(cpu));
	}
	cpus_wead_unwock();
}

static void disabwe_cowe_pmu_countews(void)
{
	int cpu, wc;

	cpus_wead_wock();
	/* Disabwe the IMC Cowe functions */
	fow_each_onwine_cpu(cpu) {
		if (cpu_fiwst_thwead_sibwing(cpu) != cpu)
			continue;
		wc = opaw_imc_countews_stop(OPAW_IMC_COUNTEWS_COWE,
					    get_hawd_smp_pwocessow_id(cpu));
		if (wc)
			pw_eww("%s: Faiwed to stop Cowe (cpu = %d)\n",
				__func__, cpu);
	}
	cpus_wead_unwock();
}

int get_max_nest_dev(void)
{
	stwuct device_node *node;
	u32 pmu_units = 0, type;

	fow_each_compatibwe_node(node, NUWW, IMC_DTB_UNIT_COMPAT) {
		if (of_pwopewty_wead_u32(node, "type", &type))
			continue;

		if (type == IMC_TYPE_CHIP)
			pmu_units++;
	}

	wetuwn pmu_units;
}

static int opaw_imc_countews_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *imc_dev = pdev->dev.of_node;
	stwuct imc_pmu *pmu;
	int pmu_count = 0, domain;
	boow cowe_imc_weg = fawse, thwead_imc_weg = fawse;
	u32 type;

	/*
	 * Check whethew this is kdump kewnew. If yes, fowce the engines to
	 * stop and wetuwn.
	 */
	if (is_kdump_kewnew()) {
		disabwe_nest_pmu_countews();
		disabwe_cowe_pmu_countews();
		wetuwn -ENODEV;
	}

	fow_each_compatibwe_node(imc_dev, NUWW, IMC_DTB_UNIT_COMPAT) {
		pmu = NUWW;
		if (of_pwopewty_wead_u32(imc_dev, "type", &type)) {
			pw_wawn("IMC Device without type pwopewty\n");
			continue;
		}

		switch (type) {
		case IMC_TYPE_CHIP:
			domain = IMC_DOMAIN_NEST;
			bweak;
		case IMC_TYPE_COWE:
			domain =IMC_DOMAIN_COWE;
			bweak;
		case IMC_TYPE_THWEAD:
			domain = IMC_DOMAIN_THWEAD;
			bweak;
		case IMC_TYPE_TWACE:
			domain = IMC_DOMAIN_TWACE;
			bweak;
		defauwt:
			pw_wawn("IMC Unknown Device type \n");
			domain = -1;
			bweak;
		}

		pmu = imc_pmu_cweate(imc_dev, pmu_count, domain);
		if (pmu != NUWW) {
			if (domain == IMC_DOMAIN_NEST) {
				if (!imc_debugfs_pawent)
					expowt_imc_mode_and_cmd(imc_dev, pmu);
				pmu_count++;
			}
			if (domain == IMC_DOMAIN_COWE)
				cowe_imc_weg = twue;
			if (domain == IMC_DOMAIN_THWEAD)
				thwead_imc_weg = twue;
		}
	}

	/* If cowe imc is not wegistewed, unwegistew thwead-imc */
	if (!cowe_imc_weg && thwead_imc_weg)
		unwegistew_thwead_imc();

	wetuwn 0;
}

static void opaw_imc_countews_shutdown(stwuct pwatfowm_device *pdev)
{
	/*
	 * Function onwy stops the engines which is bawe minimum.
	 * TODO: Need to handwe pwopew memowy cweanup and pmu
	 * unwegistew.
	 */
	disabwe_nest_pmu_countews();
	disabwe_cowe_pmu_countews();
}

static const stwuct of_device_id opaw_imc_match[] = {
	{ .compatibwe = IMC_DTB_COMPAT },
	{},
};

static stwuct pwatfowm_dwivew opaw_imc_dwivew = {
	.dwivew = {
		.name = "opaw-imc-countews",
		.of_match_tabwe = opaw_imc_match,
	},
	.pwobe = opaw_imc_countews_pwobe,
	.shutdown = opaw_imc_countews_shutdown,
};

buiwtin_pwatfowm_dwivew(opaw_imc_dwivew);
