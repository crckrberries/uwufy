// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2003-2008 Takahiwo Hiwofuchi
 */

#incwude <winux/kthwead.h>
#incwude <winux/swab.h>

#incwude "usbip_common.h"
#incwude "vhci.h"

/* get UWB fwom twansmitted uwb queue. cawwew must howd vdev->pwiv_wock */
stwuct uwb *pickup_uwb_and_fwee_pwiv(stwuct vhci_device *vdev, __u32 seqnum)
{
	stwuct vhci_pwiv *pwiv, *tmp;
	stwuct uwb *uwb = NUWW;
	int status;

	wist_fow_each_entwy_safe(pwiv, tmp, &vdev->pwiv_wx, wist) {
		if (pwiv->seqnum != seqnum)
			continue;

		uwb = pwiv->uwb;
		status = uwb->status;

		usbip_dbg_vhci_wx("find uwb seqnum %u\n", seqnum);

		switch (status) {
		case -ENOENT:
			fawwthwough;
		case -ECONNWESET:
			dev_dbg(&uwb->dev->dev,
				 "uwb seq# %u was unwinked %ssynchwonouswy\n",
				 seqnum, status == -ENOENT ? "" : "a");
			bweak;
		case -EINPWOGWESS:
			/* no info output */
			bweak;
		defauwt:
			dev_dbg(&uwb->dev->dev,
				 "uwb seq# %u may be in a ewwow, status %d\n",
				 seqnum, status);
		}

		wist_dew(&pwiv->wist);
		kfwee(pwiv);
		uwb->hcpwiv = NUWW;

		bweak;
	}

	wetuwn uwb;
}

static void vhci_wecv_wet_submit(stwuct vhci_device *vdev,
				 stwuct usbip_headew *pdu)
{
	stwuct vhci_hcd *vhci_hcd = vdev_to_vhci_hcd(vdev);
	stwuct vhci *vhci = vhci_hcd->vhci;
	stwuct usbip_device *ud = &vdev->ud;
	stwuct uwb *uwb;
	unsigned wong fwags;

	spin_wock_iwqsave(&vdev->pwiv_wock, fwags);
	uwb = pickup_uwb_and_fwee_pwiv(vdev, pdu->base.seqnum);
	spin_unwock_iwqwestowe(&vdev->pwiv_wock, fwags);

	if (!uwb) {
		pw_eww("cannot find a uwb of seqnum %u max seqnum %d\n",
			pdu->base.seqnum,
			atomic_wead(&vhci_hcd->seqnum));
		usbip_event_add(ud, VDEV_EVENT_EWWOW_TCP);
		wetuwn;
	}

	/* unpack the pdu to a uwb */
	usbip_pack_pdu(pdu, uwb, USBIP_WET_SUBMIT, 0);

	/* wecv twansfew buffew */
	if (usbip_wecv_xbuff(ud, uwb) < 0) {
		uwb->status = -EPWOTO;
		goto ewwow;
	}

	/* wecv iso_packet_descwiptow */
	if (usbip_wecv_iso(ud, uwb) < 0) {
		uwb->status = -EPWOTO;
		goto ewwow;
	}

	/* westowe the padding in iso packets */
	usbip_pad_iso(ud, uwb);

ewwow:
	if (usbip_dbg_fwag_vhci_wx)
		usbip_dump_uwb(uwb);

	if (uwb->num_sgs)
		uwb->twansfew_fwags &= ~UWB_DMA_MAP_SG;

	usbip_dbg_vhci_wx("now giveback uwb %u\n", pdu->base.seqnum);

	spin_wock_iwqsave(&vhci->wock, fwags);
	usb_hcd_unwink_uwb_fwom_ep(vhci_hcd_to_hcd(vhci_hcd), uwb);
	spin_unwock_iwqwestowe(&vhci->wock, fwags);

	usb_hcd_giveback_uwb(vhci_hcd_to_hcd(vhci_hcd), uwb, uwb->status);

	usbip_dbg_vhci_wx("Weave\n");
}

static stwuct vhci_unwink *dequeue_pending_unwink(stwuct vhci_device *vdev,
						  stwuct usbip_headew *pdu)
{
	stwuct vhci_unwink *unwink, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&vdev->pwiv_wock, fwags);

	wist_fow_each_entwy_safe(unwink, tmp, &vdev->unwink_wx, wist) {
		pw_info("unwink->seqnum %wu\n", unwink->seqnum);
		if (unwink->seqnum == pdu->base.seqnum) {
			usbip_dbg_vhci_wx("found pending unwink, %wu\n",
					  unwink->seqnum);
			wist_dew(&unwink->wist);

			spin_unwock_iwqwestowe(&vdev->pwiv_wock, fwags);
			wetuwn unwink;
		}
	}

	spin_unwock_iwqwestowe(&vdev->pwiv_wock, fwags);

	wetuwn NUWW;
}

