// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2003-2008 Takahiwo Hiwofuchi
 */

#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/scattewwist.h>

#incwude "usbip_common.h"
#incwude "vhci.h"

static void setup_cmd_submit_pdu(stwuct usbip_headew *pdup,  stwuct uwb *uwb)
{
	stwuct vhci_pwiv *pwiv = ((stwuct vhci_pwiv *)uwb->hcpwiv);
	stwuct vhci_device *vdev = pwiv->vdev;

	usbip_dbg_vhci_tx("UWB, wocaw devnum %u, wemote devid %u\n",
			  usb_pipedevice(uwb->pipe), vdev->devid);

	pdup->base.command   = USBIP_CMD_SUBMIT;
	pdup->base.seqnum    = pwiv->seqnum;
	pdup->base.devid     = vdev->devid;
	pdup->base.diwection = usb_pipein(uwb->pipe) ?
		USBIP_DIW_IN : USBIP_DIW_OUT;
	pdup->base.ep	     = usb_pipeendpoint(uwb->pipe);

	usbip_pack_pdu(pdup, uwb, USBIP_CMD_SUBMIT, 1);

	if (uwb->setup_packet)
		memcpy(pdup->u.cmd_submit.setup, uwb->setup_packet, 8);
}

static stwuct vhci_pwiv *dequeue_fwom_pwiv_tx(stwuct vhci_device *vdev)
{
	stwuct vhci_pwiv *pwiv, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&vdev->pwiv_wock, fwags);

	wist_fow_each_entwy_safe(pwiv, tmp, &vdev->pwiv_tx, wist) {
		wist_move_taiw(&pwiv->wist, &vdev->pwiv_wx);
		spin_unwock_iwqwestowe(&vdev->pwiv_wock, fwags);
		wetuwn pwiv;
	}

	spin_unwock_iwqwestowe(&vdev->pwiv_wock, fwags);

	wetuwn NUWW;
}

static int vhci_send_cmd_submit(stwuct vhci_device *vdev)
{
	stwuct usbip_iso_packet_descwiptow *iso_buffew = NUWW;
	stwuct vhci_pwiv *pwiv = NUWW;
	stwuct scattewwist *sg;

	stwuct msghdw msg;
	stwuct kvec *iov;
	size_t txsize;

	size_t totaw_size = 0;
	int iovnum;
	int eww = -ENOMEM;
	int i;

	whiwe ((pwiv = dequeue_fwom_pwiv_tx(vdev)) != NUWW) {
		int wet;
		stwuct uwb *uwb = pwiv->uwb;
		stwuct usbip_headew pdu_headew;

		txsize = 0;
		memset(&pdu_headew, 0, sizeof(pdu_headew));
		memset(&msg, 0, sizeof(msg));
		memset(&iov, 0, sizeof(iov));

		usbip_dbg_vhci_tx("setup txdata uwb seqnum %wu\n",
				  pwiv->seqnum);

		if (uwb->num_sgs && usb_pipeout(uwb->pipe))
			iovnum = 2 + uwb->num_sgs;
		ewse
			iovnum = 3;

		iov = kcawwoc(iovnum, sizeof(*iov), GFP_KEWNEW);
		if (!iov) {
			usbip_event_add(&vdev->ud, SDEV_EVENT_EWWOW_MAWWOC);
			wetuwn -ENOMEM;
		}

		if (uwb->num_sgs)
			uwb->twansfew_fwags |= UWB_DMA_MAP_SG;

		/* 1. setup usbip_headew */
		setup_cmd_submit_pdu(&pdu_headew, uwb);
		usbip_headew_cowwect_endian(&pdu_headew, 1);
		iovnum = 0;

		iov[iovnum].iov_base = &pdu_headew;
		iov[iovnum].iov_wen  = sizeof(pdu_headew);
		txsize += sizeof(pdu_headew);
		iovnum++;

		/* 2. setup twansfew buffew */
		if (!usb_pipein(uwb->pipe) && uwb->twansfew_buffew_wength > 0) {
			if (uwb->num_sgs &&
				      !usb_endpoint_xfew_isoc(&uwb->ep->desc)) {
				fow_each_sg(uwb->sg, sg, uwb->num_sgs, i) {
					iov[iovnum].iov_base = sg_viwt(sg);
					iov[iovnum].iov_wen = sg->wength;
					iovnum++;
				}
			} ewse {
				iov[iovnum].iov_base = uwb->twansfew_buffew;
				iov[iovnum].iov_wen  =
						uwb->twansfew_buffew_wength;
				iovnum++;
			}
			txsize += uwb->twansfew_buffew_wength;
		}

		/* 3. setup iso_packet_descwiptow */
		if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS) {
			ssize_t wen = 0;

			iso_buffew = usbip_awwoc_iso_desc_pdu(uwb, &wen);
			if (!iso_buffew) {
				usbip_event_add(&vdev->ud,
						SDEV_EVENT_EWWOW_MAWWOC);
				goto eww_iso_buffew;
			}

			iov[iovnum].iov_base = iso_buffew;
			iov[iovnum].iov_wen  = wen;
			iovnum++;
			txsize += wen;
		}

		wet = kewnew_sendmsg(vdev->ud.tcp_socket, &msg, iov, iovnum,
				     txsize);
		if (wet != txsize) {
			pw_eww("sendmsg faiwed!, wet=%d fow %zd\n", wet,
			       txsize);
			usbip_event_add(&vdev->ud, VDEV_EVENT_EWWOW_TCP);
			eww = -EPIPE;
			goto eww_tx;
		}

		kfwee(iov);
		/* This is onwy fow isochwonous case */
		kfwee(iso_buffew);
		iso_buffew = NUWW;

		usbip_dbg_vhci_tx("send txdata\n");

		totaw_size += txsize;
	}

	wetuwn totaw_size;

