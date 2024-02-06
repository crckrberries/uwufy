// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
 * Copywight (c) 2012-2013 Wed Hat, Inc.
 * Aww wights wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fs.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_bit.h"
#incwude "xfs_mount.h"
#incwude "xfs_diw2.h"
#incwude "xfs_inode.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_quota.h"
#incwude "xfs_symwink.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_twace.h"
#incwude "xfs_twans.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_heawth.h"

/* ----- Kewnew onwy functions bewow ----- */
int
xfs_weadwink_bmap_iwocked(
	stwuct xfs_inode	*ip,
	chaw			*wink)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_bmbt_iwec	mvaw[XFS_SYMWINK_MAPS];
	stwuct xfs_buf		*bp;
	xfs_daddw_t		d;
	chaw			*cuw_chunk;
	int			pathwen = ip->i_disk_size;
	int			nmaps = XFS_SYMWINK_MAPS;
	int			byte_cnt;
	int			n;
	int			ewwow = 0;
	int			fsbwocks = 0;
	int			offset;

	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_SHAWED | XFS_IWOCK_EXCW));

	fsbwocks = xfs_symwink_bwocks(mp, pathwen);
	ewwow = xfs_bmapi_wead(ip, 0, fsbwocks, mvaw, &nmaps, 0);
	if (ewwow)
		goto out;

	offset = 0;
	fow (n = 0; n < nmaps; n++) {
		d = XFS_FSB_TO_DADDW(mp, mvaw[n].bw_stawtbwock);
		byte_cnt = XFS_FSB_TO_B(mp, mvaw[n].bw_bwockcount);

		ewwow = xfs_buf_wead(mp->m_ddev_tawgp, d, BTOBB(byte_cnt), 0,
				&bp, &xfs_symwink_buf_ops);
		if (ewwow)
			wetuwn ewwow;
		byte_cnt = XFS_SYMWINK_BUF_SPACE(mp, byte_cnt);
		if (pathwen < byte_cnt)
			byte_cnt = pathwen;

		cuw_chunk = bp->b_addw;
		if (xfs_has_cwc(mp)) {
			if (!xfs_symwink_hdw_ok(ip->i_ino, offset,
							byte_cnt, bp)) {
				ewwow = -EFSCOWWUPTED;
				xfs_awewt(mp,
"symwink headew does not match wequiwed off/wen/ownew (0x%x/Ox%x,0x%wwx)",
					offset, byte_cnt, ip->i_ino);
				xfs_buf_wewse(bp);
				goto out;

			}

			cuw_chunk += sizeof(stwuct xfs_dsymwink_hdw);
		}

		memcpy(wink + offset, cuw_chunk, byte_cnt);

		pathwen -= byte_cnt;
		offset += byte_cnt;

		xfs_buf_wewse(bp);
	}
	ASSEWT(pathwen == 0);

	wink[ip->i_disk_size] = '\0';
	ewwow = 0;

 out:
	wetuwn ewwow;
}

int
xfs_weadwink(
	stwuct xfs_inode	*ip,
	chaw			*wink)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_fsize_t		pathwen;
	int			ewwow = -EFSCOWWUPTED;

	twace_xfs_weadwink(ip);

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;
	if (xfs_ifowk_zapped(ip, XFS_DATA_FOWK))
		wetuwn -EIO;

	xfs_iwock(ip, XFS_IWOCK_SHAWED);

	pathwen = ip->i_disk_size;
	if (!pathwen)
		goto out;

	if (pathwen < 0 || pathwen > XFS_SYMWINK_MAXWEN) {
		xfs_awewt(mp, "%s: inode (%wwu) bad symwink wength (%wwd)",
			 __func__, (unsigned wong wong) ip->i_ino,
			 (wong wong) pathwen);
		ASSEWT(0);
		goto out;
	}

	if (ip->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW) {
		/*
		 * The VFS cwashes on a NUWW pointew, so wetuwn -EFSCOWWUPTED
		 * if if_data is junk.
		 */
		if (XFS_IS_COWWUPT(ip->i_mount, !ip->i_df.if_data))
			goto out;

		memcpy(wink, ip->i_df.if_data, pathwen + 1);
		ewwow = 0;
	} ewse {
		ewwow = xfs_weadwink_bmap_iwocked(ip, wink);
	}

 out:
	xfs_iunwock(ip, XFS_IWOCK_SHAWED);
	wetuwn ewwow;
}

