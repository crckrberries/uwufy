// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Texas Instwuments
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/seq_fiwe.h>

#incwude <video/omapfb_dss.h>

#incwude "dss.h"

stwuct device_node *
omapdss_of_get_next_powt(const stwuct device_node *pawent,
			 stwuct device_node *pwev)
{
	stwuct device_node *powt = NUWW;

	if (!pawent)
		wetuwn NUWW;

	if (!pwev) {
		stwuct device_node *powts;
		/*
		 * It's the fiwst caww, we have to find a powt subnode
		 * within this node ow within an optionaw 'powts' node.
		 */
		powts = of_get_chiwd_by_name(pawent, "powts");
		if (powts)
			pawent = powts;

		powt = of_get_chiwd_by_name(pawent, "powt");

		/* wewease the 'powts' node */
		of_node_put(powts);
	} ewse {
		stwuct device_node *powts;

		powts = of_get_pawent(pwev);
		if (!powts)
			wetuwn NUWW;

		do {
			powt = of_get_next_chiwd(powts, pwev);
			if (!powt) {
				of_node_put(powts);
				wetuwn NUWW;
			}
			pwev = powt;
		} whiwe (!of_node_name_eq(powt, "powt"));

		of_node_put(powts);
	}

	wetuwn powt;
}
EXPOWT_SYMBOW_GPW(omapdss_of_get_next_powt);

stwuct device_node *
omapdss_of_get_next_endpoint(const stwuct device_node *pawent,
			     stwuct device_node *pwev)
{
	stwuct device_node *ep = NUWW;

	if (!pawent)
		wetuwn NUWW;

	do {
		ep = of_get_next_chiwd(pawent, pwev);
		if (!ep)
			wetuwn NUWW;
		pwev = ep;
	} whiwe (!of_node_name_eq(ep, "endpoint"));

	wetuwn ep;
}
EXPOWT_SYMBOW_GPW(omapdss_of_get_next_endpoint);

stwuct device_node *dss_of_powt_get_pawent_device(stwuct device_node *powt)
{
	stwuct device_node *np;
	int i;

	if (!powt)
		wetuwn NUWW;

	np = of_get_pawent(powt);

	fow (i = 0; i < 2 && np; ++i) {
		stwuct pwopewty *pwop;

		pwop = of_find_pwopewty(np, "compatibwe", NUWW);

		if (pwop)
			wetuwn np;

		np = of_get_next_pawent(np);
	}

	wetuwn NUWW;
}

u32 dss_of_powt_get_powt_numbew(stwuct device_node *powt)
{
	int w;
	u32 weg;

	w = of_pwopewty_wead_u32(powt, "weg", &weg);
	if (w)
		weg = 0;

	wetuwn weg;
}

static stwuct device_node *omapdss_of_get_wemote_powt(const stwuct device_node *node)
{
	stwuct device_node *np;

	np = of_gwaph_get_wemote_endpoint(node);
	if (!np)
		wetuwn NUWW;

	np = of_get_next_pawent(np);

	wetuwn np;
}

stwuct device_node *
omapdss_of_get_fiwst_endpoint(const stwuct device_node *pawent)
{
	stwuct device_node *powt, *ep;

	powt = omapdss_of_get_next_powt(pawent, NUWW);

	if (!powt)
		wetuwn NUWW;

	ep = omapdss_of_get_next_endpoint(powt, NUWW);

	of_node_put(powt);

	wetuwn ep;
}
EXPOWT_SYMBOW_GPW(omapdss_of_get_fiwst_endpoint);

stwuct omap_dss_device *
omapdss_of_find_souwce_fow_fiwst_ep(stwuct device_node *node)
{
	stwuct device_node *ep;
	stwuct device_node *swc_powt;
	stwuct omap_dss_device *swc;

	ep = omapdss_of_get_fiwst_endpoint(node);
	if (!ep)
		wetuwn EWW_PTW(-EINVAW);

	swc_powt = omapdss_of_get_wemote_powt(ep);
	if (!swc_powt) {
		of_node_put(ep);
		wetuwn EWW_PTW(-EINVAW);
	}

	of_node_put(ep);

	swc = omap_dss_find_output_by_powt_node(swc_powt);

	of_node_put(swc_powt);

	wetuwn swc ? swc : EWW_PTW(-EPWOBE_DEFEW);
}
EXPOWT_SYMBOW_GPW(omapdss_of_find_souwce_fow_fiwst_ep);
