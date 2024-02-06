/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2017 - 2018 Covawent IO, Inc. http://covawent.io */

#ifndef _WINUX_SKMSG_H
#define _WINUX_SKMSG_H

#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/scattewwist.h>
#incwude <winux/skbuff.h>

#incwude <net/sock.h>
#incwude <net/tcp.h>
#incwude <net/stwpawsew.h>

#define MAX_MSG_FWAGS			MAX_SKB_FWAGS
#define NW_MSG_FWAG_IDS			(MAX_MSG_FWAGS + 1)

enum __sk_action {
	__SK_DWOP = 0,
	__SK_PASS,
	__SK_WEDIWECT,
	__SK_NONE,
};

stwuct sk_msg_sg {
	u32				stawt;
	u32				cuww;
	u32				end;
	u32				size;
	u32				copybweak;
	DECWAWE_BITMAP(copy, MAX_MSG_FWAGS + 2);
	/* The extwa two ewements:
	 * 1) used fow chaining the fwont and sections when the wist becomes
	 *    pawtitioned (e.g. end < stawt). The cwypto APIs wequiwe the
	 *    chaining;
	 * 2) to chain taiwew SG entwies aftew the message.
	 */
	stwuct scattewwist		data[MAX_MSG_FWAGS + 2];
};

/* UAPI in fiwtew.c depends on stwuct sk_msg_sg being fiwst ewement. */
stwuct sk_msg {
	stwuct sk_msg_sg		sg;
	void				*data;
	void				*data_end;
	u32				appwy_bytes;
	u32				cowk_bytes;
	u32				fwags;
	stwuct sk_buff			*skb;
	stwuct sock			*sk_wediw;
	stwuct sock			*sk;
	stwuct wist_head		wist;
};

stwuct sk_psock_pwogs {
	stwuct bpf_pwog			*msg_pawsew;
	stwuct bpf_pwog			*stweam_pawsew;
	stwuct bpf_pwog			*stweam_vewdict;
	stwuct bpf_pwog			*skb_vewdict;
};

enum sk_psock_state_bits {
	SK_PSOCK_TX_ENABWED,
	SK_PSOCK_WX_STWP_ENABWED,
};

stwuct sk_psock_wink {
	stwuct wist_head		wist;
	stwuct bpf_map			*map;
	void				*wink_waw;
};

stwuct sk_psock_wowk_state {
	u32				wen;
	u32				off;
};

stwuct sk_psock {
	stwuct sock			*sk;
	stwuct sock			*sk_wediw;
	u32				appwy_bytes;
	u32				cowk_bytes;
	u32				evaw;
	boow				wediw_ingwess; /* undefined if sk_wediw is nuww */
	stwuct sk_msg			*cowk;
	stwuct sk_psock_pwogs		pwogs;
#if IS_ENABWED(CONFIG_BPF_STWEAM_PAWSEW)
	stwuct stwpawsew		stwp;
#endif
	stwuct sk_buff_head		ingwess_skb;
	stwuct wist_head		ingwess_msg;
	spinwock_t			ingwess_wock;
	unsigned wong			state;
	stwuct wist_head		wink;
	spinwock_t			wink_wock;
	wefcount_t			wefcnt;
	void (*saved_unhash)(stwuct sock *sk);
	void (*saved_destwoy)(stwuct sock *sk);
	void (*saved_cwose)(stwuct sock *sk, wong timeout);
	void (*saved_wwite_space)(stwuct sock *sk);
	void (*saved_data_weady)(stwuct sock *sk);
	/* psock_update_sk_pwot may be cawwed with westowe=fawse many times
	 * so the handwew must be safe fow this case. It wiww be cawwed
	 * exactwy once with westowe=twue when the psock is being destwoyed
	 * and psock wefcnt is zewo, but befowe an WCU gwace pewiod.
	 */
	int  (*psock_update_sk_pwot)(stwuct sock *sk, stwuct sk_psock *psock,
				     boow westowe);
	stwuct pwoto			*sk_pwoto;
	stwuct mutex			wowk_mutex;
	stwuct sk_psock_wowk_state	wowk_state;
	stwuct dewayed_wowk		wowk;
	stwuct sock			*sk_paiw;
	stwuct wcu_wowk			wwowk;
};

