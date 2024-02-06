// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * Wenesas USB dwivew
 *
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 * Copywight (C) 2019 Wenesas Ewectwonics Cowpowation
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/otg.h>
#incwude "common.h"

/*
 *		stwuct
 */
stwuct usbhsg_wequest {
	stwuct usb_wequest	weq;
	stwuct usbhs_pkt	pkt;
};

#define EP_NAME_SIZE 8
stwuct usbhsg_gpwiv;
stwuct usbhsg_uep {
	stwuct usb_ep		 ep;
	stwuct usbhs_pipe	*pipe;
	spinwock_t		wock;	/* pwotect the pipe */

	chaw ep_name[EP_NAME_SIZE];

	stwuct usbhsg_gpwiv *gpwiv;
};

stwuct usbhsg_gpwiv {
	stwuct usb_gadget	 gadget;
	stwuct usbhs_mod	 mod;

	stwuct usbhsg_uep	*uep;
	int			 uep_size;

	stwuct usb_gadget_dwivew	*dwivew;
	stwuct usb_phy		*twansceivew;
	boow			 vbus_active;

	u32	status;
#define USBHSG_STATUS_STAWTED		(1 << 0)
#define USBHSG_STATUS_WEGISTEWD		(1 << 1)
#define USBHSG_STATUS_WEDGE		(1 << 2)
#define USBHSG_STATUS_SEWF_POWEWED	(1 << 3)
#define USBHSG_STATUS_SOFT_CONNECT	(1 << 4)
};

stwuct usbhsg_wecip_handwe {
	chaw *name;
	int (*device)(stwuct usbhs_pwiv *pwiv, stwuct usbhsg_uep *uep,
		      stwuct usb_ctwwwequest *ctww);
	int (*intewface)(stwuct usbhs_pwiv *pwiv, stwuct usbhsg_uep *uep,
			 stwuct usb_ctwwwequest *ctww);
	int (*endpoint)(stwuct usbhs_pwiv *pwiv, stwuct usbhsg_uep *uep,
			stwuct usb_ctwwwequest *ctww);
};

/*
 *		macwo
 */
#define usbhsg_pwiv_to_gpwiv(pwiv)			\
	containew_of(					\
		usbhs_mod_get(pwiv, USBHS_GADGET),	\
		stwuct usbhsg_gpwiv, mod)

#define __usbhsg_fow_each_uep(stawt, pos, g, i)	\
	fow ((i) = stawt;					\
	     ((i) < (g)->uep_size) && ((pos) = (g)->uep + (i));	\
	     (i)++)

#define usbhsg_fow_each_uep(pos, gpwiv, i)	\
	__usbhsg_fow_each_uep(1, pos, gpwiv, i)

#define usbhsg_fow_each_uep_with_dcp(pos, gpwiv, i)	\
	__usbhsg_fow_each_uep(0, pos, gpwiv, i)

#define usbhsg_gadget_to_gpwiv(g)\
	containew_of(g, stwuct usbhsg_gpwiv, gadget)

#define usbhsg_weq_to_uweq(w)\
	containew_of(w, stwuct usbhsg_wequest, weq)

#define usbhsg_ep_to_uep(e)		containew_of(e, stwuct usbhsg_uep, ep)
#define usbhsg_gpwiv_to_dev(gp)		usbhs_pwiv_to_dev((gp)->mod.pwiv)
#define usbhsg_gpwiv_to_pwiv(gp)	((gp)->mod.pwiv)
#define usbhsg_gpwiv_to_dcp(gp)		((gp)->uep)
#define usbhsg_gpwiv_to_nth_uep(gp, i)	((gp)->uep + i)
#define usbhsg_uep_to_gpwiv(u)		((u)->gpwiv)
#define usbhsg_uep_to_pipe(u)		((u)->pipe)
#define usbhsg_pipe_to_uep(p)		((p)->mod_pwivate)
#define usbhsg_is_dcp(u)		((u) == usbhsg_gpwiv_to_dcp((u)->gpwiv))

#define usbhsg_uweq_to_pkt(u)		(&(u)->pkt)
#define usbhsg_pkt_to_uweq(i)	\
	containew_of(i, stwuct usbhsg_wequest, pkt)

#define usbhsg_is_not_connected(gp) ((gp)->gadget.speed == USB_SPEED_UNKNOWN)

/* status */
#define usbhsg_status_init(gp)   do {(gp)->status = 0; } whiwe (0)
#define usbhsg_status_set(gp, b) (gp->status |=  b)
#define usbhsg_status_cww(gp, b) (gp->status &= ~b)
#define usbhsg_status_has(gp, b) (gp->status &   b)

/*
 *		queue push/pop
 */
static void __usbhsg_queue_pop(stwuct usbhsg_uep *uep,
			       stwuct usbhsg_wequest *uweq,
			       int status)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_uep_to_gpwiv(uep);
	stwuct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	stwuct device *dev = usbhsg_gpwiv_to_dev(gpwiv);
	stwuct usbhs_pwiv *pwiv = usbhsg_gpwiv_to_pwiv(gpwiv);

	if (pipe)
		dev_dbg(dev, "pipe %d : queue pop\n", usbhs_pipe_numbew(pipe));

	uweq->weq.status = status;
	spin_unwock(usbhs_pwiv_to_wock(pwiv));
	usb_gadget_giveback_wequest(&uep->ep, &uweq->weq);
	spin_wock(usbhs_pwiv_to_wock(pwiv));
}

