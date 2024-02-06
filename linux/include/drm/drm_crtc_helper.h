/*
 * Copywight © 2006 Keith Packawd
 * Copywight © 2007-2008 Dave Aiwwie
 * Copywight © 2007-2008 Intew Cowpowation
 *   Jesse Bawnes <jesse.bawnes@intew.com>
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
 */

/*
 * The DWM mode setting hewpew functions awe common code fow dwivews to use if
 * they wish.  Dwivews awe not fowced to use this code in theiw
 * impwementations but it wouwd be usefuw if they code they do use at weast
 * pwovides a consistent intewface and opewation to usewspace
 */

#ifndef __DWM_CWTC_HEWPEW_H__
#define __DWM_CWTC_HEWPEW_H__

#incwude <winux/types.h>

stwuct dwm_atomic_state;
stwuct dwm_connectow;
stwuct dwm_cwtc;
stwuct dwm_device;
stwuct dwm_dispway_mode;
stwuct dwm_encodew;
stwuct dwm_fwamebuffew;
stwuct dwm_mode_set;
stwuct dwm_modeset_acquiwe_ctx;

void dwm_hewpew_disabwe_unused_functions(stwuct dwm_device *dev);
int dwm_cwtc_hewpew_set_config(stwuct dwm_mode_set *set,
			       stwuct dwm_modeset_acquiwe_ctx *ctx);
boow dwm_cwtc_hewpew_set_mode(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_dispway_mode *mode,
			      int x, int y,
			      stwuct dwm_fwamebuffew *owd_fb);
int dwm_cwtc_hewpew_atomic_check(stwuct dwm_cwtc *cwtc,
				 stwuct dwm_atomic_state *state);
boow dwm_hewpew_cwtc_in_use(stwuct dwm_cwtc *cwtc);
boow dwm_hewpew_encodew_in_use(stwuct dwm_encodew *encodew);

int dwm_hewpew_connectow_dpms(stwuct dwm_connectow *connectow, int mode);

void dwm_hewpew_wesume_fowce_mode(stwuct dwm_device *dev);
int dwm_hewpew_fowce_disabwe_aww(stwuct dwm_device *dev);

#endif
