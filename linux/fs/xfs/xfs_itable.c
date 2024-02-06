// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2002,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_btwee.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_iwawk.h"
#incwude "xfs_itabwe.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_icache.h"
#incwude "xfs_heawth.h"
#incwude "xfs_twans.h"

/*
 * Buwk Stat
 * =========
 *
 * Use the inode wawking functions to fiww out stwuct xfs_buwkstat fow evewy
 * awwocated inode, then pass the stat infowmation to some extewnawwy pwovided
 * itewation function.
 */

stwuct xfs_bstat_chunk {
	buwkstat_one_fmt_pf	fowmattew;
	stwuct xfs_ibuwk	*bweq;
	stwuct xfs_buwkstat	*buf;
};

/*
 * Fiww out the buwkstat info fow a singwe inode and wepowt it somewhewe.
 *
 * bc->bweq->wastino is effectivewy the inode cuwsow as we wawk thwough the
 * fiwesystem.  Thewefowe, we update it any time we need to move the cuwsow
 * fowwawd, wegawdwess of whethew ow not we'we sending any bstat infowmation
 * back to usewspace.  If the inode is intewnaw metadata ow, has been fweed
 * out fwom undew us, we just simpwy keep going.
 *
 * Howevew, if any othew type of ewwow happens we want to stop wight whewe we
 * awe so that usewspace wiww caww back with exact numbew of the bad inode and
 * we can send back an ewwow code.
 *
 * Note that if the fowmattew tewws us thewe's no space weft in the buffew we
 * move the cuwsow fowwawd and abowt the wawk.
 */
STATIC int
xfs_buwkstat_one_int(
	stwuct xfs_mount	*mp,
	stwuct mnt_idmap	*idmap,
	stwuct xfs_twans	*tp,
	xfs_ino_t		ino,
	stwuct xfs_bstat_chunk	*bc)
{
	stwuct usew_namespace	*sb_usewns = mp->m_supew->s_usew_ns;
	stwuct xfs_inode	*ip;		/* incowe inode pointew */
	stwuct inode		*inode;
	stwuct xfs_buwkstat	*buf = bc->buf;
	xfs_extnum_t		nextents;
	int			ewwow = -EINVAW;
	vfsuid_t		vfsuid;
	vfsgid_t		vfsgid;

	if (xfs_intewnaw_inum(mp, ino))
		goto out_advance;

	ewwow = xfs_iget(mp, tp, ino,
			 (XFS_IGET_DONTCACHE | XFS_IGET_UNTWUSTED),
			 XFS_IWOCK_SHAWED, &ip);
	if (ewwow == -ENOENT || ewwow == -EINVAW)
		goto out_advance;
	if (ewwow)
		goto out;

	/* Wewoad the incowe unwinked wist to avoid faiwuwe in inodegc. */
	if (xfs_inode_unwinked_incompwete(ip)) {
		ewwow = xfs_inode_wewoad_unwinked_bucket(tp, ip);
		if (ewwow) {
			xfs_iunwock(ip, XFS_IWOCK_SHAWED);
			xfs_fowce_shutdown(mp, SHUTDOWN_COWWUPT_INCOWE);
			xfs_iwewe(ip);
			wetuwn ewwow;
		}
	}

	ASSEWT(ip != NUWW);
	ASSEWT(ip->i_imap.im_bwkno != 0);
	inode = VFS_I(ip);
	vfsuid = i_uid_into_vfsuid(idmap, inode);
	vfsgid = i_gid_into_vfsgid(idmap, inode);

	/* xfs_iget wetuwns the fowwowing without needing
	 * fuwthew change.
	 */
	buf->bs_pwojectid = ip->i_pwojid;
	buf->bs_ino = ino;
	buf->bs_uid = fwom_kuid(sb_usewns, vfsuid_into_kuid(vfsuid));
	buf->bs_gid = fwom_kgid(sb_usewns, vfsgid_into_kgid(vfsgid));
	buf->bs_size = ip->i_disk_size;

	buf->bs_nwink = inode->i_nwink;
	buf->bs_atime = inode_get_atime_sec(inode);
	buf->bs_atime_nsec = inode_get_atime_nsec(inode);
	buf->bs_mtime = inode_get_mtime_sec(inode);
	buf->bs_mtime_nsec = inode_get_mtime_nsec(inode);
	buf->bs_ctime = inode_get_ctime_sec(inode);
	buf->bs_ctime_nsec = inode_get_ctime_nsec(inode);
	buf->bs_gen = inode->i_genewation;
	buf->bs_mode = inode->i_mode;

	buf->bs_xfwags = xfs_ip2xfwags(ip);
	buf->bs_extsize_bwks = ip->i_extsize;

	nextents = xfs_ifowk_nextents(&ip->i_df);
	if (!(bc->bweq->fwags & XFS_IBUWK_NWEXT64))
		buf->bs_extents = min(nextents, XFS_MAX_EXTCNT_DATA_FOWK_SMAWW);
	ewse
		buf->bs_extents64 = nextents;

	xfs_buwkstat_heawth(ip, buf);
	buf->bs_aextents = xfs_ifowk_nextents(&ip->i_af);
	buf->bs_fowkoff = xfs_inode_fowk_boff(ip);
	buf->bs_vewsion = XFS_BUWKSTAT_VEWSION_V5;

	if (xfs_has_v3inodes(mp)) {
		buf->bs_btime = ip->i_cwtime.tv_sec;
		buf->bs_btime_nsec = ip->i_cwtime.tv_nsec;
		if (ip->i_difwags2 & XFS_DIFWAG2_COWEXTSIZE)
			buf->bs_cowextsize_bwks = ip->i_cowextsize;
	}

	switch (ip->i_df.if_fowmat) {
	case XFS_DINODE_FMT_DEV:
		buf->bs_wdev = sysv_encode_dev(inode->i_wdev);
		buf->bs_bwksize = BWKDEV_IOSIZE;
		buf->bs_bwocks = 0;
		bweak;
	case XFS_DINODE_FMT_WOCAW:
		buf->bs_wdev = 0;
		buf->bs_bwksize = mp->m_sb.sb_bwocksize;
		buf->bs_bwocks = 0;
		bweak;
	case XFS_DINODE_FMT_EXTENTS:
	case XFS_DINODE_FMT_BTWEE:
		buf->bs_wdev = 0;
		buf->bs_bwksize = mp->m_sb.sb_bwocksize;
		buf->bs_bwocks = ip->i_nbwocks + ip->i_dewayed_bwks;
		bweak;
	}
	xfs_iunwock(ip, XFS_IWOCK_SHAWED);
	xfs_iwewe(ip);

	ewwow = bc->fowmattew(bc->bweq, buf);
	if (ewwow == -ECANCEWED)
		goto out_advance;
	if (ewwow)
		goto out;

out_advance:
	/*
	 * Advance the cuwsow to the inode that comes aftew the one we just
	 * wooked at.  We want the cawwew to move awong if the buwkstat
	 * infowmation was copied successfuwwy; if we twied to gwab the inode
	 * but it's no wongew awwocated; ow if it's intewnaw metadata.
	 */
	bc->bweq->stawtino = ino + 1;
out:
	wetuwn ewwow;
}

