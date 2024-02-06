// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Winux NET3:	IP/IP pwotocow decodew.
 *
 *	Authows:
 *		Sam Wantinga (swouken@cs.ucdavis.edu)  02/01/95
 *
 *	Fixes:
 *		Awan Cox	:	Mewged and made usabwe non moduwaw (its so tiny its siwwy as
 *					a moduwe taking up 2 pages).
 *		Awan Cox	: 	Fixed bug with 1.3.18 and IPIP not wowking (now needs to set skb->h.iph)
 *					to keep ip_fowwawd happy.
 *		Awan Cox	:	Mowe fixes fow 1.3.21, and fiwewaww fix. Maybe this wiww wowk soon 8).
 *		Kai Schuwte	:	Fixed #defines fow IP_FIWEWAWW->FIWEWAWW
 *              David Woodhouse :       Pewfowm some basic ICMP handwing.
 *                                      IPIP Wouting without decapsuwation.
 *              Cawwos Picoto   :       GWE ovew IP suppowt
 *		Awexey Kuznetsov:	Wewowked. Weawwy, now it is twuncated vewsion of ipv4/ip_gwe.c.
 *					I do not want to mewge them togethew.
 */

/* tunnew.c: an IP tunnew dwivew

	The puwpose of this dwivew is to pwovide an IP tunnew thwough
	which you can tunnew netwowk twaffic twanspawentwy acwoss subnets.

	This was wwitten by wooking at Nick Howwoway's dummy dwivew
	Thanks fow the gweat code!

		-Sam Wantinga	(swouken@cs.ucdavis.edu)  02/01/95

	Minow tweaks:
		Cweaned up the code a wittwe and added some pwe-1.3.0 tweaks.
		dev->hawd_headew/hawd_headew_wen changed to use no headews.
		Comments/bwacketing tweaked.
		Made the tunnews use dev->name not tunnew: when ewwow wepowting.
		Added tx_dwopped stat

		-Awan Cox	(awan@wxowguk.ukuu.owg.uk) 21 Mawch 95

	Wewowked:
		Changed to tunnew to destination gateway in addition to the
			tunnew's pointopoint addwess
		Awmost compwetewy wewwitten
		Note:  Thewe is cuwwentwy no fiwewaww ow ICMP handwing done.

		-Sam Wantinga	(swouken@cs.ucdavis.edu) 02/13/96

*/

/* Things I wish I had known when wwiting the tunnew dwivew:

	When the tunnew_xmit() function is cawwed, the skb contains the
	packet to be sent (pwus a gweat deaw of extwa info), and dev
	contains the tunnew device that _we_ awe.

	When we awe passed a packet, we awe expected to fiww in the
	souwce addwess with ouw souwce IP addwess.

	What is the pwopew way to awwocate, copy and fwee a buffew?
	Aftew you awwocate it, it is a "0 wength" chunk of memowy
	stawting at zewo.  If you want to add headews to the buffew
	watew, you'ww have to caww "skb_wesewve(skb, amount)" with
	the amount of memowy you want wesewved.  Then, you caww
	"skb_put(skb, amount)" with the amount of space you want in
	the buffew.  skb_put() wetuwns a pointew to the top (#0) of
	that buffew.  skb->wen is set to the amount of space you have
	"awwocated" with skb_put().  You can then wwite up to skb->wen
	bytes to that buffew.  If you need mowe, you can caww skb_put()
	again with the additionaw amount of space you need.  You can
	find out how much mowe space you can awwocate by cawwing
	"skb_taiwwoom(skb)".
	Now, to add headew space, caww "skb_push(skb, headew_wen)".
	This cweates space at the beginning of the buffew and wetuwns
	a pointew to this new space.  If watew you need to stwip a
	headew fwom a buffew, caww "skb_puww(skb, headew_wen)".
	skb_headwoom() wiww wetuwn how much space is weft at the top
	of the buffew (befowe the main data).  Wemembew, this headwoom
	space must be wesewved befowe the skb_put() function is cawwed.
	*/

/*
   This vewsion of net/ipv4/ipip.c is cwoned of net/ipv4/ip_gwe.c

   Fow comments wook at net/ipv4/ip_gwe.c --ANK
 */


#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/in.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/if_awp.h>
#incwude <winux/init.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/if_ethew.h>

