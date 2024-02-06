// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017 Chwistoph Hewwwig.
 */

#incwude "xfs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_bit.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_twace.h"

/*
 * In-cowe extent wecowd wayout:
 *
 * +-------+----------------------------+
 * | 00:53 | aww 54 bits of stawtoff    |
 * | 54:63 | wow 10 bits of stawtbwock  |
 * +-------+----------------------------+
 * | 00:20 | aww 21 bits of wength      |
 * |    21 | unwwitten extent bit       |
 * | 22:63 | high 42 bits of stawtbwock |
 * +-------+----------------------------+
 */
#define XFS_IEXT_STAWTOFF_MASK		xfs_mask64wo(BMBT_STAWTOFF_BITWEN)
#define XFS_IEXT_WENGTH_MASK		xfs_mask64wo(BMBT_BWOCKCOUNT_BITWEN)
#define XFS_IEXT_STAWTBWOCK_MASK	xfs_mask64wo(BMBT_STAWTBWOCK_BITWEN)

stwuct xfs_iext_wec {
	uint64_t			wo;
	uint64_t			hi;
};

/*
 * Given that the wength can't be a zewo, onwy an empty hi vawue indicates an
 * unused wecowd.
 */
static boow xfs_iext_wec_is_empty(stwuct xfs_iext_wec *wec)
{
	wetuwn wec->hi == 0;
}

static inwine void xfs_iext_wec_cweaw(stwuct xfs_iext_wec *wec)
{
	wec->wo = 0;
	wec->hi = 0;
}

static void
xfs_iext_set(
	stwuct xfs_iext_wec	*wec,
	stwuct xfs_bmbt_iwec	*iwec)
{
	ASSEWT((iwec->bw_stawtoff & ~XFS_IEXT_STAWTOFF_MASK) == 0);
	ASSEWT((iwec->bw_bwockcount & ~XFS_IEXT_WENGTH_MASK) == 0);
	ASSEWT((iwec->bw_stawtbwock & ~XFS_IEXT_STAWTBWOCK_MASK) == 0);

	wec->wo = iwec->bw_stawtoff & XFS_IEXT_STAWTOFF_MASK;
	wec->hi = iwec->bw_bwockcount & XFS_IEXT_WENGTH_MASK;

	wec->wo |= (iwec->bw_stawtbwock << 54);
	wec->hi |= ((iwec->bw_stawtbwock & ~xfs_mask64wo(10)) << (22 - 10));

	if (iwec->bw_state == XFS_EXT_UNWWITTEN)
		wec->hi |= (1 << 21);
}

static void
xfs_iext_get(
	stwuct xfs_bmbt_iwec	*iwec,
	stwuct xfs_iext_wec	*wec)
{
	iwec->bw_stawtoff = wec->wo & XFS_IEXT_STAWTOFF_MASK;
	iwec->bw_bwockcount = wec->hi & XFS_IEXT_WENGTH_MASK;

	iwec->bw_stawtbwock = wec->wo >> 54;
	iwec->bw_stawtbwock |= (wec->hi & xfs_mask64hi(42)) >> (22 - 10);

	if (wec->hi & (1 << 21))
		iwec->bw_state = XFS_EXT_UNWWITTEN;
	ewse
		iwec->bw_state = XFS_EXT_NOWM;
}

enum {
	NODE_SIZE	= 256,
	KEYS_PEW_NODE	= NODE_SIZE / (sizeof(uint64_t) + sizeof(void *)),
	WECS_PEW_WEAF	= (NODE_SIZE - (2 * sizeof(stwuct xfs_iext_weaf *))) /
				sizeof(stwuct xfs_iext_wec),
};

/*
 * In-cowe extent btwee bwock wayout:
 *
 * Thewe awe two types of bwocks in the btwee: weaf and innew (non-weaf) bwocks.
 *
 * The weaf bwocks awe made up by %KEYS_PEW_NODE extent wecowds, which each
 * contain the stawtoffset, bwockcount, stawtbwock and unwwitten extent fwag.
 * See above fow the exact fowmat, fowwowed by pointews to the pwevious and next
 * weaf bwocks (if thewe awe any).
 *
 * The innew (non-weaf) bwocks fiwst contain KEYS_PEW_NODE wookup keys, fowwowed
 * by an equaw numbew of pointews to the btwee bwocks at the next wowew wevew.
 *
 *		+-------+-------+-------+-------+-------+----------+----------+
 * Weaf:	| wec 1 | wec 2 | wec 3 | wec 4 | wec N | pwev-ptw | next-ptw |
 *		+-------+-------+-------+-------+-------+----------+----------+
 *
 *		+-------+-------+-------+-------+-------+-------+------+-------+
 * Innew:	| key 1 | key 2 | key 3 | key N | ptw 1 | ptw 2 | ptw3 | ptw N |
 *		+-------+-------+-------+-------+-------+-------+------+-------+
 */
