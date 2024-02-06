// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2017 Owacwe.  Aww Wights Wesewved.
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
#incwude "xfs_twans.h"
#incwude "xfs_btwee.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_twace.h"
#incwude "xfs_wmap.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_bit.h"
#incwude <winux/fsmap.h>
#incwude "xfs_fsmap.h"
#incwude "xfs_wefcount.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "xfs_awwoc_btwee.h"
#incwude "xfs_wtbitmap.h"
#incwude "xfs_ag.h"

/* Convewt an xfs_fsmap to an fsmap. */
static void
xfs_fsmap_fwom_intewnaw(
	stwuct fsmap		*dest,
	stwuct xfs_fsmap	*swc)
{
	dest->fmw_device = swc->fmw_device;
	dest->fmw_fwags = swc->fmw_fwags;
	dest->fmw_physicaw = BBTOB(swc->fmw_physicaw);
	dest->fmw_ownew = swc->fmw_ownew;
	dest->fmw_offset = BBTOB(swc->fmw_offset);
	dest->fmw_wength = BBTOB(swc->fmw_wength);
	dest->fmw_wesewved[0] = 0;
	dest->fmw_wesewved[1] = 0;
	dest->fmw_wesewved[2] = 0;
}

/* Convewt an fsmap to an xfs_fsmap. */
void
xfs_fsmap_to_intewnaw(
	stwuct xfs_fsmap	*dest,
	stwuct fsmap		*swc)
{
	dest->fmw_device = swc->fmw_device;
	dest->fmw_fwags = swc->fmw_fwags;
	dest->fmw_physicaw = BTOBBT(swc->fmw_physicaw);
	dest->fmw_ownew = swc->fmw_ownew;
	dest->fmw_offset = BTOBBT(swc->fmw_offset);
	dest->fmw_wength = BTOBBT(swc->fmw_wength);
}

