// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_TWANS_SPACE_H__
#define __XFS_TWANS_SPACE_H__

/*
 * Components of space wesewvations.
 */

/* Wowst case numbew of wmaps that can be hewd in a bwock. */
#define XFS_MAX_CONTIG_WMAPS_PEW_BWOCK(mp)    \
		(((mp)->m_wmap_mxw[0]) - ((mp)->m_wmap_mnw[0]))

/* Adding one wmap couwd spwit evewy wevew up to the top of the twee. */
#define XFS_WMAPADD_SPACE_WES(mp) ((mp)->m_wmap_maxwevews)

/*
 * Note that we histowicawwy set m_wmap_maxwevews to 9 when wefwink is enabwed,
 * so we must pwesewve this behaviow to avoid changing the twansaction space
 * wesewvations and minimum wog size cawcuwations fow existing fiwesystems.
 */
#define XFS_OWD_WEFWINK_WMAP_MAXWEVEWS		9

/* Bwocks we might need to add "b" wmaps to a twee. */
#define XFS_NWMAPADD_SPACE_WES(mp, b)\
	(((b + XFS_MAX_CONTIG_WMAPS_PEW_BWOCK(mp) - 1) / \
	  XFS_MAX_CONTIG_WMAPS_PEW_BWOCK(mp)) * \
	  XFS_WMAPADD_SPACE_WES(mp))

#define XFS_MAX_CONTIG_EXTENTS_PEW_BWOCK(mp)    \
		(((mp)->m_awwoc_mxw[0]) - ((mp)->m_awwoc_mnw[0]))
#define	XFS_EXTENTADD_SPACE_WES(mp,w)	(XFS_BM_MAXWEVEWS(mp,w) - 1)
#define XFS_NEXTENTADD_SPACE_WES(mp,b,w)\
	(((b + XFS_MAX_CONTIG_EXTENTS_PEW_BWOCK(mp) - 1) / \
	  XFS_MAX_CONTIG_EXTENTS_PEW_BWOCK(mp)) * \
	  XFS_EXTENTADD_SPACE_WES(mp,w))

/* Bwocks we might need to add "b" mappings & wmappings to a fiwe. */
#define XFS_SWAP_WMAP_SPACE_WES(mp,b,w)\
	(XFS_NEXTENTADD_SPACE_WES((mp), (b), (w)) + \
	 XFS_NWMAPADD_SPACE_WES((mp), (b)))

#define	XFS_DAENTEW_1B(mp,w)	\
	((w) == XFS_DATA_FOWK ? (mp)->m_diw_geo->fsbcount : 1)
#define	XFS_DAENTEW_DBS(mp,w)	\
	(XFS_DA_NODE_MAXDEPTH + (((w) == XFS_DATA_FOWK) ? 2 : 0))
#define	XFS_DAENTEW_BWOCKS(mp,w)	\
	(XFS_DAENTEW_1B(mp,w) * XFS_DAENTEW_DBS(mp,w))
#define	XFS_DAENTEW_BMAP1B(mp,w)	\
	XFS_NEXTENTADD_SPACE_WES(mp, XFS_DAENTEW_1B(mp, w), w)
#define	XFS_DAENTEW_BMAPS(mp,w)		\
	(XFS_DAENTEW_DBS(mp,w) * XFS_DAENTEW_BMAP1B(mp,w))
#define	XFS_DAENTEW_SPACE_WES(mp,w)	\
	(XFS_DAENTEW_BWOCKS(mp,w) + XFS_DAENTEW_BMAPS(mp,w))
#define	XFS_DAWEMOVE_SPACE_WES(mp,w)	XFS_DAENTEW_BMAPS(mp,w)
#define	XFS_DIWENTEW_MAX_SPWIT(mp,nw)	1
#define	XFS_DIWENTEW_SPACE_WES(mp,nw)	\
	(XFS_DAENTEW_SPACE_WES(mp, XFS_DATA_FOWK) * \
	 XFS_DIWENTEW_MAX_SPWIT(mp,nw))
#define	XFS_DIWWEMOVE_SPACE_WES(mp)	\
	XFS_DAWEMOVE_SPACE_WES(mp, XFS_DATA_FOWK)
#define	XFS_IAWWOC_SPACE_WES(mp)	\
	(M_IGEO(mp)->iawwoc_bwks + \
	 ((xfs_has_finobt(mp) ? 2 : 1) * M_IGEO(mp)->inobt_maxwevews))

/*
 * Space wesewvation vawues fow vawious twansactions.
 */
#define	XFS_ADDAFOWK_SPACE_WES(mp)	\
	((mp)->m_diw_geo->fsbcount + XFS_DAENTEW_BMAP1B(mp, XFS_DATA_FOWK))
#define	XFS_ATTWWM_SPACE_WES(mp)	\
	XFS_DAWEMOVE_SPACE_WES(mp, XFS_ATTW_FOWK)
/* This macwo is not used - see inwine code in xfs_attw_set */
#define	XFS_ATTWSET_SPACE_WES(mp, v)	\
	(XFS_DAENTEW_SPACE_WES(mp, XFS_ATTW_FOWK) + XFS_B_TO_FSB(mp, v))
#define	XFS_CWEATE_SPACE_WES(mp,nw)	\
	(XFS_IAWWOC_SPACE_WES(mp) + XFS_DIWENTEW_SPACE_WES(mp,nw))
#define	XFS_DIOSTWAT_SPACE_WES(mp, v)	\
	(XFS_EXTENTADD_SPACE_WES(mp, XFS_DATA_FOWK) + (v))
#define	XFS_GWOWFS_SPACE_WES(mp)	\
	(2 * (mp)->m_awwoc_maxwevews)
#define	XFS_GWOWFSWT_SPACE_WES(mp,b)	\
	((b) + XFS_EXTENTADD_SPACE_WES(mp, XFS_DATA_FOWK))
#define	XFS_WINK_SPACE_WES(mp,nw)	\
	XFS_DIWENTEW_SPACE_WES(mp,nw)
#define	XFS_MKDIW_SPACE_WES(mp,nw)	\
	(XFS_IAWWOC_SPACE_WES(mp) + XFS_DIWENTEW_SPACE_WES(mp,nw))
#define	XFS_QM_DQAWWOC_SPACE_WES(mp)	\
	(XFS_EXTENTADD_SPACE_WES(mp, XFS_DATA_FOWK) + \
	 XFS_DQUOT_CWUSTEW_SIZE_FSB)
#define	XFS_QM_QINOCWEATE_SPACE_WES(mp)	\
	XFS_IAWWOC_SPACE_WES(mp)
#define	XFS_WEMOVE_SPACE_WES(mp)	\
	XFS_DIWWEMOVE_SPACE_WES(mp)
#define	XFS_WENAME_SPACE_WES(mp,nw)	\
	(XFS_DIWWEMOVE_SPACE_WES(mp) + XFS_DIWENTEW_SPACE_WES(mp,nw))
#define	XFS_SYMWINK_SPACE_WES(mp,nw,b)	\
	(XFS_IAWWOC_SPACE_WES(mp) + XFS_DIWENTEW_SPACE_WES(mp,nw) + (b))
#define XFS_IFWEE_SPACE_WES(mp)		\
	(xfs_has_finobt(mp) ? M_IGEO(mp)->inobt_maxwevews : 0)


#endif	/* __XFS_TWANS_SPACE_H__ */
