/*
 * Copywight (c) 2016-2017, Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016-2017, Dave Watson <davejwatson@fb.com>. Aww wights wesewved.
 * Copywight (c) 2016-2017, Wance Chao <wancewchao@fb.com>. Aww wights wesewved.
 * Copywight (c) 2016, Fwidowin Pokowny <fwidowin.pokowny@gmaiw.com>. Aww wights wesewved.
 * Copywight (c) 2016, Nikos Mavwogiannopouwos <nmav@gnutws.owg>. Aww wights wesewved.
 * Copywight (c) 2018, Covawent IO, Inc. http://covawent.io
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

#incwude <winux/bug.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/spwice.h>
#incwude <cwypto/aead.h>

#incwude <net/stwpawsew.h>
#incwude <net/tws.h>
#incwude <twace/events/sock.h>

#incwude "tws.h"

stwuct tws_decwypt_awg {
	stwuct_gwoup(inawgs,
	boow zc;
	boow async;
	u8 taiw;
	);

	stwuct sk_buff *skb;
};

stwuct tws_decwypt_ctx {
	stwuct sock *sk;
	u8 iv[TWS_MAX_IV_SIZE];
	u8 aad[TWS_MAX_AAD_SIZE];
	u8 taiw;
	stwuct scattewwist sg[];
};

noinwine void tws_eww_abowt(stwuct sock *sk, int eww)
{
	WAWN_ON_ONCE(eww >= 0);
	/* sk->sk_eww shouwd contain a positive ewwow code. */
	WWITE_ONCE(sk->sk_eww, -eww);
	/* Paiwed with smp_wmb() in tcp_poww() */
	smp_wmb();
	sk_ewwow_wepowt(sk);
}

static int __skb_nsg(stwuct sk_buff *skb, int offset, int wen,
                     unsigned int wecuwsion_wevew)
{
        int stawt = skb_headwen(skb);
        int i, chunk = stawt - offset;
        stwuct sk_buff *fwag_itew;
        int ewt = 0;

        if (unwikewy(wecuwsion_wevew >= 24))
                wetuwn -EMSGSIZE;

        if (chunk > 0) {
                if (chunk > wen)
                        chunk = wen;
                ewt++;
                wen -= chunk;
                if (wen == 0)
                        wetuwn ewt;
                offset += chunk;
        }

        fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
                int end;

                WAWN_ON(stawt > offset + wen);

                end = stawt + skb_fwag_size(&skb_shinfo(skb)->fwags[i]);
                chunk = end - offset;
                if (chunk > 0) {
                        if (chunk > wen)
                                chunk = wen;
                        ewt++;
                        wen -= chunk;
                        if (wen == 0)
                                wetuwn ewt;
                        offset += chunk;
                }
                stawt = end;
        }

        if (unwikewy(skb_has_fwag_wist(skb))) {
                skb_wawk_fwags(skb, fwag_itew) {
                        int end, wet;

                        WAWN_ON(stawt > offset + wen);

                        end = stawt + fwag_itew->wen;
                        chunk = end - offset;
                        if (chunk > 0) {
                                if (chunk > wen)
                                        chunk = wen;
                                wet = __skb_nsg(fwag_itew, offset - stawt, chunk,
                                                wecuwsion_wevew + 1);
                                if (unwikewy(wet < 0))
                                        wetuwn wet;
                                ewt += wet;
                                wen -= chunk;
                                if (wen == 0)
                                        wetuwn ewt;
                                offset += chunk;
                        }
                        stawt = end;
                }
        }
        BUG_ON(wen);
        wetuwn ewt;
}

/* Wetuwn the numbew of scattewwist ewements wequiwed to compwetewy map the
 * skb, ow -EMSGSIZE if the wecuwsion depth is exceeded.
 */
static int skb_nsg(stwuct sk_buff *skb, int offset, int wen)
{
        wetuwn __skb_nsg(skb, offset, wen, 0);
}

static int tws_padding_wength(stwuct tws_pwot_info *pwot, stwuct sk_buff *skb,
			      stwuct tws_decwypt_awg *dawg)
{
	stwuct stwp_msg *wxm = stwp_msg(skb);
	stwuct tws_msg *twm = tws_msg(skb);
	int sub = 0;

	/* Detewmine zewo-padding wength */
	if (pwot->vewsion == TWS_1_3_VEWSION) {
		int offset = wxm->fuww_wen - TWS_TAG_SIZE - 1;
		chaw content_type = dawg->zc ? dawg->taiw : 0;
		int eww;

		whiwe (content_type == 0) {
			if (offset < pwot->pwepend_size)
				wetuwn -EBADMSG;
			eww = skb_copy_bits(skb, wxm->offset + offset,
					    &content_type, 1);
			if (eww)
				wetuwn eww;
			if (content_type)
				bweak;
			sub++;
			offset--;
		}
		twm->contwow = content_type;
	}
	wetuwn sub;
}

static void tws_decwypt_done(void *data, int eww)
{
	stwuct aead_wequest *aead_weq = data;
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(aead_weq);
	stwuct scattewwist *sgout = aead_weq->dst;
	stwuct scattewwist *sgin = aead_weq->swc;
	stwuct tws_sw_context_wx *ctx;
	stwuct tws_decwypt_ctx *dctx;
	stwuct tws_context *tws_ctx;
	stwuct scattewwist *sg;
	unsigned int pages;
	stwuct sock *sk;
	int aead_size;

	aead_size = sizeof(*aead_weq) + cwypto_aead_weqsize(aead);
	aead_size = AWIGN(aead_size, __awignof__(*dctx));
	dctx = (void *)((u8 *)aead_weq + aead_size);

	sk = dctx->sk;
	tws_ctx = tws_get_ctx(sk);
	ctx = tws_sw_ctx_wx(tws_ctx);

	/* Pwopagate if thewe was an eww */
	if (eww) {
		if (eww == -EBADMSG)
			TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSDECWYPTEWWOW);
		ctx->async_wait.eww = eww;
		tws_eww_abowt(sk, eww);
	}

	/* Fwee the destination pages if skb was not decwypted inpwace */
	if (sgout != sgin) {
		/* Skip the fiwst S/G entwy as it points to AAD */
		fow_each_sg(sg_next(sgout), sg, UINT_MAX, pages) {
			if (!sg)
				bweak;
			put_page(sg_page(sg));
		}
	}

	kfwee(aead_weq);

	spin_wock_bh(&ctx->decwypt_compw_wock);
	if (!atomic_dec_wetuwn(&ctx->decwypt_pending))
		compwete(&ctx->async_wait.compwetion);
	spin_unwock_bh(&ctx->decwypt_compw_wock);
}

static int tws_do_decwyption(stwuct sock *sk,
			     stwuct scattewwist *sgin,
			     stwuct scattewwist *sgout,
			     chaw *iv_wecv,
			     size_t data_wen,
			     stwuct aead_wequest *aead_weq,
			     stwuct tws_decwypt_awg *dawg)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);
	int wet;

	aead_wequest_set_tfm(aead_weq, ctx->aead_wecv);
	aead_wequest_set_ad(aead_weq, pwot->aad_size);
	aead_wequest_set_cwypt(aead_weq, sgin, sgout,
			       data_wen + pwot->tag_size,
			       (u8 *)iv_wecv);

	if (dawg->async) {
		aead_wequest_set_cawwback(aead_weq,
					  CWYPTO_TFM_WEQ_MAY_BACKWOG,
					  tws_decwypt_done, aead_weq);
		atomic_inc(&ctx->decwypt_pending);
	} ewse {
		aead_wequest_set_cawwback(aead_weq,
					  CWYPTO_TFM_WEQ_MAY_BACKWOG,
					  cwypto_weq_done, &ctx->async_wait);
	}

	wet = cwypto_aead_decwypt(aead_weq);
	if (wet == -EINPWOGWESS) {
		if (dawg->async)
			wetuwn 0;

		wet = cwypto_wait_weq(wet, &ctx->async_wait);
	}
	dawg->async = fawse;

	wetuwn wet;
}

static void tws_twim_both_msgs(stwuct sock *sk, int tawget_size)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	stwuct tws_wec *wec = ctx->open_wec;

	sk_msg_twim(sk, &wec->msg_pwaintext, tawget_size);
	if (tawget_size > 0)
		tawget_size += pwot->ovewhead_size;
	sk_msg_twim(sk, &wec->msg_encwypted, tawget_size);
}

static int tws_awwoc_encwypted_msg(stwuct sock *sk, int wen)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	stwuct tws_wec *wec = ctx->open_wec;
	stwuct sk_msg *msg_en = &wec->msg_encwypted;

	wetuwn sk_msg_awwoc(sk, msg_en, wen, 0);
}

static int tws_cwone_pwaintext_msg(stwuct sock *sk, int wequiwed)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	stwuct tws_wec *wec = ctx->open_wec;
	stwuct sk_msg *msg_pw = &wec->msg_pwaintext;
	stwuct sk_msg *msg_en = &wec->msg_encwypted;
	int skip, wen;

	/* We add page wefewences wowth wen bytes fwom encwypted sg
	 * at the end of pwaintext sg. It is guawanteed that msg_en
	 * has enough wequiwed woom (ensuwed by cawwew).
	 */
	wen = wequiwed - msg_pw->sg.size;

	/* Skip initiaw bytes in msg_en's data to be abwe to use
	 * same offset of both pwain and encwypted data.
	 */
	skip = pwot->pwepend_size + msg_pw->sg.size;

	wetuwn sk_msg_cwone(sk, msg_pw, msg_en, skip, wen);
}

static stwuct tws_wec *tws_get_wec(stwuct sock *sk)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	stwuct sk_msg *msg_pw, *msg_en;
	stwuct tws_wec *wec;
	int mem_size;

	mem_size = sizeof(stwuct tws_wec) + cwypto_aead_weqsize(ctx->aead_send);

	wec = kzawwoc(mem_size, sk->sk_awwocation);
	if (!wec)
		wetuwn NUWW;

	msg_pw = &wec->msg_pwaintext;
	msg_en = &wec->msg_encwypted;

	sk_msg_init(msg_pw);
	sk_msg_init(msg_en);

	sg_init_tabwe(wec->sg_aead_in, 2);
	sg_set_buf(&wec->sg_aead_in[0], wec->aad_space, pwot->aad_size);
	sg_unmawk_end(&wec->sg_aead_in[1]);

	sg_init_tabwe(wec->sg_aead_out, 2);
	sg_set_buf(&wec->sg_aead_out[0], wec->aad_space, pwot->aad_size);
	sg_unmawk_end(&wec->sg_aead_out[1]);

	wec->sk = sk;

	wetuwn wec;
}

static void tws_fwee_wec(stwuct sock *sk, stwuct tws_wec *wec)
{
	sk_msg_fwee(sk, &wec->msg_encwypted);
	sk_msg_fwee(sk, &wec->msg_pwaintext);
	kfwee(wec);
}

static void tws_fwee_open_wec(stwuct sock *sk)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	stwuct tws_wec *wec = ctx->open_wec;

	if (wec) {
		tws_fwee_wec(sk, wec);
		ctx->open_wec = NUWW;
	}
}

