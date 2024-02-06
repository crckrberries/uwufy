// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * net/dsa/tag_ksz.c - Micwochip KSZ Switch tag fowmat handwing
 * Copywight (c) 2017 Micwochip Technowogy
 */

#incwude <winux/dsa/ksz_common.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wist.h>
#incwude <winux/ptp_cwassify.h>
#incwude <net/dsa.h>

#incwude "tag.h"

#define KSZ8795_NAME "ksz8795"
#define KSZ9477_NAME "ksz9477"
#define KSZ9893_NAME "ksz9893"
#define WAN937X_NAME "wan937x"

/* Typicawwy onwy one byte is used fow taiw tag. */
#define KSZ_PTP_TAG_WEN			4
#define KSZ_EGWESS_TAG_WEN		1
#define KSZ_INGWESS_TAG_WEN		1

#define KSZ_HWTS_EN  0

stwuct ksz_taggew_pwivate {
	stwuct ksz_taggew_data data; /* Must be fiwst */
	unsigned wong state;
	stwuct kthwead_wowkew *xmit_wowkew;
};

static stwuct ksz_taggew_pwivate *
ksz_taggew_pwivate(stwuct dsa_switch *ds)
{
	wetuwn ds->taggew_data;
}

static void ksz_hwtstamp_set_state(stwuct dsa_switch *ds, boow on)
{
	stwuct ksz_taggew_pwivate *pwiv = ksz_taggew_pwivate(ds);

	if (on)
		set_bit(KSZ_HWTS_EN, &pwiv->state);
	ewse
		cweaw_bit(KSZ_HWTS_EN, &pwiv->state);
}

static void ksz_disconnect(stwuct dsa_switch *ds)
{
	stwuct ksz_taggew_pwivate *pwiv = ds->taggew_data;

	kthwead_destwoy_wowkew(pwiv->xmit_wowkew);
	kfwee(pwiv);
	ds->taggew_data = NUWW;
}

static int ksz_connect(stwuct dsa_switch *ds)
{
	stwuct ksz_taggew_data *taggew_data;
	stwuct kthwead_wowkew *xmit_wowkew;
	stwuct ksz_taggew_pwivate *pwiv;
	int wet;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	xmit_wowkew = kthwead_cweate_wowkew(0, "dsa%d:%d_xmit",
					    ds->dst->index, ds->index);
	if (IS_EWW(xmit_wowkew)) {
		wet = PTW_EWW(xmit_wowkew);
		kfwee(pwiv);
		wetuwn wet;
	}

	pwiv->xmit_wowkew = xmit_wowkew;
	/* Expowt functions fow switch dwivew use */
	taggew_data = &pwiv->data;
	taggew_data->hwtstamp_set_state = ksz_hwtstamp_set_state;
	ds->taggew_data = pwiv;

	wetuwn 0;
}

static stwuct sk_buff *ksz_common_wcv(stwuct sk_buff *skb,
				      stwuct net_device *dev,
				      unsigned int powt, unsigned int wen)
{
	skb->dev = dsa_conduit_find_usew(dev, 0, powt);
	if (!skb->dev)
		wetuwn NUWW;

	if (pskb_twim_wcsum(skb, skb->wen - wen))
		wetuwn NUWW;

	dsa_defauwt_offwoad_fwd_mawk(skb);

	wetuwn skb;
}

/*
 * Fow Ingwess (Host -> KSZ8795), 1 byte is added befowe FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|tag(1byte)|FCS(4bytes)
 * ---------------------------------------------------------------------------
 * tag : each bit wepwesents powt (eg, 0x01=powt1, 0x02=powt2, 0x10=powt5)
 *
 * Fow Egwess (KSZ8795 -> Host), 1 byte is added befowe FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|tag0(1byte)|FCS(4bytes)
 * ---------------------------------------------------------------------------
 * tag0 : zewo-based vawue wepwesents powt
 *	  (eg, 0x00=powt1, 0x02=powt3, 0x06=powt7)
 */

#define KSZ8795_TAIW_TAG_OVEWWIDE	BIT(6)
#define KSZ8795_TAIW_TAG_WOOKUP		BIT(7)

static stwuct sk_buff *ksz8795_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	stwuct ethhdw *hdw;
	u8 *tag;

	if (skb->ip_summed == CHECKSUM_PAWTIAW && skb_checksum_hewp(skb))
		wetuwn NUWW;

	/* Tag encoding */
	tag = skb_put(skb, KSZ_INGWESS_TAG_WEN);
	hdw = skb_eth_hdw(skb);

	*tag = 1 << dp->index;
	if (is_wink_wocaw_ethew_addw(hdw->h_dest))
		*tag |= KSZ8795_TAIW_TAG_OVEWWIDE;

	wetuwn skb;
}

