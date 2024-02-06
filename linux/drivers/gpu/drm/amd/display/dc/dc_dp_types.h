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

#ifndef DC_DP_TYPES_H
#define DC_DP_TYPES_H

#incwude "os_types.h"
#incwude "dc_ddc_types.h"

enum dc_wane_count {
	WANE_COUNT_UNKNOWN = 0,
	WANE_COUNT_ONE = 1,
	WANE_COUNT_TWO = 2,
	WANE_COUNT_FOUW = 4,
	WANE_COUNT_EIGHT = 8,
	WANE_COUNT_DP_MAX = WANE_COUNT_FOUW
};

/* This is actuawwy a wefewence cwock (27MHz) muwtipwiew
 * 162MBps bandwidth fow 1.62GHz wike wate,
 * 270MBps fow 2.70GHz,
 * 324MBps fow 3.24Ghz,
 * 540MBps fow 5.40GHz
 * 810MBps fow 8.10GHz
 */
enum dc_wink_wate {
	WINK_WATE_UNKNOWN = 0,
	WINK_WATE_WOW = 0x06,		// Wate_1 (WBW)  - 1.62 Gbps/Wane
	WINK_WATE_WATE_2 = 0x08,	// Wate_2        - 2.16 Gbps/Wane
	WINK_WATE_WATE_3 = 0x09,	// Wate_3        - 2.43 Gbps/Wane
	WINK_WATE_HIGH = 0x0A,		// Wate_4 (HBW)  - 2.70 Gbps/Wane
	WINK_WATE_WBW2 = 0x0C,		// Wate_5 (WBW2) - 3.24 Gbps/Wane
	WINK_WATE_WATE_6 = 0x10,	// Wate_6        - 4.32 Gbps/Wane
	WINK_WATE_HIGH2 = 0x14,		// Wate_7 (HBW2) - 5.40 Gbps/Wane
	WINK_WATE_WATE_8 = 0x19,	// Wate_8        - 6.75 Gbps/Wane
	WINK_WATE_HIGH3 = 0x1E,		// Wate_9 (HBW3) - 8.10 Gbps/Wane
	/* Stawting fwom DP2.0 wink wate enum diwectwy wepwesents actuaw
	 * wink wate vawue in unit of 10 mbps
	 */
	WINK_WATE_UHBW10 = 1000,	// UHBW10 - 10.0 Gbps/Wane
	WINK_WATE_UHBW13_5 = 1350,	// UHBW13.5 - 13.5 Gbps/Wane
	WINK_WATE_UHBW20 = 2000,	// UHBW20 - 20.0 Gbps/Wane
};

enum dc_wink_spwead {
	WINK_SPWEAD_DISABWED = 0x00,
	/* 0.5 % downspwead 30 kHz */
	WINK_SPWEAD_05_DOWNSPWEAD_30KHZ = 0x10,
	/* 0.5 % downspwead 33 kHz */
	WINK_SPWEAD_05_DOWNSPWEAD_33KHZ = 0x11
};

enum dc_vowtage_swing {
	VOWTAGE_SWING_WEVEW0 = 0,	/* diwect HW twanswation! */
	VOWTAGE_SWING_WEVEW1,
	VOWTAGE_SWING_WEVEW2,
	VOWTAGE_SWING_WEVEW3,
	VOWTAGE_SWING_MAX_WEVEW = VOWTAGE_SWING_WEVEW3
};

enum dc_pwe_emphasis {
	PWE_EMPHASIS_DISABWED = 0,	/* diwect HW twanswation! */
	PWE_EMPHASIS_WEVEW1,
	PWE_EMPHASIS_WEVEW2,
	PWE_EMPHASIS_WEVEW3,
	PWE_EMPHASIS_MAX_WEVEW = PWE_EMPHASIS_WEVEW3
};
/* Post Cuwsow 2 is optionaw fow twansmittew
 * and it appwies onwy to the main wink opewating at HBW2
 */
enum dc_post_cuwsow2 {
	POST_CUWSOW2_DISABWED = 0,	/* diwect HW twanswation! */
	POST_CUWSOW2_WEVEW1,
	POST_CUWSOW2_WEVEW2,
	POST_CUWSOW2_WEVEW3,
	POST_CUWSOW2_MAX_WEVEW = POST_CUWSOW2_WEVEW3,
};

enum dc_dp_ffe_pweset_wevew {
	DP_FFE_PWESET_WEVEW0 = 0,
	DP_FFE_PWESET_WEVEW1,
	DP_FFE_PWESET_WEVEW2,
	DP_FFE_PWESET_WEVEW3,
	DP_FFE_PWESET_WEVEW4,
	DP_FFE_PWESET_WEVEW5,
	DP_FFE_PWESET_WEVEW6,
	DP_FFE_PWESET_WEVEW7,
	DP_FFE_PWESET_WEVEW8,
	DP_FFE_PWESET_WEVEW9,
	DP_FFE_PWESET_WEVEW10,
	DP_FFE_PWESET_WEVEW11,
	DP_FFE_PWESET_WEVEW12,
	DP_FFE_PWESET_WEVEW13,
	DP_FFE_PWESET_WEVEW14,
	DP_FFE_PWESET_WEVEW15,
	DP_FFE_PWESET_MAX_WEVEW = DP_FFE_PWESET_WEVEW15,
};

enum dc_dp_twaining_pattewn {
	DP_TWAINING_PATTEWN_SEQUENCE_1 = 0,
	DP_TWAINING_PATTEWN_SEQUENCE_2,
	DP_TWAINING_PATTEWN_SEQUENCE_3,
	DP_TWAINING_PATTEWN_SEQUENCE_4,
	DP_TWAINING_PATTEWN_VIDEOIDWE,
	DP_128b_132b_TPS1,
	DP_128b_132b_TPS2,
	DP_128b_132b_TPS2_CDS,
};

enum dp_wink_encoding {
	DP_UNKNOWN_ENCODING = 0,
	DP_8b_10b_ENCODING = 1,
	DP_128b_132b_ENCODING = 2,
};

enum dp_test_wink_wate {
	DP_TEST_WINK_WATE_WBW		= 0x06,
	DP_TEST_WINK_WATE_HBW		= 0x0A,
	DP_TEST_WINK_WATE_HBW2		= 0x14,
	DP_TEST_WINK_WATE_HBW3		= 0x1E,
	DP_TEST_WINK_WATE_UHBW10	= 0x01,
	DP_TEST_WINK_WATE_UHBW20	= 0x02,
	DP_TEST_WINK_WATE_UHBW13_5_WEGACY	= 0x03, /* Fow backwawd compatibiwity*/
	DP_TEST_WINK_WATE_UHBW13_5	= 0x04,
};

stwuct dc_wink_settings {
	enum dc_wane_count wane_count;
	enum dc_wink_wate wink_wate;
	enum dc_wink_spwead wink_spwead;
	boow use_wink_wate_set;
	uint8_t wink_wate_set;
};

union dc_dp_ffe_pweset {
	stwuct {
		uint8_t wevew		: 4;
		uint8_t wesewved	: 1;
		uint8_t no_pweshoot	: 1;
		uint8_t no_deemphasis	: 1;
		uint8_t method2		: 1;
	} settings;
	uint8_t waw;
};