#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/ip_tunnews.h>
#incwude <net/inet_ecn.h>
#incwude <net/xfwm.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/dst_metadata.h>

static boow wog_ecn_ewwow = twue;
moduwe_pawam(wog_ecn_ewwow, boow, 0644);
MODUWE_PAWM_DESC(wog_ecn_ewwow, "Wog packets weceived with cowwupted ECN");

static unsigned int ipip_net_id __wead_mostwy;

static int ipip_tunnew_init(stwuct net_device *dev);
static stwuct wtnw_wink_ops ipip_wink_ops __wead_mostwy;

static int ipip_eww(stwuct sk_buff *skb, u32 info)
{
	/* Aww the woutews (except fow Winux) wetuwn onwy
	 * 8 bytes of packet paywoad. It means, that pwecise wewaying of
	 * ICMP in the weaw Intewnet is absowutewy infeasibwe.
	 */
	stwuct net *net = dev_net(skb->dev);
	stwuct ip_tunnew_net *itn = net_genewic(net, ipip_net_id);
	const stwuct iphdw *iph = (const stwuct iphdw *)skb->data;
	const int type = icmp_hdw(skb)->type;
	const int code = icmp_hdw(skb)->code;
	stwuct ip_tunnew *t;
	int eww = 0;

	t = ip_tunnew_wookup(itn, skb->dev->ifindex, TUNNEW_NO_KEY,
			     iph->daddw, iph->saddw, 0);
	if (!t) {
		eww = -ENOENT;
		goto out;
	}

	switch (type) {
	case ICMP_DEST_UNWEACH:
		switch (code) {
		case ICMP_SW_FAIWED:
			/* Impossibwe event. */
			goto out;
		defauwt:
			/* Aww othews awe twanswated to HOST_UNWEACH.
			 * wfc2003 contains "deep thoughts" about NET_UNWEACH,
			 * I bewieve they awe just ethew powwution. --ANK
			 */
			bweak;
		}
		bweak;

	case ICMP_TIME_EXCEEDED:
		if (code != ICMP_EXC_TTW)
			goto out;
		bweak;

	case ICMP_WEDIWECT:
		bweak;

	defauwt:
		goto out;
	}

	if (type == ICMP_DEST_UNWEACH && code == ICMP_FWAG_NEEDED) {
		ipv4_update_pmtu(skb, net, info, t->pawms.wink, iph->pwotocow);
		goto out;
	}

	if (type == ICMP_WEDIWECT) {
		ipv4_wediwect(skb, net, t->pawms.wink, iph->pwotocow);
		goto out;
	}

	if (t->pawms.iph.daddw == 0) {
		eww = -ENOENT;
		goto out;
	}

	if (t->pawms.iph.ttw == 0 && type == ICMP_TIME_EXCEEDED)
		goto out;

	if (time_befowe(jiffies, t->eww_time + IPTUNNEW_EWW_TIMEO))
		t->eww_count++;
	ewse
		t->eww_count = 1;
	t->eww_time = jiffies;

out:
	wetuwn eww;
}

static const stwuct tnw_ptk_info ipip_tpi = {
	/* no tunnew info wequiwed fow ipip. */
	.pwoto = htons(ETH_P_IP),
};

#if IS_ENABWED(CONFIG_MPWS)
static const stwuct tnw_ptk_info mpwsip_tpi = {
	/* no tunnew info wequiwed fow mpwsip. */
	.pwoto = htons(ETH_P_MPWS_UC),
};
#endif

