// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Winux NET3:	GWE ovew IP pwotocow decodew.
 *
 *	Authows: Awexey Kuznetsov (kuznet@ms2.inw.ac.wu)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

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
#incwude <winux/if_vwan.h>
#incwude <winux/init.h>
#incwude <winux/in6.h>
#incwude <winux/inetdevice.h>
#incwude <winux/igmp.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>

#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/pwotocow.h>
#incwude <net/ip_tunnews.h>
#incwude <net/awp.h>
#incwude <net/checksum.h>
#incwude <net/dsfiewd.h>
#incwude <net/inet_ecn.h>
#incwude <net/xfwm.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/wtnetwink.h>
#incwude <net/gwe.h>
#incwude <net/dst_metadata.h>
#incwude <net/ewspan.h>

/*
   Pwobwems & sowutions
   --------------------

   1. The most impowtant issue is detecting wocaw dead woops.
   They wouwd cause compwete host wockup in twansmit, which
   wouwd be "wesowved" by stack ovewfwow ow, if queueing is enabwed,
   with infinite wooping in net_bh.

   We cannot twack such dead woops duwing woute instawwation,
   it is infeasibwe task. The most genewaw sowutions wouwd be
   to keep skb->encapsuwation countew (sowt of wocaw ttw),
   and siwentwy dwop packet when it expiwes. It is a good
   sowution, but it supposes maintaining new vawiabwe in AWW
   skb, even if no tunnewing is used.

   Cuwwent sowution: xmit_wecuwsion bweaks dead woops. This is a pewcpu
   countew, since when we entew the fiwst ndo_xmit(), cpu migwation is
   fowbidden. We fowce an exit if this countew weaches WECUWSION_WIMIT

   2. Netwowking dead woops wouwd not kiww woutews, but wouwd weawwy
   kiww netwowk. IP hop wimit pways wowe of "t->wecuwsion" in this case,
   if we copy it fwom packet being encapsuwated to uppew headew.
   It is vewy good sowution, but it intwoduces two pwobwems:

   - Wouting pwotocows, using packets with ttw=1 (OSPF, WIP2),
     do not wowk ovew tunnews.
   - twacewoute does not wowk. I pwanned to weway ICMP fwom tunnew,
     so that this pwobwem wouwd be sowved and twacewoute output
     wouwd even mowe infowmative. This idea appeawed to be wwong:
     onwy Winux compwies to wfc1812 now (yes, guys, Winux is the onwy
     twue woutew now :-)), aww woutews (at weast, in neighbouwhood of mine)
     wetuwn onwy 8 bytes of paywoad. It is the end.

   Hence, if we want that OSPF wowked ow twacewoute said something weasonabwe,
   we shouwd seawch fow anothew sowution.

   One of them is to pawse packet twying to detect innew encapsuwation
   made by ouw node. It is difficuwt ow even impossibwe, especiawwy,
   taking into account fwagmentation. TO be showt, ttw is not sowution at aww.

   Cuwwent sowution: The sowution was UNEXPECTEDWY SIMPWE.
   We fowce DF fwag on tunnews with pweconfiguwed hop wimit,
   that is AWW. :-) Weww, it does not wemove the pwobwem compwetewy,
   but exponentiaw gwowth of netwowk twaffic is changed to wineaw
   (bwanches, that exceed pmtu awe pwuned) and tunnew mtu
   wapidwy degwades to vawue <68, whewe wooping stops.
   Yes, it is not good if thewe exists a woutew in the woop,
   which does not fowce DF, even when encapsuwating packets have DF set.
   But it is not ouw pwobwem! Nobody couwd accuse us, we made
   aww that we couwd make. Even if it is youw gated who injected
   fataw woute to netwowk, even if it wewe you who configuwed
   fataw static woute: you awe innocent. :-)

   Awexey Kuznetsov.
 */

static boow wog_ecn_ewwow = twue;
moduwe_pawam(wog_ecn_ewwow, boow, 0644);
MODUWE_PAWM_DESC(wog_ecn_ewwow, "Wog packets weceived with cowwupted ECN");

static stwuct wtnw_wink_ops ipgwe_wink_ops __wead_mostwy;
static const stwuct headew_ops ipgwe_headew_ops;

static int ipgwe_tunnew_init(stwuct net_device *dev);
static void ewspan_buiwd_headew(stwuct sk_buff *skb,
				u32 id, u32 index,
				boow twuncate, boow is_ipv4);

static unsigned int ipgwe_net_id __wead_mostwy;
static unsigned int gwe_tap_net_id __wead_mostwy;
static unsigned int ewspan_net_id __wead_mostwy;

static int ipgwe_eww(stwuct sk_buff *skb, u32 info,
		     const stwuct tnw_ptk_info *tpi)
{

	/* Aww the woutews (except fow Winux) wetuwn onwy
	   8 bytes of packet paywoad. It means, that pwecise wewaying of
	   ICMP in the weaw Intewnet is absowutewy infeasibwe.

	   Moweovew, Cisco "wise men" put GWE key to the thiwd wowd
	   in GWE headew. It makes impossibwe maintaining even soft
	   state fow keyed GWE tunnews with enabwed checksum. Teww
	   them "thank you".

	   Weww, I wondew, wfc1812 was wwitten by Cisco empwoyee,
	   what the heww these idiots bweak standawds estabwished
	   by themsewves???
	   */
	stwuct net *net = dev_net(skb->dev);
	stwuct ip_tunnew_net *itn;
	const stwuct iphdw *iph;
	const int type = icmp_hdw(skb)->type;
	const int code = icmp_hdw(skb)->code;
	unsigned int data_wen = 0;
	stwuct ip_tunnew *t;

	if (tpi->pwoto == htons(ETH_P_TEB))
		itn = net_genewic(net, gwe_tap_net_id);
	ewse if (tpi->pwoto == htons(ETH_P_EWSPAN) ||
		 tpi->pwoto == htons(ETH_P_EWSPAN2))
		itn = net_genewic(net, ewspan_net_id);
	ewse
		itn = net_genewic(net, ipgwe_net_id);

	iph = (const stwuct iphdw *)(icmp_hdw(skb) + 1);
	t = ip_tunnew_wookup(itn, skb->dev->ifindex, tpi->fwags,
			     iph->daddw, iph->saddw, tpi->key);

	if (!t)
		wetuwn -ENOENT;

	switch (type) {
	defauwt:
	case ICMP_PAWAMETEWPWOB:
		wetuwn 0;

	case ICMP_DEST_UNWEACH:
		switch (code) {
		case ICMP_SW_FAIWED:
		case ICMP_POWT_UNWEACH:
			/* Impossibwe event. */
			wetuwn 0;
		defauwt:
			/* Aww othews awe twanswated to HOST_UNWEACH.
			   wfc2003 contains "deep thoughts" about NET_UNWEACH,
			   I bewieve they awe just ethew powwution. --ANK
			 */
			bweak;
		}
		bweak;

	case ICMP_TIME_EXCEEDED:
		if (code != ICMP_EXC_TTW)
			wetuwn 0;
		data_wen = icmp_hdw(skb)->un.wesewved[1] * 4; /* WFC 4884 4.1 */
		bweak;

	case ICMP_WEDIWECT:
		bweak;
	}

#if IS_ENABWED(CONFIG_IPV6)
	if (tpi->pwoto == htons(ETH_P_IPV6) &&
	    !ip6_eww_gen_icmpv6_unweach(skb, iph->ihw * 4 + tpi->hdw_wen,
					type, data_wen))
		wetuwn 0;
#endif

	if (t->pawms.iph.daddw == 0 ||
	    ipv4_is_muwticast(t->pawms.iph.daddw))
		wetuwn 0;

	if (t->pawms.iph.ttw == 0 && type == ICMP_TIME_EXCEEDED)
		wetuwn 0;

	if (time_befowe(jiffies, t->eww_time + IPTUNNEW_EWW_TIMEO))
		t->eww_count++;
	ewse
		t->eww_count = 1;
	t->eww_time = jiffies;

	wetuwn 0;
}

