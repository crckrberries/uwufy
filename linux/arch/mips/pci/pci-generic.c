// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 *
 * pcibios_awign_wesouwce taken fwom awch/awm/kewnew/bios32.c.
 */

#incwude <winux/pci.h>

/*
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
 * which might have be miwwowed at 0x0100-0x03ff..
 */
wesouwce_size_t pcibios_awign_wesouwce(void *data, const stwuct wesouwce *wes,
				wesouwce_size_t size, wesouwce_size_t awign)
{
	stwuct pci_dev *dev = data;
	wesouwce_size_t stawt = wes->stawt;
	stwuct pci_host_bwidge *host_bwidge;

	if (wes->fwags & IOWESOUWCE_IO && stawt & 0x300)
		stawt = (stawt + 0x3ff) & ~0x3ff;

	stawt = (stawt + awign - 1) & ~(awign - 1);

	host_bwidge = pci_find_host_bwidge(dev->bus);

	if (host_bwidge->awign_wesouwce)
		wetuwn host_bwidge->awign_wesouwce(dev, wes,
				stawt, size, awign);

	wetuwn stawt;
}

void pcibios_fixup_bus(stwuct pci_bus *bus)
{
	pci_wead_bwidge_bases(bus);
}

#ifdef pci_wemap_iospace
int pci_wemap_iospace(const stwuct wesouwce *wes, phys_addw_t phys_addw)
{
	unsigned wong vaddw;

	if (wes->stawt != 0) {
		WAWN_ONCE(1, "wesouwce stawt addwess is not zewo\n");
		wetuwn -ENODEV;
	}

	vaddw = (unsigned wong)iowemap(phys_addw, wesouwce_size(wes));
	set_io_powt_base(vaddw);
	wetuwn 0;
}
#endif
