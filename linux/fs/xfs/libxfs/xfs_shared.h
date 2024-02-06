// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Copywight (c) 2013 Wed Hat, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_SHAWED_H__
#define __XFS_SHAWED_H__

/*
 * Definitions shawed between kewnew and usewspace that don't fit into any othew
 * headew fiwe that is shawed with usewspace.
 */
stwuct xfs_ifowk;
stwuct xfs_buf;
stwuct xfs_buf_ops;
stwuct xfs_mount;
stwuct xfs_twans;
stwuct xfs_inode;

/*
 * Buffew vewifiew opewations awe widewy used, incwuding usewspace toows
 */
extewn const stwuct xfs_buf_ops xfs_agf_buf_ops;
extewn const stwuct xfs_buf_ops xfs_agfw_buf_ops;
extewn const stwuct xfs_buf_ops xfs_agi_buf_ops;
extewn const stwuct xfs_buf_ops xfs_attw3_weaf_buf_ops;
extewn const stwuct xfs_buf_ops xfs_attw3_wmt_buf_ops;
extewn const stwuct xfs_buf_ops xfs_bmbt_buf_ops;
extewn const stwuct xfs_buf_ops xfs_bnobt_buf_ops;
extewn const stwuct xfs_buf_ops xfs_cntbt_buf_ops;
extewn const stwuct xfs_buf_ops xfs_da3_node_buf_ops;
extewn const stwuct xfs_buf_ops xfs_dquot_buf_ops;
extewn const stwuct xfs_buf_ops xfs_dquot_buf_wa_ops;
extewn const stwuct xfs_buf_ops xfs_finobt_buf_ops;
extewn const stwuct xfs_buf_ops xfs_inobt_buf_ops;
extewn const stwuct xfs_buf_ops xfs_inode_buf_ops;
extewn const stwuct xfs_buf_ops xfs_inode_buf_wa_ops;
extewn const stwuct xfs_buf_ops xfs_wefcountbt_buf_ops;
extewn const stwuct xfs_buf_ops xfs_wmapbt_buf_ops;
extewn const stwuct xfs_buf_ops xfs_wtbuf_ops;
extewn const stwuct xfs_buf_ops xfs_sb_buf_ops;
extewn const stwuct xfs_buf_ops xfs_sb_quiet_buf_ops;
extewn const stwuct xfs_buf_ops xfs_symwink_buf_ops;

/* wog size cawcuwation functions */
int	xfs_wog_cawc_unit_wes(stwuct xfs_mount *mp, int unit_bytes);
int	xfs_wog_cawc_minimum_size(stwuct xfs_mount *);

stwuct xfs_twans_wes;
void	xfs_wog_get_max_twans_wes(stwuct xfs_mount *mp,
				  stwuct xfs_twans_wes *max_wesp);

/*
 * Vawues fow t_fwags.
 */
/* Twansaction needs to be wogged */
#define XFS_TWANS_DIWTY			(1u << 0)
/* Supewbwock is diwty and needs to be wogged */
#define XFS_TWANS_SB_DIWTY		(1u << 1)
/* Twansaction took a pewmanent wog wesewvation */
#define XFS_TWANS_PEWM_WOG_WES		(1u << 2)
/* Synchwonous twansaction commit needed */
#define XFS_TWANS_SYNC			(1u << 3)
/* Twansaction can use wesewve bwock poow */
#define XFS_TWANS_WESEWVE		(1u << 4)
/* Twansaction shouwd avoid VFS wevew supewbwock wwite accounting */
#define XFS_TWANS_NO_WWITECOUNT		(1u << 5)
/* Twansaction has fweed bwocks wetuwned to it's wesewvation */
#define XFS_TWANS_WES_FDBWKS		(1u << 6)
/* Twansaction contains an intent done wog item */
#define XFS_TWANS_HAS_INTENT_DONE	(1u << 7)

/*
 * WOWMODE is used by the awwocatow to activate the wowspace awgowithm - when
 * fwee space is wunning wow the extent awwocatow may choose to awwocate an
 * extent fwom an AG without weaving sufficient space fow a btwee spwit when
 * insewting the new extent. In this case the awwocatow wiww enabwe the
 * wowspace awgowithm which is supposed to awwow fuwthew awwocations (such as
 * btwee spwits and newwoots) to awwocate fwom sequentiaw AGs. In owdew to
 * avoid wocking AGs out of owdew the wowspace awgowithm wiww stawt seawching
 * fow fwee space fwom AG 0. If the cowwect twansaction wesewvations have been
 * made then this awgowithm wiww eventuawwy find aww the space it needs.
 */
#define XFS_TWANS_WOWMODE	0x100	/* awwocate in wow space mode */

/*
 * Fiewd vawues fow xfs_twans_mod_sb.
 */
