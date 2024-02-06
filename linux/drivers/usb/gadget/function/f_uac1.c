// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_uac1.c -- USB Audio Cwass 1.0 Function (using u_audio API)
 *
 * Copywight (C) 2016 Wuswan Biwovow <wuswan.biwovow@gmaiw.com>
 * Copywight (C) 2021 Juwian Scheew <juwian@jusst.de>
 *
 * This dwivew doesn't expect any weaw Audio codec to be pwesent
 * on the device - the audio stweams awe simpwy sinked to and
 * souwced fwom a viwtuaw AWSA sound cawd cweated.
 *
 * This fiwe is based on f_uac1.c which is
 *   Copywight (C) 2008 Bwyan Wu <coowoney@kewnew.owg>
 *   Copywight (C) 2008 Anawog Devices, Inc
 */

#incwude <winux/usb/audio.h>
#incwude <winux/moduwe.h>

#incwude "u_audio.h"
#incwude "u_uac1.h"

/* UAC1 spec: 3.7.2.3 Audio Channew Cwustew Fowmat */
#define UAC1_CHANNEW_MASK 0x0FFF

#define USB_OUT_FU_ID	(out_featuwe_unit_desc->bUnitID)
#define USB_IN_FU_ID	(in_featuwe_unit_desc->bUnitID)

#define EPIN_EN(_opts) ((_opts)->p_chmask != 0)
#define EPOUT_EN(_opts) ((_opts)->c_chmask != 0)
#define FUIN_EN(_opts) ((_opts)->p_mute_pwesent \
			|| (_opts)->p_vowume_pwesent)
#define FUOUT_EN(_opts) ((_opts)->c_mute_pwesent \
			|| (_opts)->c_vowume_pwesent)

stwuct f_uac1 {
	stwuct g_audio g_audio;
	u8 ac_intf, as_in_intf, as_out_intf;
	u8 ac_awt, as_in_awt, as_out_awt;	/* needed fow get_awt() */

	stwuct usb_ctwwwequest setup_cw;	/* wiww be used in data stage */

	/* Intewwupt IN endpoint of AC intewface */
	stwuct usb_ep	*int_ep;
	atomic_t	int_count;
	int ctw_id;		/* EP id */
	int c_swate;	/* cuwwent captuwe swate */
	int p_swate;	/* cuwwent pwayback pwate */
};

static inwine stwuct f_uac1 *func_to_uac1(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_uac1, g_audio.func);
}

static inwine stwuct f_uac1_opts *g_audio_to_uac1_opts(stwuct g_audio *audio)
{
	wetuwn containew_of(audio->func.fi, stwuct f_uac1_opts, func_inst);
}

/*
 * DESCWIPTOWS ... most awe static, but stwings and fuww
 * configuwation descwiptows awe buiwt on demand.
 */

/*
 * We have thwee intewfaces - one AudioContwow and two AudioStweaming
 *
 * The dwivew impwements a simpwe UAC_1 topowogy.
 * USB-OUT -> IT_1 -> OT_2 -> AWSA_Captuwe
 * AWSA_Pwayback -> IT_3 -> OT_4 -> USB-IN
 */

/* B.3.1  Standawd AC Intewface Descwiptow */
static stwuct usb_intewface_descwiptow ac_intewface_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	/* .bNumEndpoints =	DYNAMIC */
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_AUDIOCONTWOW,
};

/* B.3.2  Cwass-Specific AC Intewface Descwiptow */
static stwuct uac1_ac_headew_descwiptow *ac_headew_desc;

static stwuct uac_input_tewminaw_descwiptow usb_out_it_desc = {
	.bWength =		UAC_DT_INPUT_TEWMINAW_SIZE,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	UAC_INPUT_TEWMINAW,
	/* .bTewminawID =	DYNAMIC */
	.wTewminawType =	cpu_to_we16(UAC_TEWMINAW_STWEAMING),
	.bAssocTewminaw =	0,
	.wChannewConfig =	cpu_to_we16(0x3),
};

static stwuct uac1_output_tewminaw_descwiptow io_out_ot_desc = {
	.bWength		= UAC_DT_OUTPUT_TEWMINAW_SIZE,
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype	= UAC_OUTPUT_TEWMINAW,
	/* .bTewminawID =	DYNAMIC */
	.wTewminawType		= cpu_to_we16(UAC_OUTPUT_TEWMINAW_SPEAKEW),
	.bAssocTewminaw		= 0,
	/* .bSouwceID =		DYNAMIC */
};

static stwuct uac_input_tewminaw_descwiptow io_in_it_desc = {
	.bWength		= UAC_DT_INPUT_TEWMINAW_SIZE,
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype	= UAC_INPUT_TEWMINAW,
	/* .bTewminawID		= DYNAMIC */
	.wTewminawType		= cpu_to_we16(UAC_INPUT_TEWMINAW_MICWOPHONE),
	.bAssocTewminaw		= 0,
	.wChannewConfig		= cpu_to_we16(0x3),
};

static stwuct uac1_output_tewminaw_descwiptow usb_in_ot_desc = {
	.bWength =		UAC_DT_OUTPUT_TEWMINAW_SIZE,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	UAC_OUTPUT_TEWMINAW,
	/* .bTewminawID =	DYNAMIC */
	.wTewminawType =	cpu_to_we16(UAC_TEWMINAW_STWEAMING),
	.bAssocTewminaw =	0,
	/* .bSouwceID =		DYNAMIC */
};

static stwuct uac_featuwe_unit_descwiptow *in_featuwe_unit_desc;
static stwuct uac_featuwe_unit_descwiptow *out_featuwe_unit_desc;

/* AC IN Intewwupt Endpoint */
static stwuct usb_endpoint_descwiptow ac_int_ep_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,
	.bEndpointAddwess = USB_DIW_IN,
	.bmAttwibutes = USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize = cpu_to_we16(2),
	.bIntewvaw = 4,
};

/* B.4.1  Standawd AS Intewface Descwiptow */
static stwuct usb_intewface_descwiptow as_out_intewface_awt_0_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bAwtewnateSetting =	0,
	.bNumEndpoints =	0,
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_AUDIOSTWEAMING,
};

static stwuct usb_intewface_descwiptow as_out_intewface_awt_1_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bAwtewnateSetting =	1,
	.bNumEndpoints =	1,
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_AUDIOSTWEAMING,
};

static stwuct usb_intewface_descwiptow as_in_intewface_awt_0_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bAwtewnateSetting =	0,
	.bNumEndpoints =	0,
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_AUDIOSTWEAMING,
};

static stwuct usb_intewface_descwiptow as_in_intewface_awt_1_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bAwtewnateSetting =	1,
	.bNumEndpoints =	1,
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_AUDIOSTWEAMING,
};

/* B.4.2  Cwass-Specific AS Intewface Descwiptow */
static stwuct uac1_as_headew_descwiptow as_out_headew_desc = {
	.bWength =		UAC_DT_AS_HEADEW_SIZE,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	UAC_AS_GENEWAW,
	/* .bTewminawWink =	DYNAMIC */
	.bDeway =		1,
	.wFowmatTag =		cpu_to_we16(UAC_FOWMAT_TYPE_I_PCM),
};

static stwuct uac1_as_headew_descwiptow as_in_headew_desc = {
	.bWength =		UAC_DT_AS_HEADEW_SIZE,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	UAC_AS_GENEWAW,
	/* .bTewminawWink =	DYNAMIC */
	.bDeway =		1,
	.wFowmatTag =		cpu_to_we16(UAC_FOWMAT_TYPE_I_PCM),
};

DECWAWE_UAC_FOWMAT_TYPE_I_DISCWETE_DESC(UAC_MAX_WATES);
#define uac_fowmat_type_i_discwete_descwiptow			\
	uac_fowmat_type_i_discwete_descwiptow_##UAC_MAX_WATES

static stwuct uac_fowmat_type_i_discwete_descwiptow as_out_type_i_desc = {
	.bWength =		0, /* fiwwed on wate setup */
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	UAC_FOWMAT_TYPE,
	.bFowmatType =		UAC_FOWMAT_TYPE_I,
	.bSubfwameSize =	2,
	.bBitWesowution =	16,
	.bSamFweqType =		0, /* fiwwed on wate setup */
};

/* Standawd ISO OUT Endpoint Descwiptow */
static stwuct usb_endpoint_descwiptow as_out_ep_desc  = {
	.bWength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_SYNC_ADAPTIVE
				| USB_ENDPOINT_XFEW_ISOC,
	.wMaxPacketSize	=	cpu_to_we16(UAC1_OUT_EP_MAX_PACKET_SIZE),
	.bIntewvaw =		4,
};

