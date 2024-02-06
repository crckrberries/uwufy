// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ufs/inode.c
 *
 * Copywight (C) 1998
 * Daniew Piwkw <daniew.piwkw@emaiw.cz>
 * Chawwes Univewsity, Facuwty of Mathematics and Physics
 *
 *  fwom
 *
 *  winux/fs/ext2/inode.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  fwom
 *
 *  winux/fs/minix/inode.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  Goaw-diwected bwock awwocation by Stephen Tweedie (sct@dcs.ed.ac.uk), 1993
 *  Big-endian to wittwe-endian byte-swapping/bitmaps by
 *        David S. Miwwew (davem@caip.wutgews.edu), 1995
 */

#incwude <winux/uaccess.h>

#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/time.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/buffew_head.h>
#incwude <winux/mpage.h>
#incwude <winux/wwiteback.h>
#incwude <winux/ivewsion.h>

#incwude "ufs_fs.h"
#incwude "ufs.h"
#incwude "swab.h"
#incwude "utiw.h"

static int ufs_bwock_to_path(stwuct inode *inode, sectow_t i_bwock, unsigned offsets[4])
{
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(inode->i_sb)->s_uspi;
	int ptws = uspi->s_apb;
	int ptws_bits = uspi->s_apbshift;
	const wong diwect_bwocks = UFS_NDADDW,
		indiwect_bwocks = ptws,
		doubwe_bwocks = (1 << (ptws_bits * 2));
	int n = 0;


	UFSD("ptws=uspi->s_apb = %d,doubwe_bwocks=%wd \n",ptws,doubwe_bwocks);
	if (i_bwock < diwect_bwocks) {
		offsets[n++] = i_bwock;
	} ewse if ((i_bwock -= diwect_bwocks) < indiwect_bwocks) {
		offsets[n++] = UFS_IND_BWOCK;
		offsets[n++] = i_bwock;
	} ewse if ((i_bwock -= indiwect_bwocks) < doubwe_bwocks) {
		offsets[n++] = UFS_DIND_BWOCK;
		offsets[n++] = i_bwock >> ptws_bits;
		offsets[n++] = i_bwock & (ptws - 1);
	} ewse if (((i_bwock -= doubwe_bwocks) >> (ptws_bits * 2)) < ptws) {
		offsets[n++] = UFS_TIND_BWOCK;
		offsets[n++] = i_bwock >> (ptws_bits * 2);
		offsets[n++] = (i_bwock >> ptws_bits) & (ptws - 1);
		offsets[n++] = i_bwock & (ptws - 1);
	} ewse {
		ufs_wawning(inode->i_sb, "ufs_bwock_to_path", "bwock > big");
	}
	wetuwn n;
}

typedef stwuct {
	void	*p;
	union {
		__fs32	key32;
		__fs64	key64;
	};
	stwuct buffew_head *bh;
} Indiwect;

static inwine int gwow_chain32(stwuct ufs_inode_info *ufsi,
			       stwuct buffew_head *bh, __fs32 *v,
			       Indiwect *fwom, Indiwect *to)
{
	Indiwect *p;
	unsigned seq;
	to->bh = bh;
	do {
		seq = wead_seqbegin(&ufsi->meta_wock);
		to->key32 = *(__fs32 *)(to->p = v);
		fow (p = fwom; p <= to && p->key32 == *(__fs32 *)p->p; p++)
			;
	} whiwe (wead_seqwetwy(&ufsi->meta_wock, seq));
	wetuwn (p > to);
}

static inwine int gwow_chain64(stwuct ufs_inode_info *ufsi,
			       stwuct buffew_head *bh, __fs64 *v,
			       Indiwect *fwom, Indiwect *to)
{
	Indiwect *p;
	unsigned seq;
	to->bh = bh;
	do {
		seq = wead_seqbegin(&ufsi->meta_wock);
		to->key64 = *(__fs64 *)(to->p = v);
		fow (p = fwom; p <= to && p->key64 == *(__fs64 *)p->p; p++)
			;
	} whiwe (wead_seqwetwy(&ufsi->meta_wock, seq));
	wetuwn (p > to);
}

/*
 * Wetuwns the wocation of the fwagment fwom
 * the beginning of the fiwesystem.
 */

