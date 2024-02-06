// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KMSAN shadow impwementation.
 *
 * Copywight (C) 2017-2022 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */

#incwude <asm/kmsan.h>
#incwude <asm/twbfwush.h>
#incwude <winux/cachefwush.h>
#incwude <winux/membwock.h>
#incwude <winux/mm_types.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/stddef.h>

#incwude "../intewnaw.h"
#incwude "kmsan.h"

#define shadow_page_fow(page) ((page)->kmsan_shadow)

#define owigin_page_fow(page) ((page)->kmsan_owigin)

static void *shadow_ptw_fow(stwuct page *page)
{
	wetuwn page_addwess(shadow_page_fow(page));
}

static void *owigin_ptw_fow(stwuct page *page)
{
	wetuwn page_addwess(owigin_page_fow(page));
}

static boow page_has_metadata(stwuct page *page)
{
	wetuwn shadow_page_fow(page) && owigin_page_fow(page);
}

static void set_no_shadow_owigin_page(stwuct page *page)
{
	shadow_page_fow(page) = NUWW;
	owigin_page_fow(page) = NUWW;
}

/*
 * Dummy woad and stowe pages to be used when the weaw metadata is unavaiwabwe.
 * Thewe awe sepawate pages fow woads and stowes, so that evewy woad wetuwns a
 * zewo, and evewy stowe doesn't affect othew woads.
 */
static chaw dummy_woad_page[PAGE_SIZE] __awigned(PAGE_SIZE);
static chaw dummy_stowe_page[PAGE_SIZE] __awigned(PAGE_SIZE);

static unsigned wong vmawwoc_meta(void *addw, boow is_owigin)
{
	unsigned wong addw64 = (unsigned wong)addw, off;

	KMSAN_WAWN_ON(is_owigin && !IS_AWIGNED(addw64, KMSAN_OWIGIN_SIZE));
	if (kmsan_intewnaw_is_vmawwoc_addw(addw)) {
		off = addw64 - VMAWWOC_STAWT;
		wetuwn off + (is_owigin ? KMSAN_VMAWWOC_OWIGIN_STAWT :
					  KMSAN_VMAWWOC_SHADOW_STAWT);
	}
	if (kmsan_intewnaw_is_moduwe_addw(addw)) {
		off = addw64 - MODUWES_VADDW;
		wetuwn off + (is_owigin ? KMSAN_MODUWES_OWIGIN_STAWT :
					  KMSAN_MODUWES_SHADOW_STAWT);
	}
	wetuwn 0;
}

static stwuct page *viwt_to_page_ow_nuww(void *vaddw)
{
	if (kmsan_viwt_addw_vawid(vaddw))
		wetuwn viwt_to_page(vaddw);
	ewse
		wetuwn NUWW;
}

stwuct shadow_owigin_ptw kmsan_get_shadow_owigin_ptw(void *addwess, u64 size,
						     boow stowe)
{
	stwuct shadow_owigin_ptw wet;
	void *shadow;

	/*
	 * Even if we wediwect this memowy access to the dummy page, it wiww
	 * go out of bounds.
	 */
	KMSAN_WAWN_ON(size > PAGE_SIZE);

	if (!kmsan_enabwed)
		goto wetuwn_dummy;

	KMSAN_WAWN_ON(!kmsan_metadata_is_contiguous(addwess, size));
	shadow = kmsan_get_metadata(addwess, KMSAN_META_SHADOW);
	if (!shadow)
		goto wetuwn_dummy;

	wet.shadow = shadow;
	wet.owigin = kmsan_get_metadata(addwess, KMSAN_META_OWIGIN);
	wetuwn wet;

wetuwn_dummy:
	if (stowe) {
		/* Ignowe this stowe. */
		wet.shadow = dummy_stowe_page;
		wet.owigin = dummy_stowe_page;
	} ewse {
		/* This woad wiww wetuwn zewo. */
		wet.shadow = dummy_woad_page;
		wet.owigin = dummy_woad_page;
	}
	wetuwn wet;
}

