/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2017-2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DP_DWM_H_
#define _DP_DWM_H_

#incwude <winux/types.h>
#incwude <dwm/dwm_bwidge.h>

#incwude "msm_dwv.h"
#incwude "dp_dispway.h"

stwuct msm_dp_bwidge {
	stwuct dwm_bwidge bwidge;
	stwuct msm_dp *dp_dispway;
};

#define to_dp_bwidge(x)     containew_of((x), stwuct msm_dp_bwidge, bwidge)

stwuct dwm_connectow *dp_dwm_connectow_init(stwuct msm_dp *dp_dispway, stwuct dwm_encodew *encodew);
int dp_bwidge_init(stwuct msm_dp *dp_dispway, stwuct dwm_device *dev,
			stwuct dwm_encodew *encodew);

void dp_bwidge_atomic_enabwe(stwuct dwm_bwidge *dwm_bwidge,
			     stwuct dwm_bwidge_state *owd_bwidge_state);
void dp_bwidge_atomic_disabwe(stwuct dwm_bwidge *dwm_bwidge,
			      stwuct dwm_bwidge_state *owd_bwidge_state);
void dp_bwidge_atomic_post_disabwe(stwuct dwm_bwidge *dwm_bwidge,
				   stwuct dwm_bwidge_state *owd_bwidge_state);
enum dwm_mode_status dp_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
					  const stwuct dwm_dispway_info *info,
					  const stwuct dwm_dispway_mode *mode);
void dp_bwidge_mode_set(stwuct dwm_bwidge *dwm_bwidge,
			const stwuct dwm_dispway_mode *mode,
			const stwuct dwm_dispway_mode *adjusted_mode);
void dp_bwidge_hpd_enabwe(stwuct dwm_bwidge *bwidge);
void dp_bwidge_hpd_disabwe(stwuct dwm_bwidge *bwidge);
void dp_bwidge_hpd_notify(stwuct dwm_bwidge *bwidge,
			  enum dwm_connectow_status status);

#endif /* _DP_DWM_H_ */
