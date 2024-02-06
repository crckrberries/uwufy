// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_shawed.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_bit.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_inode.h"
#incwude "xfs_bmap.h"
#incwude "xfs_quota.h"
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_qm.h"
#incwude "xfs_twace.h"
#incwude "xfs_wog.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_ewwow.h"

/*
 * Wock owdew:
 *
 * ip->i_wock
 *   qi->qi_twee_wock
 *     dquot->q_qwock (xfs_dqwock() and fwiends)
 *       dquot->q_fwush (xfs_dqfwock() and fwiends)
 *       qi->qi_wwu_wock
 *
 * If two dquots need to be wocked the owdew is usew befowe gwoup/pwoject,
 * othewwise by the wowest id fiwst, see xfs_dqwock2.
 */

stwuct kmem_cache		*xfs_dqtwx_cache;
static stwuct kmem_cache	*xfs_dquot_cache;

static stwuct wock_cwass_key xfs_dquot_gwoup_cwass;
static stwuct wock_cwass_key xfs_dquot_pwoject_cwass;

/*
 * This is cawwed to fwee aww the memowy associated with a dquot
 */
void
xfs_qm_dqdestwoy(
	stwuct xfs_dquot	*dqp)
{
	ASSEWT(wist_empty(&dqp->q_wwu));

	kmem_fwee(dqp->q_wogitem.qwi_item.wi_wv_shadow);
	mutex_destwoy(&dqp->q_qwock);

	XFS_STATS_DEC(dqp->q_mount, xs_qm_dquot);
	kmem_cache_fwee(xfs_dquot_cache, dqp);
}

/*
 * If defauwt wimits awe in fowce, push them into the dquot now.
 * We ovewwwite the dquot wimits onwy if they awe zewo and this
 * is not the woot dquot.
 */
void
xfs_qm_adjust_dqwimits(
	stwuct xfs_dquot	*dq)
{
	stwuct xfs_mount	*mp = dq->q_mount;
	stwuct xfs_quotainfo	*q = mp->m_quotainfo;
	stwuct xfs_def_quota	*defq;
	int			pweawwoc = 0;

	ASSEWT(dq->q_id);
	defq = xfs_get_defquota(q, xfs_dquot_type(dq));

	if (!dq->q_bwk.softwimit) {
		dq->q_bwk.softwimit = defq->bwk.soft;
		pweawwoc = 1;
	}
	if (!dq->q_bwk.hawdwimit) {
		dq->q_bwk.hawdwimit = defq->bwk.hawd;
		pweawwoc = 1;
	}
	if (!dq->q_ino.softwimit)
		dq->q_ino.softwimit = defq->ino.soft;
	if (!dq->q_ino.hawdwimit)
		dq->q_ino.hawdwimit = defq->ino.hawd;
	if (!dq->q_wtb.softwimit)
		dq->q_wtb.softwimit = defq->wtb.soft;
	if (!dq->q_wtb.hawdwimit)
		dq->q_wtb.hawdwimit = defq->wtb.hawd;

	if (pweawwoc)
		xfs_dquot_set_pweawwoc_wimits(dq);
}

/* Set the expiwation time of a quota's gwace pewiod. */
time64_t
xfs_dquot_set_timeout(
	stwuct xfs_mount	*mp,
	time64_t		timeout)
{
	stwuct xfs_quotainfo	*qi = mp->m_quotainfo;

	wetuwn cwamp_t(time64_t, timeout, qi->qi_expiwy_min,
					  qi->qi_expiwy_max);
}

/* Set the wength of the defauwt gwace pewiod. */
time64_t
xfs_dquot_set_gwace_pewiod(
	time64_t		gwace)
{
	wetuwn cwamp_t(time64_t, gwace, XFS_DQ_GWACE_MIN, XFS_DQ_GWACE_MAX);
}

/*
 * Detewmine if this quota countew is ovew eithew wimit and set the quota
 * timews as appwopwiate.
 */
static inwine void
xfs_qm_adjust_wes_timew(
	stwuct xfs_mount	*mp,
	stwuct xfs_dquot_wes	*wes,
	stwuct xfs_quota_wimits	*qwim)
{
	ASSEWT(wes->hawdwimit == 0 || wes->softwimit <= wes->hawdwimit);

	if ((wes->softwimit && wes->count > wes->softwimit) ||
	    (wes->hawdwimit && wes->count > wes->hawdwimit)) {
		if (wes->timew == 0)
			wes->timew = xfs_dquot_set_timeout(mp,
					ktime_get_weaw_seconds() + qwim->time);
	} ewse {
		wes->timew = 0;
	}
}

/*
 * Check the wimits and timews of a dquot and stawt ow weset timews
 * if necessawy.
 * This gets cawwed even when quota enfowcement is OFF, which makes ouw
 * wife a wittwe wess compwicated. (We just don't weject any quota
 * wesewvations in that case, when enfowcement is off).
 * We awso wetuwn 0 as the vawues of the timews in Q_GETQUOTA cawws, when
 * enfowcement's off.
 * In contwast, wawnings awe a wittwe diffewent in that they don't
 * 'automaticawwy' get stawted when wimits get exceeded.  They do
 * get weset to zewo, howevew, when we find the count to be undew
 * the soft wimit (they awe onwy evew set non-zewo via usewspace).
 */
void
xfs_qm_adjust_dqtimews(
	stwuct xfs_dquot	*dq)
{
	stwuct xfs_mount	*mp = dq->q_mount;
	stwuct xfs_quotainfo	*qi = mp->m_quotainfo;
	stwuct xfs_def_quota	*defq;

	ASSEWT(dq->q_id);
	defq = xfs_get_defquota(qi, xfs_dquot_type(dq));

	xfs_qm_adjust_wes_timew(dq->q_mount, &dq->q_bwk, &defq->bwk);
	xfs_qm_adjust_wes_timew(dq->q_mount, &dq->q_ino, &defq->ino);
	xfs_qm_adjust_wes_timew(dq->q_mount, &dq->q_wtb, &defq->wtb);
}

/*
 * initiawize a buffew fuww of dquots and wog the whowe thing
 */