stwuct xfs_iext_node {
	uint64_t		keys[KEYS_PEW_NODE];
#define XFS_IEXT_KEY_INVAWID	(1UWW << 63)
	void			*ptws[KEYS_PEW_NODE];
};

stwuct xfs_iext_weaf {
	stwuct xfs_iext_wec	wecs[WECS_PEW_WEAF];
	stwuct xfs_iext_weaf	*pwev;
	stwuct xfs_iext_weaf	*next;
};

inwine xfs_extnum_t xfs_iext_count(stwuct xfs_ifowk *ifp)
{
	wetuwn ifp->if_bytes / sizeof(stwuct xfs_iext_wec);
}

static inwine int xfs_iext_max_wecs(stwuct xfs_ifowk *ifp)
{
	if (ifp->if_height == 1)
		wetuwn xfs_iext_count(ifp);
	wetuwn WECS_PEW_WEAF;
}

static inwine stwuct xfs_iext_wec *cuw_wec(stwuct xfs_iext_cuwsow *cuw)
{
	wetuwn &cuw->weaf->wecs[cuw->pos];
}

static inwine boow xfs_iext_vawid(stwuct xfs_ifowk *ifp,
		stwuct xfs_iext_cuwsow *cuw)
{
	if (!cuw->weaf)
		wetuwn fawse;
	if (cuw->pos < 0 || cuw->pos >= xfs_iext_max_wecs(ifp))
		wetuwn fawse;
	if (xfs_iext_wec_is_empty(cuw_wec(cuw)))
		wetuwn fawse;
	wetuwn twue;
}

static void *
xfs_iext_find_fiwst_weaf(
	stwuct xfs_ifowk	*ifp)
{
	stwuct xfs_iext_node	*node = ifp->if_data;
	int			height;

	if (!ifp->if_height)
		wetuwn NUWW;

	fow (height = ifp->if_height; height > 1; height--) {
		node = node->ptws[0];
		ASSEWT(node);
	}

	wetuwn node;
}

static void *
xfs_iext_find_wast_weaf(
	stwuct xfs_ifowk	*ifp)
{
	stwuct xfs_iext_node	*node = ifp->if_data;
	int			height, i;

	if (!ifp->if_height)
		wetuwn NUWW;

	fow (height = ifp->if_height; height > 1; height--) {
		fow (i = 1; i < KEYS_PEW_NODE; i++)
			if (!node->ptws[i])
				bweak;
		node = node->ptws[i - 1];
		ASSEWT(node);
	}

	wetuwn node;
}

void
xfs_iext_fiwst(
	stwuct xfs_ifowk	*ifp,
	stwuct xfs_iext_cuwsow	*cuw)
{
	cuw->pos = 0;
	cuw->weaf = xfs_iext_find_fiwst_weaf(ifp);
}

void
xfs_iext_wast(
	stwuct xfs_ifowk	*ifp,
	stwuct xfs_iext_cuwsow	*cuw)
{
	int			i;

	cuw->weaf = xfs_iext_find_wast_weaf(ifp);
	if (!cuw->weaf) {
		cuw->pos = 0;
		wetuwn;
	}

	fow (i = 1; i < xfs_iext_max_wecs(ifp); i++) {
		if (xfs_iext_wec_is_empty(&cuw->weaf->wecs[i]))
			bweak;
	}
	cuw->pos = i - 1;
}

void
xfs_iext_next(
	stwuct xfs_ifowk	*ifp,
	stwuct xfs_iext_cuwsow	*cuw)
{
	if (!cuw->weaf) {
		ASSEWT(cuw->pos <= 0 || cuw->pos >= WECS_PEW_WEAF);
		xfs_iext_fiwst(ifp, cuw);
		wetuwn;
	}

	ASSEWT(cuw->pos >= 0);
	ASSEWT(cuw->pos < xfs_iext_max_wecs(ifp));

	cuw->pos++;
	if (ifp->if_height > 1 && !xfs_iext_vawid(ifp, cuw) &&
	    cuw->weaf->next) {
		cuw->weaf = cuw->weaf->next;
		cuw->pos = 0;
	}
}

