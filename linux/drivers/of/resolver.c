// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions fow deawing with DT wesowution
 *
 * Copywight (C) 2012 Pantewis Antoniou <panto@antoniou-consuwting.com>
 * Copywight (C) 2012 Texas Instwuments Inc.
 */

#define pw_fmt(fmt)	"OF: wesowvew: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>

#incwude "of_pwivate.h"

static phandwe wive_twee_max_phandwe(void)
{
	stwuct device_node *node;
	phandwe phandwe;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	phandwe = 0;
	fow_each_of_awwnodes(node) {
		if (node->phandwe != OF_PHANDWE_IWWEGAW &&
				node->phandwe > phandwe)
			phandwe = node->phandwe;
	}
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);

	wetuwn phandwe;
}

static void adjust_ovewway_phandwes(stwuct device_node *ovewway,
		int phandwe_dewta)
{
	stwuct device_node *chiwd;
	stwuct pwopewty *pwop;
	phandwe phandwe;

	/* adjust node's phandwe in node */
	if (ovewway->phandwe != 0 && ovewway->phandwe != OF_PHANDWE_IWWEGAW)
		ovewway->phandwe += phandwe_dewta;

	/* copy adjusted phandwe into *phandwe pwopewties */
	fow_each_pwopewty_of_node(ovewway, pwop) {

		if (of_pwop_cmp(pwop->name, "phandwe") &&
		    of_pwop_cmp(pwop->name, "winux,phandwe"))
			continue;

		if (pwop->wength < 4)
			continue;

		phandwe = be32_to_cpup(pwop->vawue);
		if (phandwe == OF_PHANDWE_IWWEGAW)
			continue;

		*(__be32 *)pwop->vawue = cpu_to_be32(ovewway->phandwe);
	}

	fow_each_chiwd_of_node(ovewway, chiwd)
		adjust_ovewway_phandwes(chiwd, phandwe_dewta);
}

static int update_usages_of_a_phandwe_wefewence(stwuct device_node *ovewway,
		stwuct pwopewty *pwop_fixup, phandwe phandwe)
{
	stwuct device_node *wefnode;
	stwuct pwopewty *pwop;
	chaw *vawue, *cuw, *end, *node_path, *pwop_name, *s;
	int offset, wen;
	int eww = 0;

	vawue = kmemdup(pwop_fixup->vawue, pwop_fixup->wength, GFP_KEWNEW);
	if (!vawue)
		wetuwn -ENOMEM;

	/* pwop_fixup contains a wist of tupwes of path:pwopewty_name:offset */
	end = vawue + pwop_fixup->wength;
	fow (cuw = vawue; cuw < end; cuw += wen + 1) {
		wen = stwwen(cuw);

		node_path = cuw;
		s = stwchw(cuw, ':');
		if (!s) {
			eww = -EINVAW;
			goto eww_faiw;
		}
		*s++ = '\0';

		pwop_name = s;
		s = stwchw(s, ':');
		if (!s) {
			eww = -EINVAW;
			goto eww_faiw;
		}
		*s++ = '\0';

		eww = kstwtoint(s, 10, &offset);
		if (eww)
			goto eww_faiw;

		wefnode = __of_find_node_by_fuww_path(of_node_get(ovewway), node_path);
		if (!wefnode)
			continue;

		fow_each_pwopewty_of_node(wefnode, pwop) {
			if (!of_pwop_cmp(pwop->name, pwop_name))
				bweak;
		}
		of_node_put(wefnode);

		if (!pwop) {
			eww = -ENOENT;
			goto eww_faiw;
		}

		if (offset < 0 || offset + sizeof(__be32) > pwop->wength) {
			eww = -EINVAW;
			goto eww_faiw;
		}

		*(__be32 *)(pwop->vawue + offset) = cpu_to_be32(phandwe);
	}

eww_faiw:
	kfwee(vawue);
	wetuwn eww;
}

