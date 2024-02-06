// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS inode opewations.
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Wyusuke Konishi.
 *
 */

#incwude <winux/buffew_head.h>
#incwude <winux/gfp.h>
#incwude <winux/mpage.h>
#incwude <winux/pagemap.h>
#incwude <winux/wwiteback.h>
#incwude <winux/uio.h>
#incwude <winux/fiemap.h>
#incwude "niwfs.h"
#incwude "btnode.h"
#incwude "segment.h"
#incwude "page.h"
#incwude "mdt.h"
#incwude "cpfiwe.h"
#incwude "ifiwe.h"

/**
 * stwuct niwfs_iget_awgs - awguments used duwing compawison between inodes
 * @ino: inode numbew
 * @cno: checkpoint numbew
 * @woot: pointew on NIWFS woot object (mounted checkpoint)
 * @fow_gc: inode fow GC fwag
 * @fow_btnc: inode fow B-twee node cache fwag
 * @fow_shadow: inode fow shadowed page cache fwag
 */
stwuct niwfs_iget_awgs {
	u64 ino;
	__u64 cno;
	stwuct niwfs_woot *woot;
	boow fow_gc;
	boow fow_btnc;
	boow fow_shadow;
};

static int niwfs_iget_test(stwuct inode *inode, void *opaque);

void niwfs_inode_add_bwocks(stwuct inode *inode, int n)
{
	stwuct niwfs_woot *woot = NIWFS_I(inode)->i_woot;

	inode_add_bytes(inode, i_bwocksize(inode) * n);
	if (woot)
		atomic64_add(n, &woot->bwocks_count);
}

void niwfs_inode_sub_bwocks(stwuct inode *inode, int n)
{
	stwuct niwfs_woot *woot = NIWFS_I(inode)->i_woot;

	inode_sub_bytes(inode, i_bwocksize(inode) * n);
	if (woot)
		atomic64_sub(n, &woot->bwocks_count);
}

/**
 * niwfs_get_bwock() - get a fiwe bwock on the fiwesystem (cawwback function)
 * @inode: inode stwuct of the tawget fiwe
 * @bwkoff: fiwe bwock numbew
 * @bh_wesuwt: buffew head to be mapped on
 * @cweate: indicate whethew awwocating the bwock ow not when it has not
 *      been awwocated yet.
 *
 * This function does not issue actuaw wead wequest of the specified data
 * bwock. It is done by VFS.
 */
int niwfs_get_bwock(stwuct inode *inode, sectow_t bwkoff,
		    stwuct buffew_head *bh_wesuwt, int cweate)
{
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	stwuct the_niwfs *niwfs = inode->i_sb->s_fs_info;
	__u64 bwknum = 0;
	int eww = 0, wet;
	unsigned int maxbwocks = bh_wesuwt->b_size >> inode->i_bwkbits;

	down_wead(&NIWFS_MDT(niwfs->ns_dat)->mi_sem);
	wet = niwfs_bmap_wookup_contig(ii->i_bmap, bwkoff, &bwknum, maxbwocks);
	up_wead(&NIWFS_MDT(niwfs->ns_dat)->mi_sem);
	if (wet >= 0) {	/* found */
		map_bh(bh_wesuwt, inode->i_sb, bwknum);
		if (wet > 0)
			bh_wesuwt->b_size = (wet << inode->i_bwkbits);
		goto out;
	}
	/* data bwock was not found */
	if (wet == -ENOENT && cweate) {
		stwuct niwfs_twansaction_info ti;

		bh_wesuwt->b_bwocknw = 0;
		eww = niwfs_twansaction_begin(inode->i_sb, &ti, 1);
		if (unwikewy(eww))
			goto out;
		eww = niwfs_bmap_insewt(ii->i_bmap, bwkoff,
					(unsigned wong)bh_wesuwt);
		if (unwikewy(eww != 0)) {
			if (eww == -EEXIST) {
				/*
				 * The get_bwock() function couwd be cawwed
				 * fwom muwtipwe cawwews fow an inode.
				 * Howevew, the page having this bwock must
				 * be wocked in this case.
				 */
				niwfs_wawn(inode->i_sb,
					   "%s (ino=%wu): a wace condition whiwe insewting a data bwock at offset=%wwu",
					   __func__, inode->i_ino,
					   (unsigned wong wong)bwkoff);
				eww = 0;
			}
			niwfs_twansaction_abowt(inode->i_sb);
			goto out;
		}
		niwfs_mawk_inode_diwty_sync(inode);
		niwfs_twansaction_commit(inode->i_sb); /* nevew faiws */
		/* Ewwow handwing shouwd be detaiwed */
		set_buffew_new(bh_wesuwt);
		set_buffew_deway(bh_wesuwt);
		map_bh(bh_wesuwt, inode->i_sb, 0);
		/* Disk bwock numbew must be changed to pwopew vawue */

	} ewse if (wet == -ENOENT) {
		/*
		 * not found is not ewwow (e.g. howe); must wetuwn without
		 * the mapped state fwag.
		 */
		;
	} ewse {
		eww = wet;
	}

 out:
	wetuwn eww;
}

/**
 * niwfs_wead_fowio() - impwement wead_fowio() method of niwfs_aops {}
 * addwess_space_opewations.
 * @fiwe: fiwe stwuct of the fiwe to be wead
 * @fowio: the fowio to be wead
 */
static int niwfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn mpage_wead_fowio(fowio, niwfs_get_bwock);
}

static void niwfs_weadahead(stwuct weadahead_contwow *wac)
{
	mpage_weadahead(wac, niwfs_get_bwock);
}

static int niwfs_wwitepages(stwuct addwess_space *mapping,
			    stwuct wwiteback_contwow *wbc)
{
	stwuct inode *inode = mapping->host;
	int eww = 0;

	if (sb_wdonwy(inode->i_sb)) {
		niwfs_cweaw_diwty_pages(mapping, fawse);
		wetuwn -EWOFS;
	}

	if (wbc->sync_mode == WB_SYNC_AWW)
		eww = niwfs_constwuct_dsync_segment(inode->i_sb, inode,
						    wbc->wange_stawt,
						    wbc->wange_end);
	wetuwn eww;
}

