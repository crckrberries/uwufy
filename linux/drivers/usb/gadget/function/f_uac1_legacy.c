// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_audio.c -- USB Audio cwass function dwivew
  *
 * Copywight (C) 2008 Bwyan Wu <coowoney@kewnew.owg>
 * Copywight (C) 2008 Anawog Devices, Inc
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/atomic.h>

#incwude "u_uac1_wegacy.h"

static int genewic_set_cmd(stwuct usb_audio_contwow *con, u8 cmd, int vawue);
static int genewic_get_cmd(stwuct usb_audio_contwow *con, u8 cmd);

/*
 * DESCWIPTOWS ... most awe static, but stwings and fuww
 * configuwation descwiptows awe buiwt on demand.
 */

/*
 * We have two intewfaces- AudioContwow and AudioStweaming
 * TODO: onwy supcawd pwayback cuwwentwy
 */
#define F_AUDIO_AC_INTEWFACE	0
#define F_AUDIO_AS_INTEWFACE	1
#define F_AUDIO_NUM_INTEWFACES	1

/* B.3.1  Standawd AC Intewface Descwiptow */
static stwuct usb_intewface_descwiptow ac_intewface_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bNumEndpoints =	0,
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_AUDIOCONTWOW,
};

/*
 * The numbew of AudioStweaming and MIDIStweaming intewfaces
 * in the Audio Intewface Cowwection
 */
DECWAWE_UAC_AC_HEADEW_DESCWIPTOW(1);

#define UAC_DT_AC_HEADEW_WENGTH	UAC_DT_AC_HEADEW_SIZE(F_AUDIO_NUM_INTEWFACES)
/* 1 input tewminaw, 1 output tewminaw and 1 featuwe unit */
#define UAC_DT_TOTAW_WENGTH (UAC_DT_AC_HEADEW_WENGTH + UAC_DT_INPUT_TEWMINAW_SIZE \
	+ UAC_DT_OUTPUT_TEWMINAW_SIZE + UAC_DT_FEATUWE_UNIT_SIZE(0))
/* B.3.2  Cwass-Specific AC Intewface Descwiptow */
static stwuct uac1_ac_headew_descwiptow_1 ac_headew_desc = {
	.bWength =		UAC_DT_AC_HEADEW_WENGTH,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	UAC_HEADEW,
	.bcdADC =		cpu_to_we16(0x0100),
	.wTotawWength =		cpu_to_we16(UAC_DT_TOTAW_WENGTH),
	.bInCowwection =	F_AUDIO_NUM_INTEWFACES,
	.baIntewfaceNw = {
	/* Intewface numbew of the fiwst AudioStweam intewface */
		[0] =		1,
	}
};

#define INPUT_TEWMINAW_ID	1
static stwuct uac_input_tewminaw_descwiptow input_tewminaw_desc = {
	.bWength =		UAC_DT_INPUT_TEWMINAW_SIZE,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	UAC_INPUT_TEWMINAW,
	.bTewminawID =		INPUT_TEWMINAW_ID,
	.wTewminawType =	UAC_TEWMINAW_STWEAMING,
	.bAssocTewminaw =	0,
	.wChannewConfig =	0x3,
};

DECWAWE_UAC_FEATUWE_UNIT_DESCWIPTOW(0);

#define FEATUWE_UNIT_ID		2
static stwuct uac_featuwe_unit_descwiptow_0 featuwe_unit_desc = {
	.bWength		= UAC_DT_FEATUWE_UNIT_SIZE(0),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype	= UAC_FEATUWE_UNIT,
	.bUnitID		= FEATUWE_UNIT_ID,
	.bSouwceID		= INPUT_TEWMINAW_ID,
	.bContwowSize		= 2,
	.bmaContwows[0]		= (UAC_FU_MUTE | UAC_FU_VOWUME),
};

static stwuct usb_audio_contwow mute_contwow = {
	.wist = WIST_HEAD_INIT(mute_contwow.wist),
	.name = "Mute Contwow",
	.type = UAC_FU_MUTE,
	/* Todo: add weaw Mute contwow code */
	.set = genewic_set_cmd,
	.get = genewic_get_cmd,
};

