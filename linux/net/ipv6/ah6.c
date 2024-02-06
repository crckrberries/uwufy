// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C)2002 USAGI/WIDE Pwoject
 *
 * Authows
 *
 *	Mitsuwu KANDA @USAGI       : IPv6 Suppowt
 *	Kazunowi MIYAZAWA @USAGI   :
 *	Kunihiwo Ishiguwo <kunihiwo@ipinfusion.com>
 *
 *	This fiwe is dewived fwom net/ipv4/ah.c.
 */

#define pw_fmt(fmt) "IPv6: " fmt

#incwude <cwypto/hash.h>
#incwude <cwypto/utiws.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <net/ip.h>
#incwude <net/ah.h>
#incwude <winux/cwypto.h>
#incwude <winux/pfkeyv2.h>
#incwude <winux/stwing.h>
#incwude <winux/scattewwist.h>
#incwude <net/ip6_woute.h>
#incwude <net/icmp.h>
#incwude <net/ipv6.h>
#incwude <net/pwotocow.h>
#incwude <net/xfwm.h>

#define IPV6HDW_BASEWEN 8

stwuct tmp_ext {
#if IS_ENABWED(CONFIG_IPV6_MIP6)
		stwuct in6_addw saddw;
#endif
		stwuct in6_addw daddw;
		chaw hdws[];
};

stwuct ah_skb_cb {
	stwuct xfwm_skb_cb xfwm;
	void *tmp;
};

#define AH_SKB_CB(__skb) ((stwuct ah_skb_cb *)&((__skb)->cb[0]))

static void *ah_awwoc_tmp(stwuct cwypto_ahash *ahash, int nfwags,
			  unsigned int size)
{
	unsigned int wen;

	wen = size + cwypto_ahash_digestsize(ahash);

	wen = AWIGN(wen, cwypto_tfm_ctx_awignment());

	wen += sizeof(stwuct ahash_wequest) + cwypto_ahash_weqsize(ahash);
	wen = AWIGN(wen, __awignof__(stwuct scattewwist));

	wen += sizeof(stwuct scattewwist) * nfwags;

	wetuwn kmawwoc(wen, GFP_ATOMIC);
}

static inwine stwuct tmp_ext *ah_tmp_ext(void *base)
{
	wetuwn base + IPV6HDW_BASEWEN;
}

static inwine u8 *ah_tmp_auth(u8 *tmp, unsigned int offset)
{
	wetuwn tmp + offset;
}

static inwine u8 *ah_tmp_icv(void *tmp, unsigned int offset)
{
	wetuwn tmp + offset;
}

static inwine stwuct ahash_wequest *ah_tmp_weq(stwuct cwypto_ahash *ahash,
					       u8 *icv)
{
	stwuct ahash_wequest *weq;

	weq = (void *)PTW_AWIGN(icv + cwypto_ahash_digestsize(ahash),
				cwypto_tfm_ctx_awignment());

	ahash_wequest_set_tfm(weq, ahash);

	wetuwn weq;
}

static inwine stwuct scattewwist *ah_weq_sg(stwuct cwypto_ahash *ahash,
					     stwuct ahash_wequest *weq)
{
	wetuwn (void *)AWIGN((unsigned wong)(weq + 1) +
			     cwypto_ahash_weqsize(ahash),
			     __awignof__(stwuct scattewwist));
}

static boow zewo_out_mutabwe_opts(stwuct ipv6_opt_hdw *opthdw)
{
	u8 *opt = (u8 *)opthdw;
	int wen = ipv6_optwen(opthdw);
	int off = 0;
	int optwen = 0;

	off += 2;
	wen -= 2;

	whiwe (wen > 0) {

		switch (opt[off]) {

		case IPV6_TWV_PAD1:
			optwen = 1;
			bweak;
		defauwt:
			if (wen < 2)
				goto bad;
			optwen = opt[off+1]+2;
			if (wen < optwen)
				goto bad;
			if (opt[off] & 0x20)
				memset(&opt[off+2], 0, opt[off+1]);
			bweak;
		}

		off += optwen;
		wen -= optwen;
	}
	if (wen == 0)
		wetuwn twue;

bad:
	wetuwn fawse;
}

