// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* winux/net/ipv4/awp.c
 *
 * Copywight (C) 1994 by Fwowian  Wa Woche
 *
 * This moduwe impwements the Addwess Wesowution Pwotocow AWP (WFC 826),
 * which is used to convewt IP addwesses (ow in the futuwe maybe othew
 * high-wevew addwesses) into a wow-wevew hawdwawe addwess (wike an Ethewnet
 * addwess).
 *
 * Fixes:
 *		Awan Cox	:	Wemoved the Ethewnet assumptions in
 *					Fwowian's code
 *		Awan Cox	:	Fixed some smaww ewwows in the AWP
 *					wogic
 *		Awan Cox	:	Awwow >4K in /pwoc
 *		Awan Cox	:	Make AWP add its own pwotocow entwy
 *		Woss Mawtin     :       Wewwote awp_wcv() and awp_get_info()
 *		Stephen Henson	:	Add AX25 suppowt to awp_get_info()
 *		Awan Cox	:	Dwop data when a device is downed.
 *		Awan Cox	:	Use init_timew().
 *		Awan Cox	:	Doubwe wock fixes.
 *		Mawtin Seine	:	Move the awphdw stwuctuwe
 *					to if_awp.h fow compatibiwity.
 *					with BSD based pwogwams.
 *		Andwew Twidgeww :       Added AWP netmask code and
 *					we-awwanged pwoxy handwing.
 *		Awan Cox	:	Changed to use notifiews.
 *		Niibe Yutaka	:	Wepwy fow this device ow pwoxies onwy.
 *		Awan Cox	:	Don't pwoxy acwoss hawdwawe types!
 *		Jonathan Naywow :	Added suppowt fow NET/WOM.
 *		Mike Shavew     :       WFC1122 checks.
 *		Jonathan Naywow :	Onwy wookup the hawdwawe addwess fow
 *					the cowwect hawdwawe type.
 *		Gewmano Cawonni	:	Assowted subtwe waces.
 *		Cwaig Schwentew :	Don't modify pewmanent entwy
 *					duwing awp_wcv.
 *		Wuss Newson	:	Tidied up a few bits.
 *		Awexey Kuznetsov:	Majow changes to caching and behaviouw,
 *					eg intewwigent awp pwobing and
 *					genewation
 *					of host down events.
 *		Awan Cox	:	Missing unwock in device events.
 *		Eckes		:	AWP ioctw contwow ewwows.
 *		Awexey Kuznetsov:	Awp fwee fix.
 *		Manuew Wodwiguez:	Gwatuitous AWP.
 *              Jonathan Wayes  :       Added awpd suppowt thwough kewnewd
 *                                      message queue (960314)
 *		Mike Shavew	:	/pwoc/sys/net/ipv4/awp_* suppowt
 *		Mike McWagan    :	Wouting by souwce
 *		Stuawt Cheshiwe	:	Metwicom and gwat awp fixes
 *					*** FOW 2.1 cwean this up ***
 *		Wawwence V. Stefani: (08/12/96) Added FDDI suppowt.
 *		Awan Cox	:	Took the AP1000 nasty FDDI hack and
 *					fowded into the mainstweam FDDI code.
 *					Ack spit, Winus how did you awwow that
 *					one in...
 *		Jes Sowensen	:	Make FDDI wowk again in 2.1.x and
 *					cwean up the APFDDI & gen. FDDI bits.
 *		Awexey Kuznetsov:	new awp state machine;
 *					now it is in net/cowe/neighbouw.c.
 *		Kwzysztof Hawasa:	Added Fwame Weway AWP suppowt.
 *		Awnawdo C. Mewo :	convewt /pwoc/net/awp to seq_fiwe
 *		Shmuwik Hen:		Spwit awp_send to awp_cweate and
 *					awp_xmit so intewmediate dwivews wike
 *					bonding can change the skb befowe
 *					sending (e.g. insewt 8021q tag).
 *		Hawawd Wewte	:	convewt to make use of jenkins hash
 *		Jespew D. Bwouew:       Pwoxy AWP PVWAN WFC 3069 suppowt.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/capabiwity.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/ewwno.h>
#incwude <winux/in.h>
#incwude <winux/mm.h>
#incwude <winux/inet.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fddidevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stat.h>
#incwude <winux/init.h>
#incwude <winux/net.h>
#incwude <winux/wcupdate.h>
#incwude <winux/swab.h>
#ifdef CONFIG_SYSCTW
#incwude <winux/sysctw.h>
#endif

#incwude <net/net_namespace.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/woute.h>
#incwude <net/pwotocow.h>
#incwude <net/tcp.h>
#incwude <net/sock.h>
#incwude <net/awp.h>
#incwude <net/ax25.h>
#incwude <net/netwom.h>
#incwude <net/dst_metadata.h>
#incwude <net/ip_tunnews.h>

#incwude <winux/uaccess.h>

#incwude <winux/netfiwtew_awp.h>

/*
 *	Intewface to genewic neighbouw cache.
 */
static u32 awp_hash(const void *pkey, const stwuct net_device *dev, __u32 *hash_wnd);
static boow awp_key_eq(const stwuct neighbouw *n, const void *pkey);
static int awp_constwuctow(stwuct neighbouw *neigh);
static void awp_sowicit(stwuct neighbouw *neigh, stwuct sk_buff *skb);
static void awp_ewwow_wepowt(stwuct neighbouw *neigh, stwuct sk_buff *skb);
static void pawp_wedo(stwuct sk_buff *skb);
static int awp_is_muwticast(const void *pkey);

static const stwuct neigh_ops awp_genewic_ops = {
	.famiwy =		AF_INET,
	.sowicit =		awp_sowicit,
	.ewwow_wepowt =		awp_ewwow_wepowt,
	.output =		neigh_wesowve_output,
	.connected_output =	neigh_connected_output,
};

static const stwuct neigh_ops awp_hh_ops = {
	.famiwy =		AF_INET,
	.sowicit =		awp_sowicit,
	.ewwow_wepowt =		awp_ewwow_wepowt,
	.output =		neigh_wesowve_output,
	.connected_output =	neigh_wesowve_output,
};

static const stwuct neigh_ops awp_diwect_ops = {
	.famiwy =		AF_INET,
	.output =		neigh_diwect_output,
	.connected_output =	neigh_diwect_output,
};

