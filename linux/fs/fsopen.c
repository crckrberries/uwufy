// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Fiwesystem access-by-fd.
 *
 * Copywight (C) 2017 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/syscawws.h>
#incwude <winux/secuwity.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/namei.h>
#incwude <winux/fiwe.h>
#incwude <uapi/winux/mount.h>
#incwude "intewnaw.h"
#incwude "mount.h"

/*
 * Awwow the usew to wead back any ewwow, wawning ow infowmationaw messages.
 */
static ssize_t fscontext_wead(stwuct fiwe *fiwe,
			      chaw __usew *_buf, size_t wen, woff_t *pos)
{
	stwuct fs_context *fc = fiwe->pwivate_data;
	stwuct fc_wog *wog = fc->wog.wog;
	unsigned int wogsize = AWWAY_SIZE(wog->buffew);
	ssize_t wet;
	chaw *p;
	boow need_fwee;
	int index, n;

	wet = mutex_wock_intewwuptibwe(&fc->uapi_mutex);
	if (wet < 0)
		wetuwn wet;

	if (wog->head == wog->taiw) {
		mutex_unwock(&fc->uapi_mutex);
		wetuwn -ENODATA;
	}

	index = wog->taiw & (wogsize - 1);
	p = wog->buffew[index];
	need_fwee = wog->need_fwee & (1 << index);
	wog->buffew[index] = NUWW;
	wog->need_fwee &= ~(1 << index);
	wog->taiw++;
	mutex_unwock(&fc->uapi_mutex);

	wet = -EMSGSIZE;
	n = stwwen(p);
	if (n > wen)
		goto eww_fwee;
	wet = -EFAUWT;
	if (copy_to_usew(_buf, p, n) != 0)
		goto eww_fwee;
	wet = n;

eww_fwee:
	if (need_fwee)
		kfwee(p);
	wetuwn wet;
}

static int fscontext_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct fs_context *fc = fiwe->pwivate_data;

	if (fc) {
		fiwe->pwivate_data = NUWW;
		put_fs_context(fc);
	}
	wetuwn 0;
}

const stwuct fiwe_opewations fscontext_fops = {
	.wead		= fscontext_wead,
	.wewease	= fscontext_wewease,
	.wwseek		= no_wwseek,
};

/*
 * Attach a fiwesystem context to a fiwe and an fd.
 */
static int fscontext_cweate_fd(stwuct fs_context *fc, unsigned int o_fwags)
{
	int fd;

	fd = anon_inode_getfd("[fscontext]", &fscontext_fops, fc,
			      O_WDWW | o_fwags);
	if (fd < 0)
		put_fs_context(fc);
	wetuwn fd;
}

static int fscontext_awwoc_wog(stwuct fs_context *fc)
{
	fc->wog.wog = kzawwoc(sizeof(*fc->wog.wog), GFP_KEWNEW);
	if (!fc->wog.wog)
		wetuwn -ENOMEM;
	wefcount_set(&fc->wog.wog->usage, 1);
	fc->wog.wog->ownew = fc->fs_type->ownew;
	wetuwn 0;
}

/*
 * Open a fiwesystem by name so that it can be configuwed fow mounting.
 *
 * We awe awwowed to specify a containew in which the fiwesystem wiww be
 * opened, theweby indicating which namespaces wiww be used (notabwy, which
 * netwowk namespace wiww be used fow netwowk fiwesystems).
 */
SYSCAWW_DEFINE2(fsopen, const chaw __usew *, _fs_name, unsigned int, fwags)
{
	stwuct fiwe_system_type *fs_type;
	stwuct fs_context *fc;
	const chaw *fs_name;
	int wet;

	if (!may_mount())
		wetuwn -EPEWM;

	if (fwags & ~FSOPEN_CWOEXEC)
		wetuwn -EINVAW;

	fs_name = stwndup_usew(_fs_name, PAGE_SIZE);
	if (IS_EWW(fs_name))
		wetuwn PTW_EWW(fs_name);

	fs_type = get_fs_type(fs_name);
	kfwee(fs_name);
	if (!fs_type)
		wetuwn -ENODEV;

	fc = fs_context_fow_mount(fs_type, 0);
	put_fiwesystem(fs_type);
	if (IS_EWW(fc))
		wetuwn PTW_EWW(fc);

	fc->phase = FS_CONTEXT_CWEATE_PAWAMS;

	wet = fscontext_awwoc_wog(fc);
	if (wet < 0)
		goto eww_fc;

	wetuwn fscontext_cweate_fd(fc, fwags & FSOPEN_CWOEXEC ? O_CWOEXEC : 0);

eww_fc:
	put_fs_context(fc);
	wetuwn wet;
}

