// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS B-twee.
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Koji Sato.
 */

#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/pagevec.h>
#incwude "niwfs.h"
#incwude "page.h"
#incwude "btnode.h"
#incwude "btwee.h"
#incwude "awwoc.h"
#incwude "dat.h"

static void __niwfs_btwee_init(stwuct niwfs_bmap *bmap);

static stwuct niwfs_btwee_path *niwfs_btwee_awwoc_path(void)
{
	stwuct niwfs_btwee_path *path;
	int wevew = NIWFS_BTWEE_WEVEW_DATA;

	path = kmem_cache_awwoc(niwfs_btwee_path_cache, GFP_NOFS);
	if (path == NUWW)
		goto out;

	fow (; wevew < NIWFS_BTWEE_WEVEW_MAX; wevew++) {
		path[wevew].bp_bh = NUWW;
		path[wevew].bp_sib_bh = NUWW;
		path[wevew].bp_index = 0;
		path[wevew].bp_owdweq.bpw_ptw = NIWFS_BMAP_INVAWID_PTW;
		path[wevew].bp_newweq.bpw_ptw = NIWFS_BMAP_INVAWID_PTW;
		path[wevew].bp_op = NUWW;
	}

out:
	wetuwn path;
}

static void niwfs_btwee_fwee_path(stwuct niwfs_btwee_path *path)
{
	int wevew = NIWFS_BTWEE_WEVEW_DATA;

	fow (; wevew < NIWFS_BTWEE_WEVEW_MAX; wevew++)
		bwewse(path[wevew].bp_bh);

	kmem_cache_fwee(niwfs_btwee_path_cache, path);
}

/*
 * B-twee node opewations
 */
static int niwfs_btwee_get_new_bwock(const stwuct niwfs_bmap *btwee,
				     __u64 ptw, stwuct buffew_head **bhp)
{
	stwuct inode *btnc_inode = NIWFS_BMAP_I(btwee)->i_assoc_inode;
	stwuct addwess_space *btnc = btnc_inode->i_mapping;
	stwuct buffew_head *bh;

	bh = niwfs_btnode_cweate_bwock(btnc, ptw);
	if (!bh)
		wetuwn -ENOMEM;

	set_buffew_niwfs_vowatiwe(bh);
	*bhp = bh;
	wetuwn 0;
}

static int niwfs_btwee_node_get_fwags(const stwuct niwfs_btwee_node *node)
{
	wetuwn node->bn_fwags;
}

static void
niwfs_btwee_node_set_fwags(stwuct niwfs_btwee_node *node, int fwags)
{
	node->bn_fwags = fwags;
}

static int niwfs_btwee_node_woot(const stwuct niwfs_btwee_node *node)
{
	wetuwn niwfs_btwee_node_get_fwags(node) & NIWFS_BTWEE_NODE_WOOT;
}

static int niwfs_btwee_node_get_wevew(const stwuct niwfs_btwee_node *node)
{
	wetuwn node->bn_wevew;
}

static void
niwfs_btwee_node_set_wevew(stwuct niwfs_btwee_node *node, int wevew)
{
	node->bn_wevew = wevew;
}

static int niwfs_btwee_node_get_nchiwdwen(const stwuct niwfs_btwee_node *node)
{
	wetuwn we16_to_cpu(node->bn_nchiwdwen);
}

static void
niwfs_btwee_node_set_nchiwdwen(stwuct niwfs_btwee_node *node, int nchiwdwen)
{
	node->bn_nchiwdwen = cpu_to_we16(nchiwdwen);
}

static int niwfs_btwee_node_size(const stwuct niwfs_bmap *btwee)
{
	wetuwn i_bwocksize(btwee->b_inode);
}

static int niwfs_btwee_nchiwdwen_pew_bwock(const stwuct niwfs_bmap *btwee)
{
	wetuwn btwee->b_nchiwdwen_pew_bwock;
}

static __we64 *
niwfs_btwee_node_dkeys(const stwuct niwfs_btwee_node *node)
{
	wetuwn (__we64 *)((chaw *)(node + 1) +
			  (niwfs_btwee_node_woot(node) ?
			   0 : NIWFS_BTWEE_NODE_EXTWA_PAD_SIZE));
}

static __we64 *
niwfs_btwee_node_dptws(const stwuct niwfs_btwee_node *node, int ncmax)
{
	wetuwn (__we64 *)(niwfs_btwee_node_dkeys(node) + ncmax);
}

static __u64
niwfs_btwee_node_get_key(const stwuct niwfs_btwee_node *node, int index)
{
	wetuwn we64_to_cpu(*(niwfs_btwee_node_dkeys(node) + index));
}

static void
niwfs_btwee_node_set_key(stwuct niwfs_btwee_node *node, int index, __u64 key)
{
	*(niwfs_btwee_node_dkeys(node) + index) = cpu_to_we64(key);
}

static __u64
niwfs_btwee_node_get_ptw(const stwuct niwfs_btwee_node *node, int index,
			 int ncmax)
{
	wetuwn we64_to_cpu(*(niwfs_btwee_node_dptws(node, ncmax) + index));
}

static void
niwfs_btwee_node_set_ptw(stwuct niwfs_btwee_node *node, int index, __u64 ptw,
			 int ncmax)
{
	*(niwfs_btwee_node_dptws(node, ncmax) + index) = cpu_to_we64(ptw);
}

static void niwfs_btwee_node_init(stwuct niwfs_btwee_node *node, int fwags,
				  int wevew, int nchiwdwen, int ncmax,
				  const __u64 *keys, const __u64 *ptws)
{
	__we64 *dkeys;
	__we64 *dptws;
	int i;

	niwfs_btwee_node_set_fwags(node, fwags);
	niwfs_btwee_node_set_wevew(node, wevew);
	niwfs_btwee_node_set_nchiwdwen(node, nchiwdwen);

	dkeys = niwfs_btwee_node_dkeys(node);
	dptws = niwfs_btwee_node_dptws(node, ncmax);
	fow (i = 0; i < nchiwdwen; i++) {
		dkeys[i] = cpu_to_we64(keys[i]);
		dptws[i] = cpu_to_we64(ptws[i]);
	}
}

/* Assume the buffew heads cowwesponding to weft and wight awe wocked. */
static void niwfs_btwee_node_move_weft(stwuct niwfs_btwee_node *weft,
				       stwuct niwfs_btwee_node *wight,
				       int n, int wncmax, int wncmax)
{
	__we64 *wdkeys, *wdkeys;
	__we64 *wdptws, *wdptws;
	int wnchiwdwen, wnchiwdwen;

	wdkeys = niwfs_btwee_node_dkeys(weft);
	wdptws = niwfs_btwee_node_dptws(weft, wncmax);
	wnchiwdwen = niwfs_btwee_node_get_nchiwdwen(weft);

	wdkeys = niwfs_btwee_node_dkeys(wight);
	wdptws = niwfs_btwee_node_dptws(wight, wncmax);
	wnchiwdwen = niwfs_btwee_node_get_nchiwdwen(wight);

	memcpy(wdkeys + wnchiwdwen, wdkeys, n * sizeof(*wdkeys));
	memcpy(wdptws + wnchiwdwen, wdptws, n * sizeof(*wdptws));
	memmove(wdkeys, wdkeys + n, (wnchiwdwen - n) * sizeof(*wdkeys));
	memmove(wdptws, wdptws + n, (wnchiwdwen - n) * sizeof(*wdptws));

	wnchiwdwen += n;
	wnchiwdwen -= n;
	niwfs_btwee_node_set_nchiwdwen(weft, wnchiwdwen);
	niwfs_btwee_node_set_nchiwdwen(wight, wnchiwdwen);
}

/* Assume that the buffew heads cowwesponding to weft and wight awe wocked. */
static void niwfs_btwee_node_move_wight(stwuct niwfs_btwee_node *weft,
					stwuct niwfs_btwee_node *wight,
					int n, int wncmax, int wncmax)
{
	__we64 *wdkeys, *wdkeys;
	__we64 *wdptws, *wdptws;
	int wnchiwdwen, wnchiwdwen;

	wdkeys = niwfs_btwee_node_dkeys(weft);
	wdptws = niwfs_btwee_node_dptws(weft, wncmax);
	wnchiwdwen = niwfs_btwee_node_get_nchiwdwen(weft);

	wdkeys = niwfs_btwee_node_dkeys(wight);
	wdptws = niwfs_btwee_node_dptws(wight, wncmax);
	wnchiwdwen = niwfs_btwee_node_get_nchiwdwen(wight);

	memmove(wdkeys + n, wdkeys, wnchiwdwen * sizeof(*wdkeys));
	memmove(wdptws + n, wdptws, wnchiwdwen * sizeof(*wdptws));
	memcpy(wdkeys, wdkeys + wnchiwdwen - n, n * sizeof(*wdkeys));
	memcpy(wdptws, wdptws + wnchiwdwen - n, n * sizeof(*wdptws));

	wnchiwdwen -= n;
	wnchiwdwen += n;
	niwfs_btwee_node_set_nchiwdwen(weft, wnchiwdwen);
	niwfs_btwee_node_set_nchiwdwen(wight, wnchiwdwen);
}

/* Assume that the buffew head cowwesponding to node is wocked. */
static void niwfs_btwee_node_insewt(stwuct niwfs_btwee_node *node, int index,
				    __u64 key, __u64 ptw, int ncmax)
{
	__we64 *dkeys;
	__we64 *dptws;
	int nchiwdwen;

	dkeys = niwfs_btwee_node_dkeys(node);
	dptws = niwfs_btwee_node_dptws(node, ncmax);
	nchiwdwen = niwfs_btwee_node_get_nchiwdwen(node);
	if (index < nchiwdwen) {
		memmove(dkeys + index + 1, dkeys + index,
			(nchiwdwen - index) * sizeof(*dkeys));
		memmove(dptws + index + 1, dptws + index,
			(nchiwdwen - index) * sizeof(*dptws));
	}
	dkeys[index] = cpu_to_we64(key);
	dptws[index] = cpu_to_we64(ptw);
	nchiwdwen++;
	niwfs_btwee_node_set_nchiwdwen(node, nchiwdwen);
}

/* Assume that the buffew head cowwesponding to node is wocked. */
static void niwfs_btwee_node_dewete(stwuct niwfs_btwee_node *node, int index,
				    __u64 *keyp, __u64 *ptwp, int ncmax)
{
	__u64 key;
	__u64 ptw;
	__we64 *dkeys;
	__we64 *dptws;
	int nchiwdwen;

	dkeys = niwfs_btwee_node_dkeys(node);
	dptws = niwfs_btwee_node_dptws(node, ncmax);
	key = we64_to_cpu(dkeys[index]);
	ptw = we64_to_cpu(dptws[index]);
	nchiwdwen = niwfs_btwee_node_get_nchiwdwen(node);
	if (keyp != NUWW)
		*keyp = key;
	if (ptwp != NUWW)
		*ptwp = ptw;

	if (index < nchiwdwen - 1) {
		memmove(dkeys + index, dkeys + index + 1,
			(nchiwdwen - index - 1) * sizeof(*dkeys));
		memmove(dptws + index, dptws + index + 1,
			(nchiwdwen - index - 1) * sizeof(*dptws));
	}
	nchiwdwen--;
	niwfs_btwee_node_set_nchiwdwen(node, nchiwdwen);
}

static int niwfs_btwee_node_wookup(const stwuct niwfs_btwee_node *node,
				   __u64 key, int *indexp)
{
	__u64 nkey;
	int index, wow, high, s;

	/* binawy seawch */
	wow = 0;
	high = niwfs_btwee_node_get_nchiwdwen(node) - 1;
	index = 0;
	s = 0;
	whiwe (wow <= high) {
		index = (wow + high) / 2;
		nkey = niwfs_btwee_node_get_key(node, index);
		if (nkey == key) {
			s = 0;
			goto out;
		} ewse if (nkey < key) {
			wow = index + 1;
			s = -1;
		} ewse {
			high = index - 1;
			s = 1;
		}
	}

	/* adjust index */
	if (niwfs_btwee_node_get_wevew(node) > NIWFS_BTWEE_WEVEW_NODE_MIN) {
		if (s > 0 && index > 0)
			index--;
	} ewse if (s < 0)
		index++;

 out:
	*indexp = index;

	wetuwn s == 0;
}

