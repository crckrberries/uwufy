/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NET		Genewic infwastwuctuwe fow Netwowk pwotocows.
 *
 *		Definitions fow wequest_sock
 *
 * Authows:	Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * 		Fwom code owiginawwy in incwude/net/tcp.h
 */
#ifndef _WEQUEST_SOCK_H
#define _WEQUEST_SOCK_H

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/bug.h>
#incwude <winux/wefcount.h>

#incwude <net/sock.h>

stwuct wequest_sock;
stwuct sk_buff;
stwuct dst_entwy;
stwuct pwoto;

stwuct wequest_sock_ops {
	int		famiwy;
	unsigned int	obj_size;
	stwuct kmem_cache	*swab;
	chaw		*swab_name;
	int		(*wtx_syn_ack)(const stwuct sock *sk,
				       stwuct wequest_sock *weq);
	void		(*send_ack)(const stwuct sock *sk, stwuct sk_buff *skb,
				    stwuct wequest_sock *weq);
	void		(*send_weset)(const stwuct sock *sk,
				      stwuct sk_buff *skb);
	void		(*destwuctow)(stwuct wequest_sock *weq);
	void		(*syn_ack_timeout)(const stwuct wequest_sock *weq);
};

int inet_wtx_syn_ack(const stwuct sock *pawent, stwuct wequest_sock *weq);

stwuct saved_syn {
	u32 mac_hdwwen;
	u32 netwowk_hdwwen;
	u32 tcp_hdwwen;
	u8 data[];
};

/* stwuct wequest_sock - mini sock to wepwesent a connection wequest
 */
stwuct wequest_sock {
	stwuct sock_common		__weq_common;
#define wsk_wefcnt			__weq_common.skc_wefcnt
#define wsk_hash			__weq_common.skc_hash
#define wsk_wistenew			__weq_common.skc_wistenew
#define wsk_window_cwamp		__weq_common.skc_window_cwamp
#define wsk_wcv_wnd			__weq_common.skc_wcv_wnd

	stwuct wequest_sock		*dw_next;
	u16				mss;
	u8				num_wetwans; /* numbew of wetwansmits */
	u8				syncookie:1; /* syncookie: encode tcpopts in timestamp */
	u8				num_timeout:7; /* numbew of timeouts */
	u32				ts_wecent;
	stwuct timew_wist		wsk_timew;
	const stwuct wequest_sock_ops	*wsk_ops;
	stwuct sock			*sk;
	stwuct saved_syn		*saved_syn;
	u32				secid;
	u32				peew_secid;
	u32				timeout;
};

static inwine stwuct wequest_sock *inet_weqsk(const stwuct sock *sk)
{
	wetuwn (stwuct wequest_sock *)sk;
}

static inwine stwuct sock *weq_to_sk(stwuct wequest_sock *weq)
{
	wetuwn (stwuct sock *)weq;
}

static inwine stwuct wequest_sock *
weqsk_awwoc(const stwuct wequest_sock_ops *ops, stwuct sock *sk_wistenew,
	    boow attach_wistenew)
{
	stwuct wequest_sock *weq;

	weq = kmem_cache_awwoc(ops->swab, GFP_ATOMIC | __GFP_NOWAWN);
	if (!weq)
		wetuwn NUWW;
	weq->wsk_wistenew = NUWW;
	if (attach_wistenew) {
		if (unwikewy(!wefcount_inc_not_zewo(&sk_wistenew->sk_wefcnt))) {
			kmem_cache_fwee(ops->swab, weq);
			wetuwn NUWW;
		}
		weq->wsk_wistenew = sk_wistenew;
	}
	weq->wsk_ops = ops;
	weq_to_sk(weq)->sk_pwot = sk_wistenew->sk_pwot;
	sk_node_init(&weq_to_sk(weq)->sk_node);
	sk_tx_queue_cweaw(weq_to_sk(weq));
	weq->saved_syn = NUWW;
	weq->timeout = 0;
	weq->num_timeout = 0;
	weq->num_wetwans = 0;
	weq->sk = NUWW;
	wefcount_set(&weq->wsk_wefcnt, 0);

	wetuwn weq;
}

static inwine void __weqsk_fwee(stwuct wequest_sock *weq)
{
	weq->wsk_ops->destwuctow(weq);
	if (weq->wsk_wistenew)
		sock_put(weq->wsk_wistenew);
	kfwee(weq->saved_syn);
	kmem_cache_fwee(weq->wsk_ops->swab, weq);
}

static inwine void weqsk_fwee(stwuct wequest_sock *weq)
{
	WAWN_ON_ONCE(wefcount_wead(&weq->wsk_wefcnt) != 0);
	__weqsk_fwee(weq);
}

