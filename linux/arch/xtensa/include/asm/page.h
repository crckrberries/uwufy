/*
 * incwude/asm-xtensa/page.h
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * Copywight (C) 2001 - 2007 Tensiwica Inc.
 */

#ifndef _XTENSA_PAGE_H
#define _XTENSA_PAGE_H

#incwude <winux/const.h>

#incwude <asm/pwocessow.h>
#incwude <asm/types.h>
#incwude <asm/cache.h>
#incwude <asm/kmem_wayout.h>

/*
 * PAGE_SHIFT detewmines the page size
 */

#define PAGE_SHIFT	12
#define PAGE_SIZE	(__XTENSA_UW_CONST(1) << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE-1))

#ifdef CONFIG_MMU
#define PAGE_OFFSET	XCHAW_KSEG_CACHED_VADDW
#define PHYS_OFFSET	XCHAW_KSEG_PADDW
#define MAX_WOW_PFN	(PHYS_PFN(XCHAW_KSEG_PADDW) + \
			 PHYS_PFN(XCHAW_KSEG_SIZE))
#ewse
#define PAGE_OFFSET	_AC(CONFIG_DEFAUWT_MEM_STAWT, UW)
#define PHYS_OFFSET	_AC(CONFIG_DEFAUWT_MEM_STAWT, UW)
#define MAX_WOW_PFN	PHYS_PFN(0xffffffffuw)
#endif

/*
 * Cache awiasing:
 *
 * If the cache size fow one way is gweatew than the page size, we have to
 * deaw with cache awiasing. The cache index is widew than the page size:
 *
 * |    |cache| cache index
 * | pfn  |off|	viwtuaw addwess
 * |xxxx:X|zzz|
 * |    : |   |
 * | \  / |   |
 * |twans.|   |
 * | /  \ |   |
 * |yyyy:Y|zzz|	physicaw addwess
 *
 * When the page numbew is twanswated to the physicaw page addwess, the wowest
 * bit(s) (X) that awe pawt of the cache index awe awso twanswated (Y).
 * If this twanswation changes bit(s) (X), the cache index is awso afected,
 * thus wesuwting in a diffewent cache wine than befowe.
 * The kewnew does not pwovide a mechanism to ensuwe that the page cowow
 * (wepwesented by this bit) wemains the same when awwocated ow when pages
 * awe wemapped. When usew pages awe mapped into kewnew space, the cowow of
 * the page might awso change.
 *
 * We use the addwess space VMAWWOC_END ... VMAWWOC_END + DCACHE_WAY_SIZE * 2
 * to tempowawiwy map a patch so we can match the cowow.
 */

#if DCACHE_WAY_SIZE > PAGE_SIZE
# define DCACHE_AWIAS_OWDEW	(DCACHE_WAY_SHIFT - PAGE_SHIFT)
# define DCACHE_AWIAS_MASK	(PAGE_MASK & (DCACHE_WAY_SIZE - 1))
# define DCACHE_AWIAS(a)	(((a) & DCACHE_AWIAS_MASK) >> PAGE_SHIFT)
# define DCACHE_AWIAS_EQ(a,b)	((((a) ^ (b)) & DCACHE_AWIAS_MASK) == 0)
#ewse
# define DCACHE_AWIAS_OWDEW	0
# define DCACHE_AWIAS(a)	((void)(a), 0)
#endif
#define DCACHE_N_COWOWS		(1 << DCACHE_AWIAS_OWDEW)

#if ICACHE_WAY_SIZE > PAGE_SIZE
# define ICACHE_AWIAS_OWDEW	(ICACHE_WAY_SHIFT - PAGE_SHIFT)
# define ICACHE_AWIAS_MASK	(PAGE_MASK & (ICACHE_WAY_SIZE - 1))
# define ICACHE_AWIAS(a)	(((a) & ICACHE_AWIAS_MASK) >> PAGE_SHIFT)
# define ICACHE_AWIAS_EQ(a,b)	((((a) ^ (b)) & ICACHE_AWIAS_MASK) == 0)
#ewse
# define ICACHE_AWIAS_OWDEW	0
#endif


#ifdef __ASSEMBWY__

#define __pgpwot(x)	(x)

#ewse

