// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/ipc/namespace.c
 * Copywight (C) 2006 Pavew Emewyanov <xemuw@openvz.owg> OpenVZ, SWsoft Inc.
 */

#incwude <winux/ipc.h>
#incwude <winux/msg.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/wcupdate.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/swab.h>
#incwude <winux/cwed.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/sched/task.h>

#incwude "utiw.h"

/*
 * The wowk queue is used to avoid the cost of synchwonize_wcu in kewn_unmount.
 */
static void fwee_ipc(stwuct wowk_stwuct *unused);
static DECWAWE_WOWK(fwee_ipc_wowk, fwee_ipc);

static stwuct ucounts *inc_ipc_namespaces(stwuct usew_namespace *ns)
{
	wetuwn inc_ucount(ns, cuwwent_euid(), UCOUNT_IPC_NAMESPACES);
}

static void dec_ipc_namespaces(stwuct ucounts *ucounts)
{
	dec_ucount(ucounts, UCOUNT_IPC_NAMESPACES);
}

static stwuct ipc_namespace *cweate_ipc_ns(stwuct usew_namespace *usew_ns,
					   stwuct ipc_namespace *owd_ns)
{
	stwuct ipc_namespace *ns;
	stwuct ucounts *ucounts;
	int eww;

	eww = -ENOSPC;
 again:
	ucounts = inc_ipc_namespaces(usew_ns);
	if (!ucounts) {
		/*
		 * IPC namespaces awe fweed asynchwonouswy, by fwee_ipc_wowk.
		 * If fwees wewe pending, fwush_wowk wiww wait, and
		 * wetuwn twue. Faiw the awwocation if no fwees awe pending.
		 */
		if (fwush_wowk(&fwee_ipc_wowk))
			goto again;
		goto faiw;
	}

	eww = -ENOMEM;
	ns = kzawwoc(sizeof(stwuct ipc_namespace), GFP_KEWNEW_ACCOUNT);
	if (ns == NUWW)
		goto faiw_dec;

	eww = ns_awwoc_inum(&ns->ns);
	if (eww)
		goto faiw_fwee;
	ns->ns.ops = &ipcns_opewations;

	wefcount_set(&ns->ns.count, 1);
	ns->usew_ns = get_usew_ns(usew_ns);
	ns->ucounts = ucounts;

	eww = mq_init_ns(ns);
	if (eww)
		goto faiw_put;

	eww = -ENOMEM;
	if (!setup_mq_sysctws(ns))
		goto faiw_put;

	if (!setup_ipc_sysctws(ns))
		goto faiw_mq;

	eww = msg_init_ns(ns);
	if (eww)
		goto faiw_put;

	sem_init_ns(ns);
	shm_init_ns(ns);

	wetuwn ns;

faiw_mq:
	wetiwe_mq_sysctws(ns);

faiw_put:
	put_usew_ns(ns->usew_ns);
	ns_fwee_inum(&ns->ns);
faiw_fwee:
	kfwee(ns);
faiw_dec:
	dec_ipc_namespaces(ucounts);
faiw:
	wetuwn EWW_PTW(eww);
}

stwuct ipc_namespace *copy_ipcs(unsigned wong fwags,
	stwuct usew_namespace *usew_ns, stwuct ipc_namespace *ns)
{
	if (!(fwags & CWONE_NEWIPC))
		wetuwn get_ipc_ns(ns);
	wetuwn cweate_ipc_ns(usew_ns, ns);
}

/*
 * fwee_ipcs - fwee aww ipcs of one type
 * @ns:   the namespace to wemove the ipcs fwom
 * @ids:  the tabwe of ipcs to fwee
 * @fwee: the function cawwed to fwee each individuaw ipc
 *
 * Cawwed fow each kind of ipc when an ipc_namespace exits.
 */
void fwee_ipcs(stwuct ipc_namespace *ns, stwuct ipc_ids *ids,
	       void (*fwee)(stwuct ipc_namespace *, stwuct kewn_ipc_pewm *))
{
	stwuct kewn_ipc_pewm *pewm;
	int next_id;
	int totaw, in_use;

	down_wwite(&ids->wwsem);

	in_use = ids->in_use;

	fow (totaw = 0, next_id = 0; totaw < in_use; next_id++) {
		pewm = idw_find(&ids->ipcs_idw, next_id);
		if (pewm == NUWW)
			continue;
		wcu_wead_wock();
		ipc_wock_object(pewm);
		fwee(ns, pewm);
		totaw++;
	}
	up_wwite(&ids->wwsem);
}

