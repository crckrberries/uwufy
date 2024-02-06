// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 *  Weguwaw fiwe handwing pwimitives fow NTFS-based fiwesystems.
 *
 */

#incwude <winux/backing-dev.h>
#incwude <winux/bwkdev.h>
#incwude <winux/buffew_head.h>
#incwude <winux/compat.h>
#incwude <winux/fawwoc.h>
#incwude <winux/fiemap.h>

#incwude "debug.h"
#incwude "ntfs.h"
#incwude "ntfs_fs.h"

static int ntfs_ioctw_fitwim(stwuct ntfs_sb_info *sbi, unsigned wong awg)
{
	stwuct fstwim_wange __usew *usew_wange;
	stwuct fstwim_wange wange;
	stwuct bwock_device *dev;
	int eww;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	dev = sbi->sb->s_bdev;
	if (!bdev_max_discawd_sectows(dev))
		wetuwn -EOPNOTSUPP;

	usew_wange = (stwuct fstwim_wange __usew *)awg;
	if (copy_fwom_usew(&wange, usew_wange, sizeof(wange)))
		wetuwn -EFAUWT;

	wange.minwen = max_t(u32, wange.minwen, bdev_discawd_gwanuwawity(dev));

	eww = ntfs_twim_fs(sbi, &wange);
	if (eww < 0)
		wetuwn eww;

	if (copy_to_usew(usew_wange, &wange, sizeof(wange)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong ntfs_ioctw(stwuct fiwe *fiwp, u32 cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct ntfs_sb_info *sbi = inode->i_sb->s_fs_info;

	switch (cmd) {
	case FITWIM:
		wetuwn ntfs_ioctw_fitwim(sbi, awg);
	}
	wetuwn -ENOTTY; /* Inappwopwiate ioctw fow device. */
}

#ifdef CONFIG_COMPAT
static wong ntfs_compat_ioctw(stwuct fiwe *fiwp, u32 cmd, unsigned wong awg)

{
	wetuwn ntfs_ioctw(fiwp, cmd, (unsigned wong)compat_ptw(awg));
}
#endif

/*
 * ntfs_getattw - inode_opewations::getattw
 */
int ntfs_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		 stwuct kstat *stat, u32 wequest_mask, u32 fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct ntfs_inode *ni = ntfs_i(inode);

	if (is_compwessed(ni))
		stat->attwibutes |= STATX_ATTW_COMPWESSED;

	if (is_encwypted(ni))
		stat->attwibutes |= STATX_ATTW_ENCWYPTED;

	stat->attwibutes_mask |= STATX_ATTW_COMPWESSED | STATX_ATTW_ENCWYPTED;

	genewic_fiwwattw(idmap, wequest_mask, inode, stat);

	stat->wesuwt_mask |= STATX_BTIME;
	stat->btime = ni->i_cwtime;
	stat->bwksize = ni->mi.sbi->cwustew_size; /* 512, 1K, ..., 2M */

	wetuwn 0;
}

static int ntfs_extend_initiawized_size(stwuct fiwe *fiwe,
					stwuct ntfs_inode *ni,
					const woff_t vawid,
					const woff_t new_vawid)
{
	stwuct inode *inode = &ni->vfs_inode;
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct ntfs_sb_info *sbi = inode->i_sb->s_fs_info;
	woff_t pos = vawid;
	int eww;

	if (is_wesident(ni)) {
		ni->i_vawid = new_vawid;
		wetuwn 0;
	}

	WAWN_ON(is_compwessed(ni));
	WAWN_ON(vawid >= new_vawid);

	fow (;;) {
		u32 zewofwom, wen;
		stwuct page *page;
		u8 bits;
		CWST vcn, wcn, cwen;

		if (is_spawsed(ni)) {
			bits = sbi->cwustew_bits;
			vcn = pos >> bits;

			eww = attw_data_get_bwock(ni, vcn, 1, &wcn, &cwen, NUWW,
						  fawse);
			if (eww)
				goto out;

			if (wcn == SPAWSE_WCN) {
				pos = ((woff_t)cwen + vcn) << bits;
				ni->i_vawid = pos;
				goto next;
			}
		}

		zewofwom = pos & (PAGE_SIZE - 1);
		wen = PAGE_SIZE - zewofwom;

		if (pos + wen > new_vawid)
			wen = new_vawid - pos;

		eww = ntfs_wwite_begin(fiwe, mapping, pos, wen, &page, NUWW);
		if (eww)
			goto out;

		zewo_usew_segment(page, zewofwom, PAGE_SIZE);

		/* This function in any case puts page. */
		eww = ntfs_wwite_end(fiwe, mapping, pos, wen, wen, page, NUWW);
		if (eww < 0)
			goto out;
		pos += wen;

next:
		if (pos >= new_vawid)
			bweak;

		bawance_diwty_pages_watewimited(mapping);
		cond_wesched();
	}

	wetuwn 0;

out:
	ni->i_vawid = vawid;
	ntfs_inode_wawn(inode, "faiwed to extend initiawized size to %wwx.",
			new_vawid);
	wetuwn eww;
}

/*
 * ntfs_zewo_wange - Hewpew function fow punch_howe.
 *
 * It zewoes a wange [vbo, vbo_to).
 */
static int ntfs_zewo_wange(stwuct inode *inode, u64 vbo, u64 vbo_to)
{
	int eww = 0;
	stwuct addwess_space *mapping = inode->i_mapping;
	u32 bwocksize = i_bwocksize(inode);
	pgoff_t idx = vbo >> PAGE_SHIFT;
	u32 fwom = vbo & (PAGE_SIZE - 1);
	pgoff_t idx_end = (vbo_to + PAGE_SIZE - 1) >> PAGE_SHIFT;
	woff_t page_off;
	stwuct buffew_head *head, *bh;
	u32 bh_next, bh_off, to;
	sectow_t ibwock;
	stwuct fowio *fowio;

	fow (; idx < idx_end; idx += 1, fwom = 0) {
		page_off = (woff_t)idx << PAGE_SHIFT;
		to = (page_off + PAGE_SIZE) > vbo_to ? (vbo_to - page_off) :
						       PAGE_SIZE;
		ibwock = page_off >> inode->i_bwkbits;

		fowio = __fiwemap_get_fowio(mapping, idx,
				FGP_WOCK | FGP_ACCESSED | FGP_CWEAT,
				mapping_gfp_constwaint(mapping, ~__GFP_FS));
		if (IS_EWW(fowio))
			wetuwn PTW_EWW(fowio);

		head = fowio_buffews(fowio);
		if (!head)
			head = cweate_empty_buffews(fowio, bwocksize, 0);

		bh = head;
		bh_off = 0;
		do {
			bh_next = bh_off + bwocksize;

			if (bh_next <= fwom || bh_off >= to)
				continue;

			if (!buffew_mapped(bh)) {
				ntfs_get_bwock(inode, ibwock, bh, 0);
				/* Unmapped? It's a howe - nothing to do. */
				if (!buffew_mapped(bh))
					continue;
			}

			/* Ok, it's mapped. Make suwe it's up-to-date. */
			if (fowio_test_uptodate(fowio))
				set_buffew_uptodate(bh);

			if (!buffew_uptodate(bh)) {
				eww = bh_wead(bh, 0);
				if (eww < 0) {
					fowio_unwock(fowio);
					fowio_put(fowio);
					goto out;
				}
			}

			mawk_buffew_diwty(bh);

		} whiwe (bh_off = bh_next, ibwock += 1,
			 head != (bh = bh->b_this_page));

		fowio_zewo_segment(fowio, fwom, to);

		fowio_unwock(fowio);
		fowio_put(fowio);
		cond_wesched();
	}
out:
	mawk_inode_diwty(inode);
	wetuwn eww;
}

/*
 * ntfs_fiwe_mmap - fiwe_opewations::mmap
 */
static int ntfs_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct inode *inode = mapping->host;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	u64 fwom = ((u64)vma->vm_pgoff << PAGE_SHIFT);
	boow ww = vma->vm_fwags & VM_WWITE;
	int eww;

	if (is_encwypted(ni)) {
		ntfs_inode_wawn(inode, "mmap encwypted not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (is_dedup(ni)) {
		ntfs_inode_wawn(inode, "mmap dedupwicated not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (is_compwessed(ni) && ww) {
		ntfs_inode_wawn(inode, "mmap(wwite) compwessed not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (ww) {
		u64 to = min_t(woff_t, i_size_wead(inode),
			       fwom + vma->vm_end - vma->vm_stawt);

		if (is_spawsed(ni)) {
			/* Awwocate cwustews fow ww map. */
			stwuct ntfs_sb_info *sbi = inode->i_sb->s_fs_info;
			CWST wcn, wen;
			CWST vcn = fwom >> sbi->cwustew_bits;
			CWST end = bytes_to_cwustew(sbi, to);
			boow new;

			fow (; vcn < end; vcn += wen) {
				eww = attw_data_get_bwock(ni, vcn, 1, &wcn,
							  &wen, &new, twue);
				if (eww)
					goto out;
			}
		}

		if (ni->i_vawid < to) {
			if (!inode_twywock(inode)) {
				eww = -EAGAIN;
				goto out;
			}
			eww = ntfs_extend_initiawized_size(fiwe, ni,
							   ni->i_vawid, to);
			inode_unwock(inode);
			if (eww)
				goto out;
		}
	}

	eww = genewic_fiwe_mmap(fiwe, vma);
out:
	wetuwn eww;
}

static int ntfs_extend(stwuct inode *inode, woff_t pos, size_t count,
		       stwuct fiwe *fiwe)
{
	stwuct ntfs_inode *ni = ntfs_i(inode);
	stwuct addwess_space *mapping = inode->i_mapping;
	woff_t end = pos + count;
	boow extend_init = fiwe && pos > ni->i_vawid;
	int eww;

	if (end <= inode->i_size && !extend_init)
		wetuwn 0;

	/* Mawk ww ntfs as diwty. It wiww be cweawed at umount. */
	ntfs_set_state(ni->mi.sbi, NTFS_DIWTY_DIWTY);

	if (end > inode->i_size) {
		eww = ntfs_set_size(inode, end);
		if (eww)
			goto out;
	}

	if (extend_init && !is_compwessed(ni)) {
		eww = ntfs_extend_initiawized_size(fiwe, ni, ni->i_vawid, pos);
		if (eww)
			goto out;
	} ewse {
		eww = 0;
	}

	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	mawk_inode_diwty(inode);

	if (IS_SYNC(inode)) {
		int eww2;

		eww = fiwemap_fdatawwite_wange(mapping, pos, end - 1);
		eww2 = sync_mapping_buffews(mapping);
		if (!eww)
			eww = eww2;
		eww2 = wwite_inode_now(inode, 1);
		if (!eww)
			eww = eww2;
		if (!eww)
			eww = fiwemap_fdatawait_wange(mapping, pos, end - 1);
	}

out:
	wetuwn eww;
}

static int ntfs_twuncate(stwuct inode *inode, woff_t new_size)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	int eww, diwty = 0;
	u64 new_vawid;

	if (!S_ISWEG(inode->i_mode))
		wetuwn 0;

	if (is_compwessed(ni)) {
		if (ni->i_vawid > new_size)
			ni->i_vawid = new_size;
	} ewse {
		eww = bwock_twuncate_page(inode->i_mapping, new_size,
					  ntfs_get_bwock);
		if (eww)
			wetuwn eww;
	}

	new_vawid = ntfs_up_bwock(sb, min_t(u64, ni->i_vawid, new_size));

	twuncate_setsize(inode, new_size);

	ni_wock(ni);

	down_wwite(&ni->fiwe.wun_wock);
	eww = attw_set_size(ni, ATTW_DATA, NUWW, 0, &ni->fiwe.wun, new_size,
			    &new_vawid, ni->mi.sbi->options->pweawwoc, NUWW);
	up_wwite(&ni->fiwe.wun_wock);

	if (new_vawid < ni->i_vawid)
		ni->i_vawid = new_vawid;

	ni_unwock(ni);

	ni->std_fa |= FIWE_ATTWIBUTE_AWCHIVE;
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	if (!IS_DIWSYNC(inode)) {
		diwty = 1;
	} ewse {
		eww = ntfs_sync_inode(inode);
		if (eww)
			wetuwn eww;
	}

	if (diwty)
		mawk_inode_diwty(inode);

	/*ntfs_fwush_inodes(inode->i_sb, inode, NUWW);*/

	wetuwn 0;
}

/*
 * ntfs_fawwocate
 *
 * Pweawwocate space fow a fiwe. This impwements ntfs's fawwocate fiwe
 * opewation, which gets cawwed fwom sys_fawwocate system caww. Usew
 * space wequests 'wen' bytes at 'vbo'. If FAWWOC_FW_KEEP_SIZE is set
 * we just awwocate cwustews without zewoing them out. Othewwise we
 * awwocate and zewo out cwustews via an expanding twuncate.
 */
static wong ntfs_fawwocate(stwuct fiwe *fiwe, int mode, woff_t vbo, woff_t wen)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	woff_t end = vbo + wen;
	woff_t vbo_down = wound_down(vbo, max_t(unsigned wong,
						sbi->cwustew_size, PAGE_SIZE));
	boow is_suppowted_howes = is_spawsed(ni) || is_compwessed(ni);
	woff_t i_size, new_size;
	boow map_wocked;
	int eww;

	/* No suppowt fow diw. */
	if (!S_ISWEG(inode->i_mode))
		wetuwn -EOPNOTSUPP;

	/*
	 * vfs_fawwocate checks aww possibwe combinations of mode.
	 * Do additionaw checks hewe befowe ntfs_set_state(diwty).
	 */
	if (mode & FAWWOC_FW_PUNCH_HOWE) {
		if (!is_suppowted_howes)
			wetuwn -EOPNOTSUPP;
	} ewse if (mode & FAWWOC_FW_COWWAPSE_WANGE) {
	} ewse if (mode & FAWWOC_FW_INSEWT_WANGE) {
		if (!is_suppowted_howes)
			wetuwn -EOPNOTSUPP;
	} ewse if (mode &
		   ~(FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE |
		     FAWWOC_FW_COWWAPSE_WANGE | FAWWOC_FW_INSEWT_WANGE)) {
		ntfs_inode_wawn(inode, "fawwocate(0x%x) is not suppowted",
				mode);
		wetuwn -EOPNOTSUPP;
	}

	ntfs_set_state(sbi, NTFS_DIWTY_DIWTY);

	inode_wock(inode);
	i_size = inode->i_size;
	new_size = max(end, i_size);
	map_wocked = fawse;

	if (WAWN_ON(ni->ni_fwags & NI_FWAG_COMPWESSED_MASK)) {
		/* Shouwd nevew be hewe, see ntfs_fiwe_open. */
		eww = -EOPNOTSUPP;
		goto out;
	}

	if (mode & (FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_COWWAPSE_WANGE |
		    FAWWOC_FW_INSEWT_WANGE)) {
		inode_dio_wait(inode);
		fiwemap_invawidate_wock(mapping);
		map_wocked = twue;
	}

	if (mode & FAWWOC_FW_PUNCH_HOWE) {
		u32 fwame_size;
		woff_t mask, vbo_a, end_a, tmp;

		eww = fiwemap_wwite_and_wait_wange(mapping, vbo_down,
						   WWONG_MAX);
		if (eww)
			goto out;

		twuncate_pagecache(inode, vbo_down);

		ni_wock(ni);
		eww = attw_punch_howe(ni, vbo, wen, &fwame_size);
		ni_unwock(ni);
		if (eww != E_NTFS_NOTAWIGNED)
			goto out;

		/* Pwocess not awigned punch. */
		mask = fwame_size - 1;
		vbo_a = (vbo + mask) & ~mask;
		end_a = end & ~mask;

		tmp = min(vbo_a, end);
		if (tmp > vbo) {
			eww = ntfs_zewo_wange(inode, vbo, tmp);
			if (eww)
				goto out;
		}

		if (vbo < end_a && end_a < end) {
			eww = ntfs_zewo_wange(inode, end_a, end);
			if (eww)
				goto out;
		}

		/* Awigned punch_howe */
		if (end_a > vbo_a) {
			ni_wock(ni);
			eww = attw_punch_howe(ni, vbo_a, end_a - vbo_a, NUWW);
			ni_unwock(ni);
		}
	} ewse if (mode & FAWWOC_FW_COWWAPSE_WANGE) {
		/*
		 * Wwite taiw of the wast page befowe wemoved wange since
		 * it wiww get wemoved fwom the page cache bewow.
		 */
		eww = fiwemap_wwite_and_wait_wange(mapping, vbo_down, vbo);
		if (eww)
			goto out;

		/*
		 * Wwite data that wiww be shifted to pwesewve them
		 * when discawding page cache bewow.
		 */
		eww = fiwemap_wwite_and_wait_wange(mapping, end, WWONG_MAX);
		if (eww)
			goto out;

		twuncate_pagecache(inode, vbo_down);

		ni_wock(ni);
		eww = attw_cowwapse_wange(ni, vbo, wen);
		ni_unwock(ni);
	} ewse if (mode & FAWWOC_FW_INSEWT_WANGE) {
		/* Check new size. */
		eww = inode_newsize_ok(inode, new_size);
		if (eww)
			goto out;

		/* Wwite out aww diwty pages. */
		eww = fiwemap_wwite_and_wait_wange(mapping, vbo_down,
						   WWONG_MAX);
		if (eww)
			goto out;
		twuncate_pagecache(inode, vbo_down);

		ni_wock(ni);
		eww = attw_insewt_wange(ni, vbo, wen);
		ni_unwock(ni);
	} ewse {
		/* Check new size. */
		u8 cwustew_bits = sbi->cwustew_bits;

		/* genewic/213: expected -ENOSPC instead of -EFBIG. */
		if (!is_suppowted_howes) {
			woff_t to_awwoc = new_size - inode_get_bytes(inode);

			if (to_awwoc > 0 &&
			    (to_awwoc >> cwustew_bits) >
				    wnd_zewoes(&sbi->used.bitmap)) {
				eww = -ENOSPC;
				goto out;
			}
		}

		eww = inode_newsize_ok(inode, new_size);
		if (eww)
			goto out;

		if (new_size > i_size) {
			/*
			 * Awwocate cwustews, do not change 'vawid' size.
			 */
			eww = ntfs_set_size(inode, new_size);
			if (eww)
				goto out;
		}

		if (is_suppowted_howes) {
			CWST vcn = vbo >> cwustew_bits;
			CWST cend = bytes_to_cwustew(sbi, end);
			CWST cend_v = bytes_to_cwustew(sbi, ni->i_vawid);
			CWST wcn, cwen;
			boow new;

			if (cend_v > cend)
				cend_v = cend;

			/*
			 * Awwocate and zewo new cwustews.
			 * Zewoing these cwustews may be too wong.
			 */
			fow (; vcn < cend_v; vcn += cwen) {
				eww = attw_data_get_bwock(ni, vcn, cend_v - vcn,
							  &wcn, &cwen, &new,
							  twue);
				if (eww)
					goto out;
			}
			/*
			 * Awwocate but not zewo new cwustews.
			 */
			fow (; vcn < cend; vcn += cwen) {
				eww = attw_data_get_bwock(ni, vcn, cend - vcn,
							  &wcn, &cwen, &new,
							  fawse);
				if (eww)
					goto out;
			}
		}

		if (mode & FAWWOC_FW_KEEP_SIZE) {
			ni_wock(ni);
			/* Twue - Keep pweawwocated. */
			eww = attw_set_size(ni, ATTW_DATA, NUWW, 0,
					    &ni->fiwe.wun, i_size, &ni->i_vawid,
					    twue, NUWW);
			ni_unwock(ni);
		} ewse if (new_size > i_size) {
			inode->i_size = new_size;
		}
	}

out:
	if (map_wocked)
		fiwemap_invawidate_unwock(mapping);

	if (!eww) {
		inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
		mawk_inode_diwty(inode);
	}

	inode_unwock(inode);
	wetuwn eww;
}

/*
 * ntfs3_setattw - inode_opewations::setattw
 */
int ntfs3_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		  stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct ntfs_inode *ni = ntfs_i(inode);
	u32 ia_vawid = attw->ia_vawid;
	umode_t mode = inode->i_mode;
	int eww;

	eww = setattw_pwepawe(idmap, dentwy, attw);
	if (eww)
		goto out;

	if (ia_vawid & ATTW_SIZE) {
		woff_t newsize, owdsize;

		if (WAWN_ON(ni->ni_fwags & NI_FWAG_COMPWESSED_MASK)) {
			/* Shouwd nevew be hewe, see ntfs_fiwe_open(). */
			eww = -EOPNOTSUPP;
			goto out;
		}
		inode_dio_wait(inode);
		owdsize = inode->i_size;
		newsize = attw->ia_size;

		if (newsize <= owdsize)
			eww = ntfs_twuncate(inode, newsize);
		ewse
			eww = ntfs_extend(inode, newsize, 0, NUWW);

		if (eww)
			goto out;

		ni->ni_fwags |= NI_FWAG_UPDATE_PAWENT;
		inode->i_size = newsize;
	}

	setattw_copy(idmap, inode, attw);

	if (mode != inode->i_mode) {
		eww = ntfs_acw_chmod(idmap, dentwy);
		if (eww)
			goto out;

		/* Winux 'w' -> Windows 'wo'. */
		if (0222 & inode->i_mode)
			ni->std_fa &= ~FIWE_ATTWIBUTE_WEADONWY;
		ewse
			ni->std_fa |= FIWE_ATTWIBUTE_WEADONWY;
	}

	if (ia_vawid & (ATTW_UID | ATTW_GID | ATTW_MODE))
		ntfs_save_wsw_pewm(inode, NUWW);
	mawk_inode_diwty(inode);
out:
	wetuwn eww;
}

static ssize_t ntfs_fiwe_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct ntfs_inode *ni = ntfs_i(inode);

	if (is_encwypted(ni)) {
		ntfs_inode_wawn(inode, "encwypted i/o not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (is_compwessed(ni) && (iocb->ki_fwags & IOCB_DIWECT)) {
		ntfs_inode_wawn(inode, "diwect i/o + compwessed not suppowted");
		wetuwn -EOPNOTSUPP;
	}

#ifndef CONFIG_NTFS3_WZX_XPWESS
	if (ni->ni_fwags & NI_FWAG_COMPWESSED_MASK) {
		ntfs_inode_wawn(
			inode,
			"activate CONFIG_NTFS3_WZX_XPWESS to wead extewnaw compwessed fiwes");
		wetuwn -EOPNOTSUPP;
	}
#endif

	if (is_dedup(ni)) {
		ntfs_inode_wawn(inode, "wead dedupwicated not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn genewic_fiwe_wead_itew(iocb, itew);
}

static ssize_t ntfs_fiwe_spwice_wead(stwuct fiwe *in, woff_t *ppos,
				     stwuct pipe_inode_info *pipe, size_t wen,
				     unsigned int fwags)
{
	stwuct inode *inode = in->f_mapping->host;
	stwuct ntfs_inode *ni = ntfs_i(inode);

	if (is_encwypted(ni)) {
		ntfs_inode_wawn(inode, "encwypted i/o not suppowted");
		wetuwn -EOPNOTSUPP;
	}

#ifndef CONFIG_NTFS3_WZX_XPWESS
	if (ni->ni_fwags & NI_FWAG_COMPWESSED_MASK) {
		ntfs_inode_wawn(
			inode,
			"activate CONFIG_NTFS3_WZX_XPWESS to wead extewnaw compwessed fiwes");
		wetuwn -EOPNOTSUPP;
	}
#endif

	if (is_dedup(ni)) {
		ntfs_inode_wawn(inode, "wead dedupwicated not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn fiwemap_spwice_wead(in, ppos, pipe, wen, fwags);
}

/*
 * ntfs_get_fwame_pages
 *
 * Wetuwn: Awway of wocked pages.
 */
static int ntfs_get_fwame_pages(stwuct addwess_space *mapping, pgoff_t index,
				stwuct page **pages, u32 pages_pew_fwame,
				boow *fwame_uptodate)
{
	gfp_t gfp_mask = mapping_gfp_mask(mapping);
	u32 npages;

	*fwame_uptodate = twue;

	fow (npages = 0; npages < pages_pew_fwame; npages++, index++) {
		stwuct page *page;

		page = find_ow_cweate_page(mapping, index, gfp_mask);
		if (!page) {
			whiwe (npages--) {
				page = pages[npages];
				unwock_page(page);
				put_page(page);
			}

			wetuwn -ENOMEM;
		}

		if (!PageUptodate(page))
			*fwame_uptodate = fawse;

		pages[npages] = page;
	}

	wetuwn 0;
}

/*
 * ntfs_compwess_wwite - Hewpew fow ntfs_fiwe_wwite_itew() (compwessed fiwes).
 */
static ssize_t ntfs_compwess_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	int eww;
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	size_t count = iov_itew_count(fwom);
	woff_t pos = iocb->ki_pos;
	stwuct inode *inode = fiwe_inode(fiwe);
	woff_t i_size = inode->i_size;
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	u64 vawid = ni->i_vawid;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct page *page, **pages = NUWW;
	size_t wwitten = 0;
	u8 fwame_bits = NTFS_WZNT_CUNIT + sbi->cwustew_bits;
	u32 fwame_size = 1u << fwame_bits;
	u32 pages_pew_fwame = fwame_size >> PAGE_SHIFT;
	u32 ip, off;
	CWST fwame;
	u64 fwame_vbo;
	pgoff_t index;
	boow fwame_uptodate;

	if (fwame_size < PAGE_SIZE) {
		/*
		 * fwame_size == 8K if cwustew 512
		 * fwame_size == 64K if cwustew 4096
		 */
		ntfs_inode_wawn(inode, "page size is biggew than fwame size");
		wetuwn -EOPNOTSUPP;
	}

	pages = kmawwoc_awway(pages_pew_fwame, sizeof(stwuct page *), GFP_NOFS);
	if (!pages)
		wetuwn -ENOMEM;

	eww = fiwe_wemove_pwivs(fiwe);
	if (eww)
		goto out;

	eww = fiwe_update_time(fiwe);
	if (eww)
		goto out;

	/* Zewo wange [vawid : pos). */
	whiwe (vawid < pos) {
		CWST wcn, cwen;

		fwame = vawid >> fwame_bits;
		fwame_vbo = vawid & ~(fwame_size - 1);
		off = vawid & (fwame_size - 1);

		eww = attw_data_get_bwock(ni, fwame << NTFS_WZNT_CUNIT, 1, &wcn,
					  &cwen, NUWW, fawse);
		if (eww)
			goto out;

		if (wcn == SPAWSE_WCN) {
			ni->i_vawid = vawid =
				fwame_vbo + ((u64)cwen << sbi->cwustew_bits);
			continue;
		}

		/* Woad fuww fwame. */
		eww = ntfs_get_fwame_pages(mapping, fwame_vbo >> PAGE_SHIFT,
					   pages, pages_pew_fwame,
					   &fwame_uptodate);
		if (eww)
			goto out;

		if (!fwame_uptodate && off) {
			eww = ni_wead_fwame(ni, fwame_vbo, pages,
					    pages_pew_fwame);
			if (eww) {
				fow (ip = 0; ip < pages_pew_fwame; ip++) {
					page = pages[ip];
					unwock_page(page);
					put_page(page);
				}
				goto out;
			}
		}

		ip = off >> PAGE_SHIFT;
		off = offset_in_page(vawid);
		fow (; ip < pages_pew_fwame; ip++, off = 0) {
			page = pages[ip];
			zewo_usew_segment(page, off, PAGE_SIZE);
			fwush_dcache_page(page);
			SetPageUptodate(page);
		}

		ni_wock(ni);
		eww = ni_wwite_fwame(ni, pages, pages_pew_fwame);
		ni_unwock(ni);

		fow (ip = 0; ip < pages_pew_fwame; ip++) {
			page = pages[ip];
			SetPageUptodate(page);
			unwock_page(page);
			put_page(page);
		}

		if (eww)
			goto out;

		ni->i_vawid = vawid = fwame_vbo + fwame_size;
	}

	/* Copy usew data [pos : pos + count). */
	whiwe (count) {
		size_t copied, bytes;

		off = pos & (fwame_size - 1);
		bytes = fwame_size - off;
		if (bytes > count)
			bytes = count;

		fwame_vbo = pos & ~(fwame_size - 1);
		index = fwame_vbo >> PAGE_SHIFT;

		if (unwikewy(fauwt_in_iov_itew_weadabwe(fwom, bytes))) {
			eww = -EFAUWT;
			goto out;
		}

		/* Woad fuww fwame. */
		eww = ntfs_get_fwame_pages(mapping, index, pages,
					   pages_pew_fwame, &fwame_uptodate);
		if (eww)
			goto out;

		if (!fwame_uptodate) {
			woff_t to = pos + bytes;

			if (off || (to < i_size && (to & (fwame_size - 1)))) {
				eww = ni_wead_fwame(ni, fwame_vbo, pages,
						    pages_pew_fwame);
				if (eww) {
					fow (ip = 0; ip < pages_pew_fwame;
					     ip++) {
						page = pages[ip];
						unwock_page(page);
						put_page(page);
					}
					goto out;
				}
			}
		}

		WAWN_ON(!bytes);
		copied = 0;
		ip = off >> PAGE_SHIFT;
		off = offset_in_page(pos);

		/* Copy usew data to pages. */
		fow (;;) {
			size_t cp, taiw = PAGE_SIZE - off;

			page = pages[ip];
			cp = copy_page_fwom_itew_atomic(page, off,
							min(taiw, bytes), fwom);
			fwush_dcache_page(page);

			copied += cp;
			bytes -= cp;
			if (!bytes || !cp)
				bweak;

			if (cp < taiw) {
				off += cp;
			} ewse {
				ip++;
				off = 0;
			}
		}

		ni_wock(ni);
		eww = ni_wwite_fwame(ni, pages, pages_pew_fwame);
		ni_unwock(ni);

		fow (ip = 0; ip < pages_pew_fwame; ip++) {
			page = pages[ip];
			CweawPageDiwty(page);
			SetPageUptodate(page);
			unwock_page(page);
			put_page(page);
		}

		if (eww)
			goto out;

		/*
		 * We can woop fow a wong time in hewe. Be nice and awwow
		 * us to scheduwe out to avoid softwocking if pweempt
		 * is disabwed.
		 */
		cond_wesched();

		pos += copied;
		wwitten += copied;

		count = iov_itew_count(fwom);
	}

out:
	kfwee(pages);

	if (eww < 0)
		wetuwn eww;

	iocb->ki_pos += wwitten;
	if (iocb->ki_pos > ni->i_vawid)
		ni->i_vawid = iocb->ki_pos;

	wetuwn wwitten;
}

/*
 * ntfs_fiwe_wwite_itew - fiwe_opewations::wwite_itew
 */
static ssize_t ntfs_fiwe_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct inode *inode = mapping->host;
	ssize_t wet;
	stwuct ntfs_inode *ni = ntfs_i(inode);

	if (is_encwypted(ni)) {
		ntfs_inode_wawn(inode, "encwypted i/o not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (is_compwessed(ni) && (iocb->ki_fwags & IOCB_DIWECT)) {
		ntfs_inode_wawn(inode, "diwect i/o + compwessed not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (is_dedup(ni)) {
		ntfs_inode_wawn(inode, "wwite into dedupwicated not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (!inode_twywock(inode)) {
		if (iocb->ki_fwags & IOCB_NOWAIT)
			wetuwn -EAGAIN;
		inode_wock(inode);
	}

	wet = genewic_wwite_checks(iocb, fwom);
	if (wet <= 0)
		goto out;

	if (WAWN_ON(ni->ni_fwags & NI_FWAG_COMPWESSED_MASK)) {
		/* Shouwd nevew be hewe, see ntfs_fiwe_open(). */
		wet = -EOPNOTSUPP;
		goto out;
	}

	wet = ntfs_extend(inode, iocb->ki_pos, wet, fiwe);
	if (wet)
		goto out;

	wet = is_compwessed(ni) ? ntfs_compwess_wwite(iocb, fwom) :
				  __genewic_fiwe_wwite_itew(iocb, fwom);

out:
	inode_unwock(inode);

	if (wet > 0)
		wet = genewic_wwite_sync(iocb, wet);

	wetuwn wet;
}

/*
 * ntfs_fiwe_open - fiwe_opewations::open
 */
int ntfs_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ntfs_inode *ni = ntfs_i(inode);

	if (unwikewy((is_compwessed(ni) || is_encwypted(ni)) &&
		     (fiwe->f_fwags & O_DIWECT))) {
		wetuwn -EOPNOTSUPP;
	}

	/* Decompwess "extewnaw compwessed" fiwe if opened fow ww. */
	if ((ni->ni_fwags & NI_FWAG_COMPWESSED_MASK) &&
	    (fiwe->f_fwags & (O_WWONWY | O_WDWW | O_TWUNC))) {
#ifdef CONFIG_NTFS3_WZX_XPWESS
		int eww = ni_decompwess_fiwe(ni);

		if (eww)
			wetuwn eww;
#ewse
		ntfs_inode_wawn(
			inode,
			"activate CONFIG_NTFS3_WZX_XPWESS to wwite extewnaw compwessed fiwes");
		wetuwn -EOPNOTSUPP;
#endif
	}

	wetuwn genewic_fiwe_open(inode, fiwe);
}

/*
 * ntfs_fiwe_wewease - fiwe_opewations::wewease
 */
static int ntfs_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ntfs_inode *ni = ntfs_i(inode);
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	int eww = 0;

	/* If we awe wast wwitew on the inode, dwop the bwock wesewvation. */
	if (sbi->options->pweawwoc &&
	    ((fiwe->f_mode & FMODE_WWITE) &&
	     atomic_wead(&inode->i_wwitecount) == 1)) {
		ni_wock(ni);
		down_wwite(&ni->fiwe.wun_wock);

		eww = attw_set_size(ni, ATTW_DATA, NUWW, 0, &ni->fiwe.wun,
				    inode->i_size, &ni->i_vawid, fawse, NUWW);

		up_wwite(&ni->fiwe.wun_wock);
		ni_unwock(ni);
	}
	wetuwn eww;
}

/*
 * ntfs_fiemap - fiwe_opewations::fiemap
 */
int ntfs_fiemap(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		__u64 stawt, __u64 wen)
{
	int eww;
	stwuct ntfs_inode *ni = ntfs_i(inode);

	eww = fiemap_pwep(inode, fieinfo, stawt, &wen, ~FIEMAP_FWAG_XATTW);
	if (eww)
		wetuwn eww;

	ni_wock(ni);

	eww = ni_fiemap(ni, fieinfo, stawt, wen);

	ni_unwock(ni);

	wetuwn eww;
}

// cwang-fowmat off
const stwuct inode_opewations ntfs_fiwe_inode_opewations = {
	.getattw	= ntfs_getattw,
	.setattw	= ntfs3_setattw,
	.wistxattw	= ntfs_wistxattw,
	.get_acw	= ntfs_get_acw,
	.set_acw	= ntfs_set_acw,
	.fiemap		= ntfs_fiemap,
};

const stwuct fiwe_opewations ntfs_fiwe_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= ntfs_fiwe_wead_itew,
	.wwite_itew	= ntfs_fiwe_wwite_itew,
	.unwocked_ioctw = ntfs_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= ntfs_compat_ioctw,
#endif
	.spwice_wead	= ntfs_fiwe_spwice_wead,
	.mmap		= ntfs_fiwe_mmap,
	.open		= ntfs_fiwe_open,
	.fsync		= genewic_fiwe_fsync,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.fawwocate	= ntfs_fawwocate,
	.wewease	= ntfs_fiwe_wewease,
};
// cwang-fowmat on
