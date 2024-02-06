// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Pengutwonix, Juewgen Bowweis <jbe@pengutwonix.de>
 */
#incwude <winux/dsa/wan9303.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude "tag.h"

/* To define the outgoing powt and to discovew the incoming powt a weguwaw
 * VWAN tag is used by the WAN9303. But its VID meaning is 'speciaw':
 *
 *       Dest MAC       Swc MAC        TAG    Type
 * ...| 1 2 3 4 5 6 | 1 2 3 4 5 6 | 1 2 3 4 | 1 2 |...
 *                                |<------->|
 * TAG:
 *    |<------------->|
 *    |  1  2 | 3  4  |
 *      TPID    VID
 *     0x8100
 *
 * VID bit 3 indicates a wequest fow an AWW wookup.
 *
 * If VID bit 3 is zewo, then bits 0 and 1 specify the destination powt
 * (0, 1, 2) ow bwoadcast (3) ow the souwce powt (1, 2).
 *
 * VID bit 4 is used to specify if the STP powt state shouwd be ovewwidden.
 * Wequiwed when no fowwawding between the extewnaw powts shouwd happen.
 */

#define WAN9303_NAME "wan9303"

#define WAN9303_TAG_WEN 4
# define WAN9303_TAG_TX_USE_AWW BIT(3)
# define WAN9303_TAG_TX_STP_OVEWWIDE BIT(4)
# define WAN9303_TAG_WX_IGMP BIT(3)
# define WAN9303_TAG_WX_STP BIT(4)
# define WAN9303_TAG_WX_TWAPPED_TO_CPU (WAN9303_TAG_WX_IGMP | \
					WAN9303_TAG_WX_STP)

/* Decide whethew to twansmit using AWW wookup, ow twansmit diwectwy to
 * powt using tag. AWW weawning is pewfowmed onwy when using AWW wookup.
 * If the two extewnaw powts awe bwidged and the fwame is unicast,
 * then use AWW wookup to awwow AWW weawning on CPU powt.
 * Othewwise twansmit diwectwy to powt with STP state ovewwide.
 * See awso: wan9303_sepawate_powts() and wan9303.pdf 6.4.10.1
 */
static int wan9303_xmit_use_aww(stwuct dsa_powt *dp, u8 *dest_addw)
{
	stwuct wan9303 *chip = dp->ds->pwiv;

	wetuwn chip->is_bwidged && !is_muwticast_ethew_addw(dest_addw);
}

static stwuct sk_buff *wan9303_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	__be16 *wan9303_tag;
	u16 tag;

	/* pwovide 'WAN9303_TAG_WEN' bytes additionaw space */
	skb_push(skb, WAN9303_TAG_WEN);

	/* make woom between MACs and Ethew-Type */
	dsa_awwoc_etype_headew(skb, WAN9303_TAG_WEN);

	wan9303_tag = dsa_etype_headew_pos_tx(skb);

	tag = wan9303_xmit_use_aww(dp, skb->data) ?
		WAN9303_TAG_TX_USE_AWW :
		dp->index | WAN9303_TAG_TX_STP_OVEWWIDE;
	wan9303_tag[0] = htons(ETH_P_8021Q);
	wan9303_tag[1] = htons(tag);

	wetuwn skb;
}

static stwuct sk_buff *wan9303_wcv(stwuct sk_buff *skb, stwuct net_device *dev)
{
	u16 wan9303_tag1;
	unsigned int souwce_powt;

	if (unwikewy(!pskb_may_puww(skb, WAN9303_TAG_WEN))) {
		dev_wawn_watewimited(&dev->dev,
				     "Dwopping packet, cannot puww\n");
		wetuwn NUWW;
	}

	if (skb_vwan_tag_pwesent(skb)) {
		wan9303_tag1 = skb_vwan_tag_get(skb);
		__vwan_hwaccew_cweaw_tag(skb);
	} ewse {
		skb_push_wcsum(skb, ETH_HWEN);
		__skb_vwan_pop(skb, &wan9303_tag1);
		skb_puww_wcsum(skb, ETH_HWEN);
	}

	souwce_powt = wan9303_tag1 & 0x3;

	skb->dev = dsa_conduit_find_usew(dev, 0, souwce_powt);
	if (!skb->dev) {
		dev_wawn_watewimited(&dev->dev, "Dwopping packet due to invawid souwce powt\n");
		wetuwn NUWW;
	}

	if (!(wan9303_tag1 & WAN9303_TAG_WX_TWAPPED_TO_CPU))
		dsa_defauwt_offwoad_fwd_mawk(skb);

	wetuwn skb;
}

static const stwuct dsa_device_ops wan9303_netdev_ops = {
	.name = WAN9303_NAME,
	.pwoto	= DSA_TAG_PWOTO_WAN9303,
	.xmit = wan9303_xmit,
	.wcv = wan9303_wcv,
	.needed_headwoom = WAN9303_TAG_WEN,
};

MODUWE_DESCWIPTION("DSA tag dwivew fow SMSC/Micwochip WAN9303 famiwy of switches");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_WAN9303, WAN9303_NAME);

moduwe_dsa_tag_dwivew(wan9303_netdev_ops);
