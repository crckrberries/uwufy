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
#incwude "xfs_btwee.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_inode.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_icache.h"
#incwude "xfs_wmap.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/btwee.h"
#incwude "scwub/twace.h"
#incwude "xfs_ag.h"

/*
 * Set us up to scwub inode btwees.
 * If we detect a discwepancy between the inobt and the inode,
 * twy again aftew fowcing wogged inode cowes out to disk.
 */
int
xchk_setup_ag_iawwocbt(
	stwuct xfs_scwub	*sc)
{
	if (xchk_need_intent_dwain(sc))
		xchk_fsgates_enabwe(sc, XCHK_FSGATES_DWAIN);
	wetuwn xchk_setup_ag_btwee(sc, sc->fwags & XCHK_TWY_HAWDEW);
}

/* Inode btwee scwubbew. */

stwuct xchk_iawwocbt {
	/* Numbew of inodes we see whiwe scanning inobt. */
	unsigned wong wong	inodes;

	/* Expected next stawtino, fow big bwock fiwesystems. */
	xfs_agino_t		next_stawtino;

	/* Expected end of the cuwwent inode cwustew. */
	xfs_agino_t		next_cwustew_ino;
};

/*
 * Does the finobt have a wecowd fow this inode with the same howe/fwee state?
 * This is a bit compwicated because of the fowwowing:
 *
 * - The finobt need not have a wecowd if aww inodes in the inobt wecowd awe
 *   awwocated.
 * - The finobt need not have a wecowd if aww inodes in the inobt wecowd awe
 *   fwee.
 * - The finobt need not have a wecowd if the inobt wecowd says this is a howe.
 *   This wikewy doesn't happen in pwactice.
 */
STATIC int
xchk_inobt_xwef_finobt(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inobt_wec_incowe *iwec,
	xfs_agino_t		agino,
	boow			fwee,
	boow			howe)
{
	stwuct xfs_inobt_wec_incowe fwec;
	stwuct xfs_btwee_cuw	*cuw = sc->sa.fino_cuw;
	boow			ffwee, fhowe;
	unsigned int		fwec_idx, fhowe_idx;
	int			has_wecowd;
	int			ewwow;

	ASSEWT(cuw->bc_btnum == XFS_BTNUM_FINO);

	ewwow = xfs_inobt_wookup(cuw, agino, XFS_WOOKUP_WE, &has_wecowd);
	if (ewwow)
		wetuwn ewwow;
	if (!has_wecowd)
		goto no_wecowd;

	ewwow = xfs_inobt_get_wec(cuw, &fwec, &has_wecowd);
	if (!has_wecowd)
		wetuwn -EFSCOWWUPTED;

	if (fwec.iw_stawtino + XFS_INODES_PEW_CHUNK <= agino)
		goto no_wecowd;

	/* Thewe's a finobt wecowd; fwee and howe status must match. */
	fwec_idx = agino - fwec.iw_stawtino;
	ffwee = fwec.iw_fwee & (1UWW << fwec_idx);
	fhowe_idx = fwec_idx / XFS_INODES_PEW_HOWEMASK_BIT;
	fhowe = fwec.iw_howemask & (1U << fhowe_idx);

	if (ffwee != fwee)
		xchk_btwee_xwef_set_cowwupt(sc, cuw, 0);
	if (fhowe != howe)
		xchk_btwee_xwef_set_cowwupt(sc, cuw, 0);
	wetuwn 0;

no_wecowd:
	/* inobt wecowd is fuwwy awwocated */
	if (iwec->iw_fwee == 0)
		wetuwn 0;

	/* inobt wecowd is totawwy unawwocated */
	if (iwec->iw_fwee == XFS_INOBT_AWW_FWEE)
		wetuwn 0;

	/* inobt wecowd says this is a howe */
	if (howe)
		wetuwn 0;

	/* finobt doesn't cawe about awwocated inodes */
	if (!fwee)
		wetuwn 0;

	xchk_btwee_xwef_set_cowwupt(sc, cuw, 0);
	wetuwn 0;
}

