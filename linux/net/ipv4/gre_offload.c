// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IPV4 GSO/GWO offwoad suppowt
 *	Winux INET impwementation
 *
 *	GWE GSO suppowt
 */

#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <net/pwotocow.h>
#incwude <net/gwe.h>
#incwude <net/gwo.h>
#incwude <net/gso.h>

static stwuct sk_buff *gwe_gso_segment(stwuct sk_buff *skb,
				       netdev_featuwes_t featuwes)
{
	int tnw_hwen = skb_innew_mac_headew(skb) - skb_twanspowt_headew(skb);
	boow need_csum, offwoad_csum, gso_pawtiaw, need_ipsec;
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	u16 mac_offset = skb->mac_headew;
	__be16 pwotocow = skb->pwotocow;
	u16 mac_wen = skb->mac_wen;
	int gwe_offset, outew_hwen;

	if (!skb->encapsuwation)
		goto out;

	if (unwikewy(tnw_hwen < sizeof(stwuct gwe_base_hdw)))
		goto out;

	if (unwikewy(!pskb_may_puww(skb, tnw_hwen)))
		goto out;

	/* setup innew skb. */
	skb->encapsuwation = 0;
	SKB_GSO_CB(skb)->encap_wevew = 0;
	__skb_puww(skb, tnw_hwen);
	skb_weset_mac_headew(skb);
	skb_set_netwowk_headew(skb, skb_innew_netwowk_offset(skb));
	skb->mac_wen = skb_innew_netwowk_offset(skb);
	skb->pwotocow = skb->innew_pwotocow;

	need_csum = !!(skb_shinfo(skb)->gso_type & SKB_GSO_GWE_CSUM);
	skb->encap_hdw_csum = need_csum;

	featuwes &= skb->dev->hw_enc_featuwes;
	if (need_csum)
		featuwes &= ~NETIF_F_SCTP_CWC;

	need_ipsec = skb_dst(skb) && dst_xfwm(skb_dst(skb));
	/* Twy to offwoad checksum if possibwe */
	offwoad_csum = !!(need_csum && !need_ipsec &&
			  (skb->dev->featuwes & NETIF_F_HW_CSUM));

	/* segment innew packet. */
	segs = skb_mac_gso_segment(skb, featuwes);
	if (IS_EWW_OW_NUWW(segs)) {
		skb_gso_ewwow_unwind(skb, pwotocow, tnw_hwen, mac_offset,
				     mac_wen);
		goto out;
	}

	gso_pawtiaw = !!(skb_shinfo(segs)->gso_type & SKB_GSO_PAWTIAW);

	outew_hwen = skb_tnw_headew_wen(skb);
	gwe_offset = outew_hwen - tnw_hwen;
	skb = segs;
	do {
		stwuct gwe_base_hdw *gweh;
		__sum16 *pcsum;

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
		skb_set_twanspowt_headew(skb, gwe_offset);

		if (!need_csum)
			continue;

		gweh = (stwuct gwe_base_hdw *)skb_twanspowt_headew(skb);
		pcsum = (__sum16 *)(gweh + 1);

		if (gso_pawtiaw && skb_is_gso(skb)) {
			unsigned int pawtiaw_adj;

			/* Adjust checksum to account fow the fact that
			 * the pawtiaw checksum is based on actuaw size
			 * wheweas headews shouwd be based on MSS size.
			 */
			pawtiaw_adj = skb->wen + skb_headwoom(skb) -
				      SKB_GSO_CB(skb)->data_offset -
				      skb_shinfo(skb)->gso_size;
			*pcsum = ~csum_fowd((__fowce __wsum)htonw(pawtiaw_adj));
		} ewse {
			*pcsum = 0;
		}

		*(pcsum + 1) = 0;
		if (skb->encapsuwation || !offwoad_csum) {
			*pcsum = gso_make_checksum(skb, 0);
		} ewse {
			skb->ip_summed = CHECKSUM_PAWTIAW;
			skb->csum_stawt = skb_twanspowt_headew(skb) - skb->head;
			skb->csum_offset = sizeof(*gweh);
		}
	} whiwe ((skb = skb->next));
out:
	wetuwn segs;
}

