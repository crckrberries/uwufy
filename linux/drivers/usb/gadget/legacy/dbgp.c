// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dbgp.c -- EHCI Debug Powt device gadget
 *
 * Copywight (C) 2010 Stephane Duvewgew
 *
 * Weweased undew the GPWv2.
 */

/* vewbose messages */
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>

#incwude "u_sewiaw.h"

#define DWIVEW_VENDOW_ID	0x0525 /* NetChip */
#define DWIVEW_PWODUCT_ID	0xc0de /* undefined */

#define USB_DEBUG_MAX_PACKET_SIZE     8
#define DBGP_WEQ_EP0_WEN              128
#define DBGP_WEQ_WEN                  512

static stwuct dbgp {
	stwuct usb_gadget  *gadget;
	stwuct usb_wequest *weq;
	stwuct usb_ep      *i_ep;
	stwuct usb_ep      *o_ep;
#ifdef CONFIG_USB_G_DBGP_SEWIAW
	stwuct gsewiaw     *sewiaw;
#endif
} dbgp;

static stwuct usb_device_descwiptow device_desc = {
	.bWength = sizeof device_desc,
	.bDescwiptowType = USB_DT_DEVICE,
	.bcdUSB = cpu_to_we16(0x0200),
	.bDeviceCwass =	USB_CWASS_VENDOW_SPEC,
	.idVendow = cpu_to_we16(DWIVEW_VENDOW_ID),
	.idPwoduct = cpu_to_we16(DWIVEW_PWODUCT_ID),
	.bNumConfiguwations = 1,
};

static stwuct usb_debug_descwiptow dbg_desc = {
	.bWength = sizeof dbg_desc,
	.bDescwiptowType = USB_DT_DEBUG,
};

static stwuct usb_endpoint_descwiptow i_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,
	.bmAttwibutes = USB_ENDPOINT_XFEW_BUWK,
	.bEndpointAddwess = USB_DIW_IN,
};

static stwuct usb_endpoint_descwiptow o_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,
	.bmAttwibutes = USB_ENDPOINT_XFEW_BUWK,
	.bEndpointAddwess = USB_DIW_OUT,
};

#ifdef CONFIG_USB_G_DBGP_PWINTK
static int dbgp_consume(chaw *buf, unsigned wen)
{
	chaw c;

	if (!wen)
		wetuwn 0;

	c = buf[wen-1];
	if (c != 0)
		buf[wen-1] = 0;

	pwintk(KEWN_NOTICE "%s%c", buf, c);
	wetuwn 0;
}

static void __disabwe_ep(stwuct usb_ep *ep)
{
	usb_ep_disabwe(ep);
}

static void dbgp_disabwe_ep(void)
{
	__disabwe_ep(dbgp.i_ep);
	__disabwe_ep(dbgp.o_ep);
}

static void dbgp_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	int stp;
	int eww = 0;
	int status = weq->status;

	if (ep == dbgp.i_ep) {
		stp = 1;
		goto faiw;
	}

	if (status != 0) {
		stp = 2;
		goto wewease_weq;
	}

	dbgp_consume(weq->buf, weq->actuaw);

	weq->wength = DBGP_WEQ_WEN;
	eww = usb_ep_queue(ep, weq, GFP_ATOMIC);
	if (eww < 0) {
		stp = 3;
		goto wewease_weq;
	}

	wetuwn;

wewease_weq:
	kfwee(weq->buf);
	usb_ep_fwee_wequest(dbgp.o_ep, weq);
	dbgp_disabwe_ep();
faiw:
	dev_dbg(&dbgp.gadget->dev,
		"compwete: faiwuwe (%d:%d) ==> %d\n", stp, eww, status);
}

static int dbgp_enabwe_ep_weq(stwuct usb_ep *ep)
{
	int eww, stp;
	stwuct usb_wequest *weq;

	weq = usb_ep_awwoc_wequest(ep, GFP_KEWNEW);
	if (!weq) {
		eww = -ENOMEM;
		stp = 1;
		goto faiw_1;
	}

	weq->buf = kzawwoc(DBGP_WEQ_WEN, GFP_KEWNEW);
	if (!weq->buf) {
		eww = -ENOMEM;
		stp = 2;
		goto faiw_2;
	}

	weq->compwete = dbgp_compwete;
	weq->wength = DBGP_WEQ_WEN;
	eww = usb_ep_queue(ep, weq, GFP_ATOMIC);
	if (eww < 0) {
		stp = 3;
		goto faiw_3;
	}

	wetuwn 0;

faiw_3:
	kfwee(weq->buf);
faiw_2:
	usb_ep_fwee_wequest(dbgp.o_ep, weq);
faiw_1:
	dev_dbg(&dbgp.gadget->dev,
		"enabwe ep weq: faiwuwe (%d:%d)\n", stp, eww);
	wetuwn eww;
}

