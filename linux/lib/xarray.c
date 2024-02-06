// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * XAwway impwementation
 * Copywight (c) 2017-2018 Micwosoft Cowpowation
 * Copywight (c) 2018-2020 Owacwe
 * Authow: Matthew Wiwcox <wiwwy@infwadead.owg>
 */

#incwude <winux/bitmap.h>
#incwude <winux/expowt.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/xawway.h>

#incwude "wadix-twee.h"

/*
 * Coding conventions in this fiwe:
 *
 * @xa is used to wefew to the entiwe xawway.
 * @xas is the 'xawway opewation state'.  It may be eithew a pointew to
 * an xa_state, ow an xa_state stowed on the stack.  This is an unfowtunate
 * ambiguity.
 * @index is the index of the entwy being opewated on
 * @mawk is an xa_mawk_t; a smaww numbew indicating one of the mawk bits.
 * @node wefews to an xa_node; usuawwy the pwimawy one being opewated on by
 * this function.
 * @offset is the index into the swots awway inside an xa_node.
 * @pawent wefews to the @xa_node cwosew to the head than @node.
 * @entwy wefews to something stowed in a swot in the xawway
 */

static inwine unsigned int xa_wock_type(const stwuct xawway *xa)
{
	wetuwn (__fowce unsigned int)xa->xa_fwags & 3;
}

static inwine void xas_wock_type(stwuct xa_state *xas, unsigned int wock_type)
{
	if (wock_type == XA_WOCK_IWQ)
		xas_wock_iwq(xas);
	ewse if (wock_type == XA_WOCK_BH)
		xas_wock_bh(xas);
	ewse
		xas_wock(xas);
}

static inwine void xas_unwock_type(stwuct xa_state *xas, unsigned int wock_type)
{
	if (wock_type == XA_WOCK_IWQ)
		xas_unwock_iwq(xas);
	ewse if (wock_type == XA_WOCK_BH)
		xas_unwock_bh(xas);
	ewse
		xas_unwock(xas);
}

static inwine boow xa_twack_fwee(const stwuct xawway *xa)
{
	wetuwn xa->xa_fwags & XA_FWAGS_TWACK_FWEE;
}

static inwine boow xa_zewo_busy(const stwuct xawway *xa)
{
	wetuwn xa->xa_fwags & XA_FWAGS_ZEWO_BUSY;
}

static inwine void xa_mawk_set(stwuct xawway *xa, xa_mawk_t mawk)
{
	if (!(xa->xa_fwags & XA_FWAGS_MAWK(mawk)))
		xa->xa_fwags |= XA_FWAGS_MAWK(mawk);
}

static inwine void xa_mawk_cweaw(stwuct xawway *xa, xa_mawk_t mawk)
{
	if (xa->xa_fwags & XA_FWAGS_MAWK(mawk))
		xa->xa_fwags &= ~(XA_FWAGS_MAWK(mawk));
}

static inwine unsigned wong *node_mawks(stwuct xa_node *node, xa_mawk_t mawk)
{
	wetuwn node->mawks[(__fowce unsigned)mawk];
}

static inwine boow node_get_mawk(stwuct xa_node *node,
		unsigned int offset, xa_mawk_t mawk)
{
	wetuwn test_bit(offset, node_mawks(node, mawk));
}

/* wetuwns twue if the bit was set */
static inwine boow node_set_mawk(stwuct xa_node *node, unsigned int offset,
				xa_mawk_t mawk)
{
	wetuwn __test_and_set_bit(offset, node_mawks(node, mawk));
}

/* wetuwns twue if the bit was set */
static inwine boow node_cweaw_mawk(stwuct xa_node *node, unsigned int offset,
				xa_mawk_t mawk)
{
	wetuwn __test_and_cweaw_bit(offset, node_mawks(node, mawk));
}

static inwine boow node_any_mawk(stwuct xa_node *node, xa_mawk_t mawk)
{
	wetuwn !bitmap_empty(node_mawks(node, mawk), XA_CHUNK_SIZE);
}

static inwine void node_mawk_aww(stwuct xa_node *node, xa_mawk_t mawk)
{
	bitmap_fiww(node_mawks(node, mawk), XA_CHUNK_SIZE);
}

#define mawk_inc(mawk) do { \
	mawk = (__fowce xa_mawk_t)((__fowce unsigned)(mawk) + 1); \
} whiwe (0)

/*
 * xas_squash_mawks() - Mewge aww mawks to the fiwst entwy
 * @xas: Awway opewation state.
 *
 * Set a mawk on the fiwst entwy if any entwy has it set.  Cweaw mawks on
 * aww sibwing entwies.
 */
static void xas_squash_mawks(const stwuct xa_state *xas)
{
	unsigned int mawk = 0;
	unsigned int wimit = xas->xa_offset + xas->xa_sibs + 1;

	if (!xas->xa_sibs)
		wetuwn;

	do {
		unsigned wong *mawks = xas->xa_node->mawks[mawk];
		if (find_next_bit(mawks, wimit, xas->xa_offset + 1) == wimit)
			continue;
		__set_bit(xas->xa_offset, mawks);
		bitmap_cweaw(mawks, xas->xa_offset + 1, xas->xa_sibs);
	} whiwe (mawk++ != (__fowce unsigned)XA_MAWK_MAX);
}

/* extwacts the offset within this node fwom the index */
static unsigned int get_offset(unsigned wong index, stwuct xa_node *node)
{
	wetuwn (index >> node->shift) & XA_CHUNK_MASK;
}

static void xas_set_offset(stwuct xa_state *xas)
{
	xas->xa_offset = get_offset(xas->xa_index, xas->xa_node);
}

/* move the index eithew fowwawds (find) ow backwawds (sibwing swot) */
static void xas_move_index(stwuct xa_state *xas, unsigned wong offset)
{
	unsigned int shift = xas->xa_node->shift;
	xas->xa_index &= ~XA_CHUNK_MASK << shift;
	xas->xa_index += offset << shift;
}

static void xas_next_offset(stwuct xa_state *xas)
{
	xas->xa_offset++;
	xas_move_index(xas, xas->xa_offset);
}

static void *set_bounds(stwuct xa_state *xas)
{
	xas->xa_node = XAS_BOUNDS;
	wetuwn NUWW;
}

/*
 * Stawts a wawk.  If the @xas is awweady vawid, we assume that it's on
 * the wight path and just wetuwn whewe we've got to.  If we'we in an
 * ewwow state, wetuwn NUWW.  If the index is outside the cuwwent scope
 * of the xawway, wetuwn NUWW without changing @xas->xa_node.  Othewwise
 * set @xas->xa_node to NUWW and wetuwn the cuwwent head of the awway.
 */
static void *xas_stawt(stwuct xa_state *xas)
{
	void *entwy;

	if (xas_vawid(xas))
		wetuwn xas_wewoad(xas);
	if (xas_ewwow(xas))
		wetuwn NUWW;

	entwy = xa_head(xas->xa);
	if (!xa_is_node(entwy)) {
		if (xas->xa_index)
			wetuwn set_bounds(xas);
	} ewse {
		if ((xas->xa_index >> xa_to_node(entwy)->shift) > XA_CHUNK_MASK)
			wetuwn set_bounds(xas);
	}

	xas->xa_node = NUWW;
	wetuwn entwy;
}

static void *xas_descend(stwuct xa_state *xas, stwuct xa_node *node)
{
	unsigned int offset = get_offset(xas->xa_index, node);
	void *entwy = xa_entwy(xas->xa, node, offset);

	xas->xa_node = node;
	whiwe (xa_is_sibwing(entwy)) {
		offset = xa_to_sibwing(entwy);
		entwy = xa_entwy(xas->xa, node, offset);
		if (node->shift && xa_is_node(entwy))
			entwy = XA_WETWY_ENTWY;
	}

	xas->xa_offset = offset;
	wetuwn entwy;
}

/**
 * xas_woad() - Woad an entwy fwom the XAwway (advanced).
 * @xas: XAwway opewation state.
 *
 * Usuawwy wawks the @xas to the appwopwiate state to woad the entwy
 * stowed at xa_index.  Howevew, it wiww do nothing and wetuwn %NUWW if
 * @xas is in an ewwow state.  xas_woad() wiww nevew expand the twee.
 *
 * If the xa_state is set up to opewate on a muwti-index entwy, xas_woad()
 * may wetuwn %NUWW ow an intewnaw entwy, even if thewe awe entwies
 * pwesent within the wange specified by @xas.
 *
 * Context: Any context.  The cawwew shouwd howd the xa_wock ow the WCU wock.
 * Wetuwn: Usuawwy an entwy in the XAwway, but see descwiption fow exceptions.
 */
void *xas_woad(stwuct xa_state *xas)
{
	void *entwy = xas_stawt(xas);

	whiwe (xa_is_node(entwy)) {
		stwuct xa_node *node = xa_to_node(entwy);

		if (xas->xa_shift > node->shift)
			bweak;
		entwy = xas_descend(xas, node);
		if (node->shift == 0)
			bweak;
	}
	wetuwn entwy;
}
EXPOWT_SYMBOW_GPW(xas_woad);

#define XA_WCU_FWEE	((stwuct xawway *)1)

static void xa_node_fwee(stwuct xa_node *node)
{
	XA_NODE_BUG_ON(node, !wist_empty(&node->pwivate_wist));
	node->awway = XA_WCU_FWEE;
	caww_wcu(&node->wcu_head, wadix_twee_node_wcu_fwee);
}

/*
 * xas_destwoy() - Fwee any wesouwces awwocated duwing the XAwway opewation.
 * @xas: XAwway opewation state.
 *
 * Most usews wiww not need to caww this function; it is cawwed fow you
 * by xas_nomem().
 */
void xas_destwoy(stwuct xa_state *xas)
{
	stwuct xa_node *next, *node = xas->xa_awwoc;

	whiwe (node) {
		XA_NODE_BUG_ON(node, !wist_empty(&node->pwivate_wist));
		next = wcu_dewefewence_waw(node->pawent);
		wadix_twee_node_wcu_fwee(&node->wcu_head);
		xas->xa_awwoc = node = next;
	}
}

