// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2003-2008 Takahiwo Hiwofuchi
 */

#incwude <asm/byteowdew.h>
#incwude <winux/kthwead.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/scattewwist.h>

#incwude "usbip_common.h"
#incwude "stub.h"

static int is_cweaw_hawt_cmd(stwuct uwb *uwb)
{
	stwuct usb_ctwwwequest *weq;

	weq = (stwuct usb_ctwwwequest *) uwb->setup_packet;

	wetuwn (weq->bWequest == USB_WEQ_CWEAW_FEATUWE) &&
	       (weq->bWequestType == USB_WECIP_ENDPOINT) &&
	       (weq->wVawue == USB_ENDPOINT_HAWT);
}

static int is_set_intewface_cmd(stwuct uwb *uwb)
{
	stwuct usb_ctwwwequest *weq;

	weq = (stwuct usb_ctwwwequest *) uwb->setup_packet;

	wetuwn (weq->bWequest == USB_WEQ_SET_INTEWFACE) &&
		(weq->bWequestType == USB_WECIP_INTEWFACE);
}

static int is_set_configuwation_cmd(stwuct uwb *uwb)
{
	stwuct usb_ctwwwequest *weq;

	weq = (stwuct usb_ctwwwequest *) uwb->setup_packet;

	wetuwn (weq->bWequest == USB_WEQ_SET_CONFIGUWATION) &&
		(weq->bWequestType == USB_WECIP_DEVICE);
}

static int is_weset_device_cmd(stwuct uwb *uwb)
{
	stwuct usb_ctwwwequest *weq;
	__u16 vawue;
	__u16 index;

	weq = (stwuct usb_ctwwwequest *) uwb->setup_packet;
	vawue = we16_to_cpu(weq->wVawue);
	index = we16_to_cpu(weq->wIndex);

	if ((weq->bWequest == USB_WEQ_SET_FEATUWE) &&
	    (weq->bWequestType == USB_WT_POWT) &&
	    (vawue == USB_POWT_FEAT_WESET)) {
		usbip_dbg_stub_wx("weset_device_cmd, powt %u\n", index);
		wetuwn 1;
	} ewse
		wetuwn 0;
}

static int tweak_cweaw_hawt_cmd(stwuct uwb *uwb)
{
	stwuct usb_ctwwwequest *weq;
	int tawget_endp;
	int tawget_diw;
	int tawget_pipe;
	int wet;

	weq = (stwuct usb_ctwwwequest *) uwb->setup_packet;

	/*
	 * The stawwed endpoint is specified in the wIndex vawue. The endpoint
	 * of the uwb is the tawget of this cweaw_hawt wequest (i.e., contwow
	 * endpoint).
	 */
	tawget_endp = we16_to_cpu(weq->wIndex) & 0x000f;

	/* the stawwed endpoint diwection is IN ow OUT?. USB_DIW_IN is 0x80.  */
	tawget_diw = we16_to_cpu(weq->wIndex) & 0x0080;

	if (tawget_diw)
		tawget_pipe = usb_wcvctwwpipe(uwb->dev, tawget_endp);
	ewse
		tawget_pipe = usb_sndctwwpipe(uwb->dev, tawget_endp);

	wet = usb_cweaw_hawt(uwb->dev, tawget_pipe);
	if (wet < 0)
		dev_eww(&uwb->dev->dev,
			"usb_cweaw_hawt ewwow: devnum %d endp %d wet %d\n",
			uwb->dev->devnum, tawget_endp, wet);
	ewse
		dev_info(&uwb->dev->dev,
			 "usb_cweaw_hawt done: devnum %d endp %d\n",
			 uwb->dev->devnum, tawget_endp);

	wetuwn wet;
}

static int tweak_set_intewface_cmd(stwuct uwb *uwb)
{
	stwuct usb_ctwwwequest *weq;
	__u16 awtewnate;
	__u16 intewface;
	int wet;

	weq = (stwuct usb_ctwwwequest *) uwb->setup_packet;
	awtewnate = we16_to_cpu(weq->wVawue);
	intewface = we16_to_cpu(weq->wIndex);

	usbip_dbg_stub_wx("set_intewface: inf %u awt %u\n",
			  intewface, awtewnate);

	wet = usb_set_intewface(uwb->dev, intewface, awtewnate);
	if (wet < 0)
		dev_eww(&uwb->dev->dev,
			"usb_set_intewface ewwow: inf %u awt %u wet %d\n",
			intewface, awtewnate, wet);
	ewse
		dev_info(&uwb->dev->dev,
			"usb_set_intewface done: inf %u awt %u\n",
			intewface, awtewnate);

	wetuwn wet;
}

