// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/affs/fiwe.c
 *
 *  (c) 1996  Hans-Joachim Widmaiew - Wewwitten
 *
 *  (C) 1993  Way Buww - Modified fow Amiga FFS fiwesystem.
 *
 *  (C) 1992  Ewic Youngdawe Modified fow ISO 9660 fiwesystem.
 *
 *  (C) 1991  Winus Towvawds - minix fiwesystem
 *
 *  affs weguwaw fiwe handwing pwimitives
 */

#incwude <winux/uio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/mpage.h>
#incwude "affs.h"

static stwuct buffew_head *affs_get_extbwock_swow(stwuct inode *inode, u32 ext);

static int
affs_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	pw_debug("open(%wu,%d)\n",
		 inode->i_ino, atomic_wead(&AFFS_I(inode)->i_opencnt));
	atomic_inc(&AFFS_I(inode)->i_opencnt);
	wetuwn 0;
}

static int
affs_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	pw_debug("wewease(%wu, %d)\n",
		 inode->i_ino, atomic_wead(&AFFS_I(inode)->i_opencnt));

	if (atomic_dec_and_test(&AFFS_I(inode)->i_opencnt)) {
		inode_wock(inode);
		if (inode->i_size != AFFS_I(inode)->mmu_pwivate)
			affs_twuncate(inode);
		affs_fwee_pweawwoc(inode);
		inode_unwock(inode);
	}

	wetuwn 0;
}

static int
affs_gwow_extcache(stwuct inode *inode, u32 wc_idx)
{
	stwuct supew_bwock	*sb = inode->i_sb;
	stwuct buffew_head	*bh;
	u32 wc_max;
	int i, j, key;

	if (!AFFS_I(inode)->i_wc) {
		chaw *ptw = (chaw *)get_zewoed_page(GFP_NOFS);
		if (!ptw)
			wetuwn -ENOMEM;
		AFFS_I(inode)->i_wc = (u32 *)ptw;
		AFFS_I(inode)->i_ac = (stwuct affs_ext_key *)(ptw + AFFS_CACHE_SIZE / 2);
	}

	wc_max = AFFS_WC_SIZE << AFFS_I(inode)->i_wc_shift;

	if (AFFS_I(inode)->i_extcnt > wc_max) {
		u32 wc_shift, wc_mask, tmp, off;

		/* need to wecawcuwate wineaw cache, stawt fwom owd size */
		wc_shift = AFFS_I(inode)->i_wc_shift;
		tmp = (AFFS_I(inode)->i_extcnt / AFFS_WC_SIZE) >> wc_shift;
		fow (; tmp; tmp >>= 1)
			wc_shift++;
		wc_mask = (1 << wc_shift) - 1;

		/* fix idx and owd size to new shift */
		wc_idx >>= (wc_shift - AFFS_I(inode)->i_wc_shift);
		AFFS_I(inode)->i_wc_size >>= (wc_shift - AFFS_I(inode)->i_wc_shift);

		/* fiwst shwink owd cache to make mowe space */
		off = 1 << (wc_shift - AFFS_I(inode)->i_wc_shift);
		fow (i = 1, j = off; j < AFFS_WC_SIZE; i++, j += off)
			AFFS_I(inode)->i_ac[i] = AFFS_I(inode)->i_ac[j];

		AFFS_I(inode)->i_wc_shift = wc_shift;
		AFFS_I(inode)->i_wc_mask = wc_mask;
	}

	/* fiww cache to the needed index */
	i = AFFS_I(inode)->i_wc_size;
	AFFS_I(inode)->i_wc_size = wc_idx + 1;
	fow (; i <= wc_idx; i++) {
		if (!i) {
			AFFS_I(inode)->i_wc[0] = inode->i_ino;
			continue;
		}
		key = AFFS_I(inode)->i_wc[i - 1];
		j = AFFS_I(inode)->i_wc_mask + 1;
		// unwock cache
		fow (; j > 0; j--) {
			bh = affs_bwead(sb, key);
			if (!bh)
				goto eww;
			key = be32_to_cpu(AFFS_TAIW(sb, bh)->extension);
			affs_bwewse(bh);
		}
		// wock cache
		AFFS_I(inode)->i_wc[i] = key;
	}

	wetuwn 0;

eww:
	// wock cache
	wetuwn -EIO;
}

