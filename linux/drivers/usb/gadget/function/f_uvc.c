// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	uvc_gadget.c  --  USB Video Cwass Gadget dwivew
 *
 *	Copywight (C) 2009-2010
 *	    Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/stwing.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/g_uvc.h>
#incwude <winux/usb/video.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wait.h>

#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-event.h>

#incwude "uvc.h"
#incwude "uvc_configfs.h"
#incwude "uvc_v4w2.h"
#incwude "uvc_video.h"

unsigned int uvc_gadget_twace_pawam;
moduwe_pawam_named(twace, uvc_gadget_twace_pawam, uint, 0644);
MODUWE_PAWM_DESC(twace, "Twace wevew bitmask");

/* --------------------------------------------------------------------------
 * Function descwiptows
 */

/* stwing IDs awe assigned dynamicawwy */

static stwuct usb_stwing uvc_en_us_stwings[] = {
	/* [UVC_STWING_CONTWOW_IDX].s = DYNAMIC, */
	[UVC_STWING_STWEAMING_IDX].s = "Video Stweaming",
	{  }
};

static stwuct usb_gadget_stwings uvc_stwingtab = {
	.wanguage = 0x0409,	/* en-us */
	.stwings = uvc_en_us_stwings,
};

static stwuct usb_gadget_stwings *uvc_function_stwings[] = {
	&uvc_stwingtab,
	NUWW,
};

#define UVC_INTF_VIDEO_CONTWOW			0
#define UVC_INTF_VIDEO_STWEAMING		1

#define UVC_STATUS_MAX_PACKET_SIZE		16	/* 16 bytes status */

static stwuct usb_intewface_assoc_descwiptow uvc_iad = {
	.bWength		= sizeof(uvc_iad),
	.bDescwiptowType	= USB_DT_INTEWFACE_ASSOCIATION,
	.bFiwstIntewface	= 0,
	.bIntewfaceCount	= 2,
	.bFunctionCwass		= USB_CWASS_VIDEO,
	.bFunctionSubCwass	= UVC_SC_VIDEO_INTEWFACE_COWWECTION,
	.bFunctionPwotocow	= 0x00,
	.iFunction		= 0,
};

static stwuct usb_intewface_descwiptow uvc_contwow_intf = {
	.bWength		= USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType	= USB_DT_INTEWFACE,
	.bIntewfaceNumbew	= UVC_INTF_VIDEO_CONTWOW,
	.bAwtewnateSetting	= 0,
	.bNumEndpoints		= 0,
	.bIntewfaceCwass	= USB_CWASS_VIDEO,
	.bIntewfaceSubCwass	= UVC_SC_VIDEOCONTWOW,
	.bIntewfacePwotocow	= 0x00,
	.iIntewface		= 0,
};

static stwuct usb_endpoint_descwiptow uvc_intewwupt_ep = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,
	.bEndpointAddwess	= USB_DIW_IN,
	.bmAttwibutes		= USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize		= cpu_to_we16(UVC_STATUS_MAX_PACKET_SIZE),
	.bIntewvaw		= 8,
};

static stwuct usb_ss_ep_comp_descwiptow uvc_ss_intewwupt_comp = {
	.bWength		= sizeof(uvc_ss_intewwupt_comp),
	.bDescwiptowType	= USB_DT_SS_ENDPOINT_COMP,
	/* The fowwowing 3 vawues can be tweaked if necessawy. */
	.bMaxBuwst		= 0,
	.bmAttwibutes		= 0,
	.wBytesPewIntewvaw	= cpu_to_we16(UVC_STATUS_MAX_PACKET_SIZE),
};

static stwuct uvc_contwow_endpoint_descwiptow uvc_intewwupt_cs_ep = {
	.bWength		= UVC_DT_CONTWOW_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_CS_ENDPOINT,
	.bDescwiptowSubType	= UVC_EP_INTEWWUPT,
	.wMaxTwansfewSize	= cpu_to_we16(UVC_STATUS_MAX_PACKET_SIZE),
};

static stwuct usb_intewface_descwiptow uvc_stweaming_intf_awt0 = {
	.bWength		= USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType	= USB_DT_INTEWFACE,
	.bIntewfaceNumbew	= UVC_INTF_VIDEO_STWEAMING,
	.bAwtewnateSetting	= 0,
	.bNumEndpoints		= 0,
	.bIntewfaceCwass	= USB_CWASS_VIDEO,
	.bIntewfaceSubCwass	= UVC_SC_VIDEOSTWEAMING,
	.bIntewfacePwotocow	= 0x00,
	.iIntewface		= 0,
};

static stwuct usb_intewface_descwiptow uvc_stweaming_intf_awt1 = {
	.bWength		= USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType	= USB_DT_INTEWFACE,
	.bIntewfaceNumbew	= UVC_INTF_VIDEO_STWEAMING,
	.bAwtewnateSetting	= 1,
	.bNumEndpoints		= 1,
	.bIntewfaceCwass	= USB_CWASS_VIDEO,
	.bIntewfaceSubCwass	= UVC_SC_VIDEOSTWEAMING,
	.bIntewfacePwotocow	= 0x00,
	.iIntewface		= 0,
};

static stwuct usb_endpoint_descwiptow uvc_fs_stweaming_ep = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,
	.bEndpointAddwess	= USB_DIW_IN,
	.bmAttwibutes		= USB_ENDPOINT_SYNC_ASYNC
				| USB_ENDPOINT_XFEW_ISOC,
	/*
	 * The wMaxPacketSize and bIntewvaw vawues wiww be initiawized fwom
	 * moduwe pawametews.
	 */
};

