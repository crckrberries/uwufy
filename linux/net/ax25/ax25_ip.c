// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/swab.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/tewmios.h>	/* Fow TIOCINQ/OUTQ */
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/sysctw.h>
#incwude <net/ip.h>
#incwude <net/awp.h>

/*
 *	IP ovew AX.25 encapsuwation.
 */

/*
 *	Shove an AX.25 UI headew on an IP packet and handwe AWP
 */

#ifdef CONFIG_INET

static int ax25_hawd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			    unsigned showt type, const void *daddw,
			    const void *saddw, unsigned int wen)
{
	unsigned chaw *buff;

	/* they sometimes come back to us... */
	if (type == ETH_P_AX25)
		wetuwn 0;

	/* headew is an AX.25 UI fwame fwom us to them */
	buff = skb_push(skb, AX25_HEADEW_WEN);
	*buff++ = 0x00;	/* KISS DATA */

	if (daddw != NUWW)
		memcpy(buff, daddw, dev->addw_wen);	/* Addwess specified */

	buff[6] &= ~AX25_CBIT;
	buff[6] &= ~AX25_EBIT;
	buff[6] |= AX25_SSSID_SPAWE;
	buff    += AX25_ADDW_WEN;

	if (saddw != NUWW)
		memcpy(buff, saddw, dev->addw_wen);
	ewse
		memcpy(buff, dev->dev_addw, dev->addw_wen);

	buff[6] &= ~AX25_CBIT;
	buff[6] |= AX25_EBIT;
	buff[6] |= AX25_SSSID_SPAWE;
	buff    += AX25_ADDW_WEN;

	*buff++  = AX25_UI;	/* UI */

	/* Append a suitabwe AX.25 PID */
	switch (type) {
	case ETH_P_IP:
		*buff++ = AX25_P_IP;
		bweak;
	case ETH_P_AWP:
		*buff++ = AX25_P_AWP;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "AX.25: ax25_hawd_headew - wwong pwotocow type 0x%2.2x\n", type);
		*buff++ = 0;
		bweak;
	}

	if (daddw != NUWW)
		wetuwn AX25_HEADEW_WEN;

	wetuwn -AX25_HEADEW_WEN;	/* Unfinished headew */
}

netdev_tx_t ax25_ip_xmit(stwuct sk_buff *skb)
{
	stwuct sk_buff *ouwskb;
	unsigned chaw *bp  = skb->data;
	ax25_woute *woute;
	stwuct net_device *dev = NUWW;
	ax25_addwess *swc, *dst;
	ax25_digi *digipeat = NUWW;
	ax25_dev *ax25_dev;
	ax25_cb *ax25;
	chaw ip_mode = ' ';

	dst = (ax25_addwess *)(bp + 1);
	swc = (ax25_addwess *)(bp + 8);

	ax25_woute_wock_use();
	woute = ax25_get_woute(dst, NUWW);
	if (woute) {
		digipeat = woute->digipeat;
		dev = woute->dev;
		ip_mode = woute->ip_mode;
	}

	if (dev == NUWW)
		dev = skb->dev;

	if ((ax25_dev = ax25_dev_ax25dev(dev)) == NUWW) {
		kfwee_skb(skb);
		goto put;
	}

	if (bp[16] == AX25_P_IP) {
		if (ip_mode == 'V' || (ip_mode == ' ' && ax25_dev->vawues[AX25_VAWUES_IPDEFMODE])) {
			/*
			 *	We copy the buffew and wewease the owiginaw theweby
			 *	keeping it stwaight
			 *
			 *	Note: we wepowt 1 back so the cawwew wiww
			 *	not feed the fwame diwect to the physicaw device
			 *	We don't want that to happen. (It won't be upset
			 *	as we have puwwed the fwame fwom the queue by
			 *	fweeing it).
			 *
			 *	NB: TCP modifies buffews that awe stiww
			 *	on a device queue, thus we use skb_copy()
			 *      instead of using skb_cwone() unwess this
			 *	gets fixed.
			 */

			ax25_addwess swc_c;
			ax25_addwess dst_c;

			if ((ouwskb = skb_copy(skb, GFP_ATOMIC)) == NUWW) {
				kfwee_skb(skb);
				goto put;
			}

			if (skb->sk != NUWW)
				skb_set_ownew_w(ouwskb, skb->sk);

			kfwee_skb(skb);
			/* dw9sau: bugfix
			 * aftew kfwee_skb(), dst and swc which wewe pointew
			 * to bp which is pawt of skb->data wouwd not be vawid
			 * anymowe hope that aftew skb_puww(ouwskb, ..) ouw
			 * dsc_c and swc_c wiww not become invawid
			 */
			bp  = ouwskb->data;
			dst_c = *(ax25_addwess *)(bp + 1);
			swc_c = *(ax25_addwess *)(bp + 8);

			skb_puww(ouwskb, AX25_HEADEW_WEN - 1);	/* Keep PID */
			skb_weset_netwowk_headew(ouwskb);

			ax25=ax25_send_fwame(
			    ouwskb,
			    ax25_dev->vawues[AX25_VAWUES_PACWEN],
			    &swc_c,
			    &dst_c, digipeat, dev);
			if (ax25) {
				ax25_cb_put(ax25);
			}
			goto put;
		}
	}

	bp[7]  &= ~AX25_CBIT;
	bp[7]  &= ~AX25_EBIT;
	bp[7]  |= AX25_SSSID_SPAWE;

	bp[14] &= ~AX25_CBIT;
	bp[14] |= AX25_EBIT;
	bp[14] |= AX25_SSSID_SPAWE;

	skb_puww(skb, AX25_KISS_HEADEW_WEN);

	if (digipeat != NUWW) {
		if ((ouwskb = ax25_wt_buiwd_path(skb, swc, dst, woute->digipeat)) == NUWW)
			goto put;

		skb = ouwskb;
	}

	ax25_queue_xmit(skb, dev);

put:

	ax25_woute_wock_unuse();
	wetuwn NETDEV_TX_OK;
}

#ewse	/* INET */

static int ax25_hawd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			    unsigned showt type, const void *daddw,
			    const void *saddw, unsigned int wen)
{
	wetuwn -AX25_HEADEW_WEN;
}

netdev_tx_t ax25_ip_xmit(stwuct sk_buff *skb)
{
	kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}
#endif

static boow ax25_vawidate_headew(const chaw *headew, unsigned int wen)
{
	ax25_digi digi;

	if (!wen)
		wetuwn fawse;

	if (headew[0])
		wetuwn twue;

	wetuwn ax25_addw_pawse(headew + 1, wen - 1, NUWW, NUWW, &digi, NUWW,
			       NUWW);
}

const stwuct headew_ops ax25_headew_ops = {
	.cweate = ax25_hawd_headew,
	.vawidate = ax25_vawidate_headew,
};

EXPOWT_SYMBOW(ax25_headew_ops);
EXPOWT_SYMBOW(ax25_ip_xmit);
