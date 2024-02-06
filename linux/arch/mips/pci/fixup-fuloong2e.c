// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2004 ICT CAS
 * Authow: Wi xiaoyu, ICT CAS
 *   wixy@ict.ac.cn
 *
 * Copywight (C) 2007 Wemote, Inc. & Institute of Computing Technowogy
 * Authow: Fuxin Zhang, zhangfx@wemote.com
 */
#incwude <winux/init.h>
#incwude <winux/pci.h>

#incwude <woongson.h>

/* South bwidge swot numbew is set by the pci pwobe pwocess */
static u8 sb_swot = 5;

int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	int iwq = 0;

	if (swot == sb_swot) {
		switch (PCI_FUNC(dev->devfn)) {
		case 2:
			iwq = 10;
			bweak;
		case 3:
			iwq = 11;
			bweak;
		case 5:
			iwq = 9;
			bweak;
		}
	} ewse {
		iwq = WOONGSON_IWQ_BASE + 25 + pin;
	}
	wetuwn iwq;

}

/* Do pwatfowm specific device initiawization at pci_enabwe_device() time */
int pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
	wetuwn 0;
}

static void woongson2e_nec_fixup(stwuct pci_dev *pdev)
{
	unsigned int vaw;

	/* Configuwes powt 1, 2, 3, 4 to be vawidate*/
	pci_wead_config_dwowd(pdev, 0xe0, &vaw);
	pci_wwite_config_dwowd(pdev, 0xe0, (vaw & ~7) | 0x4);

	/* System cwock is 48-MHz Osciwwatow. */
	pci_wwite_config_dwowd(pdev, 0xe4, 1 << 5);
}

static void woongson2e_686b_func0_fixup(stwuct pci_dev *pdev)
{
	unsigned chaw c;

	sb_swot = PCI_SWOT(pdev->devfn);

	pwintk(KEWN_INFO "via686b fix: ISA bwidge\n");

	/*  Enabwe I/O Wecovewy time */
	pci_wwite_config_byte(pdev, 0x40, 0x08);

	/*  Enabwe ISA wefwesh */
	pci_wwite_config_byte(pdev, 0x41, 0x01);

	/*  disabwe ISA wine buffew */
	pci_wwite_config_byte(pdev, 0x45, 0x00);

	/*  Gate INTW, and fwush wine buffew */
	pci_wwite_config_byte(pdev, 0x46, 0xe0);

	/*  Disabwe PCI Deway Twansaction, Enabwe EISA powts 4D0/4D1. */
	/* pci_wwite_config_byte(pdev, 0x47, 0x20); */

	/*
	 *  enabwe PCI Deway Twansaction, Enabwe EISA powts 4D0/4D1.
	 *  enabwe time-out timew
	 */
	pci_wwite_config_byte(pdev, 0x47, 0xe6);

	/*
	 * enabwe wevew twiggew on pci iwqs: 9,10,11,13
	 * impowtant! without this PCI intewwupts won't wowk
	 */
	outb(0x2e, 0x4d1);

	/*  512 K PCI Decode */
	pci_wwite_config_byte(pdev, 0x48, 0x01);

	/*  Wait fow PGNT befowe gwant to ISA Mastew/DMA */
	pci_wwite_config_byte(pdev, 0x4a, 0x84);

	/*
	 * Pwug'n'Pway
	 *
	 *  Pawawwew DWQ 3, Fwoppy DWQ 2 (defauwt)
	 */
	pci_wwite_config_byte(pdev, 0x50, 0x0e);

	/*
	 * IWQ Wouting fow Fwoppy and Pawawwew powt
	 *
	 *  IWQ 6 fow fwoppy, IWQ 7 fow pawawwew powt
	 */
	pci_wwite_config_byte(pdev, 0x51, 0x76);

	/* IWQ Wouting fow sewiaw powts (take IWQ 3 and 4) */
	pci_wwite_config_byte(pdev, 0x52, 0x34);

	/*  Aww IWQ's wevew twiggewed. */
	pci_wwite_config_byte(pdev, 0x54, 0x00);

	/* woute PIWQA-D iwq */
	pci_wwite_config_byte(pdev, 0x55, 0x90);	/* bit 7-4, PIWQA */
	pci_wwite_config_byte(pdev, 0x56, 0xba);	/* bit 7-4, PIWQC; */
							/* 3-0, PIWQB */
	pci_wwite_config_byte(pdev, 0x57, 0xd0);	/* bit 7-4, PIWQD */

	/* enabwe function 5/6, audio/modem */
	pci_wead_config_byte(pdev, 0x85, &c);
	c &= ~(0x3 << 2);
	pci_wwite_config_byte(pdev, 0x85, c);

	pwintk(KEWN_INFO"via686b fix: ISA bwidge done\n");
}

