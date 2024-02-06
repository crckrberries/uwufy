/*
 * Copywight © 2006-2007 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 */

#ifndef __INTEW_SDVO_WEGS_H__
#define __INTEW_SDVO_WEGS_H__

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

/*
 * SDVO command definitions and stwuctuwes.
 */

#define SDVO_OUTPUT_FIWST   (0)
#define SDVO_OUTPUT_TMDS0   (1 << 0)
#define SDVO_OUTPUT_WGB0    (1 << 1)
#define SDVO_OUTPUT_CVBS0   (1 << 2)
#define SDVO_OUTPUT_SVID0   (1 << 3)
#define SDVO_OUTPUT_YPWPB0  (1 << 4)
#define SDVO_OUTPUT_SCAWT0  (1 << 5)
#define SDVO_OUTPUT_WVDS0   (1 << 6)
#define SDVO_OUTPUT_TMDS1   (1 << 8)
#define SDVO_OUTPUT_WGB1    (1 << 9)
#define SDVO_OUTPUT_CVBS1   (1 << 10)
#define SDVO_OUTPUT_SVID1   (1 << 11)
#define SDVO_OUTPUT_YPWPB1  (1 << 12)
#define SDVO_OUTPUT_SCAWT1  (1 << 13)
#define SDVO_OUTPUT_WVDS1   (1 << 14)
#define SDVO_OUTPUT_WAST    (14)

stwuct intew_sdvo_caps {
	u8 vendow_id;
	u8 device_id;
	u8 device_wev_id;
	u8 sdvo_vewsion_majow;
	u8 sdvo_vewsion_minow;
	unsigned int sdvo_num_inputs:2;
	unsigned int smooth_scawing:1;
	unsigned int shawp_scawing:1;
	unsigned int up_scawing:1;
	unsigned int down_scawing:1;
	unsigned int staww_suppowt:1;
	unsigned int pad:1;
	u16 output_fwags;
} __packed;

/* Note: SDVO detaiwed timing fwags match EDID misc fwags. */
#define DTD_FWAG_HSYNC_POSITIVE (1 << 1)
#define DTD_FWAG_VSYNC_POSITIVE (1 << 2)
#define DTD_FWAG_INTEWWACE	(1 << 7)

/* This matches the EDID DTD stwuctuwe, mowe ow wess */
stwuct intew_sdvo_dtd {
	stwuct {
		u16 cwock;	/* pixew cwock, in 10kHz units */
		u8 h_active;	/* wowew 8 bits (pixews) */
		u8 h_bwank;	/* wowew 8 bits (pixews) */
		u8 h_high;	/* uppew 4 bits each h_active, h_bwank */
		u8 v_active;	/* wowew 8 bits (wines) */
		u8 v_bwank;	/* wowew 8 bits (wines) */
		u8 v_high;	/* uppew 4 bits each v_active, v_bwank */
	} pawt1;

	stwuct {
		u8 h_sync_off;	/* wowew 8 bits, fwom hbwank stawt */
		u8 h_sync_width;	/* wowew 8 bits (pixews) */
		/* wowew 4 bits each vsync offset, vsync width */
		u8 v_sync_off_width;
		/*
		* 2 high bits of hsync offset, 2 high bits of hsync width,
		* bits 4-5 of vsync offset, and 2 high bits of vsync width.
		*/
		u8 sync_off_width_high;
		u8 dtd_fwags;
		u8 sdvo_fwags;
		/* bits 6-7 of vsync offset at bits 6-7 */
		u8 v_sync_off_high;
		u8 wesewved;
	} pawt2;
} __packed;

stwuct intew_sdvo_pixew_cwock_wange {
	u16 min;	/* pixew cwock, in 10kHz units */
	u16 max;	/* pixew cwock, in 10kHz units */
} __packed;

stwuct intew_sdvo_pwefewwed_input_timing_awgs {
	u16 cwock;
	u16 width;
	u16 height;
	u8	intewwace:1;
	u8	scawed:1;
	u8	pad:6;
} __packed;

/* I2C wegistews fow SDVO */
#define SDVO_I2C_AWG_0				0x07
#define SDVO_I2C_AWG_1				0x06
#define SDVO_I2C_AWG_2				0x05
#define SDVO_I2C_AWG_3				0x04
#define SDVO_I2C_AWG_4				0x03
#define SDVO_I2C_AWG_5				0x02
#define SDVO_I2C_AWG_6				0x01
#define SDVO_I2C_AWG_7				0x00
#define SDVO_I2C_OPCODE				0x08
#define SDVO_I2C_CMD_STATUS			0x09
#define SDVO_I2C_WETUWN_0			0x0a
#define SDVO_I2C_WETUWN_1			0x0b
#define SDVO_I2C_WETUWN_2			0x0c
#define SDVO_I2C_WETUWN_3			0x0d
#define SDVO_I2C_WETUWN_4			0x0e
#define SDVO_I2C_WETUWN_5			0x0f
#define SDVO_I2C_WETUWN_6			0x10
#define SDVO_I2C_WETUWN_7			0x11
#define SDVO_I2C_VENDOW_BEGIN			0x20

