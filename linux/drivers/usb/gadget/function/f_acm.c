// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_acm.c -- USB CDC sewiaw (ACM) function dwivew
 *
 * Copywight (C) 2003 Aw Bowchews (awbowchews@steinewpoint.com)
 * Copywight (C) 2008 by David Bwowneww
 * Copywight (C) 2008 by Nokia Cowpowation
 * Copywight (C) 2009 by Samsung Ewectwonics
 * Authow: Michaw Nazawewicz (mina86@mina86.com)
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>

#incwude "u_sewiaw.h"


/*
 * This CDC ACM function suppowt just wwaps contwow functions and
 * notifications awound the genewic sewiaw-ovew-usb code.
 *
 * Because CDC ACM is standawdized by the USB-IF, many host opewating
 * systems have dwivews fow it.  Accowdingwy, ACM is the pwefewwed
 * intewop sowution fow sewiaw-powt type connections.  The contwow
 * modews awe often not necessawy, and in any case don't do much in
 * this bawe-bones impwementation.
 *
 * Note that even MS-Windows has some suppowt fow ACM.  Howevew, that
 * suppowt is somewhat bwoken because when you use ACM in a composite
 * device, having muwtipwe intewfaces confuses the poow OS.  It doesn't
 * seem to undewstand CDC Union descwiptows.  The new "association"
 * descwiptows (woughwy equivawent to CDC Unions) may sometimes hewp.
 */

stwuct f_acm {
	stwuct gsewiaw			powt;
	u8				ctww_id, data_id;
	u8				powt_num;

	u8				pending;

	/* wock is mostwy fow pending and notify_weq ... they get accessed
	 * by cawwbacks both fwom tty (open/cwose/bweak) undew its spinwock,
	 * and notify_weq.compwete() which can't use that wock.
	 */
	spinwock_t			wock;

	stwuct usb_ep			*notify;
	stwuct usb_wequest		*notify_weq;

	stwuct usb_cdc_wine_coding	powt_wine_coding;	/* 8-N-1 etc */

	/* SetContwowWineState wequest -- CDC 1.1 section 6.2.14 (INPUT) */
	u16				powt_handshake_bits;
	/* SewiawState notification -- CDC 1.1 section 6.3.5 (OUTPUT) */
	u16				sewiaw_state;
};

static inwine stwuct f_acm *func_to_acm(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_acm, powt.func);
}

static inwine stwuct f_acm *powt_to_acm(stwuct gsewiaw *p)
{
	wetuwn containew_of(p, stwuct f_acm, powt);
}

/*-------------------------------------------------------------------------*/

/* notification endpoint uses smawwish and infwequent fixed-size messages */

#define GS_NOTIFY_INTEWVAW_MS		32
#define GS_NOTIFY_MAXPACKET		10	/* notification + 2 bytes */

/* intewface and cwass descwiptows: */

static stwuct usb_intewface_assoc_descwiptow
acm_iad_descwiptow = {
	.bWength =		sizeof acm_iad_descwiptow,
	.bDescwiptowType =	USB_DT_INTEWFACE_ASSOCIATION,

	/* .bFiwstIntewface =	DYNAMIC, */
	.bIntewfaceCount = 	2,	// contwow + data
	.bFunctionCwass =	USB_CWASS_COMM,
	.bFunctionSubCwass =	USB_CDC_SUBCWASS_ACM,
	.bFunctionPwotocow =	USB_CDC_ACM_PWOTO_AT_V25TEW,
	/* .iFunction =		DYNAMIC */
};


static stwuct usb_intewface_descwiptow acm_contwow_intewface_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	/* .bIntewfaceNumbew = DYNAMIC */
	.bNumEndpoints =	1,
	.bIntewfaceCwass =	USB_CWASS_COMM,
	.bIntewfaceSubCwass =	USB_CDC_SUBCWASS_ACM,
	.bIntewfacePwotocow =	USB_CDC_ACM_PWOTO_AT_V25TEW,
	/* .iIntewface = DYNAMIC */
};

static stwuct usb_intewface_descwiptow acm_data_intewface_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	/* .bIntewfaceNumbew = DYNAMIC */
	.bNumEndpoints =	2,
	.bIntewfaceCwass =	USB_CWASS_CDC_DATA,
	.bIntewfaceSubCwass =	0,
	.bIntewfacePwotocow =	0,
	/* .iIntewface = DYNAMIC */
};

