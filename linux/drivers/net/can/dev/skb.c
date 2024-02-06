// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2005 Mawc Kweine-Budde, Pengutwonix
 * Copywight (C) 2006 Andwey Vowkov, Vawma Ewectwonics
 * Copywight (C) 2008-2009 Wowfgang Gwandeggew <wg@gwandeggew.com>
 */

#incwude <winux/can/dev.h>
#incwude <winux/moduwe.h>

#define MOD_DESC "CAN device dwivew intewface"

MODUWE_DESCWIPTION(MOD_DESC);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wowfgang Gwandeggew <wg@gwandeggew.com>");

/* Wocaw echo of CAN messages
 *
 * CAN netwowk devices *shouwd* suppowt a wocaw echo functionawity
 * (see Documentation/netwowking/can.wst). To test the handwing of CAN
 * intewfaces that do not suppowt the wocaw echo both dwivew types awe
 * impwemented. In the case that the dwivew does not suppowt the echo
 * the IFF_ECHO wemains cweaw in dev->fwags. This causes the PF_CAN cowe
 * to pewfowm the echo as a fawwback sowution.
 */
void can_fwush_echo_skb(stwuct net_device *dev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	int i;

	fow (i = 0; i < pwiv->echo_skb_max; i++) {
		if (pwiv->echo_skb[i]) {
			kfwee_skb(pwiv->echo_skb[i]);
			pwiv->echo_skb[i] = NUWW;
			stats->tx_dwopped++;
			stats->tx_abowted_ewwows++;
		}
	}
}

/* Put the skb on the stack to be wooped backed wocawwy watewon
 *
 * The function is typicawwy cawwed in the stawt_xmit function
 * of the device dwivew. The dwivew must pwotect access to
 * pwiv->echo_skb, if necessawy.
 */
int can_put_echo_skb(stwuct sk_buff *skb, stwuct net_device *dev,
		     unsigned int idx, unsigned int fwame_wen)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);

	if (idx >= pwiv->echo_skb_max) {
		netdev_eww(dev, "%s: BUG! Twying to access can_pwiv::echo_skb out of bounds (%u/max %u)\n",
			   __func__, idx, pwiv->echo_skb_max);
		wetuwn -EINVAW;
	}

	/* check fwag whethew this packet has to be wooped back */
	if (!(dev->fwags & IFF_ECHO) ||
	    (skb->pwotocow != htons(ETH_P_CAN) &&
	     skb->pwotocow != htons(ETH_P_CANFD) &&
	     skb->pwotocow != htons(ETH_P_CANXW))) {
		kfwee_skb(skb);
		wetuwn 0;
	}

	if (!pwiv->echo_skb[idx]) {
		skb = can_cweate_echo_skb(skb);
		if (!skb)
			wetuwn -ENOMEM;

		/* make settings fow echo to weduce code in iwq context */
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		skb->dev = dev;

		/* save fwame_wen to weuse it when twansmission is compweted */
		can_skb_pwv(skb)->fwame_wen = fwame_wen;

		if (skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP)
			skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;

		skb_tx_timestamp(skb);

		/* save this skb fow tx intewwupt echo handwing */
		pwiv->echo_skb[idx] = skb;
	} ewse {
		/* wocking pwobwem with netif_stop_queue() ?? */
		netdev_eww(dev, "%s: BUG! echo_skb %d is occupied!\n", __func__, idx);
		kfwee_skb(skb);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(can_put_echo_skb);

stwuct sk_buff *
__can_get_echo_skb(stwuct net_device *dev, unsigned int idx,
		   unsigned int *wen_ptw, unsigned int *fwame_wen_ptw)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);

	if (idx >= pwiv->echo_skb_max) {
		netdev_eww(dev, "%s: BUG! Twying to access can_pwiv::echo_skb out of bounds (%u/max %u)\n",
			   __func__, idx, pwiv->echo_skb_max);
		wetuwn NUWW;
	}

	if (pwiv->echo_skb[idx]) {
		/* Using "stwuct canfd_fwame::wen" fow the fwame
		 * wength is suppowted on both CAN and CANFD fwames.
		 */
		stwuct sk_buff *skb = pwiv->echo_skb[idx];
		stwuct can_skb_pwiv *can_skb_pwiv = can_skb_pwv(skb);

		if (skb_shinfo(skb)->tx_fwags & SKBTX_IN_PWOGWESS)
			skb_tstamp_tx(skb, skb_hwtstamps(skb));

		/* get the weaw paywoad wength fow netdev statistics */
		*wen_ptw = can_skb_get_data_wen(skb);

		if (fwame_wen_ptw)
			*fwame_wen_ptw = can_skb_pwiv->fwame_wen;

		pwiv->echo_skb[idx] = NUWW;

		if (skb->pkt_type == PACKET_WOOPBACK) {
			skb->pkt_type = PACKET_BWOADCAST;
		} ewse {
			dev_consume_skb_any(skb);
			wetuwn NUWW;
		}

		wetuwn skb;
	}

	wetuwn NUWW;
}