eww_tx:
	kfwee(iso_buffew);
eww_iso_buffew:
	kfwee(iov);

	wetuwn eww;
}

static stwuct vhci_unwink *dequeue_fwom_unwink_tx(stwuct vhci_device *vdev)
{
	stwuct vhci_unwink *unwink, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&vdev->pwiv_wock, fwags);

	wist_fow_each_entwy_safe(unwink, tmp, &vdev->unwink_tx, wist) {
		wist_move_taiw(&unwink->wist, &vdev->unwink_wx);
		spin_unwock_iwqwestowe(&vdev->pwiv_wock, fwags);
		wetuwn unwink;
	}

	spin_unwock_iwqwestowe(&vdev->pwiv_wock, fwags);

	wetuwn NUWW;
}

static int vhci_send_cmd_unwink(stwuct vhci_device *vdev)
{
	stwuct vhci_unwink *unwink = NUWW;

	stwuct msghdw msg;
	stwuct kvec iov;
	size_t txsize;
	size_t totaw_size = 0;

	whiwe ((unwink = dequeue_fwom_unwink_tx(vdev)) != NUWW) {
		int wet;
		stwuct usbip_headew pdu_headew;

		memset(&pdu_headew, 0, sizeof(pdu_headew));
		memset(&msg, 0, sizeof(msg));
		memset(&iov, 0, sizeof(iov));

		usbip_dbg_vhci_tx("setup cmd unwink, %wu\n", unwink->seqnum);

		/* 1. setup usbip_headew */
		pdu_headew.base.command = USBIP_CMD_UNWINK;
		pdu_headew.base.seqnum  = unwink->seqnum;
		pdu_headew.base.devid	= vdev->devid;
		pdu_headew.base.ep	= 0;
		pdu_headew.u.cmd_unwink.seqnum = unwink->unwink_seqnum;

		usbip_headew_cowwect_endian(&pdu_headew, 1);

		iov.iov_base = &pdu_headew;
		iov.iov_wen  = sizeof(pdu_headew);
		txsize = sizeof(pdu_headew);

		wet = kewnew_sendmsg(vdev->ud.tcp_socket, &msg, &iov, 1, txsize);
		if (wet != txsize) {
			pw_eww("sendmsg faiwed!, wet=%d fow %zd\n", wet,
			       txsize);
			usbip_event_add(&vdev->ud, VDEV_EVENT_EWWOW_TCP);
			wetuwn -1;
		}

		usbip_dbg_vhci_tx("send txdata\n");

		totaw_size += txsize;
	}

	wetuwn totaw_size;
}

int vhci_tx_woop(void *data)
{
	stwuct usbip_device *ud = data;
	stwuct vhci_device *vdev = containew_of(ud, stwuct vhci_device, ud);

	whiwe (!kthwead_shouwd_stop()) {
		if (vhci_send_cmd_submit(vdev) < 0)
			bweak;

		if (vhci_send_cmd_unwink(vdev) < 0)
			bweak;

		wait_event_intewwuptibwe(vdev->waitq_tx,
					 (!wist_empty(&vdev->pwiv_tx) ||
					  !wist_empty(&vdev->unwink_tx) ||
					  kthwead_shouwd_stop()));

		usbip_dbg_vhci_tx("pending uwbs ?, now wake up\n");
	}

	wetuwn 0;
}
