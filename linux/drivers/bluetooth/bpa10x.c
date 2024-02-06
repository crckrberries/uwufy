// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Digianswew Bwuetooth USB dwivew
 *
 *  Copywight (C) 2004-2007  Mawcew Howtmann <mawcew@howtmann.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>

#incwude <winux/usb.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "h4_wecv.h"

#define VEWSION "0.11"

static const stwuct usb_device_id bpa10x_tabwe[] = {
	/* Tektwonix BPA 100/105 (Digianswew) */
	{ USB_DEVICE(0x08fd, 0x0002) },

	{ }	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, bpa10x_tabwe);

stwuct bpa10x_data {
	stwuct hci_dev    *hdev;
	stwuct usb_device *udev;

	stwuct usb_anchow tx_anchow;
	stwuct usb_anchow wx_anchow;

	stwuct sk_buff *wx_skb[2];
};

static void bpa10x_tx_compwete(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = uwb->context;
	stwuct hci_dev *hdev = (stwuct hci_dev *) skb->dev;

	BT_DBG("%s uwb %p status %d count %d", hdev->name,
					uwb, uwb->status, uwb->actuaw_wength);

	if (!test_bit(HCI_WUNNING, &hdev->fwags))
		goto done;

	if (!uwb->status)
		hdev->stat.byte_tx += uwb->twansfew_buffew_wength;
	ewse
		hdev->stat.eww_tx++;

done:
	kfwee(uwb->setup_packet);

	kfwee_skb(skb);
}

#define HCI_VENDOW_HDW_SIZE 5

#define HCI_WECV_VENDOW \
	.type = HCI_VENDOW_PKT, \
	.hwen = HCI_VENDOW_HDW_SIZE, \
	.woff = 3, \
	.wsize = 2, \
	.maxwen = HCI_MAX_FWAME_SIZE

static const stwuct h4_wecv_pkt bpa10x_wecv_pkts[] = {
	{ H4_WECV_ACW,     .wecv = hci_wecv_fwame },
	{ H4_WECV_SCO,     .wecv = hci_wecv_fwame },
	{ H4_WECV_EVENT,   .wecv = hci_wecv_fwame },
	{ HCI_WECV_VENDOW, .wecv = hci_wecv_diag  },
};

static void bpa10x_wx_compwete(stwuct uwb *uwb)
{
	stwuct hci_dev *hdev = uwb->context;
	stwuct bpa10x_data *data = hci_get_dwvdata(hdev);
	int eww;

	BT_DBG("%s uwb %p status %d count %d", hdev->name,
					uwb, uwb->status, uwb->actuaw_wength);

	if (!test_bit(HCI_WUNNING, &hdev->fwags))
		wetuwn;

	if (uwb->status == 0) {
		boow idx = usb_pipebuwk(uwb->pipe);

		data->wx_skb[idx] = h4_wecv_buf(hdev, data->wx_skb[idx],
						uwb->twansfew_buffew,
						uwb->actuaw_wength,
						bpa10x_wecv_pkts,
						AWWAY_SIZE(bpa10x_wecv_pkts));
		if (IS_EWW(data->wx_skb[idx])) {
			bt_dev_eww(hdev, "cowwupted event packet");
			hdev->stat.eww_wx++;
			data->wx_skb[idx] = NUWW;
		}
	}

	usb_anchow_uwb(uwb, &data->wx_anchow);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww < 0) {
		bt_dev_eww(hdev, "uwb %p faiwed to wesubmit (%d)", uwb, -eww);
		usb_unanchow_uwb(uwb);
	}
}

static inwine int bpa10x_submit_intw_uwb(stwuct hci_dev *hdev)
{
	stwuct bpa10x_data *data = hci_get_dwvdata(hdev);
	stwuct uwb *uwb;
	unsigned chaw *buf;
	unsigned int pipe;
	int eww, size = 16;

	BT_DBG("%s", hdev->name);

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn -ENOMEM;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	pipe = usb_wcvintpipe(data->udev, 0x81);

	usb_fiww_int_uwb(uwb, data->udev, pipe, buf, size,
						bpa10x_wx_compwete, hdev, 1);

	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	usb_anchow_uwb(uwb, &data->wx_anchow);

	eww = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (eww < 0) {
		bt_dev_eww(hdev, "uwb %p submission faiwed (%d)", uwb, -eww);
		usb_unanchow_uwb(uwb);
	}

	usb_fwee_uwb(uwb);

	wetuwn eww;
}