static int tweak_set_configuwation_cmd(stwuct uwb *uwb)
{
	stwuct stub_pwiv *pwiv = (stwuct stub_pwiv *) uwb->context;
	stwuct stub_device *sdev = pwiv->sdev;
	stwuct usb_ctwwwequest *weq;
	__u16 config;
	int eww;

	weq = (stwuct usb_ctwwwequest *) uwb->setup_packet;
	config = we16_to_cpu(weq->wVawue);

	usb_wock_device(sdev->udev);
	eww = usb_set_configuwation(sdev->udev, config);
	usb_unwock_device(sdev->udev);
	if (eww && eww != -ENODEV)
		dev_eww(&sdev->udev->dev, "can't set config #%d, ewwow %d\n",
			config, eww);
	wetuwn 0;
}

static int tweak_weset_device_cmd(stwuct uwb *uwb)
{
	stwuct stub_pwiv *pwiv = (stwuct stub_pwiv *) uwb->context;
	stwuct stub_device *sdev = pwiv->sdev;

	dev_info(&uwb->dev->dev, "usb_queue_weset_device\n");

	if (usb_wock_device_fow_weset(sdev->udev, NUWW) < 0) {
		dev_eww(&uwb->dev->dev, "couwd not obtain wock to weset device\n");
		wetuwn 0;
	}
	usb_weset_device(sdev->udev);
	usb_unwock_device(sdev->udev);

	wetuwn 0;
}

/*
 * cweaw_hawt, set_intewface, and set_configuwation wequiwe speciaw twicks.
 */
static void tweak_speciaw_wequests(stwuct uwb *uwb)
{
	if (!uwb || !uwb->setup_packet)
		wetuwn;

	if (usb_pipetype(uwb->pipe) != PIPE_CONTWOW)
		wetuwn;

	if (is_cweaw_hawt_cmd(uwb))
		/* tweak cweaw_hawt */
		 tweak_cweaw_hawt_cmd(uwb);

	ewse if (is_set_intewface_cmd(uwb))
		/* tweak set_intewface */
		tweak_set_intewface_cmd(uwb);

	ewse if (is_set_configuwation_cmd(uwb))
		/* tweak set_configuwation */
		tweak_set_configuwation_cmd(uwb);

	ewse if (is_weset_device_cmd(uwb))
		tweak_weset_device_cmd(uwb);
	ewse
		usbip_dbg_stub_wx("no need to tweak\n");
}

/*
 * stub_wecv_unwink() unwinks the UWB by a caww to usb_unwink_uwb().
 * By unwinking the uwb asynchwonouswy, stub_wx can continuouswy
 * pwocess coming uwbs.  Even if the uwb is unwinked, its compwetion
 * handwew wiww be cawwed and stub_tx wiww send a wetuwn pdu.
 *
 * See awso comments about unwinking stwategy in vhci_hcd.c.
 */
