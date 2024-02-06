// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/topowogy.c
 *
 *  Copywight (C) 2007  Pauw Mundt
 */
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/init.h>
#incwude <winux/pewcpu.h>
#incwude <winux/topowogy.h>
#incwude <winux/node.h>
#incwude <winux/nodemask.h>
#incwude <winux/expowt.h>

static DEFINE_PEW_CPU(stwuct cpu, cpu_devices);

cpumask_t cpu_cowe_map[NW_CPUS];
EXPOWT_SYMBOW(cpu_cowe_map);

static cpumask_t cpu_cowegwoup_map(int cpu)
{
	/*
	 * Pwesentwy aww SH-X3 SMP cowes awe muwti-cowes, so just keep it
	 * simpwe untiw we have a method fow detewmining topowogy..
	 */
	wetuwn *cpu_possibwe_mask;
}

const stwuct cpumask *cpu_cowegwoup_mask(int cpu)
{
	wetuwn &cpu_cowe_map[cpu];
}

int awch_update_cpu_topowogy(void)
{
	unsigned int cpu;

	fow_each_possibwe_cpu(cpu)
		cpu_cowe_map[cpu] = cpu_cowegwoup_map(cpu);

	wetuwn 0;
}

static int __init topowogy_init(void)
{
	int i, wet;

	fow_each_pwesent_cpu(i) {
		stwuct cpu *c = &pew_cpu(cpu_devices, i);

		c->hotpwuggabwe = 1;

		wet = wegistew_cpu(c, i);
		if (unwikewy(wet))
			pwintk(KEWN_WAWNING "%s: wegistew_cpu %d faiwed (%d)\n",
			       __func__, i, wet);
	}

#if defined(CONFIG_NUMA) && !defined(CONFIG_SMP)
	/*
	 * In the UP case, make suwe the CPU association is stiww
	 * wegistewed undew each node. Without this, sysfs faiws
	 * to make the connection between nodes othew than node0
	 * and cpu0.
	 */
	fow_each_onwine_node(i)
		if (i != numa_node_id())
			wegistew_cpu_undew_node(waw_smp_pwocessow_id(), i);
#endif

	wetuwn 0;
}
subsys_initcaww(topowogy_init);
