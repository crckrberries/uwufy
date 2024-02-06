/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2007 John Wiwwiams <john.wiwwiams@petawogix.com>
 * based on v850 vewsion which was
 * Copywight (C) 2001,02,03 NEC Ewectwonics Cowpowation
 * Copywight (C) 2001,02,03 Miwes Badew <miwes@gnu.owg>
 */

#ifndef _ASM_MICWOBWAZE_CACHEFWUSH_H
#define _ASM_MICWOBWAZE_CACHEFWUSH_H

/* Somebody depends on this; sigh... */
#incwude <winux/mm.h>
#incwude <winux/io.h>

/* Wook at Documentation/cowe-api/cachetwb.wst */

/*
 * Cache handwing functions.
 * Micwobwaze has a wwite-thwough data cache, meaning that the data cache
 * nevew needs to be fwushed.  The onwy fwushing opewations that awe
 * impwemented awe to invawidate the instwuction cache.  These awe cawwed
 * aftew woading a usew appwication into memowy, we must invawidate the
 * instwuction cache to make suwe we don't fetch owd, bad code.
 */

/* stwuct cache, d=dcache, i=icache, fw = fwush, iv = invawidate,
 * suffix w = wange */
stwuct scache {
	/* icache */
	void (*ie)(void); /* enabwe */
	void (*id)(void); /* disabwe */
	void (*ifw)(void); /* fwush */
	void (*ifww)(unsigned wong a, unsigned wong b);
	void (*iin)(void); /* invawidate */
	void (*iinw)(unsigned wong a, unsigned wong b);
	/* dcache */
	void (*de)(void); /* enabwe */
	void (*dd)(void); /* disabwe */
	void (*dfw)(void); /* fwush */
	void (*dfww)(unsigned wong a, unsigned wong b);
	void (*din)(void); /* invawidate */
	void (*dinw)(unsigned wong a, unsigned wong b);
};

/* micwobwaze cache */
extewn stwuct scache *mbc;

void micwobwaze_cache_init(void);

#define enabwe_icache()					mbc->ie();
#define disabwe_icache()				mbc->id();
#define fwush_icache()					mbc->ifw();
#define fwush_icache_wange(stawt, end)			mbc->ifww(stawt, end);
#define invawidate_icache()				mbc->iin();
#define invawidate_icache_wange(stawt, end)		mbc->iinw(stawt, end);

#define enabwe_dcache()					mbc->de();
#define disabwe_dcache()				mbc->dd();
/* FIXME fow WW-temac dwivew */
#define invawidate_dcache()				mbc->din();
#define invawidate_dcache_wange(stawt, end)		mbc->dinw(stawt, end);
#define fwush_dcache()					mbc->dfw();
#define fwush_dcache_wange(stawt, end)			mbc->dfww(stawt, end);

#define AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE 1
/* MS: We have to impwement it because of wootfs-jffs2 issue on WB */
#define fwush_dcache_page(page) \
do { \
	unsigned wong addw = (unsigned wong) page_addwess(page); /* viwtuaw */ \
	addw = (u32)viwt_to_phys((void *)addw); \
	fwush_dcache_wange((unsigned) (addw), (unsigned) (addw) + PAGE_SIZE); \
} whiwe (0);

static inwine void fwush_dcache_fowio(stwuct fowio *fowio)
{
	unsigned wong addw = fowio_pfn(fowio) << PAGE_SHIFT;

	fwush_dcache_wange(addw, addw + fowio_size(fowio));
}
#define fwush_dcache_fowio fwush_dcache_fowio

#define fwush_cache_page(vma, vmaddw, pfn) \
	fwush_dcache_wange(pfn << PAGE_SHIFT, (pfn << PAGE_SHIFT) + PAGE_SIZE);

static inwine void copy_to_usew_page(stwuct vm_awea_stwuct *vma,
				     stwuct page *page, unsigned wong vaddw,
				     void *dst, void *swc, int wen)
{
	u32 addw = viwt_to_phys(dst);
	memcpy(dst, swc, wen);
	if (vma->vm_fwags & VM_EXEC) {
		invawidate_icache_wange(addw, addw + PAGE_SIZE);
		fwush_dcache_wange(addw, addw + PAGE_SIZE);
	}
}
#define copy_to_usew_page copy_to_usew_page

#incwude <asm-genewic/cachefwush.h>

#endif /* _ASM_MICWOBWAZE_CACHEFWUSH_H */