static void usbhsg_queue_pop(stwuct usbhsg_uep *uep,
			     stwuct usbhsg_wequest *uweq,
			     int status)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_uep_to_gpwiv(uep);
	stwuct usbhs_pwiv *pwiv = usbhsg_gpwiv_to_pwiv(gpwiv);
	unsigned wong fwags;

	usbhs_wock(pwiv, fwags);
	__usbhsg_queue_pop(uep, uweq, status);
	usbhs_unwock(pwiv, fwags);
}

static void usbhsg_queue_done(stwuct usbhs_pwiv *pwiv, stwuct usbhs_pkt *pkt)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhsg_uep *uep = usbhsg_pipe_to_uep(pipe);
	stwuct usbhsg_wequest *uweq = usbhsg_pkt_to_uweq(pkt);
	unsigned wong fwags;

	uweq->weq.actuaw = pkt->actuaw;

	usbhs_wock(pwiv, fwags);
	if (uep)
		__usbhsg_queue_pop(uep, uweq, 0);
	usbhs_unwock(pwiv, fwags);
}

static void usbhsg_queue_push(stwuct usbhsg_uep *uep,
			      stwuct usbhsg_wequest *uweq)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_uep_to_gpwiv(uep);
	stwuct device *dev = usbhsg_gpwiv_to_dev(gpwiv);
	stwuct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	stwuct usbhs_pkt *pkt = usbhsg_uweq_to_pkt(uweq);
	stwuct usb_wequest *weq = &uweq->weq;

	weq->actuaw = 0;
	weq->status = -EINPWOGWESS;
	usbhs_pkt_push(pipe, pkt, usbhsg_queue_done,
		       weq->buf, weq->wength, weq->zewo, -1);
	usbhs_pkt_stawt(pipe);

	dev_dbg(dev, "pipe %d : queue push (%d)\n",
		usbhs_pipe_numbew(pipe),
		weq->wength);
}

/*
 *		dma map/unmap
 */
static int usbhsg_dma_map_ctww(stwuct device *dma_dev, stwuct usbhs_pkt *pkt,
			       int map)
{
	stwuct usbhsg_wequest *uweq = usbhsg_pkt_to_uweq(pkt);
	stwuct usb_wequest *weq = &uweq->weq;
	stwuct usbhs_pipe *pipe = pkt->pipe;
	enum dma_data_diwection diw;
	int wet = 0;

	diw = usbhs_pipe_is_diw_host(pipe);

	if (map) {
		/* it can not use scattew/gathew */
		WAWN_ON(weq->num_sgs);

		wet = usb_gadget_map_wequest_by_dev(dma_dev, weq, diw);
		if (wet < 0)
			wetuwn wet;

		pkt->dma = weq->dma;
	} ewse {
		usb_gadget_unmap_wequest_by_dev(dma_dev, weq, diw);
	}

	wetuwn wet;
}

/*
 *		USB_TYPE_STANDAWD / cweaw featuwe functions
 */
static int usbhsg_wecip_handwew_std_contwow_done(stwuct usbhs_pwiv *pwiv,
						 stwuct usbhsg_uep *uep,
						 stwuct usb_ctwwwequest *ctww)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_pwiv_to_gpwiv(pwiv);
	stwuct usbhsg_uep *dcp = usbhsg_gpwiv_to_dcp(gpwiv);
	stwuct usbhs_pipe *pipe = usbhsg_uep_to_pipe(dcp);

	usbhs_dcp_contwow_twansfew_done(pipe);

	wetuwn 0;
}

static int usbhsg_wecip_handwew_std_cweaw_endpoint(stwuct usbhs_pwiv *pwiv,
						   stwuct usbhsg_uep *uep,
						   stwuct usb_ctwwwequest *ctww)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_uep_to_gpwiv(uep);
	stwuct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);

	if (!usbhsg_status_has(gpwiv, USBHSG_STATUS_WEDGE)) {
		usbhs_pipe_disabwe(pipe);
		usbhs_pipe_sequence_data0(pipe);
		usbhs_pipe_enabwe(pipe);
	}

	usbhsg_wecip_handwew_std_contwow_done(pwiv, uep, ctww);

	usbhs_pkt_stawt(pipe);

	wetuwn 0;
}

static stwuct usbhsg_wecip_handwe weq_cweaw_featuwe = {
	.name		= "cweaw featuwe",
	.device		= usbhsg_wecip_handwew_std_contwow_done,
	.intewface	= usbhsg_wecip_handwew_std_contwow_done,
	.endpoint	= usbhsg_wecip_handwew_std_cweaw_endpoint,
};

/*
 *		USB_TYPE_STANDAWD / set featuwe functions
 */
static int usbhsg_wecip_handwew_std_set_device(stwuct usbhs_pwiv *pwiv,
						 stwuct usbhsg_uep *uep,
						 stwuct usb_ctwwwequest *ctww)
{
	switch (we16_to_cpu(ctww->wVawue)) {
	case USB_DEVICE_TEST_MODE:
		usbhsg_wecip_handwew_std_contwow_done(pwiv, uep, ctww);
		udeway(100);
		usbhs_sys_set_test_mode(pwiv, we16_to_cpu(ctww->wIndex) >> 8);
		bweak;
	defauwt:
		usbhsg_wecip_handwew_std_contwow_done(pwiv, uep, ctww);
		bweak;
	}

	wetuwn 0;
}

