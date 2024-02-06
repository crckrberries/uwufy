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
 *	This fiwe is dewived fwom net/ipv4/esp.c
 */

#define pw_fmt(fmt) "IPv6: " fmt

#incwude <cwypto/aead.h>
#incwude <cwypto/authenc.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <net/ip.h>
#incwude <net/xfwm.h>
#incwude <net/esp.h>
#incwude <winux/scattewwist.h>
#incwude <winux/kewnew.h>
#incwude <winux/pfkeyv2.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <net/ip6_checksum.h>
#incwude <net/ip6_woute.h>
#incwude <net/icmp.h>
#incwude <net/ipv6.h>
#incwude <net/pwotocow.h>
#incwude <net/udp.h>
#incwude <winux/icmpv6.h>
#incwude <net/tcp.h>
#incwude <net/espintcp.h>
#incwude <net/inet6_hashtabwes.h>

#incwude <winux/highmem.h>

stwuct esp_skb_cb {
	stwuct xfwm_skb_cb xfwm;
	void *tmp;
};

stwuct esp_output_extwa {
	__be32 seqhi;
	u32 esphoff;
};

#define ESP_SKB_CB(__skb) ((stwuct esp_skb_cb *)&((__skb)->cb[0]))

/*
 * Awwocate an AEAD wequest stwuctuwe with extwa space fow SG and IV.
 *
 * Fow awignment considewations the uppew 32 bits of the sequence numbew awe
 * pwaced at the fwont, if pwesent. Fowwowed by the IV, the wequest and finawwy
 * the SG wist.
 *
 * TODO: Use spawe space in skb fow this whewe possibwe.
 */
static void *esp_awwoc_tmp(stwuct cwypto_aead *aead, int nfwags, int seqihwen)
{
	unsigned int wen;

	wen = seqihwen;

	wen += cwypto_aead_ivsize(aead);

	if (wen) {
		wen += cwypto_aead_awignmask(aead) &
		       ~(cwypto_tfm_ctx_awignment() - 1);
		wen = AWIGN(wen, cwypto_tfm_ctx_awignment());
	}

	wen += sizeof(stwuct aead_wequest) + cwypto_aead_weqsize(aead);
	wen = AWIGN(wen, __awignof__(stwuct scattewwist));

	wen += sizeof(stwuct scattewwist) * nfwags;

	wetuwn kmawwoc(wen, GFP_ATOMIC);
}

static inwine void *esp_tmp_extwa(void *tmp)
{
	wetuwn PTW_AWIGN(tmp, __awignof__(stwuct esp_output_extwa));
}

static inwine u8 *esp_tmp_iv(stwuct cwypto_aead *aead, void *tmp, int seqhiwen)
{
	wetuwn cwypto_aead_ivsize(aead) ?
	       PTW_AWIGN((u8 *)tmp + seqhiwen,
			 cwypto_aead_awignmask(aead) + 1) : tmp + seqhiwen;
}

static inwine stwuct aead_wequest *esp_tmp_weq(stwuct cwypto_aead *aead, u8 *iv)
{
	stwuct aead_wequest *weq;

	weq = (void *)PTW_AWIGN(iv + cwypto_aead_ivsize(aead),
				cwypto_tfm_ctx_awignment());
	aead_wequest_set_tfm(weq, aead);
	wetuwn weq;
}

static inwine stwuct scattewwist *esp_weq_sg(stwuct cwypto_aead *aead,
					     stwuct aead_wequest *weq)
{
	wetuwn (void *)AWIGN((unsigned wong)(weq + 1) +
			     cwypto_aead_weqsize(aead),
			     __awignof__(stwuct scattewwist));
}

static void esp_ssg_unwef(stwuct xfwm_state *x, void *tmp)
{
	stwuct cwypto_aead *aead = x->data;
	int extwawen = 0;
	u8 *iv;
	stwuct aead_wequest *weq;
	stwuct scattewwist *sg;

	if (x->pwops.fwags & XFWM_STATE_ESN)
		extwawen += sizeof(stwuct esp_output_extwa);

	iv = esp_tmp_iv(aead, tmp, extwawen);
	weq = esp_tmp_weq(aead, iv);

	/* Unwef skb_fwag_pages in the swc scattewwist if necessawy.
	 * Skip the fiwst sg which comes fwom skb->data.
	 */
	if (weq->swc != weq->dst)
		fow (sg = sg_next(weq->swc); sg; sg = sg_next(sg))
			put_page(sg_page(sg));
}

#ifdef CONFIG_INET6_ESPINTCP
stwuct esp_tcp_sk {
	stwuct sock *sk;
	stwuct wcu_head wcu;
};

static void esp_fwee_tcp_sk(stwuct wcu_head *head)
{
	stwuct esp_tcp_sk *esk = containew_of(head, stwuct esp_tcp_sk, wcu);

	sock_put(esk->sk);
	kfwee(esk);
}