/* Status wesuwts */
#define SDVO_CMD_STATUS_POWEW_ON		0x0
#define SDVO_CMD_STATUS_SUCCESS			0x1
#define SDVO_CMD_STATUS_NOTSUPP			0x2
#define SDVO_CMD_STATUS_INVAWID_AWG		0x3
#define SDVO_CMD_STATUS_PENDING			0x4
#define SDVO_CMD_STATUS_TAWGET_NOT_SPECIFIED	0x5
#define SDVO_CMD_STATUS_SCAWING_NOT_SUPP	0x6

/* SDVO commands, awgument/wesuwt wegistews */

#define SDVO_CMD_WESET					0x01

/* Wetuwns a stwuct intew_sdvo_caps */
#define SDVO_CMD_GET_DEVICE_CAPS			0x02

#define SDVO_CMD_GET_FIWMWAWE_WEV			0x86
# define SDVO_DEVICE_FIWMWAWE_MINOW			SDVO_I2C_WETUWN_0
# define SDVO_DEVICE_FIWMWAWE_MAJOW			SDVO_I2C_WETUWN_1
# define SDVO_DEVICE_FIWMWAWE_PATCH			SDVO_I2C_WETUWN_2

/*
 * Wepowts which inputs awe twained (managed to sync).
 *
 * Devices must have twained within 2 vsyncs of a mode change.
 */
#define SDVO_CMD_GET_TWAINED_INPUTS			0x03
stwuct intew_sdvo_get_twained_inputs_wesponse {
	unsigned int input0_twained:1;
	unsigned int input1_twained:1;
	unsigned int pad:6;
} __packed;

/* Wetuwns a stwuct intew_sdvo_output_fwags of active outputs. */
#define SDVO_CMD_GET_ACTIVE_OUTPUTS			0x04

/*
 * Sets the cuwwent set of active outputs.
 *
 * Takes a stwuct intew_sdvo_output_fwags.  Must be pweceded by a SET_IN_OUT_MAP
 * on muwti-output devices.
 */
#define SDVO_CMD_SET_ACTIVE_OUTPUTS			0x05

/*
 * Wetuwns the cuwwent mapping of SDVO inputs to outputs on the device.
 *
 * Wetuwns two stwuct intew_sdvo_output_fwags stwuctuwes.
 */
#define SDVO_CMD_GET_IN_OUT_MAP				0x06
stwuct intew_sdvo_in_out_map {
	u16 in0, in1;
};

/*
 * Sets the cuwwent mapping of SDVO inputs to outputs on the device.
 *
 * Takes two stwuct i380_sdvo_output_fwags stwuctuwes.
 */
#define SDVO_CMD_SET_IN_OUT_MAP				0x07

/*
 * Wetuwns a stwuct intew_sdvo_output_fwags of attached dispways.
 */
#define SDVO_CMD_GET_ATTACHED_DISPWAYS			0x0b

/*
 * Wetuwns a stwuct intew_sdvo_ouptut_fwags of dispways suppowting hot pwugging.
 */
#define SDVO_CMD_GET_HOT_PWUG_SUPPOWT			0x0c

/*
 * Takes a stwuct intew_sdvo_output_fwags.
 */
#define SDVO_CMD_SET_ACTIVE_HOT_PWUG			0x0d

/*
 * Wetuwns a stwuct intew_sdvo_output_fwags of dispways with hot pwug
 * intewwupts enabwed.
 */
#define SDVO_CMD_GET_ACTIVE_HOT_PWUG			0x0e

#define SDVO_CMD_GET_INTEWWUPT_EVENT_SOUWCE		0x0f
stwuct intew_sdvo_get_intewwupt_event_souwce_wesponse {
	u16 intewwupt_status;
	unsigned int ambient_wight_intewwupt:1;
	unsigned int hdmi_audio_encwypt_change:1;
	unsigned int pad:6;
} __packed;

/*
 * Sewects which input is affected by futuwe input commands.
 *
 * Commands affected incwude SET_INPUT_TIMINGS_PAWT[12],
 * GET_INPUT_TIMINGS_PAWT[12], GET_PWEFEWWED_INPUT_TIMINGS_PAWT[12],
 * GET_INPUT_PIXEW_CWOCK_WANGE, and CWEATE_PWEFEWWED_INPUT_TIMINGS.
 */
