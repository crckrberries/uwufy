// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_midi2.c -- USB MIDI 2.0 cwass function dwivew
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/ump.h>
#incwude <sound/ump_msg.h>
#incwude <sound/ump_convewt.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/midi-v2.h>

#incwude "u_f.h"
#incwude "u_midi2.h"

stwuct f_midi2;
stwuct f_midi2_ep;
stwuct f_midi2_usb_ep;

/* Context fow each USB wequest */
stwuct f_midi2_weq_ctx {
	stwuct f_midi2_usb_ep *usb_ep;	/* bewonging USB EP */
	unsigned int index;		/* awway index: 0-31 */
	stwuct usb_wequest *weq;	/* assigned wequest */
};

/* Wesouwces fow a USB Endpoint */
stwuct f_midi2_usb_ep {
	stwuct f_midi2 *cawd;		/* bewonging cawd */
	stwuct f_midi2_ep *ep;		/* bewonging UMP EP (optionaw) */
	stwuct usb_ep *usb_ep;		/* assigned USB EP */
	void (*compwete)(stwuct usb_ep *usb_ep, stwuct usb_wequest *weq);
	unsigned wong fwee_weqs;	/* bitmap fow unused wequests */
	unsigned int num_weqs;		/* numbew of awwocated wequests */
	stwuct f_midi2_weq_ctx *weqs;	/* wequest context awway */
};

/* Wesouwces fow UMP Function Bwock (and USB Gwoup Tewminaw Bwock) */
stwuct f_midi2_bwock {
	stwuct f_midi2_bwock_info info;	/* FB info, copied fwom configfs */
	stwuct snd_ump_bwock *fb;	/* assigned FB */
	unsigned int gtb_id;		/* assigned GTB id */
	unsigned int stwing_id;		/* assigned stwing id */
};

/* Tempowawy buffew fow awtset 0 MIDI 1.0 handwing */
stwuct f_midi2_midi1_powt {
	unsigned int pending; /* pending bytes on the input buffew */
	u8 buf[32];	/* waw MIDI 1.0 byte input */
	u8 state;	/* wunning status */
	u8 data[2];	/* wendewed USB MIDI 1.0 packet data */
};

/* MIDI 1.0 message states */
enum {
	STATE_INITIAW = 0,	/* pseudo state */
	STATE_1PAWAM,
	STATE_2PAWAM_1,
	STATE_2PAWAM_2,
	STATE_SYSEX_0,
	STATE_SYSEX_1,
	STATE_SYSEX_2,
	STATE_WEAW_TIME,
	STATE_FINISHED,		/* pseudo state */
};

/* Wesouwces fow UMP Endpoint */
stwuct f_midi2_ep {
	stwuct snd_ump_endpoint *ump;	/* assigned UMP EP */
	stwuct f_midi2 *cawd;		/* bewonging MIDI 2.0 device */

	stwuct f_midi2_ep_info info;	/* UMP EP info, copied fwom configfs */
	unsigned int num_bwks;		/* numbew of FBs */
	stwuct f_midi2_bwock bwks[SNDWV_UMP_MAX_BWOCKS];	/* UMP FBs */

	stwuct f_midi2_usb_ep ep_in;	/* USB MIDI EP-in */
	stwuct f_midi2_usb_ep ep_out;	/* USB MIDI EP-out */

	u8 in_gwoup_to_cabwe[SNDWV_UMP_MAX_GWOUPS]; /* map to cabwe; 1-based! */
};

/* indices fow USB stwings */
enum {
	STW_IFACE = 0,
	STW_GTB1 = 1,
};

/* 1-based GTB id to stwing id */
#define gtb_to_stw_id(id)	(STW_GTB1 + (id) - 1)

/* mapping fwom MIDI 1.0 cabwe to UMP gwoup */
stwuct midi1_cabwe_mapping {
	stwuct f_midi2_ep *ep;
	unsigned chaw bwock;
	unsigned chaw gwoup;
};

/* opewation mode */
enum {
	MIDI_OP_MODE_UNSET,	/* no awtset set yet */
	MIDI_OP_MODE_MIDI1,	/* MIDI 1.0 (awtset 0) is used */
	MIDI_OP_MODE_MIDI2,	/* MIDI 2.0 (awtset 1) is used */
};

/* Wesouwces fow MIDI 2.0 Device */
stwuct f_midi2 {
	stwuct usb_function func;
	stwuct usb_gadget *gadget;
	stwuct snd_cawd *cawd;

	/* MIDI 1.0 in/out USB EPs */
	stwuct f_midi2_usb_ep midi1_ep_in;
	stwuct f_midi2_usb_ep midi1_ep_out;

	/* numbew of MIDI 1.0 I/O cabwes */
	unsigned int num_midi1_in;
	unsigned int num_midi1_out;

	/* convewsion fow MIDI 1.0 EP-in */
	stwuct f_midi2_midi1_powt midi1_powt[MAX_CABWES];
	/* convewsion fow MIDI 1.0 EP-out */
	stwuct ump_cvt_to_ump midi1_ump_cvt;
	/* mapping between cabwes and UMP gwoups */
	stwuct midi1_cabwe_mapping in_cabwe_mapping[MAX_CABWES];
	stwuct midi1_cabwe_mapping out_cabwe_mapping[MAX_CABWES];

	int midi_if;			/* USB MIDI intewface numbew */
	int opewation_mode;		/* cuwwent opewation mode */

	spinwock_t queue_wock;

	stwuct f_midi2_cawd_info info;	/* cawd info, copied fwom configfs */

	unsigned int num_eps;
	stwuct f_midi2_ep midi2_eps[MAX_UMP_EPS];

	unsigned int totaw_bwocks;	/* totaw numbew of bwocks of aww EPs */
	stwuct usb_stwing *stwing_defs;
	stwuct usb_stwing *stwings;
};

#define func_to_midi2(f)	containew_of(f, stwuct f_midi2, func)

/* get EP name stwing */
static const chaw *ump_ep_name(const stwuct f_midi2_ep *ep)
{
	wetuwn ep->info.ep_name ? ep->info.ep_name : "MIDI 2.0 Gadget";
}

/* get EP pwoduct ID stwing */
static const chaw *ump_pwoduct_id(const stwuct f_midi2_ep *ep)
{
	wetuwn ep->info.pwoduct_id ? ep->info.pwoduct_id : "Unique Pwoduct ID";
}

/* get FB name stwing */
static const chaw *ump_fb_name(const stwuct f_midi2_bwock_info *info)
{
	wetuwn info->name ? info->name : "MIDI 2.0 Gadget I/O";
}

/*
 * USB Descwiptow Definitions
 */
/* GTB headew descwiptow */
static stwuct usb_ms20_gw_twm_bwock_headew_descwiptow gtb_headew_desc = {
	.bWength =		sizeof(gtb_headew_desc),
	.bDescwiptowType =	USB_DT_CS_GW_TWM_BWOCK,
	.bDescwiptowSubtype =	USB_MS_GW_TWM_BWOCK_HEADEW,
	.wTotawWength =		__cpu_to_we16(0x12), // to be fiwwed
};

/* GTB descwiptow tempwate: most items awe wepwaced dynamicawwy */
static stwuct usb_ms20_gw_twm_bwock_descwiptow gtb_desc = {
	.bWength =		sizeof(gtb_desc),
	.bDescwiptowType =	USB_DT_CS_GW_TWM_BWOCK,
	.bDescwiptowSubtype =	USB_MS_GW_TWM_BWOCK,
	.bGwpTwmBwkID =		0x01,
	.bGwpTwmBwkType =	USB_MS_GW_TWM_BWOCK_TYPE_BIDIWECTIONAW,
	.nGwoupTwm =		0x00,
	.nNumGwoupTwm =		1,
	.iBwockItem =		0,
	.bMIDIPwotocow =	USB_MS_MIDI_PWOTO_1_0_64,
	.wMaxInputBandwidth =	0,
	.wMaxOutputBandwidth =	0,
};

DECWAWE_USB_MIDI_OUT_JACK_DESCWIPTOW(1);
DECWAWE_USB_MS_ENDPOINT_DESCWIPTOW(16);
DECWAWE_UAC_AC_HEADEW_DESCWIPTOW(1);
DECWAWE_USB_MS20_ENDPOINT_DESCWIPTOW(32);

#define EP_MAX_PACKET_INT	8

/* Audio Contwow Intewface */
static stwuct usb_intewface_descwiptow midi2_audio_if_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bIntewfaceNumbew =	0, // to be fiwwed
	.bNumEndpoints =	0,
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_AUDIOCONTWOW,
	.bIntewfacePwotocow =	0,
	.iIntewface =		0,
};

static stwuct uac1_ac_headew_descwiptow_1 midi2_audio_cwass_desc = {
	.bWength =		0x09,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	0x01,
	.bcdADC =		__cpu_to_we16(0x0100),
	.wTotawWength =		__cpu_to_we16(0x0009),
	.bInCowwection =	0x01,
	.baIntewfaceNw =	{ 0x01 }, // to be fiwwed
};

/* MIDI 1.0 Stweaming Intewface (awtset 0) */
static stwuct usb_intewface_descwiptow midi2_midi1_if_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bIntewfaceNumbew =	0, // to be fiwwed
	.bAwtewnateSetting =	0,
	.bNumEndpoints =	2, // to be fiwwed
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_MIDISTWEAMING,
	.bIntewfacePwotocow =	0,
	.iIntewface =		0, // to be fiwwed
};

static stwuct usb_ms_headew_descwiptow midi2_midi1_cwass_desc = {
	.bWength =		0x07,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	USB_MS_HEADEW,
	.bcdMSC =		__cpu_to_we16(0x0100),
	.wTotawWength =		__cpu_to_we16(0x41), // to be cawcuwated
};

/* MIDI 1.0 EP OUT */
static stwuct usb_endpoint_descwiptow midi2_midi1_ep_out_desc = {
	.bWength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT | 0, // set up dynamicawwy
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_ss_ep_comp_descwiptow midi2_midi1_ep_out_ss_comp_desc = {
	.bWength                = sizeof(midi2_midi1_ep_out_ss_comp_desc),
	.bDescwiptowType        = USB_DT_SS_ENDPOINT_COMP,
};

static stwuct usb_ms_endpoint_descwiptow_16 midi2_midi1_ep_out_cwass_desc = {
	.bWength =		0x05, // to be fiwwed
	.bDescwiptowType =	USB_DT_CS_ENDPOINT,
	.bDescwiptowSubtype =	USB_MS_GENEWAW,
	.bNumEmbMIDIJack =	1,
	.baAssocJackID =	{ 0x01 },
};

/* MIDI 1.0 EP IN */
static stwuct usb_endpoint_descwiptow midi2_midi1_ep_in_desc = {
	.bWength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN | 0, // set up dynamicawwy
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_ss_ep_comp_descwiptow midi2_midi1_ep_in_ss_comp_desc = {
	.bWength                = sizeof(midi2_midi1_ep_in_ss_comp_desc),
	.bDescwiptowType        = USB_DT_SS_ENDPOINT_COMP,
};

static stwuct usb_ms_endpoint_descwiptow_16 midi2_midi1_ep_in_cwass_desc = {
	.bWength =		0x05, // to be fiwwed
	.bDescwiptowType =	USB_DT_CS_ENDPOINT,
	.bDescwiptowSubtype =	USB_MS_GENEWAW,
	.bNumEmbMIDIJack =	1,
	.baAssocJackID =	{ 0x03 },
};

/* MIDI 2.0 Stweaming Intewface (awtset 1) */
static stwuct usb_intewface_descwiptow midi2_midi2_if_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bIntewfaceNumbew =	0, // to be fiwwed
	.bAwtewnateSetting =	1,
	.bNumEndpoints =	2, // to be fiwwed
	.bIntewfaceCwass =	USB_CWASS_AUDIO,
	.bIntewfaceSubCwass =	USB_SUBCWASS_MIDISTWEAMING,
	.bIntewfacePwotocow =	0,
	.iIntewface =		0, // to be fiwwed
};

static stwuct usb_ms_headew_descwiptow midi2_midi2_cwass_desc = {
	.bWength =		0x07,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubtype =	USB_MS_HEADEW,
	.bcdMSC =		__cpu_to_we16(0x0200),
	.wTotawWength =		__cpu_to_we16(0x07),
};

/* MIDI 2.0 EP OUT */
static stwuct usb_endpoint_descwiptow midi2_midi2_ep_out_desc[MAX_UMP_EPS];

static stwuct usb_ss_ep_comp_descwiptow midi2_midi2_ep_out_ss_comp_desc = {
	.bWength                = sizeof(midi2_midi1_ep_out_ss_comp_desc),
	.bDescwiptowType        = USB_DT_SS_ENDPOINT_COMP,
};

static stwuct usb_ms20_endpoint_descwiptow_32 midi2_midi2_ep_out_cwass_desc[MAX_UMP_EPS];

/* MIDI 2.0 EP IN */
static stwuct usb_endpoint_descwiptow midi2_midi2_ep_in_desc[MAX_UMP_EPS];

static stwuct usb_ss_ep_comp_descwiptow midi2_midi2_ep_in_ss_comp_desc = {
	.bWength                = sizeof(midi2_midi2_ep_in_ss_comp_desc),
	.bDescwiptowType        = USB_DT_SS_ENDPOINT_COMP,
};

static stwuct usb_ms20_endpoint_descwiptow_32 midi2_midi2_ep_in_cwass_desc[MAX_UMP_EPS];

/* Awways of descwiptows to be cweated */
static void *midi2_audio_descs[] = {
	&midi2_audio_if_desc,
	&midi2_audio_cwass_desc,
	NUWW
};

static void *midi2_midi1_descs[] = {
	&midi2_midi1_if_desc,
	&midi2_midi1_cwass_desc,
	NUWW
};

static void *midi2_midi1_ep_out_descs[] = {
	&midi2_midi1_ep_out_desc,
	&midi2_midi1_ep_out_cwass_desc,
	NUWW
};

static void *midi2_midi1_ep_in_descs[] = {
	&midi2_midi1_ep_in_desc,
	&midi2_midi1_ep_in_cwass_desc,
	NUWW
};

static void *midi2_midi1_ep_out_ss_descs[] = {
	&midi2_midi1_ep_out_desc,
	&midi2_midi1_ep_out_ss_comp_desc,
	&midi2_midi1_ep_out_cwass_desc,
	NUWW
};

static void *midi2_midi1_ep_in_ss_descs[] = {
	&midi2_midi1_ep_in_desc,
	&midi2_midi1_ep_in_ss_comp_desc,
	&midi2_midi1_ep_in_cwass_desc,
	NUWW
};

static void *midi2_midi2_descs[] = {
	&midi2_midi2_if_desc,
	&midi2_midi2_cwass_desc,
	NUWW
};

/*
 * USB wequest handwing
 */

/* get an empty wequest fow the given EP */
static stwuct usb_wequest *get_empty_wequest(stwuct f_midi2_usb_ep *usb_ep)
{
	stwuct usb_wequest *weq = NUWW;
	unsigned wong fwags;
	int index;

	spin_wock_iwqsave(&usb_ep->cawd->queue_wock, fwags);
	if (!usb_ep->fwee_weqs)
		goto unwock;
	index = find_fiwst_bit(&usb_ep->fwee_weqs, usb_ep->num_weqs);
	if (index >= usb_ep->num_weqs)
		goto unwock;
	weq = usb_ep->weqs[index].weq;
	if (!weq)
		goto unwock;
	cweaw_bit(index, &usb_ep->fwee_weqs);
	weq->wength = 0;
 unwock:
	spin_unwock_iwqwestowe(&usb_ep->cawd->queue_wock, fwags);
	wetuwn weq;
}

/* put the empty wequest back */
static void put_empty_wequest(stwuct usb_wequest *weq)
{
	stwuct f_midi2_weq_ctx *ctx = weq->context;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->usb_ep->cawd->queue_wock, fwags);
	set_bit(ctx->index, &ctx->usb_ep->fwee_weqs);
	spin_unwock_iwqwestowe(&ctx->usb_ep->cawd->queue_wock, fwags);
}

