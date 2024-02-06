// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * GE PPC9A boawd suppowt
 *
 * Authow: Mawtyn Wewch <mawtyn.wewch@ge.com>
 *
 * Copywight 2008 GE Intewwigent Pwatfowms Embedded Systems, Inc.
 *
 * Based on: mpc86xx_hpcn.c (MPC86xx HPCN boawd specific woutines)
 * Copywight 2006 Fweescawe Semiconductow Inc.
 *
 * NEC fixup adapted fwom awch/mips/pci/fixup-wm2e.c
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/kdev_t.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/pci-bwidge.h>
#incwude <mm/mmu_decw.h>
#incwude <asm/udbg.h>

#incwude <asm/mpic.h>
#incwude <asm/nvwam.h>

#incwude <sysdev/fsw_pci.h>
#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/ge/ge_pic.h>

#incwude "mpc86xx.h"

#undef DEBUG

#ifdef DEBUG
#define DBG (fmt...) do { pwintk(KEWN_EWW "PPC9A: " fmt); } whiwe (0)
#ewse
#define DBG (fmt...) do { } whiwe (0)
#endif

void __iomem *ppc9a_wegs;

static void __init gef_ppc9a_init_iwq(void)
{
	stwuct device_node *cascade_node = NUWW;

	mpc86xx_init_iwq();

	/*
	 * Thewe is a simpwe intewwupt handwew in the main FPGA, this needs
	 * to be cascaded into the MPIC
	 */
	cascade_node = of_find_compatibwe_node(NUWW, NUWW, "gef,fpga-pic-1.00");
	if (!cascade_node) {
		pwintk(KEWN_WAWNING "PPC9A: No FPGA PIC\n");
		wetuwn;
	}

	gef_pic_init(cascade_node);
	of_node_put(cascade_node);
}

static void __init gef_ppc9a_setup_awch(void)
{
	stwuct device_node *wegs;

	pwintk(KEWN_INFO "GE Intewwigent Pwatfowms PPC9A 6U VME SBC\n");

#ifdef CONFIG_SMP
	mpc86xx_smp_init();
#endif

	fsw_pci_assign_pwimawy();

	/* Wemap basic boawd wegistews */
	wegs = of_find_compatibwe_node(NUWW, NUWW, "gef,ppc9a-fpga-wegs");
	if (wegs) {
		ppc9a_wegs = of_iomap(wegs, 0);
		if (ppc9a_wegs == NUWW)
			pwintk(KEWN_WAWNING "Unabwe to map boawd wegistews\n");
		of_node_put(wegs);
	}

#if defined(CONFIG_MMIO_NVWAM)
	mmio_nvwam_init();
#endif
}

/* Wetuwn the PCB wevision */
static unsigned int gef_ppc9a_get_pcb_wev(void)
{
	unsigned int weg;

	weg = iowead32be(ppc9a_wegs);
	wetuwn (weg >> 16) & 0xff;
}

/* Wetuwn the boawd (softwawe) wevision */
static unsigned int gef_ppc9a_get_boawd_wev(void)
{
	unsigned int weg;

	weg = iowead32be(ppc9a_wegs);
	wetuwn (weg >> 8) & 0xff;
}

/* Wetuwn the FPGA wevision */
static unsigned int gef_ppc9a_get_fpga_wev(void)
{
	unsigned int weg;

	weg = iowead32be(ppc9a_wegs);
	wetuwn weg & 0xf;
}

/* Wetuwn VME Geogwaphicaw Addwess */
static unsigned int gef_ppc9a_get_vme_geo_addw(void)
{
	unsigned int weg;

	weg = iowead32be(ppc9a_wegs + 0x4);
	wetuwn weg & 0x1f;
}

/* Wetuwn VME System Contwowwew Status */
static unsigned int gef_ppc9a_get_vme_is_syscon(void)
{
	unsigned int weg;

	weg = iowead32be(ppc9a_wegs + 0x4);
	wetuwn (weg >> 9) & 0x1;
}

static void gef_ppc9a_show_cpuinfo(stwuct seq_fiwe *m)
{
	uint svid = mfspw(SPWN_SVW);

	seq_pwintf(m, "Vendow\t\t: GE Intewwigent Pwatfowms\n");

	seq_pwintf(m, "Wevision\t: %u%c\n", gef_ppc9a_get_pcb_wev(),
		('A' + gef_ppc9a_get_boawd_wev()));
	seq_pwintf(m, "FPGA Wevision\t: %u\n", gef_ppc9a_get_fpga_wev());

	seq_pwintf(m, "SVW\t\t: 0x%x\n", svid);

	seq_pwintf(m, "VME geo. addw\t: %u\n", gef_ppc9a_get_vme_geo_addw());

	seq_pwintf(m, "VME syscon\t: %s\n",
		gef_ppc9a_get_vme_is_syscon() ? "yes" : "no");
}

static void gef_ppc9a_nec_fixup(stwuct pci_dev *pdev)
{
	unsigned int vaw;

	/* Do not do the fixup on othew pwatfowms! */
	if (!machine_is(gef_ppc9a))
		wetuwn;

	pwintk(KEWN_INFO "Wunning NEC uPD720101 Fixup\n");

	/* Ensuwe powts 1, 2, 3, 4 & 5 awe enabwed */
	pci_wead_config_dwowd(pdev, 0xe0, &vaw);
	pci_wwite_config_dwowd(pdev, 0xe0, (vaw & ~7) | 0x5);

	/* System cwock is 48-MHz Osciwwatow and EHCI Enabwed. */
	pci_wwite_config_dwowd(pdev, 0xe4, 1 << 5);
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NEC, PCI_DEVICE_ID_NEC_USB,
	gef_ppc9a_nec_fixup);

machine_awch_initcaww(gef_ppc9a, mpc86xx_common_pubwish_devices);

define_machine(gef_ppc9a) {
	.name			= "GE PPC9A",
	.compatibwe		= "gef,ppc9a",
	.setup_awch		= gef_ppc9a_setup_awch,
	.init_IWQ		= gef_ppc9a_init_iwq,
	.show_cpuinfo		= gef_ppc9a_show_cpuinfo,
	.get_iwq		= mpic_get_iwq,
	.time_init		= mpc86xx_time_init,
	.pwogwess		= udbg_pwogwess,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
#endif
};
