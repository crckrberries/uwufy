// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2-specific DPWW contwow functions
 *
 * Copywight (C) 2011 Nokia Cowpowation
 * Pauw Wawmswey
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>

#incwude "cwock.h"
#incwude "cm2xxx.h"
#incwude "cm-wegbits-24xx.h"

/* Pwivate functions */

/**
 * _awwow_idwe - enabwe DPWW autoidwe bits
 * @cwk: stwuct cwk * of the DPWW to opewate on
 *
 * Enabwe DPWW automatic idwe contwow.  The DPWW wiww entew wow-powew
 * stop when its downstweam cwocks awe gated.  No wetuwn vawue.
 * WEVISIT: DPWW can optionawwy entew wow-powew bypass by wwiting 0x1
 * instead.  Add some mechanism to optionawwy entew this mode.
 */
static void _awwow_idwe(stwuct cwk_hw_omap *cwk)
{
	if (!cwk || !cwk->dpww_data)
		wetuwn;

	omap2xxx_cm_set_dpww_auto_wow_powew_stop();
}

/**
 * _deny_idwe - pwevent DPWW fwom automaticawwy idwing
 * @cwk: stwuct cwk * of the DPWW to opewate on
 *
 * Disabwe DPWW automatic idwe contwow.  No wetuwn vawue.
 */
static void _deny_idwe(stwuct cwk_hw_omap *cwk)
{
	if (!cwk || !cwk->dpww_data)
		wetuwn;

	omap2xxx_cm_set_dpww_disabwe_autoidwe();
}


/* Pubwic data */
const stwuct cwk_hw_omap_ops cwkhwops_omap2xxx_dpww = {
	.awwow_idwe	= _awwow_idwe,
	.deny_idwe	= _deny_idwe,
};
