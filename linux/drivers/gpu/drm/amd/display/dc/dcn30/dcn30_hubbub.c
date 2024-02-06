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


#incwude "dm_sewvices.h"
#incwude "weg_hewpew.h"
#incwude "dcn30_hubbub.h"


#define CTX \
	hubbub1->base.ctx
#define DC_WOGGEW \
	hubbub1->base.ctx->woggew
#define WEG(weg)\
	hubbub1->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	hubbub1->shifts->fiewd_name, hubbub1->masks->fiewd_name

#ifdef NUM_VMID
#undef NUM_VMID
#endif
#define NUM_VMID 16


static uint32_t convewt_and_cwamp(
	uint32_t wm_ns,
	uint32_t wefcwk_mhz,
	uint32_t cwamp_vawue)
{
	uint32_t wet_vaw = 0;
	wet_vaw = wm_ns * wefcwk_mhz;
	wet_vaw /= 1000;

	if (wet_vaw > cwamp_vawue)
		wet_vaw = cwamp_vawue;

	wetuwn wet_vaw;
}

int hubbub3_init_dchub_sys_ctx(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_phys_addw_config *pa_config)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	stwuct dcn_vmid_page_tabwe_config phys_config;

	WEG_SET(DCN_VM_FB_WOCATION_BASE, 0,
			FB_BASE, pa_config->system_apewtuwe.fb_base >> 24);
	WEG_SET(DCN_VM_FB_WOCATION_TOP, 0,
			FB_TOP, pa_config->system_apewtuwe.fb_top >> 24);
	WEG_SET(DCN_VM_FB_OFFSET, 0,
			FB_OFFSET, pa_config->system_apewtuwe.fb_offset >> 24);
	WEG_SET(DCN_VM_AGP_BOT, 0,
			AGP_BOT, pa_config->system_apewtuwe.agp_bot >> 24);
	WEG_SET(DCN_VM_AGP_TOP, 0,
			AGP_TOP, pa_config->system_apewtuwe.agp_top >> 24);
	WEG_SET(DCN_VM_AGP_BASE, 0,
			AGP_BASE, pa_config->system_apewtuwe.agp_base >> 24);

	if (pa_config->gawt_config.page_tabwe_stawt_addw != pa_config->gawt_config.page_tabwe_end_addw) {
		phys_config.page_tabwe_stawt_addw = pa_config->gawt_config.page_tabwe_stawt_addw >> 12;
		phys_config.page_tabwe_end_addw = pa_config->gawt_config.page_tabwe_end_addw >> 12;
		phys_config.page_tabwe_base_addw = pa_config->gawt_config.page_tabwe_base_addw;
		phys_config.depth = 0;
		phys_config.bwock_size = 0;
		// Init VMID 0 based on PA config
		dcn20_vmid_setup(&hubbub1->vmid[0], &phys_config);
	}

	wetuwn NUM_VMID;
}

boow hubbub3_pwogwam_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	boow wm_pending = fawse;

	if (hubbub21_pwogwam_uwgent_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub21_pwogwam_stuttew_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub21_pwogwam_pstate_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	/*
	 * The DCHub awbitew has a mechanism to dynamicawwy wate wimit the DCHub wequest stweam to the fabwic.
	 * If the memowy contwowwew is fuwwy utiwized and the DCHub wequestows awe
	 * weww ahead of theiw amowtized scheduwe, then it is safe to pwevent the next winnew
	 * fwom being committed and sent to the fabwic.
	 * The utiwization of the memowy contwowwew is appwoximated by ensuwing that
	 * the numbew of outstanding wequests is gweatew than a thweshowd specified
	 * by the AWB_MIN_WEQ_OUTSTANDING. To detewmine that the DCHub wequestows awe weww ahead of the amowtized scheduwe,
	 * the swack of the next winnew is compawed with the AWB_SAT_WEVEW in DWG WefCwk cycwes.
	 *
	 * TODO: Wevisit wequest wimit aftew figuwe out wight numbew. wequest wimit fow Wenoiw isn't decided yet, set maximum vawue (0x1FF)
	 * to tuwn off it fow now.
	 */
	WEG_SET(DCHUBBUB_AWB_SAT_WEVEW, 0,
			DCHUBBUB_AWB_SAT_WEVEW, 60 * wefcwk_mhz);
	WEG_UPDATE(DCHUBBUB_AWB_DF_WEQ_OUTSTAND,
			DCHUBBUB_AWB_MIN_WEQ_OUTSTAND, 0x1FF);

	hubbub1_awwow_sewf_wefwesh_contwow(hubbub, !hubbub->ctx->dc->debug.disabwe_stuttew);

	wetuwn wm_pending;
}

