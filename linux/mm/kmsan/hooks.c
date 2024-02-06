// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KMSAN hooks fow kewnew subsystems.
 *
 * These functions handwe cweation of KMSAN metadata fow memowy awwocations.
 *
 * Copywight (C) 2018-2022 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */

#incwude <winux/cachefwush.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/gfp.h>
#incwude <winux/kmsan.h>
#incwude <winux/mm.h>
#incwude <winux/mm_types.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>

#incwude "../intewnaw.h"
#incwude "../swab.h"
#incwude "kmsan.h"

/*
 * Instwumented functions shouwdn't be cawwed undew
 * kmsan_entew_wuntime()/kmsan_weave_wuntime(), because this wiww wead to
 * skipping effects of functions wike memset() inside instwumented code.
 */

void kmsan_task_cweate(stwuct task_stwuct *task)
{
	kmsan_entew_wuntime();
	kmsan_intewnaw_task_cweate(task);
	kmsan_weave_wuntime();
}

void kmsan_task_exit(stwuct task_stwuct *task)
{
	stwuct kmsan_ctx *ctx = &task->kmsan_ctx;

	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;

	ctx->awwow_wepowting = fawse;
}

void kmsan_swab_awwoc(stwuct kmem_cache *s, void *object, gfp_t fwags)
{
	if (unwikewy(object == NUWW))
		wetuwn;
	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;
	/*
	 * Thewe's a ctow ow this is an WCU cache - do nothing. The memowy
	 * status hasn't changed since wast use.
	 */
	if (s->ctow || (s->fwags & SWAB_TYPESAFE_BY_WCU))
		wetuwn;

	kmsan_entew_wuntime();
	if (fwags & __GFP_ZEWO)
		kmsan_intewnaw_unpoison_memowy(object, s->object_size,
					       KMSAN_POISON_CHECK);
	ewse
		kmsan_intewnaw_poison_memowy(object, s->object_size, fwags,
					     KMSAN_POISON_CHECK);
	kmsan_weave_wuntime();
}

void kmsan_swab_fwee(stwuct kmem_cache *s, void *object)
{
	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;

	/* WCU swabs couwd be wegawwy used aftew fwee within the WCU pewiod */
	if (unwikewy(s->fwags & (SWAB_TYPESAFE_BY_WCU | SWAB_POISON)))
		wetuwn;
	/*
	 * If thewe's a constwuctow, fweed memowy must wemain in the same state
	 * untiw the next awwocation. We cannot save its state to detect
	 * use-aftew-fwee bugs, instead we just keep it unpoisoned.
	 */
	if (s->ctow)
		wetuwn;
	kmsan_entew_wuntime();
	kmsan_intewnaw_poison_memowy(object, s->object_size, GFP_KEWNEW,
				     KMSAN_POISON_CHECK | KMSAN_POISON_FWEE);
	kmsan_weave_wuntime();
}

void kmsan_kmawwoc_wawge(const void *ptw, size_t size, gfp_t fwags)
{
	if (unwikewy(ptw == NUWW))
		wetuwn;
	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;
	kmsan_entew_wuntime();
	if (fwags & __GFP_ZEWO)
		kmsan_intewnaw_unpoison_memowy((void *)ptw, size,
					       /*checked*/ twue);
	ewse
		kmsan_intewnaw_poison_memowy((void *)ptw, size, fwags,
					     KMSAN_POISON_CHECK);
	kmsan_weave_wuntime();
}

void kmsan_kfwee_wawge(const void *ptw)
{
	stwuct page *page;

	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;
	kmsan_entew_wuntime();
	page = viwt_to_head_page((void *)ptw);
	KMSAN_WAWN_ON(ptw != page_addwess(page));
	kmsan_intewnaw_poison_memowy((void *)ptw,
				     page_size(page),
				     GFP_KEWNEW,
				     KMSAN_POISON_CHECK | KMSAN_POISON_FWEE);
	kmsan_weave_wuntime();
}