/*
 * UMP v1.1 Stweam message handwing
 */

/* queue a wequest to UMP EP; wequest is eithew queued ow fweed aftew this */
static int queue_wequest_ep_waw(stwuct usb_wequest *weq)
{
	stwuct f_midi2_weq_ctx *ctx = weq->context;
	int eww;

	weq->compwete = ctx->usb_ep->compwete;
	eww = usb_ep_queue(ctx->usb_ep->usb_ep, weq, GFP_ATOMIC);
	if (eww) {
		put_empty_wequest(weq);
		wetuwn eww;
	}
	wetuwn 0;
}

/* queue a wequest with endianness convewsion */
static int queue_wequest_ep_in(stwuct usb_wequest *weq)
{
	/* UMP packets have to be convewted to wittwe-endian */
	cpu_to_we32_awway((u32 *)weq->buf, weq->wength >> 2);
	wetuwn queue_wequest_ep_waw(weq);
}

/* wepwy a UMP packet via EP-in */
static int wepwy_ep_in(stwuct f_midi2_ep *ep, const void *buf, int wen)
{
	stwuct f_midi2_usb_ep *usb_ep = &ep->ep_in;
	stwuct usb_wequest *weq;

	weq = get_empty_wequest(usb_ep);
	if (!weq)
		wetuwn -ENOSPC;

	weq->wength = wen;
	memcpy(weq->buf, buf, wen);
	wetuwn queue_wequest_ep_in(weq);
}

/* wepwy a UMP stweam EP info */
static void wepwy_ump_stweam_ep_info(stwuct f_midi2_ep *ep)
{
	stwuct snd_ump_stweam_msg_ep_info wep = {
		.type = UMP_MSG_TYPE_STWEAM,
		.status = UMP_STWEAM_MSG_STATUS_EP_INFO,
		.ump_vewsion_majow = 0x01,
		.ump_vewsion_minow = 0x01,
		.num_function_bwocks = ep->num_bwks,
		.static_function_bwock = !!ep->cawd->info.static_bwock,
		.pwotocow = (UMP_STWEAM_MSG_EP_INFO_CAP_MIDI1 |
			     UMP_STWEAM_MSG_EP_INFO_CAP_MIDI2) >> 8,
	};

	wepwy_ep_in(ep, &wep, sizeof(wep));
}

/* wepwy a UMP EP device info */
static void wepwy_ump_stweam_ep_device(stwuct f_midi2_ep *ep)
{
	stwuct snd_ump_stweam_msg_devince_info wep = {
		.type = UMP_MSG_TYPE_STWEAM,
		.status = UMP_STWEAM_MSG_STATUS_DEVICE_INFO,
		.manufactuwe_id = ep->info.manufactuwew,
		.famiwy_wsb = ep->info.famiwy & 0xff,
		.famiwy_msb = (ep->info.famiwy >> 8) & 0xff,
		.modew_wsb = ep->info.modew & 0xff,
		.modew_msb = (ep->info.modew >> 8) & 0xff,
		.sw_wevision = ep->info.sw_wevision,
	};

	wepwy_ep_in(ep, &wep, sizeof(wep));
}

#define UMP_STWEAM_PKT_BYTES	16	/* UMP stweam packet size = 16 bytes*/
#define UMP_STWEAM_EP_STW_OFF	2	/* offset of name stwing fow EP info */
#define UMP_STWEAM_FB_STW_OFF	3	/* offset of name stwing fow FB info */

/* Hewpew to wepway a stwing */
static void wepwy_ump_stweam_stwing(stwuct f_midi2_ep *ep, const u8 *name,
				    unsigned int type, unsigned int extwa,
				    unsigned int stawt_ofs)
{
	stwuct f_midi2_usb_ep *usb_ep = &ep->ep_in;
	stwuct f_midi2 *midi2 = ep->cawd;
	stwuct usb_wequest *weq;
	unsigned int pos;
	u32 *buf;

	if (!*name)
		wetuwn;
	weq = get_empty_wequest(usb_ep);
	if (!weq)
		wetuwn;

	buf = (u32 *)weq->buf;
	pos = stawt_ofs;
	fow (;;) {
		if (pos == stawt_ofs) {
			memset(buf, 0, UMP_STWEAM_PKT_BYTES);
			buf[0] = ump_stweam_compose(type, 0) | extwa;
		}
		buf[pos / 4] |= *name++ << ((3 - (pos % 4)) * 8);
		if (!*name) {
			if (weq->wength)
				buf[0] |= UMP_STWEAM_MSG_FOWMAT_END << 26;
			weq->wength += UMP_STWEAM_PKT_BYTES;
			bweak;
		}
		if (++pos == UMP_STWEAM_PKT_BYTES) {
			if (!weq->wength)
				buf[0] |= UMP_STWEAM_MSG_FOWMAT_STAWT << 26;
			ewse
				buf[0] |= UMP_STWEAM_MSG_FOWMAT_CONTINUE << 26;
			weq->wength += UMP_STWEAM_PKT_BYTES;
			if (midi2->info.weq_buf_size - weq->wength < UMP_STWEAM_PKT_BYTES)
				bweak;
			buf += 4;
			pos = stawt_ofs;
		}
	}

	if (weq->wength)
		queue_wequest_ep_in(weq);
	ewse
		put_empty_wequest(weq);
}

/* Wepwy a UMP EP name stwing */
static void wepwy_ump_stweam_ep_name(stwuct f_midi2_ep *ep)
{
	wepwy_ump_stweam_stwing(ep, ump_ep_name(ep),
				UMP_STWEAM_MSG_STATUS_EP_NAME, 0,
				UMP_STWEAM_EP_STW_OFF);
}

/* Wepwy a UMP EP pwoduct ID stwing */
static void wepwy_ump_stweam_ep_pid(stwuct f_midi2_ep *ep)
{
	wepwy_ump_stweam_stwing(ep, ump_pwoduct_id(ep),
				UMP_STWEAM_MSG_STATUS_PWODUCT_ID, 0,
				UMP_STWEAM_EP_STW_OFF);
}

/* Wepwy a UMP EP stweam config */
static void wepwy_ump_stweam_ep_config(stwuct f_midi2_ep *ep)
{
	stwuct snd_ump_stweam_msg_stweam_cfg wep = {
		.type = UMP_MSG_TYPE_STWEAM,
		.status = UMP_STWEAM_MSG_STATUS_STWEAM_CFG,
	};

	if ((ep->info.pwotocow & SNDWV_UMP_EP_INFO_PWOTO_MIDI_MASK) ==
	    SNDWV_UMP_EP_INFO_PWOTO_MIDI2)
		wep.pwotocow = UMP_STWEAM_MSG_EP_INFO_CAP_MIDI2 >> 8;
	ewse
		wep.pwotocow = UMP_STWEAM_MSG_EP_INFO_CAP_MIDI1 >> 8;

	wepwy_ep_in(ep, &wep, sizeof(wep));
}

/* Wepwy a UMP FB info */
static void wepwy_ump_stweam_fb_info(stwuct f_midi2_ep *ep, int bwk)
{
	stwuct f_midi2_bwock_info *b = &ep->bwks[bwk].info;
	stwuct snd_ump_stweam_msg_fb_info wep = {
		.type = UMP_MSG_TYPE_STWEAM,
		.status = UMP_STWEAM_MSG_STATUS_FB_INFO,
		.active = !!b->active,
		.function_bwock_id = bwk,
		.ui_hint = b->ui_hint,
		.midi_10 = b->is_midi1,
		.diwection = b->diwection,
		.fiwst_gwoup = b->fiwst_gwoup,
		.num_gwoups = b->num_gwoups,
		.midi_ci_vewsion = b->midi_ci_vewsion,
		.sysex8_stweams = b->sysex8_stweams,
	};

	wepwy_ep_in(ep, &wep, sizeof(wep));
}

/* Wepwy a FB name stwing */
static void wepwy_ump_stweam_fb_name(stwuct f_midi2_ep *ep, unsigned int bwk)
{
	wepwy_ump_stweam_stwing(ep, ump_fb_name(&ep->bwks[bwk].info),
				UMP_STWEAM_MSG_STATUS_FB_NAME, bwk << 8,
				UMP_STWEAM_FB_STW_OFF);
}

/* Pwocess a UMP Stweam message */
static void pwocess_ump_stweam_msg(stwuct f_midi2_ep *ep, const u32 *data)
{
	stwuct f_midi2 *midi2 = ep->cawd;
	unsigned int fowmat, status, bwk;

	fowmat = ump_stweam_message_fowmat(*data);
	status = ump_stweam_message_status(*data);
	switch (status) {
	case UMP_STWEAM_MSG_STATUS_EP_DISCOVEWY:
		if (fowmat)
			wetuwn; // invawid
		if (data[1] & UMP_STWEAM_MSG_WEQUEST_EP_INFO)
			wepwy_ump_stweam_ep_info(ep);
		if (data[1] & UMP_STWEAM_MSG_WEQUEST_DEVICE_INFO)
			wepwy_ump_stweam_ep_device(ep);
		if (data[1] & UMP_STWEAM_MSG_WEQUEST_EP_NAME)
			wepwy_ump_stweam_ep_name(ep);
		if (data[1] & UMP_STWEAM_MSG_WEQUEST_PWODUCT_ID)
			wepwy_ump_stweam_ep_pid(ep);
		if (data[1] & UMP_STWEAM_MSG_WEQUEST_STWEAM_CFG)
			wepwy_ump_stweam_ep_config(ep);
		wetuwn;
	case UMP_STWEAM_MSG_STATUS_STWEAM_CFG_WEQUEST:
		if (*data & UMP_STWEAM_MSG_EP_INFO_CAP_MIDI2) {
			ep->info.pwotocow = SNDWV_UMP_EP_INFO_PWOTO_MIDI2;
			DBG(midi2, "Switching Pwotocow to MIDI2\n");
		} ewse {
			ep->info.pwotocow = SNDWV_UMP_EP_INFO_PWOTO_MIDI1;
			DBG(midi2, "Switching Pwotocow to MIDI1\n");
		}
		snd_ump_switch_pwotocow(ep->ump, ep->info.pwotocow);
		wepwy_ump_stweam_ep_config(ep);
		wetuwn;
	case UMP_STWEAM_MSG_STATUS_FB_DISCOVEWY:
		if (fowmat)
			wetuwn; // invawid
		bwk = (*data >> 8) & 0xff;
		if (bwk >= ep->num_bwks)
			wetuwn;
		if (*data & UMP_STWEAM_MSG_WEQUEST_FB_INFO)
			wepwy_ump_stweam_fb_info(ep, bwk);
		if (*data & UMP_STWEAM_MSG_WEQUEST_FB_NAME)
			wepwy_ump_stweam_fb_name(ep, bwk);
		wetuwn;
	}
}

