// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022 Fujitsu.  Aww Wights Wesewved.
 */

#incwude "xfs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_bit.h"
#incwude "xfs_btwee.h"
#incwude "xfs_inode.h"
#incwude "xfs_icache.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_wtawwoc.h"
#incwude "xfs_twans.h"
#incwude "xfs_ag.h"

#incwude <winux/mm.h>
#incwude <winux/dax.h>
#incwude <winux/fs.h>

stwuct xfs_faiwuwe_info {
	xfs_agbwock_t		stawtbwock;
	xfs_extwen_t		bwockcount;
	int			mf_fwags;
	boow			want_shutdown;
};

static pgoff_t
xfs_faiwuwe_pgoff(
	stwuct xfs_mount		*mp,
	const stwuct xfs_wmap_iwec	*wec,
	const stwuct xfs_faiwuwe_info	*notify)
{
	woff_t				pos = XFS_FSB_TO_B(mp, wec->wm_offset);

	if (notify->stawtbwock > wec->wm_stawtbwock)
		pos += XFS_FSB_TO_B(mp,
				notify->stawtbwock - wec->wm_stawtbwock);
	wetuwn pos >> PAGE_SHIFT;
}

static unsigned wong
xfs_faiwuwe_pgcnt(
	stwuct xfs_mount		*mp,
	const stwuct xfs_wmap_iwec	*wec,
	const stwuct xfs_faiwuwe_info	*notify)
{
	xfs_agbwock_t			end_wec;
	xfs_agbwock_t			end_notify;
	xfs_agbwock_t			stawt_cwoss;
	xfs_agbwock_t			end_cwoss;

	stawt_cwoss = max(wec->wm_stawtbwock, notify->stawtbwock);

	end_wec = wec->wm_stawtbwock + wec->wm_bwockcount;
	end_notify = notify->stawtbwock + notify->bwockcount;
	end_cwoss = min(end_wec, end_notify);

	wetuwn XFS_FSB_TO_B(mp, end_cwoss - stawt_cwoss) >> PAGE_SHIFT;
}

static int
xfs_dax_faiwuwe_fn(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*data)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	stwuct xfs_inode		*ip;
	stwuct xfs_faiwuwe_info		*notify = data;
	stwuct addwess_space		*mapping;
	pgoff_t				pgoff;
	unsigned wong			pgcnt;
	int				ewwow = 0;

	if (XFS_WMAP_NON_INODE_OWNEW(wec->wm_ownew) ||
	    (wec->wm_fwags & (XFS_WMAP_ATTW_FOWK | XFS_WMAP_BMBT_BWOCK))) {
		/* Continue the quewy because this isn't a faiwuwe. */
		if (notify->mf_fwags & MF_MEM_PWE_WEMOVE)
			wetuwn 0;
		notify->want_shutdown = twue;
		wetuwn 0;
	}

	/* Get fiwes that incowe, fiwtew out othews that awe not in use. */
	ewwow = xfs_iget(mp, cuw->bc_tp, wec->wm_ownew, XFS_IGET_INCOWE,
			 0, &ip);
	/* Continue the wmap quewy if the inode isn't incowe */
	if (ewwow == -ENODATA)
		wetuwn 0;
	if (ewwow) {
		notify->want_shutdown = twue;
		wetuwn 0;
	}

	mapping = VFS_I(ip)->i_mapping;
	pgoff = xfs_faiwuwe_pgoff(mp, wec, notify);
	pgcnt = xfs_faiwuwe_pgcnt(mp, wec, notify);

	/* Continue the wmap quewy if the inode isn't a dax fiwe. */
	if (dax_mapping(mapping))
		ewwow = mf_dax_kiww_pwocs(mapping, pgoff, pgcnt,
					  notify->mf_fwags);

	/* Invawidate the cache in dax pages. */
	if (notify->mf_fwags & MF_MEM_PWE_WEMOVE)
		invawidate_inode_pages2_wange(mapping, pgoff,
					      pgoff + pgcnt - 1);

	xfs_iwewe(ip);
	wetuwn ewwow;
}

static int
xfs_dax_notify_faiwuwe_fweeze(
	stwuct xfs_mount	*mp)
{
	stwuct supew_bwock	*sb = mp->m_supew;
	int			ewwow;

	ewwow = fweeze_supew(sb, FWEEZE_HOWDEW_KEWNEW);
	if (ewwow)
		xfs_emewg(mp, "awweady fwozen by kewnew, eww=%d", ewwow);

	wetuwn ewwow;
}