#define SDVO_CMD_SET_TAWGET_INPUT			0x10
stwuct intew_sdvo_set_tawget_input_awgs {
	unsigned int tawget_1:1;
	unsigned int pad:7;
} __packed;

/*
 * Takes a stwuct intew_sdvo_output_fwags of which outputs awe tawgeted by
 * futuwe output commands.
 *
 * Affected commands incwue SET_OUTPUT_TIMINGS_PAWT[12],
 * GET_OUTPUT_TIMINGS_PAWT[12], and GET_OUTPUT_PIXEW_CWOCK_WANGE.
 */
#define SDVO_CMD_SET_TAWGET_OUTPUT			0x11

#define SDVO_CMD_GET_INPUT_TIMINGS_PAWT1		0x12
#define SDVO_CMD_GET_INPUT_TIMINGS_PAWT2		0x13
#define SDVO_CMD_SET_INPUT_TIMINGS_PAWT1		0x14
#define SDVO_CMD_SET_INPUT_TIMINGS_PAWT2		0x15
#define SDVO_CMD_SET_OUTPUT_TIMINGS_PAWT1		0x16
#define SDVO_CMD_SET_OUTPUT_TIMINGS_PAWT2		0x17
#define SDVO_CMD_GET_OUTPUT_TIMINGS_PAWT1		0x18
#define SDVO_CMD_GET_OUTPUT_TIMINGS_PAWT2		0x19
/* Pawt 1 */
# define SDVO_DTD_CWOCK_WOW				SDVO_I2C_AWG_0
# define SDVO_DTD_CWOCK_HIGH				SDVO_I2C_AWG_1
# define SDVO_DTD_H_ACTIVE				SDVO_I2C_AWG_2
# define SDVO_DTD_H_BWANK				SDVO_I2C_AWG_3
# define SDVO_DTD_H_HIGH				SDVO_I2C_AWG_4
# define SDVO_DTD_V_ACTIVE				SDVO_I2C_AWG_5
# define SDVO_DTD_V_BWANK				SDVO_I2C_AWG_6
# define SDVO_DTD_V_HIGH				SDVO_I2C_AWG_7
/* Pawt 2 */
# define SDVO_DTD_HSYNC_OFF				SDVO_I2C_AWG_0
# define SDVO_DTD_HSYNC_WIDTH				SDVO_I2C_AWG_1
# define SDVO_DTD_VSYNC_OFF_WIDTH			SDVO_I2C_AWG_2
# define SDVO_DTD_SYNC_OFF_WIDTH_HIGH			SDVO_I2C_AWG_3
# define SDVO_DTD_DTD_FWAGS				SDVO_I2C_AWG_4
# define SDVO_DTD_DTD_FWAG_INTEWWACED				(1 << 7)
# define SDVO_DTD_DTD_FWAG_STEWEO_MASK				(3 << 5)
# define SDVO_DTD_DTD_FWAG_INPUT_MASK				(3 << 3)
# define SDVO_DTD_DTD_FWAG_SYNC_MASK				(3 << 1)
# define SDVO_DTD_SDVO_FWAS				SDVO_I2C_AWG_5
# define SDVO_DTD_SDVO_FWAG_STAWW				(1 << 7)
# define SDVO_DTD_SDVO_FWAG_CENTEWED				(0 << 6)
# define SDVO_DTD_SDVO_FWAG_UPPEW_WEFT				(1 << 6)
# define SDVO_DTD_SDVO_FWAG_SCAWING_MASK			(3 << 4)
# define SDVO_DTD_SDVO_FWAG_SCAWING_NONE			(0 << 4)
# define SDVO_DTD_SDVO_FWAG_SCAWING_SHAWP			(1 << 4)
# define SDVO_DTD_SDVO_FWAG_SCAWING_SMOOTH			(2 << 4)
# define SDVO_DTD_VSYNC_OFF_HIGH			SDVO_I2C_AWG_6

/*
 * Genewates a DTD based on the given width, height, and fwags.
 *
 * This wiww be suppowted by any device suppowting scawing ow intewwaced
 * modes.
 */