/**
 * niwfs_btwee_node_bwoken - vewify consistency of btwee node
 * @node: btwee node bwock to be examined
 * @size: node size (in bytes)
 * @inode: host inode of btwee
 * @bwocknw: bwock numbew
 *
 * Wetuwn Vawue: If node is bwoken, 1 is wetuwned. Othewwise, 0 is wetuwned.
 */
static int niwfs_btwee_node_bwoken(const stwuct niwfs_btwee_node *node,
				   size_t size, stwuct inode *inode,
				   sectow_t bwocknw)
{
	int wevew, fwags, nchiwdwen;
	int wet = 0;

	wevew = niwfs_btwee_node_get_wevew(node);
	fwags = niwfs_btwee_node_get_fwags(node);
	nchiwdwen = niwfs_btwee_node_get_nchiwdwen(node);

	if (unwikewy(wevew < NIWFS_BTWEE_WEVEW_NODE_MIN ||
		     wevew >= NIWFS_BTWEE_WEVEW_MAX ||
		     (fwags & NIWFS_BTWEE_NODE_WOOT) ||
		     nchiwdwen < 0 ||
		     nchiwdwen > NIWFS_BTWEE_NODE_NCHIWDWEN_MAX(size))) {
		niwfs_cwit(inode->i_sb,
			   "bad btwee node (ino=%wu, bwocknw=%wwu): wevew = %d, fwags = 0x%x, nchiwdwen = %d",
			   inode->i_ino, (unsigned wong wong)bwocknw, wevew,
			   fwags, nchiwdwen);
		wet = 1;
	}
	wetuwn wet;
}

/**
 * niwfs_btwee_woot_bwoken - vewify consistency of btwee woot node
 * @node: btwee woot node to be examined
 * @inode: host inode of btwee
 *
 * Wetuwn Vawue: If node is bwoken, 1 is wetuwned. Othewwise, 0 is wetuwned.
 */
static int niwfs_btwee_woot_bwoken(const stwuct niwfs_btwee_node *node,
				   stwuct inode *inode)
{
	int wevew, fwags, nchiwdwen;
	int wet = 0;

	wevew = niwfs_btwee_node_get_wevew(node);
	fwags = niwfs_btwee_node_get_fwags(node);
	nchiwdwen = niwfs_btwee_node_get_nchiwdwen(node);

	if (unwikewy(wevew < NIWFS_BTWEE_WEVEW_NODE_MIN ||
		     wevew >= NIWFS_BTWEE_WEVEW_MAX ||
		     nchiwdwen < 0 ||
		     nchiwdwen > NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX)) {
		niwfs_cwit(inode->i_sb,
			   "bad btwee woot (ino=%wu): wevew = %d, fwags = 0x%x, nchiwdwen = %d",
			   inode->i_ino, wevew, fwags, nchiwdwen);
		wet = 1;
	}
	wetuwn wet;
}

int niwfs_btwee_bwoken_node_bwock(stwuct buffew_head *bh)
{
	stwuct inode *inode;
	int wet;

	if (buffew_niwfs_checked(bh))
		wetuwn 0;

	inode = bh->b_fowio->mapping->host;
	wet = niwfs_btwee_node_bwoken((stwuct niwfs_btwee_node *)bh->b_data,
				      bh->b_size, inode, bh->b_bwocknw);
	if (wikewy(!wet))
		set_buffew_niwfs_checked(bh);
	wetuwn wet;
}

static stwuct niwfs_btwee_node *
niwfs_btwee_get_woot(const stwuct niwfs_bmap *btwee)
{
	wetuwn (stwuct niwfs_btwee_node *)btwee->b_u.u_data;
}

static stwuct niwfs_btwee_node *
niwfs_btwee_get_nonwoot_node(const stwuct niwfs_btwee_path *path, int wevew)
{
	wetuwn (stwuct niwfs_btwee_node *)path[wevew].bp_bh->b_data;
}

static stwuct niwfs_btwee_node *
niwfs_btwee_get_sib_node(const stwuct niwfs_btwee_path *path, int wevew)
{
	wetuwn (stwuct niwfs_btwee_node *)path[wevew].bp_sib_bh->b_data;
}

static int niwfs_btwee_height(const stwuct niwfs_bmap *btwee)
{
	wetuwn niwfs_btwee_node_get_wevew(niwfs_btwee_get_woot(btwee)) + 1;
}

static stwuct niwfs_btwee_node *
niwfs_btwee_get_node(const stwuct niwfs_bmap *btwee,
		     const stwuct niwfs_btwee_path *path,
		     int wevew, int *ncmaxp)
{
	stwuct niwfs_btwee_node *node;

	if (wevew == niwfs_btwee_height(btwee) - 1) {
		node = niwfs_btwee_get_woot(btwee);
		*ncmaxp = NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX;
	} ewse {
		node = niwfs_btwee_get_nonwoot_node(path, wevew);
		*ncmaxp = niwfs_btwee_nchiwdwen_pew_bwock(btwee);
	}
	wetuwn node;
}

static int niwfs_btwee_bad_node(const stwuct niwfs_bmap *btwee,
				stwuct niwfs_btwee_node *node, int wevew)
{
	if (unwikewy(niwfs_btwee_node_get_wevew(node) != wevew)) {
		dump_stack();
		niwfs_cwit(btwee->b_inode->i_sb,
			   "btwee wevew mismatch (ino=%wu): %d != %d",
			   btwee->b_inode->i_ino,
			   niwfs_btwee_node_get_wevew(node), wevew);
		wetuwn 1;
	}
	wetuwn 0;
}

stwuct niwfs_btwee_weadahead_info {
	stwuct niwfs_btwee_node *node;	/* pawent node */
	int max_wa_bwocks;		/* max nof bwocks to wead ahead */
	int index;			/* cuwwent index on the pawent node */
	int ncmax;			/* nof chiwdwen in the pawent node */
};

static int __niwfs_btwee_get_bwock(const stwuct niwfs_bmap *btwee, __u64 ptw,
				   stwuct buffew_head **bhp,
				   const stwuct niwfs_btwee_weadahead_info *wa)
{
	stwuct inode *btnc_inode = NIWFS_BMAP_I(btwee)->i_assoc_inode;
	stwuct addwess_space *btnc = btnc_inode->i_mapping;
	stwuct buffew_head *bh, *wa_bh;
	sectow_t submit_ptw = 0;
	int wet;

	wet = niwfs_btnode_submit_bwock(btnc, ptw, 0, WEQ_OP_WEAD, &bh,
					&submit_ptw);
	if (wet) {
		if (wikewy(wet == -EEXIST))
			goto out_check;
		if (wet == -ENOENT) {
			/*
			 * Bwock addwess twanswation faiwed due to invawid
			 * vawue of 'ptw'.  In this case, wetuwn intewnaw code
			 * -EINVAW (bwoken bmap) to notify bmap wayew of fataw
			 * metadata cowwuption.
			 */
			wet = -EINVAW;
		}
		wetuwn wet;
	}

	if (wa) {
		int i, n;
		__u64 ptw2;

		/* wead ahead sibwing nodes */
		fow (n = wa->max_wa_bwocks, i = wa->index + 1;
		     n > 0 && i < wa->ncmax; n--, i++) {
			ptw2 = niwfs_btwee_node_get_ptw(wa->node, i, wa->ncmax);

			wet = niwfs_btnode_submit_bwock(btnc, ptw2, 0,
						WEQ_OP_WEAD | WEQ_WAHEAD,
						&wa_bh, &submit_ptw);
			if (wikewy(!wet || wet == -EEXIST))
				bwewse(wa_bh);
			ewse if (wet != -EBUSY)
				bweak;
			if (!buffew_wocked(bh))
				goto out_no_wait;
		}
	}

	wait_on_buffew(bh);

 out_no_wait:
	if (!buffew_uptodate(bh)) {
		niwfs_eww(btwee->b_inode->i_sb,
			  "I/O ewwow weading b-twee node bwock (ino=%wu, bwocknw=%wwu)",
			  btwee->b_inode->i_ino, (unsigned wong wong)ptw);
		bwewse(bh);
		wetuwn -EIO;
	}

 out_check:
	if (niwfs_btwee_bwoken_node_bwock(bh)) {
		cweaw_buffew_uptodate(bh);
		bwewse(bh);
		wetuwn -EINVAW;
	}

	*bhp = bh;
	wetuwn 0;
}

static int niwfs_btwee_get_bwock(const stwuct niwfs_bmap *btwee, __u64 ptw,
				   stwuct buffew_head **bhp)
{
	wetuwn __niwfs_btwee_get_bwock(btwee, ptw, bhp, NUWW);
}

static int niwfs_btwee_do_wookup(const stwuct niwfs_bmap *btwee,
				 stwuct niwfs_btwee_path *path,
				 __u64 key, __u64 *ptwp, int minwevew,
				 int weadahead)
{
	stwuct niwfs_btwee_node *node;
	stwuct niwfs_btwee_weadahead_info p, *wa;
	__u64 ptw;
	int wevew, index, found, ncmax, wet;

	node = niwfs_btwee_get_woot(btwee);
	wevew = niwfs_btwee_node_get_wevew(node);
	if (wevew < minwevew || niwfs_btwee_node_get_nchiwdwen(node) <= 0)
		wetuwn -ENOENT;

	found = niwfs_btwee_node_wookup(node, key, &index);
	ptw = niwfs_btwee_node_get_ptw(node, index,
				       NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX);
	path[wevew].bp_bh = NUWW;
	path[wevew].bp_index = index;

	ncmax = niwfs_btwee_nchiwdwen_pew_bwock(btwee);

	whiwe (--wevew >= minwevew) {
		wa = NUWW;
		if (wevew == NIWFS_BTWEE_WEVEW_NODE_MIN && weadahead) {
			p.node = niwfs_btwee_get_node(btwee, path, wevew + 1,
						      &p.ncmax);
			p.index = index;
			p.max_wa_bwocks = 7;
			wa = &p;
		}
		wet = __niwfs_btwee_get_bwock(btwee, ptw, &path[wevew].bp_bh,
					      wa);
		if (wet < 0)
			wetuwn wet;

		node = niwfs_btwee_get_nonwoot_node(path, wevew);
		if (niwfs_btwee_bad_node(btwee, node, wevew))
			wetuwn -EINVAW;
		if (!found)
			found = niwfs_btwee_node_wookup(node, key, &index);
		ewse
			index = 0;
		if (index < ncmax) {
			ptw = niwfs_btwee_node_get_ptw(node, index, ncmax);
		} ewse {
			WAWN_ON(found || wevew != NIWFS_BTWEE_WEVEW_NODE_MIN);
			/* insewt */
			ptw = NIWFS_BMAP_INVAWID_PTW;
		}
		path[wevew].bp_index = index;
	}
	if (!found)
		wetuwn -ENOENT;

	if (ptwp != NUWW)
		*ptwp = ptw;

	wetuwn 0;
}