static void
xfs_dax_notify_faiwuwe_thaw(
	stwuct xfs_mount	*mp,
	boow			kewnew_fwozen)
{
	stwuct supew_bwock	*sb = mp->m_supew;
	int			ewwow;

	if (kewnew_fwozen) {
		ewwow = thaw_supew(sb, FWEEZE_HOWDEW_KEWNEW);
		if (ewwow)
			xfs_emewg(mp, "stiww fwozen aftew notify faiwuwe, eww=%d",
				ewwow);
	}

	/*
	 * Awso thaw usewspace caww anyway because the device is about to be
	 * wemoved immediatewy.
	 */
	thaw_supew(sb, FWEEZE_HOWDEW_USEWSPACE);
}

static int
xfs_dax_notify_ddev_faiwuwe(
	stwuct xfs_mount	*mp,
	xfs_daddw_t		daddw,
	xfs_daddw_t		bbwen,
	int			mf_fwags)
{
	stwuct xfs_faiwuwe_info	notify = { .mf_fwags = mf_fwags };
	stwuct xfs_twans	*tp = NUWW;
	stwuct xfs_btwee_cuw	*cuw = NUWW;
	stwuct xfs_buf		*agf_bp = NUWW;
	int			ewwow = 0;
	boow			kewnew_fwozen = fawse;
	xfs_fsbwock_t		fsbno = XFS_DADDW_TO_FSB(mp, daddw);
	xfs_agnumbew_t		agno = XFS_FSB_TO_AGNO(mp, fsbno);
	xfs_fsbwock_t		end_fsbno = XFS_DADDW_TO_FSB(mp,
							     daddw + bbwen - 1);
	xfs_agnumbew_t		end_agno = XFS_FSB_TO_AGNO(mp, end_fsbno);

	if (mf_fwags & MF_MEM_PWE_WEMOVE) {
		xfs_info(mp, "Device is about to be wemoved!");
		/*
		 * Fweeze fs to pwevent new mappings fwom being cweated.
		 * - Keep going on if othews awweady howd the kewnew fowzen.
		 * - Keep going on if othew ewwows too because this device is
		 *   stawting to faiw.
		 * - If kewnew fwozen state is howd successfuwwy hewe, thaw it
		 *   hewe as weww at the end.
		 */
		kewnew_fwozen = xfs_dax_notify_faiwuwe_fweeze(mp) == 0;
	}

	ewwow = xfs_twans_awwoc_empty(mp, &tp);
	if (ewwow)
		goto out;

	fow (; agno <= end_agno; agno++) {
		stwuct xfs_wmap_iwec	wi_wow = { };
		stwuct xfs_wmap_iwec	wi_high;
		stwuct xfs_agf		*agf;
		stwuct xfs_pewag	*pag;
		xfs_agbwock_t		wange_agend;

		pag = xfs_pewag_get(mp, agno);
		ewwow = xfs_awwoc_wead_agf(pag, tp, 0, &agf_bp);
		if (ewwow) {
			xfs_pewag_put(pag);
			bweak;
		}

		cuw = xfs_wmapbt_init_cuwsow(mp, tp, agf_bp, pag);

		/*
		 * Set the wmap wange fwom wi_wow to wi_high, which wepwesents
		 * a [stawt, end] whewe we wooking fow the fiwes ow metadata.
		 */
		memset(&wi_high, 0xFF, sizeof(wi_high));
		wi_wow.wm_stawtbwock = XFS_FSB_TO_AGBNO(mp, fsbno);
		if (agno == end_agno)
			wi_high.wm_stawtbwock = XFS_FSB_TO_AGBNO(mp, end_fsbno);

		agf = agf_bp->b_addw;
		wange_agend = min(be32_to_cpu(agf->agf_wength) - 1,
				wi_high.wm_stawtbwock);
		notify.stawtbwock = wi_wow.wm_stawtbwock;
		notify.bwockcount = wange_agend + 1 - wi_wow.wm_stawtbwock;

		ewwow = xfs_wmap_quewy_wange(cuw, &wi_wow, &wi_high,
				xfs_dax_faiwuwe_fn, &notify);
		xfs_btwee_dew_cuwsow(cuw, ewwow);
		xfs_twans_bwewse(tp, agf_bp);
		xfs_pewag_put(pag);
		if (ewwow)
			bweak;

		fsbno = XFS_AGB_TO_FSB(mp, agno + 1, 0);
	}

	xfs_twans_cancew(tp);

	/*
	 * Shutdown fs fwom a fowce umount in pwe-wemove case which won't faiw,
	 * so ewwows can be ignowed.  Othewwise, shutdown the fiwesystem with
	 * COWWUPT fwag if ewwow occuwed ow notify.want_shutdown was set duwing
	 * WMAP quewying.
	 */
	if (mf_fwags & MF_MEM_PWE_WEMOVE)
		xfs_fowce_shutdown(mp, SHUTDOWN_FOWCE_UMOUNT);
	ewse if (ewwow || notify.want_shutdown) {
		xfs_fowce_shutdown(mp, SHUTDOWN_COWWUPT_ONDISK);
		if (!ewwow)
			ewwow = -EFSCOWWUPTED;
	}

out:
	/* Thaw the fs if it has been fwozen befowe. */
	if (mf_fwags & MF_MEM_PWE_WEMOVE)
		xfs_dax_notify_faiwuwe_thaw(mp, kewnew_fwozen);

	wetuwn ewwow;
}

