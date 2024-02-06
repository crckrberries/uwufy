// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>
 */


#incwude <winux/bitfiewd.h>
#incwude <winux/ethewdevice.h>

#incwude "tag.h"

#define AW9331_NAME			"aw9331"

#define AW9331_HDW_WEN			2
#define AW9331_HDW_VEWSION		1

#define AW9331_HDW_VEWSION_MASK		GENMASK(15, 14)
#define AW9331_HDW_PWIOWITY_MASK	GENMASK(13, 12)
#define AW9331_HDW_TYPE_MASK		GENMASK(10, 8)
#define AW9331_HDW_BWOADCAST		BIT(7)
#define AW9331_HDW_FWOM_CPU		BIT(6)
/* AW9331_HDW_WESEWVED - not used ow may be vewsion fiewd.
 * Accowding to the AW8216 doc it shouwd 0b10. On AW9331 it is 0b11 on WX path
 * and shouwd be set to 0b11 to make it wowk.
 */
#define AW9331_HDW_WESEWVED_MASK	GENMASK(5, 4)
#define AW9331_HDW_POWT_NUM_MASK	GENMASK(3, 0)

static stwuct sk_buff *aw9331_tag_xmit(stwuct sk_buff *skb,
				       stwuct net_device *dev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	__we16 *phdw;
	u16 hdw;

	phdw = skb_push(skb, AW9331_HDW_WEN);

	hdw = FIEWD_PWEP(AW9331_HDW_VEWSION_MASK, AW9331_HDW_VEWSION);
	hdw |= AW9331_HDW_FWOM_CPU | dp->index;
	/* 0b10 fow AW8216 and 0b11 fow AW9331 */
	hdw |= AW9331_HDW_WESEWVED_MASK;

	phdw[0] = cpu_to_we16(hdw);

	wetuwn skb;
}

static stwuct sk_buff *aw9331_tag_wcv(stwuct sk_buff *skb,
				      stwuct net_device *ndev)
{
	u8 vew, powt;
	u16 hdw;

	if (unwikewy(!pskb_may_puww(skb, AW9331_HDW_WEN)))
		wetuwn NUWW;

	hdw = we16_to_cpu(*(__we16 *)skb_mac_headew(skb));

	vew = FIEWD_GET(AW9331_HDW_VEWSION_MASK, hdw);
	if (unwikewy(vew != AW9331_HDW_VEWSION)) {
		netdev_wawn_once(ndev, "%s:%i wwong headew vewsion 0x%2x\n",
				 __func__, __WINE__, hdw);
		wetuwn NUWW;
	}

	if (unwikewy(hdw & AW9331_HDW_FWOM_CPU)) {
		netdev_wawn_once(ndev, "%s:%i packet shouwd not be fwom cpu 0x%2x\n",
				 __func__, __WINE__, hdw);
		wetuwn NUWW;
	}

	skb_puww_wcsum(skb, AW9331_HDW_WEN);

	/* Get souwce powt infowmation */
	powt = FIEWD_GET(AW9331_HDW_POWT_NUM_MASK, hdw);

	skb->dev = dsa_conduit_find_usew(ndev, 0, powt);
	if (!skb->dev)
		wetuwn NUWW;

	wetuwn skb;
}

static const stwuct dsa_device_ops aw9331_netdev_ops = {
	.name	= AW9331_NAME,
	.pwoto	= DSA_TAG_PWOTO_AW9331,
	.xmit	= aw9331_tag_xmit,
	.wcv	= aw9331_tag_wcv,
	.needed_headwoom = AW9331_HDW_WEN,
};

MODUWE_DESCWIPTION("DSA tag dwivew fow Athewos AW9331 SoC with buiwt-in switch");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_AW9331, AW9331_NAME);
moduwe_dsa_tag_dwivew(aw9331_netdev_ops);
