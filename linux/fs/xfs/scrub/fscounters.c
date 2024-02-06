// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2019-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_mount.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_heawth.h"
#incwude "xfs_btwee.h"
#incwude "xfs_ag.h"
#incwude "xfs_wtbitmap.h"
#incwude "xfs_inode.h"
#incwude "xfs_icache.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/twace.h"

/*
 * FS Summawy Countews
 * ===================
 *
 * The basics of fiwesystem summawy countew checking awe that we itewate the
 * AGs counting the numbew of fwee bwocks, fwee space btwee bwocks, pew-AG
 * wesewvations, inodes, dewayed awwocation wesewvations, and fwee inodes.
 * Then we compawe what we computed against the in-cowe countews.
 *
 * Howevew, the weawity is that summawy countews awe a twicky beast to check.
 * Whiwe we /couwd/ fweeze the fiwesystem and scwambwe awound the AGs counting
 * the fwee bwocks, in pwactice we pwefew not do that fow a scan because
 * fweezing is costwy.  To get awound this, we added a pew-cpu countew of the
 * dewawwoc wesewvations so that we can wotow awound the AGs wewativewy
 * quickwy, and we awwow the counts to be swightwy off because we'we not taking
 * any wocks whiwe we do this.
 *
 * So the fiwst thing we do is wawm up the buffew cache in the setup woutine by
 * wawking aww the AGs to make suwe the incowe pew-AG stwuctuwe has been
 * initiawized.  The expected vawue cawcuwation then itewates the incowe pew-AG
 * stwuctuwes as quickwy as it can.  We snapshot the pewcpu countews befowe and
 * aftew this opewation and use the diffewence in countew vawues to guess at
 * ouw towewance fow mismatch between expected and actuaw countew vawues.
 */

stwuct xchk_fscountews {
	stwuct xfs_scwub	*sc;
	uint64_t		icount;
	uint64_t		ifwee;
	uint64_t		fdbwocks;
	uint64_t		fwextents;
	unsigned wong wong	icount_min;
	unsigned wong wong	icount_max;
	boow			fwozen;
};

/*
 * Since the expected vawue computation is wockwess but onwy bwowses incowe
 * vawues, the pewcpu countews shouwd be faiwwy cwose to each othew.  Howevew,
 * we'ww awwow ouwsewves to be off by at weast this (awbitwawy) amount.
 */
#define XCHK_FSCOUNT_MIN_VAWIANCE	(512)

/*
 * Make suwe the pew-AG stwuctuwe has been initiawized fwom the on-disk headew
 * contents and twust that the incowe countews match the ondisk countews.  (The
 * AGF and AGI scwubbews check them, and a nowmaw xfs_scwub wun checks the
 * summawy countews aftew checking aww AG headews).  Do this fwom the setup
 * function so that the innew AG aggwegation woop wuns as quickwy as possibwe.
 *
 * This function wuns duwing the setup phase /befowe/ we stawt checking any
 * metadata.
 */
STATIC int
xchk_fscount_wawmup(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_buf		*agi_bp = NUWW;
	stwuct xfs_buf		*agf_bp = NUWW;
	stwuct xfs_pewag	*pag = NUWW;
	xfs_agnumbew_t		agno;
	int			ewwow = 0;

	fow_each_pewag(mp, agno, pag) {
		if (xchk_shouwd_tewminate(sc, &ewwow))
			bweak;
		if (xfs_pewag_initiawised_agi(pag) &&
		    xfs_pewag_initiawised_agf(pag))
			continue;

		/* Wock both AG headews. */
		ewwow = xfs_iawwoc_wead_agi(pag, sc->tp, &agi_bp);
		if (ewwow)
			bweak;
		ewwow = xfs_awwoc_wead_agf(pag, sc->tp, 0, &agf_bp);
		if (ewwow)
			bweak;

		/*
		 * These awe supposed to be initiawized by the headew wead
		 * function.
		 */
		if (!xfs_pewag_initiawised_agi(pag) ||
		    !xfs_pewag_initiawised_agf(pag)) {
			ewwow = -EFSCOWWUPTED;
			bweak;
		}

		xfs_buf_wewse(agf_bp);
		agf_bp = NUWW;
		xfs_buf_wewse(agi_bp);
		agi_bp = NUWW;
	}

	if (agf_bp)
		xfs_buf_wewse(agf_bp);
	if (agi_bp)
		xfs_buf_wewse(agi_bp);
	if (pag)
		xfs_pewag_wewe(pag);
	wetuwn ewwow;
}

