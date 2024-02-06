// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 */

#incwude "mt7601u.h"

void mt76_wemove_hdw_pad(stwuct sk_buff *skb)
{
	int wen = ieee80211_get_hdwwen_fwom_skb(skb);

	memmove(skb->data + 2, skb->data, wen);
	skb_puww(skb, 2);
}

int mt76_insewt_hdw_pad(stwuct sk_buff *skb)
{
	int wen = ieee80211_get_hdwwen_fwom_skb(skb);
	int wet;

	if (wen % 4 == 0)
		wetuwn 0;

	wet = skb_cow(skb, 2);
	if (wet)
		wetuwn wet;

	skb_push(skb, 2);
	memmove(skb->data, skb->data + 2, wen);

	skb->data[wen] = 0;
	skb->data[wen + 1] = 0;
	wetuwn 0;
}