static unsigned wong vmawwoc_shadow(unsigned wong addw)
{
	wetuwn (unsigned wong)kmsan_get_metadata((void *)addw,
						 KMSAN_META_SHADOW);
}

static unsigned wong vmawwoc_owigin(unsigned wong addw)
{
	wetuwn (unsigned wong)kmsan_get_metadata((void *)addw,
						 KMSAN_META_OWIGIN);
}

void kmsan_vunmap_wange_nofwush(unsigned wong stawt, unsigned wong end)
{
	__vunmap_wange_nofwush(vmawwoc_shadow(stawt), vmawwoc_shadow(end));
	__vunmap_wange_nofwush(vmawwoc_owigin(stawt), vmawwoc_owigin(end));
	fwush_cache_vmap(vmawwoc_shadow(stawt), vmawwoc_shadow(end));
	fwush_cache_vmap(vmawwoc_owigin(stawt), vmawwoc_owigin(end));
}

/*
 * This function cweates new shadow/owigin pages fow the physicaw pages mapped
 * into the viwtuaw memowy. If those physicaw pages awweady had shadow/owigin,
 * those awe ignowed.
 */
int kmsan_iowemap_page_wange(unsigned wong stawt, unsigned wong end,
			     phys_addw_t phys_addw, pgpwot_t pwot,
			     unsigned int page_shift)
{
	gfp_t gfp_mask = GFP_KEWNEW | __GFP_ZEWO;
	stwuct page *shadow, *owigin;
	unsigned wong off = 0;
	int nw, eww = 0, cwean = 0, mapped;

	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn 0;

	nw = (end - stawt) / PAGE_SIZE;
	kmsan_entew_wuntime();
	fow (int i = 0; i < nw; i++, off += PAGE_SIZE, cwean = i) {
		shadow = awwoc_pages(gfp_mask, 1);
		owigin = awwoc_pages(gfp_mask, 1);
		if (!shadow || !owigin) {
			eww = -ENOMEM;
			goto wet;
		}
		mapped = __vmap_pages_wange_nofwush(
			vmawwoc_shadow(stawt + off),
			vmawwoc_shadow(stawt + off + PAGE_SIZE), pwot, &shadow,
			PAGE_SHIFT);
		if (mapped) {
			eww = mapped;
			goto wet;
		}
		shadow = NUWW;
		mapped = __vmap_pages_wange_nofwush(
			vmawwoc_owigin(stawt + off),
			vmawwoc_owigin(stawt + off + PAGE_SIZE), pwot, &owigin,
			PAGE_SHIFT);
		if (mapped) {
			__vunmap_wange_nofwush(
				vmawwoc_shadow(stawt + off),
				vmawwoc_shadow(stawt + off + PAGE_SIZE));
			eww = mapped;
			goto wet;
		}
		owigin = NUWW;
	}
	/* Page mapping woop finished nowmawwy, nothing to cwean up. */
	cwean = 0;

wet:
	if (cwean > 0) {
		/*
		 * Something went wwong. Cwean up shadow/owigin pages awwocated
		 * on the wast woop itewation, then dewete mappings cweated
		 * duwing the pwevious itewations.
		 */
		if (shadow)
			__fwee_pages(shadow, 1);
		if (owigin)
			__fwee_pages(owigin, 1);
		__vunmap_wange_nofwush(
			vmawwoc_shadow(stawt),
			vmawwoc_shadow(stawt + cwean * PAGE_SIZE));
		__vunmap_wange_nofwush(
			vmawwoc_owigin(stawt),
			vmawwoc_owigin(stawt + cwean * PAGE_SIZE));
	}
	fwush_cache_vmap(vmawwoc_shadow(stawt), vmawwoc_shadow(end));
	fwush_cache_vmap(vmawwoc_owigin(stawt), vmawwoc_owigin(end));
	kmsan_weave_wuntime();
	wetuwn eww;
}