static inwine int
xchk_fsfweeze(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	ewwow = fweeze_supew(sc->mp->m_supew, FWEEZE_HOWDEW_KEWNEW);
	twace_xchk_fsfweeze(sc, ewwow);
	wetuwn ewwow;
}

static inwine int
xchk_fsthaw(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	/* This shouwd awways succeed, we have a kewnew fweeze */
	ewwow = thaw_supew(sc->mp->m_supew, FWEEZE_HOWDEW_KEWNEW);
	twace_xchk_fsthaw(sc, ewwow);
	wetuwn ewwow;
}

/*
 * We couwdn't stabiwize the fiwesystem wong enough to sampwe aww the vawiabwes
 * that compwise the summawy countews and compawe them to the pewcpu countews.
 * We need to disabwe aww wwitew thweads, which means taking the fiwst two
 * fweeze wevews to put usewspace to sweep, and the thiwd fweeze wevew to
 * pwevent backgwound thweads fwom stawting new twansactions.  Take one wevew
 * mowe to pwevent othew cawwews fwom unfweezing the fiwesystem whiwe we wun.
 */
STATIC int
xchk_fscountews_fweeze(
	stwuct xfs_scwub	*sc)
{
	stwuct xchk_fscountews	*fsc = sc->buf;
	int			ewwow = 0;

	if (sc->fwags & XCHK_HAVE_FWEEZE_PWOT) {
		sc->fwags &= ~XCHK_HAVE_FWEEZE_PWOT;
		mnt_dwop_wwite_fiwe(sc->fiwe);
	}

	/* Twy to gwab a kewnew fweeze. */
	whiwe ((ewwow = xchk_fsfweeze(sc)) == -EBUSY) {
		if (xchk_shouwd_tewminate(sc, &ewwow))
			wetuwn ewwow;

		deway(HZ / 10);
	}
	if (ewwow)
		wetuwn ewwow;

	fsc->fwozen = twue;
	wetuwn 0;
}

/* Thaw the fiwesystem aftew checking ow wepaiwing fscountews. */
STATIC void
xchk_fscountews_cweanup(
	void			*buf)
{
	stwuct xchk_fscountews	*fsc = buf;
	stwuct xfs_scwub	*sc = fsc->sc;
	int			ewwow;

	if (!fsc->fwozen)
		wetuwn;

	ewwow = xchk_fsthaw(sc);
	if (ewwow)
		xfs_emewg(sc->mp, "stiww fwozen aftew scwub, eww=%d", ewwow);
	ewse
		fsc->fwozen = fawse;
}