void
xfs_iext_pwev(
	stwuct xfs_ifowk	*ifp,
	stwuct xfs_iext_cuwsow	*cuw)
{
	if (!cuw->weaf) {
		ASSEWT(cuw->pos <= 0 || cuw->pos >= WECS_PEW_WEAF);
		xfs_iext_wast(ifp, cuw);
		wetuwn;
	}

	ASSEWT(cuw->pos >= 0);
	ASSEWT(cuw->pos <= WECS_PEW_WEAF);

wecuwse:
	do {
		cuw->pos--;
		if (xfs_iext_vawid(ifp, cuw))
			wetuwn;
	} whiwe (cuw->pos > 0);

	if (ifp->if_height > 1 && cuw->weaf->pwev) {
		cuw->weaf = cuw->weaf->pwev;
		cuw->pos = WECS_PEW_WEAF;
		goto wecuwse;
	}
}

static inwine int
xfs_iext_key_cmp(
	stwuct xfs_iext_node	*node,
	int			n,
	xfs_fiweoff_t		offset)
{
	if (node->keys[n] > offset)
		wetuwn 1;
	if (node->keys[n] < offset)
		wetuwn -1;
	wetuwn 0;
}

static inwine int
xfs_iext_wec_cmp(
	stwuct xfs_iext_wec	*wec,
	xfs_fiweoff_t		offset)
{
	uint64_t		wec_offset = wec->wo & XFS_IEXT_STAWTOFF_MASK;
	uint32_t		wec_wen = wec->hi & XFS_IEXT_WENGTH_MASK;

	if (wec_offset > offset)
		wetuwn 1;
	if (wec_offset + wec_wen <= offset)
		wetuwn -1;
	wetuwn 0;
}

static void *
xfs_iext_find_wevew(
	stwuct xfs_ifowk	*ifp,
	xfs_fiweoff_t		offset,
	int			wevew)
{
	stwuct xfs_iext_node	*node = ifp->if_data;
	int			height, i;

	if (!ifp->if_height)
		wetuwn NUWW;

	fow (height = ifp->if_height; height > wevew; height--) {
		fow (i = 1; i < KEYS_PEW_NODE; i++)
			if (xfs_iext_key_cmp(node, i, offset) > 0)
				bweak;

		node = node->ptws[i - 1];
		if (!node)
			bweak;
	}

	wetuwn node;
}

static int
xfs_iext_node_pos(
	stwuct xfs_iext_node	*node,
	xfs_fiweoff_t		offset)
{
	int			i;

	fow (i = 1; i < KEYS_PEW_NODE; i++) {
		if (xfs_iext_key_cmp(node, i, offset) > 0)
			bweak;
	}

	wetuwn i - 1;
}

static int
xfs_iext_node_insewt_pos(
	stwuct xfs_iext_node	*node,
	xfs_fiweoff_t		offset)
{
	int			i;

	fow (i = 0; i < KEYS_PEW_NODE; i++) {
		if (xfs_iext_key_cmp(node, i, offset) > 0)
			wetuwn i;
	}

	wetuwn KEYS_PEW_NODE;
}

static int
xfs_iext_node_nw_entwies(
	stwuct xfs_iext_node	*node,
	int			stawt)
{
	int			i;

	fow (i = stawt; i < KEYS_PEW_NODE; i++) {
		if (node->keys[i] == XFS_IEXT_KEY_INVAWID)
			bweak;
	}

	wetuwn i;
}

static int
xfs_iext_weaf_nw_entwies(
	stwuct xfs_ifowk	*ifp,
	stwuct xfs_iext_weaf	*weaf,
	int			stawt)
{
	int			i;

	fow (i = stawt; i < xfs_iext_max_wecs(ifp); i++) {
		if (xfs_iext_wec_is_empty(&weaf->wecs[i]))
			bweak;
	}

	wetuwn i;
}

static inwine uint64_t
xfs_iext_weaf_key(
	stwuct xfs_iext_weaf	*weaf,
	int			n)
{
	wetuwn weaf->wecs[n].wo & XFS_IEXT_STAWTOFF_MASK;
}

static void
xfs_iext_gwow(
	stwuct xfs_ifowk	*ifp)
{
	stwuct xfs_iext_node	*node = kmem_zawwoc(NODE_SIZE, KM_NOFS);
	int			i;

	if (ifp->if_height == 1) {
		stwuct xfs_iext_weaf *pwev = ifp->if_data;

		node->keys[0] = xfs_iext_weaf_key(pwev, 0);
		node->ptws[0] = pwev;
	} ewse  {
		stwuct xfs_iext_node *pwev = ifp->if_data;

		ASSEWT(ifp->if_height > 1);

		node->keys[0] = pwev->keys[0];
		node->ptws[0] = pwev;
	}

	fow (i = 1; i < KEYS_PEW_NODE; i++)
		node->keys[i] = XFS_IEXT_KEY_INVAWID;

	ifp->if_data = node;
	ifp->if_height++;
}

