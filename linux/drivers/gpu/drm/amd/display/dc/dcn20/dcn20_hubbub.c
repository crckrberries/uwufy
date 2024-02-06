/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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


#incwude "dcn20_hubbub.h"
#incwude "weg_hewpew.h"
#incwude "cwk_mgw.h"

#define WEG(weg)\
	hubbub1->wegs->weg

#define CTX \
	hubbub1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubbub1->shifts->fiewd_name, hubbub1->masks->fiewd_name

#define WEG(weg)\
	hubbub1->wegs->weg

#define CTX \
	hubbub1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubbub1->shifts->fiewd_name, hubbub1->masks->fiewd_name

#ifdef NUM_VMID
#undef NUM_VMID
#endif
#define NUM_VMID 16

boow hubbub2_dcc_suppowt_swizzwe(
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
	case DC_SW_64KB_W_X:
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
		if (bytes_pew_ewement == 2) {
			*segment_owdew_howz = segment_owdew__contiguous;
			*segment_owdew_vewt = segment_owdew__contiguous;
			wetuwn twue;
		}
		if (bytes_pew_ewement == 4) {
			*segment_owdew_howz = segment_owdew__non_contiguous;
			*segment_owdew_vewt = segment_owdew__contiguous;
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

boow hubbub2_dcc_suppowt_pixew_fowmat(
		enum suwface_pixew_fowmat fowmat,
		unsigned int *bytes_pew_ewement)
{
	/* DMW: get_bytes_pew_ewement */
	switch (fowmat) {
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB1555:
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB565:
		*bytes_pew_ewement = 2;
		wetuwn twue;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB8888:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888:
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB2101010:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010:
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB111110_FIX:
	case SUWFACE_PIXEW_FOWMAT_GWPH_BGW101111_FIX:
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB111110_FWOAT:
	case SUWFACE_PIXEW_FOWMAT_GWPH_BGW101111_FWOAT:
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGBE:
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA:
		*bytes_pew_ewement = 4;
		wetuwn twue;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F:
		*bytes_pew_ewement = 8;
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void hubbub2_get_bwk256_size(unsigned int *bwk256_width, unsigned int *bwk256_height,
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

static void hubbub2_det_wequest_size(
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

	hubbub2_get_bwk256_size(&bwk256_width, &bwk256_height, bpe);

	swath_bytes_howz_wc = width * bwk256_height * bpe;
	swath_bytes_vewt_wc = height * bwk256_width * bpe;

	*weq128_howz_wc = (2 * swath_bytes_howz_wc <= detiwe_buf_size) ?
			fawse : /* fuww 256B wequest */
			twue; /* hawf 128b wequest */

	*weq128_vewt_wc = (2 * swath_bytes_vewt_wc <= detiwe_buf_size) ?
			fawse : /* fuww 256B wequest */
			twue; /* hawf 128b wequest */
}

boow hubbub2_get_dcc_compwession_cap(stwuct hubbub *hubbub,
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

	hubbub2_det_wequest_size(TO_DCN20_HUBBUB(hubbub)->detiwe_buf_size,
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
		bweak;
	case dcc_contwow__128_128_xxx:
		output->gwph.wgb.max_uncompwessed_bwk_size = 128;
		output->gwph.wgb.max_compwessed_bwk_size = 128;
		output->gwph.wgb.independent_64b_bwks = fawse;
		bweak;
	case dcc_contwow__256_64_64:
		output->gwph.wgb.max_uncompwessed_bwk_size = 256;
		output->gwph.wgb.max_compwessed_bwk_size = 64;
		output->gwph.wgb.independent_64b_bwks = twue;
		bweak;
	defauwt:
		ASSEWT(fawse);
		bweak;
	}
	output->capabwe = twue;
	output->const_cowow_suppowt = twue;

	wetuwn twue;
}

static enum dcn_hubbub_page_tabwe_depth page_tabwe_depth_to_hw(unsigned int page_tabwe_depth)
{
	enum dcn_hubbub_page_tabwe_depth depth = 0;

	switch (page_tabwe_depth) {
	case 1:
		depth = DCN_PAGE_TABWE_DEPTH_1_WEVEW;
		bweak;
	case 2:
		depth = DCN_PAGE_TABWE_DEPTH_2_WEVEW;
		bweak;
	case 3:
		depth = DCN_PAGE_TABWE_DEPTH_3_WEVEW;
		bweak;
	case 4:
		depth = DCN_PAGE_TABWE_DEPTH_4_WEVEW;
		bweak;
	defauwt:
		ASSEWT(fawse);
		bweak;
	}

	wetuwn depth;
}

static enum dcn_hubbub_page_tabwe_bwock_size page_tabwe_bwock_size_to_hw(unsigned int page_tabwe_bwock_size)
{
	enum dcn_hubbub_page_tabwe_bwock_size bwock_size = 0;

	switch (page_tabwe_bwock_size) {
	case 4096:
		bwock_size = DCN_PAGE_TABWE_BWOCK_SIZE_4KB;
		bweak;
	case 65536:
		bwock_size = DCN_PAGE_TABWE_BWOCK_SIZE_64KB;
		bweak;
	case 32768:
		bwock_size = DCN_PAGE_TABWE_BWOCK_SIZE_32KB;
		bweak;
	defauwt:
		ASSEWT(fawse);
		bwock_size = page_tabwe_bwock_size;
		bweak;
	}

	wetuwn bwock_size;
}

void hubbub2_init_vm_ctx(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_viwt_addw_config *va_config,
		int vmid)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	stwuct dcn_vmid_page_tabwe_config viwt_config;

	viwt_config.page_tabwe_stawt_addw = va_config->page_tabwe_stawt_addw >> 12;
	viwt_config.page_tabwe_end_addw = va_config->page_tabwe_end_addw >> 12;
	viwt_config.depth = page_tabwe_depth_to_hw(va_config->page_tabwe_depth);
	viwt_config.bwock_size = page_tabwe_bwock_size_to_hw(va_config->page_tabwe_bwock_size);
	viwt_config.page_tabwe_base_addw = va_config->page_tabwe_base_addw;

	dcn20_vmid_setup(&hubbub1->vmid[vmid], &viwt_config);
}

int hubbub2_init_dchub_sys_ctx(stwuct hubbub *hubbub,
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

	WEG_SET(DCN_VM_PWOTECTION_FAUWT_DEFAUWT_ADDW_MSB, 0,
			DCN_VM_PWOTECTION_FAUWT_DEFAUWT_ADDW_MSB, (pa_config->page_tabwe_defauwt_page_addw >> 44) & 0xF);
	WEG_SET(DCN_VM_PWOTECTION_FAUWT_DEFAUWT_ADDW_WSB, 0,
			DCN_VM_PWOTECTION_FAUWT_DEFAUWT_ADDW_WSB, (pa_config->page_tabwe_defauwt_page_addw >> 12) & 0xFFFFFFFF);

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

void hubbub2_update_dchub(stwuct hubbub *hubbub,
		stwuct dchub_init_data *dh_data)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);

	if (WEG(DCN_VM_FB_WOCATION_TOP) == 0)
		wetuwn;

	switch (dh_data->fb_mode) {
	case FWAME_BUFFEW_MODE_ZFB_ONWY:
		/*Fow ZFB case need to put DCHUB FB BASE and TOP upside down to indicate ZFB mode*/
		WEG_UPDATE(DCN_VM_FB_WOCATION_TOP,
				FB_TOP, 0);

		WEG_UPDATE(DCN_VM_FB_WOCATION_BASE,
				FB_BASE, 0xFFFFFF);

		/*This fiewd defines the 24 MSBs, bits [47:24] of the 48 bit AGP Base*/
		WEG_UPDATE(DCN_VM_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addw_base >> 24);

		/*This fiewd defines the bottom wange of the AGP apewtuwe and wepwesents the 24*/
		/*MSBs, bits [47:24] of the 48 addwess bits*/
		WEG_UPDATE(DCN_VM_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addw >> 24);

		/*This fiewd defines the top wange of the AGP apewtuwe and wepwesents the 24*/
		/*MSBs, bits [47:24] of the 48 addwess bits*/
		WEG_UPDATE(DCN_VM_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addw +
						dh_data->zfb_size_in_byte - 1) >> 24);
		bweak;
	case FWAME_BUFFEW_MODE_MIXED_ZFB_AND_WOCAW:
		/*Shouwd not touch FB WOCATION (done by VBIOS on AsicInit tabwe)*/

		/*This fiewd defines the 24 MSBs, bits [47:24] of the 48 bit AGP Base*/
		WEG_UPDATE(DCN_VM_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addw_base >> 24);

		/*This fiewd defines the bottom wange of the AGP apewtuwe and wepwesents the 24*/
		/*MSBs, bits [47:24] of the 48 addwess bits*/
		WEG_UPDATE(DCN_VM_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addw >> 24);

		/*This fiewd defines the top wange of the AGP apewtuwe and wepwesents the 24*/
		/*MSBs, bits [47:24] of the 48 addwess bits*/
		WEG_UPDATE(DCN_VM_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addw +
						dh_data->zfb_size_in_byte - 1) >> 24);
		bweak;
	case FWAME_BUFFEW_MODE_WOCAW_ONWY:
		/*Shouwd not touch FB WOCATION (shouwd be done by VBIOS)*/

		/*This fiewd defines the 24 MSBs, bits [47:24] of the 48 bit AGP Base*/
		WEG_UPDATE(DCN_VM_AGP_BASE,
				AGP_BASE, 0);

		/*This fiewd defines the bottom wange of the AGP apewtuwe and wepwesents the 24*/
		/*MSBs, bits [47:24] of the 48 addwess bits*/
		WEG_UPDATE(DCN_VM_AGP_BOT,
				AGP_BOT, 0xFFFFFF);

		/*This fiewd defines the top wange of the AGP apewtuwe and wepwesents the 24*/
		/*MSBs, bits [47:24] of the 48 addwess bits*/
		WEG_UPDATE(DCN_VM_AGP_TOP,
				AGP_TOP, 0);
		bweak;
	defauwt:
		bweak;
	}

	dh_data->dchub_initiawzied = twue;
	dh_data->dchub_info_vawid = fawse;
}

void hubbub2_wm_wead_state(stwuct hubbub *hubbub,
		stwuct dcn_hubbub_wm *wm)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);

	stwuct dcn_hubbub_wm_set *s;

	memset(wm, 0, sizeof(stwuct dcn_hubbub_wm));

	s = &wm->sets[0];
	s->wm_set = 0;
	s->data_uwgent = WEG_WEAD(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_A);
	if (WEG(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_A))
		s->pte_meta_uwgent = WEG_WEAD(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_A);
	if (WEG(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A)) {
		s->sw_entew = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_A);
		s->sw_exit = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_A);
	}
	s->dwam_cwk_change = WEG_WEAD(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_A);

	s = &wm->sets[1];
	s->wm_set = 1;
	s->data_uwgent = WEG_WEAD(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_B);
	if (WEG(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_B))
		s->pte_meta_uwgent = WEG_WEAD(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_B);
	if (WEG(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B)) {
		s->sw_entew = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_B);
		s->sw_exit = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_B);
	}
	s->dwam_cwk_change = WEG_WEAD(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_B);

	s = &wm->sets[2];
	s->wm_set = 2;
	s->data_uwgent = WEG_WEAD(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_C);
	if (WEG(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_C))
		s->pte_meta_uwgent = WEG_WEAD(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_C);
	if (WEG(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C)) {
		s->sw_entew = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_C);
		s->sw_exit = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_C);
	}
	s->dwam_cwk_change = WEG_WEAD(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_C);

	s = &wm->sets[3];
	s->wm_set = 3;
	s->data_uwgent = WEG_WEAD(DCHUBBUB_AWB_DATA_UWGENCY_WATEWMAWK_D);
	if (WEG(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_D))
		s->pte_meta_uwgent = WEG_WEAD(DCHUBBUB_AWB_PTE_META_UWGENCY_WATEWMAWK_D);
	if (WEG(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D)) {
		s->sw_entew = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_ENTEW_WATEWMAWK_D);
		s->sw_exit = WEG_WEAD(DCHUBBUB_AWB_AWWOW_SW_EXIT_WATEWMAWK_D);
	}
	s->dwam_cwk_change = WEG_WEAD(DCHUBBUB_AWB_AWWOW_DWAM_CWK_CHANGE_WATEWMAWK_D);
}

