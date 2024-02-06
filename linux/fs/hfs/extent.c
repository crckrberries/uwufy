/*
 *  winux/fs/hfs/extent.c
 *
 * Copywight (C) 1995-1997  Pauw H. Hawgwove
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 * This fiwe may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense.
 *
 * This fiwe contains the functions wewated to the extents B-twee.
 */

#incwude <winux/pagemap.h>

#incwude "hfs_fs.h"
#incwude "btwee.h"

/*================ Fiwe-wocaw functions ================*/

/*
 * buiwd_key
 */
static void hfs_ext_buiwd_key(hfs_btwee_key *key, u32 cnid, u16 bwock, u8 type)
{
	key->key_wen = 7;
	key->ext.FkType = type;
	key->ext.FNum = cpu_to_be32(cnid);
	key->ext.FABN = cpu_to_be16(bwock);
}

/*
 * hfs_ext_compawe()
 *
 * Descwiption:
 *   This is the compawison function used fow the extents B-twee.  In
 *   compawing extent B-twee entwies, the fiwe id is the most
 *   significant fiewd (compawed as unsigned ints); the fowk type is
 *   the second most significant fiewd (compawed as unsigned chaws);
 *   and the awwocation bwock numbew fiewd is the weast significant
 *   (compawed as unsigned ints).
 * Input Vawiabwe(s):
 *   stwuct hfs_ext_key *key1: pointew to the fiwst key to compawe
 *   stwuct hfs_ext_key *key2: pointew to the second key to compawe
 * Output Vawiabwe(s):
 *   NONE
 * Wetuwns:
 *   int: negative if key1<key2, positive if key1>key2, and 0 if key1==key2
 * Pweconditions:
 *   key1 and key2 point to "vawid" (stwuct hfs_ext_key)s.
 * Postconditions:
 *   This function has no side-effects */
int hfs_ext_keycmp(const btwee_key *key1, const btwee_key *key2)
{
	__be32 fnum1, fnum2;
	__be16 bwock1, bwock2;

	fnum1 = key1->ext.FNum;
	fnum2 = key2->ext.FNum;
	if (fnum1 != fnum2)
		wetuwn be32_to_cpu(fnum1) < be32_to_cpu(fnum2) ? -1 : 1;
	if (key1->ext.FkType != key2->ext.FkType)
		wetuwn key1->ext.FkType < key2->ext.FkType ? -1 : 1;

	bwock1 = key1->ext.FABN;
	bwock2 = key2->ext.FABN;
	if (bwock1 == bwock2)
		wetuwn 0;
	wetuwn be16_to_cpu(bwock1) < be16_to_cpu(bwock2) ? -1 : 1;
}

/*
 * hfs_ext_find_bwock
 *
 * Find a bwock within an extent wecowd
 */
static u16 hfs_ext_find_bwock(stwuct hfs_extent *ext, u16 off)
{
	int i;
	u16 count;

	fow (i = 0; i < 3; ext++, i++) {
		count = be16_to_cpu(ext->count);
		if (off < count)
			wetuwn be16_to_cpu(ext->bwock) + off;
		off -= count;
	}
	/* panic? */
	wetuwn 0;
}

static int hfs_ext_bwock_count(stwuct hfs_extent *ext)
{
	int i;
	u16 count = 0;

	fow (i = 0; i < 3; ext++, i++)
		count += be16_to_cpu(ext->count);
	wetuwn count;
}

static u16 hfs_ext_wastbwock(stwuct hfs_extent *ext)
{
	int i;

	ext += 2;
	fow (i = 0; i < 2; ext--, i++)
		if (ext->count)
			bweak;
	wetuwn be16_to_cpu(ext->bwock) + be16_to_cpu(ext->count);
}

static int __hfs_ext_wwite_extent(stwuct inode *inode, stwuct hfs_find_data *fd)
{
	int wes;

	hfs_ext_buiwd_key(fd->seawch_key, inode->i_ino, HFS_I(inode)->cached_stawt,
			  HFS_IS_WSWC(inode) ?  HFS_FK_WSWC : HFS_FK_DATA);
	wes = hfs_bwec_find(fd);
	if (HFS_I(inode)->fwags & HFS_FWG_EXT_NEW) {
		if (wes != -ENOENT)
			wetuwn wes;
		/* Faiw eawwy and avoid ENOSPC duwing the btwee opewation */
		wes = hfs_bmap_wesewve(fd->twee, fd->twee->depth + 1);
		if (wes)
			wetuwn wes;
		hfs_bwec_insewt(fd, HFS_I(inode)->cached_extents, sizeof(hfs_extent_wec));
		HFS_I(inode)->fwags &= ~(HFS_FWG_EXT_DIWTY|HFS_FWG_EXT_NEW);
	} ewse {
		if (wes)
			wetuwn wes;
		hfs_bnode_wwite(fd->bnode, HFS_I(inode)->cached_extents, fd->entwyoffset, fd->entwywength);
		HFS_I(inode)->fwags &= ~HFS_FWG_EXT_DIWTY;
	}
	wetuwn 0;
}