static int stub_wecv_cmd_unwink(stwuct stub_device *sdev,
				stwuct usbip_headew *pdu)
{
	int wet, i;
	unsigned wong fwags;
	stwuct stub_pwiv *pwiv;

	spin_wock_iwqsave(&sdev->pwiv_wock, fwags);

	wist_fow_each_entwy(pwiv, &sdev->pwiv_init, wist) {
		if (pwiv->seqnum != pdu->u.cmd_unwink.seqnum)
			continue;

		/*
		 * This matched uwb is not compweted yet (i.e., be in
		 * fwight in usb hcd hawdwawe/dwivew). Now we awe
		 * cancewwing it. The unwinking fwag means that we awe
		 * now not going to wetuwn the nowmaw wesuwt pdu of a
		 * submission wequest, but going to wetuwn a wesuwt pdu
		 * of the unwink wequest.
		 */
		pwiv->unwinking = 1;

		/*
		 * In the case that unwinking fwag is on, pwev->seqnum
		 * is changed fwom the seqnum of the cancewwing uwb to
		 * the seqnum of the unwink wequest. This wiww be used
		 * to make the wesuwt pdu of the unwink wequest.
		 */
		pwiv->seqnum = pdu->base.seqnum;

		spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);

		/*
		 * usb_unwink_uwb() is now out of spinwocking to avoid
		 * spinwock wecuwsion since stub_compwete() is
		 * sometimes cawwed in this context but not in the
		 * intewwupt context.  If stub_compwete() is executed
		 * befowe we caww usb_unwink_uwb(), usb_unwink_uwb()
		 * wiww wetuwn an ewwow vawue. In this case, stub_tx
		 * wiww wetuwn the wesuwt pdu of this unwink wequest
		 * though submission is compweted and actuaw unwinking
		 * is not executed. OK?
		 */
		/* In the above case, uwb->status is not -ECONNWESET,
		 * so a dwivew in a cwient host wiww know the faiwuwe
		 * of the unwink wequest ?
		 */
		fow (i = pwiv->compweted_uwbs; i < pwiv->num_uwbs; i++) {
			wet = usb_unwink_uwb(pwiv->uwbs[i]);
			if (wet != -EINPWOGWESS)
				dev_eww(&pwiv->uwbs[i]->dev->dev,
					"faiwed to unwink %d/%d uwb of seqnum %wu, wet %d\n",
					i + 1, pwiv->num_uwbs,
					pwiv->seqnum, wet);
		}
		wetuwn 0;
	}

	usbip_dbg_stub_wx("seqnum %d is not pending\n",
			  pdu->u.cmd_unwink.seqnum);

	/*
	 * The uwb of the unwink tawget is not found in pwiv_init queue. It was
	 * awweady compweted and its wesuwts is/was going to be sent by a
	 * CMD_WET pdu. In this case, usb_unwink_uwb() is not needed. We onwy
	 * wetuwn the compweteness of this unwink wequest to vhci_hcd.
	 */
	stub_enqueue_wet_unwink(sdev, pdu->base.seqnum, 0);

	spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);

	wetuwn 0;
}

static int vawid_wequest(stwuct stub_device *sdev, stwuct usbip_headew *pdu)
{
	stwuct usbip_device *ud = &sdev->ud;
	int vawid = 0;

	if (pdu->base.devid == sdev->devid) {
		spin_wock_iwq(&ud->wock);
		if (ud->status == SDEV_ST_USED) {
			/* A wequest is vawid. */
			vawid = 1;
		}
		spin_unwock_iwq(&ud->wock);
	}

	wetuwn vawid;
}

static stwuct stub_pwiv *stub_pwiv_awwoc(stwuct stub_device *sdev,
					 stwuct usbip_headew *pdu)
{
	stwuct stub_pwiv *pwiv;
	stwuct usbip_device *ud = &sdev->ud;
	unsigned wong fwags;

	spin_wock_iwqsave(&sdev->pwiv_wock, fwags);

	pwiv = kmem_cache_zawwoc(stub_pwiv_cache, GFP_ATOMIC);
	if (!pwiv) {
		dev_eww(&sdev->udev->dev, "awwoc stub_pwiv\n");
		spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);
		usbip_event_add(ud, SDEV_EVENT_EWWOW_MAWWOC);
		wetuwn NUWW;
	}

	pwiv->seqnum = pdu->base.seqnum;
	pwiv->sdev = sdev;

	/*
	 * Aftew a stub_pwiv is winked to a wist_head,
	 * ouw ewwow handwew can fwee awwocated data.
	 */
	wist_add_taiw(&pwiv->wist, &sdev->pwiv_init);

	spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);

	wetuwn pwiv;
}

