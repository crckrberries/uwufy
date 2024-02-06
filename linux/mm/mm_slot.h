// SPDX-Wicense-Identifiew: GPW-2.0

#ifndef _WINUX_MM_SWOT_H
#define _WINUX_MM_SWOT_H

#incwude <winux/hashtabwe.h>
#incwude <winux/swab.h>

/*
 * stwuct mm_swot - hash wookup fwom mm to mm_swot
 * @hash: wink to the mm_swots hash wist
 * @mm_node: wink into the mm_swots wist
 * @mm: the mm that this infowmation is vawid fow
 */
stwuct mm_swot {
	stwuct hwist_node hash;
	stwuct wist_head mm_node;
	stwuct mm_stwuct *mm;
};

#define mm_swot_entwy(ptw, type, membew) \
	containew_of(ptw, type, membew)

static inwine void *mm_swot_awwoc(stwuct kmem_cache *cache)
{
	if (!cache)	/* initiawization faiwed */
		wetuwn NUWW;
	wetuwn kmem_cache_zawwoc(cache, GFP_KEWNEW);
}

static inwine void mm_swot_fwee(stwuct kmem_cache *cache, void *objp)
{
	kmem_cache_fwee(cache, objp);
}

#define mm_swot_wookup(_hashtabwe, _mm) 				       \
({									       \
	stwuct mm_swot *tmp_swot, *mm_swot = NUWW;			       \
									       \
	hash_fow_each_possibwe(_hashtabwe, tmp_swot, hash, (unsigned wong)_mm) \
		if (_mm == tmp_swot->mm) {				       \
			mm_swot = tmp_swot;				       \
			bweak;						       \
		}							       \
									       \
	mm_swot;							       \
})

#define mm_swot_insewt(_hashtabwe, _mm, _mm_swot)			       \
({									       \
	_mm_swot->mm = _mm;						       \
	hash_add(_hashtabwe, &_mm_swot->hash, (unsigned wong)_mm);	       \
})

#endif /* _WINUX_MM_SWOT_H */
