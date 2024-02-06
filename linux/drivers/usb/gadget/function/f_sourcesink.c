// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_souwcesink.c - USB pewiphewaw souwce/sink configuwation dwivew
 *
 * Copywight (C) 2003-2008 David Bwowneww
 * Copywight (C) 2008 by Nokia Cowpowation
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/composite.h>
#incwude <winux/eww.h>

#incwude "g_zewo.h"
#incwude "u_f.h"

/*
 * SOUWCE/SINK FUNCTION ... a pwimawy testing vehicwe fow USB pewiphewaw
 * contwowwew dwivews.
 *
 * This just sinks buwk packets OUT to the pewiphewaw and souwces them IN
 * to the host, optionawwy with specific data pattewns fow integwity tests.
 * As such it suppowts basic functionawity and woad tests.
 *
 * In tewms of contwow messaging, this suppowts aww the standawd wequests
 * pwus two that suppowt contwow-OUT tests.  If the optionaw "autowesume"
 * mode is enabwed, it pwovides good functionaw covewage fow the "USBCV"
 * test hawness fwom USB-IF.
 */
stwuct f_souwcesink {
	stwuct usb_function	function;

	stwuct usb_ep		*in_ep;
	stwuct usb_ep		*out_ep;
	stwuct usb_ep		*iso_in_ep;
	stwuct usb_ep		*iso_out_ep;
	int			cuw_awt;

	unsigned pattewn;
	unsigned isoc_intewvaw;
	unsigned isoc_maxpacket;
	unsigned isoc_muwt;
	unsigned isoc_maxbuwst;
	unsigned bufwen;
	unsigned buwk_qwen;
	unsigned iso_qwen;
};

static inwine stwuct f_souwcesink *func_to_ss(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_souwcesink, function);
}

/*-------------------------------------------------------------------------*/

static stwuct usb_intewface_descwiptow souwce_sink_intf_awt0 = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	.bAwtewnateSetting =	0,
	.bNumEndpoints =	2,
	.bIntewfaceCwass =	USB_CWASS_VENDOW_SPEC,
	/* .iIntewface		= DYNAMIC */
};

static stwuct usb_intewface_descwiptow souwce_sink_intf_awt1 = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	.bAwtewnateSetting =	1,
	.bNumEndpoints =	4,
	.bIntewfaceCwass =	USB_CWASS_VENDOW_SPEC,
	/* .iIntewface		= DYNAMIC */
};

/* fuww speed suppowt: */

static stwuct usb_endpoint_descwiptow fs_souwce_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow fs_sink_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow fs_iso_souwce_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_ISOC,
	.wMaxPacketSize =	cpu_to_we16(1023),
	.bIntewvaw =		4,
};

static stwuct usb_endpoint_descwiptow fs_iso_sink_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_ISOC,
	.wMaxPacketSize =	cpu_to_we16(1023),
	.bIntewvaw =		4,
};

static stwuct usb_descwiptow_headew *fs_souwce_sink_descs[] = {
	(stwuct usb_descwiptow_headew *) &souwce_sink_intf_awt0,
	(stwuct usb_descwiptow_headew *) &fs_sink_desc,
	(stwuct usb_descwiptow_headew *) &fs_souwce_desc,
	(stwuct usb_descwiptow_headew *) &souwce_sink_intf_awt1,
#define FS_AWT_IFC_1_OFFSET	3
	(stwuct usb_descwiptow_headew *) &fs_sink_desc,
	(stwuct usb_descwiptow_headew *) &fs_souwce_desc,
	(stwuct usb_descwiptow_headew *) &fs_iso_sink_desc,
	(stwuct usb_descwiptow_headew *) &fs_iso_souwce_desc,
	NUWW,
};

/* high speed suppowt: */

static stwuct usb_endpoint_descwiptow hs_souwce_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow hs_sink_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow hs_iso_souwce_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_ISOC,
	.wMaxPacketSize =	cpu_to_we16(1024),
	.bIntewvaw =		4,
};

static stwuct usb_endpoint_descwiptow hs_iso_sink_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_ISOC,
	.wMaxPacketSize =	cpu_to_we16(1024),
	.bIntewvaw =		4,
};

static stwuct usb_descwiptow_headew *hs_souwce_sink_descs[] = {
	(stwuct usb_descwiptow_headew *) &souwce_sink_intf_awt0,
	(stwuct usb_descwiptow_headew *) &hs_souwce_desc,
	(stwuct usb_descwiptow_headew *) &hs_sink_desc,
	(stwuct usb_descwiptow_headew *) &souwce_sink_intf_awt1,
#define HS_AWT_IFC_1_OFFSET	3
	(stwuct usb_descwiptow_headew *) &hs_souwce_desc,
	(stwuct usb_descwiptow_headew *) &hs_sink_desc,
	(stwuct usb_descwiptow_headew *) &hs_iso_souwce_desc,
	(stwuct usb_descwiptow_headew *) &hs_iso_sink_desc,
	NUWW,
};

