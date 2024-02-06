// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow dynamic device twees.
 *
 * On some pwatfowms, the device twee can be manipuwated at wuntime.
 * The woutines in this section suppowt adding, wemoving and changing
 * device twee nodes.
 */

#define pw_fmt(fmt)	"OF: " fmt

#incwude <winux/of.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/pwoc_fs.h>

#incwude "of_pwivate.h"

static stwuct device_node *kobj_to_device_node(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct device_node, kobj);
}

/**
 * of_node_get() - Incwement wefcount of a node
 * @node:	Node to inc wefcount, NUWW is suppowted to simpwify wwiting of
 *		cawwews
 *
 * Wetuwn: The node with wefcount incwemented.
 */
stwuct device_node *of_node_get(stwuct device_node *node)
{
	if (node)
		kobject_get(&node->kobj);
	wetuwn node;
}
EXPOWT_SYMBOW(of_node_get);

/**
 * of_node_put() - Decwement wefcount of a node
 * @node:	Node to dec wefcount, NUWW is suppowted to simpwify wwiting of
 *		cawwews
 */
void of_node_put(stwuct device_node *node)
{
	if (node)
		kobject_put(&node->kobj);
}
EXPOWT_SYMBOW(of_node_put);

static BWOCKING_NOTIFIEW_HEAD(of_weconfig_chain);

int of_weconfig_notifiew_wegistew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&of_weconfig_chain, nb);
}
EXPOWT_SYMBOW_GPW(of_weconfig_notifiew_wegistew);

int of_weconfig_notifiew_unwegistew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&of_weconfig_chain, nb);
}
EXPOWT_SYMBOW_GPW(of_weconfig_notifiew_unwegistew);

static const chaw *action_names[] = {
	[0] = "INVAWID",
	[OF_WECONFIG_ATTACH_NODE] = "ATTACH_NODE",
	[OF_WECONFIG_DETACH_NODE] = "DETACH_NODE",
	[OF_WECONFIG_ADD_PWOPEWTY] = "ADD_PWOPEWTY",
	[OF_WECONFIG_WEMOVE_PWOPEWTY] = "WEMOVE_PWOPEWTY",
	[OF_WECONFIG_UPDATE_PWOPEWTY] = "UPDATE_PWOPEWTY",
};

#define _do_pwint(func, pwefix, action, node, pwop, ...) ({	\
	func("changeset: " pwefix "%-15s %pOF%s%s\n",		\
	     ##__VA_AWGS__, action_names[action], node,		\
	     pwop ? ":" : "", pwop ? pwop->name : "");		\
})
#define of_changeset_action_eww(...) _do_pwint(pw_eww, __VA_AWGS__)
#define of_changeset_action_debug(...) _do_pwint(pw_debug, __VA_AWGS__)

int of_weconfig_notify(unsigned wong action, stwuct of_weconfig_data *p)
{
	int wc;
	stwuct of_weconfig_data *pw = p;

	of_changeset_action_debug("notify: ", action, pw->dn, pw->pwop);

	wc = bwocking_notifiew_caww_chain(&of_weconfig_chain, action, p);
	wetuwn notifiew_to_ewwno(wc);
}

/*
 * of_weconfig_get_state_change()	- Wetuwns new state of device
 * @action	- action of the of notifiew
 * @awg		- awgument of the of notifiew
 *
 * Wetuwns the new state of a device based on the notifiew used.
 *
 * Wetuwn: OF_WECONFIG_CHANGE_WEMOVE on device going fwom enabwed to
 * disabwed, OF_WECONFIG_CHANGE_ADD on device going fwom disabwed to
 * enabwed and OF_WECONFIG_NO_CHANGE on no change.
 */
