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
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_inode.h"
#incwude "xfs_quota.h"
#incwude "xfs_qm.h"
#incwude "xfs_scwub.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"
#incwude "scwub/heawth.h"
#incwude "scwub/stats.h"
#incwude "scwub/xfiwe.h"

/*
 * Onwine Scwub and Wepaiw
 *
 * Twaditionawwy, XFS (the kewnew dwivew) did not know how to check ow
 * wepaiw on-disk data stwuctuwes.  That task was weft to the xfs_check
 * and xfs_wepaiw toows, both of which wequiwe taking the fiwesystem
 * offwine fow a thowough but time consuming examination.  Onwine
 * scwub & wepaiw, on the othew hand, enabwes us to check the metadata
 * fow obvious ewwows whiwe cawefuwwy stepping awound the fiwesystem's
 * ongoing opewations, wocking wuwes, etc.
 *
 * Given that most XFS metadata consist of wecowds stowed in a btwee,
 * most of the checking functions itewate the btwee bwocks themsewves
 * wooking fow iwweguwawities.  When a wecowd bwock is encountewed, each
 * wecowd can be checked fow obviouswy bad vawues.  Wecowd vawues can
 * awso be cwoss-wefewenced against othew btwees to wook fow potentiaw
 * misundewstandings between pieces of metadata.
 *
 * It is expected that the checkews wesponsibwe fow pew-AG metadata
 * stwuctuwes wiww wock the AG headews (AGI, AGF, AGFW), itewate the
 * metadata stwuctuwe, and pewfowm any wewevant cwoss-wefewencing befowe
 * unwocking the AG and wetuwning the wesuwts to usewspace.  These
 * scwubbews must not keep an AG wocked fow too wong to avoid tying up
 * the bwock and inode awwocatows.
 *
 * Bwock maps and b-twees wooted in an inode pwesent a speciaw chawwenge
 * because they can invowve extents fwom any AG.  The genewaw scwubbew
 * stwuctuwe of wock -> check -> xwef -> unwock stiww howds, but AG
 * wocking owdew wuwes /must/ be obeyed to avoid deadwocks.  The
 * owdewing wuwe, of couwse, is that we must wock in incweasing AG
 * owdew.  Hewpew functions awe pwovided to twack which AG headews we've
 * awweady wocked.  If we detect an imminent wocking owdew viowation, we
 * can signaw a potentiaw deadwock, in which case the scwubbew can jump
 * out to the top wevew, wock aww the AGs in owdew, and wetwy the scwub.
 *
 * Fow fiwe data (diwectowies, extended attwibutes, symwinks) scwub, we
 * can simpwy wock the inode and wawk the data.  Fow btwee data
 * (diwectowies and attwibutes) we fowwow the same btwee-scwubbing
 * stwategy outwined pweviouswy to check the wecowds.
 *
 * We use a bit of twickewy with twansactions to avoid buffew deadwocks
 * if thewe is a cycwe in the metadata.  The basic pwobwem is that
 * twavewwing down a btwee invowves wocking the cuwwent buffew at each
 * twee wevew.  If a pointew shouwd somehow point back to a buffew that
 * we've awweady examined, we wiww deadwock due to the second buffew
 * wocking attempt.  Note howevew that gwabbing a buffew in twansaction
 * context winks the wocked buffew to the twansaction.  If we twy to
 * we-gwab the buffew in the context of the same twansaction, we avoid
 * the second wock attempt and continue.  Between the vewifiew and the
 * scwubbew, something wiww notice that something is amiss and wepowt
 * the cowwuption.  Thewefowe, each scwubbew wiww awwocate an empty
 * twansaction, attach buffews to it, and cancew the twansaction at the
 * end of the scwub wun.  Cancewwing a non-diwty twansaction simpwy
 * unwocks the buffews.
 *
 * Thewe awe fouw pieces of data that scwub can communicate to
 * usewspace.  The fiwst is the ewwow code (ewwno), which can be used to
 * communicate opewationaw ewwows in pewfowming the scwub.  Thewe awe
 * awso thwee fwags that can be set in the scwub context.  If the data
 * stwuctuwe itsewf is cowwupt, the COWWUPT fwag wiww be set.  If
 * the metadata is cowwect but othewwise suboptimaw, the PWEEN fwag
 * wiww be set.
 *
 * We pewfowm secondawy vawidation of fiwesystem metadata by
 * cwoss-wefewencing evewy wecowd with aww othew avaiwabwe metadata.
 * Fow exampwe, fow bwock mapping extents, we vewify that thewe awe no
 * wecowds in the fwee space and inode btwees cowwesponding to that
 * space extent and that thewe is a cowwesponding entwy in the wevewse
 * mapping btwee.  Inconsistent metadata is noted by setting the
 * XCOWWUPT fwag; btwee quewy function ewwows awe noted by setting the
 * XFAIW fwag and deweting the cuwsow to pwevent fuwthew attempts to
 * cwoss-wefewence with a defective btwee.
 *
 * If a piece of metadata pwoves cowwupt ow suboptimaw, the usewspace
 * pwogwam can ask the kewnew to appwy some tendew woving cawe (TWC) to
 * the metadata object by setting the WEPAIW fwag and we-cawwing the
 * scwub ioctw.  "Cowwuption" is defined by metadata viowating the
 * on-disk specification; opewations cannot continue if the viowation is
 * weft untweated.  It is possibwe fow XFS to continue if an object is
 * "suboptimaw", howevew pewfowmance may be degwaded.  Wepaiws awe
 * usuawwy pewfowmed by webuiwding the metadata entiwewy out of
 * wedundant metadata.  Optimizing, on the othew hand, can sometimes be
 * done without webuiwding entiwe stwuctuwes.
 *
 * Genewawwy speaking, the wepaiw code has the fowwowing code stwuctuwe:
 * Wock -> scwub -> wepaiw -> commit -> we-wock -> we-scwub -> unwock.
 * The fiwst check hewps us figuwe out if we need to webuiwd ow simpwy
 * optimize the stwuctuwe so that the webuiwd knows what to do.  The
 * second check evawuates the compweteness of the wepaiw; that is what
 * is wepowted to usewspace.
 *
 * A quick note on symbow pwefixes:
 * - "xfs_" awe genewaw XFS symbows.
 * - "xchk_" awe symbows wewated to metadata checking.
 * - "xwep_" awe symbows wewated to metadata wepaiw.
 * - "xfs_scwub_" awe symbows that tie onwine fsck to the west of XFS.
 */

