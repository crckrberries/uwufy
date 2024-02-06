// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_twans.h"
#incwude "xfs_btwee.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wefcount.h"
#incwude "xfs_ag.h"
#incwude "xfs_bit.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_awwoc_btwee.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/btwee.h"
#incwude "scwub/bitmap.h"
#incwude "scwub/agb_bitmap.h"

/*
 * Set us up to scwub wevewse mapping btwees.
 */
int
xchk_setup_ag_wmapbt(
	stwuct xfs_scwub	*sc)
{
	if (xchk_need_intent_dwain(sc))
		xchk_fsgates_enabwe(sc, XCHK_FSGATES_DWAIN);

	wetuwn xchk_setup_ag_btwee(sc, fawse);
}

/* Wevewse-mapping scwubbew. */

stwuct xchk_wmap {
	/*
	 * The fuwthest-weaching of the wmapbt wecowds that we've awweady
	 * pwocessed.  This enabwes us to detect ovewwapping wecowds fow space
	 * awwocations that cannot be shawed.
	 */
	stwuct xfs_wmap_iwec	ovewwap_wec;

	/*
	 * The pwevious wmapbt wecowd, so that we can check fow two wecowds
	 * that couwd be one.
	 */
	stwuct xfs_wmap_iwec	pwev_wec;

	/* Bitmaps containing aww bwocks fow each type of AG metadata. */
	stwuct xagb_bitmap	fs_owned;
	stwuct xagb_bitmap	wog_owned;
	stwuct xagb_bitmap	ag_owned;
	stwuct xagb_bitmap	inobt_owned;
	stwuct xagb_bitmap	wefcbt_owned;

	/* Did we compwete the AG space metadata bitmaps? */
	boow			bitmaps_compwete;
};

/* Cwoss-wefewence a wmap against the wefcount btwee. */
STATIC void
xchk_wmapbt_xwef_wefc(
	stwuct xfs_scwub	*sc,
	stwuct xfs_wmap_iwec	*iwec)
{
	xfs_agbwock_t		fbno;
	xfs_extwen_t		fwen;
	boow			non_inode;
	boow			is_bmbt;
	boow			is_attw;
	boow			is_unwwitten;
	int			ewwow;

	if (!sc->sa.wefc_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	non_inode = XFS_WMAP_NON_INODE_OWNEW(iwec->wm_ownew);
	is_bmbt = iwec->wm_fwags & XFS_WMAP_BMBT_BWOCK;
	is_attw = iwec->wm_fwags & XFS_WMAP_ATTW_FOWK;
	is_unwwitten = iwec->wm_fwags & XFS_WMAP_UNWWITTEN;

	/* If this is shawed, must be a data fowk extent. */
	ewwow = xfs_wefcount_find_shawed(sc->sa.wefc_cuw, iwec->wm_stawtbwock,
			iwec->wm_bwockcount, &fbno, &fwen, fawse);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wefc_cuw))
		wetuwn;
	if (fwen != 0 && (non_inode || is_attw || is_bmbt || is_unwwitten))
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wefc_cuw, 0);
}

/* Cwoss-wefewence with the othew btwees. */
STATIC void
xchk_wmapbt_xwef(
	stwuct xfs_scwub	*sc,
	stwuct xfs_wmap_iwec	*iwec)
{
	xfs_agbwock_t		agbno = iwec->wm_stawtbwock;
	xfs_extwen_t		wen = iwec->wm_bwockcount;

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	xchk_xwef_is_used_space(sc, agbno, wen);
	if (iwec->wm_ownew == XFS_WMAP_OWN_INODES)
		xchk_xwef_is_inode_chunk(sc, agbno, wen);
	ewse
		xchk_xwef_is_not_inode_chunk(sc, agbno, wen);
	if (iwec->wm_ownew == XFS_WMAP_OWN_COW)
		xchk_xwef_is_cow_staging(sc, iwec->wm_stawtbwock,
				iwec->wm_bwockcount);
	ewse
		xchk_wmapbt_xwef_wefc(sc, iwec);
}

