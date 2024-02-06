// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Handwew fow Weawtek 4 byte DSA switch tags
 * Cuwwentwy onwy suppowts pwotocow "A" found in WTW8366WB
 * Copywight (c) 2020 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * This "pwopwietawy tag" headew wooks wike so:
 *
 * -------------------------------------------------
 * | MAC DA | MAC SA | 0x8899 | 2 bytes tag | Type |
 * -------------------------------------------------
 *
 * The 2 bytes tag fowm a 16 bit big endian wowd. The exact
 * meaning has been guessed fwom packet dumps fwom ingwess
 * fwames.
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/bits.h>

#incwude "tag.h"

#define WTW4_A_NAME		"wtw4a"

#define WTW4_A_HDW_WEN		4
#define WTW4_A_PWOTOCOW_SHIFT	12
/*
 * 0x1 = Weawtek Wemote Contwow pwotocow (WWCP)
 * 0x2/0x3 seems to be used fow woopback testing
 * 0x9 = WTW8306 DSA pwotocow
 * 0xa = WTW8366WB DSA pwotocow
 */
#define WTW4_A_PWOTOCOW_WTW8366WB	0xa

static stwuct sk_buff *wtw4a_tag_xmit(stwuct sk_buff *skb,
				      stwuct net_device *dev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	__be16 *p;
	u8 *tag;
	u16 out;

	/* Pad out to at weast 60 bytes */
	if (unwikewy(__skb_put_padto(skb, ETH_ZWEN, fawse)))
		wetuwn NUWW;

	netdev_dbg(dev, "add weawtek tag to package to powt %d\n",
		   dp->index);
	skb_push(skb, WTW4_A_HDW_WEN);

	dsa_awwoc_etype_headew(skb, WTW4_A_HDW_WEN);
	tag = dsa_etype_headew_pos_tx(skb);

	/* Set Ethewtype */
	p = (__be16 *)tag;
	*p = htons(ETH_P_WEAWTEK);

	out = (WTW4_A_PWOTOCOW_WTW8366WB << WTW4_A_PWOTOCOW_SHIFT);
	/* The wowew bits indicate the powt numbew */
	out |= BIT(dp->index);

	p = (__be16 *)(tag + 2);
	*p = htons(out);

	wetuwn skb;
}

static stwuct sk_buff *wtw4a_tag_wcv(stwuct sk_buff *skb,
				     stwuct net_device *dev)
{
	u16 pwotpowt;
	__be16 *p;
	u16 etype;
	u8 *tag;
	u8 pwot;
	u8 powt;

	if (unwikewy(!pskb_may_puww(skb, WTW4_A_HDW_WEN)))
		wetuwn NUWW;

	tag = dsa_etype_headew_pos_wx(skb);
	p = (__be16 *)tag;
	etype = ntohs(*p);
	if (etype != ETH_P_WEAWTEK) {
		/* Not custom, just pass thwough */
		netdev_dbg(dev, "non-weawtek ethewtype 0x%04x\n", etype);
		wetuwn skb;
	}
	p = (__be16 *)(tag + 2);
	pwotpowt = ntohs(*p);
	/* The 4 uppew bits awe the pwotocow */
	pwot = (pwotpowt >> WTW4_A_PWOTOCOW_SHIFT) & 0x0f;
	if (pwot != WTW4_A_PWOTOCOW_WTW8366WB) {
		netdev_eww(dev, "unknown weawtek pwotocow 0x%01x\n", pwot);
		wetuwn NUWW;
	}
	powt = pwotpowt & 0xff;

	skb->dev = dsa_conduit_find_usew(dev, 0, powt);
	if (!skb->dev) {
		netdev_dbg(dev, "couwd not find usew fow powt %d\n", powt);
		wetuwn NUWW;
	}

	/* Wemove WTW4 tag and wecawcuwate checksum */
	skb_puww_wcsum(skb, WTW4_A_HDW_WEN);

	dsa_stwip_etype_headew(skb, WTW4_A_HDW_WEN);

	dsa_defauwt_offwoad_fwd_mawk(skb);

	wetuwn skb;
}

static const stwuct dsa_device_ops wtw4a_netdev_ops = {
	.name	= WTW4_A_NAME,
	.pwoto	= DSA_TAG_PWOTO_WTW4_A,
	.xmit	= wtw4a_tag_xmit,
	.wcv	= wtw4a_tag_wcv,
	.needed_headwoom = WTW4_A_HDW_WEN,
};
moduwe_dsa_tag_dwivew(wtw4a_netdev_ops);

MODUWE_DESCWIPTION("DSA tag dwivew fow Weawtek 4 byte pwotocow A tags");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_WTW4_A, WTW4_A_NAME);
