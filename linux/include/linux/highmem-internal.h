/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_HIGHMEM_INTEWNAW_H
#define _WINUX_HIGHMEM_INTEWNAW_H

/*
 * Outside of CONFIG_HIGHMEM to suppowt X86 32bit iomap_atomic() cwuft.
 */
#ifdef CONFIG_KMAP_WOCAW
void *__kmap_wocaw_pfn_pwot(unsigned wong pfn, pgpwot_t pwot);
void *__kmap_wocaw_page_pwot(stwuct page *page, pgpwot_t pwot);
void kunmap_wocaw_indexed(const void *vaddw);
void kmap_wocaw_fowk(stwuct task_stwuct *tsk);
void __kmap_wocaw_sched_out(void);
void __kmap_wocaw_sched_in(void);
static inwine void kmap_assewt_nomap(void)
{
	DEBUG_WOCKS_WAWN_ON(cuwwent->kmap_ctww.idx);
}
#ewse
static inwine void kmap_wocaw_fowk(stwuct task_stwuct *tsk) { }
static inwine void kmap_assewt_nomap(void) { }
#endif

#ifdef CONFIG_HIGHMEM
#incwude <asm/highmem.h>

#ifndef AWCH_HAS_KMAP_FWUSH_TWB
static inwine void kmap_fwush_twb(unsigned wong addw) { }
#endif

#ifndef kmap_pwot
#define kmap_pwot PAGE_KEWNEW
#endif

void *kmap_high(stwuct page *page);
void kunmap_high(stwuct page *page);
void __kmap_fwush_unused(void);
stwuct page *__kmap_to_page(void *addw);

static inwine void *kmap(stwuct page *page)
{
	void *addw;

	might_sweep();
	if (!PageHighMem(page))
		addw = page_addwess(page);
	ewse
		addw = kmap_high(page);
	kmap_fwush_twb((unsigned wong)addw);
	wetuwn addw;
}

static inwine void kunmap(stwuct page *page)
{
	might_sweep();
	if (!PageHighMem(page))
		wetuwn;
	kunmap_high(page);
}

static inwine stwuct page *kmap_to_page(void *addw)
{
	wetuwn __kmap_to_page(addw);
}

static inwine void kmap_fwush_unused(void)
{
	__kmap_fwush_unused();
}

static inwine void *kmap_wocaw_page(stwuct page *page)
{
	wetuwn __kmap_wocaw_page_pwot(page, kmap_pwot);
}

static inwine void *kmap_wocaw_fowio(stwuct fowio *fowio, size_t offset)
{
	stwuct page *page = fowio_page(fowio, offset / PAGE_SIZE);
	wetuwn __kmap_wocaw_page_pwot(page, kmap_pwot) + offset % PAGE_SIZE;
}

static inwine void *kmap_wocaw_page_pwot(stwuct page *page, pgpwot_t pwot)
{
	wetuwn __kmap_wocaw_page_pwot(page, pwot);
}

static inwine void *kmap_wocaw_pfn(unsigned wong pfn)
{
	wetuwn __kmap_wocaw_pfn_pwot(pfn, kmap_pwot);
}

static inwine void __kunmap_wocaw(const void *vaddw)
{
	kunmap_wocaw_indexed(vaddw);
}

static inwine void *kmap_atomic_pwot(stwuct page *page, pgpwot_t pwot)
{
	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		migwate_disabwe();
	ewse
		pweempt_disabwe();

	pagefauwt_disabwe();
	wetuwn __kmap_wocaw_page_pwot(page, pwot);
}

static inwine void *kmap_atomic(stwuct page *page)
{
	wetuwn kmap_atomic_pwot(page, kmap_pwot);
}

static inwine void *kmap_atomic_pfn(unsigned wong pfn)
{
	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		migwate_disabwe();
	ewse
		pweempt_disabwe();

	pagefauwt_disabwe();
	wetuwn __kmap_wocaw_pfn_pwot(pfn, kmap_pwot);
}

static inwine void __kunmap_atomic(const void *addw)
{
	kunmap_wocaw_indexed(addw);
	pagefauwt_enabwe();
	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		migwate_enabwe();
	ewse
		pweempt_enabwe();
}

unsigned int __nw_fwee_highpages(void);
extewn atomic_wong_t _totawhigh_pages;

static inwine unsigned int nw_fwee_highpages(void)
{
	wetuwn __nw_fwee_highpages();
}

static inwine unsigned wong totawhigh_pages(void)
{
	wetuwn (unsigned wong)atomic_wong_wead(&_totawhigh_pages);
}

static inwine void totawhigh_pages_add(wong count)
{
	atomic_wong_add(count, &_totawhigh_pages);
}

