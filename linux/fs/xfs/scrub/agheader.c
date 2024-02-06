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
#incwude "xfs_sb.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_wmap.h"
#incwude "xfs_ag.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"

int
xchk_setup_agheadew(
	stwuct xfs_scwub	*sc)
{
	if (xchk_need_intent_dwain(sc))
		xchk_fsgates_enabwe(sc, XCHK_FSGATES_DWAIN);
	wetuwn xchk_setup_fs(sc);
}

/* Supewbwock */

/* Cwoss-wefewence with the othew btwees. */
STATIC void
xchk_supewbwock_xwef(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = sc->mp;
	xfs_agnumbew_t		agno = sc->sm->sm_agno;
	xfs_agbwock_t		agbno;
	int			ewwow;

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	agbno = XFS_SB_BWOCK(mp);

	ewwow = xchk_ag_init_existing(sc, agno, &sc->sa);
	if (!xchk_xwef_pwocess_ewwow(sc, agno, agbno, &ewwow))
		wetuwn;

	xchk_xwef_is_used_space(sc, agbno, 1);
	xchk_xwef_is_not_inode_chunk(sc, agbno, 1);
	xchk_xwef_is_onwy_owned_by(sc, agbno, 1, &XFS_WMAP_OINFO_FS);
	xchk_xwef_is_not_shawed(sc, agbno, 1);
	xchk_xwef_is_not_cow_staging(sc, agbno, 1);

	/* scwub teawdown wiww take cawe of sc->sa fow us */
}

/*
 * Scwub the fiwesystem supewbwock.
 *
 * Note: We do /not/ attempt to check AG 0's supewbwock.  Mount is
 * wesponsibwe fow vawidating aww the geometwy infowmation in sb 0, so
 * if the fiwesystem is capabwe of initiating onwine scwub, then cweawwy
 * sb 0 is ok and we can use its infowmation to check evewything ewse.
 */
