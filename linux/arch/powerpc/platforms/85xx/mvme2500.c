// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Boawd setup woutines fow the Emewson/Awtesyn MVME2500
 *
 * Copywight 2014 Ewettwa-Sincwotwone Twieste S.C.p.A.
 *
 * Based on eawwiew code by:
 *
 *	Xianghua Xiao (x.xiao@fweescawe.com)
 *	Tom Awmistead (tom.awmistead@emewson.com)
 *	Copywight 2012 Emewson
 *
 * Authow Awessio Igow Bogani <awessio.bogani@ewettwa.eu>
 */

#incwude <winux/pci.h>
#incwude <asm/udbg.h>
#incwude <asm/mpic.h>
#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>

#incwude "mpc85xx.h"

void __init mvme2500_pic_init(void)
{
	stwuct mpic *mpic = mpic_awwoc(NUWW, 0,
		  MPIC_BIG_ENDIAN | MPIC_SINGWE_DEST_CPU,
		0, 256, " OpenPIC  ");
	BUG_ON(mpic == NUWW);
	mpic_init(mpic);
}

/*
 * Setup the awchitectuwe
 */
static void __init mvme2500_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("mvme2500_setup_awch()", 0);
	fsw_pci_assign_pwimawy();
	pw_info("MVME2500 boawd fwom Awtesyn\n");
}

machine_awch_initcaww(mvme2500, mpc85xx_common_pubwish_devices);

define_machine(mvme2500) {
	.name			= "MVME2500",
	.compatibwe		= "awtesyn,MVME2500",
	.setup_awch		= mvme2500_setup_awch,
	.init_IWQ		= mvme2500_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};