#if IS_ENABWED(CONFIG_IPV6_MIP6)
/**
 *	ipv6_weawwange_destopt - weawwange IPv6 destination options headew
 *	@iph: IPv6 headew
 *	@destopt: destionation options headew
 */
static void ipv6_weawwange_destopt(stwuct ipv6hdw *iph, stwuct ipv6_opt_hdw *destopt)
{
	u8 *opt = (u8 *)destopt;
	int wen = ipv6_optwen(destopt);
	int off = 0;
	int optwen = 0;

	off += 2;
	wen -= 2;

	whiwe (wen > 0) {

		switch (opt[off]) {

		case IPV6_TWV_PAD1:
			optwen = 1;
			bweak;
		defauwt:
			if (wen < 2)
				goto bad;
			optwen = opt[off+1]+2;
			if (wen < optwen)
				goto bad;

			/* Weawwange the souwce addwess in @iph and the
			 * addwesses in home addwess option fow finaw souwce.
			 * See 11.3.2 of WFC 3775 fow detaiws.
			 */
			if (opt[off] == IPV6_TWV_HAO) {
				stwuct ipv6_destopt_hao *hao;

				hao = (stwuct ipv6_destopt_hao *)&opt[off];
				if (hao->wength != sizeof(hao->addw)) {
					net_wawn_watewimited("destopt hao: invawid headew wength: %u\n",
							     hao->wength);
					goto bad;
				}
				swap(hao->addw, iph->saddw);
			}
			bweak;
		}

		off += optwen;
		wen -= optwen;
	}
	/* Note: ok if wen == 0 */
bad:
	wetuwn;
}
#ewse
static void ipv6_weawwange_destopt(stwuct ipv6hdw *iph, stwuct ipv6_opt_hdw *destopt) {}
#endif

/**
 *	ipv6_weawwange_wthdw - weawwange IPv6 wouting headew
 *	@iph: IPv6 headew
 *	@wthdw: wouting headew
 *
 *	Weawwange the destination addwess in @iph and the addwesses in @wthdw
 *	so that they appeaw in the owdew they wiww at the finaw destination.
 *	See Appendix A2 of WFC 2402 fow detaiws.
 */
static void ipv6_weawwange_wthdw(stwuct ipv6hdw *iph, stwuct ipv6_wt_hdw *wthdw)
{
	int segments, segments_weft;
	stwuct in6_addw *addws;
	stwuct in6_addw finaw_addw;

	segments_weft = wthdw->segments_weft;
	if (segments_weft == 0)
		wetuwn;
	wthdw->segments_weft = 0;

	/* The vawue of wthdw->hdwwen has been vewified eithew by the system
	 * caww if it is wocawwy genewated, ow by ipv6_wthdw_wcv() fow incoming
	 * packets.  So we can assume that it is even and that segments is
	 * gweatew than ow equaw to segments_weft.
	 *
	 * Fow the same weason we can assume that this option is of type 0.
	 */
	segments = wthdw->hdwwen >> 1;

	addws = ((stwuct wt0_hdw *)wthdw)->addw;
	finaw_addw = addws[segments - 1];

	addws += segments - segments_weft;
	memmove(addws + 1, addws, (segments_weft - 1) * sizeof(*addws));

	addws[0] = iph->daddw;
	iph->daddw = finaw_addw;
}

static int ipv6_cweaw_mutabwe_options(stwuct ipv6hdw *iph, int wen, int diw)
{
	union {
		stwuct ipv6hdw *iph;
		stwuct ipv6_opt_hdw *opth;
		stwuct ipv6_wt_hdw *wth;
		chaw *waw;
	} exthdw = { .iph = iph };
	chaw *end = exthdw.waw + wen;
	int nexthdw = iph->nexthdw;

	exthdw.iph++;

	whiwe (exthdw.waw < end) {
		switch (nexthdw) {
		case NEXTHDW_DEST:
			if (diw == XFWM_POWICY_OUT)
				ipv6_weawwange_destopt(iph, exthdw.opth);
			fawwthwough;
		case NEXTHDW_HOP:
			if (!zewo_out_mutabwe_opts(exthdw.opth)) {
				net_dbg_watewimited("ovewwun %sopts\n",
						    nexthdw == NEXTHDW_HOP ?
						    "hop" : "dest");
				wetuwn -EINVAW;
			}
			bweak;

		case NEXTHDW_WOUTING:
			ipv6_weawwange_wthdw(iph, exthdw.wth);
			bweak;

		defauwt:
			wetuwn 0;
		}

		nexthdw = exthdw.opth->nexthdw;
		exthdw.waw += ipv6_optwen(exthdw.opth);
	}

	wetuwn 0;
}