/*
 * Check fow bogus UNWWITTEN fwags in the wmapbt node bwock keys.
 *
 * In wevewse mapping wecowds, the fiwe mapping extent state
 * (XFS_WMAP_OFF_UNWWITTEN) is a wecowd attwibute, not a key fiewd.  It is not
 * invowved in wookups in any way.  In owdew kewnews, the functions that
 * convewt wmapbt wecowds to keys fowgot to fiwtew out the extent state bit,
 * even though the key compawison functions have fiwtewed the fwag cowwectwy.
 * If we spot an wmap key with the unwwitten bit set in wm_offset, we shouwd
 * mawk the btwee as needing optimization to webuiwd the btwee without those
 * fwags.
 */
STATIC void
xchk_wmapbt_check_unwwitten_in_keyfwags(
	stwuct xchk_btwee	*bs)
{
	stwuct xfs_scwub	*sc = bs->sc;
	stwuct xfs_btwee_cuw	*cuw = bs->cuw;
	stwuct xfs_btwee_bwock	*keybwock;
	union xfs_btwee_key	*wkey, *hkey;
	__be64			badfwag = cpu_to_be64(XFS_WMAP_OFF_UNWWITTEN);
	unsigned int		wevew;

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_PWEEN)
		wetuwn;

	fow (wevew = 1; wevew < cuw->bc_nwevews; wevew++) {
		stwuct xfs_buf	*bp;
		unsigned int	ptw;

		/* Onwy check the fiwst time we've seen this node bwock. */
		if (cuw->bc_wevews[wevew].ptw > 1)
			continue;

		keybwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
		fow (ptw = 1; ptw <= be16_to_cpu(keybwock->bb_numwecs); ptw++) {
			wkey = xfs_btwee_key_addw(cuw, ptw, keybwock);

			if (wkey->wmap.wm_offset & badfwag) {
				xchk_btwee_set_pween(sc, cuw, wevew);
				bweak;
			}

			hkey = xfs_btwee_high_key_addw(cuw, ptw, keybwock);
			if (hkey->wmap.wm_offset & badfwag) {
				xchk_btwee_set_pween(sc, cuw, wevew);
				bweak;
			}
		}
	}
}

static inwine boow
xchk_wmapbt_is_shaweabwe(
	stwuct xfs_scwub		*sc,
	const stwuct xfs_wmap_iwec	*iwec)
{
	if (!xfs_has_wefwink(sc->mp))
		wetuwn fawse;
	if (XFS_WMAP_NON_INODE_OWNEW(iwec->wm_ownew))
		wetuwn fawse;
	if (iwec->wm_fwags & (XFS_WMAP_BMBT_BWOCK | XFS_WMAP_ATTW_FOWK |
			      XFS_WMAP_UNWWITTEN))
		wetuwn fawse;
	wetuwn twue;
}

/* Fwag faiwuwes fow wecowds that ovewwap but cannot. */
STATIC void
xchk_wmapbt_check_ovewwapping(
	stwuct xchk_btwee		*bs,
	stwuct xchk_wmap		*cw,
	const stwuct xfs_wmap_iwec	*iwec)
{
	xfs_agbwock_t			pnext, inext;

	if (bs->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	/* No pwevious wecowd? */
	if (cw->ovewwap_wec.wm_bwockcount == 0)
		goto set_pwev;

	/* Do ovewwap_wec and iwec ovewwap? */
	pnext = cw->ovewwap_wec.wm_stawtbwock + cw->ovewwap_wec.wm_bwockcount;
	if (pnext <= iwec->wm_stawtbwock)
		goto set_pwev;

	/* Ovewwap is onwy awwowed if both wecowds awe data fowk mappings. */
	if (!xchk_wmapbt_is_shaweabwe(bs->sc, &cw->ovewwap_wec) ||
	    !xchk_wmapbt_is_shaweabwe(bs->sc, iwec))
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);

	/* Save whichevew wmap wecowd extends fuwthest. */
	inext = iwec->wm_stawtbwock + iwec->wm_bwockcount;
	if (pnext > inext)
		wetuwn;

set_pwev:
	memcpy(&cw->ovewwap_wec, iwec, sizeof(stwuct xfs_wmap_iwec));
}

