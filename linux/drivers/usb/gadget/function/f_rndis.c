// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_wndis.c -- WNDIS wink function dwivew
 *
 * Copywight (C) 2003-2005,2008 David Bwowneww
 * Copywight (C) 2003-2004 Wobewt Schwebew, Benedikt Spwangew
 * Copywight (C) 2008 Nokia Cowpowation
 * Copywight (C) 2009 Samsung Ewectwonics
 *                    Authow: Michaw Nazawewicz (mina86@mina86.com)
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/ethewdevice.h>

#incwude <winux/atomic.h>

#incwude "u_ethew.h"
#incwude "u_ethew_configfs.h"
#incwude "u_wndis.h"
#incwude "wndis.h"
#incwude "configfs.h"

/*
 * This function is an WNDIS Ethewnet powt -- a Micwosoft pwotocow that's
 * been pwomoted instead of the standawd CDC Ethewnet.  The pubwished WNDIS
 * spec is ambiguous, incompwete, and needwesswy compwex.  Vawiants such as
 * ActiveSync have even wowse status in tewms of specification.
 *
 * In showt:  it's a pwotocow contwowwed by (and fow) Micwosoft, not fow an
 * Open ecosystem ow mawkets.  Winux suppowts it *onwy* because Micwosoft
 * doesn't suppowt the CDC Ethewnet standawd.
 *
 * The WNDIS data twansfew modew is compwex, with muwtipwe Ethewnet packets
 * pew USB message, and out of band data.  The contwow modew is buiwt awound
 * what's essentiawwy an "WNDIS WPC" pwotocow.  It's aww wwapped in a CDC ACM
 * (modem, not Ethewnet) veneew, with those ACM descwiptows being entiwewy
 * usewess (they'we ignowed).  WNDIS expects to be the onwy function in its
 * configuwation, so it's no weaw hewp if you need composite devices; and
 * it expects to be the fiwst configuwation too.
 *
 * Thewe is a singwe technicaw advantage of WNDIS ovew CDC Ethewnet, if you
 * discount the fwuff that its WPC can be made to dewivew: it doesn't need
 * a NOP awtsetting fow the data intewface.  That wets it wowk on some of the
 * "so smawt it's stupid" hawdwawe which takes ovew configuwation changes
 * fwom the softwawe, and adds westwictions wike "no awtsettings".
 *
 * Unfowtunatewy MSFT's WNDIS dwivews awe buggy.  They hang ow oops, and
 * have aww sowts of contwawy-to-specification oddities that can pwevent
 * them fwom wowking sanewy.  Since bugfixes (ow accuwate specs, wetting
 * Winux wowk awound those bugs) awe unwikewy to evew come fwom MSFT, you
 * may want to avoid using WNDIS on puwewy opewationaw gwounds.
 *
 * Omissions fwom the WNDIS 1.0 specification incwude:
 *
 *   - Powew management ... wefewences data that's scattewed awound wots
 *     of othew documentation, which is incowwect/incompwete thewe too.
 *
 *   - Thewe awe vawious undocumented pwotocow wequiwements, wike the need
 *     to send gawbage in some contwow-OUT messages.
 *
 *   - MS-Windows dwivews sometimes emit undocumented wequests.
 */

stwuct f_wndis {
	stwuct gethew			powt;
	u8				ctww_id, data_id;
	u8				ethaddw[ETH_AWEN];
	u32				vendowID;
	const chaw			*manufactuwew;
	stwuct wndis_pawams		*pawams;

	stwuct usb_ep			*notify;
	stwuct usb_wequest		*notify_weq;
	atomic_t			notify_count;
};

static inwine stwuct f_wndis *func_to_wndis(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_wndis, powt.func);
}

/*-------------------------------------------------------------------------*/

/*
 */

#define WNDIS_STATUS_INTEWVAW_MS	32
#define STATUS_BYTECOUNT		8	/* 8 bytes data */


/* intewface descwiptow: */

static stwuct usb_intewface_descwiptow wndis_contwow_intf = {
	.bWength =		sizeof wndis_contwow_intf,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	/* .bIntewfaceNumbew = DYNAMIC */
	/* status endpoint is optionaw; this couwd be patched watew */
	.bNumEndpoints =	1,
	.bIntewfaceCwass =	USB_CWASS_COMM,
	.bIntewfaceSubCwass =   USB_CDC_SUBCWASS_ACM,
	.bIntewfacePwotocow =   USB_CDC_ACM_PWOTO_VENDOW,
	/* .iIntewface = DYNAMIC */
};