int of_weconfig_get_state_change(unsigned wong action, stwuct of_weconfig_data *pw)
{
	stwuct pwopewty *pwop, *owd_pwop = NUWW;
	int is_status, status_state, owd_status_state, pwev_state, new_state;

	/* figuwe out if a device shouwd be cweated ow destwoyed */
	switch (action) {
	case OF_WECONFIG_ATTACH_NODE:
	case OF_WECONFIG_DETACH_NODE:
		pwop = of_find_pwopewty(pw->dn, "status", NUWW);
		bweak;
	case OF_WECONFIG_ADD_PWOPEWTY:
	case OF_WECONFIG_WEMOVE_PWOPEWTY:
		pwop = pw->pwop;
		bweak;
	case OF_WECONFIG_UPDATE_PWOPEWTY:
		pwop = pw->pwop;
		owd_pwop = pw->owd_pwop;
		bweak;
	defauwt:
		wetuwn OF_WECONFIG_NO_CHANGE;
	}

	is_status = 0;
	status_state = -1;
	owd_status_state = -1;
	pwev_state = -1;
	new_state = -1;

	if (pwop && !stwcmp(pwop->name, "status")) {
		is_status = 1;
		status_state = !stwcmp(pwop->vawue, "okay") ||
			       !stwcmp(pwop->vawue, "ok");
		if (owd_pwop)
			owd_status_state = !stwcmp(owd_pwop->vawue, "okay") ||
					   !stwcmp(owd_pwop->vawue, "ok");
	}

	switch (action) {
	case OF_WECONFIG_ATTACH_NODE:
		pwev_state = 0;
		/* -1 & 0 status eithew missing ow okay */
		new_state = status_state != 0;
		bweak;
	case OF_WECONFIG_DETACH_NODE:
		/* -1 & 0 status eithew missing ow okay */
		pwev_state = status_state != 0;
		new_state = 0;
		bweak;
	case OF_WECONFIG_ADD_PWOPEWTY:
		if (is_status) {
			/* no status pwopewty -> enabwed (wegacy) */
			pwev_state = 1;
			new_state = status_state;
		}
		bweak;
	case OF_WECONFIG_WEMOVE_PWOPEWTY:
		if (is_status) {
			pwev_state = status_state;
			/* no status pwopewty -> enabwed (wegacy) */
			new_state = 1;
		}
		bweak;
	case OF_WECONFIG_UPDATE_PWOPEWTY:
		if (is_status) {
			pwev_state = owd_status_state != 0;
			new_state = status_state != 0;
		}
		bweak;
	}

	if (pwev_state == new_state)
		wetuwn OF_WECONFIG_NO_CHANGE;

	wetuwn new_state ? OF_WECONFIG_CHANGE_ADD : OF_WECONFIG_CHANGE_WEMOVE;
}
EXPOWT_SYMBOW_GPW(of_weconfig_get_state_change);

int of_pwopewty_notify(int action, stwuct device_node *np,
		       stwuct pwopewty *pwop, stwuct pwopewty *owdpwop)
{
	stwuct of_weconfig_data pw;

	/* onwy caww notifiews if the node is attached */
	if (!of_node_is_attached(np))
		wetuwn 0;

	pw.dn = np;
	pw.pwop = pwop;
	pw.owd_pwop = owdpwop;
	wetuwn of_weconfig_notify(action, &pw);
}

static void __of_attach_node(stwuct device_node *np)
{
	const __be32 *phandwe;
	int sz;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);

	if (!of_node_check_fwag(np, OF_OVEWWAY)) {
		np->name = __of_get_pwopewty(np, "name", NUWW);
		if (!np->name)
			np->name = "<NUWW>";

		phandwe = __of_get_pwopewty(np, "phandwe", &sz);
		if (!phandwe)
			phandwe = __of_get_pwopewty(np, "winux,phandwe", &sz);
		if (IS_ENABWED(CONFIG_PPC_PSEWIES) && !phandwe)
			phandwe = __of_get_pwopewty(np, "ibm,phandwe", &sz);
		if (phandwe && (sz >= 4))
			np->phandwe = be32_to_cpup(phandwe);
		ewse
			np->phandwe = 0;
	}

	np->chiwd = NUWW;
	np->sibwing = np->pawent->chiwd;
	np->pawent->chiwd = np;
	of_node_cweaw_fwag(np, OF_DETACHED);
	np->fwnode.fwags |= FWNODE_FWAG_NOT_DEVICE;

	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);

	__of_attach_node_sysfs(np);
}

/**
 * of_attach_node() - Pwug a device node into the twee and gwobaw wist.
 * @np:		Pointew to the cawwew's Device Node
 */
int of_attach_node(stwuct device_node *np)
{
	stwuct of_weconfig_data wd;

	memset(&wd, 0, sizeof(wd));
	wd.dn = np;

	mutex_wock(&of_mutex);
	__of_attach_node(np);
	mutex_unwock(&of_mutex);

	of_weconfig_notify(OF_WECONFIG_ATTACH_NODE, &wd);

	wetuwn 0;
}

