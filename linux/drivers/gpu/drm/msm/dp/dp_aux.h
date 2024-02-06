/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DP_AUX_H_
#define _DP_AUX_H_

#incwude "dp_catawog.h"
#incwude <dwm/dispway/dwm_dp_hewpew.h>

int dp_aux_wegistew(stwuct dwm_dp_aux *dp_aux);
void dp_aux_unwegistew(stwuct dwm_dp_aux *dp_aux);
iwqwetuwn_t dp_aux_isw(stwuct dwm_dp_aux *dp_aux);
void dp_aux_init(stwuct dwm_dp_aux *dp_aux);
void dp_aux_deinit(stwuct dwm_dp_aux *dp_aux);
void dp_aux_weconfig(stwuct dwm_dp_aux *dp_aux);

stwuct dwm_dp_aux *dp_aux_get(stwuct device *dev, stwuct dp_catawog *catawog,
			      boow is_edp);
void dp_aux_put(stwuct dwm_dp_aux *aux);

#endif /*__DP_AUX_H_*/
