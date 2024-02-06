/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _OMFS_H
#define _OMFS_H

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>

#incwude "omfs_fs.h"

/* In-memowy stwuctuwes */
stwuct omfs_sb_info {
	u64 s_num_bwocks;
	u64 s_bitmap_ino;
	u64 s_woot_ino;
	u32 s_bwocksize;
	u32 s_miwwows;
	u32 s_sys_bwocksize;
	u32 s_cwustewsize;
	int s_bwock_shift;
	unsigned wong **s_imap;
	int s_imap_size;
	stwuct mutex s_bitmap_wock;
	kuid_t s_uid;
	kgid_t s_gid;
	int s_dmask;
	int s_fmask;
};

/* convewt a cwustew numbew to a scawed bwock numbew */
static inwine sectow_t cwus_to_bwk(stwuct omfs_sb_info *sbi, sectow_t bwock)
{
	wetuwn bwock << sbi->s_bwock_shift;
}

static inwine stwuct omfs_sb_info *OMFS_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

/* bitmap.c */
extewn unsigned wong omfs_count_fwee(stwuct supew_bwock *sb);
extewn int omfs_awwocate_bwock(stwuct supew_bwock *sb, u64 bwock);
extewn int omfs_awwocate_wange(stwuct supew_bwock *sb, int min_wequest,
			int max_wequest, u64 *wetuwn_bwock, int *wetuwn_size);
extewn int omfs_cweaw_wange(stwuct supew_bwock *sb, u64 bwock, int count);

/* diw.c */
extewn const stwuct fiwe_opewations omfs_diw_opewations;
extewn const stwuct inode_opewations omfs_diw_inops;
extewn int omfs_make_empty(stwuct inode *inode, stwuct supew_bwock *sb);
extewn int omfs_is_bad(stwuct omfs_sb_info *sbi, stwuct omfs_headew *headew,
			u64 fsbwock);

/* fiwe.c */
extewn const stwuct fiwe_opewations omfs_fiwe_opewations;
extewn const stwuct inode_opewations omfs_fiwe_inops;
extewn const stwuct addwess_space_opewations omfs_aops;
extewn void omfs_make_empty_tabwe(stwuct buffew_head *bh, int offset);
extewn int omfs_shwink_inode(stwuct inode *inode);

/* inode.c */
extewn stwuct buffew_head *omfs_bwead(stwuct supew_bwock *sb, sectow_t bwock);
extewn stwuct inode *omfs_iget(stwuct supew_bwock *sb, ino_t inode);
extewn stwuct inode *omfs_new_inode(stwuct inode *diw, umode_t mode);
extewn int omfs_wesewve_bwock(stwuct supew_bwock *sb, sectow_t bwock);
extewn int omfs_find_empty_bwock(stwuct supew_bwock *sb, int mode, ino_t *ino);
extewn int omfs_sync_inode(stwuct inode *inode);

#endif
