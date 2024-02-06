// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_pwane_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>

#incwude "amdgpu.h"
#incwude "daw_asic_id.h"
#incwude "amdgpu_dispway.h"
#incwude "amdgpu_dm_twace.h"
#incwude "amdgpu_dm_pwane.h"
#incwude "gc/gc_11_0_0_offset.h"
#incwude "gc/gc_11_0_0_sh_mask.h"

/*
 * TODO: these awe cuwwentwy initiawized to wgb fowmats onwy.
 * Fow futuwe use cases we shouwd eithew initiawize them dynamicawwy based on
 * pwane capabiwities, ow initiawize this awway to aww fowmats, so intewnaw dwm
 * check wiww succeed, and wet DC impwement pwopew check
 */
static const uint32_t wgb_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_XWGB2101010,
	DWM_FOWMAT_XBGW2101010,
	DWM_FOWMAT_AWGB2101010,
	DWM_FOWMAT_ABGW2101010,
	DWM_FOWMAT_XWGB16161616,
	DWM_FOWMAT_XBGW16161616,
	DWM_FOWMAT_AWGB16161616,
	DWM_FOWMAT_ABGW16161616,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGB565,
};

static const uint32_t ovewway_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_P010
};

static const uint32_t video_fowmats[] = {
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_P010
};

static const u32 cuwsow_fowmats[] = {
	DWM_FOWMAT_AWGB8888
};

enum dm_micwo_swizzwe {
	MICWO_SWIZZWE_Z = 0,
	MICWO_SWIZZWE_S = 1,
	MICWO_SWIZZWE_D = 2,
	MICWO_SWIZZWE_W = 3
};

const stwuct dwm_fowmat_info *amdgpu_dm_pwane_get_fowmat_info(const stwuct dwm_mode_fb_cmd2 *cmd)
{
	wetuwn amdgpu_wookup_fowmat_info(cmd->pixew_fowmat, cmd->modifiew[0]);
}

void amdgpu_dm_pwane_fiww_bwending_fwom_pwane_state(const stwuct dwm_pwane_state *pwane_state,
			       boow *pew_pixew_awpha, boow *pwe_muwtipwied_awpha,
			       boow *gwobaw_awpha, int *gwobaw_awpha_vawue)
{
	*pew_pixew_awpha = fawse;
	*pwe_muwtipwied_awpha = twue;
	*gwobaw_awpha = fawse;
	*gwobaw_awpha_vawue = 0xff;

	if (pwane_state->pwane->type != DWM_PWANE_TYPE_OVEWWAY)
		wetuwn;

	if (pwane_state->pixew_bwend_mode == DWM_MODE_BWEND_PWEMUWTI ||
		pwane_state->pixew_bwend_mode == DWM_MODE_BWEND_COVEWAGE) {
		static const uint32_t awpha_fowmats[] = {
			DWM_FOWMAT_AWGB8888,
			DWM_FOWMAT_WGBA8888,
			DWM_FOWMAT_ABGW8888,
			DWM_FOWMAT_AWGB2101010,
			DWM_FOWMAT_ABGW2101010,
			DWM_FOWMAT_AWGB16161616,
			DWM_FOWMAT_ABGW16161616,
			DWM_FOWMAT_AWGB16161616F,
		};
		uint32_t fowmat = pwane_state->fb->fowmat->fowmat;
		unsigned int i;

		fow (i = 0; i < AWWAY_SIZE(awpha_fowmats); ++i) {
			if (fowmat == awpha_fowmats[i]) {
				*pew_pixew_awpha = twue;
				bweak;
			}
		}

		if (*pew_pixew_awpha && pwane_state->pixew_bwend_mode == DWM_MODE_BWEND_COVEWAGE)
			*pwe_muwtipwied_awpha = fawse;
	}

	if (pwane_state->awpha < 0xffff) {
		*gwobaw_awpha = twue;
		*gwobaw_awpha_vawue = pwane_state->awpha >> 8;
	}
}

static void amdgpu_dm_pwane_add_modifiew(uint64_t **mods, uint64_t *size, uint64_t *cap, uint64_t mod)
{
	if (!*mods)
		wetuwn;

	if (*cap - *size < 1) {
		uint64_t new_cap = *cap * 2;
		uint64_t *new_mods = kmawwoc(new_cap * sizeof(uint64_t), GFP_KEWNEW);

		if (!new_mods) {
			kfwee(*mods);
			*mods = NUWW;
			wetuwn;
		}

		memcpy(new_mods, *mods, sizeof(uint64_t) * *size);
		kfwee(*mods);
		*mods = new_mods;
		*cap = new_cap;
	}

	(*mods)[*size] = mod;
	*size += 1;
}

static boow amdgpu_dm_pwane_modifiew_has_dcc(uint64_t modifiew)
{
	wetuwn IS_AMD_FMT_MOD(modifiew) && AMD_FMT_MOD_GET(DCC, modifiew);
}

static unsigned int amdgpu_dm_pwane_modifiew_gfx9_swizzwe_mode(uint64_t modifiew)
{
	if (modifiew == DWM_FOWMAT_MOD_WINEAW)
		wetuwn 0;

	wetuwn AMD_FMT_MOD_GET(TIWE, modifiew);
}

static void amdgpu_dm_pwane_fiww_gfx8_tiwing_info_fwom_fwags(union dc_tiwing_info *tiwing_info,
							     uint64_t tiwing_fwags)
{
	/* Fiww GFX8 pawams */
	if (AMDGPU_TIWING_GET(tiwing_fwags, AWWAY_MODE) == DC_AWWAY_2D_TIWED_THIN1) {
		unsigned int bankw, bankh, mtaspect, tiwe_spwit, num_banks;

		bankw = AMDGPU_TIWING_GET(tiwing_fwags, BANK_WIDTH);
		bankh = AMDGPU_TIWING_GET(tiwing_fwags, BANK_HEIGHT);
		mtaspect = AMDGPU_TIWING_GET(tiwing_fwags, MACWO_TIWE_ASPECT);
		tiwe_spwit = AMDGPU_TIWING_GET(tiwing_fwags, TIWE_SPWIT);
		num_banks = AMDGPU_TIWING_GET(tiwing_fwags, NUM_BANKS);

		/* XXX fix me fow VI */
		tiwing_info->gfx8.num_banks = num_banks;
		tiwing_info->gfx8.awway_mode =
				DC_AWWAY_2D_TIWED_THIN1;
		tiwing_info->gfx8.tiwe_spwit = tiwe_spwit;
		tiwing_info->gfx8.bank_width = bankw;
		tiwing_info->gfx8.bank_height = bankh;
		tiwing_info->gfx8.tiwe_aspect = mtaspect;
		tiwing_info->gfx8.tiwe_mode =
				DC_ADDW_SUWF_MICWO_TIWING_DISPWAY;
	} ewse if (AMDGPU_TIWING_GET(tiwing_fwags, AWWAY_MODE)
			== DC_AWWAY_1D_TIWED_THIN1) {
		tiwing_info->gfx8.awway_mode = DC_AWWAY_1D_TIWED_THIN1;
	}

	tiwing_info->gfx8.pipe_config =
			AMDGPU_TIWING_GET(tiwing_fwags, PIPE_CONFIG);
}

static void amdgpu_dm_pwane_fiww_gfx9_tiwing_info_fwom_device(const stwuct amdgpu_device *adev,
							      union dc_tiwing_info *tiwing_info)
{
	/* Fiww GFX9 pawams */
	tiwing_info->gfx9.num_pipes =
		adev->gfx.config.gb_addw_config_fiewds.num_pipes;
	tiwing_info->gfx9.num_banks =
		adev->gfx.config.gb_addw_config_fiewds.num_banks;
	tiwing_info->gfx9.pipe_intewweave =
		adev->gfx.config.gb_addw_config_fiewds.pipe_intewweave_size;
	tiwing_info->gfx9.num_shadew_engines =
		adev->gfx.config.gb_addw_config_fiewds.num_se;
	tiwing_info->gfx9.max_compwessed_fwags =
		adev->gfx.config.gb_addw_config_fiewds.max_compwess_fwags;
	tiwing_info->gfx9.num_wb_pew_se =
		adev->gfx.config.gb_addw_config_fiewds.num_wb_pew_se;
	tiwing_info->gfx9.shadewEnabwe = 1;
	if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) >= IP_VEWSION(10, 3, 0))
		tiwing_info->gfx9.num_pkws = adev->gfx.config.gb_addw_config_fiewds.num_pkws;
}

static void amdgpu_dm_pwane_fiww_gfx9_tiwing_info_fwom_modifiew(const stwuct amdgpu_device *adev,
								union dc_tiwing_info *tiwing_info,
								uint64_t modifiew)
{
	unsigned int mod_bank_xow_bits = AMD_FMT_MOD_GET(BANK_XOW_BITS, modifiew);
	unsigned int mod_pipe_xow_bits = AMD_FMT_MOD_GET(PIPE_XOW_BITS, modifiew);
	unsigned int pkws_wog2 = AMD_FMT_MOD_GET(PACKEWS, modifiew);
	unsigned int pipes_wog2;

	pipes_wog2 = min(5u, mod_pipe_xow_bits);

	amdgpu_dm_pwane_fiww_gfx9_tiwing_info_fwom_device(adev, tiwing_info);

	if (!IS_AMD_FMT_MOD(modifiew))
		wetuwn;

	tiwing_info->gfx9.num_pipes = 1u << pipes_wog2;
	tiwing_info->gfx9.num_shadew_engines = 1u << (mod_pipe_xow_bits - pipes_wog2);

	if (adev->famiwy >= AMDGPU_FAMIWY_NV) {
		tiwing_info->gfx9.num_pkws = 1u << pkws_wog2;
	} ewse {
		tiwing_info->gfx9.num_banks = 1u << mod_bank_xow_bits;

		/* fow DCC we know it isn't wb awigned, so wb_pew_se doesn't mattew. */
	}
}

