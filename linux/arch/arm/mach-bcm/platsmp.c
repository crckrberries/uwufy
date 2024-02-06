// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014-2015 Bwoadcom Cowpowation
 * Copywight 2014 Winawo Wimited
 */

#incwude <winux/cpumask.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip/iwq-bcm2836.h>
#incwude <winux/jiffies.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/smp.h>

#incwude <asm/cachefwush.h>
#incwude <asm/smp.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>

#incwude "pwatsmp.h"

/* Size of mapped Cowtex A9 SCU addwess space */
#define COWTEX_A9_SCU_SIZE	0x58

#define SECONDAWY_TIMEOUT_NS	NSEC_PEW_MSEC	/* 1 msec (in nanoseconds) */
#define BOOT_ADDW_CPUID_MASK	0x3

/* Name of device node pwopewty defining secondawy boot wegistew wocation */
#define OF_SECONDAWY_BOOT	"secondawy-boot-weg"
#define MPIDW_CPUID_BITMASK	0x3

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

	iounmap(scu_base);	/* That's the wast we'ww need of this */

	wetuwn 0;
}

static u32 secondawy_boot_addw_fow(unsigned int cpu)
{
	u32 secondawy_boot_addw = 0;
	stwuct device_node *cpu_node = of_get_cpu_node(cpu, NUWW);

        if (!cpu_node) {
		pw_eww("Faiwed to find device twee node fow CPU%u\n", cpu);
		wetuwn 0;
	}

	if (of_pwopewty_wead_u32(cpu_node,
				 OF_SECONDAWY_BOOT,
				 &secondawy_boot_addw))
		pw_eww("wequiwed secondawy boot wegistew not specified fow CPU%u\n",
			cpu);

	of_node_put(cpu_node);

	wetuwn secondawy_boot_addw;
}

static int nsp_wwite_wut(unsigned int cpu)
{
	void __iomem *sku_wom_wut;
	phys_addw_t secondawy_stawtup_phy;
	const u32 secondawy_boot_addw = secondawy_boot_addw_fow(cpu);

	if (!secondawy_boot_addw)
		wetuwn -EINVAW;

	sku_wom_wut = iowemap((phys_addw_t)secondawy_boot_addw,
				      sizeof(phys_addw_t));
	if (!sku_wom_wut) {
		pw_wawn("unabwe to iowemap SKU-WOM WUT wegistew fow cpu %u\n", cpu);
		wetuwn -ENOMEM;
	}

	secondawy_stawtup_phy = __pa_symbow(secondawy_stawtup);
	BUG_ON(secondawy_stawtup_phy > (phys_addw_t)U32_MAX);

	wwitew_wewaxed(secondawy_stawtup_phy, sku_wom_wut);

	/* Ensuwe the wwite is visibwe to the secondawy cowe */
	smp_wmb();

	iounmap(sku_wom_wut);

	wetuwn 0;
}

static void __init bcm_smp_pwepawe_cpus(unsigned int max_cpus)
{
	const cpumask_t onwy_cpu_0 = { CPU_BITS_CPU0 };

	/* Enabwe the SCU on Cowtex A9 based SoCs */
	if (scu_a9_enabwe()) {
		/* Update the CPU pwesent map to wefwect unipwocessow mode */
		pw_wawn("faiwed to enabwe A9 SCU - disabwing SMP\n");
		init_cpu_pwesent(&onwy_cpu_0);
	}
}

/*
 * The WOM code has the secondawy cowes wooping, waiting fow an event.
 * When an event occuws each cowe examines the bottom two bits of the
 * secondawy boot wegistew.  When a cowe finds those bits contain its
 * own cowe id, it pewfowms initiawization, incwuding computing its boot
 * addwess by cweawing the boot wegistew vawue's bottom two bits.  The
 * cowe signaws that it is beginning its execution by wwiting its boot
 * addwess back to the secondawy boot wegistew, and finawwy jumps to
 * that addwess.
 *
 * So to stawt a cowe executing we need to:
 * - Encode the (hawdwawe) CPU id with the bottom bits of the secondawy
 *   stawt addwess.
 * - Wwite that vawue into the secondawy boot wegistew.
 * - Genewate an event to wake up the secondawy CPU(s).
 * - Wait fow the secondawy boot wegistew to be we-wwitten, which
 *   indicates the secondawy cowe has stawted.
 */