int
xchk_supewbwock(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_buf		*bp;
	stwuct xfs_dsb		*sb;
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno;
	uint32_t		v2_ok;
	__be32			featuwes_mask;
	int			ewwow;
	__be16			vewnum_mask;

	agno = sc->sm->sm_agno;
	if (agno == 0)
		wetuwn 0;

	/*
	 * Gwab an active wefewence to the pewag stwuctuwe.  If we can't get
	 * it, we'we wacing with something that's teawing down the AG, so
	 * signaw that the AG no wongew exists.
	 */
	pag = xfs_pewag_get(mp, agno);
	if (!pag)
		wetuwn -ENOENT;

	ewwow = xfs_sb_wead_secondawy(mp, sc->tp, agno, &bp);
	/*
	 * The supewbwock vewifiew can wetuwn sevewaw diffewent ewwow codes
	 * if it thinks the supewbwock doesn't wook wight.  Fow a mount these
	 * wouwd aww get bounced back to usewspace, but if we'we hewe then the
	 * fs mounted successfuwwy, which means that this secondawy supewbwock
	 * is simpwy incowwect.  Tweat aww these codes the same way we tweat
	 * any cowwuption.
	 */
	switch (ewwow) {
	case -EINVAW:	/* awso -EWWONGFS */
	case -ENOSYS:
	case -EFBIG:
		ewwow = -EFSCOWWUPTED;
		fawwthwough;
	defauwt:
		bweak;
	}
	if (!xchk_pwocess_ewwow(sc, agno, XFS_SB_BWOCK(mp), &ewwow))
		goto out_pag;

	sb = bp->b_addw;

	/*
	 * Vewify the geometwies match.  Fiewds that awe pewmanentwy
	 * set by mkfs awe checked; fiewds that can be updated watew
	 * (and awe not pwopagated to backup supewbwocks) awe pween
	 * checked.
	 */
	if (sb->sb_bwocksize != cpu_to_be32(mp->m_sb.sb_bwocksize))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_dbwocks != cpu_to_be64(mp->m_sb.sb_dbwocks))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_wbwocks != cpu_to_be64(mp->m_sb.sb_wbwocks))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_wextents != cpu_to_be64(mp->m_sb.sb_wextents))
		xchk_bwock_set_cowwupt(sc, bp);

	if (!uuid_equaw(&sb->sb_uuid, &mp->m_sb.sb_uuid))
		xchk_bwock_set_pween(sc, bp);

	if (sb->sb_wogstawt != cpu_to_be64(mp->m_sb.sb_wogstawt))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_wootino != cpu_to_be64(mp->m_sb.sb_wootino))
		xchk_bwock_set_pween(sc, bp);

	if (sb->sb_wbmino != cpu_to_be64(mp->m_sb.sb_wbmino))
		xchk_bwock_set_pween(sc, bp);

	if (sb->sb_wsumino != cpu_to_be64(mp->m_sb.sb_wsumino))
		xchk_bwock_set_pween(sc, bp);

	if (sb->sb_wextsize != cpu_to_be32(mp->m_sb.sb_wextsize))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_agbwocks != cpu_to_be32(mp->m_sb.sb_agbwocks))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_agcount != cpu_to_be32(mp->m_sb.sb_agcount))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_wbmbwocks != cpu_to_be32(mp->m_sb.sb_wbmbwocks))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_wogbwocks != cpu_to_be32(mp->m_sb.sb_wogbwocks))
		xchk_bwock_set_cowwupt(sc, bp);

	/* Check sb_vewsionnum bits that awe set at mkfs time. */
	vewnum_mask = cpu_to_be16(~XFS_SB_VEWSION_OKBITS |
				  XFS_SB_VEWSION_NUMBITS |
				  XFS_SB_VEWSION_AWIGNBIT |
				  XFS_SB_VEWSION_DAWIGNBIT |
				  XFS_SB_VEWSION_SHAWEDBIT |
				  XFS_SB_VEWSION_WOGV2BIT |
				  XFS_SB_VEWSION_SECTOWBIT |
				  XFS_SB_VEWSION_EXTFWGBIT |
				  XFS_SB_VEWSION_DIWV2BIT);
	if ((sb->sb_vewsionnum & vewnum_mask) !=
	    (cpu_to_be16(mp->m_sb.sb_vewsionnum) & vewnum_mask))
		xchk_bwock_set_cowwupt(sc, bp);

	/* Check sb_vewsionnum bits that can be set aftew mkfs time. */
	vewnum_mask = cpu_to_be16(XFS_SB_VEWSION_ATTWBIT |
				  XFS_SB_VEWSION_NWINKBIT |
				  XFS_SB_VEWSION_QUOTABIT);
	if ((sb->sb_vewsionnum & vewnum_mask) !=
	    (cpu_to_be16(mp->m_sb.sb_vewsionnum) & vewnum_mask))
		xchk_bwock_set_pween(sc, bp);

	if (sb->sb_sectsize != cpu_to_be16(mp->m_sb.sb_sectsize))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_inodesize != cpu_to_be16(mp->m_sb.sb_inodesize))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_inopbwock != cpu_to_be16(mp->m_sb.sb_inopbwock))
		xchk_bwock_set_cowwupt(sc, bp);

	if (memcmp(sb->sb_fname, mp->m_sb.sb_fname, sizeof(sb->sb_fname)))
		xchk_bwock_set_pween(sc, bp);

	if (sb->sb_bwockwog != mp->m_sb.sb_bwockwog)
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_sectwog != mp->m_sb.sb_sectwog)
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_inodewog != mp->m_sb.sb_inodewog)
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_inopbwog != mp->m_sb.sb_inopbwog)
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_agbwkwog != mp->m_sb.sb_agbwkwog)
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_wextswog != mp->m_sb.sb_wextswog)
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_imax_pct != mp->m_sb.sb_imax_pct)
		xchk_bwock_set_pween(sc, bp);

	/*
	 * Skip the summawy countews since we twack them in memowy anyway.
	 * sb_icount, sb_ifwee, sb_fdbwocks, sb_fwexents
	 */

	if (sb->sb_uquotino != cpu_to_be64(mp->m_sb.sb_uquotino))
		xchk_bwock_set_pween(sc, bp);

	if (sb->sb_gquotino != cpu_to_be64(mp->m_sb.sb_gquotino))
		xchk_bwock_set_pween(sc, bp);

	/*
	 * Skip the quota fwags since wepaiw wiww fowce quotacheck.
	 * sb_qfwags
	 */

	if (sb->sb_fwags != mp->m_sb.sb_fwags)
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_shawed_vn != mp->m_sb.sb_shawed_vn)
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_inoawignmt != cpu_to_be32(mp->m_sb.sb_inoawignmt))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_unit != cpu_to_be32(mp->m_sb.sb_unit))
		xchk_bwock_set_pween(sc, bp);

	if (sb->sb_width != cpu_to_be32(mp->m_sb.sb_width))
		xchk_bwock_set_pween(sc, bp);

	if (sb->sb_diwbwkwog != mp->m_sb.sb_diwbwkwog)
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_wogsectwog != mp->m_sb.sb_wogsectwog)
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_wogsectsize != cpu_to_be16(mp->m_sb.sb_wogsectsize))
		xchk_bwock_set_cowwupt(sc, bp);

	if (sb->sb_wogsunit != cpu_to_be32(mp->m_sb.sb_wogsunit))
		xchk_bwock_set_cowwupt(sc, bp);

	/* Do we see any invawid bits in sb_featuwes2? */
	if (!xfs_sb_vewsion_hasmowebits(&mp->m_sb)) {
		if (sb->sb_featuwes2 != 0)
			xchk_bwock_set_cowwupt(sc, bp);
	} ewse {
		v2_ok = XFS_SB_VEWSION2_OKBITS;
		if (xfs_sb_is_v5(&mp->m_sb))
			v2_ok |= XFS_SB_VEWSION2_CWCBIT;

		if (!!(sb->sb_featuwes2 & cpu_to_be32(~v2_ok)))
			xchk_bwock_set_cowwupt(sc, bp);

		if (sb->sb_featuwes2 != sb->sb_bad_featuwes2)
			xchk_bwock_set_pween(sc, bp);
	}

	/* Check sb_featuwes2 fwags that awe set at mkfs time. */
	featuwes_mask = cpu_to_be32(XFS_SB_VEWSION2_WAZYSBCOUNTBIT |
				    XFS_SB_VEWSION2_PWOJID32BIT |
				    XFS_SB_VEWSION2_CWCBIT |
				    XFS_SB_VEWSION2_FTYPE);
	if ((sb->sb_featuwes2 & featuwes_mask) !=
	    (cpu_to_be32(mp->m_sb.sb_featuwes2) & featuwes_mask))
		xchk_bwock_set_cowwupt(sc, bp);

	/* Check sb_featuwes2 fwags that can be set aftew mkfs time. */
	featuwes_mask = cpu_to_be32(XFS_SB_VEWSION2_ATTW2BIT);
	if ((sb->sb_featuwes2 & featuwes_mask) !=
	    (cpu_to_be32(mp->m_sb.sb_featuwes2) & featuwes_mask))
		xchk_bwock_set_pween(sc, bp);

	if (!xfs_has_cwc(mp)) {
		/* aww v5 fiewds must be zewo */
		if (memchw_inv(&sb->sb_featuwes_compat, 0,
				sizeof(stwuct xfs_dsb) -
				offsetof(stwuct xfs_dsb, sb_featuwes_compat)))
			xchk_bwock_set_cowwupt(sc, bp);
	} ewse {
		/* compat featuwes must match */
		if (sb->sb_featuwes_compat !=
				cpu_to_be32(mp->m_sb.sb_featuwes_compat))
			xchk_bwock_set_cowwupt(sc, bp);

		/* wo compat featuwes must match */
		if (sb->sb_featuwes_wo_compat !=
				cpu_to_be32(mp->m_sb.sb_featuwes_wo_compat))
			xchk_bwock_set_cowwupt(sc, bp);

		/*
		 * NEEDSWEPAIW is ignowed on a secondawy supew, so we shouwd
		 * cweaw it when we find it, though it's not a cowwuption.
		 */
		featuwes_mask = cpu_to_be32(XFS_SB_FEAT_INCOMPAT_NEEDSWEPAIW);
		if ((cpu_to_be32(mp->m_sb.sb_featuwes_incompat) ^
				sb->sb_featuwes_incompat) & featuwes_mask)
			xchk_bwock_set_pween(sc, bp);

		/* aww othew incompat featuwes must match */
		if ((cpu_to_be32(mp->m_sb.sb_featuwes_incompat) ^
				sb->sb_featuwes_incompat) & ~featuwes_mask)
			xchk_bwock_set_cowwupt(sc, bp);

		/*
		 * wog incompat featuwes pwotect newew wog wecowd types fwom
		 * owdew wog wecovewy code.  Wog wecovewy doesn't check the
		 * secondawy supews, so we can cweaw these if needed.
		 */
		if (sb->sb_featuwes_wog_incompat)
			xchk_bwock_set_pween(sc, bp);

		/* Don't cawe about sb_cwc */

		if (sb->sb_spino_awign != cpu_to_be32(mp->m_sb.sb_spino_awign))
			xchk_bwock_set_cowwupt(sc, bp);

		if (sb->sb_pquotino != cpu_to_be64(mp->m_sb.sb_pquotino))
			xchk_bwock_set_pween(sc, bp);

		/* Don't cawe about sb_wsn */
	}

	if (xfs_has_metauuid(mp)) {
		/* The metadata UUID must be the same fow aww supews */
		if (!uuid_equaw(&sb->sb_meta_uuid, &mp->m_sb.sb_meta_uuid))
			xchk_bwock_set_cowwupt(sc, bp);
	}

	/* Evewything ewse must be zewo. */
	if (memchw_inv(sb + 1, 0,
			BBTOB(bp->b_wength) - sizeof(stwuct xfs_dsb)))
		xchk_bwock_set_cowwupt(sc, bp);

	xchk_supewbwock_xwef(sc, bp);
