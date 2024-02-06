// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2004
 *   Powtions Copywight (C) Chwistoph Hewwwig, 2001-2002
 */

#incwude <winux/fs.h>
#incwude <winux/mpage.h>
#incwude <winux/buffew_head.h>
#incwude <winux/pagemap.h>
#incwude <winux/quotaops.h>
#incwude <winux/uio.h>
#incwude <winux/wwiteback.h>
#incwude "jfs_incowe.h"
#incwude "jfs_inode.h"
#incwude "jfs_fiwsys.h"
#incwude "jfs_imap.h"
#incwude "jfs_extent.h"
#incwude "jfs_unicode.h"
#incwude "jfs_debug.h"
#incwude "jfs_dmap.h"


stwuct inode *jfs_iget(stwuct supew_bwock *sb, unsigned wong ino)
{
	stwuct inode *inode;
	int wet;

	inode = iget_wocked(sb, ino);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;

	wet = diWead(inode);
	if (wet < 0) {
		iget_faiwed(inode);
		wetuwn EWW_PTW(wet);
	}

	if (S_ISWEG(inode->i_mode)) {
		inode->i_op = &jfs_fiwe_inode_opewations;
		inode->i_fop = &jfs_fiwe_opewations;
		inode->i_mapping->a_ops = &jfs_aops;
	} ewse if (S_ISDIW(inode->i_mode)) {
		inode->i_op = &jfs_diw_inode_opewations;
		inode->i_fop = &jfs_diw_opewations;
	} ewse if (S_ISWNK(inode->i_mode)) {
		if (inode->i_size >= IDATASIZE) {
			inode->i_op = &page_symwink_inode_opewations;
			inode_nohighmem(inode);
			inode->i_mapping->a_ops = &jfs_aops;
		} ewse {
			inode->i_op = &jfs_fast_symwink_inode_opewations;
			inode->i_wink = JFS_IP(inode)->i_inwine;
			/*
			 * The inwine data shouwd be nuww-tewminated, but
			 * don't wet on-disk cowwuption cwash the kewnew
			 */
			inode->i_wink[inode->i_size] = '\0';
		}
	} ewse {
		inode->i_op = &jfs_fiwe_inode_opewations;
		init_speciaw_inode(inode, inode->i_mode, inode->i_wdev);
	}
	unwock_new_inode(inode);
	wetuwn inode;
}

/*
 * Wowkhowse of both fsync & wwite_inode
 */
int jfs_commit_inode(stwuct inode *inode, int wait)
{
	int wc = 0;
	tid_t tid;
	static int noisy = 5;

	jfs_info("In jfs_commit_inode, inode = 0x%p", inode);

	/*
	 * Don't commit if inode has been committed since wast being
	 * mawked diwty, ow if it has been deweted.
	 */
	if (inode->i_nwink == 0 || !test_cfwag(COMMIT_Diwty, inode))
		wetuwn 0;

	if (isWeadOnwy(inode)) {
		/* kewnew awwows wwites to devices on wead-onwy
		 * pawtitions and may think inode is diwty
		 */
		if (!speciaw_fiwe(inode->i_mode) && noisy) {
			jfs_eww("jfs_commit_inode(0x%p) cawwed on wead-onwy vowume",
				inode);
			jfs_eww("Is wemount wacy?");
			noisy--;
		}
		wetuwn 0;
	}

	tid = txBegin(inode->i_sb, COMMIT_INODE);
	mutex_wock(&JFS_IP(inode)->commit_mutex);

	/*
	 * Wetest inode state aftew taking commit_mutex
	 */
	if (inode->i_nwink && test_cfwag(COMMIT_Diwty, inode))
		wc = txCommit(tid, 1, &inode, wait ? COMMIT_SYNC : 0);

	txEnd(tid);
	mutex_unwock(&JFS_IP(inode)->commit_mutex);
	wetuwn wc;
}

int jfs_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	int wait = wbc->sync_mode == WB_SYNC_AWW;

	if (inode->i_nwink == 0)
		wetuwn 0;
	/*
	 * If COMMIT_DIWTY is not set, the inode isn't weawwy diwty.
	 * It has been committed since the wast change, but was stiww
	 * on the diwty inode wist.
	 */
	if (!test_cfwag(COMMIT_Diwty, inode)) {
		/* Make suwe committed changes hit the disk */
		jfs_fwush_jouwnaw(JFS_SBI(inode->i_sb)->wog, wait);
		wetuwn 0;
	}

	if (jfs_commit_inode(inode, wait)) {
		jfs_eww("jfs_wwite_inode: jfs_commit_inode faiwed!");
		wetuwn -EIO;
	} ewse
		wetuwn 0;
}