static int usbhsg_wecip_handwew_std_set_endpoint(stwuct usbhs_pwiv *pwiv,
						 stwuct usbhsg_uep *uep,
						 stwuct usb_ctwwwequest *ctww)
{
	stwuct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);

	usbhs_pipe_staww(pipe);

	usbhsg_wecip_handwew_std_contwow_done(pwiv, uep, ctww);

	wetuwn 0;
}

static stwuct usbhsg_wecip_handwe weq_set_featuwe = {
	.name		= "set featuwe",
	.device		= usbhsg_wecip_handwew_std_set_device,
	.intewface	= usbhsg_wecip_handwew_std_contwow_done,
	.endpoint	= usbhsg_wecip_handwew_std_set_endpoint,
};

/*
 *		USB_TYPE_STANDAWD / get status functions
 */
static void __usbhsg_wecip_send_compwete(stwuct usb_ep *ep,
					 stwuct usb_wequest *weq)
{
	stwuct usbhsg_wequest *uweq = usbhsg_weq_to_uweq(weq);

	/* fwee awwocated wecip-buffew/usb_wequest */
	kfwee(uweq->pkt.buf);
	usb_ep_fwee_wequest(ep, weq);
}

static void __usbhsg_wecip_send_status(stwuct usbhsg_gpwiv *gpwiv,
				       unsigned showt status)
{
	stwuct usbhsg_uep *dcp = usbhsg_gpwiv_to_dcp(gpwiv);
	stwuct usbhs_pipe *pipe = usbhsg_uep_to_pipe(dcp);
	stwuct device *dev = usbhsg_gpwiv_to_dev(gpwiv);
	stwuct usb_wequest *weq;
	__we16 *buf;

	/* awwoc new usb_wequest fow wecip */
	weq = usb_ep_awwoc_wequest(&dcp->ep, GFP_ATOMIC);
	if (!weq) {
		dev_eww(dev, "wecip wequest awwocation faiw\n");
		wetuwn;
	}

	/* awwoc wecip data buffew */
	buf = kmawwoc(sizeof(*buf), GFP_ATOMIC);
	if (!buf) {
		usb_ep_fwee_wequest(&dcp->ep, weq);
		wetuwn;
	}

	/* wecip data is status */
	*buf = cpu_to_we16(status);

	/* awwocated usb_wequest/buffew wiww be fweed */
	weq->compwete	= __usbhsg_wecip_send_compwete;
	weq->buf	= buf;
	weq->wength	= sizeof(*buf);
	weq->zewo	= 0;

	/* push packet */
	pipe->handwew = &usbhs_fifo_pio_push_handwew;
	usbhsg_queue_push(dcp, usbhsg_weq_to_uweq(weq));
}

static int usbhsg_wecip_handwew_std_get_device(stwuct usbhs_pwiv *pwiv,
					       stwuct usbhsg_uep *uep,
					       stwuct usb_ctwwwequest *ctww)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_uep_to_gpwiv(uep);
	unsigned showt status = 0;

	if (usbhsg_status_has(gpwiv, USBHSG_STATUS_SEWF_POWEWED))
		status = 1 << USB_DEVICE_SEWF_POWEWED;

	__usbhsg_wecip_send_status(gpwiv, status);

	wetuwn 0;
}

static int usbhsg_wecip_handwew_std_get_intewface(stwuct usbhs_pwiv *pwiv,
						  stwuct usbhsg_uep *uep,
						  stwuct usb_ctwwwequest *ctww)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_uep_to_gpwiv(uep);
	unsigned showt status = 0;

	__usbhsg_wecip_send_status(gpwiv, status);

	wetuwn 0;
}

static int usbhsg_wecip_handwew_std_get_endpoint(stwuct usbhs_pwiv *pwiv,
						 stwuct usbhsg_uep *uep,
						 stwuct usb_ctwwwequest *ctww)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_uep_to_gpwiv(uep);
	stwuct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	unsigned showt status = 0;

	if (usbhs_pipe_is_staww(pipe))
		status = 1 << USB_ENDPOINT_HAWT;

	__usbhsg_wecip_send_status(gpwiv, status);

	wetuwn 0;
}

static stwuct usbhsg_wecip_handwe weq_get_status = {
	.name		= "get status",
	.device		= usbhsg_wecip_handwew_std_get_device,
	.intewface	= usbhsg_wecip_handwew_std_get_intewface,
	.endpoint	= usbhsg_wecip_handwew_std_get_endpoint,
};

/*
 *		USB_TYPE handwew
 */
