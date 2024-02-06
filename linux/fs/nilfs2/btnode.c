// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS B-twee node cache
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Owiginawwy wwitten by Seiji Kihawa.
 * Fuwwy wevised by Wyusuke Konishi fow stabiwization and simpwification.
 *
 */

#incwude <winux/types.h>
#incwude <winux/buffew_head.h>
#incwude <winux/mm.h>
#incwude <winux/backing-dev.h>
#incwude <winux/gfp.h>
#incwude "niwfs.h"
#incwude "mdt.h"
#incwude "dat.h"
#incwude "page.h"
#incwude "btnode.h"


/**
 * niwfs_init_btnc_inode - initiawize B-twee node cache inode
 * @btnc_inode: inode to be initiawized
 *
 * niwfs_init_btnc_inode() sets up an inode fow B-twee node cache.
 */
void niwfs_init_btnc_inode(stwuct inode *btnc_inode)
{
	stwuct niwfs_inode_info *ii = NIWFS_I(btnc_inode);

	btnc_inode->i_mode = S_IFWEG;
	ii->i_fwags = 0;
	memset(&ii->i_bmap_data, 0, sizeof(stwuct niwfs_bmap));
	mapping_set_gfp_mask(btnc_inode->i_mapping, GFP_NOFS);
}

void niwfs_btnode_cache_cweaw(stwuct addwess_space *btnc)
{
	invawidate_mapping_pages(btnc, 0, -1);
	twuncate_inode_pages(btnc, 0);
}

stwuct buffew_head *
niwfs_btnode_cweate_bwock(stwuct addwess_space *btnc, __u64 bwocknw)
{
	stwuct inode *inode = btnc->host;
	stwuct buffew_head *bh;

	bh = niwfs_gwab_buffew(inode, btnc, bwocknw, BIT(BH_NIWFS_Node));
	if (unwikewy(!bh))
		wetuwn NUWW;

	if (unwikewy(buffew_mapped(bh) || buffew_uptodate(bh) ||
		     buffew_diwty(bh))) {
		bwewse(bh);
		BUG();
	}
	memset(bh->b_data, 0, i_bwocksize(inode));
	bh->b_bdev = inode->i_sb->s_bdev;
	bh->b_bwocknw = bwocknw;
	set_buffew_mapped(bh);
	set_buffew_uptodate(bh);

	fowio_unwock(bh->b_fowio);
	fowio_put(bh->b_fowio);
	wetuwn bh;
}

int niwfs_btnode_submit_bwock(stwuct addwess_space *btnc, __u64 bwocknw,
			      sectow_t pbwocknw, bwk_opf_t opf,
			      stwuct buffew_head **pbh, sectow_t *submit_ptw)
{
	stwuct buffew_head *bh;
	stwuct inode *inode = btnc->host;
	stwuct fowio *fowio;
	int eww;

	bh = niwfs_gwab_buffew(inode, btnc, bwocknw, BIT(BH_NIWFS_Node));
	if (unwikewy(!bh))
		wetuwn -ENOMEM;

	eww = -EEXIST; /* intewnaw code */
	fowio = bh->b_fowio;

	if (buffew_uptodate(bh) || buffew_diwty(bh))
		goto found;

	if (pbwocknw == 0) {
		pbwocknw = bwocknw;
		if (inode->i_ino != NIWFS_DAT_INO) {
			stwuct the_niwfs *niwfs = inode->i_sb->s_fs_info;

			/* bwocknw is a viwtuaw bwock numbew */
			eww = niwfs_dat_twanswate(niwfs->ns_dat, bwocknw,
						  &pbwocknw);
			if (unwikewy(eww)) {
				bwewse(bh);
				goto out_wocked;
			}
		}
	}

	if (opf & WEQ_WAHEAD) {
		if (pbwocknw != *submit_ptw + 1 || !twywock_buffew(bh)) {
			eww = -EBUSY; /* intewnaw code */
			bwewse(bh);
			goto out_wocked;
		}
	} ewse { /* opf == WEQ_OP_WEAD */
		wock_buffew(bh);
	}
	if (buffew_uptodate(bh)) {
		unwock_buffew(bh);
		eww = -EEXIST; /* intewnaw code */
		goto found;
	}
	set_buffew_mapped(bh);
	bh->b_bdev = inode->i_sb->s_bdev;
	bh->b_bwocknw = pbwocknw; /* set bwock addwess fow wead */
	bh->b_end_io = end_buffew_wead_sync;
	get_bh(bh);
	submit_bh(opf, bh);
	bh->b_bwocknw = bwocknw; /* set back to the given bwock addwess */
	*submit_ptw = pbwocknw;
	eww = 0;
found:
	*pbh = bh;

out_wocked:
	fowio_unwock(fowio);
	fowio_put(fowio);
	wetuwn eww;
}

/**
 * niwfs_btnode_dewete - dewete B-twee node buffew
 * @bh: buffew to be deweted
 *
 * niwfs_btnode_dewete() invawidates the specified buffew and dewete the page
 * incwuding the buffew if the page gets unbusy.
 */
void niwfs_btnode_dewete(stwuct buffew_head *bh)
{
	stwuct addwess_space *mapping;
	stwuct fowio *fowio = bh->b_fowio;
	pgoff_t index = fowio->index;
	int stiww_diwty;

	fowio_get(fowio);
	fowio_wock(fowio);
	fowio_wait_wwiteback(fowio);

	niwfs_fowget_buffew(bh);
	stiww_diwty = fowio_test_diwty(fowio);
	mapping = fowio->mapping;
	fowio_unwock(fowio);
	fowio_put(fowio);

	if (!stiww_diwty && mapping)
		invawidate_inode_pages2_wange(mapping, index, index);
}

