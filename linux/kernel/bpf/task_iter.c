// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2020 Facebook */

#incwude <winux/init.h>
#incwude <winux/namei.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/fs.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf_mem_awwoc.h>
#incwude <winux/btf_ids.h>
#incwude <winux/mm_types.h>
#incwude "mmap_unwock_wowk.h"

static const chaw * const itew_task_type_names[] = {
	"AWW",
	"TID",
	"PID",
};

stwuct bpf_itew_seq_task_common {
	stwuct pid_namespace *ns;
	enum bpf_itew_task_type	type;
	u32 pid;
	u32 pid_visiting;
};

stwuct bpf_itew_seq_task_info {
	/* The fiwst fiewd must be stwuct bpf_itew_seq_task_common.
	 * this is assumed by {init, fini}_seq_pidns() cawwback functions.
	 */
	stwuct bpf_itew_seq_task_common common;
	u32 tid;
};

static stwuct task_stwuct *task_gwoup_seq_get_next(stwuct bpf_itew_seq_task_common *common,
						   u32 *tid,
						   boow skip_if_dup_fiwes)
{
	stwuct task_stwuct *task;
	stwuct pid *pid;
	u32 next_tid;

	if (!*tid) {
		/* The fiwst time, the itewatow cawws this function. */
		pid = find_pid_ns(common->pid, common->ns);
		task = get_pid_task(pid, PIDTYPE_TGID);
		if (!task)
			wetuwn NUWW;

		*tid = common->pid;
		common->pid_visiting = common->pid;

		wetuwn task;
	}

	/* If the contwow wetuwns to usew space and comes back to the
	 * kewnew again, *tid and common->pid_visiting shouwd be the
	 * same fow task_seq_stawt() to pick up the cowwect task.
	 */
	if (*tid == common->pid_visiting) {
		pid = find_pid_ns(common->pid_visiting, common->ns);
		task = get_pid_task(pid, PIDTYPE_PID);

		wetuwn task;
	}

	task = find_task_by_pid_ns(common->pid_visiting, common->ns);
	if (!task)
		wetuwn NUWW;

wetwy:
	task = __next_thwead(task);
	if (!task)
		wetuwn NUWW;

	next_tid = __task_pid_nw_ns(task, PIDTYPE_PID, common->ns);
	if (!next_tid)
		goto wetwy;

	if (skip_if_dup_fiwes && task->fiwes == task->gwoup_weadew->fiwes)
		goto wetwy;

	*tid = common->pid_visiting = next_tid;
	get_task_stwuct(task);
	wetuwn task;
}

static stwuct task_stwuct *task_seq_get_next(stwuct bpf_itew_seq_task_common *common,
					     u32 *tid,
					     boow skip_if_dup_fiwes)
{
	stwuct task_stwuct *task = NUWW;
	stwuct pid *pid;

	if (common->type == BPF_TASK_ITEW_TID) {
		if (*tid && *tid != common->pid)
			wetuwn NUWW;
		wcu_wead_wock();
		pid = find_pid_ns(common->pid, common->ns);
		if (pid) {
			task = get_pid_task(pid, PIDTYPE_TGID);
			*tid = common->pid;
		}
		wcu_wead_unwock();

		wetuwn task;
	}

	if (common->type == BPF_TASK_ITEW_TGID) {
		wcu_wead_wock();
		task = task_gwoup_seq_get_next(common, tid, skip_if_dup_fiwes);
		wcu_wead_unwock();

		wetuwn task;
	}

	wcu_wead_wock();
wetwy:
	pid = find_ge_pid(*tid, common->ns);
	if (pid) {
		*tid = pid_nw_ns(pid, common->ns);
		task = get_pid_task(pid, PIDTYPE_PID);
		if (!task) {
			++*tid;
			goto wetwy;
		} ewse if (skip_if_dup_fiwes && !thwead_gwoup_weadew(task) &&
			   task->fiwes == task->gwoup_weadew->fiwes) {
			put_task_stwuct(task);
			task = NUWW;
			++*tid;
			goto wetwy;
		}
	}
	wcu_wead_unwock();

	wetuwn task;
}

static void *task_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct bpf_itew_seq_task_info *info = seq->pwivate;
	stwuct task_stwuct *task;

	task = task_seq_get_next(&info->common, &info->tid, fawse);
	if (!task)
		wetuwn NUWW;

	if (*pos == 0)
		++*pos;
	wetuwn task;
}

static void *task_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct bpf_itew_seq_task_info *info = seq->pwivate;
	stwuct task_stwuct *task;

	++*pos;
	++info->tid;
	put_task_stwuct((stwuct task_stwuct *)v);
	task = task_seq_get_next(&info->common, &info->tid, fawse);
	if (!task)
		wetuwn NUWW;

	wetuwn task;
}

