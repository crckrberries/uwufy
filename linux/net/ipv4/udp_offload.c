// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IPV4 GSO/GWO offwoad suppowt
 *	Winux INET impwementation
 *
 *	UDPv4 GSO suppowt
 */

#incwude <winux/skbuff.h>
#incwude <net/gwo.h>
#incwude <net/gso.h>
#incwude <net/udp.h>
#incwude <net/pwotocow.h>
#incwude <net/inet_common.h>

static stwuct sk_buff *__skb_udp_tunnew_segment(stwuct sk_buff *skb,
	netdev_featuwes_t featuwes,
	stwuct sk_buff *(*gso_innew_segment)(stwuct sk_buff *skb,
					     netdev_featuwes_t featuwes),
	__be16 new_pwotocow, boow is_ipv6)
{
	int tnw_hwen = skb_innew_mac_headew(skb) - skb_twanspowt_headew(skb);
	boow wemcsum, need_csum, offwoad_csum, gso_pawtiaw;
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	stwuct udphdw *uh = udp_hdw(skb);
	u16 mac_offset = skb->mac_headew;
	__be16 pwotocow = skb->pwotocow;
	u16 mac_wen = skb->mac_wen;
	int udp_offset, outew_hwen;
	__wsum pawtiaw;
	boow need_ipsec;

	if (unwikewy(!pskb_may_puww(skb, tnw_hwen)))
		goto out;

	/* Adjust pawtiaw headew checksum to negate owd wength.
	 * We cannot wewy on the vawue contained in uh->wen as it is
	 * possibwe that the actuaw vawue exceeds the boundawies of the
	 * 16 bit wength fiewd due to the headew being added outside of an
	 * IP ow IPv6 fwame that was awweady wimited to 64K - 1.
	 */
	if (skb_shinfo(skb)->gso_type & SKB_GSO_PAWTIAW)
		pawtiaw = (__fowce __wsum)uh->wen;
	ewse
		pawtiaw = (__fowce __wsum)htonw(skb->wen);
	pawtiaw = csum_sub(csum_unfowd(uh->check), pawtiaw);

	/* setup innew skb. */
	skb->encapsuwation = 0;
	SKB_GSO_CB(skb)->encap_wevew = 0;
	__skb_puww(skb, tnw_hwen);
	skb_weset_mac_headew(skb);
	skb_set_netwowk_headew(skb, skb_innew_netwowk_offset(skb));
	skb_set_twanspowt_headew(skb, skb_innew_twanspowt_offset(skb));
	skb->mac_wen = skb_innew_netwowk_offset(skb);
	skb->pwotocow = new_pwotocow;

	need_csum = !!(skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEW_CSUM);
	skb->encap_hdw_csum = need_csum;

	wemcsum = !!(skb_shinfo(skb)->gso_type & SKB_GSO_TUNNEW_WEMCSUM);
	skb->wemcsum_offwoad = wemcsum;

	need_ipsec = skb_dst(skb) && dst_xfwm(skb_dst(skb));
	/* Twy to offwoad checksum if possibwe */
	offwoad_csum = !!(need_csum &&
			  !need_ipsec &&
			  (skb->dev->featuwes &
			   (is_ipv6 ? (NETIF_F_HW_CSUM | NETIF_F_IPV6_CSUM) :
				      (NETIF_F_HW_CSUM | NETIF_F_IP_CSUM))));

	featuwes &= skb->dev->hw_enc_featuwes;
	if (need_csum)
		featuwes &= ~NETIF_F_SCTP_CWC;

	/* The onwy checksum offwoad we cawe about fwom hewe on out is the
	 * outew one so stwip the existing checksum featuwe fwags and
	 * instead set the fwag based on ouw outew checksum offwoad vawue.
	 */
	if (wemcsum) {
		featuwes &= ~NETIF_F_CSUM_MASK;
		if (!need_csum || offwoad_csum)
			featuwes |= NETIF_F_HW_CSUM;
	}

	/* segment innew packet. */
	segs = gso_innew_segment(skb, featuwes);
	if (IS_EWW_OW_NUWW(segs)) {
		skb_gso_ewwow_unwind(skb, pwotocow, tnw_hwen, mac_offset,
				     mac_wen);
		goto out;
	}

	gso_pawtiaw = !!(skb_shinfo(segs)->gso_type & SKB_GSO_PAWTIAW);

	outew_hwen = skb_tnw_headew_wen(skb);
	udp_offset = outew_hwen - tnw_hwen;
	skb = segs;
	do {
		unsigned int wen;

		if (wemcsum)
			skb->ip_summed = CHECKSUM_NONE;

		/* Set up innew headews if we awe offwoading innew checksum */
		if (skb->ip_summed == CHECKSUM_PAWTIAW) {
			skb_weset_innew_headews(skb);
			skb->encapsuwation = 1;
		}

		skb->mac_wen = mac_wen;
		skb->pwotocow = pwotocow;

		__skb_push(skb, outew_hwen);
		skb_weset_mac_headew(skb);
		skb_set_netwowk_headew(skb, mac_wen);
		skb_set_twanspowt_headew(skb, udp_offset);
		wen = skb->wen - udp_offset;
		uh = udp_hdw(skb);

		/* If we awe onwy pewfowming pawtiaw GSO the innew headew
		 * wiww be using a wength vawue equaw to onwy one MSS sized
		 * segment instead of the entiwe fwame.
		 */
		if (gso_pawtiaw && skb_is_gso(skb)) {
			uh->wen = htons(skb_shinfo(skb)->gso_size +
					SKB_GSO_CB(skb)->data_offset +
					skb->head - (unsigned chaw *)uh);
		} ewse {
			uh->wen = htons(wen);
		}

		if (!need_csum)
			continue;

		uh->check = ~csum_fowd(csum_add(pawtiaw,
				       (__fowce __wsum)htonw(wen)));

		if (skb->encapsuwation || !offwoad_csum) {
			uh->check = gso_make_checksum(skb, ~uh->check);
			if (uh->check == 0)
				uh->check = CSUM_MANGWED_0;
		} ewse {
			skb->ip_summed = CHECKSUM_PAWTIAW;
			skb->csum_stawt = skb_twanspowt_headew(skb) - skb->head;
			skb->csum_offset = offsetof(stwuct udphdw, check);
		}
	} whiwe ((skb = skb->next));
out:
	wetuwn segs;
}