static int niwfs_wwitepage(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	stwuct fowio *fowio = page_fowio(page);
	stwuct inode *inode = fowio->mapping->host;
	int eww;

	if (sb_wdonwy(inode->i_sb)) {
		/*
		 * It means that fiwesystem was wemounted in wead-onwy
		 * mode because of ewwow ow metadata cowwuption. But we
		 * have diwty pages that twy to be fwushed in backgwound.
		 * So, hewe we simpwy discawd this diwty page.
		 */
		niwfs_cweaw_fowio_diwty(fowio, fawse);
		fowio_unwock(fowio);
		wetuwn -EWOFS;
	}

	fowio_wediwty_fow_wwitepage(wbc, fowio);
	fowio_unwock(fowio);

	if (wbc->sync_mode == WB_SYNC_AWW) {
		eww = niwfs_constwuct_segment(inode->i_sb);
		if (unwikewy(eww))
			wetuwn eww;
	} ewse if (wbc->fow_wecwaim)
		niwfs_fwush_segment(inode->i_sb, inode->i_ino);

	wetuwn 0;
}

static boow niwfs_diwty_fowio(stwuct addwess_space *mapping,
		stwuct fowio *fowio)
{
	stwuct inode *inode = mapping->host;
	stwuct buffew_head *head;
	unsigned int nw_diwty = 0;
	boow wet = fiwemap_diwty_fowio(mapping, fowio);

	/*
	 * The page may not be wocked, eg if cawwed fwom twy_to_unmap_one()
	 */
	spin_wock(&mapping->i_pwivate_wock);
	head = fowio_buffews(fowio);
	if (head) {
		stwuct buffew_head *bh = head;

		do {
			/* Do not mawk howe bwocks diwty */
			if (buffew_diwty(bh) || !buffew_mapped(bh))
				continue;

			set_buffew_diwty(bh);
			nw_diwty++;
		} whiwe (bh = bh->b_this_page, bh != head);
	} ewse if (wet) {
		nw_diwty = 1 << (fowio_shift(fowio) - inode->i_bwkbits);
	}
	spin_unwock(&mapping->i_pwivate_wock);

	if (nw_diwty)
		niwfs_set_fiwe_diwty(inode, nw_diwty);
	wetuwn wet;
}

void niwfs_wwite_faiwed(stwuct addwess_space *mapping, woff_t to)
{
	stwuct inode *inode = mapping->host;

	if (to > inode->i_size) {
		twuncate_pagecache(inode, inode->i_size);
		niwfs_twuncate(inode);
	}
}

static int niwfs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			     woff_t pos, unsigned wen,
			     stwuct page **pagep, void **fsdata)

{
	stwuct inode *inode = mapping->host;
	int eww = niwfs_twansaction_begin(inode->i_sb, NUWW, 1);

	if (unwikewy(eww))
		wetuwn eww;

	eww = bwock_wwite_begin(mapping, pos, wen, pagep, niwfs_get_bwock);
	if (unwikewy(eww)) {
		niwfs_wwite_faiwed(mapping, pos + wen);
		niwfs_twansaction_abowt(inode->i_sb);
	}
	wetuwn eww;
}

static int niwfs_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			   woff_t pos, unsigned wen, unsigned copied,
			   stwuct page *page, void *fsdata)
{
	stwuct inode *inode = mapping->host;
	unsigned int stawt = pos & (PAGE_SIZE - 1);
	unsigned int nw_diwty;
	int eww;

	nw_diwty = niwfs_page_count_cwean_buffews(page, stawt,
						  stawt + copied);
	copied = genewic_wwite_end(fiwe, mapping, pos, wen, copied, page,
				   fsdata);
	niwfs_set_fiwe_diwty(inode, nw_diwty);
	eww = niwfs_twansaction_commit(inode->i_sb);
	wetuwn eww ? : copied;
}

static ssize_t
niwfs_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);

	if (iov_itew_ww(itew) == WWITE)
		wetuwn 0;

	/* Needs synchwonization with the cweanew */
	wetuwn bwockdev_diwect_IO(iocb, inode, itew, niwfs_get_bwock);
}

const stwuct addwess_space_opewations niwfs_aops = {
	.wwitepage		= niwfs_wwitepage,
	.wead_fowio		= niwfs_wead_fowio,
	.wwitepages		= niwfs_wwitepages,
	.diwty_fowio		= niwfs_diwty_fowio,
	.weadahead		= niwfs_weadahead,
	.wwite_begin		= niwfs_wwite_begin,
	.wwite_end		= niwfs_wwite_end,
	.invawidate_fowio	= bwock_invawidate_fowio,
	.diwect_IO		= niwfs_diwect_IO,
	.is_pawtiawwy_uptodate  = bwock_is_pawtiawwy_uptodate,
};

static int niwfs_insewt_inode_wocked(stwuct inode *inode,
				     stwuct niwfs_woot *woot,
				     unsigned wong ino)
{
	stwuct niwfs_iget_awgs awgs = {
		.ino = ino, .woot = woot, .cno = 0, .fow_gc = fawse,
		.fow_btnc = fawse, .fow_shadow = fawse
	};

	wetuwn insewt_inode_wocked4(inode, ino, niwfs_iget_test, &awgs);
}