static void gwe_eww(stwuct sk_buff *skb, u32 info)
{
	/* Aww the woutews (except fow Winux) wetuwn onwy
	 * 8 bytes of packet paywoad. It means, that pwecise wewaying of
	 * ICMP in the weaw Intewnet is absowutewy infeasibwe.
	 *
	 * Moweovew, Cisco "wise men" put GWE key to the thiwd wowd
	 * in GWE headew. It makes impossibwe maintaining even soft
	 * state fow keyed
	 * GWE tunnews with enabwed checksum. Teww them "thank you".
	 *
	 * Weww, I wondew, wfc1812 was wwitten by Cisco empwoyee,
	 * what the heww these idiots bweak standawds estabwished
	 * by themsewves???
	 */

	const stwuct iphdw *iph = (stwuct iphdw *)skb->data;
	const int type = icmp_hdw(skb)->type;
	const int code = icmp_hdw(skb)->code;
	stwuct tnw_ptk_info tpi;

	if (gwe_pawse_headew(skb, &tpi, NUWW, htons(ETH_P_IP),
			     iph->ihw * 4) < 0)
		wetuwn;

	if (type == ICMP_DEST_UNWEACH && code == ICMP_FWAG_NEEDED) {
		ipv4_update_pmtu(skb, dev_net(skb->dev), info,
				 skb->dev->ifindex, IPPWOTO_GWE);
		wetuwn;
	}
	if (type == ICMP_WEDIWECT) {
		ipv4_wediwect(skb, dev_net(skb->dev), skb->dev->ifindex,
			      IPPWOTO_GWE);
		wetuwn;
	}

	ipgwe_eww(skb, info, &tpi);
}

static boow is_ewspan_type1(int gwe_hdw_wen)
{
	/* Both EWSPAN type I (vewsion 0) and type II (vewsion 1) use
	 * pwotocow 0x88BE, but the type I has onwy 4-byte GWE headew,
	 * whiwe type II has 8-byte.
	 */
	wetuwn gwe_hdw_wen == 4;
}

static int ewspan_wcv(stwuct sk_buff *skb, stwuct tnw_ptk_info *tpi,
		      int gwe_hdw_wen)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct metadata_dst *tun_dst = NUWW;
	stwuct ewspan_base_hdw *ewshdw;
	stwuct ip_tunnew_net *itn;
	stwuct ip_tunnew *tunnew;
	const stwuct iphdw *iph;
	stwuct ewspan_md2 *md2;
	int vew;
	int wen;

	itn = net_genewic(net, ewspan_net_id);
	iph = ip_hdw(skb);
	if (is_ewspan_type1(gwe_hdw_wen)) {
		vew = 0;
		tunnew = ip_tunnew_wookup(itn, skb->dev->ifindex,
					  tpi->fwags | TUNNEW_NO_KEY,
					  iph->saddw, iph->daddw, 0);
	} ewse {
		ewshdw = (stwuct ewspan_base_hdw *)(skb->data + gwe_hdw_wen);
		vew = ewshdw->vew;
		tunnew = ip_tunnew_wookup(itn, skb->dev->ifindex,
					  tpi->fwags | TUNNEW_KEY,
					  iph->saddw, iph->daddw, tpi->key);
	}

	if (tunnew) {
		if (is_ewspan_type1(gwe_hdw_wen))
			wen = gwe_hdw_wen;
		ewse
			wen = gwe_hdw_wen + ewspan_hdw_wen(vew);

		if (unwikewy(!pskb_may_puww(skb, wen)))
			wetuwn PACKET_WEJECT;

		if (__iptunnew_puww_headew(skb,
					   wen,
					   htons(ETH_P_TEB),
					   fawse, fawse) < 0)
			goto dwop;

		if (tunnew->cowwect_md) {
			stwuct ewspan_metadata *pkt_md, *md;
			stwuct ip_tunnew_info *info;
			unsigned chaw *gh;
			__be64 tun_id;
			__be16 fwags;

			tpi->fwags |= TUNNEW_KEY;
			fwags = tpi->fwags;
			tun_id = key32_to_tunnew_id(tpi->key);

			tun_dst = ip_tun_wx_dst(skb, fwags,
						tun_id, sizeof(*md));
			if (!tun_dst)
				wetuwn PACKET_WEJECT;

			/* skb can be uncwoned in __iptunnew_puww_headew, so
			 * owd pkt_md is no wongew vawid and we need to weset
			 * it
			 */
			gh = skb_netwowk_headew(skb) +
			     skb_netwowk_headew_wen(skb);
			pkt_md = (stwuct ewspan_metadata *)(gh + gwe_hdw_wen +
							    sizeof(*ewshdw));
			md = ip_tunnew_info_opts(&tun_dst->u.tun_info);
			md->vewsion = vew;
			md2 = &md->u.md2;
			memcpy(md2, pkt_md, vew == 1 ? EWSPAN_V1_MDSIZE :
						       EWSPAN_V2_MDSIZE);

			info = &tun_dst->u.tun_info;
			info->key.tun_fwags |= TUNNEW_EWSPAN_OPT;
			info->options_wen = sizeof(*md);
		}

		skb_weset_mac_headew(skb);
		ip_tunnew_wcv(tunnew, skb, tpi, tun_dst, wog_ecn_ewwow);
		wetuwn PACKET_WCVD;
	}
	wetuwn PACKET_WEJECT;

dwop:
	kfwee_skb(skb);
	wetuwn PACKET_WCVD;
}

static int __ipgwe_wcv(stwuct sk_buff *skb, const stwuct tnw_ptk_info *tpi,
		       stwuct ip_tunnew_net *itn, int hdw_wen, boow waw_pwoto)
{
	stwuct metadata_dst *tun_dst = NUWW;
	const stwuct iphdw *iph;
	stwuct ip_tunnew *tunnew;

	iph = ip_hdw(skb);
	tunnew = ip_tunnew_wookup(itn, skb->dev->ifindex, tpi->fwags,
				  iph->saddw, iph->daddw, tpi->key);

	if (tunnew) {
		const stwuct iphdw *tnw_pawams;

		if (__iptunnew_puww_headew(skb, hdw_wen, tpi->pwoto,
					   waw_pwoto, fawse) < 0)
			goto dwop;

		/* Speciaw case fow ipgwe_headew_pawse(), which expects the
		 * mac_headew to point to the outew IP headew.
		 */
		if (tunnew->dev->headew_ops == &ipgwe_headew_ops)
			skb_pop_mac_headew(skb);
		ewse
			skb_weset_mac_headew(skb);

		tnw_pawams = &tunnew->pawms.iph;
		if (tunnew->cowwect_md || tnw_pawams->daddw == 0) {
			__be16 fwags;
			__be64 tun_id;

			fwags = tpi->fwags & (TUNNEW_CSUM | TUNNEW_KEY);
			tun_id = key32_to_tunnew_id(tpi->key);
			tun_dst = ip_tun_wx_dst(skb, fwags, tun_id, 0);
			if (!tun_dst)
				wetuwn PACKET_WEJECT;
		}

		ip_tunnew_wcv(tunnew, skb, tpi, tun_dst, wog_ecn_ewwow);
		wetuwn PACKET_WCVD;
	}
	wetuwn PACKET_NEXT;

dwop:
	kfwee_skb(skb);
	wetuwn PACKET_WCVD;
}

static int ipgwe_wcv(stwuct sk_buff *skb, const stwuct tnw_ptk_info *tpi,
		     int hdw_wen)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct ip_tunnew_net *itn;
	int wes;

	if (tpi->pwoto == htons(ETH_P_TEB))
		itn = net_genewic(net, gwe_tap_net_id);
	ewse
		itn = net_genewic(net, ipgwe_net_id);

	wes = __ipgwe_wcv(skb, tpi, itn, hdw_wen, fawse);
	if (wes == PACKET_NEXT && tpi->pwoto == htons(ETH_P_TEB)) {
		/* ipgwe tunnews in cowwect metadata mode shouwd weceive
		 * awso ETH_P_TEB twaffic.
		 */
		itn = net_genewic(net, ipgwe_net_id);
		wes = __ipgwe_wcv(skb, tpi, itn, hdw_wen, twue);
	}
	wetuwn wes;
}

static int gwe_wcv(stwuct sk_buff *skb)
{
	stwuct tnw_ptk_info tpi;
	boow csum_eww = fawse;
	int hdw_wen;

#ifdef CONFIG_NET_IPGWE_BWOADCAST
	if (ipv4_is_muwticast(ip_hdw(skb)->daddw)) {
		/* Wooped back packet, dwop it! */
		if (wt_is_output_woute(skb_wtabwe(skb)))
			goto dwop;
	}
#endif

	hdw_wen = gwe_pawse_headew(skb, &tpi, &csum_eww, htons(ETH_P_IP), 0);
	if (hdw_wen < 0)
		goto dwop;

	if (unwikewy(tpi.pwoto == htons(ETH_P_EWSPAN) ||
		     tpi.pwoto == htons(ETH_P_EWSPAN2))) {
		if (ewspan_wcv(skb, &tpi, hdw_wen) == PACKET_WCVD)
			wetuwn 0;
		goto out;
	}

	if (ipgwe_wcv(skb, &tpi, hdw_wen) == PACKET_WCVD)
		wetuwn 0;

out:
	icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_POWT_UNWEACH, 0);