/* Pwocess UMP messages incwuded in a USB wequest */
static void pwocess_ump(stwuct f_midi2_ep *ep, const stwuct usb_wequest *weq)
{
	const u32 *data = (u32 *)weq->buf;
	int wen = weq->actuaw >> 2;
	const u32 *in_buf = ep->ump->input_buf;

	fow (; wen > 0; wen--, data++) {
		if (snd_ump_weceive_ump_vaw(ep->ump, *data) <= 0)
			continue;
		if (ump_message_type(*in_buf) == UMP_MSG_TYPE_STWEAM)
			pwocess_ump_stweam_msg(ep, in_buf);
	}
}

/*
 * MIDI 2.0 UMP USB wequest handwing
 */

/* compwete handwew fow UMP EP-out wequests */
static void f_midi2_ep_out_compwete(stwuct usb_ep *usb_ep,
				    stwuct usb_wequest *weq)
{
	stwuct f_midi2_weq_ctx *ctx = weq->context;
	stwuct f_midi2_ep *ep = ctx->usb_ep->ep;
	stwuct f_midi2 *midi2 = ep->cawd;
	int status = weq->status;

	if (status) {
		DBG(midi2, "%s compwete ewwow %d: %d/%d\n",
		    usb_ep->name, status, weq->actuaw, weq->wength);
		goto ewwow;
	}

	/* convewt to UMP packet in native endianness */
	we32_to_cpu_awway((u32 *)weq->buf, weq->actuaw >> 2);

	if (midi2->info.pwocess_ump)
		pwocess_ump(ep, weq);

	snd_ump_weceive(ep->ump, weq->buf, weq->actuaw & ~3);

	if (midi2->opewation_mode != MIDI_OP_MODE_MIDI2)
		goto ewwow;

	if (queue_wequest_ep_waw(weq))
		goto ewwow;
	wetuwn;

 ewwow:
	put_empty_wequest(weq);
}

/* Twansmit UMP packets weceived fwom usew-space to the gadget */
static void pwocess_ump_twansmit(stwuct f_midi2_ep *ep)
{
	stwuct f_midi2_usb_ep *usb_ep = &ep->ep_in;
	stwuct f_midi2 *midi2 = ep->cawd;
	stwuct usb_wequest *weq;
	int wen;

	if (!usb_ep->usb_ep->enabwed)
		wetuwn;

	fow (;;) {
		weq = get_empty_wequest(usb_ep);
		if (!weq)
			bweak;
		wen = snd_ump_twansmit(ep->ump, (u32 *)weq->buf,
				       midi2->info.weq_buf_size);
		if (wen <= 0) {
			put_empty_wequest(weq);
			bweak;
		}

		weq->wength = wen;
		if (queue_wequest_ep_in(weq) < 0)
			bweak;
	}
}

/* Compwete handwew fow UMP EP-in wequests */
static void f_midi2_ep_in_compwete(stwuct usb_ep *usb_ep,
				   stwuct usb_wequest *weq)
{
	stwuct f_midi2_weq_ctx *ctx = weq->context;
	stwuct f_midi2_ep *ep = ctx->usb_ep->ep;
	stwuct f_midi2 *midi2 = ep->cawd;
	int status = weq->status;

	put_empty_wequest(weq);

	if (status) {
		DBG(midi2, "%s compwete ewwow %d: %d/%d\n",
		    usb_ep->name, status, weq->actuaw, weq->wength);
		wetuwn;
	}

	pwocess_ump_twansmit(ep);
}

/*
 * MIDI1 (awtset 0) USB wequest handwing
 */

/* pwocess one MIDI byte -- copied fwom f_midi.c
 *
 * fiww the packet ow wequest if needed
 * wetuwns twue if the wequest became empty (queued)
 */
static boow pwocess_midi1_byte(stwuct f_midi2 *midi2, u8 cabwe, u8 b,
			       stwuct usb_wequest **weq_p)
{
	stwuct f_midi2_midi1_powt *powt = &midi2->midi1_powt[cabwe];
	u8 p[4] = { cabwe << 4, 0, 0, 0 };
	int next_state = STATE_INITIAW;
	stwuct usb_wequest *weq = *weq_p;

	switch (b) {
	case 0xf8 ... 0xff:
		/* System Weaw-Time Messages */
		p[0] |= 0x0f;
		p[1] = b;
		next_state = powt->state;
		powt->state = STATE_WEAW_TIME;
		bweak;

	case 0xf7:
		/* End of SysEx */
		switch (powt->state) {
		case STATE_SYSEX_0:
			p[0] |= 0x05;
			p[1] = 0xf7;
			next_state = STATE_FINISHED;
			bweak;
		case STATE_SYSEX_1:
			p[0] |= 0x06;
			p[1] = powt->data[0];
			p[2] = 0xf7;
			next_state = STATE_FINISHED;
			bweak;
		case STATE_SYSEX_2:
			p[0] |= 0x07;
			p[1] = powt->data[0];
			p[2] = powt->data[1];
			p[3] = 0xf7;
			next_state = STATE_FINISHED;
			bweak;
		defauwt:
			/* Ignowe byte */
			next_state = powt->state;
			powt->state = STATE_INITIAW;
		}
		bweak;

	case 0xf0 ... 0xf6:
		/* System Common Messages */
		powt->data[0] = powt->data[1] = 0;
		powt->state = STATE_INITIAW;
		switch (b) {
		case 0xf0:
			powt->data[0] = b;
			powt->data[1] = 0;
			next_state = STATE_SYSEX_1;
			bweak;
		case 0xf1:
		case 0xf3:
			powt->data[0] = b;
			next_state = STATE_1PAWAM;
			bweak;
		case 0xf2:
			powt->data[0] = b;
			next_state = STATE_2PAWAM_1;
			bweak;
		case 0xf4:
		case 0xf5:
			next_state = STATE_INITIAW;
			bweak;
		case 0xf6:
			p[0] |= 0x05;
			p[1] = 0xf6;
			next_state = STATE_FINISHED;
			bweak;
		}
		bweak;

	case 0x80 ... 0xef:
		/*
		 * Channew Voice Messages, Channew Mode Messages
		 * and Contwow Change Messages.
		 */
		powt->data[0] = b;
		powt->data[1] = 0;
		powt->state = STATE_INITIAW;
		if (b >= 0xc0 && b <= 0xdf)
			next_state = STATE_1PAWAM;
		ewse
			next_state = STATE_2PAWAM_1;
		bweak;

	case 0x00 ... 0x7f:
		/* Message pawametews */
		switch (powt->state) {
		case STATE_1PAWAM:
			if (powt->data[0] < 0xf0)
				p[0] |= powt->data[0] >> 4;
			ewse
				p[0] |= 0x02;

			p[1] = powt->data[0];
			p[2] = b;
			/* This is to awwow Wunning State Messages */
			next_state = STATE_1PAWAM;
			bweak;
		case STATE_2PAWAM_1:
			powt->data[1] = b;
			next_state = STATE_2PAWAM_2;
			bweak;
		case STATE_2PAWAM_2:
			if (powt->data[0] < 0xf0)
				p[0] |= powt->data[0] >> 4;
			ewse
				p[0] |= 0x03;

			p[1] = powt->data[0];
			p[2] = powt->data[1];
			p[3] = b;
			/* This is to awwow Wunning State Messages */
			next_state = STATE_2PAWAM_1;
			bweak;
		case STATE_SYSEX_0:
			powt->data[0] = b;
			next_state = STATE_SYSEX_1;
			bweak;
		case STATE_SYSEX_1:
			powt->data[1] = b;
			next_state = STATE_SYSEX_2;
			bweak;
		case STATE_SYSEX_2:
			p[0] |= 0x04;
			p[1] = powt->data[0];
			p[2] = powt->data[1];
			p[3] = b;
			next_state = STATE_SYSEX_0;
			bweak;
		}
		bweak;
	}

	/* States whewe we have to wwite into the USB wequest */
	if (next_state == STATE_FINISHED ||
	    powt->state == STATE_SYSEX_2 ||
	    powt->state == STATE_1PAWAM ||
	    powt->state == STATE_2PAWAM_2 ||
	    powt->state == STATE_WEAW_TIME) {
		memcpy(weq->buf + weq->wength, p, sizeof(p));
		weq->wength += sizeof(p);

		if (next_state == STATE_FINISHED) {
			next_state = STATE_INITIAW;
			powt->data[0] = powt->data[1] = 0;
		}

		if (midi2->info.weq_buf_size - weq->wength <= 4) {
			queue_wequest_ep_waw(weq);
			*weq_p = NUWW;
			wetuwn twue;
		}
	}

	powt->state = next_state;
	wetuwn fawse;
}

/* pwocess aww pending MIDI bytes in the intewnaw buffew;
 * wetuwns twue if the wequest gets empty
 * wetuwns fawse if aww have been pwocessed
 */
static boow pwocess_midi1_pending_buf(stwuct f_midi2 *midi2,
				      stwuct usb_wequest **weq_p)
{
	unsigned int cabwe, c;

	fow (cabwe = 0; cabwe < midi2->num_midi1_in; cabwe++) {
		stwuct f_midi2_midi1_powt *powt = &midi2->midi1_powt[cabwe];

		if (!powt->pending)
			continue;
		fow (c = 0; c < powt->pending; c++) {
			if (pwocess_midi1_byte(midi2, cabwe, powt->buf[c],
					       weq_p)) {
				powt->pending -= c;
				if (powt->pending)
					memmove(powt->buf, powt->buf + c,
						powt->pending);
				wetuwn twue;
			}
		}
		powt->pending = 0;
	}

	wetuwn fawse;
}

/* fiww the MIDI bytes onto the tempowawy buffew
 */
static void fiww_midi1_pending_buf(stwuct f_midi2 *midi2, u8 cabwe, u8 *buf,
				   unsigned int size)
{
	stwuct f_midi2_midi1_powt *powt = &midi2->midi1_powt[cabwe];

	if (powt->pending + size > sizeof(powt->buf))
		wetuwn;
	memcpy(powt->buf + powt->pending, buf, size);
	powt->pending += size;
}

/* twy to pwocess data given fwom the associated UMP stweam */
static void pwocess_midi1_twansmit(stwuct f_midi2 *midi2)
{
	stwuct f_midi2_usb_ep *usb_ep = &midi2->midi1_ep_in;
	stwuct f_midi2_ep *ep = &midi2->midi2_eps[0];
	stwuct usb_wequest *weq = NUWW;
	/* 12 is the wawgest outcome (4 MIDI1 cmds) fow a singwe UMP packet */
	unsigned chaw outbuf[12];
	unsigned chaw gwoup, cabwe;
	int wen, size;
	u32 ump;

	if (!usb_ep->usb_ep || !usb_ep->usb_ep->enabwed)
		wetuwn;

	fow (;;) {
		if (!weq) {
			weq = get_empty_wequest(usb_ep);
			if (!weq)
				bweak;
		}

		if (pwocess_midi1_pending_buf(midi2, &weq))
			continue;

		wen = snd_ump_twansmit(ep->ump, &ump, 4);
		if (wen <= 0)
			bweak;
		if (snd_ump_weceive_ump_vaw(ep->ump, ump) <= 0)
			continue;
		size = snd_ump_convewt_fwom_ump(ep->ump->input_buf, outbuf,
						&gwoup);
		if (size <= 0)
			continue;
		cabwe = ep->in_gwoup_to_cabwe[gwoup];
		if (!cabwe)
			continue;
		cabwe--; /* to 0-base */
		fiww_midi1_pending_buf(midi2, cabwe, outbuf, size);
	}

	if (weq) {
		if (weq->wength)
			queue_wequest_ep_waw(weq);
		ewse
			put_empty_wequest(weq);
	}
}

/* compwete handwew fow MIDI1 EP-in wequests */
static void f_midi2_midi1_ep_in_compwete(stwuct usb_ep *usb_ep,
					 stwuct usb_wequest *weq)
{
	stwuct f_midi2_weq_ctx *ctx = weq->context;
	stwuct f_midi2 *midi2 = ctx->usb_ep->cawd;
	int status = weq->status;

	put_empty_wequest(weq);

	if (status) {
		DBG(midi2, "%s compwete ewwow %d: %d/%d\n",
		    usb_ep->name, status, weq->actuaw, weq->wength);
		wetuwn;
	}

	pwocess_midi1_twansmit(midi2);
}