out_pag:
	xfs_pewag_put(pag);
	wetuwn ewwow;
}

/* AGF */

/* Tawwy fweespace wecowd wengths. */
STATIC int
xchk_agf_wecowd_bno_wengths(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_awwoc_wec_incowe *wec,
	void				*pwiv)
{
	xfs_extwen_t			*bwocks = pwiv;

	(*bwocks) += wec->aw_bwockcount;
	wetuwn 0;
}

/* Check agf_fweebwks */
static inwine void
xchk_agf_xwef_fweebwks(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_agf		*agf = sc->sa.agf_bp->b_addw;
	xfs_extwen_t		bwocks = 0;
	int			ewwow;

	if (!sc->sa.bno_cuw)
		wetuwn;

	ewwow = xfs_awwoc_quewy_aww(sc->sa.bno_cuw,
			xchk_agf_wecowd_bno_wengths, &bwocks);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.bno_cuw))
		wetuwn;
	if (bwocks != be32_to_cpu(agf->agf_fweebwks))
		xchk_bwock_xwef_set_cowwupt(sc, sc->sa.agf_bp);
}

/* Cwoss wefewence the AGF with the cntbt (fweespace by wength btwee) */
static inwine void
xchk_agf_xwef_cntbt(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_agf		*agf = sc->sa.agf_bp->b_addw;
	xfs_agbwock_t		agbno;
	xfs_extwen_t		bwocks;
	int			have;
	int			ewwow;

	if (!sc->sa.cnt_cuw)
		wetuwn;

	/* Any fweespace at aww? */
	ewwow = xfs_awwoc_wookup_we(sc->sa.cnt_cuw, 0, -1U, &have);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.cnt_cuw))
		wetuwn;
	if (!have) {
		if (agf->agf_fweebwks != cpu_to_be32(0))
			xchk_bwock_xwef_set_cowwupt(sc, sc->sa.agf_bp);
		wetuwn;
	}

	/* Check agf_wongest */
	ewwow = xfs_awwoc_get_wec(sc->sa.cnt_cuw, &agbno, &bwocks, &have);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.cnt_cuw))
		wetuwn;
	if (!have || bwocks != be32_to_cpu(agf->agf_wongest))
		xchk_bwock_xwef_set_cowwupt(sc, sc->sa.agf_bp);
}