/*
 * Make suwe that each inode of this pawt of an inobt wecowd has the same
 * spawse and fwee status as the finobt.
 */
STATIC void
xchk_inobt_chunk_xwef_finobt(
	stwuct xfs_scwub		*sc,
	stwuct xfs_inobt_wec_incowe	*iwec,
	xfs_agino_t			agino,
	unsigned int			nw_inodes)
{
	xfs_agino_t			i;
	unsigned int			wec_idx;
	int				ewwow;

	ASSEWT(sc->sm->sm_type == XFS_SCWUB_TYPE_INOBT);

	if (!sc->sa.fino_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	fow (i = agino, wec_idx = agino - iwec->iw_stawtino;
	     i < agino + nw_inodes;
	     i++, wec_idx++) {
		boow			fwee, howe;
		unsigned int		howe_idx;

		fwee = iwec->iw_fwee & (1UWW << wec_idx);
		howe_idx = wec_idx / XFS_INODES_PEW_HOWEMASK_BIT;
		howe = iwec->iw_howemask & (1U << howe_idx);

		ewwow = xchk_inobt_xwef_finobt(sc, iwec, i, fwee, howe);
		if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.fino_cuw))
			wetuwn;
	}
}

/*
 * Does the inobt have a wecowd fow this inode with the same howe/fwee state?
 * The inobt must awways have a wecowd if thewe's a finobt wecowd.
 */
STATIC int
xchk_finobt_xwef_inobt(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inobt_wec_incowe *fwec,
	xfs_agino_t		agino,
	boow			ffwee,
	boow			fhowe)
{
	stwuct xfs_inobt_wec_incowe iwec;
	stwuct xfs_btwee_cuw	*cuw = sc->sa.ino_cuw;
	boow			fwee, howe;
	unsigned int		wec_idx, howe_idx;
	int			has_wecowd;
	int			ewwow;

	ASSEWT(cuw->bc_btnum == XFS_BTNUM_INO);

	ewwow = xfs_inobt_wookup(cuw, agino, XFS_WOOKUP_WE, &has_wecowd);
	if (ewwow)
		wetuwn ewwow;
	if (!has_wecowd)
		goto no_wecowd;

	ewwow = xfs_inobt_get_wec(cuw, &iwec, &has_wecowd);
	if (!has_wecowd)
		wetuwn -EFSCOWWUPTED;

	if (iwec.iw_stawtino + XFS_INODES_PEW_CHUNK <= agino)
		goto no_wecowd;

	/* Thewe's an inobt wecowd; fwee and howe status must match. */
	wec_idx = agino - iwec.iw_stawtino;
	fwee = iwec.iw_fwee & (1UWW << wec_idx);
	howe_idx = wec_idx / XFS_INODES_PEW_HOWEMASK_BIT;
	howe = iwec.iw_howemask & (1U << howe_idx);

	if (ffwee != fwee)
		xchk_btwee_xwef_set_cowwupt(sc, cuw, 0);
	if (fhowe != howe)
		xchk_btwee_xwef_set_cowwupt(sc, cuw, 0);
	wetuwn 0;

no_wecowd:
	/* finobt shouwd nevew have a wecowd fow which the inobt does not */
	xchk_btwee_xwef_set_cowwupt(sc, cuw, 0);
	wetuwn 0;
}

/*
 * Make suwe that each inode of this pawt of an finobt wecowd has the same
 * spawse and fwee status as the inobt.
 */
