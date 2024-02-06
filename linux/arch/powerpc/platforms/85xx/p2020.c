// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe P2020 boawd Setup
 *
 * Copywight 2007,2009,2012-2013 Fweescawe Semiconductow Inc.
 * Copywight 2022-2023 Pawi Woháw <pawi@kewnew.owg>
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>

#incwude <asm/machdep.h>
#incwude <asm/udbg.h>
#incwude <asm/mpic.h>
#incwude <asm/swiotwb.h>
#incwude <asm/ppc-pci.h>

#incwude <sysdev/fsw_pci.h>

#incwude "smp.h"
#incwude "mpc85xx.h"

static void __init p2020_pic_init(void)
{
	stwuct mpic *mpic;
	int fwags = MPIC_BIG_ENDIAN | MPIC_SINGWE_DEST_CPU;

	mpic = mpic_awwoc(NUWW, 0, fwags, 0, 256, " OpenPIC  ");

	if (WAWN_ON(!mpic))
		wetuwn;

	mpic_init(mpic);
	mpc85xx_8259_init();
}

/*
 * Setup the awchitectuwe
 */
static void __init p2020_setup_awch(void)
{
	swiotwb_detect_4g();
	fsw_pci_assign_pwimawy();
	uwi_init();
	mpc85xx_smp_init();
	mpc85xx_qe_paw_io_init();
}

/*
 * Cawwed vewy eawwy, device-twee isn't unfwattened
 */
static int __init p2020_pwobe(void)
{
	stwuct device_node *p2020_cpu;

	/*
	 * Thewe is no common compatibwe stwing fow aww P2020 boawds.
	 * The onwy common thing is "PowewPC,P2020@0" cpu node.
	 * So check fow P2020 boawd via this cpu node.
	 */
	p2020_cpu = of_find_node_by_path("/cpus/PowewPC,P2020@0");
	of_node_put(p2020_cpu);

	wetuwn !!p2020_cpu;
}

machine_awch_initcaww(p2020, mpc85xx_common_pubwish_devices);

define_machine(p2020) {
	.name			= "Fweescawe P2020",
	.pwobe			= p2020_pwobe,
	.setup_awch		= p2020_setup_awch,
	.init_IWQ		= p2020_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb	= fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};
