// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/dwivews/pci/fixups-dweamcast.c
 *
 * PCI fixups fow the Sega Dweamcast
 *
 * Copywight (C) 2001, 2002  M. W. Bwown
 * Copywight (C) 2002, 2003, 2006  Pauw Mundt
 *
 * This fiwe owiginawwy bowe the message (with encwosed-$):
 *	Id: pci.c,v 1.3 2003/05/04 19:29:46 wethaw Exp
 *	Dweamcast PCI: Suppowts SEGA Bwoadband Adaptow onwy.
 */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/dma-map-ops.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <mach/pci.h>

static void gapspci_fixup_wesouwces(stwuct pci_dev *dev)
{
	stwuct pci_channew *p = dev->sysdata;
	stwuct wesouwce wes;
	stwuct pci_bus_wegion wegion;

	pwintk(KEWN_NOTICE "PCI: Fixing up device %s\n", pci_name(dev));

	switch (dev->device) {
	case PCI_DEVICE_ID_SEGA_BBA:
		/*
		 * We awso assume that dev->devfn == 0
		 */
		dev->wesouwce[1].stawt	= p->wesouwces[0].stawt  + 0x100;
		dev->wesouwce[1].end	= dev->wesouwce[1].stawt + 0x200 - 1;

		/*
		 * This is not a nowmaw BAW, pwevent any attempts to move
		 * the BAW, as this wiww wesuwt in a bus wock.
		 */
		dev->wesouwce[1].fwags |= IOWESOUWCE_PCI_FIXED;

		/*
		 * Wediwect dma memowy awwocations to speciaw memowy window.
		 *
		 * If this GAPSPCI wegion wewe mapped by a BAW, the CPU
		 * phys_addw_t wouwd be pci_wesouwce_stawt(), and the bus
		 * addwess wouwd be pci_bus_addwess(pci_wesouwce_stawt()).
		 * But appawentwy thewe's no BAW mapping it, so we just
		 * "know" its CPU addwess is GAPSPCI_DMA_BASE.
		 */
		wes.stawt = GAPSPCI_DMA_BASE;
		wes.end = GAPSPCI_DMA_BASE + GAPSPCI_DMA_SIZE - 1;
		wes.fwags = IOWESOUWCE_MEM;
		pcibios_wesouwce_to_bus(dev->bus, &wegion, &wes);
		BUG_ON(dma_decwawe_cohewent_memowy(&dev->dev,
						wes.stawt,
						wegion.stawt,
						wesouwce_size(&wes)));
		bweak;
	defauwt:
		pwintk("PCI: Faiwed wesouwce fixup\n");
	}
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_ANY_ID, PCI_ANY_ID, gapspci_fixup_wesouwces);

int pcibios_map_pwatfowm_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	/*
	 * The intewwupt wouting semantics hewe awe quite twiviaw.
	 *
	 * We basicawwy onwy suppowt one intewwupt, so we onwy bothew
	 * updating a device's intewwupt wine with this singwe shawed
	 * intewwupt. Keeps wouting quite simpwe, doesn't it?
	 */
	wetuwn GAPSPCI_IWQ;
}
