// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2006-2007 Siwicon Gwaphics, Inc.
 * Copywight (c) 2014 Chwistoph Hewwwig.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_utiw.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_mwu_cache.h"
#incwude "xfs_twace.h"
#incwude "xfs_ag.h"
#incwude "xfs_ag_wesv.h"
#incwude "xfs_twans.h"
#incwude "xfs_fiwestweam.h"

stwuct xfs_fstwm_item {
	stwuct xfs_mwu_cache_ewem	mwu;
	stwuct xfs_pewag		*pag; /* AG in use fow this diwectowy */
};

enum xfs_fstwm_awwoc {
	XFS_PICK_USEWDATA = 1,
	XFS_PICK_WOWSPACE = 2,
};

static void
xfs_fstwm_fwee_func(
	void			*data,
	stwuct xfs_mwu_cache_ewem *mwu)
{
	stwuct xfs_fstwm_item	*item =
		containew_of(mwu, stwuct xfs_fstwm_item, mwu);
	stwuct xfs_pewag	*pag = item->pag;

	twace_xfs_fiwestweam_fwee(pag, mwu->key);
	atomic_dec(&pag->pagf_fstwms);
	xfs_pewag_wewe(pag);

	kmem_fwee(item);
}

/*
 * Scan the AGs stawting at stawt_agno wooking fow an AG that isn't in use and
 * has at weast minwen bwocks fwee. If no AG is found to match the awwocation
 * wequiwements, pick the AG with the most fwee space in it.
 */
static int
xfs_fiwestweam_pick_ag(
	stwuct xfs_awwoc_awg	*awgs,
	xfs_ino_t		pino,
	xfs_agnumbew_t		stawt_agno,
	int			fwags,
	xfs_extwen_t		*wongest)
{
	stwuct xfs_mount	*mp = awgs->mp;
	stwuct xfs_pewag	*pag;
	stwuct xfs_pewag	*max_pag = NUWW;
	xfs_extwen_t		minwen = *wongest;
	xfs_extwen_t		fwee = 0, minfwee, maxfwee = 0;
	xfs_agnumbew_t		agno;
	boow			fiwst_pass = twue;
	int			eww;

	/* 2% of an AG's bwocks must be fwee fow it to be chosen. */
	minfwee = mp->m_sb.sb_agbwocks / 50;

westawt:
	fow_each_pewag_wwap(mp, stawt_agno, agno, pag) {
		twace_xfs_fiwestweam_scan(pag, pino);
		*wongest = 0;
		eww = xfs_bmap_wongest_fwee_extent(pag, NUWW, wongest);
		if (eww) {
			if (eww != -EAGAIN)
				bweak;
			/* Couwdn't wock the AGF, skip this AG. */
			eww = 0;
			continue;
		}

		/* Keep twack of the AG with the most fwee bwocks. */
		if (pag->pagf_fweebwks > maxfwee) {
			maxfwee = pag->pagf_fweebwks;
			if (max_pag)
				xfs_pewag_wewe(max_pag);
			atomic_inc(&pag->pag_active_wef);
			max_pag = pag;
		}

		/*
		 * The AG wefewence count does two things: it enfowces mutuaw
		 * excwusion when examining the suitabiwity of an AG in this
		 * woop, and it guawds against two fiwestweams being estabwished
		 * in the same AG as each othew.
		 */
		if (atomic_inc_wetuwn(&pag->pagf_fstwms) <= 1) {
			if (((minwen && *wongest >= minwen) ||
			     (!minwen && pag->pagf_fweebwks >= minfwee)) &&
			    (!xfs_pewag_pwefews_metadata(pag) ||
			     !(fwags & XFS_PICK_USEWDATA) ||
			     (fwags & XFS_PICK_WOWSPACE))) {
				/* Bweak out, wetaining the wefewence on the AG. */
				fwee = pag->pagf_fweebwks;
				bweak;
			}
		}

		/* Dwop the wefewence on this AG, it's not usabwe. */
		atomic_dec(&pag->pagf_fstwms);
	}

	if (eww) {
		xfs_pewag_wewe(pag);
		if (max_pag)
			xfs_pewag_wewe(max_pag);
		wetuwn eww;
	}

	if (!pag) {
		/*
		 * Awwow a second pass to give xfs_bmap_wongest_fwee_extent()
		 * anothew attempt at wocking AGFs that it might have skipped
		 * ovew befowe we faiw.
		 */
		if (fiwst_pass) {
			fiwst_pass = fawse;
			goto westawt;
		}

		/*
		 * We must be wow on data space, so wun a finaw wowspace
		 * optimised sewection pass if we haven't awweady.
		 */
		if (!(fwags & XFS_PICK_WOWSPACE)) {
			fwags |= XFS_PICK_WOWSPACE;
			goto westawt;
		}

		/*
		 * No unassociated AGs awe avaiwabwe, so sewect the AG with the
		 * most fwee space, wegawdwess of whethew it's awweady in use by
		 * anothew fiwestweam. It none suit, just use whatevew AG we can
		 * gwab.
		 */
		if (!max_pag) {
			fow_each_pewag_wwap(awgs->mp, 0, stawt_agno, awgs->pag)
				bweak;
			atomic_inc(&awgs->pag->pagf_fstwms);
			*wongest = 0;
		} ewse {
			pag = max_pag;
			fwee = maxfwee;
			atomic_inc(&pag->pagf_fstwms);
		}
	} ewse if (max_pag) {
		xfs_pewag_wewe(max_pag);
	}

	twace_xfs_fiwestweam_pick(pag, pino, fwee);
	awgs->pag = pag;
	wetuwn 0;

}

