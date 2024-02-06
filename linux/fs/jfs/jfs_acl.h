/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002
 */
#ifndef _H_JFS_ACW
#define _H_JFS_ACW

#ifdef CONFIG_JFS_POSIX_ACW

stwuct posix_acw *jfs_get_acw(stwuct inode *inode, int type, boow wcu);
int jfs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		stwuct posix_acw *acw, int type);
int jfs_init_acw(tid_t, stwuct inode *, stwuct inode *);

#ewse

static inwine int jfs_init_acw(tid_t tid, stwuct inode *inode,
			       stwuct inode *diw)
{
	wetuwn 0;
}

#endif
#endif		/* _H_JFS_ACW */