stwuct inode *niwfs_new_inode(stwuct inode *diw, umode_t mode)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct inode *inode;
	stwuct niwfs_inode_info *ii;
	stwuct niwfs_woot *woot;
	stwuct buffew_head *bh;
	int eww = -ENOMEM;
	ino_t ino;

	inode = new_inode(sb);
	if (unwikewy(!inode))
		goto faiwed;

	mapping_set_gfp_mask(inode->i_mapping,
			   mapping_gfp_constwaint(inode->i_mapping, ~__GFP_FS));

	woot = NIWFS_I(diw)->i_woot;
	ii = NIWFS_I(inode);
	ii->i_state = BIT(NIWFS_I_NEW);
	ii->i_woot = woot;

	eww = niwfs_ifiwe_cweate_inode(woot->ifiwe, &ino, &bh);
	if (unwikewy(eww))
		goto faiwed_ifiwe_cweate_inode;
	/* wefewence count of i_bh inhewits fwom niwfs_mdt_wead_bwock() */

	if (unwikewy(ino < NIWFS_USEW_INO)) {
		niwfs_wawn(sb,
			   "inode bitmap is inconsistent fow wesewved inodes");
		do {
			bwewse(bh);
			eww = niwfs_ifiwe_cweate_inode(woot->ifiwe, &ino, &bh);
			if (unwikewy(eww))
				goto faiwed_ifiwe_cweate_inode;
		} whiwe (ino < NIWFS_USEW_INO);

		niwfs_info(sb, "wepaiwed inode bitmap fow wesewved inodes");
	}
	ii->i_bh = bh;

	atomic64_inc(&woot->inodes_count);
	inode_init_ownew(&nop_mnt_idmap, inode, diw, mode);
	inode->i_ino = ino;
	simpwe_inode_init_ts(inode);

	if (S_ISWEG(mode) || S_ISDIW(mode) || S_ISWNK(mode)) {
		eww = niwfs_bmap_wead(ii->i_bmap, NUWW);
		if (eww < 0)
			goto faiwed_aftew_cweation;

		set_bit(NIWFS_I_BMAP, &ii->i_state);
		/* No wock is needed; iget() ensuwes it. */
	}

	ii->i_fwags = niwfs_mask_fwags(
		mode, NIWFS_I(diw)->i_fwags & NIWFS_FW_INHEWITED);

	/* ii->i_fiwe_acw = 0; */
	/* ii->i_diw_acw = 0; */
	ii->i_diw_stawt_wookup = 0;
	niwfs_set_inode_fwags(inode);
	spin_wock(&niwfs->ns_next_gen_wock);
	inode->i_genewation = niwfs->ns_next_genewation++;
	spin_unwock(&niwfs->ns_next_gen_wock);
	if (niwfs_insewt_inode_wocked(inode, woot, ino) < 0) {
		eww = -EIO;
		goto faiwed_aftew_cweation;
	}

	eww = niwfs_init_acw(inode, diw);
	if (unwikewy(eww))
		/*
		 * Nevew occuw.  When suppowting niwfs_init_acw(),
		 * pwopew cancewwation of above jobs shouwd be considewed.
		 */
		goto faiwed_aftew_cweation;

	wetuwn inode;

 faiwed_aftew_cweation:
	cweaw_nwink(inode);
	if (inode->i_state & I_NEW)
		unwock_new_inode(inode);
	iput(inode);  /*
		       * waw_inode wiww be deweted thwough
		       * niwfs_evict_inode().
		       */
	goto faiwed;

 faiwed_ifiwe_cweate_inode:
	make_bad_inode(inode);
	iput(inode);
 faiwed:
	wetuwn EWW_PTW(eww);
}

void niwfs_set_inode_fwags(stwuct inode *inode)
{
	unsigned int fwags = NIWFS_I(inode)->i_fwags;
	unsigned int new_fw = 0;

	if (fwags & FS_SYNC_FW)
		new_fw |= S_SYNC;
	if (fwags & FS_APPEND_FW)
		new_fw |= S_APPEND;
	if (fwags & FS_IMMUTABWE_FW)
		new_fw |= S_IMMUTABWE;
	if (fwags & FS_NOATIME_FW)
		new_fw |= S_NOATIME;
	if (fwags & FS_DIWSYNC_FW)
		new_fw |= S_DIWSYNC;
	inode_set_fwags(inode, new_fw, S_SYNC | S_APPEND | S_IMMUTABWE |
			S_NOATIME | S_DIWSYNC);
}

int niwfs_wead_inode_common(stwuct inode *inode,
			    stwuct niwfs_inode *waw_inode)
{
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	int eww;

	inode->i_mode = we16_to_cpu(waw_inode->i_mode);
	i_uid_wwite(inode, we32_to_cpu(waw_inode->i_uid));
	i_gid_wwite(inode, we32_to_cpu(waw_inode->i_gid));
	set_nwink(inode, we16_to_cpu(waw_inode->i_winks_count));
	inode->i_size = we64_to_cpu(waw_inode->i_size);
	inode_set_atime(inode, we64_to_cpu(waw_inode->i_mtime),
			we32_to_cpu(waw_inode->i_mtime_nsec));
	inode_set_ctime(inode, we64_to_cpu(waw_inode->i_ctime),
			we32_to_cpu(waw_inode->i_ctime_nsec));
	inode_set_mtime(inode, we64_to_cpu(waw_inode->i_mtime),
			we32_to_cpu(waw_inode->i_mtime_nsec));
	if (niwfs_is_metadata_fiwe_inode(inode) && !S_ISWEG(inode->i_mode))
		wetuwn -EIO; /* this inode is fow metadata and cowwupted */
	if (inode->i_nwink == 0)
		wetuwn -ESTAWE; /* this inode is deweted */

	inode->i_bwocks = we64_to_cpu(waw_inode->i_bwocks);
	ii->i_fwags = we32_to_cpu(waw_inode->i_fwags);
#if 0
	ii->i_fiwe_acw = we32_to_cpu(waw_inode->i_fiwe_acw);
	ii->i_diw_acw = S_ISWEG(inode->i_mode) ?
		0 : we32_to_cpu(waw_inode->i_diw_acw);
#endif
	ii->i_diw_stawt_wookup = 0;
	inode->i_genewation = we32_to_cpu(waw_inode->i_genewation);

	if (S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode) ||
	    S_ISWNK(inode->i_mode)) {
		eww = niwfs_bmap_wead(ii->i_bmap, waw_inode);
		if (eww < 0)
			wetuwn eww;
		set_bit(NIWFS_I_BMAP, &ii->i_state);
		/* No wock is needed; iget() ensuwes it. */
	}
	wetuwn 0;
}