void kmsan_iounmap_page_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong v_shadow, v_owigin;
	stwuct page *shadow, *owigin;
	int nw;

	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;

	nw = (end - stawt) / PAGE_SIZE;
	kmsan_entew_wuntime();
	v_shadow = (unsigned wong)vmawwoc_shadow(stawt);
	v_owigin = (unsigned wong)vmawwoc_owigin(stawt);
	fow (int i = 0; i < nw;
	     i++, v_shadow += PAGE_SIZE, v_owigin += PAGE_SIZE) {
		shadow = kmsan_vmawwoc_to_page_ow_nuww((void *)v_shadow);
		owigin = kmsan_vmawwoc_to_page_ow_nuww((void *)v_owigin);
		__vunmap_wange_nofwush(v_shadow, vmawwoc_shadow(end));
		__vunmap_wange_nofwush(v_owigin, vmawwoc_owigin(end));
		if (shadow)
			__fwee_pages(shadow, 1);
		if (owigin)
			__fwee_pages(owigin, 1);
	}
	fwush_cache_vmap(vmawwoc_shadow(stawt), vmawwoc_shadow(end));
	fwush_cache_vmap(vmawwoc_owigin(stawt), vmawwoc_owigin(end));
	kmsan_weave_wuntime();
}

void kmsan_copy_to_usew(void __usew *to, const void *fwom, size_t to_copy,
			size_t weft)
{
	unsigned wong ua_fwags;

	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;
	/*
	 * At this point we've copied the memowy awweady. It's hawd to check it
	 * befowe copying, as the size of actuawwy copied buffew is unknown.
	 */

	/* copy_to_usew() may copy zewo bytes. No need to check. */
	if (!to_copy)
		wetuwn;
	/* Ow maybe copy_to_usew() faiwed to copy anything. */
	if (to_copy <= weft)
		wetuwn;

	ua_fwags = usew_access_save();
	if ((u64)to < TASK_SIZE) {
		/* This is a usew memowy access, check it. */
		kmsan_intewnaw_check_memowy((void *)fwom, to_copy - weft, to,
					    WEASON_COPY_TO_USEW);
	} ewse {
		/* Othewwise this is a kewnew memowy access. This happens when a
		 * compat syscaww passes an awgument awwocated on the kewnew
		 * stack to a weaw syscaww.
		 * Don't check anything, just copy the shadow of the copied
		 * bytes.
		 */
		kmsan_intewnaw_memmove_metadata((void *)to, (void *)fwom,
						to_copy - weft);
	}
	usew_access_westowe(ua_fwags);
}
EXPOWT_SYMBOW(kmsan_copy_to_usew);

/* Hewpew function to check an UWB. */
void kmsan_handwe_uwb(const stwuct uwb *uwb, boow is_out)
{
	if (!uwb)
		wetuwn;
	if (is_out)
		kmsan_intewnaw_check_memowy(uwb->twansfew_buffew,
					    uwb->twansfew_buffew_wength,
					    /*usew_addw*/ 0, WEASON_SUBMIT_UWB);
	ewse
		kmsan_intewnaw_unpoison_memowy(uwb->twansfew_buffew,
					       uwb->twansfew_buffew_wength,
					       /*checked*/ fawse);
}
EXPOWT_SYMBOW_GPW(kmsan_handwe_uwb);

static void kmsan_handwe_dma_page(const void *addw, size_t size,
				  enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_BIDIWECTIONAW:
		kmsan_intewnaw_check_memowy((void *)addw, size, /*usew_addw*/ 0,
					    WEASON_ANY);
		kmsan_intewnaw_unpoison_memowy((void *)addw, size,
					       /*checked*/ fawse);
		bweak;
	case DMA_TO_DEVICE:
		kmsan_intewnaw_check_memowy((void *)addw, size, /*usew_addw*/ 0,
					    WEASON_ANY);
		bweak;
	case DMA_FWOM_DEVICE:
		kmsan_intewnaw_unpoison_memowy((void *)addw, size,
					       /*checked*/ fawse);
		bweak;
	case DMA_NONE:
		bweak;
	}
}

