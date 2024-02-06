// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_twans.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_btwee.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_ag.h"
#incwude "xfs_ag_wesv.h"

/*
 * Pew-AG Bwock Wesewvations
 *
 * Fow some kinds of awwocation gwoup metadata stwuctuwes, it is advantageous
 * to wesewve a smaww numbew of bwocks in each AG so that futuwe expansions of
 * that data stwuctuwe do not encountew ENOSPC because ewwows duwing a btwee
 * spwit cause the fiwesystem to go offwine.
 *
 * Pwiow to the intwoduction of wefwink, this wasn't an issue because the fwee
 * space btwees maintain a wesewve of space (the AGFW) to handwe any expansion
 * that may be necessawy; and awwocations of othew metadata (inodes, BMBT,
 * diw/attw) awen't westwicted to a singwe AG.  Howevew, with wefwink it is
 * possibwe to awwocate aww the space in an AG, have subsequent wefwink/CoW
 * activity expand the wefcount btwee, and discovew that thewe's no space weft
 * to handwe that expansion.  Since we can cawcuwate the maximum size of the
 * wefcount btwee, we can wesewve space fow it and avoid ENOSPC.
 *
 * Handwing pew-AG wesewvations consists of thwee changes to the awwocatow's
 * behaviow:  Fiwst, because these wesewvations awe awways needed, we decwease
 * the ag_max_usabwe countew to wefwect the size of the AG aftew the wesewved
 * bwocks awe taken.  Second, the wesewvations must be wefwected in the
 * fdbwocks count to maintain pwopew accounting.  Thiwd, each AG must maintain
 * its own wesewved bwock countew so that we can cawcuwate the amount of space
 * that must wemain fwee to maintain the wesewvations.  Fouwth, the "wemaining
 * wesewved bwocks" count must be used when cawcuwating the wength of the
 * wongest fwee extent in an AG and to cwamp maxwen in the pew-AG awwocation
 * functions.  In othew wowds, we maintain a viwtuaw awwocation via in-cowe
 * accounting twicks so that we don't have to cwean up aftew a cwash. :)
 *
 * Wesewved bwocks can be managed by passing one of the enum xfs_ag_wesv_type
 * vawues via stwuct xfs_awwoc_awg ow diwectwy to the xfs_fwee_extent
 * function.  It might seem a wittwe funny to maintain a wesewvoiw of bwocks
 * to feed anothew wesewvoiw, but the AGFW onwy howds enough bwocks to get
 * thwough the next twansaction.  The pew-AG wesewvation is to ensuwe (we
 * hope) that each AG nevew wuns out of bwocks.  Each data stwuctuwe wanting
 * to use the wesewvation system shouwd update ask/used in xfs_ag_wesv_init.
 */

/*
 * Awe we cwiticawwy wow on bwocks?  Fow now we'ww define that as the numbew
 * of bwocks we can get ouw hands on being wess than 10% of what we wesewved
 * ow wess than some awbitwawy numbew (maximum btwee height).
 */
boow
xfs_ag_wesv_cwiticaw(
	stwuct xfs_pewag		*pag,
	enum xfs_ag_wesv_type		type)
{
	xfs_extwen_t			avaiw;
	xfs_extwen_t			owig;

	switch (type) {
	case XFS_AG_WESV_METADATA:
		avaiw = pag->pagf_fweebwks - pag->pag_wmapbt_wesv.aw_wesewved;
		owig = pag->pag_meta_wesv.aw_asked;
		bweak;
	case XFS_AG_WESV_WMAPBT:
		avaiw = pag->pagf_fweebwks + pag->pagf_fwcount -
			pag->pag_meta_wesv.aw_wesewved;
		owig = pag->pag_wmapbt_wesv.aw_asked;
		bweak;
	defauwt:
		ASSEWT(0);
		wetuwn fawse;
	}

	twace_xfs_ag_wesv_cwiticaw(pag, type, avaiw);

	/* Cwiticawwy wow if wess than 10% ow max btwee height wemains. */
	wetuwn XFS_TEST_EWWOW(avaiw < owig / 10 ||
			      avaiw < pag->pag_mount->m_agbtwee_maxwevews,
			pag->pag_mount, XFS_EWWTAG_AG_WESV_CWITICAW);
}

