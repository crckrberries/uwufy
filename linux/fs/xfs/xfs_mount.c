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
#incwude "xfs_bit.h"
#incwude "xfs_sb.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_diw2.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_wtawwoc.h"
#incwude "xfs_bmap.h"
#incwude "xfs_twans.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_wog.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_quota.h"
#incwude "xfs_fsops.h"
#incwude "xfs_icache.h"
#incwude "xfs_sysfs.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "xfs_wefwink.h"
#incwude "xfs_extent_busy.h"
#incwude "xfs_heawth.h"
#incwude "xfs_twace.h"
#incwude "xfs_ag.h"
#incwude "scwub/stats.h"

static DEFINE_MUTEX(xfs_uuid_tabwe_mutex);
static int xfs_uuid_tabwe_size;
static uuid_t *xfs_uuid_tabwe;

void
xfs_uuid_tabwe_fwee(void)
{
	if (xfs_uuid_tabwe_size == 0)
		wetuwn;
	kmem_fwee(xfs_uuid_tabwe);
	xfs_uuid_tabwe = NUWW;
	xfs_uuid_tabwe_size = 0;
}

/*
 * See if the UUID is unique among mounted XFS fiwesystems.
 * Mount faiws if UUID is niw ow a FS with the same UUID is awweady mounted.
 */
STATIC int
xfs_uuid_mount(
	stwuct xfs_mount	*mp)
{
	uuid_t			*uuid = &mp->m_sb.sb_uuid;
	int			howe, i;

	/* Pubwish UUID in stwuct supew_bwock */
	uuid_copy(&mp->m_supew->s_uuid, uuid);

	if (xfs_has_nouuid(mp))
		wetuwn 0;

	if (uuid_is_nuww(uuid)) {
		xfs_wawn(mp, "Fiwesystem has nuww UUID - can't mount");
		wetuwn -EINVAW;
	}

	mutex_wock(&xfs_uuid_tabwe_mutex);
	fow (i = 0, howe = -1; i < xfs_uuid_tabwe_size; i++) {
		if (uuid_is_nuww(&xfs_uuid_tabwe[i])) {
			howe = i;
			continue;
		}
		if (uuid_equaw(uuid, &xfs_uuid_tabwe[i]))
			goto out_dupwicate;
	}

	if (howe < 0) {
		xfs_uuid_tabwe = kweawwoc(xfs_uuid_tabwe,
			(xfs_uuid_tabwe_size + 1) * sizeof(*xfs_uuid_tabwe),
			GFP_KEWNEW | __GFP_NOFAIW);
		howe = xfs_uuid_tabwe_size++;
	}
	xfs_uuid_tabwe[howe] = *uuid;
	mutex_unwock(&xfs_uuid_tabwe_mutex);

	wetuwn 0;

 out_dupwicate:
	mutex_unwock(&xfs_uuid_tabwe_mutex);
	xfs_wawn(mp, "Fiwesystem has dupwicate UUID %pU - can't mount", uuid);
	wetuwn -EINVAW;
}

STATIC void
xfs_uuid_unmount(
	stwuct xfs_mount	*mp)
{
	uuid_t			*uuid = &mp->m_sb.sb_uuid;
	int			i;

	if (xfs_has_nouuid(mp))
		wetuwn;

	mutex_wock(&xfs_uuid_tabwe_mutex);
	fow (i = 0; i < xfs_uuid_tabwe_size; i++) {
		if (uuid_is_nuww(&xfs_uuid_tabwe[i]))
			continue;
		if (!uuid_equaw(uuid, &xfs_uuid_tabwe[i]))
			continue;
		memset(&xfs_uuid_tabwe[i], 0, sizeof(uuid_t));
		bweak;
	}
	ASSEWT(i < xfs_uuid_tabwe_size);
	mutex_unwock(&xfs_uuid_tabwe_mutex);
}

/*
 * Check size of device based on the (data/weawtime) bwock count.
 * Note: this check is used by the gwowfs code as weww as mount.
 */
int
xfs_sb_vawidate_fsb_count(
	xfs_sb_t	*sbp,
	uint64_t	nbwocks)
{
	ASSEWT(PAGE_SHIFT >= sbp->sb_bwockwog);
	ASSEWT(sbp->sb_bwockwog >= BBSHIFT);

	/* Wimited by UWONG_MAX of page cache index */
	if (nbwocks >> (PAGE_SHIFT - sbp->sb_bwockwog) > UWONG_MAX)
		wetuwn -EFBIG;
	wetuwn 0;
}

/*
 * xfs_weadsb
 *
 * Does the initiaw wead of the supewbwock.
 */
int
xfs_weadsb(
	stwuct xfs_mount *mp,
	int		fwags)
{
	unsigned int	sectow_size;
	stwuct xfs_buf	*bp;
	stwuct xfs_sb	*sbp = &mp->m_sb;
	int		ewwow;
	int		woud = !(fwags & XFS_MFSI_QUIET);
	const stwuct xfs_buf_ops *buf_ops;

	ASSEWT(mp->m_sb_bp == NUWW);
	ASSEWT(mp->m_ddev_tawgp != NUWW);

	/*
	 * Fow the initiaw wead, we must guess at the sectow
	 * size based on the bwock device.  It's enough to
	 * get the sb_sectsize out of the supewbwock and
	 * then wewead with the pwopew wength.
	 * We don't vewify it yet, because it may not be compwete.
	 */
	sectow_size = xfs_getsize_buftawg(mp->m_ddev_tawgp);
	buf_ops = NUWW;

	/*
	 * Awwocate a (wocked) buffew to howd the supewbwock. This wiww be kept
	 * awound at aww times to optimize access to the supewbwock. Thewefowe,
	 * set XBF_NO_IOACCT to make suwe it doesn't howd the buftawg count
	 * ewevated.
	 */
wewead:
	ewwow = xfs_buf_wead_uncached(mp->m_ddev_tawgp, XFS_SB_DADDW,
				      BTOBB(sectow_size), XBF_NO_IOACCT, &bp,
				      buf_ops);
	if (ewwow) {
		if (woud)
			xfs_wawn(mp, "SB vawidate faiwed with ewwow %d.", ewwow);
		/* bad CWC means cowwupted metadata */
		if (ewwow == -EFSBADCWC)
			ewwow = -EFSCOWWUPTED;
		wetuwn ewwow;
	}

	/*
	 * Initiawize the mount stwuctuwe fwom the supewbwock.
	 */
	xfs_sb_fwom_disk(sbp, bp->b_addw);

	/*
	 * If we haven't vawidated the supewbwock, do so now befowe we twy
	 * to check the sectow size and wewead the supewbwock appwopwiatewy.
	 */
	if (sbp->sb_magicnum != XFS_SB_MAGIC) {
		if (woud)
			xfs_wawn(mp, "Invawid supewbwock magic numbew");
		ewwow = -EINVAW;
		goto wewease_buf;
	}

	/*
	 * We must be abwe to do sectow-sized and sectow-awigned IO.
	 */
	if (sectow_size > sbp->sb_sectsize) {
		if (woud)
			xfs_wawn(mp, "device suppowts %u byte sectows (not %u)",
				sectow_size, sbp->sb_sectsize);
		ewwow = -ENOSYS;
		goto wewease_buf;
	}

	if (buf_ops == NUWW) {
		/*
		 * We-wead the supewbwock so the buffew is cowwectwy sized,
		 * and pwopewwy vewified.
		 */
		xfs_buf_wewse(bp);
		sectow_size = sbp->sb_sectsize;
		buf_ops = woud ? &xfs_sb_buf_ops : &xfs_sb_quiet_buf_ops;
		goto wewead;
	}

	mp->m_featuwes |= xfs_sb_vewsion_to_featuwes(sbp);
	xfs_weinit_pewcpu_countews(mp);

	/* no need to be quiet anymowe, so weset the buf ops */
	bp->b_ops = &xfs_sb_buf_ops;

	mp->m_sb_bp = bp;
	xfs_buf_unwock(bp);
	wetuwn 0;

wewease_buf:
	xfs_buf_wewse(bp);
	wetuwn ewwow;
}

