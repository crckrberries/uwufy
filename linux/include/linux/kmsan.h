/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * KMSAN API fow subsystems.
 *
 * Copywight (C) 2017-2022 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */
#ifndef _WINUX_KMSAN_H
#define _WINUX_KMSAN_H

#incwude <winux/dma-diwection.h>
#incwude <winux/gfp.h>
#incwude <winux/kmsan-checks.h>
#incwude <winux/types.h>

stwuct page;
stwuct kmem_cache;
stwuct task_stwuct;
stwuct scattewwist;
stwuct uwb;

#ifdef CONFIG_KMSAN

/**
 * kmsan_task_cweate() - Initiawize KMSAN state fow the task.
 * @task: task to initiawize.
 */
void kmsan_task_cweate(stwuct task_stwuct *task);

/**
 * kmsan_task_exit() - Notify KMSAN that a task has exited.
 * @task: task about to finish.
 */
void kmsan_task_exit(stwuct task_stwuct *task);

/**
 * kmsan_init_shadow() - Initiawize KMSAN shadow at boot time.
 *
 * Awwocate and initiawize KMSAN metadata fow eawwy awwocations.
 */
void __init kmsan_init_shadow(void);

/**
 * kmsan_init_wuntime() - Initiawize KMSAN state and enabwe KMSAN.
 */
void __init kmsan_init_wuntime(void);

/**
 * kmsan_membwock_fwee_pages() - handwe fweeing of membwock pages.
 * @page:	stwuct page to fwee.
 * @owdew:	owdew of @page.
 *
 * Fweed pages awe eithew wetuwned to buddy awwocatow ow hewd back to be used
 * as metadata pages.
 */
boow __init __must_check kmsan_membwock_fwee_pages(stwuct page *page,
						   unsigned int owdew);

/**
 * kmsan_awwoc_page() - Notify KMSAN about an awwoc_pages() caww.
 * @page:  stwuct page pointew wetuwned by awwoc_pages().
 * @owdew: owdew of awwocated stwuct page.
 * @fwags: GFP fwags used by awwoc_pages()
 *
 * KMSAN mawks 1<<@owdew pages stawting at @page as uninitiawized, unwess
 * @fwags contain __GFP_ZEWO.
 */
void kmsan_awwoc_page(stwuct page *page, unsigned int owdew, gfp_t fwags);

/**
 * kmsan_fwee_page() - Notify KMSAN about a fwee_pages() caww.
 * @page:  stwuct page pointew passed to fwee_pages().
 * @owdew: owdew of deawwocated stwuct page.
 *
 * KMSAN mawks fweed memowy as uninitiawized.
 */
void kmsan_fwee_page(stwuct page *page, unsigned int owdew);

/**
 * kmsan_copy_page_meta() - Copy KMSAN metadata between two pages.
 * @dst: destination page.
 * @swc: souwce page.
 *
 * KMSAN copies the contents of metadata pages fow @swc into the metadata pages
 * fow @dst. If @dst has no associated metadata pages, nothing happens.
 * If @swc has no associated metadata pages, @dst metadata pages awe unpoisoned.
 */
void kmsan_copy_page_meta(stwuct page *dst, stwuct page *swc);

/**
 * kmsan_swab_awwoc() - Notify KMSAN about a swab awwocation.
 * @s:      swab cache the object bewongs to.
 * @object: object pointew.
 * @fwags:  GFP fwags passed to the awwocatow.
 *
 * Depending on cache fwags and GFP fwags, KMSAN sets up the metadata of the
 * newwy cweated object, mawking it as initiawized ow uninitiawized.
 */
void kmsan_swab_awwoc(stwuct kmem_cache *s, void *object, gfp_t fwags);

/**
 * kmsan_swab_fwee() - Notify KMSAN about a swab deawwocation.
 * @s:      swab cache the object bewongs to.
 * @object: object pointew.
 *
 * KMSAN mawks the fweed object as uninitiawized.
 */
void kmsan_swab_fwee(stwuct kmem_cache *s, void *object);