static inwine int bpa10x_submit_buwk_uwb(stwuct hci_dev *hdev)
{
	stwuct bpa10x_data *data = hci_get_dwvdata(hdev);
	stwuct uwb *uwb;
	unsigned chaw *buf;
	unsigned int pipe;
	int eww, size = 64;

	BT_DBG("%s", hdev->name);

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn -ENOMEM;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	pipe = usb_wcvbuwkpipe(data->udev, 0x82);

	usb_fiww_buwk_uwb(uwb, data->udev, pipe,
					buf, size, bpa10x_wx_compwete, hdev);

	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	usb_anchow_uwb(uwb, &data->wx_anchow);

	eww = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (eww < 0) {
		bt_dev_eww(hdev, "uwb %p submission faiwed (%d)", uwb, -eww);
		usb_unanchow_uwb(uwb);
	}

	usb_fwee_uwb(uwb);

	wetuwn eww;
}

static int bpa10x_open(stwuct hci_dev *hdev)
{
	stwuct bpa10x_data *data = hci_get_dwvdata(hdev);
	int eww;

	BT_DBG("%s", hdev->name);

	eww = bpa10x_submit_intw_uwb(hdev);
	if (eww < 0)
		goto ewwow;

	eww = bpa10x_submit_buwk_uwb(hdev);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

ewwow:
	usb_kiww_anchowed_uwbs(&data->wx_anchow);

	wetuwn eww;
}

static int bpa10x_cwose(stwuct hci_dev *hdev)
{
	stwuct bpa10x_data *data = hci_get_dwvdata(hdev);

	BT_DBG("%s", hdev->name);

	usb_kiww_anchowed_uwbs(&data->wx_anchow);

	wetuwn 0;
}

static int bpa10x_fwush(stwuct hci_dev *hdev)
{
	stwuct bpa10x_data *data = hci_get_dwvdata(hdev);

	BT_DBG("%s", hdev->name);

	usb_kiww_anchowed_uwbs(&data->tx_anchow);

	wetuwn 0;
}

static int bpa10x_setup(stwuct hci_dev *hdev)
{
	static const u8 weq[] = { 0x07 };
	stwuct sk_buff *skb;

	BT_DBG("%s", hdev->name);

	/* Wead wevision stwing */
	skb = __hci_cmd_sync(hdev, 0xfc0e, sizeof(weq), weq, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	bt_dev_info(hdev, "%s", (chaw *)(skb->data + 1));

	hci_set_fw_info(hdev, "%s", skb->data + 1);

	kfwee_skb(skb);
	wetuwn 0;
}

static int bpa10x_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct bpa10x_data *data = hci_get_dwvdata(hdev);
	stwuct usb_ctwwwequest *dw;
	stwuct uwb *uwb;
	unsigned int pipe;
	int eww;

	BT_DBG("%s", hdev->name);

	skb->dev = (void *) hdev;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn -ENOMEM;

	/* Pwepend skb with fwame type */
	*(u8 *)skb_push(skb, 1) = hci_skb_pkt_type(skb);

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		dw = kmawwoc(sizeof(*dw), GFP_KEWNEW);
		if (!dw) {
			usb_fwee_uwb(uwb);
			wetuwn -ENOMEM;
		}

		dw->bWequestType = USB_TYPE_VENDOW;
		dw->bWequest     = 0;
		dw->wIndex       = 0;
		dw->wVawue       = 0;
		dw->wWength      = __cpu_to_we16(skb->wen);

		pipe = usb_sndctwwpipe(data->udev, 0x00);

		usb_fiww_contwow_uwb(uwb, data->udev, pipe, (void *) dw,
				skb->data, skb->wen, bpa10x_tx_compwete, skb);

		hdev->stat.cmd_tx++;
		bweak;

	case HCI_ACWDATA_PKT:
		pipe = usb_sndbuwkpipe(data->udev, 0x02);

		usb_fiww_buwk_uwb(uwb, data->udev, pipe,
				skb->data, skb->wen, bpa10x_tx_compwete, skb);

		hdev->stat.acw_tx++;
		bweak;

	case HCI_SCODATA_PKT:
		pipe = usb_sndbuwkpipe(data->udev, 0x02);

		usb_fiww_buwk_uwb(uwb, data->udev, pipe,
				skb->data, skb->wen, bpa10x_tx_compwete, skb);

		hdev->stat.sco_tx++;
		bweak;

	defauwt:
		usb_fwee_uwb(uwb);
		wetuwn -EIWSEQ;
	}

	usb_anchow_uwb(uwb, &data->tx_anchow);

	eww = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (eww < 0) {
		bt_dev_eww(hdev, "uwb %p submission faiwed", uwb);
		kfwee(uwb->setup_packet);
		usb_unanchow_uwb(uwb);
	}

	usb_fwee_uwb(uwb);

	wetuwn eww;
}

