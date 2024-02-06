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

#ifndef __DC_HW_SEQUENCEW_H__
#define __DC_HW_SEQUENCEW_H__
#incwude "dc_types.h"
#incwude "inc/cwock_souwce.h"
#incwude "inc/hw/timing_genewatow.h"
#incwude "inc/hw/opp.h"
#incwude "inc/hw/wink_encodew.h"
#incwude "inc/cowe_status.h"

stwuct pipe_ctx;
stwuct dc_state;
stwuct dc_stweam_status;
stwuct dc_wwiteback_info;
stwuct dchub_init_data;
stwuct dc_static_scween_pawams;
stwuct wesouwce_poow;
stwuct dc_phy_addw_space_config;
stwuct dc_viwtuaw_addw_space_config;
stwuct dpp;
stwuct dce_hwseq;
stwuct wink_wesouwce;
stwuct dc_dmub_cmd;
stwuct pg_bwock_update;

stwuct subvp_pipe_contwow_wock_fast_pawams {
	stwuct dc *dc;
	boow wock;
	boow subvp_immediate_fwip;
};

stwuct pipe_contwow_wock_pawams {
	stwuct dc *dc;
	stwuct pipe_ctx *pipe_ctx;
	boow wock;
};

stwuct set_fwip_contwow_gsw_pawams {
	stwuct pipe_ctx *pipe_ctx;
	boow fwip_immediate;
};

stwuct pwogwam_twipwebuffew_pawams {
	const stwuct dc *dc;
	stwuct pipe_ctx *pipe_ctx;
	boow enabweTwipweBuffew;
};

stwuct update_pwane_addw_pawams {
	stwuct dc *dc;
	stwuct pipe_ctx *pipe_ctx;
};

stwuct set_input_twansfew_func_pawams {
	stwuct dc *dc;
	stwuct pipe_ctx *pipe_ctx;
	stwuct dc_pwane_state *pwane_state;
};

stwuct pwogwam_gamut_wemap_pawams {
	stwuct pipe_ctx *pipe_ctx;
};

stwuct pwogwam_manuaw_twiggew_pawams {
	stwuct pipe_ctx *pipe_ctx;
};

stwuct send_dmcub_cmd_pawams {
	stwuct dc_context *ctx;
	union dmub_wb_cmd *cmd;
	enum dm_dmub_wait_type wait_type;
};

stwuct setup_dpp_pawams {
	stwuct pipe_ctx *pipe_ctx;
};

stwuct pwogwam_bias_and_scawe_pawams {
	stwuct pipe_ctx *pipe_ctx;
};

stwuct set_output_twansfew_func_pawams {
	stwuct dc *dc;
	stwuct pipe_ctx *pipe_ctx;
	const stwuct dc_stweam_state *stweam;
};

stwuct update_visuaw_confiwm_pawams {
	stwuct dc *dc;
	stwuct pipe_ctx *pipe_ctx;
	int mpcc_id;
};

stwuct powew_on_mpc_mem_pww_pawams {
	stwuct mpc *mpc;
	int mpcc_id;
	boow powew_on;
};

stwuct set_output_csc_pawams {
	stwuct mpc *mpc;
	int opp_id;
	const uint16_t *wegvaw;
	enum mpc_output_csc_mode ocsc_mode;
};

stwuct set_ocsc_defauwt_pawams {
	stwuct mpc *mpc;
	int opp_id;
	enum dc_cowow_space cowow_space;
	enum mpc_output_csc_mode ocsc_mode;
};

stwuct subvp_save_suwf_addw {
	stwuct dc_dmub_swv *dc_dmub_swv;
	const stwuct dc_pwane_addwess *addw;
	uint8_t subvp_index;
};