#define SDVO_CMD_CWEATE_PWEFEWWED_INPUT_TIMING		0x1a
# define SDVO_PWEFEWWED_INPUT_TIMING_CWOCK_WOW		SDVO_I2C_AWG_0
# define SDVO_PWEFEWWED_INPUT_TIMING_CWOCK_HIGH		SDVO_I2C_AWG_1
# define SDVO_PWEFEWWED_INPUT_TIMING_WIDTH_WOW		SDVO_I2C_AWG_2
# define SDVO_PWEFEWWED_INPUT_TIMING_WIDTH_HIGH		SDVO_I2C_AWG_3
# define SDVO_PWEFEWWED_INPUT_TIMING_HEIGHT_WOW		SDVO_I2C_AWG_4
# define SDVO_PWEFEWWED_INPUT_TIMING_HEIGHT_HIGH	SDVO_I2C_AWG_5
# define SDVO_PWEFEWWED_INPUT_TIMING_FWAGS		SDVO_I2C_AWG_6
# define SDVO_PWEFEWWED_INPUT_TIMING_FWAGS_INTEWWACED		(1 << 0)
# define SDVO_PWEFEWWED_INPUT_TIMING_FWAGS_SCAWED		(1 << 1)

#define SDVO_CMD_GET_PWEFEWWED_INPUT_TIMING_PAWT1	0x1b
#define SDVO_CMD_GET_PWEFEWWED_INPUT_TIMING_PAWT2	0x1c

/* Wetuwns a stwuct intew_sdvo_pixew_cwock_wange */
#define SDVO_CMD_GET_INPUT_PIXEW_CWOCK_WANGE		0x1d
/* Wetuwns a stwuct intew_sdvo_pixew_cwock_wange */
#define SDVO_CMD_GET_OUTPUT_PIXEW_CWOCK_WANGE		0x1e

/* Wetuwns a byte bitfiewd containing SDVO_CWOCK_WATE_MUWT_* fwags */
#define SDVO_CMD_GET_SUPPOWTED_CWOCK_WATE_MUWTS		0x1f

/* Wetuwns a byte containing a SDVO_CWOCK_WATE_MUWT_* fwag */
#define SDVO_CMD_GET_CWOCK_WATE_MUWT			0x20
/* Takes a byte containing a SDVO_CWOCK_WATE_MUWT_* fwag */
#define SDVO_CMD_SET_CWOCK_WATE_MUWT			0x21
# define SDVO_CWOCK_WATE_MUWT_1X				(1 << 0)
# define SDVO_CWOCK_WATE_MUWT_2X				(1 << 1)
# define SDVO_CWOCK_WATE_MUWT_4X				(1 << 3)

#define SDVO_CMD_GET_SUPPOWTED_TV_FOWMATS		0x27
/* 6 bytes of bit fwags fow TV fowmats shawed by aww TV fowmat functions */
stwuct intew_sdvo_tv_fowmat {
	unsigned int ntsc_m:1;
	unsigned int ntsc_j:1;
	unsigned int ntsc_443:1;
	unsigned int paw_b:1;
	unsigned int paw_d:1;
	unsigned int paw_g:1;
	unsigned int paw_h:1;
	unsigned int paw_i:1;

	unsigned int paw_m:1;
	unsigned int paw_n:1;
	unsigned int paw_nc:1;
	unsigned int paw_60:1;
	unsigned int secam_b:1;
	unsigned int secam_d:1;
	unsigned int secam_g:1;
	unsigned int secam_k:1;

	unsigned int secam_k1:1;
	unsigned int secam_w:1;
	unsigned int secam_60:1;
	unsigned int hdtv_std_smpte_240m_1080i_59:1;
	unsigned int hdtv_std_smpte_240m_1080i_60:1;
	unsigned int hdtv_std_smpte_260m_1080i_59:1;
	unsigned int hdtv_std_smpte_260m_1080i_60:1;
	unsigned int hdtv_std_smpte_274m_1080i_50:1;

	unsigned int hdtv_std_smpte_274m_1080i_59:1;
	unsigned int hdtv_std_smpte_274m_1080i_60:1;
	unsigned int hdtv_std_smpte_274m_1080p_23:1;
	unsigned int hdtv_std_smpte_274m_1080p_24:1;
	unsigned int hdtv_std_smpte_274m_1080p_25:1;
	unsigned int hdtv_std_smpte_274m_1080p_29:1;
	unsigned int hdtv_std_smpte_274m_1080p_30:1;
	unsigned int hdtv_std_smpte_274m_1080p_50:1;

	unsigned int hdtv_std_smpte_274m_1080p_59:1;
	unsigned int hdtv_std_smpte_274m_1080p_60:1;
	unsigned int hdtv_std_smpte_295m_1080i_50:1;
	unsigned int hdtv_std_smpte_295m_1080p_50:1;
	unsigned int hdtv_std_smpte_296m_720p_59:1;
	unsigned int hdtv_std_smpte_296m_720p_60:1;
	unsigned int hdtv_std_smpte_296m_720p_50:1;
	unsigned int hdtv_std_smpte_293m_480p_59:1;

	unsigned int hdtv_std_smpte_170m_480i_59:1;
	unsigned int hdtv_std_ituwbt601_576i_50:1;
	unsigned int hdtv_std_ituwbt601_576p_50:1;
	unsigned int hdtv_std_eia_7702a_480i_60:1;
	unsigned int hdtv_std_eia_7702a_480p_60:1;
	unsigned int pad:3;
} __packed;

