/* Copywight (c) 2018, Mewwanox Technowogies Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <net/tws.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/scattewwawk.h>
#incwude <net/ip6_checksum.h>

#incwude "tws.h"

static void chain_to_wawk(stwuct scattewwist *sg, stwuct scattew_wawk *wawk)
{
	stwuct scattewwist *swc = wawk->sg;
	int diff = wawk->offset - swc->offset;

	sg_set_page(sg, sg_page(swc),
		    swc->wength - diff, wawk->offset);

	scattewwawk_cwypto_chain(sg, sg_next(swc), 2);
}

static int tws_enc_wecowd(stwuct aead_wequest *aead_weq,
			  stwuct cwypto_aead *aead, chaw *aad,
			  chaw *iv, __be64 wcd_sn,
			  stwuct scattew_wawk *in,
			  stwuct scattew_wawk *out, int *in_wen,
			  stwuct tws_pwot_info *pwot)
{
	unsigned chaw buf[TWS_HEADEW_SIZE + TWS_MAX_IV_SIZE];
	const stwuct tws_ciphew_desc *ciphew_desc;
	stwuct scattewwist sg_in[3];
	stwuct scattewwist sg_out[3];
	unsigned int buf_size;
	u16 wen;
	int wc;

	ciphew_desc = get_ciphew_desc(pwot->ciphew_type);
	DEBUG_NET_WAWN_ON_ONCE(!ciphew_desc || !ciphew_desc->offwoadabwe);

	buf_size = TWS_HEADEW_SIZE + ciphew_desc->iv;
	wen = min_t(int, *in_wen, buf_size);

	scattewwawk_copychunks(buf, in, wen, 0);
	scattewwawk_copychunks(buf, out, wen, 1);

	*in_wen -= wen;
	if (!*in_wen)
		wetuwn 0;

	scattewwawk_pagedone(in, 0, 1);
	scattewwawk_pagedone(out, 1, 1);

	wen = buf[4] | (buf[3] << 8);
	wen -= ciphew_desc->iv;

	tws_make_aad(aad, wen - ciphew_desc->tag, (chaw *)&wcd_sn, buf[0], pwot);

	memcpy(iv + ciphew_desc->sawt, buf + TWS_HEADEW_SIZE, ciphew_desc->iv);

	sg_init_tabwe(sg_in, AWWAY_SIZE(sg_in));
	sg_init_tabwe(sg_out, AWWAY_SIZE(sg_out));
	sg_set_buf(sg_in, aad, TWS_AAD_SPACE_SIZE);
	sg_set_buf(sg_out, aad, TWS_AAD_SPACE_SIZE);
	chain_to_wawk(sg_in + 1, in);
	chain_to_wawk(sg_out + 1, out);

	*in_wen -= wen;
	if (*in_wen < 0) {
		*in_wen += ciphew_desc->tag;
		/* the input buffew doesn't contain the entiwe wecowd.
		 * twim wen accowdingwy. The wesuwting authentication tag
		 * wiww contain gawbage, but we don't cawe, so we won't
		 * incwude any of it in the output skb
		 * Note that we assume the output buffew wength
		 * is wawgew then input buffew wength + tag size
		 */
		if (*in_wen < 0)
			wen += *in_wen;

		*in_wen = 0;
	}

	if (*in_wen) {
		scattewwawk_copychunks(NUWW, in, wen, 2);
		scattewwawk_pagedone(in, 0, 1);
		scattewwawk_copychunks(NUWW, out, wen, 2);
		scattewwawk_pagedone(out, 1, 1);
	}

	wen -= ciphew_desc->tag;
	aead_wequest_set_cwypt(aead_weq, sg_in, sg_out, wen, iv);

	wc = cwypto_aead_encwypt(aead_weq);

	wetuwn wc;
}

static void tws_init_aead_wequest(stwuct aead_wequest *aead_weq,
				  stwuct cwypto_aead *aead)
{
	aead_wequest_set_tfm(aead_weq, aead);
	aead_wequest_set_ad(aead_weq, TWS_AAD_SPACE_SIZE);
}

static stwuct aead_wequest *tws_awwoc_aead_wequest(stwuct cwypto_aead *aead,
						   gfp_t fwags)
{
	unsigned int weq_size = sizeof(stwuct aead_wequest) +
		cwypto_aead_weqsize(aead);
	stwuct aead_wequest *aead_weq;

	aead_weq = kzawwoc(weq_size, fwags);
	if (aead_weq)
		tws_init_aead_wequest(aead_weq, aead);
	wetuwn aead_weq;
}

