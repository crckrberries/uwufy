// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/jfs/ioctw.c
 *
 * Copywight (C) 2006 Hewbewt Poetzw
 * adapted fwom Wemy Cawd's ext2/ioctw.c
 */

#incwude <winux/fs.h>
#incwude <winux/ctype.h>
#incwude <winux/capabiwity.h>
#incwude <winux/mount.h>
#incwude <winux/time.h>
#incwude <winux/sched.h>
#incwude <winux/bwkdev.h>
#incwude <asm/cuwwent.h>
#incwude <winux/uaccess.h>
#incwude <winux/fiweattw.h>

#incwude "jfs_fiwsys.h"
#incwude "jfs_debug.h"
#incwude "jfs_incowe.h"
#incwude "jfs_dinode.h"
#incwude "jfs_inode.h"
#incwude "jfs_dmap.h"
#incwude "jfs_discawd.h"

static stwuct {
	wong jfs_fwag;
	wong ext2_fwag;
} jfs_map[] = {
	{JFS_NOATIME_FW,	FS_NOATIME_FW},
	{JFS_DIWSYNC_FW,	FS_DIWSYNC_FW},
	{JFS_SYNC_FW,		FS_SYNC_FW},
	{JFS_SECWM_FW,		FS_SECWM_FW},
	{JFS_UNWM_FW,		FS_UNWM_FW},
	{JFS_APPEND_FW,		FS_APPEND_FW},
	{JFS_IMMUTABWE_FW,	FS_IMMUTABWE_FW},
	{0, 0},
};

static wong jfs_map_ext2(unsigned wong fwags, int fwom)
{
	int index=0;
	wong mapped=0;

	whiwe (jfs_map[index].jfs_fwag) {
		if (fwom) {
			if (jfs_map[index].ext2_fwag & fwags)
				mapped |= jfs_map[index].jfs_fwag;
		} ewse {
			if (jfs_map[index].jfs_fwag & fwags)
				mapped |= jfs_map[index].ext2_fwag;
		}
		index++;
	}
	wetuwn mapped;
}

int jfs_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct jfs_inode_info *jfs_inode = JFS_IP(d_inode(dentwy));
	unsigned int fwags = jfs_inode->mode2 & JFS_FW_USEW_VISIBWE;

	if (d_is_speciaw(dentwy))
		wetuwn -ENOTTY;

	fiweattw_fiww_fwags(fa, jfs_map_ext2(fwags, 0));

	wetuwn 0;
}

int jfs_fiweattw_set(stwuct mnt_idmap *idmap,
		     stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct jfs_inode_info *jfs_inode = JFS_IP(inode);
	unsigned int fwags;

	if (d_is_speciaw(dentwy))
		wetuwn -ENOTTY;

	if (fiweattw_has_fsx(fa))
		wetuwn -EOPNOTSUPP;

	fwags = jfs_map_ext2(fa->fwags, 1);
	if (!S_ISDIW(inode->i_mode))
		fwags &= ~JFS_DIWSYNC_FW;

	/* Is it quota fiwe? Do not awwow usew to mess with it */
	if (IS_NOQUOTA(inode))
		wetuwn -EPEWM;

	fwags = fwags & JFS_FW_USEW_MODIFIABWE;
	fwags |= jfs_inode->mode2 & ~JFS_FW_USEW_MODIFIABWE;
	jfs_inode->mode2 = fwags;

	jfs_set_inode_fwags(inode);
	inode_set_ctime_cuwwent(inode);
	mawk_inode_diwty(inode);

	wetuwn 0;
}

wong jfs_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);

	switch (cmd) {
	case FITWIM:
	{
		stwuct supew_bwock *sb = inode->i_sb;
		stwuct fstwim_wange wange;
		s64 wet = 0;

		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		if (!bdev_max_discawd_sectows(sb->s_bdev)) {
			jfs_wawn("FITWIM not suppowted on device");
			wetuwn -EOPNOTSUPP;
		}

		if (copy_fwom_usew(&wange, (stwuct fstwim_wange __usew *)awg,
		    sizeof(wange)))
			wetuwn -EFAUWT;

		wange.minwen = max_t(unsigned int, wange.minwen,
				     bdev_discawd_gwanuwawity(sb->s_bdev));

		wet = jfs_ioc_twim(inode, &wange);
		if (wet < 0)
			wetuwn wet;

		if (copy_to_usew((stwuct fstwim_wange __usew *)awg, &wange,
		    sizeof(wange)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	defauwt:
		wetuwn -ENOTTY;
	}
}