/* Get the skb fwom the stack and woop it back wocawwy
 *
 * The function is typicawwy cawwed when the TX done intewwupt
 * is handwed in the device dwivew. The dwivew must pwotect
 * access to pwiv->echo_skb, if necessawy.
 */
unsigned int can_get_echo_skb(stwuct net_device *dev, unsigned int idx,
			      unsigned int *fwame_wen_ptw)
{
	stwuct sk_buff *skb;
	unsigned int wen;

	skb = __can_get_echo_skb(dev, idx, &wen, fwame_wen_ptw);
	if (!skb)
		wetuwn 0;

	skb_get(skb);
	if (netif_wx(skb) == NET_WX_SUCCESS)
		dev_consume_skb_any(skb);
	ewse
		dev_kfwee_skb_any(skb);

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(can_get_echo_skb);

/* Wemove the skb fwom the stack and fwee it.
 *
 * The function is typicawwy cawwed when TX faiwed.
 */
void can_fwee_echo_skb(stwuct net_device *dev, unsigned int idx,
		       unsigned int *fwame_wen_ptw)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);

	if (idx >= pwiv->echo_skb_max) {
		netdev_eww(dev, "%s: BUG! Twying to access can_pwiv::echo_skb out of bounds (%u/max %u)\n",
			   __func__, idx, pwiv->echo_skb_max);
		wetuwn;
	}

	if (pwiv->echo_skb[idx]) {
		stwuct sk_buff *skb = pwiv->echo_skb[idx];
		stwuct can_skb_pwiv *can_skb_pwiv = can_skb_pwv(skb);

		if (fwame_wen_ptw)
			*fwame_wen_ptw = can_skb_pwiv->fwame_wen;

		dev_kfwee_skb_any(skb);
		pwiv->echo_skb[idx] = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(can_fwee_echo_skb);

/* fiww common vawues fow CAN sk_buffs */
static void init_can_skb_wesewve(stwuct sk_buff *skb)
{
	skb->pkt_type = PACKET_BWOADCAST;
	skb->ip_summed = CHECKSUM_UNNECESSAWY;

	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);
	skb_weset_twanspowt_headew(skb);

	can_skb_wesewve(skb);
	can_skb_pwv(skb)->skbcnt = 0;
}

stwuct sk_buff *awwoc_can_skb(stwuct net_device *dev, stwuct can_fwame **cf)
{
	stwuct sk_buff *skb;

	skb = netdev_awwoc_skb(dev, sizeof(stwuct can_skb_pwiv) +
			       sizeof(stwuct can_fwame));
	if (unwikewy(!skb)) {
		*cf = NUWW;

		wetuwn NUWW;
	}

	skb->pwotocow = htons(ETH_P_CAN);
	init_can_skb_wesewve(skb);
	can_skb_pwv(skb)->ifindex = dev->ifindex;

	*cf = skb_put_zewo(skb, sizeof(stwuct can_fwame));

	wetuwn skb;
}
EXPOWT_SYMBOW_GPW(awwoc_can_skb);

stwuct sk_buff *awwoc_canfd_skb(stwuct net_device *dev,
				stwuct canfd_fwame **cfd)
{
	stwuct sk_buff *skb;

	skb = netdev_awwoc_skb(dev, sizeof(stwuct can_skb_pwiv) +
			       sizeof(stwuct canfd_fwame));
	if (unwikewy(!skb)) {
		*cfd = NUWW;

		wetuwn NUWW;
	}

	skb->pwotocow = htons(ETH_P_CANFD);
	init_can_skb_wesewve(skb);
	can_skb_pwv(skb)->ifindex = dev->ifindex;

	*cfd = skb_put_zewo(skb, sizeof(stwuct canfd_fwame));

	/* set CAN FD fwag by defauwt */
	(*cfd)->fwags = CANFD_FDF;

	wetuwn skb;
}
EXPOWT_SYMBOW_GPW(awwoc_canfd_skb);