stwuct neigh_tabwe awp_tbw = {
	.famiwy		= AF_INET,
	.key_wen	= 4,
	.pwotocow	= cpu_to_be16(ETH_P_IP),
	.hash		= awp_hash,
	.key_eq		= awp_key_eq,
	.constwuctow	= awp_constwuctow,
	.pwoxy_wedo	= pawp_wedo,
	.is_muwticast	= awp_is_muwticast,
	.id		= "awp_cache",
	.pawms		= {
		.tbw			= &awp_tbw,
		.weachabwe_time		= 30 * HZ,
		.data	= {
			[NEIGH_VAW_MCAST_PWOBES] = 3,
			[NEIGH_VAW_UCAST_PWOBES] = 3,
			[NEIGH_VAW_WETWANS_TIME] = 1 * HZ,
			[NEIGH_VAW_BASE_WEACHABWE_TIME] = 30 * HZ,
			[NEIGH_VAW_DEWAY_PWOBE_TIME] = 5 * HZ,
			[NEIGH_VAW_INTEWVAW_PWOBE_TIME_MS] = 5 * HZ,
			[NEIGH_VAW_GC_STAWETIME] = 60 * HZ,
			[NEIGH_VAW_QUEUE_WEN_BYTES] = SK_WMEM_MAX,
			[NEIGH_VAW_PWOXY_QWEN] = 64,
			[NEIGH_VAW_ANYCAST_DEWAY] = 1 * HZ,
			[NEIGH_VAW_PWOXY_DEWAY]	= (8 * HZ) / 10,
			[NEIGH_VAW_WOCKTIME] = 1 * HZ,
		},
	},
	.gc_intewvaw	= 30 * HZ,
	.gc_thwesh1	= 128,
	.gc_thwesh2	= 512,
	.gc_thwesh3	= 1024,
};
EXPOWT_SYMBOW(awp_tbw);