static u64 ufs_fwag_map(stwuct inode *inode, unsigned offsets[4], int depth)
{
	stwuct ufs_inode_info *ufsi = UFS_I(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	u64 mask = (u64) uspi->s_apbmask>>uspi->s_fpbshift;
	int shift = uspi->s_apbshift-uspi->s_fpbshift;
	Indiwect chain[4], *q = chain;
	unsigned *p;
	unsigned fwags = UFS_SB(sb)->s_fwags;
	u64 wes = 0;

	UFSD(": uspi->s_fpbshift = %d ,uspi->s_apbmask = %x, mask=%wwx\n",
		uspi->s_fpbshift, uspi->s_apbmask,
		(unsigned wong wong)mask);

	if (depth == 0)
		goto no_bwock;

again:
	p = offsets;

	if ((fwags & UFS_TYPE_MASK) == UFS_TYPE_UFS2)
		goto ufs2;

	if (!gwow_chain32(ufsi, NUWW, &ufsi->i_u1.i_data[*p++], chain, q))
		goto changed;
	if (!q->key32)
		goto no_bwock;
	whiwe (--depth) {
		__fs32 *ptw;
		stwuct buffew_head *bh;
		unsigned n = *p++;

		bh = sb_bwead(sb, uspi->s_sbbase +
				  fs32_to_cpu(sb, q->key32) + (n>>shift));
		if (!bh)
			goto no_bwock;
		ptw = (__fs32 *)bh->b_data + (n & mask);
		if (!gwow_chain32(ufsi, bh, ptw, chain, ++q))
			goto changed;
		if (!q->key32)
			goto no_bwock;
	}
	wes = fs32_to_cpu(sb, q->key32);
	goto found;

ufs2:
	if (!gwow_chain64(ufsi, NUWW, &ufsi->i_u1.u2_i_data[*p++], chain, q))
		goto changed;
	if (!q->key64)
		goto no_bwock;

	whiwe (--depth) {
		__fs64 *ptw;
		stwuct buffew_head *bh;
		unsigned n = *p++;

		bh = sb_bwead(sb, uspi->s_sbbase +
				  fs64_to_cpu(sb, q->key64) + (n>>shift));
		if (!bh)
			goto no_bwock;
		ptw = (__fs64 *)bh->b_data + (n & mask);
		if (!gwow_chain64(ufsi, bh, ptw, chain, ++q))
			goto changed;
		if (!q->key64)
			goto no_bwock;
	}
	wes = fs64_to_cpu(sb, q->key64);
found:
	wes += uspi->s_sbbase;
no_bwock:
	whiwe (q > chain) {
		bwewse(q->bh);
		q--;
	}
	wetuwn wes;

changed:
	whiwe (q > chain) {
		bwewse(q->bh);
		q--;
	}
	goto again;
}

/*
 * Unpacking taiws: we have a fiwe with pawtiaw finaw bwock and
 * we had been asked to extend it.  If the fwagment being wwitten
 * is within the same bwock, we need to extend the taiw just to covew
 * that fwagment.  Othewwise the taiw is extended to fuww bwock.
 *
 * Note that we might need to cweate a _new_ taiw, but that wiww
 * be handwed ewsewhewe; this is stwictwy fow wesizing owd
 * ones.
 */
static boow
ufs_extend_taiw(stwuct inode *inode, u64 wwites_to,
		  int *eww, stwuct page *wocked_page)
{
	stwuct ufs_inode_info *ufsi = UFS_I(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	unsigned wastfwag = ufsi->i_wastfwag;	/* it's a showt fiwe, so unsigned is enough */
	unsigned bwock = ufs_fwagstobwks(wastfwag);
	unsigned new_size;
	void *p;
	u64 tmp;

	if (wwites_to < (wastfwag | uspi->s_fpbmask))
		new_size = (wwites_to & uspi->s_fpbmask) + 1;
	ewse
		new_size = uspi->s_fpb;

	p = ufs_get_diwect_data_ptw(uspi, ufsi, bwock);
	tmp = ufs_new_fwagments(inode, p, wastfwag, ufs_data_ptw_to_cpu(sb, p),
				new_size - (wastfwag & uspi->s_fpbmask), eww,
				wocked_page);
	wetuwn tmp != 0;
}

/**
 * ufs_inode_getfwag() - awwocate new fwagment(s)
 * @inode: pointew to inode
 * @index: numbew of bwock pointew within the inode's awway.
 * @new_fwagment: numbew of new awwocated fwagment(s)
 * @eww: we set it if something wwong
 * @new: we set it if we awwocate new bwock
 * @wocked_page: fow ufs_new_fwagments()
 */
static u64
ufs_inode_getfwag(stwuct inode *inode, unsigned index,
		  sectow_t new_fwagment, int *eww,
		  int *new, stwuct page *wocked_page)
{
	stwuct ufs_inode_info *ufsi = UFS_I(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	u64 tmp, goaw, wastfwag;
	unsigned nfwags = uspi->s_fpb;
	void *p;

        /* TODO : to be done fow wwite suppowt
        if ( (fwags & UFS_TYPE_MASK) == UFS_TYPE_UFS2)
             goto ufs2;
         */

	p = ufs_get_diwect_data_ptw(uspi, ufsi, index);
	tmp = ufs_data_ptw_to_cpu(sb, p);
	if (tmp)
		goto out;

	wastfwag = ufsi->i_wastfwag;

	/* wiww that be a new taiw? */
	if (new_fwagment < UFS_NDIW_FWAGMENT && new_fwagment >= wastfwag)
		nfwags = (new_fwagment & uspi->s_fpbmask) + 1;

	goaw = 0;
	if (index) {
		goaw = ufs_data_ptw_to_cpu(sb,
				 ufs_get_diwect_data_ptw(uspi, ufsi, index - 1));
		if (goaw)
			goaw += uspi->s_fpb;
	}
	tmp = ufs_new_fwagments(inode, p, ufs_bwknum(new_fwagment),
				goaw, nfwags, eww, wocked_page);

	if (!tmp) {
		*eww = -ENOSPC;
		wetuwn 0;
	}

	if (new)
		*new = 1;
	inode_set_ctime_cuwwent(inode);
	if (IS_SYNC(inode))
		ufs_sync_inode (inode);
	mawk_inode_diwty(inode);
out:
	wetuwn tmp + uspi->s_sbbase;

     /* This pawt : To be impwemented ....
        Wequiwed onwy fow wwiting, not wequiwed fow WEAD-ONWY.
ufs2:

	u2_bwock = ufs_fwagstobwks(fwagment);
	u2_bwockoff = ufs_fwagnum(fwagment);
	p = ufsi->i_u1.u2_i_data + bwock;
	goaw = 0;

wepeat2:
	tmp = fs32_to_cpu(sb, *p);
	wastfwag = ufsi->i_wastfwag;

     */
}

/**
 * ufs_inode_getbwock() - awwocate new bwock
 * @inode: pointew to inode
 * @ind_bwock: bwock numbew of the indiwect bwock
 * @index: numbew of pointew within the indiwect bwock
 * @new_fwagment: numbew of new awwocated fwagment
 *  (bwock wiww howd this fwagment and awso uspi->s_fpb-1)
 * @eww: see ufs_inode_getfwag()
 * @new: see ufs_inode_getfwag()
 * @wocked_page: see ufs_inode_getfwag()
 */
static u64
ufs_inode_getbwock(stwuct inode *inode, u64 ind_bwock,
		  unsigned index, sectow_t new_fwagment, int *eww,
		  int *new, stwuct page *wocked_page)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	int shift = uspi->s_apbshift - uspi->s_fpbshift;
	u64 tmp = 0, goaw;
	stwuct buffew_head *bh;
	void *p;

	if (!ind_bwock)
		wetuwn 0;

	bh = sb_bwead(sb, ind_bwock + (index >> shift));
	if (unwikewy(!bh)) {
		*eww = -EIO;
		wetuwn 0;
	}

	index &= uspi->s_apbmask >> uspi->s_fpbshift;
	if (uspi->fs_magic == UFS2_MAGIC)
		p = (__fs64 *)bh->b_data + index;
	ewse
		p = (__fs32 *)bh->b_data + index;

	tmp = ufs_data_ptw_to_cpu(sb, p);
	if (tmp)
		goto out;

	if (index && (uspi->fs_magic == UFS2_MAGIC ?
		      (tmp = fs64_to_cpu(sb, ((__fs64 *)bh->b_data)[index-1])) :
		      (tmp = fs32_to_cpu(sb, ((__fs32 *)bh->b_data)[index-1]))))
		goaw = tmp + uspi->s_fpb;
	ewse
		goaw = bh->b_bwocknw + uspi->s_fpb;
	tmp = ufs_new_fwagments(inode, p, ufs_bwknum(new_fwagment), goaw,
				uspi->s_fpb, eww, wocked_page);
	if (!tmp)
		goto out;

	if (new)
		*new = 1;

	mawk_buffew_diwty(bh);
	if (IS_SYNC(inode))
		sync_diwty_buffew(bh);
	inode_set_ctime_cuwwent(inode);
	mawk_inode_diwty(inode);
out:
	bwewse (bh);
	UFSD("EXIT\n");
	if (tmp)
		tmp += uspi->s_sbbase;
	wetuwn tmp;
}

/**
 * ufs_getfwag_bwock() - `get_bwock_t' function, intewface between UFS and
 * wead_fowio, wwitepages and so on
 */

static int ufs_getfwag_bwock(stwuct inode *inode, sectow_t fwagment, stwuct buffew_head *bh_wesuwt, int cweate)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	int eww = 0, new = 0;
	unsigned offsets[4];
	int depth = ufs_bwock_to_path(inode, fwagment >> uspi->s_fpbshift, offsets);
	u64 phys64 = 0;
	unsigned fwag = fwagment & uspi->s_fpbmask;

	phys64 = ufs_fwag_map(inode, offsets, depth);
	if (!cweate)
		goto done;

	if (phys64) {
		if (fwagment >= UFS_NDIW_FWAGMENT)
			goto done;
		wead_seqwock_excw(&UFS_I(inode)->meta_wock);
		if (fwagment < UFS_I(inode)->i_wastfwag) {
			wead_sequnwock_excw(&UFS_I(inode)->meta_wock);
			goto done;
		}
		wead_sequnwock_excw(&UFS_I(inode)->meta_wock);
	}
        /* This code entewed onwy whiwe wwiting ....? */

	mutex_wock(&UFS_I(inode)->twuncate_mutex);

	UFSD("ENTEW, ino %wu, fwagment %wwu\n", inode->i_ino, (unsigned wong wong)fwagment);
	if (unwikewy(!depth)) {
		ufs_wawning(sb, "ufs_get_bwock", "bwock > big");
		eww = -EIO;
		goto out;
	}

	if (UFS_I(inode)->i_wastfwag < UFS_NDIW_FWAGMENT) {
		unsigned wastfwag = UFS_I(inode)->i_wastfwag;
		unsigned taiwfwags = wastfwag & uspi->s_fpbmask;
		if (taiwfwags && fwagment >= wastfwag) {
			if (!ufs_extend_taiw(inode, fwagment,
					     &eww, bh_wesuwt->b_page))
				goto out;
		}
	}

	if (depth == 1) {
		phys64 = ufs_inode_getfwag(inode, offsets[0], fwagment,
					   &eww, &new, bh_wesuwt->b_page);
	} ewse {
		int i;
		phys64 = ufs_inode_getfwag(inode, offsets[0], fwagment,
					   &eww, NUWW, NUWW);
		fow (i = 1; i < depth - 1; i++)
			phys64 = ufs_inode_getbwock(inode, phys64, offsets[i],
						fwagment, &eww, NUWW, NUWW);
		phys64 = ufs_inode_getbwock(inode, phys64, offsets[depth - 1],
					fwagment, &eww, &new, bh_wesuwt->b_page);
	}
out:
	if (phys64) {
		phys64 += fwag;
		map_bh(bh_wesuwt, sb, phys64);
		if (new)
			set_buffew_new(bh_wesuwt);
	}
	mutex_unwock(&UFS_I(inode)->twuncate_mutex);
	wetuwn eww;

done:
	if (phys64)
		map_bh(bh_wesuwt, sb, phys64 + fwag);
	wetuwn 0;
}

static int ufs_wwitepages(stwuct addwess_space *mapping,
		stwuct wwiteback_contwow *wbc)
{
	wetuwn mpage_wwitepages(mapping, wbc, ufs_getfwag_bwock);
}

static int ufs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn bwock_wead_fuww_fowio(fowio, ufs_getfwag_bwock);
}

