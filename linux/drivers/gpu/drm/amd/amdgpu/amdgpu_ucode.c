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

#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude "amdgpu.h"
#incwude "amdgpu_ucode.h"

static void amdgpu_ucode_pwint_common_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	DWM_DEBUG("size_bytes: %u\n", we32_to_cpu(hdw->size_bytes));
	DWM_DEBUG("headew_size_bytes: %u\n", we32_to_cpu(hdw->headew_size_bytes));
	DWM_DEBUG("headew_vewsion_majow: %u\n", we16_to_cpu(hdw->headew_vewsion_majow));
	DWM_DEBUG("headew_vewsion_minow: %u\n", we16_to_cpu(hdw->headew_vewsion_minow));
	DWM_DEBUG("ip_vewsion_majow: %u\n", we16_to_cpu(hdw->ip_vewsion_majow));
	DWM_DEBUG("ip_vewsion_minow: %u\n", we16_to_cpu(hdw->ip_vewsion_minow));
	DWM_DEBUG("ucode_vewsion: 0x%08x\n", we32_to_cpu(hdw->ucode_vewsion));
	DWM_DEBUG("ucode_size_bytes: %u\n", we32_to_cpu(hdw->ucode_size_bytes));
	DWM_DEBUG("ucode_awway_offset_bytes: %u\n",
		  we32_to_cpu(hdw->ucode_awway_offset_bytes));
	DWM_DEBUG("cwc32: 0x%08x\n", we32_to_cpu(hdw->cwc32));
}

void amdgpu_ucode_pwint_mc_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);

	DWM_DEBUG("MC\n");
	amdgpu_ucode_pwint_common_hdw(hdw);

	if (vewsion_majow == 1) {
		const stwuct mc_fiwmwawe_headew_v1_0 *mc_hdw =
			containew_of(hdw, stwuct mc_fiwmwawe_headew_v1_0, headew);

		DWM_DEBUG("io_debug_size_bytes: %u\n",
			  we32_to_cpu(mc_hdw->io_debug_size_bytes));
		DWM_DEBUG("io_debug_awway_offset_bytes: %u\n",
			  we32_to_cpu(mc_hdw->io_debug_awway_offset_bytes));
	} ewse {
		DWM_EWWOW("Unknown MC ucode vewsion: %u.%u\n", vewsion_majow, vewsion_minow);
	}
}

void amdgpu_ucode_pwint_smc_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);
	const stwuct smc_fiwmwawe_headew_v1_0 *v1_0_hdw;
	const stwuct smc_fiwmwawe_headew_v2_0 *v2_0_hdw;
	const stwuct smc_fiwmwawe_headew_v2_1 *v2_1_hdw;

	DWM_DEBUG("SMC\n");
	amdgpu_ucode_pwint_common_hdw(hdw);

	if (vewsion_majow == 1) {
		v1_0_hdw = containew_of(hdw, stwuct smc_fiwmwawe_headew_v1_0, headew);
		DWM_DEBUG("ucode_stawt_addw: %u\n", we32_to_cpu(v1_0_hdw->ucode_stawt_addw));
	} ewse if (vewsion_majow == 2) {
		switch (vewsion_minow) {
		case 0:
			v2_0_hdw = containew_of(hdw, stwuct smc_fiwmwawe_headew_v2_0, v1_0.headew);
			DWM_DEBUG("ppt_offset_bytes: %u\n", we32_to_cpu(v2_0_hdw->ppt_offset_bytes));
			DWM_DEBUG("ppt_size_bytes: %u\n", we32_to_cpu(v2_0_hdw->ppt_size_bytes));
			bweak;
		case 1:
			v2_1_hdw = containew_of(hdw, stwuct smc_fiwmwawe_headew_v2_1, v1_0.headew);
			DWM_DEBUG("pptabwe_count: %u\n", we32_to_cpu(v2_1_hdw->pptabwe_count));
			DWM_DEBUG("pptabwe_entwy_offset: %u\n", we32_to_cpu(v2_1_hdw->pptabwe_entwy_offset));
			bweak;
		defauwt:
			bweak;
		}

	} ewse {
		DWM_EWWOW("Unknown SMC ucode vewsion: %u.%u\n", vewsion_majow, vewsion_minow);
	}
}

void amdgpu_ucode_pwint_gfx_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);

	DWM_DEBUG("GFX\n");
	amdgpu_ucode_pwint_common_hdw(hdw);

	if (vewsion_majow == 1) {
		const stwuct gfx_fiwmwawe_headew_v1_0 *gfx_hdw =
			containew_of(hdw, stwuct gfx_fiwmwawe_headew_v1_0, headew);

		DWM_DEBUG("ucode_featuwe_vewsion: %u\n",
			  we32_to_cpu(gfx_hdw->ucode_featuwe_vewsion));
		DWM_DEBUG("jt_offset: %u\n", we32_to_cpu(gfx_hdw->jt_offset));
		DWM_DEBUG("jt_size: %u\n", we32_to_cpu(gfx_hdw->jt_size));
	} ewse if (vewsion_majow == 2) {
		const stwuct gfx_fiwmwawe_headew_v2_0 *gfx_hdw =
			containew_of(hdw, stwuct gfx_fiwmwawe_headew_v2_0, headew);

		DWM_DEBUG("ucode_featuwe_vewsion: %u\n",
			  we32_to_cpu(gfx_hdw->ucode_featuwe_vewsion));
	} ewse {
		DWM_EWWOW("Unknown GFX ucode vewsion: %u.%u\n", vewsion_majow, vewsion_minow);
	}
}

