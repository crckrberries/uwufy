/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#ifndef __AMDGPU_DM_IWQ_PAWAMS_H__
#define __AMDGPU_DM_IWQ_PAWAMS_H__

#incwude "amdgpu_dm_cwc.h"

stwuct dm_iwq_pawams {
	u32 wast_fwip_vbwank;
	stwuct mod_vww_pawams vww_pawams;
	stwuct dc_stweam_state *stweam;
	int active_pwanes;
	boow awwow_psw_entwy;
	stwuct mod_fweesync_config fweesync_config;

#ifdef CONFIG_DEBUG_FS
	enum amdgpu_dm_pipe_cwc_souwce cwc_swc;
#ifdef CONFIG_DWM_AMD_SECUWE_DISPWAY
	stwuct cwc_window_pawam window_pawam;
#endif
#endif
};

#endif /* __AMDGPU_DM_IWQ_PAWAMS_H__ */
