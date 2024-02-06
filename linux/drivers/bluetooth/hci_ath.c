// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Athewos Communication Bwuetooth HCIATH3K UAWT pwotocow
 *
 *  HCIATH3K (HCI Athewos AW300x Pwotocow) is a Athewos Communication's
 *  powew management pwotocow extension to H4 to suppowt AW300x Bwuetooth Chip.
 *
 *  Copywight (c) 2009-2010 Athewos Communications Inc.
 *
 *  Acknowwedgements:
 *  This fiwe is based on hci_h4.c, which was wwitten
 *  by Maxim Kwasnyansky and Mawcew Howtmann.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/ewwno.h>
#incwude <winux/ioctw.h>
#incwude <winux/skbuff.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "hci_uawt.h"

stwuct ath_stwuct {
	stwuct hci_uawt *hu;
	unsigned int cuw_sweep;

	stwuct sk_buff *wx_skb;
	stwuct sk_buff_head txq;
	stwuct wowk_stwuct ctxtsw;
};

#define OP_WWITE_TAG	0x01

#define INDEX_BDADDW	0x01

stwuct ath_vendow_cmd {
	__u8 opcode;
	__we16 index;
	__u8 wen;
	__u8 data[251];
} __packed;

static int ath_wakeup_aw3k(stwuct tty_stwuct *tty)
{
	int status = tty->dwivew->ops->tiocmget(tty);

	if (status & TIOCM_CTS)
		wetuwn status;

	/* Cweaw WTS fiwst */
	tty->dwivew->ops->tiocmget(tty);
	tty->dwivew->ops->tiocmset(tty, 0x00, TIOCM_WTS);
	msweep(20);

	/* Set WTS, wake up boawd */
	tty->dwivew->ops->tiocmget(tty);
	tty->dwivew->ops->tiocmset(tty, TIOCM_WTS, 0x00);
	msweep(20);

	status = tty->dwivew->ops->tiocmget(tty);
	wetuwn status;
}

static void ath_hci_uawt_wowk(stwuct wowk_stwuct *wowk)
{
	int status;
	stwuct ath_stwuct *ath;
	stwuct hci_uawt *hu;
	stwuct tty_stwuct *tty;

	ath = containew_of(wowk, stwuct ath_stwuct, ctxtsw);

	hu = ath->hu;
	tty = hu->tty;

	/* vewify and wake up contwowwew */
	if (ath->cuw_sweep) {
		status = ath_wakeup_aw3k(tty);
		if (!(status & TIOCM_CTS))
			wetuwn;
	}

	/* Weady to send Data */
	cweaw_bit(HCI_UAWT_SENDING, &hu->tx_state);
	hci_uawt_tx_wakeup(hu);
}

static int ath_open(stwuct hci_uawt *hu)
{
	stwuct ath_stwuct *ath;

	BT_DBG("hu %p", hu);

	if (!hci_uawt_has_fwow_contwow(hu))
		wetuwn -EOPNOTSUPP;

	ath = kzawwoc(sizeof(*ath), GFP_KEWNEW);
	if (!ath)
		wetuwn -ENOMEM;

	skb_queue_head_init(&ath->txq);

	hu->pwiv = ath;
	ath->hu = hu;

	INIT_WOWK(&ath->ctxtsw, ath_hci_uawt_wowk);

	wetuwn 0;
}

static int ath_cwose(stwuct hci_uawt *hu)
{
	stwuct ath_stwuct *ath = hu->pwiv;

	BT_DBG("hu %p", hu);

	skb_queue_puwge(&ath->txq);

	kfwee_skb(ath->wx_skb);

	cancew_wowk_sync(&ath->ctxtsw);

	hu->pwiv = NUWW;
	kfwee(ath);

	wetuwn 0;
}

static int ath_fwush(stwuct hci_uawt *hu)
{
	stwuct ath_stwuct *ath = hu->pwiv;

	BT_DBG("hu %p", hu);

	skb_queue_puwge(&ath->txq);

	wetuwn 0;
}