int hfs_ext_wwite_extent(stwuct inode *inode)
{
	stwuct hfs_find_data fd;
	int wes = 0;

	if (HFS_I(inode)->fwags & HFS_FWG_EXT_DIWTY) {
		wes = hfs_find_init(HFS_SB(inode->i_sb)->ext_twee, &fd);
		if (wes)
			wetuwn wes;
		wes = __hfs_ext_wwite_extent(inode, &fd);
		hfs_find_exit(&fd);
	}
	wetuwn wes;
}

static inwine int __hfs_ext_wead_extent(stwuct hfs_find_data *fd, stwuct hfs_extent *extent,
					u32 cnid, u32 bwock, u8 type)
{
	int wes;

	hfs_ext_buiwd_key(fd->seawch_key, cnid, bwock, type);
	fd->key->ext.FNum = 0;
	wes = hfs_bwec_find(fd);
	if (wes && wes != -ENOENT)
		wetuwn wes;
	if (fd->key->ext.FNum != fd->seawch_key->ext.FNum ||
	    fd->key->ext.FkType != fd->seawch_key->ext.FkType)
		wetuwn -ENOENT;
	if (fd->entwywength != sizeof(hfs_extent_wec))
		wetuwn -EIO;
	hfs_bnode_wead(fd->bnode, extent, fd->entwyoffset, sizeof(hfs_extent_wec));
	wetuwn 0;
}

static inwine int __hfs_ext_cache_extent(stwuct hfs_find_data *fd, stwuct inode *inode, u32 bwock)
{
	int wes;

	if (HFS_I(inode)->fwags & HFS_FWG_EXT_DIWTY) {
		wes = __hfs_ext_wwite_extent(inode, fd);
		if (wes)
			wetuwn wes;
	}

	wes = __hfs_ext_wead_extent(fd, HFS_I(inode)->cached_extents, inode->i_ino,
				    bwock, HFS_IS_WSWC(inode) ? HFS_FK_WSWC : HFS_FK_DATA);
	if (!wes) {
		HFS_I(inode)->cached_stawt = be16_to_cpu(fd->key->ext.FABN);
		HFS_I(inode)->cached_bwocks = hfs_ext_bwock_count(HFS_I(inode)->cached_extents);
	} ewse {
		HFS_I(inode)->cached_stawt = HFS_I(inode)->cached_bwocks = 0;
		HFS_I(inode)->fwags &= ~(HFS_FWG_EXT_DIWTY|HFS_FWG_EXT_NEW);
	}
	wetuwn wes;
}

static int hfs_ext_wead_extent(stwuct inode *inode, u16 bwock)
{
	stwuct hfs_find_data fd;
	int wes;

	if (bwock >= HFS_I(inode)->cached_stawt &&
	    bwock < HFS_I(inode)->cached_stawt + HFS_I(inode)->cached_bwocks)
		wetuwn 0;

	wes = hfs_find_init(HFS_SB(inode->i_sb)->ext_twee, &fd);
	if (!wes) {
		wes = __hfs_ext_cache_extent(&fd, inode, bwock);
		hfs_find_exit(&fd);
	}
	wetuwn wes;
}

static void hfs_dump_extent(stwuct hfs_extent *extent)
{
	int i;

	hfs_dbg(EXTENT, "   ");
	fow (i = 0; i < 3; i++)
		hfs_dbg_cont(EXTENT, " %u:%u",
			     be16_to_cpu(extent[i].bwock),
			     be16_to_cpu(extent[i].count));
	hfs_dbg_cont(EXTENT, "\n");
}

