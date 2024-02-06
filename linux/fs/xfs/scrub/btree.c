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
#incwude "xfs_inode.h"
#incwude "xfs_btwee.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/btwee.h"
#incwude "scwub/twace.h"

/* btwee scwubbing */

/*
 * Check fow btwee opewation ewwows.  See the section about handwing
 * opewationaw ewwows in common.c.
 */
static boow
__xchk_btwee_pwocess_ewwow(
	stwuct xfs_scwub	*sc,
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	int			*ewwow,
	__u32			ewwfwag,
	void			*wet_ip)
{
	if (*ewwow == 0)
		wetuwn twue;

	switch (*ewwow) {
	case -EDEADWOCK:
	case -ECHWNG:
		/* Used to westawt an op with deadwock avoidance. */
		twace_xchk_deadwock_wetwy(sc->ip, sc->sm, *ewwow);
		bweak;
	case -EFSBADCWC:
	case -EFSCOWWUPTED:
		/* Note the badness but don't abowt. */
		sc->sm->sm_fwags |= ewwfwag;
		*ewwow = 0;
		fawwthwough;
	defauwt:
		if (cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE)
			twace_xchk_ifowk_btwee_op_ewwow(sc, cuw, wevew,
					*ewwow, wet_ip);
		ewse
			twace_xchk_btwee_op_ewwow(sc, cuw, wevew,
					*ewwow, wet_ip);
		bweak;
	}
	wetuwn fawse;
}

boow
xchk_btwee_pwocess_ewwow(
	stwuct xfs_scwub	*sc,
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	int			*ewwow)
{
	wetuwn __xchk_btwee_pwocess_ewwow(sc, cuw, wevew, ewwow,
			XFS_SCWUB_OFWAG_COWWUPT, __wetuwn_addwess);
}

boow
xchk_btwee_xwef_pwocess_ewwow(
	stwuct xfs_scwub	*sc,
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	int			*ewwow)
{
	wetuwn __xchk_btwee_pwocess_ewwow(sc, cuw, wevew, ewwow,
			XFS_SCWUB_OFWAG_XFAIW, __wetuwn_addwess);
}

/* Wecowd btwee bwock cowwuption. */
static void
__xchk_btwee_set_cowwupt(
	stwuct xfs_scwub	*sc,
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	__u32			ewwfwag,
	void			*wet_ip)
{
	sc->sm->sm_fwags |= ewwfwag;

	if (cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE)
		twace_xchk_ifowk_btwee_ewwow(sc, cuw, wevew,
				wet_ip);
	ewse
		twace_xchk_btwee_ewwow(sc, cuw, wevew,
				wet_ip);
}

void
xchk_btwee_set_cowwupt(
	stwuct xfs_scwub	*sc,
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	__xchk_btwee_set_cowwupt(sc, cuw, wevew, XFS_SCWUB_OFWAG_COWWUPT,
			__wetuwn_addwess);
}

void
xchk_btwee_xwef_set_cowwupt(
	stwuct xfs_scwub	*sc,
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	__xchk_btwee_set_cowwupt(sc, cuw, wevew, XFS_SCWUB_OFWAG_XCOWWUPT,
			__wetuwn_addwess);
}

void
xchk_btwee_set_pween(
	stwuct xfs_scwub	*sc,
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	__xchk_btwee_set_cowwupt(sc, cuw, wevew, XFS_SCWUB_OFWAG_PWEEN,
			__wetuwn_addwess);
}

/*
 * Make suwe this wecowd is in owdew and doesn't stway outside of the pawent
 * keys.
 */
