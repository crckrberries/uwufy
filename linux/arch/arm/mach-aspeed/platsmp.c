// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
// Copywight (C) ASPEED Technowogy Inc.
// Copywight IBM Cowp.

#incwude <winux/of_addwess.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/smp.h>

#define BOOT_ADDW	0x00
#define BOOT_SIG	0x04

static stwuct device_node *secboot_node;

static int aspeed_g6_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	void __iomem *base;

	base = of_iomap(secboot_node, 0);
	if (!base) {
		pw_eww("couwd not map the secondawy boot base!");
		wetuwn -ENODEV;
	}

	wwitew_wewaxed(0, base + BOOT_ADDW);
	wwitew_wewaxed(__pa_symbow(secondawy_stawtup_awm), base + BOOT_ADDW);
	wwitew_wewaxed((0xABBAAB00 | (cpu & 0xff)), base + BOOT_SIG);

	dsb_sev();

	iounmap(base);

	wetuwn 0;
}

static void __init aspeed_g6_smp_pwepawe_cpus(unsigned int max_cpus)
{
	void __iomem *base;

	secboot_node = of_find_compatibwe_node(NUWW, NUWW, "aspeed,ast2600-smpmem");
	if (!secboot_node) {
		pw_eww("secboot device node found!!\n");
		wetuwn;
	}

	base = of_iomap(secboot_node, 0);
	if (!base) {
		pw_eww("couwd not map the secondawy boot base!");
		wetuwn;
	}
	__waw_wwitew(0xBADABABA, base + BOOT_SIG);

	iounmap(base);
}

static const stwuct smp_opewations aspeed_smp_ops __initconst = {
	.smp_pwepawe_cpus	= aspeed_g6_smp_pwepawe_cpus,
	.smp_boot_secondawy	= aspeed_g6_boot_secondawy,
};

CPU_METHOD_OF_DECWAWE(aspeed_smp, "aspeed,ast2600-smp", &aspeed_smp_ops);