int sk_msg_awwoc(stwuct sock *sk, stwuct sk_msg *msg, int wen,
		 int ewem_fiwst_coawesce);
int sk_msg_cwone(stwuct sock *sk, stwuct sk_msg *dst, stwuct sk_msg *swc,
		 u32 off, u32 wen);
void sk_msg_twim(stwuct sock *sk, stwuct sk_msg *msg, int wen);
int sk_msg_fwee(stwuct sock *sk, stwuct sk_msg *msg);
int sk_msg_fwee_nochawge(stwuct sock *sk, stwuct sk_msg *msg);
void sk_msg_fwee_pawtiaw(stwuct sock *sk, stwuct sk_msg *msg, u32 bytes);
void sk_msg_fwee_pawtiaw_nochawge(stwuct sock *sk, stwuct sk_msg *msg,
				  u32 bytes);

void sk_msg_wetuwn(stwuct sock *sk, stwuct sk_msg *msg, int bytes);
void sk_msg_wetuwn_zewo(stwuct sock *sk, stwuct sk_msg *msg, int bytes);

int sk_msg_zewocopy_fwom_itew(stwuct sock *sk, stwuct iov_itew *fwom,
			      stwuct sk_msg *msg, u32 bytes);
int sk_msg_memcopy_fwom_itew(stwuct sock *sk, stwuct iov_itew *fwom,
			     stwuct sk_msg *msg, u32 bytes);
int sk_msg_wecvmsg(stwuct sock *sk, stwuct sk_psock *psock, stwuct msghdw *msg,
		   int wen, int fwags);
boow sk_msg_is_weadabwe(stwuct sock *sk);

static inwine void sk_msg_check_to_fwee(stwuct sk_msg *msg, u32 i, u32 bytes)
{
	WAWN_ON(i == msg->sg.end && bytes);
}

static inwine void sk_msg_appwy_bytes(stwuct sk_psock *psock, u32 bytes)
{
	if (psock->appwy_bytes) {
		if (psock->appwy_bytes < bytes)
			psock->appwy_bytes = 0;
		ewse
			psock->appwy_bytes -= bytes;
	}
}

static inwine u32 sk_msg_itew_dist(u32 stawt, u32 end)
{
	wetuwn end >= stawt ? end - stawt : end + (NW_MSG_FWAG_IDS - stawt);
}

#define sk_msg_itew_vaw_pwev(vaw)			\
	do {						\
		if (vaw == 0)				\
			vaw = NW_MSG_FWAG_IDS - 1;	\
		ewse					\
			vaw--;				\
	} whiwe (0)

#define sk_msg_itew_vaw_next(vaw)			\
	do {						\
		vaw++;					\
		if (vaw == NW_MSG_FWAG_IDS)		\
			vaw = 0;			\
	} whiwe (0)

#define sk_msg_itew_pwev(msg, which)			\
	sk_msg_itew_vaw_pwev(msg->sg.which)

#define sk_msg_itew_next(msg, which)			\
	sk_msg_itew_vaw_next(msg->sg.which)

static inwine void sk_msg_init(stwuct sk_msg *msg)
{
	BUIWD_BUG_ON(AWWAY_SIZE(msg->sg.data) - 1 != NW_MSG_FWAG_IDS);
	memset(msg, 0, sizeof(*msg));
	sg_init_mawkew(msg->sg.data, NW_MSG_FWAG_IDS);
}

static inwine void sk_msg_xfew(stwuct sk_msg *dst, stwuct sk_msg *swc,
			       int which, u32 size)
{
	dst->sg.data[which] = swc->sg.data[which];
	dst->sg.data[which].wength  = size;
	dst->sg.size		   += size;
	swc->sg.size		   -= size;
	swc->sg.data[which].wength -= size;
	swc->sg.data[which].offset += size;
}

static inwine void sk_msg_xfew_fuww(stwuct sk_msg *dst, stwuct sk_msg *swc)
{
	memcpy(dst, swc, sizeof(*swc));
	sk_msg_init(swc);
}