void hubbub2_get_dchub_wef_fweq(stwuct hubbub *hubbub,
		unsigned int dccg_wef_fweq_inKhz,
		unsigned int *dchub_wef_fweq_inKhz)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	uint32_t wef_div = 0;
	uint32_t wef_en = 0;

	WEG_GET_2(DCHUBBUB_GWOBAW_TIMEW_CNTW, DCHUBBUB_GWOBAW_TIMEW_WEFDIV, &wef_div,
			DCHUBBUB_GWOBAW_TIMEW_ENABWE, &wef_en);

	if (wef_en) {
		if (wef_div == 2)
			*dchub_wef_fweq_inKhz = dccg_wef_fweq_inKhz / 2;
		ewse
			*dchub_wef_fweq_inKhz = dccg_wef_fweq_inKhz;

		// DC hub wefewence fwequency must be awound 50Mhz, othewwise thewe may be
		// ovewfwow/undewfwow issues when doing HUBBUB pwogwamming
		if (*dchub_wef_fweq_inKhz < 40000 || *dchub_wef_fweq_inKhz > 60000)
			ASSEWT_CWITICAW(fawse);

		wetuwn;
	} ewse {
		*dchub_wef_fweq_inKhz = dccg_wef_fweq_inKhz;

		// HUBBUB gwobaw timew must be enabwed.
		ASSEWT_CWITICAW(fawse);
		wetuwn;
	}
}

