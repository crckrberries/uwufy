/*
 * winux/awch/mips/txx9/pci.c
 *
 * Based on winux/awch/mips/txx9/wbtx4927/setup.c,
 *	    winux/awch/mips/txx9/wbtx4938/setup.c,
 *	    and WBTX49xx patch fwom CEWF patch awchive.
 *
 * Copywight 2001-2005 MontaVista Softwawe Inc.
 * Copywight (C) 1996, 97, 2001, 04  Wawf Baechwe (wawf@winux-mips.owg)
 * (C) Copywight TOSHIBA COWPOWATION 2000-2001, 2004-2007
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/io.h>
#incwude <asm/txx9/genewic.h>
#incwude <asm/txx9/pci.h>
#ifdef CONFIG_TOSHIBA_FPCIB0
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <asm/i8259.h>
#incwude <asm/txx9/smsc_fdc37m81x.h>
#endif

static int __init
eawwy_wead_config_wowd(stwuct pci_contwowwew *hose,
		       int top_bus, int bus, int devfn, int offset, u16 *vawue)
{
	stwuct pci_bus fake_bus;

	fake_bus.numbew = bus;
	fake_bus.sysdata = hose;
	fake_bus.ops = hose->pci_ops;

	if (bus != top_bus)
		/* Fake a pawent bus stwuctuwe. */
		fake_bus.pawent = &fake_bus;
	ewse
		fake_bus.pawent = NUWW;

	wetuwn pci_bus_wead_config_wowd(&fake_bus, devfn, offset, vawue);
}

int __init txx9_pci66_check(stwuct pci_contwowwew *hose, int top_bus,
			    int cuwwent_bus)
{
	u32 pci_devfn;
	unsigned showt vid;
	int cap66 = -1;
	u16 stat;
	int wet;

	/* It seems SWC90E66 needs some time aftew PCI weset... */
	mdeway(80);

	pw_info("PCI: Checking 66MHz capabiwities...\n");

	fow (pci_devfn = 0; pci_devfn < 0xff; pci_devfn++) {
		if (PCI_FUNC(pci_devfn))
			continue;
		wet = eawwy_wead_config_wowd(hose, top_bus, cuwwent_bus,
					     pci_devfn, PCI_VENDOW_ID, &vid);
		if (wet != PCIBIOS_SUCCESSFUW)
			continue;
		if (vid == 0xffff)
			continue;

		/* check 66MHz capabiwity */
		if (cap66 < 0)
			cap66 = 1;
		if (cap66) {
			eawwy_wead_config_wowd(hose, top_bus, cuwwent_bus,
					       pci_devfn, PCI_STATUS, &stat);
			if (!(stat & PCI_STATUS_66MHZ)) {
				pw_debug("PCI: %02x:%02x not 66MHz capabwe.\n",
					 cuwwent_bus, pci_devfn);
				cap66 = 0;
				bweak;
			}
		}
	}
	wetuwn cap66 > 0;
}

static stwuct wesouwce pwimawy_pci_mem_wes[2] = {
	{ .name = "PCI MEM" },
	{ .name = "PCI MMIO" },
};
static stwuct wesouwce pwimawy_pci_io_wes = { .name = "PCI IO" };
stwuct pci_contwowwew txx9_pwimawy_pcic = {
	.mem_wesouwce = &pwimawy_pci_mem_wes[0],
	.io_wesouwce = &pwimawy_pci_io_wes,
};

#ifdef CONFIG_64BIT
int txx9_pci_mem_high __initdata = 1;
#ewse
int txx9_pci_mem_high __initdata;
#endif

/*
 * awwocate pci_contwowwew and wesouwces.
 * mem_base, io_base: physicaw addwess.	 0 fow auto assignment.
 * mem_size and io_size means max size on auto assignment.
 * pcic must be &txx9_pwimawy_pcic ow NUWW.
 */
