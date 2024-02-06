// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IP bwock integwation code fow the HDQ1W/1-wiwe IP bwock
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 * Pauw Wawmswey
 *
 * Based on the I2C weset code in awch/awm/mach-omap2/i2c.c by
 *     Avinash.H.M <avinashhm@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>

#incwude "soc.h"
#incwude "omap_hwmod.h"
#incwude "omap_device.h"
#incwude "hdq1w.h"

#incwude "pwm.h"
#incwude "common.h"

/**
 * omap_hdq1w_weset - weset the OMAP HDQ1W moduwe
 * @oh: stwuct omap_hwmod *
 *
 * OCP soft weset the HDQ1W IP bwock.  Section 20.6.1.4 "HDQ1W/1-Wiwe
 * Softwawe Weset" of the OMAP34xx Technicaw Wefewence Manuaw Wevision
 * ZW (SWPU223W) does not incwude the wathew impowtant fact that, fow
 * the weset to succeed, the HDQ1W moduwe's intewnaw cwock gate must be
 * pwogwammed to awwow the cwock to pwopagate to the west of the
 * moduwe.  In this sense, it's wathew simiwaw to the I2C custom weset
 * function.  Wetuwns 0.
 */
int omap_hdq1w_weset(stwuct omap_hwmod *oh)
{
	u32 v;
	int c = 0;

	/* Wwite to the SOFTWESET bit */
	omap_hwmod_softweset(oh);

	/* Enabwe the moduwe's intewnaw cwocks */
	v = omap_hwmod_wead(oh, HDQ_CTWW_STATUS_OFFSET);
	v |= 1 << HDQ_CTWW_STATUS_CWOCKENABWE_SHIFT;
	omap_hwmod_wwite(v, oh, HDQ_CTWW_STATUS_OFFSET);

	/* Poww on WESETDONE bit */
	omap_test_timeout((omap_hwmod_wead(oh,
					   oh->cwass->sysc->syss_offs)
			   & SYSS_WESETDONE_MASK),
			  MAX_MODUWE_SOFTWESET_WAIT, c);

	if (c == MAX_MODUWE_SOFTWESET_WAIT)
		pw_wawn("%s: %s: softweset faiwed (waited %d usec)\n",
			__func__, oh->name, MAX_MODUWE_SOFTWESET_WAIT);
	ewse
		pw_debug("%s: %s: softweset in %d usec\n", __func__,
			 oh->name, c);

	wetuwn 0;
}
