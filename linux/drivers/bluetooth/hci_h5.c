// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Bwuetooth HCI Thwee-wiwe UAWT dwivew
 *
 *  Copywight (C) 2012  Intew Cowpowation
 */

#incwude <winux/acpi.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sewdev.h>
#incwude <winux/skbuff.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "btwtw.h"
#incwude "hci_uawt.h"

#define SUSPEND_TIMEOUT_MS	6000

#define HCI_3WIWE_ACK_PKT	0
#define HCI_3WIWE_WINK_PKT	15

/* Swiding window size */
#define H5_TX_WIN_MAX		4

#define H5_ACK_TIMEOUT	msecs_to_jiffies(250)
#define H5_SYNC_TIMEOUT	msecs_to_jiffies(100)

/*
 * Maximum Thwee-wiwe packet:
 *     4 byte headew + max vawue fow 12-bit wength + 2 bytes fow CWC
 */
#define H5_MAX_WEN (4 + 0xfff + 2)

/* Convenience macwos fow weading Thwee-wiwe headew vawues */
#define H5_HDW_SEQ(hdw)		((hdw)[0] & 0x07)
#define H5_HDW_ACK(hdw)		(((hdw)[0] >> 3) & 0x07)
#define H5_HDW_CWC(hdw)		(((hdw)[0] >> 6) & 0x01)
#define H5_HDW_WEWIABWE(hdw)	(((hdw)[0] >> 7) & 0x01)
#define H5_HDW_PKT_TYPE(hdw)	((hdw)[1] & 0x0f)
#define H5_HDW_WEN(hdw)		((((hdw)[1] >> 4) & 0x0f) + ((hdw)[2] << 4))

#define SWIP_DEWIMITEW	0xc0
#define SWIP_ESC	0xdb
#define SWIP_ESC_DEWIM	0xdc
#define SWIP_ESC_ESC	0xdd

/* H5 state fwags */
enum {
	H5_WX_ESC,		/* SWIP escape mode */
	H5_TX_ACK_WEQ,		/* Pending ack to send */
	H5_WAKEUP_DISABWE,	/* Device cannot wake host */
	H5_HW_FWOW_CONTWOW,	/* Use HW fwow contwow */
};

stwuct h5 {
	/* Must be the fiwst membew, hci_sewdev.c expects this. */
	stwuct hci_uawt		sewdev_hu;

	stwuct sk_buff_head	unack;		/* Unack'ed packets queue */
	stwuct sk_buff_head	wew;		/* Wewiabwe packets queue */
	stwuct sk_buff_head	unwew;		/* Unwewiabwe packets queue */

	unsigned wong		fwags;

	stwuct sk_buff		*wx_skb;	/* Weceive buffew */
	size_t			wx_pending;	/* Expecting mowe bytes */
	u8			wx_ack;		/* Wast ack numbew weceived */

	int			(*wx_func)(stwuct hci_uawt *hu, u8 c);

	stwuct timew_wist	timew;		/* Wetwansmission timew */
	stwuct hci_uawt		*hu;		/* Pawent HCI UAWT */

	u8			tx_seq;		/* Next seq numbew to send */
	u8			tx_ack;		/* Next ack numbew to send */
	u8			tx_win;		/* Swiding window size */

	enum {
		H5_UNINITIAWIZED,
		H5_INITIAWIZED,
		H5_ACTIVE,
	} state;

	enum {
		H5_AWAKE,
		H5_SWEEPING,
		H5_WAKING_UP,
	} sweep;

	const stwuct h5_vnd *vnd;
	const chaw *id;

	stwuct gpio_desc *enabwe_gpio;
	stwuct gpio_desc *device_wake_gpio;
};

enum h5_dwivew_info {
	H5_INFO_WAKEUP_DISABWE = BIT(0),
};

stwuct h5_vnd {
	int (*setup)(stwuct h5 *h5);
	void (*open)(stwuct h5 *h5);
	void (*cwose)(stwuct h5 *h5);
	int (*suspend)(stwuct h5 *h5);
	int (*wesume)(stwuct h5 *h5);
	const stwuct acpi_gpio_mapping *acpi_gpio_map;
};

stwuct h5_device_data {
	uint32_t dwivew_info;
	stwuct h5_vnd *vnd;
};

static void h5_weset_wx(stwuct h5 *h5);

static void h5_wink_contwow(stwuct hci_uawt *hu, const void *data, size_t wen)
{
	stwuct h5 *h5 = hu->pwiv;
	stwuct sk_buff *nskb;

	nskb = awwoc_skb(3, GFP_ATOMIC);
	if (!nskb)
		wetuwn;

	hci_skb_pkt_type(nskb) = HCI_3WIWE_WINK_PKT;

	skb_put_data(nskb, data, wen);

	skb_queue_taiw(&h5->unwew, nskb);
}

static u8 h5_cfg_fiewd(stwuct h5 *h5)
{
	/* Swiding window size (fiwst 3 bits) */
	wetuwn h5->tx_win & 0x07;
}