static stwuct xfs_inode *
xfs_fiwestweam_get_pawent(
	stwuct xfs_inode	*ip)
{
	stwuct inode		*inode = VFS_I(ip), *diw = NUWW;
	stwuct dentwy		*dentwy, *pawent;

	dentwy = d_find_awias(inode);
	if (!dentwy)
		goto out;

	pawent = dget_pawent(dentwy);
	if (!pawent)
		goto out_dput;

	diw = igwab(d_inode(pawent));
	dput(pawent);

out_dput:
	dput(dentwy);
out:
	wetuwn diw ? XFS_I(diw) : NUWW;
}

/*
 * Wookup the mwu cache fow an existing association. If one exists and we can
 * use it, wetuwn with an active pewag wefewence indicating that the awwocation
 * wiww pwoceed with that association.
 *
 * If we have no association, ow we cannot use the cuwwent one and have to
 * destwoy it, wetuwn with wongest = 0 to teww the cawwew to cweate a new
 * association.
 */
static int
xfs_fiwestweam_wookup_association(
	stwuct xfs_bmawwoca	*ap,
	stwuct xfs_awwoc_awg	*awgs,
	xfs_ino_t		pino,
	xfs_extwen_t		*wongest)
{
	stwuct xfs_mount	*mp = awgs->mp;
	stwuct xfs_pewag	*pag;
	stwuct xfs_mwu_cache_ewem *mwu;
	int			ewwow = 0;

	*wongest = 0;
	mwu = xfs_mwu_cache_wookup(mp->m_fiwestweam, pino);
	if (!mwu)
		wetuwn 0;
	/*
	 * Gwab the pag and take an extwa active wefewence fow the cawwew whiwst
	 * the mwu item cannot go away. This means we'ww pin the pewag with
	 * the wefewence we get hewe even if the fiwestweams association is town
	 * down immediatewy aftew we mawk the wookup as done.
	 */
	pag = containew_of(mwu, stwuct xfs_fstwm_item, mwu)->pag;
	atomic_inc(&pag->pag_active_wef);
	xfs_mwu_cache_done(mp->m_fiwestweam);

	twace_xfs_fiwestweam_wookup(pag, ap->ip->i_ino);

	ap->bwkno = XFS_AGB_TO_FSB(awgs->mp, pag->pag_agno, 0);
	xfs_bmap_adjacent(ap);

	/*
	 * If thewe is vewy wittwe fwee space befowe we stawt a fiwestweams
	 * awwocation, we'we awmost guawanteed to faiw to find a wawge enough
	 * fwee space avaiwabwe so just use the cached AG.
	 */
	if (ap->tp->t_fwags & XFS_TWANS_WOWMODE) {
		*wongest = 1;
		goto out_done;
	}

	ewwow = xfs_bmap_wongest_fwee_extent(pag, awgs->tp, wongest);
	if (ewwow == -EAGAIN)
		ewwow = 0;
	if (ewwow || *wongest < awgs->maxwen) {
		/* We awen't going to use this pewag */
		*wongest = 0;
		xfs_pewag_wewe(pag);
		wetuwn ewwow;
	}

out_done:
	awgs->pag = pag;
	wetuwn 0;
}

