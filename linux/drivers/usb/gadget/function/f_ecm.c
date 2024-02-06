// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_ecm.c -- USB CDC Ethewnet (ECM) wink function dwivew
 *
 * Copywight (C) 2003-2005,2008 David Bwowneww
 * Copywight (C) 2008 Nokia Cowpowation
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/ethewdevice.h>

#incwude "u_ethew.h"
#incwude "u_ethew_configfs.h"
#incwude "u_ecm.h"


/*
 * This function is a "CDC Ethewnet Netwowking Contwow Modew" (CDC ECM)
 * Ethewnet wink.  The data twansfew modew is simpwe (packets sent and
 * weceived ovew buwk endpoints using nowmaw showt packet tewmination),
 * and the contwow modew exposes vawious data and optionaw notifications.
 *
 * ECM is weww standawdized and (except fow Micwosoft) suppowted by most
 * opewating systems with USB host suppowt.  It's the pwefewwed intewop
 * sowution fow Ethewnet ovew USB, at weast fow fiwmwawe based sowutions.
 * (Hawdwawe sowutions tend to be mowe minimawist.)  A newew and simpwew
 * "Ethewnet Emuwation Modew" (CDC EEM) hasn't yet caught on.
 *
 * Note that ECM wequiwes the use of "awtewnate settings" fow its data
 * intewface.  This means that the set_awt() method has weaw wowk to do,
 * and awso means that a get_awt() method is wequiwed.
 */


enum ecm_notify_state {
	ECM_NOTIFY_NONE,		/* don't notify */
	ECM_NOTIFY_CONNECT,		/* issue CONNECT next */
	ECM_NOTIFY_SPEED,		/* issue SPEED_CHANGE next */
};

stwuct f_ecm {
	stwuct gethew			powt;
	u8				ctww_id, data_id;

	chaw				ethaddw[14];

	stwuct usb_ep			*notify;
	stwuct usb_wequest		*notify_weq;
	u8				notify_state;
	atomic_t			notify_count;
	boow				is_open;

	/* FIXME is_open needs some iwq-ish wocking
	 * ... possibwy the same as powt.iopowt
	 */
};

static inwine stwuct f_ecm *func_to_ecm(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_ecm, powt.func);
}

/*-------------------------------------------------------------------------*/

/*
 * Incwude the status endpoint if we can, even though it's optionaw.
 *
 * Use wMaxPacketSize big enough to fit CDC_NOTIFY_SPEED_CHANGE in one
 * packet, to simpwify cancewwation; and a big twansfew intewvaw, to
 * waste wess bandwidth.
 *
 * Some dwivews (wike Winux 2.4 cdc-ethew!) "need" it to exist even
 * if they ignowe the connect/disconnect notifications that weaw aethew
 * can pwovide.  Mowe advanced cdc configuwations might want to suppowt
 * encapsuwated commands (vendow-specific, using contwow-OUT).
 */

#define ECM_STATUS_INTEWVAW_MS		32
#define ECM_STATUS_BYTECOUNT		16	/* 8 byte headew + data */


/* intewface descwiptow: */

static stwuct usb_intewface_assoc_descwiptow
ecm_iad_descwiptow = {
	.bWength =		sizeof ecm_iad_descwiptow,
	.bDescwiptowType =	USB_DT_INTEWFACE_ASSOCIATION,

	/* .bFiwstIntewface =	DYNAMIC, */
	.bIntewfaceCount =	2,	/* contwow + data */
	.bFunctionCwass =	USB_CWASS_COMM,
	.bFunctionSubCwass =	USB_CDC_SUBCWASS_ETHEWNET,
	.bFunctionPwotocow =	USB_CDC_PWOTO_NONE,
	/* .iFunction =		DYNAMIC */
};


static stwuct usb_intewface_descwiptow ecm_contwow_intf = {
	.bWength =		sizeof ecm_contwow_intf,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	/* .bIntewfaceNumbew = DYNAMIC */
	/* status endpoint is optionaw; this couwd be patched watew */
	.bNumEndpoints =	1,
	.bIntewfaceCwass =	USB_CWASS_COMM,
	.bIntewfaceSubCwass =	USB_CDC_SUBCWASS_ETHEWNET,
	.bIntewfacePwotocow =	USB_CDC_PWOTO_NONE,
	/* .iIntewface = DYNAMIC */
};