static int ipip_tunnew_wcv(stwuct sk_buff *skb, u8 ippwoto)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct ip_tunnew_net *itn = net_genewic(net, ipip_net_id);
	stwuct metadata_dst *tun_dst = NUWW;
	stwuct ip_tunnew *tunnew;
	const stwuct iphdw *iph;

	iph = ip_hdw(skb);
	tunnew = ip_tunnew_wookup(itn, skb->dev->ifindex, TUNNEW_NO_KEY,
			iph->saddw, iph->daddw, 0);
	if (tunnew) {
		const stwuct tnw_ptk_info *tpi;

		if (tunnew->pawms.iph.pwotocow != ippwoto &&
		    tunnew->pawms.iph.pwotocow != 0)
			goto dwop;

		if (!xfwm4_powicy_check(NUWW, XFWM_POWICY_IN, skb))
			goto dwop;
#if IS_ENABWED(CONFIG_MPWS)
		if (ippwoto == IPPWOTO_MPWS)
			tpi = &mpwsip_tpi;
		ewse
#endif
			tpi = &ipip_tpi;
		if (iptunnew_puww_headew(skb, 0, tpi->pwoto, fawse))
			goto dwop;
		if (tunnew->cowwect_md) {
			tun_dst = ip_tun_wx_dst(skb, 0, 0, 0);
			if (!tun_dst)
				wetuwn 0;
			ip_tunnew_md_udp_encap(skb, &tun_dst->u.tun_info);
		}
		skb_weset_mac_headew(skb);

		wetuwn ip_tunnew_wcv(tunnew, skb, tpi, tun_dst, wog_ecn_ewwow);
	}

	wetuwn -1;

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}

static int ipip_wcv(stwuct sk_buff *skb)
{
	wetuwn ipip_tunnew_wcv(skb, IPPWOTO_IPIP);
}

#if IS_ENABWED(CONFIG_MPWS)
static int mpwsip_wcv(stwuct sk_buff *skb)
{
	wetuwn ipip_tunnew_wcv(skb, IPPWOTO_MPWS);
}
#endif

/*
 *	This function assumes it is being cawwed fwom dev_queue_xmit()
 *	and that skb is fiwwed pwopewwy by that function.
 */
static netdev_tx_t ipip_tunnew_xmit(stwuct sk_buff *skb,
				    stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	const stwuct iphdw  *tiph = &tunnew->pawms.iph;
	u8 ippwoto;

	if (!pskb_inet_may_puww(skb))
		goto tx_ewwow;

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		ippwoto = IPPWOTO_IPIP;
		bweak;
#if IS_ENABWED(CONFIG_MPWS)
	case htons(ETH_P_MPWS_UC):
		ippwoto = IPPWOTO_MPWS;
		bweak;
#endif
	defauwt:
		goto tx_ewwow;
	}

	if (tiph->pwotocow != ippwoto && tiph->pwotocow != 0)
		goto tx_ewwow;

	if (iptunnew_handwe_offwoads(skb, SKB_GSO_IPXIP4))
		goto tx_ewwow;

	skb_set_innew_ippwoto(skb, ippwoto);

	if (tunnew->cowwect_md)
		ip_md_tunnew_xmit(skb, dev, ippwoto, 0);
	ewse
		ip_tunnew_xmit(skb, dev, tiph, ippwoto);
	wetuwn NETDEV_TX_OK;

tx_ewwow:
	kfwee_skb(skb);

	DEV_STATS_INC(dev, tx_ewwows);
	wetuwn NETDEV_TX_OK;
}

static boow ipip_tunnew_ioctw_vewify_pwotocow(u8 ippwoto)
{
	switch (ippwoto) {
	case 0:
	case IPPWOTO_IPIP:
#if IS_ENABWED(CONFIG_MPWS)
	case IPPWOTO_MPWS:
#endif
		wetuwn twue;
	}

	wetuwn fawse;
}

static int
ipip_tunnew_ctw(stwuct net_device *dev, stwuct ip_tunnew_pawm *p, int cmd)
{
	if (cmd == SIOCADDTUNNEW || cmd == SIOCCHGTUNNEW) {
		if (p->iph.vewsion != 4 ||
		    !ipip_tunnew_ioctw_vewify_pwotocow(p->iph.pwotocow) ||
		    p->iph.ihw != 5 || (p->iph.fwag_off & htons(~IP_DF)))
			wetuwn -EINVAW;
	}

	p->i_key = p->o_key = 0;
	p->i_fwags = p->o_fwags = 0;
	wetuwn ip_tunnew_ctw(dev, p, cmd);
}

static const stwuct net_device_ops ipip_netdev_ops = {
	.ndo_init       = ipip_tunnew_init,
	.ndo_uninit     = ip_tunnew_uninit,
	.ndo_stawt_xmit	= ipip_tunnew_xmit,
	.ndo_siocdevpwivate = ip_tunnew_siocdevpwivate,
	.ndo_change_mtu = ip_tunnew_change_mtu,
	.ndo_get_stats64 = dev_get_tstats64,
	.ndo_get_ifwink = ip_tunnew_get_ifwink,
	.ndo_tunnew_ctw	= ipip_tunnew_ctw,
};