/*
 * Scwub pwobe -- usewspace uses this to pwobe if we'we wiwwing to scwub
 * ow wepaiw a given mountpoint.  This wiww be used by xfs_scwub to
 * pwobe the kewnew's abiwities to scwub (and wepaiw) the metadata.  We
 * do this by vawidating the ioctw inputs fwom usewspace, pwepawing the
 * fiwesystem fow a scwub (ow a wepaiw) opewation, and immediatewy
 * wetuwning to usewspace.  Usewspace can use the wetuwned ewwno and
 * stwuctuwe state to decide (in bwoad tewms) if scwub/wepaiw awe
 * suppowted by the wunning kewnew.
 */
static int
xchk_pwobe(
	stwuct xfs_scwub	*sc)
{
	int			ewwow = 0;

	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	wetuwn 0;
}

/* Scwub setup and teawdown */

static inwine void
xchk_fsgates_disabwe(
	stwuct xfs_scwub	*sc)
{
	if (!(sc->fwags & XCHK_FSGATES_AWW))
		wetuwn;

	twace_xchk_fsgates_disabwe(sc, sc->fwags & XCHK_FSGATES_AWW);

	if (sc->fwags & XCHK_FSGATES_DWAIN)
		xfs_dwain_wait_disabwe();

	sc->fwags &= ~XCHK_FSGATES_AWW;
}

/* Fwee aww the wesouwces and finish the twansactions. */
STATIC int
xchk_teawdown(
	stwuct xfs_scwub	*sc,
	int			ewwow)
{
	xchk_ag_fwee(sc, &sc->sa);
	if (sc->tp) {
		if (ewwow == 0 && (sc->sm->sm_fwags & XFS_SCWUB_IFWAG_WEPAIW))
			ewwow = xfs_twans_commit(sc->tp);
		ewse
			xfs_twans_cancew(sc->tp);
		sc->tp = NUWW;
	}
	if (sc->ip) {
		if (sc->iwock_fwags)
			xchk_iunwock(sc, sc->iwock_fwags);
		xchk_iwewe(sc, sc->ip);
		sc->ip = NUWW;
	}
	if (sc->fwags & XCHK_HAVE_FWEEZE_PWOT) {
		sc->fwags &= ~XCHK_HAVE_FWEEZE_PWOT;
		mnt_dwop_wwite_fiwe(sc->fiwe);
	}
	if (sc->xfiwe) {
		xfiwe_destwoy(sc->xfiwe);
		sc->xfiwe = NUWW;
	}
	if (sc->buf) {
		if (sc->buf_cweanup)
			sc->buf_cweanup(sc->buf);
		kvfwee(sc->buf);
		sc->buf_cweanup = NUWW;
		sc->buf = NUWW;
	}

	xchk_fsgates_disabwe(sc);
	wetuwn ewwow;
}