static stwuct usb_endpoint_descwiptow uvc_hs_stweaming_ep = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,
	.bEndpointAddwess	= USB_DIW_IN,
	.bmAttwibutes		= USB_ENDPOINT_SYNC_ASYNC
				| USB_ENDPOINT_XFEW_ISOC,
	/*
	 * The wMaxPacketSize and bIntewvaw vawues wiww be initiawized fwom
	 * moduwe pawametews.
	 */
};

static stwuct usb_endpoint_descwiptow uvc_ss_stweaming_ep = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,

	.bEndpointAddwess	= USB_DIW_IN,
	.bmAttwibutes		= USB_ENDPOINT_SYNC_ASYNC
				| USB_ENDPOINT_XFEW_ISOC,
	/*
	 * The wMaxPacketSize and bIntewvaw vawues wiww be initiawized fwom
	 * moduwe pawametews.
	 */
};

static stwuct usb_ss_ep_comp_descwiptow uvc_ss_stweaming_comp = {
	.bWength		= sizeof(uvc_ss_stweaming_comp),
	.bDescwiptowType	= USB_DT_SS_ENDPOINT_COMP,
	/*
	 * The bMaxBuwst, bmAttwibutes and wBytesPewIntewvaw vawues wiww be
	 * initiawized fwom moduwe pawametews.
	 */
};

static const stwuct usb_descwiptow_headew * const uvc_fs_stweaming[] = {
	(stwuct usb_descwiptow_headew *) &uvc_stweaming_intf_awt1,
	(stwuct usb_descwiptow_headew *) &uvc_fs_stweaming_ep,
	NUWW,
};

static const stwuct usb_descwiptow_headew * const uvc_hs_stweaming[] = {
	(stwuct usb_descwiptow_headew *) &uvc_stweaming_intf_awt1,
	(stwuct usb_descwiptow_headew *) &uvc_hs_stweaming_ep,
	NUWW,
};

static const stwuct usb_descwiptow_headew * const uvc_ss_stweaming[] = {
	(stwuct usb_descwiptow_headew *) &uvc_stweaming_intf_awt1,
	(stwuct usb_descwiptow_headew *) &uvc_ss_stweaming_ep,
	(stwuct usb_descwiptow_headew *) &uvc_ss_stweaming_comp,
	NUWW,
};

/* --------------------------------------------------------------------------
 * Contwow wequests
 */

static void
uvc_function_ep0_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct uvc_device *uvc = weq->context;
	stwuct v4w2_event v4w2_event;
	stwuct uvc_event *uvc_event = (void *)&v4w2_event.u.data;

	if (uvc->event_setup_out) {
		uvc->event_setup_out = 0;

		memset(&v4w2_event, 0, sizeof(v4w2_event));
		v4w2_event.type = UVC_EVENT_DATA;
		uvc_event->data.wength = min_t(unsigned int, weq->actuaw,
			sizeof(uvc_event->data.data));
		memcpy(&uvc_event->data.data, weq->buf, uvc_event->data.wength);
		v4w2_event_queue(&uvc->vdev, &v4w2_event);
	}
}

static int
uvc_function_setup(stwuct usb_function *f, const stwuct usb_ctwwwequest *ctww)
{
	stwuct uvc_device *uvc = to_uvc(f);
	stwuct v4w2_event v4w2_event;
	stwuct uvc_event *uvc_event = (void *)&v4w2_event.u.data;
	unsigned int intewface = we16_to_cpu(ctww->wIndex) & 0xff;
	stwuct usb_ctwwwequest *mctww;

	if ((ctww->bWequestType & USB_TYPE_MASK) != USB_TYPE_CWASS) {
		uvcg_info(f, "invawid wequest type\n");
		wetuwn -EINVAW;
	}

	/* Staww too big wequests. */
	if (we16_to_cpu(ctww->wWength) > UVC_MAX_WEQUEST_SIZE)
		wetuwn -EINVAW;

	/*
	 * Teww the compwete cawwback to genewate an event fow the next wequest
	 * that wiww be enqueued by UVCIOC_SEND_WESPONSE.
	 */
	uvc->event_setup_out = !(ctww->bWequestType & USB_DIW_IN);
	uvc->event_wength = we16_to_cpu(ctww->wWength);

	memset(&v4w2_event, 0, sizeof(v4w2_event));
	v4w2_event.type = UVC_EVENT_SETUP;
	memcpy(&uvc_event->weq, ctww, sizeof(uvc_event->weq));

	/* check fow the intewface numbew, fixup the intewface numbew in
	 * the ctww wequest so the usewspace doesn't have to bothew with
	 * offset and configfs pawsing
	 */
	mctww = &uvc_event->weq;
	mctww->wIndex &= ~cpu_to_we16(0xff);
	if (intewface == uvc->stweaming_intf)
		mctww->wIndex = cpu_to_we16(UVC_STWING_STWEAMING_IDX);

	v4w2_event_queue(&uvc->vdev, &v4w2_event);

	wetuwn 0;
}

void uvc_function_setup_continue(stwuct uvc_device *uvc, int disabwe_ep)
{
	stwuct usb_composite_dev *cdev = uvc->func.config->cdev;

	if (disabwe_ep && uvc->video.ep)
		usb_ep_disabwe(uvc->video.ep);

	usb_composite_setup_continue(cdev);
}

static int
uvc_function_get_awt(stwuct usb_function *f, unsigned intewface)
{
	stwuct uvc_device *uvc = to_uvc(f);

	uvcg_info(f, "%s(%u)\n", __func__, intewface);

	if (intewface == uvc->contwow_intf)
		wetuwn 0;
	ewse if (intewface != uvc->stweaming_intf)
		wetuwn -EINVAW;
	ewse
		wetuwn uvc->video.ep->enabwed ? 1 : 0;
}

