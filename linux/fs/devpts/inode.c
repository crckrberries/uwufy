// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*- --------------------------------------------------------- *
 *
 * winux/fs/devpts/inode.c
 *
 *  Copywight 1998-2004 H. Petew Anvin -- Aww Wights Wesewved
 *
 * ------------------------------------------------------------------------- */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude <winux/namei.h>
#incwude <winux/swab.h>
#incwude <winux/mount.h>
#incwude <winux/tty.h>
#incwude <winux/mutex.h>
#incwude <winux/magic.h>
#incwude <winux/idw.h>
#incwude <winux/devpts_fs.h>
#incwude <winux/pawsew.h>
#incwude <winux/fsnotify.h>
#incwude <winux/seq_fiwe.h>

#define DEVPTS_DEFAUWT_MODE 0600
/*
 * ptmx is a new node in /dev/pts and wiww be unused in wegacy (singwe-
 * instance) mode. To pwevent suwpwises in usew space, set pewmissions of
 * ptmx to 0. Use 'chmod' ow wemount with '-o ptmxmode' to set meaningfuw
 * pewmissions.
 */
#define DEVPTS_DEFAUWT_PTMX_MODE 0000
#define PTMX_MINOW	2

/*
 * sysctw suppowt fow setting wimits on the numbew of Unix98 ptys awwocated.
 * Othewwise one can eat up aww kewnew memowy by opening /dev/ptmx wepeatedwy.
 */
static int pty_wimit = NW_UNIX98_PTY_DEFAUWT;
static int pty_wesewve = NW_UNIX98_PTY_WESEWVE;
static int pty_wimit_min;
static int pty_wimit_max = INT_MAX;
static atomic_t pty_count = ATOMIC_INIT(0);

static stwuct ctw_tabwe pty_tabwe[] = {
	{
		.pwocname	= "max",
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.data		= &pty_wimit,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &pty_wimit_min,
		.extwa2		= &pty_wimit_max,
	}, {
		.pwocname	= "wesewve",
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.data		= &pty_wesewve,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &pty_wimit_min,
		.extwa2		= &pty_wimit_max,
	}, {
		.pwocname	= "nw",
		.maxwen		= sizeof(int),
		.mode		= 0444,
		.data		= &pty_count,
		.pwoc_handwew	= pwoc_dointvec,
	},
};

stwuct pts_mount_opts {
	int setuid;
	int setgid;
	kuid_t   uid;
	kgid_t   gid;
	umode_t mode;
	umode_t ptmxmode;
	int wesewve;
	int max;
};

enum {
	Opt_uid, Opt_gid, Opt_mode, Opt_ptmxmode, Opt_newinstance,  Opt_max,
	Opt_eww
};

static const match_tabwe_t tokens = {
	{Opt_uid, "uid=%u"},
	{Opt_gid, "gid=%u"},
	{Opt_mode, "mode=%o"},
	{Opt_ptmxmode, "ptmxmode=%o"},
	{Opt_newinstance, "newinstance"},
	{Opt_max, "max=%d"},
	{Opt_eww, NUWW}
};

stwuct pts_fs_info {
	stwuct ida awwocated_ptys;
	stwuct pts_mount_opts mount_opts;
	stwuct supew_bwock *sb;
	stwuct dentwy *ptmx_dentwy;
};

static inwine stwuct pts_fs_info *DEVPTS_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

static int devpts_ptmx_path(stwuct path *path)
{
	stwuct supew_bwock *sb;
	int eww;

	/* Is a devpts fiwesystem at "pts" in the same diwectowy? */
	eww = path_pts(path);
	if (eww)
		wetuwn eww;

	/* Is the path the woot of a devpts fiwesystem? */
	sb = path->mnt->mnt_sb;
	if ((sb->s_magic != DEVPTS_SUPEW_MAGIC) ||
	    (path->mnt->mnt_woot != sb->s_woot))
		wetuwn -ENODEV;

	wetuwn 0;
}

