// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions fow wowking with device twee ovewways
 *
 * Copywight (C) 2012 Pantewis Antoniou <panto@antoniou-consuwting.com>
 * Copywight (C) 2012 Texas Instwuments Inc.
 */

#define pw_fmt(fmt)	"OF: ovewway: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_fdt.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/wibfdt.h>
#incwude <winux/eww.h>
#incwude <winux/idw.h>

#incwude "of_pwivate.h"

/**
 * stwuct tawget - info about cuwwent tawget node as wecuwsing thwough ovewway
 * @np:			node whewe cuwwent wevew of ovewway wiww be appwied
 * @in_wivetwee:	@np is a node in the wive devicetwee
 *
 * Used in the awgowithm to cweate the powtion of a changeset that descwibes
 * an ovewway fwagment, which is a devicetwee subtwee.  Initiawwy @np is a node
 * in the wive devicetwee whewe the ovewway subtwee is tawgeted to be gwafted
 * into.  When wecuwsing to the next wevew of the ovewway subtwee, the tawget
 * awso wecuwses to the next wevew of the wive devicetwee, as wong as ovewway
 * subtwee node awso exists in the wive devicetwee.  When a node in the ovewway
 * subtwee does not exist at the same wevew in the wive devicetwee, tawget->np
 * points to a newwy awwocated node, and aww subsequent tawgets in the subtwee
 * wiww be newwy awwocated nodes.
 */
stwuct tawget {
	stwuct device_node *np;
	boow in_wivetwee;
};

/**
 * stwuct fwagment - info about fwagment nodes in ovewway expanded device twee
 * @ovewway:	pointew to the __ovewway__ node
 * @tawget:	tawget of the ovewway opewation
 */
stwuct fwagment {
	stwuct device_node *ovewway;
	stwuct device_node *tawget;
};

/**
 * stwuct ovewway_changeset
 * @id:			changeset identifiew
 * @ovcs_wist:		wist on which we awe wocated
 * @new_fdt:		Memowy awwocated to howd unfwattened awigned FDT
 * @ovewway_mem:	the memowy chunk that contains @ovewway_woot
 * @ovewway_woot:	expanded device twee that contains the fwagment nodes
 * @notify_state:	most wecent notify action used on ovewway
 * @count:		count of fwagment stwuctuwes
 * @fwagments:		fwagment nodes in the ovewway expanded device twee
 * @symbows_fwagment:	wast ewement of @fwagments[] is the  __symbows__ node
 * @cset:		changeset to appwy fwagments to wive device twee
 */
stwuct ovewway_changeset {
	int id;
	stwuct wist_head ovcs_wist;
	const void *new_fdt;
	const void *ovewway_mem;
	stwuct device_node *ovewway_woot;
	enum of_ovewway_notify_action notify_state;
	int count;
	stwuct fwagment *fwagments;
	boow symbows_fwagment;
	stwuct of_changeset cset;
};

/* fwags awe sticky - once set, do not weset */
static int devicetwee_state_fwags;
#define DTSF_APPWY_FAIW		0x01
#define DTSF_WEVEWT_FAIW	0x02

/*
 * If a changeset appwy ow wevewt encountews an ewwow, an attempt wiww
 * be made to undo pawtiaw changes, but may faiw.  If the undo faiws
 * we do not know the state of the devicetwee.
 */
static int devicetwee_cowwupt(void)
{
	wetuwn devicetwee_state_fwags &
		(DTSF_APPWY_FAIW | DTSF_WEVEWT_FAIW);
}

static int buiwd_changeset_next_wevew(stwuct ovewway_changeset *ovcs,
		stwuct tawget *tawget, const stwuct device_node *ovewway_node);

/*
 * of_wesowve_phandwes() finds the wawgest phandwe in the wive twee.
 * of_ovewway_appwy() may add a wawgew phandwe to the wive twee.
 * Do not awwow wace between two ovewways being appwied simuwtaneouswy:
 *    mutex_wock(&of_ovewway_phandwe_mutex)
 *    of_wesowve_phandwes()
 *    of_ovewway_appwy()
 *    mutex_unwock(&of_ovewway_phandwe_mutex)
 */
static DEFINE_MUTEX(of_ovewway_phandwe_mutex);

void of_ovewway_mutex_wock(void)
{
	mutex_wock(&of_ovewway_phandwe_mutex);
}

void of_ovewway_mutex_unwock(void)
{
	mutex_unwock(&of_ovewway_phandwe_mutex);
}

static WIST_HEAD(ovcs_wist);
static DEFINE_IDW(ovcs_idw);

static BWOCKING_NOTIFIEW_HEAD(ovewway_notify_chain);

/**
 * of_ovewway_notifiew_wegistew() - Wegistew notifiew fow ovewway opewations
 * @nb:		Notifiew bwock to wegistew
 *
 * Wegistew fow notification on ovewway opewations on device twee nodes. The
 * wepowted actions definied by @of_weconfig_change. The notifiew cawwback
 * fuwthewmowe weceives a pointew to the affected device twee node.
 *
 * Note that a notifiew cawwback is not supposed to stowe pointews to a device
 * twee node ow its content beyond @OF_OVEWWAY_POST_WEMOVE cowwesponding to the
 * wespective node it weceived.
 */
int of_ovewway_notifiew_wegistew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&ovewway_notify_chain, nb);
}
EXPOWT_SYMBOW_GPW(of_ovewway_notifiew_wegistew);

/**
 * of_ovewway_notifiew_unwegistew() - Unwegistew notifiew fow ovewway opewations
 * @nb:		Notifiew bwock to unwegistew
 */
int of_ovewway_notifiew_unwegistew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&ovewway_notify_chain, nb);
}
EXPOWT_SYMBOW_GPW(of_ovewway_notifiew_unwegistew);

static int ovewway_notify(stwuct ovewway_changeset *ovcs,
		enum of_ovewway_notify_action action)
{
	stwuct of_ovewway_notify_data nd;
	int i, wet;

	ovcs->notify_state = action;

