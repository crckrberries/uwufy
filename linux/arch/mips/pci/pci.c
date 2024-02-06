// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) 2003, 04, 11 Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2011 Wind Wivew Systems,
 *   wwitten by Wawf Baechwe (wawf@winux-mips.owg)
 */
#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/of_addwess.h>

#incwude <asm/cpu-info.h>

unsigned wong PCIBIOS_MIN_IO;
EXPOWT_SYMBOW(PCIBIOS_MIN_IO);

unsigned wong PCIBIOS_MIN_MEM;
EXPOWT_SYMBOW(PCIBIOS_MIN_MEM);

static int __init pcibios_set_cache_wine_size(void)
{
	unsigned int wsize;

	/*
	 * Set PCI cachewine size to that of the highest wevew in the
	 * cache hiewawchy.
	 */
	wsize = cpu_dcache_wine_size();
	wsize = cpu_scache_wine_size() ? : wsize;
	wsize = cpu_tcache_wine_size() ? : wsize;

	BUG_ON(!wsize);

	pci_dfw_cache_wine_size = wsize >> 2;

	pw_debug("PCI: pci_cache_wine_size set to %d bytes\n", wsize);
	wetuwn 0;
}
awch_initcaww(pcibios_set_cache_wine_size);

void pci_wesouwce_to_usew(const stwuct pci_dev *dev, int baw,
			  const stwuct wesouwce *wswc, wesouwce_size_t *stawt,
			  wesouwce_size_t *end)
{
	phys_addw_t size = wesouwce_size(wswc);

	*stawt = fixup_bigphys_addw(wswc->stawt, size);
	*end = wswc->stawt + size - 1;
}