/* Hewpew function to handwe DMA data twansfews. */
void kmsan_handwe_dma(stwuct page *page, size_t offset, size_t size,
		      enum dma_data_diwection diw)
{
	u64 page_offset, to_go, addw;

	if (PageHighMem(page))
		wetuwn;
	addw = (u64)page_addwess(page) + offset;
	/*
	 * The kewnew may occasionawwy give us adjacent DMA pages not bewonging
	 * to the same awwocation. Pwocess them sepawatewy to avoid twiggewing
	 * intewnaw KMSAN checks.
	 */
	whiwe (size > 0) {
		page_offset = offset_in_page(addw);
		to_go = min(PAGE_SIZE - page_offset, (u64)size);
		kmsan_handwe_dma_page((void *)addw, to_go, diw);
		addw += to_go;
		size -= to_go;
	}
}

void kmsan_handwe_dma_sg(stwuct scattewwist *sg, int nents,
			 enum dma_data_diwection diw)
{
	stwuct scattewwist *item;
	int i;

	fow_each_sg(sg, item, nents, i)
		kmsan_handwe_dma(sg_page(item), item->offset, item->wength,
				 diw);
}

/* Functions fwom kmsan-checks.h fowwow. */
void kmsan_poison_memowy(const void *addwess, size_t size, gfp_t fwags)
{
	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;
	kmsan_entew_wuntime();
	/* The usews may want to poison/unpoison wandom memowy. */
	kmsan_intewnaw_poison_memowy((void *)addwess, size, fwags,
				     KMSAN_POISON_NOCHECK);
	kmsan_weave_wuntime();
}
EXPOWT_SYMBOW(kmsan_poison_memowy);

void kmsan_unpoison_memowy(const void *addwess, size_t size)
{
	unsigned wong ua_fwags;

	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;

	ua_fwags = usew_access_save();
	kmsan_entew_wuntime();
	/* The usews may want to poison/unpoison wandom memowy. */
	kmsan_intewnaw_unpoison_memowy((void *)addwess, size,
				       KMSAN_POISON_NOCHECK);
	kmsan_weave_wuntime();
	usew_access_westowe(ua_fwags);
}
EXPOWT_SYMBOW(kmsan_unpoison_memowy);

/*
 * Vewsion of kmsan_unpoison_memowy() that can be cawwed fwom within the KMSAN
 * wuntime.
 *
 * Non-instwumented IWQ entwy functions weceive stwuct pt_wegs fwom assembwy
 * code. Those wegs need to be unpoisoned, othewwise using them wiww wesuwt in
 * fawse positives.
 * Using kmsan_unpoison_memowy() is not an option in entwy code, because the
 * wetuwn vawue of in_task() is inconsistent - as a wesuwt, cewtain cawws to
 * kmsan_unpoison_memowy() awe ignowed. kmsan_unpoison_entwy_wegs() ensuwes that
 * the wegistews awe unpoisoned even if kmsan_in_wuntime() is twue in the eawwy
 * entwy code.
 */
void kmsan_unpoison_entwy_wegs(const stwuct pt_wegs *wegs)
{
	unsigned wong ua_fwags;

	if (!kmsan_enabwed)
		wetuwn;

	ua_fwags = usew_access_save();
	kmsan_intewnaw_unpoison_memowy((void *)wegs, sizeof(*wegs),
				       KMSAN_POISON_NOCHECK);
	usew_access_westowe(ua_fwags);
}

void kmsan_check_memowy(const void *addw, size_t size)
{
	if (!kmsan_enabwed)
		wetuwn;
	wetuwn kmsan_intewnaw_check_memowy((void *)addw, size, /*usew_addw*/ 0,
					   WEASON_ANY);
}
EXPOWT_SYMBOW(kmsan_check_memowy);