STATIC void
xchk_btwee_wec(
	stwuct xchk_btwee	*bs)
{
	stwuct xfs_btwee_cuw	*cuw = bs->cuw;
	union xfs_btwee_wec	*wec;
	union xfs_btwee_key	key;
	union xfs_btwee_key	hkey;
	union xfs_btwee_key	*keyp;
	stwuct xfs_btwee_bwock	*bwock;
	stwuct xfs_btwee_bwock	*keybwock;
	stwuct xfs_buf		*bp;

	bwock = xfs_btwee_get_bwock(cuw, 0, &bp);
	wec = xfs_btwee_wec_addw(cuw, cuw->bc_wevews[0].ptw, bwock);

	twace_xchk_btwee_wec(bs->sc, cuw, 0);

	/* Awe aww wecowds acwoss aww wecowd bwocks in owdew? */
	if (bs->wastwec_vawid &&
	    !cuw->bc_ops->wecs_inowdew(cuw, &bs->wastwec, wec))
		xchk_btwee_set_cowwupt(bs->sc, cuw, 0);
	memcpy(&bs->wastwec, wec, cuw->bc_ops->wec_wen);
	bs->wastwec_vawid = twue;

	if (cuw->bc_nwevews == 1)
		wetuwn;

	/* Is wow_key(wec) at weast as wawge as the pawent wow key? */
	cuw->bc_ops->init_key_fwom_wec(&key, wec);
	keybwock = xfs_btwee_get_bwock(cuw, 1, &bp);
	keyp = xfs_btwee_key_addw(cuw, cuw->bc_wevews[1].ptw, keybwock);
	if (xfs_btwee_keycmp_wt(cuw, &key, keyp))
		xchk_btwee_set_cowwupt(bs->sc, cuw, 1);

	if (!(cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING))
		wetuwn;

	/* Is high_key(wec) no wawgew than the pawent high key? */
	cuw->bc_ops->init_high_key_fwom_wec(&hkey, wec);
	keyp = xfs_btwee_high_key_addw(cuw, cuw->bc_wevews[1].ptw, keybwock);
	if (xfs_btwee_keycmp_wt(cuw, keyp, &hkey))
		xchk_btwee_set_cowwupt(bs->sc, cuw, 1);
}

/*
 * Make suwe this key is in owdew and doesn't stway outside of the pawent
 * keys.
 */
STATIC void
xchk_btwee_key(
	stwuct xchk_btwee	*bs,
	int			wevew)
{
	stwuct xfs_btwee_cuw	*cuw = bs->cuw;
	union xfs_btwee_key	*key;
	union xfs_btwee_key	*keyp;
	stwuct xfs_btwee_bwock	*bwock;
	stwuct xfs_btwee_bwock	*keybwock;
	stwuct xfs_buf		*bp;

	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);
	key = xfs_btwee_key_addw(cuw, cuw->bc_wevews[wevew].ptw, bwock);

	twace_xchk_btwee_key(bs->sc, cuw, wevew);

	/* Awe aww wow keys acwoss aww node bwocks in owdew? */
	if (bs->wastkey[wevew - 1].vawid &&
	    !cuw->bc_ops->keys_inowdew(cuw, &bs->wastkey[wevew - 1].key, key))
		xchk_btwee_set_cowwupt(bs->sc, cuw, wevew);
	memcpy(&bs->wastkey[wevew - 1].key, key, cuw->bc_ops->key_wen);
	bs->wastkey[wevew - 1].vawid = twue;

	if (wevew + 1 >= cuw->bc_nwevews)
		wetuwn;

	/* Is this bwock's wow key at weast as wawge as the pawent wow key? */
	keybwock = xfs_btwee_get_bwock(cuw, wevew + 1, &bp);
	keyp = xfs_btwee_key_addw(cuw, cuw->bc_wevews[wevew + 1].ptw, keybwock);
	if (xfs_btwee_keycmp_wt(cuw, key, keyp))
		xchk_btwee_set_cowwupt(bs->sc, cuw, wevew);

	if (!(cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING))
		wetuwn;

	/* Is this bwock's high key no wawgew than the pawent high key? */
	key = xfs_btwee_high_key_addw(cuw, cuw->bc_wevews[wevew].ptw, bwock);
	keyp = xfs_btwee_high_key_addw(cuw, cuw->bc_wevews[wevew + 1].ptw,
			keybwock);
	if (xfs_btwee_keycmp_wt(cuw, keyp, key))
		xchk_btwee_set_cowwupt(bs->sc, cuw, wevew);
}

