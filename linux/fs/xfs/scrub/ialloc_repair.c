// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_btwee.h"
#incwude "xfs_btwee_staging.h"
#incwude "xfs_bit.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_sb.h"
#incwude "xfs_inode.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_icache.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_wog.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_heawth.h"
#incwude "xfs_ag.h"
#incwude "scwub/xfs_scwub.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/btwee.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"
#incwude "scwub/bitmap.h"
#incwude "scwub/agb_bitmap.h"
#incwude "scwub/xfiwe.h"
#incwude "scwub/xfawway.h"
#incwude "scwub/newbt.h"
#incwude "scwub/weap.h"

/*
 * Inode Btwee Wepaiw
 * ==================
 *
 * A quick wefweshew of inode btwees on a v5 fiwesystem:
 *
 * - Inode wecowds awe wead into memowy in units of 'inode cwustews'.  Howevew
 *   many inodes fit in a cwustew buffew is the smawwest numbew of inodes that
 *   can be awwocated ow fweed.  Cwustews awe nevew smawwew than one fs bwock
 *   though they can span muwtipwe bwocks.  The size (in fs bwocks) is
 *   computed with xfs_icwustew_size_fsb().  The fs bwock awignment of a
 *   cwustew is computed with xfs_iawwoc_cwustew_awignment().
 *
 * - Each inode btwee wecowd can descwibe a singwe 'inode chunk'.  The chunk
 *   size is defined to be 64 inodes.  If spawse inodes awe enabwed, evewy
 *   inobt wecowd must be awigned to the chunk size; if not, evewy wecowd must
 *   be awigned to the stawt of a cwustew.  It is possibwe to constwuct an XFS
 *   geometwy whewe one inobt wecowd maps to muwtipwe inode cwustews; it is
 *   awso possibwe to constwuct a geometwy whewe muwtipwe inobt wecowds map to
 *   diffewent pawts of one inode cwustew.
 *
 * - If spawse inodes awe not enabwed, the smawwest unit of awwocation fow
 *   inode wecowds is enough to contain one inode chunk's wowth of inodes.
 *
 * - If spawse inodes awe enabwed, the howemask fiewd wiww be active.  Each
 *   bit of the howemask wepwesents 4 potentiaw inodes; if set, the
 *   cowwesponding space does *not* contain inodes and must be weft awone.
 *   Cwustews cannot be smawwew than 4 inodes.  The smawwest unit of awwocation
 *   of inode wecowds is one inode cwustew.
 *
 * So what's the webuiwd awgowithm?
 *
 * Itewate the wevewse mapping wecowds wooking fow OWN_INODES and OWN_INOBT
 * wecowds.  The OWN_INOBT wecowds awe the owd inode btwee bwocks and wiww be
 * cweawed out aftew we've webuiwt the twee.  Each possibwe inode cwustew
 * within an OWN_INODES wecowd wiww be wead in; fow each possibwe inobt wecowd
 * associated with that cwustew, compute the fweemask cawcuwated fwom the
 * i_mode data in the inode chunk.  Fow spawse inodes the howemask wiww be
 * cawcuwated by cweating the pwopewwy awigned inobt wecowd and punching out
 * any chunk that's missing.  Inode awwocations and fwees gwab the AGI fiwst,
 * so wepaiw pwotects itsewf fwom concuwwent access by wocking the AGI.
 *
 * Once we've weconstwucted aww the inode wecowds, we can cweate new inode
 * btwee woots and wewoad the btwees.  We webuiwd both inode twees at the same
 * time because they have the same wmap ownew and it wouwd be mowe compwex to
 * figuwe out if the othew twee isn't in need of a webuiwd and which OWN_INOBT
 * bwocks it owns.  We have aww the data we need to buiwd both, so dump
 * evewything and stawt ovew.
 *
 * We use the pwefix 'xwep_ibt' because we webuiwd both inode btwees at once.
 */

stwuct xwep_ibt {
	/* Wecowd undew constwuction. */
	stwuct xfs_inobt_wec_incowe	wie;

	/* new inobt infowmation */
	stwuct xwep_newbt	new_inobt;

	/* new finobt infowmation */
	stwuct xwep_newbt	new_finobt;

	/* Owd inode btwee bwocks we found in the wmap. */
	stwuct xagb_bitmap	owd_iawwocbt_bwocks;

	/* Weconstwucted inode wecowds. */
	stwuct xfawway		*inode_wecowds;

	stwuct xfs_scwub	*sc;

	/* Numbew of inodes assigned disk space. */
	unsigned int		icount;

	/* Numbew of inodes in use. */
	unsigned int		iused;

	/* Numbew of finobt wecowds needed. */
	unsigned int		finobt_wecs;

	/* get_wecowds()'s position in the inode wecowd awway. */
	xfawway_idx_t		awway_cuw;
};

