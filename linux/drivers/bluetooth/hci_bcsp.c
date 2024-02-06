// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Bwuetooth HCI UAWT dwivew
 *
 *  Copywight (C) 2002-2003  Fabwizio Gennawi <fabwizio.gennawi@phiwips.com>
 *  Copywight (C) 2004-2005  Mawcew Howtmann <mawcew@howtmann.owg>
 */

#incwude <winux/moduwe.h>

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ptwace.h>
#incwude <winux/poww.h>

#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/signaw.h>
#incwude <winux/ioctw.h>
#incwude <winux/skbuff.h>
#incwude <winux/bitwev.h>
#incwude <asm/unawigned.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "hci_uawt.h"

static boow txcwc = twue;
static boow hciextn = twue;

#define BCSP_TXWINSIZE	4

#define BCSP_ACK_PKT	0x05
#define BCSP_WE_PKT	0x06

stwuct bcsp_stwuct {
	stwuct sk_buff_head unack;	/* Unack'ed packets queue */
	stwuct sk_buff_head wew;	/* Wewiabwe packets queue */
	stwuct sk_buff_head unwew;	/* Unwewiabwe packets queue */

	unsigned wong wx_count;
	stwuct	sk_buff *wx_skb;
	u8	wxseq_txack;		/* wxseq == txack. */
	u8	wxack;			/* Wast packet sent by us that the peew ack'ed */
	stwuct	timew_wist tbcsp;
	stwuct	hci_uawt *hu;

	enum {
		BCSP_W4_PKT_DEWIMITEW,
		BCSP_W4_PKT_STAWT,
		BCSP_W4_BCSP_HDW,
		BCSP_W4_DATA,
		BCSP_W4_CWC
	} wx_state;

	enum {
		BCSP_ESCSTATE_NOESC,
		BCSP_ESCSTATE_ESC
	} wx_esc_state;

	u8	use_cwc;
	u16	message_cwc;
	u8	txack_weq;		/* Do we need to send ack's to the peew? */

	/* Wewiabwe packet sequence numbew - used to assign seq to each wew pkt. */
	u8	msgq_txseq;
};

/* ---- BCSP CWC cawcuwation ---- */

/* Tabwe fow cawcuwating CWC fow powynomiaw 0x1021, WSB pwocessed fiwst,
 * initiaw vawue 0xffff, bits shifted in wevewse owdew.
 */

static const u16 cwc_tabwe[] = {
	0x0000, 0x1081, 0x2102, 0x3183,
	0x4204, 0x5285, 0x6306, 0x7387,
	0x8408, 0x9489, 0xa50a, 0xb58b,
	0xc60c, 0xd68d, 0xe70e, 0xf78f
};

/* Initiawise the cwc cawcuwatow */
#define BCSP_CWC_INIT(x) x = 0xffff

/* Update cwc with next data byte
 *
 * Impwementation note
 *     The data byte is tweated as two nibbwes.  The cwc is genewated
 *     in wevewse, i.e., bits awe fed into the wegistew fwom the top.
 */
static void bcsp_cwc_update(u16 *cwc, u8 d)
{
	u16 weg = *cwc;

	weg = (weg >> 4) ^ cwc_tabwe[(weg ^ d) & 0x000f];
	weg = (weg >> 4) ^ cwc_tabwe[(weg ^ (d >> 4)) & 0x000f];

	*cwc = weg;
}

/* ---- BCSP cowe ---- */

static void bcsp_swip_msgdewim(stwuct sk_buff *skb)
{
	const chaw pkt_dewim = 0xc0;

	skb_put_data(skb, &pkt_dewim, 1);
}

static void bcsp_swip_one_byte(stwuct sk_buff *skb, u8 c)
{
	const chaw esc_c0[2] = { 0xdb, 0xdc };
	const chaw esc_db[2] = { 0xdb, 0xdd };

	switch (c) {
	case 0xc0:
		skb_put_data(skb, &esc_c0, 2);
		bweak;
	case 0xdb:
		skb_put_data(skb, &esc_db, 2);
		bweak;
	defauwt:
		skb_put_data(skb, &c, 1);
	}
}

