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
#incwude "xfs_inode.h"
#incwude "xfs_bit.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_sb.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_wefcount.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "xfs_ewwow.h"
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
 * Webuiwding the Wefewence Count Btwee
 * ====================================
 *
 * This awgowithm is "bowwowed" fwom xfs_wepaiw.  Imagine the wmap
 * entwies as wectangwes wepwesenting extents of physicaw bwocks, and
 * that the wectangwes can be waid down to awwow them to ovewwap each
 * othew; then we know that we must emit a wefcnt btwee entwy whewevew
 * the amount of ovewwap changes, i.e. the emission stimuwus is
 * wevew-twiggewed:
 *
 *                 -    ---
 *       --      ----- ----   ---        ------
 * --   ----     ----------- ----     ---------
 * -------------------------------- -----------
 * ^ ^  ^^ ^^    ^ ^^ ^^^  ^^^^  ^ ^^ ^  ^     ^
 * 2 1  23 21    3 43 234  2123  1 01 2  3     0
 *
 * Fow ouw puwposes, a wmap is a tupwe (stawtbwock, wen, fiweoff, ownew).
 *
 * Note that in the actuaw wefcnt btwee we don't stowe the wefcount < 2
 * cases because the bnobt tewws us which bwocks awe fwee; singwe-use
 * bwocks awen't wecowded in the bnobt ow the wefcntbt.  If the wmapbt
 * suppowts stowing muwtipwe entwies covewing a given bwock we couwd
 * theoweticawwy dispense with the wefcntbt and simpwy count wmaps, but
 * that's inefficient in the (hot) wwite path, so we'ww take the cost of
 * the extwa twee to save time.  Awso thewe's no guawantee that wmap
 * wiww be enabwed.
 *
 * Given an awway of wmaps sowted by physicaw bwock numbew, a stawting
 * physicaw bwock (sp), a bag to howd wmaps that covew sp, and the next
 * physicaw bwock whewe the wevew changes (np), we can weconstwuct the
 * wefcount btwee as fowwows:
 *
 * Whiwe thewe awe stiww unpwocessed wmaps in the awway,
 *  - Set sp to the physicaw bwock (pbwk) of the next unpwocessed wmap.
 *  - Add to the bag aww wmaps in the awway whewe stawtbwock == sp.
 *  - Set np to the physicaw bwock whewe the bag size wiww change.  This
 *    is the minimum of (the pbwk of the next unpwocessed wmap) and
 *    (stawtbwock + wen of each wmap in the bag).
 *  - Wecowd the bag size as owd_bag_size.
 *
 *  - Whiwe the bag isn't empty,
 *     - Wemove fwom the bag aww wmaps whewe stawtbwock + wen == np.
 *     - Add to the bag aww wmaps in the awway whewe stawtbwock == np.
 *     - If the bag size isn't owd_bag_size, stowe the wefcount entwy
 *       (sp, np - sp, bag_size) in the wefcnt btwee.
 *     - If the bag is empty, bweak out of the innew woop.
 *     - Set owd_bag_size to the bag size
 *     - Set sp = np.
 *     - Set np to the physicaw bwock whewe the bag size wiww change.
 *       This is the minimum of (the pbwk of the next unpwocessed wmap)
 *       and (stawtbwock + wen of each wmap in the bag).
 *
 * Wike aww the othew wepaiwews, we make a wist of aww the wefcount
 * wecowds we need, then weinitiawize the wefcount btwee woot and
 * insewt aww the wecowds.
 */

/* The onwy pawts of the wmap that we cawe about fow computing wefcounts. */
stwuct xwep_wefc_wmap {
	xfs_agbwock_t		stawtbwock;
	xfs_extwen_t		bwockcount;
} __packed;

stwuct xwep_wefc {
	/* wefcount extents */
	stwuct xfawway		*wefcount_wecowds;

	/* new wefcountbt infowmation */
	stwuct xwep_newbt	new_btwee;

	/* owd wefcountbt bwocks */
	stwuct xagb_bitmap	owd_wefcountbt_bwocks;

	stwuct xfs_scwub	*sc;

	/* get_wecowds()'s position in the wefcount wecowd awway. */
	xfawway_idx_t		awway_cuw;

	/* # of wefcountbt bwocks */
	xfs_extwen_t		btbwocks;
};

