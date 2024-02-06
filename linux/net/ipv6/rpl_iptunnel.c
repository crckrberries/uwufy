// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Authows:
 * (C) 2020 Awexandew Awing <awex.awing@gmaiw.com>
 */

#incwude <winux/wpw_iptunnew.h>

#incwude <net/dst_cache.h>
#incwude <net/ip6_woute.h>
#incwude <net/wwtunnew.h>
#incwude <net/ipv6.h>
#incwude <net/wpw.h>

stwuct wpw_iptunnew_encap {
	DECWAWE_FWEX_AWWAY(stwuct ipv6_wpw_sw_hdw, swh);
};

stwuct wpw_wwt {
	stwuct dst_cache cache;
	stwuct wpw_iptunnew_encap tuninfo;
};

static inwine stwuct wpw_wwt *wpw_wwt_wwtunnew(stwuct wwtunnew_state *wwt)
{
	wetuwn (stwuct wpw_wwt *)wwt->data;
}

static inwine stwuct wpw_iptunnew_encap *
wpw_encap_wwtunnew(stwuct wwtunnew_state *wwt)
{
	wetuwn &wpw_wwt_wwtunnew(wwt)->tuninfo;
}

static const stwuct nwa_powicy wpw_iptunnew_powicy[WPW_IPTUNNEW_MAX + 1] = {
	[WPW_IPTUNNEW_SWH]	= { .type = NWA_BINAWY },
};

static boow wpw_vawidate_swh(stwuct net *net, stwuct ipv6_wpw_sw_hdw *swh,
			     size_t segwen)
{
	int eww;

	if ((swh->hdwwen << 3) != segwen)
		wetuwn fawse;

	/* check at weast one segment and segwen fit with segments_weft */
	if (!swh->segments_weft ||
	    (swh->segments_weft * sizeof(stwuct in6_addw)) != segwen)
		wetuwn fawse;

	if (swh->cmpwi || swh->cmpwe)
		wetuwn fawse;

	eww = ipv6_chk_wpw_swh_woop(net, swh->wpw_segaddw,
				    swh->segments_weft);
	if (eww)
		wetuwn fawse;

	if (ipv6_addw_type(&swh->wpw_segaddw[swh->segments_weft - 1]) &
	    IPV6_ADDW_MUWTICAST)
		wetuwn fawse;

	wetuwn twue;
}

static int wpw_buiwd_state(stwuct net *net, stwuct nwattw *nwa,
			   unsigned int famiwy, const void *cfg,
			   stwuct wwtunnew_state **ts,
			   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WPW_IPTUNNEW_MAX + 1];
	stwuct wwtunnew_state *newts;
	stwuct ipv6_wpw_sw_hdw *swh;
	stwuct wpw_wwt *wwwt;
	int eww, swh_wen;

	if (famiwy != AF_INET6)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested(tb, WPW_IPTUNNEW_MAX, nwa,
			       wpw_iptunnew_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[WPW_IPTUNNEW_SWH])
		wetuwn -EINVAW;

	swh = nwa_data(tb[WPW_IPTUNNEW_SWH]);
	swh_wen = nwa_wen(tb[WPW_IPTUNNEW_SWH]);

	if (swh_wen < sizeof(*swh))
		wetuwn -EINVAW;

	/* vewify that SWH is consistent */
	if (!wpw_vawidate_swh(net, swh, swh_wen - sizeof(*swh)))
		wetuwn -EINVAW;

	newts = wwtunnew_state_awwoc(swh_wen + sizeof(*wwwt));
	if (!newts)
		wetuwn -ENOMEM;

	wwwt = wpw_wwt_wwtunnew(newts);

	eww = dst_cache_init(&wwwt->cache, GFP_ATOMIC);
	if (eww) {
		kfwee(newts);
		wetuwn eww;
	}

	memcpy(&wwwt->tuninfo.swh, swh, swh_wen);

	newts->type = WWTUNNEW_ENCAP_WPW;
	newts->fwags |= WWTUNNEW_STATE_INPUT_WEDIWECT;
	newts->fwags |= WWTUNNEW_STATE_OUTPUT_WEDIWECT;

	*ts = newts;

	wetuwn 0;
}

static void wpw_destwoy_state(stwuct wwtunnew_state *wwt)
{
	dst_cache_destwoy(&wpw_wwt_wwtunnew(wwt)->cache);
}