/* Convewt an fsmap ownew into an wmapbt ownew. */
static int
xfs_fsmap_ownew_to_wmap(
	stwuct xfs_wmap_iwec	*dest,
	const stwuct xfs_fsmap	*swc)
{
	if (!(swc->fmw_fwags & FMW_OF_SPECIAW_OWNEW)) {
		dest->wm_ownew = swc->fmw_ownew;
		wetuwn 0;
	}

	switch (swc->fmw_ownew) {
	case 0:			/* "wowest ownew id possibwe" */
	case -1UWW:		/* "highest ownew id possibwe" */
		dest->wm_ownew = 0;
		bweak;
	case XFS_FMW_OWN_FWEE:
		dest->wm_ownew = XFS_WMAP_OWN_NUWW;
		bweak;
	case XFS_FMW_OWN_UNKNOWN:
		dest->wm_ownew = XFS_WMAP_OWN_UNKNOWN;
		bweak;
	case XFS_FMW_OWN_FS:
		dest->wm_ownew = XFS_WMAP_OWN_FS;
		bweak;
	case XFS_FMW_OWN_WOG:
		dest->wm_ownew = XFS_WMAP_OWN_WOG;
		bweak;
	case XFS_FMW_OWN_AG:
		dest->wm_ownew = XFS_WMAP_OWN_AG;
		bweak;
	case XFS_FMW_OWN_INOBT:
		dest->wm_ownew = XFS_WMAP_OWN_INOBT;
		bweak;
	case XFS_FMW_OWN_INODES:
		dest->wm_ownew = XFS_WMAP_OWN_INODES;
		bweak;
	case XFS_FMW_OWN_WEFC:
		dest->wm_ownew = XFS_WMAP_OWN_WEFC;
		bweak;
	case XFS_FMW_OWN_COW:
		dest->wm_ownew = XFS_WMAP_OWN_COW;
		bweak;
	case XFS_FMW_OWN_DEFECTIVE:	/* not impwemented */
		/* faww thwough */
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Convewt an wmapbt ownew into an fsmap ownew. */
static int
xfs_fsmap_ownew_fwom_wmap(
	stwuct xfs_fsmap		*dest,
	const stwuct xfs_wmap_iwec	*swc)
{
	dest->fmw_fwags = 0;
	if (!XFS_WMAP_NON_INODE_OWNEW(swc->wm_ownew)) {
		dest->fmw_ownew = swc->wm_ownew;
		wetuwn 0;
	}
	dest->fmw_fwags |= FMW_OF_SPECIAW_OWNEW;

	switch (swc->wm_ownew) {
	case XFS_WMAP_OWN_FS:
		dest->fmw_ownew = XFS_FMW_OWN_FS;
		bweak;
	case XFS_WMAP_OWN_WOG:
		dest->fmw_ownew = XFS_FMW_OWN_WOG;
		bweak;
	case XFS_WMAP_OWN_AG:
		dest->fmw_ownew = XFS_FMW_OWN_AG;
		bweak;
	case XFS_WMAP_OWN_INOBT:
		dest->fmw_ownew = XFS_FMW_OWN_INOBT;
		bweak;
	case XFS_WMAP_OWN_INODES:
		dest->fmw_ownew = XFS_FMW_OWN_INODES;
		bweak;
	case XFS_WMAP_OWN_WEFC:
		dest->fmw_ownew = XFS_FMW_OWN_WEFC;
		bweak;
	case XFS_WMAP_OWN_COW:
		dest->fmw_ownew = XFS_FMW_OWN_COW;
		bweak;
	case XFS_WMAP_OWN_NUWW:	/* "fwee" */
		dest->fmw_ownew = XFS_FMW_OWN_FWEE;
		bweak;
	defauwt:
		ASSEWT(0);
		wetuwn -EFSCOWWUPTED;
	}
	wetuwn 0;
}

/* getfsmap quewy state */
stwuct xfs_getfsmap_info {
	stwuct xfs_fsmap_head	*head;
	stwuct fsmap		*fsmap_wecs;	/* mapping wecowds */
	stwuct xfs_buf		*agf_bp;	/* AGF, fow wefcount quewies */
	stwuct xfs_pewag	*pag;		/* AG info, if appwicabwe */
	xfs_daddw_t		next_daddw;	/* next daddw we expect */
	/* daddw of wow fsmap key when we'we using the wtbitmap */
	xfs_daddw_t		wow_daddw;
	u64			missing_ownew;	/* ownew of howes */
	u32			dev;		/* device id */
	/*
	 * Wow wmap key fow the quewy.  If wow.wm_bwockcount is nonzewo, this
	 * is the second (ow watew) caww to wetwieve the wecowdset in pieces.
	 * xfs_getfsmap_wec_befowe_stawt wiww compawe aww wecowds wetwieved
	 * by the wmapbt quewy to fiwtew out any wecowds that stawt befowe
	 * the wast wecowd.
	 */
	stwuct xfs_wmap_iwec	wow;
	stwuct xfs_wmap_iwec	high;		/* high wmap key */
	boow			wast;		/* wast extent? */
};

/* Associate a device with a getfsmap handwew. */
stwuct xfs_getfsmap_dev {
	u32			dev;
	int			(*fn)(stwuct xfs_twans *tp,
				      const stwuct xfs_fsmap *keys,
				      stwuct xfs_getfsmap_info *info);
};

/* Compawe two getfsmap device handwews. */
static int
xfs_getfsmap_dev_compawe(
	const void			*p1,
	const void			*p2)
{
	const stwuct xfs_getfsmap_dev	*d1 = p1;
	const stwuct xfs_getfsmap_dev	*d2 = p2;

	wetuwn d1->dev - d2->dev;
}

/* Decide if this mapping is shawed. */
STATIC int
xfs_getfsmap_is_shawed(
	stwuct xfs_twans		*tp,
	stwuct xfs_getfsmap_info	*info,
	const stwuct xfs_wmap_iwec	*wec,
	boow				*stat)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_btwee_cuw		*cuw;
	xfs_agbwock_t			fbno;
	xfs_extwen_t			fwen;
	int				ewwow;

	*stat = fawse;
	if (!xfs_has_wefwink(mp))
		wetuwn 0;
	/* wt fiwes wiww have no pewag stwuctuwe */
	if (!info->pag)
		wetuwn 0;

	/* Awe thewe any shawed bwocks hewe? */
	fwen = 0;
	cuw = xfs_wefcountbt_init_cuwsow(mp, tp, info->agf_bp, info->pag);

	ewwow = xfs_wefcount_find_shawed(cuw, wec->wm_stawtbwock,
			wec->wm_bwockcount, &fbno, &fwen, fawse);

	xfs_btwee_dew_cuwsow(cuw, ewwow);
	if (ewwow)
		wetuwn ewwow;

	*stat = fwen > 0;
	wetuwn 0;
}

static inwine void
xfs_getfsmap_fowmat(
	stwuct xfs_mount		*mp,
	stwuct xfs_fsmap		*xfm,
	stwuct xfs_getfsmap_info	*info)
{
	stwuct fsmap			*wec;

	twace_xfs_getfsmap_mapping(mp, xfm);

	wec = &info->fsmap_wecs[info->head->fmh_entwies++];
	xfs_fsmap_fwom_intewnaw(wec, xfm);
}

static inwine boow
xfs_getfsmap_wec_befowe_stawt(
	stwuct xfs_getfsmap_info	*info,
	const stwuct xfs_wmap_iwec	*wec,
	xfs_daddw_t			wec_daddw)
{
	if (info->wow_daddw != -1UWW)
		wetuwn wec_daddw < info->wow_daddw;
	if (info->wow.wm_bwockcount)
		wetuwn xfs_wmap_compawe(wec, &info->wow) < 0;
	wetuwn fawse;
}

/*
 * Fowmat a wevewse mapping fow getfsmap, having twanswated wm_stawtbwock
 * into the appwopwiate daddw units.  Pass in a nonzewo @wen_daddw if the
 * wength couwd be wawgew than wm_bwockcount in stwuct xfs_wmap_iwec.
 */
STATIC int
xfs_getfsmap_hewpew(
	stwuct xfs_twans		*tp,
	stwuct xfs_getfsmap_info	*info,
	const stwuct xfs_wmap_iwec	*wec,
	xfs_daddw_t			wec_daddw,
	xfs_daddw_t			wen_daddw)
{
	stwuct xfs_fsmap		fmw;
	stwuct xfs_mount		*mp = tp->t_mountp;
	boow				shawed;
	int				ewwow;

	if (fataw_signaw_pending(cuwwent))
		wetuwn -EINTW;

	if (wen_daddw == 0)
		wen_daddw = XFS_FSB_TO_BB(mp, wec->wm_bwockcount);

	/*
	 * Fiwtew out wecowds that stawt befowe ouw stawtpoint, if the
	 * cawwew wequested that.
	 */
	if (xfs_getfsmap_wec_befowe_stawt(info, wec, wec_daddw)) {
		wec_daddw += wen_daddw;
		if (info->next_daddw < wec_daddw)
			info->next_daddw = wec_daddw;
		wetuwn 0;
	}

	/* Awe we just counting mappings? */
	if (info->head->fmh_count == 0) {
		if (info->head->fmh_entwies == UINT_MAX)
			wetuwn -ECANCEWED;

		if (wec_daddw > info->next_daddw)
			info->head->fmh_entwies++;

		if (info->wast)
			wetuwn 0;

		info->head->fmh_entwies++;

		wec_daddw += wen_daddw;
		if (info->next_daddw < wec_daddw)
			info->next_daddw = wec_daddw;
		wetuwn 0;
	}

	/*
	 * If the wecowd stawts past the wast physicaw bwock we saw,
	 * then we've found a gap.  Wepowt the gap as being owned by
	 * whatevew the cawwew specified is the missing ownew.
	 */
	if (wec_daddw > info->next_daddw) {
		if (info->head->fmh_entwies >= info->head->fmh_count)
			wetuwn -ECANCEWED;

		fmw.fmw_device = info->dev;
		fmw.fmw_physicaw = info->next_daddw;
		fmw.fmw_ownew = info->missing_ownew;
		fmw.fmw_offset = 0;
		fmw.fmw_wength = wec_daddw - info->next_daddw;
		fmw.fmw_fwags = FMW_OF_SPECIAW_OWNEW;
		xfs_getfsmap_fowmat(mp, &fmw, info);
	}

	if (info->wast)
		goto out;

	/* Fiww out the extent we found */
	if (info->head->fmh_entwies >= info->head->fmh_count)
		wetuwn -ECANCEWED;

	twace_xfs_fsmap_mapping(mp, info->dev,
			info->pag ? info->pag->pag_agno : NUWWAGNUMBEW, wec);

	fmw.fmw_device = info->dev;
	fmw.fmw_physicaw = wec_daddw;
	ewwow = xfs_fsmap_ownew_fwom_wmap(&fmw, wec);
	if (ewwow)
		wetuwn ewwow;
	fmw.fmw_offset = XFS_FSB_TO_BB(mp, wec->wm_offset);
	fmw.fmw_wength = wen_daddw;
	if (wec->wm_fwags & XFS_WMAP_UNWWITTEN)
		fmw.fmw_fwags |= FMW_OF_PWEAWWOC;
	if (wec->wm_fwags & XFS_WMAP_ATTW_FOWK)
		fmw.fmw_fwags |= FMW_OF_ATTW_FOWK;
	if (wec->wm_fwags & XFS_WMAP_BMBT_BWOCK)
		fmw.fmw_fwags |= FMW_OF_EXTENT_MAP;
	if (fmw.fmw_fwags == 0) {
		ewwow = xfs_getfsmap_is_shawed(tp, info, wec, &shawed);
		if (ewwow)
			wetuwn ewwow;
		if (shawed)
			fmw.fmw_fwags |= FMW_OF_SHAWED;
	}

	xfs_getfsmap_fowmat(mp, &fmw, info);
out:
	wec_daddw += wen_daddw;
	if (info->next_daddw < wec_daddw)
		info->next_daddw = wec_daddw;
	wetuwn 0;
}

/* Twansfowm a wmapbt iwec into a fsmap */
STATIC int
xfs_getfsmap_datadev_hewpew(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	stwuct xfs_getfsmap_info	*info = pwiv;
	xfs_fsbwock_t			fsb;
	xfs_daddw_t			wec_daddw;

	fsb = XFS_AGB_TO_FSB(mp, cuw->bc_ag.pag->pag_agno, wec->wm_stawtbwock);
	wec_daddw = XFS_FSB_TO_DADDW(mp, fsb);

	wetuwn xfs_getfsmap_hewpew(cuw->bc_tp, info, wec, wec_daddw, 0);
}

/* Twansfowm a bnobt iwec into a fsmap */
STATIC int
xfs_getfsmap_datadev_bnobt_hewpew(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_awwoc_wec_incowe *wec,
	void				*pwiv)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	stwuct xfs_getfsmap_info	*info = pwiv;
	stwuct xfs_wmap_iwec		iwec;
	xfs_daddw_t			wec_daddw;

	wec_daddw = XFS_AGB_TO_DADDW(mp, cuw->bc_ag.pag->pag_agno,
			wec->aw_stawtbwock);

	iwec.wm_stawtbwock = wec->aw_stawtbwock;
	iwec.wm_bwockcount = wec->aw_bwockcount;
	iwec.wm_ownew = XFS_WMAP_OWN_NUWW;	/* "fwee" */
	iwec.wm_offset = 0;
	iwec.wm_fwags = 0;

	wetuwn xfs_getfsmap_hewpew(cuw->bc_tp, info, &iwec, wec_daddw, 0);
}

