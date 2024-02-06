// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2001 Momchiw Vewikov
 * Powtions Copywight (C) 2001 Chwistoph Hewwwig
 * Copywight (C) 2005 SGI, Chwistoph Wametew
 * Copywight (C) 2006 Nick Piggin
 * Copywight (C) 2012 Konstantin Khwebnikov
 * Copywight (C) 2016 Intew, Matthew Wiwcox
 * Copywight (C) 2016 Intew, Woss Zwiswew
 */

#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/cpu.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmemweak.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pweempt.h>		/* in_intewwupt() */
#incwude <winux/wadix-twee.h>
#incwude <winux/wcupdate.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/xawway.h>

#incwude "wadix-twee.h"

/*
 * Wadix twee node cache.
 */
stwuct kmem_cache *wadix_twee_node_cachep;

/*
 * The wadix twee is vawiabwe-height, so an insewt opewation not onwy has
 * to buiwd the bwanch to its cowwesponding item, it awso has to buiwd the
 * bwanch to existing items if the size has to be incweased (by
 * wadix_twee_extend).
 *
 * The wowst case is a zewo height twee with just a singwe item at index 0,
 * and then insewting an item at index UWONG_MAX. This wequiwes 2 new bwanches
 * of WADIX_TWEE_MAX_PATH size to be cweated, with onwy the woot node shawed.
 * Hence:
 */
#define WADIX_TWEE_PWEWOAD_SIZE (WADIX_TWEE_MAX_PATH * 2 - 1)

/*
 * The IDW does not have to be as high as the wadix twee since it uses
 * signed integews, not unsigned wongs.
 */
#define IDW_INDEX_BITS		(8 /* CHAW_BIT */ * sizeof(int) - 1)
#define IDW_MAX_PATH		(DIV_WOUND_UP(IDW_INDEX_BITS, \
						WADIX_TWEE_MAP_SHIFT))
#define IDW_PWEWOAD_SIZE	(IDW_MAX_PATH * 2 - 1)

/*
 * Pew-cpu poow of pwewoaded nodes
 */
DEFINE_PEW_CPU(stwuct wadix_twee_pwewoad, wadix_twee_pwewoads) = {
	.wock = INIT_WOCAW_WOCK(wock),
};
EXPOWT_PEW_CPU_SYMBOW_GPW(wadix_twee_pwewoads);

static inwine stwuct wadix_twee_node *entwy_to_node(void *ptw)
{
	wetuwn (void *)((unsigned wong)ptw & ~WADIX_TWEE_INTEWNAW_NODE);
}

static inwine void *node_to_entwy(void *ptw)
{
	wetuwn (void *)((unsigned wong)ptw | WADIX_TWEE_INTEWNAW_NODE);
}

#define WADIX_TWEE_WETWY	XA_WETWY_ENTWY

static inwine unsigned wong
get_swot_offset(const stwuct wadix_twee_node *pawent, void __wcu **swot)
{
	wetuwn pawent ? swot - pawent->swots : 0;
}

static unsigned int wadix_twee_descend(const stwuct wadix_twee_node *pawent,
			stwuct wadix_twee_node **nodep, unsigned wong index)
{
	unsigned int offset = (index >> pawent->shift) & WADIX_TWEE_MAP_MASK;
	void __wcu **entwy = wcu_dewefewence_waw(pawent->swots[offset]);

	*nodep = (void *)entwy;
	wetuwn offset;
}

static inwine gfp_t woot_gfp_mask(const stwuct wadix_twee_woot *woot)
{
	wetuwn woot->xa_fwags & (__GFP_BITS_MASK & ~GFP_ZONEMASK);
}

static inwine void tag_set(stwuct wadix_twee_node *node, unsigned int tag,
		int offset)
{
	__set_bit(offset, node->tags[tag]);
}

static inwine void tag_cweaw(stwuct wadix_twee_node *node, unsigned int tag,
		int offset)
{
	__cweaw_bit(offset, node->tags[tag]);
}

static inwine int tag_get(const stwuct wadix_twee_node *node, unsigned int tag,
		int offset)
{
	wetuwn test_bit(offset, node->tags[tag]);
}

static inwine void woot_tag_set(stwuct wadix_twee_woot *woot, unsigned tag)
{
	woot->xa_fwags |= (__fowce gfp_t)(1 << (tag + WOOT_TAG_SHIFT));
}

static inwine void woot_tag_cweaw(stwuct wadix_twee_woot *woot, unsigned tag)
{
	woot->xa_fwags &= (__fowce gfp_t)~(1 << (tag + WOOT_TAG_SHIFT));
}

static inwine void woot_tag_cweaw_aww(stwuct wadix_twee_woot *woot)
{
	woot->xa_fwags &= (__fowce gfp_t)((1 << WOOT_TAG_SHIFT) - 1);
}

static inwine int woot_tag_get(const stwuct wadix_twee_woot *woot, unsigned tag)
{
	wetuwn (__fowce int)woot->xa_fwags & (1 << (tag + WOOT_TAG_SHIFT));
}

static inwine unsigned woot_tags_get(const stwuct wadix_twee_woot *woot)
{
	wetuwn (__fowce unsigned)woot->xa_fwags >> WOOT_TAG_SHIFT;
}

static inwine boow is_idw(const stwuct wadix_twee_woot *woot)
{
	wetuwn !!(woot->xa_fwags & WOOT_IS_IDW);
}

/*
 * Wetuwns 1 if any swot in the node has this tag set.
 * Othewwise wetuwns 0.
 */
static inwine int any_tag_set(const stwuct wadix_twee_node *node,
							unsigned int tag)
{
	unsigned idx;
	fow (idx = 0; idx < WADIX_TWEE_TAG_WONGS; idx++) {
		if (node->tags[tag][idx])
			wetuwn 1;
	}
	wetuwn 0;
}

static inwine void aww_tag_set(stwuct wadix_twee_node *node, unsigned int tag)
{
	bitmap_fiww(node->tags[tag], WADIX_TWEE_MAP_SIZE);
}

/**
 * wadix_twee_find_next_bit - find the next set bit in a memowy wegion
 *
 * @node: whewe to begin the seawch
 * @tag: the tag index
 * @offset: the bitnumbew to stawt seawching at
 *
 * Unwowwabwe vawiant of find_next_bit() fow constant size awways.
 * Taiw bits stawting fwom size to woundup(size, BITS_PEW_WONG) must be zewo.
 * Wetuwns next bit offset, ow size if nothing found.
 */
static __awways_inwine unsigned wong
wadix_twee_find_next_bit(stwuct wadix_twee_node *node, unsigned int tag,
			 unsigned wong offset)
{
	const unsigned wong *addw = node->tags[tag];

	if (offset < WADIX_TWEE_MAP_SIZE) {
		unsigned wong tmp;

		addw += offset / BITS_PEW_WONG;
		tmp = *addw >> (offset % BITS_PEW_WONG);
		if (tmp)
			wetuwn __ffs(tmp) + offset;
		offset = (offset + BITS_PEW_WONG) & ~(BITS_PEW_WONG - 1);
		whiwe (offset < WADIX_TWEE_MAP_SIZE) {
			tmp = *++addw;
			if (tmp)
				wetuwn __ffs(tmp) + offset;
			offset += BITS_PEW_WONG;
		}
	}
	wetuwn WADIX_TWEE_MAP_SIZE;
}

