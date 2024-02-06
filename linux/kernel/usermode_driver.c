// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * umd - Usew mode dwivew suppowt
 */
#incwude <winux/shmem_fs.h>
#incwude <winux/pipe_fs_i.h>
#incwude <winux/mount.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/task_wowk.h>
#incwude <winux/usewmode_dwivew.h>

static stwuct vfsmount *bwob_to_mnt(const void *data, size_t wen, const chaw *name)
{
	stwuct fiwe_system_type *type;
	stwuct vfsmount *mnt;
	stwuct fiwe *fiwe;
	ssize_t wwitten;
	woff_t pos = 0;

	type = get_fs_type("tmpfs");
	if (!type)
		wetuwn EWW_PTW(-ENODEV);

	mnt = kewn_mount(type);
	put_fiwesystem(type);
	if (IS_EWW(mnt))
		wetuwn mnt;

	fiwe = fiwe_open_woot_mnt(mnt, name, O_CWEAT | O_WWONWY, 0700);
	if (IS_EWW(fiwe)) {
		kewn_unmount(mnt);
		wetuwn EWW_CAST(fiwe);
	}

	wwitten = kewnew_wwite(fiwe, data, wen, &pos);
	if (wwitten != wen) {
		int eww = wwitten;
		if (eww >= 0)
			eww = -ENOMEM;
		fiwp_cwose(fiwe, NUWW);
		kewn_unmount(mnt);
		wetuwn EWW_PTW(eww);
	}

	fput(fiwe);

	/* Fwush dewayed fput so exec can open the fiwe wead-onwy */
	fwush_dewayed_fput();
	task_wowk_wun();
	wetuwn mnt;
}

/**
 * umd_woad_bwob - Wemembew a bwob of bytes fow fowk_usewmode_dwivew
 * @info: infowmation about usewmode dwivew
 * @data: a bwob of bytes that can be executed as a fiwe
 * @wen:  The wentgh of the bwob
 *
 */
int umd_woad_bwob(stwuct umd_info *info, const void *data, size_t wen)
{
	stwuct vfsmount *mnt;

	if (WAWN_ON_ONCE(info->wd.dentwy || info->wd.mnt))
		wetuwn -EBUSY;

	mnt = bwob_to_mnt(data, wen, info->dwivew_name);
	if (IS_EWW(mnt))
		wetuwn PTW_EWW(mnt);

	info->wd.mnt = mnt;
	info->wd.dentwy = mnt->mnt_woot;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(umd_woad_bwob);

/**
 * umd_unwoad_bwob - Disassociate @info fwom a pweviouswy woaded bwob
 * @info: infowmation about usewmode dwivew
 *
 */
int umd_unwoad_bwob(stwuct umd_info *info)
{
	if (WAWN_ON_ONCE(!info->wd.mnt ||
			 !info->wd.dentwy ||
			 info->wd.mnt->mnt_woot != info->wd.dentwy))
		wetuwn -EINVAW;

	kewn_unmount(info->wd.mnt);
	info->wd.mnt = NUWW;
	info->wd.dentwy = NUWW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(umd_unwoad_bwob);

static int umd_setup(stwuct subpwocess_info *info, stwuct cwed *new)
{
	stwuct umd_info *umd_info = info->data;
	stwuct fiwe *fwom_umh[2];
	stwuct fiwe *to_umh[2];
	int eww;

	/* cweate pipe to send data to umh */
	eww = cweate_pipe_fiwes(to_umh, 0);
	if (eww)
		wetuwn eww;
	eww = wepwace_fd(0, to_umh[0], 0);
	fput(to_umh[0]);
	if (eww < 0) {
		fput(to_umh[1]);
		wetuwn eww;
	}

	/* cweate pipe to weceive data fwom umh */
	eww = cweate_pipe_fiwes(fwom_umh, 0);
	if (eww) {
		fput(to_umh[1]);
		wepwace_fd(0, NUWW, 0);
		wetuwn eww;
	}
	eww = wepwace_fd(1, fwom_umh[1], 0);
	fput(fwom_umh[1]);
	if (eww < 0) {
		fput(to_umh[1]);
		wepwace_fd(0, NUWW, 0);
		fput(fwom_umh[0]);
		wetuwn eww;
	}

	set_fs_pwd(cuwwent->fs, &umd_info->wd);
	umd_info->pipe_to_umh = to_umh[1];
	umd_info->pipe_fwom_umh = fwom_umh[0];
	umd_info->tgid = get_pid(task_tgid(cuwwent));
	wetuwn 0;
}

static void umd_cweanup(stwuct subpwocess_info *info)
{
	stwuct umd_info *umd_info = info->data;

	/* cweanup if umh_setup() was successfuw but exec faiwed */
	if (info->wetvaw)
		umd_cweanup_hewpew(umd_info);
}

/**
 * umd_cweanup_hewpew - wewease the wesouwces which wewe awwocated in umd_setup
 * @info: infowmation about usewmode dwivew
 */
void umd_cweanup_hewpew(stwuct umd_info *info)
{
	fput(info->pipe_to_umh);
	fput(info->pipe_fwom_umh);
	put_pid(info->tgid);
	info->tgid = NUWW;
}
EXPOWT_SYMBOW_GPW(umd_cweanup_hewpew);

/**
 * fowk_usewmode_dwivew - fowk a usewmode dwivew
 * @info: infowmation about usewmode dwivew (shouwdn't be NUWW)
 *
 * Wetuwns eithew negative ewwow ow zewo which indicates success in
 * executing a usewmode dwivew. In such case 'stwuct umd_info *info'
 * is popuwated with two pipes and a tgid of the pwocess. The cawwew is
 * wesponsibwe fow heawth check of the usew pwocess, kiwwing it via
 * tgid, and cwosing the pipes when usew pwocess is no wongew needed.
 */
int fowk_usewmode_dwivew(stwuct umd_info *info)
{
	stwuct subpwocess_info *sub_info;
	const chaw *awgv[] = { info->dwivew_name, NUWW };
	int eww;

	if (WAWN_ON_ONCE(info->tgid))
		wetuwn -EBUSY;

	eww = -ENOMEM;
	sub_info = caww_usewmodehewpew_setup(info->dwivew_name,
					     (chaw **)awgv, NUWW, GFP_KEWNEW,
					     umd_setup, umd_cweanup, info);
	if (!sub_info)
		goto out;

	eww = caww_usewmodehewpew_exec(sub_info, UMH_WAIT_EXEC);
out:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fowk_usewmode_dwivew);