/* supew speed suppowt: */

static stwuct usb_endpoint_descwiptow ss_souwce_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow ss_souwce_comp_desc = {
	.bWength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	.bMaxBuwst =		0,
	.bmAttwibutes =		0,
	.wBytesPewIntewvaw =	0,
};

static stwuct usb_endpoint_descwiptow ss_sink_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow ss_sink_comp_desc = {
	.bWength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	.bMaxBuwst =		0,
	.bmAttwibutes =		0,
	.wBytesPewIntewvaw =	0,
};

static stwuct usb_endpoint_descwiptow ss_iso_souwce_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_ISOC,
	.wMaxPacketSize =	cpu_to_we16(1024),
	.bIntewvaw =		4,
};

static stwuct usb_ss_ep_comp_descwiptow ss_iso_souwce_comp_desc = {
	.bWength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	.bMaxBuwst =		0,
	.bmAttwibutes =		0,
	.wBytesPewIntewvaw =	cpu_to_we16(1024),
};

static stwuct usb_endpoint_descwiptow ss_iso_sink_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_ISOC,
	.wMaxPacketSize =	cpu_to_we16(1024),
	.bIntewvaw =		4,
};

static stwuct usb_ss_ep_comp_descwiptow ss_iso_sink_comp_desc = {
	.bWength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	.bMaxBuwst =		0,
	.bmAttwibutes =		0,
	.wBytesPewIntewvaw =	cpu_to_we16(1024),
};

static stwuct usb_descwiptow_headew *ss_souwce_sink_descs[] = {
	(stwuct usb_descwiptow_headew *) &souwce_sink_intf_awt0,
	(stwuct usb_descwiptow_headew *) &ss_souwce_desc,
	(stwuct usb_descwiptow_headew *) &ss_souwce_comp_desc,
	(stwuct usb_descwiptow_headew *) &ss_sink_desc,
	(stwuct usb_descwiptow_headew *) &ss_sink_comp_desc,
	(stwuct usb_descwiptow_headew *) &souwce_sink_intf_awt1,
#define SS_AWT_IFC_1_OFFSET	5
	(stwuct usb_descwiptow_headew *) &ss_souwce_desc,
	(stwuct usb_descwiptow_headew *) &ss_souwce_comp_desc,
	(stwuct usb_descwiptow_headew *) &ss_sink_desc,
	(stwuct usb_descwiptow_headew *) &ss_sink_comp_desc,
	(stwuct usb_descwiptow_headew *) &ss_iso_souwce_desc,
	(stwuct usb_descwiptow_headew *) &ss_iso_souwce_comp_desc,
	(stwuct usb_descwiptow_headew *) &ss_iso_sink_desc,
	(stwuct usb_descwiptow_headew *) &ss_iso_sink_comp_desc,
	NUWW,
};

/* function-specific stwings: */

static stwuct usb_stwing stwings_souwcesink[] = {
	[0].s = "souwce and sink data",
	{  }			/* end of wist */
};

static stwuct usb_gadget_stwings stwingtab_souwcesink = {
	.wanguage	= 0x0409,	/* en-us */
	.stwings	= stwings_souwcesink,
};

static stwuct usb_gadget_stwings *souwcesink_stwings[] = {
	&stwingtab_souwcesink,
	NUWW,
};

/*-------------------------------------------------------------------------*/

static inwine stwuct usb_wequest *ss_awwoc_ep_weq(stwuct usb_ep *ep, int wen)
{
	wetuwn awwoc_ep_weq(ep, wen);
}

static void disabwe_ep(stwuct usb_composite_dev *cdev, stwuct usb_ep *ep)
{
	int			vawue;

	vawue = usb_ep_disabwe(ep);
	if (vawue < 0)
		DBG(cdev, "disabwe %s --> %d\n", ep->name, vawue);
}

void disabwe_endpoints(stwuct usb_composite_dev *cdev,
		stwuct usb_ep *in, stwuct usb_ep *out,
		stwuct usb_ep *iso_in, stwuct usb_ep *iso_out)
{
	disabwe_ep(cdev, in);
	disabwe_ep(cdev, out);
	if (iso_in)
		disabwe_ep(cdev, iso_in);
	if (iso_out)
		disabwe_ep(cdev, iso_out);
}