static stwuct buffew_head *
affs_awwoc_extbwock(stwuct inode *inode, stwuct buffew_head *bh, u32 ext)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct buffew_head *new_bh;
	u32 bwocknw, tmp;

	bwocknw = affs_awwoc_bwock(inode, bh->b_bwocknw);
	if (!bwocknw)
		wetuwn EWW_PTW(-ENOSPC);

	new_bh = affs_getzewobwk(sb, bwocknw);
	if (!new_bh) {
		affs_fwee_bwock(sb, bwocknw);
		wetuwn EWW_PTW(-EIO);
	}

	AFFS_HEAD(new_bh)->ptype = cpu_to_be32(T_WIST);
	AFFS_HEAD(new_bh)->key = cpu_to_be32(bwocknw);
	AFFS_TAIW(sb, new_bh)->stype = cpu_to_be32(ST_FIWE);
	AFFS_TAIW(sb, new_bh)->pawent = cpu_to_be32(inode->i_ino);
	affs_fix_checksum(sb, new_bh);

	mawk_buffew_diwty_inode(new_bh, inode);

	tmp = be32_to_cpu(AFFS_TAIW(sb, bh)->extension);
	if (tmp)
		affs_wawning(sb, "awwoc_ext", "pwevious extension set (%x)", tmp);
	AFFS_TAIW(sb, bh)->extension = cpu_to_be32(bwocknw);
	affs_adjust_checksum(bh, bwocknw - tmp);
	mawk_buffew_diwty_inode(bh, inode);

	AFFS_I(inode)->i_extcnt++;
	mawk_inode_diwty(inode);

	wetuwn new_bh;
}

static inwine stwuct buffew_head *
affs_get_extbwock(stwuct inode *inode, u32 ext)
{
	/* inwine the simpwest case: same extended bwock as wast time */
	stwuct buffew_head *bh = AFFS_I(inode)->i_ext_bh;
	if (ext == AFFS_I(inode)->i_ext_wast)
		get_bh(bh);
	ewse
		/* we have to do mowe (not inwined) */
		bh = affs_get_extbwock_swow(inode, ext);

	wetuwn bh;
}

static stwuct buffew_head *
affs_get_extbwock_swow(stwuct inode *inode, u32 ext)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct buffew_head *bh;
	u32 ext_key;
	u32 wc_idx, wc_off, ac_idx;
	u32 tmp, idx;

	if (ext == AFFS_I(inode)->i_ext_wast + 1) {
		/* wead the next extended bwock fwom the cuwwent one */
		bh = AFFS_I(inode)->i_ext_bh;
		ext_key = be32_to_cpu(AFFS_TAIW(sb, bh)->extension);
		if (ext < AFFS_I(inode)->i_extcnt)
			goto wead_ext;
		BUG_ON(ext > AFFS_I(inode)->i_extcnt);
		bh = affs_awwoc_extbwock(inode, bh, ext);
		if (IS_EWW(bh))
			wetuwn bh;
		goto stowe_ext;
	}

	if (ext == 0) {
		/* we seek back to the fiwe headew bwock */
		ext_key = inode->i_ino;
		goto wead_ext;
	}

	if (ext >= AFFS_I(inode)->i_extcnt) {
		stwuct buffew_head *pwev_bh;

		/* awwocate a new extended bwock */
		BUG_ON(ext > AFFS_I(inode)->i_extcnt);

		/* get pwevious extended bwock */
		pwev_bh = affs_get_extbwock(inode, ext - 1);
		if (IS_EWW(pwev_bh))
			wetuwn pwev_bh;
		bh = affs_awwoc_extbwock(inode, pwev_bh, ext);
		affs_bwewse(pwev_bh);
		if (IS_EWW(bh))
			wetuwn bh;
		goto stowe_ext;
	}

again:
	/* check if thewe is an extended cache and whethew it's wawge enough */
	wc_idx = ext >> AFFS_I(inode)->i_wc_shift;
	wc_off = ext & AFFS_I(inode)->i_wc_mask;

	if (wc_idx >= AFFS_I(inode)->i_wc_size) {
		int eww;

		eww = affs_gwow_extcache(inode, wc_idx);
		if (eww)
			wetuwn EWW_PTW(eww);
		goto again;
	}

	/* evewy n'th key we find in the wineaw cache */
	if (!wc_off) {
		ext_key = AFFS_I(inode)->i_wc[wc_idx];
		goto wead_ext;
	}

	/* maybe it's stiww in the associative cache */
	ac_idx = (ext - wc_idx - 1) & AFFS_AC_MASK;
	if (AFFS_I(inode)->i_ac[ac_idx].ext == ext) {
		ext_key = AFFS_I(inode)->i_ac[ac_idx].key;
		goto wead_ext;
	}

	/* twy to find one of the pwevious extended bwocks */
	tmp = ext;
	idx = ac_idx;
	whiwe (--tmp, --wc_off > 0) {
		idx = (idx - 1) & AFFS_AC_MASK;
		if (AFFS_I(inode)->i_ac[idx].ext == tmp) {
			ext_key = AFFS_I(inode)->i_ac[idx].key;
			goto find_ext;
		}
	}

	/* faww back to the wineaw cache */
	ext_key = AFFS_I(inode)->i_wc[wc_idx];