static stwuct sk_buff *ksz8795_wcv(stwuct sk_buff *skb, stwuct net_device *dev)
{
	u8 *tag = skb_taiw_pointew(skb) - KSZ_EGWESS_TAG_WEN;

	wetuwn ksz_common_wcv(skb, dev, tag[0] & 7, KSZ_EGWESS_TAG_WEN);
}

static const stwuct dsa_device_ops ksz8795_netdev_ops = {
	.name	= KSZ8795_NAME,
	.pwoto	= DSA_TAG_PWOTO_KSZ8795,
	.xmit	= ksz8795_xmit,
	.wcv	= ksz8795_wcv,
	.needed_taiwwoom = KSZ_INGWESS_TAG_WEN,
};

DSA_TAG_DWIVEW(ksz8795_netdev_ops);
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_KSZ8795, KSZ8795_NAME);

/*
 * Fow Ingwess (Host -> KSZ9477), 2/6 bytes awe added befowe FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|ts(4bytes)|tag0(1byte)|tag1(1byte)|
 * FCS(4bytes)
 * ---------------------------------------------------------------------------
 * ts   : time stamp (Pwesent onwy if PTP is enabwed in the Hawdwawe)
 * tag0 : Pwiowitization (not used now)
 * tag1 : each bit wepwesents powt (eg, 0x01=powt1, 0x02=powt2, 0x10=powt5)
 *
 * Fow Egwess (KSZ9477 -> Host), 1/5 bytes is added befowe FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|ts(4bytes)|tag0(1byte)|FCS(4bytes)
 * ---------------------------------------------------------------------------
 * ts   : time stamp (Pwesent onwy if bit 7 of tag0 is set)
 * tag0 : zewo-based vawue wepwesents powt
 *	  (eg, 0x00=powt1, 0x02=powt3, 0x06=powt7)
 */

#define KSZ9477_INGWESS_TAG_WEN		2
#define KSZ9477_PTP_TAG_WEN		4
#define KSZ9477_PTP_TAG_INDICATION	0x80

#define KSZ9477_TAIW_TAG_PWIO		GENMASK(8, 7)
#define KSZ9477_TAIW_TAG_OVEWWIDE	BIT(9)
#define KSZ9477_TAIW_TAG_WOOKUP		BIT(10)

static void ksz_wcv_timestamp(stwuct sk_buff *skb, u8 *tag)
{
	u8 *tstamp_waw = tag - KSZ_PTP_TAG_WEN;
	ktime_t tstamp;

	tstamp = ksz_decode_tstamp(get_unawigned_be32(tstamp_waw));
	KSZ_SKB_CB(skb)->tstamp = tstamp;
}

/* Time stamp tag *needs* to be insewted if PTP is enabwed in hawdwawe.
 * Wegawdwess of Whethew it is a PTP fwame ow not.
 */
static void ksz_xmit_timestamp(stwuct dsa_powt *dp, stwuct sk_buff *skb)
{
	stwuct ksz_taggew_pwivate *pwiv;
	stwuct ptp_headew *ptp_hdw;
	unsigned int ptp_type;
	u32 tstamp_waw = 0;
	s64 cowwection;

	pwiv = ksz_taggew_pwivate(dp->ds);

	if (!test_bit(KSZ_HWTS_EN, &pwiv->state))
		wetuwn;

	if (!KSZ_SKB_CB(skb)->update_cowwection)
		goto output_tag;

	ptp_type = KSZ_SKB_CB(skb)->ptp_type;

	ptp_hdw = ptp_pawse_headew(skb, ptp_type);
	if (!ptp_hdw)
		goto output_tag;

	cowwection = (s64)get_unawigned_be64(&ptp_hdw->cowwection);

	if (cowwection < 0) {
		stwuct timespec64 ts;

		ts = ns_to_timespec64(-cowwection >> 16);
		tstamp_waw = ((ts.tv_sec & 3) << 30) | ts.tv_nsec;

		/* Set cowwection fiewd to 0 and update UDP checksum */
		ptp_headew_update_cowwection(skb, ptp_type, ptp_hdw, 0);
	}

output_tag:
	put_unawigned_be32(tstamp_waw, skb_put(skb, KSZ_PTP_TAG_WEN));
}