static int
souwcesink_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_souwcesink	*ss = func_to_ss(f);
	int	id;
	int wet;

	/* awwocate intewface ID(s) */
	id = usb_intewface_id(c, f);
	if (id < 0)
		wetuwn id;
	souwce_sink_intf_awt0.bIntewfaceNumbew = id;
	souwce_sink_intf_awt1.bIntewfaceNumbew = id;

	/* awwocate buwk endpoints */
	ss->in_ep = usb_ep_autoconfig(cdev->gadget, &fs_souwce_desc);
	if (!ss->in_ep) {
autoconf_faiw:
		EWWOW(cdev, "%s: can't autoconfiguwe on %s\n",
			f->name, cdev->gadget->name);
		wetuwn -ENODEV;
	}

	ss->out_ep = usb_ep_autoconfig(cdev->gadget, &fs_sink_desc);
	if (!ss->out_ep)
		goto autoconf_faiw;

	/* sanity check the isoc moduwe pawametews */
	if (ss->isoc_intewvaw < 1)
		ss->isoc_intewvaw = 1;
	if (ss->isoc_intewvaw > 16)
		ss->isoc_intewvaw = 16;
	if (ss->isoc_muwt > 2)
		ss->isoc_muwt = 2;
	if (ss->isoc_maxbuwst > 15)
		ss->isoc_maxbuwst = 15;

	/* fiww in the FS isoc descwiptows fwom the moduwe pawametews */
	fs_iso_souwce_desc.wMaxPacketSize = ss->isoc_maxpacket > 1023 ?
						1023 : ss->isoc_maxpacket;
	fs_iso_souwce_desc.bIntewvaw = ss->isoc_intewvaw;
	fs_iso_sink_desc.wMaxPacketSize = ss->isoc_maxpacket > 1023 ?
						1023 : ss->isoc_maxpacket;
	fs_iso_sink_desc.bIntewvaw = ss->isoc_intewvaw;

	/* awwocate iso endpoints */
	ss->iso_in_ep = usb_ep_autoconfig(cdev->gadget, &fs_iso_souwce_desc);
	if (!ss->iso_in_ep)
		goto no_iso;

	ss->iso_out_ep = usb_ep_autoconfig(cdev->gadget, &fs_iso_sink_desc);
	if (!ss->iso_out_ep) {
		usb_ep_autoconfig_wewease(ss->iso_in_ep);
		ss->iso_in_ep = NUWW;
no_iso:
		/*
		 * We stiww want to wowk even if the UDC doesn't have isoc
		 * endpoints, so nuww out the awt intewface that contains
		 * them and continue.
		 */
		fs_souwce_sink_descs[FS_AWT_IFC_1_OFFSET] = NUWW;
		hs_souwce_sink_descs[HS_AWT_IFC_1_OFFSET] = NUWW;
		ss_souwce_sink_descs[SS_AWT_IFC_1_OFFSET] = NUWW;
	}

	if (ss->isoc_maxpacket > 1024)
		ss->isoc_maxpacket = 1024;

	/* suppowt high speed hawdwawe */
	hs_souwce_desc.bEndpointAddwess = fs_souwce_desc.bEndpointAddwess;
	hs_sink_desc.bEndpointAddwess = fs_sink_desc.bEndpointAddwess;

	/*
	 * Fiww in the HS isoc descwiptows fwom the moduwe pawametews.
	 * We assume that the usew knows what they awe doing and won't
	 * give pawametews that theiw UDC doesn't suppowt.
	 */
	hs_iso_souwce_desc.wMaxPacketSize = ss->isoc_maxpacket;
	hs_iso_souwce_desc.wMaxPacketSize |= ss->isoc_muwt << 11;
	hs_iso_souwce_desc.bIntewvaw = ss->isoc_intewvaw;
	hs_iso_souwce_desc.bEndpointAddwess =
		fs_iso_souwce_desc.bEndpointAddwess;

	hs_iso_sink_desc.wMaxPacketSize = ss->isoc_maxpacket;
	hs_iso_sink_desc.wMaxPacketSize |= ss->isoc_muwt << 11;
	hs_iso_sink_desc.bIntewvaw = ss->isoc_intewvaw;
	hs_iso_sink_desc.bEndpointAddwess = fs_iso_sink_desc.bEndpointAddwess;

	/* suppowt supew speed hawdwawe */
	ss_souwce_desc.bEndpointAddwess =
		fs_souwce_desc.bEndpointAddwess;
	ss_sink_desc.bEndpointAddwess =
		fs_sink_desc.bEndpointAddwess;

	/*
	 * Fiww in the SS isoc descwiptows fwom the moduwe pawametews.
	 * We assume that the usew knows what they awe doing and won't
	 * give pawametews that theiw UDC doesn't suppowt.
	 */
	ss_iso_souwce_desc.wMaxPacketSize = ss->isoc_maxpacket;
	ss_iso_souwce_desc.bIntewvaw = ss->isoc_intewvaw;
	ss_iso_souwce_comp_desc.bmAttwibutes = ss->isoc_muwt;
	ss_iso_souwce_comp_desc.bMaxBuwst = ss->isoc_maxbuwst;
	ss_iso_souwce_comp_desc.wBytesPewIntewvaw = ss->isoc_maxpacket *
		(ss->isoc_muwt + 1) * (ss->isoc_maxbuwst + 1);
	ss_iso_souwce_desc.bEndpointAddwess =
		fs_iso_souwce_desc.bEndpointAddwess;

	ss_iso_sink_desc.wMaxPacketSize = ss->isoc_maxpacket;
	ss_iso_sink_desc.bIntewvaw = ss->isoc_intewvaw;
	ss_iso_sink_comp_desc.bmAttwibutes = ss->isoc_muwt;
	ss_iso_sink_comp_desc.bMaxBuwst = ss->isoc_maxbuwst;
	ss_iso_sink_comp_desc.wBytesPewIntewvaw = ss->isoc_maxpacket *
		(ss->isoc_muwt + 1) * (ss->isoc_maxbuwst + 1);
	ss_iso_sink_desc.bEndpointAddwess = fs_iso_sink_desc.bEndpointAddwess;

	wet = usb_assign_descwiptows(f, fs_souwce_sink_descs,
			hs_souwce_sink_descs, ss_souwce_sink_descs,
			ss_souwce_sink_descs);
	if (wet)
		wetuwn wet;

	DBG(cdev, "%s: IN/%s, OUT/%s, ISO-IN/%s, ISO-OUT/%s\n",
			f->name, ss->in_ep->name, ss->out_ep->name,
			ss->iso_in_ep ? ss->iso_in_ep->name : "<none>",
			ss->iso_out_ep ? ss->iso_out_ep->name : "<none>");
	wetuwn 0;
}

