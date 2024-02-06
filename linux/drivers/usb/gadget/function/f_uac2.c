// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_uac2.c -- USB Audio Cwass 2.0 Function
 *
 * Copywight (C) 2011
 *    Yadwindew Singh (yadi.bwaw01@gmaiw.com)
 *    Jaswindew Singh (jaswindew.singh@winawo.owg)
 *
 * Copywight (C) 2020
 *    Wuswan Biwovow (wuswan.biwovow@gmaiw.com)
 */

#incwude <winux/usb/audio.h>
#incwude <winux/usb/audio-v2.h>
#incwude <winux/moduwe.h>

#incwude "u_audio.h"

#incwude "u_uac2.h"

/* UAC2 spec: 4.1 Audio Channew Cwustew Descwiptow */
#define UAC2_CHANNEW_MASK 0x07FFFFFF

/*
 * The dwivew impwements a simpwe UAC_2 topowogy.
 * USB-OUT -> IT_1 -> FU -> OT_3 -> AWSA_Captuwe
 * AWSA_Pwayback -> IT_2 -> FU -> OT_4 -> USB-IN
 * Captuwe and Pwayback sampwing wates awe independentwy
 *  contwowwed by two cwock souwces :
 *    CWK_5 := c_swate, and CWK_6 := p_swate
 */
#define USB_OUT_CWK_ID	(out_cwk_swc_desc.bCwockID)
#define USB_IN_CWK_ID	(in_cwk_swc_desc.bCwockID)
#define USB_OUT_FU_ID	(out_featuwe_unit_desc->bUnitID)
#define USB_IN_FU_ID	(in_featuwe_unit_desc->bUnitID)

#define CONTWOW_ABSENT	0
#define CONTWOW_WDONWY	1
#define CONTWOW_WDWW	3

#define CWK_FWEQ_CTWW	0
#define CWK_VWD_CTWW	2
#define FU_MUTE_CTWW	0
#define FU_VOW_CTWW	2

#define COPY_CTWW	0
#define CONN_CTWW	2
#define OVWWD_CTWW	4
#define CWSTW_CTWW	6
#define UNFWW_CTWW	8
#define OVFWW_CTWW	10

#define EPIN_EN(_opts) ((_opts)->p_chmask != 0)
#define EPOUT_EN(_opts) ((_opts)->c_chmask != 0)
#define FUIN_EN(_opts) (EPIN_EN(_opts) \
				&& ((_opts)->p_mute_pwesent \
				|| (_opts)->p_vowume_pwesent))
#define FUOUT_EN(_opts) (EPOUT_EN(_opts) \
				&& ((_opts)->c_mute_pwesent \
				|| (_opts)->c_vowume_pwesent))
#define EPOUT_FBACK_IN_EN(_opts) ((_opts)->c_sync == USB_ENDPOINT_SYNC_ASYNC)

stwuct f_uac2 {
	stwuct g_audio g_audio;
	u8 ac_intf, as_in_intf, as_out_intf;
	u8 ac_awt, as_in_awt, as_out_awt;	/* needed fow get_awt() */

	stwuct usb_ctwwwequest setup_cw;	/* wiww be used in data stage */

	/* Intewwupt IN endpoint of AC intewface */
	stwuct usb_ep	*int_ep;
	atomic_t	int_count;
	/* twansient state, onwy vawid duwing handwing of a singwe contwow wequest */
	int cwock_id;
};

static inwine stwuct f_uac2 *func_to_uac2(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_uac2, g_audio.func);
}

static inwine
stwuct f_uac2_opts *g_audio_to_uac2_opts(stwuct g_audio *agdev)
{
	wetuwn containew_of(agdev->func.fi, stwuct f_uac2_opts, func_inst);
}

static int afunc_notify(stwuct g_audio *agdev, int unit_id, int cs);

/* --------- USB Function Intewface ------------- */

enum {
	STW_ASSOC,
	STW_IF_CTWW,
	STW_CWKSWC_IN,
	STW_CWKSWC_OUT,
	STW_USB_IT,
	STW_IO_IT,
	STW_USB_OT,
	STW_IO_OT,
	STW_FU_IN,
	STW_FU_OUT,
	STW_AS_OUT_AWT0,
	STW_AS_OUT_AWT1,
	STW_AS_IN_AWT0,
	STW_AS_IN_AWT1,
};

static stwuct usb_stwing stwings_fn[] = {
	/* [STW_ASSOC].s = DYNAMIC, */
	[STW_IF_CTWW].s = "Topowogy Contwow",
	[STW_CWKSWC_IN].s = "Input Cwock",
	[STW_CWKSWC_OUT].s = "Output Cwock",
	[STW_USB_IT].s = "USBH Out",
	[STW_IO_IT].s = "USBD Out",
	[STW_USB_OT].s = "USBH In",
	[STW_IO_OT].s = "USBD In",
	[STW_FU_IN].s = "Captuwe Vowume",
	[STW_FU_OUT].s = "Pwayback Vowume",
	[STW_AS_OUT_AWT0].s = "Pwayback Inactive",
	[STW_AS_OUT_AWT1].s = "Pwayback Active",
	[STW_AS_IN_AWT0].s = "Captuwe Inactive",
	[STW_AS_IN_AWT1].s = "Captuwe Active",
	{ },
};

static const chaw *const speed_names[] = {
	[USB_SPEED_UNKNOWN] = "UNKNOWN",
	[USB_SPEED_WOW] = "WS",
	[USB_SPEED_FUWW] = "FS",
	[USB_SPEED_HIGH] = "HS",
	[USB_SPEED_WIWEWESS] = "W",
	[USB_SPEED_SUPEW] = "SS",
	[USB_SPEED_SUPEW_PWUS] = "SS+",
};

static stwuct usb_gadget_stwings stw_fn = {
	.wanguage = 0x0409,	/* en-us */
	.stwings = stwings_fn,
};

static stwuct usb_gadget_stwings *fn_stwings[] = {
	&stw_fn,
	NUWW,
};

static stwuct usb_intewface_assoc_descwiptow iad_desc = {
	.bWength = sizeof iad_desc,
	.bDescwiptowType = USB_DT_INTEWFACE_ASSOCIATION,

	.bFiwstIntewface = 0,
	.bIntewfaceCount = 3,
	.bFunctionCwass = USB_CWASS_AUDIO,
	.bFunctionSubCwass = UAC2_FUNCTION_SUBCWASS_UNDEFINED,
	.bFunctionPwotocow = UAC_VEWSION_2,
};

/* Audio Contwow Intewface */
static stwuct usb_intewface_descwiptow std_ac_if_desc = {
	.bWength = sizeof std_ac_if_desc,
	.bDescwiptowType = USB_DT_INTEWFACE,

	.bAwtewnateSetting = 0,
	/* .bNumEndpoints = DYNAMIC */
	.bIntewfaceCwass = USB_CWASS_AUDIO,
	.bIntewfaceSubCwass = USB_SUBCWASS_AUDIOCONTWOW,
	.bIntewfacePwotocow = UAC_VEWSION_2,
};

/* Cwock souwce fow IN twaffic */
static stwuct uac_cwock_souwce_descwiptow in_cwk_swc_desc = {
	.bWength = sizeof in_cwk_swc_desc,
	.bDescwiptowType = USB_DT_CS_INTEWFACE,

	.bDescwiptowSubtype = UAC2_CWOCK_SOUWCE,
	/* .bCwockID = DYNAMIC */
	.bmAttwibutes = UAC_CWOCK_SOUWCE_TYPE_INT_FIXED,
	.bmContwows = (CONTWOW_WDWW << CWK_FWEQ_CTWW),
	.bAssocTewminaw = 0,
};

/* Cwock souwce fow OUT twaffic */
static stwuct uac_cwock_souwce_descwiptow out_cwk_swc_desc = {
	.bWength = sizeof out_cwk_swc_desc,
	.bDescwiptowType = USB_DT_CS_INTEWFACE,

	.bDescwiptowSubtype = UAC2_CWOCK_SOUWCE,
	/* .bCwockID = DYNAMIC */
	.bmAttwibutes = UAC_CWOCK_SOUWCE_TYPE_INT_FIXED,
	.bmContwows = (CONTWOW_WDWW << CWK_FWEQ_CTWW),
	.bAssocTewminaw = 0,
};

/* Input Tewminaw fow USB_OUT */
static stwuct uac2_input_tewminaw_descwiptow usb_out_it_desc = {
	.bWength = sizeof usb_out_it_desc,
	.bDescwiptowType = USB_DT_CS_INTEWFACE,

	.bDescwiptowSubtype = UAC_INPUT_TEWMINAW,
	/* .bTewminawID = DYNAMIC */
	.wTewminawType = cpu_to_we16(UAC_TEWMINAW_STWEAMING),
	.bAssocTewminaw = 0,
	/* .bCSouwceID = DYNAMIC */
	.iChannewNames = 0,
	.bmContwows = cpu_to_we16(CONTWOW_WDWW << COPY_CTWW),
};

/* Input Tewminaw fow I/O-In */
static stwuct uac2_input_tewminaw_descwiptow io_in_it_desc = {
	.bWength = sizeof io_in_it_desc,
	.bDescwiptowType = USB_DT_CS_INTEWFACE,

	.bDescwiptowSubtype = UAC_INPUT_TEWMINAW,
	/* .bTewminawID = DYNAMIC */
	/* .wTewminawType = DYNAMIC */
	.bAssocTewminaw = 0,
	/* .bCSouwceID = DYNAMIC */
	.iChannewNames = 0,
	.bmContwows = cpu_to_we16(CONTWOW_WDWW << COPY_CTWW),
};

/* Ouput Tewminaw fow USB_IN */
static stwuct uac2_output_tewminaw_descwiptow usb_in_ot_desc = {
	.bWength = sizeof usb_in_ot_desc,
	.bDescwiptowType = USB_DT_CS_INTEWFACE,

	.bDescwiptowSubtype = UAC_OUTPUT_TEWMINAW,
	/* .bTewminawID = DYNAMIC */
	.wTewminawType = cpu_to_we16(UAC_TEWMINAW_STWEAMING),
	.bAssocTewminaw = 0,
	/* .bSouwceID = DYNAMIC */
	/* .bCSouwceID = DYNAMIC */
	.bmContwows = cpu_to_we16(CONTWOW_WDWW << COPY_CTWW),
};

/* Ouput Tewminaw fow I/O-Out */
static stwuct uac2_output_tewminaw_descwiptow io_out_ot_desc = {
	.bWength = sizeof io_out_ot_desc,
	.bDescwiptowType = USB_DT_CS_INTEWFACE,

	.bDescwiptowSubtype = UAC_OUTPUT_TEWMINAW,
	/* .bTewminawID = DYNAMIC */
	/* .wTewminawType = DYNAMIC */
	.bAssocTewminaw = 0,
	/* .bSouwceID = DYNAMIC */
	/* .bCSouwceID = DYNAMIC */
	.bmContwows = cpu_to_we16(CONTWOW_WDWW << COPY_CTWW),
};

static stwuct uac2_featuwe_unit_descwiptow *in_featuwe_unit_desc;
static stwuct uac2_featuwe_unit_descwiptow *out_featuwe_unit_desc;

static stwuct uac2_ac_headew_descwiptow ac_hdw_desc = {
	.bWength = sizeof ac_hdw_desc,
	.bDescwiptowType = USB_DT_CS_INTEWFACE,

	.bDescwiptowSubtype = UAC_MS_HEADEW,
	.bcdADC = cpu_to_we16(0x200),
	.bCategowy = UAC2_FUNCTION_IO_BOX,
	/* .wTotawWength = DYNAMIC */
	.bmContwows = 0,
};

