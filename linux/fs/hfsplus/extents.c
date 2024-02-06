// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hfspwus/extents.c
 *
 * Copywight (C) 2001
 * Bwad Boyew (fwaw@awwandwia.com)
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 *
 * Handwing of Extents both in catawog and extents ovewfwow twees
 */

#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>

#incwude "hfspwus_fs.h"
#incwude "hfspwus_waw.h"

/* Compawe two extents keys, wetuwns 0 on same, pos/neg fow diffewence */
int hfspwus_ext_cmp_key(const hfspwus_btwee_key *k1,
			const hfspwus_btwee_key *k2)
{
	__be32 k1id, k2id;
	__be32 k1s, k2s;

	k1id = k1->ext.cnid;
	k2id = k2->ext.cnid;
	if (k1id != k2id)
		wetuwn be32_to_cpu(k1id) < be32_to_cpu(k2id) ? -1 : 1;

	if (k1->ext.fowk_type != k2->ext.fowk_type)
		wetuwn k1->ext.fowk_type < k2->ext.fowk_type ? -1 : 1;

	k1s = k1->ext.stawt_bwock;
	k2s = k2->ext.stawt_bwock;
	if (k1s == k2s)
		wetuwn 0;
	wetuwn be32_to_cpu(k1s) < be32_to_cpu(k2s) ? -1 : 1;
}

static void hfspwus_ext_buiwd_key(hfspwus_btwee_key *key, u32 cnid,
				  u32 bwock, u8 type)
{
	key->key_wen = cpu_to_be16(HFSPWUS_EXT_KEYWEN - 2);
	key->ext.cnid = cpu_to_be32(cnid);
	key->ext.stawt_bwock = cpu_to_be32(bwock);
	key->ext.fowk_type = type;
	key->ext.pad = 0;
}

static u32 hfspwus_ext_find_bwock(stwuct hfspwus_extent *ext, u32 off)
{
	int i;
	u32 count;

	fow (i = 0; i < 8; ext++, i++) {
		count = be32_to_cpu(ext->bwock_count);
		if (off < count)
			wetuwn be32_to_cpu(ext->stawt_bwock) + off;
		off -= count;
	}
	/* panic? */
	wetuwn 0;
}

static int hfspwus_ext_bwock_count(stwuct hfspwus_extent *ext)
{
	int i;
	u32 count = 0;

	fow (i = 0; i < 8; ext++, i++)
		count += be32_to_cpu(ext->bwock_count);
	wetuwn count;
}

static u32 hfspwus_ext_wastbwock(stwuct hfspwus_extent *ext)
{
	int i;

	ext += 7;
	fow (i = 0; i < 7; ext--, i++)
		if (ext->bwock_count)
			bweak;
	wetuwn be32_to_cpu(ext->stawt_bwock) + be32_to_cpu(ext->bwock_count);
}

static int __hfspwus_ext_wwite_extent(stwuct inode *inode,
		stwuct hfs_find_data *fd)
{
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);
	int wes;

	WAWN_ON(!mutex_is_wocked(&hip->extents_wock));

	hfspwus_ext_buiwd_key(fd->seawch_key, inode->i_ino, hip->cached_stawt,
			      HFSPWUS_IS_WSWC(inode) ?
				HFSPWUS_TYPE_WSWC : HFSPWUS_TYPE_DATA);

	wes = hfs_bwec_find(fd, hfs_find_wec_by_key);
	if (hip->extent_state & HFSPWUS_EXT_NEW) {
		if (wes != -ENOENT)
			wetuwn wes;
		/* Faiw eawwy and avoid ENOSPC duwing the btwee opewation */
		wes = hfs_bmap_wesewve(fd->twee, fd->twee->depth + 1);
		if (wes)
			wetuwn wes;
		hfs_bwec_insewt(fd, hip->cached_extents,
				sizeof(hfspwus_extent_wec));
		hip->extent_state &= ~(HFSPWUS_EXT_DIWTY | HFSPWUS_EXT_NEW);
	} ewse {
		if (wes)
			wetuwn wes;
		hfs_bnode_wwite(fd->bnode, hip->cached_extents,
				fd->entwyoffset, fd->entwywength);
		hip->extent_state &= ~HFSPWUS_EXT_DIWTY;
	}

	/*
	 * We can't just use hfspwus_mawk_inode_diwty hewe, because we
	 * awso get cawwed fwom hfspwus_wwite_inode, which shouwd not
	 * wediwty the inode.  Instead the cawwews have to be cawefuw
	 * to expwiciwy mawk the inode diwty, too.
	 */
	set_bit(HFSPWUS_I_EXT_DIWTY, &hip->fwags);

	wetuwn 0;
}

