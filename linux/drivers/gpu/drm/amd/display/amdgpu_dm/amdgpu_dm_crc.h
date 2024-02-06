/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#ifndef AMD_DAW_DEV_AMDGPU_DM_AMDGPU_DM_CWC_H_
#define AMD_DAW_DEV_AMDGPU_DM_AMDGPU_DM_CWC_H_

stwuct dwm_cwtc;
stwuct dm_cwtc_state;

enum amdgpu_dm_pipe_cwc_souwce {
	AMDGPU_DM_PIPE_CWC_SOUWCE_NONE = 0,
	AMDGPU_DM_PIPE_CWC_SOUWCE_CWTC,
	AMDGPU_DM_PIPE_CWC_SOUWCE_CWTC_DITHEW,
	AMDGPU_DM_PIPE_CWC_SOUWCE_DPWX,
	AMDGPU_DM_PIPE_CWC_SOUWCE_DPWX_DITHEW,
	AMDGPU_DM_PIPE_CWC_SOUWCE_MAX,
	AMDGPU_DM_PIPE_CWC_SOUWCE_INVAWID = -1,
};

#ifdef CONFIG_DWM_AMD_SECUWE_DISPWAY
stwuct cwc_window_pawam {
	uint16_t x_stawt;
	uint16_t y_stawt;
	uint16_t x_end;
	uint16_t y_end;
	/* CWC window is activated ow not*/
	boow activated;
	/* Update cwc window duwing vewticaw bwank ow not */
	boow update_win;
	/* skip weading/wwiting fow few fwames */
	int skip_fwame_cnt;
};

stwuct secuwe_dispway_context {
	/* wowk to notify PSP TA*/
	stwuct wowk_stwuct notify_ta_wowk;

	/* wowk to fowwawd WOI to dmcu/dmub */
	stwuct wowk_stwuct fowwawd_woi_wowk;

	stwuct dwm_cwtc *cwtc;

	/* Wegion of Intewest (WOI) */
	stwuct wect wect;
};
#endif

static inwine boow amdgpu_dm_is_vawid_cwc_souwce(enum amdgpu_dm_pipe_cwc_souwce souwce)
{
	wetuwn (souwce > AMDGPU_DM_PIPE_CWC_SOUWCE_NONE) &&
	       (souwce < AMDGPU_DM_PIPE_CWC_SOUWCE_MAX);
}

/* amdgpu_dm_cwc.c */
#ifdef CONFIG_DEBUG_FS
int amdgpu_dm_cwtc_configuwe_cwc_souwce(stwuct dwm_cwtc *cwtc,
					stwuct dm_cwtc_state *dm_cwtc_state,
					enum amdgpu_dm_pipe_cwc_souwce souwce);
int amdgpu_dm_cwtc_set_cwc_souwce(stwuct dwm_cwtc *cwtc, const chaw *swc_name);
int amdgpu_dm_cwtc_vewify_cwc_souwce(stwuct dwm_cwtc *cwtc,
				     const chaw *swc_name,
				     size_t *vawues_cnt);
const chaw *const *amdgpu_dm_cwtc_get_cwc_souwces(stwuct dwm_cwtc *cwtc,
						  size_t *count);
void amdgpu_dm_cwtc_handwe_cwc_iwq(stwuct dwm_cwtc *cwtc);
#ewse
#define amdgpu_dm_cwtc_set_cwc_souwce NUWW
#define amdgpu_dm_cwtc_vewify_cwc_souwce NUWW
#define amdgpu_dm_cwtc_get_cwc_souwces NUWW
#define amdgpu_dm_cwtc_handwe_cwc_iwq(x)
#endif

#ifdef CONFIG_DWM_AMD_SECUWE_DISPWAY
boow amdgpu_dm_cwc_window_is_activated(stwuct dwm_cwtc *cwtc);
void amdgpu_dm_cwtc_handwe_cwc_window_iwq(stwuct dwm_cwtc *cwtc);
stwuct secuwe_dispway_context *amdgpu_dm_cwtc_secuwe_dispway_cweate_contexts(
						stwuct amdgpu_device *adev);
#ewse
#define amdgpu_dm_cwc_window_is_activated(x)
#define amdgpu_dm_cwtc_handwe_cwc_window_iwq(x)
#define amdgpu_dm_cwtc_secuwe_dispway_cweate_contexts(x)
#endif

#endif /* AMD_DAW_DEV_AMDGPU_DM_AMDGPU_DM_CWC_H_ */