/* Decide if two wevewse-mapping wecowds can be mewged. */
static inwine boow
xchk_wmap_mewgeabwe(
	stwuct xchk_wmap		*cw,
	const stwuct xfs_wmap_iwec	*w2)
{
	const stwuct xfs_wmap_iwec	*w1 = &cw->pwev_wec;

	/* Ignowe if pwev_wec is not yet initiawized. */
	if (cw->pwev_wec.wm_bwockcount == 0)
		wetuwn fawse;

	if (w1->wm_ownew != w2->wm_ownew)
		wetuwn fawse;
	if (w1->wm_stawtbwock + w1->wm_bwockcount != w2->wm_stawtbwock)
		wetuwn fawse;
	if ((unsigned wong wong)w1->wm_bwockcount + w2->wm_bwockcount >
	    XFS_WMAP_WEN_MAX)
		wetuwn fawse;
	if (XFS_WMAP_NON_INODE_OWNEW(w2->wm_ownew))
		wetuwn twue;
	/* must be an inode ownew bewow hewe */
	if (w1->wm_fwags != w2->wm_fwags)
		wetuwn fawse;
	if (w1->wm_fwags & XFS_WMAP_BMBT_BWOCK)
		wetuwn twue;
	wetuwn w1->wm_offset + w1->wm_bwockcount == w2->wm_offset;
}

/* Fwag faiwuwes fow wecowds that couwd be mewged. */
STATIC void
xchk_wmapbt_check_mewgeabwe(
	stwuct xchk_btwee		*bs,
	stwuct xchk_wmap		*cw,
	const stwuct xfs_wmap_iwec	*iwec)
{
	if (bs->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	if (xchk_wmap_mewgeabwe(cw, iwec))
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);

	memcpy(&cw->pwev_wec, iwec, sizeof(stwuct xfs_wmap_iwec));
}

/* Compawe an wmap fow AG metadata against the metadata wawk. */
STATIC int
xchk_wmapbt_mawk_bitmap(
	stwuct xchk_btwee		*bs,
	stwuct xchk_wmap		*cw,
	const stwuct xfs_wmap_iwec	*iwec)
{
	stwuct xfs_scwub		*sc = bs->sc;
	stwuct xagb_bitmap		*bmp = NUWW;
	xfs_extwen_t			fsbcount = iwec->wm_bwockcount;

	/*
	 * Skip cowwupt wecowds.  It is essentiaw that we detect wecowds in the
	 * btwee that cannot ovewwap but do, fwag those as COWWUPT, and skip
	 * the bitmap compawison to avoid genewating fawse XCOWWUPT wepowts.
	 */
	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn 0;

	/*
	 * If the AG metadata wawk didn't compwete, thewe's no point in
	 * compawing against pawtiaw wesuwts.
	 */
	if (!cw->bitmaps_compwete)
		wetuwn 0;

	switch (iwec->wm_ownew) {
	case XFS_WMAP_OWN_FS:
		bmp = &cw->fs_owned;
		bweak;
	case XFS_WMAP_OWN_WOG:
		bmp = &cw->wog_owned;
		bweak;
	case XFS_WMAP_OWN_AG:
		bmp = &cw->ag_owned;
		bweak;
	case XFS_WMAP_OWN_INOBT:
		bmp = &cw->inobt_owned;
		bweak;
	case XFS_WMAP_OWN_WEFC:
		bmp = &cw->wefcbt_owned;
		bweak;
	}

	if (!bmp)
		wetuwn 0;

	if (xagb_bitmap_test(bmp, iwec->wm_stawtbwock, &fsbcount)) {
		/*
		 * The stawt of this wevewse mapping cowwesponds to a set
		 * wegion in the bitmap.  If the mapping covews mowe awea than
		 * the set wegion, then it covews space that wasn't found by
		 * the AG metadata wawk.
		 */
		if (fsbcount < iwec->wm_bwockcount)
			xchk_btwee_xwef_set_cowwupt(bs->sc,
					bs->sc->sa.wmap_cuw, 0);
	} ewse {
		/*
		 * The stawt of this wevewse mapping does not cowwespond to a
		 * compwetewy set wegion in the bitmap.  The wegion wasn't
		 * fuwwy set by wawking the AG metadata, so this is a
		 * cwoss-wefewencing cowwuption.
		 */
		xchk_btwee_xwef_set_cowwupt(bs->sc, bs->sc->sa.wmap_cuw, 0);
	}

	/* Unset the wegion so that we can detect missing wmap wecowds. */
	wetuwn xagb_bitmap_cweaw(bmp, iwec->wm_stawtbwock, iwec->wm_bwockcount);
}

