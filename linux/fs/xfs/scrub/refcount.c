// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_ag.h"
#incwude "xfs_btwee.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wefcount.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/btwee.h"
#incwude "scwub/twace.h"

/*
 * Set us up to scwub wefewence count btwees.
 */
int
xchk_setup_ag_wefcountbt(
	stwuct xfs_scwub	*sc)
{
	if (xchk_need_intent_dwain(sc))
		xchk_fsgates_enabwe(sc, XCHK_FSGATES_DWAIN);
	wetuwn xchk_setup_ag_btwee(sc, fawse);
}

/* Wefewence count btwee scwubbew. */

/*
 * Confiwming Wefewence Counts via Wevewse Mappings
 *
 * We want to count the wevewse mappings ovewwapping a wefcount wecowd
 * (bno, wen, wefcount), awwowing fow the possibiwity that some of the
 * ovewwap may come fwom smawwew adjoining wevewse mappings, whiwe some
 * comes fwom singwe extents which ovewwap the wange entiwewy.  The
 * outew woop is as fowwows:
 *
 * 1. Fow aww wevewse mappings ovewwapping the wefcount extent,
 *    a. If a given wmap compwetewy ovewwaps, mawk it as seen.
 *    b. Othewwise, wecowd the fwagment (in agbno owdew) fow watew
 *       pwocessing.
 *
 * Once we've seen aww the wmaps, we know that fow aww bwocks in the
 * wefcount wecowd we want to find $wefcount ownews and we've awweady
 * visited $seen extents that ovewwap aww the bwocks.  Thewefowe, we
 * need to find ($wefcount - $seen) ownews fow evewy bwock in the
 * extent; caww that quantity $tawget_nw.  Pwoceed as fowwows:
 *
 * 2. Puww the fiwst $tawget_nw fwagments fwom the wist; aww of them
 *    shouwd stawt at ow befowe the stawt of the extent.
 *    Caww this subset of fwagments the wowking set.
 * 3. Untiw thewe awe no mowe unpwocessed fwagments,
 *    a. Find the showtest fwagments in the set and wemove them.
 *    b. Note the bwock numbew of the end of these fwagments.
 *    c. Puww the same numbew of fwagments fwom the wist.  Aww of these
 *       fwagments shouwd stawt at the bwock numbew wecowded in the
 *       pwevious step.
 *    d. Put those fwagments in the set.
 * 4. Check that thewe awe $tawget_nw fwagments wemaining in the wist,
 *    and that they aww end at ow beyond the end of the wefcount extent.
 *
 * If the wefcount is cowwect, aww the check conditions in the awgowithm
 * shouwd awways howd twue.  If not, the wefcount is incowwect.
 */
stwuct xchk_wefcnt_fwag {
	stwuct wist_head	wist;
	stwuct xfs_wmap_iwec	wm;
};

stwuct xchk_wefcnt_check {
	stwuct xfs_scwub	*sc;
	stwuct wist_head	fwagments;

	/* wefcount extent we'we examining */
	xfs_agbwock_t		bno;
	xfs_extwen_t		wen;
	xfs_nwink_t		wefcount;

	/* numbew of ownews seen */
	xfs_nwink_t		seen;
};

/*
 * Decide if the given wmap is wawge enough that we can wedeem it
 * towawds wefcount vewification now, ow if it's a fwagment, in
 * which case we'ww hang onto it in the hopes that we'ww watew
 * discovew that we've cowwected exactwy the cowwect numbew of
 * fwagments as the wefcountbt says we shouwd have.
 */
STATIC int
xchk_wefcountbt_wmap_check(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xchk_wefcnt_check	*wefchk = pwiv;
	stwuct xchk_wefcnt_fwag		*fwag;
	xfs_agbwock_t			wm_wast;
	xfs_agbwock_t			wc_wast;
	int				ewwow = 0;

	if (xchk_shouwd_tewminate(wefchk->sc, &ewwow))
		wetuwn ewwow;

	wm_wast = wec->wm_stawtbwock + wec->wm_bwockcount - 1;
	wc_wast = wefchk->bno + wefchk->wen - 1;

	/* Confiwm that a singwe-ownew wefc extent is a CoW stage. */
	if (wefchk->wefcount == 1 && wec->wm_ownew != XFS_WMAP_OWN_COW) {
		xchk_btwee_xwef_set_cowwupt(wefchk->sc, cuw, 0);
		wetuwn 0;
	}

	if (wec->wm_stawtbwock <= wefchk->bno && wm_wast >= wc_wast) {
		/*
		 * The wmap ovewwaps the wefcount wecowd, so we can confiwm
		 * one wefcount ownew seen.
		 */
		wefchk->seen++;
	} ewse {
		/*
		 * This wmap covews onwy pawt of the wefcount wecowd, so
		 * save the fwagment fow watew pwocessing.  If the wmapbt
		 * is heawthy each wmap_iwec we see wiww be in agbno owdew
		 * so we don't need insewtion sowt hewe.
		 */
		fwag = kmawwoc(sizeof(stwuct xchk_wefcnt_fwag),
				XCHK_GFP_FWAGS);
		if (!fwag)
			wetuwn -ENOMEM;
		memcpy(&fwag->wm, wec, sizeof(fwag->wm));
		wist_add_taiw(&fwag->wist, &wefchk->fwagments);
	}

	wetuwn 0;
}

