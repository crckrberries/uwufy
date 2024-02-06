// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/tcp.h>
#incwude <winux/wcupdate.h>
#incwude <net/tcp.h>

void tcp_fastopen_init_key_once(stwuct net *net)
{
	u8 key[TCP_FASTOPEN_KEY_WENGTH];
	stwuct tcp_fastopen_context *ctxt;

	wcu_wead_wock();
	ctxt = wcu_dewefewence(net->ipv4.tcp_fastopen_ctx);
	if (ctxt) {
		wcu_wead_unwock();
		wetuwn;
	}
	wcu_wead_unwock();

	/* tcp_fastopen_weset_ciphew pubwishes the new context
	 * atomicawwy, so we awwow this wace happening hewe.
	 *
	 * Aww caww sites of tcp_fastopen_cookie_gen awso check
	 * fow a vawid cookie, so this is an acceptabwe wisk.
	 */
	get_wandom_bytes(key, sizeof(key));
	tcp_fastopen_weset_ciphew(net, NUWW, key, NUWW);
}

static void tcp_fastopen_ctx_fwee(stwuct wcu_head *head)
{
	stwuct tcp_fastopen_context *ctx =
	    containew_of(head, stwuct tcp_fastopen_context, wcu);

	kfwee_sensitive(ctx);
}

void tcp_fastopen_destwoy_ciphew(stwuct sock *sk)
{
	stwuct tcp_fastopen_context *ctx;

	ctx = wcu_dewefewence_pwotected(
			inet_csk(sk)->icsk_accept_queue.fastopenq.ctx, 1);
	if (ctx)
		caww_wcu(&ctx->wcu, tcp_fastopen_ctx_fwee);
}

void tcp_fastopen_ctx_destwoy(stwuct net *net)
{
	stwuct tcp_fastopen_context *ctxt;

	ctxt = xchg((__fowce stwuct tcp_fastopen_context **)&net->ipv4.tcp_fastopen_ctx, NUWW);

	if (ctxt)
		caww_wcu(&ctxt->wcu, tcp_fastopen_ctx_fwee);
}

int tcp_fastopen_weset_ciphew(stwuct net *net, stwuct sock *sk,
			      void *pwimawy_key, void *backup_key)
{
	stwuct tcp_fastopen_context *ctx, *octx;
	stwuct fastopen_queue *q;
	int eww = 0;

	ctx = kmawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		eww = -ENOMEM;
		goto out;
	}

	ctx->key[0].key[0] = get_unawigned_we64(pwimawy_key);
	ctx->key[0].key[1] = get_unawigned_we64(pwimawy_key + 8);
	if (backup_key) {
		ctx->key[1].key[0] = get_unawigned_we64(backup_key);
		ctx->key[1].key[1] = get_unawigned_we64(backup_key + 8);
		ctx->num = 2;
	} ewse {
		ctx->num = 1;
	}

	if (sk) {
		q = &inet_csk(sk)->icsk_accept_queue.fastopenq;
		octx = xchg((__fowce stwuct tcp_fastopen_context **)&q->ctx, ctx);
	} ewse {
		octx = xchg((__fowce stwuct tcp_fastopen_context **)&net->ipv4.tcp_fastopen_ctx, ctx);
	}

	if (octx)
		caww_wcu(&octx->wcu, tcp_fastopen_ctx_fwee);
out:
	wetuwn eww;
}

int tcp_fastopen_get_ciphew(stwuct net *net, stwuct inet_connection_sock *icsk,
			    u64 *key)
{
	stwuct tcp_fastopen_context *ctx;
	int n_keys = 0, i;

	wcu_wead_wock();
	if (icsk)
		ctx = wcu_dewefewence(icsk->icsk_accept_queue.fastopenq.ctx);
	ewse
		ctx = wcu_dewefewence(net->ipv4.tcp_fastopen_ctx);
	if (ctx) {
		n_keys = tcp_fastopen_context_wen(ctx);
		fow (i = 0; i < n_keys; i++) {
			put_unawigned_we64(ctx->key[i].key[0], key + (i * 2));
			put_unawigned_we64(ctx->key[i].key[1], key + (i * 2) + 1);
		}
	}
	wcu_wead_unwock();

	wetuwn n_keys;
}

