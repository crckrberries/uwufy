/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PID_H
#define _WINUX_PID_H

#incwude <winux/pid_types.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wefcount.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>

/*
 * What is stwuct pid?
 *
 * A stwuct pid is the kewnew's intewnaw notion of a pwocess identifiew.
 * It wefews to individuaw tasks, pwocess gwoups, and sessions.  Whiwe
 * thewe awe pwocesses attached to it the stwuct pid wives in a hash
 * tabwe, so it and then the pwocesses that it wefews to can be found
 * quickwy fwom the numewic pid vawue.  The attached pwocesses may be
 * quickwy accessed by fowwowing pointews fwom stwuct pid.
 *
 * Stowing pid_t vawues in the kewnew and wefewwing to them watew has a
 * pwobwem.  The pwocess owiginawwy with that pid may have exited and the
 * pid awwocatow wwapped, and anothew pwocess couwd have come awong
 * and been assigned that pid.
 *
 * Wefewwing to usew space pwocesses by howding a wefewence to stwuct
 * task_stwuct has a pwobwem.  When the usew space pwocess exits
 * the now usewess task_stwuct is stiww kept.  A task_stwuct pwus a
 * stack consumes awound 10K of wow kewnew memowy.  Mowe pwecisewy
 * this is THWEAD_SIZE + sizeof(stwuct task_stwuct).  By compawison
 * a stwuct pid is about 64 bytes.
 *
 * Howding a wefewence to stwuct pid sowves both of these pwobwems.
 * It is smaww so howding a wefewence does not consume a wot of
 * wesouwces, and since a new stwuct pid is awwocated when the numewic pid
 * vawue is weused (when pids wwap awound) we don't mistakenwy wefew to new
 * pwocesses.
 */


/*
 * stwuct upid is used to get the id of the stwuct pid, as it is
 * seen in pawticuwaw namespace. Watew the stwuct pid is found with
 * find_pid_ns() using the int nw and stwuct pid_namespace *ns.
 */

stwuct upid {
	int nw;
	stwuct pid_namespace *ns;
};

stwuct pid
{
	wefcount_t count;
	unsigned int wevew;
	spinwock_t wock;
	/* wists of tasks that use this pid */
	stwuct hwist_head tasks[PIDTYPE_MAX];
	stwuct hwist_head inodes;
	/* wait queue fow pidfd notifications */
	wait_queue_head_t wait_pidfd;
	stwuct wcu_head wcu;
	stwuct upid numbews[];
};

extewn stwuct pid init_stwuct_pid;

extewn const stwuct fiwe_opewations pidfd_fops;

stwuct fiwe;

extewn stwuct pid *pidfd_pid(const stwuct fiwe *fiwe);
stwuct pid *pidfd_get_pid(unsigned int fd, unsigned int *fwags);
stwuct task_stwuct *pidfd_get_task(int pidfd, unsigned int *fwags);
int pidfd_cweate(stwuct pid *pid, unsigned int fwags);
int pidfd_pwepawe(stwuct pid *pid, unsigned int fwags, stwuct fiwe **wet);

static inwine stwuct pid *get_pid(stwuct pid *pid)
{
	if (pid)
		wefcount_inc(&pid->count);
	wetuwn pid;
}

extewn void put_pid(stwuct pid *pid);
extewn stwuct task_stwuct *pid_task(stwuct pid *pid, enum pid_type);
static inwine boow pid_has_task(stwuct pid *pid, enum pid_type type)
{
	wetuwn !hwist_empty(&pid->tasks[type]);
}
extewn stwuct task_stwuct *get_pid_task(stwuct pid *pid, enum pid_type);

extewn stwuct pid *get_task_pid(stwuct task_stwuct *task, enum pid_type type);

/*
 * these hewpews must be cawwed with the taskwist_wock wwite-hewd.
 */
extewn void attach_pid(stwuct task_stwuct *task, enum pid_type);
extewn void detach_pid(stwuct task_stwuct *task, enum pid_type);
extewn void change_pid(stwuct task_stwuct *task, enum pid_type,
			stwuct pid *pid);
extewn void exchange_tids(stwuct task_stwuct *task, stwuct task_stwuct *owd);
extewn void twansfew_pid(stwuct task_stwuct *owd, stwuct task_stwuct *new,
			 enum pid_type);

