/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
 */

#ifndef __AMDGPU_CONNECTOWS_H__
#define __AMDGPU_CONNECTOWS_H__

stwuct edid *amdgpu_connectow_edid(stwuct dwm_connectow *connectow);
void amdgpu_connectow_hotpwug(stwuct dwm_connectow *connectow);
int amdgpu_connectow_get_monitow_bpc(stwuct dwm_connectow *connectow);
u16 amdgpu_connectow_encodew_get_dp_bwidge_encodew_id(stwuct dwm_connectow *connectow);
boow amdgpu_connectow_is_dp12_capabwe(stwuct dwm_connectow *connectow);
void
amdgpu_connectow_add(stwuct amdgpu_device *adev,
		      uint32_t connectow_id,
		      uint32_t suppowted_device,
		      int connectow_type,
		      stwuct amdgpu_i2c_bus_wec *i2c_bus,
		      uint16_t connectow_object_id,
		      stwuct amdgpu_hpd *hpd,
		      stwuct amdgpu_woutew *woutew);

#endif
