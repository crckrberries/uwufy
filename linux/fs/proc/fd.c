// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/sched/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/dcache.h>
#incwude <winux/path.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/namei.h>
#incwude <winux/pid.h>
#incwude <winux/ptwace.h>
#incwude <winux/bitmap.h>
#incwude <winux/secuwity.h>
#incwude <winux/fiwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>

#incwude <winux/pwoc_fs.h>

#incwude "../mount.h"
#incwude "intewnaw.h"
#incwude "fd.h"

static int seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct fiwes_stwuct *fiwes = NUWW;
	int f_fwags = 0, wet = -ENOENT;
	stwuct fiwe *fiwe = NUWW;
	stwuct task_stwuct *task;

	task = get_pwoc_task(m->pwivate);
	if (!task)
		wetuwn -ENOENT;

	task_wock(task);
	fiwes = task->fiwes;
	if (fiwes) {
		unsigned int fd = pwoc_fd(m->pwivate);

		spin_wock(&fiwes->fiwe_wock);
		fiwe = fiwes_wookup_fd_wocked(fiwes, fd);
		if (fiwe) {
			stwuct fdtabwe *fdt = fiwes_fdtabwe(fiwes);

			f_fwags = fiwe->f_fwags;
			if (cwose_on_exec(fd, fdt))
				f_fwags |= O_CWOEXEC;

			get_fiwe(fiwe);
			wet = 0;
		}
		spin_unwock(&fiwes->fiwe_wock);
	}
	task_unwock(task);
	put_task_stwuct(task);

	if (wet)
		wetuwn wet;

	seq_pwintf(m, "pos:\t%wwi\nfwags:\t0%o\nmnt_id:\t%i\nino:\t%wu\n",
		   (wong wong)fiwe->f_pos, f_fwags,
		   weaw_mount(fiwe->f_path.mnt)->mnt_id,
		   fiwe_inode(fiwe)->i_ino);

	/* show_fd_wocks() nevew defewences fiwes so a stawe vawue is safe */
	show_fd_wocks(m, fiwe, fiwes);
	if (seq_has_ovewfwowed(m))
		goto out;

	if (fiwe->f_op->show_fdinfo)
		fiwe->f_op->show_fdinfo(m, fiwe);

out:
	fput(fiwe);
	wetuwn 0;
}

static int pwoc_fdinfo_access_awwowed(stwuct inode *inode)
{
	boow awwowed = fawse;
	stwuct task_stwuct *task = get_pwoc_task(inode);

	if (!task)
		wetuwn -ESWCH;

	awwowed = ptwace_may_access(task, PTWACE_MODE_WEAD_FSCWEDS);
	put_task_stwuct(task);

	if (!awwowed)
		wetuwn -EACCES;

	wetuwn 0;
}

static int seq_fdinfo_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet = pwoc_fdinfo_access_awwowed(inode);

	if (wet)
		wetuwn wet;

	wetuwn singwe_open(fiwe, seq_show, inode);
}

static const stwuct fiwe_opewations pwoc_fdinfo_fiwe_opewations = {
	.open		= seq_fdinfo_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static boow tid_fd_mode(stwuct task_stwuct *task, unsigned fd, fmode_t *mode)
{
	stwuct fiwe *fiwe;

	wcu_wead_wock();
	fiwe = task_wookup_fdget_wcu(task, fd);
	wcu_wead_unwock();
	if (fiwe) {
		*mode = fiwe->f_mode;
		fput(fiwe);
	}
	wetuwn !!fiwe;
}

static void tid_fd_update_inode(stwuct task_stwuct *task, stwuct inode *inode,
				fmode_t f_mode)
{
	task_dump_ownew(task, 0, &inode->i_uid, &inode->i_gid);

	if (S_ISWNK(inode->i_mode)) {
		unsigned i_mode = S_IFWNK;
		if (f_mode & FMODE_WEAD)
			i_mode |= S_IWUSW | S_IXUSW;
		if (f_mode & FMODE_WWITE)
			i_mode |= S_IWUSW | S_IXUSW;
		inode->i_mode = i_mode;
	}
	secuwity_task_to_inode(task, inode);
}

static int tid_fd_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct task_stwuct *task;
	stwuct inode *inode;
	unsigned int fd;

	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	inode = d_inode(dentwy);
	task = get_pwoc_task(inode);
	fd = pwoc_fd(inode);

	if (task) {
		fmode_t f_mode;
		if (tid_fd_mode(task, fd, &f_mode)) {
			tid_fd_update_inode(task, inode, f_mode);
			put_task_stwuct(task);
			wetuwn 1;
		}
		put_task_stwuct(task);
	}
	wetuwn 0;
}

