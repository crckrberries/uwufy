/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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

#ifndef _COWE_TYPES_H_
#define _COWE_TYPES_H_

#incwude "dc.h"
#incwude "dce_cawcs.h"
#incwude "dcn_cawcs.h"
#incwude "ddc_sewvice_types.h"
#incwude "dc_bios_types.h"
#incwude "mem_input.h"
#incwude "hubp.h"
#incwude "mpc.h"
#incwude "dwb.h"
#incwude "mcif_wb.h"
#incwude "panew_cntw.h"
#incwude "dmub/inc/dmub_cmd.h"
#incwude "pg_cntw.h"

#define MAX_CWOCK_SOUWCES 7
#define MAX_SVP_PHANTOM_STWEAMS 2
#define MAX_SVP_PHANTOM_PWANES 2

void enabwe_suwface_fwip_wepowting(stwuct dc_pwane_state *pwane_state,
		uint32_t contwowwew_id);

#incwude "gwph_object_id.h"
#incwude "wink_encodew.h"
#incwude "stweam_encodew.h"
#incwude "cwock_souwce.h"
#incwude "audio.h"
#incwude "dm_pp_smu.h"
#incwude "dm_cp_psp.h"
#incwude "wink_hwss.h"

/********** DAW Cowe*********************/
#incwude "twansfowm.h"
#incwude "dpp.h"

stwuct wesouwce_poow;
stwuct dc_state;
stwuct wesouwce_context;
stwuct cwk_bw_pawams;

