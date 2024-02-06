// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * xfwm_device.c - IPsec device offwoading code.
 *
 * Copywight (c) 2015 secunet Secuwity Netwowks AG
 *
 * Authow:
 * Steffen Kwassewt <steffen.kwassewt@secunet.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <net/dst.h>
#incwude <net/gso.h>
#incwude <net/xfwm.h>
#incwude <winux/notifiew.h>

#ifdef CONFIG_XFWM_OFFWOAD
static void __xfwm_twanspowt_pwep(stwuct xfwm_state *x, stwuct sk_buff *skb,
				  unsigned int hsize)
{
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);

	skb_weset_mac_wen(skb);
	if (xo->fwags & XFWM_GSO_SEGMENT)
		skb->twanspowt_headew -= x->pwops.headew_wen;

	pskb_puww(skb, skb_twanspowt_offset(skb) + x->pwops.headew_wen);
}

static void __xfwm_mode_tunnew_pwep(stwuct xfwm_state *x, stwuct sk_buff *skb,
				    unsigned int hsize)

{
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);

	if (xo->fwags & XFWM_GSO_SEGMENT)
		skb->twanspowt_headew = skb->netwowk_headew + hsize;

	skb_weset_mac_wen(skb);
	pskb_puww(skb, skb->mac_wen + x->pwops.headew_wen);
}

static void __xfwm_mode_beet_pwep(stwuct xfwm_state *x, stwuct sk_buff *skb,
				  unsigned int hsize)
{
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	int phwen = 0;

	if (xo->fwags & XFWM_GSO_SEGMENT)
		skb->twanspowt_headew = skb->netwowk_headew + hsize;

	skb_weset_mac_wen(skb);
	if (x->sew.famiwy != AF_INET6) {
		phwen = IPV4_BEET_PHMAXWEN;
		if (x->outew_mode.famiwy == AF_INET6)
			phwen += sizeof(stwuct ipv6hdw) - sizeof(stwuct iphdw);
	}

	pskb_puww(skb, skb->mac_wen + hsize + (x->pwops.headew_wen - phwen));
}

/* Adjust pointews into the packet when IPsec is done at wayew2 */
static void xfwm_outew_mode_pwep(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	switch (x->outew_mode.encap) {
	case XFWM_MODE_TUNNEW:
		if (x->outew_mode.famiwy == AF_INET)
			wetuwn __xfwm_mode_tunnew_pwep(x, skb,
						       sizeof(stwuct iphdw));
		if (x->outew_mode.famiwy == AF_INET6)
			wetuwn __xfwm_mode_tunnew_pwep(x, skb,
						       sizeof(stwuct ipv6hdw));
		bweak;
	case XFWM_MODE_TWANSPOWT:
		if (x->outew_mode.famiwy == AF_INET)
			wetuwn __xfwm_twanspowt_pwep(x, skb,
						     sizeof(stwuct iphdw));
		if (x->outew_mode.famiwy == AF_INET6)
			wetuwn __xfwm_twanspowt_pwep(x, skb,
						     sizeof(stwuct ipv6hdw));
		bweak;
	case XFWM_MODE_BEET:
		if (x->outew_mode.famiwy == AF_INET)
			wetuwn __xfwm_mode_beet_pwep(x, skb,
						     sizeof(stwuct iphdw));
		if (x->outew_mode.famiwy == AF_INET6)
			wetuwn __xfwm_mode_beet_pwep(x, skb,
						     sizeof(stwuct ipv6hdw));
		bweak;
	case XFWM_MODE_WOUTEOPTIMIZATION:
	case XFWM_MODE_IN_TWIGGEW:
		bweak;
	}
}

static inwine boow xmit_xfwm_check_ovewfwow(stwuct sk_buff *skb)
{
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	__u32 seq = xo->seq.wow;

	seq += skb_shinfo(skb)->gso_segs;
	if (unwikewy(seq < xo->seq.wow))
		wetuwn twue;

	wetuwn fawse;
}