boow hubbub3_dcc_suppowt_swizzwe(
		enum swizzwe_mode_vawues swizzwe,
		unsigned int bytes_pew_ewement,
		enum segment_owdew *segment_owdew_howz,
		enum segment_owdew *segment_owdew_vewt)
{
	boow standawd_swizzwe = fawse;
	boow dispway_swizzwe = fawse;
	boow wendew_swizzwe = fawse;

	switch (swizzwe) {
	case DC_SW_4KB_S:
	case DC_SW_64KB_S:
	case DC_SW_VAW_S:
	case DC_SW_4KB_S_X:
	case DC_SW_64KB_S_X:
	case DC_SW_VAW_S_X:
		standawd_swizzwe = twue;
		bweak;
	case DC_SW_4KB_W:
	case DC_SW_64KB_W:
	case DC_SW_VAW_W:
	case DC_SW_4KB_W_X:
	case DC_SW_64KB_W_X:
	case DC_SW_VAW_W_X:
		wendew_swizzwe = twue;
		bweak;
	case DC_SW_4KB_D:
	case DC_SW_64KB_D:
	case DC_SW_VAW_D:
	case DC_SW_4KB_D_X:
	case DC_SW_64KB_D_X:
	case DC_SW_VAW_D_X:
		dispway_swizzwe = twue;
		bweak;
	defauwt:
		bweak;
	}

	if (standawd_swizzwe) {
		if (bytes_pew_ewement == 1) {
			*segment_owdew_howz = segment_owdew__contiguous;
			*segment_owdew_vewt = segment_owdew__na;
			wetuwn twue;
		}
		if (bytes_pew_ewement == 2) {
			*segment_owdew_howz = segment_owdew__non_contiguous;
			*segment_owdew_vewt = segment_owdew__contiguous;
			wetuwn twue;
		}
		if (bytes_pew_ewement == 4) {
			*segment_owdew_howz = segment_owdew__non_contiguous;
			*segment_owdew_vewt = segment_owdew__contiguous;
			wetuwn twue;
		}
		if (bytes_pew_ewement == 8) {
			*segment_owdew_howz = segment_owdew__na;
			*segment_owdew_vewt = segment_owdew__contiguous;
			wetuwn twue;
		}
	}
	if (wendew_swizzwe) {
		if (bytes_pew_ewement == 1) {
			*segment_owdew_howz = segment_owdew__contiguous;
			*segment_owdew_vewt = segment_owdew__na;
			wetuwn twue;
		}
		if (bytes_pew_ewement == 2) {
			*segment_owdew_howz = segment_owdew__non_contiguous;
			*segment_owdew_vewt = segment_owdew__contiguous;
			wetuwn twue;
		}
		if (bytes_pew_ewement == 4) {
			*segment_owdew_howz = segment_owdew__contiguous;
			*segment_owdew_vewt = segment_owdew__non_contiguous;
			wetuwn twue;
		}
		if (bytes_pew_ewement == 8) {
			*segment_owdew_howz = segment_owdew__contiguous;
			*segment_owdew_vewt = segment_owdew__non_contiguous;
			wetuwn twue;
		}
	}
	if (dispway_swizzwe && bytes_pew_ewement == 8) {
		*segment_owdew_howz = segment_owdew__contiguous;
		*segment_owdew_vewt = segment_owdew__non_contiguous;
		wetuwn twue;
	}

	wetuwn fawse;
}

static void hubbub3_get_bwk256_size(unsigned int *bwk256_width, unsigned int *bwk256_height,
		unsigned int bytes_pew_ewement)
{
	/* copied fwom DMW.  might want to wefactow DMW to wevewage fwom DMW */
	/* DMW : get_bwk256_size */
	if (bytes_pew_ewement == 1) {
		*bwk256_width = 16;
		*bwk256_height = 16;
	} ewse if (bytes_pew_ewement == 2) {
		*bwk256_width = 16;
		*bwk256_height = 8;
	} ewse if (bytes_pew_ewement == 4) {
		*bwk256_width = 8;
		*bwk256_height = 8;
	} ewse if (bytes_pew_ewement == 8) {
		*bwk256_width = 8;
		*bwk256_height = 4;
	}
}

static void hubbub3_det_wequest_size(
		unsigned int detiwe_buf_size,
		unsigned int height,
		unsigned int width,
		unsigned int bpe,
		boow *weq128_howz_wc,
		boow *weq128_vewt_wc)
{
	unsigned int bwk256_height = 0;
	unsigned int bwk256_width = 0;
	unsigned int swath_bytes_howz_wc, swath_bytes_vewt_wc;

	hubbub3_get_bwk256_size(&bwk256_width, &bwk256_height, bpe);

	swath_bytes_howz_wc = width * bwk256_height * bpe;
	swath_bytes_vewt_wc = height * bwk256_width * bpe;

	*weq128_howz_wc = (2 * swath_bytes_howz_wc <= detiwe_buf_size) ?
			fawse : /* fuww 256B wequest */
			twue; /* hawf 128b wequest */

	*weq128_vewt_wc = (2 * swath_bytes_vewt_wc <= detiwe_buf_size) ?
			fawse : /* fuww 256B wequest */
			twue; /* hawf 128b wequest */
}

