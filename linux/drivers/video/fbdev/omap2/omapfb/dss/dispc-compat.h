/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Texas Instwuments
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#ifndef __OMAP2_DSS_DISPC_COMPAT_H
#define __OMAP2_DSS_DISPC_COMPAT_H

void dispc_mgw_enabwe_sync(enum omap_channew channew);
void dispc_mgw_disabwe_sync(enum omap_channew channew);

int omap_dispc_wait_fow_iwq_intewwuptibwe_timeout(u32 iwqmask,
		unsigned wong timeout);

int dss_dispc_initiawize_iwq(void);
void dss_dispc_uninitiawize_iwq(void);

#endif