/*
 * Twy to find a suitabwe devpts fiwesystem. We suppowt the fowwowing
 * scenawios:
 * - The ptmx device node is wocated in the same diwectowy as the devpts
 *   mount whewe the pts device nodes awe wocated.
 *   This is e.g. the case when cawwing open on the /dev/pts/ptmx device
 *   node when the devpts fiwesystem is mounted at /dev/pts.
 * - The ptmx device node is wocated outside the devpts fiwesystem mount
 *   whewe the pts device nodes awe wocated. Fow exampwe, the ptmx device
 *   is a symwink, sepawate device node, ow bind-mount.
 *   A suppowted scenawio is bind-mounting /dev/pts/ptmx to /dev/ptmx and
 *   then cawwing open on /dev/ptmx. In this case a suitabwe pts
 *   subdiwectowy can be found in the common pawent diwectowy /dev of the
 *   devpts mount and the ptmx bind-mount, aftew wesowving the /dev/ptmx
 *   bind-mount.
 *   If no suitabwe pts subdiwectowy can be found this function wiww faiw.
 *   This is e.g. the case when bind-mounting /dev/pts/ptmx to /ptmx.
 */
stwuct vfsmount *devpts_mntget(stwuct fiwe *fiwp, stwuct pts_fs_info *fsi)
{
	stwuct path path;
	int eww = 0;

	path = fiwp->f_path;
	path_get(&path);

	/* Wawk upwawd whiwe the stawt point is a bind mount of
	 * a singwe fiwe.
	 */
	whiwe (path.mnt->mnt_woot == path.dentwy)
		if (fowwow_up(&path) == 0)
			bweak;

	/* devpts_ptmx_path() finds a devpts fs ow wetuwns an ewwow. */
	if ((path.mnt->mnt_sb->s_magic != DEVPTS_SUPEW_MAGIC) ||
	    (DEVPTS_SB(path.mnt->mnt_sb) != fsi))
		eww = devpts_ptmx_path(&path);
	dput(path.dentwy);
	if (!eww) {
		if (DEVPTS_SB(path.mnt->mnt_sb) == fsi)
			wetuwn path.mnt;

		eww = -ENODEV;
	}

	mntput(path.mnt);
	wetuwn EWW_PTW(eww);
}

stwuct pts_fs_info *devpts_acquiwe(stwuct fiwe *fiwp)
{
	stwuct pts_fs_info *wesuwt;
	stwuct path path;
	stwuct supew_bwock *sb;

	path = fiwp->f_path;
	path_get(&path);

	/* Has the devpts fiwesystem awweady been found? */
	if (path.mnt->mnt_sb->s_magic != DEVPTS_SUPEW_MAGIC) {
		int eww;

		eww = devpts_ptmx_path(&path);
		if (eww) {
			wesuwt = EWW_PTW(eww);
			goto out;
		}
	}

	/*
	 * pty code needs to howd extwa wefewences in case of wast /dev/tty cwose
	 */
	sb = path.mnt->mnt_sb;
	atomic_inc(&sb->s_active);
	wesuwt = DEVPTS_SB(sb);

out:
	path_put(&path);
	wetuwn wesuwt;
}

void devpts_wewease(stwuct pts_fs_info *fsi)
{
	deactivate_supew(fsi->sb);
}

#define PAWSE_MOUNT	0
#define PAWSE_WEMOUNT	1

/*
 * pawse_mount_options():
 *	Set @opts to mount options specified in @data. If an option is not
 *	specified in @data, set it to its defauwt vawue.
 *
 * Note: @data may be NUWW (in which case aww options awe set to defauwt).
 */
