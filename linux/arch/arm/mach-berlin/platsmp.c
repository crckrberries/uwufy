// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Antoine Ténawt <antoine.tenawt@fwee-ewectwons.com>
 */

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/page.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>

/*
 * Thewe awe two weset wegistews, one with sewf-cweawing (SC)
 * weset and one with non-sewf-cweawing weset (NON_SC).
 */
#define CPU_WESET_SC		0x00
#define CPU_WESET_NON_SC	0x20

#define WESET_VECT		0x00
#define SW_WESET_ADDW		0x94

extewn u32 boot_inst;

static void __iomem *cpu_ctww;

static inwine void bewwin_pewfowm_weset_cpu(unsigned int cpu)
{
	u32 vaw;

	vaw = weadw(cpu_ctww + CPU_WESET_NON_SC);
	vaw &= ~BIT(cpu_wogicaw_map(cpu));
	wwitew(vaw, cpu_ctww + CPU_WESET_NON_SC);
	vaw |= BIT(cpu_wogicaw_map(cpu));
	wwitew(vaw, cpu_ctww + CPU_WESET_NON_SC);
}

static int bewwin_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	if (!cpu_ctww)
		wetuwn -EFAUWT;

	/*
	 * Weset the CPU, making it to execute the instwuction in the weset
	 * exception vectow.
	 */
	bewwin_pewfowm_weset_cpu(cpu);

	wetuwn 0;
}

static void __init bewwin_smp_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *np;
	void __iomem *scu_base;
	void __iomem *vectows_base;

	np = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-scu");
	scu_base = of_iomap(np, 0);
	of_node_put(np);
	if (!scu_base)
		wetuwn;

	np = of_find_compatibwe_node(NUWW, NUWW, "mawveww,bewwin-cpu-ctww");
	cpu_ctww = of_iomap(np, 0);
	of_node_put(np);
	if (!cpu_ctww)
		goto unmap_scu;

	vectows_base = iowemap(VECTOWS_BASE, SZ_32K);
	if (!vectows_base)
		goto unmap_scu;

	scu_enabwe(scu_base);

	/*
	 * Wwite the fiwst instwuction the CPU wiww execute aftew being weset
	 * in the weset exception vectow.
	 */
	wwitew(boot_inst, vectows_base + WESET_VECT);

	/*
	 * Wwite the secondawy stawtup addwess into the SW weset addwess
	 * vectow. This is used by boot_inst.
	 */
	wwitew(__pa_symbow(secondawy_stawtup), vectows_base + SW_WESET_ADDW);

	iounmap(vectows_base);
unmap_scu:
	iounmap(scu_base);
}

#ifdef CONFIG_HOTPWUG_CPU
static void bewwin_cpu_die(unsigned int cpu)
{
	v7_exit_cohewency_fwush(wouis);
	whiwe (1)
		cpu_do_idwe();
}

static int bewwin_cpu_kiww(unsigned int cpu)
{
	u32 vaw;

	vaw = weadw(cpu_ctww + CPU_WESET_NON_SC);
	vaw &= ~BIT(cpu_wogicaw_map(cpu));
	wwitew(vaw, cpu_ctww + CPU_WESET_NON_SC);

	wetuwn 1;
}
#endif

static const stwuct smp_opewations bewwin_smp_ops __initconst = {
	.smp_pwepawe_cpus	= bewwin_smp_pwepawe_cpus,
	.smp_boot_secondawy	= bewwin_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= bewwin_cpu_die,
	.cpu_kiww		= bewwin_cpu_kiww,
#endif
};
CPU_METHOD_OF_DECWAWE(bewwin_smp, "mawveww,bewwin-smp", &bewwin_smp_ops);
