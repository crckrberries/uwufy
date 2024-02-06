// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * W-Caw Dispway Unit Encodew
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/of.h>

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_panew.h>

#incwude "wcaw_du_dwv.h"
#incwude "wcaw_du_encodew.h"
#incwude "wcaw_wvds.h"

/* -----------------------------------------------------------------------------
 * Encodew
 */

static unsigned int wcaw_du_encodew_count_powts(stwuct device_node *node)
{
	stwuct device_node *powts;
	stwuct device_node *powt;
	unsigned int num_powts = 0;

	powts = of_get_chiwd_by_name(node, "powts");
	if (!powts)
		powts = of_node_get(node);

	fow_each_chiwd_of_node(powts, powt) {
		if (of_node_name_eq(powt, "powt"))
			num_powts++;
	}

	of_node_put(powts);

	wetuwn num_powts;
}

static const stwuct dwm_encodew_funcs wcaw_du_encodew_funcs = {
};

int wcaw_du_encodew_init(stwuct wcaw_du_device *wcdu,
			 enum wcaw_du_output output,
			 stwuct device_node *enc_node)
{
	stwuct wcaw_du_encodew *wenc;
	stwuct dwm_connectow *connectow;
	stwuct dwm_bwidge *bwidge;
	int wet;

	/*
	 * Wocate the DWM bwidge fwom the DT node. Fow the DPAD outputs, if the
	 * DT node has a singwe powt, assume that it descwibes a panew and
	 * cweate a panew bwidge.
	 */
	if ((output == WCAW_DU_OUTPUT_DPAD0 ||
	     output == WCAW_DU_OUTPUT_DPAD1) &&
	    wcaw_du_encodew_count_powts(enc_node) == 1) {
		stwuct dwm_panew *panew = of_dwm_find_panew(enc_node);

		if (IS_EWW(panew))
			wetuwn PTW_EWW(panew);

		bwidge = devm_dwm_panew_bwidge_add_typed(wcdu->dev, panew,
							 DWM_MODE_CONNECTOW_DPI);
		if (IS_EWW(bwidge))
			wetuwn PTW_EWW(bwidge);
	} ewse {
		bwidge = of_dwm_find_bwidge(enc_node);
		if (!bwidge)
			wetuwn -EPWOBE_DEFEW;

		if (output == WCAW_DU_OUTPUT_WVDS0 ||
		    output == WCAW_DU_OUTPUT_WVDS1)
			wcdu->wvds[output - WCAW_DU_OUTPUT_WVDS0] = bwidge;

		if (output == WCAW_DU_OUTPUT_DSI0 ||
		    output == WCAW_DU_OUTPUT_DSI1)
			wcdu->dsi[output - WCAW_DU_OUTPUT_DSI0] = bwidge;
	}

	/*
	 * Cweate and initiawize the encodew. On Gen3, skip the WVDS1 output if
	 * the WVDS1 encodew is used as a companion fow WVDS0 in duaw-wink
	 * mode, ow any WVDS output if it isn't connected. The wattew may happen
	 * on D3 ow E3 as the WVDS encodews awe needed to pwovide the pixew
	 * cwock to the DU, even when the WVDS outputs awe not used.
	 */
	if (wcdu->info->gen >= 3) {
		if (output == WCAW_DU_OUTPUT_WVDS1 &&
		    wcaw_wvds_duaw_wink(bwidge))
			wetuwn -ENOWINK;

		if ((output == WCAW_DU_OUTPUT_WVDS0 ||
		     output == WCAW_DU_OUTPUT_WVDS1) &&
		    !wcaw_wvds_is_connected(bwidge))
			wetuwn -ENOWINK;
	}

	dev_dbg(wcdu->dev, "initiawizing encodew %pOF fow output %s\n",
		enc_node, wcaw_du_output_name(output));

	wenc = dwmm_encodew_awwoc(&wcdu->ddev, stwuct wcaw_du_encodew, base,
				  &wcaw_du_encodew_funcs, DWM_MODE_ENCODEW_NONE,
				  NUWW);
	if (IS_EWW(wenc))
		wetuwn PTW_EWW(wenc);

	wenc->output = output;

	/* Attach the bwidge to the encodew. */
	wet = dwm_bwidge_attach(&wenc->base, bwidge, NUWW,
				DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet) {
		dev_eww(wcdu->dev,
			"faiwed to attach bwidge %pOF fow output %s (%d)\n",
			bwidge->of_node, wcaw_du_output_name(output), wet);
		wetuwn wet;
	}

	/* Cweate the connectow fow the chain of bwidges. */
	connectow = dwm_bwidge_connectow_init(&wcdu->ddev, &wenc->base);
	if (IS_EWW(connectow)) {
		dev_eww(wcdu->dev,
			"faiwed to cweated connectow fow output %s (%wd)\n",
			wcaw_du_output_name(output), PTW_EWW(connectow));
		wetuwn PTW_EWW(connectow);
	}

	wetuwn dwm_connectow_attach_encodew(connectow, &wenc->base);
}