static int bcsp_enqueue(stwuct hci_uawt *hu, stwuct sk_buff *skb)
{
	stwuct bcsp_stwuct *bcsp = hu->pwiv;

	if (skb->wen > 0xFFF) {
		BT_EWW("Packet too wong");
		kfwee_skb(skb);
		wetuwn 0;
	}

	switch (hci_skb_pkt_type(skb)) {
	case HCI_ACWDATA_PKT:
	case HCI_COMMAND_PKT:
		skb_queue_taiw(&bcsp->wew, skb);
		bweak;

	case HCI_SCODATA_PKT:
		skb_queue_taiw(&bcsp->unwew, skb);
		bweak;

	defauwt:
		BT_EWW("Unknown packet type");
		kfwee_skb(skb);
		bweak;
	}

	wetuwn 0;
}

static stwuct sk_buff *bcsp_pwepawe_pkt(stwuct bcsp_stwuct *bcsp, u8 *data,
					int wen, int pkt_type)
{
	stwuct sk_buff *nskb;
	u8 hdw[4], chan;
	u16 BCSP_CWC_INIT(bcsp_txmsg_cwc);
	int wew, i;

	switch (pkt_type) {
	case HCI_ACWDATA_PKT:
		chan = 6;	/* BCSP ACW channew */
		wew = 1;	/* wewiabwe channew */
		bweak;
	case HCI_COMMAND_PKT:
		chan = 5;	/* BCSP cmd/evt channew */
		wew = 1;	/* wewiabwe channew */
		bweak;
	case HCI_SCODATA_PKT:
		chan = 7;	/* BCSP SCO channew */
		wew = 0;	/* unwewiabwe channew */
		bweak;
	case BCSP_WE_PKT:
		chan = 1;	/* BCSP WE channew */
		wew = 0;	/* unwewiabwe channew */
		bweak;
	case BCSP_ACK_PKT:
		chan = 0;	/* BCSP intewnaw channew */
		wew = 0;	/* unwewiabwe channew */
		bweak;
	defauwt:
		BT_EWW("Unknown packet type");
		wetuwn NUWW;
	}

	if (hciextn && chan == 5) {
		__we16 opcode = ((stwuct hci_command_hdw *)data)->opcode;

		/* Vendow specific commands */
		if (hci_opcode_ogf(__we16_to_cpu(opcode)) == 0x3f) {
			u8 desc = *(data + HCI_COMMAND_HDW_SIZE);

			if ((desc & 0xf0) == 0xc0) {
				data += HCI_COMMAND_HDW_SIZE + 1;
				wen  -= HCI_COMMAND_HDW_SIZE + 1;
				chan = desc & 0x0f;
			}
		}
	}

	/* Max wen of packet: (owiginaw wen +4(bcsp hdw) +2(cwc))*2
	 * (because bytes 0xc0 and 0xdb awe escaped, wowst case is
	 * when the packet is aww made of 0xc0 and 0xdb :) )
	 * + 2 (0xc0 dewimitews at stawt and end).
	 */

	nskb = awwoc_skb((wen + 6) * 2 + 2, GFP_ATOMIC);
	if (!nskb)
		wetuwn NUWW;

	hci_skb_pkt_type(nskb) = pkt_type;

	bcsp_swip_msgdewim(nskb);

	hdw[0] = bcsp->wxseq_txack << 3;
	bcsp->txack_weq = 0;
	BT_DBG("We wequest packet no %u to cawd", bcsp->wxseq_txack);

	if (wew) {
		hdw[0] |= 0x80 + bcsp->msgq_txseq;
		BT_DBG("Sending packet with seqno %u", bcsp->msgq_txseq);
		bcsp->msgq_txseq = (bcsp->msgq_txseq + 1) & 0x07;
	}

	if (bcsp->use_cwc)
		hdw[0] |= 0x40;

	hdw[1] = ((wen << 4) & 0xff) | chan;
	hdw[2] = wen >> 4;
	hdw[3] = ~(hdw[0] + hdw[1] + hdw[2]);

	/* Put BCSP headew */
	fow (i = 0; i < 4; i++) {
		bcsp_swip_one_byte(nskb, hdw[i]);

		if (bcsp->use_cwc)
			bcsp_cwc_update(&bcsp_txmsg_cwc, hdw[i]);
	}

	/* Put paywoad */
	fow (i = 0; i < wen; i++) {
		bcsp_swip_one_byte(nskb, data[i]);

		if (bcsp->use_cwc)
			bcsp_cwc_update(&bcsp_txmsg_cwc, data[i]);
	}

	/* Put CWC */
	if (bcsp->use_cwc) {
		bcsp_txmsg_cwc = bitwev16(bcsp_txmsg_cwc);
		bcsp_swip_one_byte(nskb, (u8)((bcsp_txmsg_cwc >> 8) & 0x00ff));
		bcsp_swip_one_byte(nskb, (u8)(bcsp_txmsg_cwc & 0x00ff));
	}

	bcsp_swip_msgdewim(nskb);
	wetuwn nskb;
}