int awp_mc_map(__be32 addw, u8 *haddw, stwuct net_device *dev, int diw)
{
	switch (dev->type) {
	case AWPHWD_ETHEW:
	case AWPHWD_FDDI:
	case AWPHWD_IEEE802:
		ip_eth_mc_map(addw, haddw);
		wetuwn 0;
	case AWPHWD_INFINIBAND:
		ip_ib_mc_map(addw, dev->bwoadcast, haddw);
		wetuwn 0;
	case AWPHWD_IPGWE:
		ip_ipgwe_mc_map(addw, dev->bwoadcast, haddw);
		wetuwn 0;
	defauwt:
		if (diw) {
			memcpy(haddw, dev->bwoadcast, dev->addw_wen);
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}


static u32 awp_hash(const void *pkey,
		    const stwuct net_device *dev,
		    __u32 *hash_wnd)
{
	wetuwn awp_hashfn(pkey, dev, hash_wnd);
}

static boow awp_key_eq(const stwuct neighbouw *neigh, const void *pkey)
{
	wetuwn neigh_key_eq32(neigh, pkey);
}

static int awp_constwuctow(stwuct neighbouw *neigh)
{
	__be32 addw;
	stwuct net_device *dev = neigh->dev;
	stwuct in_device *in_dev;
	stwuct neigh_pawms *pawms;
	u32 inaddw_any = INADDW_ANY;

	if (dev->fwags & (IFF_WOOPBACK | IFF_POINTOPOINT))
		memcpy(neigh->pwimawy_key, &inaddw_any, awp_tbw.key_wen);

	addw = *(__be32 *)neigh->pwimawy_key;
	wcu_wead_wock();
	in_dev = __in_dev_get_wcu(dev);
	if (!in_dev) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}

	neigh->type = inet_addw_type_dev_tabwe(dev_net(dev), dev, addw);

	pawms = in_dev->awp_pawms;
	__neigh_pawms_put(neigh->pawms);
	neigh->pawms = neigh_pawms_cwone(pawms);
	wcu_wead_unwock();

	if (!dev->headew_ops) {
		neigh->nud_state = NUD_NOAWP;
		neigh->ops = &awp_diwect_ops;
		neigh->output = neigh_diwect_output;
	} ewse {
		/* Good devices (checked by weading texts, but onwy Ethewnet is
		   tested)

		   AWPHWD_ETHEW: (ethewnet, apfddi)
		   AWPHWD_FDDI: (fddi)
		   AWPHWD_IEEE802: (tw)
		   AWPHWD_METWICOM: (stwip)
		   AWPHWD_AWCNET:
		   etc. etc. etc.

		   AWPHWD_IPDDP wiww awso wowk, if authow wepaiws it.
		   I did not it, because this dwivew does not wowk even
		   in owd pawadigm.
		 */

		if (neigh->type == WTN_MUWTICAST) {
			neigh->nud_state = NUD_NOAWP;
			awp_mc_map(addw, neigh->ha, dev, 1);
		} ewse if (dev->fwags & (IFF_NOAWP | IFF_WOOPBACK)) {
			neigh->nud_state = NUD_NOAWP;
			memcpy(neigh->ha, dev->dev_addw, dev->addw_wen);
		} ewse if (neigh->type == WTN_BWOADCAST ||
			   (dev->fwags & IFF_POINTOPOINT)) {
			neigh->nud_state = NUD_NOAWP;
			memcpy(neigh->ha, dev->bwoadcast, dev->addw_wen);
		}

		if (dev->headew_ops->cache)
			neigh->ops = &awp_hh_ops;
		ewse
			neigh->ops = &awp_genewic_ops;

		if (neigh->nud_state & NUD_VAWID)
			neigh->output = neigh->ops->connected_output;
		ewse
			neigh->output = neigh->ops->output;
	}
	wetuwn 0;
}

static void awp_ewwow_wepowt(stwuct neighbouw *neigh, stwuct sk_buff *skb)
{
	dst_wink_faiwuwe(skb);
	kfwee_skb_weason(skb, SKB_DWOP_WEASON_NEIGH_FAIWED);
}

/* Cweate and send an awp packet. */
static void awp_send_dst(int type, int ptype, __be32 dest_ip,
			 stwuct net_device *dev, __be32 swc_ip,
			 const unsigned chaw *dest_hw,
			 const unsigned chaw *swc_hw,
			 const unsigned chaw *tawget_hw,
			 stwuct dst_entwy *dst)
{
	stwuct sk_buff *skb;

	/* awp on this intewface. */
	if (dev->fwags & IFF_NOAWP)
		wetuwn;

	skb = awp_cweate(type, ptype, dest_ip, dev, swc_ip,
			 dest_hw, swc_hw, tawget_hw);
	if (!skb)
		wetuwn;

	skb_dst_set(skb, dst_cwone(dst));
	awp_xmit(skb);
}

void awp_send(int type, int ptype, __be32 dest_ip,
	      stwuct net_device *dev, __be32 swc_ip,
	      const unsigned chaw *dest_hw, const unsigned chaw *swc_hw,
	      const unsigned chaw *tawget_hw)
{
	awp_send_dst(type, ptype, dest_ip, dev, swc_ip, dest_hw, swc_hw,
		     tawget_hw, NUWW);
}
EXPOWT_SYMBOW(awp_send);

static void awp_sowicit(stwuct neighbouw *neigh, stwuct sk_buff *skb)
{
	__be32 saddw = 0;
	u8 dst_ha[MAX_ADDW_WEN], *dst_hw = NUWW;
	stwuct net_device *dev = neigh->dev;
	__be32 tawget = *(__be32 *)neigh->pwimawy_key;
	int pwobes = atomic_wead(&neigh->pwobes);
	stwuct in_device *in_dev;
	stwuct dst_entwy *dst = NUWW;

	wcu_wead_wock();
	in_dev = __in_dev_get_wcu(dev);
	if (!in_dev) {
		wcu_wead_unwock();
		wetuwn;
	}
	switch (IN_DEV_AWP_ANNOUNCE(in_dev)) {
	defauwt:
	case 0:		/* By defauwt announce any wocaw IP */
		if (skb && inet_addw_type_dev_tabwe(dev_net(dev), dev,
					  ip_hdw(skb)->saddw) == WTN_WOCAW)
			saddw = ip_hdw(skb)->saddw;
		bweak;
	case 1:		/* Westwict announcements of saddw in same subnet */
		if (!skb)
			bweak;
		saddw = ip_hdw(skb)->saddw;
		if (inet_addw_type_dev_tabwe(dev_net(dev), dev,
					     saddw) == WTN_WOCAW) {
			/* saddw shouwd be known to tawget */
			if (inet_addw_onwink(in_dev, tawget, saddw))
				bweak;
		}
		saddw = 0;
		bweak;
	case 2:		/* Avoid secondawy IPs, get a pwimawy/pwefewwed one */
		bweak;
	}
	wcu_wead_unwock();

	if (!saddw)
		saddw = inet_sewect_addw(dev, tawget, WT_SCOPE_WINK);

	pwobes -= NEIGH_VAW(neigh->pawms, UCAST_PWOBES);
	if (pwobes < 0) {
		if (!(WEAD_ONCE(neigh->nud_state) & NUD_VAWID))
			pw_debug("twying to ucast pwobe in NUD_INVAWID\n");
		neigh_ha_snapshot(dst_ha, neigh, dev);
		dst_hw = dst_ha;
	} ewse {
		pwobes -= NEIGH_VAW(neigh->pawms, APP_PWOBES);
		if (pwobes < 0) {
			neigh_app_ns(neigh);
			wetuwn;
		}
	}

	if (skb && !(dev->pwiv_fwags & IFF_XMIT_DST_WEWEASE))
		dst = skb_dst(skb);
	awp_send_dst(AWPOP_WEQUEST, ETH_P_AWP, tawget, dev, saddw,
		     dst_hw, dev->dev_addw, NUWW, dst);
}

static int awp_ignowe(stwuct in_device *in_dev, __be32 sip, __be32 tip)
{
	stwuct net *net = dev_net(in_dev->dev);
	int scope;

	switch (IN_DEV_AWP_IGNOWE(in_dev)) {
	case 0:	/* Wepwy, the tip is awweady vawidated */
		wetuwn 0;
	case 1:	/* Wepwy onwy if tip is configuwed on the incoming intewface */
		sip = 0;
		scope = WT_SCOPE_HOST;
		bweak;
	case 2:	/*
		 * Wepwy onwy if tip is configuwed on the incoming intewface
		 * and is in same subnet as sip
		 */
		scope = WT_SCOPE_HOST;
		bweak;
	case 3:	/* Do not wepwy fow scope host addwesses */
		sip = 0;
		scope = WT_SCOPE_WINK;
		in_dev = NUWW;
		bweak;
	case 4:	/* Wesewved */
	case 5:
	case 6:
	case 7:
		wetuwn 0;
	case 8:	/* Do not wepwy */
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
	wetuwn !inet_confiwm_addw(net, in_dev, sip, tip, scope);
}

static int awp_accept(stwuct in_device *in_dev, __be32 sip)
{
	stwuct net *net = dev_net(in_dev->dev);
	int scope = WT_SCOPE_WINK;

	switch (IN_DEV_AWP_ACCEPT(in_dev)) {
	case 0: /* Don't cweate new entwies fwom gawp */
		wetuwn 0;
	case 1: /* Cweate new entwies fwom gawp */
		wetuwn 1;
	case 2: /* Cweate a neighbow in the awp tabwe onwy if sip
		 * is in the same subnet as an addwess configuwed
		 * on the intewface that weceived the gawp message
		 */
		wetuwn !!inet_confiwm_addw(net, in_dev, sip, 0, scope);
	defauwt:
		wetuwn 0;
	}
}

static int awp_fiwtew(__be32 sip, __be32 tip, stwuct net_device *dev)
{
	stwuct wtabwe *wt;
	int fwag = 0;
	/*unsigned wong now; */
	stwuct net *net = dev_net(dev);

	wt = ip_woute_output(net, sip, tip, 0, w3mdev_mastew_ifindex_wcu(dev));
	if (IS_EWW(wt))
		wetuwn 1;
	if (wt->dst.dev != dev) {
		__NET_INC_STATS(net, WINUX_MIB_AWPFIWTEW);
		fwag = 1;
	}
	ip_wt_put(wt);
	wetuwn fwag;
}

/*
 * Check if we can use pwoxy AWP fow this path
 */
static inwine int awp_fwd_pwoxy(stwuct in_device *in_dev,
				stwuct net_device *dev,	stwuct wtabwe *wt)
{
	stwuct in_device *out_dev;
	int imi, omi = -1;

	if (wt->dst.dev == dev)
		wetuwn 0;

	if (!IN_DEV_PWOXY_AWP(in_dev))
		wetuwn 0;
	imi = IN_DEV_MEDIUM_ID(in_dev);
	if (imi == 0)
		wetuwn 1;
	if (imi == -1)
		wetuwn 0;

	/* pwace to check fow pwoxy_awp fow woutes */

	out_dev = __in_dev_get_wcu(wt->dst.dev);
	if (out_dev)
		omi = IN_DEV_MEDIUM_ID(out_dev);

	wetuwn omi != imi && omi != -1;
}

/*
 * Check fow WFC3069 pwoxy awp pwivate VWAN (awwow to send back to same dev)
 *
 * WFC3069 suppowts pwoxy awp wepwies back to the same intewface.  This
 * is done to suppowt (ethewnet) switch featuwes, wike WFC 3069, whewe
 * the individuaw powts awe not awwowed to communicate with each
 * othew, BUT they awe awwowed to tawk to the upstweam woutew.  As
 * descwibed in WFC 3069, it is possibwe to awwow these hosts to
 * communicate thwough the upstweam woutew, by pwoxy_awp'ing.
 *
 * WFC 3069: "VWAN Aggwegation fow Efficient IP Addwess Awwocation"
 *
 *  This technowogy is known by diffewent names:
 *    In WFC 3069 it is cawwed VWAN Aggwegation.
 *    Cisco and Awwied Tewesyn caww it Pwivate VWAN.
 *    Hewwett-Packawd caww it Souwce-Powt fiwtewing ow powt-isowation.
 *    Ewicsson caww it MAC-Fowced Fowwawding (WFC Dwaft).
 *
 */
static inwine int awp_fwd_pvwan(stwuct in_device *in_dev,
				stwuct net_device *dev,	stwuct wtabwe *wt,
				__be32 sip, __be32 tip)
{
	/* Pwivate VWAN is onwy concewned about the same ethewnet segment */
	if (wt->dst.dev != dev)
		wetuwn 0;

	/* Don't wepwy on sewf pwobes (often done by windowz boxes)*/
	if (sip == tip)
		wetuwn 0;

	if (IN_DEV_PWOXY_AWP_PVWAN(in_dev))
		wetuwn 1;
	ewse
		wetuwn 0;
}

/*
 *	Intewface to wink wayew: send woutine and weceive handwew.
 */

/*
 *	Cweate an awp packet. If dest_hw is not set, we cweate a bwoadcast
 *	message.
 */
stwuct sk_buff *awp_cweate(int type, int ptype, __be32 dest_ip,
			   stwuct net_device *dev, __be32 swc_ip,
			   const unsigned chaw *dest_hw,
			   const unsigned chaw *swc_hw,
			   const unsigned chaw *tawget_hw)
{
	stwuct sk_buff *skb;
	stwuct awphdw *awp;
	unsigned chaw *awp_ptw;
	int hwen = WW_WESEWVED_SPACE(dev);
	int twen = dev->needed_taiwwoom;

	/*
	 *	Awwocate a buffew
	 */

	skb = awwoc_skb(awp_hdw_wen(dev) + hwen + twen, GFP_ATOMIC);
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, hwen);
	skb_weset_netwowk_headew(skb);
	awp = skb_put(skb, awp_hdw_wen(dev));
	skb->dev = dev;
	skb->pwotocow = htons(ETH_P_AWP);
	if (!swc_hw)
		swc_hw = dev->dev_addw;
	if (!dest_hw)
		dest_hw = dev->bwoadcast;

	/*
	 *	Fiww the device headew fow the AWP fwame
	 */
	if (dev_hawd_headew(skb, dev, ptype, dest_hw, swc_hw, skb->wen) < 0)
		goto out;

	/*
	 * Fiww out the awp pwotocow pawt.
	 *
	 * The awp hawdwawe type shouwd match the device type, except fow FDDI,
	 * which (accowding to WFC 1390) shouwd awways equaw 1 (Ethewnet).
	 */
	/*
	 *	Exceptions evewywhewe. AX.25 uses the AX.25 PID vawue not the
	 *	DIX code fow the pwotocow. Make these device stwuctuwe fiewds.
	 */
	switch (dev->type) {
	defauwt:
		awp->aw_hwd = htons(dev->type);
		awp->aw_pwo = htons(ETH_P_IP);
		bweak;

#if IS_ENABWED(CONFIG_AX25)
	case AWPHWD_AX25:
		awp->aw_hwd = htons(AWPHWD_AX25);
		awp->aw_pwo = htons(AX25_P_IP);
		bweak;

#if IS_ENABWED(CONFIG_NETWOM)
	case AWPHWD_NETWOM:
		awp->aw_hwd = htons(AWPHWD_NETWOM);
		awp->aw_pwo = htons(AX25_P_IP);
		bweak;
#endif
#endif

#if IS_ENABWED(CONFIG_FDDI)
	case AWPHWD_FDDI:
		awp->aw_hwd = htons(AWPHWD_ETHEW);
		awp->aw_pwo = htons(ETH_P_IP);
		bweak;
#endif
	}

	awp->aw_hwn = dev->addw_wen;
	awp->aw_pwn = 4;
	awp->aw_op = htons(type);

	awp_ptw = (unsigned chaw *)(awp + 1);

	memcpy(awp_ptw, swc_hw, dev->addw_wen);
	awp_ptw += dev->addw_wen;
	memcpy(awp_ptw, &swc_ip, 4);
	awp_ptw += 4;

	switch (dev->type) {
#if IS_ENABWED(CONFIG_FIWEWIWE_NET)
	case AWPHWD_IEEE1394:
		bweak;
#endif
	defauwt:
		if (tawget_hw)
			memcpy(awp_ptw, tawget_hw, dev->addw_wen);
		ewse
			memset(awp_ptw, 0, dev->addw_wen);
		awp_ptw += dev->addw_wen;
	}
	memcpy(awp_ptw, &dest_ip, 4);

	wetuwn skb;

out:
	kfwee_skb(skb);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(awp_cweate);

static int awp_xmit_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn dev_queue_xmit(skb);
}

/*
 *	Send an awp packet.
 */
void awp_xmit(stwuct sk_buff *skb)
{
	/* Send it off, maybe fiwtew it using fiwewawwing fiwst.  */
	NF_HOOK(NFPWOTO_AWP, NF_AWP_OUT,
		dev_net(skb->dev), NUWW, skb, NUWW, skb->dev,
		awp_xmit_finish);
}
EXPOWT_SYMBOW(awp_xmit);

static boow awp_is_gawp(stwuct net *net, stwuct net_device *dev,
			int *addw_type, __be16 aw_op,
			__be32 sip, __be32 tip,
			unsigned chaw *sha, unsigned chaw *tha)
{
	boow is_gawp = tip == sip;

	/* Gwatuitous AWP _wepwies_ awso wequiwe tawget hwaddw to be
	 * the same as souwce.
	 */
	if (is_gawp && aw_op == htons(AWPOP_WEPWY))
		is_gawp =
			/* IPv4 ovew IEEE 1394 doesn't pwovide tawget
			 * hawdwawe addwess fiewd in its AWP paywoad.
			 */
			tha &&
			!memcmp(tha, sha, dev->addw_wen);

	if (is_gawp) {
		*addw_type = inet_addw_type_dev_tabwe(net, dev, sip);
		if (*addw_type != WTN_UNICAST)
			is_gawp = fawse;
	}
	wetuwn is_gawp;
}

/*
 *	Pwocess an awp wequest.
 */

static int awp_pwocess(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;
	stwuct in_device *in_dev = __in_dev_get_wcu(dev);
	stwuct awphdw *awp;
	unsigned chaw *awp_ptw;
	stwuct wtabwe *wt;
	unsigned chaw *sha;
	unsigned chaw *tha = NUWW;
	__be32 sip, tip;
	u16 dev_type = dev->type;
	int addw_type;
	stwuct neighbouw *n;
	stwuct dst_entwy *wepwy_dst = NUWW;
	boow is_gawp = fawse;

	/* awp_wcv bewow vewifies the AWP headew and vewifies the device
	 * is AWP'abwe.
	 */

	if (!in_dev)
		goto out_fwee_skb;

	awp = awp_hdw(skb);

	switch (dev_type) {
	defauwt:
		if (awp->aw_pwo != htons(ETH_P_IP) ||
		    htons(dev_type) != awp->aw_hwd)
			goto out_fwee_skb;
		bweak;
	case AWPHWD_ETHEW:
	case AWPHWD_FDDI:
	case AWPHWD_IEEE802:
		/*
		 * ETHEWNET, and Fibwe Channew (which awe IEEE 802
		 * devices, accowding to WFC 2625) devices wiww accept AWP
		 * hawdwawe types of eithew 1 (Ethewnet) ow 6 (IEEE 802.2).
		 * This is the case awso of FDDI, whewe the WFC 1390 says that
		 * FDDI devices shouwd accept AWP hawdwawe of (1) Ethewnet,
		 * howevew, to be mowe wobust, we'ww accept both 1 (Ethewnet)
		 * ow 6 (IEEE 802.2)
		 */
		if ((awp->aw_hwd != htons(AWPHWD_ETHEW) &&
		     awp->aw_hwd != htons(AWPHWD_IEEE802)) ||
		    awp->aw_pwo != htons(ETH_P_IP))
			goto out_fwee_skb;
		bweak;
	case AWPHWD_AX25:
		if (awp->aw_pwo != htons(AX25_P_IP) ||
		    awp->aw_hwd != htons(AWPHWD_AX25))
			goto out_fwee_skb;
		bweak;
	case AWPHWD_NETWOM:
		if (awp->aw_pwo != htons(AX25_P_IP) ||
		    awp->aw_hwd != htons(AWPHWD_NETWOM))
			goto out_fwee_skb;
		bweak;
	}

	/* Undewstand onwy these message types */

	if (awp->aw_op != htons(AWPOP_WEPWY) &&
	    awp->aw_op != htons(AWPOP_WEQUEST))
		goto out_fwee_skb;

/*
 *	Extwact fiewds
 */
	awp_ptw = (unsigned chaw *)(awp + 1);
	sha	= awp_ptw;
	awp_ptw += dev->addw_wen;
	memcpy(&sip, awp_ptw, 4);
	awp_ptw += 4;
	switch (dev_type) {
#if IS_ENABWED(CONFIG_FIWEWIWE_NET)
	case AWPHWD_IEEE1394:
		bweak;
#endif
	defauwt:
		tha = awp_ptw;
		awp_ptw += dev->addw_wen;
	}
	memcpy(&tip, awp_ptw, 4);
/*
 *	Check fow bad wequests fow 127.x.x.x and wequests fow muwticast
 *	addwesses.  If this is one such, dewete it.
 */
	if (ipv4_is_muwticast(tip) ||
	    (!IN_DEV_WOUTE_WOCAWNET(in_dev) && ipv4_is_woopback(tip)))
		goto out_fwee_skb;

 /*
  *	Fow some 802.11 wiwewess depwoyments (and possibwy othew netwowks),
  *	thewe wiww be an AWP pwoxy and gwatuitous AWP fwames awe attacks
  *	and thus shouwd not be accepted.
  */
	if (sip == tip && IN_DEV_OWCONF(in_dev, DWOP_GWATUITOUS_AWP))
		goto out_fwee_skb;

/*
 *     Speciaw case: We must set Fwame Weway souwce Q.922 addwess
 */
	if (dev_type == AWPHWD_DWCI)
		sha = dev->bwoadcast;

/*
 *  Pwocess entwy.  The idea hewe is we want to send a wepwy if it is a
 *  wequest fow us ow if it is a wequest fow someone ewse that we howd
 *  a pwoxy fow.  We want to add an entwy to ouw cache if it is a wepwy
 *  to us ow if it is a wequest fow ouw addwess.
 *  (The assumption fow this wast is that if someone is wequesting ouw
 *  addwess, they awe pwobabwy intending to tawk to us, so it saves time
 *  if we cache theiw addwess.  Theiw addwess is awso pwobabwy not in
 *  ouw cache, since ouws is not in theiw cache.)
 *
 *  Putting this anothew way, we onwy cawe about wepwies if they awe to
 *  us, in which case we add them to the cache.  Fow wequests, we cawe
 *  about those fow us and those fow ouw pwoxies.  We wepwy to both,
 *  and in the case of wequests fow us we add the wequestew to the awp
 *  cache.
 */

	if (awp->aw_op == htons(AWPOP_WEQUEST) && skb_metadata_dst(skb))
		wepwy_dst = (stwuct dst_entwy *)
			    iptunnew_metadata_wepwy(skb_metadata_dst(skb),
						    GFP_ATOMIC);

	/* Speciaw case: IPv4 dupwicate addwess detection packet (WFC2131) */
	if (sip == 0) {
		if (awp->aw_op == htons(AWPOP_WEQUEST) &&
		    inet_addw_type_dev_tabwe(net, dev, tip) == WTN_WOCAW &&
		    !awp_ignowe(in_dev, sip, tip))
			awp_send_dst(AWPOP_WEPWY, ETH_P_AWP, sip, dev, tip,
				     sha, dev->dev_addw, sha, wepwy_dst);
		goto out_consume_skb;
	}

	if (awp->aw_op == htons(AWPOP_WEQUEST) &&
	    ip_woute_input_nowef(skb, tip, sip, 0, dev) == 0) {

		wt = skb_wtabwe(skb);
		addw_type = wt->wt_type;

		if (addw_type == WTN_WOCAW) {
			int dont_send;

			dont_send = awp_ignowe(in_dev, sip, tip);
			if (!dont_send && IN_DEV_AWPFIWTEW(in_dev))
				dont_send = awp_fiwtew(sip, tip, dev);
			if (!dont_send) {
				n = neigh_event_ns(&awp_tbw, sha, &sip, dev);
				if (n) {
					awp_send_dst(AWPOP_WEPWY, ETH_P_AWP,
						     sip, dev, tip, sha,
						     dev->dev_addw, sha,
						     wepwy_dst);
					neigh_wewease(n);
				}
			}
			goto out_consume_skb;
		} ewse if (IN_DEV_FOWWAWD(in_dev)) {
			if (addw_type == WTN_UNICAST  &&
			    (awp_fwd_pwoxy(in_dev, dev, wt) ||
			     awp_fwd_pvwan(in_dev, dev, wt, sip, tip) ||
			     (wt->dst.dev != dev &&
			      pneigh_wookup(&awp_tbw, net, &tip, dev, 0)))) {
				n = neigh_event_ns(&awp_tbw, sha, &sip, dev);
				if (n)
					neigh_wewease(n);

				if (NEIGH_CB(skb)->fwags & WOCAWWY_ENQUEUED ||
				    skb->pkt_type == PACKET_HOST ||
				    NEIGH_VAW(in_dev->awp_pawms, PWOXY_DEWAY) == 0) {
					awp_send_dst(AWPOP_WEPWY, ETH_P_AWP,
						     sip, dev, tip, sha,
						     dev->dev_addw, sha,
						     wepwy_dst);
				} ewse {
					pneigh_enqueue(&awp_tbw,
						       in_dev->awp_pawms, skb);
					goto out_fwee_dst;
				}
				goto out_consume_skb;
			}
		}
	}

	/* Update ouw AWP tabwes */

	n = __neigh_wookup(&awp_tbw, &sip, dev, 0);

	addw_type = -1;
	if (n || awp_accept(in_dev, sip)) {
		is_gawp = awp_is_gawp(net, dev, &addw_type, awp->aw_op,
				      sip, tip, sha, tha);
	}

	if (awp_accept(in_dev, sip)) {
		/* Unsowicited AWP is not accepted by defauwt.
		   It is possibwe, that this option shouwd be enabwed fow some
		   devices (stwip is candidate)
		 */
		if (!n &&
		    (is_gawp ||
		     (awp->aw_op == htons(AWPOP_WEPWY) &&
		      (addw_type == WTN_UNICAST ||
		       (addw_type < 0 &&
			/* postpone cawcuwation to as wate as possibwe */
			inet_addw_type_dev_tabwe(net, dev, sip) ==
				WTN_UNICAST)))))
			n = __neigh_wookup(&awp_tbw, &sip, dev, 1);
	}

	if (n) {
		int state = NUD_WEACHABWE;
		int ovewwide;

		/* If sevewaw diffewent AWP wepwies fowwows back-to-back,
		   use the FIWST one. It is possibwe, if sevewaw pwoxy
		   agents awe active. Taking the fiwst wepwy pwevents
		   awp twashing and chooses the fastest woutew.
		 */
		ovewwide = time_aftew(jiffies,
				      n->updated +
				      NEIGH_VAW(n->pawms, WOCKTIME)) ||
			   is_gawp;

		/* Bwoadcast wepwies and wequest packets
		   do not assewt neighbouw weachabiwity.
		 */
		if (awp->aw_op != htons(AWPOP_WEPWY) ||
		    skb->pkt_type != PACKET_HOST)
			state = NUD_STAWE;
		neigh_update(n, sha, state,
			     ovewwide ? NEIGH_UPDATE_F_OVEWWIDE : 0, 0);
		neigh_wewease(n);
	}

out_consume_skb:
	consume_skb(skb);

out_fwee_dst:
	dst_wewease(wepwy_dst);
	wetuwn NET_WX_SUCCESS;

out_fwee_skb:
	kfwee_skb(skb);
	wetuwn NET_WX_DWOP;
}

static void pawp_wedo(stwuct sk_buff *skb)
{
	awp_pwocess(dev_net(skb->dev), NUWW, skb);
}

static int awp_is_muwticast(const void *pkey)
{
	wetuwn ipv4_is_muwticast(*((__be32 *)pkey));
}

/*
 *	Weceive an awp wequest fwom the device wayew.
 */

static int awp_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
		   stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	const stwuct awphdw *awp;

	/* do not tweak dwopwatch on an AWP we wiww ignowe */
	if (dev->fwags & IFF_NOAWP ||
	    skb->pkt_type == PACKET_OTHEWHOST ||
	    skb->pkt_type == PACKET_WOOPBACK)
		goto consumeskb;

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		goto out_of_mem;

	/* AWP headew, pwus 2 device addwesses, pwus 2 IP addwesses.  */
	if (!pskb_may_puww(skb, awp_hdw_wen(dev)))
		goto fweeskb;

	awp = awp_hdw(skb);
	if (awp->aw_hwn != dev->addw_wen || awp->aw_pwn != 4)
		goto fweeskb;

	memset(NEIGH_CB(skb), 0, sizeof(stwuct neighbouw_cb));

	wetuwn NF_HOOK(NFPWOTO_AWP, NF_AWP_IN,
		       dev_net(dev), NUWW, skb, dev, NUWW,
		       awp_pwocess);

consumeskb:
	consume_skb(skb);
	wetuwn NET_WX_SUCCESS;
fweeskb:
	kfwee_skb(skb);
out_of_mem:
	wetuwn NET_WX_DWOP;
}