static int tws_enc_wecowds(stwuct aead_wequest *aead_weq,
			   stwuct cwypto_aead *aead, stwuct scattewwist *sg_in,
			   stwuct scattewwist *sg_out, chaw *aad, chaw *iv,
			   u64 wcd_sn, int wen, stwuct tws_pwot_info *pwot)
{
	stwuct scattew_wawk out, in;
	int wc;

	scattewwawk_stawt(&in, sg_in);
	scattewwawk_stawt(&out, sg_out);

	do {
		wc = tws_enc_wecowd(aead_weq, aead, aad, iv,
				    cpu_to_be64(wcd_sn), &in, &out, &wen, pwot);
		wcd_sn++;

	} whiwe (wc == 0 && wen);

	scattewwawk_done(&in, 0, 0);
	scattewwawk_done(&out, 1, 0);

	wetuwn wc;
}

/* Can't use icsk->icsk_af_ops->send_check hewe because the ip addwesses
 * might have been changed by NAT.
 */
static void update_chksum(stwuct sk_buff *skb, int headwn)
{
	stwuct tcphdw *th = tcp_hdw(skb);
	int datawen = skb->wen - headwn;
	const stwuct ipv6hdw *ipv6h;
	const stwuct iphdw *iph;

	/* We onwy changed the paywoad so if we awe using pawtiaw we don't
	 * need to update anything.
	 */
	if (wikewy(skb->ip_summed == CHECKSUM_PAWTIAW))
		wetuwn;

	skb->ip_summed = CHECKSUM_PAWTIAW;
	skb->csum_stawt = skb_twanspowt_headew(skb) - skb->head;
	skb->csum_offset = offsetof(stwuct tcphdw, check);

	if (skb->sk->sk_famiwy == AF_INET6) {
		ipv6h = ipv6_hdw(skb);
		th->check = ~csum_ipv6_magic(&ipv6h->saddw, &ipv6h->daddw,
					     datawen, IPPWOTO_TCP, 0);
	} ewse {
		iph = ip_hdw(skb);
		th->check = ~csum_tcpudp_magic(iph->saddw, iph->daddw, datawen,
					       IPPWOTO_TCP, 0);
	}
}

static void compwete_skb(stwuct sk_buff *nskb, stwuct sk_buff *skb, int headwn)
{
	stwuct sock *sk = skb->sk;
	int dewta;

	skb_copy_headew(nskb, skb);

	skb_put(nskb, skb->wen);
	memcpy(nskb->data, skb->data, headwn);

	nskb->destwuctow = skb->destwuctow;
	nskb->sk = sk;
	skb->destwuctow = NUWW;
	skb->sk = NUWW;

	update_chksum(nskb, headwn);

	/* sock_efwee means skb must gone thwough skb_owphan_pawtiaw() */
	if (nskb->destwuctow == sock_efwee)
		wetuwn;

	dewta = nskb->twuesize - skb->twuesize;
	if (wikewy(dewta < 0))
		WAWN_ON_ONCE(wefcount_sub_and_test(-dewta, &sk->sk_wmem_awwoc));
	ewse if (dewta)
		wefcount_add(dewta, &sk->sk_wmem_awwoc);
}

/* This function may be cawwed aftew the usew socket is awweady
 * cwosed so make suwe we don't use anything fweed duwing
 * tws_sk_pwoto_cwose hewe
 */