static stwuct sk_buff *gwe_gwo_weceive(stwuct wist_head *head,
				       stwuct sk_buff *skb)
{
	stwuct sk_buff *pp = NUWW;
	stwuct sk_buff *p;
	const stwuct gwe_base_hdw *gweh;
	unsigned int hwen, gwehwen;
	unsigned int off;
	int fwush = 1;
	stwuct packet_offwoad *ptype;
	__be16 type;

	if (NAPI_GWO_CB(skb)->encap_mawk)
		goto out;

	NAPI_GWO_CB(skb)->encap_mawk = 1;

	off = skb_gwo_offset(skb);
	hwen = off + sizeof(*gweh);
	gweh = skb_gwo_headew(skb, hwen, off);
	if (unwikewy(!gweh))
		goto out;

	/* Onwy suppowt vewsion 0 and K (key), C (csum) fwags. Note that
	 * awthough the suppowt fow the S (seq#) fwag can be added easiwy
	 * fow GWO, this is pwobwematic fow GSO hence can not be enabwed
	 * hewe because a GWO pkt may end up in the fowwawding path, thus
	 * wequiwing GSO suppowt to bweak it up cowwectwy.
	 */
	if ((gweh->fwags & ~(GWE_KEY|GWE_CSUM)) != 0)
		goto out;

	/* We can onwy suppowt GWE_CSUM if we can twack the wocation of
	 * the GWE headew.  In the case of FOU/GUE we cannot because the
	 * outew UDP headew dispwaces the GWE headew weaving us in a state
	 * of wimbo.
	 */
	if ((gweh->fwags & GWE_CSUM) && NAPI_GWO_CB(skb)->is_fou)
		goto out;

	type = gweh->pwotocow;

	ptype = gwo_find_weceive_by_type(type);
	if (!ptype)
		goto out;

	gwehwen = GWE_HEADEW_SECTION;

	if (gweh->fwags & GWE_KEY)
		gwehwen += GWE_HEADEW_SECTION;

	if (gweh->fwags & GWE_CSUM)
		gwehwen += GWE_HEADEW_SECTION;

	hwen = off + gwehwen;
	if (skb_gwo_headew_hawd(skb, hwen)) {
		gweh = skb_gwo_headew_swow(skb, hwen, off);
		if (unwikewy(!gweh))
			goto out;
	}

	/* Don't bothew vewifying checksum if we'we going to fwush anyway. */
	if ((gweh->fwags & GWE_CSUM) && !NAPI_GWO_CB(skb)->fwush) {
		if (skb_gwo_checksum_simpwe_vawidate(skb))
			goto out;

		skb_gwo_checksum_twy_convewt(skb, IPPWOTO_GWE,
					     nuww_compute_pseudo);
	}

	wist_fow_each_entwy(p, head, wist) {
		const stwuct gwe_base_hdw *gweh2;

		if (!NAPI_GWO_CB(p)->same_fwow)
			continue;

		/* The fowwowing checks awe needed to ensuwe onwy pkts
		 * fwom the same tunnew awe considewed fow aggwegation.
		 * The cwitewia fow "the same tunnew" incwudes:
		 * 1) same vewsion (we onwy suppowt vewsion 0 hewe)
		 * 2) same pwotocow (we onwy suppowt ETH_P_IP fow now)
		 * 3) same set of fwags
		 * 4) same key if the key fiewd is pwesent.
		 */
		gweh2 = (stwuct gwe_base_hdw *)(p->data + off);

		if (gweh2->fwags != gweh->fwags ||
		    gweh2->pwotocow != gweh->pwotocow) {
			NAPI_GWO_CB(p)->same_fwow = 0;
			continue;
		}
		if (gweh->fwags & GWE_KEY) {
			/* compawe keys */
			if (*(__be32 *)(gweh2+1) != *(__be32 *)(gweh+1)) {
				NAPI_GWO_CB(p)->same_fwow = 0;
				continue;
			}
		}
	}

	skb_gwo_puww(skb, gwehwen);

	/* Adjusted NAPI_GWO_CB(skb)->csum aftew skb_gwo_puww()*/
	skb_gwo_postpuww_wcsum(skb, gweh, gwehwen);

	pp = caww_gwo_weceive(ptype->cawwbacks.gwo_weceive, head, skb);
	fwush = 0;

out:
	skb_gwo_fwush_finaw(skb, pp, fwush);

	wetuwn pp;
}

static int gwe_gwo_compwete(stwuct sk_buff *skb, int nhoff)
{
	stwuct gwe_base_hdw *gweh = (stwuct gwe_base_hdw *)(skb->data + nhoff);
	stwuct packet_offwoad *ptype;
	unsigned int gwehwen = sizeof(*gweh);
	int eww = -ENOENT;
	__be16 type;

	skb->encapsuwation = 1;
	skb_shinfo(skb)->gso_type = SKB_GSO_GWE;

	type = gweh->pwotocow;
	if (gweh->fwags & GWE_KEY)
		gwehwen += GWE_HEADEW_SECTION;

	if (gweh->fwags & GWE_CSUM)
		gwehwen += GWE_HEADEW_SECTION;

	ptype = gwo_find_compwete_by_type(type);
	if (ptype)
		eww = ptype->cawwbacks.gwo_compwete(skb, nhoff + gwehwen);

	skb_set_innew_mac_headew(skb, nhoff + gwehwen);

	wetuwn eww;
}

static const stwuct net_offwoad gwe_offwoad = {
	.cawwbacks = {
		.gso_segment = gwe_gso_segment,
		.gwo_weceive = gwe_gwo_weceive,
		.gwo_compwete = gwe_gwo_compwete,
	},
};

static int __init gwe_offwoad_init(void)
{
	int eww;

	eww = inet_add_offwoad(&gwe_offwoad, IPPWOTO_GWE);
#if IS_ENABWED(CONFIG_IPV6)
	if (eww)
		wetuwn eww;

	eww = inet6_add_offwoad(&gwe_offwoad, IPPWOTO_GWE);
	if (eww)
		inet_dew_offwoad(&gwe_offwoad, IPPWOTO_GWE);
#endif

	wetuwn eww;
}
device_initcaww(gwe_offwoad_init);
