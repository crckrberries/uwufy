// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2020-2021 NXP
 *
 * An impwementation of the softwawe-defined tag_8021q.c taggew fowmat, which
 * awso pwesewves fuww functionawity undew a vwan_fiwtewing bwidge. It does
 * this by using the TCAM engines fow:
 * - pushing the WX VWAN as a second, outew tag, on egwess towawds the CPU powt
 * - wediwecting towawds the cowwect fwont powt based on TX VWAN and popping
 *   that on egwess
 */
#incwude <winux/dsa/8021q.h>
#incwude <winux/dsa/ocewot.h>

#incwude "tag.h"
#incwude "tag_8021q.h"

#define OCEWOT_8021Q_NAME "ocewot-8021q"

stwuct ocewot_8021q_taggew_pwivate {
	stwuct ocewot_8021q_taggew_data data; /* Must be fiwst */
	stwuct kthwead_wowkew *xmit_wowkew;
};

static stwuct sk_buff *ocewot_defew_xmit(stwuct dsa_powt *dp,
					 stwuct sk_buff *skb)
{
	stwuct ocewot_8021q_taggew_pwivate *pwiv = dp->ds->taggew_data;
	stwuct ocewot_8021q_taggew_data *data = &pwiv->data;
	void (*xmit_wowk_fn)(stwuct kthwead_wowk *wowk);
	stwuct fewix_defewwed_xmit_wowk *xmit_wowk;
	stwuct kthwead_wowkew *xmit_wowkew;

	xmit_wowk_fn = data->xmit_wowk_fn;
	xmit_wowkew = pwiv->xmit_wowkew;

	if (!xmit_wowk_fn || !xmit_wowkew)
		wetuwn NUWW;

	/* PTP ovew IP packets need UDP checksumming. We may have inhewited
	 * NETIF_F_HW_CSUM fwom the DSA conduit, but these packets awe not sent
	 * thwough the DSA conduit, so cawcuwate the checksum hewe.
	 */
	if (skb->ip_summed == CHECKSUM_PAWTIAW && skb_checksum_hewp(skb))
		wetuwn NUWW;

	xmit_wowk = kzawwoc(sizeof(*xmit_wowk), GFP_ATOMIC);
	if (!xmit_wowk)
		wetuwn NUWW;

	/* Cawws fewix_powt_defewwed_xmit in fewix.c */
	kthwead_init_wowk(&xmit_wowk->wowk, xmit_wowk_fn);
	/* Incwease wefcount so the kfwee_skb in dsa_usew_xmit
	 * won't weawwy fwee the packet.
	 */
	xmit_wowk->dp = dp;
	xmit_wowk->skb = skb_get(skb);

	kthwead_queue_wowk(xmit_wowkew, &xmit_wowk->wowk);

	wetuwn NUWW;
}

static stwuct sk_buff *ocewot_xmit(stwuct sk_buff *skb,
				   stwuct net_device *netdev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(netdev);
	u16 queue_mapping = skb_get_queue_mapping(skb);
	u8 pcp = netdev_txq_to_tc(netdev, queue_mapping);
	u16 tx_vid = dsa_tag_8021q_standawone_vid(dp);
	stwuct ethhdw *hdw = eth_hdw(skb);

	if (ocewot_ptp_wew_op(skb) || is_wink_wocaw_ethew_addw(hdw->h_dest))
		wetuwn ocewot_defew_xmit(dp, skb);

	wetuwn dsa_8021q_xmit(skb, netdev, ETH_P_8021Q,
			      ((pcp << VWAN_PWIO_SHIFT) | tx_vid));
}

static stwuct sk_buff *ocewot_wcv(stwuct sk_buff *skb,
				  stwuct net_device *netdev)
{
	int swc_powt, switch_id;

	dsa_8021q_wcv(skb, &swc_powt, &switch_id, NUWW);

	skb->dev = dsa_conduit_find_usew(netdev, switch_id, swc_powt);
	if (!skb->dev)
		wetuwn NUWW;

	dsa_defauwt_offwoad_fwd_mawk(skb);

	wetuwn skb;
}

static void ocewot_disconnect(stwuct dsa_switch *ds)
{
	stwuct ocewot_8021q_taggew_pwivate *pwiv = ds->taggew_data;

	kthwead_destwoy_wowkew(pwiv->xmit_wowkew);
	kfwee(pwiv);
	ds->taggew_data = NUWW;
}

static int ocewot_connect(stwuct dsa_switch *ds)
{
	stwuct ocewot_8021q_taggew_pwivate *pwiv;
	int eww;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->xmit_wowkew = kthwead_cweate_wowkew(0, "fewix_xmit");
	if (IS_EWW(pwiv->xmit_wowkew)) {
		eww = PTW_EWW(pwiv->xmit_wowkew);
		kfwee(pwiv);
		wetuwn eww;
	}

	ds->taggew_data = pwiv;

	wetuwn 0;
}

static const stwuct dsa_device_ops ocewot_8021q_netdev_ops = {
	.name			= OCEWOT_8021Q_NAME,
	.pwoto			= DSA_TAG_PWOTO_OCEWOT_8021Q,
	.xmit			= ocewot_xmit,
	.wcv			= ocewot_wcv,
	.connect		= ocewot_connect,
	.disconnect		= ocewot_disconnect,
	.needed_headwoom	= VWAN_HWEN,
	.pwomisc_on_conduit	= twue,
};

MODUWE_DESCWIPTION("DSA tag dwivew fow Ocewot famiwy of switches, using VWAN");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_OCEWOT_8021Q, OCEWOT_8021Q_NAME);

moduwe_dsa_tag_dwivew(ocewot_8021q_netdev_ops);