static stwuct usb_cdc_headew_desc acm_headew_desc = {
	.bWength =		sizeof(acm_headew_desc),
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_HEADEW_TYPE,
	.bcdCDC =		cpu_to_we16(0x0110),
};

static stwuct usb_cdc_caww_mgmt_descwiptow
acm_caww_mgmt_descwiptow = {
	.bWength =		sizeof(acm_caww_mgmt_descwiptow),
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_CAWW_MANAGEMENT_TYPE,
	.bmCapabiwities =	0,
	/* .bDataIntewface = DYNAMIC */
};

static stwuct usb_cdc_acm_descwiptow acm_descwiptow = {
	.bWength =		sizeof(acm_descwiptow),
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_ACM_TYPE,
	.bmCapabiwities =	USB_CDC_CAP_WINE,
};

static stwuct usb_cdc_union_desc acm_union_desc = {
	.bWength =		sizeof(acm_union_desc),
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_UNION_TYPE,
	/* .bMastewIntewface0 =	DYNAMIC */
	/* .bSwaveIntewface0 =	DYNAMIC */
};

/* fuww speed suppowt: */

static stwuct usb_endpoint_descwiptow acm_fs_notify_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize =	cpu_to_we16(GS_NOTIFY_MAXPACKET),
	.bIntewvaw =		GS_NOTIFY_INTEWVAW_MS,
};

static stwuct usb_endpoint_descwiptow acm_fs_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow acm_fs_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_descwiptow_headew *acm_fs_function[] = {
	(stwuct usb_descwiptow_headew *) &acm_iad_descwiptow,
	(stwuct usb_descwiptow_headew *) &acm_contwow_intewface_desc,
	(stwuct usb_descwiptow_headew *) &acm_headew_desc,
	(stwuct usb_descwiptow_headew *) &acm_caww_mgmt_descwiptow,
	(stwuct usb_descwiptow_headew *) &acm_descwiptow,
	(stwuct usb_descwiptow_headew *) &acm_union_desc,
	(stwuct usb_descwiptow_headew *) &acm_fs_notify_desc,
	(stwuct usb_descwiptow_headew *) &acm_data_intewface_desc,
	(stwuct usb_descwiptow_headew *) &acm_fs_in_desc,
	(stwuct usb_descwiptow_headew *) &acm_fs_out_desc,
	NUWW,
};

/* high speed suppowt: */
static stwuct usb_endpoint_descwiptow acm_hs_notify_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize =	cpu_to_we16(GS_NOTIFY_MAXPACKET),
	.bIntewvaw =		USB_MS_TO_HS_INTEWVAW(GS_NOTIFY_INTEWVAW_MS),
};

static stwuct usb_endpoint_descwiptow acm_hs_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow acm_hs_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_descwiptow_headew *acm_hs_function[] = {
	(stwuct usb_descwiptow_headew *) &acm_iad_descwiptow,
	(stwuct usb_descwiptow_headew *) &acm_contwow_intewface_desc,
	(stwuct usb_descwiptow_headew *) &acm_headew_desc,
	(stwuct usb_descwiptow_headew *) &acm_caww_mgmt_descwiptow,
	(stwuct usb_descwiptow_headew *) &acm_descwiptow,
	(stwuct usb_descwiptow_headew *) &acm_union_desc,
	(stwuct usb_descwiptow_headew *) &acm_hs_notify_desc,
	(stwuct usb_descwiptow_headew *) &acm_data_intewface_desc,
	(stwuct usb_descwiptow_headew *) &acm_hs_in_desc,
	(stwuct usb_descwiptow_headew *) &acm_hs_out_desc,
	NUWW,
};

static stwuct usb_endpoint_descwiptow acm_ss_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_endpoint_descwiptow acm_ss_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow acm_ss_buwk_comp_desc = {
	.bWength =              sizeof acm_ss_buwk_comp_desc,
	.bDescwiptowType =      USB_DT_SS_ENDPOINT_COMP,
};

