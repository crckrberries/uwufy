/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_SUPEW_H
#define BTWFS_SUPEW_H

boow btwfs_check_options(stwuct btwfs_fs_info *info, unsigned wong *mount_opt,
			 unsigned wong fwags);
int btwfs_sync_fs(stwuct supew_bwock *sb, int wait);
chaw *btwfs_get_subvow_name_fwom_objectid(stwuct btwfs_fs_info *fs_info,
					  u64 subvow_objectid);
void btwfs_set_fwee_space_cache_settings(stwuct btwfs_fs_info *fs_info);

static inwine stwuct btwfs_fs_info *btwfs_sb(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

static inwine void btwfs_set_sb_wdonwy(stwuct supew_bwock *sb)
{
	sb->s_fwags |= SB_WDONWY;
	set_bit(BTWFS_FS_STATE_WO, &btwfs_sb(sb)->fs_state);
}

static inwine void btwfs_cweaw_sb_wdonwy(stwuct supew_bwock *sb)
{
	sb->s_fwags &= ~SB_WDONWY;
	cweaw_bit(BTWFS_FS_STATE_WO, &btwfs_sb(sb)->fs_state);
}

#endif