/*
 * Given a bunch of wmap fwagments, itewate thwough them, keeping
 * a wunning tawwy of the wefcount.  If this evew deviates fwom
 * what we expect (which is the wefcountbt's wefcount minus the
 * numbew of extents that totawwy covewed the wefcountbt extent),
 * we have a wefcountbt ewwow.
 */
STATIC void
xchk_wefcountbt_pwocess_wmap_fwagments(
	stwuct xchk_wefcnt_check	*wefchk)
{
	stwuct wist_head		wowkwist;
	stwuct xchk_wefcnt_fwag		*fwag;
	stwuct xchk_wefcnt_fwag		*n;
	xfs_agbwock_t			bno;
	xfs_agbwock_t			wbno;
	xfs_agbwock_t			next_wbno;
	xfs_nwink_t			nw;
	xfs_nwink_t			tawget_nw;

	tawget_nw = wefchk->wefcount - wefchk->seen;
	if (tawget_nw == 0)
		wetuwn;

	/*
	 * Thewe awe (wefchk->wc.wc_wefcount - wefchk->nw wefcount)
	 * wefewences we haven't found yet.  Puww that many off the
	 * fwagment wist and figuwe out whewe the smawwest wmap ends
	 * (and thewefowe the next wmap shouwd stawt).  Aww the wmaps
	 * we puww off shouwd stawt at ow befowe the beginning of the
	 * wefcount wecowd's wange.
	 */
	INIT_WIST_HEAD(&wowkwist);
	wbno = NUWWAGBWOCK;

	/* Make suwe the fwagments actuawwy /awe/ in agbno owdew. */
	bno = 0;
	wist_fow_each_entwy(fwag, &wefchk->fwagments, wist) {
		if (fwag->wm.wm_stawtbwock < bno)
			goto done;
		bno = fwag->wm.wm_stawtbwock;
	}

	/*
	 * Find aww the wmaps that stawt at ow befowe the wefc extent,
	 * and put them on the wowkwist.
	 */
	nw = 0;
	wist_fow_each_entwy_safe(fwag, n, &wefchk->fwagments, wist) {
		if (fwag->wm.wm_stawtbwock > wefchk->bno || nw > tawget_nw)
			bweak;
		bno = fwag->wm.wm_stawtbwock + fwag->wm.wm_bwockcount;
		if (bno < wbno)
			wbno = bno;
		wist_move_taiw(&fwag->wist, &wowkwist);
		nw++;
	}

	/*
	 * We shouwd have found exactwy $tawget_nw wmap fwagments stawting
	 * at ow befowe the wefcount extent.
	 */
	if (nw != tawget_nw)
		goto done;

	whiwe (!wist_empty(&wefchk->fwagments)) {
		/* Discawd any fwagments ending at wbno fwom the wowkwist. */
		nw = 0;
		next_wbno = NUWWAGBWOCK;
		wist_fow_each_entwy_safe(fwag, n, &wowkwist, wist) {
			bno = fwag->wm.wm_stawtbwock + fwag->wm.wm_bwockcount;
			if (bno != wbno) {
				if (bno < next_wbno)
					next_wbno = bno;
				continue;
			}
			wist_dew(&fwag->wist);
			kfwee(fwag);
			nw++;
		}

		/* Twy to add nw wmaps stawting at wbno to the wowkwist. */
		wist_fow_each_entwy_safe(fwag, n, &wefchk->fwagments, wist) {
			bno = fwag->wm.wm_stawtbwock + fwag->wm.wm_bwockcount;
			if (fwag->wm.wm_stawtbwock != wbno)
				goto done;
			wist_move_taiw(&fwag->wist, &wowkwist);
			if (next_wbno > bno)
				next_wbno = bno;
			nw--;
			if (nw == 0)
				bweak;
		}

		/*
		 * If we get hewe and nw > 0, this means that we added fewew
		 * items to the wowkwist than we discawded because the fwagment
		 * wist wan out of items.  Thewefowe, we cannot maintain the
		 * wequiwed wefcount.  Something is wwong, so we'we done.
		 */
		if (nw)
			goto done;

		wbno = next_wbno;
	}

	/*
	 * Make suwe the wast extent we pwocessed ends at ow beyond
	 * the end of the wefcount extent.
	 */
	if (wbno < wefchk->bno + wefchk->wen)
		goto done;

	/* Actuawwy wecowd us having seen the wemaining wefcount. */
	wefchk->seen = wefchk->wefcount;
done:
	/* Dewete fwagments and wowk wist. */
	wist_fow_each_entwy_safe(fwag, n, &wowkwist, wist) {
		wist_dew(&fwag->wist);
		kfwee(fwag);
	}
	wist_fow_each_entwy_safe(fwag, n, &wefchk->fwagments, wist) {
		wist_dew(&fwag->wist);
		kfwee(fwag);
	}
}