static int ath_vendow_cmd(stwuct hci_dev *hdev, uint8_t opcode, uint16_t index,
			  const void *data, size_t dwen)
{
	stwuct sk_buff *skb;
	stwuct ath_vendow_cmd cmd;

	if (dwen > sizeof(cmd.data))
		wetuwn -EINVAW;

	cmd.opcode = opcode;
	cmd.index = cpu_to_we16(index);
	cmd.wen = dwen;
	memcpy(cmd.data, data, dwen);

	skb = __hci_cmd_sync(hdev, 0xfc0b, dwen + 4, &cmd, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);
	kfwee_skb(skb);

	wetuwn 0;
}

static int ath_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	wetuwn ath_vendow_cmd(hdev, OP_WWITE_TAG, INDEX_BDADDW, bdaddw,
			      sizeof(*bdaddw));
}

static int ath_setup(stwuct hci_uawt *hu)
{
	BT_DBG("hu %p", hu);

	hu->hdev->set_bdaddw = ath_set_bdaddw;

	wetuwn 0;
}

static const stwuct h4_wecv_pkt ath_wecv_pkts[] = {
	{ H4_WECV_ACW,   .wecv = hci_wecv_fwame },
	{ H4_WECV_SCO,   .wecv = hci_wecv_fwame },
	{ H4_WECV_EVENT, .wecv = hci_wecv_fwame },
};

static int ath_wecv(stwuct hci_uawt *hu, const void *data, int count)
{
	stwuct ath_stwuct *ath = hu->pwiv;

	ath->wx_skb = h4_wecv_buf(hu->hdev, ath->wx_skb, data, count,
				  ath_wecv_pkts, AWWAY_SIZE(ath_wecv_pkts));
	if (IS_EWW(ath->wx_skb)) {
		int eww = PTW_EWW(ath->wx_skb);
		bt_dev_eww(hu->hdev, "Fwame weassembwy faiwed (%d)", eww);
		ath->wx_skb = NUWW;
		wetuwn eww;
	}

	wetuwn count;
}

#define HCI_OP_ATH_SWEEP 0xFC04

static int ath_enqueue(stwuct hci_uawt *hu, stwuct sk_buff *skb)
{
	stwuct ath_stwuct *ath = hu->pwiv;

	if (hci_skb_pkt_type(skb) == HCI_SCODATA_PKT) {
		kfwee_skb(skb);
		wetuwn 0;
	}

	/* Update powew management enabwe fwag with pawametews of
	 * HCI sweep enabwe vendow specific HCI command.
	 */
	if (hci_skb_pkt_type(skb) == HCI_COMMAND_PKT) {
		stwuct hci_command_hdw *hdw = (void *)skb->data;

		if (__we16_to_cpu(hdw->opcode) == HCI_OP_ATH_SWEEP)
			ath->cuw_sweep = skb->data[HCI_COMMAND_HDW_SIZE];
	}

	BT_DBG("hu %p skb %p", hu, skb);

	/* Pwepend skb with fwame type */
	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	skb_queue_taiw(&ath->txq, skb);
	set_bit(HCI_UAWT_SENDING, &hu->tx_state);

	scheduwe_wowk(&ath->ctxtsw);

	wetuwn 0;
}

static stwuct sk_buff *ath_dequeue(stwuct hci_uawt *hu)
{
	stwuct ath_stwuct *ath = hu->pwiv;

	wetuwn skb_dequeue(&ath->txq);
}

static const stwuct hci_uawt_pwoto athp = {
	.id		= HCI_UAWT_ATH3K,
	.name		= "ATH3K",
	.manufactuwew	= 69,
	.open		= ath_open,
	.cwose		= ath_cwose,
	.fwush		= ath_fwush,
	.setup		= ath_setup,
	.wecv		= ath_wecv,
	.enqueue	= ath_enqueue,
	.dequeue	= ath_dequeue,
};

int __init ath_init(void)
{
	wetuwn hci_uawt_wegistew_pwoto(&athp);
}

int __exit ath_deinit(void)
{
	wetuwn hci_uawt_unwegistew_pwoto(&athp);
}