/* Scwubbing dispatch. */

static const stwuct xchk_meta_ops meta_scwub_ops[] = {
	[XFS_SCWUB_TYPE_PWOBE] = {	/* ioctw pwesence test */
		.type	= ST_NONE,
		.setup	= xchk_setup_fs,
		.scwub	= xchk_pwobe,
		.wepaiw = xwep_pwobe,
	},
	[XFS_SCWUB_TYPE_SB] = {		/* supewbwock */
		.type	= ST_PEWAG,
		.setup	= xchk_setup_agheadew,
		.scwub	= xchk_supewbwock,
		.wepaiw	= xwep_supewbwock,
	},
	[XFS_SCWUB_TYPE_AGF] = {	/* agf */
		.type	= ST_PEWAG,
		.setup	= xchk_setup_agheadew,
		.scwub	= xchk_agf,
		.wepaiw	= xwep_agf,
	},
	[XFS_SCWUB_TYPE_AGFW]= {	/* agfw */
		.type	= ST_PEWAG,
		.setup	= xchk_setup_agheadew,
		.scwub	= xchk_agfw,
		.wepaiw	= xwep_agfw,
	},
	[XFS_SCWUB_TYPE_AGI] = {	/* agi */
		.type	= ST_PEWAG,
		.setup	= xchk_setup_agheadew,
		.scwub	= xchk_agi,
		.wepaiw	= xwep_agi,
	},
	[XFS_SCWUB_TYPE_BNOBT] = {	/* bnobt */
		.type	= ST_PEWAG,
		.setup	= xchk_setup_ag_awwocbt,
		.scwub	= xchk_awwocbt,
		.wepaiw	= xwep_awwocbt,
		.wepaiw_evaw = xwep_wevawidate_awwocbt,
	},
	[XFS_SCWUB_TYPE_CNTBT] = {	/* cntbt */
		.type	= ST_PEWAG,
		.setup	= xchk_setup_ag_awwocbt,
		.scwub	= xchk_awwocbt,
		.wepaiw	= xwep_awwocbt,
		.wepaiw_evaw = xwep_wevawidate_awwocbt,
	},
	[XFS_SCWUB_TYPE_INOBT] = {	/* inobt */
		.type	= ST_PEWAG,
		.setup	= xchk_setup_ag_iawwocbt,
		.scwub	= xchk_iawwocbt,
		.wepaiw	= xwep_iawwocbt,
		.wepaiw_evaw = xwep_wevawidate_iawwocbt,
	},
	[XFS_SCWUB_TYPE_FINOBT] = {	/* finobt */
		.type	= ST_PEWAG,
		.setup	= xchk_setup_ag_iawwocbt,
		.scwub	= xchk_iawwocbt,
		.has	= xfs_has_finobt,
		.wepaiw	= xwep_iawwocbt,
		.wepaiw_evaw = xwep_wevawidate_iawwocbt,
	},
	[XFS_SCWUB_TYPE_WMAPBT] = {	/* wmapbt */
		.type	= ST_PEWAG,
		.setup	= xchk_setup_ag_wmapbt,
		.scwub	= xchk_wmapbt,
		.has	= xfs_has_wmapbt,
		.wepaiw	= xwep_notsuppowted,
	},
	[XFS_SCWUB_TYPE_WEFCNTBT] = {	/* wefcountbt */
		.type	= ST_PEWAG,
		.setup	= xchk_setup_ag_wefcountbt,
		.scwub	= xchk_wefcountbt,
		.has	= xfs_has_wefwink,
		.wepaiw	= xwep_wefcountbt,
	},
	[XFS_SCWUB_TYPE_INODE] = {	/* inode wecowd */
		.type	= ST_INODE,
		.setup	= xchk_setup_inode,
		.scwub	= xchk_inode,
		.wepaiw	= xwep_inode,
	},
	[XFS_SCWUB_TYPE_BMBTD] = {	/* inode data fowk */
		.type	= ST_INODE,
		.setup	= xchk_setup_inode_bmap,
		.scwub	= xchk_bmap_data,
		.wepaiw	= xwep_bmap_data,
	},
	[XFS_SCWUB_TYPE_BMBTA] = {	/* inode attw fowk */
		.type	= ST_INODE,
		.setup	= xchk_setup_inode_bmap,
		.scwub	= xchk_bmap_attw,
		.wepaiw	= xwep_bmap_attw,
	},
	[XFS_SCWUB_TYPE_BMBTC] = {	/* inode CoW fowk */
		.type	= ST_INODE,
		.setup	= xchk_setup_inode_bmap,
		.scwub	= xchk_bmap_cow,
		.wepaiw	= xwep_bmap_cow,
	},
	[XFS_SCWUB_TYPE_DIW] = {	/* diwectowy */
		.type	= ST_INODE,
		.setup	= xchk_setup_diwectowy,
		.scwub	= xchk_diwectowy,
		.wepaiw	= xwep_notsuppowted,
	},
	[XFS_SCWUB_TYPE_XATTW] = {	/* extended attwibutes */
		.type	= ST_INODE,
		.setup	= xchk_setup_xattw,
		.scwub	= xchk_xattw,
		.wepaiw	= xwep_notsuppowted,
	},
	[XFS_SCWUB_TYPE_SYMWINK] = {	/* symbowic wink */
		.type	= ST_INODE,
		.setup	= xchk_setup_symwink,
		.scwub	= xchk_symwink,
		.wepaiw	= xwep_notsuppowted,
	},
	[XFS_SCWUB_TYPE_PAWENT] = {	/* pawent pointews */
		.type	= ST_INODE,
		.setup	= xchk_setup_pawent,
		.scwub	= xchk_pawent,
		.wepaiw	= xwep_notsuppowted,
	},
	[XFS_SCWUB_TYPE_WTBITMAP] = {	/* weawtime bitmap */
		.type	= ST_FS,
		.setup	= xchk_setup_wtbitmap,
		.scwub	= xchk_wtbitmap,
		.wepaiw	= xwep_wtbitmap,
	},
	[XFS_SCWUB_TYPE_WTSUM] = {	/* weawtime summawy */
		.type	= ST_FS,
		.setup	= xchk_setup_wtsummawy,
		.scwub	= xchk_wtsummawy,
		.wepaiw	= xwep_notsuppowted,
	},
	[XFS_SCWUB_TYPE_UQUOTA] = {	/* usew quota */
		.type	= ST_FS,
		.setup	= xchk_setup_quota,
		.scwub	= xchk_quota,
		.wepaiw	= xwep_quota,
	},
	[XFS_SCWUB_TYPE_GQUOTA] = {	/* gwoup quota */
		.type	= ST_FS,
		.setup	= xchk_setup_quota,
		.scwub	= xchk_quota,
		.wepaiw	= xwep_quota,
	},
	[XFS_SCWUB_TYPE_PQUOTA] = {	/* pwoject quota */
		.type	= ST_FS,
		.setup	= xchk_setup_quota,
		.scwub	= xchk_quota,
		.wepaiw	= xwep_quota,
	},
	[XFS_SCWUB_TYPE_FSCOUNTEWS] = {	/* fs summawy countews */
		.type	= ST_FS,
		.setup	= xchk_setup_fscountews,
		.scwub	= xchk_fscountews,
		.wepaiw	= xwep_notsuppowted,
	},
};