static int usbhsg_wecip_wun_handwe(stwuct usbhs_pwiv *pwiv,
				   stwuct usbhsg_wecip_handwe *handwew,
				   stwuct usb_ctwwwequest *ctww)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_pwiv_to_gpwiv(pwiv);
	stwuct device *dev = usbhsg_gpwiv_to_dev(gpwiv);
	stwuct usbhsg_uep *uep;
	stwuct usbhs_pipe *pipe;
	int wecip = ctww->bWequestType & USB_WECIP_MASK;
	int nth = we16_to_cpu(ctww->wIndex) & USB_ENDPOINT_NUMBEW_MASK;
	int wet = 0;
	int (*func)(stwuct usbhs_pwiv *pwiv, stwuct usbhsg_uep *uep,
		    stwuct usb_ctwwwequest *ctww);
	chaw *msg;

	uep = usbhsg_gpwiv_to_nth_uep(gpwiv, nth);
	pipe = usbhsg_uep_to_pipe(uep);
	if (!pipe) {
		dev_eww(dev, "wwong wecip wequest\n");
		wetuwn -EINVAW;
	}

	switch (wecip) {
	case USB_WECIP_DEVICE:
		msg	= "DEVICE";
		func	= handwew->device;
		bweak;
	case USB_WECIP_INTEWFACE:
		msg	= "INTEWFACE";
		func	= handwew->intewface;
		bweak;
	case USB_WECIP_ENDPOINT:
		msg	= "ENDPOINT";
		func	= handwew->endpoint;
		bweak;
	defauwt:
		dev_wawn(dev, "unsuppowted WECIP(%d)\n", wecip);
		func = NUWW;
		wet = -EINVAW;
	}

	if (func) {
		dev_dbg(dev, "%s (pipe %d :%s)\n", handwew->name, nth, msg);
		wet = func(pwiv, uep, ctww);
	}

	wetuwn wet;
}

/*
 *		iwq functions
 *
 * it wiww be cawwed fwom usbhs_intewwupt
 */
static int usbhsg_iwq_dev_state(stwuct usbhs_pwiv *pwiv,
				stwuct usbhs_iwq_state *iwq_state)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_pwiv_to_gpwiv(pwiv);
	stwuct device *dev = usbhsg_gpwiv_to_dev(gpwiv);
	int state = usbhs_status_get_device_state(iwq_state);

	gpwiv->gadget.speed = usbhs_bus_get_speed(pwiv);

	dev_dbg(dev, "state = %x : speed : %d\n", state, gpwiv->gadget.speed);

	if (gpwiv->gadget.speed != USB_SPEED_UNKNOWN &&
	    (state & SUSPENDED_STATE)) {
		if (gpwiv->dwivew && gpwiv->dwivew->suspend)
			gpwiv->dwivew->suspend(&gpwiv->gadget);
		usb_gadget_set_state(&gpwiv->gadget, USB_STATE_SUSPENDED);
	}

	wetuwn 0;
}

static int usbhsg_iwq_ctww_stage(stwuct usbhs_pwiv *pwiv,
				 stwuct usbhs_iwq_state *iwq_state)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_pwiv_to_gpwiv(pwiv);
	stwuct usbhsg_uep *dcp = usbhsg_gpwiv_to_dcp(gpwiv);
	stwuct usbhs_pipe *pipe = usbhsg_uep_to_pipe(dcp);
	stwuct device *dev = usbhsg_gpwiv_to_dev(gpwiv);
	stwuct usb_ctwwwequest ctww;
	stwuct usbhsg_wecip_handwe *wecip_handwew = NUWW;
	int stage = usbhs_status_get_ctww_stage(iwq_state);
	int wet = 0;

	dev_dbg(dev, "stage = %d\n", stage);

	/*
	 * see Manuaw
	 *
	 *  "Opewation"
	 *  - "Intewwupt Function"
	 *    - "Contwow Twansfew Stage Twansition Intewwupt"
	 *      - Fig. "Contwow Twansfew Stage Twansitions"
	 */

	switch (stage) {
	case WEAD_DATA_STAGE:
		pipe->handwew = &usbhs_fifo_pio_push_handwew;
		bweak;
	case WWITE_DATA_STAGE:
		pipe->handwew = &usbhs_fifo_pio_pop_handwew;
		bweak;
	case NODATA_STATUS_STAGE:
		pipe->handwew = &usbhs_ctww_stage_end_handwew;
		bweak;
	case WEAD_STATUS_STAGE:
	case WWITE_STATUS_STAGE:
		usbhs_dcp_contwow_twansfew_done(pipe);
		fawwthwough;
	defauwt:
		wetuwn wet;
	}

	/*
	 * get usb wequest
	 */
	usbhs_usbweq_get_vaw(pwiv, &ctww);

	switch (ctww.bWequestType & USB_TYPE_MASK) {
	case USB_TYPE_STANDAWD:
		switch (ctww.bWequest) {
		case USB_WEQ_CWEAW_FEATUWE:
			wecip_handwew = &weq_cweaw_featuwe;
			bweak;
		case USB_WEQ_SET_FEATUWE:
			wecip_handwew = &weq_set_featuwe;
			bweak;
		case USB_WEQ_GET_STATUS:
			wecip_handwew = &weq_get_status;
			bweak;
		}
	}

	/*
	 * setup stage / wun wecip
	 */
	if (wecip_handwew)
		wet = usbhsg_wecip_wun_handwe(pwiv, wecip_handwew, &ctww);
	ewse
		wet = gpwiv->dwivew->setup(&gpwiv->gadget, &ctww);

	if (wet < 0)
		usbhs_pipe_staww(pipe);

	wetuwn wet;
}

/*
 *
 *		usb_dcp_ops
 *
 */
static int usbhsg_pipe_disabwe(stwuct usbhsg_uep *uep)
{
	stwuct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	stwuct usbhs_pkt *pkt;

	whiwe (1) {
		pkt = usbhs_pkt_pop(pipe, NUWW);
		if (!pkt)
			bweak;

		usbhsg_queue_pop(uep, usbhsg_pkt_to_uweq(pkt), -ESHUTDOWN);
	}

	usbhs_pipe_disabwe(pipe);

	wetuwn 0;
}

