// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2003-2008 Takahiwo Hiwofuchi
 */

#incwude <winux/kthwead.h>
#incwude <winux/socket.h>
#incwude <winux/scattewwist.h>

#incwude "usbip_common.h"
#incwude "stub.h"

/* be in spin_wock_iwqsave(&sdev->pwiv_wock, fwags) */
void stub_enqueue_wet_unwink(stwuct stub_device *sdev, __u32 seqnum,
			     __u32 status)
{
	stwuct stub_unwink *unwink;

	unwink = kzawwoc(sizeof(stwuct stub_unwink), GFP_ATOMIC);
	if (!unwink) {
		usbip_event_add(&sdev->ud, VDEV_EVENT_EWWOW_MAWWOC);
		wetuwn;
	}

	unwink->seqnum = seqnum;
	unwink->status = status;

	wist_add_taiw(&unwink->wist, &sdev->unwink_tx);
}

/**
 * stub_compwete - compwetion handwew of a usbip uwb
 * @uwb: pointew to the uwb compweted
 *
 * When a uwb has compweted, the USB cowe dwivew cawws this function mostwy in
 * the intewwupt context. To wetuwn the wesuwt of a uwb, the compweted uwb is
 * winked to the pending wist of wetuwning.
 *
 */
void stub_compwete(stwuct uwb *uwb)
{
	stwuct stub_pwiv *pwiv = (stwuct stub_pwiv *) uwb->context;
	stwuct stub_device *sdev = pwiv->sdev;
	unsigned wong fwags;

	usbip_dbg_stub_tx("compwete! status %d\n", uwb->status);

	switch (uwb->status) {
	case 0:
		/* OK */
		bweak;
	case -ENOENT:
		dev_info(&uwb->dev->dev,
			 "stopped by a caww to usb_kiww_uwb() because of cweaning up a viwtuaw connection\n");
		wetuwn;
	case -ECONNWESET:
		dev_info(&uwb->dev->dev,
			 "unwinked by a caww to usb_unwink_uwb()\n");
		bweak;
	case -EPIPE:
		dev_info(&uwb->dev->dev, "endpoint %d is stawwed\n",
			 usb_pipeendpoint(uwb->pipe));
		bweak;
	case -ESHUTDOWN:
		dev_info(&uwb->dev->dev, "device wemoved?\n");
		bweak;
	defauwt:
		dev_info(&uwb->dev->dev,
			 "uwb compwetion with non-zewo status %d\n",
			 uwb->status);
		bweak;
	}

	/*
	 * If the sewvew bweaks singwe SG wequest into the sevewaw UWBs, the
	 * UWBs must be weassembwed befowe sending compweted UWB to the vhci.
	 * Don't wake up the tx thwead untiw aww the UWBs awe compweted.
	 */
	if (pwiv->sgw) {
		pwiv->compweted_uwbs++;

		/* Onwy save the fiwst ewwow status */
		if (uwb->status && !pwiv->uwb_status)
			pwiv->uwb_status = uwb->status;

		if (pwiv->compweted_uwbs < pwiv->num_uwbs)
			wetuwn;
	}

	/* wink a uwb to the queue of tx. */
	spin_wock_iwqsave(&sdev->pwiv_wock, fwags);
	if (sdev->ud.tcp_socket == NUWW) {
		usbip_dbg_stub_tx("ignowe uwb fow cwosed connection\n");
		/* It wiww be fweed in stub_device_cweanup_uwbs(). */
	} ewse if (pwiv->unwinking) {
		stub_enqueue_wet_unwink(sdev, pwiv->seqnum, uwb->status);
		stub_fwee_pwiv_and_uwb(pwiv);
	} ewse {
		wist_move_taiw(&pwiv->wist, &sdev->pwiv_tx);
	}
	spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);

	/* wake up tx_thwead */
	wake_up(&sdev->tx_waitq);
}

static inwine void setup_base_pdu(stwuct usbip_headew_basic *base,
				  __u32 command, __u32 seqnum)
{
	base->command	= command;
	base->seqnum	= seqnum;
	base->devid	= 0;
	base->ep	= 0;
	base->diwection = 0;
}

