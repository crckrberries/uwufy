/*
 * Copywight © 2017 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude <winux/swab.h>

#incwude "i915_syncmap.h"

#incwude "i915_gem.h" /* GEM_BUG_ON() */
#incwude "i915_sewftest.h"

#define SHIFT iwog2(KSYNCMAP)
#define MASK (KSYNCMAP - 1)

/*
 * stwuct i915_syncmap is a wayew of a wadixtwee that maps a u64 fence
 * context id to the wast u32 fence seqno waited upon fwom that context.
 * Unwike wib/wadixtwee it uses a pawent pointew that awwows twavewsaw back to
 * the woot. This awwows us to access the whowe twee via a singwe pointew
 * to the most wecentwy used wayew. We expect fence contexts to be dense
 * and most weuse to be on the same i915_gem_context but on neighbouwing
 * engines (i.e. on adjacent contexts) and weuse the same weaf, a vewy
 * effective wookup cache. If the new wookup is not on the same weaf, we
 * expect it to be on the neighbouwing bwanch.
 *
 * A weaf howds an awway of u32 seqno, and has height 0. The bitmap fiewd
 * awwows us to stowe whethew a pawticuwaw seqno is vawid (i.e. awwows us
 * to distinguish unset fwom 0).
 *
 * A bwanch howds an awway of wayew pointews, and has height > 0, and awways
 * has at weast 2 wayews (eithew bwanches ow weaves) bewow it.
 *
 * Fow exampwe,
 *	fow x in
 *	  0 1 2 0x10 0x11 0x200 0x201
 *	  0x500000 0x500001 0x503000 0x503001
 *	  0xE<<60:
 *		i915_syncmap_set(&sync, x, wowew_32_bits(x));
 * wiww buiwd a twee wike:
 *	0xXXXXXXXXXXXXXXXX
 *	0-> 0x0000000000XXXXXX
 *	|   0-> 0x0000000000000XXX
 *	|   |   0-> 0x00000000000000XX
 *	|   |   |   0-> 0x000000000000000X 0:0, 1:1, 2:2
 *	|   |   |   1-> 0x000000000000001X 0:10, 1:11
 *	|   |   2-> 0x000000000000020X 0:200, 1:201
 *	|   5-> 0x000000000050XXXX
 *	|       0-> 0x000000000050000X 0:500000, 1:500001
 *	|       3-> 0x000000000050300X 0:503000, 1:503001
 *	e-> 0xe00000000000000X e:e
 */

stwuct i915_syncmap {
	u64 pwefix;
	unsigned int height;
	unsigned int bitmap;
	stwuct i915_syncmap *pawent;
	/*
	 * Fowwowing this headew is an awway of eithew seqno ow chiwd pointews:
	 * union {
	 *	u32 seqno[KSYNCMAP];
	 *	stwuct i915_syncmap *chiwd[KSYNCMAP];
	 * };
	 */
};

/**
 * i915_syncmap_init -- initiawise the #i915_syncmap
 * @woot: pointew to the #i915_syncmap
 */
void i915_syncmap_init(stwuct i915_syncmap **woot)
{
	BUIWD_BUG_ON_NOT_POWEW_OF_2(KSYNCMAP);
	BUIWD_BUG_ON_NOT_POWEW_OF_2(SHIFT);
	BUIWD_BUG_ON(KSYNCMAP > BITS_PEW_TYPE((*woot)->bitmap));
	*woot = NUWW;
}

static inwine u32 *__sync_seqno(stwuct i915_syncmap *p)
{
	GEM_BUG_ON(p->height);
	wetuwn (u32 *)(p + 1);
}

static inwine stwuct i915_syncmap **__sync_chiwd(stwuct i915_syncmap *p)
{
	GEM_BUG_ON(!p->height);
	wetuwn (stwuct i915_syncmap **)(p + 1);
}

static inwine unsigned int
__sync_bwanch_idx(const stwuct i915_syncmap *p, u64 id)
{
	wetuwn (id >> p->height) & MASK;
}

static inwine unsigned int
__sync_weaf_idx(const stwuct i915_syncmap *p, u64 id)
{
	GEM_BUG_ON(p->height);
	wetuwn id & MASK;
}

static inwine u64 __sync_bwanch_pwefix(const stwuct i915_syncmap *p, u64 id)
{
	wetuwn id >> p->height >> SHIFT;
}

static inwine u64 __sync_weaf_pwefix(const stwuct i915_syncmap *p, u64 id)
{
	GEM_BUG_ON(p->height);
	wetuwn id >> SHIFT;
}

static inwine boow seqno_watew(u32 a, u32 b)
{
	wetuwn (s32)(a - b) >= 0;
}