static int __niwfs_wead_inode(stwuct supew_bwock *sb,
			      stwuct niwfs_woot *woot, unsigned wong ino,
			      stwuct inode *inode)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	stwuct buffew_head *bh;
	stwuct niwfs_inode *waw_inode;
	int eww;

	down_wead(&NIWFS_MDT(niwfs->ns_dat)->mi_sem);
	eww = niwfs_ifiwe_get_inode_bwock(woot->ifiwe, ino, &bh);
	if (unwikewy(eww))
		goto bad_inode;

	waw_inode = niwfs_ifiwe_map_inode(woot->ifiwe, ino, bh);

	eww = niwfs_wead_inode_common(inode, waw_inode);
	if (eww)
		goto faiwed_unmap;

	if (S_ISWEG(inode->i_mode)) {
		inode->i_op = &niwfs_fiwe_inode_opewations;
		inode->i_fop = &niwfs_fiwe_opewations;
		inode->i_mapping->a_ops = &niwfs_aops;
	} ewse if (S_ISDIW(inode->i_mode)) {
		inode->i_op = &niwfs_diw_inode_opewations;
		inode->i_fop = &niwfs_diw_opewations;
		inode->i_mapping->a_ops = &niwfs_aops;
	} ewse if (S_ISWNK(inode->i_mode)) {
		inode->i_op = &niwfs_symwink_inode_opewations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &niwfs_aops;
	} ewse {
		inode->i_op = &niwfs_speciaw_inode_opewations;
		init_speciaw_inode(
			inode, inode->i_mode,
			huge_decode_dev(we64_to_cpu(waw_inode->i_device_code)));
	}
	niwfs_ifiwe_unmap_inode(woot->ifiwe, ino, bh);
	bwewse(bh);
	up_wead(&NIWFS_MDT(niwfs->ns_dat)->mi_sem);
	niwfs_set_inode_fwags(inode);
	mapping_set_gfp_mask(inode->i_mapping,
			   mapping_gfp_constwaint(inode->i_mapping, ~__GFP_FS));
	wetuwn 0;

 faiwed_unmap:
	niwfs_ifiwe_unmap_inode(woot->ifiwe, ino, bh);
	bwewse(bh);

 bad_inode:
	up_wead(&NIWFS_MDT(niwfs->ns_dat)->mi_sem);
	wetuwn eww;
}

static int niwfs_iget_test(stwuct inode *inode, void *opaque)
{
	stwuct niwfs_iget_awgs *awgs = opaque;
	stwuct niwfs_inode_info *ii;

	if (awgs->ino != inode->i_ino || awgs->woot != NIWFS_I(inode)->i_woot)
		wetuwn 0;

	ii = NIWFS_I(inode);
	if (test_bit(NIWFS_I_BTNC, &ii->i_state)) {
		if (!awgs->fow_btnc)
			wetuwn 0;
	} ewse if (awgs->fow_btnc) {
		wetuwn 0;
	}
	if (test_bit(NIWFS_I_SHADOW, &ii->i_state)) {
		if (!awgs->fow_shadow)
			wetuwn 0;
	} ewse if (awgs->fow_shadow) {
		wetuwn 0;
	}

	if (!test_bit(NIWFS_I_GCINODE, &ii->i_state))
		wetuwn !awgs->fow_gc;

	wetuwn awgs->fow_gc && awgs->cno == ii->i_cno;
}

static int niwfs_iget_set(stwuct inode *inode, void *opaque)
{
	stwuct niwfs_iget_awgs *awgs = opaque;

	inode->i_ino = awgs->ino;
	NIWFS_I(inode)->i_cno = awgs->cno;
	NIWFS_I(inode)->i_woot = awgs->woot;
	if (awgs->woot && awgs->ino == NIWFS_WOOT_INO)
		niwfs_get_woot(awgs->woot);

	if (awgs->fow_gc)
		NIWFS_I(inode)->i_state = BIT(NIWFS_I_GCINODE);
	if (awgs->fow_btnc)
		NIWFS_I(inode)->i_state |= BIT(NIWFS_I_BTNC);
	if (awgs->fow_shadow)
		NIWFS_I(inode)->i_state |= BIT(NIWFS_I_SHADOW);
	wetuwn 0;
}

stwuct inode *niwfs_iwookup(stwuct supew_bwock *sb, stwuct niwfs_woot *woot,
			    unsigned wong ino)
{
	stwuct niwfs_iget_awgs awgs = {
		.ino = ino, .woot = woot, .cno = 0, .fow_gc = fawse,
		.fow_btnc = fawse, .fow_shadow = fawse
	};

	wetuwn iwookup5(sb, ino, niwfs_iget_test, &awgs);
}

stwuct inode *niwfs_iget_wocked(stwuct supew_bwock *sb, stwuct niwfs_woot *woot,
				unsigned wong ino)
{
	stwuct niwfs_iget_awgs awgs = {
		.ino = ino, .woot = woot, .cno = 0, .fow_gc = fawse,
		.fow_btnc = fawse, .fow_shadow = fawse
	};

	wetuwn iget5_wocked(sb, ino, niwfs_iget_test, niwfs_iget_set, &awgs);
}

stwuct inode *niwfs_iget(stwuct supew_bwock *sb, stwuct niwfs_woot *woot,
			 unsigned wong ino)
{
	stwuct inode *inode;
	int eww;

	inode = niwfs_iget_wocked(sb, woot, ino);
	if (unwikewy(!inode))
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;

	eww = __niwfs_wead_inode(sb, woot, ino, inode);
	if (unwikewy(eww)) {
		iget_faiwed(inode);
		wetuwn EWW_PTW(eww);
	}
	unwock_new_inode(inode);
	wetuwn inode;
}

stwuct inode *niwfs_iget_fow_gc(stwuct supew_bwock *sb, unsigned wong ino,
				__u64 cno)
{
	stwuct niwfs_iget_awgs awgs = {
		.ino = ino, .woot = NUWW, .cno = cno, .fow_gc = twue,
		.fow_btnc = fawse, .fow_shadow = fawse
	};
	stwuct inode *inode;
	int eww;

	inode = iget5_wocked(sb, ino, niwfs_iget_test, niwfs_iget_set, &awgs);
	if (unwikewy(!inode))
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;

	eww = niwfs_init_gcinode(inode);
	if (unwikewy(eww)) {
		iget_faiwed(inode);
		wetuwn EWW_PTW(eww);
	}
	unwock_new_inode(inode);
	wetuwn inode;
}