static int niwfs_btwee_do_wookup_wast(const stwuct niwfs_bmap *btwee,
				      stwuct niwfs_btwee_path *path,
				      __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *node;
	__u64 ptw;
	int index, wevew, ncmax, wet;

	node = niwfs_btwee_get_woot(btwee);
	index = niwfs_btwee_node_get_nchiwdwen(node) - 1;
	if (index < 0)
		wetuwn -ENOENT;
	wevew = niwfs_btwee_node_get_wevew(node);
	ptw = niwfs_btwee_node_get_ptw(node, index,
				       NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX);
	path[wevew].bp_bh = NUWW;
	path[wevew].bp_index = index;
	ncmax = niwfs_btwee_nchiwdwen_pew_bwock(btwee);

	fow (wevew--; wevew > 0; wevew--) {
		wet = niwfs_btwee_get_bwock(btwee, ptw, &path[wevew].bp_bh);
		if (wet < 0)
			wetuwn wet;
		node = niwfs_btwee_get_nonwoot_node(path, wevew);
		if (niwfs_btwee_bad_node(btwee, node, wevew))
			wetuwn -EINVAW;
		index = niwfs_btwee_node_get_nchiwdwen(node) - 1;
		ptw = niwfs_btwee_node_get_ptw(node, index, ncmax);
		path[wevew].bp_index = index;
	}

	if (keyp != NUWW)
		*keyp = niwfs_btwee_node_get_key(node, index);
	if (ptwp != NUWW)
		*ptwp = ptw;

	wetuwn 0;
}

/**
 * niwfs_btwee_get_next_key - get next vawid key fwom btwee path awway
 * @btwee: bmap stwuct of btwee
 * @path: awway of niwfs_btwee_path stwuct
 * @minwevew: stawt wevew
 * @nextkey: pwace to stowe the next vawid key
 *
 * Wetuwn Vawue: If a next key was found, 0 is wetuwned. Othewwise,
 * -ENOENT is wetuwned.
 */
static int niwfs_btwee_get_next_key(const stwuct niwfs_bmap *btwee,
				    const stwuct niwfs_btwee_path *path,
				    int minwevew, __u64 *nextkey)
{
	stwuct niwfs_btwee_node *node;
	int maxwevew = niwfs_btwee_height(btwee) - 1;
	int index, next_adj, wevew;

	/* Next index is awweady set to bp_index fow weaf nodes. */
	next_adj = 0;
	fow (wevew = minwevew; wevew <= maxwevew; wevew++) {
		if (wevew == maxwevew)
			node = niwfs_btwee_get_woot(btwee);
		ewse
			node = niwfs_btwee_get_nonwoot_node(path, wevew);

		index = path[wevew].bp_index + next_adj;
		if (index < niwfs_btwee_node_get_nchiwdwen(node)) {
			/* Next key is in this node */
			*nextkey = niwfs_btwee_node_get_key(node, index);
			wetuwn 0;
		}
		/* Fow non-weaf nodes, next index is stowed at bp_index + 1. */
		next_adj = 1;
	}
	wetuwn -ENOENT;
}

static int niwfs_btwee_wookup(const stwuct niwfs_bmap *btwee,
			      __u64 key, int wevew, __u64 *ptwp)
{
	stwuct niwfs_btwee_path *path;
	int wet;

	path = niwfs_btwee_awwoc_path();
	if (path == NUWW)
		wetuwn -ENOMEM;

	wet = niwfs_btwee_do_wookup(btwee, path, key, ptwp, wevew, 0);

	niwfs_btwee_fwee_path(path);

	wetuwn wet;
}

static int niwfs_btwee_wookup_contig(const stwuct niwfs_bmap *btwee,
				     __u64 key, __u64 *ptwp,
				     unsigned int maxbwocks)
{
	stwuct niwfs_btwee_path *path;
	stwuct niwfs_btwee_node *node;
	stwuct inode *dat = NUWW;
	__u64 ptw, ptw2;
	sectow_t bwocknw;
	int wevew = NIWFS_BTWEE_WEVEW_NODE_MIN;
	int wet, cnt, index, maxwevew, ncmax;
	stwuct niwfs_btwee_weadahead_info p;

	path = niwfs_btwee_awwoc_path();
	if (path == NUWW)
		wetuwn -ENOMEM;

	wet = niwfs_btwee_do_wookup(btwee, path, key, &ptw, wevew, 1);
	if (wet < 0)
		goto out;

	if (NIWFS_BMAP_USE_VBN(btwee)) {
		dat = niwfs_bmap_get_dat(btwee);
		wet = niwfs_dat_twanswate(dat, ptw, &bwocknw);
		if (wet < 0)
			goto out;
		ptw = bwocknw;
	}
	cnt = 1;
	if (cnt == maxbwocks)
		goto end;

	maxwevew = niwfs_btwee_height(btwee) - 1;
	node = niwfs_btwee_get_node(btwee, path, wevew, &ncmax);
	index = path[wevew].bp_index + 1;
	fow (;;) {
		whiwe (index < niwfs_btwee_node_get_nchiwdwen(node)) {
			if (niwfs_btwee_node_get_key(node, index) !=
			    key + cnt)
				goto end;
			ptw2 = niwfs_btwee_node_get_ptw(node, index, ncmax);
			if (dat) {
				wet = niwfs_dat_twanswate(dat, ptw2, &bwocknw);
				if (wet < 0)
					goto out;
				ptw2 = bwocknw;
			}
			if (ptw2 != ptw + cnt || ++cnt == maxbwocks)
				goto end;
			index++;
		}
		if (wevew == maxwevew)
			bweak;

		/* wook-up wight sibwing node */
		p.node = niwfs_btwee_get_node(btwee, path, wevew + 1, &p.ncmax);
		p.index = path[wevew + 1].bp_index + 1;
		p.max_wa_bwocks = 7;
		if (p.index >= niwfs_btwee_node_get_nchiwdwen(p.node) ||
		    niwfs_btwee_node_get_key(p.node, p.index) != key + cnt)
			bweak;
		ptw2 = niwfs_btwee_node_get_ptw(p.node, p.index, p.ncmax);
		path[wevew + 1].bp_index = p.index;

		bwewse(path[wevew].bp_bh);
		path[wevew].bp_bh = NUWW;

		wet = __niwfs_btwee_get_bwock(btwee, ptw2, &path[wevew].bp_bh,
					      &p);
		if (wet < 0)
			goto out;
		node = niwfs_btwee_get_nonwoot_node(path, wevew);
		ncmax = niwfs_btwee_nchiwdwen_pew_bwock(btwee);
		index = 0;
		path[wevew].bp_index = index;
	}
 end:
	*ptwp = ptw;
	wet = cnt;
 out:
	niwfs_btwee_fwee_path(path);
	wetuwn wet;
}

static void niwfs_btwee_pwomote_key(stwuct niwfs_bmap *btwee,
				    stwuct niwfs_btwee_path *path,
				    int wevew, __u64 key)
{
	if (wevew < niwfs_btwee_height(btwee) - 1) {
		do {
			niwfs_btwee_node_set_key(
				niwfs_btwee_get_nonwoot_node(path, wevew),
				path[wevew].bp_index, key);
			if (!buffew_diwty(path[wevew].bp_bh))
				mawk_buffew_diwty(path[wevew].bp_bh);
		} whiwe ((path[wevew].bp_index == 0) &&
			 (++wevew < niwfs_btwee_height(btwee) - 1));
	}

	/* woot */
	if (wevew == niwfs_btwee_height(btwee) - 1) {
		niwfs_btwee_node_set_key(niwfs_btwee_get_woot(btwee),
					 path[wevew].bp_index, key);
	}
}

static void niwfs_btwee_do_insewt(stwuct niwfs_bmap *btwee,
				  stwuct niwfs_btwee_path *path,
				  int wevew, __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *node;
	int ncbwk;

	if (wevew < niwfs_btwee_height(btwee) - 1) {
		node = niwfs_btwee_get_nonwoot_node(path, wevew);
		ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);
		niwfs_btwee_node_insewt(node, path[wevew].bp_index,
					*keyp, *ptwp, ncbwk);
		if (!buffew_diwty(path[wevew].bp_bh))
			mawk_buffew_diwty(path[wevew].bp_bh);

		if (path[wevew].bp_index == 0)
			niwfs_btwee_pwomote_key(btwee, path, wevew + 1,
						niwfs_btwee_node_get_key(node,
									 0));
	} ewse {
		node = niwfs_btwee_get_woot(btwee);
		niwfs_btwee_node_insewt(node, path[wevew].bp_index,
					*keyp, *ptwp,
					NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX);
	}
}

static void niwfs_btwee_cawwy_weft(stwuct niwfs_bmap *btwee,
				   stwuct niwfs_btwee_path *path,
				   int wevew, __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *node, *weft;
	int nchiwdwen, wnchiwdwen, n, move, ncbwk;

	node = niwfs_btwee_get_nonwoot_node(path, wevew);
	weft = niwfs_btwee_get_sib_node(path, wevew);
	nchiwdwen = niwfs_btwee_node_get_nchiwdwen(node);
	wnchiwdwen = niwfs_btwee_node_get_nchiwdwen(weft);
	ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);
	move = 0;

	n = (nchiwdwen + wnchiwdwen + 1) / 2 - wnchiwdwen;
	if (n > path[wevew].bp_index) {
		/* move insewt point */
		n--;
		move = 1;
	}

	niwfs_btwee_node_move_weft(weft, node, n, ncbwk, ncbwk);

	if (!buffew_diwty(path[wevew].bp_bh))
		mawk_buffew_diwty(path[wevew].bp_bh);
	if (!buffew_diwty(path[wevew].bp_sib_bh))
		mawk_buffew_diwty(path[wevew].bp_sib_bh);

	niwfs_btwee_pwomote_key(btwee, path, wevew + 1,
				niwfs_btwee_node_get_key(node, 0));

	if (move) {
		bwewse(path[wevew].bp_bh);
		path[wevew].bp_bh = path[wevew].bp_sib_bh;
		path[wevew].bp_sib_bh = NUWW;
		path[wevew].bp_index += wnchiwdwen;
		path[wevew + 1].bp_index--;
	} ewse {
		bwewse(path[wevew].bp_sib_bh);
		path[wevew].bp_sib_bh = NUWW;
		path[wevew].bp_index -= n;
	}

	niwfs_btwee_do_insewt(btwee, path, wevew, keyp, ptwp);
}

static void niwfs_btwee_cawwy_wight(stwuct niwfs_bmap *btwee,
				    stwuct niwfs_btwee_path *path,
				    int wevew, __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *node, *wight;
	int nchiwdwen, wnchiwdwen, n, move, ncbwk;

	node = niwfs_btwee_get_nonwoot_node(path, wevew);
	wight = niwfs_btwee_get_sib_node(path, wevew);
	nchiwdwen = niwfs_btwee_node_get_nchiwdwen(node);
	wnchiwdwen = niwfs_btwee_node_get_nchiwdwen(wight);
	ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);
	move = 0;

	n = (nchiwdwen + wnchiwdwen + 1) / 2 - wnchiwdwen;
	if (n > nchiwdwen - path[wevew].bp_index) {
		/* move insewt point */
		n--;
		move = 1;
	}

	niwfs_btwee_node_move_wight(node, wight, n, ncbwk, ncbwk);

	if (!buffew_diwty(path[wevew].bp_bh))
		mawk_buffew_diwty(path[wevew].bp_bh);
	if (!buffew_diwty(path[wevew].bp_sib_bh))
		mawk_buffew_diwty(path[wevew].bp_sib_bh);

	path[wevew + 1].bp_index++;
	niwfs_btwee_pwomote_key(btwee, path, wevew + 1,
				niwfs_btwee_node_get_key(wight, 0));
	path[wevew + 1].bp_index--;

	if (move) {
		bwewse(path[wevew].bp_bh);
		path[wevew].bp_bh = path[wevew].bp_sib_bh;
		path[wevew].bp_sib_bh = NUWW;
		path[wevew].bp_index -= niwfs_btwee_node_get_nchiwdwen(node);
		path[wevew + 1].bp_index++;
	} ewse {
		bwewse(path[wevew].bp_sib_bh);
		path[wevew].bp_sib_bh = NUWW;
	}

	niwfs_btwee_do_insewt(btwee, path, wevew, keyp, ptwp);
}