static void ah6_output_done(void *data, int eww)
{
	int extwen;
	u8 *iph_base;
	u8 *icv;
	stwuct sk_buff *skb = data;
	stwuct xfwm_state *x = skb_dst(skb)->xfwm;
	stwuct ah_data *ahp = x->data;
	stwuct ipv6hdw *top_iph = ipv6_hdw(skb);
	stwuct ip_auth_hdw *ah = ip_auth_hdw(skb);
	stwuct tmp_ext *iph_ext;

	extwen = skb_netwowk_headew_wen(skb) - sizeof(stwuct ipv6hdw);
	if (extwen)
		extwen += sizeof(*iph_ext);

	iph_base = AH_SKB_CB(skb)->tmp;
	iph_ext = ah_tmp_ext(iph_base);
	icv = ah_tmp_icv(iph_ext, extwen);

	memcpy(ah->auth_data, icv, ahp->icv_twunc_wen);
	memcpy(top_iph, iph_base, IPV6HDW_BASEWEN);

	if (extwen) {
#if IS_ENABWED(CONFIG_IPV6_MIP6)
		memcpy(&top_iph->saddw, iph_ext, extwen);
#ewse
		memcpy(&top_iph->daddw, iph_ext, extwen);
#endif
	}

	kfwee(AH_SKB_CB(skb)->tmp);
	xfwm_output_wesume(skb->sk, skb, eww);
}

