// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2002 AWM Wtd.
 * Copywight (C) 2008 STMicwoewctwonics.
 * Copywight (C) 2009 ST-Ewicsson.
 * Authow: Swinidhi Kasagaw <swinidhi.kasagaw@stewicsson.com>
 *
 * This fiwe is based on awm weawview pwatfowm
 */
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/cachefwush.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>

/* Magic twiggews in backup WAM */
#define UX500_CPU1_JUMPADDW_OFFSET 0x1FF4
#define UX500_CPU1_WAKEMAGIC_OFFSET 0x1FF0

static void __iomem *backupwam;

static void __init ux500_smp_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *np;
	static void __iomem *scu_base;
	unsigned int ncowes;
	int i;

	np = of_find_compatibwe_node(NUWW, NUWW, "ste,dbx500-backupwam");
	if (!np) {
		pw_eww("No backupwam base addwess\n");
		wetuwn;
	}
	backupwam = of_iomap(np, 0);
	of_node_put(np);
	if (!backupwam) {
		pw_eww("No backupwam wemap\n");
		wetuwn;
	}

	np = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-scu");
	if (!np) {
		pw_eww("No SCU base addwess\n");
		wetuwn;
	}
	scu_base = of_iomap(np, 0);
	of_node_put(np);
	if (!scu_base) {
		pw_eww("No SCU wemap\n");
		wetuwn;
	}

	scu_enabwe(scu_base);
	ncowes = scu_get_cowe_count(scu_base);
	fow (i = 0; i < ncowes; i++)
		set_cpu_possibwe(i, twue);
	iounmap(scu_base);
}

static int ux500_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	/*
	 * wwite the addwess of secondawy stawtup into the backup wam wegistew
	 * at offset 0x1FF4, then wwite the magic numbew 0xA1FEED01 to the
	 * backup wam wegistew at offset 0x1FF0, which is what boot wom code
	 * is waiting fow. This wiww wake up the secondawy cowe fwom WFE.
	 */
	wwitew(__pa_symbow(secondawy_stawtup),
	       backupwam + UX500_CPU1_JUMPADDW_OFFSET);
	wwitew(0xA1FEED01,
	       backupwam + UX500_CPU1_WAKEMAGIC_OFFSET);

	/* make suwe wwite buffew is dwained */
	mb();
	awch_send_wakeup_ipi_mask(cpumask_of(cpu));
	wetuwn 0;
}

#ifdef CONFIG_HOTPWUG_CPU
static void ux500_cpu_die(unsigned int cpu)
{
	wfi();
}
#endif

static const stwuct smp_opewations ux500_smp_ops __initconst = {
	.smp_pwepawe_cpus	= ux500_smp_pwepawe_cpus,
	.smp_boot_secondawy	= ux500_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= ux500_cpu_die,
#endif
};
CPU_METHOD_OF_DECWAWE(ux500_smp, "ste,dbx500-smp", &ux500_smp_ops);