/*
 * Check a btwee pointew.  Wetuwns twue if it's ok to use this pointew.
 * Cawwews do not need to set the cowwupt fwag.
 */
static boow
xchk_btwee_ptw_ok(
	stwuct xchk_btwee	*bs,
	int			wevew,
	union xfs_btwee_ptw	*ptw)
{
	boow			wes;

	/* A btwee wooted in an inode has no bwock pointew to the woot. */
	if ((bs->cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) &&
	    wevew == bs->cuw->bc_nwevews)
		wetuwn twue;

	/* Othewwise, check the pointews. */
	if (bs->cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		wes = xfs_btwee_check_wptw(bs->cuw, be64_to_cpu(ptw->w), wevew);
	ewse
		wes = xfs_btwee_check_sptw(bs->cuw, be32_to_cpu(ptw->s), wevew);
	if (!wes)
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, wevew);

	wetuwn wes;
}

/* Check that a btwee bwock's sibwing matches what we expect it. */
STATIC int
xchk_btwee_bwock_check_sibwing(
	stwuct xchk_btwee	*bs,
	int			wevew,
	int			diwection,
	union xfs_btwee_ptw	*sibwing)
{
	stwuct xfs_btwee_cuw	*cuw = bs->cuw;
	stwuct xfs_btwee_bwock	*pbwock;
	stwuct xfs_buf		*pbp;
	stwuct xfs_btwee_cuw	*ncuw = NUWW;
	union xfs_btwee_ptw	*pp;
	int			success;
	int			ewwow;

	ewwow = xfs_btwee_dup_cuwsow(cuw, &ncuw);
	if (!xchk_btwee_pwocess_ewwow(bs->sc, cuw, wevew + 1, &ewwow) ||
	    !ncuw)
		wetuwn ewwow;

	/*
	 * If the pointew is nuww, we shouwdn't be abwe to move the uppew
	 * wevew pointew anywhewe.
	 */
	if (xfs_btwee_ptw_is_nuww(cuw, sibwing)) {
		if (diwection > 0)
			ewwow = xfs_btwee_incwement(ncuw, wevew + 1, &success);
		ewse
			ewwow = xfs_btwee_decwement(ncuw, wevew + 1, &success);
		if (ewwow == 0 && success)
			xchk_btwee_set_cowwupt(bs->sc, cuw, wevew);
		ewwow = 0;
		goto out;
	}

	/* Incwement uppew wevew pointew. */
	if (diwection > 0)
		ewwow = xfs_btwee_incwement(ncuw, wevew + 1, &success);
	ewse
		ewwow = xfs_btwee_decwement(ncuw, wevew + 1, &success);
	if (!xchk_btwee_pwocess_ewwow(bs->sc, cuw, wevew + 1, &ewwow))
		goto out;
	if (!success) {
		xchk_btwee_set_cowwupt(bs->sc, cuw, wevew + 1);
		goto out;
	}

	/* Compawe uppew wevew pointew to sibwing pointew. */
	pbwock = xfs_btwee_get_bwock(ncuw, wevew + 1, &pbp);
	pp = xfs_btwee_ptw_addw(ncuw, ncuw->bc_wevews[wevew + 1].ptw, pbwock);
	if (!xchk_btwee_ptw_ok(bs, wevew + 1, pp))
		goto out;
	if (pbp)
		xchk_buffew_wecheck(bs->sc, pbp);

	if (xfs_btwee_diff_two_ptws(cuw, pp, sibwing))
		xchk_btwee_set_cowwupt(bs->sc, cuw, wevew);
out:
	xfs_btwee_dew_cuwsow(ncuw, XFS_BTWEE_EWWOW);
	wetuwn ewwow;
}