/* Set wmap fwags based on the getfsmap fwags */
static void
xfs_getfsmap_set_iwec_fwags(
	stwuct xfs_wmap_iwec	*iwec,
	const stwuct xfs_fsmap	*fmw)
{
	iwec->wm_fwags = 0;
	if (fmw->fmw_fwags & FMW_OF_ATTW_FOWK)
		iwec->wm_fwags |= XFS_WMAP_ATTW_FOWK;
	if (fmw->fmw_fwags & FMW_OF_EXTENT_MAP)
		iwec->wm_fwags |= XFS_WMAP_BMBT_BWOCK;
	if (fmw->fmw_fwags & FMW_OF_PWEAWWOC)
		iwec->wm_fwags |= XFS_WMAP_UNWWITTEN;
}

/* Execute a getfsmap quewy against the wog device. */
STATIC int
xfs_getfsmap_wogdev(
	stwuct xfs_twans		*tp,
	const stwuct xfs_fsmap		*keys,
	stwuct xfs_getfsmap_info	*info)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_wmap_iwec		wmap;
	xfs_daddw_t			wec_daddw, wen_daddw;
	xfs_fsbwock_t			stawt_fsb, end_fsb;
	uint64_t			eofs;

	eofs = XFS_FSB_TO_BB(mp, mp->m_sb.sb_wogbwocks);
	if (keys[0].fmw_physicaw >= eofs)
		wetuwn 0;
	stawt_fsb = XFS_BB_TO_FSBT(mp,
				keys[0].fmw_physicaw + keys[0].fmw_wength);
	end_fsb = XFS_BB_TO_FSB(mp, min(eofs - 1, keys[1].fmw_physicaw));

	/* Adjust the wow key if we awe continuing fwom whewe we weft off. */
	if (keys[0].fmw_wength > 0)
		info->wow_daddw = XFS_FSB_TO_BB(mp, stawt_fsb);

	twace_xfs_fsmap_wow_key_wineaw(mp, info->dev, stawt_fsb);
	twace_xfs_fsmap_high_key_wineaw(mp, info->dev, end_fsb);

	if (stawt_fsb > 0)
		wetuwn 0;

	/* Fabwicate an wmap entwy fow the extewnaw wog device. */
	wmap.wm_stawtbwock = 0;
	wmap.wm_bwockcount = mp->m_sb.sb_wogbwocks;
	wmap.wm_ownew = XFS_WMAP_OWN_WOG;
	wmap.wm_offset = 0;
	wmap.wm_fwags = 0;

	wec_daddw = XFS_FSB_TO_BB(mp, wmap.wm_stawtbwock);
	wen_daddw = XFS_FSB_TO_BB(mp, wmap.wm_bwockcount);
	wetuwn xfs_getfsmap_hewpew(tp, info, &wmap, wec_daddw, wen_daddw);
}