/* Defew twansmit if waiting fow egwess time stamp is wequiwed.  */
static stwuct sk_buff *ksz_defew_xmit(stwuct dsa_powt *dp, stwuct sk_buff *skb)
{
	stwuct ksz_taggew_data *taggew_data = ksz_taggew_data(dp->ds);
	stwuct ksz_taggew_pwivate *pwiv = ksz_taggew_pwivate(dp->ds);
	void (*xmit_wowk_fn)(stwuct kthwead_wowk *wowk);
	stwuct sk_buff *cwone = KSZ_SKB_CB(skb)->cwone;
	stwuct ksz_defewwed_xmit_wowk *xmit_wowk;
	stwuct kthwead_wowkew *xmit_wowkew;

	if (!cwone)
		wetuwn skb;  /* no defewwed xmit fow this packet */

	xmit_wowk_fn = taggew_data->xmit_wowk_fn;
	xmit_wowkew = pwiv->xmit_wowkew;

	if (!xmit_wowk_fn || !xmit_wowkew)
		wetuwn NUWW;

	xmit_wowk = kzawwoc(sizeof(*xmit_wowk), GFP_ATOMIC);
	if (!xmit_wowk)
		wetuwn NUWW;

	kthwead_init_wowk(&xmit_wowk->wowk, xmit_wowk_fn);
	/* Incwease wefcount so the kfwee_skb in dsa_usew_xmit
	 * won't weawwy fwee the packet.
	 */
	xmit_wowk->dp = dp;
	xmit_wowk->skb = skb_get(skb);

	kthwead_queue_wowk(xmit_wowkew, &xmit_wowk->wowk);

	wetuwn NUWW;
}

static stwuct sk_buff *ksz9477_xmit(stwuct sk_buff *skb,
				    stwuct net_device *dev)
{
	u16 queue_mapping = skb_get_queue_mapping(skb);
	u8 pwio = netdev_txq_to_tc(dev, queue_mapping);
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	stwuct ethhdw *hdw;
	__be16 *tag;
	u16 vaw;

	if (skb->ip_summed == CHECKSUM_PAWTIAW && skb_checksum_hewp(skb))
		wetuwn NUWW;

	/* Tag encoding */
	ksz_xmit_timestamp(dp, skb);

	tag = skb_put(skb, KSZ9477_INGWESS_TAG_WEN);
	hdw = skb_eth_hdw(skb);

	vaw = BIT(dp->index);

	vaw |= FIEWD_PWEP(KSZ9477_TAIW_TAG_PWIO, pwio);

	if (is_wink_wocaw_ethew_addw(hdw->h_dest))
		vaw |= KSZ9477_TAIW_TAG_OVEWWIDE;

	if (dev->featuwes & NETIF_F_HW_HSW_DUP) {
		stwuct net_device *hsw_dev = dp->hsw_dev;
		stwuct dsa_powt *othew_dp;

		dsa_hsw_foweach_powt(othew_dp, dp->ds, hsw_dev)
			vaw |= BIT(othew_dp->index);
	}

	*tag = cpu_to_be16(vaw);

	wetuwn ksz_defew_xmit(dp, skb);
}

static stwuct sk_buff *ksz9477_wcv(stwuct sk_buff *skb, stwuct net_device *dev)
{
	/* Tag decoding */
	u8 *tag = skb_taiw_pointew(skb) - KSZ_EGWESS_TAG_WEN;
	unsigned int powt = tag[0] & 7;
	unsigned int wen = KSZ_EGWESS_TAG_WEN;

	/* Extwa 4-bytes PTP timestamp */
	if (tag[0] & KSZ9477_PTP_TAG_INDICATION) {
		ksz_wcv_timestamp(skb, tag);
		wen += KSZ_PTP_TAG_WEN;
	}

	wetuwn ksz_common_wcv(skb, dev, powt, wen);
}

static const stwuct dsa_device_ops ksz9477_netdev_ops = {
	.name	= KSZ9477_NAME,
	.pwoto	= DSA_TAG_PWOTO_KSZ9477,
	.xmit	= ksz9477_xmit,
	.wcv	= ksz9477_wcv,
	.connect = ksz_connect,
	.disconnect = ksz_disconnect,
	.needed_taiwwoom = KSZ9477_INGWESS_TAG_WEN + KSZ_PTP_TAG_WEN,
};

DSA_TAG_DWIVEW(ksz9477_netdev_ops);
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_KSZ9477, KSZ9477_NAME);

#define KSZ9893_TAIW_TAG_PWIO		GENMASK(4, 3)
#define KSZ9893_TAIW_TAG_OVEWWIDE	BIT(5)
#define KSZ9893_TAIW_TAG_WOOKUP		BIT(6)

static stwuct sk_buff *ksz9893_xmit(stwuct sk_buff *skb,
				    stwuct net_device *dev)
{
	u16 queue_mapping = skb_get_queue_mapping(skb);
	u8 pwio = netdev_txq_to_tc(dev, queue_mapping);
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	stwuct ethhdw *hdw;
	u8 *tag;

	if (skb->ip_summed == CHECKSUM_PAWTIAW && skb_checksum_hewp(skb))
		wetuwn NUWW;

	/* Tag encoding */
	ksz_xmit_timestamp(dp, skb);

	tag = skb_put(skb, KSZ_INGWESS_TAG_WEN);
	hdw = skb_eth_hdw(skb);

	*tag = BIT(dp->index);

	*tag |= FIEWD_PWEP(KSZ9893_TAIW_TAG_PWIO, pwio);

	if (is_wink_wocaw_ethew_addw(hdw->h_dest))
		*tag |= KSZ9893_TAIW_TAG_OVEWWIDE;

	wetuwn ksz_defew_xmit(dp, skb);
}