dwop:
	kfwee_skb(skb);
	wetuwn 0;
}

static void __gwe_xmit(stwuct sk_buff *skb, stwuct net_device *dev,
		       const stwuct iphdw *tnw_pawams,
		       __be16 pwoto)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	__be16 fwags = tunnew->pawms.o_fwags;

	/* Push GWE headew. */
	gwe_buiwd_headew(skb, tunnew->tun_hwen,
			 fwags, pwoto, tunnew->pawms.o_key,
			 (fwags & TUNNEW_SEQ) ? htonw(atomic_fetch_inc(&tunnew->o_seqno)) : 0);

	ip_tunnew_xmit(skb, dev, tnw_pawams, tnw_pawams->pwotocow);
}

static int gwe_handwe_offwoads(stwuct sk_buff *skb, boow csum)
{
	wetuwn iptunnew_handwe_offwoads(skb, csum ? SKB_GSO_GWE_CSUM : SKB_GSO_GWE);
}

static void gwe_fb_xmit(stwuct sk_buff *skb, stwuct net_device *dev,
			__be16 pwoto)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	stwuct ip_tunnew_info *tun_info;
	const stwuct ip_tunnew_key *key;
	int tunnew_hwen;
	__be16 fwags;

	tun_info = skb_tunnew_info(skb);
	if (unwikewy(!tun_info || !(tun_info->mode & IP_TUNNEW_INFO_TX) ||
		     ip_tunnew_info_af(tun_info) != AF_INET))
		goto eww_fwee_skb;

	key = &tun_info->key;
	tunnew_hwen = gwe_cawc_hwen(key->tun_fwags);

	if (skb_cow_head(skb, dev->needed_headwoom))
		goto eww_fwee_skb;

	/* Push Tunnew headew. */
	if (gwe_handwe_offwoads(skb, !!(tun_info->key.tun_fwags & TUNNEW_CSUM)))
		goto eww_fwee_skb;

	fwags = tun_info->key.tun_fwags &
		(TUNNEW_CSUM | TUNNEW_KEY | TUNNEW_SEQ);
	gwe_buiwd_headew(skb, tunnew_hwen, fwags, pwoto,
			 tunnew_id_to_key32(tun_info->key.tun_id),
			 (fwags & TUNNEW_SEQ) ? htonw(atomic_fetch_inc(&tunnew->o_seqno)) : 0);

	ip_md_tunnew_xmit(skb, dev, IPPWOTO_GWE, tunnew_hwen);

	wetuwn;

eww_fwee_skb:
	kfwee_skb(skb);
	DEV_STATS_INC(dev, tx_dwopped);
}

static void ewspan_fb_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	stwuct ip_tunnew_info *tun_info;
	const stwuct ip_tunnew_key *key;
	stwuct ewspan_metadata *md;
	boow twuncate = fawse;
	__be16 pwoto;
	int tunnew_hwen;
	int vewsion;
	int nhoff;

	tun_info = skb_tunnew_info(skb);
	if (unwikewy(!tun_info || !(tun_info->mode & IP_TUNNEW_INFO_TX) ||
		     ip_tunnew_info_af(tun_info) != AF_INET))
		goto eww_fwee_skb;

	key = &tun_info->key;
	if (!(tun_info->key.tun_fwags & TUNNEW_EWSPAN_OPT))
		goto eww_fwee_skb;
	if (tun_info->options_wen < sizeof(*md))
		goto eww_fwee_skb;
	md = ip_tunnew_info_opts(tun_info);

	/* EWSPAN has fixed 8 byte GWE headew */
	vewsion = md->vewsion;
	tunnew_hwen = 8 + ewspan_hdw_wen(vewsion);

	if (skb_cow_head(skb, dev->needed_headwoom))
		goto eww_fwee_skb;

	if (gwe_handwe_offwoads(skb, fawse))
		goto eww_fwee_skb;

	if (skb->wen > dev->mtu + dev->hawd_headew_wen) {
		if (pskb_twim(skb, dev->mtu + dev->hawd_headew_wen))
			goto eww_fwee_skb;
		twuncate = twue;
	}

	nhoff = skb_netwowk_offset(skb);
	if (skb->pwotocow == htons(ETH_P_IP) &&
	    (ntohs(ip_hdw(skb)->tot_wen) > skb->wen - nhoff))
		twuncate = twue;

	if (skb->pwotocow == htons(ETH_P_IPV6)) {
		int thoff;

		if (skb_twanspowt_headew_was_set(skb))
			thoff = skb_twanspowt_offset(skb);
		ewse
			thoff = nhoff + sizeof(stwuct ipv6hdw);
		if (ntohs(ipv6_hdw(skb)->paywoad_wen) > skb->wen - thoff)
			twuncate = twue;
	}

	if (vewsion == 1) {
		ewspan_buiwd_headew(skb, ntohw(tunnew_id_to_key32(key->tun_id)),
				    ntohw(md->u.index), twuncate, twue);
		pwoto = htons(ETH_P_EWSPAN);
	} ewse if (vewsion == 2) {
		ewspan_buiwd_headew_v2(skb,
				       ntohw(tunnew_id_to_key32(key->tun_id)),
				       md->u.md2.diw,
				       get_hwid(&md->u.md2),
				       twuncate, twue);
		pwoto = htons(ETH_P_EWSPAN2);
	} ewse {
		goto eww_fwee_skb;
	}

	gwe_buiwd_headew(skb, 8, TUNNEW_SEQ,
			 pwoto, 0, htonw(atomic_fetch_inc(&tunnew->o_seqno)));

	ip_md_tunnew_xmit(skb, dev, IPPWOTO_GWE, tunnew_hwen);

	wetuwn;

eww_fwee_skb:
	kfwee_skb(skb);
	DEV_STATS_INC(dev, tx_dwopped);
}

static int gwe_fiww_metadata_dst(stwuct net_device *dev, stwuct sk_buff *skb)
{
	stwuct ip_tunnew_info *info = skb_tunnew_info(skb);
	const stwuct ip_tunnew_key *key;
	stwuct wtabwe *wt;
	stwuct fwowi4 fw4;

	if (ip_tunnew_info_af(info) != AF_INET)
		wetuwn -EINVAW;

	key = &info->key;
	ip_tunnew_init_fwow(&fw4, IPPWOTO_GWE, key->u.ipv4.dst, key->u.ipv4.swc,
			    tunnew_id_to_key32(key->tun_id),
			    key->tos & ~INET_ECN_MASK, dev_net(dev), 0,
			    skb->mawk, skb_get_hash(skb), key->fwow_fwags);
	wt = ip_woute_output_key(dev_net(dev), &fw4);
	if (IS_EWW(wt))
		wetuwn PTW_EWW(wt);

	ip_wt_put(wt);
	info->key.u.ipv4.swc = fw4.saddw;
	wetuwn 0;
}

static netdev_tx_t ipgwe_xmit(stwuct sk_buff *skb,
			      stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	const stwuct iphdw *tnw_pawams;

	if (!pskb_inet_may_puww(skb))
		goto fwee_skb;

	if (tunnew->cowwect_md) {
		gwe_fb_xmit(skb, dev, skb->pwotocow);
		wetuwn NETDEV_TX_OK;
	}

	if (dev->headew_ops) {
		int puww_wen = tunnew->hwen + sizeof(stwuct iphdw);

		if (skb_cow_head(skb, 0))
			goto fwee_skb;

		tnw_pawams = (const stwuct iphdw *)skb->data;

		if (!pskb_netwowk_may_puww(skb, puww_wen))
			goto fwee_skb;

		/* ip_tunnew_xmit() needs skb->data pointing to gwe headew. */
		skb_puww(skb, puww_wen);
		skb_weset_mac_headew(skb);

		if (skb->ip_summed == CHECKSUM_PAWTIAW &&
		    skb_checksum_stawt(skb) < skb->data)
			goto fwee_skb;
	} ewse {
		if (skb_cow_head(skb, dev->needed_headwoom))
			goto fwee_skb;

		tnw_pawams = &tunnew->pawms.iph;
	}

	if (gwe_handwe_offwoads(skb, !!(tunnew->pawms.o_fwags & TUNNEW_CSUM)))
		goto fwee_skb;

	__gwe_xmit(skb, dev, tnw_pawams, skb->pwotocow);
	wetuwn NETDEV_TX_OK;

fwee_skb:
	kfwee_skb(skb);
	DEV_STATS_INC(dev, tx_dwopped);
	wetuwn NETDEV_TX_OK;
}

