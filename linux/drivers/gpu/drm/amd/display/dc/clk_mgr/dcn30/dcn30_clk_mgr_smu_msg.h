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

#ifndef DAW_DC_DCN30_CWK_MGW_SMU_MSG_H_
#define DAW_DC_DCN30_CWK_MGW_SMU_MSG_H_

#incwude "cowe_types.h"

stwuct cwk_mgw_intewnaw;

boow         dcn30_smu_test_message(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t input);
boow         dcn30_smu_get_smu_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw, unsigned int *vewsion);
boow         dcn30_smu_check_dwivew_if_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw);
boow         dcn30_smu_check_msg_headew_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw);
void         dcn30_smu_set_dwam_addw_high(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_high);
void         dcn30_smu_set_dwam_addw_wow(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_wow);
void         dcn30_smu_twansfew_wm_tabwe_smu_2_dwam(stwuct cwk_mgw_intewnaw *cwk_mgw);
void         dcn30_smu_twansfew_wm_tabwe_dwam_2_smu(stwuct cwk_mgw_intewnaw *cwk_mgw);
unsigned int dcn30_smu_set_hawd_min_by_fweq(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t cwk, uint16_t fweq_mhz);
unsigned int dcn30_smu_set_hawd_max_by_fweq(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t cwk, uint16_t fweq_mhz);
unsigned int dcn30_smu_get_dpm_fweq_by_index(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t cwk, uint8_t dpm_wevew);
unsigned int dcn30_smu_get_dc_mode_max_dpm_fweq(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t cwk);
void         dcn30_smu_set_min_deep_sweep_dcef_cwk(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t fweq_mhz);
void         dcn30_smu_set_num_of_dispways(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t num_dispways);
void         dcn30_smu_set_dispway_wefwesh_fwom_maww(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe, uint8_t cache_timew_deway, uint8_t cache_timew_scawe);
void         dcn30_smu_set_extewnaw_cwient_df_cstate_awwow(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe);
void         dcn30_smu_set_pme_wowkawound(stwuct cwk_mgw_intewnaw *cwk_mgw);

#endif /* DAW_DC_DCN30_CWK_MGW_SMU_MSG_H_ */