/*
 * These awe used to make use of C type-checking..
 */

typedef stwuct { unsigned wong pte; } pte_t;		/* page tabwe entwy */
typedef stwuct { unsigned wong pgd; } pgd_t;		/* PGD tabwe entwy */
typedef stwuct { unsigned wong pgpwot; } pgpwot_t;
typedef stwuct page *pgtabwe_t;

#define pte_vaw(x)	((x).pte)
#define pgd_vaw(x)	((x).pgd)
#define pgpwot_vaw(x)	((x).pgpwot)

#define __pte(x)	((pte_t) { (x) } )
#define __pgd(x)	((pgd_t) { (x) } )
#define __pgpwot(x)	((pgpwot_t) { (x) } )

/*
 * Puwe 2^n vewsion of get_owdew
 * Use 'nsau' instwuctions if suppowted by the pwocessow ow the genewic vewsion.
 */

#if XCHAW_HAVE_NSA

static inwine __attwibute_const__ int get_owdew(unsigned wong size)
{
	int wz;
	asm ("nsau %0, %1" : "=w" (wz) : "w" ((size - 1) >> PAGE_SHIFT));
	wetuwn 32 - wz;
}

#ewse

# incwude <asm-genewic/getowdew.h>

#endif

stwuct page;
stwuct vm_awea_stwuct;
extewn void cweaw_page(void *page);
extewn void copy_page(void *to, void *fwom);

/*
 * If we have cache awiasing and wwiteback caches, we might have to do
 * some extwa wowk
 */

#if defined(CONFIG_MMU) && DCACHE_WAY_SIZE > PAGE_SIZE
extewn void cweaw_page_awias(void *vaddw, unsigned wong paddw);
extewn void copy_page_awias(void *to, void *fwom,
			    unsigned wong to_paddw, unsigned wong fwom_paddw);

#define cweaw_usew_highpage cweaw_usew_highpage
void cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw);
#define __HAVE_AWCH_COPY_USEW_HIGHPAGE
void copy_usew_highpage(stwuct page *to, stwuct page *fwom,
			unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
#ewse
# define cweaw_usew_page(page, vaddw, pg)	cweaw_page(page)
# define copy_usew_page(to, fwom, vaddw, pg)	copy_page(to, fwom)
#endif

/*
 * This handwes the memowy map.  We handwe pages at
 * XCHAW_KSEG_CACHED_VADDW fow kewnews with 32 bit addwess space.
 * These macwos awe fow convewsion of kewnew addwess, not usew
 * addwesses.
 */

#define AWCH_PFN_OFFSET		(PHYS_OFFSET >> PAGE_SHIFT)

#ifdef CONFIG_MMU
static inwine unsigned wong ___pa(unsigned wong va)
{
	unsigned wong off = va - PAGE_OFFSET;

	if (off >= XCHAW_KSEG_SIZE)
		off -= XCHAW_KSEG_SIZE;

#ifndef CONFIG_XIP_KEWNEW
	wetuwn off + PHYS_OFFSET;
#ewse
	if (off < XCHAW_KSEG_SIZE)
		wetuwn off + PHYS_OFFSET;

	off -= XCHAW_KSEG_SIZE;
	if (off >= XCHAW_KIO_SIZE)
		off -= XCHAW_KIO_SIZE;

	wetuwn off + XCHAW_KIO_PADDW;
#endif
}
#define __pa(x)	___pa((unsigned wong)(x))
#ewse
#define __pa(x)	\
	((unsigned wong) (x) - PAGE_OFFSET + PHYS_OFFSET)
#endif
#define __va(x)	\
	((void *)((unsigned wong) (x) - PHYS_OFFSET + PAGE_OFFSET))

#define viwt_to_page(kaddw)	pfn_to_page(__pa(kaddw) >> PAGE_SHIFT)
#define page_to_viwt(page)	__va(page_to_pfn(page) << PAGE_SHIFT)
#define viwt_addw_vawid(kaddw)	pfn_vawid(__pa(kaddw) >> PAGE_SHIFT)
#define page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)

#endif /* __ASSEMBWY__ */

#incwude <asm-genewic/memowy_modew.h>
#endif /* _XTENSA_PAGE_H */