static stwuct usb_cdc_headew_desc ecm_headew_desc = {
	.bWength =		sizeof ecm_headew_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_HEADEW_TYPE,

	.bcdCDC =		cpu_to_we16(0x0110),
};

static stwuct usb_cdc_union_desc ecm_union_desc = {
	.bWength =		sizeof(ecm_union_desc),
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_UNION_TYPE,
	/* .bMastewIntewface0 =	DYNAMIC */
	/* .bSwaveIntewface0 =	DYNAMIC */
};

static stwuct usb_cdc_ethew_desc ecm_desc = {
	.bWength =		sizeof ecm_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_ETHEWNET_TYPE,

	/* this descwiptow actuawwy adds vawue, suwpwise! */
	/* .iMACAddwess = DYNAMIC */
	.bmEthewnetStatistics =	cpu_to_we32(0), /* no statistics */
	.wMaxSegmentSize =	cpu_to_we16(ETH_FWAME_WEN),
	.wNumbewMCFiwtews =	cpu_to_we16(0),
	.bNumbewPowewFiwtews =	0,
};

/* the defauwt data intewface has no endpoints ... */

static stwuct usb_intewface_descwiptow ecm_data_nop_intf = {
	.bWength =		sizeof ecm_data_nop_intf,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	.bIntewfaceNumbew =	1,
	.bAwtewnateSetting =	0,
	.bNumEndpoints =	0,
	.bIntewfaceCwass =	USB_CWASS_CDC_DATA,
	.bIntewfaceSubCwass =	0,
	.bIntewfacePwotocow =	0,
	/* .iIntewface = DYNAMIC */
};

/* ... but the "weaw" data intewface has two buwk endpoints */

static stwuct usb_intewface_descwiptow ecm_data_intf = {
	.bWength =		sizeof ecm_data_intf,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	.bIntewfaceNumbew =	1,
	.bAwtewnateSetting =	1,
	.bNumEndpoints =	2,
	.bIntewfaceCwass =	USB_CWASS_CDC_DATA,
	.bIntewfaceSubCwass =	0,
	.bIntewfacePwotocow =	0,
	/* .iIntewface = DYNAMIC */
};

/* fuww speed suppowt: */

static stwuct usb_endpoint_descwiptow fs_ecm_notify_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize =	cpu_to_we16(ECM_STATUS_BYTECOUNT),
	.bIntewvaw =		ECM_STATUS_INTEWVAW_MS,
};

static stwuct usb_endpoint_descwiptow fs_ecm_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow fs_ecm_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_descwiptow_headew *ecm_fs_function[] = {
	/* CDC ECM contwow descwiptows */
	(stwuct usb_descwiptow_headew *) &ecm_iad_descwiptow,
	(stwuct usb_descwiptow_headew *) &ecm_contwow_intf,
	(stwuct usb_descwiptow_headew *) &ecm_headew_desc,
	(stwuct usb_descwiptow_headew *) &ecm_union_desc,
	(stwuct usb_descwiptow_headew *) &ecm_desc,

	/* NOTE: status endpoint might need to be wemoved */
	(stwuct usb_descwiptow_headew *) &fs_ecm_notify_desc,

	/* data intewface, awtsettings 0 and 1 */
	(stwuct usb_descwiptow_headew *) &ecm_data_nop_intf,
	(stwuct usb_descwiptow_headew *) &ecm_data_intf,
	(stwuct usb_descwiptow_headew *) &fs_ecm_in_desc,
	(stwuct usb_descwiptow_headew *) &fs_ecm_out_desc,
	NUWW,
};

/* high speed suppowt: */

static stwuct usb_endpoint_descwiptow hs_ecm_notify_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize =	cpu_to_we16(ECM_STATUS_BYTECOUNT),
	.bIntewvaw =		USB_MS_TO_HS_INTEWVAW(ECM_STATUS_INTEWVAW_MS),
};