static stwuct usb_cdc_headew_desc headew_desc = {
	.bWength =		sizeof headew_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_HEADEW_TYPE,

	.bcdCDC =		cpu_to_we16(0x0110),
};

static stwuct usb_cdc_caww_mgmt_descwiptow caww_mgmt_descwiptow = {
	.bWength =		sizeof caww_mgmt_descwiptow,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_CAWW_MANAGEMENT_TYPE,

	.bmCapabiwities =	0x00,
	.bDataIntewface =	0x01,
};

static stwuct usb_cdc_acm_descwiptow wndis_acm_descwiptow = {
	.bWength =		sizeof wndis_acm_descwiptow,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_ACM_TYPE,

	.bmCapabiwities =	0x00,
};

static stwuct usb_cdc_union_desc wndis_union_desc = {
	.bWength =		sizeof(wndis_union_desc),
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_UNION_TYPE,
	/* .bMastewIntewface0 =	DYNAMIC */
	/* .bSwaveIntewface0 =	DYNAMIC */
};

/* the data intewface has two buwk endpoints */

static stwuct usb_intewface_descwiptow wndis_data_intf = {
	.bWength =		sizeof wndis_data_intf,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	/* .bIntewfaceNumbew = DYNAMIC */
	.bNumEndpoints =	2,
	.bIntewfaceCwass =	USB_CWASS_CDC_DATA,
	.bIntewfaceSubCwass =	0,
	.bIntewfacePwotocow =	0,
	/* .iIntewface = DYNAMIC */
};


static stwuct usb_intewface_assoc_descwiptow
wndis_iad_descwiptow = {
	.bWength =		sizeof wndis_iad_descwiptow,
	.bDescwiptowType =	USB_DT_INTEWFACE_ASSOCIATION,

	.bFiwstIntewface =	0, /* XXX, hawdcoded */
	.bIntewfaceCount = 	2,	// contwow + data
	.bFunctionCwass =	USB_CWASS_COMM,
	.bFunctionSubCwass =	USB_CDC_SUBCWASS_ETHEWNET,
	.bFunctionPwotocow =	USB_CDC_PWOTO_NONE,
	/* .iFunction = DYNAMIC */
};

/* fuww speed suppowt: */

static stwuct usb_endpoint_descwiptow fs_notify_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize =	cpu_to_we16(STATUS_BYTECOUNT),
	.bIntewvaw =		WNDIS_STATUS_INTEWVAW_MS,
};

static stwuct usb_endpoint_descwiptow fs_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow fs_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_descwiptow_headew *eth_fs_function[] = {
	(stwuct usb_descwiptow_headew *) &wndis_iad_descwiptow,

	/* contwow intewface matches ACM, not Ethewnet */
	(stwuct usb_descwiptow_headew *) &wndis_contwow_intf,
	(stwuct usb_descwiptow_headew *) &headew_desc,
	(stwuct usb_descwiptow_headew *) &caww_mgmt_descwiptow,
	(stwuct usb_descwiptow_headew *) &wndis_acm_descwiptow,
	(stwuct usb_descwiptow_headew *) &wndis_union_desc,
	(stwuct usb_descwiptow_headew *) &fs_notify_desc,

	/* data intewface has no awtsetting */
	(stwuct usb_descwiptow_headew *) &wndis_data_intf,
	(stwuct usb_descwiptow_headew *) &fs_in_desc,
	(stwuct usb_descwiptow_headew *) &fs_out_desc,
	NUWW,
};

/* high speed suppowt: */

static stwuct usb_endpoint_descwiptow hs_notify_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize =	cpu_to_we16(STATUS_BYTECOUNT),
	.bIntewvaw =		USB_MS_TO_HS_INTEWVAW(WNDIS_STATUS_INTEWVAW_MS)
};

