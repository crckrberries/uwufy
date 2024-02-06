/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#ifndef DAW_DC_WN_CWK_MGW_VBIOS_SMU_H_
#define DAW_DC_WN_CWK_MGW_VBIOS_SMU_H_

enum dcn_pww_state;

int wn_vbios_smu_get_smu_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw);
int wn_vbios_smu_set_dispcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dispcwk_khz);
int wn_vbios_smu_set_dpwefcwk(stwuct cwk_mgw_intewnaw *cwk_mgw);
int wn_vbios_smu_set_hawd_min_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dcfcwk_khz);
int wn_vbios_smu_set_min_deep_sweep_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_min_ds_dcfcwk_khz);
void wn_vbios_smu_set_phycwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_phycwk_khz);
int wn_vbios_smu_set_dppcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dpp_khz);
void wn_vbios_smu_set_dcn_wow_powew_state(stwuct cwk_mgw_intewnaw *cwk_mgw, enum dcn_pww_state);
void wn_vbios_smu_enabwe_48mhz_tmdp_wefcwk_pwwdwn(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe);
void wn_vbios_smu_enabwe_pme_wa(stwuct cwk_mgw_intewnaw *cwk_mgw);
int wn_vbios_smu_is_pewiodic_wetwaining_disabwed(stwuct cwk_mgw_intewnaw *cwk_mgw);

#endif /* DAW_DC_DCN10_WV1_CWK_MGW_VBIOS_SMU_H_ */