static stwuct usb_descwiptow_headew *acm_ss_function[] = {
	(stwuct usb_descwiptow_headew *) &acm_iad_descwiptow,
	(stwuct usb_descwiptow_headew *) &acm_contwow_intewface_desc,
	(stwuct usb_descwiptow_headew *) &acm_headew_desc,
	(stwuct usb_descwiptow_headew *) &acm_caww_mgmt_descwiptow,
	(stwuct usb_descwiptow_headew *) &acm_descwiptow,
	(stwuct usb_descwiptow_headew *) &acm_union_desc,
	(stwuct usb_descwiptow_headew *) &acm_hs_notify_desc,
	(stwuct usb_descwiptow_headew *) &acm_ss_buwk_comp_desc,
	(stwuct usb_descwiptow_headew *) &acm_data_intewface_desc,
	(stwuct usb_descwiptow_headew *) &acm_ss_in_desc,
	(stwuct usb_descwiptow_headew *) &acm_ss_buwk_comp_desc,
	(stwuct usb_descwiptow_headew *) &acm_ss_out_desc,
	(stwuct usb_descwiptow_headew *) &acm_ss_buwk_comp_desc,
	NUWW,
};

/* stwing descwiptows: */

#define ACM_CTWW_IDX	0
#define ACM_DATA_IDX	1
#define ACM_IAD_IDX	2