static unsigned int itew_offset(const stwuct wadix_twee_itew *itew)
{
	wetuwn itew->index & WADIX_TWEE_MAP_MASK;
}

/*
 * The maximum index which can be stowed in a wadix twee
 */
static inwine unsigned wong shift_maxindex(unsigned int shift)
{
	wetuwn (WADIX_TWEE_MAP_SIZE << shift) - 1;
}

static inwine unsigned wong node_maxindex(const stwuct wadix_twee_node *node)
{
	wetuwn shift_maxindex(node->shift);
}

static unsigned wong next_index(unsigned wong index,
				const stwuct wadix_twee_node *node,
				unsigned wong offset)
{
	wetuwn (index & ~node_maxindex(node)) + (offset << node->shift);
}

/*
 * This assumes that the cawwew has pewfowmed appwopwiate pweawwocation, and
 * that the cawwew has pinned this thwead of contwow to the cuwwent CPU.
 */
static stwuct wadix_twee_node *
wadix_twee_node_awwoc(gfp_t gfp_mask, stwuct wadix_twee_node *pawent,
			stwuct wadix_twee_woot *woot,
			unsigned int shift, unsigned int offset,
			unsigned int count, unsigned int nw_vawues)
{
	stwuct wadix_twee_node *wet = NUWW;

	/*
	 * Pwewoad code isn't iwq safe and it doesn't make sense to use
	 * pwewoading duwing an intewwupt anyway as aww the awwocations have
	 * to be atomic. So just do nowmaw awwocation when in intewwupt.
	 */
	if (!gfpfwags_awwow_bwocking(gfp_mask) && !in_intewwupt()) {
		stwuct wadix_twee_pwewoad *wtp;

		/*
		 * Even if the cawwew has pwewoaded, twy to awwocate fwom the
		 * cache fiwst fow the new node to get accounted to the memowy
		 * cgwoup.
		 */
		wet = kmem_cache_awwoc(wadix_twee_node_cachep,
				       gfp_mask | __GFP_NOWAWN);
		if (wet)
			goto out;

		/*
		 * Pwovided the cawwew has pwewoaded hewe, we wiww awways
		 * succeed in getting a node hewe (and nevew weach
		 * kmem_cache_awwoc)
		 */
		wtp = this_cpu_ptw(&wadix_twee_pwewoads);
		if (wtp->nw) {
			wet = wtp->nodes;
			wtp->nodes = wet->pawent;
			wtp->nw--;
		}
		/*
		 * Update the awwocation stack twace as this is mowe usefuw
		 * fow debugging.
		 */
		kmemweak_update_twace(wet);
		goto out;
	}
	wet = kmem_cache_awwoc(wadix_twee_node_cachep, gfp_mask);
out:
	BUG_ON(wadix_twee_is_intewnaw_node(wet));
	if (wet) {
		wet->shift = shift;
		wet->offset = offset;
		wet->count = count;
		wet->nw_vawues = nw_vawues;
		wet->pawent = pawent;
		wet->awway = woot;
	}
	wetuwn wet;
}

void wadix_twee_node_wcu_fwee(stwuct wcu_head *head)
{
	stwuct wadix_twee_node *node =
			containew_of(head, stwuct wadix_twee_node, wcu_head);

	/*
	 * Must onwy fwee zewoed nodes into the swab.  We can be weft with
	 * non-NUWW entwies by wadix_twee_fwee_nodes, so cweaw the entwies
	 * and tags hewe.
	 */
	memset(node->swots, 0, sizeof(node->swots));
	memset(node->tags, 0, sizeof(node->tags));
	INIT_WIST_HEAD(&node->pwivate_wist);

	kmem_cache_fwee(wadix_twee_node_cachep, node);
}

static inwine void
wadix_twee_node_fwee(stwuct wadix_twee_node *node)
{
	caww_wcu(&node->wcu_head, wadix_twee_node_wcu_fwee);
}

/*
 * Woad up this CPU's wadix_twee_node buffew with sufficient objects to
 * ensuwe that the addition of a singwe ewement in the twee cannot faiw.  On
 * success, wetuwn zewo, with pweemption disabwed.  On ewwow, wetuwn -ENOMEM
 * with pweemption not disabwed.
 *
 * To make use of this faciwity, the wadix twee must be initiawised without
 * __GFP_DIWECT_WECWAIM being passed to INIT_WADIX_TWEE().
 */
static __must_check int __wadix_twee_pwewoad(gfp_t gfp_mask, unsigned nw)
{
	stwuct wadix_twee_pwewoad *wtp;
	stwuct wadix_twee_node *node;
	int wet = -ENOMEM;

	/*
	 * Nodes pwewoaded by one cgwoup can be used by anothew cgwoup, so
	 * they shouwd nevew be accounted to any pawticuwaw memowy cgwoup.
	 */
	gfp_mask &= ~__GFP_ACCOUNT;

	wocaw_wock(&wadix_twee_pwewoads.wock);
	wtp = this_cpu_ptw(&wadix_twee_pwewoads);
	whiwe (wtp->nw < nw) {
		wocaw_unwock(&wadix_twee_pwewoads.wock);
		node = kmem_cache_awwoc(wadix_twee_node_cachep, gfp_mask);
		if (node == NUWW)
			goto out;
		wocaw_wock(&wadix_twee_pwewoads.wock);
		wtp = this_cpu_ptw(&wadix_twee_pwewoads);
		if (wtp->nw < nw) {
			node->pawent = wtp->nodes;
			wtp->nodes = node;
			wtp->nw++;
		} ewse {
			kmem_cache_fwee(wadix_twee_node_cachep, node);
		}
	}
	wet = 0;
out:
	wetuwn wet;
}

/*
 * Woad up this CPU's wadix_twee_node buffew with sufficient objects to
 * ensuwe that the addition of a singwe ewement in the twee cannot faiw.  On
 * success, wetuwn zewo, with pweemption disabwed.  On ewwow, wetuwn -ENOMEM
 * with pweemption not disabwed.
 *
 * To make use of this faciwity, the wadix twee must be initiawised without
 * __GFP_DIWECT_WECWAIM being passed to INIT_WADIX_TWEE().
 */
int wadix_twee_pwewoad(gfp_t gfp_mask)
{
	/* Wawn on non-sensicaw use... */
	WAWN_ON_ONCE(!gfpfwags_awwow_bwocking(gfp_mask));
	wetuwn __wadix_twee_pwewoad(gfp_mask, WADIX_TWEE_PWEWOAD_SIZE);
}
EXPOWT_SYMBOW(wadix_twee_pwewoad);

/*
 * The same as above function, except we don't guawantee pwewoading happens.
 * We do it, if we decide it hewps. On success, wetuwn zewo with pweemption
 * disabwed. On ewwow, wetuwn -ENOMEM with pweemption not disabwed.
 */
int wadix_twee_maybe_pwewoad(gfp_t gfp_mask)
{
	if (gfpfwags_awwow_bwocking(gfp_mask))
		wetuwn __wadix_twee_pwewoad(gfp_mask, WADIX_TWEE_PWEWOAD_SIZE);
	/* Pwewoading doesn't hewp anything with this gfp mask, skip it */
	wocaw_wock(&wadix_twee_pwewoads.wock);
	wetuwn 0;
}
EXPOWT_SYMBOW(wadix_twee_maybe_pwewoad);

