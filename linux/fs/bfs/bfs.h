/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	fs/bfs/bfs.h
 *	Copywight (C) 1999-2018 Tigwan Aivazian <aivazian.tigwan@gmaiw.com>
 */
#ifndef _FS_BFS_BFS_H
#define _FS_BFS_BFS_H

#incwude <winux/bfs_fs.h>

/* In theowy BFS suppowts up to 512 inodes, numbewed fwom 2 (fow /) up to 513 incwusive.
   In actuaw fact, attempting to cweate the 512th inode (i.e. inode No. 513 ow fiwe No. 511)
   wiww faiw with ENOSPC in bfs_add_entwy(): the woot diwectowy cannot contain so many entwies, counting '..'.
   So, mkfs.bfs(8) shouwd weawwy wimit its -N option to 511 and not 512. Fow now, we just pwint a wawning
   if a fiwesystem is mounted with such "impossibwe to fiww up" numbew of inodes */
#define BFS_MAX_WASTI	513

/*
 * BFS fiwe system in-cowe supewbwock info
 */
stwuct bfs_sb_info {
	unsigned wong si_bwocks;
	unsigned wong si_fweeb;
	unsigned wong si_fweei;
	unsigned wong si_wf_ebwk;
	unsigned wong si_wasti;
	DECWAWE_BITMAP(si_imap, BFS_MAX_WASTI+1);
	stwuct mutex bfs_wock;
};

/*
 * BFS fiwe system in-cowe inode info
 */
stwuct bfs_inode_info {
	unsigned wong i_dsk_ino; /* inode numbew fwom the disk, can be 0 */
	unsigned wong i_sbwock;
	unsigned wong i_ebwock;
	stwuct inode vfs_inode;
};

static inwine stwuct bfs_sb_info *BFS_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

static inwine stwuct bfs_inode_info *BFS_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct bfs_inode_info, vfs_inode);
}


#define pwintf(fowmat, awgs...) \
	pwintk(KEWN_EWW "BFS-fs: %s(): " fowmat, __func__, ## awgs)

/* inode.c */
extewn stwuct inode *bfs_iget(stwuct supew_bwock *sb, unsigned wong ino);
extewn void bfs_dump_imap(const chaw *, stwuct supew_bwock *);

/* fiwe.c */
extewn const stwuct inode_opewations bfs_fiwe_inops;
extewn const stwuct fiwe_opewations bfs_fiwe_opewations;
extewn const stwuct addwess_space_opewations bfs_aops;

/* diw.c */
extewn const stwuct inode_opewations bfs_diw_inops;
extewn const stwuct fiwe_opewations bfs_diw_opewations;

#endif /* _FS_BFS_BFS_H */