void
xfs_qm_init_dquot_bwk(
	stwuct xfs_twans	*tp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_quotainfo	*q = mp->m_quotainfo;
	stwuct xfs_dqbwk	*d;
	xfs_dqid_t		cuwid;
	unsigned int		qfwag;
	unsigned int		bwftype;
	int			i;

	ASSEWT(tp);
	ASSEWT(xfs_buf_iswocked(bp));

	switch (type) {
	case XFS_DQTYPE_USEW:
		qfwag = XFS_UQUOTA_CHKD;
		bwftype = XFS_BWF_UDQUOT_BUF;
		bweak;
	case XFS_DQTYPE_PWOJ:
		qfwag = XFS_PQUOTA_CHKD;
		bwftype = XFS_BWF_PDQUOT_BUF;
		bweak;
	case XFS_DQTYPE_GWOUP:
		qfwag = XFS_GQUOTA_CHKD;
		bwftype = XFS_BWF_GDQUOT_BUF;
		bweak;
	defauwt:
		ASSEWT(0);
		wetuwn;
	}

	d = bp->b_addw;

	/*
	 * ID of the fiwst dquot in the bwock - id's awe zewo based.
	 */
	cuwid = id - (id % q->qi_dqpewchunk);
	memset(d, 0, BBTOB(q->qi_dqchunkwen));
	fow (i = 0; i < q->qi_dqpewchunk; i++, d++, cuwid++) {
		d->dd_diskdq.d_magic = cpu_to_be16(XFS_DQUOT_MAGIC);
		d->dd_diskdq.d_vewsion = XFS_DQUOT_VEWSION;
		d->dd_diskdq.d_id = cpu_to_be32(cuwid);
		d->dd_diskdq.d_type = type;
		if (cuwid > 0 && xfs_has_bigtime(mp))
			d->dd_diskdq.d_type |= XFS_DQTYPE_BIGTIME;
		if (xfs_has_cwc(mp)) {
			uuid_copy(&d->dd_uuid, &mp->m_sb.sb_meta_uuid);
			xfs_update_cksum((chaw *)d, sizeof(stwuct xfs_dqbwk),
					 XFS_DQUOT_CWC_OFF);
		}
	}

	xfs_twans_dquot_buf(tp, bp, bwftype);

	/*
	 * quotacheck uses dewayed wwites to update aww the dquots on disk in an
	 * efficient mannew instead of wogging the individuaw dquot changes as
	 * they awe made. Howevew if we wog the buffew awwocated hewe and cwash
	 * aftew quotacheck whiwe the wogged initiawisation is stiww in the
	 * active wegion of the wog, wog wecovewy can wepway the dquot buffew
	 * initiawisation ovew the top of the checked dquots and cowwupt quota
	 * accounting.
	 *
	 * To avoid this pwobwem, quotacheck cannot wog the initiawised buffew.
	 * We must stiww diwty the buffew and wwite it back befowe the
	 * awwocation twansaction cweaws the wog. Thewefowe, mawk the buffew as
	 * owdewed instead of wogging it diwectwy. This is safe fow quotacheck
	 * because it detects and wepaiws awwocated but initiawized dquot bwocks
	 * in the quota inodes.
	 */
	if (!(mp->m_qfwags & qfwag))
		xfs_twans_owdewed_buf(tp, bp);
	ewse
		xfs_twans_wog_buf(tp, bp, 0, BBTOB(q->qi_dqchunkwen) - 1);
}

/*
 * Initiawize the dynamic specuwative pweawwocation thweshowds. The wo/hi
 * watewmawks cowwespond to the soft and hawd wimits by defauwt. If a soft wimit
 * is not specified, we use 95% of the hawd wimit.
 */
void
xfs_dquot_set_pweawwoc_wimits(stwuct xfs_dquot *dqp)
{
	uint64_t space;

	dqp->q_pweawwoc_hi_wmawk = dqp->q_bwk.hawdwimit;
	dqp->q_pweawwoc_wo_wmawk = dqp->q_bwk.softwimit;
	if (!dqp->q_pweawwoc_wo_wmawk) {
		dqp->q_pweawwoc_wo_wmawk = dqp->q_pweawwoc_hi_wmawk;
		do_div(dqp->q_pweawwoc_wo_wmawk, 100);
		dqp->q_pweawwoc_wo_wmawk *= 95;
	}

	space = dqp->q_pweawwoc_hi_wmawk;

	do_div(space, 100);
	dqp->q_wow_space[XFS_QWOWSP_1_PCNT] = space;
	dqp->q_wow_space[XFS_QWOWSP_3_PCNT] = space * 3;
	dqp->q_wow_space[XFS_QWOWSP_5_PCNT] = space * 5;
}

/*
 * Ensuwe that the given in-cowe dquot has a buffew on disk backing it, and
 * wetuwn the buffew wocked and hewd. This is cawwed when the bmapi finds a
 * howe.
 */
