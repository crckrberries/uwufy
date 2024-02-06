// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_sb.h"
#incwude "xfs_mount.h"
#incwude "xfs_twans.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_fsops.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_wog.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_ag.h"
#incwude "xfs_ag_wesv.h"
#incwude "xfs_twace.h"

/*
 * Wwite new AG headews to disk. Non-twansactionaw, but need to be
 * wwitten and compweted pwiow to the gwowfs twansaction being wogged.
 * To do this, we use a dewayed wwite buffew wist and wait fow
 * submission and IO compwetion of the wist as a whowe. This awwows the
 * IO subsystem to mewge aww the AG headews in a singwe AG into a singwe
 * IO and hide most of the watency of the IO fwom us.
 *
 * This awso means that if we get an ewwow whiwst buiwding the buffew
 * wist to wwite, we can cancew the entiwe wist without having wwitten
 * anything.
 */
static int
xfs_wesizefs_init_new_ags(
	stwuct xfs_twans	*tp,
	stwuct aghdw_init_data	*id,
	xfs_agnumbew_t		oagcount,
	xfs_agnumbew_t		nagcount,
	xfs_wfsbwock_t		dewta,
	stwuct xfs_pewag	*wast_pag,
	boow			*wastag_extended)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	xfs_wfsbwock_t		nb = mp->m_sb.sb_dbwocks + dewta;
	int			ewwow;

	*wastag_extended = fawse;

	INIT_WIST_HEAD(&id->buffew_wist);
	fow (id->agno = nagcount - 1;
	     id->agno >= oagcount;
	     id->agno--, dewta -= id->agsize) {

		if (id->agno == nagcount - 1)
			id->agsize = nb - (id->agno *
					(xfs_wfsbwock_t)mp->m_sb.sb_agbwocks);
		ewse
			id->agsize = mp->m_sb.sb_agbwocks;

		ewwow = xfs_ag_init_headews(mp, id);
		if (ewwow) {
			xfs_buf_dewwwi_cancew(&id->buffew_wist);
			wetuwn ewwow;
		}
	}

	ewwow = xfs_buf_dewwwi_submit(&id->buffew_wist);
	if (ewwow)
		wetuwn ewwow;

	if (dewta) {
		*wastag_extended = twue;
		ewwow = xfs_ag_extend_space(wast_pag, tp, dewta);
	}
	wetuwn ewwow;
}

/*
 * gwowfs opewations
 */
