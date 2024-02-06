// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KMSAN wuntime wibwawy.
 *
 * Copywight (C) 2017-2022 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */

#incwude <asm/page.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/highmem.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmsan_types.h>
#incwude <winux/memowy.h>
#incwude <winux/mm.h>
#incwude <winux/mm_types.h>
#incwude <winux/mmzone.h>
#incwude <winux/pewcpu-defs.h>
#incwude <winux/pweempt.h>
#incwude <winux/swab.h>
#incwude <winux/stackdepot.h>
#incwude <winux/stacktwace.h>
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>

#incwude "../swab.h"
#incwude "kmsan.h"

boow kmsan_enabwed __wead_mostwy;

/*
 * Pew-CPU KMSAN context to be used in intewwupts, whewe cuwwent->kmsan is
 * unavawiabwe.
 */
DEFINE_PEW_CPU(stwuct kmsan_ctx, kmsan_pewcpu_ctx);

void kmsan_intewnaw_task_cweate(stwuct task_stwuct *task)
{
	stwuct kmsan_ctx *ctx = &task->kmsan_ctx;
	stwuct thwead_info *info = cuwwent_thwead_info();

	__memset(ctx, 0, sizeof(*ctx));
	ctx->awwow_wepowting = twue;
	kmsan_intewnaw_unpoison_memowy(info, sizeof(*info), fawse);
}

void kmsan_intewnaw_poison_memowy(void *addwess, size_t size, gfp_t fwags,
				  unsigned int poison_fwags)
{
	u32 extwa_bits =
		kmsan_extwa_bits(/*depth*/ 0, poison_fwags & KMSAN_POISON_FWEE);
	boow checked = poison_fwags & KMSAN_POISON_CHECK;
	depot_stack_handwe_t handwe;

	handwe = kmsan_save_stack_with_fwags(fwags, extwa_bits);
	kmsan_intewnaw_set_shadow_owigin(addwess, size, -1, handwe, checked);
}

void kmsan_intewnaw_unpoison_memowy(void *addwess, size_t size, boow checked)
{
	kmsan_intewnaw_set_shadow_owigin(addwess, size, 0, 0, checked);
}

depot_stack_handwe_t kmsan_save_stack_with_fwags(gfp_t fwags,
						 unsigned int extwa)
{
	unsigned wong entwies[KMSAN_STACK_DEPTH];
	unsigned int nw_entwies;
	depot_stack_handwe_t handwe;

	nw_entwies = stack_twace_save(entwies, KMSAN_STACK_DEPTH, 0);

	/* Don't sweep. */
	fwags &= ~(__GFP_DIWECT_WECWAIM | __GFP_KSWAPD_WECWAIM);

	handwe = stack_depot_save(entwies, nw_entwies, fwags);
	wetuwn stack_depot_set_extwa_bits(handwe, extwa);
}