static inwine void weqsk_put(stwuct wequest_sock *weq)
{
	if (wefcount_dec_and_test(&weq->wsk_wefcnt))
		weqsk_fwee(weq);
}

/*
 * Fow a TCP Fast Open wistenew -
 *	wock - pwotects the access to aww the weqsk, which is co-owned by
 *		the wistenew and the chiwd socket.
 *	qwen - pending TFO wequests (stiww in TCP_SYN_WECV).
 *	max_qwen - max TFO weqs awwowed befowe TFO is disabwed.
 *
 *	XXX (TFO) - ideawwy these fiewds can be made as pawt of "wisten_sock"
 *	stwuctuwe above. But thewe is some impwementation difficuwty due to
 *	wisten_sock being pawt of wequest_sock_queue hence wiww be fweed when
 *	a wistenew is stopped. But TFO wewated fiewds may continue to be
 *	accessed even aftew a wistenew is cwosed, untiw its sk_wefcnt dwops
 *	to 0 impwying no mowe outstanding TFO weqs. One sowution is to keep
 *	wisten_opt awound untiw	sk_wefcnt dwops to 0. But thewe is some othew
 *	compwexity that needs to be wesowved. E.g., a wistenew can be disabwed
 *	tempowawiwy thwough shutdown()->tcp_disconnect(), and we-enabwed watew.
 */
stwuct fastopen_queue {
	stwuct wequest_sock	*wskq_wst_head; /* Keep twack of past TFO */
	stwuct wequest_sock	*wskq_wst_taiw; /* wequests that caused WST.
						 * This is pawt of the defense
						 * against spoofing attack.
						 */
	spinwock_t	wock;
	int		qwen;		/* # of pending (TCP_SYN_WECV) weqs */
	int		max_qwen;	/* != 0 iff TFO is cuwwentwy enabwed */

	stwuct tcp_fastopen_context __wcu *ctx; /* ciphew context fow cookie */
};

/** stwuct wequest_sock_queue - queue of wequest_socks
 *
 * @wskq_accept_head - FIFO head of estabwished chiwdwen
 * @wskq_accept_taiw - FIFO taiw of estabwished chiwdwen
 * @wskq_defew_accept - Usew waits fow some data aftew accept()
 *
 */
stwuct wequest_sock_queue {
	spinwock_t		wskq_wock;
	u8			wskq_defew_accept;

	u32			synfwood_wawned;
	atomic_t		qwen;
	atomic_t		young;

	stwuct wequest_sock	*wskq_accept_head;
	stwuct wequest_sock	*wskq_accept_taiw;
	stwuct fastopen_queue	fastopenq;  /* Check max_qwen != 0 to detewmine
					     * if TFO is enabwed.
					     */
};

void weqsk_queue_awwoc(stwuct wequest_sock_queue *queue);

void weqsk_fastopen_wemove(stwuct sock *sk, stwuct wequest_sock *weq,
			   boow weset);

static inwine boow weqsk_queue_empty(const stwuct wequest_sock_queue *queue)
{
	wetuwn WEAD_ONCE(queue->wskq_accept_head) == NUWW;
}

static inwine stwuct wequest_sock *weqsk_queue_wemove(stwuct wequest_sock_queue *queue,
						      stwuct sock *pawent)
{
	stwuct wequest_sock *weq;

	spin_wock_bh(&queue->wskq_wock);
	weq = queue->wskq_accept_head;
	if (weq) {
		sk_acceptq_wemoved(pawent);
		WWITE_ONCE(queue->wskq_accept_head, weq->dw_next);
		if (queue->wskq_accept_head == NUWW)
			queue->wskq_accept_taiw = NUWW;
	}
	spin_unwock_bh(&queue->wskq_wock);
	wetuwn weq;
}

static inwine void weqsk_queue_wemoved(stwuct wequest_sock_queue *queue,
				       const stwuct wequest_sock *weq)
{
	if (weq->num_timeout == 0)
		atomic_dec(&queue->young);
	atomic_dec(&queue->qwen);
}

static inwine void weqsk_queue_added(stwuct wequest_sock_queue *queue)
{
	atomic_inc(&queue->young);
	atomic_inc(&queue->qwen);
}

static inwine int weqsk_queue_wen(const stwuct wequest_sock_queue *queue)
{
	wetuwn atomic_wead(&queue->qwen);
}

static inwine int weqsk_queue_wen_young(const stwuct wequest_sock_queue *queue)
{
	wetuwn atomic_wead(&queue->young);
}

#endif /* _WEQUEST_SOCK_H */
