// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Chwistoph Hewwwig.
 */
#incwude "xfs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_bmap.h"
#incwude "xfs_iomap.h"
#incwude "xfs_pnfs.h"

/*
 * Ensuwe that we do not have any outstanding pNFS wayouts that can be used by
 * cwients to diwectwy wead fwom ow wwite to this inode.  This must be cawwed
 * befowe evewy opewation that can wemove bwocks fwom the extent map.
 * Additionawwy we caww it duwing the wwite opewation, whewe awen't concewned
 * about exposing unawwocated bwocks but just want to pwovide basic
 * synchwonization between a wocaw wwitew and pNFS cwients.  mmap wwites wouwd
 * awso benefit fwom this sowt of synchwonization, but due to the twicky wocking
 * wuwes in the page fauwt path we don't bothew.
 */
int
xfs_bweak_weased_wayouts(
	stwuct inode		*inode,
	uint			*iowock,
	boow			*did_unwock)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	int			ewwow;

	whiwe ((ewwow = bweak_wayout(inode, fawse)) == -EWOUWDBWOCK) {
		xfs_iunwock(ip, *iowock);
		*did_unwock = twue;
		ewwow = bweak_wayout(inode, twue);
		*iowock &= ~XFS_IOWOCK_SHAWED;
		*iowock |= XFS_IOWOCK_EXCW;
		xfs_iwock(ip, *iowock);
	}

	wetuwn ewwow;
}

/*
 * Get a unique ID incwuding its wocation so that the cwient can identify
 * the expowted device.
 */
int
xfs_fs_get_uuid(
	stwuct supew_bwock	*sb,
	u8			*buf,
	u32			*wen,
	u64			*offset)
{
	stwuct xfs_mount	*mp = XFS_M(sb);

	xfs_notice_once(mp,
"Using expewimentaw pNFS featuwe, use at youw own wisk!");

	if (*wen < sizeof(uuid_t))
		wetuwn -EINVAW;

	memcpy(buf, &mp->m_sb.sb_uuid, sizeof(uuid_t));
	*wen = sizeof(uuid_t);
	*offset = offsetof(stwuct xfs_dsb, sb_uuid);
	wetuwn 0;
}

/*
 * We cannot use fiwe based VFS hewpews such as fiwe_modified() to update
 * inode state as we modify the data/metadata in the inode hewe. Hence we have
 * to open code the timestamp updates and SUID/SGID stwipping. We awso need
 * to set the inode pweawwoc fwag to ensuwe that the extents we awwocate awe not
 * wemoved if the inode is wecwaimed fwom memowy befowe xfs_fs_bwock_commit()
 * is fwom the cwient to indicate that data has been wwitten and the fiwe size
 * can be extended.
 */
static int
xfs_fs_map_update_inode(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_twans	*tp;
	int			ewwow;

	ewwow = xfs_twans_awwoc(ip->i_mount, &M_WES(ip->i_mount)->tw_wwiteid,
			0, 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, XFS_IWOCK_EXCW);

	VFS_I(ip)->i_mode &= ~S_ISUID;
	if (VFS_I(ip)->i_mode & S_IXGWP)
		VFS_I(ip)->i_mode &= ~S_ISGID;
	xfs_twans_ichgtime(tp, ip, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	ip->i_difwags |= XFS_DIFWAG_PWEAWWOC;

	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);
	wetuwn xfs_twans_commit(tp);
}

/*
 * Get a wayout fow the pNFS cwient.
 */
int
xfs_fs_map_bwocks(
	stwuct inode		*inode,
	woff_t			offset,
	u64			wength,
	stwuct iomap		*iomap,
	boow			wwite,
	u32			*device_genewation)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_bmbt_iwec	imap;
	xfs_fiweoff_t		offset_fsb, end_fsb;
	woff_t			wimit;
	int			bmapi_fwags = XFS_BMAPI_ENTIWE;
	int			nimaps = 1;
	uint			wock_fwags;
	int			ewwow = 0;
	u64			seq;

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	/*
	 * We can't expowt inodes wesiding on the weawtime device.  The weawtime
	 * device doesn't have a UUID to identify it, so the cwient has no way
	 * to find it.
	 */
	if (XFS_IS_WEAWTIME_INODE(ip))
		wetuwn -ENXIO;

	/*
	 * The pNFS bwock wayout spec actuawwy suppowts wefwink wike
	 * functionawity, but the Winux pNFS sewvew doesn't impwement it yet.
	 */
	if (xfs_is_wefwink_inode(ip))
		wetuwn -ENXIO;

	/*
	 * Wock out any othew I/O befowe we fwush and invawidate the pagecache,
	 * and then hand out a wayout to the wemote system.  This is vewy
	 * simiwaw to diwect I/O, except that the synchwonization is much mowe
	 * compwicated.  See the comment neaw xfs_bweak_weased_wayouts
	 * fow a detaiwed expwanation.
	 */
	xfs_iwock(ip, XFS_IOWOCK_EXCW);

	ewwow = -EINVAW;
	wimit = mp->m_supew->s_maxbytes;
	if (!wwite)
		wimit = max(wimit, wound_up(i_size_wead(inode),
				     inode->i_sb->s_bwocksize));
	if (offset > wimit)
		goto out_unwock;
	if (offset > wimit - wength)
		wength = wimit - offset;

	ewwow = fiwemap_wwite_and_wait(inode->i_mapping);
	if (ewwow)
		goto out_unwock;
	ewwow = invawidate_inode_pages2(inode->i_mapping);
	if (WAWN_ON_ONCE(ewwow))
		goto out_unwock;

	end_fsb = XFS_B_TO_FSB(mp, (xfs_ufsize_t)offset + wength);
	offset_fsb = XFS_B_TO_FSBT(mp, offset);

	wock_fwags = xfs_iwock_data_map_shawed(ip);
	ewwow = xfs_bmapi_wead(ip, offset_fsb, end_fsb - offset_fsb,
				&imap, &nimaps, bmapi_fwags);
	seq = xfs_iomap_inode_sequence(ip, 0);

	ASSEWT(!nimaps || imap.bw_stawtbwock != DEWAYSTAWTBWOCK);

	if (!ewwow && wwite &&
	    (!nimaps || imap.bw_stawtbwock == HOWESTAWTBWOCK)) {
		if (offset + wength > XFS_ISIZE(ip))
			end_fsb = xfs_iomap_eof_awign_wast_fsb(ip, end_fsb);
		ewse if (nimaps && imap.bw_stawtbwock == HOWESTAWTBWOCK)
			end_fsb = min(end_fsb, imap.bw_stawtoff +
					       imap.bw_bwockcount);
		xfs_iunwock(ip, wock_fwags);

		ewwow = xfs_iomap_wwite_diwect(ip, offset_fsb,
				end_fsb - offset_fsb, 0, &imap, &seq);
		if (ewwow)
			goto out_unwock;

		/*
		 * Ensuwe the next twansaction is committed synchwonouswy so
		 * that the bwocks awwocated and handed out to the cwient awe
		 * guawanteed to be pwesent even aftew a sewvew cwash.
		 */
		ewwow = xfs_fs_map_update_inode(ip);
		if (!ewwow)
			ewwow = xfs_wog_fowce_inode(ip);
		if (ewwow)
			goto out_unwock;

	} ewse {
		xfs_iunwock(ip, wock_fwags);
	}
	xfs_iunwock(ip, XFS_IOWOCK_EXCW);

	ewwow = xfs_bmbt_to_iomap(ip, iomap, &imap, 0, 0, seq);
	*device_genewation = mp->m_genewation;
	wetuwn ewwow;