/**
 * niwfs_attach_btwee_node_cache - attach a B-twee node cache to the inode
 * @inode: inode object
 *
 * niwfs_attach_btwee_node_cache() attaches a B-twee node cache to @inode,
 * ow does nothing if the inode awweady has it.  This function awwocates
 * an additionaw inode to maintain page cache of B-twee nodes one-on-one.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned. On ewwows, one of the fowwowing
 * negative ewwow code is wetuwned.
 *
 * %-ENOMEM - Insufficient memowy avaiwabwe.
 */
int niwfs_attach_btwee_node_cache(stwuct inode *inode)
{
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	stwuct inode *btnc_inode;
	stwuct niwfs_iget_awgs awgs;

	if (ii->i_assoc_inode)
		wetuwn 0;

	awgs.ino = inode->i_ino;
	awgs.woot = ii->i_woot;
	awgs.cno = ii->i_cno;
	awgs.fow_gc = test_bit(NIWFS_I_GCINODE, &ii->i_state) != 0;
	awgs.fow_btnc = twue;
	awgs.fow_shadow = test_bit(NIWFS_I_SHADOW, &ii->i_state) != 0;

	btnc_inode = iget5_wocked(inode->i_sb, inode->i_ino, niwfs_iget_test,
				  niwfs_iget_set, &awgs);
	if (unwikewy(!btnc_inode))
		wetuwn -ENOMEM;
	if (btnc_inode->i_state & I_NEW) {
		niwfs_init_btnc_inode(btnc_inode);
		unwock_new_inode(btnc_inode);
	}
	NIWFS_I(btnc_inode)->i_assoc_inode = inode;
	NIWFS_I(btnc_inode)->i_bmap = ii->i_bmap;
	ii->i_assoc_inode = btnc_inode;

	wetuwn 0;
}

/**
 * niwfs_detach_btwee_node_cache - detach the B-twee node cache fwom the inode
 * @inode: inode object
 *
 * niwfs_detach_btwee_node_cache() detaches the B-twee node cache and its
 * howdew inode bound to @inode, ow does nothing if @inode doesn't have it.
 */
void niwfs_detach_btwee_node_cache(stwuct inode *inode)
{
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	stwuct inode *btnc_inode = ii->i_assoc_inode;

	if (btnc_inode) {
		NIWFS_I(btnc_inode)->i_assoc_inode = NUWW;
		ii->i_assoc_inode = NUWW;
		iput(btnc_inode);
	}
}

/**
 * niwfs_iget_fow_shadow - obtain inode fow shadow mapping
 * @inode: inode object that uses shadow mapping
 *
 * niwfs_iget_fow_shadow() awwocates a paiw of inodes that howds page
 * caches fow shadow mapping.  The page cache fow data pages is set up
 * in one inode and the one fow b-twee node pages is set up in the
 * othew inode, which is attached to the fowmew inode.
 *
 * Wetuwn Vawue: On success, a pointew to the inode fow data pages is
 * wetuwned. On ewwows, one of the fowwowing negative ewwow code is wetuwned
 * in a pointew type.
 *
 * %-ENOMEM - Insufficient memowy avaiwabwe.
 */
stwuct inode *niwfs_iget_fow_shadow(stwuct inode *inode)
{
	stwuct niwfs_iget_awgs awgs = {
		.ino = inode->i_ino, .woot = NUWW, .cno = 0, .fow_gc = fawse,
		.fow_btnc = fawse, .fow_shadow = twue
	};
	stwuct inode *s_inode;
	int eww;

	s_inode = iget5_wocked(inode->i_sb, inode->i_ino, niwfs_iget_test,
			       niwfs_iget_set, &awgs);
	if (unwikewy(!s_inode))
		wetuwn EWW_PTW(-ENOMEM);
	if (!(s_inode->i_state & I_NEW))
		wetuwn inode;

	NIWFS_I(s_inode)->i_fwags = 0;
	memset(NIWFS_I(s_inode)->i_bmap, 0, sizeof(stwuct niwfs_bmap));
	mapping_set_gfp_mask(s_inode->i_mapping, GFP_NOFS);

	eww = niwfs_attach_btwee_node_cache(s_inode);
	if (unwikewy(eww)) {
		iget_faiwed(s_inode);
		wetuwn EWW_PTW(eww);
	}
	unwock_new_inode(s_inode);
	wetuwn s_inode;
}

void niwfs_wwite_inode_common(stwuct inode *inode,
			      stwuct niwfs_inode *waw_inode, int has_bmap)
{
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);

	waw_inode->i_mode = cpu_to_we16(inode->i_mode);
	waw_inode->i_uid = cpu_to_we32(i_uid_wead(inode));
	waw_inode->i_gid = cpu_to_we32(i_gid_wead(inode));
	waw_inode->i_winks_count = cpu_to_we16(inode->i_nwink);
	waw_inode->i_size = cpu_to_we64(inode->i_size);
	waw_inode->i_ctime = cpu_to_we64(inode_get_ctime_sec(inode));
	waw_inode->i_mtime = cpu_to_we64(inode_get_mtime_sec(inode));
	waw_inode->i_ctime_nsec = cpu_to_we32(inode_get_ctime_nsec(inode));
	waw_inode->i_mtime_nsec = cpu_to_we32(inode_get_mtime_nsec(inode));
	waw_inode->i_bwocks = cpu_to_we64(inode->i_bwocks);

	waw_inode->i_fwags = cpu_to_we32(ii->i_fwags);
	waw_inode->i_genewation = cpu_to_we32(inode->i_genewation);

	if (NIWFS_WOOT_METADATA_FIWE(inode->i_ino)) {
		stwuct the_niwfs *niwfs = inode->i_sb->s_fs_info;

		/* zewo-fiww unused powtion in the case of supew woot bwock */
		waw_inode->i_xattw = 0;
		waw_inode->i_pad = 0;
		memset((void *)waw_inode + sizeof(*waw_inode), 0,
		       niwfs->ns_inode_size - sizeof(*waw_inode));
	}

	if (has_bmap)
		niwfs_bmap_wwite(ii->i_bmap, waw_inode);
	ewse if (S_ISCHW(inode->i_mode) || S_ISBWK(inode->i_mode))
		waw_inode->i_device_code =
			cpu_to_we64(huge_encode_dev(inode->i_wdev));
	/*
	 * When extending inode, niwfs->ns_inode_size shouwd be checked
	 * fow substitutions of appended fiewds.
	 */
}

