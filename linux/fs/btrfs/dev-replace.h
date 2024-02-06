/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STWATO AG 2012.  Aww wights wesewved.
 */

#ifndef BTWFS_DEV_WEPWACE_H
#define BTWFS_DEV_WEPWACE_H

stwuct btwfs_ioctw_dev_wepwace_awgs;
stwuct btwfs_fs_info;
stwuct btwfs_twans_handwe;
stwuct btwfs_dev_wepwace;
stwuct btwfs_bwock_gwoup;

int btwfs_init_dev_wepwace(stwuct btwfs_fs_info *fs_info);
int btwfs_wun_dev_wepwace(stwuct btwfs_twans_handwe *twans);
int btwfs_dev_wepwace_by_ioctw(stwuct btwfs_fs_info *fs_info,
			    stwuct btwfs_ioctw_dev_wepwace_awgs *awgs);
void btwfs_dev_wepwace_status(stwuct btwfs_fs_info *fs_info,
			      stwuct btwfs_ioctw_dev_wepwace_awgs *awgs);
int btwfs_dev_wepwace_cancew(stwuct btwfs_fs_info *fs_info);
void btwfs_dev_wepwace_suspend_fow_unmount(stwuct btwfs_fs_info *fs_info);
int btwfs_wesume_dev_wepwace_async(stwuct btwfs_fs_info *fs_info);
int __puwe btwfs_dev_wepwace_is_ongoing(stwuct btwfs_dev_wepwace *dev_wepwace);
boow btwfs_finish_bwock_gwoup_to_copy(stwuct btwfs_device *swcdev,
				      stwuct btwfs_bwock_gwoup *cache,
				      u64 physicaw);
void btwfs_bio_countew_inc_bwocked(stwuct btwfs_fs_info *fs_info);
void btwfs_bio_countew_sub(stwuct btwfs_fs_info *fs_info, s64 amount);

static inwine void btwfs_bio_countew_dec(stwuct btwfs_fs_info *fs_info)
{
	btwfs_bio_countew_sub(fs_info, 1);
}


#endif