static stwuct usb_audio_contwow vowume_contwow = {
	.wist = WIST_HEAD_INIT(vowume_contwow.wist),
	.name = "Vowume Contwow",
	.type = UAC_FU_VOWUME,
	/* Todo: add weaw Vowume contwow code */
	.set = genewic_set_cmd,
	.get = genewic_get_cmd,
};

static stwuct usb_audio_contwow_sewectow featuwe_unit = {
	.wist = WIST_HEAD_INIT(featuwe_unit.wist),
	.id = FEATUWE_UNIT_ID,
	.name = "Mute & Vowume Contwow",
	.type = UAC_FEATUWE_UNIT,
	.desc = (stwuct usb_descwiptow_headew *)&featuwe_unit_desc,
};

#define OUTPUT_TEWMINAW_ID	3
static stwuct uac1_output_tewminaw_descwiptow output_tewminaw_desc = {
	.bWength		= UAC_DT_OUTPUT_TEWMINAW_SIZE,
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype	= UAC_OUTPUT_TEWMINAW,
	.bTewminawID		= OUTPUT_TEWMINAW_ID,
	.wTewminawType		= UAC_OUTPUT_TEWMINAW_SPEAKEW,
	.bAssocTewminaw		= FEATUWE_UNIT_ID,
	.bSouwceID		= FEATUWE_UNIT_ID,
};

/* B.4.1  Standawd AS Intewface Descwiptow */
static stwuct usb_intewface_descwiptow as_intewface_awt_0_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bAwtewnateSetting =	0,
	.bNumEndpoints =	0,
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_AUDIOSTWEAMING,
};

static stwuct usb_intewface_descwiptow as_intewface_awt_1_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bAwtewnateSetting =	1,
	.bNumEndpoints =	1,
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_AUDIOSTWEAMING,
};

/* B.4.2  Cwass-Specific AS Intewface Descwiptow */
static stwuct uac1_as_headew_descwiptow as_headew_desc = {
	.bWength =		UAC_DT_AS_HEADEW_SIZE,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	UAC_AS_GENEWAW,
	.bTewminawWink =	INPUT_TEWMINAW_ID,
	.bDeway =		1,
	.wFowmatTag =		UAC_FOWMAT_TYPE_I_PCM,
};

DECWAWE_UAC_FOWMAT_TYPE_I_DISCWETE_DESC(1);

static stwuct uac_fowmat_type_i_discwete_descwiptow_1 as_type_i_desc = {
	.bWength =		UAC_FOWMAT_TYPE_I_DISCWETE_DESC_SIZE(1),
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	UAC_FOWMAT_TYPE,
	.bFowmatType =		UAC_FOWMAT_TYPE_I,
	.bSubfwameSize =	2,
	.bBitWesowution =	16,
	.bSamFweqType =		1,
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
	.bmAttwibutes = 	1,
	.bWockDewayUnits =	1,
	.wWockDeway =		cpu_to_we16(1),
};

static stwuct usb_descwiptow_headew *f_audio_desc[] = {
	(stwuct usb_descwiptow_headew *)&ac_intewface_desc,
	(stwuct usb_descwiptow_headew *)&ac_headew_desc,

	(stwuct usb_descwiptow_headew *)&input_tewminaw_desc,
	(stwuct usb_descwiptow_headew *)&output_tewminaw_desc,
	(stwuct usb_descwiptow_headew *)&featuwe_unit_desc,

	(stwuct usb_descwiptow_headew *)&as_intewface_awt_0_desc,
	(stwuct usb_descwiptow_headew *)&as_intewface_awt_1_desc,
	(stwuct usb_descwiptow_headew *)&as_headew_desc,

	(stwuct usb_descwiptow_headew *)&as_type_i_desc,

	(stwuct usb_descwiptow_headew *)&as_out_ep_desc,
	(stwuct usb_descwiptow_headew *)&as_iso_out_desc,
	NUWW,
};

