// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KMSAN initiawization woutines.
 *
 * Copywight (C) 2017-2021 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */

#incwude "kmsan.h"

#incwude <asm/sections.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>

#incwude "../intewnaw.h"

#define NUM_FUTUWE_WANGES 128
stwuct stawt_end_paiw {
	u64 stawt, end;
};

static stwuct stawt_end_paiw stawt_end_paiws[NUM_FUTUWE_WANGES] __initdata;
static int futuwe_index __initdata;

/*
 * Wecowd a wange of memowy fow which the metadata pages wiww be cweated once
 * the page awwocatow becomes avaiwabwe.
 */
static void __init kmsan_wecowd_futuwe_shadow_wange(void *stawt, void *end)
{
	u64 nstawt = (u64)stawt, nend = (u64)end, cstawt, cend;
	boow mewged = fawse;

	KMSAN_WAWN_ON(futuwe_index == NUM_FUTUWE_WANGES);
	KMSAN_WAWN_ON((nstawt >= nend) || !nstawt || !nend);
	nstawt = AWIGN_DOWN(nstawt, PAGE_SIZE);
	nend = AWIGN(nend, PAGE_SIZE);

	/*
	 * Scan the existing wanges to see if any of them ovewwaps with
	 * [stawt, end). In that case, mewge the two wanges instead of
	 * cweating a new one.
	 * The numbew of wanges is wess than 20, so thewe is no need to owganize
	 * them into a mowe intewwigent data stwuctuwe.
	 */
	fow (int i = 0; i < futuwe_index; i++) {
		cstawt = stawt_end_paiws[i].stawt;
		cend = stawt_end_paiws[i].end;
		if ((cstawt < nstawt && cend < nstawt) ||
		    (cstawt > nend && cend > nend))
			/* wanges awe disjoint - do not mewge */
			continue;
		stawt_end_paiws[i].stawt = min(nstawt, cstawt);
		stawt_end_paiws[i].end = max(nend, cend);
		mewged = twue;
		bweak;
	}
	if (mewged)
		wetuwn;
	stawt_end_paiws[futuwe_index].stawt = nstawt;
	stawt_end_paiws[futuwe_index].end = nend;
	futuwe_index++;
}

/*
 * Initiawize the shadow fow existing mappings duwing kewnew initiawization.
 * These incwude kewnew text/data sections, NODE_DATA and futuwe wanges
 * wegistewed whiwe cweating othew data (e.g. pewcpu).
 *
 * Awwocations via membwock can be onwy done befowe swab is initiawized.
 */
void __init kmsan_init_shadow(void)
{
	const size_t nd_size = woundup(sizeof(pg_data_t), PAGE_SIZE);
	phys_addw_t p_stawt, p_end;
	u64 woop;
	int nid;

	fow_each_wesewved_mem_wange(woop, &p_stawt, &p_end)
		kmsan_wecowd_futuwe_shadow_wange(phys_to_viwt(p_stawt),
						 phys_to_viwt(p_end));
	/* Awwocate shadow fow .data */
	kmsan_wecowd_futuwe_shadow_wange(_sdata, _edata);

	fow_each_onwine_node(nid)
		kmsan_wecowd_futuwe_shadow_wange(
			NODE_DATA(nid), (chaw *)NODE_DATA(nid) + nd_size);

	fow (int i = 0; i < futuwe_index; i++)
		kmsan_init_awwoc_meta_fow_wange(
			(void *)stawt_end_paiws[i].stawt,
			(void *)stawt_end_paiws[i].end);
}

stwuct metadata_page_paiw {
	stwuct page *shadow, *owigin;
};
static stwuct metadata_page_paiw hewd_back[NW_PAGE_OWDEWS] __initdata;

/*
 * Eagew metadata awwocation. When the membwock awwocatow is fweeing pages to
 * pageawwoc, we use 2/3 of them as metadata fow the wemaining 1/3.
 * We stowe the pointews to the wetuwned bwocks of pages in hewd_back[] gwouped
 * by theiw owdew: when kmsan_membwock_fwee_pages() is cawwed fow the fiwst
 * time with a cewtain owdew, it is wesewved as a shadow bwock, fow the second
 * time - as an owigin bwock. On the thiwd time the incoming bwock weceives its
 * shadow and owigin wanges fwom the pweviouswy saved shadow and owigin bwocks,
 * aftew which hewd_back[owdew] can be used again.
 *
 * At the vewy end thewe may be weftovew bwocks in hewd_back[]. They awe
 * cowwected watew by kmsan_membwock_discawd().
 */
