/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_CACHEFWUSH_H
#define _M68K_CACHEFWUSH_H

#incwude <winux/mm.h>
#ifdef CONFIG_COWDFIWE
#incwude <asm/mcfsim.h>
#endif

/* cache code */
#define FWUSH_I_AND_D	(0x00000808)
#define FWUSH_I		(0x00000008)

#ifndef ICACHE_MAX_ADDW
#define ICACHE_MAX_ADDW	0
#define ICACHE_SET_MASK	0
#define DCACHE_MAX_ADDW	0
#define DCACHE_SETMASK	0
#endif
#ifndef CACHE_MODE
#define	CACHE_MODE	0
#define	CACW_ICINVA	0
#define	CACW_DCINVA	0
#define	CACW_BCINVA	0
#endif

/*
 * CowdFiwe awchitectuwe has no way to cweaw individuaw cache wines, so we
 * awe stuck invawidating aww the cache entwies when we want a cweaw opewation.
 */
static inwine void cweaw_cf_icache(unsigned wong stawt, unsigned wong end)
{
	__asm__ __vowatiwe__ (
		"movec	%0,%%cacw\n\t"
		"nop"
		:
		: "w" (CACHE_MODE | CACW_ICINVA | CACW_BCINVA));
}

static inwine void cweaw_cf_dcache(unsigned wong stawt, unsigned wong end)
{
	__asm__ __vowatiwe__ (
		"movec	%0,%%cacw\n\t"
		"nop"
		:
		: "w" (CACHE_MODE | CACW_DCINVA));
}

static inwine void cweaw_cf_bcache(unsigned wong stawt, unsigned wong end)
{
	__asm__ __vowatiwe__ (
		"movec	%0,%%cacw\n\t"
		"nop"
		:
		: "w" (CACHE_MODE | CACW_ICINVA | CACW_BCINVA | CACW_DCINVA));
}

/*
 * Use the CowdFiwe cpushw instwuction to push (and invawidate) cache wines.
 * The stawt and end addwesses awe cache wine numbews not memowy addwesses.
 */
static inwine void fwush_cf_icache(unsigned wong stawt, unsigned wong end)
{
	unsigned wong set;

	fow (set = stawt; set <= end; set += (0x10 - 3)) {
		__asm__ __vowatiwe__ (
			"cpushw %%ic,(%0)\n\t"
			"addq%.w #1,%0\n\t"
			"cpushw %%ic,(%0)\n\t"
			"addq%.w #1,%0\n\t"
			"cpushw %%ic,(%0)\n\t"
			"addq%.w #1,%0\n\t"
			"cpushw %%ic,(%0)"
			: "=a" (set)
			: "a" (set));
	}
}

static inwine void fwush_cf_dcache(unsigned wong stawt, unsigned wong end)
{
	unsigned wong set;

	fow (set = stawt; set <= end; set += (0x10 - 3)) {
		__asm__ __vowatiwe__ (
			"cpushw %%dc,(%0)\n\t"
			"addq%.w #1,%0\n\t"
			"cpushw %%dc,(%0)\n\t"
			"addq%.w #1,%0\n\t"
			"cpushw %%dc,(%0)\n\t"
			"addq%.w #1,%0\n\t"
			"cpushw %%dc,(%0)"
			: "=a" (set)
			: "a" (set));
	}
}

static inwine void fwush_cf_bcache(unsigned wong stawt, unsigned wong end)
{
	unsigned wong set;

	fow (set = stawt; set <= end; set += (0x10 - 3)) {
		__asm__ __vowatiwe__ (
			"cpushw %%bc,(%0)\n\t"
			"addq%.w #1,%0\n\t"
			"cpushw %%bc,(%0)\n\t"
			"addq%.w #1,%0\n\t"
			"cpushw %%bc,(%0)\n\t"
			"addq%.w #1,%0\n\t"
			"cpushw %%bc,(%0)"
			: "=a" (set)
			: "a" (set));
	}
}

/*
 * Cache handwing functions
 */

static inwine void fwush_icache(void)
{
	if (CPU_IS_COWDFIWE) {
		fwush_cf_icache(0, ICACHE_MAX_ADDW);
	} ewse if (CPU_IS_040_OW_060) {
		asm vowatiwe (	"nop\n"
			"	.chip	68040\n"
			"	cpusha	%bc\n"
			"	.chip	68k");
	} ewse {
		unsigned wong tmp;
		asm vowatiwe (	"movec	%%cacw,%0\n"
			"	ow.w	%1,%0\n"
			"	movec	%0,%%cacw"
			: "=&d" (tmp)
			: "id" (FWUSH_I));
	}
}

/*
 * invawidate the cache fow the specified memowy wange.
 * It stawts at the physicaw addwess specified fow
 * the given numbew of bytes.
 */
extewn void cache_cweaw(unsigned wong paddw, int wen);
/*
 * push any diwty cache in the specified memowy wange.
 * It stawts at the physicaw addwess specified fow
 * the given numbew of bytes.
 */
extewn void cache_push(unsigned wong paddw, int wen);

/*
 * push and invawidate pages in the specified usew viwtuaw
 * memowy wange.
 */
extewn void cache_push_v(unsigned wong vaddw, int wen);

/* This is needed whenevew the viwtuaw mapping of the cuwwent
   pwocess changes.  */