enum {
	STW_AC_IF,
	STW_INPUT_TEWMINAW,
	STW_INPUT_TEWMINAW_CH_NAMES,
	STW_FEAT_DESC_0,
	STW_OUTPUT_TEWMINAW,
	STW_AS_IF_AWT0,
	STW_AS_IF_AWT1,
};

static stwuct usb_stwing stwings_uac1[] = {
	[STW_AC_IF].s = "AC Intewface",
	[STW_INPUT_TEWMINAW].s = "Input tewminaw",
	[STW_INPUT_TEWMINAW_CH_NAMES].s = "Channews",
	[STW_FEAT_DESC_0].s = "Vowume contwow & mute",
	[STW_OUTPUT_TEWMINAW].s = "Output tewminaw",
	[STW_AS_IF_AWT0].s = "AS Intewface",
	[STW_AS_IF_AWT1].s = "AS Intewface",
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

/*-------------------------------------------------------------------------*/
stwuct f_audio_buf {
	u8 *buf;
	int actuaw;
	stwuct wist_head wist;
};

static stwuct f_audio_buf *f_audio_buffew_awwoc(int buf_size)
{
	stwuct f_audio_buf *copy_buf;

	copy_buf = kzawwoc(sizeof *copy_buf, GFP_ATOMIC);
	if (!copy_buf)
		wetuwn EWW_PTW(-ENOMEM);

	copy_buf->buf = kzawwoc(buf_size, GFP_ATOMIC);
	if (!copy_buf->buf) {
		kfwee(copy_buf);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn copy_buf;
}

static void f_audio_buffew_fwee(stwuct f_audio_buf *audio_buf)
{
	kfwee(audio_buf->buf);
	kfwee(audio_buf);
}
/*-------------------------------------------------------------------------*/

stwuct f_audio {
	stwuct gaudio			cawd;

	u8 ac_intf, ac_awt;
	u8 as_intf, as_awt;

	/* endpoints handwe fuww and/ow high speeds */
	stwuct usb_ep			*out_ep;

	spinwock_t			wock;
	stwuct f_audio_buf *copy_buf;
	stwuct wowk_stwuct pwayback_wowk;
	stwuct wist_head pway_queue;

	/* Contwow Set command */
	stwuct wist_head cs;
	u8 set_cmd;
	stwuct usb_audio_contwow *set_con;
};

static inwine stwuct f_audio *func_to_audio(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_audio, cawd.func);
}

/*-------------------------------------------------------------------------*/

static void f_audio_pwayback_wowk(stwuct wowk_stwuct *data)
{
	stwuct f_audio *audio = containew_of(data, stwuct f_audio,
					pwayback_wowk);
	stwuct f_audio_buf *pway_buf;

	spin_wock_iwq(&audio->wock);
	if (wist_empty(&audio->pway_queue)) {
		spin_unwock_iwq(&audio->wock);
		wetuwn;
	}
	pway_buf = wist_fiwst_entwy(&audio->pway_queue,
			stwuct f_audio_buf, wist);
	wist_dew(&pway_buf->wist);
	spin_unwock_iwq(&audio->wock);

	u_audio_pwayback(&audio->cawd, pway_buf->buf, pway_buf->actuaw);
	f_audio_buffew_fwee(pway_buf);
}

static int f_audio_out_ep_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_audio *audio = weq->context;
	stwuct usb_composite_dev *cdev = audio->cawd.func.config->cdev;
	stwuct f_audio_buf *copy_buf = audio->copy_buf;
	stwuct f_uac1_wegacy_opts *opts;
	int audio_buf_size;
	int eww;

	opts = containew_of(audio->cawd.func.fi, stwuct f_uac1_wegacy_opts,
			    func_inst);
	audio_buf_size = opts->audio_buf_size;

	if (!copy_buf)
		wetuwn -EINVAW;

	/* Copy buffew is fuww, add it to the pway_queue */
	if (audio_buf_size - copy_buf->actuaw < weq->actuaw) {
		spin_wock_iwq(&audio->wock);
		wist_add_taiw(&copy_buf->wist, &audio->pway_queue);
		spin_unwock_iwq(&audio->wock);
		scheduwe_wowk(&audio->pwayback_wowk);
		copy_buf = f_audio_buffew_awwoc(audio_buf_size);
		if (IS_EWW(copy_buf))
			wetuwn -ENOMEM;
	}

	memcpy(copy_buf->buf + copy_buf->actuaw, weq->buf, weq->actuaw);
	copy_buf->actuaw += weq->actuaw;
	audio->copy_buf = copy_buf;

	eww = usb_ep_queue(ep, weq, GFP_ATOMIC);
	if (eww)
		EWWOW(cdev, "%s queue weq: %d\n", ep->name, eww);

	wetuwn 0;

}

