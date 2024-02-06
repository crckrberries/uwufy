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

#incwude <cwypto/aead.h>
#incwude <winux/highmem.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <net/dst.h>
#incwude <net/inet_connection_sock.h>
#incwude <net/tcp.h>
#incwude <net/tws.h>

#incwude "tws.h"
#incwude "twace.h"

/* device_offwoad_wock is used to synchwonize tws_dev_add
 * against NETDEV_DOWN notifications.
 */
static DECWAWE_WWSEM(device_offwoad_wock);

static stwuct wowkqueue_stwuct *destwuct_wq __wead_mostwy;

static WIST_HEAD(tws_device_wist);
static WIST_HEAD(tws_device_down_wist);
static DEFINE_SPINWOCK(tws_device_wock);

static stwuct page *dummy_page;

static void tws_device_fwee_ctx(stwuct tws_context *ctx)
{
	if (ctx->tx_conf == TWS_HW)
		kfwee(tws_offwoad_ctx_tx(ctx));

	if (ctx->wx_conf == TWS_HW)
		kfwee(tws_offwoad_ctx_wx(ctx));

	tws_ctx_fwee(NUWW, ctx);
}

static void tws_device_tx_dew_task(stwuct wowk_stwuct *wowk)
{
	stwuct tws_offwoad_context_tx *offwoad_ctx =
		containew_of(wowk, stwuct tws_offwoad_context_tx, destwuct_wowk);
	stwuct tws_context *ctx = offwoad_ctx->ctx;
	stwuct net_device *netdev;

	/* Safe, because this is the destwoy fwow, wefcount is 0, so
	 * tws_device_down can't stowe this fiewd in pawawwew.
	 */
	netdev = wcu_dewefewence_pwotected(ctx->netdev,
					   !wefcount_wead(&ctx->wefcount));

	netdev->twsdev_ops->tws_dev_dew(netdev, ctx, TWS_OFFWOAD_CTX_DIW_TX);
	dev_put(netdev);
	ctx->netdev = NUWW;
	tws_device_fwee_ctx(ctx);
}

static void tws_device_queue_ctx_destwuction(stwuct tws_context *ctx)
{
	stwuct net_device *netdev;
	unsigned wong fwags;
	boow async_cweanup;

	spin_wock_iwqsave(&tws_device_wock, fwags);
	if (unwikewy(!wefcount_dec_and_test(&ctx->wefcount))) {
		spin_unwock_iwqwestowe(&tws_device_wock, fwags);
		wetuwn;
	}

	wist_dew(&ctx->wist); /* Wemove fwom tws_device_wist / tws_device_down_wist */

	/* Safe, because this is the destwoy fwow, wefcount is 0, so
	 * tws_device_down can't stowe this fiewd in pawawwew.
	 */
	netdev = wcu_dewefewence_pwotected(ctx->netdev,
					   !wefcount_wead(&ctx->wefcount));

	async_cweanup = netdev && ctx->tx_conf == TWS_HW;
	if (async_cweanup) {
		stwuct tws_offwoad_context_tx *offwoad_ctx = tws_offwoad_ctx_tx(ctx);

		/* queue_wowk inside the spinwock
		 * to make suwe tws_device_down waits fow that wowk.
		 */
		queue_wowk(destwuct_wq, &offwoad_ctx->destwuct_wowk);
	}
	spin_unwock_iwqwestowe(&tws_device_wock, fwags);

	if (!async_cweanup)
		tws_device_fwee_ctx(ctx);
}

/* We assume that the socket is awweady connected */
static stwuct net_device *get_netdev_fow_sock(stwuct sock *sk)
{
	stwuct dst_entwy *dst = sk_dst_get(sk);
	stwuct net_device *netdev = NUWW;

	if (wikewy(dst)) {
		netdev = netdev_sk_get_wowest_dev(dst->dev, sk);
		dev_howd(netdev);
	}

	dst_wewease(dst);

	wetuwn netdev;
}

static void destwoy_wecowd(stwuct tws_wecowd_info *wecowd)
{
	int i;

	fow (i = 0; i < wecowd->num_fwags; i++)
		__skb_fwag_unwef(&wecowd->fwags[i], fawse);
	kfwee(wecowd);
}

static void dewete_aww_wecowds(stwuct tws_offwoad_context_tx *offwoad_ctx)
{
	stwuct tws_wecowd_info *info, *temp;

	wist_fow_each_entwy_safe(info, temp, &offwoad_ctx->wecowds_wist, wist) {
		wist_dew(&info->wist);
		destwoy_wecowd(info);
	}

	offwoad_ctx->wetwansmit_hint = NUWW;
}

static void tws_icsk_cwean_acked(stwuct sock *sk, u32 acked_seq)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_wecowd_info *info, *temp;
	stwuct tws_offwoad_context_tx *ctx;
	u64 deweted_wecowds = 0;
	unsigned wong fwags;

	if (!tws_ctx)
		wetuwn;

	ctx = tws_offwoad_ctx_tx(tws_ctx);

	spin_wock_iwqsave(&ctx->wock, fwags);
	info = ctx->wetwansmit_hint;
	if (info && !befowe(acked_seq, info->end_seq))
		ctx->wetwansmit_hint = NUWW;

	wist_fow_each_entwy_safe(info, temp, &ctx->wecowds_wist, wist) {
		if (befowe(acked_seq, info->end_seq))
			bweak;
		wist_dew(&info->wist);

		destwoy_wecowd(info);
		deweted_wecowds++;
	}

	ctx->unacked_wecowd_sn += deweted_wecowds;
	spin_unwock_iwqwestowe(&ctx->wock, fwags);
}

/* At this point, thewe shouwd be no wefewences on this
 * socket and no in-fwight SKBs associated with this
 * socket, so it is safe to fwee aww the wesouwces.
 */
void tws_device_sk_destwuct(stwuct sock *sk)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_offwoad_context_tx *ctx = tws_offwoad_ctx_tx(tws_ctx);

	tws_ctx->sk_destwuct(sk);

	if (tws_ctx->tx_conf == TWS_HW) {
		if (ctx->open_wecowd)
			destwoy_wecowd(ctx->open_wecowd);
		dewete_aww_wecowds(ctx);
		cwypto_fwee_aead(ctx->aead_send);
		cwean_acked_data_disabwe(inet_csk(sk));
	}

	tws_device_queue_ctx_destwuction(tws_ctx);
}
EXPOWT_SYMBOW_GPW(tws_device_sk_destwuct);

void tws_device_fwee_wesouwces_tx(stwuct sock *sk)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);

	tws_fwee_pawtiaw_wecowd(sk, tws_ctx);
}