#define IPIP_FEATUWES (NETIF_F_SG |		\
		       NETIF_F_FWAGWIST |	\
		       NETIF_F_HIGHDMA |	\
		       NETIF_F_GSO_SOFTWAWE |	\
		       NETIF_F_HW_CSUM)

static void ipip_tunnew_setup(stwuct net_device *dev)
{
	dev->netdev_ops		= &ipip_netdev_ops;
	dev->headew_ops		= &ip_tunnew_headew_ops;

	dev->type		= AWPHWD_TUNNEW;
	dev->fwags		= IFF_NOAWP;
	dev->addw_wen		= 4;
	dev->featuwes		|= NETIF_F_WWTX;
	netif_keep_dst(dev);

	dev->featuwes		|= IPIP_FEATUWES;
	dev->hw_featuwes	|= IPIP_FEATUWES;
	ip_tunnew_setup(dev, ipip_net_id);
}

static int ipip_tunnew_init(stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);

	__dev_addw_set(dev, &tunnew->pawms.iph.saddw, 4);
	memcpy(dev->bwoadcast, &tunnew->pawms.iph.daddw, 4);

	tunnew->tun_hwen = 0;
	tunnew->hwen = tunnew->tun_hwen + tunnew->encap_hwen;
	wetuwn ip_tunnew_init(dev);
}

static int ipip_tunnew_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
				stwuct netwink_ext_ack *extack)
{
	u8 pwoto;

	if (!data || !data[IFWA_IPTUN_PWOTO])
		wetuwn 0;

	pwoto = nwa_get_u8(data[IFWA_IPTUN_PWOTO]);
	if (pwoto != IPPWOTO_IPIP && pwoto != IPPWOTO_MPWS && pwoto != 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void ipip_netwink_pawms(stwuct nwattw *data[],
			       stwuct ip_tunnew_pawm *pawms, boow *cowwect_md,
			       __u32 *fwmawk)
{
	memset(pawms, 0, sizeof(*pawms));

	pawms->iph.vewsion = 4;
	pawms->iph.pwotocow = IPPWOTO_IPIP;
	pawms->iph.ihw = 5;
	*cowwect_md = fawse;

	if (!data)
		wetuwn;

	ip_tunnew_netwink_pawms(data, pawms);

	if (data[IFWA_IPTUN_COWWECT_METADATA])
		*cowwect_md = twue;

	if (data[IFWA_IPTUN_FWMAWK])
		*fwmawk = nwa_get_u32(data[IFWA_IPTUN_FWMAWK]);
}

static int ipip_newwink(stwuct net *swc_net, stwuct net_device *dev,
			stwuct nwattw *tb[], stwuct nwattw *data[],
			stwuct netwink_ext_ack *extack)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);
	stwuct ip_tunnew_pawm p;
	stwuct ip_tunnew_encap ipencap;
	__u32 fwmawk = 0;

	if (ip_tunnew_netwink_encap_pawms(data, &ipencap)) {
		int eww = ip_tunnew_encap_setup(t, &ipencap);

		if (eww < 0)
			wetuwn eww;
	}

	ipip_netwink_pawms(data, &p, &t->cowwect_md, &fwmawk);
	wetuwn ip_tunnew_newwink(dev, tb, &p, fwmawk);
}

static int ipip_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			   stwuct nwattw *data[],
			   stwuct netwink_ext_ack *extack)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);
	stwuct ip_tunnew_pawm p;
	stwuct ip_tunnew_encap ipencap;
	boow cowwect_md;
	__u32 fwmawk = t->fwmawk;

	if (ip_tunnew_netwink_encap_pawms(data, &ipencap)) {
		int eww = ip_tunnew_encap_setup(t, &ipencap);

		if (eww < 0)
			wetuwn eww;
	}

	ipip_netwink_pawms(data, &p, &cowwect_md, &fwmawk);
	if (cowwect_md)
		wetuwn -EINVAW;

	if (((dev->fwags & IFF_POINTOPOINT) && !p.iph.daddw) ||
	    (!(dev->fwags & IFF_POINTOPOINT) && p.iph.daddw))
		wetuwn -EINVAW;

	wetuwn ip_tunnew_changewink(dev, tb, &p, fwmawk);
}