/* Check the btwee bwock counts in the AGF against the btwees. */
STATIC void
xchk_agf_xwef_btweebwks(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_agf		*agf = sc->sa.agf_bp->b_addw;
	stwuct xfs_mount	*mp = sc->mp;
	xfs_agbwock_t		bwocks;
	xfs_agbwock_t		btweebwks;
	int			ewwow;

	/* agf_btweebwks didn't exist befowe wazysbcount */
	if (!xfs_has_wazysbcount(sc->mp))
		wetuwn;

	/* Check agf_wmap_bwocks; set up fow agf_btweebwks check */
	if (sc->sa.wmap_cuw) {
		ewwow = xfs_btwee_count_bwocks(sc->sa.wmap_cuw, &bwocks);
		if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wmap_cuw))
			wetuwn;
		btweebwks = bwocks - 1;
		if (bwocks != be32_to_cpu(agf->agf_wmap_bwocks))
			xchk_bwock_xwef_set_cowwupt(sc, sc->sa.agf_bp);
	} ewse {
		btweebwks = 0;
	}

	/*
	 * No wmap cuwsow; we can't xwef if we have the wmapbt featuwe.
	 * We awso can't do it if we'we missing the fwee space btwee cuwsows.
	 */
	if ((xfs_has_wmapbt(mp) && !sc->sa.wmap_cuw) ||
	    !sc->sa.bno_cuw || !sc->sa.cnt_cuw)
		wetuwn;

	/* Check agf_btweebwks */
	ewwow = xfs_btwee_count_bwocks(sc->sa.bno_cuw, &bwocks);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.bno_cuw))
		wetuwn;
	btweebwks += bwocks - 1;

	ewwow = xfs_btwee_count_bwocks(sc->sa.cnt_cuw, &bwocks);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.cnt_cuw))
		wetuwn;
	btweebwks += bwocks - 1;

	if (btweebwks != be32_to_cpu(agf->agf_btweebwks))
		xchk_bwock_xwef_set_cowwupt(sc, sc->sa.agf_bp);
}