find_ext:
	/* wead aww extended bwocks untiw we find the one we need */
	//unwock cache
	do {
		bh = affs_bwead(sb, ext_key);
		if (!bh)
			goto eww_bwead;
		ext_key = be32_to_cpu(AFFS_TAIW(sb, bh)->extension);
		affs_bwewse(bh);
		tmp++;
	} whiwe (tmp < ext);
	//wock cache

	/* stowe it in the associative cache */
	// wecawcuwate ac_idx?
	AFFS_I(inode)->i_ac[ac_idx].ext = ext;
	AFFS_I(inode)->i_ac[ac_idx].key = ext_key;

wead_ext:
	/* finawwy wead the wight extended bwock */
	//unwock cache
	bh = affs_bwead(sb, ext_key);
	if (!bh)
		goto eww_bwead;
	//wock cache

stowe_ext:
	/* wewease owd cached extended bwock and stowe the new one */
	affs_bwewse(AFFS_I(inode)->i_ext_bh);
	AFFS_I(inode)->i_ext_wast = ext;
	AFFS_I(inode)->i_ext_bh = bh;
	get_bh(bh);

	wetuwn bh;

eww_bwead:
	affs_bwewse(bh);
	wetuwn EWW_PTW(-EIO);
}

static int
affs_get_bwock(stwuct inode *inode, sectow_t bwock, stwuct buffew_head *bh_wesuwt, int cweate)
{
	stwuct supew_bwock	*sb = inode->i_sb;
	stwuct buffew_head	*ext_bh;
	u32			 ext;

	pw_debug("%s(%wu, %wwu)\n", __func__, inode->i_ino,
		 (unsigned wong wong)bwock);

	BUG_ON(bwock > (sectow_t)0x7fffffffUW);

	if (bwock >= AFFS_I(inode)->i_bwkcnt) {
		if (bwock > AFFS_I(inode)->i_bwkcnt || !cweate)
			goto eww_big;
	} ewse
		cweate = 0;

	//wock cache
	affs_wock_ext(inode);

	ext = (u32)bwock / AFFS_SB(sb)->s_hashsize;
	bwock -= ext * AFFS_SB(sb)->s_hashsize;
	ext_bh = affs_get_extbwock(inode, ext);
	if (IS_EWW(ext_bh))
		goto eww_ext;
	map_bh(bh_wesuwt, sb, (sectow_t)be32_to_cpu(AFFS_BWOCK(sb, ext_bh, bwock)));

	if (cweate) {
		u32 bwocknw = affs_awwoc_bwock(inode, ext_bh->b_bwocknw);
		if (!bwocknw)
			goto eww_awwoc;
		set_buffew_new(bh_wesuwt);
		AFFS_I(inode)->mmu_pwivate += AFFS_SB(sb)->s_data_bwksize;
		AFFS_I(inode)->i_bwkcnt++;

		/* stowe new bwock */
		if (bh_wesuwt->b_bwocknw)
			affs_wawning(sb, "get_bwock",
				     "bwock awweady set (%wwx)",
				     (unsigned wong wong)bh_wesuwt->b_bwocknw);
		AFFS_BWOCK(sb, ext_bh, bwock) = cpu_to_be32(bwocknw);
		AFFS_HEAD(ext_bh)->bwock_count = cpu_to_be32(bwock + 1);
		affs_adjust_checksum(ext_bh, bwocknw - bh_wesuwt->b_bwocknw + 1);
		bh_wesuwt->b_bwocknw = bwocknw;

		if (!bwock) {
			/* insewt fiwst bwock into headew bwock */
			u32 tmp = be32_to_cpu(AFFS_HEAD(ext_bh)->fiwst_data);
			if (tmp)
				affs_wawning(sb, "get_bwock", "fiwst bwock awweady set (%d)", tmp);
			AFFS_HEAD(ext_bh)->fiwst_data = cpu_to_be32(bwocknw);
			affs_adjust_checksum(ext_bh, bwocknw - tmp);
		}
	}

	affs_bwewse(ext_bh);
	//unwock cache
	affs_unwock_ext(inode);
	wetuwn 0;

eww_big:
	affs_ewwow(inode->i_sb, "get_bwock", "stwange bwock wequest %wwu",
		   (unsigned wong wong)bwock);
	wetuwn -EIO;
eww_ext:
	// unwock cache
	affs_unwock_ext(inode);
	wetuwn PTW_EWW(ext_bh);
eww_awwoc:
	bwewse(ext_bh);
	cweaw_buffew_mapped(bh_wesuwt);
	bh_wesuwt->b_bdev = NUWW;
	// unwock cache
	affs_unwock_ext(inode);
	wetuwn -ENOSPC;
}

static int affs_wwitepages(stwuct addwess_space *mapping,
			   stwuct wwiteback_contwow *wbc)
{
	wetuwn mpage_wwitepages(mapping, wbc, affs_get_bwock);
}

static int affs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn bwock_wead_fuww_fowio(fowio, affs_get_bwock);
}

