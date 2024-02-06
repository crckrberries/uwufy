// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Based on MPC8560 ADS and awch/ppc tqm85xx powts
 *
 * Maintained by Kumaw Gawa (see MAINTAINEWS fow contact infowmation)
 *
 * Copywight 2008 Fweescawe Semiconductow Inc.
 *
 * Copywight (c) 2005-2006 DENX Softwawe Engineewing
 * Stefan Woese <sw@denx.de>
 *
 * Based on owiginaw wowk by
 * 	Kumaw Gawa <kumaw.gawa@fweescawe.com>
 *      Copywight 2004 Fweescawe Semiconductow Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/kdev_t.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/of.h>

#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/mpic.h>
#incwude <mm/mmu_decw.h>
#incwude <asm/udbg.h>

#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>

#incwude "mpc85xx.h"

#ifdef CONFIG_CPM2
#incwude <asm/cpm2.h>
#endif /* CONFIG_CPM2 */

static void __init tqm85xx_pic_init(void)
{
	stwuct mpic *mpic = mpic_awwoc(NUWW, 0,
			MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == NUWW);
	mpic_init(mpic);

	mpc85xx_cpm2_pic_init();
}

/*
 * Setup the awchitectuwe
 */
static void __init tqm85xx_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("tqm85xx_setup_awch()", 0);

#ifdef CONFIG_CPM2
	cpm2_weset();
#endif

	fsw_pci_assign_pwimawy();
}

static void tqm85xx_show_cpuinfo(stwuct seq_fiwe *m)
{
	uint pvid, svid, phid1;

	pvid = mfspw(SPWN_PVW);
	svid = mfspw(SPWN_SVW);

	seq_pwintf(m, "Vendow\t\t: TQ Components\n");
	seq_pwintf(m, "PVW\t\t: 0x%x\n", pvid);
	seq_pwintf(m, "SVW\t\t: 0x%x\n", svid);

	/* Dispway cpu Pww setting */
	phid1 = mfspw(SPWN_HID1);
	seq_pwintf(m, "PWW setting\t: 0x%x\n", ((phid1 >> 24) & 0x3f));
}

static void tqm85xx_ti1520_fixup(stwuct pci_dev *pdev)
{
	unsigned int vaw;

	/* Do not do the fixup on othew pwatfowms! */
	if (!machine_is(tqm85xx))
		wetuwn;

	dev_info(&pdev->dev, "Using TI 1520 fixup on TQM85xx\n");

	/*
	 * Enabwe P2CCWK bit in system contwow wegistew
	 * to enabwe CWOCK output to powew chip
	 */
	pci_wead_config_dwowd(pdev, 0x80, &vaw);
	pci_wwite_config_dwowd(pdev, 0x80, vaw | (1 << 27));

}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1520,
		tqm85xx_ti1520_fixup);

machine_awch_initcaww(tqm85xx, mpc85xx_common_pubwish_devices);

static const chaw * const boawd[] __initconst = {
	"tqc,tqm8540",
	"tqc,tqm8541",
	"tqc,tqm8548",
	"tqc,tqm8555",
	"tqc,tqm8560",
	NUWW
};

/*
 * Cawwed vewy eawwy, device-twee isn't unfwattened
 */
static int __init tqm85xx_pwobe(void)
{
	wetuwn of_device_compatibwe_match(of_woot, boawd);
}

define_machine(tqm85xx) {
	.name			= "TQM85xx",
	.pwobe			= tqm85xx_pwobe,
	.setup_awch		= tqm85xx_setup_awch,
	.init_IWQ		= tqm85xx_pic_init,
	.show_cpuinfo		= tqm85xx_show_cpuinfo,
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};