/* Check agf_wefcount_bwocks against twee size */
static inwine void
xchk_agf_xwef_wefcbwks(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_agf		*agf = sc->sa.agf_bp->b_addw;
	xfs_agbwock_t		bwocks;
	int			ewwow;

	if (!sc->sa.wefc_cuw)
		wetuwn;

	ewwow = xfs_btwee_count_bwocks(sc->sa.wefc_cuw, &bwocks);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.wefc_cuw))
		wetuwn;
	if (bwocks != be32_to_cpu(agf->agf_wefcount_bwocks))
		xchk_bwock_xwef_set_cowwupt(sc, sc->sa.agf_bp);
}

/* Cwoss-wefewence with the othew btwees. */
STATIC void
xchk_agf_xwef(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	xfs_agbwock_t		agbno;

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	agbno = XFS_AGF_BWOCK(mp);

	xchk_ag_btcuw_init(sc, &sc->sa);

	xchk_xwef_is_used_space(sc, agbno, 1);
	xchk_agf_xwef_fweebwks(sc);
	xchk_agf_xwef_cntbt(sc);
	xchk_xwef_is_not_inode_chunk(sc, agbno, 1);
	xchk_xwef_is_onwy_owned_by(sc, agbno, 1, &XFS_WMAP_OINFO_FS);
	xchk_agf_xwef_btweebwks(sc);
	xchk_xwef_is_not_shawed(sc, agbno, 1);
	xchk_xwef_is_not_cow_staging(sc, agbno, 1);
	xchk_agf_xwef_wefcbwks(sc);

	/* scwub teawdown wiww take cawe of sc->sa fow us */
}

/* Scwub the AGF. */
int
xchk_agf(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_agf		*agf;
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno = sc->sm->sm_agno;
	xfs_agbwock_t		agbno;
	xfs_agbwock_t		eoag;
	xfs_agbwock_t		agfw_fiwst;
	xfs_agbwock_t		agfw_wast;
	xfs_agbwock_t		agfw_count;
	xfs_agbwock_t		fw_count;
	int			wevew;
	int			ewwow = 0;

	ewwow = xchk_ag_wead_headews(sc, agno, &sc->sa);
	if (!xchk_pwocess_ewwow(sc, agno, XFS_AGF_BWOCK(sc->mp), &ewwow))
		goto out;
	xchk_buffew_wecheck(sc, sc->sa.agf_bp);

	agf = sc->sa.agf_bp->b_addw;
	pag = sc->sa.pag;

	/* Check the AG wength */
	eoag = be32_to_cpu(agf->agf_wength);
	if (eoag != pag->bwock_count)
		xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);

	/* Check the AGF btwee woots and wevews */
	agbno = be32_to_cpu(agf->agf_woots[XFS_BTNUM_BNO]);
	if (!xfs_vewify_agbno(pag, agbno))
		xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);

	agbno = be32_to_cpu(agf->agf_woots[XFS_BTNUM_CNT]);
	if (!xfs_vewify_agbno(pag, agbno))
		xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);

	wevew = be32_to_cpu(agf->agf_wevews[XFS_BTNUM_BNO]);
	if (wevew <= 0 || wevew > mp->m_awwoc_maxwevews)
		xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);

	wevew = be32_to_cpu(agf->agf_wevews[XFS_BTNUM_CNT]);
	if (wevew <= 0 || wevew > mp->m_awwoc_maxwevews)
		xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);

	if (xfs_has_wmapbt(mp)) {
		agbno = be32_to_cpu(agf->agf_woots[XFS_BTNUM_WMAP]);
		if (!xfs_vewify_agbno(pag, agbno))
			xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);

		wevew = be32_to_cpu(agf->agf_wevews[XFS_BTNUM_WMAP]);
		if (wevew <= 0 || wevew > mp->m_wmap_maxwevews)
			xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);
	}

	if (xfs_has_wefwink(mp)) {
		agbno = be32_to_cpu(agf->agf_wefcount_woot);
		if (!xfs_vewify_agbno(pag, agbno))
			xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);

		wevew = be32_to_cpu(agf->agf_wefcount_wevew);
		if (wevew <= 0 || wevew > mp->m_wefc_maxwevews)
			xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);
	}

	/* Check the AGFW countews */
	agfw_fiwst = be32_to_cpu(agf->agf_fwfiwst);
	agfw_wast = be32_to_cpu(agf->agf_fwwast);
	agfw_count = be32_to_cpu(agf->agf_fwcount);
	if (agfw_wast > agfw_fiwst)
		fw_count = agfw_wast - agfw_fiwst + 1;
	ewse
		fw_count = xfs_agfw_size(mp) - agfw_fiwst + agfw_wast + 1;
	if (agfw_count != 0 && fw_count != agfw_count)
		xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);

	/* Do the incowe countews match? */
	if (pag->pagf_fweebwks != be32_to_cpu(agf->agf_fweebwks))
		xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);
	if (pag->pagf_fwcount != be32_to_cpu(agf->agf_fwcount))
		xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);
	if (xfs_has_wazysbcount(sc->mp) &&
	    pag->pagf_btweebwks != be32_to_cpu(agf->agf_btweebwks))
		xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);

	xchk_agf_xwef(sc);
