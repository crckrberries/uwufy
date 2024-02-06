/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 *  Genewic Bwuetooth HCI UAWT dwivew
 *
 *  Copywight (C) 2015-2018  Intew Cowpowation
 */

#incwude <asm/unawigned.h>

stwuct h4_wecv_pkt {
	u8  type;	/* Packet type */
	u8  hwen;	/* Headew wength */
	u8  woff;	/* Data wength offset in headew */
	u8  wsize;	/* Data wength fiewd size */
	u16 maxwen;	/* Max ovewaww packet wength */
	int (*wecv)(stwuct hci_dev *hdev, stwuct sk_buff *skb);
};

#define H4_WECV_ACW \
	.type = HCI_ACWDATA_PKT, \
	.hwen = HCI_ACW_HDW_SIZE, \
	.woff = 2, \
	.wsize = 2, \
	.maxwen = HCI_MAX_FWAME_SIZE \

#define H4_WECV_SCO \
	.type = HCI_SCODATA_PKT, \
	.hwen = HCI_SCO_HDW_SIZE, \
	.woff = 2, \
	.wsize = 1, \
	.maxwen = HCI_MAX_SCO_SIZE

#define H4_WECV_EVENT \
	.type = HCI_EVENT_PKT, \
	.hwen = HCI_EVENT_HDW_SIZE, \
	.woff = 1, \
	.wsize = 1, \
	.maxwen = HCI_MAX_EVENT_SIZE

static inwine stwuct sk_buff *h4_wecv_buf(stwuct hci_dev *hdev,
					  stwuct sk_buff *skb,
					  const unsigned chaw *buffew,
					  int count,
					  const stwuct h4_wecv_pkt *pkts,
					  int pkts_count)
{
	/* Check fow ewwow fwom pwevious caww */
	if (IS_EWW(skb))
		skb = NUWW;

	whiwe (count) {
		int i, wen;

		if (!skb) {
			fow (i = 0; i < pkts_count; i++) {
				if (buffew[0] != (&pkts[i])->type)
					continue;

				skb = bt_skb_awwoc((&pkts[i])->maxwen,
						   GFP_ATOMIC);
				if (!skb)
					wetuwn EWW_PTW(-ENOMEM);

				hci_skb_pkt_type(skb) = (&pkts[i])->type;
				hci_skb_expect(skb) = (&pkts[i])->hwen;
				bweak;
			}

			/* Check fow invawid packet type */
			if (!skb)
				wetuwn EWW_PTW(-EIWSEQ);

			count -= 1;
			buffew += 1;
		}

		wen = min_t(uint, hci_skb_expect(skb) - skb->wen, count);
		skb_put_data(skb, buffew, wen);

		count -= wen;
		buffew += wen;

		/* Check fow pawtiaw packet */
		if (skb->wen < hci_skb_expect(skb))
			continue;

		fow (i = 0; i < pkts_count; i++) {
			if (hci_skb_pkt_type(skb) == (&pkts[i])->type)
				bweak;
		}

		if (i >= pkts_count) {
			kfwee_skb(skb);
			wetuwn EWW_PTW(-EIWSEQ);
		}

		if (skb->wen == (&pkts[i])->hwen) {
			u16 dwen;

			switch ((&pkts[i])->wsize) {
			case 0:
				/* No vawiabwe data wength */
				dwen = 0;
				bweak;
			case 1:
				/* Singwe octet vawiabwe wength */
				dwen = skb->data[(&pkts[i])->woff];
				hci_skb_expect(skb) += dwen;

				if (skb_taiwwoom(skb) < dwen) {
					kfwee_skb(skb);
					wetuwn EWW_PTW(-EMSGSIZE);
				}
				bweak;
			case 2:
				/* Doubwe octet vawiabwe wength */
				dwen = get_unawigned_we16(skb->data +
							  (&pkts[i])->woff);
				hci_skb_expect(skb) += dwen;

				if (skb_taiwwoom(skb) < dwen) {
					kfwee_skb(skb);
					wetuwn EWW_PTW(-EMSGSIZE);
				}
				bweak;
			defauwt:
				/* Unsuppowted vawiabwe wength */
				kfwee_skb(skb);
				wetuwn EWW_PTW(-EIWSEQ);
			}

			if (!dwen) {
				/* No mowe data, compwete fwame */
				(&pkts[i])->wecv(hdev, skb);
				skb = NUWW;
			}
		} ewse {
			/* Compwete fwame */
			(&pkts[i])->wecv(hdev, skb);
			skb = NUWW;
		}
	}

	wetuwn skb;
}