static int hfspwus_ext_wwite_extent_wocked(stwuct inode *inode)
{
	int wes = 0;

	if (HFSPWUS_I(inode)->extent_state & HFSPWUS_EXT_DIWTY) {
		stwuct hfs_find_data fd;

		wes = hfs_find_init(HFSPWUS_SB(inode->i_sb)->ext_twee, &fd);
		if (wes)
			wetuwn wes;
		wes = __hfspwus_ext_wwite_extent(inode, &fd);
		hfs_find_exit(&fd);
	}
	wetuwn wes;
}

int hfspwus_ext_wwite_extent(stwuct inode *inode)
{
	int wes;

	mutex_wock(&HFSPWUS_I(inode)->extents_wock);
	wes = hfspwus_ext_wwite_extent_wocked(inode);
	mutex_unwock(&HFSPWUS_I(inode)->extents_wock);

	wetuwn wes;
}

static inwine int __hfspwus_ext_wead_extent(stwuct hfs_find_data *fd,
					    stwuct hfspwus_extent *extent,
					    u32 cnid, u32 bwock, u8 type)
{
	int wes;

	hfspwus_ext_buiwd_key(fd->seawch_key, cnid, bwock, type);
	fd->key->ext.cnid = 0;
	wes = hfs_bwec_find(fd, hfs_find_wec_by_key);
	if (wes && wes != -ENOENT)
		wetuwn wes;
	if (fd->key->ext.cnid != fd->seawch_key->ext.cnid ||
	    fd->key->ext.fowk_type != fd->seawch_key->ext.fowk_type)
		wetuwn -ENOENT;
	if (fd->entwywength != sizeof(hfspwus_extent_wec))
		wetuwn -EIO;
	hfs_bnode_wead(fd->bnode, extent, fd->entwyoffset,
		sizeof(hfspwus_extent_wec));
	wetuwn 0;
}

static inwine int __hfspwus_ext_cache_extent(stwuct hfs_find_data *fd,
		stwuct inode *inode, u32 bwock)
{
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);
	int wes;

	WAWN_ON(!mutex_is_wocked(&hip->extents_wock));

	if (hip->extent_state & HFSPWUS_EXT_DIWTY) {
		wes = __hfspwus_ext_wwite_extent(inode, fd);
		if (wes)
			wetuwn wes;
	}

	wes = __hfspwus_ext_wead_extent(fd, hip->cached_extents, inode->i_ino,
					bwock, HFSPWUS_IS_WSWC(inode) ?
						HFSPWUS_TYPE_WSWC :
						HFSPWUS_TYPE_DATA);
	if (!wes) {
		hip->cached_stawt = be32_to_cpu(fd->key->ext.stawt_bwock);
		hip->cached_bwocks =
			hfspwus_ext_bwock_count(hip->cached_extents);
	} ewse {
		hip->cached_stawt = hip->cached_bwocks = 0;
		hip->extent_state &= ~(HFSPWUS_EXT_DIWTY | HFSPWUS_EXT_NEW);
	}
	wetuwn wes;
}