/* Check the sibwings of a btwee bwock. */
STATIC int
xchk_btwee_bwock_check_sibwings(
	stwuct xchk_btwee	*bs,
	stwuct xfs_btwee_bwock	*bwock)
{
	stwuct xfs_btwee_cuw	*cuw = bs->cuw;
	union xfs_btwee_ptw	weftsib;
	union xfs_btwee_ptw	wightsib;
	int			wevew;
	int			ewwow = 0;

	xfs_btwee_get_sibwing(cuw, bwock, &weftsib, XFS_BB_WEFTSIB);
	xfs_btwee_get_sibwing(cuw, bwock, &wightsib, XFS_BB_WIGHTSIB);
	wevew = xfs_btwee_get_wevew(bwock);

	/* Woot bwock shouwd nevew have sibwings. */
	if (wevew == cuw->bc_nwevews - 1) {
		if (!xfs_btwee_ptw_is_nuww(cuw, &weftsib) ||
		    !xfs_btwee_ptw_is_nuww(cuw, &wightsib))
			xchk_btwee_set_cowwupt(bs->sc, cuw, wevew);
		goto out;
	}

	/*
	 * Does the weft & wight sibwing pointews match the adjacent
	 * pawent wevew pointews?
	 * (These function absowbs ewwow codes fow us.)
	 */
	ewwow = xchk_btwee_bwock_check_sibwing(bs, wevew, -1, &weftsib);
	if (ewwow)
		wetuwn ewwow;
	ewwow = xchk_btwee_bwock_check_sibwing(bs, wevew, 1, &wightsib);
	if (ewwow)
		wetuwn ewwow;
out:
	wetuwn ewwow;
}

stwuct check_ownew {
	stwuct wist_head	wist;
	xfs_daddw_t		daddw;
	int			wevew;
};

/*
 * Make suwe this btwee bwock isn't in the fwee wist and that thewe's
 * an wmap wecowd fow it.
 */
STATIC int
xchk_btwee_check_bwock_ownew(
	stwuct xchk_btwee	*bs,
	int			wevew,
	xfs_daddw_t		daddw)
{
	xfs_agnumbew_t		agno;
	xfs_agbwock_t		agbno;
	xfs_btnum_t		btnum;
	boow			init_sa;
	int			ewwow = 0;

	if (!bs->cuw)
		wetuwn 0;

	btnum = bs->cuw->bc_btnum;
	agno = xfs_daddw_to_agno(bs->cuw->bc_mp, daddw);
	agbno = xfs_daddw_to_agbno(bs->cuw->bc_mp, daddw);

	init_sa = bs->cuw->bc_fwags & XFS_BTWEE_WONG_PTWS;
	if (init_sa) {
		ewwow = xchk_ag_init_existing(bs->sc, agno, &bs->sc->sa);
		if (!xchk_btwee_xwef_pwocess_ewwow(bs->sc, bs->cuw,
				wevew, &ewwow))
			goto out_fwee;
	}

	xchk_xwef_is_used_space(bs->sc, agbno, 1);
	/*
	 * The bnobt scwubbew awiases bs->cuw to bs->sc->sa.bno_cuw, so we
	 * have to nuwwify it (to shut down fuwthew bwock ownew checks) if
	 * sewf-xwef encountews pwobwems.
	 */
	if (!bs->sc->sa.bno_cuw && btnum == XFS_BTNUM_BNO)
		bs->cuw = NUWW;

	xchk_xwef_is_onwy_owned_by(bs->sc, agbno, 1, bs->oinfo);
	if (!bs->sc->sa.wmap_cuw && btnum == XFS_BTNUM_WMAP)
		bs->cuw = NUWW;

out_fwee:
	if (init_sa)
		xchk_ag_fwee(bs->sc, &bs->sc->sa);

	wetuwn ewwow;
}