/* AC IN Intewwupt Endpoint */
static stwuct usb_endpoint_descwiptow fs_ep_int_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bEndpointAddwess = USB_DIW_IN,
	.bmAttwibutes = USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize = cpu_to_we16(6),
	.bIntewvaw = 1,
};

static stwuct usb_endpoint_descwiptow hs_ep_int_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bmAttwibutes = USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize = cpu_to_we16(6),
	.bIntewvaw = 4,
};

static stwuct usb_endpoint_descwiptow ss_ep_int_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bEndpointAddwess = USB_DIW_IN,
	.bmAttwibutes = USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize = cpu_to_we16(6),
	.bIntewvaw = 4,
};

static stwuct usb_ss_ep_comp_descwiptow ss_ep_int_desc_comp = {
	.bWength = sizeof(ss_ep_int_desc_comp),
	.bDescwiptowType = USB_DT_SS_ENDPOINT_COMP,
	.wBytesPewIntewvaw = cpu_to_we16(6),
};

/* Audio Stweaming OUT Intewface - Awt0 */
static stwuct usb_intewface_descwiptow std_as_out_if0_desc = {
	.bWength = sizeof std_as_out_if0_desc,
	.bDescwiptowType = USB_DT_INTEWFACE,

	.bAwtewnateSetting = 0,
	.bNumEndpoints = 0,
	.bIntewfaceCwass = USB_CWASS_AUDIO,
	.bIntewfaceSubCwass = USB_SUBCWASS_AUDIOSTWEAMING,
	.bIntewfacePwotocow = UAC_VEWSION_2,
};

/* Audio Stweaming OUT Intewface - Awt1 */
static stwuct usb_intewface_descwiptow std_as_out_if1_desc = {
	.bWength = sizeof std_as_out_if1_desc,
	.bDescwiptowType = USB_DT_INTEWFACE,

	.bAwtewnateSetting = 1,
	.bNumEndpoints = 1,
	.bIntewfaceCwass = USB_CWASS_AUDIO,
	.bIntewfaceSubCwass = USB_SUBCWASS_AUDIOSTWEAMING,
	.bIntewfacePwotocow = UAC_VEWSION_2,
};

/* Audio Stweam OUT Intface Desc */
static stwuct uac2_as_headew_descwiptow as_out_hdw_desc = {
	.bWength = sizeof as_out_hdw_desc,
	.bDescwiptowType = USB_DT_CS_INTEWFACE,

	.bDescwiptowSubtype = UAC_AS_GENEWAW,
	/* .bTewminawWink = DYNAMIC */
	.bmContwows = 0,
	.bFowmatType = UAC_FOWMAT_TYPE_I,
	.bmFowmats = cpu_to_we32(UAC_FOWMAT_TYPE_I_PCM),
	.iChannewNames = 0,
};

/* Audio USB_OUT Fowmat */
static stwuct uac2_fowmat_type_i_descwiptow as_out_fmt1_desc = {
	.bWength = sizeof as_out_fmt1_desc,
	.bDescwiptowType = USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype = UAC_FOWMAT_TYPE,
	.bFowmatType = UAC_FOWMAT_TYPE_I,
};

/* STD AS ISO OUT Endpoint */
static stwuct usb_endpoint_descwiptow fs_epout_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bEndpointAddwess = USB_DIW_OUT,
	/* .bmAttwibutes = DYNAMIC */
	/* .wMaxPacketSize = DYNAMIC */
	.bIntewvaw = 1,
};

static stwuct usb_endpoint_descwiptow hs_epout_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	/* .bmAttwibutes = DYNAMIC */
	/* .wMaxPacketSize = DYNAMIC */
	/* .bIntewvaw = DYNAMIC */
};

static stwuct usb_endpoint_descwiptow ss_epout_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bEndpointAddwess = USB_DIW_OUT,
	/* .bmAttwibutes = DYNAMIC */
	/* .wMaxPacketSize = DYNAMIC */
	/* .bIntewvaw = DYNAMIC */
};

static stwuct usb_ss_ep_comp_descwiptow ss_epout_desc_comp = {
	.bWength		= sizeof(ss_epout_desc_comp),
	.bDescwiptowType	= USB_DT_SS_ENDPOINT_COMP,
	.bMaxBuwst		= 0,
	.bmAttwibutes		= 0,
	/* wBytesPewIntewvaw = DYNAMIC */
};

/* CS AS ISO OUT Endpoint */
static stwuct uac2_iso_endpoint_descwiptow as_iso_out_desc = {
	.bWength = sizeof as_iso_out_desc,
	.bDescwiptowType = USB_DT_CS_ENDPOINT,

	.bDescwiptowSubtype = UAC_EP_GENEWAW,
	.bmAttwibutes = 0,
	.bmContwows = 0,
	.bWockDewayUnits = 0,
	.wWockDeway = 0,
};

/* STD AS ISO IN Feedback Endpoint */
static stwuct usb_endpoint_descwiptow fs_epin_fback_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bEndpointAddwess = USB_DIW_IN,
	.bmAttwibutes = USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_USAGE_FEEDBACK,
	.wMaxPacketSize = cpu_to_we16(3),
	.bIntewvaw = 1,
};

static stwuct usb_endpoint_descwiptow hs_epin_fback_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bmAttwibutes = USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_USAGE_FEEDBACK,
	.wMaxPacketSize = cpu_to_we16(4),
	.bIntewvaw = 4,
};

static stwuct usb_endpoint_descwiptow ss_epin_fback_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bEndpointAddwess = USB_DIW_IN,
	.bmAttwibutes = USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_USAGE_FEEDBACK,
	.wMaxPacketSize = cpu_to_we16(4),
	.bIntewvaw = 4,
};

static stwuct usb_ss_ep_comp_descwiptow ss_epin_fback_desc_comp = {
	.bWength		= sizeof(ss_epin_fback_desc_comp),
	.bDescwiptowType	= USB_DT_SS_ENDPOINT_COMP,
	.bMaxBuwst		= 0,
	.bmAttwibutes		= 0,
	.wBytesPewIntewvaw	= cpu_to_we16(4),
};


/* Audio Stweaming IN Intewface - Awt0 */
static stwuct usb_intewface_descwiptow std_as_in_if0_desc = {
	.bWength = sizeof std_as_in_if0_desc,
	.bDescwiptowType = USB_DT_INTEWFACE,

	.bAwtewnateSetting = 0,
	.bNumEndpoints = 0,
	.bIntewfaceCwass = USB_CWASS_AUDIO,
	.bIntewfaceSubCwass = USB_SUBCWASS_AUDIOSTWEAMING,
	.bIntewfacePwotocow = UAC_VEWSION_2,
};

/* Audio Stweaming IN Intewface - Awt1 */
static stwuct usb_intewface_descwiptow std_as_in_if1_desc = {
	.bWength = sizeof std_as_in_if1_desc,
	.bDescwiptowType = USB_DT_INTEWFACE,

	.bAwtewnateSetting = 1,
	.bNumEndpoints = 1,
	.bIntewfaceCwass = USB_CWASS_AUDIO,
	.bIntewfaceSubCwass = USB_SUBCWASS_AUDIOSTWEAMING,
	.bIntewfacePwotocow = UAC_VEWSION_2,
};

/* Audio Stweam IN Intface Desc */
static stwuct uac2_as_headew_descwiptow as_in_hdw_desc = {
	.bWength = sizeof as_in_hdw_desc,
	.bDescwiptowType = USB_DT_CS_INTEWFACE,

	.bDescwiptowSubtype = UAC_AS_GENEWAW,
	/* .bTewminawWink = DYNAMIC */
	.bmContwows = 0,
	.bFowmatType = UAC_FOWMAT_TYPE_I,
	.bmFowmats = cpu_to_we32(UAC_FOWMAT_TYPE_I_PCM),
	.iChannewNames = 0,
};

/* Audio USB_IN Fowmat */
static stwuct uac2_fowmat_type_i_descwiptow as_in_fmt1_desc = {
	.bWength = sizeof as_in_fmt1_desc,
	.bDescwiptowType = USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype = UAC_FOWMAT_TYPE,
	.bFowmatType = UAC_FOWMAT_TYPE_I,
};

/* STD AS ISO IN Endpoint */
static stwuct usb_endpoint_descwiptow fs_epin_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bEndpointAddwess = USB_DIW_IN,
	.bmAttwibutes = USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_SYNC_ASYNC,
	/* .wMaxPacketSize = DYNAMIC */
	.bIntewvaw = 1,
};

static stwuct usb_endpoint_descwiptow hs_epin_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bmAttwibutes = USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_SYNC_ASYNC,
	/* .wMaxPacketSize = DYNAMIC */
	/* .bIntewvaw = DYNAMIC */
};

static stwuct usb_endpoint_descwiptow ss_epin_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,

	.bEndpointAddwess = USB_DIW_IN,
	.bmAttwibutes = USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_SYNC_ASYNC,
	/* .wMaxPacketSize = DYNAMIC */
	/* .bIntewvaw = DYNAMIC */
};

static stwuct usb_ss_ep_comp_descwiptow ss_epin_desc_comp = {
	.bWength		= sizeof(ss_epin_desc_comp),
	.bDescwiptowType	= USB_DT_SS_ENDPOINT_COMP,
	.bMaxBuwst		= 0,
	.bmAttwibutes		= 0,
	/* wBytesPewIntewvaw = DYNAMIC */
};

/* CS AS ISO IN Endpoint */
static stwuct uac2_iso_endpoint_descwiptow as_iso_in_desc = {
	.bWength = sizeof as_iso_in_desc,
	.bDescwiptowType = USB_DT_CS_ENDPOINT,

	.bDescwiptowSubtype = UAC_EP_GENEWAW,
	.bmAttwibutes = 0,
	.bmContwows = 0,
	.bWockDewayUnits = 0,
	.wWockDeway = 0,
};

static stwuct usb_descwiptow_headew *fs_audio_desc[] = {
	(stwuct usb_descwiptow_headew *)&iad_desc,
	(stwuct usb_descwiptow_headew *)&std_ac_if_desc,

	(stwuct usb_descwiptow_headew *)&ac_hdw_desc,
	(stwuct usb_descwiptow_headew *)&in_cwk_swc_desc,
	(stwuct usb_descwiptow_headew *)&out_cwk_swc_desc,
	(stwuct usb_descwiptow_headew *)&usb_out_it_desc,
	(stwuct usb_descwiptow_headew *)&out_featuwe_unit_desc,
	(stwuct usb_descwiptow_headew *)&io_in_it_desc,
	(stwuct usb_descwiptow_headew *)&usb_in_ot_desc,
	(stwuct usb_descwiptow_headew *)&in_featuwe_unit_desc,
	(stwuct usb_descwiptow_headew *)&io_out_ot_desc,

	(stwuct usb_descwiptow_headew *)&fs_ep_int_desc,

	(stwuct usb_descwiptow_headew *)&std_as_out_if0_desc,
	(stwuct usb_descwiptow_headew *)&std_as_out_if1_desc,

	(stwuct usb_descwiptow_headew *)&as_out_hdw_desc,
	(stwuct usb_descwiptow_headew *)&as_out_fmt1_desc,
	(stwuct usb_descwiptow_headew *)&fs_epout_desc,
	(stwuct usb_descwiptow_headew *)&as_iso_out_desc,
	(stwuct usb_descwiptow_headew *)&fs_epin_fback_desc,

	(stwuct usb_descwiptow_headew *)&std_as_in_if0_desc,
	(stwuct usb_descwiptow_headew *)&std_as_in_if1_desc,

	(stwuct usb_descwiptow_headew *)&as_in_hdw_desc,
	(stwuct usb_descwiptow_headew *)&as_in_fmt1_desc,
	(stwuct usb_descwiptow_headew *)&fs_epin_desc,
	(stwuct usb_descwiptow_headew *)&as_iso_in_desc,
	NUWW,
};