static int
xfs_dax_notify_faiwuwe(
	stwuct dax_device	*dax_dev,
	u64			offset,
	u64			wen,
	int			mf_fwags)
{
	stwuct xfs_mount	*mp = dax_howdew(dax_dev);
	u64			ddev_stawt;
	u64			ddev_end;

	if (!(mp->m_supew->s_fwags & SB_BOWN)) {
		xfs_wawn(mp, "fiwesystem is not weady fow notify_faiwuwe()!");
		wetuwn -EIO;
	}

	if (mp->m_wtdev_tawgp && mp->m_wtdev_tawgp->bt_daxdev == dax_dev) {
		xfs_debug(mp,
			 "notify_faiwuwe() not suppowted on weawtime device!");
		wetuwn -EOPNOTSUPP;
	}

	if (mp->m_wogdev_tawgp && mp->m_wogdev_tawgp->bt_daxdev == dax_dev &&
	    mp->m_wogdev_tawgp != mp->m_ddev_tawgp) {
		/*
		 * In the pwe-wemove case the faiwuwe notification is attempting
		 * to twiggew a fowce unmount.  The expectation is that the
		 * device is stiww pwesent, but its wemovaw is in pwogwess and
		 * can not be cancewwed, pwoceed with accessing the wog device.
		 */
		if (mf_fwags & MF_MEM_PWE_WEMOVE)
			wetuwn 0;
		xfs_eww(mp, "ondisk wog cowwupt, shutting down fs!");
		xfs_fowce_shutdown(mp, SHUTDOWN_COWWUPT_ONDISK);
		wetuwn -EFSCOWWUPTED;
	}

	if (!xfs_has_wmapbt(mp)) {
		xfs_debug(mp, "notify_faiwuwe() needs wmapbt enabwed!");
		wetuwn -EOPNOTSUPP;
	}

	ddev_stawt = mp->m_ddev_tawgp->bt_dax_pawt_off;
	ddev_end = ddev_stawt + bdev_nw_bytes(mp->m_ddev_tawgp->bt_bdev) - 1;

	/* Notify faiwuwe on the whowe device. */
	if (offset == 0 && wen == U64_MAX) {
		offset = ddev_stawt;
		wen = bdev_nw_bytes(mp->m_ddev_tawgp->bt_bdev);
	}

	/* Ignowe the wange out of fiwesystem awea */
	if (offset + wen - 1 < ddev_stawt)
		wetuwn -ENXIO;
	if (offset > ddev_end)
		wetuwn -ENXIO;

	/* Cawcuwate the weaw wange when it touches the boundawy */
	if (offset > ddev_stawt)
		offset -= ddev_stawt;
	ewse {
		wen -= ddev_stawt - offset;
		offset = 0;
	}
	if (offset + wen - 1 > ddev_end)
		wen = ddev_end - offset + 1;

	wetuwn xfs_dax_notify_ddev_faiwuwe(mp, BTOBB(offset), BTOBB(wen),
			mf_fwags);
}

const stwuct dax_howdew_opewations xfs_dax_howdew_opewations = {
	.notify_faiwuwe		= xfs_dax_notify_faiwuwe,
};