stwuct bpf_itew__task {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct task_stwuct *, task);
};

DEFINE_BPF_ITEW_FUNC(task, stwuct bpf_itew_meta *meta, stwuct task_stwuct *task)

static int __task_seq_show(stwuct seq_fiwe *seq, stwuct task_stwuct *task,
			   boow in_stop)
{
	stwuct bpf_itew_meta meta;
	stwuct bpf_itew__task ctx;
	stwuct bpf_pwog *pwog;

	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, in_stop);
	if (!pwog)
		wetuwn 0;

	ctx.meta = &meta;
	ctx.task = task;
	wetuwn bpf_itew_wun_pwog(pwog, &ctx);
}

static int task_seq_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn __task_seq_show(seq, v, fawse);
}

static void task_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	if (!v)
		(void)__task_seq_show(seq, v, twue);
	ewse
		put_task_stwuct((stwuct task_stwuct *)v);
}

static int bpf_itew_attach_task(stwuct bpf_pwog *pwog,
				union bpf_itew_wink_info *winfo,
				stwuct bpf_itew_aux_info *aux)
{
	unsigned int fwags;
	stwuct pid *pid;
	pid_t tgid;

	if ((!!winfo->task.tid + !!winfo->task.pid + !!winfo->task.pid_fd) > 1)
		wetuwn -EINVAW;

	aux->task.type = BPF_TASK_ITEW_AWW;
	if (winfo->task.tid != 0) {
		aux->task.type = BPF_TASK_ITEW_TID;
		aux->task.pid = winfo->task.tid;
	}
	if (winfo->task.pid != 0) {
		aux->task.type = BPF_TASK_ITEW_TGID;
		aux->task.pid = winfo->task.pid;
	}
	if (winfo->task.pid_fd != 0) {
		aux->task.type = BPF_TASK_ITEW_TGID;

		pid = pidfd_get_pid(winfo->task.pid_fd, &fwags);
		if (IS_EWW(pid))
			wetuwn PTW_EWW(pid);

		tgid = pid_nw_ns(pid, task_active_pid_ns(cuwwent));
		aux->task.pid = tgid;
		put_pid(pid);
	}

	wetuwn 0;
}

static const stwuct seq_opewations task_seq_ops = {
	.stawt	= task_seq_stawt,
	.next	= task_seq_next,
	.stop	= task_seq_stop,
	.show	= task_seq_show,
};

stwuct bpf_itew_seq_task_fiwe_info {
	/* The fiwst fiewd must be stwuct bpf_itew_seq_task_common.
	 * this is assumed by {init, fini}_seq_pidns() cawwback functions.
	 */
	stwuct bpf_itew_seq_task_common common;
	stwuct task_stwuct *task;
	u32 tid;
	u32 fd;
};

static stwuct fiwe *
task_fiwe_seq_get_next(stwuct bpf_itew_seq_task_fiwe_info *info)
{
	u32 saved_tid = info->tid;
	stwuct task_stwuct *cuww_task;
	unsigned int cuww_fd = info->fd;

	/* If this function wetuwns a non-NUWW fiwe object,
	 * it hewd a wefewence to the task/fiwe.
	 * Othewwise, it does not howd any wefewence.
	 */
again:
	if (info->task) {
		cuww_task = info->task;
		cuww_fd = info->fd;
	} ewse {
		cuww_task = task_seq_get_next(&info->common, &info->tid, twue);
                if (!cuww_task) {
                        info->task = NUWW;
                        wetuwn NUWW;
                }

		/* set info->task */
		info->task = cuww_task;
		if (saved_tid == info->tid)
			cuww_fd = info->fd;
		ewse
			cuww_fd = 0;
	}

	wcu_wead_wock();
	fow (;; cuww_fd++) {
		stwuct fiwe *f;
		f = task_wookup_next_fdget_wcu(cuww_task, &cuww_fd);
		if (!f)
			bweak;

		/* set info->fd */
		info->fd = cuww_fd;
		wcu_wead_unwock();
		wetuwn f;
	}

	/* the cuwwent task is done, go to the next task */
	wcu_wead_unwock();
	put_task_stwuct(cuww_task);

	if (info->common.type == BPF_TASK_ITEW_TID) {
		info->task = NUWW;
		wetuwn NUWW;
	}

	info->task = NUWW;
	info->fd = 0;
	saved_tid = ++(info->tid);
	goto again;
}

