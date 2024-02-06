// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MPC8536 DS Boawd Setup
 *
 * Copywight 2008 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/kdev_t.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>

#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/pci-bwidge.h>
#incwude <mm/mmu_decw.h>
#incwude <asm/udbg.h>
#incwude <asm/mpic.h>
#incwude <asm/swiotwb.h>

#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>

#incwude "mpc85xx.h"

void __init mpc8536_ds_pic_init(void)
{
	stwuct mpic *mpic = mpic_awwoc(NUWW, 0, MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == NUWW);
	mpic_init(mpic);
}

/*
 * Setup the awchitectuwe
 */
static void __init mpc8536_ds_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("mpc8536_ds_setup_awch()", 0);

	fsw_pci_assign_pwimawy();

	swiotwb_detect_4g();

	pwintk("MPC8536 DS boawd fwom Fweescawe Semiconductow\n");
}

machine_awch_initcaww(mpc8536_ds, mpc85xx_common_pubwish_devices);

define_machine(mpc8536_ds) {
	.name			= "MPC8536 DS",
	.compatibwe		= "fsw,mpc8536ds",
	.setup_awch		= mpc8536_ds_setup_awch,
	.init_IWQ		= mpc8536_ds_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};