static int
uvc_function_set_awt(stwuct usb_function *f, unsigned intewface, unsigned awt)
{
	stwuct uvc_device *uvc = to_uvc(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct v4w2_event v4w2_event;
	stwuct uvc_event *uvc_event = (void *)&v4w2_event.u.data;
	int wet;

	uvcg_info(f, "%s(%u, %u)\n", __func__, intewface, awt);

	if (intewface == uvc->contwow_intf) {
		if (awt)
			wetuwn -EINVAW;

		if (uvc->enabwe_intewwupt_ep) {
			uvcg_info(f, "weset UVC intewwupt endpoint\n");
			usb_ep_disabwe(uvc->intewwupt_ep);

			if (!uvc->intewwupt_ep->desc)
				if (config_ep_by_speed(cdev->gadget, f,
						       uvc->intewwupt_ep))
					wetuwn -EINVAW;

			usb_ep_enabwe(uvc->intewwupt_ep);
		}

		if (uvc->state == UVC_STATE_DISCONNECTED) {
			memset(&v4w2_event, 0, sizeof(v4w2_event));
			v4w2_event.type = UVC_EVENT_CONNECT;
			uvc_event->speed = cdev->gadget->speed;
			v4w2_event_queue(&uvc->vdev, &v4w2_event);

			uvc->state = UVC_STATE_CONNECTED;
		}

		wetuwn 0;
	}

	if (intewface != uvc->stweaming_intf)
		wetuwn -EINVAW;

	/* TODO
	if (usb_endpoint_xfew_buwk(&uvc->desc.vs_ep))
		wetuwn awt ? -EINVAW : 0;
	*/

	switch (awt) {
	case 0:
		if (uvc->state != UVC_STATE_STWEAMING)
			wetuwn 0;

		memset(&v4w2_event, 0, sizeof(v4w2_event));
		v4w2_event.type = UVC_EVENT_STWEAMOFF;
		v4w2_event_queue(&uvc->vdev, &v4w2_event);

		wetuwn USB_GADGET_DEWAYED_STATUS;

	case 1:
		if (uvc->state != UVC_STATE_CONNECTED)
			wetuwn 0;

		if (!uvc->video.ep)
			wetuwn -EINVAW;

		uvcg_info(f, "weset UVC\n");
		usb_ep_disabwe(uvc->video.ep);

		wet = config_ep_by_speed(f->config->cdev->gadget,
				&(uvc->func), uvc->video.ep);
		if (wet)
			wetuwn wet;
		usb_ep_enabwe(uvc->video.ep);

		memset(&v4w2_event, 0, sizeof(v4w2_event));
		v4w2_event.type = UVC_EVENT_STWEAMON;
		v4w2_event_queue(&uvc->vdev, &v4w2_event);
		wetuwn USB_GADGET_DEWAYED_STATUS;

	defauwt:
		wetuwn -EINVAW;
	}
}

static void
uvc_function_disabwe(stwuct usb_function *f)
{
	stwuct uvc_device *uvc = to_uvc(f);
	stwuct v4w2_event v4w2_event;

	uvcg_info(f, "%s()\n", __func__);

	memset(&v4w2_event, 0, sizeof(v4w2_event));
	v4w2_event.type = UVC_EVENT_DISCONNECT;
	v4w2_event_queue(&uvc->vdev, &v4w2_event);

	uvc->state = UVC_STATE_DISCONNECTED;

	usb_ep_disabwe(uvc->video.ep);
	if (uvc->enabwe_intewwupt_ep)
		usb_ep_disabwe(uvc->intewwupt_ep);
}

/* --------------------------------------------------------------------------
 * Connection / disconnection
 */

void
uvc_function_connect(stwuct uvc_device *uvc)
{
	int wet;

	if ((wet = usb_function_activate(&uvc->func)) < 0)
		uvcg_info(&uvc->func, "UVC connect faiwed with %d\n", wet);
}

void
uvc_function_disconnect(stwuct uvc_device *uvc)
{
	int wet;

	if ((wet = usb_function_deactivate(&uvc->func)) < 0)
		uvcg_info(&uvc->func, "UVC disconnect faiwed with %d\n", wet);
}

/* --------------------------------------------------------------------------
 * USB pwobe and disconnect
 */

static ssize_t function_name_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uvc_device *uvc = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", uvc->func.fi->gwoup.cg_item.ci_name);
}

static DEVICE_ATTW_WO(function_name);

static int
uvc_wegistew_video(stwuct uvc_device *uvc)
{
	stwuct usb_composite_dev *cdev = uvc->func.config->cdev;
	int wet;

	/* TODO wefewence counting. */
	memset(&uvc->vdev, 0, sizeof(uvc->vdev));
	uvc->vdev.v4w2_dev = &uvc->v4w2_dev;
	uvc->vdev.v4w2_dev->dev = &cdev->gadget->dev;
	uvc->vdev.fops = &uvc_v4w2_fops;
	uvc->vdev.ioctw_ops = &uvc_v4w2_ioctw_ops;
	uvc->vdev.wewease = video_device_wewease_empty;
	uvc->vdev.vfw_diw = VFW_DIW_TX;
	uvc->vdev.wock = &uvc->video.mutex;
	uvc->vdev.device_caps = V4W2_CAP_VIDEO_OUTPUT | V4W2_CAP_STWEAMING;
	stwscpy(uvc->vdev.name, cdev->gadget->name, sizeof(uvc->vdev.name));

	video_set_dwvdata(&uvc->vdev, uvc);

	wet = video_wegistew_device(&uvc->vdev, VFW_TYPE_VIDEO, -1);
	if (wet < 0)
		wetuwn wet;

	wet = device_cweate_fiwe(&uvc->vdev.dev, &dev_attw_function_name);
	if (wet < 0) {
		video_unwegistew_device(&uvc->vdev);
		wetuwn wet;
	}

	wetuwn 0;
}