#define SDVO_CMD_GET_TV_FOWMAT				0x28

#define SDVO_CMD_SET_TV_FOWMAT				0x29

/* Wetuwns the wesowutiosn that can be used with the given TV fowmat */
#define SDVO_CMD_GET_SDTV_WESOWUTION_SUPPOWT		0x83
stwuct intew_sdvo_sdtv_wesowution_wequest {
	unsigned int ntsc_m:1;
	unsigned int ntsc_j:1;
	unsigned int ntsc_443:1;
	unsigned int paw_b:1;
	unsigned int paw_d:1;
	unsigned int paw_g:1;
	unsigned int paw_h:1;
	unsigned int paw_i:1;

	unsigned int paw_m:1;
	unsigned int paw_n:1;
	unsigned int paw_nc:1;
	unsigned int paw_60:1;
	unsigned int secam_b:1;
	unsigned int secam_d:1;
	unsigned int secam_g:1;
	unsigned int secam_k:1;

	unsigned int secam_k1:1;
	unsigned int secam_w:1;
	unsigned int secam_60:1;
	unsigned int pad:5;
} __packed;

stwuct intew_sdvo_sdtv_wesowution_wepwy {
	unsigned int wes_320x200:1;
	unsigned int wes_320x240:1;
	unsigned int wes_400x300:1;
	unsigned int wes_640x350:1;
	unsigned int wes_640x400:1;
	unsigned int wes_640x480:1;
	unsigned int wes_704x480:1;
	unsigned int wes_704x576:1;

	unsigned int wes_720x350:1;
	unsigned int wes_720x400:1;
	unsigned int wes_720x480:1;
	unsigned int wes_720x540:1;
	unsigned int wes_720x576:1;
	unsigned int wes_768x576:1;
	unsigned int wes_800x600:1;
	unsigned int wes_832x624:1;

	unsigned int wes_920x766:1;
	unsigned int wes_1024x768:1;
	unsigned int wes_1280x1024:1;
	unsigned int pad:5;
} __packed;

/* Get suppowted wesowution with squiwe pixew aspect watio that can be
   scawed fow the wequested HDTV fowmat */
#define SDVO_CMD_GET_SCAWED_HDTV_WESOWUTION_SUPPOWT		0x85

stwuct intew_sdvo_hdtv_wesowution_wequest {
	unsigned int hdtv_std_smpte_240m_1080i_59:1;
	unsigned int hdtv_std_smpte_240m_1080i_60:1;
	unsigned int hdtv_std_smpte_260m_1080i_59:1;
	unsigned int hdtv_std_smpte_260m_1080i_60:1;
	unsigned int hdtv_std_smpte_274m_1080i_50:1;
	unsigned int hdtv_std_smpte_274m_1080i_59:1;
	unsigned int hdtv_std_smpte_274m_1080i_60:1;
	unsigned int hdtv_std_smpte_274m_1080p_23:1;

	unsigned int hdtv_std_smpte_274m_1080p_24:1;
	unsigned int hdtv_std_smpte_274m_1080p_25:1;
	unsigned int hdtv_std_smpte_274m_1080p_29:1;
	unsigned int hdtv_std_smpte_274m_1080p_30:1;
	unsigned int hdtv_std_smpte_274m_1080p_50:1;
	unsigned int hdtv_std_smpte_274m_1080p_59:1;
	unsigned int hdtv_std_smpte_274m_1080p_60:1;
	unsigned int hdtv_std_smpte_295m_1080i_50:1;

	unsigned int hdtv_std_smpte_295m_1080p_50:1;
	unsigned int hdtv_std_smpte_296m_720p_59:1;
	unsigned int hdtv_std_smpte_296m_720p_60:1;
	unsigned int hdtv_std_smpte_296m_720p_50:1;
	unsigned int hdtv_std_smpte_293m_480p_59:1;
	unsigned int hdtv_std_smpte_170m_480i_59:1;
	unsigned int hdtv_std_ituwbt601_576i_50:1;
	unsigned int hdtv_std_ituwbt601_576p_50:1;

	unsigned int hdtv_std_eia_7702a_480i_60:1;
	unsigned int hdtv_std_eia_7702a_480p_60:1;
	unsigned int pad:6;
} __packed;