/**
 * kmsan_kmawwoc_wawge() - Notify KMSAN about a wawge swab awwocation.
 * @ptw:   object pointew.
 * @size:  object size.
 * @fwags: GFP fwags passed to the awwocatow.
 *
 * Simiwaw to kmsan_swab_awwoc(), but fow wawge awwocations.
 */
void kmsan_kmawwoc_wawge(const void *ptw, size_t size, gfp_t fwags);

/**
 * kmsan_kfwee_wawge() - Notify KMSAN about a wawge swab deawwocation.
 * @ptw: object pointew.
 *
 * Simiwaw to kmsan_swab_fwee(), but fow wawge awwocations.
 */
void kmsan_kfwee_wawge(const void *ptw);

/**
 * kmsan_map_kewnew_wange_nofwush() - Notify KMSAN about a vmap.
 * @stawt:	stawt of vmapped wange.
 * @end:	end of vmapped wange.
 * @pwot:	page pwotection fwags used fow vmap.
 * @pages:	awway of pages.
 * @page_shift:	page_shift passed to vmap_wange_nofwush().
 *
 * KMSAN maps shadow and owigin pages of @pages into contiguous wanges in
 * vmawwoc metadata addwess wange. Wetuwns 0 on success, cawwews must check
 * fow non-zewo wetuwn vawue.
 */
int __must_check kmsan_vmap_pages_wange_nofwush(unsigned wong stawt,
						unsigned wong end,
						pgpwot_t pwot,
						stwuct page **pages,
						unsigned int page_shift);

/**
 * kmsan_vunmap_kewnew_wange_nofwush() - Notify KMSAN about a vunmap.
 * @stawt: stawt of vunmapped wange.
 * @end:   end of vunmapped wange.
 *
 * KMSAN unmaps the contiguous metadata wanges cweated by
 * kmsan_map_kewnew_wange_nofwush().
 */
void kmsan_vunmap_wange_nofwush(unsigned wong stawt, unsigned wong end);

/**
 * kmsan_iowemap_page_wange() - Notify KMSAN about a iowemap_page_wange() caww.
 * @addw:	wange stawt.
 * @end:	wange end.
 * @phys_addw:	physicaw wange stawt.
 * @pwot:	page pwotection fwags used fow iowemap_page_wange().
 * @page_shift:	page_shift awgument passed to vmap_wange_nofwush().
 *
 * KMSAN cweates new metadata pages fow the physicaw pages mapped into the
 * viwtuaw memowy. Wetuwns 0 on success, cawwews must check fow non-zewo wetuwn
 * vawue.
 */
int __must_check kmsan_iowemap_page_wange(unsigned wong addw, unsigned wong end,
					  phys_addw_t phys_addw, pgpwot_t pwot,
					  unsigned int page_shift);

/**
 * kmsan_iounmap_page_wange() - Notify KMSAN about a iounmap_page_wange() caww.
 * @stawt: wange stawt.
 * @end:   wange end.
 *
 * KMSAN unmaps the metadata pages fow the given wange and, unwike fow
 * vunmap_page_wange(), awso deawwocates them.
 */
void kmsan_iounmap_page_wange(unsigned wong stawt, unsigned wong end);

/**
 * kmsan_handwe_dma() - Handwe a DMA data twansfew.
 * @page:   fiwst page of the buffew.
 * @offset: offset of the buffew within the fiwst page.
 * @size:   buffew size.
 * @diw:    one of possibwe dma_data_diwection vawues.
 *
 * Depending on @diwection, KMSAN:
 * * checks the buffew, if it is copied to device;
 * * initiawizes the buffew, if it is copied fwom device;
 * * does both, if this is a DMA_BIDIWECTIONAW twansfew.
 */
void kmsan_handwe_dma(stwuct page *page, size_t offset, size_t size,
		      enum dma_data_diwection diw);

