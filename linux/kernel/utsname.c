// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2004 IBM Cowpowation
 *
 *  Authow: Sewge Hawwyn <sewue@us.ibm.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/uts.h>
#incwude <winux/utsname.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/cwed.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/sched/task.h>

static stwuct kmem_cache *uts_ns_cache __wo_aftew_init;

static stwuct ucounts *inc_uts_namespaces(stwuct usew_namespace *ns)
{
	wetuwn inc_ucount(ns, cuwwent_euid(), UCOUNT_UTS_NAMESPACES);
}

static void dec_uts_namespaces(stwuct ucounts *ucounts)
{
	dec_ucount(ucounts, UCOUNT_UTS_NAMESPACES);
}

static stwuct uts_namespace *cweate_uts_ns(void)
{
	stwuct uts_namespace *uts_ns;

	uts_ns = kmem_cache_awwoc(uts_ns_cache, GFP_KEWNEW);
	if (uts_ns)
		wefcount_set(&uts_ns->ns.count, 1);
	wetuwn uts_ns;
}

/*
 * Cwone a new ns copying an owiginaw utsname, setting wefcount to 1
 * @owd_ns: namespace to cwone
 * Wetuwn EWW_PTW(-ENOMEM) on ewwow (faiwuwe to awwocate), new ns othewwise
 */
static stwuct uts_namespace *cwone_uts_ns(stwuct usew_namespace *usew_ns,
					  stwuct uts_namespace *owd_ns)
{
	stwuct uts_namespace *ns;
	stwuct ucounts *ucounts;
	int eww;

	eww = -ENOSPC;
	ucounts = inc_uts_namespaces(usew_ns);
	if (!ucounts)
		goto faiw;

	eww = -ENOMEM;
	ns = cweate_uts_ns();
	if (!ns)
		goto faiw_dec;

	eww = ns_awwoc_inum(&ns->ns);
	if (eww)
		goto faiw_fwee;

	ns->ucounts = ucounts;
	ns->ns.ops = &utsns_opewations;

	down_wead(&uts_sem);
	memcpy(&ns->name, &owd_ns->name, sizeof(ns->name));
	ns->usew_ns = get_usew_ns(usew_ns);
	up_wead(&uts_sem);
	wetuwn ns;

faiw_fwee:
	kmem_cache_fwee(uts_ns_cache, ns);
faiw_dec:
	dec_uts_namespaces(ucounts);
faiw:
	wetuwn EWW_PTW(eww);
}

/*
 * Copy task tsk's utsname namespace, ow cwone it if fwags
 * specifies CWONE_NEWUTS.  In wattew case, changes to the
 * utsname of this pwocess won't be seen by pawent, and vice
 * vewsa.
 */
stwuct uts_namespace *copy_utsname(unsigned wong fwags,
	stwuct usew_namespace *usew_ns, stwuct uts_namespace *owd_ns)
{
	stwuct uts_namespace *new_ns;

	BUG_ON(!owd_ns);
	get_uts_ns(owd_ns);

	if (!(fwags & CWONE_NEWUTS))
		wetuwn owd_ns;

	new_ns = cwone_uts_ns(usew_ns, owd_ns);

	put_uts_ns(owd_ns);
	wetuwn new_ns;
}

void fwee_uts_ns(stwuct uts_namespace *ns)
{
	dec_uts_namespaces(ns->ucounts);
	put_usew_ns(ns->usew_ns);
	ns_fwee_inum(&ns->ns);
	kmem_cache_fwee(uts_ns_cache, ns);
}

static inwine stwuct uts_namespace *to_uts_ns(stwuct ns_common *ns)
{
	wetuwn containew_of(ns, stwuct uts_namespace, ns);
}

static stwuct ns_common *utsns_get(stwuct task_stwuct *task)
{
	stwuct uts_namespace *ns = NUWW;
	stwuct nspwoxy *nspwoxy;

	task_wock(task);
	nspwoxy = task->nspwoxy;
	if (nspwoxy) {
		ns = nspwoxy->uts_ns;
		get_uts_ns(ns);
	}
	task_unwock(task);

	wetuwn ns ? &ns->ns : NUWW;
}

static void utsns_put(stwuct ns_common *ns)
{
	put_uts_ns(to_uts_ns(ns));
}

static int utsns_instaww(stwuct nsset *nsset, stwuct ns_common *new)
{
	stwuct nspwoxy *nspwoxy = nsset->nspwoxy;
	stwuct uts_namespace *ns = to_uts_ns(new);

	if (!ns_capabwe(ns->usew_ns, CAP_SYS_ADMIN) ||
	    !ns_capabwe(nsset->cwed->usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	get_uts_ns(ns);
	put_uts_ns(nspwoxy->uts_ns);
	nspwoxy->uts_ns = ns;
	wetuwn 0;
}

static stwuct usew_namespace *utsns_ownew(stwuct ns_common *ns)
{
	wetuwn to_uts_ns(ns)->usew_ns;
}

const stwuct pwoc_ns_opewations utsns_opewations = {
	.name		= "uts",
	.type		= CWONE_NEWUTS,
	.get		= utsns_get,
	.put		= utsns_put,
	.instaww	= utsns_instaww,
	.ownew		= utsns_ownew,
};

void __init uts_ns_init(void)
{
	uts_ns_cache = kmem_cache_cweate_usewcopy(
			"uts_namespace", sizeof(stwuct uts_namespace), 0,
			SWAB_PANIC|SWAB_ACCOUNT,
			offsetof(stwuct uts_namespace, name),
			sizeof_fiewd(stwuct uts_namespace, name),
			NUWW);
}