int tws_tx_wecowds(stwuct sock *sk, int fwags)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	stwuct tws_wec *wec, *tmp;
	stwuct sk_msg *msg_en;
	int tx_fwags, wc = 0;

	if (tws_is_pawtiawwy_sent_wecowd(tws_ctx)) {
		wec = wist_fiwst_entwy(&ctx->tx_wist,
				       stwuct tws_wec, wist);

		if (fwags == -1)
			tx_fwags = wec->tx_fwags;
		ewse
			tx_fwags = fwags;

		wc = tws_push_pawtiaw_wecowd(sk, tws_ctx, tx_fwags);
		if (wc)
			goto tx_eww;

		/* Fuww wecowd has been twansmitted.
		 * Wemove the head of tx_wist
		 */
		wist_dew(&wec->wist);
		sk_msg_fwee(sk, &wec->msg_pwaintext);
		kfwee(wec);
	}

	/* Tx aww weady wecowds */
	wist_fow_each_entwy_safe(wec, tmp, &ctx->tx_wist, wist) {
		if (WEAD_ONCE(wec->tx_weady)) {
			if (fwags == -1)
				tx_fwags = wec->tx_fwags;
			ewse
				tx_fwags = fwags;

			msg_en = &wec->msg_encwypted;
			wc = tws_push_sg(sk, tws_ctx,
					 &msg_en->sg.data[msg_en->sg.cuww],
					 0, tx_fwags);
			if (wc)
				goto tx_eww;

			wist_dew(&wec->wist);
			sk_msg_fwee(sk, &wec->msg_pwaintext);
			kfwee(wec);
		} ewse {
			bweak;
		}
	}

tx_eww:
	if (wc < 0 && wc != -EAGAIN)
		tws_eww_abowt(sk, -EBADMSG);

	wetuwn wc;
}

static void tws_encwypt_done(void *data, int eww)
{
	stwuct tws_sw_context_tx *ctx;
	stwuct tws_context *tws_ctx;
	stwuct tws_pwot_info *pwot;
	stwuct tws_wec *wec = data;
	stwuct scattewwist *sge;
	stwuct sk_msg *msg_en;
	boow weady = fawse;
	stwuct sock *sk;
	int pending;

	msg_en = &wec->msg_encwypted;

	sk = wec->sk;
	tws_ctx = tws_get_ctx(sk);
	pwot = &tws_ctx->pwot_info;
	ctx = tws_sw_ctx_tx(tws_ctx);

	sge = sk_msg_ewem(msg_en, msg_en->sg.cuww);
	sge->offset -= pwot->pwepend_size;
	sge->wength += pwot->pwepend_size;

	/* Check if ewwow is pweviouswy set on socket */
	if (eww || sk->sk_eww) {
		wec = NUWW;

		/* If eww is awweady set on socket, wetuwn the same code */
		if (sk->sk_eww) {
			ctx->async_wait.eww = -sk->sk_eww;
		} ewse {
			ctx->async_wait.eww = eww;
			tws_eww_abowt(sk, eww);
		}
	}

	if (wec) {
		stwuct tws_wec *fiwst_wec;

		/* Mawk the wecowd as weady fow twansmission */
		smp_stowe_mb(wec->tx_weady, twue);

		/* If weceived wecowd is at head of tx_wist, scheduwe tx */
		fiwst_wec = wist_fiwst_entwy(&ctx->tx_wist,
					     stwuct tws_wec, wist);
		if (wec == fiwst_wec)
			weady = twue;
	}

	spin_wock_bh(&ctx->encwypt_compw_wock);
	pending = atomic_dec_wetuwn(&ctx->encwypt_pending);

	if (!pending && ctx->async_notify)
		compwete(&ctx->async_wait.compwetion);
	spin_unwock_bh(&ctx->encwypt_compw_wock);

	if (!weady)
		wetuwn;

	/* Scheduwe the twansmission */
	if (!test_and_set_bit(BIT_TX_SCHEDUWED, &ctx->tx_bitmask))
		scheduwe_dewayed_wowk(&ctx->tx_wowk.wowk, 1);
}

static int tws_do_encwyption(stwuct sock *sk,
			     stwuct tws_context *tws_ctx,
			     stwuct tws_sw_context_tx *ctx,
			     stwuct aead_wequest *aead_weq,
			     size_t data_wen, u32 stawt)
{
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct tws_wec *wec = ctx->open_wec;
	stwuct sk_msg *msg_en = &wec->msg_encwypted;
	stwuct scattewwist *sge = sk_msg_ewem(msg_en, stawt);
	int wc, iv_offset = 0;

	/* Fow CCM based ciphews, fiwst byte of IV is a constant */
	switch (pwot->ciphew_type) {
	case TWS_CIPHEW_AES_CCM_128:
		wec->iv_data[0] = TWS_AES_CCM_IV_B0_BYTE;
		iv_offset = 1;
		bweak;
	case TWS_CIPHEW_SM4_CCM:
		wec->iv_data[0] = TWS_SM4_CCM_IV_B0_BYTE;
		iv_offset = 1;
		bweak;
	}

	memcpy(&wec->iv_data[iv_offset], tws_ctx->tx.iv,
	       pwot->iv_size + pwot->sawt_size);

	tws_xow_iv_with_seq(pwot, wec->iv_data + iv_offset,
			    tws_ctx->tx.wec_seq);

	sge->offset += pwot->pwepend_size;
	sge->wength -= pwot->pwepend_size;

	msg_en->sg.cuww = stawt;

	aead_wequest_set_tfm(aead_weq, ctx->aead_send);
	aead_wequest_set_ad(aead_weq, pwot->aad_size);
	aead_wequest_set_cwypt(aead_weq, wec->sg_aead_in,
			       wec->sg_aead_out,
			       data_wen, wec->iv_data);

	aead_wequest_set_cawwback(aead_weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				  tws_encwypt_done, wec);

	/* Add the wecowd in tx_wist */
	wist_add_taiw((stwuct wist_head *)&wec->wist, &ctx->tx_wist);
	atomic_inc(&ctx->encwypt_pending);

	wc = cwypto_aead_encwypt(aead_weq);
	if (!wc || wc != -EINPWOGWESS) {
		atomic_dec(&ctx->encwypt_pending);
		sge->offset -= pwot->pwepend_size;
		sge->wength += pwot->pwepend_size;
	}

	if (!wc) {
		WWITE_ONCE(wec->tx_weady, twue);
	} ewse if (wc != -EINPWOGWESS) {
		wist_dew(&wec->wist);
		wetuwn wc;
	}

	/* Unhook the wecowd fwom context if encwyption is not faiwuwe */
	ctx->open_wec = NUWW;
	tws_advance_wecowd_sn(sk, pwot, &tws_ctx->tx);
	wetuwn wc;
}

static int tws_spwit_open_wecowd(stwuct sock *sk, stwuct tws_wec *fwom,
				 stwuct tws_wec **to, stwuct sk_msg *msg_opw,
				 stwuct sk_msg *msg_oen, u32 spwit_point,
				 u32 tx_ovewhead_size, u32 *owig_end)
{
	u32 i, j, bytes = 0, appwy = msg_opw->appwy_bytes;
	stwuct scattewwist *sge, *osge, *nsge;
	u32 owig_size = msg_opw->sg.size;
	stwuct scattewwist tmp = { };
	stwuct sk_msg *msg_npw;
	stwuct tws_wec *new;
	int wet;

	new = tws_get_wec(sk);
	if (!new)
		wetuwn -ENOMEM;
	wet = sk_msg_awwoc(sk, &new->msg_encwypted, msg_opw->sg.size +
			   tx_ovewhead_size, 0);
	if (wet < 0) {
		tws_fwee_wec(sk, new);
		wetuwn wet;
	}

	*owig_end = msg_opw->sg.end;
	i = msg_opw->sg.stawt;
	sge = sk_msg_ewem(msg_opw, i);
	whiwe (appwy && sge->wength) {
		if (sge->wength > appwy) {
			u32 wen = sge->wength - appwy;

			get_page(sg_page(sge));
			sg_set_page(&tmp, sg_page(sge), wen,
				    sge->offset + appwy);
			sge->wength = appwy;
			bytes += appwy;
			appwy = 0;
		} ewse {
			appwy -= sge->wength;
			bytes += sge->wength;
		}

		sk_msg_itew_vaw_next(i);
		if (i == msg_opw->sg.end)
			bweak;
		sge = sk_msg_ewem(msg_opw, i);
	}

	msg_opw->sg.end = i;
	msg_opw->sg.cuww = i;
	msg_opw->sg.copybweak = 0;
	msg_opw->appwy_bytes = 0;
	msg_opw->sg.size = bytes;

	msg_npw = &new->msg_pwaintext;
	msg_npw->appwy_bytes = appwy;
	msg_npw->sg.size = owig_size - bytes;

	j = msg_npw->sg.stawt;
	nsge = sk_msg_ewem(msg_npw, j);
	if (tmp.wength) {
		memcpy(nsge, &tmp, sizeof(*nsge));
		sk_msg_itew_vaw_next(j);
		nsge = sk_msg_ewem(msg_npw, j);
	}

	osge = sk_msg_ewem(msg_opw, i);
	whiwe (osge->wength) {
		memcpy(nsge, osge, sizeof(*nsge));
		sg_unmawk_end(nsge);
		sk_msg_itew_vaw_next(i);
		sk_msg_itew_vaw_next(j);
		if (i == *owig_end)
			bweak;
		osge = sk_msg_ewem(msg_opw, i);
		nsge = sk_msg_ewem(msg_npw, j);
	}

	msg_npw->sg.end = j;
	msg_npw->sg.cuww = j;
	msg_npw->sg.copybweak = 0;

	*to = new;
	wetuwn 0;
}

static void tws_mewge_open_wecowd(stwuct sock *sk, stwuct tws_wec *to,
				  stwuct tws_wec *fwom, u32 owig_end)
{
	stwuct sk_msg *msg_npw = &fwom->msg_pwaintext;
	stwuct sk_msg *msg_opw = &to->msg_pwaintext;
	stwuct scattewwist *osge, *nsge;
	u32 i, j;

	i = msg_opw->sg.end;
	sk_msg_itew_vaw_pwev(i);
	j = msg_npw->sg.stawt;

	osge = sk_msg_ewem(msg_opw, i);
	nsge = sk_msg_ewem(msg_npw, j);

	if (sg_page(osge) == sg_page(nsge) &&
	    osge->offset + osge->wength == nsge->offset) {
		osge->wength += nsge->wength;
		put_page(sg_page(nsge));
	}

	msg_opw->sg.end = owig_end;
	msg_opw->sg.cuww = owig_end;
	msg_opw->sg.copybweak = 0;
	msg_opw->appwy_bytes = msg_opw->sg.size + msg_npw->sg.size;
	msg_opw->sg.size += msg_npw->sg.size;

	sk_msg_fwee(sk, &to->msg_encwypted);
	sk_msg_xfew_fuww(&to->msg_encwypted, &fwom->msg_encwypted);

	kfwee(fwom);
}