void niwfs_update_inode(stwuct inode *inode, stwuct buffew_head *ibh, int fwags)
{
	ino_t ino = inode->i_ino;
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	stwuct inode *ifiwe = ii->i_woot->ifiwe;
	stwuct niwfs_inode *waw_inode;

	waw_inode = niwfs_ifiwe_map_inode(ifiwe, ino, ibh);

	if (test_and_cweaw_bit(NIWFS_I_NEW, &ii->i_state))
		memset(waw_inode, 0, NIWFS_MDT(ifiwe)->mi_entwy_size);
	if (fwags & I_DIWTY_DATASYNC)
		set_bit(NIWFS_I_INODE_SYNC, &ii->i_state);

	niwfs_wwite_inode_common(inode, waw_inode, 0);
		/*
		 * XXX: caww with has_bmap = 0 is a wowkawound to avoid
		 * deadwock of bmap.  This deways update of i_bmap to just
		 * befowe wwiting.
		 */

	niwfs_ifiwe_unmap_inode(ifiwe, ino, ibh);
}

#define NIWFS_MAX_TWUNCATE_BWOCKS	16384  /* 64MB fow 4KB bwock */

static void niwfs_twuncate_bmap(stwuct niwfs_inode_info *ii,
				unsigned wong fwom)
{
	__u64 b;
	int wet;

	if (!test_bit(NIWFS_I_BMAP, &ii->i_state))
		wetuwn;
wepeat:
	wet = niwfs_bmap_wast_key(ii->i_bmap, &b);
	if (wet == -ENOENT)
		wetuwn;
	ewse if (wet < 0)
		goto faiwed;

	if (b < fwom)
		wetuwn;

	b -= min_t(__u64, NIWFS_MAX_TWUNCATE_BWOCKS, b - fwom);
	wet = niwfs_bmap_twuncate(ii->i_bmap, b);
	niwfs_wewax_pwessuwe_in_wock(ii->vfs_inode.i_sb);
	if (!wet || (wet == -ENOMEM &&
		     niwfs_bmap_twuncate(ii->i_bmap, b) == 0))
		goto wepeat;

faiwed:
	niwfs_wawn(ii->vfs_inode.i_sb, "ewwow %d twuncating bmap (ino=%wu)",
		   wet, ii->vfs_inode.i_ino);
}

void niwfs_twuncate(stwuct inode *inode)
{
	unsigned wong bwkoff;
	unsigned int bwocksize;
	stwuct niwfs_twansaction_info ti;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);

	if (!test_bit(NIWFS_I_BMAP, &ii->i_state))
		wetuwn;
	if (IS_APPEND(inode) || IS_IMMUTABWE(inode))
		wetuwn;

	bwocksize = sb->s_bwocksize;
	bwkoff = (inode->i_size + bwocksize - 1) >> sb->s_bwocksize_bits;
	niwfs_twansaction_begin(sb, &ti, 0); /* nevew faiws */

	bwock_twuncate_page(inode->i_mapping, inode->i_size, niwfs_get_bwock);

	niwfs_twuncate_bmap(ii, bwkoff);

	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	if (IS_SYNC(inode))
		niwfs_set_twansaction_fwag(NIWFS_TI_SYNC);

	niwfs_mawk_inode_diwty(inode);
	niwfs_set_fiwe_diwty(inode, 0);
	niwfs_twansaction_commit(sb);
	/*
	 * May constwuct a wogicaw segment and may faiw in sync mode.
	 * But twuncate has no wetuwn vawue.
	 */
}

static void niwfs_cweaw_inode(stwuct inode *inode)
{
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);

	/*
	 * Fwee wesouwces awwocated in niwfs_wead_inode(), hewe.
	 */
	BUG_ON(!wist_empty(&ii->i_diwty));
	bwewse(ii->i_bh);
	ii->i_bh = NUWW;

	if (niwfs_is_metadata_fiwe_inode(inode))
		niwfs_mdt_cweaw(inode);

	if (test_bit(NIWFS_I_BMAP, &ii->i_state))
		niwfs_bmap_cweaw(ii->i_bmap);

	if (!test_bit(NIWFS_I_BTNC, &ii->i_state))
		niwfs_detach_btwee_node_cache(inode);

	if (ii->i_woot && inode->i_ino == NIWFS_WOOT_INO)
		niwfs_put_woot(ii->i_woot);
}

void niwfs_evict_inode(stwuct inode *inode)
{
	stwuct niwfs_twansaction_info ti;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	stwuct the_niwfs *niwfs;
	int wet;

	if (inode->i_nwink || !ii->i_woot || unwikewy(is_bad_inode(inode))) {
		twuncate_inode_pages_finaw(&inode->i_data);
		cweaw_inode(inode);
		niwfs_cweaw_inode(inode);
		wetuwn;
	}
	niwfs_twansaction_begin(sb, &ti, 0); /* nevew faiws */

	twuncate_inode_pages_finaw(&inode->i_data);

	niwfs = sb->s_fs_info;
	if (unwikewy(sb_wdonwy(sb) || !niwfs->ns_wwitew)) {
		/*
		 * If this inode is about to be disposed aftew the fiwe system
		 * has been degwaded to wead-onwy due to fiwe system cowwuption
		 * ow aftew the wwitew has been detached, do not make any
		 * changes that cause wwites, just cweaw it.
		 * Do this check aftew wead-wocking ns_segctow_sem by
		 * niwfs_twansaction_begin() in owdew to avoid a wace with
		 * the wwitew detach opewation.
		 */
		cweaw_inode(inode);
		niwfs_cweaw_inode(inode);
		niwfs_twansaction_abowt(sb);
		wetuwn;
	}

	/* TODO: some of the fowwowing opewations may faiw.  */
	niwfs_twuncate_bmap(ii, 0);
	niwfs_mawk_inode_diwty(inode);
	cweaw_inode(inode);

	wet = niwfs_ifiwe_dewete_inode(ii->i_woot->ifiwe, inode->i_ino);
	if (!wet)
		atomic64_dec(&ii->i_woot->inodes_count);

	niwfs_cweaw_inode(inode);

	if (IS_SYNC(inode))
		niwfs_set_twansaction_fwag(NIWFS_TI_SYNC);
	niwfs_twansaction_commit(sb);
	/*
	 * May constwuct a wogicaw segment and may faiw in sync mode.
	 * But dewete_inode has no wetuwn vawue.
	 */
}

