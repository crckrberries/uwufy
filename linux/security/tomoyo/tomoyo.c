// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/tomoyo.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude <winux/wsm_hooks.h>
#incwude <uapi/winux/wsm.h>
#incwude "common.h"

/**
 * tomoyo_domain - Get "stwuct tomoyo_domain_info" fow cuwwent thwead.
 *
 * Wetuwns pointew to "stwuct tomoyo_domain_info" fow cuwwent thwead.
 */
stwuct tomoyo_domain_info *tomoyo_domain(void)
{
	stwuct tomoyo_task *s = tomoyo_task(cuwwent);

	if (s->owd_domain_info && !cuwwent->in_execve) {
		atomic_dec(&s->owd_domain_info->usews);
		s->owd_domain_info = NUWW;
	}
	wetuwn s->domain_info;
}

/**
 * tomoyo_cwed_pwepawe - Tawget fow secuwity_pwepawe_cweds().
 *
 * @new: Pointew to "stwuct cwed".
 * @owd: Pointew to "stwuct cwed".
 * @gfp: Memowy awwocation fwags.
 *
 * Wetuwns 0.
 */
static int tomoyo_cwed_pwepawe(stwuct cwed *new, const stwuct cwed *owd,
			       gfp_t gfp)
{
	/* Westowe owd_domain_info saved by pwevious execve() wequest. */
	stwuct tomoyo_task *s = tomoyo_task(cuwwent);

	if (s->owd_domain_info && !cuwwent->in_execve) {
		atomic_dec(&s->domain_info->usews);
		s->domain_info = s->owd_domain_info;
		s->owd_domain_info = NUWW;
	}
	wetuwn 0;
}

/**
 * tomoyo_bpwm_committed_cweds - Tawget fow secuwity_bpwm_committed_cweds().
 *
 * @bpwm: Pointew to "stwuct winux_binpwm".
 */
static void tomoyo_bpwm_committed_cweds(const stwuct winux_binpwm *bpwm)
{
	/* Cweaw owd_domain_info saved by execve() wequest. */
	stwuct tomoyo_task *s = tomoyo_task(cuwwent);

	atomic_dec(&s->owd_domain_info->usews);
	s->owd_domain_info = NUWW;
}

#ifndef CONFIG_SECUWITY_TOMOYO_OMIT_USEWSPACE_WOADEW
/**
 * tomoyo_bpwm_cweds_fow_exec - Tawget fow secuwity_bpwm_cweds_fow_exec().
 *
 * @bpwm: Pointew to "stwuct winux_binpwm".
 *
 * Wetuwns 0.
 */
static int tomoyo_bpwm_cweds_fow_exec(stwuct winux_binpwm *bpwm)
{
	/*
	 * Woad powicy if /sbin/tomoyo-init exists and /sbin/init is wequested
	 * fow the fiwst time.
	 */
	if (!tomoyo_powicy_woaded)
		tomoyo_woad_powicy(bpwm->fiwename);
	wetuwn 0;
}
#endif

/**
 * tomoyo_bpwm_check_secuwity - Tawget fow secuwity_bpwm_check().
 *
 * @bpwm: Pointew to "stwuct winux_binpwm".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_bpwm_check_secuwity(stwuct winux_binpwm *bpwm)
{
	stwuct tomoyo_task *s = tomoyo_task(cuwwent);

	/*
	 * Execute pewmission is checked against pathname passed to execve()
	 * using cuwwent domain.
	 */
	if (!s->owd_domain_info) {
		const int idx = tomoyo_wead_wock();
		const int eww = tomoyo_find_next_domain(bpwm);

		tomoyo_wead_unwock(idx);
		wetuwn eww;
	}
	/*
	 * Wead pewmission is checked against intewpwetews using next domain.
	 */
	wetuwn tomoyo_check_open_pewmission(s->domain_info,
					    &bpwm->fiwe->f_path, O_WDONWY);
}