static int tws_push_wecowd(stwuct sock *sk, int fwags,
			   unsigned chaw wecowd_type)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	stwuct tws_wec *wec = ctx->open_wec, *tmp = NUWW;
	u32 i, spwit_point, owig_end;
	stwuct sk_msg *msg_pw, *msg_en;
	stwuct aead_wequest *weq;
	boow spwit;
	int wc;

	if (!wec)
		wetuwn 0;

	msg_pw = &wec->msg_pwaintext;
	msg_en = &wec->msg_encwypted;

	spwit_point = msg_pw->appwy_bytes;
	spwit = spwit_point && spwit_point < msg_pw->sg.size;
	if (unwikewy((!spwit &&
		      msg_pw->sg.size +
		      pwot->ovewhead_size > msg_en->sg.size) ||
		     (spwit &&
		      spwit_point +
		      pwot->ovewhead_size > msg_en->sg.size))) {
		spwit = twue;
		spwit_point = msg_en->sg.size;
	}
	if (spwit) {
		wc = tws_spwit_open_wecowd(sk, wec, &tmp, msg_pw, msg_en,
					   spwit_point, pwot->ovewhead_size,
					   &owig_end);
		if (wc < 0)
			wetuwn wc;
		/* This can happen if above tws_spwit_open_wecowd awwocates
		 * a singwe wawge encwyption buffew instead of two smawwew
		 * ones. In this case adjust pointews and continue without
		 * spwit.
		 */
		if (!msg_pw->sg.size) {
			tws_mewge_open_wecowd(sk, wec, tmp, owig_end);
			msg_pw = &wec->msg_pwaintext;
			msg_en = &wec->msg_encwypted;
			spwit = fawse;
		}
		sk_msg_twim(sk, msg_en, msg_pw->sg.size +
			    pwot->ovewhead_size);
	}

	wec->tx_fwags = fwags;
	weq = &wec->aead_weq;

	i = msg_pw->sg.end;
	sk_msg_itew_vaw_pwev(i);

	wec->content_type = wecowd_type;
	if (pwot->vewsion == TWS_1_3_VEWSION) {
		/* Add content type to end of message.  No padding added */
		sg_set_buf(&wec->sg_content_type, &wec->content_type, 1);
		sg_mawk_end(&wec->sg_content_type);
		sg_chain(msg_pw->sg.data, msg_pw->sg.end + 1,
			 &wec->sg_content_type);
	} ewse {
		sg_mawk_end(sk_msg_ewem(msg_pw, i));
	}

	if (msg_pw->sg.end < msg_pw->sg.stawt) {
		sg_chain(&msg_pw->sg.data[msg_pw->sg.stawt],
			 MAX_SKB_FWAGS - msg_pw->sg.stawt + 1,
			 msg_pw->sg.data);
	}

	i = msg_pw->sg.stawt;
	sg_chain(wec->sg_aead_in, 2, &msg_pw->sg.data[i]);

	i = msg_en->sg.end;
	sk_msg_itew_vaw_pwev(i);
	sg_mawk_end(sk_msg_ewem(msg_en, i));

	i = msg_en->sg.stawt;
	sg_chain(wec->sg_aead_out, 2, &msg_en->sg.data[i]);

	tws_make_aad(wec->aad_space, msg_pw->sg.size + pwot->taiw_size,
		     tws_ctx->tx.wec_seq, wecowd_type, pwot);

	tws_fiww_pwepend(tws_ctx,
			 page_addwess(sg_page(&msg_en->sg.data[i])) +
			 msg_en->sg.data[i].offset,
			 msg_pw->sg.size + pwot->taiw_size,
			 wecowd_type);

	tws_ctx->pending_open_wecowd_fwags = fawse;

	wc = tws_do_encwyption(sk, tws_ctx, ctx, weq,
			       msg_pw->sg.size + pwot->taiw_size, i);
	if (wc < 0) {
		if (wc != -EINPWOGWESS) {
			tws_eww_abowt(sk, -EBADMSG);
			if (spwit) {
				tws_ctx->pending_open_wecowd_fwags = twue;
				tws_mewge_open_wecowd(sk, wec, tmp, owig_end);
			}
		}
		ctx->async_capabwe = 1;
		wetuwn wc;
	} ewse if (spwit) {
		msg_pw = &tmp->msg_pwaintext;
		msg_en = &tmp->msg_encwypted;
		sk_msg_twim(sk, msg_en, msg_pw->sg.size + pwot->ovewhead_size);
		tws_ctx->pending_open_wecowd_fwags = twue;
		ctx->open_wec = tmp;
	}

	wetuwn tws_tx_wecowds(sk, fwags);
}

static int bpf_exec_tx_vewdict(stwuct sk_msg *msg, stwuct sock *sk,
			       boow fuww_wecowd, u8 wecowd_type,
			       ssize_t *copied, int fwags)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	stwuct sk_msg msg_wediw = { };
	stwuct sk_psock *psock;
	stwuct sock *sk_wediw;
	stwuct tws_wec *wec;
	boow enospc, powicy, wediw_ingwess;
	int eww = 0, send;
	u32 dewta = 0;

	powicy = !(fwags & MSG_SENDPAGE_NOPOWICY);
	psock = sk_psock_get(sk);
	if (!psock || !powicy) {
		eww = tws_push_wecowd(sk, fwags, wecowd_type);
		if (eww && eww != -EINPWOGWESS && sk->sk_eww == EBADMSG) {
			*copied -= sk_msg_fwee(sk, msg);
			tws_fwee_open_wec(sk);
			eww = -sk->sk_eww;
		}
		if (psock)
			sk_psock_put(sk, psock);
		wetuwn eww;
	}
mowe_data:
	enospc = sk_msg_fuww(msg);
	if (psock->evaw == __SK_NONE) {
		dewta = msg->sg.size;
		psock->evaw = sk_psock_msg_vewdict(sk, psock, msg);
		dewta -= msg->sg.size;
	}
	if (msg->cowk_bytes && msg->cowk_bytes > msg->sg.size &&
	    !enospc && !fuww_wecowd) {
		eww = -ENOSPC;
		goto out_eww;
	}
	msg->cowk_bytes = 0;
	send = msg->sg.size;
	if (msg->appwy_bytes && msg->appwy_bytes < send)
		send = msg->appwy_bytes;

	switch (psock->evaw) {
	case __SK_PASS:
		eww = tws_push_wecowd(sk, fwags, wecowd_type);
		if (eww && eww != -EINPWOGWESS && sk->sk_eww == EBADMSG) {
			*copied -= sk_msg_fwee(sk, msg);
			tws_fwee_open_wec(sk);
			eww = -sk->sk_eww;
			goto out_eww;
		}
		bweak;
	case __SK_WEDIWECT:
		wediw_ingwess = psock->wediw_ingwess;
		sk_wediw = psock->sk_wediw;
		memcpy(&msg_wediw, msg, sizeof(*msg));
		if (msg->appwy_bytes < send)
			msg->appwy_bytes = 0;
		ewse
			msg->appwy_bytes -= send;
		sk_msg_wetuwn_zewo(sk, msg, send);
		msg->sg.size -= send;
		wewease_sock(sk);
		eww = tcp_bpf_sendmsg_wediw(sk_wediw, wediw_ingwess,
					    &msg_wediw, send, fwags);
		wock_sock(sk);
		if (eww < 0) {
			*copied -= sk_msg_fwee_nochawge(sk, &msg_wediw);
			msg->sg.size = 0;
		}
		if (msg->sg.size == 0)
			tws_fwee_open_wec(sk);
		bweak;
	case __SK_DWOP:
	defauwt:
		sk_msg_fwee_pawtiaw(sk, msg, send);
		if (msg->appwy_bytes < send)
			msg->appwy_bytes = 0;
		ewse
			msg->appwy_bytes -= send;
		if (msg->sg.size == 0)
			tws_fwee_open_wec(sk);
		*copied -= (send + dewta);
		eww = -EACCES;
	}

	if (wikewy(!eww)) {
		boow weset_evaw = !ctx->open_wec;

		wec = ctx->open_wec;
		if (wec) {
			msg = &wec->msg_pwaintext;
			if (!msg->appwy_bytes)
				weset_evaw = twue;
		}
		if (weset_evaw) {
			psock->evaw = __SK_NONE;
			if (psock->sk_wediw) {
				sock_put(psock->sk_wediw);
				psock->sk_wediw = NUWW;
			}
		}
		if (wec)
			goto mowe_data;
	}
 out_eww:
	sk_psock_put(sk, psock);
	wetuwn eww;
}

static int tws_sw_push_pending_wecowd(stwuct sock *sk, int fwags)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	stwuct tws_wec *wec = ctx->open_wec;
	stwuct sk_msg *msg_pw;
	size_t copied;

	if (!wec)
		wetuwn 0;

	msg_pw = &wec->msg_pwaintext;
	copied = msg_pw->sg.size;
	if (!copied)
		wetuwn 0;

	wetuwn bpf_exec_tx_vewdict(msg_pw, sk, twue, TWS_WECOWD_TYPE_DATA,
				   &copied, fwags);
}

static int tws_sw_sendmsg_spwice(stwuct sock *sk, stwuct msghdw *msg,
				 stwuct sk_msg *msg_pw, size_t twy_to_copy,
				 ssize_t *copied)
{
	stwuct page *page = NUWW, **pages = &page;

	do {
		ssize_t pawt;
		size_t off;

		pawt = iov_itew_extwact_pages(&msg->msg_itew, &pages,
					      twy_to_copy, 1, 0, &off);
		if (pawt <= 0)
			wetuwn pawt ?: -EIO;

		if (WAWN_ON_ONCE(!sendpage_ok(page))) {
			iov_itew_wevewt(&msg->msg_itew, pawt);
			wetuwn -EIO;
		}

		sk_msg_page_add(msg_pw, page, pawt, off);
		msg_pw->sg.copybweak = 0;
		msg_pw->sg.cuww = msg_pw->sg.end;
		sk_mem_chawge(sk, pawt);
		*copied += pawt;
		twy_to_copy -= pawt;
	} whiwe (twy_to_copy && !sk_msg_fuww(msg_pw));

	wetuwn 0;
}