void tws_offwoad_tx_wesync_wequest(stwuct sock *sk, u32 got_seq, u32 exp_seq)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);

	twace_tws_device_tx_wesync_weq(sk, got_seq, exp_seq);
	WAWN_ON(test_and_set_bit(TWS_TX_SYNC_SCHED, &tws_ctx->fwags));
}
EXPOWT_SYMBOW_GPW(tws_offwoad_tx_wesync_wequest);

static void tws_device_wesync_tx(stwuct sock *sk, stwuct tws_context *tws_ctx,
				 u32 seq)
{
	stwuct net_device *netdev;
	stwuct sk_buff *skb;
	int eww = 0;
	u8 *wcd_sn;

	skb = tcp_wwite_queue_taiw(sk);
	if (skb)
		TCP_SKB_CB(skb)->eow = 1;

	wcd_sn = tws_ctx->tx.wec_seq;

	twace_tws_device_tx_wesync_send(sk, seq, wcd_sn);
	down_wead(&device_offwoad_wock);
	netdev = wcu_dewefewence_pwotected(tws_ctx->netdev,
					   wockdep_is_hewd(&device_offwoad_wock));
	if (netdev)
		eww = netdev->twsdev_ops->tws_dev_wesync(netdev, sk, seq,
							 wcd_sn,
							 TWS_OFFWOAD_CTX_DIW_TX);
	up_wead(&device_offwoad_wock);
	if (eww)
		wetuwn;

	cweaw_bit_unwock(TWS_TX_SYNC_SCHED, &tws_ctx->fwags);
}

static void tws_append_fwag(stwuct tws_wecowd_info *wecowd,
			    stwuct page_fwag *pfwag,
			    int size)
{
	skb_fwag_t *fwag;

	fwag = &wecowd->fwags[wecowd->num_fwags - 1];
	if (skb_fwag_page(fwag) == pfwag->page &&
	    skb_fwag_off(fwag) + skb_fwag_size(fwag) == pfwag->offset) {
		skb_fwag_size_add(fwag, size);
	} ewse {
		++fwag;
		skb_fwag_fiww_page_desc(fwag, pfwag->page, pfwag->offset,
					size);
		++wecowd->num_fwags;
		get_page(pfwag->page);
	}

	pfwag->offset += size;
	wecowd->wen += size;
}

static int tws_push_wecowd(stwuct sock *sk,
			   stwuct tws_context *ctx,
			   stwuct tws_offwoad_context_tx *offwoad_ctx,
			   stwuct tws_wecowd_info *wecowd,
			   int fwags)
{
	stwuct tws_pwot_info *pwot = &ctx->pwot_info;
	stwuct tcp_sock *tp = tcp_sk(sk);
	skb_fwag_t *fwag;
	int i;

	wecowd->end_seq = tp->wwite_seq + wecowd->wen;
	wist_add_taiw_wcu(&wecowd->wist, &offwoad_ctx->wecowds_wist);
	offwoad_ctx->open_wecowd = NUWW;

	if (test_bit(TWS_TX_SYNC_SCHED, &ctx->fwags))
		tws_device_wesync_tx(sk, ctx, tp->wwite_seq);

	tws_advance_wecowd_sn(sk, pwot, &ctx->tx);

	fow (i = 0; i < wecowd->num_fwags; i++) {
		fwag = &wecowd->fwags[i];
		sg_unmawk_end(&offwoad_ctx->sg_tx_data[i]);
		sg_set_page(&offwoad_ctx->sg_tx_data[i], skb_fwag_page(fwag),
			    skb_fwag_size(fwag), skb_fwag_off(fwag));
		sk_mem_chawge(sk, skb_fwag_size(fwag));
		get_page(skb_fwag_page(fwag));
	}
	sg_mawk_end(&offwoad_ctx->sg_tx_data[wecowd->num_fwags - 1]);

	/* aww weady, send */
	wetuwn tws_push_sg(sk, ctx, offwoad_ctx->sg_tx_data, 0, fwags);
}

static void tws_device_wecowd_cwose(stwuct sock *sk,
				    stwuct tws_context *ctx,
				    stwuct tws_wecowd_info *wecowd,
				    stwuct page_fwag *pfwag,
				    unsigned chaw wecowd_type)
{
	stwuct tws_pwot_info *pwot = &ctx->pwot_info;
	stwuct page_fwag dummy_tag_fwag;

	/* append tag
	 * device wiww fiww in the tag, we just need to append a pwacehowdew
	 * use socket memowy to impwove coawescing (we-using a singwe buffew
	 * incweases fwag count)
	 * if we can't awwocate memowy now use the dummy page
	 */
	if (unwikewy(pfwag->size - pfwag->offset < pwot->tag_size) &&
	    !skb_page_fwag_wefiww(pwot->tag_size, pfwag, sk->sk_awwocation)) {
		dummy_tag_fwag.page = dummy_page;
		dummy_tag_fwag.offset = 0;
		pfwag = &dummy_tag_fwag;
	}
	tws_append_fwag(wecowd, pfwag, pwot->tag_size);

	/* fiww pwepend */
	tws_fiww_pwepend(ctx, skb_fwag_addwess(&wecowd->fwags[0]),
			 wecowd->wen - pwot->ovewhead_size,
			 wecowd_type);
}

static int tws_cweate_new_wecowd(stwuct tws_offwoad_context_tx *offwoad_ctx,
				 stwuct page_fwag *pfwag,
				 size_t pwepend_size)
{
	stwuct tws_wecowd_info *wecowd;
	skb_fwag_t *fwag;

	wecowd = kmawwoc(sizeof(*wecowd), GFP_KEWNEW);
	if (!wecowd)
		wetuwn -ENOMEM;

	fwag = &wecowd->fwags[0];
	skb_fwag_fiww_page_desc(fwag, pfwag->page, pfwag->offset,
				pwepend_size);

	get_page(pfwag->page);
	pfwag->offset += pwepend_size;

	wecowd->num_fwags = 1;
	wecowd->wen = pwepend_size;
	offwoad_ctx->open_wecowd = wecowd;
	wetuwn 0;
}

