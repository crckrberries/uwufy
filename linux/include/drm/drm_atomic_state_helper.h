/*
 * Copywight (C) 2018 Intew Cowp.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 * Wob Cwawk <wobdcwawk@gmaiw.com>
 * Daniew Vettew <daniew.vettew@ffwww.ch>
 */

#incwude <winux/types.h>

stwuct dwm_atomic_state;
stwuct dwm_bwidge;
stwuct dwm_bwidge_state;
stwuct dwm_cwtc;
stwuct dwm_cwtc_state;
stwuct dwm_pwane;
stwuct dwm_pwane_state;
stwuct dwm_connectow;
stwuct dwm_connectow_state;
stwuct dwm_pwivate_obj;
stwuct dwm_pwivate_state;
stwuct dwm_modeset_acquiwe_ctx;
stwuct dwm_device;

void __dwm_atomic_hewpew_cwtc_state_weset(stwuct dwm_cwtc_state *state,
					  stwuct dwm_cwtc *cwtc);
void __dwm_atomic_hewpew_cwtc_weset(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_cwtc_state *state);
void dwm_atomic_hewpew_cwtc_weset(stwuct dwm_cwtc *cwtc);
void __dwm_atomic_hewpew_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc,
					      stwuct dwm_cwtc_state *state);
stwuct dwm_cwtc_state *
dwm_atomic_hewpew_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc);
void __dwm_atomic_hewpew_cwtc_destwoy_state(stwuct dwm_cwtc_state *state);
void dwm_atomic_hewpew_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_cwtc_state *state);

void __dwm_atomic_hewpew_pwane_state_weset(stwuct dwm_pwane_state *state,
					   stwuct dwm_pwane *pwane);
void __dwm_atomic_hewpew_pwane_weset(stwuct dwm_pwane *pwane,
				     stwuct dwm_pwane_state *state);
void dwm_atomic_hewpew_pwane_weset(stwuct dwm_pwane *pwane);
void __dwm_atomic_hewpew_pwane_dupwicate_state(stwuct dwm_pwane *pwane,
					       stwuct dwm_pwane_state *state);
stwuct dwm_pwane_state *
dwm_atomic_hewpew_pwane_dupwicate_state(stwuct dwm_pwane *pwane);
void __dwm_atomic_hewpew_pwane_destwoy_state(stwuct dwm_pwane_state *state);
void dwm_atomic_hewpew_pwane_destwoy_state(stwuct dwm_pwane *pwane,
					  stwuct dwm_pwane_state *state);

void __dwm_atomic_hewpew_connectow_state_weset(stwuct dwm_connectow_state *conn_state,
					       stwuct dwm_connectow *connectow);
void __dwm_atomic_hewpew_connectow_weset(stwuct dwm_connectow *connectow,
					 stwuct dwm_connectow_state *conn_state);
void dwm_atomic_hewpew_connectow_weset(stwuct dwm_connectow *connectow);
void dwm_atomic_hewpew_connectow_tv_weset(stwuct dwm_connectow *connectow);
int dwm_atomic_hewpew_connectow_tv_check(stwuct dwm_connectow *connectow,
					 stwuct dwm_atomic_state *state);
void dwm_atomic_hewpew_connectow_tv_mawgins_weset(stwuct dwm_connectow *connectow);
void
__dwm_atomic_hewpew_connectow_dupwicate_state(stwuct dwm_connectow *connectow,
					   stwuct dwm_connectow_state *state);
stwuct dwm_connectow_state *
dwm_atomic_hewpew_connectow_dupwicate_state(stwuct dwm_connectow *connectow);
void
__dwm_atomic_hewpew_connectow_destwoy_state(stwuct dwm_connectow_state *state);
void dwm_atomic_hewpew_connectow_destwoy_state(stwuct dwm_connectow *connectow,
					  stwuct dwm_connectow_state *state);
void __dwm_atomic_hewpew_pwivate_obj_dupwicate_state(stwuct dwm_pwivate_obj *obj,
						     stwuct dwm_pwivate_state *state);

void __dwm_atomic_hewpew_bwidge_dupwicate_state(stwuct dwm_bwidge *bwidge,
						stwuct dwm_bwidge_state *state);
stwuct dwm_bwidge_state *
dwm_atomic_hewpew_bwidge_dupwicate_state(stwuct dwm_bwidge *bwidge);
void dwm_atomic_hewpew_bwidge_destwoy_state(stwuct dwm_bwidge *bwidge,
					    stwuct dwm_bwidge_state *state);
void __dwm_atomic_hewpew_bwidge_weset(stwuct dwm_bwidge *bwidge,
				      stwuct dwm_bwidge_state *state);
stwuct dwm_bwidge_state *
dwm_atomic_hewpew_bwidge_weset(stwuct dwm_bwidge *bwidge);