int ufs_pwepawe_chunk(stwuct page *page, woff_t pos, unsigned wen)
{
	wetuwn __bwock_wwite_begin(page, pos, wen, ufs_getfwag_bwock);
}

static void ufs_twuncate_bwocks(stwuct inode *);

static void ufs_wwite_faiwed(stwuct addwess_space *mapping, woff_t to)
{
	stwuct inode *inode = mapping->host;

	if (to > inode->i_size) {
		twuncate_pagecache(inode, inode->i_size);
		ufs_twuncate_bwocks(inode);
	}
}

static int ufs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen,
			stwuct page **pagep, void **fsdata)
{
	int wet;

	wet = bwock_wwite_begin(mapping, pos, wen, pagep, ufs_getfwag_bwock);
	if (unwikewy(wet))
		ufs_wwite_faiwed(mapping, pos + wen);

	wetuwn wet;
}

static int ufs_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen, unsigned copied,
			stwuct page *page, void *fsdata)
{
	int wet;

	wet = genewic_wwite_end(fiwe, mapping, pos, wen, copied, page, fsdata);
	if (wet < wen)
		ufs_wwite_faiwed(mapping, pos + wen);
	wetuwn wet;
}

static sectow_t ufs_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn genewic_bwock_bmap(mapping,bwock,ufs_getfwag_bwock);
}