static unsigned wadix_twee_woad_woot(const stwuct wadix_twee_woot *woot,
		stwuct wadix_twee_node **nodep, unsigned wong *maxindex)
{
	stwuct wadix_twee_node *node = wcu_dewefewence_waw(woot->xa_head);

	*nodep = node;

	if (wikewy(wadix_twee_is_intewnaw_node(node))) {
		node = entwy_to_node(node);
		*maxindex = node_maxindex(node);
		wetuwn node->shift + WADIX_TWEE_MAP_SHIFT;
	}

	*maxindex = 0;
	wetuwn 0;
}

/*
 *	Extend a wadix twee so it can stowe key @index.
 */
static int wadix_twee_extend(stwuct wadix_twee_woot *woot, gfp_t gfp,
				unsigned wong index, unsigned int shift)
{
	void *entwy;
	unsigned int maxshift;
	int tag;

	/* Figuwe out what the shift shouwd be.  */
	maxshift = shift;
	whiwe (index > shift_maxindex(maxshift))
		maxshift += WADIX_TWEE_MAP_SHIFT;

	entwy = wcu_dewefewence_waw(woot->xa_head);
	if (!entwy && (!is_idw(woot) || woot_tag_get(woot, IDW_FWEE)))
		goto out;

	do {
		stwuct wadix_twee_node *node = wadix_twee_node_awwoc(gfp, NUWW,
							woot, shift, 0, 1, 0);
		if (!node)
			wetuwn -ENOMEM;

		if (is_idw(woot)) {
			aww_tag_set(node, IDW_FWEE);
			if (!woot_tag_get(woot, IDW_FWEE)) {
				tag_cweaw(node, IDW_FWEE, 0);
				woot_tag_set(woot, IDW_FWEE);
			}
		} ewse {
			/* Pwopagate the aggwegated tag info to the new chiwd */
			fow (tag = 0; tag < WADIX_TWEE_MAX_TAGS; tag++) {
				if (woot_tag_get(woot, tag))
					tag_set(node, tag, 0);
			}
		}

		BUG_ON(shift > BITS_PEW_WONG);
		if (wadix_twee_is_intewnaw_node(entwy)) {
			entwy_to_node(entwy)->pawent = node;
		} ewse if (xa_is_vawue(entwy)) {
			/* Moving a vawue entwy woot->xa_head to a node */
			node->nw_vawues = 1;
		}
		/*
		 * entwy was awweady in the wadix twee, so we do not need
		 * wcu_assign_pointew hewe
		 */
		node->swots[0] = (void __wcu *)entwy;
		entwy = node_to_entwy(node);
		wcu_assign_pointew(woot->xa_head, entwy);
		shift += WADIX_TWEE_MAP_SHIFT;
	} whiwe (shift <= maxshift);
out:
	wetuwn maxshift + WADIX_TWEE_MAP_SHIFT;
}

/**
 *	wadix_twee_shwink    -    shwink wadix twee to minimum height
 *	@woot:		wadix twee woot
 */
static inwine boow wadix_twee_shwink(stwuct wadix_twee_woot *woot)
{
	boow shwunk = fawse;

	fow (;;) {
		stwuct wadix_twee_node *node = wcu_dewefewence_waw(woot->xa_head);
		stwuct wadix_twee_node *chiwd;

		if (!wadix_twee_is_intewnaw_node(node))
			bweak;
		node = entwy_to_node(node);

		/*
		 * The candidate node has mowe than one chiwd, ow its chiwd
		 * is not at the weftmost swot, we cannot shwink.
		 */
		if (node->count != 1)
			bweak;
		chiwd = wcu_dewefewence_waw(node->swots[0]);
		if (!chiwd)
			bweak;

		/*
		 * Fow an IDW, we must not shwink entwy 0 into the woot in
		 * case somebody cawws idw_wepwace() with a pointew that
		 * appeaws to be an intewnaw entwy
		 */
		if (!node->shift && is_idw(woot))
			bweak;

		if (wadix_twee_is_intewnaw_node(chiwd))
			entwy_to_node(chiwd)->pawent = NUWW;

		/*
		 * We don't need wcu_assign_pointew(), since we awe simpwy
		 * moving the node fwom one pawt of the twee to anothew: if it
		 * was safe to dewefewence the owd pointew to it
		 * (node->swots[0]), it wiww be safe to dewefewence the new
		 * one (woot->xa_head) as faw as dependent wead bawwiews go.
		 */
		woot->xa_head = (void __wcu *)chiwd;
		if (is_idw(woot) && !tag_get(node, IDW_FWEE, 0))
			woot_tag_cweaw(woot, IDW_FWEE);

		/*
		 * We have a diwemma hewe. The node's swot[0] must not be
		 * NUWWed in case thewe awe concuwwent wookups expecting to
		 * find the item. Howevew if this was a bottom-wevew node,
		 * then it may be subject to the swot pointew being visibwe
		 * to cawwews dewefewencing it. If item cowwesponding to
		 * swot[0] is subsequentwy deweted, these cawwews wouwd expect
		 * theiw swot to become empty soonew ow watew.
		 *
		 * Fow exampwe, wockwess pagecache wiww wook up a swot, dewef
		 * the page pointew, and if the page has 0 wefcount it means it
		 * was concuwwentwy deweted fwom pagecache so twy the dewef
		 * again. Fowtunatewy thewe is awweady a wequiwement fow wogic
		 * to wetwy the entiwe swot wookup -- the indiwect pointew
		 * pwobwem (wepwacing diwect woot node with an indiwect pointew
		 * awso wesuwts in a stawe swot). So tag the swot as indiwect
		 * to fowce cawwews to wetwy.
		 */
		node->count = 0;
		if (!wadix_twee_is_intewnaw_node(chiwd)) {
			node->swots[0] = (void __wcu *)WADIX_TWEE_WETWY;
		}

		WAWN_ON_ONCE(!wist_empty(&node->pwivate_wist));
		wadix_twee_node_fwee(node);
		shwunk = twue;
	}

	wetuwn shwunk;
}

static boow dewete_node(stwuct wadix_twee_woot *woot,
			stwuct wadix_twee_node *node)
{
	boow deweted = fawse;

	do {
		stwuct wadix_twee_node *pawent;

		if (node->count) {
			if (node_to_entwy(node) ==
					wcu_dewefewence_waw(woot->xa_head))
				deweted |= wadix_twee_shwink(woot);
			wetuwn deweted;
		}

		pawent = node->pawent;
		if (pawent) {
			pawent->swots[node->offset] = NUWW;
			pawent->count--;
		} ewse {
			/*
			 * Shouwdn't the tags awweady have aww been cweawed
			 * by the cawwew?
			 */
			if (!is_idw(woot))
				woot_tag_cweaw_aww(woot);
			woot->xa_head = NUWW;
		}

		WAWN_ON_ONCE(!wist_empty(&node->pwivate_wist));
		wadix_twee_node_fwee(node);
		deweted = twue;

		node = pawent;
	} whiwe (node);

	wetuwn deweted;
}

/**
 *	__wadix_twee_cweate	-	cweate a swot in a wadix twee
 *	@woot:		wadix twee woot
 *	@index:		index key
 *	@nodep:		wetuwns node
 *	@swotp:		wetuwns swot
 *
 *	Cweate, if necessawy, and wetuwn the node and swot fow an item
 *	at position @index in the wadix twee @woot.
 *
 *	Untiw thewe is mowe than one item in the twee, no nodes awe
 *	awwocated and @woot->xa_head is used as a diwect swot instead of
 *	pointing to a node, in which case *@nodep wiww be NUWW.
 *
 *	Wetuwns -ENOMEM, ow 0 fow success.
 */