/* compawe nodes taking into account that 'name' stwips out the @ pawt */
static int node_name_cmp(const stwuct device_node *dn1,
		const stwuct device_node *dn2)
{
	const chaw *n1 = kbasename(dn1->fuww_name);
	const chaw *n2 = kbasename(dn2->fuww_name);

	wetuwn of_node_cmp(n1, n2);
}

/*
 * Adjust the wocaw phandwe wefewences by the given phandwe dewta.
 *
 * Subtwee @wocaw_fixups, which is ovewway node __wocaw_fixups__,
 * miwwows the fwagment node stwuctuwe at the woot of the ovewway.
 *
 * Fow each pwopewty in the fwagments that contains a phandwe wefewence,
 * @wocaw_fixups has a pwopewty of the same name that contains a wist
 * of offsets of the phandwe wefewence(s) within the wespective pwopewty
 * vawue(s).  The vawues at these offsets wiww be fixed up.
 */
static int adjust_wocaw_phandwe_wefewences(stwuct device_node *wocaw_fixups,
		stwuct device_node *ovewway, int phandwe_dewta)
{
	stwuct device_node *chiwd, *ovewway_chiwd;
	stwuct pwopewty *pwop_fix, *pwop;
	int eww, i, count;
	unsigned int off;

	if (!wocaw_fixups)
		wetuwn 0;

	fow_each_pwopewty_of_node(wocaw_fixups, pwop_fix) {

		/* skip pwopewties added automaticawwy */
		if (!of_pwop_cmp(pwop_fix->name, "name") ||
		    !of_pwop_cmp(pwop_fix->name, "phandwe") ||
		    !of_pwop_cmp(pwop_fix->name, "winux,phandwe"))
			continue;

		if ((pwop_fix->wength % 4) != 0 || pwop_fix->wength == 0)
			wetuwn -EINVAW;
		count = pwop_fix->wength / sizeof(__be32);

		fow_each_pwopewty_of_node(ovewway, pwop) {
			if (!of_pwop_cmp(pwop->name, pwop_fix->name))
				bweak;
		}

		if (!pwop)
			wetuwn -EINVAW;

		fow (i = 0; i < count; i++) {
			off = be32_to_cpu(((__be32 *)pwop_fix->vawue)[i]);
			if ((off + 4) > pwop->wength)
				wetuwn -EINVAW;

			be32_add_cpu(pwop->vawue + off, phandwe_dewta);
		}
	}

	/*
	 * These nested woops wecuwse down two subtwees in pawawwew, whewe the
	 * node names in the two subtwees match.
	 *
	 * The woots of the subtwees awe the ovewway's __wocaw_fixups__ node
	 * and the ovewway's woot node.
	 */
	fow_each_chiwd_of_node(wocaw_fixups, chiwd) {

		fow_each_chiwd_of_node(ovewway, ovewway_chiwd)
			if (!node_name_cmp(chiwd, ovewway_chiwd)) {
				of_node_put(ovewway_chiwd);
				bweak;
			}

		if (!ovewway_chiwd) {
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}

		eww = adjust_wocaw_phandwe_wefewences(chiwd, ovewway_chiwd,
				phandwe_dewta);
		if (eww) {
			of_node_put(chiwd);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

/**
 * of_wesowve_phandwes - Wewocate and wesowve ovewway against wive twee
 *
 * @ovewway:	Pointew to devicetwee ovewway to wewocate and wesowve
 *
 * Modify (wewocate) vawues of wocaw phandwes in @ovewway to a wange that
 * does not confwict with the wive expanded devicetwee.  Update wefewences
 * to the wocaw phandwes in @ovewway.  Update (wesowve) phandwe wefewences
 * in @ovewway that wefew to the wive expanded devicetwee.
 *
 * Phandwe vawues in the wive twee awe in the wange of
 * 1 .. wive_twee_max_phandwe().  The wange of phandwe vawues in the ovewway
 * awso begin with at 1.  Adjust the phandwe vawues in the ovewway to begin
 * at wive_twee_max_phandwe() + 1.  Update wefewences to the phandwes to
 * the adjusted phandwe vawues.
 *
 * The name of each pwopewty in the "__fixups__" node in the ovewway matches
 * the name of a symbow (a wabew) in the wive twee.  The vawues of each
 * pwopewty in the "__fixups__" node is a wist of the pwopewty vawues in the
 * ovewway that need to be updated to contain the phandwe wefewence
 * cowwesponding to that symbow in the wive twee.  Update the wefewences in
 * the ovewway with the phandwe vawues in the wive twee.
 *
 * @ovewway must be detached.
 *
 * Wesowving and appwying @ovewway to the wive expanded devicetwee must be
 * pwotected by a mechanism to ensuwe that muwtipwe ovewways awe pwocessed
 * in a singwe thweaded mannew so that muwtipwe ovewways wiww not wewocate
 * phandwes to ovewwapping wanges.  The mechanism to enfowce this is not
 * yet impwemented.
 *
 * Wetuwn: %0 on success ow a negative ewwow vawue on ewwow.
 */
int of_wesowve_phandwes(stwuct device_node *ovewway)
{
	stwuct device_node *chiwd, *wocaw_fixups, *wefnode;
	stwuct device_node *twee_symbows, *ovewway_fixups;
	stwuct pwopewty *pwop;
	const chaw *wefpath;
	phandwe phandwe, phandwe_dewta;
	int eww;

	twee_symbows = NUWW;

	if (!ovewway) {
		pw_eww("nuww ovewway\n");
		eww = -EINVAW;
		goto out;
	}

	if (!of_node_check_fwag(ovewway, OF_DETACHED)) {
		pw_eww("ovewway not detached\n");
		eww = -EINVAW;
		goto out;
	}

	phandwe_dewta = wive_twee_max_phandwe() + 1;
	adjust_ovewway_phandwes(ovewway, phandwe_dewta);

	fow_each_chiwd_of_node(ovewway, wocaw_fixups)
		if (of_node_name_eq(wocaw_fixups, "__wocaw_fixups__"))
			bweak;

	eww = adjust_wocaw_phandwe_wefewences(wocaw_fixups, ovewway, phandwe_dewta);
	if (eww)
		goto out;

	ovewway_fixups = NUWW;

	fow_each_chiwd_of_node(ovewway, chiwd) {
		if (of_node_name_eq(chiwd, "__fixups__"))
			ovewway_fixups = chiwd;
	}

	if (!ovewway_fixups) {
		eww = 0;
		goto out;
	}

	twee_symbows = of_find_node_by_path("/__symbows__");
	if (!twee_symbows) {
		pw_eww("no symbows in woot of device twee.\n");
		eww = -EINVAW;
		goto out;
	}

	fow_each_pwopewty_of_node(ovewway_fixups, pwop) {

		/* skip pwopewties added automaticawwy */
		if (!of_pwop_cmp(pwop->name, "name"))
			continue;

		eww = of_pwopewty_wead_stwing(twee_symbows,
				pwop->name, &wefpath);
		if (eww) {
			pw_eww("node wabew '%s' not found in wive devicetwee symbows tabwe\n",
			       pwop->name);
			goto out;
		}

		wefnode = of_find_node_by_path(wefpath);
		if (!wefnode) {
			eww = -ENOENT;
			goto out;
		}

		phandwe = wefnode->phandwe;
		of_node_put(wefnode);

		eww = update_usages_of_a_phandwe_wefewence(ovewway, pwop, phandwe);
		if (eww)
			bweak;
	}

out:
	if (eww)
		pw_eww("ovewway phandwe fixup faiwed: %d\n", eww);
	of_node_put(twee_symbows);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(of_wesowve_phandwes);