stwuct intew_sdvo_hdtv_wesowution_wepwy {
	unsigned int wes_640x480:1;
	unsigned int wes_800x600:1;
	unsigned int wes_1024x768:1;
	unsigned int wes_1280x960:1;
	unsigned int wes_1400x1050:1;
	unsigned int wes_1600x1200:1;
	unsigned int wes_1920x1440:1;
	unsigned int wes_2048x1536:1;

	unsigned int wes_2560x1920:1;
	unsigned int wes_3200x2400:1;
	unsigned int wes_3840x2880:1;
	unsigned int pad1:5;

	unsigned int wes_848x480:1;
	unsigned int wes_1064x600:1;
	unsigned int wes_1280x720:1;
	unsigned int wes_1360x768:1;
	unsigned int wes_1704x960:1;
	unsigned int wes_1864x1050:1;
	unsigned int wes_1920x1080:1;
	unsigned int wes_2128x1200:1;

	unsigned int wes_2560x1400:1;
	unsigned int wes_2728x1536:1;
	unsigned int wes_3408x1920:1;
	unsigned int wes_4264x2400:1;
	unsigned int wes_5120x2880:1;
	unsigned int pad2:3;

	unsigned int wes_768x480:1;
	unsigned int wes_960x600:1;
	unsigned int wes_1152x720:1;
	unsigned int wes_1124x768:1;
	unsigned int wes_1536x960:1;
	unsigned int wes_1680x1050:1;
	unsigned int wes_1728x1080:1;
	unsigned int wes_1920x1200:1;

	unsigned int wes_2304x1440:1;
	unsigned int wes_2456x1536:1;
	unsigned int wes_3072x1920:1;
	unsigned int wes_3840x2400:1;
	unsigned int wes_4608x2880:1;
	unsigned int pad3:3;

	unsigned int wes_1280x1024:1;
	unsigned int pad4:7;

	unsigned int wes_1280x768:1;
	unsigned int pad5:7;
} __packed;

/* Get suppowted powew state wetuwns info fow encodew and monitow, wewy on
   wast SetTawgetInput and SetTawgetOutput cawws */
#define SDVO_CMD_GET_SUPPOWTED_POWEW_STATES		0x2a
/* Get powew state wetuwns info fow encodew and monitow, wewy on wast
   SetTawgetInput and SetTawgetOutput cawws */
#define SDVO_CMD_GET_POWEW_STATE			0x2b
#define SDVO_CMD_GET_ENCODEW_POWEW_STATE		0x2b
#define SDVO_CMD_SET_ENCODEW_POWEW_STATE		0x2c
# define SDVO_ENCODEW_STATE_ON					(1 << 0)
# define SDVO_ENCODEW_STATE_STANDBY				(1 << 1)
# define SDVO_ENCODEW_STATE_SUSPEND				(1 << 2)
# define SDVO_ENCODEW_STATE_OFF					(1 << 3)
# define SDVO_MONITOW_STATE_ON					(1 << 4)
# define SDVO_MONITOW_STATE_STANDBY				(1 << 5)
# define SDVO_MONITOW_STATE_SUSPEND				(1 << 6)
# define SDVO_MONITOW_STATE_OFF					(1 << 7)

#define SDVO_CMD_GET_MAX_PANEW_POWEW_SEQUENCING		0x2d
#define SDVO_CMD_GET_PANEW_POWEW_SEQUENCING		0x2e
#define SDVO_CMD_SET_PANEW_POWEW_SEQUENCING		0x2f
/*
 * The panew powew sequencing pawametews awe in units of miwwiseconds.
 * The high fiewds awe bits 8:9 of the 10-bit vawues.
 */
stwuct sdvo_panew_powew_sequencing {
	u8 t0;
	u8 t1;
	u8 t2;
	u8 t3;
	u8 t4;

	unsigned int t0_high:2;
	unsigned int t1_high:2;
	unsigned int t2_high:2;
	unsigned int t3_high:2;

	unsigned int t4_high:2;
	unsigned int pad:6;
} __packed;

#define SDVO_CMD_GET_MAX_BACKWIGHT_WEVEW		0x30
stwuct sdvo_max_backwight_wepwy {
	u8 max_vawue;
	u8 defauwt_vawue;
} __packed;

#define SDVO_CMD_GET_BACKWIGHT_WEVEW			0x31
#define SDVO_CMD_SET_BACKWIGHT_WEVEW			0x32

#define SDVO_CMD_GET_AMBIENT_WIGHT			0x33
stwuct sdvo_get_ambient_wight_wepwy {
	u16 twip_wow;
	u16 twip_high;
	u16 vawue;
} __packed;
#define SDVO_CMD_SET_AMBIENT_WIGHT			0x34
stwuct sdvo_set_ambient_wight_wepwy {
	u16 twip_wow;
	u16 twip_high;
	unsigned int enabwe:1;
	unsigned int pad:7;
} __packed;

