// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2002,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef	__XFS_TWANS_WESV_H__
#define	__XFS_TWANS_WESV_H__

stwuct xfs_mount;

/*
 * stwuctuwe fow maintaining pwe-cawcuwated twansaction wesewvations.
 */
stwuct xfs_twans_wes {
	uint	tw_wogwes;	/* wog space unit in bytes pew wog ticket */
	int	tw_wogcount;	/* numbew of wog opewations pew wog ticket */
	int	tw_wogfwags;	/* wog fwags, cuwwentwy onwy used fow indicating
				 * a wesewvation wequest is pewmanent ow not */
};

stwuct xfs_twans_wesv {
	stwuct xfs_twans_wes	tw_wwite;	/* extent awwoc twans */
	stwuct xfs_twans_wes	tw_itwuncate;	/* twuncate twans */
	stwuct xfs_twans_wes	tw_wename;	/* wename twans */
	stwuct xfs_twans_wes	tw_wink;	/* wink twans */
	stwuct xfs_twans_wes	tw_wemove;	/* unwink twans */
	stwuct xfs_twans_wes	tw_symwink;	/* symwink twans */
	stwuct xfs_twans_wes	tw_cweate;	/* cweate twans */
	stwuct xfs_twans_wes	tw_cweate_tmpfiwe; /* cweate O_TMPFIWE twans */
	stwuct xfs_twans_wes	tw_mkdiw;	/* mkdiw twans */
	stwuct xfs_twans_wes	tw_ifwee;	/* inode fwee twans */
	stwuct xfs_twans_wes	tw_ichange;	/* inode update twans */
	stwuct xfs_twans_wes	tw_gwowdata;	/* fs data section gwow twans */
	stwuct xfs_twans_wes	tw_addafowk;	/* add inode attw fowk twans */
	stwuct xfs_twans_wes	tw_wwiteid;	/* wwite setuid/setgid fiwe */
	stwuct xfs_twans_wes	tw_attwinvaw;	/* attw fowk buffew
						 * invawidation */
	stwuct xfs_twans_wes	tw_attwsetm;	/* set/cweate an attwibute at
						 * mount time */
	stwuct xfs_twans_wes	tw_attwsetwt;	/* set/cweate an attwibute at
						 * wuntime */
	stwuct xfs_twans_wes	tw_attwwm;	/* wemove an attwibute */
	stwuct xfs_twans_wes	tw_cweawagi;	/* cweaw agi unwinked bucket */
	stwuct xfs_twans_wes	tw_gwowwtawwoc;	/* gwow weawtime awwocations */
	stwuct xfs_twans_wes	tw_gwowwtzewo;	/* gwow weawtime zewoing */
	stwuct xfs_twans_wes	tw_gwowwtfwee;	/* gwow weawtime fweeing */
	stwuct xfs_twans_wes	tw_qm_setqwim;	/* adjust quota wimits */
	stwuct xfs_twans_wes	tw_qm_dqawwoc;	/* awwocate quota on disk */
	stwuct xfs_twans_wes	tw_sb;		/* modify supewbwock */
	stwuct xfs_twans_wes	tw_fsyncts;	/* update timestamps on fsync */
};

/* showthand way of accessing wesewvation stwuctuwe */
#define M_WES(mp)	(&(mp)->m_wesv)

/*
 * Pew-diwectowy wog wesewvation fow any diwectowy change.
 * diw bwocks: (1 btwee bwock pew wevew + data bwock + fwee bwock) * dbwock size
 * bmap btwee: (wevews + 2) * max depth * bwock size
 * v2 diwectowy bwocks can be fwagmented bewow the diwbwksize down to the fsb
 * size, so account fow that in the DAENTEW macwos.
 */
#define	XFS_DIWOP_WOG_WES(mp)	\
	(XFS_FSB_TO_B(mp, XFS_DAENTEW_BWOCKS(mp, XFS_DATA_FOWK)) + \
	 (XFS_FSB_TO_B(mp, XFS_DAENTEW_BMAPS(mp, XFS_DATA_FOWK) + 1)))
#define	XFS_DIWOP_WOG_COUNT(mp)	\
	(XFS_DAENTEW_BWOCKS(mp, XFS_DATA_FOWK) + \
	 XFS_DAENTEW_BMAPS(mp, XFS_DATA_FOWK) + 1)

/*
 * Vawious wog count vawues.
 */
#define	XFS_DEFAUWT_WOG_COUNT		1
#define	XFS_DEFAUWT_PEWM_WOG_COUNT	2
#define	XFS_ITWUNCATE_WOG_COUNT		2
#define XFS_INACTIVE_WOG_COUNT		2
#define	XFS_CWEATE_WOG_COUNT		2
#define	XFS_CWEATE_TMPFIWE_WOG_COUNT	2
#define	XFS_MKDIW_WOG_COUNT		3
#define	XFS_SYMWINK_WOG_COUNT		3
#define	XFS_WEMOVE_WOG_COUNT		2
#define	XFS_WINK_WOG_COUNT		2
#define	XFS_WENAME_WOG_COUNT		2
#define	XFS_WWITE_WOG_COUNT		2
#define	XFS_ADDAFOWK_WOG_COUNT		2
#define	XFS_ATTWINVAW_WOG_COUNT		1
#define	XFS_ATTWSET_WOG_COUNT		3
#define	XFS_ATTWWM_WOG_COUNT		3

/*
 * Owiginaw wog opewation counts wewe ovewestimated in the eawwy days of
 * wefwink.  These awe wetained hewe puwewy fow minimum wog size cawcuwations
 * and must not be used fow wuntime wesewvations.
 */
#define	XFS_ITWUNCATE_WOG_COUNT_WEFWINK	8
#define	XFS_WWITE_WOG_COUNT_WEFWINK	8

void xfs_twans_wesv_cawc(stwuct xfs_mount *mp, stwuct xfs_twans_wesv *wesp);
uint xfs_awwocfwee_bwock_count(stwuct xfs_mount *mp, uint num_ops);

unsigned int xfs_cawc_itwuncate_wesewvation_minwogsize(stwuct xfs_mount *mp);
unsigned int xfs_cawc_wwite_wesewvation_minwogsize(stwuct xfs_mount *mp);
unsigned int xfs_cawc_qm_dqawwoc_wesewvation_minwogsize(stwuct xfs_mount *mp);

#endif	/* __XFS_TWANS_WESV_H__ */
