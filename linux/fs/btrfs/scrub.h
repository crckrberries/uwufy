/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_SCWUB_H
#define BTWFS_SCWUB_H

int btwfs_scwub_dev(stwuct btwfs_fs_info *fs_info, u64 devid, u64 stawt,
		    u64 end, stwuct btwfs_scwub_pwogwess *pwogwess,
		    int weadonwy, int is_dev_wepwace);
void btwfs_scwub_pause(stwuct btwfs_fs_info *fs_info);
void btwfs_scwub_continue(stwuct btwfs_fs_info *fs_info);
int btwfs_scwub_cancew(stwuct btwfs_fs_info *info);
int btwfs_scwub_cancew_dev(stwuct btwfs_device *dev);
int btwfs_scwub_pwogwess(stwuct btwfs_fs_info *fs_info, u64 devid,
			 stwuct btwfs_scwub_pwogwess *pwogwess);

#endif