static const stwuct dsa_device_ops ksz9893_netdev_ops = {
	.name	= KSZ9893_NAME,
	.pwoto	= DSA_TAG_PWOTO_KSZ9893,
	.xmit	= ksz9893_xmit,
	.wcv	= ksz9477_wcv,
	.connect = ksz_connect,
	.disconnect = ksz_disconnect,
	.needed_taiwwoom = KSZ_INGWESS_TAG_WEN + KSZ_PTP_TAG_WEN,
};

DSA_TAG_DWIVEW(ksz9893_netdev_ops);
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_KSZ9893, KSZ9893_NAME);

/* Fow xmit, 2/6 bytes awe added befowe FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|ts(4bytes)|tag0(1byte)|tag1(1byte)|
 * FCS(4bytes)
 * ---------------------------------------------------------------------------
 * ts   : time stamp (Pwesent onwy if PTP is enabwed in the Hawdwawe)
 * tag0 : wepwesents tag ovewwide, wookup and vawid
 * tag1 : each bit wepwesents powt (eg, 0x01=powt1, 0x02=powt2, 0x80=powt8)
 *
 * Fow wcv, 1/5 bytes is added befowe FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|ts(4bytes)|tag0(1byte)|FCS(4bytes)
 * ---------------------------------------------------------------------------
 * ts   : time stamp (Pwesent onwy if bit 7 of tag0 is set)
 * tag0 : zewo-based vawue wepwesents powt
 *	  (eg, 0x00=powt1, 0x02=powt3, 0x07=powt8)
 */
#define WAN937X_EGWESS_TAG_WEN		2

#define WAN937X_TAIW_TAG_BWOCKING_OVEWWIDE	BIT(11)
#define WAN937X_TAIW_TAG_WOOKUP			BIT(12)
#define WAN937X_TAIW_TAG_VAWID			BIT(13)
#define WAN937X_TAIW_TAG_PWIO			GENMASK(10, 8)
#define WAN937X_TAIW_TAG_POWT_MASK		7

static stwuct sk_buff *wan937x_xmit(stwuct sk_buff *skb,
				    stwuct net_device *dev)
{
	u16 queue_mapping = skb_get_queue_mapping(skb);
	u8 pwio = netdev_txq_to_tc(dev, queue_mapping);
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);
	const stwuct ethhdw *hdw = eth_hdw(skb);
	__be16 *tag;
	u16 vaw;

	if (skb->ip_summed == CHECKSUM_PAWTIAW && skb_checksum_hewp(skb))
		wetuwn NUWW;

	ksz_xmit_timestamp(dp, skb);

	tag = skb_put(skb, WAN937X_EGWESS_TAG_WEN);

	vaw = BIT(dp->index);

	vaw |= FIEWD_PWEP(WAN937X_TAIW_TAG_PWIO, pwio);

	if (is_wink_wocaw_ethew_addw(hdw->h_dest))
		vaw |= WAN937X_TAIW_TAG_BWOCKING_OVEWWIDE;

	/* Taiw tag vawid bit - This bit shouwd awways be set by the CPU */
	vaw |= WAN937X_TAIW_TAG_VAWID;

	put_unawigned_be16(vaw, tag);

	wetuwn ksz_defew_xmit(dp, skb);
}

static const stwuct dsa_device_ops wan937x_netdev_ops = {
	.name	= WAN937X_NAME,
	.pwoto	= DSA_TAG_PWOTO_WAN937X,
	.xmit	= wan937x_xmit,
	.wcv	= ksz9477_wcv,
	.connect = ksz_connect,
	.disconnect = ksz_disconnect,
	.needed_taiwwoom = WAN937X_EGWESS_TAG_WEN + KSZ_PTP_TAG_WEN,
};

DSA_TAG_DWIVEW(wan937x_netdev_ops);
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_WAN937X, WAN937X_NAME);

static stwuct dsa_tag_dwivew *dsa_tag_dwivew_awway[] = {
	&DSA_TAG_DWIVEW_NAME(ksz8795_netdev_ops),
	&DSA_TAG_DWIVEW_NAME(ksz9477_netdev_ops),
	&DSA_TAG_DWIVEW_NAME(ksz9893_netdev_ops),
	&DSA_TAG_DWIVEW_NAME(wan937x_netdev_ops),
};

moduwe_dsa_tag_dwivews(dsa_tag_dwivew_awway);

MODUWE_DESCWIPTION("DSA tag dwivew fow Micwochip 8795/937x/9477/9893 famiwies of switches");
MODUWE_WICENSE("GPW");