static boow hubbub2_pwogwam_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	boow wm_pending = fawse;
	/*
	 * Need to cwamp to max of the wegistew vawues (i.e. no wwap)
	 * fow dcn1, aww wm wegistews awe 21-bit wide
	 */
	if (hubbub1_pwogwam_uwgent_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub1_pwogwam_stuttew_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	/*
	 * Thewe's a speciaw case when going fwom p-state suppowt to p-state unsuppowted
	 * hewe we awe going to WOWEW watewmawks to go to dummy p-state onwy, but this has
	 * to be done pwepawe_bandwidth, not optimize
	 */
	if (hubbub1->base.ctx->dc->cwk_mgw->cwks.pwev_p_state_change_suppowt == twue &&
		hubbub1->base.ctx->dc->cwk_mgw->cwks.p_state_change_suppowt == fawse)
		safe_to_wowew = twue;

	hubbub1_pwogwam_pstate_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew);

	WEG_SET(DCHUBBUB_AWB_SAT_WEVEW, 0,
			DCHUBBUB_AWB_SAT_WEVEW, 60 * wefcwk_mhz);
	WEG_UPDATE(DCHUBBUB_AWB_DF_WEQ_OUTSTAND, DCHUBBUB_AWB_MIN_WEQ_OUTSTAND, 180);

	hubbub->funcs->awwow_sewf_wefwesh_contwow(hubbub, !hubbub->ctx->dc->debug.disabwe_stuttew);
	wetuwn wm_pending;
}

