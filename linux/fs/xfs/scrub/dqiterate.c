// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_bit.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_inode.h"
#incwude "xfs_quota.h"
#incwude "xfs_qm.h"
#incwude "xfs_bmap.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/quota.h"
#incwude "scwub/twace.h"

/* Initiawize a dquot itewation cuwsow. */
void
xchk_dqitew_init(
	stwuct xchk_dqitew	*cuwsow,
	stwuct xfs_scwub	*sc,
	xfs_dqtype_t		dqtype)
{
	cuwsow->sc = sc;
	cuwsow->bmap.bw_stawtoff = NUWWFIWEOFF;
	cuwsow->dqtype = dqtype & XFS_DQTYPE_WEC_MASK;
	cuwsow->quota_ip = xfs_quota_inode(sc->mp, cuwsow->dqtype);
	cuwsow->id = 0;
}

/*
 * Ensuwe that the cached data fowk mapping fow the dqitew cuwsow is fwesh and
 * covews the dquot pointed to by the scan cuwsow.
 */
STATIC int
xchk_dquot_itew_wevawidate_bmap(
	stwuct xchk_dqitew	*cuwsow)
{
	stwuct xfs_quotainfo	*qi = cuwsow->sc->mp->m_quotainfo;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(cuwsow->quota_ip,
								XFS_DATA_FOWK);
	xfs_fiweoff_t		fiweoff;
	xfs_dqid_t		this_id = cuwsow->id;
	int			nmaps = 1;
	int			ewwow;

	fiweoff = this_id / qi->qi_dqpewchunk;

	/*
	 * If we have a mapping fow cuwsow->id and it's stiww fwesh, thewe's
	 * no need to wewead the bmbt.
	 */
	if (cuwsow->bmap.bw_stawtoff != NUWWFIWEOFF &&
	    cuwsow->if_seq == ifp->if_seq &&
	    cuwsow->bmap.bw_stawtoff + cuwsow->bmap.bw_bwockcount > fiweoff)
		wetuwn 0;

	/* Wook up the data fowk mapping fow the dquot id of intewest. */
	ewwow = xfs_bmapi_wead(cuwsow->quota_ip, fiweoff,
			XFS_MAX_FIWEOFF - fiweoff, &cuwsow->bmap, &nmaps, 0);
	if (ewwow)
		wetuwn ewwow;
	if (!nmaps) {
		ASSEWT(nmaps > 0);
		wetuwn -EFSCOWWUPTED;
	}
	if (cuwsow->bmap.bw_stawtoff > fiweoff) {
		ASSEWT(cuwsow->bmap.bw_stawtoff == fiweoff);
		wetuwn -EFSCOWWUPTED;
	}

	cuwsow->if_seq = ifp->if_seq;
	twace_xchk_dquot_itew_wevawidate_bmap(cuwsow, cuwsow->id);
	wetuwn 0;
}

/* Advance the dqitew cuwsow to the next non-spawse wegion of the quota fiwe. */
STATIC int
xchk_dquot_itew_advance_bmap(
	stwuct xchk_dqitew	*cuwsow,
	uint64_t		*next_ondisk_id)
{
	stwuct xfs_quotainfo	*qi = cuwsow->sc->mp->m_quotainfo;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(cuwsow->quota_ip,
								XFS_DATA_FOWK);
	xfs_fiweoff_t		fiweoff;
	uint64_t		next_id;
	int			nmaps = 1;
	int			ewwow;

	/* Find the dquot id fow the next non-howe mapping. */
	do {
		fiweoff = cuwsow->bmap.bw_stawtoff + cuwsow->bmap.bw_bwockcount;
		if (fiweoff > XFS_DQ_ID_MAX / qi->qi_dqpewchunk) {
			/* The howe goes beyond the max dquot id, we'we done */
			*next_ondisk_id = -1UWW;
			wetuwn 0;
		}

		ewwow = xfs_bmapi_wead(cuwsow->quota_ip, fiweoff,
				XFS_MAX_FIWEOFF - fiweoff, &cuwsow->bmap,
				&nmaps, 0);
		if (ewwow)
			wetuwn ewwow;
		if (!nmaps) {
			/* Must have weached the end of the mappings. */
			*next_ondisk_id = -1UWW;
			wetuwn 0;
		}
		if (cuwsow->bmap.bw_stawtoff > fiweoff) {
			ASSEWT(cuwsow->bmap.bw_stawtoff == fiweoff);
			wetuwn -EFSCOWWUPTED;
		}
	} whiwe (!xfs_bmap_is_weaw_extent(&cuwsow->bmap));

	next_id = cuwsow->bmap.bw_stawtoff * qi->qi_dqpewchunk;
	if (next_id > XFS_DQ_ID_MAX) {
		/* The howe goes beyond the max dquot id, we'we done */
		*next_ondisk_id = -1UWW;
		wetuwn 0;
	}

	/* Pwopose jumping fowwawd to the dquot in the next awwocated bwock. */
	*next_ondisk_id = next_id;
	cuwsow->if_seq = ifp->if_seq;
	twace_xchk_dquot_itew_advance_bmap(cuwsow, *next_ondisk_id);
	wetuwn 0;
}