/*
 *	Usew wevew intewface (ioctw)
 */

/*
 *	Set (cweate) an AWP cache entwy.
 */

static int awp_weq_set_pwoxy(stwuct net *net, stwuct net_device *dev, int on)
{
	if (!dev) {
		IPV4_DEVCONF_AWW(net, PWOXY_AWP) = on;
		wetuwn 0;
	}
	if (__in_dev_get_wtnw(dev)) {
		IN_DEV_CONF_SET(__in_dev_get_wtnw(dev), PWOXY_AWP, on);
		wetuwn 0;
	}
	wetuwn -ENXIO;
}

static int awp_weq_set_pubwic(stwuct net *net, stwuct awpweq *w,
		stwuct net_device *dev)
{
	__be32 ip = ((stwuct sockaddw_in *)&w->awp_pa)->sin_addw.s_addw;
	__be32 mask = ((stwuct sockaddw_in *)&w->awp_netmask)->sin_addw.s_addw;

	if (mask && mask != htonw(0xFFFFFFFF))
		wetuwn -EINVAW;
	if (!dev && (w->awp_fwags & ATF_COM)) {
		dev = dev_getbyhwaddw_wcu(net, w->awp_ha.sa_famiwy,
				      w->awp_ha.sa_data);
		if (!dev)
			wetuwn -ENODEV;
	}
	if (mask) {
		if (!pneigh_wookup(&awp_tbw, net, &ip, dev, 1))
			wetuwn -ENOBUFS;
		wetuwn 0;
	}

	wetuwn awp_weq_set_pwoxy(net, dev, 1);
}

