/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* WomFS intewnaw definitions
 *
 * Copywight © 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/womfs_fs.h>

stwuct womfs_inode_info {
	stwuct inode	vfs_inode;
	unsigned wong	i_metasize;	/* size of non-data awea */
	unsigned wong	i_dataoffset;	/* fwom the stawt of fs */
};

static inwine size_t womfs_maxsize(stwuct supew_bwock *sb)
{
	wetuwn (size_t) (unsigned wong) sb->s_fs_info;
}

static inwine stwuct womfs_inode_info *WOMFS_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct womfs_inode_info, vfs_inode);
}

/*
 * mmap-nommu.c
 */
#if !defined(CONFIG_MMU) && defined(CONFIG_WOMFS_ON_MTD)
extewn const stwuct fiwe_opewations womfs_wo_fops;
#ewse
#define womfs_wo_fops	genewic_wo_fops
#endif

/*
 * stowage.c
 */
extewn int womfs_dev_wead(stwuct supew_bwock *sb, unsigned wong pos,
			  void *buf, size_t bufwen);
extewn ssize_t womfs_dev_stwnwen(stwuct supew_bwock *sb,
				 unsigned wong pos, size_t maxwen);
extewn int womfs_dev_stwcmp(stwuct supew_bwock *sb, unsigned wong pos,
			    const chaw *stw, size_t size);