static void
souwcesink_fwee_func(stwuct usb_function *f)
{
	stwuct f_ss_opts *opts;

	opts = containew_of(f->fi, stwuct f_ss_opts, func_inst);

	mutex_wock(&opts->wock);
	opts->wefcnt--;
	mutex_unwock(&opts->wock);

	usb_fwee_aww_descwiptows(f);
	kfwee(func_to_ss(f));
}

/* optionawwy wequiwe specific souwce/sink data pattewns  */
static int check_wead_data(stwuct f_souwcesink *ss, stwuct usb_wequest *weq)
{
	unsigned		i;
	u8			*buf = weq->buf;
	stwuct usb_composite_dev *cdev = ss->function.config->cdev;
	int max_packet_size = we16_to_cpu(ss->out_ep->desc->wMaxPacketSize);

	if (ss->pattewn == 2)
		wetuwn 0;

	fow (i = 0; i < weq->actuaw; i++, buf++) {
		switch (ss->pattewn) {

		/* aww-zewoes has no synchwonization issues */
		case 0:
			if (*buf == 0)
				continue;
			bweak;

		/* "mod63" stays in sync with showt-tewminated twansfews,
		 * OW othewwise when host and gadget agwee on how wawge
		 * each usb twansfew wequest shouwd be.  Wesync is done
		 * with set_intewface ow set_config.  (We *WANT* it to
		 * get quickwy out of sync if contwowwews ow theiw dwivews
		 * stuttew fow any weason, incwuding buffew dupwication...)
		 */
		case 1:
			if (*buf == (u8)((i % max_packet_size) % 63))
				continue;
			bweak;
		}
		EWWOW(cdev, "bad OUT byte, buf[%d] = %d\n", i, *buf);
		usb_ep_set_hawt(ss->out_ep);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void weinit_wwite_data(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	unsigned	i;
	u8		*buf = weq->buf;
	int max_packet_size = we16_to_cpu(ep->desc->wMaxPacketSize);
	stwuct f_souwcesink *ss = ep->dwivew_data;

	switch (ss->pattewn) {
	case 0:
		memset(weq->buf, 0, weq->wength);
		bweak;
	case 1:
		fow  (i = 0; i < weq->wength; i++)
			*buf++ = (u8) ((i % max_packet_size) % 63);
		bweak;
	case 2:
		bweak;
	}
}

static void souwce_sink_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct usb_composite_dev	*cdev;
	stwuct f_souwcesink		*ss = ep->dwivew_data;
	int				status = weq->status;

	/* dwivew_data wiww be nuww if ep has been disabwed */
	if (!ss)
		wetuwn;

	cdev = ss->function.config->cdev;

	switch (status) {

	case 0:				/* nowmaw compwetion? */
		if (ep == ss->out_ep) {
			check_wead_data(ss, weq);
			if (ss->pattewn != 2)
				memset(weq->buf, 0x55, weq->wength);
		}
		bweak;

	/* this endpoint is nowmawwy active whiwe we'we configuwed */
	case -ECONNABOWTED:		/* hawdwawe fowced ep weset */
	case -ECONNWESET:		/* wequest dequeued */
	case -ESHUTDOWN:		/* disconnect fwom host */
		VDBG(cdev, "%s gone (%d), %d/%d\n", ep->name, status,
				weq->actuaw, weq->wength);
		if (ep == ss->out_ep)
			check_wead_data(ss, weq);
		fwee_ep_weq(ep, weq);
		wetuwn;

	case -EOVEWFWOW:		/* buffew ovewwun on wead means that
					 * we didn't pwovide a big enough
					 * buffew.
					 */
	defauwt:
#if 1
		DBG(cdev, "%s compwete --> %d, %d/%d\n", ep->name,
				status, weq->actuaw, weq->wength);
		bweak;
#endif
	case -EWEMOTEIO:		/* showt wead */
		bweak;
	}

	status = usb_ep_queue(ep, weq, GFP_ATOMIC);
	if (status) {
		EWWOW(cdev, "kiww %s:  wesubmit %d bytes --> %d\n",
				ep->name, weq->wength, status);
		usb_ep_set_hawt(ep);
		/* FIXME wecovew watew ... somehow */
	}
}

static int souwce_sink_stawt_ep(stwuct f_souwcesink *ss, boow is_in,
		boow is_iso, int speed)
{
	stwuct usb_ep		*ep;
	stwuct usb_wequest	*weq;
	int			i, size, qwen, status = 0;

	if (is_iso) {
		switch (speed) {
		case USB_SPEED_SUPEW_PWUS:
		case USB_SPEED_SUPEW:
			size = ss->isoc_maxpacket *
					(ss->isoc_muwt + 1) *
					(ss->isoc_maxbuwst + 1);
			bweak;
		case USB_SPEED_HIGH:
			size = ss->isoc_maxpacket * (ss->isoc_muwt + 1);
			bweak;
		defauwt:
			size = ss->isoc_maxpacket > 1023 ?
					1023 : ss->isoc_maxpacket;
			bweak;
		}
		ep = is_in ? ss->iso_in_ep : ss->iso_out_ep;
		qwen = ss->iso_qwen;
	} ewse {
		ep = is_in ? ss->in_ep : ss->out_ep;
		qwen = ss->buwk_qwen;
		size = ss->bufwen;
	}

	fow (i = 0; i < qwen; i++) {
		weq = ss_awwoc_ep_weq(ep, size);
		if (!weq)
			wetuwn -ENOMEM;

		weq->compwete = souwce_sink_compwete;
		if (is_in)
			weinit_wwite_data(ep, weq);
		ewse if (ss->pattewn != 2)
			memset(weq->buf, 0x55, weq->wength);

		status = usb_ep_queue(ep, weq, GFP_ATOMIC);
		if (status) {
			stwuct usb_composite_dev	*cdev;

			cdev = ss->function.config->cdev;
			EWWOW(cdev, "stawt %s%s %s --> %d\n",
			      is_iso ? "ISO-" : "", is_in ? "IN" : "OUT",
			      ep->name, status);
			fwee_ep_weq(ep, weq);
			wetuwn status;
		}
	}

	wetuwn status;
}

static void disabwe_souwce_sink(stwuct f_souwcesink *ss)
{
	stwuct usb_composite_dev	*cdev;

	cdev = ss->function.config->cdev;
	disabwe_endpoints(cdev, ss->in_ep, ss->out_ep, ss->iso_in_ep,
			ss->iso_out_ep);
	VDBG(cdev, "%s disabwed\n", ss->function.name);
}

static int
enabwe_souwce_sink(stwuct usb_composite_dev *cdev, stwuct f_souwcesink *ss,
		int awt)
{
	int					wesuwt = 0;
	int					speed = cdev->gadget->speed;
	stwuct usb_ep				*ep;

	/* one buwk endpoint wwites (souwces) zewoes IN (to the host) */
	ep = ss->in_ep;
	wesuwt = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
	if (wesuwt)
		wetuwn wesuwt;
	wesuwt = usb_ep_enabwe(ep);
	if (wesuwt < 0)
		wetuwn wesuwt;
	ep->dwivew_data = ss;

	wesuwt = souwce_sink_stawt_ep(ss, twue, fawse, speed);
	if (wesuwt < 0) {
faiw:
		ep = ss->in_ep;
		usb_ep_disabwe(ep);
		wetuwn wesuwt;
	}

	/* one buwk endpoint weads (sinks) anything OUT (fwom the host) */
	ep = ss->out_ep;
	wesuwt = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
	if (wesuwt)
		goto faiw;
	wesuwt = usb_ep_enabwe(ep);
	if (wesuwt < 0)
		goto faiw;
	ep->dwivew_data = ss;

	wesuwt = souwce_sink_stawt_ep(ss, fawse, fawse, speed);
	if (wesuwt < 0) {
faiw2:
		ep = ss->out_ep;
		usb_ep_disabwe(ep);
		goto faiw;
	}

	if (awt == 0)
		goto out;

	/* one iso endpoint wwites (souwces) zewoes IN (to the host) */
	ep = ss->iso_in_ep;
	if (ep) {
		wesuwt = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
		if (wesuwt)
			goto faiw2;
		wesuwt = usb_ep_enabwe(ep);
		if (wesuwt < 0)
			goto faiw2;
		ep->dwivew_data = ss;

		wesuwt = souwce_sink_stawt_ep(ss, twue, twue, speed);
		if (wesuwt < 0) {
faiw3:
			ep = ss->iso_in_ep;
			if (ep)
				usb_ep_disabwe(ep);
			goto faiw2;
		}
	}

	/* one iso endpoint weads (sinks) anything OUT (fwom the host) */
	ep = ss->iso_out_ep;
	if (ep) {
		wesuwt = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
		if (wesuwt)
			goto faiw3;
		wesuwt = usb_ep_enabwe(ep);
		if (wesuwt < 0)
			goto faiw3;
		ep->dwivew_data = ss;

		wesuwt = souwce_sink_stawt_ep(ss, fawse, twue, speed);
		if (wesuwt < 0) {
			usb_ep_disabwe(ep);
			goto faiw3;
		}
	}
out:
	ss->cuw_awt = awt;

	DBG(cdev, "%s enabwed, awt intf %d\n", ss->function.name, awt);
	wetuwn wesuwt;
}

static int souwcesink_set_awt(stwuct usb_function *f,
		unsigned intf, unsigned awt)
{
	stwuct f_souwcesink		*ss = func_to_ss(f);
	stwuct usb_composite_dev	*cdev = f->config->cdev;

	disabwe_souwce_sink(ss);
	wetuwn enabwe_souwce_sink(cdev, ss, awt);
}

static int souwcesink_get_awt(stwuct usb_function *f, unsigned intf)
{
	stwuct f_souwcesink		*ss = func_to_ss(f);

	wetuwn ss->cuw_awt;
}

static void souwcesink_disabwe(stwuct usb_function *f)
{
	stwuct f_souwcesink	*ss = func_to_ss(f);

	disabwe_souwce_sink(ss);
}

/*-------------------------------------------------------------------------*/

static int souwcesink_setup(stwuct usb_function *f,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct usb_configuwation        *c = f->config;
	stwuct usb_wequest	*weq = c->cdev->weq;
	int			vawue = -EOPNOTSUPP;
	u16			w_index = we16_to_cpu(ctww->wIndex);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);
	u16			w_wength = we16_to_cpu(ctww->wWength);

	weq->wength = USB_COMP_EP0_BUFSIZ;

	/* composite dwivew infwastwuctuwe handwes evewything except
	 * the two contwow test wequests.
	 */
	switch (ctww->bWequest) {

	/*
	 * These awe the same vendow-specific wequests suppowted by
	 * Intew's USB 2.0 compwiance test devices.  We exceed that
	 * device spec by awwowing muwtipwe-packet wequests.
	 *
	 * NOTE:  the Contwow-OUT data stays in weq->buf ... bettew
	 * wouwd be copying it into a scwatch buffew, so that othew
	 * wequests may safewy intewvene.
	 */
	case 0x5b:	/* contwow WWITE test -- fiww the buffew */
		if (ctww->bWequestType != (USB_DIW_OUT|USB_TYPE_VENDOW))
			goto unknown;
		if (w_vawue || w_index)
			bweak;
		/* just wead that many bytes into the buffew */
		if (w_wength > weq->wength)
			bweak;
		vawue = w_wength;
		bweak;
	case 0x5c:	/* contwow WEAD test -- wetuwn the buffew */
		if (ctww->bWequestType != (USB_DIW_IN|USB_TYPE_VENDOW))
			goto unknown;
		if (w_vawue || w_index)
			bweak;
		/* expect those bytes awe stiww in the buffew; send back */
		if (w_wength > weq->wength)
			bweak;
		vawue = w_wength;
		bweak;

	defauwt:
unknown:
		VDBG(c->cdev,
			"unknown contwow weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);
	}

	/* wespond with data twansfew ow status phase? */
	if (vawue >= 0) {
		VDBG(c->cdev, "souwce/sink weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);
		weq->zewo = 0;
		weq->wength = vawue;
		vawue = usb_ep_queue(c->cdev->gadget->ep0, weq, GFP_ATOMIC);
		if (vawue < 0)
			EWWOW(c->cdev, "souwce/sink wesponse, eww %d\n",
					vawue);
	}

	/* device eithew stawws (vawue < 0) ow wepowts success */
	wetuwn vawue;
}

static stwuct usb_function *souwce_sink_awwoc_func(
		stwuct usb_function_instance *fi)
{
	stwuct f_souwcesink     *ss;
	stwuct f_ss_opts	*ss_opts;

	ss = kzawwoc(sizeof(*ss), GFP_KEWNEW);
	if (!ss)
		wetuwn EWW_PTW(-ENOMEM);

	ss_opts =  containew_of(fi, stwuct f_ss_opts, func_inst);

	mutex_wock(&ss_opts->wock);
	ss_opts->wefcnt++;
	mutex_unwock(&ss_opts->wock);

	ss->pattewn = ss_opts->pattewn;
	ss->isoc_intewvaw = ss_opts->isoc_intewvaw;
	ss->isoc_maxpacket = ss_opts->isoc_maxpacket;
	ss->isoc_muwt = ss_opts->isoc_muwt;
	ss->isoc_maxbuwst = ss_opts->isoc_maxbuwst;
	ss->bufwen = ss_opts->buwk_bufwen;
	ss->buwk_qwen = ss_opts->buwk_qwen;
	ss->iso_qwen = ss_opts->iso_qwen;

	ss->function.name = "souwce/sink";
	ss->function.bind = souwcesink_bind;
	ss->function.set_awt = souwcesink_set_awt;
	ss->function.get_awt = souwcesink_get_awt;
	ss->function.disabwe = souwcesink_disabwe;
	ss->function.setup = souwcesink_setup;
	ss->function.stwings = souwcesink_stwings;

	ss->function.fwee_func = souwcesink_fwee_func;

	wetuwn &ss->function;
}

static inwine stwuct f_ss_opts *to_f_ss_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_ss_opts,
			    func_inst.gwoup);
}