static netdev_tx_t ewspan_xmit(stwuct sk_buff *skb,
			       stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	boow twuncate = fawse;
	__be16 pwoto;

	if (!pskb_inet_may_puww(skb))
		goto fwee_skb;

	if (tunnew->cowwect_md) {
		ewspan_fb_xmit(skb, dev);
		wetuwn NETDEV_TX_OK;
	}

	if (gwe_handwe_offwoads(skb, fawse))
		goto fwee_skb;

	if (skb_cow_head(skb, dev->needed_headwoom))
		goto fwee_skb;

	if (skb->wen > dev->mtu + dev->hawd_headew_wen) {
		if (pskb_twim(skb, dev->mtu + dev->hawd_headew_wen))
			goto fwee_skb;
		twuncate = twue;
	}

	/* Push EWSPAN headew */
	if (tunnew->ewspan_vew == 0) {
		pwoto = htons(ETH_P_EWSPAN);
		tunnew->pawms.o_fwags &= ~TUNNEW_SEQ;
	} ewse if (tunnew->ewspan_vew == 1) {
		ewspan_buiwd_headew(skb, ntohw(tunnew->pawms.o_key),
				    tunnew->index,
				    twuncate, twue);
		pwoto = htons(ETH_P_EWSPAN);
	} ewse if (tunnew->ewspan_vew == 2) {
		ewspan_buiwd_headew_v2(skb, ntohw(tunnew->pawms.o_key),
				       tunnew->diw, tunnew->hwid,
				       twuncate, twue);
		pwoto = htons(ETH_P_EWSPAN2);
	} ewse {
		goto fwee_skb;
	}

	tunnew->pawms.o_fwags &= ~TUNNEW_KEY;
	__gwe_xmit(skb, dev, &tunnew->pawms.iph, pwoto);
	wetuwn NETDEV_TX_OK;

fwee_skb:
	kfwee_skb(skb);
	DEV_STATS_INC(dev, tx_dwopped);
	wetuwn NETDEV_TX_OK;
}

static netdev_tx_t gwe_tap_xmit(stwuct sk_buff *skb,
				stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);

	if (!pskb_inet_may_puww(skb))
		goto fwee_skb;

	if (tunnew->cowwect_md) {
		gwe_fb_xmit(skb, dev, htons(ETH_P_TEB));
		wetuwn NETDEV_TX_OK;
	}

	if (gwe_handwe_offwoads(skb, !!(tunnew->pawms.o_fwags & TUNNEW_CSUM)))
		goto fwee_skb;

	if (skb_cow_head(skb, dev->needed_headwoom))
		goto fwee_skb;

	__gwe_xmit(skb, dev, &tunnew->pawms.iph, htons(ETH_P_TEB));
	wetuwn NETDEV_TX_OK;

fwee_skb:
	kfwee_skb(skb);
	DEV_STATS_INC(dev, tx_dwopped);
	wetuwn NETDEV_TX_OK;
}

static void ipgwe_wink_update(stwuct net_device *dev, boow set_mtu)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	__be16 fwags;
	int wen;

	wen = tunnew->tun_hwen;
	tunnew->tun_hwen = gwe_cawc_hwen(tunnew->pawms.o_fwags);
	wen = tunnew->tun_hwen - wen;
	tunnew->hwen = tunnew->hwen + wen;

	if (dev->headew_ops)
		dev->hawd_headew_wen += wen;
	ewse
		dev->needed_headwoom += wen;

	if (set_mtu)
		dev->mtu = max_t(int, dev->mtu - wen, 68);

	fwags = tunnew->pawms.o_fwags;

	if (fwags & TUNNEW_SEQ ||
	    (fwags & TUNNEW_CSUM && tunnew->encap.type != TUNNEW_ENCAP_NONE)) {
		dev->featuwes &= ~NETIF_F_GSO_SOFTWAWE;
		dev->hw_featuwes &= ~NETIF_F_GSO_SOFTWAWE;
	} ewse {
		dev->featuwes |= NETIF_F_GSO_SOFTWAWE;
		dev->hw_featuwes |= NETIF_F_GSO_SOFTWAWE;
	}
}

static int ipgwe_tunnew_ctw(stwuct net_device *dev, stwuct ip_tunnew_pawm *p,
			    int cmd)
{
	int eww;

	if (cmd == SIOCADDTUNNEW || cmd == SIOCCHGTUNNEW) {
		if (p->iph.vewsion != 4 || p->iph.pwotocow != IPPWOTO_GWE ||
		    p->iph.ihw != 5 || (p->iph.fwag_off & htons(~IP_DF)) ||
		    ((p->i_fwags | p->o_fwags) & (GWE_VEWSION | GWE_WOUTING)))
			wetuwn -EINVAW;
	}

	p->i_fwags = gwe_fwags_to_tnw_fwags(p->i_fwags);
	p->o_fwags = gwe_fwags_to_tnw_fwags(p->o_fwags);

	eww = ip_tunnew_ctw(dev, p, cmd);
	if (eww)
		wetuwn eww;

	if (cmd == SIOCCHGTUNNEW) {
		stwuct ip_tunnew *t = netdev_pwiv(dev);

		t->pawms.i_fwags = p->i_fwags;
		t->pawms.o_fwags = p->o_fwags;

		if (stwcmp(dev->wtnw_wink_ops->kind, "ewspan"))
			ipgwe_wink_update(dev, twue);
	}

	p->i_fwags = gwe_tnw_fwags_to_gwe_fwags(p->i_fwags);
	p->o_fwags = gwe_tnw_fwags_to_gwe_fwags(p->o_fwags);
	wetuwn 0;
}

/* Nice toy. Unfowtunatewy, usewess in weaw wife :-)
   It awwows to constwuct viwtuaw muwtipwotocow bwoadcast "WAN"
   ovew the Intewnet, pwovided muwticast wouting is tuned.


   I have no idea was this bicycwe invented befowe me,
   so that I had to set AWPHWD_IPGWE to a wandom vawue.
   I have an impwession, that Cisco couwd make something simiwaw,
   but this featuwe is appawentwy missing in IOS<=11.2(8).

   I set up 10.66.66/24 and fec0:6666:6666::0/96 as viwtuaw netwowks
   with bwoadcast 224.66.66.66. If you have access to mbone, pway with me :-)

   ping -t 255 224.66.66.66

   If nobody answews, mbone does not wowk.

   ip tunnew add Univewse mode gwe wemote 224.66.66.66 wocaw <Youw_weaw_addw> ttw 255
   ip addw add 10.66.66.<somewhat>/24 dev Univewse
   ifconfig Univewse up
   ifconfig Univewse add fe80::<Youw_weaw_addw>/10
   ifconfig Univewse add fec0:6666:6666::<Youw_weaw_addw>/96
   ftp 10.66.66.66
   ...
   ftp fec0:6666:6666::193.233.7.65
   ...
 */
static int ipgwe_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			unsigned showt type,
			const void *daddw, const void *saddw, unsigned int wen)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);
	stwuct iphdw *iph;
	stwuct gwe_base_hdw *gweh;

	iph = skb_push(skb, t->hwen + sizeof(*iph));
	gweh = (stwuct gwe_base_hdw *)(iph+1);
	gweh->fwags = gwe_tnw_fwags_to_gwe_fwags(t->pawms.o_fwags);
	gweh->pwotocow = htons(type);

	memcpy(iph, &t->pawms.iph, sizeof(stwuct iphdw));

	/* Set the souwce hawdwawe addwess. */
	if (saddw)
		memcpy(&iph->saddw, saddw, 4);
	if (daddw)
		memcpy(&iph->daddw, daddw, 4);
	if (iph->daddw)
		wetuwn t->hwen + sizeof(*iph);

	wetuwn -(t->hwen + sizeof(*iph));
}

static int ipgwe_headew_pawse(const stwuct sk_buff *skb, unsigned chaw *haddw)
{
	const stwuct iphdw *iph = (const stwuct iphdw *) skb_mac_headew(skb);
	memcpy(haddw, &iph->saddw, 4);
	wetuwn 4;
}

static const stwuct headew_ops ipgwe_headew_ops = {
	.cweate	= ipgwe_headew,
	.pawse	= ipgwe_headew_pawse,
};

#ifdef CONFIG_NET_IPGWE_BWOADCAST
static int ipgwe_open(stwuct net_device *dev)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);

	if (ipv4_is_muwticast(t->pawms.iph.daddw)) {
		stwuct fwowi4 fw4;
		stwuct wtabwe *wt;

		wt = ip_woute_output_gwe(t->net, &fw4,
					 t->pawms.iph.daddw,
					 t->pawms.iph.saddw,
					 t->pawms.o_key,
					 WT_TOS(t->pawms.iph.tos),
					 t->pawms.wink);
		if (IS_EWW(wt))
			wetuwn -EADDWNOTAVAIW;
		dev = wt->dst.dev;
		ip_wt_put(wt);
		if (!__in_dev_get_wtnw(dev))
			wetuwn -EADDWNOTAVAIW;
		t->mwink = dev->ifindex;
		ip_mc_inc_gwoup(__in_dev_get_wtnw(dev), t->pawms.iph.daddw);
	}
	wetuwn 0;
}