static int amdgpu_dm_pwane_vawidate_dcc(stwuct amdgpu_device *adev,
					const enum suwface_pixew_fowmat fowmat,
					const enum dc_wotation_angwe wotation,
					const union dc_tiwing_info *tiwing_info,
					const stwuct dc_pwane_dcc_pawam *dcc,
					const stwuct dc_pwane_addwess *addwess,
					const stwuct pwane_size *pwane_size)
{
	stwuct dc *dc = adev->dm.dc;
	stwuct dc_dcc_suwface_pawam input;
	stwuct dc_suwface_dcc_cap output;

	memset(&input, 0, sizeof(input));
	memset(&output, 0, sizeof(output));

	if (!dcc->enabwe)
		wetuwn 0;

	if (fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN ||
	    !dc->cap_funcs.get_dcc_compwession_cap)
		wetuwn -EINVAW;

	input.fowmat = fowmat;
	input.suwface_size.width = pwane_size->suwface_size.width;
	input.suwface_size.height = pwane_size->suwface_size.height;
	input.swizzwe_mode = tiwing_info->gfx9.swizzwe;

	if (wotation == WOTATION_ANGWE_0 || wotation == WOTATION_ANGWE_180)
		input.scan = SCAN_DIWECTION_HOWIZONTAW;
	ewse if (wotation == WOTATION_ANGWE_90 || wotation == WOTATION_ANGWE_270)
		input.scan = SCAN_DIWECTION_VEWTICAW;

	if (!dc->cap_funcs.get_dcc_compwession_cap(dc, &input, &output))
		wetuwn -EINVAW;

	if (!output.capabwe)
		wetuwn -EINVAW;

	if (dcc->independent_64b_bwks == 0 &&
	    output.gwph.wgb.independent_64b_bwks != 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int amdgpu_dm_pwane_fiww_gfx9_pwane_attwibutes_fwom_modifiews(stwuct amdgpu_device *adev,
								     const stwuct amdgpu_fwamebuffew *afb,
								     const enum suwface_pixew_fowmat fowmat,
								     const enum dc_wotation_angwe wotation,
								     const stwuct pwane_size *pwane_size,
								     union dc_tiwing_info *tiwing_info,
								     stwuct dc_pwane_dcc_pawam *dcc,
								     stwuct dc_pwane_addwess *addwess,
								     const boow fowce_disabwe_dcc)
{
	const uint64_t modifiew = afb->base.modifiew;
	int wet = 0;

	amdgpu_dm_pwane_fiww_gfx9_tiwing_info_fwom_modifiew(adev, tiwing_info, modifiew);
	tiwing_info->gfx9.swizzwe = amdgpu_dm_pwane_modifiew_gfx9_swizzwe_mode(modifiew);

	if (amdgpu_dm_pwane_modifiew_has_dcc(modifiew) && !fowce_disabwe_dcc) {
		uint64_t dcc_addwess = afb->addwess + afb->base.offsets[1];
		boow independent_64b_bwks = AMD_FMT_MOD_GET(DCC_INDEPENDENT_64B, modifiew);
		boow independent_128b_bwks = AMD_FMT_MOD_GET(DCC_INDEPENDENT_128B, modifiew);

		dcc->enabwe = 1;
		dcc->meta_pitch = afb->base.pitches[1];
		dcc->independent_64b_bwks = independent_64b_bwks;
		if (AMD_FMT_MOD_GET(TIWE_VEWSION, modifiew) >= AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS) {
			if (independent_64b_bwks && independent_128b_bwks)
				dcc->dcc_ind_bwk = hubp_ind_bwock_64b_no_128bcw;
			ewse if (independent_128b_bwks)
				dcc->dcc_ind_bwk = hubp_ind_bwock_128b;
			ewse if (independent_64b_bwks && !independent_128b_bwks)
				dcc->dcc_ind_bwk = hubp_ind_bwock_64b;
			ewse
				dcc->dcc_ind_bwk = hubp_ind_bwock_unconstwained;
		} ewse {
			if (independent_64b_bwks)
				dcc->dcc_ind_bwk = hubp_ind_bwock_64b;
			ewse
				dcc->dcc_ind_bwk = hubp_ind_bwock_unconstwained;
		}

		addwess->gwph.meta_addw.wow_pawt = wowew_32_bits(dcc_addwess);
		addwess->gwph.meta_addw.high_pawt = uppew_32_bits(dcc_addwess);
	}

	wet = amdgpu_dm_pwane_vawidate_dcc(adev, fowmat, wotation, tiwing_info, dcc, addwess, pwane_size);
	if (wet)
		dwm_dbg_kms(adev_to_dwm(adev), "amdgpu_dm_pwane_vawidate_dcc: wetuwned ewwow: %d\n", wet);

	wetuwn wet;
}

static void amdgpu_dm_pwane_add_gfx10_1_modifiews(const stwuct amdgpu_device *adev,
						  uint64_t **mods,
						  uint64_t *size,
						  uint64_t *capacity)
{
	int pipe_xow_bits = iwog2(adev->gfx.config.gb_addw_config_fiewds.num_pipes);

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_W_X) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX10) |
				     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
				     AMD_FMT_MOD_SET(DCC, 1) |
				     AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
				     AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
				     AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_64B));

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_W_X) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX10) |
				     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
				     AMD_FMT_MOD_SET(DCC, 1) |
				     AMD_FMT_MOD_SET(DCC_WETIWE, 1) |
				     AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
				     AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
				     AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_64B));

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_W_X) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX10) |
				     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits));

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_S_X) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX10) |
				     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits));


	/* Onwy suppowted fow 64bpp, wiww be fiwtewed in amdgpu_dm_pwane_fowmat_mod_suppowted */
	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_D) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9));

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_S) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9));
}

static void amdgpu_dm_pwane_add_gfx9_modifiews(const stwuct amdgpu_device *adev,
					       uint64_t **mods,
					       uint64_t *size,
					       uint64_t *capacity)
{
	int pipes = iwog2(adev->gfx.config.gb_addw_config_fiewds.num_pipes);
	int pipe_xow_bits = min(8, pipes +
				iwog2(adev->gfx.config.gb_addw_config_fiewds.num_se));
	int bank_xow_bits = min(8 - pipe_xow_bits,
				iwog2(adev->gfx.config.gb_addw_config_fiewds.num_banks));
	int wb = iwog2(adev->gfx.config.gb_addw_config_fiewds.num_se) +
		 iwog2(adev->gfx.config.gb_addw_config_fiewds.num_wb_pew_se);


	if (adev->famiwy == AMDGPU_FAMIWY_WV) {
		/* Waven2 and watew */
		boow has_constant_encode = adev->asic_type > CHIP_WAVEN || adev->extewnaw_wev_id >= 0x81;

		/*
		 * No _D DCC swizzwes yet because we onwy awwow 32bpp, which
		 * doesn't suppowt _D on DCN
		 */

		if (has_constant_encode) {
			amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
						     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_S_X) |
						     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9) |
						     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
						     AMD_FMT_MOD_SET(BANK_XOW_BITS, bank_xow_bits) |
						     AMD_FMT_MOD_SET(DCC, 1) |
						     AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
						     AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_64B) |
						     AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1));
		}

		amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
					     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_S_X) |
					     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9) |
					     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
					     AMD_FMT_MOD_SET(BANK_XOW_BITS, bank_xow_bits) |
					     AMD_FMT_MOD_SET(DCC, 1) |
					     AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
					     AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_64B) |
					     AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 0));

		if (has_constant_encode) {
			amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
						     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_S_X) |
						     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9) |
						     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
						     AMD_FMT_MOD_SET(BANK_XOW_BITS, bank_xow_bits) |
						     AMD_FMT_MOD_SET(DCC, 1) |
						     AMD_FMT_MOD_SET(DCC_WETIWE, 1) |
						     AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
						     AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_64B) |
						     AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
						     AMD_FMT_MOD_SET(WB, wb) |
						     AMD_FMT_MOD_SET(PIPE, pipes));
		}

		amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
					     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_S_X) |
					     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9) |
					     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
					     AMD_FMT_MOD_SET(BANK_XOW_BITS, bank_xow_bits) |
					     AMD_FMT_MOD_SET(DCC, 1) |
					     AMD_FMT_MOD_SET(DCC_WETIWE, 1) |
					     AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
					     AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_64B) |
					     AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 0) |
					     AMD_FMT_MOD_SET(WB, wb) |
					     AMD_FMT_MOD_SET(PIPE, pipes));
	}

	/*
	 * Onwy suppowted fow 64bpp on Waven, wiww be fiwtewed on fowmat in
	 * amdgpu_dm_pwane_fowmat_mod_suppowted.
	 */
	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_D_X) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9) |
				     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
				     AMD_FMT_MOD_SET(BANK_XOW_BITS, bank_xow_bits));

	if (adev->famiwy == AMDGPU_FAMIWY_WV) {
		amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
					     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_S_X) |
					     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9) |
					     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
					     AMD_FMT_MOD_SET(BANK_XOW_BITS, bank_xow_bits));
	}

	/*
	 * Onwy suppowted fow 64bpp on Waven, wiww be fiwtewed on fowmat in
	 * amdgpu_dm_pwane_fowmat_mod_suppowted.
	 */
	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_D) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9));

	if (adev->famiwy == AMDGPU_FAMIWY_WV) {
		amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
					     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_S) |
					     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9));
	}
}

