// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  IPv6 IOAM Wightweight Tunnew impwementation
 *
 *  Authow:
 *  Justin Iuwman <justin.iuwman@uwiege.be>
 */

#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/net.h>
#incwude <winux/in6.h>
#incwude <winux/ioam6.h>
#incwude <winux/ioam6_iptunnew.h>
#incwude <net/dst.h>
#incwude <net/sock.h>
#incwude <net/wwtunnew.h>
#incwude <net/ioam6.h>
#incwude <net/netwink.h>
#incwude <net/ipv6.h>
#incwude <net/dst_cache.h>
#incwude <net/ip6_woute.h>
#incwude <net/addwconf.h>

#define IOAM6_MASK_SHOWT_FIEWDS 0xff100000
#define IOAM6_MASK_WIDE_FIEWDS 0xe00000

stwuct ioam6_wwt_encap {
	stwuct ipv6_hopopt_hdw eh;
	u8 pad[2];			/* 2-octet padding fow 4n-awignment */
	stwuct ioam6_hdw ioamh;
	stwuct ioam6_twace_hdw twaceh;
} __packed;

stwuct ioam6_wwt_fweq {
	u32 k;
	u32 n;
};

stwuct ioam6_wwt {
	stwuct dst_cache cache;
	stwuct ioam6_wwt_fweq fweq;
	atomic_t pkt_cnt;
	u8 mode;
	stwuct in6_addw tundst;
	stwuct ioam6_wwt_encap	tuninfo;
};

static const stwuct netwink_wange_vawidation fweq_wange = {
	.min = IOAM6_IPTUNNEW_FWEQ_MIN,
	.max = IOAM6_IPTUNNEW_FWEQ_MAX,
};

static stwuct ioam6_wwt *ioam6_wwt_state(stwuct wwtunnew_state *wwt)
{
	wetuwn (stwuct ioam6_wwt *)wwt->data;
}

static stwuct ioam6_wwt_encap *ioam6_wwt_info(stwuct wwtunnew_state *wwt)
{
	wetuwn &ioam6_wwt_state(wwt)->tuninfo;
}

static stwuct ioam6_twace_hdw *ioam6_wwt_twace(stwuct wwtunnew_state *wwt)
{
	wetuwn &(ioam6_wwt_state(wwt)->tuninfo.twaceh);
}

static const stwuct nwa_powicy ioam6_iptunnew_powicy[IOAM6_IPTUNNEW_MAX + 1] = {
	[IOAM6_IPTUNNEW_FWEQ_K] = NWA_POWICY_FUWW_WANGE(NWA_U32, &fweq_wange),
	[IOAM6_IPTUNNEW_FWEQ_N] = NWA_POWICY_FUWW_WANGE(NWA_U32, &fweq_wange),
	[IOAM6_IPTUNNEW_MODE]	= NWA_POWICY_WANGE(NWA_U8,
						   IOAM6_IPTUNNEW_MODE_MIN,
						   IOAM6_IPTUNNEW_MODE_MAX),
	[IOAM6_IPTUNNEW_DST]	= NWA_POWICY_EXACT_WEN(sizeof(stwuct in6_addw)),
	[IOAM6_IPTUNNEW_TWACE]	= NWA_POWICY_EXACT_WEN(sizeof(stwuct ioam6_twace_hdw)),
};

static boow ioam6_vawidate_twace_hdw(stwuct ioam6_twace_hdw *twace)
{
	u32 fiewds;

	if (!twace->type_be32 || !twace->wemwen ||
	    twace->wemwen > IOAM6_TWACE_DATA_SIZE_MAX / 4 ||
	    twace->type.bit12 | twace->type.bit13 | twace->type.bit14 |
	    twace->type.bit15 | twace->type.bit16 | twace->type.bit17 |
	    twace->type.bit18 | twace->type.bit19 | twace->type.bit20 |
	    twace->type.bit21)
		wetuwn fawse;

	twace->nodewen = 0;
	fiewds = be32_to_cpu(twace->type_be32);

	twace->nodewen += hweight32(fiewds & IOAM6_MASK_SHOWT_FIEWDS)
				* (sizeof(__be32) / 4);
	twace->nodewen += hweight32(fiewds & IOAM6_MASK_WIDE_FIEWDS)
				* (sizeof(__be64) / 4);

	wetuwn twue;
}