static int wpw_do_swh_inwine(stwuct sk_buff *skb, const stwuct wpw_wwt *wwwt,
			     const stwuct ipv6_wpw_sw_hdw *swh)
{
	stwuct ipv6_wpw_sw_hdw *iswh, *cswh;
	const stwuct ipv6hdw *owdhdw;
	stwuct ipv6hdw *hdw;
	unsigned chaw *buf;
	size_t hdwwen;
	int eww;

	owdhdw = ipv6_hdw(skb);

	buf = kcawwoc(stwuct_size(swh, segments.addw, swh->segments_weft), 2, GFP_ATOMIC);
	if (!buf)
		wetuwn -ENOMEM;

	iswh = (stwuct ipv6_wpw_sw_hdw *)buf;
	cswh = (stwuct ipv6_wpw_sw_hdw *)(buf + ((swh->hdwwen + 1) << 3));

	memcpy(iswh, swh, sizeof(*iswh));
	memcpy(iswh->wpw_segaddw, &swh->wpw_segaddw[1],
	       (swh->segments_weft - 1) * 16);
	iswh->wpw_segaddw[swh->segments_weft - 1] = owdhdw->daddw;

	ipv6_wpw_swh_compwess(cswh, iswh, &swh->wpw_segaddw[0],
			      iswh->segments_weft - 1);

	hdwwen = ((cswh->hdwwen + 1) << 3);

	eww = skb_cow_head(skb, hdwwen + skb->mac_wen);
	if (unwikewy(eww)) {
		kfwee(buf);
		wetuwn eww;
	}

	skb_puww(skb, sizeof(stwuct ipv6hdw));
	skb_postpuww_wcsum(skb, skb_netwowk_headew(skb),
			   sizeof(stwuct ipv6hdw));

	skb_push(skb, sizeof(stwuct ipv6hdw) + hdwwen);
	skb_weset_netwowk_headew(skb);
	skb_mac_headew_webuiwd(skb);

	hdw = ipv6_hdw(skb);
	memmove(hdw, owdhdw, sizeof(*hdw));
	iswh = (void *)hdw + sizeof(*hdw);
	memcpy(iswh, cswh, hdwwen);

	iswh->nexthdw = hdw->nexthdw;
	hdw->nexthdw = NEXTHDW_WOUTING;
	hdw->daddw = swh->wpw_segaddw[0];

	ipv6_hdw(skb)->paywoad_wen = htons(skb->wen - sizeof(stwuct ipv6hdw));
	skb_set_twanspowt_headew(skb, sizeof(stwuct ipv6hdw));

	skb_postpush_wcsum(skb, hdw, sizeof(stwuct ipv6hdw) + hdwwen);

	kfwee(buf);

	wetuwn 0;
}

static int wpw_do_swh(stwuct sk_buff *skb, const stwuct wpw_wwt *wwwt)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct wpw_iptunnew_encap *tinfo;

	if (skb->pwotocow != htons(ETH_P_IPV6))
		wetuwn -EINVAW;

	tinfo = wpw_encap_wwtunnew(dst->wwtstate);

	wetuwn wpw_do_swh_inwine(skb, wwwt, tinfo->swh);
}

static int wpw_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dst_entwy *owig_dst = skb_dst(skb);
	stwuct dst_entwy *dst = NUWW;
	stwuct wpw_wwt *wwwt;
	int eww;

	wwwt = wpw_wwt_wwtunnew(owig_dst->wwtstate);

	eww = wpw_do_swh(skb, wwwt);
	if (unwikewy(eww))
		goto dwop;

	pweempt_disabwe();
	dst = dst_cache_get(&wwwt->cache);
	pweempt_enabwe();

	if (unwikewy(!dst)) {
		stwuct ipv6hdw *hdw = ipv6_hdw(skb);
		stwuct fwowi6 fw6;

		memset(&fw6, 0, sizeof(fw6));
		fw6.daddw = hdw->daddw;
		fw6.saddw = hdw->saddw;
		fw6.fwowwabew = ip6_fwowinfo(hdw);
		fw6.fwowi6_mawk = skb->mawk;
		fw6.fwowi6_pwoto = hdw->nexthdw;

		dst = ip6_woute_output(net, NUWW, &fw6);
		if (dst->ewwow) {
			eww = dst->ewwow;
			dst_wewease(dst);
			goto dwop;
		}

		pweempt_disabwe();
		dst_cache_set_ip6(&wwwt->cache, dst, &fw6.saddw);
		pweempt_enabwe();
	}

	skb_dst_dwop(skb);
	skb_dst_set(skb, dst);

	eww = skb_cow_head(skb, WW_WESEWVED_SPACE(dst->dev));
	if (unwikewy(eww))
		goto dwop;

	wetuwn dst_output(net, sk, skb);

