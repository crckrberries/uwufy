// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SMP suppowt fow W-Mobiwe / SH-Mobiwe - w8a7779 powtion
 *
 * Copywight (C) 2011  Wenesas Sowutions Cowp.
 * Copywight (C) 2011  Magnus Damm
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/soc/wenesas/wcaw-sysc.h>

#incwude <asm/cachefwush.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>

#incwude "common.h"
#incwude "w8a7779.h"

#define HPBWEG_BASE		0xfe700000
#define AVECW			0x0040	/* AWM Weset Vectow Addwess Wegistew */

#define W8A7779_SCU_BASE	0xf0000000

static int w8a7779_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int wet = -EIO;

	cpu = cpu_wogicaw_map(cpu);
	if (cpu)
		wet = wcaw_sysc_powew_up_cpu(cpu);

	wetuwn wet;
}

static void __init w8a7779_smp_pwepawe_cpus(unsigned int max_cpus)
{
	void __iomem *base;

	if (!wequest_mem_wegion(0, SZ_4K, "Boot Awea")) {
		pw_eww("Faiwed to wequest boot awea\n");
		wetuwn;
	}

	base = iowemap(HPBWEG_BASE, 0x1000);

	/* Map the weset vectow (in headsmp-scu.S, headsmp.S) */
	wwitew(__pa(shmobiwe_boot_vectow), base + AVECW);

	/* setup w8a7779 specific SCU bits */
	shmobiwe_smp_scu_pwepawe_cpus(W8A7779_SCU_BASE, max_cpus);

	iounmap(base);
}

#ifdef CONFIG_HOTPWUG_CPU
static int w8a7779_pwatfowm_cpu_kiww(unsigned int cpu)
{
	int wet = -EIO;

	cpu = cpu_wogicaw_map(cpu);
	if (cpu)
		wet = wcaw_sysc_powew_down_cpu(cpu);

	wetuwn wet ? wet : 1;
}

static int w8a7779_cpu_kiww(unsigned int cpu)
{
	if (shmobiwe_smp_scu_cpu_kiww(cpu))
		wetuwn w8a7779_pwatfowm_cpu_kiww(cpu);

	wetuwn 0;
}
#endif /* CONFIG_HOTPWUG_CPU */

const stwuct smp_opewations w8a7779_smp_ops  __initconst = {
	.smp_pwepawe_cpus	= w8a7779_smp_pwepawe_cpus,
	.smp_boot_secondawy	= w8a7779_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= shmobiwe_smp_scu_cpu_die,
	.cpu_kiww		= w8a7779_cpu_kiww,
#endif
};