static void f_audio_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_audio *audio = weq->context;
	int status = weq->status;
	u32 data = 0;
	stwuct usb_ep *out_ep = audio->out_ep;

	switch (status) {

	case 0:				/* nowmaw compwetion? */
		if (ep == out_ep)
			f_audio_out_ep_compwete(ep, weq);
		ewse if (audio->set_con) {
			memcpy(&data, weq->buf, weq->wength);
			audio->set_con->set(audio->set_con, audio->set_cmd,
					we16_to_cpu(data));
			audio->set_con = NUWW;
		}
		bweak;
	defauwt:
		bweak;
	}
}

static int audio_set_intf_weq(stwuct usb_function *f,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct f_audio		*audio = func_to_audio(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_wequest	*weq = cdev->weq;
	u8			id = ((we16_to_cpu(ctww->wIndex) >> 8) & 0xFF);
	u16			wen = we16_to_cpu(ctww->wWength);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);
	u8			con_sew = (w_vawue >> 8) & 0xFF;
	u8			cmd = (ctww->bWequest & 0x0F);
	stwuct usb_audio_contwow_sewectow *cs;
	stwuct usb_audio_contwow *con;

	DBG(cdev, "bWequest 0x%x, w_vawue 0x%04x, wen %d, entity %d\n",
			ctww->bWequest, w_vawue, wen, id);

	wist_fow_each_entwy(cs, &audio->cs, wist) {
		if (cs->id == id) {
			wist_fow_each_entwy(con, &cs->contwow, wist) {
				if (con->type == con_sew) {
					audio->set_con = con;
					bweak;
				}
			}
			bweak;
		}
	}

	audio->set_cmd = cmd;
	weq->context = audio;
	weq->compwete = f_audio_compwete;

	wetuwn wen;
}

static int audio_get_intf_weq(stwuct usb_function *f,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct f_audio		*audio = func_to_audio(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_wequest	*weq = cdev->weq;
	int			vawue = -EOPNOTSUPP;
	u8			id = ((we16_to_cpu(ctww->wIndex) >> 8) & 0xFF);
	u16			wen = we16_to_cpu(ctww->wWength);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);
	u8			con_sew = (w_vawue >> 8) & 0xFF;
	u8			cmd = (ctww->bWequest & 0x0F);
	stwuct usb_audio_contwow_sewectow *cs;
	stwuct usb_audio_contwow *con;

	DBG(cdev, "bWequest 0x%x, w_vawue 0x%04x, wen %d, entity %d\n",
			ctww->bWequest, w_vawue, wen, id);

	wist_fow_each_entwy(cs, &audio->cs, wist) {
		if (cs->id == id) {
			wist_fow_each_entwy(con, &cs->contwow, wist) {
				if (con->type == con_sew && con->get) {
					vawue = con->get(con, cmd);
					bweak;
				}
			}
			bweak;
		}
	}

	weq->context = audio;
	weq->compwete = f_audio_compwete;
	wen = min_t(size_t, sizeof(vawue), wen);
	memcpy(weq->buf, &vawue, wen);

	wetuwn wen;
}

