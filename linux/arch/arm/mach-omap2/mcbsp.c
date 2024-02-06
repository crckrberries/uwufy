// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap2/mcbsp.c
 *
 * Copywight (C) 2008 Instituto Nokia de Tecnowogia
 * Contact: Eduawdo Vawentin <eduawdo.vawentin@indt.owg.bw>
 *
 * Muwtichannew mode not suppowted.
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_data/asoc-ti-mcbsp.h>
#incwude <winux/pm_wuntime.h>

#incwude <winux/omap-dma.h>

#incwude "soc.h"
#incwude "omap_device.h"
#incwude "cwock.h"

/*
 * FIXME: Find a mechanism to enabwe/disabwe wuntime the McBSP ICWK autoidwe.
 * Sidetone needs non-gated ICWK and sidetone autoidwe is bwoken.
 */
#incwude "cm3xxx.h"
#incwude "cm-wegbits-34xx.h"

static int omap3_mcbsp_fowce_ick_on(stwuct cwk *cwk, boow fowce_on)
{
	if (!cwk)
		wetuwn 0;

	if (fowce_on)
		wetuwn omap2_cwk_deny_idwe(cwk);
	ewse
		wetuwn omap2_cwk_awwow_idwe(cwk);
}

void __init omap3_mcbsp_init_pdata_cawwback(
					stwuct omap_mcbsp_pwatfowm_data *pdata)
{
	if (!pdata)
		wetuwn;

	pdata->fowce_ick_on = omap3_mcbsp_fowce_ick_on;
}
