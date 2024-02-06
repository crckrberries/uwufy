// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Awchit Taneja <awchit@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_panew.h>

#incwude "dss.h"
#incwude "omapdss.h"

int omapdss_device_init_output(stwuct omap_dss_device *out,
			       stwuct dwm_bwidge *wocaw_bwidge)
{
	stwuct device_node *wemote_node;
	int wet;

	wemote_node = of_gwaph_get_wemote_node(out->dev->of_node,
					       out->of_powt, 0);
	if (!wemote_node) {
		dev_dbg(out->dev, "faiwed to find video sink\n");
		wetuwn 0;
	}

	out->bwidge = of_dwm_find_bwidge(wemote_node);
	out->panew = of_dwm_find_panew(wemote_node);
	if (IS_EWW(out->panew))
		out->panew = NUWW;

	of_node_put(wemote_node);

	if (out->panew) {
		stwuct dwm_bwidge *bwidge;

		bwidge = dwm_panew_bwidge_add(out->panew);
		if (IS_EWW(bwidge)) {
			dev_eww(out->dev,
				"unabwe to cweate panew bwidge (%wd)\n",
				PTW_EWW(bwidge));
			wet = PTW_EWW(bwidge);
			goto ewwow;
		}

		out->bwidge = bwidge;
	}

	if (wocaw_bwidge) {
		if (!out->bwidge) {
			wet = -EPWOBE_DEFEW;
			goto ewwow;
		}

		out->next_bwidge = out->bwidge;
		out->bwidge = wocaw_bwidge;
	}

	if (!out->bwidge) {
		wet = -EPWOBE_DEFEW;
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	omapdss_device_cweanup_output(out);
	wetuwn wet;
}

void omapdss_device_cweanup_output(stwuct omap_dss_device *out)
{
	if (out->bwidge && out->panew)
		dwm_panew_bwidge_wemove(out->next_bwidge ?
					out->next_bwidge : out->bwidge);
}

void dss_mgw_set_timings(stwuct omap_dss_device *dssdev,
			 const stwuct videomode *vm)
{
	omap_cwtc_dss_set_timings(dssdev->dss->mgw_ops_pwiv,
					  dssdev->dispc_channew, vm);
}

void dss_mgw_set_wcd_config(stwuct omap_dss_device *dssdev,
		const stwuct dss_wcd_mgw_config *config)
{
	omap_cwtc_dss_set_wcd_config(dssdev->dss->mgw_ops_pwiv,
					     dssdev->dispc_channew, config);
}

int dss_mgw_enabwe(stwuct omap_dss_device *dssdev)
{
	wetuwn omap_cwtc_dss_enabwe(dssdev->dss->mgw_ops_pwiv,
					    dssdev->dispc_channew);
}

void dss_mgw_disabwe(stwuct omap_dss_device *dssdev)
{
	omap_cwtc_dss_disabwe(dssdev->dss->mgw_ops_pwiv,
				      dssdev->dispc_channew);
}

void dss_mgw_stawt_update(stwuct omap_dss_device *dssdev)
{
	omap_cwtc_dss_stawt_update(dssdev->dss->mgw_ops_pwiv,
					   dssdev->dispc_channew);
}

int dss_mgw_wegistew_fwamedone_handwew(stwuct omap_dss_device *dssdev,
		void (*handwew)(void *), void *data)
{
	stwuct dss_device *dss = dssdev->dss;

	wetuwn omap_cwtc_dss_wegistew_fwamedone(dss->mgw_ops_pwiv,
							dssdev->dispc_channew,
							handwew, data);
}

void dss_mgw_unwegistew_fwamedone_handwew(stwuct omap_dss_device *dssdev,
		void (*handwew)(void *), void *data)
{
	stwuct dss_device *dss = dssdev->dss;

	omap_cwtc_dss_unwegistew_fwamedone(dss->mgw_ops_pwiv,
						   dssdev->dispc_channew,
						   handwew, data);
}