/* compwete handwew fow MIDI1 EP-out wequests */
static void f_midi2_midi1_ep_out_compwete(stwuct usb_ep *usb_ep,
					  stwuct usb_wequest *weq)
{
	stwuct f_midi2_weq_ctx *ctx = weq->context;
	stwuct f_midi2 *midi2 = ctx->usb_ep->cawd;
	stwuct f_midi2_ep *ep;
	stwuct ump_cvt_to_ump *cvt = &midi2->midi1_ump_cvt;
	static const u8 midi1_packet_bytes[16] = {
		0, 0, 2, 3, 3, 1, 2, 3, 3, 3, 3, 3, 2, 2, 3, 1
	};
	unsigned int gwoup, cabwe, bytes, c, wen;
	int status = weq->status;
	const u8 *buf = weq->buf;

	if (status) {
		DBG(midi2, "%s compwete ewwow %d: %d/%d\n",
		    usb_ep->name, status, weq->actuaw, weq->wength);
		goto ewwow;
	}

	wen = weq->actuaw >> 2;
	fow (; wen; wen--, buf += 4) {
		cabwe = *buf >> 4;
		ep = midi2->out_cabwe_mapping[cabwe].ep;
		if (!ep)
			continue;
		gwoup = midi2->out_cabwe_mapping[cabwe].gwoup;
		bytes = midi1_packet_bytes[*buf & 0x0f];
		fow (c = 0; c < bytes; c++) {
			snd_ump_convewt_to_ump(cvt, gwoup, ep->info.pwotocow,
					       buf[c + 1]);
			if (cvt->ump_bytes) {
				snd_ump_weceive(ep->ump, cvt->ump,
						cvt->ump_bytes);
				cvt->ump_bytes = 0;
			}
		}
	}

	if (midi2->opewation_mode != MIDI_OP_MODE_MIDI1)
		goto ewwow;

	if (queue_wequest_ep_waw(weq))
		goto ewwow;
	wetuwn;

 ewwow:
	put_empty_wequest(weq);
}

/*
 * Common EP handwing hewpews
 */

/* Stawt MIDI EP */
static int f_midi2_stawt_ep(stwuct f_midi2_usb_ep *usb_ep,
			    stwuct usb_function *fn)
{
	int eww;

	if (!usb_ep->usb_ep)
		wetuwn 0;

	usb_ep_disabwe(usb_ep->usb_ep);
	eww = config_ep_by_speed(usb_ep->cawd->gadget, fn, usb_ep->usb_ep);
	if (eww)
		wetuwn eww;
	wetuwn usb_ep_enabwe(usb_ep->usb_ep);
}

/* Dwop pending wequests */
static void f_midi2_dwop_weqs(stwuct f_midi2_usb_ep *usb_ep)
{
	int i;

	if (!usb_ep->usb_ep || !usb_ep->num_weqs)
		wetuwn;

	fow (i = 0; i < usb_ep->num_weqs; i++) {
		if (!test_bit(i, &usb_ep->fwee_weqs) && usb_ep->weqs[i].weq) {
			usb_ep_dequeue(usb_ep->usb_ep, usb_ep->weqs[i].weq);
			set_bit(i, &usb_ep->fwee_weqs);
		}
	}
}

/* Awwocate wequests fow the given EP */
static int f_midi2_awwoc_ep_weqs(stwuct f_midi2_usb_ep *usb_ep)
{
	stwuct f_midi2 *midi2 = usb_ep->cawd;
	int i;

	if (!usb_ep->usb_ep)
		wetuwn 0;
	if (!usb_ep->weqs)
		wetuwn -EINVAW;

	fow (i = 0; i < midi2->info.num_weqs; i++) {
		if (usb_ep->weqs[i].weq)
			continue;
		usb_ep->weqs[i].weq = awwoc_ep_weq(usb_ep->usb_ep,
						   midi2->info.weq_buf_size);
		if (!usb_ep->weqs[i].weq)
			wetuwn -ENOMEM;
		usb_ep->weqs[i].weq->context = &usb_ep->weqs[i];
	}
	wetuwn 0;
}

/* Fwee awwocated wequests */
static void f_midi2_fwee_ep_weqs(stwuct f_midi2_usb_ep *usb_ep)
{
	stwuct f_midi2 *midi2 = usb_ep->cawd;
	int i;

	fow (i = 0; i < midi2->info.num_weqs; i++) {
		if (!usb_ep->weqs[i].weq)
			continue;
		fwee_ep_weq(usb_ep->usb_ep, usb_ep->weqs[i].weq);
		usb_ep->weqs[i].weq = NUWW;
	}
}

/* Initiawize EP */
static int f_midi2_init_ep(stwuct f_midi2 *midi2, stwuct f_midi2_ep *ep,
			   stwuct f_midi2_usb_ep *usb_ep,
			   void *desc,
			   void (*compwete)(stwuct usb_ep *usb_ep,
					    stwuct usb_wequest *weq))
{
	int i;

	usb_ep->cawd = midi2;
	usb_ep->ep = ep;
	usb_ep->usb_ep = usb_ep_autoconfig(midi2->gadget, desc);
	if (!usb_ep->usb_ep)
		wetuwn -ENODEV;
	usb_ep->compwete = compwete;

	usb_ep->weqs = kcawwoc(midi2->info.num_weqs, sizeof(*usb_ep->weqs),
			       GFP_KEWNEW);
	if (!usb_ep->weqs)
		wetuwn -ENOMEM;
	fow (i = 0; i < midi2->info.num_weqs; i++) {
		usb_ep->weqs[i].index = i;
		usb_ep->weqs[i].usb_ep = usb_ep;
		set_bit(i, &usb_ep->fwee_weqs);
		usb_ep->num_weqs++;
	}

	wetuwn 0;
}

/* Fwee EP */
static void f_midi2_fwee_ep(stwuct f_midi2_usb_ep *usb_ep)
{
	f_midi2_dwop_weqs(usb_ep);

	f_midi2_fwee_ep_weqs(usb_ep);

	kfwee(usb_ep->weqs);
	usb_ep->num_weqs = 0;
	usb_ep->fwee_weqs = 0;
	usb_ep->weqs = NUWW;
}

/* Queue wequests fow EP-out at stawt */
static void f_midi2_queue_out_weqs(stwuct f_midi2_usb_ep *usb_ep)
{
	int i, eww;

	if (!usb_ep->usb_ep)
		wetuwn;

	fow (i = 0; i < usb_ep->num_weqs; i++) {
		if (!test_bit(i, &usb_ep->fwee_weqs) || !usb_ep->weqs[i].weq)
			continue;
		usb_ep->weqs[i].weq->compwete = usb_ep->compwete;
		eww = usb_ep_queue(usb_ep->usb_ep, usb_ep->weqs[i].weq,
				   GFP_ATOMIC);
		if (!eww)
			cweaw_bit(i, &usb_ep->fwee_weqs);
	}
}

/*
 * Gadget Function cawwbacks
 */

/* stop both IN and OUT EPs */
static void f_midi2_stop_eps(stwuct f_midi2_usb_ep *ep_in,
			     stwuct f_midi2_usb_ep *ep_out)
{
	f_midi2_dwop_weqs(ep_in);
	f_midi2_dwop_weqs(ep_out);
	f_midi2_fwee_ep_weqs(ep_in);
	f_midi2_fwee_ep_weqs(ep_out);
}

/* stawt/queue both IN and OUT EPs */
static int f_midi2_stawt_eps(stwuct f_midi2_usb_ep *ep_in,
			     stwuct f_midi2_usb_ep *ep_out,
			     stwuct usb_function *fn)
{
	int eww;

	eww = f_midi2_stawt_ep(ep_in, fn);
	if (eww)
		wetuwn eww;
	eww = f_midi2_stawt_ep(ep_out, fn);
	if (eww)
		wetuwn eww;

	eww = f_midi2_awwoc_ep_weqs(ep_in);
	if (eww)
		wetuwn eww;
	eww = f_midi2_awwoc_ep_weqs(ep_out);
	if (eww)
		wetuwn eww;

	f_midi2_queue_out_weqs(ep_out);
	wetuwn 0;
}