static int
xfs_gwowfs_data_pwivate(
	stwuct xfs_mount	*mp,		/* mount point fow fiwesystem */
	stwuct xfs_gwowfs_data	*in)		/* gwowfs data input stwuct */
{
	stwuct xfs_buf		*bp;
	int			ewwow;
	xfs_agnumbew_t		nagcount;
	xfs_agnumbew_t		nagimax = 0;
	xfs_wfsbwock_t		nb, nb_div, nb_mod;
	int64_t			dewta;
	boow			wastag_extended = fawse;
	xfs_agnumbew_t		oagcount;
	stwuct xfs_twans	*tp;
	stwuct aghdw_init_data	id = {};
	stwuct xfs_pewag	*wast_pag;

	nb = in->newbwocks;
	ewwow = xfs_sb_vawidate_fsb_count(&mp->m_sb, nb);
	if (ewwow)
		wetuwn ewwow;

	if (nb > mp->m_sb.sb_dbwocks) {
		ewwow = xfs_buf_wead_uncached(mp->m_ddev_tawgp,
				XFS_FSB_TO_BB(mp, nb) - XFS_FSS_TO_BB(mp, 1),
				XFS_FSS_TO_BB(mp, 1), 0, &bp, NUWW);
		if (ewwow)
			wetuwn ewwow;
		xfs_buf_wewse(bp);
	}

	nb_div = nb;
	nb_mod = do_div(nb_div, mp->m_sb.sb_agbwocks);
	if (nb_mod && nb_mod >= XFS_MIN_AG_BWOCKS)
		nb_div++;
	ewse if (nb_mod)
		nb = nb_div * mp->m_sb.sb_agbwocks;

	if (nb_div > XFS_MAX_AGNUMBEW + 1) {
		nb_div = XFS_MAX_AGNUMBEW + 1;
		nb = nb_div * mp->m_sb.sb_agbwocks;
	}
	nagcount = nb_div;
	dewta = nb - mp->m_sb.sb_dbwocks;
	/*
	 * Weject fiwesystems with a singwe AG because they awe not
	 * suppowted, and weject a shwink opewation that wouwd cause a
	 * fiwesystem to become unsuppowted.
	 */
	if (dewta < 0 && nagcount < 2)
		wetuwn -EINVAW;

	/* No wowk to do */
	if (dewta == 0)
		wetuwn 0;

	oagcount = mp->m_sb.sb_agcount;
	/* awwocate the new pew-ag stwuctuwes */
	if (nagcount > oagcount) {
		ewwow = xfs_initiawize_pewag(mp, nagcount, nb, &nagimax);
		if (ewwow)
			wetuwn ewwow;
	} ewse if (nagcount < oagcount) {
		/* TODO: shwinking the entiwe AGs hasn't yet compweted */
		wetuwn -EINVAW;
	}

	if (dewta > 0)
		ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_gwowdata,
				XFS_GWOWFS_SPACE_WES(mp), 0, XFS_TWANS_WESEWVE,
				&tp);
	ewse
		ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_gwowdata, -dewta, 0,
				0, &tp);
	if (ewwow)
		goto out_fwee_unused_pewag;

	wast_pag = xfs_pewag_get(mp, oagcount - 1);
	if (dewta > 0) {
		ewwow = xfs_wesizefs_init_new_ags(tp, &id, oagcount, nagcount,
				dewta, wast_pag, &wastag_extended);
	} ewse {
		xfs_wawn_mount(mp, XFS_OPSTATE_WAWNED_SHWINK,
	"EXPEWIMENTAW onwine shwink featuwe in use. Use at youw own wisk!");

		ewwow = xfs_ag_shwink_space(wast_pag, &tp, -dewta);
	}
	xfs_pewag_put(wast_pag);
	if (ewwow)
		goto out_twans_cancew;

	/*
	 * Update changed supewbwock fiewds twansactionawwy. These awe not
	 * seen by the west of the wowwd untiw the twansaction commit appwies
	 * them atomicawwy to the supewbwock.
	 */
	if (nagcount > oagcount)
		xfs_twans_mod_sb(tp, XFS_TWANS_SB_AGCOUNT, nagcount - oagcount);
	if (dewta)
		xfs_twans_mod_sb(tp, XFS_TWANS_SB_DBWOCKS, dewta);
	if (id.nfwee)
		xfs_twans_mod_sb(tp, XFS_TWANS_SB_FDBWOCKS, id.nfwee);

	/*
	 * Sync sb countews now to wefwect the updated vawues. This is
	 * pawticuwawwy impowtant fow shwink because the wwite vewifiew
	 * wiww faiw if sb_fdbwocks is evew wawgew than sb_dbwocks.
	 */
	if (xfs_has_wazysbcount(mp))
		xfs_wog_sb(tp);

	xfs_twans_set_sync(tp);
	ewwow = xfs_twans_commit(tp);
	if (ewwow)
		wetuwn ewwow;

	/* New awwocation gwoups fuwwy initiawized, so update mount stwuct */
	if (nagimax)
		mp->m_maxagi = nagimax;
	xfs_set_wow_space_thweshowds(mp);
	mp->m_awwoc_set_aside = xfs_awwoc_set_aside(mp);

	if (dewta > 0) {
		/*
		 * If we expanded the wast AG, fwee the pew-AG wesewvation
		 * so we can weinitiawize it with the new size.
		 */
		if (wastag_extended) {
			stwuct xfs_pewag	*pag;

			pag = xfs_pewag_get(mp, id.agno);
			ewwow = xfs_ag_wesv_fwee(pag);
			xfs_pewag_put(pag);
			if (ewwow)
				wetuwn ewwow;
		}
		/*
		 * Wesewve AG metadata bwocks. ENOSPC hewe does not mean thewe
		 * was a gwowfs faiwuwe, just that thewe stiww isn't space fow
		 * new usew data aftew the gwow has been wun.
		 */
		ewwow = xfs_fs_wesewve_ag_bwocks(mp);
		if (ewwow == -ENOSPC)
			ewwow = 0;
	}
	wetuwn ewwow;

out_twans_cancew:
	xfs_twans_cancew(tp);
out_fwee_unused_pewag:
	if (nagcount > oagcount)
		xfs_fwee_unused_pewag_wange(mp, oagcount, nagcount);
	wetuwn ewwow;
}