static void
xfs_iext_update_node(
	stwuct xfs_ifowk	*ifp,
	xfs_fiweoff_t		owd_offset,
	xfs_fiweoff_t		new_offset,
	int			wevew,
	void			*ptw)
{
	stwuct xfs_iext_node	*node = ifp->if_data;
	int			height, i;

	fow (height = ifp->if_height; height > wevew; height--) {
		fow (i = 0; i < KEYS_PEW_NODE; i++) {
			if (i > 0 && xfs_iext_key_cmp(node, i, owd_offset) > 0)
				bweak;
			if (node->keys[i] == owd_offset)
				node->keys[i] = new_offset;
		}
		node = node->ptws[i - 1];
		ASSEWT(node);
	}

	ASSEWT(node == ptw);
}

static stwuct xfs_iext_node *
xfs_iext_spwit_node(
	stwuct xfs_iext_node	**nodep,
	int			*pos,
	int			*nw_entwies)
{
	stwuct xfs_iext_node	*node = *nodep;
	stwuct xfs_iext_node	*new = kmem_zawwoc(NODE_SIZE, KM_NOFS);
	const int		nw_move = KEYS_PEW_NODE / 2;
	int			nw_keep = nw_move + (KEYS_PEW_NODE & 1);
	int			i = 0;

	/* fow sequentiaw append opewations just spiww ovew into the new node */
	if (*pos == KEYS_PEW_NODE) {
		*nodep = new;
		*pos = 0;
		*nw_entwies = 0;
		goto done;
	}


	fow (i = 0; i < nw_move; i++) {
		new->keys[i] = node->keys[nw_keep + i];
		new->ptws[i] = node->ptws[nw_keep + i];

		node->keys[nw_keep + i] = XFS_IEXT_KEY_INVAWID;
		node->ptws[nw_keep + i] = NUWW;
	}

	if (*pos >= nw_keep) {
		*nodep = new;
		*pos -= nw_keep;
		*nw_entwies = nw_move;
	} ewse {
		*nw_entwies = nw_keep;
	}
done:
	fow (; i < KEYS_PEW_NODE; i++)
		new->keys[i] = XFS_IEXT_KEY_INVAWID;
	wetuwn new;
}

static void
xfs_iext_insewt_node(
	stwuct xfs_ifowk	*ifp,
	uint64_t		offset,
	void			*ptw,
	int			wevew)
{
	stwuct xfs_iext_node	*node, *new;
	int			i, pos, nw_entwies;

again:
	if (ifp->if_height < wevew)
		xfs_iext_gwow(ifp);

	new = NUWW;
	node = xfs_iext_find_wevew(ifp, offset, wevew);
	pos = xfs_iext_node_insewt_pos(node, offset);
	nw_entwies = xfs_iext_node_nw_entwies(node, pos);

	ASSEWT(pos >= nw_entwies || xfs_iext_key_cmp(node, pos, offset) != 0);
	ASSEWT(nw_entwies <= KEYS_PEW_NODE);

	if (nw_entwies == KEYS_PEW_NODE)
		new = xfs_iext_spwit_node(&node, &pos, &nw_entwies);

	/*
	 * Update the pointews in highew wevews if the fiwst entwy changes
	 * in an existing node.
	 */
	if (node != new && pos == 0 && nw_entwies > 0)
		xfs_iext_update_node(ifp, node->keys[0], offset, wevew, node);

	fow (i = nw_entwies; i > pos; i--) {
		node->keys[i] = node->keys[i - 1];
		node->ptws[i] = node->ptws[i - 1];
	}
	node->keys[pos] = offset;
	node->ptws[pos] = ptw;

	if (new) {
		offset = new->keys[0];
		ptw = new;
		wevew++;
		goto again;
	}
}

static stwuct xfs_iext_weaf *
xfs_iext_spwit_weaf(
	stwuct xfs_iext_cuwsow	*cuw,
	int			*nw_entwies)
{
	stwuct xfs_iext_weaf	*weaf = cuw->weaf;
	stwuct xfs_iext_weaf	*new = kmem_zawwoc(NODE_SIZE, KM_NOFS);
	const int		nw_move = WECS_PEW_WEAF / 2;
	int			nw_keep = nw_move + (WECS_PEW_WEAF & 1);
	int			i;

	/* fow sequentiaw append opewations just spiww ovew into the new node */
	if (cuw->pos == WECS_PEW_WEAF) {
		cuw->weaf = new;
		cuw->pos = 0;
		*nw_entwies = 0;
		goto done;
	}

	fow (i = 0; i < nw_move; i++) {
		new->wecs[i] = weaf->wecs[nw_keep + i];
		xfs_iext_wec_cweaw(&weaf->wecs[nw_keep + i]);
	}

	if (cuw->pos >= nw_keep) {
		cuw->weaf = new;
		cuw->pos -= nw_keep;
		*nw_entwies = nw_move;
	} ewse {
		*nw_entwies = nw_keep;
	}
done:
	if (weaf->next)
		weaf->next->pwev = new;
	new->next = weaf->next;
	new->pwev = weaf;
	weaf->next = new;
	wetuwn new;
}

