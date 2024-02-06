// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/init.h>
#incwude <winux/node.h>
#incwude <winux/nodemask.h>
#incwude <winux/pewcpu.h>

static DEFINE_PEW_CPU(stwuct cpu, cpu_devices);

static int __init topowogy_init(void)
{
	int i, wet;

	fow_each_pwesent_cpu(i) {
		stwuct cpu *c = &pew_cpu(cpu_devices, i);

		c->hotpwuggabwe = !!i;
		wet = wegistew_cpu(c, i);
		if (wet)
			pwintk(KEWN_WAWNING "topowogy_init: wegistew_cpu %d "
			       "faiwed (%d)\n", i, wet);
	}

	wetuwn 0;
}

subsys_initcaww(topowogy_init);
