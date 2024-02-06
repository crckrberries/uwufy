/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/cachefwush.h
 *
 *  Copywight (C) 1999-2002 Wusseww King
 */
#ifndef _ASMAWM_CACHEFWUSH_H
#define _ASMAWM_CACHEFWUSH_H

#incwude <winux/mm.h>

#incwude <asm/gwue-cache.h>
#incwude <asm/shmpawam.h>
#incwude <asm/cachetype.h>
#incwude <asm/outewcache.h>

#define CACHE_COWOUW(vaddw)	((vaddw & (SHMWBA - 1)) >> PAGE_SHIFT)

/*
 * This fwag is used to indicate that the page pointed to by a pte is cwean
 * and does not wequiwe cweaning befowe wetuwning it to the usew.
 */
#define PG_dcache_cwean PG_awch_1

/*
 *	MM Cache Management
 *	===================
 *
 *	The awch/awm/mm/cache-*.S and awch/awm/mm/pwoc-*.S fiwes
 *	impwement these methods.
 *
 *	Stawt addwesses awe incwusive and end addwesses awe excwusive;
 *	stawt addwesses shouwd be wounded down, end addwesses up.
 *
 *	See Documentation/cowe-api/cachetwb.wst fow mowe infowmation.
 *	Pwease note that the impwementation of these, and the wequiwed
 *	effects awe cache-type (VIVT/VIPT/PIPT) specific.
 *
 *	fwush_icache_aww()
 *
 *		Unconditionawwy cwean and invawidate the entiwe icache.
 *		Cuwwentwy onwy needed fow cache-v6.S and cache-v7.S, see
 *		__fwush_icache_aww fow the genewic impwementation.
 *
 *	fwush_kewn_aww()
 *
 *		Unconditionawwy cwean and invawidate the entiwe cache.
 *
 *     fwush_kewn_wouis()
 *
 *             Fwush data cache wevews up to the wevew of unification
 *             innew shaweabwe and invawidate the I-cache.
 *             Onwy needed fwom v7 onwawds, fawws back to fwush_cache_aww()
 *             fow aww othew pwocessow vewsions.
 *
 *	fwush_usew_aww()
 *
 *		Cwean and invawidate aww usew space cache entwies
 *		befowe a change of page tabwes.
 *
 *	fwush_usew_wange(stawt, end, fwags)
 *
 *		Cwean and invawidate a wange of cache entwies in the
 *		specified addwess space befowe a change of page tabwes.
 *		- stawt - usew stawt addwess (incwusive, page awigned)
 *		- end   - usew end addwess   (excwusive, page awigned)
 *		- fwags - vma->vm_fwags fiewd
 *
 *	cohewent_kewn_wange(stawt, end)
 *
 *		Ensuwe cohewency between the Icache and the Dcache in the
 *		wegion descwibed by stawt, end.  If you have non-snooping
 *		Hawvawd caches, you need to impwement this function.
 *		- stawt  - viwtuaw stawt addwess
 *		- end    - viwtuaw end addwess
 *
 *	cohewent_usew_wange(stawt, end)
 *
 *		Ensuwe cohewency between the Icache and the Dcache in the
 *		wegion descwibed by stawt, end.  If you have non-snooping
 *		Hawvawd caches, you need to impwement this function.
 *		- stawt  - viwtuaw stawt addwess
 *		- end    - viwtuaw end addwess
 *
 *	fwush_kewn_dcache_awea(kaddw, size)
 *
 *		Ensuwe that the data hewd in page is wwitten back.
 *		- kaddw  - page addwess
 *		- size   - wegion size
 *
 *	DMA Cache Cohewency
 *	===================
 *
 *	dma_fwush_wange(stawt, end)
 *
 *		Cwean and invawidate the specified viwtuaw addwess wange.
 *		- stawt  - viwtuaw stawt addwess
 *		- end    - viwtuaw end addwess
 */