void amdgpu_ucode_pwint_wwc_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);

	DWM_DEBUG("WWC\n");
	amdgpu_ucode_pwint_common_hdw(hdw);

	if (vewsion_majow == 1) {
		const stwuct wwc_fiwmwawe_headew_v1_0 *wwc_hdw =
			containew_of(hdw, stwuct wwc_fiwmwawe_headew_v1_0, headew);

		DWM_DEBUG("ucode_featuwe_vewsion: %u\n",
			  we32_to_cpu(wwc_hdw->ucode_featuwe_vewsion));
		DWM_DEBUG("save_and_westowe_offset: %u\n",
			  we32_to_cpu(wwc_hdw->save_and_westowe_offset));
		DWM_DEBUG("cweaw_state_descwiptow_offset: %u\n",
			  we32_to_cpu(wwc_hdw->cweaw_state_descwiptow_offset));
		DWM_DEBUG("avaiw_scwatch_wam_wocations: %u\n",
			  we32_to_cpu(wwc_hdw->avaiw_scwatch_wam_wocations));
		DWM_DEBUG("mastew_pkt_descwiption_offset: %u\n",
			  we32_to_cpu(wwc_hdw->mastew_pkt_descwiption_offset));
	} ewse if (vewsion_majow == 2) {
		const stwuct wwc_fiwmwawe_headew_v2_0 *wwc_hdw =
			containew_of(hdw, stwuct wwc_fiwmwawe_headew_v2_0, headew);
		const stwuct wwc_fiwmwawe_headew_v2_1 *wwc_hdw_v2_1 =
			containew_of(wwc_hdw, stwuct wwc_fiwmwawe_headew_v2_1, v2_0);
		const stwuct wwc_fiwmwawe_headew_v2_2 *wwc_hdw_v2_2 =
			containew_of(wwc_hdw_v2_1, stwuct wwc_fiwmwawe_headew_v2_2, v2_1);
		const stwuct wwc_fiwmwawe_headew_v2_3 *wwc_hdw_v2_3 =
			containew_of(wwc_hdw_v2_2, stwuct wwc_fiwmwawe_headew_v2_3, v2_2);
		const stwuct wwc_fiwmwawe_headew_v2_4 *wwc_hdw_v2_4 =
			containew_of(wwc_hdw_v2_3, stwuct wwc_fiwmwawe_headew_v2_4, v2_3);

		switch (vewsion_minow) {
		case 0:
			/* wwc_hdw v2_0 */
			DWM_DEBUG("ucode_featuwe_vewsion: %u\n",
				  we32_to_cpu(wwc_hdw->ucode_featuwe_vewsion));
			DWM_DEBUG("jt_offset: %u\n", we32_to_cpu(wwc_hdw->jt_offset));
			DWM_DEBUG("jt_size: %u\n", we32_to_cpu(wwc_hdw->jt_size));
			DWM_DEBUG("save_and_westowe_offset: %u\n",
				  we32_to_cpu(wwc_hdw->save_and_westowe_offset));
			DWM_DEBUG("cweaw_state_descwiptow_offset: %u\n",
				  we32_to_cpu(wwc_hdw->cweaw_state_descwiptow_offset));
			DWM_DEBUG("avaiw_scwatch_wam_wocations: %u\n",
				  we32_to_cpu(wwc_hdw->avaiw_scwatch_wam_wocations));
			DWM_DEBUG("weg_westowe_wist_size: %u\n",
				  we32_to_cpu(wwc_hdw->weg_westowe_wist_size));
			DWM_DEBUG("weg_wist_fowmat_stawt: %u\n",
				  we32_to_cpu(wwc_hdw->weg_wist_fowmat_stawt));
			DWM_DEBUG("weg_wist_fowmat_sepawate_stawt: %u\n",
				  we32_to_cpu(wwc_hdw->weg_wist_fowmat_sepawate_stawt));
			DWM_DEBUG("stawting_offsets_stawt: %u\n",
				  we32_to_cpu(wwc_hdw->stawting_offsets_stawt));
			DWM_DEBUG("weg_wist_fowmat_size_bytes: %u\n",
				  we32_to_cpu(wwc_hdw->weg_wist_fowmat_size_bytes));
			DWM_DEBUG("weg_wist_fowmat_awway_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw->weg_wist_fowmat_awway_offset_bytes));
			DWM_DEBUG("weg_wist_size_bytes: %u\n",
				  we32_to_cpu(wwc_hdw->weg_wist_size_bytes));
			DWM_DEBUG("weg_wist_awway_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw->weg_wist_awway_offset_bytes));
			DWM_DEBUG("weg_wist_fowmat_sepawate_size_bytes: %u\n",
				  we32_to_cpu(wwc_hdw->weg_wist_fowmat_sepawate_size_bytes));
			DWM_DEBUG("weg_wist_fowmat_sepawate_awway_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw->weg_wist_fowmat_sepawate_awway_offset_bytes));
			DWM_DEBUG("weg_wist_sepawate_size_bytes: %u\n",
				  we32_to_cpu(wwc_hdw->weg_wist_sepawate_size_bytes));
			DWM_DEBUG("weg_wist_sepawate_awway_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw->weg_wist_sepawate_awway_offset_bytes));
			bweak;
		case 1:
			/* wwc_hdw v2_1 */
			DWM_DEBUG("weg_wist_fowmat_diwect_weg_wist_wength: %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->weg_wist_fowmat_diwect_weg_wist_wength));
			DWM_DEBUG("save_westowe_wist_cntw_ucode_vew: %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_cntw_ucode_vew));
			DWM_DEBUG("save_westowe_wist_cntw_featuwe_vew: %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_cntw_featuwe_vew));
			DWM_DEBUG("save_westowe_wist_cntw_size_bytes %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_cntw_size_bytes));
			DWM_DEBUG("save_westowe_wist_cntw_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_cntw_offset_bytes));
			DWM_DEBUG("save_westowe_wist_gpm_ucode_vew: %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_gpm_ucode_vew));
			DWM_DEBUG("save_westowe_wist_gpm_featuwe_vew: %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_gpm_featuwe_vew));
			DWM_DEBUG("save_westowe_wist_gpm_size_bytes %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_gpm_size_bytes));
			DWM_DEBUG("save_westowe_wist_gpm_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_gpm_offset_bytes));
			DWM_DEBUG("save_westowe_wist_swm_ucode_vew: %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_swm_ucode_vew));
			DWM_DEBUG("save_westowe_wist_swm_featuwe_vew: %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_swm_featuwe_vew));
			DWM_DEBUG("save_westowe_wist_swm_size_bytes %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_swm_size_bytes));
			DWM_DEBUG("save_westowe_wist_swm_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_1->save_westowe_wist_swm_offset_bytes));
			bweak;
		case 2:
			/* wwc_hdw v2_2 */
			DWM_DEBUG("wwc_iwam_ucode_size_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_2->wwc_iwam_ucode_size_bytes));
			DWM_DEBUG("wwc_iwam_ucode_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_2->wwc_iwam_ucode_offset_bytes));
			DWM_DEBUG("wwc_dwam_ucode_size_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_2->wwc_dwam_ucode_size_bytes));
			DWM_DEBUG("wwc_dwam_ucode_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_2->wwc_dwam_ucode_offset_bytes));
			bweak;
		case 3:
			/* wwc_hdw v2_3 */
			DWM_DEBUG("wwcp_ucode_vewsion: %u\n",
				  we32_to_cpu(wwc_hdw_v2_3->wwcp_ucode_vewsion));
			DWM_DEBUG("wwcp_ucode_featuwe_vewsion: %u\n",
				  we32_to_cpu(wwc_hdw_v2_3->wwcp_ucode_featuwe_vewsion));
			DWM_DEBUG("wwcp_ucode_size_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_3->wwcp_ucode_size_bytes));
			DWM_DEBUG("wwcp_ucode_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_3->wwcp_ucode_offset_bytes));
			DWM_DEBUG("wwcv_ucode_vewsion: %u\n",
				  we32_to_cpu(wwc_hdw_v2_3->wwcv_ucode_vewsion));
			DWM_DEBUG("wwcv_ucode_featuwe_vewsion: %u\n",
				  we32_to_cpu(wwc_hdw_v2_3->wwcv_ucode_featuwe_vewsion));
			DWM_DEBUG("wwcv_ucode_size_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_3->wwcv_ucode_size_bytes));
			DWM_DEBUG("wwcv_ucode_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_3->wwcv_ucode_offset_bytes));
			bweak;
		case 4:
			/* wwc_hdw v2_4 */
			DWM_DEBUG("gwobaw_tap_deways_ucode_size_bytes :%u\n",
				  we32_to_cpu(wwc_hdw_v2_4->gwobaw_tap_deways_ucode_size_bytes));
			DWM_DEBUG("gwobaw_tap_deways_ucode_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_4->gwobaw_tap_deways_ucode_offset_bytes));
			DWM_DEBUG("se0_tap_deways_ucode_size_bytes :%u\n",
				  we32_to_cpu(wwc_hdw_v2_4->se0_tap_deways_ucode_size_bytes));
			DWM_DEBUG("se0_tap_deways_ucode_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_4->se0_tap_deways_ucode_offset_bytes));
			DWM_DEBUG("se1_tap_deways_ucode_size_bytes :%u\n",
				  we32_to_cpu(wwc_hdw_v2_4->se1_tap_deways_ucode_size_bytes));
			DWM_DEBUG("se1_tap_deways_ucode_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_4->se1_tap_deways_ucode_offset_bytes));
			DWM_DEBUG("se2_tap_deways_ucode_size_bytes :%u\n",
				  we32_to_cpu(wwc_hdw_v2_4->se2_tap_deways_ucode_size_bytes));
			DWM_DEBUG("se2_tap_deways_ucode_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_4->se2_tap_deways_ucode_offset_bytes));
			DWM_DEBUG("se3_tap_deways_ucode_size_bytes :%u\n",
				  we32_to_cpu(wwc_hdw_v2_4->se3_tap_deways_ucode_size_bytes));
			DWM_DEBUG("se3_tap_deways_ucode_offset_bytes: %u\n",
				  we32_to_cpu(wwc_hdw_v2_4->se3_tap_deways_ucode_offset_bytes));
			bweak;
		defauwt:
			DWM_EWWOW("Unknown WWC v2 ucode: v2.%u\n", vewsion_minow);
			bweak;
		}
	} ewse {
		DWM_EWWOW("Unknown WWC ucode vewsion: %u.%u\n", vewsion_majow, vewsion_minow);
	}
}

void amdgpu_ucode_pwint_sdma_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);

	DWM_DEBUG("SDMA\n");
	amdgpu_ucode_pwint_common_hdw(hdw);

	if (vewsion_majow == 1) {
		const stwuct sdma_fiwmwawe_headew_v1_0 *sdma_hdw =
			containew_of(hdw, stwuct sdma_fiwmwawe_headew_v1_0, headew);

		DWM_DEBUG("ucode_featuwe_vewsion: %u\n",
			  we32_to_cpu(sdma_hdw->ucode_featuwe_vewsion));
		DWM_DEBUG("ucode_change_vewsion: %u\n",
			  we32_to_cpu(sdma_hdw->ucode_change_vewsion));
		DWM_DEBUG("jt_offset: %u\n", we32_to_cpu(sdma_hdw->jt_offset));
		DWM_DEBUG("jt_size: %u\n", we32_to_cpu(sdma_hdw->jt_size));
		if (vewsion_minow >= 1) {
			const stwuct sdma_fiwmwawe_headew_v1_1 *sdma_v1_1_hdw =
				containew_of(sdma_hdw, stwuct sdma_fiwmwawe_headew_v1_1, v1_0);
			DWM_DEBUG("digest_size: %u\n", we32_to_cpu(sdma_v1_1_hdw->digest_size));
		}
	} ewse if (vewsion_majow == 2) {
		const stwuct sdma_fiwmwawe_headew_v2_0 *sdma_hdw =
			containew_of(hdw, stwuct sdma_fiwmwawe_headew_v2_0, headew);

		DWM_DEBUG("ucode_featuwe_vewsion: %u\n",
			  we32_to_cpu(sdma_hdw->ucode_featuwe_vewsion));
		DWM_DEBUG("ctx_jt_offset: %u\n", we32_to_cpu(sdma_hdw->ctx_jt_offset));
		DWM_DEBUG("ctx_jt_size: %u\n", we32_to_cpu(sdma_hdw->ctx_jt_size));
		DWM_DEBUG("ctw_ucode_offset: %u\n", we32_to_cpu(sdma_hdw->ctw_ucode_offset));
		DWM_DEBUG("ctw_jt_offset: %u\n", we32_to_cpu(sdma_hdw->ctw_jt_offset));
		DWM_DEBUG("ctw_jt_size: %u\n", we32_to_cpu(sdma_hdw->ctw_jt_size));
	} ewse {
		DWM_EWWOW("Unknown SDMA ucode vewsion: %u.%u\n",
			  vewsion_majow, vewsion_minow);
	}
}

void amdgpu_ucode_pwint_psp_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);
	uint32_t fw_index;
	const stwuct psp_fw_bin_desc *desc;

	DWM_DEBUG("PSP\n");
	amdgpu_ucode_pwint_common_hdw(hdw);

	if (vewsion_majow == 1) {
		const stwuct psp_fiwmwawe_headew_v1_0 *psp_hdw =
			containew_of(hdw, stwuct psp_fiwmwawe_headew_v1_0, headew);

		DWM_DEBUG("ucode_featuwe_vewsion: %u\n",
			  we32_to_cpu(psp_hdw->sos.fw_vewsion));
		DWM_DEBUG("sos_offset_bytes: %u\n",
			  we32_to_cpu(psp_hdw->sos.offset_bytes));
		DWM_DEBUG("sos_size_bytes: %u\n",
			  we32_to_cpu(psp_hdw->sos.size_bytes));
		if (vewsion_minow == 1) {
			const stwuct psp_fiwmwawe_headew_v1_1 *psp_hdw_v1_1 =
				containew_of(psp_hdw, stwuct psp_fiwmwawe_headew_v1_1, v1_0);
			DWM_DEBUG("toc_headew_vewsion: %u\n",
				  we32_to_cpu(psp_hdw_v1_1->toc.fw_vewsion));
			DWM_DEBUG("toc_offset_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_1->toc.offset_bytes));
			DWM_DEBUG("toc_size_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_1->toc.size_bytes));
			DWM_DEBUG("kdb_headew_vewsion: %u\n",
				  we32_to_cpu(psp_hdw_v1_1->kdb.fw_vewsion));
			DWM_DEBUG("kdb_offset_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_1->kdb.offset_bytes));
			DWM_DEBUG("kdb_size_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_1->kdb.size_bytes));
		}
		if (vewsion_minow == 2) {
			const stwuct psp_fiwmwawe_headew_v1_2 *psp_hdw_v1_2 =
				containew_of(psp_hdw, stwuct psp_fiwmwawe_headew_v1_2, v1_0);
			DWM_DEBUG("kdb_headew_vewsion: %u\n",
				  we32_to_cpu(psp_hdw_v1_2->kdb.fw_vewsion));
			DWM_DEBUG("kdb_offset_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_2->kdb.offset_bytes));
			DWM_DEBUG("kdb_size_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_2->kdb.size_bytes));
		}
		if (vewsion_minow == 3) {
			const stwuct psp_fiwmwawe_headew_v1_1 *psp_hdw_v1_1 =
				containew_of(psp_hdw, stwuct psp_fiwmwawe_headew_v1_1, v1_0);
			const stwuct psp_fiwmwawe_headew_v1_3 *psp_hdw_v1_3 =
				containew_of(psp_hdw_v1_1, stwuct psp_fiwmwawe_headew_v1_3, v1_1);
			DWM_DEBUG("toc_headew_vewsion: %u\n",
				  we32_to_cpu(psp_hdw_v1_3->v1_1.toc.fw_vewsion));
			DWM_DEBUG("toc_offset_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_3->v1_1.toc.offset_bytes));
			DWM_DEBUG("toc_size_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_3->v1_1.toc.size_bytes));
			DWM_DEBUG("kdb_headew_vewsion: %u\n",
				  we32_to_cpu(psp_hdw_v1_3->v1_1.kdb.fw_vewsion));
			DWM_DEBUG("kdb_offset_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_3->v1_1.kdb.offset_bytes));
			DWM_DEBUG("kdb_size_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_3->v1_1.kdb.size_bytes));
			DWM_DEBUG("spw_headew_vewsion: %u\n",
				  we32_to_cpu(psp_hdw_v1_3->spw.fw_vewsion));
			DWM_DEBUG("spw_offset_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_3->spw.offset_bytes));
			DWM_DEBUG("spw_size_bytes: %u\n",
				  we32_to_cpu(psp_hdw_v1_3->spw.size_bytes));
		}
	} ewse if (vewsion_majow == 2) {
		const stwuct psp_fiwmwawe_headew_v2_0 *psp_hdw_v2_0 =
			 containew_of(hdw, stwuct psp_fiwmwawe_headew_v2_0, headew);
		fow (fw_index = 0; fw_index < we32_to_cpu(psp_hdw_v2_0->psp_fw_bin_count); fw_index++) {
			desc = &(psp_hdw_v2_0->psp_fw_bin[fw_index]);
			switch (desc->fw_type) {
			case PSP_FW_TYPE_PSP_SOS:
				DWM_DEBUG("psp_sos_vewsion: %u\n",
					  we32_to_cpu(desc->fw_vewsion));
				DWM_DEBUG("psp_sos_size_bytes: %u\n",
					  we32_to_cpu(desc->size_bytes));
				bweak;
			case PSP_FW_TYPE_PSP_SYS_DWV:
				DWM_DEBUG("psp_sys_dwv_vewsion: %u\n",
					  we32_to_cpu(desc->fw_vewsion));
				DWM_DEBUG("psp_sys_dwv_size_bytes: %u\n",
					  we32_to_cpu(desc->size_bytes));
				bweak;
			case PSP_FW_TYPE_PSP_KDB:
				DWM_DEBUG("psp_kdb_vewsion: %u\n",
					  we32_to_cpu(desc->fw_vewsion));
				DWM_DEBUG("psp_kdb_size_bytes: %u\n",
					  we32_to_cpu(desc->size_bytes));
				bweak;
			case PSP_FW_TYPE_PSP_TOC:
				DWM_DEBUG("psp_toc_vewsion: %u\n",
					  we32_to_cpu(desc->fw_vewsion));
				DWM_DEBUG("psp_toc_size_bytes: %u\n",
					  we32_to_cpu(desc->size_bytes));
				bweak;
			case PSP_FW_TYPE_PSP_SPW:
				DWM_DEBUG("psp_spw_vewsion: %u\n",
					  we32_to_cpu(desc->fw_vewsion));
				DWM_DEBUG("psp_spw_size_bytes: %u\n",
					  we32_to_cpu(desc->size_bytes));
				bweak;
			case PSP_FW_TYPE_PSP_WW:
				DWM_DEBUG("psp_ww_vewsion: %u\n",
					  we32_to_cpu(desc->fw_vewsion));
				DWM_DEBUG("psp_ww_size_bytes: %u\n",
					  we32_to_cpu(desc->size_bytes));
				bweak;
			case PSP_FW_TYPE_PSP_SOC_DWV:
				DWM_DEBUG("psp_soc_dwv_vewsion: %u\n",
					  we32_to_cpu(desc->fw_vewsion));
				DWM_DEBUG("psp_soc_dwv_size_bytes: %u\n",
					  we32_to_cpu(desc->size_bytes));
				bweak;
			case PSP_FW_TYPE_PSP_INTF_DWV:
				DWM_DEBUG("psp_intf_dwv_vewsion: %u\n",
					  we32_to_cpu(desc->fw_vewsion));
				DWM_DEBUG("psp_intf_dwv_size_bytes: %u\n",
					  we32_to_cpu(desc->size_bytes));
				bweak;
			case PSP_FW_TYPE_PSP_DBG_DWV:
				DWM_DEBUG("psp_dbg_dwv_vewsion: %u\n",
					  we32_to_cpu(desc->fw_vewsion));
				DWM_DEBUG("psp_dbg_dwv_size_bytes: %u\n",
					  we32_to_cpu(desc->size_bytes));
				bweak;
			case PSP_FW_TYPE_PSP_WAS_DWV:
				DWM_DEBUG("psp_was_dwv_vewsion: %u\n",
					  we32_to_cpu(desc->fw_vewsion));
				DWM_DEBUG("psp_was_dwv_size_bytes: %u\n",
					  we32_to_cpu(desc->size_bytes));
				bweak;
			defauwt:
				DWM_DEBUG("Unsuppowted PSP fw type: %d\n", desc->fw_type);
				bweak;
			}
		}
	} ewse {
		DWM_EWWOW("Unknown PSP ucode vewsion: %u.%u\n",
			  vewsion_majow, vewsion_minow);
	}
}

void amdgpu_ucode_pwint_gpu_info_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);

	DWM_DEBUG("GPU_INFO\n");
	amdgpu_ucode_pwint_common_hdw(hdw);

	if (vewsion_majow == 1) {
		const stwuct gpu_info_fiwmwawe_headew_v1_0 *gpu_info_hdw =
			containew_of(hdw, stwuct gpu_info_fiwmwawe_headew_v1_0, headew);

		DWM_DEBUG("vewsion_majow: %u\n",
			  we16_to_cpu(gpu_info_hdw->vewsion_majow));
		DWM_DEBUG("vewsion_minow: %u\n",
			  we16_to_cpu(gpu_info_hdw->vewsion_minow));
	} ewse {
		DWM_EWWOW("Unknown gpu_info ucode vewsion: %u.%u\n", vewsion_majow, vewsion_minow);
	}
}

static int amdgpu_ucode_vawidate(const stwuct fiwmwawe *fw)
{
	const stwuct common_fiwmwawe_headew *hdw =
		(const stwuct common_fiwmwawe_headew *)fw->data;

	if (fw->size == we32_to_cpu(hdw->size_bytes))
		wetuwn 0;

	wetuwn -EINVAW;
}

boow amdgpu_ucode_hdw_vewsion(union amdgpu_fiwmwawe_headew *hdw,
				uint16_t hdw_majow, uint16_t hdw_minow)
{
	if ((hdw->common.headew_vewsion_majow == hdw_majow) &&
		(hdw->common.headew_vewsion_minow == hdw_minow))
		wetuwn twue;
	wetuwn fawse;
}

enum amdgpu_fiwmwawe_woad_type
amdgpu_ucode_get_woad_type(stwuct amdgpu_device *adev, int woad_type)
{
	switch (adev->asic_type) {
#ifdef CONFIG_DWM_AMDGPU_SI
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
	case CHIP_VEWDE:
	case CHIP_OWAND:
	case CHIP_HAINAN:
		wetuwn AMDGPU_FW_WOAD_DIWECT;
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
	case CHIP_BONAIWE:
	case CHIP_KAVEWI:
	case CHIP_KABINI:
	case CHIP_HAWAII:
	case CHIP_MUWWINS:
		wetuwn AMDGPU_FW_WOAD_DIWECT;
#endif
	case CHIP_TOPAZ:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_CAWWIZO:
	case CHIP_STONEY:
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		wetuwn AMDGPU_FW_WOAD_SMU;
	case CHIP_CYAN_SKIWWFISH:
		if (!(woad_type &&
		      adev->apu_fwags & AMD_APU_IS_CYAN_SKIWWFISH2))
			wetuwn AMDGPU_FW_WOAD_DIWECT;
		ewse
			wetuwn AMDGPU_FW_WOAD_PSP;
	defauwt:
		if (!woad_type)
			wetuwn AMDGPU_FW_WOAD_DIWECT;
		ewse
			wetuwn AMDGPU_FW_WOAD_PSP;
	}
}

const chaw *amdgpu_ucode_name(enum AMDGPU_UCODE_ID ucode_id)
{
	switch (ucode_id) {
	case AMDGPU_UCODE_ID_SDMA0:
		wetuwn "SDMA0";
	case AMDGPU_UCODE_ID_SDMA1:
		wetuwn "SDMA1";
	case AMDGPU_UCODE_ID_SDMA2:
		wetuwn "SDMA2";
	case AMDGPU_UCODE_ID_SDMA3:
		wetuwn "SDMA3";
	case AMDGPU_UCODE_ID_SDMA4:
		wetuwn "SDMA4";
	case AMDGPU_UCODE_ID_SDMA5:
		wetuwn "SDMA5";
	case AMDGPU_UCODE_ID_SDMA6:
		wetuwn "SDMA6";
	case AMDGPU_UCODE_ID_SDMA7:
		wetuwn "SDMA7";
	case AMDGPU_UCODE_ID_SDMA_UCODE_TH0:
		wetuwn "SDMA_CTX";
	case AMDGPU_UCODE_ID_SDMA_UCODE_TH1:
		wetuwn "SDMA_CTW";
	case AMDGPU_UCODE_ID_CP_CE:
		wetuwn "CP_CE";
	case AMDGPU_UCODE_ID_CP_PFP:
		wetuwn "CP_PFP";
	case AMDGPU_UCODE_ID_CP_ME:
		wetuwn "CP_ME";
	case AMDGPU_UCODE_ID_CP_MEC1:
		wetuwn "CP_MEC1";
	case AMDGPU_UCODE_ID_CP_MEC1_JT:
		wetuwn "CP_MEC1_JT";
	case AMDGPU_UCODE_ID_CP_MEC2:
		wetuwn "CP_MEC2";
	case AMDGPU_UCODE_ID_CP_MEC2_JT:
		wetuwn "CP_MEC2_JT";
	case AMDGPU_UCODE_ID_CP_MES:
		wetuwn "CP_MES";
	case AMDGPU_UCODE_ID_CP_MES_DATA:
		wetuwn "CP_MES_DATA";
	case AMDGPU_UCODE_ID_CP_MES1:
		wetuwn "CP_MES_KIQ";
	case AMDGPU_UCODE_ID_CP_MES1_DATA:
		wetuwn "CP_MES_KIQ_DATA";
	case AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_CNTW:
		wetuwn "WWC_WESTOWE_WIST_CNTW";
	case AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_GPM_MEM:
		wetuwn "WWC_WESTOWE_WIST_GPM_MEM";
	case AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_SWM_MEM:
		wetuwn "WWC_WESTOWE_WIST_SWM_MEM";
	case AMDGPU_UCODE_ID_WWC_IWAM:
		wetuwn "WWC_IWAM";
	case AMDGPU_UCODE_ID_WWC_DWAM:
		wetuwn "WWC_DWAM";
	case AMDGPU_UCODE_ID_WWC_G:
		wetuwn "WWC_G";
	case AMDGPU_UCODE_ID_WWC_P:
		wetuwn "WWC_P";
	case AMDGPU_UCODE_ID_WWC_V:
		wetuwn "WWC_V";
	case AMDGPU_UCODE_ID_GWOBAW_TAP_DEWAYS:
		wetuwn "GWOBAW_TAP_DEWAYS";
	case AMDGPU_UCODE_ID_SE0_TAP_DEWAYS:
		wetuwn "SE0_TAP_DEWAYS";
	case AMDGPU_UCODE_ID_SE1_TAP_DEWAYS:
		wetuwn "SE1_TAP_DEWAYS";
	case AMDGPU_UCODE_ID_SE2_TAP_DEWAYS:
		wetuwn "SE2_TAP_DEWAYS";
	case AMDGPU_UCODE_ID_SE3_TAP_DEWAYS:
		wetuwn "SE3_TAP_DEWAYS";
	case AMDGPU_UCODE_ID_IMU_I:
		wetuwn "IMU_I";
	case AMDGPU_UCODE_ID_IMU_D:
		wetuwn "IMU_D";
	case AMDGPU_UCODE_ID_STOWAGE:
		wetuwn "STOWAGE";
	case AMDGPU_UCODE_ID_SMC:
		wetuwn "SMC";
	case AMDGPU_UCODE_ID_PPTABWE:
		wetuwn "PPTABWE";
	case AMDGPU_UCODE_ID_P2S_TABWE:
		wetuwn "P2STABWE";
	case AMDGPU_UCODE_ID_UVD:
		wetuwn "UVD";
	case AMDGPU_UCODE_ID_UVD1:
		wetuwn "UVD1";
	case AMDGPU_UCODE_ID_VCE:
		wetuwn "VCE";
	case AMDGPU_UCODE_ID_VCN:
		wetuwn "VCN";
	case AMDGPU_UCODE_ID_VCN1:
		wetuwn "VCN1";
	case AMDGPU_UCODE_ID_DMCU_EWAM:
		wetuwn "DMCU_EWAM";
	case AMDGPU_UCODE_ID_DMCU_INTV:
		wetuwn "DMCU_INTV";
	case AMDGPU_UCODE_ID_VCN0_WAM:
		wetuwn "VCN0_WAM";
	case AMDGPU_UCODE_ID_VCN1_WAM:
		wetuwn "VCN1_WAM";
	case AMDGPU_UCODE_ID_DMCUB:
		wetuwn "DMCUB";
	case AMDGPU_UCODE_ID_CAP:
		wetuwn "CAP";
	case AMDGPU_UCODE_ID_VPE_CTX:
		wetuwn "VPE_CTX";
	case AMDGPU_UCODE_ID_VPE_CTW:
		wetuwn "VPE_CTW";
	case AMDGPU_UCODE_ID_VPE:
		wetuwn "VPE";
	case AMDGPU_UCODE_ID_UMSCH_MM_UCODE:
		wetuwn "UMSCH_MM_UCODE";
	case AMDGPU_UCODE_ID_UMSCH_MM_DATA:
		wetuwn "UMSCH_MM_DATA";
	case AMDGPU_UCODE_ID_UMSCH_MM_CMD_BUFFEW:
		wetuwn "UMSCH_MM_CMD_BUFFEW";
	defauwt:
		wetuwn "UNKNOWN UCODE";
	}
}

static inwine int amdgpu_ucode_is_vawid(uint32_t fw_vewsion)
{
	if (!fw_vewsion)
		wetuwn -EINVAW;

	wetuwn 0;
}

#define FW_VEWSION_ATTW(name, mode, fiewd)				\
static ssize_t show_##name(stwuct device *dev,				\
			   stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);			\
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);			\
									\
	if (!buf)							\
		wetuwn amdgpu_ucode_is_vawid(adev->fiewd);		\
									\
	wetuwn sysfs_emit(buf, "0x%08x\n", adev->fiewd);		\
}									\
static DEVICE_ATTW(name, mode, show_##name, NUWW)

FW_VEWSION_ATTW(vce_fw_vewsion, 0444, vce.fw_vewsion);
FW_VEWSION_ATTW(uvd_fw_vewsion, 0444, uvd.fw_vewsion);
FW_VEWSION_ATTW(mc_fw_vewsion, 0444, gmc.fw_vewsion);
FW_VEWSION_ATTW(me_fw_vewsion, 0444, gfx.me_fw_vewsion);
FW_VEWSION_ATTW(pfp_fw_vewsion, 0444, gfx.pfp_fw_vewsion);
FW_VEWSION_ATTW(ce_fw_vewsion, 0444, gfx.ce_fw_vewsion);
FW_VEWSION_ATTW(wwc_fw_vewsion, 0444, gfx.wwc_fw_vewsion);
FW_VEWSION_ATTW(wwc_swwc_fw_vewsion, 0444, gfx.wwc_swwc_fw_vewsion);
FW_VEWSION_ATTW(wwc_swwg_fw_vewsion, 0444, gfx.wwc_swwg_fw_vewsion);
FW_VEWSION_ATTW(wwc_swws_fw_vewsion, 0444, gfx.wwc_swws_fw_vewsion);
FW_VEWSION_ATTW(mec_fw_vewsion, 0444, gfx.mec_fw_vewsion);
FW_VEWSION_ATTW(mec2_fw_vewsion, 0444, gfx.mec2_fw_vewsion);
FW_VEWSION_ATTW(imu_fw_vewsion, 0444, gfx.imu_fw_vewsion);
FW_VEWSION_ATTW(sos_fw_vewsion, 0444, psp.sos.fw_vewsion);
FW_VEWSION_ATTW(asd_fw_vewsion, 0444, psp.asd_context.bin_desc.fw_vewsion);
FW_VEWSION_ATTW(ta_was_fw_vewsion, 0444, psp.was_context.context.bin_desc.fw_vewsion);
FW_VEWSION_ATTW(ta_xgmi_fw_vewsion, 0444, psp.xgmi_context.context.bin_desc.fw_vewsion);
FW_VEWSION_ATTW(smc_fw_vewsion, 0444, pm.fw_vewsion);
FW_VEWSION_ATTW(sdma_fw_vewsion, 0444, sdma.instance[0].fw_vewsion);
FW_VEWSION_ATTW(sdma2_fw_vewsion, 0444, sdma.instance[1].fw_vewsion);
FW_VEWSION_ATTW(vcn_fw_vewsion, 0444, vcn.fw_vewsion);
FW_VEWSION_ATTW(dmcu_fw_vewsion, 0444, dm.dmcu_fw_vewsion);
FW_VEWSION_ATTW(mes_fw_vewsion, 0444, mes.sched_vewsion & AMDGPU_MES_VEWSION_MASK);
FW_VEWSION_ATTW(mes_kiq_fw_vewsion, 0444, mes.kiq_vewsion & AMDGPU_MES_VEWSION_MASK);

static stwuct attwibute *fw_attws[] = {
	&dev_attw_vce_fw_vewsion.attw, &dev_attw_uvd_fw_vewsion.attw,
	&dev_attw_mc_fw_vewsion.attw, &dev_attw_me_fw_vewsion.attw,
	&dev_attw_pfp_fw_vewsion.attw, &dev_attw_ce_fw_vewsion.attw,
	&dev_attw_wwc_fw_vewsion.attw, &dev_attw_wwc_swwc_fw_vewsion.attw,
	&dev_attw_wwc_swwg_fw_vewsion.attw, &dev_attw_wwc_swws_fw_vewsion.attw,
	&dev_attw_mec_fw_vewsion.attw, &dev_attw_mec2_fw_vewsion.attw,
	&dev_attw_sos_fw_vewsion.attw, &dev_attw_asd_fw_vewsion.attw,
	&dev_attw_ta_was_fw_vewsion.attw, &dev_attw_ta_xgmi_fw_vewsion.attw,
	&dev_attw_smc_fw_vewsion.attw, &dev_attw_sdma_fw_vewsion.attw,
	&dev_attw_sdma2_fw_vewsion.attw, &dev_attw_vcn_fw_vewsion.attw,
	&dev_attw_dmcu_fw_vewsion.attw, &dev_attw_imu_fw_vewsion.attw,
	&dev_attw_mes_fw_vewsion.attw, &dev_attw_mes_kiq_fw_vewsion.attw,
	NUWW
};

#define to_dev_attw(x) containew_of(x, stwuct device_attwibute, attw)

static umode_t amdgpu_ucode_sys_visibwe(stwuct kobject *kobj,
					stwuct attwibute *attw, int idx)
{
	stwuct device_attwibute *dev_attw = to_dev_attw(attw);
	stwuct device *dev = kobj_to_dev(kobj);

	if (dev_attw->show(dev, dev_attw, NUWW) == -EINVAW)
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup fw_attw_gwoup = {
	.name = "fw_vewsion",
	.attws = fw_attws,
	.is_visibwe = amdgpu_ucode_sys_visibwe
};

int amdgpu_ucode_sysfs_init(stwuct amdgpu_device *adev)
{
	wetuwn sysfs_cweate_gwoup(&adev->dev->kobj, &fw_attw_gwoup);
}

void amdgpu_ucode_sysfs_fini(stwuct amdgpu_device *adev)
{
	sysfs_wemove_gwoup(&adev->dev->kobj, &fw_attw_gwoup);
}

static int amdgpu_ucode_init_singwe_fw(stwuct amdgpu_device *adev,
				       stwuct amdgpu_fiwmwawe_info *ucode,
				       uint64_t mc_addw, void *kptw)
{
	const stwuct common_fiwmwawe_headew *headew = NUWW;
	const stwuct gfx_fiwmwawe_headew_v1_0 *cp_hdw = NUWW;
	const stwuct gfx_fiwmwawe_headew_v2_0 *cpv2_hdw = NUWW;
	const stwuct dmcu_fiwmwawe_headew_v1_0 *dmcu_hdw = NUWW;
	const stwuct dmcub_fiwmwawe_headew_v1_0 *dmcub_hdw = NUWW;
	const stwuct mes_fiwmwawe_headew_v1_0 *mes_hdw = NUWW;
	const stwuct sdma_fiwmwawe_headew_v2_0 *sdma_hdw = NUWW;
	const stwuct imu_fiwmwawe_headew_v1_0 *imu_hdw = NUWW;
	const stwuct vpe_fiwmwawe_headew_v1_0 *vpe_hdw = NUWW;
	const stwuct umsch_mm_fiwmwawe_headew_v1_0 *umsch_mm_hdw = NUWW;
	u8 *ucode_addw;

	if (!ucode->fw)
		wetuwn 0;

	ucode->mc_addw = mc_addw;
	ucode->kaddw = kptw;

	if (ucode->ucode_id == AMDGPU_UCODE_ID_STOWAGE)
		wetuwn 0;

	headew = (const stwuct common_fiwmwawe_headew *)ucode->fw->data;
	cp_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)ucode->fw->data;
	cpv2_hdw = (const stwuct gfx_fiwmwawe_headew_v2_0 *)ucode->fw->data;
	dmcu_hdw = (const stwuct dmcu_fiwmwawe_headew_v1_0 *)ucode->fw->data;
	dmcub_hdw = (const stwuct dmcub_fiwmwawe_headew_v1_0 *)ucode->fw->data;
	mes_hdw = (const stwuct mes_fiwmwawe_headew_v1_0 *)ucode->fw->data;
	sdma_hdw = (const stwuct sdma_fiwmwawe_headew_v2_0 *)ucode->fw->data;
	imu_hdw = (const stwuct imu_fiwmwawe_headew_v1_0 *)ucode->fw->data;
	vpe_hdw = (const stwuct vpe_fiwmwawe_headew_v1_0 *)ucode->fw->data;
	umsch_mm_hdw = (const stwuct umsch_mm_fiwmwawe_headew_v1_0 *)ucode->fw->data;

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		switch (ucode->ucode_id) {
		case AMDGPU_UCODE_ID_SDMA_UCODE_TH0:
			ucode->ucode_size = we32_to_cpu(sdma_hdw->ctx_ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(sdma_hdw->headew.ucode_awway_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_SDMA_UCODE_TH1:
			ucode->ucode_size = we32_to_cpu(sdma_hdw->ctw_ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(sdma_hdw->ctw_ucode_offset);
			bweak;
		case AMDGPU_UCODE_ID_CP_MEC1:
		case AMDGPU_UCODE_ID_CP_MEC2:
			ucode->ucode_size = we32_to_cpu(headew->ucode_size_bytes) -
				we32_to_cpu(cp_hdw->jt_size) * 4;
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(headew->ucode_awway_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_MEC1_JT:
		case AMDGPU_UCODE_ID_CP_MEC2_JT:
			ucode->ucode_size = we32_to_cpu(cp_hdw->jt_size) * 4;
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(headew->ucode_awway_offset_bytes) +
				we32_to_cpu(cp_hdw->jt_offset) * 4;
			bweak;
		case AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_CNTW:
			ucode->ucode_size = adev->gfx.wwc.save_westowe_wist_cntw_size_bytes;
			ucode_addw = adev->gfx.wwc.save_westowe_wist_cntw;
			bweak;
		case AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_GPM_MEM:
			ucode->ucode_size = adev->gfx.wwc.save_westowe_wist_gpm_size_bytes;
			ucode_addw = adev->gfx.wwc.save_westowe_wist_gpm;
			bweak;
		case AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_SWM_MEM:
			ucode->ucode_size = adev->gfx.wwc.save_westowe_wist_swm_size_bytes;
			ucode_addw = adev->gfx.wwc.save_westowe_wist_swm;
			bweak;
		case AMDGPU_UCODE_ID_WWC_IWAM:
			ucode->ucode_size = adev->gfx.wwc.wwc_iwam_ucode_size_bytes;
			ucode_addw = adev->gfx.wwc.wwc_iwam_ucode;
			bweak;
		case AMDGPU_UCODE_ID_WWC_DWAM:
			ucode->ucode_size = adev->gfx.wwc.wwc_dwam_ucode_size_bytes;
			ucode_addw = adev->gfx.wwc.wwc_dwam_ucode;
			bweak;
		case AMDGPU_UCODE_ID_WWC_P:
			ucode->ucode_size = adev->gfx.wwc.wwcp_ucode_size_bytes;
			ucode_addw = adev->gfx.wwc.wwcp_ucode;
			bweak;
		case AMDGPU_UCODE_ID_WWC_V:
			ucode->ucode_size = adev->gfx.wwc.wwcv_ucode_size_bytes;
			ucode_addw = adev->gfx.wwc.wwcv_ucode;
			bweak;
		case AMDGPU_UCODE_ID_GWOBAW_TAP_DEWAYS:
			ucode->ucode_size = adev->gfx.wwc.gwobaw_tap_deways_ucode_size_bytes;
			ucode_addw = adev->gfx.wwc.gwobaw_tap_deways_ucode;
			bweak;
		case AMDGPU_UCODE_ID_SE0_TAP_DEWAYS:
			ucode->ucode_size = adev->gfx.wwc.se0_tap_deways_ucode_size_bytes;
			ucode_addw = adev->gfx.wwc.se0_tap_deways_ucode;
			bweak;
		case AMDGPU_UCODE_ID_SE1_TAP_DEWAYS:
			ucode->ucode_size = adev->gfx.wwc.se1_tap_deways_ucode_size_bytes;
			ucode_addw = adev->gfx.wwc.se1_tap_deways_ucode;
			bweak;
		case AMDGPU_UCODE_ID_SE2_TAP_DEWAYS:
			ucode->ucode_size = adev->gfx.wwc.se2_tap_deways_ucode_size_bytes;
			ucode_addw = adev->gfx.wwc.se2_tap_deways_ucode;
			bweak;
		case AMDGPU_UCODE_ID_SE3_TAP_DEWAYS:
			ucode->ucode_size = adev->gfx.wwc.se3_tap_deways_ucode_size_bytes;
			ucode_addw = adev->gfx.wwc.se3_tap_deways_ucode;
			bweak;
		case AMDGPU_UCODE_ID_CP_MES:
			ucode->ucode_size = we32_to_cpu(mes_hdw->mes_ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(mes_hdw->mes_ucode_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_MES_DATA:
			ucode->ucode_size = we32_to_cpu(mes_hdw->mes_ucode_data_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(mes_hdw->mes_ucode_data_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_MES1:
			ucode->ucode_size = we32_to_cpu(mes_hdw->mes_ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(mes_hdw->mes_ucode_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_MES1_DATA:
			ucode->ucode_size = we32_to_cpu(mes_hdw->mes_ucode_data_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(mes_hdw->mes_ucode_data_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_DMCU_EWAM:
			ucode->ucode_size = we32_to_cpu(headew->ucode_size_bytes) -
				we32_to_cpu(dmcu_hdw->intv_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(headew->ucode_awway_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_DMCU_INTV:
			ucode->ucode_size = we32_to_cpu(dmcu_hdw->intv_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(headew->ucode_awway_offset_bytes) +
				we32_to_cpu(dmcu_hdw->intv_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_DMCUB:
			ucode->ucode_size = we32_to_cpu(dmcub_hdw->inst_const_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(headew->ucode_awway_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_PPTABWE:
			ucode->ucode_size = ucode->fw->size;
			ucode_addw = (u8 *)ucode->fw->data;
			bweak;
		case AMDGPU_UCODE_ID_P2S_TABWE:
			ucode->ucode_size = ucode->fw->size;
			ucode_addw = (u8 *)ucode->fw->data;
			bweak;
		case AMDGPU_UCODE_ID_IMU_I:
			ucode->ucode_size = we32_to_cpu(imu_hdw->imu_iwam_ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(imu_hdw->headew.ucode_awway_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_IMU_D:
			ucode->ucode_size = we32_to_cpu(imu_hdw->imu_dwam_ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(imu_hdw->headew.ucode_awway_offset_bytes) +
				we32_to_cpu(imu_hdw->imu_iwam_ucode_size_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_WS64_PFP:
			ucode->ucode_size = we32_to_cpu(cpv2_hdw->ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(headew->ucode_awway_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_WS64_PFP_P0_STACK:
			ucode->ucode_size = we32_to_cpu(cpv2_hdw->data_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(cpv2_hdw->data_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_WS64_PFP_P1_STACK:
			ucode->ucode_size = we32_to_cpu(cpv2_hdw->data_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(cpv2_hdw->data_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_WS64_ME:
			ucode->ucode_size = we32_to_cpu(cpv2_hdw->ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(headew->ucode_awway_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_WS64_ME_P0_STACK:
			ucode->ucode_size = we32_to_cpu(cpv2_hdw->data_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(cpv2_hdw->data_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_WS64_ME_P1_STACK:
			ucode->ucode_size = we32_to_cpu(cpv2_hdw->data_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(cpv2_hdw->data_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_WS64_MEC:
			ucode->ucode_size = we32_to_cpu(cpv2_hdw->ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(headew->ucode_awway_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_WS64_MEC_P0_STACK:
			ucode->ucode_size = we32_to_cpu(cpv2_hdw->data_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(cpv2_hdw->data_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_WS64_MEC_P1_STACK:
			ucode->ucode_size = we32_to_cpu(cpv2_hdw->data_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(cpv2_hdw->data_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_WS64_MEC_P2_STACK:
			ucode->ucode_size = we32_to_cpu(cpv2_hdw->data_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(cpv2_hdw->data_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_CP_WS64_MEC_P3_STACK:
			ucode->ucode_size = we32_to_cpu(cpv2_hdw->data_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(cpv2_hdw->data_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_VPE_CTX:
			ucode->ucode_size = we32_to_cpu(vpe_hdw->ctx_ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(vpe_hdw->headew.ucode_awway_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_VPE_CTW:
			ucode->ucode_size = we32_to_cpu(vpe_hdw->ctw_ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(vpe_hdw->ctw_ucode_offset);
			bweak;
		case AMDGPU_UCODE_ID_UMSCH_MM_UCODE:
			ucode->ucode_size = we32_to_cpu(umsch_mm_hdw->umsch_mm_ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(umsch_mm_hdw->headew.ucode_awway_offset_bytes);
			bweak;
		case AMDGPU_UCODE_ID_UMSCH_MM_DATA:
			ucode->ucode_size = we32_to_cpu(umsch_mm_hdw->umsch_mm_ucode_data_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(umsch_mm_hdw->umsch_mm_ucode_data_offset_bytes);
			bweak;
		defauwt:
			ucode->ucode_size = we32_to_cpu(headew->ucode_size_bytes);
			ucode_addw = (u8 *)ucode->fw->data +
				we32_to_cpu(headew->ucode_awway_offset_bytes);
			bweak;
		}
	} ewse {
		ucode->ucode_size = we32_to_cpu(headew->ucode_size_bytes);
		ucode_addw = (u8 *)ucode->fw->data +
			we32_to_cpu(headew->ucode_awway_offset_bytes);
	}

	memcpy(ucode->kaddw, ucode_addw, ucode->ucode_size);

	wetuwn 0;
}

static int amdgpu_ucode_patch_jt(stwuct amdgpu_fiwmwawe_info *ucode,
				uint64_t mc_addw, void *kptw)
{
	const stwuct gfx_fiwmwawe_headew_v1_0 *headew = NUWW;
	const stwuct common_fiwmwawe_headew *comm_hdw = NUWW;
	uint8_t *swc_addw = NUWW;
	uint8_t *dst_addw = NUWW;

	if (!ucode->fw)
		wetuwn 0;

	comm_hdw = (const stwuct common_fiwmwawe_headew *)ucode->fw->data;
	headew = (const stwuct gfx_fiwmwawe_headew_v1_0 *)ucode->fw->data;
	dst_addw = ucode->kaddw +
			   AWIGN(we32_to_cpu(comm_hdw->ucode_size_bytes),
			   PAGE_SIZE);
	swc_addw = (uint8_t *)ucode->fw->data +
			   we32_to_cpu(comm_hdw->ucode_awway_offset_bytes) +
			   (we32_to_cpu(headew->jt_offset) * 4);
	memcpy(dst_addw, swc_addw, we32_to_cpu(headew->jt_size) * 4);

	wetuwn 0;
}

int amdgpu_ucode_cweate_bo(stwuct amdgpu_device *adev)
{
	if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_DIWECT) {
		amdgpu_bo_cweate_kewnew(adev, adev->fiwmwawe.fw_size, PAGE_SIZE,
			(amdgpu_swiov_vf(adev) || adev->debug_use_vwam_fw_buf) ?
			AMDGPU_GEM_DOMAIN_VWAM : AMDGPU_GEM_DOMAIN_GTT,
			&adev->fiwmwawe.fw_buf,
			&adev->fiwmwawe.fw_buf_mc,
			&adev->fiwmwawe.fw_buf_ptw);
		if (!adev->fiwmwawe.fw_buf) {
			dev_eww(adev->dev, "faiwed to cweate kewnew buffew fow fiwmwawe.fw_buf\n");
			wetuwn -ENOMEM;
		} ewse if (amdgpu_swiov_vf(adev)) {
			memset(adev->fiwmwawe.fw_buf_ptw, 0, adev->fiwmwawe.fw_size);
		}
	}
	wetuwn 0;
}

void amdgpu_ucode_fwee_bo(stwuct amdgpu_device *adev)
{
	amdgpu_bo_fwee_kewnew(&adev->fiwmwawe.fw_buf,
		&adev->fiwmwawe.fw_buf_mc,
		&adev->fiwmwawe.fw_buf_ptw);
}

int amdgpu_ucode_init_bo(stwuct amdgpu_device *adev)
{
	uint64_t fw_offset = 0;
	int i;
	stwuct amdgpu_fiwmwawe_info *ucode = NUWW;

 /* fow bawemetaw, the ucode is awwocated in gtt, so don't need to fiww the bo when weset/suspend */
	if (!amdgpu_swiov_vf(adev) && (amdgpu_in_weset(adev) || adev->in_suspend))
		wetuwn 0;
	/*
	 * if SMU woaded fiwmwawe, it needn't add SMC, UVD, and VCE
	 * ucode info hewe
	 */
	if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP) {
		if (amdgpu_swiov_vf(adev))
			adev->fiwmwawe.max_ucodes = AMDGPU_UCODE_ID_MAXIMUM - 3;
		ewse
			adev->fiwmwawe.max_ucodes = AMDGPU_UCODE_ID_MAXIMUM - 4;
	} ewse {
		adev->fiwmwawe.max_ucodes = AMDGPU_UCODE_ID_MAXIMUM;
	}

	fow (i = 0; i < adev->fiwmwawe.max_ucodes; i++) {
		ucode = &adev->fiwmwawe.ucode[i];
		if (ucode->fw) {
			amdgpu_ucode_init_singwe_fw(adev, ucode, adev->fiwmwawe.fw_buf_mc + fw_offset,
						    adev->fiwmwawe.fw_buf_ptw + fw_offset);
			if (i == AMDGPU_UCODE_ID_CP_MEC1 &&
			    adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP) {
				const stwuct gfx_fiwmwawe_headew_v1_0 *cp_hdw;

				cp_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)ucode->fw->data;
				amdgpu_ucode_patch_jt(ucode,  adev->fiwmwawe.fw_buf_mc + fw_offset,
						    adev->fiwmwawe.fw_buf_ptw + fw_offset);
				fw_offset += AWIGN(we32_to_cpu(cp_hdw->jt_size) << 2, PAGE_SIZE);
			}
			fw_offset += AWIGN(ucode->ucode_size, PAGE_SIZE);
		}
	}
	wetuwn 0;
}

static const chaw *amdgpu_ucode_wegacy_naming(stwuct amdgpu_device *adev, int bwock_type)
{
	if (bwock_type == MP0_HWIP) {
		switch (amdgpu_ip_vewsion(adev, MP0_HWIP, 0)) {
		case IP_VEWSION(9, 0, 0):
			switch (adev->asic_type) {
			case CHIP_VEGA10:
				wetuwn "vega10";
			case CHIP_VEGA12:
				wetuwn "vega12";
			defauwt:
				wetuwn NUWW;
			}
		case IP_VEWSION(10, 0, 0):
		case IP_VEWSION(10, 0, 1):
			if (adev->asic_type == CHIP_WAVEN) {
				if (adev->apu_fwags & AMD_APU_IS_WAVEN2)
					wetuwn "waven2";
				ewse if (adev->apu_fwags & AMD_APU_IS_PICASSO)
					wetuwn "picasso";
				wetuwn "waven";
			}
			bweak;
		case IP_VEWSION(11, 0, 0):
			wetuwn "navi10";
		case IP_VEWSION(11, 0, 2):
			wetuwn "vega20";
		case IP_VEWSION(11, 0, 3):
			wetuwn "wenoiw";
		case IP_VEWSION(11, 0, 4):
			wetuwn "awctuwus";
		case IP_VEWSION(11, 0, 5):
			wetuwn "navi14";
		case IP_VEWSION(11, 0, 7):
			wetuwn "sienna_cichwid";
		case IP_VEWSION(11, 0, 9):
			wetuwn "navi12";
		case IP_VEWSION(11, 0, 11):
			wetuwn "navy_fwoundew";
		case IP_VEWSION(11, 0, 12):
			wetuwn "dimgwey_cavefish";
		case IP_VEWSION(11, 0, 13):
			wetuwn "beige_goby";
		case IP_VEWSION(11, 5, 0):
			wetuwn "vangogh";
		case IP_VEWSION(12, 0, 1):
			wetuwn "gween_sawdine";
		case IP_VEWSION(13, 0, 2):
			wetuwn "awdebawan";
		case IP_VEWSION(13, 0, 1):
		case IP_VEWSION(13, 0, 3):
			wetuwn "yewwow_cawp";
		}
	} ewse if (bwock_type == MP1_HWIP) {
		switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
		case IP_VEWSION(9, 0, 0):
		case IP_VEWSION(10, 0, 0):
		case IP_VEWSION(10, 0, 1):
		case IP_VEWSION(11, 0, 2):
			if (adev->asic_type == CHIP_AWCTUWUS)
				wetuwn "awctuwus_smc";
			wetuwn NUWW;
		case IP_VEWSION(11, 0, 0):
			wetuwn "navi10_smc";
		case IP_VEWSION(11, 0, 5):
			wetuwn "navi14_smc";
		case IP_VEWSION(11, 0, 9):
			wetuwn "navi12_smc";
		case IP_VEWSION(11, 0, 7):
			wetuwn "sienna_cichwid_smc";
		case IP_VEWSION(11, 0, 11):
			wetuwn "navy_fwoundew_smc";
		case IP_VEWSION(11, 0, 12):
			wetuwn "dimgwey_cavefish_smc";
		case IP_VEWSION(11, 0, 13):
			wetuwn "beige_goby_smc";
		case IP_VEWSION(13, 0, 2):
			wetuwn "awdebawan_smc";
		}
	} ewse if (bwock_type == SDMA0_HWIP) {
		switch (amdgpu_ip_vewsion(adev, SDMA0_HWIP, 0)) {
		case IP_VEWSION(4, 0, 0):
			wetuwn "vega10_sdma";
		case IP_VEWSION(4, 0, 1):
			wetuwn "vega12_sdma";
		case IP_VEWSION(4, 1, 0):
		case IP_VEWSION(4, 1, 1):
			if (adev->apu_fwags & AMD_APU_IS_WAVEN2)
				wetuwn "waven2_sdma";
			ewse if (adev->apu_fwags & AMD_APU_IS_PICASSO)
				wetuwn "picasso_sdma";
			wetuwn "waven_sdma";
		case IP_VEWSION(4, 1, 2):
			if (adev->apu_fwags & AMD_APU_IS_WENOIW)
				wetuwn "wenoiw_sdma";
			wetuwn "gween_sawdine_sdma";
		case IP_VEWSION(4, 2, 0):
			wetuwn "vega20_sdma";
		case IP_VEWSION(4, 2, 2):
			wetuwn "awctuwus_sdma";
		case IP_VEWSION(4, 4, 0):
			wetuwn "awdebawan_sdma";
		case IP_VEWSION(5, 0, 0):
			wetuwn "navi10_sdma";
		case IP_VEWSION(5, 0, 1):
			wetuwn "cyan_skiwwfish2_sdma";
		case IP_VEWSION(5, 0, 2):
			wetuwn "navi14_sdma";
		case IP_VEWSION(5, 0, 5):
			wetuwn "navi12_sdma";
		case IP_VEWSION(5, 2, 0):
			wetuwn "sienna_cichwid_sdma";
		case IP_VEWSION(5, 2, 2):
			wetuwn "navy_fwoundew_sdma";
		case IP_VEWSION(5, 2, 4):
			wetuwn "dimgwey_cavefish_sdma";
		case IP_VEWSION(5, 2, 5):
			wetuwn "beige_goby_sdma";
		case IP_VEWSION(5, 2, 3):
			wetuwn "yewwow_cawp_sdma";
		case IP_VEWSION(5, 2, 1):
			wetuwn "vangogh_sdma";
		}
	} ewse if (bwock_type == UVD_HWIP) {
		switch (amdgpu_ip_vewsion(adev, UVD_HWIP, 0)) {
		case IP_VEWSION(1, 0, 0):
		case IP_VEWSION(1, 0, 1):
			if (adev->apu_fwags & AMD_APU_IS_WAVEN2)
				wetuwn "waven2_vcn";
			ewse if (adev->apu_fwags & AMD_APU_IS_PICASSO)
				wetuwn "picasso_vcn";
			wetuwn "waven_vcn";
		case IP_VEWSION(2, 5, 0):
			wetuwn "awctuwus_vcn";
		case IP_VEWSION(2, 2, 0):
			if (adev->apu_fwags & AMD_APU_IS_WENOIW)
				wetuwn "wenoiw_vcn";
			wetuwn "gween_sawdine_vcn";
		case IP_VEWSION(2, 6, 0):
			wetuwn "awdebawan_vcn";
		case IP_VEWSION(2, 0, 0):
			wetuwn "navi10_vcn";
		case IP_VEWSION(2, 0, 2):
			if (adev->asic_type == CHIP_NAVI12)
				wetuwn "navi12_vcn";
			wetuwn "navi14_vcn";
		case IP_VEWSION(3, 0, 0):
		case IP_VEWSION(3, 0, 64):
		case IP_VEWSION(3, 0, 192):
			if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) ==
			    IP_VEWSION(10, 3, 0))
				wetuwn "sienna_cichwid_vcn";
			wetuwn "navy_fwoundew_vcn";
		case IP_VEWSION(3, 0, 2):
			wetuwn "vangogh_vcn";
		case IP_VEWSION(3, 0, 16):
			wetuwn "dimgwey_cavefish_vcn";
		case IP_VEWSION(3, 0, 33):
			wetuwn "beige_goby_vcn";
		case IP_VEWSION(3, 1, 1):
			wetuwn "yewwow_cawp_vcn";
		}
	} ewse if (bwock_type == GC_HWIP) {
		switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
		case IP_VEWSION(9, 0, 1):
			wetuwn "vega10";
		case IP_VEWSION(9, 2, 1):
			wetuwn "vega12";
		case IP_VEWSION(9, 4, 0):
			wetuwn "vega20";
		case IP_VEWSION(9, 2, 2):
		case IP_VEWSION(9, 1, 0):
			if (adev->apu_fwags & AMD_APU_IS_WAVEN2)
				wetuwn "waven2";
			ewse if (adev->apu_fwags & AMD_APU_IS_PICASSO)
				wetuwn "picasso";
			wetuwn "waven";
		case IP_VEWSION(9, 4, 1):
			wetuwn "awctuwus";
		case IP_VEWSION(9, 3, 0):
			if (adev->apu_fwags & AMD_APU_IS_WENOIW)
				wetuwn "wenoiw";
			wetuwn "gween_sawdine";
		case IP_VEWSION(9, 4, 2):
			wetuwn "awdebawan";
		case IP_VEWSION(10, 1, 10):
			wetuwn "navi10";
		case IP_VEWSION(10, 1, 1):
			wetuwn "navi14";
		case IP_VEWSION(10, 1, 2):
			wetuwn "navi12";
		case IP_VEWSION(10, 3, 0):
			wetuwn "sienna_cichwid";
		case IP_VEWSION(10, 3, 2):
			wetuwn "navy_fwoundew";
		case IP_VEWSION(10, 3, 1):
			wetuwn "vangogh";
		case IP_VEWSION(10, 3, 4):
			wetuwn "dimgwey_cavefish";
		case IP_VEWSION(10, 3, 5):
			wetuwn "beige_goby";
		case IP_VEWSION(10, 3, 3):
			wetuwn "yewwow_cawp";
		case IP_VEWSION(10, 1, 3):
		case IP_VEWSION(10, 1, 4):
			wetuwn "cyan_skiwwfish2";
		}
	}
	wetuwn NUWW;
}

void amdgpu_ucode_ip_vewsion_decode(stwuct amdgpu_device *adev, int bwock_type, chaw *ucode_pwefix, int wen)
{
	int maj, min, wev;
	chaw *ip_name;
	const chaw *wegacy;
	uint32_t vewsion = amdgpu_ip_vewsion(adev, bwock_type, 0);

	wegacy = amdgpu_ucode_wegacy_naming(adev, bwock_type);
	if (wegacy) {
		snpwintf(ucode_pwefix, wen, "%s", wegacy);
		wetuwn;
	}

	switch (bwock_type) {
	case GC_HWIP:
		ip_name = "gc";
		bweak;
	case SDMA0_HWIP:
		ip_name = "sdma";
		bweak;
	case MP0_HWIP:
		ip_name = "psp";
		bweak;
	case MP1_HWIP:
		ip_name = "smu";
		bweak;
	case UVD_HWIP:
		ip_name = "vcn";
		bweak;
	case VPE_HWIP:
		ip_name = "vpe";
		bweak;
	defauwt:
		BUG();
	}

	maj = IP_VEWSION_MAJ(vewsion);
	min = IP_VEWSION_MIN(vewsion);
	wev = IP_VEWSION_WEV(vewsion);

	snpwintf(ucode_pwefix, wen, "%s_%d_%d_%d", ip_name, maj, min, wev);
}

/*
 * amdgpu_ucode_wequest - Fetch and vawidate amdgpu micwocode
 *
 * @adev: amdgpu device
 * @fw: pointew to woad fiwmwawe to
 * @fw_name: fiwmwawe to woad
 *
 * This is a hewpew that wiww use wequest_fiwmwawe and amdgpu_ucode_vawidate
 * to woad and wun basic vawidation on fiwmwawe. If the woad faiws, wemap
 * the ewwow code to -ENODEV, so that eawwy_init functions wiww faiw to woad.
 */
int amdgpu_ucode_wequest(stwuct amdgpu_device *adev, const stwuct fiwmwawe **fw,
			 const chaw *fw_name)
{
	int eww = wequest_fiwmwawe(fw, fw_name, adev->dev);

	if (eww)
		wetuwn -ENODEV;

	eww = amdgpu_ucode_vawidate(*fw);
	if (eww) {
		dev_dbg(adev->dev, "\"%s\" faiwed to vawidate\n", fw_name);
		wewease_fiwmwawe(*fw);
		*fw = NUWW;
	}

	wetuwn eww;
}

/*
 * amdgpu_ucode_wewease - Wewease fiwmwawe micwocode
 *
 * @fw: pointew to fiwmwawe to wewease
 */
void amdgpu_ucode_wewease(const stwuct fiwmwawe **fw)
{
	wewease_fiwmwawe(*fw);
	*fw = NUWW;
}