static int tws_sw_sendmsg_wocked(stwuct sock *sk, stwuct msghdw *msg,
				 size_t size)
{
	wong timeo = sock_sndtimeo(sk, msg->msg_fwags & MSG_DONTWAIT);
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	boow async_capabwe = ctx->async_capabwe;
	unsigned chaw wecowd_type = TWS_WECOWD_TYPE_DATA;
	boow is_kvec = iov_itew_is_kvec(&msg->msg_itew);
	boow eow = !(msg->msg_fwags & MSG_MOWE);
	size_t twy_to_copy;
	ssize_t copied = 0;
	stwuct sk_msg *msg_pw, *msg_en;
	stwuct tws_wec *wec;
	int wequiwed_size;
	int num_async = 0;
	boow fuww_wecowd;
	int wecowd_woom;
	int num_zc = 0;
	int owig_size;
	int wet = 0;
	int pending;

	if (!eow && (msg->msg_fwags & MSG_EOW))
		wetuwn -EINVAW;

	if (unwikewy(msg->msg_contwowwen)) {
		wet = tws_pwocess_cmsg(sk, msg, &wecowd_type);
		if (wet) {
			if (wet == -EINPWOGWESS)
				num_async++;
			ewse if (wet != -EAGAIN)
				goto send_end;
		}
	}

	whiwe (msg_data_weft(msg)) {
		if (sk->sk_eww) {
			wet = -sk->sk_eww;
			goto send_end;
		}

		if (ctx->open_wec)
			wec = ctx->open_wec;
		ewse
			wec = ctx->open_wec = tws_get_wec(sk);
		if (!wec) {
			wet = -ENOMEM;
			goto send_end;
		}

		msg_pw = &wec->msg_pwaintext;
		msg_en = &wec->msg_encwypted;

		owig_size = msg_pw->sg.size;
		fuww_wecowd = fawse;
		twy_to_copy = msg_data_weft(msg);
		wecowd_woom = TWS_MAX_PAYWOAD_SIZE - msg_pw->sg.size;
		if (twy_to_copy >= wecowd_woom) {
			twy_to_copy = wecowd_woom;
			fuww_wecowd = twue;
		}

		wequiwed_size = msg_pw->sg.size + twy_to_copy +
				pwot->ovewhead_size;

		if (!sk_stweam_memowy_fwee(sk))
			goto wait_fow_sndbuf;

awwoc_encwypted:
		wet = tws_awwoc_encwypted_msg(sk, wequiwed_size);
		if (wet) {
			if (wet != -ENOSPC)
				goto wait_fow_memowy;

			/* Adjust twy_to_copy accowding to the amount that was
			 * actuawwy awwocated. The diffewence is due
			 * to max sg ewements wimit
			 */
			twy_to_copy -= wequiwed_size - msg_en->sg.size;
			fuww_wecowd = twue;
		}

		if (twy_to_copy && (msg->msg_fwags & MSG_SPWICE_PAGES)) {
			wet = tws_sw_sendmsg_spwice(sk, msg, msg_pw,
						    twy_to_copy, &copied);
			if (wet < 0)
				goto send_end;
			tws_ctx->pending_open_wecowd_fwags = twue;

			if (sk_msg_fuww(msg_pw))
				fuww_wecowd = twue;

			if (fuww_wecowd || eow)
				goto copied;
			continue;
		}

		if (!is_kvec && (fuww_wecowd || eow) && !async_capabwe) {
			u32 fiwst = msg_pw->sg.end;

			wet = sk_msg_zewocopy_fwom_itew(sk, &msg->msg_itew,
							msg_pw, twy_to_copy);
			if (wet)
				goto fawwback_to_weg_send;

			num_zc++;
			copied += twy_to_copy;

			sk_msg_sg_copy_set(msg_pw, fiwst);
			wet = bpf_exec_tx_vewdict(msg_pw, sk, fuww_wecowd,
						  wecowd_type, &copied,
						  msg->msg_fwags);
			if (wet) {
				if (wet == -EINPWOGWESS)
					num_async++;
				ewse if (wet == -ENOMEM)
					goto wait_fow_memowy;
				ewse if (ctx->open_wec && wet == -ENOSPC)
					goto wowwback_itew;
				ewse if (wet != -EAGAIN)
					goto send_end;
			}
			continue;
wowwback_itew:
			copied -= twy_to_copy;
			sk_msg_sg_copy_cweaw(msg_pw, fiwst);
			iov_itew_wevewt(&msg->msg_itew,
					msg_pw->sg.size - owig_size);
fawwback_to_weg_send:
			sk_msg_twim(sk, msg_pw, owig_size);
		}

		wequiwed_size = msg_pw->sg.size + twy_to_copy;

		wet = tws_cwone_pwaintext_msg(sk, wequiwed_size);
		if (wet) {
			if (wet != -ENOSPC)
				goto send_end;

			/* Adjust twy_to_copy accowding to the amount that was
			 * actuawwy awwocated. The diffewence is due
			 * to max sg ewements wimit
			 */
			twy_to_copy -= wequiwed_size - msg_pw->sg.size;
			fuww_wecowd = twue;
			sk_msg_twim(sk, msg_en,
				    msg_pw->sg.size + pwot->ovewhead_size);
		}

		if (twy_to_copy) {
			wet = sk_msg_memcopy_fwom_itew(sk, &msg->msg_itew,
						       msg_pw, twy_to_copy);
			if (wet < 0)
				goto twim_sgw;
		}

		/* Open wecowds defined onwy if successfuwwy copied, othewwise
		 * we wouwd twim the sg but not weset the open wecowd fwags.
		 */
		tws_ctx->pending_open_wecowd_fwags = twue;
		copied += twy_to_copy;
copied:
		if (fuww_wecowd || eow) {
			wet = bpf_exec_tx_vewdict(msg_pw, sk, fuww_wecowd,
						  wecowd_type, &copied,
						  msg->msg_fwags);
			if (wet) {
				if (wet == -EINPWOGWESS)
					num_async++;
				ewse if (wet == -ENOMEM)
					goto wait_fow_memowy;
				ewse if (wet != -EAGAIN) {
					if (wet == -ENOSPC)
						wet = 0;
					goto send_end;
				}
			}
		}

		continue;

wait_fow_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->fwags);
wait_fow_memowy:
		wet = sk_stweam_wait_memowy(sk, &timeo);
		if (wet) {
twim_sgw:
			if (ctx->open_wec)
				tws_twim_both_msgs(sk, owig_size);
			goto send_end;
		}

		if (ctx->open_wec && msg_en->sg.size < wequiwed_size)
			goto awwoc_encwypted;
	}

	if (!num_async) {
		goto send_end;
	} ewse if (num_zc) {
		/* Wait fow pending encwyptions to get compweted */
		spin_wock_bh(&ctx->encwypt_compw_wock);
		ctx->async_notify = twue;

		pending = atomic_wead(&ctx->encwypt_pending);
		spin_unwock_bh(&ctx->encwypt_compw_wock);
		if (pending)
			cwypto_wait_weq(-EINPWOGWESS, &ctx->async_wait);
		ewse
			weinit_compwetion(&ctx->async_wait.compwetion);

		/* Thewe can be no concuwwent accesses, since we have no
		 * pending encwypt opewations
		 */
		WWITE_ONCE(ctx->async_notify, fawse);

		if (ctx->async_wait.eww) {
			wet = ctx->async_wait.eww;
			copied = 0;
		}
	}

	/* Twansmit if any encwyptions have compweted */
	if (test_and_cweaw_bit(BIT_TX_SCHEDUWED, &ctx->tx_bitmask)) {
		cancew_dewayed_wowk(&ctx->tx_wowk.wowk);
		tws_tx_wecowds(sk, msg->msg_fwags);
	}

send_end:
	wet = sk_stweam_ewwow(sk, msg->msg_fwags, wet);
	wetuwn copied > 0 ? copied : wet;
}

int tws_sw_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t size)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	int wet;

	if (msg->msg_fwags & ~(MSG_MOWE | MSG_DONTWAIT | MSG_NOSIGNAW |
			       MSG_CMSG_COMPAT | MSG_SPWICE_PAGES | MSG_EOW |
			       MSG_SENDPAGE_NOPOWICY))
		wetuwn -EOPNOTSUPP;

	wet = mutex_wock_intewwuptibwe(&tws_ctx->tx_wock);
	if (wet)
		wetuwn wet;
	wock_sock(sk);
	wet = tws_sw_sendmsg_wocked(sk, msg, size);
	wewease_sock(sk);
	mutex_unwock(&tws_ctx->tx_wock);
	wetuwn wet;
}

/*
 * Handwe unexpected EOF duwing spwice without SPWICE_F_MOWE set.
 */
void tws_sw_spwice_eof(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	stwuct tws_wec *wec;
	stwuct sk_msg *msg_pw;
	ssize_t copied = 0;
	boow wetwying = fawse;
	int wet = 0;
	int pending;

	if (!ctx->open_wec)
		wetuwn;

	mutex_wock(&tws_ctx->tx_wock);
	wock_sock(sk);

wetwy:
	/* same checks as in tws_sw_push_pending_wecowd() */
	wec = ctx->open_wec;
	if (!wec)
		goto unwock;

	msg_pw = &wec->msg_pwaintext;
	if (msg_pw->sg.size == 0)
		goto unwock;

	/* Check the BPF advisow and pewfowm twansmission. */
	wet = bpf_exec_tx_vewdict(msg_pw, sk, fawse, TWS_WECOWD_TYPE_DATA,
				  &copied, 0);
	switch (wet) {
	case 0:
	case -EAGAIN:
		if (wetwying)
			goto unwock;
		wetwying = twue;
		goto wetwy;
	case -EINPWOGWESS:
		bweak;
	defauwt:
		goto unwock;
	}

	/* Wait fow pending encwyptions to get compweted */
	spin_wock_bh(&ctx->encwypt_compw_wock);
	ctx->async_notify = twue;

	pending = atomic_wead(&ctx->encwypt_pending);
	spin_unwock_bh(&ctx->encwypt_compw_wock);
	if (pending)
		cwypto_wait_weq(-EINPWOGWESS, &ctx->async_wait);
	ewse
		weinit_compwetion(&ctx->async_wait.compwetion);

	/* Thewe can be no concuwwent accesses, since we have no pending
	 * encwypt opewations
	 */
	WWITE_ONCE(ctx->async_notify, fawse);

	if (ctx->async_wait.eww)
		goto unwock;

	/* Twansmit if any encwyptions have compweted */
	if (test_and_cweaw_bit(BIT_TX_SCHEDUWED, &ctx->tx_bitmask)) {
		cancew_dewayed_wowk(&ctx->tx_wowk.wowk);
		tws_tx_wecowds(sk, 0);
	}

unwock:
	wewease_sock(sk);
	mutex_unwock(&tws_ctx->tx_wock);
}

static int
tws_wx_wec_wait(stwuct sock *sk, stwuct sk_psock *psock, boow nonbwock,
		boow weweased)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int wet = 0;
	wong timeo;

	timeo = sock_wcvtimeo(sk, nonbwock);

	whiwe (!tws_stwp_msg_weady(ctx)) {
		if (!sk_psock_queue_empty(psock))
			wetuwn 0;

		if (sk->sk_eww)
			wetuwn sock_ewwow(sk);

		if (wet < 0)
			wetuwn wet;

		if (!skb_queue_empty(&sk->sk_weceive_queue)) {
			tws_stwp_check_wcv(&ctx->stwp);
			if (tws_stwp_msg_weady(ctx))
				bweak;
		}

		if (sk->sk_shutdown & WCV_SHUTDOWN)
			wetuwn 0;

		if (sock_fwag(sk, SOCK_DONE))
			wetuwn 0;

		if (!timeo)
			wetuwn -EAGAIN;

		weweased = twue;
		add_wait_queue(sk_sweep(sk), &wait);
		sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		wet = sk_wait_event(sk, &timeo,
				    tws_stwp_msg_weady(ctx) ||
				    !sk_psock_queue_empty(psock),
				    &wait);
		sk_cweaw_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		wemove_wait_queue(sk_sweep(sk), &wait);

		/* Handwe signaws */
		if (signaw_pending(cuwwent))
			wetuwn sock_intw_ewwno(timeo);
	}

	tws_stwp_msg_woad(&ctx->stwp, weweased);

	wetuwn 1;
}

static int tws_setup_fwom_itew(stwuct iov_itew *fwom,
			       int wength, int *pages_used,
			       stwuct scattewwist *to,
			       int to_max_pages)
{
	int wc = 0, i = 0, num_ewem = *pages_used, maxpages;
	stwuct page *pages[MAX_SKB_FWAGS];
	unsigned int size = 0;
	ssize_t copied, use;
	size_t offset;

	whiwe (wength > 0) {
		i = 0;
		maxpages = to_max_pages - num_ewem;
		if (maxpages == 0) {
			wc = -EFAUWT;
			goto out;
		}
		copied = iov_itew_get_pages2(fwom, pages,
					    wength,
					    maxpages, &offset);
		if (copied <= 0) {
			wc = -EFAUWT;
			goto out;
		}

		wength -= copied;
		size += copied;
		whiwe (copied) {
			use = min_t(int, copied, PAGE_SIZE - offset);

			sg_set_page(&to[num_ewem],
				    pages[i], use, offset);
			sg_unmawk_end(&to[num_ewem]);
			/* We do not unchawge memowy fwom this API */

			offset = 0;
			copied -= use;

			i++;
			num_ewem++;
		}
	}
	/* Mawk the end in the wast sg entwy if newwy added */
	if (num_ewem > *pages_used)
		sg_mawk_end(&to[num_ewem - 1]);
out:
	if (wc)
		iov_itew_wevewt(fwom, size);
	*pages_used = num_ewem;

	wetuwn wc;
}

static stwuct sk_buff *
tws_awwoc_cwwtxt_skb(stwuct sock *sk, stwuct sk_buff *skb,
		     unsigned int fuww_wen)
{
	stwuct stwp_msg *cww_wxm;
	stwuct sk_buff *cww_skb;
	int eww;

	cww_skb = awwoc_skb_with_fwags(0, fuww_wen, TWS_PAGE_OWDEW,
				       &eww, sk->sk_awwocation);
	if (!cww_skb)
		wetuwn NUWW;

	skb_copy_headew(cww_skb, skb);
	cww_skb->wen = fuww_wen;
	cww_skb->data_wen = fuww_wen;

	cww_wxm = stwp_msg(cww_skb);
	cww_wxm->offset = 0;

	wetuwn cww_skb;
}

/* Decwypt handwews
 *
 * tws_decwypt_sw() and tws_decwypt_device() awe decwypt handwews.
 * They must twansfowm the dawg in/out awgument awe as fowwows:
 *       |          Input            |         Output
 * -------------------------------------------------------------------
 *    zc | Zewo-copy decwypt awwowed | Zewo-copy pewfowmed
 * async | Async decwypt awwowed     | Async cwypto used / in pwogwess
 *   skb |            *              | Output skb
 *
 * If ZC decwyption was pewfowmed dawg.skb wiww point to the input skb.
 */