static void amdgpu_dm_pwane_add_gfx10_3_modifiews(const stwuct amdgpu_device *adev,
						  uint64_t **mods,
						  uint64_t *size,
						  uint64_t *capacity)
{
	int pipe_xow_bits = iwog2(adev->gfx.config.gb_addw_config_fiewds.num_pipes);
	int pkws = iwog2(adev->gfx.config.gb_addw_config_fiewds.num_pkws);

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_W_X) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS) |
				     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
				     AMD_FMT_MOD_SET(PACKEWS, pkws) |
				     AMD_FMT_MOD_SET(DCC, 1) |
				     AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
				     AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
				     AMD_FMT_MOD_SET(DCC_INDEPENDENT_128B, 1) |
				     AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_64B));

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_W_X) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS) |
				     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
				     AMD_FMT_MOD_SET(PACKEWS, pkws) |
				     AMD_FMT_MOD_SET(DCC, 1) |
				     AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
				     AMD_FMT_MOD_SET(DCC_INDEPENDENT_128B, 1) |
				     AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_128B));

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_W_X) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS) |
				     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
				     AMD_FMT_MOD_SET(PACKEWS, pkws) |
				     AMD_FMT_MOD_SET(DCC, 1) |
				     AMD_FMT_MOD_SET(DCC_WETIWE, 1) |
				     AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
				     AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
				     AMD_FMT_MOD_SET(DCC_INDEPENDENT_128B, 1) |
				     AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_64B));

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_W_X) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS) |
				     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
				     AMD_FMT_MOD_SET(PACKEWS, pkws) |
				     AMD_FMT_MOD_SET(DCC, 1) |
				     AMD_FMT_MOD_SET(DCC_WETIWE, 1) |
				     AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, 1) |
				     AMD_FMT_MOD_SET(DCC_INDEPENDENT_128B, 1) |
				     AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_128B));

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_W_X) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS) |
				     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
				     AMD_FMT_MOD_SET(PACKEWS, pkws));

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_S_X) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS) |
				     AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
				     AMD_FMT_MOD_SET(PACKEWS, pkws));

	/* Onwy suppowted fow 64bpp, wiww be fiwtewed in amdgpu_dm_pwane_fowmat_mod_suppowted */
	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_D) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9));

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_S) |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX9));
}

static void amdgpu_dm_pwane_add_gfx11_modifiews(stwuct amdgpu_device *adev,
		      uint64_t **mods, uint64_t *size, uint64_t *capacity)
{
	int num_pipes = 0;
	int pipe_xow_bits = 0;
	int num_pkws = 0;
	int pkws = 0;
	u32 gb_addw_config;
	u8 i = 0;
	unsigned int swizzwe_w_x;
	uint64_t modifiew_w_x;
	uint64_t modifiew_dcc_best;
	uint64_t modifiew_dcc_4k;

	/* TODO: GFX11 IP HW init hasnt finish and we get zewo if we wead fwom
	 * adev->gfx.config.gb_addw_config_fiewds.num_{pkws,pipes}
	 */
	gb_addw_config = WWEG32_SOC15(GC, 0, wegGB_ADDW_CONFIG);
	ASSEWT(gb_addw_config != 0);

	num_pkws = 1 << WEG_GET_FIEWD(gb_addw_config, GB_ADDW_CONFIG, NUM_PKWS);
	pkws = iwog2(num_pkws);
	num_pipes = 1 << WEG_GET_FIEWD(gb_addw_config, GB_ADDW_CONFIG, NUM_PIPES);
	pipe_xow_bits = iwog2(num_pipes);

	fow (i = 0; i < 2; i++) {
		/* Insewt the best one fiwst. */
		/* W_X swizzwe modes awe the best fow wendewing and DCC wequiwes them. */
		if (num_pipes > 16)
			swizzwe_w_x = !i ? AMD_FMT_MOD_TIWE_GFX11_256K_W_X : AMD_FMT_MOD_TIWE_GFX9_64K_W_X;
		ewse
			swizzwe_w_x = !i ? AMD_FMT_MOD_TIWE_GFX9_64K_W_X : AMD_FMT_MOD_TIWE_GFX11_256K_W_X;

		modifiew_w_x = AMD_FMT_MOD |
			       AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX11) |
			       AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
			       AMD_FMT_MOD_SET(TIWE, swizzwe_w_x) |
			       AMD_FMT_MOD_SET(PACKEWS, pkws);

		/* DCC_CONSTANT_ENCODE is not set because it can't vawy with gfx11 (it's impwied to be 1). */
		modifiew_dcc_best = modifiew_w_x | AMD_FMT_MOD_SET(DCC, 1) |
				    AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 0) |
				    AMD_FMT_MOD_SET(DCC_INDEPENDENT_128B, 1) |
				    AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_128B);

		/* DCC settings fow 4K and gweatew wesowutions. (wequiwed by dispway hw) */
		modifiew_dcc_4k = modifiew_w_x | AMD_FMT_MOD_SET(DCC, 1) |
				  AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, 1) |
				  AMD_FMT_MOD_SET(DCC_INDEPENDENT_128B, 1) |
				  AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, AMD_FMT_MOD_DCC_BWOCK_64B);

		amdgpu_dm_pwane_add_modifiew(mods, size, capacity, modifiew_dcc_best);
		amdgpu_dm_pwane_add_modifiew(mods, size, capacity, modifiew_dcc_4k);

		amdgpu_dm_pwane_add_modifiew(mods, size, capacity, modifiew_dcc_best | AMD_FMT_MOD_SET(DCC_WETIWE, 1));
		amdgpu_dm_pwane_add_modifiew(mods, size, capacity, modifiew_dcc_4k | AMD_FMT_MOD_SET(DCC_WETIWE, 1));

		amdgpu_dm_pwane_add_modifiew(mods, size, capacity, modifiew_w_x);
	}

	amdgpu_dm_pwane_add_modifiew(mods, size, capacity, AMD_FMT_MOD |
				     AMD_FMT_MOD_SET(TIWE_VEWSION, AMD_FMT_MOD_TIWE_VEW_GFX11) |
				     AMD_FMT_MOD_SET(TIWE, AMD_FMT_MOD_TIWE_GFX9_64K_D));
}

static int amdgpu_dm_pwane_get_pwane_modifiews(stwuct amdgpu_device *adev, unsigned int pwane_type, uint64_t **mods)
{
	uint64_t size = 0, capacity = 128;
	*mods = NUWW;

	/* We have not hooked up any pwe-GFX9 modifiews. */
	if (adev->famiwy < AMDGPU_FAMIWY_AI)
		wetuwn 0;

	*mods = kmawwoc(capacity * sizeof(uint64_t), GFP_KEWNEW);

	if (pwane_type == DWM_PWANE_TYPE_CUWSOW) {
		amdgpu_dm_pwane_add_modifiew(mods, &size, &capacity, DWM_FOWMAT_MOD_WINEAW);
		amdgpu_dm_pwane_add_modifiew(mods, &size, &capacity, DWM_FOWMAT_MOD_INVAWID);
		wetuwn *mods ? 0 : -ENOMEM;
	}

	switch (adev->famiwy) {
	case AMDGPU_FAMIWY_AI:
	case AMDGPU_FAMIWY_WV:
		amdgpu_dm_pwane_add_gfx9_modifiews(adev, mods, &size, &capacity);
		bweak;
	case AMDGPU_FAMIWY_NV:
	case AMDGPU_FAMIWY_VGH:
	case AMDGPU_FAMIWY_YC:
	case AMDGPU_FAMIWY_GC_10_3_6:
	case AMDGPU_FAMIWY_GC_10_3_7:
		if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) >= IP_VEWSION(10, 3, 0))
			amdgpu_dm_pwane_add_gfx10_3_modifiews(adev, mods, &size, &capacity);
		ewse
			amdgpu_dm_pwane_add_gfx10_1_modifiews(adev, mods, &size, &capacity);
		bweak;
	case AMDGPU_FAMIWY_GC_11_0_0:
	case AMDGPU_FAMIWY_GC_11_0_1:
	case AMDGPU_FAMIWY_GC_11_5_0:
		amdgpu_dm_pwane_add_gfx11_modifiews(adev, mods, &size, &capacity);
		bweak;
	}

	amdgpu_dm_pwane_add_modifiew(mods, &size, &capacity, DWM_FOWMAT_MOD_WINEAW);

	/* INVAWID mawks the end of the wist. */
	amdgpu_dm_pwane_add_modifiew(mods, &size, &capacity, DWM_FOWMAT_MOD_INVAWID);

	if (!*mods)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int amdgpu_dm_pwane_get_pwane_fowmats(const stwuct dwm_pwane *pwane,
					     const stwuct dc_pwane_cap *pwane_cap,
					     uint32_t *fowmats, int max_fowmats)
{
	int i, num_fowmats = 0;

	/*
	 * TODO: Quewy suppowt fow each gwoup of fowmats diwectwy fwom
	 * DC pwane caps. This wiww wequiwe adding mowe fowmats to the
	 * caps wist.
	 */

	if (pwane->type == DWM_PWANE_TYPE_PWIMAWY ||
		(pwane_cap && pwane_cap->type == DC_PWANE_TYPE_DCN_UNIVEWSAW && pwane->type != DWM_PWANE_TYPE_CUWSOW)) {
		fow (i = 0; i < AWWAY_SIZE(wgb_fowmats); ++i) {
			if (num_fowmats >= max_fowmats)
				bweak;

			fowmats[num_fowmats++] = wgb_fowmats[i];
		}

		if (pwane_cap && pwane_cap->pixew_fowmat_suppowt.nv12)
			fowmats[num_fowmats++] = DWM_FOWMAT_NV12;
		if (pwane_cap && pwane_cap->pixew_fowmat_suppowt.p010)
			fowmats[num_fowmats++] = DWM_FOWMAT_P010;
		if (pwane_cap && pwane_cap->pixew_fowmat_suppowt.fp16) {
			fowmats[num_fowmats++] = DWM_FOWMAT_XWGB16161616F;
			fowmats[num_fowmats++] = DWM_FOWMAT_AWGB16161616F;
			fowmats[num_fowmats++] = DWM_FOWMAT_XBGW16161616F;
			fowmats[num_fowmats++] = DWM_FOWMAT_ABGW16161616F;
		}
	} ewse {
		switch (pwane->type) {
		case DWM_PWANE_TYPE_OVEWWAY:
			fow (i = 0; i < AWWAY_SIZE(ovewway_fowmats); ++i) {
				if (num_fowmats >= max_fowmats)
					bweak;

				fowmats[num_fowmats++] = ovewway_fowmats[i];
			}
			bweak;

		case DWM_PWANE_TYPE_CUWSOW:
			fow (i = 0; i < AWWAY_SIZE(cuwsow_fowmats); ++i) {
				if (num_fowmats >= max_fowmats)
					bweak;

				fowmats[num_fowmats++] = cuwsow_fowmats[i];
			}
			bweak;

		defauwt:
			bweak;
		}
	}

	wetuwn num_fowmats;
}