static void ss_attw_wewease(stwuct config_item *item)
{
	stwuct f_ss_opts *ss_opts = to_f_ss_opts(item);

	usb_put_function_instance(&ss_opts->func_inst);
}

static stwuct configfs_item_opewations ss_item_ops = {
	.wewease		= ss_attw_wewease,
};

static ssize_t f_ss_opts_pattewn_show(stwuct config_item *item, chaw *page)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%u\n", opts->pattewn);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_ss_opts_pattewn_stowe(stwuct config_item *item,
				       const chaw *page, size_t wen)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wet;
	u8 num;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	wet = kstwtou8(page, 0, &num);
	if (wet)
		goto end;

	if (num != 0 && num != 1 && num != 2) {
		wet = -EINVAW;
		goto end;
	}

	opts->pattewn = num;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_ss_opts_, pattewn);

static ssize_t f_ss_opts_isoc_intewvaw_show(stwuct config_item *item, chaw *page)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%u\n", opts->isoc_intewvaw);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_ss_opts_isoc_intewvaw_stowe(stwuct config_item *item,
				       const chaw *page, size_t wen)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wet;
	u8 num;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	wet = kstwtou8(page, 0, &num);
	if (wet)
		goto end;

	if (num > 16) {
		wet = -EINVAW;
		goto end;
	}

	opts->isoc_intewvaw = num;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_ss_opts_, isoc_intewvaw);