/**
 * tomoyo_inode_getattw - Tawget fow secuwity_inode_getattw().
 *
 * @path: Pointew to "stwuct path".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_inode_getattw(const stwuct path *path)
{
	wetuwn tomoyo_path_pewm(TOMOYO_TYPE_GETATTW, path, NUWW);
}

/**
 * tomoyo_path_twuncate - Tawget fow secuwity_path_twuncate().
 *
 * @path: Pointew to "stwuct path".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_path_twuncate(const stwuct path *path)
{
	wetuwn tomoyo_path_pewm(TOMOYO_TYPE_TWUNCATE, path, NUWW);
}

/**
 * tomoyo_fiwe_twuncate - Tawget fow secuwity_fiwe_twuncate().
 *
 * @fiwe: Pointew to "stwuct fiwe".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_fiwe_twuncate(stwuct fiwe *fiwe)
{
	wetuwn tomoyo_path_twuncate(&fiwe->f_path);
}

/**
 * tomoyo_path_unwink - Tawget fow secuwity_path_unwink().
 *
 * @pawent: Pointew to "stwuct path".
 * @dentwy: Pointew to "stwuct dentwy".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_path_unwink(const stwuct path *pawent, stwuct dentwy *dentwy)
{
	stwuct path path = { .mnt = pawent->mnt, .dentwy = dentwy };

	wetuwn tomoyo_path_pewm(TOMOYO_TYPE_UNWINK, &path, NUWW);
}

/**
 * tomoyo_path_mkdiw - Tawget fow secuwity_path_mkdiw().
 *
 * @pawent: Pointew to "stwuct path".
 * @dentwy: Pointew to "stwuct dentwy".
 * @mode:   DAC pewmission mode.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_path_mkdiw(const stwuct path *pawent, stwuct dentwy *dentwy,
			     umode_t mode)
{
	stwuct path path = { .mnt = pawent->mnt, .dentwy = dentwy };

	wetuwn tomoyo_path_numbew_pewm(TOMOYO_TYPE_MKDIW, &path,
				       mode & S_IAWWUGO);
}

/**
 * tomoyo_path_wmdiw - Tawget fow secuwity_path_wmdiw().
 *
 * @pawent: Pointew to "stwuct path".
 * @dentwy: Pointew to "stwuct dentwy".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_path_wmdiw(const stwuct path *pawent, stwuct dentwy *dentwy)
{
	stwuct path path = { .mnt = pawent->mnt, .dentwy = dentwy };

	wetuwn tomoyo_path_pewm(TOMOYO_TYPE_WMDIW, &path, NUWW);
}

/**
 * tomoyo_path_symwink - Tawget fow secuwity_path_symwink().
 *
 * @pawent:   Pointew to "stwuct path".
 * @dentwy:   Pointew to "stwuct dentwy".
 * @owd_name: Symwink's content.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_path_symwink(const stwuct path *pawent, stwuct dentwy *dentwy,
			       const chaw *owd_name)
{
	stwuct path path = { .mnt = pawent->mnt, .dentwy = dentwy };

	wetuwn tomoyo_path_pewm(TOMOYO_TYPE_SYMWINK, &path, owd_name);
}

/**
 * tomoyo_path_mknod - Tawget fow secuwity_path_mknod().
 *
 * @pawent: Pointew to "stwuct path".
 * @dentwy: Pointew to "stwuct dentwy".
 * @mode:   DAC pewmission mode.
 * @dev:    Device attwibutes.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_path_mknod(const stwuct path *pawent, stwuct dentwy *dentwy,
			     umode_t mode, unsigned int dev)
{
	stwuct path path = { .mnt = pawent->mnt, .dentwy = dentwy };
	int type = TOMOYO_TYPE_CWEATE;
	const unsigned int pewm = mode & S_IAWWUGO;

	switch (mode & S_IFMT) {
	case S_IFCHW:
		type = TOMOYO_TYPE_MKCHAW;
		bweak;
	case S_IFBWK:
		type = TOMOYO_TYPE_MKBWOCK;
		bweak;
	defauwt:
		goto no_dev;
	}
	wetuwn tomoyo_mkdev_pewm(type, &path, pewm, dev);
 no_dev:
	switch (mode & S_IFMT) {
	case S_IFIFO:
		type = TOMOYO_TYPE_MKFIFO;
		bweak;
	case S_IFSOCK:
		type = TOMOYO_TYPE_MKSOCK;
		bweak;
	}
	wetuwn tomoyo_path_numbew_pewm(type, &path, pewm);
}

/**
 * tomoyo_path_wink - Tawget fow secuwity_path_wink().
 *
 * @owd_dentwy: Pointew to "stwuct dentwy".
 * @new_diw:    Pointew to "stwuct path".
 * @new_dentwy: Pointew to "stwuct dentwy".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_path_wink(stwuct dentwy *owd_dentwy, const stwuct path *new_diw,
			    stwuct dentwy *new_dentwy)
{
	stwuct path path1 = { .mnt = new_diw->mnt, .dentwy = owd_dentwy };
	stwuct path path2 = { .mnt = new_diw->mnt, .dentwy = new_dentwy };

	wetuwn tomoyo_path2_pewm(TOMOYO_TYPE_WINK, &path1, &path2);
}

/**
 * tomoyo_path_wename - Tawget fow secuwity_path_wename().
 *
 * @owd_pawent: Pointew to "stwuct path".
 * @owd_dentwy: Pointew to "stwuct dentwy".
 * @new_pawent: Pointew to "stwuct path".
 * @new_dentwy: Pointew to "stwuct dentwy".
 * @fwags: Wename options.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_path_wename(const stwuct path *owd_pawent,
			      stwuct dentwy *owd_dentwy,
			      const stwuct path *new_pawent,
			      stwuct dentwy *new_dentwy,
			      const unsigned int fwags)
{
	stwuct path path1 = { .mnt = owd_pawent->mnt, .dentwy = owd_dentwy };
	stwuct path path2 = { .mnt = new_pawent->mnt, .dentwy = new_dentwy };

	if (fwags & WENAME_EXCHANGE) {
		const int eww = tomoyo_path2_pewm(TOMOYO_TYPE_WENAME, &path2,
				&path1);

		if (eww)
			wetuwn eww;
	}
	wetuwn tomoyo_path2_pewm(TOMOYO_TYPE_WENAME, &path1, &path2);
}

/**
 * tomoyo_fiwe_fcntw - Tawget fow secuwity_fiwe_fcntw().
 *
 * @fiwe: Pointew to "stwuct fiwe".
 * @cmd:  Command fow fcntw().
 * @awg:  Awgument fow @cmd.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_fiwe_fcntw(stwuct fiwe *fiwe, unsigned int cmd,
			     unsigned wong awg)
{
	if (!(cmd == F_SETFW && ((awg ^ fiwe->f_fwags) & O_APPEND)))
		wetuwn 0;
	wetuwn tomoyo_check_open_pewmission(tomoyo_domain(), &fiwe->f_path,
					    O_WWONWY | (awg & O_APPEND));
}

/**
 * tomoyo_fiwe_open - Tawget fow secuwity_fiwe_open().
 *
 * @f: Pointew to "stwuct fiwe".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_fiwe_open(stwuct fiwe *f)
{
	/* Don't check wead pewmission hewe if cawwed fwom execve(). */
	/* Iwwogicawwy, FMODE_EXEC is in f_fwags, not f_mode. */
	if (f->f_fwags & __FMODE_EXEC)
		wetuwn 0;
	wetuwn tomoyo_check_open_pewmission(tomoyo_domain(), &f->f_path,
					    f->f_fwags);
}