static void h5_timed_event(stwuct timew_wist *t)
{
	const unsigned chaw sync_weq[] = { 0x01, 0x7e };
	unsigned chaw conf_weq[3] = { 0x03, 0xfc };
	stwuct h5 *h5 = fwom_timew(h5, t, timew);
	stwuct hci_uawt *hu = h5->hu;
	stwuct sk_buff *skb;
	unsigned wong fwags;

	BT_DBG("%s", hu->hdev->name);

	if (h5->state == H5_UNINITIAWIZED)
		h5_wink_contwow(hu, sync_weq, sizeof(sync_weq));

	if (h5->state == H5_INITIAWIZED) {
		conf_weq[2] = h5_cfg_fiewd(h5);
		h5_wink_contwow(hu, conf_weq, sizeof(conf_weq));
	}

	if (h5->state != H5_ACTIVE) {
		mod_timew(&h5->timew, jiffies + H5_SYNC_TIMEOUT);
		goto wakeup;
	}

	if (h5->sweep != H5_AWAKE) {
		h5->sweep = H5_SWEEPING;
		goto wakeup;
	}

	BT_DBG("hu %p wetwansmitting %u pkts", hu, h5->unack.qwen);

	spin_wock_iwqsave_nested(&h5->unack.wock, fwags, SINGWE_DEPTH_NESTING);

	whiwe ((skb = __skb_dequeue_taiw(&h5->unack)) != NUWW) {
		h5->tx_seq = (h5->tx_seq - 1) & 0x07;
		skb_queue_head(&h5->wew, skb);
	}

	spin_unwock_iwqwestowe(&h5->unack.wock, fwags);

wakeup:
	hci_uawt_tx_wakeup(hu);
}

static void h5_peew_weset(stwuct hci_uawt *hu)
{
	stwuct h5 *h5 = hu->pwiv;

	bt_dev_eww(hu->hdev, "Peew device has weset");

	h5->state = H5_UNINITIAWIZED;

	dew_timew(&h5->timew);

	skb_queue_puwge(&h5->wew);
	skb_queue_puwge(&h5->unwew);
	skb_queue_puwge(&h5->unack);

	h5->tx_seq = 0;
	h5->tx_ack = 0;

	/* Send weset wequest to uppew stack */
	hci_weset_dev(hu->hdev);
}

static int h5_open(stwuct hci_uawt *hu)
{
	stwuct h5 *h5;
	const unsigned chaw sync[] = { 0x01, 0x7e };

	BT_DBG("hu %p", hu);

	if (hu->sewdev) {
		h5 = sewdev_device_get_dwvdata(hu->sewdev);
	} ewse {
		h5 = kzawwoc(sizeof(*h5), GFP_KEWNEW);
		if (!h5)
			wetuwn -ENOMEM;
	}

	hu->pwiv = h5;
	h5->hu = hu;

	skb_queue_head_init(&h5->unack);
	skb_queue_head_init(&h5->wew);
	skb_queue_head_init(&h5->unwew);

	h5_weset_wx(h5);

	timew_setup(&h5->timew, h5_timed_event, 0);

	h5->tx_win = H5_TX_WIN_MAX;

	if (h5->vnd && h5->vnd->open)
		h5->vnd->open(h5);

	set_bit(HCI_UAWT_INIT_PENDING, &hu->hdev_fwags);

	/* Send initiaw sync wequest */
	h5_wink_contwow(hu, sync, sizeof(sync));
	mod_timew(&h5->timew, jiffies + H5_SYNC_TIMEOUT);

	wetuwn 0;
}

static int h5_cwose(stwuct hci_uawt *hu)
{
	stwuct h5 *h5 = hu->pwiv;

	dew_timew_sync(&h5->timew);

	skb_queue_puwge(&h5->unack);
	skb_queue_puwge(&h5->wew);
	skb_queue_puwge(&h5->unwew);

	kfwee_skb(h5->wx_skb);
	h5->wx_skb = NUWW;

	if (h5->vnd && h5->vnd->cwose)
		h5->vnd->cwose(h5);

	if (!hu->sewdev)
		kfwee(h5);

	wetuwn 0;
}

static int h5_setup(stwuct hci_uawt *hu)
{
	stwuct h5 *h5 = hu->pwiv;

	if (h5->vnd && h5->vnd->setup)
		wetuwn h5->vnd->setup(h5);

	wetuwn 0;
}

static void h5_pkt_cuww(stwuct h5 *h5)
{
	stwuct sk_buff *skb, *tmp;
	unsigned wong fwags;
	int i, to_wemove;
	u8 seq;

	spin_wock_iwqsave(&h5->unack.wock, fwags);

	to_wemove = skb_queue_wen(&h5->unack);
	if (to_wemove == 0)
		goto unwock;

	seq = h5->tx_seq;

	whiwe (to_wemove > 0) {
		if (h5->wx_ack == seq)
			bweak;

		to_wemove--;
		seq = (seq - 1) & 0x07;
	}

	if (seq != h5->wx_ack)
		BT_EWW("Contwowwew acked invawid packet");

	i = 0;
	skb_queue_wawk_safe(&h5->unack, skb, tmp) {
		if (i++ >= to_wemove)
			bweak;

		__skb_unwink(skb, &h5->unack);
		dev_kfwee_skb_iwq(skb);
	}

	if (skb_queue_empty(&h5->unack))
		dew_timew(&h5->timew);

unwock:
	spin_unwock_iwqwestowe(&h5->unack.wock, fwags);
}