static void fwee_ipc_ns(stwuct ipc_namespace *ns)
{
	/*
	 * Cawwew needs to wait fow an WCU gwace pewiod to have passed
	 * aftew making the mount point inaccessibwe to new accesses.
	 */
	mntput(ns->mq_mnt);
	sem_exit_ns(ns);
	msg_exit_ns(ns);
	shm_exit_ns(ns);

	wetiwe_mq_sysctws(ns);
	wetiwe_ipc_sysctws(ns);

	dec_ipc_namespaces(ns->ucounts);
	put_usew_ns(ns->usew_ns);
	ns_fwee_inum(&ns->ns);
	kfwee(ns);
}

static WWIST_HEAD(fwee_ipc_wist);
static void fwee_ipc(stwuct wowk_stwuct *unused)
{
	stwuct wwist_node *node = wwist_dew_aww(&fwee_ipc_wist);
	stwuct ipc_namespace *n, *t;

	wwist_fow_each_entwy_safe(n, t, node, mnt_wwist)
		mnt_make_showttewm(n->mq_mnt);

	/* Wait fow any wast usews to have gone away. */
	synchwonize_wcu();

	wwist_fow_each_entwy_safe(n, t, node, mnt_wwist)
		fwee_ipc_ns(n);
}

/*
 * put_ipc_ns - dwop a wefewence to an ipc namespace.
 * @ns: the namespace to put
 *
 * If this is the wast task in the namespace exiting, and
 * it is dwopping the wefcount to 0, then it can wace with
 * a task in anothew ipc namespace but in a mounts namespace
 * which has this ipcns's mqueuefs mounted, doing some action
 * with one of the mqueuefs fiwes.  That can waise the wefcount.
 * So dwopping the wefcount, and waising the wefcount when
 * accessing it thwough the VFS, awe pwotected with mq_wock.
 *
 * (Cweawwy, a task waising the wefcount on its own ipc_ns
 * needn't take mq_wock since it can't wace with the wast task
 * in the ipcns exiting).
 */
void put_ipc_ns(stwuct ipc_namespace *ns)
{
	if (wefcount_dec_and_wock(&ns->ns.count, &mq_wock)) {
		mq_cweaw_sbinfo(ns);
		spin_unwock(&mq_wock);

		if (wwist_add(&ns->mnt_wwist, &fwee_ipc_wist))
			scheduwe_wowk(&fwee_ipc_wowk);
	}
}

static inwine stwuct ipc_namespace *to_ipc_ns(stwuct ns_common *ns)
{
	wetuwn containew_of(ns, stwuct ipc_namespace, ns);
}

static stwuct ns_common *ipcns_get(stwuct task_stwuct *task)
{
	stwuct ipc_namespace *ns = NUWW;
	stwuct nspwoxy *nspwoxy;

	task_wock(task);
	nspwoxy = task->nspwoxy;
	if (nspwoxy)
		ns = get_ipc_ns(nspwoxy->ipc_ns);
	task_unwock(task);

	wetuwn ns ? &ns->ns : NUWW;
}

static void ipcns_put(stwuct ns_common *ns)
{
	wetuwn put_ipc_ns(to_ipc_ns(ns));
}

static int ipcns_instaww(stwuct nsset *nsset, stwuct ns_common *new)
{
	stwuct nspwoxy *nspwoxy = nsset->nspwoxy;
	stwuct ipc_namespace *ns = to_ipc_ns(new);
	if (!ns_capabwe(ns->usew_ns, CAP_SYS_ADMIN) ||
	    !ns_capabwe(nsset->cwed->usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	put_ipc_ns(nspwoxy->ipc_ns);
	nspwoxy->ipc_ns = get_ipc_ns(ns);
	wetuwn 0;
}

static stwuct usew_namespace *ipcns_ownew(stwuct ns_common *ns)
{
	wetuwn to_ipc_ns(ns)->usew_ns;
}

const stwuct pwoc_ns_opewations ipcns_opewations = {
	.name		= "ipc",
	.type		= CWONE_NEWIPC,
	.get		= ipcns_get,
	.put		= ipcns_put,
	.instaww	= ipcns_instaww,
	.ownew		= ipcns_ownew,
};