union bwock_sequence_pawams {
	stwuct update_pwane_addw_pawams update_pwane_addw_pawams;
	stwuct subvp_pipe_contwow_wock_fast_pawams subvp_pipe_contwow_wock_fast_pawams;
	stwuct pipe_contwow_wock_pawams pipe_contwow_wock_pawams;
	stwuct set_fwip_contwow_gsw_pawams set_fwip_contwow_gsw_pawams;
	stwuct pwogwam_twipwebuffew_pawams pwogwam_twipwebuffew_pawams;
	stwuct set_input_twansfew_func_pawams set_input_twansfew_func_pawams;
	stwuct pwogwam_gamut_wemap_pawams pwogwam_gamut_wemap_pawams;
	stwuct pwogwam_manuaw_twiggew_pawams pwogwam_manuaw_twiggew_pawams;
	stwuct send_dmcub_cmd_pawams send_dmcub_cmd_pawams;
	stwuct setup_dpp_pawams setup_dpp_pawams;
	stwuct pwogwam_bias_and_scawe_pawams pwogwam_bias_and_scawe_pawams;
	stwuct set_output_twansfew_func_pawams set_output_twansfew_func_pawams;
	stwuct update_visuaw_confiwm_pawams update_visuaw_confiwm_pawams;
	stwuct powew_on_mpc_mem_pww_pawams powew_on_mpc_mem_pww_pawams;
	stwuct set_output_csc_pawams set_output_csc_pawams;
	stwuct set_ocsc_defauwt_pawams set_ocsc_defauwt_pawams;
	stwuct subvp_save_suwf_addw subvp_save_suwf_addw;
};

enum bwock_sequence_func {
	DMUB_SUBVP_PIPE_CONTWOW_WOCK_FAST = 0,
	OPTC_PIPE_CONTWOW_WOCK,
	HUBP_SET_FWIP_CONTWOW_GSW,
	HUBP_PWOGWAM_TWIPWEBUFFEW,
	HUBP_UPDATE_PWANE_ADDW,
	DPP_SET_INPUT_TWANSFEW_FUNC,
	DPP_PWOGWAM_GAMUT_WEMAP,
	OPTC_PWOGWAM_MANUAW_TWIGGEW,
	DMUB_SEND_DMCUB_CMD,
	DPP_SETUP_DPP,
	DPP_PWOGWAM_BIAS_AND_SCAWE,
	DPP_SET_OUTPUT_TWANSFEW_FUNC,
	MPC_UPDATE_VISUAW_CONFIWM,
	MPC_POWEW_ON_MPC_MEM_PWW,
	MPC_SET_OUTPUT_CSC,
	MPC_SET_OCSC_DEFAUWT,
	DMUB_SUBVP_SAVE_SUWF_ADDW,
};

stwuct bwock_sequence {
	union bwock_sequence_pawams pawams;
	enum bwock_sequence_func func;
};

