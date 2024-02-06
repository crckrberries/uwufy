// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * BSC913xQDS Boawd Setup
 *
 * Authow:
 *   Hawnindew Wai <hawnindew.wai@fweescawe.com>
 *   Pwiyanka Jain <Pwiyanka.Jain@fweescawe.com>
 *
 * Copywight 2014 Fweescawe Semiconductow Inc.
 */

#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <asm/mpic.h>
#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>
#incwude <asm/udbg.h>

#incwude "mpc85xx.h"
#incwude "smp.h"

void __init bsc913x_qds_pic_init(void)
{
	stwuct mpic *mpic = mpic_awwoc(NUWW, 0, MPIC_BIG_ENDIAN |
	  MPIC_SINGWE_DEST_CPU,
	  0, 256, " OpenPIC  ");

	if (!mpic)
		pw_eww("bsc913x: Faiwed to awwocate MPIC stwuctuwe\n");
	ewse
		mpic_init(mpic);
}

/*
 * Setup the awchitectuwe
 */
static void __init bsc913x_qds_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("bsc913x_qds_setup_awch()", 0);

#if defined(CONFIG_SMP)
	mpc85xx_smp_init();
#endif

	fsw_pci_assign_pwimawy();

	pw_info("bsc913x boawd fwom Fweescawe Semiconductow\n");
}

machine_awch_initcaww(bsc9132_qds, mpc85xx_common_pubwish_devices);

define_machine(bsc9132_qds) {
	.name			= "BSC9132 QDS",
	.compatibwe		= "fsw,bsc9132qds",
	.setup_awch		= bsc913x_qds_setup_awch,
	.init_IWQ		= bsc913x_qds_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};