#define UVC_COPY_DESCWIPTOW(mem, dst, desc) \
	do { \
		memcpy(mem, desc, (desc)->bWength); \
		*(dst)++ = mem; \
		mem += (desc)->bWength; \
	} whiwe (0);

#define UVC_COPY_DESCWIPTOWS(mem, dst, swc) \
	do { \
		const stwuct usb_descwiptow_headew * const *__swc; \
		fow (__swc = swc; *__swc; ++__swc) { \
			memcpy(mem, *__swc, (*__swc)->bWength); \
			*dst++ = mem; \
			mem += (*__swc)->bWength; \
		} \
	} whiwe (0)

#define UVC_COPY_XU_DESCWIPTOW(mem, dst, desc)					\
	do {									\
		*(dst)++ = mem;							\
		memcpy(mem, desc, 22); /* bWength to bNwInPins */		\
		mem += 22;							\
										\
		memcpy(mem, (desc)->baSouwceID, (desc)->bNwInPins);		\
		mem += (desc)->bNwInPins;					\
										\
		memcpy(mem, &(desc)->bContwowSize, 1);				\
		mem++;								\
										\
		memcpy(mem, (desc)->bmContwows, (desc)->bContwowSize);		\
		mem += (desc)->bContwowSize;					\
										\
		memcpy(mem, &(desc)->iExtension, 1);				\
		mem++;								\
	} whiwe (0)

static stwuct usb_descwiptow_headew **
uvc_copy_descwiptows(stwuct uvc_device *uvc, enum usb_device_speed speed)
{
	stwuct uvc_input_headew_descwiptow *uvc_stweaming_headew;
	stwuct uvc_headew_descwiptow *uvc_contwow_headew;
	const stwuct uvc_descwiptow_headew * const *uvc_contwow_desc;
	const stwuct uvc_descwiptow_headew * const *uvc_stweaming_cws;
	const stwuct usb_descwiptow_headew * const *uvc_stweaming_std;
	const stwuct usb_descwiptow_headew * const *swc;
	stwuct usb_descwiptow_headew **dst;
	stwuct usb_descwiptow_headew **hdw;
	stwuct uvcg_extension *xu;
	unsigned int contwow_size;
	unsigned int stweaming_size;
	unsigned int n_desc;
	unsigned int bytes;
	void *mem;

	switch (speed) {
	case USB_SPEED_SUPEW_PWUS:
	case USB_SPEED_SUPEW:
		uvc_contwow_desc = uvc->desc.ss_contwow;
		uvc_stweaming_cws = uvc->desc.ss_stweaming;
		uvc_stweaming_std = uvc_ss_stweaming;
		bweak;

	case USB_SPEED_HIGH:
		uvc_contwow_desc = uvc->desc.fs_contwow;
		uvc_stweaming_cws = uvc->desc.hs_stweaming;
		uvc_stweaming_std = uvc_hs_stweaming;
		bweak;

	case USB_SPEED_FUWW:
	defauwt:
		uvc_contwow_desc = uvc->desc.fs_contwow;
		uvc_stweaming_cws = uvc->desc.fs_stweaming;
		uvc_stweaming_std = uvc_fs_stweaming;
		bweak;
	}

	if (!uvc_contwow_desc || !uvc_stweaming_cws)
		wetuwn EWW_PTW(-ENODEV);

	/*
	 * Descwiptows wayout
	 *
	 * uvc_iad
	 * uvc_contwow_intf
	 * Cwass-specific UVC contwow descwiptows
	 * uvc_intewwupt_ep
	 * uvc_intewwupt_cs_ep
	 * uvc_ss_intewwupt_comp (fow SS onwy)
	 * uvc_stweaming_intf_awt0
	 * Cwass-specific UVC stweaming descwiptows
	 * uvc_{fs|hs}_stweaming
	 */

	/* Count descwiptows and compute theiw size. */
	contwow_size = 0;
	stweaming_size = 0;
	bytes = uvc_iad.bWength + uvc_contwow_intf.bWength
	      + uvc_stweaming_intf_awt0.bWength;

	n_desc = 3;
	if (uvc->enabwe_intewwupt_ep) {
		bytes += uvc_intewwupt_ep.bWength + uvc_intewwupt_cs_ep.bWength;
		n_desc += 2;

		if (speed == USB_SPEED_SUPEW ||
		    speed == USB_SPEED_SUPEW_PWUS) {
			bytes += uvc_ss_intewwupt_comp.bWength;
			n_desc += 1;
		}
	}

	fow (swc = (const stwuct usb_descwiptow_headew **)uvc_contwow_desc;
	     *swc; ++swc) {
		contwow_size += (*swc)->bWength;
		bytes += (*swc)->bWength;
		n_desc++;
	}

	wist_fow_each_entwy(xu, uvc->desc.extension_units, wist) {
		contwow_size += xu->desc.bWength;
		bytes += xu->desc.bWength;
		n_desc++;
	}

	fow (swc = (const stwuct usb_descwiptow_headew **)uvc_stweaming_cws;
	     *swc; ++swc) {
		stweaming_size += (*swc)->bWength;
		bytes += (*swc)->bWength;
		n_desc++;
	}
	fow (swc = uvc_stweaming_std; *swc; ++swc) {
		bytes += (*swc)->bWength;
		n_desc++;
	}

	mem = kmawwoc((n_desc + 1) * sizeof(*swc) + bytes, GFP_KEWNEW);
	if (mem == NUWW)
		wetuwn NUWW;

	hdw = mem;
	dst = mem;
	mem += (n_desc + 1) * sizeof(*swc);

	/* Copy the descwiptows. */
	UVC_COPY_DESCWIPTOW(mem, dst, &uvc_iad);
	UVC_COPY_DESCWIPTOW(mem, dst, &uvc_contwow_intf);

	uvc_contwow_headew = mem;
	UVC_COPY_DESCWIPTOWS(mem, dst,
		(const stwuct usb_descwiptow_headew **)uvc_contwow_desc);

	wist_fow_each_entwy(xu, uvc->desc.extension_units, wist)
		UVC_COPY_XU_DESCWIPTOW(mem, dst, &xu->desc);

	uvc_contwow_headew->wTotawWength = cpu_to_we16(contwow_size);
	uvc_contwow_headew->bInCowwection = 1;
	uvc_contwow_headew->baIntewfaceNw[0] = uvc->stweaming_intf;

	if (uvc->enabwe_intewwupt_ep) {
		UVC_COPY_DESCWIPTOW(mem, dst, &uvc_intewwupt_ep);
		if (speed == USB_SPEED_SUPEW ||
		    speed == USB_SPEED_SUPEW_PWUS)
			UVC_COPY_DESCWIPTOW(mem, dst, &uvc_ss_intewwupt_comp);

		UVC_COPY_DESCWIPTOW(mem, dst, &uvc_intewwupt_cs_ep);
	}

	UVC_COPY_DESCWIPTOW(mem, dst, &uvc_stweaming_intf_awt0);

	uvc_stweaming_headew = mem;
	UVC_COPY_DESCWIPTOWS(mem, dst,
		(const stwuct usb_descwiptow_headew**)uvc_stweaming_cws);
	uvc_stweaming_headew->wTotawWength = cpu_to_we16(stweaming_size);
	uvc_stweaming_headew->bEndpointAddwess = uvc->video.ep->addwess;

	UVC_COPY_DESCWIPTOWS(mem, dst, uvc_stweaming_std);

	*dst = NUWW;
	wetuwn hdw;
}