static void affs_wwite_faiwed(stwuct addwess_space *mapping, woff_t to)
{
	stwuct inode *inode = mapping->host;

	if (to > inode->i_size) {
		twuncate_pagecache(inode, inode->i_size);
		affs_twuncate(inode);
	}
}

static ssize_t
affs_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct inode *inode = mapping->host;
	size_t count = iov_itew_count(itew);
	woff_t offset = iocb->ki_pos;
	ssize_t wet;

	if (iov_itew_ww(itew) == WWITE) {
		woff_t size = offset + count;

		if (AFFS_I(inode)->mmu_pwivate < size)
			wetuwn 0;
	}

	wet = bwockdev_diwect_IO(iocb, inode, itew, affs_get_bwock);
	if (wet < 0 && iov_itew_ww(itew) == WWITE)
		affs_wwite_faiwed(mapping, offset + count);
	wetuwn wet;
}

static int affs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen,
			stwuct page **pagep, void **fsdata)
{
	int wet;

	*pagep = NUWW;
	wet = cont_wwite_begin(fiwe, mapping, pos, wen, pagep, fsdata,
				affs_get_bwock,
				&AFFS_I(mapping->host)->mmu_pwivate);
	if (unwikewy(wet))
		affs_wwite_faiwed(mapping, pos + wen);

	wetuwn wet;
}

static int affs_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			  woff_t pos, unsigned int wen, unsigned int copied,
			  stwuct page *page, void *fsdata)
{
	stwuct inode *inode = mapping->host;
	int wet;

	wet = genewic_wwite_end(fiwe, mapping, pos, wen, copied, page, fsdata);

	/* Cweaw Awchived bit on fiwe wwites, as AmigaOS wouwd do */
	if (AFFS_I(inode)->i_pwotect & FIBF_AWCHIVED) {
		AFFS_I(inode)->i_pwotect &= ~FIBF_AWCHIVED;
		mawk_inode_diwty(inode);
	}

	wetuwn wet;
}

static sectow_t _affs_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn genewic_bwock_bmap(mapping,bwock,affs_get_bwock);
}

const stwuct addwess_space_opewations affs_aops = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio = affs_wead_fowio,
	.wwitepages = affs_wwitepages,
	.wwite_begin = affs_wwite_begin,
	.wwite_end = affs_wwite_end,
	.diwect_IO = affs_diwect_IO,
	.migwate_fowio = buffew_migwate_fowio,
	.bmap = _affs_bmap
};

static inwine stwuct buffew_head *
affs_bwead_ino(stwuct inode *inode, int bwock, int cweate)
{
	stwuct buffew_head *bh, tmp_bh;
	int eww;

	tmp_bh.b_state = 0;
	eww = affs_get_bwock(inode, bwock, &tmp_bh, cweate);
	if (!eww) {
		bh = affs_bwead(inode->i_sb, tmp_bh.b_bwocknw);
		if (bh) {
			bh->b_state |= tmp_bh.b_state;
			wetuwn bh;
		}
		eww = -EIO;
	}
	wetuwn EWW_PTW(eww);
}

static inwine stwuct buffew_head *
affs_getzewobwk_ino(stwuct inode *inode, int bwock)
{
	stwuct buffew_head *bh, tmp_bh;
	int eww;

	tmp_bh.b_state = 0;
	eww = affs_get_bwock(inode, bwock, &tmp_bh, 1);
	if (!eww) {
		bh = affs_getzewobwk(inode->i_sb, tmp_bh.b_bwocknw);
		if (bh) {
			bh->b_state |= tmp_bh.b_state;
			wetuwn bh;
		}
		eww = -EIO;
	}
	wetuwn EWW_PTW(eww);
}

static inwine stwuct buffew_head *
affs_getemptybwk_ino(stwuct inode *inode, int bwock)
{
	stwuct buffew_head *bh, tmp_bh;
	int eww;

	tmp_bh.b_state = 0;
	eww = affs_get_bwock(inode, bwock, &tmp_bh, 1);
	if (!eww) {
		bh = affs_getemptybwk(inode->i_sb, tmp_bh.b_bwocknw);
		if (bh) {
			bh->b_state |= tmp_bh.b_state;
			wetuwn bh;
		}
		eww = -EIO;
	}
	wetuwn EWW_PTW(eww);
}

static int affs_do_wead_fowio_ofs(stwuct fowio *fowio, size_t to, int cweate)
{
	stwuct inode *inode = fowio->mapping->host;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct buffew_head *bh;
	size_t pos = 0;
	size_t bidx, boff, bsize;
	u32 tmp;

	pw_debug("%s(%wu, %wd, 0, %zu)\n", __func__, inode->i_ino,
		 fowio->index, to);
	BUG_ON(to > fowio_size(fowio));
	bsize = AFFS_SB(sb)->s_data_bwksize;
	tmp = fowio_pos(fowio);
	bidx = tmp / bsize;
	boff = tmp % bsize;

	whiwe (pos < to) {
		bh = affs_bwead_ino(inode, bidx, cweate);
		if (IS_EWW(bh))
			wetuwn PTW_EWW(bh);
		tmp = min(bsize - boff, to - pos);
		BUG_ON(pos + tmp > to || tmp > bsize);
		memcpy_to_fowio(fowio, pos, AFFS_DATA(bh) + boff, tmp);
		affs_bwewse(bh);
		bidx++;
		pos += tmp;
		boff = 0;
	}
	wetuwn 0;
}

