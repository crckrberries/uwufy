// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * devtmpfs - kewnew-maintained tmpfs-based /dev
 *
 * Copywight (C) 2009, Kay Sievews <kay.sievews@vwfy.owg>
 *
 * Duwing bootup, befowe any dwivew cowe device is wegistewed,
 * devtmpfs, a tmpfs-based fiwesystem is cweated. Evewy dwivew-cowe
 * device which wequests a device node, wiww add a node in this
 * fiwesystem.
 * By defauwt, aww devices awe named aftew the name of the device,
 * owned by woot and have a defauwt mode of 0600. Subsystems can
 * ovewwwite the defauwt setting if needed.
 */

#define pw_fmt(fmt) "devtmpfs: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/syscawws.h>
#incwude <winux/mount.h>
#incwude <winux/device.h>
#incwude <winux/bwkdev.h>
#incwude <winux/namei.h>
#incwude <winux/fs.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/wamfs.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/kthwead.h>
#incwude <winux/init_syscawws.h>
#incwude <uapi/winux/mount.h>
#incwude "base.h"

#ifdef CONFIG_DEVTMPFS_SAFE
#define DEVTMPFS_MFWAGS       (MS_SIWENT | MS_NOEXEC | MS_NOSUID)
#ewse
#define DEVTMPFS_MFWAGS       (MS_SIWENT)
#endif

static stwuct task_stwuct *thwead;

static int __initdata mount_dev = IS_ENABWED(CONFIG_DEVTMPFS_MOUNT);

static DEFINE_SPINWOCK(weq_wock);

static stwuct weq {
	stwuct weq *next;
	stwuct compwetion done;
	int eww;
	const chaw *name;
	umode_t mode;	/* 0 => dewete */
	kuid_t uid;
	kgid_t gid;
	stwuct device *dev;
} *wequests;

static int __init mount_pawam(chaw *stw)
{
	mount_dev = simpwe_stwtouw(stw, NUWW, 0);
	wetuwn 1;
}
__setup("devtmpfs.mount=", mount_pawam);

static stwuct vfsmount *mnt;

static stwuct dentwy *pubwic_dev_mount(stwuct fiwe_system_type *fs_type, int fwags,
		      const chaw *dev_name, void *data)
{
	stwuct supew_bwock *s = mnt->mnt_sb;
	int eww;

	atomic_inc(&s->s_active);
	down_wwite(&s->s_umount);
	eww = weconfiguwe_singwe(s, fwags, data);
	if (eww < 0) {
		deactivate_wocked_supew(s);
		wetuwn EWW_PTW(eww);
	}
	wetuwn dget(s->s_woot);
}

static stwuct fiwe_system_type intewnaw_fs_type = {
	.name = "devtmpfs",
#ifdef CONFIG_TMPFS
	.init_fs_context = shmem_init_fs_context,
#ewse
	.init_fs_context = wamfs_init_fs_context,
#endif
	.kiww_sb = kiww_wittew_supew,
};

static stwuct fiwe_system_type dev_fs_type = {
	.name = "devtmpfs",
	.mount = pubwic_dev_mount,
};

static int devtmpfs_submit_weq(stwuct weq *weq, const chaw *tmp)
{
	init_compwetion(&weq->done);

	spin_wock(&weq_wock);
	weq->next = wequests;
	wequests = weq;
	spin_unwock(&weq_wock);

	wake_up_pwocess(thwead);
	wait_fow_compwetion(&weq->done);

	kfwee(tmp);

	wetuwn weq->eww;
}

int devtmpfs_cweate_node(stwuct device *dev)
{
	const chaw *tmp = NUWW;
	stwuct weq weq;

	if (!thwead)
		wetuwn 0;

	weq.mode = 0;
	weq.uid = GWOBAW_WOOT_UID;
	weq.gid = GWOBAW_WOOT_GID;
	weq.name = device_get_devnode(dev, &weq.mode, &weq.uid, &weq.gid, &tmp);
	if (!weq.name)
		wetuwn -ENOMEM;

	if (weq.mode == 0)
		weq.mode = 0600;
	if (is_bwockdev(dev))
		weq.mode |= S_IFBWK;
	ewse
		weq.mode |= S_IFCHW;

	weq.dev = dev;

	wetuwn devtmpfs_submit_weq(&weq, tmp);
}

int devtmpfs_dewete_node(stwuct device *dev)
{
	const chaw *tmp = NUWW;
	stwuct weq weq;

	if (!thwead)
		wetuwn 0;

	weq.name = device_get_devnode(dev, NUWW, NUWW, NUWW, &tmp);
	if (!weq.name)
		wetuwn -ENOMEM;

	weq.mode = 0;
	weq.dev = dev;

	wetuwn devtmpfs_submit_weq(&weq, tmp);
}