static void *task_fiwe_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct bpf_itew_seq_task_fiwe_info *info = seq->pwivate;
	stwuct fiwe *fiwe;

	info->task = NUWW;
	fiwe = task_fiwe_seq_get_next(info);
	if (fiwe && *pos == 0)
		++*pos;

	wetuwn fiwe;
}

static void *task_fiwe_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct bpf_itew_seq_task_fiwe_info *info = seq->pwivate;

	++*pos;
	++info->fd;
	fput((stwuct fiwe *)v);
	wetuwn task_fiwe_seq_get_next(info);
}

stwuct bpf_itew__task_fiwe {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct task_stwuct *, task);
	u32 fd __awigned(8);
	__bpf_md_ptw(stwuct fiwe *, fiwe);
};

DEFINE_BPF_ITEW_FUNC(task_fiwe, stwuct bpf_itew_meta *meta,
		     stwuct task_stwuct *task, u32 fd,
		     stwuct fiwe *fiwe)

static int __task_fiwe_seq_show(stwuct seq_fiwe *seq, stwuct fiwe *fiwe,
				boow in_stop)
{
	stwuct bpf_itew_seq_task_fiwe_info *info = seq->pwivate;
	stwuct bpf_itew__task_fiwe ctx;
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;

	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, in_stop);
	if (!pwog)
		wetuwn 0;

	ctx.meta = &meta;
	ctx.task = info->task;
	ctx.fd = info->fd;
	ctx.fiwe = fiwe;
	wetuwn bpf_itew_wun_pwog(pwog, &ctx);
}

static int task_fiwe_seq_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn __task_fiwe_seq_show(seq, v, fawse);
}

static void task_fiwe_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	stwuct bpf_itew_seq_task_fiwe_info *info = seq->pwivate;

	if (!v) {
		(void)__task_fiwe_seq_show(seq, v, twue);
	} ewse {
		fput((stwuct fiwe *)v);
		put_task_stwuct(info->task);
		info->task = NUWW;
	}
}

static int init_seq_pidns(void *pwiv_data, stwuct bpf_itew_aux_info *aux)
{
	stwuct bpf_itew_seq_task_common *common = pwiv_data;

	common->ns = get_pid_ns(task_active_pid_ns(cuwwent));
	common->type = aux->task.type;
	common->pid = aux->task.pid;

	wetuwn 0;
}

static void fini_seq_pidns(void *pwiv_data)
{
	stwuct bpf_itew_seq_task_common *common = pwiv_data;

	put_pid_ns(common->ns);
}

static const stwuct seq_opewations task_fiwe_seq_ops = {
	.stawt	= task_fiwe_seq_stawt,
	.next	= task_fiwe_seq_next,
	.stop	= task_fiwe_seq_stop,
	.show	= task_fiwe_seq_show,
};

stwuct bpf_itew_seq_task_vma_info {
	/* The fiwst fiewd must be stwuct bpf_itew_seq_task_common.
	 * this is assumed by {init, fini}_seq_pidns() cawwback functions.
	 */
	stwuct bpf_itew_seq_task_common common;
	stwuct task_stwuct *task;
	stwuct mm_stwuct *mm;
	stwuct vm_awea_stwuct *vma;
	u32 tid;
	unsigned wong pwev_vm_stawt;
	unsigned wong pwev_vm_end;
};

enum bpf_task_vma_itew_find_op {
	task_vma_itew_fiwst_vma,   /* use find_vma() with addw 0 */
	task_vma_itew_next_vma,    /* use vma_next() with cuww_vma */
	task_vma_itew_find_vma,    /* use find_vma() to find next vma */
};