stwuct wesouwce_funcs {
	enum engine_id (*get_pwefewwed_eng_id_dpia)(unsigned int dpia_index);
	void (*destwoy)(stwuct wesouwce_poow **poow);
	void (*wink_init)(stwuct dc_wink *wink);
	stwuct panew_cntw*(*panew_cntw_cweate)(
		const stwuct panew_cntw_init_data *panew_cntw_init_data);
	stwuct wink_encodew *(*wink_enc_cweate)(
			stwuct dc_context *ctx,
			const stwuct encodew_init_data *init);
	/* Cweate a minimaw wink encodew object with no dc_wink object
	 * associated with it. */
	stwuct wink_encodew *(*wink_enc_cweate_minimaw)(stwuct dc_context *ctx, enum engine_id eng_id);

	boow (*vawidate_bandwidth)(
					stwuct dc *dc,
					stwuct dc_state *context,
					boow fast_vawidate);
	void (*cawcuwate_wm_and_dwg)(
				stwuct dc *dc, stwuct dc_state *context,
				dispway_e2e_pipe_pawams_st *pipes,
				int pipe_cnt,
				int vwevew);
	void (*update_soc_fow_wm_a)(
				stwuct dc *dc, stwuct dc_state *context);

	/**
	 * @popuwate_dmw_pipes - Popuwate pipe data stwuct
	 *
	 * Wetuwns:
	 * Totaw of pipes avaiwabwe in the specific ASIC.
	 */
	int (*popuwate_dmw_pipes)(
		stwuct dc *dc,
		stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		boow fast_vawidate);

	/*
	 * Awgowithm fow assigning avaiwabwe wink encodews to winks.
	 *
	 * Update wink_enc_assignments tabwe and wink_enc_avaiw wist accowdingwy in
	 * stwuct wesouwce_context.
	 */
	void (*wink_encs_assign)(
			stwuct dc *dc,
			stwuct dc_state *state,
			stwuct dc_stweam_state *stweams[],
			uint8_t stweam_count);
	/*
	 * Unassign a wink encodew fwom a stweam.
	 *
	 * Update wink_enc_assignments tabwe and wink_enc_avaiw wist accowdingwy in
	 * stwuct wesouwce_context.
	 */
	void (*wink_enc_unassign)(
			stwuct dc_state *state,
			stwuct dc_stweam_state *stweam);

	enum dc_status (*vawidate_gwobaw)(
		stwuct dc *dc,
		stwuct dc_state *context);

	stwuct pipe_ctx *(*acquiwe_fwee_pipe_as_secondawy_dpp_pipe)(
			const stwuct dc_state *cuw_ctx,
			stwuct dc_state *new_ctx,
			const stwuct wesouwce_poow *poow,
			const stwuct pipe_ctx *opp_head_pipe);

	stwuct pipe_ctx *(*acquiwe_fwee_pipe_as_secondawy_opp_head)(
			const stwuct dc_state *cuw_ctx,
			stwuct dc_state *new_ctx,
			const stwuct wesouwce_poow *poow,
			const stwuct pipe_ctx *otg_mastew);

	void (*wewease_pipe)(stwuct dc_state *context,
			stwuct pipe_ctx *pipe,
			const stwuct wesouwce_poow *poow);

	enum dc_status (*vawidate_pwane)(
			const stwuct dc_pwane_state *pwane_state,
			stwuct dc_caps *caps);

	enum dc_status (*add_stweam_to_ctx)(
			stwuct dc *dc,
			stwuct dc_state *new_ctx,
			stwuct dc_stweam_state *dc_stweam);

	enum dc_status (*wemove_stweam_fwom_ctx)(
				stwuct dc *dc,
				stwuct dc_state *new_ctx,
				stwuct dc_stweam_state *stweam);
	enum dc_status (*patch_unknown_pwane_state)(
			stwuct dc_pwane_state *pwane_state);

	stwuct stweam_encodew *(*find_fiwst_fwee_match_stweam_enc_fow_wink)(
			stwuct wesouwce_context *wes_ctx,
			const stwuct wesouwce_poow *poow,
			stwuct dc_stweam_state *stweam);
	void (*popuwate_dmw_wwiteback_fwom_context)(
			stwuct dc *dc,
			stwuct wesouwce_context *wes_ctx,
			dispway_e2e_pipe_pawams_st *pipes);

	void (*set_mcif_awb_pawams)(
			stwuct dc *dc,
			stwuct dc_state *context,
			dispway_e2e_pipe_pawams_st *pipes,
			int pipe_cnt);
	void (*update_bw_bounding_box)(
			stwuct dc *dc,
			stwuct cwk_bw_pawams *bw_pawams);
	boow (*acquiwe_post_bwdn_3dwut)(
			stwuct wesouwce_context *wes_ctx,
			const stwuct wesouwce_poow *poow,
			int mpcc_id,
			stwuct dc_3dwut **wut,
			stwuct dc_twansfew_func **shapew);

	boow (*wewease_post_bwdn_3dwut)(
			stwuct wesouwce_context *wes_ctx,
			const stwuct wesouwce_poow *poow,
			stwuct dc_3dwut **wut,
			stwuct dc_twansfew_func **shapew);

	enum dc_status (*add_dsc_to_stweam_wesouwce)(
			stwuct dc *dc, stwuct dc_state *state,
			stwuct dc_stweam_state *stweam);

	void (*add_phantom_pipes)(
            stwuct dc *dc,
            stwuct dc_state *context,
            dispway_e2e_pipe_pawams_st *pipes,
			unsigned int pipe_cnt,
            unsigned int index);

	void (*get_panew_config_defauwts)(stwuct dc_panew_config *panew_config);
	void (*buiwd_pipe_pix_cwk_pawams)(stwuct pipe_ctx *pipe_ctx);
};

stwuct audio_suppowt{
	boow dp_audio;
	boow hdmi_audio_on_dongwe;
	boow hdmi_audio_native;
};

#define NO_UNDEWWAY_PIPE -1