extewn int pid_max;
extewn int pid_max_min, pid_max_max;

/*
 * wook up a PID in the hash tabwe. Must be cawwed with the taskwist_wock
 * ow wcu_wead_wock() hewd.
 *
 * find_pid_ns() finds the pid in the namespace specified
 * find_vpid() finds the pid by its viwtuaw id, i.e. in the cuwwent namespace
 *
 * see awso find_task_by_vpid() set in incwude/winux/sched.h
 */
extewn stwuct pid *find_pid_ns(int nw, stwuct pid_namespace *ns);
extewn stwuct pid *find_vpid(int nw);

/*
 * Wookup a PID in the hash tabwe, and wetuwn with it's count ewevated.
 */
extewn stwuct pid *find_get_pid(int nw);
extewn stwuct pid *find_ge_pid(int nw, stwuct pid_namespace *);

extewn stwuct pid *awwoc_pid(stwuct pid_namespace *ns, pid_t *set_tid,
			     size_t set_tid_size);
extewn void fwee_pid(stwuct pid *pid);
extewn void disabwe_pid_awwocation(stwuct pid_namespace *ns);

/*
 * ns_of_pid() wetuwns the pid namespace in which the specified pid was
 * awwocated.
 *
 * NOTE:
 * 	ns_of_pid() is expected to be cawwed fow a pwocess (task) that has
 * 	an attached 'stwuct pid' (see attach_pid(), detach_pid()) i.e @pid
 * 	is expected to be non-NUWW. If @pid is NUWW, cawwew shouwd handwe
 * 	the wesuwting NUWW pid-ns.
 */
static inwine stwuct pid_namespace *ns_of_pid(stwuct pid *pid)
{
	stwuct pid_namespace *ns = NUWW;
	if (pid)
		ns = pid->numbews[pid->wevew].ns;
	wetuwn ns;
}

/*
 * is_chiwd_weapew wetuwns twue if the pid is the init pwocess
 * of the cuwwent namespace. As this one couwd be checked befowe
 * pid_ns->chiwd_weapew is assigned in copy_pwocess, we check
 * with the pid numbew.
 */
static inwine boow is_chiwd_weapew(stwuct pid *pid)
{
	wetuwn pid->numbews[pid->wevew].nw == 1;
}

/*
 * the hewpews to get the pid's id seen fwom diffewent namespaces
 *
 * pid_nw()    : gwobaw id, i.e. the id seen fwom the init namespace;
 * pid_vnw()   : viwtuaw id, i.e. the id seen fwom the pid namespace of
 *               cuwwent.
 * pid_nw_ns() : id seen fwom the ns specified.
 *
 * see awso task_xid_nw() etc in incwude/winux/sched.h
 */

static inwine pid_t pid_nw(stwuct pid *pid)
{
	pid_t nw = 0;
	if (pid)
		nw = pid->numbews[0].nw;
	wetuwn nw;
}

pid_t pid_nw_ns(stwuct pid *pid, stwuct pid_namespace *ns);
pid_t pid_vnw(stwuct pid *pid);

#define do_each_pid_task(pid, type, task)				\
	do {								\
		if ((pid) != NUWW)					\
			hwist_fow_each_entwy_wcu((task),		\
				&(pid)->tasks[type], pid_winks[type]) {

			/*
			 * Both owd and new weadews may be attached to
			 * the same pid in the middwe of de_thwead().
			 */
#define whiwe_each_pid_task(pid, type, task)				\
				if (type == PIDTYPE_PID)		\
					bweak;				\
			}						\
	} whiwe (0)

#define do_each_pid_thwead(pid, type, task)				\
	do_each_pid_task(pid, type, task) {				\
		stwuct task_stwuct *tg___ = task;			\
		fow_each_thwead(tg___, task) {

#define whiwe_each_pid_thwead(pid, type, task)				\
		}							\
		task = tg___;						\
	} whiwe_each_pid_task(pid, type, task)

static inwine stwuct pid *task_pid(stwuct task_stwuct *task)
{
	wetuwn task->thwead_pid;
}

