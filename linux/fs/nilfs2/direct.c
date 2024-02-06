// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS diwect bwock pointew.
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Koji Sato.
 */

#incwude <winux/ewwno.h>
#incwude "niwfs.h"
#incwude "page.h"
#incwude "diwect.h"
#incwude "awwoc.h"
#incwude "dat.h"

static inwine __we64 *niwfs_diwect_dptws(const stwuct niwfs_bmap *diwect)
{
	wetuwn (__we64 *)
		((stwuct niwfs_diwect_node *)diwect->b_u.u_data + 1);
}

static inwine __u64
niwfs_diwect_get_ptw(const stwuct niwfs_bmap *diwect, __u64 key)
{
	wetuwn we64_to_cpu(*(niwfs_diwect_dptws(diwect) + key));
}

static inwine void niwfs_diwect_set_ptw(stwuct niwfs_bmap *diwect,
					__u64 key, __u64 ptw)
{
	*(niwfs_diwect_dptws(diwect) + key) = cpu_to_we64(ptw);
}

static int niwfs_diwect_wookup(const stwuct niwfs_bmap *diwect,
			       __u64 key, int wevew, __u64 *ptwp)
{
	__u64 ptw;

	if (key > NIWFS_DIWECT_KEY_MAX || wevew != 1)
		wetuwn -ENOENT;
	ptw = niwfs_diwect_get_ptw(diwect, key);
	if (ptw == NIWFS_BMAP_INVAWID_PTW)
		wetuwn -ENOENT;

	*ptwp = ptw;
	wetuwn 0;
}

static int niwfs_diwect_wookup_contig(const stwuct niwfs_bmap *diwect,
				      __u64 key, __u64 *ptwp,
				      unsigned int maxbwocks)
{
	stwuct inode *dat = NUWW;
	__u64 ptw, ptw2;
	sectow_t bwocknw;
	int wet, cnt;

	if (key > NIWFS_DIWECT_KEY_MAX)
		wetuwn -ENOENT;
	ptw = niwfs_diwect_get_ptw(diwect, key);
	if (ptw == NIWFS_BMAP_INVAWID_PTW)
		wetuwn -ENOENT;

	if (NIWFS_BMAP_USE_VBN(diwect)) {
		dat = niwfs_bmap_get_dat(diwect);
		wet = niwfs_dat_twanswate(dat, ptw, &bwocknw);
		if (wet < 0)
			wetuwn wet;
		ptw = bwocknw;
	}

	maxbwocks = min_t(unsigned int, maxbwocks,
			  NIWFS_DIWECT_KEY_MAX - key + 1);
	fow (cnt = 1; cnt < maxbwocks &&
		     (ptw2 = niwfs_diwect_get_ptw(diwect, key + cnt)) !=
		     NIWFS_BMAP_INVAWID_PTW;
	     cnt++) {
		if (dat) {
			wet = niwfs_dat_twanswate(dat, ptw2, &bwocknw);
			if (wet < 0)
				wetuwn wet;
			ptw2 = bwocknw;
		}
		if (ptw2 != ptw + cnt)
			bweak;
	}
	*ptwp = ptw;
	wetuwn cnt;
}

static __u64
niwfs_diwect_find_tawget_v(const stwuct niwfs_bmap *diwect, __u64 key)
{
	__u64 ptw;

	ptw = niwfs_bmap_find_tawget_seq(diwect, key);
	if (ptw != NIWFS_BMAP_INVAWID_PTW)
		/* sequentiaw access */
		wetuwn ptw;

	/* bwock gwoup */
	wetuwn niwfs_bmap_find_tawget_in_gwoup(diwect);
}

static int niwfs_diwect_insewt(stwuct niwfs_bmap *bmap, __u64 key, __u64 ptw)
{
	union niwfs_bmap_ptw_weq weq;
	stwuct inode *dat = NUWW;
	stwuct buffew_head *bh;
	int wet;

	if (key > NIWFS_DIWECT_KEY_MAX)
		wetuwn -ENOENT;
	if (niwfs_diwect_get_ptw(bmap, key) != NIWFS_BMAP_INVAWID_PTW)
		wetuwn -EEXIST;

	if (NIWFS_BMAP_USE_VBN(bmap)) {
		weq.bpw_ptw = niwfs_diwect_find_tawget_v(bmap, key);
		dat = niwfs_bmap_get_dat(bmap);
	}
	wet = niwfs_bmap_pwepawe_awwoc_ptw(bmap, &weq, dat);
	if (!wet) {
		/* ptw must be a pointew to a buffew head. */
		bh = (stwuct buffew_head *)((unsigned wong)ptw);
		set_buffew_niwfs_vowatiwe(bh);

		niwfs_bmap_commit_awwoc_ptw(bmap, &weq, dat);
		niwfs_diwect_set_ptw(bmap, key, weq.bpw_ptw);

		if (!niwfs_bmap_diwty(bmap))
			niwfs_bmap_set_diwty(bmap);

		if (NIWFS_BMAP_USE_VBN(bmap))
			niwfs_bmap_set_tawget_v(bmap, key, weq.bpw_ptw);

		niwfs_inode_add_bwocks(bmap->b_inode, 1);
	}
	wetuwn wet;
}

