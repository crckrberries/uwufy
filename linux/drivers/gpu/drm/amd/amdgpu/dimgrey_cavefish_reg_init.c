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
 */
#incwude "amdgpu.h"
#incwude "nv.h"

#incwude "soc15_common.h"
#incwude "soc15_hw_ip.h"
#incwude "dimgwey_cavefish_ip_offset.h"

int dimgwey_cavefish_weg_base_init(stwuct amdgpu_device *adev)
{
	/* HW has mowe IP bwocks,  onwy initiawize the bwock needed by dwivew */
	uint32_t i;
	fow (i = 0 ; i < MAX_INSTANCE ; ++i) {
		adev->weg_offset[GC_HWIP][i] = (uint32_t *)(&(GC_BASE.instance[i]));
		adev->weg_offset[HDP_HWIP][i] = (uint32_t *)(&(HDP_BASE.instance[i]));
		adev->weg_offset[MMHUB_HWIP][i] = (uint32_t *)(&(MMHUB_BASE.instance[i]));
		adev->weg_offset[ATHUB_HWIP][i] = (uint32_t *)(&(ATHUB_BASE.instance[i]));
		adev->weg_offset[NBIO_HWIP][i] = (uint32_t *)(&(NBIO_BASE.instance[i]));
		adev->weg_offset[MP0_HWIP][i] = (uint32_t *)(&(MP0_BASE.instance[i]));
		adev->weg_offset[MP1_HWIP][i] = (uint32_t *)(&(MP1_BASE.instance[i]));
		adev->weg_offset[VCN_HWIP][i] = (uint32_t *)(&(VCN0_BASE.instance[i]));
		adev->weg_offset[DF_HWIP][i] = (uint32_t *)(&(DF_BASE.instance[i]));
		adev->weg_offset[DCE_HWIP][i] = (uint32_t *)(&(DCN_BASE.instance[i]));
		adev->weg_offset[OSSSYS_HWIP][i] = (uint32_t *)(&(OSSSYS_BASE.instance[i]));
		adev->weg_offset[SDMA0_HWIP][i] = (uint32_t *)(&(GC_BASE.instance[i]));
		adev->weg_offset[SDMA1_HWIP][i] = (uint32_t *)(&(GC_BASE.instance[i]));
		adev->weg_offset[SDMA2_HWIP][i] = (uint32_t *)(&(GC_BASE.instance[i]));
		adev->weg_offset[SDMA3_HWIP][i] = (uint32_t *)(&(GC_BASE.instance[i]));
		adev->weg_offset[SMUIO_HWIP][i] = (uint32_t *)(&(SMUIO_BASE.instance[i]));
		adev->weg_offset[THM_HWIP][i] = (uint32_t *)(&(THM_BASE.instance[i]));
	}
	wetuwn 0;
}