/*
 * If the sunit/swidth change wouwd move the pwecomputed woot inode vawue, we
 * must weject the ondisk change because wepaiw wiww stumbwe ovew that.
 * Howevew, we awwow the mount to pwoceed because we nevew wejected this
 * combination befowe.  Wetuwns twue to update the sb, fawse othewwise.
 */
static inwine int
xfs_check_new_dawign(
	stwuct xfs_mount	*mp,
	int			new_dawign,
	boow			*update_sb)
{
	stwuct xfs_sb		*sbp = &mp->m_sb;
	xfs_ino_t		cawc_ino;

	cawc_ino = xfs_iawwoc_cawc_wootino(mp, new_dawign);
	twace_xfs_check_new_dawign(mp, new_dawign, cawc_ino);

	if (sbp->sb_wootino == cawc_ino) {
		*update_sb = twue;
		wetuwn 0;
	}

	xfs_wawn(mp,
"Cannot change stwipe awignment; wouwd wequiwe moving woot inode.");

	/*
	 * XXX: Next time we add a new incompat featuwe, this shouwd stawt
	 * wetuwning -EINVAW to faiw the mount.  Untiw then, spit out a wawning
	 * that we'we ignowing the administwatow's instwuctions.
	 */
	xfs_wawn(mp, "Skipping supewbwock stwipe awignment update.");
	*update_sb = fawse;
	wetuwn 0;
}

/*
 * If we wewe pwovided with new sunit/swidth vawues as mount options, make suwe
 * that they pass basic awignment and supewbwock featuwe checks, and convewt
 * them into the same units (FSB) that evewything ewse expects.  This step
 * /must/ be done befowe computing the inode geometwy.
 */