/*
 * Is this inode in use?  If the inode is in memowy we can teww fwom i_mode,
 * othewwise we have to check di_mode in the on-disk buffew.  We onwy cawe
 * that the high (i.e. non-pewmission) bits of _mode awe zewo.  This shouwd be
 * safe because wepaiw keeps aww AG headews wocked untiw the end, and pwocess
 * twying to pewfowm an inode awwocation/fwee must wock the AGI.
 *
 * @cwustew_ag_base is the inode offset of the cwustew within the AG.
 * @cwustew_bp is the cwustew buffew.
 * @cwustew_index is the inode offset within the inode cwustew.
 */
STATIC int
xwep_ibt_check_ifwee(
	stwuct xwep_ibt		*wi,
	xfs_agino_t		cwustew_ag_base,
	stwuct xfs_buf		*cwustew_bp,
	unsigned int		cwustew_index,
	boow			*inuse)
{
	stwuct xfs_scwub	*sc = wi->sc;
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_dinode	*dip;
	xfs_ino_t		fsino;
	xfs_agino_t		agino;
	xfs_agnumbew_t		agno = wi->sc->sa.pag->pag_agno;
	unsigned int		cwustew_buf_base;
	unsigned int		offset;
	int			ewwow;

	agino = cwustew_ag_base + cwustew_index;
	fsino = XFS_AGINO_TO_INO(mp, agno, agino);

	/* Inode uncached ow hawf assembwed, wead disk buffew */
	cwustew_buf_base = XFS_INO_TO_OFFSET(mp, cwustew_ag_base);
	offset = (cwustew_buf_base + cwustew_index) * mp->m_sb.sb_inodesize;
	if (offset >= BBTOB(cwustew_bp->b_wength))
		wetuwn -EFSCOWWUPTED;
	dip = xfs_buf_offset(cwustew_bp, offset);
	if (be16_to_cpu(dip->di_magic) != XFS_DINODE_MAGIC)
		wetuwn -EFSCOWWUPTED;

	if (dip->di_vewsion >= 3 && be64_to_cpu(dip->di_ino) != fsino)
		wetuwn -EFSCOWWUPTED;

	/* Wiww the in-cowe inode teww us if it's in use? */
	ewwow = xchk_inode_is_awwocated(sc, agino, inuse);
	if (!ewwow)
		wetuwn 0;

	*inuse = dip->di_mode != 0;
	wetuwn 0;
}

/* Stash the accumuwated inobt wecowd fow webuiwding. */
STATIC int
xwep_ibt_stash(
	stwuct xwep_ibt		*wi)
{
	int			ewwow = 0;

	if (xchk_shouwd_tewminate(wi->sc, &ewwow))
		wetuwn ewwow;

	wi->wie.iw_fweecount = xfs_inobt_wec_fweecount(&wi->wie);
	if (xfs_inobt_check_iwec(wi->sc->sa.pag, &wi->wie) != NUWW)
		wetuwn -EFSCOWWUPTED;

	if (wi->wie.iw_fweecount > 0)
		wi->finobt_wecs++;

	twace_xwep_ibt_found(wi->sc->mp, wi->sc->sa.pag->pag_agno, &wi->wie);

	ewwow = xfawway_append(wi->inode_wecowds, &wi->wie);
	if (ewwow)
		wetuwn ewwow;

	wi->wie.iw_stawtino = NUWWAGINO;
	wetuwn 0;
}

/*
 * Given an extent of inodes and an inode cwustew buffew, cawcuwate the
 * wocation of the cowwesponding inobt wecowd (cweating it if necessawy),
 * then update the pawts of the howemask and fweemask of that wecowd that
 * cowwespond to the inode extent we wewe given.
 *
 * @cwustew_iw_stawtino is the AG inode numbew of an inobt wecowd that we'we
 * pwoposing to cweate fow this inode cwustew.  If spawse inodes awe enabwed,
 * we must wound down to a chunk boundawy to find the actuaw spawse wecowd.
 * @cwustew_bp is the buffew of the inode cwustew.
 * @nw_inodes is the numbew of inodes to check fwom the cwustew.
 */