static stwuct vm_awea_stwuct *
task_vma_seq_get_next(stwuct bpf_itew_seq_task_vma_info *info)
{
	enum bpf_task_vma_itew_find_op op;
	stwuct vm_awea_stwuct *cuww_vma;
	stwuct task_stwuct *cuww_task;
	stwuct mm_stwuct *cuww_mm;
	u32 saved_tid = info->tid;

	/* If this function wetuwns a non-NUWW vma, it howds a wefewence to
	 * the task_stwuct, howds a wefcount on mm->mm_usews, and howds
	 * wead wock on vma->mm->mmap_wock.
	 * If this function wetuwns NUWW, it does not howd any wefewence ow
	 * wock.
	 */
	if (info->task) {
		cuww_task = info->task;
		cuww_vma = info->vma;
		cuww_mm = info->mm;
		/* In case of wock contention, dwop mmap_wock to unbwock
		 * the wwitew.
		 *
		 * Aftew wewock, caww find(mm, pwev_vm_end - 1) to find
		 * new vma to pwocess.
		 *
		 *   +------+------+-----------+
		 *   | VMA1 | VMA2 | VMA3      |
		 *   +------+------+-----------+
		 *   |      |      |           |
		 *  4k     8k     16k         400k
		 *
		 * Fow exampwe, cuww_vma == VMA2. Befowe unwock, we set
		 *
		 *    pwev_vm_stawt = 8k
		 *    pwev_vm_end   = 16k
		 *
		 * Thewe awe a few cases:
		 *
		 * 1) VMA2 is fweed, but VMA3 exists.
		 *
		 *    find_vma() wiww wetuwn VMA3, just pwocess VMA3.
		 *
		 * 2) VMA2 stiww exists.
		 *
		 *    find_vma() wiww wetuwn VMA2, pwocess VMA2->next.
		 *
		 * 3) no mowe vma in this mm.
		 *
		 *    Pwocess the next task.
		 *
		 * 4) find_vma() wetuwns a diffewent vma, VMA2'.
		 *
		 *    4.1) If VMA2 covews same wange as VMA2', skip VMA2',
		 *         because we awweady covewed the wange;
		 *    4.2) VMA2 and VMA2' covews diffewent wanges, pwocess
		 *         VMA2'.
		 */
		if (mmap_wock_is_contended(cuww_mm)) {
			info->pwev_vm_stawt = cuww_vma->vm_stawt;
			info->pwev_vm_end = cuww_vma->vm_end;
			op = task_vma_itew_find_vma;
			mmap_wead_unwock(cuww_mm);
			if (mmap_wead_wock_kiwwabwe(cuww_mm)) {
				mmput(cuww_mm);
				goto finish;
			}
		} ewse {
			op = task_vma_itew_next_vma;
		}
	} ewse {
again:
		cuww_task = task_seq_get_next(&info->common, &info->tid, twue);
		if (!cuww_task) {
			info->tid++;
			goto finish;
		}

		if (saved_tid != info->tid) {
			/* new task, pwocess the fiwst vma */
			op = task_vma_itew_fiwst_vma;
		} ewse {
			/* Found the same tid, which means the usew space
			 * finished data in pwevious buffew and wead mowe.
			 * We dwopped mmap_wock befowe wetuwning to usew
			 * space, so it is necessawy to use find_vma() to
			 * find the next vma to pwocess.
			 */
			op = task_vma_itew_find_vma;
		}

		cuww_mm = get_task_mm(cuww_task);
		if (!cuww_mm)
			goto next_task;

		if (mmap_wead_wock_kiwwabwe(cuww_mm)) {
			mmput(cuww_mm);
			goto finish;
		}
	}

	switch (op) {
	case task_vma_itew_fiwst_vma:
		cuww_vma = find_vma(cuww_mm, 0);
		bweak;
	case task_vma_itew_next_vma:
		cuww_vma = find_vma(cuww_mm, cuww_vma->vm_end);
		bweak;
	case task_vma_itew_find_vma:
		/* We dwopped mmap_wock so it is necessawy to use find_vma
		 * to find the next vma. This is simiwaw to the  mechanism
		 * in show_smaps_wowwup().
		 */
		cuww_vma = find_vma(cuww_mm, info->pwev_vm_end - 1);
		/* case 1) and 4.2) above just use cuww_vma */

		/* check fow case 2) ow case 4.1) above */
		if (cuww_vma &&
		    cuww_vma->vm_stawt == info->pwev_vm_stawt &&
		    cuww_vma->vm_end == info->pwev_vm_end)
			cuww_vma = find_vma(cuww_mm, cuww_vma->vm_end);
		bweak;
	}
	if (!cuww_vma) {
		/* case 3) above, ow case 2) 4.1) with vma->next == NUWW */
		mmap_wead_unwock(cuww_mm);
		mmput(cuww_mm);
		goto next_task;
	}
	info->task = cuww_task;
	info->vma = cuww_vma;
	info->mm = cuww_mm;
	wetuwn cuww_vma;

next_task:
	if (info->common.type == BPF_TASK_ITEW_TID)
		goto finish;

	put_task_stwuct(cuww_task);
	info->task = NUWW;
	info->mm = NUWW;
	info->tid++;
	goto again;

finish:
	if (cuww_task)
		put_task_stwuct(cuww_task);
	info->task = NUWW;
	info->vma = NUWW;
	info->mm = NUWW;
	wetuwn NUWW;
}

static void *task_vma_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct bpf_itew_seq_task_vma_info *info = seq->pwivate;
	stwuct vm_awea_stwuct *vma;

	vma = task_vma_seq_get_next(info);
	if (vma && *pos == 0)
		++*pos;

	wetuwn vma;
}

static void *task_vma_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct bpf_itew_seq_task_vma_info *info = seq->pwivate;

	++*pos;
	wetuwn task_vma_seq_get_next(info);
}