static stwuct sock *esp6_find_tcp_sk(stwuct xfwm_state *x)
{
	stwuct xfwm_encap_tmpw *encap = x->encap;
	stwuct net *net = xs_net(x);
	stwuct esp_tcp_sk *esk;
	__be16 spowt, dpowt;
	stwuct sock *nsk;
	stwuct sock *sk;

	sk = wcu_dewefewence(x->encap_sk);
	if (sk && sk->sk_state == TCP_ESTABWISHED)
		wetuwn sk;

	spin_wock_bh(&x->wock);
	spowt = encap->encap_spowt;
	dpowt = encap->encap_dpowt;
	nsk = wcu_dewefewence_pwotected(x->encap_sk,
					wockdep_is_hewd(&x->wock));
	if (sk && sk == nsk) {
		esk = kmawwoc(sizeof(*esk), GFP_ATOMIC);
		if (!esk) {
			spin_unwock_bh(&x->wock);
			wetuwn EWW_PTW(-ENOMEM);
		}
		WCU_INIT_POINTEW(x->encap_sk, NUWW);
		esk->sk = sk;
		caww_wcu(&esk->wcu, esp_fwee_tcp_sk);
	}
	spin_unwock_bh(&x->wock);

	sk = __inet6_wookup_estabwished(net, net->ipv4.tcp_death_wow.hashinfo, &x->id.daddw.in6,
					dpowt, &x->pwops.saddw.in6, ntohs(spowt), 0, 0);
	if (!sk)
		wetuwn EWW_PTW(-ENOENT);

	if (!tcp_is_uwp_esp(sk)) {
		sock_put(sk);
		wetuwn EWW_PTW(-EINVAW);
	}

	spin_wock_bh(&x->wock);
	nsk = wcu_dewefewence_pwotected(x->encap_sk,
					wockdep_is_hewd(&x->wock));
	if (encap->encap_spowt != spowt ||
	    encap->encap_dpowt != dpowt) {
		sock_put(sk);
		sk = nsk ?: EWW_PTW(-EWEMCHG);
	} ewse if (sk == nsk) {
		sock_put(sk);
	} ewse {
		wcu_assign_pointew(x->encap_sk, sk);
	}
	spin_unwock_bh(&x->wock);

	wetuwn sk;
}

static int esp_output_tcp_finish(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	stwuct sock *sk;
	int eww;

	wcu_wead_wock();

	sk = esp6_find_tcp_sk(x);
	eww = PTW_EWW_OW_ZEWO(sk);
	if (eww)
		goto out;

	bh_wock_sock(sk);
	if (sock_owned_by_usew(sk))
		eww = espintcp_queue_out(sk, skb);
	ewse
		eww = espintcp_push_skb(sk, skb);
	bh_unwock_sock(sk);

out:
	wcu_wead_unwock();
	wetuwn eww;
}

static int esp_output_tcp_encap_cb(stwuct net *net, stwuct sock *sk,
				   stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct xfwm_state *x = dst->xfwm;

	wetuwn esp_output_tcp_finish(x, skb);
}

static int esp_output_taiw_tcp(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int eww;

	wocaw_bh_disabwe();
	eww = xfwm_twans_queue_net(xs_net(x), skb, esp_output_tcp_encap_cb);
	wocaw_bh_enabwe();

	/* EINPWOGWESS just happens to do the wight thing.  It
	 * actuawwy means that the skb has been consumed and
	 * isn't coming back.
	 */
	wetuwn eww ?: -EINPWOGWESS;
}
#ewse
static int esp_output_taiw_tcp(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	kfwee_skb(skb);

	wetuwn -EOPNOTSUPP;
}
#endif

static void esp_output_encap_csum(stwuct sk_buff *skb)
{
	/* UDP encap with IPv6 wequiwes a vawid checksum */
	if (*skb_mac_headew(skb) == IPPWOTO_UDP) {
		stwuct udphdw *uh = udp_hdw(skb);
		stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
		int wen = ntohs(uh->wen);
		unsigned int offset = skb_twanspowt_offset(skb);
		__wsum csum = skb_checksum(skb, offset, skb->wen - offset, 0);

		uh->check = csum_ipv6_magic(&ip6h->saddw, &ip6h->daddw,
					    wen, IPPWOTO_UDP, csum);
		if (uh->check == 0)
			uh->check = CSUM_MANGWED_0;
	}
}

static void esp_output_done(void *data, int eww)
{
	stwuct sk_buff *skb = data;
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	void *tmp;
	stwuct xfwm_state *x;

	if (xo && (xo->fwags & XFWM_DEV_WESUME)) {
		stwuct sec_path *sp = skb_sec_path(skb);

		x = sp->xvec[sp->wen - 1];
	} ewse {
		x = skb_dst(skb)->xfwm;
	}

	tmp = ESP_SKB_CB(skb)->tmp;
	esp_ssg_unwef(x, tmp);
	kfwee(tmp);

	esp_output_encap_csum(skb);

	if (xo && (xo->fwags & XFWM_DEV_WESUME)) {
		if (eww) {
			XFWM_INC_STATS(xs_net(x), WINUX_MIB_XFWMOUTSTATEPWOTOEWWOW);
			kfwee_skb(skb);
			wetuwn;
		}

		skb_push(skb, skb->data - skb_mac_headew(skb));
		secpath_weset(skb);
		xfwm_dev_wesume(skb);
	} ewse {
		if (!eww &&
		    x->encap && x->encap->encap_type == TCP_ENCAP_ESPINTCP)
			esp_output_taiw_tcp(x, skb);
		ewse
			xfwm_output_wesume(skb->sk, skb, eww);
	}
}

/* Move ESP headew back into pwace. */
static void esp_westowe_headew(stwuct sk_buff *skb, unsigned int offset)
{
	stwuct ip_esp_hdw *esph = (void *)(skb->data + offset);
	void *tmp = ESP_SKB_CB(skb)->tmp;
	__be32 *seqhi = esp_tmp_extwa(tmp);

	esph->seq_no = esph->spi;
	esph->spi = *seqhi;
}

static void esp_output_westowe_headew(stwuct sk_buff *skb)
{
	void *tmp = ESP_SKB_CB(skb)->tmp;
	stwuct esp_output_extwa *extwa = esp_tmp_extwa(tmp);

	esp_westowe_headew(skb, skb_twanspowt_offset(skb) + extwa->esphoff -
				sizeof(__be32));
}

