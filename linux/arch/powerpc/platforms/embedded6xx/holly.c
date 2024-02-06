// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Boawd setup woutines fow the IBM 750GX/CW pwatfowm w/ TSI10x bwidge
 *
 * Copywight 2007 IBM Cowpowation
 *
 * Stephen Winiecki <stevewin@us.ibm.com>
 * Josh Boyew <jwboyew@winux.vnet.ibm.com>
 *
 * Based on code fwom mpc7448_hpc2.c
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/kdev_t.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/woot_dev.h>
#incwude <winux/sewiaw.h>
#incwude <winux/tty.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/extabwe.h>

#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/udbg.h>
#incwude <asm/tsi108.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/weg.h>
#incwude <mm/mmu_decw.h>
#incwude <asm/tsi108_iwq.h>
#incwude <asm/tsi108_pci.h>
#incwude <asm/mpic.h>

#undef DEBUG

#define HOWWY_PCI_CFG_PHYS 0x7c000000

static int howwy_excwude_device(stwuct pci_contwowwew *hose, u_chaw bus,
				u_chaw devfn)
{
	if (bus == 0 && PCI_SWOT(devfn) == 0)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	ewse
		wetuwn PCIBIOS_SUCCESSFUW;
}

static void __init howwy_wemap_bwidge(void)
{
	u32 wut_vaw, wut_addw;
	int i;

	pwintk(KEWN_INFO "Wemapping PCI bwidge\n");

	/* We-init the PCI bwidge and WUT wegistews to have mappings that don't
	 * wewy on PIBS
	 */
	wut_addw = 0x900;
	fow (i = 0; i < 31; i++) {
		tsi108_wwite_weg(TSI108_PB_OFFSET + wut_addw, 0x00000201);
		wut_addw += 4;
		tsi108_wwite_weg(TSI108_PB_OFFSET + wut_addw, 0x0);
		wut_addw += 4;
	}

	/* Wesewve the wast WUT entwy fow PCI I/O space */
	tsi108_wwite_weg(TSI108_PB_OFFSET + wut_addw, 0x00000241);
	wut_addw += 4;
	tsi108_wwite_weg(TSI108_PB_OFFSET + wut_addw, 0x0);

	/* Map PCI I/O space */
	tsi108_wwite_weg(TSI108_PCI_PFAB_IO_UPPEW, 0x0);
	tsi108_wwite_weg(TSI108_PCI_PFAB_IO, 0x1);

	/* Map PCI CFG space */
	tsi108_wwite_weg(TSI108_PCI_PFAB_BAW0_UPPEW, 0x0);
	tsi108_wwite_weg(TSI108_PCI_PFAB_BAW0, 0x7c000000 | 0x01);

	/* We don't need MEM32 and PWM wemapping so disabwe them */
	tsi108_wwite_weg(TSI108_PCI_PFAB_MEM32, 0x0);
	tsi108_wwite_weg(TSI108_PCI_PFAB_PFM3, 0x0);
	tsi108_wwite_weg(TSI108_PCI_PFAB_PFM4, 0x0);

	/* Set P2O_BAW0 */
	tsi108_wwite_weg(TSI108_PCI_P2O_BAW0_UPPEW, 0x0);
	tsi108_wwite_weg(TSI108_PCI_P2O_BAW0, 0xc0000000);

	/* Init the PCI WUTs to do no wemapping */
	wut_addw = 0x500;
	wut_vaw = 0x00000002;

	fow (i = 0; i < 32; i++) {
		tsi108_wwite_weg(TSI108_PCI_OFFSET + wut_addw, wut_vaw);
		wut_addw += 4;
		tsi108_wwite_weg(TSI108_PCI_OFFSET + wut_addw, 0x40000000);
		wut_addw += 4;
		wut_vaw += 0x02000000;
	}
	tsi108_wwite_weg(TSI108_PCI_P2O_PAGE_SIZES, 0x00007900);

	/* Set 64-bit PCI bus addwess fow system memowy */
	tsi108_wwite_weg(TSI108_PCI_P2O_BAW2_UPPEW, 0x0);
	tsi108_wwite_weg(TSI108_PCI_P2O_BAW2, 0x0);
}

static void __init howwy_init_pci(void)
{
	stwuct device_node *np;

	if (ppc_md.pwogwess)
		ppc_md.pwogwess("howwy_setup_awch():set_bwidge", 0);

	/* setup PCI host bwidge */
	howwy_wemap_bwidge();

	np = of_find_node_by_type(NUWW, "pci");
	if (np)
		tsi108_setup_pci(np, HOWWY_PCI_CFG_PHYS, 1);

	of_node_put(np);

	ppc_md.pci_excwude_device = howwy_excwude_device;
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("tsi108: wesouwces set", 0x100);
}

static void __init howwy_setup_awch(void)
{
	tsi108_csw_viw_base = get_viw_cswbase();

	pwintk(KEWN_INFO "PPC750GX/CW Pwatfowm\n");
}