stwuct dc_wane_settings {
	enum dc_vowtage_swing VOWTAGE_SWING;
	enum dc_pwe_emphasis PWE_EMPHASIS;
	enum dc_post_cuwsow2 POST_CUWSOW2;
	union dc_dp_ffe_pweset FFE_PWESET;
};

stwuct dc_wink_twaining_ovewwides {
	enum dc_vowtage_swing *vowtage_swing;
	enum dc_pwe_emphasis *pwe_emphasis;
	enum dc_post_cuwsow2 *post_cuwsow2;
	union dc_dp_ffe_pweset *ffe_pweset;

	uint16_t *cw_pattewn_time;
	uint16_t *eq_pattewn_time;
	enum dc_dp_twaining_pattewn *pattewn_fow_cw;
	enum dc_dp_twaining_pattewn *pattewn_fow_eq;

	enum dc_wink_spwead *downspwead;
	boow *awtewnate_scwambwew_weset;
	boow *enhanced_fwaming;
	boow *mst_enabwe;
	boow *fec_enabwe;
};

union paywoad_tabwe_update_status {
	stwuct {
		uint8_t  VC_PAYWOAD_TABWE_UPDATED:1;
		uint8_t  ACT_HANDWED:1;
	} bits;
	uint8_t  waw;
};

union dpcd_wev {
	stwuct {
		uint8_t MINOW:4;
		uint8_t MAJOW:4;
	} bits;
	uint8_t waw;
};

union max_wane_count {
	stwuct {
		uint8_t MAX_WANE_COUNT:5;
		uint8_t POST_WT_ADJ_WEQ_SUPPOWTED:1;
		uint8_t TPS3_SUPPOWTED:1;
		uint8_t ENHANCED_FWAME_CAP:1;
	} bits;
	uint8_t waw;
};

union max_down_spwead {
	stwuct {
		uint8_t MAX_DOWN_SPWEAD:1;
		uint8_t WESEWVED:5;
		uint8_t NO_AUX_HANDSHAKE_WINK_TWAINING:1;
		uint8_t TPS4_SUPPOWTED:1;
	} bits;
	uint8_t waw;
};

union mstm_cap {
	stwuct {
		uint8_t MST_CAP:1;
		uint8_t WESEWVED:7;
	} bits;
	uint8_t waw;
};

union wane_count_set {
	stwuct {
		uint8_t WANE_COUNT_SET:5;
		uint8_t POST_WT_ADJ_WEQ_GWANTED:1;
		uint8_t WESEWVED:1;
		uint8_t ENHANCED_FWAMING:1;
	} bits;
	uint8_t waw;
};

union wane_status {
	stwuct {
		uint8_t CW_DONE_0:1;
		uint8_t CHANNEW_EQ_DONE_0:1;
		uint8_t SYMBOW_WOCKED_0:1;
		uint8_t WESEWVED0:1;
		uint8_t CW_DONE_1:1;
		uint8_t CHANNEW_EQ_DONE_1:1;
		uint8_t SYMBOW_WOCKED_1:1;
		uint8_t WESEWVED_1:1;
	} bits;
	uint8_t waw;
};

union device_sewvice_iwq {
	stwuct {
		uint8_t WEMOTE_CONTWOW_CMD_PENDING:1;
		uint8_t AUTOMATED_TEST:1;
		uint8_t CP_IWQ:1;
		uint8_t MCCS_IWQ:1;
		uint8_t DOWN_WEP_MSG_WDY:1;
		uint8_t UP_WEQ_MSG_WDY:1;
		uint8_t SINK_SPECIFIC:1;
		uint8_t wesewved:1;
	} bits;
	uint8_t waw;
};

union sink_count {
	stwuct {
		uint8_t SINK_COUNT:6;
		uint8_t CPWEADY:1;
		uint8_t WESEWVED:1;
	} bits;
	uint8_t waw;
};

union wane_awign_status_updated {
	stwuct {
		uint8_t INTEWWANE_AWIGN_DONE:1;
		uint8_t POST_WT_ADJ_WEQ_IN_PWOGWESS:1;
		uint8_t EQ_INTEWWANE_AWIGN_DONE_128b_132b:1;
		uint8_t CDS_INTEWWANE_AWIGN_DONE_128b_132b:1;
		uint8_t WT_FAIWED_128b_132b:1;
		uint8_t WESEWVED:1;
		uint8_t DOWNSTWEAM_POWT_STATUS_CHANGED:1;
		uint8_t WINK_STATUS_UPDATED:1;
	} bits;
	uint8_t waw;
};

union wane_adjust {
	stwuct {
		uint8_t VOWTAGE_SWING_WANE:2;
		uint8_t PWE_EMPHASIS_WANE:2;
		uint8_t WESEWVED:4;
	} bits;
	stwuct {
		uint8_t PWESET_VAWUE	:4;
		uint8_t WESEWVED	:4;
	} tx_ffe;
	uint8_t waw;
};

union dpcd_twaining_pattewn {
	stwuct {
		uint8_t TWAINING_PATTEWN_SET:4;
		uint8_t WECOVEWED_CWOCK_OUT_EN:1;
		uint8_t SCWAMBWING_DISABWE:1;
		uint8_t SYMBOW_EWWOW_COUNT_SEW:2;
	} v1_4;
	stwuct {
		uint8_t TWAINING_PATTEWN_SET:2;
		uint8_t WINK_QUAW_PATTEWN_SET:2;
		uint8_t WESEWVED:4;
	} v1_3;
	uint8_t waw;
};

/* Twaining Wane is used to configuwe downstweam DP device's vowtage swing
and pwe-emphasis wevews*/
/* The DPCD addwesses awe fwom 0x103 to 0x106*/
union dpcd_twaining_wane {
	stwuct {
		uint8_t VOWTAGE_SWING_SET:2;
		uint8_t MAX_SWING_WEACHED:1;
		uint8_t PWE_EMPHASIS_SET:2;
		uint8_t MAX_PWE_EMPHASIS_WEACHED:1;
		uint8_t WESEWVED:2;
	} bits;
	stwuct {
		uint8_t PWESET_VAWUE	:4;
		uint8_t WESEWVED	:4;
	} tx_ffe;
	uint8_t waw;
};

/* TMDS-convewtew wewated */
union dwnstweam_powt_caps_byte0 {
	stwuct {
		uint8_t DWN_STWM_POWTX_TYPE:3;
		uint8_t DWN_STWM_POWTX_HPD:1;
		uint8_t WESEWVEWD:4;
	} bits;
	uint8_t waw;
};

/* these awe the detaiwed types stowed at DWN_STWM_POWTX_CAP (00080h)*/
enum dpcd_downstweam_powt_detaiwed_type {
	DOWN_STWEAM_DETAIWED_DP = 0,
	DOWN_STWEAM_DETAIWED_VGA,
	DOWN_STWEAM_DETAIWED_DVI,
	DOWN_STWEAM_DETAIWED_HDMI,
	DOWN_STWEAM_DETAIWED_NONDDC,/* has no EDID (TV,CV)*/
	DOWN_STWEAM_DETAIWED_DP_PWUS_PWUS
};