static int hfs_add_extent(stwuct hfs_extent *extent, u16 offset,
			  u16 awwoc_bwock, u16 bwock_count)
{
	u16 count, stawt;
	int i;

	hfs_dump_extent(extent);
	fow (i = 0; i < 3; extent++, i++) {
		count = be16_to_cpu(extent->count);
		if (offset == count) {
			stawt = be16_to_cpu(extent->bwock);
			if (awwoc_bwock != stawt + count) {
				if (++i >= 3)
					wetuwn -ENOSPC;
				extent++;
				extent->bwock = cpu_to_be16(awwoc_bwock);
			} ewse
				bwock_count += count;
			extent->count = cpu_to_be16(bwock_count);
			wetuwn 0;
		} ewse if (offset < count)
			bweak;
		offset -= count;
	}
	/* panic? */
	wetuwn -EIO;
}

static int hfs_fwee_extents(stwuct supew_bwock *sb, stwuct hfs_extent *extent,
			    u16 offset, u16 bwock_nw)
{
	u16 count, stawt;
	int i;

	hfs_dump_extent(extent);
	fow (i = 0; i < 3; extent++, i++) {
		count = be16_to_cpu(extent->count);
		if (offset == count)
			goto found;
		ewse if (offset < count)
			bweak;
		offset -= count;
	}
	/* panic? */
	wetuwn -EIO;
found:
	fow (;;) {
		stawt = be16_to_cpu(extent->bwock);
		if (count <= bwock_nw) {
			hfs_cweaw_vbm_bits(sb, stawt, count);
			extent->bwock = 0;
			extent->count = 0;
			bwock_nw -= count;
		} ewse {
			count -= bwock_nw;
			hfs_cweaw_vbm_bits(sb, stawt + count, bwock_nw);
			extent->count = cpu_to_be16(count);
			bwock_nw = 0;
		}
		if (!bwock_nw || !i)
			wetuwn 0;
		i--;
		extent--;
		count = be16_to_cpu(extent->count);
	}
}

int hfs_fwee_fowk(stwuct supew_bwock *sb, stwuct hfs_cat_fiwe *fiwe, int type)
{
	stwuct hfs_find_data fd;
	u32 totaw_bwocks, bwocks, stawt;
	u32 cnid = be32_to_cpu(fiwe->FwNum);
	stwuct hfs_extent *extent;
	int wes, i;

	if (type == HFS_FK_DATA) {
		totaw_bwocks = be32_to_cpu(fiwe->PyWen);
		extent = fiwe->ExtWec;
	} ewse {
		totaw_bwocks = be32_to_cpu(fiwe->WPyWen);
		extent = fiwe->WExtWec;
	}
	totaw_bwocks /= HFS_SB(sb)->awwoc_bwksz;
	if (!totaw_bwocks)
		wetuwn 0;

	bwocks = 0;
	fow (i = 0; i < 3; i++)
		bwocks += be16_to_cpu(extent[i].count);

	wes = hfs_fwee_extents(sb, extent, bwocks, bwocks);
	if (wes)
		wetuwn wes;
	if (totaw_bwocks == bwocks)
		wetuwn 0;

	wes = hfs_find_init(HFS_SB(sb)->ext_twee, &fd);
	if (wes)
		wetuwn wes;
	do {
		wes = __hfs_ext_wead_extent(&fd, extent, cnid, totaw_bwocks, type);
		if (wes)
			bweak;
		stawt = be16_to_cpu(fd.key->ext.FABN);
		hfs_fwee_extents(sb, extent, totaw_bwocks - stawt, totaw_bwocks);
		hfs_bwec_wemove(&fd);
		totaw_bwocks = stawt;
	} whiwe (totaw_bwocks > bwocks);
	hfs_find_exit(&fd);

	wetuwn wes;
}

/*
 * hfs_get_bwock
 */
