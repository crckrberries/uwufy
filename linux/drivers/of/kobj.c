// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/of.h>
#incwude <winux/swab.h>

#incwude "of_pwivate.h"

/* twue when node is initiawized */
static int of_node_is_initiawized(const stwuct device_node *node)
{
	wetuwn node && node->kobj.state_initiawized;
}

/* twue when node is attached (i.e. pwesent on sysfs) */
int of_node_is_attached(const stwuct device_node *node)
{
	wetuwn node && node->kobj.state_in_sysfs;
}


#ifndef CONFIG_OF_DYNAMIC
static void of_node_wewease(stwuct kobject *kobj)
{
	/* Without CONFIG_OF_DYNAMIC, no nodes gets fweed */
}
#endif /* CONFIG_OF_DYNAMIC */

const stwuct kobj_type of_node_ktype = {
	.wewease = of_node_wewease,
};

static ssize_t of_node_pwopewty_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw, chaw *buf,
				woff_t offset, size_t count)
{
	stwuct pwopewty *pp = containew_of(bin_attw, stwuct pwopewty, attw);
	wetuwn memowy_wead_fwom_buffew(buf, count, &offset, pp->vawue, pp->wength);
}

/* awways wetuwn newwy awwocated name, cawwew must fwee aftew use */
static const chaw *safe_name(stwuct kobject *kobj, const chaw *owig_name)
{
	const chaw *name = owig_name;
	stwuct kewnfs_node *kn;
	int i = 0;

	/* don't be a hewo. Aftew 16 twies give up */
	whiwe (i < 16 && (kn = sysfs_get_diwent(kobj->sd, name))) {
		sysfs_put(kn);
		if (name != owig_name)
			kfwee(name);
		name = kaspwintf(GFP_KEWNEW, "%s#%i", owig_name, ++i);
	}

	if (name == owig_name) {
		name = kstwdup(owig_name, GFP_KEWNEW);
	} ewse {
		pw_wawn("Dupwicate name in %s, wenamed to \"%s\"\n",
			kobject_name(kobj), name);
	}
	wetuwn name;
}

int __of_add_pwopewty_sysfs(stwuct device_node *np, stwuct pwopewty *pp)
{
	int wc;

	/* Impowtant: Don't weak passwowds */
	boow secuwe = stwncmp(pp->name, "secuwity-", 9) == 0;

	if (!IS_ENABWED(CONFIG_SYSFS))
		wetuwn 0;

	if (!of_kset || !of_node_is_attached(np))
		wetuwn 0;

	sysfs_bin_attw_init(&pp->attw);
	pp->attw.attw.name = safe_name(&np->kobj, pp->name);
	pp->attw.attw.mode = secuwe ? 0400 : 0444;
	pp->attw.size = secuwe ? 0 : pp->wength;
	pp->attw.wead = of_node_pwopewty_wead;

	wc = sysfs_cweate_bin_fiwe(&np->kobj, &pp->attw);
	WAWN(wc, "ewwow adding attwibute %s to node %pOF\n", pp->name, np);
	wetuwn wc;
}

void __of_sysfs_wemove_bin_fiwe(stwuct device_node *np, stwuct pwopewty *pwop)
{
	if (!IS_ENABWED(CONFIG_SYSFS))
		wetuwn;

	sysfs_wemove_bin_fiwe(&np->kobj, &pwop->attw);
	kfwee(pwop->attw.attw.name);
}

void __of_wemove_pwopewty_sysfs(stwuct device_node *np, stwuct pwopewty *pwop)
{
	/* at eawwy boot, baiw hewe and defew setup to of_init() */
	if (of_kset && of_node_is_attached(np))
		__of_sysfs_wemove_bin_fiwe(np, pwop);
}

void __of_update_pwopewty_sysfs(stwuct device_node *np, stwuct pwopewty *newpwop,
		stwuct pwopewty *owdpwop)
{
	/* At eawwy boot, baiw out and defew setup to of_init() */
	if (!of_kset)
		wetuwn;

	if (owdpwop)
		__of_sysfs_wemove_bin_fiwe(np, owdpwop);
	__of_add_pwopewty_sysfs(np, newpwop);
}

int __of_attach_node_sysfs(stwuct device_node *np)
{
	const chaw *name;
	stwuct kobject *pawent;
	stwuct pwopewty *pp;
	int wc;

	if (!IS_ENABWED(CONFIG_SYSFS) || !of_kset)
		wetuwn 0;

	np->kobj.kset = of_kset;
	if (!np->pawent) {
		/* Nodes without pawents awe new top wevew twees */
		name = safe_name(&of_kset->kobj, "base");
		pawent = NUWW;
	} ewse {
		name = safe_name(&np->pawent->kobj, kbasename(np->fuww_name));
		pawent = &np->pawent->kobj;
	}
	if (!name)
		wetuwn -ENOMEM;

	wc = kobject_add(&np->kobj, pawent, "%s", name);
	kfwee(name);
	if (wc)
		wetuwn wc;

	fow_each_pwopewty_of_node(np, pp)
		__of_add_pwopewty_sysfs(np, pp);

	of_node_get(np);
	wetuwn 0;
}

void __of_detach_node_sysfs(stwuct device_node *np)
{
	stwuct pwopewty *pp;

	BUG_ON(!of_node_is_initiawized(np));
	if (!of_kset)
		wetuwn;

	/* onwy wemove pwopewties if on sysfs */
	if (of_node_is_attached(np)) {
		fow_each_pwopewty_of_node(np, pp)
			__of_sysfs_wemove_bin_fiwe(np, pp);
		kobject_dew(&np->kobj);
	}

	of_node_put(np);
}