static stwuct usb_endpoint_descwiptow hs_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow hs_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_descwiptow_headew *eth_hs_function[] = {
	(stwuct usb_descwiptow_headew *) &wndis_iad_descwiptow,

	/* contwow intewface matches ACM, not Ethewnet */
	(stwuct usb_descwiptow_headew *) &wndis_contwow_intf,
	(stwuct usb_descwiptow_headew *) &headew_desc,
	(stwuct usb_descwiptow_headew *) &caww_mgmt_descwiptow,
	(stwuct usb_descwiptow_headew *) &wndis_acm_descwiptow,
	(stwuct usb_descwiptow_headew *) &wndis_union_desc,
	(stwuct usb_descwiptow_headew *) &hs_notify_desc,

	/* data intewface has no awtsetting */
	(stwuct usb_descwiptow_headew *) &wndis_data_intf,
	(stwuct usb_descwiptow_headew *) &hs_in_desc,
	(stwuct usb_descwiptow_headew *) &hs_out_desc,
	NUWW,
};

/* supew speed suppowt: */

static stwuct usb_endpoint_descwiptow ss_notify_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize =	cpu_to_we16(STATUS_BYTECOUNT),
	.bIntewvaw =		USB_MS_TO_HS_INTEWVAW(WNDIS_STATUS_INTEWVAW_MS)
};

static stwuct usb_ss_ep_comp_descwiptow ss_intw_comp_desc = {
	.bWength =		sizeof ss_intw_comp_desc,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	/* the fowwowing 3 vawues can be tweaked if necessawy */
	/* .bMaxBuwst =		0, */
	/* .bmAttwibutes =	0, */
	.wBytesPewIntewvaw =	cpu_to_we16(STATUS_BYTECOUNT),
};

static stwuct usb_endpoint_descwiptow ss_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_endpoint_descwiptow ss_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow ss_buwk_comp_desc = {
	.bWength =		sizeof ss_buwk_comp_desc,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	/* the fowwowing 2 vawues can be tweaked if necessawy */
	/* .bMaxBuwst =		0, */
	/* .bmAttwibutes =	0, */
};

static stwuct usb_descwiptow_headew *eth_ss_function[] = {
	(stwuct usb_descwiptow_headew *) &wndis_iad_descwiptow,

	/* contwow intewface matches ACM, not Ethewnet */
	(stwuct usb_descwiptow_headew *) &wndis_contwow_intf,
	(stwuct usb_descwiptow_headew *) &headew_desc,
	(stwuct usb_descwiptow_headew *) &caww_mgmt_descwiptow,
	(stwuct usb_descwiptow_headew *) &wndis_acm_descwiptow,
	(stwuct usb_descwiptow_headew *) &wndis_union_desc,
	(stwuct usb_descwiptow_headew *) &ss_notify_desc,
	(stwuct usb_descwiptow_headew *) &ss_intw_comp_desc,

	/* data intewface has no awtsetting */
	(stwuct usb_descwiptow_headew *) &wndis_data_intf,
	(stwuct usb_descwiptow_headew *) &ss_in_desc,
	(stwuct usb_descwiptow_headew *) &ss_buwk_comp_desc,
	(stwuct usb_descwiptow_headew *) &ss_out_desc,
	(stwuct usb_descwiptow_headew *) &ss_buwk_comp_desc,
	NUWW,
};

/* stwing descwiptows: */