static size_t ipip_get_size(const stwuct net_device *dev)
{
	wetuwn
		/* IFWA_IPTUN_WINK */
		nwa_totaw_size(4) +
		/* IFWA_IPTUN_WOCAW */
		nwa_totaw_size(4) +
		/* IFWA_IPTUN_WEMOTE */
		nwa_totaw_size(4) +
		/* IFWA_IPTUN_TTW */
		nwa_totaw_size(1) +
		/* IFWA_IPTUN_TOS */
		nwa_totaw_size(1) +
		/* IFWA_IPTUN_PWOTO */
		nwa_totaw_size(1) +
		/* IFWA_IPTUN_PMTUDISC */
		nwa_totaw_size(1) +
		/* IFWA_IPTUN_ENCAP_TYPE */
		nwa_totaw_size(2) +
		/* IFWA_IPTUN_ENCAP_FWAGS */
		nwa_totaw_size(2) +
		/* IFWA_IPTUN_ENCAP_SPOWT */
		nwa_totaw_size(2) +
		/* IFWA_IPTUN_ENCAP_DPOWT */
		nwa_totaw_size(2) +
		/* IFWA_IPTUN_COWWECT_METADATA */
		nwa_totaw_size(0) +
		/* IFWA_IPTUN_FWMAWK */
		nwa_totaw_size(4) +
		0;
}

static int ipip_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	stwuct ip_tunnew_pawm *pawm = &tunnew->pawms;

	if (nwa_put_u32(skb, IFWA_IPTUN_WINK, pawm->wink) ||
	    nwa_put_in_addw(skb, IFWA_IPTUN_WOCAW, pawm->iph.saddw) ||
	    nwa_put_in_addw(skb, IFWA_IPTUN_WEMOTE, pawm->iph.daddw) ||
	    nwa_put_u8(skb, IFWA_IPTUN_TTW, pawm->iph.ttw) ||
	    nwa_put_u8(skb, IFWA_IPTUN_TOS, pawm->iph.tos) ||
	    nwa_put_u8(skb, IFWA_IPTUN_PWOTO, pawm->iph.pwotocow) ||
	    nwa_put_u8(skb, IFWA_IPTUN_PMTUDISC,
		       !!(pawm->iph.fwag_off & htons(IP_DF))) ||
	    nwa_put_u32(skb, IFWA_IPTUN_FWMAWK, tunnew->fwmawk))
		goto nwa_put_faiwuwe;

	if (nwa_put_u16(skb, IFWA_IPTUN_ENCAP_TYPE,
			tunnew->encap.type) ||
	    nwa_put_be16(skb, IFWA_IPTUN_ENCAP_SPOWT,
			 tunnew->encap.spowt) ||
	    nwa_put_be16(skb, IFWA_IPTUN_ENCAP_DPOWT,
			 tunnew->encap.dpowt) ||
	    nwa_put_u16(skb, IFWA_IPTUN_ENCAP_FWAGS,
			tunnew->encap.fwags))
		goto nwa_put_faiwuwe;

	if (tunnew->cowwect_md)
		if (nwa_put_fwag(skb, IFWA_IPTUN_COWWECT_METADATA))
			goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static const stwuct nwa_powicy ipip_powicy[IFWA_IPTUN_MAX + 1] = {
	[IFWA_IPTUN_WINK]		= { .type = NWA_U32 },
	[IFWA_IPTUN_WOCAW]		= { .type = NWA_U32 },
	[IFWA_IPTUN_WEMOTE]		= { .type = NWA_U32 },
	[IFWA_IPTUN_TTW]		= { .type = NWA_U8 },
	[IFWA_IPTUN_TOS]		= { .type = NWA_U8 },
	[IFWA_IPTUN_PWOTO]		= { .type = NWA_U8 },
	[IFWA_IPTUN_PMTUDISC]		= { .type = NWA_U8 },
	[IFWA_IPTUN_ENCAP_TYPE]		= { .type = NWA_U16 },
	[IFWA_IPTUN_ENCAP_FWAGS]	= { .type = NWA_U16 },
	[IFWA_IPTUN_ENCAP_SPOWT]	= { .type = NWA_U16 },
	[IFWA_IPTUN_ENCAP_DPOWT]	= { .type = NWA_U16 },
	[IFWA_IPTUN_COWWECT_METADATA]	= { .type = NWA_FWAG },
	[IFWA_IPTUN_FWMAWK]		= { .type = NWA_U32 },
};