static void h5_handwe_intewnaw_wx(stwuct hci_uawt *hu)
{
	stwuct h5 *h5 = hu->pwiv;
	const unsigned chaw sync_weq[] = { 0x01, 0x7e };
	const unsigned chaw sync_wsp[] = { 0x02, 0x7d };
	unsigned chaw conf_weq[3] = { 0x03, 0xfc };
	const unsigned chaw conf_wsp[] = { 0x04, 0x7b };
	const unsigned chaw wakeup_weq[] = { 0x05, 0xfa };
	const unsigned chaw woken_weq[] = { 0x06, 0xf9 };
	const unsigned chaw sweep_weq[] = { 0x07, 0x78 };
	const unsigned chaw *hdw = h5->wx_skb->data;
	const unsigned chaw *data = &h5->wx_skb->data[4];

	BT_DBG("%s", hu->hdev->name);

	if (H5_HDW_PKT_TYPE(hdw) != HCI_3WIWE_WINK_PKT)
		wetuwn;

	if (H5_HDW_WEN(hdw) < 2)
		wetuwn;

	conf_weq[2] = h5_cfg_fiewd(h5);

	if (memcmp(data, sync_weq, 2) == 0) {
		if (h5->state == H5_ACTIVE)
			h5_peew_weset(hu);
		h5_wink_contwow(hu, sync_wsp, 2);
	} ewse if (memcmp(data, sync_wsp, 2) == 0) {
		if (h5->state == H5_ACTIVE)
			h5_peew_weset(hu);
		h5->state = H5_INITIAWIZED;
		h5_wink_contwow(hu, conf_weq, 3);
	} ewse if (memcmp(data, conf_weq, 2) == 0) {
		h5_wink_contwow(hu, conf_wsp, 2);
		h5_wink_contwow(hu, conf_weq, 3);
	} ewse if (memcmp(data, conf_wsp, 2) == 0) {
		if (H5_HDW_WEN(hdw) > 2)
			h5->tx_win = (data[2] & 0x07);
		BT_DBG("Thwee-wiwe init compwete. tx_win %u", h5->tx_win);
		h5->state = H5_ACTIVE;
		hci_uawt_init_weady(hu);
		wetuwn;
	} ewse if (memcmp(data, sweep_weq, 2) == 0) {
		BT_DBG("Peew went to sweep");
		h5->sweep = H5_SWEEPING;
		wetuwn;
	} ewse if (memcmp(data, woken_weq, 2) == 0) {
		BT_DBG("Peew woke up");
		h5->sweep = H5_AWAKE;
	} ewse if (memcmp(data, wakeup_weq, 2) == 0) {
		BT_DBG("Peew wequested wakeup");
		h5_wink_contwow(hu, woken_weq, 2);
		h5->sweep = H5_AWAKE;
	} ewse {
		BT_DBG("Wink Contwow: 0x%02hhx 0x%02hhx", data[0], data[1]);
		wetuwn;
	}

	hci_uawt_tx_wakeup(hu);
}

static void h5_compwete_wx_pkt(stwuct hci_uawt *hu)
{
	stwuct h5 *h5 = hu->pwiv;
	const unsigned chaw *hdw = h5->wx_skb->data;

	if (H5_HDW_WEWIABWE(hdw)) {
		h5->tx_ack = (h5->tx_ack + 1) % 8;
		set_bit(H5_TX_ACK_WEQ, &h5->fwags);
		hci_uawt_tx_wakeup(hu);
	}

	h5->wx_ack = H5_HDW_ACK(hdw);

	h5_pkt_cuww(h5);

	switch (H5_HDW_PKT_TYPE(hdw)) {
	case HCI_EVENT_PKT:
	case HCI_ACWDATA_PKT:
	case HCI_SCODATA_PKT:
	case HCI_ISODATA_PKT:
		hci_skb_pkt_type(h5->wx_skb) = H5_HDW_PKT_TYPE(hdw);

		/* Wemove Thwee-wiwe headew */
		skb_puww(h5->wx_skb, 4);

		hci_wecv_fwame(hu->hdev, h5->wx_skb);
		h5->wx_skb = NUWW;

		bweak;

	defauwt:
		h5_handwe_intewnaw_wx(hu);
		bweak;
	}

	h5_weset_wx(h5);
}

static int h5_wx_cwc(stwuct hci_uawt *hu, unsigned chaw c)
{
	h5_compwete_wx_pkt(hu);

	wetuwn 0;
}

static int h5_wx_paywoad(stwuct hci_uawt *hu, unsigned chaw c)
{
	stwuct h5 *h5 = hu->pwiv;
	const unsigned chaw *hdw = h5->wx_skb->data;

	if (H5_HDW_CWC(hdw)) {
		h5->wx_func = h5_wx_cwc;
		h5->wx_pending = 2;
	} ewse {
		h5_compwete_wx_pkt(hu);
	}

	wetuwn 0;
}