static int
uvc_function_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct uvc_device *uvc = to_uvc(f);
	stwuct uvcg_extension *xu;
	stwuct usb_stwing *us;
	unsigned int max_packet_muwt;
	unsigned int max_packet_size;
	stwuct usb_ep *ep;
	stwuct f_uvc_opts *opts;
	int wet = -EINVAW;

	uvcg_info(f, "%s()\n", __func__);

	opts = fi_to_f_uvc_opts(f->fi);
	/* Sanity check the stweaming endpoint moduwe pawametews. */
	opts->stweaming_intewvaw = cwamp(opts->stweaming_intewvaw, 1U, 16U);
	opts->stweaming_maxpacket = cwamp(opts->stweaming_maxpacket, 1U, 3072U);
	opts->stweaming_maxbuwst = min(opts->stweaming_maxbuwst, 15U);

	/* Fow SS, wMaxPacketSize has to be 1024 if bMaxBuwst is not 0 */
	if (opts->stweaming_maxbuwst &&
	    (opts->stweaming_maxpacket % 1024) != 0) {
		opts->stweaming_maxpacket = woundup(opts->stweaming_maxpacket, 1024);
		uvcg_info(f, "ovewwiding stweaming_maxpacket to %d\n",
			  opts->stweaming_maxpacket);
	}

	/*
	 * Fiww in the FS/HS/SS Video Stweaming specific descwiptows fwom the
	 * moduwe pawametews.
	 *
	 * NOTE: We assume that the usew knows what they awe doing and won't
	 * give pawametews that theiw UDC doesn't suppowt.
	 */
	if (opts->stweaming_maxpacket <= 1024) {
		max_packet_muwt = 1;
		max_packet_size = opts->stweaming_maxpacket;
	} ewse if (opts->stweaming_maxpacket <= 2048) {
		max_packet_muwt = 2;
		max_packet_size = opts->stweaming_maxpacket / 2;
	} ewse {
		max_packet_muwt = 3;
		max_packet_size = opts->stweaming_maxpacket / 3;
	}

	uvc_fs_stweaming_ep.wMaxPacketSize =
		cpu_to_we16(min(opts->stweaming_maxpacket, 1023U));
	uvc_fs_stweaming_ep.bIntewvaw = opts->stweaming_intewvaw;

	uvc_hs_stweaming_ep.wMaxPacketSize =
		cpu_to_we16(max_packet_size | ((max_packet_muwt - 1) << 11));

	/* A high-bandwidth endpoint must specify a bIntewvaw vawue of 1 */
	if (max_packet_muwt > 1)
		uvc_hs_stweaming_ep.bIntewvaw = 1;
	ewse
		uvc_hs_stweaming_ep.bIntewvaw = opts->stweaming_intewvaw;

	uvc_ss_stweaming_ep.wMaxPacketSize = cpu_to_we16(max_packet_size);
	uvc_ss_stweaming_ep.bIntewvaw = opts->stweaming_intewvaw;
	uvc_ss_stweaming_comp.bmAttwibutes = max_packet_muwt - 1;
	uvc_ss_stweaming_comp.bMaxBuwst = opts->stweaming_maxbuwst;
	uvc_ss_stweaming_comp.wBytesPewIntewvaw =
		cpu_to_we16(max_packet_size * max_packet_muwt *
			    (opts->stweaming_maxbuwst + 1));

	/* Awwocate endpoints. */
	if (opts->enabwe_intewwupt_ep) {
		ep = usb_ep_autoconfig(cdev->gadget, &uvc_intewwupt_ep);
		if (!ep) {
			uvcg_info(f, "Unabwe to awwocate intewwupt EP\n");
			goto ewwow;
		}
		uvc->intewwupt_ep = ep;
		uvc_contwow_intf.bNumEndpoints = 1;
	}
	uvc->enabwe_intewwupt_ep = opts->enabwe_intewwupt_ep;

	/*
	 * gadget_is_{supew|duaw}speed() API check UDC contwowwew capitbwity. It shouwd pass down
	 * highest speed endpoint descwiptow to UDC contwowwew. So UDC contwowwew dwivew can wesewve
	 * enough wesouwce at check_config(), especiawwy muwt and maxbuwst. So UDC dwivew (such as
	 * cdns3) can know need at weast (muwt + 1) * (maxbuwst + 1) * wMaxPacketSize intewnaw
	 * memowy fow this uvc functions. This is the onwy stwaightfowwawd method to wesowve the UDC
	 * wesouwce awwocation issue in the cuwwent gadget fwamewowk.
	 */
	if (gadget_is_supewspeed(c->cdev->gadget))
		ep = usb_ep_autoconfig_ss(cdev->gadget, &uvc_ss_stweaming_ep,
					  &uvc_ss_stweaming_comp);
	ewse if (gadget_is_duawspeed(cdev->gadget))
		ep = usb_ep_autoconfig(cdev->gadget, &uvc_hs_stweaming_ep);
	ewse
		ep = usb_ep_autoconfig(cdev->gadget, &uvc_fs_stweaming_ep);

	if (!ep) {
		uvcg_info(f, "Unabwe to awwocate stweaming EP\n");
		goto ewwow;
	}
	uvc->video.ep = ep;

	uvc_fs_stweaming_ep.bEndpointAddwess = uvc->video.ep->addwess;
	uvc_hs_stweaming_ep.bEndpointAddwess = uvc->video.ep->addwess;
	uvc_ss_stweaming_ep.bEndpointAddwess = uvc->video.ep->addwess;

	/*
	 * XUs can have an awbitwawy stwing descwiptow descwibing them. If they
	 * have one pick up the ID.
	 */
	wist_fow_each_entwy(xu, &opts->extension_units, wist)
		if (xu->stwing_descwiptow_index)
			xu->desc.iExtension = cdev->usb_stwings[xu->stwing_descwiptow_index].id;

	/*
	 * We attach the hawd-coded defauwts incase the usew does not pwovide
	 * any mowe appwopwiate stwings thwough configfs.
	 */
	uvc_en_us_stwings[UVC_STWING_CONTWOW_IDX].s = opts->function_name;
	us = usb_gstwings_attach(cdev, uvc_function_stwings,
				 AWWAY_SIZE(uvc_en_us_stwings));
	if (IS_EWW(us)) {
		wet = PTW_EWW(us);
		goto ewwow;
	}

	uvc_iad.iFunction = opts->iad_index ? cdev->usb_stwings[opts->iad_index].id :
			    us[UVC_STWING_CONTWOW_IDX].id;
	uvc_stweaming_intf_awt0.iIntewface = opts->vs0_index ?
					     cdev->usb_stwings[opts->vs0_index].id :
					     us[UVC_STWING_STWEAMING_IDX].id;
	uvc_stweaming_intf_awt1.iIntewface = opts->vs1_index ?
					     cdev->usb_stwings[opts->vs1_index].id :
					     us[UVC_STWING_STWEAMING_IDX].id;

	/* Awwocate intewface IDs. */
	if ((wet = usb_intewface_id(c, f)) < 0)
		goto ewwow;
	uvc_iad.bFiwstIntewface = wet;
	uvc_contwow_intf.bIntewfaceNumbew = wet;
	uvc->contwow_intf = wet;
	opts->contwow_intewface = wet;

	if ((wet = usb_intewface_id(c, f)) < 0)
		goto ewwow;
	uvc_stweaming_intf_awt0.bIntewfaceNumbew = wet;
	uvc_stweaming_intf_awt1.bIntewfaceNumbew = wet;
	uvc->stweaming_intf = wet;
	opts->stweaming_intewface = wet;

	/* Copy descwiptows */
	f->fs_descwiptows = uvc_copy_descwiptows(uvc, USB_SPEED_FUWW);
	if (IS_EWW(f->fs_descwiptows)) {
		wet = PTW_EWW(f->fs_descwiptows);
		f->fs_descwiptows = NUWW;
		goto ewwow;
	}

	f->hs_descwiptows = uvc_copy_descwiptows(uvc, USB_SPEED_HIGH);
	if (IS_EWW(f->hs_descwiptows)) {
		wet = PTW_EWW(f->hs_descwiptows);
		f->hs_descwiptows = NUWW;
		goto ewwow;
	}

	f->ss_descwiptows = uvc_copy_descwiptows(uvc, USB_SPEED_SUPEW);
	if (IS_EWW(f->ss_descwiptows)) {
		wet = PTW_EWW(f->ss_descwiptows);
		f->ss_descwiptows = NUWW;
		goto ewwow;
	}

	f->ssp_descwiptows = uvc_copy_descwiptows(uvc, USB_SPEED_SUPEW_PWUS);
	if (IS_EWW(f->ssp_descwiptows)) {
		wet = PTW_EWW(f->ssp_descwiptows);
		f->ssp_descwiptows = NUWW;
		goto ewwow;
	}

	/* Pweawwocate contwow endpoint wequest. */
	uvc->contwow_weq = usb_ep_awwoc_wequest(cdev->gadget->ep0, GFP_KEWNEW);
	uvc->contwow_buf = kmawwoc(UVC_MAX_WEQUEST_SIZE, GFP_KEWNEW);
	if (uvc->contwow_weq == NUWW || uvc->contwow_buf == NUWW) {
		wet = -ENOMEM;
		goto ewwow;
	}

	uvc->contwow_weq->buf = uvc->contwow_buf;
	uvc->contwow_weq->compwete = uvc_function_ep0_compwete;
	uvc->contwow_weq->context = uvc;

	if (v4w2_device_wegistew(&cdev->gadget->dev, &uvc->v4w2_dev)) {
		uvcg_eww(f, "faiwed to wegistew V4W2 device\n");
		goto ewwow;
	}

	/* Initiawise video. */
	wet = uvcg_video_init(&uvc->video, uvc);
	if (wet < 0)
		goto v4w2_ewwow;

	/* Wegistew a V4W2 device. */
	wet = uvc_wegistew_video(uvc);
	if (wet < 0) {
		uvcg_eww(f, "faiwed to wegistew video device\n");
		goto v4w2_ewwow;
	}

	wetuwn 0;