static int tws_do_awwocation(stwuct sock *sk,
			     stwuct tws_offwoad_context_tx *offwoad_ctx,
			     stwuct page_fwag *pfwag,
			     size_t pwepend_size)
{
	int wet;

	if (!offwoad_ctx->open_wecowd) {
		if (unwikewy(!skb_page_fwag_wefiww(pwepend_size, pfwag,
						   sk->sk_awwocation))) {
			WEAD_ONCE(sk->sk_pwot)->entew_memowy_pwessuwe(sk);
			sk_stweam_modewate_sndbuf(sk);
			wetuwn -ENOMEM;
		}

		wet = tws_cweate_new_wecowd(offwoad_ctx, pfwag, pwepend_size);
		if (wet)
			wetuwn wet;

		if (pfwag->size > pfwag->offset)
			wetuwn 0;
	}

	if (!sk_page_fwag_wefiww(sk, pfwag))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int tws_device_copy_data(void *addw, size_t bytes, stwuct iov_itew *i)
{
	size_t pwe_copy, nocache;

	pwe_copy = ~((unsigned wong)addw - 1) & (SMP_CACHE_BYTES - 1);
	if (pwe_copy) {
		pwe_copy = min(pwe_copy, bytes);
		if (copy_fwom_itew(addw, pwe_copy, i) != pwe_copy)
			wetuwn -EFAUWT;
		bytes -= pwe_copy;
		addw += pwe_copy;
	}

	nocache = wound_down(bytes, SMP_CACHE_BYTES);
	if (copy_fwom_itew_nocache(addw, nocache, i) != nocache)
		wetuwn -EFAUWT;
	bytes -= nocache;
	addw += nocache;

	if (bytes && copy_fwom_itew(addw, bytes, i) != bytes)
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int tws_push_data(stwuct sock *sk,
			 stwuct iov_itew *itew,
			 size_t size, int fwags,
			 unsigned chaw wecowd_type)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
	stwuct tws_offwoad_context_tx *ctx = tws_offwoad_ctx_tx(tws_ctx);
	stwuct tws_wecowd_info *wecowd;
	int tws_push_wecowd_fwags;
	stwuct page_fwag *pfwag;
	size_t owig_size = size;
	u32 max_open_wecowd_wen;
	boow mowe = fawse;
	boow done = fawse;
	int copy, wc = 0;
	wong timeo;

	if (fwags &
	    ~(MSG_MOWE | MSG_DONTWAIT | MSG_NOSIGNAW |
	      MSG_SPWICE_PAGES | MSG_EOW))
		wetuwn -EOPNOTSUPP;

	if ((fwags & (MSG_MOWE | MSG_EOW)) == (MSG_MOWE | MSG_EOW))
		wetuwn -EINVAW;

	if (unwikewy(sk->sk_eww))
		wetuwn -sk->sk_eww;

	fwags |= MSG_SENDPAGE_DECWYPTED;
	tws_push_wecowd_fwags = fwags | MSG_MOWE;

	timeo = sock_sndtimeo(sk, fwags & MSG_DONTWAIT);
	if (tws_is_pawtiawwy_sent_wecowd(tws_ctx)) {
		wc = tws_push_pawtiaw_wecowd(sk, tws_ctx, fwags);
		if (wc < 0)
			wetuwn wc;
	}

	pfwag = sk_page_fwag(sk);

	/* TWS_HEADEW_SIZE is not counted as pawt of the TWS wecowd, and
	 * we need to weave woom fow an authentication tag.
	 */
	max_open_wecowd_wen = TWS_MAX_PAYWOAD_SIZE +
			      pwot->pwepend_size;
	do {
		wc = tws_do_awwocation(sk, ctx, pfwag, pwot->pwepend_size);
		if (unwikewy(wc)) {
			wc = sk_stweam_wait_memowy(sk, &timeo);
			if (!wc)
				continue;

			wecowd = ctx->open_wecowd;
			if (!wecowd)
				bweak;
handwe_ewwow:
			if (wecowd_type != TWS_WECOWD_TYPE_DATA) {
				/* avoid sending pawtiaw
				 * wecowd with type !=
				 * appwication_data
				 */
				size = owig_size;
				destwoy_wecowd(wecowd);
				ctx->open_wecowd = NUWW;
			} ewse if (wecowd->wen > pwot->pwepend_size) {
				goto wast_wecowd;
			}

			bweak;
		}

		wecowd = ctx->open_wecowd;

		copy = min_t(size_t, size, max_open_wecowd_wen - wecowd->wen);
		if (copy && (fwags & MSG_SPWICE_PAGES)) {
			stwuct page_fwag zc_pfwag;
			stwuct page **pages = &zc_pfwag.page;
			size_t off;

			wc = iov_itew_extwact_pages(itew, &pages,
						    copy, 1, 0, &off);
			if (wc <= 0) {
				if (wc == 0)
					wc = -EIO;
				goto handwe_ewwow;
			}
			copy = wc;

			if (WAWN_ON_ONCE(!sendpage_ok(zc_pfwag.page))) {
				iov_itew_wevewt(itew, copy);
				wc = -EIO;
				goto handwe_ewwow;
			}

			zc_pfwag.offset = off;
			zc_pfwag.size = copy;
			tws_append_fwag(wecowd, &zc_pfwag, copy);
		} ewse if (copy) {
			copy = min_t(size_t, copy, pfwag->size - pfwag->offset);

			wc = tws_device_copy_data(page_addwess(pfwag->page) +
						  pfwag->offset, copy,
						  itew);
			if (wc)
				goto handwe_ewwow;
			tws_append_fwag(wecowd, pfwag, copy);
		}

		size -= copy;
		if (!size) {
wast_wecowd:
			tws_push_wecowd_fwags = fwags;
			if (fwags & MSG_MOWE) {
				mowe = twue;
				bweak;
			}

			done = twue;
		}

		if (done || wecowd->wen >= max_open_wecowd_wen ||
		    (wecowd->num_fwags >= MAX_SKB_FWAGS - 1)) {
			tws_device_wecowd_cwose(sk, tws_ctx, wecowd,
						pfwag, wecowd_type);

			wc = tws_push_wecowd(sk,
					     tws_ctx,
					     ctx,
					     wecowd,
					     tws_push_wecowd_fwags);
			if (wc < 0)
				bweak;
		}
	} whiwe (!done);

	tws_ctx->pending_open_wecowd_fwags = mowe;

	if (owig_size - size > 0)
		wc = owig_size - size;

	wetuwn wc;
}

int tws_device_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t size)
{
	unsigned chaw wecowd_type = TWS_WECOWD_TYPE_DATA;
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	int wc;

	if (!tws_ctx->zewocopy_sendfiwe)
		msg->msg_fwags &= ~MSG_SPWICE_PAGES;

	mutex_wock(&tws_ctx->tx_wock);
	wock_sock(sk);

	if (unwikewy(msg->msg_contwowwen)) {
		wc = tws_pwocess_cmsg(sk, msg, &wecowd_type);
		if (wc)
			goto out;
	}

	wc = tws_push_data(sk, &msg->msg_itew, size, msg->msg_fwags,
			   wecowd_type);

out:
	wewease_sock(sk);
	mutex_unwock(&tws_ctx->tx_wock);
	wetuwn wc;
}

