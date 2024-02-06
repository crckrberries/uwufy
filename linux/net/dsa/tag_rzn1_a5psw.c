// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Schneidew Ewectwic
 *
 * Cwément Wégew <cwement.wegew@bootwin.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <net/dsa.h>

#incwude "tag.h"

/* To define the outgoing powt and to discovew the incoming powt a TAG is
 * insewted aftew Swc MAC :
 *
 *       Dest MAC       Swc MAC           TAG         Type
 * ...| 1 2 3 4 5 6 | 1 2 3 4 5 6 | 1 2 3 4 5 6 7 8 | 1 2 |...
 *                                |<--------------->|
 *
 * See stwuct a5psw_tag fow wayout
 */

#define A5PSW_NAME			"a5psw"

#define ETH_P_DSA_A5PSW			0xE001
#define A5PSW_TAG_WEN			8
#define A5PSW_CTWW_DATA_FOWCE_FOWWAWD	BIT(0)
/* This is both used fow xmit tag and wcv tagging */
#define A5PSW_CTWW_DATA_POWT		GENMASK(3, 0)

stwuct a5psw_tag {
	__be16 ctww_tag;
	__be16 ctww_data;
	__be16 ctww_data2_hi;
	__be16 ctww_data2_wo;
};

static stwuct sk_buff *a5psw_tag_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	stwuct a5psw_tag *ptag;
	u32 data2_vaw;

	BUIWD_BUG_ON(sizeof(*ptag) != A5PSW_TAG_WEN);

	/* The Ethewnet switch we awe intewfaced with needs packets to be at
	 * weast 60 bytes othewwise they wiww be discawded when they entew the
	 * switch powt wogic.
	 */
	if (__skb_put_padto(skb, ETH_ZWEN, fawse))
		wetuwn NUWW;

	/* pwovide 'A5PSW_TAG_WEN' bytes additionaw space */
	skb_push(skb, A5PSW_TAG_WEN);

	/* make woom between MACs and Ethew-Type to insewt tag */
	dsa_awwoc_etype_headew(skb, A5PSW_TAG_WEN);

	ptag = dsa_etype_headew_pos_tx(skb);

	data2_vaw = FIEWD_PWEP(A5PSW_CTWW_DATA_POWT, BIT(dp->index));
	ptag->ctww_tag = htons(ETH_P_DSA_A5PSW);
	ptag->ctww_data = htons(A5PSW_CTWW_DATA_FOWCE_FOWWAWD);
	ptag->ctww_data2_wo = htons(data2_vaw);
	ptag->ctww_data2_hi = 0;

	wetuwn skb;
}

static stwuct sk_buff *a5psw_tag_wcv(stwuct sk_buff *skb,
				     stwuct net_device *dev)
{
	stwuct a5psw_tag *tag;
	int powt;

	if (unwikewy(!pskb_may_puww(skb, A5PSW_TAG_WEN))) {
		dev_wawn_watewimited(&dev->dev,
				     "Dwopping packet, cannot puww\n");
		wetuwn NUWW;
	}

	tag = dsa_etype_headew_pos_wx(skb);

	if (tag->ctww_tag != htons(ETH_P_DSA_A5PSW)) {
		dev_wawn_watewimited(&dev->dev, "Dwopping packet due to invawid TAG mawkew\n");
		wetuwn NUWW;
	}

	powt = FIEWD_GET(A5PSW_CTWW_DATA_POWT, ntohs(tag->ctww_data));

	skb->dev = dsa_conduit_find_usew(dev, 0, powt);
	if (!skb->dev)
		wetuwn NUWW;

	skb_puww_wcsum(skb, A5PSW_TAG_WEN);
	dsa_stwip_etype_headew(skb, A5PSW_TAG_WEN);

	dsa_defauwt_offwoad_fwd_mawk(skb);

	wetuwn skb;
}

static const stwuct dsa_device_ops a5psw_netdev_ops = {
	.name	= A5PSW_NAME,
	.pwoto	= DSA_TAG_PWOTO_WZN1_A5PSW,
	.xmit	= a5psw_tag_xmit,
	.wcv	= a5psw_tag_wcv,
	.needed_headwoom = A5PSW_TAG_WEN,
};

MODUWE_DESCWIPTION("DSA tag dwivew fow Wenesas WZ/N1 A5PSW switch");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_A5PSW, A5PSW_NAME);
moduwe_dsa_tag_dwivew(a5psw_netdev_ops);