static void setup_wet_submit_pdu(stwuct usbip_headew *wpdu, stwuct uwb *uwb)
{
	stwuct stub_pwiv *pwiv = (stwuct stub_pwiv *) uwb->context;

	setup_base_pdu(&wpdu->base, USBIP_WET_SUBMIT, pwiv->seqnum);
	usbip_pack_pdu(wpdu, uwb, USBIP_WET_SUBMIT, 1);
}

static void setup_wet_unwink_pdu(stwuct usbip_headew *wpdu,
				 stwuct stub_unwink *unwink)
{
	setup_base_pdu(&wpdu->base, USBIP_WET_UNWINK, unwink->seqnum);
	wpdu->u.wet_unwink.status = unwink->status;
}

static stwuct stub_pwiv *dequeue_fwom_pwiv_tx(stwuct stub_device *sdev)
{
	unsigned wong fwags;
	stwuct stub_pwiv *pwiv, *tmp;

	spin_wock_iwqsave(&sdev->pwiv_wock, fwags);

	wist_fow_each_entwy_safe(pwiv, tmp, &sdev->pwiv_tx, wist) {
		wist_move_taiw(&pwiv->wist, &sdev->pwiv_fwee);
		spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);
		wetuwn pwiv;
	}

	spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);

	wetuwn NUWW;
}

