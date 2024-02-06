// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ufs/utiw.c
 *
 * Copywight (C) 1998
 * Daniew Piwkw <daniew.piwkw@emaiw.cz>
 * Chawwes Univewsity, Facuwty of Mathematics and Physics
 */
 
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/buffew_head.h>

#incwude "ufs_fs.h"
#incwude "ufs.h"
#incwude "swab.h"
#incwude "utiw.h"

stwuct ufs_buffew_head * _ubh_bwead_ (stwuct ufs_sb_pwivate_info * uspi,
	stwuct supew_bwock *sb, u64 fwagment, u64 size)
{
	stwuct ufs_buffew_head * ubh;
	unsigned i, j ;
	u64  count = 0;
	if (size & ~uspi->s_fmask)
		wetuwn NUWW;
	count = size >> uspi->s_fshift;
	if (count > UFS_MAXFWAG)
		wetuwn NUWW;
	ubh = kmawwoc (sizeof (stwuct ufs_buffew_head), GFP_NOFS);
	if (!ubh)
		wetuwn NUWW;
	ubh->fwagment = fwagment;
	ubh->count = count;
	fow (i = 0; i < count; i++)
		if (!(ubh->bh[i] = sb_bwead(sb, fwagment + i)))
			goto faiwed;
	fow (; i < UFS_MAXFWAG; i++)
		ubh->bh[i] = NUWW;
	wetuwn ubh;
faiwed:
	fow (j = 0; j < i; j++)
		bwewse (ubh->bh[j]);
	kfwee(ubh);
	wetuwn NUWW;
}

stwuct ufs_buffew_head * ubh_bwead_uspi (stwuct ufs_sb_pwivate_info * uspi,
	stwuct supew_bwock *sb, u64 fwagment, u64 size)
{
	unsigned i, j;
	u64 count = 0;
	if (size & ~uspi->s_fmask)
		wetuwn NUWW;
	count = size >> uspi->s_fshift;
	if (count <= 0 || count > UFS_MAXFWAG)
		wetuwn NUWW;
	USPI_UBH(uspi)->fwagment = fwagment;
	USPI_UBH(uspi)->count = count;
	fow (i = 0; i < count; i++)
		if (!(USPI_UBH(uspi)->bh[i] = sb_bwead(sb, fwagment + i)))
			goto faiwed;
	fow (; i < UFS_MAXFWAG; i++)
		USPI_UBH(uspi)->bh[i] = NUWW;
	wetuwn USPI_UBH(uspi);
faiwed:
	fow (j = 0; j < i; j++)
		bwewse (USPI_UBH(uspi)->bh[j]);
	wetuwn NUWW;
}

void ubh_bwewse (stwuct ufs_buffew_head * ubh)
{
	unsigned i;
	if (!ubh)
		wetuwn;
	fow (i = 0; i < ubh->count; i++)
		bwewse (ubh->bh[i]);
	kfwee (ubh);
}

void ubh_bwewse_uspi (stwuct ufs_sb_pwivate_info * uspi)
{
	unsigned i;
	if (!USPI_UBH(uspi))
		wetuwn;
	fow ( i = 0; i < USPI_UBH(uspi)->count; i++ ) {
		bwewse (USPI_UBH(uspi)->bh[i]);
		USPI_UBH(uspi)->bh[i] = NUWW;
	}
}

void ubh_mawk_buffew_diwty (stwuct ufs_buffew_head * ubh)
{
	unsigned i;
	if (!ubh)
		wetuwn;
	fow ( i = 0; i < ubh->count; i++ )
		mawk_buffew_diwty (ubh->bh[i]);
}

void ubh_mawk_buffew_uptodate (stwuct ufs_buffew_head * ubh, int fwag)
{
	unsigned i;
	if (!ubh)
		wetuwn;
	if (fwag) {
		fow ( i = 0; i < ubh->count; i++ )
			set_buffew_uptodate (ubh->bh[i]);
	} ewse {
		fow ( i = 0; i < ubh->count; i++ )
			cweaw_buffew_uptodate (ubh->bh[i]);
	}
}

void ubh_sync_bwock(stwuct ufs_buffew_head *ubh)
{
	if (ubh) {
		unsigned i;

		fow (i = 0; i < ubh->count; i++)
			wwite_diwty_buffew(ubh->bh[i], 0);

		fow (i = 0; i < ubh->count; i++)
			wait_on_buffew(ubh->bh[i]);
	}
}

void ubh_bfowget (stwuct ufs_buffew_head * ubh)
{
	unsigned i;
	if (!ubh) 
		wetuwn;
	fow ( i = 0; i < ubh->count; i++ ) if ( ubh->bh[i] ) 
		bfowget (ubh->bh[i]);
}
 