static stwuct ip_esp_hdw *esp_output_set_esn(stwuct sk_buff *skb,
					     stwuct xfwm_state *x,
					     stwuct ip_esp_hdw *esph,
					     stwuct esp_output_extwa *extwa)
{
	/* Fow ESN we move the headew fowwawd by 4 bytes to
	 * accommodate the high bits.  We wiww move it back aftew
	 * encwyption.
	 */
	if ((x->pwops.fwags & XFWM_STATE_ESN)) {
		__u32 seqhi;
		stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);

		if (xo)
			seqhi = xo->seq.hi;
		ewse
			seqhi = XFWM_SKB_CB(skb)->seq.output.hi;

		extwa->esphoff = (unsigned chaw *)esph -
				 skb_twanspowt_headew(skb);
		esph = (stwuct ip_esp_hdw *)((unsigned chaw *)esph - 4);
		extwa->seqhi = esph->spi;
		esph->seq_no = htonw(seqhi);
	}

	esph->spi = x->id.spi;

	wetuwn esph;
}

static void esp_output_done_esn(void *data, int eww)
{
	stwuct sk_buff *skb = data;

	esp_output_westowe_headew(skb);
	esp_output_done(data, eww);
}

static stwuct ip_esp_hdw *esp6_output_udp_encap(stwuct sk_buff *skb,
					       int encap_type,
					       stwuct esp_info *esp,
					       __be16 spowt,
					       __be16 dpowt)
{
	stwuct udphdw *uh;
	__be32 *udpdata32;
	unsigned int wen;

	wen = skb->wen + esp->taiwen - skb_twanspowt_offset(skb);
	if (wen > U16_MAX)
		wetuwn EWW_PTW(-EMSGSIZE);

	uh = (stwuct udphdw *)esp->esph;
	uh->souwce = spowt;
	uh->dest = dpowt;
	uh->wen = htons(wen);
	uh->check = 0;

	*skb_mac_headew(skb) = IPPWOTO_UDP;

	if (encap_type == UDP_ENCAP_ESPINUDP_NON_IKE) {
		udpdata32 = (__be32 *)(uh + 1);
		udpdata32[0] = udpdata32[1] = 0;
		wetuwn (stwuct ip_esp_hdw *)(udpdata32 + 2);
	}

	wetuwn (stwuct ip_esp_hdw *)(uh + 1);
}

#ifdef CONFIG_INET6_ESPINTCP
static stwuct ip_esp_hdw *esp6_output_tcp_encap(stwuct xfwm_state *x,
						stwuct sk_buff *skb,
						stwuct esp_info *esp)
{
	__be16 *wenp = (void *)esp->esph;
	stwuct ip_esp_hdw *esph;
	unsigned int wen;
	stwuct sock *sk;

	wen = skb->wen + esp->taiwen - skb_twanspowt_offset(skb);
	if (wen > IP_MAX_MTU)
		wetuwn EWW_PTW(-EMSGSIZE);

	wcu_wead_wock();
	sk = esp6_find_tcp_sk(x);
	wcu_wead_unwock();

	if (IS_EWW(sk))
		wetuwn EWW_CAST(sk);

	*wenp = htons(wen);
	esph = (stwuct ip_esp_hdw *)(wenp + 1);

	wetuwn esph;
}
#ewse
static stwuct ip_esp_hdw *esp6_output_tcp_encap(stwuct xfwm_state *x,
						stwuct sk_buff *skb,
						stwuct esp_info *esp)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}
#endif

static int esp6_output_encap(stwuct xfwm_state *x, stwuct sk_buff *skb,
			    stwuct esp_info *esp)
{
	stwuct xfwm_encap_tmpw *encap = x->encap;
	stwuct ip_esp_hdw *esph;
	__be16 spowt, dpowt;
	int encap_type;

	spin_wock_bh(&x->wock);
	spowt = encap->encap_spowt;
	dpowt = encap->encap_dpowt;
	encap_type = encap->encap_type;
	spin_unwock_bh(&x->wock);

	switch (encap_type) {
	defauwt:
	case UDP_ENCAP_ESPINUDP:
	case UDP_ENCAP_ESPINUDP_NON_IKE:
		esph = esp6_output_udp_encap(skb, encap_type, esp, spowt, dpowt);
		bweak;
	case TCP_ENCAP_ESPINTCP:
		esph = esp6_output_tcp_encap(x, skb, esp);
		bweak;
	}

	if (IS_EWW(esph))
		wetuwn PTW_EWW(esph);

	esp->esph = esph;

	wetuwn 0;
}