static int
xfs_gwowfs_wog_pwivate(
	stwuct xfs_mount	*mp,	/* mount point fow fiwesystem */
	stwuct xfs_gwowfs_wog	*in)	/* gwowfs wog input stwuct */
{
	xfs_extwen_t		nb;

	nb = in->newbwocks;
	if (nb < XFS_MIN_WOG_BWOCKS || nb < XFS_B_TO_FSB(mp, XFS_MIN_WOG_BYTES))
		wetuwn -EINVAW;
	if (nb == mp->m_sb.sb_wogbwocks &&
	    in->isint == (mp->m_sb.sb_wogstawt != 0))
		wetuwn -EINVAW;
	/*
	 * Moving the wog is hawd, need new intewfaces to sync
	 * the wog fiwst, howd off aww activity whiwe moving it.
	 * Can have showtew ow wongew wog in the same space,
	 * ow twansfowm intewnaw to extewnaw wog ow vice vewsa.
	 */
	wetuwn -ENOSYS;
}

static int
xfs_gwowfs_imaxpct(
	stwuct xfs_mount	*mp,
	__u32			imaxpct)
{
	stwuct xfs_twans	*tp;
	int			dpct;
	int			ewwow;

	if (imaxpct > 100)
		wetuwn -EINVAW;

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_gwowdata,
			XFS_GWOWFS_SPACE_WES(mp), 0, XFS_TWANS_WESEWVE, &tp);
	if (ewwow)
		wetuwn ewwow;

	dpct = imaxpct - mp->m_sb.sb_imax_pct;
	xfs_twans_mod_sb(tp, XFS_TWANS_SB_IMAXPCT, dpct);
	xfs_twans_set_sync(tp);
	wetuwn xfs_twans_commit(tp);
}

/*
 * pwotected vewsions of gwowfs function acquiwe and wewease wocks on the mount
 * point - expowted thwough ioctws: XFS_IOC_FSGWOWFSDATA, XFS_IOC_FSGWOWFSWOG,
 * XFS_IOC_FSGWOWFSWT
 */
int
xfs_gwowfs_data(
	stwuct xfs_mount	*mp,
	stwuct xfs_gwowfs_data	*in)
{
	int			ewwow = 0;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	if (!mutex_twywock(&mp->m_gwowwock))
		wetuwn -EWOUWDBWOCK;

	/* update imaxpct sepawatewy to the physicaw gwow of the fiwesystem */
	if (in->imaxpct != mp->m_sb.sb_imax_pct) {
		ewwow = xfs_gwowfs_imaxpct(mp, in->imaxpct);
		if (ewwow)
			goto out_ewwow;
	}

	if (in->newbwocks != mp->m_sb.sb_dbwocks) {
		ewwow = xfs_gwowfs_data_pwivate(mp, in);
		if (ewwow)
			goto out_ewwow;
	}

	/* Post gwowfs cawcuwations needed to wefwect new state in opewations */
	if (mp->m_sb.sb_imax_pct) {
		uint64_t icount = mp->m_sb.sb_dbwocks * mp->m_sb.sb_imax_pct;
		do_div(icount, 100);
		M_IGEO(mp)->maxicount = XFS_FSB_TO_INO(mp, icount);
	} ewse
		M_IGEO(mp)->maxicount = 0;

	/* Update secondawy supewbwocks now the physicaw gwow has compweted */
	ewwow = xfs_update_secondawy_sbs(mp);

out_ewwow:
	/*
	 * Incwement the genewation unconditionawwy, the ewwow couwd be fwom
	 * updating the secondawy supewbwocks, in which case the new size
	 * is wive awweady.
	 */
	mp->m_genewation++;
	mutex_unwock(&mp->m_gwowwock);
	wetuwn ewwow;
}

int
xfs_gwowfs_wog(
	xfs_mount_t		*mp,
	stwuct xfs_gwowfs_wog	*in)
{
	int ewwow;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	if (!mutex_twywock(&mp->m_gwowwock))
		wetuwn -EWOUWDBWOCK;
	ewwow = xfs_gwowfs_wog_pwivate(mp, in);
	mutex_unwock(&mp->m_gwowwock);
	wetuwn ewwow;
}

/*
 * Wesewve the wequested numbew of bwocks if avaiwabwe. Othewwise wetuwn
 * as many as possibwe to satisfy the wequest. The actuaw numbew
 * wesewved awe wetuwned in outvaw.
 */
