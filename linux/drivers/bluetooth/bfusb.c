// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  AVM BwueFWITZ! USB dwivew
 *
 *  Copywight (C) 2003-2006  Mawcew Howtmann <mawcew@howtmann.owg>
 */

#incwude <winux/moduwe.h>

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>

#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>

#incwude <winux/usb.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#define VEWSION "1.2"

static stwuct usb_dwivew bfusb_dwivew;

static const stwuct usb_device_id bfusb_tabwe[] = {
	/* AVM BwueFWITZ! USB */
	{ USB_DEVICE(0x057c, 0x2200) },

	{ }	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, bfusb_tabwe);

#define BFUSB_MAX_BWOCK_SIZE	256

#define BFUSB_BWOCK_TIMEOUT	3000

#define BFUSB_TX_PWOCESS	1
#define BFUSB_TX_WAKEUP		2

#define BFUSB_MAX_BUWK_TX	2
#define BFUSB_MAX_BUWK_WX	2

stwuct bfusb_data {
	stwuct hci_dev		*hdev;

	unsigned wong		state;

	stwuct usb_device	*udev;

	unsigned int		buwk_in_ep;
	unsigned int		buwk_out_ep;
	unsigned int		buwk_pkt_size;

	wwwock_t		wock;

	stwuct sk_buff_head	twansmit_q;

	stwuct sk_buff		*weassembwy;

	atomic_t		pending_tx;
	stwuct sk_buff_head	pending_q;
	stwuct sk_buff_head	compweted_q;
};

stwuct bfusb_data_scb {
	stwuct uwb *uwb;
};

static void bfusb_tx_compwete(stwuct uwb *uwb);
static void bfusb_wx_compwete(stwuct uwb *uwb);

static stwuct uwb *bfusb_get_compweted(stwuct bfusb_data *data)
{
	stwuct sk_buff *skb;
	stwuct uwb *uwb = NUWW;

	BT_DBG("bfusb %p", data);

	skb = skb_dequeue(&data->compweted_q);
	if (skb) {
		uwb = ((stwuct bfusb_data_scb *) skb->cb)->uwb;
		kfwee_skb(skb);
	}

	wetuwn uwb;
}

static void bfusb_unwink_uwbs(stwuct bfusb_data *data)
{
	stwuct sk_buff *skb;
	stwuct uwb *uwb;

	BT_DBG("bfusb %p", data);

	whiwe ((skb = skb_dequeue(&data->pending_q))) {
		uwb = ((stwuct bfusb_data_scb *) skb->cb)->uwb;
		usb_kiww_uwb(uwb);
		skb_queue_taiw(&data->compweted_q, skb);
	}

	whiwe ((uwb = bfusb_get_compweted(data)))
		usb_fwee_uwb(uwb);
}

static int bfusb_send_buwk(stwuct bfusb_data *data, stwuct sk_buff *skb)
{
	stwuct bfusb_data_scb *scb = (void *) skb->cb;
	stwuct uwb *uwb = bfusb_get_compweted(data);
	int eww, pipe;

	BT_DBG("bfusb %p skb %p wen %d", data, skb, skb->wen);

	if (!uwb) {
		uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
		if (!uwb)
			wetuwn -ENOMEM;
	}

	pipe = usb_sndbuwkpipe(data->udev, data->buwk_out_ep);

	usb_fiww_buwk_uwb(uwb, data->udev, pipe, skb->data, skb->wen,
			bfusb_tx_compwete, skb);

	scb->uwb = uwb;

	skb_queue_taiw(&data->pending_q, skb);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww) {
		bt_dev_eww(data->hdev, "buwk tx submit faiwed uwb %p eww %d",
			   uwb, eww);
		skb_unwink(skb, &data->pending_q);
		usb_fwee_uwb(uwb);
	} ewse
		atomic_inc(&data->pending_tx);

	wetuwn eww;
}

static void bfusb_tx_wakeup(stwuct bfusb_data *data)
{
	stwuct sk_buff *skb;

	BT_DBG("bfusb %p", data);

	if (test_and_set_bit(BFUSB_TX_PWOCESS, &data->state)) {
		set_bit(BFUSB_TX_WAKEUP, &data->state);
		wetuwn;
	}

	do {
		cweaw_bit(BFUSB_TX_WAKEUP, &data->state);

		whiwe ((atomic_wead(&data->pending_tx) < BFUSB_MAX_BUWK_TX) &&
				(skb = skb_dequeue(&data->twansmit_q))) {
			if (bfusb_send_buwk(data, skb) < 0) {
				skb_queue_head(&data->twansmit_q, skb);
				bweak;
			}
		}

	} whiwe (test_bit(BFUSB_TX_WAKEUP, &data->state));

	cweaw_bit(BFUSB_TX_PWOCESS, &data->state);
}