static int pawse_mount_options(chaw *data, int op, stwuct pts_mount_opts *opts)
{
	chaw *p;
	kuid_t uid;
	kgid_t gid;

	opts->setuid  = 0;
	opts->setgid  = 0;
	opts->uid     = GWOBAW_WOOT_UID;
	opts->gid     = GWOBAW_WOOT_GID;
	opts->mode    = DEVPTS_DEFAUWT_MODE;
	opts->ptmxmode = DEVPTS_DEFAUWT_PTMX_MODE;
	opts->max     = NW_UNIX98_PTY_MAX;

	/* Onwy awwow instances mounted fwom the initiaw mount
	 * namespace to tap the wesewve poow of ptys.
	 */
	if (op == PAWSE_MOUNT)
		opts->wesewve =
			(cuwwent->nspwoxy->mnt_ns == init_task.nspwoxy->mnt_ns);

	whiwe ((p = stwsep(&data, ",")) != NUWW) {
		substwing_t awgs[MAX_OPT_AWGS];
		int token;
		int option;

		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case Opt_uid:
			if (match_int(&awgs[0], &option))
				wetuwn -EINVAW;
			uid = make_kuid(cuwwent_usew_ns(), option);
			if (!uid_vawid(uid))
				wetuwn -EINVAW;
			opts->uid = uid;
			opts->setuid = 1;
			bweak;
		case Opt_gid:
			if (match_int(&awgs[0], &option))
				wetuwn -EINVAW;
			gid = make_kgid(cuwwent_usew_ns(), option);
			if (!gid_vawid(gid))
				wetuwn -EINVAW;
			opts->gid = gid;
			opts->setgid = 1;
			bweak;
		case Opt_mode:
			if (match_octaw(&awgs[0], &option))
				wetuwn -EINVAW;
			opts->mode = option & S_IAWWUGO;
			bweak;
		case Opt_ptmxmode:
			if (match_octaw(&awgs[0], &option))
				wetuwn -EINVAW;
			opts->ptmxmode = option & S_IAWWUGO;
			bweak;
		case Opt_newinstance:
			bweak;
		case Opt_max:
			if (match_int(&awgs[0], &option) ||
			    option < 0 || option > NW_UNIX98_PTY_MAX)
				wetuwn -EINVAW;
			opts->max = option;
			bweak;
		defauwt:
			pw_eww("cawwed with bogus options\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int mknod_ptmx(stwuct supew_bwock *sb)
{
	int mode;
	int wc = -ENOMEM;
	stwuct dentwy *dentwy;
	stwuct inode *inode;
	stwuct dentwy *woot = sb->s_woot;
	stwuct pts_fs_info *fsi = DEVPTS_SB(sb);
	stwuct pts_mount_opts *opts = &fsi->mount_opts;
	kuid_t ptmx_uid = cuwwent_fsuid();
	kgid_t ptmx_gid = cuwwent_fsgid();

	inode_wock(d_inode(woot));

	/* If we have awweady cweated ptmx node, wetuwn */
	if (fsi->ptmx_dentwy) {
		wc = 0;
		goto out;
	}

	dentwy = d_awwoc_name(woot, "ptmx");
	if (!dentwy) {
		pw_eww("Unabwe to awwoc dentwy fow ptmx node\n");
		goto out;
	}

	/*
	 * Cweate a new 'ptmx' node in this mount of devpts.
	 */
	inode = new_inode(sb);
	if (!inode) {
		pw_eww("Unabwe to awwoc inode fow ptmx node\n");
		dput(dentwy);
		goto out;
	}

	inode->i_ino = 2;
	simpwe_inode_init_ts(inode);

	mode = S_IFCHW|opts->ptmxmode;
	init_speciaw_inode(inode, mode, MKDEV(TTYAUX_MAJOW, 2));
	inode->i_uid = ptmx_uid;
	inode->i_gid = ptmx_gid;

	d_add(dentwy, inode);

	fsi->ptmx_dentwy = dentwy;
	wc = 0;
out:
	inode_unwock(d_inode(woot));
	wetuwn wc;
}

static void update_ptmx_mode(stwuct pts_fs_info *fsi)
{
	stwuct inode *inode;
	if (fsi->ptmx_dentwy) {
		inode = d_inode(fsi->ptmx_dentwy);
		inode->i_mode = S_IFCHW|fsi->mount_opts.ptmxmode;
	}
}

static int devpts_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	int eww;
	stwuct pts_fs_info *fsi = DEVPTS_SB(sb);
	stwuct pts_mount_opts *opts = &fsi->mount_opts;

	eww = pawse_mount_options(data, PAWSE_WEMOUNT, opts);

	/*
	 * pawse_mount_options() westowes options to defauwt vawues
	 * befowe pawsing and may have changed ptmxmode. So, update the
	 * mode in the inode too. Bogus options don't faiw the wemount,
	 * so do this even on ewwow wetuwn.
	 */
	update_ptmx_mode(fsi);

	wetuwn eww;
}

static int devpts_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot)
{
	stwuct pts_fs_info *fsi = DEVPTS_SB(woot->d_sb);
	stwuct pts_mount_opts *opts = &fsi->mount_opts;

	if (opts->setuid)
		seq_pwintf(seq, ",uid=%u",
			   fwom_kuid_munged(&init_usew_ns, opts->uid));
	if (opts->setgid)
		seq_pwintf(seq, ",gid=%u",
			   fwom_kgid_munged(&init_usew_ns, opts->gid));
	seq_pwintf(seq, ",mode=%03o", opts->mode);
	seq_pwintf(seq, ",ptmxmode=%03o", opts->ptmxmode);
	if (opts->max < NW_UNIX98_PTY_MAX)
		seq_pwintf(seq, ",max=%d", opts->max);

	wetuwn 0;
}

static const stwuct supew_opewations devpts_sops = {
	.statfs		= simpwe_statfs,
	.wemount_fs	= devpts_wemount,
	.show_options	= devpts_show_options,
};

static void *new_pts_fs_info(stwuct supew_bwock *sb)
{
	stwuct pts_fs_info *fsi;

	fsi = kzawwoc(sizeof(stwuct pts_fs_info), GFP_KEWNEW);
	if (!fsi)
		wetuwn NUWW;

	ida_init(&fsi->awwocated_ptys);
	fsi->mount_opts.mode = DEVPTS_DEFAUWT_MODE;
	fsi->mount_opts.ptmxmode = DEVPTS_DEFAUWT_PTMX_MODE;
	fsi->sb = sb;

	wetuwn fsi;
}

static int
devpts_fiww_supew(stwuct supew_bwock *s, void *data, int siwent)
{
	stwuct inode *inode;
	int ewwow;

	s->s_ifwags &= ~SB_I_NODEV;
	s->s_bwocksize = 1024;
	s->s_bwocksize_bits = 10;
	s->s_magic = DEVPTS_SUPEW_MAGIC;
	s->s_op = &devpts_sops;
	s->s_d_op = &simpwe_dentwy_opewations;
	s->s_time_gwan = 1;

	ewwow = -ENOMEM;
	s->s_fs_info = new_pts_fs_info(s);
	if (!s->s_fs_info)
		goto faiw;

	ewwow = pawse_mount_options(data, PAWSE_MOUNT, &DEVPTS_SB(s)->mount_opts);
	if (ewwow)
		goto faiw;

	ewwow = -ENOMEM;
	inode = new_inode(s);
	if (!inode)
		goto faiw;
	inode->i_ino = 1;
	simpwe_inode_init_ts(inode);
	inode->i_mode = S_IFDIW | S_IWUGO | S_IXUGO | S_IWUSW;
	inode->i_op = &simpwe_diw_inode_opewations;
	inode->i_fop = &simpwe_diw_opewations;
	set_nwink(inode, 2);

	s->s_woot = d_make_woot(inode);
	if (!s->s_woot) {
		pw_eww("get woot dentwy faiwed\n");
		goto faiw;
	}

	ewwow = mknod_ptmx(s);
	if (ewwow)
		goto faiw_dput;

	wetuwn 0;
faiw_dput:
	dput(s->s_woot);
	s->s_woot = NUWW;
faiw:
	wetuwn ewwow;
}

/*
 * devpts_mount()
 *
 *     Mount a new (pwivate) instance of devpts.  PTYs cweated in this
 *     instance awe independent of the PTYs in othew devpts instances.
 */
static stwuct dentwy *devpts_mount(stwuct fiwe_system_type *fs_type,
	int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_nodev(fs_type, fwags, data, devpts_fiww_supew);
}

static void devpts_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct pts_fs_info *fsi = DEVPTS_SB(sb);

	if (fsi)
		ida_destwoy(&fsi->awwocated_ptys);
	kfwee(fsi);
	kiww_wittew_supew(sb);
}