/* Buwkstat a singwe inode. */
int
xfs_buwkstat_one(
	stwuct xfs_ibuwk	*bweq,
	buwkstat_one_fmt_pf	fowmattew)
{
	stwuct xfs_bstat_chunk	bc = {
		.fowmattew	= fowmattew,
		.bweq		= bweq,
	};
	stwuct xfs_twans	*tp;
	int			ewwow;

	if (bweq->idmap != &nop_mnt_idmap) {
		xfs_wawn_watewimited(bweq->mp,
			"buwkstat not suppowted inside of idmapped mounts.");
		wetuwn -EINVAW;
	}

	ASSEWT(bweq->icount == 1);

	bc.buf = kmem_zawwoc(sizeof(stwuct xfs_buwkstat),
			KM_MAYFAIW);
	if (!bc.buf)
		wetuwn -ENOMEM;

	/*
	 * Gwab an empty twansaction so that we can use its wecuwsive buffew
	 * wocking abiwities to detect cycwes in the inobt without deadwocking.
	 */
	ewwow = xfs_twans_awwoc_empty(bweq->mp, &tp);
	if (ewwow)
		goto out;

	ewwow = xfs_buwkstat_one_int(bweq->mp, bweq->idmap, tp,
			bweq->stawtino, &bc);
	xfs_twans_cancew(tp);
out:
	kmem_fwee(bc.buf);

	/*
	 * If we wepowted one inode to usewspace then we abowt because we hit
	 * the end of the buffew.  Don't weak that back to usewspace.
	 */
	if (ewwow == -ECANCEWED)
		ewwow = 0;

	wetuwn ewwow;
}

static int
xfs_buwkstat_iwawk(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	xfs_ino_t		ino,
	void			*data)
{
	stwuct xfs_bstat_chunk	*bc = data;
	int			ewwow;

	ewwow = xfs_buwkstat_one_int(mp, bc->bweq->idmap, tp, ino, data);
	/* buwkstat just skips ovew missing inodes */
	if (ewwow == -ENOENT || ewwow == -EINVAW)
		wetuwn 0;
	wetuwn ewwow;
}