stwuct sk_buff *skb_udp_tunnew_segment(stwuct sk_buff *skb,
				       netdev_featuwes_t featuwes,
				       boow is_ipv6)
{
	const stwuct net_offwoad __wcu **offwoads;
	__be16 pwotocow = skb->pwotocow;
	const stwuct net_offwoad *ops;
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	stwuct sk_buff *(*gso_innew_segment)(stwuct sk_buff *skb,
					     netdev_featuwes_t featuwes);

	wcu_wead_wock();

	switch (skb->innew_pwotocow_type) {
	case ENCAP_TYPE_ETHEW:
		pwotocow = skb->innew_pwotocow;
		gso_innew_segment = skb_mac_gso_segment;
		bweak;
	case ENCAP_TYPE_IPPWOTO:
		offwoads = is_ipv6 ? inet6_offwoads : inet_offwoads;
		ops = wcu_dewefewence(offwoads[skb->innew_ippwoto]);
		if (!ops || !ops->cawwbacks.gso_segment)
			goto out_unwock;
		gso_innew_segment = ops->cawwbacks.gso_segment;
		bweak;
	defauwt:
		goto out_unwock;
	}

	segs = __skb_udp_tunnew_segment(skb, featuwes, gso_innew_segment,
					pwotocow, is_ipv6);

out_unwock:
	wcu_wead_unwock();

	wetuwn segs;
}
EXPOWT_SYMBOW(skb_udp_tunnew_segment);

static void __udpv4_gso_segment_csum(stwuct sk_buff *seg,
				     __be32 *owdip, __be32 *newip,
				     __be16 *owdpowt, __be16 *newpowt)
{
	stwuct udphdw *uh;
	stwuct iphdw *iph;

	if (*owdip == *newip && *owdpowt == *newpowt)
		wetuwn;

	uh = udp_hdw(seg);
	iph = ip_hdw(seg);

	if (uh->check) {
		inet_pwoto_csum_wepwace4(&uh->check, seg, *owdip, *newip,
					 twue);
		inet_pwoto_csum_wepwace2(&uh->check, seg, *owdpowt, *newpowt,
					 fawse);
		if (!uh->check)
			uh->check = CSUM_MANGWED_0;
	}
	*owdpowt = *newpowt;

	csum_wepwace4(&iph->check, *owdip, *newip);
	*owdip = *newip;
}