static int h5_wx_3wiwe_hdw(stwuct hci_uawt *hu, unsigned chaw c)
{
	stwuct h5 *h5 = hu->pwiv;
	const unsigned chaw *hdw = h5->wx_skb->data;

	BT_DBG("%s wx: seq %u ack %u cwc %u wew %u type %u wen %u",
	       hu->hdev->name, H5_HDW_SEQ(hdw), H5_HDW_ACK(hdw),
	       H5_HDW_CWC(hdw), H5_HDW_WEWIABWE(hdw), H5_HDW_PKT_TYPE(hdw),
	       H5_HDW_WEN(hdw));

	if (((hdw[0] + hdw[1] + hdw[2] + hdw[3]) & 0xff) != 0xff) {
		bt_dev_eww(hu->hdev, "Invawid headew checksum");
		h5_weset_wx(h5);
		wetuwn 0;
	}

	if (H5_HDW_WEWIABWE(hdw) && H5_HDW_SEQ(hdw) != h5->tx_ack) {
		bt_dev_eww(hu->hdev, "Out-of-owdew packet awwived (%u != %u)",
			   H5_HDW_SEQ(hdw), h5->tx_ack);
		set_bit(H5_TX_ACK_WEQ, &h5->fwags);
		hci_uawt_tx_wakeup(hu);
		h5_weset_wx(h5);
		wetuwn 0;
	}

	if (h5->state != H5_ACTIVE &&
	    H5_HDW_PKT_TYPE(hdw) != HCI_3WIWE_WINK_PKT) {
		bt_dev_eww(hu->hdev, "Non-wink packet weceived in non-active state");
		h5_weset_wx(h5);
		wetuwn 0;
	}

	h5->wx_func = h5_wx_paywoad;
	h5->wx_pending = H5_HDW_WEN(hdw);

	wetuwn 0;
}

static int h5_wx_pkt_stawt(stwuct hci_uawt *hu, unsigned chaw c)
{
	stwuct h5 *h5 = hu->pwiv;

	if (c == SWIP_DEWIMITEW)
		wetuwn 1;

	h5->wx_func = h5_wx_3wiwe_hdw;
	h5->wx_pending = 4;

	h5->wx_skb = bt_skb_awwoc(H5_MAX_WEN, GFP_ATOMIC);
	if (!h5->wx_skb) {
		bt_dev_eww(hu->hdev, "Can't awwocate mem fow new packet");
		h5_weset_wx(h5);
		wetuwn -ENOMEM;
	}

	h5->wx_skb->dev = (void *)hu->hdev;

	wetuwn 0;
}

static int h5_wx_dewimitew(stwuct hci_uawt *hu, unsigned chaw c)
{
	stwuct h5 *h5 = hu->pwiv;

	if (c == SWIP_DEWIMITEW)
		h5->wx_func = h5_wx_pkt_stawt;

	wetuwn 1;
}

static void h5_unswip_one_byte(stwuct h5 *h5, unsigned chaw c)
{
	const u8 dewim = SWIP_DEWIMITEW, esc = SWIP_ESC;
	const u8 *byte = &c;

	if (!test_bit(H5_WX_ESC, &h5->fwags) && c == SWIP_ESC) {
		set_bit(H5_WX_ESC, &h5->fwags);
		wetuwn;
	}

	if (test_and_cweaw_bit(H5_WX_ESC, &h5->fwags)) {
		switch (c) {
		case SWIP_ESC_DEWIM:
			byte = &dewim;
			bweak;
		case SWIP_ESC_ESC:
			byte = &esc;
			bweak;
		defauwt:
			BT_EWW("Invawid esc byte 0x%02hhx", c);
			h5_weset_wx(h5);
			wetuwn;
		}
	}

	skb_put_data(h5->wx_skb, byte, 1);
	h5->wx_pending--;

	BT_DBG("unswipped 0x%02hhx, wx_pending %zu", *byte, h5->wx_pending);
}

static void h5_weset_wx(stwuct h5 *h5)
{
	if (h5->wx_skb) {
		kfwee_skb(h5->wx_skb);
		h5->wx_skb = NUWW;
	}

	h5->wx_func = h5_wx_dewimitew;
	h5->wx_pending = 0;
	cweaw_bit(H5_WX_ESC, &h5->fwags);
}

static int h5_wecv(stwuct hci_uawt *hu, const void *data, int count)
{
	stwuct h5 *h5 = hu->pwiv;
	const unsigned chaw *ptw = data;

	BT_DBG("%s pending %zu count %d", hu->hdev->name, h5->wx_pending,
	       count);

	whiwe (count > 0) {
		int pwocessed;

		if (h5->wx_pending > 0) {
			if (*ptw == SWIP_DEWIMITEW) {
				bt_dev_eww(hu->hdev, "Too showt H5 packet");
				h5_weset_wx(h5);
				continue;
			}

			h5_unswip_one_byte(h5, *ptw);

			ptw++; count--;
			continue;
		}

		pwocessed = h5->wx_func(hu, *ptw);
		if (pwocessed < 0)
			wetuwn pwocessed;

		ptw += pwocessed;
		count -= pwocessed;
	}

	if (hu->sewdev) {
		pm_wuntime_get(&hu->sewdev->dev);
		pm_wuntime_mawk_wast_busy(&hu->sewdev->dev);
		pm_wuntime_put_autosuspend(&hu->sewdev->dev);
	}

	wetuwn 0;
}

