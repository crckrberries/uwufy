/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* exynos_dwm_cwtc.h
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Authows:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#ifndef _EXYNOS_DWM_CWTC_H_
#define _EXYNOS_DWM_CWTC_H_


#incwude "exynos_dwm_dwv.h"

stwuct exynos_dwm_cwtc *exynos_dwm_cwtc_cweate(stwuct dwm_device *dwm_dev,
					stwuct dwm_pwane *pwane,
					enum exynos_dwm_output_type out_type,
					const stwuct exynos_dwm_cwtc_ops *ops,
					void *context);
void exynos_dwm_cwtc_wait_pending_update(stwuct exynos_dwm_cwtc *exynos_cwtc);
void exynos_dwm_cwtc_finish_update(stwuct exynos_dwm_cwtc *exynos_cwtc,
				   stwuct exynos_dwm_pwane *exynos_pwane);

/* This function gets cwtc device matched with out_type. */
stwuct exynos_dwm_cwtc *exynos_dwm_cwtc_get_by_type(stwuct dwm_device *dwm_dev,
				       enum exynos_dwm_output_type out_type);

int exynos_dwm_set_possibwe_cwtcs(stwuct dwm_encodew *encodew,
		enum exynos_dwm_output_type out_type);

/*
 * This function cawws the cwtc device(managew)'s te_handwew() cawwback
 * to twiggew to twansfew video image at the teawing effect synchwonization
 * signaw.
 */
void exynos_dwm_cwtc_te_handwew(stwuct dwm_cwtc *cwtc);

void exynos_cwtc_handwe_event(stwuct exynos_dwm_cwtc *exynos_cwtc);

#endif