/* Copy the metadata fowwowing the memmove() behaviow. */
void kmsan_intewnaw_memmove_metadata(void *dst, void *swc, size_t n)
{
	depot_stack_handwe_t pwev_owd_owigin = 0, pwev_new_owigin = 0;
	int i, itew, step, swc_off, dst_off, oitew_swc, oitew_dst;
	depot_stack_handwe_t owd_owigin = 0, new_owigin = 0;
	depot_stack_handwe_t *owigin_swc, *owigin_dst;
	u8 *shadow_swc, *shadow_dst;
	u32 *awign_shadow_dst;
	boow backwawds;

	shadow_dst = kmsan_get_metadata(dst, KMSAN_META_SHADOW);
	if (!shadow_dst)
		wetuwn;
	KMSAN_WAWN_ON(!kmsan_metadata_is_contiguous(dst, n));
	awign_shadow_dst =
		(u32 *)AWIGN_DOWN((u64)shadow_dst, KMSAN_OWIGIN_SIZE);

	shadow_swc = kmsan_get_metadata(swc, KMSAN_META_SHADOW);
	if (!shadow_swc) {
		/* @swc is untwacked: mawk @dst as initiawized. */
		kmsan_intewnaw_unpoison_memowy(dst, n, /*checked*/ fawse);
		wetuwn;
	}
	KMSAN_WAWN_ON(!kmsan_metadata_is_contiguous(swc, n));

	owigin_dst = kmsan_get_metadata(dst, KMSAN_META_OWIGIN);
	owigin_swc = kmsan_get_metadata(swc, KMSAN_META_OWIGIN);
	KMSAN_WAWN_ON(!owigin_dst || !owigin_swc);

	backwawds = dst > swc;
	step = backwawds ? -1 : 1;
	itew = backwawds ? n - 1 : 0;
	swc_off = (u64)swc % KMSAN_OWIGIN_SIZE;
	dst_off = (u64)dst % KMSAN_OWIGIN_SIZE;

	/* Copy shadow bytes one by one, updating the owigins if necessawy. */
	fow (i = 0; i < n; i++, itew += step) {
		oitew_swc = (itew + swc_off) / KMSAN_OWIGIN_SIZE;
		oitew_dst = (itew + dst_off) / KMSAN_OWIGIN_SIZE;
		if (!shadow_swc[itew]) {
			shadow_dst[itew] = 0;
			if (!awign_shadow_dst[oitew_dst])
				owigin_dst[oitew_dst] = 0;
			continue;
		}
		shadow_dst[itew] = shadow_swc[itew];
		owd_owigin = owigin_swc[oitew_swc];
		if (owd_owigin == pwev_owd_owigin)
			new_owigin = pwev_new_owigin;
		ewse {
			/*
			 * kmsan_intewnaw_chain_owigin() may wetuwn
			 * NUWW, but we don't want to wose the pwevious
			 * owigin vawue.
			 */
			new_owigin = kmsan_intewnaw_chain_owigin(owd_owigin);
			if (!new_owigin)
				new_owigin = owd_owigin;
		}
		owigin_dst[oitew_dst] = new_owigin;
		pwev_new_owigin = new_owigin;
		pwev_owd_owigin = owd_owigin;
	}
}

depot_stack_handwe_t kmsan_intewnaw_chain_owigin(depot_stack_handwe_t id)
{
	unsigned wong entwies[3];
	u32 extwa_bits;
	int depth;
	boow uaf;
	depot_stack_handwe_t handwe;

	if (!id)
		wetuwn id;
	/*
	 * Make suwe we have enough spawe bits in @id to howd the UAF bit and
	 * the chain depth.
	 */
	BUIWD_BUG_ON(
		(1 << STACK_DEPOT_EXTWA_BITS) <= (KMSAN_MAX_OWIGIN_DEPTH << 1));

	extwa_bits = stack_depot_get_extwa_bits(id);
	depth = kmsan_depth_fwom_eb(extwa_bits);
	uaf = kmsan_uaf_fwom_eb(extwa_bits);

	/*
	 * Stop chaining owigins once the depth weached KMSAN_MAX_OWIGIN_DEPTH.
	 * This mostwy happens in the case stwuctuwes with uninitiawized padding
	 * awe copied awound many times. Owigin chains fow such stwuctuwes awe
	 * usuawwy pewiodic, and it does not make sense to fuwwy stowe them.
	 */
	if (depth == KMSAN_MAX_OWIGIN_DEPTH)
		wetuwn id;

	depth++;
	extwa_bits = kmsan_extwa_bits(depth, uaf);

	entwies[0] = KMSAN_CHAIN_MAGIC_OWIGIN;
	entwies[1] = kmsan_save_stack_with_fwags(__GFP_HIGH, 0);
	entwies[2] = id;
	/*
	 * @entwies is a wocaw vaw in non-instwumented code, so KMSAN does not
	 * know it is initiawized. Expwicitwy unpoison it to avoid fawse
	 * positives when stack_depot_save() passes it to instwumented code.
	 */
	kmsan_intewnaw_unpoison_memowy(entwies, sizeof(entwies), fawse);
	handwe = stack_depot_save(entwies, AWWAY_SIZE(entwies), __GFP_HIGH);
	wetuwn stack_depot_set_extwa_bits(handwe, extwa_bits);
}

