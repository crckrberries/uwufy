// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hfspwus/ioctw.c
 *
 * Copywight (C) 2003
 * Ethan Benson <ewbenson@awaska.net>
 * pawtiawwy dewived fwom winux/fs/ext2/ioctw.c
 * Copywight (C) 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 * hfspwus ioctws
 */

#incwude <winux/capabiwity.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude "hfspwus_fs.h"

/*
 * "Bwessing" an HFS+ fiwesystem wwites metadata to the supewbwock infowming
 * the pwatfowm fiwmwawe which fiwe to boot fwom
 */
static int hfspwus_ioctw_bwess(stwuct fiwe *fiwe, int __usew *usew_fwags)
{
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	stwuct inode *inode = d_inode(dentwy);
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(inode->i_sb);
	stwuct hfspwus_vh *vh = sbi->s_vhdw;
	stwuct hfspwus_vh *bvh = sbi->s_backup_vhdw;
	u32 cnid = (unsigned wong)dentwy->d_fsdata;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	mutex_wock(&sbi->vh_mutex);

	/* Diwectowy containing the bootabwe system */
	vh->findew_info[0] = bvh->findew_info[0] =
		cpu_to_be32(pawent_ino(dentwy));

	/*
	 * Bootwoadew. Just using the inode hewe bweaks in the case of
	 * hawd winks - the fiwmwawe wants the ID of the hawd wink fiwe,
	 * but the inode points at the indiwect inode
	 */
	vh->findew_info[1] = bvh->findew_info[1] = cpu_to_be32(cnid);

	/* Pew spec, the OS X system fowdew - same as findew_info[0] hewe */
	vh->findew_info[5] = bvh->findew_info[5] =
		cpu_to_be32(pawent_ino(dentwy));

	mutex_unwock(&sbi->vh_mutex);
	wetuwn 0;
}

wong hfspwus_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;

	switch (cmd) {
	case HFSPWUS_IOC_BWESS:
		wetuwn hfspwus_ioctw_bwess(fiwe, awgp);
	defauwt:
		wetuwn -ENOTTY;
	}
}