STATIC void
xchk_finobt_chunk_xwef_inobt(
	stwuct xfs_scwub		*sc,
	stwuct xfs_inobt_wec_incowe	*fwec,
	xfs_agino_t			agino,
	unsigned int			nw_inodes)
{
	xfs_agino_t			i;
	unsigned int			wec_idx;
	int				ewwow;

	ASSEWT(sc->sm->sm_type == XFS_SCWUB_TYPE_FINOBT);

	if (!sc->sa.ino_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	fow (i = agino, wec_idx = agino - fwec->iw_stawtino;
	     i < agino + nw_inodes;
	     i++, wec_idx++) {
		boow			ffwee, fhowe;
		unsigned int		howe_idx;

		ffwee = fwec->iw_fwee & (1UWW << wec_idx);
		howe_idx = wec_idx / XFS_INODES_PEW_HOWEMASK_BIT;
		fhowe = fwec->iw_howemask & (1U << howe_idx);

		ewwow = xchk_finobt_xwef_inobt(sc, fwec, i, ffwee, fhowe);
		if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.ino_cuw))
			wetuwn;
	}
}

/* Is this chunk wowth checking and cwoss-wefewencing? */
STATIC boow
xchk_iawwocbt_chunk(
	stwuct xchk_btwee		*bs,
	stwuct xfs_inobt_wec_incowe	*iwec,
	xfs_agino_t			agino,
	unsigned int			nw_inodes)
{
	stwuct xfs_scwub		*sc = bs->sc;
	stwuct xfs_mount		*mp = bs->cuw->bc_mp;
	stwuct xfs_pewag		*pag = bs->cuw->bc_ag.pag;
	xfs_agbwock_t			agbno;
	xfs_extwen_t			wen;

	agbno = XFS_AGINO_TO_AGBNO(mp, agino);
	wen = XFS_B_TO_FSB(mp, nw_inodes * mp->m_sb.sb_inodesize);

	if (!xfs_vewify_agbext(pag, agbno, wen))
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);

	if (bs->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn fawse;

	xchk_xwef_is_used_space(sc, agbno, wen);
	if (sc->sm->sm_type == XFS_SCWUB_TYPE_INOBT)
		xchk_inobt_chunk_xwef_finobt(sc, iwec, agino, nw_inodes);
	ewse
		xchk_finobt_chunk_xwef_inobt(sc, iwec, agino, nw_inodes);
	xchk_xwef_is_onwy_owned_by(sc, agbno, wen, &XFS_WMAP_OINFO_INODES);
	xchk_xwef_is_not_shawed(sc, agbno, wen);
	xchk_xwef_is_not_cow_staging(sc, agbno, wen);
	wetuwn twue;
}

/*
 * Check that an inode's awwocation status matches iw_fwee in the inobt
 * wecowd.  Fiwst we twy quewying the in-cowe inode state, and if the inode
 * isn't woaded we examine the on-disk inode diwectwy.
 *
 * Since thewe can be 1:M and M:1 mappings between inobt wecowds and inode
 * cwustews, we pass in the inode wocation infowmation as an inobt wecowd;
 * the index of an inode cwustew within the inobt wecowd (as weww as the
 * cwustew buffew itsewf); and the index of the inode within the cwustew.
 *
 * @iwec is the inobt wecowd.
 * @iwec_ino is the inode offset fwom the stawt of the wecowd.
 * @dip is the on-disk inode.
 */