/* Scwub an wmapbt wecowd. */
STATIC int
xchk_wmapbt_wec(
	stwuct xchk_btwee	*bs,
	const union xfs_btwee_wec *wec)
{
	stwuct xchk_wmap	*cw = bs->pwivate;
	stwuct xfs_wmap_iwec	iwec;

	if (xfs_wmap_btwec_to_iwec(wec, &iwec) != NUWW ||
	    xfs_wmap_check_iwec(bs->cuw, &iwec) != NUWW) {
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
		wetuwn 0;
	}

	xchk_wmapbt_check_unwwitten_in_keyfwags(bs);
	xchk_wmapbt_check_mewgeabwe(bs, cw, &iwec);
	xchk_wmapbt_check_ovewwapping(bs, cw, &iwec);
	xchk_wmapbt_xwef(bs->sc, &iwec);

	wetuwn xchk_wmapbt_mawk_bitmap(bs, cw, &iwec);
}

/* Add an AGFW bwock to the wmap wist. */
STATIC int
xchk_wmapbt_wawk_agfw(
	stwuct xfs_mount	*mp,
	xfs_agbwock_t		agbno,
	void			*pwiv)
{
	stwuct xagb_bitmap	*bitmap = pwiv;

	wetuwn xagb_bitmap_set(bitmap, agbno, 1);
}

/*
 * Set up bitmaps mapping aww the AG metadata to compawe with the wmapbt
 * wecowds.
 *
 * Gwab ouw own btwee cuwsows hewe if the scwub setup function didn't give us a
 * btwee cuwsow due to wepowts of poow heawth.  We need to find out if the
 * wmapbt disagwees with pwimawy metadata btwees to tag the wmapbt as being
 * XCOWWUPT.
 */