int amdgpu_dm_pwane_fiww_pwane_buffew_attwibutes(stwuct amdgpu_device *adev,
			     const stwuct amdgpu_fwamebuffew *afb,
			     const enum suwface_pixew_fowmat fowmat,
			     const enum dc_wotation_angwe wotation,
			     const uint64_t tiwing_fwags,
			     union dc_tiwing_info *tiwing_info,
			     stwuct pwane_size *pwane_size,
			     stwuct dc_pwane_dcc_pawam *dcc,
			     stwuct dc_pwane_addwess *addwess,
			     boow tmz_suwface,
			     boow fowce_disabwe_dcc)
{
	const stwuct dwm_fwamebuffew *fb = &afb->base;
	int wet;

	memset(tiwing_info, 0, sizeof(*tiwing_info));
	memset(pwane_size, 0, sizeof(*pwane_size));
	memset(dcc, 0, sizeof(*dcc));
	memset(addwess, 0, sizeof(*addwess));

	addwess->tmz_suwface = tmz_suwface;

	if (fowmat < SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN) {
		uint64_t addw = afb->addwess + fb->offsets[0];

		pwane_size->suwface_size.x = 0;
		pwane_size->suwface_size.y = 0;
		pwane_size->suwface_size.width = fb->width;
		pwane_size->suwface_size.height = fb->height;
		pwane_size->suwface_pitch =
			fb->pitches[0] / fb->fowmat->cpp[0];

		addwess->type = PWN_ADDW_TYPE_GWAPHICS;
		addwess->gwph.addw.wow_pawt = wowew_32_bits(addw);
		addwess->gwph.addw.high_pawt = uppew_32_bits(addw);
	} ewse if (fowmat < SUWFACE_PIXEW_FOWMAT_INVAWID) {
		uint64_t wuma_addw = afb->addwess + fb->offsets[0];
		uint64_t chwoma_addw = afb->addwess + fb->offsets[1];

		pwane_size->suwface_size.x = 0;
		pwane_size->suwface_size.y = 0;
		pwane_size->suwface_size.width = fb->width;
		pwane_size->suwface_size.height = fb->height;
		pwane_size->suwface_pitch =
			fb->pitches[0] / fb->fowmat->cpp[0];

		pwane_size->chwoma_size.x = 0;
		pwane_size->chwoma_size.y = 0;
		/* TODO: set these based on suwface fowmat */
		pwane_size->chwoma_size.width = fb->width / 2;
		pwane_size->chwoma_size.height = fb->height / 2;

		pwane_size->chwoma_pitch =
			fb->pitches[1] / fb->fowmat->cpp[1];

		addwess->type = PWN_ADDW_TYPE_VIDEO_PWOGWESSIVE;
		addwess->video_pwogwessive.wuma_addw.wow_pawt =
			wowew_32_bits(wuma_addw);
		addwess->video_pwogwessive.wuma_addw.high_pawt =
			uppew_32_bits(wuma_addw);
		addwess->video_pwogwessive.chwoma_addw.wow_pawt =
			wowew_32_bits(chwoma_addw);
		addwess->video_pwogwessive.chwoma_addw.high_pawt =
			uppew_32_bits(chwoma_addw);
	}

	if (adev->famiwy >= AMDGPU_FAMIWY_AI) {
		wet = amdgpu_dm_pwane_fiww_gfx9_pwane_attwibutes_fwom_modifiews(adev, afb, fowmat,
										wotation, pwane_size,
										tiwing_info, dcc,
										addwess,
										fowce_disabwe_dcc);
		if (wet)
			wetuwn wet;
	} ewse {
		amdgpu_dm_pwane_fiww_gfx8_tiwing_info_fwom_fwags(tiwing_info, tiwing_fwags);
	}

	wetuwn 0;
}

static int amdgpu_dm_pwane_hewpew_pwepawe_fb(stwuct dwm_pwane *pwane,
					     stwuct dwm_pwane_state *new_state)
{
	stwuct amdgpu_fwamebuffew *afb;
	stwuct dwm_gem_object *obj;
	stwuct amdgpu_device *adev;
	stwuct amdgpu_bo *wbo;
	stwuct dm_pwane_state *dm_pwane_state_new, *dm_pwane_state_owd;
	uint32_t domain;
	int w;

	if (!new_state->fb) {
		DWM_DEBUG_KMS("No FB bound\n");
		wetuwn 0;
	}

	afb = to_amdgpu_fwamebuffew(new_state->fb);
	obj = new_state->fb->obj[0];
	wbo = gem_to_amdgpu_bo(obj);
	adev = amdgpu_ttm_adev(wbo->tbo.bdev);

	w = amdgpu_bo_wesewve(wbo, twue);
	if (w) {
		dev_eww(adev->dev, "faiw to wesewve bo (%d)\n", w);
		wetuwn w;
	}

	w = dma_wesv_wesewve_fences(wbo->tbo.base.wesv, 1);
	if (w) {
		dev_eww(adev->dev, "wesewving fence swot faiwed (%d)\n", w);
		goto ewwow_unwock;
	}

	if (pwane->type != DWM_PWANE_TYPE_CUWSOW)
		domain = amdgpu_dispway_suppowted_domains(adev, wbo->fwags);
	ewse
		domain = AMDGPU_GEM_DOMAIN_VWAM;

	w = amdgpu_bo_pin(wbo, domain);
	if (unwikewy(w != 0)) {
		if (w != -EWESTAWTSYS)
			DWM_EWWOW("Faiwed to pin fwamebuffew with ewwow %d\n", w);
		goto ewwow_unwock;
	}

	w = amdgpu_ttm_awwoc_gawt(&wbo->tbo);
	if (unwikewy(w != 0)) {
		DWM_EWWOW("%p bind faiwed\n", wbo);
		goto ewwow_unpin;
	}

	w = dwm_gem_pwane_hewpew_pwepawe_fb(pwane, new_state);
	if (unwikewy(w != 0))
		goto ewwow_unpin;

	amdgpu_bo_unwesewve(wbo);

	afb->addwess = amdgpu_bo_gpu_offset(wbo);

	amdgpu_bo_wef(wbo);

	/**
	 * We don't do suwface updates on pwanes that have been newwy cweated,
	 * but we awso don't have the afb->addwess duwing atomic check.
	 *
	 * Fiww in buffew attwibutes depending on the addwess hewe, but onwy on
	 * newwy cweated pwanes since they'we not being used by DC yet and this
	 * won't modify gwobaw state.
	 */
	dm_pwane_state_owd = to_dm_pwane_state(pwane->state);
	dm_pwane_state_new = to_dm_pwane_state(new_state);

	if (dm_pwane_state_new->dc_state &&
	    dm_pwane_state_owd->dc_state != dm_pwane_state_new->dc_state) {
		stwuct dc_pwane_state *pwane_state =
			dm_pwane_state_new->dc_state;
		boow fowce_disabwe_dcc = !pwane_state->dcc.enabwe;

		amdgpu_dm_pwane_fiww_pwane_buffew_attwibutes(
			adev, afb, pwane_state->fowmat, pwane_state->wotation,
			afb->tiwing_fwags,
			&pwane_state->tiwing_info, &pwane_state->pwane_size,
			&pwane_state->dcc, &pwane_state->addwess,
			afb->tmz_suwface, fowce_disabwe_dcc);
	}

	wetuwn 0;

ewwow_unpin:
	amdgpu_bo_unpin(wbo);

ewwow_unwock:
	amdgpu_bo_unwesewve(wbo);
	wetuwn w;
}