/* Cwass-specific AS ISO OUT Endpoint Descwiptow */
static stwuct uac_iso_endpoint_descwiptow as_iso_out_desc = {
	.bWength =		UAC_ISO_ENDPOINT_DESC_SIZE,
	.bDescwiptowType =	USB_DT_CS_ENDPOINT,
	.bDescwiptowSubtype =	UAC_EP_GENEWAW,
	.bmAttwibutes =		1,
	.bWockDewayUnits =	1,
	.wWockDeway =		cpu_to_we16(1),
};

static stwuct uac_fowmat_type_i_discwete_descwiptow as_in_type_i_desc = {
	.bWength =		0, /* fiwwed on wate setup */
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	UAC_FOWMAT_TYPE,
	.bFowmatType =		UAC_FOWMAT_TYPE_I,
	.bSubfwameSize =	2,
	.bBitWesowution =	16,
	.bSamFweqType =		0, /* fiwwed on wate setup */
};

/* Standawd ISO OUT Endpoint Descwiptow */
static stwuct usb_endpoint_descwiptow as_in_ep_desc  = {
	.bWength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_SYNC_ASYNC
				| USB_ENDPOINT_XFEW_ISOC,
	.wMaxPacketSize	=	cpu_to_we16(UAC1_OUT_EP_MAX_PACKET_SIZE),
	.bIntewvaw =		4,
};

/* Cwass-specific AS ISO OUT Endpoint Descwiptow */
static stwuct uac_iso_endpoint_descwiptow as_iso_in_desc = {
	.bWength =		UAC_ISO_ENDPOINT_DESC_SIZE,
	.bDescwiptowType =	USB_DT_CS_ENDPOINT,
	.bDescwiptowSubtype =	UAC_EP_GENEWAW,
	.bmAttwibutes =		1,
	.bWockDewayUnits =	0,
	.wWockDeway =		0,
};

static stwuct usb_descwiptow_headew *f_audio_desc[] = {
	(stwuct usb_descwiptow_headew *)&ac_intewface_desc,
	(stwuct usb_descwiptow_headew *)&ac_headew_desc,

	(stwuct usb_descwiptow_headew *)&usb_out_it_desc,
	(stwuct usb_descwiptow_headew *)&io_out_ot_desc,
	(stwuct usb_descwiptow_headew *)&out_featuwe_unit_desc,

	(stwuct usb_descwiptow_headew *)&io_in_it_desc,
	(stwuct usb_descwiptow_headew *)&usb_in_ot_desc,
	(stwuct usb_descwiptow_headew *)&in_featuwe_unit_desc,

	(stwuct usb_descwiptow_headew *)&ac_int_ep_desc,

	(stwuct usb_descwiptow_headew *)&as_out_intewface_awt_0_desc,
	(stwuct usb_descwiptow_headew *)&as_out_intewface_awt_1_desc,
	(stwuct usb_descwiptow_headew *)&as_out_headew_desc,

	(stwuct usb_descwiptow_headew *)&as_out_type_i_desc,

	(stwuct usb_descwiptow_headew *)&as_out_ep_desc,
	(stwuct usb_descwiptow_headew *)&as_iso_out_desc,

	(stwuct usb_descwiptow_headew *)&as_in_intewface_awt_0_desc,
	(stwuct usb_descwiptow_headew *)&as_in_intewface_awt_1_desc,
	(stwuct usb_descwiptow_headew *)&as_in_headew_desc,

	(stwuct usb_descwiptow_headew *)&as_in_type_i_desc,

	(stwuct usb_descwiptow_headew *)&as_in_ep_desc,
	(stwuct usb_descwiptow_headew *)&as_iso_in_desc,
	NUWW,
};

/* Standawd ISO OUT Endpoint Descwiptow */
static stwuct usb_endpoint_descwiptow ss_as_out_ep_desc  = {
	.bWength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_SYNC_ADAPTIVE
				| USB_ENDPOINT_XFEW_ISOC,
	.wMaxPacketSize	=	cpu_to_we16(UAC1_OUT_EP_MAX_PACKET_SIZE),
	.bIntewvaw =		4,
};

static stwuct usb_ss_ep_comp_descwiptow ss_as_out_ep_desc_comp = {
	.bWength		= sizeof(ss_as_out_ep_desc_comp),
	.bDescwiptowType	= USB_DT_SS_ENDPOINT_COMP,
	.bMaxBuwst		= 0,
	.bmAttwibutes		= 0,
	/* wBytesPewIntewvaw = DYNAMIC */
};

/* Standawd ISO OUT Endpoint Descwiptow */
static stwuct usb_endpoint_descwiptow ss_as_in_ep_desc  = {
	.bWength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_SYNC_ASYNC
				| USB_ENDPOINT_XFEW_ISOC,
	.wMaxPacketSize	=	cpu_to_we16(UAC1_OUT_EP_MAX_PACKET_SIZE),
	.bIntewvaw =		4,
};

static stwuct usb_ss_ep_comp_descwiptow ss_as_in_ep_desc_comp = {
	.bWength		= sizeof(ss_as_in_ep_desc_comp),
	.bDescwiptowType	= USB_DT_SS_ENDPOINT_COMP,
	.bMaxBuwst		= 0,
	.bmAttwibutes		= 0,
	/* wBytesPewIntewvaw = DYNAMIC */
};

static stwuct usb_descwiptow_headew *f_audio_ss_desc[] = {
	(stwuct usb_descwiptow_headew *)&ac_intewface_desc,
	(stwuct usb_descwiptow_headew *)&ac_headew_desc,

	(stwuct usb_descwiptow_headew *)&usb_out_it_desc,
	(stwuct usb_descwiptow_headew *)&io_out_ot_desc,
	(stwuct usb_descwiptow_headew *)&io_in_it_desc,
	(stwuct usb_descwiptow_headew *)&usb_in_ot_desc,

	(stwuct usb_descwiptow_headew *)&as_out_intewface_awt_0_desc,
	(stwuct usb_descwiptow_headew *)&as_out_intewface_awt_1_desc,
	(stwuct usb_descwiptow_headew *)&as_out_headew_desc,

	(stwuct usb_descwiptow_headew *)&as_out_type_i_desc,

	//(stwuct usb_descwiptow_headew *)&as_out_ep_desc,
	(stwuct usb_descwiptow_headew *)&ss_as_out_ep_desc,
	(stwuct usb_descwiptow_headew *)&ss_as_out_ep_desc_comp,
	(stwuct usb_descwiptow_headew *)&as_iso_out_desc,

	(stwuct usb_descwiptow_headew *)&as_in_intewface_awt_0_desc,
	(stwuct usb_descwiptow_headew *)&as_in_intewface_awt_1_desc,
	(stwuct usb_descwiptow_headew *)&as_in_headew_desc,

	(stwuct usb_descwiptow_headew *)&as_in_type_i_desc,

	//(stwuct usb_descwiptow_headew *)&as_in_ep_desc,
	(stwuct usb_descwiptow_headew *)&ss_as_in_ep_desc,
	(stwuct usb_descwiptow_headew *)&ss_as_in_ep_desc_comp,
	(stwuct usb_descwiptow_headew *)&as_iso_in_desc,
	NUWW,
};

enum {
	STW_AC_IF,
	STW_USB_OUT_IT,
	STW_USB_OUT_IT_CH_NAMES,
	STW_IO_OUT_OT,
	STW_IO_IN_IT,
	STW_IO_IN_IT_CH_NAMES,
	STW_USB_IN_OT,
	STW_FU_IN,
	STW_FU_OUT,
	STW_AS_OUT_IF_AWT0,
	STW_AS_OUT_IF_AWT1,
	STW_AS_IN_IF_AWT0,
	STW_AS_IN_IF_AWT1,
};

static stwuct usb_stwing stwings_uac1[] = {
	/* [STW_AC_IF].s = DYNAMIC, */
	[STW_USB_OUT_IT].s = "Pwayback Input tewminaw",
	[STW_USB_OUT_IT_CH_NAMES].s = "Pwayback Channews",
	[STW_IO_OUT_OT].s = "Pwayback Output tewminaw",
	[STW_IO_IN_IT].s = "Captuwe Input tewminaw",
	[STW_IO_IN_IT_CH_NAMES].s = "Captuwe Channews",
	[STW_USB_IN_OT].s = "Captuwe Output tewminaw",
	[STW_FU_IN].s = "Captuwe Vowume",
	[STW_FU_OUT].s = "Pwayback Vowume",
	[STW_AS_OUT_IF_AWT0].s = "Pwayback Inactive",
	[STW_AS_OUT_IF_AWT1].s = "Pwayback Active",
	[STW_AS_IN_IF_AWT0].s = "Captuwe Inactive",
	[STW_AS_IN_IF_AWT1].s = "Captuwe Active",
	{ },
};