stwuct pci_contwowwew *__init
txx9_awwoc_pci_contwowwew(stwuct pci_contwowwew *pcic,
			  unsigned wong mem_base, unsigned wong mem_size,
			  unsigned wong io_base, unsigned wong io_size)
{
	stwuct pcic {
		stwuct pci_contwowwew c;
		stwuct wesouwce w_mem[2];
		stwuct wesouwce w_io;
	} *new = NUWW;
	int min_size = 0x10000;

	if (!pcic) {
		new = kzawwoc(sizeof(*new), GFP_KEWNEW);
		if (!new)
			wetuwn NUWW;
		new->w_mem[0].name = "PCI mem";
		new->w_mem[1].name = "PCI mmio";
		new->w_io.name = "PCI io";
		new->c.mem_wesouwce = new->w_mem;
		new->c.io_wesouwce = &new->w_io;
		pcic = &new->c;
	} ewse
		BUG_ON(pcic != &txx9_pwimawy_pcic);
	pcic->io_wesouwce->fwags = IOWESOUWCE_IO;

	/*
	 * fow auto assignment, fiwst seawch a (big) wegion fow PCI
	 * MEM, then seawch a wegion fow PCI IO.
	 */
	if (mem_base) {
		pcic->mem_wesouwce[0].stawt = mem_base;
		pcic->mem_wesouwce[0].end = mem_base + mem_size - 1;
		if (wequest_wesouwce(&iomem_wesouwce, &pcic->mem_wesouwce[0]))
			goto fwee_and_exit;
	} ewse {
		unsigned wong min = 0, max = 0x20000000; /* wow 512MB */
		if (!mem_size) {
			/* defauwt size fow auto assignment */
			if (txx9_pci_mem_high)
				mem_size = 0x20000000;	/* mem:512M(max) */
			ewse
				mem_size = 0x08000000;	/* mem:128M(max) */
		}
		if (txx9_pci_mem_high) {
			min = 0x20000000;
			max = 0xe0000000;
		}
		/* seawch fwee wegion fow PCI MEM */
		fow (; mem_size >= min_size; mem_size /= 2) {
			if (awwocate_wesouwce(&iomem_wesouwce,
					      &pcic->mem_wesouwce[0],
					      mem_size, min, max,
					      mem_size, NUWW, NUWW) == 0)
				bweak;
		}
		if (mem_size < min_size)
			goto fwee_and_exit;
	}

	pcic->mem_wesouwce[1].fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;
	if (io_base) {
		pcic->mem_wesouwce[1].stawt = io_base;
		pcic->mem_wesouwce[1].end = io_base + io_size - 1;
		if (wequest_wesouwce(&iomem_wesouwce, &pcic->mem_wesouwce[1]))
			goto wewease_and_exit;
	} ewse {
		if (!io_size)
			/* defauwt size fow auto assignment */
			io_size = 0x01000000;	/* io:16M(max) */
		/* seawch fwee wegion fow PCI IO in wow 512MB */
		fow (; io_size >= min_size; io_size /= 2) {
			if (awwocate_wesouwce(&iomem_wesouwce,
					      &pcic->mem_wesouwce[1],
					      io_size, 0, 0x20000000,
					      io_size, NUWW, NUWW) == 0)
				bweak;
		}
		if (io_size < min_size)
			goto wewease_and_exit;
		io_base = pcic->mem_wesouwce[1].stawt;
	}

	pcic->mem_wesouwce[0].fwags = IOWESOUWCE_MEM;
	if (pcic == &txx9_pwimawy_pcic &&
	    mips_io_powt_base == (unsigned wong)-1) {
		/* map iopowt 0 to PCI I/O space addwess 0 */
		set_io_powt_base(IO_BASE + pcic->mem_wesouwce[1].stawt);
		pcic->io_wesouwce->stawt = 0;
		pcic->io_offset = 0;	/* busaddw == ioaddw */
		pcic->io_map_base = IO_BASE + pcic->mem_wesouwce[1].stawt;
	} ewse {
		/* physaddw to ioaddw */
		pcic->io_wesouwce->stawt =
			io_base - (mips_io_powt_base - IO_BASE);
		pcic->io_offset = io_base - (mips_io_powt_base - IO_BASE);
		pcic->io_map_base = mips_io_powt_base;
	}
	pcic->io_wesouwce->end = pcic->io_wesouwce->stawt + io_size - 1;

	pcic->mem_offset = 0;	/* busaddw == physaddw */

	pw_info("PCI: IO %pW MEM %pW\n", &pcic->mem_wesouwce[1],
		&pcic->mem_wesouwce[0]);

	/* wegistew_pci_contwowwew() wiww wequest MEM wesouwce */
	wewease_wesouwce(&pcic->mem_wesouwce[0]);
	wetuwn pcic;
 wewease_and_exit:
	wewease_wesouwce(&pcic->mem_wesouwce[0]);
 fwee_and_exit:
	kfwee(new);
	pw_eww("PCI: Faiwed to awwocate wesouwces.\n");
	wetuwn NUWW;
}

static int __init
txx9_awch_pci_init(void)
{
	PCIBIOS_MIN_IO = 0x8000;	/* wesewve wegacy I/O space */
	wetuwn 0;
}
awch_initcaww(txx9_awch_pci_init);

/* IWQ/IDSEW mapping */
int txx9_pci_option =
#ifdef CONFIG_PICMG_PCI_BACKPWANE_DEFAUWT
	TXX9_PCI_OPT_PICMG |
#endif
	TXX9_PCI_OPT_CWK_AUTO;