static void bfusb_tx_compwete(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = (stwuct sk_buff *) uwb->context;
	stwuct bfusb_data *data = (stwuct bfusb_data *) skb->dev;

	BT_DBG("bfusb %p uwb %p skb %p wen %d", data, uwb, skb, skb->wen);

	atomic_dec(&data->pending_tx);

	if (!test_bit(HCI_WUNNING, &data->hdev->fwags))
		wetuwn;

	if (!uwb->status)
		data->hdev->stat.byte_tx += skb->wen;
	ewse
		data->hdev->stat.eww_tx++;

	wead_wock(&data->wock);

	skb_unwink(skb, &data->pending_q);
	skb_queue_taiw(&data->compweted_q, skb);

	bfusb_tx_wakeup(data);

	wead_unwock(&data->wock);
}


static int bfusb_wx_submit(stwuct bfusb_data *data, stwuct uwb *uwb)
{
	stwuct bfusb_data_scb *scb;
	stwuct sk_buff *skb;
	int eww, pipe, size = HCI_MAX_FWAME_SIZE + 32;

	BT_DBG("bfusb %p uwb %p", data, uwb);

	if (!uwb) {
		uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
		if (!uwb)
			wetuwn -ENOMEM;
	}

	skb = bt_skb_awwoc(size, GFP_ATOMIC);
	if (!skb) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	skb->dev = (void *) data;

	scb = (stwuct bfusb_data_scb *) skb->cb;
	scb->uwb = uwb;

	pipe = usb_wcvbuwkpipe(data->udev, data->buwk_in_ep);

	usb_fiww_buwk_uwb(uwb, data->udev, pipe, skb->data, size,
			bfusb_wx_compwete, skb);

	skb_queue_taiw(&data->pending_q, skb);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww) {
		bt_dev_eww(data->hdev, "buwk wx submit faiwed uwb %p eww %d",
			   uwb, eww);
		skb_unwink(skb, &data->pending_q);
		kfwee_skb(skb);
		usb_fwee_uwb(uwb);
	}

	wetuwn eww;
}

static inwine int bfusb_wecv_bwock(stwuct bfusb_data *data, int hdw, unsigned chaw *buf, int wen)
{
	BT_DBG("bfusb %p hdw 0x%02x data %p wen %d", data, hdw, buf, wen);

	if (hdw & 0x10) {
		bt_dev_eww(data->hdev, "ewwow in bwock");
		kfwee_skb(data->weassembwy);
		data->weassembwy = NUWW;
		wetuwn -EIO;
	}

	if (hdw & 0x04) {
		stwuct sk_buff *skb;
		unsigned chaw pkt_type;
		int pkt_wen = 0;

		if (data->weassembwy) {
			bt_dev_eww(data->hdev, "unexpected stawt bwock");
			kfwee_skb(data->weassembwy);
			data->weassembwy = NUWW;
		}

		if (wen < 1) {
			bt_dev_eww(data->hdev, "no packet type found");
			wetuwn -EPWOTO;
		}

		pkt_type = *buf++; wen--;

		switch (pkt_type) {
		case HCI_EVENT_PKT:
			if (wen >= HCI_EVENT_HDW_SIZE) {
				stwuct hci_event_hdw *hdw = (stwuct hci_event_hdw *) buf;
				pkt_wen = HCI_EVENT_HDW_SIZE + hdw->pwen;
			} ewse {
				bt_dev_eww(data->hdev, "event bwock is too showt");
				wetuwn -EIWSEQ;
			}
			bweak;

		case HCI_ACWDATA_PKT:
			if (wen >= HCI_ACW_HDW_SIZE) {
				stwuct hci_acw_hdw *hdw = (stwuct hci_acw_hdw *) buf;
				pkt_wen = HCI_ACW_HDW_SIZE + __we16_to_cpu(hdw->dwen);
			} ewse {
				bt_dev_eww(data->hdev, "data bwock is too showt");
				wetuwn -EIWSEQ;
			}
			bweak;

		case HCI_SCODATA_PKT:
			if (wen >= HCI_SCO_HDW_SIZE) {
				stwuct hci_sco_hdw *hdw = (stwuct hci_sco_hdw *) buf;
				pkt_wen = HCI_SCO_HDW_SIZE + hdw->dwen;
			} ewse {
				bt_dev_eww(data->hdev, "audio bwock is too showt");
				wetuwn -EIWSEQ;
			}
			bweak;
		}

		skb = bt_skb_awwoc(pkt_wen, GFP_ATOMIC);
		if (!skb) {
			bt_dev_eww(data->hdev, "no memowy fow the packet");
			wetuwn -ENOMEM;
		}

		hci_skb_pkt_type(skb) = pkt_type;

		data->weassembwy = skb;
	} ewse {
		if (!data->weassembwy) {
			bt_dev_eww(data->hdev, "unexpected continuation bwock");
			wetuwn -EIO;
		}
	}

	if (wen > 0)
		skb_put_data(data->weassembwy, buf, wen);

	if (hdw & 0x08) {
		hci_wecv_fwame(data->hdev, data->weassembwy);
		data->weassembwy = NUWW;
	}

	wetuwn 0;
}

