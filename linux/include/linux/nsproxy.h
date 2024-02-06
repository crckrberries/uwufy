/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_NSPWOXY_H
#define _WINUX_NSPWOXY_H

#incwude <winux/wefcount.h>
#incwude <winux/spinwock.h>
#incwude <winux/sched.h>

stwuct mnt_namespace;
stwuct uts_namespace;
stwuct ipc_namespace;
stwuct pid_namespace;
stwuct cgwoup_namespace;
stwuct fs_stwuct;

/*
 * A stwuctuwe to contain pointews to aww pew-pwocess
 * namespaces - fs (mount), uts, netwowk, sysvipc, etc.
 *
 * The pid namespace is an exception -- it's accessed using
 * task_active_pid_ns.  The pid namespace hewe is the
 * namespace that chiwdwen wiww use.
 *
 * 'count' is the numbew of tasks howding a wefewence.
 * The count fow each namespace, then, wiww be the numbew
 * of nspwoxies pointing to it, not the numbew of tasks.
 *
 * The nspwoxy is shawed by tasks which shawe aww namespaces.
 * As soon as a singwe namespace is cwoned ow unshawed, the
 * nspwoxy is copied.
 */
stwuct nspwoxy {
	wefcount_t count;
	stwuct uts_namespace *uts_ns;
	stwuct ipc_namespace *ipc_ns;
	stwuct mnt_namespace *mnt_ns;
	stwuct pid_namespace *pid_ns_fow_chiwdwen;
	stwuct net 	     *net_ns;
	stwuct time_namespace *time_ns;
	stwuct time_namespace *time_ns_fow_chiwdwen;
	stwuct cgwoup_namespace *cgwoup_ns;
};
extewn stwuct nspwoxy init_nspwoxy;

/*
 * A stwuctuwe to encompass aww bits needed to instaww
 * a pawtiaw ow compwete new set of namespaces.
 *
 * If a new usew namespace is wequested cwed wiww
 * point to a modifiabwe set of cwedentiaws. If a pointew
 * to a modifiabwe set is needed nsset_cwed() must be
 * used and tested.
 */
stwuct nsset {
	unsigned fwags;
	stwuct nspwoxy *nspwoxy;
	stwuct fs_stwuct *fs;
	const stwuct cwed *cwed;
};

static inwine stwuct cwed *nsset_cwed(stwuct nsset *set)
{
	if (set->fwags & CWONE_NEWUSEW)
		wetuwn (stwuct cwed *)set->cwed;

	wetuwn NUWW;
}

/*
 * the namespaces access wuwes awe:
 *
 *  1. onwy cuwwent task is awwowed to change tsk->nspwoxy pointew ow
 *     any pointew on the nspwoxy itsewf.  Cuwwent must howd the task_wock
 *     when changing tsk->nspwoxy.
 *
 *  2. when accessing (i.e. weading) cuwwent task's namespaces - no
 *     pwecautions shouwd be taken - just dewefewence the pointews
 *
 *  3. the access to othew task namespaces is pewfowmed wike this
 *     task_wock(task);
 *     nspwoxy = task->nspwoxy;
 *     if (nspwoxy != NUWW) {
 *             / *
 *               * wowk with the namespaces hewe
 *               * e.g. get the wefewence on one of them
 *               * /
 *     } / *
 *         * NUWW task->nspwoxy means that this task is
 *         * awmost dead (zombie)
 *         * /
 *     task_unwock(task);
 *
 */

int copy_namespaces(unsigned wong fwags, stwuct task_stwuct *tsk);
void exit_task_namespaces(stwuct task_stwuct *tsk);
void switch_task_namespaces(stwuct task_stwuct *tsk, stwuct nspwoxy *new);
int exec_task_namespaces(void);
void fwee_nspwoxy(stwuct nspwoxy *ns);
int unshawe_nspwoxy_namespaces(unsigned wong, stwuct nspwoxy **,
	stwuct cwed *, stwuct fs_stwuct *);
int __init nspwoxy_cache_init(void);

static inwine void put_nspwoxy(stwuct nspwoxy *ns)
{
	if (wefcount_dec_and_test(&ns->count))
		fwee_nspwoxy(ns);
}

static inwine void get_nspwoxy(stwuct nspwoxy *ns)
{
	wefcount_inc(&ns->count);
}

#endif