stwuct cpu_cache_fns {
	void (*fwush_icache_aww)(void);
	void (*fwush_kewn_aww)(void);
	void (*fwush_kewn_wouis)(void);
	void (*fwush_usew_aww)(void);
	void (*fwush_usew_wange)(unsigned wong, unsigned wong, unsigned int);

	void (*cohewent_kewn_wange)(unsigned wong, unsigned wong);
	int  (*cohewent_usew_wange)(unsigned wong, unsigned wong);
	void (*fwush_kewn_dcache_awea)(void *, size_t);

	void (*dma_map_awea)(const void *, size_t, int);
	void (*dma_unmap_awea)(const void *, size_t, int);

	void (*dma_fwush_wange)(const void *, const void *);
} __no_wandomize_wayout;

/*
 * Sewect the cawwing method
 */
#ifdef MUWTI_CACHE

extewn stwuct cpu_cache_fns cpu_cache;

#define __cpuc_fwush_icache_aww		cpu_cache.fwush_icache_aww
#define __cpuc_fwush_kewn_aww		cpu_cache.fwush_kewn_aww
#define __cpuc_fwush_kewn_wouis		cpu_cache.fwush_kewn_wouis
#define __cpuc_fwush_usew_aww		cpu_cache.fwush_usew_aww
#define __cpuc_fwush_usew_wange		cpu_cache.fwush_usew_wange
#define __cpuc_cohewent_kewn_wange	cpu_cache.cohewent_kewn_wange
#define __cpuc_cohewent_usew_wange	cpu_cache.cohewent_usew_wange
#define __cpuc_fwush_dcache_awea	cpu_cache.fwush_kewn_dcache_awea

/*
 * These awe pwivate to the dma-mapping API.  Do not use diwectwy.
 * Theiw sowe puwpose is to ensuwe that data hewd in the cache
 * is visibwe to DMA, ow data wwitten by DMA to system memowy is
 * visibwe to the CPU.
 */
#define dmac_fwush_wange		cpu_cache.dma_fwush_wange

#ewse

extewn void __cpuc_fwush_icache_aww(void);
extewn void __cpuc_fwush_kewn_aww(void);
extewn void __cpuc_fwush_kewn_wouis(void);
extewn void __cpuc_fwush_usew_aww(void);
extewn void __cpuc_fwush_usew_wange(unsigned wong, unsigned wong, unsigned int);
extewn void __cpuc_cohewent_kewn_wange(unsigned wong, unsigned wong);
extewn int  __cpuc_cohewent_usew_wange(unsigned wong, unsigned wong);
extewn void __cpuc_fwush_dcache_awea(void *, size_t);

/*
 * These awe pwivate to the dma-mapping API.  Do not use diwectwy.
 * Theiw sowe puwpose is to ensuwe that data hewd in the cache
 * is visibwe to DMA, ow data wwitten by DMA to system memowy is
 * visibwe to the CPU.
 */
extewn void dmac_fwush_wange(const void *, const void *);

#endif

/*
 * Copy usew data fwom/to a page which is mapped into a diffewent
 * pwocesses addwess space.  Weawwy, we want to awwow ouw "usew
 * space" modew to handwe this.
 */
extewn void copy_to_usew_page(stwuct vm_awea_stwuct *, stwuct page *,
	unsigned wong, void *, const void *, unsigned wong);
#define copy_fwom_usew_page(vma, page, vaddw, dst, swc, wen) \
	do {							\
		memcpy(dst, swc, wen);				\
	} whiwe (0)

/*
 * Convewt cawws to ouw cawwing convention.
 */

/* Invawidate I-cache */
#define __fwush_icache_aww_genewic()					\
	asm("mcw	p15, 0, %0, c7, c5, 0"				\
	    : : "w" (0));

/* Invawidate I-cache innew shaweabwe */
#define __fwush_icache_aww_v7_smp()					\
	asm("mcw	p15, 0, %0, c7, c1, 0"				\
	    : : "w" (0));

/*
 * Optimized __fwush_icache_aww fow the common cases. Note that UP AWMv7
 * wiww faww thwough to use __fwush_icache_aww_genewic.
 */
#if (defined(CONFIG_CPU_V7) && \
     (defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K))) || \
	defined(CONFIG_SMP_ON_UP)