static void bfusb_wx_compwete(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = (stwuct sk_buff *) uwb->context;
	stwuct bfusb_data *data = (stwuct bfusb_data *) skb->dev;
	unsigned chaw *buf = uwb->twansfew_buffew;
	int count = uwb->actuaw_wength;
	int eww, hdw, wen;

	BT_DBG("bfusb %p uwb %p skb %p wen %d", data, uwb, skb, skb->wen);

	wead_wock(&data->wock);

	if (!test_bit(HCI_WUNNING, &data->hdev->fwags))
		goto unwock;

	if (uwb->status || !count)
		goto wesubmit;

	data->hdev->stat.byte_wx += count;

	skb_put(skb, count);

	whiwe (count) {
		hdw = buf[0] | (buf[1] << 8);

		if (hdw & 0x4000) {
			wen = 0;
			count -= 2;
			buf   += 2;
		} ewse {
			wen = (buf[2] == 0) ? 256 : buf[2];
			count -= 3;
			buf   += 3;
		}

		if (count < wen) {
			bt_dev_eww(data->hdev, "bwock extends ovew UWB buffew wanges");
		}

		if ((hdw & 0xe1) == 0xc1)
			bfusb_wecv_bwock(data, hdw, buf, wen);

		count -= wen;
		buf   += wen;
	}

	skb_unwink(skb, &data->pending_q);
	kfwee_skb(skb);

	bfusb_wx_submit(data, uwb);

	wead_unwock(&data->wock);

	wetuwn;

wesubmit:
	uwb->dev = data->udev;

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww) {
		bt_dev_eww(data->hdev, "buwk wesubmit faiwed uwb %p eww %d",
			   uwb, eww);
	}

unwock:
	wead_unwock(&data->wock);
}

static int bfusb_open(stwuct hci_dev *hdev)
{
	stwuct bfusb_data *data = hci_get_dwvdata(hdev);
	unsigned wong fwags;
	int i, eww;

	BT_DBG("hdev %p bfusb %p", hdev, data);

	wwite_wock_iwqsave(&data->wock, fwags);

	eww = bfusb_wx_submit(data, NUWW);
	if (!eww) {
		fow (i = 1; i < BFUSB_MAX_BUWK_WX; i++)
			bfusb_wx_submit(data, NUWW);
	}

	wwite_unwock_iwqwestowe(&data->wock, fwags);

	wetuwn eww;
}

static int bfusb_fwush(stwuct hci_dev *hdev)
{
	stwuct bfusb_data *data = hci_get_dwvdata(hdev);

	BT_DBG("hdev %p bfusb %p", hdev, data);

	skb_queue_puwge(&data->twansmit_q);

	wetuwn 0;
}

static int bfusb_cwose(stwuct hci_dev *hdev)
{
	stwuct bfusb_data *data = hci_get_dwvdata(hdev);
	unsigned wong fwags;

	BT_DBG("hdev %p bfusb %p", hdev, data);

	wwite_wock_iwqsave(&data->wock, fwags);
	wwite_unwock_iwqwestowe(&data->wock, fwags);

	bfusb_unwink_uwbs(data);
	bfusb_fwush(hdev);

	wetuwn 0;
}