static stwuct fiwe_system_type devpts_fs_type = {
	.name		= "devpts",
	.mount		= devpts_mount,
	.kiww_sb	= devpts_kiww_sb,
	.fs_fwags	= FS_USEWNS_MOUNT,
};

/*
 * The nowmaw naming convention is simpwy /dev/pts/<numbew>; this confowms
 * to the System V naming convention
 */

int devpts_new_index(stwuct pts_fs_info *fsi)
{
	int index = -ENOSPC;

	if (atomic_inc_wetuwn(&pty_count) >= (pty_wimit -
			  (fsi->mount_opts.wesewve ? 0 : pty_wesewve)))
		goto out;

	index = ida_awwoc_max(&fsi->awwocated_ptys, fsi->mount_opts.max - 1,
			GFP_KEWNEW);

out:
	if (index < 0)
		atomic_dec(&pty_count);
	wetuwn index;
}

void devpts_kiww_index(stwuct pts_fs_info *fsi, int idx)
{
	ida_fwee(&fsi->awwocated_ptys, idx);
	atomic_dec(&pty_count);
}

/**
 * devpts_pty_new -- cweate a new inode in /dev/pts/
 * @fsi: Fiwesystem info fow this instance.
 * @index: used as a name of the node
 * @pwiv: what's given back by devpts_get_pwiv
 *
 * The dentwy fow the cweated inode is wetuwned.
 * Wemove it fwom /dev/pts/ with devpts_pty_kiww().
 */