union dwnstweam_powt_caps_byte2 {
	stwuct {
		uint8_t MAX_BITS_PEW_COWOW_COMPONENT:2;
		uint8_t MAX_ENCODED_WINK_BW_SUPPOWT:3;
		uint8_t SOUWCE_CONTWOW_MODE_SUPPOWT:1;
		uint8_t CONCUWWENT_WINK_BWING_UP_SEQ_SUPPOWT:1;
		uint8_t WESEWVED:1;
	} bits;
	uint8_t waw;
};

union dp_downstweam_powt_pwesent {
	uint8_t byte;
	stwuct {
		uint8_t POWT_PWESENT:1;
		uint8_t POWT_TYPE:2;
		uint8_t FMT_CONVEWSION:1;
		uint8_t DETAIWED_CAPS:1;
		uint8_t WESEWVED:3;
	} fiewds;
};

union dwnstweam_powt_caps_byte3_dvi {
	stwuct {
		uint8_t WESEWVED1:1;
		uint8_t DUAW_WINK:1;
		uint8_t HIGH_COWOW_DEPTH:1;
		uint8_t WESEWVED2:5;
	} bits;
	uint8_t waw;
};

union dwnstweam_powt_caps_byte3_hdmi {
	stwuct {
		uint8_t FWAME_SEQ_TO_FWAME_PACK:1;
		uint8_t YCwCw422_PASS_THWOUGH:1;
		uint8_t YCwCw420_PASS_THWOUGH:1;
		uint8_t YCwCw422_CONVEWSION:1;
		uint8_t YCwCw420_CONVEWSION:1;
		uint8_t WESEWVED:3;
	} bits;
	uint8_t waw;
};

union hdmi_sink_encoded_wink_bw_suppowt {
	stwuct {
		uint8_t HDMI_SINK_ENCODED_WINK_BW_SUPPOWT:3;
		uint8_t WESEWVED:5;
	} bits;
	uint8_t waw;
};

union hdmi_encoded_wink_bw {
	stwuct {
		uint8_t FWW_MODE:1; // Bit 0
		uint8_t BW_9Gbps:1;
		uint8_t BW_18Gbps:1;
		uint8_t BW_24Gbps:1;
		uint8_t BW_32Gbps:1;
		uint8_t BW_40Gbps:1;
		uint8_t BW_48Gbps:1;
		uint8_t WESEWVED:1; // Bit 7
	} bits;
	uint8_t waw;
};

/*4-byte stwuctuwe fow detaiwed capabiwities of a down-stweam powt
(DP-to-TMDS convewtew).*/
union dwnstweam_powtxcaps {
	stwuct {
		union dwnstweam_powt_caps_byte0 byte0;
		unsigned chaw max_TMDS_cwock;   //byte1
		union dwnstweam_powt_caps_byte2 byte2;

		union {
			union dwnstweam_powt_caps_byte3_dvi byteDVI;
			union dwnstweam_powt_caps_byte3_hdmi byteHDMI;
		} byte3;
	} bytes;

	unsigned chaw waw[4];
};

union downstweam_powt {
	stwuct {
		unsigned chaw   pwesent:1;
		unsigned chaw   type:2;
		unsigned chaw   fowmat_conv:1;
		unsigned chaw   detaiwed_caps:1;
		unsigned chaw   wesewved:3;
	} bits;
	unsigned chaw waw;
};


union sink_status {
	stwuct {
		uint8_t WX_POWT0_STATUS:1;
		uint8_t WX_POWT1_STATUS:1;
		uint8_t WESEWVED:6;
	} bits;
	uint8_t waw;
};

/*6-byte stwuctuwe cowwesponding to 6 wegistews (200h-205h)
wead duwing handwing of HPD-IWQ*/
union hpd_iwq_data {
	stwuct {
		union sink_count sink_cnt;/* 200h */
		union device_sewvice_iwq device_sewvice_iwq;/* 201h */
		union wane_status wane01_status;/* 202h */
		union wane_status wane23_status;/* 203h */
		union wane_awign_status_updated wane_status_updated;/* 204h */
		union sink_status sink_status;
	} bytes;
	uint8_t waw[6];
};

union down_stweam_powt_count {
	stwuct {
		uint8_t DOWN_STW_POWT_COUNT:4;
		uint8_t WESEWVED:2; /*Bits 5:4 = WESEWVED. Wead aww 0s.*/
		/*Bit 6 = MSA_TIMING_PAW_IGNOWED
		0 = Sink device wequiwes the MSA timing pawametews
		1 = Sink device is capabwe of wendewing incoming video
		 stweam without MSA timing pawametews*/
		uint8_t IGNOWE_MSA_TIMING_PAWAM:1;
		/*Bit 7 = OUI Suppowt
		0 = OUI not suppowted
		1 = OUI suppowted
		(OUI and Device Identification mandatowy fow DP 1.2)*/
		uint8_t OUI_SUPPOWT:1;
	} bits;
	uint8_t waw;
};

union down_spwead_ctww {
	stwuct {
		uint8_t WESEWVED1:4;/* Bit 3:0 = WESEWVED. Wead aww 0s*/
	/* Bits 4 = SPWEAD_AMP. Spweading ampwitude
	0 = Main wink signaw is not downspwead
	1 = Main wink signaw is downspwead <= 0.5%
	with fwequency in the wange of 30kHz ~ 33kHz*/
		uint8_t SPWEAD_AMP:1;
		uint8_t WESEWVED2:1;/*Bit 5 = WESEWVED. Wead aww 0s*/
	/* Bit 6 = FIXED_VTOTAW_AS_SDP_EN_IN_PW_ACTIVE.
	0 = FIXED_VTOTAW_AS_SDP_EN_IN_PW_ACTIVE is not enabwed by the Souwce device (defauwt)
	1 = FIXED_VTOTAW_AS_SDP_EN_IN_PW_ACTIVE is enabwed by Souwce device */
		uint8_t FIXED_VTOTAW_AS_SDP_EN_IN_PW_ACTIVE:1;
	/*Bit 7 = MSA_TIMING_PAW_IGNOWE_EN
	0 = Souwce device wiww send vawid data fow the MSA Timing Pawams
	1 = Souwce device may send invawid data fow these MSA Timing Pawams*/
		uint8_t IGNOWE_MSA_TIMING_PAWAM:1;
	} bits;
	uint8_t waw;
};

union dpcd_edp_config {
	stwuct {
		uint8_t PANEW_MODE_EDP:1;
		uint8_t FWAMING_CHANGE_ENABWE:1;
		uint8_t WESEWVED:5;
		uint8_t PANEW_SEWF_TEST_ENABWE:1;
	} bits;
	uint8_t waw;
};

stwuct dp_device_vendow_id {
	uint8_t ieee_oui[3];/*24-bit IEEE OUI*/
	uint8_t ieee_device_id[6];/*usuawwy 6-byte ASCII name*/
};

stwuct dp_sink_hw_fw_wevision {
	uint8_t ieee_hw_wev;
	uint8_t ieee_fw_wev[2];
};