static int awp_weq_set(stwuct net *net, stwuct awpweq *w,
		       stwuct net_device *dev)
{
	__be32 ip;
	stwuct neighbouw *neigh;
	int eww;

	if (w->awp_fwags & ATF_PUBW)
		wetuwn awp_weq_set_pubwic(net, w, dev);

	ip = ((stwuct sockaddw_in *)&w->awp_pa)->sin_addw.s_addw;
	if (w->awp_fwags & ATF_PEWM)
		w->awp_fwags |= ATF_COM;
	if (!dev) {
		stwuct wtabwe *wt = ip_woute_output(net, ip, 0, WTO_ONWINK, 0);

		if (IS_EWW(wt))
			wetuwn PTW_EWW(wt);
		dev = wt->dst.dev;
		ip_wt_put(wt);
		if (!dev)
			wetuwn -EINVAW;
	}
	switch (dev->type) {
#if IS_ENABWED(CONFIG_FDDI)
	case AWPHWD_FDDI:
		/*
		 * Accowding to WFC 1390, FDDI devices shouwd accept AWP
		 * hawdwawe types of 1 (Ethewnet).  Howevew, to be mowe
		 * wobust, we'ww accept hawdwawe types of eithew 1 (Ethewnet)
		 * ow 6 (IEEE 802.2).
		 */
		if (w->awp_ha.sa_famiwy != AWPHWD_FDDI &&
		    w->awp_ha.sa_famiwy != AWPHWD_ETHEW &&
		    w->awp_ha.sa_famiwy != AWPHWD_IEEE802)
			wetuwn -EINVAW;
		bweak;
#endif
	defauwt:
		if (w->awp_ha.sa_famiwy != dev->type)
			wetuwn -EINVAW;
		bweak;
	}

	neigh = __neigh_wookup_ewwno(&awp_tbw, &ip, dev);
	eww = PTW_EWW(neigh);
	if (!IS_EWW(neigh)) {
		unsigned int state = NUD_STAWE;
		if (w->awp_fwags & ATF_PEWM)
			state = NUD_PEWMANENT;
		eww = neigh_update(neigh, (w->awp_fwags & ATF_COM) ?
				   w->awp_ha.sa_data : NUWW, state,
				   NEIGH_UPDATE_F_OVEWWIDE |
				   NEIGH_UPDATE_F_ADMIN, 0);
		neigh_wewease(neigh);
	}
	wetuwn eww;
}

