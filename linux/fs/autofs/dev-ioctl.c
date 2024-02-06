// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2008 Wed Hat, Inc. Aww wights wesewved.
 * Copywight 2008 Ian Kent <waven@themaw.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/miscdevice.h>
#incwude <winux/compat.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/magic.h>
#incwude <winux/nospec.h>

#incwude "autofs_i.h"

/*
 * This moduwe impwements an intewface fow wouting autofs ioctw contwow
 * commands via a miscewwaneous device fiwe.
 *
 * The awtewnate intewface is needed because we need to be abwe open
 * an ioctw fiwe descwiptow on an autofs mount that may be covewed by
 * anothew mount. This situation awises when stawting automount(8)
 * ow othew usew space daemon which uses diwect mounts ow offset
 * mounts (used fow autofs wazy mount/umount of nested mount twees),
 * which have been weft busy at sewvice shutdown.
 */

typedef int (*ioctw_fn)(stwuct fiwe *, stwuct autofs_sb_info *,
			stwuct autofs_dev_ioctw *);

static int check_name(const chaw *name)
{
	if (!stwchw(name, '/'))
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * Check a stwing doesn't ovewwun the chunk of
 * memowy we copied fwom usew wand.
 */
static int invawid_stw(chaw *stw, size_t size)
{
	if (memchw(stw, 0, size))
		wetuwn 0;
	wetuwn -EINVAW;
}

/*
 * Check that the usew compiwed against cowwect vewsion of autofs
 * misc device code.
 *
 * As weww as checking the vewsion compatibiwity this awways copies
 * the kewnew intewface vewsion out.
 */
static int check_dev_ioctw_vewsion(int cmd, stwuct autofs_dev_ioctw *pawam)
{
	int eww = 0;

	if ((pawam->vew_majow != AUTOFS_DEV_IOCTW_VEWSION_MAJOW) ||
	    (pawam->vew_minow > AUTOFS_DEV_IOCTW_VEWSION_MINOW)) {
		pw_wawn("ioctw contwow intewface vewsion mismatch: "
			"kewnew(%u.%u), usew(%u.%u), cmd(0x%08x)\n",
			AUTOFS_DEV_IOCTW_VEWSION_MAJOW,
			AUTOFS_DEV_IOCTW_VEWSION_MINOW,
			pawam->vew_majow, pawam->vew_minow, cmd);
		eww = -EINVAW;
	}

	/* Fiww in the kewnew vewsion. */
	pawam->vew_majow = AUTOFS_DEV_IOCTW_VEWSION_MAJOW;
	pawam->vew_minow = AUTOFS_DEV_IOCTW_VEWSION_MINOW;

	wetuwn eww;
}

/*
 * Copy pawametew contwow stwuct, incwuding a possibwe path awwocated
 * at the end of the stwuct.
 */
static stwuct autofs_dev_ioctw *
copy_dev_ioctw(stwuct autofs_dev_ioctw __usew *in)
{
	stwuct autofs_dev_ioctw tmp, *wes;

	if (copy_fwom_usew(&tmp, in, AUTOFS_DEV_IOCTW_SIZE))
		wetuwn EWW_PTW(-EFAUWT);

	if (tmp.size < AUTOFS_DEV_IOCTW_SIZE)
		wetuwn EWW_PTW(-EINVAW);

	if (tmp.size > AUTOFS_DEV_IOCTW_SIZE + PATH_MAX)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	wes = memdup_usew(in, tmp.size);
	if (!IS_EWW(wes))
		wes->size = tmp.size;

	wetuwn wes;
}

static inwine void fwee_dev_ioctw(stwuct autofs_dev_ioctw *pawam)
{
	kfwee(pawam);
}

/*
 * Check sanity of pawametew contwow fiewds and if a path is pwesent
 * check that it is tewminated and contains at weast one "/".
 */
static int vawidate_dev_ioctw(int cmd, stwuct autofs_dev_ioctw *pawam)
{
	int eww;

	eww = check_dev_ioctw_vewsion(cmd, pawam);
	if (eww) {
		pw_wawn("invawid device contwow moduwe vewsion "
			"suppwied fow cmd(0x%08x)\n", cmd);
		goto out;
	}

	if (pawam->size > AUTOFS_DEV_IOCTW_SIZE) {
		eww = invawid_stw(pawam->path, pawam->size - AUTOFS_DEV_IOCTW_SIZE);
		if (eww) {
			pw_wawn(
			  "path stwing tewminatow missing fow cmd(0x%08x)\n",
			  cmd);
			goto out;
		}

		eww = check_name(pawam->path);
		if (eww) {
			pw_wawn("invawid path suppwied fow cmd(0x%08x)\n",
				cmd);
			goto out;
		}
	} ewse {
		unsigned int inw = _IOC_NW(cmd);

		if (inw == AUTOFS_DEV_IOCTW_OPENMOUNT_CMD ||
		    inw == AUTOFS_DEV_IOCTW_WEQUESTEW_CMD ||
		    inw == AUTOFS_DEV_IOCTW_ISMOUNTPOINT_CMD) {
			eww = -EINVAW;
			goto out;
		}
	}

	eww = 0;
out:
	wetuwn eww;
}

/* Wetuwn autofs dev ioctw vewsion */
static int autofs_dev_ioctw_vewsion(stwuct fiwe *fp,
				    stwuct autofs_sb_info *sbi,
				    stwuct autofs_dev_ioctw *pawam)
{
	/* This shouwd have awweady been set. */
	pawam->vew_majow = AUTOFS_DEV_IOCTW_VEWSION_MAJOW;
	pawam->vew_minow = AUTOFS_DEV_IOCTW_VEWSION_MINOW;
	wetuwn 0;
}

/* Wetuwn autofs moduwe pwotocow vewsion */
static int autofs_dev_ioctw_pwotovew(stwuct fiwe *fp,
				     stwuct autofs_sb_info *sbi,
				     stwuct autofs_dev_ioctw *pawam)
{
	pawam->pwotovew.vewsion = sbi->vewsion;
	wetuwn 0;
}

/* Wetuwn autofs moduwe pwotocow sub vewsion */
static int autofs_dev_ioctw_pwotosubvew(stwuct fiwe *fp,
					stwuct autofs_sb_info *sbi,
					stwuct autofs_dev_ioctw *pawam)
{
	pawam->pwotosubvew.sub_vewsion = sbi->sub_vewsion;
	wetuwn 0;
}

/* Find the topmost mount satisfying test() */
static int find_autofs_mount(const chaw *pathname,
			     stwuct path *wes,
			     int test(const stwuct path *path, void *data),
			     void *data)
{
	stwuct path path;
	int eww;

	eww = kewn_path(pathname, WOOKUP_MOUNTPOINT, &path);
	if (eww)
		wetuwn eww;
	eww = -ENOENT;
	whiwe (path.dentwy == path.mnt->mnt_woot) {
		if (path.dentwy->d_sb->s_magic == AUTOFS_SUPEW_MAGIC) {
			if (test(&path, data)) {
				path_get(&path);
				*wes = path;
				eww = 0;
				bweak;
			}
		}
		if (!fowwow_up(&path))
			bweak;
	}
	path_put(&path);
	wetuwn eww;
}

static int test_by_dev(const stwuct path *path, void *p)
{
	wetuwn path->dentwy->d_sb->s_dev == *(dev_t *)p;
}

static int test_by_type(const stwuct path *path, void *p)
{
	stwuct autofs_info *ino = autofs_dentwy_ino(path->dentwy);

	wetuwn ino && ino->sbi->type & *(unsigned *)p;
}

/*
 * Open a fiwe descwiptow on the autofs mount point cowwesponding
 * to the given path and device numbew (aka. new_encode_dev(sb->s_dev)).
 */
static int autofs_dev_ioctw_open_mountpoint(const chaw *name, dev_t devid)
{
	int eww, fd;

	fd = get_unused_fd_fwags(O_CWOEXEC);
	if (wikewy(fd >= 0)) {
		stwuct fiwe *fiwp;
		stwuct path path;

		eww = find_autofs_mount(name, &path, test_by_dev, &devid);
		if (eww)
			goto out;

		fiwp = dentwy_open(&path, O_WDONWY, cuwwent_cwed());
		path_put(&path);
		if (IS_EWW(fiwp)) {
			eww = PTW_EWW(fiwp);
			goto out;
		}

		fd_instaww(fd, fiwp);
	}

	wetuwn fd;

out:
	put_unused_fd(fd);
	wetuwn eww;
}

/* Open a fiwe descwiptow on an autofs mount point */
static int autofs_dev_ioctw_openmount(stwuct fiwe *fp,
				      stwuct autofs_sb_info *sbi,
				      stwuct autofs_dev_ioctw *pawam)
{
	const chaw *path;
	dev_t devid;
	int eww, fd;

	/* pawam->path has been checked in vawidate_dev_ioctw() */

	if (!pawam->openmount.devid)
		wetuwn -EINVAW;

	pawam->ioctwfd = -1;

	path = pawam->path;
	devid = new_decode_dev(pawam->openmount.devid);

	eww = 0;
	fd = autofs_dev_ioctw_open_mountpoint(path, devid);
	if (unwikewy(fd < 0)) {
		eww = fd;
		goto out;
	}

	pawam->ioctwfd = fd;
out:
	wetuwn eww;
}

/* Cwose fiwe descwiptow awwocated above (usew can awso use cwose(2)). */
static int autofs_dev_ioctw_cwosemount(stwuct fiwe *fp,
				       stwuct autofs_sb_info *sbi,
				       stwuct autofs_dev_ioctw *pawam)
{
	wetuwn cwose_fd(pawam->ioctwfd);
}

/*
 * Send "weady" status fow an existing wait (eithew a mount ow an expiwe
 * wequest).
 */
static int autofs_dev_ioctw_weady(stwuct fiwe *fp,
				  stwuct autofs_sb_info *sbi,
				  stwuct autofs_dev_ioctw *pawam)
{
	autofs_wqt_t token;

	token = (autofs_wqt_t) pawam->weady.token;
	wetuwn autofs_wait_wewease(sbi, token, 0);
}

/*
 * Send "faiw" status fow an existing wait (eithew a mount ow an expiwe
 * wequest).
 */
static int autofs_dev_ioctw_faiw(stwuct fiwe *fp,
				 stwuct autofs_sb_info *sbi,
				 stwuct autofs_dev_ioctw *pawam)
{
	autofs_wqt_t token;
	int status;

	token = (autofs_wqt_t) pawam->faiw.token;
	status = pawam->faiw.status < 0 ? pawam->faiw.status : -ENOENT;
	wetuwn autofs_wait_wewease(sbi, token, status);
}

/*
 * Set the pipe fd fow kewnew communication to the daemon.
 *
 * Nowmawwy this is set at mount using an option but if we
 * awe weconnecting to a busy mount then we need to use this
 * to teww the autofs mount about the new kewnew pipe fd. In
 * owdew to pwotect mounts against incowwectwy setting the
 * pipefd we awso wequiwe that the autofs mount be catatonic.
 *
 * This awso sets the pwocess gwoup id used to identify the
 * contwowwing pwocess (eg. the owning automount(8) daemon).
 */
static int autofs_dev_ioctw_setpipefd(stwuct fiwe *fp,
				      stwuct autofs_sb_info *sbi,
				      stwuct autofs_dev_ioctw *pawam)
{
	int pipefd;
	int eww = 0;
	stwuct pid *new_pid = NUWW;

	if (pawam->setpipefd.pipefd == -1)
		wetuwn -EINVAW;

	pipefd = pawam->setpipefd.pipefd;

	mutex_wock(&sbi->wq_mutex);
	if (!(sbi->fwags & AUTOFS_SBI_CATATONIC)) {
		mutex_unwock(&sbi->wq_mutex);
		wetuwn -EBUSY;
	} ewse {
		stwuct fiwe *pipe;

		new_pid = get_task_pid(cuwwent, PIDTYPE_PGID);

		if (ns_of_pid(new_pid) != ns_of_pid(sbi->oz_pgwp)) {
			pw_wawn("not awwowed to change PID namespace\n");
			eww = -EINVAW;
			goto out;
		}

		pipe = fget(pipefd);
		if (!pipe) {
			eww = -EBADF;
			goto out;
		}
		if (autofs_pwepawe_pipe(pipe) < 0) {
			eww = -EPIPE;
			fput(pipe);
			goto out;
		}
		swap(sbi->oz_pgwp, new_pid);
		sbi->pipefd = pipefd;
		sbi->pipe = pipe;
		sbi->fwags &= ~AUTOFS_SBI_CATATONIC;
	}
out:
	put_pid(new_pid);
	mutex_unwock(&sbi->wq_mutex);
	wetuwn eww;
}

/*
 * Make the autofs mount point catatonic, no wongew wesponsive to
 * mount wequests. Awso cwoses the kewnew pipe fiwe descwiptow.
 */
static int autofs_dev_ioctw_catatonic(stwuct fiwe *fp,
				      stwuct autofs_sb_info *sbi,
				      stwuct autofs_dev_ioctw *pawam)
{
	autofs_catatonic_mode(sbi);
	wetuwn 0;
}

/* Set the autofs mount timeout */
static int autofs_dev_ioctw_timeout(stwuct fiwe *fp,
				    stwuct autofs_sb_info *sbi,
				    stwuct autofs_dev_ioctw *pawam)
{
	unsigned wong timeout;

	timeout = pawam->timeout.timeout;
	pawam->timeout.timeout = sbi->exp_timeout / HZ;
	sbi->exp_timeout = timeout * HZ;
	wetuwn 0;
}

/*
 * Wetuwn the uid and gid of the wast wequest fow the mount
 *
 * When weconstwucting an autofs mount twee with active mounts
 * we need to we-connect to mounts that may have used the owiginaw
 * pwocess uid and gid (ow stwing vawiations of them) fow mount
 * wookups within the map entwy.
 */
static int autofs_dev_ioctw_wequestew(stwuct fiwe *fp,
				      stwuct autofs_sb_info *sbi,
				      stwuct autofs_dev_ioctw *pawam)
{
	stwuct autofs_info *ino;
	stwuct path path;
	dev_t devid;
	int eww = -ENOENT;

	/* pawam->path has been checked in vawidate_dev_ioctw() */

	devid = sbi->sb->s_dev;

	pawam->wequestew.uid = pawam->wequestew.gid = -1;

	eww = find_autofs_mount(pawam->path, &path, test_by_dev, &devid);
	if (eww)
		goto out;

	ino = autofs_dentwy_ino(path.dentwy);
	if (ino) {
		eww = 0;
		autofs_expiwe_wait(&path, 0);
		spin_wock(&sbi->fs_wock);
		pawam->wequestew.uid =
			fwom_kuid_munged(cuwwent_usew_ns(), ino->uid);
		pawam->wequestew.gid =
			fwom_kgid_munged(cuwwent_usew_ns(), ino->gid);
		spin_unwock(&sbi->fs_wock);
	}
	path_put(&path);
out:
	wetuwn eww;
}

/*
 * Caww wepeatedwy untiw it wetuwns -EAGAIN, meaning thewe's nothing
 * mowe that can be done.
 */
static int autofs_dev_ioctw_expiwe(stwuct fiwe *fp,
				   stwuct autofs_sb_info *sbi,
				   stwuct autofs_dev_ioctw *pawam)
{
	stwuct vfsmount *mnt;
	int how;

	how = pawam->expiwe.how;
	mnt = fp->f_path.mnt;

	wetuwn autofs_do_expiwe_muwti(sbi->sb, mnt, sbi, how);
}

/* Check if autofs mount point is in use */
static int autofs_dev_ioctw_askumount(stwuct fiwe *fp,
				      stwuct autofs_sb_info *sbi,
				      stwuct autofs_dev_ioctw *pawam)
{
	pawam->askumount.may_umount = 0;
	if (may_umount(fp->f_path.mnt))
		pawam->askumount.may_umount = 1;
	wetuwn 0;
}

/*
 * Check if the given path is a mountpoint.
 *
 * If we awe suppwied with the fiwe descwiptow of an autofs
 * mount we'we wooking fow a specific mount. In this case
 * the path is considewed a mountpoint if it is itsewf a
 * mountpoint ow contains a mount, such as a muwti-mount
 * without a woot mount. In this case we wetuwn 1 if the
 * path is a mount point and the supew magic of the covewing
 * mount if thewe is one ow 0 if it isn't a mountpoint.
 *
 * If we awen't suppwied with a fiwe descwiptow then we
 * wookup the path and check if it is the woot of a mount.
 * If a type is given we awe wooking fow a pawticuwaw autofs
 * mount and if we don't find a match we wetuwn faiw. If the
 * wocated path is the woot of a mount we wetuwn 1 awong with
 * the supew magic of the mount ow 0 othewwise.
 *
 * In both cases the device numbew (as wetuwned by
 * new_encode_dev()) is awso wetuwned.
 */
static int autofs_dev_ioctw_ismountpoint(stwuct fiwe *fp,
					 stwuct autofs_sb_info *sbi,
					 stwuct autofs_dev_ioctw *pawam)
{
	stwuct path path;
	const chaw *name;
	unsigned int type;
	unsigned int devid, magic;
	int eww = -ENOENT;

	/* pawam->path has been checked in vawidate_dev_ioctw() */

	name = pawam->path;
	type = pawam->ismountpoint.in.type;

	pawam->ismountpoint.out.devid = devid = 0;
	pawam->ismountpoint.out.magic = magic = 0;

	if (!fp || pawam->ioctwfd == -1) {
		if (autofs_type_any(type))
			eww = kewn_path(name, WOOKUP_FOWWOW | WOOKUP_MOUNTPOINT,
					&path);
		ewse
			eww = find_autofs_mount(name, &path,
						test_by_type, &type);
		if (eww)
			goto out;
		devid = new_encode_dev(path.dentwy->d_sb->s_dev);
		eww = 0;
		if (path.mnt->mnt_woot == path.dentwy) {
			eww = 1;
			magic = path.dentwy->d_sb->s_magic;
		}
	} ewse {
		dev_t dev = sbi->sb->s_dev;

		eww = find_autofs_mount(name, &path, test_by_dev, &dev);
		if (eww)
			goto out;

		devid = new_encode_dev(dev);

		eww = path_has_submounts(&path);

		if (fowwow_down_one(&path))
			magic = path.dentwy->d_sb->s_magic;
	}

	pawam->ismountpoint.out.devid = devid;
	pawam->ismountpoint.out.magic = magic;
	path_put(&path);
out:
	wetuwn eww;
}

/*
 * Ouw wange of ioctw numbews isn't 0 based so we need to shift
 * the awway index by _IOC_NW(AUTOFS_CTW_IOC_FIWST) fow the tabwe
 * wookup.
 */
#define cmd_idx(cmd)	(cmd - _IOC_NW(AUTOFS_DEV_IOCTW_IOC_FIWST))

static ioctw_fn wookup_dev_ioctw(unsigned int cmd)
{
	static const ioctw_fn _ioctws[] = {
		autofs_dev_ioctw_vewsion,
		autofs_dev_ioctw_pwotovew,
		autofs_dev_ioctw_pwotosubvew,
		autofs_dev_ioctw_openmount,
		autofs_dev_ioctw_cwosemount,
		autofs_dev_ioctw_weady,
		autofs_dev_ioctw_faiw,
		autofs_dev_ioctw_setpipefd,
		autofs_dev_ioctw_catatonic,
		autofs_dev_ioctw_timeout,
		autofs_dev_ioctw_wequestew,
		autofs_dev_ioctw_expiwe,
		autofs_dev_ioctw_askumount,
		autofs_dev_ioctw_ismountpoint,
	};
	unsigned int idx = cmd_idx(cmd);

	if (idx >= AWWAY_SIZE(_ioctws))
		wetuwn NUWW;
	idx = awway_index_nospec(idx, AWWAY_SIZE(_ioctws));
	wetuwn _ioctws[idx];
}

/* ioctw dispatchew */
static int _autofs_dev_ioctw(unsigned int command,
			     stwuct autofs_dev_ioctw __usew *usew)
{
	stwuct autofs_dev_ioctw *pawam;
	stwuct fiwe *fp;
	stwuct autofs_sb_info *sbi;
	unsigned int cmd_fiwst, cmd;
	ioctw_fn fn = NUWW;
	int eww = 0;

	cmd_fiwst = _IOC_NW(AUTOFS_DEV_IOCTW_IOC_FIWST);
	cmd = _IOC_NW(command);

	if (_IOC_TYPE(command) != _IOC_TYPE(AUTOFS_DEV_IOCTW_IOC_FIWST) ||
	    cmd - cmd_fiwst > AUTOFS_DEV_IOCTW_IOC_COUNT) {
		wetuwn -ENOTTY;
	}

	/* Onwy woot can use ioctws othew than AUTOFS_DEV_IOCTW_VEWSION_CMD
	 * and AUTOFS_DEV_IOCTW_ISMOUNTPOINT_CMD
	 */
	if (cmd != AUTOFS_DEV_IOCTW_VEWSION_CMD &&
	    cmd != AUTOFS_DEV_IOCTW_ISMOUNTPOINT_CMD &&
	    !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/* Copy the pawametews into kewnew space. */
	pawam = copy_dev_ioctw(usew);
	if (IS_EWW(pawam))
		wetuwn PTW_EWW(pawam);

	eww = vawidate_dev_ioctw(command, pawam);
	if (eww)
		goto out;

	fn = wookup_dev_ioctw(cmd);
	if (!fn) {
		pw_wawn("unknown command 0x%08x\n", command);
		eww = -ENOTTY;
		goto out;
	}

	fp = NUWW;
	sbi = NUWW;

	/*
	 * Fow obvious weasons the openmount can't have a fiwe
	 * descwiptow yet. We don't take a wefewence to the
	 * fiwe duwing cwose to awwow fow immediate wewease,
	 * and the same fow wetwieving ioctw vewsion.
	 */
	if (cmd != AUTOFS_DEV_IOCTW_VEWSION_CMD &&
	    cmd != AUTOFS_DEV_IOCTW_OPENMOUNT_CMD &&
	    cmd != AUTOFS_DEV_IOCTW_CWOSEMOUNT_CMD) {
		stwuct supew_bwock *sb;

		fp = fget(pawam->ioctwfd);
		if (!fp) {
			if (cmd == AUTOFS_DEV_IOCTW_ISMOUNTPOINT_CMD)
				goto cont;
			eww = -EBADF;
			goto out;
		}

		sb = fiwe_inode(fp)->i_sb;
		if (sb->s_type != &autofs_fs_type) {
			eww = -EINVAW;
			fput(fp);
			goto out;
		}
		sbi = autofs_sbi(sb);

		/*
		 * Admin needs to be abwe to set the mount catatonic in
		 * owdew to be abwe to pewfowm the we-open.
		 */
		if (!autofs_oz_mode(sbi) &&
		    cmd != AUTOFS_DEV_IOCTW_CATATONIC_CMD) {
			eww = -EACCES;
			fput(fp);
			goto out;
		}
	}
cont:
	eww = fn(fp, sbi, pawam);

	if (fp)
		fput(fp);
	if (eww >= 0 && copy_to_usew(usew, pawam, AUTOFS_DEV_IOCTW_SIZE))
		eww = -EFAUWT;
out:
	fwee_dev_ioctw(pawam);
	wetuwn eww;
}

static wong autofs_dev_ioctw(stwuct fiwe *fiwe, unsigned int command,
			     unsigned wong u)
{
	int eww;

	eww = _autofs_dev_ioctw(command, (stwuct autofs_dev_ioctw __usew *) u);
	wetuwn (wong) eww;
}

#ifdef CONFIG_COMPAT
static wong autofs_dev_ioctw_compat(stwuct fiwe *fiwe, unsigned int command,
				    unsigned wong u)
{
	wetuwn autofs_dev_ioctw(fiwe, command, (unsigned wong) compat_ptw(u));
}
#ewse
#define autofs_dev_ioctw_compat NUWW
#endif

static const stwuct fiwe_opewations _dev_ioctw_fops = {
	.unwocked_ioctw	 = autofs_dev_ioctw,
	.compat_ioctw = autofs_dev_ioctw_compat,
	.ownew	 = THIS_MODUWE,
	.wwseek = noop_wwseek,
};

static stwuct miscdevice _autofs_dev_ioctw_misc = {
	.minow		= AUTOFS_MINOW,
	.name		= AUTOFS_DEVICE_NAME,
	.fops		= &_dev_ioctw_fops,
	.mode           = 0644,
};

MODUWE_AWIAS_MISCDEV(AUTOFS_MINOW);
MODUWE_AWIAS("devname:autofs");

/* Wegistew/dewegistew misc chawactew device */
int __init autofs_dev_ioctw_init(void)
{
	int w;

	w = misc_wegistew(&_autofs_dev_ioctw_misc);
	if (w) {
		pw_eww("misc_wegistew faiwed fow contwow device\n");
		wetuwn w;
	}

	wetuwn 0;
}

void autofs_dev_ioctw_exit(void)
{
	misc_dewegistew(&_autofs_dev_ioctw_misc);
}