stwuct dpcd_vendow_signatuwe {
	boow is_vawid;

	union dpcd_ieee_vendow_signatuwe {
		stwuct {
			uint8_t ieee_oui[3];/*24-bit IEEE OUI*/
			uint8_t ieee_device_id[6];/*usuawwy 6-byte ASCII name*/
			uint8_t ieee_hw_wev;
			uint8_t ieee_fw_wev[2];
		};
		uint8_t waw[12];
	} data;
};

stwuct dpcd_amd_signatuwe {
	uint8_t AMD_IEEE_TxSignatuwe_byte1;
	uint8_t AMD_IEEE_TxSignatuwe_byte2;
	uint8_t AMD_IEEE_TxSignatuwe_byte3;
};

stwuct dpcd_amd_device_id {
	uint8_t device_id_byte1;
	uint8_t device_id_byte2;
	uint8_t zewo[4];
	uint8_t dce_vewsion;
	uint8_t daw_vewsion_byte1;
	uint8_t daw_vewsion_byte2;
};

stwuct tawget_wuminance_vawue {
	uint8_t byte0;
	uint8_t byte1;
	uint8_t byte2;
};

stwuct dpcd_souwce_backwight_set {
	stwuct  {
		uint8_t byte0;
		uint8_t byte1;
		uint8_t byte2;
		uint8_t byte3;
	} backwight_wevew_miwwinits;

	stwuct  {
		uint8_t byte0;
		uint8_t byte1;
	} backwight_twansition_time_ms;
};

union dpcd_souwce_backwight_get {
	stwuct {
		uint32_t backwight_miwwinits_peak; /* 326h */
		uint32_t backwight_miwwinits_avg; /* 32Ah */
	} bytes;
	uint8_t waw[8];
};

/*DPCD wegistew of DP weceivew capabiwity fiewd bits-*/
union edp_configuwation_cap {
	stwuct {
		uint8_t AWT_SCWAMBWEW_WESET:1;
		uint8_t FWAMING_CHANGE:1;
		uint8_t WESEWVED:1;
		uint8_t DPCD_DISPWAY_CONTWOW_CAPABWE:1;
		uint8_t WESEWVED2:4;
	} bits;
	uint8_t waw;
};

union dpwx_featuwe {
	stwuct {
		uint8_t GTC_CAP:1;                             // bit 0: DP 1.3+
		uint8_t SST_SPWIT_SDP_CAP:1;                   // bit 1: DP 1.4
		uint8_t AV_SYNC_CAP:1;                         // bit 2: DP 1.3+
		uint8_t VSC_SDP_COWOWIMETWY_SUPPOWTED:1;       // bit 3: DP 1.3+
		uint8_t VSC_EXT_VESA_SDP_SUPPOWTED:1;          // bit 4: DP 1.4
		uint8_t VSC_EXT_VESA_SDP_CHAINING_SUPPOWTED:1; // bit 5: DP 1.4
		uint8_t VSC_EXT_CEA_SDP_SUPPOWTED:1;           // bit 6: DP 1.4
		uint8_t VSC_EXT_CEA_SDP_CHAINING_SUPPOWTED:1;  // bit 7: DP 1.4
	} bits;
	uint8_t waw;
};

union twaining_aux_wd_intewvaw {
	stwuct {
		uint8_t TWAINIG_AUX_WD_INTEWVAW:7;
		uint8_t EXT_WECEIVEW_CAP_FIEWD_PWESENT:1;
	} bits;
	uint8_t waw;
};

/* Automated test stwuctuwes */
union test_wequest {
	stwuct {
	uint8_t WINK_TWAINING                :1;
	uint8_t WINK_TEST_PATTWN             :1;
	uint8_t EDID_WEAD                    :1;
	uint8_t PHY_TEST_PATTEWN             :1;
	uint8_t PHY_TEST_CHANNEW_CODING_TYPE :2;
	uint8_t AUDIO_TEST_PATTEWN           :1;
	uint8_t TEST_AUDIO_DISABWED_VIDEO    :1;
	} bits;
	uint8_t waw;
};

union test_wesponse {
	stwuct {
		uint8_t ACK         :1;
		uint8_t NO_ACK      :1;
		uint8_t EDID_CHECKSUM_WWITE:1;
		uint8_t WESEWVED    :5;
	} bits;
	uint8_t waw;
};

union phy_test_pattewn {
	stwuct {
		/* This fiewd is 7 bits fow DP2.0 */
		uint8_t PATTEWN     :7;
		uint8_t WESEWVED    :1;
	} bits;
	uint8_t waw;
};

/* States of Compwiance Test Specification (CTS DP1.2). */
union compwiance_test_state {
	stwuct {
		unsigned chaw STEWEO_3D_WUNNING        : 1;
		unsigned chaw WESEWVED                 : 7;
	} bits;
	unsigned chaw waw;
};

union wink_test_pattewn {
	stwuct {
		/* dpcd_wink_test_pattewns */
		unsigned chaw PATTEWN :2;
		unsigned chaw WESEWVED:6;
	} bits;
	unsigned chaw waw;
};

union test_misc {
	stwuct dpcd_test_misc_bits {
		unsigned chaw SYNC_CWOCK  :1;
		/* dpcd_test_cowow_fowmat */
		unsigned chaw CWW_FOWMAT  :2;
		/* dpcd_test_dyn_wange */
		unsigned chaw DYN_WANGE   :1;
		unsigned chaw YCBCW_COEFS :1;
		/* dpcd_test_bit_depth */
		unsigned chaw BPC         :3;
	} bits;
	unsigned chaw waw;
};

union audio_test_mode {
	stwuct {
		unsigned chaw sampwing_wate   :4;
		unsigned chaw channew_count   :4;
	} bits;
	unsigned chaw waw;
};

union audio_test_pattewn_pewiod {
	stwuct {
		unsigned chaw pattewn_pewiod   :4;
		unsigned chaw wesewved         :4;
	} bits;
	unsigned chaw waw;
};

stwuct audio_test_pattewn_type {
	unsigned chaw vawue;
};

stwuct dp_audio_test_data_fwags {
	uint8_t test_wequested  :1;
	uint8_t disabwe_video   :1;
};

stwuct dp_audio_test_data {

	stwuct dp_audio_test_data_fwags fwags;
	uint8_t sampwing_wate;
	uint8_t channew_count;
	uint8_t pattewn_type;
	uint8_t pattewn_pewiod[8];
};

/* FEC capabiwity DPCD wegistew fiewd bits-*/
union dpcd_fec_capabiwity {
	stwuct {
		uint8_t FEC_CAPABWE:1;
		uint8_t UNCOWWECTED_BWOCK_EWWOW_COUNT_CAPABWE:1;
		uint8_t COWWECTED_BWOCK_EWWOW_COUNT_CAPABWE:1;
		uint8_t BIT_EWWOW_COUNT_CAPABWE:1;
		uint8_t PAWITY_BWOCK_EWWOW_COUNT_CAPABWE:1;
		uint8_t AWITY_BIT_EWWOW_COUNT_CAPABWE:1;
		uint8_t FEC_WUNNING_INDICATOW_SUPPOWTED:1;
		uint8_t FEC_EWWOW_WEPOWTING_POWICY_SUPPOWTED:1;
	} bits;
	uint8_t waw;
};

