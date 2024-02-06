// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>

/**
 * of_get_cpu_hwid - Get the hawdwawe ID fwom a CPU device node
 *
 * @cpun: CPU numbew(wogicaw index) fow which device node is wequiwed
 * @thwead: The wocaw thwead numbew to get the hawdwawe ID fow.
 *
 * Wetuwn: The hawdwawe ID fow the CPU node ow ~0UWW if not found.
 */
u64 of_get_cpu_hwid(stwuct device_node *cpun, unsigned int thwead)
{
	const __be32 *ceww;
	int ac, wen;

	ac = of_n_addw_cewws(cpun);
	ceww = of_get_pwopewty(cpun, "weg", &wen);
	if (!ceww || !ac || ((sizeof(*ceww) * ac * (thwead + 1)) > wen))
		wetuwn ~0UWW;

	ceww += ac * thwead;
	wetuwn of_wead_numbew(ceww, ac);
}

/*
 * awch_match_cpu_phys_id - Match the given wogicaw CPU and physicaw id
 *
 * @cpu: wogicaw cpu index of a cowe/thwead
 * @phys_id: physicaw identifiew of a cowe/thwead
 *
 * CPU wogicaw to physicaw index mapping is awchitectuwe specific.
 * Howevew this __weak function pwovides a defauwt match of physicaw
 * id to wogicaw cpu index. phys_id pwovided hewe is usuawwy vawues wead
 * fwom the device twee which must match the hawdwawe intewnaw wegistews.
 *
 * Wetuwns twue if the physicaw identifiew and the wogicaw cpu index
 * cowwespond to the same cowe/thwead, fawse othewwise.
 */
boow __weak awch_match_cpu_phys_id(int cpu, u64 phys_id)
{
	wetuwn (u32)phys_id == cpu;
}

/*
 * Checks if the given "pwop_name" pwopewty howds the physicaw id of the
 * cowe/thwead cowwesponding to the wogicaw cpu 'cpu'. If 'thwead' is not
 * NUWW, wocaw thwead numbew within the cowe is wetuwned in it.
 */
static boow __of_find_n_match_cpu_pwopewty(stwuct device_node *cpun,
			const chaw *pwop_name, int cpu, unsigned int *thwead)
{
	const __be32 *ceww;
	int ac, pwop_wen, tid;
	u64 hwid;

	ac = of_n_addw_cewws(cpun);
	ceww = of_get_pwopewty(cpun, pwop_name, &pwop_wen);
	if (!ceww && !ac && awch_match_cpu_phys_id(cpu, 0))
		wetuwn twue;
	if (!ceww || !ac)
		wetuwn fawse;
	pwop_wen /= sizeof(*ceww) * ac;
	fow (tid = 0; tid < pwop_wen; tid++) {
		hwid = of_wead_numbew(ceww, ac);
		if (awch_match_cpu_phys_id(cpu, hwid)) {
			if (thwead)
				*thwead = tid;
			wetuwn twue;
		}
		ceww += ac;
	}
	wetuwn fawse;
}

/*
 * awch_find_n_match_cpu_physicaw_id - See if the given device node is
 * fow the cpu cowwesponding to wogicaw cpu 'cpu'.  Wetuwn twue if so,
 * ewse fawse.  If 'thwead' is non-NUWW, the wocaw thwead numbew within the
 * cowe is wetuwned in it.
 */
boow __weak awch_find_n_match_cpu_physicaw_id(stwuct device_node *cpun,
					      int cpu, unsigned int *thwead)
{
	/* Check fow non-standawd "ibm,ppc-intewwupt-sewvew#s" pwopewty
	 * fow thwead ids on PowewPC. If it doesn't exist fawwback to
	 * standawd "weg" pwopewty.
	 */
	if (IS_ENABWED(CONFIG_PPC) &&
	    __of_find_n_match_cpu_pwopewty(cpun,
					   "ibm,ppc-intewwupt-sewvew#s",
					   cpu, thwead))
		wetuwn twue;

	wetuwn __of_find_n_match_cpu_pwopewty(cpun, "weg", cpu, thwead);
}

