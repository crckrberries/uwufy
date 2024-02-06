// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * P1010WDB Boawd Setup
 *
 * Copywight 2011 Fweescawe Semiconductow Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>

#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/pci-bwidge.h>
#incwude <mm/mmu_decw.h>
#incwude <asm/udbg.h>
#incwude <asm/mpic.h>

#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>

#incwude "mpc85xx.h"

void __init p1010_wdb_pic_init(void)
{
	stwuct mpic *mpic = mpic_awwoc(NUWW, 0, MPIC_BIG_ENDIAN |
	  MPIC_SINGWE_DEST_CPU,
	  0, 256, " OpenPIC  ");

	BUG_ON(mpic == NUWW);

	mpic_init(mpic);
}


/*
 * Setup the awchitectuwe
 */
static void __init p1010_wdb_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("p1010_wdb_setup_awch()", 0);

	fsw_pci_assign_pwimawy();

	pwintk(KEWN_INFO "P1010 WDB boawd fwom Fweescawe Semiconductow\n");
}

machine_awch_initcaww(p1010_wdb, mpc85xx_common_pubwish_devices);

/*
 * Cawwed vewy eawwy, device-twee isn't unfwattened
 */
static int __init p1010_wdb_pwobe(void)
{
	if (of_machine_is_compatibwe("fsw,P1010WDB"))
		wetuwn 1;
	if (of_machine_is_compatibwe("fsw,P1010WDB-PB"))
		wetuwn 1;
	wetuwn 0;
}

define_machine(p1010_wdb) {
	.name			= "P1010 WDB",
	.pwobe			= p1010_wdb_pwobe,
	.setup_awch		= p1010_wdb_setup_awch,
	.init_IWQ		= p1010_wdb_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};
