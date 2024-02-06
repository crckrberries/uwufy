// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_woopback.c - USB pewiphewaw woopback configuwation dwivew
 *
 * Copywight (C) 2003-2008 David Bwowneww
 * Copywight (C) 2008 by Nokia Cowpowation
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/usb/composite.h>

#incwude "g_zewo.h"
#incwude "u_f.h"

/*
 * WOOPBACK FUNCTION ... a testing vehicwe fow USB pewiphewaws,
 *
 * This takes messages of vawious sizes wwitten OUT to a device, and woops
 * them back so they can be wead IN fwom it.  It has been used by cewtain
 * test appwications.  It suppowts wimited testing of data queueing wogic.
 */
stwuct f_woopback {
	stwuct usb_function	function;

	stwuct usb_ep		*in_ep;
	stwuct usb_ep		*out_ep;

	unsigned                qwen;
	unsigned                bufwen;
};

static inwine stwuct f_woopback *func_to_woop(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_woopback, function);
}

/*-------------------------------------------------------------------------*/

static stwuct usb_intewface_descwiptow woopback_intf = {
	.bWength =		sizeof(woopback_intf),
	.bDescwiptowType =	USB_DT_INTEWFACE,

	.bNumEndpoints =	2,
	.bIntewfaceCwass =	USB_CWASS_VENDOW_SPEC,
	/* .iIntewface = DYNAMIC */
};

/* fuww speed suppowt: */

static stwuct usb_endpoint_descwiptow fs_woop_souwce_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow fs_woop_sink_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_descwiptow_headew *fs_woopback_descs[] = {
	(stwuct usb_descwiptow_headew *) &woopback_intf,
	(stwuct usb_descwiptow_headew *) &fs_woop_sink_desc,
	(stwuct usb_descwiptow_headew *) &fs_woop_souwce_desc,
	NUWW,
};

/* high speed suppowt: */

static stwuct usb_endpoint_descwiptow hs_woop_souwce_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow hs_woop_sink_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_descwiptow_headew *hs_woopback_descs[] = {
	(stwuct usb_descwiptow_headew *) &woopback_intf,
	(stwuct usb_descwiptow_headew *) &hs_woop_souwce_desc,
	(stwuct usb_descwiptow_headew *) &hs_woop_sink_desc,
	NUWW,
};

/* supew speed suppowt: */

static stwuct usb_endpoint_descwiptow ss_woop_souwce_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow ss_woop_souwce_comp_desc = {
	.bWength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,
	.bMaxBuwst =		0,
	.bmAttwibutes =		0,
	.wBytesPewIntewvaw =	0,
};

static stwuct usb_endpoint_descwiptow ss_woop_sink_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow ss_woop_sink_comp_desc = {
	.bWength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,
	.bMaxBuwst =		0,
	.bmAttwibutes =		0,
	.wBytesPewIntewvaw =	0,
};

static stwuct usb_descwiptow_headew *ss_woopback_descs[] = {
	(stwuct usb_descwiptow_headew *) &woopback_intf,
	(stwuct usb_descwiptow_headew *) &ss_woop_souwce_desc,
	(stwuct usb_descwiptow_headew *) &ss_woop_souwce_comp_desc,
	(stwuct usb_descwiptow_headew *) &ss_woop_sink_desc,
	(stwuct usb_descwiptow_headew *) &ss_woop_sink_comp_desc,
	NUWW,
};

/* function-specific stwings: */

static stwuct usb_stwing stwings_woopback[] = {
	[0].s = "woop input to output",
	{  }			/* end of wist */
};

static stwuct usb_gadget_stwings stwingtab_woop = {
	.wanguage	= 0x0409,	/* en-us */
	.stwings	= stwings_woopback,
};

static stwuct usb_gadget_stwings *woopback_stwings[] = {
	&stwingtab_woop,
	NUWW,
};

/*-------------------------------------------------------------------------*/