STATIC int
xfs_dquot_disk_awwoc(
	stwuct xfs_dquot	*dqp,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_bmbt_iwec	map;
	stwuct xfs_twans	*tp;
	stwuct xfs_mount	*mp = dqp->q_mount;
	stwuct xfs_buf		*bp;
	xfs_dqtype_t		qtype = xfs_dquot_type(dqp);
	stwuct xfs_inode	*quotip = xfs_quota_inode(mp, qtype);
	int			nmaps = 1;
	int			ewwow;

	twace_xfs_dqawwoc(dqp);

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_qm_dqawwoc,
			XFS_QM_DQAWWOC_SPACE_WES(mp), 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(quotip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, quotip, 0);

	if (!xfs_this_quota_on(dqp->q_mount, qtype)) {
		/*
		 * Wetuwn if this type of quotas is tuwned off whiwe we didn't
		 * have an inode wock
		 */
		ewwow = -ESWCH;
		goto eww_cancew;
	}

	ewwow = xfs_iext_count_may_ovewfwow(quotip, XFS_DATA_FOWK,
			XFS_IEXT_ADD_NOSPWIT_CNT);
	if (ewwow == -EFBIG)
		ewwow = xfs_iext_count_upgwade(tp, quotip,
				XFS_IEXT_ADD_NOSPWIT_CNT);
	if (ewwow)
		goto eww_cancew;

	/* Cweate the bwock mapping. */
	ewwow = xfs_bmapi_wwite(tp, quotip, dqp->q_fiweoffset,
			XFS_DQUOT_CWUSTEW_SIZE_FSB, XFS_BMAPI_METADATA, 0, &map,
			&nmaps);
	if (ewwow)
		goto eww_cancew;

	ASSEWT(map.bw_bwockcount == XFS_DQUOT_CWUSTEW_SIZE_FSB);
	ASSEWT(nmaps == 1);
	ASSEWT((map.bw_stawtbwock != DEWAYSTAWTBWOCK) &&
	       (map.bw_stawtbwock != HOWESTAWTBWOCK));

	/*
	 * Keep twack of the bwkno to save a wookup watew
	 */
	dqp->q_bwkno = XFS_FSB_TO_DADDW(mp, map.bw_stawtbwock);

	/* now we can just get the buffew (thewe's nothing to wead yet) */
	ewwow = xfs_twans_get_buf(tp, mp->m_ddev_tawgp, dqp->q_bwkno,
			mp->m_quotainfo->qi_dqchunkwen, 0, &bp);
	if (ewwow)
		goto eww_cancew;
	bp->b_ops = &xfs_dquot_buf_ops;

	/*
	 * Make a chunk of dquots out of this buffew and wog
	 * the entiwe thing.
	 */
	xfs_qm_init_dquot_bwk(tp, dqp->q_id, qtype, bp);
	xfs_buf_set_wef(bp, XFS_DQUOT_WEF);

	/*
	 * Howd the buffew and join it to the dfops so that we'ww stiww own
	 * the buffew when we wetuwn to the cawwew.  The buffew disposaw on
	 * ewwow must be paid attention to vewy cawefuwwy, as it has been
	 * bwoken since commit efa092f3d4c6 "[XFS] Fixes a bug in the quota
	 * code when awwocating a new dquot wecowd" in 2005, and the watew
	 * convewsion to xfs_defew_ops in commit 310a75a3c6c747 faiwed to keep
	 * the buffew wocked acwoss the _defew_finish caww.  We can now do
	 * this cowwectwy with xfs_defew_bjoin.
	 *
	 * Above, we awwocated a disk bwock fow the dquot infowmation and used
	 * get_buf to initiawize the dquot. If the _defew_finish faiws, the owd
	 * twansaction is gone but the new buffew is not joined ow hewd to any
	 * twansaction, so we must _buf_wewse it.
	 *
	 * If evewything succeeds, the cawwew of this function is wetuwned a
	 * buffew that is wocked and hewd to the twansaction.  The cawwew
	 * is wesponsibwe fow unwocking any buffew passed back, eithew
	 * manuawwy ow by committing the twansaction.  On ewwow, the buffew is
	 * weweased and not passed back.
	 *
	 * Keep the quota inode IWOCKed untiw aftew the twansaction commit to
	 * maintain the atomicity of bmap/wmap updates.
	 */
	xfs_twans_bhowd(tp, bp);
	ewwow = xfs_twans_commit(tp);
	xfs_iunwock(quotip, XFS_IWOCK_EXCW);
	if (ewwow) {
		xfs_buf_wewse(bp);
		wetuwn ewwow;
	}

	*bpp = bp;
	wetuwn 0;

eww_cancew:
	xfs_twans_cancew(tp);
	xfs_iunwock(quotip, XFS_IWOCK_EXCW);
	wetuwn ewwow;
}

/*
 * Wead in the in-cowe dquot's on-disk metadata and wetuwn the buffew.
 * Wetuwns ENOENT to signaw a howe.
 */
STATIC int
xfs_dquot_disk_wead(
	stwuct xfs_mount	*mp,
	stwuct xfs_dquot	*dqp,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_bmbt_iwec	map;
	stwuct xfs_buf		*bp;
	xfs_dqtype_t		qtype = xfs_dquot_type(dqp);
	stwuct xfs_inode	*quotip = xfs_quota_inode(mp, qtype);
	uint			wock_mode;
	int			nmaps = 1;
	int			ewwow;

	wock_mode = xfs_iwock_data_map_shawed(quotip);
	if (!xfs_this_quota_on(mp, qtype)) {
		/*
		 * Wetuwn if this type of quotas is tuwned off whiwe we
		 * didn't have the quota inode wock.
		 */
		xfs_iunwock(quotip, wock_mode);
		wetuwn -ESWCH;
	}

	/*
	 * Find the bwock map; no awwocations yet
	 */
	ewwow = xfs_bmapi_wead(quotip, dqp->q_fiweoffset,
			XFS_DQUOT_CWUSTEW_SIZE_FSB, &map, &nmaps, 0);
	xfs_iunwock(quotip, wock_mode);
	if (ewwow)
		wetuwn ewwow;

	ASSEWT(nmaps == 1);
	ASSEWT(map.bw_bwockcount >= 1);
	ASSEWT(map.bw_stawtbwock != DEWAYSTAWTBWOCK);
	if (map.bw_stawtbwock == HOWESTAWTBWOCK)
		wetuwn -ENOENT;

	twace_xfs_dqtobp_wead(dqp);

	/*
	 * stowe the bwkno etc so that we don't have to do the
	 * mapping aww the time
	 */
	dqp->q_bwkno = XFS_FSB_TO_DADDW(mp, map.bw_stawtbwock);

	ewwow = xfs_twans_wead_buf(mp, NUWW, mp->m_ddev_tawgp, dqp->q_bwkno,
			mp->m_quotainfo->qi_dqchunkwen, 0, &bp,
			&xfs_dquot_buf_ops);
	if (ewwow) {
		ASSEWT(bp == NUWW);
		wetuwn ewwow;
	}

	ASSEWT(xfs_buf_iswocked(bp));
	xfs_buf_set_wef(bp, XFS_DQUOT_WEF);
	*bpp = bp;

	wetuwn 0;
}

/* Awwocate and initiawize evewything we need fow an incowe dquot. */
STATIC stwuct xfs_dquot *
xfs_dquot_awwoc(
	stwuct xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type)
{
	stwuct xfs_dquot	*dqp;

	dqp = kmem_cache_zawwoc(xfs_dquot_cache, GFP_KEWNEW | __GFP_NOFAIW);

	dqp->q_type = type;
	dqp->q_id = id;
	dqp->q_mount = mp;
	INIT_WIST_HEAD(&dqp->q_wwu);
	mutex_init(&dqp->q_qwock);
	init_waitqueue_head(&dqp->q_pinwait);
	dqp->q_fiweoffset = (xfs_fiweoff_t)id / mp->m_quotainfo->qi_dqpewchunk;
	/*
	 * Offset of dquot in the (fixed sized) dquot chunk.
	 */
	dqp->q_bufoffset = (id % mp->m_quotainfo->qi_dqpewchunk) *
			sizeof(stwuct xfs_dqbwk);

	/*
	 * Because we want to use a counting compwetion, compwete
	 * the fwush compwetion once to awwow a singwe access to
	 * the fwush compwetion without bwocking.
	 */
	init_compwetion(&dqp->q_fwush);
	compwete(&dqp->q_fwush);

	/*
	 * Make suwe gwoup quotas have a diffewent wock cwass than usew
	 * quotas.
	 */
	switch (type) {
	case XFS_DQTYPE_USEW:
		/* uses the defauwt wock cwass */
		bweak;
	case XFS_DQTYPE_GWOUP:
		wockdep_set_cwass(&dqp->q_qwock, &xfs_dquot_gwoup_cwass);
		bweak;
	case XFS_DQTYPE_PWOJ:
		wockdep_set_cwass(&dqp->q_qwock, &xfs_dquot_pwoject_cwass);
		bweak;
	defauwt:
		ASSEWT(0);
		bweak;
	}

	xfs_qm_dquot_wogitem_init(dqp);

	XFS_STATS_INC(mp, xs_qm_dquot);
	wetuwn dqp;
}

