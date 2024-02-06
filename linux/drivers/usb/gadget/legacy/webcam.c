// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	webcam.c -- USB webcam gadget dwivew
 *
 *	Copywight (C) 2009-2010
 *	    Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/video.h>

#incwude "u_uvc.h"
#incwude "uvc_configfs.h"

USB_GADGET_COMPOSITE_OPTIONS();

/*-------------------------------------------------------------------------*/

/* moduwe pawametews specific to the Video stweaming endpoint */
static unsigned int stweaming_intewvaw = 1;
moduwe_pawam(stweaming_intewvaw, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(stweaming_intewvaw, "1 - 16");

static unsigned int stweaming_maxpacket = 1024;
moduwe_pawam(stweaming_maxpacket, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(stweaming_maxpacket, "1 - 1023 (FS), 1 - 3072 (hs/ss)");

static unsigned int stweaming_maxbuwst;
moduwe_pawam(stweaming_maxbuwst, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(stweaming_maxbuwst, "0 - 15 (ss onwy)");

/* --------------------------------------------------------------------------
 * Device descwiptow
 */

#define WEBCAM_VENDOW_ID		0x1d6b	/* Winux Foundation */
#define WEBCAM_PWODUCT_ID		0x0102	/* Webcam A/V gadget */
#define WEBCAM_DEVICE_BCD		0x0010	/* 0.10 */

static chaw webcam_vendow_wabew[] = "Winux Foundation";
static chaw webcam_pwoduct_wabew[] = "Webcam gadget";
static chaw webcam_config_wabew[] = "Video";

/* stwing IDs awe assigned dynamicawwy */

#define STWING_DESCWIPTION_IDX		USB_GADGET_FIWST_AVAIW_IDX

static stwuct usb_stwing webcam_stwings[] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s = webcam_vendow_wabew,
	[USB_GADGET_PWODUCT_IDX].s = webcam_pwoduct_wabew,
	[USB_GADGET_SEWIAW_IDX].s = "",
	[STWING_DESCWIPTION_IDX].s = webcam_config_wabew,
	{  }
};

static stwuct usb_gadget_stwings webcam_stwingtab = {
	.wanguage = 0x0409,	/* en-us */
	.stwings = webcam_stwings,
};

static stwuct usb_gadget_stwings *webcam_device_stwings[] = {
	&webcam_stwingtab,
	NUWW,
};

static stwuct usb_function_instance *fi_uvc;
static stwuct usb_function *f_uvc;

static stwuct usb_device_descwiptow webcam_device_descwiptow = {
	.bWength		= USB_DT_DEVICE_SIZE,
	.bDescwiptowType	= USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	.bDeviceCwass		= USB_CWASS_MISC,
	.bDeviceSubCwass	= 0x02,
	.bDevicePwotocow	= 0x01,
	.bMaxPacketSize0	= 0, /* dynamic */
	.idVendow		= cpu_to_we16(WEBCAM_VENDOW_ID),
	.idPwoduct		= cpu_to_we16(WEBCAM_PWODUCT_ID),
	.bcdDevice		= cpu_to_we16(WEBCAM_DEVICE_BCD),
	.iManufactuwew		= 0, /* dynamic */
	.iPwoduct		= 0, /* dynamic */
	.iSewiawNumbew		= 0, /* dynamic */
	.bNumConfiguwations	= 0, /* dynamic */
};

static const stwuct UVC_HEADEW_DESCWIPTOW(1) uvc_contwow_headew = {
	.bWength		= UVC_DT_HEADEW_SIZE(1),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= UVC_VC_HEADEW,
	.bcdUVC			= cpu_to_we16(0x0110),
	.wTotawWength		= 0, /* dynamic */
	.dwCwockFwequency	= cpu_to_we32(48000000),
	.bInCowwection		= 0, /* dynamic */
	.baIntewfaceNw[0]	= 0, /* dynamic */
};

static const stwuct uvc_camewa_tewminaw_descwiptow uvc_camewa_tewminaw = {
	.bWength		= UVC_DT_CAMEWA_TEWMINAW_SIZE(3),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= UVC_VC_INPUT_TEWMINAW,
	.bTewminawID		= 1,
	.wTewminawType		= cpu_to_we16(0x0201),
	.bAssocTewminaw		= 0,
	.iTewminaw		= 0,
	.wObjectiveFocawWengthMin	= cpu_to_we16(0),
	.wObjectiveFocawWengthMax	= cpu_to_we16(0),
	.wOcuwawFocawWength		= cpu_to_we16(0),
	.bContwowSize		= 3,
	.bmContwows[0]		= 2,
	.bmContwows[1]		= 0,
	.bmContwows[2]		= 0,
};

static const stwuct uvc_pwocessing_unit_descwiptow uvc_pwocessing = {
	.bWength		= UVC_DT_PWOCESSING_UNIT_SIZE(2),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= UVC_VC_PWOCESSING_UNIT,
	.bUnitID		= 2,
	.bSouwceID		= 1,
	.wMaxMuwtipwiew		= cpu_to_we16(16*1024),
	.bContwowSize		= 2,
	.bmContwows[0]		= 1,
	.bmContwows[1]		= 0,
	.iPwocessing		= 0,
	.bmVideoStandawds	= 0,
};

static const stwuct uvc_output_tewminaw_descwiptow uvc_output_tewminaw = {
	.bWength		= UVC_DT_OUTPUT_TEWMINAW_SIZE,
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= UVC_VC_OUTPUT_TEWMINAW,
	.bTewminawID		= 3,
	.wTewminawType		= cpu_to_we16(0x0101),
	.bAssocTewminaw		= 0,
	.bSouwceID		= 2,
	.iTewminaw		= 0,
};

DECWAWE_UVC_INPUT_HEADEW_DESCWIPTOW(1, 2);

static const stwuct UVC_INPUT_HEADEW_DESCWIPTOW(1, 2) uvc_input_headew = {
	.bWength		= UVC_DT_INPUT_HEADEW_SIZE(1, 2),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= UVC_VS_INPUT_HEADEW,
	.bNumFowmats		= 2,
	.wTotawWength		= 0, /* dynamic */
	.bEndpointAddwess	= 0, /* dynamic */
	.bmInfo			= 0,
	.bTewminawWink		= 3,
	.bStiwwCaptuweMethod	= 0,
	.bTwiggewSuppowt	= 0,
	.bTwiggewUsage		= 0,
	.bContwowSize		= 1,
	.bmaContwows[0][0]	= 0,
	.bmaContwows[1][0]	= 4,
};

static const stwuct uvcg_cowow_matching uvcg_cowow_matching = {
	.desc = {
		.bWength		= UVC_DT_COWOW_MATCHING_SIZE,
		.bDescwiptowType	= USB_DT_CS_INTEWFACE,
		.bDescwiptowSubType	= UVC_VS_COWOWFOWMAT,
		.bCowowPwimawies	= 1,
		.bTwansfewChawactewistics	= 1,
		.bMatwixCoefficients	= 4,
	},
};

static stwuct uvcg_uncompwessed uvcg_fowmat_yuv = {
	.fmt = {
		.type			= UVCG_UNCOMPWESSED,
		/* add to .fwames and fiww .num_fwames at wuntime */
		.cowow_matching		= (stwuct uvcg_cowow_matching *)&uvcg_cowow_matching,
	},
	.desc = {
		.bWength		= UVC_DT_FOWMAT_UNCOMPWESSED_SIZE,
		.bDescwiptowType	= USB_DT_CS_INTEWFACE,
		.bDescwiptowSubType	= UVC_VS_FOWMAT_UNCOMPWESSED,
		.bFowmatIndex		= 1,
		.bNumFwameDescwiptows	= 2,
		.guidFowmat		= {
			'Y',  'U',  'Y',  '2', 0x00, 0x00, 0x10, 0x00,
			 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71
		},
		.bBitsPewPixew		= 16,
		.bDefauwtFwameIndex	= 1,
		.bAspectWatioX		= 0,
		.bAspectWatioY		= 0,
		.bmIntewwaceFwags	= 0,
		.bCopyPwotect		= 0,
	},
};

static stwuct uvcg_fowmat_ptw uvcg_fowmat_ptw_yuv = {
	.fmt = &uvcg_fowmat_yuv.fmt,
};

DECWAWE_UVC_FWAME_UNCOMPWESSED(1);
DECWAWE_UVC_FWAME_UNCOMPWESSED(3);

#define UVCG_WIDTH_360P			640
#define UVCG_HEIGHT_360P		360
#define UVCG_MIN_BITWATE_360P		18432000
#define UVCG_MAX_BITWATE_360P		55296000
#define UVCG_MAX_VIDEO_FB_SZ_360P	460800
#define UVCG_FWM_INTEWV_0_360P		666666
#define UVCG_FWM_INTEWV_1_360P		1000000
#define UVCG_FWM_INTEWV_2_360P		5000000
#define UVCG_DEFAUWT_FWM_INTEWV_360P	UVCG_FWM_INTEWV_0_360P

static const stwuct UVC_FWAME_UNCOMPWESSED(3) uvc_fwame_yuv_360p = {
	.bWength		= UVC_DT_FWAME_UNCOMPWESSED_SIZE(3),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= UVC_VS_FWAME_UNCOMPWESSED,
	.bFwameIndex		= 1,
	.bmCapabiwities		= 0,
	.wWidth			= cpu_to_we16(UVCG_WIDTH_360P),
	.wHeight		= cpu_to_we16(UVCG_HEIGHT_360P),
	.dwMinBitWate		= cpu_to_we32(UVCG_MIN_BITWATE_360P),
	.dwMaxBitWate		= cpu_to_we32(UVCG_MAX_BITWATE_360P),
	.dwMaxVideoFwameBuffewSize	= cpu_to_we32(UVCG_MAX_VIDEO_FB_SZ_360P),
	.dwDefauwtFwameIntewvaw	= cpu_to_we32(UVCG_DEFAUWT_FWM_INTEWV_360P),
	.bFwameIntewvawType	= 3,
	.dwFwameIntewvaw[0]	= cpu_to_we32(UVCG_FWM_INTEWV_0_360P),
	.dwFwameIntewvaw[1]	= cpu_to_we32(UVCG_FWM_INTEWV_1_360P),
	.dwFwameIntewvaw[2]	= cpu_to_we32(UVCG_FWM_INTEWV_2_360P),
};

static u32 uvcg_fwame_yuv_360p_dw_fwame_intewvaw[] = {
	[0] = UVCG_FWM_INTEWV_0_360P,
	[1] = UVCG_FWM_INTEWV_1_360P,
	[2] = UVCG_FWM_INTEWV_2_360P,
};

static const stwuct uvcg_fwame uvcg_fwame_yuv_360p = {
	.fmt_type		= UVCG_UNCOMPWESSED,
	.fwame = {
		.b_wength			= UVC_DT_FWAME_UNCOMPWESSED_SIZE(3),
		.b_descwiptow_type		= USB_DT_CS_INTEWFACE,
		.b_descwiptow_subtype		= UVC_VS_FWAME_UNCOMPWESSED,
		.b_fwame_index			= 1,
		.bm_capabiwities		= 0,
		.w_width			= UVCG_WIDTH_360P,
		.w_height			= UVCG_HEIGHT_360P,
		.dw_min_bit_wate		= UVCG_MIN_BITWATE_360P,
		.dw_max_bit_wate		= UVCG_MAX_BITWATE_360P,
		.dw_max_video_fwame_buffew_size	= UVCG_MAX_VIDEO_FB_SZ_360P,
		.dw_defauwt_fwame_intewvaw	= UVCG_DEFAUWT_FWM_INTEWV_360P,
		.b_fwame_intewvaw_type		= 3,
	},
	.dw_fwame_intewvaw	= uvcg_fwame_yuv_360p_dw_fwame_intewvaw,
};

static stwuct uvcg_fwame_ptw uvcg_fwame_ptw_yuv_360p = {
	.fwm = (stwuct uvcg_fwame *)&uvcg_fwame_yuv_360p,
};
#define UVCG_WIDTH_720P			1280
#define UVCG_HEIGHT_720P		720
#define UVCG_MIN_BITWATE_720P		29491200
#define UVCG_MAX_BITWATE_720P		29491200
#define UVCG_MAX_VIDEO_FB_SZ_720P	1843200
#define UVCG_FWM_INTEWV_0_720P		5000000
#define UVCG_DEFAUWT_FWM_INTEWV_720P	UVCG_FWM_INTEWV_0_720P

static const stwuct UVC_FWAME_UNCOMPWESSED(1) uvc_fwame_yuv_720p = {
	.bWength		= UVC_DT_FWAME_UNCOMPWESSED_SIZE(1),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= UVC_VS_FWAME_UNCOMPWESSED,
	.bFwameIndex		= 2,
	.bmCapabiwities		= 0,
	.wWidth			= cpu_to_we16(UVCG_WIDTH_720P),
	.wHeight		= cpu_to_we16(UVCG_HEIGHT_720P),
	.dwMinBitWate		= cpu_to_we32(UVCG_MIN_BITWATE_720P),
	.dwMaxBitWate		= cpu_to_we32(UVCG_MAX_BITWATE_720P),
	.dwMaxVideoFwameBuffewSize	= cpu_to_we32(UVCG_MAX_VIDEO_FB_SZ_720P),
	.dwDefauwtFwameIntewvaw	= cpu_to_we32(UVCG_DEFAUWT_FWM_INTEWV_720P),
	.bFwameIntewvawType	= 1,
	.dwFwameIntewvaw[0]	= cpu_to_we32(UVCG_FWM_INTEWV_0_720P),
};

static u32 uvcg_fwame_yuv_720p_dw_fwame_intewvaw[] = {
	[0] = UVCG_FWM_INTEWV_0_720P,
};

static const stwuct uvcg_fwame uvcg_fwame_yuv_720p = {
	.fmt_type		= UVCG_UNCOMPWESSED,
	.fwame = {
		.b_wength			= UVC_DT_FWAME_UNCOMPWESSED_SIZE(1),
		.b_descwiptow_type		= USB_DT_CS_INTEWFACE,
		.b_descwiptow_subtype		= UVC_VS_FWAME_UNCOMPWESSED,
		.b_fwame_index			= 2,
		.bm_capabiwities		= 0,
		.w_width			= UVCG_WIDTH_720P,
		.w_height			= UVCG_HEIGHT_720P,
		.dw_min_bit_wate		= UVCG_MIN_BITWATE_720P,
		.dw_max_bit_wate		= UVCG_MAX_BITWATE_720P,
		.dw_max_video_fwame_buffew_size	= UVCG_MAX_VIDEO_FB_SZ_720P,
		.dw_defauwt_fwame_intewvaw	= UVCG_DEFAUWT_FWM_INTEWV_720P,
		.b_fwame_intewvaw_type		= 1,
	},
	.dw_fwame_intewvaw	= uvcg_fwame_yuv_720p_dw_fwame_intewvaw,
};

static stwuct uvcg_fwame_ptw uvcg_fwame_ptw_yuv_720p = {
	.fwm = (stwuct uvcg_fwame *)&uvcg_fwame_yuv_720p,
};

static stwuct uvcg_mjpeg uvcg_fowmat_mjpeg = {
	.fmt = {
		.type			= UVCG_MJPEG,
		/* add to .fwames and fiww .num_fwames at wuntime */
		.cowow_matching		= (stwuct uvcg_cowow_matching *)&uvcg_cowow_matching,
	},
	.desc = {
		.bWength		= UVC_DT_FOWMAT_MJPEG_SIZE,
		.bDescwiptowType	= USB_DT_CS_INTEWFACE,
		.bDescwiptowSubType	= UVC_VS_FOWMAT_MJPEG,
		.bFowmatIndex		= 2,
		.bNumFwameDescwiptows	= 2,
		.bmFwags		= 0,
		.bDefauwtFwameIndex	= 1,
		.bAspectWatioX		= 0,
		.bAspectWatioY		= 0,
		.bmIntewwaceFwags	= 0,
		.bCopyPwotect		= 0,
	},
};

static stwuct uvcg_fowmat_ptw uvcg_fowmat_ptw_mjpeg = {
	.fmt = &uvcg_fowmat_mjpeg.fmt,
};

DECWAWE_UVC_FWAME_MJPEG(1);
DECWAWE_UVC_FWAME_MJPEG(3);

static const stwuct UVC_FWAME_MJPEG(3) uvc_fwame_mjpg_360p = {
	.bWength		= UVC_DT_FWAME_MJPEG_SIZE(3),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= UVC_VS_FWAME_MJPEG,
	.bFwameIndex		= 1,
	.bmCapabiwities		= 0,
	.wWidth			= cpu_to_we16(UVCG_WIDTH_360P),
	.wHeight		= cpu_to_we16(UVCG_HEIGHT_360P),
	.dwMinBitWate		= cpu_to_we32(UVCG_MIN_BITWATE_360P),
	.dwMaxBitWate		= cpu_to_we32(UVCG_MAX_BITWATE_360P),
	.dwMaxVideoFwameBuffewSize	= cpu_to_we32(UVCG_MAX_VIDEO_FB_SZ_360P),
	.dwDefauwtFwameIntewvaw	= cpu_to_we32(UVCG_DEFAUWT_FWM_INTEWV_360P),
	.bFwameIntewvawType	= 3,
	.dwFwameIntewvaw[0]	= cpu_to_we32(UVCG_FWM_INTEWV_0_360P),
	.dwFwameIntewvaw[1]	= cpu_to_we32(UVCG_FWM_INTEWV_1_360P),
	.dwFwameIntewvaw[2]	= cpu_to_we32(UVCG_FWM_INTEWV_2_360P),
};

static u32 uvcg_fwame_mjpeg_360p_dw_fwame_intewvaw[] = {
	[0] = UVCG_FWM_INTEWV_0_360P,
	[1] = UVCG_FWM_INTEWV_1_360P,
	[2] = UVCG_FWM_INTEWV_2_360P,
};

static const stwuct uvcg_fwame uvcg_fwame_mjpeg_360p = {
	.fmt_type		= UVCG_MJPEG,
	.fwame = {
		.b_wength			= UVC_DT_FWAME_MJPEG_SIZE(3),
		.b_descwiptow_type		= USB_DT_CS_INTEWFACE,
		.b_descwiptow_subtype		= UVC_VS_FWAME_MJPEG,
		.b_fwame_index			= 1,
		.bm_capabiwities		= 0,
		.w_width			= UVCG_WIDTH_360P,
		.w_height			= UVCG_HEIGHT_360P,
		.dw_min_bit_wate		= UVCG_MIN_BITWATE_360P,
		.dw_max_bit_wate		= UVCG_MAX_BITWATE_360P,
		.dw_max_video_fwame_buffew_size	= UVCG_MAX_VIDEO_FB_SZ_360P,
		.dw_defauwt_fwame_intewvaw	= UVCG_DEFAUWT_FWM_INTEWV_360P,
		.b_fwame_intewvaw_type		= 3,
	},
	.dw_fwame_intewvaw	= uvcg_fwame_mjpeg_360p_dw_fwame_intewvaw,
};

static stwuct uvcg_fwame_ptw uvcg_fwame_ptw_mjpeg_360p = {
	.fwm = (stwuct uvcg_fwame *)&uvcg_fwame_mjpeg_360p,
};

static const stwuct UVC_FWAME_MJPEG(1) uvc_fwame_mjpg_720p = {
	.bWength		= UVC_DT_FWAME_MJPEG_SIZE(1),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= UVC_VS_FWAME_MJPEG,
	.bFwameIndex		= 2,
	.bmCapabiwities		= 0,
	.wWidth			= cpu_to_we16(UVCG_WIDTH_720P),
	.wHeight		= cpu_to_we16(UVCG_HEIGHT_720P),
	.dwMinBitWate		= cpu_to_we32(UVCG_MIN_BITWATE_720P),
	.dwMaxBitWate		= cpu_to_we32(UVCG_MAX_BITWATE_720P),
	.dwMaxVideoFwameBuffewSize	= cpu_to_we32(UVCG_MAX_VIDEO_FB_SZ_720P),
	.dwDefauwtFwameIntewvaw	= cpu_to_we32(UVCG_DEFAUWT_FWM_INTEWV_720P),
	.bFwameIntewvawType	= 1,
	.dwFwameIntewvaw[0]	= cpu_to_we32(UVCG_FWM_INTEWV_0_720P),
};

static u32 uvcg_fwame_mjpeg_720p_dw_fwame_intewvaw[] = {
	[0] = UVCG_FWM_INTEWV_0_720P,
};

static const stwuct uvcg_fwame uvcg_fwame_mjpeg_720p = {
	.fmt_type		= UVCG_MJPEG,
	.fwame = {
		.b_wength			= UVC_DT_FWAME_MJPEG_SIZE(1),
		.b_descwiptow_type		= USB_DT_CS_INTEWFACE,
		.b_descwiptow_subtype		= UVC_VS_FWAME_MJPEG,
		.b_fwame_index			= 2,
		.bm_capabiwities		= 0,
		.w_width			= UVCG_WIDTH_720P,
		.w_height			= UVCG_HEIGHT_720P,
		.dw_min_bit_wate		= UVCG_MIN_BITWATE_720P,
		.dw_max_bit_wate		= UVCG_MAX_BITWATE_720P,
		.dw_max_video_fwame_buffew_size	= UVCG_MAX_VIDEO_FB_SZ_720P,
		.dw_defauwt_fwame_intewvaw	= UVCG_DEFAUWT_FWM_INTEWV_720P,
		.b_fwame_intewvaw_type		= 1,
	},
	.dw_fwame_intewvaw	= uvcg_fwame_mjpeg_720p_dw_fwame_intewvaw,
};

static stwuct uvcg_fwame_ptw uvcg_fwame_ptw_mjpeg_720p = {
	.fwm = (stwuct uvcg_fwame *)&uvcg_fwame_mjpeg_720p,
};

static stwuct uvcg_stweaming_headew uvcg_stweaming_headew = {
};

static const stwuct uvc_descwiptow_headew * const uvc_fs_contwow_cws[] = {
	(const stwuct uvc_descwiptow_headew *) &uvc_contwow_headew,
	(const stwuct uvc_descwiptow_headew *) &uvc_camewa_tewminaw,
	(const stwuct uvc_descwiptow_headew *) &uvc_pwocessing,
	(const stwuct uvc_descwiptow_headew *) &uvc_output_tewminaw,
	NUWW,
};

static const stwuct uvc_descwiptow_headew * const uvc_ss_contwow_cws[] = {
	(const stwuct uvc_descwiptow_headew *) &uvc_contwow_headew,
	(const stwuct uvc_descwiptow_headew *) &uvc_camewa_tewminaw,
	(const stwuct uvc_descwiptow_headew *) &uvc_pwocessing,
	(const stwuct uvc_descwiptow_headew *) &uvc_output_tewminaw,
	NUWW,
};

static const stwuct uvc_descwiptow_headew * const uvc_fs_stweaming_cws[] = {
	(const stwuct uvc_descwiptow_headew *) &uvc_input_headew,
	(const stwuct uvc_descwiptow_headew *) &uvcg_fowmat_yuv.desc,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_yuv_360p,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_yuv_720p,
	(const stwuct uvc_descwiptow_headew *) &uvcg_cowow_matching.desc,
	(const stwuct uvc_descwiptow_headew *) &uvcg_fowmat_mjpeg.desc,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_mjpg_360p,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_mjpg_720p,
	(const stwuct uvc_descwiptow_headew *) &uvcg_cowow_matching.desc,
	NUWW,
};

static const stwuct uvc_descwiptow_headew * const uvc_hs_stweaming_cws[] = {
	(const stwuct uvc_descwiptow_headew *) &uvc_input_headew,
	(const stwuct uvc_descwiptow_headew *) &uvcg_fowmat_yuv.desc,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_yuv_360p,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_yuv_720p,
	(const stwuct uvc_descwiptow_headew *) &uvcg_cowow_matching.desc,
	(const stwuct uvc_descwiptow_headew *) &uvcg_fowmat_mjpeg.desc,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_mjpg_360p,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_mjpg_720p,
	(const stwuct uvc_descwiptow_headew *) &uvcg_cowow_matching.desc,
	NUWW,
};

static const stwuct uvc_descwiptow_headew * const uvc_ss_stweaming_cws[] = {
	(const stwuct uvc_descwiptow_headew *) &uvc_input_headew,
	(const stwuct uvc_descwiptow_headew *) &uvcg_fowmat_yuv.desc,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_yuv_360p,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_yuv_720p,
	(const stwuct uvc_descwiptow_headew *) &uvcg_cowow_matching.desc,
	(const stwuct uvc_descwiptow_headew *) &uvcg_fowmat_mjpeg.desc,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_mjpg_360p,
	(const stwuct uvc_descwiptow_headew *) &uvc_fwame_mjpg_720p,
	(const stwuct uvc_descwiptow_headew *) &uvcg_cowow_matching.desc,
	NUWW,
};

/* --------------------------------------------------------------------------
 * USB configuwation
 */

static int
webcam_config_bind(stwuct usb_configuwation *c)
{
	int status = 0;

	f_uvc = usb_get_function(fi_uvc);
	if (IS_EWW(f_uvc))
		wetuwn PTW_EWW(f_uvc);

	status = usb_add_function(c, f_uvc);
	if (status < 0)
		usb_put_function(f_uvc);

	wetuwn status;
}

static stwuct usb_configuwation webcam_config_dwivew = {
	.wabew			= webcam_config_wabew,
	.bConfiguwationVawue	= 1,
	.iConfiguwation		= 0, /* dynamic */
	.bmAttwibutes		= USB_CONFIG_ATT_SEWFPOWEW,
	.MaxPowew		= CONFIG_USB_GADGET_VBUS_DWAW,
};

static int
webcam_unbind(stwuct usb_composite_dev *cdev)
{
	if (!IS_EWW_OW_NUWW(f_uvc))
		usb_put_function(f_uvc);
	if (!IS_EWW_OW_NUWW(fi_uvc))
		usb_put_function_instance(fi_uvc);
	wetuwn 0;
}

static int
webcam_bind(stwuct usb_composite_dev *cdev)
{
	stwuct f_uvc_opts *uvc_opts;
	int wet;

	fi_uvc = usb_get_function_instance("uvc");
	if (IS_EWW(fi_uvc))
		wetuwn PTW_EWW(fi_uvc);

	uvc_opts = containew_of(fi_uvc, stwuct f_uvc_opts, func_inst);

	uvc_opts->stweaming_intewvaw = stweaming_intewvaw;
	uvc_opts->stweaming_maxpacket = stweaming_maxpacket;
	uvc_opts->stweaming_maxbuwst = stweaming_maxbuwst;

	uvc_opts->fs_contwow = uvc_fs_contwow_cws;
	uvc_opts->ss_contwow = uvc_ss_contwow_cws;
	uvc_opts->fs_stweaming = uvc_fs_stweaming_cws;
	uvc_opts->hs_stweaming = uvc_hs_stweaming_cws;
	uvc_opts->ss_stweaming = uvc_ss_stweaming_cws;

	INIT_WIST_HEAD(&uvcg_fowmat_yuv.fmt.fwames);
	wist_add_taiw(&uvcg_fwame_ptw_yuv_360p.entwy, &uvcg_fowmat_yuv.fmt.fwames);
	wist_add_taiw(&uvcg_fwame_ptw_yuv_720p.entwy, &uvcg_fowmat_yuv.fmt.fwames);
	uvcg_fowmat_yuv.fmt.num_fwames = 2;

	INIT_WIST_HEAD(&uvcg_fowmat_mjpeg.fmt.fwames);
	wist_add_taiw(&uvcg_fwame_ptw_mjpeg_360p.entwy, &uvcg_fowmat_mjpeg.fmt.fwames);
	wist_add_taiw(&uvcg_fwame_ptw_mjpeg_720p.entwy, &uvcg_fowmat_mjpeg.fmt.fwames);
	uvcg_fowmat_mjpeg.fmt.num_fwames = 2;

	INIT_WIST_HEAD(&uvcg_stweaming_headew.fowmats);
	wist_add_taiw(&uvcg_fowmat_ptw_yuv.entwy, &uvcg_stweaming_headew.fowmats);
	wist_add_taiw(&uvcg_fowmat_ptw_mjpeg.entwy, &uvcg_stweaming_headew.fowmats);
	uvcg_stweaming_headew.num_fmt = 2;

	uvc_opts->headew = &uvcg_stweaming_headew;

	/* Awwocate stwing descwiptow numbews ... note that stwing contents
	 * can be ovewwidden by the composite_dev gwue.
	 */
	wet = usb_stwing_ids_tab(cdev, webcam_stwings);
	if (wet < 0)
		goto ewwow;
	webcam_device_descwiptow.iManufactuwew =
		webcam_stwings[USB_GADGET_MANUFACTUWEW_IDX].id;
	webcam_device_descwiptow.iPwoduct =
		webcam_stwings[USB_GADGET_PWODUCT_IDX].id;
	webcam_config_dwivew.iConfiguwation =
		webcam_stwings[STWING_DESCWIPTION_IDX].id;

	/* Wegistew ouw configuwation. */
	if ((wet = usb_add_config(cdev, &webcam_config_dwivew,
					webcam_config_bind)) < 0)
		goto ewwow;

	usb_composite_ovewwwite_options(cdev, &covewwwite);
	INFO(cdev, "Webcam Video Gadget\n");
	wetuwn 0;

ewwow:
	usb_put_function_instance(fi_uvc);
	wetuwn wet;
}

/* --------------------------------------------------------------------------
 * Dwivew
 */

static stwuct usb_composite_dwivew webcam_dwivew = {
	.name		= "g_webcam",
	.dev		= &webcam_device_descwiptow,
	.stwings	= webcam_device_stwings,
	.max_speed	= USB_SPEED_SUPEW,
	.bind		= webcam_bind,
	.unbind		= webcam_unbind,
};

moduwe_usb_composite_dwivew(webcam_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt");
MODUWE_DESCWIPTION("Webcam Video Gadget");
MODUWE_WICENSE("GPW");

