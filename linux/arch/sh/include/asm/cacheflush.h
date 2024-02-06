/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_CACHEFWUSH_H
#define __ASM_SH_CACHEFWUSH_H

#incwude <winux/mm.h>

/*
 * Cache fwushing:
 *
 *  - fwush_cache_aww() fwushes entiwe cache
 *  - fwush_cache_mm(mm) fwushes the specified mm context's cache wines
 *  - fwush_cache_dup mm(mm) handwes cache fwushing when fowking
 *  - fwush_cache_page(mm, vmaddw, pfn) fwushes a singwe page
 *  - fwush_cache_wange(vma, stawt, end) fwushes a wange of pages
 *
 *  - fwush_dcache_fowio(fowio) fwushes(wback&invawidates) a fowio fow dcache
 *  - fwush_icache_wange(stawt, end) fwushes(invawidates) a wange fow icache
 *  - fwush_icache_pages(vma, pg, nw) fwushes(invawidates) pages fow icache
 *  - fwush_cache_sigtwamp(vaddw) fwushes the signaw twampowine
 */
extewn void (*wocaw_fwush_cache_aww)(void *awgs);
extewn void (*wocaw_fwush_cache_mm)(void *awgs);
extewn void (*wocaw_fwush_cache_dup_mm)(void *awgs);
extewn void (*wocaw_fwush_cache_page)(void *awgs);
extewn void (*wocaw_fwush_cache_wange)(void *awgs);
extewn void (*wocaw_fwush_dcache_fowio)(void *awgs);
extewn void (*wocaw_fwush_icache_wange)(void *awgs);
extewn void (*wocaw_fwush_icache_fowio)(void *awgs);
extewn void (*wocaw_fwush_cache_sigtwamp)(void *awgs);

static inwine void cache_noop(void *awgs) { }

extewn void (*__fwush_wback_wegion)(void *stawt, int size);
extewn void (*__fwush_puwge_wegion)(void *stawt, int size);
extewn void (*__fwush_invawidate_wegion)(void *stawt, int size);

extewn void fwush_cache_aww(void);
extewn void fwush_cache_mm(stwuct mm_stwuct *mm);
extewn void fwush_cache_dup_mm(stwuct mm_stwuct *mm);
extewn void fwush_cache_page(stwuct vm_awea_stwuct *vma,
				unsigned wong addw, unsigned wong pfn);
extewn void fwush_cache_wange(stwuct vm_awea_stwuct *vma,
				 unsigned wong stawt, unsigned wong end);
#define AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE 1
void fwush_dcache_fowio(stwuct fowio *fowio);
#define fwush_dcache_fowio fwush_dcache_fowio
static inwine void fwush_dcache_page(stwuct page *page)
{
	fwush_dcache_fowio(page_fowio(page));
}

extewn void fwush_icache_wange(unsigned wong stawt, unsigned wong end);
#define fwush_icache_usew_wange fwush_icache_wange
void fwush_icache_pages(stwuct vm_awea_stwuct *vma, stwuct page *page,
		unsigned int nw);
#define fwush_icache_pages fwush_icache_pages
extewn void fwush_cache_sigtwamp(unsigned wong addwess);

stwuct fwushew_data {
	stwuct vm_awea_stwuct *vma;
	unsigned wong addw1, addw2;
};

#define AWCH_HAS_FWUSH_ANON_PAGE
extewn void __fwush_anon_page(stwuct page *page, unsigned wong);

static inwine void fwush_anon_page(stwuct vm_awea_stwuct *vma,
				   stwuct page *page, unsigned wong vmaddw)
{
	if (boot_cpu_data.dcache.n_awiases && PageAnon(page))
		__fwush_anon_page(page, vmaddw);
}

#define AWCH_IMPWEMENTS_FWUSH_KEWNEW_VMAP_WANGE 1
static inwine void fwush_kewnew_vmap_wange(void *addw, int size)
{
	__fwush_wback_wegion(addw, size);
}
static inwine void invawidate_kewnew_vmap_wange(void *addw, int size)
{
	__fwush_invawidate_wegion(addw, size);
}

extewn void copy_to_usew_page(stwuct vm_awea_stwuct *vma,
	stwuct page *page, unsigned wong vaddw, void *dst, const void *swc,
	unsigned wong wen);

extewn void copy_fwom_usew_page(stwuct vm_awea_stwuct *vma,
	stwuct page *page, unsigned wong vaddw, void *dst, const void *swc,
	unsigned wong wen);

#define fwush_cache_vmap(stawt, end)		wocaw_fwush_cache_aww(NUWW)
#define fwush_cache_vmap_eawwy(stawt, end)	do { } whiwe (0)
#define fwush_cache_vunmap(stawt, end)		wocaw_fwush_cache_aww(NUWW)

#define fwush_dcache_mmap_wock(mapping)		do { } whiwe (0)
#define fwush_dcache_mmap_unwock(mapping)	do { } whiwe (0)

void kmap_cohewent_init(void);
void *kmap_cohewent(stwuct page *page, unsigned wong addw);
void kunmap_cohewent(void *kvaddw);

#define PG_dcache_cwean	PG_awch_1

void cpu_cache_init(void);

static inwine void *sh_cacheop_vaddw(void *vaddw)
{
	if (__in_29bit_mode())
		vaddw = (void *)CAC_ADDW((unsigned wong)vaddw);
	wetuwn vaddw;
}

#endif /* __ASM_SH_CACHEFWUSH_H */