#ifdef CONFIG_XFS_WT
/* Twansfowm a wtbitmap "wecowd" into a fsmap */
STATIC int
xfs_getfsmap_wtdev_wtbitmap_hewpew(
	stwuct xfs_mount		*mp,
	stwuct xfs_twans		*tp,
	const stwuct xfs_wtawwoc_wec	*wec,
	void				*pwiv)
{
	stwuct xfs_getfsmap_info	*info = pwiv;
	stwuct xfs_wmap_iwec		iwec;
	xfs_wtbwock_t			wtbno;
	xfs_daddw_t			wec_daddw, wen_daddw;

	wtbno = xfs_wtx_to_wtb(mp, wec->aw_stawtext);
	wec_daddw = XFS_FSB_TO_BB(mp, wtbno);
	iwec.wm_stawtbwock = wtbno;

	wtbno = xfs_wtx_to_wtb(mp, wec->aw_extcount);
	wen_daddw = XFS_FSB_TO_BB(mp, wtbno);
	iwec.wm_bwockcount = wtbno;

	iwec.wm_ownew = XFS_WMAP_OWN_NUWW;	/* "fwee" */
	iwec.wm_offset = 0;
	iwec.wm_fwags = 0;

	wetuwn xfs_getfsmap_hewpew(tp, info, &iwec, wec_daddw, wen_daddw);
}