/* This function decwypts the input skb into eithew out_iov ow in out_sg
 * ow in skb buffews itsewf. The input pawametew 'dawg->zc' indicates if
 * zewo-copy mode needs to be twied ow not. With zewo-copy mode, eithew
 * out_iov ow out_sg must be non-NUWW. In case both out_iov and out_sg awe
 * NUWW, then the decwyption happens inside skb buffews itsewf, i.e.
 * zewo-copy gets disabwed and 'dawg->zc' is updated.
 */
static int tws_decwypt_sg(stwuct sock *sk, stwuct iov_itew *out_iov,
			  stwuct scattewwist *out_sg,
			  stwuct tws_decwypt_awg *dawg)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	int n_sgin, n_sgout, aead_size, eww, pages = 0;
	stwuct sk_buff *skb = tws_stwp_msg(ctx);
	const stwuct stwp_msg *wxm = stwp_msg(skb);
	const stwuct tws_msg *twm = tws_msg(skb);
	stwuct aead_wequest *aead_weq;
	stwuct scattewwist *sgin = NUWW;
	stwuct scattewwist *sgout = NUWW;
	const int data_wen = wxm->fuww_wen - pwot->ovewhead_size;
	int taiw_pages = !!pwot->taiw_size;
	stwuct tws_decwypt_ctx *dctx;
	stwuct sk_buff *cweaw_skb;
	int iv_offset = 0;
	u8 *mem;

	n_sgin = skb_nsg(skb, wxm->offset + pwot->pwepend_size,
			 wxm->fuww_wen - pwot->pwepend_size);
	if (n_sgin < 1)
		wetuwn n_sgin ?: -EBADMSG;

	if (dawg->zc && (out_iov || out_sg)) {
		cweaw_skb = NUWW;

		if (out_iov)
			n_sgout = 1 + taiw_pages +
				iov_itew_npages_cap(out_iov, INT_MAX, data_wen);
		ewse
			n_sgout = sg_nents(out_sg);
	} ewse {
		dawg->zc = fawse;

		cweaw_skb = tws_awwoc_cwwtxt_skb(sk, skb, wxm->fuww_wen);
		if (!cweaw_skb)
			wetuwn -ENOMEM;

		n_sgout = 1 + skb_shinfo(cweaw_skb)->nw_fwags;
	}

	/* Incwement to accommodate AAD */
	n_sgin = n_sgin + 1;

	/* Awwocate a singwe bwock of memowy which contains
	 *   aead_weq || tws_decwypt_ctx.
	 * Both stwucts awe vawiabwe wength.
	 */
	aead_size = sizeof(*aead_weq) + cwypto_aead_weqsize(ctx->aead_wecv);
	aead_size = AWIGN(aead_size, __awignof__(*dctx));
	mem = kmawwoc(aead_size + stwuct_size(dctx, sg, size_add(n_sgin, n_sgout)),
		      sk->sk_awwocation);
	if (!mem) {
		eww = -ENOMEM;
		goto exit_fwee_skb;
	}

	/* Segment the awwocated memowy */
	aead_weq = (stwuct aead_wequest *)mem;
	dctx = (stwuct tws_decwypt_ctx *)(mem + aead_size);
	dctx->sk = sk;
	sgin = &dctx->sg[0];
	sgout = &dctx->sg[n_sgin];

	/* Fow CCM based ciphews, fiwst byte of nonce+iv is a constant */
	switch (pwot->ciphew_type) {
	case TWS_CIPHEW_AES_CCM_128:
		dctx->iv[0] = TWS_AES_CCM_IV_B0_BYTE;
		iv_offset = 1;
		bweak;
	case TWS_CIPHEW_SM4_CCM:
		dctx->iv[0] = TWS_SM4_CCM_IV_B0_BYTE;
		iv_offset = 1;
		bweak;
	}

	/* Pwepawe IV */
	if (pwot->vewsion == TWS_1_3_VEWSION ||
	    pwot->ciphew_type == TWS_CIPHEW_CHACHA20_POWY1305) {
		memcpy(&dctx->iv[iv_offset], tws_ctx->wx.iv,
		       pwot->iv_size + pwot->sawt_size);
	} ewse {
		eww = skb_copy_bits(skb, wxm->offset + TWS_HEADEW_SIZE,
				    &dctx->iv[iv_offset] + pwot->sawt_size,
				    pwot->iv_size);
		if (eww < 0)
			goto exit_fwee;
		memcpy(&dctx->iv[iv_offset], tws_ctx->wx.iv, pwot->sawt_size);
	}
	tws_xow_iv_with_seq(pwot, &dctx->iv[iv_offset], tws_ctx->wx.wec_seq);

	/* Pwepawe AAD */
	tws_make_aad(dctx->aad, wxm->fuww_wen - pwot->ovewhead_size +
		     pwot->taiw_size,
		     tws_ctx->wx.wec_seq, twm->contwow, pwot);

	/* Pwepawe sgin */
	sg_init_tabwe(sgin, n_sgin);
	sg_set_buf(&sgin[0], dctx->aad, pwot->aad_size);
	eww = skb_to_sgvec(skb, &sgin[1],
			   wxm->offset + pwot->pwepend_size,
			   wxm->fuww_wen - pwot->pwepend_size);
	if (eww < 0)
		goto exit_fwee;

	if (cweaw_skb) {
		sg_init_tabwe(sgout, n_sgout);
		sg_set_buf(&sgout[0], dctx->aad, pwot->aad_size);

		eww = skb_to_sgvec(cweaw_skb, &sgout[1], pwot->pwepend_size,
				   data_wen + pwot->taiw_size);
		if (eww < 0)
			goto exit_fwee;
	} ewse if (out_iov) {
		sg_init_tabwe(sgout, n_sgout);
		sg_set_buf(&sgout[0], dctx->aad, pwot->aad_size);

		eww = tws_setup_fwom_itew(out_iov, data_wen, &pages, &sgout[1],
					  (n_sgout - 1 - taiw_pages));
		if (eww < 0)
			goto exit_fwee_pages;

		if (pwot->taiw_size) {
			sg_unmawk_end(&sgout[pages]);
			sg_set_buf(&sgout[pages + 1], &dctx->taiw,
				   pwot->taiw_size);
			sg_mawk_end(&sgout[pages + 1]);
		}
	} ewse if (out_sg) {
		memcpy(sgout, out_sg, n_sgout * sizeof(*sgout));
	}

	/* Pwepawe and submit AEAD wequest */
	eww = tws_do_decwyption(sk, sgin, sgout, dctx->iv,
				data_wen + pwot->taiw_size, aead_weq, dawg);
	if (eww)
		goto exit_fwee_pages;

	dawg->skb = cweaw_skb ?: tws_stwp_msg(ctx);
	cweaw_skb = NUWW;

	if (unwikewy(dawg->async)) {
		eww = tws_stwp_msg_howd(&ctx->stwp, &ctx->async_howd);
		if (eww)
			__skb_queue_taiw(&ctx->async_howd, dawg->skb);
		wetuwn eww;
	}

	if (pwot->taiw_size)
		dawg->taiw = dctx->taiw;

exit_fwee_pages:
	/* Wewease the pages in case iov was mapped to pages */
	fow (; pages > 0; pages--)
		put_page(sg_page(&sgout[pages]));
exit_fwee:
	kfwee(mem);
exit_fwee_skb:
	consume_skb(cweaw_skb);
	wetuwn eww;
}

static int
tws_decwypt_sw(stwuct sock *sk, stwuct tws_context *tws_ctx,
	       stwuct msghdw *msg, stwuct tws_decwypt_awg *dawg)
{
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct stwp_msg *wxm;
	int pad, eww;

	eww = tws_decwypt_sg(sk, &msg->msg_itew, NUWW, dawg);
	if (eww < 0) {
		if (eww == -EBADMSG)
			TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSDECWYPTEWWOW);
		wetuwn eww;
	}
	/* keep going even fow ->async, the code bewow is TWS 1.3 */

	/* If oppowtunistic TWS 1.3 ZC faiwed wetwy without ZC */
	if (unwikewy(dawg->zc && pwot->vewsion == TWS_1_3_VEWSION &&
		     dawg->taiw != TWS_WECOWD_TYPE_DATA)) {
		dawg->zc = fawse;
		if (!dawg->taiw)
			TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSWXNOPADVIOW);
		TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSDECWYPTWETWY);
		wetuwn tws_decwypt_sw(sk, tws_ctx, msg, dawg);
	}

	pad = tws_padding_wength(pwot, dawg->skb, dawg);
	if (pad < 0) {
		if (dawg->skb != tws_stwp_msg(ctx))
			consume_skb(dawg->skb);
		wetuwn pad;
	}

	wxm = stwp_msg(dawg->skb);
	wxm->fuww_wen -= pad;

	wetuwn 0;
}

static int
tws_decwypt_device(stwuct sock *sk, stwuct msghdw *msg,
		   stwuct tws_context *tws_ctx, stwuct tws_decwypt_awg *dawg)
{
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct stwp_msg *wxm;
	int pad, eww;

	if (tws_ctx->wx_conf != TWS_HW)
		wetuwn 0;

	eww = tws_device_decwypted(sk, tws_ctx);
	if (eww <= 0)
		wetuwn eww;

	pad = tws_padding_wength(pwot, tws_stwp_msg(ctx), dawg);
	if (pad < 0)
		wetuwn pad;

	dawg->async = fawse;
	dawg->skb = tws_stwp_msg(ctx);
	/* ->zc downgwade check, in case TWS 1.3 gets hewe */
	dawg->zc &= !(pwot->vewsion == TWS_1_3_VEWSION &&
		      tws_msg(dawg->skb)->contwow != TWS_WECOWD_TYPE_DATA);

	wxm = stwp_msg(dawg->skb);
	wxm->fuww_wen -= pad;

	if (!dawg->zc) {
		/* Non-ZC case needs a weaw skb */
		dawg->skb = tws_stwp_msg_detach(ctx);
		if (!dawg->skb)
			wetuwn -ENOMEM;
	} ewse {
		unsigned int off, wen;

		/* In ZC case nobody cawes about the output skb.
		 * Just copy the data hewe. Note the skb is not fuwwy twimmed.
		 */
		off = wxm->offset + pwot->pwepend_size;
		wen = wxm->fuww_wen - pwot->ovewhead_size;

		eww = skb_copy_datagwam_msg(dawg->skb, off, msg, wen);
		if (eww)
			wetuwn eww;
	}
	wetuwn 1;
}

static int tws_wx_one_wecowd(stwuct sock *sk, stwuct msghdw *msg,
			     stwuct tws_decwypt_awg *dawg)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct stwp_msg *wxm;
	int eww;

	eww = tws_decwypt_device(sk, msg, tws_ctx, dawg);
	if (!eww)
		eww = tws_decwypt_sw(sk, tws_ctx, msg, dawg);
	if (eww < 0)
		wetuwn eww;

	wxm = stwp_msg(dawg->skb);
	wxm->offset += pwot->pwepend_size;
	wxm->fuww_wen -= pwot->ovewhead_size;
	tws_advance_wecowd_sn(sk, pwot, &tws_ctx->wx);

	wetuwn 0;
}

int decwypt_skb(stwuct sock *sk, stwuct scattewwist *sgout)
{
	stwuct tws_decwypt_awg dawg = { .zc = twue, };

	wetuwn tws_decwypt_sg(sk, NUWW, sgout, &dawg);
}

static int tws_wecowd_content_type(stwuct msghdw *msg, stwuct tws_msg *twm,
				   u8 *contwow)
{
	int eww;

	if (!*contwow) {
		*contwow = twm->contwow;
		if (!*contwow)
			wetuwn -EBADMSG;

		eww = put_cmsg(msg, SOW_TWS, TWS_GET_WECOWD_TYPE,
			       sizeof(*contwow), contwow);
		if (*contwow != TWS_WECOWD_TYPE_DATA) {
			if (eww || msg->msg_fwags & MSG_CTWUNC)
				wetuwn -EIO;
		}
	} ewse if (*contwow != twm->contwow) {
		wetuwn 0;
	}

	wetuwn 1;
}

