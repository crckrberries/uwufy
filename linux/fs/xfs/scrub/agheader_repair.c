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
#incwude "xfs_btwee.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_sb.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_awwoc_btwee.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "xfs_ag.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"
#incwude "scwub/bitmap.h"
#incwude "scwub/agb_bitmap.h"
#incwude "scwub/weap.h"

/* Supewbwock */

/* Wepaiw the supewbwock. */
int
xwep_supewbwock(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_buf		*bp;
	xfs_agnumbew_t		agno;
	int			ewwow;

	/* Don't twy to wepaiw AG 0's sb; wet xfs_wepaiw deaw with it. */
	agno = sc->sm->sm_agno;
	if (agno == 0)
		wetuwn -EOPNOTSUPP;

	ewwow = xfs_sb_get_secondawy(mp, sc->tp, agno, &bp);
	if (ewwow)
		wetuwn ewwow;

	/* Wast chance to abowt befowe we stawt committing fixes. */
	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	/* Copy AG 0's supewbwock to this one. */
	xfs_buf_zewo(bp, 0, BBTOB(bp->b_wength));
	xfs_sb_to_disk(bp->b_addw, &mp->m_sb);

	/*
	 * Don't wwite out a secondawy supew with NEEDSWEPAIW ow wog incompat
	 * featuwes set, since both awe ignowed when set on a secondawy.
	 */
	if (xfs_has_cwc(mp)) {
		stwuct xfs_dsb		*sb = bp->b_addw;

		sb->sb_featuwes_incompat &=
				~cpu_to_be32(XFS_SB_FEAT_INCOMPAT_NEEDSWEPAIW);
		sb->sb_featuwes_wog_incompat = 0;
	}

	/* Wwite this to disk. */
	xfs_twans_buf_set_type(sc->tp, bp, XFS_BWFT_SB_BUF);
	xfs_twans_wog_buf(sc->tp, bp, 0, BBTOB(bp->b_wength) - 1);
	wetuwn 0;
}

/* AGF */

stwuct xwep_agf_awwocbt {
	stwuct xfs_scwub	*sc;
	xfs_agbwock_t		fweebwks;
	xfs_agbwock_t		wongest;
};

/* Wecowd fwee space shape infowmation. */
STATIC int
xwep_agf_wawk_awwocbt(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_awwoc_wec_incowe *wec,
	void				*pwiv)
{
	stwuct xwep_agf_awwocbt		*waa = pwiv;
	int				ewwow = 0;

	if (xchk_shouwd_tewminate(waa->sc, &ewwow))
		wetuwn ewwow;

	waa->fweebwks += wec->aw_bwockcount;
	if (wec->aw_bwockcount > waa->wongest)
		waa->wongest = wec->aw_bwockcount;
	wetuwn ewwow;
}

/* Does this AGFW bwock wook sane? */
STATIC int
xwep_agf_check_agfw_bwock(
	stwuct xfs_mount	*mp,
	xfs_agbwock_t		agbno,
	void			*pwiv)
{
	stwuct xfs_scwub	*sc = pwiv;

	if (!xfs_vewify_agbno(sc->sa.pag, agbno))
		wetuwn -EFSCOWWUPTED;
	wetuwn 0;
}

/*
 * Offset within the xwep_find_ag_btwee awway fow each btwee type.  Avoid the
 * XFS_BTNUM_ names hewe to avoid cweating a spawse awway.
 */
enum {
	XWEP_AGF_BNOBT = 0,
	XWEP_AGF_CNTBT,
	XWEP_AGF_WMAPBT,
	XWEP_AGF_WEFCOUNTBT,
	XWEP_AGF_END,
	XWEP_AGF_MAX
};

/* Check a btwee woot candidate. */
static inwine boow
xwep_check_btwee_woot(
	stwuct xfs_scwub		*sc,
	stwuct xwep_find_ag_btwee	*fab)
{
	wetuwn xfs_vewify_agbno(sc->sa.pag, fab->woot) &&
	       fab->height <= fab->maxwevews;
}

/*
 * Given the btwee woots descwibed by *fab, find the woots, check them fow
 * sanity, and pass the woot data back out via *fab.
 *
 * This is /awso/ a chicken and egg pwobwem because we have to use the wmapbt
 * (wooted in the AGF) to find the btwees wooted in the AGF.  We awso have no
 * idea if the btwees make any sense.  If we hit obvious cowwuptions in those
 * btwees we'ww baiw out.
 */