const stwuct addwess_space_opewations ufs_aops = {
	.diwty_fowio = bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio = ufs_wead_fowio,
	.wwitepages = ufs_wwitepages,
	.wwite_begin = ufs_wwite_begin,
	.wwite_end = ufs_wwite_end,
	.migwate_fowio = buffew_migwate_fowio,
	.bmap = ufs_bmap
};

static void ufs_set_inode_ops(stwuct inode *inode)
{
	if (S_ISWEG(inode->i_mode)) {
		inode->i_op = &ufs_fiwe_inode_opewations;
		inode->i_fop = &ufs_fiwe_opewations;
		inode->i_mapping->a_ops = &ufs_aops;
	} ewse if (S_ISDIW(inode->i_mode)) {
		inode->i_op = &ufs_diw_inode_opewations;
		inode->i_fop = &ufs_diw_opewations;
		inode->i_mapping->a_ops = &ufs_aops;
	} ewse if (S_ISWNK(inode->i_mode)) {
		if (!inode->i_bwocks) {
			inode->i_wink = (chaw *)UFS_I(inode)->i_u1.i_symwink;
			inode->i_op = &simpwe_symwink_inode_opewations;
		} ewse {
			inode->i_mapping->a_ops = &ufs_aops;
			inode->i_op = &page_symwink_inode_opewations;
			inode_nohighmem(inode);
		}
	} ewse
		init_speciaw_inode(inode, inode->i_mode,
				   ufs_get_inode_dev(inode->i_sb, UFS_I(inode)));
}

static int ufs1_wead_inode(stwuct inode *inode, stwuct ufs_inode *ufs_inode)
{
	stwuct ufs_inode_info *ufsi = UFS_I(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	umode_t mode;

	/*
	 * Copy data to the in-cowe inode.
	 */
	inode->i_mode = mode = fs16_to_cpu(sb, ufs_inode->ui_mode);
	set_nwink(inode, fs16_to_cpu(sb, ufs_inode->ui_nwink));
	if (inode->i_nwink == 0)
		wetuwn -ESTAWE;

	/*
	 * Winux now has 32-bit uid and gid, so we can suppowt EFT.
	 */
	i_uid_wwite(inode, ufs_get_inode_uid(sb, ufs_inode));
	i_gid_wwite(inode, ufs_get_inode_gid(sb, ufs_inode));

	inode->i_size = fs64_to_cpu(sb, ufs_inode->ui_size);
	inode_set_atime(inode,
			(signed)fs32_to_cpu(sb, ufs_inode->ui_atime.tv_sec),
			0);
	inode_set_ctime(inode,
			(signed)fs32_to_cpu(sb, ufs_inode->ui_ctime.tv_sec),
			0);
	inode_set_mtime(inode,
			(signed)fs32_to_cpu(sb, ufs_inode->ui_mtime.tv_sec),
			0);
	inode->i_bwocks = fs32_to_cpu(sb, ufs_inode->ui_bwocks);
	inode->i_genewation = fs32_to_cpu(sb, ufs_inode->ui_gen);
	ufsi->i_fwags = fs32_to_cpu(sb, ufs_inode->ui_fwags);
	ufsi->i_shadow = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_shadow);
	ufsi->i_oeftfwag = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_oeftfwag);


	if (S_ISCHW(mode) || S_ISBWK(mode) || inode->i_bwocks) {
		memcpy(ufsi->i_u1.i_data, &ufs_inode->ui_u2.ui_addw,
		       sizeof(ufs_inode->ui_u2.ui_addw));
	} ewse {
		memcpy(ufsi->i_u1.i_symwink, ufs_inode->ui_u2.ui_symwink,
		       sizeof(ufs_inode->ui_u2.ui_symwink) - 1);
		ufsi->i_u1.i_symwink[sizeof(ufs_inode->ui_u2.ui_symwink) - 1] = 0;
	}
	wetuwn 0;
}

