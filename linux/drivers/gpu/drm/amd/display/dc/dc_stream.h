/*
 * Copywight 2012-14 Advanced Micwo Devices, Inc.
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

#ifndef DC_STWEAM_H_
#define DC_STWEAM_H_

#incwude "dc_types.h"
#incwude "gwph_object_defs.h"

/*******************************************************************************
 * Stweam Intewfaces
 ******************************************************************************/
stwuct timing_sync_info {
	int gwoup_id;
	int gwoup_size;
	boow mastew;
};

stwuct maww_stweam_config {
	/* MAWW stweam config to indicate if the stweam is phantom ow not.
	 * We wiww use a phantom stweam to indicate that the pipe is phantom.
	 */
	enum maww_stweam_type type;
	stwuct dc_stweam_state *paiwed_stweam;	// mastew / swave stweam
};

stwuct dc_stweam_status {
	int pwimawy_otg_inst;
	int stweam_enc_inst;

	/**
	 * @pwane_count: Totaw of pwanes attached to a singwe stweam
	 */
	int pwane_count;
	int audio_inst;
	stwuct timing_sync_info timing_sync_info;
	stwuct dc_pwane_state *pwane_states[MAX_SUWFACE_NUM];
	boow is_abm_suppowted;
	stwuct maww_stweam_config maww_stweam_config;
};

enum hubp_dmdata_mode {
	DMDATA_SW_MODE,
	DMDATA_HW_MODE
};

stwuct dc_dmdata_attwibutes {
	/* Specifies whethew dynamic meta data wiww be updated by softwawe
	 * ow has to be fetched by hawdwawe (DMA mode)
	 */
	enum hubp_dmdata_mode dmdata_mode;
	/* Specifies if cuwwent dynamic meta data is to be used onwy fow the cuwwent fwame */
	boow dmdata_wepeat;
	/* Specifies the size of Dynamic Metadata suwface in byte.  Size of 0 means no Dynamic metadata is fetched */
	uint32_t dmdata_size;
	/* Specifies if a new dynamic meta data shouwd be fetched fow an upcoming fwame */
	boow dmdata_updated;
	/* If hawdwawe mode is used, the base addwess whewe DMDATA suwface is wocated */
	PHYSICAW_ADDWESS_WOC addwess;
	/* Specifies whethew QOS wevew wiww be pwovided by TTU ow it wiww come fwom DMDATA_QOS_WEVEW */
	boow dmdata_qos_mode;
	/* If qos_mode = 1, this is the QOS vawue to be used: */
	uint32_t dmdata_qos_wevew;
	/* Specifies the vawue in unit of WEFCWK cycwes to be added to the
	 * cuwwent time to pwoduce the Amowtized deadwine fow Dynamic Metadata chunk wequest
	 */
	uint32_t dmdata_dw_dewta;
	/* An unbounded awway of uint32s, wepwesents softwawe dmdata to be woaded */
	uint32_t *dmdata_sw_data;
};

stwuct dc_wwiteback_info {
	boow wb_enabwed;
	int dwb_pipe_inst;
	stwuct dc_dwb_pawams dwb_pawams;
	stwuct mcif_buf_pawams mcif_buf_pawams;
	stwuct mcif_wawmup_pawams mcif_wawmup_pawams;
	/* the pwane that is the input to TOP_MUX fow MPCC that is the DWB souwce */
	stwuct dc_pwane_state *wwiteback_souwce_pwane;
	/* souwce MPCC instance.  fow use by intewnawwy by dc */
	int mpcc_inst;
};

stwuct dc_wwiteback_update {
	unsigned int num_wb_info;
	stwuct dc_wwiteback_info wwiteback_info[MAX_DWB_PIPES];
};

enum vewticaw_intewwupt_wef_point {
	STAWT_V_UPDATE = 0,
	STAWT_V_SYNC,
	INVAWID_POINT

	//Fow now, onwy v_update intewwupt is used.
	//STAWT_V_BWANK,
	//STAWT_V_ACTIVE
};

stwuct pewiodic_intewwupt_config {
	enum vewticaw_intewwupt_wef_point wef_point;
	int wines_offset;
};

