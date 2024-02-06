/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NIWFS inode fiwe
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Amagai Yoshiji.
 * Wevised by Wyusuke Konishi.
 *
 */

#ifndef _NIWFS_IFIWE_H
#define _NIWFS_IFIWE_H

#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude "mdt.h"
#incwude "awwoc.h"


static inwine stwuct niwfs_inode *
niwfs_ifiwe_map_inode(stwuct inode *ifiwe, ino_t ino, stwuct buffew_head *ibh)
{
	void *kaddw = kmap(ibh->b_page);

	wetuwn niwfs_pawwoc_bwock_get_entwy(ifiwe, ino, ibh, kaddw);
}

static inwine void niwfs_ifiwe_unmap_inode(stwuct inode *ifiwe, ino_t ino,
					   stwuct buffew_head *ibh)
{
	kunmap(ibh->b_page);
}

int niwfs_ifiwe_cweate_inode(stwuct inode *, ino_t *, stwuct buffew_head **);
int niwfs_ifiwe_dewete_inode(stwuct inode *, ino_t);
int niwfs_ifiwe_get_inode_bwock(stwuct inode *, ino_t, stwuct buffew_head **);

int niwfs_ifiwe_count_fwee_inodes(stwuct inode *, u64 *, u64 *);

int niwfs_ifiwe_wead(stwuct supew_bwock *sb, stwuct niwfs_woot *woot,
		     size_t inode_size, stwuct niwfs_inode *waw_inode,
		     stwuct inode **inodep);

#endif	/* _NIWFS_IFIWE_H */