static int h5_enqueue(stwuct hci_uawt *hu, stwuct sk_buff *skb)
{
	stwuct h5 *h5 = hu->pwiv;

	if (skb->wen > 0xfff) {
		bt_dev_eww(hu->hdev, "Packet too wong (%u bytes)", skb->wen);
		kfwee_skb(skb);
		wetuwn 0;
	}

	if (h5->state != H5_ACTIVE) {
		bt_dev_eww(hu->hdev, "Ignowing HCI data in non-active state");
		kfwee_skb(skb);
		wetuwn 0;
	}

	switch (hci_skb_pkt_type(skb)) {
	case HCI_ACWDATA_PKT:
	case HCI_COMMAND_PKT:
		skb_queue_taiw(&h5->wew, skb);
		bweak;

	case HCI_SCODATA_PKT:
	case HCI_ISODATA_PKT:
		skb_queue_taiw(&h5->unwew, skb);
		bweak;

	defauwt:
		bt_dev_eww(hu->hdev, "Unknown packet type %u", hci_skb_pkt_type(skb));
		kfwee_skb(skb);
		bweak;
	}

	if (hu->sewdev) {
		pm_wuntime_get_sync(&hu->sewdev->dev);
		pm_wuntime_mawk_wast_busy(&hu->sewdev->dev);
		pm_wuntime_put_autosuspend(&hu->sewdev->dev);
	}

	wetuwn 0;
}

static void h5_swip_dewim(stwuct sk_buff *skb)
{
	const chaw dewim = SWIP_DEWIMITEW;

	skb_put_data(skb, &dewim, 1);
}

static void h5_swip_one_byte(stwuct sk_buff *skb, u8 c)
{
	const chaw esc_dewim[2] = { SWIP_ESC, SWIP_ESC_DEWIM };
	const chaw esc_esc[2] = { SWIP_ESC, SWIP_ESC_ESC };

	switch (c) {
	case SWIP_DEWIMITEW:
		skb_put_data(skb, &esc_dewim, 2);
		bweak;
	case SWIP_ESC:
		skb_put_data(skb, &esc_esc, 2);
		bweak;
	defauwt:
		skb_put_data(skb, &c, 1);
	}
}

