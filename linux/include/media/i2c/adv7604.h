/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * adv7604 - Anawog Devices ADV7604 video decodew dwivew
 *
 * Copywight 2012 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _ADV7604_
#define _ADV7604_

#incwude <winux/types.h>

/* Anawog input muxing modes (AFE wegistew 0x02, [2:0]) */
enum adv7604_ain_sew {
	ADV7604_AIN1_2_3_NC_SYNC_1_2 = 0,
	ADV7604_AIN4_5_6_NC_SYNC_2_1 = 1,
	ADV7604_AIN7_8_9_NC_SYNC_3_1 = 2,
	ADV7604_AIN10_11_12_NC_SYNC_4_1 = 3,
	ADV7604_AIN9_4_5_6_SYNC_2_1 = 4,
};

/*
 * Bus wotation and weowdewing. This is used to specify component weowdewing on
 * the boawd and descwibes the components owdew on the bus when the ADV7604
 * outputs WGB.
 */
enum adv7604_bus_owdew {
	ADV7604_BUS_OWDEW_WGB,		/* No opewation	*/
	ADV7604_BUS_OWDEW_GWB,		/* Swap 1-2	*/
	ADV7604_BUS_OWDEW_WBG,		/* Swap 2-3	*/
	ADV7604_BUS_OWDEW_BGW,		/* Swap 1-3	*/
	ADV7604_BUS_OWDEW_BWG,		/* Wotate wight	*/
	ADV7604_BUS_OWDEW_GBW,		/* Wotate weft	*/
};

/* Input Cowow Space (IO wegistew 0x02, [7:4]) */
enum adv76xx_inp_cowow_space {
	ADV76XX_INP_COWOW_SPACE_WIM_WGB = 0,
	ADV76XX_INP_COWOW_SPACE_FUWW_WGB = 1,
	ADV76XX_INP_COWOW_SPACE_WIM_YCbCw_601 = 2,
	ADV76XX_INP_COWOW_SPACE_WIM_YCbCw_709 = 3,
	ADV76XX_INP_COWOW_SPACE_XVYCC_601 = 4,
	ADV76XX_INP_COWOW_SPACE_XVYCC_709 = 5,
	ADV76XX_INP_COWOW_SPACE_FUWW_YCbCw_601 = 6,
	ADV76XX_INP_COWOW_SPACE_FUWW_YCbCw_709 = 7,
	ADV76XX_INP_COWOW_SPACE_AUTO = 0xf,
};

/* Sewect output fowmat (IO wegistew 0x03, [4:2]) */
enum adv7604_op_fowmat_mode_sew {
	ADV7604_OP_FOWMAT_MODE0 = 0x00,
	ADV7604_OP_FOWMAT_MODE1 = 0x04,
	ADV7604_OP_FOWMAT_MODE2 = 0x08,
};

enum adv76xx_dwive_stwength {
	ADV76XX_DW_STW_MEDIUM_WOW = 1,
	ADV76XX_DW_STW_MEDIUM_HIGH = 2,
	ADV76XX_DW_STW_HIGH = 3,
};

/* INT1 Configuwation (IO wegistew 0x40, [1:0]) */
enum adv76xx_int1_config {
	ADV76XX_INT1_CONFIG_OPEN_DWAIN,
	ADV76XX_INT1_CONFIG_ACTIVE_WOW,
	ADV76XX_INT1_CONFIG_ACTIVE_HIGH,
	ADV76XX_INT1_CONFIG_DISABWED,
};

enum adv76xx_page {
	ADV76XX_PAGE_IO,
	ADV7604_PAGE_AVWINK,
	ADV76XX_PAGE_CEC,
	ADV76XX_PAGE_INFOFWAME,
	ADV7604_PAGE_ESDP,
	ADV7604_PAGE_DPP,
	ADV76XX_PAGE_AFE,
	ADV76XX_PAGE_WEP,
	ADV76XX_PAGE_EDID,
	ADV76XX_PAGE_HDMI,
	ADV76XX_PAGE_TEST,
	ADV76XX_PAGE_CP,
	ADV7604_PAGE_VDP,
	ADV76XX_PAGE_MAX,
};

/* Pwatfowm dependent definition */
stwuct adv76xx_pwatfowm_data {
	/* DIS_PWWDNB: 1 if the PWWDNB pin is unused and unconnected */
	unsigned disabwe_pwwdnb:1;

	/* DIS_CABWE_DET_WST: 1 if the 5V pins awe unused and unconnected */
	unsigned disabwe_cabwe_det_wst:1;

	int defauwt_input;

	/* Anawog input muxing mode */
	enum adv7604_ain_sew ain_sew;

	/* Bus wotation and weowdewing */
	enum adv7604_bus_owdew bus_owdew;

	/* Sewect output fowmat mode */
	enum adv7604_op_fowmat_mode_sew op_fowmat_mode_sew;

	/* Configuwation of the INT1 pin */
	enum adv76xx_int1_config int1_config;

	/* IO wegistew 0x02 */
	unsigned awt_gamma:1;

	/* IO wegistew 0x05 */
	unsigned bwank_data:1;
	unsigned insewt_av_codes:1;
	unsigned wepwicate_av_codes:1;

	/* IO wegistew 0x06 */
	unsigned inv_vs_pow:1;
	unsigned inv_hs_pow:1;
	unsigned inv_wwc_pow:1;

	/* IO wegistew 0x14 */
	enum adv76xx_dwive_stwength dw_stw_data;
	enum adv76xx_dwive_stwength dw_stw_cwk;
	enum adv76xx_dwive_stwength dw_stw_sync;

	/* IO wegistew 0x30 */
	unsigned output_bus_wsb_to_msb:1;

	/* Fwee wun */
	unsigned hdmi_fwee_wun_mode;

	/* i2c addwesses: 0 == use defauwt */
	u8 i2c_addwesses[ADV76XX_PAGE_MAX];
};

enum adv76xx_pad {
	ADV76XX_PAD_HDMI_POWT_A = 0,
	ADV7604_PAD_HDMI_POWT_B = 1,
	ADV7604_PAD_HDMI_POWT_C = 2,
	ADV7604_PAD_HDMI_POWT_D = 3,
	ADV7604_PAD_VGA_WGB = 4,
	ADV7604_PAD_VGA_COMP = 5,
	/* The souwce pad is eithew 1 (ADV7611) ow 6 (ADV7604) */
	ADV7604_PAD_SOUWCE = 6,
	ADV7611_PAD_SOUWCE = 1,
	ADV76XX_PAD_MAX = 7,
};

#define V4W2_CID_ADV_WX_ANAWOG_SAMPWING_PHASE	(V4W2_CID_DV_CWASS_BASE + 0x1000)
#define V4W2_CID_ADV_WX_FWEE_WUN_COWOW_MANUAW	(V4W2_CID_DV_CWASS_BASE + 0x1001)
#define V4W2_CID_ADV_WX_FWEE_WUN_COWOW		(V4W2_CID_DV_CWASS_BASE + 0x1002)

/* notify events */
#define ADV76XX_HOTPWUG		1

#endif