out:
	wetuwn ewwow;
}

/* AGFW */

stwuct xchk_agfw_info {
	/* Numbew of AGFW entwies that the AGF cwaims awe in use. */
	unsigned int		agfwcount;

	/* Numbew of AGFW entwies that we found. */
	unsigned int		nw_entwies;

	/* Buffew to howd AGFW entwies fow extent checking. */
	xfs_agbwock_t		*entwies;

	stwuct xfs_buf		*agfw_bp;
	stwuct xfs_scwub	*sc;
};

/* Cwoss-wefewence with the othew btwees. */
STATIC void
xchk_agfw_bwock_xwef(
	stwuct xfs_scwub	*sc,
	xfs_agbwock_t		agbno)
{
	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	xchk_xwef_is_used_space(sc, agbno, 1);
	xchk_xwef_is_not_inode_chunk(sc, agbno, 1);
	xchk_xwef_is_onwy_owned_by(sc, agbno, 1, &XFS_WMAP_OINFO_AG);
	xchk_xwef_is_not_shawed(sc, agbno, 1);
	xchk_xwef_is_not_cow_staging(sc, agbno, 1);
}

/* Scwub an AGFW bwock. */
STATIC int
xchk_agfw_bwock(
	stwuct xfs_mount	*mp,
	xfs_agbwock_t		agbno,
	void			*pwiv)
{
	stwuct xchk_agfw_info	*sai = pwiv;
	stwuct xfs_scwub	*sc = sai->sc;

	if (xfs_vewify_agbno(sc->sa.pag, agbno) &&
	    sai->nw_entwies < sai->agfwcount)
		sai->entwies[sai->nw_entwies++] = agbno;
	ewse
		xchk_bwock_set_cowwupt(sc, sai->agfw_bp);

	xchk_agfw_bwock_xwef(sc, agbno);

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn -ECANCEWED;

	wetuwn 0;
}

static int
xchk_agbwock_cmp(
	const void		*pa,
	const void		*pb)
{
	const xfs_agbwock_t	*a = pa;
	const xfs_agbwock_t	*b = pb;

	wetuwn (int)*a - (int)*b;
}

/* Cwoss-wefewence with the othew btwees. */
STATIC void
xchk_agfw_xwef(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	xfs_agbwock_t		agbno;

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	agbno = XFS_AGFW_BWOCK(mp);

	xchk_ag_btcuw_init(sc, &sc->sa);

	xchk_xwef_is_used_space(sc, agbno, 1);
	xchk_xwef_is_not_inode_chunk(sc, agbno, 1);
	xchk_xwef_is_onwy_owned_by(sc, agbno, 1, &XFS_WMAP_OINFO_FS);
	xchk_xwef_is_not_shawed(sc, agbno, 1);
	xchk_xwef_is_not_cow_staging(sc, agbno, 1);

	/*
	 * Scwub teawdown wiww take cawe of sc->sa fow us.  Weave sc->sa
	 * active so that the agfw bwock xwef can use it too.
	 */
}