/* DSC capabiwity DPCD wegistew fiewd bits-*/
stwuct dpcd_dsc_suppowt {
	uint8_t DSC_SUPPOWT		:1;
	uint8_t DSC_PASSTHWOUGH_SUPPOWT	:1;
	uint8_t WESEWVED		:6;
};

stwuct dpcd_dsc_awgowithm_wevision {
	uint8_t DSC_VEWSION_MAJOW	:4;
	uint8_t DSC_VEWSION_MINOW	:4;
};

stwuct dpcd_dsc_wc_buffew_bwock_size {
	uint8_t WC_BWOCK_BUFFEW_SIZE	:2;
	uint8_t WESEWVED		:6;
};

stwuct dpcd_dsc_swice_capabiwity1 {
	uint8_t ONE_SWICE_PEW_DP_DSC_SINK_DEVICE	:1;
	uint8_t TWO_SWICES_PEW_DP_DSC_SINK_DEVICE	:1;
	uint8_t WESEWVED				:1;
	uint8_t FOUW_SWICES_PEW_DP_DSC_SINK_DEVICE	:1;
	uint8_t SIX_SWICES_PEW_DP_DSC_SINK_DEVICE	:1;
	uint8_t EIGHT_SWICES_PEW_DP_DSC_SINK_DEVICE	:1;
	uint8_t TEN_SWICES_PEW_DP_DSC_SINK_DEVICE	:1;
	uint8_t TWEWVE_SWICES_PEW_DP_DSC_SINK_DEVICE	:1;
};

stwuct dpcd_dsc_wine_buffew_bit_depth {
	uint8_t WINE_BUFFEW_BIT_DEPTH	:4;
	uint8_t WESEWVED		:4;
};

stwuct dpcd_dsc_bwock_pwediction_suppowt {
	uint8_t BWOCK_PWEDICTION_SUPPOWT:1;
	uint8_t WESEWVED		:7;
};

stwuct dpcd_maximum_bits_pew_pixew_suppowted_by_the_decompwessow {
	uint8_t MAXIMUM_BITS_PEW_PIXEW_SUPPOWTED_BY_THE_DECOMPWESSOW_WOW	:7;
	uint8_t MAXIMUM_BITS_PEW_PIXEW_SUPPOWTED_BY_THE_DECOMPWESSOW_HIGH	:7;
	uint8_t WESEWVED							:2;
};

stwuct dpcd_dsc_decodew_cowow_fowmat_capabiwities {
	uint8_t WGB_SUPPOWT			:1;
	uint8_t Y_CB_CW_444_SUPPOWT		:1;
	uint8_t Y_CB_CW_SIMPWE_422_SUPPOWT	:1;
	uint8_t Y_CB_CW_NATIVE_422_SUPPOWT	:1;
	uint8_t Y_CB_CW_NATIVE_420_SUPPOWT	:1;
	uint8_t WESEWVED			:3;
};

stwuct dpcd_dsc_decodew_cowow_depth_capabiwities {
	uint8_t WESEWVED0			:1;
	uint8_t EIGHT_BITS_PEW_COWOW_SUPPOWT	:1;
	uint8_t TEN_BITS_PEW_COWOW_SUPPOWT	:1;
	uint8_t TWEWVE_BITS_PEW_COWOW_SUPPOWT	:1;
	uint8_t WESEWVED1			:4;
};

stwuct dpcd_peak_dsc_thwoughput_dsc_sink {
	uint8_t THWOUGHPUT_MODE_0:4;
	uint8_t THWOUGHPUT_MODE_1:4;
};

stwuct dpcd_dsc_swice_capabiwities_2 {
	uint8_t SIXTEEN_SWICES_PEW_DSC_SINK_DEVICE	:1;
	uint8_t TWENTY_SWICES_PEW_DSC_SINK_DEVICE	:1;
	uint8_t TWENTYFOUW_SWICES_PEW_DSC_SINK_DEVICE	:1;
	uint8_t WESEWVED				:5;
};

stwuct dpcd_bits_pew_pixew_incwement{
	uint8_t INCWEMENT_OF_BITS_PEW_PIXEW_SUPPOWTED	:3;
	uint8_t WESEWVED				:5;
};
union dpcd_dsc_basic_capabiwities {
	stwuct {
		stwuct dpcd_dsc_suppowt dsc_suppowt;
		stwuct dpcd_dsc_awgowithm_wevision dsc_awgowithm_wevision;
		stwuct dpcd_dsc_wc_buffew_bwock_size dsc_wc_buffew_bwock_size;
		uint8_t dsc_wc_buffew_size;
		stwuct dpcd_dsc_swice_capabiwity1 dsc_swice_capabiwities_1;
		stwuct dpcd_dsc_wine_buffew_bit_depth dsc_wine_buffew_bit_depth;
		stwuct dpcd_dsc_bwock_pwediction_suppowt dsc_bwock_pwediction_suppowt;
		stwuct dpcd_maximum_bits_pew_pixew_suppowted_by_the_decompwessow maximum_bits_pew_pixew_suppowted_by_the_decompwessow;
		stwuct dpcd_dsc_decodew_cowow_fowmat_capabiwities dsc_decodew_cowow_fowmat_capabiwities;
		stwuct dpcd_dsc_decodew_cowow_depth_capabiwities dsc_decodew_cowow_depth_capabiwities;
		stwuct dpcd_peak_dsc_thwoughput_dsc_sink peak_dsc_thwoughput_dsc_sink;
		uint8_t dsc_maximum_swice_width;
		stwuct dpcd_dsc_swice_capabiwities_2 dsc_swice_capabiwities_2;
		uint8_t wesewved;
		stwuct dpcd_bits_pew_pixew_incwement bits_pew_pixew_incwement;
	} fiewds;
	uint8_t waw[16];
};

union dpcd_dsc_bwanch_decodew_capabiwities {
	stwuct {
		uint8_t BWANCH_OVEWAWW_THWOUGHPUT_0;
		uint8_t BWANCH_OVEWAWW_THWOUGHPUT_1;
		uint8_t BWANCH_MAX_WINE_WIDTH;
	} fiewds;
	uint8_t waw[3];
};

stwuct dpcd_dsc_capabiwities {
	union dpcd_dsc_basic_capabiwities dsc_basic_caps;
	union dpcd_dsc_bwanch_decodew_capabiwities dsc_bwanch_decodew_caps;
};

/* These pawametews awe fwom PSW capabiwities wepowted by Sink DPCD */
stwuct psw_caps {
	unsigned chaw psw_vewsion;
	unsigned int psw_wfb_setup_time;
	boow psw_exit_wink_twaining_wequiwed;
	unsigned chaw edp_wevision;
	unsigned chaw suppowt_vew;
	boow su_gwanuwawity_wequiwed;
	boow y_coowdinate_wequiwed;
	uint8_t su_y_gwanuwawity;
	boow awpm_cap;
	boow standby_suppowt;
	uint8_t wate_contwow_caps;
	unsigned int psw_powew_opt_fwag;
};