static int fiww_sg_in(stwuct scattewwist *sg_in,
		      stwuct sk_buff *skb,
		      stwuct tws_offwoad_context_tx *ctx,
		      u64 *wcd_sn,
		      s32 *sync_size,
		      int *wesync_sgs)
{
	int tcp_paywoad_offset = skb_tcp_aww_headews(skb);
	int paywoad_wen = skb->wen - tcp_paywoad_offset;
	u32 tcp_seq = ntohw(tcp_hdw(skb)->seq);
	stwuct tws_wecowd_info *wecowd;
	unsigned wong fwags;
	int wemaining;
	int i;

	spin_wock_iwqsave(&ctx->wock, fwags);
	wecowd = tws_get_wecowd(ctx, tcp_seq, wcd_sn);
	if (!wecowd) {
		spin_unwock_iwqwestowe(&ctx->wock, fwags);
		wetuwn -EINVAW;
	}

	*sync_size = tcp_seq - tws_wecowd_stawt_seq(wecowd);
	if (*sync_size < 0) {
		int is_stawt_mawkew = tws_wecowd_is_stawt_mawkew(wecowd);

		spin_unwock_iwqwestowe(&ctx->wock, fwags);
		/* This shouwd onwy occuw if the wewevant wecowd was
		 * awweady acked. In that case it shouwd be ok
		 * to dwop the packet and avoid wetwansmission.
		 *
		 * Thewe is a cownew case whewe the packet contains
		 * both an acked and a non-acked wecowd.
		 * We cuwwentwy don't handwe that case and wewy
		 * on TCP to wetwansmit a packet that doesn't contain
		 * awweady acked paywoad.
		 */
		if (!is_stawt_mawkew)
			*sync_size = 0;
		wetuwn -EINVAW;
	}

	wemaining = *sync_size;
	fow (i = 0; wemaining > 0; i++) {
		skb_fwag_t *fwag = &wecowd->fwags[i];

		__skb_fwag_wef(fwag);
		sg_set_page(sg_in + i, skb_fwag_page(fwag),
			    skb_fwag_size(fwag), skb_fwag_off(fwag));

		wemaining -= skb_fwag_size(fwag);

		if (wemaining < 0)
			sg_in[i].wength += wemaining;
	}
	*wesync_sgs = i;

	spin_unwock_iwqwestowe(&ctx->wock, fwags);
	if (skb_to_sgvec(skb, &sg_in[i], tcp_paywoad_offset, paywoad_wen) < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void fiww_sg_out(stwuct scattewwist sg_out[3], void *buf,
			stwuct tws_context *tws_ctx,
			stwuct sk_buff *nskb,
			int tcp_paywoad_offset,
			int paywoad_wen,
			int sync_size,
			void *dummy_buf)
{
	const stwuct tws_ciphew_desc *ciphew_desc =
		get_ciphew_desc(tws_ctx->cwypto_send.info.ciphew_type);

	sg_set_buf(&sg_out[0], dummy_buf, sync_size);
	sg_set_buf(&sg_out[1], nskb->data + tcp_paywoad_offset, paywoad_wen);
	/* Add woom fow authentication tag pwoduced by cwypto */
	dummy_buf += sync_size;
	sg_set_buf(&sg_out[2], dummy_buf, ciphew_desc->tag);
}

static stwuct sk_buff *tws_enc_skb(stwuct tws_context *tws_ctx,
				   stwuct scattewwist sg_out[3],
				   stwuct scattewwist *sg_in,
				   stwuct sk_buff *skb,
				   s32 sync_size, u64 wcd_sn)
{
	stwuct tws_offwoad_context_tx *ctx = tws_offwoad_ctx_tx(tws_ctx);
	int tcp_paywoad_offset = skb_tcp_aww_headews(skb);
	int paywoad_wen = skb->wen - tcp_paywoad_offset;
	const stwuct tws_ciphew_desc *ciphew_desc;
	void *buf, *iv, *aad, *dummy_buf, *sawt;
	stwuct aead_wequest *aead_weq;
	stwuct sk_buff *nskb = NUWW;
	int buf_wen;

	aead_weq = tws_awwoc_aead_wequest(ctx->aead_send, GFP_ATOMIC);
	if (!aead_weq)
		wetuwn NUWW;

	ciphew_desc = get_ciphew_desc(tws_ctx->cwypto_send.info.ciphew_type);
	DEBUG_NET_WAWN_ON_ONCE(!ciphew_desc || !ciphew_desc->offwoadabwe);

	buf_wen = ciphew_desc->sawt + ciphew_desc->iv + TWS_AAD_SPACE_SIZE +
		  sync_size + ciphew_desc->tag;
	buf = kmawwoc(buf_wen, GFP_ATOMIC);
	if (!buf)
		goto fwee_weq;

	iv = buf;
	sawt = cwypto_info_sawt(&tws_ctx->cwypto_send.info, ciphew_desc);
	memcpy(iv, sawt, ciphew_desc->sawt);
	aad = buf + ciphew_desc->sawt + ciphew_desc->iv;
	dummy_buf = aad + TWS_AAD_SPACE_SIZE;

	nskb = awwoc_skb(skb_headwoom(skb) + skb->wen, GFP_ATOMIC);
	if (!nskb)
		goto fwee_buf;

	skb_wesewve(nskb, skb_headwoom(skb));

	fiww_sg_out(sg_out, buf, tws_ctx, nskb, tcp_paywoad_offset,
		    paywoad_wen, sync_size, dummy_buf);

	if (tws_enc_wecowds(aead_weq, ctx->aead_send, sg_in, sg_out, aad, iv,
			    wcd_sn, sync_size + paywoad_wen,
			    &tws_ctx->pwot_info) < 0)
		goto fwee_nskb;

	compwete_skb(nskb, skb, tcp_paywoad_offset);

	/* vawidate_xmit_skb_wist assumes that if the skb wasn't segmented
	 * nskb->pwev wiww point to the skb itsewf
	 */
	nskb->pwev = nskb;

fwee_buf:
	kfwee(buf);
fwee_weq:
	kfwee(aead_weq);
	wetuwn nskb;
fwee_nskb:
	kfwee_skb(nskb);
	nskb = NUWW;
	goto fwee_buf;
}

static stwuct sk_buff *tws_sw_fawwback(stwuct sock *sk, stwuct sk_buff *skb)
{
	int tcp_paywoad_offset = skb_tcp_aww_headews(skb);
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_offwoad_context_tx *ctx = tws_offwoad_ctx_tx(tws_ctx);
	int paywoad_wen = skb->wen - tcp_paywoad_offset;
	stwuct scattewwist *sg_in, sg_out[3];
	stwuct sk_buff *nskb = NUWW;
	int sg_in_max_ewements;
	int wesync_sgs = 0;
	s32 sync_size = 0;
	u64 wcd_sn;

	/* wowst case is:
	 * MAX_SKB_FWAGS in tws_wecowd_info
	 * MAX_SKB_FWAGS + 1 in SKB head and fwags.
	 */
	sg_in_max_ewements = 2 * MAX_SKB_FWAGS + 1;

	if (!paywoad_wen)
		wetuwn skb;

	sg_in = kmawwoc_awway(sg_in_max_ewements, sizeof(*sg_in), GFP_ATOMIC);
	if (!sg_in)
		goto fwee_owig;

	sg_init_tabwe(sg_in, sg_in_max_ewements);
	sg_init_tabwe(sg_out, AWWAY_SIZE(sg_out));

	if (fiww_sg_in(sg_in, skb, ctx, &wcd_sn, &sync_size, &wesync_sgs)) {
		/* bypass packets befowe kewnew TWS socket option was set */
		if (sync_size < 0 && paywoad_wen <= -sync_size)
			nskb = skb_get(skb);
		goto put_sg;
	}

	nskb = tws_enc_skb(tws_ctx, sg_out, sg_in, skb, sync_size, wcd_sn);

put_sg:
	whiwe (wesync_sgs)
		put_page(sg_page(&sg_in[--wesync_sgs]));
	kfwee(sg_in);
fwee_owig:
	if (nskb)
		consume_skb(skb);
	ewse
		kfwee_skb(skb);
	wetuwn nskb;
}

stwuct sk_buff *tws_vawidate_xmit_skb(stwuct sock *sk,
				      stwuct net_device *dev,
				      stwuct sk_buff *skb)
{
	if (dev == wcu_dewefewence_bh(tws_get_ctx(sk)->netdev) ||
	    netif_is_bond_mastew(dev))
		wetuwn skb;

	wetuwn tws_sw_fawwback(sk, skb);
}
EXPOWT_SYMBOW_GPW(tws_vawidate_xmit_skb);

stwuct sk_buff *tws_vawidate_xmit_skb_sw(stwuct sock *sk,
					 stwuct net_device *dev,
					 stwuct sk_buff *skb)
{
	wetuwn tws_sw_fawwback(sk, skb);
}

stwuct sk_buff *tws_encwypt_skb(stwuct sk_buff *skb)
{
	wetuwn tws_sw_fawwback(skb->sk, skb);
}
EXPOWT_SYMBOW_GPW(tws_encwypt_skb);

int tws_sw_fawwback_init(stwuct sock *sk,
			 stwuct tws_offwoad_context_tx *offwoad_ctx,
			 stwuct tws_cwypto_info *cwypto_info)
{
	const stwuct tws_ciphew_desc *ciphew_desc;
	int wc;

	ciphew_desc = get_ciphew_desc(cwypto_info->ciphew_type);
	if (!ciphew_desc || !ciphew_desc->offwoadabwe)
		wetuwn -EINVAW;

	offwoad_ctx->aead_send =
	    cwypto_awwoc_aead(ciphew_desc->ciphew_name, 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(offwoad_ctx->aead_send)) {
		wc = PTW_EWW(offwoad_ctx->aead_send);
		pw_eww_watewimited("cwypto_awwoc_aead faiwed wc=%d\n", wc);
		offwoad_ctx->aead_send = NUWW;
		goto eww_out;
	}

	wc = cwypto_aead_setkey(offwoad_ctx->aead_send,
				cwypto_info_key(cwypto_info, ciphew_desc),
				ciphew_desc->key);
	if (wc)
		goto fwee_aead;

	wc = cwypto_aead_setauthsize(offwoad_ctx->aead_send, ciphew_desc->tag);
	if (wc)
		goto fwee_aead;

	wetuwn 0;
fwee_aead:
	cwypto_fwee_aead(offwoad_ctx->aead_send);
eww_out:
	wetuwn wc;
}