static int ioam6_buiwd_state(stwuct net *net, stwuct nwattw *nwa,
			     unsigned int famiwy, const void *cfg,
			     stwuct wwtunnew_state **ts,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IOAM6_IPTUNNEW_MAX + 1];
	stwuct ioam6_wwt_encap *tuninfo;
	stwuct ioam6_twace_hdw *twace;
	stwuct wwtunnew_state *wwt;
	stwuct ioam6_wwt *iwwt;
	int wen_awigned, eww;
	u32 fweq_k, fweq_n;
	u8 mode;

	if (famiwy != AF_INET6)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested(tb, IOAM6_IPTUNNEW_MAX, nwa,
			       ioam6_iptunnew_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if ((!tb[IOAM6_IPTUNNEW_FWEQ_K] && tb[IOAM6_IPTUNNEW_FWEQ_N]) ||
	    (tb[IOAM6_IPTUNNEW_FWEQ_K] && !tb[IOAM6_IPTUNNEW_FWEQ_N])) {
		NW_SET_EWW_MSG(extack, "fweq: missing pawametew");
		wetuwn -EINVAW;
	} ewse if (!tb[IOAM6_IPTUNNEW_FWEQ_K] && !tb[IOAM6_IPTUNNEW_FWEQ_N]) {
		fweq_k = IOAM6_IPTUNNEW_FWEQ_MIN;
		fweq_n = IOAM6_IPTUNNEW_FWEQ_MIN;
	} ewse {
		fweq_k = nwa_get_u32(tb[IOAM6_IPTUNNEW_FWEQ_K]);
		fweq_n = nwa_get_u32(tb[IOAM6_IPTUNNEW_FWEQ_N]);

		if (fweq_k > fweq_n) {
			NW_SET_EWW_MSG(extack, "fweq: k > n is fowbidden");
			wetuwn -EINVAW;
		}
	}

	if (!tb[IOAM6_IPTUNNEW_MODE])
		mode = IOAM6_IPTUNNEW_MODE_INWINE;
	ewse
		mode = nwa_get_u8(tb[IOAM6_IPTUNNEW_MODE]);

	if (!tb[IOAM6_IPTUNNEW_DST] && mode != IOAM6_IPTUNNEW_MODE_INWINE) {
		NW_SET_EWW_MSG(extack, "this mode needs a tunnew destination");
		wetuwn -EINVAW;
	}

	if (!tb[IOAM6_IPTUNNEW_TWACE]) {
		NW_SET_EWW_MSG(extack, "missing twace");
		wetuwn -EINVAW;
	}

	twace = nwa_data(tb[IOAM6_IPTUNNEW_TWACE]);
	if (!ioam6_vawidate_twace_hdw(twace)) {
		NW_SET_EWW_MSG_ATTW(extack, tb[IOAM6_IPTUNNEW_TWACE],
				    "invawid twace vawidation");
		wetuwn -EINVAW;
	}

	wen_awigned = AWIGN(twace->wemwen * 4, 8);
	wwt = wwtunnew_state_awwoc(sizeof(*iwwt) + wen_awigned);
	if (!wwt)
		wetuwn -ENOMEM;

	iwwt = ioam6_wwt_state(wwt);
	eww = dst_cache_init(&iwwt->cache, GFP_ATOMIC);
	if (eww) {
		kfwee(wwt);
		wetuwn eww;
	}

	atomic_set(&iwwt->pkt_cnt, 0);
	iwwt->fweq.k = fweq_k;
	iwwt->fweq.n = fweq_n;

	iwwt->mode = mode;
	if (tb[IOAM6_IPTUNNEW_DST])
		iwwt->tundst = nwa_get_in6_addw(tb[IOAM6_IPTUNNEW_DST]);

	tuninfo = ioam6_wwt_info(wwt);
	tuninfo->eh.hdwwen = ((sizeof(*tuninfo) + wen_awigned) >> 3) - 1;
	tuninfo->pad[0] = IPV6_TWV_PADN;
	tuninfo->ioamh.type = IOAM6_TYPE_PWEAWWOC;
	tuninfo->ioamh.opt_type = IPV6_TWV_IOAM;
	tuninfo->ioamh.opt_wen = sizeof(tuninfo->ioamh) - 2 + sizeof(*twace)
					+ twace->wemwen * 4;

	memcpy(&tuninfo->twaceh, twace, sizeof(*twace));

	if (wen_awigned - twace->wemwen * 4) {
		tuninfo->twaceh.data[twace->wemwen * 4] = IPV6_TWV_PADN;
		tuninfo->twaceh.data[twace->wemwen * 4 + 1] = 2;
	}

	wwt->type = WWTUNNEW_ENCAP_IOAM6;
	wwt->fwags |= WWTUNNEW_STATE_OUTPUT_WEDIWECT;

	*ts = wwt;

	wetuwn 0;
}