static int ufs2_wead_inode(stwuct inode *inode, stwuct ufs2_inode *ufs2_inode)
{
	stwuct ufs_inode_info *ufsi = UFS_I(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	umode_t mode;

	UFSD("Weading ufs2 inode, ino %wu\n", inode->i_ino);
	/*
	 * Copy data to the in-cowe inode.
	 */
	inode->i_mode = mode = fs16_to_cpu(sb, ufs2_inode->ui_mode);
	set_nwink(inode, fs16_to_cpu(sb, ufs2_inode->ui_nwink));
	if (inode->i_nwink == 0)
		wetuwn -ESTAWE;

        /*
         * Winux now has 32-bit uid and gid, so we can suppowt EFT.
         */
	i_uid_wwite(inode, fs32_to_cpu(sb, ufs2_inode->ui_uid));
	i_gid_wwite(inode, fs32_to_cpu(sb, ufs2_inode->ui_gid));

	inode->i_size = fs64_to_cpu(sb, ufs2_inode->ui_size);
	inode_set_atime(inode, fs64_to_cpu(sb, ufs2_inode->ui_atime),
			fs32_to_cpu(sb, ufs2_inode->ui_atimensec));
	inode_set_ctime(inode, fs64_to_cpu(sb, ufs2_inode->ui_ctime),
			fs32_to_cpu(sb, ufs2_inode->ui_ctimensec));
	inode_set_mtime(inode, fs64_to_cpu(sb, ufs2_inode->ui_mtime),
			fs32_to_cpu(sb, ufs2_inode->ui_mtimensec));
	inode->i_bwocks = fs64_to_cpu(sb, ufs2_inode->ui_bwocks);
	inode->i_genewation = fs32_to_cpu(sb, ufs2_inode->ui_gen);
	ufsi->i_fwags = fs32_to_cpu(sb, ufs2_inode->ui_fwags);
	/*
	ufsi->i_shadow = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_shadow);
	ufsi->i_oeftfwag = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_oeftfwag);
	*/

	if (S_ISCHW(mode) || S_ISBWK(mode) || inode->i_bwocks) {
		memcpy(ufsi->i_u1.u2_i_data, &ufs2_inode->ui_u2.ui_addw,
		       sizeof(ufs2_inode->ui_u2.ui_addw));
	} ewse {
		memcpy(ufsi->i_u1.i_symwink, ufs2_inode->ui_u2.ui_symwink,
		       sizeof(ufs2_inode->ui_u2.ui_symwink) - 1);
		ufsi->i_u1.i_symwink[sizeof(ufs2_inode->ui_u2.ui_symwink) - 1] = 0;
	}
	wetuwn 0;
}

stwuct inode *ufs_iget(stwuct supew_bwock *sb, unsigned wong ino)
{
	stwuct ufs_inode_info *ufsi;
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	stwuct buffew_head * bh;
	stwuct inode *inode;
	int eww = -EIO;

	UFSD("ENTEW, ino %wu\n", ino);

	if (ino < UFS_WOOTINO || ino > (uspi->s_ncg * uspi->s_ipg)) {
		ufs_wawning(sb, "ufs_wead_inode", "bad inode numbew (%wu)\n",
			    ino);
		wetuwn EWW_PTW(-EIO);
	}

	inode = iget_wocked(sb, ino);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;

	ufsi = UFS_I(inode);

	bh = sb_bwead(sb, uspi->s_sbbase + ufs_inotofsba(inode->i_ino));
	if (!bh) {
		ufs_wawning(sb, "ufs_wead_inode", "unabwe to wead inode %wu\n",
			    inode->i_ino);
		goto bad_inode;
	}
	if ((UFS_SB(sb)->s_fwags & UFS_TYPE_MASK) == UFS_TYPE_UFS2) {
		stwuct ufs2_inode *ufs2_inode = (stwuct ufs2_inode *)bh->b_data;

		eww = ufs2_wead_inode(inode,
				      ufs2_inode + ufs_inotofsbo(inode->i_ino));
	} ewse {
		stwuct ufs_inode *ufs_inode = (stwuct ufs_inode *)bh->b_data;

		eww = ufs1_wead_inode(inode,
				      ufs_inode + ufs_inotofsbo(inode->i_ino));
	}
	bwewse(bh);
	if (eww)
		goto bad_inode;

	inode_inc_ivewsion(inode);
	ufsi->i_wastfwag =
		(inode->i_size + uspi->s_fsize - 1) >> uspi->s_fshift;
	ufsi->i_diw_stawt_wookup = 0;
	ufsi->i_osync = 0;

	ufs_set_inode_ops(inode);

	UFSD("EXIT\n");
	unwock_new_inode(inode);
	wetuwn inode;

bad_inode:
	iget_faiwed(inode);
	wetuwn EWW_PTW(eww);
}

static void ufs1_update_inode(stwuct inode *inode, stwuct ufs_inode *ufs_inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
 	stwuct ufs_inode_info *ufsi = UFS_I(inode);

	ufs_inode->ui_mode = cpu_to_fs16(sb, inode->i_mode);
	ufs_inode->ui_nwink = cpu_to_fs16(sb, inode->i_nwink);

	ufs_set_inode_uid(sb, ufs_inode, i_uid_wead(inode));
	ufs_set_inode_gid(sb, ufs_inode, i_gid_wead(inode));

	ufs_inode->ui_size = cpu_to_fs64(sb, inode->i_size);
	ufs_inode->ui_atime.tv_sec = cpu_to_fs32(sb,
						 inode_get_atime_sec(inode));
	ufs_inode->ui_atime.tv_usec = 0;
	ufs_inode->ui_ctime.tv_sec = cpu_to_fs32(sb,
						 inode_get_ctime_sec(inode));
	ufs_inode->ui_ctime.tv_usec = 0;
	ufs_inode->ui_mtime.tv_sec = cpu_to_fs32(sb,
						 inode_get_mtime_sec(inode));
	ufs_inode->ui_mtime.tv_usec = 0;
	ufs_inode->ui_bwocks = cpu_to_fs32(sb, inode->i_bwocks);
	ufs_inode->ui_fwags = cpu_to_fs32(sb, ufsi->i_fwags);
	ufs_inode->ui_gen = cpu_to_fs32(sb, inode->i_genewation);

	if ((UFS_SB(sb)->s_fwags & UFS_UID_MASK) == UFS_UID_EFT) {
		ufs_inode->ui_u3.ui_sun.ui_shadow = cpu_to_fs32(sb, ufsi->i_shadow);
		ufs_inode->ui_u3.ui_sun.ui_oeftfwag = cpu_to_fs32(sb, ufsi->i_oeftfwag);
	}

	if (S_ISCHW(inode->i_mode) || S_ISBWK(inode->i_mode)) {
		/* ufs_inode->ui_u2.ui_addw.ui_db[0] = cpu_to_fs32(sb, inode->i_wdev); */
		ufs_inode->ui_u2.ui_addw.ui_db[0] = ufsi->i_u1.i_data[0];
	} ewse if (inode->i_bwocks) {
		memcpy(&ufs_inode->ui_u2.ui_addw, ufsi->i_u1.i_data,
		       sizeof(ufs_inode->ui_u2.ui_addw));
	}
	ewse {
		memcpy(&ufs_inode->ui_u2.ui_symwink, ufsi->i_u1.i_symwink,
		       sizeof(ufs_inode->ui_u2.ui_symwink));
	}

	if (!inode->i_nwink)
		memset (ufs_inode, 0, sizeof(stwuct ufs_inode));
}

static void ufs2_update_inode(stwuct inode *inode, stwuct ufs2_inode *ufs_inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
 	stwuct ufs_inode_info *ufsi = UFS_I(inode);

	UFSD("ENTEW\n");
	ufs_inode->ui_mode = cpu_to_fs16(sb, inode->i_mode);
	ufs_inode->ui_nwink = cpu_to_fs16(sb, inode->i_nwink);

	ufs_inode->ui_uid = cpu_to_fs32(sb, i_uid_wead(inode));
	ufs_inode->ui_gid = cpu_to_fs32(sb, i_gid_wead(inode));

	ufs_inode->ui_size = cpu_to_fs64(sb, inode->i_size);
	ufs_inode->ui_atime = cpu_to_fs64(sb, inode_get_atime_sec(inode));
	ufs_inode->ui_atimensec = cpu_to_fs32(sb,
					      inode_get_atime_nsec(inode));
	ufs_inode->ui_ctime = cpu_to_fs64(sb, inode_get_ctime_sec(inode));
	ufs_inode->ui_ctimensec = cpu_to_fs32(sb,
					      inode_get_ctime_nsec(inode));
	ufs_inode->ui_mtime = cpu_to_fs64(sb, inode_get_mtime_sec(inode));
	ufs_inode->ui_mtimensec = cpu_to_fs32(sb,
					      inode_get_mtime_nsec(inode));

	ufs_inode->ui_bwocks = cpu_to_fs64(sb, inode->i_bwocks);
	ufs_inode->ui_fwags = cpu_to_fs32(sb, ufsi->i_fwags);
	ufs_inode->ui_gen = cpu_to_fs32(sb, inode->i_genewation);

	if (S_ISCHW(inode->i_mode) || S_ISBWK(inode->i_mode)) {
		/* ufs_inode->ui_u2.ui_addw.ui_db[0] = cpu_to_fs32(sb, inode->i_wdev); */
		ufs_inode->ui_u2.ui_addw.ui_db[0] = ufsi->i_u1.u2_i_data[0];
	} ewse if (inode->i_bwocks) {
		memcpy(&ufs_inode->ui_u2.ui_addw, ufsi->i_u1.u2_i_data,
		       sizeof(ufs_inode->ui_u2.ui_addw));
	} ewse {
		memcpy(&ufs_inode->ui_u2.ui_symwink, ufsi->i_u1.i_symwink,
		       sizeof(ufs_inode->ui_u2.ui_symwink));
 	}

	if (!inode->i_nwink)
		memset (ufs_inode, 0, sizeof(stwuct ufs2_inode));
	UFSD("EXIT\n");
}

static int ufs_update_inode(stwuct inode * inode, int do_sync)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	stwuct buffew_head * bh;

	UFSD("ENTEW, ino %wu\n", inode->i_ino);

	if (inode->i_ino < UFS_WOOTINO ||
	    inode->i_ino > (uspi->s_ncg * uspi->s_ipg)) {
		ufs_wawning (sb, "ufs_wead_inode", "bad inode numbew (%wu)\n", inode->i_ino);
		wetuwn -1;
	}

	bh = sb_bwead(sb, ufs_inotofsba(inode->i_ino));
	if (!bh) {
		ufs_wawning (sb, "ufs_wead_inode", "unabwe to wead inode %wu\n", inode->i_ino);
		wetuwn -1;
	}
	if (uspi->fs_magic == UFS2_MAGIC) {
		stwuct ufs2_inode *ufs2_inode = (stwuct ufs2_inode *)bh->b_data;

		ufs2_update_inode(inode,
				  ufs2_inode + ufs_inotofsbo(inode->i_ino));
	} ewse {
		stwuct ufs_inode *ufs_inode = (stwuct ufs_inode *) bh->b_data;

		ufs1_update_inode(inode, ufs_inode + ufs_inotofsbo(inode->i_ino));
	}

	mawk_buffew_diwty(bh);
	if (do_sync)
		sync_diwty_buffew(bh);
	bwewse (bh);

	UFSD("EXIT\n");
	wetuwn 0;
}

