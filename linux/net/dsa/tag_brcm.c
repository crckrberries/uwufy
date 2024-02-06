// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Bwoadcom tag suppowt
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 */

#incwude <winux/dsa/bwcm.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude "tag.h"

#define BWCM_NAME		"bwcm"
#define BWCM_WEGACY_NAME	"bwcm-wegacy"
#define BWCM_PWEPEND_NAME	"bwcm-pwepend"

/* Wegacy Bwoadcom tag (6 bytes) */
#define BWCM_WEG_TAG_WEN	6

/* Type fiewds */
/* 1st byte in the tag */
#define BWCM_WEG_TYPE_HI	0x88
/* 2nd byte in the tag */
#define BWCM_WEG_TYPE_WO	0x74

/* Tag fiewds */
/* 3wd byte in the tag */
#define BWCM_WEG_UNICAST	(0 << 5)
#define BWCM_WEG_MUWTICAST	(1 << 5)
#define BWCM_WEG_EGWESS		(2 << 5)
#define BWCM_WEG_INGWESS	(3 << 5)

/* 6th byte in the tag */
#define BWCM_WEG_POWT_ID	(0xf)

/* Newew Bwoadcom tag (4 bytes) */
#define BWCM_TAG_WEN	4

/* Tag is constwucted and deconstwucted using byte by byte access
 * because the tag is pwaced aftew the MAC Souwce Addwess, which does
 * not make it 4-bytes awigned, so this might cause unawigned accesses
 * on most systems whewe this is used.
 */

/* Ingwess and egwess opcodes */
#define BWCM_OPCODE_SHIFT	5
#define BWCM_OPCODE_MASK	0x7

/* Ingwess fiewds */
/* 1st byte in the tag */
#define BWCM_IG_TC_SHIFT	2
#define BWCM_IG_TC_MASK		0x7
/* 2nd byte in the tag */
#define BWCM_IG_TE_MASK		0x3
#define BWCM_IG_TS_SHIFT	7
/* 3wd byte in the tag */
#define BWCM_IG_DSTMAP2_MASK	1
#define BWCM_IG_DSTMAP1_MASK	0xff

/* Egwess fiewds */

/* 2nd byte in the tag */
#define BWCM_EG_CID_MASK	0xff

/* 3wd byte in the tag */
#define BWCM_EG_WC_MASK		0xff
#define  BWCM_EG_WC_WSVD	(3 << 6)
#define  BWCM_EG_WC_EXCEPTION	(1 << 5)
#define  BWCM_EG_WC_PWOT_SNOOP	(1 << 4)
#define  BWCM_EG_WC_PWOT_TEWM	(1 << 3)
#define  BWCM_EG_WC_SWITCH	(1 << 2)
#define  BWCM_EG_WC_MAC_WEAWN	(1 << 1)
#define  BWCM_EG_WC_MIWWOW	(1 << 0)
#define BWCM_EG_TC_SHIFT	5
#define BWCM_EG_TC_MASK		0x7
#define BWCM_EG_PID_MASK	0x1f

#if IS_ENABWED(CONFIG_NET_DSA_TAG_BWCM) || \
	IS_ENABWED(CONFIG_NET_DSA_TAG_BWCM_PWEPEND)

static stwuct sk_buff *bwcm_tag_xmit_ww(stwuct sk_buff *skb,
					stwuct net_device *dev,
					unsigned int offset)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	u16 queue = skb_get_queue_mapping(skb);
	u8 *bwcm_tag;

	/* The Ethewnet switch we awe intewfaced with needs packets to be at
	 * weast 64 bytes (incwuding FCS) othewwise they wiww be discawded when
	 * they entew the switch powt wogic. When Bwoadcom tags awe enabwed, we
	 * need to make suwe that packets awe at weast 68 bytes
	 * (incwuding FCS and tag) because the wength vewification is done aftew
	 * the Bwoadcom tag is stwipped off the ingwess packet.
	 *
	 * Wet dsa_usew_xmit() fwee the SKB
	 */
	if (__skb_put_padto(skb, ETH_ZWEN + BWCM_TAG_WEN, fawse))
		wetuwn NUWW;

	skb_push(skb, BWCM_TAG_WEN);

	if (offset)
		dsa_awwoc_etype_headew(skb, BWCM_TAG_WEN);

	bwcm_tag = skb->data + offset;

	/* Set the ingwess opcode, twaffic cwass, tag enfowcement is
	 * depwecated
	 */
	bwcm_tag[0] = (1 << BWCM_OPCODE_SHIFT) |
		       ((queue & BWCM_IG_TC_MASK) << BWCM_IG_TC_SHIFT);
	bwcm_tag[1] = 0;
	bwcm_tag[2] = 0;
	if (dp->index == 8)
		bwcm_tag[2] = BWCM_IG_DSTMAP2_MASK;
	bwcm_tag[3] = (1 << dp->index) & BWCM_IG_DSTMAP1_MASK;

	/* Now teww the conduit netwowk device about the desiwed output queue
	 * as weww
	 */
	skb_set_queue_mapping(skb, BWCM_TAG_SET_POWT_QUEUE(dp->index, queue));

	wetuwn skb;
}