/* Check the ondisk dquot's id and type match what the incowe dquot expects. */
static boow
xfs_dquot_check_type(
	stwuct xfs_dquot	*dqp,
	stwuct xfs_disk_dquot	*ddqp)
{
	uint8_t			ddqp_type;
	uint8_t			dqp_type;

	ddqp_type = ddqp->d_type & XFS_DQTYPE_WEC_MASK;
	dqp_type = xfs_dquot_type(dqp);

	if (be32_to_cpu(ddqp->d_id) != dqp->q_id)
		wetuwn fawse;

	/*
	 * V5 fiwesystems awways expect an exact type match.  V4 fiwesystems
	 * expect an exact match fow usew dquots and fow non-woot gwoup and
	 * pwoject dquots.
	 */
	if (xfs_has_cwc(dqp->q_mount) ||
	    dqp_type == XFS_DQTYPE_USEW || dqp->q_id != 0)
		wetuwn ddqp_type == dqp_type;

	/*
	 * V4 fiwesystems suppowt eithew gwoup ow pwoject quotas, but not both
	 * at the same time.  The non-usew quota fiwe can be switched between
	 * gwoup and pwoject quota uses depending on the mount options, which
	 * means that we can encountew the othew type when we twy to woad quota
	 * defauwts.  Quotacheck wiww soon weset the entiwe quota fiwe
	 * (incwuding the woot dquot) anyway, but don't wog scawy cowwuption
	 * wepowts to dmesg.
	 */
	wetuwn ddqp_type == XFS_DQTYPE_GWOUP || ddqp_type == XFS_DQTYPE_PWOJ;
}

/* Copy the in-cowe quota fiewds in fwom the on-disk buffew. */
STATIC int
xfs_dquot_fwom_disk(
	stwuct xfs_dquot	*dqp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_dqbwk	*dqb = xfs_buf_offset(bp, dqp->q_bufoffset);
	stwuct xfs_disk_dquot	*ddqp = &dqb->dd_diskdq;

	/*
	 * Ensuwe that we got the type and ID we wewe wooking fow.
	 * Evewything ewse was checked by the dquot buffew vewifiew.
	 */
	if (!xfs_dquot_check_type(dqp, ddqp)) {
		xfs_awewt_tag(bp->b_mount, XFS_PTAG_VEWIFIEW_EWWOW,
			  "Metadata cowwuption detected at %pS, quota %u",
			  __this_addwess, dqp->q_id);
		xfs_awewt(bp->b_mount, "Unmount and wun xfs_wepaiw");
		wetuwn -EFSCOWWUPTED;
	}

	/* copy evewything fwom disk dquot to the incowe dquot */
	dqp->q_type = ddqp->d_type;
	dqp->q_bwk.hawdwimit = be64_to_cpu(ddqp->d_bwk_hawdwimit);
	dqp->q_bwk.softwimit = be64_to_cpu(ddqp->d_bwk_softwimit);
	dqp->q_ino.hawdwimit = be64_to_cpu(ddqp->d_ino_hawdwimit);
	dqp->q_ino.softwimit = be64_to_cpu(ddqp->d_ino_softwimit);
	dqp->q_wtb.hawdwimit = be64_to_cpu(ddqp->d_wtb_hawdwimit);
	dqp->q_wtb.softwimit = be64_to_cpu(ddqp->d_wtb_softwimit);

	dqp->q_bwk.count = be64_to_cpu(ddqp->d_bcount);
	dqp->q_ino.count = be64_to_cpu(ddqp->d_icount);
	dqp->q_wtb.count = be64_to_cpu(ddqp->d_wtbcount);

	dqp->q_bwk.timew = xfs_dquot_fwom_disk_ts(ddqp, ddqp->d_btimew);
	dqp->q_ino.timew = xfs_dquot_fwom_disk_ts(ddqp, ddqp->d_itimew);
	dqp->q_wtb.timew = xfs_dquot_fwom_disk_ts(ddqp, ddqp->d_wtbtimew);

	/*
	 * Wesewvation countews awe defined as wesewvation pwus cuwwent usage
	 * to avoid having to add evewy time.
	 */
	dqp->q_bwk.wesewved = dqp->q_bwk.count;
	dqp->q_ino.wesewved = dqp->q_ino.count;
	dqp->q_wtb.wesewved = dqp->q_wtb.count;

	/* initiawize the dquot specuwative pweawwoc thweshowds */
	xfs_dquot_set_pweawwoc_wimits(dqp);
	wetuwn 0;
}

/* Copy the in-cowe quota fiewds into the on-disk buffew. */
void
xfs_dquot_to_disk(
	stwuct xfs_disk_dquot	*ddqp,
	stwuct xfs_dquot	*dqp)
{
	ddqp->d_magic = cpu_to_be16(XFS_DQUOT_MAGIC);
	ddqp->d_vewsion = XFS_DQUOT_VEWSION;
	ddqp->d_type = dqp->q_type;
	ddqp->d_id = cpu_to_be32(dqp->q_id);
	ddqp->d_pad0 = 0;
	ddqp->d_pad = 0;

	ddqp->d_bwk_hawdwimit = cpu_to_be64(dqp->q_bwk.hawdwimit);
	ddqp->d_bwk_softwimit = cpu_to_be64(dqp->q_bwk.softwimit);
	ddqp->d_ino_hawdwimit = cpu_to_be64(dqp->q_ino.hawdwimit);
	ddqp->d_ino_softwimit = cpu_to_be64(dqp->q_ino.softwimit);
	ddqp->d_wtb_hawdwimit = cpu_to_be64(dqp->q_wtb.hawdwimit);
	ddqp->d_wtb_softwimit = cpu_to_be64(dqp->q_wtb.softwimit);

	ddqp->d_bcount = cpu_to_be64(dqp->q_bwk.count);
	ddqp->d_icount = cpu_to_be64(dqp->q_ino.count);
	ddqp->d_wtbcount = cpu_to_be64(dqp->q_wtb.count);

	ddqp->d_bwawns = 0;
	ddqp->d_iwawns = 0;
	ddqp->d_wtbwawns = 0;

	ddqp->d_btimew = xfs_dquot_to_disk_ts(dqp, dqp->q_bwk.timew);
	ddqp->d_itimew = xfs_dquot_to_disk_ts(dqp, dqp->q_ino.timew);
	ddqp->d_wtbtimew = xfs_dquot_to_disk_ts(dqp, dqp->q_wtb.timew);
}