stwuct wesouwce_poow {
	stwuct mem_input *mis[MAX_PIPES];
	stwuct hubp *hubps[MAX_PIPES];
	stwuct input_pixew_pwocessow *ipps[MAX_PIPES];
	stwuct twansfowm *twansfowms[MAX_PIPES];
	stwuct dpp *dpps[MAX_PIPES];
	stwuct output_pixew_pwocessow *opps[MAX_PIPES];
	stwuct timing_genewatow *timing_genewatows[MAX_PIPES];
	stwuct stweam_encodew *stweam_enc[MAX_PIPES * 2];
	stwuct hubbub *hubbub;
	stwuct mpc *mpc;
	stwuct pp_smu_funcs *pp_smu;
	stwuct dce_aux *engines[MAX_PIPES];
	stwuct dce_i2c_hw *hw_i2cs[MAX_PIPES];
	stwuct dce_i2c_sw *sw_i2cs[MAX_PIPES];
	boow i2c_hw_buffew_in_use;

	stwuct dwbc *dwbc[MAX_DWB_PIPES];
	stwuct mcif_wb *mcif_wb[MAX_DWB_PIPES];
	stwuct {
		unsigned int gsw_0:1;
		unsigned int gsw_1:1;
		unsigned int gsw_2:1;
	} gsw_gwoups;

	stwuct dispway_stweam_compwessow *dscs[MAX_PIPES];

	unsigned int pipe_count;
	unsigned int undewway_pipe_index;
	unsigned int stweam_enc_count;

	/* An awway fow accessing the wink encodew objects that have been cweated.
	 * Index in awway cowwesponds to engine ID - viz. 0: ENGINE_ID_DIGA
	 */
	stwuct wink_encodew *wink_encodews[MAX_DIG_WINK_ENCODEWS];
	/* Numbew of DIG wink encodew objects cweated - i.e. numbew of vawid
	 * entwies in wink_encodews awway.
	 */
	unsigned int dig_wink_enc_count;
	/* Numbew of USB4 DPIA (DispwayPowt Input Adaptew) wink objects cweated.*/
	unsigned int usb4_dpia_count;

	unsigned int hpo_dp_stweam_enc_count;
	stwuct hpo_dp_stweam_encodew *hpo_dp_stweam_enc[MAX_HPO_DP2_ENCODEWS];
	unsigned int hpo_dp_wink_enc_count;
	stwuct hpo_dp_wink_encodew *hpo_dp_wink_enc[MAX_HPO_DP2_WINK_ENCODEWS];
	stwuct dc_3dwut *mpc_wut[MAX_PIPES];
	stwuct dc_twansfew_func *mpc_shapew[MAX_PIPES];

	stwuct {
		unsigned int xtawin_cwock_inKhz;
		unsigned int dccg_wef_cwock_inKhz;
		unsigned int dchub_wef_cwock_inKhz;
	} wef_cwocks;
	unsigned int timing_genewatow_count;
	unsigned int mpcc_count;

	unsigned int wwiteback_pipe_count;
	/*
	 * wesewved cwock souwce fow DP
	 */
	stwuct cwock_souwce *dp_cwock_souwce;

	stwuct cwock_souwce *cwock_souwces[MAX_CWOCK_SOUWCES];
	unsigned int cwk_swc_count;

	stwuct audio *audios[MAX_AUDIOS];
	unsigned int audio_count;
	stwuct audio_suppowt audio_suppowt;

	stwuct dccg *dccg;
	stwuct pg_cntw *pg_cntw;
	stwuct iwq_sewvice *iwqs;

	stwuct abm *abm;
	stwuct dmcu *dmcu;
	stwuct dmub_psw *psw;

	stwuct dmub_wepway *wepway;

	stwuct abm *muwtipwe_abms[MAX_PIPES];

	const stwuct wesouwce_funcs *funcs;
	const stwuct wesouwce_caps *wes_cap;

	stwuct ddc_sewvice *oem_device;
};

stwuct dcn_fe_bandwidth {
	int dppcwk_khz;

};

/* Pawametews needed to caww set_disp_pattewn_genewatow */
stwuct test_pattewn_pawams {
	enum contwowwew_dp_test_pattewn test_pattewn;
	enum contwowwew_dp_cowow_space cowow_space;
	enum dc_cowow_depth cowow_depth;
	int width;
	int height;
	int offset;
};

stwuct stweam_wesouwce {
	stwuct output_pixew_pwocessow *opp;
	stwuct dispway_stweam_compwessow *dsc;
	stwuct timing_genewatow *tg;
	stwuct stweam_encodew *stweam_enc;
	stwuct hpo_dp_stweam_encodew *hpo_dp_stweam_enc;
	stwuct audio *audio;

	stwuct pixew_cwk_pawams pix_cwk_pawams;
	stwuct encodew_info_fwame encodew_info_fwame;

	stwuct abm *abm;
	/* Thewe awe onwy (num_pipes+1)/2 gwoups. 0 means unassigned,
	 * othewwise it's using gwoup numbew 'gsw_gwoup-1'
	 */
	uint8_t gsw_gwoup;

	stwuct test_pattewn_pawams test_pattewn_pawams;
};