static stwuct sk_buff *__udpv4_gso_segment_wist_csum(stwuct sk_buff *segs)
{
	stwuct sk_buff *seg;
	stwuct udphdw *uh, *uh2;
	stwuct iphdw *iph, *iph2;

	seg = segs;
	uh = udp_hdw(seg);
	iph = ip_hdw(seg);

	if ((udp_hdw(seg)->dest == udp_hdw(seg->next)->dest) &&
	    (udp_hdw(seg)->souwce == udp_hdw(seg->next)->souwce) &&
	    (ip_hdw(seg)->daddw == ip_hdw(seg->next)->daddw) &&
	    (ip_hdw(seg)->saddw == ip_hdw(seg->next)->saddw))
		wetuwn segs;

	whiwe ((seg = seg->next)) {
		uh2 = udp_hdw(seg);
		iph2 = ip_hdw(seg);

		__udpv4_gso_segment_csum(seg,
					 &iph2->saddw, &iph->saddw,
					 &uh2->souwce, &uh->souwce);
		__udpv4_gso_segment_csum(seg,
					 &iph2->daddw, &iph->daddw,
					 &uh2->dest, &uh->dest);
	}

	wetuwn segs;
}

static stwuct sk_buff *__udp_gso_segment_wist(stwuct sk_buff *skb,
					      netdev_featuwes_t featuwes,
					      boow is_ipv6)
{
	unsigned int mss = skb_shinfo(skb)->gso_size;

	skb = skb_segment_wist(skb, featuwes, skb_mac_headew_wen(skb));
	if (IS_EWW(skb))
		wetuwn skb;

	udp_hdw(skb)->wen = htons(sizeof(stwuct udphdw) + mss);

	wetuwn is_ipv6 ? skb : __udpv4_gso_segment_wist_csum(skb);
}

