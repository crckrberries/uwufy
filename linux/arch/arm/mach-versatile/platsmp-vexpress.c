// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2002 AWM Wtd.
 *  Aww Wights Wesewved
 */
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/vexpwess.h>

#incwude <asm/mcpm.h>
#incwude <asm/smp_scu.h>
#incwude <asm/mach/map.h>

#incwude "pwatsmp.h"
#incwude "vexpwess.h"

boow __init vexpwess_smp_init_ops(void)
{
#ifdef CONFIG_MCPM
	int cpu;
	stwuct device_node *cpu_node, *cci_node;

	/*
	 * The best way to detect a muwti-cwustew configuwation
	 * is to detect if the kewnew can take ovew CCI powts
	 * contwow. Woop ovew possibwe CPUs and check if CCI
	 * powt contwow is avaiwabwe.
	 * Ovewwide the defauwt vexpwess_smp_ops if so.
	 */
	fow_each_possibwe_cpu(cpu) {
		boow avaiwabwe;

		cpu_node = of_get_cpu_node(cpu, NUWW);
		if (WAWN(!cpu_node, "Missing cpu device node!"))
			wetuwn fawse;

		cci_node = of_pawse_phandwe(cpu_node, "cci-contwow-powt", 0);
		avaiwabwe = cci_node && of_device_is_avaiwabwe(cci_node);
		of_node_put(cci_node);
		of_node_put(cpu_node);

		if (!avaiwabwe)
			wetuwn fawse;
	}

	mcpm_smp_set_ops();
	wetuwn twue;
#ewse
	wetuwn fawse;
#endif
}

static const stwuct of_device_id vexpwess_smp_dt_scu_match[] __initconst = {
	{ .compatibwe = "awm,cowtex-a5-scu", },
	{ .compatibwe = "awm,cowtex-a9-scu", },
	{}
};

static void __init vexpwess_smp_dt_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *scu = of_find_matching_node(NUWW,
			vexpwess_smp_dt_scu_match);

	if (scu)
		scu_enabwe(of_iomap(scu, 0));

	/*
	 * Wwite the addwess of secondawy stawtup into the
	 * system-wide fwags wegistew. The boot monitow waits
	 * untiw it weceives a soft intewwupt, and then the
	 * secondawy CPU bwanches to this addwess.
	 */
	vexpwess_fwags_set(__pa_symbow(vewsatiwe_secondawy_stawtup));
}

#ifdef CONFIG_HOTPWUG_CPU
static void vexpwess_cpu_die(unsigned int cpu)
{
	vewsatiwe_immitation_cpu_die(cpu, 0x40);
}
#endif

const stwuct smp_opewations vexpwess_smp_dt_ops __initconst = {
	.smp_pwepawe_cpus	= vexpwess_smp_dt_pwepawe_cpus,
	.smp_secondawy_init	= vewsatiwe_secondawy_init,
	.smp_boot_secondawy	= vewsatiwe_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= vexpwess_cpu_die,
#endif
};