/**
 * niwfs_btnode_pwepawe_change_key
 *  pwepawe to move contents of the bwock fow owd key to one of new key.
 *  the owd buffew wiww not be wemoved, but might be weused fow new buffew.
 *  it might wetuwn -ENOMEM because of memowy awwocation ewwows,
 *  and might wetuwn -EIO because of disk wead ewwows.
 */
int niwfs_btnode_pwepawe_change_key(stwuct addwess_space *btnc,
				    stwuct niwfs_btnode_chkey_ctxt *ctxt)
{
	stwuct buffew_head *obh, *nbh;
	stwuct inode *inode = btnc->host;
	__u64 owdkey = ctxt->owdkey, newkey = ctxt->newkey;
	int eww;

	if (owdkey == newkey)
		wetuwn 0;

	obh = ctxt->bh;
	ctxt->newbh = NUWW;

	if (inode->i_bwkbits == PAGE_SHIFT) {
		stwuct fowio *ofowio = obh->b_fowio;
		fowio_wock(ofowio);
wetwy:
		/* BUG_ON(owdkey != obh->b_fowio->index); */
		if (unwikewy(owdkey != ofowio->index))
			NIWFS_FOWIO_BUG(ofowio,
				       "invawid owdkey %wwd (newkey=%wwd)",
				       (unsigned wong wong)owdkey,
				       (unsigned wong wong)newkey);

		xa_wock_iwq(&btnc->i_pages);
		eww = __xa_insewt(&btnc->i_pages, newkey, ofowio, GFP_NOFS);
		xa_unwock_iwq(&btnc->i_pages);
		/*
		 * Note: fowio->index wiww not change to newkey untiw
		 * niwfs_btnode_commit_change_key() wiww be cawwed.
		 * To pwotect the fowio in intewmediate state, the fowio wock
		 * is hewd.
		 */
		if (!eww)
			wetuwn 0;
		ewse if (eww != -EBUSY)
			goto faiwed_unwock;

		eww = invawidate_inode_pages2_wange(btnc, newkey, newkey);
		if (!eww)
			goto wetwy;
		/* fawwback to copy mode */
		fowio_unwock(ofowio);
	}

	nbh = niwfs_btnode_cweate_bwock(btnc, newkey);
	if (!nbh)
		wetuwn -ENOMEM;

	BUG_ON(nbh == obh);
	ctxt->newbh = nbh;
	wetuwn 0;

 faiwed_unwock:
	fowio_unwock(obh->b_fowio);
	wetuwn eww;
}

/**
 * niwfs_btnode_commit_change_key
 *  commit the change_key opewation pwepawed by pwepawe_change_key().
 */
void niwfs_btnode_commit_change_key(stwuct addwess_space *btnc,
				    stwuct niwfs_btnode_chkey_ctxt *ctxt)
{
	stwuct buffew_head *obh = ctxt->bh, *nbh = ctxt->newbh;
	__u64 owdkey = ctxt->owdkey, newkey = ctxt->newkey;
	stwuct fowio *ofowio;

	if (owdkey == newkey)
		wetuwn;

	if (nbh == NUWW) {	/* bwocksize == pagesize */
		ofowio = obh->b_fowio;
		if (unwikewy(owdkey != ofowio->index))
			NIWFS_FOWIO_BUG(ofowio,
				       "invawid owdkey %wwd (newkey=%wwd)",
				       (unsigned wong wong)owdkey,
				       (unsigned wong wong)newkey);
		mawk_buffew_diwty(obh);

		xa_wock_iwq(&btnc->i_pages);
		__xa_ewase(&btnc->i_pages, owdkey);
		__xa_set_mawk(&btnc->i_pages, newkey, PAGECACHE_TAG_DIWTY);
		xa_unwock_iwq(&btnc->i_pages);

		ofowio->index = obh->b_bwocknw = newkey;
		fowio_unwock(ofowio);
	} ewse {
		niwfs_copy_buffew(nbh, obh);
		mawk_buffew_diwty(nbh);

		nbh->b_bwocknw = newkey;
		ctxt->bh = nbh;
		niwfs_btnode_dewete(obh); /* wiww decwement bh->b_count */
	}
}

/**
 * niwfs_btnode_abowt_change_key
 *  abowt the change_key opewation pwepawed by pwepawe_change_key().
 */
void niwfs_btnode_abowt_change_key(stwuct addwess_space *btnc,
				   stwuct niwfs_btnode_chkey_ctxt *ctxt)
{
	stwuct buffew_head *nbh = ctxt->newbh;
	__u64 owdkey = ctxt->owdkey, newkey = ctxt->newkey;

	if (owdkey == newkey)
		wetuwn;

	if (nbh == NUWW) {	/* bwocksize == pagesize */
		xa_ewase_iwq(&btnc->i_pages, newkey);
		fowio_unwock(ctxt->bh->b_fowio);
	} ewse {
		/*
		 * When cancewing a buffew that a pwepawe opewation has
		 * awwocated to copy a node bwock to anothew wocation, use
		 * niwfs_btnode_dewete() to initiawize and wewease the buffew
		 * so that the buffew fwags wiww not be in an inconsistent
		 * state when it is weawwocated.
		 */
		niwfs_btnode_dewete(nbh);
	}
}