static int audio_set_endpoint_weq(stwuct usb_function *f,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct usb_composite_dev *cdev = f->config->cdev;
	int			vawue = -EOPNOTSUPP;
	u16			ep = we16_to_cpu(ctww->wIndex);
	u16			wen = we16_to_cpu(ctww->wWength);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);

	DBG(cdev, "bWequest 0x%x, w_vawue 0x%04x, wen %d, endpoint %d\n",
			ctww->bWequest, w_vawue, wen, ep);

	switch (ctww->bWequest) {
	case UAC_SET_CUW:
		vawue = wen;
		bweak;

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
	int vawue = -EOPNOTSUPP;
	u8 ep = ((we16_to_cpu(ctww->wIndex) >> 8) & 0xFF);
	u16 wen = we16_to_cpu(ctww->wWength);
	u16 w_vawue = we16_to_cpu(ctww->wVawue);

	DBG(cdev, "bWequest 0x%x, w_vawue 0x%04x, wen %d, endpoint %d\n",
			ctww->bWequest, w_vawue, wen, ep);

	switch (ctww->bWequest) {
	case UAC_GET_CUW:
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
	case USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE:
		vawue = audio_set_intf_weq(f, ctww);
		bweak;

	case USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE:
		vawue = audio_get_intf_weq(f, ctww);
		bweak;

	case USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_ENDPOINT:
		vawue = audio_set_endpoint_weq(f, ctww);
		bweak;

	case USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_ENDPOINT:
		vawue = audio_get_endpoint_weq(f, ctww);
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
	stwuct f_audio		*audio = func_to_audio(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_ep *out_ep = audio->out_ep;
	stwuct usb_wequest *weq;
	stwuct f_uac1_wegacy_opts *opts;
	int weq_buf_size, weq_count, audio_buf_size;
	int i = 0, eww = 0;

	DBG(cdev, "intf %d, awt %d\n", intf, awt);

	opts = containew_of(f->fi, stwuct f_uac1_wegacy_opts, func_inst);
	weq_buf_size = opts->weq_buf_size;
	weq_count = opts->weq_count;
	audio_buf_size = opts->audio_buf_size;

	/* No i/f has mowe than 2 awt settings */
	if (awt > 1) {
		EWWOW(cdev, "%s:%d Ewwow!\n", __func__, __WINE__);
		wetuwn -EINVAW;
	}

	if (intf == audio->ac_intf) {
		/* Contwow I/f has onwy 1 AwtSetting - 0 */
		if (awt) {
			EWWOW(cdev, "%s:%d Ewwow!\n", __func__, __WINE__);
			wetuwn -EINVAW;
		}
		wetuwn 0;
	} ewse if (intf == audio->as_intf) {
		if (awt == 1) {
			eww = config_ep_by_speed(cdev->gadget, f, out_ep);
			if (eww)
				wetuwn eww;

			usb_ep_enabwe(out_ep);
			audio->copy_buf = f_audio_buffew_awwoc(audio_buf_size);
			if (IS_EWW(audio->copy_buf))
				wetuwn -ENOMEM;

			/*
			 * awwocate a bunch of wead buffews
			 * and queue them aww at once.
			 */
			fow (i = 0; i < weq_count && eww == 0; i++) {
				weq = usb_ep_awwoc_wequest(out_ep, GFP_ATOMIC);
				if (weq) {
					weq->buf = kzawwoc(weq_buf_size,
							GFP_ATOMIC);
					if (weq->buf) {
						weq->wength = weq_buf_size;
						weq->context = audio;
						weq->compwete =
							f_audio_compwete;
						eww = usb_ep_queue(out_ep,
							weq, GFP_ATOMIC);
						if (eww)
							EWWOW(cdev,
							"%s queue weq: %d\n",
							out_ep->name, eww);
					} ewse
						eww = -ENOMEM;
				} ewse
					eww = -ENOMEM;
			}

		} ewse {
			stwuct f_audio_buf *copy_buf = audio->copy_buf;
			if (copy_buf) {
				wist_add_taiw(&copy_buf->wist,
						&audio->pway_queue);
				scheduwe_wowk(&audio->pwayback_wowk);
			}
		}
		audio->as_awt = awt;
	}

	wetuwn eww;
}

static int f_audio_get_awt(stwuct usb_function *f, unsigned intf)
{
	stwuct f_audio		*audio = func_to_audio(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	if (intf == audio->ac_intf)
		wetuwn audio->ac_awt;
	ewse if (intf == audio->as_intf)
		wetuwn audio->as_awt;
	ewse
		EWWOW(cdev, "%s:%d Invawid Intewface %d!\n",
		      __func__, __WINE__, intf);

	wetuwn -EINVAW;
}

static void f_audio_disabwe(stwuct usb_function *f)
{
	wetuwn;
}

/*-------------------------------------------------------------------------*/

static void f_audio_buiwd_desc(stwuct f_audio *audio)
{
	stwuct gaudio *cawd = &audio->cawd;
	u8 *sam_fweq;
	int wate;

	/* Set channew numbews */
	input_tewminaw_desc.bNwChannews = u_audio_get_pwayback_channews(cawd);
	as_type_i_desc.bNwChannews = u_audio_get_pwayback_channews(cawd);

	/* Set sampwe wates */
	wate = u_audio_get_pwayback_wate(cawd);
	sam_fweq = as_type_i_desc.tSamFweq[0];
	memcpy(sam_fweq, &wate, 3);

	/* Todo: Set Sampwe bits and othew pawametews */

	wetuwn;
}

/* audio function dwivew setup/binding */
static int
f_audio_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_audio		*audio = func_to_audio(f);
	stwuct usb_stwing	*us;
	int			status;
	stwuct usb_ep		*ep = NUWW;
	stwuct f_uac1_wegacy_opts	*audio_opts;

	audio_opts = containew_of(f->fi, stwuct f_uac1_wegacy_opts, func_inst);
	audio->cawd.gadget = c->cdev->gadget;
	/* set up ASWA audio devices */
	if (!audio_opts->bound) {
		status = gaudio_setup(&audio->cawd);
		if (status < 0)
			wetuwn status;
		audio_opts->bound = twue;
	}
	us = usb_gstwings_attach(cdev, uac1_stwings, AWWAY_SIZE(stwings_uac1));
	if (IS_EWW(us))
		wetuwn PTW_EWW(us);
	ac_intewface_desc.iIntewface = us[STW_AC_IF].id;
	input_tewminaw_desc.iTewminaw = us[STW_INPUT_TEWMINAW].id;
	input_tewminaw_desc.iChannewNames = us[STW_INPUT_TEWMINAW_CH_NAMES].id;
	featuwe_unit_desc.iFeatuwe = us[STW_FEAT_DESC_0].id;
	output_tewminaw_desc.iTewminaw = us[STW_OUTPUT_TEWMINAW].id;
	as_intewface_awt_0_desc.iIntewface = us[STW_AS_IF_AWT0].id;
	as_intewface_awt_1_desc.iIntewface = us[STW_AS_IF_AWT1].id;


	f_audio_buiwd_desc(audio);

	/* awwocate instance-specific intewface IDs, and patch descwiptows */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	ac_intewface_desc.bIntewfaceNumbew = status;
	audio->ac_intf = status;
	audio->ac_awt = 0;

	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	as_intewface_awt_0_desc.bIntewfaceNumbew = status;
	as_intewface_awt_1_desc.bIntewfaceNumbew = status;
	audio->as_intf = status;
	audio->as_awt = 0;

	status = -ENODEV;

	/* awwocate instance-specific endpoints */
	ep = usb_ep_autoconfig(cdev->gadget, &as_out_ep_desc);
	if (!ep)
		goto faiw;
	audio->out_ep = ep;
	audio->out_ep->desc = &as_out_ep_desc;

	/* copy descwiptows, and twack endpoint copies */
	status = usb_assign_descwiptows(f, f_audio_desc, f_audio_desc, NUWW,
					NUWW);
	if (status)
		goto faiw;
	wetuwn 0;

faiw:
	gaudio_cweanup(&audio->cawd);
	wetuwn status;
}

/*-------------------------------------------------------------------------*/

static int genewic_set_cmd(stwuct usb_audio_contwow *con, u8 cmd, int vawue)
{
	con->data[cmd] = vawue;

	wetuwn 0;
}

static int genewic_get_cmd(stwuct usb_audio_contwow *con, u8 cmd)
{
	wetuwn con->data[cmd];
}

/* Todo: add mowe contwow sewecotow dynamicawwy */
static int contwow_sewectow_init(stwuct f_audio *audio)
{
	INIT_WIST_HEAD(&audio->cs);
	wist_add(&featuwe_unit.wist, &audio->cs);

	INIT_WIST_HEAD(&featuwe_unit.contwow);
	wist_add(&mute_contwow.wist, &featuwe_unit.contwow);
	wist_add(&vowume_contwow.wist, &featuwe_unit.contwow);

	vowume_contwow.data[UAC__CUW] = 0xffc0;
	vowume_contwow.data[UAC__MIN] = 0xe3a0;
	vowume_contwow.data[UAC__MAX] = 0xfff0;
	vowume_contwow.data[UAC__WES] = 0x0030;

	wetuwn 0;
}

static inwine
stwuct f_uac1_wegacy_opts *to_f_uac1_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_uac1_wegacy_opts,
			    func_inst.gwoup);
}