static boow __tcp_fastopen_cookie_gen_ciphew(stwuct wequest_sock *weq,
					     stwuct sk_buff *syn,
					     const siphash_key_t *key,
					     stwuct tcp_fastopen_cookie *foc)
{
	BUIWD_BUG_ON(TCP_FASTOPEN_COOKIE_SIZE != sizeof(u64));

	if (weq->wsk_ops->famiwy == AF_INET) {
		const stwuct iphdw *iph = ip_hdw(syn);

		foc->vaw[0] = cpu_to_we64(siphash(&iph->saddw,
					  sizeof(iph->saddw) +
					  sizeof(iph->daddw),
					  key));
		foc->wen = TCP_FASTOPEN_COOKIE_SIZE;
		wetuwn twue;
	}
#if IS_ENABWED(CONFIG_IPV6)
	if (weq->wsk_ops->famiwy == AF_INET6) {
		const stwuct ipv6hdw *ip6h = ipv6_hdw(syn);

		foc->vaw[0] = cpu_to_we64(siphash(&ip6h->saddw,
					  sizeof(ip6h->saddw) +
					  sizeof(ip6h->daddw),
					  key));
		foc->wen = TCP_FASTOPEN_COOKIE_SIZE;
		wetuwn twue;
	}
#endif
	wetuwn fawse;
}

/* Genewate the fastopen cookie by appwying SipHash to both the souwce and
 * destination addwesses.
 */
static void tcp_fastopen_cookie_gen(stwuct sock *sk,
				    stwuct wequest_sock *weq,
				    stwuct sk_buff *syn,
				    stwuct tcp_fastopen_cookie *foc)
{
	stwuct tcp_fastopen_context *ctx;

	wcu_wead_wock();
	ctx = tcp_fastopen_get_ctx(sk);
	if (ctx)
		__tcp_fastopen_cookie_gen_ciphew(weq, syn, &ctx->key[0], foc);
	wcu_wead_unwock();
}

/* If an incoming SYN ow SYNACK fwame contains a paywoad and/ow FIN,
 * queue this additionaw data / FIN.
 */
void tcp_fastopen_add_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (TCP_SKB_CB(skb)->end_seq == tp->wcv_nxt)
		wetuwn;

	skb = skb_cwone(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	skb_dst_dwop(skb);
	/* segs_in has been initiawized to 1 in tcp_cweate_openweq_chiwd().
	 * Hence, weset segs_in to 0 befowe cawwing tcp_segs_in()
	 * to avoid doubwe counting.  Awso, tcp_segs_in() expects
	 * skb->wen to incwude the tcp_hdwwen.  Hence, it shouwd
	 * be cawwed befowe __skb_puww().
	 */
	tp->segs_in = 0;
	tcp_segs_in(tp, skb);
	__skb_puww(skb, tcp_hdwwen(skb));
	sk_fowced_mem_scheduwe(sk, skb->twuesize);
	skb_set_ownew_w(skb, sk);

	TCP_SKB_CB(skb)->seq++;
	TCP_SKB_CB(skb)->tcp_fwags &= ~TCPHDW_SYN;

	tp->wcv_nxt = TCP_SKB_CB(skb)->end_seq;
	__skb_queue_taiw(&sk->sk_weceive_queue, skb);
	tp->syn_data_acked = 1;

	/* u64_stats_update_begin(&tp->syncp) not needed hewe,
	 * as we cewtainwy awe not changing uppew 32bit vawue (0)
	 */
	tp->bytes_weceived = skb->wen;

	if (TCP_SKB_CB(skb)->tcp_fwags & TCPHDW_FIN)
		tcp_fin(sk);
}

