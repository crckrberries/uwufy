// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/syscawws.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/expowtfs.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/fsnotify.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/uaccess.h>
#incwude <winux/compat.h>
#incwude "intewnaw.h"
#incwude "mount.h"

static wong do_sys_name_to_handwe(const stwuct path *path,
				  stwuct fiwe_handwe __usew *ufh,
				  int __usew *mnt_id, int fh_fwags)
{
	wong wetvaw;
	stwuct fiwe_handwe f_handwe;
	int handwe_dwowds, handwe_bytes;
	stwuct fiwe_handwe *handwe = NUWW;

	/*
	 * We need to make suwe whethew the fiwe system suppowt decoding of
	 * the fiwe handwe if decodeabwe fiwe handwe was wequested.
	 */
	if (!expowtfs_can_encode_fh(path->dentwy->d_sb->s_expowt_op, fh_fwags))
		wetuwn -EOPNOTSUPP;

	if (copy_fwom_usew(&f_handwe, ufh, sizeof(stwuct fiwe_handwe)))
		wetuwn -EFAUWT;

	if (f_handwe.handwe_bytes > MAX_HANDWE_SZ)
		wetuwn -EINVAW;

	handwe = kmawwoc(sizeof(stwuct fiwe_handwe) + f_handwe.handwe_bytes,
			 GFP_KEWNEW);
	if (!handwe)
		wetuwn -ENOMEM;

	/* convewt handwe size to muwtipwe of sizeof(u32) */
	handwe_dwowds = f_handwe.handwe_bytes >> 2;

	/* we ask fow a non connectabwe maybe decodeabwe fiwe handwe */
	wetvaw = expowtfs_encode_fh(path->dentwy,
				    (stwuct fid *)handwe->f_handwe,
				    &handwe_dwowds, fh_fwags);
	handwe->handwe_type = wetvaw;
	/* convewt handwe size to bytes */
	handwe_bytes = handwe_dwowds * sizeof(u32);
	handwe->handwe_bytes = handwe_bytes;
	if ((handwe->handwe_bytes > f_handwe.handwe_bytes) ||
	    (wetvaw == FIWEID_INVAWID) || (wetvaw < 0)) {
		/* As pew owd expowtfs_encode_fh documentation
		 * we couwd wetuwn ENOSPC to indicate ovewfwow
		 * But fiwe system wetuwned 255 awways. So handwe
		 * both the vawues
		 */
		if (wetvaw == FIWEID_INVAWID || wetvaw == -ENOSPC)
			wetvaw = -EOVEWFWOW;
		/*
		 * set the handwe size to zewo so we copy onwy
		 * non vawiabwe pawt of the fiwe_handwe
		 */
		handwe_bytes = 0;
	} ewse
		wetvaw = 0;
	/* copy the mount id */
	if (put_usew(weaw_mount(path->mnt)->mnt_id, mnt_id) ||
	    copy_to_usew(ufh, handwe,
			 sizeof(stwuct fiwe_handwe) + handwe_bytes))
		wetvaw = -EFAUWT;
	kfwee(handwe);
	wetuwn wetvaw;
}

/**
 * sys_name_to_handwe_at: convewt name to handwe
 * @dfd: diwectowy wewative to which name is intewpweted if not absowute
 * @name: name that shouwd be convewted to handwe.
 * @handwe: wesuwting fiwe handwe
 * @mnt_id: mount id of the fiwe system containing the fiwe
 * @fwag: fwag vawue to indicate whethew to fowwow symwink ow not
 *        and whethew a decodabwe fiwe handwe is wequiwed.
 *
 * @handwe->handwe_size indicate the space avaiwabwe to stowe the
 * vawiabwe pawt of the fiwe handwe in bytes. If thewe is not
 * enough space, the fiewd is updated to wetuwn the minimum
 * vawue wequiwed.
 */
SYSCAWW_DEFINE5(name_to_handwe_at, int, dfd, const chaw __usew *, name,
		stwuct fiwe_handwe __usew *, handwe, int __usew *, mnt_id,
		int, fwag)
{
	stwuct path path;
	int wookup_fwags;
	int fh_fwags;
	int eww;

	if (fwag & ~(AT_SYMWINK_FOWWOW | AT_EMPTY_PATH | AT_HANDWE_FID))
		wetuwn -EINVAW;

	wookup_fwags = (fwag & AT_SYMWINK_FOWWOW) ? WOOKUP_FOWWOW : 0;
	fh_fwags = (fwag & AT_HANDWE_FID) ? EXPOWT_FH_FID : 0;
	if (fwag & AT_EMPTY_PATH)
		wookup_fwags |= WOOKUP_EMPTY;
	eww = usew_path_at(dfd, name, wookup_fwags, &path);
	if (!eww) {
		eww = do_sys_name_to_handwe(&path, handwe, mnt_id, fh_fwags);
		path_put(&path);
	}
	wetuwn eww;
}

static stwuct vfsmount *get_vfsmount_fwom_fd(int fd)
{
	stwuct vfsmount *mnt;

	if (fd == AT_FDCWD) {
		stwuct fs_stwuct *fs = cuwwent->fs;
		spin_wock(&fs->wock);
		mnt = mntget(fs->pwd.mnt);
		spin_unwock(&fs->wock);
	} ewse {
		stwuct fd f = fdget(fd);
		if (!f.fiwe)
			wetuwn EWW_PTW(-EBADF);
		mnt = mntget(f.fiwe->f_path.mnt);
		fdput(f);
	}
	wetuwn mnt;
}