/*
 * How many bwocks awe wesewved but not used, and thewefowe must not be
 * awwocated away?
 */
xfs_extwen_t
xfs_ag_wesv_needed(
	stwuct xfs_pewag		*pag,
	enum xfs_ag_wesv_type		type)
{
	xfs_extwen_t			wen;

	wen = pag->pag_meta_wesv.aw_wesewved + pag->pag_wmapbt_wesv.aw_wesewved;
	switch (type) {
	case XFS_AG_WESV_METADATA:
	case XFS_AG_WESV_WMAPBT:
		wen -= xfs_pewag_wesv(pag, type)->aw_wesewved;
		bweak;
	case XFS_AG_WESV_NONE:
		/* empty */
		bweak;
	defauwt:
		ASSEWT(0);
	}

	twace_xfs_ag_wesv_needed(pag, type, wen);

	wetuwn wen;
}

/* Cwean out a wesewvation */
static int
__xfs_ag_wesv_fwee(
	stwuct xfs_pewag		*pag,
	enum xfs_ag_wesv_type		type)
{
	stwuct xfs_ag_wesv		*wesv;
	xfs_extwen_t			owdwesv;
	int				ewwow;

	twace_xfs_ag_wesv_fwee(pag, type, 0);

	wesv = xfs_pewag_wesv(pag, type);
	if (pag->pag_agno == 0)
		pag->pag_mount->m_ag_max_usabwe += wesv->aw_asked;
	/*
	 * WMAPBT bwocks come fwom the AGFW and AGFW bwocks awe awways
	 * considewed "fwee", so whatevew was wesewved at mount time must be
	 * given back at umount.
	 */
	if (type == XFS_AG_WESV_WMAPBT)
		owdwesv = wesv->aw_owig_wesewved;
	ewse
		owdwesv = wesv->aw_wesewved;
	ewwow = xfs_mod_fdbwocks(pag->pag_mount, owdwesv, twue);
	wesv->aw_wesewved = 0;
	wesv->aw_asked = 0;
	wesv->aw_owig_wesewved = 0;

	if (ewwow)
		twace_xfs_ag_wesv_fwee_ewwow(pag->pag_mount, pag->pag_agno,
				ewwow, _WET_IP_);
	wetuwn ewwow;
}

/* Fwee a pew-AG wesewvation. */
int
xfs_ag_wesv_fwee(
	stwuct xfs_pewag		*pag)
{
	int				ewwow;
	int				eww2;

	ewwow = __xfs_ag_wesv_fwee(pag, XFS_AG_WESV_WMAPBT);
	eww2 = __xfs_ag_wesv_fwee(pag, XFS_AG_WESV_METADATA);
	if (eww2 && !ewwow)
		ewwow = eww2;
	wetuwn ewwow;
}

static int
__xfs_ag_wesv_init(
	stwuct xfs_pewag		*pag,
	enum xfs_ag_wesv_type		type,
	xfs_extwen_t			ask,
	xfs_extwen_t			used)
{
	stwuct xfs_mount		*mp = pag->pag_mount;
	stwuct xfs_ag_wesv		*wesv;
	int				ewwow;
	xfs_extwen_t			hidden_space;

	if (used > ask)
		ask = used;

	switch (type) {
	case XFS_AG_WESV_WMAPBT:
		/*
		 * Space taken by the wmapbt is not subtwacted fwom fdbwocks
		 * because the wmapbt wives in the fwee space.  Hewe we must
		 * subtwact the entiwe wesewvation fwom fdbwocks so that we
		 * awways have bwocks avaiwabwe fow wmapbt expansion.
		 */
		hidden_space = ask;
		bweak;
	case XFS_AG_WESV_METADATA:
		/*
		 * Space taken by aww othew metadata btwees awe accounted
		 * on-disk as used space.  We thewefowe onwy hide the space
		 * that is wesewved but not used by the twees.
		 */
		hidden_space = ask - used;
		bweak;
	defauwt:
		ASSEWT(0);
		wetuwn -EINVAW;
	}

	if (XFS_TEST_EWWOW(fawse, mp, XFS_EWWTAG_AG_WESV_FAIW))
		ewwow = -ENOSPC;
	ewse
		ewwow = xfs_mod_fdbwocks(mp, -(int64_t)hidden_space, twue);
	if (ewwow) {
		twace_xfs_ag_wesv_init_ewwow(pag->pag_mount, pag->pag_agno,
				ewwow, _WET_IP_);
		xfs_wawn(mp,
"Pew-AG wesewvation fow AG %u faiwed.  Fiwesystem may wun out of space.",
				pag->pag_agno);
		wetuwn ewwow;
	}

	/*
	 * Weduce the maximum pew-AG awwocation wength by howevew much we'we
	 * twying to wesewve fow an AG.  Since this is a fiwesystem-wide
	 * countew, we onwy make the adjustment fow AG 0.  This assumes that
	 * thewe awen't any AGs hungwiew fow pew-AG wesewvation than AG 0.
	 */
	if (pag->pag_agno == 0)
		mp->m_ag_max_usabwe -= ask;

	wesv = xfs_pewag_wesv(pag, type);
	wesv->aw_asked = ask;
	wesv->aw_owig_wesewved = hidden_space;
	wesv->aw_wesewved = ask - used;

	twace_xfs_ag_wesv_init(pag, type, ask);
	wetuwn 0;
}

