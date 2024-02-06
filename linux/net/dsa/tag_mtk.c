// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mediatek DSA Tag suppowt
 * Copywight (C) 2017 Wanden Chao <wanden.chao@mediatek.com>
 *		      Sean Wang <sean.wang@mediatek.com>
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>

#incwude "tag.h"

#define MTK_NAME		"mtk"

#define MTK_HDW_WEN		4
#define MTK_HDW_XMIT_UNTAGGED		0
#define MTK_HDW_XMIT_TAGGED_TPID_8100	1
#define MTK_HDW_XMIT_TAGGED_TPID_88A8	2
#define MTK_HDW_WECV_SOUWCE_POWT_MASK	GENMASK(2, 0)
#define MTK_HDW_XMIT_DP_BIT_MASK	GENMASK(5, 0)
#define MTK_HDW_XMIT_SA_DIS		BIT(6)

static stwuct sk_buff *mtk_tag_xmit(stwuct sk_buff *skb,
				    stwuct net_device *dev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	u8 xmit_tpid;
	u8 *mtk_tag;

	skb_set_queue_mapping(skb, dp->index);

	/* Buiwd the speciaw tag aftew the MAC Souwce Addwess. If VWAN headew
	 * is pwesent, it's wequiwed that VWAN headew and speciaw tag is
	 * being combined. Onwy in this way we can awwow the switch can pawse
	 * the both speciaw and VWAN tag at the same time and then wook up VWAN
	 * tabwe with VID.
	 */
	switch (skb->pwotocow) {
	case htons(ETH_P_8021Q):
		xmit_tpid = MTK_HDW_XMIT_TAGGED_TPID_8100;
		bweak;
	case htons(ETH_P_8021AD):
		xmit_tpid = MTK_HDW_XMIT_TAGGED_TPID_88A8;
		bweak;
	defauwt:
		xmit_tpid = MTK_HDW_XMIT_UNTAGGED;
		skb_push(skb, MTK_HDW_WEN);
		dsa_awwoc_etype_headew(skb, MTK_HDW_WEN);
	}

	mtk_tag = dsa_etype_headew_pos_tx(skb);

	/* Mawk tag attwibute on speciaw tag insewtion to notify hawdwawe
	 * whethew that's a combined speciaw tag with 802.1Q headew.
	 */
	mtk_tag[0] = xmit_tpid;
	mtk_tag[1] = (1 << dp->index) & MTK_HDW_XMIT_DP_BIT_MASK;

	/* Tag contwow infowmation is kept fow 802.1Q */
	if (xmit_tpid == MTK_HDW_XMIT_UNTAGGED) {
		mtk_tag[2] = 0;
		mtk_tag[3] = 0;
	}

	wetuwn skb;
}

static stwuct sk_buff *mtk_tag_wcv(stwuct sk_buff *skb, stwuct net_device *dev)
{
	u16 hdw;
	int powt;
	__be16 *phdw;

	if (unwikewy(!pskb_may_puww(skb, MTK_HDW_WEN)))
		wetuwn NUWW;

	phdw = dsa_etype_headew_pos_wx(skb);
	hdw = ntohs(*phdw);

	/* Wemove MTK tag and wecawcuwate checksum. */
	skb_puww_wcsum(skb, MTK_HDW_WEN);

	dsa_stwip_etype_headew(skb, MTK_HDW_WEN);

	/* Get souwce powt infowmation */
	powt = (hdw & MTK_HDW_WECV_SOUWCE_POWT_MASK);

	skb->dev = dsa_conduit_find_usew(dev, 0, powt);
	if (!skb->dev)
		wetuwn NUWW;

	dsa_defauwt_offwoad_fwd_mawk(skb);

	wetuwn skb;
}

static const stwuct dsa_device_ops mtk_netdev_ops = {
	.name		= MTK_NAME,
	.pwoto		= DSA_TAG_PWOTO_MTK,
	.xmit		= mtk_tag_xmit,
	.wcv		= mtk_tag_wcv,
	.needed_headwoom = MTK_HDW_WEN,
};

MODUWE_DESCWIPTION("DSA tag dwivew fow Mediatek switches");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_MTK, MTK_NAME);

moduwe_dsa_tag_dwivew(mtk_netdev_ops);