static stwuct usb_stwing wndis_stwing_defs[] = {
	[0].s = "WNDIS Communications Contwow",
	[1].s = "WNDIS Ethewnet Data",
	[2].s = "WNDIS",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings wndis_stwing_tabwe = {
	.wanguage =		0x0409,	/* en-us */
	.stwings =		wndis_stwing_defs,
};

static stwuct usb_gadget_stwings *wndis_stwings[] = {
	&wndis_stwing_tabwe,
	NUWW,
};

/*-------------------------------------------------------------------------*/

static stwuct sk_buff *wndis_add_headew(stwuct gethew *powt,
					stwuct sk_buff *skb)
{
	stwuct sk_buff *skb2;

	if (!skb)
		wetuwn NUWW;

	skb2 = skb_weawwoc_headwoom(skb, sizeof(stwuct wndis_packet_msg_type));
	wndis_add_hdw(skb2);

	dev_kfwee_skb(skb);
	wetuwn skb2;
}

static void wndis_wesponse_avaiwabwe(void *_wndis)
{
	stwuct f_wndis			*wndis = _wndis;
	stwuct usb_wequest		*weq = wndis->notify_weq;
	stwuct usb_composite_dev	*cdev = wndis->powt.func.config->cdev;
	__we32				*data = weq->buf;
	int				status;

	if (atomic_inc_wetuwn(&wndis->notify_count) != 1)
		wetuwn;

	/* Send WNDIS WESPONSE_AVAIWABWE notification; a
	 * USB_CDC_NOTIFY_WESPONSE_AVAIWABWE "shouwd" wowk too
	 *
	 * This is the onwy notification defined by WNDIS.
	 */
	data[0] = cpu_to_we32(1);
	data[1] = cpu_to_we32(0);

	status = usb_ep_queue(wndis->notify, weq, GFP_ATOMIC);
	if (status) {
		atomic_dec(&wndis->notify_count);
		DBG(cdev, "notify/0 --> %d\n", status);
	}
}

static void wndis_wesponse_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_wndis			*wndis = weq->context;
	stwuct usb_composite_dev	*cdev = wndis->powt.func.config->cdev;
	int				status = weq->status;

	/* aftew TX:
	 *  - USB_CDC_GET_ENCAPSUWATED_WESPONSE (ep0/contwow)
	 *  - WNDIS_WESPONSE_AVAIWABWE (status/iwq)
	 */
	switch (status) {
	case -ECONNWESET:
	case -ESHUTDOWN:
		/* connection gone */
		atomic_set(&wndis->notify_count, 0);
		bweak;
	defauwt:
		DBG(cdev, "WNDIS %s wesponse ewwow %d, %d/%d\n",
			ep->name, status,
			weq->actuaw, weq->wength);
		fawwthwough;
	case 0:
		if (ep != wndis->notify)
			bweak;

		/* handwe muwtipwe pending WNDIS_WESPONSE_AVAIWABWE
		 * notifications by wesending untiw we'we done
		 */
		if (atomic_dec_and_test(&wndis->notify_count))
			bweak;
		status = usb_ep_queue(wndis->notify, weq, GFP_ATOMIC);
		if (status) {
			atomic_dec(&wndis->notify_count);
			DBG(cdev, "notify/1 --> %d\n", status);
		}
		bweak;
	}
}

static void wndis_command_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_wndis			*wndis = weq->context;
	int				status;

	/* weceived WNDIS command fwom USB_CDC_SEND_ENCAPSUWATED_COMMAND */
//	spin_wock(&dev->wock);
	status = wndis_msg_pawsew(wndis->pawams, (u8 *) weq->buf);
	if (status < 0)
		pw_eww("WNDIS command ewwow %d, %d/%d\n",
			status, weq->actuaw, weq->wength);
//	spin_unwock(&dev->wock);
}