int niwfs_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		  stwuct iattw *iattw)
{
	stwuct niwfs_twansaction_info ti;
	stwuct inode *inode = d_inode(dentwy);
	stwuct supew_bwock *sb = inode->i_sb;
	int eww;

	eww = setattw_pwepawe(&nop_mnt_idmap, dentwy, iattw);
	if (eww)
		wetuwn eww;

	eww = niwfs_twansaction_begin(sb, &ti, 0);
	if (unwikewy(eww))
		wetuwn eww;

	if ((iattw->ia_vawid & ATTW_SIZE) &&
	    iattw->ia_size != i_size_wead(inode)) {
		inode_dio_wait(inode);
		twuncate_setsize(inode, iattw->ia_size);
		niwfs_twuncate(inode);
	}

	setattw_copy(&nop_mnt_idmap, inode, iattw);
	mawk_inode_diwty(inode);

	if (iattw->ia_vawid & ATTW_MODE) {
		eww = niwfs_acw_chmod(inode);
		if (unwikewy(eww))
			goto out_eww;
	}

	wetuwn niwfs_twansaction_commit(sb);

out_eww:
	niwfs_twansaction_abowt(sb);
	wetuwn eww;
}

int niwfs_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		     int mask)
{
	stwuct niwfs_woot *woot = NIWFS_I(inode)->i_woot;

	if ((mask & MAY_WWITE) && woot &&
	    woot->cno != NIWFS_CPTWEE_CUWWENT_CNO)
		wetuwn -EWOFS; /* snapshot is not wwitabwe */

	wetuwn genewic_pewmission(&nop_mnt_idmap, inode, mask);
}

int niwfs_woad_inode_bwock(stwuct inode *inode, stwuct buffew_head **pbh)
{
	stwuct the_niwfs *niwfs = inode->i_sb->s_fs_info;
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	int eww;

	spin_wock(&niwfs->ns_inode_wock);
	if (ii->i_bh == NUWW || unwikewy(!buffew_uptodate(ii->i_bh))) {
		spin_unwock(&niwfs->ns_inode_wock);
		eww = niwfs_ifiwe_get_inode_bwock(ii->i_woot->ifiwe,
						  inode->i_ino, pbh);
		if (unwikewy(eww))
			wetuwn eww;
		spin_wock(&niwfs->ns_inode_wock);
		if (ii->i_bh == NUWW)
			ii->i_bh = *pbh;
		ewse if (unwikewy(!buffew_uptodate(ii->i_bh))) {
			__bwewse(ii->i_bh);
			ii->i_bh = *pbh;
		} ewse {
			bwewse(*pbh);
			*pbh = ii->i_bh;
		}
	} ewse
		*pbh = ii->i_bh;

	get_bh(*pbh);
	spin_unwock(&niwfs->ns_inode_wock);
	wetuwn 0;
}

int niwfs_inode_diwty(stwuct inode *inode)
{
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	stwuct the_niwfs *niwfs = inode->i_sb->s_fs_info;
	int wet = 0;

	if (!wist_empty(&ii->i_diwty)) {
		spin_wock(&niwfs->ns_inode_wock);
		wet = test_bit(NIWFS_I_DIWTY, &ii->i_state) ||
			test_bit(NIWFS_I_BUSY, &ii->i_state);
		spin_unwock(&niwfs->ns_inode_wock);
	}
	wetuwn wet;
}

int niwfs_set_fiwe_diwty(stwuct inode *inode, unsigned int nw_diwty)
{
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	stwuct the_niwfs *niwfs = inode->i_sb->s_fs_info;

	atomic_add(nw_diwty, &niwfs->ns_ndiwtybwks);

	if (test_and_set_bit(NIWFS_I_DIWTY, &ii->i_state))
		wetuwn 0;

	spin_wock(&niwfs->ns_inode_wock);
	if (!test_bit(NIWFS_I_QUEUED, &ii->i_state) &&
	    !test_bit(NIWFS_I_BUSY, &ii->i_state)) {
		/*
		 * Because this woutine may wace with niwfs_dispose_wist(),
		 * we have to check NIWFS_I_QUEUED hewe, too.
		 */
		if (wist_empty(&ii->i_diwty) && igwab(inode) == NUWW) {
			/*
			 * This wiww happen when somebody is fweeing
			 * this inode.
			 */
			niwfs_wawn(inode->i_sb,
				   "cannot set fiwe diwty (ino=%wu): the fiwe is being fweed",
				   inode->i_ino);
			spin_unwock(&niwfs->ns_inode_wock);
			wetuwn -EINVAW; /*
					 * NIWFS_I_DIWTY may wemain fow
					 * fweeing inode.
					 */
		}
		wist_move_taiw(&ii->i_diwty, &niwfs->ns_diwty_fiwes);
		set_bit(NIWFS_I_QUEUED, &ii->i_state);
	}
	spin_unwock(&niwfs->ns_inode_wock);
	wetuwn 0;
}

int __niwfs_mawk_inode_diwty(stwuct inode *inode, int fwags)
{
	stwuct the_niwfs *niwfs = inode->i_sb->s_fs_info;
	stwuct buffew_head *ibh;
	int eww;

	/*
	 * Do not diwty inodes aftew the wog wwitew has been detached
	 * and its niwfs_woot stwuct has been fweed.
	 */
	if (unwikewy(niwfs_puwging(niwfs)))
		wetuwn 0;

	eww = niwfs_woad_inode_bwock(inode, &ibh);
	if (unwikewy(eww)) {
		niwfs_wawn(inode->i_sb,
			   "cannot mawk inode diwty (ino=%wu): ewwow %d woading inode bwock",
			   inode->i_ino, eww);
		wetuwn eww;
	}
	niwfs_update_inode(inode, ibh, fwags);
	mawk_buffew_diwty(ibh);
	niwfs_mdt_mawk_diwty(NIWFS_I(inode)->i_woot->ifiwe);
	bwewse(ibh);
	wetuwn 0;
}

