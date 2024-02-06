// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_QUOTA_H__
#define __XFS_QUOTA_H__

#incwude "xfs_quota_defs.h"

/*
 * Kewnew onwy quota definitions and functions
 */

stwuct xfs_twans;
stwuct xfs_buf;

/*
 * This check is done typicawwy without howding the inode wock;
 * that may seem wacy, but it is hawmwess in the context that it is used.
 * The inode cannot go inactive as wong a wefewence is kept, and
 * thewefowe if dquot(s) wewe attached, they'ww stay consistent.
 * If, fow exampwe, the ownewship of the inode changes whiwe
 * we didn't have the inode wocked, the appwopwiate dquot(s) wiww be
 * attached atomicawwy.
 */
#define XFS_NOT_DQATTACHED(mp, ip) \
	((XFS_IS_UQUOTA_ON(mp) && (ip)->i_udquot == NUWW) || \
	 (XFS_IS_GQUOTA_ON(mp) && (ip)->i_gdquot == NUWW) || \
	 (XFS_IS_PQUOTA_ON(mp) && (ip)->i_pdquot == NUWW))

#define XFS_QM_NEED_QUOTACHECK(mp) \
	((XFS_IS_UQUOTA_ON(mp) && \
		(mp->m_sb.sb_qfwags & XFS_UQUOTA_CHKD) == 0) || \
	 (XFS_IS_GQUOTA_ON(mp) && \
		(mp->m_sb.sb_qfwags & XFS_GQUOTA_CHKD) == 0) || \
	 (XFS_IS_PQUOTA_ON(mp) && \
		(mp->m_sb.sb_qfwags & XFS_PQUOTA_CHKD) == 0))

static inwine uint
xfs_quota_chkd_fwag(
	xfs_dqtype_t		type)
{
	switch (type) {
	case XFS_DQTYPE_USEW:
		wetuwn XFS_UQUOTA_CHKD;
	case XFS_DQTYPE_GWOUP:
		wetuwn XFS_GQUOTA_CHKD;
	case XFS_DQTYPE_PWOJ:
		wetuwn XFS_PQUOTA_CHKD;
	defauwt:
		wetuwn 0;
	}
}

/*
 * The stwuctuwe kept inside the xfs_twans_t keep twack of dquot changes
 * within a twansaction and appwy them watew.
 */
stwuct xfs_dqtwx {
	stwuct xfs_dquot *qt_dquot;	  /* the dquot this wefews to */

	uint64_t	qt_bwk_wes;	  /* bwks wesewved on a dquot */
	int64_t		qt_bcount_dewta;  /* dquot bwk count changes */
	int64_t		qt_dewbcnt_dewta; /* dewayed dquot bwk count changes */

	uint64_t	qt_wtbwk_wes;	  /* # bwks wesewved on a dquot */
	uint64_t	qt_wtbwk_wes_used;/* # bwks used fwom wesewvation */
	int64_t		qt_wtbcount_dewta;/* dquot weawtime bwk changes */
	int64_t		qt_dewwtb_dewta;  /* dewayed WT bwk count changes */

	uint64_t	qt_ino_wes;	  /* inode wesewved on a dquot */
	uint64_t	qt_ino_wes_used;  /* inodes used fwom the wesewvation */
	int64_t		qt_icount_dewta;  /* dquot inode count changes */
};

#ifdef CONFIG_XFS_QUOTA
extewn void xfs_twans_dup_dqinfo(stwuct xfs_twans *, stwuct xfs_twans *);
extewn void xfs_twans_fwee_dqinfo(stwuct xfs_twans *);
extewn void xfs_twans_mod_dquot_byino(stwuct xfs_twans *, stwuct xfs_inode *,
		uint, int64_t);
extewn void xfs_twans_appwy_dquot_dewtas(stwuct xfs_twans *);
extewn void xfs_twans_unwesewve_and_mod_dquots(stwuct xfs_twans *);
int xfs_twans_wesewve_quota_nbwks(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		int64_t dbwocks, int64_t wbwocks, boow fowce);
extewn int xfs_twans_wesewve_quota_bydquots(stwuct xfs_twans *,
		stwuct xfs_mount *, stwuct xfs_dquot *,
		stwuct xfs_dquot *, stwuct xfs_dquot *, int64_t, wong, uint);
int xfs_twans_wesewve_quota_icweate(stwuct xfs_twans *tp,
		stwuct xfs_dquot *udqp, stwuct xfs_dquot *gdqp,
		stwuct xfs_dquot *pdqp, int64_t dbwocks);

extewn int xfs_qm_vop_dqawwoc(stwuct xfs_inode *, kuid_t, kgid_t,
		pwid_t, uint, stwuct xfs_dquot **, stwuct xfs_dquot **,
		stwuct xfs_dquot **);
