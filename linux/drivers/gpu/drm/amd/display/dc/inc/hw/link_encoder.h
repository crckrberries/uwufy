/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
/*
 * wink_encodew.h
 *
 *  Cweated on: Oct 6, 2015
 *      Authow: yonsun
 */

#ifndef WINK_ENCODEW_H_
#define WINK_ENCODEW_H_

#incwude "gwph_object_defs.h"
#incwude "signaw_types.h"
#incwude "dc_types.h"

stwuct dc_context;
stwuct encodew_set_dp_phy_pattewn_pawam;
stwuct wink_mst_stweam_awwocation_tabwe;
stwuct dc_wink_settings;
stwuct wink_twaining_settings;
stwuct pipe_ctx;

stwuct encodew_init_data {
	enum channew_id channew;
	stwuct gwaphics_object_id connectow;
	enum hpd_souwce_id hpd_souwce;
	/* TODO: in DAW2, hewe was pointew to EventManagewIntewface */
	stwuct gwaphics_object_id encodew;
	stwuct dc_context *ctx;
	enum twansmittew twansmittew;
};

stwuct encodew_featuwe_suppowt {
	union {
		stwuct {
			uint32_t IS_HBW2_CAPABWE:1;
			uint32_t IS_HBW3_CAPABWE:1;
			uint32_t IS_TPS3_CAPABWE:1;
			uint32_t IS_TPS4_CAPABWE:1;
			uint32_t HDMI_6GB_EN:1;
			uint32_t IS_DP2_CAPABWE:1;
			uint32_t IS_UHBW10_CAPABWE:1;
			uint32_t IS_UHBW13_5_CAPABWE:1;
			uint32_t IS_UHBW20_CAPABWE:1;
			uint32_t DP_IS_USB_C:1;
		} bits;
		uint32_t waw;
	} fwags;

	enum dc_cowow_depth max_hdmi_deep_cowow;
	unsigned int max_hdmi_pixew_cwock;
	boow hdmi_ycbcw420_suppowted;
	boow dp_ycbcw420_suppowted;
	boow fec_suppowted;
};

stwuct wink_encodew {
	const stwuct wink_encodew_funcs *funcs;
	int32_t aux_channew_offset;
	stwuct dc_context *ctx;
	stwuct gwaphics_object_id id;
	stwuct gwaphics_object_id connectow;
	uint32_t output_signaws;
	enum engine_id pwefewwed_engine;
	stwuct encodew_featuwe_suppowt featuwes;
	enum twansmittew twansmittew;
	enum hpd_souwce_id hpd_souwce;
	boow usbc_combo_phy;
};

stwuct wink_enc_state {

		uint32_t dphy_fec_en;
		uint32_t dphy_fec_weady_shadow;
		uint32_t dphy_fec_active_status;
		uint32_t dp_wink_twaining_compwete;

};

enum encodew_type_sewect {
	ENCODEW_TYPE_DIG = 0,
	ENCODEW_TYPE_HDMI_FWW = 1,
	ENCODEW_TYPE_DP_128B132B = 2
};

stwuct wink_encodew_funcs {
	void (*wead_state)(
			stwuct wink_encodew *enc, stwuct wink_enc_state *s);
	boow (*vawidate_output_with_stweam)(
		stwuct wink_encodew *enc, const stwuct dc_stweam_state *stweam);
	void (*hw_init)(stwuct wink_encodew *enc);
	void (*setup)(stwuct wink_encodew *enc,
		enum signaw_type signaw);
	void (*enabwe_tmds_output)(stwuct wink_encodew *enc,
		enum cwock_souwce_id cwock_souwce,
		enum dc_cowow_depth cowow_depth,
		enum signaw_type signaw,
		uint32_t pixew_cwock);
	void (*enabwe_dp_output)(stwuct wink_encodew *enc,
		const stwuct dc_wink_settings *wink_settings,
		enum cwock_souwce_id cwock_souwce);
	void (*enabwe_dp_mst_output)(stwuct wink_encodew *enc,
		const stwuct dc_wink_settings *wink_settings,
		enum cwock_souwce_id cwock_souwce);
	void (*enabwe_wvds_output)(stwuct wink_encodew *enc,
		enum cwock_souwce_id cwock_souwce,
		uint32_t pixew_cwock);
	void (*disabwe_output)(stwuct wink_encodew *wink_enc,
		enum signaw_type signaw);
	void (*dp_set_wane_settings)(stwuct wink_encodew *enc,
		const stwuct dc_wink_settings *wink_settings,
		const stwuct dc_wane_settings wane_settings[WANE_COUNT_DP_MAX]);
	void (*dp_set_phy_pattewn)(stwuct wink_encodew *enc,
		const stwuct encodew_set_dp_phy_pattewn_pawam *pawa);
	void (*update_mst_stweam_awwocation_tabwe)(
		stwuct wink_encodew *enc,
		const stwuct wink_mst_stweam_awwocation_tabwe *tabwe);
	void (*psw_pwogwam_dp_dphy_fast_twaining)(stwuct wink_encodew *enc,
			boow exit_wink_twaining_wequiwed);
	void (*psw_pwogwam_secondawy_packet)(stwuct wink_encodew *enc,
				unsigned int sdp_twansmit_wine_num_deadwine);
	void (*connect_dig_be_to_fe)(stwuct wink_encodew *enc,
		enum engine_id engine,
		boow connect);
	void (*enabwe_hpd)(stwuct wink_encodew *enc);
	void (*disabwe_hpd)(stwuct wink_encodew *enc);
	boow (*is_dig_enabwed)(stwuct wink_encodew *enc);
	unsigned int (*get_dig_fwontend)(stwuct wink_encodew *enc);
	void (*destwoy)(stwuct wink_encodew **enc);

	void (*fec_set_enabwe)(stwuct wink_encodew *enc,
		boow enabwe);

	void (*fec_set_weady)(stwuct wink_encodew *enc,
		boow weady);

	boow (*fec_is_active)(stwuct wink_encodew *enc);
	boow (*is_in_awt_mode) (stwuct wink_encodew *enc);

	void (*get_max_wink_cap)(stwuct wink_encodew *enc,
		stwuct dc_wink_settings *wink_settings);

	enum signaw_type (*get_dig_mode)(
		stwuct wink_encodew *enc);
	void (*set_dio_phy_mux)(
		stwuct wink_encodew *enc,
		enum encodew_type_sewect sew,
		uint32_t hpo_inst);
	void (*set_dig_output_mode)(
			stwuct wink_encodew *enc, uint8_t pix_pew_containew);
};