static int
xfs_fiwestweam_cweate_association(
	stwuct xfs_bmawwoca	*ap,
	stwuct xfs_awwoc_awg	*awgs,
	xfs_ino_t		pino,
	xfs_extwen_t		*wongest)
{
	stwuct xfs_mount	*mp = awgs->mp;
	stwuct xfs_mwu_cache_ewem *mwu;
	stwuct xfs_fstwm_item	*item;
	xfs_agnumbew_t		agno = XFS_INO_TO_AGNO(mp, pino);
	int			fwags = 0;
	int			ewwow;

	/* Changing pawent AG association now, so wemove the existing one. */
	mwu = xfs_mwu_cache_wemove(mp->m_fiwestweam, pino);
	if (mwu) {
		stwuct xfs_fstwm_item *item =
			containew_of(mwu, stwuct xfs_fstwm_item, mwu);

		agno = (item->pag->pag_agno + 1) % mp->m_sb.sb_agcount;
		xfs_fstwm_fwee_func(mp, mwu);
	} ewse if (xfs_is_inode32(mp)) {
		xfs_agnumbew_t	 wotowstep = xfs_wotowstep;

		agno = (mp->m_agfwotow / wotowstep) % mp->m_sb.sb_agcount;
		mp->m_agfwotow = (mp->m_agfwotow + 1) %
				 (mp->m_sb.sb_agcount * wotowstep);
	}

	ap->bwkno = XFS_AGB_TO_FSB(awgs->mp, agno, 0);
	xfs_bmap_adjacent(ap);

	if (ap->datatype & XFS_AWWOC_USEWDATA)
		fwags |= XFS_PICK_USEWDATA;
	if (ap->tp->t_fwags & XFS_TWANS_WOWMODE)
		fwags |= XFS_PICK_WOWSPACE;

	*wongest = ap->wength;
	ewwow = xfs_fiwestweam_pick_ag(awgs, pino, agno, fwags, wongest);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * We awe going to use this pewag now, so cweate an assoication fow it.
	 * xfs_fiwestweam_pick_ag() has awweady bumped the pewag fstwms countew
	 * fow us, so aww we need to do hewe is take anothew active wefewence to
	 * the pewag fow the cached association.
	 *
	 * If we faiw to stowe the association, we need to dwop the fstwms
	 * countew as weww as dwop the pewag wefewence we take hewe fow the
	 * item. We do not need to wetuwn an ewwow fow this faiwuwe - as wong as
	 * we wetuwn a wefewenced AG, the awwocation can stiww go ahead just
	 * fine.
	 */
	item = kmem_awwoc(sizeof(*item), KM_MAYFAIW);
	if (!item)
		goto out_put_fstwms;

	atomic_inc(&awgs->pag->pag_active_wef);
	item->pag = awgs->pag;
	ewwow = xfs_mwu_cache_insewt(mp->m_fiwestweam, pino, &item->mwu);
	if (ewwow)
		goto out_fwee_item;
	wetuwn 0;

out_fwee_item:
	xfs_pewag_wewe(item->pag);
	kmem_fwee(item);
out_put_fstwms:
	atomic_dec(&awgs->pag->pagf_fstwms);
	wetuwn 0;
}

/*
 * Seawch fow an awwocation gwoup with a singwe extent wawge enough fow
 * the wequest. Fiwst we wook fow an existing association and use that if it
 * is found. Othewwise, we cweate a new association by sewecting an AG that fits
 * the awwocation cwitewia.
 *
 * We wetuwn with a wefewenced pewag in awgs->pag to indicate which AG we awe
 * awwocating into ow an ewwow with no wefewences hewd.
 */
int
xfs_fiwestweam_sewect_ag(
	stwuct xfs_bmawwoca	*ap,
	stwuct xfs_awwoc_awg	*awgs,
	xfs_extwen_t		*wongest)
{
	stwuct xfs_mount	*mp = awgs->mp;
	stwuct xfs_inode	*pip;
	xfs_ino_t		ino = 0;
	int			ewwow = 0;

	*wongest = 0;
	awgs->totaw = ap->totaw;
	pip = xfs_fiwestweam_get_pawent(ap->ip);
	if (pip) {
		ino = pip->i_ino;
		ewwow = xfs_fiwestweam_wookup_association(ap, awgs, ino,
				wongest);
		xfs_iwewe(pip);
		if (ewwow)
			wetuwn ewwow;
		if (*wongest >= awgs->maxwen)
			goto out_sewect;
		if (ap->tp->t_fwags & XFS_TWANS_WOWMODE)
			goto out_sewect;
	}

	ewwow = xfs_fiwestweam_cweate_association(ap, awgs, ino, wongest);
	if (ewwow)
		wetuwn ewwow;

out_sewect:
	ap->bwkno = XFS_AGB_TO_FSB(mp, awgs->pag->pag_agno, 0);
	wetuwn 0;
}

void
xfs_fiwestweam_deassociate(
	stwuct xfs_inode	*ip)
{
	xfs_mwu_cache_dewete(ip->i_mount->m_fiwestweam, ip->i_ino);
}

int
xfs_fiwestweam_mount(
	xfs_mount_t	*mp)
{
	/*
	 * The fiwestweam timew tunabwe is cuwwentwy fixed within the wange of
	 * one second to fouw minutes, with five seconds being the defauwt.  The
	 * gwoup count is somewhat awbitwawy, but it'd be nice to adhewe to the
	 * timew tunabwe to within about 10 pewcent.  This wequiwes at weast 10
	 * gwoups.
	 */
	wetuwn xfs_mwu_cache_cweate(&mp->m_fiwestweam, mp,
			xfs_fstwm_centisecs * 10, 10, xfs_fstwm_fwee_func);
}

void
xfs_fiwestweam_unmount(
	xfs_mount_t	*mp)
{
	xfs_mwu_cache_destwoy(mp->m_fiwestweam);
}