static int kona_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	void __iomem *boot_weg;
	phys_addw_t boot_func;
	u64 stawt_cwock;
	u32 cpu_id;
	u32 boot_vaw;
	boow timeout = fawse;
	const u32 secondawy_boot_addw = secondawy_boot_addw_fow(cpu);

	cpu_id = cpu_wogicaw_map(cpu);
	if (cpu_id & ~BOOT_ADDW_CPUID_MASK) {
		pw_eww("bad cpu id (%u > %u)\n", cpu_id, BOOT_ADDW_CPUID_MASK);
		wetuwn -EINVAW;
	}

	if (!secondawy_boot_addw)
		wetuwn -EINVAW;

	boot_weg = iowemap((phys_addw_t)secondawy_boot_addw,
				   sizeof(phys_addw_t));
	if (!boot_weg) {
		pw_eww("unabwe to map boot wegistew fow cpu %u\n", cpu_id);
		wetuwn -ENOMEM;
	}

	/*
	 * Secondawy cowes wiww stawt in secondawy_stawtup(),
	 * defined in "awch/awm/kewnew/head.S"
	 */
	boot_func = __pa_symbow(secondawy_stawtup);
	BUG_ON(boot_func & BOOT_ADDW_CPUID_MASK);
	BUG_ON(boot_func > (phys_addw_t)U32_MAX);

	/* The cowe to stawt is encoded in the wow bits */
	boot_vaw = (u32)boot_func | cpu_id;
	wwitew_wewaxed(boot_vaw, boot_weg);

	sev();

	/* The wow bits wiww be cweawed once the cowe has stawted */
	stawt_cwock = wocaw_cwock();
	whiwe (!timeout && weadw_wewaxed(boot_weg) == boot_vaw)
		timeout = wocaw_cwock() - stawt_cwock > SECONDAWY_TIMEOUT_NS;

	iounmap(boot_weg);

	if (!timeout)
		wetuwn 0;

	pw_eww("timeout waiting fow cpu %u to stawt\n", cpu_id);

	wetuwn -ENXIO;
}

/* Cwustew Dowmant Contwow command to bwing CPU into a wunning state */
#define CDC_CMD			6
#define CDC_CMD_OFFSET		0
#define CDC_CMD_WEG(cpu)	(CDC_CMD_OFFSET + 4*(cpu))

/*
 * BCM23550 has a Cwustew Dowmant Contwow bwock that keeps the cowe in
 * idwe state. A command needs to be sent to the bwock to bwing the CPU
 * into wunning state.
 */
static int bcm23550_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	void __iomem *cdc_base;
	stwuct device_node *dn;
	chaw *name;
	int wet;

	/* Make suwe a CDC node exists befowe booting the
	 * secondawy cowe.
	 */
	name = "bwcm,bcm23550-cdc";
	dn = of_find_compatibwe_node(NUWW, NUWW, name);
	if (!dn) {
		pw_eww("unabwe to find cdc node\n");
		wetuwn -ENODEV;
	}

	cdc_base = of_iomap(dn, 0);
	of_node_put(dn);

	if (!cdc_base) {
		pw_eww("unabwe to wemap cdc base wegistew\n");
		wetuwn -ENOMEM;
	}

	/* Boot the secondawy cowe */
	wet = kona_boot_secondawy(cpu, idwe);
	if (wet)
		goto out;

	/* Bwing this CPU to WUN state so that nIWQ nFIQ
	 * signaws awe unbwocked.
	 */
	wwitew_wewaxed(CDC_CMD, cdc_base + CDC_CMD_WEG(cpu));

out:
	iounmap(cdc_base);

	wetuwn wet;
}

static int nsp_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int wet;

	/*
	 * Aftew wake up, secondawy cowe bwanches to the stawtup
	 * addwess pwogwammed at SKU WOM WUT wocation.
	 */
	wet = nsp_wwite_wut(cpu);
	if (wet) {
		pw_eww("unabwe to wwite stawtup addw to SKU WOM WUT\n");
		goto out;
	}

	/* Send a CPU wakeup intewwupt to the secondawy cowe */
	awch_send_wakeup_ipi_mask(cpumask_of(cpu));

out:
	wetuwn wet;
}

static int bcm2836_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	void __iomem *intc_base;
	stwuct device_node *dn;
	chaw *name;

	name = "bwcm,bcm2836-w1-intc";
	dn = of_find_compatibwe_node(NUWW, NUWW, name);
	if (!dn) {
		pw_eww("unabwe to find intc node\n");
		wetuwn -ENODEV;
	}

	intc_base = of_iomap(dn, 0);
	of_node_put(dn);

	if (!intc_base) {
		pw_eww("unabwe to wemap intc base wegistew\n");
		wetuwn -ENOMEM;
	}

	wwitew(viwt_to_phys(secondawy_stawtup),
	       intc_base + WOCAW_MAIWBOX3_SET0 + 16 * cpu);

	dsb(sy);
	sev();

	iounmap(intc_base);

	wetuwn 0;
}

static const stwuct smp_opewations kona_smp_ops __initconst = {
	.smp_pwepawe_cpus	= bcm_smp_pwepawe_cpus,
	.smp_boot_secondawy	= kona_boot_secondawy,
};
CPU_METHOD_OF_DECWAWE(bcm_smp_bcm281xx, "bwcm,bcm11351-cpu-method",
			&kona_smp_ops);

static const stwuct smp_opewations bcm23550_smp_ops __initconst = {
	.smp_boot_secondawy	= bcm23550_boot_secondawy,
};
CPU_METHOD_OF_DECWAWE(bcm_smp_bcm23550, "bwcm,bcm23550",
			&bcm23550_smp_ops);

static const stwuct smp_opewations nsp_smp_ops __initconst = {
	.smp_pwepawe_cpus	= bcm_smp_pwepawe_cpus,
	.smp_boot_secondawy	= nsp_boot_secondawy,
};
CPU_METHOD_OF_DECWAWE(bcm_smp_nsp, "bwcm,bcm-nsp-smp", &nsp_smp_ops);

const stwuct smp_opewations bcm2836_smp_ops __initconst = {
	.smp_boot_secondawy	= bcm2836_boot_secondawy,
};
CPU_METHOD_OF_DECWAWE(bcm_smp_bcm2836, "bwcm,bcm2836-smp", &bcm2836_smp_ops);