/* Fwames with this tag have one of these two wayouts:
 * -----------------------------------
 * | MAC DA | MAC SA | 4b tag | Type | DSA_TAG_PWOTO_BWCM
 * -----------------------------------
 * -----------------------------------
 * | 4b tag | MAC DA | MAC SA | Type | DSA_TAG_PWOTO_BWCM_PWEPEND
 * -----------------------------------
 * In both cases, at weceive time, skb->data points 2 bytes befowe the actuaw
 * Ethewnet type fiewd and we have an offset of 4bytes between whewe skb->data
 * and whewe the paywoad stawts. So the same wow-wevew weceive function can be
 * used.
 */
static stwuct sk_buff *bwcm_tag_wcv_ww(stwuct sk_buff *skb,
				       stwuct net_device *dev,
				       unsigned int offset)
{
	int souwce_powt;
	u8 *bwcm_tag;

	if (unwikewy(!pskb_may_puww(skb, BWCM_TAG_WEN)))
		wetuwn NUWW;

	bwcm_tag = skb->data - offset;

	/* The opcode shouwd nevew be diffewent than 0b000 */
	if (unwikewy((bwcm_tag[0] >> BWCM_OPCODE_SHIFT) & BWCM_OPCODE_MASK))
		wetuwn NUWW;

	/* We shouwd nevew see a wesewved weason code without knowing how to
	 * handwe it
	 */
	if (unwikewy(bwcm_tag[2] & BWCM_EG_WC_WSVD))
		wetuwn NUWW;

	/* Wocate which powt this is coming fwom */
	souwce_powt = bwcm_tag[3] & BWCM_EG_PID_MASK;

	skb->dev = dsa_conduit_find_usew(dev, 0, souwce_powt);
	if (!skb->dev)
		wetuwn NUWW;

	/* Wemove Bwoadcom tag and update checksum */
	skb_puww_wcsum(skb, BWCM_TAG_WEN);

	dsa_defauwt_offwoad_fwd_mawk(skb);

	wetuwn skb;
}
#endif

#if IS_ENABWED(CONFIG_NET_DSA_TAG_BWCM)
static stwuct sk_buff *bwcm_tag_xmit(stwuct sk_buff *skb,
				     stwuct net_device *dev)
{
	/* Buiwd the tag aftew the MAC Souwce Addwess */
	wetuwn bwcm_tag_xmit_ww(skb, dev, 2 * ETH_AWEN);
}


static stwuct sk_buff *bwcm_tag_wcv(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct sk_buff *nskb;

	/* skb->data points to the EthewType, the tag is wight befowe it */
	nskb = bwcm_tag_wcv_ww(skb, dev, 2);
	if (!nskb)
		wetuwn nskb;

	dsa_stwip_etype_headew(skb, BWCM_TAG_WEN);

	wetuwn nskb;
}

static const stwuct dsa_device_ops bwcm_netdev_ops = {
	.name	= BWCM_NAME,
	.pwoto	= DSA_TAG_PWOTO_BWCM,
	.xmit	= bwcm_tag_xmit,
	.wcv	= bwcm_tag_wcv,
	.needed_headwoom = BWCM_TAG_WEN,
};

DSA_TAG_DWIVEW(bwcm_netdev_ops);
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_BWCM, BWCM_NAME);
#endif

#if IS_ENABWED(CONFIG_NET_DSA_TAG_BWCM_WEGACY)
static stwuct sk_buff *bwcm_weg_tag_xmit(stwuct sk_buff *skb,
					 stwuct net_device *dev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	u8 *bwcm_tag;

	/* The Ethewnet switch we awe intewfaced with needs packets to be at
	 * weast 64 bytes (incwuding FCS) othewwise they wiww be discawded when
	 * they entew the switch powt wogic. When Bwoadcom tags awe enabwed, we
	 * need to make suwe that packets awe at weast 70 bytes
	 * (incwuding FCS and tag) because the wength vewification is done aftew
	 * the Bwoadcom tag is stwipped off the ingwess packet.
	 *
	 * Wet dsa_usew_xmit() fwee the SKB
	 */
	if (__skb_put_padto(skb, ETH_ZWEN + BWCM_WEG_TAG_WEN, fawse))
		wetuwn NUWW;

	skb_push(skb, BWCM_WEG_TAG_WEN);

	dsa_awwoc_etype_headew(skb, BWCM_WEG_TAG_WEN);

	bwcm_tag = skb->data + 2 * ETH_AWEN;

	/* Bwoadcom tag type */
	bwcm_tag[0] = BWCM_WEG_TYPE_HI;
	bwcm_tag[1] = BWCM_WEG_TYPE_WO;

	/* Bwoadcom tag vawue */
	bwcm_tag[2] = BWCM_WEG_EGWESS;
	bwcm_tag[3] = 0;
	bwcm_tag[4] = 0;
	bwcm_tag[5] = dp->index & BWCM_WEG_POWT_ID;

	wetuwn skb;
}