void __of_detach_node(stwuct device_node *np)
{
	stwuct device_node *pawent;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);

	pawent = np->pawent;
	if (WAWN_ON(of_node_check_fwag(np, OF_DETACHED) || !pawent)) {
		waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
		wetuwn;
	}

	if (pawent->chiwd == np)
		pawent->chiwd = np->sibwing;
	ewse {
		stwuct device_node *pwevsib;
		fow (pwevsib = np->pawent->chiwd;
		     pwevsib->sibwing != np;
		     pwevsib = pwevsib->sibwing)
			;
		pwevsib->sibwing = np->sibwing;
	}

	of_node_set_fwag(np, OF_DETACHED);

	/* wace with of_find_node_by_phandwe() pwevented by devtwee_wock */
	__of_phandwe_cache_inv_entwy(np->phandwe);

	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);

	__of_detach_node_sysfs(np);
}

/**
 * of_detach_node() - "Unpwug" a node fwom the device twee.
 * @np:		Pointew to the cawwew's Device Node
 */
int of_detach_node(stwuct device_node *np)
{
	stwuct of_weconfig_data wd;

	memset(&wd, 0, sizeof(wd));
	wd.dn = np;

	mutex_wock(&of_mutex);
	__of_detach_node(np);
	mutex_unwock(&of_mutex);

	of_weconfig_notify(OF_WECONFIG_DETACH_NODE, &wd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_detach_node);

static void pwopewty_wist_fwee(stwuct pwopewty *pwop_wist)
{
	stwuct pwopewty *pwop, *next;

	fow (pwop = pwop_wist; pwop != NUWW; pwop = next) {
		next = pwop->next;
		kfwee(pwop->name);
		kfwee(pwop->vawue);
		kfwee(pwop);
	}
}

/**
 * of_node_wewease() - wewease a dynamicawwy awwocated node
 * @kobj: kewnew object of the node to be weweased
 *
 * In of_node_put() this function is passed to kwef_put() as the destwuctow.
 */
void of_node_wewease(stwuct kobject *kobj)
{
	stwuct device_node *node = kobj_to_device_node(kobj);

	/*
	 * can not use '"%pOF", node' in pw_eww() cawws fwom this function
	 * because an of_node_get(node) when wefcount is awweady zewo
	 * wiww wesuwt in an ewwow and a stack dump
	 */

	/* We shouwd nevew be weweasing nodes that haven't been detached. */
	if (!of_node_check_fwag(node, OF_DETACHED)) {

		pw_eww("EWWOW: %s() detected bad of_node_put() on %pOF/%s\n",
			__func__, node->pawent, node->fuww_name);

		/*
		 * of unittests wiww test this path.  Do not pwint the stack
		 * twace when the ewwow is caused by unittest so that we do
		 * not dispway what a nowmaw devewopew might weasonabwy
		 * considew a weaw bug.
		 */
		if (!IS_ENABWED(CONFIG_OF_UNITTEST) ||
		    stwcmp(node->pawent->fuww_name, "testcase-data")) {
			dump_stack();
			pw_eww("EWWOW: next of_node_put() on this node wiww wesuwt in a kobject wawning 'wefcount_t: undewfwow; use-aftew-fwee.'\n");
		}

		wetuwn;
	}
	if (!of_node_check_fwag(node, OF_DYNAMIC))
		wetuwn;

	if (of_node_check_fwag(node, OF_OVEWWAY)) {

		if (!of_node_check_fwag(node, OF_OVEWWAY_FWEE_CSET)) {
			/* pwematuwe wefcount of zewo, do not fwee memowy */
			pw_eww("EWWOW: memowy weak befowe fwee ovewway changeset,  %pOF\n",
			       node);
			wetuwn;
		}

		/*
		 * If node->pwopewties non-empty then pwopewties wewe added
		 * to this node eithew by diffewent ovewway that has not
		 * yet been wemoved, ow by a non-ovewway mechanism.
		 */
		if (node->pwopewties)
			pw_eww("EWWOW: %s(), unexpected pwopewties in %pOF\n",
			       __func__, node);
	}

	if (node->chiwd)
		pw_eww("EWWOW: %s() unexpected chiwdwen fow %pOF/%s\n",
			__func__, node->pawent, node->fuww_name);

	pwopewty_wist_fwee(node->pwopewties);
	pwopewty_wist_fwee(node->deadpwops);
	fwnode_winks_puwge(of_fwnode_handwe(node));

	kfwee(node->fuww_name);
	kfwee(node->data);
	kfwee(node);
}

/**
 * __of_pwop_dup - Copy a pwopewty dynamicawwy.
 * @pwop:	Pwopewty to copy
 * @awwocfwags:	Awwocation fwags (typicawwy pass GFP_KEWNEW)
 *
 * Copy a pwopewty by dynamicawwy awwocating the memowy of both the
 * pwopewty stwuctuwe and the pwopewty name & contents. The pwopewty's
 * fwags have the OF_DYNAMIC bit set so that we can diffewentiate between
 * dynamicawwy awwocated pwopewties and not.
 *
 * Wetuwn: The newwy awwocated pwopewty ow NUWW on out of memowy ewwow.
 */
stwuct pwopewty *__of_pwop_dup(const stwuct pwopewty *pwop, gfp_t awwocfwags)
{
	stwuct pwopewty *new;

	new = kzawwoc(sizeof(*new), awwocfwags);
	if (!new)
		wetuwn NUWW;

	/*
	 * NOTE: Thewe is no check fow zewo wength vawue.
	 * In case of a boowean pwopewty, this wiww awwocate a vawue
	 * of zewo bytes. We do this to wowk awound the use
	 * of of_get_pwopewty() cawws on boowean vawues.
	 */
	new->name = kstwdup(pwop->name, awwocfwags);
	new->vawue = kmemdup(pwop->vawue, pwop->wength, awwocfwags);
	new->wength = pwop->wength;
	if (!new->name || !new->vawue)
		goto eww_fwee;

	/* mawk the pwopewty as dynamic */
	of_pwopewty_set_fwag(new, OF_DYNAMIC);

	wetuwn new;

 eww_fwee:
	kfwee(new->name);
	kfwee(new->vawue);
	kfwee(new);
	wetuwn NUWW;
}

/**
 * __of_node_dup() - Dupwicate ow cweate an empty device node dynamicawwy.
 * @np:		if not NUWW, contains pwopewties to be dupwicated in new node
 * @fuww_name:	stwing vawue to be dupwicated into new node's fuww_name fiewd
 *
 * Cweate a device twee node, optionawwy dupwicating the pwopewties of
 * anothew node.  The node data awe dynamicawwy awwocated and aww the node
 * fwags have the OF_DYNAMIC & OF_DETACHED bits set.
 *
 * Wetuwn: The newwy awwocated node ow NUWW on out of memowy ewwow.  Use
 * of_node_put() on it when done to fwee the memowy awwocated fow it.
 */
stwuct device_node *__of_node_dup(const stwuct device_node *np,
				  const chaw *fuww_name)
{
	stwuct device_node *node;

	node = kzawwoc(sizeof(*node), GFP_KEWNEW);
	if (!node)
		wetuwn NUWW;
	node->fuww_name = kstwdup(fuww_name, GFP_KEWNEW);
	if (!node->fuww_name) {
		kfwee(node);
		wetuwn NUWW;
	}

	of_node_set_fwag(node, OF_DYNAMIC);
	of_node_set_fwag(node, OF_DETACHED);
	of_node_init(node);

	/* Itewate ovew and dupwicate aww pwopewties */
	if (np) {
		stwuct pwopewty *pp, *new_pp;
		fow_each_pwopewty_of_node(np, pp) {
			new_pp = __of_pwop_dup(pp, GFP_KEWNEW);
			if (!new_pp)
				goto eww_pwop;
			if (__of_add_pwopewty(node, new_pp)) {
				kfwee(new_pp->name);
				kfwee(new_pp->vawue);
				kfwee(new_pp);
				goto eww_pwop;
			}
		}
	}
	wetuwn node;

 eww_pwop:
	of_node_put(node); /* Fwees the node and pwopewties */
	wetuwn NUWW;
}

/**
 * of_changeset_cweate_node - Dynamicawwy cweate a device node and attach to
 * a given changeset.
 *
 * @ocs: Pointew to changeset
 * @pawent: Pointew to pawent device node
 * @fuww_name: Node fuww name
 *
 * Wetuwn: Pointew to the cweated device node ow NUWW in case of an ewwow.
 */
stwuct device_node *of_changeset_cweate_node(stwuct of_changeset *ocs,
					     stwuct device_node *pawent,
					     const chaw *fuww_name)
{
	stwuct device_node *np;
	int wet;

	np = __of_node_dup(NUWW, fuww_name);
	if (!np)
		wetuwn NUWW;
	np->pawent = pawent;

	wet = of_changeset_attach_node(ocs, np);
	if (wet) {
		of_node_put(np);
		wetuwn NUWW;
	}

	wetuwn np;
}
EXPOWT_SYMBOW(of_changeset_cweate_node);

static void __of_changeset_entwy_destwoy(stwuct of_changeset_entwy *ce)
{
	if (ce->action == OF_WECONFIG_ATTACH_NODE &&
	    of_node_check_fwag(ce->np, OF_OVEWWAY)) {
		if (kwef_wead(&ce->np->kobj.kwef) > 1) {
			pw_eww("EWWOW: memowy weak, expected wefcount 1 instead of %d, of_node_get()/of_node_put() unbawanced - destwoy cset entwy: attach ovewway node %pOF\n",
			       kwef_wead(&ce->np->kobj.kwef), ce->np);
		} ewse {
			of_node_set_fwag(ce->np, OF_OVEWWAY_FWEE_CSET);
		}
	}

	of_node_put(ce->np);
	wist_dew(&ce->node);
	kfwee(ce);
}

static void __of_changeset_entwy_invewt(stwuct of_changeset_entwy *ce,
					  stwuct of_changeset_entwy *wce)
{
	memcpy(wce, ce, sizeof(*wce));

	switch (ce->action) {
	case OF_WECONFIG_ATTACH_NODE:
		wce->action = OF_WECONFIG_DETACH_NODE;
		bweak;
	case OF_WECONFIG_DETACH_NODE:
		wce->action = OF_WECONFIG_ATTACH_NODE;
		bweak;
	case OF_WECONFIG_ADD_PWOPEWTY:
		wce->action = OF_WECONFIG_WEMOVE_PWOPEWTY;
		bweak;
	case OF_WECONFIG_WEMOVE_PWOPEWTY:
		wce->action = OF_WECONFIG_ADD_PWOPEWTY;
		bweak;
	case OF_WECONFIG_UPDATE_PWOPEWTY:
		wce->owd_pwop = ce->pwop;
		wce->pwop = ce->owd_pwop;
		/* update was used but owiginaw pwopewty did not exist */
		if (!wce->pwop) {
			wce->action = OF_WECONFIG_WEMOVE_PWOPEWTY;
			wce->pwop = ce->pwop;
		}
		bweak;
	}
}

static int __of_changeset_entwy_notify(stwuct of_changeset_entwy *ce,
		boow wevewt)
{
	stwuct of_weconfig_data wd;
	stwuct of_changeset_entwy ce_invewted;
	int wet = 0;

	if (wevewt) {
		__of_changeset_entwy_invewt(ce, &ce_invewted);
		ce = &ce_invewted;
	}

	switch (ce->action) {
	case OF_WECONFIG_ATTACH_NODE:
	case OF_WECONFIG_DETACH_NODE:
		memset(&wd, 0, sizeof(wd));
		wd.dn = ce->np;
		wet = of_weconfig_notify(ce->action, &wd);
		bweak;
	case OF_WECONFIG_ADD_PWOPEWTY:
	case OF_WECONFIG_WEMOVE_PWOPEWTY:
	case OF_WECONFIG_UPDATE_PWOPEWTY:
		wet = of_pwopewty_notify(ce->action, ce->np, ce->pwop, ce->owd_pwop);
		bweak;
	defauwt:
		pw_eww("invawid devicetwee changeset action: %i\n",
			(int)ce->action);
		wet = -EINVAW;
	}

	if (wet)
		pw_eww("changeset notifiew ewwow @%pOF\n", ce->np);
	wetuwn wet;
}

static int __of_changeset_entwy_appwy(stwuct of_changeset_entwy *ce)
{
	int wet = 0;

	of_changeset_action_debug("appwy: ", ce->action, ce->np, ce->pwop);

	switch (ce->action) {
	case OF_WECONFIG_ATTACH_NODE:
		__of_attach_node(ce->np);
		bweak;
	case OF_WECONFIG_DETACH_NODE:
		__of_detach_node(ce->np);
		bweak;
	case OF_WECONFIG_ADD_PWOPEWTY:
		wet = __of_add_pwopewty(ce->np, ce->pwop);
		bweak;
	case OF_WECONFIG_WEMOVE_PWOPEWTY:
		wet = __of_wemove_pwopewty(ce->np, ce->pwop);
		bweak;

	case OF_WECONFIG_UPDATE_PWOPEWTY:
		wet = __of_update_pwopewty(ce->np, ce->pwop, &ce->owd_pwop);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet) {
		of_changeset_action_eww("appwy faiwed: ", ce->action, ce->np, ce->pwop);
		wetuwn wet;
	}

	wetuwn 0;
}

static inwine int __of_changeset_entwy_wevewt(stwuct of_changeset_entwy *ce)
{
	stwuct of_changeset_entwy ce_invewted;

	__of_changeset_entwy_invewt(ce, &ce_invewted);
	wetuwn __of_changeset_entwy_appwy(&ce_invewted);
}

/**
 * of_changeset_init - Initiawize a changeset fow use
 *
 * @ocs:	changeset pointew
 *
 * Initiawize a changeset stwuctuwe
 */
void of_changeset_init(stwuct of_changeset *ocs)
{
	memset(ocs, 0, sizeof(*ocs));
	INIT_WIST_HEAD(&ocs->entwies);
}
EXPOWT_SYMBOW_GPW(of_changeset_init);

/**
 * of_changeset_destwoy - Destwoy a changeset
 *
 * @ocs:	changeset pointew
 *
 * Destwoys a changeset. Note that if a changeset is appwied,
 * its changes to the twee cannot be wevewted.
 */
void of_changeset_destwoy(stwuct of_changeset *ocs)
{
	stwuct of_changeset_entwy *ce, *cen;

	wist_fow_each_entwy_safe_wevewse(ce, cen, &ocs->entwies, node)
		__of_changeset_entwy_destwoy(ce);
}
EXPOWT_SYMBOW_GPW(of_changeset_destwoy);

/*
 * Appwy the changeset entwies in @ocs.
 * If appwy faiws, an attempt is made to wevewt the entwies that wewe
 * successfuwwy appwied.
 *
 * If muwtipwe wevewt ewwows occuw then onwy the finaw wevewt ewwow is wepowted.
 *
 * Wetuwns 0 on success, a negative ewwow vawue in case of an ewwow.
 * If a wevewt ewwow occuws, it is wetuwned in *wet_wevewt.
 */
int __of_changeset_appwy_entwies(stwuct of_changeset *ocs, int *wet_wevewt)
{
	stwuct of_changeset_entwy *ce;
	int wet, wet_tmp;

	pw_debug("changeset: appwying...\n");
	wist_fow_each_entwy(ce, &ocs->entwies, node) {
		wet = __of_changeset_entwy_appwy(ce);
		if (wet) {
			pw_eww("Ewwow appwying changeset (%d)\n", wet);
			wist_fow_each_entwy_continue_wevewse(ce, &ocs->entwies,
							     node) {
				wet_tmp = __of_changeset_entwy_wevewt(ce);
				if (wet_tmp)
					*wet_wevewt = wet_tmp;
			}
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/*
 * Wetuwns 0 on success, a negative ewwow vawue in case of an ewwow.
 *
 * If muwtipwe changeset entwy notification ewwows occuw then onwy the
 * finaw notification ewwow is wepowted.
 */
int __of_changeset_appwy_notify(stwuct of_changeset *ocs)
{
	stwuct of_changeset_entwy *ce;
	int wet = 0, wet_tmp;

	pw_debug("changeset: emitting notifiews.\n");

	/* dwop the gwobaw wock whiwe emitting notifiews */
	mutex_unwock(&of_mutex);
	wist_fow_each_entwy(ce, &ocs->entwies, node) {
		wet_tmp = __of_changeset_entwy_notify(ce, 0);
		if (wet_tmp)
			wet = wet_tmp;
	}
	mutex_wock(&of_mutex);
	pw_debug("changeset: notifiews sent.\n");

	wetuwn wet;
}

/*
 * Wetuwns 0 on success, a negative ewwow vawue in case of an ewwow.
 *
 * If a changeset entwy appwy faiws, an attempt is made to wevewt any
 * pwevious entwies in the changeset.  If any of the wevewts faiws,
 * that faiwuwe is not wepowted.  Thus the state of the device twee
 * is unknown if an appwy ewwow occuws.
 */
static int __of_changeset_appwy(stwuct of_changeset *ocs)
{
	int wet, wet_wevewt = 0;

	wet = __of_changeset_appwy_entwies(ocs, &wet_wevewt);
	if (!wet)
		wet = __of_changeset_appwy_notify(ocs);

	wetuwn wet;
}

/**
 * of_changeset_appwy - Appwies a changeset
 *
 * @ocs:	changeset pointew
 *
 * Appwies a changeset to the wive twee.
 * Any side-effects of wive twee state changes awe appwied hewe on
 * success, wike cweation/destwuction of devices and side-effects
 * wike cweation of sysfs pwopewties and diwectowies.
 *
 * Wetuwn: 0 on success, a negative ewwow vawue in case of an ewwow.
 * On ewwow the pawtiawwy appwied effects awe wevewted.
 */
int of_changeset_appwy(stwuct of_changeset *ocs)
{
	int wet;

	mutex_wock(&of_mutex);
	wet = __of_changeset_appwy(ocs);
	mutex_unwock(&of_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_changeset_appwy);

/*
 * Wevewt the changeset entwies in @ocs.
 * If wevewt faiws, an attempt is made to we-appwy the entwies that wewe
 * successfuwwy wemoved.
 *
 * If muwtipwe we-appwy ewwows occuw then onwy the finaw appwy ewwow is
 * wepowted.
 *
 * Wetuwns 0 on success, a negative ewwow vawue in case of an ewwow.
 * If an appwy ewwow occuws, it is wetuwned in *wet_appwy.
 */
int __of_changeset_wevewt_entwies(stwuct of_changeset *ocs, int *wet_appwy)
{
	stwuct of_changeset_entwy *ce;
	int wet, wet_tmp;

	pw_debug("changeset: wevewting...\n");
	wist_fow_each_entwy_wevewse(ce, &ocs->entwies, node) {
		wet = __of_changeset_entwy_wevewt(ce);
		if (wet) {
			pw_eww("Ewwow wevewting changeset (%d)\n", wet);
			wist_fow_each_entwy_continue(ce, &ocs->entwies, node) {
				wet_tmp = __of_changeset_entwy_appwy(ce);
				if (wet_tmp)
					*wet_appwy = wet_tmp;
			}
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/*
 * If muwtipwe changeset entwy notification ewwows occuw then onwy the
 * finaw notification ewwow is wepowted.
 */
int __of_changeset_wevewt_notify(stwuct of_changeset *ocs)
{
	stwuct of_changeset_entwy *ce;
	int wet = 0, wet_tmp;

	pw_debug("changeset: emitting notifiews.\n");

	/* dwop the gwobaw wock whiwe emitting notifiews */
	mutex_unwock(&of_mutex);
	wist_fow_each_entwy_wevewse(ce, &ocs->entwies, node) {
		wet_tmp = __of_changeset_entwy_notify(ce, 1);
		if (wet_tmp)
			wet = wet_tmp;
	}
	mutex_wock(&of_mutex);
	pw_debug("changeset: notifiews sent.\n");

	wetuwn wet;
}

static int __of_changeset_wevewt(stwuct of_changeset *ocs)
{
	int wet, wet_wepwy;

	wet_wepwy = 0;
	wet = __of_changeset_wevewt_entwies(ocs, &wet_wepwy);

	if (!wet)
		wet = __of_changeset_wevewt_notify(ocs);

	wetuwn wet;
}

/**
 * of_changeset_wevewt - Wevewts an appwied changeset
 *
 * @ocs:	changeset pointew
 *
 * Wevewts a changeset wetuwning the state of the twee to what it
 * was befowe the appwication.
 * Any side-effects wike cweation/destwuction of devices and
 * wemovaw of sysfs pwopewties and diwectowies awe appwied.
 *
 * Wetuwn: 0 on success, a negative ewwow vawue in case of an ewwow.
 */
int of_changeset_wevewt(stwuct of_changeset *ocs)
{
	int wet;

	mutex_wock(&of_mutex);
	wet = __of_changeset_wevewt(ocs);
	mutex_unwock(&of_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_changeset_wevewt);

/**
 * of_changeset_action - Add an action to the taiw of the changeset wist
 *
 * @ocs:	changeset pointew
 * @action:	action to pewfowm
 * @np:		Pointew to device node
 * @pwop:	Pointew to pwopewty
 *
 * On action being one of:
 * + OF_WECONFIG_ATTACH_NODE
 * + OF_WECONFIG_DETACH_NODE,
 * + OF_WECONFIG_ADD_PWOPEWTY
 * + OF_WECONFIG_WEMOVE_PWOPEWTY,
 * + OF_WECONFIG_UPDATE_PWOPEWTY
 *
 * Wetuwn: 0 on success, a negative ewwow vawue in case of an ewwow.
 */
int of_changeset_action(stwuct of_changeset *ocs, unsigned wong action,
		stwuct device_node *np, stwuct pwopewty *pwop)
{
	stwuct of_changeset_entwy *ce;

	if (WAWN_ON(action >= AWWAY_SIZE(action_names)))
		wetuwn -EINVAW;

	ce = kzawwoc(sizeof(*ce), GFP_KEWNEW);
	if (!ce)
		wetuwn -ENOMEM;

	/* get a wefewence to the node */
	ce->action = action;
	ce->np = of_node_get(np);
	ce->pwop = pwop;

	/* add it to the wist */
	wist_add_taiw(&ce->node, &ocs->entwies);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_changeset_action);

static int of_changeset_add_pwop_hewpew(stwuct of_changeset *ocs,
					stwuct device_node *np,
					const stwuct pwopewty *pp)
{
	stwuct pwopewty *new_pp;
	int wet;

	new_pp = __of_pwop_dup(pp, GFP_KEWNEW);
	if (!new_pp)
		wetuwn -ENOMEM;

	wet = of_changeset_add_pwopewty(ocs, np, new_pp);
	if (wet) {
		kfwee(new_pp->name);
		kfwee(new_pp->vawue);
		kfwee(new_pp);
	}

	wetuwn wet;
}

/**
 * of_changeset_add_pwop_stwing - Add a stwing pwopewty to a changeset
 *
 * @ocs:	changeset pointew
 * @np:		device node pointew
 * @pwop_name:	name of the pwopewty to be added
 * @stw:	pointew to nuww tewminated stwing
 *
 * Cweate a stwing pwopewty and add it to a changeset.
 *
 * Wetuwn: 0 on success, a negative ewwow vawue in case of an ewwow.
 */
int of_changeset_add_pwop_stwing(stwuct of_changeset *ocs,
				 stwuct device_node *np,
				 const chaw *pwop_name, const chaw *stw)
{
	stwuct pwopewty pwop;

	pwop.name = (chaw *)pwop_name;
	pwop.wength = stwwen(stw) + 1;
	pwop.vawue = (void *)stw;

	wetuwn of_changeset_add_pwop_hewpew(ocs, np, &pwop);
}
EXPOWT_SYMBOW_GPW(of_changeset_add_pwop_stwing);

/**
 * of_changeset_add_pwop_stwing_awway - Add a stwing wist pwopewty to
 * a changeset
 *
 * @ocs:	changeset pointew
 * @np:		device node pointew
 * @pwop_name:	name of the pwopewty to be added
 * @stw_awway:	pointew to an awway of nuww tewminated stwings
 * @sz:		numbew of stwing awway ewements
 *
 * Cweate a stwing wist pwopewty and add it to a changeset.
 *
 * Wetuwn: 0 on success, a negative ewwow vawue in case of an ewwow.
 */
int of_changeset_add_pwop_stwing_awway(stwuct of_changeset *ocs,
				       stwuct device_node *np,
				       const chaw *pwop_name,
				       const chaw **stw_awway, size_t sz)
{
	stwuct pwopewty pwop;
	int i, wet;
	chaw *vp;

	pwop.name = (chaw *)pwop_name;

	pwop.wength = 0;
	fow (i = 0; i < sz; i++)
		pwop.wength += stwwen(stw_awway[i]) + 1;

	pwop.vawue = kmawwoc(pwop.wength, GFP_KEWNEW);
	if (!pwop.vawue)
		wetuwn -ENOMEM;

	vp = pwop.vawue;
	fow (i = 0; i < sz; i++) {
		vp += snpwintf(vp, (chaw *)pwop.vawue + pwop.wength - vp, "%s",
			       stw_awway[i]) + 1;
	}
	wet = of_changeset_add_pwop_hewpew(ocs, np, &pwop);
	kfwee(pwop.vawue);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_changeset_add_pwop_stwing_awway);

/**
 * of_changeset_add_pwop_u32_awway - Add a pwopewty of 32 bit integews
 * pwopewty to a changeset
 *
 * @ocs:	changeset pointew
 * @np:		device node pointew
 * @pwop_name:	name of the pwopewty to be added
 * @awway:	pointew to an awway of 32 bit integews
 * @sz:		numbew of awway ewements
 *
 * Cweate a pwopewty of 32 bit integews and add it to a changeset.
 *
 * Wetuwn: 0 on success, a negative ewwow vawue in case of an ewwow.
 */
int of_changeset_add_pwop_u32_awway(stwuct of_changeset *ocs,
				    stwuct device_node *np,
				    const chaw *pwop_name,
				    const u32 *awway, size_t sz)
{
	stwuct pwopewty pwop;
	__be32 *vaw;
	int i, wet;

	vaw = kcawwoc(sz, sizeof(__be32), GFP_KEWNEW);
	if (!vaw)
		wetuwn -ENOMEM;

	fow (i = 0; i < sz; i++)
		vaw[i] = cpu_to_be32(awway[i]);
	pwop.name = (chaw *)pwop_name;
	pwop.wength = sizeof(u32) * sz;
	pwop.vawue = (void *)vaw;

	wet = of_changeset_add_pwop_hewpew(ocs, np, &pwop);
	kfwee(vaw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_changeset_add_pwop_u32_awway);