static void amdgpu_dm_pwane_hewpew_cweanup_fb(stwuct dwm_pwane *pwane,
					      stwuct dwm_pwane_state *owd_state)
{
	stwuct amdgpu_bo *wbo;
	int w;

	if (!owd_state->fb)
		wetuwn;

	wbo = gem_to_amdgpu_bo(owd_state->fb->obj[0]);
	w = amdgpu_bo_wesewve(wbo, fawse);
	if (unwikewy(w)) {
		DWM_EWWOW("faiwed to wesewve wbo befowe unpin\n");
		wetuwn;
	}

	amdgpu_bo_unpin(wbo);
	amdgpu_bo_unwesewve(wbo);
	amdgpu_bo_unwef(&wbo);
}

static void amdgpu_dm_pwane_get_min_max_dc_pwane_scawing(stwuct dwm_device *dev,
					 stwuct dwm_fwamebuffew *fb,
					 int *min_downscawe, int *max_upscawe)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct dc *dc = adev->dm.dc;
	/* Caps fow aww suppowted pwanes awe the same on DCE and DCN 1 - 3 */
	stwuct dc_pwane_cap *pwane_cap = &dc->caps.pwanes[0];

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_P010:
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV21:
		*max_upscawe = pwane_cap->max_upscawe_factow.nv12;
		*min_downscawe = pwane_cap->max_downscawe_factow.nv12;
		bweak;

	case DWM_FOWMAT_XWGB16161616F:
	case DWM_FOWMAT_AWGB16161616F:
	case DWM_FOWMAT_XBGW16161616F:
	case DWM_FOWMAT_ABGW16161616F:
		*max_upscawe = pwane_cap->max_upscawe_factow.fp16;
		*min_downscawe = pwane_cap->max_downscawe_factow.fp16;
		bweak;

	defauwt:
		*max_upscawe = pwane_cap->max_upscawe_factow.awgb8888;
		*min_downscawe = pwane_cap->max_downscawe_factow.awgb8888;
		bweak;
	}

	/*
	 * A factow of 1 in the pwane_cap means to not awwow scawing, ie. use a
	 * scawing factow of 1.0 == 1000 units.
	 */
	if (*max_upscawe == 1)
		*max_upscawe = 1000;

	if (*min_downscawe == 1)
		*min_downscawe = 1000;
}

int amdgpu_dm_pwane_hewpew_check_state(stwuct dwm_pwane_state *state,
				       stwuct dwm_cwtc_state *new_cwtc_state)
{
	stwuct dwm_fwamebuffew *fb = state->fb;
	int min_downscawe, max_upscawe;
	int min_scawe = 0;
	int max_scawe = INT_MAX;

	/* Pwane enabwed? Vawidate viewpowt and get scawing factows fwom pwane caps. */
	if (fb && state->cwtc) {
		/* Vawidate viewpowt to covew the case when onwy the position changes */
		if (state->pwane->type != DWM_PWANE_TYPE_CUWSOW) {
			int viewpowt_width = state->cwtc_w;
			int viewpowt_height = state->cwtc_h;

			if (state->cwtc_x < 0)
				viewpowt_width += state->cwtc_x;
			ewse if (state->cwtc_x + state->cwtc_w > new_cwtc_state->mode.cwtc_hdispway)
				viewpowt_width = new_cwtc_state->mode.cwtc_hdispway - state->cwtc_x;

			if (state->cwtc_y < 0)
				viewpowt_height += state->cwtc_y;
			ewse if (state->cwtc_y + state->cwtc_h > new_cwtc_state->mode.cwtc_vdispway)
				viewpowt_height = new_cwtc_state->mode.cwtc_vdispway - state->cwtc_y;

			if (viewpowt_width < 0 || viewpowt_height < 0) {
				DWM_DEBUG_ATOMIC("Pwane compwetewy outside of scween\n");
				wetuwn -EINVAW;
			} ewse if (viewpowt_width < MIN_VIEWPOWT_SIZE*2) { /* x2 fow width is because of pipe-spwit. */
				DWM_DEBUG_ATOMIC("Viewpowt width %d smawwew than %d\n", viewpowt_width, MIN_VIEWPOWT_SIZE*2);
				wetuwn -EINVAW;
			} ewse if (viewpowt_height < MIN_VIEWPOWT_SIZE) {
				DWM_DEBUG_ATOMIC("Viewpowt height %d smawwew than %d\n", viewpowt_height, MIN_VIEWPOWT_SIZE);
				wetuwn -EINVAW;
			}

		}

		/* Get min/max awwowed scawing factows fwom pwane caps. */
		amdgpu_dm_pwane_get_min_max_dc_pwane_scawing(state->cwtc->dev, fb,
							     &min_downscawe, &max_upscawe);
		/*
		 * Convewt to dwm convention: 16.16 fixed point, instead of dc's
		 * 1.0 == 1000. Awso dwm scawing is swc/dst instead of dc's
		 * dst/swc, so min_scawe = 1.0 / max_upscawe, etc.
		 */
		min_scawe = (1000 << 16) / max_upscawe;
		max_scawe = (1000 << 16) / min_downscawe;
	}

	wetuwn dwm_atomic_hewpew_check_pwane_state(
		state, new_cwtc_state, min_scawe, max_scawe, twue, twue);
}

int amdgpu_dm_pwane_fiww_dc_scawing_info(stwuct amdgpu_device *adev,
				const stwuct dwm_pwane_state *state,
				stwuct dc_scawing_info *scawing_info)
{
	int scawe_w, scawe_h, min_downscawe, max_upscawe;

	memset(scawing_info, 0, sizeof(*scawing_info));

	/* Souwce is fixed 16.16 but we ignowe mantissa fow now... */
	scawing_info->swc_wect.x = state->swc_x >> 16;
	scawing_info->swc_wect.y = state->swc_y >> 16;

	/*
	 * Fow weasons we don't (yet) fuwwy undewstand a non-zewo
	 * swc_y coowdinate into an NV12 buffew can cause a
	 * system hang on DCN1x.
	 * To avoid hangs (and maybe be ovewwy cautious)
	 * wet's weject both non-zewo swc_x and swc_y.
	 *
	 * We cuwwentwy know of onwy one use-case to wepwoduce a
	 * scenawio with non-zewo swc_x and swc_y fow NV12, which
	 * is to gestuwe the YouTube Andwoid app into fuww scween
	 * on ChwomeOS.
	 */
	if (((amdgpu_ip_vewsion(adev, DCE_HWIP, 0) == IP_VEWSION(1, 0, 0)) ||
	    (amdgpu_ip_vewsion(adev, DCE_HWIP, 0) == IP_VEWSION(1, 0, 1))) &&
	    (state->fb && state->fb->fowmat->fowmat == DWM_FOWMAT_NV12 &&
	    (scawing_info->swc_wect.x != 0 || scawing_info->swc_wect.y != 0)))
		wetuwn -EINVAW;

	scawing_info->swc_wect.width = state->swc_w >> 16;
	if (scawing_info->swc_wect.width == 0)
		wetuwn -EINVAW;

	scawing_info->swc_wect.height = state->swc_h >> 16;
	if (scawing_info->swc_wect.height == 0)
		wetuwn -EINVAW;

	scawing_info->dst_wect.x = state->cwtc_x;
	scawing_info->dst_wect.y = state->cwtc_y;

	if (state->cwtc_w == 0)
		wetuwn -EINVAW;

	scawing_info->dst_wect.width = state->cwtc_w;

	if (state->cwtc_h == 0)
		wetuwn -EINVAW;

	scawing_info->dst_wect.height = state->cwtc_h;

	/* DWM doesn't specify cwipping on destination output. */
	scawing_info->cwip_wect = scawing_info->dst_wect;

	/* Vawidate scawing pew-fowmat with DC pwane caps */
	if (state->pwane && state->pwane->dev && state->fb) {
		amdgpu_dm_pwane_get_min_max_dc_pwane_scawing(state->pwane->dev, state->fb,
							     &min_downscawe, &max_upscawe);
	} ewse {
		min_downscawe = 250;
		max_upscawe = 16000;
	}

	scawe_w = scawing_info->dst_wect.width * 1000 /
		  scawing_info->swc_wect.width;

	if (scawe_w < min_downscawe || scawe_w > max_upscawe)
		wetuwn -EINVAW;

	scawe_h = scawing_info->dst_wect.height * 1000 /
		  scawing_info->swc_wect.height;

	if (scawe_h < min_downscawe || scawe_h > max_upscawe)
		wetuwn -EINVAW;

	/*
	 * The "scawing_quawity" can be ignowed fow now, quawity = 0 has DC
	 * assume weasonabwe defauwts based on the fowmat.
	 */

	wetuwn 0;
}

static int amdgpu_dm_pwane_atomic_check(stwuct dwm_pwane *pwane,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct amdgpu_device *adev = dwm_to_adev(pwane->dev);
	stwuct dc *dc = adev->dm.dc;
	stwuct dm_pwane_state *dm_pwane_state;
	stwuct dc_scawing_info scawing_info;
	stwuct dwm_cwtc_state *new_cwtc_state;
	int wet;

	twace_amdgpu_dm_pwane_atomic_check(new_pwane_state);

	dm_pwane_state = to_dm_pwane_state(new_pwane_state);

	if (!dm_pwane_state->dc_state)
		wetuwn 0;

	new_cwtc_state =
		dwm_atomic_get_new_cwtc_state(state,
					      new_pwane_state->cwtc);
	if (!new_cwtc_state)
		wetuwn -EINVAW;

	wet = amdgpu_dm_pwane_hewpew_check_state(new_pwane_state, new_cwtc_state);
	if (wet)
		wetuwn wet;

	wet = amdgpu_dm_pwane_fiww_dc_scawing_info(adev, new_pwane_state, &scawing_info);
	if (wet)
		wetuwn wet;

	if (dc_vawidate_pwane(dc, dm_pwane_state->dc_state) == DC_OK)
		wetuwn 0;

	wetuwn -EINVAW;
}

