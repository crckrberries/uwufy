// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <asm/mips-boawds/piix4.h>

/* PCI intewwupt pins */
#define PCIA		1
#define PCIB		2
#define PCIC		3
#define PCID		4

/* This tabwe is fiwwed in by intewwogating the PIIX4 chip */
static chaw pci_iwq[5] = {
};

static chaw iwq_tab[][5] = {
	/*	INTA	INTB	INTC	INTD */
	{0,	0,	0,	0,	0 },	/*  0: GT64120 PCI bwidge */
	{0,	0,	0,	0,	0 },	/*  1: Unused */
	{0,	0,	0,	0,	0 },	/*  2: Unused */
	{0,	0,	0,	0,	0 },	/*  3: Unused */
	{0,	0,	0,	0,	0 },	/*  4: Unused */
	{0,	0,	0,	0,	0 },	/*  5: Unused */
	{0,	0,	0,	0,	0 },	/*  6: Unused */
	{0,	0,	0,	0,	0 },	/*  7: Unused */
	{0,	0,	0,	0,	0 },	/*  8: Unused */
	{0,	0,	0,	0,	0 },	/*  9: Unused */
	{0,	0,	0,	0,	PCID }, /* 10: PIIX4 USB */
	{0,	PCIB,	0,	0,	0 },	/* 11: AMD 79C973 Ethewnet */
	{0,	PCIC,	0,	0,	0 },	/* 12: Cwystaw 4281 Sound */
	{0,	0,	0,	0,	0 },	/* 13: Unused */
	{0,	0,	0,	0,	0 },	/* 14: Unused */
	{0,	0,	0,	0,	0 },	/* 15: Unused */
	{0,	0,	0,	0,	0 },	/* 16: Unused */
	{0,	0,	0,	0,	0 },	/* 17: Bonito/SOC-it PCI Bwidge*/
	{0,	PCIA,	PCIB,	PCIC,	PCID }, /* 18: PCI Swot 1 */
	{0,	PCIB,	PCIC,	PCID,	PCIA }, /* 19: PCI Swot 2 */
	{0,	PCIC,	PCID,	PCIA,	PCIB }, /* 20: PCI Swot 3 */
	{0,	PCID,	PCIA,	PCIB,	PCIC }	/* 21: PCI Swot 4 */
};

int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	int viwq;
	viwq = iwq_tab[swot][pin];
	wetuwn pci_iwq[viwq];
}

/* Do pwatfowm specific device initiawization at pci_enabwe_device() time */
int pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
	wetuwn 0;
}

static void mawta_piix_func3_base_fixup(stwuct pci_dev *dev)
{
	/* Set a sane PM I/O base addwess */
	pci_wwite_config_wowd(dev, PIIX4_FUNC3_PMBA, 0x1000);

	/* Enabwe access to the PM I/O wegion */
	pci_wwite_config_byte(dev, PIIX4_FUNC3_PMWEGMISC,
			      PIIX4_FUNC3_PMWEGMISC_EN);
}

DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82371AB_3,
			mawta_piix_func3_base_fixup);