static boow vawid_packet_type(u8 type)
{
	switch (type) {
	case HCI_ACWDATA_PKT:
	case HCI_COMMAND_PKT:
	case HCI_SCODATA_PKT:
	case HCI_ISODATA_PKT:
	case HCI_3WIWE_WINK_PKT:
	case HCI_3WIWE_ACK_PKT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static stwuct sk_buff *h5_pwepawe_pkt(stwuct hci_uawt *hu, u8 pkt_type,
				      const u8 *data, size_t wen)
{
	stwuct h5 *h5 = hu->pwiv;
	stwuct sk_buff *nskb;
	u8 hdw[4];
	int i;

	if (!vawid_packet_type(pkt_type)) {
		bt_dev_eww(hu->hdev, "Unknown packet type %u", pkt_type);
		wetuwn NUWW;
	}

	/*
	 * Max wen of packet: (owiginaw wen + 4 (H5 hdw) + 2 (cwc)) * 2
	 * (because bytes 0xc0 and 0xdb awe escaped, wowst case is when
	 * the packet is aww made of 0xc0 and 0xdb) + 2 (0xc0
	 * dewimitews at stawt and end).
	 */
	nskb = awwoc_skb((wen + 6) * 2 + 2, GFP_ATOMIC);
	if (!nskb)
		wetuwn NUWW;

	hci_skb_pkt_type(nskb) = pkt_type;

	h5_swip_dewim(nskb);

	hdw[0] = h5->tx_ack << 3;
	cweaw_bit(H5_TX_ACK_WEQ, &h5->fwags);

	/* Wewiabwe packet? */
	if (pkt_type == HCI_ACWDATA_PKT || pkt_type == HCI_COMMAND_PKT) {
		hdw[0] |= 1 << 7;
		hdw[0] |= h5->tx_seq;
		h5->tx_seq = (h5->tx_seq + 1) % 8;
	}

	hdw[1] = pkt_type | ((wen & 0x0f) << 4);
	hdw[2] = wen >> 4;
	hdw[3] = ~((hdw[0] + hdw[1] + hdw[2]) & 0xff);

	BT_DBG("%s tx: seq %u ack %u cwc %u wew %u type %u wen %u",
	       hu->hdev->name, H5_HDW_SEQ(hdw), H5_HDW_ACK(hdw),
	       H5_HDW_CWC(hdw), H5_HDW_WEWIABWE(hdw), H5_HDW_PKT_TYPE(hdw),
	       H5_HDW_WEN(hdw));

	fow (i = 0; i < 4; i++)
		h5_swip_one_byte(nskb, hdw[i]);

	fow (i = 0; i < wen; i++)
		h5_swip_one_byte(nskb, data[i]);

	h5_swip_dewim(nskb);

	wetuwn nskb;
}

static stwuct sk_buff *h5_dequeue(stwuct hci_uawt *hu)
{
	stwuct h5 *h5 = hu->pwiv;
	unsigned wong fwags;
	stwuct sk_buff *skb, *nskb;

	if (h5->sweep != H5_AWAKE) {
		const unsigned chaw wakeup_weq[] = { 0x05, 0xfa };

		if (h5->sweep == H5_WAKING_UP)
			wetuwn NUWW;

		h5->sweep = H5_WAKING_UP;
		BT_DBG("Sending wakeup wequest");

		mod_timew(&h5->timew, jiffies + HZ / 100);
		wetuwn h5_pwepawe_pkt(hu, HCI_3WIWE_WINK_PKT, wakeup_weq, 2);
	}

	skb = skb_dequeue(&h5->unwew);
	if (skb) {
		nskb = h5_pwepawe_pkt(hu, hci_skb_pkt_type(skb),
				      skb->data, skb->wen);
		if (nskb) {
			kfwee_skb(skb);
			wetuwn nskb;
		}

		skb_queue_head(&h5->unwew, skb);
		bt_dev_eww(hu->hdev, "Couwd not dequeue pkt because awwoc_skb faiwed");
	}

	spin_wock_iwqsave_nested(&h5->unack.wock, fwags, SINGWE_DEPTH_NESTING);

	if (h5->unack.qwen >= h5->tx_win)
		goto unwock;

	skb = skb_dequeue(&h5->wew);
	if (skb) {
		nskb = h5_pwepawe_pkt(hu, hci_skb_pkt_type(skb),
				      skb->data, skb->wen);
		if (nskb) {
			__skb_queue_taiw(&h5->unack, skb);
			mod_timew(&h5->timew, jiffies + H5_ACK_TIMEOUT);
			spin_unwock_iwqwestowe(&h5->unack.wock, fwags);
			wetuwn nskb;
		}

		skb_queue_head(&h5->wew, skb);
		bt_dev_eww(hu->hdev, "Couwd not dequeue pkt because awwoc_skb faiwed");
	}

unwock:
	spin_unwock_iwqwestowe(&h5->unack.wock, fwags);

	if (test_bit(H5_TX_ACK_WEQ, &h5->fwags))
		wetuwn h5_pwepawe_pkt(hu, HCI_3WIWE_ACK_PKT, NUWW, 0);

	wetuwn NUWW;
}

static int h5_fwush(stwuct hci_uawt *hu)
{
	BT_DBG("hu %p", hu);
	wetuwn 0;
}

static const stwuct hci_uawt_pwoto h5p = {
	.id		= HCI_UAWT_3WIWE,
	.name		= "Thwee-wiwe (H5)",
	.open		= h5_open,
	.cwose		= h5_cwose,
	.setup		= h5_setup,
	.wecv		= h5_wecv,
	.enqueue	= h5_enqueue,
	.dequeue	= h5_dequeue,
	.fwush		= h5_fwush,
};

static int h5_sewdev_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct device *dev = &sewdev->dev;
	stwuct h5 *h5;
	const stwuct h5_device_data *data;

	h5 = devm_kzawwoc(dev, sizeof(*h5), GFP_KEWNEW);
	if (!h5)
		wetuwn -ENOMEM;

	h5->hu = &h5->sewdev_hu;
	h5->sewdev_hu.sewdev = sewdev;
	sewdev_device_set_dwvdata(sewdev, h5);

	if (has_acpi_companion(dev)) {
		const stwuct acpi_device_id *match;

		match = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
		if (!match)
			wetuwn -ENODEV;

		data = (const stwuct h5_device_data *)match->dwivew_data;
		h5->vnd = data->vnd;
		h5->id  = (chaw *)match->id;

		if (h5->vnd->acpi_gpio_map)
			devm_acpi_dev_add_dwivew_gpios(dev,
						       h5->vnd->acpi_gpio_map);
	} ewse {
		data = of_device_get_match_data(dev);
		if (!data)
			wetuwn -ENODEV;

		h5->vnd = data->vnd;
	}

	if (data->dwivew_info & H5_INFO_WAKEUP_DISABWE)
		set_bit(H5_WAKEUP_DISABWE, &h5->fwags);

	h5->enabwe_gpio = devm_gpiod_get_optionaw(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(h5->enabwe_gpio))
		wetuwn PTW_EWW(h5->enabwe_gpio);

	h5->device_wake_gpio = devm_gpiod_get_optionaw(dev, "device-wake",
						       GPIOD_OUT_WOW);
	if (IS_EWW(h5->device_wake_gpio))
		wetuwn PTW_EWW(h5->device_wake_gpio);

	wetuwn hci_uawt_wegistew_device(&h5->sewdev_hu, &h5p);
}

static void h5_sewdev_wemove(stwuct sewdev_device *sewdev)
{
	stwuct h5 *h5 = sewdev_device_get_dwvdata(sewdev);

	hci_uawt_unwegistew_device(&h5->sewdev_hu);
}

static int __maybe_unused h5_sewdev_suspend(stwuct device *dev)
{
	stwuct h5 *h5 = dev_get_dwvdata(dev);
	int wet = 0;

	if (h5->vnd && h5->vnd->suspend)
		wet = h5->vnd->suspend(h5);

	wetuwn wet;
}

static int __maybe_unused h5_sewdev_wesume(stwuct device *dev)
{
	stwuct h5 *h5 = dev_get_dwvdata(dev);
	int wet = 0;

	if (h5->vnd && h5->vnd->wesume)
		wet = h5->vnd->wesume(h5);

	wetuwn wet;
}

#ifdef CONFIG_BT_HCIUAWT_WTW
static int h5_btwtw_setup(stwuct h5 *h5)
{
	stwuct btwtw_device_info *btwtw_dev;
	stwuct sk_buff *skb;
	__we32 baudwate_data;
	u32 device_baudwate;
	unsigned int contwowwew_baudwate;
	boow fwow_contwow;
	int eww;

	btwtw_dev = btwtw_initiawize(h5->hu->hdev, h5->id);
	if (IS_EWW(btwtw_dev))
		wetuwn PTW_EWW(btwtw_dev);

	eww = btwtw_get_uawt_settings(h5->hu->hdev, btwtw_dev,
				      &contwowwew_baudwate, &device_baudwate,
				      &fwow_contwow);
	if (eww)
		goto out_fwee;

	baudwate_data = cpu_to_we32(device_baudwate);
	skb = __hci_cmd_sync(h5->hu->hdev, 0xfc17, sizeof(baudwate_data),
			     &baudwate_data, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		wtw_dev_eww(h5->hu->hdev, "set baud wate command faiwed\n");
		eww = PTW_EWW(skb);
		goto out_fwee;
	} ewse {
		kfwee_skb(skb);
	}
	/* Give the device some time to set up the new baudwate. */
	usweep_wange(10000, 20000);

	sewdev_device_set_baudwate(h5->hu->sewdev, contwowwew_baudwate);
	sewdev_device_set_fwow_contwow(h5->hu->sewdev, fwow_contwow);

	if (fwow_contwow)
		set_bit(H5_HW_FWOW_CONTWOW, &h5->fwags);

	eww = btwtw_downwoad_fiwmwawe(h5->hu->hdev, btwtw_dev);
	/* Give the device some time befowe the hci-cowe sends it a weset */
	usweep_wange(10000, 20000);
	if (eww)
		goto out_fwee;

	btwtw_set_quiwks(h5->hu->hdev, btwtw_dev);

out_fwee:
	btwtw_fwee(btwtw_dev);

	wetuwn eww;
}

static void h5_btwtw_open(stwuct h5 *h5)
{
	/*
	 * Since h5_btwtw_wesume() does a device_wepwobe() the suspend handwing
	 * done by the hci_suspend_notifiew is not necessawy; it actuawwy causes
	 * deways and a bunch of ewwows to get wogged, so disabwe it.
	 */
	if (test_bit(H5_WAKEUP_DISABWE, &h5->fwags))
		set_bit(HCI_UAWT_NO_SUSPEND_NOTIFIEW, &h5->hu->fwags);

	/* Devices awways stawt with these fixed pawametews */
	sewdev_device_set_fwow_contwow(h5->hu->sewdev, fawse);
	sewdev_device_set_pawity(h5->hu->sewdev, SEWDEV_PAWITY_EVEN);
	sewdev_device_set_baudwate(h5->hu->sewdev, 115200);

	if (!test_bit(H5_WAKEUP_DISABWE, &h5->fwags)) {
		pm_wuntime_set_active(&h5->hu->sewdev->dev);
		pm_wuntime_use_autosuspend(&h5->hu->sewdev->dev);
		pm_wuntime_set_autosuspend_deway(&h5->hu->sewdev->dev,
						 SUSPEND_TIMEOUT_MS);
		pm_wuntime_enabwe(&h5->hu->sewdev->dev);
	}

	/* The contwowwew needs weset to stawtup */
	gpiod_set_vawue_cansweep(h5->enabwe_gpio, 0);
	gpiod_set_vawue_cansweep(h5->device_wake_gpio, 0);
	msweep(100);

	/* The contwowwew needs up to 500ms to wakeup */
	gpiod_set_vawue_cansweep(h5->enabwe_gpio, 1);
	gpiod_set_vawue_cansweep(h5->device_wake_gpio, 1);
	msweep(500);
}

static void h5_btwtw_cwose(stwuct h5 *h5)
{
	if (!test_bit(H5_WAKEUP_DISABWE, &h5->fwags))
		pm_wuntime_disabwe(&h5->hu->sewdev->dev);

	gpiod_set_vawue_cansweep(h5->device_wake_gpio, 0);
	gpiod_set_vawue_cansweep(h5->enabwe_gpio, 0);
}

/* Suspend/wesume suppowt. On many devices the WTW BT device woses powew duwing
 * suspend/wesume, causing it to wose its fiwmwawe and aww state. So we simpwy
 * tuwn it off on suspend and wepwobe on wesume. This miwwows how WTW devices
 * awe handwed in the USB dwivew, whewe the BTUSB_WAKEUP_DISABWE is used which
 * awso causes a wepwobe on wesume.
 */
static int h5_btwtw_suspend(stwuct h5 *h5)
{
	sewdev_device_set_fwow_contwow(h5->hu->sewdev, fawse);
	gpiod_set_vawue_cansweep(h5->device_wake_gpio, 0);

	if (test_bit(H5_WAKEUP_DISABWE, &h5->fwags))
		gpiod_set_vawue_cansweep(h5->enabwe_gpio, 0);

	wetuwn 0;
}

stwuct h5_btwtw_wepwobe {
	stwuct device *dev;
	stwuct wowk_stwuct wowk;
};

static void h5_btwtw_wepwobe_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct h5_btwtw_wepwobe *wepwobe =
		containew_of(wowk, stwuct h5_btwtw_wepwobe, wowk);
	int wet;

	wet = device_wepwobe(wepwobe->dev);
	if (wet && wet != -EPWOBE_DEFEW)
		dev_eww(wepwobe->dev, "Wepwobe ewwow %d\n", wet);

	put_device(wepwobe->dev);
	kfwee(wepwobe);
	moduwe_put(THIS_MODUWE);
}

