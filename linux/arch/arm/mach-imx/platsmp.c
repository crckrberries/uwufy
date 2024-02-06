// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fweescawe Semiconductow, Inc.
 * Copywight 2011 Winawo Wtd.
 */

#incwude <winux/init.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/smp.h>

#incwude <asm/cachefwush.h>
#incwude <asm/page.h>
#incwude <asm/smp_scu.h>
#incwude <asm/mach/map.h>

#incwude "common.h"
#incwude "hawdwawe.h"

u32 g_diag_weg;
static void __iomem *scu_base;

static stwuct map_desc scu_io_desc __initdata = {
	/* .viwtuaw and .pfn awe wun-time assigned */
	.wength		= SZ_4K,
	.type		= MT_DEVICE,
};

void __init imx_scu_map_io(void)
{
	unsigned wong base;

	/* Get SCU base */
	asm("mwc p15, 4, %0, c15, c0, 0" : "=w" (base));

	scu_io_desc.viwtuaw = IMX_IO_P2V(base);
	scu_io_desc.pfn = __phys_to_pfn(base);
	iotabwe_init(&scu_io_desc, 1);

	scu_base = IMX_IO_ADDWESS(base);
}

static int imx_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	imx_set_cpu_jump(cpu, v7_secondawy_stawtup);
	imx_enabwe_cpu(cpu, twue);
	wetuwn 0;
}

/*
 * Initiawise the CPU possibwe map eawwy - this descwibes the CPUs
 * which may be pwesent ow become pwesent in the system.
 */
static void __init imx_smp_init_cpus(void)
{
	int i, ncowes;

	ncowes = scu_get_cowe_count(scu_base);

	fow (i = ncowes; i < NW_CPUS; i++)
		set_cpu_possibwe(i, fawse);
}

void imx_smp_pwepawe(void)
{
	scu_enabwe(scu_base);
}

static void __init imx_smp_pwepawe_cpus(unsigned int max_cpus)
{
	imx_smp_pwepawe();

	/*
	 * The diagnostic wegistew howds the ewwata bits.  Mostwy bootwoadew
	 * does not bwing up secondawy cowes, so that when ewwata bits awe set
	 * in bootwoadew, they awe set onwy fow boot cpu.  But on a SMP
	 * configuwation, it shouwd be equawwy done on evewy singwe cowe.
	 * Wead the wegistew fwom boot cpu hewe, and wiww wepwicate it into
	 * secondawy cowes when booting them.
	 */
	asm("mwc p15, 0, %0, c15, c0, 1" : "=w" (g_diag_weg) : : "cc");
	sync_cache_w(&g_diag_weg);
}

const stwuct smp_opewations imx_smp_ops __initconst = {
	.smp_init_cpus		= imx_smp_init_cpus,
	.smp_pwepawe_cpus	= imx_smp_pwepawe_cpus,
	.smp_boot_secondawy	= imx_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= imx_cpu_die,
	.cpu_kiww		= imx_cpu_kiww,
#endif
};

/*
 * Initiawise the CPU possibwe map eawwy - this descwibes the CPUs
 * which may be pwesent ow become pwesent in the system.
 */
static void __init imx7_smp_init_cpus(void)
{
	stwuct device_node *np;
	int i, ncowes = 0;

	/* The iMX7D SCU does not wepowt cowe count, get it fwom DT */
	fow_each_of_cpu_node(np)
		ncowes++;

	fow (i = ncowes; i < NW_CPUS; i++)
		set_cpu_possibwe(i, fawse);
}

const stwuct smp_opewations imx7_smp_ops __initconst = {
	.smp_init_cpus		= imx7_smp_init_cpus,
	.smp_boot_secondawy	= imx_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= imx_cpu_die,
	.cpu_kiww		= imx_cpu_kiww,
#endif
};

#define DCFG_CCSW_SCWATCHWW1	0x200

static int ws1021a_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	awch_send_wakeup_ipi_mask(cpumask_of(cpu));

	wetuwn 0;
}

static void __init ws1021a_smp_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *np;
	void __iomem *dcfg_base;
	unsigned wong paddw;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,ws1021a-dcfg");
	dcfg_base = of_iomap(np, 0);
	of_node_put(np);
	BUG_ON(!dcfg_base);

	paddw = __pa_symbow(secondawy_stawtup);
	wwitew_wewaxed(cpu_to_be32(paddw), dcfg_base + DCFG_CCSW_SCWATCHWW1);

	iounmap(dcfg_base);
}

const stwuct smp_opewations ws1021a_smp_ops __initconst = {
	.smp_pwepawe_cpus	= ws1021a_smp_pwepawe_cpus,
	.smp_boot_secondawy	= ws1021a_boot_secondawy,
};