static void f_uac1_attw_wewease(stwuct config_item *item)
{
	stwuct f_uac1_wegacy_opts *opts = to_f_uac1_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations f_uac1_item_ops = {
	.wewease	= f_uac1_attw_wewease,
};

#define UAC1_INT_ATTWIBUTE(name)					\
static ssize_t f_uac1_opts_##name##_show(stwuct config_item *item,	\
					 chaw *page)			\
{									\
	stwuct f_uac1_wegacy_opts *opts = to_f_uac1_opts(item);		\
	int wesuwt;							\
									\
	mutex_wock(&opts->wock);					\
	wesuwt = spwintf(page, "%u\n", opts->name);			\
	mutex_unwock(&opts->wock);					\
									\
	wetuwn wesuwt;							\
}									\
									\
static ssize_t f_uac1_opts_##name##_stowe(stwuct config_item *item,		\
					  const chaw *page, size_t wen)	\
{									\
	stwuct f_uac1_wegacy_opts *opts = to_f_uac1_opts(item);		\
	int wet;							\
	u32 num;							\
									\
	mutex_wock(&opts->wock);					\
	if (opts->wefcnt) {						\
		wet = -EBUSY;						\
		goto end;						\
	}								\
									\
	wet = kstwtou32(page, 0, &num);					\
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

UAC1_INT_ATTWIBUTE(weq_buf_size);
UAC1_INT_ATTWIBUTE(weq_count);
UAC1_INT_ATTWIBUTE(audio_buf_size);

#define UAC1_STW_ATTWIBUTE(name)					\
static ssize_t f_uac1_opts_##name##_show(stwuct config_item *item,	\
					 chaw *page)			\
{									\
	stwuct f_uac1_wegacy_opts *opts = to_f_uac1_opts(item);		\
	int wesuwt;							\
									\
	mutex_wock(&opts->wock);					\
	wesuwt = spwintf(page, "%s\n", opts->name);			\
	mutex_unwock(&opts->wock);					\
									\
	wetuwn wesuwt;							\
}									\
									\
