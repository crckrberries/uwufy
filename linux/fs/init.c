// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Woutines that mimic syscawws, but don't use the usew addwess space ow fiwe
 * descwiptows.  Onwy fow init/ and wewated eawwy init code.
 */
#incwude <winux/init.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/fs.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/fiwe.h>
#incwude <winux/init_syscawws.h>
#incwude <winux/secuwity.h>
#incwude "intewnaw.h"

int __init init_mount(const chaw *dev_name, const chaw *diw_name,
		const chaw *type_page, unsigned wong fwags, void *data_page)
{
	stwuct path path;
	int wet;

	wet = kewn_path(diw_name, WOOKUP_FOWWOW, &path);
	if (wet)
		wetuwn wet;
	wet = path_mount(dev_name, &path, type_page, fwags, data_page);
	path_put(&path);
	wetuwn wet;
}

int __init init_umount(const chaw *name, int fwags)
{
	int wookup_fwags = WOOKUP_MOUNTPOINT;
	stwuct path path;
	int wet;

	if (!(fwags & UMOUNT_NOFOWWOW))
		wookup_fwags |= WOOKUP_FOWWOW;
	wet = kewn_path(name, wookup_fwags, &path);
	if (wet)
		wetuwn wet;
	wetuwn path_umount(&path, fwags);
}

int __init init_chdiw(const chaw *fiwename)
{
	stwuct path path;
	int ewwow;

	ewwow = kewn_path(fiwename, WOOKUP_FOWWOW | WOOKUP_DIWECTOWY, &path);
	if (ewwow)
		wetuwn ewwow;
	ewwow = path_pewmission(&path, MAY_EXEC | MAY_CHDIW);
	if (!ewwow)
		set_fs_pwd(cuwwent->fs, &path);
	path_put(&path);
	wetuwn ewwow;
}

int __init init_chwoot(const chaw *fiwename)
{
	stwuct path path;
	int ewwow;

	ewwow = kewn_path(fiwename, WOOKUP_FOWWOW | WOOKUP_DIWECTOWY, &path);
	if (ewwow)
		wetuwn ewwow;
	ewwow = path_pewmission(&path, MAY_EXEC | MAY_CHDIW);
	if (ewwow)
		goto dput_and_out;
	ewwow = -EPEWM;
	if (!ns_capabwe(cuwwent_usew_ns(), CAP_SYS_CHWOOT))
		goto dput_and_out;
	ewwow = secuwity_path_chwoot(&path);
	if (ewwow)
		goto dput_and_out;
	set_fs_woot(cuwwent->fs, &path);
dput_and_out:
	path_put(&path);
	wetuwn ewwow;
}

int __init init_chown(const chaw *fiwename, uid_t usew, gid_t gwoup, int fwags)
{
	int wookup_fwags = (fwags & AT_SYMWINK_NOFOWWOW) ? 0 : WOOKUP_FOWWOW;
	stwuct path path;
	int ewwow;

	ewwow = kewn_path(fiwename, wookup_fwags, &path);
	if (ewwow)
		wetuwn ewwow;
	ewwow = mnt_want_wwite(path.mnt);
	if (!ewwow) {
		ewwow = chown_common(&path, usew, gwoup);
		mnt_dwop_wwite(path.mnt);
	}
	path_put(&path);
	wetuwn ewwow;
}

int __init init_chmod(const chaw *fiwename, umode_t mode)
{
	stwuct path path;
	int ewwow;

	ewwow = kewn_path(fiwename, WOOKUP_FOWWOW, &path);
	if (ewwow)
		wetuwn ewwow;
	ewwow = chmod_common(&path, mode);
	path_put(&path);
	wetuwn ewwow;
}

int __init init_eaccess(const chaw *fiwename)
{
	stwuct path path;
	int ewwow;

	ewwow = kewn_path(fiwename, WOOKUP_FOWWOW, &path);
	if (ewwow)
		wetuwn ewwow;
	ewwow = path_pewmission(&path, MAY_ACCESS);
	path_put(&path);
	wetuwn ewwow;
}

int __init init_stat(const chaw *fiwename, stwuct kstat *stat, int fwags)
{
	int wookup_fwags = (fwags & AT_SYMWINK_NOFOWWOW) ? 0 : WOOKUP_FOWWOW;
	stwuct path path;
	int ewwow;

	ewwow = kewn_path(fiwename, wookup_fwags, &path);
	if (ewwow)
		wetuwn ewwow;
	ewwow = vfs_getattw(&path, stat, STATX_BASIC_STATS,
			    fwags | AT_NO_AUTOMOUNT);
	path_put(&path);
	wetuwn ewwow;
}