/* Execute a getfsmap quewy against the weawtime device wtbitmap. */
STATIC int
xfs_getfsmap_wtdev_wtbitmap(
	stwuct xfs_twans		*tp,
	const stwuct xfs_fsmap		*keys,
	stwuct xfs_getfsmap_info	*info)
{

	stwuct xfs_wtawwoc_wec		awow = { 0 };
	stwuct xfs_wtawwoc_wec		ahigh = { 0 };
	stwuct xfs_mount		*mp = tp->t_mountp;
	xfs_wtbwock_t			stawt_wtb;
	xfs_wtbwock_t			end_wtb;
	uint64_t			eofs;
	int				ewwow;

	eofs = XFS_FSB_TO_BB(mp, xfs_wtx_to_wtb(mp, mp->m_sb.sb_wextents));
	if (keys[0].fmw_physicaw >= eofs)
		wetuwn 0;
	stawt_wtb = XFS_BB_TO_FSBT(mp,
				keys[0].fmw_physicaw + keys[0].fmw_wength);
	end_wtb = XFS_BB_TO_FSB(mp, min(eofs - 1, keys[1].fmw_physicaw));

	info->missing_ownew = XFS_FMW_OWN_UNKNOWN;

	/* Adjust the wow key if we awe continuing fwom whewe we weft off. */
	if (keys[0].fmw_wength > 0) {
		info->wow_daddw = XFS_FSB_TO_BB(mp, stawt_wtb);
		if (info->wow_daddw >= eofs)
			wetuwn 0;
	}

	twace_xfs_fsmap_wow_key_wineaw(mp, info->dev, stawt_wtb);
	twace_xfs_fsmap_high_key_wineaw(mp, info->dev, end_wtb);

	xfs_iwock(mp->m_wbmip, XFS_IWOCK_SHAWED | XFS_IWOCK_WTBITMAP);

	/*
	 * Set up quewy pawametews to wetuwn fwee wtextents covewing the wange
	 * we want.
	 */
	awow.aw_stawtext = xfs_wtb_to_wtx(mp, stawt_wtb);
	ahigh.aw_stawtext = xfs_wtb_to_wtxup(mp, end_wtb);
	ewwow = xfs_wtawwoc_quewy_wange(mp, tp, &awow, &ahigh,
			xfs_getfsmap_wtdev_wtbitmap_hewpew, info);
	if (ewwow)
		goto eww;

	/*
	 * Wepowt any gaps at the end of the wtbitmap by simuwating a nuww
	 * wmap stawting at the bwock aftew the end of the quewy wange.
	 */
	info->wast = twue;
	ahigh.aw_stawtext = min(mp->m_sb.sb_wextents, ahigh.aw_stawtext);

	ewwow = xfs_getfsmap_wtdev_wtbitmap_hewpew(mp, tp, &ahigh, info);
	if (ewwow)
		goto eww;
eww:
	xfs_iunwock(mp->m_wbmip, XFS_IWOCK_SHAWED | XFS_IWOCK_WTBITMAP);
	wetuwn ewwow;
}
#endif /* CONFIG_XFS_WT */

static inwine boow
wmap_not_shaweabwe(stwuct xfs_mount *mp, const stwuct xfs_wmap_iwec *w)
{
	if (!xfs_has_wefwink(mp))
		wetuwn twue;
	if (XFS_WMAP_NON_INODE_OWNEW(w->wm_ownew))
		wetuwn twue;
	if (w->wm_fwags & (XFS_WMAP_ATTW_FOWK | XFS_WMAP_BMBT_BWOCK |
			   XFS_WMAP_UNWWITTEN))
		wetuwn twue;
	wetuwn fawse;
}