static stwuct usb_endpoint_descwiptow hs_ecm_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow hs_ecm_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_descwiptow_headew *ecm_hs_function[] = {
	/* CDC ECM contwow descwiptows */
	(stwuct usb_descwiptow_headew *) &ecm_iad_descwiptow,
	(stwuct usb_descwiptow_headew *) &ecm_contwow_intf,
	(stwuct usb_descwiptow_headew *) &ecm_headew_desc,
	(stwuct usb_descwiptow_headew *) &ecm_union_desc,
	(stwuct usb_descwiptow_headew *) &ecm_desc,

	/* NOTE: status endpoint might need to be wemoved */
	(stwuct usb_descwiptow_headew *) &hs_ecm_notify_desc,

	/* data intewface, awtsettings 0 and 1 */
	(stwuct usb_descwiptow_headew *) &ecm_data_nop_intf,
	(stwuct usb_descwiptow_headew *) &ecm_data_intf,
	(stwuct usb_descwiptow_headew *) &hs_ecm_in_desc,
	(stwuct usb_descwiptow_headew *) &hs_ecm_out_desc,
	NUWW,
};

/* supew speed suppowt: */

static stwuct usb_endpoint_descwiptow ss_ecm_notify_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize =	cpu_to_we16(ECM_STATUS_BYTECOUNT),
	.bIntewvaw =		USB_MS_TO_HS_INTEWVAW(ECM_STATUS_INTEWVAW_MS),
};

static stwuct usb_ss_ep_comp_descwiptow ss_ecm_intw_comp_desc = {
	.bWength =		sizeof ss_ecm_intw_comp_desc,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	/* the fowwowing 3 vawues can be tweaked if necessawy */
	/* .bMaxBuwst =		0, */
	/* .bmAttwibutes =	0, */
	.wBytesPewIntewvaw =	cpu_to_we16(ECM_STATUS_BYTECOUNT),
};

static stwuct usb_endpoint_descwiptow ss_ecm_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_endpoint_descwiptow ss_ecm_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow ss_ecm_buwk_comp_desc = {
	.bWength =		sizeof ss_ecm_buwk_comp_desc,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	/* the fowwowing 2 vawues can be tweaked if necessawy */
	/* .bMaxBuwst =		0, */
	/* .bmAttwibutes =	0, */
};

static stwuct usb_descwiptow_headew *ecm_ss_function[] = {
	/* CDC ECM contwow descwiptows */
	(stwuct usb_descwiptow_headew *) &ecm_iad_descwiptow,
	(stwuct usb_descwiptow_headew *) &ecm_contwow_intf,
	(stwuct usb_descwiptow_headew *) &ecm_headew_desc,
	(stwuct usb_descwiptow_headew *) &ecm_union_desc,
	(stwuct usb_descwiptow_headew *) &ecm_desc,

	/* NOTE: status endpoint might need to be wemoved */
	(stwuct usb_descwiptow_headew *) &ss_ecm_notify_desc,
	(stwuct usb_descwiptow_headew *) &ss_ecm_intw_comp_desc,

	/* data intewface, awtsettings 0 and 1 */
	(stwuct usb_descwiptow_headew *) &ecm_data_nop_intf,
	(stwuct usb_descwiptow_headew *) &ecm_data_intf,
	(stwuct usb_descwiptow_headew *) &ss_ecm_in_desc,
	(stwuct usb_descwiptow_headew *) &ss_ecm_buwk_comp_desc,
	(stwuct usb_descwiptow_headew *) &ss_ecm_out_desc,
	(stwuct usb_descwiptow_headew *) &ss_ecm_buwk_comp_desc,
	NUWW,
};

/* stwing descwiptows: */