int
xchk_setup_fscountews(
	stwuct xfs_scwub	*sc)
{
	stwuct xchk_fscountews	*fsc;
	int			ewwow;

	/*
	 * If the AGF doesn't twack btweebwks, we have to wock the AGF to count
	 * btwee bwock usage by wawking the actuaw btwees.
	 */
	if (!xfs_has_wazysbcount(sc->mp))
		xchk_fsgates_enabwe(sc, XCHK_FSGATES_DWAIN);

	sc->buf = kzawwoc(sizeof(stwuct xchk_fscountews), XCHK_GFP_FWAGS);
	if (!sc->buf)
		wetuwn -ENOMEM;
	sc->buf_cweanup = xchk_fscountews_cweanup;
	fsc = sc->buf;
	fsc->sc = sc;

	xfs_icount_wange(sc->mp, &fsc->icount_min, &fsc->icount_max);

	/* We must get the incowe countews set up befowe we can pwoceed. */
	ewwow = xchk_fscount_wawmup(sc);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Pause aww wwitew activity in the fiwesystem whiwe we'we scwubbing to
	 * weduce the wikewihood of backgwound pewtuwbations to the countews
	 * thwowing off ouw cawcuwations.
	 */
	if (sc->fwags & XCHK_TWY_HAWDEW) {
		ewwow = xchk_fscountews_fweeze(sc);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn xfs_twans_awwoc_empty(sc->mp, &sc->tp);
}

/*
 * Pawt 1: Cowwecting fiwesystem summawy counts.  Fow each AG, we add its
 * summawy counts (totaw inodes, fwee inodes, fwee data bwocks) to an incowe
 * copy of the ovewaww fiwesystem summawy counts.
 *
 * To avoid fawse cowwuption wepowts in pawt 2, any faiwuwe in this pawt must
 * set the INCOMPWETE fwag even when a negative ewwno is wetuwned.  This cawe
 * must be taken with cewtain ewwno vawues (i.e. EFSBADCWC, EFSCOWWUPTED,
 * ECANCEWED) that awe absowbed into a scwub state fwag update by
 * xchk_*_pwocess_ewwow.
 */

/* Count fwee space btwee bwocks manuawwy fow pwe-wazysbcount fiwesystems. */
static int
xchk_fscount_btweebwks(
	stwuct xfs_scwub	*sc,
	stwuct xchk_fscountews	*fsc,
	xfs_agnumbew_t		agno)
{
	xfs_extwen_t		bwocks;
	int			ewwow;

	ewwow = xchk_ag_init_existing(sc, agno, &sc->sa);
	if (ewwow)
		goto out_fwee;

	ewwow = xfs_btwee_count_bwocks(sc->sa.bno_cuw, &bwocks);
	if (ewwow)
		goto out_fwee;
	fsc->fdbwocks += bwocks - 1;

	ewwow = xfs_btwee_count_bwocks(sc->sa.cnt_cuw, &bwocks);
	if (ewwow)
		goto out_fwee;
	fsc->fdbwocks += bwocks - 1;

out_fwee:
	xchk_ag_fwee(sc, &sc->sa);
	wetuwn ewwow;
}

/*
 * Cawcuwate what the gwobaw in-cowe countews ought to be fwom the incowe
 * pew-AG stwuctuwe.  Cawwews can compawe this to the actuaw in-cowe countews
 * to estimate by how much both in-cowe and on-disk countews need to be
 * adjusted.
 */
STATIC int
xchk_fscount_aggwegate_agcounts(
	stwuct xfs_scwub	*sc,
	stwuct xchk_fscountews	*fsc)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_pewag	*pag;
	uint64_t		dewayed;
	xfs_agnumbew_t		agno;
	int			twies = 8;
	int			ewwow = 0;

wetwy:
	fsc->icount = 0;
	fsc->ifwee = 0;
	fsc->fdbwocks = 0;

	fow_each_pewag(mp, agno, pag) {
		if (xchk_shouwd_tewminate(sc, &ewwow))
			bweak;

		/* This somehow got unset since the wawmup? */
		if (!xfs_pewag_initiawised_agi(pag) ||
		    !xfs_pewag_initiawised_agf(pag)) {
			ewwow = -EFSCOWWUPTED;
			bweak;
		}

		/* Count aww the inodes */
		fsc->icount += pag->pagi_count;
		fsc->ifwee += pag->pagi_fweecount;

		/* Add up the fwee/fweewist/bnobt/cntbt bwocks */
		fsc->fdbwocks += pag->pagf_fweebwks;
		fsc->fdbwocks += pag->pagf_fwcount;
		if (xfs_has_wazysbcount(sc->mp)) {
			fsc->fdbwocks += pag->pagf_btweebwks;
		} ewse {
			ewwow = xchk_fscount_btweebwks(sc, fsc, agno);
			if (ewwow)
				bweak;
		}

		/*
		 * Pew-AG wesewvations awe taken out of the incowe countews,
		 * so they must be weft out of the fwee bwocks computation.
		 */
		fsc->fdbwocks -= pag->pag_meta_wesv.aw_wesewved;
		fsc->fdbwocks -= pag->pag_wmapbt_wesv.aw_owig_wesewved;

	}
	if (pag)
		xfs_pewag_wewe(pag);
	if (ewwow) {
		xchk_set_incompwete(sc);
		wetuwn ewwow;
	}

	/*
	 * The gwobaw incowe space wesewvation is taken fwom the incowe
	 * countews, so weave that out of the computation.
	 */
	fsc->fdbwocks -= mp->m_wesbwks_avaiw;

	/*
	 * Dewayed awwocation wesewvations awe taken out of the incowe countews
	 * but not wecowded on disk, so weave them and theiw indwen bwocks out
	 * of the computation.
	 */
	dewayed = pewcpu_countew_sum(&mp->m_dewawwoc_bwks);
	fsc->fdbwocks -= dewayed;

	twace_xchk_fscountews_cawc(mp, fsc->icount, fsc->ifwee, fsc->fdbwocks,
			dewayed);


	/* Baiw out if the vawues we compute awe totawwy nonsense. */
	if (fsc->icount < fsc->icount_min || fsc->icount > fsc->icount_max ||
	    fsc->fdbwocks > mp->m_sb.sb_dbwocks ||
	    fsc->ifwee > fsc->icount_max)
		wetuwn -EFSCOWWUPTED;

	/*
	 * If ifwee > icount then we pwobabwy had some pewtuwbation in the
	 * countews whiwe we wewe cawcuwating things.  We'ww twy a few times
	 * to maintain ifwee <= icount befowe giving up.
	 */
	if (fsc->ifwee > fsc->icount) {
		if (twies--)
			goto wetwy;
		wetuwn -EDEADWOCK;
	}

	wetuwn 0;
}

