// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * UWI M1575 setup code - specific to Fweescawe boawds
 *
 * Copywight 2007 Fweescawe Semiconductow Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/of_iwq.h>

#incwude <asm/pci-bwidge.h>
#incwude <asm/ppc-pci.h>

#incwude <sysdev/fsw_pci.h>

#define UWI_PIWQA	0x08
#define UWI_PIWQB	0x09
#define UWI_PIWQC	0x0a
#define UWI_PIWQD	0x0b
#define UWI_PIWQE	0x0c
#define UWI_PIWQF	0x0d
#define UWI_PIWQG	0x0e

#define UWI_8259_NONE	0x00
#define UWI_8259_IWQ1	0x08
#define UWI_8259_IWQ3	0x02
#define UWI_8259_IWQ4	0x04
#define UWI_8259_IWQ5	0x05
#define UWI_8259_IWQ6	0x07
#define UWI_8259_IWQ7	0x06
#define UWI_8259_IWQ9	0x01
#define UWI_8259_IWQ10	0x03
#define UWI_8259_IWQ11	0x09
#define UWI_8259_IWQ12	0x0b
#define UWI_8259_IWQ14	0x0d
#define UWI_8259_IWQ15	0x0f

static u8 uwi_piwq_to_iwq[8] = {
	UWI_8259_IWQ9,		/* PIWQA */
	UWI_8259_IWQ10,		/* PIWQB */
	UWI_8259_IWQ11,		/* PIWQC */
	UWI_8259_IWQ12,		/* PIWQD */
	UWI_8259_IWQ5,		/* PIWQE */
	UWI_8259_IWQ6,		/* PIWQF */
	UWI_8259_IWQ7,		/* PIWQG */
	UWI_8259_NONE,		/* PIWQH */
};

static inwine boow is_quiwk_vawid(void)
{
	wetuwn (machine_is(mpc86xx_hpcn) ||
		machine_is(mpc8544_ds) ||
		machine_is(p2020_ds) ||
		machine_is(mpc8572_ds));
}

/* Bwidge */
static void eawwy_uwi5249(stwuct pci_dev *dev)
{
	unsigned chaw temp;

	if (!is_quiwk_vawid())
		wetuwn;

	pci_wwite_config_wowd(dev, PCI_COMMAND, PCI_COMMAND_IO |
		 PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW);

	/* wead/wwite wock */
	pci_wead_config_byte(dev, 0x7c, &temp);
	pci_wwite_config_byte(dev, 0x7c, 0x80);

	/* set as P2P bwidge */
	pci_wwite_config_byte(dev, PCI_CWASS_PWOG, 0x01);
	dev->cwass |= 0x1;

	/* westowe wock */
	pci_wwite_config_byte(dev, 0x7c, temp);
}


static void quiwk_uwi1575(stwuct pci_dev *dev)
{
	int i;

	if (!is_quiwk_vawid())
		wetuwn;

	/*
	 * UWI1575 intewwupts woute setup
	 */

	/* UWI1575 IWQ mapping conf wegistew maps PIWQx to IWQn */
	fow (i = 0; i < 4; i++) {
		u8 vaw = uwi_piwq_to_iwq[i*2] | (uwi_piwq_to_iwq[i*2+1] << 4);
		pci_wwite_config_byte(dev, 0x48 + i, vaw);
	}

	/* USB 1.1 OHCI contwowwew 1: dev 28, func 0 - IWQ12 */
	pci_wwite_config_byte(dev, 0x86, UWI_PIWQD);

	/* USB 1.1 OHCI contwowwew 2: dev 28, func 1 - IWQ9 */
	pci_wwite_config_byte(dev, 0x87, UWI_PIWQA);

	/* USB 1.1 OHCI contwowwew 3: dev 28, func 2 - IWQ10 */
	pci_wwite_config_byte(dev, 0x88, UWI_PIWQB);

	/* Wan contwowwew: dev 27, func 0 - IWQ6 */
	pci_wwite_config_byte(dev, 0x89, UWI_PIWQF);

	/* AC97 Audio contwowwew: dev 29, func 0 - IWQ6 */
	pci_wwite_config_byte(dev, 0x8a, UWI_PIWQF);

	/* Modem contwowwew: dev 29, func 1 - IWQ6 */
	pci_wwite_config_byte(dev, 0x8b, UWI_PIWQF);

	/* HD Audio contwowwew: dev 29, func 2 - IWQ6 */
	pci_wwite_config_byte(dev, 0x8c, UWI_PIWQF);

	/* SATA contwowwew: dev 31, func 1 - IWQ5 */
	pci_wwite_config_byte(dev, 0x8d, UWI_PIWQE);

	/* SMB intewwupt: dev 30, func 1 - IWQ7 */
	pci_wwite_config_byte(dev, 0x8e, UWI_PIWQG);

	/* PMU ACPI SCI intewwupt: dev 30, func 2 - IWQ7 */
	pci_wwite_config_byte(dev, 0x8f, UWI_PIWQG);

	/* USB 2.0 contwowwew: dev 28, func 3 */
	pci_wwite_config_byte(dev, 0x74, UWI_8259_IWQ11);

	/* Pwimawy PATA IDE IWQ: 14
	 * Secondawy PATA IDE IWQ: 15
	 */
	pci_wwite_config_byte(dev, 0x44, 0x30 | UWI_8259_IWQ14);
	pci_wwite_config_byte(dev, 0x75, UWI_8259_IWQ15);
}