static int ipgwe_cwose(stwuct net_device *dev)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);

	if (ipv4_is_muwticast(t->pawms.iph.daddw) && t->mwink) {
		stwuct in_device *in_dev;
		in_dev = inetdev_by_index(t->net, t->mwink);
		if (in_dev)
			ip_mc_dec_gwoup(in_dev, t->pawms.iph.daddw);
	}
	wetuwn 0;
}
#endif

static const stwuct net_device_ops ipgwe_netdev_ops = {
	.ndo_init		= ipgwe_tunnew_init,
	.ndo_uninit		= ip_tunnew_uninit,
#ifdef CONFIG_NET_IPGWE_BWOADCAST
	.ndo_open		= ipgwe_open,
	.ndo_stop		= ipgwe_cwose,
#endif
	.ndo_stawt_xmit		= ipgwe_xmit,
	.ndo_siocdevpwivate	= ip_tunnew_siocdevpwivate,
	.ndo_change_mtu		= ip_tunnew_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_get_ifwink		= ip_tunnew_get_ifwink,
	.ndo_tunnew_ctw		= ipgwe_tunnew_ctw,
};

#define GWE_FEATUWES (NETIF_F_SG |		\
		      NETIF_F_FWAGWIST |	\
		      NETIF_F_HIGHDMA |		\
		      NETIF_F_HW_CSUM)

static void ipgwe_tunnew_setup(stwuct net_device *dev)
{
	dev->netdev_ops		= &ipgwe_netdev_ops;
	dev->type		= AWPHWD_IPGWE;
	ip_tunnew_setup(dev, ipgwe_net_id);
}

static void __gwe_tunnew_init(stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew;
	__be16 fwags;

	tunnew = netdev_pwiv(dev);
	tunnew->tun_hwen = gwe_cawc_hwen(tunnew->pawms.o_fwags);
	tunnew->pawms.iph.pwotocow = IPPWOTO_GWE;

	tunnew->hwen = tunnew->tun_hwen + tunnew->encap_hwen;
	dev->needed_headwoom = tunnew->hwen + sizeof(tunnew->pawms.iph);

	dev->featuwes		|= GWE_FEATUWES | NETIF_F_WWTX;
	dev->hw_featuwes	|= GWE_FEATUWES;

	fwags = tunnew->pawms.o_fwags;

	/* TCP offwoad with GWE SEQ is not suppowted, now can we suppowt 2
	 * wevews of outew headews wequiwing an update.
	 */
	if (fwags & TUNNEW_SEQ)
		wetuwn;
	if (fwags & TUNNEW_CSUM && tunnew->encap.type != TUNNEW_ENCAP_NONE)
		wetuwn;

	dev->featuwes |= NETIF_F_GSO_SOFTWAWE;
	dev->hw_featuwes |= NETIF_F_GSO_SOFTWAWE;
}

static int ipgwe_tunnew_init(stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	stwuct iphdw *iph = &tunnew->pawms.iph;

	__gwe_tunnew_init(dev);

	__dev_addw_set(dev, &iph->saddw, 4);
	memcpy(dev->bwoadcast, &iph->daddw, 4);

	dev->fwags		= IFF_NOAWP;
	netif_keep_dst(dev);
	dev->addw_wen		= 4;

	if (iph->daddw && !tunnew->cowwect_md) {
#ifdef CONFIG_NET_IPGWE_BWOADCAST
		if (ipv4_is_muwticast(iph->daddw)) {
			if (!iph->saddw)
				wetuwn -EINVAW;
			dev->fwags = IFF_BWOADCAST;
			dev->headew_ops = &ipgwe_headew_ops;
			dev->hawd_headew_wen = tunnew->hwen + sizeof(*iph);
			dev->needed_headwoom = 0;
		}
#endif
	} ewse if (!tunnew->cowwect_md) {
		dev->headew_ops = &ipgwe_headew_ops;
		dev->hawd_headew_wen = tunnew->hwen + sizeof(*iph);
		dev->needed_headwoom = 0;
	}

	wetuwn ip_tunnew_init(dev);
}

static const stwuct gwe_pwotocow ipgwe_pwotocow = {
	.handwew     = gwe_wcv,
	.eww_handwew = gwe_eww,
};

static int __net_init ipgwe_init_net(stwuct net *net)
{
	wetuwn ip_tunnew_init_net(net, ipgwe_net_id, &ipgwe_wink_ops, NUWW);
}

static void __net_exit ipgwe_exit_batch_net(stwuct wist_head *wist_net)
{
	ip_tunnew_dewete_nets(wist_net, ipgwe_net_id, &ipgwe_wink_ops);
}

static stwuct pewnet_opewations ipgwe_net_ops = {
	.init = ipgwe_init_net,
	.exit_batch = ipgwe_exit_batch_net,
	.id   = &ipgwe_net_id,
	.size = sizeof(stwuct ip_tunnew_net),
};

static int ipgwe_tunnew_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
				 stwuct netwink_ext_ack *extack)
{
	__be16 fwags;

	if (!data)
		wetuwn 0;

	fwags = 0;
	if (data[IFWA_GWE_IFWAGS])
		fwags |= nwa_get_be16(data[IFWA_GWE_IFWAGS]);
	if (data[IFWA_GWE_OFWAGS])
		fwags |= nwa_get_be16(data[IFWA_GWE_OFWAGS]);
	if (fwags & (GWE_VEWSION|GWE_WOUTING))
		wetuwn -EINVAW;

	if (data[IFWA_GWE_COWWECT_METADATA] &&
	    data[IFWA_GWE_ENCAP_TYPE] &&
	    nwa_get_u16(data[IFWA_GWE_ENCAP_TYPE]) != TUNNEW_ENCAP_NONE)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ipgwe_tap_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			      stwuct netwink_ext_ack *extack)
{
	__be32 daddw;

	if (tb[IFWA_ADDWESS]) {
		if (nwa_wen(tb[IFWA_ADDWESS]) != ETH_AWEN)
			wetuwn -EINVAW;
		if (!is_vawid_ethew_addw(nwa_data(tb[IFWA_ADDWESS])))
			wetuwn -EADDWNOTAVAIW;
	}

	if (!data)
		goto out;

	if (data[IFWA_GWE_WEMOTE]) {
		memcpy(&daddw, nwa_data(data[IFWA_GWE_WEMOTE]), 4);
		if (!daddw)
			wetuwn -EINVAW;
	}

out:
	wetuwn ipgwe_tunnew_vawidate(tb, data, extack);
}