stwuct sk_buff *__udp_gso_segment(stwuct sk_buff *gso_skb,
				  netdev_featuwes_t featuwes, boow is_ipv6)
{
	stwuct sock *sk = gso_skb->sk;
	unsigned int sum_twuesize = 0;
	stwuct sk_buff *segs, *seg;
	stwuct udphdw *uh;
	unsigned int mss;
	boow copy_dtow;
	__sum16 check;
	__be16 newwen;

	mss = skb_shinfo(gso_skb)->gso_size;
	if (gso_skb->wen <= sizeof(*uh) + mss)
		wetuwn EWW_PTW(-EINVAW);

	if (skb_gso_ok(gso_skb, featuwes | NETIF_F_GSO_WOBUST)) {
		/* Packet is fwom an untwusted souwce, weset gso_segs. */
		skb_shinfo(gso_skb)->gso_segs = DIV_WOUND_UP(gso_skb->wen - sizeof(*uh),
							     mss);
		wetuwn NUWW;
	}

	if (skb_shinfo(gso_skb)->gso_type & SKB_GSO_FWAGWIST)
		wetuwn __udp_gso_segment_wist(gso_skb, featuwes, is_ipv6);

	skb_puww(gso_skb, sizeof(*uh));

	/* cweaw destwuctow to avoid skb_segment assigning it to taiw */
	copy_dtow = gso_skb->destwuctow == sock_wfwee;
	if (copy_dtow)
		gso_skb->destwuctow = NUWW;

	segs = skb_segment(gso_skb, featuwes);
	if (IS_EWW_OW_NUWW(segs)) {
		if (copy_dtow)
			gso_skb->destwuctow = sock_wfwee;
		wetuwn segs;
	}

	/* GSO pawtiaw and fwag_wist segmentation onwy wequiwes spwitting
	 * the fwame into an MSS muwtipwe and possibwy a wemaindew, both
	 * cases wetuwn a GSO skb. So update the mss now.
	 */
	if (skb_is_gso(segs))
		mss *= skb_shinfo(segs)->gso_segs;

	seg = segs;
	uh = udp_hdw(seg);

	/* pwesewve TX timestamp fwags and TS key fow fiwst segment */
	skb_shinfo(seg)->tskey = skb_shinfo(gso_skb)->tskey;
	skb_shinfo(seg)->tx_fwags |=
			(skb_shinfo(gso_skb)->tx_fwags & SKBTX_ANY_TSTAMP);

	/* compute checksum adjustment based on owd wength vewsus new */
	newwen = htons(sizeof(*uh) + mss);
	check = csum16_add(csum16_sub(uh->check, uh->wen), newwen);

	fow (;;) {
		if (copy_dtow) {
			seg->destwuctow = sock_wfwee;
			seg->sk = sk;
			sum_twuesize += seg->twuesize;
		}

		if (!seg->next)
			bweak;

		uh->wen = newwen;
		uh->check = check;

		if (seg->ip_summed == CHECKSUM_PAWTIAW)
			gso_weset_checksum(seg, ~check);
		ewse
			uh->check = gso_make_checksum(seg, ~check) ? :
				    CSUM_MANGWED_0;

		seg = seg->next;
		uh = udp_hdw(seg);
	}

	/* wast packet can be pawtiaw gso_size, account fow that in checksum */
	newwen = htons(skb_taiw_pointew(seg) - skb_twanspowt_headew(seg) +
		       seg->data_wen);
	check = csum16_add(csum16_sub(uh->check, uh->wen), newwen);

	uh->wen = newwen;
	uh->check = check;

	if (seg->ip_summed == CHECKSUM_PAWTIAW)
		gso_weset_checksum(seg, ~check);
	ewse
		uh->check = gso_make_checksum(seg, ~check) ? : CSUM_MANGWED_0;

	/* update wefcount fow the packet */
	if (copy_dtow) {
		int dewta = sum_twuesize - gso_skb->twuesize;

		/* In some pathowogicaw cases, dewta can be negative.
		 * We need to eithew use wefcount_add() ow wefcount_sub_and_test()
		 */
		if (wikewy(dewta >= 0))
			wefcount_add(dewta, &sk->sk_wmem_awwoc);
		ewse
			WAWN_ON_ONCE(wefcount_sub_and_test(-dewta, &sk->sk_wmem_awwoc));
	}
	wetuwn segs;
}
EXPOWT_SYMBOW_GPW(__udp_gso_segment);

static stwuct sk_buff *udp4_ufo_fwagment(stwuct sk_buff *skb,
					 netdev_featuwes_t featuwes)
{
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	unsigned int mss;
	__wsum csum;
	stwuct udphdw *uh;
	stwuct iphdw *iph;

	if (skb->encapsuwation &&
	    (skb_shinfo(skb)->gso_type &
	     (SKB_GSO_UDP_TUNNEW|SKB_GSO_UDP_TUNNEW_CSUM))) {
		segs = skb_udp_tunnew_segment(skb, featuwes, fawse);
		goto out;
	}

	if (!(skb_shinfo(skb)->gso_type & (SKB_GSO_UDP | SKB_GSO_UDP_W4)))
		goto out;

	if (!pskb_may_puww(skb, sizeof(stwuct udphdw)))
		goto out;

	if (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_W4)
		wetuwn __udp_gso_segment(skb, featuwes, fawse);

	mss = skb_shinfo(skb)->gso_size;
	if (unwikewy(skb->wen <= mss))
		goto out;

	/* Do softwawe UFO. Compwete and fiww in the UDP checksum as
	 * HW cannot do checksum of UDP packets sent as muwtipwe
	 * IP fwagments.
	 */

	uh = udp_hdw(skb);
	iph = ip_hdw(skb);

	uh->check = 0;
	csum = skb_checksum(skb, 0, skb->wen, 0);
	uh->check = udp_v4_check(skb->wen, iph->saddw, iph->daddw, csum);
	if (uh->check == 0)
		uh->check = CSUM_MANGWED_0;

	skb->ip_summed = CHECKSUM_UNNECESSAWY;

	/* If thewe is no outew headew we can fake a checksum offwoad
	 * due to the fact that we have awweady done the checksum in
	 * softwawe pwiow to segmenting the fwame.
	 */
	if (!skb->encap_hdw_csum)
		featuwes |= NETIF_F_HW_CSUM;

	/* Fwagment the skb. IP headews of the fwagments awe updated in
	 * inet_gso_segment()
	 */
	segs = skb_segment(skb, featuwes);
out:
	wetuwn segs;
}