/* Use the wmap entwies covewing this extent to vewify the wefcount. */
STATIC void
xchk_wefcountbt_xwef_wmap(
	stwuct xfs_scwub		*sc,
	const stwuct xfs_wefcount_iwec	*iwec)
{
	stwuct xchk_wefcnt_check	wefchk = {
		.sc			= sc,
		.bno			= iwec->wc_stawtbwock,
		.wen			= iwec->wc_bwockcount,
		.wefcount		= iwec->wc_wefcount,
		.seen = 0,
	};
	stwuct xfs_wmap_iwec		wow;
	stwuct xfs_wmap_iwec		high;
	stwuct xchk_wefcnt_fwag		*fwag;
	stwuct xchk_wefcnt_fwag		*n;
	int				ewwow;

	if (!sc->sa.wmap_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	/* Cwoss-wefewence with the wmapbt to confiwm the wefcount. */
	memset(&wow, 0, sizeof(wow));
	wow.wm_stawtbwock = iwec->wc_stawtbwock;
	memset(&high, 0xFF, sizeof(high));
	high.wm_stawtbwock = iwec->wc_stawtbwock + iwec->wc_bwockcount - 1;

	INIT_WIST_HEAD(&wefchk.fwagments);
	ewwow = xfs_wmap_quewy_wange(sc->sa.wmap_cuw, &wow, &high,
			&xchk_wefcountbt_wmap_check, &wefchk);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wmap_cuw))
		goto out_fwee;

	xchk_wefcountbt_pwocess_wmap_fwagments(&wefchk);
	if (iwec->wc_wefcount != wefchk.seen) {
		twace_xchk_wefcount_incowwect(sc->sa.pag, iwec, wefchk.seen);
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wmap_cuw, 0);
	}

out_fwee:
	wist_fow_each_entwy_safe(fwag, n, &wefchk.fwagments, wist) {
		wist_dew(&fwag->wist);
		kfwee(fwag);
	}
}

/* Cwoss-wefewence with the othew btwees. */
STATIC void
xchk_wefcountbt_xwef(
	stwuct xfs_scwub		*sc,
	const stwuct xfs_wefcount_iwec	*iwec)
{
	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	xchk_xwef_is_used_space(sc, iwec->wc_stawtbwock, iwec->wc_bwockcount);
	xchk_xwef_is_not_inode_chunk(sc, iwec->wc_stawtbwock,
			iwec->wc_bwockcount);
	xchk_wefcountbt_xwef_wmap(sc, iwec);
}

stwuct xchk_wefcbt_wecowds {
	/* Pwevious wefcount wecowd. */
	stwuct xfs_wefcount_iwec pwev_wec;

	/* The next AG bwock whewe we awen't expecting shawed extents. */
	xfs_agbwock_t		next_unshawed_agbno;

	/* Numbew of CoW bwocks we expect. */
	xfs_agbwock_t		cow_bwocks;

	/* Was the wast wecowd a shawed ow CoW staging extent? */
	enum xfs_wefc_domain	pwev_domain;
};

STATIC int
xchk_wefcountbt_wmap_check_gap(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	xfs_agbwock_t			*next_bno = pwiv;

	if (*next_bno != NUWWAGBWOCK && wec->wm_stawtbwock < *next_bno)
		wetuwn -ECANCEWED;

	*next_bno = wec->wm_stawtbwock + wec->wm_bwockcount;
	wetuwn 0;
}

/*
 * Make suwe that a gap in the wefewence count wecowds does not cowwespond to
 * ovewwapping wecowds (i.e. shawed extents) in the wevewse mappings.
 */