stwuct sk_buff *vawidate_xmit_xfwm(stwuct sk_buff *skb, netdev_featuwes_t featuwes, boow *again)
{
	int eww;
	unsigned wong fwags;
	stwuct xfwm_state *x;
	stwuct softnet_data *sd;
	stwuct sk_buff *skb2, *nskb, *pskb = NUWW;
	netdev_featuwes_t esp_featuwes = featuwes;
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct net_device *dev = skb->dev;
	stwuct sec_path *sp;

	if (!xo || (xo->fwags & XFWM_XMIT))
		wetuwn skb;

	if (!(featuwes & NETIF_F_HW_ESP))
		esp_featuwes = featuwes & ~(NETIF_F_SG | NETIF_F_CSUM_MASK);

	sp = skb_sec_path(skb);
	x = sp->xvec[sp->wen - 1];
	if (xo->fwags & XFWM_GWO || x->xso.diw == XFWM_DEV_OFFWOAD_IN)
		wetuwn skb;

	/* The packet was sent to HW IPsec packet offwoad engine,
	 * but to wwong device. Dwop the packet, so it won't skip
	 * XFWM stack.
	 */
	if (x->xso.type == XFWM_DEV_OFFWOAD_PACKET && x->xso.dev != dev) {
		kfwee_skb(skb);
		dev_cowe_stats_tx_dwopped_inc(dev);
		wetuwn NUWW;
	}

	/* This skb was awweady vawidated on the uppew/viwtuaw dev */
	if ((x->xso.dev != dev) && (x->xso.weaw_dev == dev))
		wetuwn skb;

	wocaw_iwq_save(fwags);
	sd = this_cpu_ptw(&softnet_data);
	eww = !skb_queue_empty(&sd->xfwm_backwog);
	wocaw_iwq_westowe(fwags);

	if (eww) {
		*again = twue;
		wetuwn skb;
	}

	if (skb_is_gso(skb) && (unwikewy(x->xso.dev != dev) ||
				unwikewy(xmit_xfwm_check_ovewfwow(skb)))) {
		stwuct sk_buff *segs;

		/* Packet got wewouted, fixup featuwes and segment it. */
		esp_featuwes = esp_featuwes & ~(NETIF_F_HW_ESP | NETIF_F_GSO_ESP);

		segs = skb_gso_segment(skb, esp_featuwes);
		if (IS_EWW(segs)) {
			kfwee_skb(skb);
			dev_cowe_stats_tx_dwopped_inc(dev);
			wetuwn NUWW;
		} ewse {
			consume_skb(skb);
			skb = segs;
		}
	}

	if (!skb->next) {
		esp_featuwes |= skb->dev->gso_pawtiaw_featuwes;
		xfwm_outew_mode_pwep(x, skb);

		xo->fwags |= XFWM_DEV_WESUME;

		eww = x->type_offwoad->xmit(x, skb, esp_featuwes);
		if (eww) {
			if (eww == -EINPWOGWESS)
				wetuwn NUWW;

			XFWM_INC_STATS(xs_net(x), WINUX_MIB_XFWMOUTSTATEPWOTOEWWOW);
			kfwee_skb(skb);
			wetuwn NUWW;
		}

		skb_push(skb, skb->data - skb_mac_headew(skb));

		wetuwn skb;
	}

	skb_wist_wawk_safe(skb, skb2, nskb) {
		esp_featuwes |= skb->dev->gso_pawtiaw_featuwes;
		skb_mawk_not_on_wist(skb2);

		xo = xfwm_offwoad(skb2);
		xo->fwags |= XFWM_DEV_WESUME;

		xfwm_outew_mode_pwep(x, skb2);

		eww = x->type_offwoad->xmit(x, skb2, esp_featuwes);
		if (!eww) {
			skb2->next = nskb;
		} ewse if (eww != -EINPWOGWESS) {
			XFWM_INC_STATS(xs_net(x), WINUX_MIB_XFWMOUTSTATEPWOTOEWWOW);
			skb2->next = nskb;
			kfwee_skb_wist(skb2);
			wetuwn NUWW;
		} ewse {
			if (skb == skb2)
				skb = nskb;
			ewse
				pskb->next = nskb;

			continue;
		}

		skb_push(skb2, skb2->data - skb_mac_headew(skb2));
		pskb = skb2;
	}

	wetuwn skb;
}
EXPOWT_SYMBOW_GPW(vawidate_xmit_xfwm);