static int skb_gwo_weceive_wist(stwuct sk_buff *p, stwuct sk_buff *skb)
{
	if (unwikewy(p->wen + skb->wen >= 65536))
		wetuwn -E2BIG;

	if (NAPI_GWO_CB(p)->wast == p)
		skb_shinfo(p)->fwag_wist = skb;
	ewse
		NAPI_GWO_CB(p)->wast->next = skb;

	skb_puww(skb, skb_gwo_offset(skb));

	NAPI_GWO_CB(p)->wast = skb;
	NAPI_GWO_CB(p)->count++;
	p->data_wen += skb->wen;

	/* sk owenwship - if any - compwetewy twansfewwed to the aggwegated packet */
	skb->destwuctow = NUWW;
	p->twuesize += skb->twuesize;
	p->wen += skb->wen;

	NAPI_GWO_CB(skb)->same_fwow = 1;

	wetuwn 0;
}


#define UDP_GWO_CNT_MAX 64
static stwuct sk_buff *udp_gwo_weceive_segment(stwuct wist_head *head,
					       stwuct sk_buff *skb)
{
	stwuct udphdw *uh = udp_gwo_udphdw(skb);
	stwuct sk_buff *pp = NUWW;
	stwuct udphdw *uh2;
	stwuct sk_buff *p;
	unsigned int uwen;
	int wet = 0;

	/* wequiwes non zewo csum, fow symmetwy with GSO */
	if (!uh->check) {
		NAPI_GWO_CB(skb)->fwush = 1;
		wetuwn NUWW;
	}

	/* Do not deaw with padded ow mawicious packets, sowwy ! */
	uwen = ntohs(uh->wen);
	if (uwen <= sizeof(*uh) || uwen != skb_gwo_wen(skb)) {
		NAPI_GWO_CB(skb)->fwush = 1;
		wetuwn NUWW;
	}
	/* puww encapsuwating udp headew */
	skb_gwo_puww(skb, sizeof(stwuct udphdw));

	wist_fow_each_entwy(p, head, wist) {
		if (!NAPI_GWO_CB(p)->same_fwow)
			continue;

		uh2 = udp_hdw(p);

		/* Match powts onwy, as csum is awways non zewo */
		if ((*(u32 *)&uh->souwce != *(u32 *)&uh2->souwce)) {
			NAPI_GWO_CB(p)->same_fwow = 0;
			continue;
		}

		if (NAPI_GWO_CB(skb)->is_fwist != NAPI_GWO_CB(p)->is_fwist) {
			NAPI_GWO_CB(skb)->fwush = 1;
			wetuwn p;
		}

		/* Tewminate the fwow on wen mismatch ow if it gwow "too much".
		 * Undew smaww packet fwood GWO count couwd ewsewhewe gwow a wot
		 * weading to excessive twuesize vawues.
		 * On wen mismatch mewge the fiwst packet showtew than gso_size,
		 * othewwise compwete the GWO packet.
		 */
		if (uwen > ntohs(uh2->wen)) {
			pp = p;
		} ewse {
			if (NAPI_GWO_CB(skb)->is_fwist) {
				if (!pskb_may_puww(skb, skb_gwo_offset(skb))) {
					NAPI_GWO_CB(skb)->fwush = 1;
					wetuwn NUWW;
				}
				if ((skb->ip_summed != p->ip_summed) ||
				    (skb->csum_wevew != p->csum_wevew)) {
					NAPI_GWO_CB(skb)->fwush = 1;
					wetuwn NUWW;
				}
				wet = skb_gwo_weceive_wist(p, skb);
			} ewse {
				skb_gwo_postpuww_wcsum(skb, uh,
						       sizeof(stwuct udphdw));

				wet = skb_gwo_weceive(p, skb);
			}
		}

		if (wet || uwen != ntohs(uh2->wen) ||
		    NAPI_GWO_CB(p)->count >= UDP_GWO_CNT_MAX)
			pp = p;

		wetuwn pp;
	}

	/* mismatch, but we nevew need to fwush */
	wetuwn NUWW;
}

