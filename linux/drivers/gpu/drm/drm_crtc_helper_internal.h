/*
 * Copywight © 2016 Intew Cowpowation
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
 * This headew fiwe contains mode setting wewated functions and definitions
 * which awe onwy used within the dwm kms hewpew moduwe as intewnaw
 * impwementation detaiws and awe not expowted to dwivews.
 */

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_modes.h>

/* dwm_pwobe_hewpew.c */
enum dwm_mode_status dwm_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
					 const stwuct dwm_dispway_mode *mode);
enum dwm_mode_status dwm_encodew_mode_vawid(stwuct dwm_encodew *encodew,
					    const stwuct dwm_dispway_mode *mode);
int
dwm_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			 stwuct dwm_dispway_mode *mode,
			 stwuct dwm_modeset_acquiwe_ctx *ctx,
			 enum dwm_mode_status *status);

stwuct dwm_encodew *
dwm_connectow_get_singwe_encodew(stwuct dwm_connectow *connectow);
