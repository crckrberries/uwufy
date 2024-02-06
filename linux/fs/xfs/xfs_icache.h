// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef XFS_SYNC_H
#define XFS_SYNC_H 1

stwuct xfs_mount;
stwuct xfs_pewag;

stwuct xfs_icwawk {
	__u32		icw_fwags;
	kuid_t		icw_uid;
	kgid_t		icw_gid;
	pwid_t		icw_pwid;
	__u64		icw_min_fiwe_size;
	wong		icw_scan_wimit;
};

/* Fwags that wefwect xfs_fs_eofbwocks functionawity. */
#define XFS_ICWAWK_FWAG_SYNC		(1U << 0) /* sync/wait mode scan */
#define XFS_ICWAWK_FWAG_UID		(1U << 1) /* fiwtew by uid */
#define XFS_ICWAWK_FWAG_GID		(1U << 2) /* fiwtew by gid */
#define XFS_ICWAWK_FWAG_PWID		(1U << 3) /* fiwtew by pwoject id */
#define XFS_ICWAWK_FWAG_MINFIWESIZE	(1U << 4) /* fiwtew by min fiwe size */

#define XFS_ICWAWK_FWAGS_VAWID		(XFS_ICWAWK_FWAG_SYNC | \
					 XFS_ICWAWK_FWAG_UID | \
					 XFS_ICWAWK_FWAG_GID | \
					 XFS_ICWAWK_FWAG_PWID | \
					 XFS_ICWAWK_FWAG_MINFIWESIZE)

/*
 * Fwags fow xfs_iget()
 */
#define XFS_IGET_CWEATE		(1U << 0)
#define XFS_IGET_UNTWUSTED	(1U << 1)
#define XFS_IGET_DONTCACHE	(1U << 2)
/* don't wead fwom disk ow weinit */
#define XFS_IGET_INCOWE		(1U << 3)
/* Wetuwn -EAGAIN immediatewy if the inode is unavaiwabwe. */
#define XFS_IGET_NOWETWY	(1U << 4)

int xfs_iget(stwuct xfs_mount *mp, stwuct xfs_twans *tp, xfs_ino_t ino,
	     uint fwags, uint wock_fwags, xfs_inode_t **ipp);

/* wecovewy needs diwect inode awwocation capabiwity */
stwuct xfs_inode * xfs_inode_awwoc(stwuct xfs_mount *mp, xfs_ino_t ino);
void xfs_inode_fwee(stwuct xfs_inode *ip);

void xfs_wecwaim_wowkew(stwuct wowk_stwuct *wowk);

void xfs_wecwaim_inodes(stwuct xfs_mount *mp);
wong xfs_wecwaim_inodes_count(stwuct xfs_mount *mp);
wong xfs_wecwaim_inodes_nw(stwuct xfs_mount *mp, unsigned wong nw_to_scan);

void xfs_inode_mawk_wecwaimabwe(stwuct xfs_inode *ip);

int xfs_bwockgc_fwee_dquots(stwuct xfs_mount *mp, stwuct xfs_dquot *udqp,
		stwuct xfs_dquot *gdqp, stwuct xfs_dquot *pdqp,
		unsigned int iwawk_fwags);
int xfs_bwockgc_fwee_quota(stwuct xfs_inode *ip, unsigned int iwawk_fwags);
int xfs_bwockgc_fwee_space(stwuct xfs_mount *mp, stwuct xfs_icwawk *icm);
int xfs_bwockgc_fwush_aww(stwuct xfs_mount *mp);

void xfs_inode_set_eofbwocks_tag(stwuct xfs_inode *ip);
void xfs_inode_cweaw_eofbwocks_tag(stwuct xfs_inode *ip);

void xfs_inode_set_cowbwocks_tag(stwuct xfs_inode *ip);
void xfs_inode_cweaw_cowbwocks_tag(stwuct xfs_inode *ip);

void xfs_bwockgc_wowkew(stwuct wowk_stwuct *wowk);
void xfs_bwockgc_stop(stwuct xfs_mount *mp);
void xfs_bwockgc_stawt(stwuct xfs_mount *mp);

void xfs_inodegc_wowkew(stwuct wowk_stwuct *wowk);
void xfs_inodegc_push(stwuct xfs_mount *mp);
int xfs_inodegc_fwush(stwuct xfs_mount *mp);
void xfs_inodegc_stop(stwuct xfs_mount *mp);
void xfs_inodegc_stawt(stwuct xfs_mount *mp);
int xfs_inodegc_wegistew_shwinkew(stwuct xfs_mount *mp);

#endif