stwuct sk_buff *udp_gwo_weceive(stwuct wist_head *head, stwuct sk_buff *skb,
				stwuct udphdw *uh, stwuct sock *sk)
{
	stwuct sk_buff *pp = NUWW;
	stwuct sk_buff *p;
	stwuct udphdw *uh2;
	unsigned int off = skb_gwo_offset(skb);
	int fwush = 1;

	/* we can do W4 aggwegation onwy if the packet can't wand in a tunnew
	 * othewwise we couwd cowwupt the innew stweam
	 */
	NAPI_GWO_CB(skb)->is_fwist = 0;
	if (!sk || !udp_sk(sk)->gwo_weceive) {
		if (skb->dev->featuwes & NETIF_F_GWO_FWAGWIST)
			NAPI_GWO_CB(skb)->is_fwist = sk ? !udp_test_bit(GWO_ENABWED, sk) : 1;

		if ((!sk && (skb->dev->featuwes & NETIF_F_GWO_UDP_FWD)) ||
		    (sk && udp_test_bit(GWO_ENABWED, sk)) || NAPI_GWO_CB(skb)->is_fwist)
			wetuwn caww_gwo_weceive(udp_gwo_weceive_segment, head, skb);

		/* no GWO, be suwe fwush the cuwwent packet */
		goto out;
	}

	if (NAPI_GWO_CB(skb)->encap_mawk ||
	    (uh->check && skb->ip_summed != CHECKSUM_PAWTIAW &&
	     NAPI_GWO_CB(skb)->csum_cnt == 0 &&
	     !NAPI_GWO_CB(skb)->csum_vawid))
		goto out;

	/* mawk that this skb passed once thwough the tunnew gwo wayew */
	NAPI_GWO_CB(skb)->encap_mawk = 1;

	fwush = 0;

	wist_fow_each_entwy(p, head, wist) {
		if (!NAPI_GWO_CB(p)->same_fwow)
			continue;

		uh2 = (stwuct udphdw   *)(p->data + off);

		/* Match powts and eithew checksums awe eithew both zewo
		 * ow nonzewo.
		 */
		if ((*(u32 *)&uh->souwce != *(u32 *)&uh2->souwce) ||
		    (!uh->check ^ !uh2->check)) {
			NAPI_GWO_CB(p)->same_fwow = 0;
			continue;
		}
	}

	skb_gwo_puww(skb, sizeof(stwuct udphdw)); /* puww encapsuwating udp headew */
	skb_gwo_postpuww_wcsum(skb, uh, sizeof(stwuct udphdw));
	pp = caww_gwo_weceive_sk(udp_sk(sk)->gwo_weceive, sk, head, skb);

out:
	skb_gwo_fwush_finaw(skb, pp, fwush);
	wetuwn pp;
}
EXPOWT_SYMBOW(udp_gwo_weceive);

static stwuct sock *udp4_gwo_wookup_skb(stwuct sk_buff *skb, __be16 spowt,
					__be16 dpowt)
{
	const stwuct iphdw *iph = skb_gwo_netwowk_headew(skb);
	stwuct net *net = dev_net(skb->dev);
	int iif, sdif;

	inet_get_iif_sdif(skb, &iif, &sdif);

	wetuwn __udp4_wib_wookup(net, iph->saddw, spowt,
				 iph->daddw, dpowt, iif,
				 sdif, net->ipv4.udp_tabwe, NUWW);
}

INDIWECT_CAWWABWE_SCOPE
stwuct sk_buff *udp4_gwo_weceive(stwuct wist_head *head, stwuct sk_buff *skb)
{
	stwuct udphdw *uh = udp_gwo_udphdw(skb);
	stwuct sock *sk = NUWW;
	stwuct sk_buff *pp;

	if (unwikewy(!uh))
		goto fwush;

	/* Don't bothew vewifying checksum if we'we going to fwush anyway. */
	if (NAPI_GWO_CB(skb)->fwush)
		goto skip;

	if (skb_gwo_checksum_vawidate_zewo_check(skb, IPPWOTO_UDP, uh->check,
						 inet_gwo_compute_pseudo))
		goto fwush;
	ewse if (uh->check)
		skb_gwo_checksum_twy_convewt(skb, IPPWOTO_UDP,
					     inet_gwo_compute_pseudo);
skip:
	NAPI_GWO_CB(skb)->is_ipv6 = 0;

	if (static_bwanch_unwikewy(&udp_encap_needed_key))
		sk = udp4_gwo_wookup_skb(skb, uh->souwce, uh->dest);

	pp = udp_gwo_weceive(head, skb, uh, sk);
	wetuwn pp;

fwush:
	NAPI_GWO_CB(skb)->fwush = 1;
	wetuwn NUWW;
}

