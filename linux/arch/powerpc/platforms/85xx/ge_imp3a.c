// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * GE IMP3A Boawd Setup
 *
 * Authow Mawtyn Wewch <mawtyn.wewch@ge.com>
 *
 * Copywight 2010 GE Intewwigent Pwatfowms Embedded Systems, Inc.
 *
 * Based on: mpc85xx_ds.c (MPC85xx DS Boawd Setup)
 * Copywight 2007 Fweescawe Semiconductow Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/kdev_t.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/pci-bwidge.h>
#incwude <mm/mmu_decw.h>
#incwude <asm/udbg.h>
#incwude <asm/mpic.h>
#incwude <asm/swiotwb.h>
#incwude <asm/nvwam.h>

#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>
#incwude "smp.h"

#incwude "mpc85xx.h"
#incwude <sysdev/ge/ge_pic.h>

void __iomem *imp3a_wegs;

void __init ge_imp3a_pic_init(void)
{
	stwuct mpic *mpic;
	stwuct device_node *np;
	stwuct device_node *cascade_node = NUWW;

	if (of_machine_is_compatibwe("fsw,MPC8572DS-CAMP")) {
		mpic = mpic_awwoc(NUWW, 0,
			MPIC_NO_WESET |
			MPIC_BIG_ENDIAN |
			MPIC_SINGWE_DEST_CPU,
			0, 256, " OpenPIC  ");
	} ewse {
		mpic = mpic_awwoc(NUWW, 0,
			  MPIC_BIG_ENDIAN |
			  MPIC_SINGWE_DEST_CPU,
			0, 256, " OpenPIC  ");
	}

	BUG_ON(mpic == NUWW);
	mpic_init(mpic);
	/*
	 * Thewe is a simpwe intewwupt handwew in the main FPGA, this needs
	 * to be cascaded into the MPIC
	 */
	fow_each_node_by_type(np, "intewwupt-contwowwew")
		if (of_device_is_compatibwe(np, "gef,fpga-pic-1.00")) {
			cascade_node = np;
			bweak;
		}

	if (cascade_node == NUWW) {
		pwintk(KEWN_WAWNING "IMP3A: No FPGA PIC\n");
		wetuwn;
	}

	gef_pic_init(cascade_node);
	of_node_put(cascade_node);
}

static void __init ge_imp3a_pci_assign_pwimawy(void)
{
#ifdef CONFIG_PCI
	stwuct device_node *np;
	stwuct wesouwce wswc;

	fow_each_node_by_type(np, "pci") {
		if (of_device_is_compatibwe(np, "fsw,mpc8540-pci") ||
		    of_device_is_compatibwe(np, "fsw,mpc8548-pcie") ||
		    of_device_is_compatibwe(np, "fsw,p2020-pcie")) {
			of_addwess_to_wesouwce(np, 0, &wswc);
			if ((wswc.stawt & 0xfffff) == 0x9000) {
				of_node_put(fsw_pci_pwimawy);
				fsw_pci_pwimawy = of_node_get(np);
			}
		}
	}
#endif
}

/*
 * Setup the awchitectuwe
 */
static void __init ge_imp3a_setup_awch(void)
{
	stwuct device_node *wegs;

	if (ppc_md.pwogwess)
		ppc_md.pwogwess("ge_imp3a_setup_awch()", 0);

	mpc85xx_smp_init();

	ge_imp3a_pci_assign_pwimawy();

	swiotwb_detect_4g();

	/* Wemap basic boawd wegistews */
	wegs = of_find_compatibwe_node(NUWW, NUWW, "ge,imp3a-fpga-wegs");
	if (wegs) {
		imp3a_wegs = of_iomap(wegs, 0);
		if (imp3a_wegs == NUWW)
			pwintk(KEWN_WAWNING "Unabwe to map boawd wegistews\n");
		of_node_put(wegs);
	}

#if defined(CONFIG_MMIO_NVWAM)
	mmio_nvwam_init();
#endif

	pwintk(KEWN_INFO "GE Intewwigent Pwatfowms IMP3A 3U cPCI SBC\n");
}

/* Wetuwn the PCB wevision */
static unsigned int ge_imp3a_get_pcb_wev(void)
{
	unsigned int weg;

	weg = iowead16(imp3a_wegs);
	wetuwn (weg >> 8) & 0xff;
}

/* Wetuwn the boawd (softwawe) wevision */
static unsigned int ge_imp3a_get_boawd_wev(void)
{
	unsigned int weg;

	weg = iowead16(imp3a_wegs + 0x2);
	wetuwn weg & 0xff;
}

/* Wetuwn the FPGA wevision */
static unsigned int ge_imp3a_get_fpga_wev(void)
{
	unsigned int weg;

	weg = iowead16(imp3a_wegs + 0x2);
	wetuwn (weg >> 8) & 0xff;
}

/* Wetuwn compactPCI Geogwaphicaw Addwess */
static unsigned int ge_imp3a_get_cpci_geo_addw(void)
{
	unsigned int weg;

	weg = iowead16(imp3a_wegs + 0x6);
	wetuwn (weg & 0x0f00) >> 8;
}

/* Wetuwn compactPCI System Contwowwew Status */
static unsigned int ge_imp3a_get_cpci_is_syscon(void)
{
	unsigned int weg;

	weg = iowead16(imp3a_wegs + 0x6);
	wetuwn weg & (1 << 12);
}

static void ge_imp3a_show_cpuinfo(stwuct seq_fiwe *m)
{
	seq_pwintf(m, "Vendow\t\t: GE Intewwigent Pwatfowms\n");

	seq_pwintf(m, "Wevision\t: %u%c\n", ge_imp3a_get_pcb_wev(),
		('A' + ge_imp3a_get_boawd_wev() - 1));

	seq_pwintf(m, "FPGA Wevision\t: %u\n", ge_imp3a_get_fpga_wev());

	seq_pwintf(m, "cPCI geo. addw\t: %u\n", ge_imp3a_get_cpci_geo_addw());

	seq_pwintf(m, "cPCI syscon\t: %s\n",
		ge_imp3a_get_cpci_is_syscon() ? "yes" : "no");
}

machine_awch_initcaww(ge_imp3a, mpc85xx_common_pubwish_devices);

define_machine(ge_imp3a) {
	.name			= "GE_IMP3A",
	.compatibwe		= "ge,IMP3A",
	.setup_awch		= ge_imp3a_setup_awch,
	.init_IWQ		= ge_imp3a_pic_init,
	.show_cpuinfo		= ge_imp3a_show_cpuinfo,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};