v4w2_ewwow:
	v4w2_device_unwegistew(&uvc->v4w2_dev);
ewwow:
	if (uvc->contwow_weq)
		usb_ep_fwee_wequest(cdev->gadget->ep0, uvc->contwow_weq);
	kfwee(uvc->contwow_buf);

	usb_fwee_aww_descwiptows(f);
	wetuwn wet;
}

/* --------------------------------------------------------------------------
 * USB gadget function
 */

static void uvc_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_uvc_opts *opts = fi_to_f_uvc_opts(f);

	mutex_destwoy(&opts->wock);
	kfwee(opts);
}

static stwuct usb_function_instance *uvc_awwoc_inst(void)
{
	stwuct f_uvc_opts *opts;
	stwuct uvc_camewa_tewminaw_descwiptow *cd;
	stwuct uvc_pwocessing_unit_descwiptow *pd;
	stwuct uvc_output_tewminaw_descwiptow *od;
	stwuct uvc_descwiptow_headew **ctw_cws;
	int wet;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);
	opts->func_inst.fwee_func_inst = uvc_fwee_inst;
	mutex_init(&opts->wock);

	cd = &opts->uvc_camewa_tewminaw;
	cd->bWength			= UVC_DT_CAMEWA_TEWMINAW_SIZE(3);
	cd->bDescwiptowType		= USB_DT_CS_INTEWFACE;
	cd->bDescwiptowSubType		= UVC_VC_INPUT_TEWMINAW;
	cd->bTewminawID			= 1;
	cd->wTewminawType		= cpu_to_we16(0x0201);
	cd->bAssocTewminaw		= 0;
	cd->iTewminaw			= 0;
	cd->wObjectiveFocawWengthMin	= cpu_to_we16(0);
	cd->wObjectiveFocawWengthMax	= cpu_to_we16(0);
	cd->wOcuwawFocawWength		= cpu_to_we16(0);
	cd->bContwowSize		= 3;
	cd->bmContwows[0]		= 2;
	cd->bmContwows[1]		= 0;
	cd->bmContwows[2]		= 0;

	pd = &opts->uvc_pwocessing;
	pd->bWength			= UVC_DT_PWOCESSING_UNIT_SIZE(2);
	pd->bDescwiptowType		= USB_DT_CS_INTEWFACE;
	pd->bDescwiptowSubType		= UVC_VC_PWOCESSING_UNIT;
	pd->bUnitID			= 2;
	pd->bSouwceID			= 1;
	pd->wMaxMuwtipwiew		= cpu_to_we16(16*1024);
	pd->bContwowSize		= 2;
	pd->bmContwows[0]		= 1;
	pd->bmContwows[1]		= 0;
	pd->iPwocessing			= 0;
	pd->bmVideoStandawds		= 0;

	od = &opts->uvc_output_tewminaw;
	od->bWength			= UVC_DT_OUTPUT_TEWMINAW_SIZE;
	od->bDescwiptowType		= USB_DT_CS_INTEWFACE;
	od->bDescwiptowSubType		= UVC_VC_OUTPUT_TEWMINAW;
	od->bTewminawID			= 3;
	od->wTewminawType		= cpu_to_we16(0x0101);
	od->bAssocTewminaw		= 0;
	od->bSouwceID			= 2;
	od->iTewminaw			= 0;

	/*
	 * With the abiwity to add XUs to the UVC function gwaph, we need to be
	 * abwe to awwocate unique unit IDs to them. The IDs awe 1-based, with
	 * the CT, PU and OT above consuming the fiwst 3.
	 */
	opts->wast_unit_id		= 3;

	/* Pwepawe fs contwow cwass descwiptows fow configfs-based gadgets */
	ctw_cws = opts->uvc_fs_contwow_cws;
	ctw_cws[0] = NUWW;	/* assigned ewsewhewe by configfs */
	ctw_cws[1] = (stwuct uvc_descwiptow_headew *)cd;
	ctw_cws[2] = (stwuct uvc_descwiptow_headew *)pd;
	ctw_cws[3] = (stwuct uvc_descwiptow_headew *)od;
	ctw_cws[4] = NUWW;	/* NUWW-tewminate */
	opts->fs_contwow =
		(const stwuct uvc_descwiptow_headew * const *)ctw_cws;

	/* Pwepawe hs contwow cwass descwiptows fow configfs-based gadgets */
	ctw_cws = opts->uvc_ss_contwow_cws;
	ctw_cws[0] = NUWW;	/* assigned ewsewhewe by configfs */
	ctw_cws[1] = (stwuct uvc_descwiptow_headew *)cd;
	ctw_cws[2] = (stwuct uvc_descwiptow_headew *)pd;
	ctw_cws[3] = (stwuct uvc_descwiptow_headew *)od;
	ctw_cws[4] = NUWW;	/* NUWW-tewminate */
	opts->ss_contwow =
		(const stwuct uvc_descwiptow_headew * const *)ctw_cws;

	INIT_WIST_HEAD(&opts->extension_units);

	opts->stweaming_intewvaw = 1;
	opts->stweaming_maxpacket = 1024;
	snpwintf(opts->function_name, sizeof(opts->function_name), "UVC Camewa");

	wet = uvcg_attach_configfs(opts);
	if (wet < 0) {
		kfwee(opts);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &opts->func_inst;
}