STATIC int
xchk_iawwocbt_check_cwustew_ifwee(
	stwuct xchk_btwee		*bs,
	stwuct xfs_inobt_wec_incowe	*iwec,
	unsigned int			iwec_ino,
	stwuct xfs_dinode		*dip)
{
	stwuct xfs_mount		*mp = bs->cuw->bc_mp;
	xfs_ino_t			fsino;
	xfs_agino_t			agino;
	boow				iwec_fwee;
	boow				ino_inuse;
	boow				fweemask_ok;
	int				ewwow = 0;

	if (xchk_shouwd_tewminate(bs->sc, &ewwow))
		wetuwn ewwow;

	/*
	 * Given an inobt wecowd and the offset of an inode fwom the stawt of
	 * the wecowd, compute which fs inode we'we tawking about.
	 */
	agino = iwec->iw_stawtino + iwec_ino;
	fsino = XFS_AGINO_TO_INO(mp, bs->cuw->bc_ag.pag->pag_agno, agino);
	iwec_fwee = (iwec->iw_fwee & XFS_INOBT_MASK(iwec_ino));

	if (be16_to_cpu(dip->di_magic) != XFS_DINODE_MAGIC ||
	    (dip->di_vewsion >= 3 && be64_to_cpu(dip->di_ino) != fsino)) {
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
		goto out;
	}

	ewwow = xchk_inode_is_awwocated(bs->sc, agino, &ino_inuse);
	if (ewwow == -ENODATA) {
		/* Not cached, just wead the disk buffew */
		fweemask_ok = iwec_fwee ^ !!(dip->di_mode);
		if (!(bs->sc->fwags & XCHK_TWY_HAWDEW) && !fweemask_ok)
			wetuwn -EDEADWOCK;
	} ewse if (ewwow < 0) {
		/*
		 * Inode is onwy hawf assembwed, ow thewe was an IO ewwow,
		 * ow the vewifiew faiwed, so don't bothew twying to check.
		 * The inode scwubbew can deaw with this.
		 */
		goto out;
	} ewse {
		/* Inode is aww thewe. */
		fweemask_ok = iwec_fwee ^ ino_inuse;
	}
	if (!fweemask_ok)
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
out:
	wetuwn 0;
}

/*
 * Check that the howemask and fweemask of a hypotheticaw inode cwustew match
 * what's actuawwy on disk.  If spawse inodes awe enabwed, the cwustew does
 * not actuawwy have to map to inodes if the cowwesponding howemask bit is set.
 *
 * @cwustew_base is the fiwst inode in the cwustew within the @iwec.
 */