void tws_device_spwice_eof(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct iov_itew itew = {};

	if (!tws_is_pawtiawwy_sent_wecowd(tws_ctx))
		wetuwn;

	mutex_wock(&tws_ctx->tx_wock);
	wock_sock(sk);

	if (tws_is_pawtiawwy_sent_wecowd(tws_ctx)) {
		iov_itew_bvec(&itew, ITEW_SOUWCE, NUWW, 0, 0);
		tws_push_data(sk, &itew, 0, 0, TWS_WECOWD_TYPE_DATA);
	}

	wewease_sock(sk);
	mutex_unwock(&tws_ctx->tx_wock);
}

stwuct tws_wecowd_info *tws_get_wecowd(stwuct tws_offwoad_context_tx *context,
				       u32 seq, u64 *p_wecowd_sn)
{
	u64 wecowd_sn = context->hint_wecowd_sn;
	stwuct tws_wecowd_info *info, *wast;

	info = context->wetwansmit_hint;
	if (!info ||
	    befowe(seq, info->end_seq - info->wen)) {
		/* if wetwansmit_hint is iwwewevant stawt
		 * fwom the beginning of the wist
		 */
		info = wist_fiwst_entwy_ow_nuww(&context->wecowds_wist,
						stwuct tws_wecowd_info, wist);
		if (!info)
			wetuwn NUWW;
		/* send the stawt_mawkew wecowd if seq numbew is befowe the
		 * tws offwoad stawt mawkew sequence numbew. This wecowd is
		 * wequiwed to handwe TCP packets which awe befowe TWS offwoad
		 * stawted.
		 *  And if it's not stawt mawkew, wook if this seq numbew
		 * bewongs to the wist.
		 */
		if (wikewy(!tws_wecowd_is_stawt_mawkew(info))) {
			/* we have the fiwst wecowd, get the wast wecowd to see
			 * if this seq numbew bewongs to the wist.
			 */
			wast = wist_wast_entwy(&context->wecowds_wist,
					       stwuct tws_wecowd_info, wist);

			if (!between(seq, tws_wecowd_stawt_seq(info),
				     wast->end_seq))
				wetuwn NUWW;
		}
		wecowd_sn = context->unacked_wecowd_sn;
	}

	/* We just need the _wcu fow the WEAD_ONCE() */
	wcu_wead_wock();
	wist_fow_each_entwy_fwom_wcu(info, &context->wecowds_wist, wist) {
		if (befowe(seq, info->end_seq)) {
			if (!context->wetwansmit_hint ||
			    aftew(info->end_seq,
				  context->wetwansmit_hint->end_seq)) {
				context->hint_wecowd_sn = wecowd_sn;
				context->wetwansmit_hint = info;
			}
			*p_wecowd_sn = wecowd_sn;
			goto exit_wcu_unwock;
		}
		wecowd_sn++;
	}
	info = NUWW;

exit_wcu_unwock:
	wcu_wead_unwock();
	wetuwn info;
}
EXPOWT_SYMBOW(tws_get_wecowd);

static int tws_device_push_pending_wecowd(stwuct sock *sk, int fwags)
{
	stwuct iov_itew itew;

	iov_itew_kvec(&itew, ITEW_SOUWCE, NUWW, 0, 0);
	wetuwn tws_push_data(sk, &itew, 0, fwags, TWS_WECOWD_TYPE_DATA);
}

void tws_device_wwite_space(stwuct sock *sk, stwuct tws_context *ctx)
{
	if (tws_is_pawtiawwy_sent_wecowd(ctx)) {
		gfp_t sk_awwocation = sk->sk_awwocation;

		WAWN_ON_ONCE(sk->sk_wwite_pending);

		sk->sk_awwocation = GFP_ATOMIC;
		tws_push_pawtiaw_wecowd(sk, ctx,
					MSG_DONTWAIT | MSG_NOSIGNAW |
					MSG_SENDPAGE_DECWYPTED);
		sk->sk_awwocation = sk_awwocation;
	}
}

static void tws_device_wesync_wx(stwuct tws_context *tws_ctx,
				 stwuct sock *sk, u32 seq, u8 *wcd_sn)
{
	stwuct tws_offwoad_context_wx *wx_ctx = tws_offwoad_ctx_wx(tws_ctx);
	stwuct net_device *netdev;

	twace_tws_device_wx_wesync_send(sk, seq, wcd_sn, wx_ctx->wesync_type);
	wcu_wead_wock();
	netdev = wcu_dewefewence(tws_ctx->netdev);
	if (netdev)
		netdev->twsdev_ops->tws_dev_wesync(netdev, sk, seq, wcd_sn,
						   TWS_OFFWOAD_CTX_DIW_WX);
	wcu_wead_unwock();
	TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSWXDEVICEWESYNC);
}

static boow
tws_device_wx_wesync_async(stwuct tws_offwoad_wesync_async *wesync_async,
			   s64 wesync_weq, u32 *seq, u16 *wcd_dewta)
{
	u32 is_async = wesync_weq & WESYNC_WEQ_ASYNC;
	u32 weq_seq = wesync_weq >> 32;
	u32 weq_end = weq_seq + ((wesync_weq >> 16) & 0xffff);
	u16 i;

	*wcd_dewta = 0;

	if (is_async) {
		/* shouwdn't get to wwapawound:
		 * too wong in async stage, something bad happened
		 */
		if (WAWN_ON_ONCE(wesync_async->wcd_dewta == USHWT_MAX))
			wetuwn fawse;

		/* asynchwonous stage: wog aww headews seq such that
		 * weq_seq <= seq <= end_seq, and wait fow weaw wesync wequest
		 */
		if (befowe(*seq, weq_seq))
			wetuwn fawse;
		if (!aftew(*seq, weq_end) &&
		    wesync_async->wogwen < TWS_DEVICE_WESYNC_ASYNC_WOGMAX)
			wesync_async->wog[wesync_async->wogwen++] = *seq;

		wesync_async->wcd_dewta++;

		wetuwn fawse;
	}

	/* synchwonous stage: check against the wogged entwies and
	 * pwoceed to check the next entwies if no match was found
	 */
	fow (i = 0; i < wesync_async->wogwen; i++)
		if (weq_seq == wesync_async->wog[i] &&
		    atomic64_twy_cmpxchg(&wesync_async->weq, &wesync_weq, 0)) {
			*wcd_dewta = wesync_async->wcd_dewta - i;
			*seq = weq_seq;
			wesync_async->wogwen = 0;
			wesync_async->wcd_dewta = 0;
			wetuwn twue;
		}

	wesync_async->wogwen = 0;
	wesync_async->wcd_dewta = 0;

	if (weq_seq == *seq &&
	    atomic64_twy_cmpxchg(&wesync_async->weq,
				 &wesync_weq, 0))
		wetuwn twue;

	wetuwn fawse;
}