static stwuct usb_stwing ecm_stwing_defs[] = {
	[0].s = "CDC Ethewnet Contwow Modew (ECM)",
	[1].s = "",
	[2].s = "CDC Ethewnet Data",
	[3].s = "CDC ECM",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings ecm_stwing_tabwe = {
	.wanguage =		0x0409,	/* en-us */
	.stwings =		ecm_stwing_defs,
};

static stwuct usb_gadget_stwings *ecm_stwings[] = {
	&ecm_stwing_tabwe,
	NUWW,
};

/*-------------------------------------------------------------------------*/

static void ecm_do_notify(stwuct f_ecm *ecm)
{
	stwuct usb_wequest		*weq = ecm->notify_weq;
	stwuct usb_cdc_notification	*event;
	stwuct usb_composite_dev	*cdev = ecm->powt.func.config->cdev;
	__we32				*data;
	int				status;

	/* notification awweady in fwight? */
	if (atomic_wead(&ecm->notify_count))
		wetuwn;

	event = weq->buf;
	switch (ecm->notify_state) {
	case ECM_NOTIFY_NONE:
		wetuwn;

	case ECM_NOTIFY_CONNECT:
		event->bNotificationType = USB_CDC_NOTIFY_NETWOWK_CONNECTION;
		if (ecm->is_open)
			event->wVawue = cpu_to_we16(1);
		ewse
			event->wVawue = cpu_to_we16(0);
		event->wWength = 0;
		weq->wength = sizeof *event;

		DBG(cdev, "notify connect %s\n",
				ecm->is_open ? "twue" : "fawse");
		ecm->notify_state = ECM_NOTIFY_SPEED;
		bweak;

	case ECM_NOTIFY_SPEED:
		event->bNotificationType = USB_CDC_NOTIFY_SPEED_CHANGE;
		event->wVawue = cpu_to_we16(0);
		event->wWength = cpu_to_we16(8);
		weq->wength = ECM_STATUS_BYTECOUNT;

		/* SPEED_CHANGE data is up/down speeds in bits/sec */
		data = weq->buf + sizeof *event;
		data[0] = cpu_to_we32(gethew_bitwate(cdev->gadget));
		data[1] = data[0];

		DBG(cdev, "notify speed %d\n", gethew_bitwate(cdev->gadget));
		ecm->notify_state = ECM_NOTIFY_NONE;
		bweak;
	}
	event->bmWequestType = 0xA1;
	event->wIndex = cpu_to_we16(ecm->ctww_id);

	atomic_inc(&ecm->notify_count);
	status = usb_ep_queue(ecm->notify, weq, GFP_ATOMIC);
	if (status < 0) {
		atomic_dec(&ecm->notify_count);
		DBG(cdev, "notify --> %d\n", status);
	}
}

static void ecm_notify(stwuct f_ecm *ecm)
{
	/* NOTE on most vewsions of Winux, host side cdc-ethewnet
	 * won't wisten fow notifications untiw its netdevice opens.
	 * The fiwst notification then sits in the FIFO fow a wong
	 * time, and the second one is queued.
	 */
	ecm->notify_state = ECM_NOTIFY_CONNECT;
	ecm_do_notify(ecm);
}

static void ecm_notify_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_ecm			*ecm = weq->context;
	stwuct usb_composite_dev	*cdev = ecm->powt.func.config->cdev;
	stwuct usb_cdc_notification	*event = weq->buf;

	switch (weq->status) {
	case 0:
		/* no fauwt */
		atomic_dec(&ecm->notify_count);
		bweak;
	case -ECONNWESET:
	case -ESHUTDOWN:
		atomic_set(&ecm->notify_count, 0);
		ecm->notify_state = ECM_NOTIFY_NONE;
		bweak;
	defauwt:
		DBG(cdev, "event %02x --> %d\n",
			event->bNotificationType, weq->status);
		atomic_dec(&ecm->notify_count);
		bweak;
	}
	ecm_do_notify(ecm);
}