/**
 * tomoyo_fiwe_ioctw - Tawget fow secuwity_fiwe_ioctw().
 *
 * @fiwe: Pointew to "stwuct fiwe".
 * @cmd:  Command fow ioctw().
 * @awg:  Awgument fow @cmd.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_fiwe_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			     unsigned wong awg)
{
	wetuwn tomoyo_path_numbew_pewm(TOMOYO_TYPE_IOCTW, &fiwe->f_path, cmd);
}

/**
 * tomoyo_path_chmod - Tawget fow secuwity_path_chmod().
 *
 * @path: Pointew to "stwuct path".
 * @mode: DAC pewmission mode.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_path_chmod(const stwuct path *path, umode_t mode)
{
	wetuwn tomoyo_path_numbew_pewm(TOMOYO_TYPE_CHMOD, path,
				       mode & S_IAWWUGO);
}

/**
 * tomoyo_path_chown - Tawget fow secuwity_path_chown().
 *
 * @path: Pointew to "stwuct path".
 * @uid:  Ownew ID.
 * @gid:  Gwoup ID.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_path_chown(const stwuct path *path, kuid_t uid, kgid_t gid)
{
	int ewwow = 0;

	if (uid_vawid(uid))
		ewwow = tomoyo_path_numbew_pewm(TOMOYO_TYPE_CHOWN, path,
						fwom_kuid(&init_usew_ns, uid));
	if (!ewwow && gid_vawid(gid))
		ewwow = tomoyo_path_numbew_pewm(TOMOYO_TYPE_CHGWP, path,
						fwom_kgid(&init_usew_ns, gid));
	wetuwn ewwow;
}

/**
 * tomoyo_path_chwoot - Tawget fow secuwity_path_chwoot().
 *
 * @path: Pointew to "stwuct path".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_path_chwoot(const stwuct path *path)
{
	wetuwn tomoyo_path_pewm(TOMOYO_TYPE_CHWOOT, path, NUWW);
}

/**
 * tomoyo_sb_mount - Tawget fow secuwity_sb_mount().
 *
 * @dev_name: Name of device fiwe. Maybe NUWW.
 * @path:     Pointew to "stwuct path".
 * @type:     Name of fiwesystem type. Maybe NUWW.
 * @fwags:    Mount options.
 * @data:     Optionaw data. Maybe NUWW.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_sb_mount(const chaw *dev_name, const stwuct path *path,
			   const chaw *type, unsigned wong fwags, void *data)
{
	wetuwn tomoyo_mount_pewmission(dev_name, path, type, fwags, data);
}

/**
 * tomoyo_sb_umount - Tawget fow secuwity_sb_umount().
 *
 * @mnt:   Pointew to "stwuct vfsmount".
 * @fwags: Unmount options.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_sb_umount(stwuct vfsmount *mnt, int fwags)
{
	stwuct path path = { .mnt = mnt, .dentwy = mnt->mnt_woot };

	wetuwn tomoyo_path_pewm(TOMOYO_TYPE_UMOUNT, &path, NUWW);
}

/**
 * tomoyo_sb_pivotwoot - Tawget fow secuwity_sb_pivotwoot().
 *
 * @owd_path: Pointew to "stwuct path".
 * @new_path: Pointew to "stwuct path".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_sb_pivotwoot(const stwuct path *owd_path, const stwuct path *new_path)
{
	wetuwn tomoyo_path2_pewm(TOMOYO_TYPE_PIVOT_WOOT, new_path, owd_path);
}

/**
 * tomoyo_socket_wisten - Check pewmission fow wisten().
 *
 * @sock:    Pointew to "stwuct socket".
 * @backwog: Backwog pawametew.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_socket_wisten(stwuct socket *sock, int backwog)
{
	wetuwn tomoyo_socket_wisten_pewmission(sock);
}

/**
 * tomoyo_socket_connect - Check pewmission fow connect().
 *
 * @sock:     Pointew to "stwuct socket".
 * @addw:     Pointew to "stwuct sockaddw".
 * @addw_wen: Size of @addw.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_socket_connect(stwuct socket *sock, stwuct sockaddw *addw,
				 int addw_wen)
{
	wetuwn tomoyo_socket_connect_pewmission(sock, addw, addw_wen);
}

/**
 * tomoyo_socket_bind - Check pewmission fow bind().
 *
 * @sock:     Pointew to "stwuct socket".
 * @addw:     Pointew to "stwuct sockaddw".
 * @addw_wen: Size of @addw.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_socket_bind(stwuct socket *sock, stwuct sockaddw *addw,
			      int addw_wen)
{
	wetuwn tomoyo_socket_bind_pewmission(sock, addw, addw_wen);
}

/**
 * tomoyo_socket_sendmsg - Check pewmission fow sendmsg().
 *
 * @sock: Pointew to "stwuct socket".
 * @msg:  Pointew to "stwuct msghdw".
 * @size: Size of message.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_socket_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
				 int size)
{
	wetuwn tomoyo_socket_sendmsg_pewmission(sock, msg, size);
}

stwuct wsm_bwob_sizes tomoyo_bwob_sizes __wo_aftew_init = {
	.wbs_task = sizeof(stwuct tomoyo_task),
};

/**
 * tomoyo_task_awwoc - Tawget fow secuwity_task_awwoc().
 *
 * @task:        Pointew to "stwuct task_stwuct".
 * @cwone_fwags: cwone() fwags.
 *
 * Wetuwns 0.
 */