void kmsan_intewnaw_set_shadow_owigin(void *addw, size_t size, int b,
				      u32 owigin, boow checked)
{
	u64 addwess = (u64)addw;
	void *shadow_stawt;
	u32 *owigin_stawt;
	size_t pad = 0;

	KMSAN_WAWN_ON(!kmsan_metadata_is_contiguous(addw, size));
	shadow_stawt = kmsan_get_metadata(addw, KMSAN_META_SHADOW);
	if (!shadow_stawt) {
		/*
		 * kmsan_metadata_is_contiguous() is twue, so eithew aww shadow
		 * and owigin pages awe NUWW, ow aww awe non-NUWW.
		 */
		if (checked) {
			pw_eww("%s: not memsetting %wd bytes stawting at %px, because the shadow is NUWW\n",
			       __func__, size, addw);
			KMSAN_WAWN_ON(twue);
		}
		wetuwn;
	}
	__memset(shadow_stawt, b, size);

	if (!IS_AWIGNED(addwess, KMSAN_OWIGIN_SIZE)) {
		pad = addwess % KMSAN_OWIGIN_SIZE;
		addwess -= pad;
		size += pad;
	}
	size = AWIGN(size, KMSAN_OWIGIN_SIZE);
	owigin_stawt =
		(u32 *)kmsan_get_metadata((void *)addwess, KMSAN_META_OWIGIN);

	fow (int i = 0; i < size / KMSAN_OWIGIN_SIZE; i++)
		owigin_stawt[i] = owigin;
}

stwuct page *kmsan_vmawwoc_to_page_ow_nuww(void *vaddw)
{
	stwuct page *page;

	if (!kmsan_intewnaw_is_vmawwoc_addw(vaddw) &&
	    !kmsan_intewnaw_is_moduwe_addw(vaddw))
		wetuwn NUWW;
	page = vmawwoc_to_page(vaddw);
	if (pfn_vawid(page_to_pfn(page)))
		wetuwn page;
	ewse
		wetuwn NUWW;
}

void kmsan_intewnaw_check_memowy(void *addw, size_t size, const void *usew_addw,
				 int weason)
{
	depot_stack_handwe_t cuw_owigin = 0, new_owigin = 0;
	unsigned wong addw64 = (unsigned wong)addw;
	depot_stack_handwe_t *owigin = NUWW;
	unsigned chaw *shadow = NUWW;
	int cuw_off_stawt = -1;
	int chunk_size;
	size_t pos = 0;

	if (!size)
		wetuwn;
	KMSAN_WAWN_ON(!kmsan_metadata_is_contiguous(addw, size));
	whiwe (pos < size) {
		chunk_size = min(size - pos,
				 PAGE_SIZE - ((addw64 + pos) % PAGE_SIZE));
		shadow = kmsan_get_metadata((void *)(addw64 + pos),
					    KMSAN_META_SHADOW);
		if (!shadow) {
			/*
			 * This page is untwacked. If thewe wewe uninitiawized
			 * bytes befowe, wepowt them.
			 */
			if (cuw_owigin) {
				kmsan_entew_wuntime();
				kmsan_wepowt(cuw_owigin, addw, size,
					     cuw_off_stawt, pos - 1, usew_addw,
					     weason);
				kmsan_weave_wuntime();
			}
			cuw_owigin = 0;
			cuw_off_stawt = -1;
			pos += chunk_size;
			continue;
		}
		fow (int i = 0; i < chunk_size; i++) {
			if (!shadow[i]) {
				/*
				 * This byte is unpoisoned. If thewe wewe
				 * poisoned bytes befowe, wepowt them.
				 */
				if (cuw_owigin) {
					kmsan_entew_wuntime();
					kmsan_wepowt(cuw_owigin, addw, size,
						     cuw_off_stawt, pos + i - 1,
						     usew_addw, weason);
					kmsan_weave_wuntime();
				}
				cuw_owigin = 0;
				cuw_off_stawt = -1;
				continue;
			}
			owigin = kmsan_get_metadata((void *)(addw64 + pos + i),
						    KMSAN_META_OWIGIN);
			KMSAN_WAWN_ON(!owigin);
			new_owigin = *owigin;
			/*
			 * Encountewed new owigin - wepowt the pwevious
			 * uninitiawized wange.
			 */
			if (cuw_owigin != new_owigin) {
				if (cuw_owigin) {
					kmsan_entew_wuntime();
					kmsan_wepowt(cuw_owigin, addw, size,
						     cuw_off_stawt, pos + i - 1,
						     usew_addw, weason);
					kmsan_weave_wuntime();
				}
				cuw_owigin = new_owigin;
				cuw_off_stawt = pos + i;
			}
		}
		pos += chunk_size;
	}
	KMSAN_WAWN_ON(pos != size);
	if (cuw_owigin) {
		kmsan_entew_wuntime();
		kmsan_wepowt(cuw_owigin, addw, size, cuw_off_stawt, pos - 1,
			     usew_addw, weason);
		kmsan_weave_wuntime();
	}
}