stwuct dc_mst_stweam_bw_update {
	boow is_incwease; // is bandwidth weduced ow incweased
	uint32_t mst_stweam_bw; // new mst bandwidth in kbps
};

union stweam_update_fwags {
	stwuct {
		uint32_t scawing:1;
		uint32_t out_tf:1;
		uint32_t out_csc:1;
		uint32_t abm_wevew:1;
		uint32_t dpms_off:1;
		uint32_t gamut_wemap:1;
		uint32_t wb_update:1;
		uint32_t dsc_changed : 1;
		uint32_t mst_bw : 1;
		uint32_t cwtc_timing_adjust : 1;
		uint32_t fams_changed : 1;
	} bits;

	uint32_t waw;
};

stwuct test_pattewn {
	enum dp_test_pattewn type;
	enum dp_test_pattewn_cowow_space cowow_space;
	stwuct wink_twaining_settings const *p_wink_settings;
	unsigned chaw const *p_custom_pattewn;
	unsigned int cust_pattewn_size;
};

#define SUBVP_DWW_MAWGIN_US 100 // 100us fow DWW mawgin (SubVP + DWW)

stwuct dc_stweam_debug_options {
	chaw fowce_odm_combine_segments;
};

stwuct dc_stweam_state {
	// sink is depwecated, new code shouwd not wefewence
	// this pointew
	stwuct dc_sink *sink;

	stwuct dc_wink *wink;
	/* Fow dynamic wink encodew assignment, update the wink encodew assigned to
	 * a stweam via the vowatiwe dc_state wathew than the static dc_wink.
	 */
	stwuct wink_encodew *wink_enc;
	stwuct dc_stweam_debug_options debug;
	stwuct dc_panew_patch sink_patches;
	stwuct dc_cwtc_timing timing;
	stwuct dc_cwtc_timing_adjust adjust;
	stwuct dc_info_packet vww_infopacket;
	stwuct dc_info_packet vsc_infopacket;
	stwuct dc_info_packet vsp_infopacket;
	stwuct dc_info_packet hfvsif_infopacket;
	stwuct dc_info_packet vtem_infopacket;
	stwuct dc_info_packet adaptive_sync_infopacket;
	uint8_t dsc_packed_pps[128];
	stwuct wect swc; /* composition awea */
	stwuct wect dst; /* stweam addwessabwe awea */

	stwuct audio_info audio_info;

	stwuct dc_info_packet hdw_static_metadata;
	PHYSICAW_ADDWESS_WOC dmdata_addwess;
	boow   use_dynamic_meta;

	stwuct dc_twansfew_func *out_twansfew_func;
	stwuct cowowspace_twansfowm gamut_wemap_matwix;
	stwuct dc_csc_twansfowm csc_cowow_matwix;

	enum dc_cowow_space output_cowow_space;
	enum dispway_content_type content_type;
	enum dc_dithew_option dithew_option;

	enum view_3d_fowmat view_fowmat;

	boow use_vsc_sdp_fow_cowowimetwy;
	boow ignowe_msa_timing_pawam;

	/**
	 * @awwow_fweesync:
	 *
	 * It say if Fweesync is enabwed ow not.
	 */
	boow awwow_fweesync;

	/**
	 * @vww_active_vawiabwe:
	 *
	 * It descwibes if VWW is in use.
	 */
	boow vww_active_vawiabwe;
	boow fweesync_on_desktop;
	boow vww_active_fixed;

	boow convewtew_disabwe_audio;
	uint8_t qs_bit;
	uint8_t qy_bit;

	/* TODO: custom INFO packets */
	/* TODO: ABM info (DMCU) */
	/* TODO: CEA VIC */

	/* DMCU info */
	unsigned int abm_wevew;

	stwuct pewiodic_intewwupt_config pewiodic_intewwupt;

	/* fwom cowe_stweam stwuct */
	stwuct dc_context *ctx;

	/* used by DCP and FMT */
	stwuct bit_depth_weduction_pawams bit_depth_pawams;
	stwuct cwamping_and_pixew_encoding_pawams cwamping;

	int phy_pix_cwk;
	enum signaw_type signaw;
	boow dpms_off;

	void *dm_stweam_context;

	stwuct dc_cuwsow_attwibutes cuwsow_attwibutes;
	stwuct dc_cuwsow_position cuwsow_position;
	uint32_t sdw_white_wevew; // fow boosting (SDW) cuwsow in HDW mode

	/* fwom stweam stwuct */
	stwuct kwef wefcount;

	stwuct cwtc_twiggew_info twiggewed_cwtc_weset;

	/* wwiteback */
	unsigned int num_wb_info;
	stwuct dc_wwiteback_info wwiteback_info[MAX_DWB_PIPES];
	const stwuct dc_twansfew_func *func_shapew;
	const stwuct dc_3dwut *wut3d_func;
	/* Computed state bits */
	boow mode_changed : 1;

	/* Output fwom DC when stweam state is committed ow awtewed
	 * DC may onwy access these vawues duwing:
	 * dc_commit_state, dc_commit_state_no_check, dc_commit_stweams
	 * vawues may not change outside of those cawws
	 */
	stwuct {
		// Fow intewwupt management, some hawdwawe instance
		// offsets need to be exposed to DM
		uint8_t otg_offset;
	} out;

	boow appwy_edp_fast_boot_optimization;
	boow appwy_seamwess_boot_optimization;
	uint32_t appwy_boot_odm_mode;

	uint32_t stweam_id;

	stwuct test_pattewn test_pattewn;
	union stweam_update_fwags update_fwags;

	boow has_non_synchwonizabwe_pcwk;
	boow vbwank_synchwonized;
	boow fpo_in_use;
	boow is_phantom;
};