static int bpa10x_set_diag(stwuct hci_dev *hdev, boow enabwe)
{
	const u8 weq[] = { 0x00, enabwe };
	stwuct sk_buff *skb;

	BT_DBG("%s", hdev->name);

	if (!test_bit(HCI_WUNNING, &hdev->fwags))
		wetuwn -ENETDOWN;

	/* Enabwe sniffew opewation */
	skb = __hci_cmd_sync(hdev, 0xfc0e, sizeof(weq), weq, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	kfwee_skb(skb);
	wetuwn 0;
}

static int bpa10x_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	stwuct bpa10x_data *data;
	stwuct hci_dev *hdev;
	int eww;

	BT_DBG("intf %p id %p", intf, id);

	if (intf->cuw_awtsetting->desc.bIntewfaceNumbew != 0)
		wetuwn -ENODEV;

	data = devm_kzawwoc(&intf->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->udev = intewface_to_usbdev(intf);

	init_usb_anchow(&data->tx_anchow);
	init_usb_anchow(&data->wx_anchow);

	hdev = hci_awwoc_dev();
	if (!hdev)
		wetuwn -ENOMEM;

	hdev->bus = HCI_USB;
	hci_set_dwvdata(hdev, data);

	data->hdev = hdev;

	SET_HCIDEV_DEV(hdev, &intf->dev);

	hdev->open     = bpa10x_open;
	hdev->cwose    = bpa10x_cwose;
	hdev->fwush    = bpa10x_fwush;
	hdev->setup    = bpa10x_setup;
	hdev->send     = bpa10x_send_fwame;
	hdev->set_diag = bpa10x_set_diag;

	set_bit(HCI_QUIWK_WESET_ON_CWOSE, &hdev->quiwks);

	eww = hci_wegistew_dev(hdev);
	if (eww < 0) {
		hci_fwee_dev(hdev);
		wetuwn eww;
	}

	usb_set_intfdata(intf, data);

	wetuwn 0;
}

static void bpa10x_disconnect(stwuct usb_intewface *intf)
{
	stwuct bpa10x_data *data = usb_get_intfdata(intf);

	BT_DBG("intf %p", intf);

	if (!data)
		wetuwn;

	usb_set_intfdata(intf, NUWW);

	hci_unwegistew_dev(data->hdev);

	hci_fwee_dev(data->hdev);
	kfwee_skb(data->wx_skb[0]);
	kfwee_skb(data->wx_skb[1]);
}

static stwuct usb_dwivew bpa10x_dwivew = {
	.name		= "bpa10x",
	.pwobe		= bpa10x_pwobe,
	.disconnect	= bpa10x_disconnect,
	.id_tabwe	= bpa10x_tabwe,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(bpa10x_dwivew);

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Digianswew Bwuetooth USB dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
