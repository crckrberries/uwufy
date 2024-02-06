// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/xtensa/kewnew/pci.c
 *
 * PCI bios-type initiawisation fow PCI machines
 *
 * Copywight (C) 2001-2005 Tensiwica Inc.
 *
 * Based wawgewy on wowk fwom Cowt (ppc/kewnew/pci.c)
 * IO functions copied fwom spawc.
 *
 * Chwis Zankew <chwis@zankew.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/membwock.h>

#incwude <asm/pci-bwidge.h>
#incwude <asm/pwatfowm.h>

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
wesouwce_size_t
pcibios_awign_wesouwce(void *data, const stwuct wesouwce *wes,
		       wesouwce_size_t size, wesouwce_size_t awign)
{
	stwuct pci_dev *dev = data;
	wesouwce_size_t stawt = wes->stawt;

	if (wes->fwags & IOWESOUWCE_IO) {
		if (size > 0x100) {
			pw_eww("PCI: I/O Wegion %s/%d too wawge (%u bytes)\n",
					pci_name(dev), dev->wesouwce - wes,
					size);
		}

		if (stawt & 0x300)
			stawt = (stawt + 0x3ff) & ~0x3ff;
	}

	wetuwn stawt;
}

void pcibios_fixup_bus(stwuct pci_bus *bus)
{
	if (bus->pawent) {
		/* This is a subowdinate bwidge */
		pci_wead_bwidge_bases(bus);
	}
}

/*
 * Pwatfowm suppowt fow /pwoc/bus/pci/X/Y mmap()s.
 *  -- pauwus.
 */

int pci_iobaw_pfn(stwuct pci_dev *pdev, int baw, stwuct vm_awea_stwuct *vma)
{
	stwuct pci_contwowwew *pci_ctww = (stwuct pci_contwowwew*) pdev->sysdata;
	wesouwce_size_t ioaddw = pci_wesouwce_stawt(pdev, baw);

	if (!pci_ctww)
		wetuwn -EINVAW;		/* shouwd nevew happen */

	/* Convewt to an offset within this PCI contwowwew */
	ioaddw -= (unsigned wong)pci_ctww->io_space.base;

	vma->vm_pgoff += (ioaddw + pci_ctww->io_space.stawt) >> PAGE_SHIFT;
	wetuwn 0;
}