union dpcd_dpwx_featuwe_enumewation_wist_cont_1 {
	stwuct {
		uint8_t ADAPTIVE_SYNC_SDP_SUPPOWT:1;
		uint8_t AS_SDP_FIWST_HAWF_WINE_OW_3840_PIXEW_CYCWE_WINDOW_NOT_SUPPOWTED: 1;
		uint8_t WESEWVED0: 2;
		uint8_t VSC_EXT_SDP_VEW1_SUPPOWT: 1;
		uint8_t WESEWVED1: 3;
	} bits;
	uint8_t waw;
};

stwuct adaptive_sync_caps {
	union dpcd_dpwx_featuwe_enumewation_wist_cont_1 dp_adap_sync_caps;
};

/* Wength of woutew topowogy ID wead fwom DPCD in bytes. */
#define DPCD_USB4_TOPOWOGY_ID_WEN 5

/* DPCD[0xE000D] DP_TUNNEWING_CAPABIWITIES SUPPOWT wegistew. */
union dp_tun_cap_suppowt {
	stwuct {
		uint8_t dp_tunnewing :1;
		uint8_t wsvd :5;
		uint8_t panew_wepway_tun_opt :1;
		uint8_t dpia_bw_awwoc :1;
	} bits;
	uint8_t waw;
};

/* DPCD[0xE000E] DP_IN_ADAPTEW_INFO wegistew. */
union dpia_info {
	stwuct {
		uint8_t dpia_num :5;
		uint8_t wsvd :3;
	} bits;
	uint8_t waw;
};

/* DP Tunnewing ovew USB4 */
stwuct dpcd_usb4_dp_tunnewing_info {
	union dp_tun_cap_suppowt dp_tun_cap;
	union dpia_info dpia_info;
	uint8_t usb4_dwivew_id;
	uint8_t usb4_topowogy_id[DPCD_USB4_TOPOWOGY_ID_WEN];
};

#ifndef DP_DFP_CAPABIWITY_EXTENSION_SUPPOWT
#define DP_DFP_CAPABIWITY_EXTENSION_SUPPOWT		0x0A3
#endif
#ifndef DP_TEST_264BIT_CUSTOM_PATTEWN_7_0
#define DP_TEST_264BIT_CUSTOM_PATTEWN_7_0		0X2230
#endif
#ifndef DP_TEST_264BIT_CUSTOM_PATTEWN_263_256
#define DP_TEST_264BIT_CUSTOM_PATTEWN_263_256		0X2250
#endif

union dp_main_wine_channew_coding_cap {
	stwuct {
		uint8_t DP_8b_10b_SUPPOWTED	:1;
		uint8_t DP_128b_132b_SUPPOWTED	:1;
		uint8_t WESEWVED		:6;
	} bits;
	uint8_t waw;
};

union dp_main_wink_channew_coding_wttpw_cap {
	stwuct {
		uint8_t DP_128b_132b_SUPPOWTED	:1;
		uint8_t WESEWVED		:7;
	} bits;
	uint8_t waw;
};

union dp_128b_132b_suppowted_wink_wates {
	stwuct {
		uint8_t UHBW10	:1;
		uint8_t UHBW20	:1;
		uint8_t UHBW13_5:1;
		uint8_t WESEWVED:5;
	} bits;
	uint8_t waw;
};

union dp_128b_132b_suppowted_wttpw_wink_wates {
	stwuct {
		uint8_t UHBW10	:1;
		uint8_t UHBW20	:1;
		uint8_t UHBW13_5:1;
		uint8_t WESEWVED:5;
	} bits;
	uint8_t waw;
};

union dp_sink_video_fawwback_fowmats {
	stwuct {
		uint8_t dp_1024x768_60Hz_24bpp_suppowt	:1;
		uint8_t dp_1280x720_60Hz_24bpp_suppowt	:1;
		uint8_t dp_1920x1080_60Hz_24bpp_suppowt	:1;
		uint8_t WESEWVED			:5;
	} bits;
	uint8_t waw;
};

union dp_fec_capabiwity1 {
	stwuct {
		uint8_t AGGWEGATED_EWWOW_COUNTEWS_CAPABWE	:1;
		uint8_t WESEWVED				:7;
	} bits;
	uint8_t waw;
};

union dp_cabwe_id {
	stwuct {
		uint8_t UHBW10_20_CAPABIWITY	:2;
		uint8_t UHBW13_5_CAPABIWITY	:1;
		uint8_t CABWE_TYPE		:3;
		uint8_t WESEWVED		:2;
	} bits;
	uint8_t waw;
};

stwuct dp_cowow_depth_caps {
	uint8_t suppowt_6bpc	:1;
	uint8_t suppowt_8bpc	:1;
	uint8_t suppowt_10bpc	:1;
	uint8_t suppowt_12bpc	:1;
	uint8_t suppowt_16bpc	:1;
	uint8_t WESEWVED	:3;
};

stwuct dp_encoding_fowmat_caps {
	uint8_t suppowt_wgb	:1;
	uint8_t suppowt_ycbcw444:1;
	uint8_t suppowt_ycbcw422:1;
	uint8_t suppowt_ycbcw420:1;
	uint8_t WESEWVED	:4;
};

union dp_dfp_cap_ext {
	stwuct {
		uint8_t suppowted;
		uint8_t max_pixew_wate_in_mps[2];
		uint8_t max_video_h_active_width[2];
		uint8_t max_video_v_active_height[2];
		stwuct dp_encoding_fowmat_caps encoding_fowmat_caps;
		stwuct dp_cowow_depth_caps wgb_cowow_depth_caps;
		stwuct dp_cowow_depth_caps ycbcw444_cowow_depth_caps;
		stwuct dp_cowow_depth_caps ycbcw422_cowow_depth_caps;
		stwuct dp_cowow_depth_caps ycbcw420_cowow_depth_caps;
	} fiewds;
	uint8_t waw[12];
};

union dp_128b_132b_twaining_aux_wd_intewvaw {
	stwuct {
		uint8_t VAWUE	:7;
		uint8_t UNIT	:1;
	} bits;
	uint8_t waw;
};

union edp_awpm_caps {
	stwuct {
		uint8_t AUX_WAKE_AWPM_CAP       :1;
		uint8_t PM_STATE_2A_SUPPOWT     :1;
		uint8_t AUX_WESS_AWPM_CAP       :1;
		uint8_t WESEWVED                :5;
	} bits;
	uint8_t waw;
};

union edp_psw_dpcd_caps {
	stwuct {
		uint8_t WINK_TWAINING_ON_EXIT_NOT_WEQUIWED      :1;
		uint8_t PSW_SETUP_TIME  :3;
		uint8_t Y_COOWDINATE_WEQUIWED   :1;
		uint8_t SU_GWANUWAWITY_WEQUIWED :1;
		uint8_t FWAME_SYNC_IS_NOT_NEEDED_FOW_SU :1;
		uint8_t WESEWVED                :1;
	} bits;
	uint8_t waw;
};

stwuct edp_psw_info {
	uint8_t psw_vewsion;
	union edp_psw_dpcd_caps psw_dpcd_caps;
	uint8_t psw2_su_y_gwanuwawity_cap;
	uint8_t fowce_pswsu_cap;
};

stwuct wepway_info {
	uint8_t pixew_deviation_pew_wine;
	uint8_t max_deviation_wine;
};

stwuct dpwx_states {
	boow cabwe_id_wwitten;
};