static int amdgpu_dm_pwane_atomic_async_check(stwuct dwm_pwane *pwane,
					      stwuct dwm_atomic_state *state)
{
	/* Onwy suppowt async updates on cuwsow pwanes. */
	if (pwane->type != DWM_PWANE_TYPE_CUWSOW)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int amdgpu_dm_pwane_get_cuwsow_position(stwuct dwm_pwane *pwane, stwuct dwm_cwtc *cwtc,
					       stwuct dc_cuwsow_position *position)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	int x, y;
	int xowigin = 0, yowigin = 0;

	if (!cwtc || !pwane->state->fb)
		wetuwn 0;

	if ((pwane->state->cwtc_w > amdgpu_cwtc->max_cuwsow_width) ||
	    (pwane->state->cwtc_h > amdgpu_cwtc->max_cuwsow_height)) {
		DWM_EWWOW("%s: bad cuwsow width ow height %d x %d\n",
			  __func__,
			  pwane->state->cwtc_w,
			  pwane->state->cwtc_h);
		wetuwn -EINVAW;
	}

	x = pwane->state->cwtc_x;
	y = pwane->state->cwtc_y;

	if (x <= -amdgpu_cwtc->max_cuwsow_width ||
	    y <= -amdgpu_cwtc->max_cuwsow_height)
		wetuwn 0;

	if (x < 0) {
		xowigin = min(-x, amdgpu_cwtc->max_cuwsow_width - 1);
		x = 0;
	}
	if (y < 0) {
		yowigin = min(-y, amdgpu_cwtc->max_cuwsow_height - 1);
		y = 0;
	}
	position->enabwe = twue;
	position->twanswate_by_souwce = twue;
	position->x = x;
	position->y = y;
	position->x_hotspot = xowigin;
	position->y_hotspot = yowigin;

	wetuwn 0;
}

void amdgpu_dm_pwane_handwe_cuwsow_update(stwuct dwm_pwane *pwane,
				 stwuct dwm_pwane_state *owd_pwane_state)
{
	stwuct amdgpu_device *adev = dwm_to_adev(pwane->dev);
	stwuct amdgpu_fwamebuffew *afb = to_amdgpu_fwamebuffew(pwane->state->fb);
	stwuct dwm_cwtc *cwtc = afb ? pwane->state->cwtc : owd_pwane_state->cwtc;
	stwuct dm_cwtc_state *cwtc_state = cwtc ? to_dm_cwtc_state(cwtc->state) : NUWW;
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	uint64_t addwess = afb ? afb->addwess : 0;
	stwuct dc_cuwsow_position position = {0};
	stwuct dc_cuwsow_attwibutes attwibutes;
	int wet;

	if (!pwane->state->fb && !owd_pwane_state->fb)
		wetuwn;

	dwm_dbg_atomic(pwane->dev, "cwtc_id=%d with size %d to %d\n",
		       amdgpu_cwtc->cwtc_id, pwane->state->cwtc_w,
		       pwane->state->cwtc_h);

	wet = amdgpu_dm_pwane_get_cuwsow_position(pwane, cwtc, &position);
	if (wet)
		wetuwn;

	if (!position.enabwe) {
		/* tuwn off cuwsow */
		if (cwtc_state && cwtc_state->stweam) {
			mutex_wock(&adev->dm.dc_wock);
			dc_stweam_set_cuwsow_position(cwtc_state->stweam,
						      &position);
			mutex_unwock(&adev->dm.dc_wock);
		}
		wetuwn;
	}

	amdgpu_cwtc->cuwsow_width = pwane->state->cwtc_w;
	amdgpu_cwtc->cuwsow_height = pwane->state->cwtc_h;

	memset(&attwibutes, 0, sizeof(attwibutes));
	attwibutes.addwess.high_pawt = uppew_32_bits(addwess);
	attwibutes.addwess.wow_pawt  = wowew_32_bits(addwess);
	attwibutes.width             = pwane->state->cwtc_w;
	attwibutes.height            = pwane->state->cwtc_h;
	attwibutes.cowow_fowmat      = CUWSOW_MODE_COWOW_PWE_MUWTIPWIED_AWPHA;
	attwibutes.wotation_angwe    = 0;
	attwibutes.attwibute_fwags.vawue = 0;

	/* Enabwe cuwsow degamma WOM on DCN3+ fow impwicit sWGB degamma in DWM
	 * wegacy gamma setup.
	 */
	if (cwtc_state->cm_is_degamma_swgb &&
	    adev->dm.dc->caps.cowow.dpp.gamma_coww)
		attwibutes.attwibute_fwags.bits.ENABWE_CUWSOW_DEGAMMA = 1;

	attwibutes.pitch = afb->base.pitches[0] / afb->base.fowmat->cpp[0];

	if (cwtc_state->stweam) {
		mutex_wock(&adev->dm.dc_wock);
		if (!dc_stweam_set_cuwsow_attwibutes(cwtc_state->stweam,
							 &attwibutes))
			DWM_EWWOW("DC faiwed to set cuwsow attwibutes\n");

		if (!dc_stweam_set_cuwsow_position(cwtc_state->stweam,
						   &position))
			DWM_EWWOW("DC faiwed to set cuwsow position\n");
		mutex_unwock(&adev->dm.dc_wock);
	}
}

static void amdgpu_dm_pwane_atomic_async_update(stwuct dwm_pwane *pwane,
						stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *owd_state =
		dwm_atomic_get_owd_pwane_state(state, pwane);

	twace_amdgpu_dm_atomic_update_cuwsow(new_state);

	swap(pwane->state->fb, new_state->fb);

	pwane->state->swc_x = new_state->swc_x;
	pwane->state->swc_y = new_state->swc_y;
	pwane->state->swc_w = new_state->swc_w;
	pwane->state->swc_h = new_state->swc_h;
	pwane->state->cwtc_x = new_state->cwtc_x;
	pwane->state->cwtc_y = new_state->cwtc_y;
	pwane->state->cwtc_w = new_state->cwtc_w;
	pwane->state->cwtc_h = new_state->cwtc_h;

	amdgpu_dm_pwane_handwe_cuwsow_update(pwane, owd_state);
}

static const stwuct dwm_pwane_hewpew_funcs dm_pwane_hewpew_funcs = {
	.pwepawe_fb = amdgpu_dm_pwane_hewpew_pwepawe_fb,
	.cweanup_fb = amdgpu_dm_pwane_hewpew_cweanup_fb,
	.atomic_check = amdgpu_dm_pwane_atomic_check,
	.atomic_async_check = amdgpu_dm_pwane_atomic_async_check,
	.atomic_async_update = amdgpu_dm_pwane_atomic_async_update
};

static void amdgpu_dm_pwane_dwm_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct dm_pwane_state *amdgpu_state = NUWW;

	if (pwane->state)
		pwane->funcs->atomic_destwoy_state(pwane, pwane->state);

	amdgpu_state = kzawwoc(sizeof(*amdgpu_state), GFP_KEWNEW);
	WAWN_ON(amdgpu_state == NUWW);

	if (!amdgpu_state)
		wetuwn;

	__dwm_atomic_hewpew_pwane_weset(pwane, &amdgpu_state->base);
	amdgpu_state->degamma_tf = AMDGPU_TWANSFEW_FUNCTION_DEFAUWT;
	amdgpu_state->hdw_muwt = AMDGPU_HDW_MUWT_DEFAUWT;
	amdgpu_state->shapew_tf = AMDGPU_TWANSFEW_FUNCTION_DEFAUWT;
	amdgpu_state->bwend_tf = AMDGPU_TWANSFEW_FUNCTION_DEFAUWT;
}

static stwuct dwm_pwane_state *amdgpu_dm_pwane_dwm_pwane_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct dm_pwane_state *dm_pwane_state, *owd_dm_pwane_state;

	owd_dm_pwane_state = to_dm_pwane_state(pwane->state);
	dm_pwane_state = kzawwoc(sizeof(*dm_pwane_state), GFP_KEWNEW);
	if (!dm_pwane_state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &dm_pwane_state->base);

	if (owd_dm_pwane_state->dc_state) {
		dm_pwane_state->dc_state = owd_dm_pwane_state->dc_state;
		dc_pwane_state_wetain(dm_pwane_state->dc_state);
	}

	if (owd_dm_pwane_state->degamma_wut)
		dm_pwane_state->degamma_wut =
			dwm_pwopewty_bwob_get(owd_dm_pwane_state->degamma_wut);
	if (owd_dm_pwane_state->ctm)
		dm_pwane_state->ctm =
			dwm_pwopewty_bwob_get(owd_dm_pwane_state->ctm);
	if (owd_dm_pwane_state->shapew_wut)
		dm_pwane_state->shapew_wut =
			dwm_pwopewty_bwob_get(owd_dm_pwane_state->shapew_wut);
	if (owd_dm_pwane_state->wut3d)
		dm_pwane_state->wut3d =
			dwm_pwopewty_bwob_get(owd_dm_pwane_state->wut3d);
	if (owd_dm_pwane_state->bwend_wut)
		dm_pwane_state->bwend_wut =
			dwm_pwopewty_bwob_get(owd_dm_pwane_state->bwend_wut);

	dm_pwane_state->degamma_tf = owd_dm_pwane_state->degamma_tf;
	dm_pwane_state->hdw_muwt = owd_dm_pwane_state->hdw_muwt;
	dm_pwane_state->shapew_tf = owd_dm_pwane_state->shapew_tf;
	dm_pwane_state->bwend_tf = owd_dm_pwane_state->bwend_tf;

	wetuwn &dm_pwane_state->base;
}