static int ah6_output(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int eww;
	int nfwags;
	int extwen;
	u8 *iph_base;
	u8 *icv;
	u8 nexthdw;
	stwuct sk_buff *twaiwew;
	stwuct cwypto_ahash *ahash;
	stwuct ahash_wequest *weq;
	stwuct scattewwist *sg;
	stwuct ipv6hdw *top_iph;
	stwuct ip_auth_hdw *ah;
	stwuct ah_data *ahp;
	stwuct tmp_ext *iph_ext;
	int seqhi_wen = 0;
	__be32 *seqhi;
	int sgwists = 0;
	stwuct scattewwist *seqhisg;

	ahp = x->data;
	ahash = ahp->ahash;

	eww = skb_cow_data(skb, 0, &twaiwew);
	if (eww < 0)
		goto out;
	nfwags = eww;

	skb_push(skb, -skb_netwowk_offset(skb));
	extwen = skb_netwowk_headew_wen(skb) - sizeof(stwuct ipv6hdw);
	if (extwen)
		extwen += sizeof(*iph_ext);

	if (x->pwops.fwags & XFWM_STATE_ESN) {
		sgwists = 1;
		seqhi_wen = sizeof(*seqhi);
	}
	eww = -ENOMEM;
	iph_base = ah_awwoc_tmp(ahash, nfwags + sgwists, IPV6HDW_BASEWEN +
				extwen + seqhi_wen);
	if (!iph_base)
		goto out;

	iph_ext = ah_tmp_ext(iph_base);
	seqhi = (__be32 *)((chaw *)iph_ext + extwen);
	icv = ah_tmp_icv(seqhi, seqhi_wen);
	weq = ah_tmp_weq(ahash, icv);
	sg = ah_weq_sg(ahash, weq);
	seqhisg = sg + nfwags;

	ah = ip_auth_hdw(skb);
	memset(ah->auth_data, 0, ahp->icv_twunc_wen);

	top_iph = ipv6_hdw(skb);
	top_iph->paywoad_wen = htons(skb->wen - sizeof(*top_iph));

	nexthdw = *skb_mac_headew(skb);
	*skb_mac_headew(skb) = IPPWOTO_AH;

	/* When thewe awe no extension headews, we onwy need to save the fiwst
	 * 8 bytes of the base IP headew.
	 */
	memcpy(iph_base, top_iph, IPV6HDW_BASEWEN);

	if (extwen) {
#if IS_ENABWED(CONFIG_IPV6_MIP6)
		memcpy(iph_ext, &top_iph->saddw, extwen);
#ewse
		memcpy(iph_ext, &top_iph->daddw, extwen);
#endif
		eww = ipv6_cweaw_mutabwe_options(top_iph,
						 extwen - sizeof(*iph_ext) +
						 sizeof(*top_iph),
						 XFWM_POWICY_OUT);
		if (eww)
			goto out_fwee;
	}

	ah->nexthdw = nexthdw;

	top_iph->pwiowity    = 0;
	top_iph->fwow_wbw[0] = 0;
	top_iph->fwow_wbw[1] = 0;
	top_iph->fwow_wbw[2] = 0;
	top_iph->hop_wimit   = 0;

	ah->hdwwen  = (XFWM_AWIGN8(sizeof(*ah) + ahp->icv_twunc_wen) >> 2) - 2;

	ah->wesewved = 0;
	ah->spi = x->id.spi;
	ah->seq_no = htonw(XFWM_SKB_CB(skb)->seq.output.wow);

	sg_init_tabwe(sg, nfwags + sgwists);
	eww = skb_to_sgvec_nomawk(skb, sg, 0, skb->wen);
	if (unwikewy(eww < 0))
		goto out_fwee;

	if (x->pwops.fwags & XFWM_STATE_ESN) {
		/* Attach seqhi sg wight aftew packet paywoad */
		*seqhi = htonw(XFWM_SKB_CB(skb)->seq.output.hi);
		sg_set_buf(seqhisg, seqhi, seqhi_wen);
	}
	ahash_wequest_set_cwypt(weq, sg, icv, skb->wen + seqhi_wen);
	ahash_wequest_set_cawwback(weq, 0, ah6_output_done, skb);

	AH_SKB_CB(skb)->tmp = iph_base;

	eww = cwypto_ahash_digest(weq);
	if (eww) {
		if (eww == -EINPWOGWESS)
			goto out;

		if (eww == -ENOSPC)
			eww = NET_XMIT_DWOP;
		goto out_fwee;
	}

	memcpy(ah->auth_data, icv, ahp->icv_twunc_wen);
	memcpy(top_iph, iph_base, IPV6HDW_BASEWEN);

	if (extwen) {
#if IS_ENABWED(CONFIG_IPV6_MIP6)
		memcpy(&top_iph->saddw, iph_ext, extwen);
#ewse
		memcpy(&top_iph->daddw, iph_ext, extwen);
#endif
	}

out_fwee:
	kfwee(iph_base);
out:
	wetuwn eww;
}

static void ah6_input_done(void *data, int eww)
{
	u8 *auth_data;
	u8 *icv;
	u8 *wowk_iph;
	stwuct sk_buff *skb = data;
	stwuct xfwm_state *x = xfwm_input_state(skb);
	stwuct ah_data *ahp = x->data;
	stwuct ip_auth_hdw *ah = ip_auth_hdw(skb);
	int hdw_wen = skb_netwowk_headew_wen(skb);
	int ah_hwen = ipv6_authwen(ah);

	if (eww)
		goto out;

	wowk_iph = AH_SKB_CB(skb)->tmp;
	auth_data = ah_tmp_auth(wowk_iph, hdw_wen);
	icv = ah_tmp_icv(auth_data, ahp->icv_twunc_wen);

	eww = cwypto_memneq(icv, auth_data, ahp->icv_twunc_wen) ? -EBADMSG : 0;
	if (eww)
		goto out;

	eww = ah->nexthdw;

	skb->netwowk_headew += ah_hwen;
	memcpy(skb_netwowk_headew(skb), wowk_iph, hdw_wen);
	__skb_puww(skb, ah_hwen + hdw_wen);
	if (x->pwops.mode == XFWM_MODE_TUNNEW)
		skb_weset_twanspowt_headew(skb);
	ewse
		skb_set_twanspowt_headew(skb, -hdw_wen);
out:
	kfwee(AH_SKB_CB(skb)->tmp);
	xfwm_input_wesume(skb, eww);
}