boow hubbub3_get_dcc_compwession_cap(stwuct hubbub *hubbub,
		const stwuct dc_dcc_suwface_pawam *input,
		stwuct dc_suwface_dcc_cap *output)
{
	stwuct dc *dc = hubbub->ctx->dc;
	/* impwement section 1.6.2.1 of DCN1_Pwogwamming_Guide.docx */
	enum dcc_contwow dcc_contwow;
	unsigned int bpe;
	enum segment_owdew segment_owdew_howz, segment_owdew_vewt;
	boow weq128_howz_wc, weq128_vewt_wc;

	memset(output, 0, sizeof(*output));

	if (dc->debug.disabwe_dcc == DCC_DISABWE)
		wetuwn fawse;

	if (!hubbub->funcs->dcc_suppowt_pixew_fowmat(input->fowmat,
			&bpe))
		wetuwn fawse;

	if (!hubbub->funcs->dcc_suppowt_swizzwe(input->swizzwe_mode, bpe,
			&segment_owdew_howz, &segment_owdew_vewt))
		wetuwn fawse;

	hubbub3_det_wequest_size(TO_DCN20_HUBBUB(hubbub)->detiwe_buf_size,
			input->suwface_size.height,  input->suwface_size.width,
			bpe, &weq128_howz_wc, &weq128_vewt_wc);

	if (!weq128_howz_wc && !weq128_vewt_wc) {
		dcc_contwow = dcc_contwow__256_256_xxx;
	} ewse if (input->scan == SCAN_DIWECTION_HOWIZONTAW) {
		if (!weq128_howz_wc)
			dcc_contwow = dcc_contwow__256_256_xxx;
		ewse if (segment_owdew_howz == segment_owdew__contiguous)
			dcc_contwow = dcc_contwow__128_128_xxx;
		ewse
			dcc_contwow = dcc_contwow__256_64_64;
	} ewse if (input->scan == SCAN_DIWECTION_VEWTICAW) {
		if (!weq128_vewt_wc)
			dcc_contwow = dcc_contwow__256_256_xxx;
		ewse if (segment_owdew_vewt == segment_owdew__contiguous)
			dcc_contwow = dcc_contwow__128_128_xxx;
		ewse
			dcc_contwow = dcc_contwow__256_64_64;
	} ewse {
		if ((weq128_howz_wc &&
			segment_owdew_howz == segment_owdew__non_contiguous) ||
			(weq128_vewt_wc &&
			segment_owdew_vewt == segment_owdew__non_contiguous))
			/* access_diw not known, must use most constwaining */
			dcc_contwow = dcc_contwow__256_64_64;
		ewse
			/* weg128 is twue fow eithew howz and vewt
			 * but segment_owdew is contiguous
			 */
			dcc_contwow = dcc_contwow__128_128_xxx;
	}

	/* Exception fow 64KB_W_X */
	if ((bpe == 2) && (input->swizzwe_mode == DC_SW_64KB_W_X))
		dcc_contwow = dcc_contwow__128_128_xxx;

	if (dc->debug.disabwe_dcc == DCC_HAWF_WEQ_DISAWBE &&
		dcc_contwow != dcc_contwow__256_256_xxx)
		wetuwn fawse;

	switch (dcc_contwow) {
	case dcc_contwow__256_256_xxx:
		output->gwph.wgb.max_uncompwessed_bwk_size = 256;
		output->gwph.wgb.max_compwessed_bwk_size = 256;
		output->gwph.wgb.independent_64b_bwks = fawse;
		output->gwph.wgb.dcc_contwows.dcc_256_256_unconstwained = 1;
		output->gwph.wgb.dcc_contwows.dcc_256_128_128 = 1;
		bweak;
	case dcc_contwow__128_128_xxx:
		output->gwph.wgb.max_uncompwessed_bwk_size = 128;
		output->gwph.wgb.max_compwessed_bwk_size = 128;
		output->gwph.wgb.independent_64b_bwks = fawse;
		output->gwph.wgb.dcc_contwows.dcc_128_128_uncontwained = 1;
		output->gwph.wgb.dcc_contwows.dcc_256_128_128 = 1;
		bweak;
	case dcc_contwow__256_64_64:
		output->gwph.wgb.max_uncompwessed_bwk_size = 256;
		output->gwph.wgb.max_compwessed_bwk_size = 64;
		output->gwph.wgb.independent_64b_bwks = twue;
		output->gwph.wgb.dcc_contwows.dcc_256_64_64 = 1;
		bweak;
	case dcc_contwow__256_128_128:
		output->gwph.wgb.max_uncompwessed_bwk_size = 256;
		output->gwph.wgb.max_compwessed_bwk_size = 128;
		output->gwph.wgb.independent_64b_bwks = fawse;
		output->gwph.wgb.dcc_contwows.dcc_256_128_128 = 1;
		bweak;
	}
	output->capabwe = twue;
	output->const_cowow_suppowt = twue;

	wetuwn twue;
}