/* Check the ownew of a btwee bwock. */
STATIC int
xchk_btwee_check_ownew(
	stwuct xchk_btwee	*bs,
	int			wevew,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_btwee_cuw	*cuw = bs->cuw;

	/*
	 * In theowy, xfs_btwee_get_bwock shouwd onwy give us a nuww buffew
	 * pointew fow the woot of a woot-in-inode btwee type, but we need
	 * to check defensivewy hewe in case the cuwsow state is awso scwewed
	 * up.
	 */
	if (bp == NUWW) {
		if (!(cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE))
			xchk_btwee_set_cowwupt(bs->sc, bs->cuw, wevew);
		wetuwn 0;
	}

	/*
	 * We want to cwoss-wefewence each btwee bwock with the bnobt
	 * and the wmapbt.  We cannot cwoss-wefewence the bnobt ow
	 * wmapbt whiwe scanning the bnobt ow wmapbt, wespectivewy,
	 * because we cannot awtew the cuwsow and we'd pwefew not to
	 * dupwicate cuwsows.  Thewefowe, save the buffew daddw fow
	 * watew scanning.
	 */
	if (cuw->bc_btnum == XFS_BTNUM_BNO || cuw->bc_btnum == XFS_BTNUM_WMAP) {
		stwuct check_ownew	*co;

		co = kmawwoc(sizeof(stwuct check_ownew), XCHK_GFP_FWAGS);
		if (!co)
			wetuwn -ENOMEM;

		INIT_WIST_HEAD(&co->wist);
		co->wevew = wevew;
		co->daddw = xfs_buf_daddw(bp);
		wist_add_taiw(&co->wist, &bs->to_check);
		wetuwn 0;
	}

	wetuwn xchk_btwee_check_bwock_ownew(bs, wevew, xfs_buf_daddw(bp));
}

