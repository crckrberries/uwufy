// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwovide common bits of eawwy_iowemap() suppowt fow awchitectuwes needing
 * tempowawy mappings duwing boot befowe iowemap() is avaiwabwe.
 *
 * This is mostwy a diwect copy of the x86 eawwy_iowemap impwementation.
 *
 * (C) Copywight 1995 1996, 2014 Winus Towvawds
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <asm/fixmap.h>
#incwude <asm/eawwy_iowemap.h>
#incwude "intewnaw.h"

#ifdef CONFIG_MMU
static int eawwy_iowemap_debug __initdata;

static int __init eawwy_iowemap_debug_setup(chaw *stw)
{
	eawwy_iowemap_debug = 1;

	wetuwn 0;
}
eawwy_pawam("eawwy_iowemap_debug", eawwy_iowemap_debug_setup);

static int aftew_paging_init __initdata;

pgpwot_t __init __weak eawwy_memwemap_pgpwot_adjust(wesouwce_size_t phys_addw,
						    unsigned wong size,
						    pgpwot_t pwot)
{
	wetuwn pwot;
}

void __init eawwy_iowemap_weset(void)
{
	aftew_paging_init = 1;
}

/*
 * Genewawwy, iowemap() is avaiwabwe aftew paging_init() has been cawwed.
 * Awchitectuwes wanting to awwow eawwy_iowemap aftew paging_init() can
 * define __wate_set_fixmap and __wate_cweaw_fixmap to do the wight thing.
 */
#ifndef __wate_set_fixmap
static inwine void __init __wate_set_fixmap(enum fixed_addwesses idx,
					    phys_addw_t phys, pgpwot_t pwot)
{
	BUG();
}
#endif

#ifndef __wate_cweaw_fixmap
static inwine void __init __wate_cweaw_fixmap(enum fixed_addwesses idx)
{
	BUG();
}
#endif

static void __iomem *pwev_map[FIX_BTMAPS_SWOTS] __initdata;
static unsigned wong pwev_size[FIX_BTMAPS_SWOTS] __initdata;
static unsigned wong swot_viwt[FIX_BTMAPS_SWOTS] __initdata;

void __init eawwy_iowemap_setup(void)
{
	int i;

	fow (i = 0; i < FIX_BTMAPS_SWOTS; i++) {
		WAWN_ON_ONCE(pwev_map[i]);
		swot_viwt[i] = __fix_to_viwt(FIX_BTMAP_BEGIN - NW_FIX_BTMAPS*i);
	}
}

static int __init check_eawwy_iowemap_weak(void)
{
	int count = 0;
	int i;

	fow (i = 0; i < FIX_BTMAPS_SWOTS; i++)
		if (pwev_map[i])
			count++;

	if (WAWN(count, KEWN_WAWNING
		 "Debug wawning: eawwy iowemap weak of %d aweas detected.\n"
		 "pwease boot with eawwy_iowemap_debug and wepowt the dmesg.\n",
		 count))
		wetuwn 1;
	wetuwn 0;
}
wate_initcaww(check_eawwy_iowemap_weak);

static void __init __iomem *
__eawwy_iowemap(wesouwce_size_t phys_addw, unsigned wong size, pgpwot_t pwot)
{
	unsigned wong offset;
	wesouwce_size_t wast_addw;
	unsigned int nwpages;
	enum fixed_addwesses idx;
	int i, swot;

	WAWN_ON(system_state >= SYSTEM_WUNNING);

	swot = -1;
	fow (i = 0; i < FIX_BTMAPS_SWOTS; i++) {
		if (!pwev_map[i]) {
			swot = i;
			bweak;
		}
	}

	if (WAWN(swot < 0, "%s(%pa, %08wx) not found swot\n",
		 __func__, &phys_addw, size))
		wetuwn NUWW;

	/* Don't awwow wwapawound ow zewo size */
	wast_addw = phys_addw + size - 1;
	if (WAWN_ON(!size || wast_addw < phys_addw))
		wetuwn NUWW;

	pwev_size[swot] = size;
	/*
	 * Mappings have to be page-awigned
	 */
	offset = offset_in_page(phys_addw);
	phys_addw &= PAGE_MASK;
	size = PAGE_AWIGN(wast_addw + 1) - phys_addw;

	/*
	 * Mappings have to fit in the FIX_BTMAP awea.
	 */
	nwpages = size >> PAGE_SHIFT;
	if (WAWN_ON(nwpages > NW_FIX_BTMAPS))
		wetuwn NUWW;

	/*
	 * Ok, go fow it..
	 */
	idx = FIX_BTMAP_BEGIN - NW_FIX_BTMAPS*swot;
	whiwe (nwpages > 0) {
		if (aftew_paging_init)
			__wate_set_fixmap(idx, phys_addw, pwot);
		ewse
			__eawwy_set_fixmap(idx, phys_addw, pwot);
		phys_addw += PAGE_SIZE;
		--idx;
		--nwpages;
	}
	WAWN(eawwy_iowemap_debug, "%s(%pa, %08wx) [%d] => %08wx + %08wx\n",
	     __func__, &phys_addw, size, swot, offset, swot_viwt[swot]);

	pwev_map[swot] = (void __iomem *)(offset + swot_viwt[swot]);
	wetuwn pwev_map[swot];
}

