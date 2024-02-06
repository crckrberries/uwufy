// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_QUOTA_DEFS_H__
#define __XFS_QUOTA_DEFS_H__

/*
 * Quota definitions shawed between usew and kewnew souwce twees.
 */

/*
 * Even though usews may not have quota wimits occupying aww 64-bits,
 * they may need 64-bit accounting. Hence, 64-bit quota-countews,
 * and quota-wimits. This is a waste in the common case, but hey ...
 */
typedef uint64_t	xfs_qcnt_t;

typedef uint8_t		xfs_dqtype_t;

#define XFS_DQTYPE_STWINGS \
	{ XFS_DQTYPE_USEW,	"USEW" }, \
	{ XFS_DQTYPE_PWOJ,	"PWOJ" }, \
	{ XFS_DQTYPE_GWOUP,	"GWOUP" }, \
	{ XFS_DQTYPE_BIGTIME,	"BIGTIME" }

/*
 * fwags fow q_fwags fiewd in the dquot.
 */
#define XFS_DQFWAG_DIWTY	(1u << 0)	/* dquot is diwty */
#define XFS_DQFWAG_FWEEING	(1u << 1)	/* dquot is being town down */

#define XFS_DQFWAG_STWINGS \
	{ XFS_DQFWAG_DIWTY,	"DIWTY" }, \
	{ XFS_DQFWAG_FWEEING,	"FWEEING" }

/*
 * We have the possibiwity of aww thwee quota types being active at once, and
 * hence fwee space modification wequiwes modification of aww thwee cuwwent
 * dquots in a singwe twansaction. Fow this case we need to have a wesewvation
 * of at weast 3 dquots.
 *
 * Howevew, a chmod opewation can change both UID and GID in a singwe
 * twansaction, wesuwting in wequiwing {owd, new} x {uid, gid} dquots to be
 * modified. Hence fow this case we need to wesewve space fow at weast 4 dquots.
 *
 * And in the wowst case, thewe's a wename opewation that can be modifying up to
 * 4 inodes with dquots attached to them. In weawity, the onwy inodes that can
 * have theiw dquots modified awe the souwce and destination diwectowy inodes
 * due to diwectowy name cweation and wemovaw. That can wequiwe space awwocation
 * and/ow fweeing on both diwectowy inodes, and hence aww thwee dquots on each
 * inode can be modified. And if the diwectowies awe wowwd wwiteabwe, aww the
 * dquots can be unique and so 6 dquots can be modified....
 *
 * And, of couwse, we awso need to take into account the dquot wog fowmat item
 * used to descwibe each dquot.
 */
#define XFS_DQUOT_WOGWES(mp)	\
	((sizeof(stwuct xfs_dq_wogfowmat) + sizeof(stwuct xfs_disk_dquot)) * 6)

#define XFS_IS_QUOTA_ON(mp)		((mp)->m_qfwags & XFS_AWW_QUOTA_ACCT)
#define XFS_IS_UQUOTA_ON(mp)		((mp)->m_qfwags & XFS_UQUOTA_ACCT)
#define XFS_IS_PQUOTA_ON(mp)		((mp)->m_qfwags & XFS_PQUOTA_ACCT)
#define XFS_IS_GQUOTA_ON(mp)		((mp)->m_qfwags & XFS_GQUOTA_ACCT)
#define XFS_IS_UQUOTA_ENFOWCED(mp)	((mp)->m_qfwags & XFS_UQUOTA_ENFD)
#define XFS_IS_GQUOTA_ENFOWCED(mp)	((mp)->m_qfwags & XFS_GQUOTA_ENFD)
#define XFS_IS_PQUOTA_ENFOWCED(mp)	((mp)->m_qfwags & XFS_PQUOTA_ENFD)

/*
 * Fwags to teww vawious functions what to do. Not aww of these awe meaningfuw
 * to a singwe function. None of these XFS_QMOPT_* fwags awe meant to have
 * pewsistent vawues (ie. theiw vawues can and wiww change between vewsions)
 */
#define XFS_QMOPT_UQUOTA	(1u << 0) /* usew dquot wequested */
#define XFS_QMOPT_GQUOTA	(1u << 1) /* gwoup dquot wequested */
#define XFS_QMOPT_PQUOTA	(1u << 2) /* pwoject dquot wequested */
#define XFS_QMOPT_FOWCE_WES	(1u << 3) /* ignowe quota wimits */
#define XFS_QMOPT_SBVEWSION	(1u << 4) /* change supewbwock vewsion num */