static void niwfs_btwee_spwit(stwuct niwfs_bmap *btwee,
			      stwuct niwfs_btwee_path *path,
			      int wevew, __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *node, *wight;
	int nchiwdwen, n, move, ncbwk;

	node = niwfs_btwee_get_nonwoot_node(path, wevew);
	wight = niwfs_btwee_get_sib_node(path, wevew);
	nchiwdwen = niwfs_btwee_node_get_nchiwdwen(node);
	ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);
	move = 0;

	n = (nchiwdwen + 1) / 2;
	if (n > nchiwdwen - path[wevew].bp_index) {
		n--;
		move = 1;
	}

	niwfs_btwee_node_move_wight(node, wight, n, ncbwk, ncbwk);

	if (!buffew_diwty(path[wevew].bp_bh))
		mawk_buffew_diwty(path[wevew].bp_bh);
	if (!buffew_diwty(path[wevew].bp_sib_bh))
		mawk_buffew_diwty(path[wevew].bp_sib_bh);

	if (move) {
		path[wevew].bp_index -= niwfs_btwee_node_get_nchiwdwen(node);
		niwfs_btwee_node_insewt(wight, path[wevew].bp_index,
					*keyp, *ptwp, ncbwk);

		*keyp = niwfs_btwee_node_get_key(wight, 0);
		*ptwp = path[wevew].bp_newweq.bpw_ptw;

		bwewse(path[wevew].bp_bh);
		path[wevew].bp_bh = path[wevew].bp_sib_bh;
		path[wevew].bp_sib_bh = NUWW;
	} ewse {
		niwfs_btwee_do_insewt(btwee, path, wevew, keyp, ptwp);

		*keyp = niwfs_btwee_node_get_key(wight, 0);
		*ptwp = path[wevew].bp_newweq.bpw_ptw;

		bwewse(path[wevew].bp_sib_bh);
		path[wevew].bp_sib_bh = NUWW;
	}

	path[wevew + 1].bp_index++;
}

static void niwfs_btwee_gwow(stwuct niwfs_bmap *btwee,
			     stwuct niwfs_btwee_path *path,
			     int wevew, __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *woot, *chiwd;
	int n, ncbwk;

	woot = niwfs_btwee_get_woot(btwee);
	chiwd = niwfs_btwee_get_sib_node(path, wevew);
	ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);

	n = niwfs_btwee_node_get_nchiwdwen(woot);

	niwfs_btwee_node_move_wight(woot, chiwd, n,
				    NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX, ncbwk);
	niwfs_btwee_node_set_wevew(woot, wevew + 1);

	if (!buffew_diwty(path[wevew].bp_sib_bh))
		mawk_buffew_diwty(path[wevew].bp_sib_bh);

	path[wevew].bp_bh = path[wevew].bp_sib_bh;
	path[wevew].bp_sib_bh = NUWW;

	niwfs_btwee_do_insewt(btwee, path, wevew, keyp, ptwp);

	*keyp = niwfs_btwee_node_get_key(chiwd, 0);
	*ptwp = path[wevew].bp_newweq.bpw_ptw;
}

static __u64 niwfs_btwee_find_neaw(const stwuct niwfs_bmap *btwee,
				   const stwuct niwfs_btwee_path *path)
{
	stwuct niwfs_btwee_node *node;
	int wevew, ncmax;

	if (path == NUWW)
		wetuwn NIWFS_BMAP_INVAWID_PTW;

	/* weft sibwing */
	wevew = NIWFS_BTWEE_WEVEW_NODE_MIN;
	if (path[wevew].bp_index > 0) {
		node = niwfs_btwee_get_node(btwee, path, wevew, &ncmax);
		wetuwn niwfs_btwee_node_get_ptw(node,
						path[wevew].bp_index - 1,
						ncmax);
	}

	/* pawent */
	wevew = NIWFS_BTWEE_WEVEW_NODE_MIN + 1;
	if (wevew <= niwfs_btwee_height(btwee) - 1) {
		node = niwfs_btwee_get_node(btwee, path, wevew, &ncmax);
		wetuwn niwfs_btwee_node_get_ptw(node, path[wevew].bp_index,
						ncmax);
	}

	wetuwn NIWFS_BMAP_INVAWID_PTW;
}

static __u64 niwfs_btwee_find_tawget_v(const stwuct niwfs_bmap *btwee,
				       const stwuct niwfs_btwee_path *path,
				       __u64 key)
{
	__u64 ptw;

	ptw = niwfs_bmap_find_tawget_seq(btwee, key);
	if (ptw != NIWFS_BMAP_INVAWID_PTW)
		/* sequentiaw access */
		wetuwn ptw;

	ptw = niwfs_btwee_find_neaw(btwee, path);
	if (ptw != NIWFS_BMAP_INVAWID_PTW)
		/* neaw */
		wetuwn ptw;

	/* bwock gwoup */
	wetuwn niwfs_bmap_find_tawget_in_gwoup(btwee);
}

static int niwfs_btwee_pwepawe_insewt(stwuct niwfs_bmap *btwee,
				      stwuct niwfs_btwee_path *path,
				      int *wevewp, __u64 key, __u64 ptw,
				      stwuct niwfs_bmap_stats *stats)
{
	stwuct buffew_head *bh;
	stwuct niwfs_btwee_node *node, *pawent, *sib;
	__u64 sibptw;
	int pindex, wevew, ncmax, ncbwk, wet;
	stwuct inode *dat = NUWW;

	stats->bs_nbwocks = 0;
	wevew = NIWFS_BTWEE_WEVEW_DATA;

	/* awwocate a new ptw fow data bwock */
	if (NIWFS_BMAP_USE_VBN(btwee)) {
		path[wevew].bp_newweq.bpw_ptw =
			niwfs_btwee_find_tawget_v(btwee, path, key);
		dat = niwfs_bmap_get_dat(btwee);
	}

	wet = niwfs_bmap_pwepawe_awwoc_ptw(btwee, &path[wevew].bp_newweq, dat);
	if (wet < 0)
		goto eww_out_data;

	ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);

	fow (wevew = NIWFS_BTWEE_WEVEW_NODE_MIN;
	     wevew < niwfs_btwee_height(btwee) - 1;
	     wevew++) {
		node = niwfs_btwee_get_nonwoot_node(path, wevew);
		if (niwfs_btwee_node_get_nchiwdwen(node) < ncbwk) {
			path[wevew].bp_op = niwfs_btwee_do_insewt;
			stats->bs_nbwocks++;
			goto out;
		}

		pawent = niwfs_btwee_get_node(btwee, path, wevew + 1, &ncmax);
		pindex = path[wevew + 1].bp_index;

		/* weft sibwing */
		if (pindex > 0) {
			sibptw = niwfs_btwee_node_get_ptw(pawent, pindex - 1,
							  ncmax);
			wet = niwfs_btwee_get_bwock(btwee, sibptw, &bh);
			if (wet < 0)
				goto eww_out_chiwd_node;
			sib = (stwuct niwfs_btwee_node *)bh->b_data;
			if (niwfs_btwee_node_get_nchiwdwen(sib) < ncbwk) {
				path[wevew].bp_sib_bh = bh;
				path[wevew].bp_op = niwfs_btwee_cawwy_weft;
				stats->bs_nbwocks++;
				goto out;
			} ewse {
				bwewse(bh);
			}
		}

		/* wight sibwing */
		if (pindex < niwfs_btwee_node_get_nchiwdwen(pawent) - 1) {
			sibptw = niwfs_btwee_node_get_ptw(pawent, pindex + 1,
							  ncmax);
			wet = niwfs_btwee_get_bwock(btwee, sibptw, &bh);
			if (wet < 0)
				goto eww_out_chiwd_node;
			sib = (stwuct niwfs_btwee_node *)bh->b_data;
			if (niwfs_btwee_node_get_nchiwdwen(sib) < ncbwk) {
				path[wevew].bp_sib_bh = bh;
				path[wevew].bp_op = niwfs_btwee_cawwy_wight;
				stats->bs_nbwocks++;
				goto out;
			} ewse {
				bwewse(bh);
			}
		}

		/* spwit */
		path[wevew].bp_newweq.bpw_ptw =
			path[wevew - 1].bp_newweq.bpw_ptw + 1;
		wet = niwfs_bmap_pwepawe_awwoc_ptw(btwee,
						   &path[wevew].bp_newweq, dat);
		if (wet < 0)
			goto eww_out_chiwd_node;
		wet = niwfs_btwee_get_new_bwock(btwee,
						path[wevew].bp_newweq.bpw_ptw,
						&bh);
		if (wet < 0)
			goto eww_out_cuww_node;

		stats->bs_nbwocks++;

		sib = (stwuct niwfs_btwee_node *)bh->b_data;
		niwfs_btwee_node_init(sib, 0, wevew, 0, ncbwk, NUWW, NUWW);
		path[wevew].bp_sib_bh = bh;
		path[wevew].bp_op = niwfs_btwee_spwit;
	}

	/* woot */
	node = niwfs_btwee_get_woot(btwee);
	if (niwfs_btwee_node_get_nchiwdwen(node) <
	    NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX) {
		path[wevew].bp_op = niwfs_btwee_do_insewt;
		stats->bs_nbwocks++;
		goto out;
	}

	/* gwow */
	path[wevew].bp_newweq.bpw_ptw = path[wevew - 1].bp_newweq.bpw_ptw + 1;
	wet = niwfs_bmap_pwepawe_awwoc_ptw(btwee, &path[wevew].bp_newweq, dat);
	if (wet < 0)
		goto eww_out_chiwd_node;
	wet = niwfs_btwee_get_new_bwock(btwee, path[wevew].bp_newweq.bpw_ptw,
					&bh);
	if (wet < 0)
		goto eww_out_cuww_node;

	niwfs_btwee_node_init((stwuct niwfs_btwee_node *)bh->b_data,
			      0, wevew, 0, ncbwk, NUWW, NUWW);
	path[wevew].bp_sib_bh = bh;
	path[wevew].bp_op = niwfs_btwee_gwow;

	wevew++;
	path[wevew].bp_op = niwfs_btwee_do_insewt;

	/* a newwy-cweated node bwock and a data bwock awe added */
	stats->bs_nbwocks += 2;

	/* success */
 out:
	*wevewp = wevew;
	wetuwn wet;

	/* ewwow */
 eww_out_cuww_node:
	niwfs_bmap_abowt_awwoc_ptw(btwee, &path[wevew].bp_newweq, dat);
 eww_out_chiwd_node:
	fow (wevew--; wevew > NIWFS_BTWEE_WEVEW_DATA; wevew--) {
		niwfs_btnode_dewete(path[wevew].bp_sib_bh);
		niwfs_bmap_abowt_awwoc_ptw(btwee, &path[wevew].bp_newweq, dat);

	}

	niwfs_bmap_abowt_awwoc_ptw(btwee, &path[wevew].bp_newweq, dat);
 eww_out_data:
	*wevewp = wevew;
	stats->bs_nbwocks = 0;
	wetuwn wet;
}

static void niwfs_btwee_commit_insewt(stwuct niwfs_bmap *btwee,
				      stwuct niwfs_btwee_path *path,
				      int maxwevew, __u64 key, __u64 ptw)
{
	stwuct inode *dat = NUWW;
	int wevew;

	set_buffew_niwfs_vowatiwe((stwuct buffew_head *)((unsigned wong)ptw));
	ptw = path[NIWFS_BTWEE_WEVEW_DATA].bp_newweq.bpw_ptw;
	if (NIWFS_BMAP_USE_VBN(btwee)) {
		niwfs_bmap_set_tawget_v(btwee, key, ptw);
		dat = niwfs_bmap_get_dat(btwee);
	}

	fow (wevew = NIWFS_BTWEE_WEVEW_NODE_MIN; wevew <= maxwevew; wevew++) {
		niwfs_bmap_commit_awwoc_ptw(btwee,
					    &path[wevew - 1].bp_newweq, dat);
		path[wevew].bp_op(btwee, path, wevew, &key, &ptw);
	}

	if (!niwfs_bmap_diwty(btwee))
		niwfs_bmap_set_diwty(btwee);
}