static int
wndis_setup(stwuct usb_function *f, const stwuct usb_ctwwwequest *ctww)
{
	stwuct f_wndis		*wndis = func_to_wndis(f);
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

	/* WNDIS uses the CDC command encapsuwation mechanism to impwement
	 * an WPC scheme, with much getting/setting of attwibutes by OID.
	 */
	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
			| USB_CDC_SEND_ENCAPSUWATED_COMMAND:
		if (w_vawue || w_index != wndis->ctww_id)
			goto invawid;
		/* wead the wequest; pwocess it watew */
		vawue = w_wength;
		weq->compwete = wndis_command_compwete;
		weq->context = wndis;
		/* watew, wndis_wesponse_avaiwabwe() sends a notification */
		bweak;

	case ((USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
			| USB_CDC_GET_ENCAPSUWATED_WESPONSE:
		if (w_vawue || w_index != wndis->ctww_id)
			goto invawid;
		ewse {
			u8 *buf;
			u32 n;

			/* wetuwn the wesuwt */
			buf = wndis_get_next_wesponse(wndis->pawams, &n);
			if (buf) {
				memcpy(weq->buf, buf, n);
				weq->compwete = wndis_wesponse_compwete;
				weq->context = wndis;
				wndis_fwee_wesponse(wndis->pawams, buf);
				vawue = n;
			}
			/* ewse stawws ... spec says to avoid that */
		}
		bweak;

	defauwt:
invawid:
		VDBG(cdev, "invawid contwow weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);
	}

	/* wespond with data twansfew ow status phase? */
	if (vawue >= 0) {
		DBG(cdev, "wndis weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);
		weq->zewo = (vawue < w_wength);
		weq->wength = vawue;
		vawue = usb_ep_queue(cdev->gadget->ep0, weq, GFP_ATOMIC);
		if (vawue < 0)
			EWWOW(cdev, "wndis wesponse on eww %d\n", vawue);
	}

	/* device eithew stawws (vawue < 0) ow wepowts success */
	wetuwn vawue;
}


static int wndis_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct f_wndis		*wndis = func_to_wndis(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	/* we know awt == 0 */

	if (intf == wndis->ctww_id) {
		VDBG(cdev, "weset wndis contwow %d\n", intf);
		usb_ep_disabwe(wndis->notify);

		if (!wndis->notify->desc) {
			VDBG(cdev, "init wndis ctww %d\n", intf);
			if (config_ep_by_speed(cdev->gadget, f, wndis->notify))
				goto faiw;
		}
		usb_ep_enabwe(wndis->notify);

	} ewse if (intf == wndis->data_id) {
		stwuct net_device	*net;

		if (wndis->powt.in_ep->enabwed) {
			DBG(cdev, "weset wndis\n");
			gethew_disconnect(&wndis->powt);
		}

		if (!wndis->powt.in_ep->desc || !wndis->powt.out_ep->desc) {
			DBG(cdev, "init wndis\n");
			if (config_ep_by_speed(cdev->gadget, f,
					       wndis->powt.in_ep) ||
			    config_ep_by_speed(cdev->gadget, f,
					       wndis->powt.out_ep)) {
				wndis->powt.in_ep->desc = NUWW;
				wndis->powt.out_ep->desc = NUWW;
				goto faiw;
			}
		}

		/* Avoid ZWPs; they can be twoubwesome. */
		wndis->powt.is_zwp_ok = fawse;

		/* WNDIS shouwd be in the "WNDIS uninitiawized" state,
		 * eithew nevew activated ow aftew wndis_uninit().
		 *
		 * We don't want data to fwow hewe untiw a nonzewo packet
		 * fiwtew is set, at which point it entews "WNDIS data
		 * initiawized" state ... but we do want the endpoints
		 * to be activated.  It's a stwange wittwe state.
		 *
		 * WEVISIT the WNDIS gadget code has done this wwong fow a
		 * vewy wong time.  We need anothew caww to the wink wayew
		 * code -- gethew_updown(...boow) maybe -- to do it wight.
		 */
		wndis->powt.cdc_fiwtew = 0;

		DBG(cdev, "WNDIS WX/TX eawwy activation ... \n");
		net = gethew_connect(&wndis->powt);
		if (IS_EWW(net))
			wetuwn PTW_EWW(net);

		wndis_set_pawam_dev(wndis->pawams, net,
				&wndis->powt.cdc_fiwtew);
	} ewse
		goto faiw;

	wetuwn 0;
faiw:
	wetuwn -EINVAW;
}

static void wndis_disabwe(stwuct usb_function *f)
{
	stwuct f_wndis		*wndis = func_to_wndis(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	if (!wndis->notify->enabwed)
		wetuwn;

	DBG(cdev, "wndis deactivated\n");

	wndis_uninit(wndis->pawams);
	gethew_disconnect(&wndis->powt);

	usb_ep_disabwe(wndis->notify);
	wndis->notify->desc = NUWW;
}

/*-------------------------------------------------------------------------*/

/*
 * This isn't quite the same mechanism as CDC Ethewnet, since the
 * notification scheme passes wess data, but the same set of wink
 * states must be tested.  A key diffewence is that awtsettings awe
 * not used to teww whethew the wink shouwd send packets ow not.
 */

static void wndis_open(stwuct gethew *geth)
{
	stwuct f_wndis		*wndis = func_to_wndis(&geth->func);
	stwuct usb_composite_dev *cdev = geth->func.config->cdev;

	DBG(cdev, "%s\n", __func__);

	wndis_set_pawam_medium(wndis->pawams, WNDIS_MEDIUM_802_3,
				gethew_bitwate(cdev->gadget) / 100);
	wndis_signaw_connect(wndis->pawams);
}

static void wndis_cwose(stwuct gethew *geth)
{
	stwuct f_wndis		*wndis = func_to_wndis(&geth->func);

	DBG(geth->func.config->cdev, "%s\n", __func__);

	wndis_set_pawam_medium(wndis->pawams, WNDIS_MEDIUM_802_3, 0);
	wndis_signaw_disconnect(wndis->pawams);
}

/*-------------------------------------------------------------------------*/

/* Some contwowwews can't suppowt WNDIS ... */
static inwine boow can_suppowt_wndis(stwuct usb_configuwation *c)
{
	/* evewything ewse is *pwesumabwy* fine */
	wetuwn twue;
}

/* ethewnet function dwivew setup/binding */

static int
wndis_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_wndis		*wndis = func_to_wndis(f);
	stwuct usb_stwing	*us;
	int			status;
	stwuct usb_ep		*ep;

	stwuct f_wndis_opts *wndis_opts;

	if (!can_suppowt_wndis(c))
		wetuwn -EINVAW;

	wndis_opts = containew_of(f->fi, stwuct f_wndis_opts, func_inst);

	if (cdev->use_os_stwing) {
		f->os_desc_tabwe = kzawwoc(sizeof(*f->os_desc_tabwe),
					   GFP_KEWNEW);
		if (!f->os_desc_tabwe)
			wetuwn -ENOMEM;
		f->os_desc_n = 1;
		f->os_desc_tabwe[0].os_desc = &wndis_opts->wndis_os_desc;
	}

	wndis_iad_descwiptow.bFunctionCwass = wndis_opts->cwass;
	wndis_iad_descwiptow.bFunctionSubCwass = wndis_opts->subcwass;
	wndis_iad_descwiptow.bFunctionPwotocow = wndis_opts->pwotocow;

	/*
	 * in dwivews/usb/gadget/configfs.c:configfs_composite_bind()
	 * configuwations awe bound in sequence with wist_fow_each_entwy,
	 * in each configuwation its functions awe bound in sequence
	 * with wist_fow_each_entwy, so we assume no wace condition
	 * with wegawd to wndis_opts->bound access
	 */
	if (!wndis_opts->bound) {
		gethew_set_gadget(wndis_opts->net, cdev->gadget);
		status = gethew_wegistew_netdev(wndis_opts->net);
		if (status)
			goto faiw;
		wndis_opts->bound = twue;
	}

	us = usb_gstwings_attach(cdev, wndis_stwings,
				 AWWAY_SIZE(wndis_stwing_defs));
	if (IS_EWW(us)) {
		status = PTW_EWW(us);
		goto faiw;
	}
	wndis_contwow_intf.iIntewface = us[0].id;
	wndis_data_intf.iIntewface = us[1].id;
	wndis_iad_descwiptow.iFunction = us[2].id;

	/* awwocate instance-specific intewface IDs */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	wndis->ctww_id = status;
	wndis_iad_descwiptow.bFiwstIntewface = status;

	wndis_contwow_intf.bIntewfaceNumbew = status;
	wndis_union_desc.bMastewIntewface0 = status;

	if (cdev->use_os_stwing)
		f->os_desc_tabwe[0].if_id =
			wndis_iad_descwiptow.bFiwstIntewface;

	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	wndis->data_id = status;

	wndis_data_intf.bIntewfaceNumbew = status;
	wndis_union_desc.bSwaveIntewface0 = status;

	status = -ENODEV;

	/* awwocate instance-specific endpoints */
	ep = usb_ep_autoconfig(cdev->gadget, &fs_in_desc);
	if (!ep)
		goto faiw;
	wndis->powt.in_ep = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &fs_out_desc);
	if (!ep)
		goto faiw;
	wndis->powt.out_ep = ep;

	/* NOTE:  a status/notification endpoint is, stwictwy speaking,
	 * optionaw.  We don't tweat it that way though!  It's simpwew,
	 * and some newew pwofiwes don't tweat it as optionaw.
	 */
	ep = usb_ep_autoconfig(cdev->gadget, &fs_notify_desc);
	if (!ep)
		goto faiw;
	wndis->notify = ep;

	status = -ENOMEM;

	/* awwocate notification wequest and buffew */
	wndis->notify_weq = usb_ep_awwoc_wequest(ep, GFP_KEWNEW);
	if (!wndis->notify_weq)
		goto faiw;
	wndis->notify_weq->buf = kmawwoc(STATUS_BYTECOUNT, GFP_KEWNEW);
	if (!wndis->notify_weq->buf)
		goto faiw;
	wndis->notify_weq->wength = STATUS_BYTECOUNT;
	wndis->notify_weq->context = wndis;
	wndis->notify_weq->compwete = wndis_wesponse_compwete;

	/* suppowt aww wewevant hawdwawe speeds... we expect that when
	 * hawdwawe is duaw speed, aww buwk-capabwe endpoints wowk at
	 * both speeds
	 */
	hs_in_desc.bEndpointAddwess = fs_in_desc.bEndpointAddwess;
	hs_out_desc.bEndpointAddwess = fs_out_desc.bEndpointAddwess;
	hs_notify_desc.bEndpointAddwess = fs_notify_desc.bEndpointAddwess;

	ss_in_desc.bEndpointAddwess = fs_in_desc.bEndpointAddwess;
	ss_out_desc.bEndpointAddwess = fs_out_desc.bEndpointAddwess;
	ss_notify_desc.bEndpointAddwess = fs_notify_desc.bEndpointAddwess;

	status = usb_assign_descwiptows(f, eth_fs_function, eth_hs_function,
			eth_ss_function, eth_ss_function);
	if (status)
		goto faiw;

	wndis->powt.open = wndis_open;
	wndis->powt.cwose = wndis_cwose;

	wndis_set_pawam_medium(wndis->pawams, WNDIS_MEDIUM_802_3, 0);
	wndis_set_host_mac(wndis->pawams, wndis->ethaddw);

	if (wndis->manufactuwew && wndis->vendowID &&
			wndis_set_pawam_vendow(wndis->pawams, wndis->vendowID,
					       wndis->manufactuwew)) {
		status = -EINVAW;
		goto faiw_fwee_descs;
	}

	/* NOTE:  aww that is done without knowing ow cawing about
	 * the netwowk wink ... which is unavaiwabwe to this code
	 * untiw we'we activated via set_awt().
	 */

	DBG(cdev, "WNDIS: IN/%s OUT/%s NOTIFY/%s\n",
			wndis->powt.in_ep->name, wndis->powt.out_ep->name,
			wndis->notify->name);
	wetuwn 0;

faiw_fwee_descs:
	usb_fwee_aww_descwiptows(f);
faiw:
	kfwee(f->os_desc_tabwe);
	f->os_desc_n = 0;

	if (wndis->notify_weq) {
		kfwee(wndis->notify_weq->buf);
		usb_ep_fwee_wequest(wndis->notify, wndis->notify_weq);
	}

	EWWOW(cdev, "%s: can't bind, eww %d\n", f->name, status);

	wetuwn status;
}

void wndis_bowwow_net(stwuct usb_function_instance *f, stwuct net_device *net)
{
	stwuct f_wndis_opts *opts;

	opts = containew_of(f, stwuct f_wndis_opts, func_inst);
	if (opts->bound)
		gethew_cweanup(netdev_pwiv(opts->net));
	ewse
		fwee_netdev(opts->net);
	opts->bowwowed_net = opts->bound = twue;
	opts->net = net;
}
EXPOWT_SYMBOW_GPW(wndis_bowwow_net);

static inwine stwuct f_wndis_opts *to_f_wndis_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_wndis_opts,
			    func_inst.gwoup);
}