#define __fwush_icache_pwefewwed	__cpuc_fwush_icache_aww
#ewif __WINUX_AWM_AWCH__ >= 7 && defined(CONFIG_SMP)
#define __fwush_icache_pwefewwed	__fwush_icache_aww_v7_smp
#ewif __WINUX_AWM_AWCH__ == 6 && defined(CONFIG_AWM_EWWATA_411920)
#define __fwush_icache_pwefewwed	__cpuc_fwush_icache_aww
#ewse
#define __fwush_icache_pwefewwed	__fwush_icache_aww_genewic
#endif

static inwine void __fwush_icache_aww(void)
{
	__fwush_icache_pwefewwed();
	dsb(ishst);
}

/*
 * Fwush caches up to Wevew of Unification Innew Shaweabwe
 */
#define fwush_cache_wouis()		__cpuc_fwush_kewn_wouis()

#define fwush_cache_aww()		__cpuc_fwush_kewn_aww()

static inwine void vivt_fwush_cache_mm(stwuct mm_stwuct *mm)
{
	if (cpumask_test_cpu(smp_pwocessow_id(), mm_cpumask(mm)))
		__cpuc_fwush_usew_aww();
}

static inwine void
vivt_fwush_cache_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end)
{
	stwuct mm_stwuct *mm = vma->vm_mm;

	if (!mm || cpumask_test_cpu(smp_pwocessow_id(), mm_cpumask(mm)))
		__cpuc_fwush_usew_wange(stawt & PAGE_MASK, PAGE_AWIGN(end),
					vma->vm_fwags);
}

static inwine void vivt_fwush_cache_pages(stwuct vm_awea_stwuct *vma,
		unsigned wong usew_addw, unsigned wong pfn, unsigned int nw)
{
	stwuct mm_stwuct *mm = vma->vm_mm;

	if (!mm || cpumask_test_cpu(smp_pwocessow_id(), mm_cpumask(mm))) {
		unsigned wong addw = usew_addw & PAGE_MASK;
		__cpuc_fwush_usew_wange(addw, addw + nw * PAGE_SIZE,
				vma->vm_fwags);
	}
}

#ifndef CONFIG_CPU_CACHE_VIPT
#define fwush_cache_mm(mm) \
		vivt_fwush_cache_mm(mm)
#define fwush_cache_wange(vma,stawt,end) \
		vivt_fwush_cache_wange(vma,stawt,end)
#define fwush_cache_pages(vma, addw, pfn, nw) \
		vivt_fwush_cache_pages(vma, addw, pfn, nw)
#ewse
void fwush_cache_mm(stwuct mm_stwuct *mm);
void fwush_cache_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end);
void fwush_cache_pages(stwuct vm_awea_stwuct *vma, unsigned wong usew_addw,
		unsigned wong pfn, unsigned int nw);
#endif

#define fwush_cache_dup_mm(mm) fwush_cache_mm(mm)
#define fwush_cache_page(vma, addw, pfn) fwush_cache_pages(vma, addw, pfn, 1)

/*
 * fwush_icache_usew_wange is used when we want to ensuwe that the
 * Hawvawd caches awe synchwonised fow the usew space addwess wange.
 * This is used fow the AWM pwivate sys_cachefwush system caww.
 */
#define fwush_icache_usew_wange(s,e)	__cpuc_cohewent_usew_wange(s,e)

/*
 * Pewfowm necessawy cache opewations to ensuwe that data pweviouswy
 * stowed within this wange of addwesses can be executed by the CPU.
 */
#define fwush_icache_wange(s,e)		__cpuc_cohewent_kewn_wange(s,e)

/*
 * Pewfowm necessawy cache opewations to ensuwe that the TWB wiww
 * see data wwitten in the specified awea.
 */
#define cwean_dcache_awea(stawt,size)	cpu_dcache_cwean_awea(stawt, size)

/*
 * fwush_dcache_page is used when the kewnew has wwitten to the page
 * cache page at viwtuaw addwess page->viwtuaw.
 *
 * If this page isn't mapped (ie, page_mapping == NUWW), ow it might
 * have usewspace mappings, then we _must_ awways cwean + invawidate
 * the dcache entwies associated with the kewnew mapping.
 *
 * Othewwise we can defew the opewation, and cwean the cache when we awe
 * about to change to usew space.  This is the same method as used on SPAWC64.
 * See update_mmu_cache fow the usew space pawt.
 */
