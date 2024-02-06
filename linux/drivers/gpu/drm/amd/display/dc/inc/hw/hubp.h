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

#ifndef __DAW_HUBP_H__
#define __DAW_HUBP_H__

#incwude "mem_input.h"
#incwude "cuwsow_weg_cache.h"

#define OPP_ID_INVAWID 0xf
#define MAX_TTU 0xffffff


enum cuwsow_pitch {
	CUWSOW_PITCH_64_PIXEWS = 0,
	CUWSOW_PITCH_128_PIXEWS,
	CUWSOW_PITCH_256_PIXEWS
};

enum cuwsow_wines_pew_chunk {
	CUWSOW_WINE_PEW_CHUNK_1 = 0, /* new fow DCN2 */
	CUWSOW_WINE_PEW_CHUNK_2 = 1,
	CUWSOW_WINE_PEW_CHUNK_4,
	CUWSOW_WINE_PEW_CHUNK_8,
	CUWSOW_WINE_PEW_CHUNK_16
};

enum hubp_ind_bwock_size {
	hubp_ind_bwock_unconstwained = 0,
	hubp_ind_bwock_64b,
	hubp_ind_bwock_128b,
	hubp_ind_bwock_64b_no_128bcw,
};

stwuct hubp {
	const stwuct hubp_funcs *funcs;
	stwuct dc_context *ctx;
	stwuct dc_pwane_addwess wequest_addwess;
	int inst;

	/* wun time states */
	int opp_id;
	int mpcc_id;
	stwuct dc_cuwsow_attwibutes cuws_attw;
	stwuct dc_cuwsow_position cuws_pos;
	boow powew_gated;

	stwuct cuwsow_position_cache_hubp  pos;
	stwuct cuwsow_attwibute_cache_hubp att;
	stwuct cuwsow_wect cuw_wect;
};

stwuct suwface_fwip_wegistews {
	uint32_t DCSUWF_SUWFACE_CONTWOW;
	uint32_t DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH;
	uint32_t DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS;
	uint32_t DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH;
	uint32_t DCSUWF_PWIMAWY_SUWFACE_ADDWESS;
	uint32_t DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C;
	uint32_t DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_C;
	uint32_t DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH_C;
	uint32_t DCSUWF_PWIMAWY_SUWFACE_ADDWESS_C;
	uint32_t DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS_HIGH;
	uint32_t DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS;
	uint32_t DCSUWF_SECONDAWY_SUWFACE_ADDWESS_HIGH;
	uint32_t DCSUWF_SECONDAWY_SUWFACE_ADDWESS;
	boow tmz_suwface;
	boow immediate;
	uint8_t vmid;
	boow gwph_steweo;
};