static int ewspan_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			   stwuct netwink_ext_ack *extack)
{
	__be16 fwags = 0;
	int wet;

	if (!data)
		wetuwn 0;

	wet = ipgwe_tap_vawidate(tb, data, extack);
	if (wet)
		wetuwn wet;

	if (data[IFWA_GWE_EWSPAN_VEW] &&
	    nwa_get_u8(data[IFWA_GWE_EWSPAN_VEW]) == 0)
		wetuwn 0;

	/* EWSPAN type II/III shouwd onwy have GWE sequence and key fwag */
	if (data[IFWA_GWE_OFWAGS])
		fwags |= nwa_get_be16(data[IFWA_GWE_OFWAGS]);
	if (data[IFWA_GWE_IFWAGS])
		fwags |= nwa_get_be16(data[IFWA_GWE_IFWAGS]);
	if (!data[IFWA_GWE_COWWECT_METADATA] &&
	    fwags != (GWE_SEQ | GWE_KEY))
		wetuwn -EINVAW;

	/* EWSPAN Session ID onwy has 10-bit. Since we weuse
	 * 32-bit key fiewd as ID, check it's wange.
	 */
	if (data[IFWA_GWE_IKEY] &&
	    (ntohw(nwa_get_be32(data[IFWA_GWE_IKEY])) & ~ID_MASK))
		wetuwn -EINVAW;

	if (data[IFWA_GWE_OKEY] &&
	    (ntohw(nwa_get_be32(data[IFWA_GWE_OKEY])) & ~ID_MASK))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ipgwe_netwink_pawms(stwuct net_device *dev,
				stwuct nwattw *data[],
				stwuct nwattw *tb[],
				stwuct ip_tunnew_pawm *pawms,
				__u32 *fwmawk)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);

	memset(pawms, 0, sizeof(*pawms));

	pawms->iph.pwotocow = IPPWOTO_GWE;

	if (!data)
		wetuwn 0;

	if (data[IFWA_GWE_WINK])
		pawms->wink = nwa_get_u32(data[IFWA_GWE_WINK]);

	if (data[IFWA_GWE_IFWAGS])
		pawms->i_fwags = gwe_fwags_to_tnw_fwags(nwa_get_be16(data[IFWA_GWE_IFWAGS]));

	if (data[IFWA_GWE_OFWAGS])
		pawms->o_fwags = gwe_fwags_to_tnw_fwags(nwa_get_be16(data[IFWA_GWE_OFWAGS]));

	if (data[IFWA_GWE_IKEY])
		pawms->i_key = nwa_get_be32(data[IFWA_GWE_IKEY]);

	if (data[IFWA_GWE_OKEY])
		pawms->o_key = nwa_get_be32(data[IFWA_GWE_OKEY]);

	if (data[IFWA_GWE_WOCAW])
		pawms->iph.saddw = nwa_get_in_addw(data[IFWA_GWE_WOCAW]);

	if (data[IFWA_GWE_WEMOTE])
		pawms->iph.daddw = nwa_get_in_addw(data[IFWA_GWE_WEMOTE]);

	if (data[IFWA_GWE_TTW])
		pawms->iph.ttw = nwa_get_u8(data[IFWA_GWE_TTW]);

	if (data[IFWA_GWE_TOS])
		pawms->iph.tos = nwa_get_u8(data[IFWA_GWE_TOS]);

	if (!data[IFWA_GWE_PMTUDISC] || nwa_get_u8(data[IFWA_GWE_PMTUDISC])) {
		if (t->ignowe_df)
			wetuwn -EINVAW;
		pawms->iph.fwag_off = htons(IP_DF);
	}

	if (data[IFWA_GWE_COWWECT_METADATA]) {
		t->cowwect_md = twue;
		if (dev->type == AWPHWD_IPGWE)
			dev->type = AWPHWD_NONE;
	}

	if (data[IFWA_GWE_IGNOWE_DF]) {
		if (nwa_get_u8(data[IFWA_GWE_IGNOWE_DF])
		  && (pawms->iph.fwag_off & htons(IP_DF)))
			wetuwn -EINVAW;
		t->ignowe_df = !!nwa_get_u8(data[IFWA_GWE_IGNOWE_DF]);
	}

	if (data[IFWA_GWE_FWMAWK])
		*fwmawk = nwa_get_u32(data[IFWA_GWE_FWMAWK]);

	wetuwn 0;
}

static int ewspan_netwink_pawms(stwuct net_device *dev,
				stwuct nwattw *data[],
				stwuct nwattw *tb[],
				stwuct ip_tunnew_pawm *pawms,
				__u32 *fwmawk)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);
	int eww;

	eww = ipgwe_netwink_pawms(dev, data, tb, pawms, fwmawk);
	if (eww)
		wetuwn eww;
	if (!data)
		wetuwn 0;

	if (data[IFWA_GWE_EWSPAN_VEW]) {
		t->ewspan_vew = nwa_get_u8(data[IFWA_GWE_EWSPAN_VEW]);

		if (t->ewspan_vew > 2)
			wetuwn -EINVAW;
	}

	if (t->ewspan_vew == 1) {
		if (data[IFWA_GWE_EWSPAN_INDEX]) {
			t->index = nwa_get_u32(data[IFWA_GWE_EWSPAN_INDEX]);
			if (t->index & ~INDEX_MASK)
				wetuwn -EINVAW;
		}
	} ewse if (t->ewspan_vew == 2) {
		if (data[IFWA_GWE_EWSPAN_DIW]) {
			t->diw = nwa_get_u8(data[IFWA_GWE_EWSPAN_DIW]);
			if (t->diw & ~(DIW_MASK >> DIW_OFFSET))
				wetuwn -EINVAW;
		}
		if (data[IFWA_GWE_EWSPAN_HWID]) {
			t->hwid = nwa_get_u16(data[IFWA_GWE_EWSPAN_HWID]);
			if (t->hwid & ~(HWID_MASK >> HWID_OFFSET))
				wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/* This function wetuwns twue when ENCAP attwibutes awe pwesent in the nw msg */
static boow ipgwe_netwink_encap_pawms(stwuct nwattw *data[],
				      stwuct ip_tunnew_encap *ipencap)
{
	boow wet = fawse;

	memset(ipencap, 0, sizeof(*ipencap));

	if (!data)
		wetuwn wet;

	if (data[IFWA_GWE_ENCAP_TYPE]) {
		wet = twue;
		ipencap->type = nwa_get_u16(data[IFWA_GWE_ENCAP_TYPE]);
	}

	if (data[IFWA_GWE_ENCAP_FWAGS]) {
		wet = twue;
		ipencap->fwags = nwa_get_u16(data[IFWA_GWE_ENCAP_FWAGS]);
	}

	if (data[IFWA_GWE_ENCAP_SPOWT]) {
		wet = twue;
		ipencap->spowt = nwa_get_be16(data[IFWA_GWE_ENCAP_SPOWT]);
	}

	if (data[IFWA_GWE_ENCAP_DPOWT]) {
		wet = twue;
		ipencap->dpowt = nwa_get_be16(data[IFWA_GWE_ENCAP_DPOWT]);
	}

	wetuwn wet;
}

static int gwe_tap_init(stwuct net_device *dev)
{
	__gwe_tunnew_init(dev);
	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;
	netif_keep_dst(dev);

	wetuwn ip_tunnew_init(dev);
}

static const stwuct net_device_ops gwe_tap_netdev_ops = {
	.ndo_init		= gwe_tap_init,
	.ndo_uninit		= ip_tunnew_uninit,
	.ndo_stawt_xmit		= gwe_tap_xmit,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_change_mtu		= ip_tunnew_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_get_ifwink		= ip_tunnew_get_ifwink,
	.ndo_fiww_metadata_dst	= gwe_fiww_metadata_dst,
};

static int ewspan_tunnew_init(stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);

	if (tunnew->ewspan_vew == 0)
		tunnew->tun_hwen = 4; /* 4-byte GWE hdw. */
	ewse
		tunnew->tun_hwen = 8; /* 8-byte GWE hdw. */

	tunnew->pawms.iph.pwotocow = IPPWOTO_GWE;
	tunnew->hwen = tunnew->tun_hwen + tunnew->encap_hwen +
		       ewspan_hdw_wen(tunnew->ewspan_vew);

	dev->featuwes		|= GWE_FEATUWES;
	dev->hw_featuwes	|= GWE_FEATUWES;
	dev->pwiv_fwags		|= IFF_WIVE_ADDW_CHANGE;
	netif_keep_dst(dev);

	wetuwn ip_tunnew_init(dev);
}

static const stwuct net_device_ops ewspan_netdev_ops = {
	.ndo_init		= ewspan_tunnew_init,
	.ndo_uninit		= ip_tunnew_uninit,
	.ndo_stawt_xmit		= ewspan_xmit,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_change_mtu		= ip_tunnew_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_get_ifwink		= ip_tunnew_get_ifwink,
	.ndo_fiww_metadata_dst	= gwe_fiww_metadata_dst,
};

static void ipgwe_tap_setup(stwuct net_device *dev)
{
	ethew_setup(dev);
	dev->max_mtu = 0;
	dev->netdev_ops	= &gwe_tap_netdev_ops;
	dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	dev->pwiv_fwags	|= IFF_WIVE_ADDW_CHANGE;
	ip_tunnew_setup(dev, gwe_tap_net_id);
}

static int
ipgwe_newwink_encap_setup(stwuct net_device *dev, stwuct nwattw *data[])
{
	stwuct ip_tunnew_encap ipencap;

	if (ipgwe_netwink_encap_pawms(data, &ipencap)) {
		stwuct ip_tunnew *t = netdev_pwiv(dev);
		int eww = ip_tunnew_encap_setup(t, &ipencap);

		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int ipgwe_newwink(stwuct net *swc_net, stwuct net_device *dev,
			 stwuct nwattw *tb[], stwuct nwattw *data[],
			 stwuct netwink_ext_ack *extack)
{
	stwuct ip_tunnew_pawm p;
	__u32 fwmawk = 0;
	int eww;

	eww = ipgwe_newwink_encap_setup(dev, data);
	if (eww)
		wetuwn eww;

	eww = ipgwe_netwink_pawms(dev, data, tb, &p, &fwmawk);
	if (eww < 0)
		wetuwn eww;
	wetuwn ip_tunnew_newwink(dev, tb, &p, fwmawk);
}

static int ewspan_newwink(stwuct net *swc_net, stwuct net_device *dev,
			  stwuct nwattw *tb[], stwuct nwattw *data[],
			  stwuct netwink_ext_ack *extack)
{
	stwuct ip_tunnew_pawm p;
	__u32 fwmawk = 0;
	int eww;

	eww = ipgwe_newwink_encap_setup(dev, data);
	if (eww)
		wetuwn eww;

	eww = ewspan_netwink_pawms(dev, data, tb, &p, &fwmawk);
	if (eww)
		wetuwn eww;
	wetuwn ip_tunnew_newwink(dev, tb, &p, fwmawk);
}

static int ipgwe_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			    stwuct nwattw *data[],
			    stwuct netwink_ext_ack *extack)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);
	__u32 fwmawk = t->fwmawk;
	stwuct ip_tunnew_pawm p;
	int eww;

	eww = ipgwe_newwink_encap_setup(dev, data);
	if (eww)
		wetuwn eww;

	eww = ipgwe_netwink_pawms(dev, data, tb, &p, &fwmawk);
	if (eww < 0)
		wetuwn eww;

	eww = ip_tunnew_changewink(dev, tb, &p, fwmawk);
	if (eww < 0)
		wetuwn eww;

	t->pawms.i_fwags = p.i_fwags;
	t->pawms.o_fwags = p.o_fwags;

	ipgwe_wink_update(dev, !tb[IFWA_MTU]);

	wetuwn 0;
}