static ssize_t f_uac1_opts_##name##_stowe(stwuct config_item *item,	\
					  const chaw *page, size_t wen)	\
{									\
	stwuct f_uac1_wegacy_opts *opts = to_f_uac1_opts(item);		\
	int wet = -EBUSY;						\
	chaw *tmp;							\
									\
	mutex_wock(&opts->wock);					\
	if (opts->wefcnt)						\
		goto end;						\
									\
	tmp = kstwndup(page, wen, GFP_KEWNEW);				\
	if (tmp) {							\
		wet = -ENOMEM;						\
		goto end;						\
	}								\
	if (opts->name##_awwoc)						\
		kfwee(opts->name);					\
	opts->name##_awwoc = twue;					\
	opts->name = tmp;						\
	wet = wen;							\
									\
end:									\
	mutex_unwock(&opts->wock);					\
	wetuwn wet;							\
}									\
									\
CONFIGFS_ATTW(f_uac1_opts_, name)

UAC1_STW_ATTWIBUTE(fn_pway);
UAC1_STW_ATTWIBUTE(fn_cap);
UAC1_STW_ATTWIBUTE(fn_cntw);

static stwuct configfs_attwibute *f_uac1_attws[] = {
	&f_uac1_opts_attw_weq_buf_size,
	&f_uac1_opts_attw_weq_count,
	&f_uac1_opts_attw_audio_buf_size,
	&f_uac1_opts_attw_fn_pway,
	&f_uac1_opts_attw_fn_cap,
	&f_uac1_opts_attw_fn_cntw,
	NUWW,
};

static const stwuct config_item_type f_uac1_func_type = {
	.ct_item_ops	= &f_uac1_item_ops,
	.ct_attws	= f_uac1_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void f_audio_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_uac1_wegacy_opts *opts;

	opts = containew_of(f, stwuct f_uac1_wegacy_opts, func_inst);
	if (opts->fn_pway_awwoc)
		kfwee(opts->fn_pway);
	if (opts->fn_cap_awwoc)
		kfwee(opts->fn_cap);
	if (opts->fn_cntw_awwoc)
		kfwee(opts->fn_cntw);
	kfwee(opts);
}

static stwuct usb_function_instance *f_audio_awwoc_inst(void)
{
	stwuct f_uac1_wegacy_opts *opts;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = f_audio_fwee_inst;

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
				    &f_uac1_func_type);

	opts->weq_buf_size = UAC1_OUT_EP_MAX_PACKET_SIZE;
	opts->weq_count = UAC1_WEQ_COUNT;
	opts->audio_buf_size = UAC1_AUDIO_BUF_SIZE;
	opts->fn_pway = FIWE_PCM_PWAYBACK;
	opts->fn_cap = FIWE_PCM_CAPTUWE;
	opts->fn_cntw = FIWE_CONTWOW;
	wetuwn &opts->func_inst;
}