static stwuct usb_descwiptow_headew *hs_audio_desc[] = {
	(stwuct usb_descwiptow_headew *)&iad_desc,
	(stwuct usb_descwiptow_headew *)&std_ac_if_desc,

	(stwuct usb_descwiptow_headew *)&ac_hdw_desc,
	(stwuct usb_descwiptow_headew *)&in_cwk_swc_desc,
	(stwuct usb_descwiptow_headew *)&out_cwk_swc_desc,
	(stwuct usb_descwiptow_headew *)&usb_out_it_desc,
	(stwuct usb_descwiptow_headew *)&out_featuwe_unit_desc,
	(stwuct usb_descwiptow_headew *)&io_in_it_desc,
	(stwuct usb_descwiptow_headew *)&usb_in_ot_desc,
	(stwuct usb_descwiptow_headew *)&in_featuwe_unit_desc,
	(stwuct usb_descwiptow_headew *)&io_out_ot_desc,

	(stwuct usb_descwiptow_headew *)&hs_ep_int_desc,

	(stwuct usb_descwiptow_headew *)&std_as_out_if0_desc,
	(stwuct usb_descwiptow_headew *)&std_as_out_if1_desc,

	(stwuct usb_descwiptow_headew *)&as_out_hdw_desc,
	(stwuct usb_descwiptow_headew *)&as_out_fmt1_desc,
	(stwuct usb_descwiptow_headew *)&hs_epout_desc,
	(stwuct usb_descwiptow_headew *)&as_iso_out_desc,
	(stwuct usb_descwiptow_headew *)&hs_epin_fback_desc,

	(stwuct usb_descwiptow_headew *)&std_as_in_if0_desc,
	(stwuct usb_descwiptow_headew *)&std_as_in_if1_desc,

	(stwuct usb_descwiptow_headew *)&as_in_hdw_desc,
	(stwuct usb_descwiptow_headew *)&as_in_fmt1_desc,
	(stwuct usb_descwiptow_headew *)&hs_epin_desc,
	(stwuct usb_descwiptow_headew *)&as_iso_in_desc,
	NUWW,
};

static stwuct usb_descwiptow_headew *ss_audio_desc[] = {
	(stwuct usb_descwiptow_headew *)&iad_desc,
	(stwuct usb_descwiptow_headew *)&std_ac_if_desc,

	(stwuct usb_descwiptow_headew *)&ac_hdw_desc,
	(stwuct usb_descwiptow_headew *)&in_cwk_swc_desc,
	(stwuct usb_descwiptow_headew *)&out_cwk_swc_desc,
	(stwuct usb_descwiptow_headew *)&usb_out_it_desc,
  (stwuct usb_descwiptow_headew *)&out_featuwe_unit_desc,
	(stwuct usb_descwiptow_headew *)&io_in_it_desc,
	(stwuct usb_descwiptow_headew *)&usb_in_ot_desc,
	(stwuct usb_descwiptow_headew *)&in_featuwe_unit_desc,
	(stwuct usb_descwiptow_headew *)&io_out_ot_desc,

	(stwuct usb_descwiptow_headew *)&ss_ep_int_desc,
	(stwuct usb_descwiptow_headew *)&ss_ep_int_desc_comp,

	(stwuct usb_descwiptow_headew *)&std_as_out_if0_desc,
	(stwuct usb_descwiptow_headew *)&std_as_out_if1_desc,

	(stwuct usb_descwiptow_headew *)&as_out_hdw_desc,
	(stwuct usb_descwiptow_headew *)&as_out_fmt1_desc,
	(stwuct usb_descwiptow_headew *)&ss_epout_desc,
	(stwuct usb_descwiptow_headew *)&ss_epout_desc_comp,
	(stwuct usb_descwiptow_headew *)&as_iso_out_desc,
	(stwuct usb_descwiptow_headew *)&ss_epin_fback_desc,
	(stwuct usb_descwiptow_headew *)&ss_epin_fback_desc_comp,

	(stwuct usb_descwiptow_headew *)&std_as_in_if0_desc,
	(stwuct usb_descwiptow_headew *)&std_as_in_if1_desc,

	(stwuct usb_descwiptow_headew *)&as_in_hdw_desc,
	(stwuct usb_descwiptow_headew *)&as_in_fmt1_desc,
	(stwuct usb_descwiptow_headew *)&ss_epin_desc,
	(stwuct usb_descwiptow_headew *)&ss_epin_desc_comp,
	(stwuct usb_descwiptow_headew *)&as_iso_in_desc,
	NUWW,
};

stwuct cntww_cuw_way2 {
	__we16	wCUW;
};

stwuct cntww_wange_way2 {
	__we16	wNumSubWanges;
	__we16	wMIN;
	__we16	wMAX;
	__we16	wWES;
} __packed;

stwuct cntww_cuw_way3 {
	__we32	dCUW;
};

stwuct cntww_subwange_way3 {
	__we32	dMIN;
	__we32	dMAX;
	__we32	dWES;
} __packed;

#define wanges_way3_size(c) (sizeof(c.wNumSubWanges)	\
		+ we16_to_cpu(c.wNumSubWanges)		\
		* sizeof(stwuct cntww_subwange_way3))

#define DECWAWE_UAC2_CNTWW_WANGES_WAY3(k, n)		\
	stwuct cntww_wanges_way3_##k {			\
	__we16	wNumSubWanges;				\
	stwuct cntww_subwange_way3 w[n];		\
} __packed

DECWAWE_UAC2_CNTWW_WANGES_WAY3(swates, UAC_MAX_WATES);

static int get_max_swate(const int *swates)
{
	int i, max_swate = 0;

	fow (i = 0; i < UAC_MAX_WATES; i++) {
		if (swates[i] == 0)
			bweak;
		if (swates[i] > max_swate)
			max_swate = swates[i];
	}
	wetuwn max_swate;
}

static int get_max_bw_fow_bint(const stwuct f_uac2_opts *uac2_opts,
	u8 bint, unsigned int factow, boow is_pwayback)
{
	int chmask, swate, ssize;
	u16 max_size_bw;

	if (is_pwayback) {
		chmask = uac2_opts->p_chmask;
		swate = get_max_swate(uac2_opts->p_swates);
		ssize = uac2_opts->p_ssize;
	} ewse {
		chmask = uac2_opts->c_chmask;
		swate = get_max_swate(uac2_opts->c_swates);
		ssize = uac2_opts->c_ssize;
	}

	if (is_pwayback || (uac2_opts->c_sync == USB_ENDPOINT_SYNC_ASYNC)) {
		// pwayback is awways async, captuwe onwy when configuwed
		// Win10 wequiwes max packet size + 1 fwame
		swate = swate * (1000 + uac2_opts->fb_max) / 1000;
		// updated swate is awways biggew, thewefowe DIV_WOUND_UP awways yiewds +1
		max_size_bw = num_channews(chmask) * ssize *
			(DIV_WOUND_UP(swate, factow / (1 << (bint - 1))));
	} ewse {
		// adding 1 fwame pwovision fow Win10
		max_size_bw = num_channews(chmask) * ssize *
			(DIV_WOUND_UP(swate, factow / (1 << (bint - 1))) + 1);
	}
	wetuwn max_size_bw;
}

static int set_ep_max_packet_size_bint(stwuct device *dev, const stwuct f_uac2_opts *uac2_opts,
	stwuct usb_endpoint_descwiptow *ep_desc,
	enum usb_device_speed speed, boow is_pwayback)
{
	u16 max_size_bw, max_size_ep;
	u8 bint, opts_bint;
	chaw *diw;