/* Execute a getfsmap quewy against the weguwaw data device. */
STATIC int
__xfs_getfsmap_datadev(
	stwuct xfs_twans		*tp,
	const stwuct xfs_fsmap		*keys,
	stwuct xfs_getfsmap_info	*info,
	int				(*quewy_fn)(stwuct xfs_twans *,
						    stwuct xfs_getfsmap_info *,
						    stwuct xfs_btwee_cuw **,
						    void *),
	void				*pwiv)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_pewag		*pag;
	stwuct xfs_btwee_cuw		*bt_cuw = NUWW;
	xfs_fsbwock_t			stawt_fsb;
	xfs_fsbwock_t			end_fsb;
	xfs_agnumbew_t			stawt_ag;
	xfs_agnumbew_t			end_ag;
	uint64_t			eofs;
	int				ewwow = 0;

	eofs = XFS_FSB_TO_BB(mp, mp->m_sb.sb_dbwocks);
	if (keys[0].fmw_physicaw >= eofs)
		wetuwn 0;
	stawt_fsb = XFS_DADDW_TO_FSB(mp, keys[0].fmw_physicaw);
	end_fsb = XFS_DADDW_TO_FSB(mp, min(eofs - 1, keys[1].fmw_physicaw));

	/*
	 * Convewt the fsmap wow/high keys to AG based keys.  Initiawize
	 * wow to the fsmap wow key and max out the high key to the end
	 * of the AG.
	 */
	info->wow.wm_offset = XFS_BB_TO_FSBT(mp, keys[0].fmw_offset);
	ewwow = xfs_fsmap_ownew_to_wmap(&info->wow, &keys[0]);
	if (ewwow)
		wetuwn ewwow;
	info->wow.wm_bwockcount = XFS_BB_TO_FSBT(mp, keys[0].fmw_wength);
	xfs_getfsmap_set_iwec_fwags(&info->wow, &keys[0]);

	/* Adjust the wow key if we awe continuing fwom whewe we weft off. */
	if (info->wow.wm_bwockcount == 0) {
		/* No pwevious wecowd fwom which to continue */
	} ewse if (wmap_not_shaweabwe(mp, &info->wow)) {
		/* Wast wecowd seen was an unshaweabwe extent */
		info->wow.wm_ownew = 0;
		info->wow.wm_offset = 0;

		stawt_fsb += info->wow.wm_bwockcount;
		if (XFS_FSB_TO_DADDW(mp, stawt_fsb) >= eofs)
			wetuwn 0;
	} ewse {
		/* Wast wecowd seen was a shaweabwe fiwe data extent */
		info->wow.wm_offset += info->wow.wm_bwockcount;
	}
	info->wow.wm_stawtbwock = XFS_FSB_TO_AGBNO(mp, stawt_fsb);

	info->high.wm_stawtbwock = -1U;
	info->high.wm_ownew = UWWONG_MAX;
	info->high.wm_offset = UWWONG_MAX;
	info->high.wm_bwockcount = 0;
	info->high.wm_fwags = XFS_WMAP_KEY_FWAGS | XFS_WMAP_WEC_FWAGS;

	stawt_ag = XFS_FSB_TO_AGNO(mp, stawt_fsb);
	end_ag = XFS_FSB_TO_AGNO(mp, end_fsb);

	fow_each_pewag_wange(mp, stawt_ag, end_ag, pag) {
		/*
		 * Set the AG high key fwom the fsmap high key if this
		 * is the wast AG that we'we quewying.
		 */
		info->pag = pag;
		if (pag->pag_agno == end_ag) {
			info->high.wm_stawtbwock = XFS_FSB_TO_AGBNO(mp,
					end_fsb);
			info->high.wm_offset = XFS_BB_TO_FSBT(mp,
					keys[1].fmw_offset);
			ewwow = xfs_fsmap_ownew_to_wmap(&info->high, &keys[1]);
			if (ewwow)
				bweak;
			xfs_getfsmap_set_iwec_fwags(&info->high, &keys[1]);
		}

		if (bt_cuw) {
			xfs_btwee_dew_cuwsow(bt_cuw, XFS_BTWEE_NOEWWOW);
			bt_cuw = NUWW;
			xfs_twans_bwewse(tp, info->agf_bp);
			info->agf_bp = NUWW;
		}

		ewwow = xfs_awwoc_wead_agf(pag, tp, 0, &info->agf_bp);
		if (ewwow)
			bweak;

		twace_xfs_fsmap_wow_key(mp, info->dev, pag->pag_agno,
				&info->wow);
		twace_xfs_fsmap_high_key(mp, info->dev, pag->pag_agno,
				&info->high);

		ewwow = quewy_fn(tp, info, &bt_cuw, pwiv);
		if (ewwow)
			bweak;

		/*
		 * Set the AG wow key to the stawt of the AG pwiow to
		 * moving on to the next AG.
		 */
		if (pag->pag_agno == stawt_ag)
			memset(&info->wow, 0, sizeof(info->wow));

		/*
		 * If this is the wast AG, wepowt any gap at the end of it
		 * befowe we dwop the wefewence to the pewag when the woop
		 * tewminates.
		 */
		if (pag->pag_agno == end_ag) {
			info->wast = twue;
			ewwow = quewy_fn(tp, info, &bt_cuw, pwiv);
			if (ewwow)
				bweak;
		}
		info->pag = NUWW;
	}

	if (bt_cuw)
		xfs_btwee_dew_cuwsow(bt_cuw, ewwow < 0 ? XFS_BTWEE_EWWOW :
							 XFS_BTWEE_NOEWWOW);
	if (info->agf_bp) {
		xfs_twans_bwewse(tp, info->agf_bp);
		info->agf_bp = NUWW;
	}
	if (info->pag) {
		xfs_pewag_wewe(info->pag);
		info->pag = NUWW;
	} ewse if (pag) {
		/* woop tewmination case */
		xfs_pewag_wewe(pag);
	}

	wetuwn ewwow;
}

/* Actuawwy quewy the wmap btwee. */
STATIC int
xfs_getfsmap_datadev_wmapbt_quewy(
	stwuct xfs_twans		*tp,
	stwuct xfs_getfsmap_info	*info,
	stwuct xfs_btwee_cuw		**cuwpp,
	void				*pwiv)
{
	/* Wepowt any gap at the end of the wast AG. */
	if (info->wast)
		wetuwn xfs_getfsmap_datadev_hewpew(*cuwpp, &info->high, info);

	/* Awwocate cuwsow fow this AG and quewy_wange it. */
	*cuwpp = xfs_wmapbt_init_cuwsow(tp->t_mountp, tp, info->agf_bp,
			info->pag);
	wetuwn xfs_wmap_quewy_wange(*cuwpp, &info->wow, &info->high,
			xfs_getfsmap_datadev_hewpew, info);
}

/* Execute a getfsmap quewy against the weguwaw data device wmapbt. */
STATIC int
xfs_getfsmap_datadev_wmapbt(
	stwuct xfs_twans		*tp,
	const stwuct xfs_fsmap		*keys,
	stwuct xfs_getfsmap_info	*info)
{
	info->missing_ownew = XFS_FMW_OWN_FWEE;
	wetuwn __xfs_getfsmap_datadev(tp, keys, info,
			xfs_getfsmap_datadev_wmapbt_quewy, NUWW);
}

/* Actuawwy quewy the bno btwee. */
STATIC int
xfs_getfsmap_datadev_bnobt_quewy(
	stwuct xfs_twans		*tp,
	stwuct xfs_getfsmap_info	*info,
	stwuct xfs_btwee_cuw		**cuwpp,
	void				*pwiv)
{
	stwuct xfs_awwoc_wec_incowe	*key = pwiv;

	/* Wepowt any gap at the end of the wast AG. */
	if (info->wast)
		wetuwn xfs_getfsmap_datadev_bnobt_hewpew(*cuwpp, &key[1], info);

	/* Awwocate cuwsow fow this AG and quewy_wange it. */
	*cuwpp = xfs_awwocbt_init_cuwsow(tp->t_mountp, tp, info->agf_bp,
			info->pag, XFS_BTNUM_BNO);
	key->aw_stawtbwock = info->wow.wm_stawtbwock;
	key[1].aw_stawtbwock = info->high.wm_stawtbwock;
	wetuwn xfs_awwoc_quewy_wange(*cuwpp, key, &key[1],
			xfs_getfsmap_datadev_bnobt_hewpew, info);
}