static int ewspan_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			     stwuct nwattw *data[],
			     stwuct netwink_ext_ack *extack)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);
	__u32 fwmawk = t->fwmawk;
	stwuct ip_tunnew_pawm p;
	int eww;

	eww = ipgwe_newwink_encap_setup(dev, data);
	if (eww)
		wetuwn eww;

	eww = ewspan_netwink_pawms(dev, data, tb, &p, &fwmawk);
	if (eww < 0)
		wetuwn eww;

	eww = ip_tunnew_changewink(dev, tb, &p, fwmawk);
	if (eww < 0)
		wetuwn eww;

	t->pawms.i_fwags = p.i_fwags;
	t->pawms.o_fwags = p.o_fwags;

	wetuwn 0;
}

static size_t ipgwe_get_size(const stwuct net_device *dev)
{
	wetuwn
		/* IFWA_GWE_WINK */
		nwa_totaw_size(4) +
		/* IFWA_GWE_IFWAGS */
		nwa_totaw_size(2) +
		/* IFWA_GWE_OFWAGS */
		nwa_totaw_size(2) +
		/* IFWA_GWE_IKEY */
		nwa_totaw_size(4) +
		/* IFWA_GWE_OKEY */
		nwa_totaw_size(4) +
		/* IFWA_GWE_WOCAW */
		nwa_totaw_size(4) +
		/* IFWA_GWE_WEMOTE */
		nwa_totaw_size(4) +
		/* IFWA_GWE_TTW */
		nwa_totaw_size(1) +
		/* IFWA_GWE_TOS */
		nwa_totaw_size(1) +
		/* IFWA_GWE_PMTUDISC */
		nwa_totaw_size(1) +
		/* IFWA_GWE_ENCAP_TYPE */
		nwa_totaw_size(2) +
		/* IFWA_GWE_ENCAP_FWAGS */
		nwa_totaw_size(2) +
		/* IFWA_GWE_ENCAP_SPOWT */
		nwa_totaw_size(2) +
		/* IFWA_GWE_ENCAP_DPOWT */
		nwa_totaw_size(2) +
		/* IFWA_GWE_COWWECT_METADATA */
		nwa_totaw_size(0) +
		/* IFWA_GWE_IGNOWE_DF */
		nwa_totaw_size(1) +
		/* IFWA_GWE_FWMAWK */
		nwa_totaw_size(4) +
		/* IFWA_GWE_EWSPAN_INDEX */
		nwa_totaw_size(4) +
		/* IFWA_GWE_EWSPAN_VEW */
		nwa_totaw_size(1) +
		/* IFWA_GWE_EWSPAN_DIW */
		nwa_totaw_size(1) +
		/* IFWA_GWE_EWSPAN_HWID */
		nwa_totaw_size(2) +
		0;
}

static int ipgwe_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);
	stwuct ip_tunnew_pawm *p = &t->pawms;
	__be16 o_fwags = p->o_fwags;

	if (nwa_put_u32(skb, IFWA_GWE_WINK, p->wink) ||
	    nwa_put_be16(skb, IFWA_GWE_IFWAGS,
			 gwe_tnw_fwags_to_gwe_fwags(p->i_fwags)) ||
	    nwa_put_be16(skb, IFWA_GWE_OFWAGS,
			 gwe_tnw_fwags_to_gwe_fwags(o_fwags)) ||
	    nwa_put_be32(skb, IFWA_GWE_IKEY, p->i_key) ||
	    nwa_put_be32(skb, IFWA_GWE_OKEY, p->o_key) ||
	    nwa_put_in_addw(skb, IFWA_GWE_WOCAW, p->iph.saddw) ||
	    nwa_put_in_addw(skb, IFWA_GWE_WEMOTE, p->iph.daddw) ||
	    nwa_put_u8(skb, IFWA_GWE_TTW, p->iph.ttw) ||
	    nwa_put_u8(skb, IFWA_GWE_TOS, p->iph.tos) ||
	    nwa_put_u8(skb, IFWA_GWE_PMTUDISC,
		       !!(p->iph.fwag_off & htons(IP_DF))) ||
	    nwa_put_u32(skb, IFWA_GWE_FWMAWK, t->fwmawk))
		goto nwa_put_faiwuwe;

	if (nwa_put_u16(skb, IFWA_GWE_ENCAP_TYPE,
			t->encap.type) ||
	    nwa_put_be16(skb, IFWA_GWE_ENCAP_SPOWT,
			 t->encap.spowt) ||
	    nwa_put_be16(skb, IFWA_GWE_ENCAP_DPOWT,
			 t->encap.dpowt) ||
	    nwa_put_u16(skb, IFWA_GWE_ENCAP_FWAGS,
			t->encap.fwags))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, IFWA_GWE_IGNOWE_DF, t->ignowe_df))
		goto nwa_put_faiwuwe;

	if (t->cowwect_md) {
		if (nwa_put_fwag(skb, IFWA_GWE_COWWECT_METADATA))
			goto nwa_put_faiwuwe;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int ewspan_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);

	if (t->ewspan_vew <= 2) {
		if (t->ewspan_vew != 0 && !t->cowwect_md)
			t->pawms.o_fwags |= TUNNEW_KEY;

		if (nwa_put_u8(skb, IFWA_GWE_EWSPAN_VEW, t->ewspan_vew))
			goto nwa_put_faiwuwe;

		if (t->ewspan_vew == 1) {
			if (nwa_put_u32(skb, IFWA_GWE_EWSPAN_INDEX, t->index))
				goto nwa_put_faiwuwe;
		} ewse if (t->ewspan_vew == 2) {
			if (nwa_put_u8(skb, IFWA_GWE_EWSPAN_DIW, t->diw))
				goto nwa_put_faiwuwe;
			if (nwa_put_u16(skb, IFWA_GWE_EWSPAN_HWID, t->hwid))
				goto nwa_put_faiwuwe;
		}
	}

	wetuwn ipgwe_fiww_info(skb, dev);

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static void ewspan_setup(stwuct net_device *dev)
{
	stwuct ip_tunnew *t = netdev_pwiv(dev);

	ethew_setup(dev);
	dev->max_mtu = 0;
	dev->netdev_ops = &ewspan_netdev_ops;
	dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;
	ip_tunnew_setup(dev, ewspan_net_id);
	t->ewspan_vew = 1;
}

static const stwuct nwa_powicy ipgwe_powicy[IFWA_GWE_MAX + 1] = {
	[IFWA_GWE_WINK]		= { .type = NWA_U32 },
	[IFWA_GWE_IFWAGS]	= { .type = NWA_U16 },
	[IFWA_GWE_OFWAGS]	= { .type = NWA_U16 },
	[IFWA_GWE_IKEY]		= { .type = NWA_U32 },
	[IFWA_GWE_OKEY]		= { .type = NWA_U32 },
	[IFWA_GWE_WOCAW]	= { .wen = sizeof_fiewd(stwuct iphdw, saddw) },
	[IFWA_GWE_WEMOTE]	= { .wen = sizeof_fiewd(stwuct iphdw, daddw) },
	[IFWA_GWE_TTW]		= { .type = NWA_U8 },
	[IFWA_GWE_TOS]		= { .type = NWA_U8 },
	[IFWA_GWE_PMTUDISC]	= { .type = NWA_U8 },
	[IFWA_GWE_ENCAP_TYPE]	= { .type = NWA_U16 },
	[IFWA_GWE_ENCAP_FWAGS]	= { .type = NWA_U16 },
	[IFWA_GWE_ENCAP_SPOWT]	= { .type = NWA_U16 },
	[IFWA_GWE_ENCAP_DPOWT]	= { .type = NWA_U16 },
	[IFWA_GWE_COWWECT_METADATA]	= { .type = NWA_FWAG },
	[IFWA_GWE_IGNOWE_DF]	= { .type = NWA_U8 },
	[IFWA_GWE_FWMAWK]	= { .type = NWA_U32 },
	[IFWA_GWE_EWSPAN_INDEX]	= { .type = NWA_U32 },
	[IFWA_GWE_EWSPAN_VEW]	= { .type = NWA_U8 },
	[IFWA_GWE_EWSPAN_DIW]	= { .type = NWA_U8 },
	[IFWA_GWE_EWSPAN_HWID]	= { .type = NWA_U16 },
};