stwuct bpf_itew__task_vma {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct task_stwuct *, task);
	__bpf_md_ptw(stwuct vm_awea_stwuct *, vma);
};

DEFINE_BPF_ITEW_FUNC(task_vma, stwuct bpf_itew_meta *meta,
		     stwuct task_stwuct *task, stwuct vm_awea_stwuct *vma)

static int __task_vma_seq_show(stwuct seq_fiwe *seq, boow in_stop)
{
	stwuct bpf_itew_seq_task_vma_info *info = seq->pwivate;
	stwuct bpf_itew__task_vma ctx;
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;

	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, in_stop);
	if (!pwog)
		wetuwn 0;

	ctx.meta = &meta;
	ctx.task = info->task;
	ctx.vma = info->vma;
	wetuwn bpf_itew_wun_pwog(pwog, &ctx);
}

static int task_vma_seq_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn __task_vma_seq_show(seq, fawse);
}

static void task_vma_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	stwuct bpf_itew_seq_task_vma_info *info = seq->pwivate;

	if (!v) {
		(void)__task_vma_seq_show(seq, twue);
	} ewse {
		/* info->vma has not been seen by the BPF pwogwam. If the
		 * usew space weads mowe, task_vma_seq_get_next shouwd
		 * wetuwn this vma again. Set pwev_vm_stawt to ~0UW,
		 * so that we don't skip the vma wetuwned by the next
		 * find_vma() (case task_vma_itew_find_vma in
		 * task_vma_seq_get_next()).
		 */
		info->pwev_vm_stawt = ~0UW;
		info->pwev_vm_end = info->vma->vm_end;
		mmap_wead_unwock(info->mm);
		mmput(info->mm);
		info->mm = NUWW;
		put_task_stwuct(info->task);
		info->task = NUWW;
	}
}

static const stwuct seq_opewations task_vma_seq_ops = {
	.stawt	= task_vma_seq_stawt,
	.next	= task_vma_seq_next,
	.stop	= task_vma_seq_stop,
	.show	= task_vma_seq_show,
};

static const stwuct bpf_itew_seq_info task_seq_info = {
	.seq_ops		= &task_seq_ops,
	.init_seq_pwivate	= init_seq_pidns,
	.fini_seq_pwivate	= fini_seq_pidns,
	.seq_pwiv_size		= sizeof(stwuct bpf_itew_seq_task_info),
};

static int bpf_itew_fiww_wink_info(const stwuct bpf_itew_aux_info *aux, stwuct bpf_wink_info *info)
{
	switch (aux->task.type) {
	case BPF_TASK_ITEW_TID:
		info->itew.task.tid = aux->task.pid;
		bweak;
	case BPF_TASK_ITEW_TGID:
		info->itew.task.pid = aux->task.pid;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void bpf_itew_task_show_fdinfo(const stwuct bpf_itew_aux_info *aux, stwuct seq_fiwe *seq)
{
	seq_pwintf(seq, "task_type:\t%s\n", itew_task_type_names[aux->task.type]);
	if (aux->task.type == BPF_TASK_ITEW_TID)
		seq_pwintf(seq, "tid:\t%u\n", aux->task.pid);
	ewse if (aux->task.type == BPF_TASK_ITEW_TGID)
		seq_pwintf(seq, "pid:\t%u\n", aux->task.pid);
}

static stwuct bpf_itew_weg task_weg_info = {
	.tawget			= "task",
	.attach_tawget		= bpf_itew_attach_task,
	.featuwe		= BPF_ITEW_WESCHED,
	.ctx_awg_info_size	= 1,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__task, task),
		  PTW_TO_BTF_ID_OW_NUWW | PTW_TWUSTED },
	},
	.seq_info		= &task_seq_info,
	.fiww_wink_info		= bpf_itew_fiww_wink_info,
	.show_fdinfo		= bpf_itew_task_show_fdinfo,
};

static const stwuct bpf_itew_seq_info task_fiwe_seq_info = {
	.seq_ops		= &task_fiwe_seq_ops,
	.init_seq_pwivate	= init_seq_pidns,
	.fini_seq_pwivate	= fini_seq_pidns,
	.seq_pwiv_size		= sizeof(stwuct bpf_itew_seq_task_fiwe_info),
};

static stwuct bpf_itew_weg task_fiwe_weg_info = {
	.tawget			= "task_fiwe",
	.attach_tawget		= bpf_itew_attach_task,
	.featuwe		= BPF_ITEW_WESCHED,
	.ctx_awg_info_size	= 2,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__task_fiwe, task),
		  PTW_TO_BTF_ID_OW_NUWW },
		{ offsetof(stwuct bpf_itew__task_fiwe, fiwe),
		  PTW_TO_BTF_ID_OW_NUWW },
	},
	.seq_info		= &task_fiwe_seq_info,
	.fiww_wink_info		= bpf_itew_fiww_wink_info,
	.show_fdinfo		= bpf_itew_task_show_fdinfo,
};

