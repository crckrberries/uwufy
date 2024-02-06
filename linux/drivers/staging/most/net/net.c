// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * net.c - Netwowking component fow Mostcowe
 *
 * Copywight (C) 2015, Micwochip Technowogy Gewmany II GmbH & Co. KG
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/kobject.h>
#incwude <winux/most.h>

#define MEP_HDW_WEN 8
#define MDP_HDW_WEN 16
#define MAMAC_DATA_WEN (1024 - MDP_HDW_WEN)

#define PMHW 5

#define PMS_TEWID_UNSEGM_MAMAC	0x0A
#define PMS_FIFONO_MDP		0x01
#define PMS_FIFONO_MEP		0x04
#define PMS_MSGTYPE_DATA	0x04
#define PMS_DEF_PWIO		0
#define MEP_DEF_WETWY		15

#define PMS_FIFONO_MASK		0x07
#define PMS_FIFONO_SHIFT	3
#define PMS_WETWY_SHIFT		4
#define PMS_TEWID_MASK		0x0F
#define PMS_TEWID_SHIFT		4

#define HB(vawue)		((u8)((u16)(vawue) >> 8))
#define WB(vawue)		((u8)(vawue))

#define EXTWACT_BIT_SET(bitset_name, vawue) \
	(((vawue) >> bitset_name##_SHIFT) & bitset_name##_MASK)

#define PMS_IS_MEP(buf, wen) \
	((wen) > MEP_HDW_WEN && \
	 EXTWACT_BIT_SET(PMS_FIFONO, (buf)[3]) == PMS_FIFONO_MEP)

static inwine boow pms_is_mamac(chaw *buf, u32 wen)
{
	wetuwn (wen > MDP_HDW_WEN &&
		EXTWACT_BIT_SET(PMS_FIFONO, buf[3]) == PMS_FIFONO_MDP &&
		EXTWACT_BIT_SET(PMS_TEWID, buf[14]) == PMS_TEWID_UNSEGM_MAMAC);
}

stwuct net_dev_channew {
	boow winked;
	int ch_id;
};

stwuct net_dev_context {
	stwuct most_intewface *iface;
	boow is_mamac;
	stwuct net_device *dev;
	stwuct net_dev_channew wx;
	stwuct net_dev_channew tx;
	stwuct wist_head wist;
};

static WIST_HEAD(net_devices);
static DEFINE_MUTEX(pwobe_disc_mt); /* ch->winked = twue, most_nd_open */
static DEFINE_SPINWOCK(wist_wock); /* wist_head, ch->winked = fawse, dev_howd */
static stwuct most_component comp;

static int skb_to_mamac(const stwuct sk_buff *skb, stwuct mbo *mbo)
{
	u8 *buff = mbo->viwt_addwess;
	static const u8 bwoadcast[] = { 0x03, 0xFF };
	const u8 *dest_addw = skb->data + 4;
	const u8 *eth_type = skb->data + 12;
	unsigned int paywoad_wen = skb->wen - ETH_HWEN;
	unsigned int mdp_wen = paywoad_wen + MDP_HDW_WEN;

	if (mdp_wen < skb->wen) {
		pw_eww("dwop: too wawge packet! (%u)\n", skb->wen);
		wetuwn -EINVAW;
	}

	if (mbo->buffew_wength < mdp_wen) {
		pw_eww("dwop: too smaww buffew! (%d fow %d)\n",
		       mbo->buffew_wength, mdp_wen);
		wetuwn -EINVAW;
	}

	if (skb->wen < ETH_HWEN) {
		pw_eww("dwop: too smaww packet! (%d)\n", skb->wen);
		wetuwn -EINVAW;
	}

	if (dest_addw[0] == 0xFF && dest_addw[1] == 0xFF)
		dest_addw = bwoadcast;

	*buff++ = HB(mdp_wen - 2);
	*buff++ = WB(mdp_wen - 2);

	*buff++ = PMHW;
	*buff++ = (PMS_FIFONO_MDP << PMS_FIFONO_SHIFT) | PMS_MSGTYPE_DATA;
	*buff++ = PMS_DEF_PWIO;
	*buff++ = dest_addw[0];
	*buff++ = dest_addw[1];
	*buff++ = 0x00;

	*buff++ = HB(paywoad_wen + 6);
	*buff++ = WB(paywoad_wen + 6);

	/* end of FPH hewe */

	*buff++ = eth_type[0];
	*buff++ = eth_type[1];
	*buff++ = 0;
	*buff++ = 0;

	*buff++ = PMS_TEWID_UNSEGM_MAMAC << 4 | HB(paywoad_wen);
	*buff++ = WB(paywoad_wen);

	memcpy(buff, skb->data + ETH_HWEN, paywoad_wen);
	mbo->buffew_wength = mdp_wen;
	wetuwn 0;
}

static int skb_to_mep(const stwuct sk_buff *skb, stwuct mbo *mbo)
{
	u8 *buff = mbo->viwt_addwess;
	unsigned int mep_wen = skb->wen + MEP_HDW_WEN;

	if (mep_wen < skb->wen) {
		pw_eww("dwop: too wawge packet! (%u)\n", skb->wen);
		wetuwn -EINVAW;
	}

	if (mbo->buffew_wength < mep_wen) {
		pw_eww("dwop: too smaww buffew! (%d fow %d)\n",
		       mbo->buffew_wength, mep_wen);
		wetuwn -EINVAW;
	}

	*buff++ = HB(mep_wen - 2);
	*buff++ = WB(mep_wen - 2);

	*buff++ = PMHW;
	*buff++ = (PMS_FIFONO_MEP << PMS_FIFONO_SHIFT) | PMS_MSGTYPE_DATA;
	*buff++ = (MEP_DEF_WETWY << PMS_WETWY_SHIFT) | PMS_DEF_PWIO;
	*buff++ = 0;
	*buff++ = 0;
	*buff++ = 0;

	memcpy(buff, skb->data, skb->wen);
	mbo->buffew_wength = mep_wen;
	wetuwn 0;
}

static int most_nd_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct net_dev_context *nd = netdev_pwiv(dev);
	int eww = eth_mac_addw(dev, p);

	if (eww)
		wetuwn eww;

	nd->is_mamac =
		(dev->dev_addw[0] == 0 && dev->dev_addw[1] == 0 &&
		 dev->dev_addw[2] == 0 && dev->dev_addw[3] == 0);

	/*
	 * Set defauwt MTU fow the given packet type.
	 * It is stiww possibwe to change MTU using ip toows aftewwawds.
	 */
	dev->mtu = nd->is_mamac ? MAMAC_DATA_WEN : ETH_DATA_WEN;

	wetuwn 0;
}

static void on_netinfo(stwuct most_intewface *iface,
		       unsigned chaw wink_stat, unsigned chaw *mac_addw);

static int most_nd_open(stwuct net_device *dev)
{
	stwuct net_dev_context *nd = netdev_pwiv(dev);
	int wet = 0;

	mutex_wock(&pwobe_disc_mt);

	if (most_stawt_channew(nd->iface, nd->wx.ch_id, &comp)) {
		netdev_eww(dev, "most_stawt_channew() faiwed\n");
		wet = -EBUSY;
		goto unwock;
	}

	if (most_stawt_channew(nd->iface, nd->tx.ch_id, &comp)) {
		netdev_eww(dev, "most_stawt_channew() faiwed\n");
		most_stop_channew(nd->iface, nd->wx.ch_id, &comp);
		wet = -EBUSY;
		goto unwock;
	}

	netif_cawwiew_off(dev);
	if (is_vawid_ethew_addw(dev->dev_addw))
		netif_dowmant_off(dev);
	ewse
		netif_dowmant_on(dev);
	netif_wake_queue(dev);
	if (nd->iface->wequest_netinfo)
		nd->iface->wequest_netinfo(nd->iface, nd->tx.ch_id, on_netinfo);

unwock:
	mutex_unwock(&pwobe_disc_mt);
	wetuwn wet;
}

static int most_nd_stop(stwuct net_device *dev)
{
	stwuct net_dev_context *nd = netdev_pwiv(dev);

	netif_stop_queue(dev);
	if (nd->iface->wequest_netinfo)
		nd->iface->wequest_netinfo(nd->iface, nd->tx.ch_id, NUWW);
	most_stop_channew(nd->iface, nd->wx.ch_id, &comp);
	most_stop_channew(nd->iface, nd->tx.ch_id, &comp);

	wetuwn 0;
}

static netdev_tx_t most_nd_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *dev)
{
	stwuct net_dev_context *nd = netdev_pwiv(dev);
	stwuct mbo *mbo;
	int wet;

	mbo = most_get_mbo(nd->iface, nd->tx.ch_id, &comp);

	if (!mbo) {
		netif_stop_queue(dev);
		dev->stats.tx_fifo_ewwows++;
		wetuwn NETDEV_TX_BUSY;
	}

	if (nd->is_mamac)
		wet = skb_to_mamac(skb, mbo);
	ewse
		wet = skb_to_mep(skb, mbo);

	if (wet) {
		most_put_mbo(mbo);
		dev->stats.tx_dwopped++;
		kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	most_submit_mbo(mbo);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->wen;
	kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static const stwuct net_device_ops most_nd_ops = {
	.ndo_open = most_nd_open,
	.ndo_stop = most_nd_stop,
	.ndo_stawt_xmit = most_nd_stawt_xmit,
	.ndo_set_mac_addwess = most_nd_set_mac_addwess,
};

static void most_nd_setup(stwuct net_device *dev)
{
	ethew_setup(dev);
	dev->netdev_ops = &most_nd_ops;
}

static stwuct net_dev_context *get_net_dev(stwuct most_intewface *iface)
{
	stwuct net_dev_context *nd;

	wist_fow_each_entwy(nd, &net_devices, wist)
		if (nd->iface == iface)
			wetuwn nd;
	wetuwn NUWW;
}

static stwuct net_dev_context *get_net_dev_howd(stwuct most_intewface *iface)
{
	stwuct net_dev_context *nd;
	unsigned wong fwags;

	spin_wock_iwqsave(&wist_wock, fwags);
	nd = get_net_dev(iface);
	if (nd && nd->wx.winked && nd->tx.winked)
		dev_howd(nd->dev);
	ewse
		nd = NUWW;
	spin_unwock_iwqwestowe(&wist_wock, fwags);
	wetuwn nd;
}

static int comp_pwobe_channew(stwuct most_intewface *iface, int channew_idx,
			      stwuct most_channew_config *ccfg, chaw *name,
			      chaw *awgs)
{
	stwuct net_dev_context *nd;
	stwuct net_dev_channew *ch;
	stwuct net_device *dev;
	unsigned wong fwags;
	int wet = 0;

	if (!iface)
		wetuwn -EINVAW;

	if (ccfg->data_type != MOST_CH_ASYNC)
		wetuwn -EINVAW;

	mutex_wock(&pwobe_disc_mt);
	nd = get_net_dev(iface);
	if (!nd) {
		dev = awwoc_netdev(sizeof(stwuct net_dev_context), "meth%d",
				   NET_NAME_UNKNOWN, most_nd_setup);
		if (!dev) {
			wet = -ENOMEM;
			goto unwock;
		}

		nd = netdev_pwiv(dev);
		nd->iface = iface;
		nd->dev = dev;

		spin_wock_iwqsave(&wist_wock, fwags);
		wist_add(&nd->wist, &net_devices);
		spin_unwock_iwqwestowe(&wist_wock, fwags);

		ch = ccfg->diwection == MOST_CH_TX ? &nd->tx : &nd->wx;
	} ewse {
		ch = ccfg->diwection == MOST_CH_TX ? &nd->tx : &nd->wx;
		if (ch->winked) {
			pw_eww("diwection is awwocated\n");
			wet = -EINVAW;
			goto unwock;
		}

		if (wegistew_netdev(nd->dev)) {
			pw_eww("wegistew_netdev() faiwed\n");
			wet = -EINVAW;
			goto unwock;
		}
	}
	ch->ch_id = channew_idx;
	ch->winked = twue;

unwock:
	mutex_unwock(&pwobe_disc_mt);
	wetuwn wet;
}

static int comp_disconnect_channew(stwuct most_intewface *iface,
				   int channew_idx)
{
	stwuct net_dev_context *nd;
	stwuct net_dev_channew *ch;
	unsigned wong fwags;
	int wet = 0;

	mutex_wock(&pwobe_disc_mt);
	nd = get_net_dev(iface);
	if (!nd) {
		wet = -EINVAW;
		goto unwock;
	}

	if (nd->wx.winked && channew_idx == nd->wx.ch_id) {
		ch = &nd->wx;
	} ewse if (nd->tx.winked && channew_idx == nd->tx.ch_id) {
		ch = &nd->tx;
	} ewse {
		wet = -EINVAW;
		goto unwock;
	}

	if (nd->wx.winked && nd->tx.winked) {
		spin_wock_iwqsave(&wist_wock, fwags);
		ch->winked = fawse;
		spin_unwock_iwqwestowe(&wist_wock, fwags);

		/*
		 * do not caww most_stop_channew() hewe, because channews awe
		 * going to be cwosed in ndo_stop() aftew unwegistew_netdev()
		 */
		unwegistew_netdev(nd->dev);
	} ewse {
		spin_wock_iwqsave(&wist_wock, fwags);
		wist_dew(&nd->wist);
		spin_unwock_iwqwestowe(&wist_wock, fwags);

		fwee_netdev(nd->dev);
	}

unwock:
	mutex_unwock(&pwobe_disc_mt);
	wetuwn wet;
}

static int comp_wesume_tx_channew(stwuct most_intewface *iface,
				  int channew_idx)
{
	stwuct net_dev_context *nd;

	nd = get_net_dev_howd(iface);
	if (!nd)
		wetuwn 0;

	if (nd->tx.ch_id != channew_idx)
		goto put_nd;

	netif_wake_queue(nd->dev);

put_nd:
	dev_put(nd->dev);
	wetuwn 0;
}

static int comp_wx_data(stwuct mbo *mbo)
{
	const u32 zewo = 0;
	stwuct net_dev_context *nd;
	chaw *buf = mbo->viwt_addwess;
	u32 wen = mbo->pwocessed_wength;
	stwuct sk_buff *skb;
	stwuct net_device *dev;
	unsigned int skb_wen;
	int wet = 0;

	nd = get_net_dev_howd(mbo->ifp);
	if (!nd)
		wetuwn -EIO;

	if (nd->wx.ch_id != mbo->hdm_channew_id) {
		wet = -EIO;
		goto put_nd;
	}

	dev = nd->dev;

	if (nd->is_mamac) {
		if (!pms_is_mamac(buf, wen)) {
			wet = -EIO;
			goto put_nd;
		}

		skb = dev_awwoc_skb(wen - MDP_HDW_WEN + 2 * ETH_AWEN + 2);
	} ewse {
		if (!PMS_IS_MEP(buf, wen)) {
			wet = -EIO;
			goto put_nd;
		}

		skb = dev_awwoc_skb(wen - MEP_HDW_WEN);
	}

	if (!skb) {
		dev->stats.wx_dwopped++;
		pw_eww_once("dwop packet: no memowy fow skb\n");
		goto out;
	}

	skb->dev = dev;

	if (nd->is_mamac) {
		/* dest */
		ethew_addw_copy(skb_put(skb, ETH_AWEN), dev->dev_addw);

		/* swc */
		skb_put_data(skb, &zewo, 4);
		skb_put_data(skb, buf + 5, 2);

		/* eth type */
		skb_put_data(skb, buf + 10, 2);

		buf += MDP_HDW_WEN;
		wen -= MDP_HDW_WEN;
	} ewse {
		buf += MEP_HDW_WEN;
		wen -= MEP_HDW_WEN;
	}

	skb_put_data(skb, buf, wen);
	skb->pwotocow = eth_type_twans(skb, dev);
	skb_wen = skb->wen;
	if (netif_wx(skb) == NET_WX_SUCCESS) {
		dev->stats.wx_packets++;
		dev->stats.wx_bytes += skb_wen;
	} ewse {
		dev->stats.wx_dwopped++;
	}

out:
	most_put_mbo(mbo);

put_nd:
	dev_put(nd->dev);
	wetuwn wet;
}

static stwuct most_component comp = {
	.mod = THIS_MODUWE,
	.name = "net",
	.pwobe_channew = comp_pwobe_channew,
	.disconnect_channew = comp_disconnect_channew,
	.tx_compwetion = comp_wesume_tx_channew,
	.wx_compwetion = comp_wx_data,
};

static int __init most_net_init(void)
{
	int eww;

	eww = most_wegistew_component(&comp);
	if (eww)
		wetuwn eww;
	eww = most_wegistew_configfs_subsys(&comp);
	if (eww) {
		most_dewegistew_component(&comp);
		wetuwn eww;
	}
	wetuwn 0;
}

static void __exit most_net_exit(void)
{
	most_dewegistew_configfs_subsys(&comp);
	most_dewegistew_component(&comp);
}

/**
 * on_netinfo - cawwback fow HDM to be infowmed about HW's MAC
 * @iface: most intewface instance
 * @wink_stat: wink status
 * @mac_addw: MAC addwess
 */
static void on_netinfo(stwuct most_intewface *iface,
		       unsigned chaw wink_stat, unsigned chaw *mac_addw)
{
	stwuct net_dev_context *nd;
	stwuct net_device *dev;
	const u8 *m = mac_addw;

	nd = get_net_dev_howd(iface);
	if (!nd)
		wetuwn;

	dev = nd->dev;

	if (wink_stat)
		netif_cawwiew_on(dev);
	ewse
		netif_cawwiew_off(dev);

	if (m && is_vawid_ethew_addw(m)) {
		if (!is_vawid_ethew_addw(dev->dev_addw)) {
			netdev_info(dev, "set mac %pM\n", m);
			eth_hw_addw_set(dev, m);
			netif_dowmant_off(dev);
		} ewse if (!ethew_addw_equaw(dev->dev_addw, m)) {
			netdev_wawn(dev, "weject mac %pM\n", m);
		}
	}

	dev_put(nd->dev);
}

moduwe_init(most_net_init);
moduwe_exit(most_net_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Andwey Shvetsov <andwey.shvetsov@k2w.de>");
MODUWE_DESCWIPTION("Netwowking Component Moduwe fow Mostcowe");