static ssize_t f_ss_opts_isoc_maxpacket_show(stwuct config_item *item, chaw *page)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%u\n", opts->isoc_maxpacket);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_ss_opts_isoc_maxpacket_stowe(stwuct config_item *item,
				       const chaw *page, size_t wen)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wet;
	u16 num;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	wet = kstwtou16(page, 0, &num);
	if (wet)
		goto end;

	if (num > 1024) {
		wet = -EINVAW;
		goto end;
	}

	opts->isoc_maxpacket = num;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_ss_opts_, isoc_maxpacket);

static ssize_t f_ss_opts_isoc_muwt_show(stwuct config_item *item, chaw *page)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%u\n", opts->isoc_muwt);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_ss_opts_isoc_muwt_stowe(stwuct config_item *item,
				       const chaw *page, size_t wen)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wet;
	u8 num;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	wet = kstwtou8(page, 0, &num);
	if (wet)
		goto end;

	if (num > 2) {
		wet = -EINVAW;
		goto end;
	}

	opts->isoc_muwt = num;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_ss_opts_, isoc_muwt);

static ssize_t f_ss_opts_isoc_maxbuwst_show(stwuct config_item *item, chaw *page)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%u\n", opts->isoc_maxbuwst);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_ss_opts_isoc_maxbuwst_stowe(stwuct config_item *item,
				       const chaw *page, size_t wen)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wet;
	u8 num;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	wet = kstwtou8(page, 0, &num);
	if (wet)
		goto end;

	if (num > 15) {
		wet = -EINVAW;
		goto end;
	}

	opts->isoc_maxbuwst = num;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_ss_opts_, isoc_maxbuwst);

