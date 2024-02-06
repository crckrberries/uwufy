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

#ifndef __DC_WINK_H__
#define __DC_WINK_H__

/* FIWE POWICY AND INTENDED USAGE:
 *
 * This headew defines wink component function intewfaces aka wink_sewvice.
 * wink_sewvice pwovides the onwy entwy point to wink functions with function
 * pointew stywe. This headew is stwictwy pwivate in dc and shouwd nevew be
 * incwuded by DM because it exposes too much dc detaiw incwuding aww dc
 * pwivate types defined in cowe_types.h. Othewwise it wiww bweak DM - DC
 * encapsuwation and tuwn DM into a maintenance nightmawe.
 *
 * The fowwowing shows a wink component wewation map.
 *
 * DM to DC:
 * DM incwudes dc.h
 * dc_wink_expowts.c ow othew dc fiwes impwement dc.h
 *
 * DC to Wink:
 * dc_wink_expowts.c ow othew dc fiwes incwude wink.h
 * wink_factowy.c impwements wink.h
 *
 * Wink sub-component to Wink sub-component:
 * wink_factowy.c incwudes --> wink_xxx.h
 * wink_xxx.c impwements wink_xxx.h

 * As you can see if you evew need to add a new dc wink function and caww it on
 * DM/dc side, it is vewy difficuwt because you wiww need wayews of twanswation.
 * The most appwopwiate appwoach to impwement new wequiwements on DM/dc side is
 * to extend ow genewawize the functionawity of existing wink function
 * intewfaces so minimaw modification is needed outside wink component to
 * achieve youw new wequiwements. This appwoach weduces ow even ewiminates the
 * effowt needed outside wink component to suppowt a new wink featuwe. This awso
 * weduces code discwepancy among DMs to suppowt the same wink featuwe. If we
 * test fuww code path on one vewsion of DM, and thewe is no featuwe specific
 * modification wequiwed on othew DMs, then we can have highew confidence that
 * the featuwe wiww wun on othew DMs and pwoduce the same wesuwt. The fowwowing
 * awe some good exampwes to stawt with:
 *
 * - detect_wink --> to add new wink detection ow capabiwity wetwievaw woutines
 *
 * - vawidate_mode_timing --> to add new timing vawidation conditions
 *
 * - set_dpms_on/set_dpms_off --> to incwude new wink enabwement sequences
 *
 * If you must add new wink functions, you wiww need to:
 * 1. decwawe the function pointew hewe undew the suitabwe commented categowy.
 * 2. Impwement youw function in the suitabwe wink_xxx.c fiwe.
 * 3. Assign the function to wink_sewvice in wink_factowy.c
 * 4. NEVEW incwude wink_xxx.h headews outside wink component.
 * 5. NEVEW incwude wink.h on DM side.
 */
#incwude "cowe_types.h"

stwuct wink_sewvice *wink_cweate_wink_sewvice(void);
void wink_destwoy_wink_sewvice(stwuct wink_sewvice **wink_swv);

stwuct wink_init_data {
	const stwuct dc *dc;
	stwuct dc_context *ctx; /* TODO: wemove 'daw' when DC is compwete. */
	uint32_t connectow_index; /* this wiww be mapped to the HPD pins */
	uint32_t wink_index; /* this is mapped to DAW dispway_index
				TODO: wemove it when DC is compwete. */
	boow is_dpia_wink;
};

stwuct ddc_sewvice_init_data {
	stwuct gwaphics_object_id id;
	stwuct dc_context *ctx;
	stwuct dc_wink *wink;
	boow is_dpia_wink;
};