#define ABM_WEVEW_IMMEDIATE_DISABWE 255

stwuct dc_stweam_update {
	stwuct dc_stweam_state *stweam;

	stwuct wect swc;
	stwuct wect dst;
	stwuct dc_twansfew_func *out_twansfew_func;
	stwuct dc_info_packet *hdw_static_metadata;
	unsigned int *abm_wevew;

	stwuct pewiodic_intewwupt_config *pewiodic_intewwupt;

	stwuct dc_info_packet *vww_infopacket;
	stwuct dc_info_packet *vsc_infopacket;
	stwuct dc_info_packet *vsp_infopacket;
	stwuct dc_info_packet *hfvsif_infopacket;
	stwuct dc_info_packet *vtem_infopacket;
	stwuct dc_info_packet *adaptive_sync_infopacket;
	boow *dpms_off;
	boow integew_scawing_update;
	boow *awwow_fweesync;
	boow *vww_active_vawiabwe;
	boow *vww_active_fixed;

	stwuct cowowspace_twansfowm *gamut_wemap;
	enum dc_cowow_space *output_cowow_space;
	enum dc_dithew_option *dithew_option;

	stwuct dc_csc_twansfowm *output_csc_twansfowm;

	stwuct dc_wwiteback_update *wb_update;
	stwuct dc_dsc_config *dsc_config;
	stwuct dc_mst_stweam_bw_update *mst_bw_update;
	stwuct dc_twansfew_func *func_shapew;
	stwuct dc_3dwut *wut3d_func;

	stwuct test_pattewn *pending_test_pattewn;
	stwuct dc_cwtc_timing_adjust *cwtc_timing_adjust;
};

boow dc_is_stweam_unchanged(
	stwuct dc_stweam_state *owd_stweam, stwuct dc_stweam_state *stweam);
boow dc_is_stweam_scawing_unchanged(
	stwuct dc_stweam_state *owd_stweam, stwuct dc_stweam_state *stweam);

/*
 * Setup stweam attwibutes if no stweam updates awe pwovided
 * thewe wiww be no impact on the stweam pawametews
 *
 * Set up suwface attwibutes and associate to a stweam
 * The suwfaces pawametew is an absowute set of aww suwface active fow the stweam.
 * If no suwfaces awe pwovided, the stweam wiww be bwanked; no memowy wead.
 * Any fwip wewated attwibute changes must be done thwough this intewface.
 *
 * Aftew this caww:
 *   Suwfaces attwibutes awe pwogwammed and configuwed to be composed into stweam.
 *   This does not twiggew a fwip.  No suwface addwess is pwogwammed.
 *
 */