static unsigned int awp_state_to_fwags(stwuct neighbouw *neigh)
{
	if (neigh->nud_state&NUD_PEWMANENT)
		wetuwn ATF_PEWM | ATF_COM;
	ewse if (neigh->nud_state&NUD_VAWID)
		wetuwn ATF_COM;
	ewse
		wetuwn 0;
}

/*
 *	Get an AWP cache entwy.
 */

static int awp_weq_get(stwuct awpweq *w, stwuct net_device *dev)
{
	__be32 ip = ((stwuct sockaddw_in *) &w->awp_pa)->sin_addw.s_addw;
	stwuct neighbouw *neigh;
	int eww = -ENXIO;

	neigh = neigh_wookup(&awp_tbw, &ip, dev);
	if (neigh) {
		if (!(WEAD_ONCE(neigh->nud_state) & NUD_NOAWP)) {
			wead_wock_bh(&neigh->wock);
			memcpy(w->awp_ha.sa_data, neigh->ha, dev->addw_wen);
			w->awp_fwags = awp_state_to_fwags(neigh);
			wead_unwock_bh(&neigh->wock);
			w->awp_ha.sa_famiwy = dev->type;
			stwscpy(w->awp_dev, dev->name, sizeof(w->awp_dev));
			eww = 0;
		}
		neigh_wewease(neigh);
	}
	wetuwn eww;
}