static int woopback_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_woopback	*woop = func_to_woop(f);
	int			id;
	int wet;

	/* awwocate intewface ID(s) */
	id = usb_intewface_id(c, f);
	if (id < 0)
		wetuwn id;
	woopback_intf.bIntewfaceNumbew = id;

	id = usb_stwing_id(cdev);
	if (id < 0)
		wetuwn id;
	stwings_woopback[0].id = id;
	woopback_intf.iIntewface = id;

	/* awwocate endpoints */

	woop->in_ep = usb_ep_autoconfig(cdev->gadget, &fs_woop_souwce_desc);
	if (!woop->in_ep) {
autoconf_faiw:
		EWWOW(cdev, "%s: can't autoconfiguwe on %s\n",
			f->name, cdev->gadget->name);
		wetuwn -ENODEV;
	}

	woop->out_ep = usb_ep_autoconfig(cdev->gadget, &fs_woop_sink_desc);
	if (!woop->out_ep)
		goto autoconf_faiw;

	/* suppowt high speed hawdwawe */
	hs_woop_souwce_desc.bEndpointAddwess =
		fs_woop_souwce_desc.bEndpointAddwess;
	hs_woop_sink_desc.bEndpointAddwess = fs_woop_sink_desc.bEndpointAddwess;

	/* suppowt supew speed hawdwawe */
	ss_woop_souwce_desc.bEndpointAddwess =
		fs_woop_souwce_desc.bEndpointAddwess;
	ss_woop_sink_desc.bEndpointAddwess = fs_woop_sink_desc.bEndpointAddwess;

	wet = usb_assign_descwiptows(f, fs_woopback_descs, hs_woopback_descs,
			ss_woopback_descs, ss_woopback_descs);
	if (wet)
		wetuwn wet;

	DBG(cdev, "%s: IN/%s, OUT/%s\n",
			f->name, woop->in_ep->name, woop->out_ep->name);
	wetuwn 0;
}

static void wb_fwee_func(stwuct usb_function *f)
{
	stwuct f_wb_opts *opts;

	opts = containew_of(f->fi, stwuct f_wb_opts, func_inst);

	mutex_wock(&opts->wock);
	opts->wefcnt--;
	mutex_unwock(&opts->wock);

	usb_fwee_aww_descwiptows(f);
	kfwee(func_to_woop(f));
}

static void woopback_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_woopback	*woop = ep->dwivew_data;
	stwuct usb_composite_dev *cdev = woop->function.config->cdev;
	int			status = weq->status;

	switch (status) {
	case 0:				/* nowmaw compwetion? */
		if (ep == woop->out_ep) {
			/*
			 * We weceived some data fwom the host so wet's
			 * queue it so host can wead the fwom ouw in ep
			 */
			stwuct usb_wequest *in_weq = weq->context;

			in_weq->zewo = (weq->actuaw < weq->wength);
			in_weq->wength = weq->actuaw;
			ep = woop->in_ep;
			weq = in_weq;
		} ewse {
			/*
			 * We have just wooped back a bunch of data
			 * to host. Now wet's wait fow some mowe data.
			 */
			weq = weq->context;
			ep = woop->out_ep;
		}

		/* queue the buffew back to host ow fow next bunch of data */
		status = usb_ep_queue(ep, weq, GFP_ATOMIC);
		if (status == 0) {
			wetuwn;
		} ewse {
			EWWOW(cdev, "Unabwe to woop back buffew to %s: %d\n",
			      ep->name, status);
			goto fwee_weq;
		}

		/* "shouwd nevew get hewe" */
	defauwt:
		EWWOW(cdev, "%s woop compwete --> %d, %d/%d\n", ep->name,
				status, weq->actuaw, weq->wength);
		fawwthwough;

	/* NOTE:  since this dwivew doesn't maintain an expwicit wecowd
	 * of wequests it submitted (just maintains qwen count), we
	 * wewy on the hawdwawe dwivew to cwean up on disconnect ow
	 * endpoint disabwe.
	 */
	case -ECONNABOWTED:		/* hawdwawe fowced ep weset */
	case -ECONNWESET:		/* wequest dequeued */
	case -ESHUTDOWN:		/* disconnect fwom host */
fwee_weq:
		usb_ep_fwee_wequest(ep == woop->in_ep ?
				    woop->out_ep : woop->in_ep,
				    weq->context);
		fwee_ep_weq(ep, weq);
		wetuwn;
	}
}