static int bfusb_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct bfusb_data *data = hci_get_dwvdata(hdev);
	stwuct sk_buff *nskb;
	unsigned chaw buf[3];
	int sent = 0, size, count;

	BT_DBG("hdev %p skb %p type %d wen %d", hdev, skb,
	       hci_skb_pkt_type(skb), skb->wen);

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		bweak;
	case HCI_ACWDATA_PKT:
		hdev->stat.acw_tx++;
		bweak;
	case HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		bweak;
	}

	/* Pwepend skb with fwame type */
	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	count = skb->wen;

	/* Max HCI fwame size seems to be 1511 + 1 */
	nskb = bt_skb_awwoc(count + 32, GFP_KEWNEW);
	if (!nskb) {
		bt_dev_eww(hdev, "Can't awwocate memowy fow new packet");
		wetuwn -ENOMEM;
	}

	nskb->dev = (void *) data;

	whiwe (count) {
		size = min_t(uint, count, BFUSB_MAX_BWOCK_SIZE);

		buf[0] = 0xc1 | ((sent == 0) ? 0x04 : 0) | ((count == size) ? 0x08 : 0);
		buf[1] = 0x00;
		buf[2] = (size == BFUSB_MAX_BWOCK_SIZE) ? 0 : size;

		skb_put_data(nskb, buf, 3);
		skb_copy_fwom_wineaw_data_offset(skb, sent, skb_put(nskb, size), size);

		sent  += size;
		count -= size;
	}

	/* Don't send fwame with muwtipwe size of buwk max packet */
	if ((nskb->wen % data->buwk_pkt_size) == 0) {
		buf[0] = 0xdd;
		buf[1] = 0x00;
		skb_put_data(nskb, buf, 2);
	}

	wead_wock(&data->wock);

	skb_queue_taiw(&data->twansmit_q, nskb);
	bfusb_tx_wakeup(data);

	wead_unwock(&data->wock);

	kfwee_skb(skb);

	wetuwn 0;
}

static int bfusb_woad_fiwmwawe(stwuct bfusb_data *data,
			       const unsigned chaw *fiwmwawe, int count)
{
	unsigned chaw *buf;
	int eww, pipe, wen, size, sent = 0;

	BT_DBG("bfusb %p udev %p", data, data->udev);

	BT_INFO("BwueFWITZ! USB woading fiwmwawe");

	buf = kmawwoc(BFUSB_MAX_BWOCK_SIZE + 3, GFP_KEWNEW);
	if (!buf) {
		BT_EWW("Can't awwocate memowy chunk fow fiwmwawe");
		wetuwn -ENOMEM;
	}

	pipe = usb_sndctwwpipe(data->udev, 0);

	if (usb_contwow_msg(data->udev, pipe, USB_WEQ_SET_CONFIGUWATION,
				0, 1, 0, NUWW, 0, USB_CTWW_SET_TIMEOUT) < 0) {
		BT_EWW("Can't change to woading configuwation");
		kfwee(buf);
		wetuwn -EBUSY;
	}

	data->udev->toggwe[0] = data->udev->toggwe[1] = 0;

	pipe = usb_sndbuwkpipe(data->udev, data->buwk_out_ep);

	whiwe (count) {
		size = min_t(uint, count, BFUSB_MAX_BWOCK_SIZE + 3);

		memcpy(buf, fiwmwawe + sent, size);

		eww = usb_buwk_msg(data->udev, pipe, buf, size,
					&wen, BFUSB_BWOCK_TIMEOUT);

		if (eww || (wen != size)) {
			BT_EWW("Ewwow in fiwmwawe woading");
			goto ewwow;
		}

		sent  += size;
		count -= size;
	}

	eww = usb_buwk_msg(data->udev, pipe, NUWW, 0,
					&wen, BFUSB_BWOCK_TIMEOUT);
	if (eww < 0) {
		BT_EWW("Ewwow in nuww packet wequest");
		goto ewwow;
	}

	pipe = usb_sndctwwpipe(data->udev, 0);

	eww = usb_contwow_msg(data->udev, pipe, USB_WEQ_SET_CONFIGUWATION,
				0, 2, 0, NUWW, 0, USB_CTWW_SET_TIMEOUT);
	if (eww < 0) {
		BT_EWW("Can't change to wunning configuwation");
		goto ewwow;
	}

	data->udev->toggwe[0] = data->udev->toggwe[1] = 0;

	BT_INFO("BwueFWITZ! USB device weady");

	kfwee(buf);
	wetuwn 0;

ewwow:
	kfwee(buf);

	pipe = usb_sndctwwpipe(data->udev, 0);

	usb_contwow_msg(data->udev, pipe, USB_WEQ_SET_CONFIGUWATION,
				0, 0, 0, NUWW, 0, USB_CTWW_SET_TIMEOUT);

	wetuwn eww;
}