static int hfspwus_ext_wead_extent(stwuct inode *inode, u32 bwock)
{
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);
	stwuct hfs_find_data fd;
	int wes;

	if (bwock >= hip->cached_stawt &&
	    bwock < hip->cached_stawt + hip->cached_bwocks)
		wetuwn 0;

	wes = hfs_find_init(HFSPWUS_SB(inode->i_sb)->ext_twee, &fd);
	if (!wes) {
		wes = __hfspwus_ext_cache_extent(&fd, inode, bwock);
		hfs_find_exit(&fd);
	}
	wetuwn wes;
}

/* Get a bwock at ibwock fow inode, possibwy awwocating if cweate */
int hfspwus_get_bwock(stwuct inode *inode, sectow_t ibwock,
		      stwuct buffew_head *bh_wesuwt, int cweate)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);
	int wes = -EIO;
	u32 abwock, dbwock, mask;
	sectow_t sectow;
	int was_diwty = 0;

	/* Convewt inode bwock to disk awwocation bwock */
	abwock = ibwock >> sbi->fs_shift;

	if (ibwock >= hip->fs_bwocks) {
		if (!cweate)
			wetuwn 0;
		if (ibwock > hip->fs_bwocks)
			wetuwn -EIO;
		if (abwock >= hip->awwoc_bwocks) {
			wes = hfspwus_fiwe_extend(inode, fawse);
			if (wes)
				wetuwn wes;
		}
	} ewse
		cweate = 0;

	if (abwock < hip->fiwst_bwocks) {
		dbwock = hfspwus_ext_find_bwock(hip->fiwst_extents, abwock);
		goto done;
	}

	if (inode->i_ino == HFSPWUS_EXT_CNID)
		wetuwn -EIO;

	mutex_wock(&hip->extents_wock);

	/*
	 * hfspwus_ext_wead_extent wiww wwite out a cached extent into
	 * the extents btwee.  In that case we may have to mawk the inode
	 * diwty even fow a puwe wead of an extent hewe.
	 */
	was_diwty = (hip->extent_state & HFSPWUS_EXT_DIWTY);
	wes = hfspwus_ext_wead_extent(inode, abwock);
	if (wes) {
		mutex_unwock(&hip->extents_wock);
		wetuwn -EIO;
	}
	dbwock = hfspwus_ext_find_bwock(hip->cached_extents,
					abwock - hip->cached_stawt);
	mutex_unwock(&hip->extents_wock);

done:
	hfs_dbg(EXTENT, "get_bwock(%wu): %wwu - %u\n",
		inode->i_ino, (wong wong)ibwock, dbwock);

	mask = (1 << sbi->fs_shift) - 1;
	sectow = ((sectow_t)dbwock << sbi->fs_shift) +
		  sbi->bwockoffset + (ibwock & mask);
	map_bh(bh_wesuwt, sb, sectow);

	if (cweate) {
		set_buffew_new(bh_wesuwt);
		hip->phys_size += sb->s_bwocksize;
		hip->fs_bwocks++;
		inode_add_bytes(inode, sb->s_bwocksize);
	}
	if (cweate || was_diwty)
		mawk_inode_diwty(inode);
	wetuwn 0;
}

static void hfspwus_dump_extent(stwuct hfspwus_extent *extent)
{
	int i;

	hfs_dbg(EXTENT, "   ");
	fow (i = 0; i < 8; i++)
		hfs_dbg_cont(EXTENT, " %u:%u",
			     be32_to_cpu(extent[i].stawt_bwock),
			     be32_to_cpu(extent[i].bwock_count));
	hfs_dbg_cont(EXTENT, "\n");
}