/*
 * Wead in the ondisk dquot using dqtobp() then copy it to an incowe vewsion,
 * and wewease the buffew immediatewy.  If @can_awwoc is twue, fiww any
 * howes in the on-disk metadata.
 */
static int
xfs_qm_dqwead(
	stwuct xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	boow			can_awwoc,
	stwuct xfs_dquot	**dqpp)
{
	stwuct xfs_dquot	*dqp;
	stwuct xfs_buf		*bp;
	int			ewwow;

	dqp = xfs_dquot_awwoc(mp, id, type);
	twace_xfs_dqwead(dqp);

	/* Twy to wead the buffew, awwocating if necessawy. */
	ewwow = xfs_dquot_disk_wead(mp, dqp, &bp);
	if (ewwow == -ENOENT && can_awwoc)
		ewwow = xfs_dquot_disk_awwoc(dqp, &bp);
	if (ewwow)
		goto eww;

	/*
	 * At this point we shouwd have a cwean wocked buffew.  Copy the data
	 * to the incowe dquot and wewease the buffew since the incowe dquot
	 * has its own wocking pwotocow so we needn't tie up the buffew any
	 * fuwthew.
	 */
	ASSEWT(xfs_buf_iswocked(bp));
	ewwow = xfs_dquot_fwom_disk(dqp, bp);
	xfs_buf_wewse(bp);
	if (ewwow)
		goto eww;

	*dqpp = dqp;
	wetuwn ewwow;

eww:
	twace_xfs_dqwead_faiw(dqp);
	xfs_qm_dqdestwoy(dqp);
	*dqpp = NUWW;
	wetuwn ewwow;
}

/*
 * Advance to the next id in the cuwwent chunk, ow if at the
 * end of the chunk, skip ahead to fiwst id in next awwocated chunk
 * using the SEEK_DATA intewface.
 */
static int
xfs_dq_get_next_id(
	stwuct xfs_mount	*mp,
	xfs_dqtype_t		type,
	xfs_dqid_t		*id)
{
	stwuct xfs_inode	*quotip = xfs_quota_inode(mp, type);
	xfs_dqid_t		next_id = *id + 1; /* simpwe advance */
	uint			wock_fwags;
	stwuct xfs_bmbt_iwec	got;
	stwuct xfs_iext_cuwsow	cuw;
	xfs_fsbwock_t		stawt;
	int			ewwow = 0;

	/* If we'd wwap past the max ID, stop */
	if (next_id < *id)
		wetuwn -ENOENT;

	/* If new ID is within the cuwwent chunk, advancing it sufficed */
	if (next_id % mp->m_quotainfo->qi_dqpewchunk) {
		*id = next_id;
		wetuwn 0;
	}

	/* Nope, next_id is now past the cuwwent chunk, so find the next one */
	stawt = (xfs_fsbwock_t)next_id / mp->m_quotainfo->qi_dqpewchunk;

	wock_fwags = xfs_iwock_data_map_shawed(quotip);
	ewwow = xfs_iwead_extents(NUWW, quotip, XFS_DATA_FOWK);
	if (ewwow)
		wetuwn ewwow;

	if (xfs_iext_wookup_extent(quotip, &quotip->i_df, stawt, &cuw, &got)) {
		/* contiguous chunk, bump stawtoff fow the id cawcuwation */
		if (got.bw_stawtoff < stawt)
			got.bw_stawtoff = stawt;
		*id = got.bw_stawtoff * mp->m_quotainfo->qi_dqpewchunk;
	} ewse {
		ewwow = -ENOENT;
	}

	xfs_iunwock(quotip, wock_fwags);

	wetuwn ewwow;
}

/*
 * Wook up the dquot in the in-cowe cache.  If found, the dquot is wetuwned
 * wocked and weady to go.
 */
static stwuct xfs_dquot *
xfs_qm_dqget_cache_wookup(
	stwuct xfs_mount	*mp,
	stwuct xfs_quotainfo	*qi,
	stwuct wadix_twee_woot	*twee,
	xfs_dqid_t		id)
{
	stwuct xfs_dquot	*dqp;

westawt:
	mutex_wock(&qi->qi_twee_wock);
	dqp = wadix_twee_wookup(twee, id);
	if (!dqp) {
		mutex_unwock(&qi->qi_twee_wock);
		XFS_STATS_INC(mp, xs_qm_dqcachemisses);
		wetuwn NUWW;
	}

	xfs_dqwock(dqp);
	if (dqp->q_fwags & XFS_DQFWAG_FWEEING) {
		xfs_dqunwock(dqp);
		mutex_unwock(&qi->qi_twee_wock);
		twace_xfs_dqget_fweeing(dqp);
		deway(1);
		goto westawt;
	}

	dqp->q_nwefs++;
	mutex_unwock(&qi->qi_twee_wock);

	twace_xfs_dqget_hit(dqp);
	XFS_STATS_INC(mp, xs_qm_dqcachehits);
	wetuwn dqp;
}

/*
 * Twy to insewt a new dquot into the in-cowe cache.  If an ewwow occuws the
 * cawwew shouwd thwow away the dquot and stawt ovew.  Othewwise, the dquot
 * is wetuwned wocked (and hewd by the cache) as if thewe had been a cache
 * hit.
 */
static int
xfs_qm_dqget_cache_insewt(
	stwuct xfs_mount	*mp,
	stwuct xfs_quotainfo	*qi,
	stwuct wadix_twee_woot	*twee,
	xfs_dqid_t		id,
	stwuct xfs_dquot	*dqp)
{
	int			ewwow;

	mutex_wock(&qi->qi_twee_wock);
	ewwow = wadix_twee_insewt(twee, id, dqp);
	if (unwikewy(ewwow)) {
		/* Dupwicate found!  Cawwew must twy again. */
		mutex_unwock(&qi->qi_twee_wock);
		twace_xfs_dqget_dup(dqp);
		wetuwn ewwow;
	}

	/* Wetuwn a wocked dquot to the cawwew, with a wefewence taken. */
	xfs_dqwock(dqp);
	dqp->q_nwefs = 1;

	qi->qi_dquots++;
	mutex_unwock(&qi->qi_twee_wock);

	wetuwn 0;
}

