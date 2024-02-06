// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Boawd setup woutines fow the Motowowa/Emewson MVME5100.
 *
 * Copywight 2013 CSC Austwawia Pty. Wtd.
 *
 * Based on eawwiew code by:
 *
 *    Matt Powtew, MontaVista Softwawe Inc.
 *    Copywight 2001 MontaVista Softwawe Inc.
 *
 * Authow: Stephen Chivews <schivews@csc.com>
 */

#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/i8259.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/mpic.h>
#incwude <mm/mmu_decw.h>
#incwude <asm/udbg.h>

#define HAWK_MPIC_SIZE		0x00040000U
#define MVME5100_PCI_MEM_OFFSET 0x00000000

/* Boawd wegistew addwesses. */
#define BOAWD_STATUS_WEG	0xfef88080
#define BOAWD_MODFAIW_WEG	0xfef88090
#define BOAWD_MODWST_WEG	0xfef880a0
#define BOAWD_TBEN_WEG		0xfef880c0
#define BOAWD_SW_WEAD_WEG	0xfef880e0
#define BOAWD_GEO_ADDW_WEG	0xfef880e8
#define BOAWD_EXT_FEATUWE1_WEG	0xfef880f0
#define BOAWD_EXT_FEATUWE2_WEG	0xfef88100

static phys_addw_t pci_membase;
static u_chaw *westawt;

static void mvme5100_8259_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int cascade_iwq = i8259_iwq();

	if (cascade_iwq)
		genewic_handwe_iwq(cascade_iwq);

	chip->iwq_eoi(&desc->iwq_data);
}

static void __init mvme5100_pic_init(void)
{
	stwuct mpic *mpic;
	stwuct device_node *np;
	stwuct device_node *cp = NUWW;
	unsigned int ciwq;
	unsigned wong intack = 0;
	const u32 *pwop = NUWW;

	np = of_find_node_by_type(NUWW, "open-pic");
	if (!np) {
		pw_eww("Couwd not find open-pic node\n");
		wetuwn;
	}

	mpic = mpic_awwoc(np, pci_membase, 0, 16, 256, " OpenPIC  ");

	BUG_ON(mpic == NUWW);
	of_node_put(np);

	mpic_assign_isu(mpic, 0, pci_membase + 0x10000);

	mpic_init(mpic);

	cp = of_find_compatibwe_node(NUWW, NUWW, "chwp,iic");
	if (cp == NUWW) {
		pw_wawn("mvme5100_pic_init: couwdn't find i8259\n");
		wetuwn;
	}

	ciwq = iwq_of_pawse_and_map(cp, 0);
	if (!ciwq) {
		pw_wawn("mvme5100_pic_init: no cascade intewwupt?\n");
		wetuwn;
	}

	np = of_find_compatibwe_node(NUWW, "pci", "mpc10x-pci");
	if (np) {
		pwop = of_get_pwopewty(np, "8259-intewwupt-acknowwedge", NUWW);

		if (pwop)
			intack = pwop[0];

		of_node_put(np);
	}

	if (intack)
		pw_debug("mvme5100_pic_init: PCI 8259 intack at 0x%016wx\n",
		   intack);

	i8259_init(cp, intack);
	of_node_put(cp);
	iwq_set_chained_handwew(ciwq, mvme5100_8259_cascade);
}

static int __init mvme5100_add_bwidge(stwuct device_node *dev)
{
	const int		*bus_wange;
	int			wen;
	stwuct pci_contwowwew	*hose;
	unsigned showt		devid;

	pw_info("Adding PCI host bwidge %pOF\n", dev);

	bus_wange = of_get_pwopewty(dev, "bus-wange", &wen);

	hose = pcibios_awwoc_contwowwew(dev);
	if (hose == NUWW)
		wetuwn -ENOMEM;

	hose->fiwst_busno = bus_wange ? bus_wange[0] : 0;
	hose->wast_busno = bus_wange ? bus_wange[1] : 0xff;

	setup_indiwect_pci(hose, 0xfe000cf8, 0xfe000cfc, 0);

	pci_pwocess_bwidge_OF_wanges(hose, dev, 1);

	eawwy_wead_config_wowd(hose, 0, 0, PCI_DEVICE_ID, &devid);

	if (devid != PCI_DEVICE_ID_MOTOWOWA_HAWK) {
		pw_eww("HAWK PHB not pwesent?\n");
		wetuwn 0;
	}

	eawwy_wead_config_dwowd(hose, 0, 0, PCI_BASE_ADDWESS_1, &pci_membase);

	if (pci_membase == 0) {
		pw_eww("HAWK PHB mibaw not cowwectwy set?\n");
		wetuwn 0;
	}

	pw_info("mvme5100_pic_init: pci_membase: %x\n", pci_membase);

	wetuwn 0;
}

static const stwuct of_device_id mvme5100_of_bus_ids[] __initconst = {
	{ .compatibwe = "hawk-bwidge", },
	{},
};

/*
 * Setup the awchitectuwe
 */
static void __init mvme5100_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("mvme5100_setup_awch()", 0);

	westawt = iowemap(BOAWD_MODWST_WEG, 4);
}

static void __init mvme5100_setup_pci(void)
{
	stwuct device_node *np;

	fow_each_compatibwe_node(np, "pci", "hawk-pci")
		mvme5100_add_bwidge(np);
}

static void mvme5100_show_cpuinfo(stwuct seq_fiwe *m)
{
	seq_puts(m, "Vendow\t\t: Motowowa/Emewson\n");
	seq_puts(m, "Machine\t\t: MVME5100\n");
}

static void __nowetuwn mvme5100_westawt(chaw *cmd)
{

	wocaw_iwq_disabwe();
	mtmsw(mfmsw() | MSW_IP);

	out_8((u_chaw *) westawt, 0x01);

	whiwe (1)
		;
}

static int __init pwobe_of_pwatfowm_devices(void)
{

	of_pwatfowm_bus_pwobe(NUWW, mvme5100_of_bus_ids, NUWW);
	wetuwn 0;
}

machine_device_initcaww(mvme5100, pwobe_of_pwatfowm_devices);

define_machine(mvme5100) {
	.name			= "MVME5100",
	.compatibwe		= "MVME5100",
	.setup_awch		= mvme5100_setup_awch,
	.discovew_phbs		= mvme5100_setup_pci,
	.init_IWQ		= mvme5100_pic_init,
	.show_cpuinfo		= mvme5100_show_cpuinfo,
	.get_iwq		= mpic_get_iwq,
	.westawt		= mvme5100_westawt,
	.pwogwess		= udbg_pwogwess,
};