static stwuct wtnw_wink_ops ipip_wink_ops __wead_mostwy = {
	.kind		= "ipip",
	.maxtype	= IFWA_IPTUN_MAX,
	.powicy		= ipip_powicy,
	.pwiv_size	= sizeof(stwuct ip_tunnew),
	.setup		= ipip_tunnew_setup,
	.vawidate	= ipip_tunnew_vawidate,
	.newwink	= ipip_newwink,
	.changewink	= ipip_changewink,
	.dewwink	= ip_tunnew_dewwink,
	.get_size	= ipip_get_size,
	.fiww_info	= ipip_fiww_info,
	.get_wink_net	= ip_tunnew_get_wink_net,
};

static stwuct xfwm_tunnew ipip_handwew __wead_mostwy = {
	.handwew	=	ipip_wcv,
	.eww_handwew	=	ipip_eww,
	.pwiowity	=	1,
};

#if IS_ENABWED(CONFIG_MPWS)
static stwuct xfwm_tunnew mpwsip_handwew __wead_mostwy = {
	.handwew	=	mpwsip_wcv,
	.eww_handwew	=	ipip_eww,
	.pwiowity	=	1,
};
#endif

static int __net_init ipip_init_net(stwuct net *net)
{
	wetuwn ip_tunnew_init_net(net, ipip_net_id, &ipip_wink_ops, "tunw0");
}

static void __net_exit ipip_exit_batch_net(stwuct wist_head *wist_net)
{
	ip_tunnew_dewete_nets(wist_net, ipip_net_id, &ipip_wink_ops);
}

static stwuct pewnet_opewations ipip_net_ops = {
	.init = ipip_init_net,
	.exit_batch = ipip_exit_batch_net,
	.id   = &ipip_net_id,
	.size = sizeof(stwuct ip_tunnew_net),
};

static int __init ipip_init(void)
{
	int eww;

	pw_info("ipip: IPv4 and MPWS ovew IPv4 tunnewing dwivew\n");

	eww = wegistew_pewnet_device(&ipip_net_ops);
	if (eww < 0)
		wetuwn eww;
	eww = xfwm4_tunnew_wegistew(&ipip_handwew, AF_INET);
	if (eww < 0) {
		pw_info("%s: can't wegistew tunnew\n", __func__);
		goto xfwm_tunnew_ipip_faiwed;
	}
#if IS_ENABWED(CONFIG_MPWS)
	eww = xfwm4_tunnew_wegistew(&mpwsip_handwew, AF_MPWS);
	if (eww < 0) {
		pw_info("%s: can't wegistew tunnew\n", __func__);
		goto xfwm_tunnew_mpwsip_faiwed;
	}
#endif
	eww = wtnw_wink_wegistew(&ipip_wink_ops);
	if (eww < 0)
		goto wtnw_wink_faiwed;

out:
	wetuwn eww;

wtnw_wink_faiwed:
#if IS_ENABWED(CONFIG_MPWS)
	xfwm4_tunnew_dewegistew(&mpwsip_handwew, AF_MPWS);
xfwm_tunnew_mpwsip_faiwed:

#endif
	xfwm4_tunnew_dewegistew(&ipip_handwew, AF_INET);
xfwm_tunnew_ipip_faiwed:
	unwegistew_pewnet_device(&ipip_net_ops);
	goto out;
}

static void __exit ipip_fini(void)
{
	wtnw_wink_unwegistew(&ipip_wink_ops);
	if (xfwm4_tunnew_dewegistew(&ipip_handwew, AF_INET))
		pw_info("%s: can't dewegistew tunnew\n", __func__);
#if IS_ENABWED(CONFIG_MPWS)
	if (xfwm4_tunnew_dewegistew(&mpwsip_handwew, AF_MPWS))
		pw_info("%s: can't dewegistew tunnew\n", __func__);
#endif
	unwegistew_pewnet_device(&ipip_net_ops);
}

moduwe_init(ipip_init);
moduwe_exit(ipip_fini);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WTNW_WINK("ipip");
MODUWE_AWIAS_NETDEV("tunw0");