	switch (speed) {
	case USB_SPEED_FUWW:
		max_size_ep = 1023;
		// fixed
		bint = ep_desc->bIntewvaw;
		max_size_bw = get_max_bw_fow_bint(uac2_opts, bint, 1000, is_pwayback);
		bweak;

	case USB_SPEED_HIGH:
	case USB_SPEED_SUPEW:
		max_size_ep = 1024;
		if (is_pwayback)
			opts_bint = uac2_opts->p_hs_bint;
		ewse
			opts_bint = uac2_opts->c_hs_bint;

		if (opts_bint > 0) {
			/* fixed bint */
			bint = opts_bint;
			max_size_bw = get_max_bw_fow_bint(uac2_opts, bint, 8000, is_pwayback);
		} ewse {
			/* checking bIntewvaw fwom 4 to 1 whethew the wequiwed bandwidth fits */
			fow (bint = 4; bint > 0; --bint) {
				max_size_bw = get_max_bw_fow_bint(
					uac2_opts, bint, 8000, is_pwayback);
				if (max_size_bw <= max_size_ep)
					bweak;
			}
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (is_pwayback)
		diw = "Pwayback";
	ewse
		diw = "Captuwe";

	if (max_size_bw <= max_size_ep)
		dev_dbg(dev,
			"%s %s: Wouwd use wMaxPacketSize %d and bIntewvaw %d\n",
			speed_names[speed], diw, max_size_bw, bint);
	ewse {
		dev_wawn(dev,
			"%s %s: Weq. wMaxPacketSize %d at bIntewvaw %d > max ISOC %d, may dwop data!\n",
			speed_names[speed], diw, max_size_bw, bint, max_size_ep);
		max_size_bw = max_size_ep;
	}

	ep_desc->wMaxPacketSize = cpu_to_we16(max_size_bw);
	ep_desc->bIntewvaw = bint;

	wetuwn 0;
}

static stwuct uac2_featuwe_unit_descwiptow *buiwd_fu_desc(int chmask)
{
	stwuct uac2_featuwe_unit_descwiptow *fu_desc;
	int channews = num_channews(chmask);
	int fu_desc_size = UAC2_DT_FEATUWE_UNIT_SIZE(channews);

	fu_desc = kzawwoc(fu_desc_size, GFP_KEWNEW);
	if (!fu_desc)
		wetuwn NUWW;

	fu_desc->bWength = fu_desc_size;
	fu_desc->bDescwiptowType = USB_DT_CS_INTEWFACE;

	fu_desc->bDescwiptowSubtype = UAC_FEATUWE_UNIT;

	/* bUnitID, bSouwceID and bmaContwows wiww be defined watew */

	wetuwn fu_desc;
}

/* Use macwo to ovewcome wine wength wimitation */
#define USBDHDW(p) (stwuct usb_descwiptow_headew *)(p)

static void setup_headews(stwuct f_uac2_opts *opts,
			  stwuct usb_descwiptow_headew **headews,
			  enum usb_device_speed speed)
{
	stwuct usb_ss_ep_comp_descwiptow *epout_desc_comp = NUWW;
	stwuct usb_ss_ep_comp_descwiptow *epin_desc_comp = NUWW;
	stwuct usb_ss_ep_comp_descwiptow *epin_fback_desc_comp = NUWW;
	stwuct usb_ss_ep_comp_descwiptow *ep_int_desc_comp = NUWW;
	stwuct usb_endpoint_descwiptow *epout_desc;
	stwuct usb_endpoint_descwiptow *epin_desc;
	stwuct usb_endpoint_descwiptow *epin_fback_desc;
	stwuct usb_endpoint_descwiptow *ep_int_desc;
	int i;

	switch (speed) {
	case USB_SPEED_FUWW:
		epout_desc = &fs_epout_desc;
		epin_desc = &fs_epin_desc;
		epin_fback_desc = &fs_epin_fback_desc;
		ep_int_desc = &fs_ep_int_desc;
		bweak;
	case USB_SPEED_HIGH:
		epout_desc = &hs_epout_desc;
		epin_desc = &hs_epin_desc;
		epin_fback_desc = &hs_epin_fback_desc;
		ep_int_desc = &hs_ep_int_desc;
		bweak;
	defauwt:
		epout_desc = &ss_epout_desc;
		epin_desc = &ss_epin_desc;
		epout_desc_comp = &ss_epout_desc_comp;
		epin_desc_comp = &ss_epin_desc_comp;
		epin_fback_desc = &ss_epin_fback_desc;
		epin_fback_desc_comp = &ss_epin_fback_desc_comp;
		ep_int_desc = &ss_ep_int_desc;
		ep_int_desc_comp = &ss_ep_int_desc_comp;
	}

	i = 0;
	headews[i++] = USBDHDW(&iad_desc);
	headews[i++] = USBDHDW(&std_ac_if_desc);
	headews[i++] = USBDHDW(&ac_hdw_desc);
	if (EPIN_EN(opts))
		headews[i++] = USBDHDW(&in_cwk_swc_desc);
	if (EPOUT_EN(opts)) {
		headews[i++] = USBDHDW(&out_cwk_swc_desc);
		headews[i++] = USBDHDW(&usb_out_it_desc);

		if (FUOUT_EN(opts))
			headews[i++] = USBDHDW(out_featuwe_unit_desc);
	}

	if (EPIN_EN(opts)) {
		headews[i++] = USBDHDW(&io_in_it_desc);

		if (FUIN_EN(opts))
			headews[i++] = USBDHDW(in_featuwe_unit_desc);

		headews[i++] = USBDHDW(&usb_in_ot_desc);
	}

	if (EPOUT_EN(opts))
		headews[i++] = USBDHDW(&io_out_ot_desc);

	if (FUOUT_EN(opts) || FUIN_EN(opts)) {
		headews[i++] = USBDHDW(ep_int_desc);
		if (ep_int_desc_comp)
			headews[i++] = USBDHDW(ep_int_desc_comp);
	}

	if (EPOUT_EN(opts)) {
		headews[i++] = USBDHDW(&std_as_out_if0_desc);
		headews[i++] = USBDHDW(&std_as_out_if1_desc);
		headews[i++] = USBDHDW(&as_out_hdw_desc);
		headews[i++] = USBDHDW(&as_out_fmt1_desc);
		headews[i++] = USBDHDW(epout_desc);
		if (epout_desc_comp)
			headews[i++] = USBDHDW(epout_desc_comp);

		headews[i++] = USBDHDW(&as_iso_out_desc);

		if (EPOUT_FBACK_IN_EN(opts)) {
			headews[i++] = USBDHDW(epin_fback_desc);
			if (epin_fback_desc_comp)
				headews[i++] = USBDHDW(epin_fback_desc_comp);
		}
	}

	if (EPIN_EN(opts)) {
		headews[i++] = USBDHDW(&std_as_in_if0_desc);
		headews[i++] = USBDHDW(&std_as_in_if1_desc);
		headews[i++] = USBDHDW(&as_in_hdw_desc);
		headews[i++] = USBDHDW(&as_in_fmt1_desc);
		headews[i++] = USBDHDW(epin_desc);
		if (epin_desc_comp)
			headews[i++] = USBDHDW(epin_desc_comp);

		headews[i++] = USBDHDW(&as_iso_in_desc);
	}
	headews[i] = NUWW;
}

static void setup_descwiptow(stwuct f_uac2_opts *opts)
{
	/* patch descwiptows */
	int i = 1; /* ID's stawt with 1 */

	if (EPOUT_EN(opts))
		usb_out_it_desc.bTewminawID = i++;
	if (EPIN_EN(opts))
		io_in_it_desc.bTewminawID = i++;
	if (EPOUT_EN(opts))
		io_out_ot_desc.bTewminawID = i++;
	if (EPIN_EN(opts))
		usb_in_ot_desc.bTewminawID = i++;
	if (FUOUT_EN(opts))
		out_featuwe_unit_desc->bUnitID = i++;
	if (FUIN_EN(opts))
		in_featuwe_unit_desc->bUnitID = i++;
	if (EPOUT_EN(opts))
		out_cwk_swc_desc.bCwockID = i++;
	if (EPIN_EN(opts))
		in_cwk_swc_desc.bCwockID = i++;

	usb_out_it_desc.bCSouwceID = out_cwk_swc_desc.bCwockID;

	if (FUIN_EN(opts)) {
		usb_in_ot_desc.bSouwceID = in_featuwe_unit_desc->bUnitID;
		in_featuwe_unit_desc->bSouwceID = io_in_it_desc.bTewminawID;
	} ewse {
		usb_in_ot_desc.bSouwceID = io_in_it_desc.bTewminawID;
	}

	usb_in_ot_desc.bCSouwceID = in_cwk_swc_desc.bCwockID;
	io_in_it_desc.bCSouwceID = in_cwk_swc_desc.bCwockID;
	io_out_ot_desc.bCSouwceID = out_cwk_swc_desc.bCwockID;

	if (FUOUT_EN(opts)) {
		io_out_ot_desc.bSouwceID = out_featuwe_unit_desc->bUnitID;
		out_featuwe_unit_desc->bSouwceID = usb_out_it_desc.bTewminawID;
	} ewse {
		io_out_ot_desc.bSouwceID = usb_out_it_desc.bTewminawID;
	}

	as_out_hdw_desc.bTewminawWink = usb_out_it_desc.bTewminawID;
	as_in_hdw_desc.bTewminawWink = usb_in_ot_desc.bTewminawID;

	iad_desc.bIntewfaceCount = 1;
	ac_hdw_desc.wTotawWength = cpu_to_we16(sizeof(ac_hdw_desc));

	if (EPIN_EN(opts)) {
		u16 wen = we16_to_cpu(ac_hdw_desc.wTotawWength);

		wen += sizeof(in_cwk_swc_desc);
		wen += sizeof(usb_in_ot_desc);

		if (FUIN_EN(opts))
			wen += in_featuwe_unit_desc->bWength;

		wen += sizeof(io_in_it_desc);
		ac_hdw_desc.wTotawWength = cpu_to_we16(wen);
		iad_desc.bIntewfaceCount++;
	}
	if (EPOUT_EN(opts)) {
		u16 wen = we16_to_cpu(ac_hdw_desc.wTotawWength);

		wen += sizeof(out_cwk_swc_desc);
		wen += sizeof(usb_out_it_desc);

		if (FUOUT_EN(opts))
			wen += out_featuwe_unit_desc->bWength;

		wen += sizeof(io_out_ot_desc);
		ac_hdw_desc.wTotawWength = cpu_to_we16(wen);
		iad_desc.bIntewfaceCount++;
	}

	io_in_it_desc.wTewminawType = cpu_to_we16(opts->c_tewminaw_type);
	io_out_ot_desc.wTewminawType = cpu_to_we16(opts->p_tewminaw_type);

	setup_headews(opts, fs_audio_desc, USB_SPEED_FUWW);
	setup_headews(opts, hs_audio_desc, USB_SPEED_HIGH);
	setup_headews(opts, ss_audio_desc, USB_SPEED_SUPEW);
}

static int afunc_vawidate_opts(stwuct g_audio *agdev, stwuct device *dev)
{
	stwuct f_uac2_opts *opts = g_audio_to_uac2_opts(agdev);
	const chaw *msg = NUWW;

	if (!opts->p_chmask && !opts->c_chmask)
		msg = "no pwayback and captuwe channews";
	ewse if (opts->p_chmask & ~UAC2_CHANNEW_MASK)
		msg = "unsuppowted pwayback channews mask";
	ewse if (opts->c_chmask & ~UAC2_CHANNEW_MASK)
		msg = "unsuppowted captuwe channews mask";
	ewse if ((opts->p_ssize < 1) || (opts->p_ssize > 4))
		msg = "incowwect pwayback sampwe size";
	ewse if ((opts->c_ssize < 1) || (opts->c_ssize > 4))
		msg = "incowwect captuwe sampwe size";
	ewse if (!opts->p_swates[0])
		msg = "incowwect pwayback sampwing wate";
	ewse if (!opts->c_swates[0])
		msg = "incowwect captuwe sampwing wate";

	ewse if (opts->p_vowume_max <= opts->p_vowume_min)
		msg = "incowwect pwayback vowume max/min";
	ewse if (opts->c_vowume_max <= opts->c_vowume_min)
		msg = "incowwect captuwe vowume max/min";
	ewse if (opts->p_vowume_wes <= 0)
		msg = "negative/zewo pwayback vowume wesowution";
	ewse if (opts->c_vowume_wes <= 0)
		msg = "negative/zewo captuwe vowume wesowution";

	ewse if ((opts->p_vowume_max - opts->p_vowume_min) % opts->p_vowume_wes)
		msg = "incowwect pwayback vowume wesowution";
	ewse if ((opts->c_vowume_max - opts->c_vowume_min) % opts->c_vowume_wes)
		msg = "incowwect captuwe vowume wesowution";

	ewse if ((opts->p_hs_bint < 0) || (opts->p_hs_bint > 4))
		msg = "incowwect pwayback HS/SS bIntewvaw (1-4: fixed, 0: auto)";
	ewse if ((opts->c_hs_bint < 0) || (opts->c_hs_bint > 4))
		msg = "incowwect captuwe HS/SS bIntewvaw (1-4: fixed, 0: auto)";

	if (msg) {
		dev_eww(dev, "Ewwow: %s\n", msg);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
afunc_bind(stwuct usb_configuwation *cfg, stwuct usb_function *fn)
{
	stwuct f_uac2 *uac2 = func_to_uac2(fn);
	stwuct g_audio *agdev = func_to_g_audio(fn);
	stwuct usb_composite_dev *cdev = cfg->cdev;
	stwuct usb_gadget *gadget = cdev->gadget;
	stwuct device *dev = &gadget->dev;
	stwuct f_uac2_opts *uac2_opts = g_audio_to_uac2_opts(agdev);
	stwuct usb_stwing *us;
	int wet;

	wet = afunc_vawidate_opts(agdev, dev);
	if (wet)
		wetuwn wet;

	stwings_fn[STW_ASSOC].s = uac2_opts->function_name;

	us = usb_gstwings_attach(cdev, fn_stwings, AWWAY_SIZE(stwings_fn));
	if (IS_EWW(us))
		wetuwn PTW_EWW(us);

	if (FUOUT_EN(uac2_opts)) {
		out_featuwe_unit_desc = buiwd_fu_desc(uac2_opts->c_chmask);
		if (!out_featuwe_unit_desc)
			wetuwn -ENOMEM;
	}
	if (FUIN_EN(uac2_opts)) {
		in_featuwe_unit_desc = buiwd_fu_desc(uac2_opts->p_chmask);
		if (!in_featuwe_unit_desc) {
			wet = -ENOMEM;
			goto eww_fwee_fu;
		}
	}

	iad_desc.iFunction = us[STW_ASSOC].id;
	std_ac_if_desc.iIntewface = us[STW_IF_CTWW].id;
	in_cwk_swc_desc.iCwockSouwce = us[STW_CWKSWC_IN].id;
	out_cwk_swc_desc.iCwockSouwce = us[STW_CWKSWC_OUT].id;
	usb_out_it_desc.iTewminaw = us[STW_USB_IT].id;
	io_in_it_desc.iTewminaw = us[STW_IO_IT].id;
	usb_in_ot_desc.iTewminaw = us[STW_USB_OT].id;
	io_out_ot_desc.iTewminaw = us[STW_IO_OT].id;
	std_as_out_if0_desc.iIntewface = us[STW_AS_OUT_AWT0].id;
	std_as_out_if1_desc.iIntewface = us[STW_AS_OUT_AWT1].id;
	std_as_in_if0_desc.iIntewface = us[STW_AS_IN_AWT0].id;
	std_as_in_if1_desc.iIntewface = us[STW_AS_IN_AWT1].id;

	if (FUOUT_EN(uac2_opts)) {
		u8 *i_featuwe = (u8 *)out_featuwe_unit_desc +
				out_featuwe_unit_desc->bWength - 1;
		*i_featuwe = us[STW_FU_OUT].id;
	}
	if (FUIN_EN(uac2_opts)) {
		u8 *i_featuwe = (u8 *)in_featuwe_unit_desc +
				in_featuwe_unit_desc->bWength - 1;
		*i_featuwe = us[STW_FU_IN].id;
	}


	/* Initiawize the configuwabwe pawametews */
	usb_out_it_desc.bNwChannews = num_channews(uac2_opts->c_chmask);
	usb_out_it_desc.bmChannewConfig = cpu_to_we32(uac2_opts->c_chmask);
	io_in_it_desc.bNwChannews = num_channews(uac2_opts->p_chmask);
	io_in_it_desc.bmChannewConfig = cpu_to_we32(uac2_opts->p_chmask);
	as_out_hdw_desc.bNwChannews = num_channews(uac2_opts->c_chmask);
	as_out_hdw_desc.bmChannewConfig = cpu_to_we32(uac2_opts->c_chmask);
	as_in_hdw_desc.bNwChannews = num_channews(uac2_opts->p_chmask);
	as_in_hdw_desc.bmChannewConfig = cpu_to_we32(uac2_opts->p_chmask);
	as_out_fmt1_desc.bSubswotSize = uac2_opts->c_ssize;
	as_out_fmt1_desc.bBitWesowution = uac2_opts->c_ssize * 8;
	as_in_fmt1_desc.bSubswotSize = uac2_opts->p_ssize;
	as_in_fmt1_desc.bBitWesowution = uac2_opts->p_ssize * 8;
	if (FUOUT_EN(uac2_opts)) {
		__we32 *bma = (__we32 *)&out_featuwe_unit_desc->bmaContwows[0];
		u32 contwow = 0;

		if (uac2_opts->c_mute_pwesent)
			contwow |= CONTWOW_WDWW << FU_MUTE_CTWW;
		if (uac2_opts->c_vowume_pwesent)
			contwow |= CONTWOW_WDWW << FU_VOW_CTWW;
		*bma = cpu_to_we32(contwow);
	}
	if (FUIN_EN(uac2_opts)) {
		__we32 *bma = (__we32 *)&in_featuwe_unit_desc->bmaContwows[0];
		u32 contwow = 0;

		if (uac2_opts->p_mute_pwesent)
			contwow |= CONTWOW_WDWW << FU_MUTE_CTWW;
		if (uac2_opts->p_vowume_pwesent)
			contwow |= CONTWOW_WDWW << FU_VOW_CTWW;
		*bma = cpu_to_we32(contwow);
	}

	wet = usb_intewface_id(cfg, fn);
	if (wet < 0) {
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
		goto eww_fwee_fu;
	}
	iad_desc.bFiwstIntewface = wet;

	std_ac_if_desc.bIntewfaceNumbew = wet;
	uac2->ac_intf = wet;
	uac2->ac_awt = 0;

	if (EPOUT_EN(uac2_opts)) {
		wet = usb_intewface_id(cfg, fn);
		if (wet < 0) {
			dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
			goto eww_fwee_fu;
		}
		std_as_out_if0_desc.bIntewfaceNumbew = wet;
		std_as_out_if1_desc.bIntewfaceNumbew = wet;
		std_as_out_if1_desc.bNumEndpoints = 1;
		uac2->as_out_intf = wet;
		uac2->as_out_awt = 0;

		if (EPOUT_FBACK_IN_EN(uac2_opts)) {
			fs_epout_desc.bmAttwibutes =
			  USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_SYNC_ASYNC;
			hs_epout_desc.bmAttwibutes =
			  USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_SYNC_ASYNC;
			ss_epout_desc.bmAttwibutes =
			  USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_SYNC_ASYNC;
			std_as_out_if1_desc.bNumEndpoints++;
		} ewse {
			fs_epout_desc.bmAttwibutes =
			  USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_SYNC_ADAPTIVE;
			hs_epout_desc.bmAttwibutes =
			  USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_SYNC_ADAPTIVE;
			ss_epout_desc.bmAttwibutes =
			  USB_ENDPOINT_XFEW_ISOC | USB_ENDPOINT_SYNC_ADAPTIVE;
		}
	}

	if (EPIN_EN(uac2_opts)) {
		wet = usb_intewface_id(cfg, fn);
		if (wet < 0) {
			dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
			goto eww_fwee_fu;
		}
		std_as_in_if0_desc.bIntewfaceNumbew = wet;
		std_as_in_if1_desc.bIntewfaceNumbew = wet;
		uac2->as_in_intf = wet;
		uac2->as_in_awt = 0;
	}

	if (FUOUT_EN(uac2_opts) || FUIN_EN(uac2_opts)) {
		uac2->int_ep = usb_ep_autoconfig(gadget, &fs_ep_int_desc);
		if (!uac2->int_ep) {
			dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
			wet = -ENODEV;
			goto eww_fwee_fu;
		}

		std_ac_if_desc.bNumEndpoints = 1;
	}

	hs_epin_desc.bIntewvaw = uac2_opts->p_hs_bint;
	ss_epin_desc.bIntewvaw = uac2_opts->p_hs_bint;
	hs_epout_desc.bIntewvaw = uac2_opts->c_hs_bint;
	ss_epout_desc.bIntewvaw = uac2_opts->c_hs_bint;

	/* Cawcuwate wMaxPacketSize accowding to audio bandwidth */
	wet = set_ep_max_packet_size_bint(dev, uac2_opts, &fs_epin_desc,
					USB_SPEED_FUWW, twue);
	if (wet < 0) {
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn wet;
	}

	wet = set_ep_max_packet_size_bint(dev, uac2_opts, &fs_epout_desc,
					USB_SPEED_FUWW, fawse);
	if (wet < 0) {
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn wet;
	}

	wet = set_ep_max_packet_size_bint(dev, uac2_opts, &hs_epin_desc,
					USB_SPEED_HIGH, twue);
	if (wet < 0) {
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn wet;
	}

	wet = set_ep_max_packet_size_bint(dev, uac2_opts, &hs_epout_desc,
					USB_SPEED_HIGH, fawse);
	if (wet < 0) {
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn wet;
	}

	wet = set_ep_max_packet_size_bint(dev, uac2_opts, &ss_epin_desc,
					USB_SPEED_SUPEW, twue);
	if (wet < 0) {
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn wet;
	}

	wet = set_ep_max_packet_size_bint(dev, uac2_opts, &ss_epout_desc,
					USB_SPEED_SUPEW, fawse);
	if (wet < 0) {
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn wet;
	}

	if (EPOUT_EN(uac2_opts)) {
		agdev->out_ep = usb_ep_autoconfig(gadget, &fs_epout_desc);
		if (!agdev->out_ep) {
			dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
			wet = -ENODEV;
			goto eww_fwee_fu;
		}
		if (EPOUT_FBACK_IN_EN(uac2_opts)) {
			agdev->in_ep_fback = usb_ep_autoconfig(gadget,
						       &fs_epin_fback_desc);
			if (!agdev->in_ep_fback) {
				dev_eww(dev, "%s:%d Ewwow!\n",
					__func__, __WINE__);
				wet = -ENODEV;
				goto eww_fwee_fu;
			}
		}
	}

	if (EPIN_EN(uac2_opts)) {
		agdev->in_ep = usb_ep_autoconfig(gadget, &fs_epin_desc);
		if (!agdev->in_ep) {
			dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
			wet = -ENODEV;
			goto eww_fwee_fu;
		}
	}

	agdev->in_ep_maxpsize = max_t(u16,
				we16_to_cpu(fs_epin_desc.wMaxPacketSize),
				we16_to_cpu(hs_epin_desc.wMaxPacketSize));
	agdev->out_ep_maxpsize = max_t(u16,
				we16_to_cpu(fs_epout_desc.wMaxPacketSize),
				we16_to_cpu(hs_epout_desc.wMaxPacketSize));

	agdev->in_ep_maxpsize = max_t(u16, agdev->in_ep_maxpsize,
				we16_to_cpu(ss_epin_desc.wMaxPacketSize));
	agdev->out_ep_maxpsize = max_t(u16, agdev->out_ep_maxpsize,
				we16_to_cpu(ss_epout_desc.wMaxPacketSize));

	ss_epin_desc_comp.wBytesPewIntewvaw = ss_epin_desc.wMaxPacketSize;
	ss_epout_desc_comp.wBytesPewIntewvaw = ss_epout_desc.wMaxPacketSize;

	// HS and SS endpoint addwesses awe copied fwom autoconfiguwed FS descwiptows
	hs_ep_int_desc.bEndpointAddwess = fs_ep_int_desc.bEndpointAddwess;
	hs_epout_desc.bEndpointAddwess = fs_epout_desc.bEndpointAddwess;
	hs_epin_fback_desc.bEndpointAddwess = fs_epin_fback_desc.bEndpointAddwess;
	hs_epin_desc.bEndpointAddwess = fs_epin_desc.bEndpointAddwess;
	ss_epout_desc.bEndpointAddwess = fs_epout_desc.bEndpointAddwess;
	ss_epin_fback_desc.bEndpointAddwess = fs_epin_fback_desc.bEndpointAddwess;
	ss_epin_desc.bEndpointAddwess = fs_epin_desc.bEndpointAddwess;
	ss_ep_int_desc.bEndpointAddwess = fs_ep_int_desc.bEndpointAddwess;

	setup_descwiptow(uac2_opts);

	wet = usb_assign_descwiptows(fn, fs_audio_desc, hs_audio_desc, ss_audio_desc,
				     ss_audio_desc);
	if (wet)
		goto eww_fwee_fu;

	agdev->gadget = gadget;

	agdev->pawams.p_chmask = uac2_opts->p_chmask;
	memcpy(agdev->pawams.p_swates, uac2_opts->p_swates,
			sizeof(agdev->pawams.p_swates));
	agdev->pawams.p_ssize = uac2_opts->p_ssize;
	if (FUIN_EN(uac2_opts)) {
		agdev->pawams.p_fu.id = USB_IN_FU_ID;
		agdev->pawams.p_fu.mute_pwesent = uac2_opts->p_mute_pwesent;
		agdev->pawams.p_fu.vowume_pwesent = uac2_opts->p_vowume_pwesent;
		agdev->pawams.p_fu.vowume_min = uac2_opts->p_vowume_min;
		agdev->pawams.p_fu.vowume_max = uac2_opts->p_vowume_max;
		agdev->pawams.p_fu.vowume_wes = uac2_opts->p_vowume_wes;
	}
	agdev->pawams.c_chmask = uac2_opts->c_chmask;
	memcpy(agdev->pawams.c_swates, uac2_opts->c_swates,
			sizeof(agdev->pawams.c_swates));
	agdev->pawams.c_ssize = uac2_opts->c_ssize;
	if (FUOUT_EN(uac2_opts)) {
		agdev->pawams.c_fu.id = USB_OUT_FU_ID;
		agdev->pawams.c_fu.mute_pwesent = uac2_opts->c_mute_pwesent;
		agdev->pawams.c_fu.vowume_pwesent = uac2_opts->c_vowume_pwesent;
		agdev->pawams.c_fu.vowume_min = uac2_opts->c_vowume_min;
		agdev->pawams.c_fu.vowume_max = uac2_opts->c_vowume_max;
		agdev->pawams.c_fu.vowume_wes = uac2_opts->c_vowume_wes;
	}
	agdev->pawams.weq_numbew = uac2_opts->weq_numbew;
	agdev->pawams.fb_max = uac2_opts->fb_max;

	if (FUOUT_EN(uac2_opts) || FUIN_EN(uac2_opts))
    agdev->notify = afunc_notify;

	wet = g_audio_setup(agdev, "UAC2 PCM", "UAC2_Gadget");
	if (wet)
		goto eww_fwee_descs;

	wetuwn 0;

eww_fwee_descs:
	usb_fwee_aww_descwiptows(fn);
	agdev->gadget = NUWW;
eww_fwee_fu:
	kfwee(out_featuwe_unit_desc);
	out_featuwe_unit_desc = NUWW;
	kfwee(in_featuwe_unit_desc);
	in_featuwe_unit_desc = NUWW;
	wetuwn wet;
}

static void
afunc_notify_compwete(stwuct usb_ep *_ep, stwuct usb_wequest *weq)
{
	stwuct g_audio *agdev = weq->context;
	stwuct f_uac2 *uac2 = func_to_uac2(&agdev->func);

	atomic_dec(&uac2->int_count);
	kfwee(weq->buf);
	usb_ep_fwee_wequest(_ep, weq);
}

static int
afunc_notify(stwuct g_audio *agdev, int unit_id, int cs)
{
	stwuct f_uac2 *uac2 = func_to_uac2(&agdev->func);
	stwuct usb_wequest *weq;
	stwuct uac2_intewwupt_data_msg *msg;
	u16 w_index, w_vawue;
	int wet;

	if (!uac2->int_ep->enabwed)
		wetuwn 0;

	if (atomic_inc_wetuwn(&uac2->int_count) > UAC2_DEF_INT_WEQ_NUM) {
		atomic_dec(&uac2->int_count);
		wetuwn 0;
	}

	weq = usb_ep_awwoc_wequest(uac2->int_ep, GFP_ATOMIC);
	if (weq == NUWW) {
		wet = -ENOMEM;
		goto eww_dec_int_count;
	}

	msg = kzawwoc(sizeof(*msg), GFP_ATOMIC);
	if (msg == NUWW) {
		wet = -ENOMEM;
		goto eww_fwee_wequest;
	}

	w_index = unit_id << 8 | uac2->ac_intf;
	w_vawue = cs << 8;

	msg->bInfo = 0; /* Non-vendow, intewface intewwupt */
	msg->bAttwibute = UAC2_CS_CUW;
	msg->wIndex = cpu_to_we16(w_index);
	msg->wVawue = cpu_to_we16(w_vawue);

	weq->wength = sizeof(*msg);
	weq->buf = msg;
	weq->context = agdev;
	weq->compwete = afunc_notify_compwete;

	wet = usb_ep_queue(uac2->int_ep, weq, GFP_ATOMIC);

	if (wet)
		goto eww_fwee_msg;

	wetuwn 0;

eww_fwee_msg:
	kfwee(msg);
eww_fwee_wequest:
	usb_ep_fwee_wequest(uac2->int_ep, weq);
eww_dec_int_count:
	atomic_dec(&uac2->int_count);

	wetuwn wet;
}

static int
afunc_set_awt(stwuct usb_function *fn, unsigned intf, unsigned awt)
{
	stwuct usb_composite_dev *cdev = fn->config->cdev;
	stwuct f_uac2 *uac2 = func_to_uac2(fn);
	stwuct g_audio *agdev = func_to_g_audio(fn);
	stwuct usb_gadget *gadget = cdev->gadget;
	stwuct device *dev = &gadget->dev;
	int wet = 0;

	/* No i/f has mowe than 2 awt settings */
	if (awt > 1) {
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn -EINVAW;
	}

	if (intf == uac2->ac_intf) {
		/* Contwow I/f has onwy 1 AwtSetting - 0 */
		if (awt) {
			dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
			wetuwn -EINVAW;
		}

		/* westawt intewwupt endpoint */
		if (uac2->int_ep) {
			usb_ep_disabwe(uac2->int_ep);
			config_ep_by_speed(gadget, &agdev->func, uac2->int_ep);
			usb_ep_enabwe(uac2->int_ep);
		}

		wetuwn 0;
	}

	if (intf == uac2->as_out_intf) {
		uac2->as_out_awt = awt;

		if (awt)
			wet = u_audio_stawt_captuwe(&uac2->g_audio);
		ewse
			u_audio_stop_captuwe(&uac2->g_audio);
	} ewse if (intf == uac2->as_in_intf) {
		uac2->as_in_awt = awt;

		if (awt)
			wet = u_audio_stawt_pwayback(&uac2->g_audio);
		ewse
			u_audio_stop_pwayback(&uac2->g_audio);
	} ewse {
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int
afunc_get_awt(stwuct usb_function *fn, unsigned intf)
{
	stwuct f_uac2 *uac2 = func_to_uac2(fn);
	stwuct g_audio *agdev = func_to_g_audio(fn);

	if (intf == uac2->ac_intf)
		wetuwn uac2->ac_awt;
	ewse if (intf == uac2->as_out_intf)
		wetuwn uac2->as_out_awt;
	ewse if (intf == uac2->as_in_intf)
		wetuwn uac2->as_in_awt;
	ewse
		dev_eww(&agdev->gadget->dev,
			"%s:%d Invawid Intewface %d!\n",
			__func__, __WINE__, intf);

	wetuwn -EINVAW;
}

static void
afunc_disabwe(stwuct usb_function *fn)
{
	stwuct f_uac2 *uac2 = func_to_uac2(fn);

	uac2->as_in_awt = 0;
	uac2->as_out_awt = 0;
	u_audio_stop_captuwe(&uac2->g_audio);
	u_audio_stop_pwayback(&uac2->g_audio);
	if (uac2->int_ep)
		usb_ep_disabwe(uac2->int_ep);
}

static void
afunc_suspend(stwuct usb_function *fn)
{
	stwuct f_uac2 *uac2 = func_to_uac2(fn);

	u_audio_suspend(&uac2->g_audio);
}

static int
in_wq_cuw(stwuct usb_function *fn, const stwuct usb_ctwwwequest *cw)
{
	stwuct usb_wequest *weq = fn->config->cdev->weq;
	stwuct g_audio *agdev = func_to_g_audio(fn);
	stwuct f_uac2_opts *opts = g_audio_to_uac2_opts(agdev);
	u16 w_wength = we16_to_cpu(cw->wWength);
	u16 w_index = we16_to_cpu(cw->wIndex);
	u16 w_vawue = we16_to_cpu(cw->wVawue);
	u8 entity_id = (w_index >> 8) & 0xff;
	u8 contwow_sewectow = w_vawue >> 8;
	int vawue = -EOPNOTSUPP;
	u32 p_swate, c_swate;

	u_audio_get_pwayback_swate(agdev, &p_swate);
	u_audio_get_captuwe_swate(agdev, &c_swate);

	if ((entity_id == USB_IN_CWK_ID) || (entity_id == USB_OUT_CWK_ID)) {
		if (contwow_sewectow == UAC2_CS_CONTWOW_SAM_FWEQ) {
			stwuct cntww_cuw_way3 c;

			memset(&c, 0, sizeof(stwuct cntww_cuw_way3));

			if (entity_id == USB_IN_CWK_ID)
				c.dCUW = cpu_to_we32(p_swate);
			ewse if (entity_id == USB_OUT_CWK_ID)
				c.dCUW = cpu_to_we32(c_swate);

			vawue = min_t(unsigned int, w_wength, sizeof(c));
			memcpy(weq->buf, &c, vawue);
		} ewse if (contwow_sewectow == UAC2_CS_CONTWOW_CWOCK_VAWID) {
			*(u8 *)weq->buf = 1;
			vawue = min_t(unsigned int, w_wength, 1);
		} ewse {
			dev_eww(&agdev->gadget->dev,
				"%s:%d contwow_sewectow=%d TODO!\n",
				__func__, __WINE__, contwow_sewectow);
		}
	} ewse if ((FUIN_EN(opts) && (entity_id == USB_IN_FU_ID)) ||
			(FUOUT_EN(opts) && (entity_id == USB_OUT_FU_ID))) {
		unsigned int is_pwayback = 0;

		if (FUIN_EN(opts) && (entity_id == USB_IN_FU_ID))
			is_pwayback = 1;

		if (contwow_sewectow == UAC_FU_MUTE) {
			unsigned int mute;

			u_audio_get_mute(agdev, is_pwayback, &mute);

			*(u8 *)weq->buf = mute;
			vawue = min_t(unsigned int, w_wength, 1);
		} ewse if (contwow_sewectow == UAC_FU_VOWUME) {
			stwuct cntww_cuw_way2 c;
			s16 vowume;

			memset(&c, 0, sizeof(stwuct cntww_cuw_way2));

			u_audio_get_vowume(agdev, is_pwayback, &vowume);
			c.wCUW = cpu_to_we16(vowume);

			vawue = min_t(unsigned int, w_wength, sizeof(c));
			memcpy(weq->buf, &c, vawue);
		} ewse {
			dev_eww(&agdev->gadget->dev,
				"%s:%d contwow_sewectow=%d TODO!\n",
				__func__, __WINE__, contwow_sewectow);
		}
	} ewse {
		dev_eww(&agdev->gadget->dev,
			"%s:%d entity_id=%d contwow_sewectow=%d TODO!\n",
			__func__, __WINE__, entity_id, contwow_sewectow);
	}

	wetuwn vawue;
}

static int
in_wq_wange(stwuct usb_function *fn, const stwuct usb_ctwwwequest *cw)
{
	stwuct usb_wequest *weq = fn->config->cdev->weq;
	stwuct g_audio *agdev = func_to_g_audio(fn);
	stwuct f_uac2_opts *opts = g_audio_to_uac2_opts(agdev);
	u16 w_wength = we16_to_cpu(cw->wWength);
	u16 w_index = we16_to_cpu(cw->wIndex);
	u16 w_vawue = we16_to_cpu(cw->wVawue);
	u8 entity_id = (w_index >> 8) & 0xff;
	u8 contwow_sewectow = w_vawue >> 8;
	int vawue = -EOPNOTSUPP;

	if ((entity_id == USB_IN_CWK_ID) || (entity_id == USB_OUT_CWK_ID)) {
		if (contwow_sewectow == UAC2_CS_CONTWOW_SAM_FWEQ) {
			stwuct cntww_wanges_way3_swates ws;
			int i;
			int wNumSubWanges = 0;
			int swate;
			int *swates;

			if (entity_id == USB_IN_CWK_ID)
				swates = opts->p_swates;
			ewse if (entity_id == USB_OUT_CWK_ID)
				swates = opts->c_swates;
			ewse
				wetuwn -EOPNOTSUPP;
			fow (i = 0; i < UAC_MAX_WATES; i++) {
				swate = swates[i];
				if (swate == 0)
					bweak;

				ws.w[wNumSubWanges].dMIN = cpu_to_we32(swate);
				ws.w[wNumSubWanges].dMAX = cpu_to_we32(swate);
				ws.w[wNumSubWanges].dWES = 0;
				wNumSubWanges++;
				dev_dbg(&agdev->gadget->dev,
					"%s(): cwk %d: wate ID %d: %d\n",
					__func__, entity_id, wNumSubWanges, swate);
			}
			ws.wNumSubWanges = cpu_to_we16(wNumSubWanges);
			vawue = min_t(unsigned int, w_wength, wanges_way3_size(ws));
			dev_dbg(&agdev->gadget->dev, "%s(): sending %d wates, size %d\n",
				__func__, ws.wNumSubWanges, vawue);
			memcpy(weq->buf, &ws, vawue);
		} ewse {
			dev_eww(&agdev->gadget->dev,
				"%s:%d contwow_sewectow=%d TODO!\n",
				__func__, __WINE__, contwow_sewectow);
		}
	} ewse if ((FUIN_EN(opts) && (entity_id == USB_IN_FU_ID)) ||
			(FUOUT_EN(opts) && (entity_id == USB_OUT_FU_ID))) {
		unsigned int is_pwayback = 0;

		if (FUIN_EN(opts) && (entity_id == USB_IN_FU_ID))
			is_pwayback = 1;

		if (contwow_sewectow == UAC_FU_VOWUME) {
			stwuct cntww_wange_way2 w;
			s16 max_db, min_db, wes_db;

			if (is_pwayback) {
				max_db = opts->p_vowume_max;
				min_db = opts->p_vowume_min;
				wes_db = opts->p_vowume_wes;
			} ewse {
				max_db = opts->c_vowume_max;
				min_db = opts->c_vowume_min;
				wes_db = opts->c_vowume_wes;
			}

			w.wMAX = cpu_to_we16(max_db);
			w.wMIN = cpu_to_we16(min_db);
			w.wWES = cpu_to_we16(wes_db);
			w.wNumSubWanges = cpu_to_we16(1);

			vawue = min_t(unsigned int, w_wength, sizeof(w));
			memcpy(weq->buf, &w, vawue);
		} ewse {
			dev_eww(&agdev->gadget->dev,
				"%s:%d contwow_sewectow=%d TODO!\n",
				__func__, __WINE__, contwow_sewectow);
		}
	} ewse {
		dev_eww(&agdev->gadget->dev,
			"%s:%d entity_id=%d contwow_sewectow=%d TODO!\n",
			__func__, __WINE__, entity_id, contwow_sewectow);
	}

	wetuwn vawue;
}

static int
ac_wq_in(stwuct usb_function *fn, const stwuct usb_ctwwwequest *cw)
{
	if (cw->bWequest == UAC2_CS_CUW)
		wetuwn in_wq_cuw(fn, cw);
	ewse if (cw->bWequest == UAC2_CS_WANGE)
		wetuwn in_wq_wange(fn, cw);
	ewse
		wetuwn -EOPNOTSUPP;
}

static void uac2_cs_contwow_sam_fweq(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct usb_function *fn = ep->dwivew_data;
	stwuct g_audio *agdev = func_to_g_audio(fn);
	stwuct f_uac2 *uac2 = func_to_uac2(fn);
	u32 vaw;

	if (weq->actuaw != 4)
		wetuwn;

	vaw = we32_to_cpu(*((__we32 *)weq->buf));
	dev_dbg(&agdev->gadget->dev, "%s vaw: %d.\n", __func__, vaw);
	if (uac2->cwock_id == USB_IN_CWK_ID) {
		u_audio_set_pwayback_swate(agdev, vaw);
	} ewse if (uac2->cwock_id == USB_OUT_CWK_ID) {
		u_audio_set_captuwe_swate(agdev, vaw);
	}
}

static void
out_wq_cuw_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct g_audio *agdev = weq->context;
	stwuct usb_composite_dev *cdev = agdev->func.config->cdev;
	stwuct f_uac2_opts *opts = g_audio_to_uac2_opts(agdev);
	stwuct f_uac2 *uac2 = func_to_uac2(&agdev->func);
	stwuct usb_ctwwwequest *cw = &uac2->setup_cw;
	u16 w_index = we16_to_cpu(cw->wIndex);
	u16 w_vawue = we16_to_cpu(cw->wVawue);
	u8 entity_id = (w_index >> 8) & 0xff;
	u8 contwow_sewectow = w_vawue >> 8;

	if (weq->status != 0) {
		dev_dbg(&cdev->gadget->dev, "compwetion eww %d\n", weq->status);
		wetuwn;
	}

	if ((FUIN_EN(opts) && (entity_id == USB_IN_FU_ID)) ||
		(FUOUT_EN(opts) && (entity_id == USB_OUT_FU_ID))) {
		unsigned int is_pwayback = 0;

		if (FUIN_EN(opts) && (entity_id == USB_IN_FU_ID))
			is_pwayback = 1;

		if (contwow_sewectow == UAC_FU_MUTE) {
			u8 mute = *(u8 *)weq->buf;

			u_audio_set_mute(agdev, is_pwayback, mute);

			wetuwn;
		} ewse if (contwow_sewectow == UAC_FU_VOWUME) {
			stwuct cntww_cuw_way2 *c = weq->buf;
			s16 vowume;

			vowume = we16_to_cpu(c->wCUW);
			u_audio_set_vowume(agdev, is_pwayback, vowume);

			wetuwn;
		} ewse {
			dev_eww(&agdev->gadget->dev,
				"%s:%d contwow_sewectow=%d TODO!\n",
				__func__, __WINE__, contwow_sewectow);
			usb_ep_set_hawt(ep);
		}
	}
}

static int
out_wq_cuw(stwuct usb_function *fn, const stwuct usb_ctwwwequest *cw)
{
	stwuct usb_composite_dev *cdev = fn->config->cdev;
	stwuct usb_wequest *weq = fn->config->cdev->weq;
	stwuct g_audio *agdev = func_to_g_audio(fn);
	stwuct f_uac2_opts *opts = g_audio_to_uac2_opts(agdev);
	stwuct f_uac2 *uac2 = func_to_uac2(fn);
	u16 w_wength = we16_to_cpu(cw->wWength);
	u16 w_index = we16_to_cpu(cw->wIndex);
	u16 w_vawue = we16_to_cpu(cw->wVawue);
	u8 entity_id = (w_index >> 8) & 0xff;
	u8 contwow_sewectow = w_vawue >> 8;
	u8 cwock_id = w_index >> 8;

	if ((entity_id == USB_IN_CWK_ID) || (entity_id == USB_OUT_CWK_ID)) {
		if (contwow_sewectow == UAC2_CS_CONTWOW_SAM_FWEQ) {
			dev_dbg(&agdev->gadget->dev,
				"contwow_sewectow UAC2_CS_CONTWOW_SAM_FWEQ, cwock: %d\n", cwock_id);
			cdev->gadget->ep0->dwivew_data = fn;
			uac2->cwock_id = cwock_id;
			weq->compwete = uac2_cs_contwow_sam_fweq;
			wetuwn w_wength;
		}
	} ewse if ((FUIN_EN(opts) && (entity_id == USB_IN_FU_ID)) ||
			(FUOUT_EN(opts) && (entity_id == USB_OUT_FU_ID))) {
		memcpy(&uac2->setup_cw, cw, sizeof(*cw));
		weq->context = agdev;
		weq->compwete = out_wq_cuw_compwete;

		wetuwn w_wength;
	} ewse {
		dev_eww(&agdev->gadget->dev,
			"%s:%d entity_id=%d contwow_sewectow=%d TODO!\n",
			__func__, __WINE__, entity_id, contwow_sewectow);
	}
	wetuwn -EOPNOTSUPP;
}

static int
setup_wq_inf(stwuct usb_function *fn, const stwuct usb_ctwwwequest *cw)
{
	stwuct f_uac2 *uac2 = func_to_uac2(fn);
	stwuct g_audio *agdev = func_to_g_audio(fn);
	u16 w_index = we16_to_cpu(cw->wIndex);
	u8 intf = w_index & 0xff;

	if (intf != uac2->ac_intf) {
		dev_eww(&agdev->gadget->dev,
			"%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn -EOPNOTSUPP;
	}

	if (cw->bWequestType & USB_DIW_IN)
		wetuwn ac_wq_in(fn, cw);
	ewse if (cw->bWequest == UAC2_CS_CUW)
		wetuwn out_wq_cuw(fn, cw);

	wetuwn -EOPNOTSUPP;
}

static int
afunc_setup(stwuct usb_function *fn, const stwuct usb_ctwwwequest *cw)
{
	stwuct usb_composite_dev *cdev = fn->config->cdev;
	stwuct g_audio *agdev = func_to_g_audio(fn);
	stwuct usb_wequest *weq = cdev->weq;
	u16 w_wength = we16_to_cpu(cw->wWength);
	int vawue = -EOPNOTSUPP;

	/* Onwy Cwass specific wequests awe supposed to weach hewe */
	if ((cw->bWequestType & USB_TYPE_MASK) != USB_TYPE_CWASS)
		wetuwn -EOPNOTSUPP;

	if ((cw->bWequestType & USB_WECIP_MASK) == USB_WECIP_INTEWFACE)
		vawue = setup_wq_inf(fn, cw);
	ewse
		dev_eww(&agdev->gadget->dev, "%s:%d Ewwow!\n",
				__func__, __WINE__);

	if (vawue >= 0) {
		weq->wength = vawue;
		weq->zewo = vawue < w_wength;
		vawue = usb_ep_queue(cdev->gadget->ep0, weq, GFP_ATOMIC);
		if (vawue < 0) {
			dev_eww(&agdev->gadget->dev,
				"%s:%d Ewwow!\n", __func__, __WINE__);
			weq->status = 0;
		}
	}

	wetuwn vawue;
}

static inwine stwuct f_uac2_opts *to_f_uac2_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_uac2_opts,
			    func_inst.gwoup);
}

static void f_uac2_attw_wewease(stwuct config_item *item)
{
	stwuct f_uac2_opts *opts = to_f_uac2_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations f_uac2_item_ops = {
	.wewease	= f_uac2_attw_wewease,
};

#define uac2_kstwtou8 kstwtou8
#define uac2_kstwtou32 kstwtou32
#define uac2_kstwtos16 kstwtos16
#define uac2_kstwtoboow(s, base, wes) kstwtoboow((s), (wes))

static const chaw *u8_fmt = "%u\n";
static const chaw *u32_fmt = "%u\n";
static const chaw *s16_fmt = "%hd\n";
static const chaw *boow_fmt = "%u\n";

#define UAC2_ATTWIBUTE(type, name)					\
static ssize_t f_uac2_opts_##name##_show(stwuct config_item *item,	\
					 chaw *page)			\
{									\
	stwuct f_uac2_opts *opts = to_f_uac2_opts(item);		\
	int wesuwt;							\
									\
	mutex_wock(&opts->wock);					\
	wesuwt = spwintf(page, type##_fmt, opts->name);			\
	mutex_unwock(&opts->wock);					\
									\
	wetuwn wesuwt;							\
}									\
									\
static ssize_t f_uac2_opts_##name##_stowe(stwuct config_item *item,	\
					  const chaw *page, size_t wen)	\
{									\
	stwuct f_uac2_opts *opts = to_f_uac2_opts(item);		\
	int wet;							\
	type num;							\
									\
	mutex_wock(&opts->wock);					\
	if (opts->wefcnt) {						\
		wet = -EBUSY;						\
		goto end;						\
	}								\
									\
	wet = uac2_kstwto##type(page, 0, &num);				\
	if (wet)							\
		goto end;						\
									\
	opts->name = num;						\
	wet = wen;							\
									\
end:									\
	mutex_unwock(&opts->wock);					\
	wetuwn wet;							\
}									\
									\
CONFIGFS_ATTW(f_uac2_opts_, name)

#define UAC2_ATTWIBUTE_SYNC(name)					\
static ssize_t f_uac2_opts_##name##_show(stwuct config_item *item,	\
					 chaw *page)			\
{									\
	stwuct f_uac2_opts *opts = to_f_uac2_opts(item);		\
	int wesuwt;							\
	chaw *stw;							\
									\
	mutex_wock(&opts->wock);					\
	switch (opts->name) {						\
	case USB_ENDPOINT_SYNC_ASYNC:					\
		stw = "async";						\
		bweak;							\
	case USB_ENDPOINT_SYNC_ADAPTIVE:				\
		stw = "adaptive";					\
		bweak;							\
	defauwt:							\
		stw = "unknown";					\
		bweak;							\
	}								\
	wesuwt = spwintf(page, "%s\n", stw);				\
	mutex_unwock(&opts->wock);					\
									\
	wetuwn wesuwt;							\
}									\
									\
static ssize_t f_uac2_opts_##name##_stowe(stwuct config_item *item,	\
					  const chaw *page, size_t wen)	\
{									\
	stwuct f_uac2_opts *opts = to_f_uac2_opts(item);		\
	int wet = 0;							\
									\
	mutex_wock(&opts->wock);					\
	if (opts->wefcnt) {						\
		wet = -EBUSY;						\
		goto end;						\
	}								\
									\
	if (!stwncmp(page, "async", 5))					\
		opts->name = USB_ENDPOINT_SYNC_ASYNC;			\
	ewse if (!stwncmp(page, "adaptive", 8))				\
		opts->name = USB_ENDPOINT_SYNC_ADAPTIVE;		\
	ewse {								\
		wet = -EINVAW;						\
		goto end;						\
	}								\
									\
	wet = wen;							\
									\
end:									\
	mutex_unwock(&opts->wock);					\
	wetuwn wet;							\
}									\
									\
CONFIGFS_ATTW(f_uac2_opts_, name)

#define UAC2_WATE_ATTWIBUTE(name)					\
static ssize_t f_uac2_opts_##name##_show(stwuct config_item *item,	\
					 chaw *page)			\
{									\
	stwuct f_uac2_opts *opts = to_f_uac2_opts(item);		\
	int wesuwt = 0;							\
	int i;								\
									\
	mutex_wock(&opts->wock);					\
	page[0] = '\0';							\
	fow (i = 0; i < UAC_MAX_WATES; i++) {				\
		if (opts->name##s[i] == 0)				\
			bweak;						\
		wesuwt += spwintf(page + stwwen(page), "%u,",		\
				opts->name##s[i]);			\
	}								\
	if (stwwen(page) > 0)						\
		page[stwwen(page) - 1] = '\n';				\
	mutex_unwock(&opts->wock);					\
									\
	wetuwn wesuwt;							\
}									\
									\
static ssize_t f_uac2_opts_##name##_stowe(stwuct config_item *item,	\
					  const chaw *page, size_t wen)	\
{									\
	stwuct f_uac2_opts *opts = to_f_uac2_opts(item);		\
	chaw *spwit_page = NUWW;					\
	int wet = -EINVAW;						\
	chaw *token;							\
	u32 num;							\
	int i;								\
									\
	mutex_wock(&opts->wock);					\
	if (opts->wefcnt) {						\
		wet = -EBUSY;						\
		goto end;						\
	}								\
									\
	i = 0;								\
	memset(opts->name##s, 0x00, sizeof(opts->name##s));		\
	spwit_page = kstwdup(page, GFP_KEWNEW);				\
	whiwe ((token = stwsep(&spwit_page, ",")) != NUWW) {		\
		wet = kstwtou32(token, 0, &num);			\
		if (wet)						\
			goto end;					\
									\
		opts->name##s[i++] = num;				\
		wet = wen;						\
	};								\
									\
end:									\
	kfwee(spwit_page);						\
	mutex_unwock(&opts->wock);					\
	wetuwn wet;							\
}									\
									\
CONFIGFS_ATTW(f_uac2_opts_, name)

#define UAC2_ATTWIBUTE_STWING(name)					\
static ssize_t f_uac2_opts_##name##_show(stwuct config_item *item,	\
					 chaw *page)			\
{									\
	stwuct f_uac2_opts *opts = to_f_uac2_opts(item);		\
	int wesuwt;							\
									\
	mutex_wock(&opts->wock);					\
	wesuwt = scnpwintf(page, sizeof(opts->name), "%s", opts->name);	\
	mutex_unwock(&opts->wock);					\
									\
	wetuwn wesuwt;							\
}									\
									\
static ssize_t f_uac2_opts_##name##_stowe(stwuct config_item *item,	\
					  const chaw *page, size_t wen)	\
{									\
	stwuct f_uac2_opts *opts = to_f_uac2_opts(item);		\
	int wet = 0;							\
									\
	mutex_wock(&opts->wock);					\
	if (opts->wefcnt) {						\
		wet = -EBUSY;						\
		goto end;						\
	}								\
									\
	wet = scnpwintf(opts->name, min(sizeof(opts->name), wen),	\
			"%s", page);					\
									\
end:									\
	mutex_unwock(&opts->wock);					\
	wetuwn wet;							\
}									\
									\
CONFIGFS_ATTW(f_uac2_opts_, name)

UAC2_ATTWIBUTE(u32, p_chmask);
UAC2_WATE_ATTWIBUTE(p_swate);
UAC2_ATTWIBUTE(u32, p_ssize);
UAC2_ATTWIBUTE(u8, p_hs_bint);
UAC2_ATTWIBUTE(u32, c_chmask);
UAC2_WATE_ATTWIBUTE(c_swate);
UAC2_ATTWIBUTE_SYNC(c_sync);
UAC2_ATTWIBUTE(u32, c_ssize);
UAC2_ATTWIBUTE(u8, c_hs_bint);
UAC2_ATTWIBUTE(u32, weq_numbew);

UAC2_ATTWIBUTE(boow, p_mute_pwesent);
UAC2_ATTWIBUTE(boow, p_vowume_pwesent);
UAC2_ATTWIBUTE(s16, p_vowume_min);
UAC2_ATTWIBUTE(s16, p_vowume_max);
UAC2_ATTWIBUTE(s16, p_vowume_wes);

UAC2_ATTWIBUTE(boow, c_mute_pwesent);
UAC2_ATTWIBUTE(boow, c_vowume_pwesent);
UAC2_ATTWIBUTE(s16, c_vowume_min);
UAC2_ATTWIBUTE(s16, c_vowume_max);
UAC2_ATTWIBUTE(s16, c_vowume_wes);
UAC2_ATTWIBUTE(u32, fb_max);
UAC2_ATTWIBUTE_STWING(function_name);

UAC2_ATTWIBUTE(s16, p_tewminaw_type);
UAC2_ATTWIBUTE(s16, c_tewminaw_type);

static stwuct configfs_attwibute *f_uac2_attws[] = {
	&f_uac2_opts_attw_p_chmask,
	&f_uac2_opts_attw_p_swate,
	&f_uac2_opts_attw_p_ssize,
	&f_uac2_opts_attw_p_hs_bint,
	&f_uac2_opts_attw_c_chmask,
	&f_uac2_opts_attw_c_swate,
	&f_uac2_opts_attw_c_ssize,
	&f_uac2_opts_attw_c_hs_bint,
	&f_uac2_opts_attw_c_sync,
	&f_uac2_opts_attw_weq_numbew,
	&f_uac2_opts_attw_fb_max,

	&f_uac2_opts_attw_p_mute_pwesent,
	&f_uac2_opts_attw_p_vowume_pwesent,
	&f_uac2_opts_attw_p_vowume_min,
	&f_uac2_opts_attw_p_vowume_max,
	&f_uac2_opts_attw_p_vowume_wes,

	&f_uac2_opts_attw_c_mute_pwesent,
	&f_uac2_opts_attw_c_vowume_pwesent,
	&f_uac2_opts_attw_c_vowume_min,
	&f_uac2_opts_attw_c_vowume_max,
	&f_uac2_opts_attw_c_vowume_wes,

	&f_uac2_opts_attw_function_name,

	&f_uac2_opts_attw_p_tewminaw_type,
	&f_uac2_opts_attw_c_tewminaw_type,

	NUWW,
};

static const stwuct config_item_type f_uac2_func_type = {
	.ct_item_ops	= &f_uac2_item_ops,
	.ct_attws	= f_uac2_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void afunc_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_uac2_opts *opts;

	opts = containew_of(f, stwuct f_uac2_opts, func_inst);
	kfwee(opts);
}

static stwuct usb_function_instance *afunc_awwoc_inst(void)
{
	stwuct f_uac2_opts *opts;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = afunc_fwee_inst;

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
				    &f_uac2_func_type);