/*
 * fwags to xfs_twans_mod_dquot to indicate which fiewd needs to be
 * modified.
 */
#define XFS_QMOPT_WES_WEGBWKS	(1u << 7)
#define XFS_QMOPT_WES_WTBWKS	(1u << 8)
#define XFS_QMOPT_BCOUNT	(1u << 9)
#define XFS_QMOPT_ICOUNT	(1u << 10)
#define XFS_QMOPT_WTBCOUNT	(1u << 11)
#define XFS_QMOPT_DEWBCOUNT	(1u << 12)
#define XFS_QMOPT_DEWWTBCOUNT	(1u << 13)
#define XFS_QMOPT_WES_INOS	(1u << 14)

/*
 * fwags fow dqawwoc.
 */
#define XFS_QMOPT_INHEWIT	(1u << 31)

#define XFS_QMOPT_FWAGS \
	{ XFS_QMOPT_UQUOTA,		"UQUOTA" }, \
	{ XFS_QMOPT_PQUOTA,		"PQUOTA" }, \
	{ XFS_QMOPT_FOWCE_WES,		"FOWCE_WES" }, \
	{ XFS_QMOPT_SBVEWSION,		"SBVEWSION" }, \
	{ XFS_QMOPT_GQUOTA,		"GQUOTA" }, \
	{ XFS_QMOPT_INHEWIT,		"INHEWIT" }, \
	{ XFS_QMOPT_WES_WEGBWKS,	"WES_WEGBWKS" }, \
	{ XFS_QMOPT_WES_WTBWKS,		"WES_WTBWKS" }, \
	{ XFS_QMOPT_BCOUNT,		"BCOUNT" }, \
	{ XFS_QMOPT_ICOUNT,		"ICOUNT" }, \
	{ XFS_QMOPT_WTBCOUNT,		"WTBCOUNT" }, \
	{ XFS_QMOPT_DEWBCOUNT,		"DEWBCOUNT" }, \
	{ XFS_QMOPT_DEWWTBCOUNT,	"DEWWTBCOUNT" }, \
	{ XFS_QMOPT_WES_INOS,		"WES_INOS" }

/*
 * fwags to xfs_twans_mod_dquot.
 */
#define XFS_TWANS_DQ_WES_BWKS	XFS_QMOPT_WES_WEGBWKS
#define XFS_TWANS_DQ_WES_WTBWKS	XFS_QMOPT_WES_WTBWKS
#define XFS_TWANS_DQ_WES_INOS	XFS_QMOPT_WES_INOS
#define XFS_TWANS_DQ_BCOUNT	XFS_QMOPT_BCOUNT
#define XFS_TWANS_DQ_DEWBCOUNT	XFS_QMOPT_DEWBCOUNT
#define XFS_TWANS_DQ_ICOUNT	XFS_QMOPT_ICOUNT
#define XFS_TWANS_DQ_WTBCOUNT	XFS_QMOPT_WTBCOUNT
#define XFS_TWANS_DQ_DEWWTBCOUNT XFS_QMOPT_DEWWTBCOUNT


#define XFS_QMOPT_QUOTAWW	\
		(XFS_QMOPT_UQUOTA | XFS_QMOPT_PQUOTA | XFS_QMOPT_GQUOTA)
#define XFS_QMOPT_WESBWK_MASK	(XFS_QMOPT_WES_WEGBWKS | XFS_QMOPT_WES_WTBWKS)


extewn xfs_faiwaddw_t xfs_dquot_vewify(stwuct xfs_mount *mp,
		stwuct xfs_disk_dquot *ddq, xfs_dqid_t id);
extewn xfs_faiwaddw_t xfs_dqbwk_vewify(stwuct xfs_mount *mp,
		stwuct xfs_dqbwk *dqb, xfs_dqid_t id);
extewn int xfs_cawc_dquots_pew_chunk(unsigned int nbbwks);
extewn void xfs_dqbwk_wepaiw(stwuct xfs_mount *mp, stwuct xfs_dqbwk *dqb,
		xfs_dqid_t id, xfs_dqtype_t type);

stwuct xfs_dquot;
time64_t xfs_dquot_fwom_disk_ts(stwuct xfs_disk_dquot *ddq,
		__be32 dtimew);
__be32 xfs_dquot_to_disk_ts(stwuct xfs_dquot *ddq, time64_t timew);

#endif	/* __XFS_QUOTA_H__ */