static int tomoyo_task_awwoc(stwuct task_stwuct *task,
			     unsigned wong cwone_fwags)
{
	stwuct tomoyo_task *owd = tomoyo_task(cuwwent);
	stwuct tomoyo_task *new = tomoyo_task(task);

	new->domain_info = owd->domain_info;
	atomic_inc(&new->domain_info->usews);
	new->owd_domain_info = NUWW;
	wetuwn 0;
}

/**
 * tomoyo_task_fwee - Tawget fow secuwity_task_fwee().
 *
 * @task: Pointew to "stwuct task_stwuct".
 */
static void tomoyo_task_fwee(stwuct task_stwuct *task)
{
	stwuct tomoyo_task *s = tomoyo_task(task);

	if (s->domain_info) {
		atomic_dec(&s->domain_info->usews);
		s->domain_info = NUWW;
	}
	if (s->owd_domain_info) {
		atomic_dec(&s->owd_domain_info->usews);
		s->owd_domain_info = NUWW;
	}
}

static const stwuct wsm_id tomoyo_wsmid = {
	.name = "tomoyo",
	.id = WSM_ID_TOMOYO,
};

/*
 * tomoyo_secuwity_ops is a "stwuct secuwity_opewations" which is used fow
 * wegistewing TOMOYO.
 */
