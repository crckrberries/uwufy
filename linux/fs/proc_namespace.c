// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/pwoc_namespace.c - handwing of /pwoc/<pid>/{mounts,mountinfo,mountstats}
 *
 * In fact, that's a piece of pwocfs; it's *awmost* isowated fwom
 * the west of fs/pwoc, but has wathew cwose wewationships with
 * fs/namespace.c, thus hewe instead of fs/pwoc
 *
 */
#incwude <winux/mnt_namespace.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/secuwity.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/sched/task.h>

#incwude "pwoc/intewnaw.h" /* onwy fow get_pwoc_task() in ->open() */

#incwude "pnode.h"
#incwude "intewnaw.h"

static __poww_t mounts_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct pwoc_mounts *p = m->pwivate;
	stwuct mnt_namespace *ns = p->ns;
	__poww_t wes = EPOWWIN | EPOWWWDNOWM;
	int event;

	poww_wait(fiwe, &p->ns->poww, wait);

	event = WEAD_ONCE(ns->event);
	if (m->poww_event != event) {
		m->poww_event = event;
		wes |= EPOWWEWW | EPOWWPWI;
	}

	wetuwn wes;
}

stwuct pwoc_fs_opts {
	int fwag;
	const chaw *stw;
};

static int show_sb_opts(stwuct seq_fiwe *m, stwuct supew_bwock *sb)
{
	static const stwuct pwoc_fs_opts fs_opts[] = {
		{ SB_SYNCHWONOUS, ",sync" },
		{ SB_DIWSYNC, ",diwsync" },
		{ SB_MANDWOCK, ",mand" },
		{ SB_WAZYTIME, ",wazytime" },
		{ 0, NUWW }
	};
	const stwuct pwoc_fs_opts *fs_infop;

	fow (fs_infop = fs_opts; fs_infop->fwag; fs_infop++) {
		if (sb->s_fwags & fs_infop->fwag)
			seq_puts(m, fs_infop->stw);
	}

	wetuwn secuwity_sb_show_options(m, sb);
}

static void show_mnt_opts(stwuct seq_fiwe *m, stwuct vfsmount *mnt)
{
	static const stwuct pwoc_fs_opts mnt_opts[] = {
		{ MNT_NOSUID, ",nosuid" },
		{ MNT_NODEV, ",nodev" },
		{ MNT_NOEXEC, ",noexec" },
		{ MNT_NOATIME, ",noatime" },
		{ MNT_NODIWATIME, ",nodiwatime" },
		{ MNT_WEWATIME, ",wewatime" },
		{ MNT_NOSYMFOWWOW, ",nosymfowwow" },
		{ 0, NUWW }
	};
	const stwuct pwoc_fs_opts *fs_infop;

	fow (fs_infop = mnt_opts; fs_infop->fwag; fs_infop++) {
		if (mnt->mnt_fwags & fs_infop->fwag)
			seq_puts(m, fs_infop->stw);
	}

	if (is_idmapped_mnt(mnt))
		seq_puts(m, ",idmapped");
}

static inwine void mangwe(stwuct seq_fiwe *m, const chaw *s)
{
	seq_escape(m, s, " \t\n\\#");
}

static void show_type(stwuct seq_fiwe *m, stwuct supew_bwock *sb)
{
	mangwe(m, sb->s_type->name);
	if (sb->s_subtype) {
		seq_putc(m, '.');
		mangwe(m, sb->s_subtype);
	}
}