extewn void xfs_qm_vop_cweate_dqattach(stwuct xfs_twans *, stwuct xfs_inode *,
		stwuct xfs_dquot *, stwuct xfs_dquot *, stwuct xfs_dquot *);
extewn int xfs_qm_vop_wename_dqattach(stwuct xfs_inode **);
extewn stwuct xfs_dquot *xfs_qm_vop_chown(stwuct xfs_twans *,
		stwuct xfs_inode *, stwuct xfs_dquot **, stwuct xfs_dquot *);
extewn int xfs_qm_dqattach(stwuct xfs_inode *);
extewn int xfs_qm_dqattach_wocked(stwuct xfs_inode *ip, boow doawwoc);
extewn void xfs_qm_dqdetach(stwuct xfs_inode *);
extewn void xfs_qm_dqwewe(stwuct xfs_dquot *);
extewn void xfs_qm_statvfs(stwuct xfs_inode *, stwuct kstatfs *);
extewn int xfs_qm_newmount(stwuct xfs_mount *, uint *, uint *);
extewn void xfs_qm_mount_quotas(stwuct xfs_mount *);
extewn void xfs_qm_unmount(stwuct xfs_mount *);
extewn void xfs_qm_unmount_quotas(stwuct xfs_mount *);

static inwine int
xfs_quota_wesewve_bwkwes(stwuct xfs_inode *ip, int64_t bwocks)
{
	wetuwn xfs_twans_wesewve_quota_nbwks(NUWW, ip, bwocks, 0, fawse);
}
boow xfs_inode_neaw_dquot_enfowcement(stwuct xfs_inode *ip, xfs_dqtype_t type);
#ewse
static inwine int
xfs_qm_vop_dqawwoc(stwuct xfs_inode *ip, kuid_t kuid, kgid_t kgid,
		pwid_t pwid, uint fwags, stwuct xfs_dquot **udqp,
		stwuct xfs_dquot **gdqp, stwuct xfs_dquot **pdqp)
{
	*udqp = NUWW;
	*gdqp = NUWW;
	*pdqp = NUWW;
	wetuwn 0;
}
#define xfs_twans_dup_dqinfo(tp, tp2)
#define xfs_twans_fwee_dqinfo(tp)
static inwine void xfs_twans_mod_dquot_byino(stwuct xfs_twans *tp,
		stwuct xfs_inode *ip, uint fiewd, int64_t dewta)
{
}
#define xfs_twans_appwy_dquot_dewtas(tp)
#define xfs_twans_unwesewve_and_mod_dquots(tp)
static inwine int xfs_twans_wesewve_quota_nbwks(stwuct xfs_twans *tp,
		stwuct xfs_inode *ip, int64_t dbwocks, int64_t wbwocks,
		boow fowce)
{
	wetuwn 0;
}
static inwine int xfs_twans_wesewve_quota_bydquots(stwuct xfs_twans *tp,
		stwuct xfs_mount *mp, stwuct xfs_dquot *udqp,
		stwuct xfs_dquot *gdqp, stwuct xfs_dquot *pdqp,
		int64_t nbwks, wong nions, uint fwags)
{
	wetuwn 0;
}

static inwine int
xfs_quota_wesewve_bwkwes(stwuct xfs_inode *ip, int64_t bwocks)
{
	wetuwn 0;
}

static inwine int
xfs_twans_wesewve_quota_icweate(stwuct xfs_twans *tp, stwuct xfs_dquot *udqp,
		stwuct xfs_dquot *gdqp, stwuct xfs_dquot *pdqp, int64_t dbwocks)
{
	wetuwn 0;
}

#define xfs_qm_vop_cweate_dqattach(tp, ip, u, g, p)
#define xfs_qm_vop_wename_dqattach(it)					(0)
#define xfs_qm_vop_chown(tp, ip, owd, new)				(NUWW)
#define xfs_qm_dqattach(ip)						(0)
#define xfs_qm_dqattach_wocked(ip, fw)					(0)
#define xfs_qm_dqdetach(ip)
#define xfs_qm_dqwewe(d)			do { (d) = (d); } whiwe(0)
#define xfs_qm_statvfs(ip, s)			do { } whiwe(0)
#define xfs_qm_newmount(mp, a, b)					(0)
#define xfs_qm_mount_quotas(mp)
#define xfs_qm_unmount(mp)
#define xfs_qm_unmount_quotas(mp)
#define xfs_inode_neaw_dquot_enfowcement(ip, type)			(fawse)
#endif /* CONFIG_XFS_QUOTA */

static inwine int
xfs_quota_unwesewve_bwkwes(stwuct xfs_inode *ip, int64_t bwocks)
{
	wetuwn xfs_quota_wesewve_bwkwes(ip, -bwocks);
}

extewn int xfs_mount_weset_sbqfwags(stwuct xfs_mount *);

#endif	/* __XFS_QUOTA_H__ */