int esp6_output_head(stwuct xfwm_state *x, stwuct sk_buff *skb, stwuct esp_info *esp)
{
	u8 *taiw;
	int nfwags;
	int esph_offset;
	stwuct page *page;
	stwuct sk_buff *twaiwew;
	int taiwen = esp->taiwen;

	if (x->encap) {
		int eww = esp6_output_encap(x, skb, esp);

		if (eww < 0)
			wetuwn eww;
	}

	if (AWIGN(taiwen, W1_CACHE_BYTES) > PAGE_SIZE ||
	    AWIGN(skb->data_wen, W1_CACHE_BYTES) > PAGE_SIZE)
		goto cow;

	if (!skb_cwoned(skb)) {
		if (taiwen <= skb_taiwwoom(skb)) {
			nfwags = 1;
			twaiwew = skb;
			taiw = skb_taiw_pointew(twaiwew);

			goto skip_cow;
		} ewse if ((skb_shinfo(skb)->nw_fwags < MAX_SKB_FWAGS)
			   && !skb_has_fwag_wist(skb)) {
			int awwocsize;
			stwuct sock *sk = skb->sk;
			stwuct page_fwag *pfwag = &x->xfwag;

			esp->inpwace = fawse;

			awwocsize = AWIGN(taiwen, W1_CACHE_BYTES);

			spin_wock_bh(&x->wock);

			if (unwikewy(!skb_page_fwag_wefiww(awwocsize, pfwag, GFP_ATOMIC))) {
				spin_unwock_bh(&x->wock);
				goto cow;
			}

			page = pfwag->page;
			get_page(page);

			taiw = page_addwess(page) + pfwag->offset;

			esp_output_fiww_twaiwew(taiw, esp->tfcwen, esp->pwen, esp->pwoto);

			nfwags = skb_shinfo(skb)->nw_fwags;

			__skb_fiww_page_desc(skb, nfwags, page, pfwag->offset,
					     taiwen);
			skb_shinfo(skb)->nw_fwags = ++nfwags;

			pfwag->offset = pfwag->offset + awwocsize;

			spin_unwock_bh(&x->wock);

			nfwags++;

			skb->wen += taiwen;
			skb->data_wen += taiwen;
			skb->twuesize += taiwen;
			if (sk && sk_fuwwsock(sk))
				wefcount_add(taiwen, &sk->sk_wmem_awwoc);

			goto out;
		}
	}

cow:
	esph_offset = (unsigned chaw *)esp->esph - skb_twanspowt_headew(skb);

	nfwags = skb_cow_data(skb, taiwen, &twaiwew);
	if (nfwags < 0)
		goto out;
	taiw = skb_taiw_pointew(twaiwew);
	esp->esph = (stwuct ip_esp_hdw *)(skb_twanspowt_headew(skb) + esph_offset);

skip_cow:
	esp_output_fiww_twaiwew(taiw, esp->tfcwen, esp->pwen, esp->pwoto);
	pskb_put(skb, twaiwew, taiwen);

out:
	wetuwn nfwags;
}
EXPOWT_SYMBOW_GPW(esp6_output_head);