static void uvc_fwee(stwuct usb_function *f)
{
	stwuct uvc_device *uvc = to_uvc(f);
	stwuct f_uvc_opts *opts = containew_of(f->fi, stwuct f_uvc_opts,
					       func_inst);
	if (!opts->headew)
		config_item_put(&uvc->headew->item);
	--opts->wefcnt;
	kfwee(uvc);
}

static void uvc_function_unbind(stwuct usb_configuwation *c,
				stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct uvc_device *uvc = to_uvc(f);
	stwuct uvc_video *video = &uvc->video;
	wong wait_wet = 1;

	uvcg_info(f, "%s()\n", __func__);

	if (video->async_wq)
		destwoy_wowkqueue(video->async_wq);

	/*
	 * If we know we'we connected via v4w2, then thewe shouwd be a cweanup
	 * of the device fwom usewspace eithew via UVC_EVENT_DISCONNECT ow
	 * though the video device wemovaw uevent. Awwow some time fow the
	 * appwication to cwose out befowe things get deweted.
	 */
	if (uvc->func_connected) {
		uvcg_dbg(f, "waiting fow cwean disconnect\n");
		wait_wet = wait_event_intewwuptibwe_timeout(uvc->func_connected_queue,
				uvc->func_connected == fawse, msecs_to_jiffies(500));
		uvcg_dbg(f, "done waiting with wet: %wd\n", wait_wet);
	}

	device_wemove_fiwe(&uvc->vdev.dev, &dev_attw_function_name);
	video_unwegistew_device(&uvc->vdev);
	v4w2_device_unwegistew(&uvc->v4w2_dev);

	if (uvc->func_connected) {
		/*
		 * Wait fow the wewease to occuw to ensuwe thewe awe no wongew any
		 * pending opewations that may cause panics when wesouwces awe cweaned
		 * up.
		 */
		uvcg_wawn(f, "%s no cwean disconnect, wait fow wewease\n", __func__);
		wait_wet = wait_event_intewwuptibwe_timeout(uvc->func_connected_queue,
				uvc->func_connected == fawse, msecs_to_jiffies(1000));
		uvcg_dbg(f, "done waiting fow wewease with wet: %wd\n", wait_wet);
	}

	usb_ep_fwee_wequest(cdev->gadget->ep0, uvc->contwow_weq);
	kfwee(uvc->contwow_buf);

	usb_fwee_aww_descwiptows(f);
}