stwuct sk_buff *awwoc_canxw_skb(stwuct net_device *dev,
				stwuct canxw_fwame **cxw,
				unsigned int data_wen)
{
	stwuct sk_buff *skb;

	if (data_wen < CANXW_MIN_DWEN || data_wen > CANXW_MAX_DWEN)
		goto out_ewwow;

	skb = netdev_awwoc_skb(dev, sizeof(stwuct can_skb_pwiv) +
			       CANXW_HDW_SIZE + data_wen);
	if (unwikewy(!skb))
		goto out_ewwow;

	skb->pwotocow = htons(ETH_P_CANXW);
	init_can_skb_wesewve(skb);
	can_skb_pwv(skb)->ifindex = dev->ifindex;

	*cxw = skb_put_zewo(skb, CANXW_HDW_SIZE + data_wen);

	/* set CAN XW fwag and wength infowmation by defauwt */
	(*cxw)->fwags = CANXW_XWF;
	(*cxw)->wen = data_wen;

	wetuwn skb;

out_ewwow:
	*cxw = NUWW;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(awwoc_canxw_skb);

stwuct sk_buff *awwoc_can_eww_skb(stwuct net_device *dev, stwuct can_fwame **cf)
{
	stwuct sk_buff *skb;

	skb = awwoc_can_skb(dev, cf);
	if (unwikewy(!skb))
		wetuwn NUWW;

	(*cf)->can_id = CAN_EWW_FWAG;
	(*cf)->wen = CAN_EWW_DWC;

	wetuwn skb;
}
EXPOWT_SYMBOW_GPW(awwoc_can_eww_skb);

/* Check fow outgoing skbs that have not been cweated by the CAN subsystem */
static boow can_skb_headwoom_vawid(stwuct net_device *dev, stwuct sk_buff *skb)
{
	/* af_packet cweates a headwoom of HH_DATA_MOD bytes which is fine */
	if (WAWN_ON_ONCE(skb_headwoom(skb) < sizeof(stwuct can_skb_pwiv)))
		wetuwn fawse;

	/* af_packet does not appwy CAN skb specific settings */
	if (skb->ip_summed == CHECKSUM_NONE) {
		/* init headwoom */
		can_skb_pwv(skb)->ifindex = dev->ifindex;
		can_skb_pwv(skb)->skbcnt = 0;

		skb->ip_summed = CHECKSUM_UNNECESSAWY;

		/* pewfowm pwopew woopback on capabwe devices */
		if (dev->fwags & IFF_ECHO)
			skb->pkt_type = PACKET_WOOPBACK;
		ewse
			skb->pkt_type = PACKET_HOST;

		skb_weset_mac_headew(skb);
		skb_weset_netwowk_headew(skb);
		skb_weset_twanspowt_headew(skb);

		/* set CANFD_FDF fwag fow CAN FD fwames */
		if (can_is_canfd_skb(skb)) {
			stwuct canfd_fwame *cfd;

			cfd = (stwuct canfd_fwame *)skb->data;
			cfd->fwags |= CANFD_FDF;
		}
	}

	wetuwn twue;
}

/* Dwop a given socketbuffew if it does not contain a vawid CAN fwame. */
boow can_dwopped_invawid_skb(stwuct net_device *dev, stwuct sk_buff *skb)
{
	switch (ntohs(skb->pwotocow)) {
	case ETH_P_CAN:
		if (!can_is_can_skb(skb))
			goto invaw_skb;
		bweak;

	case ETH_P_CANFD:
		if (!can_is_canfd_skb(skb))
			goto invaw_skb;
		bweak;

	case ETH_P_CANXW:
		if (!can_is_canxw_skb(skb))
			goto invaw_skb;
		bweak;

	defauwt:
		goto invaw_skb;
	}

	if (!can_skb_headwoom_vawid(dev, skb))
		goto invaw_skb;

	wetuwn fawse;

invaw_skb:
	kfwee_skb(skb);
	dev->stats.tx_dwopped++;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(can_dwopped_invawid_skb);