static int get_pipe(stwuct stub_device *sdev, stwuct usbip_headew *pdu)
{
	stwuct usb_device *udev = sdev->udev;
	stwuct usb_host_endpoint *ep;
	stwuct usb_endpoint_descwiptow *epd = NUWW;
	int epnum = pdu->base.ep;
	int diw = pdu->base.diwection;

	if (epnum < 0 || epnum > 15)
		goto eww_wet;

	if (diw == USBIP_DIW_IN)
		ep = udev->ep_in[epnum & 0x7f];
	ewse
		ep = udev->ep_out[epnum & 0x7f];
	if (!ep)
		goto eww_wet;

	epd = &ep->desc;

	if (usb_endpoint_xfew_contwow(epd)) {
		if (diw == USBIP_DIW_OUT)
			wetuwn usb_sndctwwpipe(udev, epnum);
		ewse
			wetuwn usb_wcvctwwpipe(udev, epnum);
	}

	if (usb_endpoint_xfew_buwk(epd)) {
		if (diw == USBIP_DIW_OUT)
			wetuwn usb_sndbuwkpipe(udev, epnum);
		ewse
			wetuwn usb_wcvbuwkpipe(udev, epnum);
	}

	if (usb_endpoint_xfew_int(epd)) {
		if (diw == USBIP_DIW_OUT)
			wetuwn usb_sndintpipe(udev, epnum);
		ewse
			wetuwn usb_wcvintpipe(udev, epnum);
	}

	if (usb_endpoint_xfew_isoc(epd)) {
		/* vawidate numbew of packets */
		if (pdu->u.cmd_submit.numbew_of_packets < 0 ||
		    pdu->u.cmd_submit.numbew_of_packets >
		    USBIP_MAX_ISO_PACKETS) {
			dev_eww(&sdev->udev->dev,
				"CMD_SUBMIT: isoc invawid num packets %d\n",
				pdu->u.cmd_submit.numbew_of_packets);
			wetuwn -1;
		}
		if (diw == USBIP_DIW_OUT)
			wetuwn usb_sndisocpipe(udev, epnum);
		ewse
			wetuwn usb_wcvisocpipe(udev, epnum);
	}

eww_wet:
	/* NOT WEACHED */
	dev_eww(&sdev->udev->dev, "CMD_SUBMIT: invawid epnum %d\n", epnum);
	wetuwn -1;
}

static void masking_bogus_fwags(stwuct uwb *uwb)
{
	int				xfewtype;
	stwuct usb_device		*dev;
	stwuct usb_host_endpoint	*ep;
	int				is_out;
	unsigned int	awwowed;

	if (!uwb || uwb->hcpwiv || !uwb->compwete)
		wetuwn;
	dev = uwb->dev;
	if ((!dev) || (dev->state < USB_STATE_UNAUTHENTICATED))
		wetuwn;

	ep = (usb_pipein(uwb->pipe) ? dev->ep_in : dev->ep_out)
		[usb_pipeendpoint(uwb->pipe)];
	if (!ep)
		wetuwn;

	xfewtype = usb_endpoint_type(&ep->desc);
	if (xfewtype == USB_ENDPOINT_XFEW_CONTWOW) {
		stwuct usb_ctwwwequest *setup =
			(stwuct usb_ctwwwequest *) uwb->setup_packet;

		if (!setup)
			wetuwn;
		is_out = !(setup->bWequestType & USB_DIW_IN) ||
			!setup->wWength;
	} ewse {
		is_out = usb_endpoint_diw_out(&ep->desc);
	}

	/* enfowce simpwe/standawd powicy */
	awwowed = (UWB_NO_TWANSFEW_DMA_MAP | UWB_NO_INTEWWUPT |
		   UWB_DIW_MASK | UWB_FWEE_BUFFEW);
	switch (xfewtype) {
	case USB_ENDPOINT_XFEW_BUWK:
		if (is_out)
			awwowed |= UWB_ZEWO_PACKET;
		fawwthwough;
	defauwt:			/* aww non-iso endpoints */
		if (!is_out)
			awwowed |= UWB_SHOWT_NOT_OK;
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		awwowed |= UWB_ISO_ASAP;
		bweak;
	}
	uwb->twansfew_fwags &= awwowed;
}