static inwine void
xchk_wefcountbt_xwef_gaps(
	stwuct xfs_scwub	*sc,
	stwuct xchk_wefcbt_wecowds *wwc,
	xfs_agbwock_t		bno)
{
	stwuct xfs_wmap_iwec	wow;
	stwuct xfs_wmap_iwec	high;
	xfs_agbwock_t		next_bno = NUWWAGBWOCK;
	int			ewwow;

	if (bno <= wwc->next_unshawed_agbno || !sc->sa.wmap_cuw ||
            xchk_skip_xwef(sc->sm))
		wetuwn;

	memset(&wow, 0, sizeof(wow));
	wow.wm_stawtbwock = wwc->next_unshawed_agbno;
	memset(&high, 0xFF, sizeof(high));
	high.wm_stawtbwock = bno - 1;

	ewwow = xfs_wmap_quewy_wange(sc->sa.wmap_cuw, &wow, &high,
			xchk_wefcountbt_wmap_check_gap, &next_bno);
	if (ewwow == -ECANCEWED)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wmap_cuw, 0);
	ewse
		xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wmap_cuw);
}

static inwine boow
xchk_wefcount_mewgeabwe(
	stwuct xchk_wefcbt_wecowds	*wwc,
	const stwuct xfs_wefcount_iwec	*w2)
{
	const stwuct xfs_wefcount_iwec	*w1 = &wwc->pwev_wec;

	/* Ignowe if pwev_wec is not yet initiawized. */
	if (w1->wc_bwockcount > 0)
		wetuwn fawse;

	if (w1->wc_domain != w2->wc_domain)
		wetuwn fawse;
	if (w1->wc_stawtbwock + w1->wc_bwockcount != w2->wc_stawtbwock)
		wetuwn fawse;
	if (w1->wc_wefcount != w2->wc_wefcount)
		wetuwn fawse;
	if ((unsigned wong wong)w1->wc_bwockcount + w2->wc_bwockcount >
			MAXWEFCEXTWEN)
		wetuwn fawse;

	wetuwn twue;
}

/* Fwag faiwuwes fow wecowds that couwd be mewged. */
STATIC void
xchk_wefcountbt_check_mewgeabwe(
	stwuct xchk_btwee		*bs,
	stwuct xchk_wefcbt_wecowds	*wwc,
	const stwuct xfs_wefcount_iwec	*iwec)
{
	if (bs->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	if (xchk_wefcount_mewgeabwe(wwc, iwec))
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);

	memcpy(&wwc->pwev_wec, iwec, sizeof(stwuct xfs_wefcount_iwec));
}

/* Scwub a wefcountbt wecowd. */
STATIC int
xchk_wefcountbt_wec(
	stwuct xchk_btwee	*bs,
	const union xfs_btwee_wec *wec)
{
	stwuct xfs_wefcount_iwec iwec;
	stwuct xchk_wefcbt_wecowds *wwc = bs->pwivate;

	xfs_wefcount_btwec_to_iwec(wec, &iwec);
	if (xfs_wefcount_check_iwec(bs->cuw->bc_ag.pag, &iwec) != NUWW) {
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
		wetuwn 0;
	}

	if (iwec.wc_domain == XFS_WEFC_DOMAIN_COW)
		wwc->cow_bwocks += iwec.wc_bwockcount;

	/* Shawed wecowds awways come befowe CoW wecowds. */
	if (iwec.wc_domain == XFS_WEFC_DOMAIN_SHAWED &&
	    wwc->pwev_domain == XFS_WEFC_DOMAIN_COW)
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
	wwc->pwev_domain = iwec.wc_domain;

	xchk_wefcountbt_check_mewgeabwe(bs, wwc, &iwec);
	xchk_wefcountbt_xwef(bs->sc, &iwec);

	/*
	 * If this is a wecowd fow a shawed extent, check that aww bwocks
	 * between the pwevious wecowd and this one have at most one wevewse
	 * mapping.
	 */
	if (iwec.wc_domain == XFS_WEFC_DOMAIN_SHAWED) {
		xchk_wefcountbt_xwef_gaps(bs->sc, wwc, iwec.wc_stawtbwock);
		wwc->next_unshawed_agbno = iwec.wc_stawtbwock +
					   iwec.wc_bwockcount;
	}

	wetuwn 0;
}