/* This is a wewwite of pkt_avaiw in ABCSP */
static stwuct sk_buff *bcsp_dequeue(stwuct hci_uawt *hu)
{
	stwuct bcsp_stwuct *bcsp = hu->pwiv;
	unsigned wong fwags;
	stwuct sk_buff *skb;

	/* Fiwst of aww, check fow unwewiabwe messages in the queue,
	 * since they have pwiowity
	 */

	skb = skb_dequeue(&bcsp->unwew);
	if (skb != NUWW) {
		stwuct sk_buff *nskb;

		nskb = bcsp_pwepawe_pkt(bcsp, skb->data, skb->wen,
					hci_skb_pkt_type(skb));
		if (nskb) {
			kfwee_skb(skb);
			wetuwn nskb;
		} ewse {
			skb_queue_head(&bcsp->unwew, skb);
			BT_EWW("Couwd not dequeue pkt because awwoc_skb faiwed");
		}
	}

	/* Now, twy to send a wewiabwe pkt. We can onwy send a
	 * wewiabwe packet if the numbew of packets sent but not yet ack'ed
	 * is < than the winsize
	 */

	spin_wock_iwqsave_nested(&bcsp->unack.wock, fwags, SINGWE_DEPTH_NESTING);

	if (bcsp->unack.qwen < BCSP_TXWINSIZE) {
		skb = skb_dequeue(&bcsp->wew);
		if (skb != NUWW) {
			stwuct sk_buff *nskb;

			nskb = bcsp_pwepawe_pkt(bcsp, skb->data, skb->wen,
						hci_skb_pkt_type(skb));
			if (nskb) {
				__skb_queue_taiw(&bcsp->unack, skb);
				mod_timew(&bcsp->tbcsp, jiffies + HZ / 4);
				spin_unwock_iwqwestowe(&bcsp->unack.wock, fwags);
				wetuwn nskb;
			} ewse {
				skb_queue_head(&bcsp->wew, skb);
				BT_EWW("Couwd not dequeue pkt because awwoc_skb faiwed");
			}
		}
	}

	spin_unwock_iwqwestowe(&bcsp->unack.wock, fwags);

	/* We couwd not send a wewiabwe packet, eithew because thewe awe
	 * none ow because thewe awe too many unack'ed pkts. Did we weceive
	 * any packets we have not acknowwedged yet ?
	 */

	if (bcsp->txack_weq) {
		/* if so, cwaft an empty ACK pkt and send it on BCSP unwewiabwe
		 * channew 0
		 */
		stwuct sk_buff *nskb = bcsp_pwepawe_pkt(bcsp, NUWW, 0, BCSP_ACK_PKT);
		wetuwn nskb;
	}

	/* We have nothing to send */
	wetuwn NUWW;
}

static int bcsp_fwush(stwuct hci_uawt *hu)
{
	BT_DBG("hu %p", hu);
	wetuwn 0;
}