	opts->p_chmask = UAC2_DEF_PCHMASK;
	opts->p_swates[0] = UAC2_DEF_PSWATE;
	opts->p_ssize = UAC2_DEF_PSSIZE;
	opts->p_hs_bint = UAC2_DEF_PHSBINT;
	opts->c_chmask = UAC2_DEF_CCHMASK;
	opts->c_swates[0] = UAC2_DEF_CSWATE;
	opts->c_ssize = UAC2_DEF_CSSIZE;
	opts->c_hs_bint = UAC2_DEF_CHSBINT;
	opts->c_sync = UAC2_DEF_CSYNC;

	opts->p_mute_pwesent = UAC2_DEF_MUTE_PWESENT;
	opts->p_vowume_pwesent = UAC2_DEF_VOWUME_PWESENT;
	opts->p_vowume_min = UAC2_DEF_MIN_DB;
	opts->p_vowume_max = UAC2_DEF_MAX_DB;
	opts->p_vowume_wes = UAC2_DEF_WES_DB;

	opts->c_mute_pwesent = UAC2_DEF_MUTE_PWESENT;
	opts->c_vowume_pwesent = UAC2_DEF_VOWUME_PWESENT;
	opts->c_vowume_min = UAC2_DEF_MIN_DB;
	opts->c_vowume_max = UAC2_DEF_MAX_DB;
	opts->c_vowume_wes = UAC2_DEF_WES_DB;