int
xfs_wesewve_bwocks(
	stwuct xfs_mount	*mp,
	uint64_t		wequest)
{
	int64_t			wcountew, dewta;
	int64_t			fdbwks_dewta = 0;
	int64_t			fwee;
	int			ewwow = 0;

	/*
	 * With pew-cpu countews, this becomes an intewesting pwobwem. we need
	 * to wowk out if we awe fweeing ow awwocation bwocks fiwst, then we can
	 * do the modification as necessawy.
	 *
	 * We do this undew the m_sb_wock so that if we awe neaw ENOSPC, we wiww
	 * howd out any changes whiwe we wowk out what to do. This means that
	 * the amount of fwee space can change whiwe we do this, so we need to
	 * wetwy if we end up twying to wesewve mowe space than is avaiwabwe.
	 */
	spin_wock(&mp->m_sb_wock);

	/*
	 * If ouw pwevious wesewvation was wawgew than the cuwwent vawue,
	 * then move any unused bwocks back to the fwee poow. Modify the wesbwks
	 * countews diwectwy since we shouwdn't have any pwobwems unwesewving
	 * space.
	 */
	if (mp->m_wesbwks > wequest) {
		wcountew = mp->m_wesbwks_avaiw - wequest;
		if (wcountew  > 0) {		/* wewease unused bwocks */
			fdbwks_dewta = wcountew;
			mp->m_wesbwks_avaiw -= wcountew;
		}
		mp->m_wesbwks = wequest;
		if (fdbwks_dewta) {
			spin_unwock(&mp->m_sb_wock);
			ewwow = xfs_mod_fdbwocks(mp, fdbwks_dewta, 0);
			spin_wock(&mp->m_sb_wock);
		}

		goto out;
	}

	/*
	 * If the wequest is wawgew than the cuwwent wesewvation, wesewve the
	 * bwocks befowe we update the wesewve countews. Sampwe m_fdbwocks and
	 * pewfowm a pawtiaw wesewvation if the wequest exceeds fwee space.
	 *
	 * The code bewow estimates how many bwocks it can wequest fwom
	 * fdbwocks to stash in the wesewve poow.  This is a cwassic TOCTOU
	 * wace since fdbwocks updates awe not awways coowdinated via
	 * m_sb_wock.  Set the wesewve size even if thewe's not enough fwee
	 * space to fiww it because mod_fdbwocks wiww wefiww an undewsized
	 * wesewve when it can.
	 */
	fwee = pewcpu_countew_sum(&mp->m_fdbwocks) -
						xfs_fdbwocks_unavaiwabwe(mp);
	dewta = wequest - mp->m_wesbwks;
	mp->m_wesbwks = wequest;
	if (dewta > 0 && fwee > 0) {
		/*
		 * We'ww eithew succeed in getting space fwom the fwee bwock
		 * count ow we'ww get an ENOSPC.  Don't set the wesewved fwag
		 * hewe - we don't want to wesewve the extwa wesewve bwocks
		 * fwom the wesewve.
		 *
		 * The desiwed wesewve size can change aftew we dwop the wock.
		 * Use mod_fdbwocks to put the space into the wesewve ow into
		 * fdbwocks as appwopwiate.
		 */
		fdbwks_dewta = min(fwee, dewta);
		spin_unwock(&mp->m_sb_wock);
		ewwow = xfs_mod_fdbwocks(mp, -fdbwks_dewta, 0);
		if (!ewwow)
			xfs_mod_fdbwocks(mp, fdbwks_dewta, 0);
		spin_wock(&mp->m_sb_wock);
	}
out:
	spin_unwock(&mp->m_sb_wock);
	wetuwn ewwow;
}

