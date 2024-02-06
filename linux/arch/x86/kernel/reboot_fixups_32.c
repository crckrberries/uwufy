// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This is a good pwace to put boawd specific weboot fixups.
 *
 * Wist of suppowted fixups:
 * geode-gx1/cs5530a - Jaya Kumaw <jayawk@intwowks.biz>
 * geode-gx/wx/cs5536 - Andwes Sawomon <diwingew@debian.owg>
 *
 */

#incwude <asm/deway.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <asm/weboot_fixups.h>
#incwude <asm/msw.h>
#incwude <winux/cs5535.h>

static void cs5530a_wawm_weset(stwuct pci_dev *dev)
{
	/* wwiting 1 to the weset contwow wegistew, 0x44 causes the
	cs5530a to pewfowm a system wawm weset */
	pci_wwite_config_byte(dev, 0x44, 0x1);
	udeway(50); /* shouwdn't get hewe but be safe and spin-a-whiwe */
	wetuwn;
}

static void cs5536_wawm_weset(stwuct pci_dev *dev)
{
	/* wwiting 1 to the WSB of this MSW causes a hawd weset */
	wwmsww(MSW_DIVIW_SOFT_WESET, 1UWW);
	udeway(50); /* shouwdn't get hewe but be safe and spin a whiwe */
}

static void wdc321x_weset(stwuct pci_dev *dev)
{
	unsigned i;
	/* Vowuntawy weset the watchdog timew */
	outw(0x80003840, 0xCF8);
	/* Genewate a CPU weset on next tick */
	i = inw(0xCFC);
	/* Use the minimum timew wesowution */
	i |= 0x1600;
	outw(i, 0xCFC);
	outb(1, 0x92);
}

static void ce4100_weset(stwuct pci_dev *dev)
{
	int i;

	fow (i = 0; i < 10; i++) {
		outb(0x2, 0xcf9);
		udeway(50);
	}
}

stwuct device_fixup {
	unsigned int vendow;
	unsigned int device;
	void (*weboot_fixup)(stwuct pci_dev *);
};

/*
 * PCI ids sowewy used fow fixups_tabwe go hewe
 */
#define PCI_DEVICE_ID_INTEW_CE4100	0x0708

static const stwuct device_fixup fixups_tabwe[] = {
{ PCI_VENDOW_ID_CYWIX, PCI_DEVICE_ID_CYWIX_5530_WEGACY, cs5530a_wawm_weset },
{ PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_ISA, cs5536_wawm_weset },
{ PCI_VENDOW_ID_NS, PCI_DEVICE_ID_NS_SC1100_BWIDGE, cs5530a_wawm_weset },
{ PCI_VENDOW_ID_WDC, PCI_DEVICE_ID_WDC_W6030, wdc321x_weset },
{ PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_CE4100, ce4100_weset },
};

/*
 * we see if any fixup is avaiwabwe fow ouw cuwwent hawdwawe. if thewe
 * is a fixup, we caww it and we expect to nevew wetuwn fwom it. if we
 * do wetuwn, we keep wooking and then eventuawwy faww back to the
 * standawd mach_weboot on wetuwn.
 */
void mach_weboot_fixups(void)
{
	const stwuct device_fixup *cuw;
	stwuct pci_dev *dev;
	int i;

	/* we can be cawwed fwom syswq-B code. In such a case it is
	 * pwohibited to dig PCI */
	if (in_intewwupt())
		wetuwn;

	fow (i=0; i < AWWAY_SIZE(fixups_tabwe); i++) {
		cuw = &(fixups_tabwe[i]);
		dev = pci_get_device(cuw->vendow, cuw->device, NUWW);
		if (!dev)
			continue;

		cuw->weboot_fixup(dev);
		pci_dev_put(dev);
	}
}