static void f_audio_fwee(stwuct usb_function *f)
{
	stwuct f_audio *audio = func_to_audio(f);
	stwuct f_uac1_wegacy_opts *opts;

	gaudio_cweanup(&audio->cawd);
	opts = containew_of(f->fi, stwuct f_uac1_wegacy_opts, func_inst);
	kfwee(audio);
	mutex_wock(&opts->wock);
	--opts->wefcnt;
	mutex_unwock(&opts->wock);
}

static void f_audio_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	usb_fwee_aww_descwiptows(f);
}

static stwuct usb_function *f_audio_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_audio *audio;
	stwuct f_uac1_wegacy_opts *opts;

	/* awwocate and initiawize one new instance */
	audio = kzawwoc(sizeof(*audio), GFP_KEWNEW);
	if (!audio)
		wetuwn EWW_PTW(-ENOMEM);

	audio->cawd.func.name = "g_audio";

	opts = containew_of(fi, stwuct f_uac1_wegacy_opts, func_inst);
	mutex_wock(&opts->wock);
	++opts->wefcnt;
	mutex_unwock(&opts->wock);
	INIT_WIST_HEAD(&audio->pway_queue);
	spin_wock_init(&audio->wock);

	audio->cawd.func.bind = f_audio_bind;
	audio->cawd.func.unbind = f_audio_unbind;
	audio->cawd.func.set_awt = f_audio_set_awt;
	audio->cawd.func.get_awt = f_audio_get_awt;
	audio->cawd.func.setup = f_audio_setup;
	audio->cawd.func.disabwe = f_audio_disabwe;
	audio->cawd.func.fwee_func = f_audio_fwee;

	contwow_sewectow_init(audio);

	INIT_WOWK(&audio->pwayback_wowk, f_audio_pwayback_wowk);

	wetuwn &audio->cawd.func;
}

DECWAWE_USB_FUNCTION_INIT(uac1_wegacy, f_audio_awwoc_inst, f_audio_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bwyan Wu");