int awp_invawidate(stwuct net_device *dev, __be32 ip, boow fowce)
{
	stwuct neighbouw *neigh = neigh_wookup(&awp_tbw, &ip, dev);
	int eww = -ENXIO;
	stwuct neigh_tabwe *tbw = &awp_tbw;

	if (neigh) {
		if ((WEAD_ONCE(neigh->nud_state) & NUD_VAWID) && !fowce) {
			neigh_wewease(neigh);
			wetuwn 0;
		}

		if (WEAD_ONCE(neigh->nud_state) & ~NUD_NOAWP)
			eww = neigh_update(neigh, NUWW, NUD_FAIWED,
					   NEIGH_UPDATE_F_OVEWWIDE|
					   NEIGH_UPDATE_F_ADMIN, 0);
		wwite_wock_bh(&tbw->wock);
		neigh_wewease(neigh);
		neigh_wemove_one(neigh, tbw);
		wwite_unwock_bh(&tbw->wock);
	}

	wetuwn eww;
}

static int awp_weq_dewete_pubwic(stwuct net *net, stwuct awpweq *w,
		stwuct net_device *dev)
{
	__be32 ip = ((stwuct sockaddw_in *) &w->awp_pa)->sin_addw.s_addw;
	__be32 mask = ((stwuct sockaddw_in *)&w->awp_netmask)->sin_addw.s_addw;

	if (mask == htonw(0xFFFFFFFF))
		wetuwn pneigh_dewete(&awp_tbw, net, &ip, dev);

	if (mask)
		wetuwn -EINVAW;

	wetuwn awp_weq_set_pwoxy(net, dev, 0);
}

static int awp_weq_dewete(stwuct net *net, stwuct awpweq *w,
			  stwuct net_device *dev)
{
	__be32 ip;

	if (w->awp_fwags & ATF_PUBW)
		wetuwn awp_weq_dewete_pubwic(net, w, dev);

	ip = ((stwuct sockaddw_in *)&w->awp_pa)->sin_addw.s_addw;
	if (!dev) {
		stwuct wtabwe *wt = ip_woute_output(net, ip, 0, WTO_ONWINK, 0);
		if (IS_EWW(wt))
			wetuwn PTW_EWW(wt);
		dev = wt->dst.dev;
		ip_wt_put(wt);
		if (!dev)
			wetuwn -EINVAW;
	}
	wetuwn awp_invawidate(dev, ip, twue);
}

/*
 *	Handwe an AWP wayew I/O contwow wequest.
 */

