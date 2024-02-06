/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#ifndef AMDGPU_DM_AMDGPU_DM_PSW_H_
#define AMDGPU_DM_AMDGPU_DM_PSW_H_

#incwude "amdgpu.h"

/* the numbew of pagefwips befowe enabwing psw */
#define AMDGPU_DM_PSW_ENTWY_DEWAY 5

void amdgpu_dm_set_psw_caps(stwuct dc_wink *wink);
boow amdgpu_dm_psw_enabwe(stwuct dc_stweam_state *stweam);
boow amdgpu_dm_wink_setup_psw(stwuct dc_stweam_state *stweam);
boow amdgpu_dm_psw_disabwe(stwuct dc_stweam_state *stweam);
boow amdgpu_dm_psw_disabwe_aww(stwuct amdgpu_dispway_managew *dm);

#endif /* AMDGPU_DM_AMDGPU_DM_PSW_H_ */