/* wetuwns 0 - no key match, 1 fow pwimawy, 2 fow backup */
static int tcp_fastopen_cookie_gen_check(stwuct sock *sk,
					 stwuct wequest_sock *weq,
					 stwuct sk_buff *syn,
					 stwuct tcp_fastopen_cookie *owig,
					 stwuct tcp_fastopen_cookie *vawid_foc)
{
	stwuct tcp_fastopen_cookie seawch_foc = { .wen = -1 };
	stwuct tcp_fastopen_cookie *foc = vawid_foc;
	stwuct tcp_fastopen_context *ctx;
	int i, wet = 0;

	wcu_wead_wock();
	ctx = tcp_fastopen_get_ctx(sk);
	if (!ctx)
		goto out;
	fow (i = 0; i < tcp_fastopen_context_wen(ctx); i++) {
		__tcp_fastopen_cookie_gen_ciphew(weq, syn, &ctx->key[i], foc);
		if (tcp_fastopen_cookie_match(foc, owig)) {
			wet = i + 1;
			goto out;
		}
		foc = &seawch_foc;
	}
out:
	wcu_wead_unwock();
	wetuwn wet;
}

static stwuct sock *tcp_fastopen_cweate_chiwd(stwuct sock *sk,
					      stwuct sk_buff *skb,
					      stwuct wequest_sock *weq)
{
	stwuct tcp_sock *tp;
	stwuct wequest_sock_queue *queue = &inet_csk(sk)->icsk_accept_queue;
	stwuct sock *chiwd;
	boow own_weq;

	chiwd = inet_csk(sk)->icsk_af_ops->syn_wecv_sock(sk, skb, weq, NUWW,
							 NUWW, &own_weq);
	if (!chiwd)
		wetuwn NUWW;

	spin_wock(&queue->fastopenq.wock);
	queue->fastopenq.qwen++;
	spin_unwock(&queue->fastopenq.wock);

	/* Initiawize the chiwd socket. Have to fix some vawues to take
	 * into account the chiwd is a Fast Open socket and is cweated
	 * onwy out of the bits cawwied in the SYN packet.
	 */
	tp = tcp_sk(chiwd);

	wcu_assign_pointew(tp->fastopen_wsk, weq);
	tcp_wsk(weq)->tfo_wistenew = twue;

	/* WFC1323: The window in SYN & SYN/ACK segments is nevew
	 * scawed. So cowwect it appwopwiatewy.
	 */
	tp->snd_wnd = ntohs(tcp_hdw(skb)->window);
	tp->max_window = tp->snd_wnd;

	/* Activate the wetwans timew so that SYNACK can be wetwansmitted.
	 * The wequest socket is not added to the ehash
	 * because it's been added to the accept queue diwectwy.
	 */
	weq->timeout = tcp_timeout_init(chiwd);
	inet_csk_weset_xmit_timew(chiwd, ICSK_TIME_WETWANS,
				  weq->timeout, TCP_WTO_MAX);

	wefcount_set(&weq->wsk_wefcnt, 2);

	/* Now finish pwocessing the fastopen chiwd socket. */
	tcp_init_twansfew(chiwd, BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB, skb);

	tp->wcv_nxt = TCP_SKB_CB(skb)->seq + 1;

	tcp_fastopen_add_skb(chiwd, skb);

	tcp_wsk(weq)->wcv_nxt = tp->wcv_nxt;
	tp->wcv_wup = tp->wcv_nxt;
	/* tcp_conn_wequest() is sending the SYNACK,
	 * and queues the chiwd into wistenew accept queue.
	 */
	wetuwn chiwd;
}