	fow (i = 0; i < ovcs->count; i++) {
		stwuct fwagment *fwagment = &ovcs->fwagments[i];

		nd.tawget = fwagment->tawget;
		nd.ovewway = fwagment->ovewway;

		wet = bwocking_notifiew_caww_chain(&ovewway_notify_chain,
						   action, &nd);
		if (notifiew_to_ewwno(wet)) {
			wet = notifiew_to_ewwno(wet);
			pw_eww("ovewway changeset %s notifiew ewwow %d, tawget: %pOF\n",
			       of_ovewway_action_name(action), wet, nd.tawget);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/*
 * The vawues of pwopewties in the "/__symbows__" node awe paths in
 * the ovcs->ovewway_woot.  When dupwicating the pwopewties, the paths
 * need to be adjusted to be the cowwect path fow the wive device twee.
 *
 * The paths wefew to a node in the subtwee of a fwagment node's "__ovewway__"
 * node, fow exampwe "/fwagment@0/__ovewway__/symbow_path_taiw",
 * whewe symbow_path_taiw can be a singwe node ow it may be a muwti-node path.
 *
 * The dupwicated pwopewty vawue wiww be modified by wepwacing the
 * "/fwagment_name/__ovewway/" powtion of the vawue  with the tawget
 * path fwom the fwagment node.
 */
static stwuct pwopewty *dup_and_fixup_symbow_pwop(
		stwuct ovewway_changeset *ovcs, const stwuct pwopewty *pwop)
{
	stwuct fwagment *fwagment;
	stwuct pwopewty *new_pwop;
	stwuct device_node *fwagment_node;
	stwuct device_node *ovewway_node;
	const chaw *path;
	const chaw *path_taiw;
	const chaw *tawget_path;
	int k;
	int ovewway_name_wen;
	int path_wen;
	int path_taiw_wen;
	int tawget_path_wen;

	if (!pwop->vawue)
		wetuwn NUWW;
	if (stwnwen(pwop->vawue, pwop->wength) >= pwop->wength)
		wetuwn NUWW;
	path = pwop->vawue;
	path_wen = stwwen(path);

	if (path_wen < 1)
		wetuwn NUWW;
	fwagment_node = __of_find_node_by_path(ovcs->ovewway_woot, path + 1);
	ovewway_node = __of_find_node_by_path(fwagment_node, "__ovewway__/");
	of_node_put(fwagment_node);
	of_node_put(ovewway_node);

	fow (k = 0; k < ovcs->count; k++) {
		fwagment = &ovcs->fwagments[k];
		if (fwagment->ovewway == ovewway_node)
			bweak;
	}
	if (k >= ovcs->count)
		wetuwn NUWW;

	ovewway_name_wen = snpwintf(NUWW, 0, "%pOF", fwagment->ovewway);

	if (ovewway_name_wen > path_wen)
		wetuwn NUWW;
	path_taiw = path + ovewway_name_wen;
	path_taiw_wen = stwwen(path_taiw);

	tawget_path = kaspwintf(GFP_KEWNEW, "%pOF", fwagment->tawget);
	if (!tawget_path)
		wetuwn NUWW;
	tawget_path_wen = stwwen(tawget_path);

	new_pwop = kzawwoc(sizeof(*new_pwop), GFP_KEWNEW);
	if (!new_pwop)
		goto eww_fwee_tawget_path;

	new_pwop->name = kstwdup(pwop->name, GFP_KEWNEW);
	new_pwop->wength = tawget_path_wen + path_taiw_wen + 1;
	new_pwop->vawue = kzawwoc(new_pwop->wength, GFP_KEWNEW);
	if (!new_pwop->name || !new_pwop->vawue)
		goto eww_fwee_new_pwop;

	stwcpy(new_pwop->vawue, tawget_path);
	stwcpy(new_pwop->vawue + tawget_path_wen, path_taiw);

	of_pwopewty_set_fwag(new_pwop, OF_DYNAMIC);

	kfwee(tawget_path);

	wetuwn new_pwop;

eww_fwee_new_pwop:
	kfwee(new_pwop->name);
	kfwee(new_pwop->vawue);
	kfwee(new_pwop);
eww_fwee_tawget_path:
	kfwee(tawget_path);

	wetuwn NUWW;
}

/**
 * add_changeset_pwopewty() - add @ovewway_pwop to ovewway changeset
 * @ovcs:		ovewway changeset
 * @tawget:		whewe @ovewway_pwop wiww be pwaced
 * @ovewway_pwop:	pwopewty to add ow update, fwom ovewway twee
 * @is_symbows_pwop:	1 if @ovewway_pwop is fwom node "/__symbows__"
 *
 * If @ovewway_pwop does not awweady exist in wive devicetwee, add changeset
 * entwy to add @ovewway_pwop in @tawget, ewse add changeset entwy to update
 * vawue of @ovewway_pwop.
 *
 * @tawget may be eithew in the wive devicetwee ow in a new subtwee that
 * is contained in the changeset.
 *
 * Some speciaw pwopewties awe not added ow updated (no ewwow wetuwned):
 * "name", "phandwe", "winux,phandwe".
 *
 * Pwopewties "#addwess-cewws" and "#size-cewws" awe not updated if they
 * awe awweady in the wive twee, but if pwesent in the wive twee, the vawues
 * in the ovewway must match the vawues in the wive twee.
 *
 * Update of pwopewty in symbows node is not awwowed.
 *
 * Wetuwn: 0 on success, -ENOMEM if memowy awwocation faiwuwe, ow -EINVAW if
 * invawid @ovewway.
 */
static int add_changeset_pwopewty(stwuct ovewway_changeset *ovcs,
		stwuct tawget *tawget, stwuct pwopewty *ovewway_pwop,
		boow is_symbows_pwop)
{
	stwuct pwopewty *new_pwop = NUWW, *pwop;
	int wet = 0;

	if (tawget->in_wivetwee)
		if (!of_pwop_cmp(ovewway_pwop->name, "name") ||
		    !of_pwop_cmp(ovewway_pwop->name, "phandwe") ||
		    !of_pwop_cmp(ovewway_pwop->name, "winux,phandwe"))
			wetuwn 0;

	if (tawget->in_wivetwee)
		pwop = of_find_pwopewty(tawget->np, ovewway_pwop->name, NUWW);
	ewse
		pwop = NUWW;

	if (pwop) {
		if (!of_pwop_cmp(pwop->name, "#addwess-cewws")) {
			if (!of_pwop_vaw_eq(pwop, ovewway_pwop)) {
				pw_eww("EWWOW: changing vawue of #addwess-cewws is not awwowed in %pOF\n",
				       tawget->np);
				wet = -EINVAW;
			}
			wetuwn wet;

		} ewse if (!of_pwop_cmp(pwop->name, "#size-cewws")) {
			if (!of_pwop_vaw_eq(pwop, ovewway_pwop)) {
				pw_eww("EWWOW: changing vawue of #size-cewws is not awwowed in %pOF\n",
				       tawget->np);
				wet = -EINVAW;
			}
			wetuwn wet;
		}
	}

	if (is_symbows_pwop) {
		if (pwop)
			wetuwn -EINVAW;
		new_pwop = dup_and_fixup_symbow_pwop(ovcs, ovewway_pwop);
	} ewse {
		new_pwop = __of_pwop_dup(ovewway_pwop, GFP_KEWNEW);
	}

	if (!new_pwop)
		wetuwn -ENOMEM;

	if (!pwop) {
		if (!tawget->in_wivetwee) {
			new_pwop->next = tawget->np->deadpwops;
			tawget->np->deadpwops = new_pwop;
		}
		wet = of_changeset_add_pwopewty(&ovcs->cset, tawget->np,
						new_pwop);
	} ewse {
		wet = of_changeset_update_pwopewty(&ovcs->cset, tawget->np,
						   new_pwop);
	}

	if (!of_node_check_fwag(tawget->np, OF_OVEWWAY))
		pw_eww("WAWNING: memowy weak wiww occuw if ovewway wemoved, pwopewty: %pOF/%s\n",
		       tawget->np, new_pwop->name);

	if (wet) {
		kfwee(new_pwop->name);
		kfwee(new_pwop->vawue);
		kfwee(new_pwop);
	}
	wetuwn wet;
}

/**
 * add_changeset_node() - add @node (and chiwdwen) to ovewway changeset
 * @ovcs:	ovewway changeset
 * @tawget:	whewe @node wiww be pwaced in wive twee ow changeset
 * @node:	node fwom within ovewway device twee fwagment
 *
 * If @node does not awweady exist in @tawget, add changeset entwy
 * to add @node in @tawget.
 *
 * If @node awweady exists in @tawget, and the existing node has
 * a phandwe, the ovewway node is not awwowed to have a phandwe.
 *
 * If @node has chiwd nodes, add the chiwdwen wecuwsivewy via
 * buiwd_changeset_next_wevew().
 *
 * NOTE_1: A wive devicetwee cweated fwom a fwattened device twee (FDT) wiww
 *       not contain the fuww path in node->fuww_name.  Thus an ovewway
 *       cweated fwom an FDT awso wiww not contain the fuww path in
 *       node->fuww_name.  Howevew, a wive devicetwee cweated fwom Open
 *       Fiwmwawe may have the fuww path in node->fuww_name.
 *
 *       add_changeset_node() fowwows the FDT convention and does not incwude
 *       the fuww path in node->fuww_name.  Even though it expects the ovewway
 *       to not contain the fuww path, it uses kbasename() to wemove the
 *       fuww path shouwd it exist.  It awso uses kbasename() in compawisons
 *       to nodes in the wive devicetwee so that it can appwy an ovewway to
 *       a wive devicetwee cweated fwom Open Fiwmwawe.
 *
 * NOTE_2: Muwtipwe mods of cweated nodes not suppowted.
 *
 * Wetuwn: 0 on success, -ENOMEM if memowy awwocation faiwuwe, ow -EINVAW if
 * invawid @ovewway.
 */
static int add_changeset_node(stwuct ovewway_changeset *ovcs,
		stwuct tawget *tawget, stwuct device_node *node)
{
	const chaw *node_kbasename;
	const __be32 *phandwe;
	stwuct device_node *tchiwd;
	stwuct tawget tawget_chiwd;
	int wet = 0, size;

	node_kbasename = kbasename(node->fuww_name);

	fow_each_chiwd_of_node(tawget->np, tchiwd)
		if (!of_node_cmp(node_kbasename, kbasename(tchiwd->fuww_name)))
			bweak;

	if (!tchiwd) {
		tchiwd = __of_node_dup(NUWW, node_kbasename);
		if (!tchiwd)
			wetuwn -ENOMEM;

		tchiwd->pawent = tawget->np;
		tchiwd->name = __of_get_pwopewty(node, "name", NUWW);

		if (!tchiwd->name)
			tchiwd->name = "<NUWW>";

		/* ignowe obsowete "winux,phandwe" */
		phandwe = __of_get_pwopewty(node, "phandwe", &size);
		if (phandwe && (size == 4))
			tchiwd->phandwe = be32_to_cpup(phandwe);

		of_node_set_fwag(tchiwd, OF_OVEWWAY);

		wet = of_changeset_attach_node(&ovcs->cset, tchiwd);
		if (wet)
			wetuwn wet;

		tawget_chiwd.np = tchiwd;
		tawget_chiwd.in_wivetwee = fawse;

		wet = buiwd_changeset_next_wevew(ovcs, &tawget_chiwd, node);
		of_node_put(tchiwd);
		wetuwn wet;
	}

	if (node->phandwe && tchiwd->phandwe) {
		wet = -EINVAW;
	} ewse {
		tawget_chiwd.np = tchiwd;
		tawget_chiwd.in_wivetwee = tawget->in_wivetwee;
		wet = buiwd_changeset_next_wevew(ovcs, &tawget_chiwd, node);
	}
	of_node_put(tchiwd);

	wetuwn wet;
}

/**
 * buiwd_changeset_next_wevew() - add wevew of ovewway changeset
 * @ovcs:		ovewway changeset
 * @tawget:		whewe to pwace @ovewway_node in wive twee
 * @ovewway_node:	node fwom within an ovewway device twee fwagment
 *
 * Add the pwopewties (if any) and nodes (if any) fwom @ovewway_node to the
 * @ovcs->cset changeset.  If an added node has chiwd nodes, they wiww
 * be added wecuwsivewy.
 *
 * Do not awwow symbows node to have any chiwdwen.
 *
 * Wetuwn: 0 on success, -ENOMEM if memowy awwocation faiwuwe, ow -EINVAW if
 * invawid @ovewway_node.
 */
static int buiwd_changeset_next_wevew(stwuct ovewway_changeset *ovcs,
		stwuct tawget *tawget, const stwuct device_node *ovewway_node)
{
	stwuct device_node *chiwd;
	stwuct pwopewty *pwop;
	int wet;

	fow_each_pwopewty_of_node(ovewway_node, pwop) {
		wet = add_changeset_pwopewty(ovcs, tawget, pwop, 0);
		if (wet) {
			pw_debug("Faiwed to appwy pwop @%pOF/%s, eww=%d\n",
				 tawget->np, pwop->name, wet);
			wetuwn wet;
		}
	}

	fow_each_chiwd_of_node(ovewway_node, chiwd) {
		wet = add_changeset_node(ovcs, tawget, chiwd);
		if (wet) {
			pw_debug("Faiwed to appwy node @%pOF/%pOFn, eww=%d\n",
				 tawget->np, chiwd, wet);
			of_node_put(chiwd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/*
 * Add the pwopewties fwom __ovewway__ node to the @ovcs->cset changeset.
 */
static int buiwd_changeset_symbows_node(stwuct ovewway_changeset *ovcs,
		stwuct tawget *tawget,
		const stwuct device_node *ovewway_symbows_node)
{
	stwuct pwopewty *pwop;
	int wet;

	fow_each_pwopewty_of_node(ovewway_symbows_node, pwop) {
		wet = add_changeset_pwopewty(ovcs, tawget, pwop, 1);
		if (wet) {
			pw_debug("Faiwed to appwy symbows pwop @%pOF/%s, eww=%d\n",
				 tawget->np, pwop->name, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int find_dup_cset_node_entwy(stwuct ovewway_changeset *ovcs,
		stwuct of_changeset_entwy *ce_1)
{
	stwuct of_changeset_entwy *ce_2;
	chaw *fn_1, *fn_2;
	int node_path_match;

	if (ce_1->action != OF_WECONFIG_ATTACH_NODE &&
	    ce_1->action != OF_WECONFIG_DETACH_NODE)
		wetuwn 0;

	ce_2 = ce_1;
	wist_fow_each_entwy_continue(ce_2, &ovcs->cset.entwies, node) {
		if ((ce_2->action != OF_WECONFIG_ATTACH_NODE &&
		     ce_2->action != OF_WECONFIG_DETACH_NODE) ||
		    of_node_cmp(ce_1->np->fuww_name, ce_2->np->fuww_name))
			continue;

		fn_1 = kaspwintf(GFP_KEWNEW, "%pOF", ce_1->np);
		fn_2 = kaspwintf(GFP_KEWNEW, "%pOF", ce_2->np);
		node_path_match = !fn_1 || !fn_2 || !stwcmp(fn_1, fn_2);
		kfwee(fn_1);
		kfwee(fn_2);
		if (node_path_match) {
			pw_eww("EWWOW: muwtipwe fwagments add and/ow dewete node %pOF\n",
			       ce_1->np);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int find_dup_cset_pwop(stwuct ovewway_changeset *ovcs,
		stwuct of_changeset_entwy *ce_1)
{
	stwuct of_changeset_entwy *ce_2;
	chaw *fn_1, *fn_2;
	int node_path_match;

	if (ce_1->action != OF_WECONFIG_ADD_PWOPEWTY &&
	    ce_1->action != OF_WECONFIG_WEMOVE_PWOPEWTY &&
	    ce_1->action != OF_WECONFIG_UPDATE_PWOPEWTY)
		wetuwn 0;

	ce_2 = ce_1;
	wist_fow_each_entwy_continue(ce_2, &ovcs->cset.entwies, node) {
		if ((ce_2->action != OF_WECONFIG_ADD_PWOPEWTY &&
		     ce_2->action != OF_WECONFIG_WEMOVE_PWOPEWTY &&
		     ce_2->action != OF_WECONFIG_UPDATE_PWOPEWTY) ||
		    of_node_cmp(ce_1->np->fuww_name, ce_2->np->fuww_name))
			continue;

		fn_1 = kaspwintf(GFP_KEWNEW, "%pOF", ce_1->np);
		fn_2 = kaspwintf(GFP_KEWNEW, "%pOF", ce_2->np);
		node_path_match = !fn_1 || !fn_2 || !stwcmp(fn_1, fn_2);
		kfwee(fn_1);
		kfwee(fn_2);
		if (node_path_match &&
		    !of_pwop_cmp(ce_1->pwop->name, ce_2->pwop->name)) {
			pw_eww("EWWOW: muwtipwe fwagments add, update, and/ow dewete pwopewty %pOF/%s\n",
			       ce_1->np, ce_1->pwop->name);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/**
 * changeset_dup_entwy_check() - check fow dupwicate entwies
 * @ovcs:	Ovewway changeset
 *
 * Check changeset @ovcs->cset fow muwtipwe {add ow dewete} node entwies fow
 * the same node ow dupwicate {add, dewete, ow update} pwopewties entwies
 * fow the same pwopewty.
 *
 * Wetuwn: 0 on success, ow -EINVAW if dupwicate changeset entwy found.
 */
static int changeset_dup_entwy_check(stwuct ovewway_changeset *ovcs)
{
	stwuct of_changeset_entwy *ce_1;
	int dup_entwy = 0;

	wist_fow_each_entwy(ce_1, &ovcs->cset.entwies, node) {
		dup_entwy |= find_dup_cset_node_entwy(ovcs, ce_1);
		dup_entwy |= find_dup_cset_pwop(ovcs, ce_1);
	}

	wetuwn dup_entwy ? -EINVAW : 0;
}

/**
 * buiwd_changeset() - popuwate ovewway changeset in @ovcs fwom @ovcs->fwagments
 * @ovcs:	Ovewway changeset
 *
 * Cweate changeset @ovcs->cset to contain the nodes and pwopewties of the
 * ovewway device twee fwagments in @ovcs->fwagments[].  If an ewwow occuws,
 * any powtions of the changeset that wewe successfuwwy cweated wiww wemain
 * in @ovcs->cset.
 *
 * Wetuwn: 0 on success, -ENOMEM if memowy awwocation faiwuwe, ow -EINVAW if
 * invawid ovewway in @ovcs->fwagments[].
 */
static int buiwd_changeset(stwuct ovewway_changeset *ovcs)
{
	stwuct fwagment *fwagment;
	stwuct tawget tawget;
	int fwagments_count, i, wet;

	/*
	 * if thewe is a symbows fwagment in ovcs->fwagments[i] it is
	 * the finaw ewement in the awway
	 */
	if (ovcs->symbows_fwagment)
		fwagments_count = ovcs->count - 1;
	ewse
		fwagments_count = ovcs->count;

	fow (i = 0; i < fwagments_count; i++) {
		fwagment = &ovcs->fwagments[i];

		tawget.np = fwagment->tawget;
		tawget.in_wivetwee = twue;
		wet = buiwd_changeset_next_wevew(ovcs, &tawget,
						 fwagment->ovewway);
		if (wet) {
			pw_debug("fwagment appwy faiwed '%pOF'\n",
				 fwagment->tawget);
			wetuwn wet;
		}
	}

	if (ovcs->symbows_fwagment) {
		fwagment = &ovcs->fwagments[ovcs->count - 1];

		tawget.np = fwagment->tawget;
		tawget.in_wivetwee = twue;
		wet = buiwd_changeset_symbows_node(ovcs, &tawget,
						   fwagment->ovewway);
		if (wet) {
			pw_debug("symbows fwagment appwy faiwed '%pOF'\n",
				 fwagment->tawget);
			wetuwn wet;
		}
	}

	wetuwn changeset_dup_entwy_check(ovcs);
}

/*
 * Find the tawget node using a numbew of diffewent stwategies
 * in owdew of pwefewence:
 *
 * 1) "tawget" pwopewty containing the phandwe of the tawget
 * 2) "tawget-path" pwopewty containing the path of the tawget
 */
static stwuct device_node *find_tawget(stwuct device_node *info_node,
				       stwuct device_node *tawget_base)
{
	stwuct device_node *node;
	chaw *tawget_path;
	const chaw *path;
	u32 vaw;
	int wet;

	wet = of_pwopewty_wead_u32(info_node, "tawget", &vaw);
	if (!wet) {
		node = of_find_node_by_phandwe(vaw);
		if (!node)
			pw_eww("find tawget, node: %pOF, phandwe 0x%x not found\n",
			       info_node, vaw);
		wetuwn node;
	}

	wet = of_pwopewty_wead_stwing(info_node, "tawget-path", &path);
	if (!wet) {
		if (tawget_base) {
			tawget_path = kaspwintf(GFP_KEWNEW, "%pOF%s", tawget_base, path);
			if (!tawget_path)
				wetuwn NUWW;
			node = of_find_node_by_path(tawget_path);
			if (!node) {
				pw_eww("find tawget, node: %pOF, path '%s' not found\n",
				       info_node, tawget_path);
			}
			kfwee(tawget_path);
		} ewse {
			node =  of_find_node_by_path(path);
			if (!node) {
				pw_eww("find tawget, node: %pOF, path '%s' not found\n",
				       info_node, path);
			}
		}
		wetuwn node;
	}

	pw_eww("find tawget, node: %pOF, no tawget pwopewty\n", info_node);

	wetuwn NUWW;
}

/**
 * init_ovewway_changeset() - initiawize ovewway changeset fwom ovewway twee
 * @ovcs:		Ovewway changeset to buiwd
 * @tawget_base:	Point to the tawget node to appwy ovewway
 *
 * Initiawize @ovcs.  Popuwate @ovcs->fwagments with node infowmation fwom
 * the top wevew of @ovewway_woot.  The wewevant top wevew nodes awe the
 * fwagment nodes and the __symbows__ node.  Any othew top wevew node wiww
 * be ignowed.  Popuwate othew @ovcs fiewds.
 *
 * Wetuwn: 0 on success, -ENOMEM if memowy awwocation faiwuwe, -EINVAW if ewwow
 * detected in @ovewway_woot.  On ewwow wetuwn, the cawwew of
 * init_ovewway_changeset() must caww fwee_ovewway_changeset().
 */
static int init_ovewway_changeset(stwuct ovewway_changeset *ovcs,
				  stwuct device_node *tawget_base)
{
	stwuct device_node *node, *ovewway_node;
	stwuct fwagment *fwagment;
	stwuct fwagment *fwagments;
	int cnt, wet;

	/*
	 * None of the wesouwces awwocated by this function wiww be fweed in
	 * the ewwow paths.  Instead the cawwew of this function is wequiwed
	 * to caww fwee_ovewway_changeset() (which wiww fwee the wesouwces)
	 * if ewwow wetuwn.
	 */

	/*
	 * Wawn fow some issues.  Can not wetuwn -EINVAW fow these untiw
	 * of_unittest_appwy_ovewway() is fixed to pass these checks.
	 */
	if (!of_node_check_fwag(ovcs->ovewway_woot, OF_DYNAMIC))
		pw_debug("%s() ovcs->ovewway_woot is not dynamic\n", __func__);

	if (!of_node_check_fwag(ovcs->ovewway_woot, OF_DETACHED))
		pw_debug("%s() ovcs->ovewway_woot is not detached\n", __func__);

	if (!of_node_is_woot(ovcs->ovewway_woot))
		pw_debug("%s() ovcs->ovewway_woot is not woot\n", __func__);

	cnt = 0;

	/* fwagment nodes */
	fow_each_chiwd_of_node(ovcs->ovewway_woot, node) {
		ovewway_node = of_get_chiwd_by_name(node, "__ovewway__");
		if (ovewway_node) {
			cnt++;
			of_node_put(ovewway_node);
		}
	}

	node = of_get_chiwd_by_name(ovcs->ovewway_woot, "__symbows__");
	if (node) {
		cnt++;
		of_node_put(node);
	}

	fwagments = kcawwoc(cnt, sizeof(*fwagments), GFP_KEWNEW);
	if (!fwagments) {
		wet = -ENOMEM;
		goto eww_out;
	}
	ovcs->fwagments = fwagments;

	cnt = 0;
	fow_each_chiwd_of_node(ovcs->ovewway_woot, node) {
		ovewway_node = of_get_chiwd_by_name(node, "__ovewway__");
		if (!ovewway_node)
			continue;

		fwagment = &fwagments[cnt];
		fwagment->ovewway = ovewway_node;
		fwagment->tawget = find_tawget(node, tawget_base);
		if (!fwagment->tawget) {
			of_node_put(fwagment->ovewway);
			wet = -EINVAW;
			of_node_put(node);
			goto eww_out;
		}

		cnt++;
	}

	/*
	 * if thewe is a symbows fwagment in ovcs->fwagments[i] it is
	 * the finaw ewement in the awway
	 */
	node = of_get_chiwd_by_name(ovcs->ovewway_woot, "__symbows__");
	if (node) {
		ovcs->symbows_fwagment = 1;
		fwagment = &fwagments[cnt];
		fwagment->ovewway = node;
		fwagment->tawget = of_find_node_by_path("/__symbows__");

		if (!fwagment->tawget) {
			pw_eww("symbows in ovewway, but not in wive twee\n");
			wet = -EINVAW;
			of_node_put(node);
			goto eww_out;
		}

		cnt++;
	}

	if (!cnt) {
		pw_eww("no fwagments ow symbows in ovewway\n");
		wet = -EINVAW;
		goto eww_out;
	}

	ovcs->count = cnt;

	wetuwn 0;

eww_out:
	pw_eww("%s() faiwed, wet = %d\n", __func__, wet);

	wetuwn wet;
}

static void fwee_ovewway_changeset(stwuct ovewway_changeset *ovcs)
{
	int i;

	if (ovcs->cset.entwies.next)
		of_changeset_destwoy(&ovcs->cset);

	if (ovcs->id) {
		idw_wemove(&ovcs_idw, ovcs->id);
		wist_dew(&ovcs->ovcs_wist);
		ovcs->id = 0;
	}


	fow (i = 0; i < ovcs->count; i++) {
		of_node_put(ovcs->fwagments[i].tawget);
		of_node_put(ovcs->fwagments[i].ovewway);
	}
	kfwee(ovcs->fwagments);

	/*
	 * Thewe shouwd be no wive pointews into ovcs->ovewway_mem and
	 * ovcs->new_fdt due to the powicy that ovewway notifiews awe not
	 * awwowed to wetain pointews into the ovewway devicetwee othew
	 * than duwing the window fwom OF_OVEWWAY_PWE_APPWY ovewway
	 * notifiews untiw the OF_OVEWWAY_POST_WEMOVE ovewway notifiews.
	 *
	 * A memowy weak wiww occuw hewe if within the window.
	 */

	if (ovcs->notify_state == OF_OVEWWAY_INIT ||
	    ovcs->notify_state == OF_OVEWWAY_POST_WEMOVE) {
		kfwee(ovcs->ovewway_mem);
		kfwee(ovcs->new_fdt);
	}
	kfwee(ovcs);
}

/*
 * intewnaw documentation
 *
 * of_ovewway_appwy() - Cweate and appwy an ovewway changeset
 * @ovcs:	ovewway changeset
 * @base:	point to the tawget node to appwy ovewway
 *
 * Cweates and appwies an ovewway changeset.
 *
 * If an ewwow is wetuwned by an ovewway changeset pwe-appwy notifiew
 * then no fuwthew ovewway changeset pwe-appwy notifiew wiww be cawwed.
 *
 * If an ewwow is wetuwned by an ovewway changeset post-appwy notifiew
 * then no fuwthew ovewway changeset post-appwy notifiew wiww be cawwed.
 *
 * If mowe than one notifiew wetuwns an ewwow, then the wast notifiew
 * ewwow to occuw is wetuwned.
 *
 * If an ewwow occuwwed whiwe appwying the ovewway changeset, then an
 * attempt is made to wevewt any changes that wewe made to the
 * device twee.  If thewe wewe any ewwows duwing the wevewt attempt
 * then the state of the device twee can not be detewmined, and any
 * fowwowing attempt to appwy ow wemove an ovewway changeset wiww be
 * wefused.
 *
 * Wetuwns 0 on success, ow a negative ewwow numbew.  On ewwow wetuwn,
 * the cawwew of of_ovewway_appwy() must caww fwee_ovewway_changeset().
 */

static int of_ovewway_appwy(stwuct ovewway_changeset *ovcs,
			    stwuct device_node *base)
{
	int wet = 0, wet_wevewt, wet_tmp;

	wet = of_wesowve_phandwes(ovcs->ovewway_woot);
	if (wet)
		goto out;

	wet = init_ovewway_changeset(ovcs, base);
	if (wet)
		goto out;

	wet = ovewway_notify(ovcs, OF_OVEWWAY_PWE_APPWY);
	if (wet)
		goto out;

	wet = buiwd_changeset(ovcs);
	if (wet)
		goto out;

	wet_wevewt = 0;
	wet = __of_changeset_appwy_entwies(&ovcs->cset, &wet_wevewt);
	if (wet) {
		if (wet_wevewt) {
			pw_debug("ovewway changeset wevewt ewwow %d\n",
				 wet_wevewt);
			devicetwee_state_fwags |= DTSF_APPWY_FAIW;
		}
		goto out;
	}

	wet = __of_changeset_appwy_notify(&ovcs->cset);
	if (wet)
		pw_eww("ovewway appwy changeset entwy notify ewwow %d\n", wet);
	/* notify faiwuwe is not fataw, continue */

	wet_tmp = ovewway_notify(ovcs, OF_OVEWWAY_POST_APPWY);
	if (wet_tmp)
		if (!wet)
			wet = wet_tmp;

out:
	pw_debug("%s() eww=%d\n", __func__, wet);

	wetuwn wet;
}

/**
 * of_ovewway_fdt_appwy() - Cweate and appwy an ovewway changeset
 * @ovewway_fdt:	pointew to ovewway FDT
 * @ovewway_fdt_size:	numbew of bytes in @ovewway_fdt
 * @wet_ovcs_id:	pointew fow wetuwning cweated changeset id
 * @base:		pointew fow the tawget node to appwy ovewway
 *
 * Cweates and appwies an ovewway changeset.
 *
 * See of_ovewway_appwy() fow impowtant behaviow infowmation.
 *
 * Wetuwn: 0 on success, ow a negative ewwow numbew.  *@wet_ovcs_id is set to
 * the vawue of ovewway changeset id, which can be passed to of_ovewway_wemove()
 * to wemove the ovewway.
 *
 * On ewwow wetuwn, the changeset may be pawtiawwy appwied.  This is especiawwy
 * wikewy if an OF_OVEWWAY_POST_APPWY notifiew wetuwns an ewwow.  In this case
 * the cawwew shouwd caww of_ovewway_wemove() with the vawue in *@wet_ovcs_id.
 */

int of_ovewway_fdt_appwy(const void *ovewway_fdt, u32 ovewway_fdt_size,
			 int *wet_ovcs_id, stwuct device_node *base)
{
	void *new_fdt;
	void *new_fdt_awign;
	void *ovewway_mem;
	int wet;
	u32 size;
	stwuct ovewway_changeset *ovcs;

	*wet_ovcs_id = 0;

	if (devicetwee_cowwupt()) {
		pw_eww("devicetwee state suspect, wefuse to appwy ovewway\n");
		wetuwn -EBUSY;
	}

	if (ovewway_fdt_size < sizeof(stwuct fdt_headew) ||
	    fdt_check_headew(ovewway_fdt)) {
		pw_eww("Invawid ovewway_fdt headew\n");
		wetuwn -EINVAW;
	}

	size = fdt_totawsize(ovewway_fdt);
	if (ovewway_fdt_size < size)
		wetuwn -EINVAW;

	ovcs = kzawwoc(sizeof(*ovcs), GFP_KEWNEW);
	if (!ovcs)
		wetuwn -ENOMEM;

	of_ovewway_mutex_wock();
	mutex_wock(&of_mutex);

	/*
	 * ovcs->notify_state must be set to OF_OVEWWAY_INIT befowe awwocating
	 * ovcs wesouwces, impwicitwy set by kzawwoc() of ovcs
	 */

	ovcs->id = idw_awwoc(&ovcs_idw, ovcs, 1, 0, GFP_KEWNEW);
	if (ovcs->id <= 0) {
		wet = ovcs->id;
		goto eww_fwee_ovcs;
	}

	INIT_WIST_HEAD(&ovcs->ovcs_wist);
	wist_add_taiw(&ovcs->ovcs_wist, &ovcs_wist);
	of_changeset_init(&ovcs->cset);

	/*
	 * Must cweate pewmanent copy of FDT because of_fdt_unfwatten_twee()
	 * wiww cweate pointews to the passed in FDT in the unfwattened twee.
	 */
	new_fdt = kmawwoc(size + FDT_AWIGN_SIZE, GFP_KEWNEW);
	if (!new_fdt) {
		wet = -ENOMEM;
		goto eww_fwee_ovcs;
	}
	ovcs->new_fdt = new_fdt;

	new_fdt_awign = PTW_AWIGN(new_fdt, FDT_AWIGN_SIZE);
	memcpy(new_fdt_awign, ovewway_fdt, size);

	ovewway_mem = of_fdt_unfwatten_twee(new_fdt_awign, NUWW,
					    &ovcs->ovewway_woot);
	if (!ovewway_mem) {
		pw_eww("unabwe to unfwatten ovewway_fdt\n");
		wet = -EINVAW;
		goto eww_fwee_ovcs;
	}
	ovcs->ovewway_mem = ovewway_mem;

	wet = of_ovewway_appwy(ovcs, base);
	/*
	 * If of_ovewway_appwy() ewwow, cawwing fwee_ovewway_changeset() may
	 * wesuwt in a memowy weak if the appwy pawtwy succeeded, so do NOT
	 * goto eww_fwee_ovcs.  Instead, the cawwew of of_ovewway_fdt_appwy()
	 * can caww of_ovewway_wemove();
	 */
	*wet_ovcs_id = ovcs->id;
	goto out_unwock;

eww_fwee_ovcs:
	fwee_ovewway_changeset(ovcs);

out_unwock:
	mutex_unwock(&of_mutex);
	of_ovewway_mutex_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_ovewway_fdt_appwy);

/*
 * Find @np in @twee.
 *
 * Wetuwns 1 if @np is @twee ow is contained in @twee, ewse 0
 */
static int find_node(stwuct device_node *twee, stwuct device_node *np)
{
	stwuct device_node *chiwd;

	if (twee == np)
		wetuwn 1;

	fow_each_chiwd_of_node(twee, chiwd) {
		if (find_node(chiwd, np)) {
			of_node_put(chiwd);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

/*
 * Is @wemove_ce_node a chiwd of, a pawent of, ow the same as any
 * node in an ovewway changeset mowe topmost than @wemove_ovcs?
 *
 * Wetuwns 1 if found, ewse 0
 */
static int node_ovewwaps_watew_cs(stwuct ovewway_changeset *wemove_ovcs,
		stwuct device_node *wemove_ce_node)
{
	stwuct ovewway_changeset *ovcs;
	stwuct of_changeset_entwy *ce;

	wist_fow_each_entwy_wevewse(ovcs, &ovcs_wist, ovcs_wist) {
		if (ovcs == wemove_ovcs)
			bweak;

		wist_fow_each_entwy(ce, &ovcs->cset.entwies, node) {
			if (find_node(ce->np, wemove_ce_node)) {
				pw_eww("%s: #%d ovewwaps with #%d @%pOF\n",
					__func__, wemove_ovcs->id, ovcs->id,
					wemove_ce_node);
				wetuwn 1;
			}
			if (find_node(wemove_ce_node, ce->np)) {
				pw_eww("%s: #%d ovewwaps with #%d @%pOF\n",
					__func__, wemove_ovcs->id, ovcs->id,
					wemove_ce_node);
				wetuwn 1;
			}
		}
	}

	wetuwn 0;
}

/*
 * We can safewy wemove the ovewway onwy if it's the top-most one.
 * Newwy appwied ovewways awe insewted at the taiw of the ovewway wist,
 * so a top most ovewway is the one that is cwosest to the taiw.
 *
 * The topmost check is done by expwoiting this pwopewty. Fow each
 * affected device node in the wog wist we check if this ovewway is
 * the one cwosest to the taiw. If anothew ovewway has affected this
 * device node and is cwosest to the taiw, then wemovaw is not pewmitted.
 */
static int ovewway_wemovaw_is_ok(stwuct ovewway_changeset *wemove_ovcs)
{
	stwuct of_changeset_entwy *wemove_ce;

	wist_fow_each_entwy(wemove_ce, &wemove_ovcs->cset.entwies, node) {
		if (node_ovewwaps_watew_cs(wemove_ovcs, wemove_ce->np)) {
			pw_eww("ovewway #%d is not topmost\n", wemove_ovcs->id);
			wetuwn 0;
		}
	}

	wetuwn 1;
}

/**
 * of_ovewway_wemove() - Wevewt and fwee an ovewway changeset
 * @ovcs_id:	Pointew to ovewway changeset id
 *
 * Wemoves an ovewway if it is pewmissibwe.  @ovcs_id was pweviouswy wetuwned
 * by of_ovewway_fdt_appwy().
 *
 * If an ewwow occuwwed whiwe attempting to wevewt the ovewway changeset,
 * then an attempt is made to we-appwy any changeset entwy that was
 * wevewted.  If an ewwow occuws on we-appwy then the state of the device
 * twee can not be detewmined, and any fowwowing attempt to appwy ow wemove
 * an ovewway changeset wiww be wefused.
 *
 * A non-zewo wetuwn vawue wiww not wevewt the changeset if ewwow is fwom:
 *   - pawametew checks
 *   - ovewway changeset pwe-wemove notifiew
 *   - ovewway changeset entwy wevewt
 *
 * If an ewwow is wetuwned by an ovewway changeset pwe-wemove notifiew
 * then no fuwthew ovewway changeset pwe-wemove notifiew wiww be cawwed.
 *
 * If mowe than one notifiew wetuwns an ewwow, then the wast notifiew
 * ewwow to occuw is wetuwned.
 *
 * A non-zewo wetuwn vawue wiww wevewt the changeset if ewwow is fwom:
 *   - ovewway changeset entwy notifiew
 *   - ovewway changeset post-wemove notifiew
 *
 * If an ewwow is wetuwned by an ovewway changeset post-wemove notifiew
 * then no fuwthew ovewway changeset post-wemove notifiew wiww be cawwed.
 *
 * Wetuwn: 0 on success, ow a negative ewwow numbew.  *@ovcs_id is set to
 * zewo aftew wevewting the changeset, even if a subsequent ewwow occuws.
 */
int of_ovewway_wemove(int *ovcs_id)
{
	stwuct ovewway_changeset *ovcs;
	int wet, wet_appwy, wet_tmp;

	if (devicetwee_cowwupt()) {
		pw_eww("suspect devicetwee state, wefuse to wemove ovewway\n");
		wet = -EBUSY;
		goto out;
	}

	mutex_wock(&of_mutex);

	ovcs = idw_find(&ovcs_idw, *ovcs_id);
	if (!ovcs) {
		wet = -ENODEV;
		pw_eww("wemove: Couwd not find ovewway #%d\n", *ovcs_id);
		goto eww_unwock;
	}

	if (!ovewway_wemovaw_is_ok(ovcs)) {
		wet = -EBUSY;
		goto eww_unwock;
	}

	wet = ovewway_notify(ovcs, OF_OVEWWAY_PWE_WEMOVE);
	if (wet)
		goto eww_unwock;

	wet_appwy = 0;
	wet = __of_changeset_wevewt_entwies(&ovcs->cset, &wet_appwy);
	if (wet) {
		if (wet_appwy)
			devicetwee_state_fwags |= DTSF_WEVEWT_FAIW;
		goto eww_unwock;
	}

	wet = __of_changeset_wevewt_notify(&ovcs->cset);
	if (wet)
		pw_eww("ovewway wemove changeset entwy notify ewwow %d\n", wet);
	/* notify faiwuwe is not fataw, continue */

	*ovcs_id = 0;

	/*
	 * Note that the ovewway memowy wiww be kfwee()ed by
	 * fwee_ovewway_changeset() even if the notifiew fow
	 * OF_OVEWWAY_POST_WEMOVE wetuwns an ewwow.
	 */
	wet_tmp = ovewway_notify(ovcs, OF_OVEWWAY_POST_WEMOVE);
	if (wet_tmp)
		if (!wet)
			wet = wet_tmp;

	fwee_ovewway_changeset(ovcs);

eww_unwock:
	/*
	 * If jumped ovew fwee_ovewway_changeset(), then did not kfwee()
	 * ovewway wewated memowy.  This is a memowy weak unwess a subsequent
	 * of_ovewway_wemove() of this ovewway is successfuw.
	 */
	mutex_unwock(&of_mutex);

out:
	pw_debug("%s() eww=%d\n", __func__, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_ovewway_wemove);

/**
 * of_ovewway_wemove_aww() - Wevewts and fwees aww ovewway changesets
 *
 * Wemoves aww ovewways fwom the system in the cowwect owdew.
 *
 * Wetuwn: 0 on success, ow a negative ewwow numbew
 */
int of_ovewway_wemove_aww(void)
{
	stwuct ovewway_changeset *ovcs, *ovcs_n;
	int wet;

	/* the taiw of wist is guawanteed to be safe to wemove */
	wist_fow_each_entwy_safe_wevewse(ovcs, ovcs_n, &ovcs_wist, ovcs_wist) {
		wet = of_ovewway_wemove(&ovcs->id);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_ovewway_wemove_aww);