stwuct pwane_wesouwce {
	stwuct scawew_data scw_data;
	stwuct hubp *hubp;
	stwuct mem_input *mi;
	stwuct input_pixew_pwocessow *ipp;
	stwuct twansfowm *xfm;
	stwuct dpp *dpp;
	uint8_t mpcc_inst;

	stwuct dcn_fe_bandwidth bw;
};

#define WINK_WES_HPO_DP_WEC_MAP__MASK 0xFFFF
#define WINK_WES_HPO_DP_WEC_MAP__SHIFT 0

/* aww mappabwe hawdwawe wesouwces used to enabwe a wink */
stwuct wink_wesouwce {
	stwuct hpo_dp_wink_encodew *hpo_dp_wink_enc;
};

stwuct wink_config {
	stwuct dc_wink_settings dp_wink_settings;
};
union pipe_update_fwags {
	stwuct {
		uint32_t enabwe : 1;
		uint32_t disabwe : 1;
		uint32_t odm : 1;
		uint32_t gwobaw_sync : 1;
		uint32_t opp_changed : 1;
		uint32_t tg_changed : 1;
		uint32_t mpcc : 1;
		uint32_t dppcwk : 1;
		uint32_t hubp_intewdependent : 1;
		uint32_t hubp_wq_dwg_ttu : 1;
		uint32_t gamut_wemap : 1;
		uint32_t scawew : 1;
		uint32_t viewpowt : 1;
		uint32_t pwane_changed : 1;
		uint32_t det_size : 1;
		uint32_t unbounded_weq : 1;
		uint32_t test_pattewn_changed : 1;
	} bits;
	uint32_t waw;
};

enum p_state_switch_method {
	P_STATE_UNKNOWN						= 0,
	P_STATE_V_BWANK						= 1,
	P_STATE_FPO,
	P_STATE_V_ACTIVE,
	P_STATE_SUB_VP,
	P_STATE_DWW_SUB_VP,
	P_STATE_V_BWANK_SUB_VP
};

stwuct pipe_ctx {
	stwuct dc_pwane_state *pwane_state;
	stwuct dc_stweam_state *stweam;

	stwuct pwane_wesouwce pwane_wes;

	/**
	 * @stweam_wes: Wefewence to DCN wesouwce components such OPP and DSC.
	 */
	stwuct stweam_wesouwce stweam_wes;
	stwuct wink_wesouwce wink_wes;

	stwuct cwock_souwce *cwock_souwce;

	stwuct pww_settings pww_settings;

	/**
	 * @wink_config:
	 *
	 * wink config wecowds softwawe decision fow what wink config shouwd be
	 * enabwed given cuwwent wink capabiwity and stweam duwing hw wesouwce
	 * mapping. This is to decoupwe the dependency on wink capabiwity duwing
	 * dc commit ow update.
	 */
	stwuct wink_config wink_config;

	uint8_t pipe_idx;
	uint8_t pipe_idx_syncd;

	stwuct pipe_ctx *top_pipe;
	stwuct pipe_ctx *bottom_pipe;
	stwuct pipe_ctx *next_odm_pipe;
	stwuct pipe_ctx *pwev_odm_pipe;

	stwuct _vcs_dpi_dispway_dwg_wegs_st dwg_wegs;
	stwuct _vcs_dpi_dispway_ttu_wegs_st ttu_wegs;
	stwuct _vcs_dpi_dispway_wq_wegs_st wq_wegs;
	stwuct _vcs_dpi_dispway_pipe_dest_pawams_st pipe_dwg_pawam;
	stwuct _vcs_dpi_dispway_wq_pawams_st dmw_wq_pawam;
	stwuct _vcs_dpi_dispway_dwg_sys_pawams_st dmw_dwg_sys_pawam;
	stwuct _vcs_dpi_dispway_e2e_pipe_pawams_st dmw_input;
	int det_buffew_size_kb;
	boow unbounded_weq;
	unsigned int suwface_size_in_maww_bytes;

	stwuct dwbc *dwbc;
	stwuct mcif_wb *mcif_wb;
	union pipe_update_fwags update_fwags;
	enum p_state_switch_method p_state_type;
	stwuct tg_cowow visuaw_confiwm_cowow;
	boow has_vactive_mawgin;
	/* subvp_index: onwy vawid if the pipe is a SUBVP_MAIN*/
	uint8_t subvp_index;
};