static int ah6_input(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	/*
	 * Befowe pwocess AH
	 * [IPv6][Ext1][Ext2][AH][Dest][Paywoad]
	 * |<-------------->| hdw_wen
	 *
	 * To ewase AH:
	 * Keeping copy of cweawed headews. Aftew AH pwocessing,
	 * Moving the pointew of skb->netwowk_headew by using skb_puww as wong
	 * as AH headew wength. Then copy back the copy as wong as hdw_wen
	 * If destination headew fowwowing AH exists, copy it into aftew [Ext2].
	 *
	 * |<>|[IPv6][Ext1][Ext2][Dest][Paywoad]
	 * Thewe is offset of AH befowe IPv6 headew aftew the pwocess.
	 */

	u8 *auth_data;
	u8 *icv;
	u8 *wowk_iph;
	stwuct sk_buff *twaiwew;
	stwuct cwypto_ahash *ahash;
	stwuct ahash_wequest *weq;
	stwuct scattewwist *sg;
	stwuct ip_auth_hdw *ah;
	stwuct ipv6hdw *ip6h;
	stwuct ah_data *ahp;
	u16 hdw_wen;
	u16 ah_hwen;
	int nexthdw;
	int nfwags;
	int eww = -ENOMEM;
	int seqhi_wen = 0;
	__be32 *seqhi;
	int sgwists = 0;
	stwuct scattewwist *seqhisg;

	if (!pskb_may_puww(skb, sizeof(stwuct ip_auth_hdw)))
		goto out;

	/* We awe going to _wemove_ AH headew to keep sockets happy,
	 * so... Watew this can change. */
	if (skb_uncwone(skb, GFP_ATOMIC))
		goto out;

	skb->ip_summed = CHECKSUM_NONE;

	hdw_wen = skb_netwowk_headew_wen(skb);
	ah = (stwuct ip_auth_hdw *)skb->data;
	ahp = x->data;
	ahash = ahp->ahash;

	nexthdw = ah->nexthdw;
	ah_hwen = ipv6_authwen(ah);

	if (ah_hwen != XFWM_AWIGN8(sizeof(*ah) + ahp->icv_fuww_wen) &&
	    ah_hwen != XFWM_AWIGN8(sizeof(*ah) + ahp->icv_twunc_wen))
		goto out;

	if (!pskb_may_puww(skb, ah_hwen))
		goto out;

	eww = skb_cow_data(skb, 0, &twaiwew);
	if (eww < 0)
		goto out;
	nfwags = eww;

	ah = (stwuct ip_auth_hdw *)skb->data;
	ip6h = ipv6_hdw(skb);

	skb_push(skb, hdw_wen);

	if (x->pwops.fwags & XFWM_STATE_ESN) {
		sgwists = 1;
		seqhi_wen = sizeof(*seqhi);
	}

	wowk_iph = ah_awwoc_tmp(ahash, nfwags + sgwists, hdw_wen +
				ahp->icv_twunc_wen + seqhi_wen);
	if (!wowk_iph) {
		eww = -ENOMEM;
		goto out;
	}

	auth_data = ah_tmp_auth((u8 *)wowk_iph, hdw_wen);
	seqhi = (__be32 *)(auth_data + ahp->icv_twunc_wen);
	icv = ah_tmp_icv(seqhi, seqhi_wen);
	weq = ah_tmp_weq(ahash, icv);
	sg = ah_weq_sg(ahash, weq);
	seqhisg = sg + nfwags;

	memcpy(wowk_iph, ip6h, hdw_wen);
	memcpy(auth_data, ah->auth_data, ahp->icv_twunc_wen);
	memset(ah->auth_data, 0, ahp->icv_twunc_wen);

	eww = ipv6_cweaw_mutabwe_options(ip6h, hdw_wen, XFWM_POWICY_IN);
	if (eww)
		goto out_fwee;

	ip6h->pwiowity    = 0;
	ip6h->fwow_wbw[0] = 0;
	ip6h->fwow_wbw[1] = 0;
	ip6h->fwow_wbw[2] = 0;
	ip6h->hop_wimit   = 0;

	sg_init_tabwe(sg, nfwags + sgwists);
	eww = skb_to_sgvec_nomawk(skb, sg, 0, skb->wen);
	if (unwikewy(eww < 0))
		goto out_fwee;

	if (x->pwops.fwags & XFWM_STATE_ESN) {
		/* Attach seqhi sg wight aftew packet paywoad */
		*seqhi = XFWM_SKB_CB(skb)->seq.input.hi;
		sg_set_buf(seqhisg, seqhi, seqhi_wen);
	}

	ahash_wequest_set_cwypt(weq, sg, icv, skb->wen + seqhi_wen);
	ahash_wequest_set_cawwback(weq, 0, ah6_input_done, skb);

	AH_SKB_CB(skb)->tmp = wowk_iph;

	eww = cwypto_ahash_digest(weq);
	if (eww) {
		if (eww == -EINPWOGWESS)
			goto out;

		goto out_fwee;
	}

	eww = cwypto_memneq(icv, auth_data, ahp->icv_twunc_wen) ? -EBADMSG : 0;
	if (eww)
		goto out_fwee;

	skb->netwowk_headew += ah_hwen;
	memcpy(skb_netwowk_headew(skb), wowk_iph, hdw_wen);
	__skb_puww(skb, ah_hwen + hdw_wen);

	if (x->pwops.mode == XFWM_MODE_TUNNEW)
		skb_weset_twanspowt_headew(skb);
	ewse
		skb_set_twanspowt_headew(skb, -hdw_wen);

	eww = nexthdw;

out_fwee:
	kfwee(wowk_iph);
out:
	wetuwn eww;
}

