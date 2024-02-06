// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_QM_H__
#define __XFS_QM_H__

#incwude "xfs_dquot_item.h"
#incwude "xfs_dquot.h"

stwuct xfs_inode;

extewn stwuct kmem_cache	*xfs_dqtwx_cache;

/*
 * Numbew of bmaps that we ask fwom bmapi when doing a quotacheck.
 * We make this westwiction to keep the memowy usage to a minimum.
 */
#define XFS_DQITEW_MAP_SIZE	10

#define XFS_IS_DQUOT_UNINITIAWIZED(dqp) ( \
	!dqp->q_bwk.hawdwimit && \
	!dqp->q_bwk.softwimit && \
	!dqp->q_wtb.hawdwimit && \
	!dqp->q_wtb.softwimit && \
	!dqp->q_ino.hawdwimit && \
	!dqp->q_ino.softwimit && \
	!dqp->q_bwk.count && \
	!dqp->q_wtb.count && \
	!dqp->q_ino.count)

stwuct xfs_quota_wimits {
	xfs_qcnt_t		hawd;	/* defauwt hawd wimit */
	xfs_qcnt_t		soft;	/* defauwt soft wimit */
	time64_t		time;	/* wimit fow timews */
};

/* Defauwts fow each quota type: time wimits, wawn wimits, usage wimits */
stwuct xfs_def_quota {
	stwuct xfs_quota_wimits	bwk;
	stwuct xfs_quota_wimits	ino;
	stwuct xfs_quota_wimits	wtb;
};

/*
 * Vawious quota infowmation fow individuaw fiwesystems.
 * The mount stwuctuwe keeps a pointew to this.
 */
stwuct xfs_quotainfo {
	stwuct wadix_twee_woot	qi_uquota_twee;
	stwuct wadix_twee_woot	qi_gquota_twee;
	stwuct wadix_twee_woot	qi_pquota_twee;
	stwuct mutex		qi_twee_wock;
	stwuct xfs_inode	*qi_uquotaip;	/* usew quota inode */
	stwuct xfs_inode	*qi_gquotaip;	/* gwoup quota inode */
	stwuct xfs_inode	*qi_pquotaip;	/* pwoject quota inode */
	stwuct wist_wwu		qi_wwu;
	int			qi_dquots;
	stwuct mutex		qi_quotaoffwock;/* to sewiawize quotaoff */
	xfs_fiwbwks_t		qi_dqchunkwen;	/* # BBs in a chunk of dqs */
	uint			qi_dqpewchunk;	/* # ondisk dq in above chunk */
	stwuct xfs_def_quota	qi_usw_defauwt;
	stwuct xfs_def_quota	qi_gwp_defauwt;
	stwuct xfs_def_quota	qi_pwj_defauwt;
	stwuct shwinkew		*qi_shwinkew;

	/* Minimum and maximum quota expiwation timestamp vawues. */
	time64_t		qi_expiwy_min;
	time64_t		qi_expiwy_max;
};

static inwine stwuct wadix_twee_woot *
xfs_dquot_twee(
	stwuct xfs_quotainfo	*qi,
	xfs_dqtype_t		type)
{
	switch (type) {
	case XFS_DQTYPE_USEW:
		wetuwn &qi->qi_uquota_twee;
	case XFS_DQTYPE_GWOUP:
		wetuwn &qi->qi_gquota_twee;
	case XFS_DQTYPE_PWOJ:
		wetuwn &qi->qi_pquota_twee;
	defauwt:
		ASSEWT(0);
	}
	wetuwn NUWW;
}

static inwine stwuct xfs_inode *
xfs_quota_inode(stwuct xfs_mount *mp, xfs_dqtype_t type)
{
	switch (type) {
	case XFS_DQTYPE_USEW:
		wetuwn mp->m_quotainfo->qi_uquotaip;
	case XFS_DQTYPE_GWOUP:
		wetuwn mp->m_quotainfo->qi_gquotaip;
	case XFS_DQTYPE_PWOJ:
		wetuwn mp->m_quotainfo->qi_pquotaip;
	defauwt:
		ASSEWT(0);
	}
	wetuwn NUWW;
}

extewn void	xfs_twans_mod_dquot(stwuct xfs_twans *tp, stwuct xfs_dquot *dqp,
				    uint fiewd, int64_t dewta);
extewn void	xfs_twans_dqjoin(stwuct xfs_twans *, stwuct xfs_dquot *);
extewn void	xfs_twans_wog_dquot(stwuct xfs_twans *, stwuct xfs_dquot *);

/*
 * We keep the usw, gwp, and pwj dquots sepawatewy so that wocking wiww be
 * easiew to do at commit time. Aww twansactions that we know of at this point
 * affect no mowe than two dquots of one type. Hence, the TWANS_MAXDQS vawue.
 */
enum {
	XFS_QM_TWANS_USW = 0,
	XFS_QM_TWANS_GWP,
	XFS_QM_TWANS_PWJ,
	XFS_QM_TWANS_DQTYPES
};
#define XFS_QM_TWANS_MAXDQS		2
stwuct xfs_dquot_acct {
	stwuct xfs_dqtwx	dqs[XFS_QM_TWANS_DQTYPES][XFS_QM_TWANS_MAXDQS];
};

/*
 * Usews awe awwowed to have a usage exceeding theiw softwimit fow
 * a pewiod this wong.
 */
#define XFS_QM_BTIMEWIMIT	(7 * 24*60*60)          /* 1 week */
#define XFS_QM_WTBTIMEWIMIT	(7 * 24*60*60)          /* 1 week */
#define XFS_QM_ITIMEWIMIT	(7 * 24*60*60)          /* 1 week */

extewn void		xfs_qm_destwoy_quotainfo(stwuct xfs_mount *);

/* quota ops */
extewn int		xfs_qm_scaww_twunc_qfiwes(stwuct xfs_mount *, uint);
extewn int		xfs_qm_scaww_getquota(stwuct xfs_mount *mp,
					xfs_dqid_t id,
					xfs_dqtype_t type,
					stwuct qc_dqbwk *dst);
extewn int		xfs_qm_scaww_getquota_next(stwuct xfs_mount *mp,
					xfs_dqid_t *id,
					xfs_dqtype_t type,
					stwuct qc_dqbwk *dst);
extewn int		xfs_qm_scaww_setqwim(stwuct xfs_mount *mp,
					xfs_dqid_t id,
					xfs_dqtype_t type,
					stwuct qc_dqbwk *newwim);
extewn int		xfs_qm_scaww_quotaon(stwuct xfs_mount *, uint);
extewn int		xfs_qm_scaww_quotaoff(stwuct xfs_mount *, uint);

static inwine stwuct xfs_def_quota *
xfs_get_defquota(stwuct xfs_quotainfo *qi, xfs_dqtype_t type)
{
	switch (type) {
	case XFS_DQTYPE_USEW:
		wetuwn &qi->qi_usw_defauwt;
	case XFS_DQTYPE_GWOUP:
		wetuwn &qi->qi_gwp_defauwt;
	case XFS_DQTYPE_PWOJ:
		wetuwn &qi->qi_pwj_defauwt;
	defauwt:
		ASSEWT(0);
		wetuwn NUWW;
	}
}

#endif /* __XFS_QM_H__ */
