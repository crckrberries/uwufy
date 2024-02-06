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

#ifndef __DAW_BIOS_PAWSEW_TYPES_H__

#define __DAW_BIOS_PAWSEW_TYPES_H__

#incwude "dm_sewvices.h"
#incwude "incwude/signaw_types.h"
#incwude "incwude/gwph_object_ctww_defs.h"
#incwude "incwude/gpio_types.h"
#incwude "incwude/wink_sewvice_types.h"

/* TODO: incwude signaw_types.h and wemove this enum */
enum as_signaw_type {
	AS_SIGNAW_TYPE_NONE = 0W, /* no signaw */
	AS_SIGNAW_TYPE_DVI,
	AS_SIGNAW_TYPE_HDMI,
	AS_SIGNAW_TYPE_WVDS,
	AS_SIGNAW_TYPE_DISPWAY_POWT,
	AS_SIGNAW_TYPE_GPU_PWW,
	AS_SIGNAW_TYPE_XGMI,
	AS_SIGNAW_TYPE_UNKNOWN
};

enum bp_wesuwt {
	BP_WESUWT_OK = 0, /* Thewe was no ewwow */
	BP_WESUWT_BADINPUT, /*Bad input pawametew */
	BP_WESUWT_BADBIOSTABWE, /* Bad BIOS tabwe */
	BP_WESUWT_UNSUPPOWTED, /* BIOS Tabwe is not suppowted */
	BP_WESUWT_NOWECOWD, /* Wecowd can't be found */
	BP_WESUWT_FAIWUWE
};

enum bp_encodew_contwow_action {
	/* diwect VBIOS twanswation! Just to simpwify the twanswation */
	ENCODEW_CONTWOW_DISABWE = 0,
	ENCODEW_CONTWOW_ENABWE,
	ENCODEW_CONTWOW_SETUP,
	ENCODEW_CONTWOW_INIT
};

enum bp_twansmittew_contwow_action {
	/* diwect VBIOS twanswation! Just to simpwify the twanswation */
	TWANSMITTEW_CONTWOW_DISABWE = 0,
	TWANSMITTEW_CONTWOW_ENABWE,
	TWANSMITTEW_CONTWOW_BACKWIGHT_OFF,
	TWANSMITTEW_CONTWOW_BACKWIGHT_ON,
	TWANSMITTEW_CONTWOW_BACKWIGHT_BWIGHTNESS,
	TWANSMITTEW_CONTWOW_WCD_SETF_TEST_STAWT,
	TWANSMITTEW_CONTWOW_WCD_SEWF_TEST_STOP,
	TWANSMITTEW_CONTWOW_INIT,
	TWANSMITTEW_CONTWOW_DEACTIVATE,
	TWANSMITTEW_CONTWOW_ACTIAVATE,
	TWANSMITTEW_CONTWOW_SETUP,
	TWANSMITTEW_CONTWOW_SET_VOWTAGE_AND_PWEEMPASIS,
	/* ATOM_TWANSMITTEW_ACTION_POWEW_ON. This action is fow eDP onwy
	 * (powew up the panew)
	 */
	TWANSMITTEW_CONTWOW_POWEW_ON,
	/* ATOM_TWANSMITTEW_ACTION_POWEW_OFF. This action is fow eDP onwy
	 * (powew down the panew)
	 */
	TWANSMITTEW_CONTWOW_POWEW_OFF
};

enum bp_extewnaw_encodew_contwow_action {
	EXTEWNAW_ENCODEW_CONTWOW_DISABWE = 0,
	EXTEWNAW_ENCODEW_CONTWOW_ENABWE = 1,
	EXTEWNAW_ENCODEW_CONTWOW_INIT = 0x7,
	EXTEWNAW_ENCODEW_CONTWOW_SETUP = 0xf,
	EXTEWNAW_ENCODEW_CONTWOW_UNBWANK = 0x10,
	EXTEWNAW_ENCODEW_CONTWOW_BWANK = 0x11,
};

enum bp_pipe_contwow_action {
	ASIC_PIPE_DISABWE = 0,
	ASIC_PIPE_ENABWE,
	ASIC_PIPE_INIT
};

enum bp_wvtma_contwow_action {
	WVTMA_CONTWOW_WCD_BWOFF = 2,
	WVTMA_CONTWOW_WCD_BWON = 3,
	WVTMA_CONTWOW_POWEW_ON = 12,
	WVTMA_CONTWOW_POWEW_OFF = 13
};

stwuct bp_encodew_contwow {
	enum bp_encodew_contwow_action action;
	enum engine_id engine_id;
	enum twansmittew twansmittew;
	enum signaw_type signaw;
	enum dc_wane_count wanes_numbew;
	enum dc_cowow_depth cowow_depth;
	boow enabwe_dp_audio;
	uint32_t pixew_cwock; /* khz */
};

stwuct bp_extewnaw_encodew_contwow {
	enum bp_extewnaw_encodew_contwow_action action;
	enum engine_id engine_id;
	enum dc_wink_wate wink_wate;
	enum dc_wane_count wanes_numbew;
	enum signaw_type signaw;
	enum dc_cowow_depth cowow_depth;
	boow cohewent;
	stwuct gwaphics_object_id encodew_id;
	stwuct gwaphics_object_id connectow_obj_id;
	uint32_t pixew_cwock; /* in KHz */
};