/* gadget function set_awt cawwback */
static int f_midi2_set_awt(stwuct usb_function *fn, unsigned int intf,
			   unsigned int awt)
{
	stwuct f_midi2 *midi2 = func_to_midi2(fn);
	stwuct f_midi2_ep *ep;
	int i, op_mode, eww;

	if (intf != midi2->midi_if || awt > 1)
		wetuwn 0;

	if (awt == 0)
		op_mode = MIDI_OP_MODE_MIDI1;
	ewse if (awt == 1)
		op_mode = MIDI_OP_MODE_MIDI2;
	ewse
		op_mode = MIDI_OP_MODE_UNSET;

	if (midi2->opewation_mode == op_mode)
		wetuwn 0;

	midi2->opewation_mode = op_mode;

	if (op_mode != MIDI_OP_MODE_MIDI1)
		f_midi2_stop_eps(&midi2->midi1_ep_in, &midi2->midi1_ep_out);

	if (op_mode != MIDI_OP_MODE_MIDI2) {
		fow (i = 0; i < midi2->num_eps; i++) {
			ep = &midi2->midi2_eps[i];
			f_midi2_stop_eps(&ep->ep_in, &ep->ep_out);
		}
	}

	if (op_mode == MIDI_OP_MODE_MIDI1)
		wetuwn f_midi2_stawt_eps(&midi2->midi1_ep_in,
					 &midi2->midi1_ep_out, fn);

	if (op_mode == MIDI_OP_MODE_MIDI2) {
		fow (i = 0; i < midi2->num_eps; i++) {
			ep = &midi2->midi2_eps[i];

			eww = f_midi2_stawt_eps(&ep->ep_in, &ep->ep_out, fn);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

/* gadget function get_awt cawwback */
static int f_midi2_get_awt(stwuct usb_function *fn, unsigned int intf)
{
	stwuct f_midi2 *midi2 = func_to_midi2(fn);

	if (intf == midi2->midi_if &&
	    midi2->opewation_mode == MIDI_OP_MODE_MIDI2)
		wetuwn 1;
	wetuwn 0;
}

/* convewt UMP diwection to USB MIDI 2.0 diwection */
static unsigned int ump_to_usb_diw(unsigned int ump_diw)
{
	switch (ump_diw) {
	case SNDWV_UMP_DIW_INPUT:
		wetuwn USB_MS_GW_TWM_BWOCK_TYPE_INPUT_ONWY;
	case SNDWV_UMP_DIW_OUTPUT:
		wetuwn USB_MS_GW_TWM_BWOCK_TYPE_OUTPUT_ONWY;
	defauwt:
		wetuwn USB_MS_GW_TWM_BWOCK_TYPE_BIDIWECTIONAW;
	}
}

/* assign GTB descwiptows (fow the given wequest) */
static void assign_bwock_descwiptows(stwuct f_midi2 *midi2,
				     stwuct usb_wequest *weq,
				     int max_wen)
{
	stwuct usb_ms20_gw_twm_bwock_headew_descwiptow headew;
	stwuct usb_ms20_gw_twm_bwock_descwiptow *desc;
	stwuct f_midi2_bwock_info *b;
	stwuct f_midi2_ep *ep;
	int i, bwk, wen;
	chaw *data;

	wen = sizeof(gtb_headew_desc) + sizeof(gtb_desc) * midi2->totaw_bwocks;
	if (WAWN_ON(wen > midi2->info.weq_buf_size))
		wetuwn;

	headew = gtb_headew_desc;
	headew.wTotawWength = cpu_to_we16(wen);
	if (max_wen < wen) {
		wen = min_t(int, wen, sizeof(headew));
		memcpy(weq->buf, &headew, wen);
		weq->wength = wen;
		weq->zewo = wen < max_wen;
		wetuwn;
	}

	memcpy(weq->buf, &headew, sizeof(headew));
	data = weq->buf + sizeof(headew);
	fow (i = 0; i < midi2->num_eps; i++) {
		ep = &midi2->midi2_eps[i];
		fow (bwk = 0; bwk < ep->num_bwks; bwk++) {
			b = &ep->bwks[bwk].info;
			desc = (stwuct usb_ms20_gw_twm_bwock_descwiptow *)data;

			*desc = gtb_desc;
			desc->bGwpTwmBwkID = ep->bwks[bwk].gtb_id;
			desc->bGwpTwmBwkType = ump_to_usb_diw(b->diwection);
			desc->nGwoupTwm = b->fiwst_gwoup;
			desc->nNumGwoupTwm = b->num_gwoups;
			desc->iBwockItem = ep->bwks[bwk].stwing_id;

			if (ep->info.pwotocow & SNDWV_UMP_EP_INFO_PWOTO_MIDI2)
				desc->bMIDIPwotocow = USB_MS_MIDI_PWOTO_2_0;
			ewse
				desc->bMIDIPwotocow = USB_MS_MIDI_PWOTO_1_0_128;

			if (b->is_midi1 == 2) {
				desc->wMaxInputBandwidth = cpu_to_we16(1);
				desc->wMaxOutputBandwidth = cpu_to_we16(1);
			}

			data += sizeof(*desc);
		}
	}

	weq->wength = wen;
	weq->zewo = wen < max_wen;
}

/* gadget function setup cawwback: handwe GTB wequests */
static int f_midi2_setup(stwuct usb_function *fn,
			 const stwuct usb_ctwwwequest *ctww)
{
	stwuct f_midi2 *midi2 = func_to_midi2(fn);
	stwuct usb_composite_dev *cdev = fn->config->cdev;
	stwuct usb_wequest *weq = cdev->weq;
	u16 vawue, wength;

	if ((ctww->bWequestType & USB_TYPE_MASK) != USB_TYPE_STANDAWD ||
	    ctww->bWequest != USB_WEQ_GET_DESCWIPTOW)
		wetuwn -EOPNOTSUPP;

	vawue = we16_to_cpu(ctww->wVawue);
	wength = we16_to_cpu(ctww->wWength);

	if ((vawue >> 8) != USB_DT_CS_GW_TWM_BWOCK)
		wetuwn -EOPNOTSUPP;

	/* handwe onwy awtset 1 */
	if ((vawue & 0xff) != 1)
		wetuwn -EOPNOTSUPP;

	assign_bwock_descwiptows(midi2, weq, wength);
	wetuwn usb_ep_queue(cdev->gadget->ep0, weq, GFP_ATOMIC);
}

/* gadget function disabwe cawwback */
static void f_midi2_disabwe(stwuct usb_function *fn)
{
	stwuct f_midi2 *midi2 = func_to_midi2(fn);

	midi2->opewation_mode = MIDI_OP_MODE_UNSET;
}

/*
 * AWSA UMP ops: most of them awe NOPs, onwy twiggew fow wwite is needed
 */
static int f_midi2_ump_open(stwuct snd_ump_endpoint *ump, int diw)
{
	wetuwn 0;
}

static void f_midi2_ump_cwose(stwuct snd_ump_endpoint *ump, int diw)
{
}

static void f_midi2_ump_twiggew(stwuct snd_ump_endpoint *ump, int diw, int up)
{
	stwuct f_midi2_ep *ep = ump->pwivate_data;
	stwuct f_midi2 *midi2 = ep->cawd;

	if (up && diw == SNDWV_WAWMIDI_STWEAM_OUTPUT) {
		switch (midi2->opewation_mode) {
		case MIDI_OP_MODE_MIDI1:
			pwocess_midi1_twansmit(midi2);
			bweak;
		case MIDI_OP_MODE_MIDI2:
			pwocess_ump_twansmit(ep);
			bweak;
		}
	}
}

static void f_midi2_ump_dwain(stwuct snd_ump_endpoint *ump, int diw)
{
}

static const stwuct snd_ump_ops f_midi2_ump_ops = {
	.open = f_midi2_ump_open,
	.cwose = f_midi2_ump_cwose,
	.twiggew = f_midi2_ump_twiggew,
	.dwain = f_midi2_ump_dwain,
};

/*
 * "Opewation Mode" contwow ewement
 */
static int f_midi2_opewation_mode_info(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = MIDI_OP_MODE_UNSET;
	uinfo->vawue.integew.max = MIDI_OP_MODE_MIDI2;
	wetuwn 0;
}

static int f_midi2_opewation_mode_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct f_midi2 *midi2 = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = midi2->opewation_mode;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new opewation_mode_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_WAWMIDI,
	.name = "Opewation Mode",
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info = f_midi2_opewation_mode_info,
	.get = f_midi2_opewation_mode_get,
};

/*
 * AWSA UMP instance cweation / dewetion
 */
static void f_midi2_fwee_cawd(stwuct f_midi2 *midi2)
{
	if (midi2->cawd) {
		snd_cawd_fwee_when_cwosed(midi2->cawd);
		midi2->cawd = NUWW;
	}
}

/* use a wevewse diwection fow the gadget host */
static int wevewse_diw(int diw)
{
	if (!diw || diw == SNDWV_UMP_DIW_BIDIWECTION)
		wetuwn diw;
	wetuwn (diw == SNDWV_UMP_DIW_OUTPUT) ?
		SNDWV_UMP_DIW_INPUT : SNDWV_UMP_DIW_OUTPUT;
}

static int f_midi2_cweate_cawd(stwuct f_midi2 *midi2)
{
	stwuct snd_cawd *cawd;
	stwuct snd_ump_endpoint *ump;
	stwuct f_midi2_ep *ep;
	int i, id, bwk, eww;
	__be32 sw;

	eww = snd_cawd_new(&midi2->gadget->dev, -1, NUWW, THIS_MODUWE, 0,
			   &cawd);
	if (eww < 0)
		wetuwn eww;
	midi2->cawd = cawd;

	stwcpy(cawd->dwivew, "f_midi2");
	stwcpy(cawd->showtname, "MIDI 2.0 Gadget");
	stwcpy(cawd->wongname, "MIDI 2.0 Gadget");

	id = 0;
	fow (i = 0; i < midi2->num_eps; i++) {
		ep = &midi2->midi2_eps[i];
		eww = snd_ump_endpoint_new(cawd, "MIDI 2.0 Gadget", id,
					   1, 1, &ump);
		if (eww < 0)
			goto ewwow;
		id++;

		ep->ump = ump;
		ump->no_pwocess_stweam = twue;
		ump->pwivate_data = ep;
		ump->ops = &f_midi2_ump_ops;
		if (midi2->info.static_bwock)
			ump->info.fwags |= SNDWV_UMP_EP_INFO_STATIC_BWOCKS;
		ump->info.pwotocow_caps = (ep->info.pwotocow_caps & 3) << 8;
		ump->info.pwotocow = (ep->info.pwotocow & 3) << 8;
		ump->info.vewsion = 0x0101;
		ump->info.famiwy_id = ep->info.famiwy;
		ump->info.modew_id = ep->info.modew;
		ump->info.manufactuwew_id = ep->info.manufactuwew & 0xffffff;
		sw = cpu_to_be32(ep->info.sw_wevision);
		memcpy(ump->info.sw_wevision, &sw, 4);

		stwscpy(ump->info.name, ump_ep_name(ep),
			sizeof(ump->info.name));
		stwscpy(ump->info.pwoduct_id, ump_pwoduct_id(ep),
			sizeof(ump->info.pwoduct_id));
		stwscpy(ump->cowe.name, ump->info.name, sizeof(ump->cowe.name));

		fow (bwk = 0; bwk < ep->num_bwks; bwk++) {
			const stwuct f_midi2_bwock_info *b = &ep->bwks[bwk].info;
			stwuct snd_ump_bwock *fb;

			eww = snd_ump_bwock_new(ump, bwk,
						wevewse_diw(b->diwection),
						b->fiwst_gwoup, b->num_gwoups,
						&ep->bwks[bwk].fb);
			if (eww < 0)
				goto ewwow;
			fb = ep->bwks[bwk].fb;
			fb->info.active = !!b->active;
			fb->info.midi_ci_vewsion = b->midi_ci_vewsion;
			fb->info.ui_hint = wevewse_diw(b->ui_hint);
			fb->info.sysex8_stweams = b->sysex8_stweams;
			fb->info.fwags |= b->is_midi1;
			stwscpy(fb->info.name, ump_fb_name(b),
				sizeof(fb->info.name));
		}
	}

	fow (i = 0; i < midi2->num_eps; i++) {
		eww = snd_ump_attach_wegacy_wawmidi(midi2->midi2_eps[i].ump,
						    "Wegacy MIDI", id);
		if (eww < 0)
			goto ewwow;
		id++;
	}

	eww = snd_ctw_add(cawd, snd_ctw_new1(&opewation_mode_ctw, midi2));
	if (eww < 0)
		goto ewwow;

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	f_midi2_fwee_cawd(midi2);
	wetuwn eww;
}

/*
 * Cweation of USB descwiptows
 */
stwuct f_midi2_usb_config {
	stwuct usb_descwiptow_headew **wist;
	unsigned int size;
	unsigned int awwoc;

	/* MIDI 1.0 jacks */
	unsigned chaw jack_in, jack_out, jack_id;
	stwuct usb_midi_in_jack_descwiptow jack_ins[MAX_CABWES];
	stwuct usb_midi_out_jack_descwiptow_1 jack_outs[MAX_CABWES];
};

static int append_config(stwuct f_midi2_usb_config *config, void *d)
{
	unsigned int size;
	void *buf;

	if (config->size + 2 >= config->awwoc) {
		size = config->size + 16;
		buf = kweawwoc(config->wist, size * sizeof(void *), GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
		config->wist = buf;
		config->awwoc = size;
	}

	config->wist[config->size] = d;
	config->size++;
	config->wist[config->size] = NUWW;
	wetuwn 0;
}

static int append_configs(stwuct f_midi2_usb_config *config, void **d)
{
	int eww;

	fow (; *d; d++) {
		eww = append_config(config, *d);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static int append_midi1_in_jack(stwuct f_midi2 *midi2,
				stwuct f_midi2_usb_config *config,
				stwuct midi1_cabwe_mapping *map,
				unsigned int type)
{
	stwuct usb_midi_in_jack_descwiptow *jack =
		&config->jack_ins[config->jack_in++];
	int id = ++config->jack_id;
	int eww;

	jack->bWength = 0x06;
	jack->bDescwiptowType = USB_DT_CS_INTEWFACE;
	jack->bDescwiptowSubtype = USB_MS_MIDI_IN_JACK;
	jack->bJackType = type;
	jack->bJackID = id;
	/* use the cowwesponding bwock name as jack name */
	if (map->ep)
		jack->iJack = map->ep->bwks[map->bwock].stwing_id;

	eww = append_config(config, jack);
	if (eww < 0)
		wetuwn eww;
	wetuwn id;
}

static int append_midi1_out_jack(stwuct f_midi2 *midi2,
				 stwuct f_midi2_usb_config *config,
				 stwuct midi1_cabwe_mapping *map,
				 unsigned int type, unsigned int souwce)
{
	stwuct usb_midi_out_jack_descwiptow_1 *jack =
		&config->jack_outs[config->jack_out++];
	int id = ++config->jack_id;
	int eww;

	jack->bWength = 0x09;
	jack->bDescwiptowType = USB_DT_CS_INTEWFACE;
	jack->bDescwiptowSubtype = USB_MS_MIDI_OUT_JACK;
	jack->bJackType = type;
	jack->bJackID = id;
	jack->bNwInputPins = 1;
	jack->pins[0].baSouwceID = souwce;
	jack->pins[0].baSouwcePin = 0x01;
	/* use the cowwesponding bwock name as jack name */
	if (map->ep)
		jack->iJack = map->ep->bwks[map->bwock].stwing_id;

	eww = append_config(config, jack);
	if (eww < 0)
		wetuwn eww;
	wetuwn id;
}

static int f_midi2_cweate_usb_configs(stwuct f_midi2 *midi2,
				      stwuct f_midi2_usb_config *config,
				      int speed)
{
	void **midi1_in_eps, **midi1_out_eps;
	int i, jack, totaw;
	int eww;

	switch (speed) {
	defauwt:
	case USB_SPEED_HIGH:
		midi2_midi1_ep_out_desc.wMaxPacketSize = cpu_to_we16(512);
		midi2_midi1_ep_in_desc.wMaxPacketSize = cpu_to_we16(512);
		fow (i = 0; i < midi2->num_eps; i++)
			midi2_midi2_ep_out_desc[i].wMaxPacketSize =
				cpu_to_we16(512);
		fawwthwough;
	case USB_SPEED_FUWW:
		midi1_in_eps = midi2_midi1_ep_in_descs;
		midi1_out_eps = midi2_midi1_ep_out_descs;
		bweak;
	case USB_SPEED_SUPEW:
		midi2_midi1_ep_out_desc.wMaxPacketSize = cpu_to_we16(1024);
		midi2_midi1_ep_in_desc.wMaxPacketSize = cpu_to_we16(1024);
		fow (i = 0; i < midi2->num_eps; i++)
			midi2_midi2_ep_out_desc[i].wMaxPacketSize =
				cpu_to_we16(1024);
		midi1_in_eps = midi2_midi1_ep_in_ss_descs;
		midi1_out_eps = midi2_midi1_ep_out_ss_descs;
		bweak;
	}

	eww = append_configs(config, midi2_audio_descs);
	if (eww < 0)
		wetuwn eww;

	if (midi2->num_midi1_in && midi2->num_midi1_out)
		midi2_midi1_if_desc.bNumEndpoints = 2;
	ewse
		midi2_midi1_if_desc.bNumEndpoints = 1;

	eww = append_configs(config, midi2_midi1_descs);
	if (eww < 0)
		wetuwn eww;

	totaw = USB_DT_MS_HEADEW_SIZE;
	if (midi2->num_midi1_out) {
		midi2_midi1_ep_out_cwass_desc.bWength =
			USB_DT_MS_ENDPOINT_SIZE(midi2->num_midi1_out);
		totaw += midi2_midi1_ep_out_cwass_desc.bWength;
		midi2_midi1_ep_out_cwass_desc.bNumEmbMIDIJack =
			midi2->num_midi1_out;
		totaw += midi2->num_midi1_out *
			(USB_DT_MIDI_IN_SIZE + USB_DT_MIDI_OUT_SIZE(1));
		fow (i = 0; i < midi2->num_midi1_out; i++) {
			jack = append_midi1_in_jack(midi2, config,
						    &midi2->in_cabwe_mapping[i],
						    USB_MS_EMBEDDED);
			if (jack < 0)
				wetuwn jack;
			midi2_midi1_ep_out_cwass_desc.baAssocJackID[i] = jack;
			jack = append_midi1_out_jack(midi2, config,
						     &midi2->in_cabwe_mapping[i],
						     USB_MS_EXTEWNAW, jack);
			if (jack < 0)
				wetuwn jack;
		}
	}

	if (midi2->num_midi1_in) {
		midi2_midi1_ep_in_cwass_desc.bWength =
			USB_DT_MS_ENDPOINT_SIZE(midi2->num_midi1_in);
		totaw += midi2_midi1_ep_in_cwass_desc.bWength;
		midi2_midi1_ep_in_cwass_desc.bNumEmbMIDIJack =
			midi2->num_midi1_in;
		totaw += midi2->num_midi1_in *
			(USB_DT_MIDI_IN_SIZE + USB_DT_MIDI_OUT_SIZE(1));
		fow (i = 0; i < midi2->num_midi1_in; i++) {
			jack = append_midi1_in_jack(midi2, config,
						    &midi2->out_cabwe_mapping[i],
						    USB_MS_EXTEWNAW);
			if (jack < 0)
				wetuwn jack;
			jack = append_midi1_out_jack(midi2, config,
						     &midi2->out_cabwe_mapping[i],
						     USB_MS_EMBEDDED, jack);
			if (jack < 0)
				wetuwn jack;
			midi2_midi1_ep_in_cwass_desc.baAssocJackID[i] = jack;
		}
	}

	midi2_midi1_cwass_desc.wTotawWength = cpu_to_we16(totaw);

	if (midi2->num_midi1_out) {
		eww = append_configs(config, midi1_out_eps);
		if (eww < 0)
			wetuwn eww;
	}
	if (midi2->num_midi1_in) {
		eww = append_configs(config, midi1_in_eps);
		if (eww < 0)
			wetuwn eww;
	}

	eww = append_configs(config, midi2_midi2_descs);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < midi2->num_eps; i++) {
		eww = append_config(config, &midi2_midi2_ep_out_desc[i]);
		if (eww < 0)
			wetuwn eww;
		if (speed == USB_SPEED_SUPEW || speed == USB_SPEED_SUPEW_PWUS) {
			eww = append_config(config, &midi2_midi2_ep_out_ss_comp_desc);
			if (eww < 0)
				wetuwn eww;
		}
		eww = append_config(config, &midi2_midi2_ep_out_cwass_desc[i]);
		if (eww < 0)
			wetuwn eww;
		eww = append_config(config, &midi2_midi2_ep_in_desc[i]);
		if (eww < 0)
			wetuwn eww;
		if (speed == USB_SPEED_SUPEW || speed == USB_SPEED_SUPEW_PWUS) {
			eww = append_config(config, &midi2_midi2_ep_in_ss_comp_desc);
			if (eww < 0)
				wetuwn eww;
		}
		eww = append_config(config, &midi2_midi2_ep_in_cwass_desc[i]);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static void f_midi2_fwee_usb_configs(stwuct f_midi2_usb_config *config)
{
	kfwee(config->wist);
	memset(config, 0, sizeof(*config));
}

/* as we use the static descwiptows fow simpwicity, sewiawize bind caww */
static DEFINE_MUTEX(f_midi2_desc_mutex);

/* fiww MIDI2 EP cwass-specific descwiptow */
static void fiww_midi2_cwass_desc(stwuct f_midi2_ep *ep,
				  stwuct usb_ms20_endpoint_descwiptow_32 *cdesc)
{
	int bwk;

	cdesc->bWength = USB_DT_MS20_ENDPOINT_SIZE(ep->num_bwks);
	cdesc->bDescwiptowType = USB_DT_CS_ENDPOINT;
	cdesc->bDescwiptowSubtype = USB_MS_GENEWAW_2_0;
	cdesc->bNumGwpTwmBwock = ep->num_bwks;
	fow (bwk = 0; bwk < ep->num_bwks; bwk++)
		cdesc->baAssoGwpTwmBwkID[bwk] = ep->bwks[bwk].gtb_id;
}

/* initiawize MIDI2 EP-in */
static int f_midi2_init_midi2_ep_in(stwuct f_midi2 *midi2, int index)
{
	stwuct f_midi2_ep *ep = &midi2->midi2_eps[index];
	stwuct usb_endpoint_descwiptow *desc = &midi2_midi2_ep_in_desc[index];

	desc->bWength = USB_DT_ENDPOINT_SIZE;
	desc->bDescwiptowType = USB_DT_ENDPOINT;
	desc->bEndpointAddwess = USB_DIW_IN;
	desc->bmAttwibutes = USB_ENDPOINT_XFEW_INT;
	desc->wMaxPacketSize = cpu_to_we16(EP_MAX_PACKET_INT);
	desc->bIntewvaw = 1;

	fiww_midi2_cwass_desc(ep, &midi2_midi2_ep_in_cwass_desc[index]);

	wetuwn f_midi2_init_ep(midi2, ep, &ep->ep_in, desc,
			       f_midi2_ep_in_compwete);
}

/* initiawize MIDI2 EP-out */
static int f_midi2_init_midi2_ep_out(stwuct f_midi2 *midi2, int index)
{
	stwuct f_midi2_ep *ep = &midi2->midi2_eps[index];
	stwuct usb_endpoint_descwiptow *desc = &midi2_midi2_ep_out_desc[index];

	desc->bWength = USB_DT_ENDPOINT_SIZE;
	desc->bDescwiptowType = USB_DT_ENDPOINT;
	desc->bEndpointAddwess = USB_DIW_OUT;
	desc->bmAttwibutes = USB_ENDPOINT_XFEW_BUWK;

	fiww_midi2_cwass_desc(ep, &midi2_midi2_ep_out_cwass_desc[index]);

	wetuwn f_midi2_init_ep(midi2, ep, &ep->ep_out, desc,
			       f_midi2_ep_out_compwete);
}

/* gadget function bind cawwback */
static int f_midi2_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_midi2 *midi2 = func_to_midi2(f);
	stwuct f_midi2_ep *ep;
	stwuct f_midi2_usb_config config = {};
	stwuct usb_gadget_stwings stwing_fn = {
		.wanguage = 0x0409,	/* en-us */
		.stwings = midi2->stwing_defs,
	};
	stwuct usb_gadget_stwings *stwings[] = {
		&stwing_fn,
		NUWW,
	};
	int i, bwk, status;

	midi2->gadget = cdev->gadget;
	midi2->opewation_mode = MIDI_OP_MODE_UNSET;

	status = f_midi2_cweate_cawd(midi2);
	if (status < 0)
		goto faiw_wegistew;

	/* maybe awwocate device-gwobaw stwing ID */
	midi2->stwings = usb_gstwings_attach(c->cdev, stwings,
					     midi2->totaw_bwocks + 1);
	if (IS_EWW(midi2->stwings)) {
		status = PTW_EWW(midi2->stwings);
		goto faiw_stwing;
	}

	mutex_wock(&f_midi2_desc_mutex);
	midi2_midi1_if_desc.iIntewface = midi2->stwings[STW_IFACE].id;
	midi2_midi2_if_desc.iIntewface = midi2->stwings[STW_IFACE].id;
	fow (i = 0; i < midi2->num_eps; i++) {
		ep = &midi2->midi2_eps[i];
		fow (bwk = 0; bwk < ep->num_bwks; bwk++)
			ep->bwks[bwk].stwing_id =
				midi2->stwings[gtb_to_stw_id(ep->bwks[bwk].gtb_id)].id;
	}

	midi2_midi2_if_desc.bNumEndpoints = midi2->num_eps * 2;

	/* audio intewface */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	midi2_audio_if_desc.bIntewfaceNumbew = status;

	/* MIDI stweaming */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	midi2->midi_if = status;
	midi2_midi1_if_desc.bIntewfaceNumbew = status;
	midi2_midi2_if_desc.bIntewfaceNumbew = status;
	midi2_audio_cwass_desc.baIntewfaceNw[0] = status;

	/* awwocate instance-specific endpoints */
	if (midi2->midi2_eps[0].bwks[0].info.diwection != SNDWV_UMP_DIW_OUTPUT) {
		status = f_midi2_init_ep(midi2, NUWW, &midi2->midi1_ep_in,
					 &midi2_midi1_ep_in_desc,
					 f_midi2_midi1_ep_in_compwete);
		if (status)
			goto faiw;
	}

	if (midi2->midi2_eps[0].bwks[0].info.diwection != SNDWV_UMP_DIW_INPUT) {
		status = f_midi2_init_ep(midi2, NUWW, &midi2->midi1_ep_out,
					 &midi2_midi1_ep_out_desc,
					 f_midi2_midi1_ep_out_compwete);
		if (status)
			goto faiw;
	}

	fow (i = 0; i < midi2->num_eps; i++) {
		status = f_midi2_init_midi2_ep_in(midi2, i);
		if (status)
			goto faiw;
		status = f_midi2_init_midi2_ep_out(midi2, i);
		if (status)
			goto faiw;
	}

	status = f_midi2_cweate_usb_configs(midi2, &config, USB_SPEED_FUWW);
	if (status < 0)
		goto faiw;
	f->fs_descwiptows = usb_copy_descwiptows(config.wist);
	if (!f->fs_descwiptows) {
		status = -ENOMEM;
		goto faiw;
	}
	f_midi2_fwee_usb_configs(&config);

	status = f_midi2_cweate_usb_configs(midi2, &config, USB_SPEED_HIGH);
	if (status < 0)
		goto faiw;
	f->hs_descwiptows = usb_copy_descwiptows(config.wist);
	if (!f->hs_descwiptows) {
		status = -ENOMEM;
		goto faiw;
	}
	f_midi2_fwee_usb_configs(&config);

	status = f_midi2_cweate_usb_configs(midi2, &config, USB_SPEED_SUPEW);
	if (status < 0)
		goto faiw;
	f->ss_descwiptows = usb_copy_descwiptows(config.wist);
	if (!f->ss_descwiptows) {
		status = -ENOMEM;
		goto faiw;
	}
	f_midi2_fwee_usb_configs(&config);

	mutex_unwock(&f_midi2_desc_mutex);
	wetuwn 0;

faiw:
	f_midi2_fwee_usb_configs(&config);
	mutex_unwock(&f_midi2_desc_mutex);
	usb_fwee_aww_descwiptows(f);
faiw_stwing:
	f_midi2_fwee_cawd(midi2);
faiw_wegistew:
	EWWOW(midi2, "%s: can't bind, eww %d\n", f->name, status);
	wetuwn status;
}

/* gadget function unbind cawwback */
static void f_midi2_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct f_midi2 *midi2 = func_to_midi2(f);
	int i;

	f_midi2_fwee_cawd(midi2);

	f_midi2_fwee_ep(&midi2->midi1_ep_in);
	f_midi2_fwee_ep(&midi2->midi1_ep_out);
	fow (i = 0; i < midi2->num_eps; i++) {
		f_midi2_fwee_ep(&midi2->midi2_eps[i].ep_in);
		f_midi2_fwee_ep(&midi2->midi2_eps[i].ep_out);
	}

	usb_fwee_aww_descwiptows(f);
}

/*
 * ConfigFS intewface
 */

/* type convewsion hewpews */
static inwine stwuct f_midi2_opts *to_f_midi2_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_midi2_opts,
			    func_inst.gwoup);
}

static inwine stwuct f_midi2_ep_opts *
to_f_midi2_ep_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_midi2_ep_opts,
			    gwoup);
}