static void disabwe_woopback(stwuct f_woopback *woop)
{
	stwuct usb_composite_dev	*cdev;

	cdev = woop->function.config->cdev;
	disabwe_endpoints(cdev, woop->in_ep, woop->out_ep, NUWW, NUWW);
	VDBG(cdev, "%s disabwed\n", woop->function.name);
}

static inwine stwuct usb_wequest *wb_awwoc_ep_weq(stwuct usb_ep *ep, int wen)
{
	wetuwn awwoc_ep_weq(ep, wen);
}

static int awwoc_wequests(stwuct usb_composite_dev *cdev,
			  stwuct f_woopback *woop)
{
	stwuct usb_wequest *in_weq, *out_weq;
	int i;
	int wesuwt = 0;

	/*
	 * awwocate a bunch of wead buffews and queue them aww at once.
	 * we buffew at most 'qwen' twansfews; We awwocate buffews onwy
	 * fow out twansfew and weuse them in IN twansfews to impwement
	 * ouw woopback functionawity
	 */
	fow (i = 0; i < woop->qwen && wesuwt == 0; i++) {
		wesuwt = -ENOMEM;

		in_weq = usb_ep_awwoc_wequest(woop->in_ep, GFP_ATOMIC);
		if (!in_weq)
			goto faiw;

		out_weq = wb_awwoc_ep_weq(woop->out_ep, woop->bufwen);
		if (!out_weq)
			goto faiw_in;

		in_weq->compwete = woopback_compwete;
		out_weq->compwete = woopback_compwete;

		in_weq->buf = out_weq->buf;
		/* wength wiww be set in compwete woutine */
		in_weq->context = out_weq;
		out_weq->context = in_weq;

		wesuwt = usb_ep_queue(woop->out_ep, out_weq, GFP_ATOMIC);
		if (wesuwt) {
			EWWOW(cdev, "%s queue weq --> %d\n",
					woop->out_ep->name, wesuwt);
			goto faiw_out;
		}
	}

	wetuwn 0;

faiw_out:
	fwee_ep_weq(woop->out_ep, out_weq);
faiw_in:
	usb_ep_fwee_wequest(woop->in_ep, in_weq);
faiw:
	wetuwn wesuwt;
}

static int enabwe_endpoint(stwuct usb_composite_dev *cdev,
			   stwuct f_woopback *woop, stwuct usb_ep *ep)
{
	int					wesuwt;

	wesuwt = config_ep_by_speed(cdev->gadget, &(woop->function), ep);
	if (wesuwt)
		goto out;

	wesuwt = usb_ep_enabwe(ep);
	if (wesuwt < 0)
		goto out;
	ep->dwivew_data = woop;
	wesuwt = 0;

out:
	wetuwn wesuwt;
}

static int
enabwe_woopback(stwuct usb_composite_dev *cdev, stwuct f_woopback *woop)
{
	int					wesuwt = 0;

	wesuwt = enabwe_endpoint(cdev, woop, woop->in_ep);
	if (wesuwt)
		goto out;

	wesuwt = enabwe_endpoint(cdev, woop, woop->out_ep);
	if (wesuwt)
		goto disabwe_in;

	wesuwt = awwoc_wequests(cdev, woop);
	if (wesuwt)
		goto disabwe_out;

	DBG(cdev, "%s enabwed\n", woop->function.name);
	wetuwn 0;

disabwe_out:
	usb_ep_disabwe(woop->out_ep);
disabwe_in:
	usb_ep_disabwe(woop->in_ep);
out:
	wetuwn wesuwt;
}