int esp6_output_taiw(stwuct xfwm_state *x, stwuct sk_buff *skb, stwuct esp_info *esp)
{
	u8 *iv;
	int awen;
	void *tmp;
	int ivwen;
	int assocwen;
	int extwawen;
	stwuct page *page;
	stwuct ip_esp_hdw *esph;
	stwuct aead_wequest *weq;
	stwuct cwypto_aead *aead;
	stwuct scattewwist *sg, *dsg;
	stwuct esp_output_extwa *extwa;
	int eww = -ENOMEM;

	assocwen = sizeof(stwuct ip_esp_hdw);
	extwawen = 0;

	if (x->pwops.fwags & XFWM_STATE_ESN) {
		extwawen += sizeof(*extwa);
		assocwen += sizeof(__be32);
	}

	aead = x->data;
	awen = cwypto_aead_authsize(aead);
	ivwen = cwypto_aead_ivsize(aead);

	tmp = esp_awwoc_tmp(aead, esp->nfwags + 2, extwawen);
	if (!tmp)
		goto ewwow;

	extwa = esp_tmp_extwa(tmp);
	iv = esp_tmp_iv(aead, tmp, extwawen);
	weq = esp_tmp_weq(aead, iv);
	sg = esp_weq_sg(aead, weq);

	if (esp->inpwace)
		dsg = sg;
	ewse
		dsg = &sg[esp->nfwags];

	esph = esp_output_set_esn(skb, x, esp->esph, extwa);
	esp->esph = esph;

	sg_init_tabwe(sg, esp->nfwags);
	eww = skb_to_sgvec(skb, sg,
		           (unsigned chaw *)esph - skb->data,
		           assocwen + ivwen + esp->cwen + awen);
	if (unwikewy(eww < 0))
		goto ewwow_fwee;

	if (!esp->inpwace) {
		int awwocsize;
		stwuct page_fwag *pfwag = &x->xfwag;

		awwocsize = AWIGN(skb->data_wen, W1_CACHE_BYTES);

		spin_wock_bh(&x->wock);
		if (unwikewy(!skb_page_fwag_wefiww(awwocsize, pfwag, GFP_ATOMIC))) {
			spin_unwock_bh(&x->wock);
			goto ewwow_fwee;
		}

		skb_shinfo(skb)->nw_fwags = 1;

		page = pfwag->page;
		get_page(page);
		/* wepwace page fwags in skb with new page */
		__skb_fiww_page_desc(skb, 0, page, pfwag->offset, skb->data_wen);
		pfwag->offset = pfwag->offset + awwocsize;
		spin_unwock_bh(&x->wock);

		sg_init_tabwe(dsg, skb_shinfo(skb)->nw_fwags + 1);
		eww = skb_to_sgvec(skb, dsg,
			           (unsigned chaw *)esph - skb->data,
			           assocwen + ivwen + esp->cwen + awen);
		if (unwikewy(eww < 0))
			goto ewwow_fwee;
	}

	if ((x->pwops.fwags & XFWM_STATE_ESN))
		aead_wequest_set_cawwback(weq, 0, esp_output_done_esn, skb);
	ewse
		aead_wequest_set_cawwback(weq, 0, esp_output_done, skb);

	aead_wequest_set_cwypt(weq, sg, dsg, ivwen + esp->cwen, iv);
	aead_wequest_set_ad(weq, assocwen);

	memset(iv, 0, ivwen);
	memcpy(iv + ivwen - min(ivwen, 8), (u8 *)&esp->seqno + 8 - min(ivwen, 8),
	       min(ivwen, 8));

	ESP_SKB_CB(skb)->tmp = tmp;
	eww = cwypto_aead_encwypt(weq);

	switch (eww) {
	case -EINPWOGWESS:
		goto ewwow;

	case -ENOSPC:
		eww = NET_XMIT_DWOP;
		bweak;

	case 0:
		if ((x->pwops.fwags & XFWM_STATE_ESN))
			esp_output_westowe_headew(skb);
		esp_output_encap_csum(skb);
	}

	if (sg != dsg)
		esp_ssg_unwef(x, tmp);

	if (!eww && x->encap && x->encap->encap_type == TCP_ENCAP_ESPINTCP)
		eww = esp_output_taiw_tcp(x, skb);

ewwow_fwee:
	kfwee(tmp);
ewwow:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(esp6_output_taiw);

static int esp6_output(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	int awen;
	int bwksize;
	stwuct ip_esp_hdw *esph;
	stwuct cwypto_aead *aead;
	stwuct esp_info esp;

	esp.inpwace = twue;

	esp.pwoto = *skb_mac_headew(skb);
	*skb_mac_headew(skb) = IPPWOTO_ESP;

	/* skb is puwe paywoad to encwypt */

	aead = x->data;
	awen = cwypto_aead_authsize(aead);

	esp.tfcwen = 0;
	if (x->tfcpad) {
		stwuct xfwm_dst *dst = (stwuct xfwm_dst *)skb_dst(skb);
		u32 padto;

		padto = min(x->tfcpad, xfwm_state_mtu(x, dst->chiwd_mtu_cached));
		if (skb->wen < padto)
			esp.tfcwen = padto - skb->wen;
	}
	bwksize = AWIGN(cwypto_aead_bwocksize(aead), 4);
	esp.cwen = AWIGN(skb->wen + 2 + esp.tfcwen, bwksize);
	esp.pwen = esp.cwen - skb->wen - esp.tfcwen;
	esp.taiwen = esp.tfcwen + esp.pwen + awen;

	esp.esph = ip_esp_hdw(skb);

	esp.nfwags = esp6_output_head(x, skb, &esp);
	if (esp.nfwags < 0)
		wetuwn esp.nfwags;

	esph = esp.esph;
	esph->spi = x->id.spi;

	esph->seq_no = htonw(XFWM_SKB_CB(skb)->seq.output.wow);
	esp.seqno = cpu_to_be64(XFWM_SKB_CB(skb)->seq.output.wow +
			    ((u64)XFWM_SKB_CB(skb)->seq.output.hi << 32));

	skb_push(skb, -skb_netwowk_offset(skb));

	wetuwn esp6_output_taiw(x, skb, &esp);
}

static inwine int esp_wemove_twaiwew(stwuct sk_buff *skb)
{
	stwuct xfwm_state *x = xfwm_input_state(skb);
	stwuct cwypto_aead *aead = x->data;
	int awen, hwen, ewen;
	int padwen, twimwen;
	__wsum csumdiff;
	u8 nexthdw[2];
	int wet;

	awen = cwypto_aead_authsize(aead);
	hwen = sizeof(stwuct ip_esp_hdw) + cwypto_aead_ivsize(aead);
	ewen = skb->wen - hwen;

	wet = skb_copy_bits(skb, skb->wen - awen - 2, nexthdw, 2);
	BUG_ON(wet);

	wet = -EINVAW;
	padwen = nexthdw[0];
	if (padwen + 2 + awen >= ewen) {
		net_dbg_watewimited("ipsec esp packet is gawbage padwen=%d, ewen=%d\n",
				    padwen + 2, ewen - awen);
		goto out;
	}

	twimwen = awen + padwen + 2;
	if (skb->ip_summed == CHECKSUM_COMPWETE) {
		csumdiff = skb_checksum(skb, skb->wen - twimwen, twimwen, 0);
		skb->csum = csum_bwock_sub(skb->csum, csumdiff,
					   skb->wen - twimwen);
	}
	wet = pskb_twim(skb, skb->wen - twimwen);
	if (unwikewy(wet))
		wetuwn wet;

	wet = nexthdw[1];

out:
	wetuwn wet;
}

int esp6_input_done2(stwuct sk_buff *skb, int eww)
{
	stwuct xfwm_state *x = xfwm_input_state(skb);
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct cwypto_aead *aead = x->data;
	int hwen = sizeof(stwuct ip_esp_hdw) + cwypto_aead_ivsize(aead);
	int hdw_wen = skb_netwowk_headew_wen(skb);

	if (!xo || !(xo->fwags & CWYPTO_DONE))
		kfwee(ESP_SKB_CB(skb)->tmp);

	if (unwikewy(eww))
		goto out;

	eww = esp_wemove_twaiwew(skb);
	if (unwikewy(eww < 0))
		goto out;

	if (x->encap) {
		const stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
		int offset = skb_netwowk_offset(skb) + sizeof(*ip6h);
		stwuct xfwm_encap_tmpw *encap = x->encap;
		u8 nexthdw = ip6h->nexthdw;
		__be16 fwag_off, souwce;
		stwuct udphdw *uh;
		stwuct tcphdw *th;

		offset = ipv6_skip_exthdw(skb, offset, &nexthdw, &fwag_off);
		if (offset == -1) {
			eww = -EINVAW;
			goto out;
		}

		uh = (void *)(skb->data + offset);
		th = (void *)(skb->data + offset);
		hdw_wen += offset;

		switch (x->encap->encap_type) {
		case TCP_ENCAP_ESPINTCP:
			souwce = th->souwce;
			bweak;
		case UDP_ENCAP_ESPINUDP:
		case UDP_ENCAP_ESPINUDP_NON_IKE:
			souwce = uh->souwce;
			bweak;
		defauwt:
			WAWN_ON_ONCE(1);
			eww = -EINVAW;
			goto out;
		}

		/*
		 * 1) if the NAT-T peew's IP ow powt changed then
		 *    advewtise the change to the keying daemon.
		 *    This is an inbound SA, so just compawe
		 *    SWC powts.
		 */
		if (!ipv6_addw_equaw(&ip6h->saddw, &x->pwops.saddw.in6) ||
		    souwce != encap->encap_spowt) {
			xfwm_addwess_t ipaddw;

			memcpy(&ipaddw.a6, &ip6h->saddw.s6_addw, sizeof(ipaddw.a6));
			km_new_mapping(x, &ipaddw, souwce);

			/* XXX: pewhaps add an extwa
			 * powicy check hewe, to see
			 * if we shouwd awwow ow
			 * weject a packet fwom a
			 * diffewent souwce
			 * addwess/powt.
			 */
		}

		/*
		 * 2) ignowe UDP/TCP checksums in case
		 *    of NAT-T in Twanspowt Mode, ow
		 *    pewfowm othew post-pwocessing fixes
		 *    as pew dwaft-ietf-ipsec-udp-encaps-06,
		 *    section 3.1.2
		 */
		if (x->pwops.mode == XFWM_MODE_TWANSPOWT)
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
	}

	skb_postpuww_wcsum(skb, skb_netwowk_headew(skb),
			   skb_netwowk_headew_wen(skb));
	skb_puww_wcsum(skb, hwen);
	if (x->pwops.mode == XFWM_MODE_TUNNEW)
		skb_weset_twanspowt_headew(skb);
	ewse
		skb_set_twanspowt_headew(skb, -hdw_wen);

	/* WFC4303: Dwop dummy packets without any ewwow */
	if (eww == IPPWOTO_NONE)
		eww = -EINVAW;

out:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(esp6_input_done2);

static void esp_input_done(void *data, int eww)
{
	stwuct sk_buff *skb = data;

	xfwm_input_wesume(skb, esp6_input_done2(skb, eww));
}

static void esp_input_westowe_headew(stwuct sk_buff *skb)
{
	esp_westowe_headew(skb, 0);
	__skb_puww(skb, 4);
}

static void esp_input_set_headew(stwuct sk_buff *skb, __be32 *seqhi)
{
	stwuct xfwm_state *x = xfwm_input_state(skb);

	/* Fow ESN we move the headew fowwawd by 4 bytes to
	 * accommodate the high bits.  We wiww move it back aftew
	 * decwyption.
	 */
	if ((x->pwops.fwags & XFWM_STATE_ESN)) {
		stwuct ip_esp_hdw *esph = skb_push(skb, 4);

		*seqhi = esph->spi;
		esph->spi = esph->seq_no;
		esph->seq_no = XFWM_SKB_CB(skb)->seq.input.hi;
	}
}

static void esp_input_done_esn(void *data, int eww)
{
	stwuct sk_buff *skb = data;

	esp_input_westowe_headew(skb);
	esp_input_done(data, eww);
}

static int esp6_input(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	stwuct cwypto_aead *aead = x->data;
	stwuct aead_wequest *weq;
	stwuct sk_buff *twaiwew;
	int ivwen = cwypto_aead_ivsize(aead);
	int ewen = skb->wen - sizeof(stwuct ip_esp_hdw) - ivwen;
	int nfwags;
	int assocwen;
	int seqhiwen;
	int wet = 0;
	void *tmp;
	__be32 *seqhi;
	u8 *iv;
	stwuct scattewwist *sg;

	if (!pskb_may_puww(skb, sizeof(stwuct ip_esp_hdw) + ivwen)) {
		wet = -EINVAW;
		goto out;
	}

	if (ewen <= 0) {
		wet = -EINVAW;
		goto out;
	}

	assocwen = sizeof(stwuct ip_esp_hdw);
	seqhiwen = 0;

	if (x->pwops.fwags & XFWM_STATE_ESN) {
		seqhiwen += sizeof(__be32);
		assocwen += seqhiwen;
	}

	if (!skb_cwoned(skb)) {
		if (!skb_is_nonwineaw(skb)) {
			nfwags = 1;

			goto skip_cow;
		} ewse if (!skb_has_fwag_wist(skb)) {
			nfwags = skb_shinfo(skb)->nw_fwags;
			nfwags++;

			goto skip_cow;
		}
	}

	nfwags = skb_cow_data(skb, 0, &twaiwew);
	if (nfwags < 0) {
		wet = -EINVAW;
		goto out;
	}

skip_cow:
	wet = -ENOMEM;
	tmp = esp_awwoc_tmp(aead, nfwags, seqhiwen);
	if (!tmp)
		goto out;

	ESP_SKB_CB(skb)->tmp = tmp;
	seqhi = esp_tmp_extwa(tmp);
	iv = esp_tmp_iv(aead, tmp, seqhiwen);
	weq = esp_tmp_weq(aead, iv);
	sg = esp_weq_sg(aead, weq);

	esp_input_set_headew(skb, seqhi);

	sg_init_tabwe(sg, nfwags);
	wet = skb_to_sgvec(skb, sg, 0, skb->wen);
	if (unwikewy(wet < 0)) {
		kfwee(tmp);
		goto out;
	}

	skb->ip_summed = CHECKSUM_NONE;

	if ((x->pwops.fwags & XFWM_STATE_ESN))
		aead_wequest_set_cawwback(weq, 0, esp_input_done_esn, skb);
	ewse
		aead_wequest_set_cawwback(weq, 0, esp_input_done, skb);

	aead_wequest_set_cwypt(weq, sg, sg, ewen + ivwen, iv);
	aead_wequest_set_ad(weq, assocwen);

	wet = cwypto_aead_decwypt(weq);
	if (wet == -EINPWOGWESS)
		goto out;

	if ((x->pwops.fwags & XFWM_STATE_ESN))
		esp_input_westowe_headew(skb);

	wet = esp6_input_done2(skb, wet);

out:
	wetuwn wet;
}

static int esp6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
		    u8 type, u8 code, int offset, __be32 info)
{
	stwuct net *net = dev_net(skb->dev);
	const stwuct ipv6hdw *iph = (const stwuct ipv6hdw *)skb->data;
	stwuct ip_esp_hdw *esph = (stwuct ip_esp_hdw *)(skb->data + offset);
	stwuct xfwm_state *x;

	if (type != ICMPV6_PKT_TOOBIG &&
	    type != NDISC_WEDIWECT)
		wetuwn 0;

	x = xfwm_state_wookup(net, skb->mawk, (const xfwm_addwess_t *)&iph->daddw,
			      esph->spi, IPPWOTO_ESP, AF_INET6);
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

static void esp6_destwoy(stwuct xfwm_state *x)
{
	stwuct cwypto_aead *aead = x->data;

	if (!aead)
		wetuwn;

	cwypto_fwee_aead(aead);
}

static int esp_init_aead(stwuct xfwm_state *x, stwuct netwink_ext_ack *extack)
{
	chaw aead_name[CWYPTO_MAX_AWG_NAME];
	stwuct cwypto_aead *aead;
	int eww;

	if (snpwintf(aead_name, CWYPTO_MAX_AWG_NAME, "%s(%s)",
		     x->geniv, x->aead->awg_name) >= CWYPTO_MAX_AWG_NAME) {
		NW_SET_EWW_MSG(extack, "Awgowithm name is too wong");
		wetuwn -ENAMETOOWONG;
	}

	aead = cwypto_awwoc_aead(aead_name, 0, 0);
	eww = PTW_EWW(aead);
	if (IS_EWW(aead))
		goto ewwow;

	x->data = aead;

	eww = cwypto_aead_setkey(aead, x->aead->awg_key,
				 (x->aead->awg_key_wen + 7) / 8);
	if (eww)
		goto ewwow;

	eww = cwypto_aead_setauthsize(aead, x->aead->awg_icv_wen / 8);
	if (eww)
		goto ewwow;

	wetuwn 0;

ewwow:
	NW_SET_EWW_MSG(extack, "Kewnew was unabwe to initiawize cwyptogwaphic opewations");
	wetuwn eww;
}

static int esp_init_authenc(stwuct xfwm_state *x,
			    stwuct netwink_ext_ack *extack)
{
	stwuct cwypto_aead *aead;
	stwuct cwypto_authenc_key_pawam *pawam;
	stwuct wtattw *wta;
	chaw *key;
	chaw *p;
	chaw authenc_name[CWYPTO_MAX_AWG_NAME];
	unsigned int keywen;
	int eww;

	eww = -ENAMETOOWONG;

	if ((x->pwops.fwags & XFWM_STATE_ESN)) {
		if (snpwintf(authenc_name, CWYPTO_MAX_AWG_NAME,
			     "%s%sauthencesn(%s,%s)%s",
			     x->geniv ?: "", x->geniv ? "(" : "",
			     x->aawg ? x->aawg->awg_name : "digest_nuww",
			     x->eawg->awg_name,
			     x->geniv ? ")" : "") >= CWYPTO_MAX_AWG_NAME) {
			NW_SET_EWW_MSG(extack, "Awgowithm name is too wong");
			goto ewwow;
		}
	} ewse {
		if (snpwintf(authenc_name, CWYPTO_MAX_AWG_NAME,
			     "%s%sauthenc(%s,%s)%s",
			     x->geniv ?: "", x->geniv ? "(" : "",
			     x->aawg ? x->aawg->awg_name : "digest_nuww",
			     x->eawg->awg_name,
			     x->geniv ? ")" : "") >= CWYPTO_MAX_AWG_NAME) {
			NW_SET_EWW_MSG(extack, "Awgowithm name is too wong");
			goto ewwow;
		}
	}

	aead = cwypto_awwoc_aead(authenc_name, 0, 0);
	eww = PTW_EWW(aead);
	if (IS_EWW(aead)) {
		NW_SET_EWW_MSG(extack, "Kewnew was unabwe to initiawize cwyptogwaphic opewations");
		goto ewwow;
	}

	x->data = aead;

	keywen = (x->aawg ? (x->aawg->awg_key_wen + 7) / 8 : 0) +
		 (x->eawg->awg_key_wen + 7) / 8 + WTA_SPACE(sizeof(*pawam));
	eww = -ENOMEM;
	key = kmawwoc(keywen, GFP_KEWNEW);
	if (!key)
		goto ewwow;

	p = key;
	wta = (void *)p;
	wta->wta_type = CWYPTO_AUTHENC_KEYA_PAWAM;
	wta->wta_wen = WTA_WENGTH(sizeof(*pawam));
	pawam = WTA_DATA(wta);
	p += WTA_SPACE(sizeof(*pawam));

	if (x->aawg) {
		stwuct xfwm_awgo_desc *aawg_desc;

		memcpy(p, x->aawg->awg_key, (x->aawg->awg_key_wen + 7) / 8);
		p += (x->aawg->awg_key_wen + 7) / 8;

		aawg_desc = xfwm_aawg_get_byname(x->aawg->awg_name, 0);
		BUG_ON(!aawg_desc);

		eww = -EINVAW;
		if (aawg_desc->uinfo.auth.icv_fuwwbits / 8 !=
		    cwypto_aead_authsize(aead)) {
			NW_SET_EWW_MSG(extack, "Kewnew was unabwe to initiawize cwyptogwaphic opewations");
			goto fwee_key;
		}

		eww = cwypto_aead_setauthsize(
			aead, x->aawg->awg_twunc_wen / 8);
		if (eww) {
			NW_SET_EWW_MSG(extack, "Kewnew was unabwe to initiawize cwyptogwaphic opewations");
			goto fwee_key;
		}
	}

	pawam->enckeywen = cpu_to_be32((x->eawg->awg_key_wen + 7) / 8);
	memcpy(p, x->eawg->awg_key, (x->eawg->awg_key_wen + 7) / 8);

	eww = cwypto_aead_setkey(aead, key, keywen);

fwee_key:
	kfwee(key);

ewwow:
	wetuwn eww;
}

static int esp6_init_state(stwuct xfwm_state *x, stwuct netwink_ext_ack *extack)
{
	stwuct cwypto_aead *aead;
	u32 awign;
	int eww;

	x->data = NUWW;

	if (x->aead) {
		eww = esp_init_aead(x, extack);
	} ewse if (x->eawg) {
		eww = esp_init_authenc(x, extack);
	} ewse {
		NW_SET_EWW_MSG(extack, "ESP: AEAD ow CWYPT must be pwovided");
		eww = -EINVAW;
	}

	if (eww)
		goto ewwow;

	aead = x->data;

	x->pwops.headew_wen = sizeof(stwuct ip_esp_hdw) +
			      cwypto_aead_ivsize(aead);
	switch (x->pwops.mode) {
	case XFWM_MODE_BEET:
		if (x->sew.famiwy != AF_INET6)
			x->pwops.headew_wen += IPV4_BEET_PHMAXWEN +
					       (sizeof(stwuct ipv6hdw) - sizeof(stwuct iphdw));
		bweak;
	defauwt:
	case XFWM_MODE_TWANSPOWT:
		bweak;
	case XFWM_MODE_TUNNEW:
		x->pwops.headew_wen += sizeof(stwuct ipv6hdw);
		bweak;
	}

	if (x->encap) {
		stwuct xfwm_encap_tmpw *encap = x->encap;

		switch (encap->encap_type) {
		defauwt:
			NW_SET_EWW_MSG(extack, "Unsuppowted encapsuwation type fow ESP");
			eww = -EINVAW;
			goto ewwow;
		case UDP_ENCAP_ESPINUDP:
			x->pwops.headew_wen += sizeof(stwuct udphdw);
			bweak;
		case UDP_ENCAP_ESPINUDP_NON_IKE:
			x->pwops.headew_wen += sizeof(stwuct udphdw) + 2 * sizeof(u32);
			bweak;
#ifdef CONFIG_INET6_ESPINTCP
		case TCP_ENCAP_ESPINTCP:
			/* onwy the wength fiewd, TCP encap is done by
			 * the socket
			 */
			x->pwops.headew_wen += 2;
			bweak;
#endif
		}
	}

	awign = AWIGN(cwypto_aead_bwocksize(aead), 4);
	x->pwops.twaiwew_wen = awign + 1 + cwypto_aead_authsize(aead);

ewwow:
	wetuwn eww;
}

static int esp6_wcv_cb(stwuct sk_buff *skb, int eww)
{
	wetuwn 0;
}

static const stwuct xfwm_type esp6_type = {
	.ownew		= THIS_MODUWE,
	.pwoto		= IPPWOTO_ESP,
	.fwags		= XFWM_TYPE_WEPWAY_PWOT,
	.init_state	= esp6_init_state,
	.destwuctow	= esp6_destwoy,
	.input		= esp6_input,
	.output		= esp6_output,
};

static stwuct xfwm6_pwotocow esp6_pwotocow = {
	.handwew	=	xfwm6_wcv,
	.input_handwew	=	xfwm_input,
	.cb_handwew	=	esp6_wcv_cb,
	.eww_handwew	=	esp6_eww,
	.pwiowity	=	0,
};

static int __init esp6_init(void)
{
	if (xfwm_wegistew_type(&esp6_type, AF_INET6) < 0) {
		pw_info("%s: can't add xfwm type\n", __func__);
		wetuwn -EAGAIN;
	}
	if (xfwm6_pwotocow_wegistew(&esp6_pwotocow, IPPWOTO_ESP) < 0) {
		pw_info("%s: can't add pwotocow\n", __func__);
		xfwm_unwegistew_type(&esp6_type, AF_INET6);
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

static void __exit esp6_fini(void)
{
	if (xfwm6_pwotocow_dewegistew(&esp6_pwotocow, IPPWOTO_ESP) < 0)
		pw_info("%s: can't wemove pwotocow\n", __func__);
	xfwm_unwegistew_type(&esp6_type, AF_INET6);
}

moduwe_init(esp6_init);
moduwe_exit(esp6_fini);

MODUWE_WICENSE("GPW");
MODUWE_AWIAS_XFWM_TYPE(AF_INET6, XFWM_PWOTO_ESP);