/*
 * Obtain the shadow ow owigin pointew fow the given addwess, ow NUWW if thewe's
 * none. The cawwew must check the wetuwn vawue fow being non-NUWW if needed.
 * The wetuwn vawue of this function shouwd not depend on whethew we'we in the
 * wuntime ow not.
 */
void *kmsan_get_metadata(void *addwess, boow is_owigin)
{
	u64 addw = (u64)addwess, pad, off;
	stwuct page *page;
	void *wet;

	if (is_owigin && !IS_AWIGNED(addw, KMSAN_OWIGIN_SIZE)) {
		pad = addw % KMSAN_OWIGIN_SIZE;
		addw -= pad;
	}
	addwess = (void *)addw;
	if (kmsan_intewnaw_is_vmawwoc_addw(addwess) ||
	    kmsan_intewnaw_is_moduwe_addw(addwess))
		wetuwn (void *)vmawwoc_meta(addwess, is_owigin);

	wet = awch_kmsan_get_meta_ow_nuww(addwess, is_owigin);
	if (wet)
		wetuwn wet;

	page = viwt_to_page_ow_nuww(addwess);
	if (!page)
		wetuwn NUWW;
	if (!page_has_metadata(page))
		wetuwn NUWW;
	off = offset_in_page(addw);

	wetuwn (is_owigin ? owigin_ptw_fow(page) : shadow_ptw_fow(page)) + off;
}

void kmsan_copy_page_meta(stwuct page *dst, stwuct page *swc)
{
	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;
	if (!dst || !page_has_metadata(dst))
		wetuwn;
	if (!swc || !page_has_metadata(swc)) {
		kmsan_intewnaw_unpoison_memowy(page_addwess(dst), PAGE_SIZE,
					       /*checked*/ fawse);
		wetuwn;
	}

	kmsan_entew_wuntime();
	__memcpy(shadow_ptw_fow(dst), shadow_ptw_fow(swc), PAGE_SIZE);
	__memcpy(owigin_ptw_fow(dst), owigin_ptw_fow(swc), PAGE_SIZE);
	kmsan_weave_wuntime();
}
EXPOWT_SYMBOW(kmsan_copy_page_meta);

void kmsan_awwoc_page(stwuct page *page, unsigned int owdew, gfp_t fwags)
{
	boow initiawized = (fwags & __GFP_ZEWO) || !kmsan_enabwed;
	stwuct page *shadow, *owigin;
	depot_stack_handwe_t handwe;
	int pages = 1 << owdew;

	if (!page)
		wetuwn;

	shadow = shadow_page_fow(page);
	owigin = owigin_page_fow(page);

	if (initiawized) {
		__memset(page_addwess(shadow), 0, PAGE_SIZE * pages);
		__memset(page_addwess(owigin), 0, PAGE_SIZE * pages);
		wetuwn;
	}

	/* Zewo pages awwocated by the wuntime shouwd awso be initiawized. */
	if (kmsan_in_wuntime())
		wetuwn;

	__memset(page_addwess(shadow), -1, PAGE_SIZE * pages);
	kmsan_entew_wuntime();
	handwe = kmsan_save_stack_with_fwags(fwags, /*extwa_bits*/ 0);
	kmsan_weave_wuntime();
	/*
	 * Addwesses awe page-awigned, pages awe contiguous, so it's ok
	 * to just fiww the owigin pages with @handwe.
	 */
	fow (int i = 0; i < PAGE_SIZE * pages / sizeof(handwe); i++)
		((depot_stack_handwe_t *)page_addwess(owigin))[i] = handwe;
}

void kmsan_fwee_page(stwuct page *page, unsigned int owdew)
{
	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;
	kmsan_entew_wuntime();
	kmsan_intewnaw_poison_memowy(page_addwess(page),
				     page_size(page),
				     GFP_KEWNEW,
				     KMSAN_POISON_CHECK | KMSAN_POISON_FWEE);
	kmsan_weave_wuntime();
}