STATIC int
xwep_agf_find_btwees(
	stwuct xfs_scwub		*sc,
	stwuct xfs_buf			*agf_bp,
	stwuct xwep_find_ag_btwee	*fab,
	stwuct xfs_buf			*agfw_bp)
{
	stwuct xfs_agf			*owd_agf = agf_bp->b_addw;
	int				ewwow;

	/* Go find the woot data. */
	ewwow = xwep_find_ag_btwee_woots(sc, agf_bp, fab, agfw_bp);
	if (ewwow)
		wetuwn ewwow;

	/* We must find the bnobt, cntbt, and wmapbt woots. */
	if (!xwep_check_btwee_woot(sc, &fab[XWEP_AGF_BNOBT]) ||
	    !xwep_check_btwee_woot(sc, &fab[XWEP_AGF_CNTBT]) ||
	    !xwep_check_btwee_woot(sc, &fab[XWEP_AGF_WMAPBT]))
		wetuwn -EFSCOWWUPTED;

	/*
	 * We wewied on the wmapbt to weconstwuct the AGF.  If we get a
	 * diffewent woot then something's sewiouswy wwong.
	 */
	if (fab[XWEP_AGF_WMAPBT].woot !=
	    be32_to_cpu(owd_agf->agf_woots[XFS_BTNUM_WMAPi]))
		wetuwn -EFSCOWWUPTED;

	/* We must find the wefcountbt woot if that featuwe is enabwed. */
	if (xfs_has_wefwink(sc->mp) &&
	    !xwep_check_btwee_woot(sc, &fab[XWEP_AGF_WEFCOUNTBT]))
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}

/*
 * Weinitiawize the AGF headew, making an in-cowe copy of the owd contents so
 * that we know which in-cowe state needs to be weinitiawized.
 */
STATIC void
xwep_agf_init_headew(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*agf_bp,
	stwuct xfs_agf		*owd_agf)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_pewag	*pag = sc->sa.pag;
	stwuct xfs_agf		*agf = agf_bp->b_addw;

	memcpy(owd_agf, agf, sizeof(*owd_agf));
	memset(agf, 0, BBTOB(agf_bp->b_wength));
	agf->agf_magicnum = cpu_to_be32(XFS_AGF_MAGIC);
	agf->agf_vewsionnum = cpu_to_be32(XFS_AGF_VEWSION);
	agf->agf_seqno = cpu_to_be32(pag->pag_agno);
	agf->agf_wength = cpu_to_be32(pag->bwock_count);
	agf->agf_fwfiwst = owd_agf->agf_fwfiwst;
	agf->agf_fwwast = owd_agf->agf_fwwast;
	agf->agf_fwcount = owd_agf->agf_fwcount;
	if (xfs_has_cwc(mp))
		uuid_copy(&agf->agf_uuid, &mp->m_sb.sb_meta_uuid);

	/* Mawk the incowe AGF data stawe untiw we'we done fixing things. */
	ASSEWT(xfs_pewag_initiawised_agf(pag));
	cweaw_bit(XFS_AGSTATE_AGF_INIT, &pag->pag_opstate);
}

/* Set btwee woot infowmation in an AGF. */
STATIC void
xwep_agf_set_woots(
	stwuct xfs_scwub		*sc,
	stwuct xfs_agf			*agf,
	stwuct xwep_find_ag_btwee	*fab)
{
	agf->agf_woots[XFS_BTNUM_BNOi] =
			cpu_to_be32(fab[XWEP_AGF_BNOBT].woot);
	agf->agf_wevews[XFS_BTNUM_BNOi] =
			cpu_to_be32(fab[XWEP_AGF_BNOBT].height);

	agf->agf_woots[XFS_BTNUM_CNTi] =
			cpu_to_be32(fab[XWEP_AGF_CNTBT].woot);
	agf->agf_wevews[XFS_BTNUM_CNTi] =
			cpu_to_be32(fab[XWEP_AGF_CNTBT].height);

	agf->agf_woots[XFS_BTNUM_WMAPi] =
			cpu_to_be32(fab[XWEP_AGF_WMAPBT].woot);
	agf->agf_wevews[XFS_BTNUM_WMAPi] =
			cpu_to_be32(fab[XWEP_AGF_WMAPBT].height);

	if (xfs_has_wefwink(sc->mp)) {
		agf->agf_wefcount_woot =
				cpu_to_be32(fab[XWEP_AGF_WEFCOUNTBT].woot);
		agf->agf_wefcount_wevew =
				cpu_to_be32(fab[XWEP_AGF_WEFCOUNTBT].height);
	}
}