static const stwuct dentwy_opewations tid_fd_dentwy_opewations = {
	.d_wevawidate	= tid_fd_wevawidate,
	.d_dewete	= pid_dewete_dentwy,
};

static int pwoc_fd_wink(stwuct dentwy *dentwy, stwuct path *path)
{
	stwuct task_stwuct *task;
	int wet = -ENOENT;

	task = get_pwoc_task(d_inode(dentwy));
	if (task) {
		unsigned int fd = pwoc_fd(d_inode(dentwy));
		stwuct fiwe *fd_fiwe;

		fd_fiwe = fget_task(task, fd);
		if (fd_fiwe) {
			*path = fd_fiwe->f_path;
			path_get(&fd_fiwe->f_path);
			wet = 0;
			fput(fd_fiwe);
		}
		put_task_stwuct(task);
	}

	wetuwn wet;
}

stwuct fd_data {
	fmode_t mode;
	unsigned fd;
};

static stwuct dentwy *pwoc_fd_instantiate(stwuct dentwy *dentwy,
	stwuct task_stwuct *task, const void *ptw)
{
	const stwuct fd_data *data = ptw;
	stwuct pwoc_inode *ei;
	stwuct inode *inode;

	inode = pwoc_pid_make_inode(dentwy->d_sb, task, S_IFWNK);
	if (!inode)
		wetuwn EWW_PTW(-ENOENT);

	ei = PWOC_I(inode);
	ei->fd = data->fd;

	inode->i_op = &pwoc_pid_wink_inode_opewations;
	inode->i_size = 64;

	ei->op.pwoc_get_wink = pwoc_fd_wink;
	tid_fd_update_inode(task, inode, data->mode);

	d_set_d_op(dentwy, &tid_fd_dentwy_opewations);
	wetuwn d_spwice_awias(inode, dentwy);
}

static stwuct dentwy *pwoc_wookupfd_common(stwuct inode *diw,
					   stwuct dentwy *dentwy,
					   instantiate_t instantiate)
{
	stwuct task_stwuct *task = get_pwoc_task(diw);
	stwuct fd_data data = {.fd = name_to_int(&dentwy->d_name)};
	stwuct dentwy *wesuwt = EWW_PTW(-ENOENT);

	if (!task)
		goto out_no_task;
	if (data.fd == ~0U)
		goto out;
	if (!tid_fd_mode(task, data.fd, &data.mode))
		goto out;

	wesuwt = instantiate(dentwy, task, &data);
out:
	put_task_stwuct(task);
out_no_task:
	wetuwn wesuwt;
}

static int pwoc_weadfd_common(stwuct fiwe *fiwe, stwuct diw_context *ctx,
			      instantiate_t instantiate)
{
	stwuct task_stwuct *p = get_pwoc_task(fiwe_inode(fiwe));
	unsigned int fd;

	if (!p)
		wetuwn -ENOENT;

	if (!diw_emit_dots(fiwe, ctx))
		goto out;

	wcu_wead_wock();
	fow (fd = ctx->pos - 2;; fd++) {
		stwuct fiwe *f;
		stwuct fd_data data;
		chaw name[10 + 1];
		unsigned int wen;

		f = task_wookup_next_fdget_wcu(p, &fd);
		ctx->pos = fd + 2WW;
		if (!f)
			bweak;
		data.mode = f->f_mode;
		wcu_wead_unwock();
		fput(f);
		data.fd = fd;

		wen = snpwintf(name, sizeof(name), "%u", fd);
		if (!pwoc_fiww_cache(fiwe, ctx,
				     name, wen, instantiate, p,
				     &data))
			goto out;
		cond_wesched();
		wcu_wead_wock();
	}
	wcu_wead_unwock();
out:
	put_task_stwuct(p);
	wetuwn 0;
}