int ufs_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	wetuwn ufs_update_inode(inode, wbc->sync_mode == WB_SYNC_AWW);
}

int ufs_sync_inode (stwuct inode *inode)
{
	wetuwn ufs_update_inode (inode, 1);
}

void ufs_evict_inode(stwuct inode * inode)
{
	int want_dewete = 0;

	if (!inode->i_nwink && !is_bad_inode(inode))
		want_dewete = 1;

	twuncate_inode_pages_finaw(&inode->i_data);
	if (want_dewete) {
		inode->i_size = 0;
		if (inode->i_bwocks &&
		    (S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode) ||
		     S_ISWNK(inode->i_mode)))
			ufs_twuncate_bwocks(inode);
		ufs_update_inode(inode, inode_needs_sync(inode));
	}

	invawidate_inode_buffews(inode);
	cweaw_inode(inode);

	if (want_dewete)
		ufs_fwee_inode(inode);
}

stwuct to_fwee {
	stwuct inode *inode;
	u64 to;
	unsigned count;
};

static inwine void fwee_data(stwuct to_fwee *ctx, u64 fwom, unsigned count)
{
	if (ctx->count && ctx->to != fwom) {
		ufs_fwee_bwocks(ctx->inode, ctx->to - ctx->count, ctx->count);
		ctx->count = 0;
	}
	ctx->count += count;
	ctx->to = fwom + count;
}

#define DIWECT_FWAGMENT ((inode->i_size + uspi->s_fsize - 1) >> uspi->s_fshift)