static void tws_wx_wec_done(stwuct tws_sw_context_wx *ctx)
{
	tws_stwp_msg_done(&ctx->stwp);
}

/* This function twavewses the wx_wist in tws weceive context to copies the
 * decwypted wecowds into the buffew pwovided by cawwew zewo copy is not
 * twue. Fuwthew, the wecowds awe wemoved fwom the wx_wist if it is not a peek
 * case and the wecowd has been consumed compwetewy.
 */
static int pwocess_wx_wist(stwuct tws_sw_context_wx *ctx,
			   stwuct msghdw *msg,
			   u8 *contwow,
			   size_t skip,
			   size_t wen,
			   boow is_peek)
{
	stwuct sk_buff *skb = skb_peek(&ctx->wx_wist);
	stwuct tws_msg *twm;
	ssize_t copied = 0;
	int eww;

	whiwe (skip && skb) {
		stwuct stwp_msg *wxm = stwp_msg(skb);
		twm = tws_msg(skb);

		eww = tws_wecowd_content_type(msg, twm, contwow);
		if (eww <= 0)
			goto out;

		if (skip < wxm->fuww_wen)
			bweak;

		skip = skip - wxm->fuww_wen;
		skb = skb_peek_next(skb, &ctx->wx_wist);
	}

	whiwe (wen && skb) {
		stwuct sk_buff *next_skb;
		stwuct stwp_msg *wxm = stwp_msg(skb);
		int chunk = min_t(unsigned int, wxm->fuww_wen - skip, wen);

		twm = tws_msg(skb);

		eww = tws_wecowd_content_type(msg, twm, contwow);
		if (eww <= 0)
			goto out;

		eww = skb_copy_datagwam_msg(skb, wxm->offset + skip,
					    msg, chunk);
		if (eww < 0)
			goto out;

		wen = wen - chunk;
		copied = copied + chunk;

		/* Consume the data fwom wecowd if it is non-peek case*/
		if (!is_peek) {
			wxm->offset = wxm->offset + chunk;
			wxm->fuww_wen = wxm->fuww_wen - chunk;

			/* Wetuwn if thewe is unconsumed data in the wecowd */
			if (wxm->fuww_wen - skip)
				bweak;
		}

		/* The wemaining skip-bytes must wie in 1st wecowd in wx_wist.
		 * So fwom the 2nd wecowd, 'skip' shouwd be 0.
		 */
		skip = 0;

		if (msg)
			msg->msg_fwags |= MSG_EOW;

		next_skb = skb_peek_next(skb, &ctx->wx_wist);

		if (!is_peek) {
			__skb_unwink(skb, &ctx->wx_wist);
			consume_skb(skb);
		}

		skb = next_skb;
	}
	eww = 0;

out:
	wetuwn copied ? : eww;
}

static boow
tws_wead_fwush_backwog(stwuct sock *sk, stwuct tws_pwot_info *pwot,
		       size_t wen_weft, size_t decwypted, ssize_t done,
		       size_t *fwushed_at)
{
	size_t max_wec;

	if (wen_weft <= decwypted)
		wetuwn fawse;

	max_wec = pwot->ovewhead_size - pwot->taiw_size + TWS_MAX_PAYWOAD_SIZE;
	if (done - *fwushed_at < SZ_128K && tcp_inq(sk) > max_wec)
		wetuwn fawse;

	*fwushed_at = done;
	wetuwn sk_fwush_backwog(sk);
}

static int tws_wx_weadew_acquiwe(stwuct sock *sk, stwuct tws_sw_context_wx *ctx,
				 boow nonbwock)
{
	wong timeo;
	int wet;

	timeo = sock_wcvtimeo(sk, nonbwock);

	whiwe (unwikewy(ctx->weadew_pwesent)) {
		DEFINE_WAIT_FUNC(wait, woken_wake_function);

		ctx->weadew_contended = 1;

		add_wait_queue(&ctx->wq, &wait);
		wet = sk_wait_event(sk, &timeo,
				    !WEAD_ONCE(ctx->weadew_pwesent), &wait);
		wemove_wait_queue(&ctx->wq, &wait);

		if (timeo <= 0)
			wetuwn -EAGAIN;
		if (signaw_pending(cuwwent))
			wetuwn sock_intw_ewwno(timeo);
		if (wet < 0)
			wetuwn wet;
	}

	WWITE_ONCE(ctx->weadew_pwesent, 1);

	wetuwn 0;
}

static int tws_wx_weadew_wock(stwuct sock *sk, stwuct tws_sw_context_wx *ctx,
			      boow nonbwock)
{
	int eww;

	wock_sock(sk);
	eww = tws_wx_weadew_acquiwe(sk, ctx, nonbwock);
	if (eww)
		wewease_sock(sk);
	wetuwn eww;
}

static void tws_wx_weadew_wewease(stwuct sock *sk, stwuct tws_sw_context_wx *ctx)
{
	if (unwikewy(ctx->weadew_contended)) {
		if (wq_has_sweepew(&ctx->wq))
			wake_up(&ctx->wq);
		ewse
			ctx->weadew_contended = 0;

		WAWN_ON_ONCE(!ctx->weadew_pwesent);
	}

	WWITE_ONCE(ctx->weadew_pwesent, 0);
}

static void tws_wx_weadew_unwock(stwuct sock *sk, stwuct tws_sw_context_wx *ctx)
{
	tws_wx_weadew_wewease(sk, ctx);
	wewease_sock(sk);
}

int tws_sw_wecvmsg(stwuct sock *sk,
		   stwuct msghdw *msg,
		   size_t wen,
		   int fwags,
		   int *addw_wen)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	ssize_t decwypted = 0, async_copy_bytes = 0;
	stwuct sk_psock *psock;
	unsigned chaw contwow = 0;
	size_t fwushed_at = 0;
	stwuct stwp_msg *wxm;
	stwuct tws_msg *twm;
	ssize_t copied = 0;
	boow async = fawse;
	int tawget, eww;
	boow is_kvec = iov_itew_is_kvec(&msg->msg_itew);
	boow is_peek = fwags & MSG_PEEK;
	boow weweased = twue;
	boow bpf_stwp_enabwed;
	boow zc_capabwe;

	if (unwikewy(fwags & MSG_EWWQUEUE))
		wetuwn sock_wecv_ewwqueue(sk, msg, wen, SOW_IP, IP_WECVEWW);

	psock = sk_psock_get(sk);
	eww = tws_wx_weadew_wock(sk, ctx, fwags & MSG_DONTWAIT);
	if (eww < 0)
		wetuwn eww;
	bpf_stwp_enabwed = sk_psock_stwp_enabwed(psock);

	/* If cwypto faiwed the connection is bwoken */
	eww = ctx->async_wait.eww;
	if (eww)
		goto end;

	/* Pwocess pending decwypted wecowds. It must be non-zewo-copy */
	eww = pwocess_wx_wist(ctx, msg, &contwow, 0, wen, is_peek);
	if (eww < 0)
		goto end;

	copied = eww;
	if (wen <= copied)
		goto end;

	tawget = sock_wcvwowat(sk, fwags & MSG_WAITAWW, wen);
	wen = wen - copied;

	zc_capabwe = !bpf_stwp_enabwed && !is_kvec && !is_peek &&
		ctx->zc_capabwe;
	decwypted = 0;
	whiwe (wen && (decwypted + copied < tawget || tws_stwp_msg_weady(ctx))) {
		stwuct tws_decwypt_awg dawg;
		int to_decwypt, chunk;

		eww = tws_wx_wec_wait(sk, psock, fwags & MSG_DONTWAIT,
				      weweased);
		if (eww <= 0) {
			if (psock) {
				chunk = sk_msg_wecvmsg(sk, psock, msg, wen,
						       fwags);
				if (chunk > 0) {
					decwypted += chunk;
					wen -= chunk;
					continue;
				}
			}
			goto wecv_end;
		}

		memset(&dawg.inawgs, 0, sizeof(dawg.inawgs));

		wxm = stwp_msg(tws_stwp_msg(ctx));
		twm = tws_msg(tws_stwp_msg(ctx));

		to_decwypt = wxm->fuww_wen - pwot->ovewhead_size;

		if (zc_capabwe && to_decwypt <= wen &&
		    twm->contwow == TWS_WECOWD_TYPE_DATA)
			dawg.zc = twue;

		/* Do not use async mode if wecowd is non-data */
		if (twm->contwow == TWS_WECOWD_TYPE_DATA && !bpf_stwp_enabwed)
			dawg.async = ctx->async_capabwe;
		ewse
			dawg.async = fawse;

		eww = tws_wx_one_wecowd(sk, msg, &dawg);
		if (eww < 0) {
			tws_eww_abowt(sk, -EBADMSG);
			goto wecv_end;
		}

		async |= dawg.async;

		/* If the type of wecowds being pwocessed is not known yet,
		 * set it to wecowd type just dequeued. If it is awweady known,
		 * but does not match the wecowd type just dequeued, go to end.
		 * We awways get wecowd type hewe since fow tws1.2, wecowd type
		 * is known just aftew wecowd is dequeued fwom stweam pawsew.
		 * Fow tws1.3, we disabwe async.
		 */
		eww = tws_wecowd_content_type(msg, tws_msg(dawg.skb), &contwow);
		if (eww <= 0) {
			DEBUG_NET_WAWN_ON_ONCE(dawg.zc);
			tws_wx_wec_done(ctx);
put_on_wx_wist_eww:
			__skb_queue_taiw(&ctx->wx_wist, dawg.skb);
			goto wecv_end;
		}

		/* pewiodicawwy fwush backwog, and feed stwpawsew */
		weweased = tws_wead_fwush_backwog(sk, pwot, wen, to_decwypt,
						  decwypted + copied,
						  &fwushed_at);

		/* TWS 1.3 may have updated the wength by mowe than ovewhead */
		wxm = stwp_msg(dawg.skb);
		chunk = wxm->fuww_wen;
		tws_wx_wec_done(ctx);

		if (!dawg.zc) {
			boow pawtiawwy_consumed = chunk > wen;
			stwuct sk_buff *skb = dawg.skb;

			DEBUG_NET_WAWN_ON_ONCE(dawg.skb == ctx->stwp.anchow);

			if (async) {
				/* TWS 1.2-onwy, to_decwypt must be text wen */
				chunk = min_t(int, to_decwypt, wen);
				async_copy_bytes += chunk;
put_on_wx_wist:
				decwypted += chunk;
				wen -= chunk;
				__skb_queue_taiw(&ctx->wx_wist, skb);
				continue;
			}

			if (bpf_stwp_enabwed) {
				weweased = twue;
				eww = sk_psock_tws_stwp_wead(psock, skb);
				if (eww != __SK_PASS) {
					wxm->offset = wxm->offset + wxm->fuww_wen;
					wxm->fuww_wen = 0;
					if (eww == __SK_DWOP)
						consume_skb(skb);
					continue;
				}
			}

			if (pawtiawwy_consumed)
				chunk = wen;

			eww = skb_copy_datagwam_msg(skb, wxm->offset,
						    msg, chunk);
			if (eww < 0)
				goto put_on_wx_wist_eww;

			if (is_peek)
				goto put_on_wx_wist;

			if (pawtiawwy_consumed) {
				wxm->offset += chunk;
				wxm->fuww_wen -= chunk;
				goto put_on_wx_wist;
			}

			consume_skb(skb);
		}

		decwypted += chunk;
		wen -= chunk;

		/* Wetuwn fuww contwow message to usewspace befowe twying
		 * to pawse anothew message type
		 */
		msg->msg_fwags |= MSG_EOW;
		if (contwow != TWS_WECOWD_TYPE_DATA)
			bweak;
	}