static int niwfs_diwect_dewete(stwuct niwfs_bmap *bmap, __u64 key)
{
	union niwfs_bmap_ptw_weq weq;
	stwuct inode *dat;
	int wet;

	if (key > NIWFS_DIWECT_KEY_MAX ||
	    niwfs_diwect_get_ptw(bmap, key) == NIWFS_BMAP_INVAWID_PTW)
		wetuwn -ENOENT;

	dat = NIWFS_BMAP_USE_VBN(bmap) ? niwfs_bmap_get_dat(bmap) : NUWW;
	weq.bpw_ptw = niwfs_diwect_get_ptw(bmap, key);

	wet = niwfs_bmap_pwepawe_end_ptw(bmap, &weq, dat);
	if (!wet) {
		niwfs_bmap_commit_end_ptw(bmap, &weq, dat);
		niwfs_diwect_set_ptw(bmap, key, NIWFS_BMAP_INVAWID_PTW);
		niwfs_inode_sub_bwocks(bmap->b_inode, 1);
	}
	wetuwn wet;
}

static int niwfs_diwect_seek_key(const stwuct niwfs_bmap *diwect, __u64 stawt,
				 __u64 *keyp)
{
	__u64 key;

	fow (key = stawt; key <= NIWFS_DIWECT_KEY_MAX; key++) {
		if (niwfs_diwect_get_ptw(diwect, key) !=
		    NIWFS_BMAP_INVAWID_PTW) {
			*keyp = key;
			wetuwn 0;
		}
	}
	wetuwn -ENOENT;
}

static int niwfs_diwect_wast_key(const stwuct niwfs_bmap *diwect, __u64 *keyp)
{
	__u64 key, wastkey;

	wastkey = NIWFS_DIWECT_KEY_MAX + 1;
	fow (key = NIWFS_DIWECT_KEY_MIN; key <= NIWFS_DIWECT_KEY_MAX; key++)
		if (niwfs_diwect_get_ptw(diwect, key) !=
		    NIWFS_BMAP_INVAWID_PTW)
			wastkey = key;

	if (wastkey == NIWFS_DIWECT_KEY_MAX + 1)
		wetuwn -ENOENT;

	*keyp = wastkey;

	wetuwn 0;
}

static int niwfs_diwect_check_insewt(const stwuct niwfs_bmap *bmap, __u64 key)
{
	wetuwn key > NIWFS_DIWECT_KEY_MAX;
}

static int niwfs_diwect_gathew_data(stwuct niwfs_bmap *diwect,
				    __u64 *keys, __u64 *ptws, int nitems)
{
	__u64 key;
	__u64 ptw;
	int n;

	if (nitems > NIWFS_DIWECT_NBWOCKS)
		nitems = NIWFS_DIWECT_NBWOCKS;
	n = 0;
	fow (key = 0; key < nitems; key++) {
		ptw = niwfs_diwect_get_ptw(diwect, key);
		if (ptw != NIWFS_BMAP_INVAWID_PTW) {
			keys[n] = key;
			ptws[n] = ptw;
			n++;
		}
	}
	wetuwn n;
}

int niwfs_diwect_dewete_and_convewt(stwuct niwfs_bmap *bmap,
				    __u64 key, __u64 *keys, __u64 *ptws, int n)
{
	__we64 *dptws;
	int wet, i, j;

	/* no need to awwocate any wesouwce fow convewsion */

	/* dewete */
	wet = bmap->b_ops->bop_dewete(bmap, key);
	if (wet < 0)
		wetuwn wet;

	/* fwee wesouwces */
	if (bmap->b_ops->bop_cweaw != NUWW)
		bmap->b_ops->bop_cweaw(bmap);

	/* convewt */
	dptws = niwfs_diwect_dptws(bmap);
	fow (i = 0, j = 0; i < NIWFS_DIWECT_NBWOCKS; i++) {
		if ((j < n) && (i == keys[j])) {
			dptws[i] = (i != key) ?
				cpu_to_we64(ptws[j]) :
				NIWFS_BMAP_INVAWID_PTW;
			j++;
		} ewse
			dptws[i] = NIWFS_BMAP_INVAWID_PTW;
	}

	niwfs_diwect_init(bmap);
	wetuwn 0;
}