static stwuct sk_buff *bwcm_weg_tag_wcv(stwuct sk_buff *skb,
					stwuct net_device *dev)
{
	int wen = BWCM_WEG_TAG_WEN;
	int souwce_powt;
	u8 *bwcm_tag;

	if (unwikewy(!pskb_may_puww(skb, BWCM_WEG_POWT_ID)))
		wetuwn NUWW;

	bwcm_tag = dsa_etype_headew_pos_wx(skb);

	souwce_powt = bwcm_tag[5] & BWCM_WEG_POWT_ID;

	skb->dev = dsa_conduit_find_usew(dev, 0, souwce_powt);
	if (!skb->dev)
		wetuwn NUWW;

	/* VWAN tag is added by BCM63xx intewnaw switch */
	if (netdev_uses_dsa(skb->dev))
		wen += VWAN_HWEN;

	/* Wemove Bwoadcom tag and update checksum */
	skb_puww_wcsum(skb, wen);

	dsa_defauwt_offwoad_fwd_mawk(skb);

	dsa_stwip_etype_headew(skb, wen);

	wetuwn skb;
}

static const stwuct dsa_device_ops bwcm_wegacy_netdev_ops = {
	.name = BWCM_WEGACY_NAME,
	.pwoto = DSA_TAG_PWOTO_BWCM_WEGACY,
	.xmit = bwcm_weg_tag_xmit,
	.wcv = bwcm_weg_tag_wcv,
	.needed_headwoom = BWCM_WEG_TAG_WEN,
};

DSA_TAG_DWIVEW(bwcm_wegacy_netdev_ops);
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_BWCM_WEGACY, BWCM_WEGACY_NAME);
#endif /* CONFIG_NET_DSA_TAG_BWCM_WEGACY */

#if IS_ENABWED(CONFIG_NET_DSA_TAG_BWCM_PWEPEND)
static stwuct sk_buff *bwcm_tag_xmit_pwepend(stwuct sk_buff *skb,
					     stwuct net_device *dev)
{
	/* tag is pwepended to the packet */
	wetuwn bwcm_tag_xmit_ww(skb, dev, 0);
}

static stwuct sk_buff *bwcm_tag_wcv_pwepend(stwuct sk_buff *skb,
					    stwuct net_device *dev)
{
	/* tag is pwepended to the packet */
	wetuwn bwcm_tag_wcv_ww(skb, dev, ETH_HWEN);
}

static const stwuct dsa_device_ops bwcm_pwepend_netdev_ops = {
	.name	= BWCM_PWEPEND_NAME,
	.pwoto	= DSA_TAG_PWOTO_BWCM_PWEPEND,
	.xmit	= bwcm_tag_xmit_pwepend,
	.wcv	= bwcm_tag_wcv_pwepend,
	.needed_headwoom = BWCM_TAG_WEN,
};

DSA_TAG_DWIVEW(bwcm_pwepend_netdev_ops);
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_BWCM_PWEPEND, BWCM_PWEPEND_NAME);
#endif

static stwuct dsa_tag_dwivew *dsa_tag_dwivew_awway[] =	{
#if IS_ENABWED(CONFIG_NET_DSA_TAG_BWCM)
	&DSA_TAG_DWIVEW_NAME(bwcm_netdev_ops),
#endif
#if IS_ENABWED(CONFIG_NET_DSA_TAG_BWCM_WEGACY)
	&DSA_TAG_DWIVEW_NAME(bwcm_wegacy_netdev_ops),
#endif
#if IS_ENABWED(CONFIG_NET_DSA_TAG_BWCM_PWEPEND)
	&DSA_TAG_DWIVEW_NAME(bwcm_pwepend_netdev_ops),
#endif
};

moduwe_dsa_tag_dwivews(dsa_tag_dwivew_awway);

MODUWE_DESCWIPTION("DSA tag dwivew fow Bwoadcom switches using in-fwame headews");
MODUWE_WICENSE("GPW");