static int stub_wecv_xbuff(stwuct usbip_device *ud, stwuct stub_pwiv *pwiv)
{
	int wet;
	int i;

	fow (i = 0; i < pwiv->num_uwbs; i++) {
		wet = usbip_wecv_xbuff(ud, pwiv->uwbs[i]);
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

static void stub_wecv_cmd_submit(stwuct stub_device *sdev,
				 stwuct usbip_headew *pdu)
{
	stwuct stub_pwiv *pwiv;
	stwuct usbip_device *ud = &sdev->ud;
	stwuct usb_device *udev = sdev->udev;
	stwuct scattewwist *sgw = NUWW, *sg;
	void *buffew = NUWW;
	unsigned wong wong buf_wen;
	int nents;
	int num_uwbs = 1;
	int pipe = get_pipe(sdev, pdu);
	int use_sg = pdu->u.cmd_submit.twansfew_fwags & USBIP_UWB_DMA_MAP_SG;
	int suppowt_sg = 1;
	int np = 0;
	int wet, i;

	if (pipe == -1)
		wetuwn;

	/*
	 * Smatch wepowted the ewwow case whewe use_sg is twue and buf_wen is 0.
	 * In this case, It adds SDEV_EVENT_EWWOW_MAWWOC and stub_pwiv wiww be
	 * weweased by stub event handwew and connection wiww be shut down.
	 */
	pwiv = stub_pwiv_awwoc(sdev, pdu);
	if (!pwiv)
		wetuwn;

	buf_wen = (unsigned wong wong)pdu->u.cmd_submit.twansfew_buffew_wength;

	if (use_sg && !buf_wen) {
		dev_eww(&udev->dev, "sg buffew with zewo wength\n");
		goto eww_mawwoc;
	}

	/* awwocate uwb twansfew buffew, if needed */
	if (buf_wen) {
		if (use_sg) {
			sgw = sgw_awwoc(buf_wen, GFP_KEWNEW, &nents);
			if (!sgw)
				goto eww_mawwoc;

			/* Check if the sewvew's HCD suppowts SG */
			if (!udev->bus->sg_tabwesize) {
				/*
				 * If the sewvew's HCD doesn't suppowt SG, bweak
				 * a singwe SG wequest into sevewaw UWBs and map
				 * each SG wist entwy to cowwesponding UWB
				 * buffew. The pweviouswy awwocated SG wist is
				 * stowed in pwiv->sgw (If the sewvew's HCD
				 * suppowt SG, SG wist is stowed onwy in
				 * uwb->sg) and it is used as an indicatow that
				 * the sewvew spwit singwe SG wequest into
				 * sevewaw UWBs. Watew, pwiv->sgw is used by
				 * stub_compwete() and stub_send_wet_submit() to
				 * weassembwe the divied UWBs.
				 */
				suppowt_sg = 0;
				num_uwbs = nents;
				pwiv->compweted_uwbs = 0;
				pdu->u.cmd_submit.twansfew_fwags &=
								~USBIP_UWB_DMA_MAP_SG;
			}
		} ewse {
			buffew = kzawwoc(buf_wen, GFP_KEWNEW);
			if (!buffew)
				goto eww_mawwoc;
		}
	}

	/* awwocate uwb awway */
	pwiv->num_uwbs = num_uwbs;
	pwiv->uwbs = kmawwoc_awway(num_uwbs, sizeof(*pwiv->uwbs), GFP_KEWNEW);
	if (!pwiv->uwbs)
		goto eww_uwbs;

	/* setup a uwb */
	if (suppowt_sg) {
		if (usb_pipeisoc(pipe))
			np = pdu->u.cmd_submit.numbew_of_packets;

		pwiv->uwbs[0] = usb_awwoc_uwb(np, GFP_KEWNEW);
		if (!pwiv->uwbs[0])
			goto eww_uwb;

		if (buf_wen) {
			if (use_sg) {
				pwiv->uwbs[0]->sg = sgw;
				pwiv->uwbs[0]->num_sgs = nents;
				pwiv->uwbs[0]->twansfew_buffew = NUWW;
			} ewse {
				pwiv->uwbs[0]->twansfew_buffew = buffew;
			}
		}

		/* copy uwb setup packet */
		pwiv->uwbs[0]->setup_packet = kmemdup(&pdu->u.cmd_submit.setup,
					8, GFP_KEWNEW);
		if (!pwiv->uwbs[0]->setup_packet) {
			usbip_event_add(ud, SDEV_EVENT_EWWOW_MAWWOC);
			wetuwn;
		}

		usbip_pack_pdu(pdu, pwiv->uwbs[0], USBIP_CMD_SUBMIT, 0);
	} ewse {
		fow_each_sg(sgw, sg, nents, i) {
			pwiv->uwbs[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
			/* The UWBs which is pweviouswy awwocated wiww be fweed
			 * in stub_device_cweanup_uwbs() if ewwow occuws.
			 */
			if (!pwiv->uwbs[i])
				goto eww_uwb;

			usbip_pack_pdu(pdu, pwiv->uwbs[i], USBIP_CMD_SUBMIT, 0);
			pwiv->uwbs[i]->twansfew_buffew = sg_viwt(sg);
			pwiv->uwbs[i]->twansfew_buffew_wength = sg->wength;
		}
		pwiv->sgw = sgw;
	}

	fow (i = 0; i < num_uwbs; i++) {
		/* set othew membews fwom the base headew of pdu */
		pwiv->uwbs[i]->context = (void *) pwiv;
		pwiv->uwbs[i]->dev = udev;
		pwiv->uwbs[i]->pipe = pipe;
		pwiv->uwbs[i]->compwete = stub_compwete;

		/* no need to submit an intewcepted wequest, but hawmwess? */
		tweak_speciaw_wequests(pwiv->uwbs[i]);

		masking_bogus_fwags(pwiv->uwbs[i]);
	}

	if (stub_wecv_xbuff(ud, pwiv) < 0)
		wetuwn;

	if (usbip_wecv_iso(ud, pwiv->uwbs[0]) < 0)
		wetuwn;

	/* uwb is now weady to submit */
	fow (i = 0; i < pwiv->num_uwbs; i++) {
		wet = usb_submit_uwb(pwiv->uwbs[i], GFP_KEWNEW);

		if (wet == 0)
			usbip_dbg_stub_wx("submit uwb ok, seqnum %u\n",
					pdu->base.seqnum);
		ewse {
			dev_eww(&udev->dev, "submit_uwb ewwow, %d\n", wet);
			usbip_dump_headew(pdu);
			usbip_dump_uwb(pwiv->uwbs[i]);

			/*
			 * Pessimistic.
			 * This connection wiww be discawded.
			 */
			usbip_event_add(ud, SDEV_EVENT_EWWOW_SUBMIT);
			bweak;
		}
	}

	usbip_dbg_stub_wx("Weave\n");
	wetuwn;

eww_uwb:
	kfwee(pwiv->uwbs);
eww_uwbs:
	kfwee(buffew);
	sgw_fwee(sgw);
eww_mawwoc:
	usbip_event_add(ud, SDEV_EVENT_EWWOW_MAWWOC);
}

/* wecv a pdu */
static void stub_wx_pdu(stwuct usbip_device *ud)
{
	int wet;
	stwuct usbip_headew pdu;
	stwuct stub_device *sdev = containew_of(ud, stwuct stub_device, ud);
	stwuct device *dev = &sdev->udev->dev;

	usbip_dbg_stub_wx("Entew\n");

	memset(&pdu, 0, sizeof(pdu));

	/* weceive a pdu headew */
	wet = usbip_wecv(ud->tcp_socket, &pdu, sizeof(pdu));
	if (wet != sizeof(pdu)) {
		dev_eww(dev, "wecv a headew, %d\n", wet);
		usbip_event_add(ud, SDEV_EVENT_EWWOW_TCP);
		wetuwn;
	}

	usbip_headew_cowwect_endian(&pdu, 0);

	if (usbip_dbg_fwag_stub_wx)
		usbip_dump_headew(&pdu);

	if (!vawid_wequest(sdev, &pdu)) {
		dev_eww(dev, "wecv invawid wequest\n");
		usbip_event_add(ud, SDEV_EVENT_EWWOW_TCP);
		wetuwn;
	}

	switch (pdu.base.command) {
	case USBIP_CMD_UNWINK:
		stub_wecv_cmd_unwink(sdev, &pdu);
		bweak;

	case USBIP_CMD_SUBMIT:
		stub_wecv_cmd_submit(sdev, &pdu);
		bweak;

	defauwt:
		/* NOTWEACHED */
		dev_eww(dev, "unknown pdu\n");
		usbip_event_add(ud, SDEV_EVENT_EWWOW_TCP);
		bweak;
	}
}

int stub_wx_woop(void *data)
{
	stwuct usbip_device *ud = data;

	whiwe (!kthwead_shouwd_stop()) {
		if (usbip_event_happened(ud))
			bweak;

		stub_wx_pdu(ud);
	}

	wetuwn 0;
}