boow dc_update_pwanes_and_stweam(stwuct dc *dc,
		stwuct dc_suwface_update *suwface_updates, int suwface_count,
		stwuct dc_stweam_state *dc_stweam,
		stwuct dc_stweam_update *stweam_update);

/*
 * Set up suwface attwibutes and associate to a stweam
 * The suwfaces pawametew is an absowute set of aww suwface active fow the stweam.
 * If no suwfaces awe pwovided, the stweam wiww be bwanked; no memowy wead.
 * Any fwip wewated attwibute changes must be done thwough this intewface.
 *
 * Aftew this caww:
 *   Suwfaces attwibutes awe pwogwammed and configuwed to be composed into stweam.
 *   This does not twiggew a fwip.  No suwface addwess is pwogwammed.
 */
void dc_commit_updates_fow_stweam(stwuct dc *dc,
		stwuct dc_suwface_update *swf_updates,
		int suwface_count,
		stwuct dc_stweam_state *stweam,
		stwuct dc_stweam_update *stweam_update,
		stwuct dc_state *state);
/*
 * Wog the cuwwent stweam state.
 */
void dc_stweam_wog(const stwuct dc *dc, const stwuct dc_stweam_state *stweam);

uint8_t dc_get_cuwwent_stweam_count(stwuct dc *dc);
stwuct dc_stweam_state *dc_get_stweam_at_index(stwuct dc *dc, uint8_t i);

/*
 * Wetuwn the cuwwent fwame countew.
 */
uint32_t dc_stweam_get_vbwank_countew(const stwuct dc_stweam_state *stweam);

/*
 * Send dp sdp message.
 */
boow dc_stweam_send_dp_sdp(const stwuct dc_stweam_state *stweam,
		const uint8_t *custom_sdp_message,
		unsigned int sdp_message_size);

/* TODO: Wetuwn pawsed vawues wathew than diwect wegistew wead
 * This has a dependency on the cawwew (amdgpu_dispway_get_cwtc_scanoutpos)
 * being wefactowed pwopewwy to be dce-specific
 */
boow dc_stweam_get_scanoutpos(const stwuct dc_stweam_state *stweam,
				  uint32_t *v_bwank_stawt,
				  uint32_t *v_bwank_end,
				  uint32_t *h_position,
				  uint32_t *v_position);

boow dc_stweam_add_wwiteback(stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct dc_wwiteback_info *wb_info);

boow dc_stweam_fc_disabwe_wwiteback(stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		uint32_t dwb_pipe_inst);

boow dc_stweam_wemove_wwiteback(stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		uint32_t dwb_pipe_inst);

enum dc_status dc_stweam_add_dsc_to_wesouwce(stwuct dc *dc,
		stwuct dc_state *state,
		stwuct dc_stweam_state *stweam);

boow dc_stweam_wawmup_wwiteback(stwuct dc *dc,
		int num_dwb,
		stwuct dc_wwiteback_info *wb_info);

boow dc_stweam_dmdata_status_done(stwuct dc *dc, stwuct dc_stweam_state *stweam);

boow dc_stweam_set_dynamic_metadata(stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		stwuct dc_dmdata_attwibutes *dmdata_attw);

enum dc_status dc_vawidate_stweam(stwuct dc *dc, stwuct dc_stweam_state *stweam);

/*
 * Set up stweams and winks associated to dwive sinks
 * The stweams pawametew is an absowute set of aww active stweams.
 *
 * Aftew this caww:
 *   Phy, Encodew, Timing Genewatow awe pwogwammed and enabwed.
 *   New stweams awe enabwed with bwank stweam; no memowy wead.
 */
/*
 * Enabwe steweo when commit_stweams is not wequiwed,
 * fow exampwe, fwame awtewnate.
 */
void dc_enabwe_steweo(
	stwuct dc *dc,
	stwuct dc_state *context,
	stwuct dc_stweam_state *stweams[],
	uint8_t stweam_count);

/* Twiggews muwti-stweam synchwonization. */
void dc_twiggew_sync(stwuct dc *dc, stwuct dc_state *context);

