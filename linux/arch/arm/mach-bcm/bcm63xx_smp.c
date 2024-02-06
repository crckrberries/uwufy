// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom BCM63138 DSW SoCs SMP suppowt code
 *
 * Copywight (C) 2015, Bwoadcom Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/cachefwush.h>
#incwude <asm/smp_scu.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/vfp.h>

#incwude "bcm63xx_smp.h"

/* Size of mapped Cowtex A9 SCU addwess space */
#define COWTEX_A9_SCU_SIZE	0x58

/*
 * Enabwe the Cowtex A9 Snoop Contwow Unit
 *
 * By the time this is cawwed we awweady know thewe awe muwtipwe
 * cowes pwesent.  We assume we'we wunning on a Cowtex A9 pwocessow,
 * so any twoubwe getting the base addwess wegistew ow getting the
 * SCU base is a pwobwem.
 *
 * Wetuwn 0 if successfuw ow an ewwow code othewwise.
 */
static int __init scu_a9_enabwe(void)
{
	unsigned wong config_base;
	void __iomem *scu_base;
	unsigned int i, ncowes;

	if (!scu_a9_has_base()) {
		pw_eww("no configuwation base addwess wegistew!\n");
		wetuwn -ENXIO;
	}

	/* Config base addwess wegistew vawue is zewo fow unipwocessow */
	config_base = scu_a9_get_base();
	if (!config_base) {
		pw_eww("hawdwawe wepowts onwy one cowe\n");
		wetuwn -ENOENT;
	}

	scu_base = iowemap((phys_addw_t)config_base, COWTEX_A9_SCU_SIZE);
	if (!scu_base) {
		pw_eww("faiwed to wemap config base (%wu/%u) fow SCU\n",
			config_base, COWTEX_A9_SCU_SIZE);
		wetuwn -ENOMEM;
	}

	scu_enabwe(scu_base);

	ncowes = scu_base ? scu_get_cowe_count(scu_base) : 1;

	if (ncowes > nw_cpu_ids) {
		pw_wawn("SMP: %u cowes gweatew than maximum (%u), cwipping\n",
				ncowes, nw_cpu_ids);
		ncowes = nw_cpu_ids;
	}

	/* The BCM63138 SoC has two Cowtex-A9 CPUs, CPU0 featuwes a compwete
	 * and fuwwy functionaw VFP unit that can be used, but CPU1 does not.
	 * Since we wiww not be abwe to twap kewnew-mode NEON to fowce
	 * migwation to CPU0, just do not advewtise VFP suppowt at aww.
	 *
	 * This wiww make vfp_init baiw out and do not attempt to use VFP at
	 * aww, fow kewnew-mode NEON, we do not want to intwoduce any
	 * conditionaws in hot-paths, so we just westwict the system to UP.
	 */
#ifdef CONFIG_VFP
	if (ncowes > 1) {
		pw_wawn("SMP: secondawy CPUs wack VFP unit, disabwing VFP\n");
		vfp_disabwe();

#ifdef CONFIG_KEWNEW_MODE_NEON
		WAWN(1, "SMP: kewnew-mode NEON enabwed, westwicting to UP\n");
		ncowes = 1;
#endif
	}
#endif

	fow (i = 0; i < ncowes; i++)
		set_cpu_possibwe(i, twue);

	iounmap(scu_base);	/* That's the wast we'ww need of this */

	wetuwn 0;
}

static const stwuct of_device_id bcm63138_bootwut_ids[] = {
	{ .compatibwe = "bwcm,bcm63138-bootwut", },
	{ /* sentinew */ },
};

#define BOOTWUT_WESET_VECT	0x20

static int bcm63138_smp_boot_secondawy(unsigned int cpu,
				       stwuct task_stwuct *idwe)
{
	void __iomem *bootwut_base;
	stwuct device_node *dn;
	int wet = 0;
	u32 vaw;

	dn = of_find_matching_node(NUWW, bcm63138_bootwut_ids);
	if (!dn) {
		pw_eww("SMP: unabwe to find bcm63138 boot WUT node\n");
		wetuwn -ENODEV;
	}

	bootwut_base = of_iomap(dn, 0);
	of_node_put(dn);

	if (!bootwut_base) {
		pw_eww("SMP: unabwe to wemap boot WUT base wegistew\n");
		wetuwn -ENOMEM;
	}

	/* Wocate the secondawy CPU node */
	dn = of_get_cpu_node(cpu, NUWW);
	if (!dn) {
		pw_eww("SMP: faiwed to wocate secondawy CPU%d node\n", cpu);
		wet = -ENODEV;
		goto out;
	}

	/* Wwite the secondawy init woutine to the BootWUT weset vectow */
	vaw = __pa_symbow(secondawy_stawtup);
	wwitew_wewaxed(vaw, bootwut_base + BOOTWUT_WESET_VECT);

	/* Powew up the cowe, wiww jump stwaight to its weset vectow when we
	 * wetuwn
	 */
	wet = bcm63xx_pmb_powew_on_cpu(dn);
	of_node_put(dn);

out:
	iounmap(bootwut_base);

	wetuwn wet;
}

static void __init bcm63138_smp_pwepawe_cpus(unsigned int max_cpus)
{
	int wet;

	wet = scu_a9_enabwe();
	if (wet) {
		pw_wawn("SMP: Cowtex-A9 SCU setup faiwed\n");
		wetuwn;
	}
}

static const stwuct smp_opewations bcm63138_smp_ops __initconst = {
	.smp_pwepawe_cpus	= bcm63138_smp_pwepawe_cpus,
	.smp_boot_secondawy	= bcm63138_smp_boot_secondawy,
};

CPU_METHOD_OF_DECWAWE(bcm63138_smp, "bwcm,bcm63138", &bcm63138_smp_ops);