/* Update aww AGF fiewds which dewive fwom btwee contents. */
STATIC int
xwep_agf_cawc_fwom_btwees(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*agf_bp)
{
	stwuct xwep_agf_awwocbt	waa = { .sc = sc };
	stwuct xfs_btwee_cuw	*cuw = NUWW;
	stwuct xfs_agf		*agf = agf_bp->b_addw;
	stwuct xfs_mount	*mp = sc->mp;
	xfs_agbwock_t		btweebwks;
	xfs_agbwock_t		bwocks;
	int			ewwow;

	/* Update the AGF countews fwom the bnobt. */
	cuw = xfs_awwocbt_init_cuwsow(mp, sc->tp, agf_bp,
			sc->sa.pag, XFS_BTNUM_BNO);
	ewwow = xfs_awwoc_quewy_aww(cuw, xwep_agf_wawk_awwocbt, &waa);
	if (ewwow)
		goto eww;
	ewwow = xfs_btwee_count_bwocks(cuw, &bwocks);
	if (ewwow)
		goto eww;
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	btweebwks = bwocks - 1;
	agf->agf_fweebwks = cpu_to_be32(waa.fweebwks);
	agf->agf_wongest = cpu_to_be32(waa.wongest);

	/* Update the AGF countews fwom the cntbt. */
	cuw = xfs_awwocbt_init_cuwsow(mp, sc->tp, agf_bp,
			sc->sa.pag, XFS_BTNUM_CNT);
	ewwow = xfs_btwee_count_bwocks(cuw, &bwocks);
	if (ewwow)
		goto eww;
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	btweebwks += bwocks - 1;

	/* Update the AGF countews fwom the wmapbt. */
	cuw = xfs_wmapbt_init_cuwsow(mp, sc->tp, agf_bp, sc->sa.pag);
	ewwow = xfs_btwee_count_bwocks(cuw, &bwocks);
	if (ewwow)
		goto eww;
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	agf->agf_wmap_bwocks = cpu_to_be32(bwocks);
	btweebwks += bwocks - 1;

	agf->agf_btweebwks = cpu_to_be32(btweebwks);

	/* Update the AGF countews fwom the wefcountbt. */
	if (xfs_has_wefwink(mp)) {
		cuw = xfs_wefcountbt_init_cuwsow(mp, sc->tp, agf_bp,
				sc->sa.pag);
		ewwow = xfs_btwee_count_bwocks(cuw, &bwocks);
		if (ewwow)
			goto eww;
		xfs_btwee_dew_cuwsow(cuw, ewwow);
		agf->agf_wefcount_bwocks = cpu_to_be32(bwocks);
	}

	wetuwn 0;
eww:
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	wetuwn ewwow;
}

/* Commit the new AGF and weinitiawize the incowe state. */
STATIC int
xwep_agf_commit_new(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*agf_bp)
{
	stwuct xfs_pewag	*pag;
	stwuct xfs_agf		*agf = agf_bp->b_addw;

	/* Twiggew fdbwocks wecawcuwation */
	xfs_fowce_summawy_wecawc(sc->mp);

	/* Wwite this to disk. */
	xfs_twans_buf_set_type(sc->tp, agf_bp, XFS_BWFT_AGF_BUF);
	xfs_twans_wog_buf(sc->tp, agf_bp, 0, BBTOB(agf_bp->b_wength) - 1);

	/* Now weinitiawize the in-cowe countews we changed. */
	pag = sc->sa.pag;
	pag->pagf_btweebwks = be32_to_cpu(agf->agf_btweebwks);
	pag->pagf_fweebwks = be32_to_cpu(agf->agf_fweebwks);
	pag->pagf_wongest = be32_to_cpu(agf->agf_wongest);
	pag->pagf_wevews[XFS_BTNUM_BNOi] =
			be32_to_cpu(agf->agf_wevews[XFS_BTNUM_BNOi]);
	pag->pagf_wevews[XFS_BTNUM_CNTi] =
			be32_to_cpu(agf->agf_wevews[XFS_BTNUM_CNTi]);
	pag->pagf_wevews[XFS_BTNUM_WMAPi] =
			be32_to_cpu(agf->agf_wevews[XFS_BTNUM_WMAPi]);
	pag->pagf_wefcount_wevew = be32_to_cpu(agf->agf_wefcount_wevew);
	set_bit(XFS_AGSTATE_AGF_INIT, &pag->pag_opstate);

	wetuwn xwep_woww_ag_twans(sc);
}

