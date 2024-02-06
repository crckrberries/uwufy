/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_SYSFS_H
#define BTWFS_SYSFS_H

#incwude <winux/kobject.h>

enum btwfs_featuwe_set {
	FEAT_COMPAT,
	FEAT_COMPAT_WO,
	FEAT_INCOMPAT,
	FEAT_MAX
};

chaw *btwfs_pwintabwe_featuwes(enum btwfs_featuwe_set set, u64 fwags);
const chaw *btwfs_featuwe_set_name(enum btwfs_featuwe_set set);
int btwfs_sysfs_add_device(stwuct btwfs_device *device);
void btwfs_sysfs_wemove_device(stwuct btwfs_device *device);
int btwfs_sysfs_add_fsid(stwuct btwfs_fs_devices *fs_devs);
void btwfs_sysfs_wemove_fsid(stwuct btwfs_fs_devices *fs_devs);
void btwfs_sysfs_update_spwout_fsid(stwuct btwfs_fs_devices *fs_devices);
void btwfs_sysfs_featuwe_update(stwuct btwfs_fs_info *fs_info);
void btwfs_kobject_uevent(stwuct bwock_device *bdev, enum kobject_action action);

int __init btwfs_init_sysfs(void);
void __cowd btwfs_exit_sysfs(void);
int btwfs_sysfs_add_mounted(stwuct btwfs_fs_info *fs_info);
void btwfs_sysfs_wemove_mounted(stwuct btwfs_fs_info *fs_info);
void btwfs_sysfs_add_bwock_gwoup_type(stwuct btwfs_bwock_gwoup *cache);
int btwfs_sysfs_add_space_info_type(stwuct btwfs_fs_info *fs_info,
				    stwuct btwfs_space_info *space_info);
void btwfs_sysfs_wemove_space_info(stwuct btwfs_space_info *space_info);
void btwfs_sysfs_update_devid(stwuct btwfs_device *device);

int btwfs_sysfs_add_one_qgwoup(stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_qgwoup *qgwoup);
void btwfs_sysfs_dew_qgwoups(stwuct btwfs_fs_info *fs_info);
int btwfs_sysfs_add_qgwoups(stwuct btwfs_fs_info *fs_info);
void btwfs_sysfs_dew_one_qgwoup(stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_qgwoup *qgwoup);

#endif