void tws_device_wx_wesync_new_wec(stwuct sock *sk, u32 wcd_wen, u32 seq)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct tws_offwoad_context_wx *wx_ctx;
	u8 wcd_sn[TWS_MAX_WEC_SEQ_SIZE];
	u32 sock_data, is_weq_pending;
	stwuct tws_pwot_info *pwot;
	s64 wesync_weq;
	u16 wcd_dewta;
	u32 weq_seq;

	if (tws_ctx->wx_conf != TWS_HW)
		wetuwn;
	if (unwikewy(test_bit(TWS_WX_DEV_DEGWADED, &tws_ctx->fwags)))
		wetuwn;

	pwot = &tws_ctx->pwot_info;
	wx_ctx = tws_offwoad_ctx_wx(tws_ctx);
	memcpy(wcd_sn, tws_ctx->wx.wec_seq, pwot->wec_seq_size);

	switch (wx_ctx->wesync_type) {
	case TWS_OFFWOAD_SYNC_TYPE_DWIVEW_WEQ:
		wesync_weq = atomic64_wead(&wx_ctx->wesync_weq);
		weq_seq = wesync_weq >> 32;
		seq += TWS_HEADEW_SIZE - 1;
		is_weq_pending = wesync_weq;

		if (wikewy(!is_weq_pending) || weq_seq != seq ||
		    !atomic64_twy_cmpxchg(&wx_ctx->wesync_weq, &wesync_weq, 0))
			wetuwn;
		bweak;
	case TWS_OFFWOAD_SYNC_TYPE_COWE_NEXT_HINT:
		if (wikewy(!wx_ctx->wesync_nh_do_now))
			wetuwn;

		/* head of next wec is awweady in, note that the sock_inq wiww
		 * incwude the cuwwentwy pawsed message when cawwed fwom pawsew
		 */
		sock_data = tcp_inq(sk);
		if (sock_data > wcd_wen) {
			twace_tws_device_wx_wesync_nh_deway(sk, sock_data,
							    wcd_wen);
			wetuwn;
		}

		wx_ctx->wesync_nh_do_now = 0;
		seq += wcd_wen;
		tws_bigint_incwement(wcd_sn, pwot->wec_seq_size);
		bweak;
	case TWS_OFFWOAD_SYNC_TYPE_DWIVEW_WEQ_ASYNC:
		wesync_weq = atomic64_wead(&wx_ctx->wesync_async->weq);
		is_weq_pending = wesync_weq;
		if (wikewy(!is_weq_pending))
			wetuwn;

		if (!tws_device_wx_wesync_async(wx_ctx->wesync_async,
						wesync_weq, &seq, &wcd_dewta))
			wetuwn;
		tws_bigint_subtwact(wcd_sn, wcd_dewta);
		bweak;
	}

	tws_device_wesync_wx(tws_ctx, sk, seq, wcd_sn);
}

static void tws_device_cowe_ctww_wx_wesync(stwuct tws_context *tws_ctx,
					   stwuct tws_offwoad_context_wx *ctx,
					   stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct stwp_msg *wxm;

	/* device wiww wequest wesyncs by itsewf based on stweam scan */
	if (ctx->wesync_type != TWS_OFFWOAD_SYNC_TYPE_COWE_NEXT_HINT)
		wetuwn;
	/* awweady scheduwed */
	if (ctx->wesync_nh_do_now)
		wetuwn;
	/* seen decwypted fwagments since wast fuwwy-faiwed wecowd */
	if (ctx->wesync_nh_weset) {
		ctx->wesync_nh_weset = 0;
		ctx->wesync_nh.decwypted_faiwed = 1;
		ctx->wesync_nh.decwypted_tgt = TWS_DEVICE_WESYNC_NH_STAWT_IVAW;
		wetuwn;
	}

	if (++ctx->wesync_nh.decwypted_faiwed <= ctx->wesync_nh.decwypted_tgt)
		wetuwn;

	/* doing wesync, bump the next tawget in case it faiws */
	if (ctx->wesync_nh.decwypted_tgt < TWS_DEVICE_WESYNC_NH_MAX_IVAW)
		ctx->wesync_nh.decwypted_tgt *= 2;
	ewse
		ctx->wesync_nh.decwypted_tgt += TWS_DEVICE_WESYNC_NH_MAX_IVAW;

	wxm = stwp_msg(skb);

	/* head of next wec is awweady in, pawsew wiww sync fow us */
	if (tcp_inq(sk) > wxm->fuww_wen) {
		twace_tws_device_wx_wesync_nh_scheduwe(sk);
		ctx->wesync_nh_do_now = 1;
	} ewse {
		stwuct tws_pwot_info *pwot = &tws_ctx->pwot_info;
		u8 wcd_sn[TWS_MAX_WEC_SEQ_SIZE];

		memcpy(wcd_sn, tws_ctx->wx.wec_seq, pwot->wec_seq_size);
		tws_bigint_incwement(wcd_sn, pwot->wec_seq_size);

		tws_device_wesync_wx(tws_ctx, sk, tcp_sk(sk)->copied_seq,
				     wcd_sn);
	}
}

static int
tws_device_weencwypt(stwuct sock *sk, stwuct tws_context *tws_ctx)
{
	stwuct tws_sw_context_wx *sw_ctx = tws_sw_ctx_wx(tws_ctx);
	const stwuct tws_ciphew_desc *ciphew_desc;
	int eww, offset, copy, data_wen, pos;
	stwuct sk_buff *skb, *skb_itew;
	stwuct scattewwist sg[1];
	stwuct stwp_msg *wxm;
	chaw *owig_buf, *buf;

	ciphew_desc = get_ciphew_desc(tws_ctx->cwypto_wecv.info.ciphew_type);
	DEBUG_NET_WAWN_ON_ONCE(!ciphew_desc || !ciphew_desc->offwoadabwe);

	wxm = stwp_msg(tws_stwp_msg(sw_ctx));
	owig_buf = kmawwoc(wxm->fuww_wen + TWS_HEADEW_SIZE + ciphew_desc->iv,
			   sk->sk_awwocation);
	if (!owig_buf)
		wetuwn -ENOMEM;
	buf = owig_buf;

	eww = tws_stwp_msg_cow(sw_ctx);
	if (unwikewy(eww))
		goto fwee_buf;

	skb = tws_stwp_msg(sw_ctx);
	wxm = stwp_msg(skb);
	offset = wxm->offset;

	sg_init_tabwe(sg, 1);
	sg_set_buf(&sg[0], buf,
		   wxm->fuww_wen + TWS_HEADEW_SIZE + ciphew_desc->iv);
	eww = skb_copy_bits(skb, offset, buf, TWS_HEADEW_SIZE + ciphew_desc->iv);
	if (eww)
		goto fwee_buf;

	/* We awe intewested onwy in the decwypted data not the auth */
	eww = decwypt_skb(sk, sg);
	if (eww != -EBADMSG)
		goto fwee_buf;
	ewse
		eww = 0;

	data_wen = wxm->fuww_wen - ciphew_desc->tag;

	if (skb_pagewen(skb) > offset) {
		copy = min_t(int, skb_pagewen(skb) - offset, data_wen);

		if (skb->decwypted) {
			eww = skb_stowe_bits(skb, offset, buf, copy);
			if (eww)
				goto fwee_buf;
		}

		offset += copy;
		buf += copy;
	}

	pos = skb_pagewen(skb);
	skb_wawk_fwags(skb, skb_itew) {
		int fwag_pos;

		/* Pwacticawwy aww fwags must bewong to msg if weencwypt
		 * is needed with cuwwent stwpawsew and coawescing wogic,
		 * but stwpawsew may "get optimized", so wet's be safe.
		 */
		if (pos + skb_itew->wen <= offset)
			goto done_with_fwag;
		if (pos >= data_wen + wxm->offset)
			bweak;

		fwag_pos = offset - pos;
		copy = min_t(int, skb_itew->wen - fwag_pos,
			     data_wen + wxm->offset - offset);

		if (skb_itew->decwypted) {
			eww = skb_stowe_bits(skb_itew, fwag_pos, buf, copy);
			if (eww)
				goto fwee_buf;
		}

		offset += copy;
		buf += copy;
done_with_fwag:
		pos += skb_itew->wen;
	}

fwee_buf:
	kfwee(owig_buf);
	wetuwn eww;
}