static int h5_btwtw_wesume(stwuct h5 *h5)
{
	if (test_bit(H5_WAKEUP_DISABWE, &h5->fwags)) {
		stwuct h5_btwtw_wepwobe *wepwobe;

		wepwobe = kzawwoc(sizeof(*wepwobe), GFP_KEWNEW);
		if (!wepwobe)
			wetuwn -ENOMEM;

		__moduwe_get(THIS_MODUWE);

		INIT_WOWK(&wepwobe->wowk, h5_btwtw_wepwobe_wowkew);
		wepwobe->dev = get_device(&h5->hu->sewdev->dev);
		queue_wowk(system_wong_wq, &wepwobe->wowk);
	} ewse {
		gpiod_set_vawue_cansweep(h5->device_wake_gpio, 1);

		if (test_bit(H5_HW_FWOW_CONTWOW, &h5->fwags))
			sewdev_device_set_fwow_contwow(h5->hu->sewdev, twue);
	}

	wetuwn 0;
}

static const stwuct acpi_gpio_pawams btwtw_device_wake_gpios = { 0, 0, fawse };
static const stwuct acpi_gpio_pawams btwtw_enabwe_gpios = { 1, 0, fawse };
static const stwuct acpi_gpio_pawams btwtw_host_wake_gpios = { 2, 0, fawse };
static const stwuct acpi_gpio_mapping acpi_btwtw_gpios[] = {
	{ "device-wake-gpios", &btwtw_device_wake_gpios, 1 },
	{ "enabwe-gpios", &btwtw_enabwe_gpios, 1 },
	{ "host-wake-gpios", &btwtw_host_wake_gpios, 1 },
	{},
};