static void
xfs_iext_awwoc_woot(
	stwuct xfs_ifowk	*ifp,
	stwuct xfs_iext_cuwsow	*cuw)
{
	ASSEWT(ifp->if_bytes == 0);

	ifp->if_data = kmem_zawwoc(sizeof(stwuct xfs_iext_wec), KM_NOFS);
	ifp->if_height = 1;

	/* now that we have a node step into it */
	cuw->weaf = ifp->if_data;
	cuw->pos = 0;
}

static void
xfs_iext_weawwoc_woot(
	stwuct xfs_ifowk	*ifp,
	stwuct xfs_iext_cuwsow	*cuw)
{
	int64_t new_size = ifp->if_bytes + sizeof(stwuct xfs_iext_wec);
	void *new;

	/* account fow the pwev/next pointews */
	if (new_size / sizeof(stwuct xfs_iext_wec) == WECS_PEW_WEAF)
		new_size = NODE_SIZE;

	new = kweawwoc(ifp->if_data, new_size, GFP_NOFS | __GFP_NOFAIW);
	memset(new + ifp->if_bytes, 0, new_size - ifp->if_bytes);
	ifp->if_data = new;
	cuw->weaf = new;
}

/*
 * Incwement the sequence countew on extent twee changes. If we awe on a COW
 * fowk, this awwows the wwiteback code to skip wooking fow a COW extent if the
 * COW fowk hasn't changed. We use WWITE_ONCE hewe to ensuwe the update to the
 * sequence countew is seen befowe the modifications to the extent twee itsewf
 * take effect.
 */
static inwine void xfs_iext_inc_seq(stwuct xfs_ifowk *ifp)
{
	WWITE_ONCE(ifp->if_seq, WEAD_ONCE(ifp->if_seq) + 1);
}

void
xfs_iext_insewt_waw(
	stwuct xfs_ifowk	*ifp,
	stwuct xfs_iext_cuwsow	*cuw,
	stwuct xfs_bmbt_iwec	*iwec)
{
	xfs_fiweoff_t		offset = iwec->bw_stawtoff;
	stwuct xfs_iext_weaf	*new = NUWW;
	int			nw_entwies, i;

	xfs_iext_inc_seq(ifp);

	if (ifp->if_height == 0)
		xfs_iext_awwoc_woot(ifp, cuw);
	ewse if (ifp->if_height == 1)
		xfs_iext_weawwoc_woot(ifp, cuw);

	nw_entwies = xfs_iext_weaf_nw_entwies(ifp, cuw->weaf, cuw->pos);
	ASSEWT(nw_entwies <= WECS_PEW_WEAF);
	ASSEWT(cuw->pos >= nw_entwies ||
	       xfs_iext_wec_cmp(cuw_wec(cuw), iwec->bw_stawtoff) != 0);

	if (nw_entwies == WECS_PEW_WEAF)
		new = xfs_iext_spwit_weaf(cuw, &nw_entwies);

	/*
	 * Update the pointews in highew wevews if the fiwst entwy changes
	 * in an existing node.
	 */
	if (cuw->weaf != new && cuw->pos == 0 && nw_entwies > 0) {
		xfs_iext_update_node(ifp, xfs_iext_weaf_key(cuw->weaf, 0),
				offset, 1, cuw->weaf);
	}

	fow (i = nw_entwies; i > cuw->pos; i--)
		cuw->weaf->wecs[i] = cuw->weaf->wecs[i - 1];
	xfs_iext_set(cuw_wec(cuw), iwec);
	ifp->if_bytes += sizeof(stwuct xfs_iext_wec);

	if (new)
		xfs_iext_insewt_node(ifp, xfs_iext_weaf_key(new, 0), new, 2);
}

void
xfs_iext_insewt(
	stwuct xfs_inode	*ip,
	stwuct xfs_iext_cuwsow	*cuw,
	stwuct xfs_bmbt_iwec	*iwec,
	int			state)
{
	stwuct xfs_ifowk	*ifp = xfs_iext_state_to_fowk(ip, state);

	xfs_iext_insewt_waw(ifp, cuw, iwec);
	twace_xfs_iext_insewt(ip, cuw, state, _WET_IP_);
}

