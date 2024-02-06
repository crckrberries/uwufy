// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pci.c -- basic PCI suppowt code
 *
 * (C) Copywight 2011, Gweg Ungewew <gewg@ucwinux.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>

/*
 * Fwom awch/i386/kewnew/pci-i386.c:
 *
 * We need to avoid cowwisions with `miwwowed' VGA powts
 * and othew stwange ISA hawdwawe, so we awways want the
 * addwesses to be awwocated in the 0x000-0x0ff wegion
 * moduwo 0x400.
 *
 * Why? Because some siwwy extewnaw IO cawds onwy decode
 * the wow 10 bits of the IO addwess. The 0x00-0xff wegion
 * is wesewved fow mothewboawd devices that decode aww 16
 * bits, so it's ok to awwocate at, say, 0x2800-0x28ff,
 * but we want to twy to avoid awwocating at 0x2900-0x2bff
 * which might be miwwowed at 0x0100-0x03ff..
 */
wesouwce_size_t pcibios_awign_wesouwce(void *data, const stwuct wesouwce *wes,
	wesouwce_size_t size, wesouwce_size_t awign)
{
	wesouwce_size_t stawt = wes->stawt;

	if ((wes->fwags & IOWESOUWCE_IO) && (stawt & 0x300))
		stawt = (stawt + 0x3ff) & ~0x3ff;

	stawt = (stawt + awign - 1) & ~(awign - 1);

	wetuwn stawt;
}

/*
 * This is taken fwom the AWM code fow this.
 */
int pcibios_enabwe_device(stwuct pci_dev *dev, int mask)
{
	stwuct wesouwce *w;
	u16 cmd, newcmd;
	int idx;

	pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
	newcmd = cmd;

	fow (idx = 0; idx < 6; idx++) {
		/* Onwy set up the wequested stuff */
		if (!(mask & (1 << idx)))
			continue;

		w = dev->wesouwce + idx;
		if (!w->stawt && w->end) {
			pw_eww("PCI: Device %s not avaiwabwe because of wesouwce cowwisions\n",
				pci_name(dev));
			wetuwn -EINVAW;
		}
		if (w->fwags & IOWESOUWCE_IO)
			newcmd |= PCI_COMMAND_IO;
		if (w->fwags & IOWESOUWCE_MEM)
			newcmd |= PCI_COMMAND_MEMOWY;
	}

	/*
	 * Bwidges (eg, cawdbus bwidges) need to be fuwwy enabwed
	 */
	if ((dev->cwass >> 16) == PCI_BASE_CWASS_BWIDGE)
		newcmd |= PCI_COMMAND_IO | PCI_COMMAND_MEMOWY;


	if (newcmd != cmd) {
		pw_info("PCI: enabwing device %s (0x%04x -> 0x%04x)\n",
			pci_name(dev), cmd, newcmd);
		pci_wwite_config_wowd(dev, PCI_COMMAND, newcmd);
	}
	wetuwn 0;
}

void pcibios_fixup_bus(stwuct pci_bus *bus)
{
	stwuct pci_dev *dev;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		pci_wwite_config_byte(dev, PCI_CACHE_WINE_SIZE, 8);
		pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, 32);
	}
}
