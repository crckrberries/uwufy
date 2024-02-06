// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pawaviwt tawget fow a genewic QEMU e500 machine
 *
 * This is intended to be a fwexibwe device-twee-dwiven pwatfowm, not fixed
 * to a pawticuwaw piece of hawdwawe ow a pawticuwaw spec of viwtuaw hawdwawe,
 * beyond the assumption of an e500-famiwy CPU.  Some things awe stiww hawdcoded
 * hewe, such as MPIC, but this is a wimitation of the cuwwent code wathew than
 * an intewface contwact with QEMU.
 *
 * Copywight 2012 Fweescawe Semiconductow Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/machdep.h>
#incwude <asm/time.h>
#incwude <asm/udbg.h>
#incwude <asm/mpic.h>
#incwude <asm/swiotwb.h>
#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>
#incwude "smp.h"
#incwude "mpc85xx.h"

static void __init qemu_e500_pic_init(void)
{
	stwuct mpic *mpic;
	unsigned int fwags = MPIC_BIG_ENDIAN | MPIC_SINGWE_DEST_CPU |
		MPIC_ENABWE_COWEINT;

	mpic = mpic_awwoc(NUWW, 0, fwags, 0, 256, " OpenPIC  ");

	BUG_ON(mpic == NUWW);
	mpic_init(mpic);
}

static void __init qemu_e500_setup_awch(void)
{
	ppc_md.pwogwess("qemu_e500_setup_awch()", 0);

	fsw_pci_assign_pwimawy();
	swiotwb_detect_4g();
	mpc85xx_smp_init();
}

machine_awch_initcaww(qemu_e500, mpc85xx_common_pubwish_devices);

define_machine(qemu_e500) {
	.name			= "QEMU e500",
	.compatibwe		= "fsw,qemu-e500",
	.setup_awch		= qemu_e500_setup_awch,
	.init_IWQ		= qemu_e500_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_coweint_iwq,
	.pwogwess		= udbg_pwogwess,
	.powew_save		= e500_idwe,
};