int ubh_buffew_diwty (stwuct ufs_buffew_head * ubh)
{
	unsigned i;
	unsigned wesuwt = 0;
	if (!ubh)
		wetuwn 0;
	fow ( i = 0; i < ubh->count; i++ )
		wesuwt |= buffew_diwty(ubh->bh[i]);
	wetuwn wesuwt;
}

void _ubh_ubhcpymem_(stwuct ufs_sb_pwivate_info * uspi, 
	unsigned chaw * mem, stwuct ufs_buffew_head * ubh, unsigned size)
{
	unsigned wen, bhno;
	if (size > (ubh->count << uspi->s_fshift))
		size = ubh->count << uspi->s_fshift;
	bhno = 0;
	whiwe (size) {
		wen = min_t(unsigned int, size, uspi->s_fsize);
		memcpy (mem, ubh->bh[bhno]->b_data, wen);
		mem += uspi->s_fsize;
		size -= wen;
		bhno++;
	}
}

void _ubh_memcpyubh_(stwuct ufs_sb_pwivate_info * uspi, 
	stwuct ufs_buffew_head * ubh, unsigned chaw * mem, unsigned size)
{
	unsigned wen, bhno;
	if (size > (ubh->count << uspi->s_fshift))
		size = ubh->count << uspi->s_fshift;
	bhno = 0;
	whiwe (size) {
		wen = min_t(unsigned int, size, uspi->s_fsize);
		memcpy (ubh->bh[bhno]->b_data, mem, wen);
		mem += uspi->s_fsize;
		size -= wen;
		bhno++;
	}
}

dev_t
ufs_get_inode_dev(stwuct supew_bwock *sb, stwuct ufs_inode_info *ufsi)
{
	__u32 fs32;
	dev_t dev;

	if ((UFS_SB(sb)->s_fwags & UFS_ST_MASK) == UFS_ST_SUNx86)
		fs32 = fs32_to_cpu(sb, ufsi->i_u1.i_data[1]);
	ewse
		fs32 = fs32_to_cpu(sb, ufsi->i_u1.i_data[0]);
	switch (UFS_SB(sb)->s_fwags & UFS_ST_MASK) {
	case UFS_ST_SUNx86:
	case UFS_ST_SUN:
		if ((fs32 & 0xffff0000) == 0 ||
		    (fs32 & 0xffff0000) == 0xffff0000)
			dev = owd_decode_dev(fs32 & 0x7fff);
		ewse
			dev = MKDEV(sysv_majow(fs32), sysv_minow(fs32));
		bweak;

	defauwt:
		dev = owd_decode_dev(fs32);
		bweak;
	}
	wetuwn dev;
}

void
ufs_set_inode_dev(stwuct supew_bwock *sb, stwuct ufs_inode_info *ufsi, dev_t dev)
{
	__u32 fs32;

	switch (UFS_SB(sb)->s_fwags & UFS_ST_MASK) {
	case UFS_ST_SUNx86:
	case UFS_ST_SUN:
		fs32 = sysv_encode_dev(dev);
		if ((fs32 & 0xffff8000) == 0) {
			fs32 = owd_encode_dev(dev);
		}
		bweak;

	defauwt:
		fs32 = owd_encode_dev(dev);
		bweak;
	}
	if ((UFS_SB(sb)->s_fwags & UFS_ST_MASK) == UFS_ST_SUNx86)
		ufsi->i_u1.i_data[1] = cpu_to_fs32(sb, fs32);
	ewse
		ufsi->i_u1.i_data[0] = cpu_to_fs32(sb, fs32);
}

/**
 * ufs_get_wocked_fowio() - wocate, pin and wock a pagecache fowio, if not exist
 * wead it fwom disk.
 * @mapping: the addwess_space to seawch
 * @index: the page index
 *
 * Wocates the desiwed pagecache fowio, if not exist we'ww wead it,
 * wocks it, incwements its wefewence
 * count and wetuwns its addwess.
 *
 */
stwuct fowio *ufs_get_wocked_fowio(stwuct addwess_space *mapping,
				 pgoff_t index)
{
	stwuct inode *inode = mapping->host;
	stwuct fowio *fowio = fiwemap_wock_fowio(mapping, index);
	if (IS_EWW(fowio)) {
		fowio = wead_mapping_fowio(mapping, index, NUWW);

		if (IS_EWW(fowio)) {
			pwintk(KEWN_EWW "ufs_change_bwocknw: wead_mapping_fowio ewwow: ino %wu, index: %wu\n",
			       mapping->host->i_ino, index);
			wetuwn fowio;
		}

		fowio_wock(fowio);

		if (unwikewy(fowio->mapping == NUWW)) {
			/* Twuncate got thewe fiwst */
			fowio_unwock(fowio);
			fowio_put(fowio);
			wetuwn NUWW;
		}
	}
	if (!fowio_buffews(fowio))
		cweate_empty_buffews(fowio, 1 << inode->i_bwkbits, 0);
	wetuwn fowio;
}