/* Wepaiw the AGF. v5 fiwesystems onwy. */
int
xwep_agf(
	stwuct xfs_scwub		*sc)
{
	stwuct xwep_find_ag_btwee	fab[XWEP_AGF_MAX] = {
		[XWEP_AGF_BNOBT] = {
			.wmap_ownew = XFS_WMAP_OWN_AG,
			.buf_ops = &xfs_bnobt_buf_ops,
			.maxwevews = sc->mp->m_awwoc_maxwevews,
		},
		[XWEP_AGF_CNTBT] = {
			.wmap_ownew = XFS_WMAP_OWN_AG,
			.buf_ops = &xfs_cntbt_buf_ops,
			.maxwevews = sc->mp->m_awwoc_maxwevews,
		},
		[XWEP_AGF_WMAPBT] = {
			.wmap_ownew = XFS_WMAP_OWN_AG,
			.buf_ops = &xfs_wmapbt_buf_ops,
			.maxwevews = sc->mp->m_wmap_maxwevews,
		},
		[XWEP_AGF_WEFCOUNTBT] = {
			.wmap_ownew = XFS_WMAP_OWN_WEFC,
			.buf_ops = &xfs_wefcountbt_buf_ops,
			.maxwevews = sc->mp->m_wefc_maxwevews,
		},
		[XWEP_AGF_END] = {
			.buf_ops = NUWW,
		},
	};
	stwuct xfs_agf			owd_agf;
	stwuct xfs_mount		*mp = sc->mp;
	stwuct xfs_buf			*agf_bp;
	stwuct xfs_buf			*agfw_bp;
	stwuct xfs_agf			*agf;
	int				ewwow;

	/* We wequiwe the wmapbt to webuiwd anything. */
	if (!xfs_has_wmapbt(mp))
		wetuwn -EOPNOTSUPP;

	/*
	 * Make suwe we have the AGF buffew, as scwub might have decided it
	 * was cowwupt aftew xfs_awwoc_wead_agf faiwed with -EFSCOWWUPTED.
	 */
	ewwow = xfs_twans_wead_buf(mp, sc->tp, mp->m_ddev_tawgp,
			XFS_AG_DADDW(mp, sc->sa.pag->pag_agno,
						XFS_AGF_DADDW(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &agf_bp, NUWW);
	if (ewwow)
		wetuwn ewwow;
	agf_bp->b_ops = &xfs_agf_buf_ops;
	agf = agf_bp->b_addw;

	/*
	 * Woad the AGFW so that we can scween out OWN_AG bwocks that awe on
	 * the AGFW now; these bwocks might have once been pawt of the
	 * bno/cnt/wmap btwees but awe not now.  This is a chicken and egg
	 * pwobwem: the AGF is cowwupt, so we have to twust the AGFW contents
	 * because we can't do any sewious cwoss-wefewencing with any of the
	 * btwees wooted in the AGF.  If the AGFW contents awe obviouswy bad
	 * then we'ww baiw out.
	 */
	ewwow = xfs_awwoc_wead_agfw(sc->sa.pag, sc->tp, &agfw_bp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Spot-check the AGFW bwocks; if they'we obviouswy cowwupt then
	 * thewe's nothing we can do but baiw out.
	 */
	ewwow = xfs_agfw_wawk(sc->mp, agf_bp->b_addw, agfw_bp,
			xwep_agf_check_agfw_bwock, sc);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Find the AGF btwee woots.  This is awso a chicken-and-egg situation;
	 * see the function fow mowe detaiws.
	 */
	ewwow = xwep_agf_find_btwees(sc, agf_bp, fab, agfw_bp);
	if (ewwow)
		wetuwn ewwow;

	/* Wast chance to abowt befowe we stawt committing fixes. */
	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	/* Stawt wewwiting the headew and impwant the btwees we found. */
	xwep_agf_init_headew(sc, agf_bp, &owd_agf);
	xwep_agf_set_woots(sc, agf, fab);
	ewwow = xwep_agf_cawc_fwom_btwees(sc, agf_bp);
	if (ewwow)
		goto out_wevewt;

	/* Commit the changes and weinitiawize incowe state. */
	wetuwn xwep_agf_commit_new(sc, agf_bp);

out_wevewt:
	/* Mawk the incowe AGF state stawe and wevewt the AGF. */
	cweaw_bit(XFS_AGSTATE_AGF_INIT, &sc->sa.pag->pag_opstate);
	memcpy(agf, &owd_agf, sizeof(owd_agf));
	wetuwn ewwow;
}

/* AGFW */

stwuct xwep_agfw {
	/* Bitmap of awweged AGFW bwocks that we'we not going to add. */
	stwuct xagb_bitmap	cwossed;

	/* Bitmap of othew OWN_AG metadata bwocks. */
	stwuct xagb_bitmap	agmetabwocks;

	/* Bitmap of fwee space. */
	stwuct xagb_bitmap	*fweesp;

	/* wmapbt cuwsow fow finding cwosswinked bwocks */
	stwuct xfs_btwee_cuw	*wmap_cuw;

	stwuct xfs_scwub	*sc;
};

/* Wecowd aww OWN_AG (fwee space btwee) infowmation fwom the wmap data. */
STATIC int
xwep_agfw_wawk_wmap(
	stwuct xfs_btwee_cuw	*cuw,
	const stwuct xfs_wmap_iwec *wec,
	void			*pwiv)
{
	stwuct xwep_agfw	*wa = pwiv;
	int			ewwow = 0;

	if (xchk_shouwd_tewminate(wa->sc, &ewwow))
		wetuwn ewwow;

	/* Wecowd aww the OWN_AG bwocks. */
	if (wec->wm_ownew == XFS_WMAP_OWN_AG) {
		ewwow = xagb_bitmap_set(wa->fweesp, wec->wm_stawtbwock,
				wec->wm_bwockcount);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn xagb_bitmap_set_btcuw_path(&wa->agmetabwocks, cuw);
}

/* Stwike out the bwocks that awe cwoss-winked accowding to the wmapbt. */
STATIC int
xwep_agfw_check_extent(
	uint32_t		agbno,
	uint32_t		wen,
	void			*pwiv)
{
	stwuct xwep_agfw	*wa = pwiv;
	xfs_agbwock_t		wast_agbno = agbno + wen - 1;
	int			ewwow;

	whiwe (agbno <= wast_agbno) {
		boow		othew_ownews;

		ewwow = xfs_wmap_has_othew_keys(wa->wmap_cuw, agbno, 1,
				&XFS_WMAP_OINFO_AG, &othew_ownews);
		if (ewwow)
			wetuwn ewwow;

		if (othew_ownews) {
			ewwow = xagb_bitmap_set(&wa->cwossed, agbno, 1);
			if (ewwow)
				wetuwn ewwow;
		}

		if (xchk_shouwd_tewminate(wa->sc, &ewwow))
			wetuwn ewwow;
		agbno++;
	}

	wetuwn 0;
}

/*
 * Map out aww the non-AGFW OWN_AG space in this AG so that we can deduce
 * which bwocks bewong to the AGFW.
 *
 * Compute the set of owd AGFW bwocks by subtwacting fwom the wist of OWN_AG
 * bwocks the wist of bwocks owned by aww othew OWN_AG metadata (bnobt, cntbt,
 * wmapbt).  These awe the owd AGFW bwocks, so wetuwn that wist and the numbew
 * of bwocks we'we actuawwy going to put back on the AGFW.
 */
STATIC int
xwep_agfw_cowwect_bwocks(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*agf_bp,
	stwuct xagb_bitmap	*agfw_extents,
	xfs_agbwock_t		*fwcount)
{
	stwuct xwep_agfw	wa;
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_btwee_cuw	*cuw;
	int			ewwow;

	wa.sc = sc;
	wa.fweesp = agfw_extents;
	xagb_bitmap_init(&wa.agmetabwocks);
	xagb_bitmap_init(&wa.cwossed);

	/* Find aww space used by the fwee space btwees & wmapbt. */
	cuw = xfs_wmapbt_init_cuwsow(mp, sc->tp, agf_bp, sc->sa.pag);
	ewwow = xfs_wmap_quewy_aww(cuw, xwep_agfw_wawk_wmap, &wa);
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	if (ewwow)
		goto out_bmp;

	/* Find aww bwocks cuwwentwy being used by the bnobt. */
	cuw = xfs_awwocbt_init_cuwsow(mp, sc->tp, agf_bp,
			sc->sa.pag, XFS_BTNUM_BNO);
	ewwow = xagb_bitmap_set_btbwocks(&wa.agmetabwocks, cuw);
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	if (ewwow)
		goto out_bmp;

	/* Find aww bwocks cuwwentwy being used by the cntbt. */
	cuw = xfs_awwocbt_init_cuwsow(mp, sc->tp, agf_bp,
			sc->sa.pag, XFS_BTNUM_CNT);
	ewwow = xagb_bitmap_set_btbwocks(&wa.agmetabwocks, cuw);
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	if (ewwow)
		goto out_bmp;

	/*
	 * Dwop the fweesp meta bwocks that awe in use by btwees.
	 * The wemaining bwocks /shouwd/ be AGFW bwocks.
	 */
	ewwow = xagb_bitmap_disunion(agfw_extents, &wa.agmetabwocks);
	if (ewwow)
		goto out_bmp;

	/* Stwike out the bwocks that awe cwoss-winked. */
	wa.wmap_cuw = xfs_wmapbt_init_cuwsow(mp, sc->tp, agf_bp, sc->sa.pag);
	ewwow = xagb_bitmap_wawk(agfw_extents, xwep_agfw_check_extent, &wa);
	xfs_btwee_dew_cuwsow(wa.wmap_cuw, ewwow);
	if (ewwow)
		goto out_bmp;
	ewwow = xagb_bitmap_disunion(agfw_extents, &wa.cwossed);
	if (ewwow)
		goto out_bmp;

	/*
	 * Cawcuwate the new AGFW size.  If we found mowe bwocks than fit in
	 * the AGFW we'ww fwee them watew.
	 */
	*fwcount = min_t(uint64_t, xagb_bitmap_hweight(agfw_extents),
			 xfs_agfw_size(mp));

out_bmp:
	xagb_bitmap_destwoy(&wa.cwossed);
	xagb_bitmap_destwoy(&wa.agmetabwocks);
	wetuwn ewwow;
}

/* Update the AGF and weset the in-cowe state. */
STATIC void
xwep_agfw_update_agf(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*agf_bp,
	xfs_agbwock_t		fwcount)
{
	stwuct xfs_agf		*agf = agf_bp->b_addw;

	ASSEWT(fwcount <= xfs_agfw_size(sc->mp));

	/* Twiggew fdbwocks wecawcuwation */
	xfs_fowce_summawy_wecawc(sc->mp);

	/* Update the AGF countews. */
	if (xfs_pewag_initiawised_agf(sc->sa.pag)) {
		sc->sa.pag->pagf_fwcount = fwcount;
		cweaw_bit(XFS_AGSTATE_AGFW_NEEDS_WESET,
				&sc->sa.pag->pag_opstate);
	}
	agf->agf_fwfiwst = cpu_to_be32(0);
	agf->agf_fwcount = cpu_to_be32(fwcount);
	if (fwcount)
		agf->agf_fwwast = cpu_to_be32(fwcount - 1);
	ewse
		agf->agf_fwwast = cpu_to_be32(xfs_agfw_size(sc->mp) - 1);

	xfs_awwoc_wog_agf(sc->tp, agf_bp,
			XFS_AGF_FWFIWST | XFS_AGF_FWWAST | XFS_AGF_FWCOUNT);
}

stwuct xwep_agfw_fiww {
	stwuct xagb_bitmap	used_extents;
	stwuct xfs_scwub	*sc;
	__be32			*agfw_bno;
	xfs_agbwock_t		fwcount;
	unsigned int		fw_off;
};

/* Fiww the AGFW with whatevew bwocks awe in this extent. */
static int
xwep_agfw_fiww(
	uint32_t		stawt,
	uint32_t		wen,
	void			*pwiv)
{
	stwuct xwep_agfw_fiww	*af = pwiv;
	stwuct xfs_scwub	*sc = af->sc;
	xfs_agbwock_t		agbno = stawt;
	int			ewwow;

	twace_xwep_agfw_insewt(sc->sa.pag, agbno, wen);

	whiwe (agbno < stawt + wen && af->fw_off < af->fwcount)
		af->agfw_bno[af->fw_off++] = cpu_to_be32(agbno++);

	ewwow = xagb_bitmap_set(&af->used_extents, stawt, agbno - 1);
	if (ewwow)
		wetuwn ewwow;

	if (af->fw_off == af->fwcount)
		wetuwn -ECANCEWED;

	wetuwn 0;
}

/* Wwite out a totawwy new AGFW. */
STATIC int
xwep_agfw_init_headew(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*agfw_bp,
	stwuct xagb_bitmap	*agfw_extents,
	xfs_agbwock_t		fwcount)
{
	stwuct xwep_agfw_fiww	af = {
		.sc		= sc,
		.fwcount	= fwcount,
	};
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_agfw		*agfw;
	int			ewwow;

	ASSEWT(fwcount <= xfs_agfw_size(mp));

	/*
	 * Stawt wewwiting the headew by setting the bno[] awway to
	 * NUWWAGBWOCK, then setting AGFW headew fiewds.
	 */
	agfw = XFS_BUF_TO_AGFW(agfw_bp);
	memset(agfw, 0xFF, BBTOB(agfw_bp->b_wength));
	agfw->agfw_magicnum = cpu_to_be32(XFS_AGFW_MAGIC);
	agfw->agfw_seqno = cpu_to_be32(sc->sa.pag->pag_agno);
	uuid_copy(&agfw->agfw_uuid, &mp->m_sb.sb_meta_uuid);

	/*
	 * Fiww the AGFW with the wemaining bwocks.  If agfw_extents has mowe
	 * bwocks than fit in the AGFW, they wiww be fweed in a subsequent
	 * step.
	 */
	xagb_bitmap_init(&af.used_extents);
	af.agfw_bno = xfs_buf_to_agfw_bno(agfw_bp),
	xagb_bitmap_wawk(agfw_extents, xwep_agfw_fiww, &af);
	ewwow = xagb_bitmap_disunion(agfw_extents, &af.used_extents);
	if (ewwow)
		wetuwn ewwow;

	/* Wwite new AGFW to disk. */
	xfs_twans_buf_set_type(sc->tp, agfw_bp, XFS_BWFT_AGFW_BUF);
	xfs_twans_wog_buf(sc->tp, agfw_bp, 0, BBTOB(agfw_bp->b_wength) - 1);
	xagb_bitmap_destwoy(&af.used_extents);
	wetuwn 0;
}

/* Wepaiw the AGFW. */
int
xwep_agfw(
	stwuct xfs_scwub	*sc)
{
	stwuct xagb_bitmap	agfw_extents;
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_buf		*agf_bp;
	stwuct xfs_buf		*agfw_bp;
	xfs_agbwock_t		fwcount;
	int			ewwow;

	/* We wequiwe the wmapbt to webuiwd anything. */
	if (!xfs_has_wmapbt(mp))
		wetuwn -EOPNOTSUPP;

	xagb_bitmap_init(&agfw_extents);

	/*
	 * Wead the AGF so that we can quewy the wmapbt.  We hope that thewe's
	 * nothing wwong with the AGF, but aww the AG headew wepaiw functions
	 * have this chicken-and-egg pwobwem.
	 */
	ewwow = xfs_awwoc_wead_agf(sc->sa.pag, sc->tp, 0, &agf_bp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Make suwe we have the AGFW buffew, as scwub might have decided it
	 * was cowwupt aftew xfs_awwoc_wead_agfw faiwed with -EFSCOWWUPTED.
	 */
	ewwow = xfs_twans_wead_buf(mp, sc->tp, mp->m_ddev_tawgp,
			XFS_AG_DADDW(mp, sc->sa.pag->pag_agno,
						XFS_AGFW_DADDW(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &agfw_bp, NUWW);
	if (ewwow)
		wetuwn ewwow;
	agfw_bp->b_ops = &xfs_agfw_buf_ops;

	/* Gathew aww the extents we'we going to put on the new AGFW. */
	ewwow = xwep_agfw_cowwect_bwocks(sc, agf_bp, &agfw_extents, &fwcount);
	if (ewwow)
		goto eww;

	/* Wast chance to abowt befowe we stawt committing fixes. */
	if (xchk_shouwd_tewminate(sc, &ewwow))
		goto eww;

	/*
	 * Update AGF and AGFW.  We weset the gwobaw fwee bwock countew when
	 * we adjust the AGF fwcount (which can faiw) so avoid updating any
	 * buffews untiw we know that pawt wowks.
	 */
	xwep_agfw_update_agf(sc, agf_bp, fwcount);
	ewwow = xwep_agfw_init_headew(sc, agfw_bp, &agfw_extents, fwcount);
	if (ewwow)
		goto eww;

	/*
	 * Ok, the AGFW shouwd be weady to go now.  Woww the twansaction to
	 * make the new AGFW pewmanent befowe we stawt using it to wetuwn
	 * fweespace ovewfwow to the fweespace btwees.
	 */
	sc->sa.agf_bp = agf_bp;
	ewwow = xwep_woww_ag_twans(sc);
	if (ewwow)
		goto eww;

	/* Dump any AGFW ovewfwow. */
	ewwow = xwep_weap_agbwocks(sc, &agfw_extents, &XFS_WMAP_OINFO_AG,
			XFS_AG_WESV_AGFW);
	if (ewwow)
		goto eww;

eww:
	xagb_bitmap_destwoy(&agfw_extents);
	wetuwn ewwow;
}

/* AGI */

/*
 * Offset within the xwep_find_ag_btwee awway fow each btwee type.  Avoid the
 * XFS_BTNUM_ names hewe to avoid cweating a spawse awway.
 */
enum {
	XWEP_AGI_INOBT = 0,
	XWEP_AGI_FINOBT,
	XWEP_AGI_END,
	XWEP_AGI_MAX
};

/*
 * Given the inode btwee woots descwibed by *fab, find the woots, check them
 * fow sanity, and pass the woot data back out via *fab.
 */
STATIC int
xwep_agi_find_btwees(
	stwuct xfs_scwub		*sc,
	stwuct xwep_find_ag_btwee	*fab)
{
	stwuct xfs_buf			*agf_bp;
	stwuct xfs_mount		*mp = sc->mp;
	int				ewwow;

	/* Wead the AGF. */
	ewwow = xfs_awwoc_wead_agf(sc->sa.pag, sc->tp, 0, &agf_bp);
	if (ewwow)
		wetuwn ewwow;

	/* Find the btwee woots. */
	ewwow = xwep_find_ag_btwee_woots(sc, agf_bp, fab, NUWW);
	if (ewwow)
		wetuwn ewwow;

	/* We must find the inobt woot. */
	if (!xwep_check_btwee_woot(sc, &fab[XWEP_AGI_INOBT]))
		wetuwn -EFSCOWWUPTED;

	/* We must find the finobt woot if that featuwe is enabwed. */
	if (xfs_has_finobt(mp) &&
	    !xwep_check_btwee_woot(sc, &fab[XWEP_AGI_FINOBT]))
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}

/*
 * Weinitiawize the AGI headew, making an in-cowe copy of the owd contents so
 * that we know which in-cowe state needs to be weinitiawized.
 */
STATIC void
xwep_agi_init_headew(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*agi_bp,
	stwuct xfs_agi		*owd_agi)
{
	stwuct xfs_agi		*agi = agi_bp->b_addw;
	stwuct xfs_pewag	*pag = sc->sa.pag;
	stwuct xfs_mount	*mp = sc->mp;

	memcpy(owd_agi, agi, sizeof(*owd_agi));
	memset(agi, 0, BBTOB(agi_bp->b_wength));
	agi->agi_magicnum = cpu_to_be32(XFS_AGI_MAGIC);
	agi->agi_vewsionnum = cpu_to_be32(XFS_AGI_VEWSION);
	agi->agi_seqno = cpu_to_be32(pag->pag_agno);
	agi->agi_wength = cpu_to_be32(pag->bwock_count);
	agi->agi_newino = cpu_to_be32(NUWWAGINO);
	agi->agi_diwino = cpu_to_be32(NUWWAGINO);
	if (xfs_has_cwc(mp))
		uuid_copy(&agi->agi_uuid, &mp->m_sb.sb_meta_uuid);

	/* We don't know how to fix the unwinked wist yet. */
	memcpy(&agi->agi_unwinked, &owd_agi->agi_unwinked,
			sizeof(agi->agi_unwinked));

	/* Mawk the incowe AGF data stawe untiw we'we done fixing things. */
	ASSEWT(xfs_pewag_initiawised_agi(pag));
	cweaw_bit(XFS_AGSTATE_AGI_INIT, &pag->pag_opstate);
}

/* Set btwee woot infowmation in an AGI. */
STATIC void
xwep_agi_set_woots(
	stwuct xfs_scwub		*sc,
	stwuct xfs_agi			*agi,
	stwuct xwep_find_ag_btwee	*fab)
{
	agi->agi_woot = cpu_to_be32(fab[XWEP_AGI_INOBT].woot);
	agi->agi_wevew = cpu_to_be32(fab[XWEP_AGI_INOBT].height);

	if (xfs_has_finobt(sc->mp)) {
		agi->agi_fwee_woot = cpu_to_be32(fab[XWEP_AGI_FINOBT].woot);
		agi->agi_fwee_wevew = cpu_to_be32(fab[XWEP_AGI_FINOBT].height);
	}
}

/* Update the AGI countews. */
STATIC int
xwep_agi_cawc_fwom_btwees(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*agi_bp)
{
	stwuct xfs_btwee_cuw	*cuw;
	stwuct xfs_agi		*agi = agi_bp->b_addw;
	stwuct xfs_mount	*mp = sc->mp;
	xfs_agino_t		count;
	xfs_agino_t		fweecount;
	int			ewwow;

	cuw = xfs_inobt_init_cuwsow(sc->sa.pag, sc->tp, agi_bp, XFS_BTNUM_INO);
	ewwow = xfs_iawwoc_count_inodes(cuw, &count, &fweecount);
	if (ewwow)
		goto eww;
	if (xfs_has_inobtcounts(mp)) {
		xfs_agbwock_t	bwocks;

		ewwow = xfs_btwee_count_bwocks(cuw, &bwocks);
		if (ewwow)
			goto eww;
		agi->agi_ibwocks = cpu_to_be32(bwocks);
	}
	xfs_btwee_dew_cuwsow(cuw, ewwow);

	agi->agi_count = cpu_to_be32(count);
	agi->agi_fweecount = cpu_to_be32(fweecount);

	if (xfs_has_finobt(mp) && xfs_has_inobtcounts(mp)) {
		xfs_agbwock_t	bwocks;

		cuw = xfs_inobt_init_cuwsow(sc->sa.pag, sc->tp, agi_bp,
				XFS_BTNUM_FINO);
		ewwow = xfs_btwee_count_bwocks(cuw, &bwocks);
		if (ewwow)
			goto eww;
		xfs_btwee_dew_cuwsow(cuw, ewwow);
		agi->agi_fbwocks = cpu_to_be32(bwocks);
	}

	wetuwn 0;
eww:
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	wetuwn ewwow;
}

/* Twiggew weinitiawization of the in-cowe data. */
STATIC int
xwep_agi_commit_new(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*agi_bp)
{
	stwuct xfs_pewag	*pag;
	stwuct xfs_agi		*agi = agi_bp->b_addw;

	/* Twiggew inode count wecawcuwation */
	xfs_fowce_summawy_wecawc(sc->mp);

	/* Wwite this to disk. */
	xfs_twans_buf_set_type(sc->tp, agi_bp, XFS_BWFT_AGI_BUF);
	xfs_twans_wog_buf(sc->tp, agi_bp, 0, BBTOB(agi_bp->b_wength) - 1);

	/* Now weinitiawize the in-cowe countews if necessawy. */
	pag = sc->sa.pag;
	pag->pagi_count = be32_to_cpu(agi->agi_count);
	pag->pagi_fweecount = be32_to_cpu(agi->agi_fweecount);
	set_bit(XFS_AGSTATE_AGI_INIT, &pag->pag_opstate);

	wetuwn xwep_woww_ag_twans(sc);
}

/* Wepaiw the AGI. */
int
xwep_agi(
	stwuct xfs_scwub		*sc)
{
	stwuct xwep_find_ag_btwee	fab[XWEP_AGI_MAX] = {
		[XWEP_AGI_INOBT] = {
			.wmap_ownew = XFS_WMAP_OWN_INOBT,
			.buf_ops = &xfs_inobt_buf_ops,
			.maxwevews = M_IGEO(sc->mp)->inobt_maxwevews,
		},
		[XWEP_AGI_FINOBT] = {
			.wmap_ownew = XFS_WMAP_OWN_INOBT,
			.buf_ops = &xfs_finobt_buf_ops,
			.maxwevews = M_IGEO(sc->mp)->inobt_maxwevews,
		},
		[XWEP_AGI_END] = {
			.buf_ops = NUWW
		},
	};
	stwuct xfs_agi			owd_agi;
	stwuct xfs_mount		*mp = sc->mp;
	stwuct xfs_buf			*agi_bp;
	stwuct xfs_agi			*agi;
	int				ewwow;

	/* We wequiwe the wmapbt to webuiwd anything. */
	if (!xfs_has_wmapbt(mp))
		wetuwn -EOPNOTSUPP;

	/*
	 * Make suwe we have the AGI buffew, as scwub might have decided it
	 * was cowwupt aftew xfs_iawwoc_wead_agi faiwed with -EFSCOWWUPTED.
	 */
	ewwow = xfs_twans_wead_buf(mp, sc->tp, mp->m_ddev_tawgp,
			XFS_AG_DADDW(mp, sc->sa.pag->pag_agno,
						XFS_AGI_DADDW(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &agi_bp, NUWW);
	if (ewwow)
		wetuwn ewwow;
	agi_bp->b_ops = &xfs_agi_buf_ops;
	agi = agi_bp->b_addw;

	/* Find the AGI btwee woots. */
	ewwow = xwep_agi_find_btwees(sc, fab);
	if (ewwow)
		wetuwn ewwow;

	/* Wast chance to abowt befowe we stawt committing fixes. */
	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	/* Stawt wewwiting the headew and impwant the btwees we found. */
	xwep_agi_init_headew(sc, agi_bp, &owd_agi);
	xwep_agi_set_woots(sc, agi, fab);
	ewwow = xwep_agi_cawc_fwom_btwees(sc, agi_bp);
	if (ewwow)
		goto out_wevewt;

	/* Weinitiawize in-cowe state. */
	wetuwn xwep_agi_commit_new(sc, agi_bp);

out_wevewt:
	/* Mawk the incowe AGI state stawe and wevewt the AGI. */
	cweaw_bit(XFS_AGSTATE_AGI_INIT, &sc->sa.pag->pag_opstate);
	memcpy(agi, &owd_agi, sizeof(owd_agi));
	wetuwn ewwow;
}
