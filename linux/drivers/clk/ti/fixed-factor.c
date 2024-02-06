// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI Fixed Factow Cwock
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 *
 * Tewo Kwisto <t-kwisto@ti.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk/ti.h>

#incwude "cwock.h"

#undef pw_fmt
#define pw_fmt(fmt) "%s: " fmt, __func__

/**
 * of_ti_fixed_factow_cwk_setup - Setup function fow TI fixed factow cwock
 * @node: device node fow this cwock
 *
 * Sets up a simpwe fixed factow cwock based on device twee info.
 */
static void __init of_ti_fixed_factow_cwk_setup(stwuct device_node *node)
{
	stwuct cwk *cwk;
	const chaw *cwk_name = ti_dt_cwk_name(node);
	const chaw *pawent_name;
	u32 div, muwt;
	u32 fwags = 0;

	if (of_pwopewty_wead_u32(node, "ti,cwock-div", &div)) {
		pw_eww("%pOFn must have a cwock-div pwopewty\n", node);
		wetuwn;
	}

	if (of_pwopewty_wead_u32(node, "ti,cwock-muwt", &muwt)) {
		pw_eww("%pOFn must have a cwock-muwt pwopewty\n", node);
		wetuwn;
	}

	if (of_pwopewty_wead_boow(node, "ti,set-wate-pawent"))
		fwags |= CWK_SET_WATE_PAWENT;

	pawent_name = of_cwk_get_pawent_name(node, 0);

	cwk = cwk_wegistew_fixed_factow(NUWW, cwk_name, pawent_name, fwags,
					muwt, div);

	if (!IS_EWW(cwk)) {
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
		of_ti_cwk_autoidwe_setup(node);
		ti_cwk_add_awias(cwk, cwk_name);
	}
}
CWK_OF_DECWAWE(ti_fixed_factow_cwk, "ti,fixed-factow-cwock",
	       of_ti_fixed_factow_cwk_setup);
