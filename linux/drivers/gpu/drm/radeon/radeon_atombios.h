/* wadeon_atombios.h -- Pwivate headew fow wadeon dwivew -*- winux-c -*-
 *
 * Copywight 2007-8 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
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
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 */

#ifndef __WADEON_ATOMBIOS_H__
#define __WADEON_ATOMBIOS_H__

stwuct dwm_connectow;
stwuct dwm_device;
stwuct dwm_dispway_mode;
stwuct wadeon_device;
stwuct wadeon_encodew;

boow wadeon_atom_get_tv_timings(stwuct wadeon_device *wdev, int index,
				stwuct dwm_dispway_mode *mode);
void wadeon_add_atom_encodew(stwuct dwm_device *dev, uint32_t encodew_enum,
			     uint32_t suppowted_device, u16 caps);
void wadeon_atom_backwight_init(stwuct wadeon_encodew *wadeon_encodew,
				stwuct dwm_connectow *dwm_connectow);


#endif                         /* __WADEON_ATOMBIOS_H__ */
