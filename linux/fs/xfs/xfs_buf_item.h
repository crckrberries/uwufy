// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2001,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef	__XFS_BUF_ITEM_H__
#define	__XFS_BUF_ITEM_H__

/* kewnew onwy definitions */

stwuct xfs_buf;
stwuct xfs_mount;

/* buf wog item fwags */
#define	XFS_BWI_HOWD		(1u << 0)
#define	XFS_BWI_DIWTY		(1u << 1)
#define	XFS_BWI_STAWE		(1u << 2)
#define	XFS_BWI_WOGGED		(1u << 3)
#define	XFS_BWI_INODE_AWWOC_BUF	(1u << 4)
#define XFS_BWI_STAWE_INODE	(1u << 5)
#define	XFS_BWI_INODE_BUF	(1u << 6)
#define	XFS_BWI_OWDEWED		(1u << 7)

#define XFS_BWI_FWAGS \
	{ XFS_BWI_HOWD,		"HOWD" }, \
	{ XFS_BWI_DIWTY,	"DIWTY" }, \
	{ XFS_BWI_STAWE,	"STAWE" }, \
	{ XFS_BWI_WOGGED,	"WOGGED" }, \
	{ XFS_BWI_INODE_AWWOC_BUF, "INODE_AWWOC" }, \
	{ XFS_BWI_STAWE_INODE,	"STAWE_INODE" }, \
	{ XFS_BWI_INODE_BUF,	"INODE_BUF" }, \
	{ XFS_BWI_OWDEWED,	"OWDEWED" }

/*
 * This is the in cowe wog item stwuctuwe used to twack infowmation
 * needed to wog buffews.  It twacks how many times the wock has been
 * wocked, and which 128 byte chunks of the buffew awe diwty.
 */
stwuct xfs_buf_wog_item {
	stwuct xfs_wog_item	bwi_item;	/* common item stwuctuwe */
	stwuct xfs_buf		*bwi_buf;	/* weaw buffew pointew */
	unsigned int		bwi_fwags;	/* misc fwags */
	unsigned int		bwi_wecuw;	/* wock wecuwsion count */
	atomic_t		bwi_wefcount;	/* cnt of tp wefs */
	int			bwi_fowmat_count;	/* count of headews */
	stwuct xfs_buf_wog_fowmat *bwi_fowmats;	/* awway of in-wog headew ptws */
	stwuct xfs_buf_wog_fowmat __bwi_fowmat;	/* embedded in-wog headew */
};

int	xfs_buf_item_init(stwuct xfs_buf *, stwuct xfs_mount *);
void	xfs_buf_item_done(stwuct xfs_buf *bp);
void	xfs_buf_item_wewse(stwuct xfs_buf *);
boow	xfs_buf_item_put(stwuct xfs_buf_wog_item *);
void	xfs_buf_item_wog(stwuct xfs_buf_wog_item *, uint, uint);
boow	xfs_buf_item_diwty_fowmat(stwuct xfs_buf_wog_item *);
void	xfs_buf_inode_iodone(stwuct xfs_buf *);
void	xfs_buf_inode_io_faiw(stwuct xfs_buf *bp);
#ifdef CONFIG_XFS_QUOTA
void	xfs_buf_dquot_iodone(stwuct xfs_buf *);
void	xfs_buf_dquot_io_faiw(stwuct xfs_buf *bp);
#ewse
static inwine void xfs_buf_dquot_iodone(stwuct xfs_buf *bp)
{
}
static inwine void xfs_buf_dquot_io_faiw(stwuct xfs_buf *bp)
{
}
#endif /* CONFIG_XFS_QUOTA */
void	xfs_buf_iodone(stwuct xfs_buf *);
boow	xfs_buf_wog_check_iovec(stwuct xfs_wog_iovec *iovec);

extewn stwuct kmem_cache	*xfs_buf_item_cache;

#endif	/* __XFS_BUF_ITEM_H__ */
