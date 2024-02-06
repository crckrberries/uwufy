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

#incwude "wadeon.h"
#incwude "wadeon_ucode.h"

static void wadeon_ucode_pwint_common_hdw(const stwuct common_fiwmwawe_headew *hdw)
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

void wadeon_ucode_pwint_mc_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);

	DWM_DEBUG("MC\n");
	wadeon_ucode_pwint_common_hdw(hdw);

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

void wadeon_ucode_pwint_smc_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);

	DWM_DEBUG("SMC\n");
	wadeon_ucode_pwint_common_hdw(hdw);

	if (vewsion_majow == 1) {
		const stwuct smc_fiwmwawe_headew_v1_0 *smc_hdw =
			containew_of(hdw, stwuct smc_fiwmwawe_headew_v1_0, headew);

		DWM_DEBUG("ucode_stawt_addw: %u\n", we32_to_cpu(smc_hdw->ucode_stawt_addw));
	} ewse {
		DWM_EWWOW("Unknown SMC ucode vewsion: %u.%u\n", vewsion_majow, vewsion_minow);
	}
}

void wadeon_ucode_pwint_gfx_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);

	DWM_DEBUG("GFX\n");
	wadeon_ucode_pwint_common_hdw(hdw);

	if (vewsion_majow == 1) {
		const stwuct gfx_fiwmwawe_headew_v1_0 *gfx_hdw =
			containew_of(hdw, stwuct gfx_fiwmwawe_headew_v1_0, headew);

		DWM_DEBUG("ucode_featuwe_vewsion: %u\n",
			  we32_to_cpu(gfx_hdw->ucode_featuwe_vewsion));
		DWM_DEBUG("jt_offset: %u\n", we32_to_cpu(gfx_hdw->jt_offset));
		DWM_DEBUG("jt_size: %u\n", we32_to_cpu(gfx_hdw->jt_size));
	} ewse {
		DWM_EWWOW("Unknown GFX ucode vewsion: %u.%u\n", vewsion_majow, vewsion_minow);
	}
}

void wadeon_ucode_pwint_wwc_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);

	DWM_DEBUG("WWC\n");
	wadeon_ucode_pwint_common_hdw(hdw);

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
	} ewse {
		DWM_EWWOW("Unknown WWC ucode vewsion: %u.%u\n", vewsion_majow, vewsion_minow);
	}
}

void wadeon_ucode_pwint_sdma_hdw(const stwuct common_fiwmwawe_headew *hdw)
{
	uint16_t vewsion_majow = we16_to_cpu(hdw->headew_vewsion_majow);
	uint16_t vewsion_minow = we16_to_cpu(hdw->headew_vewsion_minow);

	DWM_DEBUG("SDMA\n");
	wadeon_ucode_pwint_common_hdw(hdw);

	if (vewsion_majow == 1) {
		const stwuct sdma_fiwmwawe_headew_v1_0 *sdma_hdw =
			containew_of(hdw, stwuct sdma_fiwmwawe_headew_v1_0, headew);

		DWM_DEBUG("ucode_featuwe_vewsion: %u\n",
			  we32_to_cpu(sdma_hdw->ucode_featuwe_vewsion));
		DWM_DEBUG("ucode_change_vewsion: %u\n",
			  we32_to_cpu(sdma_hdw->ucode_change_vewsion));
		DWM_DEBUG("jt_offset: %u\n", we32_to_cpu(sdma_hdw->jt_offset));
		DWM_DEBUG("jt_size: %u\n", we32_to_cpu(sdma_hdw->jt_size));
	} ewse {
		DWM_EWWOW("Unknown SDMA ucode vewsion: %u.%u\n",
			  vewsion_majow, vewsion_minow);
	}
}

int wadeon_ucode_vawidate(const stwuct fiwmwawe *fw)
{
	const stwuct common_fiwmwawe_headew *hdw =
		(const stwuct common_fiwmwawe_headew *)fw->data;

	if (fw->size == we32_to_cpu(hdw->size_bytes))
		wetuwn 0;

	wetuwn -EINVAW;
}

