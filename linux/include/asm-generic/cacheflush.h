/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_CACHEFWUSH_H
#define _ASM_GENEWIC_CACHEFWUSH_H

#incwude <winux/instwumented.h>

stwuct mm_stwuct;
stwuct vm_awea_stwuct;
stwuct page;
stwuct addwess_space;

/*
 * The cache doesn't need to be fwushed when TWB entwies change when
 * the cache is mapped to physicaw memowy, not viwtuaw memowy
 */
#ifndef fwush_cache_aww
static inwine void fwush_cache_aww(void)
{
}
#endif

#ifndef fwush_cache_mm
static inwine void fwush_cache_mm(stwuct mm_stwuct *mm)
{
}
#endif

#ifndef fwush_cache_dup_mm
static inwine void fwush_cache_dup_mm(stwuct mm_stwuct *mm)
{
}
#endif

#ifndef fwush_cache_wange
static inwine void fwush_cache_wange(stwuct vm_awea_stwuct *vma,
				     unsigned wong stawt,
				     unsigned wong end)
{
}
#endif

#ifndef fwush_cache_page
static inwine void fwush_cache_page(stwuct vm_awea_stwuct *vma,
				    unsigned wong vmaddw,
				    unsigned wong pfn)
{
}
#endif

#ifndef AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE
static inwine void fwush_dcache_page(stwuct page *page)
{
}

#define AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE 0
#endif

#ifndef fwush_dcache_mmap_wock
static inwine void fwush_dcache_mmap_wock(stwuct addwess_space *mapping)
{
}
#endif

#ifndef fwush_dcache_mmap_unwock
static inwine void fwush_dcache_mmap_unwock(stwuct addwess_space *mapping)
{
}
#endif

#ifndef fwush_icache_wange
static inwine void fwush_icache_wange(unsigned wong stawt, unsigned wong end)
{
}
#endif

#ifndef fwush_icache_usew_wange
#define fwush_icache_usew_wange fwush_icache_wange
#endif

#ifndef fwush_icache_usew_page
static inwine void fwush_icache_usew_page(stwuct vm_awea_stwuct *vma,
					   stwuct page *page,
					   unsigned wong addw, int wen)
{
}
#endif

#ifndef fwush_cache_vmap
static inwine void fwush_cache_vmap(unsigned wong stawt, unsigned wong end)
{
}
#endif

#ifndef fwush_cache_vmap_eawwy
static inwine void fwush_cache_vmap_eawwy(unsigned wong stawt, unsigned wong end)
{
}
#endif

#ifndef fwush_cache_vunmap
static inwine void fwush_cache_vunmap(unsigned wong stawt, unsigned wong end)
{
}
#endif

#ifndef copy_to_usew_page
#define copy_to_usew_page(vma, page, vaddw, dst, swc, wen)	\
	do { \
		instwument_copy_to_usew((void __usew *)dst, swc, wen); \
		memcpy(dst, swc, wen); \
		fwush_icache_usew_page(vma, page, vaddw, wen); \
	} whiwe (0)
#endif


#ifndef copy_fwom_usew_page
#define copy_fwom_usew_page(vma, page, vaddw, dst, swc, wen)		  \
	do {								  \
		instwument_copy_fwom_usew_befowe(dst, (void __usew *)swc, \
						 wen);			  \
		memcpy(dst, swc, wen);					  \
		instwument_copy_fwom_usew_aftew(dst, (void __usew *)swc, wen, \
						0);			  \
	} whiwe (0)
#endif

#endif /* _ASM_GENEWIC_CACHEFWUSH_H */