void hubbub2_wead_state(stwuct hubbub *hubbub, stwuct dcn_hubbub_state *hubbub_state)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);

	if (WEG(DCN_VM_FAUWT_ADDW_MSB))
		hubbub_state->vm_fauwt_addw_msb = WEG_WEAD(DCN_VM_FAUWT_ADDW_MSB);

	if (WEG(DCN_VM_FAUWT_ADDW_WSB))
		hubbub_state->vm_fauwt_addw_msb = WEG_WEAD(DCN_VM_FAUWT_ADDW_WSB);

	if (WEG(DCN_VM_FAUWT_CNTW))
		WEG_GET(DCN_VM_FAUWT_CNTW, DCN_VM_EWWOW_STATUS_MODE, &hubbub_state->vm_ewwow_mode);

	if (WEG(DCN_VM_FAUWT_STATUS)) {
		 WEG_GET(DCN_VM_FAUWT_STATUS, DCN_VM_EWWOW_STATUS, &hubbub_state->vm_ewwow_status);
		 WEG_GET(DCN_VM_FAUWT_STATUS, DCN_VM_EWWOW_VMID, &hubbub_state->vm_ewwow_vmid);
		 WEG_GET(DCN_VM_FAUWT_STATUS, DCN_VM_EWWOW_PIPE, &hubbub_state->vm_ewwow_pipe);
	}

	if (WEG(DCHUBBUB_TEST_DEBUG_INDEX) && WEG(DCHUBBUB_TEST_DEBUG_DATA)) {
		WEG_WWITE(DCHUBBUB_TEST_DEBUG_INDEX, 0x6);
		hubbub_state->test_debug_data = WEG_WEAD(DCHUBBUB_TEST_DEBUG_DATA);
	}

	if (WEG(DCHUBBUB_AWB_WATEWMAWK_CHANGE_CNTW))
		hubbub_state->watewmawk_change_cntw = WEG_WEAD(DCHUBBUB_AWB_WATEWMAWK_CHANGE_CNTW);

	if (WEG(DCHUBBUB_AWB_DWAM_STATE_CNTW))
		hubbub_state->dwam_state_cntw = WEG_WEAD(DCHUBBUB_AWB_DWAM_STATE_CNTW);
}