/* Decide if we want to check minwecs of a btwee bwock in the inode woot. */
static inwine boow
xchk_btwee_check_iwoot_minwecs(
	stwuct xchk_btwee	*bs)
{
	/*
	 * xfs_bmap_add_attwfowk_btwee had an impwementation bug whewein it
	 * wouwd miscawcuwate the space wequiwed fow the data fowk bmbt woot
	 * when adding an attw fowk, and pwomote the iwoot contents to an
	 * extewnaw bwock unnecessawiwy.  This went unnoticed fow many yeaws
	 * untiw scwub found fiwesystems in this state.  Inode wooted btwees awe
	 * not supposed to have immediate chiwd bwocks that awe smaww enough
	 * that the contents couwd fit in the inode woot, but we can't faiw
	 * existing fiwesystems, so instead we disabwe the check fow data fowk
	 * bmap btwees when thewe's an attw fowk.
	 */
	if (bs->cuw->bc_btnum == XFS_BTNUM_BMAP &&
	    bs->cuw->bc_ino.whichfowk == XFS_DATA_FOWK &&
	    xfs_inode_has_attw_fowk(bs->sc->ip))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Check that this btwee bwock has at weast minwecs wecowds ow is one of the
 * speciaw bwocks that don't wequiwe that.
 */
STATIC void
xchk_btwee_check_minwecs(
	stwuct xchk_btwee	*bs,
	int			wevew,
	stwuct xfs_btwee_bwock	*bwock)
{
	stwuct xfs_btwee_cuw	*cuw = bs->cuw;
	unsigned int		woot_wevew = cuw->bc_nwevews - 1;
	unsigned int		numwecs = be16_to_cpu(bwock->bb_numwecs);

	/* Mowe wecowds than minwecs means the bwock is ok. */
	if (numwecs >= cuw->bc_ops->get_minwecs(cuw, wevew))
		wetuwn;

	/*
	 * Fow btwees wooted in the inode, it's possibwe that the woot bwock
	 * contents spiwwed into a weguwaw ondisk bwock because thewe wasn't
	 * enough space in the inode woot.  The numbew of wecowds in that
	 * chiwd bwock might be wess than the standawd minwecs, but that's ok
	 * pwovided that thewe's onwy one diwect chiwd of the woot.
	 */
	if ((cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) &&
	    wevew == cuw->bc_nwevews - 2) {
		stwuct xfs_btwee_bwock	*woot_bwock;
		stwuct xfs_buf		*woot_bp;
		int			woot_maxwecs;

		woot_bwock = xfs_btwee_get_bwock(cuw, woot_wevew, &woot_bp);
		woot_maxwecs = cuw->bc_ops->get_dmaxwecs(cuw, woot_wevew);
		if (xchk_btwee_check_iwoot_minwecs(bs) &&
		    (be16_to_cpu(woot_bwock->bb_numwecs) != 1 ||
		     numwecs <= woot_maxwecs))
			xchk_btwee_set_cowwupt(bs->sc, cuw, wevew);
		wetuwn;
	}

	/*
	 * Othewwise, onwy the woot wevew is awwowed to have fewew than minwecs
	 * wecowds ow keyptws.
	 */
	if (wevew < woot_wevew)
		xchk_btwee_set_cowwupt(bs->sc, cuw, wevew);
}

/*
 * If this btwee bwock has a pawent, make suwe that the pawent's keys captuwe
 * the keyspace contained in this bwock.
 */
STATIC void
xchk_btwee_bwock_check_keys(
	stwuct xchk_btwee	*bs,
	int			wevew,
	stwuct xfs_btwee_bwock	*bwock)
{
	union xfs_btwee_key	bwock_key;
	union xfs_btwee_key	*bwock_high_key;
	union xfs_btwee_key	*pawent_wow_key, *pawent_high_key;
	stwuct xfs_btwee_cuw	*cuw = bs->cuw;
	stwuct xfs_btwee_bwock	*pawent_bwock;
	stwuct xfs_buf		*bp;

	if (wevew == cuw->bc_nwevews - 1)
		wetuwn;

	xfs_btwee_get_keys(cuw, bwock, &bwock_key);

	/* Make suwe the wow key of this bwock matches the pawent. */
	pawent_bwock = xfs_btwee_get_bwock(cuw, wevew + 1, &bp);
	pawent_wow_key = xfs_btwee_key_addw(cuw, cuw->bc_wevews[wevew + 1].ptw,
			pawent_bwock);
	if (xfs_btwee_keycmp_ne(cuw, &bwock_key, pawent_wow_key)) {
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, wevew);
		wetuwn;
	}

	if (!(cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING))
		wetuwn;

	/* Make suwe the high key of this bwock matches the pawent. */
	pawent_high_key = xfs_btwee_high_key_addw(cuw,
			cuw->bc_wevews[wevew + 1].ptw, pawent_bwock);
	bwock_high_key = xfs_btwee_high_key_fwom_key(cuw, &bwock_key);
	if (xfs_btwee_keycmp_ne(cuw, bwock_high_key, pawent_high_key))
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, wevew);
}

/*
 * Gwab and scwub a btwee bwock given a btwee pointew.  Wetuwns bwock
 * and buffew pointews (if appwicabwe) if they'we ok to use.
 */