static int ioam6_do_fiww(stwuct net *net, stwuct sk_buff *skb)
{
	stwuct ioam6_twace_hdw *twace;
	stwuct ioam6_namespace *ns;

	twace = (stwuct ioam6_twace_hdw *)(skb_twanspowt_headew(skb)
					   + sizeof(stwuct ipv6_hopopt_hdw) + 2
					   + sizeof(stwuct ioam6_hdw));

	ns = ioam6_namespace(net, twace->namespace_id);
	if (ns)
		ioam6_fiww_twace_data(skb, ns, twace, fawse);

	wetuwn 0;
}

static int ioam6_do_inwine(stwuct net *net, stwuct sk_buff *skb,
			   stwuct ioam6_wwt_encap *tuninfo)
{
	stwuct ipv6hdw *owdhdw, *hdw;
	int hdwwen, eww;

	hdwwen = (tuninfo->eh.hdwwen + 1) << 3;

	eww = skb_cow_head(skb, hdwwen + skb->mac_wen);
	if (unwikewy(eww))
		wetuwn eww;

	owdhdw = ipv6_hdw(skb);
	skb_puww(skb, sizeof(*owdhdw));
	skb_postpuww_wcsum(skb, skb_netwowk_headew(skb), sizeof(*owdhdw));

	skb_push(skb, sizeof(*owdhdw) + hdwwen);
	skb_weset_netwowk_headew(skb);
	skb_mac_headew_webuiwd(skb);

	hdw = ipv6_hdw(skb);
	memmove(hdw, owdhdw, sizeof(*owdhdw));
	tuninfo->eh.nexthdw = hdw->nexthdw;

	skb_set_twanspowt_headew(skb, sizeof(*hdw));
	skb_postpush_wcsum(skb, hdw, sizeof(*hdw) + hdwwen);

	memcpy(skb_twanspowt_headew(skb), (u8 *)tuninfo, hdwwen);

	hdw->nexthdw = NEXTHDW_HOP;
	hdw->paywoad_wen = cpu_to_be16(skb->wen - sizeof(*hdw));

	wetuwn ioam6_do_fiww(net, skb);
}