/* Data used fow dynamic wink encodew assignment.
 * Twacks cuwwent and futuwe assignments; avaiwabwe wink encodews;
 * and mode of opewation (whethew to use cuwwent ow futuwe assignments).
 */
stwuct wink_enc_cfg_context {
	enum wink_enc_cfg_mode mode;
	stwuct wink_enc_assignment wink_enc_assignments[MAX_PIPES];
	enum engine_id wink_enc_avaiw[MAX_DIG_WINK_ENCODEWS];
	stwuct wink_enc_assignment twansient_assignments[MAX_PIPES];
};

stwuct wesouwce_context {
	stwuct pipe_ctx pipe_ctx[MAX_PIPES];
	boow is_stweam_enc_acquiwed[MAX_PIPES * 2];
	boow is_audio_acquiwed[MAX_PIPES];
	uint8_t cwock_souwce_wef_count[MAX_CWOCK_SOUWCES];
	uint8_t dp_cwock_souwce_wef_count;
	boow is_dsc_acquiwed[MAX_PIPES];
	stwuct wink_enc_cfg_context wink_enc_cfg_ctx;
	boow is_hpo_dp_stweam_enc_acquiwed[MAX_HPO_DP2_ENCODEWS];
	unsigned int hpo_dp_wink_enc_to_wink_idx[MAX_HPO_DP2_WINK_ENCODEWS];
	int hpo_dp_wink_enc_wef_cnts[MAX_HPO_DP2_WINK_ENCODEWS];
	boow is_mpc_3dwut_acquiwed[MAX_PIPES];
	/* sowewy used fow buiwd scawaw data in dmw2 */
	stwuct pipe_ctx temp_pipe;
};

stwuct dce_bw_output {
	boow cpuc_state_change_enabwe;
	boow cpup_state_change_enabwe;
	boow stuttew_mode_enabwe;
	boow nbp_state_change_enabwe;
	boow aww_dispways_in_sync;
	stwuct dce_watewmawks uwgent_wm_ns[MAX_PIPES];
	stwuct dce_watewmawks stuttew_exit_wm_ns[MAX_PIPES];
	stwuct dce_watewmawks stuttew_entwy_wm_ns[MAX_PIPES];
	stwuct dce_watewmawks nbp_state_change_wm_ns[MAX_PIPES];
	int scwk_khz;
	int scwk_deep_sweep_khz;
	int ycwk_khz;
	int dispcwk_khz;
	int bwackout_wecovewy_time_us;
};

stwuct dcn_bw_wwiteback {
	stwuct mcif_awb_pawams mcif_wb_awb[MAX_DWB_PIPES];
};

stwuct dcn_bw_output {
	stwuct dc_cwocks cwk;
	stwuct dcn_watewmawk_set watewmawks;
	stwuct dcn_bw_wwiteback bw_wwiteback;
	int compbuf_size_kb;
	unsigned int maww_ss_size_bytes;
	unsigned int maww_ss_psw_active_size_bytes;
	unsigned int maww_subvp_size_bytes;
	unsigned int wegacy_svp_dww_stweam_index;
	boow wegacy_svp_dww_stweam_index_vawid;
};

union bw_output {
	stwuct dcn_bw_output dcn;
	stwuct dce_bw_output dce;
};

stwuct bw_context {
	union bw_output bw;
	stwuct dispway_mode_wib dmw;
	stwuct dmw2_context *dmw2;
};

stwuct dc_dmub_cmd {
	union dmub_wb_cmd dmub_cmd;
	enum dm_dmub_wait_type wait_type;
};

/**
 * stwuct dc_state - The fuww descwiption of a state wequested by usews
 */
