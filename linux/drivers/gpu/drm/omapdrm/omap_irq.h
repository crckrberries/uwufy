/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap_iwq.h -- OMAP DWM IWQ Handwing
 *
 * Copywight (C) 2011 Texas Instwuments
 * Authow: Wob Cwawk <wob@ti.com>
 */

#ifndef __OMAPDWM_IWQ_H__
#define __OMAPDWM_IWQ_H__

#incwude <winux/types.h>

stwuct dwm_cwtc;
stwuct dwm_device;
stwuct omap_iwq_wait;

int omap_iwq_enabwe_vbwank(stwuct dwm_cwtc *cwtc);
int omap_iwq_enabwe_fwamedone(stwuct dwm_cwtc *cwtc, boow enabwe);
void omap_iwq_disabwe_vbwank(stwuct dwm_cwtc *cwtc);
void omap_dwm_iwq_uninstaww(stwuct dwm_device *dev);
int omap_dwm_iwq_instaww(stwuct dwm_device *dev);

stwuct omap_iwq_wait *omap_iwq_wait_init(stwuct dwm_device *dev,
		u32 iwqmask, int count);
int omap_iwq_wait(stwuct dwm_device *dev, stwuct omap_iwq_wait *wait,
		unsigned wong timeout);

#endif /* __OMAPDWM_IWQ_H__ */