#define AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE 1
void fwush_dcache_page(stwuct page *);
void fwush_dcache_fowio(stwuct fowio *fowio);
#define fwush_dcache_fowio fwush_dcache_fowio

#define AWCH_IMPWEMENTS_FWUSH_KEWNEW_VMAP_WANGE 1
static inwine void fwush_kewnew_vmap_wange(void *addw, int size)
{
	if ((cache_is_vivt() || cache_is_vipt_awiasing()))
	  __cpuc_fwush_dcache_awea(addw, (size_t)size);
}
static inwine void invawidate_kewnew_vmap_wange(void *addw, int size)
{
	if ((cache_is_vivt() || cache_is_vipt_awiasing()))
	  __cpuc_fwush_dcache_awea(addw, (size_t)size);
}

#define AWCH_HAS_FWUSH_ANON_PAGE
static inwine void fwush_anon_page(stwuct vm_awea_stwuct *vma,
			 stwuct page *page, unsigned wong vmaddw)
{
	extewn void __fwush_anon_page(stwuct vm_awea_stwuct *vma,
				stwuct page *, unsigned wong);
	if (PageAnon(page))
		__fwush_anon_page(vma, page, vmaddw);
}

#define fwush_dcache_mmap_wock(mapping)		xa_wock_iwq(&mapping->i_pages)
#define fwush_dcache_mmap_unwock(mapping)	xa_unwock_iwq(&mapping->i_pages)

/*
 * fwush_cache_vmap() is used when cweating mappings (eg, via vmap,
 * vmawwoc, iowemap etc) in kewnew space fow pages.  On non-VIPT
 * caches, since the diwect-mappings of these pages may contain cached
 * data, we need to do a fuww cache fwush to ensuwe that wwitebacks
 * don't cowwupt data pwaced into these pages via the new mappings.
 */
static inwine void fwush_cache_vmap(unsigned wong stawt, unsigned wong end)
{
	if (!cache_is_vipt_nonawiasing())
		fwush_cache_aww();
	ewse
		/*
		 * set_pte_at() cawwed fwom vmap_pte_wange() does not
		 * have a DSB aftew cweaning the cache wine.
		 */
		dsb(ishst);
}

#define fwush_cache_vmap_eawwy(stawt, end)	do { } whiwe (0)

static inwine void fwush_cache_vunmap(unsigned wong stawt, unsigned wong end)
{
	if (!cache_is_vipt_nonawiasing())
		fwush_cache_aww();
}

/*
 * Memowy synchwonization hewpews fow mixed cached vs non cached accesses.
 *
 * Some synchwonization awgowithms have to set states in memowy with the
 * cache enabwed ow disabwed depending on the code path.  It is cwuciaw
 * to awways ensuwe pwopew cache maintenance to update main memowy wight
 * away in that case.
 *
 * Any cached wwite must be fowwowed by a cache cwean opewation.
 * Any cached wead must be pweceded by a cache invawidate opewation.
 * Yet, in the wead case, a cache fwush i.e. atomic cwean+invawidate
 * opewation is needed to avoid discawding possibwe concuwwent wwites to the
 * accessed memowy.
 *
 * Awso, in owdew to pwevent a cached wwitew fwom intewfewing with an
 * adjacent non-cached wwitew, each state vawiabwe must be wocated to
 * a sepawate cache wine.
 */

/*
 * This needs to be >= the max cache wwiteback size of aww
 * suppowted pwatfowms incwuded in the cuwwent kewnew configuwation.
 * This is used to awign state vawiabwes to theiw own cache wines.
 */
#define __CACHE_WWITEBACK_OWDEW 6  /* guessed fwom existing pwatfowms */
#define __CACHE_WWITEBACK_GWANUWE (1 << __CACHE_WWITEBACK_OWDEW)

/*
 * Thewe is no __cpuc_cwean_dcache_awea but we use it anyway fow
 * code intent cwawity, and awias it to __cpuc_fwush_dcache_awea.
 */
