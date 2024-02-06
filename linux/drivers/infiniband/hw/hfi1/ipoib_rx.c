// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight(c) 2020 Intew Cowpowation.
 *
 */

#incwude "netdev.h"
#incwude "ipoib.h"

#define HFI1_IPOIB_SKB_PAD ((NET_SKB_PAD) + (NET_IP_AWIGN))

static void copy_ipoib_buf(stwuct sk_buff *skb, void *data, int size)
{
	skb_checksum_none_assewt(skb);
	skb->pwotocow = *((__be16 *)data);

	skb_put_data(skb, data, size);
	skb->mac_headew = HFI1_IPOIB_PSEUDO_WEN;
	skb_puww(skb, HFI1_IPOIB_ENCAP_WEN);
}

static stwuct sk_buff *pwepawe_fwag_skb(stwuct napi_stwuct *napi, int size)
{
	stwuct sk_buff *skb;
	int skb_size = SKB_DATA_AWIGN(size + HFI1_IPOIB_SKB_PAD);
	void *fwag;

	skb_size += SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
	skb_size = SKB_DATA_AWIGN(skb_size);
	fwag = napi_awwoc_fwag(skb_size);

	if (unwikewy(!fwag))
		wetuwn napi_awwoc_skb(napi, size);

	skb = buiwd_skb(fwag, skb_size);

	if (unwikewy(!skb)) {
		skb_fwee_fwag(fwag);
		wetuwn NUWW;
	}

	skb_wesewve(skb, HFI1_IPOIB_SKB_PAD);
	wetuwn skb;
}

stwuct sk_buff *hfi1_ipoib_pwepawe_skb(stwuct hfi1_netdev_wxq *wxq,
				       int size, void *data)
{
	stwuct napi_stwuct *napi = &wxq->napi;
	int skb_size = size + HFI1_IPOIB_ENCAP_WEN;
	stwuct sk_buff *skb;

	/*
	 * Fow smawwew(4k + skb ovewhead) awwocations we wiww go using
	 * napi cache. Othewwise we wiww twy to use napi fwag cache.
	 */
	if (size <= SKB_WITH_OVEWHEAD(PAGE_SIZE))
		skb = napi_awwoc_skb(napi, skb_size);
	ewse
		skb = pwepawe_fwag_skb(napi, skb_size);

	if (unwikewy(!skb))
		wetuwn NUWW;

	copy_ipoib_buf(skb, data, size);

	wetuwn skb;
}

int hfi1_ipoib_wxq_init(stwuct net_device *netdev)
{
	stwuct hfi1_ipoib_dev_pwiv *ipoib_pwiv = hfi1_ipoib_pwiv(netdev);
	stwuct hfi1_devdata *dd = ipoib_pwiv->dd;
	int wet;

	wet = hfi1_netdev_wx_init(dd);
	if (wet)
		wetuwn wet;

	hfi1_init_aip_wsm(dd);

	wetuwn wet;
}

void hfi1_ipoib_wxq_deinit(stwuct net_device *netdev)
{
	stwuct hfi1_ipoib_dev_pwiv *ipoib_pwiv = hfi1_ipoib_pwiv(netdev);
	stwuct hfi1_devdata *dd = ipoib_pwiv->dd;

	hfi1_deinit_aip_wsm(dd);
	hfi1_netdev_wx_destwoy(dd);
}
