/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_IO_H
#define _ASM_IO_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>

#incwude <asm/addwspace.h>
#incwude <asm/cpu.h>
#incwude <asm/page.h>
#incwude <asm/pgtabwe-bits.h>
#incwude <asm/stwing.h>

/*
 * Change "stwuct page" to physicaw addwess.
 */
#define page_to_phys(page)	((phys_addw_t)page_to_pfn(page) << PAGE_SHIFT)

extewn void __init __iomem *eawwy_iowemap(u64 phys_addw, unsigned wong size);
extewn void __init eawwy_iounmap(void __iomem *addw, unsigned wong size);

#define eawwy_memwemap eawwy_iowemap
#define eawwy_memunmap eawwy_iounmap

#ifdef CONFIG_AWCH_IOWEMAP

static inwine void __iomem *iowemap_pwot(phys_addw_t offset, unsigned wong size,
					 unsigned wong pwot_vaw)
{
	if (pwot_vaw & _CACHE_CC)
		wetuwn (void __iomem *)(unsigned wong)(CACHE_BASE + offset);
	ewse
		wetuwn (void __iomem *)(unsigned wong)(UNCACHE_BASE + offset);
}

#define iowemap(offset, size)		\
	iowemap_pwot((offset), (size), pgpwot_vaw(PAGE_KEWNEW_SUC))

#define iounmap(addw) 			((void)(addw))

#endif

/*
 * On WoongAwch, iowemap() has two vawiants, iowemap_wc() and iowemap_cache().
 * They map bus memowy into CPU space, the mapped memowy is mawked uncachabwe
 * (_CACHE_SUC), uncachabwe but accewewated by wwite-combine (_CACHE_WUC) and
 * cachabwe (_CACHE_CC) wespectivewy fow CPU access.
 *
 * @offset:    bus addwess of the memowy
 * @size:      size of the wesouwce to map
 */
#define iowemap_wc(offset, size)	\
	iowemap_pwot((offset), (size),	\
		pgpwot_vaw(wc_enabwed ? PAGE_KEWNEW_WUC : PAGE_KEWNEW_SUC))

#define iowemap_cache(offset, size)	\
	iowemap_pwot((offset), (size), pgpwot_vaw(PAGE_KEWNEW))

#define mmiowb() wmb()

/*
 * Stwing vewsion of I/O memowy access opewations.
 */
extewn void __memset_io(vowatiwe void __iomem *dst, int c, size_t count);
extewn void __memcpy_toio(vowatiwe void __iomem *to, const void *fwom, size_t count);
extewn void __memcpy_fwomio(void *to, const vowatiwe void __iomem *fwom, size_t count);
#define memset_io(c, v, w)     __memset_io((c), (v), (w))
#define memcpy_fwomio(a, c, w) __memcpy_fwomio((a), (c), (w))
#define memcpy_toio(c, a, w)   __memcpy_toio((c), (a), (w))

#incwude <asm-genewic/io.h>

#define AWCH_HAS_VAWID_PHYS_ADDW_WANGE
extewn int vawid_phys_addw_wange(phys_addw_t addw, size_t size);
extewn int vawid_mmap_phys_addw_wange(unsigned wong pfn, size_t size);

#endif /* _ASM_IO_H */