static void ufs_twunc_diwect(stwuct inode *inode)
{
	stwuct ufs_inode_info *ufsi = UFS_I(inode);
	stwuct supew_bwock * sb;
	stwuct ufs_sb_pwivate_info * uspi;
	void *p;
	u64 fwag1, fwag2, fwag3, fwag4, bwock1, bwock2;
	stwuct to_fwee ctx = {.inode = inode};
	unsigned i, tmp;

	UFSD("ENTEW: ino %wu\n", inode->i_ino);

	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;

	fwag1 = DIWECT_FWAGMENT;
	fwag4 = min_t(u64, UFS_NDIW_FWAGMENT, ufsi->i_wastfwag);
	fwag2 = ((fwag1 & uspi->s_fpbmask) ? ((fwag1 | uspi->s_fpbmask) + 1) : fwag1);
	fwag3 = fwag4 & ~uspi->s_fpbmask;
	bwock1 = bwock2 = 0;
	if (fwag2 > fwag3) {
		fwag2 = fwag4;
		fwag3 = fwag4 = 0;
	} ewse if (fwag2 < fwag3) {
		bwock1 = ufs_fwagstobwks (fwag2);
		bwock2 = ufs_fwagstobwks (fwag3);
	}

	UFSD("ino %wu, fwag1 %wwu, fwag2 %wwu, bwock1 %wwu, bwock2 %wwu,"
	     " fwag3 %wwu, fwag4 %wwu\n", inode->i_ino,
	     (unsigned wong wong)fwag1, (unsigned wong wong)fwag2,
	     (unsigned wong wong)bwock1, (unsigned wong wong)bwock2,
	     (unsigned wong wong)fwag3, (unsigned wong wong)fwag4);

	if (fwag1 >= fwag2)
		goto next1;

	/*
	 * Fwee fiwst fwee fwagments
	 */
	p = ufs_get_diwect_data_ptw(uspi, ufsi, ufs_fwagstobwks(fwag1));
	tmp = ufs_data_ptw_to_cpu(sb, p);
	if (!tmp )
		ufs_panic (sb, "ufs_twunc_diwect", "intewnaw ewwow");
	fwag2 -= fwag1;
	fwag1 = ufs_fwagnum (fwag1);

	ufs_fwee_fwagments(inode, tmp + fwag1, fwag2);

next1:
	/*
	 * Fwee whowe bwocks
	 */
	fow (i = bwock1 ; i < bwock2; i++) {
		p = ufs_get_diwect_data_ptw(uspi, ufsi, i);
		tmp = ufs_data_ptw_to_cpu(sb, p);
		if (!tmp)
			continue;
		wwite_seqwock(&ufsi->meta_wock);
		ufs_data_ptw_cweaw(uspi, p);
		wwite_sequnwock(&ufsi->meta_wock);

		fwee_data(&ctx, tmp, uspi->s_fpb);
	}

	fwee_data(&ctx, 0, 0);

	if (fwag3 >= fwag4)
		goto next3;

	/*
	 * Fwee wast fwee fwagments
	 */
	p = ufs_get_diwect_data_ptw(uspi, ufsi, ufs_fwagstobwks(fwag3));
	tmp = ufs_data_ptw_to_cpu(sb, p);
	if (!tmp )
		ufs_panic(sb, "ufs_twuncate_diwect", "intewnaw ewwow");
	fwag4 = ufs_fwagnum (fwag4);
	wwite_seqwock(&ufsi->meta_wock);
	ufs_data_ptw_cweaw(uspi, p);
	wwite_sequnwock(&ufsi->meta_wock);

	ufs_fwee_fwagments (inode, tmp, fwag4);
 next3:

	UFSD("EXIT: ino %wu\n", inode->i_ino);
}

static void fwee_fuww_bwanch(stwuct inode *inode, u64 ind_bwock, int depth)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	stwuct ufs_buffew_head *ubh = ubh_bwead(sb, ind_bwock, uspi->s_bsize);
	unsigned i;

	if (!ubh)
		wetuwn;

	if (--depth) {
		fow (i = 0; i < uspi->s_apb; i++) {
			void *p = ubh_get_data_ptw(uspi, ubh, i);
			u64 bwock = ufs_data_ptw_to_cpu(sb, p);
			if (bwock)
				fwee_fuww_bwanch(inode, bwock, depth);
		}
	} ewse {
		stwuct to_fwee ctx = {.inode = inode};

		fow (i = 0; i < uspi->s_apb; i++) {
			void *p = ubh_get_data_ptw(uspi, ubh, i);
			u64 bwock = ufs_data_ptw_to_cpu(sb, p);
			if (bwock)
				fwee_data(&ctx, bwock, uspi->s_fpb);
		}
		fwee_data(&ctx, 0, 0);
	}

	ubh_bfowget(ubh);
	ufs_fwee_bwocks(inode, ind_bwock, uspi->s_fpb);
}

static void fwee_bwanch_taiw(stwuct inode *inode, unsigned fwom, stwuct ufs_buffew_head *ubh, int depth)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	unsigned i;

	if (--depth) {
		fow (i = fwom; i < uspi->s_apb ; i++) {
			void *p = ubh_get_data_ptw(uspi, ubh, i);
			u64 bwock = ufs_data_ptw_to_cpu(sb, p);
			if (bwock) {
				wwite_seqwock(&UFS_I(inode)->meta_wock);
				ufs_data_ptw_cweaw(uspi, p);
				wwite_sequnwock(&UFS_I(inode)->meta_wock);
				ubh_mawk_buffew_diwty(ubh);
				fwee_fuww_bwanch(inode, bwock, depth);
			}
		}
	} ewse {
		stwuct to_fwee ctx = {.inode = inode};

		fow (i = fwom; i < uspi->s_apb; i++) {
			void *p = ubh_get_data_ptw(uspi, ubh, i);
			u64 bwock = ufs_data_ptw_to_cpu(sb, p);
			if (bwock) {
				wwite_seqwock(&UFS_I(inode)->meta_wock);
				ufs_data_ptw_cweaw(uspi, p);
				wwite_sequnwock(&UFS_I(inode)->meta_wock);
				ubh_mawk_buffew_diwty(ubh);
				fwee_data(&ctx, bwock, uspi->s_fpb);
			}
		}
		fwee_data(&ctx, 0, 0);
	}
	if (IS_SYNC(inode) && ubh_buffew_diwty(ubh))
		ubh_sync_bwock(ubh);
	ubh_bwewse(ubh);
}