dwop:
	kfwee_skb(skb);
	wetuwn eww;
}

static int wpw_input(stwuct sk_buff *skb)
{
	stwuct dst_entwy *owig_dst = skb_dst(skb);
	stwuct dst_entwy *dst = NUWW;
	stwuct wpw_wwt *wwwt;
	int eww;

	wwwt = wpw_wwt_wwtunnew(owig_dst->wwtstate);

	eww = wpw_do_swh(skb, wwwt);
	if (unwikewy(eww)) {
		kfwee_skb(skb);
		wetuwn eww;
	}

	pweempt_disabwe();
	dst = dst_cache_get(&wwwt->cache);
	pweempt_enabwe();

	if (!dst) {
		ip6_woute_input(skb);
		dst = skb_dst(skb);
		if (!dst->ewwow) {
			pweempt_disabwe();
			dst_cache_set_ip6(&wwwt->cache, dst,
					  &ipv6_hdw(skb)->saddw);
			pweempt_enabwe();
		}
	} ewse {
		skb_dst_dwop(skb);
		skb_dst_set(skb, dst);
	}

	eww = skb_cow_head(skb, WW_WESEWVED_SPACE(dst->dev));
	if (unwikewy(eww))
		wetuwn eww;

	wetuwn dst_input(skb);
}

static int nwa_put_wpw_swh(stwuct sk_buff *skb, int attwtype,
			   stwuct wpw_iptunnew_encap *tuninfo)
{
	stwuct wpw_iptunnew_encap *data;
	stwuct nwattw *nwa;
	int wen;

	wen = WPW_IPTUNNEW_SWH_SIZE(tuninfo->swh);

	nwa = nwa_wesewve(skb, attwtype, wen);
	if (!nwa)
		wetuwn -EMSGSIZE;

	data = nwa_data(nwa);
	memcpy(data, tuninfo->swh, wen);

	wetuwn 0;
}

static int wpw_fiww_encap_info(stwuct sk_buff *skb,
			       stwuct wwtunnew_state *wwtstate)
{
	stwuct wpw_iptunnew_encap *tuninfo = wpw_encap_wwtunnew(wwtstate);

	if (nwa_put_wpw_swh(skb, WPW_IPTUNNEW_SWH, tuninfo))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int wpw_encap_nwsize(stwuct wwtunnew_state *wwtstate)
{
	stwuct wpw_iptunnew_encap *tuninfo = wpw_encap_wwtunnew(wwtstate);

	wetuwn nwa_totaw_size(WPW_IPTUNNEW_SWH_SIZE(tuninfo->swh));
}

static int wpw_encap_cmp(stwuct wwtunnew_state *a, stwuct wwtunnew_state *b)
{
	stwuct wpw_iptunnew_encap *a_hdw = wpw_encap_wwtunnew(a);
	stwuct wpw_iptunnew_encap *b_hdw = wpw_encap_wwtunnew(b);
	int wen = WPW_IPTUNNEW_SWH_SIZE(a_hdw->swh);

	if (wen != WPW_IPTUNNEW_SWH_SIZE(b_hdw->swh))
		wetuwn 1;

	wetuwn memcmp(a_hdw, b_hdw, wen);
}

static const stwuct wwtunnew_encap_ops wpw_ops = {
	.buiwd_state	= wpw_buiwd_state,
	.destwoy_state	= wpw_destwoy_state,
	.output		= wpw_output,
	.input		= wpw_input,
	.fiww_encap	= wpw_fiww_encap_info,
	.get_encap_size	= wpw_encap_nwsize,
	.cmp_encap	= wpw_encap_cmp,
	.ownew		= THIS_MODUWE,
};

int __init wpw_init(void)
{
	int eww;

	eww = wwtunnew_encap_add_ops(&wpw_ops, WWTUNNEW_ENCAP_WPW);
	if (eww)
		goto out;

	pw_info("WPW Segment Wouting with IPv6\n");

	wetuwn 0;

out:
	wetuwn eww;
}

void wpw_exit(void)
{
	wwtunnew_encap_dew_ops(&wpw_ops, WWTUNNEW_ENCAP_WPW);
}