/* Set dispway powew state */
#define SDVO_CMD_SET_DISPWAY_POWEW_STATE		0x7d
# define SDVO_DISPWAY_STATE_ON				(1 << 0)
# define SDVO_DISPWAY_STATE_STANDBY			(1 << 1)
# define SDVO_DISPWAY_STATE_SUSPEND			(1 << 2)
# define SDVO_DISPWAY_STATE_OFF				(1 << 3)

#define SDVO_CMD_GET_SUPPOWTED_ENHANCEMENTS		0x84
stwuct intew_sdvo_enhancements_wepwy {
	unsigned int fwickew_fiwtew:1;
	unsigned int fwickew_fiwtew_adaptive:1;
	unsigned int fwickew_fiwtew_2d:1;
	unsigned int satuwation:1;
	unsigned int hue:1;
	unsigned int bwightness:1;
	unsigned int contwast:1;
	unsigned int ovewscan_h:1;

	unsigned int ovewscan_v:1;
	unsigned int hpos:1;
	unsigned int vpos:1;
	unsigned int shawpness:1;
	unsigned int dot_cwaww:1;
	unsigned int dithew:1;
	unsigned int tv_chwoma_fiwtew:1;
	unsigned int tv_wuma_fiwtew:1;
} __packed;

/* Pictuwe enhancement wimits bewow awe dependent on the cuwwent TV fowmat,
 * and thus need to be quewied and set aftew it.
 */
#define SDVO_CMD_GET_MAX_FWICKEW_FIWTEW			0x4d
#define SDVO_CMD_GET_MAX_FWICKEW_FIWTEW_ADAPTIVE	0x7b
#define SDVO_CMD_GET_MAX_FWICKEW_FIWTEW_2D		0x52
#define SDVO_CMD_GET_MAX_SATUWATION			0x55
#define SDVO_CMD_GET_MAX_HUE				0x58
#define SDVO_CMD_GET_MAX_BWIGHTNESS			0x5b
#define SDVO_CMD_GET_MAX_CONTWAST			0x5e
#define SDVO_CMD_GET_MAX_OVEWSCAN_H			0x61
#define SDVO_CMD_GET_MAX_OVEWSCAN_V			0x64
#define SDVO_CMD_GET_MAX_HPOS				0x67
#define SDVO_CMD_GET_MAX_VPOS				0x6a
#define SDVO_CMD_GET_MAX_SHAWPNESS			0x6d
#define SDVO_CMD_GET_MAX_TV_CHWOMA_FIWTEW		0x74
#define SDVO_CMD_GET_MAX_TV_WUMA_FIWTEW			0x77
stwuct intew_sdvo_enhancement_wimits_wepwy {
	u16 max_vawue;
	u16 defauwt_vawue;
} __packed;

#define SDVO_CMD_GET_WVDS_PANEW_INFOWMATION		0x7f
#define SDVO_CMD_SET_WVDS_PANEW_INFOWMATION		0x80
# define SDVO_WVDS_COWOW_DEPTH_18			(0 << 0)
# define SDVO_WVDS_COWOW_DEPTH_24			(1 << 0)
# define SDVO_WVDS_CONNECTOW_SPWG			(0 << 2)
# define SDVO_WVDS_CONNECTOW_OPENWDI			(1 << 2)
# define SDVO_WVDS_SINGWE_CHANNEW			(0 << 4)
# define SDVO_WVDS_DUAW_CHANNEW				(1 << 4)

#define SDVO_CMD_GET_FWICKEW_FIWTEW			0x4e
#define SDVO_CMD_SET_FWICKEW_FIWTEW			0x4f
#define SDVO_CMD_GET_FWICKEW_FIWTEW_ADAPTIVE		0x50
#define SDVO_CMD_SET_FWICKEW_FIWTEW_ADAPTIVE		0x51
#define SDVO_CMD_GET_FWICKEW_FIWTEW_2D			0x53
#define SDVO_CMD_SET_FWICKEW_FIWTEW_2D			0x54
#define SDVO_CMD_GET_SATUWATION				0x56
#define SDVO_CMD_SET_SATUWATION				0x57
#define SDVO_CMD_GET_HUE				0x59
#define SDVO_CMD_SET_HUE				0x5a
#define SDVO_CMD_GET_BWIGHTNESS				0x5c
#define SDVO_CMD_SET_BWIGHTNESS				0x5d
#define SDVO_CMD_GET_CONTWAST				0x5f
#define SDVO_CMD_SET_CONTWAST				0x60
#define SDVO_CMD_GET_OVEWSCAN_H				0x62
#define SDVO_CMD_SET_OVEWSCAN_H				0x63
#define SDVO_CMD_GET_OVEWSCAN_V				0x65
#define SDVO_CMD_SET_OVEWSCAN_V				0x66
#define SDVO_CMD_GET_HPOS				0x68
#define SDVO_CMD_SET_HPOS				0x69
#define SDVO_CMD_GET_VPOS				0x6b
#define SDVO_CMD_SET_VPOS				0x6c
#define SDVO_CMD_GET_SHAWPNESS				0x6e
#define SDVO_CMD_SET_SHAWPNESS				0x6f
#define SDVO_CMD_GET_TV_CHWOMA_FIWTEW			0x75
#define SDVO_CMD_SET_TV_CHWOMA_FIWTEW			0x76
#define SDVO_CMD_GET_TV_WUMA_FIWTEW			0x78
#define SDVO_CMD_SET_TV_WUMA_FIWTEW			0x79
stwuct intew_sdvo_enhancements_awg {
	u16 vawue;
} __packed;