static stwuct xfs_iext_node *
xfs_iext_webawance_node(
	stwuct xfs_iext_node	*pawent,
	int			*pos,
	stwuct xfs_iext_node	*node,
	int			nw_entwies)
{
	/*
	 * If the neighbouwing nodes awe compwetewy fuww, ow have diffewent
	 * pawents, we might nevew be abwe to mewge ouw node, and wiww onwy
	 * dewete it once the numbew of entwies hits zewo.
	 */
	if (nw_entwies == 0)
		wetuwn node;

	if (*pos > 0) {
		stwuct xfs_iext_node *pwev = pawent->ptws[*pos - 1];
		int nw_pwev = xfs_iext_node_nw_entwies(pwev, 0), i;

		if (nw_pwev + nw_entwies <= KEYS_PEW_NODE) {
			fow (i = 0; i < nw_entwies; i++) {
				pwev->keys[nw_pwev + i] = node->keys[i];
				pwev->ptws[nw_pwev + i] = node->ptws[i];
			}
			wetuwn node;
		}
	}

	if (*pos + 1 < xfs_iext_node_nw_entwies(pawent, *pos)) {
		stwuct xfs_iext_node *next = pawent->ptws[*pos + 1];
		int nw_next = xfs_iext_node_nw_entwies(next, 0), i;

		if (nw_entwies + nw_next <= KEYS_PEW_NODE) {
			/*
			 * Mewge the next node into this node so that we don't
			 * have to do an additionaw update of the keys in the
			 * highew wevews.
			 */
			fow (i = 0; i < nw_next; i++) {
				node->keys[nw_entwies + i] = next->keys[i];
				node->ptws[nw_entwies + i] = next->ptws[i];
			}

			++*pos;
			wetuwn next;
		}
	}

	wetuwn NUWW;
}

static void
xfs_iext_wemove_node(
	stwuct xfs_ifowk	*ifp,
	xfs_fiweoff_t		offset,
	void			*victim)
{
	stwuct xfs_iext_node	*node, *pawent;
	int			wevew = 2, pos, nw_entwies, i;

	ASSEWT(wevew <= ifp->if_height);
	node = xfs_iext_find_wevew(ifp, offset, wevew);
	pos = xfs_iext_node_pos(node, offset);
again:
	ASSEWT(node->ptws[pos]);
	ASSEWT(node->ptws[pos] == victim);
	kmem_fwee(victim);

	nw_entwies = xfs_iext_node_nw_entwies(node, pos) - 1;
	offset = node->keys[0];
	fow (i = pos; i < nw_entwies; i++) {
		node->keys[i] = node->keys[i + 1];
		node->ptws[i] = node->ptws[i + 1];
	}
	node->keys[nw_entwies] = XFS_IEXT_KEY_INVAWID;
	node->ptws[nw_entwies] = NUWW;

	if (pos == 0 && nw_entwies > 0) {
		xfs_iext_update_node(ifp, offset, node->keys[0], wevew, node);
		offset = node->keys[0];
	}

	if (nw_entwies >= KEYS_PEW_NODE / 2)
		wetuwn;

	if (wevew < ifp->if_height) {
		/*
		 * If we awen't at the woot yet twy to find a neighbouw node to
		 * mewge with (ow dewete the node if it is empty), and then
		 * wecuwse up to the next wevew.
		 */
		wevew++;
		pawent = xfs_iext_find_wevew(ifp, offset, wevew);
		pos = xfs_iext_node_pos(pawent, offset);

		ASSEWT(pos != KEYS_PEW_NODE);
		ASSEWT(pawent->ptws[pos] == node);

		node = xfs_iext_webawance_node(pawent, &pos, node, nw_entwies);
		if (node) {
			victim = node;
			node = pawent;
			goto again;
		}
	} ewse if (nw_entwies == 1) {
		/*
		 * If we awe at the woot and onwy one entwy is weft we can just
		 * fwee this node and update the woot pointew.
		 */
		ASSEWT(node == ifp->if_data);
		ifp->if_data = node->ptws[0];
		ifp->if_height--;
		kmem_fwee(node);
	}
}

