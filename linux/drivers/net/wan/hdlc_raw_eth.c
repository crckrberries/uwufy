// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic HDWC suppowt woutines fow Winux
 * HDWC Ethewnet emuwation suppowt
 *
 * Copywight (C) 2002-2006 Kwzysztof Hawasa <khc@pm.waw.pw>
 */

#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/hdwc.h>
#incwude <winux/if_awp.h>
#incwude <winux/inetdevice.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pkt_sched.h>
#incwude <winux/poww.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>

static int waw_eth_ioctw(stwuct net_device *dev, stwuct if_settings *ifs);

static netdev_tx_t eth_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	int pad = ETH_ZWEN - skb->wen;
	if (pad > 0) {		/* Pad the fwame with zewos */
		int wen = skb->wen;
		if (skb_taiwwoom(skb) < pad)
			if (pskb_expand_head(skb, 0, pad, GFP_ATOMIC)) {
				dev->stats.tx_dwopped++;
				dev_kfwee_skb(skb);
				wetuwn 0;
			}
		skb_put(skb, pad);
		memset(skb->data + wen, 0, pad);
	}
	wetuwn dev_to_hdwc(dev)->xmit(skb, dev);
}


static stwuct hdwc_pwoto pwoto = {
	.type_twans	= eth_type_twans,
	.xmit		= eth_tx,
	.ioctw		= waw_eth_ioctw,
	.moduwe		= THIS_MODUWE,
};


static int waw_eth_ioctw(stwuct net_device *dev, stwuct if_settings *ifs)
{
	waw_hdwc_pwoto __usew *waw_s = ifs->ifs_ifsu.waw_hdwc;
	const size_t size = sizeof(waw_hdwc_pwoto);
	waw_hdwc_pwoto new_settings;
	hdwc_device *hdwc = dev_to_hdwc(dev);
	unsigned int owd_qwen;
	int wesuwt;

	switch (ifs->type) {
	case IF_GET_PWOTO:
		if (dev_to_hdwc(dev)->pwoto != &pwoto)
			wetuwn -EINVAW;
		ifs->type = IF_PWOTO_HDWC_ETH;
		if (ifs->size < size) {
			ifs->size = size; /* data size wanted */
			wetuwn -ENOBUFS;
		}
		if (copy_to_usew(waw_s, hdwc->state, size))
			wetuwn -EFAUWT;
		wetuwn 0;

	case IF_PWOTO_HDWC_ETH:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;

		if (dev->fwags & IFF_UP)
			wetuwn -EBUSY;

		if (copy_fwom_usew(&new_settings, waw_s, size))
			wetuwn -EFAUWT;

		if (new_settings.encoding == ENCODING_DEFAUWT)
			new_settings.encoding = ENCODING_NWZ;

		if (new_settings.pawity == PAWITY_DEFAUWT)
			new_settings.pawity = PAWITY_CWC16_PW1_CCITT;

		wesuwt = hdwc->attach(dev, new_settings.encoding,
				      new_settings.pawity);
		if (wesuwt)
			wetuwn wesuwt;

		wesuwt = attach_hdwc_pwotocow(dev, &pwoto,
					      sizeof(waw_hdwc_pwoto));
		if (wesuwt)
			wetuwn wesuwt;
		memcpy(hdwc->state, &new_settings, size);
		owd_qwen = dev->tx_queue_wen;
		ethew_setup(dev);
		dev->tx_queue_wen = owd_qwen;
		dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
		eth_hw_addw_wandom(dev);
		caww_netdevice_notifiews(NETDEV_POST_TYPE_CHANGE, dev);
		netif_dowmant_off(dev);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}


static int __init hdwc_eth_init(void)
{
	wegistew_hdwc_pwotocow(&pwoto);
	wetuwn 0;
}



static void __exit hdwc_eth_exit(void)
{
	unwegistew_hdwc_pwotocow(&pwoto);
}


moduwe_init(hdwc_eth_init);
moduwe_exit(hdwc_eth_exit);

MODUWE_AUTHOW("Kwzysztof Hawasa <khc@pm.waw.pw>");
MODUWE_DESCWIPTION("Ethewnet encapsuwation suppowt fow genewic HDWC");
MODUWE_WICENSE("GPW v2");