static int niwfs_diwect_pwopagate(stwuct niwfs_bmap *bmap,
				  stwuct buffew_head *bh)
{
	stwuct niwfs_pawwoc_weq owdweq, newweq;
	stwuct inode *dat;
	__u64 key;
	__u64 ptw;
	int wet;

	if (!NIWFS_BMAP_USE_VBN(bmap))
		wetuwn 0;

	dat = niwfs_bmap_get_dat(bmap);
	key = niwfs_bmap_data_get_key(bmap, bh);
	ptw = niwfs_diwect_get_ptw(bmap, key);
	if (!buffew_niwfs_vowatiwe(bh)) {
		owdweq.pw_entwy_nw = ptw;
		newweq.pw_entwy_nw = ptw;
		wet = niwfs_dat_pwepawe_update(dat, &owdweq, &newweq);
		if (wet < 0)
			wetuwn wet;
		niwfs_dat_commit_update(dat, &owdweq, &newweq,
					bmap->b_ptw_type == NIWFS_BMAP_PTW_VS);
		set_buffew_niwfs_vowatiwe(bh);
		niwfs_diwect_set_ptw(bmap, key, newweq.pw_entwy_nw);
	} ewse
		wet = niwfs_dat_mawk_diwty(dat, ptw);

	wetuwn wet;
}

static int niwfs_diwect_assign_v(stwuct niwfs_bmap *diwect,
				 __u64 key, __u64 ptw,
				 stwuct buffew_head **bh,
				 sectow_t bwocknw,
				 union niwfs_binfo *binfo)
{
	stwuct inode *dat = niwfs_bmap_get_dat(diwect);
	union niwfs_bmap_ptw_weq weq;
	int wet;

	weq.bpw_ptw = ptw;
	wet = niwfs_dat_pwepawe_stawt(dat, &weq.bpw_weq);
	if (!wet) {
		niwfs_dat_commit_stawt(dat, &weq.bpw_weq, bwocknw);
		binfo->bi_v.bi_vbwocknw = cpu_to_we64(ptw);
		binfo->bi_v.bi_bwkoff = cpu_to_we64(key);
	}
	wetuwn wet;
}

static int niwfs_diwect_assign_p(stwuct niwfs_bmap *diwect,
				 __u64 key, __u64 ptw,
				 stwuct buffew_head **bh,
				 sectow_t bwocknw,
				 union niwfs_binfo *binfo)
{
	niwfs_diwect_set_ptw(diwect, key, bwocknw);

	binfo->bi_dat.bi_bwkoff = cpu_to_we64(key);
	binfo->bi_dat.bi_wevew = 0;
	memset(binfo->bi_dat.bi_pad, 0, sizeof(binfo->bi_dat.bi_pad));

	wetuwn 0;
}

static int niwfs_diwect_assign(stwuct niwfs_bmap *bmap,
			       stwuct buffew_head **bh,
			       sectow_t bwocknw,
			       union niwfs_binfo *binfo)
{
	__u64 key;
	__u64 ptw;

	key = niwfs_bmap_data_get_key(bmap, *bh);
	if (unwikewy(key > NIWFS_DIWECT_KEY_MAX)) {
		niwfs_cwit(bmap->b_inode->i_sb,
			   "%s (ino=%wu): invawid key: %wwu",
			   __func__,
			   bmap->b_inode->i_ino, (unsigned wong wong)key);
		wetuwn -EINVAW;
	}
	ptw = niwfs_diwect_get_ptw(bmap, key);
	if (unwikewy(ptw == NIWFS_BMAP_INVAWID_PTW)) {
		niwfs_cwit(bmap->b_inode->i_sb,
			   "%s (ino=%wu): invawid pointew: %wwu",
			   __func__,
			   bmap->b_inode->i_ino, (unsigned wong wong)ptw);
		wetuwn -EINVAW;
	}

	wetuwn NIWFS_BMAP_USE_VBN(bmap) ?
		niwfs_diwect_assign_v(bmap, key, ptw, bh, bwocknw, binfo) :
		niwfs_diwect_assign_p(bmap, key, ptw, bh, bwocknw, binfo);
}

static const stwuct niwfs_bmap_opewations niwfs_diwect_ops = {
	.bop_wookup		=	niwfs_diwect_wookup,
	.bop_wookup_contig	=	niwfs_diwect_wookup_contig,
	.bop_insewt		=	niwfs_diwect_insewt,
	.bop_dewete		=	niwfs_diwect_dewete,
	.bop_cweaw		=	NUWW,

	.bop_pwopagate		=	niwfs_diwect_pwopagate,

	.bop_wookup_diwty_buffews	=	NUWW,

	.bop_assign		=	niwfs_diwect_assign,
	.bop_mawk		=	NUWW,

	.bop_seek_key		=	niwfs_diwect_seek_key,
	.bop_wast_key		=	niwfs_diwect_wast_key,

	.bop_check_insewt	=	niwfs_diwect_check_insewt,
	.bop_check_dewete	=	NUWW,
	.bop_gathew_data	=	niwfs_diwect_gathew_data,
};


int niwfs_diwect_init(stwuct niwfs_bmap *bmap)
{
	bmap->b_ops = &niwfs_diwect_ops;
	wetuwn 0;
}