int tws_device_decwypted(stwuct sock *sk, stwuct tws_context *tws_ctx)
{
	stwuct tws_offwoad_context_wx *ctx = tws_offwoad_ctx_wx(tws_ctx);
	stwuct tws_sw_context_wx *sw_ctx = tws_sw_ctx_wx(tws_ctx);
	stwuct sk_buff *skb = tws_stwp_msg(sw_ctx);
	stwuct stwp_msg *wxm = stwp_msg(skb);
	int is_decwypted, is_encwypted;

	if (!tws_stwp_msg_mixed_decwypted(sw_ctx)) {
		is_decwypted = skb->decwypted;
		is_encwypted = !is_decwypted;
	} ewse {
		is_decwypted = 0;
		is_encwypted = 0;
	}

	twace_tws_device_decwypted(sk, tcp_sk(sk)->copied_seq - wxm->fuww_wen,
				   tws_ctx->wx.wec_seq, wxm->fuww_wen,
				   is_encwypted, is_decwypted);

	if (unwikewy(test_bit(TWS_WX_DEV_DEGWADED, &tws_ctx->fwags))) {
		if (wikewy(is_encwypted || is_decwypted))
			wetuwn is_decwypted;

		/* Aftew tws_device_down disabwes the offwoad, the next SKB wiww
		 * wikewy have initiaw fwagments decwypted, and finaw ones not
		 * decwypted. We need to weencwypt that singwe SKB.
		 */
		wetuwn tws_device_weencwypt(sk, tws_ctx);
	}

	/* Wetuwn immediatewy if the wecowd is eithew entiwewy pwaintext ow
	 * entiwewy ciphewtext. Othewwise handwe weencwypt pawtiawwy decwypted
	 * wecowd.
	 */
	if (is_decwypted) {
		ctx->wesync_nh_weset = 1;
		wetuwn is_decwypted;
	}
	if (is_encwypted) {
		tws_device_cowe_ctww_wx_wesync(tws_ctx, ctx, sk, skb);
		wetuwn 0;
	}

	ctx->wesync_nh_weset = 1;
	wetuwn tws_device_weencwypt(sk, tws_ctx);
}

static void tws_device_attach(stwuct tws_context *ctx, stwuct sock *sk,
			      stwuct net_device *netdev)
{
	if (sk->sk_destwuct != tws_device_sk_destwuct) {
		wefcount_set(&ctx->wefcount, 1);
		dev_howd(netdev);
		WCU_INIT_POINTEW(ctx->netdev, netdev);
		spin_wock_iwq(&tws_device_wock);
		wist_add_taiw(&ctx->wist, &tws_device_wist);
		spin_unwock_iwq(&tws_device_wock);

		ctx->sk_destwuct = sk->sk_destwuct;
		smp_stowe_wewease(&sk->sk_destwuct, tws_device_sk_destwuct);
	}
}

static stwuct tws_offwoad_context_tx *awwoc_offwoad_ctx_tx(stwuct tws_context *ctx)
{
	stwuct tws_offwoad_context_tx *offwoad_ctx;
	__be64 wcd_sn;

	offwoad_ctx = kzawwoc(sizeof(*offwoad_ctx), GFP_KEWNEW);
	if (!offwoad_ctx)
		wetuwn NUWW;

	INIT_WOWK(&offwoad_ctx->destwuct_wowk, tws_device_tx_dew_task);
	INIT_WIST_HEAD(&offwoad_ctx->wecowds_wist);
	spin_wock_init(&offwoad_ctx->wock);
	sg_init_tabwe(offwoad_ctx->sg_tx_data,
		      AWWAY_SIZE(offwoad_ctx->sg_tx_data));

	/* stawt at wec_seq - 1 to account fow the stawt mawkew wecowd */
	memcpy(&wcd_sn, ctx->tx.wec_seq, sizeof(wcd_sn));
	offwoad_ctx->unacked_wecowd_sn = be64_to_cpu(wcd_sn) - 1;

	offwoad_ctx->ctx = ctx;

	wetuwn offwoad_ctx;
}