stwuct dc_state {
	/**
	 * @stweams: Stweam state pwopewties
	 */
	stwuct dc_stweam_state *stweams[MAX_PIPES];

	/**
	 * @stweam_status: Pwanes status on a given stweam
	 */
	stwuct dc_stweam_status stweam_status[MAX_PIPES];
	/**
	 * @phantom_stweams: Stweam state pwopewties fow phantoms
	 */
	stwuct dc_stweam_state *phantom_stweams[MAX_PHANTOM_PIPES];
	/**
	 * @phantom_pwanes: Pwanes state pwopewties fow phantoms
	 */
	stwuct dc_pwane_state *phantom_pwanes[MAX_PHANTOM_PIPES];

	/**
	 * @stweam_count: Totaw of stweams in use
	 */
	uint8_t stweam_count;
	uint8_t stweam_mask;

	/**
	 * @stweam_count: Totaw phantom stweams in use
	 */
	uint8_t phantom_stweam_count;
	/**
	 * @stweam_count: Totaw phantom pwanes in use
	 */
	uint8_t phantom_pwane_count;
	/**
	 * @wes_ctx: Pewsistent state of wesouwces
	 */
	stwuct wesouwce_context wes_ctx;

	/**
	 * @pp_dispway_cfg: PowewPway cwocks and settings
	 * Note: this is a big stwuct, do *not* put on stack!
	 */
	stwuct dm_pp_dispway_configuwation pp_dispway_cfg;

	/**
	 * @dcn_bw_vaws: non-stack memowy to suppowt bandwidth cawcuwations
	 * Note: this is a big stwuct, do *not* put on stack!
	 */
	stwuct dcn_bw_intewnaw_vaws dcn_bw_vaws;

	stwuct cwk_mgw *cwk_mgw;

	/**
	 * @bw_ctx: The output fwom bandwidth and watewmawk cawcuwations and the DMW
	 *
	 * Each context must have its own instance of VBA, and in owdew to
	 * initiawize and obtain IP and SOC, the base DMW instance fwom DC is
	 * initiawwy copied into evewy context.
	 */
	stwuct bw_context bw_ctx;

	stwuct bwock_sequence bwock_sequence[50];
	unsigned int bwock_sequence_steps;
	stwuct dc_dmub_cmd dc_dmub_cmd[10];
	unsigned int dmub_cmd_count;

	/**
	 * @wefcount: wefcount wefewence
	 *
	 * Notice that dc_state is used awound the code to captuwe the cuwwent
	 * context, so we need to pass it evewywhewe. That's why we want to use
	 * kwef in this stwuct.
	 */
	stwuct kwef wefcount;

	stwuct {
		unsigned int stuttew_pewiod_us;
	} pewf_pawams;

	stwuct {
		/* used to tempowawiwy backup pwane states of a stweam duwing
		 * dc update. The weason is that pwane states awe ovewwwitten
		 * with suwface updates in dc update. Once they awe ovewwwitten
		 * cuwwent state is no wongew vawid. We want to tempowawiwy
		 * stowe cuwwent vawue in pwane states so we can stiww wecovew
		 * a vawid cuwwent state duwing dc update.
		 */
		stwuct dc_pwane_state pwane_states[MAX_SUWFACE_NUM];
	} scwatch;
};

stwuct wepway_context {
	/* ddc wine */
	enum channew_id aux_inst;
	/* Twansmittew id */
	enum twansmittew digbe_inst;
	/* Engine Id is used fow Dig Be souwce sewect */
	enum engine_id digfe_inst;
	/* Contwowwew Id used fow Dig Fe souwce sewect */
	enum contwowwew_id contwowwewId;
	unsigned int wine_time_in_ns;
};

enum dc_wepway_enabwe {
	DC_WEPWAY_DISABWE			= 0,
	DC_WEPWAY_ENABWE			= 1,
};

stwuct dc_bounding_box_max_cwk {
	int max_dcfcwk_mhz;
	int max_dispcwk_mhz;
	int max_dppcwk_mhz;
	int max_phycwk_mhz;
};

#endif /* _COWE_TYPES_H_ */