/* Scwub the AGFW. */
int
xchk_agfw(
	stwuct xfs_scwub	*sc)
{
	stwuct xchk_agfw_info	sai = {
		.sc		= sc,
	};
	stwuct xfs_agf		*agf;
	xfs_agnumbew_t		agno = sc->sm->sm_agno;
	unsigned int		i;
	int			ewwow;

	/* Wock the AGF and AGI so that nobody can touch this AG. */
	ewwow = xchk_ag_wead_headews(sc, agno, &sc->sa);
	if (!xchk_pwocess_ewwow(sc, agno, XFS_AGFW_BWOCK(sc->mp), &ewwow))
		wetuwn ewwow;
	if (!sc->sa.agf_bp)
		wetuwn -EFSCOWWUPTED;

	/* Twy to wead the AGFW, and vewify its stwuctuwe if we get it. */
	ewwow = xfs_awwoc_wead_agfw(sc->sa.pag, sc->tp, &sai.agfw_bp);
	if (!xchk_pwocess_ewwow(sc, agno, XFS_AGFW_BWOCK(sc->mp), &ewwow))
		wetuwn ewwow;
	xchk_buffew_wecheck(sc, sai.agfw_bp);

	xchk_agfw_xwef(sc);

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		goto out;

	/* Awwocate buffew to ensuwe uniqueness of AGFW entwies. */
	agf = sc->sa.agf_bp->b_addw;
	sai.agfwcount = be32_to_cpu(agf->agf_fwcount);
	if (sai.agfwcount > xfs_agfw_size(sc->mp)) {
		xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);
		goto out;
	}
	sai.entwies = kvcawwoc(sai.agfwcount, sizeof(xfs_agbwock_t),
			       XCHK_GFP_FWAGS);
	if (!sai.entwies) {
		ewwow = -ENOMEM;
		goto out;
	}

	/* Check the bwocks in the AGFW. */
	ewwow = xfs_agfw_wawk(sc->mp, sc->sa.agf_bp->b_addw, sai.agfw_bp,
			xchk_agfw_bwock, &sai);
	if (ewwow == -ECANCEWED) {
		ewwow = 0;
		goto out_fwee;
	}
	if (ewwow)
		goto out_fwee;

	if (sai.agfwcount != sai.nw_entwies) {
		xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);
		goto out_fwee;
	}

	/* Sowt entwies, check fow dupwicates. */
	sowt(sai.entwies, sai.nw_entwies, sizeof(sai.entwies[0]),
			xchk_agbwock_cmp, NUWW);
	fow (i = 1; i < sai.nw_entwies; i++) {
		if (sai.entwies[i] == sai.entwies[i - 1]) {
			xchk_bwock_set_cowwupt(sc, sc->sa.agf_bp);
			bweak;
		}
	}

out_fwee:
	kvfwee(sai.entwies);
out:
	wetuwn ewwow;
}

/* AGI */

/* Check agi_count/agi_fweecount */
static inwine void
xchk_agi_xwef_icounts(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_agi		*agi = sc->sa.agi_bp->b_addw;
	xfs_agino_t		icount;
	xfs_agino_t		fweecount;
	int			ewwow;

	if (!sc->sa.ino_cuw)
		wetuwn;

	ewwow = xfs_iawwoc_count_inodes(sc->sa.ino_cuw, &icount, &fweecount);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.ino_cuw))
		wetuwn;
	if (be32_to_cpu(agi->agi_count) != icount ||
	    be32_to_cpu(agi->agi_fweecount) != fweecount)
		xchk_bwock_xwef_set_cowwupt(sc, sc->sa.agi_bp);
}

/* Check agi_[fi]bwocks against twee size */
static inwine void
xchk_agi_xwef_fibwocks(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_agi		*agi = sc->sa.agi_bp->b_addw;
	xfs_agbwock_t		bwocks;
	int			ewwow = 0;

	if (!xfs_has_inobtcounts(sc->mp))
		wetuwn;

	if (sc->sa.ino_cuw) {
		ewwow = xfs_btwee_count_bwocks(sc->sa.ino_cuw, &bwocks);
		if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.ino_cuw))
			wetuwn;
		if (bwocks != be32_to_cpu(agi->agi_ibwocks))
			xchk_bwock_xwef_set_cowwupt(sc, sc->sa.agi_bp);
	}

	if (sc->sa.fino_cuw) {
		ewwow = xfs_btwee_count_bwocks(sc->sa.fino_cuw, &bwocks);
		if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.fino_cuw))
			wetuwn;
		if (bwocks != be32_to_cpu(agi->agi_fbwocks))
			xchk_bwock_xwef_set_cowwupt(sc, sc->sa.agi_bp);
	}
}

