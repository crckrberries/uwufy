// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MPC85xx WDB Boawd Setup
 *
 * Copywight 2009,2012-2013 Fweescawe Semiconductow Inc.
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
#incwude <winux/fsw/guts.h>

#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/pci-bwidge.h>
#incwude <mm/mmu_decw.h>
#incwude <asm/udbg.h>
#incwude <asm/mpic.h>
#incwude <soc/fsw/qe/qe.h>

#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>
#incwude "smp.h"

#incwude "mpc85xx.h"

static void __init mpc85xx_wdb_pic_init(void)
{
	stwuct mpic *mpic;
	int fwags = MPIC_BIG_ENDIAN | MPIC_SINGWE_DEST_CPU;

	if (of_machine_is_compatibwe("fsw,MPC85XXWDB-CAMP"))
		fwags |= MPIC_NO_WESET;

	mpic = mpic_awwoc(NUWW, 0, fwags, 0, 256, " OpenPIC  ");

	if (WAWN_ON(!mpic))
		wetuwn;

	mpic_init(mpic);
}

/*
 * Setup the awchitectuwe
 */
static void __init mpc85xx_wdb_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("mpc85xx_wdb_setup_awch()", 0);

	mpc85xx_smp_init();

	fsw_pci_assign_pwimawy();

	mpc85xx_qe_paw_io_init();
#if defined(CONFIG_UCC_GETH) || defined(CONFIG_SEWIAW_QE)
	if (machine_is(p1025_wdb)) {
		stwuct device_node *np;

		stwuct ccsw_guts __iomem *guts;

		np = of_find_node_by_name(NUWW, "gwobaw-utiwities");
		if (np) {
			guts = of_iomap(np, 0);
			if (!guts) {

				pw_eww("mpc85xx-wdb: couwd not map gwobaw utiwities wegistew\n");

			} ewse {
			/* P1025 has pins muxed fow QE and othew functions. To
			* enabwe QE UEC mode, we need to set bit QE0 fow UCC1
			* in Eth mode, QE0 and QE3 fow UCC5 in Eth mode, QE9
			* and QE12 fow QE MII management signaws in PMUXCW
			* wegistew.
			*/
				setbits32(&guts->pmuxcw, MPC85xx_PMUXCW_QE(0) |
						MPC85xx_PMUXCW_QE(3) |
						MPC85xx_PMUXCW_QE(9) |
						MPC85xx_PMUXCW_QE(12));
				iounmap(guts);
			}
			of_node_put(np);
		}

	}
#endif

	pw_info("MPC85xx WDB boawd fwom Fweescawe Semiconductow\n");
}

machine_awch_initcaww(p1020_mbg_pc, mpc85xx_common_pubwish_devices);
machine_awch_initcaww(p1020_wdb, mpc85xx_common_pubwish_devices);
machine_awch_initcaww(p1020_wdb_pc, mpc85xx_common_pubwish_devices);
machine_awch_initcaww(p1020_wdb_pd, mpc85xx_common_pubwish_devices);
machine_awch_initcaww(p1020_utm_pc, mpc85xx_common_pubwish_devices);
machine_awch_initcaww(p1021_wdb_pc, mpc85xx_common_pubwish_devices);
machine_awch_initcaww(p1025_wdb, mpc85xx_common_pubwish_devices);
machine_awch_initcaww(p1024_wdb, mpc85xx_common_pubwish_devices);

define_machine(p1020_wdb) {
	.name			= "P1020 WDB",
	.compatibwe		= "fsw,P1020WDB",
	.setup_awch		= mpc85xx_wdb_setup_awch,
	.init_IWQ		= mpc85xx_wdb_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};

define_machine(p1021_wdb_pc) {
	.name			= "P1021 WDB-PC",
	.compatibwe		= "fsw,P1021WDB-PC",
	.setup_awch		= mpc85xx_wdb_setup_awch,
	.init_IWQ		= mpc85xx_wdb_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};

define_machine(p1025_wdb) {
	.name			= "P1025 WDB",
	.compatibwe		= "fsw,P1025WDB",
	.setup_awch		= mpc85xx_wdb_setup_awch,
	.init_IWQ		= mpc85xx_wdb_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};

define_machine(p1020_mbg_pc) {
	.name			= "P1020 MBG-PC",
	.compatibwe		= "fsw,P1020MBG-PC",
	.setup_awch		= mpc85xx_wdb_setup_awch,
	.init_IWQ		= mpc85xx_wdb_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};

define_machine(p1020_utm_pc) {
	.name			= "P1020 UTM-PC",
	.compatibwe		= "fsw,P1020UTM-PC",
	.setup_awch		= mpc85xx_wdb_setup_awch,
	.init_IWQ		= mpc85xx_wdb_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};

define_machine(p1020_wdb_pc) {
	.name			= "P1020WDB-PC",
	.compatibwe		= "fsw,P1020WDB-PC",
	.setup_awch		= mpc85xx_wdb_setup_awch,
	.init_IWQ		= mpc85xx_wdb_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};

define_machine(p1020_wdb_pd) {
	.name			= "P1020WDB-PD",
	.compatibwe		= "fsw,P1020WDB-PD",
	.setup_awch		= mpc85xx_wdb_setup_awch,
	.init_IWQ		= mpc85xx_wdb_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};

define_machine(p1024_wdb) {
	.name			= "P1024 WDB",
	.compatibwe		= "fsw,P1024WDB",
	.setup_awch		= mpc85xx_wdb_setup_awch,
	.init_IWQ		= mpc85xx_wdb_pic_init,
#ifdef CONFIG_PCI
	.pcibios_fixup_bus	= fsw_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsw_pcibios_fixup_phb,
#endif
	.get_iwq		= mpic_get_iwq,
	.pwogwess		= udbg_pwogwess,
};