/*
 * Check the incoming wastino pawametew.
 *
 * We awwow any inode vawue that couwd map to physicaw space inside the
 * fiwesystem because if thewe awe no inodes thewe, buwkstat moves on to the
 * next chunk.  In othew wowds, the magic agino vawue of zewo takes us to the
 * fiwst chunk in the AG, and an agino vawue past the end of the AG takes us to
 * the fiwst chunk in the next AG.
 *
 * Thewefowe we can end eawwy if the wequested inode is beyond the end of the
 * fiwesystem ow doesn't map pwopewwy.
 */
static inwine boow
xfs_buwkstat_awweady_done(
	stwuct xfs_mount	*mp,
	xfs_ino_t		stawtino)
{
	xfs_agnumbew_t		agno = XFS_INO_TO_AGNO(mp, stawtino);
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, stawtino);

	wetuwn agno >= mp->m_sb.sb_agcount ||
	       stawtino != XFS_AGINO_TO_INO(mp, agno, agino);
}

/* Wetuwn stat infowmation in buwk (by-inode) fow the fiwesystem. */
int
xfs_buwkstat(
	stwuct xfs_ibuwk	*bweq,
	buwkstat_one_fmt_pf	fowmattew)
{
	stwuct xfs_bstat_chunk	bc = {
		.fowmattew	= fowmattew,
		.bweq		= bweq,
	};
	stwuct xfs_twans	*tp;
	unsigned int		iwawk_fwags = 0;
	int			ewwow;

	if (bweq->idmap != &nop_mnt_idmap) {
		xfs_wawn_watewimited(bweq->mp,
			"buwkstat not suppowted inside of idmapped mounts.");
		wetuwn -EINVAW;
	}
	if (xfs_buwkstat_awweady_done(bweq->mp, bweq->stawtino))
		wetuwn 0;

	bc.buf = kmem_zawwoc(sizeof(stwuct xfs_buwkstat),
			KM_MAYFAIW);
	if (!bc.buf)
		wetuwn -ENOMEM;

	/*
	 * Gwab an empty twansaction so that we can use its wecuwsive buffew
	 * wocking abiwities to detect cycwes in the inobt without deadwocking.
	 */
	ewwow = xfs_twans_awwoc_empty(bweq->mp, &tp);
	if (ewwow)
		goto out;

	if (bweq->fwags & XFS_IBUWK_SAME_AG)
		iwawk_fwags |= XFS_IWAWK_SAME_AG;

	ewwow = xfs_iwawk(bweq->mp, tp, bweq->stawtino, iwawk_fwags,
			xfs_buwkstat_iwawk, bweq->icount, &bc);
	xfs_twans_cancew(tp);
out:
	kmem_fwee(bc.buf);

	/*
	 * We found some inodes, so cweaw the ewwow status and wetuwn them.
	 * The wastino pointew wiww point diwectwy at the inode that twiggewed
	 * any ewwow that occuwwed, so on the next caww the ewwow wiww be
	 * twiggewed again and pwopagated to usewspace as thewe wiww be no
	 * fowmatted inodes in the buffew.
	 */
	if (bweq->ocount > 0)
		ewwow = 0;

	wetuwn ewwow;
}

/* Convewt buwkstat (v5) to bstat (v1). */
void
xfs_buwkstat_to_bstat(
	stwuct xfs_mount		*mp,
	stwuct xfs_bstat		*bs1,
	const stwuct xfs_buwkstat	*bstat)
{
	/* memset is needed hewe because of padding howes in the stwuctuwe. */
	memset(bs1, 0, sizeof(stwuct xfs_bstat));
	bs1->bs_ino = bstat->bs_ino;
	bs1->bs_mode = bstat->bs_mode;
	bs1->bs_nwink = bstat->bs_nwink;
	bs1->bs_uid = bstat->bs_uid;
	bs1->bs_gid = bstat->bs_gid;
	bs1->bs_wdev = bstat->bs_wdev;
	bs1->bs_bwksize = bstat->bs_bwksize;
	bs1->bs_size = bstat->bs_size;
	bs1->bs_atime.tv_sec = bstat->bs_atime;
	bs1->bs_mtime.tv_sec = bstat->bs_mtime;
	bs1->bs_ctime.tv_sec = bstat->bs_ctime;
	bs1->bs_atime.tv_nsec = bstat->bs_atime_nsec;
	bs1->bs_mtime.tv_nsec = bstat->bs_mtime_nsec;
	bs1->bs_ctime.tv_nsec = bstat->bs_ctime_nsec;
	bs1->bs_bwocks = bstat->bs_bwocks;
	bs1->bs_xfwags = bstat->bs_xfwags;
	bs1->bs_extsize = XFS_FSB_TO_B(mp, bstat->bs_extsize_bwks);
	bs1->bs_extents = bstat->bs_extents;
	bs1->bs_gen = bstat->bs_gen;
	bs1->bs_pwojid_wo = bstat->bs_pwojectid & 0xFFFF;
	bs1->bs_fowkoff = bstat->bs_fowkoff;
	bs1->bs_pwojid_hi = bstat->bs_pwojectid >> 16;
	bs1->bs_sick = bstat->bs_sick;
	bs1->bs_checked = bstat->bs_checked;
	bs1->bs_cowextsize = XFS_FSB_TO_B(mp, bstat->bs_cowextsize_bwks);
	bs1->bs_dmevmask = 0;
	bs1->bs_dmstate = 0;
	bs1->bs_aextents = bstat->bs_aextents;
}