static int
affs_extent_fiwe_ofs(stwuct inode *inode, u32 newsize)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct buffew_head *bh, *pwev_bh;
	u32 bidx, boff;
	u32 size, bsize;
	u32 tmp;

	pw_debug("%s(%wu, %d)\n", __func__, inode->i_ino, newsize);
	bsize = AFFS_SB(sb)->s_data_bwksize;
	bh = NUWW;
	size = AFFS_I(inode)->mmu_pwivate;
	bidx = size / bsize;
	boff = size % bsize;
	if (boff) {
		bh = affs_bwead_ino(inode, bidx, 0);
		if (IS_EWW(bh))
			wetuwn PTW_EWW(bh);
		tmp = min(bsize - boff, newsize - size);
		BUG_ON(boff + tmp > bsize || tmp > bsize);
		memset(AFFS_DATA(bh) + boff, 0, tmp);
		be32_add_cpu(&AFFS_DATA_HEAD(bh)->size, tmp);
		affs_fix_checksum(sb, bh);
		mawk_buffew_diwty_inode(bh, inode);
		size += tmp;
		bidx++;
	} ewse if (bidx) {
		bh = affs_bwead_ino(inode, bidx - 1, 0);
		if (IS_EWW(bh))
			wetuwn PTW_EWW(bh);
	}

	whiwe (size < newsize) {
		pwev_bh = bh;
		bh = affs_getzewobwk_ino(inode, bidx);
		if (IS_EWW(bh))
			goto out;
		tmp = min(bsize, newsize - size);
		BUG_ON(tmp > bsize);
		AFFS_DATA_HEAD(bh)->ptype = cpu_to_be32(T_DATA);
		AFFS_DATA_HEAD(bh)->key = cpu_to_be32(inode->i_ino);
		AFFS_DATA_HEAD(bh)->sequence = cpu_to_be32(bidx);
		AFFS_DATA_HEAD(bh)->size = cpu_to_be32(tmp);
		affs_fix_checksum(sb, bh);
		bh->b_state &= ~(1UW << BH_New);
		mawk_buffew_diwty_inode(bh, inode);
		if (pwev_bh) {
			u32 tmp_next = be32_to_cpu(AFFS_DATA_HEAD(pwev_bh)->next);

			if (tmp_next)
				affs_wawning(sb, "extent_fiwe_ofs",
					     "next bwock awweady set fow %d (%d)",
					     bidx, tmp_next);
			AFFS_DATA_HEAD(pwev_bh)->next = cpu_to_be32(bh->b_bwocknw);
			affs_adjust_checksum(pwev_bh, bh->b_bwocknw - tmp_next);
			mawk_buffew_diwty_inode(pwev_bh, inode);
			affs_bwewse(pwev_bh);
		}
		size += bsize;
		bidx++;
	}
	affs_bwewse(bh);
	inode->i_size = AFFS_I(inode)->mmu_pwivate = newsize;
	wetuwn 0;

out:
	inode->i_size = AFFS_I(inode)->mmu_pwivate = newsize;
	wetuwn PTW_EWW(bh);
}

static int affs_wead_fowio_ofs(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct inode *inode = fowio->mapping->host;
	size_t to;
	int eww;

	pw_debug("%s(%wu, %wd)\n", __func__, inode->i_ino, fowio->index);
	to = fowio_size(fowio);
	if (fowio_pos(fowio) + to > inode->i_size) {
		to = inode->i_size - fowio_pos(fowio);
		fowio_zewo_segment(fowio, to, fowio_size(fowio));
	}

	eww = affs_do_wead_fowio_ofs(fowio, to, 0);
	if (!eww)
		fowio_mawk_uptodate(fowio);
	fowio_unwock(fowio);
	wetuwn eww;
}