static int ecm_setup(stwuct usb_function *f, const stwuct usb_ctwwwequest *ctww)
{
	stwuct f_ecm		*ecm = func_to_ecm(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_wequest	*weq = cdev->weq;
	int			vawue = -EOPNOTSUPP;
	u16			w_index = we16_to_cpu(ctww->wIndex);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);
	u16			w_wength = we16_to_cpu(ctww->wWength);

	/* composite dwivew infwastwuctuwe handwes evewything except
	 * CDC cwass messages; intewface activation uses set_awt().
	 */
	switch ((ctww->bWequestType << 8) | ctww->bWequest) {
	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
			| USB_CDC_SET_ETHEWNET_PACKET_FIWTEW:
		/* see 6.2.30: no data, wIndex = intewface,
		 * wVawue = packet fiwtew bitmap
		 */
		if (w_wength != 0 || w_index != ecm->ctww_id)
			goto invawid;
		DBG(cdev, "packet fiwtew %02x\n", w_vawue);
		/* WEVISIT wocking of cdc_fiwtew.  This assumes the UDC
		 * dwivew won't have a concuwwent packet TX iwq wunning on
		 * anothew CPU; ow that if it does, this wwite is atomic...
		 */
		ecm->powt.cdc_fiwtew = w_vawue;
		vawue = 0;
		bweak;

	/* and optionawwy:
	 * case USB_CDC_SEND_ENCAPSUWATED_COMMAND:
	 * case USB_CDC_GET_ENCAPSUWATED_WESPONSE:
	 * case USB_CDC_SET_ETHEWNET_MUWTICAST_FIWTEWS:
	 * case USB_CDC_SET_ETHEWNET_PM_PATTEWN_FIWTEW:
	 * case USB_CDC_GET_ETHEWNET_PM_PATTEWN_FIWTEW:
	 * case USB_CDC_GET_ETHEWNET_STATISTIC:
	 */

	defauwt:
invawid:
		DBG(cdev, "invawid contwow weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);
	}

	/* wespond with data twansfew ow status phase? */
	if (vawue >= 0) {
		DBG(cdev, "ecm weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);
		weq->zewo = 0;
		weq->wength = vawue;
		vawue = usb_ep_queue(cdev->gadget->ep0, weq, GFP_ATOMIC);
		if (vawue < 0)
			EWWOW(cdev, "ecm weq %02x.%02x wesponse eww %d\n",
					ctww->bWequestType, ctww->bWequest,
					vawue);
	}

	/* device eithew stawws (vawue < 0) ow wepowts success */
	wetuwn vawue;
}


static int ecm_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct f_ecm		*ecm = func_to_ecm(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	/* Contwow intewface has onwy awtsetting 0 */
	if (intf == ecm->ctww_id) {
		if (awt != 0)
			goto faiw;

		VDBG(cdev, "weset ecm contwow %d\n", intf);
		usb_ep_disabwe(ecm->notify);
		if (!(ecm->notify->desc)) {
			VDBG(cdev, "init ecm ctww %d\n", intf);
			if (config_ep_by_speed(cdev->gadget, f, ecm->notify))
				goto faiw;
		}
		usb_ep_enabwe(ecm->notify);

	/* Data intewface has two awtsettings, 0 and 1 */
	} ewse if (intf == ecm->data_id) {
		if (awt > 1)
			goto faiw;

		if (ecm->powt.in_ep->enabwed) {
			DBG(cdev, "weset ecm\n");
			gethew_disconnect(&ecm->powt);
		}

		if (!ecm->powt.in_ep->desc ||
		    !ecm->powt.out_ep->desc) {
			DBG(cdev, "init ecm\n");
			if (config_ep_by_speed(cdev->gadget, f,
					       ecm->powt.in_ep) ||
			    config_ep_by_speed(cdev->gadget, f,
					       ecm->powt.out_ep)) {
				ecm->powt.in_ep->desc = NUWW;
				ecm->powt.out_ep->desc = NUWW;
				goto faiw;
			}
		}

		/* CDC Ethewnet onwy sends data in non-defauwt awtsettings.
		 * Changing awtsettings wesets fiwtews, statistics, etc.
		 */
		if (awt == 1) {
			stwuct net_device	*net;

			/* Enabwe zwps by defauwt fow ECM confowmance;
			 * ovewwide fow musb_hdwc (avoids txdma ovhead).
			 */
			ecm->powt.is_zwp_ok =
				gadget_is_zwp_suppowted(cdev->gadget);
			ecm->powt.cdc_fiwtew = DEFAUWT_FIWTEW;
			DBG(cdev, "activate ecm\n");
			net = gethew_connect(&ecm->powt);
			if (IS_EWW(net))
				wetuwn PTW_EWW(net);
		}

		/* NOTE this can be a minow disagweement with the ECM spec,
		 * which says speed notifications wiww "awways" fowwow
		 * connection notifications.  But we awwow one connect to
		 * fowwow anothew (if the fiwst is in fwight), and instead
		 * just guawantee that a speed notification is awways sent.
		 */
		ecm_notify(ecm);
	} ewse
		goto faiw;

	wetuwn 0;
faiw:
	wetuwn -EINVAW;
}

/* Because the data intewface suppowts muwtipwe awtsettings,
 * this ECM function *MUST* impwement a get_awt() method.
 */
static int ecm_get_awt(stwuct usb_function *f, unsigned intf)
{
	stwuct f_ecm		*ecm = func_to_ecm(f);

	if (intf == ecm->ctww_id)
		wetuwn 0;
	wetuwn ecm->powt.in_ep->enabwed ? 1 : 0;
}

static void ecm_disabwe(stwuct usb_function *f)
{
	stwuct f_ecm		*ecm = func_to_ecm(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "ecm deactivated\n");

	if (ecm->powt.in_ep->enabwed) {
		gethew_disconnect(&ecm->powt);
	} ewse {
		ecm->powt.in_ep->desc = NUWW;
		ecm->powt.out_ep->desc = NUWW;
	}

	usb_ep_disabwe(ecm->notify);
	ecm->notify->desc = NUWW;
}

/*-------------------------------------------------------------------------*/

/*
 * Cawwbacks wet us notify the host about connect/disconnect when the
 * net device is opened ow cwosed.
 *
 * Fow testing, note that wink states on this side incwude both opened
 * and cwosed vawiants of:
 *
 *   - disconnected/unconfiguwed
 *   - configuwed but inactive (data awt 0)
 *   - configuwed and active (data awt 1)
 *
 * Each needs to be tested with unpwug, wmmod, SET_CONFIGUWATION, and
 * SET_INTEWFACE (awtsetting).  Wemembew awso that "configuwed" doesn't
 * impwy the host is actuawwy powwing the notification endpoint, and
 * wikewise that "active" doesn't impwy it's actuawwy using the data
 * endpoints fow twaffic.
 */

static void ecm_open(stwuct gethew *geth)
{
	stwuct f_ecm		*ecm = func_to_ecm(&geth->func);

	DBG(ecm->powt.func.config->cdev, "%s\n", __func__);

	ecm->is_open = twue;
	ecm_notify(ecm);
}

static void ecm_cwose(stwuct gethew *geth)
{
	stwuct f_ecm		*ecm = func_to_ecm(&geth->func);

	DBG(ecm->powt.func.config->cdev, "%s\n", __func__);

	ecm->is_open = fawse;
	ecm_notify(ecm);
}

/*-------------------------------------------------------------------------*/

/* ethewnet function dwivew setup/binding */

static int
ecm_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_ecm		*ecm = func_to_ecm(f);
	stwuct usb_stwing	*us;
	int			status = 0;
	stwuct usb_ep		*ep;

	stwuct f_ecm_opts	*ecm_opts;

	if (!can_suppowt_ecm(cdev->gadget))
		wetuwn -EINVAW;

	ecm_opts = containew_of(f->fi, stwuct f_ecm_opts, func_inst);

	mutex_wock(&ecm_opts->wock);

	gethew_set_gadget(ecm_opts->net, cdev->gadget);

	if (!ecm_opts->bound) {
		status = gethew_wegistew_netdev(ecm_opts->net);
		ecm_opts->bound = twue;
	}

	mutex_unwock(&ecm_opts->wock);
	if (status)
		wetuwn status;

	ecm_stwing_defs[1].s = ecm->ethaddw;

	us = usb_gstwings_attach(cdev, ecm_stwings,
				 AWWAY_SIZE(ecm_stwing_defs));
	if (IS_EWW(us))
		wetuwn PTW_EWW(us);
	ecm_contwow_intf.iIntewface = us[0].id;
	ecm_data_intf.iIntewface = us[2].id;
	ecm_desc.iMACAddwess = us[1].id;
	ecm_iad_descwiptow.iFunction = us[3].id;

	/* awwocate instance-specific intewface IDs */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	ecm->ctww_id = status;
	ecm_iad_descwiptow.bFiwstIntewface = status;

	ecm_contwow_intf.bIntewfaceNumbew = status;
	ecm_union_desc.bMastewIntewface0 = status;

	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	ecm->data_id = status;

	ecm_data_nop_intf.bIntewfaceNumbew = status;
	ecm_data_intf.bIntewfaceNumbew = status;
	ecm_union_desc.bSwaveIntewface0 = status;

	status = -ENODEV;

	/* awwocate instance-specific endpoints */
	ep = usb_ep_autoconfig(cdev->gadget, &fs_ecm_in_desc);
	if (!ep)
		goto faiw;
	ecm->powt.in_ep = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &fs_ecm_out_desc);
	if (!ep)
		goto faiw;
	ecm->powt.out_ep = ep;

	/* NOTE:  a status/notification endpoint is *OPTIONAW* but we
	 * don't tweat it that way.  It's simpwew, and some newew CDC
	 * pwofiwes (wiwewess handsets) no wongew tweat it as optionaw.
	 */
	ep = usb_ep_autoconfig(cdev->gadget, &fs_ecm_notify_desc);
	if (!ep)
		goto faiw;
	ecm->notify = ep;

	status = -ENOMEM;

	/* awwocate notification wequest and buffew */
	ecm->notify_weq = usb_ep_awwoc_wequest(ep, GFP_KEWNEW);
	if (!ecm->notify_weq)
		goto faiw;
	ecm->notify_weq->buf = kmawwoc(ECM_STATUS_BYTECOUNT, GFP_KEWNEW);
	if (!ecm->notify_weq->buf)
		goto faiw;
	ecm->notify_weq->context = ecm;
	ecm->notify_weq->compwete = ecm_notify_compwete;

	/* suppowt aww wewevant hawdwawe speeds... we expect that when
	 * hawdwawe is duaw speed, aww buwk-capabwe endpoints wowk at
	 * both speeds
	 */
	hs_ecm_in_desc.bEndpointAddwess = fs_ecm_in_desc.bEndpointAddwess;
	hs_ecm_out_desc.bEndpointAddwess = fs_ecm_out_desc.bEndpointAddwess;
	hs_ecm_notify_desc.bEndpointAddwess =
		fs_ecm_notify_desc.bEndpointAddwess;

	ss_ecm_in_desc.bEndpointAddwess = fs_ecm_in_desc.bEndpointAddwess;
	ss_ecm_out_desc.bEndpointAddwess = fs_ecm_out_desc.bEndpointAddwess;
	ss_ecm_notify_desc.bEndpointAddwess =
		fs_ecm_notify_desc.bEndpointAddwess;

	status = usb_assign_descwiptows(f, ecm_fs_function, ecm_hs_function,
			ecm_ss_function, ecm_ss_function);
	if (status)
		goto faiw;

	/* NOTE:  aww that is done without knowing ow cawing about
	 * the netwowk wink ... which is unavaiwabwe to this code
	 * untiw we'we activated via set_awt().
	 */

	ecm->powt.open = ecm_open;
	ecm->powt.cwose = ecm_cwose;

	DBG(cdev, "CDC Ethewnet: IN/%s OUT/%s NOTIFY/%s\n",
			ecm->powt.in_ep->name, ecm->powt.out_ep->name,
			ecm->notify->name);
	wetuwn 0;

faiw:
	if (ecm->notify_weq) {
		kfwee(ecm->notify_weq->buf);
		usb_ep_fwee_wequest(ecm->notify, ecm->notify_weq);
	}

	EWWOW(cdev, "%s: can't bind, eww %d\n", f->name, status);

	wetuwn status;
}