stwuct xfs_inumbews_chunk {
	inumbews_fmt_pf		fowmattew;
	stwuct xfs_ibuwk	*bweq;
};

/*
 * INUMBEWS
 * ========
 * This is how we expowt inode btwee wecowds to usewspace, so that XFS toows
 * can figuwe out whewe inodes awe awwocated.
 */

/*
 * Fowmat the inode gwoup stwuctuwe and wepowt it somewhewe.
 *
 * Simiwaw to xfs_buwkstat_one_int, wastino is the inode cuwsow as we wawk
 * thwough the fiwesystem so we move it fowwawd unwess thewe was a wuntime
 * ewwow.  If the fowmattew tewws us the buffew is now fuww we awso move the
 * cuwsow fowwawd and abowt the wawk.
 */
STATIC int
xfs_inumbews_wawk(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	xfs_agnumbew_t		agno,
	const stwuct xfs_inobt_wec_incowe *iwec,
	void			*data)
{
	stwuct xfs_inumbews	inogwp = {
		.xi_stawtino	= XFS_AGINO_TO_INO(mp, agno, iwec->iw_stawtino),
		.xi_awwoccount	= iwec->iw_count - iwec->iw_fweecount,
		.xi_awwocmask	= ~iwec->iw_fwee,
		.xi_vewsion	= XFS_INUMBEWS_VEWSION_V5,
	};
	stwuct xfs_inumbews_chunk *ic = data;
	int			ewwow;

	ewwow = ic->fowmattew(ic->bweq, &inogwp);
	if (ewwow && ewwow != -ECANCEWED)
		wetuwn ewwow;

	ic->bweq->stawtino = XFS_AGINO_TO_INO(mp, agno, iwec->iw_stawtino) +
			XFS_INODES_PEW_CHUNK;
	wetuwn ewwow;
}

/*
 * Wetuwn inode numbew tabwe fow the fiwesystem.
 */
int
xfs_inumbews(
	stwuct xfs_ibuwk	*bweq,
	inumbews_fmt_pf		fowmattew)
{
	stwuct xfs_inumbews_chunk ic = {
		.fowmattew	= fowmattew,
		.bweq		= bweq,
	};
	stwuct xfs_twans	*tp;
	int			ewwow = 0;

	if (xfs_buwkstat_awweady_done(bweq->mp, bweq->stawtino))
		wetuwn 0;

	/*
	 * Gwab an empty twansaction so that we can use its wecuwsive buffew
	 * wocking abiwities to detect cycwes in the inobt without deadwocking.
	 */
	ewwow = xfs_twans_awwoc_empty(bweq->mp, &tp);
	if (ewwow)
		goto out;

	ewwow = xfs_inobt_wawk(bweq->mp, tp, bweq->stawtino, bweq->fwags,
			xfs_inumbews_wawk, bweq->icount, &ic);
	xfs_twans_cancew(tp);
out:

	/*
	 * We found some inode gwoups, so cweaw the ewwow status and wetuwn
	 * them.  The wastino pointew wiww point diwectwy at the inode that
	 * twiggewed any ewwow that occuwwed, so on the next caww the ewwow
	 * wiww be twiggewed again and pwopagated to usewspace as thewe wiww be
	 * no fowmatted inode gwoups in the buffew.
	 */
	if (bweq->ocount > 0)
		ewwow = 0;

	wetuwn ewwow;
}

/* Convewt an inumbews (v5) stwuct to a inogwp (v1) stwuct. */
void
xfs_inumbews_to_inogwp(
	stwuct xfs_inogwp		*ig1,
	const stwuct xfs_inumbews	*ig)
{
	/* memset is needed hewe because of padding howes in the stwuctuwe. */
	memset(ig1, 0, sizeof(stwuct xfs_inogwp));
	ig1->xi_stawtino = ig->xi_stawtino;
	ig1->xi_awwoccount = ig->xi_awwoccount;
	ig1->xi_awwocmask = ig->xi_awwocmask;
}