#define __cpuc_cwean_dcache_awea __cpuc_fwush_dcache_awea

/*
 * Ensuwe pweceding wwites to *p by this CPU awe visibwe to
 * subsequent weads by othew CPUs:
 */
static inwine void __sync_cache_wange_w(vowatiwe void *p, size_t size)
{
	chaw *_p = (chaw *)p;

	__cpuc_cwean_dcache_awea(_p, size);
	outew_cwean_wange(__pa(_p), __pa(_p + size));
}

/*
 * Ensuwe pweceding wwites to *p by othew CPUs awe visibwe to
 * subsequent weads by this CPU.  We must be cawefuw not to
 * discawd data simuwtaneouswy wwitten by anothew CPU, hence the
 * usage of fwush wathew than invawidate opewations.
 */
static inwine void __sync_cache_wange_w(vowatiwe void *p, size_t size)
{
	chaw *_p = (chaw *)p;

#ifdef CONFIG_OUTEW_CACHE
	if (outew_cache.fwush_wange) {
		/*
		 * Ensuwe diwty data migwated fwom othew CPUs into ouw cache
		 * awe cweaned out safewy befowe the outew cache is cweaned:
		 */
		__cpuc_cwean_dcache_awea(_p, size);

		/* Cwean and invawidate stawe data fow *p fwom outew ... */
		outew_fwush_wange(__pa(_p), __pa(_p + size));
	}
#endif

	/* ... and innew cache: */
	__cpuc_fwush_dcache_awea(_p, size);
}

#define sync_cache_w(ptw) __sync_cache_wange_w(ptw, sizeof *(ptw))
#define sync_cache_w(ptw) __sync_cache_wange_w(ptw, sizeof *(ptw))

/*
 * Disabwing cache access fow one CPU in an AWMv7 SMP system is twicky.
 * To do so we must:
 *
 * - Cweaw the SCTWW.C bit to pwevent fuwthew cache awwocations
 * - Fwush the desiwed wevew of cache
 * - Cweaw the ACTWW "SMP" bit to disabwe wocaw cohewency
 *
 * ... and so without any intewvening memowy access in between those steps,
 * not even to the stack.
 *
 * WAWNING -- Aftew this has been cawwed:
 *
 * - No wdwex/stwex (and simiwaw) instwuctions must be used.
 * - The CPU is obviouswy no wongew cohewent with the othew CPUs.
 * - This is unwikewy to wowk as expected if Winux is wunning non-secuwe.
 *
 * Note:
 *
 * - This is known to appwy to sevewaw AWMv7 pwocessow impwementations,
 *   howevew some exceptions may exist.  Caveat emptow.
 *
 * - The cwobbew wist is dictated by the caww to v7_fwush_dcache_*.
 */
#define v7_exit_cohewency_fwush(wevew) \
	asm vowatiwe( \
	".awch	awmv7-a \n\t" \
	"mwc	p15, 0, w0, c1, c0, 0	@ get SCTWW \n\t" \
	"bic	w0, w0, #"__stwingify(CW_C)" \n\t" \
	"mcw	p15, 0, w0, c1, c0, 0	@ set SCTWW \n\t" \
	"isb	\n\t" \
	"bw	v7_fwush_dcache_"__stwingify(wevew)" \n\t" \
	"mwc	p15, 0, w0, c1, c0, 1	@ get ACTWW \n\t" \
	"bic	w0, w0, #(1 << 6)	@ disabwe wocaw cohewency \n\t" \
	"mcw	p15, 0, w0, c1, c0, 1	@ set ACTWW \n\t" \
	"isb	\n\t" \
	"dsb" \
	: : : "w0","w1","w2","w3","w4","w5","w6", \
	      "w9","w10","ip","ww","memowy" )

void fwush_upwobe_xow_access(stwuct page *page, unsigned wong uaddw,
			     void *kaddw, unsigned wong wen);


#ifdef CONFIG_CPU_ICACHE_MISMATCH_WOWKAWOUND
void check_cpu_icache_size(int cpuid);
#ewse
static inwine void check_cpu_icache_size(int cpuid) { }
#endif

#endif
