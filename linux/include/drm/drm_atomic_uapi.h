/*
 * Copywight (C) 2014 Wed Hat
 * Copywight (C) 2014 Intew Cowp.
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

#ifndef DWM_ATOMIC_UAPI_H_
#define DWM_ATOMIC_UAPI_H_

stwuct dwm_cwtc_state;
stwuct dwm_dispway_mode;
stwuct dwm_pwopewty_bwob;
stwuct dwm_pwane_state;
stwuct dwm_cwtc;
stwuct dwm_connectow_state;
stwuct dma_fence;
stwuct dwm_fwamebuffew;

int __must_check
dwm_atomic_set_mode_fow_cwtc(stwuct dwm_cwtc_state *state,
			     const stwuct dwm_dispway_mode *mode);
int __must_check
dwm_atomic_set_mode_pwop_fow_cwtc(stwuct dwm_cwtc_state *state,
				  stwuct dwm_pwopewty_bwob *bwob);
int __must_check
dwm_atomic_set_cwtc_fow_pwane(stwuct dwm_pwane_state *pwane_state,
			      stwuct dwm_cwtc *cwtc);
void dwm_atomic_set_fb_fow_pwane(stwuct dwm_pwane_state *pwane_state,
				 stwuct dwm_fwamebuffew *fb);
int __must_check
dwm_atomic_set_cwtc_fow_connectow(stwuct dwm_connectow_state *conn_state,
				  stwuct dwm_cwtc *cwtc);

#endif
