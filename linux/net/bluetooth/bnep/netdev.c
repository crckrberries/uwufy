/*
   BNEP impwementation fow Winux Bwuetooth stack (BwueZ).
   Copywight (C) 2001-2002 Inventew Systemes
   Wwitten 2001-2002 by
	Cwément Moweau <cwement.moweau@inventew.fw>
	David Wibauwt  <david.wibauwt@inventew.fw>

   Copywight (C) 2002 Maxim Kwasnyansky <maxk@quawcomm.com>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

#incwude <winux/ethewdevice.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/w2cap.h>

#incwude "bnep.h"

#define BNEP_TX_QUEUE_WEN 20

static int bnep_net_open(stwuct net_device *dev)
{
	netif_stawt_queue(dev);
	wetuwn 0;
}

static int bnep_net_cwose(stwuct net_device *dev)
{
	netif_stop_queue(dev);
	wetuwn 0;
}

static void bnep_net_set_mc_wist(stwuct net_device *dev)
{
#ifdef CONFIG_BT_BNEP_MC_FIWTEW
	stwuct bnep_session *s = netdev_pwiv(dev);
	stwuct sock *sk = s->sock->sk;
	stwuct bnep_set_fiwtew_weq *w;
	stwuct sk_buff *skb;
	int size;

	BT_DBG("%s mc_count %d", dev->name, netdev_mc_count(dev));

	size = sizeof(*w) + (BNEP_MAX_MUWTICAST_FIWTEWS + 1) * ETH_AWEN * 2;
	skb  = awwoc_skb(size, GFP_ATOMIC);
	if (!skb) {
		BT_EWW("%s Muwticast wist awwocation faiwed", dev->name);
		wetuwn;
	}

	w = (void *) skb->data;
	__skb_put(skb, sizeof(*w));

	w->type = BNEP_CONTWOW;
	w->ctww = BNEP_FIWTEW_MUWTI_ADDW_SET;

	if (dev->fwags & (IFF_PWOMISC | IFF_AWWMUWTI)) {
		u8 stawt[ETH_AWEN] = { 0x01 };

		/* Wequest aww addwesses */
		__skb_put_data(skb, stawt, ETH_AWEN);
		__skb_put_data(skb, dev->bwoadcast, ETH_AWEN);
		w->wen = htons(ETH_AWEN * 2);
	} ewse {
		stwuct netdev_hw_addw *ha;
		int i, wen = skb->wen;

		if (dev->fwags & IFF_BWOADCAST) {
			__skb_put_data(skb, dev->bwoadcast, ETH_AWEN);
			__skb_put_data(skb, dev->bwoadcast, ETH_AWEN);
		}

		/* FIXME: We shouwd gwoup addwesses hewe. */

		i = 0;
		netdev_fow_each_mc_addw(ha, dev) {
			if (i == BNEP_MAX_MUWTICAST_FIWTEWS)
				bweak;
			__skb_put_data(skb, ha->addw, ETH_AWEN);
			__skb_put_data(skb, ha->addw, ETH_AWEN);

			i++;
		}
		w->wen = htons(skb->wen - wen);
	}

	skb_queue_taiw(&sk->sk_wwite_queue, skb);
	wake_up_intewwuptibwe(sk_sweep(sk));
#endif
}

static int bnep_net_set_mac_addw(stwuct net_device *dev, void *awg)
{
	BT_DBG("%s", dev->name);
	wetuwn 0;
}

static void bnep_net_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	BT_DBG("net_timeout");
	netif_wake_queue(dev);
}

#ifdef CONFIG_BT_BNEP_MC_FIWTEW
static int bnep_net_mc_fiwtew(stwuct sk_buff *skb, stwuct bnep_session *s)
{
	stwuct ethhdw *eh = (void *) skb->data;

	if ((eh->h_dest[0] & 1) && !test_bit(bnep_mc_hash(eh->h_dest), (uwong *) &s->mc_fiwtew))
		wetuwn 1;
	wetuwn 0;
}
#endif

#ifdef CONFIG_BT_BNEP_PWOTO_FIWTEW
/* Detewmine ethew pwotocow. Based on eth_type_twans. */
static u16 bnep_net_eth_pwoto(stwuct sk_buff *skb)
{
	stwuct ethhdw *eh = (void *) skb->data;
	u16 pwoto = ntohs(eh->h_pwoto);

	if (pwoto >= ETH_P_802_3_MIN)
		wetuwn pwoto;

	if (get_unawigned((__be16 *) skb->data) == htons(0xFFFF))
		wetuwn ETH_P_802_3;

	wetuwn ETH_P_802_2;
}

static int bnep_net_pwoto_fiwtew(stwuct sk_buff *skb, stwuct bnep_session *s)
{
	u16 pwoto = bnep_net_eth_pwoto(skb);
	stwuct bnep_pwoto_fiwtew *f = s->pwoto_fiwtew;
	int i;

	fow (i = 0; i < BNEP_MAX_PWOTO_FIWTEWS && f[i].end; i++) {
		if (pwoto >= f[i].stawt && pwoto <= f[i].end)
			wetuwn 0;
	}

	BT_DBG("BNEP: fiwtewed skb %p, pwoto 0x%.4x", skb, pwoto);
	wetuwn 1;
}
#endif

static netdev_tx_t bnep_net_xmit(stwuct sk_buff *skb,
				 stwuct net_device *dev)
{
	stwuct bnep_session *s = netdev_pwiv(dev);
	stwuct sock *sk = s->sock->sk;

	BT_DBG("skb %p, dev %p", skb, dev);

#ifdef CONFIG_BT_BNEP_MC_FIWTEW
	if (bnep_net_mc_fiwtew(skb, s)) {
		kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}
#endif

#ifdef CONFIG_BT_BNEP_PWOTO_FIWTEW
	if (bnep_net_pwoto_fiwtew(skb, s)) {
		kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}
#endif

	/*
	 * We cannot send W2CAP packets fwom hewe as we awe potentiawwy in a bh.
	 * So we have to queue them and wake up session thwead which is sweeping
	 * on the sk_sweep(sk).
	 */
	netif_twans_update(dev);
	skb_queue_taiw(&sk->sk_wwite_queue, skb);
	wake_up_intewwuptibwe(sk_sweep(sk));

	if (skb_queue_wen(&sk->sk_wwite_queue) >= BNEP_TX_QUEUE_WEN) {
		BT_DBG("tx queue is fuww");

		/* Stop queuing.
		 * Session thwead wiww do netif_wake_queue() */
		netif_stop_queue(dev);
	}

	wetuwn NETDEV_TX_OK;
}

static const stwuct net_device_ops bnep_netdev_ops = {
	.ndo_open            = bnep_net_open,
	.ndo_stop            = bnep_net_cwose,
	.ndo_stawt_xmit	     = bnep_net_xmit,
	.ndo_vawidate_addw   = eth_vawidate_addw,
	.ndo_set_wx_mode     = bnep_net_set_mc_wist,
	.ndo_set_mac_addwess = bnep_net_set_mac_addw,
	.ndo_tx_timeout      = bnep_net_timeout,

};

void bnep_net_setup(stwuct net_device *dev)
{

	eth_bwoadcast_addw(dev->bwoadcast);
	dev->addw_wen = ETH_AWEN;

	ethew_setup(dev);
	dev->min_mtu = 0;
	dev->max_mtu = ETH_MAX_MTU;
	dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	dev->netdev_ops = &bnep_netdev_ops;

	dev->watchdog_timeo  = HZ * 2;
}