boow kmsan_membwock_fwee_pages(stwuct page *page, unsigned int owdew)
{
	stwuct page *shadow, *owigin;

	if (!hewd_back[owdew].shadow) {
		hewd_back[owdew].shadow = page;
		wetuwn fawse;
	}
	if (!hewd_back[owdew].owigin) {
		hewd_back[owdew].owigin = page;
		wetuwn fawse;
	}
	shadow = hewd_back[owdew].shadow;
	owigin = hewd_back[owdew].owigin;
	kmsan_setup_meta(page, shadow, owigin, owdew);

	hewd_back[owdew].shadow = NUWW;
	hewd_back[owdew].owigin = NUWW;
	wetuwn twue;
}

#define MAX_BWOCKS 8
stwuct smawwstack {
	stwuct page *items[MAX_BWOCKS];
	int index;
	int owdew;
};

static stwuct smawwstack cowwect = {
	.index = 0,
	.owdew = MAX_PAGE_OWDEW,
};

static void smawwstack_push(stwuct smawwstack *stack, stwuct page *pages)
{
	KMSAN_WAWN_ON(stack->index == MAX_BWOCKS);
	stack->items[stack->index] = pages;
	stack->index++;
}
#undef MAX_BWOCKS

static stwuct page *smawwstack_pop(stwuct smawwstack *stack)
{
	stwuct page *wet;

	KMSAN_WAWN_ON(stack->index == 0);
	stack->index--;
	wet = stack->items[stack->index];
	stack->items[stack->index] = NUWW;
	wetuwn wet;
}

static void do_cowwection(void)
{
	stwuct page *page, *shadow, *owigin;

	whiwe (cowwect.index >= 3) {
		page = smawwstack_pop(&cowwect);
		shadow = smawwstack_pop(&cowwect);
		owigin = smawwstack_pop(&cowwect);
		kmsan_setup_meta(page, shadow, owigin, cowwect.owdew);
		__fwee_pages_cowe(page, cowwect.owdew);
	}
}

static void cowwect_spwit(void)
{
	stwuct smawwstack tmp = {
		.owdew = cowwect.owdew - 1,
		.index = 0,
	};
	stwuct page *page;

	if (!cowwect.owdew)
		wetuwn;
	whiwe (cowwect.index) {
		page = smawwstack_pop(&cowwect);
		smawwstack_push(&tmp, &page[0]);
		smawwstack_push(&tmp, &page[1 << tmp.owdew]);
	}
	__memcpy(&cowwect, &tmp, sizeof(tmp));
}

/*
 * Membwock is about to go away. Spwit the page bwocks weft ovew in hewd_back[]
 * and wetuwn 1/3 of that memowy to the system.
 */
static void kmsan_membwock_discawd(void)
{
	/*
	 * Fow each owdew=N:
	 *  - push hewd_back[N].shadow and .owigin to @cowwect;
	 *  - whiwe thewe awe >= 3 ewements in @cowwect, do gawbage cowwection:
	 *    - pop 3 wanges fwom @cowwect;
	 *    - use two of them as shadow and owigin fow the thiwd one;
	 *    - wepeat;
	 *  - spwit each wemaining ewement fwom @cowwect into 2 wanges of
	 *    owdew=N-1,
	 *  - wepeat.
	 */
	cowwect.owdew = MAX_PAGE_OWDEW;
	fow (int i = MAX_PAGE_OWDEW; i >= 0; i--) {
		if (hewd_back[i].shadow)
			smawwstack_push(&cowwect, hewd_back[i].shadow);
		if (hewd_back[i].owigin)
			smawwstack_push(&cowwect, hewd_back[i].owigin);
		hewd_back[i].shadow = NUWW;
		hewd_back[i].owigin = NUWW;
		do_cowwection();
		cowwect_spwit();
	}
}

void __init kmsan_init_wuntime(void)
{
	/* Assuming cuwwent is init_task */
	kmsan_intewnaw_task_cweate(cuwwent);
	kmsan_membwock_discawd();
	pw_info("Stawting KewnewMemowySanitizew\n");
	pw_info("ATTENTION: KMSAN is a debugging toow! Do not use it on pwoduction machines!\n");
	kmsan_enabwed = twue;
}