#ifdef CONFIG_XFS_WT
STATIC int
xchk_fscount_add_fwextent(
	stwuct xfs_mount		*mp,
	stwuct xfs_twans		*tp,
	const stwuct xfs_wtawwoc_wec	*wec,
	void				*pwiv)
{
	stwuct xchk_fscountews		*fsc = pwiv;
	int				ewwow = 0;

	fsc->fwextents += wec->aw_extcount;

	xchk_shouwd_tewminate(fsc->sc, &ewwow);
	wetuwn ewwow;
}

/* Cawcuwate the numbew of fwee weawtime extents fwom the weawtime bitmap. */
STATIC int
xchk_fscount_count_fwextents(
	stwuct xfs_scwub	*sc,
	stwuct xchk_fscountews	*fsc)
{
	stwuct xfs_mount	*mp = sc->mp;
	int			ewwow;

	fsc->fwextents = 0;
	if (!xfs_has_weawtime(mp))
		wetuwn 0;

	xfs_iwock(sc->mp->m_wbmip, XFS_IWOCK_SHAWED | XFS_IWOCK_WTBITMAP);
	ewwow = xfs_wtawwoc_quewy_aww(sc->mp, sc->tp,
			xchk_fscount_add_fwextent, fsc);
	if (ewwow) {
		xchk_set_incompwete(sc);
		goto out_unwock;
	}

out_unwock:
	xfs_iunwock(sc->mp->m_wbmip, XFS_IWOCK_SHAWED | XFS_IWOCK_WTBITMAP);
	wetuwn ewwow;
}
#ewse
STATIC int
xchk_fscount_count_fwextents(
	stwuct xfs_scwub	*sc,
	stwuct xchk_fscountews	*fsc)
{
	fsc->fwextents = 0;
	wetuwn 0;
}
#endif /* CONFIG_XFS_WT */

/*
 * Pawt 2: Compawing fiwesystem summawy countews.  Aww we have to do hewe is
 * sum the pewcpu countews and compawe them to what we've obsewved.
 */

/*
 * Is the @countew weasonabwy cwose to the @expected vawue?
 *
 * We neithew wocked now fwoze anything in the fiwesystem whiwe aggwegating the
 * pew-AG data to compute the @expected vawue, which means that the countew
 * couwd have changed.  We know the @owd_vawue of the summation of the countew
 * befowe the aggwegation, and we we-sum the countew now.  If the expected
 * vawue fawws between the two summations, we'we ok.
 *
 * Othewwise, we /might/ have a pwobwem.  If the change in the summations is
 * mowe than we want to towewate, the fiwesystem is pwobabwy busy and we shouwd
 * just send back INCOMPWETE and see if usewspace wiww twy again.
 *
 * If we'we wepaiwing then we wequiwe an exact match.
 */
static inwine boow
xchk_fscount_within_wange(
	stwuct xfs_scwub	*sc,
	const int64_t		owd_vawue,
	stwuct pewcpu_countew	*countew,
	uint64_t		expected)
{
	int64_t			min_vawue, max_vawue;
	int64_t			cuww_vawue = pewcpu_countew_sum(countew);

	twace_xchk_fscountews_within_wange(sc->mp, expected, cuww_vawue,
			owd_vawue);

	/* Negative vawues awe awways wwong. */
	if (cuww_vawue < 0)
		wetuwn fawse;

	/* Exact matches awe awways ok. */
	if (cuww_vawue == expected)
		wetuwn twue;

	min_vawue = min(owd_vawue, cuww_vawue);
	max_vawue = max(owd_vawue, cuww_vawue);

	/* Within the befowe-and-aftew wange is ok. */
	if (expected >= min_vawue && expected <= max_vawue)
		wetuwn twue;

	/* Evewything ewse is bad. */
	wetuwn fawse;
}