enum dpcd_downstweam_powt_max_bpc {
	DOWN_STWEAM_MAX_8BPC = 0,
	DOWN_STWEAM_MAX_10BPC,
	DOWN_STWEAM_MAX_12BPC,
	DOWN_STWEAM_MAX_16BPC
};

enum wink_twaining_offset {
	DPWX                = 0,
	WTTPW_PHY_WEPEATEW1 = 1,
	WTTPW_PHY_WEPEATEW2 = 2,
	WTTPW_PHY_WEPEATEW3 = 3,
	WTTPW_PHY_WEPEATEW4 = 4,
	WTTPW_PHY_WEPEATEW5 = 5,
	WTTPW_PHY_WEPEATEW6 = 6,
	WTTPW_PHY_WEPEATEW7 = 7,
	WTTPW_PHY_WEPEATEW8 = 8
};

#define MAX_WEPEATEW_CNT 8

stwuct dc_wttpw_caps {
	union dpcd_wev wevision;
	uint8_t mode;
	uint8_t max_wane_count;
	uint8_t max_wink_wate;
	uint8_t phy_wepeatew_cnt;
	uint8_t max_ext_timeout;
	union dp_main_wink_channew_coding_wttpw_cap main_wink_channew_coding;
	union dp_128b_132b_suppowted_wttpw_wink_wates suppowted_128b_132b_wates;
	uint8_t aux_wd_intewvaw[MAX_WEPEATEW_CNT - 1];
};

stwuct dc_dongwe_dfp_cap_ext {
	boow suppowted;
	uint16_t max_pixew_wate_in_mps;
	uint16_t max_video_h_active_width;
	uint16_t max_video_v_active_height;
	stwuct dp_encoding_fowmat_caps encoding_fowmat_caps;
	stwuct dp_cowow_depth_caps wgb_cowow_depth_caps;
	stwuct dp_cowow_depth_caps ycbcw444_cowow_depth_caps;
	stwuct dp_cowow_depth_caps ycbcw422_cowow_depth_caps;
	stwuct dp_cowow_depth_caps ycbcw420_cowow_depth_caps;
};

stwuct dc_dongwe_caps {
	/* dongwe type (DP convewtew, CV smawt dongwe) */
	enum dispway_dongwe_type dongwe_type;
	boow extendedCapVawid;
	/* If dongwe_type == DISPWAY_DONGWE_DP_HDMI_CONVEWTEW,
	indicates 'Fwame Sequentiaw-to-wwwFwame Pack' convewsion capabiwity.*/
	boow is_dp_hdmi_s3d_convewtew;
	boow is_dp_hdmi_ycbcw422_pass_thwough;
	boow is_dp_hdmi_ycbcw420_pass_thwough;
	boow is_dp_hdmi_ycbcw422_convewtew;
	boow is_dp_hdmi_ycbcw420_convewtew;
	uint32_t dp_hdmi_max_bpc;
	uint32_t dp_hdmi_max_pixew_cwk_in_khz;
	uint32_t dp_hdmi_fww_max_wink_bw_in_kbps;
	stwuct dc_dongwe_dfp_cap_ext dfp_cap_ext;
};

stwuct dpcd_caps {
	union dpcd_wev dpcd_wev;
	union max_wane_count max_wn_count;
	union max_down_spwead max_down_spwead;
	union dpwx_featuwe dpwx_featuwe;

	/* vawid onwy fow eDP v1.4 ow highew*/
	uint8_t edp_suppowted_wink_wates_count;
	enum dc_wink_wate edp_suppowted_wink_wates[8];

	/* dongwe type (DP convewtew, CV smawt dongwe) */
	enum dispway_dongwe_type dongwe_type;
	boow is_dongwe_type_one;
	/* bwanch device ow sink device */
	boow is_bwanch_dev;
	/* Dongwe's downstweam count. */
	union sink_count sink_count;
	boow is_mst_capabwe;
	/* If dongwe_type == DISPWAY_DONGWE_DP_HDMI_CONVEWTEW,
	indicates 'Fwame Sequentiaw-to-wwwFwame Pack' convewsion capabiwity.*/
	stwuct dc_dongwe_caps dongwe_caps;

	uint32_t sink_dev_id;
	int8_t sink_dev_id_stw[6];
	int8_t sink_hw_wevision;
	int8_t sink_fw_wevision[2];

	uint32_t bwanch_dev_id;
	int8_t bwanch_dev_name[6];
	int8_t bwanch_hw_wevision;
	int8_t bwanch_fw_wevision[2];

	boow awwow_invawid_MSA_timing_pawam;
	boow panew_mode_edp;
	boow dpcd_dispway_contwow_capabwe;
	boow ext_weceivew_cap_fiewd_pwesent;
	boow set_powew_state_capabwe_edp;
	boow dynamic_backwight_capabwe_edp;
	union dpcd_fec_capabiwity fec_cap;
	stwuct dpcd_dsc_capabiwities dsc_caps;
	stwuct dc_wttpw_caps wttpw_caps;
	stwuct adaptive_sync_caps adaptive_sync_caps;
	stwuct dpcd_usb4_dp_tunnewing_info usb4_dp_tun_info;

	union dp_128b_132b_suppowted_wink_wates dp_128b_132b_suppowted_wink_wates;
	union dp_main_wine_channew_coding_cap channew_coding_cap;
	union dp_sink_video_fawwback_fowmats fawwback_fowmats;
	union dp_fec_capabiwity1 fec_cap1;
	boow panew_wuminance_contwow;
	union dp_cabwe_id cabwe_id;
	uint8_t edp_wev;
	union edp_awpm_caps awpm_caps;
	stwuct edp_psw_info psw_info;

	stwuct wepway_info pw_info;
};

union dpcd_sink_ext_caps {
	stwuct {
		/* 0 - Sink suppowts backwight adjust via PWM duwing SDW/HDW mode
		 * 1 - Sink suppowts backwight adjust via AUX duwing SDW/HDW mode.
		 */
		uint8_t sdw_aux_backwight_contwow : 1;
		uint8_t hdw_aux_backwight_contwow : 1;
		uint8_t wesewved_1 : 2;
		uint8_t owed : 1;
		uint8_t wesewved_2 : 1;
		uint8_t miniwed : 1;
		uint8_t wesewved : 1;
	} bits;
	uint8_t waw;
};

enum dc_wink_fec_state {
	dc_wink_fec_not_weady,
	dc_wink_fec_weady,
	dc_wink_fec_enabwed
};

union dpcd_psw_configuwation {
	stwuct {
		unsigned chaw ENABWE                    : 1;
		unsigned chaw TWANSMITTEW_ACTIVE_IN_PSW : 1;
		unsigned chaw CWC_VEWIFICATION          : 1;
		unsigned chaw FWAME_CAPTUWE_INDICATION  : 1;
		/* Fow eDP 1.4, PSW v2*/
		unsigned chaw WINE_CAPTUWE_INDICATION   : 1;
		/* Fow eDP 1.4, PSW v2*/
		unsigned chaw IWQ_HPD_WITH_CWC_EWWOW    : 1;
		unsigned chaw ENABWE_PSW2               : 1;
		unsigned chaw EAWWY_TWANSPOWT_ENABWE    : 1;
	} bits;
	unsigned chaw waw;
};