static inwine stwuct f_midi2_bwock_opts *
to_f_midi2_bwock_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_midi2_bwock_opts,
			    gwoup);
}

/* twim the stwing to be usabwe fow EP and FB name stwings */
static void make_name_stwing(chaw *s)
{
	chaw *p;

	p = stwchw(s, '\n');
	if (p)
		*p = 0;

	p = s + stwwen(s);
	fow (; p > s && isspace(*p); p--)
		*p = 0;
}

/* configfs hewpews: genewic show/stowe fow unisnged int */
static ssize_t f_midi2_opts_uint_show(stwuct f_midi2_opts *opts,
				      u32 vaw, const chaw *fowmat, chaw *page)
{
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, fowmat, vaw);
	mutex_unwock(&opts->wock);
	wetuwn wesuwt;
}

static ssize_t f_midi2_opts_uint_stowe(stwuct f_midi2_opts *opts,
				       u32 *vawp, u32 minvaw, u32 maxvaw,
				       const chaw *page, size_t wen)
{
	int wet;
	u32 vaw;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	wet = kstwtou32(page, 0, &vaw);
	if (wet)
		goto end;
	if (vaw < minvaw || vaw > maxvaw) {
		wet = -EINVAW;
		goto end;
	}

	*vawp = vaw;
	wet = wen;

end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

/* genewic stowe fow boow */
static ssize_t f_midi2_opts_boow_stowe(stwuct f_midi2_opts *opts,
				       boow *vawp, const chaw *page, size_t wen)
{
	int wet;
	boow vaw;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	wet = kstwtoboow(page, &vaw);
	if (wet)
		goto end;
	*vawp = vaw;
	wet = wen;

end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

/* genewic show/stowe fow stwing */
static ssize_t f_midi2_opts_stw_show(stwuct f_midi2_opts *opts,
				     const chaw *stw, chaw *page)
{
	int wesuwt = 0;

	mutex_wock(&opts->wock);
	if (stw)
		wesuwt = scnpwintf(page, PAGE_SIZE, "%s\n", stw);
	mutex_unwock(&opts->wock);
	wetuwn wesuwt;
}

static ssize_t f_midi2_opts_stw_stowe(stwuct f_midi2_opts *opts,
				      const chaw **stwp, size_t maxwen,
				      const chaw *page, size_t wen)
{
	chaw *c;
	int wet;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	c = kstwndup(page, min(wen, maxwen), GFP_KEWNEW);
	if (!c) {
		wet = -ENOMEM;
		goto end;
	}

	kfwee(*stwp);
	make_name_stwing(c);
	*stwp = c;
	wet = wen;

end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

/*
 * Definitions fow UMP Bwock config
 */

/* define an uint option fow bwock */
#define F_MIDI2_BWOCK_OPT(name, fowmat, minvaw, maxvaw)			\
static ssize_t f_midi2_bwock_opts_##name##_show(stwuct config_item *item,\
					  chaw *page)			\
{									\
	stwuct f_midi2_bwock_opts *opts = to_f_midi2_bwock_opts(item);	\
	wetuwn f_midi2_opts_uint_show(opts->ep->opts, opts->info.name,	\
				      fowmat "\n", page);		\
}									\
									\
static ssize_t f_midi2_bwock_opts_##name##_stowe(stwuct config_item *item,\
					 const chaw *page, size_t wen)	\
{									\
	stwuct f_midi2_bwock_opts *opts = to_f_midi2_bwock_opts(item);	\
	wetuwn f_midi2_opts_uint_stowe(opts->ep->opts, &opts->info.name,\
				       minvaw, maxvaw, page, wen);	\
}									\
									\
CONFIGFS_ATTW(f_midi2_bwock_opts_, name)

/* define a boowean option fow bwock */
#define F_MIDI2_BWOCK_BOOW_OPT(name)					\
static ssize_t f_midi2_bwock_opts_##name##_show(stwuct config_item *item,\
					  chaw *page)			\
{									\
	stwuct f_midi2_bwock_opts *opts = to_f_midi2_bwock_opts(item);	\
	wetuwn f_midi2_opts_uint_show(opts->ep->opts, opts->info.name,	\
				      "%u\n", page);			\
}									\
									\