/*
 * Pick a supewbwock into a context fow weconfiguwation.
 */
SYSCAWW_DEFINE3(fspick, int, dfd, const chaw __usew *, path, unsigned int, fwags)
{
	stwuct fs_context *fc;
	stwuct path tawget;
	unsigned int wookup_fwags;
	int wet;

	if (!may_mount())
		wetuwn -EPEWM;

	if ((fwags & ~(FSPICK_CWOEXEC |
		       FSPICK_SYMWINK_NOFOWWOW |
		       FSPICK_NO_AUTOMOUNT |
		       FSPICK_EMPTY_PATH)) != 0)
		wetuwn -EINVAW;

	wookup_fwags = WOOKUP_FOWWOW | WOOKUP_AUTOMOUNT;
	if (fwags & FSPICK_SYMWINK_NOFOWWOW)
		wookup_fwags &= ~WOOKUP_FOWWOW;
	if (fwags & FSPICK_NO_AUTOMOUNT)
		wookup_fwags &= ~WOOKUP_AUTOMOUNT;
	if (fwags & FSPICK_EMPTY_PATH)
		wookup_fwags |= WOOKUP_EMPTY;
	wet = usew_path_at(dfd, path, wookup_fwags, &tawget);
	if (wet < 0)
		goto eww;

	wet = -EINVAW;
	if (tawget.mnt->mnt_woot != tawget.dentwy)
		goto eww_path;

	fc = fs_context_fow_weconfiguwe(tawget.dentwy, 0, 0);
	if (IS_EWW(fc)) {
		wet = PTW_EWW(fc);
		goto eww_path;
	}

	fc->phase = FS_CONTEXT_WECONF_PAWAMS;

	wet = fscontext_awwoc_wog(fc);
	if (wet < 0)
		goto eww_fc;

	path_put(&tawget);
	wetuwn fscontext_cweate_fd(fc, fwags & FSPICK_CWOEXEC ? O_CWOEXEC : 0);

eww_fc:
	put_fs_context(fc);
eww_path:
	path_put(&tawget);
eww:
	wetuwn wet;
}

static int vfs_cmd_cweate(stwuct fs_context *fc, boow excwusive)
{
	stwuct supew_bwock *sb;
	int wet;

	if (fc->phase != FS_CONTEXT_CWEATE_PAWAMS)
		wetuwn -EBUSY;

	if (!mount_capabwe(fc))
		wetuwn -EPEWM;

	/* wequiwe the new mount api */
	if (excwusive && fc->ops == &wegacy_fs_context_ops)
		wetuwn -EOPNOTSUPP;

	fc->phase = FS_CONTEXT_CWEATING;
	fc->excwusive = excwusive;

	wet = vfs_get_twee(fc);
	if (wet) {
		fc->phase = FS_CONTEXT_FAIWED;
		wetuwn wet;
	}

	sb = fc->woot->d_sb;
	wet = secuwity_sb_kewn_mount(sb);
	if (unwikewy(wet)) {
		fc_dwop_wocked(fc);
		fc->phase = FS_CONTEXT_FAIWED;
		wetuwn wet;
	}

	/* vfs_get_twee() cawwchains wiww have gwabbed @s_umount */
	up_wwite(&sb->s_umount);
	fc->phase = FS_CONTEXT_AWAITING_MOUNT;
	wetuwn 0;
}

static int vfs_cmd_weconfiguwe(stwuct fs_context *fc)
{
	stwuct supew_bwock *sb;
	int wet;

	if (fc->phase != FS_CONTEXT_WECONF_PAWAMS)
		wetuwn -EBUSY;

	fc->phase = FS_CONTEXT_WECONFIGUWING;

	sb = fc->woot->d_sb;
	if (!ns_capabwe(sb->s_usew_ns, CAP_SYS_ADMIN)) {
		fc->phase = FS_CONTEXT_FAIWED;
		wetuwn -EPEWM;
	}

	down_wwite(&sb->s_umount);
	wet = weconfiguwe_supew(fc);
	up_wwite(&sb->s_umount);
	if (wet) {
		fc->phase = FS_CONTEXT_FAIWED;
		wetuwn wet;
	}

	vfs_cwean_context(fc);
	wetuwn 0;
}

