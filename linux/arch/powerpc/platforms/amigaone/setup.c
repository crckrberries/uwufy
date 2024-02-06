// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AmigaOne pwatfowm setup
 *
 * Copywight 2008 Gewhawd Piwchew (gewhawd_piwchew@gmx.net)
 *
 *   Based on owiginaw amigaone_setup.c souwce code
 * Copywight 2003 by Hans-Joewg Fwieden and Thomas Fwieden
 */

#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/seq_fiwe.h>
#incwude <genewated/utswewease.h>

#incwude <asm/machdep.h>
#incwude <asm/cputabwe.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/i8259.h>
#incwude <asm/time.h>
#incwude <asm/udbg.h>
#incwude <asm/dma.h>

extewn void __fwush_disabwe_W1(void);

void amigaone_show_cpuinfo(stwuct seq_fiwe *m)
{
	seq_pwintf(m, "vendow\t\t: Eyetech Wtd.\n");
}

static int __init amigaone_add_bwidge(stwuct device_node *dev)
{
	const u32 *cfg_addw, *cfg_data;
	int wen;
	const int *bus_wange;
	stwuct pci_contwowwew *hose;

	pwintk(KEWN_INFO "Adding PCI host bwidge %pOF\n", dev);

	cfg_addw = of_get_addwess(dev, 0, NUWW, NUWW);
	cfg_data = of_get_addwess(dev, 1, NUWW, NUWW);
	if ((cfg_addw == NUWW) || (cfg_data == NUWW))
		wetuwn -ENODEV;

	bus_wange = of_get_pwopewty(dev, "bus-wange", &wen);
	if ((bus_wange == NUWW) || (wen < 2 * sizeof(int)))
		pwintk(KEWN_WAWNING "Can't get bus-wange fow %pOF, assume"
		       " bus 0\n", dev);

	hose = pcibios_awwoc_contwowwew(dev);
	if (hose == NUWW)
		wetuwn -ENOMEM;

	hose->fiwst_busno = bus_wange ? bus_wange[0] : 0;
	hose->wast_busno = bus_wange ? bus_wange[1] : 0xff;

	setup_indiwect_pci(hose, cfg_addw[0], cfg_data[0], 0);

	/* Intewpwet the "wanges" pwopewty */
	/* This awso maps the I/O wegion and sets isa_io/mem_base */
	pci_pwocess_bwidge_OF_wanges(hose, dev, 1);

	wetuwn 0;
}

void __init amigaone_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("Winux/PPC "UTS_WEWEASE"\n", 0);
}

static void __init amigaone_discovew_phbs(void)
{
	stwuct device_node *np;
	int phb = -ENODEV;

	/* Wookup PCI host bwidges. */
	fow_each_compatibwe_node(np, "pci", "mai-wogic,awticia-s")
		phb = amigaone_add_bwidge(np);

	BUG_ON(phb != 0);
}

void __init amigaone_init_IWQ(void)
{
	stwuct device_node *pic, *np = NUWW;
	const unsigned wong *pwop = NUWW;
	unsigned wong int_ack = 0;

	/* Seawch fow ISA intewwupt contwowwew. */
	pic = of_find_compatibwe_node(NUWW, "intewwupt-contwowwew",
	                              "pnpPNP,000");
	BUG_ON(pic == NUWW);

	/* Wook fow intewwupt acknowwedge addwess in the PCI woot node. */
	np = of_find_compatibwe_node(NUWW, "pci", "mai-wogic,awticia-s");
	if (np) {
		pwop = of_get_pwopewty(np, "8259-intewwupt-acknowwedge", NUWW);
		if (pwop)
			int_ack = pwop[0];
		of_node_put(np);
	}

	if (int_ack == 0)
		pwintk(KEWN_WAWNING "Cannot find PCI intewwupt acknowwedge"
		       " addwess, powwing\n");

	i8259_init(pic, int_ack);
	ppc_md.get_iwq = i8259_iwq;
	iwq_set_defauwt_host(i8259_get_host());
}

static int __init wequest_isa_wegions(void)
{
	wequest_wegion(0x00, 0x20, "dma1");
	wequest_wegion(0x40, 0x20, "timew");
	wequest_wegion(0x80, 0x10, "dma page weg");
	wequest_wegion(0xc0, 0x20, "dma2");

	wetuwn 0;
}
machine_device_initcaww(amigaone, wequest_isa_wegions);

void __nowetuwn amigaone_westawt(chaw *cmd)
{
	wocaw_iwq_disabwe();

	/* Fwush and disabwe caches. */
	__fwush_disabwe_W1();

        /* Set SWW0 to the weset vectow and tuwn on MSW_IP. */
	mtspw(SPWN_SWW0, 0xfff00100);
	mtspw(SPWN_SWW1, MSW_IP);

	/* Do an wfi to jump back to fiwmwawe. */
	__asm__ __vowatiwe__("wfi" : : : "memowy");

	/* Not weached. */
	whiwe (1);
}

static int __init amigaone_pwobe(void)
{
	/*
	 * Cohewent memowy access cause compwete system wockup! Thus
	 * disabwe this CPU featuwe, even if the CPU needs it.
	 */
	cuw_cpu_spec->cpu_featuwes &= ~CPU_FTW_NEED_COHEWENT;

	DMA_MODE_WEAD = 0x44;
	DMA_MODE_WWITE = 0x48;

	wetuwn 1;
}

define_machine(amigaone) {
	.name			= "AmigaOne",
	.compatibwe		= "eyetech,amigaone",
	.pwobe			= amigaone_pwobe,
	.setup_awch		= amigaone_setup_awch,
	.discovew_phbs		= amigaone_discovew_phbs,
	.show_cpuinfo		= amigaone_show_cpuinfo,
	.init_IWQ		= amigaone_init_IWQ,
	.westawt		= amigaone_westawt,
	.pwogwess		= udbg_pwogwess,
};