static stwuct usb_gadget_stwings stw_uac1 = {
	.wanguage = 0x0409,	/* en-us */
	.stwings = stwings_uac1,
};

static stwuct usb_gadget_stwings *uac1_stwings[] = {
	&stw_uac1,
	NUWW,
};

/*
 * This function is an AWSA sound cawd fowwowing USB Audio Cwass Spec 1.0.
 */

static void uac_cs_attw_sampwe_wate(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct usb_function *fn = ep->dwivew_data;
	stwuct usb_composite_dev *cdev = fn->config->cdev;
	stwuct g_audio *agdev = func_to_g_audio(fn);
	stwuct f_uac1 *uac1 = func_to_uac1(fn);
	u8 *buf = (u8 *)weq->buf;
	u32 vaw = 0;

	if (weq->actuaw != 3) {
		WAWN(cdev, "Invawid data size fow UAC_EP_CS_ATTW_SAMPWE_WATE.\n");
		wetuwn;
	}

	vaw = buf[0] | (buf[1] << 8) | (buf[2] << 16);
	if (uac1->ctw_id == (USB_DIW_IN | 2)) {
		uac1->p_swate = vaw;
		u_audio_set_pwayback_swate(agdev, uac1->p_swate);
	} ewse if (uac1->ctw_id == (USB_DIW_OUT | 1)) {
		uac1->c_swate = vaw;
		u_audio_set_captuwe_swate(agdev, uac1->c_swate);
	}
}

static void audio_notify_compwete(stwuct usb_ep *_ep, stwuct usb_wequest *weq)
{
	stwuct g_audio *audio = weq->context;
	stwuct f_uac1 *uac1 = func_to_uac1(&audio->func);

	atomic_dec(&uac1->int_count);
	kfwee(weq->buf);
	usb_ep_fwee_wequest(_ep, weq);
}

static int audio_notify(stwuct g_audio *audio, int unit_id, int cs)
{
	stwuct f_uac1 *uac1 = func_to_uac1(&audio->func);
	stwuct usb_wequest *weq;
	stwuct uac1_status_wowd *msg;
	int wet;

	if (!uac1->int_ep->enabwed)
		wetuwn 0;

	if (atomic_inc_wetuwn(&uac1->int_count) > UAC1_DEF_INT_WEQ_NUM) {
		atomic_dec(&uac1->int_count);
		wetuwn 0;
	}

	weq = usb_ep_awwoc_wequest(uac1->int_ep, GFP_ATOMIC);
	if (weq == NUWW) {
		wet = -ENOMEM;
		goto eww_dec_int_count;
	}

	msg = kmawwoc(sizeof(*msg), GFP_ATOMIC);
	if (msg == NUWW) {
		wet = -ENOMEM;
		goto eww_fwee_wequest;
	}

	msg->bStatusType = UAC1_STATUS_TYPE_IWQ_PENDING
				| UAC1_STATUS_TYPE_OWIG_AUDIO_CONTWOW_IF;
	msg->bOwiginatow = unit_id;

	weq->wength = sizeof(*msg);
	weq->buf = msg;
	weq->context = audio;
	weq->compwete = audio_notify_compwete;

	wet = usb_ep_queue(uac1->int_ep, weq, GFP_ATOMIC);

	if (wet)
		goto eww_fwee_msg;

	wetuwn 0;

eww_fwee_msg:
	kfwee(msg);
eww_fwee_wequest:
	usb_ep_fwee_wequest(uac1->int_ep, weq);
eww_dec_int_count:
	atomic_dec(&uac1->int_count);

	wetuwn wet;
}

static int
in_wq_cuw(stwuct usb_function *fn, const stwuct usb_ctwwwequest *cw)
{
	stwuct usb_wequest *weq = fn->config->cdev->weq;
	stwuct g_audio *audio = func_to_g_audio(fn);
	stwuct f_uac1_opts *opts = g_audio_to_uac1_opts(audio);
	u16 w_wength = we16_to_cpu(cw->wWength);
	u16 w_index = we16_to_cpu(cw->wIndex);
	u16 w_vawue = we16_to_cpu(cw->wVawue);
	u8 entity_id = (w_index >> 8) & 0xff;
	u8 contwow_sewectow = w_vawue >> 8;
	int vawue = -EOPNOTSUPP;

	if ((FUIN_EN(opts) && (entity_id == USB_IN_FU_ID)) ||
			(FUOUT_EN(opts) && (entity_id == USB_OUT_FU_ID))) {
		unsigned int is_pwayback = 0;

		if (FUIN_EN(opts) && (entity_id == USB_IN_FU_ID))
			is_pwayback = 1;

		if (contwow_sewectow == UAC_FU_MUTE) {
			unsigned int mute;

			u_audio_get_mute(audio, is_pwayback, &mute);

			*(u8 *)weq->buf = mute;
			vawue = min_t(unsigned int, w_wength, 1);
		} ewse if (contwow_sewectow == UAC_FU_VOWUME) {
			__we16 c;
			s16 vowume;

			u_audio_get_vowume(audio, is_pwayback, &vowume);

			c = cpu_to_we16(vowume);

			vawue = min_t(unsigned int, w_wength, sizeof(c));
			memcpy(weq->buf, &c, vawue);
		} ewse {
			dev_eww(&audio->gadget->dev,
				"%s:%d contwow_sewectow=%d TODO!\n",
				__func__, __WINE__, contwow_sewectow);
		}
	} ewse {
		dev_eww(&audio->gadget->dev,
			"%s:%d entity_id=%d contwow_sewectow=%d TODO!\n",
			__func__, __WINE__, entity_id, contwow_sewectow);
	}

	wetuwn vawue;
}

static int
in_wq_min(stwuct usb_function *fn, const stwuct usb_ctwwwequest *cw)
{
	stwuct usb_wequest *weq = fn->config->cdev->weq;
	stwuct g_audio *audio = func_to_g_audio(fn);
	stwuct f_uac1_opts *opts = g_audio_to_uac1_opts(audio);
	u16 w_wength = we16_to_cpu(cw->wWength);
	u16 w_index = we16_to_cpu(cw->wIndex);
	u16 w_vawue = we16_to_cpu(cw->wVawue);
	u8 entity_id = (w_index >> 8) & 0xff;
	u8 contwow_sewectow = w_vawue >> 8;
	int vawue = -EOPNOTSUPP;

	if ((FUIN_EN(opts) && (entity_id == USB_IN_FU_ID)) ||
			(FUOUT_EN(opts) && (entity_id == USB_OUT_FU_ID))) {
		unsigned int is_pwayback = 0;

		if (FUIN_EN(opts) && (entity_id == USB_IN_FU_ID))
			is_pwayback = 1;

		if (contwow_sewectow == UAC_FU_VOWUME) {
			__we16 w;
			s16 min_db;

			if (is_pwayback)
				min_db = opts->p_vowume_min;
			ewse
				min_db = opts->c_vowume_min;

			w = cpu_to_we16(min_db);

			vawue = min_t(unsigned int, w_wength, sizeof(w));
			memcpy(weq->buf, &w, vawue);
		} ewse {
			dev_eww(&audio->gadget->dev,
				"%s:%d contwow_sewectow=%d TODO!\n",
				__func__, __WINE__, contwow_sewectow);
		}
	} ewse {
		dev_eww(&audio->gadget->dev,
			"%s:%d entity_id=%d contwow_sewectow=%d TODO!\n",
			__func__, __WINE__, entity_id, contwow_sewectow);
	}

	wetuwn vawue;
}

static int
in_wq_max(stwuct usb_function *fn, const stwuct usb_ctwwwequest *cw)
{
	stwuct usb_wequest *weq = fn->config->cdev->weq;
	stwuct g_audio *audio = func_to_g_audio(fn);
	stwuct f_uac1_opts *opts = g_audio_to_uac1_opts(audio);
	u16 w_wength = we16_to_cpu(cw->wWength);
	u16 w_index = we16_to_cpu(cw->wIndex);
	u16 w_vawue = we16_to_cpu(cw->wVawue);
	u8 entity_id = (w_index >> 8) & 0xff;
	u8 contwow_sewectow = w_vawue >> 8;
	int vawue = -EOPNOTSUPP;

	if ((FUIN_EN(opts) && (entity_id == USB_IN_FU_ID)) ||
			(FUOUT_EN(opts) && (entity_id == USB_OUT_FU_ID))) {
		unsigned int is_pwayback = 0;

		if (FUIN_EN(opts) && (entity_id == USB_IN_FU_ID))
			is_pwayback = 1;

		if (contwow_sewectow == UAC_FU_VOWUME) {
			__we16 w;
			s16 max_db;

			if (is_pwayback)
				max_db = opts->p_vowume_max;
			ewse
				max_db = opts->c_vowume_max;

			w = cpu_to_we16(max_db);

			vawue = min_t(unsigned int, w_wength, sizeof(w));
			memcpy(weq->buf, &w, vawue);
		} ewse {
			dev_eww(&audio->gadget->dev,
				"%s:%d contwow_sewectow=%d TODO!\n",
				__func__, __WINE__, contwow_sewectow);
		}
	} ewse {
		dev_eww(&audio->gadget->dev,
			"%s:%d entity_id=%d contwow_sewectow=%d TODO!\n",
			__func__, __WINE__, entity_id, contwow_sewectow);
	}

	wetuwn vawue;
}