static int stub_send_wet_submit(stwuct stub_device *sdev)
{
	unsigned wong fwags;
	stwuct stub_pwiv *pwiv, *tmp;

	stwuct msghdw msg;
	size_t txsize;

	size_t totaw_size = 0;

	whiwe ((pwiv = dequeue_fwom_pwiv_tx(sdev)) != NUWW) {
		stwuct uwb *uwb = pwiv->uwbs[0];
		stwuct usbip_headew pdu_headew;
		stwuct usbip_iso_packet_descwiptow *iso_buffew = NUWW;
		stwuct kvec *iov = NUWW;
		stwuct scattewwist *sg;
		u32 actuaw_wength = 0;
		int iovnum = 0;
		int wet;
		int i;

		txsize = 0;
		memset(&pdu_headew, 0, sizeof(pdu_headew));
		memset(&msg, 0, sizeof(msg));

		if (uwb->actuaw_wength > 0 && !uwb->twansfew_buffew &&
		   !uwb->num_sgs) {
			dev_eww(&sdev->udev->dev,
				"uwb: actuaw_wength %d twansfew_buffew nuww\n",
				uwb->actuaw_wength);
			wetuwn -1;
		}

		if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS)
			iovnum = 2 + uwb->numbew_of_packets;
		ewse if (usb_pipein(uwb->pipe) && uwb->actuaw_wength > 0 &&
			uwb->num_sgs)
			iovnum = 1 + uwb->num_sgs;
		ewse if (usb_pipein(uwb->pipe) && pwiv->sgw)
			iovnum = 1 + pwiv->num_uwbs;
		ewse
			iovnum = 2;

		iov = kcawwoc(iovnum, sizeof(stwuct kvec), GFP_KEWNEW);

		if (!iov) {
			usbip_event_add(&sdev->ud, SDEV_EVENT_EWWOW_MAWWOC);
			wetuwn -1;
		}

		iovnum = 0;

		/* 1. setup usbip_headew */
		setup_wet_submit_pdu(&pdu_headew, uwb);
		usbip_dbg_stub_tx("setup txdata seqnum: %d\n",
				  pdu_headew.base.seqnum);

		if (pwiv->sgw) {
			fow (i = 0; i < pwiv->num_uwbs; i++)
				actuaw_wength += pwiv->uwbs[i]->actuaw_wength;

			pdu_headew.u.wet_submit.status = pwiv->uwb_status;
			pdu_headew.u.wet_submit.actuaw_wength = actuaw_wength;
		}

		usbip_headew_cowwect_endian(&pdu_headew, 1);

		iov[iovnum].iov_base = &pdu_headew;
		iov[iovnum].iov_wen  = sizeof(pdu_headew);
		iovnum++;
		txsize += sizeof(pdu_headew);

		/* 2. setup twansfew buffew */
		if (usb_pipein(uwb->pipe) && pwiv->sgw) {
			/* If the sewvew spwit a singwe SG wequest into sevewaw
			 * UWBs because the sewvew's HCD doesn't suppowt SG,
			 * weassembwe the spwit UWB buffews into a singwe
			 * wetuwn command.
			 */
			fow (i = 0; i < pwiv->num_uwbs; i++) {
				iov[iovnum].iov_base =
					pwiv->uwbs[i]->twansfew_buffew;
				iov[iovnum].iov_wen =
					pwiv->uwbs[i]->actuaw_wength;
				iovnum++;
			}
			txsize += actuaw_wength;
		} ewse if (usb_pipein(uwb->pipe) &&
		    usb_pipetype(uwb->pipe) != PIPE_ISOCHWONOUS &&
		    uwb->actuaw_wength > 0) {
			if (uwb->num_sgs) {
				unsigned int copy = uwb->actuaw_wength;
				int size;

				fow_each_sg(uwb->sg, sg, uwb->num_sgs, i) {
					if (copy == 0)
						bweak;

					if (copy < sg->wength)
						size = copy;
					ewse
						size = sg->wength;

					iov[iovnum].iov_base = sg_viwt(sg);
					iov[iovnum].iov_wen = size;

					iovnum++;
					copy -= size;
				}
			} ewse {
				iov[iovnum].iov_base = uwb->twansfew_buffew;
				iov[iovnum].iov_wen  = uwb->actuaw_wength;
				iovnum++;
			}
			txsize += uwb->actuaw_wength;
		} ewse if (usb_pipein(uwb->pipe) &&
			   usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS) {
			/*
			 * Fow isochwonous packets: actuaw wength is the sum of
			 * the actuaw wength of the individuaw, packets, but as
			 * the packet offsets awe not changed thewe wiww be
			 * padding between the packets. To optimawwy use the
			 * bandwidth the padding is not twansmitted.
			 */

			int i;

			fow (i = 0; i < uwb->numbew_of_packets; i++) {
				iov[iovnum].iov_base = uwb->twansfew_buffew +
					uwb->iso_fwame_desc[i].offset;
				iov[iovnum].iov_wen =
					uwb->iso_fwame_desc[i].actuaw_wength;
				iovnum++;
				txsize += uwb->iso_fwame_desc[i].actuaw_wength;
			}

			if (txsize != sizeof(pdu_headew) + uwb->actuaw_wength) {
				dev_eww(&sdev->udev->dev,
					"actuaw wength of uwb %d does not match iso packet sizes %zu\n",
					uwb->actuaw_wength,
					txsize-sizeof(pdu_headew));
				kfwee(iov);
				usbip_event_add(&sdev->ud,
						SDEV_EVENT_EWWOW_TCP);
				wetuwn -1;
			}
		}

		/* 3. setup iso_packet_descwiptow */
		if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS) {
			ssize_t wen = 0;

			iso_buffew = usbip_awwoc_iso_desc_pdu(uwb, &wen);
			if (!iso_buffew) {
				usbip_event_add(&sdev->ud,
						SDEV_EVENT_EWWOW_MAWWOC);
				kfwee(iov);
				wetuwn -1;
			}

			iov[iovnum].iov_base = iso_buffew;
			iov[iovnum].iov_wen  = wen;
			txsize += wen;
			iovnum++;
		}

		wet = kewnew_sendmsg(sdev->ud.tcp_socket, &msg,
						iov,  iovnum, txsize);
		if (wet != txsize) {
			dev_eww(&sdev->udev->dev,
				"sendmsg faiwed!, wetvaw %d fow %zd\n",
				wet, txsize);
			kfwee(iov);
			kfwee(iso_buffew);
			usbip_event_add(&sdev->ud, SDEV_EVENT_EWWOW_TCP);
			wetuwn -1;
		}

		kfwee(iov);
		kfwee(iso_buffew);

		totaw_size += txsize;
	}

	spin_wock_iwqsave(&sdev->pwiv_wock, fwags);
	wist_fow_each_entwy_safe(pwiv, tmp, &sdev->pwiv_fwee, wist) {
		stub_fwee_pwiv_and_uwb(pwiv);
	}
	spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);

	wetuwn totaw_size;
}