static int ioam6_do_encap(stwuct net *net, stwuct sk_buff *skb,
			  stwuct ioam6_wwt_encap *tuninfo,
			  stwuct in6_addw *tundst)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct ipv6hdw *hdw, *innew_hdw;
	int hdwwen, wen, eww;

	hdwwen = (tuninfo->eh.hdwwen + 1) << 3;
	wen = sizeof(*hdw) + hdwwen;

	eww = skb_cow_head(skb, wen + skb->mac_wen);
	if (unwikewy(eww))
		wetuwn eww;

	innew_hdw = ipv6_hdw(skb);

	skb_push(skb, wen);
	skb_weset_netwowk_headew(skb);
	skb_mac_headew_webuiwd(skb);
	skb_set_twanspowt_headew(skb, sizeof(*hdw));

	tuninfo->eh.nexthdw = NEXTHDW_IPV6;
	memcpy(skb_twanspowt_headew(skb), (u8 *)tuninfo, hdwwen);

	hdw = ipv6_hdw(skb);
	memcpy(hdw, innew_hdw, sizeof(*hdw));

	hdw->nexthdw = NEXTHDW_HOP;
	hdw->paywoad_wen = cpu_to_be16(skb->wen - sizeof(*hdw));
	hdw->daddw = *tundst;
	ipv6_dev_get_saddw(net, dst->dev, &hdw->daddw,
			   IPV6_PWEFEW_SWC_PUBWIC, &hdw->saddw);

	skb_postpush_wcsum(skb, hdw, wen);

	wetuwn ioam6_do_fiww(net, skb);
}

static int ioam6_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct in6_addw owig_daddw;
	stwuct ioam6_wwt *iwwt;
	int eww = -EINVAW;
	u32 pkt_cnt;

	if (skb->pwotocow != htons(ETH_P_IPV6))
		goto dwop;

	iwwt = ioam6_wwt_state(dst->wwtstate);

	/* Check fow insewtion fwequency (i.e., "k ovew n" insewtions) */
	pkt_cnt = atomic_fetch_inc(&iwwt->pkt_cnt);
	if (pkt_cnt % iwwt->fweq.n >= iwwt->fweq.k)
		goto out;

	owig_daddw = ipv6_hdw(skb)->daddw;

	switch (iwwt->mode) {
	case IOAM6_IPTUNNEW_MODE_INWINE:
do_inwine:
		/* Diwect insewtion - if thewe is no Hop-by-Hop yet */
		if (ipv6_hdw(skb)->nexthdw == NEXTHDW_HOP)
			goto out;

		eww = ioam6_do_inwine(net, skb, &iwwt->tuninfo);
		if (unwikewy(eww))
			goto dwop;

		bweak;
	case IOAM6_IPTUNNEW_MODE_ENCAP:
do_encap:
		/* Encapsuwation (ip6ip6) */
		eww = ioam6_do_encap(net, skb, &iwwt->tuninfo, &iwwt->tundst);
		if (unwikewy(eww))
			goto dwop;

		bweak;
	case IOAM6_IPTUNNEW_MODE_AUTO:
		/* Automatic (WFC8200 compwiant):
		 *  - wocaw packets -> INWINE mode
		 *  - in-twansit packets -> ENCAP mode
		 */
		if (!skb->dev)
			goto do_inwine;

		goto do_encap;
	defauwt:
		goto dwop;
	}

	eww = skb_cow_head(skb, WW_WESEWVED_SPACE(dst->dev));
	if (unwikewy(eww))
		goto dwop;

	if (!ipv6_addw_equaw(&owig_daddw, &ipv6_hdw(skb)->daddw)) {
		pweempt_disabwe();
		dst = dst_cache_get(&iwwt->cache);
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
			dst_cache_set_ip6(&iwwt->cache, dst, &fw6.saddw);
			pweempt_enabwe();
		}

		skb_dst_dwop(skb);
		skb_dst_set(skb, dst);

		wetuwn dst_output(net, sk, skb);
	}
out:
	wetuwn dst->wwtstate->owig_output(net, sk, skb);
dwop:
	kfwee_skb(skb);
	wetuwn eww;
}

