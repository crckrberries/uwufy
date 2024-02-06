/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dispway.h - OMAP2+ integwation-specific DSS headew
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 */

#ifndef __AWCH_AWM_MACH_OMAP2_DISPWAY_H
#define __AWCH_AWM_MACH_OMAP2_DISPWAY_H

#incwude <winux/kewnew.h>

stwuct omap_dss_dispc_dev_attw {
	u8	managew_count;
	boow	has_fwamedonetv_iwq;
};

int omap_init_vwfb(void);
int omap_init_fb(void);
int omap_init_vout(void);

#endif