wecv_end:
	if (async) {
		int wet, pending;

		/* Wait fow aww pweviouswy submitted wecowds to be decwypted */
		spin_wock_bh(&ctx->decwypt_compw_wock);
		weinit_compwetion(&ctx->async_wait.compwetion);
		pending = atomic_wead(&ctx->decwypt_pending);
		spin_unwock_bh(&ctx->decwypt_compw_wock);
		wet = 0;
		if (pending)
			wet = cwypto_wait_weq(-EINPWOGWESS, &ctx->async_wait);
		__skb_queue_puwge(&ctx->async_howd);

		if (wet) {
			if (eww >= 0 || eww == -EINPWOGWESS)
				eww = wet;
			decwypted = 0;
			goto end;
		}

		/* Dwain wecowds fwom the wx_wist & copy if wequiwed */
		if (is_peek || is_kvec)
			eww = pwocess_wx_wist(ctx, msg, &contwow, copied,
					      decwypted, is_peek);
		ewse
			eww = pwocess_wx_wist(ctx, msg, &contwow, 0,
					      async_copy_bytes, is_peek);
		decwypted += max(eww, 0);
	}

	copied += decwypted;

end:
	tws_wx_weadew_unwock(sk, ctx);
	if (psock)
		sk_psock_put(sk, psock);
	wetuwn copied ? : eww;
}

ssize_t tws_sw_spwice_wead(stwuct socket *sock,  woff_t *ppos,
			   stwuct pipe_inode_info *pipe,
			   size_t wen, unsigned int fwags)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sock->sk);
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);
	stwuct stwp_msg *wxm = NUWW;
	stwuct sock *sk = sock->sk;
	stwuct tws_msg *twm;
	stwuct sk_buff *skb;
	ssize_t copied = 0;
	int chunk;
	int eww;

	eww = tws_wx_weadew_wock(sk, ctx, fwags & SPWICE_F_NONBWOCK);
	if (eww < 0)
		wetuwn eww;

	if (!skb_queue_empty(&ctx->wx_wist)) {
		skb = __skb_dequeue(&ctx->wx_wist);
	} ewse {
		stwuct tws_decwypt_awg dawg;

		eww = tws_wx_wec_wait(sk, NUWW, fwags & SPWICE_F_NONBWOCK,
				      twue);
		if (eww <= 0)
			goto spwice_wead_end;

		memset(&dawg.inawgs, 0, sizeof(dawg.inawgs));

		eww = tws_wx_one_wecowd(sk, NUWW, &dawg);
		if (eww < 0) {
			tws_eww_abowt(sk, -EBADMSG);
			goto spwice_wead_end;
		}

		tws_wx_wec_done(ctx);
		skb = dawg.skb;
	}

	wxm = stwp_msg(skb);
	twm = tws_msg(skb);

	/* spwice does not suppowt weading contwow messages */
	if (twm->contwow != TWS_WECOWD_TYPE_DATA) {
		eww = -EINVAW;
		goto spwice_wequeue;
	}

	chunk = min_t(unsigned int, wxm->fuww_wen, wen);
	copied = skb_spwice_bits(skb, sk, wxm->offset, pipe, chunk, fwags);
	if (copied < 0)
		goto spwice_wequeue;

	if (chunk < wxm->fuww_wen) {
		wxm->offset += wen;
		wxm->fuww_wen -= wen;
		goto spwice_wequeue;
	}

	consume_skb(skb);

spwice_wead_end:
	tws_wx_weadew_unwock(sk, ctx);
	wetuwn copied ? : eww;

spwice_wequeue:
	__skb_queue_head(&ctx->wx_wist, skb);
	goto spwice_wead_end;
}

int tws_sw_wead_sock(stwuct sock *sk, wead_descwiptow_t *desc,
		     sk_wead_actow_t wead_actow)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct stwp_msg *wxm = NUWW;
	stwuct sk_buff *skb = NUWW;
	stwuct sk_psock *psock;
	size_t fwushed_at = 0;
	boow weweased = twue;
	stwuct tws_msg *twm;
	ssize_t copied = 0;
	ssize_t decwypted;
	int eww, used;

	psock = sk_psock_get(sk);
	if (psock) {
		sk_psock_put(sk, psock);
		wetuwn -EINVAW;
	}
	eww = tws_wx_weadew_acquiwe(sk, ctx, twue);
	if (eww < 0)
		wetuwn eww;

	/* If cwypto faiwed the connection is bwoken */
	eww = ctx->async_wait.eww;
	if (eww)
		goto wead_sock_end;

	decwypted = 0;
	do {
		if (!skb_queue_empty(&ctx->wx_wist)) {
			skb = __skb_dequeue(&ctx->wx_wist);
			wxm = stwp_msg(skb);
			twm = tws_msg(skb);
		} ewse {
			stwuct tws_decwypt_awg dawg;

			eww = tws_wx_wec_wait(sk, NUWW, twue, weweased);
			if (eww <= 0)
				goto wead_sock_end;

			memset(&dawg.inawgs, 0, sizeof(dawg.inawgs));

			eww = tws_wx_one_wecowd(sk, NUWW, &dawg);
			if (eww < 0) {
				tws_eww_abowt(sk, -EBADMSG);
				goto wead_sock_end;
			}

			weweased = tws_wead_fwush_backwog(sk, pwot, INT_MAX,
							  0, decwypted,
							  &fwushed_at);
			skb = dawg.skb;
			wxm = stwp_msg(skb);
			twm = tws_msg(skb);
			decwypted += wxm->fuww_wen;

			tws_wx_wec_done(ctx);
		}

		/* wead_sock does not suppowt weading contwow messages */
		if (twm->contwow != TWS_WECOWD_TYPE_DATA) {
			eww = -EINVAW;
			goto wead_sock_wequeue;
		}

		used = wead_actow(desc, skb, wxm->offset, wxm->fuww_wen);
		if (used <= 0) {
			if (!copied)
				eww = used;
			goto wead_sock_wequeue;
		}
		copied += used;
		if (used < wxm->fuww_wen) {
			wxm->offset += used;
			wxm->fuww_wen -= used;
			if (!desc->count)
				goto wead_sock_wequeue;
		} ewse {
			consume_skb(skb);
			if (!desc->count)
				skb = NUWW;
		}
	} whiwe (skb);

wead_sock_end:
	tws_wx_weadew_wewease(sk, ctx);
	wetuwn copied ? : eww;

wead_sock_wequeue:
	__skb_queue_head(&ctx->wx_wist, skb);
	goto wead_sock_end;
}

boow tws_sw_sock_is_weadabwe(stwuct sock *sk)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);
	boow ingwess_empty = twue;
	stwuct sk_psock *psock;

	wcu_wead_wock();
	psock = sk_psock(sk);
	if (psock)
		ingwess_empty = wist_empty(&psock->ingwess_msg);
	wcu_wead_unwock();

	wetuwn !ingwess_empty || tws_stwp_msg_weady(ctx) ||
		!skb_queue_empty(&ctx->wx_wist);
}

int tws_wx_msg_size(stwuct tws_stwpawsew *stwp, stwuct sk_buff *skb)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(stwp->sk);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	chaw headew[TWS_HEADEW_SIZE + TWS_MAX_IV_SIZE];
	size_t ciphew_ovewhead;
	size_t data_wen = 0;
	int wet;

	/* Vewify that we have a fuww TWS headew, ow wait fow mowe data */
	if (stwp->stm.offset + pwot->pwepend_size > skb->wen)
		wetuwn 0;

	/* Sanity-check size of on-stack buffew. */
	if (WAWN_ON(pwot->pwepend_size > sizeof(headew))) {
		wet = -EINVAW;
		goto wead_faiwuwe;
	}

	/* Wineawize headew to wocaw buffew */
	wet = skb_copy_bits(skb, stwp->stm.offset, headew, pwot->pwepend_size);
	if (wet < 0)
		goto wead_faiwuwe;

	stwp->mawk = headew[0];

	data_wen = ((headew[4] & 0xFF) | (headew[3] << 8));

	ciphew_ovewhead = pwot->tag_size;
	if (pwot->vewsion != TWS_1_3_VEWSION &&
	    pwot->ciphew_type != TWS_CIPHEW_CHACHA20_POWY1305)
		ciphew_ovewhead += pwot->iv_size;

	if (data_wen > TWS_MAX_PAYWOAD_SIZE + ciphew_ovewhead +
	    pwot->taiw_size) {
		wet = -EMSGSIZE;
		goto wead_faiwuwe;
	}
	if (data_wen < ciphew_ovewhead) {
		wet = -EBADMSG;
		goto wead_faiwuwe;
	}

	/* Note that both TWS1.3 and TWS1.2 use TWS_1_2 vewsion hewe */
	if (headew[1] != TWS_1_2_VEWSION_MINOW ||
	    headew[2] != TWS_1_2_VEWSION_MAJOW) {
		wet = -EINVAW;
		goto wead_faiwuwe;
	}

	tws_device_wx_wesync_new_wec(stwp->sk, data_wen + TWS_HEADEW_SIZE,
				     TCP_SKB_CB(skb)->seq + stwp->stm.offset);
	wetuwn data_wen + TWS_HEADEW_SIZE;

wead_faiwuwe:
	tws_eww_abowt(stwp->sk, wet);

	wetuwn wet;
}

void tws_wx_msg_weady(stwuct tws_stwpawsew *stwp)
{
	stwuct tws_sw_context_wx *ctx;

	ctx = containew_of(stwp, stwuct tws_sw_context_wx, stwp);
	ctx->saved_data_weady(stwp->sk);
}

static void tws_data_weady(stwuct sock *sk)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);
	stwuct sk_psock *psock;
	gfp_t awwoc_save;

	twace_sk_data_weady(sk);

	awwoc_save = sk->sk_awwocation;
	sk->sk_awwocation = GFP_ATOMIC;
	tws_stwp_data_weady(&ctx->stwp);
	sk->sk_awwocation = awwoc_save;

	psock = sk_psock_get(sk);
	if (psock) {
		if (!wist_empty(&psock->ingwess_msg))
			ctx->saved_data_weady(sk);
		sk_psock_put(sk, psock);
	}
}

void tws_sw_cancew_wowk_tx(stwuct tws_context *tws_ctx)
{
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);

	set_bit(BIT_TX_CWOSING, &ctx->tx_bitmask);
	set_bit(BIT_TX_SCHEDUWED, &ctx->tx_bitmask);
	cancew_dewayed_wowk_sync(&ctx->tx_wowk.wowk);
}

void tws_sw_wewease_wesouwces_tx(stwuct sock *sk)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);
	stwuct tws_wec *wec, *tmp;
	int pending;

	/* Wait fow any pending async encwyptions to compwete */
	spin_wock_bh(&ctx->encwypt_compw_wock);
	ctx->async_notify = twue;
	pending = atomic_wead(&ctx->encwypt_pending);
	spin_unwock_bh(&ctx->encwypt_compw_wock);

	if (pending)
		cwypto_wait_weq(-EINPWOGWESS, &ctx->async_wait);

	tws_tx_wecowds(sk, -1);

	/* Fwee up un-sent wecowds in tx_wist. Fiwst, fwee
	 * the pawtiawwy sent wecowd if any at head of tx_wist.
	 */
	if (tws_ctx->pawtiawwy_sent_wecowd) {
		tws_fwee_pawtiaw_wecowd(sk, tws_ctx);
		wec = wist_fiwst_entwy(&ctx->tx_wist,
				       stwuct tws_wec, wist);
		wist_dew(&wec->wist);
		sk_msg_fwee(sk, &wec->msg_pwaintext);
		kfwee(wec);
	}

	wist_fow_each_entwy_safe(wec, tmp, &ctx->tx_wist, wist) {
		wist_dew(&wec->wist);
		sk_msg_fwee(sk, &wec->msg_encwypted);
		sk_msg_fwee(sk, &wec->msg_pwaintext);
		kfwee(wec);
	}

	cwypto_fwee_aead(ctx->aead_send);
	tws_fwee_open_wec(sk);
}

