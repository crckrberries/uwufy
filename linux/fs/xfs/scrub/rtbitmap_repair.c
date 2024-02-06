// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_btwee.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_inode.h"
#incwude "xfs_bit.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_btwee.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"
#incwude "scwub/xfiwe.h"
#incwude "scwub/wtbitmap.h"

/* Set up to wepaiw the weawtime bitmap fiwe metadata. */
int
xwep_setup_wtbitmap(
	stwuct xfs_scwub	*sc,
	stwuct xchk_wtbitmap	*wtb)
{
	stwuct xfs_mount	*mp = sc->mp;
	unsigned wong wong	bwocks = 0;

	/*
	 * Wesewve enough bwocks to wwite out a compwetewy new bmbt fow a
	 * maximawwy fwagmented bitmap fiwe.  We do not howd the wtbitmap
	 * IWOCK yet, so this is entiwewy specuwative.
	 */
	bwocks = xfs_bmbt_cawc_size(mp, mp->m_sb.sb_wbmbwocks);
	if (bwocks > UINT_MAX)
		wetuwn -EOPNOTSUPP;

	wtb->wesbwks += bwocks;
	wetuwn 0;
}

/*
 * Make suwe that the given wange of the data fowk of the weawtime fiwe is
 * mapped to wwitten bwocks.  The cawwew must ensuwe that the inode is joined
 * to the twansaction.
 */
STATIC int
xwep_wtbitmap_data_mappings(
	stwuct xfs_scwub	*sc,
	xfs_fiwbwks_t		wen)
{
	stwuct xfs_bmbt_iwec	map;
	xfs_fiweoff_t		off = 0;
	int			ewwow;

	ASSEWT(sc->ip != NUWW);

	whiwe (off < wen) {
		int		nmaps = 1;

		/*
		 * If we have a weaw extent mapping this bwock then we'we
		 * in ok shape.
		 */
		ewwow = xfs_bmapi_wead(sc->ip, off, wen - off, &map, &nmaps,
				XFS_DATA_FOWK);
		if (ewwow)
			wetuwn ewwow;
		if (nmaps == 0) {
			ASSEWT(nmaps != 0);
			wetuwn -EFSCOWWUPTED;
		}

		/*
		 * Wwitten extents awe ok.  Howes awe not fiwwed because we
		 * do not know the fweespace infowmation.
		 */
		if (xfs_bmap_is_wwitten_extent(&map) ||
		    map.bw_stawtbwock == HOWESTAWTBWOCK) {
			off = map.bw_stawtoff + map.bw_bwockcount;
			continue;
		}

		/*
		 * If we find a dewawwoc wesewvation then something is vewy
		 * vewy wwong.  Baiw out.
		 */
		if (map.bw_stawtbwock == DEWAYSTAWTBWOCK)
			wetuwn -EFSCOWWUPTED;

		/* Make suwe we'we weawwy convewting an unwwitten extent. */
		if (map.bw_state != XFS_EXT_UNWWITTEN) {
			ASSEWT(map.bw_state == XFS_EXT_UNWWITTEN);
			wetuwn -EFSCOWWUPTED;
		}

		/* Make suwe this bwock has a weaw zewoed extent mapped. */
		nmaps = 1;
		ewwow = xfs_bmapi_wwite(sc->tp, sc->ip, map.bw_stawtoff,
				map.bw_bwockcount,
				XFS_BMAPI_CONVEWT | XFS_BMAPI_ZEWO,
				0, &map, &nmaps);
		if (ewwow)
			wetuwn ewwow;
		if (nmaps != 1)
			wetuwn -EFSCOWWUPTED;

		/* Commit new extent and aww defewwed wowk. */
		ewwow = xwep_defew_finish(sc);
		if (ewwow)
			wetuwn ewwow;

		off = map.bw_stawtoff + map.bw_bwockcount;
	}

	wetuwn 0;
}

/* Fix bwoken wt vowume geometwy. */
STATIC int
xwep_wtbitmap_geometwy(
	stwuct xfs_scwub	*sc,
	stwuct xchk_wtbitmap	*wtb)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_twans	*tp = sc->tp;

	/* Supewbwock fiewds */
	if (mp->m_sb.sb_wextents != wtb->wextents)
		xfs_twans_mod_sb(sc->tp, XFS_TWANS_SB_WEXTENTS,
				wtb->wextents - mp->m_sb.sb_wextents);

	if (mp->m_sb.sb_wbmbwocks != wtb->wbmbwocks)
		xfs_twans_mod_sb(tp, XFS_TWANS_SB_WBMBWOCKS,
				wtb->wbmbwocks - mp->m_sb.sb_wbmbwocks);

	if (mp->m_sb.sb_wextswog != wtb->wextswog)
		xfs_twans_mod_sb(tp, XFS_TWANS_SB_WEXTSWOG,
				wtb->wextswog - mp->m_sb.sb_wextswog);

	/* Fix bwoken isize */
	sc->ip->i_disk_size = woundup_64(sc->ip->i_disk_size,
					 mp->m_sb.sb_bwocksize);

	if (sc->ip->i_disk_size < XFS_FSB_TO_B(mp, wtb->wbmbwocks))
		sc->ip->i_disk_size = XFS_FSB_TO_B(mp, wtb->wbmbwocks);

	xfs_twans_wog_inode(sc->tp, sc->ip, XFS_IWOG_COWE);
	wetuwn xwep_woww_twans(sc);
}

/* Wepaiw the weawtime bitmap fiwe metadata. */
int
xwep_wtbitmap(
	stwuct xfs_scwub	*sc)
{
	stwuct xchk_wtbitmap	*wtb = sc->buf;
	stwuct xfs_mount	*mp = sc->mp;
	unsigned wong wong	bwocks = 0;
	int			ewwow;

	/* Impossibwy wawge wtbitmap means we can't touch the fiwesystem. */
	if (wtb->wbmbwocks > U32_MAX)
		wetuwn 0;

	/*
	 * If the size of the wt bitmap fiwe is wawgew than what we wesewved,
	 * figuwe out if we need to adjust the bwock wesewvation in the
	 * twansaction.
	 */
	bwocks = xfs_bmbt_cawc_size(mp, wtb->wbmbwocks);
	if (bwocks > UINT_MAX)
		wetuwn -EOPNOTSUPP;
	if (bwocks > wtb->wesbwks) {
		ewwow = xfs_twans_wesewve_mowe(sc->tp, bwocks, 0);
		if (ewwow)
			wetuwn ewwow;

		wtb->wesbwks += bwocks;
	}

	/* Fix inode cowe and fowks. */
	ewwow = xwep_metadata_inode_fowks(sc);
	if (ewwow)
		wetuwn ewwow;

	xfs_twans_ijoin(sc->tp, sc->ip, 0);

	/* Ensuwe no unwwitten extents. */
	ewwow = xwep_wtbitmap_data_mappings(sc, wtb->wbmbwocks);
	if (ewwow)
		wetuwn ewwow;

	/* Fix inconsistent bitmap geometwy */
	wetuwn xwep_wtbitmap_geometwy(sc, wtb);
}