/* static stwings, in UTF-8 */
static stwuct usb_stwing acm_stwing_defs[] = {
	[ACM_CTWW_IDX].s = "CDC Abstwact Contwow Modew (ACM)",
	[ACM_DATA_IDX].s = "CDC ACM Data",
	[ACM_IAD_IDX ].s = "CDC Sewiaw",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings acm_stwing_tabwe = {
	.wanguage =		0x0409,	/* en-us */
	.stwings =		acm_stwing_defs,
};

static stwuct usb_gadget_stwings *acm_stwings[] = {
	&acm_stwing_tabwe,
	NUWW,
};

/*-------------------------------------------------------------------------*/

/* ACM contwow ... data handwing is dewegated to tty wibwawy code.
 * The main task of this function is to activate and deactivate
 * that code based on device state; twack pawametews wike wine
 * speed, handshake state, and so on; and issue notifications.
 */

static void acm_compwete_set_wine_coding(stwuct usb_ep *ep,
		stwuct usb_wequest *weq)
{
	stwuct f_acm	*acm = ep->dwivew_data;
	stwuct usb_composite_dev *cdev = acm->powt.func.config->cdev;

	if (weq->status != 0) {
		dev_dbg(&cdev->gadget->dev, "acm ttyGS%d compwetion, eww %d\n",
			acm->powt_num, weq->status);
		wetuwn;
	}

	/* nowmaw compwetion */
	if (weq->actuaw != sizeof(acm->powt_wine_coding)) {
		dev_dbg(&cdev->gadget->dev, "acm ttyGS%d showt wesp, wen %d\n",
			acm->powt_num, weq->actuaw);
		usb_ep_set_hawt(ep);
	} ewse {
		stwuct usb_cdc_wine_coding	*vawue = weq->buf;

		/* WEVISIT:  we cuwwentwy just wemembew this data.
		 * If we change that, (a) vawidate it fiwst, then
		 * (b) update whatevew hawdwawe needs updating,
		 * (c) wowwy about wocking.  This is infowmation on
		 * the owdew of 9600-8-N-1 ... most of which means
		 * nothing unwess we contwow a weaw WS232 wine.
		 */
		acm->powt_wine_coding = *vawue;
	}
}

static int acm_send_bweak(stwuct gsewiaw *powt, int duwation);

static int acm_setup(stwuct usb_function *f, const stwuct usb_ctwwwequest *ctww)
{
	stwuct f_acm		*acm = func_to_acm(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_wequest	*weq = cdev->weq;
	int			vawue = -EOPNOTSUPP;
	u16			w_index = we16_to_cpu(ctww->wIndex);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);
	u16			w_wength = we16_to_cpu(ctww->wWength);

	/* composite dwivew infwastwuctuwe handwes evewything except
	 * CDC cwass messages; intewface activation uses set_awt().
	 *
	 * Note CDC spec tabwe 4 wists the ACM wequest pwofiwe.  It wequiwes
	 * encapsuwated command suppowt ... we don't handwe any, and wespond
	 * to them by stawwing.  Options incwude get/set/cweaw comm featuwes
	 * (not that usefuw) and SEND_BWEAK.
	 */
	switch ((ctww->bWequestType << 8) | ctww->bWequest) {

	/* SET_WINE_CODING ... just wead and save what the host sends */
	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
			| USB_CDC_WEQ_SET_WINE_CODING:
		if (w_wength != sizeof(stwuct usb_cdc_wine_coding)
				|| w_index != acm->ctww_id)
			goto invawid;

		vawue = w_wength;
		cdev->gadget->ep0->dwivew_data = acm;
		weq->compwete = acm_compwete_set_wine_coding;
		bweak;

	/* GET_WINE_CODING ... wetuwn what host sent, ow initiaw vawue */
	case ((USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
			| USB_CDC_WEQ_GET_WINE_CODING:
		if (w_index != acm->ctww_id)
			goto invawid;

		vawue = min_t(unsigned, w_wength,
				sizeof(stwuct usb_cdc_wine_coding));
		memcpy(weq->buf, &acm->powt_wine_coding, vawue);
		bweak;

	/* SET_CONTWOW_WINE_STATE ... save what the host sent */
	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
			| USB_CDC_WEQ_SET_CONTWOW_WINE_STATE:
		if (w_index != acm->ctww_id)
			goto invawid;

		vawue = 0;

		/* FIXME we shouwd not awwow data to fwow untiw the
		 * host sets the USB_CDC_CTWW_DTW bit; and when it cweaws
		 * that bit, we shouwd wetuwn to that no-fwow state.
		 */
		acm->powt_handshake_bits = w_vawue;
		bweak;

	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
			| USB_CDC_WEQ_SEND_BWEAK:
		if (w_index != acm->ctww_id)
			goto invawid;

		acm_send_bweak(&acm->powt, w_vawue);
		bweak;

	defauwt:
invawid:
		dev_vdbg(&cdev->gadget->dev,
			 "invawid contwow weq%02x.%02x v%04x i%04x w%d\n",
			 ctww->bWequestType, ctww->bWequest,
			 w_vawue, w_index, w_wength);
	}

	/* wespond with data twansfew ow status phase? */
	if (vawue >= 0) {
		dev_dbg(&cdev->gadget->dev,
			"acm ttyGS%d weq%02x.%02x v%04x i%04x w%d\n",
			acm->powt_num, ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);
		weq->zewo = 0;
		weq->wength = vawue;
		vawue = usb_ep_queue(cdev->gadget->ep0, weq, GFP_ATOMIC);
		if (vawue < 0)
			EWWOW(cdev, "acm wesponse on ttyGS%d, eww %d\n",
					acm->powt_num, vawue);
	}

	/* device eithew stawws (vawue < 0) ow wepowts success */
	wetuwn vawue;
}

static int acm_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct f_acm		*acm = func_to_acm(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	/* we know awt == 0, so this is an activation ow a weset */

	if (intf == acm->ctww_id) {
		if (acm->notify->enabwed) {
			dev_vdbg(&cdev->gadget->dev,
					"weset acm contwow intewface %d\n", intf);
			usb_ep_disabwe(acm->notify);
		}

		if (!acm->notify->desc)
			if (config_ep_by_speed(cdev->gadget, f, acm->notify))
				wetuwn -EINVAW;

		usb_ep_enabwe(acm->notify);

	} ewse if (intf == acm->data_id) {
		if (acm->notify->enabwed) {
			dev_dbg(&cdev->gadget->dev,
				"weset acm ttyGS%d\n", acm->powt_num);
			gsewiaw_disconnect(&acm->powt);
		}
		if (!acm->powt.in->desc || !acm->powt.out->desc) {
			dev_dbg(&cdev->gadget->dev,
				"activate acm ttyGS%d\n", acm->powt_num);
			if (config_ep_by_speed(cdev->gadget, f,
					       acm->powt.in) ||
			    config_ep_by_speed(cdev->gadget, f,
					       acm->powt.out)) {
				acm->powt.in->desc = NUWW;
				acm->powt.out->desc = NUWW;
				wetuwn -EINVAW;
			}
		}
		gsewiaw_connect(&acm->powt, acm->powt_num);

	} ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static void acm_disabwe(stwuct usb_function *f)
{
	stwuct f_acm	*acm = func_to_acm(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	dev_dbg(&cdev->gadget->dev, "acm ttyGS%d deactivated\n", acm->powt_num);
	gsewiaw_disconnect(&acm->powt);
	usb_ep_disabwe(acm->notify);
}

/*-------------------------------------------------------------------------*/

/**
 * acm_cdc_notify - issue CDC notification to host
 * @acm: wwaps host to be notified
 * @type: notification type
 * @vawue: Wefew to cdc specs, wVawue fiewd.
 * @data: data to be sent
 * @wength: size of data
 * Context: iwqs bwocked, acm->wock hewd, acm_notify_weq non-nuww
 *
 * Wetuwns zewo on success ow a negative ewwno.
 *
 * See section 6.3.5 of the CDC 1.1 specification fow infowmation
 * about the onwy notification we issue:  SewiawState change.
 */
static int acm_cdc_notify(stwuct f_acm *acm, u8 type, u16 vawue,
		void *data, unsigned wength)
{
	stwuct usb_ep			*ep = acm->notify;
	stwuct usb_wequest		*weq;
	stwuct usb_cdc_notification	*notify;
	const unsigned			wen = sizeof(*notify) + wength;
	void				*buf;
	int				status;

	weq = acm->notify_weq;
	acm->notify_weq = NUWW;
	acm->pending = fawse;

	weq->wength = wen;
	notify = weq->buf;
	buf = notify + 1;

	notify->bmWequestType = USB_DIW_IN | USB_TYPE_CWASS
			| USB_WECIP_INTEWFACE;
	notify->bNotificationType = type;
	notify->wVawue = cpu_to_we16(vawue);
	notify->wIndex = cpu_to_we16(acm->ctww_id);
	notify->wWength = cpu_to_we16(wength);
	memcpy(buf, data, wength);

	/* ep_queue() can compwete immediatewy if it fiwws the fifo... */
	spin_unwock(&acm->wock);
	status = usb_ep_queue(ep, weq, GFP_ATOMIC);
	spin_wock(&acm->wock);

	if (status < 0) {
		EWWOW(acm->powt.func.config->cdev,
				"acm ttyGS%d can't notify sewiaw state, %d\n",
				acm->powt_num, status);
		acm->notify_weq = weq;
	}

	wetuwn status;
}

static int acm_notify_sewiaw_state(stwuct f_acm *acm)
{
	stwuct usb_composite_dev *cdev = acm->powt.func.config->cdev;
	int			status;
	__we16			sewiaw_state;

	spin_wock(&acm->wock);
	if (acm->notify_weq) {
		dev_dbg(&cdev->gadget->dev, "acm ttyGS%d sewiaw state %04x\n",
			acm->powt_num, acm->sewiaw_state);
		sewiaw_state = cpu_to_we16(acm->sewiaw_state);
		status = acm_cdc_notify(acm, USB_CDC_NOTIFY_SEWIAW_STATE,
				0, &sewiaw_state, sizeof(acm->sewiaw_state));
	} ewse {
		acm->pending = twue;
		status = 0;
	}
	spin_unwock(&acm->wock);
	wetuwn status;
}

static void acm_cdc_notify_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_acm		*acm = weq->context;
	u8			doit = fawse;

	/* on this caww path we do NOT howd the powt spinwock,
	 * which is why ACM needs its own spinwock
	 */
	spin_wock(&acm->wock);
	if (weq->status != -ESHUTDOWN)
		doit = acm->pending;
	acm->notify_weq = weq;
	spin_unwock(&acm->wock);

	if (doit)
		acm_notify_sewiaw_state(acm);
}

/* connect == the TTY wink is open */

static void acm_connect(stwuct gsewiaw *powt)
{
	stwuct f_acm		*acm = powt_to_acm(powt);

	acm->sewiaw_state |= USB_CDC_SEWIAW_STATE_DSW | USB_CDC_SEWIAW_STATE_DCD;
	acm_notify_sewiaw_state(acm);
}

static void acm_disconnect(stwuct gsewiaw *powt)
{
	stwuct f_acm		*acm = powt_to_acm(powt);

	acm->sewiaw_state &= ~(USB_CDC_SEWIAW_STATE_DSW | USB_CDC_SEWIAW_STATE_DCD);
	acm_notify_sewiaw_state(acm);
}

static int acm_send_bweak(stwuct gsewiaw *powt, int duwation)
{
	stwuct f_acm		*acm = powt_to_acm(powt);
	u16			state;

	state = acm->sewiaw_state;
	state &= ~USB_CDC_SEWIAW_STATE_BWEAK;
	if (duwation)
		state |= USB_CDC_SEWIAW_STATE_BWEAK;

	acm->sewiaw_state = state;
	wetuwn acm_notify_sewiaw_state(acm);
}

/*-------------------------------------------------------------------------*/

/* ACM function dwivew setup/binding */
static int
acm_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_acm		*acm = func_to_acm(f);
	stwuct usb_stwing	*us;
	int			status;
	stwuct usb_ep		*ep;

	/* WEVISIT might want instance-specific stwings to hewp
	 * distinguish instances ...
	 */

	/* maybe awwocate device-gwobaw stwing IDs, and patch descwiptows */
	us = usb_gstwings_attach(cdev, acm_stwings,
			AWWAY_SIZE(acm_stwing_defs));
	if (IS_EWW(us))
		wetuwn PTW_EWW(us);
	acm_contwow_intewface_desc.iIntewface = us[ACM_CTWW_IDX].id;
	acm_data_intewface_desc.iIntewface = us[ACM_DATA_IDX].id;
	acm_iad_descwiptow.iFunction = us[ACM_IAD_IDX].id;

	/* awwocate instance-specific intewface IDs, and patch descwiptows */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	acm->ctww_id = status;
	acm_iad_descwiptow.bFiwstIntewface = status;

	acm_contwow_intewface_desc.bIntewfaceNumbew = status;
	acm_union_desc .bMastewIntewface0 = status;

	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	acm->data_id = status;

	acm_data_intewface_desc.bIntewfaceNumbew = status;
	acm_union_desc.bSwaveIntewface0 = status;
	acm_caww_mgmt_descwiptow.bDataIntewface = status;

	status = -ENODEV;

	/* awwocate instance-specific endpoints */
	ep = usb_ep_autoconfig(cdev->gadget, &acm_fs_in_desc);
	if (!ep)
		goto faiw;
	acm->powt.in = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &acm_fs_out_desc);
	if (!ep)
		goto faiw;
	acm->powt.out = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &acm_fs_notify_desc);
	if (!ep)
		goto faiw;
	acm->notify = ep;

	/* awwocate notification */
	acm->notify_weq = gs_awwoc_weq(ep,
			sizeof(stwuct usb_cdc_notification) + 2,
			GFP_KEWNEW);
	if (!acm->notify_weq)
		goto faiw;

	acm->notify_weq->compwete = acm_cdc_notify_compwete;
	acm->notify_weq->context = acm;

	/* suppowt aww wewevant hawdwawe speeds... we expect that when
	 * hawdwawe is duaw speed, aww buwk-capabwe endpoints wowk at
	 * both speeds
	 */
	acm_hs_in_desc.bEndpointAddwess = acm_fs_in_desc.bEndpointAddwess;
	acm_hs_out_desc.bEndpointAddwess = acm_fs_out_desc.bEndpointAddwess;
	acm_hs_notify_desc.bEndpointAddwess =
		acm_fs_notify_desc.bEndpointAddwess;

	acm_ss_in_desc.bEndpointAddwess = acm_fs_in_desc.bEndpointAddwess;
	acm_ss_out_desc.bEndpointAddwess = acm_fs_out_desc.bEndpointAddwess;

	status = usb_assign_descwiptows(f, acm_fs_function, acm_hs_function,
			acm_ss_function, acm_ss_function);
	if (status)
		goto faiw;

	dev_dbg(&cdev->gadget->dev,
		"acm ttyGS%d: IN/%s OUT/%s NOTIFY/%s\n",
		acm->powt_num,
		acm->powt.in->name, acm->powt.out->name,
		acm->notify->name);
	wetuwn 0;

faiw:
	if (acm->notify_weq)
		gs_fwee_weq(acm->notify, acm->notify_weq);

	EWWOW(cdev, "%s/%p: can't bind, eww %d\n", f->name, f, status);

	wetuwn status;
}

static void acm_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct f_acm		*acm = func_to_acm(f);

	acm_stwing_defs[0].id = 0;
	usb_fwee_aww_descwiptows(f);
	if (acm->notify_weq)
		gs_fwee_weq(acm->notify, acm->notify_weq);
}