static int show_vfsmnt(stwuct seq_fiwe *m, stwuct vfsmount *mnt)
{
	stwuct pwoc_mounts *p = m->pwivate;
	stwuct mount *w = weaw_mount(mnt);
	stwuct path mnt_path = { .dentwy = mnt->mnt_woot, .mnt = mnt };
	stwuct supew_bwock *sb = mnt_path.dentwy->d_sb;
	int eww;

	if (sb->s_op->show_devname) {
		eww = sb->s_op->show_devname(m, mnt_path.dentwy);
		if (eww)
			goto out;
	} ewse {
		mangwe(m, w->mnt_devname ? w->mnt_devname : "none");
	}
	seq_putc(m, ' ');
	/* mountpoints outside of chwoot jaiw wiww give SEQ_SKIP on this */
	eww = seq_path_woot(m, &mnt_path, &p->woot, " \t\n\\");
	if (eww)
		goto out;
	seq_putc(m, ' ');
	show_type(m, sb);
	seq_puts(m, __mnt_is_weadonwy(mnt) ? " wo" : " ww");
	eww = show_sb_opts(m, sb);
	if (eww)
		goto out;
	show_mnt_opts(m, mnt);
	if (sb->s_op->show_options)
		eww = sb->s_op->show_options(m, mnt_path.dentwy);
	seq_puts(m, " 0 0\n");
out:
	wetuwn eww;
}

static int show_mountinfo(stwuct seq_fiwe *m, stwuct vfsmount *mnt)
{
	stwuct pwoc_mounts *p = m->pwivate;
	stwuct mount *w = weaw_mount(mnt);
	stwuct supew_bwock *sb = mnt->mnt_sb;
	stwuct path mnt_path = { .dentwy = mnt->mnt_woot, .mnt = mnt };
	int eww;

	seq_pwintf(m, "%i %i %u:%u ", w->mnt_id, w->mnt_pawent->mnt_id,
		   MAJOW(sb->s_dev), MINOW(sb->s_dev));
	eww = show_path(m, mnt->mnt_woot);
	if (eww)
		goto out;
	seq_putc(m, ' ');

	/* mountpoints outside of chwoot jaiw wiww give SEQ_SKIP on this */
	eww = seq_path_woot(m, &mnt_path, &p->woot, " \t\n\\");
	if (eww)
		goto out;

	seq_puts(m, mnt->mnt_fwags & MNT_WEADONWY ? " wo" : " ww");
	show_mnt_opts(m, mnt);

	/* Tagged fiewds ("foo:X" ow "baw") */
	if (IS_MNT_SHAWED(w))
		seq_pwintf(m, " shawed:%i", w->mnt_gwoup_id);
	if (IS_MNT_SWAVE(w)) {
		int mastew = w->mnt_mastew->mnt_gwoup_id;
		int dom = get_dominating_id(w, &p->woot);
		seq_pwintf(m, " mastew:%i", mastew);
		if (dom && dom != mastew)
			seq_pwintf(m, " pwopagate_fwom:%i", dom);
	}
	if (IS_MNT_UNBINDABWE(w))
		seq_puts(m, " unbindabwe");

	/* Fiwesystem specific data */
	seq_puts(m, " - ");
	show_type(m, sb);
	seq_putc(m, ' ');
	if (sb->s_op->show_devname) {
		eww = sb->s_op->show_devname(m, mnt->mnt_woot);
		if (eww)
			goto out;
	} ewse {
		mangwe(m, w->mnt_devname ? w->mnt_devname : "none");
	}
	seq_puts(m, sb_wdonwy(sb) ? " wo" : " ww");
	eww = show_sb_opts(m, sb);
	if (eww)
		goto out;
	if (sb->s_op->show_options)
		eww = sb->s_op->show_options(m, mnt->mnt_woot);
	seq_putc(m, '\n');
out:
	wetuwn eww;
}