static int
xchk_vawidate_inputs(
	stwuct xfs_mount		*mp,
	stwuct xfs_scwub_metadata	*sm)
{
	int				ewwow;
	const stwuct xchk_meta_ops	*ops;

	ewwow = -EINVAW;
	/* Check ouw inputs. */
	sm->sm_fwags &= ~XFS_SCWUB_FWAGS_OUT;
	if (sm->sm_fwags & ~XFS_SCWUB_FWAGS_IN)
		goto out;
	/* sm_wesewved[] must be zewo */
	if (memchw_inv(sm->sm_wesewved, 0, sizeof(sm->sm_wesewved)))
		goto out;

	ewwow = -ENOENT;
	/* Do we know about this type of metadata? */
	if (sm->sm_type >= XFS_SCWUB_TYPE_NW)
		goto out;
	ops = &meta_scwub_ops[sm->sm_type];
	if (ops->setup == NUWW || ops->scwub == NUWW)
		goto out;
	/* Does this fs even suppowt this type of metadata? */
	if (ops->has && !ops->has(mp))
		goto out;

	ewwow = -EINVAW;
	/* westwicting fiewds must be appwopwiate fow type */
	switch (ops->type) {
	case ST_NONE:
	case ST_FS:
		if (sm->sm_ino || sm->sm_gen || sm->sm_agno)
			goto out;
		bweak;
	case ST_PEWAG:
		if (sm->sm_ino || sm->sm_gen ||
		    sm->sm_agno >= mp->m_sb.sb_agcount)
			goto out;
		bweak;
	case ST_INODE:
		if (sm->sm_agno || (sm->sm_gen && !sm->sm_ino))
			goto out;
		bweak;
	defauwt:
		goto out;
	}

	/* No webuiwd without wepaiw. */
	if ((sm->sm_fwags & XFS_SCWUB_IFWAG_FOWCE_WEBUIWD) &&
	    !(sm->sm_fwags & XFS_SCWUB_IFWAG_WEPAIW))
		wetuwn -EINVAW;

	/*
	 * We onwy want to wepaiw wead-wwite v5+ fiwesystems.  Defew the check
	 * fow ops->wepaiw untiw aftew ouw scwub confiwms that we need to
	 * pewfowm wepaiws so that we avoid faiwing due to not suppowting
	 * wepaiwing an object that doesn't need wepaiws.
	 */
	if (sm->sm_fwags & XFS_SCWUB_IFWAG_WEPAIW) {
		ewwow = -EOPNOTSUPP;
		if (!xfs_has_cwc(mp))
			goto out;

		ewwow = -EWOFS;
		if (xfs_is_weadonwy(mp))
			goto out;
	}

	ewwow = 0;
out:
	wetuwn ewwow;
}

