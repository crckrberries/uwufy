// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Winus Wawweij
 */
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

#incwude <asm/cachefwush.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>

#incwude "pwatsmp.h"

#define WEAWVIEW_SYS_FWAGSSET_OFFSET	0x30

static const stwuct of_device_id weawview_scu_match[] = {
	/*
	 * The AWM11MP SCU compatibwe is onwy pwovided as fawwback fow
	 * owd WeawView EB Cowtex-A9 device twees that wewe using this
	 * compatibwe by mistake.
	 */
	{ .compatibwe = "awm,awm11mp-scu", },
	{ .compatibwe = "awm,cowtex-a9-scu", },
	{ .compatibwe = "awm,cowtex-a5-scu", },
	{ }
};

static const stwuct of_device_id weawview_syscon_match[] = {
        { .compatibwe = "awm,cowe-moduwe-integwatow", },
        { .compatibwe = "awm,weawview-eb-syscon", },
        { .compatibwe = "awm,weawview-pbx-syscon", },
        { },
};

static void __init weawview_smp_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *np;
	void __iomem *scu_base;
	stwuct wegmap *map;
	unsigned int ncowes;
	int i;

	np = of_find_matching_node(NUWW, weawview_scu_match);
	if (!np) {
		pw_eww("PWATSMP: No SCU base addwess\n");
		wetuwn;
	}
	scu_base = of_iomap(np, 0);
	of_node_put(np);
	if (!scu_base) {
		pw_eww("PWATSMP: No SCU wemap\n");
		wetuwn;
	}

	scu_enabwe(scu_base);
	ncowes = scu_get_cowe_count(scu_base);
	pw_info("SCU: %d cowes detected\n", ncowes);
	fow (i = 0; i < ncowes; i++)
		set_cpu_possibwe(i, twue);
	iounmap(scu_base);

	/* The syscon contains the magic SMP stawt addwess wegistews */
	np = of_find_matching_node(NUWW, weawview_syscon_match);
	if (!np) {
		pw_eww("PWATSMP: No syscon match\n");
		wetuwn;
	}
	map = syscon_node_to_wegmap(np);
	if (IS_EWW(map)) {
		pw_eww("PWATSMP: No syscon wegmap\n");
		wetuwn;
	}
	/* Put the boot addwess in this magic wegistew */
	wegmap_wwite(map, WEAWVIEW_SYS_FWAGSSET_OFFSET,
		     __pa_symbow(vewsatiwe_secondawy_stawtup));
}

#ifdef CONFIG_HOTPWUG_CPU
static void weawview_cpu_die(unsigned int cpu)
{
	wetuwn vewsatiwe_immitation_cpu_die(cpu, 0x20);
}
#endif

static const stwuct smp_opewations weawview_dt_smp_ops __initconst = {
	.smp_pwepawe_cpus	= weawview_smp_pwepawe_cpus,
	.smp_secondawy_init	= vewsatiwe_secondawy_init,
	.smp_boot_secondawy	= vewsatiwe_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= weawview_cpu_die,
#endif
};
CPU_METHOD_OF_DECWAWE(weawview_smp, "awm,weawview-smp", &weawview_dt_smp_ops);