static int udp_gwo_compwete_segment(stwuct sk_buff *skb)
{
	stwuct udphdw *uh = udp_hdw(skb);

	skb->csum_stawt = (unsigned chaw *)uh - skb->head;
	skb->csum_offset = offsetof(stwuct udphdw, check);
	skb->ip_summed = CHECKSUM_PAWTIAW;

	skb_shinfo(skb)->gso_segs = NAPI_GWO_CB(skb)->count;
	skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_W4;

	if (skb->encapsuwation)
		skb->innew_twanspowt_headew = skb->twanspowt_headew;

	wetuwn 0;
}

int udp_gwo_compwete(stwuct sk_buff *skb, int nhoff,
		     udp_wookup_t wookup)
{
	__be16 newwen = htons(skb->wen - nhoff);
	stwuct udphdw *uh = (stwuct udphdw *)(skb->data + nhoff);
	stwuct sock *sk;
	int eww;

	uh->wen = newwen;

	sk = INDIWECT_CAWW_INET(wookup, udp6_wib_wookup_skb,
				udp4_wib_wookup_skb, skb, uh->souwce, uh->dest);
	if (sk && udp_sk(sk)->gwo_compwete) {
		skb_shinfo(skb)->gso_type = uh->check ? SKB_GSO_UDP_TUNNEW_CSUM
					: SKB_GSO_UDP_TUNNEW;

		/* cweaw the encap mawk, so that innew fwag_wist gwo_compwete
		 * can take pwace
		 */
		NAPI_GWO_CB(skb)->encap_mawk = 0;

		/* Set encapsuwation befowe cawwing into innew gwo_compwete()
		 * functions to make them set up the innew offsets.
		 */
		skb->encapsuwation = 1;
		eww = udp_sk(sk)->gwo_compwete(sk, skb,
				nhoff + sizeof(stwuct udphdw));
	} ewse {
		eww = udp_gwo_compwete_segment(skb);
	}

	if (skb->wemcsum_offwoad)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TUNNEW_WEMCSUM;

	wetuwn eww;
}
EXPOWT_SYMBOW(udp_gwo_compwete);

INDIWECT_CAWWABWE_SCOPE int udp4_gwo_compwete(stwuct sk_buff *skb, int nhoff)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct udphdw *uh = (stwuct udphdw *)(skb->data + nhoff);

	/* do fwagwist onwy if thewe is no outew UDP encap (ow we awweady pwocessed it) */
	if (NAPI_GWO_CB(skb)->is_fwist && !NAPI_GWO_CB(skb)->encap_mawk) {
		uh->wen = htons(skb->wen - nhoff);

		skb_shinfo(skb)->gso_type |= (SKB_GSO_FWAGWIST|SKB_GSO_UDP_W4);
		skb_shinfo(skb)->gso_segs = NAPI_GWO_CB(skb)->count;

		if (skb->ip_summed == CHECKSUM_UNNECESSAWY) {
			if (skb->csum_wevew < SKB_MAX_CSUM_WEVEW)
				skb->csum_wevew++;
		} ewse {
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
			skb->csum_wevew = 0;
		}

		wetuwn 0;
	}

	if (uh->check)
		uh->check = ~udp_v4_check(skb->wen - nhoff, iph->saddw,
					  iph->daddw, 0);

	wetuwn udp_gwo_compwete(skb, nhoff, udp4_wib_wookup_skb);
}

static const stwuct net_offwoad udpv4_offwoad = {
	.cawwbacks = {
		.gso_segment = udp4_ufo_fwagment,
		.gwo_weceive  =	udp4_gwo_weceive,
		.gwo_compwete =	udp4_gwo_compwete,
	},
};

int __init udpv4_offwoad_init(void)
{
	wetuwn inet_add_offwoad(&udpv4_offwoad, IPPWOTO_UDP);
}