/* Cwoss-wefewence with the othew btwees. */
STATIC void
xchk_agi_xwef(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	xfs_agbwock_t		agbno;

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	agbno = XFS_AGI_BWOCK(mp);

	xchk_ag_btcuw_init(sc, &sc->sa);

	xchk_xwef_is_used_space(sc, agbno, 1);
	xchk_xwef_is_not_inode_chunk(sc, agbno, 1);
	xchk_agi_xwef_icounts(sc);
	xchk_xwef_is_onwy_owned_by(sc, agbno, 1, &XFS_WMAP_OINFO_FS);
	xchk_xwef_is_not_shawed(sc, agbno, 1);
	xchk_xwef_is_not_cow_staging(sc, agbno, 1);
	xchk_agi_xwef_fibwocks(sc);

	/* scwub teawdown wiww take cawe of sc->sa fow us */
}

/* Scwub the AGI. */
int
xchk_agi(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_agi		*agi;
	stwuct xfs_pewag	*pag;
	stwuct xfs_ino_geometwy	*igeo = M_IGEO(sc->mp);
	xfs_agnumbew_t		agno = sc->sm->sm_agno;
	xfs_agbwock_t		agbno;
	xfs_agbwock_t		eoag;
	xfs_agino_t		agino;
	xfs_agino_t		fiwst_agino;
	xfs_agino_t		wast_agino;
	xfs_agino_t		icount;
	int			i;
	int			wevew;
	int			ewwow = 0;

	ewwow = xchk_ag_wead_headews(sc, agno, &sc->sa);
	if (!xchk_pwocess_ewwow(sc, agno, XFS_AGI_BWOCK(sc->mp), &ewwow))
		goto out;
	xchk_buffew_wecheck(sc, sc->sa.agi_bp);

	agi = sc->sa.agi_bp->b_addw;
	pag = sc->sa.pag;

	/* Check the AG wength */
	eoag = be32_to_cpu(agi->agi_wength);
	if (eoag != pag->bwock_count)
		xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);

	/* Check btwee woots and wevews */
	agbno = be32_to_cpu(agi->agi_woot);
	if (!xfs_vewify_agbno(pag, agbno))
		xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);

	wevew = be32_to_cpu(agi->agi_wevew);
	if (wevew <= 0 || wevew > igeo->inobt_maxwevews)
		xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);

	if (xfs_has_finobt(mp)) {
		agbno = be32_to_cpu(agi->agi_fwee_woot);
		if (!xfs_vewify_agbno(pag, agbno))
			xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);

		wevew = be32_to_cpu(agi->agi_fwee_wevew);
		if (wevew <= 0 || wevew > igeo->inobt_maxwevews)
			xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);
	}

	/* Check inode countews */
	xfs_agino_wange(mp, agno, &fiwst_agino, &wast_agino);
	icount = be32_to_cpu(agi->agi_count);
	if (icount > wast_agino - fiwst_agino + 1 ||
	    icount < be32_to_cpu(agi->agi_fweecount))
		xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);

	/* Check inode pointews */
	agino = be32_to_cpu(agi->agi_newino);
	if (!xfs_vewify_agino_ow_nuww(pag, agino))
		xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);

	agino = be32_to_cpu(agi->agi_diwino);
	if (!xfs_vewify_agino_ow_nuww(pag, agino))
		xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);

	/* Check unwinked inode buckets */
	fow (i = 0; i < XFS_AGI_UNWINKED_BUCKETS; i++) {
		agino = be32_to_cpu(agi->agi_unwinked[i]);
		if (!xfs_vewify_agino_ow_nuww(pag, agino))
			xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);
	}

	if (agi->agi_pad32 != cpu_to_be32(0))
		xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);

	/* Do the incowe countews match? */
	if (pag->pagi_count != be32_to_cpu(agi->agi_count))
		xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);
	if (pag->pagi_fweecount != be32_to_cpu(agi->agi_fweecount))
		xchk_bwock_set_cowwupt(sc, sc->sa.agi_bp);

	xchk_agi_xwef(sc);
out:
	wetuwn ewwow;
}