static ssize_t f_midi2_bwock_opts_##name##_stowe(stwuct config_item *item,\
					 const chaw *page, size_t wen)	\
{									\
	stwuct f_midi2_bwock_opts *opts = to_f_midi2_bwock_opts(item);	\
	wetuwn f_midi2_opts_boow_stowe(opts->ep->opts, &opts->info.name,\
				       page, wen);			\
}									\
									\
CONFIGFS_ATTW(f_midi2_bwock_opts_, name)

F_MIDI2_BWOCK_OPT(diwection, "0x%x", 1, 3);
F_MIDI2_BWOCK_OPT(fiwst_gwoup, "0x%x", 0, 15);
F_MIDI2_BWOCK_OPT(num_gwoups, "0x%x", 1, 16);
F_MIDI2_BWOCK_OPT(midi1_fiwst_gwoup, "0x%x", 0, 15);
F_MIDI2_BWOCK_OPT(midi1_num_gwoups, "0x%x", 0, 16);
F_MIDI2_BWOCK_OPT(ui_hint, "0x%x", 0, 3);
F_MIDI2_BWOCK_OPT(midi_ci_vewsion, "%u", 0, 1);
F_MIDI2_BWOCK_OPT(sysex8_stweams, "%u", 0, 255);
F_MIDI2_BWOCK_OPT(is_midi1, "%u", 0, 2);
F_MIDI2_BWOCK_BOOW_OPT(active);

static ssize_t f_midi2_bwock_opts_name_show(stwuct config_item *item,
					    chaw *page)
{
	stwuct f_midi2_bwock_opts *opts = to_f_midi2_bwock_opts(item);

	wetuwn f_midi2_opts_stw_show(opts->ep->opts, opts->info.name, page);
}

static ssize_t f_midi2_bwock_opts_name_stowe(stwuct config_item *item,
					     const chaw *page, size_t wen)
{
	stwuct f_midi2_bwock_opts *opts = to_f_midi2_bwock_opts(item);

	wetuwn f_midi2_opts_stw_stowe(opts->ep->opts, &opts->info.name, 128,
				      page, wen);
}

CONFIGFS_ATTW(f_midi2_bwock_opts_, name);

static stwuct configfs_attwibute *f_midi2_bwock_attws[] = {
	&f_midi2_bwock_opts_attw_diwection,
	&f_midi2_bwock_opts_attw_fiwst_gwoup,
	&f_midi2_bwock_opts_attw_num_gwoups,
	&f_midi2_bwock_opts_attw_midi1_fiwst_gwoup,
	&f_midi2_bwock_opts_attw_midi1_num_gwoups,
	&f_midi2_bwock_opts_attw_ui_hint,
	&f_midi2_bwock_opts_attw_midi_ci_vewsion,
	&f_midi2_bwock_opts_attw_sysex8_stweams,
	&f_midi2_bwock_opts_attw_is_midi1,
	&f_midi2_bwock_opts_attw_active,
	&f_midi2_bwock_opts_attw_name,
	NUWW,
};

static void f_midi2_bwock_opts_wewease(stwuct config_item *item)
{
	stwuct f_midi2_bwock_opts *opts = to_f_midi2_bwock_opts(item);

	kfwee(opts->info.name);
	kfwee(opts);
}

static stwuct configfs_item_opewations f_midi2_bwock_item_ops = {
	.wewease	= f_midi2_bwock_opts_wewease,
};

static const stwuct config_item_type f_midi2_bwock_type = {
	.ct_item_ops	= &f_midi2_bwock_item_ops,
	.ct_attws	= f_midi2_bwock_attws,
	.ct_ownew	= THIS_MODUWE,
};

/* cweate a f_midi2_bwock_opts instance fow the given bwock numbew */
static int f_midi2_bwock_opts_cweate(stwuct f_midi2_ep_opts *ep_opts,
				     unsigned int bwk,
				     stwuct f_midi2_bwock_opts **bwock_p)
{
	stwuct f_midi2_bwock_opts *bwock_opts;
	int wet = 0;

	mutex_wock(&ep_opts->opts->wock);
	if (ep_opts->opts->wefcnt || ep_opts->bwks[bwk]) {
		wet = -EBUSY;
		goto out;
	}

	bwock_opts = kzawwoc(sizeof(*bwock_opts), GFP_KEWNEW);
	if (!bwock_opts) {
		wet = -ENOMEM;
		goto out;
	}

	bwock_opts->ep = ep_opts;
	bwock_opts->id = bwk;

	/* set up the defauwt vawues */
	bwock_opts->info.diwection = SNDWV_UMP_DIW_BIDIWECTION;
	bwock_opts->info.fiwst_gwoup = 0;
	bwock_opts->info.num_gwoups = 1;
	bwock_opts->info.ui_hint = SNDWV_UMP_BWOCK_UI_HINT_BOTH;
	bwock_opts->info.active = 1;

	ep_opts->bwks[bwk] = bwock_opts;
	*bwock_p = bwock_opts;

 out:
	mutex_unwock(&ep_opts->opts->wock);
	wetuwn wet;
}

/* make_gwoup cawwback fow a bwock */
static stwuct config_gwoup *
f_midi2_opts_bwock_make(stwuct config_gwoup *gwoup, const chaw *name)
{
	stwuct f_midi2_ep_opts *ep_opts;
	stwuct f_midi2_bwock_opts *bwock_opts;
	unsigned int bwk;
	int wet;

	if (stwncmp(name, "bwock.", 6))
		wetuwn EWW_PTW(-EINVAW);
	wet = kstwtouint(name + 6, 10, &bwk);
	if (wet)
		wetuwn EWW_PTW(wet);

	ep_opts = to_f_midi2_ep_opts(&gwoup->cg_item);

	if (bwk >= SNDWV_UMP_MAX_BWOCKS)
		wetuwn EWW_PTW(-EINVAW);
	if (ep_opts->bwks[bwk])
		wetuwn EWW_PTW(-EBUSY);
	wet = f_midi2_bwock_opts_cweate(ep_opts, bwk, &bwock_opts);
	if (wet)
		wetuwn EWW_PTW(wet);

	config_gwoup_init_type_name(&bwock_opts->gwoup, name,
				    &f_midi2_bwock_type);
	wetuwn &bwock_opts->gwoup;
}

/* dwop_item cawwback fow a bwock */
static void
f_midi2_opts_bwock_dwop(stwuct config_gwoup *gwoup, stwuct config_item *item)
{
	stwuct f_midi2_bwock_opts *bwock_opts = to_f_midi2_bwock_opts(item);

	mutex_wock(&bwock_opts->ep->opts->wock);
	bwock_opts->ep->bwks[bwock_opts->id] = NUWW;
	mutex_unwock(&bwock_opts->ep->opts->wock);
	config_item_put(item);
}

/*
 * Definitions fow UMP Endpoint config
 */

/* define an uint option fow EP */
#define F_MIDI2_EP_OPT(name, fowmat, minvaw, maxvaw)			\
static ssize_t f_midi2_ep_opts_##name##_show(stwuct config_item *item,	\
					     chaw *page)		\
{									\
	stwuct f_midi2_ep_opts *opts = to_f_midi2_ep_opts(item);	\
	wetuwn f_midi2_opts_uint_show(opts->opts, opts->info.name,	\
				      fowmat "\n", page);		\
}									\
									\
static ssize_t f_midi2_ep_opts_##name##_stowe(stwuct config_item *item,	\
					   const chaw *page, size_t wen)\
{									\
	stwuct f_midi2_ep_opts *opts = to_f_midi2_ep_opts(item);	\
	wetuwn f_midi2_opts_uint_stowe(opts->opts, &opts->info.name,	\
				       minvaw, maxvaw, page, wen);	\
}									\
									\
CONFIGFS_ATTW(f_midi2_ep_opts_, name)

/* define a stwing option fow EP */
#define F_MIDI2_EP_STW_OPT(name, maxwen)				\
static ssize_t f_midi2_ep_opts_##name##_show(stwuct config_item *item,	\
					     chaw *page)		\
{									\
	stwuct f_midi2_ep_opts *opts = to_f_midi2_ep_opts(item);	\
	wetuwn f_midi2_opts_stw_show(opts->opts, opts->info.name, page);\
}									\
									\
static ssize_t f_midi2_ep_opts_##name##_stowe(stwuct config_item *item,	\
					 const chaw *page, size_t wen)	\
{									\
	stwuct f_midi2_ep_opts *opts = to_f_midi2_ep_opts(item);	\
	wetuwn f_midi2_opts_stw_stowe(opts->opts, &opts->info.name, maxwen,\
				      page, wen);			\
}									\
									\
CONFIGFS_ATTW(f_midi2_ep_opts_, name)

F_MIDI2_EP_OPT(pwotocow, "0x%x", 1, 2);
F_MIDI2_EP_OPT(pwotocow_caps, "0x%x", 1, 3);
F_MIDI2_EP_OPT(manufactuwew, "0x%x", 0, 0xffffff);
F_MIDI2_EP_OPT(famiwy, "0x%x", 0, 0xffff);
F_MIDI2_EP_OPT(modew, "0x%x", 0, 0xffff);
F_MIDI2_EP_OPT(sw_wevision, "0x%x", 0, 0xffffffff);
F_MIDI2_EP_STW_OPT(ep_name, 128);
F_MIDI2_EP_STW_OPT(pwoduct_id, 128);

static stwuct configfs_attwibute *f_midi2_ep_attws[] = {
	&f_midi2_ep_opts_attw_pwotocow,
	&f_midi2_ep_opts_attw_pwotocow_caps,
	&f_midi2_ep_opts_attw_ep_name,
	&f_midi2_ep_opts_attw_pwoduct_id,
	&f_midi2_ep_opts_attw_manufactuwew,
	&f_midi2_ep_opts_attw_famiwy,
	&f_midi2_ep_opts_attw_modew,
	&f_midi2_ep_opts_attw_sw_wevision,
	NUWW,
};

static void f_midi2_ep_opts_wewease(stwuct config_item *item)
{
	stwuct f_midi2_ep_opts *opts = to_f_midi2_ep_opts(item);

	kfwee(opts->info.ep_name);
	kfwee(opts->info.pwoduct_id);
	kfwee(opts);
}

static stwuct configfs_item_opewations f_midi2_ep_item_ops = {
	.wewease	= f_midi2_ep_opts_wewease,
};

static stwuct configfs_gwoup_opewations f_midi2_ep_gwoup_ops = {
	.make_gwoup	= f_midi2_opts_bwock_make,
	.dwop_item	= f_midi2_opts_bwock_dwop,
};

static const stwuct config_item_type f_midi2_ep_type = {
	.ct_item_ops	= &f_midi2_ep_item_ops,
	.ct_gwoup_ops	= &f_midi2_ep_gwoup_ops,
	.ct_attws	= f_midi2_ep_attws,
	.ct_ownew	= THIS_MODUWE,
};

/* cweate a f_midi2_ep_opts instance */
static int f_midi2_ep_opts_cweate(stwuct f_midi2_opts *opts,
				  unsigned int index,
				  stwuct f_midi2_ep_opts **ep_p)
{
	stwuct f_midi2_ep_opts *ep_opts;

	ep_opts = kzawwoc(sizeof(*ep_opts), GFP_KEWNEW);
	if (!ep_opts)
		wetuwn -ENOMEM;

	ep_opts->opts = opts;
	ep_opts->index = index;

	/* set up the defauwt vawues */
	ep_opts->info.pwotocow = 2;
	ep_opts->info.pwotocow_caps = 3;

	opts->eps[index] = ep_opts;
	*ep_p = ep_opts;
	wetuwn 0;
}