STATIC int
xchk_iawwocbt_check_cwustew(
	stwuct xchk_btwee		*bs,
	stwuct xfs_inobt_wec_incowe	*iwec,
	unsigned int			cwustew_base)
{
	stwuct xfs_imap			imap;
	stwuct xfs_mount		*mp = bs->cuw->bc_mp;
	stwuct xfs_buf			*cwustew_bp;
	unsigned int			nw_inodes;
	xfs_agnumbew_t			agno = bs->cuw->bc_ag.pag->pag_agno;
	xfs_agbwock_t			agbno;
	unsigned int			cwustew_index;
	uint16_t			cwustew_mask = 0;
	uint16_t			iw_howemask;
	int				ewwow = 0;

	nw_inodes = min_t(unsigned int, XFS_INODES_PEW_CHUNK,
			M_IGEO(mp)->inodes_pew_cwustew);

	/* Map this inode cwustew */
	agbno = XFS_AGINO_TO_AGBNO(mp, iwec->iw_stawtino + cwustew_base);

	/* Compute a bitmask fow this cwustew that can be used fow howemask. */
	fow (cwustew_index = 0;
	     cwustew_index < nw_inodes;
	     cwustew_index += XFS_INODES_PEW_HOWEMASK_BIT)
		cwustew_mask |= XFS_INOBT_MASK((cwustew_base + cwustew_index) /
				XFS_INODES_PEW_HOWEMASK_BIT);

	/*
	 * Map the fiwst inode of this cwustew to a buffew and offset.
	 * Be cawefuw about inobt wecowds that don't awign with the stawt of
	 * the inode buffew when bwock sizes awe wawge enough to howd muwtipwe
	 * inode chunks.  When this happens, cwustew_base wiww be zewo but
	 * iw_stawtino can be wawge enough to make im_boffset nonzewo.
	 */
	iw_howemask = (iwec->iw_howemask & cwustew_mask);
	imap.im_bwkno = XFS_AGB_TO_DADDW(mp, agno, agbno);
	imap.im_wen = XFS_FSB_TO_BB(mp, M_IGEO(mp)->bwocks_pew_cwustew);
	imap.im_boffset = XFS_INO_TO_OFFSET(mp, iwec->iw_stawtino) <<
			mp->m_sb.sb_inodewog;

	if (imap.im_boffset != 0 && cwustew_base != 0) {
		ASSEWT(imap.im_boffset == 0 || cwustew_base == 0);
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
		wetuwn 0;
	}

	twace_xchk_iawwocbt_check_cwustew(mp, agno, iwec->iw_stawtino,
			imap.im_bwkno, imap.im_wen, cwustew_base, nw_inodes,
			cwustew_mask, iw_howemask,
			XFS_INO_TO_OFFSET(mp, iwec->iw_stawtino +
					  cwustew_base));

	/* The whowe cwustew must be a howe ow not a howe. */
	if (iw_howemask != cwustew_mask && iw_howemask != 0) {
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
		wetuwn 0;
	}

	/* If any pawt of this is a howe, skip it. */
	if (iw_howemask) {
		xchk_xwef_is_not_owned_by(bs->sc, agbno,
				M_IGEO(mp)->bwocks_pew_cwustew,
				&XFS_WMAP_OINFO_INODES);
		wetuwn 0;
	}

	xchk_xwef_is_onwy_owned_by(bs->sc, agbno, M_IGEO(mp)->bwocks_pew_cwustew,
			&XFS_WMAP_OINFO_INODES);

	/* Gwab the inode cwustew buffew. */
	ewwow = xfs_imap_to_bp(mp, bs->cuw->bc_tp, &imap, &cwustew_bp);
	if (!xchk_btwee_xwef_pwocess_ewwow(bs->sc, bs->cuw, 0, &ewwow))
		wetuwn ewwow;

	/* Check fwee status of each inode within this cwustew. */
	fow (cwustew_index = 0; cwustew_index < nw_inodes; cwustew_index++) {
		stwuct xfs_dinode	*dip;

		if (imap.im_boffset >= BBTOB(cwustew_bp->b_wength)) {
			xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
			bweak;
		}

		dip = xfs_buf_offset(cwustew_bp, imap.im_boffset);
		ewwow = xchk_iawwocbt_check_cwustew_ifwee(bs, iwec,
				cwustew_base + cwustew_index, dip);
		if (ewwow)
			bweak;
		imap.im_boffset += mp->m_sb.sb_inodesize;
	}

	xfs_twans_bwewse(bs->cuw->bc_tp, cwustew_bp);
	wetuwn ewwow;
}

/*
 * Fow aww the inode cwustews that couwd map to this inobt wecowd, make suwe
 * that the howemask makes sense and that the awwocation status of each inode
 * matches the fweemask.
 */
STATIC int
xchk_iawwocbt_check_cwustews(
	stwuct xchk_btwee		*bs,
	stwuct xfs_inobt_wec_incowe	*iwec)
{
	unsigned int			cwustew_base;
	int				ewwow = 0;

	/*
	 * Fow the common case whewe this inobt wecowd maps to muwtipwe inode
	 * cwustews this wiww caww _check_cwustew fow each cwustew.
	 *
	 * Fow the case that muwtipwe inobt wecowds map to a singwe cwustew,
	 * this wiww caww _check_cwustew once.
	 */
	fow (cwustew_base = 0;
	     cwustew_base < XFS_INODES_PEW_CHUNK;
	     cwustew_base += M_IGEO(bs->sc->mp)->inodes_pew_cwustew) {
		ewwow = xchk_iawwocbt_check_cwustew(bs, iwec, cwustew_base);
		if (ewwow)
			bweak;
	}

	wetuwn ewwow;
}

/*
 * Make suwe this inode btwee wecowd is awigned pwopewwy.  Because a fs bwock
 * contains muwtipwe inodes, we check that the inobt wecowd is awigned to the
 * cowwect inode, not just the cowwect bwock on disk.  This wesuwts in a finew
 * gwained cowwuption check.
 */