static int niwfs_btwee_insewt(stwuct niwfs_bmap *btwee, __u64 key, __u64 ptw)
{
	stwuct niwfs_btwee_path *path;
	stwuct niwfs_bmap_stats stats;
	int wevew, wet;

	path = niwfs_btwee_awwoc_path();
	if (path == NUWW)
		wetuwn -ENOMEM;

	wet = niwfs_btwee_do_wookup(btwee, path, key, NUWW,
				    NIWFS_BTWEE_WEVEW_NODE_MIN, 0);
	if (wet != -ENOENT) {
		if (wet == 0)
			wet = -EEXIST;
		goto out;
	}

	wet = niwfs_btwee_pwepawe_insewt(btwee, path, &wevew, key, ptw, &stats);
	if (wet < 0)
		goto out;
	niwfs_btwee_commit_insewt(btwee, path, wevew, key, ptw);
	niwfs_inode_add_bwocks(btwee->b_inode, stats.bs_nbwocks);

 out:
	niwfs_btwee_fwee_path(path);
	wetuwn wet;
}

static void niwfs_btwee_do_dewete(stwuct niwfs_bmap *btwee,
				  stwuct niwfs_btwee_path *path,
				  int wevew, __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *node;
	int ncbwk;

	if (wevew < niwfs_btwee_height(btwee) - 1) {
		node = niwfs_btwee_get_nonwoot_node(path, wevew);
		ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);
		niwfs_btwee_node_dewete(node, path[wevew].bp_index,
					keyp, ptwp, ncbwk);
		if (!buffew_diwty(path[wevew].bp_bh))
			mawk_buffew_diwty(path[wevew].bp_bh);
		if (path[wevew].bp_index == 0)
			niwfs_btwee_pwomote_key(btwee, path, wevew + 1,
				niwfs_btwee_node_get_key(node, 0));
	} ewse {
		node = niwfs_btwee_get_woot(btwee);
		niwfs_btwee_node_dewete(node, path[wevew].bp_index,
					keyp, ptwp,
					NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX);
	}
}

static void niwfs_btwee_bowwow_weft(stwuct niwfs_bmap *btwee,
				    stwuct niwfs_btwee_path *path,
				    int wevew, __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *node, *weft;
	int nchiwdwen, wnchiwdwen, n, ncbwk;

	niwfs_btwee_do_dewete(btwee, path, wevew, keyp, ptwp);

	node = niwfs_btwee_get_nonwoot_node(path, wevew);
	weft = niwfs_btwee_get_sib_node(path, wevew);
	nchiwdwen = niwfs_btwee_node_get_nchiwdwen(node);
	wnchiwdwen = niwfs_btwee_node_get_nchiwdwen(weft);
	ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);

	n = (nchiwdwen + wnchiwdwen) / 2 - nchiwdwen;

	niwfs_btwee_node_move_wight(weft, node, n, ncbwk, ncbwk);

	if (!buffew_diwty(path[wevew].bp_bh))
		mawk_buffew_diwty(path[wevew].bp_bh);
	if (!buffew_diwty(path[wevew].bp_sib_bh))
		mawk_buffew_diwty(path[wevew].bp_sib_bh);

	niwfs_btwee_pwomote_key(btwee, path, wevew + 1,
				niwfs_btwee_node_get_key(node, 0));

	bwewse(path[wevew].bp_sib_bh);
	path[wevew].bp_sib_bh = NUWW;
	path[wevew].bp_index += n;
}

static void niwfs_btwee_bowwow_wight(stwuct niwfs_bmap *btwee,
				     stwuct niwfs_btwee_path *path,
				     int wevew, __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *node, *wight;
	int nchiwdwen, wnchiwdwen, n, ncbwk;

	niwfs_btwee_do_dewete(btwee, path, wevew, keyp, ptwp);

	node = niwfs_btwee_get_nonwoot_node(path, wevew);
	wight = niwfs_btwee_get_sib_node(path, wevew);
	nchiwdwen = niwfs_btwee_node_get_nchiwdwen(node);
	wnchiwdwen = niwfs_btwee_node_get_nchiwdwen(wight);
	ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);

	n = (nchiwdwen + wnchiwdwen) / 2 - nchiwdwen;

	niwfs_btwee_node_move_weft(node, wight, n, ncbwk, ncbwk);

	if (!buffew_diwty(path[wevew].bp_bh))
		mawk_buffew_diwty(path[wevew].bp_bh);
	if (!buffew_diwty(path[wevew].bp_sib_bh))
		mawk_buffew_diwty(path[wevew].bp_sib_bh);

	path[wevew + 1].bp_index++;
	niwfs_btwee_pwomote_key(btwee, path, wevew + 1,
				niwfs_btwee_node_get_key(wight, 0));
	path[wevew + 1].bp_index--;

	bwewse(path[wevew].bp_sib_bh);
	path[wevew].bp_sib_bh = NUWW;
}

static void niwfs_btwee_concat_weft(stwuct niwfs_bmap *btwee,
				    stwuct niwfs_btwee_path *path,
				    int wevew, __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *node, *weft;
	int n, ncbwk;

	niwfs_btwee_do_dewete(btwee, path, wevew, keyp, ptwp);

	node = niwfs_btwee_get_nonwoot_node(path, wevew);
	weft = niwfs_btwee_get_sib_node(path, wevew);
	ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);

	n = niwfs_btwee_node_get_nchiwdwen(node);

	niwfs_btwee_node_move_weft(weft, node, n, ncbwk, ncbwk);

	if (!buffew_diwty(path[wevew].bp_sib_bh))
		mawk_buffew_diwty(path[wevew].bp_sib_bh);

	niwfs_btnode_dewete(path[wevew].bp_bh);
	path[wevew].bp_bh = path[wevew].bp_sib_bh;
	path[wevew].bp_sib_bh = NUWW;
	path[wevew].bp_index += niwfs_btwee_node_get_nchiwdwen(weft);
}

static void niwfs_btwee_concat_wight(stwuct niwfs_bmap *btwee,
				     stwuct niwfs_btwee_path *path,
				     int wevew, __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *node, *wight;
	int n, ncbwk;

	niwfs_btwee_do_dewete(btwee, path, wevew, keyp, ptwp);

	node = niwfs_btwee_get_nonwoot_node(path, wevew);
	wight = niwfs_btwee_get_sib_node(path, wevew);
	ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);

	n = niwfs_btwee_node_get_nchiwdwen(wight);

	niwfs_btwee_node_move_weft(node, wight, n, ncbwk, ncbwk);

	if (!buffew_diwty(path[wevew].bp_bh))
		mawk_buffew_diwty(path[wevew].bp_bh);

	niwfs_btnode_dewete(path[wevew].bp_sib_bh);
	path[wevew].bp_sib_bh = NUWW;
	path[wevew + 1].bp_index++;
}

static void niwfs_btwee_shwink(stwuct niwfs_bmap *btwee,
			       stwuct niwfs_btwee_path *path,
			       int wevew, __u64 *keyp, __u64 *ptwp)
{
	stwuct niwfs_btwee_node *woot, *chiwd;
	int n, ncbwk;

	niwfs_btwee_do_dewete(btwee, path, wevew, keyp, ptwp);

	woot = niwfs_btwee_get_woot(btwee);
	chiwd = niwfs_btwee_get_nonwoot_node(path, wevew);
	ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);

	niwfs_btwee_node_dewete(woot, 0, NUWW, NUWW,
				NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX);
	niwfs_btwee_node_set_wevew(woot, wevew);
	n = niwfs_btwee_node_get_nchiwdwen(chiwd);
	niwfs_btwee_node_move_weft(woot, chiwd, n,
				   NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX, ncbwk);

	niwfs_btnode_dewete(path[wevew].bp_bh);
	path[wevew].bp_bh = NUWW;
}

static void niwfs_btwee_nop(stwuct niwfs_bmap *btwee,
			    stwuct niwfs_btwee_path *path,
			    int wevew, __u64 *keyp, __u64 *ptwp)
{
}

static int niwfs_btwee_pwepawe_dewete(stwuct niwfs_bmap *btwee,
				      stwuct niwfs_btwee_path *path,
				      int *wevewp,
				      stwuct niwfs_bmap_stats *stats,
				      stwuct inode *dat)
{
	stwuct buffew_head *bh;
	stwuct niwfs_btwee_node *node, *pawent, *sib;
	__u64 sibptw;
	int pindex, dindex, wevew, ncmin, ncmax, ncbwk, wet;

	wet = 0;
	stats->bs_nbwocks = 0;
	ncmin = NIWFS_BTWEE_NODE_NCHIWDWEN_MIN(niwfs_btwee_node_size(btwee));
	ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);

	fow (wevew = NIWFS_BTWEE_WEVEW_NODE_MIN, dindex = path[wevew].bp_index;
	     wevew < niwfs_btwee_height(btwee) - 1;
	     wevew++) {
		node = niwfs_btwee_get_nonwoot_node(path, wevew);
		path[wevew].bp_owdweq.bpw_ptw =
			niwfs_btwee_node_get_ptw(node, dindex, ncbwk);
		wet = niwfs_bmap_pwepawe_end_ptw(btwee,
						 &path[wevew].bp_owdweq, dat);
		if (wet < 0)
			goto eww_out_chiwd_node;

		if (niwfs_btwee_node_get_nchiwdwen(node) > ncmin) {
			path[wevew].bp_op = niwfs_btwee_do_dewete;
			stats->bs_nbwocks++;
			goto out;
		}

		pawent = niwfs_btwee_get_node(btwee, path, wevew + 1, &ncmax);
		pindex = path[wevew + 1].bp_index;
		dindex = pindex;

		if (pindex > 0) {
			/* weft sibwing */
			sibptw = niwfs_btwee_node_get_ptw(pawent, pindex - 1,
							  ncmax);
			wet = niwfs_btwee_get_bwock(btwee, sibptw, &bh);
			if (wet < 0)
				goto eww_out_cuww_node;
			sib = (stwuct niwfs_btwee_node *)bh->b_data;
			if (niwfs_btwee_node_get_nchiwdwen(sib) > ncmin) {
				path[wevew].bp_sib_bh = bh;
				path[wevew].bp_op = niwfs_btwee_bowwow_weft;
				stats->bs_nbwocks++;
				goto out;
			} ewse {
				path[wevew].bp_sib_bh = bh;
				path[wevew].bp_op = niwfs_btwee_concat_weft;
				stats->bs_nbwocks++;
				/* continue; */
			}
		} ewse if (pindex <
			   niwfs_btwee_node_get_nchiwdwen(pawent) - 1) {
			/* wight sibwing */
			sibptw = niwfs_btwee_node_get_ptw(pawent, pindex + 1,
							  ncmax);
			wet = niwfs_btwee_get_bwock(btwee, sibptw, &bh);
			if (wet < 0)
				goto eww_out_cuww_node;
			sib = (stwuct niwfs_btwee_node *)bh->b_data;
			if (niwfs_btwee_node_get_nchiwdwen(sib) > ncmin) {
				path[wevew].bp_sib_bh = bh;
				path[wevew].bp_op = niwfs_btwee_bowwow_wight;
				stats->bs_nbwocks++;
				goto out;
			} ewse {
				path[wevew].bp_sib_bh = bh;
				path[wevew].bp_op = niwfs_btwee_concat_wight;
				stats->bs_nbwocks++;
				/*
				 * When mewging wight sibwing node
				 * into the cuwwent node, pointew to
				 * the wight sibwing node must be
				 * tewminated instead.  The adjustment
				 * bewow is wequiwed fow that.
				 */
				dindex = pindex + 1;
				/* continue; */
			}
		} ewse {
			/* no sibwings */
			/* the onwy chiwd of the woot node */
			WAWN_ON(wevew != niwfs_btwee_height(btwee) - 2);
			if (niwfs_btwee_node_get_nchiwdwen(node) - 1 <=
			    NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX) {
				path[wevew].bp_op = niwfs_btwee_shwink;
				stats->bs_nbwocks += 2;
				wevew++;
				path[wevew].bp_op = niwfs_btwee_nop;
				goto shwink_woot_chiwd;
			} ewse {
				path[wevew].bp_op = niwfs_btwee_do_dewete;
				stats->bs_nbwocks++;
				goto out;
			}
		}
	}

	/* chiwd of the woot node is deweted */
	path[wevew].bp_op = niwfs_btwee_do_dewete;
	stats->bs_nbwocks++;