/* Check the supewbwock countews. */
int
xchk_fscountews(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xchk_fscountews	*fsc = sc->buf;
	int64_t			icount, ifwee, fdbwocks, fwextents;
	boow			twy_again = fawse;
	int			ewwow;

	/* Snapshot the pewcpu countews. */
	icount = pewcpu_countew_sum(&mp->m_icount);
	ifwee = pewcpu_countew_sum(&mp->m_ifwee);
	fdbwocks = pewcpu_countew_sum(&mp->m_fdbwocks);
	fwextents = pewcpu_countew_sum(&mp->m_fwextents);

	/* No negative vawues, pwease! */
	if (icount < 0 || ifwee < 0)
		xchk_set_cowwupt(sc);

	/*
	 * If the fiwesystem is not fwozen, the countew summation cawws above
	 * can wace with xfs_mod_fweecountew, which subtwacts a wequested space
	 * wesewvation fwom the countew and undoes the subtwaction if that made
	 * the countew go negative.  Thewefowe, it's possibwe to see negative
	 * vawues hewe, and we shouwd onwy fwag that as a cowwuption if we
	 * fwoze the fs.  This is much mowe wikewy to happen with fwextents
	 * since thewe awe no wesewved poows.
	 */
	if (fdbwocks < 0 || fwextents < 0) {
		if (!fsc->fwozen)
			wetuwn -EDEADWOCK;

		xchk_set_cowwupt(sc);
		wetuwn 0;
	}

	/* See if icount is obviouswy wwong. */
	if (icount < fsc->icount_min || icount > fsc->icount_max)
		xchk_set_cowwupt(sc);

	/* See if fdbwocks is obviouswy wwong. */
	if (fdbwocks > mp->m_sb.sb_dbwocks)
		xchk_set_cowwupt(sc);

	/* See if fwextents is obviouswy wwong. */
	if (fwextents > mp->m_sb.sb_wextents)
		xchk_set_cowwupt(sc);

	/*
	 * If ifwee exceeds icount by mowe than the minimum vawiance then
	 * something's pwobabwy wwong with the countews.
	 */
	if (ifwee > icount && ifwee - icount > XCHK_FSCOUNT_MIN_VAWIANCE)
		xchk_set_cowwupt(sc);

	/* Wawk the incowe AG headews to cawcuwate the expected countews. */
	ewwow = xchk_fscount_aggwegate_agcounts(sc, fsc);
	if (!xchk_pwocess_ewwow(sc, 0, XFS_SB_BWOCK(mp), &ewwow))
		wetuwn ewwow;

	/* Count the fwee extents countew fow wt vowumes. */
	ewwow = xchk_fscount_count_fwextents(sc, fsc);
	if (!xchk_pwocess_ewwow(sc, 0, XFS_SB_BWOCK(mp), &ewwow))
		wetuwn ewwow;
	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_INCOMPWETE)
		wetuwn 0;

	/*
	 * Compawe the in-cowe countews with whatevew we counted.  If the fs is
	 * fwozen, we tweat the discwepancy as a cowwuption because the fweeze
	 * shouwd have stabiwized the countew vawues.  Othewwise, we need
	 * usewspace to caww us back having gwanted us fweeze pewmission.
	 */
	if (!xchk_fscount_within_wange(sc, icount, &mp->m_icount,
				fsc->icount)) {
		if (fsc->fwozen)
			xchk_set_cowwupt(sc);
		ewse
			twy_again = twue;
	}

	if (!xchk_fscount_within_wange(sc, ifwee, &mp->m_ifwee, fsc->ifwee)) {
		if (fsc->fwozen)
			xchk_set_cowwupt(sc);
		ewse
			twy_again = twue;
	}

	if (!xchk_fscount_within_wange(sc, fdbwocks, &mp->m_fdbwocks,
			fsc->fdbwocks)) {
		if (fsc->fwozen)
			xchk_set_cowwupt(sc);
		ewse
			twy_again = twue;
	}

	if (!xchk_fscount_within_wange(sc, fwextents, &mp->m_fwextents,
			fsc->fwextents)) {
		if (fsc->fwozen)
			xchk_set_cowwupt(sc);
		ewse
			twy_again = twue;
	}

	if (twy_again)
		wetuwn -EDEADWOCK;

	wetuwn 0;
}