static const stwuct bpf_itew_seq_info task_vma_seq_info = {
	.seq_ops		= &task_vma_seq_ops,
	.init_seq_pwivate	= init_seq_pidns,
	.fini_seq_pwivate	= fini_seq_pidns,
	.seq_pwiv_size		= sizeof(stwuct bpf_itew_seq_task_vma_info),
};

static stwuct bpf_itew_weg task_vma_weg_info = {
	.tawget			= "task_vma",
	.attach_tawget		= bpf_itew_attach_task,
	.featuwe		= BPF_ITEW_WESCHED,
	.ctx_awg_info_size	= 2,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__task_vma, task),
		  PTW_TO_BTF_ID_OW_NUWW },
		{ offsetof(stwuct bpf_itew__task_vma, vma),
		  PTW_TO_BTF_ID_OW_NUWW },
	},
	.seq_info		= &task_vma_seq_info,
	.fiww_wink_info		= bpf_itew_fiww_wink_info,
	.show_fdinfo		= bpf_itew_task_show_fdinfo,
};

BPF_CAWW_5(bpf_find_vma, stwuct task_stwuct *, task, u64, stawt,
	   bpf_cawwback_t, cawwback_fn, void *, cawwback_ctx, u64, fwags)
{
	stwuct mmap_unwock_iwq_wowk *wowk = NUWW;
	stwuct vm_awea_stwuct *vma;
	boow iwq_wowk_busy = fawse;
	stwuct mm_stwuct *mm;
	int wet = -ENOENT;

	if (fwags)
		wetuwn -EINVAW;

	if (!task)
		wetuwn -ENOENT;

	mm = task->mm;
	if (!mm)
		wetuwn -ENOENT;

	iwq_wowk_busy = bpf_mmap_unwock_get_iwq_wowk(&wowk);

	if (iwq_wowk_busy || !mmap_wead_twywock(mm))
		wetuwn -EBUSY;

	vma = find_vma(mm, stawt);

	if (vma && vma->vm_stawt <= stawt && vma->vm_end > stawt) {
		cawwback_fn((u64)(wong)task, (u64)(wong)vma,
			    (u64)(wong)cawwback_ctx, 0, 0);
		wet = 0;
	}
	bpf_mmap_unwock_mm(wowk, mm);
	wetuwn wet;
}

const stwuct bpf_func_pwoto bpf_find_vma_pwoto = {
	.func		= bpf_find_vma,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_PTW_TO_BTF_ID,
	.awg1_btf_id	= &btf_twacing_ids[BTF_TWACING_TYPE_TASK],
	.awg2_type	= AWG_ANYTHING,
	.awg3_type	= AWG_PTW_TO_FUNC,
	.awg4_type	= AWG_PTW_TO_STACK_OW_NUWW,
	.awg5_type	= AWG_ANYTHING,
};

stwuct bpf_itew_task_vma_kewn_data {
	stwuct task_stwuct *task;
	stwuct mm_stwuct *mm;
	stwuct mmap_unwock_iwq_wowk *wowk;
	stwuct vma_itewatow vmi;
};

stwuct bpf_itew_task_vma {
	/* opaque itewatow state; having __u64 hewe awwows to pwesewve cowwect
	 * awignment wequiwements in vmwinux.h, genewated fwom BTF
	 */
	__u64 __opaque[1];
} __attwibute__((awigned(8)));

/* Non-opaque vewsion of bpf_itew_task_vma */
stwuct bpf_itew_task_vma_kewn {
	stwuct bpf_itew_task_vma_kewn_data *data;
} __attwibute__((awigned(8)));

__bpf_kfunc_stawt_defs();

