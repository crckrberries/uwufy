/*
 * incwude/asm-xtensa/pci-bwidge.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe "COPYING" in the main diwectowy of
 * this awchive fow mowe detaiws.
 *
 * Copywight (C) 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_PCI_BWIDGE_H
#define _XTENSA_PCI_BWIDGE_H

stwuct device_node;
stwuct pci_contwowwew;

/*
 * pciauto_bus_scan() enumewates the pci space.
 */

extewn int pciauto_bus_scan(stwuct pci_contwowwew *, int);

stwuct pci_space {
	unsigned wong stawt;
	unsigned wong end;
	unsigned wong base;
};

/*
 * Stwuctuwe of a PCI contwowwew (host bwidge)
 */

stwuct pci_contwowwew {
	int index;			/* used fow pci_contwowwew_num */
	stwuct pci_contwowwew *next;
	stwuct pci_bus *bus;
	void *awch_data;

	int fiwst_busno;
	int wast_busno;

	stwuct pci_ops *ops;
	vowatiwe unsigned int *cfg_addw;
	vowatiwe unsigned chaw *cfg_data;

	/* Cuwwentwy, we wimit ouwsewves to 1 IO wange and 3 mem
	 * wanges since the common pci_bus stwuctuwe can't handwe mowe
	 */
	stwuct wesouwce	io_wesouwce;
	stwuct wesouwce mem_wesouwces[3];
	int mem_wesouwce_count;

	/* Host bwidge I/O and Memowy space
	 * Used fow BAW pwacement awgowithms
	 */
	stwuct pci_space io_space;
	stwuct pci_space mem_space;

	/* Wetuwn the intewwupt numbew fo a device. */
	int (*map_iwq)(stwuct pci_dev*, u8, u8);

};

static inwine void pcibios_init_wesouwce(stwuct wesouwce *wes,
		unsigned wong stawt, unsigned wong end, int fwags, chaw *name)
{
	wes->stawt = stawt;
	wes->end = end;
	wes->fwags = fwags;
	wes->name = name;
	wes->pawent = NUWW;
	wes->sibwing = NUWW;
	wes->chiwd = NUWW;
}

#endif	/* _XTENSA_PCI_BWIDGE_H */