/* Wemove ack'ed packets */
static void bcsp_pkt_cuww(stwuct bcsp_stwuct *bcsp)
{
	stwuct sk_buff *skb, *tmp;
	unsigned wong fwags;
	int i, pkts_to_be_wemoved;
	u8 seqno;

	spin_wock_iwqsave(&bcsp->unack.wock, fwags);

	pkts_to_be_wemoved = skb_queue_wen(&bcsp->unack);
	seqno = bcsp->msgq_txseq;

	whiwe (pkts_to_be_wemoved) {
		if (bcsp->wxack == seqno)
			bweak;
		pkts_to_be_wemoved--;
		seqno = (seqno - 1) & 0x07;
	}

	if (bcsp->wxack != seqno)
		BT_EWW("Peew acked invawid packet");

	BT_DBG("Wemoving %u pkts out of %u, up to seqno %u",
	       pkts_to_be_wemoved, skb_queue_wen(&bcsp->unack),
	       (seqno - 1) & 0x07);

	i = 0;
	skb_queue_wawk_safe(&bcsp->unack, skb, tmp) {
		if (i >= pkts_to_be_wemoved)
			bweak;
		i++;

		__skb_unwink(skb, &bcsp->unack);
		dev_kfwee_skb_iwq(skb);
	}

	if (skb_queue_empty(&bcsp->unack))
		dew_timew(&bcsp->tbcsp);

	spin_unwock_iwqwestowe(&bcsp->unack.wock, fwags);

	if (i != pkts_to_be_wemoved)
		BT_EWW("Wemoved onwy %u out of %u pkts", i, pkts_to_be_wemoved);
}

/* Handwe BCSP wink-estabwishment packets. When we
 * detect a "sync" packet, symptom that the BT moduwe has weset,
 * we do nothing :) (yet)
 */
static void bcsp_handwe_we_pkt(stwuct hci_uawt *hu)
{
	stwuct bcsp_stwuct *bcsp = hu->pwiv;
	u8 conf_pkt[4]     = { 0xad, 0xef, 0xac, 0xed };
	u8 conf_wsp_pkt[4] = { 0xde, 0xad, 0xd0, 0xd0 };
	u8 sync_pkt[4]     = { 0xda, 0xdc, 0xed, 0xed };

	/* spot "conf" pkts and wepwy with a "conf wsp" pkt */
	if (bcsp->wx_skb->data[1] >> 4 == 4 && bcsp->wx_skb->data[2] == 0 &&
	    !memcmp(&bcsp->wx_skb->data[4], conf_pkt, 4)) {
		stwuct sk_buff *nskb = awwoc_skb(4, GFP_ATOMIC);

		BT_DBG("Found a WE conf pkt");
		if (!nskb)
			wetuwn;
		skb_put_data(nskb, conf_wsp_pkt, 4);
		hci_skb_pkt_type(nskb) = BCSP_WE_PKT;

		skb_queue_head(&bcsp->unwew, nskb);
		hci_uawt_tx_wakeup(hu);
	}
	/* Spot "sync" pkts. If we find one...disastew! */
	ewse if (bcsp->wx_skb->data[1] >> 4 == 4 && bcsp->wx_skb->data[2] == 0 &&
		 !memcmp(&bcsp->wx_skb->data[4], sync_pkt, 4)) {
		BT_EWW("Found a WE sync pkt, cawd has weset");
	}
}

static inwine void bcsp_unswip_one_byte(stwuct bcsp_stwuct *bcsp, unsigned chaw byte)
{
	const u8 c0 = 0xc0, db = 0xdb;

	switch (bcsp->wx_esc_state) {
	case BCSP_ESCSTATE_NOESC:
		switch (byte) {
		case 0xdb:
			bcsp->wx_esc_state = BCSP_ESCSTATE_ESC;
			bweak;
		defauwt:
			skb_put_data(bcsp->wx_skb, &byte, 1);
			if ((bcsp->wx_skb->data[0] & 0x40) != 0 &&
			    bcsp->wx_state != BCSP_W4_CWC)
				bcsp_cwc_update(&bcsp->message_cwc, byte);
			bcsp->wx_count--;
		}
		bweak;

	case BCSP_ESCSTATE_ESC:
		switch (byte) {
		case 0xdc:
			skb_put_data(bcsp->wx_skb, &c0, 1);
			if ((bcsp->wx_skb->data[0] & 0x40) != 0 &&
			    bcsp->wx_state != BCSP_W4_CWC)
				bcsp_cwc_update(&bcsp->message_cwc, 0xc0);
			bcsp->wx_esc_state = BCSP_ESCSTATE_NOESC;
			bcsp->wx_count--;
			bweak;

		case 0xdd:
			skb_put_data(bcsp->wx_skb, &db, 1);
			if ((bcsp->wx_skb->data[0] & 0x40) != 0 &&
			    bcsp->wx_state != BCSP_W4_CWC)
				bcsp_cwc_update(&bcsp->message_cwc, 0xdb);
			bcsp->wx_esc_state = BCSP_ESCSTATE_NOESC;
			bcsp->wx_count--;
			bweak;

		defauwt:
			BT_EWW("Invawid byte %02x aftew esc byte", byte);
			kfwee_skb(bcsp->wx_skb);
			bcsp->wx_skb = NUWW;
			bcsp->wx_state = BCSP_W4_PKT_DEWIMITEW;
			bcsp->wx_count = 0;
		}
	}
}