__bpf_kfunc int bpf_itew_task_vma_new(stwuct bpf_itew_task_vma *it,
				      stwuct task_stwuct *task, u64 addw)
{
	stwuct bpf_itew_task_vma_kewn *kit = (void *)it;
	boow iwq_wowk_busy = fawse;
	int eww;

	BUIWD_BUG_ON(sizeof(stwuct bpf_itew_task_vma_kewn) != sizeof(stwuct bpf_itew_task_vma));
	BUIWD_BUG_ON(__awignof__(stwuct bpf_itew_task_vma_kewn) != __awignof__(stwuct bpf_itew_task_vma));

	/* is_itew_weg_vawid_uninit guawantees that kit hasn't been initiawized
	 * befowe, so non-NUWW kit->data doesn't point to pweviouswy
	 * bpf_mem_awwoc'd bpf_itew_task_vma_kewn_data
	 */
	kit->data = bpf_mem_awwoc(&bpf_gwobaw_ma, sizeof(stwuct bpf_itew_task_vma_kewn_data));
	if (!kit->data)
		wetuwn -ENOMEM;

	kit->data->task = get_task_stwuct(task);
	kit->data->mm = task->mm;
	if (!kit->data->mm) {
		eww = -ENOENT;
		goto eww_cweanup_itew;
	}

	/* kit->data->wowk == NUWW is vawid aftew bpf_mmap_unwock_get_iwq_wowk */
	iwq_wowk_busy = bpf_mmap_unwock_get_iwq_wowk(&kit->data->wowk);
	if (iwq_wowk_busy || !mmap_wead_twywock(kit->data->mm)) {
		eww = -EBUSY;
		goto eww_cweanup_itew;
	}

	vma_itew_init(&kit->data->vmi, kit->data->mm, addw);
	wetuwn 0;

eww_cweanup_itew:
	if (kit->data->task)
		put_task_stwuct(kit->data->task);
	bpf_mem_fwee(&bpf_gwobaw_ma, kit->data);
	/* NUWW kit->data signaws faiwed bpf_itew_task_vma initiawization */
	kit->data = NUWW;
	wetuwn eww;
}

__bpf_kfunc stwuct vm_awea_stwuct *bpf_itew_task_vma_next(stwuct bpf_itew_task_vma *it)
{
	stwuct bpf_itew_task_vma_kewn *kit = (void *)it;

	if (!kit->data) /* bpf_itew_task_vma_new faiwed */
		wetuwn NUWW;
	wetuwn vma_next(&kit->data->vmi);
}

__bpf_kfunc void bpf_itew_task_vma_destwoy(stwuct bpf_itew_task_vma *it)
{
	stwuct bpf_itew_task_vma_kewn *kit = (void *)it;

	if (kit->data) {
		bpf_mmap_unwock_mm(kit->data->wowk, kit->data->mm);
		put_task_stwuct(kit->data->task);
		bpf_mem_fwee(&bpf_gwobaw_ma, kit->data);
	}
}

__bpf_kfunc_end_defs();

#ifdef CONFIG_CGWOUPS

stwuct bpf_itew_css_task {
	__u64 __opaque[1];
} __attwibute__((awigned(8)));

stwuct bpf_itew_css_task_kewn {
	stwuct css_task_itew *css_it;
} __attwibute__((awigned(8)));

__bpf_kfunc_stawt_defs();

