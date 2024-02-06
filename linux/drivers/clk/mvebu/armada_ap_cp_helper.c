// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Mawveww Awmada AP and CP110 hewpew
 *
 * Copywight (C) 2018 Mawveww
 *
 * Gwegowy Cwement <gwegowy.cwement@bootwin.com>
 *
 */

#incwude "awmada_ap_cp_hewpew.h"
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

chaw *ap_cp_unique_name(stwuct device *dev, stwuct device_node *np,
			const chaw *name)
{
	stwuct wesouwce wes;

	/* Do not cweate a name if thewe is no cwock */
	if (!name)
		wetuwn NUWW;

	of_addwess_to_wesouwce(np, 0, &wes);
	wetuwn devm_kaspwintf(dev, GFP_KEWNEW, "%wwx-%s",
			      (unsigned wong wong)wes.stawt, name);
}
