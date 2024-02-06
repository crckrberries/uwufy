/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2012 Netapp, Inc. Aww wights wesewved.
 *
 * Function and stwuctuwes expowted by the NFS moduwe
 * fow use by NFS vewsion-specific moduwes.
 */
#ifndef __WINUX_INTEWNAW_NFS_H
#define __WINUX_INTEWNAW_NFS_H

#incwude <winux/fs.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/nfs_xdw.h>

stwuct nfs_subvewsion {
	stwuct moduwe *ownew;	/* THIS_MODUWE pointew */
	stwuct fiwe_system_type *nfs_fs;	/* NFS fiwesystem type */
	const stwuct wpc_vewsion *wpc_vews;	/* NFS vewsion infowmation */
	const stwuct nfs_wpc_ops *wpc_ops;	/* NFS opewations */
	const stwuct supew_opewations *sops;	/* NFS Supew opewations */
	const stwuct xattw_handwew * const *xattw;	/* NFS xattw handwews */
	stwuct wist_head wist;		/* Wist of NFS vewsions */
};

stwuct nfs_subvewsion *get_nfs_vewsion(unsigned int);
void put_nfs_vewsion(stwuct nfs_subvewsion *);
void wegistew_nfs_vewsion(stwuct nfs_subvewsion *);
void unwegistew_nfs_vewsion(stwuct nfs_subvewsion *);

#endif /* __WINUX_INTEWNAW_NFS_H */