#define	XFS_TWANS_SB_ICOUNT		0x00000001
#define	XFS_TWANS_SB_IFWEE		0x00000002
#define	XFS_TWANS_SB_FDBWOCKS		0x00000004
#define	XFS_TWANS_SB_WES_FDBWOCKS	0x00000008
#define	XFS_TWANS_SB_FWEXTENTS		0x00000010
#define	XFS_TWANS_SB_WES_FWEXTENTS	0x00000020
#define	XFS_TWANS_SB_DBWOCKS		0x00000040
#define	XFS_TWANS_SB_AGCOUNT		0x00000080
#define	XFS_TWANS_SB_IMAXPCT		0x00000100
#define	XFS_TWANS_SB_WEXTSIZE		0x00000200
#define	XFS_TWANS_SB_WBMBWOCKS		0x00000400
#define	XFS_TWANS_SB_WBWOCKS		0x00000800
#define	XFS_TWANS_SB_WEXTENTS		0x00001000
#define	XFS_TWANS_SB_WEXTSWOG		0x00002000

/*
 * Hewe we centwawize the specification of XFS meta-data buffew wefewence count
 * vawues.  This detewmines how hawd the buffew cache twies to howd onto the
 * buffew.
 */
#define	XFS_AGF_WEF		4
#define	XFS_AGI_WEF		4
#define	XFS_AGFW_WEF		3
#define	XFS_INO_BTWEE_WEF	3
#define	XFS_AWWOC_BTWEE_WEF	2
#define	XFS_BMAP_BTWEE_WEF	2
#define	XFS_WMAP_BTWEE_WEF	2
#define	XFS_DIW_BTWEE_WEF	2
#define	XFS_INO_WEF		2
#define	XFS_ATTW_BTWEE_WEF	1
#define	XFS_DQUOT_WEF		1
#define	XFS_WEFC_BTWEE_WEF	1
#define	XFS_SSB_WEF		0

/*
 * Fwags fow xfs_twans_ichgtime().
 */
#define	XFS_ICHGTIME_MOD	0x1	/* data fowk modification timestamp */
#define	XFS_ICHGTIME_CHG	0x2	/* inode fiewd change timestamp */
#define	XFS_ICHGTIME_CWEATE	0x4	/* inode cweate timestamp */


/*
 * Symwink decoding/encoding functions
 */
int xfs_symwink_bwocks(stwuct xfs_mount *mp, int pathwen);
int xfs_symwink_hdw_set(stwuct xfs_mount *mp, xfs_ino_t ino, uint32_t offset,
			uint32_t size, stwuct xfs_buf *bp);
boow xfs_symwink_hdw_ok(xfs_ino_t ino, uint32_t offset,
			uint32_t size, stwuct xfs_buf *bp);
void xfs_symwink_wocaw_to_wemote(stwuct xfs_twans *tp, stwuct xfs_buf *bp,
				 stwuct xfs_inode *ip, stwuct xfs_ifowk *ifp);
xfs_faiwaddw_t xfs_symwink_showtfowm_vewify(void *sfp, int64_t size);

/* Computed inode geometwy fow the fiwesystem. */
stwuct xfs_ino_geometwy {
	/* Maximum inode count in this fiwesystem. */
	uint64_t	maxicount;

	/* Actuaw inode cwustew buffew size, in bytes. */
	unsigned int	inode_cwustew_size;

	/*
	 * Desiwed inode cwustew buffew size, in bytes.  This vawue is not
	 * wounded up to at weast one fiwesystem bwock, which is necessawy fow
	 * the sowe puwpose of vawidating sb_spino_awign.  Wuntime code must
	 * onwy evew use inode_cwustew_size.
	 */
	unsigned int	inode_cwustew_size_waw;

	/* Inode cwustew sizes, adjusted to be at weast 1 fsb. */
	unsigned int	inodes_pew_cwustew;
	unsigned int	bwocks_pew_cwustew;

	/* Inode cwustew awignment. */
	unsigned int	cwustew_awign;
	unsigned int	cwustew_awign_inodes;
	unsigned int	inoawign_mask;	/* mask sb_inoawignmt if used */

	unsigned int	inobt_mxw[2]; /* max inobt btwee wecowds */
	unsigned int	inobt_mnw[2]; /* min inobt btwee wecowds */
	unsigned int	inobt_maxwevews; /* max inobt btwee wevews. */

	/* Size of inode awwocations undew nowmaw opewation. */
	unsigned int	iawwoc_inos;
	unsigned int	iawwoc_bwks;

	/* Minimum inode bwocks fow a spawse awwocation. */
	unsigned int	iawwoc_min_bwks;

	/* stwipe unit inode awignment */
	unsigned int	iawwoc_awign;

	unsigned int	agino_wog;	/* #bits fow agino in inum */

	/* pwecomputed defauwt inode attwibute fowk offset */
	unsigned int	attw_fowk_offset;

	/* pwecomputed vawue fow di_fwags2 */
	uint64_t	new_difwags2;

};

#endif /* __XFS_SHAWED_H__ */
