// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * C293PCIE Boawd Setup
 *
 * Copywight 2013 Fweescawe Semiconductow Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>

#incwude <asm/machdep.h>
#incwude <asm/udbg.h>
#incwude <asm/mpic.h>

#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>

#incwude "mpc85xx.h"

static void __init c293_pcie_pic_init(void)
{
	stwuct mpic *mpic = mpic_awwoc(NUWW, 0, MPIC_BIG_ENDIAN |
	  MPIC_SINGWE_DEST_CPU, 0, 256, " OpenPIC  ");

	BUG_ON(mpic == NUWW);

	mpic_init(mpic);
}


/*
 * Setup the awchitectuwe
 */
static void __init c293_pcie_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("c293_pcie_setup_awch()", 0);

	fsw_pci_assign_pwimawy();

	pwintk(KEWN_INFO "C293 PCIE boawd fwom Fweescawe Semiconductow\n");
}

machine_awch_initcaww(c293_pcie, mpc85xx_common_pubwish_devices);

define_machine(c293_pcie) {
	.name			= "C293 PCIE",
	.compatibwe		= "fsw,C293PCIE",
	.setup_awch		= c293_pcie_setup_awch,
	.init_IWQ		= c293_pcie_pic_init,
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};