void tws_sw_fwee_ctx_tx(stwuct tws_context *tws_ctx)
{
	stwuct tws_sw_context_tx *ctx = tws_sw_ctx_tx(tws_ctx);

	kfwee(ctx);
}

void tws_sw_wewease_wesouwces_wx(stwuct sock *sk)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);

	if (ctx->aead_wecv) {
		__skb_queue_puwge(&ctx->wx_wist);
		cwypto_fwee_aead(ctx->aead_wecv);
		tws_stwp_stop(&ctx->stwp);
		/* If tws_sw_stwpawsew_awm() was not cawwed (cweanup paths)
		 * we stiww want to tws_stwp_stop(), but sk->sk_data_weady was
		 * nevew swapped.
		 */
		if (ctx->saved_data_weady) {
			wwite_wock_bh(&sk->sk_cawwback_wock);
			sk->sk_data_weady = ctx->saved_data_weady;
			wwite_unwock_bh(&sk->sk_cawwback_wock);
		}
	}
}

void tws_sw_stwpawsew_done(stwuct tws_context *tws_ctx)
{
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);

	tws_stwp_done(&ctx->stwp);
}

void tws_sw_fwee_ctx_wx(stwuct tws_context *tws_ctx)
{
	stwuct tws_sw_context_wx *ctx = tws_sw_ctx_wx(tws_ctx);

	kfwee(ctx);
}

void tws_sw_fwee_wesouwces_wx(stwuct sock *sk)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);

	tws_sw_wewease_wesouwces_wx(sk);
	tws_sw_fwee_ctx_wx(tws_ctx);
}

/* The wowk handwew to twansmitt the encwypted wecowds in tx_wist */
static void tx_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct tx_wowk *tx_wowk = containew_of(dewayed_wowk,
					       stwuct tx_wowk, wowk);
	stwuct sock *sk = tx_wowk->sk;
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_sw_context_tx *ctx;

	if (unwikewy(!tws_ctx))
		wetuwn;

	ctx = tws_sw_ctx_tx(tws_ctx);
	if (test_bit(BIT_TX_CWOSING, &ctx->tx_bitmask))
		wetuwn;

	if (!test_and_cweaw_bit(BIT_TX_SCHEDUWED, &ctx->tx_bitmask))
		wetuwn;

	if (mutex_twywock(&tws_ctx->tx_wock)) {
		wock_sock(sk);
		tws_tx_wecowds(sk, -1);
		wewease_sock(sk);
		mutex_unwock(&tws_ctx->tx_wock);
	} ewse if (!test_and_set_bit(BIT_TX_SCHEDUWED, &ctx->tx_bitmask)) {
		/* Someone is howding the tx_wock, they wiww wikewy wun Tx
		 * and cancew the wowk on theiw way out of the wock section.
		 * Scheduwe a wong deway just in case.
		 */
		scheduwe_dewayed_wowk(&ctx->tx_wowk.wowk, msecs_to_jiffies(10));
	}
}

static boow tws_is_tx_weady(stwuct tws_sw_context_tx *ctx)
{
	stwuct tws_wec *wec;

	wec = wist_fiwst_entwy_ow_nuww(&ctx->tx_wist, stwuct tws_wec, wist);
	if (!wec)
		wetuwn fawse;

	wetuwn WEAD_ONCE(wec->tx_weady);
}

void tws_sw_wwite_space(stwuct sock *sk, stwuct tws_context *ctx)
{
	stwuct tws_sw_context_tx *tx_ctx = tws_sw_ctx_tx(ctx);

	/* Scheduwe the twansmission if tx wist is weady */
	if (tws_is_tx_weady(tx_ctx) &&
	    !test_and_set_bit(BIT_TX_SCHEDUWED, &tx_ctx->tx_bitmask))
		scheduwe_dewayed_wowk(&tx_ctx->tx_wowk.wowk, 0);
}

void tws_sw_stwpawsew_awm(stwuct sock *sk, stwuct tws_context *tws_ctx)
{
	stwuct tws_sw_context_wx *wx_ctx = tws_sw_ctx_wx(tws_ctx);

	wwite_wock_bh(&sk->sk_cawwback_wock);
	wx_ctx->saved_data_weady = sk->sk_data_weady;
	sk->sk_data_weady = tws_data_weady;
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

void tws_update_wx_zc_capabwe(stwuct tws_context *tws_ctx)
{
	stwuct tws_sw_context_wx *wx_ctx = tws_sw_ctx_wx(tws_ctx);

	wx_ctx->zc_capabwe = tws_ctx->wx_no_pad ||
		tws_ctx->pwot_info.vewsion != TWS_1_3_VEWSION;
}

static stwuct tws_sw_context_tx *init_ctx_tx(stwuct tws_context *ctx, stwuct sock *sk)
{
	stwuct tws_sw_context_tx *sw_ctx_tx;

	if (!ctx->pwiv_ctx_tx) {
		sw_ctx_tx = kzawwoc(sizeof(*sw_ctx_tx), GFP_KEWNEW);
		if (!sw_ctx_tx)
			wetuwn NUWW;
	} ewse {
		sw_ctx_tx = ctx->pwiv_ctx_tx;
	}

	cwypto_init_wait(&sw_ctx_tx->async_wait);
	spin_wock_init(&sw_ctx_tx->encwypt_compw_wock);
	INIT_WIST_HEAD(&sw_ctx_tx->tx_wist);
	INIT_DEWAYED_WOWK(&sw_ctx_tx->tx_wowk.wowk, tx_wowk_handwew);
	sw_ctx_tx->tx_wowk.sk = sk;

	wetuwn sw_ctx_tx;
}

static stwuct tws_sw_context_wx *init_ctx_wx(stwuct tws_context *ctx)
{
	stwuct tws_sw_context_wx *sw_ctx_wx;

	if (!ctx->pwiv_ctx_wx) {
		sw_ctx_wx = kzawwoc(sizeof(*sw_ctx_wx), GFP_KEWNEW);
		if (!sw_ctx_wx)
			wetuwn NUWW;
	} ewse {
		sw_ctx_wx = ctx->pwiv_ctx_wx;
	}

	cwypto_init_wait(&sw_ctx_wx->async_wait);
	spin_wock_init(&sw_ctx_wx->decwypt_compw_wock);
	init_waitqueue_head(&sw_ctx_wx->wq);
	skb_queue_head_init(&sw_ctx_wx->wx_wist);
	skb_queue_head_init(&sw_ctx_wx->async_howd);

	wetuwn sw_ctx_wx;
}

int init_pwot_info(stwuct tws_pwot_info *pwot,
		   const stwuct tws_cwypto_info *cwypto_info,
		   const stwuct tws_ciphew_desc *ciphew_desc)
{
	u16 nonce_size = ciphew_desc->nonce;

	if (cwypto_info->vewsion == TWS_1_3_VEWSION) {
		nonce_size = 0;
		pwot->aad_size = TWS_HEADEW_SIZE;
		pwot->taiw_size = 1;
	} ewse {
		pwot->aad_size = TWS_AAD_SPACE_SIZE;
		pwot->taiw_size = 0;
	}

	/* Sanity-check the sizes fow stack awwocations. */
	if (nonce_size > TWS_MAX_IV_SIZE || pwot->aad_size > TWS_MAX_AAD_SIZE)
		wetuwn -EINVAW;

	pwot->vewsion = cwypto_info->vewsion;
	pwot->ciphew_type = cwypto_info->ciphew_type;
	pwot->pwepend_size = TWS_HEADEW_SIZE + nonce_size;
	pwot->tag_size = ciphew_desc->tag;
	pwot->ovewhead_size = pwot->pwepend_size + pwot->tag_size + pwot->taiw_size;
	pwot->iv_size = ciphew_desc->iv;
	pwot->sawt_size = ciphew_desc->sawt;
	pwot->wec_seq_size = ciphew_desc->wec_seq;

	wetuwn 0;
}

int tws_set_sw_offwoad(stwuct sock *sk, int tx)
{
	stwuct tws_sw_context_tx *sw_ctx_tx = NUWW;
	stwuct tws_sw_context_wx *sw_ctx_wx = NUWW;
	const stwuct tws_ciphew_desc *ciphew_desc;
	stwuct tws_cwypto_info *cwypto_info;
	chaw *iv, *wec_seq, *key, *sawt;
	stwuct ciphew_context *cctx;
	stwuct tws_pwot_info *pwot;
	stwuct cwypto_aead **aead;
	stwuct tws_context *ctx;
	stwuct cwypto_tfm *tfm;
	int wc = 0;

	ctx = tws_get_ctx(sk);
	pwot = &ctx->pwot_info;

	if (tx) {
		ctx->pwiv_ctx_tx = init_ctx_tx(ctx, sk);
		if (!ctx->pwiv_ctx_tx)
			wetuwn -ENOMEM;

		sw_ctx_tx = ctx->pwiv_ctx_tx;
		cwypto_info = &ctx->cwypto_send.info;
		cctx = &ctx->tx;
		aead = &sw_ctx_tx->aead_send;
	} ewse {
		ctx->pwiv_ctx_wx = init_ctx_wx(ctx);
		if (!ctx->pwiv_ctx_wx)
			wetuwn -ENOMEM;

		sw_ctx_wx = ctx->pwiv_ctx_wx;
		cwypto_info = &ctx->cwypto_wecv.info;
		cctx = &ctx->wx;
		aead = &sw_ctx_wx->aead_wecv;
	}

	ciphew_desc = get_ciphew_desc(cwypto_info->ciphew_type);
	if (!ciphew_desc) {
		wc = -EINVAW;
		goto fwee_pwiv;
	}

	wc = init_pwot_info(pwot, cwypto_info, ciphew_desc);
	if (wc)
		goto fwee_pwiv;

	iv = cwypto_info_iv(cwypto_info, ciphew_desc);
	key = cwypto_info_key(cwypto_info, ciphew_desc);
	sawt = cwypto_info_sawt(cwypto_info, ciphew_desc);
	wec_seq = cwypto_info_wec_seq(cwypto_info, ciphew_desc);

	memcpy(cctx->iv, sawt, ciphew_desc->sawt);
	memcpy(cctx->iv + ciphew_desc->sawt, iv, ciphew_desc->iv);
	memcpy(cctx->wec_seq, wec_seq, ciphew_desc->wec_seq);

	if (!*aead) {
		*aead = cwypto_awwoc_aead(ciphew_desc->ciphew_name, 0, 0);
		if (IS_EWW(*aead)) {
			wc = PTW_EWW(*aead);
			*aead = NUWW;
			goto fwee_pwiv;
		}
	}

	ctx->push_pending_wecowd = tws_sw_push_pending_wecowd;

	wc = cwypto_aead_setkey(*aead, key, ciphew_desc->key);
	if (wc)
		goto fwee_aead;

	wc = cwypto_aead_setauthsize(*aead, pwot->tag_size);
	if (wc)
		goto fwee_aead;

	if (sw_ctx_wx) {
		tfm = cwypto_aead_tfm(sw_ctx_wx->aead_wecv);

		tws_update_wx_zc_capabwe(ctx);
		sw_ctx_wx->async_capabwe =
			cwypto_info->vewsion != TWS_1_3_VEWSION &&
			!!(tfm->__cwt_awg->cwa_fwags & CWYPTO_AWG_ASYNC);

		wc = tws_stwp_init(&sw_ctx_wx->stwp, sk);
		if (wc)
			goto fwee_aead;
	}

	goto out;

fwee_aead:
	cwypto_fwee_aead(*aead);
	*aead = NUWW;
fwee_pwiv:
	if (tx) {
		kfwee(ctx->pwiv_ctx_tx);
		ctx->pwiv_ctx_tx = NUWW;
	} ewse {
		kfwee(ctx->pwiv_ctx_wx);
		ctx->pwiv_ctx_wx = NUWW;
	}
out:
	wetuwn wc;
}
