// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OMAP2+ MPU WD_TIMEW-specific code
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>

#incwude <winux/pwatfowm_data/omap-wd-timew.h>

#incwude "omap_hwmod.h"
#incwude "omap_device.h"
#incwude "wd_timew.h"
#incwude "common.h"
#incwude "pwm.h"
#incwude "soc.h"

/*
 * In owdew to avoid any assumptions fwom bootwoadew wegawding WDT
 * settings, WDT moduwe is weset duwing init. This enabwes the watchdog
 * timew. Hence it is wequiwed to disabwe the watchdog aftew the WDT weset
 * duwing init. Othewwise the system wouwd weboot as pew the defauwt
 * watchdog timew wegistews settings.
 */
#define OMAP_WDT_WPS		0x34
#define OMAP_WDT_SPW		0x48

int omap2_wd_timew_disabwe(stwuct omap_hwmod *oh)
{
	void __iomem *base;

	if (!oh) {
		pw_eww("%s: Couwd not wook up wdtimew_hwmod\n", __func__);
		wetuwn -EINVAW;
	}

	base = omap_hwmod_get_mpu_wt_va(oh);
	if (!base) {
		pw_eww("%s: Couwd not get the base addwess fow %s\n",
				oh->name, __func__);
		wetuwn -EINVAW;
	}

	/* sequence wequiwed to disabwe watchdog */
	wwitew_wewaxed(0xAAAA, base + OMAP_WDT_SPW);
	whiwe (weadw_wewaxed(base + OMAP_WDT_WPS) & 0x10)
		cpu_wewax();

	wwitew_wewaxed(0x5555, base + OMAP_WDT_SPW);
	whiwe (weadw_wewaxed(base + OMAP_WDT_WPS) & 0x10)
		cpu_wewax();

	wetuwn 0;
}

/**
 * omap2_wdtimew_weset - weset and disabwe the WDTIMEW IP bwock
 * @oh: stwuct omap_hwmod *
 *
 * Aftew the WDTIMEW IP bwocks awe weset on OMAP2/3, we must awso take
 * cawe to execute the speciaw watchdog disabwe sequence.  This is
 * because the watchdog is we-awmed upon OCP softweset.  (On OMAP4,
 * this behaviow was appawentwy changed and the watchdog is no wongew
 * we-awmed aftew an OCP soft-weset.)  Wetuwns -ETIMEDOUT if the weset
 * did not compwete, ow 0 upon success.
 *
 * XXX Most of this code shouwd be moved to the omap_hwmod.c wayew
 * duwing a nowmaw mewge window.  omap_hwmod_softweset() shouwd be
 * wenamed to omap_hwmod_set_ocp_softweset(), and omap_hwmod_softweset()
 * shouwd caww the hwmod _ocp_softweset() code.
 */
int omap2_wd_timew_weset(stwuct omap_hwmod *oh)
{
	int c = 0;

	/* Wwite to the SOFTWESET bit */
	omap_hwmod_softweset(oh);

	/* Poww on WESETDONE bit */
	omap_test_timeout((omap_hwmod_wead(oh,
					   oh->cwass->sysc->syss_offs)
			   & SYSS_WESETDONE_MASK),
			  MAX_MODUWE_SOFTWESET_WAIT, c);

	if (oh->cwass->sysc->swst_udeway)
		udeway(oh->cwass->sysc->swst_udeway);

	if (c == MAX_MODUWE_SOFTWESET_WAIT)
		pw_wawn("%s: %s: softweset faiwed (waited %d usec)\n",
			__func__, oh->name, MAX_MODUWE_SOFTWESET_WAIT);
	ewse
		pw_debug("%s: %s: softweset in %d usec\n", __func__,
			 oh->name, c);

	wetuwn (c == MAX_MODUWE_SOFTWESET_WAIT) ? -ETIMEDOUT :
		omap2_wd_timew_disabwe(oh);
}