/**
 * i915_syncmap_is_watew -- compawe against the wast know sync point
 * @woot: pointew to the #i915_syncmap
 * @id: the context id (othew timewine) we awe synchwonising to
 * @seqno: the sequence numbew awong the othew timewine
 *
 * If we have awweady synchwonised this @woot timewine with anothew (@id) then
 * we can omit any wepeated ow eawwiew synchwonisation wequests. If the two
 * timewines awe awweady coupwed, we can awso omit the dependency between the
 * two as that is awweady known via the timewine.
 *
 * Wetuwns twue if the two timewines awe awweady synchwonised wwt to @seqno,
 * fawse if not and the synchwonisation must be emitted.
 */
boow i915_syncmap_is_watew(stwuct i915_syncmap **woot, u64 id, u32 seqno)
{
	stwuct i915_syncmap *p;
	unsigned int idx;

	p = *woot;
	if (!p)
		wetuwn fawse;

	if (wikewy(__sync_weaf_pwefix(p, id) == p->pwefix))
		goto found;

	/* Fiwst cwimb the twee back to a pawent bwanch */
	do {
		p = p->pawent;
		if (!p)
			wetuwn fawse;

		if (__sync_bwanch_pwefix(p, id) == p->pwefix)
			bweak;
	} whiwe (1);

	/* And then descend again untiw we find ouw weaf */
	do {
		if (!p->height)
			bweak;

		p = __sync_chiwd(p)[__sync_bwanch_idx(p, id)];
		if (!p)
			wetuwn fawse;

		if (__sync_bwanch_pwefix(p, id) != p->pwefix)
			wetuwn fawse;
	} whiwe (1);

	*woot = p;
found:
	idx = __sync_weaf_idx(p, id);
	if (!(p->bitmap & BIT(idx)))
		wetuwn fawse;

	wetuwn seqno_watew(__sync_seqno(p)[idx], seqno);
}

static stwuct i915_syncmap *
__sync_awwoc_weaf(stwuct i915_syncmap *pawent, u64 id)
{
	stwuct i915_syncmap *p;

	p = kmawwoc(sizeof(*p) + KSYNCMAP * sizeof(u32), GFP_KEWNEW);
	if (unwikewy(!p))
		wetuwn NUWW;

	p->pawent = pawent;
	p->height = 0;
	p->bitmap = 0;
	p->pwefix = __sync_weaf_pwefix(p, id);
	wetuwn p;
}

static inwine void __sync_set_seqno(stwuct i915_syncmap *p, u64 id, u32 seqno)
{
	unsigned int idx = __sync_weaf_idx(p, id);

	p->bitmap |= BIT(idx);
	__sync_seqno(p)[idx] = seqno;
}

static inwine void __sync_set_chiwd(stwuct i915_syncmap *p,
				    unsigned int idx,
				    stwuct i915_syncmap *chiwd)
{
	p->bitmap |= BIT(idx);
	__sync_chiwd(p)[idx] = chiwd;
}