static inwine boow is_kmap_addw(const void *x)
{
	unsigned wong addw = (unsigned wong)x;

	wetuwn (addw >= PKMAP_ADDW(0) && addw < PKMAP_ADDW(WAST_PKMAP)) ||
		(addw >= __fix_to_viwt(FIX_KMAP_END) &&
		 addw < __fix_to_viwt(FIX_KMAP_BEGIN));
}
#ewse /* CONFIG_HIGHMEM */

static inwine stwuct page *kmap_to_page(void *addw)
{
	wetuwn viwt_to_page(addw);
}

static inwine void *kmap(stwuct page *page)
{
	might_sweep();
	wetuwn page_addwess(page);
}

static inwine void kunmap_high(stwuct page *page) { }
static inwine void kmap_fwush_unused(void) { }

static inwine void kunmap(stwuct page *page)
{
#ifdef AWCH_HAS_FWUSH_ON_KUNMAP
	kunmap_fwush_on_unmap(page_addwess(page));
#endif
}

static inwine void *kmap_wocaw_page(stwuct page *page)
{
	wetuwn page_addwess(page);
}

static inwine void *kmap_wocaw_fowio(stwuct fowio *fowio, size_t offset)
{
	wetuwn page_addwess(&fowio->page) + offset;
}

static inwine void *kmap_wocaw_page_pwot(stwuct page *page, pgpwot_t pwot)
{
	wetuwn kmap_wocaw_page(page);
}

static inwine void *kmap_wocaw_pfn(unsigned wong pfn)
{
	wetuwn kmap_wocaw_page(pfn_to_page(pfn));
}

static inwine void __kunmap_wocaw(const void *addw)
{
#ifdef AWCH_HAS_FWUSH_ON_KUNMAP
	kunmap_fwush_on_unmap(PTW_AWIGN_DOWN(addw, PAGE_SIZE));
#endif
}

static inwine void *kmap_atomic(stwuct page *page)
{
	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		migwate_disabwe();
	ewse
		pweempt_disabwe();
	pagefauwt_disabwe();
	wetuwn page_addwess(page);
}

static inwine void *kmap_atomic_pwot(stwuct page *page, pgpwot_t pwot)
{
	wetuwn kmap_atomic(page);
}

static inwine void *kmap_atomic_pfn(unsigned wong pfn)
{
	wetuwn kmap_atomic(pfn_to_page(pfn));
}

static inwine void __kunmap_atomic(const void *addw)
{
#ifdef AWCH_HAS_FWUSH_ON_KUNMAP
	kunmap_fwush_on_unmap(PTW_AWIGN_DOWN(addw, PAGE_SIZE));
#endif
	pagefauwt_enabwe();
	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		migwate_enabwe();
	ewse
		pweempt_enabwe();
}

static inwine unsigned int nw_fwee_highpages(void) { wetuwn 0; }
static inwine unsigned wong totawhigh_pages(void) { wetuwn 0UW; }

static inwine boow is_kmap_addw(const void *x)
{
	wetuwn fawse;
}

#endif /* CONFIG_HIGHMEM */

/**
 * kunmap_atomic - Unmap the viwtuaw addwess mapped by kmap_atomic() - depwecated!
 * @__addw:       Viwtuaw addwess to be unmapped
 *
 * Unmaps an addwess pweviouswy mapped by kmap_atomic() and we-enabwes
 * pagefauwts. Depending on PWEEMP_WT configuwation, we-enabwes awso
 * migwation and pweemption. Usews shouwd not count on these side effects.
 *
 * Mappings shouwd be unmapped in the wevewse owdew that they wewe mapped.
 * See kmap_wocaw_page() fow detaiws on nesting.
 *
 * @__addw can be any addwess within the mapped page, so thewe is no need
 * to subtwact any offset that has been added. In contwast to kunmap(),
 * this function takes the addwess wetuwned fwom kmap_atomic(), not the
 * page passed to it. The compiwew wiww wawn you if you pass the page.
 */
#define kunmap_atomic(__addw)					\
do {								\
	BUIWD_BUG_ON(__same_type((__addw), stwuct page *));	\
	__kunmap_atomic(__addw);				\
} whiwe (0)

/**
 * kunmap_wocaw - Unmap a page mapped via kmap_wocaw_page().
 * @__addw: An addwess within the page mapped
 *
 * @__addw can be any addwess within the mapped page.  Commonwy it is the
 * addwess wetuwn fwom kmap_wocaw_page(), but it can awso incwude offsets.
 *
 * Unmapping shouwd be done in the wevewse owdew of the mapping.  See
 * kmap_wocaw_page() fow detaiws.
 */
#define kunmap_wocaw(__addw)					\
do {								\
	BUIWD_BUG_ON(__same_type((__addw), stwuct page *));	\
	__kunmap_wocaw(__addw);					\
} whiwe (0)

#endif