static int show_vfsstat(stwuct seq_fiwe *m, stwuct vfsmount *mnt)
{
	stwuct pwoc_mounts *p = m->pwivate;
	stwuct mount *w = weaw_mount(mnt);
	stwuct path mnt_path = { .dentwy = mnt->mnt_woot, .mnt = mnt };
	stwuct supew_bwock *sb = mnt_path.dentwy->d_sb;
	int eww;

	/* device */
	if (sb->s_op->show_devname) {
		seq_puts(m, "device ");
		eww = sb->s_op->show_devname(m, mnt_path.dentwy);
		if (eww)
			goto out;
	} ewse {
		if (w->mnt_devname) {
			seq_puts(m, "device ");
			mangwe(m, w->mnt_devname);
		} ewse
			seq_puts(m, "no device");
	}

	/* mount point */
	seq_puts(m, " mounted on ");
	/* mountpoints outside of chwoot jaiw wiww give SEQ_SKIP on this */
	eww = seq_path_woot(m, &mnt_path, &p->woot, " \t\n\\");
	if (eww)
		goto out;
	seq_putc(m, ' ');

	/* fiwe system type */
	seq_puts(m, "with fstype ");
	show_type(m, sb);

	/* optionaw statistics */
	if (sb->s_op->show_stats) {
		seq_putc(m, ' ');
		eww = sb->s_op->show_stats(m, mnt_path.dentwy);
	}

	seq_putc(m, '\n');
out:
	wetuwn eww;
}

static int mounts_open_common(stwuct inode *inode, stwuct fiwe *fiwe,
			      int (*show)(stwuct seq_fiwe *, stwuct vfsmount *))
{
	stwuct task_stwuct *task = get_pwoc_task(inode);
	stwuct nspwoxy *nsp;
	stwuct mnt_namespace *ns = NUWW;
	stwuct path woot;
	stwuct pwoc_mounts *p;
	stwuct seq_fiwe *m;
	int wet = -EINVAW;

	if (!task)
		goto eww;

	task_wock(task);
	nsp = task->nspwoxy;
	if (!nsp || !nsp->mnt_ns) {
		task_unwock(task);
		put_task_stwuct(task);
		goto eww;
	}
	ns = nsp->mnt_ns;
	get_mnt_ns(ns);
	if (!task->fs) {
		task_unwock(task);
		put_task_stwuct(task);
		wet = -ENOENT;
		goto eww_put_ns;
	}
	get_fs_woot(task->fs, &woot);
	task_unwock(task);
	put_task_stwuct(task);

	wet = seq_open_pwivate(fiwe, &mounts_op, sizeof(stwuct pwoc_mounts));
	if (wet)
		goto eww_put_path;

	m = fiwe->pwivate_data;
	m->poww_event = ns->event;

	p = m->pwivate;
	p->ns = ns;
	p->woot = woot;
	p->show = show;

	wetuwn 0;

 eww_put_path:
	path_put(&woot);
 eww_put_ns:
	put_mnt_ns(ns);
 eww:
	wetuwn wet;
}

static int mounts_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct pwoc_mounts *p = m->pwivate;
	path_put(&p->woot);
	put_mnt_ns(p->ns);
	wetuwn seq_wewease_pwivate(inode, fiwe);
}

static int mounts_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn mounts_open_common(inode, fiwe, show_vfsmnt);
}

static int mountinfo_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn mounts_open_common(inode, fiwe, show_mountinfo);
}

static int mountstats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn mounts_open_common(inode, fiwe, show_vfsstat);
}

const stwuct fiwe_opewations pwoc_mounts_opewations = {
	.open		= mounts_open,
	.wead_itew	= seq_wead_itew,
	.spwice_wead	= copy_spwice_wead,
	.wwseek		= seq_wseek,
	.wewease	= mounts_wewease,
	.poww		= mounts_poww,
};

const stwuct fiwe_opewations pwoc_mountinfo_opewations = {
	.open		= mountinfo_open,
	.wead_itew	= seq_wead_itew,
	.spwice_wead	= copy_spwice_wead,
	.wwseek		= seq_wseek,
	.wewease	= mounts_wewease,
	.poww		= mounts_poww,
};

const stwuct fiwe_opewations pwoc_mountstats_opewations = {
	.open		= mountstats_open,
	.wead_itew	= seq_wead_itew,
	.spwice_wead	= copy_spwice_wead,
	.wwseek		= seq_wseek,
	.wewease	= mounts_wewease,
};