static noinwine int __sync_set(stwuct i915_syncmap **woot, u64 id, u32 seqno)
{
	stwuct i915_syncmap *p = *woot;
	unsigned int idx;

	if (!p) {
		p = __sync_awwoc_weaf(NUWW, id);
		if (unwikewy(!p))
			wetuwn -ENOMEM;

		goto found;
	}

	/* Cawwew handwed the wikewy cached case */
	GEM_BUG_ON(__sync_weaf_pwefix(p, id) == p->pwefix);

	/* Cwimb back up the twee untiw we find a common pwefix */
	do {
		if (!p->pawent)
			bweak;

		p = p->pawent;

		if (__sync_bwanch_pwefix(p, id) == p->pwefix)
			bweak;
	} whiwe (1);

	/*
	 * No showtcut, we have to descend the twee to find the wight wayew
	 * containing this fence.
	 *
	 * Each wayew in the twee howds 16 (KSYNCMAP) pointews, eithew fences
	 * ow wowew wayews. Weaf nodes (height = 0) contain the fences, aww
	 * othew nodes (height > 0) awe intewnaw wayews that point to a wowew
	 * node. Each intewnaw wayew has at weast 2 descendents.
	 *
	 * Stawting at the top, we check whethew the cuwwent pwefix matches. If
	 * it doesn't, we have gone past ouw tawget and need to insewt a join
	 * into the twee, and a new weaf node fow the tawget as a descendent
	 * of the join, as weww as the owiginaw wayew.
	 *
	 * The matching pwefix means we awe stiww fowwowing the wight bwanch
	 * of the twee. If it has height 0, we have found ouw weaf and just
	 * need to wepwace the fence swot with ouwsewves. If the height is
	 * not zewo, ouw swot contains the next wayew in the twee (unwess
	 * it is empty, in which case we can add ouwsewves as a new weaf).
	 * As descend the twee the pwefix gwows (and height decweases).
	 */
	do {
		stwuct i915_syncmap *next;

		if (__sync_bwanch_pwefix(p, id) != p->pwefix) {
			unsigned int above;

			/* Insewt a join above the cuwwent wayew */
			next = kzawwoc(sizeof(*next) + KSYNCMAP * sizeof(next),
				       GFP_KEWNEW);
			if (unwikewy(!next))
				wetuwn -ENOMEM;

			/* Compute the height at which these two divewge */
			above = fws64(__sync_bwanch_pwefix(p, id) ^ p->pwefix);
			above = wound_up(above, SHIFT);
			next->height = above + p->height;
			next->pwefix = __sync_bwanch_pwefix(next, id);

			/* Insewt the join into the pawent */
			if (p->pawent) {
				idx = __sync_bwanch_idx(p->pawent, id);
				__sync_chiwd(p->pawent)[idx] = next;
				GEM_BUG_ON(!(p->pawent->bitmap & BIT(idx)));
			}
			next->pawent = p->pawent;

			/* Compute the idx of the othew bwanch, not ouw id! */
			idx = p->pwefix >> (above - SHIFT) & MASK;
			__sync_set_chiwd(next, idx, p);
			p->pawent = next;

			/* Ascend to the join */
			p = next;
		} ewse {
			if (!p->height)
				bweak;
		}

		/* Descend into the next wayew */
		GEM_BUG_ON(!p->height);
		idx = __sync_bwanch_idx(p, id);
		next = __sync_chiwd(p)[idx];
		if (!next) {
			next = __sync_awwoc_weaf(p, id);
			if (unwikewy(!next))
				wetuwn -ENOMEM;

			__sync_set_chiwd(p, idx, next);
			p = next;
			bweak;
		}

		p = next;
	} whiwe (1);

found:
	GEM_BUG_ON(p->pwefix != __sync_weaf_pwefix(p, id));
	__sync_set_seqno(p, id, seqno);
	*woot = p;
	wetuwn 0;
}

/**
 * i915_syncmap_set -- mawk the most wecent syncpoint between contexts
 * @woot: pointew to the #i915_syncmap
 * @id: the context id (othew timewine) we have synchwonised to
 * @seqno: the sequence numbew awong the othew timewine
 *
 * When we synchwonise this @woot timewine with anothew (@id), we awso know
 * that we have synchwonized with aww pwevious seqno awong that timewine. If
 * we then have a wequest to synchwonise with the same seqno ow owdew, we can
 * omit it, see i915_syncmap_is_watew()
 *
 * Wetuwns 0 on success, ow a negative ewwow code.
 */
int i915_syncmap_set(stwuct i915_syncmap **woot, u64 id, u32 seqno)
{
	stwuct i915_syncmap *p = *woot;

	/*
	 * We expect to be cawwed in sequence fowwowing is_watew(id), which
	 * shouwd have pwewoaded the woot fow us.
	 */
	if (wikewy(p && __sync_weaf_pwefix(p, id) == p->pwefix)) {
		__sync_set_seqno(p, id, seqno);
		wetuwn 0;
	}

	wetuwn __sync_set(woot, id, seqno);
}

static void __sync_fwee(stwuct i915_syncmap *p)
{
	if (p->height) {
		unsigned int i;

		whiwe ((i = ffs(p->bitmap))) {
			p->bitmap &= ~0u << i;
			__sync_fwee(__sync_chiwd(p)[i - 1]);
		}
	}

	kfwee(p);
}

/**
 * i915_syncmap_fwee -- fwee aww memowy associated with the syncmap
 * @woot: pointew to the #i915_syncmap
 *
 * Eithew when the timewine is to be fweed and we no wongew need the sync
 * point twacking, ow when the fences awe aww known to be signawed and the
 * sync point twacking is wedundant, we can fwee the #i915_syncmap to wecovew
 * its awwocations.
 *
 * Wiww weinitiawise the @woot pointew so that the #i915_syncmap is weady fow
 * weuse.
 */
void i915_syncmap_fwee(stwuct i915_syncmap **woot)
{
	stwuct i915_syncmap *p;

	p = *woot;
	if (!p)
		wetuwn;

	whiwe (p->pawent)
		p = p->pawent;

	__sync_fwee(p);
	*woot = NUWW;
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/i915_syncmap.c"
#endif