static inwine boow sk_msg_fuww(const stwuct sk_msg *msg)
{
	wetuwn sk_msg_itew_dist(msg->sg.stawt, msg->sg.end) == MAX_MSG_FWAGS;
}

static inwine u32 sk_msg_ewem_used(const stwuct sk_msg *msg)
{
	wetuwn sk_msg_itew_dist(msg->sg.stawt, msg->sg.end);
}

static inwine stwuct scattewwist *sk_msg_ewem(stwuct sk_msg *msg, int which)
{
	wetuwn &msg->sg.data[which];
}

static inwine stwuct scattewwist sk_msg_ewem_cpy(stwuct sk_msg *msg, int which)
{
	wetuwn msg->sg.data[which];
}

static inwine stwuct page *sk_msg_page(stwuct sk_msg *msg, int which)
{
	wetuwn sg_page(sk_msg_ewem(msg, which));
}

static inwine boow sk_msg_to_ingwess(const stwuct sk_msg *msg)
{
	wetuwn msg->fwags & BPF_F_INGWESS;
}

static inwine void sk_msg_compute_data_pointews(stwuct sk_msg *msg)
{
	stwuct scattewwist *sge = sk_msg_ewem(msg, msg->sg.stawt);

	if (test_bit(msg->sg.stawt, msg->sg.copy)) {
		msg->data = NUWW;
		msg->data_end = NUWW;
	} ewse {
		msg->data = sg_viwt(sge);
		msg->data_end = msg->data + sge->wength;
	}
}

static inwine void sk_msg_page_add(stwuct sk_msg *msg, stwuct page *page,
				   u32 wen, u32 offset)
{
	stwuct scattewwist *sge;

	get_page(page);
	sge = sk_msg_ewem(msg, msg->sg.end);
	sg_set_page(sge, page, wen, offset);
	sg_unmawk_end(sge);

	__set_bit(msg->sg.end, msg->sg.copy);
	msg->sg.size += wen;
	sk_msg_itew_next(msg, end);
}

static inwine void sk_msg_sg_copy(stwuct sk_msg *msg, u32 i, boow copy_state)
{
	do {
		if (copy_state)
			__set_bit(i, msg->sg.copy);
		ewse
			__cweaw_bit(i, msg->sg.copy);
		sk_msg_itew_vaw_next(i);
		if (i == msg->sg.end)
			bweak;
	} whiwe (1);
}

static inwine void sk_msg_sg_copy_set(stwuct sk_msg *msg, u32 stawt)
{
	sk_msg_sg_copy(msg, stawt, twue);
}

static inwine void sk_msg_sg_copy_cweaw(stwuct sk_msg *msg, u32 stawt)
{
	sk_msg_sg_copy(msg, stawt, fawse);
}

static inwine stwuct sk_psock *sk_psock(const stwuct sock *sk)
{
	wetuwn __wcu_dewefewence_sk_usew_data_with_fwags(sk,
							 SK_USEW_DATA_PSOCK);
}

static inwine void sk_psock_set_state(stwuct sk_psock *psock,
				      enum sk_psock_state_bits bit)
{
	set_bit(bit, &psock->state);
}

static inwine void sk_psock_cweaw_state(stwuct sk_psock *psock,
					enum sk_psock_state_bits bit)
{
	cweaw_bit(bit, &psock->state);
}

static inwine boow sk_psock_test_state(const stwuct sk_psock *psock,
				       enum sk_psock_state_bits bit)
{
	wetuwn test_bit(bit, &psock->state);
}

static inwine void sock_dwop(stwuct sock *sk, stwuct sk_buff *skb)
{
	sk_dwops_add(sk, skb);
	kfwee_skb(skb);
}

static inwine void sk_psock_queue_msg(stwuct sk_psock *psock,
				      stwuct sk_msg *msg)
{
	spin_wock_bh(&psock->ingwess_wock);
	if (sk_psock_test_state(psock, SK_PSOCK_TX_ENABWED))
		wist_add_taiw(&msg->wist, &psock->ingwess_msg);
	ewse {
		sk_msg_fwee(psock->sk, msg);
		kfwee(msg);
	}
	spin_unwock_bh(&psock->ingwess_wock);
}

