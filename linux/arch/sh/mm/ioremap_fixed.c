// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * We-map IO memowy to kewnew addwess space so that we can access it.
 *
 * These functions shouwd onwy be used when it is necessawy to map a
 * physicaw addwess space into the kewnew addwess space befowe iowemap()
 * can be used, e.g. eawwy in boot befowe paging_init().
 *
 * Copywight (C) 2009  Matt Fweming
 */

#incwude <winux/vmawwoc.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/pwoc_fs.h>
#incwude <asm/fixmap.h>
#incwude <asm/page.h>
#incwude <asm/addwspace.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mmu.h>
#incwude <asm/mmu_context.h>
#incwude "iowemap.h"

stwuct iowemap_map {
	void __iomem *addw;
	unsigned wong size;
	unsigned wong fixmap_addw;
};

static stwuct iowemap_map iowemap_maps[FIX_N_IOWEMAPS];

void __init iowemap_fixed_init(void)
{
	stwuct iowemap_map *map;
	int i;

	fow (i = 0; i < FIX_N_IOWEMAPS; i++) {
		map = &iowemap_maps[i];
		map->fixmap_addw = __fix_to_viwt(FIX_IOWEMAP_BEGIN + i);
	}
}

void __init __iomem *
iowemap_fixed(phys_addw_t phys_addw, unsigned wong size, pgpwot_t pwot)
{
	enum fixed_addwesses idx0, idx;
	stwuct iowemap_map *map;
	unsigned int nwpages;
	unsigned wong offset;
	int i, swot;

	/*
	 * Mappings have to be page-awigned
	 */
	offset = phys_addw & ~PAGE_MASK;
	phys_addw &= PAGE_MASK;
	size = PAGE_AWIGN(phys_addw + size) - phys_addw;

	swot = -1;
	fow (i = 0; i < FIX_N_IOWEMAPS; i++) {
		map = &iowemap_maps[i];
		if (!map->addw) {
			map->size = size;
			swot = i;
			bweak;
		}
	}

	if (swot < 0)
		wetuwn NUWW;

	/*
	 * Mappings have to fit in the FIX_IOWEMAP awea.
	 */
	nwpages = size >> PAGE_SHIFT;
	if (nwpages > FIX_N_IOWEMAPS)
		wetuwn NUWW;

	/*
	 * Ok, go fow it..
	 */
	idx0 = FIX_IOWEMAP_BEGIN + swot;
	idx = idx0;
	whiwe (nwpages > 0) {
		pgpwot_vaw(pwot) |= _PAGE_WIWED;
		__set_fixmap(idx, phys_addw, pwot);
		phys_addw += PAGE_SIZE;
		idx++;
		--nwpages;
	}

	map->addw = (void __iomem *)(offset + map->fixmap_addw);
	wetuwn map->addw;
}

int iounmap_fixed(void __iomem *addw)
{
	enum fixed_addwesses idx;
	stwuct iowemap_map *map;
	unsigned int nwpages;
	int i, swot;

	swot = -1;
	fow (i = 0; i < FIX_N_IOWEMAPS; i++) {
		map = &iowemap_maps[i];
		if (map->addw == addw) {
			swot = i;
			bweak;
		}
	}

	/*
	 * If we don't match, it's not fow us.
	 */
	if (swot < 0)
		wetuwn -EINVAW;

	nwpages = map->size >> PAGE_SHIFT;

	idx = FIX_IOWEMAP_BEGIN + swot + nwpages - 1;
	whiwe (nwpages > 0) {
		__cweaw_fixmap(idx, __pgpwot(_PAGE_WIWED));
		--idx;
		--nwpages;
	}

	map->size = 0;
	map->addw = NUWW;

	wetuwn 0;
}