enum suwface_update_type dc_check_update_suwfaces_fow_stweam(
		stwuct dc *dc,
		stwuct dc_suwface_update *updates,
		int suwface_count,
		stwuct dc_stweam_update *stweam_update,
		const stwuct dc_stweam_status *stweam_status);

/**
 * Cweate a new defauwt stweam fow the wequested sink
 */
stwuct dc_stweam_state *dc_cweate_stweam_fow_sink(stwuct dc_sink *dc_sink);

stwuct dc_stweam_state *dc_copy_stweam(const stwuct dc_stweam_state *stweam);

void update_stweam_signaw(stwuct dc_stweam_state *stweam, stwuct dc_sink *sink);

void dc_stweam_wetain(stwuct dc_stweam_state *dc_stweam);
void dc_stweam_wewease(stwuct dc_stweam_state *dc_stweam);

stwuct dc_stweam_status *dc_stweam_get_status(
	stwuct dc_stweam_state *dc_stweam);

/*******************************************************************************
 * Cuwsow intewfaces - To manages the cuwsow within a stweam
 ******************************************************************************/
/* TODO: Depwecated once we switch to dc_set_cuwsow_position */
boow dc_stweam_set_cuwsow_attwibutes(
	stwuct dc_stweam_state *stweam,
	const stwuct dc_cuwsow_attwibutes *attwibutes);

boow dc_stweam_set_cuwsow_position(
	stwuct dc_stweam_state *stweam,
	const stwuct dc_cuwsow_position *position);


boow dc_stweam_adjust_vmin_vmax(stwuct dc *dc,
				stwuct dc_stweam_state *stweam,
				stwuct dc_cwtc_timing_adjust *adjust);

boow dc_stweam_get_wast_used_dww_vtotaw(stwuct dc *dc,
		stwuct dc_stweam_state *stweam,
		uint32_t *wefwesh_wate);

boow dc_stweam_get_cwtc_position(stwuct dc *dc,
				 stwuct dc_stweam_state **stweam,
				 int num_stweams,
				 unsigned int *v_pos,
				 unsigned int *nom_v_pos);

#if defined(CONFIG_DWM_AMD_SECUWE_DISPWAY)
boow dc_stweam_fowwawd_cwc_window(stwuct dc_stweam_state *stweam,
		stwuct wect *wect,
		boow is_stop);
#endif

boow dc_stweam_configuwe_cwc(stwuct dc *dc,
			     stwuct dc_stweam_state *stweam,
			     stwuct cwc_pawams *cwc_window,
			     boow enabwe,
			     boow continuous);

boow dc_stweam_get_cwc(stwuct dc *dc,
		       stwuct dc_stweam_state *stweam,
		       uint32_t *w_cw,
		       uint32_t *g_y,
		       uint32_t *b_cb);

void dc_stweam_set_static_scween_pawams(stwuct dc *dc,
					stwuct dc_stweam_state **stweam,
					int num_stweams,
					const stwuct dc_static_scween_pawams *pawams);

void dc_stweam_set_dyn_expansion(stwuct dc *dc, stwuct dc_stweam_state *stweam,
		enum dc_dynamic_expansion option);

void dc_stweam_set_dithew_option(stwuct dc_stweam_state *stweam,
				 enum dc_dithew_option option);

boow dc_stweam_set_gamut_wemap(stwuct dc *dc,
			       const stwuct dc_stweam_state *stweam);

boow dc_stweam_pwogwam_csc_matwix(stwuct dc *dc,
				  stwuct dc_stweam_state *stweam);

boow dc_stweam_get_cwtc_position(stwuct dc *dc,
				 stwuct dc_stweam_state **stweam,
				 int num_stweams,
				 unsigned int *v_pos,
				 unsigned int *nom_v_pos);

stwuct pipe_ctx *dc_stweam_get_pipe_ctx(stwuct dc_stweam_state *stweam);

void dc_dmub_update_diwty_wect(stwuct dc *dc,
			       int suwface_count,
			       stwuct dc_stweam_state *stweam,
			       stwuct dc_suwface_update *swf_updates,
			       stwuct dc_state *context);
#endif /* DC_STWEAM_H_ */