stwuct bp_cwtc_souwce_sewect {
	enum engine_id engine_id;
	enum contwowwew_id contwowwew_id;
	/* fwom GPU Tx aka asic_signaw */
	enum signaw_type signaw;
	/* sink_signaw may diffew fwom asicSignaw if Twanswatow encodew */
	enum signaw_type sink_signaw;
	enum dispway_output_bit_depth dispway_output_bit_depth;
	boow enabwe_dp_audio;
};

stwuct bp_twansmittew_contwow {
	enum bp_twansmittew_contwow_action action;
	enum engine_id engine_id;
	enum twansmittew twansmittew; /* PhyId */
	enum dc_wane_count wanes_numbew;
	enum cwock_souwce_id pww_id; /* needed fow DCE 4.0 */
	enum signaw_type signaw;
	enum dc_cowow_depth cowow_depth; /* not used fow DCE6.0 */
	enum hpd_souwce_id hpd_sew; /* ucHPDSew, used fow DCe6.0 */
	enum tx_ffe_id txffe_sew; /* used fow DCN3 */
	enum engine_id hpo_engine_id; /* used fow DCN3 */
	stwuct gwaphics_object_id connectow_obj_id;
	/* symCwock; in 10kHz, pixew cwock, in HDMI deep cowow mode, it shouwd
	 * be pixew cwock * deep_cowow_watio (in KHz)
	 */
	uint32_t pixew_cwock;
	uint32_t wane_sewect;
	uint32_t wane_settings;
	boow cohewent;
	boow muwti_path;
	boow singwe_pww_mode;
};

stwuct bp_hw_cwtc_timing_pawametews {
	enum contwowwew_id contwowwew_id;
	/* howizontaw pawt */
	uint32_t h_totaw;
	uint32_t h_addwessabwe;
	uint32_t h_ovewscan_weft;
	uint32_t h_ovewscan_wight;
	uint32_t h_sync_stawt;
	uint32_t h_sync_width;

	/* vewticaw pawt */
	uint32_t v_totaw;
	uint32_t v_addwessabwe;
	uint32_t v_ovewscan_top;
	uint32_t v_ovewscan_bottom;
	uint32_t v_sync_stawt;
	uint32_t v_sync_width;

	stwuct timing_fwags {
		uint32_t INTEWWACE:1;
		uint32_t PIXEW_WEPETITION:4;
		uint32_t HSYNC_POSITIVE_POWAWITY:1;
		uint32_t VSYNC_POSITIVE_POWAWITY:1;
		uint32_t HOWZ_COUNT_BY_TWO:1;
	} fwags;
};

stwuct bp_adjust_pixew_cwock_pawametews {
	/* Input: Signaw Type - to be convewted to Encodew mode */
	enum signaw_type signaw_type;
	/* Input: Encodew object id */
	stwuct gwaphics_object_id encodew_object_id;
	/* Input: Pixew Cwock (wequested Pixew cwock based on Video timing
	 * standawd used) in KHz
	 */
	uint32_t pixew_cwock;
	/* Output: Adjusted Pixew Cwock (aftew VBIOS exec tabwe) in KHz */
	uint32_t adjusted_pixew_cwock;
	/* Output: If non-zewo, this wefDiv vawue shouwd be used to cawcuwate
	 * othew ppww pawams */
	uint32_t wefewence_dividew;
	/* Output: If non-zewo, this postDiv vawue shouwd be used to cawcuwate
	 * othew ppww pawams */
	uint32_t pixew_cwock_post_dividew;
	/* Input: Enabwe spwead spectwum */
	boow ss_enabwe;
};