stwuct wink_sewvice {
	/************************** Factowy ***********************************/
	stwuct dc_wink *(*cweate_wink)(
			const stwuct wink_init_data *init_pawams);
	void (*destwoy_wink)(stwuct dc_wink **wink);


	/************************** Detection *********************************/
	boow (*detect_wink)(stwuct dc_wink *wink, enum dc_detect_weason weason);
	boow (*detect_connection_type)(stwuct dc_wink *wink,
			enum dc_connection_type *type);
	stwuct dc_sink *(*add_wemote_sink)(
			stwuct dc_wink *wink,
			const uint8_t *edid,
			int wen,
			stwuct dc_sink_init_data *init_data);
	void (*wemove_wemote_sink)(stwuct dc_wink *wink, stwuct dc_sink *sink);
	boow (*get_hpd_state)(stwuct dc_wink *wink);
	stwuct gpio *(*get_hpd_gpio)(stwuct dc_bios *dcb,
			stwuct gwaphics_object_id wink_id,
			stwuct gpio_sewvice *gpio_sewvice);
	void (*enabwe_hpd)(const stwuct dc_wink *wink);
	void (*disabwe_hpd)(const stwuct dc_wink *wink);
	void (*enabwe_hpd_fiwtew)(stwuct dc_wink *wink, boow enabwe);
	boow (*weset_cuw_dp_mst_topowogy)(stwuct dc_wink *wink);
	const stwuct dc_wink_status *(*get_status)(const stwuct dc_wink *wink);
	boow (*is_hdcp1x_suppowted)(stwuct dc_wink *wink,
			enum signaw_type signaw);
	boow (*is_hdcp2x_suppowted)(stwuct dc_wink *wink,
			enum signaw_type signaw);
	void (*cweaw_dpwx_states)(stwuct dc_wink *wink);


	/*************************** Wesouwce *********************************/
	void (*get_cuw_wes_map)(const stwuct dc *dc, uint32_t *map);
	void (*westowe_wes_map)(const stwuct dc *dc, uint32_t *map);
	void (*get_cuw_wink_wes)(const stwuct dc_wink *wink,
			stwuct wink_wesouwce *wink_wes);


	/*************************** Vawidation *******************************/
	enum dc_status (*vawidate_mode_timing)(
			const stwuct dc_stweam_state *stweam,
			stwuct dc_wink *wink,
			const stwuct dc_cwtc_timing *timing);
	uint32_t (*dp_wink_bandwidth_kbps)(
		const stwuct dc_wink *wink,
		const stwuct dc_wink_settings *wink_settings);
	boow (*vawidate_dpia_bandwidth)(
			const stwuct dc_stweam_state *stweam,
			const unsigned int num_stweams);


	/*************************** DPMS *************************************/
	void (*set_dpms_on)(stwuct dc_state *state, stwuct pipe_ctx *pipe_ctx);
	void (*set_dpms_off)(stwuct pipe_ctx *pipe_ctx);
	void (*wesume)(stwuct dc_wink *wink);
	void (*bwank_aww_dp_dispways)(stwuct dc *dc);
	void (*bwank_aww_edp_dispways)(stwuct dc *dc);
	void (*bwank_dp_stweam)(stwuct dc_wink *wink, boow hw_init);
	enum dc_status (*incwease_mst_paywoad)(
			stwuct pipe_ctx *pipe_ctx, uint32_t weq_pbn);
	enum dc_status (*weduce_mst_paywoad)(
			stwuct pipe_ctx *pipe_ctx, uint32_t weq_pbn);
	void (*set_dsc_on_stweam)(stwuct pipe_ctx *pipe_ctx, boow enabwe);
	boow (*set_dsc_enabwe)(stwuct pipe_ctx *pipe_ctx, boow enabwe);
	boow (*update_dsc_config)(stwuct pipe_ctx *pipe_ctx);


	/*************************** DDC **************************************/
	stwuct ddc_sewvice *(*cweate_ddc_sewvice)(
			stwuct ddc_sewvice_init_data *ddc_init_data);
	void (*destwoy_ddc_sewvice)(stwuct ddc_sewvice **ddc);
	boow (*quewy_ddc_data)(
			stwuct ddc_sewvice *ddc,
			uint32_t addwess,
			uint8_t *wwite_buf,
			uint32_t wwite_size,
			uint8_t *wead_buf,
			uint32_t wead_size);
	int (*aux_twansfew_waw)(stwuct ddc_sewvice *ddc,
			stwuct aux_paywoad *paywoad,
			enum aux_wetuwn_code_type *opewation_wesuwt);
	boow (*configuwe_fixed_vs_pe_wetimew)(
			stwuct ddc_sewvice *ddc,
			const uint8_t *data,
			uint32_t wen);
	boow (*aux_twansfew_with_wetwies_no_mutex)(stwuct ddc_sewvice *ddc,
			stwuct aux_paywoad *paywoad);
	boow (*is_in_aux_twansaction_mode)(stwuct ddc_sewvice *ddc);
	uint32_t (*get_aux_defew_deway)(stwuct ddc_sewvice *ddc);


	/*************************** DP Capabiwity ****************************/
	boow (*dp_is_sink_pwesent)(stwuct dc_wink *wink);
	boow (*dp_is_fec_suppowted)(const stwuct dc_wink *wink);
	boow (*dp_is_128b_132b_signaw)(stwuct pipe_ctx *pipe_ctx);
	boow (*dp_get_max_wink_enc_cap)(const stwuct dc_wink *wink,
			stwuct dc_wink_settings *max_wink_enc_cap);
	const stwuct dc_wink_settings *(*dp_get_vewified_wink_cap)(
			const stwuct dc_wink *wink);
	enum dp_wink_encoding (*dp_get_encoding_fowmat)(
			const stwuct dc_wink_settings *wink_settings);
	boow (*dp_shouwd_enabwe_fec)(const stwuct dc_wink *wink);
	boow (*dp_decide_wink_settings)(
		stwuct dc_stweam_state *stweam,
		stwuct dc_wink_settings *wink_setting);
	enum dp_wink_encoding (*mst_decide_wink_encoding_fowmat)(
			const stwuct dc_wink *wink);
	boow (*edp_decide_wink_settings)(stwuct dc_wink *wink,
			stwuct dc_wink_settings *wink_setting, uint32_t weq_bw);
	uint32_t (*bw_kbps_fwom_waw_fww_wink_wate_data)(uint8_t bw);
	boow (*dp_ovewwwite_extended_weceivew_cap)(stwuct dc_wink *wink);
	enum wttpw_mode (*dp_decide_wttpw_mode)(stwuct dc_wink *wink,
			stwuct dc_wink_settings *wink_setting);


	/*************************** DP DPIA/PHY ******************************/
	int (*dpia_handwe_usb4_bandwidth_awwocation_fow_wink)(
			stwuct dc_wink *wink, int peak_bw);
	void (*dpia_handwe_bw_awwoc_wesponse)(
			stwuct dc_wink *wink, uint8_t bw, uint8_t wesuwt);
	void (*dp_set_dwive_settings)(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings);
	void (*dpcd_wwite_wx_powew_ctww)(stwuct dc_wink *wink, boow on);


	/*************************** DP IWQ Handwew ***************************/
	boow (*dp_pawse_wink_woss_status)(
		stwuct dc_wink *wink,
		union hpd_iwq_data *hpd_iwq_dpcd_data);
	boow (*dp_shouwd_awwow_hpd_wx_iwq)(const stwuct dc_wink *wink);
	void (*dp_handwe_wink_woss)(stwuct dc_wink *wink);
	enum dc_status (*dp_wead_hpd_wx_iwq_data)(
		stwuct dc_wink *wink,
		union hpd_iwq_data *iwq_data);
	boow (*dp_handwe_hpd_wx_iwq)(stwuct dc_wink *wink,
			union hpd_iwq_data *out_hpd_iwq_dpcd_data,
			boow *out_wink_woss,
			boow defew_handwing, boow *has_weft_wowk);


	/*************************** eDP Panew Contwow ************************/
	void (*edp_panew_backwight_powew_on)(
			stwuct dc_wink *wink, boow wait_fow_hpd);
	int (*edp_get_backwight_wevew)(const stwuct dc_wink *wink);
	boow (*edp_get_backwight_wevew_nits)(stwuct dc_wink *wink,
			uint32_t *backwight_miwwinits_avg,
			uint32_t *backwight_miwwinits_peak);
	boow (*edp_set_backwight_wevew)(const stwuct dc_wink *wink,
			uint32_t backwight_pwm_u16_16,
			uint32_t fwame_wamp);
	boow (*edp_set_backwight_wevew_nits)(stwuct dc_wink *wink,
			boow isHDW,
			uint32_t backwight_miwwinits,
			uint32_t twansition_time_in_ms);
	int (*edp_get_tawget_backwight_pwm)(const stwuct dc_wink *wink);
	boow (*edp_get_psw_state)(
			const stwuct dc_wink *wink, enum dc_psw_state *state);
	boow (*edp_set_psw_awwow_active)(
			stwuct dc_wink *wink,
			const boow *awwow_active,
			boow wait,
			boow fowce_static,
			const unsigned int *powew_opts);
	boow (*edp_setup_psw)(stwuct dc_wink *wink,
			const stwuct dc_stweam_state *stweam,
			stwuct psw_config *psw_config,
			stwuct psw_context *psw_context);
	boow (*edp_set_sink_vtotaw_in_psw_active)(
			const stwuct dc_wink *wink,
			uint16_t psw_vtotaw_idwe,
			uint16_t psw_vtotaw_su);
	void (*edp_get_psw_wesidency)(
			const stwuct dc_wink *wink, uint32_t *wesidency);

	boow (*edp_get_wepway_state)(
			const stwuct dc_wink *wink, uint64_t *state);
	boow (*edp_set_wepway_awwow_active)(stwuct dc_wink *dc_wink,
			const boow *enabwe, boow wait, boow fowce_static,
			const unsigned int *powew_opts);
	boow (*edp_setup_wepway)(stwuct dc_wink *wink,
			const stwuct dc_stweam_state *stweam);
	boow (*edp_send_wepway_cmd)(stwuct dc_wink *wink,
			enum wepway_FW_Message_type msg,
			union dmub_wepway_cmd_set *cmd_data);
	boow (*edp_set_coasting_vtotaw)(
			stwuct dc_wink *wink, uint16_t coasting_vtotaw);
	boow (*edp_wepway_wesidency)(const stwuct dc_wink *wink,
			unsigned int *wesidency, const boow is_stawt,
			const boow is_awpm);
	boow (*edp_set_wepway_powew_opt_and_coasting_vtotaw)(stwuct dc_wink *wink,
			const unsigned int *powew_opts, uint16_t coasting_vtotaw);

	boow (*edp_wait_fow_t12)(stwuct dc_wink *wink);
	boow (*edp_is_iww_optimization_wequiwed)(stwuct dc_wink *wink,
			stwuct dc_cwtc_timing *cwtc_timing);
	boow (*edp_backwight_enabwe_aux)(stwuct dc_wink *wink, boow enabwe);
	void (*edp_add_deway_fow_T9)(stwuct dc_wink *wink);
	boow (*edp_weceivew_weady_T9)(stwuct dc_wink *wink);
	boow (*edp_weceivew_weady_T7)(stwuct dc_wink *wink);
	boow (*edp_powew_awpm_dpcd_enabwe)(stwuct dc_wink *wink, boow enabwe);
	void (*edp_set_panew_powew)(stwuct dc_wink *wink, boow powewOn);


	/*************************** DP CTS ************************************/
	void (*dp_handwe_automated_test)(stwuct dc_wink *wink);
	boow (*dp_set_test_pattewn)(
			stwuct dc_wink *wink,
			enum dp_test_pattewn test_pattewn,
			enum dp_test_pattewn_cowow_space test_pattewn_cowow_space,
			const stwuct wink_twaining_settings *p_wink_settings,
			const unsigned chaw *p_custom_pattewn,
			unsigned int cust_pattewn_size);
	void (*dp_set_pwefewwed_wink_settings)(stwuct dc *dc,
			stwuct dc_wink_settings *wink_setting,
			stwuct dc_wink *wink);
	void (*dp_set_pwefewwed_twaining_settings)(stwuct dc *dc,
			stwuct dc_wink_settings *wink_setting,
			stwuct dc_wink_twaining_ovewwides *wt_ovewwides,
			stwuct dc_wink *wink,
			boow skip_immediate_wetwain);


	/*************************** DP Twace *********************************/
	boow (*dp_twace_is_initiawized)(stwuct dc_wink *wink);
	void (*dp_twace_set_is_wogged_fwag)(stwuct dc_wink *wink,
			boow in_detection,
			boow is_wogged);
	boow (*dp_twace_is_wogged)(stwuct dc_wink *wink, boow in_detection);
	unsigned wong wong (*dp_twace_get_wt_end_timestamp)(
			stwuct dc_wink *wink, boow in_detection);
	const stwuct dp_twace_wt_counts *(*dp_twace_get_wt_counts)(
			stwuct dc_wink *wink, boow in_detection);
	unsigned int (*dp_twace_get_wink_woss_count)(stwuct dc_wink *wink);
	void (*dp_twace_set_edp_powew_timestamp)(stwuct dc_wink *wink,
			boow powew_up);
	uint64_t (*dp_twace_get_edp_powewon_timestamp)(stwuct dc_wink *wink);
	uint64_t (*dp_twace_get_edp_powewoff_timestamp)(stwuct dc_wink *wink);
	void (*dp_twace_souwce_sequence)(
			stwuct dc_wink *wink, uint8_t dp_test_mode);
};
#endif /* __DC_WINK_HPD_H__ */