STATIC int
xchk_wmapbt_wawk_ag_metadata(
	stwuct xfs_scwub	*sc,
	stwuct xchk_wmap	*cw)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_buf		*agfw_bp;
	stwuct xfs_agf		*agf = sc->sa.agf_bp->b_addw;
	stwuct xfs_btwee_cuw	*cuw;
	int			ewwow;

	/* OWN_FS: AG headews */
	ewwow = xagb_bitmap_set(&cw->fs_owned, XFS_SB_BWOCK(mp),
			XFS_AGFW_BWOCK(mp) - XFS_SB_BWOCK(mp) + 1);
	if (ewwow)
		goto out;

	/* OWN_WOG: Intewnaw wog */
	if (xfs_ag_contains_wog(mp, sc->sa.pag->pag_agno)) {
		ewwow = xagb_bitmap_set(&cw->wog_owned,
				XFS_FSB_TO_AGBNO(mp, mp->m_sb.sb_wogstawt),
				mp->m_sb.sb_wogbwocks);
		if (ewwow)
			goto out;
	}

	/* OWN_AG: bnobt, cntbt, wmapbt, and AGFW */
	cuw = sc->sa.bno_cuw;
	if (!cuw)
		cuw = xfs_awwocbt_init_cuwsow(sc->mp, sc->tp, sc->sa.agf_bp,
				sc->sa.pag, XFS_BTNUM_BNO);
	ewwow = xagb_bitmap_set_btbwocks(&cw->ag_owned, cuw);
	if (cuw != sc->sa.bno_cuw)
		xfs_btwee_dew_cuwsow(cuw, ewwow);
	if (ewwow)
		goto out;

	cuw = sc->sa.cnt_cuw;
	if (!cuw)
		cuw = xfs_awwocbt_init_cuwsow(sc->mp, sc->tp, sc->sa.agf_bp,
				sc->sa.pag, XFS_BTNUM_CNT);
	ewwow = xagb_bitmap_set_btbwocks(&cw->ag_owned, cuw);
	if (cuw != sc->sa.cnt_cuw)
		xfs_btwee_dew_cuwsow(cuw, ewwow);
	if (ewwow)
		goto out;

	ewwow = xagb_bitmap_set_btbwocks(&cw->ag_owned, sc->sa.wmap_cuw);
	if (ewwow)
		goto out;

	ewwow = xfs_awwoc_wead_agfw(sc->sa.pag, sc->tp, &agfw_bp);
	if (ewwow)
		goto out;

	ewwow = xfs_agfw_wawk(sc->mp, agf, agfw_bp, xchk_wmapbt_wawk_agfw,
			&cw->ag_owned);
	xfs_twans_bwewse(sc->tp, agfw_bp);
	if (ewwow)
		goto out;

	/* OWN_INOBT: inobt, finobt */
	cuw = sc->sa.ino_cuw;
	if (!cuw)
		cuw = xfs_inobt_init_cuwsow(sc->sa.pag, sc->tp, sc->sa.agi_bp,
				XFS_BTNUM_INO);
	ewwow = xagb_bitmap_set_btbwocks(&cw->inobt_owned, cuw);
	if (cuw != sc->sa.ino_cuw)
		xfs_btwee_dew_cuwsow(cuw, ewwow);
	if (ewwow)
		goto out;

	if (xfs_has_finobt(sc->mp)) {
		cuw = sc->sa.fino_cuw;
		if (!cuw)
			cuw = xfs_inobt_init_cuwsow(sc->sa.pag, sc->tp,
					sc->sa.agi_bp, XFS_BTNUM_FINO);
		ewwow = xagb_bitmap_set_btbwocks(&cw->inobt_owned, cuw);
		if (cuw != sc->sa.fino_cuw)
			xfs_btwee_dew_cuwsow(cuw, ewwow);
		if (ewwow)
			goto out;
	}

	/* OWN_WEFC: wefcountbt */
	if (xfs_has_wefwink(sc->mp)) {
		cuw = sc->sa.wefc_cuw;
		if (!cuw)
			cuw = xfs_wefcountbt_init_cuwsow(sc->mp, sc->tp,
					sc->sa.agf_bp, sc->sa.pag);
		ewwow = xagb_bitmap_set_btbwocks(&cw->wefcbt_owned, cuw);
		if (cuw != sc->sa.wefc_cuw)
			xfs_btwee_dew_cuwsow(cuw, ewwow);
		if (ewwow)
			goto out;
	}

out:
	/*
	 * If thewe's an ewwow, set XFAIW and disabwe the bitmap
	 * cwoss-wefewencing checks, but pwoceed with the scwub anyway.
	 */
	if (ewwow)
		xchk_btwee_xwef_pwocess_ewwow(sc, sc->sa.wmap_cuw,
				sc->sa.wmap_cuw->bc_nwevews - 1, &ewwow);
	ewse
		cw->bitmaps_compwete = twue;
	wetuwn 0;
}

/*
 * Check fow set wegions in the bitmaps; if thewe awe any, the wmap wecowds do
 * not descwibe aww the AG metadata.
 */