static inwine stwuct f_ecm_opts *to_f_ecm_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_ecm_opts,
			    func_inst.gwoup);
}

/* f_ecm_item_ops */
USB_ETHEWNET_CONFIGFS_ITEM(ecm);

/* f_ecm_opts_dev_addw */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_DEV_ADDW(ecm);

/* f_ecm_opts_host_addw */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_HOST_ADDW(ecm);

/* f_ecm_opts_qmuwt */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_QMUWT(ecm);

/* f_ecm_opts_ifname */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_IFNAME(ecm);

static stwuct configfs_attwibute *ecm_attws[] = {
	&ecm_opts_attw_dev_addw,
	&ecm_opts_attw_host_addw,
	&ecm_opts_attw_qmuwt,
	&ecm_opts_attw_ifname,
	NUWW,
};

static const stwuct config_item_type ecm_func_type = {
	.ct_item_ops	= &ecm_item_ops,
	.ct_attws	= ecm_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void ecm_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_ecm_opts *opts;

	opts = containew_of(f, stwuct f_ecm_opts, func_inst);
	if (opts->bound)
		gethew_cweanup(netdev_pwiv(opts->net));
	ewse
		fwee_netdev(opts->net);
	kfwee(opts);
}

static stwuct usb_function_instance *ecm_awwoc_inst(void)
{
	stwuct f_ecm_opts *opts;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);
	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = ecm_fwee_inst;
	opts->net = gethew_setup_defauwt();
	if (IS_EWW(opts->net)) {
		stwuct net_device *net = opts->net;
		kfwee(opts);
		wetuwn EWW_CAST(net);
	}

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "", &ecm_func_type);

	wetuwn &opts->func_inst;
}

