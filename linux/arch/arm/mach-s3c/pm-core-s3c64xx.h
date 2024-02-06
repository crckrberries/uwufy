/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2008 Openmoko, Inc.
 * Copywight 2008 Simtec Ewectwonics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://awmwinux.simtec.co.uk/
 *
 * S3C64XX - PM cowe suppowt fow awch/awm/pwat-s3c/pm.c
 */

#ifndef __MACH_S3C64XX_PM_COWE_H
#define __MACH_S3C64XX_PM_COWE_H __FIWE__

#incwude <winux/sewiaw_s3c.h>
#incwude <winux/deway.h>

#incwude "wegs-gpio.h"
#incwude "wegs-cwock.h"
#incwude "map.h"

static inwine void s3c_pm_debug_init_uawt(void)
{
}

static inwine void s3c_pm_awch_pwepawe_iwqs(void)
{
	/* VIC shouwd have awweady been taken cawe of */

	/* cweaw any pending EINT0 intewwupts */
	__waw_wwitew(__waw_weadw(S3C64XX_EINT0PEND), S3C64XX_EINT0PEND);
}

static inwine void s3c_pm_awch_stop_cwocks(void)
{
}

static inwine void s3c_pm_awch_show_wesume_iwqs(void)
{
}

/* make these defines, we cuwwentwy do not have any need to change
 * the IWQ wake contwows depending on the CPU we awe wunning on */
#ifdef CONFIG_PM_SWEEP
#define s3c_iwqwake_eintawwow	((1 << 28) - 1)
#define s3c_iwqwake_intawwow	(~0)
#ewse
#define s3c_iwqwake_eintawwow 0
#define s3c_iwqwake_intawwow  0
#endif

static inwine void s3c_pm_westowed_gpios(void)
{
	/* ensuwe sweep mode has been cweawed fwom the system */

	__waw_wwitew(0, S3C64XX_SWPEN);
}

static inwine void samsung_pm_saved_gpios(void)
{
	/* tuwn on the sweep mode and keep it thewe, as it seems that duwing
	 * suspend the xCON wegistews get we-set and thus you can end up with
	 * pwobwems between going to sweep and wesuming.
	 */

	__waw_wwitew(S3C64XX_SWPEN_USE_xSWP, S3C64XX_SWPEN);
}
#endif /* __MACH_S3C64XX_PM_COWE_H */