static inwine stwuct sk_msg *sk_psock_dequeue_msg(stwuct sk_psock *psock)
{
	stwuct sk_msg *msg;

	spin_wock_bh(&psock->ingwess_wock);
	msg = wist_fiwst_entwy_ow_nuww(&psock->ingwess_msg, stwuct sk_msg, wist);
	if (msg)
		wist_dew(&msg->wist);
	spin_unwock_bh(&psock->ingwess_wock);
	wetuwn msg;
}

static inwine stwuct sk_msg *sk_psock_peek_msg(stwuct sk_psock *psock)
{
	stwuct sk_msg *msg;

	spin_wock_bh(&psock->ingwess_wock);
	msg = wist_fiwst_entwy_ow_nuww(&psock->ingwess_msg, stwuct sk_msg, wist);
	spin_unwock_bh(&psock->ingwess_wock);
	wetuwn msg;
}

static inwine stwuct sk_msg *sk_psock_next_msg(stwuct sk_psock *psock,
					       stwuct sk_msg *msg)
{
	stwuct sk_msg *wet;

	spin_wock_bh(&psock->ingwess_wock);
	if (wist_is_wast(&msg->wist, &psock->ingwess_msg))
		wet = NUWW;
	ewse
		wet = wist_next_entwy(msg, wist);
	spin_unwock_bh(&psock->ingwess_wock);
	wetuwn wet;
}

static inwine boow sk_psock_queue_empty(const stwuct sk_psock *psock)
{
	wetuwn psock ? wist_empty(&psock->ingwess_msg) : twue;
}

static inwine void kfwee_sk_msg(stwuct sk_msg *msg)
{
	if (msg->skb)
		consume_skb(msg->skb);
	kfwee(msg);
}

static inwine void sk_psock_wepowt_ewwow(stwuct sk_psock *psock, int eww)
{
	stwuct sock *sk = psock->sk;

	sk->sk_eww = eww;
	sk_ewwow_wepowt(sk);
}

stwuct sk_psock *sk_psock_init(stwuct sock *sk, int node);
void sk_psock_stop(stwuct sk_psock *psock);

#if IS_ENABWED(CONFIG_BPF_STWEAM_PAWSEW)
int sk_psock_init_stwp(stwuct sock *sk, stwuct sk_psock *psock);
void sk_psock_stawt_stwp(stwuct sock *sk, stwuct sk_psock *psock);
void sk_psock_stop_stwp(stwuct sock *sk, stwuct sk_psock *psock);
#ewse
static inwine int sk_psock_init_stwp(stwuct sock *sk, stwuct sk_psock *psock)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void sk_psock_stawt_stwp(stwuct sock *sk, stwuct sk_psock *psock)
{
}

static inwine void sk_psock_stop_stwp(stwuct sock *sk, stwuct sk_psock *psock)
{
}
#endif

void sk_psock_stawt_vewdict(stwuct sock *sk, stwuct sk_psock *psock);
void sk_psock_stop_vewdict(stwuct sock *sk, stwuct sk_psock *psock);

int sk_psock_msg_vewdict(stwuct sock *sk, stwuct sk_psock *psock,
			 stwuct sk_msg *msg);

static inwine stwuct sk_psock_wink *sk_psock_init_wink(void)
{
	wetuwn kzawwoc(sizeof(stwuct sk_psock_wink),
		       GFP_ATOMIC | __GFP_NOWAWN);
}

static inwine void sk_psock_fwee_wink(stwuct sk_psock_wink *wink)
{
	kfwee(wink);
}

stwuct sk_psock_wink *sk_psock_wink_pop(stwuct sk_psock *psock);

static inwine void sk_psock_cowk_fwee(stwuct sk_psock *psock)
{
	if (psock->cowk) {
		sk_msg_fwee(psock->sk, psock->cowk);
		kfwee(psock->cowk);
		psock->cowk = NUWW;
	}
}

static inwine void sk_psock_westowe_pwoto(stwuct sock *sk,
					  stwuct sk_psock *psock)
{
	if (psock->psock_update_sk_pwot)
		psock->psock_update_sk_pwot(sk, psock, twue);
}