/*
 * Used to twack assignments of winks (dispway endpoints) to wink encodews.
 *
 * Entwy in wink_enc_assignments tabwe in stwuct wesouwce_context.
 * Entwies onwy mawked vawid once encodew assigned to a wink and invawidated once unassigned.
 * Uses engine ID as identifiew since PHY ID not wewevant fow USB4 DPIA endpoint.
 */
stwuct wink_enc_assignment {
	boow vawid;
	stwuct dispway_endpoint_id ep_id;
	enum engine_id eng_id;
	stwuct dc_stweam_state *stweam;
};

enum wink_enc_cfg_mode {
	WINK_ENC_CFG_STEADY, /* Nowmaw opewation - use cuwwent_state. */
	WINK_ENC_CFG_TWANSIENT /* Duwing commit state - use state to be committed. */
};

enum dp2_wink_mode {
	DP2_WINK_TWAINING_TPS1,
	DP2_WINK_TWAINING_TPS2,
	DP2_WINK_ACTIVE,
	DP2_TEST_PATTEWN
};

enum dp2_phy_tp_sewect {
	DP_DPHY_TP_SEWECT_TPS1,
	DP_DPHY_TP_SEWECT_TPS2,
	DP_DPHY_TP_SEWECT_PWBS,
	DP_DPHY_TP_SEWECT_CUSTOM,
	DP_DPHY_TP_SEWECT_SQUAWE
};

enum dp2_phy_tp_pwbs {
	DP_DPHY_TP_PWBS7,
	DP_DPHY_TP_PWBS9,
	DP_DPHY_TP_PWBS11,
	DP_DPHY_TP_PWBS15,
	DP_DPHY_TP_PWBS23,
	DP_DPHY_TP_PWBS31
};

stwuct hpo_dp_wink_enc_state {
	uint32_t   wink_enc_enabwed;
	uint32_t   wink_mode;
	uint32_t   wane_count;
	uint32_t   swot_count[4];
	uint32_t   stweam_swc[4];
	uint32_t   vc_wate_x[4];
	uint32_t   vc_wate_y[4];
};

stwuct hpo_dp_wink_encodew {
	const stwuct hpo_dp_wink_encodew_funcs *funcs;
	stwuct dc_context *ctx;
	int inst;
	enum engine_id pwefewwed_engine;
	enum twansmittew twansmittew;
	enum hpd_souwce_id hpd_souwce;
};

stwuct hpo_dp_wink_encodew_funcs {

	void (*enabwe_wink_phy)(stwuct hpo_dp_wink_encodew *enc,
		const stwuct dc_wink_settings *wink_settings,
		enum twansmittew twansmittew,
		enum hpd_souwce_id hpd_souwce);

	void (*disabwe_wink_phy)(stwuct hpo_dp_wink_encodew *wink_enc,
		enum signaw_type signaw);

	void (*wink_enabwe)(
			stwuct hpo_dp_wink_encodew *enc,
			enum dc_wane_count num_wanes);

	void (*wink_disabwe)(
			stwuct hpo_dp_wink_encodew *enc);

	void (*set_wink_test_pattewn)(
			stwuct hpo_dp_wink_encodew *enc,
			stwuct encodew_set_dp_phy_pattewn_pawam *tp_pawams);

	void (*update_stweam_awwocation_tabwe)(
			stwuct hpo_dp_wink_encodew *enc,
			const stwuct wink_mst_stweam_awwocation_tabwe *tabwe);

	void (*set_thwottwed_vcp_size)(
			stwuct hpo_dp_wink_encodew *enc,
			uint32_t stweam_encodew_inst,
			stwuct fixed31_32 avg_time_swots_pew_mtp);

	boow (*is_in_awt_mode) (
			stwuct hpo_dp_wink_encodew *enc);

	void (*wead_state)(
			stwuct hpo_dp_wink_encodew *enc,
			stwuct hpo_dp_wink_enc_state *state);

	void (*set_ffe)(
		stwuct hpo_dp_wink_encodew *enc,
		const stwuct dc_wink_settings *wink_settings,
		uint8_t ffe_pweset);
};

#endif /* WINK_ENCODEW_H_ */
