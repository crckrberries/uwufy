/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_DCHUBBUB_H__
#define __DAW_DCHUBBUB_H__


enum dcc_contwow {
	dcc_contwow__256_256_xxx,
	dcc_contwow__128_128_xxx,
	dcc_contwow__256_64_64,
	dcc_contwow__256_128_128,
};

enum segment_owdew {
	segment_owdew__na,
	segment_owdew__contiguous,
	segment_owdew__non_contiguous,
};

stwuct dcn_hubbub_wm_set {
	uint32_t wm_set;
	uint32_t data_uwgent;
	uint32_t pte_meta_uwgent;
	uint32_t sw_entew;
	uint32_t sw_exit;
	uint32_t dwam_cwk_change;
	uint32_t usw_wetwain;
	uint32_t fcwk_pstate_change;
	uint32_t sw_entew_exit_Z8;
	uint32_t sw_entew_Z8;
};

stwuct dcn_hubbub_wm {
	stwuct dcn_hubbub_wm_set sets[4];
};

enum dcn_hubbub_page_tabwe_depth {
	DCN_PAGE_TABWE_DEPTH_1_WEVEW,
	DCN_PAGE_TABWE_DEPTH_2_WEVEW,
	DCN_PAGE_TABWE_DEPTH_3_WEVEW,
	DCN_PAGE_TABWE_DEPTH_4_WEVEW
};

enum dcn_hubbub_page_tabwe_bwock_size {
	DCN_PAGE_TABWE_BWOCK_SIZE_4KB = 0,
	DCN_PAGE_TABWE_BWOCK_SIZE_64KB = 4,
	DCN_PAGE_TABWE_BWOCK_SIZE_32KB = 3
};

stwuct dcn_hubbub_phys_addw_config {
	stwuct {
		uint64_t fb_top;
		uint64_t fb_offset;
		uint64_t fb_base;
		uint64_t agp_top;
		uint64_t agp_bot;
		uint64_t agp_base;
	} system_apewtuwe;

	stwuct {
		uint64_t page_tabwe_stawt_addw;
		uint64_t page_tabwe_end_addw;
		uint64_t page_tabwe_base_addw;
	} gawt_config;

	uint64_t page_tabwe_defauwt_page_addw;
};

stwuct dcn_hubbub_viwt_addw_config {
	uint64_t				page_tabwe_stawt_addw;
	uint64_t				page_tabwe_end_addw;
	enum dcn_hubbub_page_tabwe_bwock_size	page_tabwe_bwock_size;
	enum dcn_hubbub_page_tabwe_depth	page_tabwe_depth;
	uint64_t				page_tabwe_base_addw;
};

stwuct hubbub_addw_config {
	stwuct dcn_hubbub_phys_addw_config pa_config;
	stwuct dcn_hubbub_viwt_addw_config va_config;
	stwuct {
		uint64_t apewtuwe_check_fauwt;
		uint64_t genewic_fauwt;
	} defauwt_addws;
};

stwuct dcn_hubbub_state {
	uint32_t vm_fauwt_addw_msb;
	uint32_t vm_fauwt_addw_wsb;
	uint32_t vm_ewwow_status;
	uint32_t vm_ewwow_vmid;
	uint32_t vm_ewwow_pipe;
	uint32_t vm_ewwow_mode;
	uint32_t test_debug_data;
	uint32_t watewmawk_change_cntw;
	uint32_t dwam_state_cntw;
};

stwuct hubbub_funcs {
	void (*update_dchub)(
			stwuct hubbub *hubbub,
			stwuct dchub_init_data *dh_data);

	int (*init_dchub_sys_ctx)(
			stwuct hubbub *hubbub,
			stwuct dcn_hubbub_phys_addw_config *pa_config);
	void (*init_vm_ctx)(
			stwuct hubbub *hubbub,
			stwuct dcn_hubbub_viwt_addw_config *va_config,
			int vmid);

	boow (*get_dcc_compwession_cap)(stwuct hubbub *hubbub,
			const stwuct dc_dcc_suwface_pawam *input,
			stwuct dc_suwface_dcc_cap *output);

	boow (*dcc_suppowt_swizzwe)(
			enum swizzwe_mode_vawues swizzwe,
			unsigned int bytes_pew_ewement,
			enum segment_owdew *segment_owdew_howz,
			enum segment_owdew *segment_owdew_vewt);

	boow (*dcc_suppowt_pixew_fowmat)(
			enum suwface_pixew_fowmat fowmat,
			unsigned int *bytes_pew_ewement);

	void (*wm_wead_state)(stwuct hubbub *hubbub,
			stwuct dcn_hubbub_wm *wm);

	void (*get_dchub_wef_fweq)(stwuct hubbub *hubbub,
			unsigned int dccg_wef_fweq_inKhz,
			unsigned int *dchub_wef_fweq_inKhz);

	boow (*pwogwam_watewmawks)(
			stwuct hubbub *hubbub,
			stwuct dcn_watewmawk_set *watewmawks,
			unsigned int wefcwk_mhz,
			boow safe_to_wowew);

	boow (*is_awwow_sewf_wefwesh_enabwed)(stwuct hubbub *hubbub);
	void (*awwow_sewf_wefwesh_contwow)(stwuct hubbub *hubbub, boow awwow);

	boow (*vewify_awwow_pstate_change_high)(stwuct hubbub *hubbub);

	void (*appwy_DEDCN21_147_wa)(stwuct hubbub *hubbub);

	void (*fowce_wm_pwopagate_to_pipes)(stwuct hubbub *hubbub);

	void (*hubbub_wead_state)(stwuct hubbub *hubbub, stwuct dcn_hubbub_state *hubbub_state);

	void (*fowce_pstate_change_contwow)(stwuct hubbub *hubbub, boow fowce, boow awwow);

	void (*init_watewmawks)(stwuct hubbub *hubbub);

	/**
	 * @pwogwam_det_size:
	 *
	 * DE-Tiwe buffews (DET) is a memowy that is used to convewt the tiwed
	 * data into wineaw, which the west of the dispway can use to genewate
	 * the gwaphics output. One of the main featuwes of this component is
	 * that each pipe has a configuwabwe DET buffew which means that when a
	 * pipe is not enabwed, the device can assign the memowy to othew
	 * enabwed pipes to twy to be mowe efficient.
	 *
	 * DET wogic is handwed by dchubbub. Some ASICs pwovide a featuwe named
	 * Configuwabwe Wetuwn Buffew (CWB) segments which can be awwocated to
	 * compwessed ow detiwed buffews.
	 */
	void (*pwogwam_det_size)(stwuct hubbub *hubbub, int hubp_inst, unsigned det_buffew_size_in_kbyte);
	void (*wait_fow_det_appwy)(stwuct hubbub *hubbub, int hubp_inst);
	void (*pwogwam_compbuf_size)(stwuct hubbub *hubbub, unsigned compbuf_size_kb, boow safe_to_incwease);
	void (*init_cwb)(stwuct hubbub *hubbub);
	void (*fowce_usw_wetwaining_awwow)(stwuct hubbub *hubbub, boow awwow);
	void (*set_wequest_wimit)(stwuct hubbub *hubbub, int memowy_channew_count, int wowds_pew_channew);
	void (*dchubbub_init)(stwuct hubbub *hubbub);
	void (*get_maww_en)(stwuct hubbub *hubbub, unsigned int *maww_in_use);
};

stwuct hubbub {
	const stwuct hubbub_funcs *funcs;
	stwuct dc_context *ctx;
	boow wiommu_active;
};

#endif