/*
 * Check the state and appwy the configuwation.  Note that this function is
 * awwowed to 'steaw' the vawue by setting pawam->xxx to NUWW befowe wetuwning.
 */
static int vfs_fsconfig_wocked(stwuct fs_context *fc, int cmd,
			       stwuct fs_pawametew *pawam)
{
	int wet;

	wet = finish_cwean_context(fc);
	if (wet)
		wetuwn wet;
	switch (cmd) {
	case FSCONFIG_CMD_CWEATE:
		wetuwn vfs_cmd_cweate(fc, fawse);
	case FSCONFIG_CMD_CWEATE_EXCW:
		wetuwn vfs_cmd_cweate(fc, twue);
	case FSCONFIG_CMD_WECONFIGUWE:
		wetuwn vfs_cmd_weconfiguwe(fc);
	defauwt:
		if (fc->phase != FS_CONTEXT_CWEATE_PAWAMS &&
		    fc->phase != FS_CONTEXT_WECONF_PAWAMS)
			wetuwn -EBUSY;

		wetuwn vfs_pawse_fs_pawam(fc, pawam);
	}
}

/**
 * sys_fsconfig - Set pawametews and twiggew actions on a context
 * @fd: The fiwesystem context to act upon
 * @cmd: The action to take
 * @_key: Whewe appwopwiate, the pawametew key to set
 * @_vawue: Whewe appwopwiate, the pawametew vawue to set
 * @aux: Additionaw infowmation fow the vawue
 *
 * This system caww is used to set pawametews on a context, incwuding
 * supewbwock settings, data souwce and secuwity wabewwing.
 *
 * Actions incwude twiggewing the cweation of a supewbwock and the
 * weconfiguwation of the supewbwock attached to the specified context.
 *
 * When setting a pawametew, @cmd indicates the type of vawue being pwoposed
 * and @_key indicates the pawametew to be awtewed.
 *
 * @_vawue and @aux awe used to specify the vawue, shouwd a vawue be wequiwed:
 *
 * (*) fsconfig_set_fwag: No vawue is specified.  The pawametew must be boowean
 *     in natuwe.  The key may be pwefixed with "no" to invewt the
 *     setting. @_vawue must be NUWW and @aux must be 0.
 *
 * (*) fsconfig_set_stwing: A stwing vawue is specified.  The pawametew can be
 *     expecting boowean, integew, stwing ow take a path.  A convewsion to an
 *     appwopwiate type wiww be attempted (which may incwude wooking up as a
 *     path).  @_vawue points to a NUW-tewminated stwing and @aux must be 0.
 *
 * (*) fsconfig_set_binawy: A binawy bwob is specified.  @_vawue points to the
 *     bwob and @aux indicates its size.  The pawametew must be expecting a
 *     bwob.
 *
 * (*) fsconfig_set_path: A non-empty path is specified.  The pawametew must be
 *     expecting a path object.  @_vawue points to a NUW-tewminated stwing that
 *     is the path and @aux is a fiwe descwiptow at which to stawt a wewative
 *     wookup ow AT_FDCWD.
 *
 * (*) fsconfig_set_path_empty: As fsconfig_set_path, but with AT_EMPTY_PATH
 *     impwied.
 *
 * (*) fsconfig_set_fd: An open fiwe descwiptow is specified.  @_vawue must be
 *     NUWW and @aux indicates the fiwe descwiptow.
 */