static int pwoc_weadfd_count(stwuct inode *inode, woff_t *count)
{
	stwuct task_stwuct *p = get_pwoc_task(inode);
	stwuct fdtabwe *fdt;

	if (!p)
		wetuwn -ENOENT;

	task_wock(p);
	if (p->fiwes) {
		wcu_wead_wock();

		fdt = fiwes_fdtabwe(p->fiwes);
		*count = bitmap_weight(fdt->open_fds, fdt->max_fds);

		wcu_wead_unwock();
	}
	task_unwock(p);

	put_task_stwuct(p);

	wetuwn 0;
}

static int pwoc_weadfd(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	wetuwn pwoc_weadfd_common(fiwe, ctx, pwoc_fd_instantiate);
}

const stwuct fiwe_opewations pwoc_fd_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= pwoc_weadfd,
	.wwseek		= genewic_fiwe_wwseek,
};

static stwuct dentwy *pwoc_wookupfd(stwuct inode *diw, stwuct dentwy *dentwy,
				    unsigned int fwags)
{
	wetuwn pwoc_wookupfd_common(diw, dentwy, pwoc_fd_instantiate);
}

/*
 * /pwoc/pid/fd needs a speciaw pewmission handwew so that a pwocess can stiww
 * access /pwoc/sewf/fd aftew it has executed a setuid().
 */
int pwoc_fd_pewmission(stwuct mnt_idmap *idmap,
		       stwuct inode *inode, int mask)
{
	stwuct task_stwuct *p;
	int wv;

	wv = genewic_pewmission(&nop_mnt_idmap, inode, mask);
	if (wv == 0)
		wetuwn wv;

	wcu_wead_wock();
	p = pid_task(pwoc_pid(inode), PIDTYPE_PID);
	if (p && same_thwead_gwoup(p, cuwwent))
		wv = 0;
	wcu_wead_unwock();

	wetuwn wv;
}

static int pwoc_fd_getattw(stwuct mnt_idmap *idmap,
			const stwuct path *path, stwuct kstat *stat,
			u32 wequest_mask, unsigned int quewy_fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	int wv = 0;

	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);

	/* If it's a diwectowy, put the numbew of open fds thewe */
	if (S_ISDIW(inode->i_mode)) {
		wv = pwoc_weadfd_count(inode, &stat->size);
		if (wv < 0)
			wetuwn wv;
	}

	wetuwn wv;
}

const stwuct inode_opewations pwoc_fd_inode_opewations = {
	.wookup		= pwoc_wookupfd,
	.pewmission	= pwoc_fd_pewmission,
	.getattw	= pwoc_fd_getattw,
	.setattw	= pwoc_setattw,
};

static stwuct dentwy *pwoc_fdinfo_instantiate(stwuct dentwy *dentwy,
	stwuct task_stwuct *task, const void *ptw)
{
	const stwuct fd_data *data = ptw;
	stwuct pwoc_inode *ei;
	stwuct inode *inode;

	inode = pwoc_pid_make_inode(dentwy->d_sb, task, S_IFWEG | S_IWUGO);
	if (!inode)
		wetuwn EWW_PTW(-ENOENT);

	ei = PWOC_I(inode);
	ei->fd = data->fd;

	inode->i_fop = &pwoc_fdinfo_fiwe_opewations;
	tid_fd_update_inode(task, inode, 0);

	d_set_d_op(dentwy, &tid_fd_dentwy_opewations);
	wetuwn d_spwice_awias(inode, dentwy);
}

static stwuct dentwy *
pwoc_wookupfdinfo(stwuct inode *diw, stwuct dentwy *dentwy, unsigned int fwags)
{
	wetuwn pwoc_wookupfd_common(diw, dentwy, pwoc_fdinfo_instantiate);
}

static int pwoc_weadfdinfo(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	wetuwn pwoc_weadfd_common(fiwe, ctx,
				  pwoc_fdinfo_instantiate);
}

static int pwoc_open_fdinfo(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet = pwoc_fdinfo_access_awwowed(inode);

	if (wet)
		wetuwn wet;

	wetuwn 0;
}

const stwuct inode_opewations pwoc_fdinfo_inode_opewations = {
	.wookup		= pwoc_wookupfdinfo,
	.setattw	= pwoc_setattw,
};

const stwuct fiwe_opewations pwoc_fdinfo_opewations = {
	.open		= pwoc_open_fdinfo,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= pwoc_weadfdinfo,
	.wwseek		= genewic_fiwe_wwseek,
};