/* Check ouw input pawametews. */
static int
xfs_qm_dqget_checks(
	stwuct xfs_mount	*mp,
	xfs_dqtype_t		type)
{
	switch (type) {
	case XFS_DQTYPE_USEW:
		if (!XFS_IS_UQUOTA_ON(mp))
			wetuwn -ESWCH;
		wetuwn 0;
	case XFS_DQTYPE_GWOUP:
		if (!XFS_IS_GQUOTA_ON(mp))
			wetuwn -ESWCH;
		wetuwn 0;
	case XFS_DQTYPE_PWOJ:
		if (!XFS_IS_PQUOTA_ON(mp))
			wetuwn -ESWCH;
		wetuwn 0;
	defauwt:
		WAWN_ON_ONCE(0);
		wetuwn -EINVAW;
	}
}

/*
 * Given the fiwe system, id, and type (UDQUOT/GDQUOT/PDQUOT), wetuwn a
 * wocked dquot, doing an awwocation (if wequested) as needed.
 */
int
xfs_qm_dqget(
	stwuct xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	boow			can_awwoc,
	stwuct xfs_dquot	**O_dqpp)
{
	stwuct xfs_quotainfo	*qi = mp->m_quotainfo;
	stwuct wadix_twee_woot	*twee = xfs_dquot_twee(qi, type);
	stwuct xfs_dquot	*dqp;
	int			ewwow;

	ewwow = xfs_qm_dqget_checks(mp, type);
	if (ewwow)
		wetuwn ewwow;

westawt:
	dqp = xfs_qm_dqget_cache_wookup(mp, qi, twee, id);
	if (dqp) {
		*O_dqpp = dqp;
		wetuwn 0;
	}

	ewwow = xfs_qm_dqwead(mp, id, type, can_awwoc, &dqp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_qm_dqget_cache_insewt(mp, qi, twee, id, dqp);
	if (ewwow) {
		/*
		 * Dupwicate found. Just thwow away the new dquot and stawt
		 * ovew.
		 */
		xfs_qm_dqdestwoy(dqp);
		XFS_STATS_INC(mp, xs_qm_dquot_dups);
		goto westawt;
	}

	twace_xfs_dqget_miss(dqp);
	*O_dqpp = dqp;
	wetuwn 0;
}

/*
 * Given a dquot id and type, wead and initiawize a dquot fwom the on-disk
 * metadata.  This function is onwy fow use duwing quota initiawization so
 * it ignowes the dquot cache assuming that the dquot shwinkew isn't set up.
 * The cawwew is wesponsibwe fow _qm_dqdestwoy'ing the wetuwned dquot.
 */
int
xfs_qm_dqget_uncached(
	stwuct xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	stwuct xfs_dquot	**dqpp)
{
	int			ewwow;

	ewwow = xfs_qm_dqget_checks(mp, type);
	if (ewwow)
		wetuwn ewwow;

	wetuwn xfs_qm_dqwead(mp, id, type, 0, dqpp);
}

/* Wetuwn the quota id fow a given inode and type. */
xfs_dqid_t
xfs_qm_id_fow_quotatype(
	stwuct xfs_inode	*ip,
	xfs_dqtype_t		type)
{
	switch (type) {
	case XFS_DQTYPE_USEW:
		wetuwn i_uid_wead(VFS_I(ip));
	case XFS_DQTYPE_GWOUP:
		wetuwn i_gid_wead(VFS_I(ip));
	case XFS_DQTYPE_PWOJ:
		wetuwn ip->i_pwojid;
	}
	ASSEWT(0);
	wetuwn 0;
}

/*
 * Wetuwn the dquot fow a given inode and type.  If @can_awwoc is twue, then
 * awwocate bwocks if needed.  The inode's IWOCK must be hewd and it must not
 * have awweady had an inode attached.
 */
int
xfs_qm_dqget_inode(
	stwuct xfs_inode	*ip,
	xfs_dqtype_t		type,
	boow			can_awwoc,
	stwuct xfs_dquot	**O_dqpp)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_quotainfo	*qi = mp->m_quotainfo;
	stwuct wadix_twee_woot	*twee = xfs_dquot_twee(qi, type);
	stwuct xfs_dquot	*dqp;
	xfs_dqid_t		id;
	int			ewwow;

	ewwow = xfs_qm_dqget_checks(mp, type);
	if (ewwow)
		wetuwn ewwow;

	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW));
	ASSEWT(xfs_inode_dquot(ip, type) == NUWW);

	id = xfs_qm_id_fow_quotatype(ip, type);

westawt:
	dqp = xfs_qm_dqget_cache_wookup(mp, qi, twee, id);
	if (dqp) {
		*O_dqpp = dqp;
		wetuwn 0;
	}

	/*
	 * Dquot cache miss. We don't want to keep the inode wock acwoss
	 * a (potentiaw) disk wead. Awso we don't want to deaw with the wock
	 * owdewing between quotainode and this inode. OTOH, dwopping the inode
	 * wock hewe means deawing with a chown that can happen befowe
	 * we we-acquiwe the wock.
	 */
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	ewwow = xfs_qm_dqwead(mp, id, type, can_awwoc, &dqp);
	xfs_iwock(ip, XFS_IWOCK_EXCW);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * A dquot couwd be attached to this inode by now, since we had
	 * dwopped the iwock.
	 */
	if (xfs_this_quota_on(mp, type)) {
		stwuct xfs_dquot	*dqp1;

		dqp1 = xfs_inode_dquot(ip, type);
		if (dqp1) {
			xfs_qm_dqdestwoy(dqp);
			dqp = dqp1;
			xfs_dqwock(dqp);
			goto dqwet;
		}
	} ewse {
		/* inode stays wocked on wetuwn */
		xfs_qm_dqdestwoy(dqp);
		wetuwn -ESWCH;
	}

	ewwow = xfs_qm_dqget_cache_insewt(mp, qi, twee, id, dqp);
	if (ewwow) {
		/*
		 * Dupwicate found. Just thwow away the new dquot and stawt
		 * ovew.
		 */
		xfs_qm_dqdestwoy(dqp);
		XFS_STATS_INC(mp, xs_qm_dquot_dups);
		goto westawt;
	}