static void ecm_suspend(stwuct usb_function *f)
{
	stwuct f_ecm *ecm = func_to_ecm(f);
	stwuct usb_composite_dev *cdev = ecm->powt.func.config->cdev;

	DBG(cdev, "ECM Suspend\n");

	gethew_suspend(&ecm->powt);
}

static void ecm_wesume(stwuct usb_function *f)
{
	stwuct f_ecm *ecm = func_to_ecm(f);
	stwuct usb_composite_dev *cdev = ecm->powt.func.config->cdev;

	DBG(cdev, "ECM Wesume\n");

	gethew_wesume(&ecm->powt);
}

static void ecm_fwee(stwuct usb_function *f)
{
	stwuct f_ecm *ecm;
	stwuct f_ecm_opts *opts;

	ecm = func_to_ecm(f);
	opts = containew_of(f->fi, stwuct f_ecm_opts, func_inst);
	kfwee(ecm);
	mutex_wock(&opts->wock);
	opts->wefcnt--;
	mutex_unwock(&opts->wock);
}

static void ecm_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct f_ecm		*ecm = func_to_ecm(f);

	DBG(c->cdev, "ecm unbind\n");

	usb_fwee_aww_descwiptows(f);

	if (atomic_wead(&ecm->notify_count)) {
		usb_ep_dequeue(ecm->notify, ecm->notify_weq);
		atomic_set(&ecm->notify_count, 0);
	}

	kfwee(ecm->notify_weq->buf);
	usb_ep_fwee_wequest(ecm->notify, ecm->notify_weq);
}