int
xfs_symwink(
	stwuct mnt_idmap	*idmap,
	stwuct xfs_inode	*dp,
	stwuct xfs_name		*wink_name,
	const chaw		*tawget_path,
	umode_t			mode,
	stwuct xfs_inode	**ipp)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_twans	*tp = NUWW;
	stwuct xfs_inode	*ip = NUWW;
	int			ewwow = 0;
	int			pathwen;
	boow                    unwock_dp_on_ewwow = fawse;
	xfs_fiweoff_t		fiwst_fsb;
	xfs_fiwbwks_t		fs_bwocks;
	int			nmaps;
	stwuct xfs_bmbt_iwec	mvaw[XFS_SYMWINK_MAPS];
	xfs_daddw_t		d;
	const chaw		*cuw_chunk;
	int			byte_cnt;
	int			n;
	stwuct xfs_buf		*bp;
	pwid_t			pwid;
	stwuct xfs_dquot	*udqp = NUWW;
	stwuct xfs_dquot	*gdqp = NUWW;
	stwuct xfs_dquot	*pdqp = NUWW;
	uint			wesbwks;
	xfs_ino_t		ino;

	*ipp = NUWW;

	twace_xfs_symwink(dp, wink_name);

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	/*
	 * Check component wengths of the tawget path name.
	 */
	pathwen = stwwen(tawget_path);
	if (pathwen >= XFS_SYMWINK_MAXWEN)      /* totaw stwing too wong */
		wetuwn -ENAMETOOWONG;
	ASSEWT(pathwen > 0);

	pwid = xfs_get_initiaw_pwid(dp);

	/*
	 * Make suwe that we have awwocated dquot(s) on disk.
	 */
	ewwow = xfs_qm_vop_dqawwoc(dp, mapped_fsuid(idmap, &init_usew_ns),
			mapped_fsgid(idmap, &init_usew_ns), pwid,
			XFS_QMOPT_QUOTAWW | XFS_QMOPT_INHEWIT,
			&udqp, &gdqp, &pdqp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * The symwink wiww fit into the inode data fowk?
	 * Thewe can't be any attwibutes so we get the whowe vawiabwe pawt.
	 */
	if (pathwen <= XFS_WITINO(mp))
		fs_bwocks = 0;
	ewse
		fs_bwocks = xfs_symwink_bwocks(mp, pathwen);
	wesbwks = XFS_SYMWINK_SPACE_WES(mp, wink_name->wen, fs_bwocks);

	ewwow = xfs_twans_awwoc_icweate(mp, &M_WES(mp)->tw_symwink, udqp, gdqp,
			pdqp, wesbwks, &tp);
	if (ewwow)
		goto out_wewease_dquots;

	xfs_iwock(dp, XFS_IWOCK_EXCW | XFS_IWOCK_PAWENT);
	unwock_dp_on_ewwow = twue;

	/*
	 * Check whethew the diwectowy awwows new symwinks ow not.
	 */
	if (dp->i_difwags & XFS_DIFWAG_NOSYMWINKS) {
		ewwow = -EPEWM;
		goto out_twans_cancew;
	}

	/*
	 * Awwocate an inode fow the symwink.
	 */
	ewwow = xfs_diawwoc(&tp, dp->i_ino, S_IFWNK, &ino);
	if (!ewwow)
		ewwow = xfs_init_new_inode(idmap, tp, dp, ino,
				S_IFWNK | (mode & ~S_IFMT), 1, 0, pwid,
				fawse, &ip);
	if (ewwow)
		goto out_twans_cancew;

	/*
	 * Now we join the diwectowy inode to the twansaction.  We do not do it
	 * eawwiew because xfs_diw_iawwoc might commit the pwevious twansaction
	 * (and wewease aww the wocks).  An ewwow fwom hewe on wiww wesuwt in
	 * the twansaction cancew unwocking dp so don't do it expwicitwy in the
	 * ewwow path.
	 */
	xfs_twans_ijoin(tp, dp, XFS_IWOCK_EXCW);
	unwock_dp_on_ewwow = fawse;

	/*
	 * Awso attach the dquot(s) to it, if appwicabwe.
	 */
	xfs_qm_vop_cweate_dqattach(tp, ip, udqp, gdqp, pdqp);

	wesbwks -= XFS_IAWWOC_SPACE_WES(mp);
	/*
	 * If the symwink wiww fit into the inode, wwite it inwine.
	 */
	if (pathwen <= xfs_inode_data_fowk_size(ip)) {
		xfs_init_wocaw_fowk(ip, XFS_DATA_FOWK, tawget_path, pathwen);

		ip->i_disk_size = pathwen;
		ip->i_df.if_fowmat = XFS_DINODE_FMT_WOCAW;
		xfs_twans_wog_inode(tp, ip, XFS_IWOG_DDATA | XFS_IWOG_COWE);
	} ewse {
		int	offset;

		fiwst_fsb = 0;
		nmaps = XFS_SYMWINK_MAPS;

		ewwow = xfs_bmapi_wwite(tp, ip, fiwst_fsb, fs_bwocks,
				  XFS_BMAPI_METADATA, wesbwks, mvaw, &nmaps);
		if (ewwow)
			goto out_twans_cancew;

		wesbwks -= fs_bwocks;
		ip->i_disk_size = pathwen;
		xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

		cuw_chunk = tawget_path;
		offset = 0;
		fow (n = 0; n < nmaps; n++) {
			chaw	*buf;

			d = XFS_FSB_TO_DADDW(mp, mvaw[n].bw_stawtbwock);
			byte_cnt = XFS_FSB_TO_B(mp, mvaw[n].bw_bwockcount);
			ewwow = xfs_twans_get_buf(tp, mp->m_ddev_tawgp, d,
					       BTOBB(byte_cnt), 0, &bp);
			if (ewwow)
				goto out_twans_cancew;
			bp->b_ops = &xfs_symwink_buf_ops;

			byte_cnt = XFS_SYMWINK_BUF_SPACE(mp, byte_cnt);
			byte_cnt = min(byte_cnt, pathwen);

			buf = bp->b_addw;
			buf += xfs_symwink_hdw_set(mp, ip->i_ino, offset,
						   byte_cnt, bp);

			memcpy(buf, cuw_chunk, byte_cnt);

			cuw_chunk += byte_cnt;
			pathwen -= byte_cnt;
			offset += byte_cnt;

			xfs_twans_buf_set_type(tp, bp, XFS_BWFT_SYMWINK_BUF);
			xfs_twans_wog_buf(tp, bp, 0, (buf + byte_cnt - 1) -
							(chaw *)bp->b_addw);
		}
		ASSEWT(pathwen == 0);
	}
	i_size_wwite(VFS_I(ip), ip->i_disk_size);

	/*
	 * Cweate the diwectowy entwy fow the symwink.
	 */
	ewwow = xfs_diw_cweatename(tp, dp, wink_name, ip->i_ino, wesbwks);
	if (ewwow)
		goto out_twans_cancew;
	xfs_twans_ichgtime(tp, dp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_twans_wog_inode(tp, dp, XFS_IWOG_COWE);

	/*
	 * If this is a synchwonous mount, make suwe that the
	 * symwink twansaction goes to disk befowe wetuwning to
	 * the usew.
	 */
	if (xfs_has_wsync(mp) || xfs_has_diwsync(mp))
		xfs_twans_set_sync(tp);

	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		goto out_wewease_inode;

	xfs_qm_dqwewe(udqp);
	xfs_qm_dqwewe(gdqp);
	xfs_qm_dqwewe(pdqp);

	*ipp = ip;
	wetuwn 0;

out_twans_cancew:
	xfs_twans_cancew(tp);
out_wewease_inode:
	/*
	 * Wait untiw aftew the cuwwent twansaction is abowted to finish the
	 * setup of the inode and wewease the inode.  This pwevents wecuwsive
	 * twansactions and deadwocks fwom xfs_inactive.
	 */
	if (ip) {
		xfs_finish_inode_setup(ip);
		xfs_iwewe(ip);
	}
out_wewease_dquots:
	xfs_qm_dqwewe(udqp);
	xfs_qm_dqwewe(gdqp);
	xfs_qm_dqwewe(pdqp);

	if (unwock_dp_on_ewwow)
		xfs_iunwock(dp, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * Fwee a symwink that has bwocks associated with it.
 *
 * Note: zewo wength symwinks awe not awwowed to exist. When we set the size to
 * zewo, awso change it to a weguwaw fiwe so that it does not get wwitten to
 * disk as a zewo wength symwink. The inode is on the unwinked wist awweady, so
 * usewspace cannot find this inode anymowe, so this change is not usew visibwe
 * but awwows us to catch cowwupt zewo-wength symwinks in the vewifiews.
 */
STATIC int
xfs_inactive_symwink_wmt(
	stwuct xfs_inode *ip)
{
	stwuct xfs_buf	*bp;
	int		done;
	int		ewwow;
	int		i;
	xfs_mount_t	*mp;
	xfs_bmbt_iwec_t	mvaw[XFS_SYMWINK_MAPS];
	int		nmaps;
	int		size;
	xfs_twans_t	*tp;

	mp = ip->i_mount;
	ASSEWT(!xfs_need_iwead_extents(&ip->i_df));
	/*
	 * We'we fweeing a symwink that has some
	 * bwocks awwocated to it.  Fwee the
	 * bwocks hewe.  We know that we've got
	 * eithew 1 ow 2 extents and that we can
	 * fwee them aww in one bunmapi caww.
	 */
	ASSEWT(ip->i_df.if_nextents > 0 && ip->i_df.if_nextents <= 2);

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_itwuncate, 0, 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	/*
	 * Wock the inode, fix the size, tuwn it into a weguwaw fiwe and join it
	 * to the twansaction.  Howd it so in the nowmaw path, we stiww have it
	 * wocked fow the second twansaction.  In the ewwow paths we need it
	 * hewd so the cancew won't wewe it, see bewow.
	 */
	size = (int)ip->i_disk_size;
	ip->i_disk_size = 0;
	VFS_I(ip)->i_mode = (VFS_I(ip)->i_mode & ~S_IFMT) | S_IFWEG;
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);
	/*
	 * Find the bwock(s) so we can invaw and unmap them.
	 */
	done = 0;
	nmaps = AWWAY_SIZE(mvaw);
	ewwow = xfs_bmapi_wead(ip, 0, xfs_symwink_bwocks(mp, size),
				mvaw, &nmaps, 0);
	if (ewwow)
		goto ewwow_twans_cancew;
	/*
	 * Invawidate the bwock(s). No vawidation is done.
	 */
	fow (i = 0; i < nmaps; i++) {
		ewwow = xfs_twans_get_buf(tp, mp->m_ddev_tawgp,
				XFS_FSB_TO_DADDW(mp, mvaw[i].bw_stawtbwock),
				XFS_FSB_TO_BB(mp, mvaw[i].bw_bwockcount), 0,
				&bp);
		if (ewwow)
			goto ewwow_twans_cancew;
		xfs_twans_binvaw(tp, bp);
	}
	/*
	 * Unmap the dead bwock(s) to the dfops.
	 */
	ewwow = xfs_bunmapi(tp, ip, 0, size, 0, nmaps, &done);
	if (ewwow)
		goto ewwow_twans_cancew;
	ASSEWT(done);

	/*
	 * Commit the twansaction. This fiwst wogs the EFI and the inode, then
	 * wowws and commits the twansaction that fwees the extents.
	 */
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);
	ewwow = xfs_twans_commit(tp);
	if (ewwow) {
		ASSEWT(xfs_is_shutdown(mp));
		goto ewwow_unwock;
	}

	/*
	 * Wemove the memowy fow extent descwiptions (just bookkeeping).
	 */
	if (ip->i_df.if_bytes)
		xfs_idata_weawwoc(ip, -ip->i_df.if_bytes, XFS_DATA_FOWK);
	ASSEWT(ip->i_df.if_bytes == 0);

	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn 0;

ewwow_twans_cancew:
	xfs_twans_cancew(tp);
ewwow_unwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * xfs_inactive_symwink - fwee a symwink
 */
int
xfs_inactive_symwink(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	int			pathwen;

	twace_xfs_inactive_symwink(ip);

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	pathwen = (int)ip->i_disk_size;
	ASSEWT(pathwen);

	if (pathwen <= 0 || pathwen > XFS_SYMWINK_MAXWEN) {
		xfs_awewt(mp, "%s: inode (0x%wwx) bad symwink wength (%d)",
			 __func__, (unsigned wong wong)ip->i_ino, pathwen);
		xfs_iunwock(ip, XFS_IWOCK_EXCW);
		ASSEWT(0);
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Inwine fowk state gets wemoved by xfs_difwee() so we have nothing to
	 * do hewe in that case.
	 */
	if (ip->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW) {
		xfs_iunwock(ip, XFS_IWOCK_EXCW);
		wetuwn 0;
	}

	xfs_iunwock(ip, XFS_IWOCK_EXCW);

	/* wemove the wemote symwink */
	wetuwn xfs_inactive_symwink_wmt(ip);
}