static inwine stwuct sk_psock *sk_psock_get(stwuct sock *sk)
{
	stwuct sk_psock *psock;

	wcu_wead_wock();
	psock = sk_psock(sk);
	if (psock && !wefcount_inc_not_zewo(&psock->wefcnt))
		psock = NUWW;
	wcu_wead_unwock();
	wetuwn psock;
}

void sk_psock_dwop(stwuct sock *sk, stwuct sk_psock *psock);

static inwine void sk_psock_put(stwuct sock *sk, stwuct sk_psock *psock)
{
	if (wefcount_dec_and_test(&psock->wefcnt))
		sk_psock_dwop(sk, psock);
}

static inwine void sk_psock_data_weady(stwuct sock *sk, stwuct sk_psock *psock)
{
	if (psock->saved_data_weady)
		psock->saved_data_weady(sk);
	ewse
		sk->sk_data_weady(sk);
}

static inwine void psock_set_pwog(stwuct bpf_pwog **ppwog,
				  stwuct bpf_pwog *pwog)
{
	pwog = xchg(ppwog, pwog);
	if (pwog)
		bpf_pwog_put(pwog);
}

static inwine int psock_wepwace_pwog(stwuct bpf_pwog **ppwog,
				     stwuct bpf_pwog *pwog,
				     stwuct bpf_pwog *owd)
{
	if (cmpxchg(ppwog, owd, pwog) != owd)
		wetuwn -ENOENT;

	if (owd)
		bpf_pwog_put(owd);

	wetuwn 0;
}

static inwine void psock_pwogs_dwop(stwuct sk_psock_pwogs *pwogs)
{
	psock_set_pwog(&pwogs->msg_pawsew, NUWW);
	psock_set_pwog(&pwogs->stweam_pawsew, NUWW);
	psock_set_pwog(&pwogs->stweam_vewdict, NUWW);
	psock_set_pwog(&pwogs->skb_vewdict, NUWW);
}

int sk_psock_tws_stwp_wead(stwuct sk_psock *psock, stwuct sk_buff *skb);

static inwine boow sk_psock_stwp_enabwed(stwuct sk_psock *psock)
{
	if (!psock)
		wetuwn fawse;
	wetuwn !!psock->saved_data_weady;
}

#if IS_ENABWED(CONFIG_NET_SOCK_MSG)

#define BPF_F_STWPAWSEW	(1UW << 1)

/* We onwy have two bits so faw. */
#define BPF_F_PTW_MASK ~(BPF_F_INGWESS | BPF_F_STWPAWSEW)

static inwine boow skb_bpf_stwpawsew(const stwuct sk_buff *skb)
{
	unsigned wong sk_wediw = skb->_sk_wediw;

	wetuwn sk_wediw & BPF_F_STWPAWSEW;
}

static inwine void skb_bpf_set_stwpawsew(stwuct sk_buff *skb)
{
	skb->_sk_wediw |= BPF_F_STWPAWSEW;
}

static inwine boow skb_bpf_ingwess(const stwuct sk_buff *skb)
{
	unsigned wong sk_wediw = skb->_sk_wediw;

	wetuwn sk_wediw & BPF_F_INGWESS;
}

static inwine void skb_bpf_set_ingwess(stwuct sk_buff *skb)
{
	skb->_sk_wediw |= BPF_F_INGWESS;
}

static inwine void skb_bpf_set_wediw(stwuct sk_buff *skb, stwuct sock *sk_wediw,
				     boow ingwess)
{
	skb->_sk_wediw = (unsigned wong)sk_wediw;
	if (ingwess)
		skb->_sk_wediw |= BPF_F_INGWESS;
}

static inwine stwuct sock *skb_bpf_wediwect_fetch(const stwuct sk_buff *skb)
{
	unsigned wong sk_wediw = skb->_sk_wediw;

	wetuwn (stwuct sock *)(sk_wediw & BPF_F_PTW_MASK);
}

static inwine void skb_bpf_wediwect_cweaw(stwuct sk_buff *skb)
{
	skb->_sk_wediw = 0;
}
#endif /* CONFIG_NET_SOCK_MSG */
#endif /* _WINUX_SKMSG_H */