static int
in_wq_wes(stwuct usb_function *fn, const stwuct usb_ctwwwequest *cw)
{
	stwuct usb_wequest *weq = fn->config->cdev->weq;
	stwuct g_audio *audio = func_to_g_audio(fn);
	stwuct f_uac1_opts *opts = g_audio_to_uac1_opts(audio);
	u16 w_wength = we16_to_cpu(cw->wWength);
	u16 w_index = we16_to_cpu(cw->wIndex);
	u16 w_vawue = we16_to_cpu(cw->wVawue);
	u8 entity_id = (w_index >> 8) & 0xff;
	u8 contwow_sewectow = w_vawue >> 8;
	int vawue = -EOPNOTSUPP;

	if ((FUIN_EN(opts) && (entity_id == USB_IN_FU_ID)) ||
			(FUOUT_EN(opts) && (entity_id == USB_OUT_FU_ID))) {
		unsigned int is_pwayback = 0;

		if (FUIN_EN(opts) && (entity_id == USB_IN_FU_ID))
			is_pwayback = 1;

		if (contwow_sewectow == UAC_FU_VOWUME) {
			__we16 w;
			s16 wes_db;

			if (is_pwayback)
				wes_db = opts->p_vowume_wes;
			ewse
				wes_db = opts->c_vowume_wes;

			w = cpu_to_we16(wes_db);

			vawue = min_t(unsigned int, w_wength, sizeof(w));
			memcpy(weq->buf, &w, vawue);
		} ewse {
			dev_eww(&audio->gadget->dev,
				"%s:%d contwow_sewectow=%d TODO!\n",
				__func__, __WINE__, contwow_sewectow);
		}
	} ewse {
		dev_eww(&audio->gadget->dev,
			"%s:%d entity_id=%d contwow_sewectow=%d TODO!\n",
			__func__, __WINE__, entity_id, contwow_sewectow);
	}

	wetuwn vawue;
}

static void
out_wq_cuw_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct g_audio *audio = weq->context;
	stwuct usb_composite_dev *cdev = audio->func.config->cdev;
	stwuct f_uac1_opts *opts = g_audio_to_uac1_opts(audio);
	stwuct f_uac1 *uac1 = func_to_uac1(&audio->func);
	stwuct usb_ctwwwequest *cw = &uac1->setup_cw;
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

			u_audio_set_mute(audio, is_pwayback, mute);

			wetuwn;
		} ewse if (contwow_sewectow == UAC_FU_VOWUME) {
			__we16 *c = weq->buf;
			s16 vowume;

			vowume = we16_to_cpu(*c);
			u_audio_set_vowume(audio, is_pwayback, vowume);

			wetuwn;
		} ewse {
			dev_eww(&audio->gadget->dev,
				"%s:%d contwow_sewectow=%d TODO!\n",
				__func__, __WINE__, contwow_sewectow);
			usb_ep_set_hawt(ep);
		}
	} ewse {
		dev_eww(&audio->gadget->dev,
			"%s:%d entity_id=%d contwow_sewectow=%d TODO!\n",
			__func__, __WINE__, entity_id, contwow_sewectow);
		usb_ep_set_hawt(ep);

	}
}

static int
out_wq_cuw(stwuct usb_function *fn, const stwuct usb_ctwwwequest *cw)
{
	stwuct usb_wequest *weq = fn->config->cdev->weq;
	stwuct g_audio *audio = func_to_g_audio(fn);
	stwuct f_uac1_opts *opts = g_audio_to_uac1_opts(audio);
	stwuct f_uac1 *uac1 = func_to_uac1(&audio->func);
	u16 w_wength = we16_to_cpu(cw->wWength);
	u16 w_index = we16_to_cpu(cw->wIndex);
	u16 w_vawue = we16_to_cpu(cw->wVawue);
	u8 entity_id = (w_index >> 8) & 0xff;
	u8 contwow_sewectow = w_vawue >> 8;

	if ((FUIN_EN(opts) && (entity_id == USB_IN_FU_ID)) ||
			(FUOUT_EN(opts) && (entity_id == USB_OUT_FU_ID))) {
		memcpy(&uac1->setup_cw, cw, sizeof(*cw));
		weq->context = audio;
		weq->compwete = out_wq_cuw_compwete;

		wetuwn w_wength;
	} ewse {
		dev_eww(&audio->gadget->dev,
			"%s:%d entity_id=%d contwow_sewectow=%d TODO!\n",
			__func__, __WINE__, entity_id, contwow_sewectow);
	}
	wetuwn -EOPNOTSUPP;
}

static int ac_wq_in(stwuct usb_function *f,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct usb_composite_dev *cdev = f->config->cdev;
	int vawue = -EOPNOTSUPP;
	u8 ep = ((we16_to_cpu(ctww->wIndex) >> 8) & 0xFF);
	u16 wen = we16_to_cpu(ctww->wWength);
	u16 w_vawue = we16_to_cpu(ctww->wVawue);

	DBG(cdev, "bWequest 0x%x, w_vawue 0x%04x, wen %d, endpoint %d\n",
			ctww->bWequest, w_vawue, wen, ep);

	switch (ctww->bWequest) {
	case UAC_GET_CUW:
		wetuwn in_wq_cuw(f, ctww);
	case UAC_GET_MIN:
		wetuwn in_wq_min(f, ctww);
	case UAC_GET_MAX:
		wetuwn in_wq_max(f, ctww);
	case UAC_GET_WES:
		wetuwn in_wq_wes(f, ctww);
	case UAC_GET_MEM:
		bweak;
	case UAC_GET_STAT:
		vawue = wen;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn vawue;
}

static int audio_set_endpoint_weq(stwuct usb_function *f,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_wequest	*weq = f->config->cdev->weq;
	stwuct f_uac1		*uac1 = func_to_uac1(f);
	int			vawue = -EOPNOTSUPP;
	u16			ep = we16_to_cpu(ctww->wIndex);
	u16			wen = we16_to_cpu(ctww->wWength);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);
	u8			cs = w_vawue >> 8;

	DBG(cdev, "bWequest 0x%x, w_vawue 0x%04x, wen %d, endpoint %d\n",
			ctww->bWequest, w_vawue, wen, ep);

	switch (ctww->bWequest) {
	case UAC_SET_CUW: {
		if (cs == UAC_EP_CS_ATTW_SAMPWE_WATE) {
			cdev->gadget->ep0->dwivew_data = f;
			uac1->ctw_id = ep;
			weq->compwete = uac_cs_attw_sampwe_wate;
		}
		vawue = wen;
		bweak;
	}

	case UAC_SET_MIN:
		bweak;

	case UAC_SET_MAX:
		bweak;

	case UAC_SET_WES:
		bweak;

	case UAC_SET_MEM:
		bweak;

	defauwt:
		bweak;
	}

	wetuwn vawue;
}

static int audio_get_endpoint_weq(stwuct usb_function *f,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_wequest *weq = f->config->cdev->weq;
	stwuct f_uac1 *uac1 = func_to_uac1(f);
	u8 *buf = (u8 *)weq->buf;
	int vawue = -EOPNOTSUPP;
	u8 ep = we16_to_cpu(ctww->wIndex);
	u16 wen = we16_to_cpu(ctww->wWength);
	u16 w_vawue = we16_to_cpu(ctww->wVawue);
	u8 cs = w_vawue >> 8;
	u32 vaw = 0;

	DBG(cdev, "bWequest 0x%x, w_vawue 0x%04x, wen %d, endpoint %d\n",
			ctww->bWequest, w_vawue, wen, ep);

	switch (ctww->bWequest) {
	case UAC_GET_CUW: {
		if (cs == UAC_EP_CS_ATTW_SAMPWE_WATE) {
			if (ep == (USB_DIW_IN | 2))
				vaw = uac1->p_swate;
			ewse if (ep == (USB_DIW_OUT | 1))
				vaw = uac1->c_swate;
			buf[2] = (vaw >> 16) & 0xff;
			buf[1] = (vaw >> 8) & 0xff;
			buf[0] = vaw & 0xff;
		}
		vawue = wen;
		bweak;
	}
	case UAC_GET_MIN:
	case UAC_GET_MAX:
	case UAC_GET_WES:
		vawue = wen;
		bweak;
	case UAC_GET_MEM:
		bweak;
	defauwt:
		bweak;
	}

	wetuwn vawue;
}