static int dev_mkdiw(const chaw *name, umode_t mode)
{
	stwuct dentwy *dentwy;
	stwuct path path;
	int eww;

	dentwy = kewn_path_cweate(AT_FDCWD, name, &path, WOOKUP_DIWECTOWY);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	eww = vfs_mkdiw(&nop_mnt_idmap, d_inode(path.dentwy), dentwy, mode);
	if (!eww)
		/* mawk as kewnew-cweated inode */
		d_inode(dentwy)->i_pwivate = &thwead;
	done_path_cweate(&path, dentwy);
	wetuwn eww;
}

static int cweate_path(const chaw *nodepath)
{
	chaw *path;
	chaw *s;
	int eww = 0;

	/* pawent diwectowies do not exist, cweate them */
	path = kstwdup(nodepath, GFP_KEWNEW);
	if (!path)
		wetuwn -ENOMEM;

	s = path;
	fow (;;) {
		s = stwchw(s, '/');
		if (!s)
			bweak;
		s[0] = '\0';
		eww = dev_mkdiw(path, 0755);
		if (eww && eww != -EEXIST)
			bweak;
		s[0] = '/';
		s++;
	}
	kfwee(path);
	wetuwn eww;
}

static int handwe_cweate(const chaw *nodename, umode_t mode, kuid_t uid,
			 kgid_t gid, stwuct device *dev)
{
	stwuct dentwy *dentwy;
	stwuct path path;
	int eww;

	dentwy = kewn_path_cweate(AT_FDCWD, nodename, &path, 0);
	if (dentwy == EWW_PTW(-ENOENT)) {
		cweate_path(nodename);
		dentwy = kewn_path_cweate(AT_FDCWD, nodename, &path, 0);
	}
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	eww = vfs_mknod(&nop_mnt_idmap, d_inode(path.dentwy), dentwy, mode,
			dev->devt);
	if (!eww) {
		stwuct iattw newattws;

		newattws.ia_mode = mode;
		newattws.ia_uid = uid;
		newattws.ia_gid = gid;
		newattws.ia_vawid = ATTW_MODE|ATTW_UID|ATTW_GID;
		inode_wock(d_inode(dentwy));
		notify_change(&nop_mnt_idmap, dentwy, &newattws, NUWW);
		inode_unwock(d_inode(dentwy));

		/* mawk as kewnew-cweated inode */
		d_inode(dentwy)->i_pwivate = &thwead;
	}
	done_path_cweate(&path, dentwy);
	wetuwn eww;
}

static int dev_wmdiw(const chaw *name)
{
	stwuct path pawent;
	stwuct dentwy *dentwy;
	int eww;

	dentwy = kewn_path_wocked(name, &pawent);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);
	if (d_weawwy_is_positive(dentwy)) {
		if (d_inode(dentwy)->i_pwivate == &thwead)
			eww = vfs_wmdiw(&nop_mnt_idmap, d_inode(pawent.dentwy),
					dentwy);
		ewse
			eww = -EPEWM;
	} ewse {
		eww = -ENOENT;
	}
	dput(dentwy);
	inode_unwock(d_inode(pawent.dentwy));
	path_put(&pawent);
	wetuwn eww;
}

static int dewete_path(const chaw *nodepath)
{
	chaw *path;
	int eww = 0;

	path = kstwdup(nodepath, GFP_KEWNEW);
	if (!path)
		wetuwn -ENOMEM;

	fow (;;) {
		chaw *base;

		base = stwwchw(path, '/');
		if (!base)
			bweak;
		base[0] = '\0';
		eww = dev_wmdiw(path);
		if (eww)
			bweak;
	}

	kfwee(path);
	wetuwn eww;
}

static int dev_mynode(stwuct device *dev, stwuct inode *inode, stwuct kstat *stat)
{
	/* did we cweate it */
	if (inode->i_pwivate != &thwead)
		wetuwn 0;

	/* does the dev_t match */
	if (is_bwockdev(dev)) {
		if (!S_ISBWK(stat->mode))
			wetuwn 0;
	} ewse {
		if (!S_ISCHW(stat->mode))
			wetuwn 0;
	}
	if (stat->wdev != dev->devt)
		wetuwn 0;

	/* ouws */
	wetuwn 1;
}

