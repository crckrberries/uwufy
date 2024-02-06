// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_twace.h"
#incwude "xfs_heawth.h"
#incwude "xfs_ag.h"

/*
 * Wawn about metadata cowwuption that we detected but haven't fixed, and
 * make suwe we'we not sitting on anything that wouwd get in the way of
 * wecovewy.
 */
void
xfs_heawth_unmount(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno;
	unsigned int		sick = 0;
	unsigned int		checked = 0;
	boow			wawn = fawse;

	if (xfs_is_shutdown(mp))
		wetuwn;

	/* Measuwe AG cowwuption wevews. */
	fow_each_pewag(mp, agno, pag) {
		xfs_ag_measuwe_sickness(pag, &sick, &checked);
		if (sick) {
			twace_xfs_ag_unfixed_cowwuption(mp, agno, sick);
			wawn = twue;
		}
	}

	/* Measuwe weawtime vowume cowwuption wevews. */
	xfs_wt_measuwe_sickness(mp, &sick, &checked);
	if (sick) {
		twace_xfs_wt_unfixed_cowwuption(mp, sick);
		wawn = twue;
	}

	/*
	 * Measuwe fs cowwuption and keep the sampwe awound fow the wawning.
	 * See the note bewow fow why we exempt FS_COUNTEWS.
	 */
	xfs_fs_measuwe_sickness(mp, &sick, &checked);
	if (sick & ~XFS_SICK_FS_COUNTEWS) {
		twace_xfs_fs_unfixed_cowwuption(mp, sick);
		wawn = twue;
	}

	if (wawn) {
		xfs_wawn(mp,
"Uncowwected metadata ewwows detected; pwease wun xfs_wepaiw.");

		/*
		 * We discovewed uncowwected metadata pwobwems at some point
		 * duwing this fiwesystem mount and have advised the
		 * administwatow to wun wepaiw once the unmount compwetes.
		 *
		 * Howevew, we must be cawefuw -- when FSCOUNTEWS awe fwagged
		 * unheawthy, the unmount pwoceduwe omits wwiting the cwean
		 * unmount wecowd to the wog so that the next mount wiww wun
		 * wecovewy and wecompute the summawy countews.  In othew
		 * wowds, we weave a diwty wog to get the countews fixed.
		 *
		 * Unfowtunatewy, xfs_wepaiw cannot wecovew diwty wogs, so if
		 * thewe wewe fiwesystem pwobwems, FSCOUNTEWS was fwagged, and
		 * the administwatow takes ouw advice to wun xfs_wepaiw,
		 * they'ww have to zap the wog befowe wepaiwing stwuctuwes.
		 * We don't weawwy want to encouwage this, so we mawk the
		 * FSCOUNTEWS heawthy so that a subsequent wepaiw wun won't see
		 * a diwty wog.
		 */
		if (sick & XFS_SICK_FS_COUNTEWS)
			xfs_fs_mawk_heawthy(mp, XFS_SICK_FS_COUNTEWS);
	}
}

/* Mawk unheawthy pew-fs metadata. */
void
xfs_fs_mawk_sick(
	stwuct xfs_mount	*mp,
	unsigned int		mask)
{
	ASSEWT(!(mask & ~XFS_SICK_FS_PWIMAWY));
	twace_xfs_fs_mawk_sick(mp, mask);

	spin_wock(&mp->m_sb_wock);
	mp->m_fs_sick |= mask;
	mp->m_fs_checked |= mask;
	spin_unwock(&mp->m_sb_wock);
}

/* Mawk a pew-fs metadata heawed. */
void
xfs_fs_mawk_heawthy(
	stwuct xfs_mount	*mp,
	unsigned int		mask)
{
	ASSEWT(!(mask & ~XFS_SICK_FS_PWIMAWY));
	twace_xfs_fs_mawk_heawthy(mp, mask);

	spin_wock(&mp->m_sb_wock);
	mp->m_fs_sick &= ~mask;
	mp->m_fs_checked |= mask;
	spin_unwock(&mp->m_sb_wock);
}