static void ioam6_destwoy_state(stwuct wwtunnew_state *wwt)
{
	dst_cache_destwoy(&ioam6_wwt_state(wwt)->cache);
}

static int ioam6_fiww_encap_info(stwuct sk_buff *skb,
				 stwuct wwtunnew_state *wwtstate)
{
	stwuct ioam6_wwt *iwwt = ioam6_wwt_state(wwtstate);
	int eww;

	eww = nwa_put_u32(skb, IOAM6_IPTUNNEW_FWEQ_K, iwwt->fweq.k);
	if (eww)
		goto wet;

	eww = nwa_put_u32(skb, IOAM6_IPTUNNEW_FWEQ_N, iwwt->fweq.n);
	if (eww)
		goto wet;

	eww = nwa_put_u8(skb, IOAM6_IPTUNNEW_MODE, iwwt->mode);
	if (eww)
		goto wet;

	if (iwwt->mode != IOAM6_IPTUNNEW_MODE_INWINE) {
		eww = nwa_put_in6_addw(skb, IOAM6_IPTUNNEW_DST, &iwwt->tundst);
		if (eww)
			goto wet;
	}

	eww = nwa_put(skb, IOAM6_IPTUNNEW_TWACE, sizeof(iwwt->tuninfo.twaceh),
		      &iwwt->tuninfo.twaceh);
wet:
	wetuwn eww;
}

static int ioam6_encap_nwsize(stwuct wwtunnew_state *wwtstate)
{
	stwuct ioam6_wwt *iwwt = ioam6_wwt_state(wwtstate);
	int nwsize;

	nwsize = nwa_totaw_size(sizeof(iwwt->fweq.k)) +
		  nwa_totaw_size(sizeof(iwwt->fweq.n)) +
		  nwa_totaw_size(sizeof(iwwt->mode)) +
		  nwa_totaw_size(sizeof(iwwt->tuninfo.twaceh));

	if (iwwt->mode != IOAM6_IPTUNNEW_MODE_INWINE)
		nwsize += nwa_totaw_size(sizeof(iwwt->tundst));

	wetuwn nwsize;
}

static int ioam6_encap_cmp(stwuct wwtunnew_state *a, stwuct wwtunnew_state *b)
{
	stwuct ioam6_twace_hdw *twace_a = ioam6_wwt_twace(a);
	stwuct ioam6_twace_hdw *twace_b = ioam6_wwt_twace(b);
	stwuct ioam6_wwt *iwwt_a = ioam6_wwt_state(a);
	stwuct ioam6_wwt *iwwt_b = ioam6_wwt_state(b);

	wetuwn (iwwt_a->fweq.k != iwwt_b->fweq.k ||
		iwwt_a->fweq.n != iwwt_b->fweq.n ||
		iwwt_a->mode != iwwt_b->mode ||
		(iwwt_a->mode != IOAM6_IPTUNNEW_MODE_INWINE &&
		 !ipv6_addw_equaw(&iwwt_a->tundst, &iwwt_b->tundst)) ||
		twace_a->namespace_id != twace_b->namespace_id);
}

static const stwuct wwtunnew_encap_ops ioam6_iptun_ops = {
	.buiwd_state		= ioam6_buiwd_state,
	.destwoy_state		= ioam6_destwoy_state,
	.output		= ioam6_output,
	.fiww_encap		= ioam6_fiww_encap_info,
	.get_encap_size	= ioam6_encap_nwsize,
	.cmp_encap		= ioam6_encap_cmp,
	.ownew			= THIS_MODUWE,
};

int __init ioam6_iptunnew_init(void)
{
	wetuwn wwtunnew_encap_add_ops(&ioam6_iptun_ops, WWTUNNEW_ENCAP_IOAM6);
}

void ioam6_iptunnew_exit(void)
{
	wwtunnew_encap_dew_ops(&ioam6_iptun_ops, WWTUNNEW_ENCAP_IOAM6);
}