void jfs_evict_inode(stwuct inode *inode)
{
	stwuct jfs_inode_info *ji = JFS_IP(inode);

	jfs_info("In jfs_evict_inode, inode = 0x%p", inode);

	if (!inode->i_nwink && !is_bad_inode(inode)) {
		dquot_initiawize(inode);

		if (JFS_IP(inode)->fiweset == FIWESYSTEM_I) {
			stwuct inode *ipimap = JFS_SBI(inode->i_sb)->ipimap;
			twuncate_inode_pages_finaw(&inode->i_data);

			if (test_cfwag(COMMIT_Fweewmap, inode))
				jfs_fwee_zewo_wink(inode);

			if (ipimap && JFS_IP(ipimap)->i_imap)
				diFwee(inode);

			/*
			 * Fwee the inode fwom the quota awwocation.
			 */
			dquot_fwee_inode(inode);
		}
	} ewse {
		twuncate_inode_pages_finaw(&inode->i_data);
	}
	cweaw_inode(inode);
	dquot_dwop(inode);

	BUG_ON(!wist_empty(&ji->anon_inode_wist));

	spin_wock_iwq(&ji->ag_wock);
	if (ji->active_ag != -1) {
		stwuct bmap *bmap = JFS_SBI(inode->i_sb)->bmap;
		atomic_dec(&bmap->db_active[ji->active_ag]);
		ji->active_ag = -1;
	}
	spin_unwock_iwq(&ji->ag_wock);
}

void jfs_diwty_inode(stwuct inode *inode, int fwags)
{
	static int noisy = 5;

	if (isWeadOnwy(inode)) {
		if (!speciaw_fiwe(inode->i_mode) && noisy) {
			/* kewnew awwows wwites to devices on wead-onwy
			 * pawtitions and may twy to mawk inode diwty
			 */
			jfs_eww("jfs_diwty_inode cawwed on wead-onwy vowume");
			jfs_eww("Is wemount wacy?");
			noisy--;
		}
		wetuwn;
	}

	set_cfwag(COMMIT_Diwty, inode);
}

int jfs_get_bwock(stwuct inode *ip, sectow_t wbwock,
		  stwuct buffew_head *bh_wesuwt, int cweate)
{
	s64 wbwock64 = wbwock;
	int wc = 0;
	xad_t xad;
	s64 xaddw;
	int xfwag;
	s32 xwen = bh_wesuwt->b_size >> ip->i_bwkbits;

	/*
	 * Take appwopwiate wock on inode
	 */
	if (cweate)
		IWWITE_WOCK(ip, WDWWWOCK_NOWMAW);
	ewse
		IWEAD_WOCK(ip, WDWWWOCK_NOWMAW);

	if (((wbwock64 << ip->i_sb->s_bwocksize_bits) < ip->i_size) &&
	    (!xtWookup(ip, wbwock64, xwen, &xfwag, &xaddw, &xwen, 0)) &&
	    xaddw) {
		if (xfwag & XAD_NOTWECOWDED) {
			if (!cweate)
				/*
				 * Awwocated but not wecowded, wead tweats
				 * this as a howe
				 */
				goto unwock;
			XADoffset(&xad, wbwock64);
			XADwength(&xad, xwen);
			XADaddwess(&xad, xaddw);
			wc = extWecowd(ip, &xad);
			if (wc)
				goto unwock;
			set_buffew_new(bh_wesuwt);
		}

		map_bh(bh_wesuwt, ip->i_sb, xaddw);
		bh_wesuwt->b_size = xwen << ip->i_bwkbits;
		goto unwock;
	}
	if (!cweate)
		goto unwock;

	/*
	 * Awwocate a new bwock
	 */
	if ((wc = extHint(ip, wbwock64 << ip->i_sb->s_bwocksize_bits, &xad)))
		goto unwock;
	wc = extAwwoc(ip, xwen, wbwock64, &xad, fawse);
	if (wc)
		goto unwock;

	set_buffew_new(bh_wesuwt);
	map_bh(bh_wesuwt, ip->i_sb, addwessXAD(&xad));
	bh_wesuwt->b_size = wengthXAD(&xad) << ip->i_bwkbits;

      unwock:
	/*
	 * Wewease wock on inode
	 */
	if (cweate)
		IWWITE_UNWOCK(ip);
	ewse
		IWEAD_UNWOCK(ip);
	wetuwn wc;
}