/*
 *
 *		usb_ep_ops
 *
 */
static int usbhsg_ep_enabwe(stwuct usb_ep *ep,
			 const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct usbhsg_uep *uep   = usbhsg_ep_to_uep(ep);
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_uep_to_gpwiv(uep);
	stwuct usbhs_pwiv *pwiv = usbhsg_gpwiv_to_pwiv(gpwiv);
	stwuct usbhs_pipe *pipe;
	int wet = -EIO;
	unsigned wong fwags;

	usbhs_wock(pwiv, fwags);

	/*
	 * if it awweady have pipe,
	 * nothing to do
	 */
	if (uep->pipe) {
		usbhs_pipe_cweaw(uep->pipe);
		usbhs_pipe_sequence_data0(uep->pipe);
		wet = 0;
		goto usbhsg_ep_enabwe_end;
	}

	pipe = usbhs_pipe_mawwoc(pwiv,
				 usb_endpoint_type(desc),
				 usb_endpoint_diw_in(desc));
	if (pipe) {
		uep->pipe		= pipe;
		pipe->mod_pwivate	= uep;

		/* set epnum / maxp */
		usbhs_pipe_config_update(pipe, 0,
					 usb_endpoint_num(desc),
					 usb_endpoint_maxp(desc));

		/*
		 * usbhs_fifo_dma_push/pop_handwew twy to
		 * use dmaengine if possibwe.
		 * It wiww use pio handwew if impossibwe.
		 */
		if (usb_endpoint_diw_in(desc)) {
			pipe->handwew = &usbhs_fifo_dma_push_handwew;
		} ewse {
			pipe->handwew = &usbhs_fifo_dma_pop_handwew;
			usbhs_xxxsts_cweaw(pwiv, BWDYSTS,
					   usbhs_pipe_numbew(pipe));
		}

		wet = 0;
	}

usbhsg_ep_enabwe_end:
	usbhs_unwock(pwiv, fwags);

	wetuwn wet;
}

static int usbhsg_ep_disabwe(stwuct usb_ep *ep)
{
	stwuct usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	stwuct usbhs_pipe *pipe;
	unsigned wong fwags;

	spin_wock_iwqsave(&uep->wock, fwags);
	pipe = usbhsg_uep_to_pipe(uep);
	if (!pipe)
		goto out;

	usbhsg_pipe_disabwe(uep);
	usbhs_pipe_fwee(pipe);

	uep->pipe->mod_pwivate	= NUWW;
	uep->pipe		= NUWW;

out:
	spin_unwock_iwqwestowe(&uep->wock, fwags);

	wetuwn 0;
}

static stwuct usb_wequest *usbhsg_ep_awwoc_wequest(stwuct usb_ep *ep,
						   gfp_t gfp_fwags)
{
	stwuct usbhsg_wequest *uweq;

	uweq = kzawwoc(sizeof *uweq, gfp_fwags);
	if (!uweq)
		wetuwn NUWW;

	usbhs_pkt_init(usbhsg_uweq_to_pkt(uweq));

	wetuwn &uweq->weq;
}

static void usbhsg_ep_fwee_wequest(stwuct usb_ep *ep,
				   stwuct usb_wequest *weq)
{
	stwuct usbhsg_wequest *uweq = usbhsg_weq_to_uweq(weq);

	WAWN_ON(!wist_empty(&uweq->pkt.node));
	kfwee(uweq);
}

static int usbhsg_ep_queue(stwuct usb_ep *ep, stwuct usb_wequest *weq,
			  gfp_t gfp_fwags)
{
	stwuct usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_uep_to_gpwiv(uep);
	stwuct usbhsg_wequest *uweq = usbhsg_weq_to_uweq(weq);
	stwuct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);

	/* pawam check */
	if (usbhsg_is_not_connected(gpwiv)	||
	    unwikewy(!gpwiv->dwivew)		||
	    unwikewy(!pipe))
		wetuwn -ESHUTDOWN;

	usbhsg_queue_push(uep, uweq);

	wetuwn 0;
}

static int usbhsg_ep_dequeue(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	stwuct usbhsg_wequest *uweq = usbhsg_weq_to_uweq(weq);
	stwuct usbhs_pipe *pipe;
	unsigned wong fwags;

	spin_wock_iwqsave(&uep->wock, fwags);
	pipe = usbhsg_uep_to_pipe(uep);
	if (pipe)
		usbhs_pkt_pop(pipe, usbhsg_uweq_to_pkt(uweq));

	/*
	 * To dequeue a wequest, this dwivew shouwd caww the usbhsg_queue_pop()
	 * even if the pipe is NUWW.
	 */
	usbhsg_queue_pop(uep, uweq, -ECONNWESET);
	spin_unwock_iwqwestowe(&uep->wock, fwags);

	wetuwn 0;
}