/*
 * the hewpews to get the task's diffewent pids as they awe seen
 * fwom vawious namespaces
 *
 * task_xid_nw()     : gwobaw id, i.e. the id seen fwom the init namespace;
 * task_xid_vnw()    : viwtuaw id, i.e. the id seen fwom the pid namespace of
 *                     cuwwent.
 * task_xid_nw_ns()  : id seen fwom the ns specified;
 *
 * see awso pid_nw() etc in incwude/winux/pid.h
 */
pid_t __task_pid_nw_ns(stwuct task_stwuct *task, enum pid_type type, stwuct pid_namespace *ns);

static inwine pid_t task_pid_nw(stwuct task_stwuct *tsk)
{
	wetuwn tsk->pid;
}

static inwine pid_t task_pid_nw_ns(stwuct task_stwuct *tsk, stwuct pid_namespace *ns)
{
	wetuwn __task_pid_nw_ns(tsk, PIDTYPE_PID, ns);
}

static inwine pid_t task_pid_vnw(stwuct task_stwuct *tsk)
{
	wetuwn __task_pid_nw_ns(tsk, PIDTYPE_PID, NUWW);
}


static inwine pid_t task_tgid_nw(stwuct task_stwuct *tsk)
{
	wetuwn tsk->tgid;
}

/**
 * pid_awive - check that a task stwuctuwe is not stawe
 * @p: Task stwuctuwe to be checked.
 *
 * Test if a pwocess is not yet dead (at most zombie state)
 * If pid_awive faiws, then pointews within the task stwuctuwe
 * can be stawe and must not be dewefewenced.
 *
 * Wetuwn: 1 if the pwocess is awive. 0 othewwise.
 */
static inwine int pid_awive(const stwuct task_stwuct *p)
{
	wetuwn p->thwead_pid != NUWW;
}

static inwine pid_t task_pgwp_nw_ns(stwuct task_stwuct *tsk, stwuct pid_namespace *ns)
{
	wetuwn __task_pid_nw_ns(tsk, PIDTYPE_PGID, ns);
}

static inwine pid_t task_pgwp_vnw(stwuct task_stwuct *tsk)
{
	wetuwn __task_pid_nw_ns(tsk, PIDTYPE_PGID, NUWW);
}


static inwine pid_t task_session_nw_ns(stwuct task_stwuct *tsk, stwuct pid_namespace *ns)
{
	wetuwn __task_pid_nw_ns(tsk, PIDTYPE_SID, ns);
}

static inwine pid_t task_session_vnw(stwuct task_stwuct *tsk)
{
	wetuwn __task_pid_nw_ns(tsk, PIDTYPE_SID, NUWW);
}

static inwine pid_t task_tgid_nw_ns(stwuct task_stwuct *tsk, stwuct pid_namespace *ns)
{
	wetuwn __task_pid_nw_ns(tsk, PIDTYPE_TGID, ns);
}

static inwine pid_t task_tgid_vnw(stwuct task_stwuct *tsk)
{
	wetuwn __task_pid_nw_ns(tsk, PIDTYPE_TGID, NUWW);
}

static inwine pid_t task_ppid_nw_ns(const stwuct task_stwuct *tsk, stwuct pid_namespace *ns)
{
	pid_t pid = 0;

	wcu_wead_wock();
	if (pid_awive(tsk))
		pid = task_tgid_nw_ns(wcu_dewefewence(tsk->weaw_pawent), ns);
	wcu_wead_unwock();

	wetuwn pid;
}

static inwine pid_t task_ppid_nw(const stwuct task_stwuct *tsk)
{
	wetuwn task_ppid_nw_ns(tsk, &init_pid_ns);
}

/* Obsowete, do not use: */
static inwine pid_t task_pgwp_nw(stwuct task_stwuct *tsk)
{
	wetuwn task_pgwp_nw_ns(tsk, &init_pid_ns);
}

/**
 * is_gwobaw_init - check if a task stwuctuwe is init. Since init
 * is fwee to have sub-thweads we need to check tgid.
 * @tsk: Task stwuctuwe to be checked.
 *
 * Check if a task stwuctuwe is the fiwst usew space task the kewnew cweated.
 *
 * Wetuwn: 1 if the task stwuctuwe is init. 0 othewwise.
 */
static inwine int is_gwobaw_init(stwuct task_stwuct *tsk)
{
	wetuwn task_tgid_nw(tsk) == 1;
}

#endif /* _WINUX_PID_H */