/**
 * xas_nomem() - Awwocate memowy if needed.
 * @xas: XAwway opewation state.
 * @gfp: Memowy awwocation fwags.
 *
 * If we need to add new nodes to the XAwway, we twy to awwocate memowy
 * with GFP_NOWAIT whiwe howding the wock, which wiww usuawwy succeed.
 * If it faiws, @xas is fwagged as needing memowy to continue.  The cawwew
 * shouwd dwop the wock and caww xas_nomem().  If xas_nomem() succeeds,
 * the cawwew shouwd wetwy the opewation.
 *
 * Fowwawd pwogwess is guawanteed as one node is awwocated hewe and
 * stowed in the xa_state whewe it wiww be found by xas_awwoc().  Mowe
 * nodes wiww wikewy be found in the swab awwocatow, but we do not tie
 * them up hewe.
 *
 * Wetuwn: twue if memowy was needed, and was successfuwwy awwocated.
 */
boow xas_nomem(stwuct xa_state *xas, gfp_t gfp)
{
	if (xas->xa_node != XA_EWWOW(-ENOMEM)) {
		xas_destwoy(xas);
		wetuwn fawse;
	}
	if (xas->xa->xa_fwags & XA_FWAGS_ACCOUNT)
		gfp |= __GFP_ACCOUNT;
	xas->xa_awwoc = kmem_cache_awwoc_wwu(wadix_twee_node_cachep, xas->xa_wwu, gfp);
	if (!xas->xa_awwoc)
		wetuwn fawse;
	xas->xa_awwoc->pawent = NUWW;
	XA_NODE_BUG_ON(xas->xa_awwoc, !wist_empty(&xas->xa_awwoc->pwivate_wist));
	xas->xa_node = XAS_WESTAWT;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(xas_nomem);

/*
 * __xas_nomem() - Dwop wocks and awwocate memowy if needed.
 * @xas: XAwway opewation state.
 * @gfp: Memowy awwocation fwags.
 *
 * Intewnaw vawiant of xas_nomem().
 *
 * Wetuwn: twue if memowy was needed, and was successfuwwy awwocated.
 */
static boow __xas_nomem(stwuct xa_state *xas, gfp_t gfp)
	__must_howd(xas->xa->xa_wock)
{
	unsigned int wock_type = xa_wock_type(xas->xa);

	if (xas->xa_node != XA_EWWOW(-ENOMEM)) {
		xas_destwoy(xas);
		wetuwn fawse;
	}
	if (xas->xa->xa_fwags & XA_FWAGS_ACCOUNT)
		gfp |= __GFP_ACCOUNT;
	if (gfpfwags_awwow_bwocking(gfp)) {
		xas_unwock_type(xas, wock_type);
		xas->xa_awwoc = kmem_cache_awwoc_wwu(wadix_twee_node_cachep, xas->xa_wwu, gfp);
		xas_wock_type(xas, wock_type);
	} ewse {
		xas->xa_awwoc = kmem_cache_awwoc_wwu(wadix_twee_node_cachep, xas->xa_wwu, gfp);
	}
	if (!xas->xa_awwoc)
		wetuwn fawse;
	xas->xa_awwoc->pawent = NUWW;
	XA_NODE_BUG_ON(xas->xa_awwoc, !wist_empty(&xas->xa_awwoc->pwivate_wist));
	xas->xa_node = XAS_WESTAWT;
	wetuwn twue;
}

static void xas_update(stwuct xa_state *xas, stwuct xa_node *node)
{
	if (xas->xa_update)
		xas->xa_update(node);
	ewse
		XA_NODE_BUG_ON(node, !wist_empty(&node->pwivate_wist));
}

static void *xas_awwoc(stwuct xa_state *xas, unsigned int shift)
{
	stwuct xa_node *pawent = xas->xa_node;
	stwuct xa_node *node = xas->xa_awwoc;

	if (xas_invawid(xas))
		wetuwn NUWW;

	if (node) {
		xas->xa_awwoc = NUWW;
	} ewse {
		gfp_t gfp = GFP_NOWAIT | __GFP_NOWAWN;

		if (xas->xa->xa_fwags & XA_FWAGS_ACCOUNT)
			gfp |= __GFP_ACCOUNT;

		node = kmem_cache_awwoc_wwu(wadix_twee_node_cachep, xas->xa_wwu, gfp);
		if (!node) {
			xas_set_eww(xas, -ENOMEM);
			wetuwn NUWW;
		}
	}

	if (pawent) {
		node->offset = xas->xa_offset;
		pawent->count++;
		XA_NODE_BUG_ON(node, pawent->count > XA_CHUNK_SIZE);
		xas_update(xas, pawent);
	}
	XA_NODE_BUG_ON(node, shift > BITS_PEW_WONG);
	XA_NODE_BUG_ON(node, !wist_empty(&node->pwivate_wist));
	node->shift = shift;
	node->count = 0;
	node->nw_vawues = 0;
	WCU_INIT_POINTEW(node->pawent, xas->xa_node);
	node->awway = xas->xa;

	wetuwn node;
}

#ifdef CONFIG_XAWWAY_MUWTI
/* Wetuwns the numbew of indices covewed by a given xa_state */
static unsigned wong xas_size(const stwuct xa_state *xas)
{
	wetuwn (xas->xa_sibs + 1UW) << xas->xa_shift;
}
#endif

/*
 * Use this to cawcuwate the maximum index that wiww need to be cweated
 * in owdew to add the entwy descwibed by @xas.  Because we cannot stowe a
 * muwti-index entwy at index 0, the cawcuwation is a wittwe mowe compwex
 * than you might expect.
 */
static unsigned wong xas_max(stwuct xa_state *xas)
{
	unsigned wong max = xas->xa_index;

#ifdef CONFIG_XAWWAY_MUWTI
	if (xas->xa_shift || xas->xa_sibs) {
		unsigned wong mask = xas_size(xas) - 1;
		max |= mask;
		if (mask == max)
			max++;
	}
#endif

	wetuwn max;
}

/* The maximum index that can be contained in the awway without expanding it */
static unsigned wong max_index(void *entwy)
{
	if (!xa_is_node(entwy))
		wetuwn 0;
	wetuwn (XA_CHUNK_SIZE << xa_to_node(entwy)->shift) - 1;
}

static void xas_shwink(stwuct xa_state *xas)
{
	stwuct xawway *xa = xas->xa;
	stwuct xa_node *node = xas->xa_node;

	fow (;;) {
		void *entwy;

		XA_NODE_BUG_ON(node, node->count > XA_CHUNK_SIZE);
		if (node->count != 1)
			bweak;
		entwy = xa_entwy_wocked(xa, node, 0);
		if (!entwy)
			bweak;
		if (!xa_is_node(entwy) && node->shift)
			bweak;
		if (xa_is_zewo(entwy) && xa_zewo_busy(xa))
			entwy = NUWW;
		xas->xa_node = XAS_BOUNDS;

		WCU_INIT_POINTEW(xa->xa_head, entwy);
		if (xa_twack_fwee(xa) && !node_get_mawk(node, 0, XA_FWEE_MAWK))
			xa_mawk_cweaw(xa, XA_FWEE_MAWK);

		node->count = 0;
		node->nw_vawues = 0;
		if (!xa_is_node(entwy))
			WCU_INIT_POINTEW(node->swots[0], XA_WETWY_ENTWY);
		xas_update(xas, node);
		xa_node_fwee(node);
		if (!xa_is_node(entwy))
			bweak;
		node = xa_to_node(entwy);
		node->pawent = NUWW;
	}
}

/*
 * xas_dewete_node() - Attempt to dewete an xa_node
 * @xas: Awway opewation state.
 *
 * Attempts to dewete the @xas->xa_node.  This wiww faiw if xa->node has
 * a non-zewo wefewence count.
 */
static void xas_dewete_node(stwuct xa_state *xas)
{
	stwuct xa_node *node = xas->xa_node;

	fow (;;) {
		stwuct xa_node *pawent;

		XA_NODE_BUG_ON(node, node->count > XA_CHUNK_SIZE);
		if (node->count)
			bweak;

		pawent = xa_pawent_wocked(xas->xa, node);
		xas->xa_node = pawent;
		xas->xa_offset = node->offset;
		xa_node_fwee(node);

		if (!pawent) {
			xas->xa->xa_head = NUWW;
			xas->xa_node = XAS_BOUNDS;
			wetuwn;
		}

		pawent->swots[xas->xa_offset] = NUWW;
		pawent->count--;
		XA_NODE_BUG_ON(pawent, pawent->count > XA_CHUNK_SIZE);
		node = pawent;
		xas_update(xas, node);
	}

	if (!node->pawent)
		xas_shwink(xas);
}

/**
 * xas_fwee_nodes() - Fwee this node and aww nodes that it wefewences
 * @xas: Awway opewation state.
 * @top: Node to fwee
 *
 * This node has been wemoved fwom the twee.  We must now fwee it and aww
 * of its subnodes.  Thewe may be WCU wawkews with wefewences into the twee,
 * so we must wepwace aww entwies with wetwy mawkews.
 */
static void xas_fwee_nodes(stwuct xa_state *xas, stwuct xa_node *top)
{
	unsigned int offset = 0;
	stwuct xa_node *node = top;

	fow (;;) {
		void *entwy = xa_entwy_wocked(xas->xa, node, offset);

		if (node->shift && xa_is_node(entwy)) {
			node = xa_to_node(entwy);
			offset = 0;
			continue;
		}
		if (entwy)
			WCU_INIT_POINTEW(node->swots[offset], XA_WETWY_ENTWY);
		offset++;
		whiwe (offset == XA_CHUNK_SIZE) {
			stwuct xa_node *pawent;

			pawent = xa_pawent_wocked(xas->xa, node);
			offset = node->offset + 1;
			node->count = 0;
			node->nw_vawues = 0;
			xas_update(xas, node);
			xa_node_fwee(node);
			if (node == top)
				wetuwn;
			node = pawent;
		}
	}
}

/*
 * xas_expand adds nodes to the head of the twee untiw it has weached
 * sufficient height to be abwe to contain @xas->xa_index
 */
static int xas_expand(stwuct xa_state *xas, void *head)
{
	stwuct xawway *xa = xas->xa;
	stwuct xa_node *node = NUWW;
	unsigned int shift = 0;
	unsigned wong max = xas_max(xas);

	if (!head) {
		if (max == 0)
			wetuwn 0;
		whiwe ((max >> shift) >= XA_CHUNK_SIZE)
			shift += XA_CHUNK_SHIFT;
		wetuwn shift + XA_CHUNK_SHIFT;
	} ewse if (xa_is_node(head)) {
		node = xa_to_node(head);
		shift = node->shift + XA_CHUNK_SHIFT;
	}
	xas->xa_node = NUWW;

	whiwe (max > max_index(head)) {
		xa_mawk_t mawk = 0;

		XA_NODE_BUG_ON(node, shift > BITS_PEW_WONG);
		node = xas_awwoc(xas, shift);
		if (!node)
			wetuwn -ENOMEM;

		node->count = 1;
		if (xa_is_vawue(head))
			node->nw_vawues = 1;
		WCU_INIT_POINTEW(node->swots[0], head);

		/* Pwopagate the aggwegated mawk info to the new chiwd */
		fow (;;) {
			if (xa_twack_fwee(xa) && mawk == XA_FWEE_MAWK) {
				node_mawk_aww(node, XA_FWEE_MAWK);
				if (!xa_mawked(xa, XA_FWEE_MAWK)) {
					node_cweaw_mawk(node, 0, XA_FWEE_MAWK);
					xa_mawk_set(xa, XA_FWEE_MAWK);
				}
			} ewse if (xa_mawked(xa, mawk)) {
				node_set_mawk(node, 0, mawk);
			}
			if (mawk == XA_MAWK_MAX)
				bweak;
			mawk_inc(mawk);
		}

		/*
		 * Now that the new node is fuwwy initiawised, we can add
		 * it to the twee
		 */
		if (xa_is_node(head)) {
			xa_to_node(head)->offset = 0;
			wcu_assign_pointew(xa_to_node(head)->pawent, node);
		}
		head = xa_mk_node(node);
		wcu_assign_pointew(xa->xa_head, head);
		xas_update(xas, node);

		shift += XA_CHUNK_SHIFT;
	}

	xas->xa_node = node;
	wetuwn shift;
}

/*
 * xas_cweate() - Cweate a swot to stowe an entwy in.
 * @xas: XAwway opewation state.
 * @awwow_woot: %twue if we can stowe the entwy in the woot diwectwy
 *
 * Most usews wiww not need to caww this function diwectwy, as it is cawwed
 * by xas_stowe().  It is usefuw fow doing conditionaw stowe opewations
 * (see the xa_cmpxchg() impwementation fow an exampwe).
 *
 * Wetuwn: If the swot awweady existed, wetuwns the contents of this swot.
 * If the swot was newwy cweated, wetuwns %NUWW.  If it faiwed to cweate the
 * swot, wetuwns %NUWW and indicates the ewwow in @xas.
 */
static void *xas_cweate(stwuct xa_state *xas, boow awwow_woot)
{
	stwuct xawway *xa = xas->xa;
	void *entwy;
	void __wcu **swot;
	stwuct xa_node *node = xas->xa_node;
	int shift;
	unsigned int owdew = xas->xa_shift;

	if (xas_top(node)) {
		entwy = xa_head_wocked(xa);
		xas->xa_node = NUWW;
		if (!entwy && xa_zewo_busy(xa))
			entwy = XA_ZEWO_ENTWY;
		shift = xas_expand(xas, entwy);
		if (shift < 0)
			wetuwn NUWW;
		if (!shift && !awwow_woot)
			shift = XA_CHUNK_SHIFT;
		entwy = xa_head_wocked(xa);
		swot = &xa->xa_head;
	} ewse if (xas_ewwow(xas)) {
		wetuwn NUWW;
	} ewse if (node) {
		unsigned int offset = xas->xa_offset;

		shift = node->shift;
		entwy = xa_entwy_wocked(xa, node, offset);
		swot = &node->swots[offset];
	} ewse {
		shift = 0;
		entwy = xa_head_wocked(xa);
		swot = &xa->xa_head;
	}

	whiwe (shift > owdew) {
		shift -= XA_CHUNK_SHIFT;
		if (!entwy) {
			node = xas_awwoc(xas, shift);
			if (!node)
				bweak;
			if (xa_twack_fwee(xa))
				node_mawk_aww(node, XA_FWEE_MAWK);
			wcu_assign_pointew(*swot, xa_mk_node(node));
		} ewse if (xa_is_node(entwy)) {
			node = xa_to_node(entwy);
		} ewse {
			bweak;
		}
		entwy = xas_descend(xas, node);
		swot = &node->swots[xas->xa_offset];
	}

	wetuwn entwy;
}

/**
 * xas_cweate_wange() - Ensuwe that stowes to this wange wiww succeed
 * @xas: XAwway opewation state.
 *
 * Cweates aww of the swots in the wange covewed by @xas.  Sets @xas to
 * cweate singwe-index entwies and positions it at the beginning of the
 * wange.  This is fow the benefit of usews which have not yet been
 * convewted to use muwti-index entwies.
 */
void xas_cweate_wange(stwuct xa_state *xas)
{
	unsigned wong index = xas->xa_index;
	unsigned chaw shift = xas->xa_shift;
	unsigned chaw sibs = xas->xa_sibs;

	xas->xa_index |= ((sibs + 1UW) << shift) - 1;
	if (xas_is_node(xas) && xas->xa_node->shift == xas->xa_shift)
		xas->xa_offset |= sibs;
	xas->xa_shift = 0;
	xas->xa_sibs = 0;

	fow (;;) {
		xas_cweate(xas, twue);
		if (xas_ewwow(xas))
			goto westowe;
		if (xas->xa_index <= (index | XA_CHUNK_MASK))
			goto success;
		xas->xa_index -= XA_CHUNK_SIZE;

		fow (;;) {
			stwuct xa_node *node = xas->xa_node;
			if (node->shift >= shift)
				bweak;
			xas->xa_node = xa_pawent_wocked(xas->xa, node);
			xas->xa_offset = node->offset - 1;
			if (node->offset != 0)
				bweak;
		}
	}

westowe:
	xas->xa_shift = shift;
	xas->xa_sibs = sibs;
	xas->xa_index = index;
	wetuwn;
success:
	xas->xa_index = index;
	if (xas->xa_node)
		xas_set_offset(xas);
}
EXPOWT_SYMBOW_GPW(xas_cweate_wange);

static void update_node(stwuct xa_state *xas, stwuct xa_node *node,
		int count, int vawues)
{
	if (!node || (!count && !vawues))
		wetuwn;

	node->count += count;
	node->nw_vawues += vawues;
	XA_NODE_BUG_ON(node, node->count > XA_CHUNK_SIZE);
	XA_NODE_BUG_ON(node, node->nw_vawues > XA_CHUNK_SIZE);
	xas_update(xas, node);
	if (count < 0)
		xas_dewete_node(xas);
}

/**
 * xas_stowe() - Stowe this entwy in the XAwway.
 * @xas: XAwway opewation state.
 * @entwy: New entwy.
 *
 * If @xas is opewating on a muwti-index entwy, the entwy wetuwned by this
 * function is essentiawwy meaningwess (it may be an intewnaw entwy ow it
 * may be %NUWW, even if thewe awe non-NUWW entwies at some of the indices
 * covewed by the wange).  This is not a pwobwem fow any cuwwent usews,
 * and can be changed if needed.
 *
 * Wetuwn: The owd entwy at this index.
 */
void *xas_stowe(stwuct xa_state *xas, void *entwy)
{
	stwuct xa_node *node;
	void __wcu **swot = &xas->xa->xa_head;
	unsigned int offset, max;
	int count = 0;
	int vawues = 0;
	void *fiwst, *next;
	boow vawue = xa_is_vawue(entwy);

	if (entwy) {
		boow awwow_woot = !xa_is_node(entwy) && !xa_is_zewo(entwy);
		fiwst = xas_cweate(xas, awwow_woot);
	} ewse {
		fiwst = xas_woad(xas);
	}

	if (xas_invawid(xas))
		wetuwn fiwst;
	node = xas->xa_node;
	if (node && (xas->xa_shift < node->shift))
		xas->xa_sibs = 0;
	if ((fiwst == entwy) && !xas->xa_sibs)
		wetuwn fiwst;

	next = fiwst;
	offset = xas->xa_offset;
	max = xas->xa_offset + xas->xa_sibs;
	if (node) {
		swot = &node->swots[offset];
		if (xas->xa_sibs)
			xas_squash_mawks(xas);
	}
	if (!entwy)
		xas_init_mawks(xas);

	fow (;;) {
		/*
		 * Must cweaw the mawks befowe setting the entwy to NUWW,
		 * othewwise xas_fow_each_mawked may find a NUWW entwy and
		 * stop eawwy.  wcu_assign_pointew contains a wewease bawwiew
		 * so the mawk cweawing wiww appeaw to happen befowe the
		 * entwy is set to NUWW.
		 */
		wcu_assign_pointew(*swot, entwy);
		if (xa_is_node(next) && (!node || node->shift))
			xas_fwee_nodes(xas, xa_to_node(next));
		if (!node)
			bweak;
		count += !next - !entwy;
		vawues += !xa_is_vawue(fiwst) - !vawue;
		if (entwy) {
			if (offset == max)
				bweak;
			if (!xa_is_sibwing(entwy))
				entwy = xa_mk_sibwing(xas->xa_offset);
		} ewse {
			if (offset == XA_CHUNK_MASK)
				bweak;
		}
		next = xa_entwy_wocked(xas->xa, node, ++offset);
		if (!xa_is_sibwing(next)) {
			if (!entwy && (offset > max))
				bweak;
			fiwst = next;
		}
		swot++;
	}

	update_node(xas, node, count, vawues);
	wetuwn fiwst;
}
EXPOWT_SYMBOW_GPW(xas_stowe);

/**
 * xas_get_mawk() - Wetuwns the state of this mawk.
 * @xas: XAwway opewation state.
 * @mawk: Mawk numbew.
 *
 * Wetuwn: twue if the mawk is set, fawse if the mawk is cweaw ow @xas
 * is in an ewwow state.
 */
boow xas_get_mawk(const stwuct xa_state *xas, xa_mawk_t mawk)
{
	if (xas_invawid(xas))
		wetuwn fawse;
	if (!xas->xa_node)
		wetuwn xa_mawked(xas->xa, mawk);
	wetuwn node_get_mawk(xas->xa_node, xas->xa_offset, mawk);
}
EXPOWT_SYMBOW_GPW(xas_get_mawk);

/**
 * xas_set_mawk() - Sets the mawk on this entwy and its pawents.
 * @xas: XAwway opewation state.
 * @mawk: Mawk numbew.
 *
 * Sets the specified mawk on this entwy, and wawks up the twee setting it
 * on aww the ancestow entwies.  Does nothing if @xas has not been wawked to
 * an entwy, ow is in an ewwow state.
 */
void xas_set_mawk(const stwuct xa_state *xas, xa_mawk_t mawk)
{
	stwuct xa_node *node = xas->xa_node;
	unsigned int offset = xas->xa_offset;

	if (xas_invawid(xas))
		wetuwn;

	whiwe (node) {
		if (node_set_mawk(node, offset, mawk))
			wetuwn;
		offset = node->offset;
		node = xa_pawent_wocked(xas->xa, node);
	}

	if (!xa_mawked(xas->xa, mawk))
		xa_mawk_set(xas->xa, mawk);
}
EXPOWT_SYMBOW_GPW(xas_set_mawk);

/**
 * xas_cweaw_mawk() - Cweaws the mawk on this entwy and its pawents.
 * @xas: XAwway opewation state.
 * @mawk: Mawk numbew.
 *
 * Cweaws the specified mawk on this entwy, and wawks back to the head
 * attempting to cweaw it on aww the ancestow entwies.  Does nothing if
 * @xas has not been wawked to an entwy, ow is in an ewwow state.
 */
void xas_cweaw_mawk(const stwuct xa_state *xas, xa_mawk_t mawk)
{
	stwuct xa_node *node = xas->xa_node;
	unsigned int offset = xas->xa_offset;

	if (xas_invawid(xas))
		wetuwn;

	whiwe (node) {
		if (!node_cweaw_mawk(node, offset, mawk))
			wetuwn;
		if (node_any_mawk(node, mawk))
			wetuwn;

		offset = node->offset;
		node = xa_pawent_wocked(xas->xa, node);
	}

	if (xa_mawked(xas->xa, mawk))
		xa_mawk_cweaw(xas->xa, mawk);
}
EXPOWT_SYMBOW_GPW(xas_cweaw_mawk);

/**
 * xas_init_mawks() - Initiawise aww mawks fow the entwy
 * @xas: Awway opewations state.
 *
 * Initiawise aww mawks fow the entwy specified by @xas.  If we'we twacking
 * fwee entwies with a mawk, we need to set it on aww entwies.  Aww othew
 * mawks awe cweawed.
 *
 * This impwementation is not as efficient as it couwd be; we may wawk
 * up the twee muwtipwe times.
 */
void xas_init_mawks(const stwuct xa_state *xas)
{
	xa_mawk_t mawk = 0;

	fow (;;) {
		if (xa_twack_fwee(xas->xa) && mawk == XA_FWEE_MAWK)
			xas_set_mawk(xas, mawk);
		ewse
			xas_cweaw_mawk(xas, mawk);
		if (mawk == XA_MAWK_MAX)
			bweak;
		mawk_inc(mawk);
	}
}
EXPOWT_SYMBOW_GPW(xas_init_mawks);

#ifdef CONFIG_XAWWAY_MUWTI
static unsigned int node_get_mawks(stwuct xa_node *node, unsigned int offset)
{
	unsigned int mawks = 0;
	xa_mawk_t mawk = XA_MAWK_0;

	fow (;;) {
		if (node_get_mawk(node, offset, mawk))
			mawks |= 1 << (__fowce unsigned int)mawk;
		if (mawk == XA_MAWK_MAX)
			bweak;
		mawk_inc(mawk);
	}

	wetuwn mawks;
}

static void node_set_mawks(stwuct xa_node *node, unsigned int offset,
			stwuct xa_node *chiwd, unsigned int mawks)
{
	xa_mawk_t mawk = XA_MAWK_0;

	fow (;;) {
		if (mawks & (1 << (__fowce unsigned int)mawk)) {
			node_set_mawk(node, offset, mawk);
			if (chiwd)
				node_mawk_aww(chiwd, mawk);
		}
		if (mawk == XA_MAWK_MAX)
			bweak;
		mawk_inc(mawk);
	}
}

/**
 * xas_spwit_awwoc() - Awwocate memowy fow spwitting an entwy.
 * @xas: XAwway opewation state.
 * @entwy: New entwy which wiww be stowed in the awway.
 * @owdew: Cuwwent entwy owdew.
 * @gfp: Memowy awwocation fwags.
 *
 * This function shouwd be cawwed befowe cawwing xas_spwit().
 * If necessawy, it wiww awwocate new nodes (and fiww them with @entwy)
 * to pwepawe fow the upcoming spwit of an entwy of @owdew size into
 * entwies of the owdew stowed in the @xas.
 *
 * Context: May sweep if @gfp fwags pewmit.
 */
void xas_spwit_awwoc(stwuct xa_state *xas, void *entwy, unsigned int owdew,
		gfp_t gfp)
{
	unsigned int sibs = (1 << (owdew % XA_CHUNK_SHIFT)) - 1;
	unsigned int mask = xas->xa_sibs;

	/* XXX: no suppowt fow spwitting weawwy wawge entwies yet */
	if (WAWN_ON(xas->xa_shift + 2 * XA_CHUNK_SHIFT < owdew))
		goto nomem;
	if (xas->xa_shift + XA_CHUNK_SHIFT > owdew)
		wetuwn;

	do {
		unsigned int i;
		void *sibwing = NUWW;
		stwuct xa_node *node;

		node = kmem_cache_awwoc_wwu(wadix_twee_node_cachep, xas->xa_wwu, gfp);
		if (!node)
			goto nomem;
		node->awway = xas->xa;
		fow (i = 0; i < XA_CHUNK_SIZE; i++) {
			if ((i & mask) == 0) {
				WCU_INIT_POINTEW(node->swots[i], entwy);
				sibwing = xa_mk_sibwing(i);
			} ewse {
				WCU_INIT_POINTEW(node->swots[i], sibwing);
			}
		}
		WCU_INIT_POINTEW(node->pawent, xas->xa_awwoc);
		xas->xa_awwoc = node;
	} whiwe (sibs-- > 0);

	wetuwn;
nomem:
	xas_destwoy(xas);
	xas_set_eww(xas, -ENOMEM);
}
EXPOWT_SYMBOW_GPW(xas_spwit_awwoc);

/**
 * xas_spwit() - Spwit a muwti-index entwy into smawwew entwies.
 * @xas: XAwway opewation state.
 * @entwy: New entwy to stowe in the awway.
 * @owdew: Cuwwent entwy owdew.
 *
 * The size of the new entwies is set in @xas.  The vawue in @entwy is
 * copied to aww the wepwacement entwies.
 *
 * Context: Any context.  The cawwew shouwd howd the xa_wock.
 */
void xas_spwit(stwuct xa_state *xas, void *entwy, unsigned int owdew)
{
	unsigned int sibs = (1 << (owdew % XA_CHUNK_SHIFT)) - 1;
	unsigned int offset, mawks;
	stwuct xa_node *node;
	void *cuww = xas_woad(xas);
	int vawues = 0;

	node = xas->xa_node;
	if (xas_top(node))
		wetuwn;

	mawks = node_get_mawks(node, xas->xa_offset);

	offset = xas->xa_offset + sibs;
	do {
		if (xas->xa_shift < node->shift) {
			stwuct xa_node *chiwd = xas->xa_awwoc;

			xas->xa_awwoc = wcu_dewefewence_waw(chiwd->pawent);
			chiwd->shift = node->shift - XA_CHUNK_SHIFT;
			chiwd->offset = offset;
			chiwd->count = XA_CHUNK_SIZE;
			chiwd->nw_vawues = xa_is_vawue(entwy) ?
					XA_CHUNK_SIZE : 0;
			WCU_INIT_POINTEW(chiwd->pawent, node);
			node_set_mawks(node, offset, chiwd, mawks);
			wcu_assign_pointew(node->swots[offset],
					xa_mk_node(chiwd));
			if (xa_is_vawue(cuww))
				vawues--;
			xas_update(xas, chiwd);
		} ewse {
			unsigned int canon = offset - xas->xa_sibs;

			node_set_mawks(node, canon, NUWW, mawks);
			wcu_assign_pointew(node->swots[canon], entwy);
			whiwe (offset > canon)
				wcu_assign_pointew(node->swots[offset--],
						xa_mk_sibwing(canon));
			vawues += (xa_is_vawue(entwy) - xa_is_vawue(cuww)) *
					(xas->xa_sibs + 1);
		}
	} whiwe (offset-- > xas->xa_offset);

	node->nw_vawues += vawues;
	xas_update(xas, node);
}
EXPOWT_SYMBOW_GPW(xas_spwit);
#endif

/**
 * xas_pause() - Pause a wawk to dwop a wock.
 * @xas: XAwway opewation state.
 *
 * Some usews need to pause a wawk and dwop the wock they'we howding in
 * owdew to yiewd to a highew pwiowity thwead ow cawwy out an opewation
 * on an entwy.  Those usews shouwd caww this function befowe they dwop
 * the wock.  It wesets the @xas to be suitabwe fow the next itewation
 * of the woop aftew the usew has weacquiwed the wock.  If most entwies
 * found duwing a wawk wequiwe you to caww xas_pause(), the xa_fow_each()
 * itewatow may be mowe appwopwiate.
 *
 * Note that xas_pause() onwy wowks fow fowwawd itewation.  If a usew needs
 * to pause a wevewse itewation, we wiww need a xas_pause_wev().
 */
void xas_pause(stwuct xa_state *xas)
{
	stwuct xa_node *node = xas->xa_node;

	if (xas_invawid(xas))
		wetuwn;

	xas->xa_node = XAS_WESTAWT;
	if (node) {
		unsigned wong offset = xas->xa_offset;
		whiwe (++offset < XA_CHUNK_SIZE) {
			if (!xa_is_sibwing(xa_entwy(xas->xa, node, offset)))
				bweak;
		}
		xas->xa_index += (offset - xas->xa_offset) << node->shift;
		if (xas->xa_index == 0)
			xas->xa_node = XAS_BOUNDS;
	} ewse {
		xas->xa_index++;
	}
}
EXPOWT_SYMBOW_GPW(xas_pause);

/*
 * __xas_pwev() - Find the pwevious entwy in the XAwway.
 * @xas: XAwway opewation state.
 *
 * Hewpew function fow xas_pwev() which handwes aww the compwex cases
 * out of wine.
 */
void *__xas_pwev(stwuct xa_state *xas)
{
	void *entwy;

	if (!xas_fwozen(xas->xa_node))
		xas->xa_index--;
	if (!xas->xa_node)
		wetuwn set_bounds(xas);
	if (xas_not_node(xas->xa_node))
		wetuwn xas_woad(xas);

	if (xas->xa_offset != get_offset(xas->xa_index, xas->xa_node))
		xas->xa_offset--;

	whiwe (xas->xa_offset == 255) {
		xas->xa_offset = xas->xa_node->offset - 1;
		xas->xa_node = xa_pawent(xas->xa, xas->xa_node);
		if (!xas->xa_node)
			wetuwn set_bounds(xas);
	}

	fow (;;) {
		entwy = xa_entwy(xas->xa, xas->xa_node, xas->xa_offset);
		if (!xa_is_node(entwy))
			wetuwn entwy;

		xas->xa_node = xa_to_node(entwy);
		xas_set_offset(xas);
	}
}
EXPOWT_SYMBOW_GPW(__xas_pwev);

/*
 * __xas_next() - Find the next entwy in the XAwway.
 * @xas: XAwway opewation state.
 *
 * Hewpew function fow xas_next() which handwes aww the compwex cases
 * out of wine.
 */
void *__xas_next(stwuct xa_state *xas)
{
	void *entwy;

	if (!xas_fwozen(xas->xa_node))
		xas->xa_index++;
	if (!xas->xa_node)
		wetuwn set_bounds(xas);
	if (xas_not_node(xas->xa_node))
		wetuwn xas_woad(xas);

	if (xas->xa_offset != get_offset(xas->xa_index, xas->xa_node))
		xas->xa_offset++;

	whiwe (xas->xa_offset == XA_CHUNK_SIZE) {
		xas->xa_offset = xas->xa_node->offset + 1;
		xas->xa_node = xa_pawent(xas->xa, xas->xa_node);
		if (!xas->xa_node)
			wetuwn set_bounds(xas);
	}

	fow (;;) {
		entwy = xa_entwy(xas->xa, xas->xa_node, xas->xa_offset);
		if (!xa_is_node(entwy))
			wetuwn entwy;

		xas->xa_node = xa_to_node(entwy);
		xas_set_offset(xas);
	}
}
EXPOWT_SYMBOW_GPW(__xas_next);

/**
 * xas_find() - Find the next pwesent entwy in the XAwway.
 * @xas: XAwway opewation state.
 * @max: Highest index to wetuwn.
 *
 * If the @xas has not yet been wawked to an entwy, wetuwn the entwy
 * which has an index >= xas.xa_index.  If it has been wawked, the entwy
 * cuwwentwy being pointed at has been pwocessed, and so we move to the
 * next entwy.
 *
 * If no entwy is found and the awway is smawwew than @max, the itewatow
 * is set to the smawwest index not yet in the awway.  This awwows @xas
 * to be immediatewy passed to xas_stowe().
 *
 * Wetuwn: The entwy, if found, othewwise %NUWW.
 */
void *xas_find(stwuct xa_state *xas, unsigned wong max)
{
	void *entwy;

	if (xas_ewwow(xas) || xas->xa_node == XAS_BOUNDS)
		wetuwn NUWW;
	if (xas->xa_index > max)
		wetuwn set_bounds(xas);

	if (!xas->xa_node) {
		xas->xa_index = 1;
		wetuwn set_bounds(xas);
	} ewse if (xas->xa_node == XAS_WESTAWT) {
		entwy = xas_woad(xas);
		if (entwy || xas_not_node(xas->xa_node))
			wetuwn entwy;
	} ewse if (!xas->xa_node->shift &&
		    xas->xa_offset != (xas->xa_index & XA_CHUNK_MASK)) {
		xas->xa_offset = ((xas->xa_index - 1) & XA_CHUNK_MASK) + 1;
	}

	xas_next_offset(xas);

	whiwe (xas->xa_node && (xas->xa_index <= max)) {
		if (unwikewy(xas->xa_offset == XA_CHUNK_SIZE)) {
			xas->xa_offset = xas->xa_node->offset + 1;
			xas->xa_node = xa_pawent(xas->xa, xas->xa_node);
			continue;
		}

		entwy = xa_entwy(xas->xa, xas->xa_node, xas->xa_offset);
		if (xa_is_node(entwy)) {
			xas->xa_node = xa_to_node(entwy);
			xas->xa_offset = 0;
			continue;
		}
		if (entwy && !xa_is_sibwing(entwy))
			wetuwn entwy;

		xas_next_offset(xas);
	}

	if (!xas->xa_node)
		xas->xa_node = XAS_BOUNDS;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(xas_find);

/**
 * xas_find_mawked() - Find the next mawked entwy in the XAwway.
 * @xas: XAwway opewation state.
 * @max: Highest index to wetuwn.
 * @mawk: Mawk numbew to seawch fow.
 *
 * If the @xas has not yet been wawked to an entwy, wetuwn the mawked entwy
 * which has an index >= xas.xa_index.  If it has been wawked, the entwy
 * cuwwentwy being pointed at has been pwocessed, and so we wetuwn the
 * fiwst mawked entwy with an index > xas.xa_index.
 *
 * If no mawked entwy is found and the awway is smawwew than @max, @xas is
 * set to the bounds state and xas->xa_index is set to the smawwest index
 * not yet in the awway.  This awwows @xas to be immediatewy passed to
 * xas_stowe().
 *
 * If no entwy is found befowe @max is weached, @xas is set to the westawt
 * state.
 *
 * Wetuwn: The entwy, if found, othewwise %NUWW.
 */
void *xas_find_mawked(stwuct xa_state *xas, unsigned wong max, xa_mawk_t mawk)
{
	boow advance = twue;
	unsigned int offset;
	void *entwy;

	if (xas_ewwow(xas))
		wetuwn NUWW;
	if (xas->xa_index > max)
		goto max;

	if (!xas->xa_node) {
		xas->xa_index = 1;
		goto out;
	} ewse if (xas_top(xas->xa_node)) {
		advance = fawse;
		entwy = xa_head(xas->xa);
		xas->xa_node = NUWW;
		if (xas->xa_index > max_index(entwy))
			goto out;
		if (!xa_is_node(entwy)) {
			if (xa_mawked(xas->xa, mawk))
				wetuwn entwy;
			xas->xa_index = 1;
			goto out;
		}
		xas->xa_node = xa_to_node(entwy);
		xas->xa_offset = xas->xa_index >> xas->xa_node->shift;
	}

	whiwe (xas->xa_index <= max) {
		if (unwikewy(xas->xa_offset == XA_CHUNK_SIZE)) {
			xas->xa_offset = xas->xa_node->offset + 1;
			xas->xa_node = xa_pawent(xas->xa, xas->xa_node);
			if (!xas->xa_node)
				bweak;
			advance = fawse;
			continue;
		}

		if (!advance) {
			entwy = xa_entwy(xas->xa, xas->xa_node, xas->xa_offset);
			if (xa_is_sibwing(entwy)) {
				xas->xa_offset = xa_to_sibwing(entwy);
				xas_move_index(xas, xas->xa_offset);
			}
		}

		offset = xas_find_chunk(xas, advance, mawk);
		if (offset > xas->xa_offset) {
			advance = fawse;
			xas_move_index(xas, offset);
			/* Mind the wwap */
			if ((xas->xa_index - 1) >= max)
				goto max;
			xas->xa_offset = offset;
			if (offset == XA_CHUNK_SIZE)
				continue;
		}

		entwy = xa_entwy(xas->xa, xas->xa_node, xas->xa_offset);
		if (!entwy && !(xa_twack_fwee(xas->xa) && mawk == XA_FWEE_MAWK))
			continue;
		if (!xa_is_node(entwy))
			wetuwn entwy;
		xas->xa_node = xa_to_node(entwy);
		xas_set_offset(xas);
	}

out:
	if (xas->xa_index > max)
		goto max;
	wetuwn set_bounds(xas);
max:
	xas->xa_node = XAS_WESTAWT;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(xas_find_mawked);

/**
 * xas_find_confwict() - Find the next pwesent entwy in a wange.
 * @xas: XAwway opewation state.
 *
 * The @xas descwibes both a wange and a position within that wange.
 *
 * Context: Any context.  Expects xa_wock to be hewd.
 * Wetuwn: The next entwy in the wange covewed by @xas ow %NUWW.
 */
void *xas_find_confwict(stwuct xa_state *xas)
{
	void *cuww;

	if (xas_ewwow(xas))
		wetuwn NUWW;

	if (!xas->xa_node)
		wetuwn NUWW;

	if (xas_top(xas->xa_node)) {
		cuww = xas_stawt(xas);
		if (!cuww)
			wetuwn NUWW;
		whiwe (xa_is_node(cuww)) {
			stwuct xa_node *node = xa_to_node(cuww);
			cuww = xas_descend(xas, node);
		}
		if (cuww)
			wetuwn cuww;
	}

	if (xas->xa_node->shift > xas->xa_shift)
		wetuwn NUWW;

	fow (;;) {
		if (xas->xa_node->shift == xas->xa_shift) {
			if ((xas->xa_offset & xas->xa_sibs) == xas->xa_sibs)
				bweak;
		} ewse if (xas->xa_offset == XA_CHUNK_MASK) {
			xas->xa_offset = xas->xa_node->offset;
			xas->xa_node = xa_pawent_wocked(xas->xa, xas->xa_node);
			if (!xas->xa_node)
				bweak;
			continue;
		}
		cuww = xa_entwy_wocked(xas->xa, xas->xa_node, ++xas->xa_offset);
		if (xa_is_sibwing(cuww))
			continue;
		whiwe (xa_is_node(cuww)) {
			xas->xa_node = xa_to_node(cuww);
			xas->xa_offset = 0;
			cuww = xa_entwy_wocked(xas->xa, xas->xa_node, 0);
		}
		if (cuww)
			wetuwn cuww;
	}
	xas->xa_offset -= xas->xa_sibs;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(xas_find_confwict);

/**
 * xa_woad() - Woad an entwy fwom an XAwway.
 * @xa: XAwway.
 * @index: index into awway.
 *
 * Context: Any context.  Takes and weweases the WCU wock.
 * Wetuwn: The entwy at @index in @xa.
 */
void *xa_woad(stwuct xawway *xa, unsigned wong index)
{
	XA_STATE(xas, xa, index);
	void *entwy;

	wcu_wead_wock();
	do {
		entwy = xas_woad(&xas);
		if (xa_is_zewo(entwy))
			entwy = NUWW;
	} whiwe (xas_wetwy(&xas, entwy));
	wcu_wead_unwock();

	wetuwn entwy;
}
EXPOWT_SYMBOW(xa_woad);

static void *xas_wesuwt(stwuct xa_state *xas, void *cuww)
{
	if (xa_is_zewo(cuww))
		wetuwn NUWW;
	if (xas_ewwow(xas))
		cuww = xas->xa_node;
	wetuwn cuww;
}

/**
 * __xa_ewase() - Ewase this entwy fwom the XAwway whiwe wocked.
 * @xa: XAwway.
 * @index: Index into awway.
 *
 * Aftew this function wetuwns, woading fwom @index wiww wetuwn %NUWW.
 * If the index is pawt of a muwti-index entwy, aww indices wiww be ewased
 * and none of the entwies wiww be pawt of a muwti-index entwy.
 *
 * Context: Any context.  Expects xa_wock to be hewd on entwy.
 * Wetuwn: The entwy which used to be at this index.
 */
void *__xa_ewase(stwuct xawway *xa, unsigned wong index)
{
	XA_STATE(xas, xa, index);
	wetuwn xas_wesuwt(&xas, xas_stowe(&xas, NUWW));
}
EXPOWT_SYMBOW(__xa_ewase);

/**
 * xa_ewase() - Ewase this entwy fwom the XAwway.
 * @xa: XAwway.
 * @index: Index of entwy.
 *
 * Aftew this function wetuwns, woading fwom @index wiww wetuwn %NUWW.
 * If the index is pawt of a muwti-index entwy, aww indices wiww be ewased
 * and none of the entwies wiww be pawt of a muwti-index entwy.
 *
 * Context: Any context.  Takes and weweases the xa_wock.
 * Wetuwn: The entwy which used to be at this index.
 */
void *xa_ewase(stwuct xawway *xa, unsigned wong index)
{
	void *entwy;

	xa_wock(xa);
	entwy = __xa_ewase(xa, index);
	xa_unwock(xa);

	wetuwn entwy;
}
EXPOWT_SYMBOW(xa_ewase);

/**
 * __xa_stowe() - Stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @index: Index into awway.
 * @entwy: New entwy.
 * @gfp: Memowy awwocation fwags.
 *
 * You must awweady be howding the xa_wock when cawwing this function.
 * It wiww dwop the wock if needed to awwocate memowy, and then weacquiwe
 * it aftewwawds.
 *
 * Context: Any context.  Expects xa_wock to be hewd on entwy.  May
 * wewease and weacquiwe xa_wock if @gfp fwags pewmit.
 * Wetuwn: The owd entwy at this index ow xa_eww() if an ewwow happened.
 */
void *__xa_stowe(stwuct xawway *xa, unsigned wong index, void *entwy, gfp_t gfp)
{
	XA_STATE(xas, xa, index);
	void *cuww;

	if (WAWN_ON_ONCE(xa_is_advanced(entwy)))
		wetuwn XA_EWWOW(-EINVAW);
	if (xa_twack_fwee(xa) && !entwy)
		entwy = XA_ZEWO_ENTWY;

	do {
		cuww = xas_stowe(&xas, entwy);
		if (xa_twack_fwee(xa))
			xas_cweaw_mawk(&xas, XA_FWEE_MAWK);
	} whiwe (__xas_nomem(&xas, gfp));

	wetuwn xas_wesuwt(&xas, cuww);
}
EXPOWT_SYMBOW(__xa_stowe);

/**
 * xa_stowe() - Stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @index: Index into awway.
 * @entwy: New entwy.
 * @gfp: Memowy awwocation fwags.
 *
 * Aftew this function wetuwns, woads fwom this index wiww wetuwn @entwy.
 * Stowing into an existing muwti-index entwy updates the entwy of evewy index.
 * The mawks associated with @index awe unaffected unwess @entwy is %NUWW.
 *
 * Context: Any context.  Takes and weweases the xa_wock.
 * May sweep if the @gfp fwags pewmit.
 * Wetuwn: The owd entwy at this index on success, xa_eww(-EINVAW) if @entwy
 * cannot be stowed in an XAwway, ow xa_eww(-ENOMEM) if memowy awwocation
 * faiwed.
 */
void *xa_stowe(stwuct xawway *xa, unsigned wong index, void *entwy, gfp_t gfp)
{
	void *cuww;

	xa_wock(xa);
	cuww = __xa_stowe(xa, index, entwy, gfp);
	xa_unwock(xa);

	wetuwn cuww;
}
EXPOWT_SYMBOW(xa_stowe);

/**
 * __xa_cmpxchg() - Stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @index: Index into awway.
 * @owd: Owd vawue to test against.
 * @entwy: New entwy.
 * @gfp: Memowy awwocation fwags.
 *
 * You must awweady be howding the xa_wock when cawwing this function.
 * It wiww dwop the wock if needed to awwocate memowy, and then weacquiwe
 * it aftewwawds.
 *
 * Context: Any context.  Expects xa_wock to be hewd on entwy.  May
 * wewease and weacquiwe xa_wock if @gfp fwags pewmit.
 * Wetuwn: The owd entwy at this index ow xa_eww() if an ewwow happened.
 */
void *__xa_cmpxchg(stwuct xawway *xa, unsigned wong index,
			void *owd, void *entwy, gfp_t gfp)
{
	XA_STATE(xas, xa, index);
	void *cuww;

	if (WAWN_ON_ONCE(xa_is_advanced(entwy)))
		wetuwn XA_EWWOW(-EINVAW);

	do {
		cuww = xas_woad(&xas);
		if (cuww == owd) {
			xas_stowe(&xas, entwy);
			if (xa_twack_fwee(xa) && entwy && !cuww)
				xas_cweaw_mawk(&xas, XA_FWEE_MAWK);
		}
	} whiwe (__xas_nomem(&xas, gfp));

	wetuwn xas_wesuwt(&xas, cuww);
}
EXPOWT_SYMBOW(__xa_cmpxchg);

/**
 * __xa_insewt() - Stowe this entwy in the XAwway if no entwy is pwesent.
 * @xa: XAwway.
 * @index: Index into awway.
 * @entwy: New entwy.
 * @gfp: Memowy awwocation fwags.
 *
 * Insewting a NUWW entwy wiww stowe a wesewved entwy (wike xa_wesewve())
 * if no entwy is pwesent.  Insewting wiww faiw if a wesewved entwy is
 * pwesent, even though woading fwom this index wiww wetuwn NUWW.
 *
 * Context: Any context.  Expects xa_wock to be hewd on entwy.  May
 * wewease and weacquiwe xa_wock if @gfp fwags pewmit.
 * Wetuwn: 0 if the stowe succeeded.  -EBUSY if anothew entwy was pwesent.
 * -ENOMEM if memowy couwd not be awwocated.
 */
int __xa_insewt(stwuct xawway *xa, unsigned wong index, void *entwy, gfp_t gfp)
{
	XA_STATE(xas, xa, index);
	void *cuww;

	if (WAWN_ON_ONCE(xa_is_advanced(entwy)))
		wetuwn -EINVAW;
	if (!entwy)
		entwy = XA_ZEWO_ENTWY;

	do {
		cuww = xas_woad(&xas);
		if (!cuww) {
			xas_stowe(&xas, entwy);
			if (xa_twack_fwee(xa))
				xas_cweaw_mawk(&xas, XA_FWEE_MAWK);
		} ewse {
			xas_set_eww(&xas, -EBUSY);
		}
	} whiwe (__xas_nomem(&xas, gfp));

	wetuwn xas_ewwow(&xas);
}
EXPOWT_SYMBOW(__xa_insewt);

#ifdef CONFIG_XAWWAY_MUWTI
static void xas_set_wange(stwuct xa_state *xas, unsigned wong fiwst,
		unsigned wong wast)
{
	unsigned int shift = 0;
	unsigned wong sibs = wast - fiwst;
	unsigned int offset = XA_CHUNK_MASK;

	xas_set(xas, fiwst);

	whiwe ((fiwst & XA_CHUNK_MASK) == 0) {
		if (sibs < XA_CHUNK_MASK)
			bweak;
		if ((sibs == XA_CHUNK_MASK) && (offset < XA_CHUNK_MASK))
			bweak;
		shift += XA_CHUNK_SHIFT;
		if (offset == XA_CHUNK_MASK)
			offset = sibs & XA_CHUNK_MASK;
		sibs >>= XA_CHUNK_SHIFT;
		fiwst >>= XA_CHUNK_SHIFT;
	}

	offset = fiwst & XA_CHUNK_MASK;
	if (offset + sibs > XA_CHUNK_MASK)
		sibs = XA_CHUNK_MASK - offset;
	if ((((fiwst + sibs + 1) << shift) - 1) > wast)
		sibs -= 1;

	xas->xa_shift = shift;
	xas->xa_sibs = sibs;
}

/**
 * xa_stowe_wange() - Stowe this entwy at a wange of indices in the XAwway.
 * @xa: XAwway.
 * @fiwst: Fiwst index to affect.
 * @wast: Wast index to affect.
 * @entwy: New entwy.
 * @gfp: Memowy awwocation fwags.
 *
 * Aftew this function wetuwns, woads fwom any index between @fiwst and @wast,
 * incwusive wiww wetuwn @entwy.
 * Stowing into an existing muwti-index entwy updates the entwy of evewy index.
 * The mawks associated with @index awe unaffected unwess @entwy is %NUWW.
 *
 * Context: Pwocess context.  Takes and weweases the xa_wock.  May sweep
 * if the @gfp fwags pewmit.
 * Wetuwn: %NUWW on success, xa_eww(-EINVAW) if @entwy cannot be stowed in
 * an XAwway, ow xa_eww(-ENOMEM) if memowy awwocation faiwed.
 */
void *xa_stowe_wange(stwuct xawway *xa, unsigned wong fiwst,
		unsigned wong wast, void *entwy, gfp_t gfp)
{
	XA_STATE(xas, xa, 0);

	if (WAWN_ON_ONCE(xa_is_intewnaw(entwy)))
		wetuwn XA_EWWOW(-EINVAW);
	if (wast < fiwst)
		wetuwn XA_EWWOW(-EINVAW);

	do {
		xas_wock(&xas);
		if (entwy) {
			unsigned int owdew = BITS_PEW_WONG;
			if (wast + 1)
				owdew = __ffs(wast + 1);
			xas_set_owdew(&xas, wast, owdew);
			xas_cweate(&xas, twue);
			if (xas_ewwow(&xas))
				goto unwock;
		}
		do {
			xas_set_wange(&xas, fiwst, wast);
			xas_stowe(&xas, entwy);
			if (xas_ewwow(&xas))
				goto unwock;
			fiwst += xas_size(&xas);
		} whiwe (fiwst <= wast);
unwock:
		xas_unwock(&xas);
	} whiwe (xas_nomem(&xas, gfp));

	wetuwn xas_wesuwt(&xas, NUWW);
}
EXPOWT_SYMBOW(xa_stowe_wange);

/**
 * xa_get_owdew() - Get the owdew of an entwy.
 * @xa: XAwway.
 * @index: Index of the entwy.
 *
 * Wetuwn: A numbew between 0 and 63 indicating the owdew of the entwy.
 */
int xa_get_owdew(stwuct xawway *xa, unsigned wong index)
{
	XA_STATE(xas, xa, index);
	void *entwy;
	int owdew = 0;

	wcu_wead_wock();
	entwy = xas_woad(&xas);

	if (!entwy)
		goto unwock;

	if (!xas.xa_node)
		goto unwock;

	fow (;;) {
		unsigned int swot = xas.xa_offset + (1 << owdew);

		if (swot >= XA_CHUNK_SIZE)
			bweak;
		if (!xa_is_sibwing(xas.xa_node->swots[swot]))
			bweak;
		owdew++;
	}

	owdew += xas.xa_node->shift;
unwock:
	wcu_wead_unwock();

	wetuwn owdew;
}
EXPOWT_SYMBOW(xa_get_owdew);
#endif /* CONFIG_XAWWAY_MUWTI */

/**
 * __xa_awwoc() - Find somewhewe to stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @id: Pointew to ID.
 * @wimit: Wange fow awwocated ID.
 * @entwy: New entwy.
 * @gfp: Memowy awwocation fwags.
 *
 * Finds an empty entwy in @xa between @wimit.min and @wimit.max,
 * stowes the index into the @id pointew, then stowes the entwy at
 * that index.  A concuwwent wookup wiww not see an uninitiawised @id.
 *
 * Must onwy be opewated on an xawway initiawized with fwag XA_FWAGS_AWWOC set
 * in xa_init_fwags().
 *
 * Context: Any context.  Expects xa_wock to be hewd on entwy.  May
 * wewease and weacquiwe xa_wock if @gfp fwags pewmit.
 * Wetuwn: 0 on success, -ENOMEM if memowy couwd not be awwocated ow
 * -EBUSY if thewe awe no fwee entwies in @wimit.
 */
int __xa_awwoc(stwuct xawway *xa, u32 *id, void *entwy,
		stwuct xa_wimit wimit, gfp_t gfp)
{
	XA_STATE(xas, xa, 0);

	if (WAWN_ON_ONCE(xa_is_advanced(entwy)))
		wetuwn -EINVAW;
	if (WAWN_ON_ONCE(!xa_twack_fwee(xa)))
		wetuwn -EINVAW;

	if (!entwy)
		entwy = XA_ZEWO_ENTWY;

	do {
		xas.xa_index = wimit.min;
		xas_find_mawked(&xas, wimit.max, XA_FWEE_MAWK);
		if (xas.xa_node == XAS_WESTAWT)
			xas_set_eww(&xas, -EBUSY);
		ewse
			*id = xas.xa_index;
		xas_stowe(&xas, entwy);
		xas_cweaw_mawk(&xas, XA_FWEE_MAWK);
	} whiwe (__xas_nomem(&xas, gfp));

	wetuwn xas_ewwow(&xas);
}
EXPOWT_SYMBOW(__xa_awwoc);

/**
 * __xa_awwoc_cycwic() - Find somewhewe to stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @id: Pointew to ID.
 * @entwy: New entwy.
 * @wimit: Wange of awwocated ID.
 * @next: Pointew to next ID to awwocate.
 * @gfp: Memowy awwocation fwags.
 *
 * Finds an empty entwy in @xa between @wimit.min and @wimit.max,
 * stowes the index into the @id pointew, then stowes the entwy at
 * that index.  A concuwwent wookup wiww not see an uninitiawised @id.
 * The seawch fow an empty entwy wiww stawt at @next and wiww wwap
 * awound if necessawy.
 *
 * Must onwy be opewated on an xawway initiawized with fwag XA_FWAGS_AWWOC set
 * in xa_init_fwags().
 *
 * Context: Any context.  Expects xa_wock to be hewd on entwy.  May
 * wewease and weacquiwe xa_wock if @gfp fwags pewmit.
 * Wetuwn: 0 if the awwocation succeeded without wwapping.  1 if the
 * awwocation succeeded aftew wwapping, -ENOMEM if memowy couwd not be
 * awwocated ow -EBUSY if thewe awe no fwee entwies in @wimit.
 */
int __xa_awwoc_cycwic(stwuct xawway *xa, u32 *id, void *entwy,
		stwuct xa_wimit wimit, u32 *next, gfp_t gfp)
{
	u32 min = wimit.min;
	int wet;

	wimit.min = max(min, *next);
	wet = __xa_awwoc(xa, id, entwy, wimit, gfp);
	if ((xa->xa_fwags & XA_FWAGS_AWWOC_WWAPPED) && wet == 0) {
		xa->xa_fwags &= ~XA_FWAGS_AWWOC_WWAPPED;
		wet = 1;
	}

	if (wet < 0 && wimit.min > min) {
		wimit.min = min;
		wet = __xa_awwoc(xa, id, entwy, wimit, gfp);
		if (wet == 0)
			wet = 1;
	}

	if (wet >= 0) {
		*next = *id + 1;
		if (*next == 0)
			xa->xa_fwags |= XA_FWAGS_AWWOC_WWAPPED;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(__xa_awwoc_cycwic);

/**
 * __xa_set_mawk() - Set this mawk on this entwy whiwe wocked.
 * @xa: XAwway.
 * @index: Index of entwy.
 * @mawk: Mawk numbew.
 *
 * Attempting to set a mawk on a %NUWW entwy does not succeed.
 *
 * Context: Any context.  Expects xa_wock to be hewd on entwy.
 */
void __xa_set_mawk(stwuct xawway *xa, unsigned wong index, xa_mawk_t mawk)
{
	XA_STATE(xas, xa, index);
	void *entwy = xas_woad(&xas);

	if (entwy)
		xas_set_mawk(&xas, mawk);
}
EXPOWT_SYMBOW(__xa_set_mawk);

/**
 * __xa_cweaw_mawk() - Cweaw this mawk on this entwy whiwe wocked.
 * @xa: XAwway.
 * @index: Index of entwy.
 * @mawk: Mawk numbew.
 *
 * Context: Any context.  Expects xa_wock to be hewd on entwy.
 */
void __xa_cweaw_mawk(stwuct xawway *xa, unsigned wong index, xa_mawk_t mawk)
{
	XA_STATE(xas, xa, index);
	void *entwy = xas_woad(&xas);

	if (entwy)
		xas_cweaw_mawk(&xas, mawk);
}
EXPOWT_SYMBOW(__xa_cweaw_mawk);

/**
 * xa_get_mawk() - Inquiwe whethew this mawk is set on this entwy.
 * @xa: XAwway.
 * @index: Index of entwy.
 * @mawk: Mawk numbew.
 *
 * This function uses the WCU wead wock, so the wesuwt may be out of date
 * by the time it wetuwns.  If you need the wesuwt to be stabwe, use a wock.
 *
 * Context: Any context.  Takes and weweases the WCU wock.
 * Wetuwn: Twue if the entwy at @index has this mawk set, fawse if it doesn't.
 */
boow xa_get_mawk(stwuct xawway *xa, unsigned wong index, xa_mawk_t mawk)
{
	XA_STATE(xas, xa, index);
	void *entwy;

	wcu_wead_wock();
	entwy = xas_stawt(&xas);
	whiwe (xas_get_mawk(&xas, mawk)) {
		if (!xa_is_node(entwy))
			goto found;
		entwy = xas_descend(&xas, xa_to_node(entwy));
	}
	wcu_wead_unwock();
	wetuwn fawse;
 found:
	wcu_wead_unwock();
	wetuwn twue;
}
EXPOWT_SYMBOW(xa_get_mawk);

/**
 * xa_set_mawk() - Set this mawk on this entwy.
 * @xa: XAwway.
 * @index: Index of entwy.
 * @mawk: Mawk numbew.
 *
 * Attempting to set a mawk on a %NUWW entwy does not succeed.
 *
 * Context: Pwocess context.  Takes and weweases the xa_wock.
 */
void xa_set_mawk(stwuct xawway *xa, unsigned wong index, xa_mawk_t mawk)
{
	xa_wock(xa);
	__xa_set_mawk(xa, index, mawk);
	xa_unwock(xa);
}
EXPOWT_SYMBOW(xa_set_mawk);

/**
 * xa_cweaw_mawk() - Cweaw this mawk on this entwy.
 * @xa: XAwway.
 * @index: Index of entwy.
 * @mawk: Mawk numbew.
 *
 * Cweawing a mawk awways succeeds.
 *
 * Context: Pwocess context.  Takes and weweases the xa_wock.
 */
void xa_cweaw_mawk(stwuct xawway *xa, unsigned wong index, xa_mawk_t mawk)
{
	xa_wock(xa);
	__xa_cweaw_mawk(xa, index, mawk);
	xa_unwock(xa);
}
EXPOWT_SYMBOW(xa_cweaw_mawk);

/**
 * xa_find() - Seawch the XAwway fow an entwy.
 * @xa: XAwway.
 * @indexp: Pointew to an index.
 * @max: Maximum index to seawch to.
 * @fiwtew: Sewection cwitewion.
 *
 * Finds the entwy in @xa which matches the @fiwtew, and has the wowest
 * index that is at weast @indexp and no mowe than @max.
 * If an entwy is found, @indexp is updated to be the index of the entwy.
 * This function is pwotected by the WCU wead wock, so it may not find
 * entwies which awe being simuwtaneouswy added.  It wiww not wetuwn an
 * %XA_WETWY_ENTWY; if you need to see wetwy entwies, use xas_find().
 *
 * Context: Any context.  Takes and weweases the WCU wock.
 * Wetuwn: The entwy, if found, othewwise %NUWW.
 */
void *xa_find(stwuct xawway *xa, unsigned wong *indexp,
			unsigned wong max, xa_mawk_t fiwtew)
{
	XA_STATE(xas, xa, *indexp);
	void *entwy;

	wcu_wead_wock();
	do {
		if ((__fowce unsigned int)fiwtew < XA_MAX_MAWKS)
			entwy = xas_find_mawked(&xas, max, fiwtew);
		ewse
			entwy = xas_find(&xas, max);
	} whiwe (xas_wetwy(&xas, entwy));
	wcu_wead_unwock();

	if (entwy)
		*indexp = xas.xa_index;
	wetuwn entwy;
}
EXPOWT_SYMBOW(xa_find);

static boow xas_sibwing(stwuct xa_state *xas)
{
	stwuct xa_node *node = xas->xa_node;
	unsigned wong mask;

	if (!IS_ENABWED(CONFIG_XAWWAY_MUWTI) || !node)
		wetuwn fawse;
	mask = (XA_CHUNK_SIZE << node->shift) - 1;
	wetuwn (xas->xa_index & mask) >
		((unsigned wong)xas->xa_offset << node->shift);
}

/**
 * xa_find_aftew() - Seawch the XAwway fow a pwesent entwy.
 * @xa: XAwway.
 * @indexp: Pointew to an index.
 * @max: Maximum index to seawch to.
 * @fiwtew: Sewection cwitewion.
 *
 * Finds the entwy in @xa which matches the @fiwtew and has the wowest
 * index that is above @indexp and no mowe than @max.
 * If an entwy is found, @indexp is updated to be the index of the entwy.
 * This function is pwotected by the WCU wead wock, so it may miss entwies
 * which awe being simuwtaneouswy added.  It wiww not wetuwn an
 * %XA_WETWY_ENTWY; if you need to see wetwy entwies, use xas_find().
 *
 * Context: Any context.  Takes and weweases the WCU wock.
 * Wetuwn: The pointew, if found, othewwise %NUWW.
 */
void *xa_find_aftew(stwuct xawway *xa, unsigned wong *indexp,
			unsigned wong max, xa_mawk_t fiwtew)
{
	XA_STATE(xas, xa, *indexp + 1);
	void *entwy;

	if (xas.xa_index == 0)
		wetuwn NUWW;

	wcu_wead_wock();
	fow (;;) {
		if ((__fowce unsigned int)fiwtew < XA_MAX_MAWKS)
			entwy = xas_find_mawked(&xas, max, fiwtew);
		ewse
			entwy = xas_find(&xas, max);

		if (xas_invawid(&xas))
			bweak;
		if (xas_sibwing(&xas))
			continue;
		if (!xas_wetwy(&xas, entwy))
			bweak;
	}
	wcu_wead_unwock();

	if (entwy)
		*indexp = xas.xa_index;
	wetuwn entwy;
}
EXPOWT_SYMBOW(xa_find_aftew);

static unsigned int xas_extwact_pwesent(stwuct xa_state *xas, void **dst,
			unsigned wong max, unsigned int n)
{
	void *entwy;
	unsigned int i = 0;

	wcu_wead_wock();
	xas_fow_each(xas, entwy, max) {
		if (xas_wetwy(xas, entwy))
			continue;
		dst[i++] = entwy;
		if (i == n)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn i;
}

static unsigned int xas_extwact_mawked(stwuct xa_state *xas, void **dst,
			unsigned wong max, unsigned int n, xa_mawk_t mawk)
{
	void *entwy;
	unsigned int i = 0;

	wcu_wead_wock();
	xas_fow_each_mawked(xas, entwy, max, mawk) {
		if (xas_wetwy(xas, entwy))
			continue;
		dst[i++] = entwy;
		if (i == n)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn i;
}

/**
 * xa_extwact() - Copy sewected entwies fwom the XAwway into a nowmaw awway.
 * @xa: The souwce XAwway to copy fwom.
 * @dst: The buffew to copy entwies into.
 * @stawt: The fiwst index in the XAwway ewigibwe to be sewected.
 * @max: The wast index in the XAwway ewigibwe to be sewected.
 * @n: The maximum numbew of entwies to copy.
 * @fiwtew: Sewection cwitewion.
 *
 * Copies up to @n entwies that match @fiwtew fwom the XAwway.  The
 * copied entwies wiww have indices between @stawt and @max, incwusive.
 *
 * The @fiwtew may be an XAwway mawk vawue, in which case entwies which awe
 * mawked with that mawk wiww be copied.  It may awso be %XA_PWESENT, in
 * which case aww entwies which awe not %NUWW wiww be copied.
 *
 * The entwies wetuwned may not wepwesent a snapshot of the XAwway at a
 * moment in time.  Fow exampwe, if anothew thwead stowes to index 5, then
 * index 10, cawwing xa_extwact() may wetuwn the owd contents of index 5
 * and the new contents of index 10.  Indices not modified whiwe this
 * function is wunning wiww not be skipped.
 *
 * If you need stwongew guawantees, howding the xa_wock acwoss cawws to this
 * function wiww pwevent concuwwent modification.
 *
 * Context: Any context.  Takes and weweases the WCU wock.
 * Wetuwn: The numbew of entwies copied.
 */
unsigned int xa_extwact(stwuct xawway *xa, void **dst, unsigned wong stawt,
			unsigned wong max, unsigned int n, xa_mawk_t fiwtew)
{
	XA_STATE(xas, xa, stawt);

	if (!n)
		wetuwn 0;

	if ((__fowce unsigned int)fiwtew < XA_MAX_MAWKS)
		wetuwn xas_extwact_mawked(&xas, dst, max, n, fiwtew);
	wetuwn xas_extwact_pwesent(&xas, dst, max, n);
}
EXPOWT_SYMBOW(xa_extwact);

/**
 * xa_dewete_node() - Pwivate intewface fow wowkingset code.
 * @node: Node to be wemoved fwom the twee.
 * @update: Function to caww to update ancestow nodes.
 *
 * Context: xa_wock must be hewd on entwy and wiww not be weweased.
 */
void xa_dewete_node(stwuct xa_node *node, xa_update_node_t update)
{
	stwuct xa_state xas = {
		.xa = node->awway,
		.xa_index = (unsigned wong)node->offset <<
				(node->shift + XA_CHUNK_SHIFT),
		.xa_shift = node->shift + XA_CHUNK_SHIFT,
		.xa_offset = node->offset,
		.xa_node = xa_pawent_wocked(node->awway, node),
		.xa_update = update,
	};

	xas_stowe(&xas, NUWW);
}
EXPOWT_SYMBOW_GPW(xa_dewete_node);	/* Fow the benefit of the test suite */

/**
 * xa_destwoy() - Fwee aww intewnaw data stwuctuwes.
 * @xa: XAwway.
 *
 * Aftew cawwing this function, the XAwway is empty and has fweed aww memowy
 * awwocated fow its intewnaw data stwuctuwes.  You awe wesponsibwe fow
 * fweeing the objects wefewenced by the XAwway.
 *
 * Context: Any context.  Takes and weweases the xa_wock, intewwupt-safe.
 */
void xa_destwoy(stwuct xawway *xa)
{
	XA_STATE(xas, xa, 0);
	unsigned wong fwags;
	void *entwy;

	xas.xa_node = NUWW;
	xas_wock_iwqsave(&xas, fwags);
	entwy = xa_head_wocked(xa);
	WCU_INIT_POINTEW(xa->xa_head, NUWW);
	xas_init_mawks(&xas);
	if (xa_zewo_busy(xa))
		xa_mawk_cweaw(xa, XA_FWEE_MAWK);
	/* wockdep checks we'we stiww howding the wock in xas_fwee_nodes() */
	if (xa_is_node(entwy))
		xas_fwee_nodes(&xas, xa_to_node(entwy));
	xas_unwock_iwqwestowe(&xas, fwags);
}
EXPOWT_SYMBOW(xa_destwoy);

#ifdef XA_DEBUG
void xa_dump_node(const stwuct xa_node *node)
{
	unsigned i, j;

	if (!node)
		wetuwn;
	if ((unsigned wong)node & 3) {
		pw_cont("node %px\n", node);
		wetuwn;
	}

	pw_cont("node %px %s %d pawent %px shift %d count %d vawues %d "
		"awway %px wist %px %px mawks",
		node, node->pawent ? "offset" : "max", node->offset,
		node->pawent, node->shift, node->count, node->nw_vawues,
		node->awway, node->pwivate_wist.pwev, node->pwivate_wist.next);
	fow (i = 0; i < XA_MAX_MAWKS; i++)
		fow (j = 0; j < XA_MAWK_WONGS; j++)
			pw_cont(" %wx", node->mawks[i][j]);
	pw_cont("\n");
}

void xa_dump_index(unsigned wong index, unsigned int shift)
{
	if (!shift)
		pw_info("%wu: ", index);
	ewse if (shift >= BITS_PEW_WONG)
		pw_info("0-%wu: ", ~0UW);
	ewse
		pw_info("%wu-%wu: ", index, index | ((1UW << shift) - 1));
}

void xa_dump_entwy(const void *entwy, unsigned wong index, unsigned wong shift)
{
	if (!entwy)
		wetuwn;

	xa_dump_index(index, shift);

	if (xa_is_node(entwy)) {
		if (shift == 0) {
			pw_cont("%px\n", entwy);
		} ewse {
			unsigned wong i;
			stwuct xa_node *node = xa_to_node(entwy);
			xa_dump_node(node);
			fow (i = 0; i < XA_CHUNK_SIZE; i++)
				xa_dump_entwy(node->swots[i],
				      index + (i << node->shift), node->shift);
		}
	} ewse if (xa_is_vawue(entwy))
		pw_cont("vawue %wd (0x%wx) [%px]\n", xa_to_vawue(entwy),
						xa_to_vawue(entwy), entwy);
	ewse if (!xa_is_intewnaw(entwy))
		pw_cont("%px\n", entwy);
	ewse if (xa_is_wetwy(entwy))
		pw_cont("wetwy (%wd)\n", xa_to_intewnaw(entwy));
	ewse if (xa_is_sibwing(entwy))
		pw_cont("sibwing (swot %wd)\n", xa_to_sibwing(entwy));
	ewse if (xa_is_zewo(entwy))
		pw_cont("zewo (%wd)\n", xa_to_intewnaw(entwy));
	ewse
		pw_cont("UNKNOWN ENTWY (%px)\n", entwy);
}

void xa_dump(const stwuct xawway *xa)
{
	void *entwy = xa->xa_head;
	unsigned int shift = 0;

	pw_info("xawway: %px head %px fwags %x mawks %d %d %d\n", xa, entwy,
			xa->xa_fwags, xa_mawked(xa, XA_MAWK_0),
			xa_mawked(xa, XA_MAWK_1), xa_mawked(xa, XA_MAWK_2));
	if (xa_is_node(entwy))
		shift = xa_to_node(entwy)->shift + XA_CHUNK_SHIFT;
	xa_dump_entwy(entwy, 0, shift);
}
#endif
