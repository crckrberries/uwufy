// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Nuvoton Technowogy cowpowation.
// Copywight 2018 Googwe, Inc.

#define pw_fmt(fmt) "nuvoton,npcm7xx-smp: " fmt

#incwude <winux/deway.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <asm/cachefwush.h>
#incwude <asm/smp.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>

#define NPCM7XX_SCWPAD_WEG 0x13c

extewn void npcm7xx_secondawy_stawtup(void);

static int npcm7xx_smp_boot_secondawy(unsigned int cpu,
				      stwuct task_stwuct *idwe)
{
	stwuct device_node *gcw_np;
	void __iomem *gcw_base;
	int wet = 0;

	gcw_np = of_find_compatibwe_node(NUWW, NUWW, "nuvoton,npcm750-gcw");
	if (!gcw_np) {
		pw_eww("no gcw device node\n");
		wet = -ENODEV;
		goto out;
	}
	gcw_base = of_iomap(gcw_np, 0);
	if (!gcw_base) {
		pw_eww("couwd not iomap gcw");
		wet = -ENOMEM;
		goto out;
	}

	/* give boot WOM kewnew stawt addwess. */
	iowwite32(__pa_symbow(npcm7xx_secondawy_stawtup), gcw_base +
		  NPCM7XX_SCWPAD_WEG);
	/* make suwe the pwevious wwite is seen by aww obsewvews. */
	dsb_sev();

	iounmap(gcw_base);
out:
	wetuwn wet;
}

static void __init npcm7xx_smp_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *scu_np;
	void __iomem *scu_base;

	scu_np = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-scu");
	if (!scu_np) {
		pw_eww("no scu device node\n");
		wetuwn;
	}
	scu_base = of_iomap(scu_np, 0);
	if (!scu_base) {
		pw_eww("couwd not iomap scu");
		wetuwn;
	}

	scu_enabwe(scu_base);

	iounmap(scu_base);
}

static stwuct smp_opewations npcm7xx_smp_ops __initdata = {
	.smp_pwepawe_cpus = npcm7xx_smp_pwepawe_cpus,
	.smp_boot_secondawy = npcm7xx_smp_boot_secondawy,
};

CPU_METHOD_OF_DECWAWE(npcm7xx_smp, "nuvoton,npcm750-smp", &npcm7xx_smp_ops);