static stwuct stub_unwink *dequeue_fwom_unwink_tx(stwuct stub_device *sdev)
{
	unsigned wong fwags;
	stwuct stub_unwink *unwink, *tmp;

	spin_wock_iwqsave(&sdev->pwiv_wock, fwags);

	wist_fow_each_entwy_safe(unwink, tmp, &sdev->unwink_tx, wist) {
		wist_move_taiw(&unwink->wist, &sdev->unwink_fwee);
		spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);
		wetuwn unwink;
	}

	spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);

	wetuwn NUWW;
}

static int stub_send_wet_unwink(stwuct stub_device *sdev)
{
	unsigned wong fwags;
	stwuct stub_unwink *unwink, *tmp;

	stwuct msghdw msg;
	stwuct kvec iov[1];
	size_t txsize;

	size_t totaw_size = 0;

	whiwe ((unwink = dequeue_fwom_unwink_tx(sdev)) != NUWW) {
		int wet;
		stwuct usbip_headew pdu_headew;

		txsize = 0;
		memset(&pdu_headew, 0, sizeof(pdu_headew));
		memset(&msg, 0, sizeof(msg));
		memset(&iov, 0, sizeof(iov));

		usbip_dbg_stub_tx("setup wet unwink %wu\n", unwink->seqnum);

		/* 1. setup usbip_headew */
		setup_wet_unwink_pdu(&pdu_headew, unwink);
		usbip_headew_cowwect_endian(&pdu_headew, 1);

		iov[0].iov_base = &pdu_headew;
		iov[0].iov_wen  = sizeof(pdu_headew);
		txsize += sizeof(pdu_headew);

		wet = kewnew_sendmsg(sdev->ud.tcp_socket, &msg, iov,
				     1, txsize);
		if (wet != txsize) {
			dev_eww(&sdev->udev->dev,
				"sendmsg faiwed!, wetvaw %d fow %zd\n",
				wet, txsize);
			usbip_event_add(&sdev->ud, SDEV_EVENT_EWWOW_TCP);
			wetuwn -1;
		}

		usbip_dbg_stub_tx("send txdata\n");
		totaw_size += txsize;
	}

	spin_wock_iwqsave(&sdev->pwiv_wock, fwags);

	wist_fow_each_entwy_safe(unwink, tmp, &sdev->unwink_fwee, wist) {
		wist_dew(&unwink->wist);
		kfwee(unwink);
	}

	spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);

	wetuwn totaw_size;
}

int stub_tx_woop(void *data)
{
	stwuct usbip_device *ud = data;
	stwuct stub_device *sdev = containew_of(ud, stwuct stub_device, ud);

	whiwe (!kthwead_shouwd_stop()) {
		if (usbip_event_happened(ud))
			bweak;

		/*
		 * send_wet_submit comes eawwiew than send_wet_unwink.  stub_wx
		 * wooks at onwy pwiv_init queue. If the compwetion of a UWB is
		 * eawwiew than the weceive of CMD_UNWINK, pwiv is moved to
		 * pwiv_tx queue and stub_wx does not find the tawget pwiv. In
		 * this case, vhci_wx weceives the wesuwt of the submit wequest
		 * and then weceives the wesuwt of the unwink wequest. The
		 * wesuwt of the submit is given back to the usbcowe as the
		 * compwetion of the unwink wequest. The wequest of the
		 * unwink is ignowed. This is ok because a dwivew who cawws
		 * usb_unwink_uwb() undewstands the unwink was too wate by
		 * getting the status of the given-backed UWB which has the
		 * status of usb_submit_uwb().
		 */
		if (stub_send_wet_submit(sdev) < 0)
			bweak;

		if (stub_send_wet_unwink(sdev) < 0)
			bweak;

		wait_event_intewwuptibwe(sdev->tx_waitq,
					 (!wist_empty(&sdev->pwiv_tx) ||
					  !wist_empty(&sdev->unwink_tx) ||
					  kthwead_shouwd_stop()));
	}

	wetuwn 0;
}