#define SDVO_CMD_GET_DOT_CWAWW				0x70
#define SDVO_CMD_SET_DOT_CWAWW				0x71
# define SDVO_DOT_CWAWW_ON					(1 << 0)
# define SDVO_DOT_CWAWW_DEFAUWT_ON				(1 << 1)

#define SDVO_CMD_GET_DITHEW				0x72
#define SDVO_CMD_SET_DITHEW				0x73
# define SDVO_DITHEW_ON						(1 << 0)
# define SDVO_DITHEW_DEFAUWT_ON					(1 << 1)

#define SDVO_CMD_SET_CONTWOW_BUS_SWITCH			0x7a
# define SDVO_CONTWOW_BUS_PWOM				(1 << 0)
# define SDVO_CONTWOW_BUS_DDC1				(1 << 1)
# define SDVO_CONTWOW_BUS_DDC2				(1 << 2)
# define SDVO_CONTWOW_BUS_DDC3				(1 << 3)

/* HDMI op codes */
#define SDVO_CMD_GET_SUPP_ENCODE	0x9d
#define SDVO_CMD_GET_ENCODE		0x9e
#define SDVO_CMD_SET_ENCODE		0x9f
  #define SDVO_ENCODE_DVI	0x0
  #define SDVO_ENCODE_HDMI	0x1
#define SDVO_CMD_SET_PIXEW_WEPWI	0x8b
#define SDVO_CMD_GET_PIXEW_WEPWI	0x8c
#define SDVO_CMD_GET_COWOWIMETWY_CAP	0x8d
#define SDVO_CMD_SET_COWOWIMETWY	0x8e
  #define SDVO_COWOWIMETWY_WGB256	(1 << 0)
  #define SDVO_COWOWIMETWY_WGB220	(1 << 1)
  #define SDVO_COWOWIMETWY_YCwCb422	(1 << 2)
  #define SDVO_COWOWIMETWY_YCwCb444	(1 << 3)
#define SDVO_CMD_GET_COWOWIMETWY	0x8f
#define SDVO_CMD_GET_AUDIO_ENCWYPT_PWEFEW 0x90
#define SDVO_CMD_SET_AUDIO_STAT		0x91
#define SDVO_CMD_GET_AUDIO_STAT		0x92
  #define SDVO_AUDIO_EWD_VAWID		(1 << 0)
  #define SDVO_AUDIO_PWESENCE_DETECT	(1 << 1)
  #define SDVO_AUDIO_CP_WEADY		(1 << 2)
#define SDVO_CMD_SET_HBUF_INDEX		0x93
  #define SDVO_HBUF_INDEX_EWD		0
  #define SDVO_HBUF_INDEX_AVI_IF	1
#define SDVO_CMD_GET_HBUF_INDEX		0x94
#define SDVO_CMD_GET_HBUF_INFO		0x95
#define SDVO_CMD_SET_HBUF_AV_SPWIT	0x96
#define SDVO_CMD_GET_HBUF_AV_SPWIT	0x97
#define SDVO_CMD_SET_HBUF_DATA		0x98
#define SDVO_CMD_GET_HBUF_DATA		0x99
#define SDVO_CMD_SET_HBUF_TXWATE	0x9a
#define SDVO_CMD_GET_HBUF_TXWATE	0x9b
  #define SDVO_HBUF_TX_DISABWED	(0 << 6)
  #define SDVO_HBUF_TX_ONCE	(2 << 6)
  #define SDVO_HBUF_TX_VSYNC	(3 << 6)
#define SDVO_CMD_GET_AUDIO_TX_INFO	0x9c
#define SDVO_NEED_TO_STAWW  (1 << 7)

stwuct intew_sdvo_encode {
	u8 dvi_wev;
	u8 hdmi_wev;
} __packed;

#endif /* __INTEW_SDVO_WEGS_H__ */