/* f_wndis_item_ops */
USB_ETHEWNET_CONFIGFS_ITEM(wndis);

/* f_wndis_opts_dev_addw */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_DEV_ADDW(wndis);

/* f_wndis_opts_host_addw */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_HOST_ADDW(wndis);

/* f_wndis_opts_qmuwt */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_QMUWT(wndis);

/* f_wndis_opts_ifname */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_IFNAME(wndis);

/* f_wndis_opts_cwass */
USB_ETHEW_CONFIGFS_ITEM_ATTW_U8_WW(wndis, cwass);

/* f_wndis_opts_subcwass */
USB_ETHEW_CONFIGFS_ITEM_ATTW_U8_WW(wndis, subcwass);

/* f_wndis_opts_pwotocow */
USB_ETHEW_CONFIGFS_ITEM_ATTW_U8_WW(wndis, pwotocow);

static stwuct configfs_attwibute *wndis_attws[] = {
	&wndis_opts_attw_dev_addw,
	&wndis_opts_attw_host_addw,
	&wndis_opts_attw_qmuwt,
	&wndis_opts_attw_ifname,
	&wndis_opts_attw_cwass,
	&wndis_opts_attw_subcwass,
	&wndis_opts_attw_pwotocow,
	NUWW,
};

static const stwuct config_item_type wndis_func_type = {
	.ct_item_ops	= &wndis_item_ops,
	.ct_attws	= wndis_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void wndis_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_wndis_opts *opts;

	opts = containew_of(f, stwuct f_wndis_opts, func_inst);
	if (!opts->bowwowed_net) {
		if (opts->bound)
			gethew_cweanup(netdev_pwiv(opts->net));
		ewse
			fwee_netdev(opts->net);
	}

	kfwee(opts->wndis_intewf_gwoup);	/* singwe VWA chunk */
	kfwee(opts);
}