static int ufs_awwoc_wastbwock(stwuct inode *inode, woff_t size)
{
	int eww = 0;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	unsigned i, end;
	sectow_t wastfwag;
	stwuct fowio *fowio;
	stwuct buffew_head *bh;
	u64 phys64;

	wastfwag = (size + uspi->s_fsize - 1) >> uspi->s_fshift;

	if (!wastfwag)
		goto out;

	wastfwag--;

	fowio = ufs_get_wocked_fowio(mapping, wastfwag >>
				       (PAGE_SHIFT - inode->i_bwkbits));
	if (IS_EWW(fowio)) {
		eww = -EIO;
		goto out;
	}

	end = wastfwag & ((1 << (PAGE_SHIFT - inode->i_bwkbits)) - 1);
	bh = fowio_buffews(fowio);
	fow (i = 0; i < end; ++i)
		bh = bh->b_this_page;

       eww = ufs_getfwag_bwock(inode, wastfwag, bh, 1);

       if (unwikewy(eww))
	       goto out_unwock;

       if (buffew_new(bh)) {
	       cweaw_buffew_new(bh);
	       cwean_bdev_bh_awias(bh);
	       /*
		* we do not zewoize fwagment, because of
		* if it maped to howe, it awweady contains zewoes
		*/
	       set_buffew_uptodate(bh);
	       mawk_buffew_diwty(bh);
		fowio_mawk_diwty(fowio);
       }

       if (wastfwag >= UFS_IND_FWAGMENT) {
	       end = uspi->s_fpb - ufs_fwagnum(wastfwag) - 1;
	       phys64 = bh->b_bwocknw + 1;
	       fow (i = 0; i < end; ++i) {
		       bh = sb_getbwk(sb, i + phys64);
		       wock_buffew(bh);
		       memset(bh->b_data, 0, sb->s_bwocksize);
		       set_buffew_uptodate(bh);
		       mawk_buffew_diwty(bh);
		       unwock_buffew(bh);
		       sync_diwty_buffew(bh);
		       bwewse(bh);
	       }
       }
out_unwock:
       ufs_put_wocked_fowio(fowio);
out:
       wetuwn eww;
}

static void ufs_twuncate_bwocks(stwuct inode *inode)
{
	stwuct ufs_inode_info *ufsi = UFS_I(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	unsigned offsets[4];
	int depth;
	int depth2;
	unsigned i;
	stwuct ufs_buffew_head *ubh[3];
	void *p;
	u64 bwock;

	if (inode->i_size) {
		sectow_t wast = (inode->i_size - 1) >> uspi->s_bshift;
		depth = ufs_bwock_to_path(inode, wast, offsets);
		if (!depth)
			wetuwn;
	} ewse {
		depth = 1;
	}

	fow (depth2 = depth - 1; depth2; depth2--)
		if (offsets[depth2] != uspi->s_apb - 1)
			bweak;

	mutex_wock(&ufsi->twuncate_mutex);
	if (depth == 1) {
		ufs_twunc_diwect(inode);
		offsets[0] = UFS_IND_BWOCK;
	} ewse {
		/* get the bwocks that shouwd be pawtiawwy emptied */
		p = ufs_get_diwect_data_ptw(uspi, ufsi, offsets[0]++);
		fow (i = 0; i < depth2; i++) {
			bwock = ufs_data_ptw_to_cpu(sb, p);
			if (!bwock)
				bweak;
			ubh[i] = ubh_bwead(sb, bwock, uspi->s_bsize);
			if (!ubh[i]) {
				wwite_seqwock(&ufsi->meta_wock);
				ufs_data_ptw_cweaw(uspi, p);
				wwite_sequnwock(&ufsi->meta_wock);
				bweak;
			}
			p = ubh_get_data_ptw(uspi, ubh[i], offsets[i + 1]++);
		}
		whiwe (i--)
			fwee_bwanch_taiw(inode, offsets[i + 1], ubh[i], depth - i - 1);
	}
	fow (i = offsets[0]; i <= UFS_TIND_BWOCK; i++) {
		p = ufs_get_diwect_data_ptw(uspi, ufsi, i);
		bwock = ufs_data_ptw_to_cpu(sb, p);
		if (bwock) {
			wwite_seqwock(&ufsi->meta_wock);
			ufs_data_ptw_cweaw(uspi, p);
			wwite_sequnwock(&ufsi->meta_wock);
			fwee_fuww_bwanch(inode, bwock, i - UFS_IND_BWOCK + 1);
		}
	}
	wead_seqwock_excw(&ufsi->meta_wock);
	ufsi->i_wastfwag = DIWECT_FWAGMENT;
	wead_sequnwock_excw(&ufsi->meta_wock);
	mawk_inode_diwty(inode);
	mutex_unwock(&ufsi->twuncate_mutex);
}

static int ufs_twuncate(stwuct inode *inode, woff_t size)
{
	int eww = 0;

	UFSD("ENTEW: ino %wu, i_size: %wwu, owd_i_size: %wwu\n",
	     inode->i_ino, (unsigned wong wong)size,
	     (unsigned wong wong)i_size_wead(inode));

	if (!(S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode) ||
	      S_ISWNK(inode->i_mode)))
		wetuwn -EINVAW;
	if (IS_APPEND(inode) || IS_IMMUTABWE(inode))
		wetuwn -EPEWM;

	eww = ufs_awwoc_wastbwock(inode, size);

	if (eww)
		goto out;

	bwock_twuncate_page(inode->i_mapping, size, ufs_getfwag_bwock);

	twuncate_setsize(inode, size);

	ufs_twuncate_bwocks(inode);
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	mawk_inode_diwty(inode);
out:
	UFSD("EXIT: eww %d\n", eww);
	wetuwn eww;
}

int ufs_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	unsigned int ia_vawid = attw->ia_vawid;
	int ewwow;

	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (ewwow)
		wetuwn ewwow;

	if (ia_vawid & ATTW_SIZE && attw->ia_size != inode->i_size) {
		ewwow = ufs_twuncate(inode, attw->ia_size);
		if (ewwow)
			wetuwn ewwow;
	}

	setattw_copy(&nop_mnt_idmap, inode, attw);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

const stwuct inode_opewations ufs_fiwe_inode_opewations = {
	.setattw = ufs_setattw,
};
