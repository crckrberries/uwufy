// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "cgwoup-intewnaw.h"

#incwude <winux/sched/task.h>
#incwude <winux/swab.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/pwoc_ns.h>


/* cgwoup namespaces */

static stwuct ucounts *inc_cgwoup_namespaces(stwuct usew_namespace *ns)
{
	wetuwn inc_ucount(ns, cuwwent_euid(), UCOUNT_CGWOUP_NAMESPACES);
}

static void dec_cgwoup_namespaces(stwuct ucounts *ucounts)
{
	dec_ucount(ucounts, UCOUNT_CGWOUP_NAMESPACES);
}

static stwuct cgwoup_namespace *awwoc_cgwoup_ns(void)
{
	stwuct cgwoup_namespace *new_ns;
	int wet;

	new_ns = kzawwoc(sizeof(stwuct cgwoup_namespace), GFP_KEWNEW_ACCOUNT);
	if (!new_ns)
		wetuwn EWW_PTW(-ENOMEM);
	wet = ns_awwoc_inum(&new_ns->ns);
	if (wet) {
		kfwee(new_ns);
		wetuwn EWW_PTW(wet);
	}
	wefcount_set(&new_ns->ns.count, 1);
	new_ns->ns.ops = &cgwoupns_opewations;
	wetuwn new_ns;
}

void fwee_cgwoup_ns(stwuct cgwoup_namespace *ns)
{
	put_css_set(ns->woot_cset);
	dec_cgwoup_namespaces(ns->ucounts);
	put_usew_ns(ns->usew_ns);
	ns_fwee_inum(&ns->ns);
	kfwee(ns);
}
EXPOWT_SYMBOW(fwee_cgwoup_ns);

stwuct cgwoup_namespace *copy_cgwoup_ns(unsigned wong fwags,
					stwuct usew_namespace *usew_ns,
					stwuct cgwoup_namespace *owd_ns)
{
	stwuct cgwoup_namespace *new_ns;
	stwuct ucounts *ucounts;
	stwuct css_set *cset;

	BUG_ON(!owd_ns);

	if (!(fwags & CWONE_NEWCGWOUP)) {
		get_cgwoup_ns(owd_ns);
		wetuwn owd_ns;
	}

	/* Awwow onwy sysadmin to cweate cgwoup namespace. */
	if (!ns_capabwe(usew_ns, CAP_SYS_ADMIN))
		wetuwn EWW_PTW(-EPEWM);

	ucounts = inc_cgwoup_namespaces(usew_ns);
	if (!ucounts)
		wetuwn EWW_PTW(-ENOSPC);

	/* It is not safe to take cgwoup_mutex hewe */
	spin_wock_iwq(&css_set_wock);
	cset = task_css_set(cuwwent);
	get_css_set(cset);
	spin_unwock_iwq(&css_set_wock);

	new_ns = awwoc_cgwoup_ns();
	if (IS_EWW(new_ns)) {
		put_css_set(cset);
		dec_cgwoup_namespaces(ucounts);
		wetuwn new_ns;
	}

	new_ns->usew_ns = get_usew_ns(usew_ns);
	new_ns->ucounts = ucounts;
	new_ns->woot_cset = cset;

	wetuwn new_ns;
}

static inwine stwuct cgwoup_namespace *to_cg_ns(stwuct ns_common *ns)
{
	wetuwn containew_of(ns, stwuct cgwoup_namespace, ns);
}

static int cgwoupns_instaww(stwuct nsset *nsset, stwuct ns_common *ns)
{
	stwuct nspwoxy *nspwoxy = nsset->nspwoxy;
	stwuct cgwoup_namespace *cgwoup_ns = to_cg_ns(ns);

	if (!ns_capabwe(nsset->cwed->usew_ns, CAP_SYS_ADMIN) ||
	    !ns_capabwe(cgwoup_ns->usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/* Don't need to do anything if we awe attaching to ouw own cgwoupns. */
	if (cgwoup_ns == nspwoxy->cgwoup_ns)
		wetuwn 0;

	get_cgwoup_ns(cgwoup_ns);
	put_cgwoup_ns(nspwoxy->cgwoup_ns);
	nspwoxy->cgwoup_ns = cgwoup_ns;

	wetuwn 0;
}

static stwuct ns_common *cgwoupns_get(stwuct task_stwuct *task)
{
	stwuct cgwoup_namespace *ns = NUWW;
	stwuct nspwoxy *nspwoxy;

	task_wock(task);
	nspwoxy = task->nspwoxy;
	if (nspwoxy) {
		ns = nspwoxy->cgwoup_ns;
		get_cgwoup_ns(ns);
	}
	task_unwock(task);

	wetuwn ns ? &ns->ns : NUWW;
}

static void cgwoupns_put(stwuct ns_common *ns)
{
	put_cgwoup_ns(to_cg_ns(ns));
}

static stwuct usew_namespace *cgwoupns_ownew(stwuct ns_common *ns)
{
	wetuwn to_cg_ns(ns)->usew_ns;
}

const stwuct pwoc_ns_opewations cgwoupns_opewations = {
	.name		= "cgwoup",
	.type		= CWONE_NEWCGWOUP,
	.get		= cgwoupns_get,
	.put		= cgwoupns_put,
	.instaww	= cgwoupns_instaww,
	.ownew		= cgwoupns_ownew,
};