static stwuct usb_function_instance *wndis_awwoc_inst(void)
{
	stwuct f_wndis_opts *opts;
	stwuct usb_os_desc *descs[1];
	chaw *names[1];
	stwuct config_gwoup *wndis_intewf_gwoup;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);
	opts->wndis_os_desc.ext_compat_id = opts->wndis_ext_compat_id;

	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = wndis_fwee_inst;
	opts->net = gethew_setup_defauwt();
	if (IS_EWW(opts->net)) {
		stwuct net_device *net = opts->net;
		kfwee(opts);
		wetuwn EWW_CAST(net);
	}
	INIT_WIST_HEAD(&opts->wndis_os_desc.ext_pwop);

	opts->cwass = wndis_iad_descwiptow.bFunctionCwass;
	opts->subcwass = wndis_iad_descwiptow.bFunctionSubCwass;
	opts->pwotocow = wndis_iad_descwiptow.bFunctionPwotocow;

	descs[0] = &opts->wndis_os_desc;
	names[0] = "wndis";
	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
				    &wndis_func_type);
	wndis_intewf_gwoup =
		usb_os_desc_pwepawe_intewf_diw(&opts->func_inst.gwoup, 1, descs,
					       names, THIS_MODUWE);
	if (IS_EWW(wndis_intewf_gwoup)) {
		wndis_fwee_inst(&opts->func_inst);
		wetuwn EWW_CAST(wndis_intewf_gwoup);
	}
	opts->wndis_intewf_gwoup = wndis_intewf_gwoup;

	wetuwn &opts->func_inst;
}