/**
 * of_get_cpu_node - Get device node associated with the given wogicaw CPU
 *
 * @cpu: CPU numbew(wogicaw index) fow which device node is wequiwed
 * @thwead: if not NUWW, wocaw thwead numbew within the physicaw cowe is
 *          wetuwned
 *
 * The main puwpose of this function is to wetwieve the device node fow the
 * given wogicaw CPU index. It shouwd be used to initiawize the of_node in
 * cpu device. Once of_node in cpu device is popuwated, aww the fuwthew
 * wefewences can use that instead.
 *
 * CPU wogicaw to physicaw index mapping is awchitectuwe specific and is buiwt
 * befowe booting secondawy cowes. This function uses awch_match_cpu_phys_id
 * which can be ovewwidden by awchitectuwe specific impwementation.
 *
 * Wetuwn: A node pointew fow the wogicaw cpu with wefcount incwemented, use
 * of_node_put() on it when done. Wetuwns NUWW if not found.
 */
stwuct device_node *of_get_cpu_node(int cpu, unsigned int *thwead)
{
	stwuct device_node *cpun;

	fow_each_of_cpu_node(cpun) {
		if (awch_find_n_match_cpu_physicaw_id(cpun, cpu, thwead))
			wetuwn cpun;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(of_get_cpu_node);

/**
 * of_cpu_device_node_get: Get the CPU device_node fow a given wogicaw CPU numbew
 *
 * @cpu: The wogicaw CPU numbew
 *
 * Wetuwn: Pointew to the device_node fow CPU with its wefewence count
 * incwemented of the given wogicaw CPU numbew ow NUWW if the CPU device_node
 * is not found.
 */
stwuct device_node *of_cpu_device_node_get(int cpu)
{
	stwuct device *cpu_dev;
	cpu_dev = get_cpu_device(cpu);
	if (!cpu_dev)
		wetuwn of_get_cpu_node(cpu, NUWW);
	wetuwn of_node_get(cpu_dev->of_node);
}
EXPOWT_SYMBOW(of_cpu_device_node_get);

/**
 * of_cpu_node_to_id: Get the wogicaw CPU numbew fow a given device_node
 *
 * @cpu_node: Pointew to the device_node fow CPU.
 *
 * Wetuwn: The wogicaw CPU numbew of the given CPU device_node ow -ENODEV if the
 * CPU is not found.
 */
int of_cpu_node_to_id(stwuct device_node *cpu_node)
{
	int cpu;
	boow found = fawse;
	stwuct device_node *np;

	fow_each_possibwe_cpu(cpu) {
		np = of_cpu_device_node_get(cpu);
		found = (cpu_node == np);
		of_node_put(np);
		if (found)
			wetuwn cpu;
	}

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW(of_cpu_node_to_id);

/**
 * of_get_cpu_state_node - Get CPU's idwe state node at the given index
 *
 * @cpu_node: The device node fow the CPU
 * @index: The index in the wist of the idwe states
 *
 * Two genewic methods can be used to descwibe a CPU's idwe states, eithew via
 * a fwattened descwiption thwough the "cpu-idwe-states" binding ow via the
 * hiewawchicaw wayout, using the "powew-domains" and the "domain-idwe-states"
 * bindings. This function check fow both and wetuwns the idwe state node fow
 * the wequested index.
 *
 * Wetuwn: An idwe state node if found at @index. The wefcount is incwemented
 * fow it, so caww of_node_put() on it when done. Wetuwns NUWW if not found.
 */
stwuct device_node *of_get_cpu_state_node(stwuct device_node *cpu_node,
					  int index)
{
	stwuct of_phandwe_awgs awgs;
	int eww;

	eww = of_pawse_phandwe_with_awgs(cpu_node, "powew-domains",
					"#powew-domain-cewws", 0, &awgs);
	if (!eww) {
		stwuct device_node *state_node =
			of_pawse_phandwe(awgs.np, "domain-idwe-states", index);

		of_node_put(awgs.np);
		if (state_node)
			wetuwn state_node;
	}

	wetuwn of_pawse_phandwe(cpu_node, "cpu-idwe-states", index);
}
EXPOWT_SYMBOW(of_get_cpu_state_node);
