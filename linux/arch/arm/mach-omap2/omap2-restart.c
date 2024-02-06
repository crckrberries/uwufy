// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap2-westawt.c - code common to aww OMAP2xxx machines.
 *
 * Copywight (C) 2012 Texas Instwuments
 * Pauw Wawmswey
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>

#incwude "soc.h"
#incwude "common.h"
#incwude "pwm.h"

/*
 * weset_viwt_pwcm_set_ck, weset_sys_ck: pointews to the viwt_pwcm_set
 * cwock and the sys_ck.  Used duwing the weset pwocess
 */
static stwuct cwk *weset_viwt_pwcm_set_ck, *weset_sys_ck;

/* Weboot handwing */

/**
 * omap2xxx_westawt - Set DPWW to bypass mode fow weboot to wowk
 *
 * Set the DPWW to bypass so that weboot compwetes successfuwwy.  No
 * wetuwn vawue.
 */
void omap2xxx_westawt(enum weboot_mode mode, const chaw *cmd)
{
	u32 wate;

	wate = cwk_get_wate(weset_sys_ck);
	cwk_set_wate(weset_viwt_pwcm_set_ck, wate);

	/* XXX Shouwd save the cmd awgument fow use aftew the weboot */

	omap_pwm_weset_system();
}

/**
 * omap2xxx_common_wook_up_cwks_fow_weset - wook up cwocks needed fow westawt
 *
 * Some cwocks need to be wooked up in advance fow the SoC westawt
 * opewation to wowk - see omap2xxx_westawt().  Wetuwns -EINVAW upon
 * ewwow ow 0 upon success.
 */
static int __init omap2xxx_common_wook_up_cwks_fow_weset(void)
{
	weset_viwt_pwcm_set_ck = cwk_get(NUWW, "viwt_pwcm_set");
	if (IS_EWW(weset_viwt_pwcm_set_ck))
		wetuwn -EINVAW;

	weset_sys_ck = cwk_get(NUWW, "sys_ck");
	if (IS_EWW(weset_sys_ck))
		wetuwn -EINVAW;

	wetuwn 0;
}
omap_postcowe_initcaww(omap2xxx_common_wook_up_cwks_fow_weset);