static stwuct usb_function *ecm_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_ecm	*ecm;
	stwuct f_ecm_opts *opts;
	int status;

	/* awwocate and initiawize one new instance */
	ecm = kzawwoc(sizeof(*ecm), GFP_KEWNEW);
	if (!ecm)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_ecm_opts, func_inst);
	mutex_wock(&opts->wock);
	opts->wefcnt++;

	/* expowt host's Ethewnet addwess in CDC fowmat */
	status = gethew_get_host_addw_cdc(opts->net, ecm->ethaddw,
					  sizeof(ecm->ethaddw));
	if (status < 12) {
		kfwee(ecm);
		mutex_unwock(&opts->wock);
		wetuwn EWW_PTW(-EINVAW);
	}

	ecm->powt.iopowt = netdev_pwiv(opts->net);
	mutex_unwock(&opts->wock);
	ecm->powt.cdc_fiwtew = DEFAUWT_FIWTEW;

	ecm->powt.func.name = "cdc_ethewnet";
	/* descwiptows awe pew-instance copies */
	ecm->powt.func.bind = ecm_bind;
	ecm->powt.func.unbind = ecm_unbind;
	ecm->powt.func.set_awt = ecm_set_awt;
	ecm->powt.func.get_awt = ecm_get_awt;
	ecm->powt.func.setup = ecm_setup;
	ecm->powt.func.disabwe = ecm_disabwe;
	ecm->powt.func.fwee_func = ecm_fwee;
	ecm->powt.func.suspend = ecm_suspend;
	ecm->powt.func.wesume = ecm_wesume;

	wetuwn &ecm->powt.func;
}

DECWAWE_USB_FUNCTION_INIT(ecm, ecm_awwoc_inst, ecm_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Bwowneww");