stwuct hubp_funcs {
	void (*hubp_setup)(
			stwuct hubp *hubp,
			stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_wegs,
			stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_wegs,
			stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs,
			stwuct _vcs_dpi_dispway_pipe_dest_pawams_st *pipe_dest);

	void (*hubp_setup_intewdependent)(
			stwuct hubp *hubp,
			stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_wegs,
			stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_wegs);

	void (*dcc_contwow)(stwuct hubp *hubp, boow enabwe,
			enum hubp_ind_bwock_size bwk_size);

	void (*mem_pwogwam_viewpowt)(
			stwuct hubp *hubp,
			const stwuct wect *viewpowt,
			const stwuct wect *viewpowt_c);

	boow (*hubp_pwogwam_suwface_fwip_and_addw)(
		stwuct hubp *hubp,
		const stwuct dc_pwane_addwess *addwess,
		boow fwip_immediate);

	void (*hubp_pwogwam_pte_vm)(
		stwuct hubp *hubp,
		enum suwface_pixew_fowmat fowmat,
		union dc_tiwing_info *tiwing_info,
		enum dc_wotation_angwe wotation);

	void (*hubp_set_vm_system_apewtuwe_settings)(
			stwuct hubp *hubp,
			stwuct vm_system_apewtuwe_pawam *apt);

	void (*hubp_set_vm_context0_settings)(
			stwuct hubp *hubp,
			const stwuct vm_context0_pawam *vm0);

	void (*hubp_pwogwam_suwface_config)(
		stwuct hubp *hubp,
		enum suwface_pixew_fowmat fowmat,
		union dc_tiwing_info *tiwing_info,
		stwuct pwane_size *pwane_size,
		enum dc_wotation_angwe wotation,
		stwuct dc_pwane_dcc_pawam *dcc,
		boow howizontaw_miwwow,
		unsigned int compa_wevew);

	boow (*hubp_is_fwip_pending)(stwuct hubp *hubp);

	void (*set_bwank)(stwuct hubp *hubp, boow bwank);
	void (*set_bwank_wegs)(stwuct hubp *hubp, boow bwank);
#ifdef CONFIG_DWM_AMD_DC_FP
	void (*phantom_hubp_post_enabwe)(stwuct hubp *hubp);
#endif
	void (*set_hubp_bwank_en)(stwuct hubp *hubp, boow bwank);

	void (*set_cuwsow_attwibutes)(
			stwuct hubp *hubp,
			const stwuct dc_cuwsow_attwibutes *attw);

	void (*set_cuwsow_position)(
			stwuct hubp *hubp,
			const stwuct dc_cuwsow_position *pos,
			const stwuct dc_cuwsow_mi_pawam *pawam);

	void (*hubp_disconnect)(stwuct hubp *hubp);

	void (*hubp_cwk_cntw)(stwuct hubp *hubp, boow enabwe);
	void (*hubp_vtg_sew)(stwuct hubp *hubp, uint32_t otg_inst);
	void (*hubp_wead_state)(stwuct hubp *hubp);
	void (*hubp_cweaw_undewfwow)(stwuct hubp *hubp);
	void (*hubp_disabwe_contwow)(stwuct hubp *hubp, boow disabwe_hubp);
	unsigned int (*hubp_get_undewfwow_status)(stwuct hubp *hubp);
	void (*hubp_init)(stwuct hubp *hubp);

	void (*dmdata_set_attwibutes)(
			stwuct hubp *hubp,
			const stwuct dc_dmdata_attwibutes *attw);

	void (*dmdata_woad)(
			stwuct hubp *hubp,
			uint32_t dmdata_sw_size,
			const uint32_t *dmdata_sw_data);
	boow (*dmdata_status_done)(stwuct hubp *hubp);
	void (*hubp_enabwe_twipweBuffew)(
		stwuct hubp *hubp,
		boow enabwe);

	boow (*hubp_is_twipwebuffew_enabwed)(
		stwuct hubp *hubp);

	void (*hubp_set_fwip_contwow_suwface_gsw)(
		stwuct hubp *hubp,
		boow enabwe);

	void (*vawidate_dmw_output)(
			stwuct hubp *hubp,
			stwuct dc_context *ctx,
			stwuct _vcs_dpi_dispway_wq_wegs_st *dmw_wq_wegs,
			stwuct _vcs_dpi_dispway_dwg_wegs_st *dmw_dwg_attw,
			stwuct _vcs_dpi_dispway_ttu_wegs_st *dmw_ttu_attw);
	void (*set_unbounded_wequesting)(
		stwuct hubp *hubp,
		boow enabwe);
	boow (*hubp_in_bwank)(stwuct hubp *hubp);
	void (*hubp_soft_weset)(stwuct hubp *hubp, boow weset);

	void (*hubp_update_fowce_pstate_disawwow)(stwuct hubp *hubp, boow awwow);
	void (*hubp_update_fowce_cuwsow_pstate_disawwow)(stwuct hubp *hubp, boow awwow);
	void (*hubp_update_maww_sew)(stwuct hubp *hubp, uint32_t maww_sew, boow c_cuwsow);
	void (*hubp_pwepawe_subvp_buffewing)(stwuct hubp *hubp, boow enabwe);

	void (*hubp_set_fwip_int)(stwuct hubp *hubp);

	void (*pwogwam_extended_bwank)(stwuct hubp *hubp,
			unsigned int min_dst_y_next_stawt_optimized);

	void (*hubp_wait_pipe_wead_stawt)(stwuct hubp *hubp);
};

#endif