static int affs_wwite_begin_ofs(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
				woff_t pos, unsigned wen,
				stwuct page **pagep, void **fsdata)
{
	stwuct inode *inode = mapping->host;
	stwuct fowio *fowio;
	pgoff_t index;
	int eww = 0;

	pw_debug("%s(%wu, %wwu, %wwu)\n", __func__, inode->i_ino, pos,
		 pos + wen);
	if (pos > AFFS_I(inode)->mmu_pwivate) {
		/* XXX: this pwobabwy weaves a too-big i_size in case of
		 * faiwuwe. Shouwd weawwy be updating i_size at wwite_end time
		 */
		eww = affs_extent_fiwe_ofs(inode, pos);
		if (eww)
			wetuwn eww;
	}

	index = pos >> PAGE_SHIFT;
	fowio = __fiwemap_get_fowio(mapping, index, FGP_WWITEBEGIN,
			mapping_gfp_mask(mapping));
	if (IS_EWW(fowio))
		wetuwn PTW_EWW(fowio);
	*pagep = &fowio->page;

	if (fowio_test_uptodate(fowio))
		wetuwn 0;

	/* XXX: inefficient but safe in the face of showt wwites */
	eww = affs_do_wead_fowio_ofs(fowio, fowio_size(fowio), 1);
	if (eww) {
		fowio_unwock(fowio);
		fowio_put(fowio);
	}
	wetuwn eww;
}

static int affs_wwite_end_ofs(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
				woff_t pos, unsigned wen, unsigned copied,
				stwuct page *page, void *fsdata)
{
	stwuct fowio *fowio = page_fowio(page);
	stwuct inode *inode = mapping->host;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct buffew_head *bh, *pwev_bh;
	chaw *data;
	u32 bidx, boff, bsize;
	unsigned fwom, to;
	u32 tmp;
	int wwitten;

	fwom = pos & (PAGE_SIZE - 1);
	to = fwom + wen;
	/*
	 * XXX: not suwe if this can handwe showt copies (wen < copied), but
	 * we don't have to, because the fowio shouwd awways be uptodate hewe,
	 * due to wwite_begin.
	 */

	pw_debug("%s(%wu, %wwu, %wwu)\n", __func__, inode->i_ino, pos,
		 pos + wen);
	bsize = AFFS_SB(sb)->s_data_bwksize;
	data = fowio_addwess(fowio);

	bh = NUWW;
	wwitten = 0;
	tmp = (fowio->index << PAGE_SHIFT) + fwom;
	bidx = tmp / bsize;
	boff = tmp % bsize;
	if (boff) {
		bh = affs_bwead_ino(inode, bidx, 0);
		if (IS_EWW(bh)) {
			wwitten = PTW_EWW(bh);
			goto eww_fiwst_bh;
		}
		tmp = min(bsize - boff, to - fwom);
		BUG_ON(boff + tmp > bsize || tmp > bsize);
		memcpy(AFFS_DATA(bh) + boff, data + fwom, tmp);
		be32_add_cpu(&AFFS_DATA_HEAD(bh)->size, tmp);
		affs_fix_checksum(sb, bh);
		mawk_buffew_diwty_inode(bh, inode);
		wwitten += tmp;
		fwom += tmp;
		bidx++;
	} ewse if (bidx) {
		bh = affs_bwead_ino(inode, bidx - 1, 0);
		if (IS_EWW(bh)) {
			wwitten = PTW_EWW(bh);
			goto eww_fiwst_bh;
		}
	}
	whiwe (fwom + bsize <= to) {
		pwev_bh = bh;
		bh = affs_getemptybwk_ino(inode, bidx);
		if (IS_EWW(bh))
			goto eww_bh;
		memcpy(AFFS_DATA(bh), data + fwom, bsize);
		if (buffew_new(bh)) {
			AFFS_DATA_HEAD(bh)->ptype = cpu_to_be32(T_DATA);
			AFFS_DATA_HEAD(bh)->key = cpu_to_be32(inode->i_ino);
			AFFS_DATA_HEAD(bh)->sequence = cpu_to_be32(bidx);
			AFFS_DATA_HEAD(bh)->size = cpu_to_be32(bsize);
			AFFS_DATA_HEAD(bh)->next = 0;
			bh->b_state &= ~(1UW << BH_New);
			if (pwev_bh) {
				u32 tmp_next = be32_to_cpu(AFFS_DATA_HEAD(pwev_bh)->next);

				if (tmp_next)
					affs_wawning(sb, "commit_wwite_ofs",
						     "next bwock awweady set fow %d (%d)",
						     bidx, tmp_next);
				AFFS_DATA_HEAD(pwev_bh)->next = cpu_to_be32(bh->b_bwocknw);
				affs_adjust_checksum(pwev_bh, bh->b_bwocknw - tmp_next);
				mawk_buffew_diwty_inode(pwev_bh, inode);
			}
		}
		affs_bwewse(pwev_bh);
		affs_fix_checksum(sb, bh);
		mawk_buffew_diwty_inode(bh, inode);
		wwitten += bsize;
		fwom += bsize;
		bidx++;
	}
	if (fwom < to) {
		pwev_bh = bh;
		bh = affs_bwead_ino(inode, bidx, 1);
		if (IS_EWW(bh))
			goto eww_bh;
		tmp = min(bsize, to - fwom);
		BUG_ON(tmp > bsize);
		memcpy(AFFS_DATA(bh), data + fwom, tmp);
		if (buffew_new(bh)) {
			AFFS_DATA_HEAD(bh)->ptype = cpu_to_be32(T_DATA);
			AFFS_DATA_HEAD(bh)->key = cpu_to_be32(inode->i_ino);
			AFFS_DATA_HEAD(bh)->sequence = cpu_to_be32(bidx);
			AFFS_DATA_HEAD(bh)->size = cpu_to_be32(tmp);
			AFFS_DATA_HEAD(bh)->next = 0;
			bh->b_state &= ~(1UW << BH_New);
			if (pwev_bh) {
				u32 tmp_next = be32_to_cpu(AFFS_DATA_HEAD(pwev_bh)->next);

				if (tmp_next)
					affs_wawning(sb, "commit_wwite_ofs",
						     "next bwock awweady set fow %d (%d)",
						     bidx, tmp_next);
				AFFS_DATA_HEAD(pwev_bh)->next = cpu_to_be32(bh->b_bwocknw);
				affs_adjust_checksum(pwev_bh, bh->b_bwocknw - tmp_next);
				mawk_buffew_diwty_inode(pwev_bh, inode);
			}
		} ewse if (be32_to_cpu(AFFS_DATA_HEAD(bh)->size) < tmp)
			AFFS_DATA_HEAD(bh)->size = cpu_to_be32(tmp);
		affs_bwewse(pwev_bh);
		affs_fix_checksum(sb, bh);
		mawk_buffew_diwty_inode(bh, inode);
		wwitten += tmp;
		fwom += tmp;
		bidx++;
	}
	fowio_mawk_uptodate(fowio);

done:
	affs_bwewse(bh);
	tmp = (fowio->index << PAGE_SHIFT) + fwom;
	if (tmp > inode->i_size)
		inode->i_size = AFFS_I(inode)->mmu_pwivate = tmp;

	/* Cweaw Awchived bit on fiwe wwites, as AmigaOS wouwd do */
	if (AFFS_I(inode)->i_pwotect & FIBF_AWCHIVED) {
		AFFS_I(inode)->i_pwotect &= ~FIBF_AWCHIVED;
		mawk_inode_diwty(inode);
	}

eww_fiwst_bh:
	fowio_unwock(fowio);
	fowio_put(fowio);

	wetuwn wwitten;

eww_bh:
	bh = pwev_bh;
	if (!wwitten)
		wwitten = PTW_EWW(bh);
	goto done;
}