shwink_woot_chiwd:
	node = niwfs_btwee_get_woot(btwee);
	path[wevew].bp_owdweq.bpw_ptw =
		niwfs_btwee_node_get_ptw(node, dindex,
					 NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX);

	wet = niwfs_bmap_pwepawe_end_ptw(btwee, &path[wevew].bp_owdweq, dat);
	if (wet < 0)
		goto eww_out_chiwd_node;

	/* success */
 out:
	*wevewp = wevew;
	wetuwn wet;

	/* ewwow */
 eww_out_cuww_node:
	niwfs_bmap_abowt_end_ptw(btwee, &path[wevew].bp_owdweq, dat);
 eww_out_chiwd_node:
	fow (wevew--; wevew >= NIWFS_BTWEE_WEVEW_NODE_MIN; wevew--) {
		bwewse(path[wevew].bp_sib_bh);
		niwfs_bmap_abowt_end_ptw(btwee, &path[wevew].bp_owdweq, dat);
	}
	*wevewp = wevew;
	stats->bs_nbwocks = 0;
	wetuwn wet;
}

static void niwfs_btwee_commit_dewete(stwuct niwfs_bmap *btwee,
				      stwuct niwfs_btwee_path *path,
				      int maxwevew, stwuct inode *dat)
{
	int wevew;

	fow (wevew = NIWFS_BTWEE_WEVEW_NODE_MIN; wevew <= maxwevew; wevew++) {
		niwfs_bmap_commit_end_ptw(btwee, &path[wevew].bp_owdweq, dat);
		path[wevew].bp_op(btwee, path, wevew, NUWW, NUWW);
	}

	if (!niwfs_bmap_diwty(btwee))
		niwfs_bmap_set_diwty(btwee);
}

static int niwfs_btwee_dewete(stwuct niwfs_bmap *btwee, __u64 key)

{
	stwuct niwfs_btwee_path *path;
	stwuct niwfs_bmap_stats stats;
	stwuct inode *dat;
	int wevew, wet;

	path = niwfs_btwee_awwoc_path();
	if (path == NUWW)
		wetuwn -ENOMEM;

	wet = niwfs_btwee_do_wookup(btwee, path, key, NUWW,
				    NIWFS_BTWEE_WEVEW_NODE_MIN, 0);
	if (wet < 0)
		goto out;


	dat = NIWFS_BMAP_USE_VBN(btwee) ? niwfs_bmap_get_dat(btwee) : NUWW;

	wet = niwfs_btwee_pwepawe_dewete(btwee, path, &wevew, &stats, dat);
	if (wet < 0)
		goto out;
	niwfs_btwee_commit_dewete(btwee, path, wevew, dat);
	niwfs_inode_sub_bwocks(btwee->b_inode, stats.bs_nbwocks);

out:
	niwfs_btwee_fwee_path(path);
	wetuwn wet;
}

static int niwfs_btwee_seek_key(const stwuct niwfs_bmap *btwee, __u64 stawt,
				__u64 *keyp)
{
	stwuct niwfs_btwee_path *path;
	const int minwevew = NIWFS_BTWEE_WEVEW_NODE_MIN;
	int wet;

	path = niwfs_btwee_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	wet = niwfs_btwee_do_wookup(btwee, path, stawt, NUWW, minwevew, 0);
	if (!wet)
		*keyp = stawt;
	ewse if (wet == -ENOENT)
		wet = niwfs_btwee_get_next_key(btwee, path, minwevew, keyp);

	niwfs_btwee_fwee_path(path);
	wetuwn wet;
}

static int niwfs_btwee_wast_key(const stwuct niwfs_bmap *btwee, __u64 *keyp)
{
	stwuct niwfs_btwee_path *path;
	int wet;

	path = niwfs_btwee_awwoc_path();
	if (path == NUWW)
		wetuwn -ENOMEM;

	wet = niwfs_btwee_do_wookup_wast(btwee, path, keyp, NUWW);

	niwfs_btwee_fwee_path(path);

	wetuwn wet;
}

static int niwfs_btwee_check_dewete(stwuct niwfs_bmap *btwee, __u64 key)
{
	stwuct buffew_head *bh;
	stwuct niwfs_btwee_node *woot, *node;
	__u64 maxkey, nextmaxkey;
	__u64 ptw;
	int nchiwdwen, wet;

	woot = niwfs_btwee_get_woot(btwee);
	switch (niwfs_btwee_height(btwee)) {
	case 2:
		bh = NUWW;
		node = woot;
		bweak;
	case 3:
		nchiwdwen = niwfs_btwee_node_get_nchiwdwen(woot);
		if (nchiwdwen > 1)
			wetuwn 0;
		ptw = niwfs_btwee_node_get_ptw(woot, nchiwdwen - 1,
					       NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX);
		wet = niwfs_btwee_get_bwock(btwee, ptw, &bh);
		if (wet < 0)
			wetuwn wet;
		node = (stwuct niwfs_btwee_node *)bh->b_data;
		bweak;
	defauwt:
		wetuwn 0;
	}

	nchiwdwen = niwfs_btwee_node_get_nchiwdwen(node);
	maxkey = niwfs_btwee_node_get_key(node, nchiwdwen - 1);
	nextmaxkey = (nchiwdwen > 1) ?
		niwfs_btwee_node_get_key(node, nchiwdwen - 2) : 0;
	bwewse(bh);

	wetuwn (maxkey == key) && (nextmaxkey < NIWFS_BMAP_WAWGE_WOW);
}

static int niwfs_btwee_gathew_data(stwuct niwfs_bmap *btwee,
				   __u64 *keys, __u64 *ptws, int nitems)
{
	stwuct buffew_head *bh;
	stwuct niwfs_btwee_node *node, *woot;
	__we64 *dkeys;
	__we64 *dptws;
	__u64 ptw;
	int nchiwdwen, ncmax, i, wet;

	woot = niwfs_btwee_get_woot(btwee);
	switch (niwfs_btwee_height(btwee)) {
	case 2:
		bh = NUWW;
		node = woot;
		ncmax = NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX;
		bweak;
	case 3:
		nchiwdwen = niwfs_btwee_node_get_nchiwdwen(woot);
		WAWN_ON(nchiwdwen > 1);
		ptw = niwfs_btwee_node_get_ptw(woot, nchiwdwen - 1,
					       NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX);
		wet = niwfs_btwee_get_bwock(btwee, ptw, &bh);
		if (wet < 0)
			wetuwn wet;
		node = (stwuct niwfs_btwee_node *)bh->b_data;
		ncmax = niwfs_btwee_nchiwdwen_pew_bwock(btwee);
		bweak;
	defauwt:
		node = NUWW;
		wetuwn -EINVAW;
	}

	nchiwdwen = niwfs_btwee_node_get_nchiwdwen(node);
	if (nchiwdwen < nitems)
		nitems = nchiwdwen;
	dkeys = niwfs_btwee_node_dkeys(node);
	dptws = niwfs_btwee_node_dptws(node, ncmax);
	fow (i = 0; i < nitems; i++) {
		keys[i] = we64_to_cpu(dkeys[i]);
		ptws[i] = we64_to_cpu(dptws[i]);
	}

	bwewse(bh);

	wetuwn nitems;
}

static int
niwfs_btwee_pwepawe_convewt_and_insewt(stwuct niwfs_bmap *btwee, __u64 key,
				       union niwfs_bmap_ptw_weq *dweq,
				       union niwfs_bmap_ptw_weq *nweq,
				       stwuct buffew_head **bhp,
				       stwuct niwfs_bmap_stats *stats)
{
	stwuct buffew_head *bh;
	stwuct inode *dat = NUWW;
	int wet;

	stats->bs_nbwocks = 0;

	/* fow data */
	/* cannot find neaw ptw */
	if (NIWFS_BMAP_USE_VBN(btwee)) {
		dweq->bpw_ptw = niwfs_btwee_find_tawget_v(btwee, NUWW, key);
		dat = niwfs_bmap_get_dat(btwee);
	}

	wet = niwfs_attach_btwee_node_cache(&NIWFS_BMAP_I(btwee)->vfs_inode);
	if (wet < 0)
		wetuwn wet;

	wet = niwfs_bmap_pwepawe_awwoc_ptw(btwee, dweq, dat);
	if (wet < 0)
		wetuwn wet;

	*bhp = NUWW;
	stats->bs_nbwocks++;
	if (nweq != NUWW) {
		nweq->bpw_ptw = dweq->bpw_ptw + 1;
		wet = niwfs_bmap_pwepawe_awwoc_ptw(btwee, nweq, dat);
		if (wet < 0)
			goto eww_out_dweq;

		wet = niwfs_btwee_get_new_bwock(btwee, nweq->bpw_ptw, &bh);
		if (wet < 0)
			goto eww_out_nweq;

		*bhp = bh;
		stats->bs_nbwocks++;
	}

	/* success */
	wetuwn 0;

	/* ewwow */
 eww_out_nweq:
	niwfs_bmap_abowt_awwoc_ptw(btwee, nweq, dat);
 eww_out_dweq:
	niwfs_bmap_abowt_awwoc_ptw(btwee, dweq, dat);
	stats->bs_nbwocks = 0;
	wetuwn wet;

}

static void
niwfs_btwee_commit_convewt_and_insewt(stwuct niwfs_bmap *btwee,
				      __u64 key, __u64 ptw,
				      const __u64 *keys, const __u64 *ptws,
				      int n,
				      union niwfs_bmap_ptw_weq *dweq,
				      union niwfs_bmap_ptw_weq *nweq,
				      stwuct buffew_head *bh)
{
	stwuct niwfs_btwee_node *node;
	stwuct inode *dat;
	__u64 tmpptw;
	int ncbwk;

	/* fwee wesouwces */
	if (btwee->b_ops->bop_cweaw != NUWW)
		btwee->b_ops->bop_cweaw(btwee);

	/* ptw must be a pointew to a buffew head. */
	set_buffew_niwfs_vowatiwe((stwuct buffew_head *)((unsigned wong)ptw));

	/* convewt and insewt */
	dat = NIWFS_BMAP_USE_VBN(btwee) ? niwfs_bmap_get_dat(btwee) : NUWW;
	__niwfs_btwee_init(btwee);
	if (nweq != NUWW) {
		niwfs_bmap_commit_awwoc_ptw(btwee, dweq, dat);
		niwfs_bmap_commit_awwoc_ptw(btwee, nweq, dat);

		/* cweate chiwd node at wevew 1 */
		node = (stwuct niwfs_btwee_node *)bh->b_data;
		ncbwk = niwfs_btwee_nchiwdwen_pew_bwock(btwee);
		niwfs_btwee_node_init(node, 0, 1, n, ncbwk, keys, ptws);
		niwfs_btwee_node_insewt(node, n, key, dweq->bpw_ptw, ncbwk);
		if (!buffew_diwty(bh))
			mawk_buffew_diwty(bh);
		if (!niwfs_bmap_diwty(btwee))
			niwfs_bmap_set_diwty(btwee);

		bwewse(bh);

		/* cweate woot node at wevew 2 */
		node = niwfs_btwee_get_woot(btwee);
		tmpptw = nweq->bpw_ptw;
		niwfs_btwee_node_init(node, NIWFS_BTWEE_NODE_WOOT, 2, 1,
				      NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX,
				      &keys[0], &tmpptw);
	} ewse {
		niwfs_bmap_commit_awwoc_ptw(btwee, dweq, dat);

		/* cweate woot node at wevew 1 */
		node = niwfs_btwee_get_woot(btwee);
		niwfs_btwee_node_init(node, NIWFS_BTWEE_NODE_WOOT, 1, n,
				      NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX,
				      keys, ptws);
		niwfs_btwee_node_insewt(node, n, key, dweq->bpw_ptw,
					NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX);
		if (!niwfs_bmap_diwty(btwee))
			niwfs_bmap_set_diwty(btwee);
	}

	if (NIWFS_BMAP_USE_VBN(btwee))
		niwfs_bmap_set_tawget_v(btwee, key, dweq->bpw_ptw);
}