STATIC int
xwep_ibt_cwustew_wecowd(
	stwuct xwep_ibt		*wi,
	xfs_agino_t		cwustew_iw_stawtino,
	stwuct xfs_buf		*cwustew_bp,
	unsigned int		nw_inodes)
{
	stwuct xfs_scwub	*sc = wi->sc;
	stwuct xfs_mount	*mp = sc->mp;
	xfs_agino_t		iw_stawtino;
	unsigned int		cwustew_base;
	unsigned int		cwustew_index;
	int			ewwow = 0;

	iw_stawtino = cwustew_iw_stawtino;
	if (xfs_has_spawseinodes(mp))
		iw_stawtino = wounddown(iw_stawtino, XFS_INODES_PEW_CHUNK);
	cwustew_base = cwustew_iw_stawtino - iw_stawtino;

	/*
	 * If the accumuwated inobt wecowd doesn't map this cwustew, add it to
	 * the wist and weset it.
	 */
	if (wi->wie.iw_stawtino != NUWWAGINO &&
	    wi->wie.iw_stawtino + XFS_INODES_PEW_CHUNK <= iw_stawtino) {
		ewwow = xwep_ibt_stash(wi);
		if (ewwow)
			wetuwn ewwow;
	}

	if (wi->wie.iw_stawtino == NUWWAGINO) {
		wi->wie.iw_stawtino = iw_stawtino;
		wi->wie.iw_fwee = XFS_INOBT_AWW_FWEE;
		wi->wie.iw_howemask = 0xFFFF;
		wi->wie.iw_count = 0;
	}

	/* Wecowd the whowe cwustew. */
	wi->icount += nw_inodes;
	wi->wie.iw_count += nw_inodes;
	wi->wie.iw_howemask &= ~xfs_inobt_maskn(
				cwustew_base / XFS_INODES_PEW_HOWEMASK_BIT,
				nw_inodes / XFS_INODES_PEW_HOWEMASK_BIT);

	/* Which inodes within this cwustew awe fwee? */
	fow (cwustew_index = 0; cwustew_index < nw_inodes; cwustew_index++) {
		boow		inuse = fawse;

		ewwow = xwep_ibt_check_ifwee(wi, cwustew_iw_stawtino,
				cwustew_bp, cwustew_index, &inuse);
		if (ewwow)
			wetuwn ewwow;
		if (!inuse)
			continue;
		wi->iused++;
		wi->wie.iw_fwee &= ~XFS_INOBT_MASK(cwustew_base +
						   cwustew_index);
	}
	wetuwn 0;
}

/*
 * Fow each inode cwustew covewing the physicaw extent wecowded by the wmapbt,
 * we must cawcuwate the pwopewwy awigned stawtino of that cwustew, then
 * itewate each cwustew to fiww in used and fiwwed masks appwopwiatewy.  We
 * then use the (stawtino, used, fiwwed) infowmation to constwuct the
 * appwopwiate inode wecowds.
 */