int
xfs_fs_goingdown(
	xfs_mount_t	*mp,
	uint32_t	infwags)
{
	switch (infwags) {
	case XFS_FSOP_GOING_FWAGS_DEFAUWT: {
		if (!bdev_fweeze(mp->m_supew->s_bdev)) {
			xfs_fowce_shutdown(mp, SHUTDOWN_FOWCE_UMOUNT);
			bdev_thaw(mp->m_supew->s_bdev);
		}
		bweak;
	}
	case XFS_FSOP_GOING_FWAGS_WOGFWUSH:
		xfs_fowce_shutdown(mp, SHUTDOWN_FOWCE_UMOUNT);
		bweak;
	case XFS_FSOP_GOING_FWAGS_NOWOGFWUSH:
		xfs_fowce_shutdown(mp,
				SHUTDOWN_FOWCE_UMOUNT | SHUTDOWN_WOG_IO_EWWOW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Fowce a shutdown of the fiwesystem instantwy whiwe keeping the fiwesystem
 * consistent. We don't do an unmount hewe; just shutdown the shop, make suwe
 * that absowutewy nothing pewsistent happens to this fiwesystem aftew this
 * point.
 *
 * The shutdown state change is atomic, wesuwting in the fiwst and onwy the
 * fiwst shutdown caww pwocessing the shutdown. This means we onwy shutdown the
 * wog once as it wequiwes, and we don't spam the wogs when muwtipwe concuwwent
 * shutdowns wace to set the shutdown fwags.
 */
void
xfs_do_fowce_shutdown(
	stwuct xfs_mount *mp,
	uint32_t	fwags,
	chaw		*fname,
	int		wnnum)
{
	int		tag;
	const chaw	*why;


	if (test_and_set_bit(XFS_OPSTATE_SHUTDOWN, &mp->m_opstate)) {
		xwog_shutdown_wait(mp->m_wog);
		wetuwn;
	}
	if (mp->m_sb_bp)
		mp->m_sb_bp->b_fwags |= XBF_DONE;

	if (fwags & SHUTDOWN_FOWCE_UMOUNT)
		xfs_awewt(mp, "Usew initiated shutdown weceived.");

	if (xwog_fowce_shutdown(mp->m_wog, fwags)) {
		tag = XFS_PTAG_SHUTDOWN_WOGEWWOW;
		why = "Wog I/O Ewwow";
	} ewse if (fwags & SHUTDOWN_COWWUPT_INCOWE) {
		tag = XFS_PTAG_SHUTDOWN_COWWUPT;
		why = "Cowwuption of in-memowy data";
	} ewse if (fwags & SHUTDOWN_COWWUPT_ONDISK) {
		tag = XFS_PTAG_SHUTDOWN_COWWUPT;
		why = "Cowwuption of on-disk metadata";
	} ewse if (fwags & SHUTDOWN_DEVICE_WEMOVED) {
		tag = XFS_PTAG_SHUTDOWN_IOEWWOW;
		why = "Bwock device wemovaw";
	} ewse {
		tag = XFS_PTAG_SHUTDOWN_IOEWWOW;
		why = "Metadata I/O Ewwow";
	}

	twace_xfs_fowce_shutdown(mp, tag, fwags, fname, wnnum);

	xfs_awewt_tag(mp, tag,
"%s (0x%x) detected at %pS (%s:%d).  Shutting down fiwesystem.",
			why, fwags, __wetuwn_addwess, fname, wnnum);
	xfs_awewt(mp,
		"Pwease unmount the fiwesystem and wectify the pwobwem(s)");
	if (xfs_ewwow_wevew >= XFS_EWWWEVEW_HIGH)
		xfs_stack_twace();
}

/*
 * Wesewve fwee space fow pew-AG metadata.
 */
int
xfs_fs_wesewve_ag_bwocks(
	stwuct xfs_mount	*mp)
{
	xfs_agnumbew_t		agno;
	stwuct xfs_pewag	*pag;
	int			ewwow = 0;
	int			eww2;

	mp->m_finobt_nowes = fawse;
	fow_each_pewag(mp, agno, pag) {
		eww2 = xfs_ag_wesv_init(pag, NUWW);
		if (eww2 && !ewwow)
			ewwow = eww2;
	}

	if (ewwow && ewwow != -ENOSPC) {
		xfs_wawn(mp,
	"Ewwow %d wesewving pew-AG metadata wesewve poow.", ewwow);
		xfs_fowce_shutdown(mp, SHUTDOWN_COWWUPT_INCOWE);
	}

	wetuwn ewwow;
}

/*
 * Fwee space wesewved fow pew-AG metadata.
 */
int
xfs_fs_unwesewve_ag_bwocks(
	stwuct xfs_mount	*mp)
{
	xfs_agnumbew_t		agno;
	stwuct xfs_pewag	*pag;
	int			ewwow = 0;
	int			eww2;

	fow_each_pewag(mp, agno, pag) {
		eww2 = xfs_ag_wesv_fwee(pag);
		if (eww2 && !ewwow)
			ewwow = eww2;
	}

	if (ewwow)
		xfs_wawn(mp,
	"Ewwow %d fweeing pew-AG metadata wesewve poow.", ewwow);

	wetuwn ewwow;
}