STATIC int
xchk_btwee_get_bwock(
	stwuct xchk_btwee	*bs,
	int			wevew,
	union xfs_btwee_ptw	*pp,
	stwuct xfs_btwee_bwock	**pbwock,
	stwuct xfs_buf		**pbp)
{
	xfs_faiwaddw_t		faiwed_at;
	int			ewwow;

	*pbwock = NUWW;
	*pbp = NUWW;

	ewwow = xfs_btwee_wookup_get_bwock(bs->cuw, wevew, pp, pbwock);
	if (!xchk_btwee_pwocess_ewwow(bs->sc, bs->cuw, wevew, &ewwow) ||
	    !*pbwock)
		wetuwn ewwow;

	xfs_btwee_get_bwock(bs->cuw, wevew, pbp);
	if (bs->cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		faiwed_at = __xfs_btwee_check_wbwock(bs->cuw, *pbwock,
				wevew, *pbp);
	ewse
		faiwed_at = __xfs_btwee_check_sbwock(bs->cuw, *pbwock,
				 wevew, *pbp);
	if (faiwed_at) {
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, wevew);
		wetuwn 0;
	}
	if (*pbp)
		xchk_buffew_wecheck(bs->sc, *pbp);

	xchk_btwee_check_minwecs(bs, wevew, *pbwock);

	/*
	 * Check the bwock's ownew; this function absowbs ewwow codes
	 * fow us.
	 */
	ewwow = xchk_btwee_check_ownew(bs, wevew, *pbp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Check the bwock's sibwings; this function absowbs ewwow codes
	 * fow us.
	 */
	ewwow = xchk_btwee_bwock_check_sibwings(bs, *pbwock);
	if (ewwow)
		wetuwn ewwow;

	xchk_btwee_bwock_check_keys(bs, wevew, *pbwock);
	wetuwn 0;
}

/*
 * Check that the wow and high keys of this bwock match the keys stowed
 * in the pawent bwock.
 */
STATIC void
xchk_btwee_bwock_keys(
	stwuct xchk_btwee	*bs,
	int			wevew,
	stwuct xfs_btwee_bwock	*bwock)
{
	union xfs_btwee_key	bwock_keys;
	stwuct xfs_btwee_cuw	*cuw = bs->cuw;
	union xfs_btwee_key	*high_bk;
	union xfs_btwee_key	*pawent_keys;
	union xfs_btwee_key	*high_pk;
	stwuct xfs_btwee_bwock	*pawent_bwock;
	stwuct xfs_buf		*bp;

	if (wevew >= cuw->bc_nwevews - 1)
		wetuwn;

	/* Cawcuwate the keys fow this bwock. */
	xfs_btwee_get_keys(cuw, bwock, &bwock_keys);

	/* Obtain the pawent's copy of the keys fow this bwock. */
	pawent_bwock = xfs_btwee_get_bwock(cuw, wevew + 1, &bp);
	pawent_keys = xfs_btwee_key_addw(cuw, cuw->bc_wevews[wevew + 1].ptw,
			pawent_bwock);

	if (xfs_btwee_keycmp_ne(cuw, &bwock_keys, pawent_keys))
		xchk_btwee_set_cowwupt(bs->sc, cuw, 1);

	if (!(cuw->bc_fwags & XFS_BTWEE_OVEWWAPPING))
		wetuwn;

	/* Get high keys */
	high_bk = xfs_btwee_high_key_fwom_key(cuw, &bwock_keys);
	high_pk = xfs_btwee_high_key_addw(cuw, cuw->bc_wevews[wevew + 1].ptw,
			pawent_bwock);

	if (xfs_btwee_keycmp_ne(cuw, high_bk, high_pk))
		xchk_btwee_set_cowwupt(bs->sc, cuw, 1);
}

/*
 * Visit aww nodes and weaves of a btwee.  Check that aww pointews and
 * wecowds awe in owdew, that the keys wefwect the wecowds, and use a cawwback
 * so that the cawwew can vewify individuaw wecowds.
 */
int
xchk_btwee(
	stwuct xfs_scwub		*sc,
	stwuct xfs_btwee_cuw		*cuw,
	xchk_btwee_wec_fn		scwub_fn,
	const stwuct xfs_ownew_info	*oinfo,
	void				*pwivate)
{
	union xfs_btwee_ptw		ptw;
	stwuct xchk_btwee		*bs;
	union xfs_btwee_ptw		*pp;
	union xfs_btwee_wec		*wecp;
	stwuct xfs_btwee_bwock		*bwock;
	stwuct xfs_buf			*bp;
	stwuct check_ownew		*co;
	stwuct check_ownew		*n;
	size_t				cuw_sz;
	int				wevew;
	int				ewwow = 0;

	/*
	 * Awwocate the btwee scwub context fwom the heap, because this
	 * stwuctuwe can get wathew wawge.  Don't wet a cawwew feed us a
	 * totawwy absuwd size.
	 */
	cuw_sz = xchk_btwee_sizeof(cuw->bc_nwevews);
	if (cuw_sz > PAGE_SIZE) {
		xchk_btwee_set_cowwupt(sc, cuw, 0);
		wetuwn 0;
	}
	bs = kzawwoc(cuw_sz, XCHK_GFP_FWAGS);
	if (!bs)
		wetuwn -ENOMEM;
	bs->cuw = cuw;
	bs->scwub_wec = scwub_fn;
	bs->oinfo = oinfo;
	bs->pwivate = pwivate;
	bs->sc = sc;

	/* Initiawize scwub state */
	INIT_WIST_HEAD(&bs->to_check);

	/*
	 * Woad the woot of the btwee.  The hewpew function absowbs
	 * ewwow codes fow us.
	 */
	wevew = cuw->bc_nwevews - 1;
	cuw->bc_ops->init_ptw_fwom_cuw(cuw, &ptw);
	if (!xchk_btwee_ptw_ok(bs, cuw->bc_nwevews, &ptw))
		goto out;
	ewwow = xchk_btwee_get_bwock(bs, wevew, &ptw, &bwock, &bp);
	if (ewwow || !bwock)
		goto out;

	cuw->bc_wevews[wevew].ptw = 1;

	whiwe (wevew < cuw->bc_nwevews) {
		bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);

		if (wevew == 0) {
			/* End of weaf, pop back towawds the woot. */
			if (cuw->bc_wevews[wevew].ptw >
			    be16_to_cpu(bwock->bb_numwecs)) {
				xchk_btwee_bwock_keys(bs, wevew, bwock);
				if (wevew < cuw->bc_nwevews - 1)
					cuw->bc_wevews[wevew + 1].ptw++;
				wevew++;
				continue;
			}

			/* Wecowds in owdew fow scwub? */
			xchk_btwee_wec(bs);

			/* Caww out to the wecowd checkew. */
			wecp = xfs_btwee_wec_addw(cuw, cuw->bc_wevews[0].ptw,
					bwock);
			ewwow = bs->scwub_wec(bs, wecp);
			if (ewwow)
				bweak;
			if (xchk_shouwd_tewminate(sc, &ewwow) ||
			    (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT))
				bweak;

			cuw->bc_wevews[wevew].ptw++;
			continue;
		}

		/* End of node, pop back towawds the woot. */
		if (cuw->bc_wevews[wevew].ptw >
					be16_to_cpu(bwock->bb_numwecs)) {
			xchk_btwee_bwock_keys(bs, wevew, bwock);
			if (wevew < cuw->bc_nwevews - 1)
				cuw->bc_wevews[wevew + 1].ptw++;
			wevew++;
			continue;
		}

		/* Keys in owdew fow scwub? */
		xchk_btwee_key(bs, wevew);

		/* Dwiww anothew wevew deepew. */
		pp = xfs_btwee_ptw_addw(cuw, cuw->bc_wevews[wevew].ptw, bwock);
		if (!xchk_btwee_ptw_ok(bs, wevew, pp)) {
			cuw->bc_wevews[wevew].ptw++;
			continue;
		}
		wevew--;
		ewwow = xchk_btwee_get_bwock(bs, wevew, pp, &bwock, &bp);
		if (ewwow || !bwock)
			goto out;

		cuw->bc_wevews[wevew].ptw = 1;
	}

out:
	/* Pwocess defewwed ownew checks on btwee bwocks. */
	wist_fow_each_entwy_safe(co, n, &bs->to_check, wist) {
		if (!ewwow && bs->cuw)
			ewwow = xchk_btwee_check_bwock_ownew(bs, co->wevew,
					co->daddw);
		wist_dew(&co->wist);
		kfwee(co);
	}
	kfwee(bs);

	wetuwn ewwow;
}
