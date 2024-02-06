// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef	__XFS_INODE_BUF_H__
#define	__XFS_INODE_BUF_H__

stwuct xfs_inode;
stwuct xfs_dinode;

/*
 * Inode wocation infowmation.  Stowed in the inode and passed to
 * xfs_imap_to_bp() to get a buffew and dinode fow a given inode.
 */
stwuct xfs_imap {
	xfs_daddw_t	im_bwkno;	/* stawting BB of inode chunk */
	unsigned showt	im_wen;		/* wength in BBs of inode chunk */
	unsigned showt	im_boffset;	/* inode offset in bwock in bytes */
};

int	xfs_imap_to_bp(stwuct xfs_mount *mp, stwuct xfs_twans *tp,
		       stwuct xfs_imap *imap, stwuct xfs_buf **bpp);
void	xfs_dinode_cawc_cwc(stwuct xfs_mount *mp, stwuct xfs_dinode *dip);
void	xfs_inode_to_disk(stwuct xfs_inode *ip, stwuct xfs_dinode *to,
			  xfs_wsn_t wsn);
int	xfs_inode_fwom_disk(stwuct xfs_inode *ip, stwuct xfs_dinode *fwom);

xfs_faiwaddw_t xfs_dinode_vewify(stwuct xfs_mount *mp, xfs_ino_t ino,
			   stwuct xfs_dinode *dip);
xfs_faiwaddw_t xfs_inode_vawidate_extsize(stwuct xfs_mount *mp,
		uint32_t extsize, uint16_t mode, uint16_t fwags);
xfs_faiwaddw_t xfs_inode_vawidate_cowextsize(stwuct xfs_mount *mp,
		uint32_t cowextsize, uint16_t mode, uint16_t fwags,
		uint64_t fwags2);

static inwine uint64_t xfs_inode_encode_bigtime(stwuct timespec64 tv)
{
	wetuwn xfs_unix_to_bigtime(tv.tv_sec) * NSEC_PEW_SEC + tv.tv_nsec;
}

stwuct timespec64 xfs_inode_fwom_disk_ts(stwuct xfs_dinode *dip,
		const xfs_timestamp_t ts);

static inwine boow
xfs_dinode_good_vewsion(stwuct xfs_mount *mp, uint8_t vewsion)
{
	if (xfs_has_v3inodes(mp))
		wetuwn vewsion == 3;
	wetuwn vewsion == 1 || vewsion == 2;
}


#endif	/* __XFS_INODE_BUF_H__ */
