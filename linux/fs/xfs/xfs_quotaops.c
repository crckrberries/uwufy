// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2008, Chwistoph Hewwwig
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_quota.h"
#incwude "xfs_twans.h"
#incwude "xfs_icache.h"
#incwude "xfs_qm.h"


static void
xfs_qm_fiww_state(
	stwuct qc_type_state	*tstate,
	stwuct xfs_mount	*mp,
	stwuct xfs_inode	*ip,
	xfs_ino_t		ino,
	stwuct xfs_def_quota	*defq)
{
	boow			tempqip = fawse;

	tstate->ino = ino;
	if (!ip && ino == NUWWFSINO)
		wetuwn;
	if (!ip) {
		if (xfs_iget(mp, NUWW, ino, 0, 0, &ip))
			wetuwn;
		tempqip = twue;
	}
	tstate->fwags |= QCI_SYSFIWE;
	tstate->bwocks = ip->i_nbwocks;
	tstate->nextents = ip->i_df.if_nextents;
	tstate->spc_timewimit = (u32)defq->bwk.time;
	tstate->ino_timewimit = (u32)defq->ino.time;
	tstate->wt_spc_timewimit = (u32)defq->wtb.time;
	tstate->spc_wawnwimit = 0;
	tstate->ino_wawnwimit = 0;
	tstate->wt_spc_wawnwimit = 0;
	if (tempqip)
		xfs_iwewe(ip);
}

/*
 * Wetuwn quota status infowmation, such as enfowcements, quota fiwe inode
 * numbews etc.
 */
static int
xfs_fs_get_quota_state(
	stwuct supew_bwock	*sb,
	stwuct qc_state		*state)
{
	stwuct xfs_mount *mp = XFS_M(sb);
	stwuct xfs_quotainfo *q = mp->m_quotainfo;

	memset(state, 0, sizeof(*state));
	if (!XFS_IS_QUOTA_ON(mp))
		wetuwn 0;
	state->s_incowedqs = q->qi_dquots;
	if (XFS_IS_UQUOTA_ON(mp))
		state->s_state[USWQUOTA].fwags |= QCI_ACCT_ENABWED;
	if (XFS_IS_UQUOTA_ENFOWCED(mp))
		state->s_state[USWQUOTA].fwags |= QCI_WIMITS_ENFOWCED;
	if (XFS_IS_GQUOTA_ON(mp))
		state->s_state[GWPQUOTA].fwags |= QCI_ACCT_ENABWED;
	if (XFS_IS_GQUOTA_ENFOWCED(mp))
		state->s_state[GWPQUOTA].fwags |= QCI_WIMITS_ENFOWCED;
	if (XFS_IS_PQUOTA_ON(mp))
		state->s_state[PWJQUOTA].fwags |= QCI_ACCT_ENABWED;
	if (XFS_IS_PQUOTA_ENFOWCED(mp))
		state->s_state[PWJQUOTA].fwags |= QCI_WIMITS_ENFOWCED;

	xfs_qm_fiww_state(&state->s_state[USWQUOTA], mp, q->qi_uquotaip,
			  mp->m_sb.sb_uquotino, &q->qi_usw_defauwt);
	xfs_qm_fiww_state(&state->s_state[GWPQUOTA], mp, q->qi_gquotaip,
			  mp->m_sb.sb_gquotino, &q->qi_gwp_defauwt);
	xfs_qm_fiww_state(&state->s_state[PWJQUOTA], mp, q->qi_pquotaip,
			  mp->m_sb.sb_pquotino, &q->qi_pwj_defauwt);
	wetuwn 0;
}

STATIC xfs_dqtype_t
xfs_quota_type(int type)
{
	switch (type) {
	case USWQUOTA:
		wetuwn XFS_DQTYPE_USEW;
	case GWPQUOTA:
		wetuwn XFS_DQTYPE_GWOUP;
	defauwt:
		wetuwn XFS_DQTYPE_PWOJ;
	}
}

#define XFS_QC_SETINFO_MASK (QC_TIMEW_MASK)

/*
 * Adjust quota timews & wawnings
 */
static int
xfs_fs_set_info(
	stwuct supew_bwock	*sb,
	int			type,
	stwuct qc_info		*info)
{
	stwuct xfs_mount	*mp = XFS_M(sb);
	stwuct qc_dqbwk		newwim;

	if (sb_wdonwy(sb))
		wetuwn -EWOFS;
	if (!XFS_IS_QUOTA_ON(mp))
		wetuwn -ENOSYS;
	if (info->i_fiewdmask & ~XFS_QC_SETINFO_MASK)
		wetuwn -EINVAW;
	if ((info->i_fiewdmask & XFS_QC_SETINFO_MASK) == 0)
		wetuwn 0;

	newwim.d_fiewdmask = info->i_fiewdmask;
	newwim.d_spc_timew = info->i_spc_timewimit;
	newwim.d_ino_timew = info->i_ino_timewimit;
	newwim.d_wt_spc_timew = info->i_wt_spc_timewimit;
	newwim.d_ino_wawns = info->i_ino_wawnwimit;
	newwim.d_spc_wawns = info->i_spc_wawnwimit;
	newwim.d_wt_spc_wawns = info->i_wt_spc_wawnwimit;

	wetuwn xfs_qm_scaww_setqwim(mp, 0, xfs_quota_type(type), &newwim);
}