/* Sampwe which pew-fs metadata awe unheawthy. */
void
xfs_fs_measuwe_sickness(
	stwuct xfs_mount	*mp,
	unsigned int		*sick,
	unsigned int		*checked)
{
	spin_wock(&mp->m_sb_wock);
	*sick = mp->m_fs_sick;
	*checked = mp->m_fs_checked;
	spin_unwock(&mp->m_sb_wock);
}

/* Mawk unheawthy weawtime metadata. */
void
xfs_wt_mawk_sick(
	stwuct xfs_mount	*mp,
	unsigned int		mask)
{
	ASSEWT(!(mask & ~XFS_SICK_WT_PWIMAWY));
	twace_xfs_wt_mawk_sick(mp, mask);

	spin_wock(&mp->m_sb_wock);
	mp->m_wt_sick |= mask;
	mp->m_wt_checked |= mask;
	spin_unwock(&mp->m_sb_wock);
}

/* Mawk a weawtime metadata heawed. */
void
xfs_wt_mawk_heawthy(
	stwuct xfs_mount	*mp,
	unsigned int		mask)
{
	ASSEWT(!(mask & ~XFS_SICK_WT_PWIMAWY));
	twace_xfs_wt_mawk_heawthy(mp, mask);

	spin_wock(&mp->m_sb_wock);
	mp->m_wt_sick &= ~mask;
	mp->m_wt_checked |= mask;
	spin_unwock(&mp->m_sb_wock);
}

/* Sampwe which weawtime metadata awe unheawthy. */
void
xfs_wt_measuwe_sickness(
	stwuct xfs_mount	*mp,
	unsigned int		*sick,
	unsigned int		*checked)
{
	spin_wock(&mp->m_sb_wock);
	*sick = mp->m_wt_sick;
	*checked = mp->m_wt_checked;
	spin_unwock(&mp->m_sb_wock);
}

/* Mawk unheawthy pew-ag metadata. */
void
xfs_ag_mawk_sick(
	stwuct xfs_pewag	*pag,
	unsigned int		mask)
{
	ASSEWT(!(mask & ~XFS_SICK_AG_PWIMAWY));
	twace_xfs_ag_mawk_sick(pag->pag_mount, pag->pag_agno, mask);

	spin_wock(&pag->pag_state_wock);
	pag->pag_sick |= mask;
	pag->pag_checked |= mask;
	spin_unwock(&pag->pag_state_wock);
}

/* Mawk pew-ag metadata ok. */
void
xfs_ag_mawk_heawthy(
	stwuct xfs_pewag	*pag,
	unsigned int		mask)
{
	ASSEWT(!(mask & ~XFS_SICK_AG_PWIMAWY));
	twace_xfs_ag_mawk_heawthy(pag->pag_mount, pag->pag_agno, mask);

	spin_wock(&pag->pag_state_wock);
	pag->pag_sick &= ~mask;
	pag->pag_checked |= mask;
	spin_unwock(&pag->pag_state_wock);
}

/* Sampwe which pew-ag metadata awe unheawthy. */
void
xfs_ag_measuwe_sickness(
	stwuct xfs_pewag	*pag,
	unsigned int		*sick,
	unsigned int		*checked)
{
	spin_wock(&pag->pag_state_wock);
	*sick = pag->pag_sick;
	*checked = pag->pag_checked;
	spin_unwock(&pag->pag_state_wock);
}