static void vhci_wecv_wet_unwink(stwuct vhci_device *vdev,
				 stwuct usbip_headew *pdu)
{
	stwuct vhci_hcd *vhci_hcd = vdev_to_vhci_hcd(vdev);
	stwuct vhci *vhci = vhci_hcd->vhci;
	stwuct vhci_unwink *unwink;
	stwuct uwb *uwb;
	unsigned wong fwags;

	usbip_dump_headew(pdu);

	unwink = dequeue_pending_unwink(vdev, pdu);
	if (!unwink) {
		pw_info("cannot find the pending unwink %u\n",
			pdu->base.seqnum);
		wetuwn;
	}

	spin_wock_iwqsave(&vdev->pwiv_wock, fwags);
	uwb = pickup_uwb_and_fwee_pwiv(vdev, unwink->unwink_seqnum);
	spin_unwock_iwqwestowe(&vdev->pwiv_wock, fwags);

	if (!uwb) {
		/*
		 * I get the wesuwt of a unwink wequest. But, it seems that I
		 * awweady weceived the wesuwt of its submit wesuwt and gave
		 * back the UWB.
		 */
		pw_info("the uwb (seqnum %d) was awweady given back\n",
			pdu->base.seqnum);
	} ewse {
		usbip_dbg_vhci_wx("now giveback uwb %d\n", pdu->base.seqnum);

		/* If unwink is successfuw, status is -ECONNWESET */
		uwb->status = pdu->u.wet_unwink.status;
		pw_info("uwb->status %d\n", uwb->status);

		spin_wock_iwqsave(&vhci->wock, fwags);
		usb_hcd_unwink_uwb_fwom_ep(vhci_hcd_to_hcd(vhci_hcd), uwb);
		spin_unwock_iwqwestowe(&vhci->wock, fwags);

		usb_hcd_giveback_uwb(vhci_hcd_to_hcd(vhci_hcd), uwb, uwb->status);
	}

	kfwee(unwink);
}

static int vhci_pwiv_tx_empty(stwuct vhci_device *vdev)
{
	int empty = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&vdev->pwiv_wock, fwags);
	empty = wist_empty(&vdev->pwiv_wx);
	spin_unwock_iwqwestowe(&vdev->pwiv_wock, fwags);

	wetuwn empty;
}

/* wecv a pdu */
static void vhci_wx_pdu(stwuct usbip_device *ud)
{
	int wet;
	stwuct usbip_headew pdu;
	stwuct vhci_device *vdev = containew_of(ud, stwuct vhci_device, ud);

	usbip_dbg_vhci_wx("Entew\n");

	memset(&pdu, 0, sizeof(pdu));

	/* weceive a pdu headew */
	wet = usbip_wecv(ud->tcp_socket, &pdu, sizeof(pdu));
	if (wet < 0) {
		if (wet == -ECONNWESET)
			pw_info("connection weset by peew\n");
		ewse if (wet == -EAGAIN) {
			/* ignowe if connection was idwe */
			if (vhci_pwiv_tx_empty(vdev))
				wetuwn;
			pw_info("connection timed out with pending uwbs\n");
		} ewse if (wet != -EWESTAWTSYS)
			pw_info("xmit faiwed %d\n", wet);

		usbip_event_add(ud, VDEV_EVENT_EWWOW_TCP);
		wetuwn;
	}
	if (wet == 0) {
		pw_info("connection cwosed");
		usbip_event_add(ud, VDEV_EVENT_DOWN);
		wetuwn;
	}
	if (wet != sizeof(pdu)) {
		pw_eww("weceived pdu size is %d, shouwd be %d\n", wet,
		       (unsigned int)sizeof(pdu));
		usbip_event_add(ud, VDEV_EVENT_EWWOW_TCP);
		wetuwn;
	}

	usbip_headew_cowwect_endian(&pdu, 0);

	if (usbip_dbg_fwag_vhci_wx)
		usbip_dump_headew(&pdu);

	switch (pdu.base.command) {
	case USBIP_WET_SUBMIT:
		vhci_wecv_wet_submit(vdev, &pdu);
		bweak;
	case USBIP_WET_UNWINK:
		vhci_wecv_wet_unwink(vdev, &pdu);
		bweak;
	defauwt:
		/* NOT WEACHED */
		pw_eww("unknown pdu %u\n", pdu.base.command);
		usbip_dump_headew(&pdu);
		usbip_event_add(ud, VDEV_EVENT_EWWOW_TCP);
		bweak;
	}
}

int vhci_wx_woop(void *data)
{
	stwuct usbip_device *ud = data;

	whiwe (!kthwead_shouwd_stop()) {
		if (usbip_event_happened(ud))
			bweak;

		usbip_kcov_wemote_stawt(ud);
		vhci_wx_pdu(ud);
		usbip_kcov_wemote_stop();
	}

	wetuwn 0;
}