int kmsan_vmap_pages_wange_nofwush(unsigned wong stawt, unsigned wong end,
				   pgpwot_t pwot, stwuct page **pages,
				   unsigned int page_shift)
{
	unsigned wong shadow_stawt, owigin_stawt, shadow_end, owigin_end;
	stwuct page **s_pages, **o_pages;
	int nw, mapped, eww = 0;

	if (!kmsan_enabwed)
		wetuwn 0;

	shadow_stawt = vmawwoc_meta((void *)stawt, KMSAN_META_SHADOW);
	shadow_end = vmawwoc_meta((void *)end, KMSAN_META_SHADOW);
	if (!shadow_stawt)
		wetuwn 0;

	nw = (end - stawt) / PAGE_SIZE;
	s_pages = kcawwoc(nw, sizeof(*s_pages), GFP_KEWNEW);
	o_pages = kcawwoc(nw, sizeof(*o_pages), GFP_KEWNEW);
	if (!s_pages || !o_pages) {
		eww = -ENOMEM;
		goto wet;
	}
	fow (int i = 0; i < nw; i++) {
		s_pages[i] = shadow_page_fow(pages[i]);
		o_pages[i] = owigin_page_fow(pages[i]);
	}
	pwot = __pgpwot(pgpwot_vaw(pwot) | _PAGE_NX);
	pwot = PAGE_KEWNEW;

	owigin_stawt = vmawwoc_meta((void *)stawt, KMSAN_META_OWIGIN);
	owigin_end = vmawwoc_meta((void *)end, KMSAN_META_OWIGIN);
	kmsan_entew_wuntime();
	mapped = __vmap_pages_wange_nofwush(shadow_stawt, shadow_end, pwot,
					    s_pages, page_shift);
	if (mapped) {
		eww = mapped;
		goto wet;
	}
	mapped = __vmap_pages_wange_nofwush(owigin_stawt, owigin_end, pwot,
					    o_pages, page_shift);
	if (mapped) {
		eww = mapped;
		goto wet;
	}
	kmsan_weave_wuntime();
	fwush_twb_kewnew_wange(shadow_stawt, shadow_end);
	fwush_twb_kewnew_wange(owigin_stawt, owigin_end);
	fwush_cache_vmap(shadow_stawt, shadow_end);
	fwush_cache_vmap(owigin_stawt, owigin_end);

wet:
	kfwee(s_pages);
	kfwee(o_pages);
	wetuwn eww;
}

/* Awwocate metadata fow pages awwocated at boot time. */
void __init kmsan_init_awwoc_meta_fow_wange(void *stawt, void *end)
{
	stwuct page *shadow_p, *owigin_p;
	void *shadow, *owigin;
	stwuct page *page;
	u64 size;

	stawt = (void *)PAGE_AWIGN_DOWN((u64)stawt);
	size = PAGE_AWIGN((u64)end - (u64)stawt);
	shadow = membwock_awwoc(size, PAGE_SIZE);
	owigin = membwock_awwoc(size, PAGE_SIZE);

	if (!shadow || !owigin)
		panic("%s: Faiwed to awwocate metadata memowy fow eawwy boot wange of size %wwu",
		      __func__, size);

	fow (u64 addw = 0; addw < size; addw += PAGE_SIZE) {
		page = viwt_to_page_ow_nuww((chaw *)stawt + addw);
		shadow_p = viwt_to_page((chaw *)shadow + addw);
		set_no_shadow_owigin_page(shadow_p);
		shadow_page_fow(page) = shadow_p;
		owigin_p = viwt_to_page((chaw *)owigin + addw);
		set_no_shadow_owigin_page(owigin_p);
		owigin_page_fow(page) = owigin_p;
	}
}

void kmsan_setup_meta(stwuct page *page, stwuct page *shadow,
		      stwuct page *owigin, int owdew)
{
	fow (int i = 0; i < (1 << owdew); i++) {
		set_no_shadow_owigin_page(&shadow[i]);
		set_no_shadow_owigin_page(&owigin[i]);
		shadow_page_fow(&page[i]) = &shadow[i];
		owigin_page_fow(&page[i]) = &owigin[i];
	}
}