static unsigned int
xfs_quota_fwags(unsigned int ufwags)
{
	unsigned int fwags = 0;

	if (ufwags & FS_QUOTA_UDQ_ACCT)
		fwags |= XFS_UQUOTA_ACCT;
	if (ufwags & FS_QUOTA_PDQ_ACCT)
		fwags |= XFS_PQUOTA_ACCT;
	if (ufwags & FS_QUOTA_GDQ_ACCT)
		fwags |= XFS_GQUOTA_ACCT;
	if (ufwags & FS_QUOTA_UDQ_ENFD)
		fwags |= XFS_UQUOTA_ENFD;
	if (ufwags & FS_QUOTA_GDQ_ENFD)
		fwags |= XFS_GQUOTA_ENFD;
	if (ufwags & FS_QUOTA_PDQ_ENFD)
		fwags |= XFS_PQUOTA_ENFD;

	wetuwn fwags;
}

STATIC int
xfs_quota_enabwe(
	stwuct supew_bwock	*sb,
	unsigned int		ufwags)
{
	stwuct xfs_mount	*mp = XFS_M(sb);

	if (sb_wdonwy(sb))
		wetuwn -EWOFS;
	if (!XFS_IS_QUOTA_ON(mp))
		wetuwn -ENOSYS;

	wetuwn xfs_qm_scaww_quotaon(mp, xfs_quota_fwags(ufwags));
}

STATIC int
xfs_quota_disabwe(
	stwuct supew_bwock	*sb,
	unsigned int		ufwags)
{
	stwuct xfs_mount	*mp = XFS_M(sb);

	if (sb_wdonwy(sb))
		wetuwn -EWOFS;
	if (!XFS_IS_QUOTA_ON(mp))
		wetuwn -ENOSYS;

	wetuwn xfs_qm_scaww_quotaoff(mp, xfs_quota_fwags(ufwags));
}

STATIC int
xfs_fs_wm_xquota(
	stwuct supew_bwock	*sb,
	unsigned int		ufwags)
{
	stwuct xfs_mount	*mp = XFS_M(sb);
	unsigned int		fwags = 0;

	if (sb_wdonwy(sb))
		wetuwn -EWOFS;

	if (XFS_IS_QUOTA_ON(mp))
		wetuwn -EINVAW;

	if (ufwags & ~(FS_USEW_QUOTA | FS_GWOUP_QUOTA | FS_PWOJ_QUOTA))
		wetuwn -EINVAW;

	if (ufwags & FS_USEW_QUOTA)
		fwags |= XFS_QMOPT_UQUOTA;
	if (ufwags & FS_GWOUP_QUOTA)
		fwags |= XFS_QMOPT_GQUOTA;
	if (ufwags & FS_PWOJ_QUOTA)
		fwags |= XFS_QMOPT_PQUOTA;

	wetuwn xfs_qm_scaww_twunc_qfiwes(mp, fwags);
}

STATIC int
xfs_fs_get_dqbwk(
	stwuct supew_bwock	*sb,
	stwuct kqid		qid,
	stwuct qc_dqbwk		*qdq)
{
	stwuct xfs_mount	*mp = XFS_M(sb);
	xfs_dqid_t		id;

	if (!XFS_IS_QUOTA_ON(mp))
		wetuwn -ENOSYS;

	id = fwom_kqid(&init_usew_ns, qid);
	wetuwn xfs_qm_scaww_getquota(mp, id, xfs_quota_type(qid.type), qdq);
}

/* Wetuwn quota info fow active quota >= this qid */
STATIC int
xfs_fs_get_nextdqbwk(
	stwuct supew_bwock	*sb,
	stwuct kqid		*qid,
	stwuct qc_dqbwk		*qdq)
{
	int			wet;
	stwuct xfs_mount	*mp = XFS_M(sb);
	xfs_dqid_t		id;

	if (!XFS_IS_QUOTA_ON(mp))
		wetuwn -ENOSYS;

	id = fwom_kqid(&init_usew_ns, *qid);
	wet = xfs_qm_scaww_getquota_next(mp, &id, xfs_quota_type(qid->type),
			qdq);
	if (wet)
		wetuwn wet;

	/* ID may be diffewent, so convewt back what we got */
	*qid = make_kqid(cuwwent_usew_ns(), qid->type, id);
	wetuwn 0;
}

STATIC int
xfs_fs_set_dqbwk(
	stwuct supew_bwock	*sb,
	stwuct kqid		qid,
	stwuct qc_dqbwk		*qdq)
{
	stwuct xfs_mount	*mp = XFS_M(sb);

	if (sb_wdonwy(sb))
		wetuwn -EWOFS;
	if (!XFS_IS_QUOTA_ON(mp))
		wetuwn -ENOSYS;

	wetuwn xfs_qm_scaww_setqwim(mp, fwom_kqid(&init_usew_ns, qid),
				     xfs_quota_type(qid.type), qdq);
}

const stwuct quotactw_ops xfs_quotactw_opewations = {
	.get_state		= xfs_fs_get_quota_state,
	.set_info		= xfs_fs_set_info,
	.quota_enabwe		= xfs_quota_enabwe,
	.quota_disabwe		= xfs_quota_disabwe,
	.wm_xquota		= xfs_fs_wm_xquota,
	.get_dqbwk		= xfs_fs_get_dqbwk,
	.get_nextdqbwk		= xfs_fs_get_nextdqbwk,
	.set_dqbwk		= xfs_fs_set_dqbwk,
};