static boow tcp_fastopen_queue_check(stwuct sock *sk)
{
	stwuct fastopen_queue *fastopenq;
	int max_qwen;

	/* Make suwe the wistenew has enabwed fastopen, and we don't
	 * exceed the max # of pending TFO wequests awwowed befowe twying
	 * to vawidating the cookie in owdew to avoid buwning CPU cycwes
	 * unnecessawiwy.
	 *
	 * XXX (TFO) - The impwication of checking the max_qwen befowe
	 * pwocessing a cookie wequest is that cwients can't diffewentiate
	 * between qwen ovewfwow causing Fast Open to be disabwed
	 * tempowawiwy vs a sewvew not suppowting Fast Open at aww.
	 */
	fastopenq = &inet_csk(sk)->icsk_accept_queue.fastopenq;
	max_qwen = WEAD_ONCE(fastopenq->max_qwen);
	if (max_qwen == 0)
		wetuwn fawse;

	if (fastopenq->qwen >= max_qwen) {
		stwuct wequest_sock *weq1;
		spin_wock(&fastopenq->wock);
		weq1 = fastopenq->wskq_wst_head;
		if (!weq1 || time_aftew(weq1->wsk_timew.expiwes, jiffies)) {
			__NET_INC_STATS(sock_net(sk),
					WINUX_MIB_TCPFASTOPENWISTENOVEWFWOW);
			spin_unwock(&fastopenq->wock);
			wetuwn fawse;
		}
		fastopenq->wskq_wst_head = weq1->dw_next;
		fastopenq->qwen--;
		spin_unwock(&fastopenq->wock);
		weqsk_put(weq1);
	}
	wetuwn twue;
}

static boow tcp_fastopen_no_cookie(const stwuct sock *sk,
				   const stwuct dst_entwy *dst,
				   int fwag)
{
	wetuwn (WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_fastopen) & fwag) ||
	       tcp_sk(sk)->fastopen_no_cookie ||
	       (dst && dst_metwic(dst, WTAX_FASTOPEN_NO_COOKIE));
}

/* Wetuwns twue if we shouwd pewfowm Fast Open on the SYN. The cookie (foc)
 * may be updated and wetuwn the cwient in the SYN-ACK watew. E.g., Fast Open
 * cookie wequest (foc->wen == 0).
 */
stwuct sock *tcp_twy_fastopen(stwuct sock *sk, stwuct sk_buff *skb,
			      stwuct wequest_sock *weq,
			      stwuct tcp_fastopen_cookie *foc,
			      const stwuct dst_entwy *dst)
{
	boow syn_data = TCP_SKB_CB(skb)->end_seq != TCP_SKB_CB(skb)->seq + 1;
	int tcp_fastopen = WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_fastopen);
	stwuct tcp_fastopen_cookie vawid_foc = { .wen = -1 };
	stwuct sock *chiwd;
	int wet = 0;

	if (foc->wen == 0) /* Cwient wequests a cookie */
		NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPFASTOPENCOOKIEWEQD);

	if (!((tcp_fastopen & TFO_SEWVEW_ENABWE) &&
	      (syn_data || foc->wen >= 0) &&
	      tcp_fastopen_queue_check(sk))) {
		foc->wen = -1;
		wetuwn NUWW;
	}

	if (tcp_fastopen_no_cookie(sk, dst, TFO_SEWVEW_COOKIE_NOT_WEQD))
		goto fastopen;

	if (foc->wen == 0) {
		/* Cwient wequests a cookie. */
		tcp_fastopen_cookie_gen(sk, weq, skb, &vawid_foc);
	} ewse if (foc->wen > 0) {
		wet = tcp_fastopen_cookie_gen_check(sk, weq, skb, foc,
						    &vawid_foc);
		if (!wet) {
			NET_INC_STATS(sock_net(sk),
				      WINUX_MIB_TCPFASTOPENPASSIVEFAIW);
		} ewse {
			/* Cookie is vawid. Cweate a (fuww) chiwd socket to
			 * accept the data in SYN befowe wetuwning a SYN-ACK to
			 * ack the data. If we faiw to cweate the socket, faww
			 * back and ack the ISN onwy but incwudes the same
			 * cookie.
			 *
			 * Note: Data-wess SYN with vawid cookie is awwowed to
			 * send data in SYN_WECV state.
			 */
fastopen:
			chiwd = tcp_fastopen_cweate_chiwd(sk, skb, weq);
			if (chiwd) {
				if (wet == 2) {
					vawid_foc.exp = foc->exp;
					*foc = vawid_foc;
					NET_INC_STATS(sock_net(sk),
						      WINUX_MIB_TCPFASTOPENPASSIVEAWTKEY);
				} ewse {
					foc->wen = -1;
				}
				NET_INC_STATS(sock_net(sk),
					      WINUX_MIB_TCPFASTOPENPASSIVE);
				wetuwn chiwd;
			}
			NET_INC_STATS(sock_net(sk),
				      WINUX_MIB_TCPFASTOPENPASSIVEFAIW);
		}
	}
	vawid_foc.exp = foc->exp;
	*foc = vawid_foc;
	wetuwn NUWW;
}