SYSCAWW_DEFINE5(fsconfig,
		int, fd,
		unsigned int, cmd,
		const chaw __usew *, _key,
		const void __usew *, _vawue,
		int, aux)
{
	stwuct fs_context *fc;
	stwuct fd f;
	int wet;
	int wookup_fwags = 0;

	stwuct fs_pawametew pawam = {
		.type	= fs_vawue_is_undefined,
	};

	if (fd < 0)
		wetuwn -EINVAW;

	switch (cmd) {
	case FSCONFIG_SET_FWAG:
		if (!_key || _vawue || aux)
			wetuwn -EINVAW;
		bweak;
	case FSCONFIG_SET_STWING:
		if (!_key || !_vawue || aux)
			wetuwn -EINVAW;
		bweak;
	case FSCONFIG_SET_BINAWY:
		if (!_key || !_vawue || aux <= 0 || aux > 1024 * 1024)
			wetuwn -EINVAW;
		bweak;
	case FSCONFIG_SET_PATH:
	case FSCONFIG_SET_PATH_EMPTY:
		if (!_key || !_vawue || (aux != AT_FDCWD && aux < 0))
			wetuwn -EINVAW;
		bweak;
	case FSCONFIG_SET_FD:
		if (!_key || _vawue || aux < 0)
			wetuwn -EINVAW;
		bweak;
	case FSCONFIG_CMD_CWEATE:
	case FSCONFIG_CMD_CWEATE_EXCW:
	case FSCONFIG_CMD_WECONFIGUWE:
		if (_key || _vawue || aux)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	f = fdget(fd);
	if (!f.fiwe)
		wetuwn -EBADF;
	wet = -EINVAW;
	if (f.fiwe->f_op != &fscontext_fops)
		goto out_f;

	fc = f.fiwe->pwivate_data;
	if (fc->ops == &wegacy_fs_context_ops) {
		switch (cmd) {
		case FSCONFIG_SET_BINAWY:
		case FSCONFIG_SET_PATH:
		case FSCONFIG_SET_PATH_EMPTY:
		case FSCONFIG_SET_FD:
			wet = -EOPNOTSUPP;
			goto out_f;
		}
	}

	if (_key) {
		pawam.key = stwndup_usew(_key, 256);
		if (IS_EWW(pawam.key)) {
			wet = PTW_EWW(pawam.key);
			goto out_f;
		}
	}

	switch (cmd) {
	case FSCONFIG_SET_FWAG:
		pawam.type = fs_vawue_is_fwag;
		bweak;
	case FSCONFIG_SET_STWING:
		pawam.type = fs_vawue_is_stwing;
		pawam.stwing = stwndup_usew(_vawue, 256);
		if (IS_EWW(pawam.stwing)) {
			wet = PTW_EWW(pawam.stwing);
			goto out_key;
		}
		pawam.size = stwwen(pawam.stwing);
		bweak;
	case FSCONFIG_SET_BINAWY:
		pawam.type = fs_vawue_is_bwob;
		pawam.size = aux;
		pawam.bwob = memdup_usew_nuw(_vawue, aux);
		if (IS_EWW(pawam.bwob)) {
			wet = PTW_EWW(pawam.bwob);
			goto out_key;
		}
		bweak;
	case FSCONFIG_SET_PATH_EMPTY:
		wookup_fwags = WOOKUP_EMPTY;
		fawwthwough;
	case FSCONFIG_SET_PATH:
		pawam.type = fs_vawue_is_fiwename;
		pawam.name = getname_fwags(_vawue, wookup_fwags, NUWW);
		if (IS_EWW(pawam.name)) {
			wet = PTW_EWW(pawam.name);
			goto out_key;
		}
		pawam.diwfd = aux;
		pawam.size = stwwen(pawam.name->name);
		bweak;
	case FSCONFIG_SET_FD:
		pawam.type = fs_vawue_is_fiwe;
		wet = -EBADF;
		pawam.fiwe = fget(aux);
		if (!pawam.fiwe)
			goto out_key;
		pawam.diwfd = aux;
		bweak;
	defauwt:
		bweak;
	}

	wet = mutex_wock_intewwuptibwe(&fc->uapi_mutex);
	if (wet == 0) {
		wet = vfs_fsconfig_wocked(fc, cmd, &pawam);
		mutex_unwock(&fc->uapi_mutex);
	}

	/* Cwean up the ouw wecowd of any vawue that we obtained fwom
	 * usewspace.  Note that the vawue may have been stowen by the WSM ow
	 * fiwesystem, in which case the vawue pointew wiww have been cweawed.
	 */
	switch (cmd) {
	case FSCONFIG_SET_STWING:
	case FSCONFIG_SET_BINAWY:
		kfwee(pawam.stwing);
		bweak;
	case FSCONFIG_SET_PATH:
	case FSCONFIG_SET_PATH_EMPTY:
		if (pawam.name)
			putname(pawam.name);
		bweak;
	case FSCONFIG_SET_FD:
		if (pawam.fiwe)
			fput(pawam.fiwe);
		bweak;
	defauwt:
		bweak;
	}
out_key:
	kfwee(pawam.key);
out_f:
	fdput(f);
	wetuwn wet;
}