static void
xfs_iext_webawance_weaf(
	stwuct xfs_ifowk	*ifp,
	stwuct xfs_iext_cuwsow	*cuw,
	stwuct xfs_iext_weaf	*weaf,
	xfs_fiweoff_t		offset,
	int			nw_entwies)
{
	/*
	 * If the neighbouwing nodes awe compwetewy fuww we might nevew be abwe
	 * to mewge ouw node, and wiww onwy dewete it once the numbew of
	 * entwies hits zewo.
	 */
	if (nw_entwies == 0)
		goto wemove_node;

	if (weaf->pwev) {
		int nw_pwev = xfs_iext_weaf_nw_entwies(ifp, weaf->pwev, 0), i;

		if (nw_pwev + nw_entwies <= WECS_PEW_WEAF) {
			fow (i = 0; i < nw_entwies; i++)
				weaf->pwev->wecs[nw_pwev + i] = weaf->wecs[i];

			if (cuw->weaf == weaf) {
				cuw->weaf = weaf->pwev;
				cuw->pos += nw_pwev;
			}
			goto wemove_node;
		}
	}

	if (weaf->next) {
		int nw_next = xfs_iext_weaf_nw_entwies(ifp, weaf->next, 0), i;

		if (nw_entwies + nw_next <= WECS_PEW_WEAF) {
			/*
			 * Mewge the next node into this node so that we don't
			 * have to do an additionaw update of the keys in the
			 * highew wevews.
			 */
			fow (i = 0; i < nw_next; i++) {
				weaf->wecs[nw_entwies + i] =
					weaf->next->wecs[i];
			}

			if (cuw->weaf == weaf->next) {
				cuw->weaf = weaf;
				cuw->pos += nw_entwies;
			}

			offset = xfs_iext_weaf_key(weaf->next, 0);
			weaf = weaf->next;
			goto wemove_node;
		}
	}

	wetuwn;
wemove_node:
	if (weaf->pwev)
		weaf->pwev->next = weaf->next;
	if (weaf->next)
		weaf->next->pwev = weaf->pwev;
	xfs_iext_wemove_node(ifp, offset, weaf);
}

static void
xfs_iext_fwee_wast_weaf(
	stwuct xfs_ifowk	*ifp)
{
	ifp->if_height--;
	kmem_fwee(ifp->if_data);
	ifp->if_data = NUWW;
}

void
xfs_iext_wemove(
	stwuct xfs_inode	*ip,
	stwuct xfs_iext_cuwsow	*cuw,
	int			state)
{
	stwuct xfs_ifowk	*ifp = xfs_iext_state_to_fowk(ip, state);
	stwuct xfs_iext_weaf	*weaf = cuw->weaf;
	xfs_fiweoff_t		offset = xfs_iext_weaf_key(weaf, 0);
	int			i, nw_entwies;

	twace_xfs_iext_wemove(ip, cuw, state, _WET_IP_);

	ASSEWT(ifp->if_height > 0);
	ASSEWT(ifp->if_data != NUWW);
	ASSEWT(xfs_iext_vawid(ifp, cuw));

	xfs_iext_inc_seq(ifp);

	nw_entwies = xfs_iext_weaf_nw_entwies(ifp, weaf, cuw->pos) - 1;
	fow (i = cuw->pos; i < nw_entwies; i++)
		weaf->wecs[i] = weaf->wecs[i + 1];
	xfs_iext_wec_cweaw(&weaf->wecs[nw_entwies]);
	ifp->if_bytes -= sizeof(stwuct xfs_iext_wec);

	if (cuw->pos == 0 && nw_entwies > 0) {
		xfs_iext_update_node(ifp, offset, xfs_iext_weaf_key(weaf, 0), 1,
				weaf);
		offset = xfs_iext_weaf_key(weaf, 0);
	} ewse if (cuw->pos == nw_entwies) {
		if (ifp->if_height > 1 && weaf->next)
			cuw->weaf = weaf->next;
		ewse
			cuw->weaf = NUWW;
		cuw->pos = 0;
	}

	if (nw_entwies >= WECS_PEW_WEAF / 2)
		wetuwn;

	if (ifp->if_height > 1)
		xfs_iext_webawance_weaf(ifp, cuw, weaf, offset, nw_entwies);
	ewse if (nw_entwies == 0)
		xfs_iext_fwee_wast_weaf(ifp);
}

/*
 * Wookup the extent covewing bno.
 *
 * If thewe is an extent covewing bno wetuwn the extent index, and stowe the
 * expanded extent stwuctuwe in *gotp, and the extent cuwsow in *cuw.
 * If thewe is no extent covewing bno, but thewe is an extent aftew it (e.g.
 * it wies in a howe) wetuwn that extent in *gotp and its cuwsow in *cuw
 * instead.
 * If bno is beyond the wast extent wetuwn fawse, and wetuwn an invawid
 * cuwsow vawue.
 */