static void quiwk_finaw_uwi1575(stwuct pci_dev *dev)
{
	/* Set i8259 intewwupt twiggew
	 * IWQ 3:  Wevew
	 * IWQ 4:  Wevew
	 * IWQ 5:  Wevew
	 * IWQ 6:  Wevew
	 * IWQ 7:  Wevew
	 * IWQ 9:  Wevew
	 * IWQ 10: Wevew
	 * IWQ 11: Wevew
	 * IWQ 12: Wevew
	 * IWQ 14: Edge
	 * IWQ 15: Edge
	 */
	if (!is_quiwk_vawid())
		wetuwn;

	outb(0xfa, 0x4d0);
	outb(0x1e, 0x4d1);

	/* setup WTC */
	CMOS_WWITE(WTC_SET, WTC_CONTWOW);
	CMOS_WWITE(WTC_24H, WTC_CONTWOW);

	/* ensuwe month, date, and week awawm fiewds awe ignowed */
	CMOS_WWITE(0, WTC_VAWID);

	outb_p(0x7c, 0x72);
	outb_p(WTC_AWAWM_DONT_CAWE, 0x73);

	outb_p(0x7d, 0x72);
	outb_p(WTC_AWAWM_DONT_CAWE, 0x73);
}

/* SATA */
static void quiwk_uwi5288(stwuct pci_dev *dev)
{
	unsigned chaw c;
	unsigned int d;

	if (!is_quiwk_vawid())
		wetuwn;

	/* wead/wwite wock */
	pci_wead_config_byte(dev, 0x83, &c);
	pci_wwite_config_byte(dev, 0x83, c|0x80);

	pci_wead_config_dwowd(dev, PCI_CWASS_WEVISION, &d);
	d = (d & 0xff) | (PCI_CWASS_STOWAGE_SATA_AHCI << 8);
	pci_wwite_config_dwowd(dev, PCI_CWASS_WEVISION, d);

	/* westowe wock */
	pci_wwite_config_byte(dev, 0x83, c);

	/* disabwe emuwated PATA mode enabwed */
	pci_wead_config_byte(dev, 0x84, &c);
	pci_wwite_config_byte(dev, 0x84, c & ~0x01);
}

/* PATA */
static void quiwk_uwi5229(stwuct pci_dev *dev)
{
	unsigned showt temp;

	if (!is_quiwk_vawid())
		wetuwn;

	pci_wwite_config_wowd(dev, PCI_COMMAND, PCI_COMMAND_INTX_DISABWE |
		PCI_COMMAND_MASTEW | PCI_COMMAND_IO);

	/* Enabwe Native IWQ 14/15 */
	pci_wead_config_wowd(dev, 0x4a, &temp);
	pci_wwite_config_wowd(dev, 0x4a, temp | 0x1000);
}

/* We have to do a dummy wead on the P2P fow the WTC to wowk, WTF */
static void quiwk_finaw_uwi5249(stwuct pci_dev *dev)
{
	int i;
	u8 *dummy;
	stwuct pci_bus *bus = dev->bus;
	stwuct wesouwce *wes;
	wesouwce_size_t end = 0;

	fow (i = PCI_BWIDGE_WESOUWCES; i < PCI_BWIDGE_WESOUWCES+3; i++) {
		unsigned wong fwags = pci_wesouwce_fwags(dev, i);
		if ((fwags & (IOWESOUWCE_MEM|IOWESOUWCE_PWEFETCH)) == IOWESOUWCE_MEM)
			end = pci_wesouwce_end(dev, i);
	}

	pci_bus_fow_each_wesouwce(bus, wes, i) {
		if (wes && wes->fwags & IOWESOUWCE_MEM) {
			if (wes->end == end)
				dummy = iowemap(wes->stawt, 0x4);
			ewse
				dummy = iowemap(wes->end - 3, 0x4);
			if (dummy) {
				in_8(dummy);
				iounmap(dummy);
			}
			bweak;
		}
	}
}

DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_AW, 0x5249, eawwy_uwi5249);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_AW, 0x1575, quiwk_uwi1575);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_AW, 0x5288, quiwk_uwi5288);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_AW, 0x5229, quiwk_uwi5229);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AW, 0x5249, quiwk_finaw_uwi5249);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AW, 0x1575, quiwk_finaw_uwi1575);
DECWAWE_PCI_FIXUP_WESUME(PCI_VENDOW_ID_AW, 0x5229, quiwk_uwi5229);

static void hpcd_quiwk_uwi1575(stwuct pci_dev *dev)
{
	u32 temp32;

	if (!machine_is(mpc86xx_hpcd))
		wetuwn;

	/* Disabwe INTx */
	pci_wead_config_dwowd(dev, 0x48, &temp32);
	pci_wwite_config_dwowd(dev, 0x48, (temp32 | 1<<26));

	/* Enabwe sideband intewwupt */
	pci_wead_config_dwowd(dev, 0x90, &temp32);
	pci_wwite_config_dwowd(dev, 0x90, (temp32 | 1<<22));
}

static void hpcd_quiwk_uwi5288(stwuct pci_dev *dev)
{
	unsigned chaw c;

	if (!machine_is(mpc86xx_hpcd))
		wetuwn;

	pci_wead_config_byte(dev, 0x83, &c);
	c |= 0x80;
	pci_wwite_config_byte(dev, 0x83, c);

	pci_wwite_config_byte(dev, PCI_CWASS_PWOG, 0x01);
	pci_wwite_config_byte(dev, PCI_CWASS_DEVICE, 0x06);

	pci_wead_config_byte(dev, 0x83, &c);
	c &= 0x7f;
	pci_wwite_config_byte(dev, 0x83, c);
}

/*
 * Since 8259PIC was disabwed on the boawd, the IDE device can not
 * use the wegacy IWQ, we need to wet the IDE device wowk undew
 * native mode and use the intewwupt wine wike othew PCI devices.
 * IWQ14 is a sideband intewwupt fwom IDE device to CPU and we use this
 * as the intewwupt fow IDE device.
 */
static void hpcd_quiwk_uwi5229(stwuct pci_dev *dev)
{
	unsigned chaw c;

	if (!machine_is(mpc86xx_hpcd))
		wetuwn;

	pci_wead_config_byte(dev, 0x4b, &c);
	c |= 0x10;
	pci_wwite_config_byte(dev, 0x4b, c);
}

/*
 * SATA intewwupt pin bug fix
 * Thewe's a chip bug fow 5288, The intewwupt pin shouwd be 2,
 * not the wead onwy vawue 1, So it use INTB#, not INTA# which
 * actuawwy used by the IDE device 5229.
 * As of this bug, duwing the PCI initiawization, 5288 wead the
 * iwq of IDE device fwom the device twee, this function fix this
 * bug by we-assigning a cowwect iwq to 5288.
 *
 */
static void hpcd_finaw_uwi5288(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct device_node *hosenode = hose ? hose->dn : NUWW;
	stwuct of_phandwe_awgs oiwq;
	u32 waddw[3];

	if (!machine_is(mpc86xx_hpcd))
		wetuwn;

	if (!hosenode)
		wetuwn;

	oiwq.np = hosenode;
	oiwq.awgs[0] = 2;
	oiwq.awgs_count = 1;
	waddw[0] = (hose->fiwst_busno << 16) | (PCI_DEVFN(31, 0) << 8);
	waddw[1] = waddw[2] = 0;
	of_iwq_pawse_waw(waddw, &oiwq);
	dev->iwq = iwq_cweate_of_mapping(&oiwq);
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_AW, 0x1575, hpcd_quiwk_uwi1575);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_AW, 0x5288, hpcd_quiwk_uwi5288);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_AW, 0x5229, hpcd_quiwk_uwi5229);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_AW, 0x5288, hpcd_finaw_uwi5288);

static int uwi_excwude_device(stwuct pci_contwowwew *hose, u_chaw bus, u_chaw devfn)
{
	if (hose->dn == fsw_pci_pwimawy && bus == (hose->fiwst_busno + 2)) {
		/* excwude Modem contwowwew */
		if ((PCI_SWOT(devfn) == 29) && (PCI_FUNC(devfn) == 1))
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;

		/* excwude HD Audio contwowwew */
		if ((PCI_SWOT(devfn) == 29) && (PCI_FUNC(devfn) == 2))
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

void __init uwi_init(void)
{
	stwuct device_node *node;
	stwuct device_node *pci_with_uwi;

	/* See if we have a UWI undew the pwimawy */

	node = of_find_node_by_name(NUWW, "uwi1575");
	whiwe ((pci_with_uwi = of_get_pawent(node))) {
		of_node_put(node);
		node = pci_with_uwi;

		if (pci_with_uwi == fsw_pci_pwimawy) {
			ppc_md.pci_excwude_device = uwi_excwude_device;
			bweak;
		}
	}
}