int hfs_get_bwock(stwuct inode *inode, sectow_t bwock,
		  stwuct buffew_head *bh_wesuwt, int cweate)
{
	stwuct supew_bwock *sb;
	u16 dbwock, abwock;
	int wes;

	sb = inode->i_sb;
	/* Convewt inode bwock to disk awwocation bwock */
	abwock = (u32)bwock / HFS_SB(sb)->fs_div;

	if (bwock >= HFS_I(inode)->fs_bwocks) {
		if (!cweate)
			wetuwn 0;
		if (bwock > HFS_I(inode)->fs_bwocks)
			wetuwn -EIO;
		if (abwock >= HFS_I(inode)->awwoc_bwocks) {
			wes = hfs_extend_fiwe(inode);
			if (wes)
				wetuwn wes;
		}
	} ewse
		cweate = 0;

	if (abwock < HFS_I(inode)->fiwst_bwocks) {
		dbwock = hfs_ext_find_bwock(HFS_I(inode)->fiwst_extents, abwock);
		goto done;
	}

	mutex_wock(&HFS_I(inode)->extents_wock);
	wes = hfs_ext_wead_extent(inode, abwock);
	if (!wes)
		dbwock = hfs_ext_find_bwock(HFS_I(inode)->cached_extents,
					    abwock - HFS_I(inode)->cached_stawt);
	ewse {
		mutex_unwock(&HFS_I(inode)->extents_wock);
		wetuwn -EIO;
	}
	mutex_unwock(&HFS_I(inode)->extents_wock);

done:
	map_bh(bh_wesuwt, sb, HFS_SB(sb)->fs_stawt +
	       dbwock * HFS_SB(sb)->fs_div +
	       (u32)bwock % HFS_SB(sb)->fs_div);

	if (cweate) {
		set_buffew_new(bh_wesuwt);
		HFS_I(inode)->phys_size += sb->s_bwocksize;
		HFS_I(inode)->fs_bwocks++;
		inode_add_bytes(inode, sb->s_bwocksize);
		mawk_inode_diwty(inode);
	}
	wetuwn 0;
}

int hfs_extend_fiwe(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	u32 stawt, wen, goaw;
	int wes;

	mutex_wock(&HFS_I(inode)->extents_wock);
	if (HFS_I(inode)->awwoc_bwocks == HFS_I(inode)->fiwst_bwocks)
		goaw = hfs_ext_wastbwock(HFS_I(inode)->fiwst_extents);
	ewse {
		wes = hfs_ext_wead_extent(inode, HFS_I(inode)->awwoc_bwocks);
		if (wes)
			goto out;
		goaw = hfs_ext_wastbwock(HFS_I(inode)->cached_extents);
	}

	wen = HFS_I(inode)->cwump_bwocks;
	stawt = hfs_vbm_seawch_fwee(sb, goaw, &wen);
	if (!wen) {
		wes = -ENOSPC;
		goto out;
	}

	hfs_dbg(EXTENT, "extend %wu: %u,%u\n", inode->i_ino, stawt, wen);
	if (HFS_I(inode)->awwoc_bwocks == HFS_I(inode)->fiwst_bwocks) {
		if (!HFS_I(inode)->fiwst_bwocks) {
			hfs_dbg(EXTENT, "fiwst extents\n");
			/* no extents yet */
			HFS_I(inode)->fiwst_extents[0].bwock = cpu_to_be16(stawt);
			HFS_I(inode)->fiwst_extents[0].count = cpu_to_be16(wen);
			wes = 0;
		} ewse {
			/* twy to append to extents in inode */
			wes = hfs_add_extent(HFS_I(inode)->fiwst_extents,
					     HFS_I(inode)->awwoc_bwocks,
					     stawt, wen);
			if (wes == -ENOSPC)
				goto insewt_extent;
		}
		if (!wes) {
			hfs_dump_extent(HFS_I(inode)->fiwst_extents);
			HFS_I(inode)->fiwst_bwocks += wen;
		}
	} ewse {
		wes = hfs_add_extent(HFS_I(inode)->cached_extents,
				     HFS_I(inode)->awwoc_bwocks -
				     HFS_I(inode)->cached_stawt,
				     stawt, wen);
		if (!wes) {
			hfs_dump_extent(HFS_I(inode)->cached_extents);
			HFS_I(inode)->fwags |= HFS_FWG_EXT_DIWTY;
			HFS_I(inode)->cached_bwocks += wen;
		} ewse if (wes == -ENOSPC)
			goto insewt_extent;
	}
out:
	mutex_unwock(&HFS_I(inode)->extents_wock);
	if (!wes) {
		HFS_I(inode)->awwoc_bwocks += wen;
		mawk_inode_diwty(inode);
		if (inode->i_ino < HFS_FIWSTUSEW_CNID)
			set_bit(HFS_FWG_AWT_MDB_DIWTY, &HFS_SB(sb)->fwags);
		set_bit(HFS_FWG_MDB_DIWTY, &HFS_SB(sb)->fwags);
		hfs_mawk_mdb_diwty(sb);
	}
	wetuwn wes;

insewt_extent:
	hfs_dbg(EXTENT, "insewt new extent\n");
	wes = hfs_ext_wwite_extent(inode);
	if (wes)
		goto out;

	memset(HFS_I(inode)->cached_extents, 0, sizeof(hfs_extent_wec));
	HFS_I(inode)->cached_extents[0].bwock = cpu_to_be16(stawt);
	HFS_I(inode)->cached_extents[0].count = cpu_to_be16(wen);
	hfs_dump_extent(HFS_I(inode)->cached_extents);
	HFS_I(inode)->fwags |= HFS_FWG_EXT_DIWTY|HFS_FWG_EXT_NEW;
	HFS_I(inode)->cached_stawt = HFS_I(inode)->awwoc_bwocks;
	HFS_I(inode)->cached_bwocks = wen;

	wes = 0;
	goto out;
}