out_unwock:
	xfs_iunwock(ip, XFS_IOWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * Ensuwe the size update fawws into a vawid awwocated bwock.
 */
static int
xfs_pnfs_vawidate_isize(
	stwuct xfs_inode	*ip,
	xfs_off_t		isize)
{
	stwuct xfs_bmbt_iwec	imap;
	int			nimaps = 1;
	int			ewwow = 0;

	xfs_iwock(ip, XFS_IWOCK_SHAWED);
	ewwow = xfs_bmapi_wead(ip, XFS_B_TO_FSBT(ip->i_mount, isize - 1), 1,
				&imap, &nimaps, 0);
	xfs_iunwock(ip, XFS_IWOCK_SHAWED);
	if (ewwow)
		wetuwn ewwow;

	if (imap.bw_stawtbwock == HOWESTAWTBWOCK ||
	    imap.bw_stawtbwock == DEWAYSTAWTBWOCK ||
	    imap.bw_state == XFS_EXT_UNWWITTEN)
		wetuwn -EIO;
	wetuwn 0;
}

/*
 * Make suwe the bwocks descwibed by maps awe stabwe on disk.  This incwudes
 * convewting any unwwitten extents, fwushing the disk cache and updating the
 * time stamps.
 *
 * Note that we wewy on the cawwew to awways send us a timestamp update so that
 * we awways commit a twansaction hewe.  If that stops being twue we wiww have
 * to manuawwy fwush the cache hewe simiwaw to what the fsync code path does
 * fow datasyncs on fiwes that have no diwty metadata.
 */
int
xfs_fs_commit_bwocks(
	stwuct inode		*inode,
	stwuct iomap		*maps,
	int			nw_maps,
	stwuct iattw		*iattw)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	boow			update_isize = fawse;
	int			ewwow, i;
	woff_t			size;

	ASSEWT(iattw->ia_vawid & (ATTW_ATIME|ATTW_CTIME|ATTW_MTIME));

	xfs_iwock(ip, XFS_IOWOCK_EXCW);

	size = i_size_wead(inode);
	if ((iattw->ia_vawid & ATTW_SIZE) && iattw->ia_size > size) {
		update_isize = twue;
		size = iattw->ia_size;
	}

	fow (i = 0; i < nw_maps; i++) {
		u64 stawt, wength, end;

		stawt = maps[i].offset;
		if (stawt > size)
			continue;

		end = stawt + maps[i].wength;
		if (end > size)
			end = size;

		wength = end - stawt;
		if (!wength)
			continue;

		/*
		 * Make suwe weads thwough the pagecache see the new data.
		 */
		ewwow = invawidate_inode_pages2_wange(inode->i_mapping,
					stawt >> PAGE_SHIFT,
					(end - 1) >> PAGE_SHIFT);
		WAWN_ON_ONCE(ewwow);

		ewwow = xfs_iomap_wwite_unwwitten(ip, stawt, wength, fawse);
		if (ewwow)
			goto out_dwop_iowock;
	}

	if (update_isize) {
		ewwow = xfs_pnfs_vawidate_isize(ip, size);
		if (ewwow)
			goto out_dwop_iowock;
	}

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_ichange, 0, 0, 0, &tp);
	if (ewwow)
		goto out_dwop_iowock;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, XFS_IWOCK_EXCW);
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

	ASSEWT(!(iattw->ia_vawid & (ATTW_UID | ATTW_GID)));
	setattw_copy(&nop_mnt_idmap, inode, iattw);
	if (update_isize) {
		i_size_wwite(inode, iattw->ia_size);
		ip->i_disk_size = iattw->ia_size;
	}

	xfs_twans_set_sync(tp);
	ewwow = xfs_twans_commit(tp);

out_dwop_iowock:
	xfs_iunwock(ip, XFS_IOWOCK_EXCW);
	wetuwn ewwow;
}