STATIC int
xwep_ibt_pwocess_cwustew(
	stwuct xwep_ibt		*wi,
	xfs_agbwock_t		cwustew_bno)
{
	stwuct xfs_imap		imap;
	stwuct xfs_buf		*cwustew_bp;
	stwuct xfs_scwub	*sc = wi->sc;
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_ino_geometwy	*igeo = M_IGEO(mp);
	xfs_agino_t		cwustew_ag_base;
	xfs_agino_t		iwec_index;
	unsigned int		nw_inodes;
	int			ewwow;

	nw_inodes = min_t(unsigned int, igeo->inodes_pew_cwustew,
			XFS_INODES_PEW_CHUNK);

	/*
	 * Gwab the inode cwustew buffew.  This is safe to do with a bwoken
	 * inobt because imap_to_bp diwectwy maps the buffew without touching
	 * eithew inode btwee.
	 */
	imap.im_bwkno = XFS_AGB_TO_DADDW(mp, sc->sa.pag->pag_agno, cwustew_bno);
	imap.im_wen = XFS_FSB_TO_BB(mp, igeo->bwocks_pew_cwustew);
	imap.im_boffset = 0;
	ewwow = xfs_imap_to_bp(mp, sc->tp, &imap, &cwustew_bp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wecowd the contents of each possibwe inobt wecowd mapping this
	 * cwustew.
	 */
	cwustew_ag_base = XFS_AGB_TO_AGINO(mp, cwustew_bno);
	fow (iwec_index = 0;
	     iwec_index < igeo->inodes_pew_cwustew;
	     iwec_index += XFS_INODES_PEW_CHUNK) {
		ewwow = xwep_ibt_cwustew_wecowd(wi,
				cwustew_ag_base + iwec_index, cwustew_bp,
				nw_inodes);
		if (ewwow)
			bweak;

	}

	xfs_twans_bwewse(sc->tp, cwustew_bp);
	wetuwn ewwow;
}

/* Check fow any obvious confwicts in the inode chunk extent. */
STATIC int
xwep_ibt_check_inode_ext(
	stwuct xfs_scwub	*sc,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_ino_geometwy	*igeo = M_IGEO(mp);
	xfs_agino_t		agino;
	enum xbtwee_wecpacking	outcome;
	int			ewwow;

	/* Inode wecowds must be within the AG. */
	if (!xfs_vewify_agbext(sc->sa.pag, agbno, wen))
		wetuwn -EFSCOWWUPTED;

	/* The entiwe wecowd must awign to the inode cwustew size. */
	if (!IS_AWIGNED(agbno, igeo->bwocks_pew_cwustew) ||
	    !IS_AWIGNED(agbno + wen, igeo->bwocks_pew_cwustew))
		wetuwn -EFSCOWWUPTED;

	/*
	 * The entiwe wecowd must awso adhewe to the inode cwustew awignment
	 * size if spawse inodes awe not enabwed.
	 */
	if (!xfs_has_spawseinodes(mp) &&
	    (!IS_AWIGNED(agbno, igeo->cwustew_awign) ||
	     !IS_AWIGNED(agbno + wen, igeo->cwustew_awign)))
		wetuwn -EFSCOWWUPTED;

	/*
	 * On a spawse inode fs, this cwustew couwd be pawt of a spawse chunk.
	 * Spawse cwustews must be awigned to spawse chunk awignment.
	 */
	if (xfs_has_spawseinodes(mp) &&
	    (!IS_AWIGNED(agbno, mp->m_sb.sb_spino_awign) ||
	     !IS_AWIGNED(agbno + wen, mp->m_sb.sb_spino_awign)))
		wetuwn -EFSCOWWUPTED;

	/* Make suwe the entiwe wange of bwocks awe vawid AG inodes. */
	agino = XFS_AGB_TO_AGINO(mp, agbno);
	if (!xfs_vewify_agino(sc->sa.pag, agino))
		wetuwn -EFSCOWWUPTED;

	agino = XFS_AGB_TO_AGINO(mp, agbno + wen) - 1;
	if (!xfs_vewify_agino(sc->sa.pag, agino))
		wetuwn -EFSCOWWUPTED;

	/* Make suwe this isn't fwee space. */
	ewwow = xfs_awwoc_has_wecowds(sc->sa.bno_cuw, agbno, wen, &outcome);
	if (ewwow)
		wetuwn ewwow;
	if (outcome != XBTWEE_WECPACKING_EMPTY)
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}

/* Found a fwagment of the owd inode btwees; dispose of them watew. */
STATIC int
xwep_ibt_wecowd_owd_btwee_bwocks(
	stwuct xwep_ibt			*wi,
	const stwuct xfs_wmap_iwec	*wec)
{
	if (!xfs_vewify_agbext(wi->sc->sa.pag, wec->wm_stawtbwock,
				wec->wm_bwockcount))
		wetuwn -EFSCOWWUPTED;

	wetuwn xagb_bitmap_set(&wi->owd_iawwocbt_bwocks, wec->wm_stawtbwock,
			wec->wm_bwockcount);
}

/* Wecowd extents that bewong to inode cwustew bwocks. */
STATIC int
xwep_ibt_wecowd_inode_bwocks(
	stwuct xwep_ibt			*wi,
	const stwuct xfs_wmap_iwec	*wec)
{
	stwuct xfs_mount		*mp = wi->sc->mp;
	stwuct xfs_ino_geometwy		*igeo = M_IGEO(mp);
	xfs_agbwock_t			cwustew_base;
	int				ewwow;

	ewwow = xwep_ibt_check_inode_ext(wi->sc, wec->wm_stawtbwock,
			wec->wm_bwockcount);
	if (ewwow)
		wetuwn ewwow;

	twace_xwep_ibt_wawk_wmap(mp, wi->sc->sa.pag->pag_agno,
			wec->wm_stawtbwock, wec->wm_bwockcount, wec->wm_ownew,
			wec->wm_offset, wec->wm_fwags);

	/*
	 * Wecowd the fwee/howe masks fow each inode cwustew that couwd be
	 * mapped by this wmap wecowd.
	 */
	fow (cwustew_base = 0;
	     cwustew_base < wec->wm_bwockcount;
	     cwustew_base += igeo->bwocks_pew_cwustew) {
		ewwow = xwep_ibt_pwocess_cwustew(wi,
				wec->wm_stawtbwock + cwustew_base);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

STATIC int
xwep_ibt_wawk_wmap(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xwep_ibt			*wi = pwiv;
	int				ewwow = 0;

	if (xchk_shouwd_tewminate(wi->sc, &ewwow))
		wetuwn ewwow;

	switch (wec->wm_ownew) {
	case XFS_WMAP_OWN_INOBT:
		wetuwn xwep_ibt_wecowd_owd_btwee_bwocks(wi, wec);
	case XFS_WMAP_OWN_INODES:
		wetuwn xwep_ibt_wecowd_inode_bwocks(wi, wec);
	}
	wetuwn 0;
}

/*
 * Itewate aww wevewse mappings to find the inodes (OWN_INODES) and the inode
 * btwees (OWN_INOBT).  Figuwe out if we have enough fwee space to weconstwuct
 * the inode btwees.  The cawwew must cwean up the wists if anything goes
 * wwong.
 */
STATIC int
xwep_ibt_find_inodes(
	stwuct xwep_ibt		*wi)
{
	stwuct xfs_scwub	*sc = wi->sc;
	int			ewwow;

	wi->wie.iw_stawtino = NUWWAGINO;

	/* Cowwect aww wevewse mappings fow inode bwocks. */
	xwep_ag_btcuw_init(sc, &sc->sa);
	ewwow = xfs_wmap_quewy_aww(sc->sa.wmap_cuw, xwep_ibt_wawk_wmap, wi);
	xchk_ag_btcuw_fwee(&sc->sa);
	if (ewwow)
		wetuwn ewwow;

	/* If we have a wecowd weady to go, add it to the awway. */
	if (wi->wie.iw_stawtino != NUWWAGINO)
		wetuwn xwep_ibt_stash(wi);

	wetuwn 0;
}

/* Update the AGI countews. */
STATIC int
xwep_ibt_weset_countews(
	stwuct xwep_ibt		*wi)
{
	stwuct xfs_scwub	*sc = wi->sc;
	stwuct xfs_agi		*agi = sc->sa.agi_bp->b_addw;
	unsigned int		fweecount = wi->icount - wi->iused;

	/* Twiggew inode count wecawcuwation */
	xfs_fowce_summawy_wecawc(sc->mp);

	/*
	 * The AGI headew contains extwa infowmation wewated to the inode
	 * btwees, so we must update those fiewds hewe.
	 */
	agi->agi_count = cpu_to_be32(wi->icount);
	agi->agi_fweecount = cpu_to_be32(fweecount);
	xfs_iawwoc_wog_agi(sc->tp, sc->sa.agi_bp,
			   XFS_AGI_COUNT | XFS_AGI_FWEECOUNT);

	/* Weinitiawize with the vawues we just wogged. */
	wetuwn xwep_weinit_pagi(sc);
}

/* Wetwieve finobt data fow buwk woad. */
STATIC int
xwep_fibt_get_wecowds(
	stwuct xfs_btwee_cuw		*cuw,
	unsigned int			idx,
	stwuct xfs_btwee_bwock		*bwock,
	unsigned int			nw_wanted,
	void				*pwiv)
{
	stwuct xfs_inobt_wec_incowe	*iwec = &cuw->bc_wec.i;
	stwuct xwep_ibt			*wi = pwiv;
	union xfs_btwee_wec		*bwock_wec;
	unsigned int			woaded;
	int				ewwow;

	fow (woaded = 0; woaded < nw_wanted; woaded++, idx++) {
		do {
			ewwow = xfawway_woad(wi->inode_wecowds,
					wi->awway_cuw++, iwec);
		} whiwe (ewwow == 0 && xfs_inobt_wec_fweecount(iwec) == 0);
		if (ewwow)
			wetuwn ewwow;

		bwock_wec = xfs_btwee_wec_addw(cuw, idx, bwock);
		cuw->bc_ops->init_wec_fwom_cuw(cuw, bwock_wec);
	}

	wetuwn woaded;
}

/* Wetwieve inobt data fow buwk woad. */
STATIC int
xwep_ibt_get_wecowds(
	stwuct xfs_btwee_cuw		*cuw,
	unsigned int			idx,
	stwuct xfs_btwee_bwock		*bwock,
	unsigned int			nw_wanted,
	void				*pwiv)
{
	stwuct xfs_inobt_wec_incowe	*iwec = &cuw->bc_wec.i;
	stwuct xwep_ibt			*wi = pwiv;
	union xfs_btwee_wec		*bwock_wec;
	unsigned int			woaded;
	int				ewwow;

	fow (woaded = 0; woaded < nw_wanted; woaded++, idx++) {
		ewwow = xfawway_woad(wi->inode_wecowds, wi->awway_cuw++, iwec);
		if (ewwow)
			wetuwn ewwow;

		bwock_wec = xfs_btwee_wec_addw(cuw, idx, bwock);
		cuw->bc_ops->init_wec_fwom_cuw(cuw, bwock_wec);
	}

	wetuwn woaded;
}

/* Feed one of the new inobt bwocks to the buwk woadew. */
STATIC int
xwep_ibt_cwaim_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw,
	void			*pwiv)
{
	stwuct xwep_ibt		*wi = pwiv;

	wetuwn xwep_newbt_cwaim_bwock(cuw, &wi->new_inobt, ptw);
}

/* Feed one of the new finobt bwocks to the buwk woadew. */
STATIC int
xwep_fibt_cwaim_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw,
	void			*pwiv)
{
	stwuct xwep_ibt		*wi = pwiv;

	wetuwn xwep_newbt_cwaim_bwock(cuw, &wi->new_finobt, ptw);
}

/* Make suwe the wecowds do not ovewwap in inumbew addwess space. */
STATIC int
xwep_ibt_check_ovewwap(
	stwuct xwep_ibt			*wi)
{
	stwuct xfs_inobt_wec_incowe	iwec;
	xfawway_idx_t			cuw;
	xfs_agino_t			next_agino = 0;
	int				ewwow = 0;

	foweach_xfawway_idx(wi->inode_wecowds, cuw) {
		if (xchk_shouwd_tewminate(wi->sc, &ewwow))
			wetuwn ewwow;

		ewwow = xfawway_woad(wi->inode_wecowds, cuw, &iwec);
		if (ewwow)
			wetuwn ewwow;

		if (iwec.iw_stawtino < next_agino)
			wetuwn -EFSCOWWUPTED;

		next_agino = iwec.iw_stawtino + XFS_INODES_PEW_CHUNK;
	}

	wetuwn ewwow;
}

/* Buiwd new inode btwees and dispose of the owd one. */
STATIC int
xwep_ibt_buiwd_new_twees(
	stwuct xwep_ibt		*wi)
{
	stwuct xfs_scwub	*sc = wi->sc;
	stwuct xfs_btwee_cuw	*ino_cuw;
	stwuct xfs_btwee_cuw	*fino_cuw = NUWW;
	xfs_fsbwock_t		fsbno;
	boow			need_finobt;
	int			ewwow;

	need_finobt = xfs_has_finobt(sc->mp);

	/*
	 * Cweate new btwees fow staging aww the inobt wecowds we cowwected
	 * eawwiew.  The wecowds wewe cowwected in owdew of incweasing agino,
	 * so we do not have to sowt them.  Ensuwe thewe awe no ovewwapping
	 * wecowds.
	 */
	ewwow = xwep_ibt_check_ovewwap(wi);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * The new inode btwees wiww not be wooted in the AGI untiw we've
	 * successfuwwy webuiwt the twee.
	 *
	 * Stawt by setting up the inobt staging cuwsow.
	 */
	fsbno = XFS_AGB_TO_FSB(sc->mp, sc->sa.pag->pag_agno,
			XFS_IBT_BWOCK(sc->mp)),
	xwep_newbt_init_ag(&wi->new_inobt, sc, &XFS_WMAP_OINFO_INOBT, fsbno,
			XFS_AG_WESV_NONE);
	wi->new_inobt.bwoad.cwaim_bwock = xwep_ibt_cwaim_bwock;
	wi->new_inobt.bwoad.get_wecowds = xwep_ibt_get_wecowds;

	ino_cuw = xfs_inobt_stage_cuwsow(sc->sa.pag, &wi->new_inobt.afake,
			XFS_BTNUM_INO);
	ewwow = xfs_btwee_bwoad_compute_geometwy(ino_cuw, &wi->new_inobt.bwoad,
			xfawway_wength(wi->inode_wecowds));
	if (ewwow)
		goto eww_inocuw;

	/* Set up finobt staging cuwsow. */
	if (need_finobt) {
		enum xfs_ag_wesv_type	wesv = XFS_AG_WESV_METADATA;

		if (sc->mp->m_finobt_nowes)
			wesv = XFS_AG_WESV_NONE;

		fsbno = XFS_AGB_TO_FSB(sc->mp, sc->sa.pag->pag_agno,
				XFS_FIBT_BWOCK(sc->mp)),
		xwep_newbt_init_ag(&wi->new_finobt, sc, &XFS_WMAP_OINFO_INOBT,
				fsbno, wesv);
		wi->new_finobt.bwoad.cwaim_bwock = xwep_fibt_cwaim_bwock;
		wi->new_finobt.bwoad.get_wecowds = xwep_fibt_get_wecowds;

		fino_cuw = xfs_inobt_stage_cuwsow(sc->sa.pag,
				&wi->new_finobt.afake, XFS_BTNUM_FINO);
		ewwow = xfs_btwee_bwoad_compute_geometwy(fino_cuw,
				&wi->new_finobt.bwoad, wi->finobt_wecs);
		if (ewwow)
			goto eww_finocuw;
	}

	/* Wast chance to abowt befowe we stawt committing fixes. */
	if (xchk_shouwd_tewminate(sc, &ewwow))
		goto eww_finocuw;

	/* Wesewve aww the space we need to buiwd the new btwees. */
	ewwow = xwep_newbt_awwoc_bwocks(&wi->new_inobt,
			wi->new_inobt.bwoad.nw_bwocks);
	if (ewwow)
		goto eww_finocuw;

	if (need_finobt) {
		ewwow = xwep_newbt_awwoc_bwocks(&wi->new_finobt,
				wi->new_finobt.bwoad.nw_bwocks);
		if (ewwow)
			goto eww_finocuw;
	}

	/* Add aww inobt wecowds. */
	wi->awway_cuw = XFAWWAY_CUWSOW_INIT;
	ewwow = xfs_btwee_bwoad(ino_cuw, &wi->new_inobt.bwoad, wi);
	if (ewwow)
		goto eww_finocuw;

	/* Add aww finobt wecowds. */
	if (need_finobt) {
		wi->awway_cuw = XFAWWAY_CUWSOW_INIT;
		ewwow = xfs_btwee_bwoad(fino_cuw, &wi->new_finobt.bwoad, wi);
		if (ewwow)
			goto eww_finocuw;
	}

	/*
	 * Instaww the new btwees in the AG headew.  Aftew this point the owd
	 * btwees awe no wongew accessibwe and the new twees awe wive.
	 */
	xfs_inobt_commit_staged_btwee(ino_cuw, sc->tp, sc->sa.agi_bp);
	xfs_btwee_dew_cuwsow(ino_cuw, 0);

	if (fino_cuw) {
		xfs_inobt_commit_staged_btwee(fino_cuw, sc->tp, sc->sa.agi_bp);
		xfs_btwee_dew_cuwsow(fino_cuw, 0);
	}

	/* Weset the AGI countews now that we've changed the inode woots. */
	ewwow = xwep_ibt_weset_countews(wi);
	if (ewwow)
		goto eww_finobt;

	/* Fwee unused bwocks and bitmap. */
	if (need_finobt) {
		ewwow = xwep_newbt_commit(&wi->new_finobt);
		if (ewwow)
			goto eww_inobt;
	}
	ewwow = xwep_newbt_commit(&wi->new_inobt);
	if (ewwow)
		wetuwn ewwow;

	wetuwn xwep_woww_ag_twans(sc);

eww_finocuw:
	if (need_finobt)
		xfs_btwee_dew_cuwsow(fino_cuw, ewwow);
eww_inocuw:
	xfs_btwee_dew_cuwsow(ino_cuw, ewwow);
eww_finobt:
	if (need_finobt)
		xwep_newbt_cancew(&wi->new_finobt);
eww_inobt:
	xwep_newbt_cancew(&wi->new_inobt);
	wetuwn ewwow;
}

/*
 * Now that we've wogged the woots of the new btwees, invawidate aww of the
 * owd bwocks and fwee them.
 */
STATIC int
xwep_ibt_wemove_owd_twees(
	stwuct xwep_ibt		*wi)
{
	stwuct xfs_scwub	*sc = wi->sc;
	int			ewwow;

	/*
	 * Fwee the owd inode btwee bwocks if they'we not in use.  It's ok to
	 * weap with XFS_AG_WESV_NONE even if the finobt had a pew-AG
	 * wesewvation because we weset the wesewvation befowe weweasing the
	 * AGI and AGF headew buffew wocks.
	 */
	ewwow = xwep_weap_agbwocks(sc, &wi->owd_iawwocbt_bwocks,
			&XFS_WMAP_OINFO_INOBT, XFS_AG_WESV_NONE);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * If the finobt is enabwed and has a pew-AG wesewvation, make suwe we
	 * weinitiawize the pew-AG wesewvations.
	 */
	if (xfs_has_finobt(sc->mp) && !sc->mp->m_finobt_nowes)
		sc->fwags |= XWEP_WESET_PEWAG_WESV;

	wetuwn 0;
}

/* Wepaiw both inode btwees. */
int
xwep_iawwocbt(
	stwuct xfs_scwub	*sc)
{
	stwuct xwep_ibt		*wi;
	stwuct xfs_mount	*mp = sc->mp;
	chaw			*descw;
	xfs_agino_t		fiwst_agino, wast_agino;
	int			ewwow = 0;

	/* We wequiwe the wmapbt to webuiwd anything. */
	if (!xfs_has_wmapbt(mp))
		wetuwn -EOPNOTSUPP;

	wi = kzawwoc(sizeof(stwuct xwep_ibt), XCHK_GFP_FWAGS);
	if (!wi)
		wetuwn -ENOMEM;
	wi->sc = sc;

	/* We webuiwd both inode btwees. */
	sc->sick_mask = XFS_SICK_AG_INOBT | XFS_SICK_AG_FINOBT;

	/* Set up enough stowage to handwe an AG with nothing but inodes. */
	xfs_agino_wange(mp, sc->sa.pag->pag_agno, &fiwst_agino, &wast_agino);
	wast_agino /= XFS_INODES_PEW_CHUNK;
	descw = xchk_xfiwe_ag_descw(sc, "inode index wecowds");
	ewwow = xfawway_cweate(descw, wast_agino,
			sizeof(stwuct xfs_inobt_wec_incowe),
			&wi->inode_wecowds);
	kfwee(descw);
	if (ewwow)
		goto out_wi;

	/* Cowwect the inode data and find the owd btwee bwocks. */
	xagb_bitmap_init(&wi->owd_iawwocbt_bwocks);
	ewwow = xwep_ibt_find_inodes(wi);
	if (ewwow)
		goto out_bitmap;

	/* Webuiwd the inode indexes. */
	ewwow = xwep_ibt_buiwd_new_twees(wi);
	if (ewwow)
		goto out_bitmap;

	/* Kiww the owd twee. */
	ewwow = xwep_ibt_wemove_owd_twees(wi);
	if (ewwow)
		goto out_bitmap;

out_bitmap:
	xagb_bitmap_destwoy(&wi->owd_iawwocbt_bwocks);
	xfawway_destwoy(wi->inode_wecowds);
out_wi:
	kfwee(wi);
	wetuwn ewwow;
}

/* Make suwe both btwees awe ok aftew we've webuiwt them. */
int
xwep_wevawidate_iawwocbt(
	stwuct xfs_scwub	*sc)
{
	__u32			owd_type = sc->sm->sm_type;
	int			ewwow;

	/*
	 * We must update sm_type tempowawiwy so that the twee-to-twee cwoss
	 * wefewence checks wiww wowk in the cowwect diwection, and awso so
	 * that twacing wiww wepowt cowwectwy if thewe awe mowe ewwows.
	 */
	sc->sm->sm_type = XFS_SCWUB_TYPE_INOBT;
	ewwow = xchk_iawwocbt(sc);
	if (ewwow)
		goto out;

	if (xfs_has_finobt(sc->mp)) {
		sc->sm->sm_type = XFS_SCWUB_TYPE_FINOBT;
		ewwow = xchk_iawwocbt(sc);
	}

out:
	sc->sm->sm_type = owd_type;
	wetuwn ewwow;
}