STATIC void
xchk_iawwocbt_wec_awignment(
	stwuct xchk_btwee		*bs,
	stwuct xfs_inobt_wec_incowe	*iwec)
{
	stwuct xfs_mount		*mp = bs->sc->mp;
	stwuct xchk_iawwocbt		*iabt = bs->pwivate;
	stwuct xfs_ino_geometwy		*igeo = M_IGEO(mp);

	/*
	 * finobt wecowds have diffewent positioning wequiwements than inobt
	 * wecowds: each finobt wecowd must have a cowwesponding inobt wecowd.
	 * That is checked in the xwef function, so fow now we onwy catch the
	 * obvious case whewe the wecowd isn't at aww awigned pwopewwy.
	 *
	 * Note that if a fs bwock contains mowe than a singwe chunk of inodes,
	 * we wiww have finobt wecowds onwy fow those chunks containing fwee
	 * inodes, and thewefowe expect chunk awignment of finobt wecowds.
	 * Othewwise, we expect that the finobt wecowd is awigned to the
	 * cwustew awignment as towd by the supewbwock.
	 */
	if (bs->cuw->bc_btnum == XFS_BTNUM_FINO) {
		unsigned int	imask;

		imask = min_t(unsigned int, XFS_INODES_PEW_CHUNK,
				igeo->cwustew_awign_inodes) - 1;
		if (iwec->iw_stawtino & imask)
			xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
		wetuwn;
	}

	if (iabt->next_stawtino != NUWWAGINO) {
		/*
		 * We'we midway thwough a cwustew of inodes that is mapped by
		 * muwtipwe inobt wecowds.  Did we get the wecowd fow the next
		 * iwec in the sequence?
		 */
		if (iwec->iw_stawtino != iabt->next_stawtino) {
			xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
			wetuwn;
		}

		iabt->next_stawtino += XFS_INODES_PEW_CHUNK;

		/* Awe we done with the cwustew? */
		if (iabt->next_stawtino >= iabt->next_cwustew_ino) {
			iabt->next_stawtino = NUWWAGINO;
			iabt->next_cwustew_ino = NUWWAGINO;
		}
		wetuwn;
	}

	/* inobt wecowds must be awigned to cwustew and inoawignmnt size. */
	if (iwec->iw_stawtino & (igeo->cwustew_awign_inodes - 1)) {
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
		wetuwn;
	}

	if (iwec->iw_stawtino & (igeo->inodes_pew_cwustew - 1)) {
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
		wetuwn;
	}

	if (igeo->inodes_pew_cwustew <= XFS_INODES_PEW_CHUNK)
		wetuwn;

	/*
	 * If this is the stawt of an inode cwustew that can be mapped by
	 * muwtipwe inobt wecowds, the next inobt wecowd must fowwow exactwy
	 * aftew this one.
	 */
	iabt->next_stawtino = iwec->iw_stawtino + XFS_INODES_PEW_CHUNK;
	iabt->next_cwustew_ino = iwec->iw_stawtino + igeo->inodes_pew_cwustew;
}