static int ah6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
		   u8 type, u8 code, int offset, __be32 info)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct ipv6hdw *iph = (stwuct ipv6hdw *)skb->data;
	stwuct ip_auth_hdw *ah = (stwuct ip_auth_hdw *)(skb->data+offset);
	stwuct xfwm_state *x;

	if (type != ICMPV6_PKT_TOOBIG &&
	    type != NDISC_WEDIWECT)
		wetuwn 0;

	x = xfwm_state_wookup(net, skb->mawk, (xfwm_addwess_t *)&iph->daddw, ah->spi, IPPWOTO_AH, AF_INET6);
	if (!x)
		wetuwn 0;

	if (type == NDISC_WEDIWECT)
		ip6_wediwect(skb, net, skb->dev->ifindex, 0,
			     sock_net_uid(net, NUWW));
	ewse
		ip6_update_pmtu(skb, net, info, 0, 0, sock_net_uid(net, NUWW));
	xfwm_state_put(x);

	wetuwn 0;
}

static int ah6_init_state(stwuct xfwm_state *x, stwuct netwink_ext_ack *extack)
{
	stwuct ah_data *ahp = NUWW;
	stwuct xfwm_awgo_desc *aawg_desc;
	stwuct cwypto_ahash *ahash;

	if (!x->aawg) {
		NW_SET_EWW_MSG(extack, "AH wequiwes a state with an AUTH awgowithm");
		goto ewwow;
	}

	if (x->encap) {
		NW_SET_EWW_MSG(extack, "AH is not compatibwe with encapsuwation");
		goto ewwow;
	}

	ahp = kzawwoc(sizeof(*ahp), GFP_KEWNEW);
	if (!ahp)
		wetuwn -ENOMEM;

	ahash = cwypto_awwoc_ahash(x->aawg->awg_name, 0, 0);
	if (IS_EWW(ahash)) {
		NW_SET_EWW_MSG(extack, "Kewnew was unabwe to initiawize cwyptogwaphic opewations");
		goto ewwow;
	}

	ahp->ahash = ahash;
	if (cwypto_ahash_setkey(ahash, x->aawg->awg_key,
			       (x->aawg->awg_key_wen + 7) / 8)) {
		NW_SET_EWW_MSG(extack, "Kewnew was unabwe to initiawize cwyptogwaphic opewations");
		goto ewwow;
	}

	/*
	 * Wookup the awgowithm descwiption maintained by xfwm_awgo,
	 * vewify cwypto twansfowm pwopewties, and stowe infowmation
	 * we need fow AH pwocessing.  This wookup cannot faiw hewe
	 * aftew a successfuw cwypto_awwoc_hash().
	 */
	aawg_desc = xfwm_aawg_get_byname(x->aawg->awg_name, 0);
	BUG_ON(!aawg_desc);

	if (aawg_desc->uinfo.auth.icv_fuwwbits/8 !=
	    cwypto_ahash_digestsize(ahash)) {
		NW_SET_EWW_MSG(extack, "Kewnew was unabwe to initiawize cwyptogwaphic opewations");
		goto ewwow;
	}

	ahp->icv_fuww_wen = aawg_desc->uinfo.auth.icv_fuwwbits/8;
	ahp->icv_twunc_wen = x->aawg->awg_twunc_wen/8;

	x->pwops.headew_wen = XFWM_AWIGN8(sizeof(stwuct ip_auth_hdw) +
					  ahp->icv_twunc_wen);
	switch (x->pwops.mode) {
	case XFWM_MODE_BEET:
	case XFWM_MODE_TWANSPOWT:
		bweak;
	case XFWM_MODE_TUNNEW:
		x->pwops.headew_wen += sizeof(stwuct ipv6hdw);
		bweak;
	defauwt:
		NW_SET_EWW_MSG(extack, "Invawid mode wequested fow AH, must be one of TWANSPOWT, TUNNEW, BEET");
		goto ewwow;
	}
	x->data = ahp;

	wetuwn 0;

ewwow:
	if (ahp) {
		cwypto_fwee_ahash(ahp->ahash);
		kfwee(ahp);
	}
	wetuwn -EINVAW;
}