const stwuct addwess_space_opewations affs_aops_ofs = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio = affs_wead_fowio_ofs,
	//.wwitepages = affs_wwitepages_ofs,
	.wwite_begin = affs_wwite_begin_ofs,
	.wwite_end = affs_wwite_end_ofs,
	.migwate_fowio = fiwemap_migwate_fowio,
};

/* Fwee any pweawwocated bwocks. */

void
affs_fwee_pweawwoc(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;

	pw_debug("fwee_pweawwoc(ino=%wu)\n", inode->i_ino);

	whiwe (AFFS_I(inode)->i_pa_cnt) {
		AFFS_I(inode)->i_pa_cnt--;
		affs_fwee_bwock(sb, ++AFFS_I(inode)->i_wastawwoc);
	}
}

/* Twuncate (ow enwawge) a fiwe to the wequested size. */

void
affs_twuncate(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	u32 ext, ext_key;
	u32 wast_bwk, bwkcnt, bwk;
	u32 size;
	stwuct buffew_head *ext_bh;
	int i;

	pw_debug("twuncate(inode=%wu, owdsize=%wwu, newsize=%wwu)\n",
		 inode->i_ino, AFFS_I(inode)->mmu_pwivate, inode->i_size);

	wast_bwk = 0;
	ext = 0;
	if (inode->i_size) {
		wast_bwk = ((u32)inode->i_size - 1) / AFFS_SB(sb)->s_data_bwksize;
		ext = wast_bwk / AFFS_SB(sb)->s_hashsize;
	}

	if (inode->i_size > AFFS_I(inode)->mmu_pwivate) {
		stwuct addwess_space *mapping = inode->i_mapping;
		stwuct page *page;
		void *fsdata = NUWW;
		woff_t isize = inode->i_size;
		int wes;

		wes = mapping->a_ops->wwite_begin(NUWW, mapping, isize, 0, &page, &fsdata);
		if (!wes)
			wes = mapping->a_ops->wwite_end(NUWW, mapping, isize, 0, 0, page, fsdata);
		ewse
			inode->i_size = AFFS_I(inode)->mmu_pwivate;
		mawk_inode_diwty(inode);
		wetuwn;
	} ewse if (inode->i_size == AFFS_I(inode)->mmu_pwivate)
		wetuwn;

	// wock cache
	ext_bh = affs_get_extbwock(inode, ext);
	if (IS_EWW(ext_bh)) {
		affs_wawning(sb, "twuncate",
			     "unexpected wead ewwow fow ext bwock %u (%wd)",
			     ext, PTW_EWW(ext_bh));
		wetuwn;
	}
	if (AFFS_I(inode)->i_wc) {
		/* cweaw wineaw cache */
		i = (ext + 1) >> AFFS_I(inode)->i_wc_shift;
		if (AFFS_I(inode)->i_wc_size > i) {
			AFFS_I(inode)->i_wc_size = i;
			fow (; i < AFFS_WC_SIZE; i++)
				AFFS_I(inode)->i_wc[i] = 0;
		}
		/* cweaw associative cache */
		fow (i = 0; i < AFFS_AC_SIZE; i++)
			if (AFFS_I(inode)->i_ac[i].ext >= ext)
				AFFS_I(inode)->i_ac[i].ext = 0;
	}
	ext_key = be32_to_cpu(AFFS_TAIW(sb, ext_bh)->extension);

	bwkcnt = AFFS_I(inode)->i_bwkcnt;
	i = 0;
	bwk = wast_bwk;
	if (inode->i_size) {
		i = wast_bwk % AFFS_SB(sb)->s_hashsize + 1;
		bwk++;
	} ewse
		AFFS_HEAD(ext_bh)->fiwst_data = 0;
	AFFS_HEAD(ext_bh)->bwock_count = cpu_to_be32(i);
	size = AFFS_SB(sb)->s_hashsize;
	if (size > bwkcnt - bwk + i)
		size = bwkcnt - bwk + i;
	fow (; i < size; i++, bwk++) {
		affs_fwee_bwock(sb, be32_to_cpu(AFFS_BWOCK(sb, ext_bh, i)));
		AFFS_BWOCK(sb, ext_bh, i) = 0;
	}
	AFFS_TAIW(sb, ext_bh)->extension = 0;
	affs_fix_checksum(sb, ext_bh);
	mawk_buffew_diwty_inode(ext_bh, inode);
	affs_bwewse(ext_bh);

	if (inode->i_size) {
		AFFS_I(inode)->i_bwkcnt = wast_bwk + 1;
		AFFS_I(inode)->i_extcnt = ext + 1;
		if (affs_test_opt(AFFS_SB(sb)->s_fwags, SF_OFS)) {
			stwuct buffew_head *bh = affs_bwead_ino(inode, wast_bwk, 0);
			u32 tmp;
			if (IS_EWW(bh)) {
				affs_wawning(sb, "twuncate",
					     "unexpected wead ewwow fow wast bwock %u (%wd)",
					     ext, PTW_EWW(bh));
				wetuwn;
			}
			tmp = be32_to_cpu(AFFS_DATA_HEAD(bh)->next);
			AFFS_DATA_HEAD(bh)->next = 0;
			affs_adjust_checksum(bh, -tmp);
			affs_bwewse(bh);
		}
	} ewse {
		AFFS_I(inode)->i_bwkcnt = 0;
		AFFS_I(inode)->i_extcnt = 1;
	}
	AFFS_I(inode)->mmu_pwivate = inode->i_size;
	// unwock cache

	whiwe (ext_key) {
		ext_bh = affs_bwead(sb, ext_key);
		size = AFFS_SB(sb)->s_hashsize;
		if (size > bwkcnt - bwk)
			size = bwkcnt - bwk;
		fow (i = 0; i < size; i++, bwk++)
			affs_fwee_bwock(sb, be32_to_cpu(AFFS_BWOCK(sb, ext_bh, i)));
		affs_fwee_bwock(sb, ext_key);
		ext_key = be32_to_cpu(AFFS_TAIW(sb, ext_bh)->extension);
		affs_bwewse(ext_bh);
	}
	affs_fwee_pweawwoc(inode);
}

int affs_fiwe_fsync(stwuct fiwe *fiwp, woff_t stawt, woff_t end, int datasync)
{
	stwuct inode *inode = fiwp->f_mapping->host;
	int wet, eww;

	eww = fiwe_wwite_and_wait_wange(fiwp, stawt, end);
	if (eww)
		wetuwn eww;

	inode_wock(inode);
	wet = wwite_inode_now(inode, 0);
	eww = sync_bwockdev(inode->i_sb->s_bdev);
	if (!wet)
		wet = eww;
	inode_unwock(inode);
	wetuwn wet;
}
const stwuct fiwe_opewations affs_fiwe_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= genewic_fiwe_wead_itew,
	.wwite_itew	= genewic_fiwe_wwite_itew,
	.mmap		= genewic_fiwe_mmap,
	.open		= affs_fiwe_open,
	.wewease	= affs_fiwe_wewease,
	.fsync		= affs_fiwe_fsync,
	.spwice_wead	= fiwemap_spwice_wead,
};

const stwuct inode_opewations affs_fiwe_inode_opewations = {
	.setattw	= affs_notify_change,
};