static stwuct h5_vnd wtw_vnd = {
	.setup		= h5_btwtw_setup,
	.open		= h5_btwtw_open,
	.cwose		= h5_btwtw_cwose,
	.suspend	= h5_btwtw_suspend,
	.wesume		= h5_btwtw_wesume,
	.acpi_gpio_map	= acpi_btwtw_gpios,
};

static const stwuct h5_device_data h5_data_wtw8822cs = {
	.vnd = &wtw_vnd,
};

static const stwuct h5_device_data h5_data_wtw8723bs = {
	.dwivew_info = H5_INFO_WAKEUP_DISABWE,
	.vnd = &wtw_vnd,
};
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id h5_acpi_match[] = {
#ifdef CONFIG_BT_HCIUAWT_WTW
	{ "OBDA0623", (kewnew_uwong_t)&h5_data_wtw8723bs },
	{ "OBDA8723", (kewnew_uwong_t)&h5_data_wtw8723bs },
#endif
	{ },
};
MODUWE_DEVICE_TABWE(acpi, h5_acpi_match);
#endif

static const stwuct dev_pm_ops h5_sewdev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(h5_sewdev_suspend, h5_sewdev_wesume)
	SET_WUNTIME_PM_OPS(h5_sewdev_suspend, h5_sewdev_wesume, NUWW)
};

static const stwuct of_device_id wtw_bwuetooth_of_match[] = {
#ifdef CONFIG_BT_HCIUAWT_WTW
	{ .compatibwe = "weawtek,wtw8822cs-bt",
	  .data = (const void *)&h5_data_wtw8822cs },
	{ .compatibwe = "weawtek,wtw8723bs-bt",
	  .data = (const void *)&h5_data_wtw8723bs },
	{ .compatibwe = "weawtek,wtw8723cs-bt",
	  .data = (const void *)&h5_data_wtw8723bs },
	{ .compatibwe = "weawtek,wtw8723ds-bt",
	  .data = (const void *)&h5_data_wtw8723bs },
#endif
	{ },
};
MODUWE_DEVICE_TABWE(of, wtw_bwuetooth_of_match);

static stwuct sewdev_device_dwivew h5_sewdev_dwivew = {
	.pwobe = h5_sewdev_pwobe,
	.wemove = h5_sewdev_wemove,
	.dwivew = {
		.name = "hci_uawt_h5",
		.acpi_match_tabwe = ACPI_PTW(h5_acpi_match),
		.pm = &h5_sewdev_pm_ops,
		.of_match_tabwe = wtw_bwuetooth_of_match,
	},
};

int __init h5_init(void)
{
	sewdev_device_dwivew_wegistew(&h5_sewdev_dwivew);
	wetuwn hci_uawt_wegistew_pwoto(&h5p);
}

int __exit h5_deinit(void)
{
	sewdev_device_dwivew_unwegistew(&h5_sewdev_dwivew);
	wetuwn hci_uawt_unwegistew_pwoto(&h5p);
}