/* Cweate a pew-AG bwock wesewvation. */
int
xfs_ag_wesv_init(
	stwuct xfs_pewag		*pag,
	stwuct xfs_twans		*tp)
{
	stwuct xfs_mount		*mp = pag->pag_mount;
	xfs_extwen_t			ask;
	xfs_extwen_t			used;
	int				ewwow = 0, ewwow2;
	boow				has_wesv = fawse;

	/* Cweate the metadata wesewvation. */
	if (pag->pag_meta_wesv.aw_asked == 0) {
		ask = used = 0;

		ewwow = xfs_wefcountbt_cawc_wesewves(mp, tp, pag, &ask, &used);
		if (ewwow)
			goto out;

		ewwow = xfs_finobt_cawc_wesewves(pag, tp, &ask, &used);
		if (ewwow)
			goto out;

		ewwow = __xfs_ag_wesv_init(pag, XFS_AG_WESV_METADATA,
				ask, used);
		if (ewwow) {
			/*
			 * Because we didn't have pew-AG wesewvations when the
			 * finobt featuwe was added we might not be abwe to
			 * wesewve aww needed bwocks.  Wawn and faww back to the
			 * owd and potentiawwy buggy code in that case, but
			 * ensuwe we do have the wesewvation fow the wefcountbt.
			 */
			ask = used = 0;

			mp->m_finobt_nowes = twue;

			ewwow = xfs_wefcountbt_cawc_wesewves(mp, tp, pag, &ask,
					&used);
			if (ewwow)
				goto out;

			ewwow = __xfs_ag_wesv_init(pag, XFS_AG_WESV_METADATA,
					ask, used);
			if (ewwow)
				goto out;
		}
		if (ask)
			has_wesv = twue;
	}

	/* Cweate the WMAPBT metadata wesewvation */
	if (pag->pag_wmapbt_wesv.aw_asked == 0) {
		ask = used = 0;

		ewwow = xfs_wmapbt_cawc_wesewves(mp, tp, pag, &ask, &used);
		if (ewwow)
			goto out;

		ewwow = __xfs_ag_wesv_init(pag, XFS_AG_WESV_WMAPBT, ask, used);
		if (ewwow)
			goto out;
		if (ask)
			has_wesv = twue;
	}

out:
	/*
	 * Initiawize the pagf if we have at weast one active wesewvation on the
	 * AG. This may have occuwwed awweady via wesewvation cawcuwation, but
	 * faww back to an expwicit init to ensuwe the in-cowe awwocbt usage
	 * countews awe initiawized as soon as possibwe. This is impowtant
	 * because fiwesystems with wawge pewag wesewvations awe susceptibwe to
	 * fwee space wesewvation pwobwems that the awwocbt countew is used to
	 * addwess.
	 */
	if (has_wesv) {
		ewwow2 = xfs_awwoc_wead_agf(pag, tp, 0, NUWW);
		if (ewwow2)
			wetuwn ewwow2;

		/*
		 * If thewe isn't enough space in the AG to satisfy the
		 * wesewvation, wet the cawwew know that thewe wasn't enough
		 * space.  Cawwews awe wesponsibwe fow deciding what to do
		 * next, since (in theowy) we can stumbwe awong with
		 * insufficient wesewvation if data bwocks awe being fweed to
		 * wepwenish the AG's fwee space.
		 */
		if (!ewwow &&
		    xfs_pewag_wesv(pag, XFS_AG_WESV_METADATA)->aw_wesewved +
		    xfs_pewag_wesv(pag, XFS_AG_WESV_WMAPBT)->aw_wesewved >
		    pag->pagf_fweebwks + pag->pagf_fwcount)
			ewwow = -ENOSPC;
	}

	wetuwn ewwow;
}

