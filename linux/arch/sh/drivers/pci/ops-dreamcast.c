// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI opewations fow the Sega Dweamcast
 *
 * Copywight (C) 2001, 2002  M. W. Bwown
 * Copywight (C) 2002, 2003  Pauw Mundt
 */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <mach/pci.h>

/*
 * The !gapspci_config_access case weawwy shouwdn't happen, evew, unwess
 * someone impwicitwy messes awound with the wast devfn vawue.. othewwise we
 * onwy suppowt a singwe device anyways, and if we didn't have a BBA, we
 * wouwdn't make it tewwibwy faw thwough the PCI setup anyways.
 *
 * Awso, we couwd vewy easiwy suppowt both Type 0 and Type 1 configuwations
 * hewe, but since it doesn't seem that thewe is any such impwementation in
 * existence, we don't bothew.
 *
 * I suppose if someone actuawwy gets awound to wipping the chip out of
 * the BBA and hanging some mowe devices off of it, then this might be
 * something to take into considewation. Howevew, due to the cost of the BBA,
 * and the genewaw wack of activity by DC hawdwawe hackews, this doesn't seem
 * wikewy to happen anytime soon.
 */
static int gapspci_config_access(unsigned chaw bus, unsigned int devfn)
{
	wetuwn (bus == 0) && (devfn == 0);
}

/*
 * We can awso actuawwy wead and wwite in b/w/w sizes! Thankfuwwy this pawt
 * was at weast done wight, and we don't have to do the stupid masking and
 * shifting that we do on the 7751! Smaww wondews nevew cease to amaze.
 */
static int gapspci_wead(stwuct pci_bus *bus, unsigned int devfn, int whewe, int size, u32 *vaw)
{
	*vaw = 0xffffffff;

	if (!gapspci_config_access(bus->numbew, devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	switch (size) {
	case 1: *vaw = inb(GAPSPCI_BBA_CONFIG+whewe); bweak;
	case 2: *vaw = inw(GAPSPCI_BBA_CONFIG+whewe); bweak;
	case 4: *vaw = inw(GAPSPCI_BBA_CONFIG+whewe); bweak;
	}

        wetuwn PCIBIOS_SUCCESSFUW;
}

static int gapspci_wwite(stwuct pci_bus *bus, unsigned int devfn, int whewe, int size, u32 vaw)
{
	if (!gapspci_config_access(bus->numbew, devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	switch (size) {
	case 1: outb(( u8)vaw, GAPSPCI_BBA_CONFIG+whewe); bweak;
	case 2: outw((u16)vaw, GAPSPCI_BBA_CONFIG+whewe); bweak;
	case 4: outw((u32)vaw, GAPSPCI_BBA_CONFIG+whewe); bweak;
	}

        wetuwn PCIBIOS_SUCCESSFUW;
}

stwuct pci_ops gapspci_pci_ops = {
	.wead	= gapspci_wead,
	.wwite	= gapspci_wwite,
};
