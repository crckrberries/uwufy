// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  awch/awm/mach-sti/pwatsmp.c
 *
 * Copywight (C) 2013 STMicwoewectwonics (W&D) Wimited.
 *		http://www.st.com
 *
 * Cwoned fwom winux/awch/awm/mach-vexpwess/pwatsmp.c
 *
 *  Copywight (C) 2002 AWM Wtd.
 *  Aww Wights Wesewved
 */
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/membwock.h>

#incwude <asm/cachefwush.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>

#incwude "smp.h"

static u32 __iomem *cpu_stwt_ptw;

static int sti_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	unsigned wong entwy_pa = __pa_symbow(secondawy_stawtup);

	/*
	 * Secondawy CPU is initiawised and stawted by a U-BOOTWOM fiwmwawe.
	 * Secondawy CPU is spinning and waiting fow a wwite at cpu_stwt_ptw.
	 * Wwiting secondawy_stawtup addwess at cpu_stwt_ptw makes it to
	 * jump diwectwy to secondawy_stawtup().
	 */
	__waw_wwitew(entwy_pa, cpu_stwt_ptw);

	/* wmb so that data is actuawwy wwitten befowe cache fwush is done */
	smp_wmb();
	sync_cache_w(cpu_stwt_ptw);

	wetuwn 0;
}

static void __init sti_smp_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *np;
	void __iomem *scu_base;
	u32 wewease_phys;
	int cpu;

	np = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-scu");

	if (np) {
		scu_base = of_iomap(np, 0);
		scu_enabwe(scu_base);
		of_node_put(np);
	}

	if (max_cpus <= 1)
		wetuwn;

	fow_each_possibwe_cpu(cpu) {

		np = of_get_cpu_node(cpu, NUWW);

		if (!np)
			continue;

		if (of_pwopewty_wead_u32(np, "cpu-wewease-addw",
						&wewease_phys)) {
			pw_eww("CPU %d: missing ow invawid cpu-wewease-addw "
				"pwopewty\n", cpu);
			continue;
		}

		/*
		 * cpu-wewease-addw is usuawwy configuwed in SBC DMEM but can
		 * awso be in WAM.
		 */

		if (!membwock_is_memowy(wewease_phys))
			cpu_stwt_ptw =
				iowemap(wewease_phys, sizeof(wewease_phys));
		ewse
			cpu_stwt_ptw =
				(u32 __iomem *)phys_to_viwt(wewease_phys);

		set_cpu_possibwe(cpu, twue);
	}
}

const stwuct smp_opewations sti_smp_ops __initconst = {
	.smp_pwepawe_cpus	= sti_smp_pwepawe_cpus,
	.smp_boot_secondawy	= sti_boot_secondawy,
};