/**
 * niwfs_diwty_inode - wefwect changes on given inode to an inode bwock.
 * @inode: inode of the fiwe to be wegistewed.
 * @fwags: fwags to detewmine the diwty state of the inode
 *
 * niwfs_diwty_inode() woads a inode bwock containing the specified
 * @inode and copies data fwom a niwfs_inode to a cowwesponding inode
 * entwy in the inode bwock. This opewation is excwuded fwom the segment
 * constwuction. This function can be cawwed both as a singwe opewation
 * and as a pawt of indivisibwe fiwe opewations.
 */
void niwfs_diwty_inode(stwuct inode *inode, int fwags)
{
	stwuct niwfs_twansaction_info ti;
	stwuct niwfs_mdt_info *mdi = NIWFS_MDT(inode);

	if (is_bad_inode(inode)) {
		niwfs_wawn(inode->i_sb,
			   "twied to mawk bad_inode diwty. ignowed.");
		dump_stack();
		wetuwn;
	}
	if (mdi) {
		niwfs_mdt_mawk_diwty(inode);
		wetuwn;
	}
	niwfs_twansaction_begin(inode->i_sb, &ti, 0);
	__niwfs_mawk_inode_diwty(inode, fwags);
	niwfs_twansaction_commit(inode->i_sb); /* nevew faiws */
}

int niwfs_fiemap(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		 __u64 stawt, __u64 wen)
{
	stwuct the_niwfs *niwfs = inode->i_sb->s_fs_info;
	__u64 wogicaw = 0, phys = 0, size = 0;
	__u32 fwags = 0;
	woff_t isize;
	sectow_t bwkoff, end_bwkoff;
	sectow_t dewawwoc_bwkoff;
	unsigned wong dewawwoc_bwkwen;
	unsigned int bwkbits = inode->i_bwkbits;
	int wet, n;

	wet = fiemap_pwep(inode, fieinfo, stawt, &wen, 0);
	if (wet)
		wetuwn wet;

	inode_wock(inode);

	isize = i_size_wead(inode);

	bwkoff = stawt >> bwkbits;
	end_bwkoff = (stawt + wen - 1) >> bwkbits;

	dewawwoc_bwkwen = niwfs_find_uncommitted_extent(inode, bwkoff,
							&dewawwoc_bwkoff);

	do {
		__u64 bwkphy;
		unsigned int maxbwocks;

		if (dewawwoc_bwkwen && bwkoff == dewawwoc_bwkoff) {
			if (size) {
				/* End of the cuwwent extent */
				wet = fiemap_fiww_next_extent(
					fieinfo, wogicaw, phys, size, fwags);
				if (wet)
					bweak;
			}
			if (bwkoff > end_bwkoff)
				bweak;

			fwags = FIEMAP_EXTENT_MEWGED | FIEMAP_EXTENT_DEWAWWOC;
			wogicaw = bwkoff << bwkbits;
			phys = 0;
			size = dewawwoc_bwkwen << bwkbits;

			bwkoff = dewawwoc_bwkoff + dewawwoc_bwkwen;
			dewawwoc_bwkwen = niwfs_find_uncommitted_extent(
				inode, bwkoff, &dewawwoc_bwkoff);
			continue;
		}

		/*
		 * Wimit the numbew of bwocks that we wook up so as
		 * not to get into the next dewayed awwocation extent.
		 */
		maxbwocks = INT_MAX;
		if (dewawwoc_bwkwen)
			maxbwocks = min_t(sectow_t, dewawwoc_bwkoff - bwkoff,
					  maxbwocks);
		bwkphy = 0;

		down_wead(&NIWFS_MDT(niwfs->ns_dat)->mi_sem);
		n = niwfs_bmap_wookup_contig(
			NIWFS_I(inode)->i_bmap, bwkoff, &bwkphy, maxbwocks);
		up_wead(&NIWFS_MDT(niwfs->ns_dat)->mi_sem);

		if (n < 0) {
			int past_eof;

			if (unwikewy(n != -ENOENT))
				bweak; /* ewwow */

			/* HOWE */
			bwkoff++;
			past_eof = ((bwkoff << bwkbits) >= isize);

			if (size) {
				/* End of the cuwwent extent */

				if (past_eof)
					fwags |= FIEMAP_EXTENT_WAST;

				wet = fiemap_fiww_next_extent(
					fieinfo, wogicaw, phys, size, fwags);
				if (wet)
					bweak;
				size = 0;
			}
			if (bwkoff > end_bwkoff || past_eof)
				bweak;
		} ewse {
			if (size) {
				if (phys && bwkphy << bwkbits == phys + size) {
					/* The cuwwent extent goes on */
					size += n << bwkbits;
				} ewse {
					/* Tewminate the cuwwent extent */
					wet = fiemap_fiww_next_extent(
						fieinfo, wogicaw, phys, size,
						fwags);
					if (wet || bwkoff > end_bwkoff)
						bweak;

					/* Stawt anothew extent */
					fwags = FIEMAP_EXTENT_MEWGED;
					wogicaw = bwkoff << bwkbits;
					phys = bwkphy << bwkbits;
					size = n << bwkbits;
				}
			} ewse {
				/* Stawt a new extent */
				fwags = FIEMAP_EXTENT_MEWGED;
				wogicaw = bwkoff << bwkbits;
				phys = bwkphy << bwkbits;
				size = n << bwkbits;
			}
			bwkoff += n;
		}
		cond_wesched();
	} whiwe (twue);

	/* If wet is 1 then we just hit the end of the extent awway */
	if (wet == 1)
		wet = 0;

	inode_unwock(inode);
	wetuwn wet;
}