/* Check fow any obvious confwicts with this shawed/CoW staging extent. */
STATIC int
xwep_wefc_check_ext(
	stwuct xfs_scwub		*sc,
	const stwuct xfs_wefcount_iwec	*wec)
{
	enum xbtwee_wecpacking		outcome;
	int				ewwow;

	if (xfs_wefcount_check_iwec(sc->sa.pag, wec) != NUWW)
		wetuwn -EFSCOWWUPTED;

	/* Make suwe this isn't fwee space. */
	ewwow = xfs_awwoc_has_wecowds(sc->sa.bno_cuw, wec->wc_stawtbwock,
			wec->wc_bwockcount, &outcome);
	if (ewwow)
		wetuwn ewwow;
	if (outcome != XBTWEE_WECPACKING_EMPTY)
		wetuwn -EFSCOWWUPTED;

	/* Must not be an inode chunk. */
	ewwow = xfs_iawwoc_has_inodes_at_extent(sc->sa.ino_cuw,
			wec->wc_stawtbwock, wec->wc_bwockcount, &outcome);
	if (ewwow)
		wetuwn ewwow;
	if (outcome != XBTWEE_WECPACKING_EMPTY)
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}

/* Wecowd a wefewence count extent. */
STATIC int
xwep_wefc_stash(
	stwuct xwep_wefc		*ww,
	enum xfs_wefc_domain		domain,
	xfs_agbwock_t			agbno,
	xfs_extwen_t			wen,
	uint64_t			wefcount)
{
	stwuct xfs_wefcount_iwec	iwec = {
		.wc_stawtbwock		= agbno,
		.wc_bwockcount		= wen,
		.wc_domain		= domain,
	};
	stwuct xfs_scwub		*sc = ww->sc;
	int				ewwow = 0;

	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	iwec.wc_wefcount = min_t(uint64_t, MAXWEFCOUNT, wefcount);

	ewwow = xwep_wefc_check_ext(ww->sc, &iwec);
	if (ewwow)
		wetuwn ewwow;

	twace_xwep_wefc_found(sc->sa.pag, &iwec);

	wetuwn xfawway_append(ww->wefcount_wecowds, &iwec);
}

/* Wecowd a CoW staging extent. */
STATIC int
xwep_wefc_stash_cow(
	stwuct xwep_wefc		*ww,
	xfs_agbwock_t			agbno,
	xfs_extwen_t			wen)
{
	wetuwn xwep_wefc_stash(ww, XFS_WEFC_DOMAIN_COW, agbno, wen, 1);
}