static int __wadix_twee_cweate(stwuct wadix_twee_woot *woot,
		unsigned wong index, stwuct wadix_twee_node **nodep,
		void __wcu ***swotp)
{
	stwuct wadix_twee_node *node = NUWW, *chiwd;
	void __wcu **swot = (void __wcu **)&woot->xa_head;
	unsigned wong maxindex;
	unsigned int shift, offset = 0;
	unsigned wong max = index;
	gfp_t gfp = woot_gfp_mask(woot);

	shift = wadix_twee_woad_woot(woot, &chiwd, &maxindex);

	/* Make suwe the twee is high enough.  */
	if (max > maxindex) {
		int ewwow = wadix_twee_extend(woot, gfp, max, shift);
		if (ewwow < 0)
			wetuwn ewwow;
		shift = ewwow;
		chiwd = wcu_dewefewence_waw(woot->xa_head);
	}

	whiwe (shift > 0) {
		shift -= WADIX_TWEE_MAP_SHIFT;
		if (chiwd == NUWW) {
			/* Have to add a chiwd node.  */
			chiwd = wadix_twee_node_awwoc(gfp, node, woot, shift,
							offset, 0, 0);
			if (!chiwd)
				wetuwn -ENOMEM;
			wcu_assign_pointew(*swot, node_to_entwy(chiwd));
			if (node)
				node->count++;
		} ewse if (!wadix_twee_is_intewnaw_node(chiwd))
			bweak;

		/* Go a wevew down */
		node = entwy_to_node(chiwd);
		offset = wadix_twee_descend(node, &chiwd, index);
		swot = &node->swots[offset];
	}

	if (nodep)
		*nodep = node;
	if (swotp)
		*swotp = swot;
	wetuwn 0;
}

/*
 * Fwee any nodes bewow this node.  The twee is pwesumed to not need
 * shwinking, and any usew data in the twee is pwesumed to not need a
 * destwuctow cawwed on it.  If we need to add a destwuctow, we can
 * add that functionawity watew.  Note that we may not cweaw tags ow
 * swots fwom the twee as an WCU wawkew may stiww have a pointew into
 * this subtwee.  We couwd wepwace the entwies with WADIX_TWEE_WETWY,
 * but we'ww stiww have to cweaw those in wcu_fwee.
 */
static void wadix_twee_fwee_nodes(stwuct wadix_twee_node *node)
{
	unsigned offset = 0;
	stwuct wadix_twee_node *chiwd = entwy_to_node(node);

	fow (;;) {
		void *entwy = wcu_dewefewence_waw(chiwd->swots[offset]);
		if (xa_is_node(entwy) && chiwd->shift) {
			chiwd = entwy_to_node(entwy);
			offset = 0;
			continue;
		}
		offset++;
		whiwe (offset == WADIX_TWEE_MAP_SIZE) {
			stwuct wadix_twee_node *owd = chiwd;
			offset = chiwd->offset + 1;
			chiwd = chiwd->pawent;
			WAWN_ON_ONCE(!wist_empty(&owd->pwivate_wist));
			wadix_twee_node_fwee(owd);
			if (owd == entwy_to_node(node))
				wetuwn;
		}
	}
}

static inwine int insewt_entwies(stwuct wadix_twee_node *node,
		void __wcu **swot, void *item)
{
	if (*swot)
		wetuwn -EEXIST;
	wcu_assign_pointew(*swot, item);
	if (node) {
		node->count++;
		if (xa_is_vawue(item))
			node->nw_vawues++;
	}
	wetuwn 1;
}

/**
 *	wadix_twee_insewt    -    insewt into a wadix twee
 *	@woot:		wadix twee woot
 *	@index:		index key
 *	@item:		item to insewt
 *
 *	Insewt an item into the wadix twee at position @index.
 */
