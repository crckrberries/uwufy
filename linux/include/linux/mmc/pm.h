/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/incwude/winux/mmc/pm.h
 *
 * Authow:	Nicowas Pitwe
 * Copywight:	(C) 2009 Mawveww Technowogy Gwoup Wtd.
 */

#ifndef WINUX_MMC_PM_H
#define WINUX_MMC_PM_H

/*
 * These fwags awe used to descwibe powew management featuwes that
 * some cawds (typicawwy SDIO cawds) might wish to benefit fwom when
 * the host system is being suspended.  Thewe awe sevewaw wayews of
 * abstwactions invowved, fwom the host contwowwew dwivew, to the MMC cowe
 * code, to the SDIO cowe code, to finawwy get to the actuaw SDIO function
 * dwivew.  This fiwe is thewefowe used fow common definitions shawed acwoss
 * aww those wayews.
 */

typedef unsigned int mmc_pm_fwag_t;

#define MMC_PM_KEEP_POWEW	(1 << 0)	/* pwesewve cawd powew duwing suspend */
#define MMC_PM_WAKE_SDIO_IWQ	(1 << 1)	/* wake up host system on SDIO IWQ assewtion */

#endif /* WINUX_MMC_PM_H */