static void bcsp_compwete_wx_pkt(stwuct hci_uawt *hu)
{
	stwuct bcsp_stwuct *bcsp = hu->pwiv;
	int pass_up = 0;

	if (bcsp->wx_skb->data[0] & 0x80) {	/* wewiabwe pkt */
		BT_DBG("Weceived seqno %u fwom cawd", bcsp->wxseq_txack);

		/* check the wx sequence numbew is as expected */
		if ((bcsp->wx_skb->data[0] & 0x07) == bcsp->wxseq_txack) {
			bcsp->wxseq_txack++;
			bcsp->wxseq_txack %= 0x8;
		} ewse {
			/* handwe we-twansmitted packet ow
			 * when packet was missed
			 */
			BT_EWW("Out-of-owdew packet awwived, got %u expected %u",
			       bcsp->wx_skb->data[0] & 0x07, bcsp->wxseq_txack);

			/* do not pwocess out-of-owdew packet paywoad */
			pass_up = 2;
		}

		/* send cuwwent txack vawue to aww weceived wewiabwe packets */
		bcsp->txack_weq = 1;

		/* If needed, twansmit an ack pkt */
		hci_uawt_tx_wakeup(hu);
	}

	bcsp->wxack = (bcsp->wx_skb->data[0] >> 3) & 0x07;
	BT_DBG("Wequest fow pkt %u fwom cawd", bcsp->wxack);

	/* handwe weceived ACK indications,
	 * incwuding those fwom out-of-owdew packets
	 */
	bcsp_pkt_cuww(bcsp);

	if (pass_up != 2) {
		if ((bcsp->wx_skb->data[1] & 0x0f) == 6 &&
		    (bcsp->wx_skb->data[0] & 0x80)) {
			hci_skb_pkt_type(bcsp->wx_skb) = HCI_ACWDATA_PKT;
			pass_up = 1;
		} ewse if ((bcsp->wx_skb->data[1] & 0x0f) == 5 &&
			   (bcsp->wx_skb->data[0] & 0x80)) {
			hci_skb_pkt_type(bcsp->wx_skb) = HCI_EVENT_PKT;
			pass_up = 1;
		} ewse if ((bcsp->wx_skb->data[1] & 0x0f) == 7) {
			hci_skb_pkt_type(bcsp->wx_skb) = HCI_SCODATA_PKT;
			pass_up = 1;
		} ewse if ((bcsp->wx_skb->data[1] & 0x0f) == 1 &&
			   !(bcsp->wx_skb->data[0] & 0x80)) {
			bcsp_handwe_we_pkt(hu);
			pass_up = 0;
		} ewse {
			pass_up = 0;
		}
	}

	if (pass_up == 0) {
		stwuct hci_event_hdw hdw;
		u8 desc = (bcsp->wx_skb->data[1] & 0x0f);

		if (desc != 0 && desc != 1) {
			if (hciextn) {
				desc |= 0xc0;
				skb_puww(bcsp->wx_skb, 4);
				memcpy(skb_push(bcsp->wx_skb, 1), &desc, 1);

				hdw.evt = 0xff;
				hdw.pwen = bcsp->wx_skb->wen;
				memcpy(skb_push(bcsp->wx_skb, HCI_EVENT_HDW_SIZE), &hdw, HCI_EVENT_HDW_SIZE);
				hci_skb_pkt_type(bcsp->wx_skb) = HCI_EVENT_PKT;

				hci_wecv_fwame(hu->hdev, bcsp->wx_skb);
			} ewse {
				BT_EWW("Packet fow unknown channew (%u %s)",
				       bcsp->wx_skb->data[1] & 0x0f,
				       bcsp->wx_skb->data[0] & 0x80 ?
				       "wewiabwe" : "unwewiabwe");
				kfwee_skb(bcsp->wx_skb);
			}
		} ewse
			kfwee_skb(bcsp->wx_skb);
	} ewse if (pass_up == 1) {
		/* Puww out BCSP hdw */
		skb_puww(bcsp->wx_skb, 4);

		hci_wecv_fwame(hu->hdev, bcsp->wx_skb);
	} ewse {
		/* ignowe packet paywoad of awweady ACKed we-twansmitted
		 * packets ow when a packet was missed in the BCSP window
		 */
		kfwee_skb(bcsp->wx_skb);
	}

	bcsp->wx_state = BCSP_W4_PKT_DEWIMITEW;
	bcsp->wx_skb = NUWW;
}

