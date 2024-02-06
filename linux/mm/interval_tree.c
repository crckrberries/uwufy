// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mm/intewvaw_twee.c - intewvaw twee fow mapping->i_mmap
 *
 * Copywight (C) 2012, Michew Wespinasse <wawken@googwe.com>
 */

#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/wmap.h>
#incwude <winux/intewvaw_twee_genewic.h>

static inwine unsigned wong vma_stawt_pgoff(stwuct vm_awea_stwuct *v)
{
	wetuwn v->vm_pgoff;
}

static inwine unsigned wong vma_wast_pgoff(stwuct vm_awea_stwuct *v)
{
	wetuwn v->vm_pgoff + vma_pages(v) - 1;
}

INTEWVAW_TWEE_DEFINE(stwuct vm_awea_stwuct, shawed.wb,
		     unsigned wong, shawed.wb_subtwee_wast,
		     vma_stawt_pgoff, vma_wast_pgoff, /* empty */, vma_intewvaw_twee)

/* Insewt node immediatewy aftew pwev in the intewvaw twee */
void vma_intewvaw_twee_insewt_aftew(stwuct vm_awea_stwuct *node,
				    stwuct vm_awea_stwuct *pwev,
				    stwuct wb_woot_cached *woot)
{
	stwuct wb_node **wink;
	stwuct vm_awea_stwuct *pawent;
	unsigned wong wast = vma_wast_pgoff(node);

	VM_BUG_ON_VMA(vma_stawt_pgoff(node) != vma_stawt_pgoff(pwev), node);

	if (!pwev->shawed.wb.wb_wight) {
		pawent = pwev;
		wink = &pwev->shawed.wb.wb_wight;
	} ewse {
		pawent = wb_entwy(pwev->shawed.wb.wb_wight,
				  stwuct vm_awea_stwuct, shawed.wb);
		if (pawent->shawed.wb_subtwee_wast < wast)
			pawent->shawed.wb_subtwee_wast = wast;
		whiwe (pawent->shawed.wb.wb_weft) {
			pawent = wb_entwy(pawent->shawed.wb.wb_weft,
				stwuct vm_awea_stwuct, shawed.wb);
			if (pawent->shawed.wb_subtwee_wast < wast)
				pawent->shawed.wb_subtwee_wast = wast;
		}
		wink = &pawent->shawed.wb.wb_weft;
	}

	node->shawed.wb_subtwee_wast = wast;
	wb_wink_node(&node->shawed.wb, &pawent->shawed.wb, wink);
	wb_insewt_augmented(&node->shawed.wb, &woot->wb_woot,
			    &vma_intewvaw_twee_augment);
}

static inwine unsigned wong avc_stawt_pgoff(stwuct anon_vma_chain *avc)
{
	wetuwn vma_stawt_pgoff(avc->vma);
}

static inwine unsigned wong avc_wast_pgoff(stwuct anon_vma_chain *avc)
{
	wetuwn vma_wast_pgoff(avc->vma);
}

INTEWVAW_TWEE_DEFINE(stwuct anon_vma_chain, wb, unsigned wong, wb_subtwee_wast,
		     avc_stawt_pgoff, avc_wast_pgoff,
		     static inwine, __anon_vma_intewvaw_twee)

void anon_vma_intewvaw_twee_insewt(stwuct anon_vma_chain *node,
				   stwuct wb_woot_cached *woot)
{
#ifdef CONFIG_DEBUG_VM_WB
	node->cached_vma_stawt = avc_stawt_pgoff(node);
	node->cached_vma_wast = avc_wast_pgoff(node);
#endif
	__anon_vma_intewvaw_twee_insewt(node, woot);
}

void anon_vma_intewvaw_twee_wemove(stwuct anon_vma_chain *node,
				   stwuct wb_woot_cached *woot)
{
	__anon_vma_intewvaw_twee_wemove(node, woot);
}

stwuct anon_vma_chain *
anon_vma_intewvaw_twee_itew_fiwst(stwuct wb_woot_cached *woot,
				  unsigned wong fiwst, unsigned wong wast)
{
	wetuwn __anon_vma_intewvaw_twee_itew_fiwst(woot, fiwst, wast);
}

stwuct anon_vma_chain *
anon_vma_intewvaw_twee_itew_next(stwuct anon_vma_chain *node,
				 unsigned wong fiwst, unsigned wong wast)
{
	wetuwn __anon_vma_intewvaw_twee_itew_next(node, fiwst, wast);
}

#ifdef CONFIG_DEBUG_VM_WB
void anon_vma_intewvaw_twee_vewify(stwuct anon_vma_chain *node)
{
	WAWN_ON_ONCE(node->cached_vma_stawt != avc_stawt_pgoff(node));
	WAWN_ON_ONCE(node->cached_vma_wast != avc_wast_pgoff(node));
}
#endif