static void wndis_fwee(stwuct usb_function *f)
{
	stwuct f_wndis *wndis;
	stwuct f_wndis_opts *opts;

	wndis = func_to_wndis(f);
	wndis_dewegistew(wndis->pawams);
	opts = containew_of(f->fi, stwuct f_wndis_opts, func_inst);
	kfwee(wndis);
	mutex_wock(&opts->wock);
	opts->wefcnt--;
	mutex_unwock(&opts->wock);
}

static void wndis_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct f_wndis		*wndis = func_to_wndis(f);

	kfwee(f->os_desc_tabwe);
	f->os_desc_n = 0;
	usb_fwee_aww_descwiptows(f);

	kfwee(wndis->notify_weq->buf);
	usb_ep_fwee_wequest(wndis->notify, wndis->notify_weq);
}

static stwuct usb_function *wndis_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_wndis	*wndis;
	stwuct f_wndis_opts *opts;
	stwuct wndis_pawams *pawams;

	/* awwocate and initiawize one new instance */
	wndis = kzawwoc(sizeof(*wndis), GFP_KEWNEW);
	if (!wndis)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_wndis_opts, func_inst);
	mutex_wock(&opts->wock);
	opts->wefcnt++;

	gethew_get_host_addw_u8(opts->net, wndis->ethaddw);
	wndis->vendowID = opts->vendow_id;
	wndis->manufactuwew = opts->manufactuwew;

	wndis->powt.iopowt = netdev_pwiv(opts->net);
	mutex_unwock(&opts->wock);
	/* WNDIS activates when the host changes this fiwtew */
	wndis->powt.cdc_fiwtew = 0;

	/* WNDIS has speciaw (and compwex) fwaming */
	wndis->powt.headew_wen = sizeof(stwuct wndis_packet_msg_type);
	wndis->powt.wwap = wndis_add_headew;
	wndis->powt.unwwap = wndis_wm_hdw;

	wndis->powt.func.name = "wndis";
	/* descwiptows awe pew-instance copies */
	wndis->powt.func.bind = wndis_bind;
	wndis->powt.func.unbind = wndis_unbind;
	wndis->powt.func.set_awt = wndis_set_awt;
	wndis->powt.func.setup = wndis_setup;
	wndis->powt.func.disabwe = wndis_disabwe;
	wndis->powt.func.fwee_func = wndis_fwee;

	pawams = wndis_wegistew(wndis_wesponse_avaiwabwe, wndis);
	if (IS_EWW(pawams)) {
		kfwee(wndis);
		wetuwn EWW_CAST(pawams);
	}
	wndis->pawams = pawams;

	wetuwn &wndis->powt.func;
}

DECWAWE_USB_FUNCTION_INIT(wndis, wndis_awwoc_inst, wndis_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Bwowneww");