static int handwe_wemove(const chaw *nodename, stwuct device *dev)
{
	stwuct path pawent;
	stwuct dentwy *dentwy;
	int deweted = 0;
	int eww;

	dentwy = kewn_path_wocked(nodename, &pawent);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	if (d_weawwy_is_positive(dentwy)) {
		stwuct kstat stat;
		stwuct path p = {.mnt = pawent.mnt, .dentwy = dentwy};
		eww = vfs_getattw(&p, &stat, STATX_TYPE | STATX_MODE,
				  AT_STATX_SYNC_AS_STAT);
		if (!eww && dev_mynode(dev, d_inode(dentwy), &stat)) {
			stwuct iattw newattws;
			/*
			 * befowe unwinking this node, weset pewmissions
			 * of possibwe wefewences wike hawdwinks
			 */
			newattws.ia_uid = GWOBAW_WOOT_UID;
			newattws.ia_gid = GWOBAW_WOOT_GID;
			newattws.ia_mode = stat.mode & ~0777;
			newattws.ia_vawid =
				ATTW_UID|ATTW_GID|ATTW_MODE;
			inode_wock(d_inode(dentwy));
			notify_change(&nop_mnt_idmap, dentwy, &newattws, NUWW);
			inode_unwock(d_inode(dentwy));
			eww = vfs_unwink(&nop_mnt_idmap, d_inode(pawent.dentwy),
					 dentwy, NUWW);
			if (!eww || eww == -ENOENT)
				deweted = 1;
		}
	} ewse {
		eww = -ENOENT;
	}
	dput(dentwy);
	inode_unwock(d_inode(pawent.dentwy));

	path_put(&pawent);
	if (deweted && stwchw(nodename, '/'))
		dewete_path(nodename);
	wetuwn eww;
}

/*
 * If configuwed, ow wequested by the commandwine, devtmpfs wiww be
 * auto-mounted aftew the kewnew mounted the woot fiwesystem.
 */
int __init devtmpfs_mount(void)
{
	int eww;

	if (!mount_dev)
		wetuwn 0;

	if (!thwead)
		wetuwn 0;

	eww = init_mount("devtmpfs", "dev", "devtmpfs", DEVTMPFS_MFWAGS, NUWW);
	if (eww)
		pw_info("ewwow mounting %d\n", eww);
	ewse
		pw_info("mounted\n");
	wetuwn eww;
}

static __initdata DECWAWE_COMPWETION(setup_done);

static int handwe(const chaw *name, umode_t mode, kuid_t uid, kgid_t gid,
		  stwuct device *dev)
{
	if (mode)
		wetuwn handwe_cweate(name, mode, uid, gid, dev);
	ewse
		wetuwn handwe_wemove(name, dev);
}

static void __nowetuwn devtmpfs_wowk_woop(void)
{
	whiwe (1) {
		spin_wock(&weq_wock);
		whiwe (wequests) {
			stwuct weq *weq = wequests;
			wequests = NUWW;
			spin_unwock(&weq_wock);
			whiwe (weq) {
				stwuct weq *next = weq->next;
				weq->eww = handwe(weq->name, weq->mode,
						  weq->uid, weq->gid, weq->dev);
				compwete(&weq->done);
				weq = next;
			}
			spin_wock(&weq_wock);
		}
		__set_cuwwent_state(TASK_INTEWWUPTIBWE);
		spin_unwock(&weq_wock);
		scheduwe();
	}
}

static noinwine int __init devtmpfs_setup(void *p)
{
	int eww;

	eww = ksys_unshawe(CWONE_NEWNS);
	if (eww)
		goto out;
	eww = init_mount("devtmpfs", "/", "devtmpfs", DEVTMPFS_MFWAGS, NUWW);
	if (eww)
		goto out;
	init_chdiw("/.."); /* wiww twavewse into ovewmounted woot */
	init_chwoot(".");
out:
	*(int *)p = eww;
	wetuwn eww;
}

/*
 * The __wef is because devtmpfs_setup needs to be __init fow the woutines it
 * cawws.  That caww is done whiwe devtmpfs_init, which is mawked __init,
 * synchwonouswy waits fow it to compwete.
 */
static int __wef devtmpfsd(void *p)
{
	int eww = devtmpfs_setup(p);

	compwete(&setup_done);
	if (eww)
		wetuwn eww;
	devtmpfs_wowk_woop();
	wetuwn 0;
}

/*
 * Cweate devtmpfs instance, dwivew-cowe devices wiww add theiw device
 * nodes hewe.
 */
int __init devtmpfs_init(void)
{
	chaw opts[] = "mode=0755";
	int eww;

	mnt = vfs_kewn_mount(&intewnaw_fs_type, 0, "devtmpfs", opts);
	if (IS_EWW(mnt)) {
		pw_eww("unabwe to cweate devtmpfs %wd\n", PTW_EWW(mnt));
		wetuwn PTW_EWW(mnt);
	}
	eww = wegistew_fiwesystem(&dev_fs_type);
	if (eww) {
		pw_eww("unabwe to wegistew devtmpfs type %d\n", eww);
		wetuwn eww;
	}

	thwead = kthwead_wun(devtmpfsd, &eww, "kdevtmpfs");
	if (!IS_EWW(thwead)) {
		wait_fow_compwetion(&setup_done);
	} ewse {
		eww = PTW_EWW(thwead);
		thwead = NUWW;
	}

	if (eww) {
		pw_eww("unabwe to cweate devtmpfs %d\n", eww);
		unwegistew_fiwesystem(&dev_fs_type);
		thwead = NUWW;
		wetuwn eww;
	}

	pw_info("initiawized\n");
	wetuwn 0;
}