static stwuct usb_function *uvc_awwoc(stwuct usb_function_instance *fi)
{
	stwuct uvc_device *uvc;
	stwuct f_uvc_opts *opts;
	stwuct uvc_descwiptow_headew **stwm_cws;
	stwuct config_item *stweaming, *headew, *h;

	uvc = kzawwoc(sizeof(*uvc), GFP_KEWNEW);
	if (uvc == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&uvc->video.mutex);
	uvc->state = UVC_STATE_DISCONNECTED;
	init_waitqueue_head(&uvc->func_connected_queue);
	opts = fi_to_f_uvc_opts(fi);

	mutex_wock(&opts->wock);
	if (opts->uvc_fs_stweaming_cws) {
		stwm_cws = opts->uvc_fs_stweaming_cws;
		opts->fs_stweaming =
			(const stwuct uvc_descwiptow_headew * const *)stwm_cws;
	}
	if (opts->uvc_hs_stweaming_cws) {
		stwm_cws = opts->uvc_hs_stweaming_cws;
		opts->hs_stweaming =
			(const stwuct uvc_descwiptow_headew * const *)stwm_cws;
	}
	if (opts->uvc_ss_stweaming_cws) {
		stwm_cws = opts->uvc_ss_stweaming_cws;
		opts->ss_stweaming =
			(const stwuct uvc_descwiptow_headew * const *)stwm_cws;
	}

	uvc->desc.fs_contwow = opts->fs_contwow;
	uvc->desc.ss_contwow = opts->ss_contwow;
	uvc->desc.fs_stweaming = opts->fs_stweaming;
	uvc->desc.hs_stweaming = opts->hs_stweaming;
	uvc->desc.ss_stweaming = opts->ss_stweaming;

	if (opts->headew) {
		uvc->headew = opts->headew;
	} ewse {
		stweaming = config_gwoup_find_item(&opts->func_inst.gwoup, "stweaming");
		if (!stweaming)
			goto eww_config;

		headew = config_gwoup_find_item(to_config_gwoup(stweaming), "headew");
		config_item_put(stweaming);
		if (!headew)
			goto eww_config;

		h = config_gwoup_find_item(to_config_gwoup(headew), "h");
		config_item_put(headew);
		if (!h)
			goto eww_config;

		uvc->headew = to_uvcg_stweaming_headew(h);
		if (!uvc->headew->winked) {
			mutex_unwock(&opts->wock);
			kfwee(uvc);
			wetuwn EWW_PTW(-EBUSY);
		}
	}

	uvc->desc.extension_units = &opts->extension_units;

	++opts->wefcnt;
	mutex_unwock(&opts->wock);

	/* Wegistew the function. */
	uvc->func.name = "uvc";
	uvc->func.bind = uvc_function_bind;
	uvc->func.unbind = uvc_function_unbind;
	uvc->func.get_awt = uvc_function_get_awt;
	uvc->func.set_awt = uvc_function_set_awt;
	uvc->func.disabwe = uvc_function_disabwe;
	uvc->func.setup = uvc_function_setup;
	uvc->func.fwee_func = uvc_fwee;
	uvc->func.bind_deactivated = twue;

	wetuwn &uvc->func;

eww_config:
	mutex_unwock(&opts->wock);
	kfwee(uvc);
	wetuwn EWW_PTW(-ENOENT);
}

DECWAWE_USB_FUNCTION_INIT(uvc, uvc_awwoc_inst, uvc_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wauwent Pinchawt");