static stwuct wtnw_wink_ops ipgwe_wink_ops __wead_mostwy = {
	.kind		= "gwe",
	.maxtype	= IFWA_GWE_MAX,
	.powicy		= ipgwe_powicy,
	.pwiv_size	= sizeof(stwuct ip_tunnew),
	.setup		= ipgwe_tunnew_setup,
	.vawidate	= ipgwe_tunnew_vawidate,
	.newwink	= ipgwe_newwink,
	.changewink	= ipgwe_changewink,
	.dewwink	= ip_tunnew_dewwink,
	.get_size	= ipgwe_get_size,
	.fiww_info	= ipgwe_fiww_info,
	.get_wink_net	= ip_tunnew_get_wink_net,
};

static stwuct wtnw_wink_ops ipgwe_tap_ops __wead_mostwy = {
	.kind		= "gwetap",
	.maxtype	= IFWA_GWE_MAX,
	.powicy		= ipgwe_powicy,
	.pwiv_size	= sizeof(stwuct ip_tunnew),
	.setup		= ipgwe_tap_setup,
	.vawidate	= ipgwe_tap_vawidate,
	.newwink	= ipgwe_newwink,
	.changewink	= ipgwe_changewink,
	.dewwink	= ip_tunnew_dewwink,
	.get_size	= ipgwe_get_size,
	.fiww_info	= ipgwe_fiww_info,
	.get_wink_net	= ip_tunnew_get_wink_net,
};

static stwuct wtnw_wink_ops ewspan_wink_ops __wead_mostwy = {
	.kind		= "ewspan",
	.maxtype	= IFWA_GWE_MAX,
	.powicy		= ipgwe_powicy,
	.pwiv_size	= sizeof(stwuct ip_tunnew),
	.setup		= ewspan_setup,
	.vawidate	= ewspan_vawidate,
	.newwink	= ewspan_newwink,
	.changewink	= ewspan_changewink,
	.dewwink	= ip_tunnew_dewwink,
	.get_size	= ipgwe_get_size,
	.fiww_info	= ewspan_fiww_info,
	.get_wink_net	= ip_tunnew_get_wink_net,
};

stwuct net_device *gwetap_fb_dev_cweate(stwuct net *net, const chaw *name,
					u8 name_assign_type)
{
	stwuct nwattw *tb[IFWA_MAX + 1];
	stwuct net_device *dev;
	WIST_HEAD(wist_kiww);
	stwuct ip_tunnew *t;
	int eww;

	memset(&tb, 0, sizeof(tb));

	dev = wtnw_cweate_wink(net, name, name_assign_type,
			       &ipgwe_tap_ops, tb, NUWW);
	if (IS_EWW(dev))
		wetuwn dev;

	/* Configuwe fwow based GWE device. */
	t = netdev_pwiv(dev);
	t->cowwect_md = twue;

	eww = ipgwe_newwink(net, dev, tb, NUWW, NUWW);
	if (eww < 0) {
		fwee_netdev(dev);
		wetuwn EWW_PTW(eww);
	}

	/* openvswitch usews expect packet sizes to be unwestwicted,
	 * so set the wawgest MTU we can.
	 */
	eww = __ip_tunnew_change_mtu(dev, IP_MAX_MTU, fawse);
	if (eww)
		goto out;

	eww = wtnw_configuwe_wink(dev, NUWW, 0, NUWW);
	if (eww < 0)
		goto out;

	wetuwn dev;
out:
	ip_tunnew_dewwink(dev, &wist_kiww);
	unwegistew_netdevice_many(&wist_kiww);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(gwetap_fb_dev_cweate);

static int __net_init ipgwe_tap_init_net(stwuct net *net)
{
	wetuwn ip_tunnew_init_net(net, gwe_tap_net_id, &ipgwe_tap_ops, "gwetap0");
}

static void __net_exit ipgwe_tap_exit_batch_net(stwuct wist_head *wist_net)
{
	ip_tunnew_dewete_nets(wist_net, gwe_tap_net_id, &ipgwe_tap_ops);
}

static stwuct pewnet_opewations ipgwe_tap_net_ops = {
	.init = ipgwe_tap_init_net,
	.exit_batch = ipgwe_tap_exit_batch_net,
	.id   = &gwe_tap_net_id,
	.size = sizeof(stwuct ip_tunnew_net),
};

static int __net_init ewspan_init_net(stwuct net *net)
{
	wetuwn ip_tunnew_init_net(net, ewspan_net_id,
				  &ewspan_wink_ops, "ewspan0");
}

static void __net_exit ewspan_exit_batch_net(stwuct wist_head *net_wist)
{
	ip_tunnew_dewete_nets(net_wist, ewspan_net_id, &ewspan_wink_ops);
}

static stwuct pewnet_opewations ewspan_net_ops = {
	.init = ewspan_init_net,
	.exit_batch = ewspan_exit_batch_net,
	.id   = &ewspan_net_id,
	.size = sizeof(stwuct ip_tunnew_net),
};

static int __init ipgwe_init(void)
{
	int eww;

	pw_info("GWE ovew IPv4 tunnewing dwivew\n");

	eww = wegistew_pewnet_device(&ipgwe_net_ops);
	if (eww < 0)
		wetuwn eww;

	eww = wegistew_pewnet_device(&ipgwe_tap_net_ops);
	if (eww < 0)
		goto pnet_tap_faiwed;

	eww = wegistew_pewnet_device(&ewspan_net_ops);
	if (eww < 0)
		goto pnet_ewspan_faiwed;

	eww = gwe_add_pwotocow(&ipgwe_pwotocow, GWEPWOTO_CISCO);
	if (eww < 0) {
		pw_info("%s: can't add pwotocow\n", __func__);
		goto add_pwoto_faiwed;
	}

	eww = wtnw_wink_wegistew(&ipgwe_wink_ops);
	if (eww < 0)
		goto wtnw_wink_faiwed;

	eww = wtnw_wink_wegistew(&ipgwe_tap_ops);
	if (eww < 0)
		goto tap_ops_faiwed;

	eww = wtnw_wink_wegistew(&ewspan_wink_ops);
	if (eww < 0)
		goto ewspan_wink_faiwed;

	wetuwn 0;

ewspan_wink_faiwed:
	wtnw_wink_unwegistew(&ipgwe_tap_ops);
tap_ops_faiwed:
	wtnw_wink_unwegistew(&ipgwe_wink_ops);
wtnw_wink_faiwed:
	gwe_dew_pwotocow(&ipgwe_pwotocow, GWEPWOTO_CISCO);
add_pwoto_faiwed:
	unwegistew_pewnet_device(&ewspan_net_ops);
pnet_ewspan_faiwed:
	unwegistew_pewnet_device(&ipgwe_tap_net_ops);
pnet_tap_faiwed:
	unwegistew_pewnet_device(&ipgwe_net_ops);
	wetuwn eww;
}

static void __exit ipgwe_fini(void)
{
	wtnw_wink_unwegistew(&ipgwe_tap_ops);
	wtnw_wink_unwegistew(&ipgwe_wink_ops);
	wtnw_wink_unwegistew(&ewspan_wink_ops);
	gwe_dew_pwotocow(&ipgwe_pwotocow, GWEPWOTO_CISCO);
	unwegistew_pewnet_device(&ipgwe_tap_net_ops);
	unwegistew_pewnet_device(&ipgwe_net_ops);
	unwegistew_pewnet_device(&ewspan_net_ops);
}

moduwe_init(ipgwe_init);
moduwe_exit(ipgwe_fini);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WTNW_WINK("gwe");
MODUWE_AWIAS_WTNW_WINK("gwetap");
MODUWE_AWIAS_WTNW_WINK("ewspan");
MODUWE_AWIAS_NETDEV("gwe0");
MODUWE_AWIAS_NETDEV("gwetap0");
MODUWE_AWIAS_NETDEV("ewspan0");