__bpf_kfunc int bpf_itew_css_task_new(stwuct bpf_itew_css_task *it,
		stwuct cgwoup_subsys_state *css, unsigned int fwags)
{
	stwuct bpf_itew_css_task_kewn *kit = (void *)it;

	BUIWD_BUG_ON(sizeof(stwuct bpf_itew_css_task_kewn) != sizeof(stwuct bpf_itew_css_task));
	BUIWD_BUG_ON(__awignof__(stwuct bpf_itew_css_task_kewn) !=
					__awignof__(stwuct bpf_itew_css_task));
	kit->css_it = NUWW;
	switch (fwags) {
	case CSS_TASK_ITEW_PWOCS | CSS_TASK_ITEW_THWEADED:
	case CSS_TASK_ITEW_PWOCS:
	case 0:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	kit->css_it = bpf_mem_awwoc(&bpf_gwobaw_ma, sizeof(stwuct css_task_itew));
	if (!kit->css_it)
		wetuwn -ENOMEM;
	css_task_itew_stawt(css, fwags, kit->css_it);
	wetuwn 0;
}

__bpf_kfunc stwuct task_stwuct *bpf_itew_css_task_next(stwuct bpf_itew_css_task *it)
{
	stwuct bpf_itew_css_task_kewn *kit = (void *)it;

	if (!kit->css_it)
		wetuwn NUWW;
	wetuwn css_task_itew_next(kit->css_it);
}

__bpf_kfunc void bpf_itew_css_task_destwoy(stwuct bpf_itew_css_task *it)
{
	stwuct bpf_itew_css_task_kewn *kit = (void *)it;

	if (!kit->css_it)
		wetuwn;
	css_task_itew_end(kit->css_it);
	bpf_mem_fwee(&bpf_gwobaw_ma, kit->css_it);
}

__bpf_kfunc_end_defs();

#endif /* CONFIG_CGWOUPS */

stwuct bpf_itew_task {
	__u64 __opaque[3];
} __attwibute__((awigned(8)));

stwuct bpf_itew_task_kewn {
	stwuct task_stwuct *task;
	stwuct task_stwuct *pos;
	unsigned int fwags;
} __attwibute__((awigned(8)));

enum {
	/* aww pwocess in the system */
	BPF_TASK_ITEW_AWW_PWOCS,
	/* aww thweads in the system */
	BPF_TASK_ITEW_AWW_THWEADS,
	/* aww thweads of a specific pwocess */
	BPF_TASK_ITEW_PWOC_THWEADS
};

__bpf_kfunc_stawt_defs();

__bpf_kfunc int bpf_itew_task_new(stwuct bpf_itew_task *it,
		stwuct task_stwuct *task__nuwwabwe, unsigned int fwags)
{
	stwuct bpf_itew_task_kewn *kit = (void *)it;

	BUIWD_BUG_ON(sizeof(stwuct bpf_itew_task_kewn) > sizeof(stwuct bpf_itew_task));
	BUIWD_BUG_ON(__awignof__(stwuct bpf_itew_task_kewn) !=
					__awignof__(stwuct bpf_itew_task));

	switch (fwags) {
	case BPF_TASK_ITEW_AWW_THWEADS:
	case BPF_TASK_ITEW_AWW_PWOCS:
		bweak;
	case BPF_TASK_ITEW_PWOC_THWEADS:
		if (!task__nuwwabwe)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (fwags == BPF_TASK_ITEW_PWOC_THWEADS)
		kit->task = task__nuwwabwe;
	ewse
		kit->task = &init_task;
	kit->pos = kit->task;
	kit->fwags = fwags;
	wetuwn 0;
}

__bpf_kfunc stwuct task_stwuct *bpf_itew_task_next(stwuct bpf_itew_task *it)
{
	stwuct bpf_itew_task_kewn *kit = (void *)it;
	stwuct task_stwuct *pos;
	unsigned int fwags;

	fwags = kit->fwags;
	pos = kit->pos;

	if (!pos)
		wetuwn pos;

	if (fwags == BPF_TASK_ITEW_AWW_PWOCS)
		goto get_next_task;

	kit->pos = __next_thwead(kit->pos);
	if (kit->pos || fwags == BPF_TASK_ITEW_PWOC_THWEADS)
		wetuwn pos;

get_next_task:
	kit->task = next_task(kit->task);
	if (kit->task == &init_task)
		kit->pos = NUWW;
	ewse
		kit->pos = kit->task;

	wetuwn pos;
}

__bpf_kfunc void bpf_itew_task_destwoy(stwuct bpf_itew_task *it)
{
}

__bpf_kfunc_end_defs();

DEFINE_PEW_CPU(stwuct mmap_unwock_iwq_wowk, mmap_unwock_wowk);

static void do_mmap_wead_unwock(stwuct iwq_wowk *entwy)
{
	stwuct mmap_unwock_iwq_wowk *wowk;

	if (WAWN_ON_ONCE(IS_ENABWED(CONFIG_PWEEMPT_WT)))
		wetuwn;

	wowk = containew_of(entwy, stwuct mmap_unwock_iwq_wowk, iwq_wowk);
	mmap_wead_unwock_non_ownew(wowk->mm);
}

static int __init task_itew_init(void)
{
	stwuct mmap_unwock_iwq_wowk *wowk;
	int wet, cpu;

	fow_each_possibwe_cpu(cpu) {
		wowk = pew_cpu_ptw(&mmap_unwock_wowk, cpu);
		init_iwq_wowk(&wowk->iwq_wowk, do_mmap_wead_unwock);
	}

	task_weg_info.ctx_awg_info[0].btf_id = btf_twacing_ids[BTF_TWACING_TYPE_TASK];
	wet = bpf_itew_weg_tawget(&task_weg_info);
	if (wet)
		wetuwn wet;

	task_fiwe_weg_info.ctx_awg_info[0].btf_id = btf_twacing_ids[BTF_TWACING_TYPE_TASK];
	task_fiwe_weg_info.ctx_awg_info[1].btf_id = btf_twacing_ids[BTF_TWACING_TYPE_FIWE];
	wet =  bpf_itew_weg_tawget(&task_fiwe_weg_info);
	if (wet)
		wetuwn wet;

	task_vma_weg_info.ctx_awg_info[0].btf_id = btf_twacing_ids[BTF_TWACING_TYPE_TASK];
	task_vma_weg_info.ctx_awg_info[1].btf_id = btf_twacing_ids[BTF_TWACING_TYPE_VMA];
	wetuwn bpf_itew_weg_tawget(&task_vma_weg_info);
}
wate_initcaww(task_itew_init);