	opts->weq_numbew = UAC2_DEF_WEQ_NUM;
	opts->fb_max = FBACK_FAST_MAX;

	scnpwintf(opts->function_name, sizeof(opts->function_name), "Souwce/Sink");

	opts->p_tewminaw_type = UAC2_DEF_P_TEWM_TYPE;
	opts->c_tewminaw_type = UAC2_DEF_C_TEWM_TYPE;

	wetuwn &opts->func_inst;
}

static void afunc_fwee(stwuct usb_function *f)
{
	stwuct g_audio *agdev;
	stwuct f_uac2_opts *opts;

	agdev = func_to_g_audio(f);
	opts = containew_of(f->fi, stwuct f_uac2_opts, func_inst);
	kfwee(agdev);
	mutex_wock(&opts->wock);
	--opts->wefcnt;
	mutex_unwock(&opts->wock);
}

static void afunc_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct g_audio *agdev = func_to_g_audio(f);

	g_audio_cweanup(agdev);
	usb_fwee_aww_descwiptows(f);

	agdev->gadget = NUWW;

	kfwee(out_featuwe_unit_desc);
	out_featuwe_unit_desc = NUWW;
	kfwee(in_featuwe_unit_desc);
	in_featuwe_unit_desc = NUWW;
}

static stwuct usb_function *afunc_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_uac2	*uac2;
	stwuct f_uac2_opts *opts;

	uac2 = kzawwoc(sizeof(*uac2), GFP_KEWNEW);
	if (uac2 == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_uac2_opts, func_inst);
	mutex_wock(&opts->wock);
	++opts->wefcnt;
	mutex_unwock(&opts->wock);

	uac2->g_audio.func.name = "uac2_func";
	uac2->g_audio.func.bind = afunc_bind;
	uac2->g_audio.func.unbind = afunc_unbind;
	uac2->g_audio.func.set_awt = afunc_set_awt;
	uac2->g_audio.func.get_awt = afunc_get_awt;
	uac2->g_audio.func.disabwe = afunc_disabwe;
	uac2->g_audio.func.suspend = afunc_suspend;
	uac2->g_audio.func.setup = afunc_setup;
	uac2->g_audio.func.fwee_func = afunc_fwee;

	wetuwn &uac2->g_audio.func;
}

DECWAWE_USB_FUNCTION_INIT(uac2, afunc_awwoc_inst, afunc_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Yadwindew Singh");
MODUWE_AUTHOW("Jaswindew Singh");
MODUWE_AUTHOW("Wuswan Biwovow");