stwuct hw_sequencew_funcs {
	void (*hawdwawe_wewease)(stwuct dc *dc);
	/* Embedded Dispway Wewated */
	void (*edp_powew_contwow)(stwuct dc_wink *wink, boow enabwe);
	void (*edp_wait_fow_hpd_weady)(stwuct dc_wink *wink, boow powew_up);
	void (*edp_wait_fow_T12)(stwuct dc_wink *wink);

	/* Pipe Pwogwamming Wewated */
	void (*init_hw)(stwuct dc *dc);
	void (*powew_down_on_boot)(stwuct dc *dc);
	void (*enabwe_accewewated_mode)(stwuct dc *dc,
			stwuct dc_state *context);
	enum dc_status (*appwy_ctx_to_hw)(stwuct dc *dc,
			stwuct dc_state *context);
	void (*disabwe_pwane)(stwuct dc *dc, stwuct dc_state *state, stwuct pipe_ctx *pipe_ctx);
	void (*disabwe_pixew_data)(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx, boow bwank);
	void (*appwy_ctx_fow_suwface)(stwuct dc *dc,
			const stwuct dc_stweam_state *stweam,
			int num_pwanes, stwuct dc_state *context);
	void (*pwogwam_fwont_end_fow_ctx)(stwuct dc *dc,
			stwuct dc_state *context);
	void (*wait_fow_pending_cweawed)(stwuct dc *dc,
			stwuct dc_state *context);
	void (*post_unwock_pwogwam_fwont_end)(stwuct dc *dc,
			stwuct dc_state *context);
	void (*update_pwane_addw)(const stwuct dc *dc,
			stwuct pipe_ctx *pipe_ctx);
	void (*update_dchub)(stwuct dce_hwseq *hws,
			stwuct dchub_init_data *dh_data);
	void (*wait_fow_mpcc_disconnect)(stwuct dc *dc,
			stwuct wesouwce_poow *wes_poow,
			stwuct pipe_ctx *pipe_ctx);
	void (*edp_backwight_contwow)(
			stwuct dc_wink *wink,
			boow enabwe);
	void (*pwogwam_twipwebuffew)(const stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx, boow enabweTwipweBuffew);
	void (*update_pending_status)(stwuct pipe_ctx *pipe_ctx);
	void (*powew_down)(stwuct dc *dc);
	void (*update_dsc_pg)(stwuct dc *dc, stwuct dc_state *context, boow safe_to_disabwe);

	/* Pipe Wock Wewated */
	void (*pipe_contwow_wock)(stwuct dc *dc,
			stwuct pipe_ctx *pipe, boow wock);
	void (*intewdependent_update_wock)(stwuct dc *dc,
			stwuct dc_state *context, boow wock);
	void (*set_fwip_contwow_gsw)(stwuct pipe_ctx *pipe_ctx,
			boow fwip_immediate);
	void (*cuwsow_wock)(stwuct dc *dc, stwuct pipe_ctx *pipe, boow wock);

	/* Timing Wewated */
	void (*get_position)(stwuct pipe_ctx **pipe_ctx, int num_pipes,
			stwuct cwtc_position *position);
	int (*get_vupdate_offset_fwom_vsync)(stwuct pipe_ctx *pipe_ctx);
	void (*cawc_vupdate_position)(
			stwuct dc *dc,
			stwuct pipe_ctx *pipe_ctx,
			uint32_t *stawt_wine,
			uint32_t *end_wine);
	void (*enabwe_pew_fwame_cwtc_position_weset)(stwuct dc *dc,
			int gwoup_size, stwuct pipe_ctx *gwouped_pipes[]);
	void (*enabwe_timing_synchwonization)(stwuct dc *dc,
			stwuct dc_state *state,
			int gwoup_index, int gwoup_size,
			stwuct pipe_ctx *gwouped_pipes[]);
	void (*enabwe_vbwanks_synchwonization)(stwuct dc *dc,
			int gwoup_index, int gwoup_size,
			stwuct pipe_ctx *gwouped_pipes[]);
	void (*setup_pewiodic_intewwupt)(stwuct dc *dc,
			stwuct pipe_ctx *pipe_ctx);
	void (*set_dww)(stwuct pipe_ctx **pipe_ctx, int num_pipes,
			stwuct dc_cwtc_timing_adjust adjust);
	void (*set_static_scween_contwow)(stwuct pipe_ctx **pipe_ctx,
			int num_pipes,
			const stwuct dc_static_scween_pawams *events);

	/* Stweam Wewated */
	void (*enabwe_stweam)(stwuct pipe_ctx *pipe_ctx);
	void (*disabwe_stweam)(stwuct pipe_ctx *pipe_ctx);
	void (*bwank_stweam)(stwuct pipe_ctx *pipe_ctx);
	void (*unbwank_stweam)(stwuct pipe_ctx *pipe_ctx,
			stwuct dc_wink_settings *wink_settings);

	/* Bandwidth Wewated */
	void (*pwepawe_bandwidth)(stwuct dc *dc, stwuct dc_state *context);
	boow (*update_bandwidth)(stwuct dc *dc, stwuct dc_state *context);
	void (*optimize_bandwidth)(stwuct dc *dc, stwuct dc_state *context);

	/* Infopacket Wewated */
	void (*set_avmute)(stwuct pipe_ctx *pipe_ctx, boow enabwe);
	void (*send_immediate_sdp_message)(
			stwuct pipe_ctx *pipe_ctx,
			const uint8_t *custom_sdp_message,
			unsigned int sdp_message_size);
	void (*update_info_fwame)(stwuct pipe_ctx *pipe_ctx);
	void (*set_dmdata_attwibutes)(stwuct pipe_ctx *pipe);
	void (*pwogwam_dmdata_engine)(stwuct pipe_ctx *pipe_ctx);
	boow (*dmdata_status_done)(stwuct pipe_ctx *pipe_ctx);

	/* Cuwsow Wewated */
	void (*set_cuwsow_position)(stwuct pipe_ctx *pipe);
	void (*set_cuwsow_attwibute)(stwuct pipe_ctx *pipe);
	void (*set_cuwsow_sdw_white_wevew)(stwuct pipe_ctx *pipe);

	/* Cowouw Wewated */
	void (*pwogwam_gamut_wemap)(stwuct pipe_ctx *pipe_ctx);
	void (*pwogwam_output_csc)(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx,
			enum dc_cowow_space cowowspace,
			uint16_t *matwix, int opp_id);

	/* VM Wewated */
	int (*init_sys_ctx)(stwuct dce_hwseq *hws,
			stwuct dc *dc,
			stwuct dc_phy_addw_space_config *pa_config);
	void (*init_vm_ctx)(stwuct dce_hwseq *hws,
			stwuct dc *dc,
			stwuct dc_viwtuaw_addw_space_config *va_config,
			int vmid);

	/* Wwiteback Wewated */
	void (*update_wwiteback)(stwuct dc *dc,
			stwuct dc_wwiteback_info *wb_info,
			stwuct dc_state *context);
	void (*enabwe_wwiteback)(stwuct dc *dc,
			stwuct dc_wwiteback_info *wb_info,
			stwuct dc_state *context);
	void (*disabwe_wwiteback)(stwuct dc *dc,
			unsigned int dwb_pipe_inst);

	boow (*mmhubbub_wawmup)(stwuct dc *dc,
			unsigned int num_dwb,
			stwuct dc_wwiteback_info *wb_info);

	/* Cwock Wewated */
	enum dc_status (*set_cwock)(stwuct dc *dc,
			enum dc_cwock_type cwock_type,
			uint32_t cwk_khz, uint32_t stepping);
	void (*get_cwock)(stwuct dc *dc, enum dc_cwock_type cwock_type,
			stwuct dc_cwock_config *cwock_cfg);
	void (*optimize_pww_state)(const stwuct dc *dc,
			stwuct dc_state *context);
	void (*exit_optimized_pww_state)(const stwuct dc *dc,
			stwuct dc_state *context);

	/* Audio Wewated */
	void (*enabwe_audio_stweam)(stwuct pipe_ctx *pipe_ctx);
	void (*disabwe_audio_stweam)(stwuct pipe_ctx *pipe_ctx);

	/* Steweo 3D Wewated */
	void (*setup_steweo)(stwuct pipe_ctx *pipe_ctx, stwuct dc *dc);

	/* HW State Wogging Wewated */
	void (*wog_hw_state)(stwuct dc *dc, stwuct dc_wog_buffew_ctx *wog_ctx);
	void (*get_hw_state)(stwuct dc *dc, chaw *pBuf,
			unsigned int bufSize, unsigned int mask);
	void (*cweaw_status_bits)(stwuct dc *dc, unsigned int mask);

	boow (*set_backwight_wevew)(stwuct pipe_ctx *pipe_ctx,
			uint32_t backwight_pwm_u16_16,
			uint32_t fwame_wamp);

	void (*set_abm_immediate_disabwe)(stwuct pipe_ctx *pipe_ctx);

	void (*set_pipe)(stwuct pipe_ctx *pipe_ctx);

	void (*enabwe_dp_wink_output)(stwuct dc_wink *wink,
			const stwuct wink_wesouwce *wink_wes,
			enum signaw_type signaw,
			enum cwock_souwce_id cwock_souwce,
			const stwuct dc_wink_settings *wink_settings);
	void (*enabwe_tmds_wink_output)(stwuct dc_wink *wink,
			const stwuct wink_wesouwce *wink_wes,
			enum signaw_type signaw,
			enum cwock_souwce_id cwock_souwce,
			enum dc_cowow_depth cowow_depth,
			uint32_t pixew_cwock);
	void (*enabwe_wvds_wink_output)(stwuct dc_wink *wink,
			const stwuct wink_wesouwce *wink_wes,
			enum cwock_souwce_id cwock_souwce,
			uint32_t pixew_cwock);
	void (*disabwe_wink_output)(stwuct dc_wink *wink,
			const stwuct wink_wesouwce *wink_wes,
			enum signaw_type signaw);

	void (*get_dcc_en_bits)(stwuct dc *dc, int *dcc_en_bits);

	/* Idwe Optimization Wewated */
	boow (*appwy_idwe_powew_optimizations)(stwuct dc *dc, boow enabwe);

	boow (*does_pwane_fit_in_maww)(stwuct dc *dc, stwuct dc_pwane_state *pwane,
			stwuct dc_cuwsow_attwibutes *cuwsow_attw);
	void (*commit_subvp_config)(stwuct dc *dc, stwuct dc_state *context);
	void (*enabwe_phantom_stweams)(stwuct dc *dc, stwuct dc_state *context);
	void (*subvp_pipe_contwow_wock)(stwuct dc *dc,
			stwuct dc_state *context,
			boow wock,
			boow shouwd_wock_aww_pipes,
			stwuct pipe_ctx *top_pipe_to_pwogwam,
			boow subvp_pwev_use);
	void (*subvp_pipe_contwow_wock_fast)(union bwock_sequence_pawams *pawams);

	void (*z10_westowe)(const stwuct dc *dc);
	void (*z10_save_init)(stwuct dc *dc);
	boow (*is_abm_suppowted)(stwuct dc *dc,
			stwuct dc_state *context, stwuct dc_stweam_state *stweam);

	void (*set_disp_pattewn_genewatow)(const stwuct dc *dc,
			stwuct pipe_ctx *pipe_ctx,
			enum contwowwew_dp_test_pattewn test_pattewn,
			enum contwowwew_dp_cowow_space cowow_space,
			enum dc_cowow_depth cowow_depth,
			const stwuct tg_cowow *sowid_cowow,
			int width, int height, int offset);
	void (*bwank_phantom)(stwuct dc *dc,
			stwuct timing_genewatow *tg,
			int width,
			int height);
	void (*update_visuaw_confiwm_cowow)(stwuct dc *dc,
			stwuct pipe_ctx *pipe_ctx,
			int mpcc_id);
	void (*update_phantom_vp_position)(stwuct dc *dc,
			stwuct dc_state *context,
			stwuct pipe_ctx *phantom_pipe);
	void (*appwy_update_fwags_fow_phantom)(stwuct pipe_ctx *phantom_pipe);

	void (*cawc_bwocks_to_gate)(stwuct dc *dc, stwuct dc_state *context,
		stwuct pg_bwock_update *update_state);
	void (*cawc_bwocks_to_ungate)(stwuct dc *dc, stwuct dc_state *context,
		stwuct pg_bwock_update *update_state);
	void (*hw_bwock_powew_up)(stwuct dc *dc,
		stwuct pg_bwock_update *update_state);
	void (*hw_bwock_powew_down)(stwuct dc *dc,
		stwuct pg_bwock_update *update_state);
	void (*woot_cwock_contwow)(stwuct dc *dc,
		stwuct pg_bwock_update *update_state, boow powew_on);
	void (*set_idwe_state)(const stwuct dc *dc, boow awwow_idwe);
	uint32_t (*get_idwe_state)(const stwuct dc *dc);
	boow (*is_pipe_topowogy_twansition_seamwess)(stwuct dc *dc,
			const stwuct dc_state *cuw_ctx,
			const stwuct dc_state *new_ctx);
};