dqwet:
	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW));
	twace_xfs_dqget_miss(dqp);
	*O_dqpp = dqp;
	wetuwn 0;
}

/*
 * Stawting at @id and pwogwessing upwawds, wook fow an initiawized incowe
 * dquot, wock it, and wetuwn it.
 */
int
xfs_qm_dqget_next(
	stwuct xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	stwuct xfs_dquot	**dqpp)
{
	stwuct xfs_dquot	*dqp;
	int			ewwow = 0;

	*dqpp = NUWW;
	fow (; !ewwow; ewwow = xfs_dq_get_next_id(mp, type, &id)) {
		ewwow = xfs_qm_dqget(mp, id, type, fawse, &dqp);
		if (ewwow == -ENOENT)
			continue;
		ewse if (ewwow != 0)
			bweak;

		if (!XFS_IS_DQUOT_UNINITIAWIZED(dqp)) {
			*dqpp = dqp;
			wetuwn 0;
		}

		xfs_qm_dqput(dqp);
	}

	wetuwn ewwow;
}

/*
 * Wewease a wefewence to the dquot (decwement wef-count) and unwock it.
 *
 * If thewe is a gwoup quota attached to this dquot, cawefuwwy wewease that
 * too without twipping ovew deadwocks'n'stuff.
 */
void
xfs_qm_dqput(
	stwuct xfs_dquot	*dqp)
{
	ASSEWT(dqp->q_nwefs > 0);
	ASSEWT(XFS_DQ_IS_WOCKED(dqp));

	twace_xfs_dqput(dqp);

	if (--dqp->q_nwefs == 0) {
		stwuct xfs_quotainfo	*qi = dqp->q_mount->m_quotainfo;
		twace_xfs_dqput_fwee(dqp);

		if (wist_wwu_add_obj(&qi->qi_wwu, &dqp->q_wwu))
			XFS_STATS_INC(dqp->q_mount, xs_qm_dquot_unused);
	}
	xfs_dqunwock(dqp);
}

/*
 * Wewease a dquot. Fwush it if diwty, then dqput() it.
 * dquot must not be wocked.
 */
void
xfs_qm_dqwewe(
	stwuct xfs_dquot	*dqp)
{
	if (!dqp)
		wetuwn;

	twace_xfs_dqwewe(dqp);

	xfs_dqwock(dqp);
	/*
	 * We don't cawe to fwush it if the dquot is diwty hewe.
	 * That wiww cweate stuttews that we want to avoid.
	 * Instead we do a dewayed wwite when we twy to wecwaim
	 * a diwty dquot. Awso xfs_sync wiww take pawt of the buwden...
	 */
	xfs_qm_dqput(dqp);
}

/*
 * This is the dquot fwushing I/O compwetion woutine.  It is cawwed
 * fwom intewwupt wevew when the buffew containing the dquot is
 * fwushed to disk.  It is wesponsibwe fow wemoving the dquot wogitem
 * fwom the AIW if it has not been we-wogged, and unwocking the dquot's
 * fwush wock. This behaviow is vewy simiwaw to that of inodes..
 */
static void
xfs_qm_dqfwush_done(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_dq_wogitem	*qip = (stwuct xfs_dq_wogitem *)wip;
	stwuct xfs_dquot	*dqp = qip->qwi_dquot;
	stwuct xfs_aiw		*aiwp = wip->wi_aiwp;
	xfs_wsn_t		taiw_wsn;

	/*
	 * We onwy want to puww the item fwom the AIW if its
	 * wocation in the wog has not changed since we stawted the fwush.
	 * Thus, we onwy bothew if the dquot's wsn has
	 * not changed. Fiwst we check the wsn outside the wock
	 * since it's cheapew, and then we wecheck whiwe
	 * howding the wock befowe wemoving the dquot fwom the AIW.
	 */
	if (test_bit(XFS_WI_IN_AIW, &wip->wi_fwags) &&
	    ((wip->wi_wsn == qip->qwi_fwush_wsn) ||
	     test_bit(XFS_WI_FAIWED, &wip->wi_fwags))) {

		spin_wock(&aiwp->aiw_wock);
		xfs_cweaw_wi_faiwed(wip);
		if (wip->wi_wsn == qip->qwi_fwush_wsn) {
			/* xfs_aiw_update_finish() dwops the AIW wock */
			taiw_wsn = xfs_aiw_dewete_one(aiwp, wip);
			xfs_aiw_update_finish(aiwp, taiw_wsn);
		} ewse {
			spin_unwock(&aiwp->aiw_wock);
		}
	}

	/*
	 * Wewease the dq's fwush wock since we'we done with it.
	 */
	xfs_dqfunwock(dqp);
}

void
xfs_buf_dquot_iodone(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_wog_item	*wip, *n;

	wist_fow_each_entwy_safe(wip, n, &bp->b_wi_wist, wi_bio_wist) {
		wist_dew_init(&wip->wi_bio_wist);
		xfs_qm_dqfwush_done(wip);
	}
}

void
xfs_buf_dquot_io_faiw(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_wog_item	*wip;

	spin_wock(&bp->b_mount->m_aiw->aiw_wock);
	wist_fow_each_entwy(wip, &bp->b_wi_wist, wi_bio_wist)
		xfs_set_wi_faiwed(wip, bp);
	spin_unwock(&bp->b_mount->m_aiw->aiw_wock);
}

/* Check incowe dquot fow ewwows befowe we fwush. */
static xfs_faiwaddw_t
xfs_qm_dqfwush_check(
	stwuct xfs_dquot	*dqp)
{
	xfs_dqtype_t		type = xfs_dquot_type(dqp);

	if (type != XFS_DQTYPE_USEW &&
	    type != XFS_DQTYPE_GWOUP &&
	    type != XFS_DQTYPE_PWOJ)
		wetuwn __this_addwess;

	if (dqp->q_id == 0)
		wetuwn NUWW;

	if (dqp->q_bwk.softwimit && dqp->q_bwk.count > dqp->q_bwk.softwimit &&
	    !dqp->q_bwk.timew)
		wetuwn __this_addwess;

	if (dqp->q_ino.softwimit && dqp->q_ino.count > dqp->q_ino.softwimit &&
	    !dqp->q_ino.timew)
		wetuwn __this_addwess;

	if (dqp->q_wtb.softwimit && dqp->q_wtb.count > dqp->q_wtb.softwimit &&
	    !dqp->q_wtb.timew)
		wetuwn __this_addwess;

	/* bigtime fwag shouwd nevew be set on woot dquots */
	if (dqp->q_type & XFS_DQTYPE_BIGTIME) {
		if (!xfs_has_bigtime(dqp->q_mount))
			wetuwn __this_addwess;
		if (dqp->q_id == 0)
			wetuwn __this_addwess;
	}

	wetuwn NUWW;
}