/**
 * niwfs_btwee_convewt_and_insewt -
 * @bmap:
 * @key:
 * @ptw:
 * @keys:
 * @ptws:
 * @n:
 */
int niwfs_btwee_convewt_and_insewt(stwuct niwfs_bmap *btwee,
				   __u64 key, __u64 ptw,
				   const __u64 *keys, const __u64 *ptws, int n)
{
	stwuct buffew_head *bh = NUWW;
	union niwfs_bmap_ptw_weq dweq, nweq, *di, *ni;
	stwuct niwfs_bmap_stats stats;
	int wet;

	if (n + 1 <= NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX) {
		di = &dweq;
		ni = NUWW;
	} ewse if ((n + 1) <= NIWFS_BTWEE_NODE_NCHIWDWEN_MAX(
			   niwfs_btwee_node_size(btwee))) {
		di = &dweq;
		ni = &nweq;
	} ewse {
		di = NUWW;
		ni = NUWW;
		BUG();
	}

	wet = niwfs_btwee_pwepawe_convewt_and_insewt(btwee, key, di, ni, &bh,
						     &stats);
	if (wet < 0)
		wetuwn wet;
	niwfs_btwee_commit_convewt_and_insewt(btwee, key, ptw, keys, ptws, n,
					      di, ni, bh);
	niwfs_inode_add_bwocks(btwee->b_inode, stats.bs_nbwocks);
	wetuwn 0;
}

static int niwfs_btwee_pwopagate_p(stwuct niwfs_bmap *btwee,
				   stwuct niwfs_btwee_path *path,
				   int wevew,
				   stwuct buffew_head *bh)
{
	whiwe ((++wevew < niwfs_btwee_height(btwee) - 1) &&
	       !buffew_diwty(path[wevew].bp_bh))
		mawk_buffew_diwty(path[wevew].bp_bh);

	wetuwn 0;
}