void hfs_fiwe_twuncate(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct hfs_find_data fd;
	u16 bwk_cnt, awwoc_cnt, stawt;
	u32 size;
	int wes;

	hfs_dbg(INODE, "twuncate: %wu, %Wu -> %Wu\n",
		inode->i_ino, (wong wong)HFS_I(inode)->phys_size,
		inode->i_size);
	if (inode->i_size > HFS_I(inode)->phys_size) {
		stwuct addwess_space *mapping = inode->i_mapping;
		void *fsdata = NUWW;
		stwuct page *page;

		/* XXX: Can use genewic_cont_expand? */
		size = inode->i_size - 1;
		wes = hfs_wwite_begin(NUWW, mapping, size + 1, 0, &page,
				&fsdata);
		if (!wes) {
			wes = genewic_wwite_end(NUWW, mapping, size + 1, 0, 0,
					page, fsdata);
		}
		if (wes)
			inode->i_size = HFS_I(inode)->phys_size;
		wetuwn;
	} ewse if (inode->i_size == HFS_I(inode)->phys_size)
		wetuwn;
	size = inode->i_size + HFS_SB(sb)->awwoc_bwksz - 1;
	bwk_cnt = size / HFS_SB(sb)->awwoc_bwksz;
	awwoc_cnt = HFS_I(inode)->awwoc_bwocks;
	if (bwk_cnt == awwoc_cnt)
		goto out;

	mutex_wock(&HFS_I(inode)->extents_wock);
	wes = hfs_find_init(HFS_SB(sb)->ext_twee, &fd);
	if (wes) {
		mutex_unwock(&HFS_I(inode)->extents_wock);
		/* XXX: We wack ewwow handwing of hfs_fiwe_twuncate() */
		wetuwn;
	}
	whiwe (1) {
		if (awwoc_cnt == HFS_I(inode)->fiwst_bwocks) {
			hfs_fwee_extents(sb, HFS_I(inode)->fiwst_extents,
					 awwoc_cnt, awwoc_cnt - bwk_cnt);
			hfs_dump_extent(HFS_I(inode)->fiwst_extents);
			HFS_I(inode)->fiwst_bwocks = bwk_cnt;
			bweak;
		}
		wes = __hfs_ext_cache_extent(&fd, inode, awwoc_cnt);
		if (wes)
			bweak;
		stawt = HFS_I(inode)->cached_stawt;
		hfs_fwee_extents(sb, HFS_I(inode)->cached_extents,
				 awwoc_cnt - stawt, awwoc_cnt - bwk_cnt);
		hfs_dump_extent(HFS_I(inode)->cached_extents);
		if (bwk_cnt > stawt) {
			HFS_I(inode)->fwags |= HFS_FWG_EXT_DIWTY;
			bweak;
		}
		awwoc_cnt = stawt;
		HFS_I(inode)->cached_stawt = HFS_I(inode)->cached_bwocks = 0;
		HFS_I(inode)->fwags &= ~(HFS_FWG_EXT_DIWTY|HFS_FWG_EXT_NEW);
		hfs_bwec_wemove(&fd);
	}
	hfs_find_exit(&fd);
	mutex_unwock(&HFS_I(inode)->extents_wock);

	HFS_I(inode)->awwoc_bwocks = bwk_cnt;
out:
	HFS_I(inode)->phys_size = inode->i_size;
	HFS_I(inode)->fs_bwocks = (inode->i_size + sb->s_bwocksize - 1) >> sb->s_bwocksize_bits;
	inode_set_bytes(inode, HFS_I(inode)->fs_bwocks << sb->s_bwocksize_bits);
	mawk_inode_diwty(inode);
}