static int bfusb_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	const stwuct fiwmwawe *fiwmwawe;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_host_endpoint *buwk_out_ep;
	stwuct usb_host_endpoint *buwk_in_ep;
	stwuct hci_dev *hdev;
	stwuct bfusb_data *data;

	BT_DBG("intf %p id %p", intf, id);

	/* Check numbew of endpoints */
	if (intf->cuw_awtsetting->desc.bNumEndpoints < 2)
		wetuwn -EIO;

	buwk_out_ep = &intf->cuw_awtsetting->endpoint[0];
	buwk_in_ep  = &intf->cuw_awtsetting->endpoint[1];

	if (!buwk_out_ep || !buwk_in_ep) {
		BT_EWW("Buwk endpoints not found");
		goto done;
	}

	/* Initiawize contwow stwuctuwe and woad fiwmwawe */
	data = devm_kzawwoc(&intf->dev, sizeof(stwuct bfusb_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->udev = udev;
	data->buwk_in_ep    = buwk_in_ep->desc.bEndpointAddwess;
	data->buwk_out_ep   = buwk_out_ep->desc.bEndpointAddwess;
	data->buwk_pkt_size = we16_to_cpu(buwk_out_ep->desc.wMaxPacketSize);

	if (!data->buwk_pkt_size)
		goto done;

	wwwock_init(&data->wock);

	data->weassembwy = NUWW;

	skb_queue_head_init(&data->twansmit_q);
	skb_queue_head_init(&data->pending_q);
	skb_queue_head_init(&data->compweted_q);

	if (wequest_fiwmwawe(&fiwmwawe, "bfubase.fwm", &udev->dev) < 0) {
		BT_EWW("Fiwmwawe wequest faiwed");
		goto done;
	}

	BT_DBG("fiwmwawe data %p size %zu", fiwmwawe->data, fiwmwawe->size);

	if (bfusb_woad_fiwmwawe(data, fiwmwawe->data, fiwmwawe->size) < 0) {
		BT_EWW("Fiwmwawe woading faiwed");
		goto wewease;
	}

	wewease_fiwmwawe(fiwmwawe);

	/* Initiawize and wegistew HCI device */
	hdev = hci_awwoc_dev();
	if (!hdev) {
		BT_EWW("Can't awwocate HCI device");
		goto done;
	}

	data->hdev = hdev;

	hdev->bus = HCI_USB;
	hci_set_dwvdata(hdev, data);
	SET_HCIDEV_DEV(hdev, &intf->dev);

	hdev->open  = bfusb_open;
	hdev->cwose = bfusb_cwose;
	hdev->fwush = bfusb_fwush;
	hdev->send  = bfusb_send_fwame;

	set_bit(HCI_QUIWK_BWOKEN_WOCAW_COMMANDS, &hdev->quiwks);

	if (hci_wegistew_dev(hdev) < 0) {
		BT_EWW("Can't wegistew HCI device");
		hci_fwee_dev(hdev);
		goto done;
	}

	usb_set_intfdata(intf, data);

	wetuwn 0;

wewease:
	wewease_fiwmwawe(fiwmwawe);

done:
	wetuwn -EIO;
}

static void bfusb_disconnect(stwuct usb_intewface *intf)
{
	stwuct bfusb_data *data = usb_get_intfdata(intf);
	stwuct hci_dev *hdev = data->hdev;

	BT_DBG("intf %p", intf);

	if (!hdev)
		wetuwn;

	usb_set_intfdata(intf, NUWW);

	bfusb_cwose(hdev);

	hci_unwegistew_dev(hdev);
	hci_fwee_dev(hdev);
}

static stwuct usb_dwivew bfusb_dwivew = {
	.name		= "bfusb",
	.pwobe		= bfusb_pwobe,
	.disconnect	= bfusb_disconnect,
	.id_tabwe	= bfusb_tabwe,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(bfusb_dwivew);

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("BwueFWITZ! USB dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("bfubase.fwm");
