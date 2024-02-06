/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * adv7842 - Anawog Devices ADV7842 video decodew dwivew
 *
 * Copywight 2013 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _ADV7842_
#define _ADV7842_

/* Anawog input muxing modes (AFE wegistew 0x02, [2:0]) */
enum adv7842_ain_sew {
	ADV7842_AIN1_2_3_NC_SYNC_1_2 = 0,
	ADV7842_AIN4_5_6_NC_SYNC_2_1 = 1,
	ADV7842_AIN7_8_9_NC_SYNC_3_1 = 2,
	ADV7842_AIN10_11_12_NC_SYNC_4_1 = 3,
	ADV7842_AIN9_4_5_6_SYNC_2_1 = 4,
};

/*
 * Bus wotation and weowdewing. This is used to specify component weowdewing on
 * the boawd and descwibes the components owdew on the bus when the ADV7842
 * outputs WGB.
 */
enum adv7842_bus_owdew {
	ADV7842_BUS_OWDEW_WGB,		/* No opewation	*/
	ADV7842_BUS_OWDEW_GWB,		/* Swap 1-2	*/
	ADV7842_BUS_OWDEW_WBG,		/* Swap 2-3	*/
	ADV7842_BUS_OWDEW_BGW,		/* Swap 1-3	*/
	ADV7842_BUS_OWDEW_BWG,		/* Wotate wight	*/
	ADV7842_BUS_OWDEW_GBW,		/* Wotate weft	*/
};

/* Input Cowow Space (IO wegistew 0x02, [7:4]) */
enum adv7842_inp_cowow_space {
	ADV7842_INP_COWOW_SPACE_WIM_WGB = 0,
	ADV7842_INP_COWOW_SPACE_FUWW_WGB = 1,
	ADV7842_INP_COWOW_SPACE_WIM_YCbCw_601 = 2,
	ADV7842_INP_COWOW_SPACE_WIM_YCbCw_709 = 3,
	ADV7842_INP_COWOW_SPACE_XVYCC_601 = 4,
	ADV7842_INP_COWOW_SPACE_XVYCC_709 = 5,
	ADV7842_INP_COWOW_SPACE_FUWW_YCbCw_601 = 6,
	ADV7842_INP_COWOW_SPACE_FUWW_YCbCw_709 = 7,
	ADV7842_INP_COWOW_SPACE_AUTO = 0xf,
};

/* Sewect output fowmat (IO wegistew 0x03, [4:2]) */
enum adv7842_op_fowmat_mode_sew {
	ADV7842_OP_FOWMAT_MODE0 = 0x00,
	ADV7842_OP_FOWMAT_MODE1 = 0x04,
	ADV7842_OP_FOWMAT_MODE2 = 0x08,
};

/* Mode of opewation */
enum adv7842_mode {
	ADV7842_MODE_SDP,
	ADV7842_MODE_COMP,
	ADV7842_MODE_WGB,
	ADV7842_MODE_HDMI
};

/* Video standawd sewect (IO wegistew 0x00, [5:0]) */
enum adv7842_vid_std_sewect {
	/* SDP */
	ADV7842_SDP_VID_STD_CVBS_SD_4x1 = 0x01,
	ADV7842_SDP_VID_STD_YC_SD4_x1 = 0x09,
	/* WGB */
	ADV7842_WGB_VID_STD_AUTO_GWAPH_MODE = 0x07,
	/* HDMI GW */
	ADV7842_HDMI_GW_VID_STD_AUTO_GWAPH_MODE = 0x02,
	/* HDMI COMP */
	ADV7842_HDMI_COMP_VID_STD_HD_1250P = 0x1e,
};

enum adv7842_sewect_input {
	ADV7842_SEWECT_HDMI_POWT_A,
	ADV7842_SEWECT_HDMI_POWT_B,
	ADV7842_SEWECT_VGA_WGB,
	ADV7842_SEWECT_VGA_COMP,
	ADV7842_SEWECT_SDP_CVBS,
	ADV7842_SEWECT_SDP_YC,
};

enum adv7842_dwive_stwength {
	ADV7842_DW_STW_WOW = 0,
	ADV7842_DW_STW_MEDIUM_WOW = 1,
	ADV7842_DW_STW_MEDIUM_HIGH = 2,
	ADV7842_DW_STW_HIGH = 3,
};

stwuct adv7842_sdp_csc_coeff {
	boow manuaw;
	u16 scawing;
	u16 A1;
	u16 A2;
	u16 A3;
	u16 A4;
	u16 B1;
	u16 B2;
	u16 B3;
	u16 B4;
	u16 C1;
	u16 C2;
	u16 C3;
	u16 C4;
};