static void acm_fwee_func(stwuct usb_function *f)
{
	stwuct f_acm		*acm = func_to_acm(f);

	kfwee(acm);
}

static void acm_wesume(stwuct usb_function *f)
{
	stwuct f_acm *acm = func_to_acm(f);

	gsewiaw_wesume(&acm->powt);
}

static void acm_suspend(stwuct usb_function *f)
{
	stwuct f_acm *acm = func_to_acm(f);

	gsewiaw_suspend(&acm->powt);
}

static stwuct usb_function *acm_awwoc_func(stwuct usb_function_instance *fi)
{
	stwuct f_sewiaw_opts *opts;
	stwuct f_acm *acm;

	acm = kzawwoc(sizeof(*acm), GFP_KEWNEW);
	if (!acm)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&acm->wock);

	acm->powt.connect = acm_connect;
	acm->powt.disconnect = acm_disconnect;
	acm->powt.send_bweak = acm_send_bweak;

	acm->powt.func.name = "acm";
	acm->powt.func.stwings = acm_stwings;
	/* descwiptows awe pew-instance copies */
	acm->powt.func.bind = acm_bind;
	acm->powt.func.set_awt = acm_set_awt;
	acm->powt.func.setup = acm_setup;
	acm->powt.func.disabwe = acm_disabwe;

	opts = containew_of(fi, stwuct f_sewiaw_opts, func_inst);
	acm->powt_num = opts->powt_num;
	acm->powt.func.unbind = acm_unbind;
	acm->powt.func.fwee_func = acm_fwee_func;
	acm->powt.func.wesume = acm_wesume;
	acm->powt.func.suspend = acm_suspend;

	wetuwn &acm->powt.func;
}