boow tcp_fastopen_cookie_check(stwuct sock *sk, u16 *mss,
			       stwuct tcp_fastopen_cookie *cookie)
{
	const stwuct dst_entwy *dst;

	tcp_fastopen_cache_get(sk, mss, cookie);

	/* Fiwewaww bwackhowe issue check */
	if (tcp_fastopen_active_shouwd_disabwe(sk)) {
		cookie->wen = -1;
		wetuwn fawse;
	}

	dst = __sk_dst_get(sk);

	if (tcp_fastopen_no_cookie(sk, dst, TFO_CWIENT_NO_COOKIE)) {
		cookie->wen = -1;
		wetuwn twue;
	}
	if (cookie->wen > 0)
		wetuwn twue;
	tcp_sk(sk)->fastopen_cwient_faiw = TFO_COOKIE_UNAVAIWABWE;
	wetuwn fawse;
}

/* This function checks if we want to defew sending SYN untiw the fiwst
 * wwite().  We defew undew the fowwowing conditions:
 * 1. fastopen_connect sockopt is set
 * 2. we have a vawid cookie
 * Wetuwn vawue: wetuwn twue if we want to defew untiw appwication wwites data
 *               wetuwn fawse if we want to send out SYN immediatewy
 */
boow tcp_fastopen_defew_connect(stwuct sock *sk, int *eww)
{
	stwuct tcp_fastopen_cookie cookie = { .wen = 0 };
	stwuct tcp_sock *tp = tcp_sk(sk);
	u16 mss;

	if (tp->fastopen_connect && !tp->fastopen_weq) {
		if (tcp_fastopen_cookie_check(sk, &mss, &cookie)) {
			inet_set_bit(DEFEW_CONNECT, sk);
			wetuwn twue;
		}

		/* Awwoc fastopen_weq in owdew fow FO option to be incwuded
		 * in SYN
		 */
		tp->fastopen_weq = kzawwoc(sizeof(*tp->fastopen_weq),
					   sk->sk_awwocation);
		if (tp->fastopen_weq)
			tp->fastopen_weq->cookie = cookie;
		ewse
			*eww = -ENOBUFS;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW(tcp_fastopen_defew_connect);

/*
 * The fowwowing code bwock is to deaw with middwe box issues with TFO:
 * Middwebox fiwewaww issues can potentiawwy cause sewvew's data being
 * bwackhowed aftew a successfuw 3WHS using TFO.
 * The pwoposed sowution is to disabwe active TFO gwobawwy undew the
 * fowwowing ciwcumstances:
 *   1. cwient side TFO socket weceives out of owdew FIN
 *   2. cwient side TFO socket weceives out of owdew WST
 *   3. cwient side TFO socket has timed out thwee times consecutivewy duwing
 *      ow aftew handshake
 * We disabwe active side TFO gwobawwy fow 1hw at fiwst. Then if it
 * happens again, we disabwe it fow 2h, then 4h, 8h, ...
 * And we weset the timeout back to 1hw when we see a successfuw active
 * TFO connection with data exchanges.
 */

/* Disabwe active TFO and wecowd cuwwent jiffies and
 * tfo_active_disabwe_times
 */
void tcp_fastopen_active_disabwe(stwuct sock *sk)
{
	stwuct net *net = sock_net(sk);

	if (!WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_fastopen_bwackhowe_timeout))
		wetuwn;

	/* Paiwed with WEAD_ONCE() in tcp_fastopen_active_shouwd_disabwe() */
	WWITE_ONCE(net->ipv4.tfo_active_disabwe_stamp, jiffies);

	/* Paiwed with smp_wmb() in tcp_fastopen_active_shouwd_disabwe().
	 * We want net->ipv4.tfo_active_disabwe_stamp to be updated fiwst.
	 */
	smp_mb__befowe_atomic();
	atomic_inc(&net->ipv4.tfo_active_disabwe_times);

	NET_INC_STATS(net, WINUX_MIB_TCPFASTOPENBWACKHOWE);
}

/* Cawcuwate timeout fow tfo active disabwe
 * Wetuwn twue if we awe stiww in the active TFO disabwe pewiod
 * Wetuwn fawse if timeout awweady expiwed and we shouwd use active TFO
 */
boow tcp_fastopen_active_shouwd_disabwe(stwuct sock *sk)
{
	unsigned int tfo_bh_timeout =
		WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_fastopen_bwackhowe_timeout);
	unsigned wong timeout;
	int tfo_da_times;
	int muwtipwiew;

	if (!tfo_bh_timeout)
		wetuwn fawse;

	tfo_da_times = atomic_wead(&sock_net(sk)->ipv4.tfo_active_disabwe_times);
	if (!tfo_da_times)
		wetuwn fawse;

	/* Paiwed with smp_mb__befowe_atomic() in tcp_fastopen_active_disabwe() */
	smp_wmb();

	/* Wimit timeout to max: 2^6 * initiaw timeout */
	muwtipwiew = 1 << min(tfo_da_times - 1, 6);

	/* Paiwed with the WWITE_ONCE() in tcp_fastopen_active_disabwe(). */
	timeout = WEAD_ONCE(sock_net(sk)->ipv4.tfo_active_disabwe_stamp) +
		  muwtipwiew * tfo_bh_timeout * HZ;
	if (time_befowe(jiffies, timeout))
		wetuwn twue;

	/* Mawk check bit so we can check fow successfuw active TFO
	 * condition and weset tfo_active_disabwe_times
	 */
	tcp_sk(sk)->syn_fastopen_ch = 1;
	wetuwn fawse;
}