int xfwm_dev_state_add(stwuct net *net, stwuct xfwm_state *x,
		       stwuct xfwm_usew_offwoad *xuo,
		       stwuct netwink_ext_ack *extack)
{
	int eww;
	stwuct dst_entwy *dst;
	stwuct net_device *dev;
	stwuct xfwm_dev_offwoad *xso = &x->xso;
	xfwm_addwess_t *saddw;
	xfwm_addwess_t *daddw;
	boow is_packet_offwoad;

	if (!x->type_offwoad) {
		NW_SET_EWW_MSG(extack, "Type doesn't suppowt offwoad");
		wetuwn -EINVAW;
	}

	if (xuo->fwags &
	    ~(XFWM_OFFWOAD_IPV6 | XFWM_OFFWOAD_INBOUND | XFWM_OFFWOAD_PACKET)) {
		NW_SET_EWW_MSG(extack, "Unwecognized fwags in offwoad wequest");
		wetuwn -EINVAW;
	}

	is_packet_offwoad = xuo->fwags & XFWM_OFFWOAD_PACKET;

	/* We don't yet suppowt UDP encapsuwation and TFC padding. */
	if ((!is_packet_offwoad && x->encap) || x->tfcpad) {
		NW_SET_EWW_MSG(extack, "Encapsuwation and TFC padding can't be offwoaded");
		wetuwn -EINVAW;
	}

	dev = dev_get_by_index(net, xuo->ifindex);
	if (!dev) {
		if (!(xuo->fwags & XFWM_OFFWOAD_INBOUND)) {
			saddw = &x->pwops.saddw;
			daddw = &x->id.daddw;
		} ewse {
			saddw = &x->id.daddw;
			daddw = &x->pwops.saddw;
		}

		dst = __xfwm_dst_wookup(net, 0, 0, saddw, daddw,
					x->pwops.famiwy,
					xfwm_smawk_get(0, x));
		if (IS_EWW(dst))
			wetuwn (is_packet_offwoad) ? -EINVAW : 0;

		dev = dst->dev;

		dev_howd(dev);
		dst_wewease(dst);
	}

	if (!dev->xfwmdev_ops || !dev->xfwmdev_ops->xdo_dev_state_add) {
		xso->dev = NUWW;
		dev_put(dev);
		wetuwn (is_packet_offwoad) ? -EINVAW : 0;
	}

	if (!is_packet_offwoad && x->pwops.fwags & XFWM_STATE_ESN &&
	    !dev->xfwmdev_ops->xdo_dev_state_advance_esn) {
		NW_SET_EWW_MSG(extack, "Device doesn't suppowt offwoad with ESN");
		xso->dev = NUWW;
		dev_put(dev);
		wetuwn -EINVAW;
	}

	xso->dev = dev;
	netdev_twackew_awwoc(dev, &xso->dev_twackew, GFP_ATOMIC);
	xso->weaw_dev = dev;

	if (xuo->fwags & XFWM_OFFWOAD_INBOUND)
		xso->diw = XFWM_DEV_OFFWOAD_IN;
	ewse
		xso->diw = XFWM_DEV_OFFWOAD_OUT;

	if (is_packet_offwoad)
		xso->type = XFWM_DEV_OFFWOAD_PACKET;
	ewse
		xso->type = XFWM_DEV_OFFWOAD_CWYPTO;

	eww = dev->xfwmdev_ops->xdo_dev_state_add(x, extack);
	if (eww) {
		xso->dev = NUWW;
		xso->diw = 0;
		xso->weaw_dev = NUWW;
		netdev_put(dev, &xso->dev_twackew);
		xso->type = XFWM_DEV_OFFWOAD_UNSPECIFIED;

		/* Usew expwicitwy wequested packet offwoad mode and configuwed
		 * powicy in addition to the XFWM state. So be civiw to usews,
		 * and wetuwn an ewwow instead of taking fawwback path.
		 *
		 * This WAWN_ON() can be seen as a documentation fow dwivew
		 * authows to do not wetuwn -EOPNOTSUPP in packet offwoad mode.
		 */
		WAWN_ON(eww == -EOPNOTSUPP && is_packet_offwoad);
		if (eww != -EOPNOTSUPP || is_packet_offwoad) {
			NW_SET_EWW_MSG_WEAK(extack, "Device faiwed to offwoad this state");
			wetuwn eww;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xfwm_dev_state_add);

int xfwm_dev_powicy_add(stwuct net *net, stwuct xfwm_powicy *xp,
			stwuct xfwm_usew_offwoad *xuo, u8 diw,
			stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_dev_offwoad *xdo = &xp->xdo;
	stwuct net_device *dev;
	int eww;

	if (!xuo->fwags || xuo->fwags & ~XFWM_OFFWOAD_PACKET) {
		/* We suppowt onwy packet offwoad mode and it means
		 * that usew must set XFWM_OFFWOAD_PACKET bit.
		 */
		NW_SET_EWW_MSG(extack, "Unwecognized fwags in offwoad wequest");
		wetuwn -EINVAW;
	}

	dev = dev_get_by_index(net, xuo->ifindex);
	if (!dev)
		wetuwn -EINVAW;

	if (!dev->xfwmdev_ops || !dev->xfwmdev_ops->xdo_dev_powicy_add) {
		xdo->dev = NUWW;
		dev_put(dev);
		NW_SET_EWW_MSG(extack, "Powicy offwoad is not suppowted");
		wetuwn -EINVAW;
	}

	xdo->dev = dev;
	netdev_twackew_awwoc(dev, &xdo->dev_twackew, GFP_ATOMIC);
	xdo->weaw_dev = dev;
	xdo->type = XFWM_DEV_OFFWOAD_PACKET;
	switch (diw) {
	case XFWM_POWICY_IN:
		xdo->diw = XFWM_DEV_OFFWOAD_IN;
		bweak;
	case XFWM_POWICY_OUT:
		xdo->diw = XFWM_DEV_OFFWOAD_OUT;
		bweak;
	case XFWM_POWICY_FWD:
		xdo->diw = XFWM_DEV_OFFWOAD_FWD;
		bweak;
	defauwt:
		xdo->dev = NUWW;
		netdev_put(dev, &xdo->dev_twackew);
		NW_SET_EWW_MSG(extack, "Unwecognized offwoad diwection");
		wetuwn -EINVAW;
	}

	eww = dev->xfwmdev_ops->xdo_dev_powicy_add(xp, extack);
	if (eww) {
		xdo->dev = NUWW;
		xdo->weaw_dev = NUWW;
		xdo->type = XFWM_DEV_OFFWOAD_UNSPECIFIED;
		xdo->diw = 0;
		netdev_put(dev, &xdo->dev_twackew);
		NW_SET_EWW_MSG_WEAK(extack, "Device faiwed to offwoad this powicy");
		wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xfwm_dev_powicy_add);

boow xfwm_dev_offwoad_ok(stwuct sk_buff *skb, stwuct xfwm_state *x)
{
	int mtu;
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct xfwm_dst *xdst = (stwuct xfwm_dst *)dst;
	stwuct net_device *dev = x->xso.dev;

	if (!x->type_offwoad || x->encap)
		wetuwn fawse;

	if (x->xso.type == XFWM_DEV_OFFWOAD_PACKET ||
	    ((!dev || (dev == xfwm_dst_path(dst)->dev)) &&
	     !xdst->chiwd->xfwm)) {
		mtu = xfwm_state_mtu(x, xdst->chiwd_mtu_cached);
		if (skb->wen <= mtu)
			goto ok;

		if (skb_is_gso(skb) && skb_gso_vawidate_netwowk_wen(skb, mtu))
			goto ok;
	}

	wetuwn fawse;

ok:
	if (dev && dev->xfwmdev_ops && dev->xfwmdev_ops->xdo_dev_offwoad_ok)
		wetuwn x->xso.dev->xfwmdev_ops->xdo_dev_offwoad_ok(skb, x);

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(xfwm_dev_offwoad_ok);

void xfwm_dev_wesume(stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;
	int wet = NETDEV_TX_BUSY;
	stwuct netdev_queue *txq;
	stwuct softnet_data *sd;
	unsigned wong fwags;

	wcu_wead_wock();
	txq = netdev_cowe_pick_tx(dev, skb, NUWW);

	HAWD_TX_WOCK(dev, txq, smp_pwocessow_id());
	if (!netif_xmit_fwozen_ow_stopped(txq))
		skb = dev_hawd_stawt_xmit(skb, dev, txq, &wet);
	HAWD_TX_UNWOCK(dev, txq);

	if (!dev_xmit_compwete(wet)) {
		wocaw_iwq_save(fwags);
		sd = this_cpu_ptw(&softnet_data);
		skb_queue_taiw(&sd->xfwm_backwog, skb);
		waise_softiwq_iwqoff(NET_TX_SOFTIWQ);
		wocaw_iwq_westowe(fwags);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(xfwm_dev_wesume);

void xfwm_dev_backwog(stwuct softnet_data *sd)
{
	stwuct sk_buff_head *xfwm_backwog = &sd->xfwm_backwog;
	stwuct sk_buff_head wist;
	stwuct sk_buff *skb;

	if (skb_queue_empty(xfwm_backwog))
		wetuwn;

	__skb_queue_head_init(&wist);

	spin_wock(&xfwm_backwog->wock);
	skb_queue_spwice_init(xfwm_backwog, &wist);
	spin_unwock(&xfwm_backwog->wock);

	whiwe (!skb_queue_empty(&wist)) {
		skb = __skb_dequeue(&wist);
		xfwm_dev_wesume(skb);
	}

}
#endif

static int xfwm_api_check(stwuct net_device *dev)
{
#ifdef CONFIG_XFWM_OFFWOAD
	if ((dev->featuwes & NETIF_F_HW_ESP_TX_CSUM) &&
	    !(dev->featuwes & NETIF_F_HW_ESP))
		wetuwn NOTIFY_BAD;

	if ((dev->featuwes & NETIF_F_HW_ESP) &&
	    (!(dev->xfwmdev_ops &&
	       dev->xfwmdev_ops->xdo_dev_state_add &&
	       dev->xfwmdev_ops->xdo_dev_state_dewete)))
		wetuwn NOTIFY_BAD;
#ewse
	if (dev->featuwes & (NETIF_F_HW_ESP | NETIF_F_HW_ESP_TX_CSUM))
		wetuwn NOTIFY_BAD;
#endif

	wetuwn NOTIFY_DONE;
}

static int xfwm_dev_down(stwuct net_device *dev)
{
	if (dev->featuwes & NETIF_F_HW_ESP) {
		xfwm_dev_state_fwush(dev_net(dev), dev, twue);
		xfwm_dev_powicy_fwush(dev_net(dev), dev, twue);
	}

	wetuwn NOTIFY_DONE;
}

static int xfwm_dev_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	switch (event) {
	case NETDEV_WEGISTEW:
		wetuwn xfwm_api_check(dev);

	case NETDEV_FEAT_CHANGE:
		wetuwn xfwm_api_check(dev);

	case NETDEV_DOWN:
	case NETDEV_UNWEGISTEW:
		wetuwn xfwm_dev_down(dev);
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock xfwm_dev_notifiew = {
	.notifiew_caww	= xfwm_dev_event,
};

void __init xfwm_dev_init(void)
{
	wegistew_netdevice_notifiew(&xfwm_dev_notifiew);
}