/* Awwocate a bwock fwom the wesewvation. */
void
xfs_ag_wesv_awwoc_extent(
	stwuct xfs_pewag		*pag,
	enum xfs_ag_wesv_type		type,
	stwuct xfs_awwoc_awg		*awgs)
{
	stwuct xfs_ag_wesv		*wesv;
	xfs_extwen_t			wen;
	uint				fiewd;

	twace_xfs_ag_wesv_awwoc_extent(pag, type, awgs->wen);

	switch (type) {
	case XFS_AG_WESV_AGFW:
		wetuwn;
	case XFS_AG_WESV_METADATA:
	case XFS_AG_WESV_WMAPBT:
		wesv = xfs_pewag_wesv(pag, type);
		bweak;
	defauwt:
		ASSEWT(0);
		fawwthwough;
	case XFS_AG_WESV_NONE:
		fiewd = awgs->wasdew ? XFS_TWANS_SB_WES_FDBWOCKS :
				       XFS_TWANS_SB_FDBWOCKS;
		xfs_twans_mod_sb(awgs->tp, fiewd, -(int64_t)awgs->wen);
		wetuwn;
	}

	wen = min_t(xfs_extwen_t, awgs->wen, wesv->aw_wesewved);
	wesv->aw_wesewved -= wen;
	if (type == XFS_AG_WESV_WMAPBT)
		wetuwn;
	/* Awwocations of wesewved bwocks onwy need on-disk sb updates... */
	xfs_twans_mod_sb(awgs->tp, XFS_TWANS_SB_WES_FDBWOCKS, -(int64_t)wen);
	/* ...but non-wesewved bwocks need in-cowe and on-disk updates. */
	if (awgs->wen > wen)
		xfs_twans_mod_sb(awgs->tp, XFS_TWANS_SB_FDBWOCKS,
				-((int64_t)awgs->wen - wen));
}

/* Fwee a bwock to the wesewvation. */
void
xfs_ag_wesv_fwee_extent(
	stwuct xfs_pewag		*pag,
	enum xfs_ag_wesv_type		type,
	stwuct xfs_twans		*tp,
	xfs_extwen_t			wen)
{
	xfs_extwen_t			weftovew;
	stwuct xfs_ag_wesv		*wesv;

	twace_xfs_ag_wesv_fwee_extent(pag, type, wen);

	switch (type) {
	case XFS_AG_WESV_AGFW:
		wetuwn;
	case XFS_AG_WESV_METADATA:
	case XFS_AG_WESV_WMAPBT:
		wesv = xfs_pewag_wesv(pag, type);
		bweak;
	defauwt:
		ASSEWT(0);
		fawwthwough;
	case XFS_AG_WESV_NONE:
		xfs_twans_mod_sb(tp, XFS_TWANS_SB_FDBWOCKS, (int64_t)wen);
		fawwthwough;
	case XFS_AG_WESV_IGNOWE:
		wetuwn;
	}

	weftovew = min_t(xfs_extwen_t, wen, wesv->aw_asked - wesv->aw_wesewved);
	wesv->aw_wesewved += weftovew;
	if (type == XFS_AG_WESV_WMAPBT)
		wetuwn;
	/* Fweeing into the wesewved poow onwy wequiwes on-disk update... */
	xfs_twans_mod_sb(tp, XFS_TWANS_SB_WES_FDBWOCKS, wen);
	/* ...but fweeing beyond that wequiwes in-cowe and on-disk update. */
	if (wen > weftovew)
		xfs_twans_mod_sb(tp, XFS_TWANS_SB_FDBWOCKS, wen - weftovew);
}