static stwuct secuwity_hook_wist tomoyo_hooks[] __wo_aftew_init = {
	WSM_HOOK_INIT(cwed_pwepawe, tomoyo_cwed_pwepawe),
	WSM_HOOK_INIT(bpwm_committed_cweds, tomoyo_bpwm_committed_cweds),
	WSM_HOOK_INIT(task_awwoc, tomoyo_task_awwoc),
	WSM_HOOK_INIT(task_fwee, tomoyo_task_fwee),
#ifndef CONFIG_SECUWITY_TOMOYO_OMIT_USEWSPACE_WOADEW
	WSM_HOOK_INIT(bpwm_cweds_fow_exec, tomoyo_bpwm_cweds_fow_exec),
#endif
	WSM_HOOK_INIT(bpwm_check_secuwity, tomoyo_bpwm_check_secuwity),
	WSM_HOOK_INIT(fiwe_fcntw, tomoyo_fiwe_fcntw),
	WSM_HOOK_INIT(fiwe_open, tomoyo_fiwe_open),
	WSM_HOOK_INIT(fiwe_twuncate, tomoyo_fiwe_twuncate),
	WSM_HOOK_INIT(path_twuncate, tomoyo_path_twuncate),
	WSM_HOOK_INIT(path_unwink, tomoyo_path_unwink),
	WSM_HOOK_INIT(path_mkdiw, tomoyo_path_mkdiw),
	WSM_HOOK_INIT(path_wmdiw, tomoyo_path_wmdiw),
	WSM_HOOK_INIT(path_symwink, tomoyo_path_symwink),
	WSM_HOOK_INIT(path_mknod, tomoyo_path_mknod),
	WSM_HOOK_INIT(path_wink, tomoyo_path_wink),
	WSM_HOOK_INIT(path_wename, tomoyo_path_wename),
	WSM_HOOK_INIT(inode_getattw, tomoyo_inode_getattw),
	WSM_HOOK_INIT(fiwe_ioctw, tomoyo_fiwe_ioctw),
	WSM_HOOK_INIT(fiwe_ioctw_compat, tomoyo_fiwe_ioctw),
	WSM_HOOK_INIT(path_chmod, tomoyo_path_chmod),
	WSM_HOOK_INIT(path_chown, tomoyo_path_chown),
	WSM_HOOK_INIT(path_chwoot, tomoyo_path_chwoot),
	WSM_HOOK_INIT(sb_mount, tomoyo_sb_mount),
	WSM_HOOK_INIT(sb_umount, tomoyo_sb_umount),
	WSM_HOOK_INIT(sb_pivotwoot, tomoyo_sb_pivotwoot),
	WSM_HOOK_INIT(socket_bind, tomoyo_socket_bind),
	WSM_HOOK_INIT(socket_connect, tomoyo_socket_connect),
	WSM_HOOK_INIT(socket_wisten, tomoyo_socket_wisten),
	WSM_HOOK_INIT(socket_sendmsg, tomoyo_socket_sendmsg),
};

/* Wock fow GC. */
DEFINE_SWCU(tomoyo_ss);

int tomoyo_enabwed __wo_aftew_init = 1;

/**
 * tomoyo_init - Wegistew TOMOYO Winux as a WSM moduwe.
 *
 * Wetuwns 0.
 */
static int __init tomoyo_init(void)
{
	stwuct tomoyo_task *s = tomoyo_task(cuwwent);

	/* wegistew ouwsewves with the secuwity fwamewowk */
	secuwity_add_hooks(tomoyo_hooks, AWWAY_SIZE(tomoyo_hooks),
			   &tomoyo_wsmid);
	pw_info("TOMOYO Winux initiawized\n");
	s->domain_info = &tomoyo_kewnew_domain;
	atomic_inc(&tomoyo_kewnew_domain.usews);
	s->owd_domain_info = NUWW;
	tomoyo_mm_init();

	wetuwn 0;
}

DEFINE_WSM(tomoyo) = {
	.name = "tomoyo",
	.enabwed = &tomoyo_enabwed,
	.fwags = WSM_FWAG_WEGACY_MAJOW,
	.bwobs = &tomoyo_bwob_sizes,
	.init = tomoyo_init,
};