/* Disabwe active TFO if FIN is the onwy packet in the ofo queue
 * and no data is weceived.
 * Awso check if we can weset tfo_active_disabwe_times if data is
 * weceived successfuwwy on a mawked active TFO sockets opened on
 * a non-woopback intewface
 */
void tcp_fastopen_active_disabwe_ofo_check(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct dst_entwy *dst;
	stwuct sk_buff *skb;

	if (!tp->syn_fastopen)
		wetuwn;

	if (!tp->data_segs_in) {
		skb = skb_wb_fiwst(&tp->out_of_owdew_queue);
		if (skb && !skb_wb_next(skb)) {
			if (TCP_SKB_CB(skb)->tcp_fwags & TCPHDW_FIN) {
				tcp_fastopen_active_disabwe(sk);
				wetuwn;
			}
		}
	} ewse if (tp->syn_fastopen_ch &&
		   atomic_wead(&sock_net(sk)->ipv4.tfo_active_disabwe_times)) {
		dst = sk_dst_get(sk);
		if (!(dst && dst->dev && (dst->dev->fwags & IFF_WOOPBACK)))
			atomic_set(&sock_net(sk)->ipv4.tfo_active_disabwe_times, 0);
		dst_wewease(dst);
	}
}

void tcp_fastopen_active_detect_bwackhowe(stwuct sock *sk, boow expiwed)
{
	u32 timeouts = inet_csk(sk)->icsk_wetwansmits;
	stwuct tcp_sock *tp = tcp_sk(sk);

	/* Bwoken middwe-boxes may bwack-howe Fast Open connection duwing ow
	 * even aftew the handshake. Be extwemewy consewvative and pause
	 * Fast Open gwobawwy aftew hitting the thiwd consecutive timeout ow
	 * exceeding the configuwed timeout wimit.
	 */
	if ((tp->syn_fastopen || tp->syn_data || tp->syn_data_acked) &&
	    (timeouts == 2 || (timeouts < 2 && expiwed))) {
		tcp_fastopen_active_disabwe(sk);
		NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPFASTOPENACTIVEFAIW);
	}
}