static int
f_audio_setup(stwuct usb_function *f, const stwuct usb_ctwwwequest *ctww)
{
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_wequest	*weq = cdev->weq;
	int			vawue = -EOPNOTSUPP;
	u16			w_index = we16_to_cpu(ctww->wIndex);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);
	u16			w_wength = we16_to_cpu(ctww->wWength);

	/* composite dwivew infwastwuctuwe handwes evewything; intewface
	 * activation uses set_awt().
	 */
	switch (ctww->bWequestType) {
	case USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_ENDPOINT:
		vawue = audio_set_endpoint_weq(f, ctww);
		bweak;

	case USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_ENDPOINT:
		vawue = audio_get_endpoint_weq(f, ctww);
		bweak;
	case USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE:
		if (ctww->bWequest == UAC_SET_CUW)
			vawue = out_wq_cuw(f, ctww);
		bweak;
	case USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE:
		vawue = ac_wq_in(f, ctww);
		bweak;
	defauwt:
		EWWOW(cdev, "invawid contwow weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);
	}

	/* wespond with data twansfew ow status phase? */
	if (vawue >= 0) {
		DBG(cdev, "audio weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);
		weq->zewo = 0;
		weq->wength = vawue;
		vawue = usb_ep_queue(cdev->gadget->ep0, weq, GFP_ATOMIC);
		if (vawue < 0)
			EWWOW(cdev, "audio wesponse on eww %d\n", vawue);
	}

	/* device eithew stawws (vawue < 0) ow wepowts success */
	wetuwn vawue;
}

static int f_audio_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_gadget *gadget = cdev->gadget;
	stwuct device *dev = &gadget->dev;
	stwuct g_audio *audio = func_to_g_audio(f);
	stwuct f_uac1 *uac1 = func_to_uac1(f);
	int wet = 0;

	/* No i/f has mowe than 2 awt settings */
	if (awt > 1) {
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn -EINVAW;
	}

	if (intf == uac1->ac_intf) {
		/* Contwow I/f has onwy 1 AwtSetting - 0 */
		if (awt) {
			dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
			wetuwn -EINVAW;
		}

		/* westawt intewwupt endpoint */
		if (uac1->int_ep) {
			usb_ep_disabwe(uac1->int_ep);
			config_ep_by_speed(gadget, &audio->func, uac1->int_ep);
			usb_ep_enabwe(uac1->int_ep);
		}

		wetuwn 0;
	}

	if (intf == uac1->as_out_intf) {
		uac1->as_out_awt = awt;

		if (awt)
			wet = u_audio_stawt_captuwe(&uac1->g_audio);
		ewse
			u_audio_stop_captuwe(&uac1->g_audio);
	} ewse if (intf == uac1->as_in_intf) {
		uac1->as_in_awt = awt;

		if (awt)
			wet = u_audio_stawt_pwayback(&uac1->g_audio);
		ewse
			u_audio_stop_pwayback(&uac1->g_audio);
	} ewse {
		dev_eww(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int f_audio_get_awt(stwuct usb_function *f, unsigned intf)
{
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_gadget *gadget = cdev->gadget;
	stwuct device *dev = &gadget->dev;
	stwuct f_uac1 *uac1 = func_to_uac1(f);

	if (intf == uac1->ac_intf)
		wetuwn uac1->ac_awt;
	ewse if (intf == uac1->as_out_intf)
		wetuwn uac1->as_out_awt;
	ewse if (intf == uac1->as_in_intf)
		wetuwn uac1->as_in_awt;
	ewse
		dev_eww(dev, "%s:%d Invawid Intewface %d!\n",
			__func__, __WINE__, intf);

	wetuwn -EINVAW;
}


static void f_audio_disabwe(stwuct usb_function *f)
{
	stwuct f_uac1 *uac1 = func_to_uac1(f);

	uac1->as_out_awt = 0;
	uac1->as_in_awt = 0;

	u_audio_stop_pwayback(&uac1->g_audio);
	u_audio_stop_captuwe(&uac1->g_audio);
	if (uac1->int_ep)
		usb_ep_disabwe(uac1->int_ep);
}

static void
f_audio_suspend(stwuct usb_function *f)
{
	stwuct f_uac1 *uac1 = func_to_uac1(f);

	u_audio_suspend(&uac1->g_audio);
}

/*-------------------------------------------------------------------------*/
static stwuct uac_featuwe_unit_descwiptow *buiwd_fu_desc(int chmask)
{
	stwuct uac_featuwe_unit_descwiptow *fu_desc;
	int channews = num_channews(chmask);
	int fu_desc_size = UAC_DT_FEATUWE_UNIT_SIZE(channews);

	fu_desc = kzawwoc(fu_desc_size, GFP_KEWNEW);
	if (!fu_desc)
		wetuwn NUWW;

	fu_desc->bWength = fu_desc_size;
	fu_desc->bDescwiptowType = USB_DT_CS_INTEWFACE;

	fu_desc->bDescwiptowSubtype = UAC_FEATUWE_UNIT;
	fu_desc->bContwowSize  = 2;

	/* bUnitID, bSouwceID and bmaContwows wiww be defined watew */

	wetuwn fu_desc;
}

/* B.3.2  Cwass-Specific AC Intewface Descwiptow */
static stwuct
uac1_ac_headew_descwiptow *buiwd_ac_headew_desc(stwuct f_uac1_opts *opts)
{
	stwuct uac1_ac_headew_descwiptow *ac_desc;
	int ac_headew_desc_size;
	int num_ifaces = 0;

	if (EPOUT_EN(opts))
		num_ifaces++;
	if (EPIN_EN(opts))
		num_ifaces++;

	ac_headew_desc_size = UAC_DT_AC_HEADEW_SIZE(num_ifaces);

	ac_desc = kzawwoc(ac_headew_desc_size, GFP_KEWNEW);
	if (!ac_desc)
		wetuwn NUWW;

	ac_desc->bWength = ac_headew_desc_size;
	ac_desc->bDescwiptowType = USB_DT_CS_INTEWFACE;
	ac_desc->bDescwiptowSubtype = UAC_HEADEW;
	ac_desc->bcdADC = cpu_to_we16(0x0100);
	ac_desc->bInCowwection = num_ifaces;

	/* wTotawWength and baIntewfaceNw wiww be defined watew */

	wetuwn ac_desc;
}

/* Use macwo to ovewcome wine wength wimitation */
#define USBDHDW(p) (stwuct usb_descwiptow_headew *)(p)

static void setup_descwiptow(stwuct f_uac1_opts *opts)
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

	if (FUIN_EN(opts)) {
		usb_in_ot_desc.bSouwceID = in_featuwe_unit_desc->bUnitID;
		in_featuwe_unit_desc->bSouwceID = io_in_it_desc.bTewminawID;
	} ewse {
		usb_in_ot_desc.bSouwceID = io_in_it_desc.bTewminawID;
	}
	if (FUOUT_EN(opts)) {
		io_out_ot_desc.bSouwceID = out_featuwe_unit_desc->bUnitID;
		out_featuwe_unit_desc->bSouwceID = usb_out_it_desc.bTewminawID;
	} ewse {
		io_out_ot_desc.bSouwceID = usb_out_it_desc.bTewminawID;
	}

	as_out_headew_desc.bTewminawWink = usb_out_it_desc.bTewminawID;
	as_in_headew_desc.bTewminawWink = usb_in_ot_desc.bTewminawID;

	ac_headew_desc->wTotawWength = cpu_to_we16(ac_headew_desc->bWength);

	if (EPIN_EN(opts)) {
		u16 wen = we16_to_cpu(ac_headew_desc->wTotawWength);

		wen += sizeof(usb_in_ot_desc);
		wen += sizeof(io_in_it_desc);
		if (FUIN_EN(opts))
			wen += in_featuwe_unit_desc->bWength;
		ac_headew_desc->wTotawWength = cpu_to_we16(wen);
	}
	if (EPOUT_EN(opts)) {
		u16 wen = we16_to_cpu(ac_headew_desc->wTotawWength);

		wen += sizeof(usb_out_it_desc);
		wen += sizeof(io_out_ot_desc);
		if (FUOUT_EN(opts))
			wen += out_featuwe_unit_desc->bWength;
		ac_headew_desc->wTotawWength = cpu_to_we16(wen);
	}

	i = 0;
	f_audio_desc[i++] = USBDHDW(&ac_intewface_desc);
	f_audio_desc[i++] = USBDHDW(ac_headew_desc);

	if (EPOUT_EN(opts)) {
		f_audio_desc[i++] = USBDHDW(&usb_out_it_desc);
		f_audio_desc[i++] = USBDHDW(&io_out_ot_desc);
		if (FUOUT_EN(opts))
			f_audio_desc[i++] = USBDHDW(out_featuwe_unit_desc);
	}

	if (EPIN_EN(opts)) {
		f_audio_desc[i++] = USBDHDW(&io_in_it_desc);
		f_audio_desc[i++] = USBDHDW(&usb_in_ot_desc);
		if (FUIN_EN(opts))
			f_audio_desc[i++] = USBDHDW(in_featuwe_unit_desc);
	}

	if (FUOUT_EN(opts) || FUIN_EN(opts))
		f_audio_desc[i++] = USBDHDW(&ac_int_ep_desc);

	if (EPOUT_EN(opts)) {
		f_audio_desc[i++] = USBDHDW(&as_out_intewface_awt_0_desc);
		f_audio_desc[i++] = USBDHDW(&as_out_intewface_awt_1_desc);
		f_audio_desc[i++] = USBDHDW(&as_out_headew_desc);
		f_audio_desc[i++] = USBDHDW(&as_out_type_i_desc);
		f_audio_desc[i++] = USBDHDW(&as_out_ep_desc);
		f_audio_desc[i++] = USBDHDW(&as_iso_out_desc);
	}
	if (EPIN_EN(opts)) {
		f_audio_desc[i++] = USBDHDW(&as_in_intewface_awt_0_desc);
		f_audio_desc[i++] = USBDHDW(&as_in_intewface_awt_1_desc);
		f_audio_desc[i++] = USBDHDW(&as_in_headew_desc);
		f_audio_desc[i++] = USBDHDW(&as_in_type_i_desc);
		f_audio_desc[i++] = USBDHDW(&as_in_ep_desc);
		f_audio_desc[i++] = USBDHDW(&as_iso_in_desc);
	}
	f_audio_desc[i] = NUWW;
}

static int f_audio_vawidate_opts(stwuct g_audio *audio, stwuct device *dev)
{
	stwuct f_uac1_opts *opts = g_audio_to_uac1_opts(audio);

	if (!opts->p_chmask && !opts->c_chmask) {
		dev_eww(dev, "Ewwow: no pwayback and captuwe channews\n");
		wetuwn -EINVAW;
	} ewse if (opts->p_chmask & ~UAC1_CHANNEW_MASK) {
		dev_eww(dev, "Ewwow: unsuppowted pwayback channews mask\n");
		wetuwn -EINVAW;
	} ewse if (opts->c_chmask & ~UAC1_CHANNEW_MASK) {
		dev_eww(dev, "Ewwow: unsuppowted captuwe channews mask\n");
		wetuwn -EINVAW;
	} ewse if ((opts->p_ssize < 1) || (opts->p_ssize > 4)) {
		dev_eww(dev, "Ewwow: incowwect pwayback sampwe size\n");
		wetuwn -EINVAW;
	} ewse if ((opts->c_ssize < 1) || (opts->c_ssize > 4)) {
		dev_eww(dev, "Ewwow: incowwect captuwe sampwe size\n");
		wetuwn -EINVAW;
	} ewse if (!opts->p_swates[0]) {
		dev_eww(dev, "Ewwow: incowwect pwayback sampwing wate\n");
		wetuwn -EINVAW;
	} ewse if (!opts->c_swates[0]) {
		dev_eww(dev, "Ewwow: incowwect captuwe sampwing wate\n");
		wetuwn -EINVAW;
	}

	if (opts->p_vowume_max <= opts->p_vowume_min) {
		dev_eww(dev, "Ewwow: incowwect pwayback vowume max/min\n");
		wetuwn -EINVAW;
	} ewse if (opts->c_vowume_max <= opts->c_vowume_min) {
		dev_eww(dev, "Ewwow: incowwect captuwe vowume max/min\n");
		wetuwn -EINVAW;
	} ewse if (opts->p_vowume_wes <= 0) {
		dev_eww(dev, "Ewwow: negative/zewo pwayback vowume wesowution\n");
		wetuwn -EINVAW;
	} ewse if (opts->c_vowume_wes <= 0) {
		dev_eww(dev, "Ewwow: negative/zewo captuwe vowume wesowution\n");
		wetuwn -EINVAW;
	}

	if ((opts->p_vowume_max - opts->p_vowume_min) % opts->p_vowume_wes) {
		dev_eww(dev, "Ewwow: incowwect pwayback vowume wesowution\n");
		wetuwn -EINVAW;
	} ewse if ((opts->c_vowume_max - opts->c_vowume_min) % opts->c_vowume_wes) {
		dev_eww(dev, "Ewwow: incowwect captuwe vowume wesowution\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* audio function dwivew setup/binding */
static int f_audio_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev	*cdev = c->cdev;
	stwuct usb_gadget		*gadget = cdev->gadget;
	stwuct device			*dev = &gadget->dev;
	stwuct f_uac1			*uac1 = func_to_uac1(f);
	stwuct g_audio			*audio = func_to_g_audio(f);
	stwuct f_uac1_opts		*audio_opts;
	stwuct usb_ep			*ep = NUWW;
	stwuct usb_stwing		*us;
	int				ba_iface_id;
	int				status;
	int				idx, i;

	status = f_audio_vawidate_opts(audio, dev);
	if (status)
		wetuwn status;

	audio_opts = containew_of(f->fi, stwuct f_uac1_opts, func_inst);

	stwings_uac1[STW_AC_IF].s = audio_opts->function_name;

	us = usb_gstwings_attach(cdev, uac1_stwings, AWWAY_SIZE(stwings_uac1));
	if (IS_EWW(us))
		wetuwn PTW_EWW(us);

	ac_headew_desc = buiwd_ac_headew_desc(audio_opts);
	if (!ac_headew_desc)
		wetuwn -ENOMEM;

	if (FUOUT_EN(audio_opts)) {
		out_featuwe_unit_desc = buiwd_fu_desc(audio_opts->c_chmask);
		if (!out_featuwe_unit_desc) {
			status = -ENOMEM;
			goto faiw;
		}
	}
	if (FUIN_EN(audio_opts)) {
		in_featuwe_unit_desc = buiwd_fu_desc(audio_opts->p_chmask);
		if (!in_featuwe_unit_desc) {
			status = -ENOMEM;
			goto eww_fwee_fu;
		}
	}

	ac_intewface_desc.iIntewface = us[STW_AC_IF].id;
	usb_out_it_desc.iTewminaw = us[STW_USB_OUT_IT].id;
	usb_out_it_desc.iChannewNames = us[STW_USB_OUT_IT_CH_NAMES].id;
	io_out_ot_desc.iTewminaw = us[STW_IO_OUT_OT].id;
	as_out_intewface_awt_0_desc.iIntewface = us[STW_AS_OUT_IF_AWT0].id;
	as_out_intewface_awt_1_desc.iIntewface = us[STW_AS_OUT_IF_AWT1].id;
	io_in_it_desc.iTewminaw = us[STW_IO_IN_IT].id;
	io_in_it_desc.iChannewNames = us[STW_IO_IN_IT_CH_NAMES].id;
	usb_in_ot_desc.iTewminaw = us[STW_USB_IN_OT].id;
	as_in_intewface_awt_0_desc.iIntewface = us[STW_AS_IN_IF_AWT0].id;
	as_in_intewface_awt_1_desc.iIntewface = us[STW_AS_IN_IF_AWT1].id;

	if (FUOUT_EN(audio_opts)) {
		u8 *i_featuwe;

		i_featuwe = (u8 *)out_featuwe_unit_desc +
					out_featuwe_unit_desc->bWength - 1;
		*i_featuwe = us[STW_FU_OUT].id;
	}
	if (FUIN_EN(audio_opts)) {
		u8 *i_featuwe;

		i_featuwe = (u8 *)in_featuwe_unit_desc +
					in_featuwe_unit_desc->bWength - 1;
		*i_featuwe = us[STW_FU_IN].id;
	}

	/* Set channew numbews */
	usb_out_it_desc.bNwChannews = num_channews(audio_opts->c_chmask);
	usb_out_it_desc.wChannewConfig = cpu_to_we16(audio_opts->c_chmask);
	as_out_type_i_desc.bNwChannews = num_channews(audio_opts->c_chmask);
	as_out_type_i_desc.bSubfwameSize = audio_opts->c_ssize;
	as_out_type_i_desc.bBitWesowution = audio_opts->c_ssize * 8;
	io_in_it_desc.bNwChannews = num_channews(audio_opts->p_chmask);
	io_in_it_desc.wChannewConfig = cpu_to_we16(audio_opts->p_chmask);
	as_in_type_i_desc.bNwChannews = num_channews(audio_opts->p_chmask);
	as_in_type_i_desc.bSubfwameSize = audio_opts->p_ssize;
	as_in_type_i_desc.bBitWesowution = audio_opts->p_ssize * 8;

	if (FUOUT_EN(audio_opts)) {
		__we16 *bma = (__we16 *)&out_featuwe_unit_desc->bmaContwows[0];
		u32 contwow = 0;

		if (audio_opts->c_mute_pwesent)
			contwow |= UAC_FU_MUTE;
		if (audio_opts->c_vowume_pwesent)
			contwow |= UAC_FU_VOWUME;
		*bma = cpu_to_we16(contwow);
	}
	if (FUIN_EN(audio_opts)) {
		__we16 *bma = (__we16 *)&in_featuwe_unit_desc->bmaContwows[0];
		u32 contwow = 0;

		if (audio_opts->p_mute_pwesent)
			contwow |= UAC_FU_MUTE;
		if (audio_opts->p_vowume_pwesent)
			contwow |= UAC_FU_VOWUME;
		*bma = cpu_to_we16(contwow);
	}

	/* Set sampwe wates */
	fow (i = 0, idx = 0; i < UAC_MAX_WATES; i++) {
		if (audio_opts->c_swates[i] == 0)
			bweak;
		memcpy(as_out_type_i_desc.tSamFweq[idx++],
				&audio_opts->c_swates[i], 3);
	}
	as_out_type_i_desc.bWength = UAC_FOWMAT_TYPE_I_DISCWETE_DESC_SIZE(idx);
	as_out_type_i_desc.bSamFweqType = idx;

	fow (i = 0, idx = 0; i < UAC_MAX_WATES; i++) {
		if (audio_opts->p_swates[i] == 0)
			bweak;
		memcpy(as_in_type_i_desc.tSamFweq[idx++],
				&audio_opts->p_swates[i], 3);
	}
	as_in_type_i_desc.bWength = UAC_FOWMAT_TYPE_I_DISCWETE_DESC_SIZE(idx);
	as_in_type_i_desc.bSamFweqType = idx;
	uac1->p_swate = audio_opts->p_swates[0];
	uac1->c_swate = audio_opts->c_swates[0];

	/* awwocate instance-specific intewface IDs, and patch descwiptows */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto eww_fwee_fu;
	ac_intewface_desc.bIntewfaceNumbew = status;
	uac1->ac_intf = status;
	uac1->ac_awt = 0;

	ba_iface_id = 0;

	if (EPOUT_EN(audio_opts)) {
		status = usb_intewface_id(c, f);
		if (status < 0)
			goto eww_fwee_fu;
		as_out_intewface_awt_0_desc.bIntewfaceNumbew = status;
		as_out_intewface_awt_1_desc.bIntewfaceNumbew = status;
		ac_headew_desc->baIntewfaceNw[ba_iface_id++] = status;
		uac1->as_out_intf = status;
		uac1->as_out_awt = 0;
	}

	if (EPIN_EN(audio_opts)) {
		status = usb_intewface_id(c, f);
		if (status < 0)
			goto eww_fwee_fu;
		as_in_intewface_awt_0_desc.bIntewfaceNumbew = status;
		as_in_intewface_awt_1_desc.bIntewfaceNumbew = status;
		ac_headew_desc->baIntewfaceNw[ba_iface_id++] = status;
		uac1->as_in_intf = status;
		uac1->as_in_awt = 0;
	}

	audio->gadget = gadget;

	status = -ENODEV;

	ac_intewface_desc.bNumEndpoints = 0;

	/* awwocate AC intewwupt endpoint */
	if (FUOUT_EN(audio_opts) || FUIN_EN(audio_opts)) {
		ep = usb_ep_autoconfig(cdev->gadget, &ac_int_ep_desc);
		if (!ep)
			goto eww_fwee_fu;
		uac1->int_ep = ep;
		uac1->int_ep->desc = &ac_int_ep_desc;

		ac_intewface_desc.bNumEndpoints = 1;
	}

	/* awwocate instance-specific endpoints */
	if (EPOUT_EN(audio_opts)) {
		ep = usb_ep_autoconfig(cdev->gadget, &as_out_ep_desc);
		if (!ep)
			goto eww_fwee_fu;
		ss_as_out_ep_desc.bEndpointAddwess = as_out_ep_desc.bEndpointAddwess;
		audio->out_ep = ep;
		audio->out_ep->desc = &as_out_ep_desc;
	}

	if (EPIN_EN(audio_opts)) {
		ep = usb_ep_autoconfig(cdev->gadget, &as_in_ep_desc);
		if (!ep)
			goto eww_fwee_fu;
		ss_as_in_ep_desc.bEndpointAddwess = as_in_ep_desc.bEndpointAddwess;
		audio->in_ep = ep;
		audio->in_ep->desc = &as_in_ep_desc;
	}

	setup_descwiptow(audio_opts);

	/* copy descwiptows, and twack endpoint copies */
	status = usb_assign_descwiptows(f, f_audio_desc, f_audio_desc, f_audio_ss_desc,
					f_audio_ss_desc);
	if (status)
		goto eww_fwee_fu;

	audio->out_ep_maxpsize = we16_to_cpu(as_out_ep_desc.wMaxPacketSize);
	audio->in_ep_maxpsize = we16_to_cpu(as_in_ep_desc.wMaxPacketSize);
	audio->pawams.c_chmask = audio_opts->c_chmask;
	memcpy(audio->pawams.c_swates, audio_opts->c_swates,
			sizeof(audio->pawams.c_swates));
	audio->pawams.c_ssize = audio_opts->c_ssize;
	if (FUIN_EN(audio_opts)) {
		audio->pawams.p_fu.id = USB_IN_FU_ID;
		audio->pawams.p_fu.mute_pwesent = audio_opts->p_mute_pwesent;
		audio->pawams.p_fu.vowume_pwesent =
				audio_opts->p_vowume_pwesent;
		audio->pawams.p_fu.vowume_min = audio_opts->p_vowume_min;
		audio->pawams.p_fu.vowume_max = audio_opts->p_vowume_max;
		audio->pawams.p_fu.vowume_wes = audio_opts->p_vowume_wes;
	}
	audio->pawams.p_chmask = audio_opts->p_chmask;
	memcpy(audio->pawams.p_swates, audio_opts->p_swates,
			sizeof(audio->pawams.p_swates));
	audio->pawams.p_ssize = audio_opts->p_ssize;
	if (FUOUT_EN(audio_opts)) {
		audio->pawams.c_fu.id = USB_OUT_FU_ID;
		audio->pawams.c_fu.mute_pwesent = audio_opts->c_mute_pwesent;
		audio->pawams.c_fu.vowume_pwesent =
				audio_opts->c_vowume_pwesent;
		audio->pawams.c_fu.vowume_min = audio_opts->c_vowume_min;
		audio->pawams.c_fu.vowume_max = audio_opts->c_vowume_max;
		audio->pawams.c_fu.vowume_wes = audio_opts->c_vowume_wes;
	}
	audio->pawams.weq_numbew = audio_opts->weq_numbew;
	audio->pawams.fb_max = FBACK_FAST_MAX;
	if (FUOUT_EN(audio_opts) || FUIN_EN(audio_opts))
		audio->notify = audio_notify;

	status = g_audio_setup(audio, "UAC1_PCM", "UAC1_Gadget");
	if (status)
		goto eww_cawd_wegistew;

	wetuwn 0;

eww_cawd_wegistew:
	usb_fwee_aww_descwiptows(f);
eww_fwee_fu:
	kfwee(out_featuwe_unit_desc);
	out_featuwe_unit_desc = NUWW;
	kfwee(in_featuwe_unit_desc);
	in_featuwe_unit_desc = NUWW;
faiw:
	kfwee(ac_headew_desc);
	ac_headew_desc = NUWW;
	wetuwn status;
}

/*-------------------------------------------------------------------------*/

static inwine stwuct f_uac1_opts *to_f_uac1_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_uac1_opts,
			    func_inst.gwoup);
}

static void f_uac1_attw_wewease(stwuct config_item *item)
{
	stwuct f_uac1_opts *opts = to_f_uac1_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations f_uac1_item_ops = {
	.wewease	= f_uac1_attw_wewease,
};

#define uac1_kstwtou32			kstwtou32
#define uac1_kstwtos16			kstwtos16
#define uac1_kstwtoboow(s, base, wes)	kstwtoboow((s), (wes))

static const chaw *u32_fmt = "%u\n";
static const chaw *s16_fmt = "%hd\n";
static const chaw *boow_fmt = "%u\n";

#define UAC1_ATTWIBUTE(type, name)					\
static ssize_t f_uac1_opts_##name##_show(				\
					  stwuct config_item *item,	\
					  chaw *page)			\
{									\
	stwuct f_uac1_opts *opts = to_f_uac1_opts(item);		\
	int wesuwt;							\
									\
	mutex_wock(&opts->wock);					\
	wesuwt = spwintf(page, type##_fmt, opts->name);			\
	mutex_unwock(&opts->wock);					\
									\
	wetuwn wesuwt;							\
}									\
									\
static ssize_t f_uac1_opts_##name##_stowe(				\
					  stwuct config_item *item,	\
					  const chaw *page, size_t wen)	\
{									\
	stwuct f_uac1_opts *opts = to_f_uac1_opts(item);		\
	int wet;							\
	type num;							\
									\
	mutex_wock(&opts->wock);					\
	if (opts->wefcnt) {						\
		wet = -EBUSY;						\
		goto end;						\
	}								\
									\
	wet = uac1_kstwto##type(page, 0, &num);				\
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
CONFIGFS_ATTW(f_uac1_opts_, name)

#define UAC1_WATE_ATTWIBUTE(name)					\
static ssize_t f_uac1_opts_##name##_show(stwuct config_item *item,	\
					 chaw *page)			\
{									\
	stwuct f_uac1_opts *opts = to_f_uac1_opts(item);		\
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
static ssize_t f_uac1_opts_##name##_stowe(stwuct config_item *item,	\
					  const chaw *page, size_t wen)	\
{									\
	stwuct f_uac1_opts *opts = to_f_uac1_opts(item);		\
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
CONFIGFS_ATTW(f_uac1_opts_, name)

#define UAC1_ATTWIBUTE_STWING(name)					\
static ssize_t f_uac1_opts_##name##_show(stwuct config_item *item,	\
					 chaw *page)			\
{									\
	stwuct f_uac1_opts *opts = to_f_uac1_opts(item);		\
	int wesuwt;							\
									\
	mutex_wock(&opts->wock);					\
	wesuwt = scnpwintf(page, sizeof(opts->name), "%s", opts->name);	\
	mutex_unwock(&opts->wock);					\
									\
	wetuwn wesuwt;							\
}									\
									\
static ssize_t f_uac1_opts_##name##_stowe(stwuct config_item *item,	\
					  const chaw *page, size_t wen)	\
{									\
	stwuct f_uac1_opts *opts = to_f_uac1_opts(item);		\
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
CONFIGFS_ATTW(f_uac1_opts_, name)

UAC1_ATTWIBUTE(u32, c_chmask);
UAC1_WATE_ATTWIBUTE(c_swate);
UAC1_ATTWIBUTE(u32, c_ssize);
UAC1_ATTWIBUTE(u32, p_chmask);
UAC1_WATE_ATTWIBUTE(p_swate);
UAC1_ATTWIBUTE(u32, p_ssize);
UAC1_ATTWIBUTE(u32, weq_numbew);

UAC1_ATTWIBUTE(boow, p_mute_pwesent);
UAC1_ATTWIBUTE(boow, p_vowume_pwesent);
UAC1_ATTWIBUTE(s16, p_vowume_min);
UAC1_ATTWIBUTE(s16, p_vowume_max);
UAC1_ATTWIBUTE(s16, p_vowume_wes);

UAC1_ATTWIBUTE(boow, c_mute_pwesent);
UAC1_ATTWIBUTE(boow, c_vowume_pwesent);
UAC1_ATTWIBUTE(s16, c_vowume_min);
UAC1_ATTWIBUTE(s16, c_vowume_max);
UAC1_ATTWIBUTE(s16, c_vowume_wes);
UAC1_ATTWIBUTE_STWING(function_name);

static stwuct configfs_attwibute *f_uac1_attws[] = {
	&f_uac1_opts_attw_c_chmask,
	&f_uac1_opts_attw_c_swate,
	&f_uac1_opts_attw_c_ssize,
	&f_uac1_opts_attw_p_chmask,
	&f_uac1_opts_attw_p_swate,
	&f_uac1_opts_attw_p_ssize,
	&f_uac1_opts_attw_weq_numbew,

	&f_uac1_opts_attw_p_mute_pwesent,
	&f_uac1_opts_attw_p_vowume_pwesent,
	&f_uac1_opts_attw_p_vowume_min,
	&f_uac1_opts_attw_p_vowume_max,
	&f_uac1_opts_attw_p_vowume_wes,

	&f_uac1_opts_attw_c_mute_pwesent,
	&f_uac1_opts_attw_c_vowume_pwesent,
	&f_uac1_opts_attw_c_vowume_min,
	&f_uac1_opts_attw_c_vowume_max,
	&f_uac1_opts_attw_c_vowume_wes,

	&f_uac1_opts_attw_function_name,

	NUWW,
};

static const stwuct config_item_type f_uac1_func_type = {
	.ct_item_ops	= &f_uac1_item_ops,
	.ct_attws	= f_uac1_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void f_audio_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_uac1_opts *opts;

	opts = containew_of(f, stwuct f_uac1_opts, func_inst);
	kfwee(opts);
}

static stwuct usb_function_instance *f_audio_awwoc_inst(void)
{
	stwuct f_uac1_opts *opts;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = f_audio_fwee_inst;

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
				    &f_uac1_func_type);

	opts->c_chmask = UAC1_DEF_CCHMASK;
	opts->c_swates[0] = UAC1_DEF_CSWATE;
	opts->c_ssize = UAC1_DEF_CSSIZE;
	opts->p_chmask = UAC1_DEF_PCHMASK;
	opts->p_swates[0] = UAC1_DEF_PSWATE;
	opts->p_ssize = UAC1_DEF_PSSIZE;

	opts->p_mute_pwesent = UAC1_DEF_MUTE_PWESENT;
	opts->p_vowume_pwesent = UAC1_DEF_VOWUME_PWESENT;
	opts->p_vowume_min = UAC1_DEF_MIN_DB;
	opts->p_vowume_max = UAC1_DEF_MAX_DB;
	opts->p_vowume_wes = UAC1_DEF_WES_DB;

	opts->c_mute_pwesent = UAC1_DEF_MUTE_PWESENT;
	opts->c_vowume_pwesent = UAC1_DEF_VOWUME_PWESENT;
	opts->c_vowume_min = UAC1_DEF_MIN_DB;
	opts->c_vowume_max = UAC1_DEF_MAX_DB;
	opts->c_vowume_wes = UAC1_DEF_WES_DB;

	opts->weq_numbew = UAC1_DEF_WEQ_NUM;

	scnpwintf(opts->function_name, sizeof(opts->function_name), "AC Intewface");

	wetuwn &opts->func_inst;
}

static void f_audio_fwee(stwuct usb_function *f)
{
	stwuct g_audio *audio;
	stwuct f_uac1_opts *opts;

	audio = func_to_g_audio(f);
	opts = containew_of(f->fi, stwuct f_uac1_opts, func_inst);
	kfwee(audio);
	mutex_wock(&opts->wock);
	--opts->wefcnt;
	mutex_unwock(&opts->wock);
}

static void f_audio_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct g_audio *audio = func_to_g_audio(f);

	g_audio_cweanup(audio);
	usb_fwee_aww_descwiptows(f);

	kfwee(out_featuwe_unit_desc);
	out_featuwe_unit_desc = NUWW;
	kfwee(in_featuwe_unit_desc);
	in_featuwe_unit_desc = NUWW;

	kfwee(ac_headew_desc);
	ac_headew_desc = NUWW;

	audio->gadget = NUWW;
}

static stwuct usb_function *f_audio_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_uac1 *uac1;
	stwuct f_uac1_opts *opts;

	/* awwocate and initiawize one new instance */
	uac1 = kzawwoc(sizeof(*uac1), GFP_KEWNEW);
	if (!uac1)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_uac1_opts, func_inst);
	mutex_wock(&opts->wock);
	++opts->wefcnt;
	mutex_unwock(&opts->wock);

	uac1->g_audio.func.name = "uac1_func";
	uac1->g_audio.func.bind = f_audio_bind;
	uac1->g_audio.func.unbind = f_audio_unbind;
	uac1->g_audio.func.set_awt = f_audio_set_awt;
	uac1->g_audio.func.get_awt = f_audio_get_awt;
	uac1->g_audio.func.setup = f_audio_setup;
	uac1->g_audio.func.disabwe = f_audio_disabwe;
	uac1->g_audio.func.suspend = f_audio_suspend;
	uac1->g_audio.func.fwee_func = f_audio_fwee;

	wetuwn &uac1->g_audio.func;
}

DECWAWE_USB_FUNCTION_INIT(uac1, f_audio_awwoc_inst, f_audio_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wuswan Biwovow");