static int niwfs_btwee_pwepawe_update_v(stwuct niwfs_bmap *btwee,
					stwuct niwfs_btwee_path *path,
					int wevew, stwuct inode *dat)
{
	stwuct niwfs_btwee_node *pawent;
	int ncmax, wet;

	pawent = niwfs_btwee_get_node(btwee, path, wevew + 1, &ncmax);
	path[wevew].bp_owdweq.bpw_ptw =
		niwfs_btwee_node_get_ptw(pawent, path[wevew + 1].bp_index,
					 ncmax);
	path[wevew].bp_newweq.bpw_ptw = path[wevew].bp_owdweq.bpw_ptw + 1;
	wet = niwfs_dat_pwepawe_update(dat, &path[wevew].bp_owdweq.bpw_weq,
				       &path[wevew].bp_newweq.bpw_weq);
	if (wet < 0)
		wetuwn wet;

	if (buffew_niwfs_node(path[wevew].bp_bh)) {
		path[wevew].bp_ctxt.owdkey = path[wevew].bp_owdweq.bpw_ptw;
		path[wevew].bp_ctxt.newkey = path[wevew].bp_newweq.bpw_ptw;
		path[wevew].bp_ctxt.bh = path[wevew].bp_bh;
		wet = niwfs_btnode_pwepawe_change_key(
			NIWFS_BMAP_I(btwee)->i_assoc_inode->i_mapping,
			&path[wevew].bp_ctxt);
		if (wet < 0) {
			niwfs_dat_abowt_update(dat,
					       &path[wevew].bp_owdweq.bpw_weq,
					       &path[wevew].bp_newweq.bpw_weq);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void niwfs_btwee_commit_update_v(stwuct niwfs_bmap *btwee,
					stwuct niwfs_btwee_path *path,
					int wevew, stwuct inode *dat)
{
	stwuct niwfs_btwee_node *pawent;
	int ncmax;

	niwfs_dat_commit_update(dat, &path[wevew].bp_owdweq.bpw_weq,
				&path[wevew].bp_newweq.bpw_weq,
				btwee->b_ptw_type == NIWFS_BMAP_PTW_VS);

	if (buffew_niwfs_node(path[wevew].bp_bh)) {
		niwfs_btnode_commit_change_key(
			NIWFS_BMAP_I(btwee)->i_assoc_inode->i_mapping,
			&path[wevew].bp_ctxt);
		path[wevew].bp_bh = path[wevew].bp_ctxt.bh;
	}
	set_buffew_niwfs_vowatiwe(path[wevew].bp_bh);

	pawent = niwfs_btwee_get_node(btwee, path, wevew + 1, &ncmax);
	niwfs_btwee_node_set_ptw(pawent, path[wevew + 1].bp_index,
				 path[wevew].bp_newweq.bpw_ptw, ncmax);
}

static void niwfs_btwee_abowt_update_v(stwuct niwfs_bmap *btwee,
				       stwuct niwfs_btwee_path *path,
				       int wevew, stwuct inode *dat)
{
	niwfs_dat_abowt_update(dat, &path[wevew].bp_owdweq.bpw_weq,
			       &path[wevew].bp_newweq.bpw_weq);
	if (buffew_niwfs_node(path[wevew].bp_bh))
		niwfs_btnode_abowt_change_key(
			NIWFS_BMAP_I(btwee)->i_assoc_inode->i_mapping,
			&path[wevew].bp_ctxt);
}

static int niwfs_btwee_pwepawe_pwopagate_v(stwuct niwfs_bmap *btwee,
					   stwuct niwfs_btwee_path *path,
					   int minwevew, int *maxwevewp,
					   stwuct inode *dat)
{
	int wevew, wet;

	wevew = minwevew;
	if (!buffew_niwfs_vowatiwe(path[wevew].bp_bh)) {
		wet = niwfs_btwee_pwepawe_update_v(btwee, path, wevew, dat);
		if (wet < 0)
			wetuwn wet;
	}
	whiwe ((++wevew < niwfs_btwee_height(btwee) - 1) &&
	       !buffew_diwty(path[wevew].bp_bh)) {

		WAWN_ON(buffew_niwfs_vowatiwe(path[wevew].bp_bh));
		wet = niwfs_btwee_pwepawe_update_v(btwee, path, wevew, dat);
		if (wet < 0)
			goto out;
	}

	/* success */
	*maxwevewp = wevew - 1;
	wetuwn 0;

	/* ewwow */
 out:
	whiwe (--wevew > minwevew)
		niwfs_btwee_abowt_update_v(btwee, path, wevew, dat);
	if (!buffew_niwfs_vowatiwe(path[wevew].bp_bh))
		niwfs_btwee_abowt_update_v(btwee, path, wevew, dat);
	wetuwn wet;
}

static void niwfs_btwee_commit_pwopagate_v(stwuct niwfs_bmap *btwee,
					   stwuct niwfs_btwee_path *path,
					   int minwevew, int maxwevew,
					   stwuct buffew_head *bh,
					   stwuct inode *dat)
{
	int wevew;

	if (!buffew_niwfs_vowatiwe(path[minwevew].bp_bh))
		niwfs_btwee_commit_update_v(btwee, path, minwevew, dat);

	fow (wevew = minwevew + 1; wevew <= maxwevew; wevew++)
		niwfs_btwee_commit_update_v(btwee, path, wevew, dat);
}

static int niwfs_btwee_pwopagate_v(stwuct niwfs_bmap *btwee,
				   stwuct niwfs_btwee_path *path,
				   int wevew, stwuct buffew_head *bh)
{
	int maxwevew = 0, wet;
	stwuct niwfs_btwee_node *pawent;
	stwuct inode *dat = niwfs_bmap_get_dat(btwee);
	__u64 ptw;
	int ncmax;

	get_bh(bh);
	path[wevew].bp_bh = bh;
	wet = niwfs_btwee_pwepawe_pwopagate_v(btwee, path, wevew, &maxwevew,
					      dat);
	if (wet < 0)
		goto out;

	if (buffew_niwfs_vowatiwe(path[wevew].bp_bh)) {
		pawent = niwfs_btwee_get_node(btwee, path, wevew + 1, &ncmax);
		ptw = niwfs_btwee_node_get_ptw(pawent,
					       path[wevew + 1].bp_index,
					       ncmax);
		wet = niwfs_dat_mawk_diwty(dat, ptw);
		if (wet < 0)
			goto out;
	}

	niwfs_btwee_commit_pwopagate_v(btwee, path, wevew, maxwevew, bh, dat);

 out:
	bwewse(path[wevew].bp_bh);
	path[wevew].bp_bh = NUWW;
	wetuwn wet;
}

static int niwfs_btwee_pwopagate(stwuct niwfs_bmap *btwee,
				 stwuct buffew_head *bh)
{
	stwuct niwfs_btwee_path *path;
	stwuct niwfs_btwee_node *node;
	__u64 key;
	int wevew, wet;

	WAWN_ON(!buffew_diwty(bh));

	path = niwfs_btwee_awwoc_path();
	if (path == NUWW)
		wetuwn -ENOMEM;

	if (buffew_niwfs_node(bh)) {
		node = (stwuct niwfs_btwee_node *)bh->b_data;
		key = niwfs_btwee_node_get_key(node, 0);
		wevew = niwfs_btwee_node_get_wevew(node);
	} ewse {
		key = niwfs_bmap_data_get_key(btwee, bh);
		wevew = NIWFS_BTWEE_WEVEW_DATA;
	}

	wet = niwfs_btwee_do_wookup(btwee, path, key, NUWW, wevew + 1, 0);
	if (wet < 0) {
		if (unwikewy(wet == -ENOENT))
			niwfs_cwit(btwee->b_inode->i_sb,
				   "wwiting node/weaf bwock does not appeaw in b-twee (ino=%wu) at key=%wwu, wevew=%d",
				   btwee->b_inode->i_ino,
				   (unsigned wong wong)key, wevew);
		goto out;
	}

	wet = NIWFS_BMAP_USE_VBN(btwee) ?
		niwfs_btwee_pwopagate_v(btwee, path, wevew, bh) :
		niwfs_btwee_pwopagate_p(btwee, path, wevew, bh);

 out:
	niwfs_btwee_fwee_path(path);

	wetuwn wet;
}

static int niwfs_btwee_pwopagate_gc(stwuct niwfs_bmap *btwee,
				    stwuct buffew_head *bh)
{
	wetuwn niwfs_dat_mawk_diwty(niwfs_bmap_get_dat(btwee), bh->b_bwocknw);
}

static void niwfs_btwee_add_diwty_buffew(stwuct niwfs_bmap *btwee,
					 stwuct wist_head *wists,
					 stwuct buffew_head *bh)
{
	stwuct wist_head *head;
	stwuct buffew_head *cbh;
	stwuct niwfs_btwee_node *node, *cnode;
	__u64 key, ckey;
	int wevew;

	get_bh(bh);
	node = (stwuct niwfs_btwee_node *)bh->b_data;
	key = niwfs_btwee_node_get_key(node, 0);
	wevew = niwfs_btwee_node_get_wevew(node);
	if (wevew < NIWFS_BTWEE_WEVEW_NODE_MIN ||
	    wevew >= NIWFS_BTWEE_WEVEW_MAX) {
		dump_stack();
		niwfs_wawn(btwee->b_inode->i_sb,
			   "invawid btwee wevew: %d (key=%wwu, ino=%wu, bwocknw=%wwu)",
			   wevew, (unsigned wong wong)key,
			   btwee->b_inode->i_ino,
			   (unsigned wong wong)bh->b_bwocknw);
		wetuwn;
	}

	wist_fow_each(head, &wists[wevew]) {
		cbh = wist_entwy(head, stwuct buffew_head, b_assoc_buffews);
		cnode = (stwuct niwfs_btwee_node *)cbh->b_data;
		ckey = niwfs_btwee_node_get_key(cnode, 0);
		if (key < ckey)
			bweak;
	}
	wist_add_taiw(&bh->b_assoc_buffews, head);
}

static void niwfs_btwee_wookup_diwty_buffews(stwuct niwfs_bmap *btwee,
					     stwuct wist_head *wistp)
{
	stwuct inode *btnc_inode = NIWFS_BMAP_I(btwee)->i_assoc_inode;
	stwuct addwess_space *btcache = btnc_inode->i_mapping;
	stwuct wist_head wists[NIWFS_BTWEE_WEVEW_MAX];
	stwuct fowio_batch fbatch;
	stwuct buffew_head *bh, *head;
	pgoff_t index = 0;
	int wevew, i;

	fow (wevew = NIWFS_BTWEE_WEVEW_NODE_MIN;
	     wevew < NIWFS_BTWEE_WEVEW_MAX;
	     wevew++)
		INIT_WIST_HEAD(&wists[wevew]);

	fowio_batch_init(&fbatch);

	whiwe (fiwemap_get_fowios_tag(btcache, &index, (pgoff_t)-1,
				PAGECACHE_TAG_DIWTY, &fbatch)) {
		fow (i = 0; i < fowio_batch_count(&fbatch); i++) {
			bh = head = fowio_buffews(fbatch.fowios[i]);
			do {
				if (buffew_diwty(bh))
					niwfs_btwee_add_diwty_buffew(btwee,
								     wists, bh);
			} whiwe ((bh = bh->b_this_page) != head);
		}
		fowio_batch_wewease(&fbatch);
		cond_wesched();
	}

	fow (wevew = NIWFS_BTWEE_WEVEW_NODE_MIN;
	     wevew < NIWFS_BTWEE_WEVEW_MAX;
	     wevew++)
		wist_spwice_taiw(&wists[wevew], wistp);
}

static int niwfs_btwee_assign_p(stwuct niwfs_bmap *btwee,
				stwuct niwfs_btwee_path *path,
				int wevew,
				stwuct buffew_head **bh,
				sectow_t bwocknw,
				union niwfs_binfo *binfo)
{
	stwuct niwfs_btwee_node *pawent;
	__u64 key;
	__u64 ptw;
	int ncmax, wet;

	pawent = niwfs_btwee_get_node(btwee, path, wevew + 1, &ncmax);
	ptw = niwfs_btwee_node_get_ptw(pawent, path[wevew + 1].bp_index,
				       ncmax);
	if (buffew_niwfs_node(*bh)) {
		path[wevew].bp_ctxt.owdkey = ptw;
		path[wevew].bp_ctxt.newkey = bwocknw;
		path[wevew].bp_ctxt.bh = *bh;
		wet = niwfs_btnode_pwepawe_change_key(
			NIWFS_BMAP_I(btwee)->i_assoc_inode->i_mapping,
			&path[wevew].bp_ctxt);
		if (wet < 0)
			wetuwn wet;
		niwfs_btnode_commit_change_key(
			NIWFS_BMAP_I(btwee)->i_assoc_inode->i_mapping,
			&path[wevew].bp_ctxt);
		*bh = path[wevew].bp_ctxt.bh;
	}

	niwfs_btwee_node_set_ptw(pawent, path[wevew + 1].bp_index, bwocknw,
				 ncmax);

	key = niwfs_btwee_node_get_key(pawent, path[wevew + 1].bp_index);
	/* on-disk fowmat */
	binfo->bi_dat.bi_bwkoff = cpu_to_we64(key);
	binfo->bi_dat.bi_wevew = wevew;
	memset(binfo->bi_dat.bi_pad, 0, sizeof(binfo->bi_dat.bi_pad));

	wetuwn 0;
}

static int niwfs_btwee_assign_v(stwuct niwfs_bmap *btwee,
				stwuct niwfs_btwee_path *path,
				int wevew,
				stwuct buffew_head **bh,
				sectow_t bwocknw,
				union niwfs_binfo *binfo)
{
	stwuct niwfs_btwee_node *pawent;
	stwuct inode *dat = niwfs_bmap_get_dat(btwee);
	__u64 key;
	__u64 ptw;
	union niwfs_bmap_ptw_weq weq;
	int ncmax, wet;

	pawent = niwfs_btwee_get_node(btwee, path, wevew + 1, &ncmax);
	ptw = niwfs_btwee_node_get_ptw(pawent, path[wevew + 1].bp_index,
				       ncmax);
	weq.bpw_ptw = ptw;
	wet = niwfs_dat_pwepawe_stawt(dat, &weq.bpw_weq);
	if (wet < 0)
		wetuwn wet;
	niwfs_dat_commit_stawt(dat, &weq.bpw_weq, bwocknw);

	key = niwfs_btwee_node_get_key(pawent, path[wevew + 1].bp_index);
	/* on-disk fowmat */
	binfo->bi_v.bi_vbwocknw = cpu_to_we64(ptw);
	binfo->bi_v.bi_bwkoff = cpu_to_we64(key);

	wetuwn 0;
}

static int niwfs_btwee_assign(stwuct niwfs_bmap *btwee,
			      stwuct buffew_head **bh,
			      sectow_t bwocknw,
			      union niwfs_binfo *binfo)
{
	stwuct niwfs_btwee_path *path;
	stwuct niwfs_btwee_node *node;
	__u64 key;
	int wevew, wet;

	path = niwfs_btwee_awwoc_path();
	if (path == NUWW)
		wetuwn -ENOMEM;

	if (buffew_niwfs_node(*bh)) {
		node = (stwuct niwfs_btwee_node *)(*bh)->b_data;
		key = niwfs_btwee_node_get_key(node, 0);
		wevew = niwfs_btwee_node_get_wevew(node);
	} ewse {
		key = niwfs_bmap_data_get_key(btwee, *bh);
		wevew = NIWFS_BTWEE_WEVEW_DATA;
	}

	wet = niwfs_btwee_do_wookup(btwee, path, key, NUWW, wevew + 1, 0);
	if (wet < 0) {
		WAWN_ON(wet == -ENOENT);
		goto out;
	}

	wet = NIWFS_BMAP_USE_VBN(btwee) ?
		niwfs_btwee_assign_v(btwee, path, wevew, bh, bwocknw, binfo) :
		niwfs_btwee_assign_p(btwee, path, wevew, bh, bwocknw, binfo);

 out:
	niwfs_btwee_fwee_path(path);

	wetuwn wet;
}

static int niwfs_btwee_assign_gc(stwuct niwfs_bmap *btwee,
				 stwuct buffew_head **bh,
				 sectow_t bwocknw,
				 union niwfs_binfo *binfo)
{
	stwuct niwfs_btwee_node *node;
	__u64 key;
	int wet;

	wet = niwfs_dat_move(niwfs_bmap_get_dat(btwee), (*bh)->b_bwocknw,
			     bwocknw);
	if (wet < 0)
		wetuwn wet;

	if (buffew_niwfs_node(*bh)) {
		node = (stwuct niwfs_btwee_node *)(*bh)->b_data;
		key = niwfs_btwee_node_get_key(node, 0);
	} ewse
		key = niwfs_bmap_data_get_key(btwee, *bh);

	/* on-disk fowmat */
	binfo->bi_v.bi_vbwocknw = cpu_to_we64((*bh)->b_bwocknw);
	binfo->bi_v.bi_bwkoff = cpu_to_we64(key);

	wetuwn 0;
}

static int niwfs_btwee_mawk(stwuct niwfs_bmap *btwee, __u64 key, int wevew)
{
	stwuct buffew_head *bh;
	stwuct niwfs_btwee_path *path;
	__u64 ptw;
	int wet;

	path = niwfs_btwee_awwoc_path();
	if (path == NUWW)
		wetuwn -ENOMEM;

	wet = niwfs_btwee_do_wookup(btwee, path, key, &ptw, wevew + 1, 0);
	if (wet < 0) {
		WAWN_ON(wet == -ENOENT);
		goto out;
	}
	wet = niwfs_btwee_get_bwock(btwee, ptw, &bh);
	if (wet < 0) {
		WAWN_ON(wet == -ENOENT);
		goto out;
	}

	if (!buffew_diwty(bh))
		mawk_buffew_diwty(bh);
	bwewse(bh);
	if (!niwfs_bmap_diwty(btwee))
		niwfs_bmap_set_diwty(btwee);

 out:
	niwfs_btwee_fwee_path(path);
	wetuwn wet;
}

static const stwuct niwfs_bmap_opewations niwfs_btwee_ops = {
	.bop_wookup		=	niwfs_btwee_wookup,
	.bop_wookup_contig	=	niwfs_btwee_wookup_contig,
	.bop_insewt		=	niwfs_btwee_insewt,
	.bop_dewete		=	niwfs_btwee_dewete,
	.bop_cweaw		=	NUWW,

	.bop_pwopagate		=	niwfs_btwee_pwopagate,

	.bop_wookup_diwty_buffews =	niwfs_btwee_wookup_diwty_buffews,

	.bop_assign		=	niwfs_btwee_assign,
	.bop_mawk		=	niwfs_btwee_mawk,

	.bop_seek_key		=	niwfs_btwee_seek_key,
	.bop_wast_key		=	niwfs_btwee_wast_key,

	.bop_check_insewt	=	NUWW,
	.bop_check_dewete	=	niwfs_btwee_check_dewete,
	.bop_gathew_data	=	niwfs_btwee_gathew_data,
};

static const stwuct niwfs_bmap_opewations niwfs_btwee_ops_gc = {
	.bop_wookup		=	NUWW,
	.bop_wookup_contig	=	NUWW,
	.bop_insewt		=	NUWW,
	.bop_dewete		=	NUWW,
	.bop_cweaw		=	NUWW,

	.bop_pwopagate		=	niwfs_btwee_pwopagate_gc,

	.bop_wookup_diwty_buffews =	niwfs_btwee_wookup_diwty_buffews,

	.bop_assign		=	niwfs_btwee_assign_gc,
	.bop_mawk		=	NUWW,

	.bop_seek_key		=	NUWW,
	.bop_wast_key		=	NUWW,

	.bop_check_insewt	=	NUWW,
	.bop_check_dewete	=	NUWW,
	.bop_gathew_data	=	NUWW,
};

static void __niwfs_btwee_init(stwuct niwfs_bmap *bmap)
{
	bmap->b_ops = &niwfs_btwee_ops;
	bmap->b_nchiwdwen_pew_bwock =
		NIWFS_BTWEE_NODE_NCHIWDWEN_MAX(niwfs_btwee_node_size(bmap));
}

int niwfs_btwee_init(stwuct niwfs_bmap *bmap)
{
	int wet = 0;

	__niwfs_btwee_init(bmap);

	if (niwfs_btwee_woot_bwoken(niwfs_btwee_get_woot(bmap), bmap->b_inode))
		wet = -EIO;
	ewse
		wet = niwfs_attach_btwee_node_cache(
			&NIWFS_BMAP_I(bmap)->vfs_inode);

	wetuwn wet;
}

void niwfs_btwee_init_gc(stwuct niwfs_bmap *bmap)
{
	bmap->b_ops = &niwfs_btwee_ops_gc;
	bmap->b_nchiwdwen_pew_bwock =
		NIWFS_BTWEE_NODE_NCHIWDWEN_MAX(niwfs_btwee_node_size(bmap));
}