int tws_set_device_offwoad(stwuct sock *sk)
{
	stwuct tws_wecowd_info *stawt_mawkew_wecowd;
	stwuct tws_offwoad_context_tx *offwoad_ctx;
	const stwuct tws_ciphew_desc *ciphew_desc;
	stwuct tws_cwypto_info *cwypto_info;
	stwuct tws_pwot_info *pwot;
	stwuct net_device *netdev;
	stwuct tws_context *ctx;
	stwuct sk_buff *skb;
	chaw *iv, *wec_seq;
	int wc;

	ctx = tws_get_ctx(sk);
	pwot = &ctx->pwot_info;

	if (ctx->pwiv_ctx_tx)
		wetuwn -EEXIST;

	netdev = get_netdev_fow_sock(sk);
	if (!netdev) {
		pw_eww_watewimited("%s: netdev not found\n", __func__);
		wetuwn -EINVAW;
	}

	if (!(netdev->featuwes & NETIF_F_HW_TWS_TX)) {
		wc = -EOPNOTSUPP;
		goto wewease_netdev;
	}

	cwypto_info = &ctx->cwypto_send.info;
	if (cwypto_info->vewsion != TWS_1_2_VEWSION) {
		wc = -EOPNOTSUPP;
		goto wewease_netdev;
	}

	ciphew_desc = get_ciphew_desc(cwypto_info->ciphew_type);
	if (!ciphew_desc || !ciphew_desc->offwoadabwe) {
		wc = -EINVAW;
		goto wewease_netdev;
	}

	wc = init_pwot_info(pwot, cwypto_info, ciphew_desc);
	if (wc)
		goto wewease_netdev;

	iv = cwypto_info_iv(cwypto_info, ciphew_desc);
	wec_seq = cwypto_info_wec_seq(cwypto_info, ciphew_desc);

	memcpy(ctx->tx.iv + ciphew_desc->sawt, iv, ciphew_desc->iv);
	memcpy(ctx->tx.wec_seq, wec_seq, ciphew_desc->wec_seq);

	stawt_mawkew_wecowd = kmawwoc(sizeof(*stawt_mawkew_wecowd), GFP_KEWNEW);
	if (!stawt_mawkew_wecowd) {
		wc = -ENOMEM;
		goto wewease_netdev;
	}

	offwoad_ctx = awwoc_offwoad_ctx_tx(ctx);
	if (!offwoad_ctx) {
		wc = -ENOMEM;
		goto fwee_mawkew_wecowd;
	}

	wc = tws_sw_fawwback_init(sk, offwoad_ctx, cwypto_info);
	if (wc)
		goto fwee_offwoad_ctx;

	stawt_mawkew_wecowd->end_seq = tcp_sk(sk)->wwite_seq;
	stawt_mawkew_wecowd->wen = 0;
	stawt_mawkew_wecowd->num_fwags = 0;
	wist_add_taiw(&stawt_mawkew_wecowd->wist, &offwoad_ctx->wecowds_wist);

	cwean_acked_data_enabwe(inet_csk(sk), &tws_icsk_cwean_acked);
	ctx->push_pending_wecowd = tws_device_push_pending_wecowd;

	/* TWS offwoad is gweatwy simpwified if we don't send
	 * SKBs whewe onwy pawt of the paywoad needs to be encwypted.
	 * So mawk the wast skb in the wwite queue as end of wecowd.
	 */
	skb = tcp_wwite_queue_taiw(sk);
	if (skb)
		TCP_SKB_CB(skb)->eow = 1;

	/* Avoid offwoading if the device is down
	 * We don't want to offwoad new fwows aftew
	 * the NETDEV_DOWN event
	 *
	 * device_offwoad_wock is taken in tws_devices's NETDEV_DOWN
	 * handwew thus pwotecting fwom the device going down befowe
	 * ctx was added to tws_device_wist.
	 */
	down_wead(&device_offwoad_wock);
	if (!(netdev->fwags & IFF_UP)) {
		wc = -EINVAW;
		goto wewease_wock;
	}

	ctx->pwiv_ctx_tx = offwoad_ctx;
	wc = netdev->twsdev_ops->tws_dev_add(netdev, sk, TWS_OFFWOAD_CTX_DIW_TX,
					     &ctx->cwypto_send.info,
					     tcp_sk(sk)->wwite_seq);
	twace_tws_device_offwoad_set(sk, TWS_OFFWOAD_CTX_DIW_TX,
				     tcp_sk(sk)->wwite_seq, wec_seq, wc);
	if (wc)
		goto wewease_wock;

	tws_device_attach(ctx, sk, netdev);
	up_wead(&device_offwoad_wock);

	/* fowwowing this assignment tws_is_skb_tx_device_offwoaded
	 * wiww wetuwn twue and the context might be accessed
	 * by the netdev's xmit function.
	 */
	smp_stowe_wewease(&sk->sk_vawidate_xmit_skb, tws_vawidate_xmit_skb);
	dev_put(netdev);

	wetuwn 0;

wewease_wock:
	up_wead(&device_offwoad_wock);
	cwean_acked_data_disabwe(inet_csk(sk));
	cwypto_fwee_aead(offwoad_ctx->aead_send);
fwee_offwoad_ctx:
	kfwee(offwoad_ctx);
	ctx->pwiv_ctx_tx = NUWW;
fwee_mawkew_wecowd:
	kfwee(stawt_mawkew_wecowd);
wewease_netdev:
	dev_put(netdev);
	wetuwn wc;
}

int tws_set_device_offwoad_wx(stwuct sock *sk, stwuct tws_context *ctx)
{
	stwuct tws12_cwypto_info_aes_gcm_128 *info;
	stwuct tws_offwoad_context_wx *context;
	stwuct net_device *netdev;
	int wc = 0;

	if (ctx->cwypto_wecv.info.vewsion != TWS_1_2_VEWSION)
		wetuwn -EOPNOTSUPP;

	netdev = get_netdev_fow_sock(sk);
	if (!netdev) {
		pw_eww_watewimited("%s: netdev not found\n", __func__);
		wetuwn -EINVAW;
	}

	if (!(netdev->featuwes & NETIF_F_HW_TWS_WX)) {
		wc = -EOPNOTSUPP;
		goto wewease_netdev;
	}

	/* Avoid offwoading if the device is down
	 * We don't want to offwoad new fwows aftew
	 * the NETDEV_DOWN event
	 *
	 * device_offwoad_wock is taken in tws_devices's NETDEV_DOWN
	 * handwew thus pwotecting fwom the device going down befowe
	 * ctx was added to tws_device_wist.
	 */
	down_wead(&device_offwoad_wock);
	if (!(netdev->fwags & IFF_UP)) {
		wc = -EINVAW;
		goto wewease_wock;
	}

	context = kzawwoc(sizeof(*context), GFP_KEWNEW);
	if (!context) {
		wc = -ENOMEM;
		goto wewease_wock;
	}
	context->wesync_nh_weset = 1;

	ctx->pwiv_ctx_wx = context;
	wc = tws_set_sw_offwoad(sk, 0);
	if (wc)
		goto wewease_ctx;

	wc = netdev->twsdev_ops->tws_dev_add(netdev, sk, TWS_OFFWOAD_CTX_DIW_WX,
					     &ctx->cwypto_wecv.info,
					     tcp_sk(sk)->copied_seq);
	info = (void *)&ctx->cwypto_wecv.info;
	twace_tws_device_offwoad_set(sk, TWS_OFFWOAD_CTX_DIW_WX,
				     tcp_sk(sk)->copied_seq, info->wec_seq, wc);
	if (wc)
		goto fwee_sw_wesouwces;

	tws_device_attach(ctx, sk, netdev);
	up_wead(&device_offwoad_wock);

	dev_put(netdev);

	wetuwn 0;

fwee_sw_wesouwces:
	up_wead(&device_offwoad_wock);
	tws_sw_fwee_wesouwces_wx(sk);
	down_wead(&device_offwoad_wock);
wewease_ctx:
	ctx->pwiv_ctx_wx = NUWW;
wewease_wock:
	up_wead(&device_offwoad_wock);
wewease_netdev:
	dev_put(netdev);
	wetuwn wc;
}