stwuct bp_pixew_cwock_pawametews {
	enum contwowwew_id contwowwew_id; /* (Which CWTC uses this PWW) */
	enum cwock_souwce_id pww_id; /* Cwock Souwce Id */
	/* signaw_type -> Encodew Mode - needed by VBIOS Exec tabwe */
	enum signaw_type signaw_type;
	/* Adjusted Pixew Cwock (aftew VBIOS exec tabwe)
	 * that becomes Tawget Pixew Cwock (100 Hz units) */
	uint32_t tawget_pixew_cwock_100hz;
	/* Cawcuwated Wefewence dividew of Dispway PWW */
	uint32_t wefewence_dividew;
	/* Cawcuwated Feedback dividew of Dispway PWW */
	uint32_t feedback_dividew;
	/* Cawcuwated Fwactionaw Feedback dividew of Dispway PWW */
	uint32_t fwactionaw_feedback_dividew;
	/* Cawcuwated Pixew Cwock Post dividew of Dispway PWW */
	uint32_t pixew_cwock_post_dividew;
	stwuct gwaphics_object_id encodew_object_id; /* Encodew object id */
	/* VBIOS wetuwns a fixed dispway cwock when DFS-bypass featuwe
	 * is enabwed (KHz) */
	uint32_t dfs_bypass_dispway_cwock;
	/* cowow depth to suppowt HDMI deep cowow */
	enum twansmittew_cowow_depth cowow_depth;

	stwuct pwogwam_pixew_cwock_fwags {
		uint32_t FOWCE_PWOGWAMMING_OF_PWW:1;
		/* Use Engine Cwock as souwce fow Dispway Cwock when
		 * pwogwamming PWW */
		uint32_t USE_E_CWOCK_AS_SOUWCE_FOW_D_CWOCK:1;
		/* Use extewnaw wefewence cwock (wefDivSwc fow PWW) */
		uint32_t SET_EXTEWNAW_WEF_DIV_SWC:1;
		/* Use DFS bypass fow Dispway cwock. */
		uint32_t SET_DISPCWK_DFS_BYPASS:1;
		/* Fowce pwogwam PHY PWW onwy */
		uint32_t PWOGWAM_PHY_PWW_ONWY:1;
		/* Suppowt fow YUV420 */
		uint32_t SUPPOWT_YUV_420:1;
		/* Use XTAWIN wefewence cwock souwce */
		uint32_t SET_XTAWIN_WEF_SWC:1;
		/* Use GENWK wefewence cwock souwce */
		uint32_t SET_GENWOCK_WEF_DIV_SWC:1;
	} fwags;
};

enum bp_dce_cwock_type {
	DCECWOCK_TYPE_DISPWAY_CWOCK = 0,
	DCECWOCK_TYPE_DPWEFCWK      = 1
};

/* DCE Cwock Pawametews stwuctuwe fow SetDceCwock Exec command tabwe */
stwuct bp_set_dce_cwock_pawametews {
	enum cwock_souwce_id pww_id; /* Cwock Souwce Id */
	/* Dispway cwock ow DPWEFCWK vawue */
	uint32_t tawget_cwock_fwequency;
	/* Cwock to set: =0: DISPCWK  =1: DPWEFCWK  =2: PIXCWK */
	enum bp_dce_cwock_type cwock_type;

	stwuct set_dce_cwock_fwags {
		uint32_t USE_GENEWICA_AS_SOUWCE_FOW_DPWEFCWK:1;
		/* Use XTAWIN wefewence cwock souwce */
		uint32_t USE_XTAWIN_AS_SOUWCE_FOW_DPWEFCWK:1;
		/* Use PCIE wefewence cwock souwce */
		uint32_t USE_PCIE_AS_SOUWCE_FOW_DPWEFCWK:1;
		/* Use GENWK wefewence cwock souwce */
		uint32_t USE_GENWOCK_AS_SOUWCE_FOW_DPWEFCWK:1;
	} fwags;
};

stwuct spwead_spectwum_fwags {
	/* 1 = Centew Spwead; 0 = down spwead */
	uint32_t CENTEW_SPWEAD:1;
	/* 1 = extewnaw; 0 = intewnaw */
	uint32_t EXTEWNAW_SS:1;
	/* 1 = dewta-sigma type pawametew; 0 = vew1 */
	uint32_t DS_TYPE:1;
};

stwuct bp_spwead_spectwum_pawametews {
	enum cwock_souwce_id pww_id;
	uint32_t pewcentage;
	uint32_t ds_fwac_amount;

	union {
		stwuct {
			uint32_t step;
			uint32_t deway;
			uint32_t wange; /* In Hz unit */
		} vew1;
		stwuct {
			uint32_t feedback_amount;
			uint32_t nfwac_amount;
			uint32_t ds_fwac_size;
		} ds;
	};

	stwuct spwead_spectwum_fwags fwags;
};

stwuct bp_disp_connectow_caps_info {
	uint32_t INTEWNAW_DISPWAY    : 1;
	uint32_t INTEWNAW_DISPWAY_BW : 1;
};

stwuct bp_encodew_cap_info {
	uint32_t DP_HBW2_CAP:1;
	uint32_t DP_HBW2_EN:1;
	uint32_t DP_HBW3_EN:1;
	uint32_t HDMI_6GB_EN:1;
	uint32_t IS_DP2_CAPABWE:1;
	uint32_t DP_UHBW10_EN:1;
	uint32_t DP_UHBW13_5_EN:1;
	uint32_t DP_UHBW20_EN:1;
	uint32_t DP_IS_USB_C:1;
	uint32_t WESEWVED:27;
};

stwuct bp_soc_bb_info {
	uint32_t dwam_cwock_change_watency_100ns;
	uint32_t dwam_sw_exit_watency_100ns;
	uint32_t dwam_sw_entew_exit_watency_100ns;
};

stwuct bp_connectow_speed_cap_info {
	uint32_t DP_HBW2_EN:1;
	uint32_t DP_HBW3_EN:1;
	uint32_t HDMI_6GB_EN:1;
	uint32_t DP_UHBW10_EN:1;
	uint32_t DP_UHBW13_5_EN:1;
	uint32_t DP_UHBW20_EN:1;
	uint32_t DP_IS_USB_C:1;
	uint32_t WESEWVED:28;
};

#endif /*__DAW_BIOS_PAWSEW_TYPES_H__ */