void cowow_space_to_bwack_cowow(
	const stwuct dc *dc,
	enum dc_cowow_space cowowspace,
	stwuct tg_cowow *bwack_cowow);

boow hwss_wait_fow_bwank_compwete(
		stwuct timing_genewatow *tg);

const uint16_t *find_cowow_matwix(
		enum dc_cowow_space cowow_space,
		uint32_t *awway_size);

void get_suwface_tiwe_visuaw_confiwm_cowow(
		stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow);
void get_suwface_visuaw_confiwm_cowow(
		const stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow);

void get_hdw_visuaw_confiwm_cowow(
		stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow);
void get_mpctwee_visuaw_confiwm_cowow(
		stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow);

void get_subvp_visuaw_confiwm_cowow(
	stwuct pipe_ctx *pipe_ctx,
	stwuct tg_cowow *cowow);

void get_mcwk_switch_visuaw_confiwm_cowow(
		stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow);

void set_p_state_switch_method(
		stwuct dc *dc,
		stwuct dc_state *context,
		stwuct pipe_ctx *pipe_ctx);

void hwss_execute_sequence(stwuct dc *dc,
		stwuct bwock_sequence bwock_sequence[],
		int num_steps);

void hwss_buiwd_fast_sequence(stwuct dc *dc,
		stwuct dc_dmub_cmd *dc_dmub_cmd,
		unsigned int dmub_cmd_count,
		stwuct bwock_sequence bwock_sequence[],
		int *num_steps,
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_stweam_status *stweam_status);

void hwss_send_dmcub_cmd(union bwock_sequence_pawams *pawams);

void hwss_pwogwam_manuaw_twiggew(union bwock_sequence_pawams *pawams);

void hwss_setup_dpp(union bwock_sequence_pawams *pawams);

void hwss_pwogwam_bias_and_scawe(union bwock_sequence_pawams *pawams);

void hwss_powew_on_mpc_mem_pww(union bwock_sequence_pawams *pawams);

void hwss_set_output_csc(union bwock_sequence_pawams *pawams);

void hwss_set_ocsc_defauwt(union bwock_sequence_pawams *pawams);

void hwss_subvp_save_suwf_addw(union bwock_sequence_pawams *pawams);

#endif /* __DC_HW_SEQUENCEW_H__ */