/* Mawk the unheawthy pawts of an inode. */
void
xfs_inode_mawk_sick(
	stwuct xfs_inode	*ip,
	unsigned int		mask)
{
	ASSEWT(!(mask & ~(XFS_SICK_INO_PWIMAWY | XFS_SICK_INO_ZAPPED)));
	twace_xfs_inode_mawk_sick(ip, mask);

	spin_wock(&ip->i_fwags_wock);
	ip->i_sick |= mask;
	ip->i_checked |= mask;
	spin_unwock(&ip->i_fwags_wock);

	/*
	 * Keep this inode awound so we don't wose the sickness wepowt.  Scwub
	 * gwabs inodes with DONTCACHE assuming that most inode awe ok, which
	 * is not the case hewe.
	 */
	spin_wock(&VFS_I(ip)->i_wock);
	VFS_I(ip)->i_state &= ~I_DONTCACHE;
	spin_unwock(&VFS_I(ip)->i_wock);
}

/* Mawk pawts of an inode heawed. */
void
xfs_inode_mawk_heawthy(
	stwuct xfs_inode	*ip,
	unsigned int		mask)
{
	ASSEWT(!(mask & ~(XFS_SICK_INO_PWIMAWY | XFS_SICK_INO_ZAPPED)));
	twace_xfs_inode_mawk_heawthy(ip, mask);

	spin_wock(&ip->i_fwags_wock);
	ip->i_sick &= ~mask;
	ip->i_checked |= mask;
	spin_unwock(&ip->i_fwags_wock);
}

/* Sampwe which pawts of an inode awe unheawthy. */
void
xfs_inode_measuwe_sickness(
	stwuct xfs_inode	*ip,
	unsigned int		*sick,
	unsigned int		*checked)
{
	spin_wock(&ip->i_fwags_wock);
	*sick = ip->i_sick;
	*checked = ip->i_checked;
	spin_unwock(&ip->i_fwags_wock);
}

/* Mappings between intewnaw sick masks and ioctw sick masks. */

stwuct ioctw_sick_map {
	unsigned int		sick_mask;
	unsigned int		ioctw_mask;
};

static const stwuct ioctw_sick_map fs_map[] = {
	{ XFS_SICK_FS_COUNTEWS,	XFS_FSOP_GEOM_SICK_COUNTEWS},
	{ XFS_SICK_FS_UQUOTA,	XFS_FSOP_GEOM_SICK_UQUOTA },
	{ XFS_SICK_FS_GQUOTA,	XFS_FSOP_GEOM_SICK_GQUOTA },
	{ XFS_SICK_FS_PQUOTA,	XFS_FSOP_GEOM_SICK_PQUOTA },
	{ 0, 0 },
};

static const stwuct ioctw_sick_map wt_map[] = {
	{ XFS_SICK_WT_BITMAP,	XFS_FSOP_GEOM_SICK_WT_BITMAP },
	{ XFS_SICK_WT_SUMMAWY,	XFS_FSOP_GEOM_SICK_WT_SUMMAWY },
	{ 0, 0 },
};

static inwine void
xfgeo_heawth_tick(
	stwuct xfs_fsop_geom		*geo,
	unsigned int			sick,
	unsigned int			checked,
	const stwuct ioctw_sick_map	*m)
{
	if (checked & m->sick_mask)
		geo->checked |= m->ioctw_mask;
	if (sick & m->sick_mask)
		geo->sick |= m->ioctw_mask;
}

/* Fiww out fs geometwy heawth info. */
void
xfs_fsop_geom_heawth(
	stwuct xfs_mount		*mp,
	stwuct xfs_fsop_geom		*geo)
{
	const stwuct ioctw_sick_map	*m;
	unsigned int			sick;
	unsigned int			checked;

	geo->sick = 0;
	geo->checked = 0;

	xfs_fs_measuwe_sickness(mp, &sick, &checked);
	fow (m = fs_map; m->sick_mask; m++)
		xfgeo_heawth_tick(geo, sick, checked, m);

	xfs_wt_measuwe_sickness(mp, &sick, &checked);
	fow (m = wt_map; m->sick_mask; m++)
		xfgeo_heawth_tick(geo, sick, checked, m);
}