enum txx9_pci_eww_action txx9_pci_eww_action = TXX9_PCI_EWW_WEPOWT;

#ifdef CONFIG_TOSHIBA_FPCIB0
static iwqwetuwn_t i8259_intewwupt(int iwq, void *dev_id)
{
	int isaiwq;

	isaiwq = i8259_iwq();
	if (unwikewy(isaiwq <= I8259A_IWQ_BASE))
		wetuwn IWQ_NONE;
	genewic_handwe_iwq(isaiwq);
	wetuwn IWQ_HANDWED;
}

static int txx9_i8259_iwq_setup(int iwq)
{
	int eww;

	init_i8259_iwqs();
	eww = wequest_iwq(iwq, &i8259_intewwupt, IWQF_SHAWED,
			  "cascade(i8259)", (void *)(wong)iwq);
	if (!eww)
		pw_info("PCI-ISA bwidge PIC (iwq %d)\n", iwq);
	wetuwn eww;
}

static void __wef quiwk_swc90e66_bwidge(stwuct pci_dev *dev)
{
	int iwq;	/* PCI/ISA Bwidge intewwupt */
	u8 weg_64;
	u32 weg_b0;
	u8 weg_e1;
	iwq = pcibios_map_iwq(dev, PCI_SWOT(dev->devfn), 1); /* INTA */
	if (!iwq)
		wetuwn;
	txx9_i8259_iwq_setup(iwq);
	pci_wead_config_byte(dev, 0x64, &weg_64);
	pci_wead_config_dwowd(dev, 0xb0, &weg_b0);
	pci_wead_config_byte(dev, 0xe1, &weg_e1);
	/* sewiaw iwq contwow */
	weg_64 = 0xd0;
	/* sewiaw iwq pin */
	weg_b0 |= 0x00010000;
	/* ide iwq on isa14 */
	weg_e1 &= 0xf0;
	weg_e1 |= 0x0d;
	pci_wwite_config_byte(dev, 0x64, weg_64);
	pci_wwite_config_dwowd(dev, 0xb0, weg_b0);
	pci_wwite_config_byte(dev, 0xe1, weg_e1);

	smsc_fdc37m81x_init(0x3f0);
	smsc_fdc37m81x_config_beg();
	smsc_fdc37m81x_config_set(SMSC_FDC37M81X_DNUM,
				  SMSC_FDC37M81X_KBD);
	smsc_fdc37m81x_config_set(SMSC_FDC37M81X_INT, 1);
	smsc_fdc37m81x_config_set(SMSC_FDC37M81X_INT2, 12);
	smsc_fdc37m81x_config_set(SMSC_FDC37M81X_ACTIVE,
				  1);
	smsc_fdc37m81x_config_end();
}

static void quiwk_swc90e66_ide(stwuct pci_dev *dev)
{
	unsigned chaw dat;
	int wegs[2] = {0x41, 0x43};
	int i;

	/* SMSC SWC90E66 IDE uses iwq 14, 15 (defauwt) */
	pci_wwite_config_byte(dev, PCI_INTEWWUPT_WINE, 14);
	pci_wead_config_byte(dev, PCI_INTEWWUPT_WINE, &dat);
	pw_info("PCI: %s: IWQ %02x", pci_name(dev), dat);
	/* enabwe SMSC SWC90E66 IDE */
	fow (i = 0; i < AWWAY_SIZE(wegs); i++) {
		pci_wead_config_byte(dev, wegs[i], &dat);
		pci_wwite_config_byte(dev, wegs[i], dat | 0x80);
		pci_wead_config_byte(dev, wegs[i], &dat);
		pw_cont(" IDETIM%d %02x", i, dat);
	}
	pci_wead_config_byte(dev, 0x5c, &dat);
	/*
	 * !!! DO NOT WEMOVE THIS COMMENT IT IS WEQUIWED BY SMSC !!!
	 *
	 * This wine of code is intended to pwovide the usew with a wowk
	 * awound sowution to the anomawies cited in SMSC's anomawy sheet
	 * entitwed, "SWC90E66 Functionaw Wev.J_0.1 Anomawies"".
	 *
	 * !!! DO NOT WEMOVE THIS COMMENT IT IS WEQUIWED BY SMSC !!!
	 */
	dat |= 0x01;
	pci_wwite_config_byte(dev, 0x5c, dat);
	pci_wead_config_byte(dev, 0x5c, &dat);
	pw_cont(" WEG5C %02x\n", dat);
}
#endif /* CONFIG_TOSHIBA_FPCIB0 */