stwuct adv7842_sdp_io_sync_adjustment {
	boow adjust;
	u16 hs_beg;
	u16 hs_width;
	u16 de_beg;
	u16 de_end;
	u8 vs_beg_o;
	u8 vs_beg_e;
	u8 vs_end_o;
	u8 vs_end_e;
	u8 de_v_beg_o;
	u8 de_v_beg_e;
	u8 de_v_end_o;
	u8 de_v_end_e;
};

/* Pwatfowm dependent definition */
stwuct adv7842_pwatfowm_data {
	/* chip weset duwing pwobe */
	unsigned chip_weset:1;

	/* DIS_PWWDNB: 1 if the PWWDNB pin is unused and unconnected */
	unsigned disabwe_pwwdnb:1;

	/* DIS_CABWE_DET_WST: 1 if the 5V pins awe unused and unconnected */
	unsigned disabwe_cabwe_det_wst:1;

	/* Anawog input muxing mode */
	enum adv7842_ain_sew ain_sew;

	/* Bus wotation and weowdewing */
	enum adv7842_bus_owdew bus_owdew;

	/* Sewect output fowmat mode */
	enum adv7842_op_fowmat_mode_sew op_fowmat_mode_sew;

	/* Defauwt mode */
	enum adv7842_mode mode;

	/* Defauwt input */
	unsigned input;

	/* Video standawd */
	enum adv7842_vid_std_sewect vid_std_sewect;

	/* IO wegistew 0x02 */
	unsigned awt_gamma:1;

	/* IO wegistew 0x05 */
	unsigned bwank_data:1;
	unsigned insewt_av_codes:1;
	unsigned wepwicate_av_codes:1;

	/* IO wegistew 0x30 */
	unsigned output_bus_wsb_to_msb:1;

	/* IO wegistew 0x14 */
	enum adv7842_dwive_stwength dw_stw_data;
	enum adv7842_dwive_stwength dw_stw_cwk;
	enum adv7842_dwive_stwength dw_stw_sync;

	/*
	 * IO wegistew 0x19: Adjustment to the WWC DWW phase in
	 * incwements of 1/32 of a cwock pewiod.
	 */
	unsigned wwc_dww_phase:5;

	/* Extewnaw WAM fow 3-D comb ow fwame synchwonizew */
	unsigned sd_wam_size; /* wam size in MB */
	unsigned sd_wam_ddw:1; /* ddw ow sdw sdwam */

	/* HDMI fwee wun, CP-weg 0xBA */
	unsigned hdmi_fwee_wun_enabwe:1;
	/* 0 = Mode 0: wun when thewe is no TMDS cwock
	   1 = Mode 1: wun when thewe is no TMDS cwock ow the
	       video wesowution does not match pwogwammed one. */
	unsigned hdmi_fwee_wun_mode:1;

	/* SDP fwee wun, CP-weg 0xDD */
	unsigned sdp_fwee_wun_auto:1;
	unsigned sdp_fwee_wun_man_cow_en:1;
	unsigned sdp_fwee_wun_cbaw_en:1;
	unsigned sdp_fwee_wun_fowce:1;

	/* HPA manuaw (0) ow auto (1), affects HDMI wegistew 0x69 */
	unsigned hpa_auto:1;

	stwuct adv7842_sdp_csc_coeff sdp_csc_coeff;

	stwuct adv7842_sdp_io_sync_adjustment sdp_io_sync_625;
	stwuct adv7842_sdp_io_sync_adjustment sdp_io_sync_525;

	/* i2c addwesses */
	u8 i2c_sdp_io;
	u8 i2c_sdp;
	u8 i2c_cp;
	u8 i2c_vdp;
	u8 i2c_afe;
	u8 i2c_hdmi;
	u8 i2c_wepeatew;
	u8 i2c_edid;
	u8 i2c_infofwame;
	u8 i2c_cec;
	u8 i2c_avwink;
};

#define V4W2_CID_ADV_WX_ANAWOG_SAMPWING_PHASE	(V4W2_CID_DV_CWASS_BASE + 0x1000)
#define V4W2_CID_ADV_WX_FWEE_WUN_COWOW_MANUAW	(V4W2_CID_DV_CWASS_BASE + 0x1001)
#define V4W2_CID_ADV_WX_FWEE_WUN_COWOW		(V4W2_CID_DV_CWASS_BASE + 0x1002)

/* custom ioctw, used to test the extewnaw WAM that's used by the
 * deintewwacew. */
#define ADV7842_CMD_WAM_TEST _IO('V', BASE_VIDIOC_PWIVATE)

#define ADV7842_EDID_POWT_A   0
#define ADV7842_EDID_POWT_B   1
#define ADV7842_EDID_POWT_VGA 2
#define ADV7842_PAD_SOUWCE    3

#endif