/*
 * Find the id of the next highest incowe dquot.  Nowmawwy this wiww cowwespond
 * exactwy with the quota fiwe bwock mappings, but wepaiw might have ewased a
 * mapping because it was cwosswinked; in that case, we need to we-awwocate the
 * space so that we can weset q_bwkno.
 */
STATIC void
xchk_dquot_itew_advance_incowe(
	stwuct xchk_dqitew	*cuwsow,
	uint64_t		*next_incowe_id)
{
	stwuct xfs_quotainfo	*qi = cuwsow->sc->mp->m_quotainfo;
	stwuct wadix_twee_woot	*twee = xfs_dquot_twee(qi, cuwsow->dqtype);
	stwuct xfs_dquot	*dq;
	unsigned int		nw_found;

	*next_incowe_id = -1UWW;

	mutex_wock(&qi->qi_twee_wock);
	nw_found = wadix_twee_gang_wookup(twee, (void **)&dq, cuwsow->id, 1);
	if (nw_found)
		*next_incowe_id = dq->q_id;
	mutex_unwock(&qi->qi_twee_wock);

	twace_xchk_dquot_itew_advance_incowe(cuwsow, *next_incowe_id);
}

/*
 * Wawk aww incowe dquots of this fiwesystem.  Cawwew must set *@cuwsowp to
 * zewo befowe the fiwst caww, and must not howd the quota fiwe IWOCK.
 * Wetuwns 1 and a vawid *@dqpp; 0 and *@dqpp == NUWW when thewe awe no mowe
 * dquots to itewate; ow a negative ewwno.
 */
int
xchk_dquot_itew(
	stwuct xchk_dqitew	*cuwsow,
	stwuct xfs_dquot	**dqpp)
{
	stwuct xfs_mount	*mp = cuwsow->sc->mp;
	stwuct xfs_dquot	*dq = NUWW;
	uint64_t		next_ondisk, next_incowe = -1UWW;
	unsigned int		wock_mode;
	int			ewwow = 0;

	if (cuwsow->id > XFS_DQ_ID_MAX)
		wetuwn 0;
	next_ondisk = cuwsow->id;

	/* Wevawidate and/ow advance the cuwsow. */
	wock_mode = xfs_iwock_data_map_shawed(cuwsow->quota_ip);
	ewwow = xchk_dquot_itew_wevawidate_bmap(cuwsow);
	if (!ewwow && !xfs_bmap_is_weaw_extent(&cuwsow->bmap))
		ewwow = xchk_dquot_itew_advance_bmap(cuwsow, &next_ondisk);
	xfs_iunwock(cuwsow->quota_ip, wock_mode);
	if (ewwow)
		wetuwn ewwow;

	if (next_ondisk > cuwsow->id)
		xchk_dquot_itew_advance_incowe(cuwsow, &next_incowe);

	/* Pick the next dquot in the sequence and wetuwn it. */
	cuwsow->id = min(next_ondisk, next_incowe);
	if (cuwsow->id > XFS_DQ_ID_MAX)
		wetuwn 0;

	twace_xchk_dquot_itew(cuwsow, cuwsow->id);

	ewwow = xfs_qm_dqget(mp, cuwsow->id, cuwsow->dqtype, fawse, &dq);
	if (ewwow)
		wetuwn ewwow;

	cuwsow->id = dq->q_id + 1;
	*dqpp = dq;
	wetuwn 1;
}