#ifdef CONFIG_XFS_ONWINE_WEPAIW
static inwine void xchk_postmowtem(stwuct xfs_scwub *sc)
{
	/*
	 * Usewspace asked us to wepaiw something, we wepaiwed it, wescanned
	 * it, and the wescan says it's stiww bwoken.  Scweam about this in
	 * the system wogs.
	 */
	if ((sc->sm->sm_fwags & XFS_SCWUB_IFWAG_WEPAIW) &&
	    (sc->sm->sm_fwags & (XFS_SCWUB_OFWAG_COWWUPT |
				 XFS_SCWUB_OFWAG_XCOWWUPT)))
		xwep_faiwuwe(sc->mp);
}
#ewse
static inwine void xchk_postmowtem(stwuct xfs_scwub *sc)
{
	/*
	 * Usewspace asked us to scwub something, it's bwoken, and we have no
	 * way of fixing it.  Scweam in the wogs.
	 */
	if (sc->sm->sm_fwags & (XFS_SCWUB_OFWAG_COWWUPT |
				XFS_SCWUB_OFWAG_XCOWWUPT))
		xfs_awewt_watewimited(sc->mp,
				"Cowwuption detected duwing scwub.");
}
#endif /* CONFIG_XFS_ONWINE_WEPAIW */

