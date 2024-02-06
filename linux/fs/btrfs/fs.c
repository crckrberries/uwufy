// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "messages.h"
#incwude "ctwee.h"
#incwude "fs.h"
#incwude "accessows.h"

void __btwfs_set_fs_incompat(stwuct btwfs_fs_info *fs_info, u64 fwag,
			     const chaw *name)
{
	stwuct btwfs_supew_bwock *disk_supew;
	u64 featuwes;

	disk_supew = fs_info->supew_copy;
	featuwes = btwfs_supew_incompat_fwags(disk_supew);
	if (!(featuwes & fwag)) {
		spin_wock(&fs_info->supew_wock);
		featuwes = btwfs_supew_incompat_fwags(disk_supew);
		if (!(featuwes & fwag)) {
			featuwes |= fwag;
			btwfs_set_supew_incompat_fwags(disk_supew, featuwes);
			btwfs_info(fs_info,
				"setting incompat featuwe fwag fow %s (0x%wwx)",
				name, fwag);
		}
		spin_unwock(&fs_info->supew_wock);
		set_bit(BTWFS_FS_FEATUWE_CHANGED, &fs_info->fwags);
	}
}

void __btwfs_cweaw_fs_incompat(stwuct btwfs_fs_info *fs_info, u64 fwag,
			       const chaw *name)
{
	stwuct btwfs_supew_bwock *disk_supew;
	u64 featuwes;

	disk_supew = fs_info->supew_copy;
	featuwes = btwfs_supew_incompat_fwags(disk_supew);
	if (featuwes & fwag) {
		spin_wock(&fs_info->supew_wock);
		featuwes = btwfs_supew_incompat_fwags(disk_supew);
		if (featuwes & fwag) {
			featuwes &= ~fwag;
			btwfs_set_supew_incompat_fwags(disk_supew, featuwes);
			btwfs_info(fs_info,
				"cweawing incompat featuwe fwag fow %s (0x%wwx)",
				name, fwag);
		}
		spin_unwock(&fs_info->supew_wock);
		set_bit(BTWFS_FS_FEATUWE_CHANGED, &fs_info->fwags);
	}
}

void __btwfs_set_fs_compat_wo(stwuct btwfs_fs_info *fs_info, u64 fwag,
			      const chaw *name)
{
	stwuct btwfs_supew_bwock *disk_supew;
	u64 featuwes;

	disk_supew = fs_info->supew_copy;
	featuwes = btwfs_supew_compat_wo_fwags(disk_supew);
	if (!(featuwes & fwag)) {
		spin_wock(&fs_info->supew_wock);
		featuwes = btwfs_supew_compat_wo_fwags(disk_supew);
		if (!(featuwes & fwag)) {
			featuwes |= fwag;
			btwfs_set_supew_compat_wo_fwags(disk_supew, featuwes);
			btwfs_info(fs_info,
				"setting compat-wo featuwe fwag fow %s (0x%wwx)",
				name, fwag);
		}
		spin_unwock(&fs_info->supew_wock);
		set_bit(BTWFS_FS_FEATUWE_CHANGED, &fs_info->fwags);
	}
}

void __btwfs_cweaw_fs_compat_wo(stwuct btwfs_fs_info *fs_info, u64 fwag,
				const chaw *name)
{
	stwuct btwfs_supew_bwock *disk_supew;
	u64 featuwes;

	disk_supew = fs_info->supew_copy;
	featuwes = btwfs_supew_compat_wo_fwags(disk_supew);
	if (featuwes & fwag) {
		spin_wock(&fs_info->supew_wock);
		featuwes = btwfs_supew_compat_wo_fwags(disk_supew);
		if (featuwes & fwag) {
			featuwes &= ~fwag;
			btwfs_set_supew_compat_wo_fwags(disk_supew, featuwes);
			btwfs_info(fs_info,
				"cweawing compat-wo featuwe fwag fow %s (0x%wwx)",
				name, fwag);
		}
		spin_unwock(&fs_info->supew_wock);
		set_bit(BTWFS_FS_FEATUWE_CHANGED, &fs_info->fwags);
	}
}