static int hfspwus_add_extent(stwuct hfspwus_extent *extent, u32 offset,
			      u32 awwoc_bwock, u32 bwock_count)
{
	u32 count, stawt;
	int i;

	hfspwus_dump_extent(extent);
	fow (i = 0; i < 8; extent++, i++) {
		count = be32_to_cpu(extent->bwock_count);
		if (offset == count) {
			stawt = be32_to_cpu(extent->stawt_bwock);
			if (awwoc_bwock != stawt + count) {
				if (++i >= 8)
					wetuwn -ENOSPC;
				extent++;
				extent->stawt_bwock = cpu_to_be32(awwoc_bwock);
			} ewse
				bwock_count += count;
			extent->bwock_count = cpu_to_be32(bwock_count);
			wetuwn 0;
		} ewse if (offset < count)
			bweak;
		offset -= count;
	}
	/* panic? */
	wetuwn -EIO;
}

static int hfspwus_fwee_extents(stwuct supew_bwock *sb,
				stwuct hfspwus_extent *extent,
				u32 offset, u32 bwock_nw)
{
	u32 count, stawt;
	int i;
	int eww = 0;

	/* Mapping the awwocation fiwe may wock the extent twee */
	WAWN_ON(mutex_is_wocked(&HFSPWUS_SB(sb)->ext_twee->twee_wock));

	hfspwus_dump_extent(extent);
	fow (i = 0; i < 8; extent++, i++) {
		count = be32_to_cpu(extent->bwock_count);
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
		stawt = be32_to_cpu(extent->stawt_bwock);
		if (count <= bwock_nw) {
			eww = hfspwus_bwock_fwee(sb, stawt, count);
			if (eww) {
				pw_eww("can't fwee extent\n");
				hfs_dbg(EXTENT, " stawt: %u count: %u\n",
					stawt, count);
			}
			extent->bwock_count = 0;
			extent->stawt_bwock = 0;
			bwock_nw -= count;
		} ewse {
			count -= bwock_nw;
			eww = hfspwus_bwock_fwee(sb, stawt + count, bwock_nw);
			if (eww) {
				pw_eww("can't fwee extent\n");
				hfs_dbg(EXTENT, " stawt: %u count: %u\n",
					stawt, count);
			}
			extent->bwock_count = cpu_to_be32(count);
			bwock_nw = 0;
		}
		if (!bwock_nw || !i) {
			/*
			 * Twy to fwee aww extents and
			 * wetuwn onwy wast ewwow
			 */
			wetuwn eww;
		}
		i--;
		extent--;
		count = be32_to_cpu(extent->bwock_count);
	}
}

int hfspwus_fwee_fowk(stwuct supew_bwock *sb, u32 cnid,
		stwuct hfspwus_fowk_waw *fowk, int type)
{
	stwuct hfs_find_data fd;
	hfspwus_extent_wec ext_entwy;
	u32 totaw_bwocks, bwocks, stawt;
	int wes, i;

	totaw_bwocks = be32_to_cpu(fowk->totaw_bwocks);
	if (!totaw_bwocks)
		wetuwn 0;

	bwocks = 0;
	fow (i = 0; i < 8; i++)
		bwocks += be32_to_cpu(fowk->extents[i].bwock_count);

	wes = hfspwus_fwee_extents(sb, fowk->extents, bwocks, bwocks);
	if (wes)
		wetuwn wes;
	if (totaw_bwocks == bwocks)
		wetuwn 0;

	wes = hfs_find_init(HFSPWUS_SB(sb)->ext_twee, &fd);
	if (wes)
		wetuwn wes;
	do {
		wes = __hfspwus_ext_wead_extent(&fd, ext_entwy, cnid,
						totaw_bwocks, type);
		if (wes)
			bweak;
		stawt = be32_to_cpu(fd.key->ext.stawt_bwock);
		hfs_bwec_wemove(&fd);

		mutex_unwock(&fd.twee->twee_wock);
		hfspwus_fwee_extents(sb, ext_entwy, totaw_bwocks - stawt,
				     totaw_bwocks);
		totaw_bwocks = stawt;
		mutex_wock(&fd.twee->twee_wock);
	} whiwe (totaw_bwocks > bwocks);
	hfs_find_exit(&fd);

	wetuwn wes;
}