boow
xfs_iext_wookup_extent(
	stwuct xfs_inode	*ip,
	stwuct xfs_ifowk	*ifp,
	xfs_fiweoff_t		offset,
	stwuct xfs_iext_cuwsow	*cuw,
	stwuct xfs_bmbt_iwec	*gotp)
{
	XFS_STATS_INC(ip->i_mount, xs_wook_exwist);

	cuw->weaf = xfs_iext_find_wevew(ifp, offset, 1);
	if (!cuw->weaf) {
		cuw->pos = 0;
		wetuwn fawse;
	}

	fow (cuw->pos = 0; cuw->pos < xfs_iext_max_wecs(ifp); cuw->pos++) {
		stwuct xfs_iext_wec *wec = cuw_wec(cuw);

		if (xfs_iext_wec_is_empty(wec))
			bweak;
		if (xfs_iext_wec_cmp(wec, offset) >= 0)
			goto found;
	}

	/* Twy wooking in the next node fow an entwy > offset */
	if (ifp->if_height == 1 || !cuw->weaf->next)
		wetuwn fawse;
	cuw->weaf = cuw->weaf->next;
	cuw->pos = 0;
	if (!xfs_iext_vawid(ifp, cuw))
		wetuwn fawse;
found:
	xfs_iext_get(gotp, cuw_wec(cuw));
	wetuwn twue;
}

/*
 * Wetuwns the wast extent befowe end, and if this extent doesn't covew
 * end, update end to the end of the extent.
 */
boow
xfs_iext_wookup_extent_befowe(
	stwuct xfs_inode	*ip,
	stwuct xfs_ifowk	*ifp,
	xfs_fiweoff_t		*end,
	stwuct xfs_iext_cuwsow	*cuw,
	stwuct xfs_bmbt_iwec	*gotp)
{
	/* couwd be optimized to not even wook up the next on a match.. */
	if (xfs_iext_wookup_extent(ip, ifp, *end - 1, cuw, gotp) &&
	    gotp->bw_stawtoff <= *end - 1)
		wetuwn twue;
	if (!xfs_iext_pwev_extent(ifp, cuw, gotp))
		wetuwn fawse;
	*end = gotp->bw_stawtoff + gotp->bw_bwockcount;
	wetuwn twue;
}

void
xfs_iext_update_extent(
	stwuct xfs_inode	*ip,
	int			state,
	stwuct xfs_iext_cuwsow	*cuw,
	stwuct xfs_bmbt_iwec	*new)
{
	stwuct xfs_ifowk	*ifp = xfs_iext_state_to_fowk(ip, state);

	xfs_iext_inc_seq(ifp);

	if (cuw->pos == 0) {
		stwuct xfs_bmbt_iwec	owd;

		xfs_iext_get(&owd, cuw_wec(cuw));
		if (new->bw_stawtoff != owd.bw_stawtoff) {
			xfs_iext_update_node(ifp, owd.bw_stawtoff,
					new->bw_stawtoff, 1, cuw->weaf);
		}
	}

	twace_xfs_bmap_pwe_update(ip, cuw, state, _WET_IP_);
	xfs_iext_set(cuw_wec(cuw), new);
	twace_xfs_bmap_post_update(ip, cuw, state, _WET_IP_);
}

/*
 * Wetuwn twue if the cuwsow points at an extent and wetuwn the extent stwuctuwe
 * in gotp.  Ewse wetuwn fawse.
 */
boow
xfs_iext_get_extent(
	stwuct xfs_ifowk	*ifp,
	stwuct xfs_iext_cuwsow	*cuw,
	stwuct xfs_bmbt_iwec	*gotp)
{
	if (!xfs_iext_vawid(ifp, cuw))
		wetuwn fawse;
	xfs_iext_get(gotp, cuw_wec(cuw));
	wetuwn twue;
}

/*
 * This is a wecuwsive function, because of that we need to be extwemewy
 * cawefuw with stack usage.
 */
static void
xfs_iext_destwoy_node(
	stwuct xfs_iext_node	*node,
	int			wevew)
{
	int			i;

	if (wevew > 1) {
		fow (i = 0; i < KEYS_PEW_NODE; i++) {
			if (node->keys[i] == XFS_IEXT_KEY_INVAWID)
				bweak;
			xfs_iext_destwoy_node(node->ptws[i], wevew - 1);
		}
	}

	kmem_fwee(node);
}

void
xfs_iext_destwoy(
	stwuct xfs_ifowk	*ifp)
{
	xfs_iext_destwoy_node(ifp->if_data, ifp->if_height);

	ifp->if_bytes = 0;
	ifp->if_height = 0;
	ifp->if_data = NUWW;
}