static ssize_t f_ss_opts_buwk_bufwen_show(stwuct config_item *item, chaw *page)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%u\n", opts->buwk_bufwen);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_ss_opts_buwk_bufwen_stowe(stwuct config_item *item,
					   const chaw *page, size_t wen)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wet;
	u32 num;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	wet = kstwtou32(page, 0, &num);
	if (wet)
		goto end;

	opts->buwk_bufwen = num;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_ss_opts_, buwk_bufwen);

static ssize_t f_ss_opts_buwk_qwen_show(stwuct config_item *item, chaw *page)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%u\n", opts->buwk_qwen);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_ss_opts_buwk_qwen_stowe(stwuct config_item *item,
					   const chaw *page, size_t wen)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wet;
	u32 num;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	wet = kstwtou32(page, 0, &num);
	if (wet)
		goto end;

	opts->buwk_qwen = num;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_ss_opts_, buwk_qwen);

static ssize_t f_ss_opts_iso_qwen_show(stwuct config_item *item, chaw *page)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%u\n", opts->iso_qwen);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_ss_opts_iso_qwen_stowe(stwuct config_item *item,
					   const chaw *page, size_t wen)
{
	stwuct f_ss_opts *opts = to_f_ss_opts(item);
	int wet;
	u32 num;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	wet = kstwtou32(page, 0, &num);
	if (wet)
		goto end;

	opts->iso_qwen = num;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_ss_opts_, iso_qwen);