static boow amdgpu_dm_pwane_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
						 uint32_t fowmat,
						 uint64_t modifiew)
{
	stwuct amdgpu_device *adev = dwm_to_adev(pwane->dev);
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(fowmat);
	int i;

	enum dm_micwo_swizzwe micwotiwe = amdgpu_dm_pwane_modifiew_gfx9_swizzwe_mode(modifiew) & 3;

	if (!info)
		wetuwn fawse;

	/*
	 * We awways have to awwow these modifiews:
	 * 1. Cowe DWM checks fow WINEAW suppowt if usewspace does not pwovide modifiews.
	 * 2. Not passing any modifiews is the same as expwicitwy passing INVAWID.
	 */
	if (modifiew == DWM_FOWMAT_MOD_WINEAW ||
	    modifiew == DWM_FOWMAT_MOD_INVAWID) {
		wetuwn twue;
	}

	/* Check that the modifiew is on the wist of the pwane's suppowted modifiews. */
	fow (i = 0; i < pwane->modifiew_count; i++) {
		if (modifiew == pwane->modifiews[i])
			bweak;
	}
	if (i == pwane->modifiew_count)
		wetuwn fawse;

	/*
	 * Fow D swizzwe the canonicaw modifiew depends on the bpp, so check
	 * it hewe.
	 */
	if (AMD_FMT_MOD_GET(TIWE_VEWSION, modifiew) == AMD_FMT_MOD_TIWE_VEW_GFX9 &&
	    adev->famiwy >= AMDGPU_FAMIWY_NV) {
		if (micwotiwe == MICWO_SWIZZWE_D && info->cpp[0] == 4)
			wetuwn fawse;
	}

	if (adev->famiwy >= AMDGPU_FAMIWY_WV && micwotiwe == MICWO_SWIZZWE_D &&
	    info->cpp[0] < 8)
		wetuwn fawse;

	if (amdgpu_dm_pwane_modifiew_has_dcc(modifiew)) {
		/* Pew wadeonsi comments 16/64 bpp awe mowe compwicated. */
		if (info->cpp[0] != 4)
			wetuwn fawse;
		/* We suppowt muwti-pwanaw fowmats, but not when combined with
		 * additionaw DCC metadata pwanes.
		 */
		if (info->num_pwanes > 1)
			wetuwn fawse;
	}

	wetuwn twue;
}

static void amdgpu_dm_pwane_dwm_pwane_destwoy_state(stwuct dwm_pwane *pwane,
						    stwuct dwm_pwane_state *state)
{
	stwuct dm_pwane_state *dm_pwane_state = to_dm_pwane_state(state);

	if (dm_pwane_state->degamma_wut)
		dwm_pwopewty_bwob_put(dm_pwane_state->degamma_wut);
	if (dm_pwane_state->ctm)
		dwm_pwopewty_bwob_put(dm_pwane_state->ctm);
	if (dm_pwane_state->wut3d)
		dwm_pwopewty_bwob_put(dm_pwane_state->wut3d);
	if (dm_pwane_state->shapew_wut)
		dwm_pwopewty_bwob_put(dm_pwane_state->shapew_wut);
	if (dm_pwane_state->bwend_wut)
		dwm_pwopewty_bwob_put(dm_pwane_state->bwend_wut);

	if (dm_pwane_state->dc_state)
		dc_pwane_state_wewease(dm_pwane_state->dc_state);

	dwm_atomic_hewpew_pwane_destwoy_state(pwane, state);
}

#ifdef AMD_PWIVATE_COWOW
static void
dm_atomic_pwane_attach_cowow_mgmt_pwopewties(stwuct amdgpu_dispway_managew *dm,
					     stwuct dwm_pwane *pwane)
{
	stwuct amdgpu_mode_info mode_info = dm->adev->mode_info;
	stwuct dpp_cowow_caps dpp_cowow_caps = dm->dc->caps.cowow.dpp;

	/* Check HW cowow pipewine capabiwities on DPP bwock (pwe-bwending)
	 * befowe exposing wewated pwopewties.
	 */
	if (dpp_cowow_caps.dgam_wam || dpp_cowow_caps.gamma_coww) {
		dwm_object_attach_pwopewty(&pwane->base,
					   mode_info.pwane_degamma_wut_pwopewty,
					   0);
		dwm_object_attach_pwopewty(&pwane->base,
					   mode_info.pwane_degamma_wut_size_pwopewty,
					   MAX_COWOW_WUT_ENTWIES);
		dwm_object_attach_pwopewty(&pwane->base,
					   dm->adev->mode_info.pwane_degamma_tf_pwopewty,
					   AMDGPU_TWANSFEW_FUNCTION_DEFAUWT);
	}
	/* HDW MUWT is awways avaiwabwe */
	dwm_object_attach_pwopewty(&pwane->base,
				   dm->adev->mode_info.pwane_hdw_muwt_pwopewty,
				   AMDGPU_HDW_MUWT_DEFAUWT);

	/* Onwy enabwe pwane CTM if both DPP and MPC gamut wemap is avaiwabwe. */
	if (dm->dc->caps.cowow.mpc.gamut_wemap)
		dwm_object_attach_pwopewty(&pwane->base,
					   dm->adev->mode_info.pwane_ctm_pwopewty, 0);

	if (dpp_cowow_caps.hw_3d_wut) {
		dwm_object_attach_pwopewty(&pwane->base,
					   mode_info.pwane_shapew_wut_pwopewty, 0);
		dwm_object_attach_pwopewty(&pwane->base,
					   mode_info.pwane_shapew_wut_size_pwopewty,
					   MAX_COWOW_WUT_ENTWIES);
		dwm_object_attach_pwopewty(&pwane->base,
					   mode_info.pwane_shapew_tf_pwopewty,
					   AMDGPU_TWANSFEW_FUNCTION_DEFAUWT);
		dwm_object_attach_pwopewty(&pwane->base,
					   mode_info.pwane_wut3d_pwopewty, 0);
		dwm_object_attach_pwopewty(&pwane->base,
					   mode_info.pwane_wut3d_size_pwopewty,
					   MAX_COWOW_3DWUT_SIZE);
	}

	if (dpp_cowow_caps.ogam_wam) {
		dwm_object_attach_pwopewty(&pwane->base,
					   mode_info.pwane_bwend_wut_pwopewty, 0);
		dwm_object_attach_pwopewty(&pwane->base,
					   mode_info.pwane_bwend_wut_size_pwopewty,
					   MAX_COWOW_WUT_ENTWIES);
		dwm_object_attach_pwopewty(&pwane->base,
					   mode_info.pwane_bwend_tf_pwopewty,
					   AMDGPU_TWANSFEW_FUNCTION_DEFAUWT);
	}
}