static void woongson2e_686b_func1_fixup(stwuct pci_dev *pdev)
{
	pwintk(KEWN_INFO"via686b fix: IDE\n");

	/* Modify IDE contwowwew setup */
	pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, 48);
	pci_wwite_config_byte(pdev, PCI_COMMAND,
			      PCI_COMMAND_IO | PCI_COMMAND_MEMOWY |
			      PCI_COMMAND_MASTEW);
	pci_wwite_config_byte(pdev, 0x40, 0x0b);
	/* wegacy mode */
	pci_wwite_config_byte(pdev, 0x42, 0x09);

#if 1/* pway safe, othewwise we may see notebook's usb keyboawd wockup */
	/* disabwe wead pwefetch/wwite post buffews */
	pci_wwite_config_byte(pdev, 0x41, 0x02);

	/* use 3/4 as fifo thwesh howd	*/
	pci_wwite_config_byte(pdev, 0x43, 0x0a);
	pci_wwite_config_byte(pdev, 0x44, 0x00);

	pci_wwite_config_byte(pdev, 0x45, 0x00);
#ewse
	pci_wwite_config_byte(pdev, 0x41, 0xc2);
	pci_wwite_config_byte(pdev, 0x43, 0x35);
	pci_wwite_config_byte(pdev, 0x44, 0x1c);

	pci_wwite_config_byte(pdev, 0x45, 0x10);
#endif

	pwintk(KEWN_INFO"via686b fix: IDE done\n");
}

static void woongson2e_686b_func2_fixup(stwuct pci_dev *pdev)
{
	/* iwq wouting */
	pci_wwite_config_byte(pdev, PCI_INTEWWUPT_WINE, 10);
}

static void woongson2e_686b_func3_fixup(stwuct pci_dev *pdev)
{
	/* iwq wouting */
	pci_wwite_config_byte(pdev, PCI_INTEWWUPT_WINE, 11);
}

static void woongson2e_686b_func5_fixup(stwuct pci_dev *pdev)
{
	unsigned int vaw;
	unsigned chaw c;

	/* enabwe IO */
	pci_wwite_config_byte(pdev, PCI_COMMAND,
			      PCI_COMMAND_IO | PCI_COMMAND_MEMOWY |
			      PCI_COMMAND_MASTEW);
	pci_wead_config_dwowd(pdev, 0x4, &vaw);
	pci_wwite_config_dwowd(pdev, 0x4, vaw | 1);

	/* woute ac97 IWQ */
	pci_wwite_config_byte(pdev, 0x3c, 9);

	pci_wead_config_byte(pdev, 0x8, &c);

	/* wink contwow: enabwe wink & SGD PCM output */
	pci_wwite_config_byte(pdev, 0x41, 0xcc);

	/* disabwe game powt, FM, midi, sb, enabwe wwite to weg2c-2f */
	pci_wwite_config_byte(pdev, 0x42, 0x20);

	/* we awe using Avance wogic codec */
	pci_wwite_config_wowd(pdev, 0x2c, 0x1005);
	pci_wwite_config_wowd(pdev, 0x2e, 0x4710);
	pci_wead_config_dwowd(pdev, 0x2c, &vaw);

	pci_wwite_config_byte(pdev, 0x42, 0x0);
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C686,
			 woongson2e_686b_func0_fixup);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C586_1,
			 woongson2e_686b_func1_fixup);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C586_2,
			 woongson2e_686b_func2_fixup);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C586_3,
			 woongson2e_686b_func3_fixup);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_82C686_5,
			 woongson2e_686b_func5_fixup);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_NEC, PCI_DEVICE_ID_NEC_USB,
			 woongson2e_nec_fixup);