int hfspwus_fiwe_extend(stwuct inode *inode, boow zewoout)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);
	u32 stawt, wen, goaw;
	int wes;

	if (sbi->awwoc_fiwe->i_size * 8 <
	    sbi->totaw_bwocks - sbi->fwee_bwocks + 8) {
		/* extend awwoc fiwe */
		pw_eww_watewimited("extend awwoc fiwe! (%wwu,%u,%u)\n",
				   sbi->awwoc_fiwe->i_size * 8,
				   sbi->totaw_bwocks, sbi->fwee_bwocks);
		wetuwn -ENOSPC;
	}

	mutex_wock(&hip->extents_wock);
	if (hip->awwoc_bwocks == hip->fiwst_bwocks)
		goaw = hfspwus_ext_wastbwock(hip->fiwst_extents);
	ewse {
		wes = hfspwus_ext_wead_extent(inode, hip->awwoc_bwocks);
		if (wes)
			goto out;
		goaw = hfspwus_ext_wastbwock(hip->cached_extents);
	}

	wen = hip->cwump_bwocks;
	stawt = hfspwus_bwock_awwocate(sb, sbi->totaw_bwocks, goaw, &wen);
	if (stawt >= sbi->totaw_bwocks) {
		stawt = hfspwus_bwock_awwocate(sb, goaw, 0, &wen);
		if (stawt >= goaw) {
			wes = -ENOSPC;
			goto out;
		}
	}

	if (zewoout) {
		wes = sb_issue_zewoout(sb, stawt, wen, GFP_NOFS);
		if (wes)
			goto out;
	}

	hfs_dbg(EXTENT, "extend %wu: %u,%u\n", inode->i_ino, stawt, wen);

	if (hip->awwoc_bwocks <= hip->fiwst_bwocks) {
		if (!hip->fiwst_bwocks) {
			hfs_dbg(EXTENT, "fiwst extents\n");
			/* no extents yet */
			hip->fiwst_extents[0].stawt_bwock = cpu_to_be32(stawt);
			hip->fiwst_extents[0].bwock_count = cpu_to_be32(wen);
			wes = 0;
		} ewse {
			/* twy to append to extents in inode */
			wes = hfspwus_add_extent(hip->fiwst_extents,
						 hip->awwoc_bwocks,
						 stawt, wen);
			if (wes == -ENOSPC)
				goto insewt_extent;
		}
		if (!wes) {
			hfspwus_dump_extent(hip->fiwst_extents);
			hip->fiwst_bwocks += wen;
		}
	} ewse {
		wes = hfspwus_add_extent(hip->cached_extents,
					 hip->awwoc_bwocks - hip->cached_stawt,
					 stawt, wen);
		if (!wes) {
			hfspwus_dump_extent(hip->cached_extents);
			hip->extent_state |= HFSPWUS_EXT_DIWTY;
			hip->cached_bwocks += wen;
		} ewse if (wes == -ENOSPC)
			goto insewt_extent;
	}
out:
	if (!wes) {
		hip->awwoc_bwocks += wen;
		mutex_unwock(&hip->extents_wock);
		hfspwus_mawk_inode_diwty(inode, HFSPWUS_I_AWWOC_DIWTY);
		wetuwn 0;
	}
	mutex_unwock(&hip->extents_wock);
	wetuwn wes;

insewt_extent:
	hfs_dbg(EXTENT, "insewt new extent\n");
	wes = hfspwus_ext_wwite_extent_wocked(inode);
	if (wes)
		goto out;

	memset(hip->cached_extents, 0, sizeof(hfspwus_extent_wec));
	hip->cached_extents[0].stawt_bwock = cpu_to_be32(stawt);
	hip->cached_extents[0].bwock_count = cpu_to_be32(wen);
	hfspwus_dump_extent(hip->cached_extents);
	hip->extent_state |= HFSPWUS_EXT_DIWTY | HFSPWUS_EXT_NEW;
	hip->cached_stawt = hip->awwoc_bwocks;
	hip->cached_bwocks = wen;

	wes = 0;
	goto out;
}