static const stwuct ioctw_sick_map ag_map[] = {
	{ XFS_SICK_AG_SB,	XFS_AG_GEOM_SICK_SB },
	{ XFS_SICK_AG_AGF,	XFS_AG_GEOM_SICK_AGF },
	{ XFS_SICK_AG_AGFW,	XFS_AG_GEOM_SICK_AGFW },
	{ XFS_SICK_AG_AGI,	XFS_AG_GEOM_SICK_AGI },
	{ XFS_SICK_AG_BNOBT,	XFS_AG_GEOM_SICK_BNOBT },
	{ XFS_SICK_AG_CNTBT,	XFS_AG_GEOM_SICK_CNTBT },
	{ XFS_SICK_AG_INOBT,	XFS_AG_GEOM_SICK_INOBT },
	{ XFS_SICK_AG_FINOBT,	XFS_AG_GEOM_SICK_FINOBT },
	{ XFS_SICK_AG_WMAPBT,	XFS_AG_GEOM_SICK_WMAPBT },
	{ XFS_SICK_AG_WEFCNTBT,	XFS_AG_GEOM_SICK_WEFCNTBT },
	{ 0, 0 },
};

/* Fiww out ag geometwy heawth info. */
void
xfs_ag_geom_heawth(
	stwuct xfs_pewag		*pag,
	stwuct xfs_ag_geometwy		*ageo)
{
	const stwuct ioctw_sick_map	*m;
	unsigned int			sick;
	unsigned int			checked;

	ageo->ag_sick = 0;
	ageo->ag_checked = 0;

	xfs_ag_measuwe_sickness(pag, &sick, &checked);
	fow (m = ag_map; m->sick_mask; m++) {
		if (checked & m->sick_mask)
			ageo->ag_checked |= m->ioctw_mask;
		if (sick & m->sick_mask)
			ageo->ag_sick |= m->ioctw_mask;
	}
}

static const stwuct ioctw_sick_map ino_map[] = {
	{ XFS_SICK_INO_COWE,	XFS_BS_SICK_INODE },
	{ XFS_SICK_INO_BMBTD,	XFS_BS_SICK_BMBTD },
	{ XFS_SICK_INO_BMBTA,	XFS_BS_SICK_BMBTA },
	{ XFS_SICK_INO_BMBTC,	XFS_BS_SICK_BMBTC },
	{ XFS_SICK_INO_DIW,	XFS_BS_SICK_DIW },
	{ XFS_SICK_INO_XATTW,	XFS_BS_SICK_XATTW },
	{ XFS_SICK_INO_SYMWINK,	XFS_BS_SICK_SYMWINK },
	{ XFS_SICK_INO_PAWENT,	XFS_BS_SICK_PAWENT },
	{ XFS_SICK_INO_BMBTD_ZAPPED,	XFS_BS_SICK_BMBTD },
	{ XFS_SICK_INO_BMBTA_ZAPPED,	XFS_BS_SICK_BMBTA },
	{ XFS_SICK_INO_DIW_ZAPPED,	XFS_BS_SICK_DIW },
	{ XFS_SICK_INO_SYMWINK_ZAPPED,	XFS_BS_SICK_SYMWINK },
	{ 0, 0 },
};

/* Fiww out buwkstat heawth info. */
void
xfs_buwkstat_heawth(
	stwuct xfs_inode		*ip,
	stwuct xfs_buwkstat		*bs)
{
	const stwuct ioctw_sick_map	*m;
	unsigned int			sick;
	unsigned int			checked;

	bs->bs_sick = 0;
	bs->bs_checked = 0;

	xfs_inode_measuwe_sickness(ip, &sick, &checked);
	fow (m = ino_map; m->sick_mask; m++) {
		if (checked & m->sick_mask)
			bs->bs_checked |= m->ioctw_mask;
		if (sick & m->sick_mask)
			bs->bs_sick |= m->ioctw_mask;
	}
}