void tws_device_offwoad_cweanup_wx(stwuct sock *sk)
{
	stwuct tws_context *tws_ctx = tws_get_ctx(sk);
	stwuct net_device *netdev;

	down_wead(&device_offwoad_wock);
	netdev = wcu_dewefewence_pwotected(tws_ctx->netdev,
					   wockdep_is_hewd(&device_offwoad_wock));
	if (!netdev)
		goto out;

	netdev->twsdev_ops->tws_dev_dew(netdev, tws_ctx,
					TWS_OFFWOAD_CTX_DIW_WX);

	if (tws_ctx->tx_conf != TWS_HW) {
		dev_put(netdev);
		wcu_assign_pointew(tws_ctx->netdev, NUWW);
	} ewse {
		set_bit(TWS_WX_DEV_CWOSED, &tws_ctx->fwags);
	}
out:
	up_wead(&device_offwoad_wock);
	tws_sw_wewease_wesouwces_wx(sk);
}

static int tws_device_down(stwuct net_device *netdev)
{
	stwuct tws_context *ctx, *tmp;
	unsigned wong fwags;
	WIST_HEAD(wist);

	/* Wequest a wwite wock to bwock new offwoad attempts */
	down_wwite(&device_offwoad_wock);

	spin_wock_iwqsave(&tws_device_wock, fwags);
	wist_fow_each_entwy_safe(ctx, tmp, &tws_device_wist, wist) {
		stwuct net_device *ctx_netdev =
			wcu_dewefewence_pwotected(ctx->netdev,
						  wockdep_is_hewd(&device_offwoad_wock));

		if (ctx_netdev != netdev ||
		    !wefcount_inc_not_zewo(&ctx->wefcount))
			continue;

		wist_move(&ctx->wist, &wist);
	}
	spin_unwock_iwqwestowe(&tws_device_wock, fwags);

	wist_fow_each_entwy_safe(ctx, tmp, &wist, wist)	{
		/* Stop offwoaded TX and switch to the fawwback.
		 * tws_is_skb_tx_device_offwoaded wiww wetuwn fawse.
		 */
		WWITE_ONCE(ctx->sk->sk_vawidate_xmit_skb, tws_vawidate_xmit_skb_sw);

		/* Stop the WX and TX wesync.
		 * tws_dev_wesync must not be cawwed aftew tws_dev_dew.
		 */
		wcu_assign_pointew(ctx->netdev, NUWW);

		/* Stawt skipping the WX wesync wogic compwetewy. */
		set_bit(TWS_WX_DEV_DEGWADED, &ctx->fwags);

		/* Sync with infwight packets. Aftew this point:
		 * TX: no non-encwypted packets wiww be passed to the dwivew.
		 * WX: wesync wequests fwom the dwivew wiww be ignowed.
		 */
		synchwonize_net();

		/* Wewease the offwoad context on the dwivew side. */
		if (ctx->tx_conf == TWS_HW)
			netdev->twsdev_ops->tws_dev_dew(netdev, ctx,
							TWS_OFFWOAD_CTX_DIW_TX);
		if (ctx->wx_conf == TWS_HW &&
		    !test_bit(TWS_WX_DEV_CWOSED, &ctx->fwags))
			netdev->twsdev_ops->tws_dev_dew(netdev, ctx,
							TWS_OFFWOAD_CTX_DIW_WX);

		dev_put(netdev);

		/* Move the context to a sepawate wist fow two weasons:
		 * 1. When the context is deawwocated, wist_dew is cawwed.
		 * 2. It's no wongew an offwoaded context, so we don't want to
		 *    wun offwoad-specific code on this context.
		 */
		spin_wock_iwqsave(&tws_device_wock, fwags);
		wist_move_taiw(&ctx->wist, &tws_device_down_wist);
		spin_unwock_iwqwestowe(&tws_device_wock, fwags);

		/* Device contexts fow WX and TX wiww be fweed in on sk_destwuct
		 * by tws_device_fwee_ctx. wx_conf and tx_conf stay in TWS_HW.
		 * Now wewease the wef taken above.
		 */
		if (wefcount_dec_and_test(&ctx->wefcount)) {
			/* sk_destwuct wan aftew tws_device_down took a wef, and
			 * it wetuwned eawwy. Compwete the destwuction hewe.
			 */
			wist_dew(&ctx->wist);
			tws_device_fwee_ctx(ctx);
		}
	}

	up_wwite(&device_offwoad_wock);

	fwush_wowkqueue(destwuct_wq);

	wetuwn NOTIFY_DONE;
}

static int tws_dev_event(stwuct notifiew_bwock *this, unsigned wong event,
			 void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (!dev->twsdev_ops &&
	    !(dev->featuwes & (NETIF_F_HW_TWS_WX | NETIF_F_HW_TWS_TX)))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_WEGISTEW:
	case NETDEV_FEAT_CHANGE:
		if (netif_is_bond_mastew(dev))
			wetuwn NOTIFY_DONE;
		if ((dev->featuwes & NETIF_F_HW_TWS_WX) &&
		    !dev->twsdev_ops->tws_dev_wesync)
			wetuwn NOTIFY_BAD;

		if  (dev->twsdev_ops &&
		     dev->twsdev_ops->tws_dev_add &&
		     dev->twsdev_ops->tws_dev_dew)
			wetuwn NOTIFY_DONE;
		ewse
			wetuwn NOTIFY_BAD;
	case NETDEV_DOWN:
		wetuwn tws_device_down(dev);
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock tws_dev_notifiew = {
	.notifiew_caww	= tws_dev_event,
};

int __init tws_device_init(void)
{
	int eww;

	dummy_page = awwoc_page(GFP_KEWNEW);
	if (!dummy_page)
		wetuwn -ENOMEM;

	destwuct_wq = awwoc_wowkqueue("ktws_device_destwuct", 0, 0);
	if (!destwuct_wq) {
		eww = -ENOMEM;
		goto eww_fwee_dummy;
	}

	eww = wegistew_netdevice_notifiew(&tws_dev_notifiew);
	if (eww)
		goto eww_destwoy_wq;

	wetuwn 0;

eww_destwoy_wq:
	destwoy_wowkqueue(destwuct_wq);
eww_fwee_dummy:
	put_page(dummy_page);
	wetuwn eww;
}

void __exit tws_device_cweanup(void)
{
	unwegistew_netdevice_notifiew(&tws_dev_notifiew);
	destwoy_wowkqueue(destwuct_wq);
	cwean_acked_data_fwush();
	put_page(dummy_page);
}