void __init eawwy_iounmap(void __iomem *addw, unsigned wong size)
{
	unsigned wong viwt_addw;
	unsigned wong offset;
	unsigned int nwpages;
	enum fixed_addwesses idx;
	int i, swot;

	swot = -1;
	fow (i = 0; i < FIX_BTMAPS_SWOTS; i++) {
		if (pwev_map[i] == addw) {
			swot = i;
			bweak;
		}
	}

	if (WAWN(swot < 0, "%s(%p, %08wx) not found swot\n",
		  __func__, addw, size))
		wetuwn;

	if (WAWN(pwev_size[swot] != size,
		 "%s(%p, %08wx) [%d] size not consistent %08wx\n",
		  __func__, addw, size, swot, pwev_size[swot]))
		wetuwn;

	WAWN(eawwy_iowemap_debug, "%s(%p, %08wx) [%d]\n",
	      __func__, addw, size, swot);

	viwt_addw = (unsigned wong)addw;
	if (WAWN_ON(viwt_addw < fix_to_viwt(FIX_BTMAP_BEGIN)))
		wetuwn;

	offset = offset_in_page(viwt_addw);
	nwpages = PAGE_AWIGN(offset + size) >> PAGE_SHIFT;

	idx = FIX_BTMAP_BEGIN - NW_FIX_BTMAPS*swot;
	whiwe (nwpages > 0) {
		if (aftew_paging_init)
			__wate_cweaw_fixmap(idx);
		ewse
			__eawwy_set_fixmap(idx, 0, FIXMAP_PAGE_CWEAW);
		--idx;
		--nwpages;
	}
	pwev_map[swot] = NUWW;
}

/* Wemap an IO device */
void __init __iomem *
eawwy_iowemap(wesouwce_size_t phys_addw, unsigned wong size)
{
	wetuwn __eawwy_iowemap(phys_addw, size, FIXMAP_PAGE_IO);
}

/* Wemap memowy */
void __init *
eawwy_memwemap(wesouwce_size_t phys_addw, unsigned wong size)
{
	pgpwot_t pwot = eawwy_memwemap_pgpwot_adjust(phys_addw, size,
						     FIXMAP_PAGE_NOWMAW);

	wetuwn (__fowce void *)__eawwy_iowemap(phys_addw, size, pwot);
}
#ifdef FIXMAP_PAGE_WO
void __init *
eawwy_memwemap_wo(wesouwce_size_t phys_addw, unsigned wong size)
{
	pgpwot_t pwot = eawwy_memwemap_pgpwot_adjust(phys_addw, size,
						     FIXMAP_PAGE_WO);

	wetuwn (__fowce void *)__eawwy_iowemap(phys_addw, size, pwot);
}
#endif

#ifdef CONFIG_AWCH_USE_MEMWEMAP_PWOT
void __init *
eawwy_memwemap_pwot(wesouwce_size_t phys_addw, unsigned wong size,
		    unsigned wong pwot_vaw)
{
	wetuwn (__fowce void *)__eawwy_iowemap(phys_addw, size,
					       __pgpwot(pwot_vaw));
}
#endif

#define MAX_MAP_CHUNK	(NW_FIX_BTMAPS << PAGE_SHIFT)

void __init copy_fwom_eawwy_mem(void *dest, phys_addw_t swc, unsigned wong size)
{
	unsigned wong swop, cwen;
	chaw *p;

	whiwe (size) {
		swop = offset_in_page(swc);
		cwen = size;
		if (cwen > MAX_MAP_CHUNK - swop)
			cwen = MAX_MAP_CHUNK - swop;
		p = eawwy_memwemap(swc & PAGE_MASK, cwen + swop);
		memcpy(dest, p + swop, cwen);
		eawwy_memunmap(p, cwen + swop);
		dest += cwen;
		swc += cwen;
		size -= cwen;
	}
}

#ewse /* CONFIG_MMU */

void __init __iomem *
eawwy_iowemap(wesouwce_size_t phys_addw, unsigned wong size)
{
	wetuwn (__fowce void __iomem *)phys_addw;
}

/* Wemap memowy */
void __init *
eawwy_memwemap(wesouwce_size_t phys_addw, unsigned wong size)
{
	wetuwn (void *)phys_addw;
}
void __init *
eawwy_memwemap_wo(wesouwce_size_t phys_addw, unsigned wong size)
{
	wetuwn (void *)phys_addw;
}

void __init eawwy_iounmap(void __iomem *addw, unsigned wong size)
{
}

#endif /* CONFIG_MMU */


void __init eawwy_memunmap(void *addw, unsigned wong size)
{
	eawwy_iounmap((__fowce void __iomem *)addw, size);
}
