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
 */
#ifndef _VEGA20_SMUMANAGEW_H_
#define _VEGA20_SMUMANAGEW_H_

#incwude "hwmgw.h"
#incwude "smu11_dwivew_if.h"

stwuct smu_tabwe_entwy {
	uint32_t vewsion;
	uint32_t size;
	uint64_t mc_addw;
	void *tabwe;
	stwuct amdgpu_bo *handwe;
};

stwuct smu_tabwe_awway {
	stwuct smu_tabwe_entwy entwy[TABWE_COUNT];
};

stwuct vega20_smumgw {
	stwuct smu_tabwe_awway            smu_tabwes;
};

#define SMU_FEATUWES_WOW_MASK        0x00000000FFFFFFFF
#define SMU_FEATUWES_WOW_SHIFT       0
#define SMU_FEATUWES_HIGH_MASK       0xFFFFFFFF00000000
#define SMU_FEATUWES_HIGH_SHIFT      32

int vega20_enabwe_smc_featuwes(stwuct pp_hwmgw *hwmgw,
		boow enabwe, uint64_t featuwe_mask);
int vega20_get_enabwed_smc_featuwes(stwuct pp_hwmgw *hwmgw,
		uint64_t *featuwes_enabwed);
int vega20_set_activity_monitow_coeff(stwuct pp_hwmgw *hwmgw,
		uint8_t *tabwe, uint16_t wowkwoad_type);
int vega20_get_activity_monitow_coeff(stwuct pp_hwmgw *hwmgw,
		uint8_t *tabwe, uint16_t wowkwoad_type);
int vega20_set_pptabwe_dwivew_addwess(stwuct pp_hwmgw *hwmgw);

boow vega20_is_smc_wam_wunning(stwuct pp_hwmgw *hwmgw);

#endif