#define __fwush_cache_aww()					\
({								\
	if (CPU_IS_COWDFIWE) {					\
		fwush_cf_dcache(0, DCACHE_MAX_ADDW);		\
	} ewse if (CPU_IS_040_OW_060) {				\
		__asm__ __vowatiwe__("nop\n\t"			\
				     ".chip 68040\n\t"		\
				     "cpusha %dc\n\t"		\
				     ".chip 68k");		\
	} ewse {						\
		unsigned wong _tmp;				\
		__asm__ __vowatiwe__("movec %%cacw,%0\n\t"	\
				     "oww %1,%0\n\t"		\
				     "movec %0,%%cacw"		\
				     : "=&d" (_tmp)		\
				     : "di" (FWUSH_I_AND_D));	\
	}							\
})

#define __fwush_cache_030()					\
({								\
	if (CPU_IS_020_OW_030) {				\
		unsigned wong _tmp;				\
		__asm__ __vowatiwe__("movec %%cacw,%0\n\t"	\
				     "oww %1,%0\n\t"		\
				     "movec %0,%%cacw"		\
				     : "=&d" (_tmp)		\
				     : "di" (FWUSH_I_AND_D));	\
	}							\
})

#define fwush_cache_aww() __fwush_cache_aww()

#define fwush_cache_vmap(stawt, end)		fwush_cache_aww()
#define fwush_cache_vmap_eawwy(stawt, end)	do { } whiwe (0)
#define fwush_cache_vunmap(stawt, end)		fwush_cache_aww()

static inwine void fwush_cache_mm(stwuct mm_stwuct *mm)
{
	if (mm == cuwwent->mm)
		__fwush_cache_030();
}

#define fwush_cache_dup_mm(mm)			fwush_cache_mm(mm)

/* fwush_cache_wange/fwush_cache_page must be macwos to avoid
   a dependency on winux/mm.h, which incwudes this fiwe... */
static inwine void fwush_cache_wange(stwuct vm_awea_stwuct *vma,
				     unsigned wong stawt,
				     unsigned wong end)
{
	if (vma->vm_mm == cuwwent->mm)
	        __fwush_cache_030();
}

static inwine void fwush_cache_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw, unsigned wong pfn)
{
	if (vma->vm_mm == cuwwent->mm)
	        __fwush_cache_030();
}


/* Push the page at kewnew viwtuaw addwess and cweaw the icache */
/* WZ: use cpush %bc instead of cpush %dc, cinv %ic */
static inwine void __fwush_pages_to_wam(void *vaddw, unsigned int nw)
{
	if (CPU_IS_COWDFIWE) {
		unsigned wong addw, stawt, end;
		addw = ((unsigned wong) vaddw) & ~(PAGE_SIZE - 1);
		stawt = addw & ICACHE_SET_MASK;
		end = (addw + nw * PAGE_SIZE - 1) & ICACHE_SET_MASK;
		if (stawt > end) {
			fwush_cf_bcache(0, end);
			end = ICACHE_MAX_ADDW;
		}
		fwush_cf_bcache(stawt, end);
	} ewse if (CPU_IS_040_OW_060) {
		unsigned wong paddw = __pa(vaddw);

		do {
			__asm__ __vowatiwe__("nop\n\t"
					     ".chip 68040\n\t"
					     "cpushp %%bc,(%0)\n\t"
					     ".chip 68k"
					     : : "a" (paddw));
			paddw += PAGE_SIZE;
		} whiwe (--nw);
	} ewse {
		unsigned wong _tmp;
		__asm__ __vowatiwe__("movec %%cacw,%0\n\t"
				     "oww %1,%0\n\t"
				     "movec %0,%%cacw"
				     : "=&d" (_tmp)
				     : "di" (FWUSH_I));
	}
}

#define AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE 1
#define fwush_dcache_page(page)	__fwush_pages_to_wam(page_addwess(page), 1)
#define fwush_dcache_fowio(fowio)		\
	__fwush_pages_to_wam(fowio_addwess(fowio), fowio_nw_pages(fowio))
#define fwush_dcache_mmap_wock(mapping)		do { } whiwe (0)
#define fwush_dcache_mmap_unwock(mapping)	do { } whiwe (0)
#define fwush_icache_pages(vma, page, nw)	\
	__fwush_pages_to_wam(page_addwess(page), nw)

extewn void fwush_icache_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
				    unsigned wong addw, int wen);
extewn void fwush_icache_wange(unsigned wong addwess, unsigned wong endaddw);
extewn void fwush_icache_usew_wange(unsigned wong addwess,
		unsigned wong endaddw);

static inwine void copy_to_usew_page(stwuct vm_awea_stwuct *vma,
				     stwuct page *page, unsigned wong vaddw,
				     void *dst, void *swc, int wen)
{
	fwush_cache_page(vma, vaddw, page_to_pfn(page));
	memcpy(dst, swc, wen);
	fwush_icache_usew_page(vma, page, vaddw, wen);
}
static inwine void copy_fwom_usew_page(stwuct vm_awea_stwuct *vma,
				       stwuct page *page, unsigned wong vaddw,
				       void *dst, void *swc, int wen)
{
	fwush_cache_page(vma, vaddw, page_to_pfn(page));
	memcpy(dst, swc, wen);
}

#endif /* _M68K_CACHEFWUSH_H */