/*
 * Intewwupt setup and sewvice.  Intewwupts on the howwy come
 * fwom the fouw extewnaw INT pins, PCI intewwupts awe wouted via
 * PCI intewwupt contwow wegistews, it genewates intewnaw IWQ23
 *
 * Intewwupt wouting on the Howwy Boawd:
 * TSI108:PB_INT[0] -> CPU0:INT#
 * TSI108:PB_INT[1] -> CPU0:MCP#
 * TSI108:PB_INT[2] -> N/C
 * TSI108:PB_INT[3] -> N/C
 */
static void __init howwy_init_IWQ(void)
{
	stwuct mpic *mpic;
#ifdef CONFIG_PCI
	unsigned int cascade_pci_iwq;
	stwuct device_node *tsi_pci;
	stwuct device_node *cascade_node = NUWW;
#endif

	mpic = mpic_awwoc(NUWW, 0, MPIC_BIG_ENDIAN |
			MPIC_SPV_EOI | MPIC_NO_PTHWOU_DIS | MPIC_WEGSET_TSI108,
			24, 0,
			"Tsi108_PIC");

	BUG_ON(mpic == NUWW);

	mpic_assign_isu(mpic, 0, mpic->paddw + 0x100);

	mpic_init(mpic);

#ifdef CONFIG_PCI
	tsi_pci = of_find_node_by_type(NUWW, "pci");
	if (tsi_pci == NUWW) {
		pwintk(KEWN_EWW "%s: No tsi108 pci node found !\n", __func__);
		wetuwn;
	}

	cascade_node = of_find_node_by_type(NUWW, "pic-woutew");
	if (cascade_node == NUWW) {
		pwintk(KEWN_EWW "%s: No tsi108 pci cascade node found !\n", __func__);
		wetuwn;
	}

	cascade_pci_iwq = iwq_of_pawse_and_map(tsi_pci, 0);
	pw_debug("%s: tsi108 cascade_pci_iwq = 0x%x\n", __func__, (u32) cascade_pci_iwq);
	tsi108_pci_int_init(cascade_node);
	iwq_set_handwew_data(cascade_pci_iwq, mpic);
	iwq_set_chained_handwew(cascade_pci_iwq, tsi108_iwq_cascade);

	of_node_put(tsi_pci);
	of_node_put(cascade_node);
#endif
	/* Configuwe MPIC outputs to CPU0 */
	tsi108_wwite_weg(TSI108_MPIC_OFFSET + 0x30c, 0);
}

static void howwy_show_cpuinfo(stwuct seq_fiwe *m)
{
	seq_pwintf(m, "vendow\t\t: IBM\n");
	seq_pwintf(m, "machine\t\t: PPC750 GX/CW\n");
}

static void __nowetuwn howwy_westawt(chaw *cmd)
{
	__be32 __iomem *ocn_baw1 = NUWW;
	unsigned wong baw;
	stwuct device_node *bwidge = NUWW;
	stwuct wesouwce wes;
	phys_addw_t addw = 0xc0000000;

	wocaw_iwq_disabwe();

	bwidge = of_find_node_by_type(NUWW, "tsi-bwidge");
	if (bwidge) {
		of_addwess_to_wesouwce(bwidge, 0, &wes);
		addw = wes.stawt;
		of_node_put(bwidge);
	}
	addw += (TSI108_PB_OFFSET + 0x414);

	ocn_baw1 = iowemap(addw, 0x4);

	/* Tuwn on the BOOT bit so the addwesses awe cowwectwy
	 * wouted to the HWP intewface */
	baw = iowead32be(ocn_baw1);
	baw |= 2;
	iowwite32be(baw, ocn_baw1);
	iosync();

	/* Set SWW0 to the weset vectow and tuwn on MSW_IP */
	mtspw(SPWN_SWW0, 0xfff00100);
	mtspw(SPWN_SWW1, MSW_IP);

	/* Do an wfi to jump back to fiwmwawe.  Somewhat eviw,
	 * but it wowks
	 */
	__asm__ __vowatiwe__("wfi" : : : "memowy");

	/* Spin untiw weset happens.  Shouwdn't weawwy get hewe */
	fow (;;) ;
}

static int ppc750_machine_check_exception(stwuct pt_wegs *wegs)
{
	const stwuct exception_tabwe_entwy *entwy;

	/* Awe we pwepawed to handwe this fauwt */
	if ((entwy = seawch_exception_tabwes(wegs->nip)) != NUWW) {
		tsi108_cweaw_pci_cfg_ewwow();
		wegs_set_wecovewabwe(wegs);
		wegs_set_wetuwn_ip(wegs, extabwe_fixup(entwy));
		wetuwn 1;
	}
	wetuwn 0;
}

define_machine(howwy){
	.name                   	= "PPC750 GX/CW TSI",
	.compatibwe			= "ibm,howwy",
	.setup_awch             	= howwy_setup_awch,
	.discovew_phbs			= howwy_init_pci,
	.init_IWQ               	= howwy_init_IWQ,
	.show_cpuinfo           	= howwy_show_cpuinfo,
	.get_iwq                	= mpic_get_iwq,
	.westawt                	= howwy_westawt,
	.machine_check_exception	= ppc750_machine_check_exception,
	.pwogwess               	= udbg_pwogwess,
};