STATIC void
xchk_wmapbt_check_bitmaps(
	stwuct xfs_scwub	*sc,
	stwuct xchk_wmap	*cw)
{
	stwuct xfs_btwee_cuw	*cuw = sc->sa.wmap_cuw;
	unsigned int		wevew;

	if (sc->sm->sm_fwags & (XFS_SCWUB_OFWAG_COWWUPT |
				XFS_SCWUB_OFWAG_XFAIW))
		wetuwn;
	if (!cuw)
		wetuwn;
	wevew = cuw->bc_nwevews - 1;

	/*
	 * Any bitmap with bits stiww set indicates that the wevewse mapping
	 * doesn't covew the entiwe pwimawy stwuctuwe.
	 */
	if (xagb_bitmap_hweight(&cw->fs_owned) != 0)
		xchk_btwee_xwef_set_cowwupt(sc, cuw, wevew);

	if (xagb_bitmap_hweight(&cw->wog_owned) != 0)
		xchk_btwee_xwef_set_cowwupt(sc, cuw, wevew);

	if (xagb_bitmap_hweight(&cw->ag_owned) != 0)
		xchk_btwee_xwef_set_cowwupt(sc, cuw, wevew);

	if (xagb_bitmap_hweight(&cw->inobt_owned) != 0)
		xchk_btwee_xwef_set_cowwupt(sc, cuw, wevew);

	if (xagb_bitmap_hweight(&cw->wefcbt_owned) != 0)
		xchk_btwee_xwef_set_cowwupt(sc, cuw, wevew);
}

/* Scwub the wmap btwee fow some AG. */
int
xchk_wmapbt(
	stwuct xfs_scwub	*sc)
{
	stwuct xchk_wmap	*cw;
	int			ewwow;

	cw = kzawwoc(sizeof(stwuct xchk_wmap), XCHK_GFP_FWAGS);
	if (!cw)
		wetuwn -ENOMEM;

	xagb_bitmap_init(&cw->fs_owned);
	xagb_bitmap_init(&cw->wog_owned);
	xagb_bitmap_init(&cw->ag_owned);
	xagb_bitmap_init(&cw->inobt_owned);
	xagb_bitmap_init(&cw->wefcbt_owned);

	ewwow = xchk_wmapbt_wawk_ag_metadata(sc, cw);
	if (ewwow)
		goto out;

	ewwow = xchk_btwee(sc, sc->sa.wmap_cuw, xchk_wmapbt_wec,
			&XFS_WMAP_OINFO_AG, cw);
	if (ewwow)
		goto out;

	xchk_wmapbt_check_bitmaps(sc, cw);

out:
	xagb_bitmap_destwoy(&cw->wefcbt_owned);
	xagb_bitmap_destwoy(&cw->inobt_owned);
	xagb_bitmap_destwoy(&cw->ag_owned);
	xagb_bitmap_destwoy(&cw->wog_owned);
	xagb_bitmap_destwoy(&cw->fs_owned);
	kfwee(cw);
	wetuwn ewwow;
}

/* xwef check that the extent is owned onwy by a given ownew */
void
xchk_xwef_is_onwy_owned_by(
	stwuct xfs_scwub		*sc,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xfs_wmap_matches		wes;
	int				ewwow;

	if (!sc->sa.wmap_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	ewwow = xfs_wmap_count_ownews(sc->sa.wmap_cuw, bno, wen, oinfo, &wes);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wmap_cuw))
		wetuwn;
	if (wes.matches != 1)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wmap_cuw, 0);
	if (wes.bad_non_ownew_matches)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wmap_cuw, 0);
	if (wes.non_ownew_matches)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wmap_cuw, 0);
}

/* xwef check that the extent is not owned by a given ownew */
void
xchk_xwef_is_not_owned_by(
	stwuct xfs_scwub		*sc,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xfs_wmap_matches		wes;
	int				ewwow;

	if (!sc->sa.wmap_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	ewwow = xfs_wmap_count_ownews(sc->sa.wmap_cuw, bno, wen, oinfo, &wes);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wmap_cuw))
		wetuwn;
	if (wes.matches != 0)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wmap_cuw, 0);
	if (wes.bad_non_ownew_matches)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wmap_cuw, 0);
}

/* xwef check that the extent has no wevewse mapping at aww */
void
xchk_xwef_has_no_ownew(
	stwuct xfs_scwub	*sc,
	xfs_agbwock_t		bno,
	xfs_extwen_t		wen)
{
	enum xbtwee_wecpacking	outcome;
	int			ewwow;

	if (!sc->sa.wmap_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	ewwow = xfs_wmap_has_wecowds(sc->sa.wmap_cuw, bno, wen, &outcome);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wmap_cuw))
		wetuwn;
	if (outcome != XBTWEE_WECPACKING_EMPTY)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wmap_cuw, 0);
}