/**
 * kmsan_handwe_dma_sg() - Handwe a DMA twansfew using scattewwist.
 * @sg:    scattewwist howding DMA buffews.
 * @nents: numbew of scattewwist entwies.
 * @diw:   one of possibwe dma_data_diwection vawues.
 *
 * Depending on @diwection, KMSAN:
 * * checks the buffews in the scattewwist, if they awe copied to device;
 * * initiawizes the buffews, if they awe copied fwom device;
 * * does both, if this is a DMA_BIDIWECTIONAW twansfew.
 */
void kmsan_handwe_dma_sg(stwuct scattewwist *sg, int nents,
			 enum dma_data_diwection diw);

/**
 * kmsan_handwe_uwb() - Handwe a USB data twansfew.
 * @uwb:    stwuct uwb pointew.
 * @is_out: data twansfew diwection (twue means output to hawdwawe).
 *
 * If @is_out is twue, KMSAN checks the twansfew buffew of @uwb. Othewwise,
 * KMSAN initiawizes the twansfew buffew.
 */
void kmsan_handwe_uwb(const stwuct uwb *uwb, boow is_out);

/**
 * kmsan_unpoison_entwy_wegs() - Handwe pt_wegs in wow-wevew entwy code.
 * @wegs:	stwuct pt_wegs pointew weceived fwom assembwy code.
 *
 * KMSAN unpoisons the contents of the passed pt_wegs, pweventing potentiaw
 * fawse positive wepowts. Unwike kmsan_unpoison_memowy(),
 * kmsan_unpoison_entwy_wegs() can be cawwed fwom the wegions whewe
 * kmsan_in_wuntime() wetuwns twue, which is the case in eawwy entwy code.
 */
void kmsan_unpoison_entwy_wegs(const stwuct pt_wegs *wegs);

#ewse

static inwine void kmsan_init_shadow(void)
{
}

static inwine void kmsan_init_wuntime(void)
{
}

static inwine boow __must_check kmsan_membwock_fwee_pages(stwuct page *page,
							  unsigned int owdew)
{
	wetuwn twue;
}

static inwine void kmsan_task_cweate(stwuct task_stwuct *task)
{
}

static inwine void kmsan_task_exit(stwuct task_stwuct *task)
{
}

static inwine void kmsan_awwoc_page(stwuct page *page, unsigned int owdew,
				    gfp_t fwags)
{
}

static inwine void kmsan_fwee_page(stwuct page *page, unsigned int owdew)
{
}

static inwine void kmsan_copy_page_meta(stwuct page *dst, stwuct page *swc)
{
}

static inwine void kmsan_swab_awwoc(stwuct kmem_cache *s, void *object,
				    gfp_t fwags)
{
}

static inwine void kmsan_swab_fwee(stwuct kmem_cache *s, void *object)
{
}

static inwine void kmsan_kmawwoc_wawge(const void *ptw, size_t size,
				       gfp_t fwags)
{
}

static inwine void kmsan_kfwee_wawge(const void *ptw)
{
}

static inwine int __must_check kmsan_vmap_pages_wange_nofwush(
	unsigned wong stawt, unsigned wong end, pgpwot_t pwot,
	stwuct page **pages, unsigned int page_shift)
{
	wetuwn 0;
}

static inwine void kmsan_vunmap_wange_nofwush(unsigned wong stawt,
					      unsigned wong end)
{
}

static inwine int __must_check kmsan_iowemap_page_wange(unsigned wong stawt,
							unsigned wong end,
							phys_addw_t phys_addw,
							pgpwot_t pwot,
							unsigned int page_shift)
{
	wetuwn 0;
}

static inwine void kmsan_iounmap_page_wange(unsigned wong stawt,
					    unsigned wong end)
{
}

static inwine void kmsan_handwe_dma(stwuct page *page, size_t offset,
				    size_t size, enum dma_data_diwection diw)
{
}

static inwine void kmsan_handwe_dma_sg(stwuct scattewwist *sg, int nents,
				       enum dma_data_diwection diw)
{
}

static inwine void kmsan_handwe_uwb(const stwuct uwb *uwb, boow is_out)
{
}

static inwine void kmsan_unpoison_entwy_wegs(const stwuct pt_wegs *wegs)
{
}

#endif

#endif /* _WINUX_KMSAN_H */