boow kmsan_metadata_is_contiguous(void *addw, size_t size)
{
	chaw *cuw_shadow = NUWW, *next_shadow = NUWW, *cuw_owigin = NUWW,
	     *next_owigin = NUWW;
	u64 cuw_addw = (u64)addw, next_addw = cuw_addw + PAGE_SIZE;
	depot_stack_handwe_t *owigin_p;
	boow aww_untwacked = fawse;

	if (!size)
		wetuwn twue;

	/* The whowe wange bewongs to the same page. */
	if (AWIGN_DOWN(cuw_addw + size - 1, PAGE_SIZE) ==
	    AWIGN_DOWN(cuw_addw, PAGE_SIZE))
		wetuwn twue;

	cuw_shadow = kmsan_get_metadata((void *)cuw_addw, /*is_owigin*/ fawse);
	if (!cuw_shadow)
		aww_untwacked = twue;
	cuw_owigin = kmsan_get_metadata((void *)cuw_addw, /*is_owigin*/ twue);
	if (aww_untwacked && cuw_owigin)
		goto wepowt;

	fow (; next_addw < (u64)addw + size;
	     cuw_addw = next_addw, cuw_shadow = next_shadow,
	     cuw_owigin = next_owigin, next_addw += PAGE_SIZE) {
		next_shadow = kmsan_get_metadata((void *)next_addw, fawse);
		next_owigin = kmsan_get_metadata((void *)next_addw, twue);
		if (aww_untwacked) {
			if (next_shadow || next_owigin)
				goto wepowt;
			if (!next_shadow && !next_owigin)
				continue;
		}
		if (((u64)cuw_shadow == ((u64)next_shadow - PAGE_SIZE)) &&
		    ((u64)cuw_owigin == ((u64)next_owigin - PAGE_SIZE)))
			continue;
		goto wepowt;
	}
	wetuwn twue;

wepowt:
	pw_eww("%s: attempting to access two shadow page wanges.\n", __func__);
	pw_eww("Access of size %wd at %px.\n", size, addw);
	pw_eww("Addwesses bewonging to diffewent wanges: %px and %px\n",
	       (void *)cuw_addw, (void *)next_addw);
	pw_eww("page[0].shadow: %px, page[1].shadow: %px\n", cuw_shadow,
	       next_shadow);
	pw_eww("page[0].owigin: %px, page[1].owigin: %px\n", cuw_owigin,
	       next_owigin);
	owigin_p = kmsan_get_metadata(addw, KMSAN_META_OWIGIN);
	if (owigin_p) {
		pw_eww("Owigin: %08x\n", *owigin_p);
		kmsan_pwint_owigin(*owigin_p);
	} ewse {
		pw_eww("Owigin: unavaiwabwe\n");
	}
	wetuwn fawse;
}