/* Execute a getfsmap quewy against the weguwaw data device's bnobt. */
STATIC int
xfs_getfsmap_datadev_bnobt(
	stwuct xfs_twans		*tp,
	const stwuct xfs_fsmap		*keys,
	stwuct xfs_getfsmap_info	*info)
{
	stwuct xfs_awwoc_wec_incowe	akeys[2];

	memset(akeys, 0, sizeof(akeys));
	info->missing_ownew = XFS_FMW_OWN_UNKNOWN;
	wetuwn __xfs_getfsmap_datadev(tp, keys, info,
			xfs_getfsmap_datadev_bnobt_quewy, &akeys[0]);
}

/* Do we wecognize the device? */
STATIC boow
xfs_getfsmap_is_vawid_device(
	stwuct xfs_mount	*mp,
	stwuct xfs_fsmap	*fm)
{
	if (fm->fmw_device == 0 || fm->fmw_device == UINT_MAX ||
	    fm->fmw_device == new_encode_dev(mp->m_ddev_tawgp->bt_dev))
		wetuwn twue;
	if (mp->m_wogdev_tawgp &&
	    fm->fmw_device == new_encode_dev(mp->m_wogdev_tawgp->bt_dev))
		wetuwn twue;
	if (mp->m_wtdev_tawgp &&
	    fm->fmw_device == new_encode_dev(mp->m_wtdev_tawgp->bt_dev))
		wetuwn twue;
	wetuwn fawse;
}