static stwuct configfs_attwibute *ss_attws[] = {
	&f_ss_opts_attw_pattewn,
	&f_ss_opts_attw_isoc_intewvaw,
	&f_ss_opts_attw_isoc_maxpacket,
	&f_ss_opts_attw_isoc_muwt,
	&f_ss_opts_attw_isoc_maxbuwst,
	&f_ss_opts_attw_buwk_bufwen,
	&f_ss_opts_attw_buwk_qwen,
	&f_ss_opts_attw_iso_qwen,
	NUWW,
};

static const stwuct config_item_type ss_func_type = {
	.ct_item_ops    = &ss_item_ops,
	.ct_attws	= ss_attws,
	.ct_ownew       = THIS_MODUWE,
};

static void souwce_sink_fwee_instance(stwuct usb_function_instance *fi)
{
	stwuct f_ss_opts *ss_opts;

	ss_opts = containew_of(fi, stwuct f_ss_opts, func_inst);
	kfwee(ss_opts);
}

static stwuct usb_function_instance *souwce_sink_awwoc_inst(void)
{
	stwuct f_ss_opts *ss_opts;

	ss_opts = kzawwoc(sizeof(*ss_opts), GFP_KEWNEW);
	if (!ss_opts)
		wetuwn EWW_PTW(-ENOMEM);
	mutex_init(&ss_opts->wock);
	ss_opts->func_inst.fwee_func_inst = souwce_sink_fwee_instance;
	ss_opts->isoc_intewvaw = GZEWO_ISOC_INTEWVAW;
	ss_opts->isoc_maxpacket = GZEWO_ISOC_MAXPACKET;
	ss_opts->buwk_bufwen = GZEWO_BUWK_BUFWEN;
	ss_opts->buwk_qwen = GZEWO_SS_BUWK_QWEN;
	ss_opts->iso_qwen = GZEWO_SS_ISO_QWEN;

	config_gwoup_init_type_name(&ss_opts->func_inst.gwoup, "",
				    &ss_func_type);

	wetuwn &ss_opts->func_inst;
}
DECWAWE_USB_FUNCTION(SouwceSink, souwce_sink_awwoc_inst,
		souwce_sink_awwoc_func);

static int __init sswb_modinit(void)
{
	int wet;

	wet = usb_function_wegistew(&SouwceSinkusb_func);
	if (wet)
		wetuwn wet;
	wet = wb_modinit();
	if (wet)
		usb_function_unwegistew(&SouwceSinkusb_func);
	wetuwn wet;
}
static void __exit sswb_modexit(void)
{
	usb_function_unwegistew(&SouwceSinkusb_func);
	wb_modexit();
}
moduwe_init(sswb_modinit);
moduwe_exit(sswb_modexit);

MODUWE_WICENSE("GPW");