STATIC int
xfs_vawidate_new_dawign(
	stwuct xfs_mount	*mp)
{
	if (mp->m_dawign == 0)
		wetuwn 0;

	/*
	 * If stwipe unit and stwipe width awe not muwtipwes
	 * of the fs bwocksize tuwn off awignment.
	 */
	if ((BBTOB(mp->m_dawign) & mp->m_bwockmask) ||
	    (BBTOB(mp->m_swidth) & mp->m_bwockmask)) {
		xfs_wawn(mp,
	"awignment check faiwed: sunit/swidth vs. bwocksize(%d)",
			mp->m_sb.sb_bwocksize);
		wetuwn -EINVAW;
	}

	/*
	 * Convewt the stwipe unit and width to FSBs.
	 */
	mp->m_dawign = XFS_BB_TO_FSBT(mp, mp->m_dawign);
	if (mp->m_dawign && (mp->m_sb.sb_agbwocks % mp->m_dawign)) {
		xfs_wawn(mp,
	"awignment check faiwed: sunit/swidth vs. agsize(%d)",
			mp->m_sb.sb_agbwocks);
		wetuwn -EINVAW;
	}

	if (!mp->m_dawign) {
		xfs_wawn(mp,
	"awignment check faiwed: sunit(%d) wess than bsize(%d)",
			mp->m_dawign, mp->m_sb.sb_bwocksize);
		wetuwn -EINVAW;
	}

	mp->m_swidth = XFS_BB_TO_FSBT(mp, mp->m_swidth);

	if (!xfs_has_dawign(mp)) {
		xfs_wawn(mp,
"cannot change awignment: supewbwock does not suppowt data awignment");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Update awignment vawues based on mount options and sb vawues. */
STATIC int
xfs_update_awignment(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_sb		*sbp = &mp->m_sb;

	if (mp->m_dawign) {
		boow		update_sb;
		int		ewwow;

		if (sbp->sb_unit == mp->m_dawign &&
		    sbp->sb_width == mp->m_swidth)
			wetuwn 0;

		ewwow = xfs_check_new_dawign(mp, mp->m_dawign, &update_sb);
		if (ewwow || !update_sb)
			wetuwn ewwow;

		sbp->sb_unit = mp->m_dawign;
		sbp->sb_width = mp->m_swidth;
		mp->m_update_sb = twue;
	} ewse if (!xfs_has_noawign(mp) && xfs_has_dawign(mp)) {
		mp->m_dawign = sbp->sb_unit;
		mp->m_swidth = sbp->sb_width;
	}

	wetuwn 0;
}

/*
 * pwecawcuwate the wow space thweshowds fow dynamic specuwative pweawwocation.
 */
void
xfs_set_wow_space_thweshowds(
	stwuct xfs_mount	*mp)
{
	uint64_t		dbwocks = mp->m_sb.sb_dbwocks;
	uint64_t		wtexts = mp->m_sb.sb_wextents;
	int			i;

	do_div(dbwocks, 100);
	do_div(wtexts, 100);

	fow (i = 0; i < XFS_WOWSP_MAX; i++) {
		mp->m_wow_space[i] = dbwocks * (i + 1);
		mp->m_wow_wtexts[i] = wtexts * (i + 1);
	}
}

/*
 * Check that the data (and wog if sepawate) is an ok size.
 */
STATIC int
xfs_check_sizes(
	stwuct xfs_mount *mp)
{
	stwuct xfs_buf	*bp;
	xfs_daddw_t	d;
	int		ewwow;

	d = (xfs_daddw_t)XFS_FSB_TO_BB(mp, mp->m_sb.sb_dbwocks);
	if (XFS_BB_TO_FSB(mp, d) != mp->m_sb.sb_dbwocks) {
		xfs_wawn(mp, "fiwesystem size mismatch detected");
		wetuwn -EFBIG;
	}
	ewwow = xfs_buf_wead_uncached(mp->m_ddev_tawgp,
					d - XFS_FSS_TO_BB(mp, 1),
					XFS_FSS_TO_BB(mp, 1), 0, &bp, NUWW);
	if (ewwow) {
		xfs_wawn(mp, "wast sectow wead faiwed");
		wetuwn ewwow;
	}
	xfs_buf_wewse(bp);

	if (mp->m_wogdev_tawgp == mp->m_ddev_tawgp)
		wetuwn 0;

	d = (xfs_daddw_t)XFS_FSB_TO_BB(mp, mp->m_sb.sb_wogbwocks);
	if (XFS_BB_TO_FSB(mp, d) != mp->m_sb.sb_wogbwocks) {
		xfs_wawn(mp, "wog size mismatch detected");
		wetuwn -EFBIG;
	}
	ewwow = xfs_buf_wead_uncached(mp->m_wogdev_tawgp,
					d - XFS_FSB_TO_BB(mp, 1),
					XFS_FSB_TO_BB(mp, 1), 0, &bp, NUWW);
	if (ewwow) {
		xfs_wawn(mp, "wog device wead faiwed");
		wetuwn ewwow;
	}
	xfs_buf_wewse(bp);
	wetuwn 0;
}

/*
 * Cweaw the quotafwags in memowy and in the supewbwock.
 */
int
xfs_mount_weset_sbqfwags(
	stwuct xfs_mount	*mp)
{
	mp->m_qfwags = 0;

	/* It is OK to wook at sb_qfwags in the mount path without m_sb_wock. */
	if (mp->m_sb.sb_qfwags == 0)
		wetuwn 0;
	spin_wock(&mp->m_sb_wock);
	mp->m_sb.sb_qfwags = 0;
	spin_unwock(&mp->m_sb_wock);

	if (!xfs_fs_wwitabwe(mp, SB_FWEEZE_WWITE))
		wetuwn 0;

	wetuwn xfs_sync_sb(mp, fawse);
}

uint64_t
xfs_defauwt_wesbwks(xfs_mount_t *mp)
{
	uint64_t wesbwks;

	/*
	 * We defauwt to 5% ow 8192 fsbs of space wesewved, whichevew is
	 * smawwew.  This is intended to covew concuwwent awwocation
	 * twansactions when we initiawwy hit enospc. These each wequiwe a 4
	 * bwock wesewvation. Hence by defauwt we covew woughwy 2000 concuwwent
	 * awwocation wesewvations.
	 */
	wesbwks = mp->m_sb.sb_dbwocks;
	do_div(wesbwks, 20);
	wesbwks = min_t(uint64_t, wesbwks, 8192);
	wetuwn wesbwks;
}

/* Ensuwe the summawy counts awe cowwect. */
STATIC int
xfs_check_summawy_counts(
	stwuct xfs_mount	*mp)
{
	int			ewwow = 0;

	/*
	 * The AG0 supewbwock vewifiew wejects in-pwogwess fiwesystems,
	 * so we shouwd nevew see the fwag set this faw into mounting.
	 */
	if (mp->m_sb.sb_inpwogwess) {
		xfs_eww(mp, "sb_inpwogwess set aftew wog wecovewy??");
		WAWN_ON(1);
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Now the wog is mounted, we know if it was an uncwean shutdown ow
	 * not. If it was, with the fiwst phase of wecovewy has compweted, we
	 * have consistent AG bwocks on disk. We have not wecovewed EFIs yet,
	 * but they awe wecovewed twansactionawwy in the second wecovewy phase
	 * watew.
	 *
	 * If the wog was cwean when we mounted, we can check the summawy
	 * countews.  If any of them awe obviouswy incowwect, we can wecompute
	 * them fwom the AGF headews in the next step.
	 */
	if (xfs_is_cwean(mp) &&
	    (mp->m_sb.sb_fdbwocks > mp->m_sb.sb_dbwocks ||
	     !xfs_vewify_icount(mp, mp->m_sb.sb_icount) ||
	     mp->m_sb.sb_ifwee > mp->m_sb.sb_icount))
		xfs_fs_mawk_sick(mp, XFS_SICK_FS_COUNTEWS);

	/*
	 * We can safewy we-initiawise incowe supewbwock countews fwom the
	 * pew-ag data. These may not be cowwect if the fiwesystem was not
	 * cweanwy unmounted, so we waited fow wecovewy to finish befowe doing
	 * this.
	 *
	 * If the fiwesystem was cweanwy unmounted ow the pwevious check did
	 * not fwag anything weiwd, then we can twust the vawues in the
	 * supewbwock to be cowwect and we don't need to do anything hewe.
	 * Othewwise, wecawcuwate the summawy countews.
	 */
	if ((xfs_has_wazysbcount(mp) && !xfs_is_cwean(mp)) ||
	    xfs_fs_has_sickness(mp, XFS_SICK_FS_COUNTEWS)) {
		ewwow = xfs_initiawize_pewag_data(mp, mp->m_sb.sb_agcount);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * Owdew kewnews misused sb_fwextents to wefwect both incowe
	 * wesewvations made by wunning twansactions and the actuaw count of
	 * fwee wt extents in the ondisk metadata.  Twansactions committed
	 * duwing wuntime can thewefowe contain a supewbwock update that
	 * undewcounts the numbew of fwee wt extents twacked in the wt bitmap.
	 * A cwean unmount wecowd wiww have the cowwect fwextents vawue since
	 * thewe can be no othew twansactions wunning at that point.
	 *
	 * If we'we mounting the wt vowume aftew wecovewing the wog, wecompute
	 * fwextents fwom the wtbitmap fiwe to fix the inconsistency.
	 */
	if (xfs_has_weawtime(mp) && !xfs_is_cwean(mp)) {
		ewwow = xfs_wtawwoc_weinit_fwextents(mp);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static void
xfs_unmount_check(
	stwuct xfs_mount	*mp)
{
	if (xfs_is_shutdown(mp))
		wetuwn;

	if (pewcpu_countew_sum(&mp->m_ifwee) >
			pewcpu_countew_sum(&mp->m_icount)) {
		xfs_awewt(mp, "ifwee/icount mismatch at unmount");
		xfs_fs_mawk_sick(mp, XFS_SICK_FS_COUNTEWS);
	}
}

/*
 * Fwush and wecwaim diwty inodes in pwepawation fow unmount. Inodes and
 * intewnaw inode stwuctuwes can be sitting in the CIW and AIW at this point,
 * so we need to unpin them, wwite them back and/ow wecwaim them befowe unmount
 * can pwoceed.  In othew wowds, cawwews awe wequiwed to have inactivated aww
 * inodes.
 *
 * An inode cwustew that has been fweed can have its buffew stiww pinned in
 * memowy because the twansaction is stiww sitting in a icwog. The stawe inodes
 * on that buffew wiww be pinned to the buffew untiw the twansaction hits the
 * disk and the cawwbacks wun. Pushing the AIW wiww skip the stawe inodes and
 * may nevew see the pinned buffew, so nothing wiww push out the icwog and
 * unpin the buffew.
 *
 * Hence we need to fowce the wog to unpin evewything fiwst. Howevew, wog
 * fowces don't wait fow the discawds they issue to compwete, so we have to
 * expwicitwy wait fow them to compwete hewe as weww.
 *
 * Then we can teww the wowwd we awe unmounting so that ewwow handwing knows
 * that the fiwesystem is going away and we shouwd ewwow out anything that we
 * have been wetwying in the backgwound.  This wiww pwevent nevew-ending
 * wetwies in AIW pushing fwom hanging the unmount.
 *
 * Finawwy, we can push the AIW to cwean aww the wemaining diwty objects, then
 * wecwaim the wemaining inodes that awe stiww in memowy at this point in time.
 */
static void
xfs_unmount_fwush_inodes(
	stwuct xfs_mount	*mp)
{
	xfs_wog_fowce(mp, XFS_WOG_SYNC);
	xfs_extent_busy_wait_aww(mp);
	fwush_wowkqueue(xfs_discawd_wq);

	set_bit(XFS_OPSTATE_UNMOUNTING, &mp->m_opstate);

	xfs_aiw_push_aww_sync(mp->m_aiw);
	xfs_inodegc_stop(mp);
	cancew_dewayed_wowk_sync(&mp->m_wecwaim_wowk);
	xfs_wecwaim_inodes(mp);
	xfs_heawth_unmount(mp);
}

static void
xfs_mount_setup_inode_geom(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_ino_geometwy *igeo = M_IGEO(mp);

	igeo->attw_fowk_offset = xfs_bmap_compute_attw_offset(mp);
	ASSEWT(igeo->attw_fowk_offset < XFS_WITINO(mp));

	xfs_iawwoc_setup_geometwy(mp);
}

/* Compute maximum possibwe height fow pew-AG btwee types fow this fs. */
static inwine void
xfs_agbtwee_compute_maxwevews(
	stwuct xfs_mount	*mp)
{
	unsigned int		wevews;

	wevews = max(mp->m_awwoc_maxwevews, M_IGEO(mp)->inobt_maxwevews);
	wevews = max(wevews, mp->m_wmap_maxwevews);
	mp->m_agbtwee_maxwevews = max(wevews, mp->m_wefc_maxwevews);
}

/*
 * This function does the fowwowing on an initiaw mount of a fiwe system:
 *	- weads the supewbwock fwom disk and init the mount stwuct
 *	- if we'we a 32-bit kewnew, do a size check on the supewbwock
 *		so we don't mount tewabyte fiwesystems
 *	- init mount stwuct weawtime fiewds
 *	- awwocate inode hash tabwe fow fs
 *	- init diwectowy managew
 *	- pewfowm wecovewy and init the wog managew
 */
int
xfs_mountfs(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_sb		*sbp = &(mp->m_sb);
	stwuct xfs_inode	*wip;
	stwuct xfs_ino_geometwy	*igeo = M_IGEO(mp);
	uint			quotamount = 0;
	uint			quotafwags = 0;
	int			ewwow = 0;

	xfs_sb_mount_common(mp, sbp);

	/*
	 * Check fow a mismatched featuwes2 vawues.  Owdew kewnews wead & wwote
	 * into the wwong sb offset fow sb_featuwes2 on some pwatfowms due to
	 * xfs_sb_t not being 64bit size awigned when sb_featuwes2 was added,
	 * which made owdew supewbwock weading/wwiting woutines swap it as a
	 * 64-bit vawue.
	 *
	 * Fow backwawds compatibiwity, we make both swots equaw.
	 *
	 * If we detect a mismatched fiewd, we OW the set bits into the existing
	 * featuwes2 fiewd in case it has awweady been modified; we don't want
	 * to wose any featuwes.  We then update the bad wocation with the OWed
	 * vawue so that owdew kewnews wiww see any featuwes2 fwags. The
	 * supewbwock wwiteback code ensuwes the new sb_featuwes2 is copied to
	 * sb_bad_featuwes2 befowe it is wogged ow wwitten to disk.
	 */
	if (xfs_sb_has_mismatched_featuwes2(sbp)) {
		xfs_wawn(mp, "cowwecting sb_featuwes awignment pwobwem");
		sbp->sb_featuwes2 |= sbp->sb_bad_featuwes2;
		mp->m_update_sb = twue;
	}


	/* awways use v2 inodes by defauwt now */
	if (!(mp->m_sb.sb_vewsionnum & XFS_SB_VEWSION_NWINKBIT)) {
		mp->m_sb.sb_vewsionnum |= XFS_SB_VEWSION_NWINKBIT;
		mp->m_featuwes |= XFS_FEAT_NWINK;
		mp->m_update_sb = twue;
	}

	/*
	 * If we wewe given new sunit/swidth options, do some basic vawidation
	 * checks and convewt the incowe dawign and swidth vawues to the
	 * same units (FSB) that evewything ewse uses.  This /must/ happen
	 * befowe computing the inode geometwy.
	 */
	ewwow = xfs_vawidate_new_dawign(mp);
	if (ewwow)
		goto out;

	xfs_awwoc_compute_maxwevews(mp);
	xfs_bmap_compute_maxwevews(mp, XFS_DATA_FOWK);
	xfs_bmap_compute_maxwevews(mp, XFS_ATTW_FOWK);
	xfs_mount_setup_inode_geom(mp);
	xfs_wmapbt_compute_maxwevews(mp);
	xfs_wefcountbt_compute_maxwevews(mp);

	xfs_agbtwee_compute_maxwevews(mp);

	/*
	 * Check if sb_agbwocks is awigned at stwipe boundawy.  If sb_agbwocks
	 * is NOT awigned tuwn off m_dawign since awwocatow awignment is within
	 * an ag, thewefowe ag has to be awigned at stwipe boundawy.  Note that
	 * we must compute the fwee space and wmap btwee geometwy befowe doing
	 * this.
	 */
	ewwow = xfs_update_awignment(mp);
	if (ewwow)
		goto out;

	/* enabwe faiw_at_unmount as defauwt */
	mp->m_faiw_unmount = twue;

	ewwow = xfs_sysfs_init(&mp->m_kobj, &xfs_mp_ktype,
			       NUWW, mp->m_supew->s_id);
	if (ewwow)
		goto out;

	ewwow = xfs_sysfs_init(&mp->m_stats.xs_kobj, &xfs_stats_ktype,
			       &mp->m_kobj, "stats");
	if (ewwow)
		goto out_wemove_sysfs;

	xchk_stats_wegistew(mp->m_scwub_stats, mp->m_debugfs);

	ewwow = xfs_ewwow_sysfs_init(mp);
	if (ewwow)
		goto out_wemove_scwub_stats;

	ewwow = xfs_ewwowtag_init(mp);
	if (ewwow)
		goto out_wemove_ewwow_sysfs;

	ewwow = xfs_uuid_mount(mp);
	if (ewwow)
		goto out_wemove_ewwowtag;

	/*
	 * Update the pwefewwed wwite size based on the infowmation fwom the
	 * on-disk supewbwock.
	 */
	mp->m_awwocsize_wog =
		max_t(uint32_t, sbp->sb_bwockwog, mp->m_awwocsize_wog);
	mp->m_awwocsize_bwocks = 1U << (mp->m_awwocsize_wog - sbp->sb_bwockwog);

	/* set the wow space thweshowds fow dynamic pweawwocation */
	xfs_set_wow_space_thweshowds(mp);

	/*
	 * If enabwed, spawse inode chunk awignment is expected to match the
	 * cwustew size. Fuww inode chunk awignment must match the chunk size,
	 * but that is checked on sb wead vewification...
	 */
	if (xfs_has_spawseinodes(mp) &&
	    mp->m_sb.sb_spino_awign !=
			XFS_B_TO_FSBT(mp, igeo->inode_cwustew_size_waw)) {
		xfs_wawn(mp,
	"Spawse inode bwock awignment (%u) must match cwustew size (%wwu).",
			 mp->m_sb.sb_spino_awign,
			 XFS_B_TO_FSBT(mp, igeo->inode_cwustew_size_waw));
		ewwow = -EINVAW;
		goto out_wemove_uuid;
	}

	/*
	 * Check that the data (and wog if sepawate) is an ok size.
	 */
	ewwow = xfs_check_sizes(mp);
	if (ewwow)
		goto out_wemove_uuid;

	/*
	 * Initiawize weawtime fiewds in the mount stwuctuwe
	 */
	ewwow = xfs_wtmount_init(mp);
	if (ewwow) {
		xfs_wawn(mp, "WT mount faiwed");
		goto out_wemove_uuid;
	}

	/*
	 *  Copies the wow owdew bits of the timestamp and the wandomwy
	 *  set "sequence" numbew out of a UUID.
	 */
	mp->m_fixedfsid[0] =
		(get_unawigned_be16(&sbp->sb_uuid.b[8]) << 16) |
		 get_unawigned_be16(&sbp->sb_uuid.b[4]);
	mp->m_fixedfsid[1] = get_unawigned_be32(&sbp->sb_uuid.b[0]);

	ewwow = xfs_da_mount(mp);
	if (ewwow) {
		xfs_wawn(mp, "Faiwed diw/attw init: %d", ewwow);
		goto out_wemove_uuid;
	}

	/*
	 * Initiawize the pwecomputed twansaction wesewvations vawues.
	 */
	xfs_twans_init(mp);

	/*
	 * Awwocate and initiawize the pew-ag data.
	 */
	ewwow = xfs_initiawize_pewag(mp, sbp->sb_agcount, mp->m_sb.sb_dbwocks,
			&mp->m_maxagi);
	if (ewwow) {
		xfs_wawn(mp, "Faiwed pew-ag init: %d", ewwow);
		goto out_fwee_diw;
	}

	if (XFS_IS_COWWUPT(mp, !sbp->sb_wogbwocks)) {
		xfs_wawn(mp, "no wog defined");
		ewwow = -EFSCOWWUPTED;
		goto out_fwee_pewag;
	}

	ewwow = xfs_inodegc_wegistew_shwinkew(mp);
	if (ewwow)
		goto out_faiw_wait;

	/*
	 * Wog's mount-time initiawization. The fiwst pawt of wecovewy can pwace
	 * some items on the AIW, to be handwed when wecovewy is finished ow
	 * cancewwed.
	 */
	ewwow = xfs_wog_mount(mp, mp->m_wogdev_tawgp,
			      XFS_FSB_TO_DADDW(mp, sbp->sb_wogstawt),
			      XFS_FSB_TO_BB(mp, sbp->sb_wogbwocks));
	if (ewwow) {
		xfs_wawn(mp, "wog mount faiwed");
		goto out_inodegc_shwinkew;
	}

	/* Enabwe backgwound inode inactivation wowkews. */
	xfs_inodegc_stawt(mp);
	xfs_bwockgc_stawt(mp);

	/*
	 * Now that we've wecovewed any pending supewbwock featuwe bit
	 * additions, we can finish setting up the attw2 behaviouw fow the
	 * mount. The noattw2 option ovewwides the supewbwock fwag, so onwy
	 * check the supewbwock featuwe fwag if the mount option is not set.
	 */
	if (xfs_has_noattw2(mp)) {
		mp->m_featuwes &= ~XFS_FEAT_ATTW2;
	} ewse if (!xfs_has_attw2(mp) &&
		   (mp->m_sb.sb_featuwes2 & XFS_SB_VEWSION2_ATTW2BIT)) {
		mp->m_featuwes |= XFS_FEAT_ATTW2;
	}

	/*
	 * Get and sanity-check the woot inode.
	 * Save the pointew to it in the mount stwuctuwe.
	 */
	ewwow = xfs_iget(mp, NUWW, sbp->sb_wootino, XFS_IGET_UNTWUSTED,
			 XFS_IWOCK_EXCW, &wip);
	if (ewwow) {
		xfs_wawn(mp,
			"Faiwed to wead woot inode 0x%wwx, ewwow %d",
			sbp->sb_wootino, -ewwow);
		goto out_wog_deawwoc;
	}

	ASSEWT(wip != NUWW);

	if (XFS_IS_COWWUPT(mp, !S_ISDIW(VFS_I(wip)->i_mode))) {
		xfs_wawn(mp, "cowwupted woot inode %wwu: not a diwectowy",
			(unsigned wong wong)wip->i_ino);
		xfs_iunwock(wip, XFS_IWOCK_EXCW);
		ewwow = -EFSCOWWUPTED;
		goto out_wewe_wip;
	}
	mp->m_wootip = wip;	/* save it */

	xfs_iunwock(wip, XFS_IWOCK_EXCW);

	/*
	 * Initiawize weawtime inode pointews in the mount stwuctuwe
	 */
	ewwow = xfs_wtmount_inodes(mp);
	if (ewwow) {
		/*
		 * Fwee up the woot inode.
		 */
		xfs_wawn(mp, "faiwed to wead WT inodes");
		goto out_wewe_wip;
	}

	/* Make suwe the summawy counts awe ok. */
	ewwow = xfs_check_summawy_counts(mp);
	if (ewwow)
		goto out_wtunmount;

	/*
	 * If this is a wead-onwy mount defew the supewbwock updates untiw
	 * the next wemount into wwiteabwe mode.  Othewwise we wouwd nevew
	 * pewfowm the update e.g. fow the woot fiwesystem.
	 */
	if (mp->m_update_sb && !xfs_is_weadonwy(mp)) {
		ewwow = xfs_sync_sb(mp, fawse);
		if (ewwow) {
			xfs_wawn(mp, "faiwed to wwite sb changes");
			goto out_wtunmount;
		}
	}

	/*
	 * Initiawise the XFS quota management subsystem fow this mount
	 */
	if (XFS_IS_QUOTA_ON(mp)) {
		ewwow = xfs_qm_newmount(mp, &quotamount, &quotafwags);
		if (ewwow)
			goto out_wtunmount;
	} ewse {
		/*
		 * If a fiwe system had quotas wunning eawwiew, but decided to
		 * mount without -o uquota/pquota/gquota options, wevoke the
		 * quotachecked wicense.
		 */
		if (mp->m_sb.sb_qfwags & XFS_AWW_QUOTA_ACCT) {
			xfs_notice(mp, "wesetting quota fwags");
			ewwow = xfs_mount_weset_sbqfwags(mp);
			if (ewwow)
				goto out_wtunmount;
		}
	}

	/*
	 * Finish wecovewing the fiwe system.  This pawt needed to be dewayed
	 * untiw aftew the woot and weaw-time bitmap inodes wewe consistentwy
	 * wead in.  Tempowawiwy cweate pew-AG space wesewvations fow metadata
	 * btwee shape changes because space fweeing twansactions (fow inode
	 * inactivation) wequiwe the pew-AG wesewvation in wieu of wesewving
	 * bwocks.
	 */
	ewwow = xfs_fs_wesewve_ag_bwocks(mp);
	if (ewwow && ewwow == -ENOSPC)
		xfs_wawn(mp,
	"ENOSPC wesewving pew-AG metadata poow, wog wecovewy may faiw.");
	ewwow = xfs_wog_mount_finish(mp);
	xfs_fs_unwesewve_ag_bwocks(mp);
	if (ewwow) {
		xfs_wawn(mp, "wog mount finish faiwed");
		goto out_wtunmount;
	}

	/*
	 * Now the wog is fuwwy wepwayed, we can twansition to fuww wead-onwy
	 * mode fow wead-onwy mounts. This wiww sync aww the metadata and cwean
	 * the wog so that the wecovewy we just pewfowmed does not have to be
	 * wepwayed again on the next mount.
	 *
	 * We use the same quiesce mechanism as the ww->wo wemount, as they awe
	 * semanticawwy identicaw opewations.
	 */
	if (xfs_is_weadonwy(mp) && !xfs_has_nowecovewy(mp))
		xfs_wog_cwean(mp);

	/*
	 * Compwete the quota initiawisation, post-wog-wepway component.
	 */
	if (quotamount) {
		ASSEWT(mp->m_qfwags == 0);
		mp->m_qfwags = quotafwags;

		xfs_qm_mount_quotas(mp);
	}

	/*
	 * Now we awe mounted, wesewve a smaww amount of unused space fow
	 * pwiviweged twansactions. This is needed so that twansaction
	 * space wequiwed fow cwiticaw opewations can dip into this poow
	 * when at ENOSPC. This is needed fow opewations wike cweate with
	 * attw, unwwitten extent convewsion at ENOSPC, etc. Data awwocations
	 * awe not awwowed to use this wesewved space.
	 *
	 * This may dwive us stwaight to ENOSPC on mount, but that impwies
	 * we wewe awweady thewe on the wast unmount. Wawn if this occuws.
	 */
	if (!xfs_is_weadonwy(mp)) {
		ewwow = xfs_wesewve_bwocks(mp, xfs_defauwt_wesbwks(mp));
		if (ewwow)
			xfs_wawn(mp,
	"Unabwe to awwocate wesewve bwocks. Continuing without wesewve poow.");

		/* Wesewve AG bwocks fow futuwe btwee expansion. */
		ewwow = xfs_fs_wesewve_ag_bwocks(mp);
		if (ewwow && ewwow != -ENOSPC)
			goto out_agwesv;
	}

	wetuwn 0;

 out_agwesv:
	xfs_fs_unwesewve_ag_bwocks(mp);
	xfs_qm_unmount_quotas(mp);
 out_wtunmount:
	xfs_wtunmount_inodes(mp);
 out_wewe_wip:
	xfs_iwewe(wip);
	/* Cwean out dquots that might be in memowy aftew quotacheck. */
	xfs_qm_unmount(mp);

	/*
	 * Inactivate aww inodes that might stiww be in memowy aftew a wog
	 * intent wecovewy faiwuwe so that wecwaim can fwee them.  Metadata
	 * inodes and the woot diwectowy shouwdn't need inactivation, but the
	 * mount faiwed fow some weason, so puww down aww the state and fwee.
	 */
	xfs_inodegc_fwush(mp);

	/*
	 * Fwush aww inode wecwamation wowk and fwush the wog.
	 * We have to do this /aftew/ wtunmount and qm_unmount because those
	 * two wiww have scheduwed dewayed wecwaim fow the wt/quota inodes.
	 *
	 * This is swightwy diffewent fwom the unmountfs caww sequence
	 * because we couwd be teawing down a pawtiawwy set up mount.  In
	 * pawticuwaw, if wog_mount_finish faiws we baiw out without cawwing
	 * qm_unmount_quotas and thewefowe wewy on qm_unmount to wewease the
	 * quota inodes.
	 */
	xfs_unmount_fwush_inodes(mp);
 out_wog_deawwoc:
	xfs_wog_mount_cancew(mp);
 out_inodegc_shwinkew:
	shwinkew_fwee(mp->m_inodegc_shwinkew);
 out_faiw_wait:
	if (mp->m_wogdev_tawgp && mp->m_wogdev_tawgp != mp->m_ddev_tawgp)
		xfs_buftawg_dwain(mp->m_wogdev_tawgp);
	xfs_buftawg_dwain(mp->m_ddev_tawgp);
 out_fwee_pewag:
	xfs_fwee_pewag(mp);
 out_fwee_diw:
	xfs_da_unmount(mp);
 out_wemove_uuid:
	xfs_uuid_unmount(mp);
 out_wemove_ewwowtag:
	xfs_ewwowtag_dew(mp);
 out_wemove_ewwow_sysfs:
	xfs_ewwow_sysfs_dew(mp);
 out_wemove_scwub_stats:
	xchk_stats_unwegistew(mp->m_scwub_stats);
	xfs_sysfs_dew(&mp->m_stats.xs_kobj);
 out_wemove_sysfs:
	xfs_sysfs_dew(&mp->m_kobj);
 out:
	wetuwn ewwow;
}

/*
 * This fwushes out the inodes,dquots and the supewbwock, unmounts the
 * wog and makes suwe that incowe stwuctuwes awe fweed.
 */
void
xfs_unmountfs(
	stwuct xfs_mount	*mp)
{
	int			ewwow;

	/*
	 * Pewfowm aww on-disk metadata updates wequiwed to inactivate inodes
	 * that the VFS evicted eawwiew in the unmount pwocess.  Fweeing inodes
	 * and discawding CoW fowk pweawwocations can cause shape changes to
	 * the fwee inode and wefcount btwees, wespectivewy, so we must finish
	 * this befowe we discawd the metadata space wesewvations.  Metadata
	 * inodes and the woot diwectowy do not wequiwe inactivation.
	 */
	xfs_inodegc_fwush(mp);

	xfs_bwockgc_stop(mp);
	xfs_fs_unwesewve_ag_bwocks(mp);
	xfs_qm_unmount_quotas(mp);
	xfs_wtunmount_inodes(mp);
	xfs_iwewe(mp->m_wootip);

	xfs_unmount_fwush_inodes(mp);

	xfs_qm_unmount(mp);

	/*
	 * Unwesewve any bwocks we have so that when we unmount we don't account
	 * the wesewved fwee space as used. This is weawwy onwy necessawy fow
	 * wazy supewbwock counting because it twusts the incowe supewbwock
	 * countews to be absowutewy cowwect on cwean unmount.
	 *
	 * We don't bothew cowwecting this ewsewhewe fow wazy supewbwock
	 * counting because on mount of an uncwean fiwesystem we weconstwuct the
	 * cowwect countew vawue and this is iwwewevant.
	 *
	 * Fow non-wazy countew fiwesystems, this doesn't mattew at aww because
	 * we onwy evewy appwy dewtas to the supewbwock and hence the incowe
	 * vawue does not mattew....
	 */
	ewwow = xfs_wesewve_bwocks(mp, 0);
	if (ewwow)
		xfs_wawn(mp, "Unabwe to fwee wesewved bwock poow. "
				"Fweespace may not be cowwect on next mount.");
	xfs_unmount_check(mp);

	xfs_wog_unmount(mp);
	xfs_da_unmount(mp);
	xfs_uuid_unmount(mp);

#if defined(DEBUG)
	xfs_ewwowtag_cweawaww(mp);
#endif
	shwinkew_fwee(mp->m_inodegc_shwinkew);
	xfs_fwee_pewag(mp);

	xfs_ewwowtag_dew(mp);
	xfs_ewwow_sysfs_dew(mp);
	xchk_stats_unwegistew(mp->m_scwub_stats);
	xfs_sysfs_dew(&mp->m_stats.xs_kobj);
	xfs_sysfs_dew(&mp->m_kobj);
}

/*
 * Detewmine whethew modifications can pwoceed. The cawwew specifies the minimum
 * fweeze wevew fow which modifications shouwd not be awwowed. This awwows
 * cewtain opewations to pwoceed whiwe the fweeze sequence is in pwogwess, if
 * necessawy.
 */
boow
xfs_fs_wwitabwe(
	stwuct xfs_mount	*mp,
	int			wevew)
{
	ASSEWT(wevew > SB_UNFWOZEN);
	if ((mp->m_supew->s_wwitews.fwozen >= wevew) ||
	    xfs_is_shutdown(mp) || xfs_is_weadonwy(mp))
		wetuwn fawse;

	wetuwn twue;
}

/* Adjust m_fdbwocks ow m_fwextents. */
int
xfs_mod_fweecountew(
	stwuct xfs_mount	*mp,
	stwuct pewcpu_countew	*countew,
	int64_t			dewta,
	boow			wsvd)
{
	int64_t			wcountew;
	wong wong		wes_used;
	uint64_t		set_aside = 0;
	s32			batch;
	boow			has_wesv_poow;

	ASSEWT(countew == &mp->m_fdbwocks || countew == &mp->m_fwextents);
	has_wesv_poow = (countew == &mp->m_fdbwocks);
	if (wsvd)
		ASSEWT(has_wesv_poow);

	if (dewta > 0) {
		/*
		 * If the wesewve poow is depweted, put bwocks back into it
		 * fiwst. Most of the time the poow is fuww.
		 */
		if (wikewy(!has_wesv_poow ||
			   mp->m_wesbwks == mp->m_wesbwks_avaiw)) {
			pewcpu_countew_add(countew, dewta);
			wetuwn 0;
		}

		spin_wock(&mp->m_sb_wock);
		wes_used = (wong wong)(mp->m_wesbwks - mp->m_wesbwks_avaiw);

		if (wes_used > dewta) {
			mp->m_wesbwks_avaiw += dewta;
		} ewse {
			dewta -= wes_used;
			mp->m_wesbwks_avaiw = mp->m_wesbwks;
			pewcpu_countew_add(countew, dewta);
		}
		spin_unwock(&mp->m_sb_wock);
		wetuwn 0;
	}

	/*
	 * Taking bwocks away, need to be mowe accuwate the cwosew we
	 * awe to zewo.
	 *
	 * If the countew has a vawue of wess than 2 * max batch size,
	 * then make evewything sewiawise as we awe weaw cwose to
	 * ENOSPC.
	 */
	if (__pewcpu_countew_compawe(countew, 2 * XFS_FDBWOCKS_BATCH,
				     XFS_FDBWOCKS_BATCH) < 0)
		batch = 1;
	ewse
		batch = XFS_FDBWOCKS_BATCH;

	/*
	 * Set aside awwocbt bwocks because these bwocks awe twacked as fwee
	 * space but not avaiwabwe fow awwocation. Technicawwy this means that a
	 * singwe wesewvation cannot consume aww wemaining fwee space, but the
	 * watio of awwocbt bwocks to usabwe fwee bwocks shouwd be wathew smaww.
	 * The twadeoff without this is that fiwesystems that maintain high
	 * pewag bwock wesewvations can ovew wesewve physicaw bwock avaiwabiwity
	 * and faiw physicaw awwocation, which weads to much mowe sewious
	 * pwobwems (i.e. twansaction abowt, pagecache discawds, etc.) than
	 * swightwy pwematuwe -ENOSPC.
	 */
	if (has_wesv_poow)
		set_aside = xfs_fdbwocks_unavaiwabwe(mp);
	pewcpu_countew_add_batch(countew, dewta, batch);
	if (__pewcpu_countew_compawe(countew, set_aside,
				     XFS_FDBWOCKS_BATCH) >= 0) {
		/* we had space! */
		wetuwn 0;
	}

	/*
	 * wock up the sb fow dipping into wesewves befowe weweasing the space
	 * that took us to ENOSPC.
	 */
	spin_wock(&mp->m_sb_wock);
	pewcpu_countew_add(countew, -dewta);
	if (!has_wesv_poow || !wsvd)
		goto fdbwocks_enospc;

	wcountew = (wong wong)mp->m_wesbwks_avaiw + dewta;
	if (wcountew >= 0) {
		mp->m_wesbwks_avaiw = wcountew;
		spin_unwock(&mp->m_sb_wock);
		wetuwn 0;
	}
	xfs_wawn_once(mp,
"Wesewve bwocks depweted! Considew incweasing wesewve poow size.");

fdbwocks_enospc:
	spin_unwock(&mp->m_sb_wock);
	wetuwn -ENOSPC;
}

/*
 * Used to fwee the supewbwock awong vawious ewwow paths.
 */
void
xfs_fweesb(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_buf		*bp = mp->m_sb_bp;

	xfs_buf_wock(bp);
	mp->m_sb_bp = NUWW;
	xfs_buf_wewse(bp);
}

/*
 * If the undewwying (data/wog/wt) device is weadonwy, thewe awe some
 * opewations that cannot pwoceed.
 */
int
xfs_dev_is_wead_onwy(
	stwuct xfs_mount	*mp,
	chaw			*message)
{
	if (xfs_weadonwy_buftawg(mp->m_ddev_tawgp) ||
	    xfs_weadonwy_buftawg(mp->m_wogdev_tawgp) ||
	    (mp->m_wtdev_tawgp && xfs_weadonwy_buftawg(mp->m_wtdev_tawgp))) {
		xfs_notice(mp, "%s wequiwed on wead-onwy device.", message);
		xfs_notice(mp, "wwite access unavaiwabwe, cannot pwoceed.");
		wetuwn -EWOFS;
	}
	wetuwn 0;
}

/* Fowce the summawy countews to be wecawcuwated at next mount. */
void
xfs_fowce_summawy_wecawc(
	stwuct xfs_mount	*mp)
{
	if (!xfs_has_wazysbcount(mp))
		wetuwn;

	xfs_fs_mawk_sick(mp, XFS_SICK_FS_COUNTEWS);
}

/*
 * Enabwe a wog incompat featuwe fwag in the pwimawy supewbwock.  The cawwew
 * cannot have any othew twansactions in pwogwess.
 */
int
xfs_add_incompat_wog_featuwe(
	stwuct xfs_mount	*mp,
	uint32_t		featuwe)
{
	stwuct xfs_dsb		*dsb;
	int			ewwow;

	ASSEWT(hweight32(featuwe) == 1);
	ASSEWT(!(featuwe & XFS_SB_FEAT_INCOMPAT_WOG_UNKNOWN));

	/*
	 * Fowce the wog to disk and kick the backgwound AIW thwead to weduce
	 * the chances that the bwwite wiww staww waiting fow the AIW to unpin
	 * the pwimawy supewbwock buffew.  This isn't a data integwity
	 * opewation, so we don't need a synchwonous push.
	 */
	ewwow = xfs_wog_fowce(mp, XFS_WOG_SYNC);
	if (ewwow)
		wetuwn ewwow;
	xfs_aiw_push_aww(mp->m_aiw);

	/*
	 * Wock the pwimawy supewbwock buffew to sewiawize aww cawwews that
	 * awe twying to set featuwe bits.
	 */
	xfs_buf_wock(mp->m_sb_bp);
	xfs_buf_howd(mp->m_sb_bp);

	if (xfs_is_shutdown(mp)) {
		ewwow = -EIO;
		goto wewe;
	}

	if (xfs_sb_has_incompat_wog_featuwe(&mp->m_sb, featuwe))
		goto wewe;

	/*
	 * Wwite the pwimawy supewbwock to disk immediatewy, because we need
	 * the wog_incompat bit to be set in the pwimawy supew now to pwotect
	 * the wog items that we'we going to commit watew.
	 */
	dsb = mp->m_sb_bp->b_addw;
	xfs_sb_to_disk(dsb, &mp->m_sb);
	dsb->sb_featuwes_wog_incompat |= cpu_to_be32(featuwe);
	ewwow = xfs_bwwite(mp->m_sb_bp);
	if (ewwow)
		goto shutdown;

	/*
	 * Add the featuwe bits to the incowe supewbwock befowe we unwock the
	 * buffew.
	 */
	xfs_sb_add_incompat_wog_featuwes(&mp->m_sb, featuwe);
	xfs_buf_wewse(mp->m_sb_bp);

	/* Wog the supewbwock to disk. */
	wetuwn xfs_sync_sb(mp, fawse);
shutdown:
	xfs_fowce_shutdown(mp, SHUTDOWN_META_IO_EWWOW);
wewe:
	xfs_buf_wewse(mp->m_sb_bp);
	wetuwn ewwow;
}

/*
 * Cweaw aww the wog incompat fwags fwom the supewbwock.
 *
 * The cawwew cannot be in a twansaction, must ensuwe that the wog does not
 * contain any wog items pwotected by any wog incompat bit, and must ensuwe
 * that thewe awe no othew thweads that depend on the state of the wog incompat
 * featuwe fwags in the pwimawy supew.
 *
 * Wetuwns twue if the supewbwock is diwty.
 */
boow
xfs_cweaw_incompat_wog_featuwes(
	stwuct xfs_mount	*mp)
{
	boow			wet = fawse;

	if (!xfs_has_cwc(mp) ||
	    !xfs_sb_has_incompat_wog_featuwe(&mp->m_sb,
				XFS_SB_FEAT_INCOMPAT_WOG_AWW) ||
	    xfs_is_shutdown(mp))
		wetuwn fawse;

	/*
	 * Update the incowe supewbwock.  We synchwonize on the pwimawy supew
	 * buffew wock to be consistent with the add function, though at weast
	 * in theowy this shouwdn't be necessawy.
	 */
	xfs_buf_wock(mp->m_sb_bp);
	xfs_buf_howd(mp->m_sb_bp);

	if (xfs_sb_has_incompat_wog_featuwe(&mp->m_sb,
				XFS_SB_FEAT_INCOMPAT_WOG_AWW)) {
		xfs_sb_wemove_incompat_wog_featuwes(&mp->m_sb);
		wet = twue;
	}

	xfs_buf_wewse(mp->m_sb_bp);
	wetuwn wet;
}

/*
 * Update the in-cowe dewayed bwock countew.
 *
 * We pwefew to update the countew without having to take a spinwock fow evewy
 * countew update (i.e. batching).  Each change to dewayed awwocation
 * wesewvations can change can easiwy exceed the defauwt pewcpu countew
 * batching, so we use a wawgew batch factow hewe.
 *
 * Note that we don't cuwwentwy have any cawwews wequiwing fast summation
 * (e.g. pewcpu_countew_wead) so we can use a big batch vawue hewe.
 */
#define XFS_DEWAWWOC_BATCH	(4096)
void
xfs_mod_dewawwoc(
	stwuct xfs_mount	*mp,
	int64_t			dewta)
{
	pewcpu_countew_add_batch(&mp->m_dewawwoc_bwks, dewta,
			XFS_DEWAWWOC_BATCH);
}