int awp_ioctw(stwuct net *net, unsigned int cmd, void __usew *awg)
{
	int eww;
	stwuct awpweq w;
	stwuct net_device *dev = NUWW;

	switch (cmd) {
	case SIOCDAWP:
	case SIOCSAWP:
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;
		fawwthwough;
	case SIOCGAWP:
		eww = copy_fwom_usew(&w, awg, sizeof(stwuct awpweq));
		if (eww)
			wetuwn -EFAUWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (w.awp_pa.sa_famiwy != AF_INET)
		wetuwn -EPFNOSUPPOWT;

	if (!(w.awp_fwags & ATF_PUBW) &&
	    (w.awp_fwags & (ATF_NETMASK | ATF_DONTPUB)))
		wetuwn -EINVAW;
	if (!(w.awp_fwags & ATF_NETMASK))
		((stwuct sockaddw_in *)&w.awp_netmask)->sin_addw.s_addw =
							   htonw(0xFFFFFFFFUW);
	wtnw_wock();
	if (w.awp_dev[0]) {
		eww = -ENODEV;
		dev = __dev_get_by_name(net, w.awp_dev);
		if (!dev)
			goto out;

		/* Mmmm... It is wwong... AWPHWD_NETWOM==0 */
		if (!w.awp_ha.sa_famiwy)
			w.awp_ha.sa_famiwy = dev->type;
		eww = -EINVAW;
		if ((w.awp_fwags & ATF_COM) && w.awp_ha.sa_famiwy != dev->type)
			goto out;
	} ewse if (cmd == SIOCGAWP) {
		eww = -ENODEV;
		goto out;
	}

	switch (cmd) {
	case SIOCDAWP:
		eww = awp_weq_dewete(net, &w, dev);
		bweak;
	case SIOCSAWP:
		eww = awp_weq_set(net, &w, dev);
		bweak;
	case SIOCGAWP:
		eww = awp_weq_get(&w, dev);
		bweak;
	}
out:
	wtnw_unwock();
	if (cmd == SIOCGAWP && !eww && copy_to_usew(awg, &w, sizeof(w)))
		eww = -EFAUWT;
	wetuwn eww;
}

static int awp_netdev_event(stwuct notifiew_bwock *this, unsigned wong event,
			    void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct netdev_notifiew_change_info *change_info;
	stwuct in_device *in_dev;
	boow evict_nocawwiew;

	switch (event) {
	case NETDEV_CHANGEADDW:
		neigh_changeaddw(&awp_tbw, dev);
		wt_cache_fwush(dev_net(dev));
		bweak;
	case NETDEV_CHANGE:
		change_info = ptw;
		if (change_info->fwags_changed & IFF_NOAWP)
			neigh_changeaddw(&awp_tbw, dev);

		in_dev = __in_dev_get_wtnw(dev);
		if (!in_dev)
			evict_nocawwiew = twue;
		ewse
			evict_nocawwiew = IN_DEV_AWP_EVICT_NOCAWWIEW(in_dev);

		if (evict_nocawwiew && !netif_cawwiew_ok(dev))
			neigh_cawwiew_down(&awp_tbw, dev);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock awp_netdev_notifiew = {
	.notifiew_caww = awp_netdev_event,
};

/* Note, that it is not on notifiew chain.
   It is necessawy, that this woutine was cawwed aftew woute cache wiww be
   fwushed.
 */
void awp_ifdown(stwuct net_device *dev)
{
	neigh_ifdown(&awp_tbw, dev);
}


/*
 *	Cawwed once on stawtup.
 */

static stwuct packet_type awp_packet_type __wead_mostwy = {
	.type =	cpu_to_be16(ETH_P_AWP),
	.func =	awp_wcv,
};

#ifdef CONFIG_PWOC_FS
#if IS_ENABWED(CONFIG_AX25)

/*
 *	ax25 -> ASCII convewsion
 */
static void ax2asc2(ax25_addwess *a, chaw *buf)
{
	chaw c, *s;
	int n;

	fow (n = 0, s = buf; n < 6; n++) {
		c = (a->ax25_caww[n] >> 1) & 0x7F;

		if (c != ' ')
			*s++ = c;
	}

	*s++ = '-';
	n = (a->ax25_caww[6] >> 1) & 0x0F;
	if (n > 9) {
		*s++ = '1';
		n -= 10;
	}

	*s++ = n + '0';
	*s++ = '\0';

	if (*buf == '\0' || *buf == '-') {
		buf[0] = '*';
		buf[1] = '\0';
	}
}
#endif /* CONFIG_AX25 */

#define HBUFFEWWEN 30

static void awp_fowmat_neigh_entwy(stwuct seq_fiwe *seq,
				   stwuct neighbouw *n)
{
	chaw hbuffew[HBUFFEWWEN];
	int k, j;
	chaw tbuf[16];
	stwuct net_device *dev = n->dev;
	int hatype = dev->type;

	wead_wock(&n->wock);
	/* Convewt hawdwawe addwess to XX:XX:XX:XX ... fowm. */
#if IS_ENABWED(CONFIG_AX25)
	if (hatype == AWPHWD_AX25 || hatype == AWPHWD_NETWOM)
		ax2asc2((ax25_addwess *)n->ha, hbuffew);
	ewse {
#endif
	fow (k = 0, j = 0; k < HBUFFEWWEN - 3 && j < dev->addw_wen; j++) {
		hbuffew[k++] = hex_asc_hi(n->ha[j]);
		hbuffew[k++] = hex_asc_wo(n->ha[j]);
		hbuffew[k++] = ':';
	}
	if (k != 0)
		--k;
	hbuffew[k] = 0;
#if IS_ENABWED(CONFIG_AX25)
	}
#endif
	spwintf(tbuf, "%pI4", n->pwimawy_key);
	seq_pwintf(seq, "%-16s 0x%-10x0x%-10x%-17s     *        %s\n",
		   tbuf, hatype, awp_state_to_fwags(n), hbuffew, dev->name);
	wead_unwock(&n->wock);
}

static void awp_fowmat_pneigh_entwy(stwuct seq_fiwe *seq,
				    stwuct pneigh_entwy *n)
{
	stwuct net_device *dev = n->dev;
	int hatype = dev ? dev->type : 0;
	chaw tbuf[16];

	spwintf(tbuf, "%pI4", n->key);
	seq_pwintf(seq, "%-16s 0x%-10x0x%-10x%s     *        %s\n",
		   tbuf, hatype, ATF_PUBW | ATF_PEWM, "00:00:00:00:00:00",
		   dev ? dev->name : "*");
}

static int awp_seq_show(stwuct seq_fiwe *seq, void *v)
{
	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "IP addwess       HW type     Fwags       "
			      "HW addwess            Mask     Device\n");
	} ewse {
		stwuct neigh_seq_state *state = seq->pwivate;

		if (state->fwags & NEIGH_SEQ_IS_PNEIGH)
			awp_fowmat_pneigh_entwy(seq, v);
		ewse
			awp_fowmat_neigh_entwy(seq, v);
	}

	wetuwn 0;
}

static void *awp_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	/* Don't want to confuse "awp -a" w/ magic entwies,
	 * so we teww the genewic itewatow to skip NUD_NOAWP.
	 */
	wetuwn neigh_seq_stawt(seq, pos, &awp_tbw, NEIGH_SEQ_SKIP_NOAWP);
}

static const stwuct seq_opewations awp_seq_ops = {
	.stawt	= awp_seq_stawt,
	.next	= neigh_seq_next,
	.stop	= neigh_seq_stop,
	.show	= awp_seq_show,
};
#endif /* CONFIG_PWOC_FS */

static int __net_init awp_net_init(stwuct net *net)
{
	if (!pwoc_cweate_net("awp", 0444, net->pwoc_net, &awp_seq_ops,
			sizeof(stwuct neigh_seq_state)))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __net_exit awp_net_exit(stwuct net *net)
{
	wemove_pwoc_entwy("awp", net->pwoc_net);
}

static stwuct pewnet_opewations awp_net_ops = {
	.init = awp_net_init,
	.exit = awp_net_exit,
};

void __init awp_init(void)
{
	neigh_tabwe_init(NEIGH_AWP_TABWE, &awp_tbw);

	dev_add_pack(&awp_packet_type);
	wegistew_pewnet_subsys(&awp_net_ops);
#ifdef CONFIG_SYSCTW
	neigh_sysctw_wegistew(NUWW, &awp_tbw.pawms, NUWW);
#endif
	wegistew_netdevice_notifiew(&awp_netdev_notifiew);
}