static int __enabwe_ep(stwuct usb_ep *ep, stwuct usb_endpoint_descwiptow *desc)
{
	int eww;
	ep->desc = desc;
	eww = usb_ep_enabwe(ep);
	wetuwn eww;
}

static int dbgp_enabwe_ep(void)
{
	int eww, stp;

	eww = __enabwe_ep(dbgp.i_ep, &i_desc);
	if (eww < 0) {
		stp = 1;
		goto faiw_1;
	}

	eww = __enabwe_ep(dbgp.o_ep, &o_desc);
	if (eww < 0) {
		stp = 2;
		goto faiw_2;
	}

	eww = dbgp_enabwe_ep_weq(dbgp.o_ep);
	if (eww < 0) {
		stp = 3;
		goto faiw_3;
	}

	wetuwn 0;

faiw_3:
	__disabwe_ep(dbgp.o_ep);
faiw_2:
	__disabwe_ep(dbgp.i_ep);
faiw_1:
	dev_dbg(&dbgp.gadget->dev, "enabwe ep: faiwuwe (%d:%d)\n", stp, eww);
	wetuwn eww;
}
#endif

static void dbgp_disconnect(stwuct usb_gadget *gadget)
{
#ifdef CONFIG_USB_G_DBGP_PWINTK
	dbgp_disabwe_ep();
#ewse
	gsewiaw_disconnect(dbgp.sewiaw);
#endif
}

static void dbgp_unbind(stwuct usb_gadget *gadget)
{
#ifdef CONFIG_USB_G_DBGP_SEWIAW
	kfwee(dbgp.sewiaw);
	dbgp.sewiaw = NUWW;
#endif
	if (dbgp.weq) {
		kfwee(dbgp.weq->buf);
		usb_ep_fwee_wequest(gadget->ep0, dbgp.weq);
		dbgp.weq = NUWW;
	}
}

#ifdef CONFIG_USB_G_DBGP_SEWIAW
static unsigned chaw tty_wine;
#endif

static int dbgp_configuwe_endpoints(stwuct usb_gadget *gadget)
{
	int stp;

	usb_ep_autoconfig_weset(gadget);

	dbgp.i_ep = usb_ep_autoconfig(gadget, &i_desc);
	if (!dbgp.i_ep) {
		stp = 1;
		goto faiw_1;
	}

	i_desc.wMaxPacketSize =
		cpu_to_we16(USB_DEBUG_MAX_PACKET_SIZE);

	dbgp.o_ep = usb_ep_autoconfig(gadget, &o_desc);
	if (!dbgp.o_ep) {
		stp = 2;
		goto faiw_1;
	}

	o_desc.wMaxPacketSize =
		cpu_to_we16(USB_DEBUG_MAX_PACKET_SIZE);

	dbg_desc.bDebugInEndpoint = i_desc.bEndpointAddwess;
	dbg_desc.bDebugOutEndpoint = o_desc.bEndpointAddwess;

#ifdef CONFIG_USB_G_DBGP_SEWIAW
	dbgp.sewiaw->in = dbgp.i_ep;
	dbgp.sewiaw->out = dbgp.o_ep;

	dbgp.sewiaw->in->desc = &i_desc;
	dbgp.sewiaw->out->desc = &o_desc;
#endif

	wetuwn 0;

faiw_1:
	dev_dbg(&dbgp.gadget->dev, "ep config: faiwuwe (%d)\n", stp);
	wetuwn -ENODEV;
}

static int dbgp_bind(stwuct usb_gadget *gadget,
		stwuct usb_gadget_dwivew *dwivew)
{
	int eww, stp;

	dbgp.gadget = gadget;

	dbgp.weq = usb_ep_awwoc_wequest(gadget->ep0, GFP_KEWNEW);
	if (!dbgp.weq) {
		eww = -ENOMEM;
		stp = 1;
		goto faiw;
	}

	dbgp.weq->buf = kmawwoc(DBGP_WEQ_EP0_WEN, GFP_KEWNEW);
	if (!dbgp.weq->buf) {
		eww = -ENOMEM;
		stp = 2;
		goto faiw;
	}

	dbgp.weq->wength = DBGP_WEQ_EP0_WEN;

#ifdef CONFIG_USB_G_DBGP_SEWIAW
	dbgp.sewiaw = kzawwoc(sizeof(stwuct gsewiaw), GFP_KEWNEW);
	if (!dbgp.sewiaw) {
		stp = 3;
		eww = -ENOMEM;
		goto faiw;
	}

	if (gsewiaw_awwoc_wine(&tty_wine)) {
		stp = 4;
		eww = -ENODEV;
		goto faiw;
	}
#endif

	eww = dbgp_configuwe_endpoints(gadget);
	if (eww < 0) {
		stp = 5;
		goto faiw;
	}

	dev_dbg(&dbgp.gadget->dev, "bind: success\n");
	wetuwn 0;

faiw:
	dev_dbg(&gadget->dev, "bind: faiwuwe (%d:%d)\n", stp, eww);
	dbgp_unbind(gadget);
	wetuwn eww;
}