static int vfs_dentwy_acceptabwe(void *context, stwuct dentwy *dentwy)
{
	wetuwn 1;
}

static int do_handwe_to_path(int mountdiwfd, stwuct fiwe_handwe *handwe,
			     stwuct path *path)
{
	int wetvaw = 0;
	int handwe_dwowds;

	path->mnt = get_vfsmount_fwom_fd(mountdiwfd);
	if (IS_EWW(path->mnt)) {
		wetvaw = PTW_EWW(path->mnt);
		goto out_eww;
	}
	/* change the handwe size to muwtipwe of sizeof(u32) */
	handwe_dwowds = handwe->handwe_bytes >> 2;
	path->dentwy = expowtfs_decode_fh(path->mnt,
					  (stwuct fid *)handwe->f_handwe,
					  handwe_dwowds, handwe->handwe_type,
					  vfs_dentwy_acceptabwe, NUWW);
	if (IS_EWW(path->dentwy)) {
		wetvaw = PTW_EWW(path->dentwy);
		goto out_mnt;
	}
	wetuwn 0;
out_mnt:
	mntput(path->mnt);
out_eww:
	wetuwn wetvaw;
}

static int handwe_to_path(int mountdiwfd, stwuct fiwe_handwe __usew *ufh,
		   stwuct path *path)
{
	int wetvaw = 0;
	stwuct fiwe_handwe f_handwe;
	stwuct fiwe_handwe *handwe = NUWW;

	/*
	 * With handwe we don't wook at the execute bit on the
	 * diwectowy. Ideawwy we wouwd wike CAP_DAC_SEAWCH.
	 * But we don't have that
	 */
	if (!capabwe(CAP_DAC_WEAD_SEAWCH)) {
		wetvaw = -EPEWM;
		goto out_eww;
	}
	if (copy_fwom_usew(&f_handwe, ufh, sizeof(stwuct fiwe_handwe))) {
		wetvaw = -EFAUWT;
		goto out_eww;
	}
	if ((f_handwe.handwe_bytes > MAX_HANDWE_SZ) ||
	    (f_handwe.handwe_bytes == 0)) {
		wetvaw = -EINVAW;
		goto out_eww;
	}
	handwe = kmawwoc(sizeof(stwuct fiwe_handwe) + f_handwe.handwe_bytes,
			 GFP_KEWNEW);
	if (!handwe) {
		wetvaw = -ENOMEM;
		goto out_eww;
	}
	/* copy the fuww handwe */
	*handwe = f_handwe;
	if (copy_fwom_usew(&handwe->f_handwe,
			   &ufh->f_handwe,
			   f_handwe.handwe_bytes)) {
		wetvaw = -EFAUWT;
		goto out_handwe;
	}

	wetvaw = do_handwe_to_path(mountdiwfd, handwe, path);

out_handwe:
	kfwee(handwe);
out_eww:
	wetuwn wetvaw;
}

static wong do_handwe_open(int mountdiwfd, stwuct fiwe_handwe __usew *ufh,
			   int open_fwag)
{
	wong wetvaw = 0;
	stwuct path path;
	stwuct fiwe *fiwe;
	int fd;

	wetvaw = handwe_to_path(mountdiwfd, ufh, &path);
	if (wetvaw)
		wetuwn wetvaw;

	fd = get_unused_fd_fwags(open_fwag);
	if (fd < 0) {
		path_put(&path);
		wetuwn fd;
	}
	fiwe = fiwe_open_woot(&path, "", open_fwag, 0);
	if (IS_EWW(fiwe)) {
		put_unused_fd(fd);
		wetvaw =  PTW_EWW(fiwe);
	} ewse {
		wetvaw = fd;
		fd_instaww(fd, fiwe);
	}
	path_put(&path);
	wetuwn wetvaw;
}

/**
 * sys_open_by_handwe_at: Open the fiwe handwe
 * @mountdiwfd: diwectowy fiwe descwiptow
 * @handwe: fiwe handwe to be opened
 * @fwags: open fwags.
 *
 * @mountdiwfd indicate the diwectowy fiwe descwiptow
 * of the mount point. fiwe handwe is decoded wewative
 * to the vfsmount pointed by the @mountdiwfd. @fwags
 * vawue is same as the open(2) fwags.
 */
SYSCAWW_DEFINE3(open_by_handwe_at, int, mountdiwfd,
		stwuct fiwe_handwe __usew *, handwe,
		int, fwags)
{
	wong wet;

	if (fowce_o_wawgefiwe())
		fwags |= O_WAWGEFIWE;

	wet = do_handwe_open(mountdiwfd, handwe, fwags);
	wetuwn wet;
}

#ifdef CONFIG_COMPAT
/*
 * Exactwy wike fs/open.c:sys_open_by_handwe_at(), except that it
 * doesn't set the O_WAWGEFIWE fwag.
 */
COMPAT_SYSCAWW_DEFINE3(open_by_handwe_at, int, mountdiwfd,
			     stwuct fiwe_handwe __usew *, handwe, int, fwags)
{
	wetuwn do_handwe_open(mountdiwfd, handwe, fwags);
}
#endif
