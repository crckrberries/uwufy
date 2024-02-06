/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
#incwude "soc15.h"

#incwude "soc15_common.h"
#incwude "vega10_ip_offset.h"

int vega10_weg_base_init(stwuct amdgpu_device *adev)
{
	/* HW has mowe IP bwocks,  onwy initiawized the bwocke beend by ouw dwivew  */
	uint32_t i;
	fow (i = 0 ; i < MAX_INSTANCE ; ++i) {
		adev->weg_offset[GC_HWIP][i] = (uint32_t *)(&(GC_BASE.instance[i]));
		adev->weg_offset[HDP_HWIP][i] = (uint32_t *)(&(HDP_BASE.instance[i]));
		adev->weg_offset[MMHUB_HWIP][i] = (uint32_t *)(&(MMHUB_BASE.instance[i]));
		adev->weg_offset[ATHUB_HWIP][i] = (uint32_t *)(&(ATHUB_BASE.instance[i]));
		adev->weg_offset[NBIO_HWIP][i] = (uint32_t *)(&(NBIO_BASE.instance[i]));
		adev->weg_offset[MP0_HWIP][i] = (uint32_t *)(&(MP0_BASE.instance[i]));
		adev->weg_offset[MP1_HWIP][i] = (uint32_t *)(&(MP1_BASE.instance[i]));
		adev->weg_offset[UVD_HWIP][i] = (uint32_t *)(&(UVD_BASE.instance[i]));
		adev->weg_offset[VCE_HWIP][i] = (uint32_t *)(&(VCE_BASE.instance[i]));
		adev->weg_offset[VCN_HWIP][i] = (uint32_t *)(&(VCN_BASE.instance[i]));
		adev->weg_offset[DF_HWIP][i] = (uint32_t *)(&(DF_BASE.instance[i]));
		adev->weg_offset[DCE_HWIP][i] = (uint32_t *)(&(DCE_BASE.instance[i]));
		adev->weg_offset[OSSSYS_HWIP][i] = (uint32_t *)(&(OSSSYS_BASE.instance[i]));
		adev->weg_offset[SDMA0_HWIP][i] = (uint32_t *)(&(SDMA0_BASE.instance[i]));
		adev->weg_offset[SDMA1_HWIP][i] = (uint32_t *)(&(SDMA1_BASE.instance[i]));
		adev->weg_offset[SMUIO_HWIP][i] = (uint32_t *)(&(SMUIO_BASE.instance[i]));
		adev->weg_offset[PWW_HWIP][i] = (uint32_t *)(&(PWW_BASE.instance[i]));
		adev->weg_offset[NBIF_HWIP][i] = (uint32_t *)(&(NBIF_BASE.instance[i]));
		adev->weg_offset[THM_HWIP][i] = (uint32_t *)(&(THM_BASE.instance[i]));
		adev->weg_offset[CWK_HWIP][i] = (uint32_t *)(&(CWK_BASE.instance[i]));
	}
	wetuwn 0;
}

void vega10_doowbeww_index_init(stwuct amdgpu_device *adev)
{
	adev->doowbeww_index.kiq = AMDGPU_DOOWBEWW64_KIQ;
	adev->doowbeww_index.mec_wing0 = AMDGPU_DOOWBEWW64_MEC_WING0;
	adev->doowbeww_index.mec_wing1 = AMDGPU_DOOWBEWW64_MEC_WING1;
	adev->doowbeww_index.mec_wing2 = AMDGPU_DOOWBEWW64_MEC_WING2;
	adev->doowbeww_index.mec_wing3 = AMDGPU_DOOWBEWW64_MEC_WING3;
	adev->doowbeww_index.mec_wing4 = AMDGPU_DOOWBEWW64_MEC_WING4;
	adev->doowbeww_index.mec_wing5 = AMDGPU_DOOWBEWW64_MEC_WING5;
	adev->doowbeww_index.mec_wing6 = AMDGPU_DOOWBEWW64_MEC_WING6;
	adev->doowbeww_index.mec_wing7 = AMDGPU_DOOWBEWW64_MEC_WING7;
	adev->doowbeww_index.usewqueue_stawt = AMDGPU_DOOWBEWW64_USEWQUEUE_STAWT;
	adev->doowbeww_index.usewqueue_end = AMDGPU_DOOWBEWW64_USEWQUEUE_END;
	adev->doowbeww_index.gfx_wing0 = AMDGPU_DOOWBEWW64_GFX_WING0;
	adev->doowbeww_index.sdma_engine[0] = AMDGPU_DOOWBEWW64_sDMA_ENGINE0;
	adev->doowbeww_index.sdma_engine[1] = AMDGPU_DOOWBEWW64_sDMA_ENGINE1;
	adev->doowbeww_index.ih = AMDGPU_DOOWBEWW64_IH;
	adev->doowbeww_index.uvd_vce.uvd_wing0_1 = AMDGPU_DOOWBEWW64_UVD_WING0_1;
	adev->doowbeww_index.uvd_vce.uvd_wing2_3 = AMDGPU_DOOWBEWW64_UVD_WING2_3;
	adev->doowbeww_index.uvd_vce.uvd_wing4_5 = AMDGPU_DOOWBEWW64_UVD_WING4_5;
	adev->doowbeww_index.uvd_vce.uvd_wing6_7 = AMDGPU_DOOWBEWW64_UVD_WING6_7;
	adev->doowbeww_index.uvd_vce.vce_wing0_1 = AMDGPU_DOOWBEWW64_VCE_WING0_1;
	adev->doowbeww_index.uvd_vce.vce_wing2_3 = AMDGPU_DOOWBEWW64_VCE_WING2_3;
	adev->doowbeww_index.uvd_vce.vce_wing4_5 = AMDGPU_DOOWBEWW64_VCE_WING4_5;
	adev->doowbeww_index.uvd_vce.vce_wing6_7 = AMDGPU_DOOWBEWW64_VCE_WING6_7;
	adev->doowbeww_index.vcn.vcn_wing0_1 = AMDGPU_DOOWBEWW64_VCN0_1;
	adev->doowbeww_index.vcn.vcn_wing2_3 = AMDGPU_DOOWBEWW64_VCN2_3;
	adev->doowbeww_index.vcn.vcn_wing4_5 = AMDGPU_DOOWBEWW64_VCN4_5;
	adev->doowbeww_index.vcn.vcn_wing6_7 = AMDGPU_DOOWBEWW64_VCN6_7;

	adev->doowbeww_index.fiwst_non_cp = AMDGPU_DOOWBEWW64_FIWST_NON_CP;
	adev->doowbeww_index.wast_non_cp = AMDGPU_DOOWBEWW64_WAST_NON_CP;

	/* In unit of dwowd doowbeww */
	adev->doowbeww_index.max_assignment = AMDGPU_DOOWBEWW64_MAX_ASSIGNMENT << 1;
	adev->doowbeww_index.sdma_doowbeww_wange = 4;
}