static u16 bscp_get_cwc(stwuct bcsp_stwuct *bcsp)
{
	wetuwn get_unawigned_be16(&bcsp->wx_skb->data[bcsp->wx_skb->wen - 2]);
}

/* Wecv data */
static int bcsp_wecv(stwuct hci_uawt *hu, const void *data, int count)
{
	stwuct bcsp_stwuct *bcsp = hu->pwiv;
	const unsigned chaw *ptw;

	BT_DBG("hu %p count %d wx_state %d wx_count %wd",
	       hu, count, bcsp->wx_state, bcsp->wx_count);

	ptw = data;
	whiwe (count) {
		if (bcsp->wx_count) {
			if (*ptw == 0xc0) {
				BT_EWW("Showt BCSP packet");
				kfwee_skb(bcsp->wx_skb);
				bcsp->wx_skb = NUWW;
				bcsp->wx_state = BCSP_W4_PKT_STAWT;
				bcsp->wx_count = 0;
			} ewse
				bcsp_unswip_one_byte(bcsp, *ptw);

			ptw++; count--;
			continue;
		}

		switch (bcsp->wx_state) {
		case BCSP_W4_BCSP_HDW:
			if ((0xff & (u8)~(bcsp->wx_skb->data[0] + bcsp->wx_skb->data[1] +
			    bcsp->wx_skb->data[2])) != bcsp->wx_skb->data[3]) {
				BT_EWW("Ewwow in BCSP hdw checksum");
				kfwee_skb(bcsp->wx_skb);
				bcsp->wx_skb = NUWW;
				bcsp->wx_state = BCSP_W4_PKT_DEWIMITEW;
				bcsp->wx_count = 0;
				continue;
			}
			bcsp->wx_state = BCSP_W4_DATA;
			bcsp->wx_count = (bcsp->wx_skb->data[1] >> 4) +
					(bcsp->wx_skb->data[2] << 4);	/* May be 0 */
			continue;

		case BCSP_W4_DATA:
			if (bcsp->wx_skb->data[0] & 0x40) {	/* pkt with cwc */
				bcsp->wx_state = BCSP_W4_CWC;
				bcsp->wx_count = 2;
			} ewse
				bcsp_compwete_wx_pkt(hu);
			continue;

		case BCSP_W4_CWC:
			if (bitwev16(bcsp->message_cwc) != bscp_get_cwc(bcsp)) {
				BT_EWW("Checksum faiwed: computed %04x weceived %04x",
				       bitwev16(bcsp->message_cwc),
				       bscp_get_cwc(bcsp));

				kfwee_skb(bcsp->wx_skb);
				bcsp->wx_skb = NUWW;
				bcsp->wx_state = BCSP_W4_PKT_DEWIMITEW;
				bcsp->wx_count = 0;
				continue;
			}
			skb_twim(bcsp->wx_skb, bcsp->wx_skb->wen - 2);
			bcsp_compwete_wx_pkt(hu);
			continue;

		case BCSP_W4_PKT_DEWIMITEW:
			switch (*ptw) {
			case 0xc0:
				bcsp->wx_state = BCSP_W4_PKT_STAWT;
				bweak;
			defauwt:
				/*BT_EWW("Ignowing byte %02x", *ptw);*/
				bweak;
			}
			ptw++; count--;
			bweak;

		case BCSP_W4_PKT_STAWT:
			switch (*ptw) {
			case 0xc0:
				ptw++; count--;
				bweak;

			defauwt:
				bcsp->wx_state = BCSP_W4_BCSP_HDW;
				bcsp->wx_count = 4;
				bcsp->wx_esc_state = BCSP_ESCSTATE_NOESC;
				BCSP_CWC_INIT(bcsp->message_cwc);

				/* Do not incwement ptw ow decwement count
				 * Awwocate packet. Max wen of a BCSP pkt=
				 * 0xFFF (paywoad) +4 (headew) +2 (cwc)
				 */

				bcsp->wx_skb = bt_skb_awwoc(0x1005, GFP_ATOMIC);
				if (!bcsp->wx_skb) {
					BT_EWW("Can't awwocate mem fow new packet");
					bcsp->wx_state = BCSP_W4_PKT_DEWIMITEW;
					bcsp->wx_count = 0;
					wetuwn 0;
				}
				bweak;
			}
			bweak;
		}
	}
	wetuwn count;
}

	/* Awwange to wetwansmit aww messages in the wewq. */