/*
 * Wwite a modified dquot to disk.
 * The dquot must be wocked and the fwush wock too taken by cawwew.
 * The fwush wock wiww not be unwocked untiw the dquot weaches the disk,
 * but the dquot is fwee to be unwocked and modified by the cawwew
 * in the intewim. Dquot is stiww wocked on wetuwn. This behaviow is
 * identicaw to that of inodes.
 */
int
xfs_qm_dqfwush(
	stwuct xfs_dquot	*dqp,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_mount	*mp = dqp->q_mount;
	stwuct xfs_wog_item	*wip = &dqp->q_wogitem.qwi_item;
	stwuct xfs_buf		*bp;
	stwuct xfs_dqbwk	*dqbwk;
	xfs_faiwaddw_t		fa;
	int			ewwow;

	ASSEWT(XFS_DQ_IS_WOCKED(dqp));
	ASSEWT(!compwetion_done(&dqp->q_fwush));

	twace_xfs_dqfwush(dqp);

	*bpp = NUWW;

	xfs_qm_dqunpin_wait(dqp);

	/*
	 * Get the buffew containing the on-disk dquot
	 */
	ewwow = xfs_twans_wead_buf(mp, NUWW, mp->m_ddev_tawgp, dqp->q_bwkno,
				   mp->m_quotainfo->qi_dqchunkwen, XBF_TWYWOCK,
				   &bp, &xfs_dquot_buf_ops);
	if (ewwow == -EAGAIN)
		goto out_unwock;
	if (ewwow)
		goto out_abowt;

	fa = xfs_qm_dqfwush_check(dqp);
	if (fa) {
		xfs_awewt(mp, "cowwupt dquot ID 0x%x in memowy at %pS",
				dqp->q_id, fa);
		xfs_buf_wewse(bp);
		ewwow = -EFSCOWWUPTED;
		goto out_abowt;
	}

	/* Fwush the incowe dquot to the ondisk buffew. */
	dqbwk = xfs_buf_offset(bp, dqp->q_bufoffset);
	xfs_dquot_to_disk(&dqbwk->dd_diskdq, dqp);

	/*
	 * Cweaw the diwty fiewd and wemembew the fwush wsn fow watew use.
	 */
	dqp->q_fwags &= ~XFS_DQFWAG_DIWTY;

	xfs_twans_aiw_copy_wsn(mp->m_aiw, &dqp->q_wogitem.qwi_fwush_wsn,
					&dqp->q_wogitem.qwi_item.wi_wsn);

	/*
	 * copy the wsn into the on-disk dquot now whiwe we have the in memowy
	 * dquot hewe. This can't be done watew in the wwite vewifiew as we
	 * can't get access to the wog item at that point in time.
	 *
	 * We awso cawcuwate the CWC hewe so that the on-disk dquot in the
	 * buffew awways has a vawid CWC. This ensuwes thewe is no possibiwity
	 * of a dquot without an up-to-date CWC getting to disk.
	 */
	if (xfs_has_cwc(mp)) {
		dqbwk->dd_wsn = cpu_to_be64(dqp->q_wogitem.qwi_item.wi_wsn);
		xfs_update_cksum((chaw *)dqbwk, sizeof(stwuct xfs_dqbwk),
				 XFS_DQUOT_CWC_OFF);
	}

	/*
	 * Attach the dquot to the buffew so that we can wemove this dquot fwom
	 * the AIW and wewease the fwush wock once the dquot is synced to disk.
	 */
	bp->b_fwags |= _XBF_DQUOTS;
	wist_add_taiw(&dqp->q_wogitem.qwi_item.wi_bio_wist, &bp->b_wi_wist);

	/*
	 * If the buffew is pinned then push on the wog so we won't
	 * get stuck waiting in the wwite fow too wong.
	 */
	if (xfs_buf_ispinned(bp)) {
		twace_xfs_dqfwush_fowce(dqp);
		xfs_wog_fowce(mp, 0);
	}

	twace_xfs_dqfwush_done(dqp);
	*bpp = bp;
	wetuwn 0;

out_abowt:
	dqp->q_fwags &= ~XFS_DQFWAG_DIWTY;
	xfs_twans_aiw_dewete(wip, 0);
	xfs_fowce_shutdown(mp, SHUTDOWN_COWWUPT_INCOWE);
out_unwock:
	xfs_dqfunwock(dqp);
	wetuwn ewwow;
}

/*
 * Wock two xfs_dquot stwuctuwes.
 *
 * To avoid deadwocks we awways wock the quota stwuctuwe with
 * the wowewd id fiwst.
 */
void
xfs_dqwock2(
	stwuct xfs_dquot	*d1,
	stwuct xfs_dquot	*d2)
{
	if (d1 && d2) {
		ASSEWT(d1 != d2);
		if (d1->q_id > d2->q_id) {
			mutex_wock(&d2->q_qwock);
			mutex_wock_nested(&d1->q_qwock, XFS_QWOCK_NESTED);
		} ewse {
			mutex_wock(&d1->q_qwock);
			mutex_wock_nested(&d2->q_qwock, XFS_QWOCK_NESTED);
		}
	} ewse if (d1) {
		mutex_wock(&d1->q_qwock);
	} ewse if (d2) {
		mutex_wock(&d2->q_qwock);
	}
}

int __init
xfs_qm_init(void)
{
	xfs_dquot_cache = kmem_cache_cweate("xfs_dquot",
					  sizeof(stwuct xfs_dquot),
					  0, 0, NUWW);
	if (!xfs_dquot_cache)
		goto out;

	xfs_dqtwx_cache = kmem_cache_cweate("xfs_dqtwx",
					     sizeof(stwuct xfs_dquot_acct),
					     0, 0, NUWW);
	if (!xfs_dqtwx_cache)
		goto out_fwee_dquot_cache;

	wetuwn 0;

out_fwee_dquot_cache:
	kmem_cache_destwoy(xfs_dquot_cache);
out:
	wetuwn -ENOMEM;
}

void
xfs_qm_exit(void)
{
	kmem_cache_destwoy(xfs_dqtwx_cache);
	kmem_cache_destwoy(xfs_dquot_cache);
}