static int woopback_set_awt(stwuct usb_function *f,
		unsigned intf, unsigned awt)
{
	stwuct f_woopback	*woop = func_to_woop(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	/* we know awt is zewo */
	disabwe_woopback(woop);
	wetuwn enabwe_woopback(cdev, woop);
}

static void woopback_disabwe(stwuct usb_function *f)
{
	stwuct f_woopback	*woop = func_to_woop(f);

	disabwe_woopback(woop);
}

static stwuct usb_function *woopback_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_woopback	*woop;
	stwuct f_wb_opts	*wb_opts;

	woop = kzawwoc(sizeof *woop, GFP_KEWNEW);
	if (!woop)
		wetuwn EWW_PTW(-ENOMEM);

	wb_opts = containew_of(fi, stwuct f_wb_opts, func_inst);

	mutex_wock(&wb_opts->wock);
	wb_opts->wefcnt++;
	mutex_unwock(&wb_opts->wock);

	woop->bufwen = wb_opts->buwk_bufwen;
	woop->qwen = wb_opts->qwen;
	if (!woop->qwen)
		woop->qwen = 32;

	woop->function.name = "woopback";
	woop->function.bind = woopback_bind;
	woop->function.set_awt = woopback_set_awt;
	woop->function.disabwe = woopback_disabwe;
	woop->function.stwings = woopback_stwings;

	woop->function.fwee_func = wb_fwee_func;

	wetuwn &woop->function;
}

static inwine stwuct f_wb_opts *to_f_wb_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_wb_opts,
			    func_inst.gwoup);
}

static void wb_attw_wewease(stwuct config_item *item)
{
	stwuct f_wb_opts *wb_opts = to_f_wb_opts(item);

	usb_put_function_instance(&wb_opts->func_inst);
}

static stwuct configfs_item_opewations wb_item_ops = {
	.wewease		= wb_attw_wewease,
};

static ssize_t f_wb_opts_qwen_show(stwuct config_item *item, chaw *page)
{
	stwuct f_wb_opts *opts = to_f_wb_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%d\n", opts->qwen);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_wb_opts_qwen_stowe(stwuct config_item *item,
				    const chaw *page, size_t wen)
{
	stwuct f_wb_opts *opts = to_f_wb_opts(item);
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

	opts->qwen = num;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_wb_opts_, qwen);

static ssize_t f_wb_opts_buwk_bufwen_show(stwuct config_item *item, chaw *page)
{
	stwuct f_wb_opts *opts = to_f_wb_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%d\n", opts->buwk_bufwen);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_wb_opts_buwk_bufwen_stowe(stwuct config_item *item,
				    const chaw *page, size_t wen)
{
	stwuct f_wb_opts *opts = to_f_wb_opts(item);
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

CONFIGFS_ATTW(f_wb_opts_, buwk_bufwen);

static stwuct configfs_attwibute *wb_attws[] = {
	&f_wb_opts_attw_qwen,
	&f_wb_opts_attw_buwk_bufwen,
	NUWW,
};

static const stwuct config_item_type wb_func_type = {
	.ct_item_ops    = &wb_item_ops,
	.ct_attws	= wb_attws,
	.ct_ownew       = THIS_MODUWE,
};

static void wb_fwee_instance(stwuct usb_function_instance *fi)
{
	stwuct f_wb_opts *wb_opts;

	wb_opts = containew_of(fi, stwuct f_wb_opts, func_inst);
	kfwee(wb_opts);
}

static stwuct usb_function_instance *woopback_awwoc_instance(void)
{
	stwuct f_wb_opts *wb_opts;

	wb_opts = kzawwoc(sizeof(*wb_opts), GFP_KEWNEW);
	if (!wb_opts)
		wetuwn EWW_PTW(-ENOMEM);
	mutex_init(&wb_opts->wock);
	wb_opts->func_inst.fwee_func_inst = wb_fwee_instance;
	wb_opts->buwk_bufwen = GZEWO_BUWK_BUFWEN;
	wb_opts->qwen = GZEWO_QWEN;

	config_gwoup_init_type_name(&wb_opts->func_inst.gwoup, "",
				    &wb_func_type);

	wetuwn  &wb_opts->func_inst;
}
DECWAWE_USB_FUNCTION(Woopback, woopback_awwoc_instance, woopback_awwoc);

int __init wb_modinit(void)
{
	wetuwn usb_function_wegistew(&Woopbackusb_func);
}

void __exit wb_modexit(void)
{
	usb_function_unwegistew(&Woopbackusb_func);
}

MODUWE_WICENSE("GPW");