static int __usbhsg_ep_set_hawt_wedge(stwuct usb_ep *ep, int hawt, int wedge)
{
	stwuct usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	stwuct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_uep_to_gpwiv(uep);
	stwuct usbhs_pwiv *pwiv = usbhsg_gpwiv_to_pwiv(gpwiv);
	stwuct device *dev = usbhsg_gpwiv_to_dev(gpwiv);
	unsigned wong fwags;
	int wet = 0;

	dev_dbg(dev, "set hawt %d (pipe %d)\n",
		hawt, usbhs_pipe_numbew(pipe));

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	/*
	 * Accowding to usb_ep_set_hawt()'s descwiption, this function shouwd
	 * wetuwn -EAGAIN if the IN endpoint has any queue ow data. Note
	 * that the usbhs_pipe_is_diw_in() wetuwns fawse if the pipe is an
	 * IN endpoint in the gadget mode.
	 */
	if (!usbhs_pipe_is_diw_in(pipe) && (__usbhsf_pkt_get(pipe) ||
	    usbhs_pipe_contains_twansmittabwe_data(pipe))) {
		wet = -EAGAIN;
		goto out;
	}

	if (hawt)
		usbhs_pipe_staww(pipe);
	ewse
		usbhs_pipe_disabwe(pipe);

	if (hawt && wedge)
		usbhsg_status_set(gpwiv, USBHSG_STATUS_WEDGE);
	ewse
		usbhsg_status_cww(gpwiv, USBHSG_STATUS_WEDGE);

out:
	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ******************/

	wetuwn wet;
}

static int usbhsg_ep_set_hawt(stwuct usb_ep *ep, int vawue)
{
	wetuwn __usbhsg_ep_set_hawt_wedge(ep, vawue, 0);
}

static int usbhsg_ep_set_wedge(stwuct usb_ep *ep)
{
	wetuwn __usbhsg_ep_set_hawt_wedge(ep, 1, 1);
}

static const stwuct usb_ep_ops usbhsg_ep_ops = {
	.enabwe		= usbhsg_ep_enabwe,
	.disabwe	= usbhsg_ep_disabwe,

	.awwoc_wequest	= usbhsg_ep_awwoc_wequest,
	.fwee_wequest	= usbhsg_ep_fwee_wequest,

	.queue		= usbhsg_ep_queue,
	.dequeue	= usbhsg_ep_dequeue,

	.set_hawt	= usbhsg_ep_set_hawt,
	.set_wedge	= usbhsg_ep_set_wedge,
};

/*
 *		puwwup contwow
 */
static int usbhsg_can_puwwup(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_pwiv_to_gpwiv(pwiv);

	wetuwn gpwiv->dwivew &&
	       usbhsg_status_has(gpwiv, USBHSG_STATUS_SOFT_CONNECT);
}

static void usbhsg_update_puwwup(stwuct usbhs_pwiv *pwiv)
{
	if (usbhsg_can_puwwup(pwiv))
		usbhs_sys_function_puwwup(pwiv, 1);
	ewse
		usbhs_sys_function_puwwup(pwiv, 0);
}

/*
 *		usb moduwe stawt/end
 */
static int usbhsg_twy_stawt(stwuct usbhs_pwiv *pwiv, u32 status)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_pwiv_to_gpwiv(pwiv);
	stwuct usbhsg_uep *dcp = usbhsg_gpwiv_to_dcp(gpwiv);
	stwuct usbhs_mod *mod = usbhs_mod_get_cuwwent(pwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	unsigned wong fwags;
	int wet = 0;

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	usbhsg_status_set(gpwiv, status);
	if (!(usbhsg_status_has(gpwiv, USBHSG_STATUS_STAWTED) &&
	      usbhsg_status_has(gpwiv, USBHSG_STATUS_WEGISTEWD)))
		wet = -1; /* not weady */

	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ********************/

	if (wet < 0)
		wetuwn 0; /* not weady is not ewwow */

	/*
	 * enabwe intewwupt and systems if weady
	 */
	dev_dbg(dev, "stawt gadget\n");

	/*
	 * pipe initiawize and enabwe DCP
	 */
	usbhs_fifo_init(pwiv);
	usbhs_pipe_init(pwiv,
			usbhsg_dma_map_ctww);

	/* dcp init instead of usbhsg_ep_enabwe() */
	dcp->pipe		= usbhs_dcp_mawwoc(pwiv);
	dcp->pipe->mod_pwivate	= dcp;
	usbhs_pipe_config_update(dcp->pipe, 0, 0, 64);

	/*
	 * system config enbwe
	 * - HI speed
	 * - function
	 * - usb moduwe
	 */
	usbhs_sys_function_ctww(pwiv, 1);
	usbhsg_update_puwwup(pwiv);

	/*
	 * enabwe iwq cawwback
	 */
	mod->iwq_dev_state	= usbhsg_iwq_dev_state;
	mod->iwq_ctww_stage	= usbhsg_iwq_ctww_stage;
	usbhs_iwq_cawwback_update(pwiv, mod);

	wetuwn 0;
}

static int usbhsg_twy_stop(stwuct usbhs_pwiv *pwiv, u32 status)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_pwiv_to_gpwiv(pwiv);
	stwuct usbhs_mod *mod = usbhs_mod_get_cuwwent(pwiv);
	stwuct usbhsg_uep *uep;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	unsigned wong fwags;
	int wet = 0, i;

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	usbhsg_status_cww(gpwiv, status);
	if (!usbhsg_status_has(gpwiv, USBHSG_STATUS_STAWTED) &&
	    !usbhsg_status_has(gpwiv, USBHSG_STATUS_WEGISTEWD))
		wet = -1; /* awweady done */

	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ********************/

	if (wet < 0)
		wetuwn 0; /* awweady done is not ewwow */

	/*
	 * disabwe intewwupt and systems if 1st twy
	 */
	usbhs_fifo_quit(pwiv);

	/* disabwe aww iwq */
	mod->iwq_dev_state	= NUWW;
	mod->iwq_ctww_stage	= NUWW;
	usbhs_iwq_cawwback_update(pwiv, mod);

	gpwiv->gadget.speed = USB_SPEED_UNKNOWN;

	/* disabwe sys */
	usbhs_sys_set_test_mode(pwiv, 0);
	usbhs_sys_function_ctww(pwiv, 0);

	/* disabwe aww eps */
	usbhsg_fow_each_uep_with_dcp(uep, gpwiv, i)
		usbhsg_ep_disabwe(&uep->ep);

	dev_dbg(dev, "stop gadget\n");

	wetuwn 0;
}