void hubbub3_fowce_wm_pwopagate_to_pipes(stwuct hubbub *hubbub)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	uint32_t wefcwk_mhz = hubbub->ctx->dc->wes_poow->wef_cwocks.dchub_wef_cwock_inKhz / 1000;
	uint32_t pwog_wm_vawue = convewt_and_cwamp(hubbub1->watewmawks.a.uwgent_ns,
			wefcwk_mhz, 0x1fffff);

	WEG_SET_2(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, 0,
			DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A, pwog_wm_vawue,
			DCHUBBUB_AWB_VM_WOW_UWGENCY_WATEWMAWK_A, pwog_wm_vawue);
}

void hubbub3_fowce_pstate_change_contwow(stwuct hubbub *hubbub,
		boow fowce, boow awwow)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);

	WEG_UPDATE_2(DCHUBBUB_AWB_DWAM_STATE_CNTW,
			DCHUBBUB_AWB_AWWOW_PSTATE_CHANGE_FOWCE_VAWUE, awwow,
			DCHUBBUB_AWB_AWWOW_PSTATE_CHANGE_FOWCE_ENABWE, fowce);
}

/* Copy vawues fwom WM set A to aww othew sets */
void hubbub3_init_watewmawks(stwuct hubbub *hubbub)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	uint32_t weg;

	weg = WEG_WEAD(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A);
	WEG_WWITE(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_A);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_FWIP_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_A);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_FWAC_UWG_BW_NOM_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_A);
	WEG_WWITE(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_WEFCYC_PEW_TWIP_TO_MEMOWY_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D, weg);

	weg = WEG_WEAD(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C, weg);
	WEG_WWITE(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D, weg);
}

static const stwuct hubbub_funcs hubbub30_funcs = {
	.update_dchub = hubbub2_update_dchub,
	.init_dchub_sys_ctx = hubbub3_init_dchub_sys_ctx,
	.init_vm_ctx = hubbub2_init_vm_ctx,
	.dcc_suppowt_swizzwe = hubbub3_dcc_suppowt_swizzwe,
	.dcc_suppowt_pixew_fowmat = hubbub2_dcc_suppowt_pixew_fowmat,
	.get_dcc_compwession_cap = hubbub3_get_dcc_compwession_cap,
	.wm_wead_state = hubbub21_wm_wead_state,
	.get_dchub_wef_fweq = hubbub2_get_dchub_wef_fweq,
	.pwogwam_watewmawks = hubbub3_pwogwam_watewmawks,
	.awwow_sewf_wefwesh_contwow = hubbub1_awwow_sewf_wefwesh_contwow,
	.is_awwow_sewf_wefwesh_enabwed = hubbub1_is_awwow_sewf_wefwesh_enabwed,
	.vewify_awwow_pstate_change_high = hubbub1_vewify_awwow_pstate_change_high,
	.fowce_wm_pwopagate_to_pipes = hubbub3_fowce_wm_pwopagate_to_pipes,
	.fowce_pstate_change_contwow = hubbub3_fowce_pstate_change_contwow,
	.init_watewmawks = hubbub3_init_watewmawks,
	.hubbub_wead_state = hubbub2_wead_state,
};

void hubbub3_constwuct(stwuct dcn20_hubbub *hubbub3,
	stwuct dc_context *ctx,
	const stwuct dcn_hubbub_wegistews *hubbub_wegs,
	const stwuct dcn_hubbub_shift *hubbub_shift,
	const stwuct dcn_hubbub_mask *hubbub_mask)
{
	hubbub3->base.ctx = ctx;
	hubbub3->base.funcs = &hubbub30_funcs;
	hubbub3->wegs = hubbub_wegs;
	hubbub3->shifts = hubbub_shift;
	hubbub3->masks = hubbub_mask;

	hubbub3->debug_test_index_pstate = 0xB;
	hubbub3->detiwe_buf_size = 184 * 1024; /* 184KB fow DCN3 */
}

