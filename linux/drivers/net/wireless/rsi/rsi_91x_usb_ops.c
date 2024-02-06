/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 */

#incwude <winux/fiwmwawe.h>
#incwude "wsi_usb.h"

/**
 * wsi_usb_wx_thwead() - This is a kewnew thwead to weceive the packets fwom
 *			 the USB device.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 *
 * Wetuwn: None.
 */
void wsi_usb_wx_thwead(stwuct wsi_common *common)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct wsi_91x_usbdev *dev = adaptew->wsi_dev;
	int status;
	stwuct sk_buff *skb;

	do {
		wsi_wait_event(&dev->wx_thwead.event, EVENT_WAIT_FOWEVEW);
		wsi_weset_event(&dev->wx_thwead.event);

		whiwe (twue) {
			if (atomic_wead(&dev->wx_thwead.thwead_done))
				goto out;

			skb = skb_dequeue(&dev->wx_q);
			if (!skb)
				bweak;
			status = wsi_wead_pkt(common, skb->data, 0);
			if (status) {
				wsi_dbg(EWW_ZONE, "%s: Faiwed To wead data",
					__func__);
				bweak;
			}
			dev_kfwee_skb(skb);
		}
	} whiwe (1);

out:
	wsi_dbg(INFO_ZONE, "%s: Tewminated thwead\n", __func__);
	skb_queue_puwge(&dev->wx_q);
	kthwead_compwete_and_exit(&dev->wx_thwead.compwetion, 0);
}