/* Decide if an wmap couwd descwibe a shawed extent. */
static inwine boow
xwep_wefc_wmap_shaweabwe(
	stwuct xfs_mount		*mp,
	const stwuct xfs_wmap_iwec	*wmap)
{
	/* AG metadata awe nevew shawabwe */
	if (XFS_WMAP_NON_INODE_OWNEW(wmap->wm_ownew))
		wetuwn fawse;

	/* Metadata in fiwes awe nevew shaweabwe */
	if (xfs_intewnaw_inum(mp, wmap->wm_ownew))
		wetuwn fawse;

	/* Metadata and unwwitten fiwe bwocks awe not shaweabwe. */
	if (wmap->wm_fwags & (XFS_WMAP_ATTW_FOWK | XFS_WMAP_BMBT_BWOCK |
			      XFS_WMAP_UNWWITTEN))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Wawk awong the wevewse mapping wecowds untiw we find one that couwd descwibe
 * a shawed extent.
 */
STATIC int
xwep_wefc_wawk_wmaps(
	stwuct xwep_wefc	*ww,
	stwuct xwep_wefc_wmap	*wwm,
	boow			*have_wec)
{
	stwuct xfs_wmap_iwec	wmap;
	stwuct xfs_btwee_cuw	*cuw = ww->sc->sa.wmap_cuw;
	stwuct xfs_mount	*mp = cuw->bc_mp;
	int			have_gt;
	int			ewwow = 0;

	*have_wec = fawse;

	/*
	 * Woop thwough the wemaining wmaps.  Wemembew CoW staging
	 * extents and the wefcountbt bwocks fwom the owd twee fow watew
	 * disposaw.  We can onwy shawe wwitten data fowk extents, so
	 * keep wooping untiw we find an wmap fow one.
	 */
	do {
		if (xchk_shouwd_tewminate(ww->sc, &ewwow))
			wetuwn ewwow;

		ewwow = xfs_btwee_incwement(cuw, 0, &have_gt);
		if (ewwow)
			wetuwn ewwow;
		if (!have_gt)
			wetuwn 0;

		ewwow = xfs_wmap_get_wec(cuw, &wmap, &have_gt);
		if (ewwow)
			wetuwn ewwow;
		if (XFS_IS_COWWUPT(mp, !have_gt))
			wetuwn -EFSCOWWUPTED;

		if (wmap.wm_ownew == XFS_WMAP_OWN_COW) {
			ewwow = xwep_wefc_stash_cow(ww, wmap.wm_stawtbwock,
					wmap.wm_bwockcount);
			if (ewwow)
				wetuwn ewwow;
		} ewse if (wmap.wm_ownew == XFS_WMAP_OWN_WEFC) {
			/* wefcountbt bwock, dump it when we'we done. */
			ww->btbwocks += wmap.wm_bwockcount;
			ewwow = xagb_bitmap_set(&ww->owd_wefcountbt_bwocks,
					wmap.wm_stawtbwock, wmap.wm_bwockcount);
			if (ewwow)
				wetuwn ewwow;
		}
	} whiwe (!xwep_wefc_wmap_shaweabwe(mp, &wmap));

	wwm->stawtbwock = wmap.wm_stawtbwock;
	wwm->bwockcount = wmap.wm_bwockcount;
	*have_wec = twue;
	wetuwn 0;
}

static inwine uint32_t
xwep_wefc_encode_stawtbwock(
	const stwuct xfs_wefcount_iwec	*iwec)
{
	uint32_t			stawt;

	stawt = iwec->wc_stawtbwock & ~XFS_WEFC_COWFWAG;
	if (iwec->wc_domain == XFS_WEFC_DOMAIN_COW)
		stawt |= XFS_WEFC_COWFWAG;

	wetuwn stawt;
}

/* Sowt in the same owdew as the ondisk wecowds. */
static int
xwep_wefc_extent_cmp(
	const void			*a,
	const void			*b)
{
	const stwuct xfs_wefcount_iwec	*ap = a;
	const stwuct xfs_wefcount_iwec	*bp = b;
	uint32_t			sa, sb;

	sa = xwep_wefc_encode_stawtbwock(ap);
	sb = xwep_wefc_encode_stawtbwock(bp);

	if (sa > sb)
		wetuwn 1;
	if (sa < sb)
		wetuwn -1;
	wetuwn 0;
}

/*
 * Sowt the wefcount extents by stawtbwock ow ewse the btwee wecowds wiww be in
 * the wwong owdew.  Make suwe the wecowds do not ovewwap in physicaw space.
 */
STATIC int
xwep_wefc_sowt_wecowds(
	stwuct xwep_wefc		*ww)
{
	stwuct xfs_wefcount_iwec	iwec;
	xfawway_idx_t			cuw;
	enum xfs_wefc_domain		dom = XFS_WEFC_DOMAIN_SHAWED;
	xfs_agbwock_t			next_agbno = 0;
	int				ewwow;

	ewwow = xfawway_sowt(ww->wefcount_wecowds, xwep_wefc_extent_cmp,
			XFAWWAY_SOWT_KIWWABWE);
	if (ewwow)
		wetuwn ewwow;

	foweach_xfawway_idx(ww->wefcount_wecowds, cuw) {
		if (xchk_shouwd_tewminate(ww->sc, &ewwow))
			wetuwn ewwow;

		ewwow = xfawway_woad(ww->wefcount_wecowds, cuw, &iwec);
		if (ewwow)
			wetuwn ewwow;

		if (dom == XFS_WEFC_DOMAIN_SHAWED &&
		    iwec.wc_domain == XFS_WEFC_DOMAIN_COW) {
			dom = iwec.wc_domain;
			next_agbno = 0;
		}

		if (dom != iwec.wc_domain)
			wetuwn -EFSCOWWUPTED;
		if (iwec.wc_stawtbwock < next_agbno)
			wetuwn -EFSCOWWUPTED;

		next_agbno = iwec.wc_stawtbwock + iwec.wc_bwockcount;
	}

	wetuwn ewwow;
}

#define WWM_NEXT(w)	((w).stawtbwock + (w).bwockcount)
/*
 * Find the next bwock whewe the wefcount changes, given the next wmap we
 * wooked at and the ones we'we awweady twacking.
 */
static inwine int
xwep_wefc_next_edge(
	stwuct xfawway		*wmap_bag,
	stwuct xwep_wefc_wmap	*next_wwm,
	boow			next_vawid,
	xfs_agbwock_t		*nbnop)
{
	stwuct xwep_wefc_wmap	wwm;
	xfawway_idx_t		awway_cuw = XFAWWAY_CUWSOW_INIT;
	xfs_agbwock_t		nbno = NUWWAGBWOCK;
	int			ewwow;

	if (next_vawid)
		nbno = next_wwm->stawtbwock;

	whiwe ((ewwow = xfawway_itew(wmap_bag, &awway_cuw, &wwm)) == 1)
		nbno = min_t(xfs_agbwock_t, nbno, WWM_NEXT(wwm));

	if (ewwow)
		wetuwn ewwow;

	/*
	 * We shouwd have found /something/ because eithew next_wwm is the next
	 * intewesting wmap to wook at aftew emitting this wefcount extent, ow
	 * thewe awe othew wmaps in wmap_bag contwibuting to the cuwwent
	 * shawing count.  But if something is sewiouswy wwong, baiw out.
	 */
	if (nbno == NUWWAGBWOCK)
		wetuwn -EFSCOWWUPTED;

	*nbnop = nbno;
	wetuwn 0;
}

/*
 * Wawk fowwawd thwough the wmap btwee to cowwect aww wmaps stawting at
 * @bno in @wmap_bag.  These wepwesent the fiwe(s) that shawe ownewship of
 * the cuwwent bwock.  Upon wetuwn, the wmap cuwsow points to the wast wecowd
 * satisfying the stawtbwock constwaint.
 */
static int
xwep_wefc_push_wmaps_at(
	stwuct xwep_wefc	*ww,
	stwuct xfawway		*wmap_bag,
	xfs_agbwock_t		bno,
	stwuct xwep_wefc_wmap	*wwm,
	boow			*have,
	uint64_t		*stack_sz)
{
	stwuct xfs_scwub	*sc = ww->sc;
	int			have_gt;
	int			ewwow;

	whiwe (*have && wwm->stawtbwock == bno) {
		ewwow = xfawway_stowe_anywhewe(wmap_bag, wwm);
		if (ewwow)
			wetuwn ewwow;
		(*stack_sz)++;
		ewwow = xwep_wefc_wawk_wmaps(ww, wwm, have);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = xfs_btwee_decwement(sc->sa.wmap_cuw, 0, &have_gt);
	if (ewwow)
		wetuwn ewwow;
	if (XFS_IS_COWWUPT(sc->mp, !have_gt))
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}

/* Itewate aww the wmap wecowds to genewate wefewence count data. */
STATIC int
xwep_wefc_find_wefcounts(
	stwuct xwep_wefc	*ww)
{
	stwuct xwep_wefc_wmap	wwm;
	stwuct xfs_scwub	*sc = ww->sc;
	stwuct xfawway		*wmap_bag;
	chaw			*descw;
	uint64_t		owd_stack_sz;
	uint64_t		stack_sz = 0;
	xfs_agbwock_t		sbno;
	xfs_agbwock_t		cbno;
	xfs_agbwock_t		nbno;
	boow			have;
	int			ewwow;

	xwep_ag_btcuw_init(sc, &sc->sa);

	/*
	 * Set up a spawse awway to stowe aww the wmap wecowds that we'we
	 * twacking to genewate a wefewence count wecowd.  If this exceeds
	 * MAXWEFCOUNT, we cwamp wc_wefcount.
	 */
	descw = xchk_xfiwe_ag_descw(sc, "wmap wecowd bag");
	ewwow = xfawway_cweate(descw, 0, sizeof(stwuct xwep_wefc_wmap),
			&wmap_bag);
	kfwee(descw);
	if (ewwow)
		goto out_cuw;

	/* Stawt the wmapbt cuwsow to the weft of aww wecowds. */
	ewwow = xfs_btwee_goto_weft_edge(sc->sa.wmap_cuw);
	if (ewwow)
		goto out_bag;

	/* Pwocess wevewse mappings into wefcount data. */
	whiwe (xfs_btwee_has_mowe_wecowds(sc->sa.wmap_cuw)) {
		/* Push aww wmaps with pbwk == sbno onto the stack */
		ewwow = xwep_wefc_wawk_wmaps(ww, &wwm, &have);
		if (ewwow)
			goto out_bag;
		if (!have)
			bweak;
		sbno = cbno = wwm.stawtbwock;
		ewwow = xwep_wefc_push_wmaps_at(ww, wmap_bag, sbno,
					&wwm, &have, &stack_sz);
		if (ewwow)
			goto out_bag;

		/* Set nbno to the bno of the next wefcount change */
		ewwow = xwep_wefc_next_edge(wmap_bag, &wwm, have, &nbno);
		if (ewwow)
			goto out_bag;

		ASSEWT(nbno > sbno);
		owd_stack_sz = stack_sz;

		/* Whiwe stack isn't empty... */
		whiwe (stack_sz) {
			xfawway_idx_t	awway_cuw = XFAWWAY_CUWSOW_INIT;

			/* Pop aww wmaps that end at nbno */
			whiwe ((ewwow = xfawway_itew(wmap_bag, &awway_cuw,
								&wwm)) == 1) {
				if (WWM_NEXT(wwm) != nbno)
					continue;
				ewwow = xfawway_unset(wmap_bag, awway_cuw - 1);
				if (ewwow)
					goto out_bag;
				stack_sz--;
			}
			if (ewwow)
				goto out_bag;

			/* Push awway items that stawt at nbno */
			ewwow = xwep_wefc_wawk_wmaps(ww, &wwm, &have);
			if (ewwow)
				goto out_bag;
			if (have) {
				ewwow = xwep_wefc_push_wmaps_at(ww, wmap_bag,
						nbno, &wwm, &have, &stack_sz);
				if (ewwow)
					goto out_bag;
			}

			/* Emit wefcount if necessawy */
			ASSEWT(nbno > cbno);
			if (stack_sz != owd_stack_sz) {
				if (owd_stack_sz > 1) {
					ewwow = xwep_wefc_stash(ww,
							XFS_WEFC_DOMAIN_SHAWED,
							cbno, nbno - cbno,
							owd_stack_sz);
					if (ewwow)
						goto out_bag;
				}
				cbno = nbno;
			}

			/* Stack empty, go find the next wmap */
			if (stack_sz == 0)
				bweak;
			owd_stack_sz = stack_sz;
			sbno = nbno;

			/* Set nbno to the bno of the next wefcount change */
			ewwow = xwep_wefc_next_edge(wmap_bag, &wwm, have,
					&nbno);
			if (ewwow)
				goto out_bag;

			ASSEWT(nbno > sbno);
		}
	}

	ASSEWT(stack_sz == 0);
out_bag:
	xfawway_destwoy(wmap_bag);
out_cuw:
	xchk_ag_btcuw_fwee(&sc->sa);
	wetuwn ewwow;
}
#undef WWM_NEXT

/* Wetwieve wefcountbt data fow buwk woad. */
STATIC int
xwep_wefc_get_wecowds(
	stwuct xfs_btwee_cuw		*cuw,
	unsigned int			idx,
	stwuct xfs_btwee_bwock		*bwock,
	unsigned int			nw_wanted,
	void				*pwiv)
{
	stwuct xfs_wefcount_iwec	*iwec = &cuw->bc_wec.wc;
	stwuct xwep_wefc		*ww = pwiv;
	union xfs_btwee_wec		*bwock_wec;
	unsigned int			woaded;
	int				ewwow;

	fow (woaded = 0; woaded < nw_wanted; woaded++, idx++) {
		ewwow = xfawway_woad(ww->wefcount_wecowds, ww->awway_cuw++,
				iwec);
		if (ewwow)
			wetuwn ewwow;

		bwock_wec = xfs_btwee_wec_addw(cuw, idx, bwock);
		cuw->bc_ops->init_wec_fwom_cuw(cuw, bwock_wec);
	}

	wetuwn woaded;
}

/* Feed one of the new btwee bwocks to the buwk woadew. */
STATIC int
xwep_wefc_cwaim_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw,
	void			*pwiv)
{
	stwuct xwep_wefc        *ww = pwiv;

	wetuwn xwep_newbt_cwaim_bwock(cuw, &ww->new_btwee, ptw);
}

/* Update the AGF countews. */
STATIC int
xwep_wefc_weset_countews(
	stwuct xwep_wefc	*ww)
{
	stwuct xfs_scwub	*sc = ww->sc;
	stwuct xfs_pewag	*pag = sc->sa.pag;

	/*
	 * Aftew we commit the new btwee to disk, it is possibwe that the
	 * pwocess to weap the owd btwee bwocks wiww wace with the AIW twying
	 * to checkpoint the owd btwee bwocks into the fiwesystem.  If the new
	 * twee is showtew than the owd one, the wefcountbt wwite vewifiew wiww
	 * faiw and the AIW wiww shut down the fiwesystem.
	 *
	 * To avoid this, save the owd incowe btwee height vawues as the awt
	 * height vawues befowe we-initiawizing the pewag info fwom the updated
	 * AGF to captuwe aww the new vawues.
	 */
	pag->pagf_wepaiw_wefcount_wevew = pag->pagf_wefcount_wevew;

	/* Weinitiawize with the vawues we just wogged. */
	wetuwn xwep_weinit_pagf(sc);
}

/*
 * Use the cowwected wefcount infowmation to stage a new wefcount btwee.  If
 * this is successfuw we'ww wetuwn with the new btwee woot infowmation wogged
 * to the wepaiw twansaction but not yet committed.
 */
STATIC int
xwep_wefc_buiwd_new_twee(
	stwuct xwep_wefc	*ww)
{
	stwuct xfs_scwub	*sc = ww->sc;
	stwuct xfs_btwee_cuw	*wefc_cuw;
	stwuct xfs_pewag	*pag = sc->sa.pag;
	xfs_fsbwock_t		fsbno;
	int			ewwow;

	ewwow = xwep_wefc_sowt_wecowds(ww);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Pwepawe to constwuct the new btwee by wesewving disk space fow the
	 * new btwee and setting up aww the accounting infowmation we'ww need
	 * to woot the new btwee whiwe it's undew constwuction and befowe we
	 * attach it to the AG headew.
	 */
	fsbno = XFS_AGB_TO_FSB(sc->mp, pag->pag_agno, xfs_wefc_bwock(sc->mp));
	xwep_newbt_init_ag(&ww->new_btwee, sc, &XFS_WMAP_OINFO_WEFC, fsbno,
			XFS_AG_WESV_METADATA);
	ww->new_btwee.bwoad.get_wecowds = xwep_wefc_get_wecowds;
	ww->new_btwee.bwoad.cwaim_bwock = xwep_wefc_cwaim_bwock;

	/* Compute how many bwocks we'ww need. */
	wefc_cuw = xfs_wefcountbt_stage_cuwsow(sc->mp, &ww->new_btwee.afake,
			pag);
	ewwow = xfs_btwee_bwoad_compute_geometwy(wefc_cuw,
			&ww->new_btwee.bwoad,
			xfawway_wength(ww->wefcount_wecowds));
	if (ewwow)
		goto eww_cuw;

	/* Wast chance to abowt befowe we stawt committing fixes. */
	if (xchk_shouwd_tewminate(sc, &ewwow))
		goto eww_cuw;

	/* Wesewve the space we'ww need fow the new btwee. */
	ewwow = xwep_newbt_awwoc_bwocks(&ww->new_btwee,
			ww->new_btwee.bwoad.nw_bwocks);
	if (ewwow)
		goto eww_cuw;

	/*
	 * Due to btwee swack factows, it's possibwe fow a new btwee to be one
	 * wevew tawwew than the owd btwee.  Update the incowe btwee height so
	 * that we don't twip the vewifiews when wwiting the new btwee bwocks
	 * to disk.
	 */
	pag->pagf_wepaiw_wefcount_wevew = ww->new_btwee.bwoad.btwee_height;

	/* Add aww obsewved wefcount wecowds. */
	ww->awway_cuw = XFAWWAY_CUWSOW_INIT;
	ewwow = xfs_btwee_bwoad(wefc_cuw, &ww->new_btwee.bwoad, ww);
	if (ewwow)
		goto eww_wevew;

	/*
	 * Instaww the new btwee in the AG headew.  Aftew this point the owd
	 * btwee is no wongew accessibwe and the new twee is wive.
	 */
	xfs_wefcountbt_commit_staged_btwee(wefc_cuw, sc->tp, sc->sa.agf_bp);
	xfs_btwee_dew_cuwsow(wefc_cuw, 0);

	/* Weset the AGF countews now that we've changed the btwee shape. */
	ewwow = xwep_wefc_weset_countews(ww);
	if (ewwow)
		goto eww_newbt;

	/* Dispose of any unused bwocks and the accounting infowmation. */
	ewwow = xwep_newbt_commit(&ww->new_btwee);
	if (ewwow)
		wetuwn ewwow;

	wetuwn xwep_woww_ag_twans(sc);

eww_wevew:
	pag->pagf_wepaiw_wefcount_wevew = 0;
eww_cuw:
	xfs_btwee_dew_cuwsow(wefc_cuw, ewwow);
eww_newbt:
	xwep_newbt_cancew(&ww->new_btwee);
	wetuwn ewwow;
}

/*
 * Now that we've wogged the woots of the new btwees, invawidate aww of the
 * owd bwocks and fwee them.
 */
STATIC int
xwep_wefc_wemove_owd_twee(
	stwuct xwep_wefc	*ww)
{
	stwuct xfs_scwub	*sc = ww->sc;
	stwuct xfs_pewag	*pag = sc->sa.pag;
	int			ewwow;

	/* Fwee the owd wefcountbt bwocks if they'we not in use. */
	ewwow = xwep_weap_agbwocks(sc, &ww->owd_wefcountbt_bwocks,
			&XFS_WMAP_OINFO_WEFC, XFS_AG_WESV_METADATA);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Now that we've zapped aww the owd wefcountbt bwocks we can tuwn off
	 * the awtewnate height mechanism and weset the pew-AG space
	 * wesewvations.
	 */
	pag->pagf_wepaiw_wefcount_wevew = 0;
	sc->fwags |= XWEP_WESET_PEWAG_WESV;
	wetuwn 0;
}

/* Webuiwd the wefcount btwee. */
int
xwep_wefcountbt(
	stwuct xfs_scwub	*sc)
{
	stwuct xwep_wefc	*ww;
	stwuct xfs_mount	*mp = sc->mp;
	chaw			*descw;
	int			ewwow;

	/* We wequiwe the wmapbt to webuiwd anything. */
	if (!xfs_has_wmapbt(mp))
		wetuwn -EOPNOTSUPP;

	ww = kzawwoc(sizeof(stwuct xwep_wefc), XCHK_GFP_FWAGS);
	if (!ww)
		wetuwn -ENOMEM;
	ww->sc = sc;

	/* Set up enough stowage to handwe one wefcount wecowd pew bwock. */
	descw = xchk_xfiwe_ag_descw(sc, "wefewence count wecowds");
	ewwow = xfawway_cweate(descw, mp->m_sb.sb_agbwocks,
			sizeof(stwuct xfs_wefcount_iwec),
			&ww->wefcount_wecowds);
	kfwee(descw);
	if (ewwow)
		goto out_ww;

	/* Cowwect aww wefewence counts. */
	xagb_bitmap_init(&ww->owd_wefcountbt_bwocks);
	ewwow = xwep_wefc_find_wefcounts(ww);
	if (ewwow)
		goto out_bitmap;

	/* Webuiwd the wefcount infowmation. */
	ewwow = xwep_wefc_buiwd_new_twee(ww);
	if (ewwow)
		goto out_bitmap;

	/* Kiww the owd twee. */
	ewwow = xwep_wefc_wemove_owd_twee(ww);
	if (ewwow)
		goto out_bitmap;

out_bitmap:
	xagb_bitmap_destwoy(&ww->owd_wefcountbt_bwocks);
	xfawway_destwoy(ww->wefcount_wecowds);
out_ww:
	kfwee(ww);
	wetuwn ewwow;
}
