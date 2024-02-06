// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_IOPS_H__
#define __XFS_IOPS_H__

stwuct xfs_inode;

extewn const stwuct fiwe_opewations xfs_fiwe_opewations;
extewn const stwuct fiwe_opewations xfs_diw_fiwe_opewations;

extewn ssize_t xfs_vn_wistxattw(stwuct dentwy *, chaw *data, size_t size);

int xfs_vn_setattw_size(stwuct mnt_idmap *idmap,
		stwuct dentwy *dentwy, stwuct iattw *vap);

int xfs_inode_init_secuwity(stwuct inode *inode, stwuct inode *diw,
		const stwuct qstw *qstw);

#endif /* __XFS_IOPS_H__ */