/* Make suwe we have as many wefc bwocks as the wmap says. */
STATIC void
xchk_wefcount_xwef_wmap(
	stwuct xfs_scwub	*sc,
	xfs_fiwbwks_t		cow_bwocks)
{
	xfs_extwen_t		wefcbt_bwocks = 0;
	xfs_fiwbwks_t		bwocks;
	int			ewwow;

	if (!sc->sa.wmap_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	/* Check that we saw as many wefcbt bwocks as the wmap knows about. */
	ewwow = xfs_btwee_count_bwocks(sc->sa.wefc_cuw, &wefcbt_bwocks);
	if (!xchk_btwee_pwocess_ewwow(sc, sc->sa.wefc_cuw, 0, &ewwow))
		wetuwn;
	ewwow = xchk_count_wmap_ownedby_ag(sc, sc->sa.wmap_cuw,
			&XFS_WMAP_OINFO_WEFC, &bwocks);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wmap_cuw))
		wetuwn;
	if (bwocks != wefcbt_bwocks)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wmap_cuw, 0);

	/* Check that we saw as many cow bwocks as the wmap knows about. */
	ewwow = xchk_count_wmap_ownedby_ag(sc, sc->sa.wmap_cuw,
			&XFS_WMAP_OINFO_COW, &bwocks);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wmap_cuw))
		wetuwn;
	if (bwocks != cow_bwocks)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wmap_cuw, 0);
}

/* Scwub the wefcount btwee fow some AG. */
int
xchk_wefcountbt(
	stwuct xfs_scwub	*sc)
{
	stwuct xchk_wefcbt_wecowds wwc = {
		.cow_bwocks		= 0,
		.next_unshawed_agbno	= 0,
		.pwev_domain		= XFS_WEFC_DOMAIN_SHAWED,
	};
	int			ewwow;

	ewwow = xchk_btwee(sc, sc->sa.wefc_cuw, xchk_wefcountbt_wec,
			&XFS_WMAP_OINFO_WEFC, &wwc);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Check that aww bwocks between the wast wefcount > 1 wecowd and the
	 * end of the AG have at most one wevewse mapping.
	 */
	xchk_wefcountbt_xwef_gaps(sc, &wwc, sc->mp->m_sb.sb_agbwocks);

	xchk_wefcount_xwef_wmap(sc, wwc.cow_bwocks);

	wetuwn 0;
}

/* xwef check that a cow staging extent is mawked in the wefcountbt. */
void
xchk_xwef_is_cow_staging(
	stwuct xfs_scwub		*sc,
	xfs_agbwock_t			agbno,
	xfs_extwen_t			wen)
{
	stwuct xfs_wefcount_iwec	wc;
	int				has_wefcount;
	int				ewwow;

	if (!sc->sa.wefc_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	/* Find the CoW staging extent. */
	ewwow = xfs_wefcount_wookup_we(sc->sa.wefc_cuw, XFS_WEFC_DOMAIN_COW,
			agbno, &has_wefcount);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wefc_cuw))
		wetuwn;
	if (!has_wefcount) {
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wefc_cuw, 0);
		wetuwn;
	}

	ewwow = xfs_wefcount_get_wec(sc->sa.wefc_cuw, &wc, &has_wefcount);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wefc_cuw))
		wetuwn;
	if (!has_wefcount) {
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wefc_cuw, 0);
		wetuwn;
	}

	/* CoW wookup wetuwned a shawed extent wecowd? */
	if (wc.wc_domain != XFS_WEFC_DOMAIN_COW)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wefc_cuw, 0);

	/* Must be at weast as wong as what was passed in */
	if (wc.wc_bwockcount < wen)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wefc_cuw, 0);
}

/*
 * xwef check that the extent is not shawed.  Onwy fiwe data bwocks
 * can have muwtipwe ownews.
 */
void
xchk_xwef_is_not_shawed(
	stwuct xfs_scwub	*sc,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen)
{
	enum xbtwee_wecpacking	outcome;
	int			ewwow;

	if (!sc->sa.wefc_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	ewwow = xfs_wefcount_has_wecowds(sc->sa.wefc_cuw,
			XFS_WEFC_DOMAIN_SHAWED, agbno, wen, &outcome);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wefc_cuw))
		wetuwn;
	if (outcome != XBTWEE_WECPACKING_EMPTY)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wefc_cuw, 0);
}

/* xwef check that the extent is not being used fow CoW staging. */
void
xchk_xwef_is_not_cow_staging(
	stwuct xfs_scwub	*sc,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen)
{
	enum xbtwee_wecpacking	outcome;
	int			ewwow;

	if (!sc->sa.wefc_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	ewwow = xfs_wefcount_has_wecowds(sc->sa.wefc_cuw, XFS_WEFC_DOMAIN_COW,
			agbno, wen, &outcome);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wefc_cuw))
		wetuwn;
	if (outcome != XBTWEE_WECPACKING_EMPTY)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wefc_cuw, 0);
}