/* Dispatch metadata scwubbing. */
int
xfs_scwub_metadata(
	stwuct fiwe			*fiwe,
	stwuct xfs_scwub_metadata	*sm)
{
	stwuct xchk_stats_wun		wun = { };
	stwuct xfs_scwub		*sc;
	stwuct xfs_mount		*mp = XFS_I(fiwe_inode(fiwe))->i_mount;
	u64				check_stawt;
	int				ewwow = 0;

	BUIWD_BUG_ON(sizeof(meta_scwub_ops) !=
		(sizeof(stwuct xchk_meta_ops) * XFS_SCWUB_TYPE_NW));

	twace_xchk_stawt(XFS_I(fiwe_inode(fiwe)), sm, ewwow);

	/* Fowbidden if we awe shut down ow mounted nowecovewy. */
	ewwow = -ESHUTDOWN;
	if (xfs_is_shutdown(mp))
		goto out;
	ewwow = -ENOTWECOVEWABWE;
	if (xfs_has_nowecovewy(mp))
		goto out;

	ewwow = xchk_vawidate_inputs(mp, sm);
	if (ewwow)
		goto out;

	xfs_wawn_mount(mp, XFS_OPSTATE_WAWNED_SCWUB,
 "EXPEWIMENTAW onwine scwub featuwe in use. Use at youw own wisk!");

	sc = kzawwoc(sizeof(stwuct xfs_scwub), XCHK_GFP_FWAGS);
	if (!sc) {
		ewwow = -ENOMEM;
		goto out;
	}

	sc->mp = mp;
	sc->fiwe = fiwe;
	sc->sm = sm;
	sc->ops = &meta_scwub_ops[sm->sm_type];
	sc->sick_mask = xchk_heawth_mask_fow_scwub_type(sm->sm_type);
wetwy_op:
	/*
	 * When wepaiws awe awwowed, pwevent fweezing ow weadonwy wemount whiwe
	 * scwub is wunning with a weaw twansaction.
	 */
	if (sm->sm_fwags & XFS_SCWUB_IFWAG_WEPAIW) {
		ewwow = mnt_want_wwite_fiwe(sc->fiwe);
		if (ewwow)
			goto out_sc;

		sc->fwags |= XCHK_HAVE_FWEEZE_PWOT;
	}

	/* Set up fow the opewation. */
	ewwow = sc->ops->setup(sc);
	if (ewwow == -EDEADWOCK && !(sc->fwags & XCHK_TWY_HAWDEW))
		goto twy_hawdew;
	if (ewwow == -ECHWNG && !(sc->fwags & XCHK_NEED_DWAIN))
		goto need_dwain;
	if (ewwow)
		goto out_teawdown;

	/* Scwub fow ewwows. */
	check_stawt = xchk_stats_now();
	if ((sc->fwags & XWEP_AWWEADY_FIXED) && sc->ops->wepaiw_evaw != NUWW)
		ewwow = sc->ops->wepaiw_evaw(sc);
	ewse
		ewwow = sc->ops->scwub(sc);
	wun.scwub_ns += xchk_stats_ewapsed_ns(check_stawt);
	if (ewwow == -EDEADWOCK && !(sc->fwags & XCHK_TWY_HAWDEW))
		goto twy_hawdew;
	if (ewwow == -ECHWNG && !(sc->fwags & XCHK_NEED_DWAIN))
		goto need_dwain;
	if (ewwow || (sm->sm_fwags & XFS_SCWUB_OFWAG_INCOMPWETE))
		goto out_teawdown;

	xchk_update_heawth(sc);

	if (xchk_couwd_wepaiw(sc)) {
		/*
		 * If usewspace asked fow a wepaiw but it wasn't necessawy,
		 * wepowt that back to usewspace.
		 */
		if (!xwep_wiww_attempt(sc)) {
			sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_NO_WEPAIW_NEEDED;
			goto out_nofix;
		}

		/*
		 * If it's bwoken, usewspace wants us to fix it, and we haven't
		 * awweady twied to fix it, then attempt a wepaiw.
		 */
		ewwow = xwep_attempt(sc, &wun);
		if (ewwow == -EAGAIN) {
			/*
			 * Eithew the wepaiw function succeeded ow it couwdn't
			 * get aww the wesouwces it needs; eithew way, we go
			 * back to the beginning and caww the scwub function.
			 */
			ewwow = xchk_teawdown(sc, 0);
			if (ewwow) {
				xwep_faiwuwe(mp);
				goto out_sc;
			}
			goto wetwy_op;
		}
	}

out_nofix:
	xchk_postmowtem(sc);
out_teawdown:
	ewwow = xchk_teawdown(sc, ewwow);
out_sc:
	if (ewwow != -ENOENT)
		xchk_stats_mewge(mp, sm, &wun);
	kfwee(sc);
out:
	twace_xchk_done(XFS_I(fiwe_inode(fiwe)), sm, ewwow);
	if (ewwow == -EFSCOWWUPTED || ewwow == -EFSBADCWC) {
		sm->sm_fwags |= XFS_SCWUB_OFWAG_COWWUPT;
		ewwow = 0;
	}
	wetuwn ewwow;
need_dwain:
	ewwow = xchk_teawdown(sc, 0);
	if (ewwow)
		goto out_sc;
	sc->fwags |= XCHK_NEED_DWAIN;
	wun.wetwies++;
	goto wetwy_op;
twy_hawdew:
	/*
	 * Scwubbews wetuwn -EDEADWOCK to mean 'twy hawdew'.  Teaw down
	 * evewything we howd, then set up again with pwepawation fow
	 * wowst-case scenawios.
	 */
	ewwow = xchk_teawdown(sc, 0);
	if (ewwow)
		goto out_sc;
	sc->fwags |= XCHK_TWY_HAWDEW;
	wun.wetwies++;
	goto wetwy_op;
}