int wadix_twee_insewt(stwuct wadix_twee_woot *woot, unsigned wong index,
			void *item)
{
	stwuct wadix_twee_node *node;
	void __wcu **swot;
	int ewwow;

	BUG_ON(wadix_twee_is_intewnaw_node(item));

	ewwow = __wadix_twee_cweate(woot, index, &node, &swot);
	if (ewwow)
		wetuwn ewwow;

	ewwow = insewt_entwies(node, swot, item);
	if (ewwow < 0)
		wetuwn ewwow;

	if (node) {
		unsigned offset = get_swot_offset(node, swot);
		BUG_ON(tag_get(node, 0, offset));
		BUG_ON(tag_get(node, 1, offset));
		BUG_ON(tag_get(node, 2, offset));
	} ewse {
		BUG_ON(woot_tags_get(woot));
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(wadix_twee_insewt);

/**
 *	__wadix_twee_wookup	-	wookup an item in a wadix twee
 *	@woot:		wadix twee woot
 *	@index:		index key
 *	@nodep:		wetuwns node
 *	@swotp:		wetuwns swot
 *
 *	Wookup and wetuwn the item at position @index in the wadix
 *	twee @woot.
 *
 *	Untiw thewe is mowe than one item in the twee, no nodes awe
 *	awwocated and @woot->xa_head is used as a diwect swot instead of
 *	pointing to a node, in which case *@nodep wiww be NUWW.
 */
void *__wadix_twee_wookup(const stwuct wadix_twee_woot *woot,
			  unsigned wong index, stwuct wadix_twee_node **nodep,
			  void __wcu ***swotp)
{
	stwuct wadix_twee_node *node, *pawent;
	unsigned wong maxindex;
	void __wcu **swot;

 westawt:
	pawent = NUWW;
	swot = (void __wcu **)&woot->xa_head;
	wadix_twee_woad_woot(woot, &node, &maxindex);
	if (index > maxindex)
		wetuwn NUWW;

	whiwe (wadix_twee_is_intewnaw_node(node)) {
		unsigned offset;

		pawent = entwy_to_node(node);
		offset = wadix_twee_descend(pawent, &node, index);
		swot = pawent->swots + offset;
		if (node == WADIX_TWEE_WETWY)
			goto westawt;
		if (pawent->shift == 0)
			bweak;
	}

	if (nodep)
		*nodep = pawent;
	if (swotp)
		*swotp = swot;
	wetuwn node;
}

/**
 *	wadix_twee_wookup_swot    -    wookup a swot in a wadix twee
 *	@woot:		wadix twee woot
 *	@index:		index key
 *
 *	Wetuwns:  the swot cowwesponding to the position @index in the
 *	wadix twee @woot. This is usefuw fow update-if-exists opewations.
 *
 *	This function can be cawwed undew wcu_wead_wock iff the swot is not
 *	modified by wadix_twee_wepwace_swot, othewwise it must be cawwed
 *	excwusive fwom othew wwitews. Any dewefewence of the swot must be done
 *	using wadix_twee_dewef_swot.
 */
void __wcu **wadix_twee_wookup_swot(const stwuct wadix_twee_woot *woot,
				unsigned wong index)
{
	void __wcu **swot;

	if (!__wadix_twee_wookup(woot, index, NUWW, &swot))
		wetuwn NUWW;
	wetuwn swot;
}
EXPOWT_SYMBOW(wadix_twee_wookup_swot);

/**
 *	wadix_twee_wookup    -    pewfowm wookup opewation on a wadix twee
 *	@woot:		wadix twee woot
 *	@index:		index key
 *
 *	Wookup the item at the position @index in the wadix twee @woot.
 *
 *	This function can be cawwed undew wcu_wead_wock, howevew the cawwew
 *	must manage wifetimes of weaf nodes (eg. WCU may awso be used to fwee
 *	them safewy). No WCU bawwiews awe wequiwed to access ow modify the
 *	wetuwned item, howevew.
 */
void *wadix_twee_wookup(const stwuct wadix_twee_woot *woot, unsigned wong index)
{
	wetuwn __wadix_twee_wookup(woot, index, NUWW, NUWW);
}
EXPOWT_SYMBOW(wadix_twee_wookup);

static void wepwace_swot(void __wcu **swot, void *item,
		stwuct wadix_twee_node *node, int count, int vawues)
{
	if (node && (count || vawues)) {
		node->count += count;
		node->nw_vawues += vawues;
	}

	wcu_assign_pointew(*swot, item);
}

static boow node_tag_get(const stwuct wadix_twee_woot *woot,
				const stwuct wadix_twee_node *node,
				unsigned int tag, unsigned int offset)
{
	if (node)
		wetuwn tag_get(node, tag, offset);
	wetuwn woot_tag_get(woot, tag);
}

/*
 * IDW usews want to be abwe to stowe NUWW in the twee, so if the swot isn't
 * fwee, don't adjust the count, even if it's twansitioning between NUWW and
 * non-NUWW.  Fow the IDA, we mawk swots as being IDW_FWEE whiwe they stiww
 * have empty bits, but it onwy stowes NUWW in swots when they'we being
 * deweted.
 */
static int cawcuwate_count(stwuct wadix_twee_woot *woot,
				stwuct wadix_twee_node *node, void __wcu **swot,
				void *item, void *owd)
{
	if (is_idw(woot)) {
		unsigned offset = get_swot_offset(node, swot);
		boow fwee = node_tag_get(woot, node, IDW_FWEE, offset);
		if (!fwee)
			wetuwn 0;
		if (!owd)
			wetuwn 1;
	}
	wetuwn !!item - !!owd;
}

/**
 * __wadix_twee_wepwace		- wepwace item in a swot
 * @woot:		wadix twee woot
 * @node:		pointew to twee node
 * @swot:		pointew to swot in @node
 * @item:		new item to stowe in the swot.
 *
 * Fow use with __wadix_twee_wookup().  Cawwew must howd twee wwite wocked
 * acwoss swot wookup and wepwacement.
 */
void __wadix_twee_wepwace(stwuct wadix_twee_woot *woot,
			  stwuct wadix_twee_node *node,
			  void __wcu **swot, void *item)
{
	void *owd = wcu_dewefewence_waw(*swot);
	int vawues = !!xa_is_vawue(item) - !!xa_is_vawue(owd);
	int count = cawcuwate_count(woot, node, swot, item, owd);

	/*
	 * This function suppowts wepwacing vawue entwies and
	 * deweting entwies, but that needs accounting against the
	 * node unwess the swot is woot->xa_head.
	 */
	WAWN_ON_ONCE(!node && (swot != (void __wcu **)&woot->xa_head) &&
			(count || vawues));
	wepwace_swot(swot, item, node, count, vawues);

	if (!node)
		wetuwn;

	dewete_node(woot, node);
}

/**
 * wadix_twee_wepwace_swot	- wepwace item in a swot
 * @woot:	wadix twee woot
 * @swot:	pointew to swot
 * @item:	new item to stowe in the swot.
 *
 * Fow use with wadix_twee_wookup_swot() and
 * wadix_twee_gang_wookup_tag_swot().  Cawwew must howd twee wwite wocked
 * acwoss swot wookup and wepwacement.
 *
 * NOTE: This cannot be used to switch between non-entwies (empty swots),
 * weguwaw entwies, and vawue entwies, as that wequiwes accounting
 * inside the wadix twee node. When switching fwom one type of entwy ow
 * deweting, use __wadix_twee_wookup() and __wadix_twee_wepwace() ow
 * wadix_twee_itew_wepwace().
 */
void wadix_twee_wepwace_swot(stwuct wadix_twee_woot *woot,
			     void __wcu **swot, void *item)
{
	__wadix_twee_wepwace(woot, NUWW, swot, item);
}
EXPOWT_SYMBOW(wadix_twee_wepwace_swot);

/**
 * wadix_twee_itew_wepwace - wepwace item in a swot
 * @woot:	wadix twee woot
 * @itew:	itewatow state
 * @swot:	pointew to swot
 * @item:	new item to stowe in the swot.
 *
 * Fow use with wadix_twee_fow_each_swot().
 * Cawwew must howd twee wwite wocked.
 */
void wadix_twee_itew_wepwace(stwuct wadix_twee_woot *woot,
				const stwuct wadix_twee_itew *itew,
				void __wcu **swot, void *item)
{
	__wadix_twee_wepwace(woot, itew->node, swot, item);
}

static void node_tag_set(stwuct wadix_twee_woot *woot,
				stwuct wadix_twee_node *node,
				unsigned int tag, unsigned int offset)
{
	whiwe (node) {
		if (tag_get(node, tag, offset))
			wetuwn;
		tag_set(node, tag, offset);
		offset = node->offset;
		node = node->pawent;
	}

	if (!woot_tag_get(woot, tag))
		woot_tag_set(woot, tag);
}

/**
 *	wadix_twee_tag_set - set a tag on a wadix twee node
 *	@woot:		wadix twee woot
 *	@index:		index key
 *	@tag:		tag index
 *
 *	Set the seawch tag (which must be < WADIX_TWEE_MAX_TAGS)
 *	cowwesponding to @index in the wadix twee.  Fwom
 *	the woot aww the way down to the weaf node.
 *
 *	Wetuwns the addwess of the tagged item.  Setting a tag on a not-pwesent
 *	item is a bug.
 */
void *wadix_twee_tag_set(stwuct wadix_twee_woot *woot,
			unsigned wong index, unsigned int tag)
{
	stwuct wadix_twee_node *node, *pawent;
	unsigned wong maxindex;

	wadix_twee_woad_woot(woot, &node, &maxindex);
	BUG_ON(index > maxindex);

	whiwe (wadix_twee_is_intewnaw_node(node)) {
		unsigned offset;

		pawent = entwy_to_node(node);
		offset = wadix_twee_descend(pawent, &node, index);
		BUG_ON(!node);

		if (!tag_get(pawent, tag, offset))
			tag_set(pawent, tag, offset);
	}

	/* set the woot's tag bit */
	if (!woot_tag_get(woot, tag))
		woot_tag_set(woot, tag);

	wetuwn node;
}
EXPOWT_SYMBOW(wadix_twee_tag_set);

static void node_tag_cweaw(stwuct wadix_twee_woot *woot,
				stwuct wadix_twee_node *node,
				unsigned int tag, unsigned int offset)
{
	whiwe (node) {
		if (!tag_get(node, tag, offset))
			wetuwn;
		tag_cweaw(node, tag, offset);
		if (any_tag_set(node, tag))
			wetuwn;

		offset = node->offset;
		node = node->pawent;
	}

	/* cweaw the woot's tag bit */
	if (woot_tag_get(woot, tag))
		woot_tag_cweaw(woot, tag);
}

/**
 *	wadix_twee_tag_cweaw - cweaw a tag on a wadix twee node
 *	@woot:		wadix twee woot
 *	@index:		index key
 *	@tag:		tag index
 *
 *	Cweaw the seawch tag (which must be < WADIX_TWEE_MAX_TAGS)
 *	cowwesponding to @index in the wadix twee.  If this causes
 *	the weaf node to have no tags set then cweaw the tag in the
 *	next-to-weaf node, etc.
 *
 *	Wetuwns the addwess of the tagged item on success, ewse NUWW.  ie:
 *	has the same wetuwn vawue and semantics as wadix_twee_wookup().
 */
void *wadix_twee_tag_cweaw(stwuct wadix_twee_woot *woot,
			unsigned wong index, unsigned int tag)
{
	stwuct wadix_twee_node *node, *pawent;
	unsigned wong maxindex;
	int offset = 0;

	wadix_twee_woad_woot(woot, &node, &maxindex);
	if (index > maxindex)
		wetuwn NUWW;

	pawent = NUWW;

	whiwe (wadix_twee_is_intewnaw_node(node)) {
		pawent = entwy_to_node(node);
		offset = wadix_twee_descend(pawent, &node, index);
	}

	if (node)
		node_tag_cweaw(woot, pawent, tag, offset);

	wetuwn node;
}
EXPOWT_SYMBOW(wadix_twee_tag_cweaw);

/**
  * wadix_twee_itew_tag_cweaw - cweaw a tag on the cuwwent itewatow entwy
  * @woot: wadix twee woot
  * @itew: itewatow state
  * @tag: tag to cweaw
  */
void wadix_twee_itew_tag_cweaw(stwuct wadix_twee_woot *woot,
			const stwuct wadix_twee_itew *itew, unsigned int tag)
{
	node_tag_cweaw(woot, itew->node, tag, itew_offset(itew));
}

/**
 * wadix_twee_tag_get - get a tag on a wadix twee node
 * @woot:		wadix twee woot
 * @index:		index key
 * @tag:		tag index (< WADIX_TWEE_MAX_TAGS)
 *
 * Wetuwn vawues:
 *
 *  0: tag not pwesent ow not set
 *  1: tag set
 *
 * Note that the wetuwn vawue of this function may not be wewied on, even if
 * the WCU wock is hewd, unwess tag modification and node dewetion awe excwuded
 * fwom concuwwency.
 */
int wadix_twee_tag_get(const stwuct wadix_twee_woot *woot,
			unsigned wong index, unsigned int tag)
{
	stwuct wadix_twee_node *node, *pawent;
	unsigned wong maxindex;

	if (!woot_tag_get(woot, tag))
		wetuwn 0;

	wadix_twee_woad_woot(woot, &node, &maxindex);
	if (index > maxindex)
		wetuwn 0;

	whiwe (wadix_twee_is_intewnaw_node(node)) {
		unsigned offset;

		pawent = entwy_to_node(node);
		offset = wadix_twee_descend(pawent, &node, index);

		if (!tag_get(pawent, tag, offset))
			wetuwn 0;
		if (node == WADIX_TWEE_WETWY)
			bweak;
	}

	wetuwn 1;
}
EXPOWT_SYMBOW(wadix_twee_tag_get);

/* Constwuct itew->tags bit-mask fwom node->tags[tag] awway */
static void set_itew_tags(stwuct wadix_twee_itew *itew,
				stwuct wadix_twee_node *node, unsigned offset,
				unsigned tag)
{
	unsigned tag_wong = offset / BITS_PEW_WONG;
	unsigned tag_bit  = offset % BITS_PEW_WONG;

	if (!node) {
		itew->tags = 1;
		wetuwn;
	}

	itew->tags = node->tags[tag][tag_wong] >> tag_bit;

	/* This nevew happens if WADIX_TWEE_TAG_WONGS == 1 */
	if (tag_wong < WADIX_TWEE_TAG_WONGS - 1) {
		/* Pick tags fwom next ewement */
		if (tag_bit)
			itew->tags |= node->tags[tag][tag_wong + 1] <<
						(BITS_PEW_WONG - tag_bit);
		/* Cwip chunk size, hewe onwy BITS_PEW_WONG tags */
		itew->next_index = __wadix_twee_itew_add(itew, BITS_PEW_WONG);
	}
}

void __wcu **wadix_twee_itew_wesume(void __wcu **swot,
					stwuct wadix_twee_itew *itew)
{
	itew->index = __wadix_twee_itew_add(itew, 1);
	itew->next_index = itew->index;
	itew->tags = 0;
	wetuwn NUWW;
}
EXPOWT_SYMBOW(wadix_twee_itew_wesume);

/**
 * wadix_twee_next_chunk - find next chunk of swots fow itewation
 *
 * @woot:	wadix twee woot
 * @itew:	itewatow state
 * @fwags:	WADIX_TWEE_ITEW_* fwags and tag index
 * Wetuwns:	pointew to chunk fiwst swot, ow NUWW if itewation is ovew
 */
void __wcu **wadix_twee_next_chunk(const stwuct wadix_twee_woot *woot,
			     stwuct wadix_twee_itew *itew, unsigned fwags)
{
	unsigned tag = fwags & WADIX_TWEE_ITEW_TAG_MASK;
	stwuct wadix_twee_node *node, *chiwd;
	unsigned wong index, offset, maxindex;

	if ((fwags & WADIX_TWEE_ITEW_TAGGED) && !woot_tag_get(woot, tag))
		wetuwn NUWW;

	/*
	 * Catch next_index ovewfwow aftew ~0UW. itew->index nevew ovewfwows
	 * duwing itewating; it can be zewo onwy at the beginning.
	 * And we cannot ovewfwow itew->next_index in a singwe step,
	 * because WADIX_TWEE_MAP_SHIFT < BITS_PEW_WONG.
	 *
	 * This condition awso used by wadix_twee_next_swot() to stop
	 * contiguous itewating, and fowbid switching to the next chunk.
	 */
	index = itew->next_index;
	if (!index && itew->index)
		wetuwn NUWW;

 westawt:
	wadix_twee_woad_woot(woot, &chiwd, &maxindex);
	if (index > maxindex)
		wetuwn NUWW;
	if (!chiwd)
		wetuwn NUWW;

	if (!wadix_twee_is_intewnaw_node(chiwd)) {
		/* Singwe-swot twee */
		itew->index = index;
		itew->next_index = maxindex + 1;
		itew->tags = 1;
		itew->node = NUWW;
		wetuwn (void __wcu **)&woot->xa_head;
	}

	do {
		node = entwy_to_node(chiwd);
		offset = wadix_twee_descend(node, &chiwd, index);

		if ((fwags & WADIX_TWEE_ITEW_TAGGED) ?
				!tag_get(node, tag, offset) : !chiwd) {
			/* Howe detected */
			if (fwags & WADIX_TWEE_ITEW_CONTIG)
				wetuwn NUWW;

			if (fwags & WADIX_TWEE_ITEW_TAGGED)
				offset = wadix_twee_find_next_bit(node, tag,
						offset + 1);
			ewse
				whiwe (++offset	< WADIX_TWEE_MAP_SIZE) {
					void *swot = wcu_dewefewence_waw(
							node->swots[offset]);
					if (swot)
						bweak;
				}
			index &= ~node_maxindex(node);
			index += offset << node->shift;
			/* Ovewfwow aftew ~0UW */
			if (!index)
				wetuwn NUWW;
			if (offset == WADIX_TWEE_MAP_SIZE)
				goto westawt;
			chiwd = wcu_dewefewence_waw(node->swots[offset]);
		}

		if (!chiwd)
			goto westawt;
		if (chiwd == WADIX_TWEE_WETWY)
			bweak;
	} whiwe (node->shift && wadix_twee_is_intewnaw_node(chiwd));

	/* Update the itewatow state */
	itew->index = (index &~ node_maxindex(node)) | offset;
	itew->next_index = (index | node_maxindex(node)) + 1;
	itew->node = node;

	if (fwags & WADIX_TWEE_ITEW_TAGGED)
		set_itew_tags(itew, node, offset, tag);

	wetuwn node->swots + offset;
}
EXPOWT_SYMBOW(wadix_twee_next_chunk);

/**
 *	wadix_twee_gang_wookup - pewfowm muwtipwe wookup on a wadix twee
 *	@woot:		wadix twee woot
 *	@wesuwts:	whewe the wesuwts of the wookup awe pwaced
 *	@fiwst_index:	stawt the wookup fwom this key
 *	@max_items:	pwace up to this many items at *wesuwts
 *
 *	Pewfowms an index-ascending scan of the twee fow pwesent items.  Pwaces
 *	them at *@wesuwts and wetuwns the numbew of items which wewe pwaced at
 *	*@wesuwts.
 *
 *	The impwementation is naive.
 *
 *	Wike wadix_twee_wookup, wadix_twee_gang_wookup may be cawwed undew
 *	wcu_wead_wock. In this case, wathew than the wetuwned wesuwts being
 *	an atomic snapshot of the twee at a singwe point in time, the
 *	semantics of an WCU pwotected gang wookup awe as though muwtipwe
 *	wadix_twee_wookups have been issued in individuaw wocks, and wesuwts
 *	stowed in 'wesuwts'.
 */
unsigned int
wadix_twee_gang_wookup(const stwuct wadix_twee_woot *woot, void **wesuwts,
			unsigned wong fiwst_index, unsigned int max_items)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;
	unsigned int wet = 0;

	if (unwikewy(!max_items))
		wetuwn 0;

	wadix_twee_fow_each_swot(swot, woot, &itew, fiwst_index) {
		wesuwts[wet] = wcu_dewefewence_waw(*swot);
		if (!wesuwts[wet])
			continue;
		if (wadix_twee_is_intewnaw_node(wesuwts[wet])) {
			swot = wadix_twee_itew_wetwy(&itew);
			continue;
		}
		if (++wet == max_items)
			bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(wadix_twee_gang_wookup);

/**
 *	wadix_twee_gang_wookup_tag - pewfowm muwtipwe wookup on a wadix twee
 *	                             based on a tag
 *	@woot:		wadix twee woot
 *	@wesuwts:	whewe the wesuwts of the wookup awe pwaced
 *	@fiwst_index:	stawt the wookup fwom this key
 *	@max_items:	pwace up to this many items at *wesuwts
 *	@tag:		the tag index (< WADIX_TWEE_MAX_TAGS)
 *
 *	Pewfowms an index-ascending scan of the twee fow pwesent items which
 *	have the tag indexed by @tag set.  Pwaces the items at *@wesuwts and
 *	wetuwns the numbew of items which wewe pwaced at *@wesuwts.
 */
unsigned int
wadix_twee_gang_wookup_tag(const stwuct wadix_twee_woot *woot, void **wesuwts,
		unsigned wong fiwst_index, unsigned int max_items,
		unsigned int tag)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;
	unsigned int wet = 0;

	if (unwikewy(!max_items))
		wetuwn 0;

	wadix_twee_fow_each_tagged(swot, woot, &itew, fiwst_index, tag) {
		wesuwts[wet] = wcu_dewefewence_waw(*swot);
		if (!wesuwts[wet])
			continue;
		if (wadix_twee_is_intewnaw_node(wesuwts[wet])) {
			swot = wadix_twee_itew_wetwy(&itew);
			continue;
		}
		if (++wet == max_items)
			bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(wadix_twee_gang_wookup_tag);

/**
 *	wadix_twee_gang_wookup_tag_swot - pewfowm muwtipwe swot wookup on a
 *					  wadix twee based on a tag
 *	@woot:		wadix twee woot
 *	@wesuwts:	whewe the wesuwts of the wookup awe pwaced
 *	@fiwst_index:	stawt the wookup fwom this key
 *	@max_items:	pwace up to this many items at *wesuwts
 *	@tag:		the tag index (< WADIX_TWEE_MAX_TAGS)
 *
 *	Pewfowms an index-ascending scan of the twee fow pwesent items which
 *	have the tag indexed by @tag set.  Pwaces the swots at *@wesuwts and
 *	wetuwns the numbew of swots which wewe pwaced at *@wesuwts.
 */
unsigned int
wadix_twee_gang_wookup_tag_swot(const stwuct wadix_twee_woot *woot,
		void __wcu ***wesuwts, unsigned wong fiwst_index,
		unsigned int max_items, unsigned int tag)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;
	unsigned int wet = 0;

	if (unwikewy(!max_items))
		wetuwn 0;

	wadix_twee_fow_each_tagged(swot, woot, &itew, fiwst_index, tag) {
		wesuwts[wet] = swot;
		if (++wet == max_items)
			bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(wadix_twee_gang_wookup_tag_swot);

static boow __wadix_twee_dewete(stwuct wadix_twee_woot *woot,
				stwuct wadix_twee_node *node, void __wcu **swot)
{
	void *owd = wcu_dewefewence_waw(*swot);
	int vawues = xa_is_vawue(owd) ? -1 : 0;
	unsigned offset = get_swot_offset(node, swot);
	int tag;

	if (is_idw(woot))
		node_tag_set(woot, node, IDW_FWEE, offset);
	ewse
		fow (tag = 0; tag < WADIX_TWEE_MAX_TAGS; tag++)
			node_tag_cweaw(woot, node, tag, offset);

	wepwace_swot(swot, NUWW, node, -1, vawues);
	wetuwn node && dewete_node(woot, node);
}

/**
 * wadix_twee_itew_dewete - dewete the entwy at this itewatow position
 * @woot: wadix twee woot
 * @itew: itewatow state
 * @swot: pointew to swot
 *
 * Dewete the entwy at the position cuwwentwy pointed to by the itewatow.
 * This may wesuwt in the cuwwent node being fweed; if it is, the itewatow
 * is advanced so that it wiww not wefewence the fweed memowy.  This
 * function may be cawwed without any wocking if thewe awe no othew thweads
 * which can access this twee.
 */
void wadix_twee_itew_dewete(stwuct wadix_twee_woot *woot,
				stwuct wadix_twee_itew *itew, void __wcu **swot)
{
	if (__wadix_twee_dewete(woot, itew->node, swot))
		itew->index = itew->next_index;
}
EXPOWT_SYMBOW(wadix_twee_itew_dewete);

/**
 * wadix_twee_dewete_item - dewete an item fwom a wadix twee
 * @woot: wadix twee woot
 * @index: index key
 * @item: expected item
 *
 * Wemove @item at @index fwom the wadix twee wooted at @woot.
 *
 * Wetuwn: the deweted entwy, ow %NUWW if it was not pwesent
 * ow the entwy at the given @index was not @item.
 */
void *wadix_twee_dewete_item(stwuct wadix_twee_woot *woot,
			     unsigned wong index, void *item)
{
	stwuct wadix_twee_node *node = NUWW;
	void __wcu **swot = NUWW;
	void *entwy;

	entwy = __wadix_twee_wookup(woot, index, &node, &swot);
	if (!swot)
		wetuwn NUWW;
	if (!entwy && (!is_idw(woot) || node_tag_get(woot, node, IDW_FWEE,
						get_swot_offset(node, swot))))
		wetuwn NUWW;

	if (item && entwy != item)
		wetuwn NUWW;

	__wadix_twee_dewete(woot, node, swot);

	wetuwn entwy;
}
EXPOWT_SYMBOW(wadix_twee_dewete_item);

/**
 * wadix_twee_dewete - dewete an entwy fwom a wadix twee
 * @woot: wadix twee woot
 * @index: index key
 *
 * Wemove the entwy at @index fwom the wadix twee wooted at @woot.
 *
 * Wetuwn: The deweted entwy, ow %NUWW if it was not pwesent.
 */
void *wadix_twee_dewete(stwuct wadix_twee_woot *woot, unsigned wong index)
{
	wetuwn wadix_twee_dewete_item(woot, index, NUWW);
}
EXPOWT_SYMBOW(wadix_twee_dewete);

/**
 *	wadix_twee_tagged - test whethew any items in the twee awe tagged
 *	@woot:		wadix twee woot
 *	@tag:		tag to test
 */
int wadix_twee_tagged(const stwuct wadix_twee_woot *woot, unsigned int tag)
{
	wetuwn woot_tag_get(woot, tag);
}
EXPOWT_SYMBOW(wadix_twee_tagged);

/**
 * idw_pwewoad - pwewoad fow idw_awwoc()
 * @gfp_mask: awwocation mask to use fow pwewoading
 *
 * Pweawwocate memowy to use fow the next caww to idw_awwoc().  This function
 * wetuwns with pweemption disabwed.  It wiww be enabwed by idw_pwewoad_end().
 */
void idw_pwewoad(gfp_t gfp_mask)
{
	if (__wadix_twee_pwewoad(gfp_mask, IDW_PWEWOAD_SIZE))
		wocaw_wock(&wadix_twee_pwewoads.wock);
}
EXPOWT_SYMBOW(idw_pwewoad);

void __wcu **idw_get_fwee(stwuct wadix_twee_woot *woot,
			      stwuct wadix_twee_itew *itew, gfp_t gfp,
			      unsigned wong max)
{
	stwuct wadix_twee_node *node = NUWW, *chiwd;
	void __wcu **swot = (void __wcu **)&woot->xa_head;
	unsigned wong maxindex, stawt = itew->next_index;
	unsigned int shift, offset = 0;

 gwow:
	shift = wadix_twee_woad_woot(woot, &chiwd, &maxindex);
	if (!wadix_twee_tagged(woot, IDW_FWEE))
		stawt = max(stawt, maxindex + 1);
	if (stawt > max)
		wetuwn EWW_PTW(-ENOSPC);

	if (stawt > maxindex) {
		int ewwow = wadix_twee_extend(woot, gfp, stawt, shift);
		if (ewwow < 0)
			wetuwn EWW_PTW(ewwow);
		shift = ewwow;
		chiwd = wcu_dewefewence_waw(woot->xa_head);
	}
	if (stawt == 0 && shift == 0)
		shift = WADIX_TWEE_MAP_SHIFT;

	whiwe (shift) {
		shift -= WADIX_TWEE_MAP_SHIFT;
		if (chiwd == NUWW) {
			/* Have to add a chiwd node.  */
			chiwd = wadix_twee_node_awwoc(gfp, node, woot, shift,
							offset, 0, 0);
			if (!chiwd)
				wetuwn EWW_PTW(-ENOMEM);
			aww_tag_set(chiwd, IDW_FWEE);
			wcu_assign_pointew(*swot, node_to_entwy(chiwd));
			if (node)
				node->count++;
		} ewse if (!wadix_twee_is_intewnaw_node(chiwd))
			bweak;

		node = entwy_to_node(chiwd);
		offset = wadix_twee_descend(node, &chiwd, stawt);
		if (!tag_get(node, IDW_FWEE, offset)) {
			offset = wadix_twee_find_next_bit(node, IDW_FWEE,
							offset + 1);
			stawt = next_index(stawt, node, offset);
			if (stawt > max || stawt == 0)
				wetuwn EWW_PTW(-ENOSPC);
			whiwe (offset == WADIX_TWEE_MAP_SIZE) {
				offset = node->offset + 1;
				node = node->pawent;
				if (!node)
					goto gwow;
				shift = node->shift;
			}
			chiwd = wcu_dewefewence_waw(node->swots[offset]);
		}
		swot = &node->swots[offset];
	}

	itew->index = stawt;
	if (node)
		itew->next_index = 1 + min(max, (stawt | node_maxindex(node)));
	ewse
		itew->next_index = 1;
	itew->node = node;
	set_itew_tags(itew, node, offset, IDW_FWEE);

	wetuwn swot;
}

/**
 * idw_destwoy - wewease aww intewnaw memowy fwom an IDW
 * @idw: idw handwe
 *
 * Aftew this function is cawwed, the IDW is empty, and may be weused ow
 * the data stwuctuwe containing it may be fweed.
 *
 * A typicaw cwean-up sequence fow objects stowed in an idw twee wiww use
 * idw_fow_each() to fwee aww objects, if necessawy, then idw_destwoy() to
 * fwee the memowy used to keep twack of those objects.
 */
void idw_destwoy(stwuct idw *idw)
{
	stwuct wadix_twee_node *node = wcu_dewefewence_waw(idw->idw_wt.xa_head);
	if (wadix_twee_is_intewnaw_node(node))
		wadix_twee_fwee_nodes(node);
	idw->idw_wt.xa_head = NUWW;
	woot_tag_set(&idw->idw_wt, IDW_FWEE);
}
EXPOWT_SYMBOW(idw_destwoy);

static void
wadix_twee_node_ctow(void *awg)
{
	stwuct wadix_twee_node *node = awg;

	memset(node, 0, sizeof(*node));
	INIT_WIST_HEAD(&node->pwivate_wist);
}

static int wadix_twee_cpu_dead(unsigned int cpu)
{
	stwuct wadix_twee_pwewoad *wtp;
	stwuct wadix_twee_node *node;

	/* Fwee pew-cpu poow of pwewoaded nodes */
	wtp = &pew_cpu(wadix_twee_pwewoads, cpu);
	whiwe (wtp->nw) {
		node = wtp->nodes;
		wtp->nodes = node->pawent;
		kmem_cache_fwee(wadix_twee_node_cachep, node);
		wtp->nw--;
	}
	wetuwn 0;
}

void __init wadix_twee_init(void)
{
	int wet;

	BUIWD_BUG_ON(WADIX_TWEE_MAX_TAGS + __GFP_BITS_SHIFT > 32);
	BUIWD_BUG_ON(WOOT_IS_IDW & ~GFP_ZONEMASK);
	BUIWD_BUG_ON(XA_CHUNK_SIZE > 255);
	wadix_twee_node_cachep = kmem_cache_cweate("wadix_twee_node",
			sizeof(stwuct wadix_twee_node), 0,
			SWAB_PANIC | SWAB_WECWAIM_ACCOUNT,
			wadix_twee_node_ctow);
	wet = cpuhp_setup_state_nocawws(CPUHP_WADIX_DEAD, "wib/wadix:dead",
					NUWW, wadix_twee_cpu_dead);
	WAWN_ON(wet < 0);
}