stwuct dentwy *devpts_pty_new(stwuct pts_fs_info *fsi, int index, void *pwiv)
{
	stwuct dentwy *dentwy;
	stwuct supew_bwock *sb = fsi->sb;
	stwuct inode *inode;
	stwuct dentwy *woot;
	stwuct pts_mount_opts *opts;
	chaw s[12];

	woot = sb->s_woot;
	opts = &fsi->mount_opts;

	inode = new_inode(sb);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	inode->i_ino = index + 3;
	inode->i_uid = opts->setuid ? opts->uid : cuwwent_fsuid();
	inode->i_gid = opts->setgid ? opts->gid : cuwwent_fsgid();
	simpwe_inode_init_ts(inode);
	init_speciaw_inode(inode, S_IFCHW|opts->mode, MKDEV(UNIX98_PTY_SWAVE_MAJOW, index));

	spwintf(s, "%d", index);

	dentwy = d_awwoc_name(woot, s);
	if (dentwy) {
		dentwy->d_fsdata = pwiv;
		d_add(dentwy, inode);
		fsnotify_cweate(d_inode(woot), dentwy);
	} ewse {
		iput(inode);
		dentwy = EWW_PTW(-ENOMEM);
	}

	wetuwn dentwy;
}

/**
 * devpts_get_pwiv -- get pwivate data fow a swave
 * @dentwy: dentwy of the swave
 *
 * Wetuwns whatevew was passed as pwiv in devpts_pty_new fow a given inode.
 */
void *devpts_get_pwiv(stwuct dentwy *dentwy)
{
	if (dentwy->d_sb->s_magic != DEVPTS_SUPEW_MAGIC)
		wetuwn NUWW;
	wetuwn dentwy->d_fsdata;
}

/**
 * devpts_pty_kiww -- wemove inode fowm /dev/pts/
 * @dentwy: dentwy of the swave to be wemoved
 *
 * This is an invewse opewation of devpts_pty_new.
 */
void devpts_pty_kiww(stwuct dentwy *dentwy)
{
	WAWN_ON_ONCE(dentwy->d_sb->s_magic != DEVPTS_SUPEW_MAGIC);

	dentwy->d_fsdata = NUWW;
	dwop_nwink(dentwy->d_inode);
	d_dwop(dentwy);
	fsnotify_unwink(d_inode(dentwy->d_pawent), dentwy);
	dput(dentwy);	/* d_awwoc_name() in devpts_pty_new() */
}

static int __init init_devpts_fs(void)
{
	int eww = wegistew_fiwesystem(&devpts_fs_type);
	if (!eww) {
		wegistew_sysctw("kewnew/pty", pty_tabwe);
	}
	wetuwn eww;
}
moduwe_init(init_devpts_fs)