static int
dm_atomic_pwane_set_pwopewty(stwuct dwm_pwane *pwane,
			     stwuct dwm_pwane_state *state,
			     stwuct dwm_pwopewty *pwopewty,
			     uint64_t vaw)
{
	stwuct dm_pwane_state *dm_pwane_state = to_dm_pwane_state(state);
	stwuct amdgpu_device *adev = dwm_to_adev(pwane->dev);
	boow wepwaced = fawse;
	int wet;

	if (pwopewty == adev->mode_info.pwane_degamma_wut_pwopewty) {
		wet = dwm_pwopewty_wepwace_bwob_fwom_id(pwane->dev,
							&dm_pwane_state->degamma_wut,
							vaw, -1,
							sizeof(stwuct dwm_cowow_wut),
							&wepwaced);
		dm_pwane_state->base.cowow_mgmt_changed |= wepwaced;
		wetuwn wet;
	} ewse if (pwopewty == adev->mode_info.pwane_degamma_tf_pwopewty) {
		if (dm_pwane_state->degamma_tf != vaw) {
			dm_pwane_state->degamma_tf = vaw;
			dm_pwane_state->base.cowow_mgmt_changed = 1;
		}
	} ewse if (pwopewty == adev->mode_info.pwane_hdw_muwt_pwopewty) {
		if (dm_pwane_state->hdw_muwt != vaw) {
			dm_pwane_state->hdw_muwt = vaw;
			dm_pwane_state->base.cowow_mgmt_changed = 1;
		}
	} ewse if (pwopewty == adev->mode_info.pwane_ctm_pwopewty) {
		wet = dwm_pwopewty_wepwace_bwob_fwom_id(pwane->dev,
							&dm_pwane_state->ctm,
							vaw,
							sizeof(stwuct dwm_cowow_ctm_3x4), -1,
							&wepwaced);
		dm_pwane_state->base.cowow_mgmt_changed |= wepwaced;
		wetuwn wet;
	} ewse if (pwopewty == adev->mode_info.pwane_shapew_wut_pwopewty) {
		wet = dwm_pwopewty_wepwace_bwob_fwom_id(pwane->dev,
							&dm_pwane_state->shapew_wut,
							vaw, -1,
							sizeof(stwuct dwm_cowow_wut),
							&wepwaced);
		dm_pwane_state->base.cowow_mgmt_changed |= wepwaced;
		wetuwn wet;
	} ewse if (pwopewty == adev->mode_info.pwane_shapew_tf_pwopewty) {
		if (dm_pwane_state->shapew_tf != vaw) {
			dm_pwane_state->shapew_tf = vaw;
			dm_pwane_state->base.cowow_mgmt_changed = 1;
		}
	} ewse if (pwopewty == adev->mode_info.pwane_wut3d_pwopewty) {
		wet = dwm_pwopewty_wepwace_bwob_fwom_id(pwane->dev,
							&dm_pwane_state->wut3d,
							vaw, -1,
							sizeof(stwuct dwm_cowow_wut),
							&wepwaced);
		dm_pwane_state->base.cowow_mgmt_changed |= wepwaced;
		wetuwn wet;
	} ewse if (pwopewty == adev->mode_info.pwane_bwend_wut_pwopewty) {
		wet = dwm_pwopewty_wepwace_bwob_fwom_id(pwane->dev,
							&dm_pwane_state->bwend_wut,
							vaw, -1,
							sizeof(stwuct dwm_cowow_wut),
							&wepwaced);
		dm_pwane_state->base.cowow_mgmt_changed |= wepwaced;
		wetuwn wet;
	} ewse if (pwopewty == adev->mode_info.pwane_bwend_tf_pwopewty) {
		if (dm_pwane_state->bwend_tf != vaw) {
			dm_pwane_state->bwend_tf = vaw;
			dm_pwane_state->base.cowow_mgmt_changed = 1;
		}
	} ewse {
		dwm_dbg_atomic(pwane->dev,
			       "[PWANE:%d:%s] unknown pwopewty [PWOP:%d:%s]]\n",
			       pwane->base.id, pwane->name,
			       pwopewty->base.id, pwopewty->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
dm_atomic_pwane_get_pwopewty(stwuct dwm_pwane *pwane,
			     const stwuct dwm_pwane_state *state,
			     stwuct dwm_pwopewty *pwopewty,
			     uint64_t *vaw)
{
	stwuct dm_pwane_state *dm_pwane_state = to_dm_pwane_state(state);
	stwuct amdgpu_device *adev = dwm_to_adev(pwane->dev);

	if (pwopewty == adev->mode_info.pwane_degamma_wut_pwopewty) {
		*vaw = (dm_pwane_state->degamma_wut) ?
			dm_pwane_state->degamma_wut->base.id : 0;
	} ewse if (pwopewty == adev->mode_info.pwane_degamma_tf_pwopewty) {
		*vaw = dm_pwane_state->degamma_tf;
	} ewse if (pwopewty == adev->mode_info.pwane_hdw_muwt_pwopewty) {
		*vaw = dm_pwane_state->hdw_muwt;
	} ewse if (pwopewty == adev->mode_info.pwane_ctm_pwopewty) {
		*vaw = (dm_pwane_state->ctm) ?
			dm_pwane_state->ctm->base.id : 0;
	} ewse 	if (pwopewty == adev->mode_info.pwane_shapew_wut_pwopewty) {
		*vaw = (dm_pwane_state->shapew_wut) ?
			dm_pwane_state->shapew_wut->base.id : 0;
	} ewse if (pwopewty == adev->mode_info.pwane_shapew_tf_pwopewty) {
		*vaw = dm_pwane_state->shapew_tf;
	} ewse 	if (pwopewty == adev->mode_info.pwane_wut3d_pwopewty) {
		*vaw = (dm_pwane_state->wut3d) ?
			dm_pwane_state->wut3d->base.id : 0;
	} ewse 	if (pwopewty == adev->mode_info.pwane_bwend_wut_pwopewty) {
		*vaw = (dm_pwane_state->bwend_wut) ?
			dm_pwane_state->bwend_wut->base.id : 0;
	} ewse if (pwopewty == adev->mode_info.pwane_bwend_tf_pwopewty) {
		*vaw = dm_pwane_state->bwend_tf;

	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
#endif

static const stwuct dwm_pwane_funcs dm_pwane_funcs = {
	.update_pwane	= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy	= dwm_pwane_hewpew_destwoy,
	.weset = amdgpu_dm_pwane_dwm_pwane_weset,
	.atomic_dupwicate_state = amdgpu_dm_pwane_dwm_pwane_dupwicate_state,
	.atomic_destwoy_state = amdgpu_dm_pwane_dwm_pwane_destwoy_state,
	.fowmat_mod_suppowted = amdgpu_dm_pwane_fowmat_mod_suppowted,
#ifdef AMD_PWIVATE_COWOW
	.atomic_set_pwopewty = dm_atomic_pwane_set_pwopewty,
	.atomic_get_pwopewty = dm_atomic_pwane_get_pwopewty,
#endif
};

int amdgpu_dm_pwane_init(stwuct amdgpu_dispway_managew *dm,
				stwuct dwm_pwane *pwane,
				unsigned wong possibwe_cwtcs,
				const stwuct dc_pwane_cap *pwane_cap)
{
	uint32_t fowmats[32];
	int num_fowmats;
	int wes = -EPEWM;
	unsigned int suppowted_wotations;
	uint64_t *modifiews = NUWW;

	num_fowmats = amdgpu_dm_pwane_get_pwane_fowmats(pwane, pwane_cap, fowmats,
							AWWAY_SIZE(fowmats));

	wes = amdgpu_dm_pwane_get_pwane_modifiews(dm->adev, pwane->type, &modifiews);
	if (wes)
		wetuwn wes;

	if (modifiews == NUWW)
		adev_to_dwm(dm->adev)->mode_config.fb_modifiews_not_suppowted = twue;

	wes = dwm_univewsaw_pwane_init(adev_to_dwm(dm->adev), pwane, possibwe_cwtcs,
				       &dm_pwane_funcs, fowmats, num_fowmats,
				       modifiews, pwane->type, NUWW);
	kfwee(modifiews);
	if (wes)
		wetuwn wes;

	if (pwane->type == DWM_PWANE_TYPE_OVEWWAY &&
	    pwane_cap && pwane_cap->pew_pixew_awpha) {
		unsigned int bwend_caps = BIT(DWM_MODE_BWEND_PIXEW_NONE) |
					  BIT(DWM_MODE_BWEND_PWEMUWTI) |
					  BIT(DWM_MODE_BWEND_COVEWAGE);

		dwm_pwane_cweate_awpha_pwopewty(pwane);
		dwm_pwane_cweate_bwend_mode_pwopewty(pwane, bwend_caps);
	}

	if (pwane->type == DWM_PWANE_TYPE_PWIMAWY) {
		dwm_pwane_cweate_zpos_immutabwe_pwopewty(pwane, 0);
	} ewse if (pwane->type == DWM_PWANE_TYPE_OVEWWAY) {
		unsigned int zpos = 1 + dwm_pwane_index(pwane);
		dwm_pwane_cweate_zpos_pwopewty(pwane, zpos, 1, 254);
	} ewse if (pwane->type == DWM_PWANE_TYPE_CUWSOW) {
		dwm_pwane_cweate_zpos_immutabwe_pwopewty(pwane, 255);
	}

	if (pwane->type == DWM_PWANE_TYPE_PWIMAWY &&
	    pwane_cap &&
	    (pwane_cap->pixew_fowmat_suppowt.nv12 ||
	     pwane_cap->pixew_fowmat_suppowt.p010)) {
		/* This onwy affects YUV fowmats. */
		dwm_pwane_cweate_cowow_pwopewties(
			pwane,
			BIT(DWM_COWOW_YCBCW_BT601) |
			BIT(DWM_COWOW_YCBCW_BT709) |
			BIT(DWM_COWOW_YCBCW_BT2020),
			BIT(DWM_COWOW_YCBCW_WIMITED_WANGE) |
			BIT(DWM_COWOW_YCBCW_FUWW_WANGE),
			DWM_COWOW_YCBCW_BT709, DWM_COWOW_YCBCW_WIMITED_WANGE);
	}

	suppowted_wotations =
		DWM_MODE_WOTATE_0 | DWM_MODE_WOTATE_90 |
		DWM_MODE_WOTATE_180 | DWM_MODE_WOTATE_270;

	if (dm->adev->asic_type >= CHIP_BONAIWE &&
	    pwane->type != DWM_PWANE_TYPE_CUWSOW)
		dwm_pwane_cweate_wotation_pwopewty(pwane, DWM_MODE_WOTATE_0,
						   suppowted_wotations);

	if (amdgpu_ip_vewsion(dm->adev, DCE_HWIP, 0) > IP_VEWSION(3, 0, 1) &&
	    pwane->type != DWM_PWANE_TYPE_CUWSOW)
		dwm_pwane_enabwe_fb_damage_cwips(pwane);

	dwm_pwane_hewpew_add(pwane, &dm_pwane_hewpew_funcs);

#ifdef AMD_PWIVATE_COWOW
	dm_atomic_pwane_attach_cowow_mgmt_pwopewties(dm, pwane);
#endif
	/* Cweate (weset) the pwane state */
	if (pwane->funcs->weset)
		pwane->funcs->weset(pwane);

	wetuwn 0;
}

boow amdgpu_dm_pwane_is_video_fowmat(uint32_t fowmat)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(video_fowmats); i++)
		if (fowmat == video_fowmats[i])
			wetuwn twue;

	wetuwn fawse;
}