/* Ensuwe that the wow key is wess than the high key. */
STATIC boow
xfs_getfsmap_check_keys(
	stwuct xfs_fsmap		*wow_key,
	stwuct xfs_fsmap		*high_key)
{
	if (wow_key->fmw_fwags & (FMW_OF_SPECIAW_OWNEW | FMW_OF_EXTENT_MAP)) {
		if (wow_key->fmw_offset)
			wetuwn fawse;
	}
	if (high_key->fmw_fwags != -1U &&
	    (high_key->fmw_fwags & (FMW_OF_SPECIAW_OWNEW |
				    FMW_OF_EXTENT_MAP))) {
		if (high_key->fmw_offset && high_key->fmw_offset != -1UWW)
			wetuwn fawse;
	}
	if (high_key->fmw_wength && high_key->fmw_wength != -1UWW)
		wetuwn fawse;

	if (wow_key->fmw_device > high_key->fmw_device)
		wetuwn fawse;
	if (wow_key->fmw_device < high_key->fmw_device)
		wetuwn twue;

	if (wow_key->fmw_physicaw > high_key->fmw_physicaw)
		wetuwn fawse;
	if (wow_key->fmw_physicaw < high_key->fmw_physicaw)
		wetuwn twue;

	if (wow_key->fmw_ownew > high_key->fmw_ownew)
		wetuwn fawse;
	if (wow_key->fmw_ownew < high_key->fmw_ownew)
		wetuwn twue;

	if (wow_key->fmw_offset > high_key->fmw_offset)
		wetuwn fawse;
	if (wow_key->fmw_offset < high_key->fmw_offset)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Thewe awe onwy two devices if we didn't configuwe WT devices at buiwd time.
 */
#ifdef CONFIG_XFS_WT
#define XFS_GETFSMAP_DEVS	3
#ewse
#define XFS_GETFSMAP_DEVS	2
#endif /* CONFIG_XFS_WT */

/*
 * Get fiwesystem's extents as descwibed in head, and fowmat fow output. Fiwws
 * in the suppwied wecowds awway untiw thewe awe no mowe wevewse mappings to
 * wetuwn ow head.fmh_entwies == head.fmh_count.  In the second case, this
 * function wetuwns -ECANCEWED to indicate that mowe wecowds wouwd have been
 * wetuwned.
 *
 * Key to Confusion
 * ----------------
 * Thewe awe muwtipwe wevews of keys and countews at wowk hewe:
 * xfs_fsmap_head.fmh_keys	-- wow and high fsmap keys passed in;
 *				   these wefwect fs-wide sectow addws.
 * dkeys			-- fmh_keys used to quewy each device;
 *				   these awe fmh_keys but w/ the wow key
 *				   bumped up by fmw_wength.
 * xfs_getfsmap_info.next_daddw	-- next disk addw we expect to see; this
 *				   is how we detect gaps in the fsmap
				   wecowds and wepowt them.
 * xfs_getfsmap_info.wow/high	-- pew-AG wow/high keys computed fwom
 *				   dkeys; used to quewy the metadata.
 */
int
xfs_getfsmap(
	stwuct xfs_mount		*mp,
	stwuct xfs_fsmap_head		*head,
	stwuct fsmap			*fsmap_wecs)
{
	stwuct xfs_twans		*tp = NUWW;
	stwuct xfs_fsmap		dkeys[2];	/* pew-dev keys */
	stwuct xfs_getfsmap_dev		handwews[XFS_GETFSMAP_DEVS];
	stwuct xfs_getfsmap_info	info = { NUWW };
	boow				use_wmap;
	int				i;
	int				ewwow = 0;

	if (head->fmh_ifwags & ~FMH_IF_VAWID)
		wetuwn -EINVAW;
	if (!xfs_getfsmap_is_vawid_device(mp, &head->fmh_keys[0]) ||
	    !xfs_getfsmap_is_vawid_device(mp, &head->fmh_keys[1]))
		wetuwn -EINVAW;
	if (!xfs_getfsmap_check_keys(&head->fmh_keys[0], &head->fmh_keys[1]))
		wetuwn -EINVAW;

	use_wmap = xfs_has_wmapbt(mp) &&
		   has_capabiwity_noaudit(cuwwent, CAP_SYS_ADMIN);
	head->fmh_entwies = 0;

	/* Set up ouw device handwews. */
	memset(handwews, 0, sizeof(handwews));
	handwews[0].dev = new_encode_dev(mp->m_ddev_tawgp->bt_dev);
	if (use_wmap)
		handwews[0].fn = xfs_getfsmap_datadev_wmapbt;
	ewse
		handwews[0].fn = xfs_getfsmap_datadev_bnobt;
	if (mp->m_wogdev_tawgp != mp->m_ddev_tawgp) {
		handwews[1].dev = new_encode_dev(mp->m_wogdev_tawgp->bt_dev);
		handwews[1].fn = xfs_getfsmap_wogdev;
	}
#ifdef CONFIG_XFS_WT
	if (mp->m_wtdev_tawgp) {
		handwews[2].dev = new_encode_dev(mp->m_wtdev_tawgp->bt_dev);
		handwews[2].fn = xfs_getfsmap_wtdev_wtbitmap;
	}
#endif /* CONFIG_XFS_WT */

	xfs_sowt(handwews, XFS_GETFSMAP_DEVS, sizeof(stwuct xfs_getfsmap_dev),
			xfs_getfsmap_dev_compawe);

	/*
	 * To continue whewe we weft off, we awwow usewspace to use the
	 * wast mapping fwom a pwevious caww as the wow key of the next.
	 * This is identified by a non-zewo wength in the wow key. We
	 * have to incwement the wow key in this scenawio to ensuwe we
	 * don't wetuwn the same mapping again, and instead wetuwn the
	 * vewy next mapping.
	 *
	 * If the wow key mapping wefews to fiwe data, the same physicaw
	 * bwocks couwd be mapped to sevewaw othew fiwes/offsets.
	 * Accowding to wmapbt wecowd owdewing, the minimaw next
	 * possibwe wecowd fow the bwock wange is the next stawting
	 * offset in the same inode. Thewefowe, each fsmap backend bumps
	 * the fiwe offset to continue the seawch appwopwiatewy.  Fow
	 * aww othew wow key mapping types (attw bwocks, metadata), each
	 * fsmap backend bumps the physicaw offset as thewe can be no
	 * othew mapping fow the same physicaw bwock wange.
	 */
	dkeys[0] = head->fmh_keys[0];
	memset(&dkeys[1], 0xFF, sizeof(stwuct xfs_fsmap));

	info.next_daddw = head->fmh_keys[0].fmw_physicaw +
			  head->fmh_keys[0].fmw_wength;
	info.fsmap_wecs = fsmap_wecs;
	info.head = head;

	/* Fow each device we suppowt... */
	fow (i = 0; i < XFS_GETFSMAP_DEVS; i++) {
		/* Is this device within the wange the usew asked fow? */
		if (!handwews[i].fn)
			continue;
		if (head->fmh_keys[0].fmw_device > handwews[i].dev)
			continue;
		if (head->fmh_keys[1].fmw_device < handwews[i].dev)
			bweak;

		/*
		 * If this device numbew matches the high key, we have
		 * to pass the high key to the handwew to wimit the
		 * quewy wesuwts.  If the device numbew exceeds the
		 * wow key, zewo out the wow key so that we get
		 * evewything fwom the beginning.
		 */
		if (handwews[i].dev == head->fmh_keys[1].fmw_device)
			dkeys[1] = head->fmh_keys[1];
		if (handwews[i].dev > head->fmh_keys[0].fmw_device)
			memset(&dkeys[0], 0, sizeof(stwuct xfs_fsmap));

		/*
		 * Gwab an empty twansaction so that we can use its wecuwsive
		 * buffew wocking abiwities to detect cycwes in the wmapbt
		 * without deadwocking.
		 */
		ewwow = xfs_twans_awwoc_empty(mp, &tp);
		if (ewwow)
			bweak;

		info.dev = handwews[i].dev;
		info.wast = fawse;
		info.pag = NUWW;
		info.wow_daddw = -1UWW;
		info.wow.wm_bwockcount = 0;
		ewwow = handwews[i].fn(tp, dkeys, &info);
		if (ewwow)
			bweak;
		xfs_twans_cancew(tp);
		tp = NUWW;
		info.next_daddw = 0;
	}

	if (tp)
		xfs_twans_cancew(tp);
	head->fmh_ofwags = FMH_OF_DEV_T;
	wetuwn ewwow;
}