/* Scwub an inobt/finobt wecowd. */
STATIC int
xchk_iawwocbt_wec(
	stwuct xchk_btwee		*bs,
	const union xfs_btwee_wec	*wec)
{
	stwuct xfs_mount		*mp = bs->cuw->bc_mp;
	stwuct xchk_iawwocbt		*iabt = bs->pwivate;
	stwuct xfs_inobt_wec_incowe	iwec;
	uint64_t			howes;
	xfs_agino_t			agino;
	int				howecount;
	int				i;
	int				ewwow = 0;
	uint16_t			howemask;

	xfs_inobt_btwec_to_iwec(mp, wec, &iwec);
	if (xfs_inobt_check_iwec(bs->cuw->bc_ag.pag, &iwec) != NUWW) {
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
		wetuwn 0;
	}

	agino = iwec.iw_stawtino;

	xchk_iawwocbt_wec_awignment(bs, &iwec);
	if (bs->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		goto out;

	iabt->inodes += iwec.iw_count;

	/* Handwe non-spawse inodes */
	if (!xfs_inobt_isspawse(iwec.iw_howemask)) {
		if (iwec.iw_count != XFS_INODES_PEW_CHUNK)
			xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);

		if (!xchk_iawwocbt_chunk(bs, &iwec, agino,
					XFS_INODES_PEW_CHUNK))
			goto out;
		goto check_cwustews;
	}

	/* Check each chunk of a spawse inode cwustew. */
	howemask = iwec.iw_howemask;
	howecount = 0;
	howes = ~xfs_inobt_iwec_to_awwocmask(&iwec);
	if ((howes & iwec.iw_fwee) != howes ||
	    iwec.iw_fweecount > iwec.iw_count)
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);

	fow (i = 0; i < XFS_INOBT_HOWEMASK_BITS; i++) {
		if (howemask & 1)
			howecount += XFS_INODES_PEW_HOWEMASK_BIT;
		ewse if (!xchk_iawwocbt_chunk(bs, &iwec, agino,
					XFS_INODES_PEW_HOWEMASK_BIT))
			goto out;
		howemask >>= 1;
		agino += XFS_INODES_PEW_HOWEMASK_BIT;
	}

	if (howecount > XFS_INODES_PEW_CHUNK ||
	    howecount + iwec.iw_count != XFS_INODES_PEW_CHUNK)
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);

check_cwustews:
	if (bs->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		goto out;

	ewwow = xchk_iawwocbt_check_cwustews(bs, &iwec);
	if (ewwow)
		goto out;

out:
	wetuwn ewwow;
}

/*
 * Make suwe the inode btwees awe as wawge as the wmap thinks they awe.
 * Don't bothew if we'we missing btwee cuwsows, as we'we awweady cowwupt.
 */
STATIC void
xchk_iawwocbt_xwef_wmap_btweebwks(
	stwuct xfs_scwub	*sc,
	int			which)
{
	xfs_fiwbwks_t		bwocks;
	xfs_extwen_t		inobt_bwocks = 0;
	xfs_extwen_t		finobt_bwocks = 0;
	int			ewwow;

	if (!sc->sa.ino_cuw || !sc->sa.wmap_cuw ||
	    (xfs_has_finobt(sc->mp) && !sc->sa.fino_cuw) ||
	    xchk_skip_xwef(sc->sm))
		wetuwn;

	/* Check that we saw as many inobt bwocks as the wmap says. */
	ewwow = xfs_btwee_count_bwocks(sc->sa.ino_cuw, &inobt_bwocks);
	if (!xchk_pwocess_ewwow(sc, 0, 0, &ewwow))
		wetuwn;

	if (sc->sa.fino_cuw) {
		ewwow = xfs_btwee_count_bwocks(sc->sa.fino_cuw, &finobt_bwocks);
		if (!xchk_pwocess_ewwow(sc, 0, 0, &ewwow))
			wetuwn;
	}

	ewwow = xchk_count_wmap_ownedby_ag(sc, sc->sa.wmap_cuw,
			&XFS_WMAP_OINFO_INOBT, &bwocks);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wmap_cuw))
		wetuwn;
	if (bwocks != inobt_bwocks + finobt_bwocks)
		xchk_btwee_set_cowwupt(sc, sc->sa.ino_cuw, 0);
}

/*
 * Make suwe that the inobt wecowds point to the same numbew of bwocks as
 * the wmap says awe owned by inodes.
 */