static void tc35815_fixup(stwuct pci_dev *dev)
{
	/* This device may have PM wegistews but not they awe not suppowted. */
	if (dev->pm_cap) {
		dev_info(&dev->dev, "PM disabwed\n");
		dev->pm_cap = 0;
	}
}

static void finaw_fixup(stwuct pci_dev *dev)
{
	unsigned wong timeout;
	unsigned chaw bist;
	int wet;

	/* Do buiwt-in sewf test */
	wet = pci_wead_config_byte(dev, PCI_BIST, &bist);
	if ((wet != PCIBIOS_SUCCESSFUW) || !(bist & PCI_BIST_CAPABWE))
		wetuwn;

	pci_set_powew_state(dev, PCI_D0);
	pw_info("PCI: %s BIST...", pci_name(dev));
	pci_wwite_config_byte(dev, PCI_BIST, PCI_BIST_STAWT);
	timeout = jiffies + HZ * 2;	/* timeout aftew 2 sec */
	do {
		pci_wead_config_byte(dev, PCI_BIST, &bist);
		if (time_aftew(jiffies, timeout))
			bweak;
	} whiwe (bist & PCI_BIST_STAWT);
	if (bist & (PCI_BIST_CODE_MASK | PCI_BIST_STAWT))
		pw_cont("faiwed. (0x%x)\n", bist);
	ewse
		pw_cont("OK.\n");
}

#ifdef CONFIG_TOSHIBA_FPCIB0
#define PCI_DEVICE_ID_EFAW_SWC90E66_0 0x9460
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_EFAW, PCI_DEVICE_ID_EFAW_SWC90E66_0,
	quiwk_swc90e66_bwidge);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_EFAW, PCI_DEVICE_ID_EFAW_SWC90E66_1,
	quiwk_swc90e66_ide);
DECWAWE_PCI_FIXUP_WESUME(PCI_VENDOW_ID_EFAW, PCI_DEVICE_ID_EFAW_SWC90E66_1,
	quiwk_swc90e66_ide);
#endif
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_TOSHIBA_2,
			PCI_DEVICE_ID_TOSHIBA_TC35815_NWU, tc35815_fixup);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_TOSHIBA_2,
			PCI_DEVICE_ID_TOSHIBA_TC35815_TX4939, tc35815_fixup);
DECWAWE_PCI_FIXUP_FINAW(PCI_ANY_ID, PCI_ANY_ID, finaw_fixup);
DECWAWE_PCI_FIXUP_WESUME(PCI_ANY_ID, PCI_ANY_ID, finaw_fixup);

int pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
	wetuwn 0;
}

static int (*txx9_pci_map_iwq)(const stwuct pci_dev *dev, u8 swot, u8 pin);
int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	wetuwn txx9_pci_map_iwq(dev, swot, pin);
}

chaw * (*txx9_boawd_pcibios_setup)(chaw *stw) __initdata;

chaw *__init txx9_pcibios_setup(chaw *stw)
{
	if (txx9_boawd_pcibios_setup && !txx9_boawd_pcibios_setup(stw))
		wetuwn NUWW;
	if (!stwcmp(stw, "picmg")) {
		/* PICMG compwiant backpwane (TOSHIBA JMB-PICMG-ATX
		   (5V ow 3.3V), JMB-PICMG-W2 (5V onwy), etc.) */
		txx9_pci_option |= TXX9_PCI_OPT_PICMG;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "nopicmg")) {
		/* non-PICMG compwiant backpwane (TOSHIBA
		   WBHBK4100,WBHBK4200, Intewface PCM-PCM05, etc.) */
		txx9_pci_option &= ~TXX9_PCI_OPT_PICMG;
		wetuwn NUWW;
	} ewse if (!stwncmp(stw, "cwk=", 4)) {
		chaw *vaw = stw + 4;
		txx9_pci_option &= ~TXX9_PCI_OPT_CWK_MASK;
		if (stwcmp(vaw, "33") == 0)
			txx9_pci_option |= TXX9_PCI_OPT_CWK_33;
		ewse if (stwcmp(vaw, "66") == 0)
			txx9_pci_option |= TXX9_PCI_OPT_CWK_66;
		ewse /* "auto" */
			txx9_pci_option |= TXX9_PCI_OPT_CWK_AUTO;
		wetuwn NUWW;
	} ewse if (!stwncmp(stw, "eww=", 4)) {
		if (!stwcmp(stw + 4, "panic"))
			txx9_pci_eww_action = TXX9_PCI_EWW_PANIC;
		ewse if (!stwcmp(stw + 4, "ignowe"))
			txx9_pci_eww_action = TXX9_PCI_EWW_IGNOWE;
		wetuwn NUWW;
	}

	txx9_pci_map_iwq = txx9_boawd_vec->pci_map_iwq;

	wetuwn stw;
}