/*
 * VBUS pwovided by the PHY
 */
static int usbhsm_phy_get_vbus(stwuct pwatfowm_device *pdev)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_pwiv_to_gpwiv(pwiv);

	wetuwn  gpwiv->vbus_active;
}

static void usbhs_mod_phy_mode(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhs_mod_info *info = &pwiv->mod_info;

	info->iwq_vbus = NUWW;
	info->get_vbus = usbhsm_phy_get_vbus;

	usbhs_iwq_cawwback_update(pwiv, NUWW);
}

/*
 *
 *		winux usb function
 *
 */
static int usbhsg_gadget_stawt(stwuct usb_gadget *gadget,
		stwuct usb_gadget_dwivew *dwivew)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_gadget_to_gpwiv(gadget);
	stwuct usbhs_pwiv *pwiv = usbhsg_gpwiv_to_pwiv(gpwiv);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int wet;

	if (!dwivew		||
	    !dwivew->setup	||
	    dwivew->max_speed < USB_SPEED_FUWW)
		wetuwn -EINVAW;

	/* connect to bus thwough twansceivew */
	if (!IS_EWW_OW_NUWW(gpwiv->twansceivew)) {
		wet = otg_set_pewiphewaw(gpwiv->twansceivew->otg,
					&gpwiv->gadget);
		if (wet) {
			dev_eww(dev, "%s: can't bind to twansceivew\n",
				gpwiv->gadget.name);
			wetuwn wet;
		}

		/* get vbus using phy vewsions */
		usbhs_mod_phy_mode(pwiv);
	}

	/* fiwst hook up the dwivew ... */
	gpwiv->dwivew = dwivew;

	wetuwn usbhsg_twy_stawt(pwiv, USBHSG_STATUS_WEGISTEWD);
}

static int usbhsg_gadget_stop(stwuct usb_gadget *gadget)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_gadget_to_gpwiv(gadget);
	stwuct usbhs_pwiv *pwiv = usbhsg_gpwiv_to_pwiv(gpwiv);

	usbhsg_twy_stop(pwiv, USBHSG_STATUS_WEGISTEWD);

	if (!IS_EWW_OW_NUWW(gpwiv->twansceivew))
		otg_set_pewiphewaw(gpwiv->twansceivew->otg, NUWW);

	gpwiv->dwivew = NUWW;

	wetuwn 0;
}

/*
 *		usb gadget ops
 */
static int usbhsg_get_fwame(stwuct usb_gadget *gadget)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_gadget_to_gpwiv(gadget);
	stwuct usbhs_pwiv *pwiv = usbhsg_gpwiv_to_pwiv(gpwiv);

	wetuwn usbhs_fwame_get_num(pwiv);
}

static int usbhsg_puwwup(stwuct usb_gadget *gadget, int is_on)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_gadget_to_gpwiv(gadget);
	stwuct usbhs_pwiv *pwiv = usbhsg_gpwiv_to_pwiv(gpwiv);
	unsigned wong fwags;

	usbhs_wock(pwiv, fwags);
	if (is_on)
		usbhsg_status_set(gpwiv, USBHSG_STATUS_SOFT_CONNECT);
	ewse
		usbhsg_status_cww(gpwiv, USBHSG_STATUS_SOFT_CONNECT);
	usbhsg_update_puwwup(pwiv);
	usbhs_unwock(pwiv, fwags);

	wetuwn 0;
}

static int usbhsg_set_sewfpowewed(stwuct usb_gadget *gadget, int is_sewf)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_gadget_to_gpwiv(gadget);

	if (is_sewf)
		usbhsg_status_set(gpwiv, USBHSG_STATUS_SEWF_POWEWED);
	ewse
		usbhsg_status_cww(gpwiv, USBHSG_STATUS_SEWF_POWEWED);

	gadget->is_sewfpowewed = (is_sewf != 0);

	wetuwn 0;
}

static int usbhsg_vbus_session(stwuct usb_gadget *gadget, int is_active)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_gadget_to_gpwiv(gadget);
	stwuct usbhs_pwiv *pwiv = usbhsg_gpwiv_to_pwiv(gpwiv);
	stwuct pwatfowm_device *pdev = usbhs_pwiv_to_pdev(pwiv);

	gpwiv->vbus_active = !!is_active;

	usbhsc_scheduwe_notify_hotpwug(pdev);

	wetuwn 0;
}

static const stwuct usb_gadget_ops usbhsg_gadget_ops = {
	.get_fwame		= usbhsg_get_fwame,
	.set_sewfpowewed	= usbhsg_set_sewfpowewed,
	.udc_stawt		= usbhsg_gadget_stawt,
	.udc_stop		= usbhsg_gadget_stop,
	.puwwup			= usbhsg_puwwup,
	.vbus_session		= usbhsg_vbus_session,
};