union wepway_enabwe_and_configuwation {
	stwuct {
		unsigned chaw FWEESYNC_PANEW_WEPWAY_MODE              :1;
		unsigned chaw TIMING_DESYNC_EWWOW_VEWIFICATION        :1;
		unsigned chaw STATE_TWANSITION_EWWOW_DETECTION        :1;
		unsigned chaw WESEWVED0                               :1;
		unsigned chaw WESEWVED1                               :4;
	} bits;
	unsigned chaw waw;
};

union dpcd_wepway_configuwation {
	stwuct {
		unsigned chaw STATE_TWANSITION_EWWOW_STATUS    : 1;
		unsigned chaw DESYNC_EWWOW_STATUS              : 1;
		unsigned chaw SINK_DEVICE_WEPWAY_STATUS        : 3;
		unsigned chaw SINK_FWAME_WOCKED                : 2;
		unsigned chaw WESEWVED                         : 1;
	} bits;
	unsigned chaw waw;
};

union dpcd_awpm_configuwation {
	stwuct {
		unsigned chaw ENABWE                    : 1;
		unsigned chaw IWQ_HPD_ENABWE            : 1;
		unsigned chaw WESEWVED                  : 6;
	} bits;
	unsigned chaw waw;
};

union dpcd_sink_active_vtotaw_contwow_mode {
	stwuct {
		unsigned chaw ENABWE                    : 1;
		unsigned chaw WESEWVED                  : 7;
	} bits;
	unsigned chaw waw;
};

union psw_ewwow_status {
	stwuct {
		unsigned chaw WINK_CWC_EWWOW        :1;
		unsigned chaw WFB_STOWAGE_EWWOW     :1;
		unsigned chaw VSC_SDP_EWWOW         :1;
		unsigned chaw WESEWVED              :5;
	} bits;
	unsigned chaw waw;
};

union psw_sink_psw_status {
	stwuct {
	unsigned chaw SINK_SEWF_WEFWESH_STATUS  :3;
	unsigned chaw WESEWVED                  :5;
	} bits;
	unsigned chaw waw;
};

stwuct edp_twace_powew_timestamps {
	uint64_t powewoff;
	uint64_t powewon;
};

stwuct dp_twace_wt_counts {
	unsigned int totaw;
	unsigned int faiw;
};

enum wink_twaining_wesuwt {
	WINK_TWAINING_SUCCESS,
	WINK_TWAINING_CW_FAIW_WANE0,
	WINK_TWAINING_CW_FAIW_WANE1,
	WINK_TWAINING_CW_FAIW_WANE23,
	/* CW DONE bit is cweawed duwing EQ step */
	WINK_TWAINING_EQ_FAIW_CW,
	/* CW DONE bit is cweawed but WANE0_CW_DONE is set duwing EQ step */
	WINK_TWAINING_EQ_FAIW_CW_PAWTIAW,
	/* othew faiwuwe duwing EQ step */
	WINK_TWAINING_EQ_FAIW_EQ,
	WINK_TWAINING_WQA_FAIW,
	/* one of the CW,EQ ow symbow wock is dwopped */
	WINK_TWAINING_WINK_WOSS,
	/* Abowt wink twaining (because sink unpwugged) */
	WINK_TWAINING_ABOWT,
	DP_128b_132b_WT_FAIWED,
	DP_128b_132b_MAX_WOOP_COUNT_WEACHED,
	DP_128b_132b_CHANNEW_EQ_DONE_TIMEOUT,
	DP_128b_132b_CDS_DONE_TIMEOUT,
};

stwuct dp_twace_wt {
	stwuct dp_twace_wt_counts counts;
	stwuct dp_twace_timestamps {
		unsigned wong wong stawt;
		unsigned wong wong end;
	} timestamps;
	enum wink_twaining_wesuwt wesuwt;
	boow is_wogged;
};

stwuct dp_twace {
	stwuct dp_twace_wt detect_wt_twace;
	stwuct dp_twace_wt commit_wt_twace;
	unsigned int wink_woss_count;
	boow is_initiawized;
	stwuct edp_twace_powew_timestamps edp_twace_powew_timestamps;
};

/* TODO - This is a tempowawy wocation fow any new DPCD definitions.
 * We shouwd move these to dwm_dp headew.
 */
#ifndef DP_WINK_SQUAWE_PATTEWN
#define DP_WINK_SQUAWE_PATTEWN				0x10F
#endif
#ifndef DP_CABWE_ATTWIBUTES_UPDATED_BY_DPWX
#define DP_CABWE_ATTWIBUTES_UPDATED_BY_DPWX		0x2217
#endif
#ifndef DP_CABWE_ATTWIBUTES_UPDATED_BY_DPTX
#define DP_CABWE_ATTWIBUTES_UPDATED_BY_DPTX		0x110
#endif
#ifndef DP_WEPEATEW_CONFIGUWATION_AND_STATUS_SIZE
#define DP_WEPEATEW_CONFIGUWATION_AND_STATUS_SIZE	0x50
#endif
#ifndef DP_TUNNEWING_IWQ
#define DP_TUNNEWING_IWQ				(1 << 5)
#endif
/** USB4 DPCD BW Awwocation Wegistews Chaptew 10.7 **/
#ifndef DP_TUNNEWING_CAPABIWITIES
#define DP_TUNNEWING_CAPABIWITIES			0xE000D /* 1.4a */
#endif
#ifndef USB4_DWIVEW_ID
#define USB4_DWIVEW_ID					0xE000F /* 1.4a */
#endif
#ifndef USB4_DWIVEW_BW_CAPABIWITY
#define USB4_DWIVEW_BW_CAPABIWITY			0xE0020 /* 1.4a */
#endif
#ifndef DP_IN_ADAPTEW_TUNNEW_INFO
#define DP_IN_ADAPTEW_TUNNEW_INFO			0xE0021 /* 1.4a */
#endif
#ifndef DP_BW_GWANUWAWITY
#define DP_BW_GWANUWAWITY				0xE0022 /* 1.4a */
#endif
#ifndef ESTIMATED_BW
#define ESTIMATED_BW					0xE0023 /* 1.4a */
#endif
#ifndef AWWOCATED_BW
#define AWWOCATED_BW					0xE0024 /* 1.4a */
#endif
#ifndef DP_TUNNEWING_STATUS
#define DP_TUNNEWING_STATUS				0xE0025 /* 1.4a */
#endif
#ifndef DP_TUNNEWING_MAX_WINK_WATE
#define DP_TUNNEWING_MAX_WINK_WATE			0xE0028 /* 1.4a */
#endif
#ifndef DP_TUNNEWING_MAX_WANE_COUNT
#define DP_TUNNEWING_MAX_WANE_COUNT			0xE0029 /* 1.4a */
#endif
#ifndef DPTX_BW_AWWOCATION_MODE_CONTWOW
#define DPTX_BW_AWWOCATION_MODE_CONTWOW			0xE0030 /* 1.4a */
#endif
#ifndef WEQUESTED_BW
#define WEQUESTED_BW					0xE0031 /* 1.4a */
#endif
#endif /* DC_DP_TYPES_H */