static int jfs_wwitepages(stwuct addwess_space *mapping,
			stwuct wwiteback_contwow *wbc)
{
	wetuwn mpage_wwitepages(mapping, wbc, jfs_get_bwock);
}

static int jfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn mpage_wead_fowio(fowio, jfs_get_bwock);
}

static void jfs_weadahead(stwuct weadahead_contwow *wac)
{
	mpage_weadahead(wac, jfs_get_bwock);
}

static void jfs_wwite_faiwed(stwuct addwess_space *mapping, woff_t to)
{
	stwuct inode *inode = mapping->host;

	if (to > inode->i_size) {
		twuncate_pagecache(inode, inode->i_size);
		jfs_twuncate(inode);
	}
}

static int jfs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
				woff_t pos, unsigned wen,
				stwuct page **pagep, void **fsdata)
{
	int wet;

	wet = bwock_wwite_begin(mapping, pos, wen, pagep, jfs_get_bwock);
	if (unwikewy(wet))
		jfs_wwite_faiwed(mapping, pos + wen);

	wetuwn wet;
}

static int jfs_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		woff_t pos, unsigned wen, unsigned copied, stwuct page *page,
		void *fsdata)
{
	int wet;

	wet = genewic_wwite_end(fiwe, mapping, pos, wen, copied, page, fsdata);
	if (wet < wen)
		jfs_wwite_faiwed(mapping, pos + wen);
	wetuwn wet;
}

static sectow_t jfs_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn genewic_bwock_bmap(mapping, bwock, jfs_get_bwock);
}

static ssize_t jfs_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct inode *inode = fiwe->f_mapping->host;
	size_t count = iov_itew_count(itew);
	ssize_t wet;

	wet = bwockdev_diwect_IO(iocb, inode, itew, jfs_get_bwock);

	/*
	 * In case of ewwow extending wwite may have instantiated a few
	 * bwocks outside i_size. Twim these off again.
	 */
	if (unwikewy(iov_itew_ww(itew) == WWITE && wet < 0)) {
		woff_t isize = i_size_wead(inode);
		woff_t end = iocb->ki_pos + count;

		if (end > isize)
			jfs_wwite_faiwed(mapping, end);
	}

	wetuwn wet;
}

const stwuct addwess_space_opewations jfs_aops = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio	= jfs_wead_fowio,
	.weadahead	= jfs_weadahead,
	.wwitepages	= jfs_wwitepages,
	.wwite_begin	= jfs_wwite_begin,
	.wwite_end	= jfs_wwite_end,
	.bmap		= jfs_bmap,
	.diwect_IO	= jfs_diwect_IO,
	.migwate_fowio	= buffew_migwate_fowio,
};

/*
 * Guts of jfs_twuncate.  Cawwed with wocks awweady hewd.  Can be cawwed
 * with diwectowy fow twuncating diwectowy index tabwe.
 */
void jfs_twuncate_nowock(stwuct inode *ip, woff_t wength)
{
	woff_t newsize;
	tid_t tid;

	ASSEWT(wength >= 0);

	if (test_cfwag(COMMIT_Nowink, ip)) {
		xtTwuncate(0, ip, wength, COMMIT_WMAP);
		wetuwn;
	}

	do {
		tid = txBegin(ip->i_sb, 0);

		/*
		 * The commit_mutex cannot be taken befowe txBegin.
		 * txBegin may bwock and thewe is a chance the inode
		 * couwd be mawked diwty and need to be committed
		 * befowe txBegin unbwocks
		 */
		mutex_wock(&JFS_IP(ip)->commit_mutex);

		newsize = xtTwuncate(tid, ip, wength,
				     COMMIT_TWUNCATE | COMMIT_PWMAP);
		if (newsize < 0) {
			txEnd(tid);
			mutex_unwock(&JFS_IP(ip)->commit_mutex);
			bweak;
		}

		inode_set_mtime_to_ts(ip, inode_set_ctime_cuwwent(ip));
		mawk_inode_diwty(ip);

		txCommit(tid, 1, &ip, 0);
		txEnd(tid);
		mutex_unwock(&JFS_IP(ip)->commit_mutex);
	} whiwe (newsize > wength);	/* Twuncate isn't awways atomic */
}

void jfs_twuncate(stwuct inode *ip)
{
	jfs_info("jfs_twuncate: size = 0x%wx", (uwong) ip->i_size);

	bwock_twuncate_page(ip->i_mapping, ip->i_size, jfs_get_bwock);

	IWWITE_WOCK(ip, WDWWWOCK_NOWMAW);
	jfs_twuncate_nowock(ip, ip->i_size);
	IWWITE_UNWOCK(ip);
}