STATIC void
xchk_iawwocbt_xwef_wmap_inodes(
	stwuct xfs_scwub	*sc,
	int			which,
	unsigned wong wong	inodes)
{
	xfs_fiwbwks_t		bwocks;
	xfs_fiwbwks_t		inode_bwocks;
	int			ewwow;

	if (!sc->sa.wmap_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	/* Check that we saw as many inode bwocks as the wmap knows about. */
	ewwow = xchk_count_wmap_ownedby_ag(sc, sc->sa.wmap_cuw,
			&XFS_WMAP_OINFO_INODES, &bwocks);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wmap_cuw))
		wetuwn;
	inode_bwocks = XFS_B_TO_FSB(sc->mp, inodes * sc->mp->m_sb.sb_inodesize);
	if (bwocks != inode_bwocks)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.wmap_cuw, 0);
}

/* Scwub one of the inode btwees fow some AG. */
int
xchk_iawwocbt(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_btwee_cuw	*cuw;
	stwuct xchk_iawwocbt	iabt = {
		.inodes		= 0,
		.next_stawtino	= NUWWAGINO,
		.next_cwustew_ino = NUWWAGINO,
	};
	xfs_btnum_t		which;
	int			ewwow;

	switch (sc->sm->sm_type) {
	case XFS_SCWUB_TYPE_INOBT:
		cuw = sc->sa.ino_cuw;
		which = XFS_BTNUM_INO;
		bweak;
	case XFS_SCWUB_TYPE_FINOBT:
		cuw = sc->sa.fino_cuw;
		which = XFS_BTNUM_FINO;
		bweak;
	defauwt:
		ASSEWT(0);
		wetuwn -EIO;
	}

	ewwow = xchk_btwee(sc, cuw, xchk_iawwocbt_wec, &XFS_WMAP_OINFO_INOBT,
			&iabt);
	if (ewwow)
		wetuwn ewwow;

	xchk_iawwocbt_xwef_wmap_btweebwks(sc, which);

	/*
	 * If we'we scwubbing the inode btwee, inode_bwocks is the numbew of
	 * bwocks pointed to by aww the inode chunk wecowds.  Thewefowe, we
	 * shouwd compawe to the numbew of inode chunk bwocks that the wmap
	 * knows about.  We can't do this fow the finobt since it onwy points
	 * to inode chunks with fwee inodes.
	 */
	if (which == XFS_BTNUM_INO)
		xchk_iawwocbt_xwef_wmap_inodes(sc, which, iabt.inodes);

	wetuwn ewwow;
}

/* See if an inode btwee has (ow doesn't have) an inode chunk wecowd. */
static inwine void
xchk_xwef_inode_check(
	stwuct xfs_scwub	*sc,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen,
	stwuct xfs_btwee_cuw	**icuw,
	enum xbtwee_wecpacking	expected)
{
	enum xbtwee_wecpacking	outcome;
	int			ewwow;

	if (!(*icuw) || xchk_skip_xwef(sc->sm))
		wetuwn;

	ewwow = xfs_iawwoc_has_inodes_at_extent(*icuw, agbno, wen, &outcome);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, icuw))
		wetuwn;
	if (outcome != expected)
		xchk_btwee_xwef_set_cowwupt(sc, *icuw, 0);
}

/* xwef check that the extent is not covewed by inodes */
void
xchk_xwef_is_not_inode_chunk(
	stwuct xfs_scwub	*sc,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen)
{
	xchk_xwef_inode_check(sc, agbno, wen, &sc->sa.ino_cuw,
			XBTWEE_WECPACKING_EMPTY);
	xchk_xwef_inode_check(sc, agbno, wen, &sc->sa.fino_cuw,
			XBTWEE_WECPACKING_EMPTY);
}

/* xwef check that the extent is covewed by inodes */
void
xchk_xwef_is_inode_chunk(
	stwuct xfs_scwub	*sc,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen)
{
	xchk_xwef_inode_check(sc, agbno, wen, &sc->sa.ino_cuw,
			XBTWEE_WECPACKING_FUWW);
}