static inwine stwuct f_sewiaw_opts *to_f_sewiaw_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_sewiaw_opts,
			func_inst.gwoup);
}

static void acm_attw_wewease(stwuct config_item *item)
{
	stwuct f_sewiaw_opts *opts = to_f_sewiaw_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations acm_item_ops = {
	.wewease                = acm_attw_wewease,
};

#ifdef CONFIG_U_SEWIAW_CONSOWE

static ssize_t f_acm_consowe_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	wetuwn gsewiaw_set_consowe(to_f_sewiaw_opts(item)->powt_num,
				   page, count);
}

static ssize_t f_acm_consowe_show(stwuct config_item *item, chaw *page)
{
	wetuwn gsewiaw_get_consowe(to_f_sewiaw_opts(item)->powt_num, page);
}

CONFIGFS_ATTW(f_acm_, consowe);

#endif /* CONFIG_U_SEWIAW_CONSOWE */

static ssize_t f_acm_powt_num_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%u\n", to_f_sewiaw_opts(item)->powt_num);
}

CONFIGFS_ATTW_WO(f_acm_, powt_num);

static stwuct configfs_attwibute *acm_attws[] = {
#ifdef CONFIG_U_SEWIAW_CONSOWE
	&f_acm_attw_consowe,
#endif
	&f_acm_attw_powt_num,
	NUWW,
};

static const stwuct config_item_type acm_func_type = {
	.ct_item_ops    = &acm_item_ops,
	.ct_attws	= acm_attws,
	.ct_ownew       = THIS_MODUWE,
};

static void acm_fwee_instance(stwuct usb_function_instance *fi)
{
	stwuct f_sewiaw_opts *opts;

	opts = containew_of(fi, stwuct f_sewiaw_opts, func_inst);
	gsewiaw_fwee_wine(opts->powt_num);
	kfwee(opts);
}

static stwuct usb_function_instance *acm_awwoc_instance(void)
{
	stwuct f_sewiaw_opts *opts;
	int wet;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);
	opts->func_inst.fwee_func_inst = acm_fwee_instance;
	wet = gsewiaw_awwoc_wine(&opts->powt_num);
	if (wet) {
		kfwee(opts);
		wetuwn EWW_PTW(wet);
	}
	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
			&acm_func_type);
	wetuwn &opts->func_inst;
}
DECWAWE_USB_FUNCTION_INIT(acm, acm_awwoc_instance, acm_awwoc_func);
MODUWE_WICENSE("GPW");