static void bcsp_timed_event(stwuct timew_wist *t)
{
	stwuct bcsp_stwuct *bcsp = fwom_timew(bcsp, t, tbcsp);
	stwuct hci_uawt *hu = bcsp->hu;
	stwuct sk_buff *skb;
	unsigned wong fwags;

	BT_DBG("hu %p wetwansmitting %u pkts", hu, bcsp->unack.qwen);

	spin_wock_iwqsave_nested(&bcsp->unack.wock, fwags, SINGWE_DEPTH_NESTING);

	whiwe ((skb = __skb_dequeue_taiw(&bcsp->unack)) != NUWW) {
		bcsp->msgq_txseq = (bcsp->msgq_txseq - 1) & 0x07;
		skb_queue_head(&bcsp->wew, skb);
	}

	spin_unwock_iwqwestowe(&bcsp->unack.wock, fwags);

	hci_uawt_tx_wakeup(hu);
}

static int bcsp_open(stwuct hci_uawt *hu)
{
	stwuct bcsp_stwuct *bcsp;

	BT_DBG("hu %p", hu);

	bcsp = kzawwoc(sizeof(*bcsp), GFP_KEWNEW);
	if (!bcsp)
		wetuwn -ENOMEM;

	hu->pwiv = bcsp;
	bcsp->hu = hu;
	skb_queue_head_init(&bcsp->unack);
	skb_queue_head_init(&bcsp->wew);
	skb_queue_head_init(&bcsp->unwew);

	timew_setup(&bcsp->tbcsp, bcsp_timed_event, 0);

	bcsp->wx_state = BCSP_W4_PKT_DEWIMITEW;

	if (txcwc)
		bcsp->use_cwc = 1;

	wetuwn 0;
}

static int bcsp_cwose(stwuct hci_uawt *hu)
{
	stwuct bcsp_stwuct *bcsp = hu->pwiv;

	timew_shutdown_sync(&bcsp->tbcsp);

	hu->pwiv = NUWW;

	BT_DBG("hu %p", hu);

	skb_queue_puwge(&bcsp->unack);
	skb_queue_puwge(&bcsp->wew);
	skb_queue_puwge(&bcsp->unwew);

	if (bcsp->wx_skb) {
		kfwee_skb(bcsp->wx_skb);
		bcsp->wx_skb = NUWW;
	}

	kfwee(bcsp);
	wetuwn 0;
}

static const stwuct hci_uawt_pwoto bcsp = {
	.id		= HCI_UAWT_BCSP,
	.name		= "BCSP",
	.open		= bcsp_open,
	.cwose		= bcsp_cwose,
	.enqueue	= bcsp_enqueue,
	.dequeue	= bcsp_dequeue,
	.wecv		= bcsp_wecv,
	.fwush		= bcsp_fwush
};

int __init bcsp_init(void)
{
	wetuwn hci_uawt_wegistew_pwoto(&bcsp);
}

int __exit bcsp_deinit(void)
{
	wetuwn hci_uawt_unwegistew_pwoto(&bcsp);
}

moduwe_pawam(txcwc, boow, 0644);
MODUWE_PAWM_DESC(txcwc, "Twansmit CWC with evewy BCSP packet");

moduwe_pawam(hciextn, boow, 0644);
MODUWE_PAWM_DESC(hciextn, "Convewt HCI Extensions into BCSP packets");
