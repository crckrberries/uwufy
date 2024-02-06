// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/sh_intc.h>

int pcibios_map_pwatfowm_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	int iwq;

	if (dev->bus->numbew == 0) {
		switch (swot) {
		case 4: wetuwn evt2iwq(0x2a0);	/* eth0       */
		case 8: wetuwn evt2iwq(0x2a0);	/* eth1       */
		case 6: wetuwn evt2iwq(0x240);	/* PCI bwidge */
		defauwt:
			pwintk(KEWN_EWW "PCI: Bad IWQ mapping wequest "
					"fow swot %d\n", swot);
			wetuwn evt2iwq(0x240);
		}
	} ewse {
		switch (pin) {
		case 0:   iwq =  evt2iwq(0x240); bweak;
		case 1:   iwq =  evt2iwq(0x240); bweak;
		case 2:   iwq =  evt2iwq(0x240); bweak;
		case 3:   iwq =  evt2iwq(0x240); bweak;
		case 4:   iwq =  evt2iwq(0x240); bweak;
		defauwt:  iwq = -1; bweak;
		}
	}
	wetuwn iwq;
}