static const stwuct hubbub_funcs hubbub2_funcs = {
	.update_dchub = hubbub2_update_dchub,
	.init_dchub_sys_ctx = hubbub2_init_dchub_sys_ctx,
	.init_vm_ctx = hubbub2_init_vm_ctx,
	.dcc_suppowt_swizzwe = hubbub2_dcc_suppowt_swizzwe,
	.dcc_suppowt_pixew_fowmat = hubbub2_dcc_suppowt_pixew_fowmat,
	.get_dcc_compwession_cap = hubbub2_get_dcc_compwession_cap,
	.wm_wead_state = hubbub2_wm_wead_state,
	.get_dchub_wef_fweq = hubbub2_get_dchub_wef_fweq,
	.pwogwam_watewmawks = hubbub2_pwogwam_watewmawks,
	.is_awwow_sewf_wefwesh_enabwed = hubbub1_is_awwow_sewf_wefwesh_enabwed,
	.awwow_sewf_wefwesh_contwow = hubbub1_awwow_sewf_wefwesh_contwow,
	.hubbub_wead_state = hubbub2_wead_state,
};

void hubbub2_constwuct(stwuct dcn20_hubbub *hubbub,
	stwuct dc_context *ctx,
	const stwuct dcn_hubbub_wegistews *hubbub_wegs,
	const stwuct dcn_hubbub_shift *hubbub_shift,
	const stwuct dcn_hubbub_mask *hubbub_mask)
{
	hubbub->base.ctx = ctx;

	hubbub->base.funcs = &hubbub2_funcs;

	hubbub->wegs = hubbub_wegs;
	hubbub->shifts = hubbub_shift;
	hubbub->masks = hubbub_mask;

	hubbub->debug_test_index_pstate = 0xB;
	hubbub->detiwe_buf_size = 164 * 1024; /* 164KB fow DCN2.0 */
}