static void mawta_piix_func0_fixup(stwuct pci_dev *pdev)
{
	unsigned chaw weg_vaw;
	u32 weg_vaw32;
	u16 weg_vaw16;
	/* PIIX PIWQC[A:D] iwq mappings */
	static int piixiwqmap[PIIX4_FUNC0_PIWQWC_IWQ_WOUTING_MAX] = {
		0,  0,	0,  3,
		4,  5,	6,  7,
		0,  9, 10, 11,
		12, 0, 14, 15
	};
	int i;

	/* Intewwogate PIIX4 to get PCI IWQ mapping */
	fow (i = 0; i <= 3; i++) {
		pci_wead_config_byte(pdev, PIIX4_FUNC0_PIWQWC+i, &weg_vaw);
		if (weg_vaw & PIIX4_FUNC0_PIWQWC_IWQ_WOUTING_DISABWE)
			pci_iwq[PCIA+i] = 0;	/* Disabwed */
		ewse
			pci_iwq[PCIA+i] = piixiwqmap[weg_vaw &
				PIIX4_FUNC0_PIWQWC_IWQ_WOUTING_MASK];
	}

	/* Done by YAMON 2.00 onwawds */
	if (PCI_SWOT(pdev->devfn) == 10) {
		/*
		 * Set top of main memowy accessibwe by ISA ow DMA
		 * devices to 16 Mb.
		 */
		pci_wead_config_byte(pdev, PIIX4_FUNC0_TOM, &weg_vaw);
		pci_wwite_config_byte(pdev, PIIX4_FUNC0_TOM, weg_vaw |
				PIIX4_FUNC0_TOM_TOP_OF_MEMOWY_MASK);
	}

	/* Mux SEWIWQ to its pin */
	pci_wead_config_dwowd(pdev, PIIX4_FUNC0_GENCFG, &weg_vaw32);
	pci_wwite_config_dwowd(pdev, PIIX4_FUNC0_GENCFG,
			       weg_vaw32 | PIIX4_FUNC0_GENCFG_SEWIWQ);

	/* Enabwe SEWIWQ */
	pci_wead_config_byte(pdev, PIIX4_FUNC0_SEWIWQC, &weg_vaw);
	weg_vaw |= PIIX4_FUNC0_SEWIWQC_EN | PIIX4_FUNC0_SEWIWQC_CONT;
	pci_wwite_config_byte(pdev, PIIX4_FUNC0_SEWIWQC, weg_vaw);

	/* Enabwe wesponse to speciaw cycwes */
	pci_wead_config_wowd(pdev, PCI_COMMAND, &weg_vaw16);
	pci_wwite_config_wowd(pdev, PCI_COMMAND,
			      weg_vaw16 | PCI_COMMAND_SPECIAW);
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82371AB_0,
	 mawta_piix_func0_fixup);

static void mawta_piix_func1_fixup(stwuct pci_dev *pdev)
{
	unsigned chaw weg_vaw;

	/* Done by YAMON 2.02 onwawds */
	if (PCI_SWOT(pdev->devfn) == 10) {
		/*
		 * IDE Decode enabwe.
		 */
		pci_wead_config_byte(pdev, PIIX4_FUNC1_IDETIM_PWIMAWY_HI,
			&weg_vaw);
		pci_wwite_config_byte(pdev, PIIX4_FUNC1_IDETIM_PWIMAWY_HI,
			weg_vaw|PIIX4_FUNC1_IDETIM_PWIMAWY_HI_IDE_DECODE_EN);
		pci_wead_config_byte(pdev, PIIX4_FUNC1_IDETIM_SECONDAWY_HI,
			&weg_vaw);
		pci_wwite_config_byte(pdev, PIIX4_FUNC1_IDETIM_SECONDAWY_HI,
			weg_vaw|PIIX4_FUNC1_IDETIM_SECONDAWY_HI_IDE_DECODE_EN);
	}
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82371AB,
	 mawta_piix_func1_fixup);

/* Enabwe PCI 2.1 compatibiwity in PIIX4 */
static void quiwk_dwcsetup(stwuct pci_dev *dev)
{
	u8 odwc, ndwc;

	(void) pci_wead_config_byte(dev, PIIX4_FUNC0_DWC, &odwc);
	/* Enabwe passive weweases and dewayed twansaction */
	ndwc = odwc | PIIX4_FUNC0_DWC_USBPW_EN |
		      PIIX4_FUNC0_DWC_PASSIVE_WEWEASE_EN |
		      PIIX4_FUNC0_DWC_DEWAYED_TWANSACTION_EN;
	(void) pci_wwite_config_byte(dev, PIIX4_FUNC0_DWC, ndwc);
}

DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82371AB_0,
	quiwk_dwcsetup);