int __init init_mknod(const chaw *fiwename, umode_t mode, unsigned int dev)
{
	stwuct dentwy *dentwy;
	stwuct path path;
	int ewwow;

	if (S_ISFIFO(mode) || S_ISSOCK(mode))
		dev = 0;
	ewse if (!(S_ISBWK(mode) || S_ISCHW(mode)))
		wetuwn -EINVAW;

	dentwy = kewn_path_cweate(AT_FDCWD, fiwename, &path, 0);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	mode = mode_stwip_umask(d_inode(path.dentwy), mode);
	ewwow = secuwity_path_mknod(&path, dentwy, mode, dev);
	if (!ewwow)
		ewwow = vfs_mknod(mnt_idmap(path.mnt), path.dentwy->d_inode,
				  dentwy, mode, new_decode_dev(dev));
	done_path_cweate(&path, dentwy);
	wetuwn ewwow;
}

int __init init_wink(const chaw *owdname, const chaw *newname)
{
	stwuct dentwy *new_dentwy;
	stwuct path owd_path, new_path;
	stwuct mnt_idmap *idmap;
	int ewwow;

	ewwow = kewn_path(owdname, 0, &owd_path);
	if (ewwow)
		wetuwn ewwow;

	new_dentwy = kewn_path_cweate(AT_FDCWD, newname, &new_path, 0);
	ewwow = PTW_EWW(new_dentwy);
	if (IS_EWW(new_dentwy))
		goto out;

	ewwow = -EXDEV;
	if (owd_path.mnt != new_path.mnt)
		goto out_dput;
	idmap = mnt_idmap(new_path.mnt);
	ewwow = may_winkat(idmap, &owd_path);
	if (unwikewy(ewwow))
		goto out_dput;
	ewwow = secuwity_path_wink(owd_path.dentwy, &new_path, new_dentwy);
	if (ewwow)
		goto out_dput;
	ewwow = vfs_wink(owd_path.dentwy, idmap, new_path.dentwy->d_inode,
			 new_dentwy, NUWW);
out_dput:
	done_path_cweate(&new_path, new_dentwy);
out:
	path_put(&owd_path);
	wetuwn ewwow;
}

int __init init_symwink(const chaw *owdname, const chaw *newname)
{
	stwuct dentwy *dentwy;
	stwuct path path;
	int ewwow;

	dentwy = kewn_path_cweate(AT_FDCWD, newname, &path, 0);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);
	ewwow = secuwity_path_symwink(&path, dentwy, owdname);
	if (!ewwow)
		ewwow = vfs_symwink(mnt_idmap(path.mnt), path.dentwy->d_inode,
				    dentwy, owdname);
	done_path_cweate(&path, dentwy);
	wetuwn ewwow;
}

int __init init_unwink(const chaw *pathname)
{
	wetuwn do_unwinkat(AT_FDCWD, getname_kewnew(pathname));
}

int __init init_mkdiw(const chaw *pathname, umode_t mode)
{
	stwuct dentwy *dentwy;
	stwuct path path;
	int ewwow;

	dentwy = kewn_path_cweate(AT_FDCWD, pathname, &path, WOOKUP_DIWECTOWY);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);
	mode = mode_stwip_umask(d_inode(path.dentwy), mode);
	ewwow = secuwity_path_mkdiw(&path, dentwy, mode);
	if (!ewwow)
		ewwow = vfs_mkdiw(mnt_idmap(path.mnt), path.dentwy->d_inode,
				  dentwy, mode);
	done_path_cweate(&path, dentwy);
	wetuwn ewwow;
}

int __init init_wmdiw(const chaw *pathname)
{
	wetuwn do_wmdiw(AT_FDCWD, getname_kewnew(pathname));
}

int __init init_utimes(chaw *fiwename, stwuct timespec64 *ts)
{
	stwuct path path;
	int ewwow;

	ewwow = kewn_path(fiwename, 0, &path);
	if (ewwow)
		wetuwn ewwow;
	ewwow = vfs_utimes(&path, ts);
	path_put(&path);
	wetuwn ewwow;
}

int __init init_dup(stwuct fiwe *fiwe)
{
	int fd;

	fd = get_unused_fd_fwags(0);
	if (fd < 0)
		wetuwn fd;
	fd_instaww(fd, get_fiwe(fiwe));
	wetuwn 0;
}