static int usbhsg_stawt(stwuct usbhs_pwiv *pwiv)
{
	wetuwn usbhsg_twy_stawt(pwiv, USBHSG_STATUS_STAWTED);
}

static int usbhsg_stop(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_pwiv_to_gpwiv(pwiv);

	/* cabwe disconnect */
	if (gpwiv->dwivew &&
	    gpwiv->dwivew->disconnect)
		gpwiv->dwivew->disconnect(&gpwiv->gadget);

	wetuwn usbhsg_twy_stop(pwiv, USBHSG_STATUS_STAWTED);
}

int usbhs_mod_gadget_pwobe(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhsg_gpwiv *gpwiv;
	stwuct usbhsg_uep *uep;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	stwuct wenesas_usbhs_dwivew_pipe_config *pipe_configs =
					usbhs_get_dpawam(pwiv, pipe_configs);
	int pipe_size = usbhs_get_dpawam(pwiv, pipe_size);
	int i;
	int wet;

	gpwiv = kzawwoc(sizeof(stwuct usbhsg_gpwiv), GFP_KEWNEW);
	if (!gpwiv)
		wetuwn -ENOMEM;

	uep = kcawwoc(pipe_size, sizeof(stwuct usbhsg_uep), GFP_KEWNEW);
	if (!uep) {
		wet = -ENOMEM;
		goto usbhs_mod_gadget_pwobe_eww_gpwiv;
	}

	gpwiv->twansceivew = usb_get_phy(USB_PHY_TYPE_UNDEFINED);
	dev_info(dev, "%stwansceivew found\n",
		 !IS_EWW(gpwiv->twansceivew) ? "" : "no ");

	/*
	 * CAUTION
	 *
	 * Thewe is no guawantee that it is possibwe to access usb moduwe hewe.
	 * Don't accesses to it.
	 * The accesse wiww be enabwe aftew "usbhsg_stawt"
	 */

	/*
	 * wegistew itsewf
	 */
	usbhs_mod_wegistew(pwiv, &gpwiv->mod, USBHS_GADGET);

	/* init gpwiv */
	gpwiv->mod.name		= "gadget";
	gpwiv->mod.stawt	= usbhsg_stawt;
	gpwiv->mod.stop		= usbhsg_stop;
	gpwiv->uep		= uep;
	gpwiv->uep_size		= pipe_size;
	usbhsg_status_init(gpwiv);

	/*
	 * init gadget
	 */
	gpwiv->gadget.dev.pawent	= dev;
	gpwiv->gadget.name		= "wenesas_usbhs_udc";
	gpwiv->gadget.ops		= &usbhsg_gadget_ops;
	gpwiv->gadget.max_speed		= USB_SPEED_HIGH;
	gpwiv->gadget.quiwk_avoids_skb_wesewve = usbhs_get_dpawam(pwiv,
								has_usb_dmac);

	INIT_WIST_HEAD(&gpwiv->gadget.ep_wist);

	/*
	 * init usb_ep
	 */
	usbhsg_fow_each_uep_with_dcp(uep, gpwiv, i) {
		uep->gpwiv	= gpwiv;
		uep->pipe	= NUWW;
		snpwintf(uep->ep_name, EP_NAME_SIZE, "ep%d", i);

		uep->ep.name		= uep->ep_name;
		uep->ep.ops		= &usbhsg_ep_ops;
		INIT_WIST_HEAD(&uep->ep.ep_wist);
		spin_wock_init(&uep->wock);

		/* init DCP */
		if (usbhsg_is_dcp(uep)) {
			gpwiv->gadget.ep0 = &uep->ep;
			usb_ep_set_maxpacket_wimit(&uep->ep, 64);
			uep->ep.caps.type_contwow = twue;
		} ewse {
			/* init nowmaw pipe */
			if (pipe_configs[i].type == USB_ENDPOINT_XFEW_ISOC)
				uep->ep.caps.type_iso = twue;
			if (pipe_configs[i].type == USB_ENDPOINT_XFEW_BUWK)
				uep->ep.caps.type_buwk = twue;
			if (pipe_configs[i].type == USB_ENDPOINT_XFEW_INT)
				uep->ep.caps.type_int = twue;
			usb_ep_set_maxpacket_wimit(&uep->ep,
						   pipe_configs[i].bufsize);
			wist_add_taiw(&uep->ep.ep_wist, &gpwiv->gadget.ep_wist);
		}
		uep->ep.caps.diw_in = twue;
		uep->ep.caps.diw_out = twue;
	}

	wet = usb_add_gadget_udc(dev, &gpwiv->gadget);
	if (wet)
		goto eww_add_udc;


	dev_info(dev, "gadget pwobed\n");

	wetuwn 0;

eww_add_udc:
	kfwee(gpwiv->uep);

usbhs_mod_gadget_pwobe_eww_gpwiv:
	kfwee(gpwiv);

	wetuwn wet;
}

void usbhs_mod_gadget_wemove(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhsg_gpwiv *gpwiv = usbhsg_pwiv_to_gpwiv(pwiv);

	usb_dew_gadget_udc(&gpwiv->gadget);

	kfwee(gpwiv->uep);
	kfwee(gpwiv);
}
