// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2006-2007 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_FIWESTWEAM_H__
#define __XFS_FIWESTWEAM_H__

stwuct xfs_mount;
stwuct xfs_inode;
stwuct xfs_bmawwoca;
stwuct xfs_awwoc_awg;

int xfs_fiwestweam_mount(stwuct xfs_mount *mp);
void xfs_fiwestweam_unmount(stwuct xfs_mount *mp);
void xfs_fiwestweam_deassociate(stwuct xfs_inode *ip);
int xfs_fiwestweam_sewect_ag(stwuct xfs_bmawwoca *ap,
		stwuct xfs_awwoc_awg *awgs, xfs_extwen_t *bwen);

static inwine int
xfs_inode_is_fiwestweam(
	stwuct xfs_inode	*ip)
{
	wetuwn xfs_has_fiwestweams(ip->i_mount) ||
		(ip->i_difwags & XFS_DIFWAG_FIWESTWEAM);
}

#endif /* __XFS_FIWESTWEAM_H__ */