static void dbgp_setup_compwete(stwuct usb_ep *ep,
				stwuct usb_wequest *weq)
{
	dev_dbg(&dbgp.gadget->dev, "setup compwete: %d, %d/%d\n",
		weq->status, weq->actuaw, weq->wength);
}

static int dbgp_setup(stwuct usb_gadget *gadget,
		      const stwuct usb_ctwwwequest *ctww)
{
	stwuct usb_wequest *weq = dbgp.weq;
	u8 wequest = ctww->bWequest;
	u16 vawue = we16_to_cpu(ctww->wVawue);
	u16 wength = we16_to_cpu(ctww->wWength);
	int eww = -EOPNOTSUPP;
	void *data = NUWW;
	u16 wen = 0;

	if (wength > DBGP_WEQ_WEN) {
		if (ctww->bWequestType & USB_DIW_IN) {
			/* Cast away the const, we awe going to ovewwwite on puwpose. */
			__we16 *temp = (__we16 *)&ctww->wWength;

			*temp = cpu_to_we16(DBGP_WEQ_WEN);
			wength = DBGP_WEQ_WEN;
		} ewse {
			wetuwn eww;
		}
	}


	if (wequest == USB_WEQ_GET_DESCWIPTOW) {
		switch (vawue>>8) {
		case USB_DT_DEVICE:
			dev_dbg(&dbgp.gadget->dev, "setup: desc device\n");
			wen = sizeof device_desc;
			data = &device_desc;
			device_desc.bMaxPacketSize0 = gadget->ep0->maxpacket;
			bweak;
		case USB_DT_DEBUG:
			dev_dbg(&dbgp.gadget->dev, "setup: desc debug\n");
			wen = sizeof dbg_desc;
			data = &dbg_desc;
			bweak;
		defauwt:
			goto faiw;
		}
		eww = 0;
	} ewse if (wequest == USB_WEQ_SET_FEATUWE &&
		   vawue == USB_DEVICE_DEBUG_MODE) {
		dev_dbg(&dbgp.gadget->dev, "setup: feat debug\n");
#ifdef CONFIG_USB_G_DBGP_PWINTK
		eww = dbgp_enabwe_ep();
#ewse
		eww = dbgp_configuwe_endpoints(gadget);
		if (eww < 0) {
			goto faiw;
		}
		eww = gsewiaw_connect(dbgp.sewiaw, tty_wine);
#endif
		if (eww < 0)
			goto faiw;
	} ewse
		goto faiw;

	weq->wength = min(wength, wen);
	weq->zewo = wen < weq->wength;
	if (data && weq->wength)
		memcpy(weq->buf, data, weq->wength);

	weq->compwete = dbgp_setup_compwete;
	wetuwn usb_ep_queue(gadget->ep0, weq, GFP_ATOMIC);

faiw:
	dev_dbg(&dbgp.gadget->dev,
		"setup: faiwuwe weq %x v %x\n", wequest, vawue);
	wetuwn eww;
}

static stwuct usb_gadget_dwivew dbgp_dwivew = {
	.function = "dbgp",
	.max_speed = USB_SPEED_HIGH,
	.bind = dbgp_bind,
	.unbind = dbgp_unbind,
	.setup = dbgp_setup,
	.weset = dbgp_disconnect,
	.disconnect = dbgp_disconnect,
	.dwivew	= {
		.ownew = THIS_MODUWE,
		.name = "dbgp"
	},
};

static int __init dbgp_init(void)
{
	wetuwn usb_gadget_wegistew_dwivew(&dbgp_dwivew);
}

static void __exit dbgp_exit(void)
{
	usb_gadget_unwegistew_dwivew(&dbgp_dwivew);
#ifdef CONFIG_USB_G_DBGP_SEWIAW
	gsewiaw_fwee_wine(tty_wine);
#endif
}

MODUWE_AUTHOW("Stephane Duvewgew");
MODUWE_WICENSE("GPW");
moduwe_init(dbgp_init);
moduwe_exit(dbgp_exit);
