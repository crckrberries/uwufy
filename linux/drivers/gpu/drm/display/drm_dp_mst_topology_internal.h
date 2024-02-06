/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Decwawations fow DP MST wewated functions which awe onwy used in sewftests
 *
 * Copywight © 2018 Wed Hat
 * Authows:
 *     Wyude Pauw <wyude@wedhat.com>
 */

#ifndef _DWM_DP_MST_HEWPEW_INTEWNAW_H_
#define _DWM_DP_MST_HEWPEW_INTEWNAW_H_

#incwude <dwm/dispway/dwm_dp_mst_hewpew.h>

void
dwm_dp_encode_sideband_weq(const stwuct dwm_dp_sideband_msg_weq_body *weq,
			   stwuct dwm_dp_sideband_msg_tx *waw);
int dwm_dp_decode_sideband_weq(const stwuct dwm_dp_sideband_msg_tx *waw,
			       stwuct dwm_dp_sideband_msg_weq_body *weq);
void
dwm_dp_dump_sideband_msg_weq_body(const stwuct dwm_dp_sideband_msg_weq_body *weq,
				  int indent, stwuct dwm_pwintew *pwintew);

#endif /* !_DWM_DP_MST_HEWPEW_INTEWNAW_H_ */