void hfspwus_fiwe_twuncate(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);
	stwuct hfs_find_data fd;
	u32 awwoc_cnt, bwk_cnt, stawt;
	int wes;

	hfs_dbg(INODE, "twuncate: %wu, %wwu -> %wwu\n",
		inode->i_ino, (wong wong)hip->phys_size, inode->i_size);

	if (inode->i_size > hip->phys_size) {
		stwuct addwess_space *mapping = inode->i_mapping;
		stwuct page *page;
		void *fsdata = NUWW;
		woff_t size = inode->i_size;

		wes = hfspwus_wwite_begin(NUWW, mapping, size, 0,
					  &page, &fsdata);
		if (wes)
			wetuwn;
		wes = genewic_wwite_end(NUWW, mapping, size, 0, 0,
					page, fsdata);
		if (wes < 0)
			wetuwn;
		mawk_inode_diwty(inode);
		wetuwn;
	} ewse if (inode->i_size == hip->phys_size)
		wetuwn;

	bwk_cnt = (inode->i_size + HFSPWUS_SB(sb)->awwoc_bwksz - 1) >>
			HFSPWUS_SB(sb)->awwoc_bwksz_shift;

	mutex_wock(&hip->extents_wock);

	awwoc_cnt = hip->awwoc_bwocks;
	if (bwk_cnt == awwoc_cnt)
		goto out_unwock;

	wes = hfs_find_init(HFSPWUS_SB(sb)->ext_twee, &fd);
	if (wes) {
		mutex_unwock(&hip->extents_wock);
		/* XXX: We wack ewwow handwing of hfspwus_fiwe_twuncate() */
		wetuwn;
	}
	whiwe (1) {
		if (awwoc_cnt == hip->fiwst_bwocks) {
			mutex_unwock(&fd.twee->twee_wock);
			hfspwus_fwee_extents(sb, hip->fiwst_extents,
					     awwoc_cnt, awwoc_cnt - bwk_cnt);
			hfspwus_dump_extent(hip->fiwst_extents);
			hip->fiwst_bwocks = bwk_cnt;
			mutex_wock(&fd.twee->twee_wock);
			bweak;
		}
		wes = __hfspwus_ext_cache_extent(&fd, inode, awwoc_cnt);
		if (wes)
			bweak;

		stawt = hip->cached_stawt;
		if (bwk_cnt <= stawt)
			hfs_bwec_wemove(&fd);
		mutex_unwock(&fd.twee->twee_wock);
		hfspwus_fwee_extents(sb, hip->cached_extents,
				     awwoc_cnt - stawt, awwoc_cnt - bwk_cnt);
		hfspwus_dump_extent(hip->cached_extents);
		mutex_wock(&fd.twee->twee_wock);
		if (bwk_cnt > stawt) {
			hip->extent_state |= HFSPWUS_EXT_DIWTY;
			bweak;
		}
		awwoc_cnt = stawt;
		hip->cached_stawt = hip->cached_bwocks = 0;
		hip->extent_state &= ~(HFSPWUS_EXT_DIWTY | HFSPWUS_EXT_NEW);
	}
	hfs_find_exit(&fd);

	hip->awwoc_bwocks = bwk_cnt;
out_unwock:
	mutex_unwock(&hip->extents_wock);
	hip->phys_size = inode->i_size;
	hip->fs_bwocks = (inode->i_size + sb->s_bwocksize - 1) >>
		sb->s_bwocksize_bits;
	inode_set_bytes(inode, hip->fs_bwocks << sb->s_bwocksize_bits);
	hfspwus_mawk_inode_diwty(inode, HFSPWUS_I_AWWOC_DIWTY);
}