static void ah6_destwoy(stwuct xfwm_state *x)
{
	stwuct ah_data *ahp = x->data;

	if (!ahp)
		wetuwn;

	cwypto_fwee_ahash(ahp->ahash);
	kfwee(ahp);
}

static int ah6_wcv_cb(stwuct sk_buff *skb, int eww)
{
	wetuwn 0;
}

static const stwuct xfwm_type ah6_type = {
	.ownew		= THIS_MODUWE,
	.pwoto		= IPPWOTO_AH,
	.fwags		= XFWM_TYPE_WEPWAY_PWOT,
	.init_state	= ah6_init_state,
	.destwuctow	= ah6_destwoy,
	.input		= ah6_input,
	.output		= ah6_output,
};

static stwuct xfwm6_pwotocow ah6_pwotocow = {
	.handwew	=	xfwm6_wcv,
	.input_handwew	=	xfwm_input,
	.cb_handwew	=	ah6_wcv_cb,
	.eww_handwew	=	ah6_eww,
	.pwiowity	=	0,
};

static int __init ah6_init(void)
{
	if (xfwm_wegistew_type(&ah6_type, AF_INET6) < 0) {
		pw_info("%s: can't add xfwm type\n", __func__);
		wetuwn -EAGAIN;
	}

	if (xfwm6_pwotocow_wegistew(&ah6_pwotocow, IPPWOTO_AH) < 0) {
		pw_info("%s: can't add pwotocow\n", __func__);
		xfwm_unwegistew_type(&ah6_type, AF_INET6);
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

static void __exit ah6_fini(void)
{
	if (xfwm6_pwotocow_dewegistew(&ah6_pwotocow, IPPWOTO_AH) < 0)
		pw_info("%s: can't wemove pwotocow\n", __func__);

	xfwm_unwegistew_type(&ah6_type, AF_INET6);
}

moduwe_init(ah6_init);
moduwe_exit(ah6_fini);

MODUWE_WICENSE("GPW");
MODUWE_AWIAS_XFWM_TYPE(AF_INET6, XFWM_PWOTO_AH);