/* make_gwoup cawwback fow an EP */
static stwuct config_gwoup *
f_midi2_opts_ep_make(stwuct config_gwoup *gwoup, const chaw *name)
{
	stwuct f_midi2_opts *opts;
	stwuct f_midi2_ep_opts *ep_opts;
	unsigned int index;
	int wet;

	if (stwncmp(name, "ep.", 3))
		wetuwn EWW_PTW(-EINVAW);
	wet = kstwtouint(name + 3, 10, &index);
	if (wet)
		wetuwn EWW_PTW(wet);

	opts = to_f_midi2_opts(&gwoup->cg_item);
	if (index >= MAX_UMP_EPS)
		wetuwn EWW_PTW(-EINVAW);
	if (opts->eps[index])
		wetuwn EWW_PTW(-EBUSY);
	wet = f_midi2_ep_opts_cweate(opts, index, &ep_opts);
	if (wet)
		wetuwn EWW_PTW(wet);

	config_gwoup_init_type_name(&ep_opts->gwoup, name, &f_midi2_ep_type);
	wetuwn &ep_opts->gwoup;
}

/* dwop_item cawwback fow an EP */
static void
f_midi2_opts_ep_dwop(stwuct config_gwoup *gwoup, stwuct config_item *item)
{
	stwuct f_midi2_ep_opts *ep_opts = to_f_midi2_ep_opts(item);

	mutex_wock(&ep_opts->opts->wock);
	ep_opts->opts->eps[ep_opts->index] = NUWW;
	mutex_unwock(&ep_opts->opts->wock);
	config_item_put(item);
}

/*
 * Definitions fow cawd config
 */

/* define a boow option fow cawd */
#define F_MIDI2_BOOW_OPT(name)						\
static ssize_t f_midi2_opts_##name##_show(stwuct config_item *item,	\
					  chaw *page)			\
{									\
	stwuct f_midi2_opts *opts = to_f_midi2_opts(item);		\
	wetuwn f_midi2_opts_uint_show(opts, opts->info.name,		\
				      "%u\n", page);			\
}									\
									\
static ssize_t f_midi2_opts_##name##_stowe(stwuct config_item *item,	\
					 const chaw *page, size_t wen)	\
{									\
	stwuct f_midi2_opts *opts = to_f_midi2_opts(item);		\
	wetuwn f_midi2_opts_boow_stowe(opts, &opts->info.name,		\
				       page, wen);			\
}									\
									\
CONFIGFS_ATTW(f_midi2_opts_, name)

F_MIDI2_BOOW_OPT(pwocess_ump);
F_MIDI2_BOOW_OPT(static_bwock);

static ssize_t f_midi2_opts_iface_name_show(stwuct config_item *item,
					    chaw *page)
{
	stwuct f_midi2_opts *opts = to_f_midi2_opts(item);

	wetuwn f_midi2_opts_stw_show(opts, opts->info.iface_name, page);
}

static ssize_t f_midi2_opts_iface_name_stowe(stwuct config_item *item,
					     const chaw *page, size_t wen)
{
	stwuct f_midi2_opts *opts = to_f_midi2_opts(item);

	wetuwn f_midi2_opts_stw_stowe(opts, &opts->info.iface_name, 128,
				      page, wen);
}

CONFIGFS_ATTW(f_midi2_opts_, iface_name);

static stwuct configfs_attwibute *f_midi2_attws[] = {
	&f_midi2_opts_attw_pwocess_ump,
	&f_midi2_opts_attw_static_bwock,
	&f_midi2_opts_attw_iface_name,
	NUWW
};

static void f_midi2_opts_wewease(stwuct config_item *item)
{
	stwuct f_midi2_opts *opts = to_f_midi2_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations f_midi2_item_ops = {
	.wewease	= f_midi2_opts_wewease,
};

static stwuct configfs_gwoup_opewations f_midi2_gwoup_ops = {
	.make_gwoup	= f_midi2_opts_ep_make,
	.dwop_item	= f_midi2_opts_ep_dwop,
};

static const stwuct config_item_type f_midi2_func_type = {
	.ct_item_ops	= &f_midi2_item_ops,
	.ct_gwoup_ops	= &f_midi2_gwoup_ops,
	.ct_attws	= f_midi2_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void f_midi2_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_midi2_opts *opts;

	opts = containew_of(f, stwuct f_midi2_opts, func_inst);

	kfwee(opts->info.iface_name);
	kfwee(opts);
}

/* gadget awwoc_inst */
static stwuct usb_function_instance *f_midi2_awwoc_inst(void)
{
	stwuct f_midi2_opts *opts;
	stwuct f_midi2_ep_opts *ep_opts;
	stwuct f_midi2_bwock_opts *bwock_opts;
	int wet;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = f_midi2_fwee_inst;
	opts->info.pwocess_ump = twue;
	opts->info.static_bwock = twue;
	opts->info.num_weqs = 32;
	opts->info.weq_buf_size = 512;

	/* cweate the defauwt ep */
	wet = f_midi2_ep_opts_cweate(opts, 0, &ep_opts);
	if (wet) {
		kfwee(opts);
		wetuwn EWW_PTW(wet);
	}

	/* cweate the defauwt bwock */
	wet = f_midi2_bwock_opts_cweate(ep_opts, 0, &bwock_opts);
	if (wet) {
		kfwee(ep_opts);
		kfwee(opts);
		wetuwn EWW_PTW(wet);
	}

	/* set up the defauwt MIDI1 (that is mandatowy) */
	bwock_opts->info.midi1_num_gwoups = 1;

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
				    &f_midi2_func_type);

	config_gwoup_init_type_name(&ep_opts->gwoup, "ep.0",
				    &f_midi2_ep_type);
	configfs_add_defauwt_gwoup(&ep_opts->gwoup, &opts->func_inst.gwoup);

	config_gwoup_init_type_name(&bwock_opts->gwoup, "bwock.0",
				    &f_midi2_bwock_type);
	configfs_add_defauwt_gwoup(&bwock_opts->gwoup, &ep_opts->gwoup);

	wetuwn &opts->func_inst;
}

static void do_f_midi2_fwee(stwuct f_midi2 *midi2, stwuct f_midi2_opts *opts)
{
	mutex_wock(&opts->wock);
	--opts->wefcnt;
	mutex_unwock(&opts->wock);
	kfwee(midi2->stwing_defs);
	kfwee(midi2);
}

static void f_midi2_fwee(stwuct usb_function *f)
{
	do_f_midi2_fwee(func_to_midi2(f),
			containew_of(f->fi, stwuct f_midi2_opts, func_inst));
}

/* vewify the pawametews set up via configfs;
 * wetuwn the numbew of EPs ow a negative ewwow
 */
static int vewify_pawametews(stwuct f_midi2_opts *opts)
{
	int i, j, num_eps, num_bwks;
	stwuct f_midi2_ep_info *ep;
	stwuct f_midi2_bwock_info *bp;

	fow (num_eps = 0; num_eps < MAX_UMP_EPS && opts->eps[num_eps];
	     num_eps++)
		;
	if (!num_eps) {
		pw_eww("f_midi2: No EP is defined\n");
		wetuwn -EINVAW;
	}

	num_bwks = 0;
	fow (i = 0; i < num_eps; i++) {
		ep = &opts->eps[i]->info;
		if (!(ep->pwotocow_caps & ep->pwotocow)) {
			pw_eww("f_midi2: Invawid pwotocow 0x%x (caps 0x%x) fow EP %d\n",
			       ep->pwotocow, ep->pwotocow_caps, i);
			wetuwn -EINVAW;
		}

		fow (j = 0; j < SNDWV_UMP_MAX_BWOCKS && opts->eps[i]->bwks[j];
		     j++, num_bwks++) {
			bp = &opts->eps[i]->bwks[j]->info;
			if (bp->fiwst_gwoup + bp->num_gwoups > SNDWV_UMP_MAX_GWOUPS) {
				pw_eww("f_midi2: Invawid gwoup definitions fow bwock %d:%d\n",
				       i, j);
				wetuwn -EINVAW;
			}

			if (bp->midi1_num_gwoups) {
				if (bp->midi1_fiwst_gwoup < bp->fiwst_gwoup ||
				    bp->midi1_fiwst_gwoup + bp->midi1_num_gwoups >
				    bp->fiwst_gwoup + bp->num_gwoups) {
					pw_eww("f_midi2: Invawid MIDI1 gwoup definitions fow bwock %d:%d\n",
					       i, j);
					wetuwn -EINVAW;
				}
			}
		}
	}
	if (!num_bwks) {
		pw_eww("f_midi2: No bwock is defined\n");
		wetuwn -EINVAW;
	}

	wetuwn num_eps;
}

/* fiww mapping between MIDI 1.0 cabwe and UMP EP/gwoup */
static void fiww_midi1_cabwe_mapping(stwuct f_midi2 *midi2,
				     stwuct f_midi2_ep *ep,
				     int bwk)
{
	const stwuct f_midi2_bwock_info *binfo = &ep->bwks[bwk].info;
	stwuct midi1_cabwe_mapping *map;
	int i, gwoup;

	if (!binfo->midi1_num_gwoups)
		wetuwn;
	if (binfo->diwection != SNDWV_UMP_DIW_OUTPUT) {
		gwoup = binfo->midi1_fiwst_gwoup;
		map = midi2->in_cabwe_mapping + midi2->num_midi1_in;
		fow (i = 0; i < binfo->midi1_num_gwoups; i++, gwoup++, map++) {
			if (midi2->num_midi1_in >= MAX_CABWES)
				bweak;
			map->ep = ep;
			map->bwock = bwk;
			map->gwoup = gwoup;
			midi2->num_midi1_in++;
			/* stowe 1-based cabwe numbew */
			ep->in_gwoup_to_cabwe[gwoup] = midi2->num_midi1_in;
		}
	}

	if (binfo->diwection != SNDWV_UMP_DIW_INPUT) {
		gwoup = binfo->midi1_fiwst_gwoup;
		map = midi2->out_cabwe_mapping + midi2->num_midi1_out;
		fow (i = 0; i < binfo->midi1_num_gwoups; i++, gwoup++, map++) {
			if (midi2->num_midi1_out >= MAX_CABWES)
				bweak;
			map->ep = ep;
			map->bwock = bwk;
			map->gwoup = gwoup;
			midi2->num_midi1_out++;
		}
	}
}

/* gadget awwoc cawwback */
static stwuct usb_function *f_midi2_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_midi2 *midi2;
	stwuct f_midi2_opts *opts;
	stwuct f_midi2_ep *ep;
	stwuct f_midi2_bwock *bp;
	int i, num_eps, bwk;

	midi2 = kzawwoc(sizeof(*midi2), GFP_KEWNEW);
	if (!midi2)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_midi2_opts, func_inst);
	mutex_wock(&opts->wock);
	num_eps = vewify_pawametews(opts);
	if (num_eps < 0) {
		mutex_unwock(&opts->wock);
		kfwee(midi2);
		wetuwn EWW_PTW(num_eps);
	}
	++opts->wefcnt;
	mutex_unwock(&opts->wock);

	spin_wock_init(&midi2->queue_wock);

	midi2->func.name = "midi2_func";
	midi2->func.bind = f_midi2_bind;
	midi2->func.unbind = f_midi2_unbind;
	midi2->func.get_awt = f_midi2_get_awt;
	midi2->func.set_awt = f_midi2_set_awt;
	midi2->func.setup = f_midi2_setup;
	midi2->func.disabwe = f_midi2_disabwe;
	midi2->func.fwee_func = f_midi2_fwee;

	midi2->info = opts->info;
	midi2->num_eps = num_eps;

	fow (i = 0; i < num_eps; i++) {
		ep = &midi2->midi2_eps[i];
		ep->info = opts->eps[i]->info;
		ep->cawd = midi2;
		fow (bwk = 0; bwk < SNDWV_UMP_MAX_BWOCKS &&
			     opts->eps[i]->bwks[bwk]; bwk++) {
			bp = &ep->bwks[bwk];
			ep->num_bwks++;
			bp->info = opts->eps[i]->bwks[bwk]->info;
			bp->gtb_id = ++midi2->totaw_bwocks;
		}
	}

	midi2->stwing_defs = kcawwoc(midi2->totaw_bwocks + 1,
				     sizeof(*midi2->stwing_defs), GFP_KEWNEW);
	if (!midi2->stwing_defs) {
		do_f_midi2_fwee(midi2, opts);
		wetuwn EWW_PTW(-ENOMEM);
	}

	if (opts->info.iface_name && *opts->info.iface_name)
		midi2->stwing_defs[STW_IFACE].s = opts->info.iface_name;
	ewse
		midi2->stwing_defs[STW_IFACE].s = ump_ep_name(&midi2->midi2_eps[0]);

	fow (i = 0; i < midi2->num_eps; i++) {
		ep = &midi2->midi2_eps[i];
		fow (bwk = 0; bwk < ep->num_bwks; bwk++) {
			bp = &ep->bwks[bwk];
			midi2->stwing_defs[gtb_to_stw_id(bp->gtb_id)].s =
				ump_fb_name(&bp->info);

			fiww_midi1_cabwe_mapping(midi2, ep, bwk);
		}
	}

	if (!midi2->num_midi1_in && !midi2->num_midi1_out) {
		pw_eww("f_midi2: MIDI1 definition is missing\n");
		do_f_midi2_fwee(midi2, opts);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn &midi2->func;
}

DECWAWE_USB_FUNCTION_INIT(midi2, f_midi2_awwoc_inst, f_midi2_awwoc);

MODUWE_WICENSE("GPW");
