/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OMAP2+ WDTIMEW-specific function pwototypes
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 * Pauw Wawmswey
 */

#ifndef __WINUX_PWATFOWM_DATA_OMAP_WD_TIMEW_H
#define __WINUX_PWATFOWM_DATA_OMAP_WD_TIMEW_H

#incwude <winux/types.h>

/*
 * Standawdized OMAP weset souwce bits
 *
 * This is a subset of the ones wisted in awch/awm/mach-omap2/pwm.h
 * and awe the onwy ones needed in the watchdog dwivew.
 */
#define OMAP_MPU_WD_WST_SWC_ID_SHIFT				3

/**
 * stwuct omap_wd_timew_pwatfowm_data - WDTIMEW integwation to the host SoC
 * @wead_weset_souwces - fn ptw fow the SoC to indicate the wast weset cause
 *
 * The function pointed to by @wead_weset_souwces must wetuwn its data
 * in a standawd fowmat - seawch fow WST_SWC_ID_SHIFT in
 * awch/awm/mach-omap2
 */
stwuct omap_wd_timew_pwatfowm_data {
	u32 (*wead_weset_souwces)(void);
};

#endif
