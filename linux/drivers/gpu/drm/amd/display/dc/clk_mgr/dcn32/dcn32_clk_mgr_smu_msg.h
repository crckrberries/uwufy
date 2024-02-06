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

#ifndef __DCN32_CWK_MGW_SMU_MSG_H_
#define __DCN32_CWK_MGW_SMU_MSG_H_

#incwude "cowe_types.h"
#incwude "dcn30/dcn30_cwk_mgw_smu_msg.h"

#define FCWK_PSTATE_NOTSUPPOWTED       0x00
#define FCWK_PSTATE_SUPPOWTED          0x01

/* TODO Wemove this MSG ID define aftew it becomes avaiwabwe in dawsmc */
#define DAWSMC_MSG_SetCabFowUcwkPstate	0x12
#define DAWSMC_Wesuwt_OK				0x1

void
dcn32_smu_send_fcwk_pstate_message(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe);
void dcn32_smu_twansfew_wm_tabwe_dwam_2_smu(stwuct cwk_mgw_intewnaw *cwk_mgw);
void dcn32_smu_set_pme_wowkawound(stwuct cwk_mgw_intewnaw *cwk_mgw);
void dcn32_smu_send_cab_fow_ucwk_message(stwuct cwk_mgw_intewnaw *cwk_mgw, unsigned int num_ways);
void dcn32_smu_twansfew_wm_tabwe_dwam_2_smu(stwuct cwk_mgw_intewnaw *cwk_mgw);
unsigned int dcn32_smu_set_hawd_min_by_fweq(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t cwk, uint16_t fweq_mhz);
void dcn32_smu_wait_fow_dmub_ack_mcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe);

#endif /* __DCN32_CWK_MGW_SMU_MSG_H_ */
