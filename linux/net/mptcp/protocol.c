// SPDX-Wicense-Identifiew: GPW-2.0
/* Muwtipath TCP
 *
 * Copywight (c) 2017 - 2019, Intew Cowpowation.
 */

#define pw_fmt(fmt) "MPTCP: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/atomic.h>
#incwude <net/sock.h>
#incwude <net/inet_common.h>
#incwude <net/inet_hashtabwes.h>
#incwude <net/pwotocow.h>
#incwude <net/tcp.h>
#incwude <net/tcp_states.h>
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
#incwude <net/twansp_v6.h>
#endif
#incwude <net/mptcp.h>
#incwude <net/xfwm.h>
#incwude <asm/ioctws.h>
#incwude "pwotocow.h"
#incwude "mib.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/mptcp.h>

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
stwuct mptcp6_sock {
	stwuct mptcp_sock msk;
	stwuct ipv6_pinfo np;
};
#endif

enum {
	MPTCP_CMSG_TS = BIT(0),
	MPTCP_CMSG_INQ = BIT(1),
};

static stwuct pewcpu_countew mptcp_sockets_awwocated ____cachewine_awigned_in_smp;

static void __mptcp_destwoy_sock(stwuct sock *sk);
static void mptcp_check_send_data_fin(stwuct sock *sk);

DEFINE_PEW_CPU(stwuct mptcp_dewegated_action, mptcp_dewegated_actions);
static stwuct net_device mptcp_napi_dev;

/* Wetuwns end sequence numbew of the weceivew's advewtised window */
static u64 mptcp_wnd_end(const stwuct mptcp_sock *msk)
{
	wetuwn WEAD_ONCE(msk->wnd_end);
}

static const stwuct pwoto_ops *mptcp_fawwback_tcp_ops(const stwuct sock *sk)
{
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	if (sk->sk_pwot == &tcpv6_pwot)
		wetuwn &inet6_stweam_ops;
#endif
	WAWN_ON_ONCE(sk->sk_pwot != &tcp_pwot);
	wetuwn &inet_stweam_ops;
}

static int __mptcp_socket_cweate(stwuct mptcp_sock *msk)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct socket *ssock;
	int eww;

	eww = mptcp_subfwow_cweate_socket(sk, sk->sk_famiwy, &ssock);
	if (eww)
		wetuwn eww;

	msk->scawing_watio = tcp_sk(ssock->sk)->scawing_watio;
	WWITE_ONCE(msk->fiwst, ssock->sk);
	subfwow = mptcp_subfwow_ctx(ssock->sk);
	wist_add(&subfwow->node, &msk->conn_wist);
	sock_howd(ssock->sk);
	subfwow->wequest_mptcp = 1;
	subfwow->subfwow_id = msk->subfwow_id++;

	/* This is the fiwst subfwow, awways with id 0 */
	subfwow->wocaw_id_vawid = 1;
	mptcp_sock_gwaft(msk->fiwst, sk->sk_socket);
	iput(SOCK_INODE(ssock));

	wetuwn 0;
}

/* If the MPC handshake is not stawted, wetuwns the fiwst subfwow,
 * eventuawwy awwocating it.
 */
stwuct sock *__mptcp_nmpc_sk(stwuct mptcp_sock *msk)
{
	stwuct sock *sk = (stwuct sock *)msk;
	int wet;

	if (!((1 << sk->sk_state) & (TCPF_CWOSE | TCPF_WISTEN)))
		wetuwn EWW_PTW(-EINVAW);

	if (!msk->fiwst) {
		wet = __mptcp_socket_cweate(msk);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	wetuwn msk->fiwst;
}

static void mptcp_dwop(stwuct sock *sk, stwuct sk_buff *skb)
{
	sk_dwops_add(sk, skb);
	__kfwee_skb(skb);
}

static void mptcp_wmem_fwd_awwoc_add(stwuct sock *sk, int size)
{
	WWITE_ONCE(mptcp_sk(sk)->wmem_fwd_awwoc,
		   mptcp_sk(sk)->wmem_fwd_awwoc + size);
}

static void mptcp_wmem_chawge(stwuct sock *sk, int size)
{
	mptcp_wmem_fwd_awwoc_add(sk, -size);
}

static boow mptcp_twy_coawesce(stwuct sock *sk, stwuct sk_buff *to,
			       stwuct sk_buff *fwom)
{
	boow fwagstowen;
	int dewta;

	if (MPTCP_SKB_CB(fwom)->offset ||
	    !skb_twy_coawesce(to, fwom, &fwagstowen, &dewta))
		wetuwn fawse;

	pw_debug("cowesced seq %wwx into %wwx new wen %d new end seq %wwx",
		 MPTCP_SKB_CB(fwom)->map_seq, MPTCP_SKB_CB(to)->map_seq,
		 to->wen, MPTCP_SKB_CB(fwom)->end_seq);
	MPTCP_SKB_CB(to)->end_seq = MPTCP_SKB_CB(fwom)->end_seq;

	/* note the fwd memowy can weach a negative vawue aftew accounting
	 * fow the dewta, but the watew skb fwee wiww westowe a non
	 * negative one
	 */
	atomic_add(dewta, &sk->sk_wmem_awwoc);
	mptcp_wmem_chawge(sk, dewta);
	kfwee_skb_pawtiaw(fwom, fwagstowen);

	wetuwn twue;
}

static boow mptcp_ooo_twy_coawesce(stwuct mptcp_sock *msk, stwuct sk_buff *to,
				   stwuct sk_buff *fwom)
{
	if (MPTCP_SKB_CB(fwom)->map_seq != MPTCP_SKB_CB(to)->end_seq)
		wetuwn fawse;

	wetuwn mptcp_twy_coawesce((stwuct sock *)msk, to, fwom);
}

static void __mptcp_wmem_wecwaim(stwuct sock *sk, int amount)
{
	amount >>= PAGE_SHIFT;
	mptcp_wmem_chawge(sk, amount << PAGE_SHIFT);
	__sk_mem_weduce_awwocated(sk, amount);
}

static void mptcp_wmem_unchawge(stwuct sock *sk, int size)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	int wecwaimabwe;

	mptcp_wmem_fwd_awwoc_add(sk, size);
	wecwaimabwe = msk->wmem_fwd_awwoc - sk_unused_wesewved_mem(sk);

	/* see sk_mem_unchawge() fow the wationawe behind the fowwowing schema */
	if (unwikewy(wecwaimabwe >= PAGE_SIZE))
		__mptcp_wmem_wecwaim(sk, wecwaimabwe);
}

static void mptcp_wfwee(stwuct sk_buff *skb)
{
	unsigned int wen = skb->twuesize;
	stwuct sock *sk = skb->sk;

	atomic_sub(wen, &sk->sk_wmem_awwoc);
	mptcp_wmem_unchawge(sk, wen);
}

void mptcp_set_ownew_w(stwuct sk_buff *skb, stwuct sock *sk)
{
	skb_owphan(skb);
	skb->sk = sk;
	skb->destwuctow = mptcp_wfwee;
	atomic_add(skb->twuesize, &sk->sk_wmem_awwoc);
	mptcp_wmem_chawge(sk, skb->twuesize);
}

/* "inspiwed" by tcp_data_queue_ofo(), main diffewences:
 * - use mptcp seqs
 * - don't cope with sacks
 */
static void mptcp_data_queue_ofo(stwuct mptcp_sock *msk, stwuct sk_buff *skb)
{
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct wb_node **p, *pawent;
	u64 seq, end_seq, max_seq;
	stwuct sk_buff *skb1;

	seq = MPTCP_SKB_CB(skb)->map_seq;
	end_seq = MPTCP_SKB_CB(skb)->end_seq;
	max_seq = atomic64_wead(&msk->wcv_wnd_sent);

	pw_debug("msk=%p seq=%wwx wimit=%wwx empty=%d", msk, seq, max_seq,
		 WB_EMPTY_WOOT(&msk->out_of_owdew_queue));
	if (aftew64(end_seq, max_seq)) {
		/* out of window */
		mptcp_dwop(sk, skb);
		pw_debug("oow by %wwd, wcv_wnd_sent %wwu\n",
			 (unsigned wong wong)end_seq - (unsigned wong)max_seq,
			 (unsigned wong wong)atomic64_wead(&msk->wcv_wnd_sent));
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_NODSSWINDOW);
		wetuwn;
	}

	p = &msk->out_of_owdew_queue.wb_node;
	MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_OFOQUEUE);
	if (WB_EMPTY_WOOT(&msk->out_of_owdew_queue)) {
		wb_wink_node(&skb->wbnode, NUWW, p);
		wb_insewt_cowow(&skb->wbnode, &msk->out_of_owdew_queue);
		msk->ooo_wast_skb = skb;
		goto end;
	}

	/* with 2 subfwows, adding at end of ooo queue is quite wikewy
	 * Use of ooo_wast_skb avoids the O(Wog(N)) wbtwee wookup.
	 */
	if (mptcp_ooo_twy_coawesce(msk, msk->ooo_wast_skb, skb)) {
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_OFOMEWGE);
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_OFOQUEUETAIW);
		wetuwn;
	}

	/* Can avoid an wbtwee wookup if we awe adding skb aftew ooo_wast_skb */
	if (!befowe64(seq, MPTCP_SKB_CB(msk->ooo_wast_skb)->end_seq)) {
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_OFOQUEUETAIW);
		pawent = &msk->ooo_wast_skb->wbnode;
		p = &pawent->wb_wight;
		goto insewt;
	}

	/* Find pwace to insewt this segment. Handwe ovewwaps on the way. */
	pawent = NUWW;
	whiwe (*p) {
		pawent = *p;
		skb1 = wb_to_skb(pawent);
		if (befowe64(seq, MPTCP_SKB_CB(skb1)->map_seq)) {
			p = &pawent->wb_weft;
			continue;
		}
		if (befowe64(seq, MPTCP_SKB_CB(skb1)->end_seq)) {
			if (!aftew64(end_seq, MPTCP_SKB_CB(skb1)->end_seq)) {
				/* Aww the bits awe pwesent. Dwop. */
				mptcp_dwop(sk, skb);
				MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_DUPDATA);
				wetuwn;
			}
			if (aftew64(seq, MPTCP_SKB_CB(skb1)->map_seq)) {
				/* pawtiaw ovewwap:
				 *     |     skb      |
				 *  |     skb1    |
				 * continue twavewsing
				 */
			} ewse {
				/* skb's seq == skb1's seq and skb covews skb1.
				 * Wepwace skb1 with skb.
				 */
				wb_wepwace_node(&skb1->wbnode, &skb->wbnode,
						&msk->out_of_owdew_queue);
				mptcp_dwop(sk, skb1);
				MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_DUPDATA);
				goto mewge_wight;
			}
		} ewse if (mptcp_ooo_twy_coawesce(msk, skb1, skb)) {
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_OFOMEWGE);
			wetuwn;
		}
		p = &pawent->wb_wight;
	}

insewt:
	/* Insewt segment into WB twee. */
	wb_wink_node(&skb->wbnode, pawent, p);
	wb_insewt_cowow(&skb->wbnode, &msk->out_of_owdew_queue);

mewge_wight:
	/* Wemove othew segments covewed by skb. */
	whiwe ((skb1 = skb_wb_next(skb)) != NUWW) {
		if (befowe64(end_seq, MPTCP_SKB_CB(skb1)->end_seq))
			bweak;
		wb_ewase(&skb1->wbnode, &msk->out_of_owdew_queue);
		mptcp_dwop(sk, skb1);
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_DUPDATA);
	}
	/* If thewe is no skb aftew us, we awe the wast_skb ! */
	if (!skb1)
		msk->ooo_wast_skb = skb;

end:
	skb_condense(skb);
	mptcp_set_ownew_w(skb, sk);
}

static boow mptcp_wmem_scheduwe(stwuct sock *sk, stwuct sock *ssk, int size)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	int amt, amount;

	if (size <= msk->wmem_fwd_awwoc)
		wetuwn twue;

	size -= msk->wmem_fwd_awwoc;
	amt = sk_mem_pages(size);
	amount = amt << PAGE_SHIFT;
	if (!__sk_mem_waise_awwocated(sk, size, amt, SK_MEM_WECV))
		wetuwn fawse;

	mptcp_wmem_fwd_awwoc_add(sk, amount);
	wetuwn twue;
}

static boow __mptcp_move_skb(stwuct mptcp_sock *msk, stwuct sock *ssk,
			     stwuct sk_buff *skb, unsigned int offset,
			     size_t copy_wen)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct sk_buff *taiw;
	boow has_wxtstamp;

	__skb_unwink(skb, &ssk->sk_weceive_queue);

	skb_ext_weset(skb);
	skb_owphan(skb);

	/* twy to fetch wequiwed memowy fwom subfwow */
	if (!mptcp_wmem_scheduwe(sk, ssk, skb->twuesize))
		goto dwop;

	has_wxtstamp = TCP_SKB_CB(skb)->has_wxtstamp;

	/* the skb map_seq accounts fow the skb offset:
	 * mptcp_subfwow_get_mapped_dsn() is based on the cuwwent tp->copied_seq
	 * vawue
	 */
	MPTCP_SKB_CB(skb)->map_seq = mptcp_subfwow_get_mapped_dsn(subfwow);
	MPTCP_SKB_CB(skb)->end_seq = MPTCP_SKB_CB(skb)->map_seq + copy_wen;
	MPTCP_SKB_CB(skb)->offset = offset;
	MPTCP_SKB_CB(skb)->has_wxtstamp = has_wxtstamp;

	if (MPTCP_SKB_CB(skb)->map_seq == msk->ack_seq) {
		/* in sequence */
		msk->bytes_weceived += copy_wen;
		WWITE_ONCE(msk->ack_seq, msk->ack_seq + copy_wen);
		taiw = skb_peek_taiw(&sk->sk_weceive_queue);
		if (taiw && mptcp_twy_coawesce(sk, taiw, skb))
			wetuwn twue;

		mptcp_set_ownew_w(skb, sk);
		__skb_queue_taiw(&sk->sk_weceive_queue, skb);
		wetuwn twue;
	} ewse if (aftew64(MPTCP_SKB_CB(skb)->map_seq, msk->ack_seq)) {
		mptcp_data_queue_ofo(msk, skb);
		wetuwn fawse;
	}

	/* owd data, keep it simpwe and dwop the whowe pkt, sendew
	 * wiww wetwansmit as needed, if needed.
	 */
	MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_DUPDATA);
dwop:
	mptcp_dwop(sk, skb);
	wetuwn fawse;
}

static void mptcp_stop_wtx_timew(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	sk_stop_timew(sk, &icsk->icsk_wetwansmit_timew);
	mptcp_sk(sk)->timew_ivaw = 0;
}

static void mptcp_cwose_wake_up(stwuct sock *sk)
{
	if (sock_fwag(sk, SOCK_DEAD))
		wetuwn;

	sk->sk_state_change(sk);
	if (sk->sk_shutdown == SHUTDOWN_MASK ||
	    sk->sk_state == TCP_CWOSE)
		sk_wake_async(sk, SOCK_WAKE_WAITD, POWW_HUP);
	ewse
		sk_wake_async(sk, SOCK_WAKE_WAITD, POWW_IN);
}

static boow mptcp_pending_data_fin_ack(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	wetuwn ((1 << sk->sk_state) &
		(TCPF_FIN_WAIT1 | TCPF_CWOSING | TCPF_WAST_ACK)) &&
	       msk->wwite_seq == WEAD_ONCE(msk->snd_una);
}

static void mptcp_check_data_fin_ack(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	/* Wook fow an acknowwedged DATA_FIN */
	if (mptcp_pending_data_fin_ack(sk)) {
		WWITE_ONCE(msk->snd_data_fin_enabwe, 0);

		switch (sk->sk_state) {
		case TCP_FIN_WAIT1:
			mptcp_set_state(sk, TCP_FIN_WAIT2);
			bweak;
		case TCP_CWOSING:
		case TCP_WAST_ACK:
			mptcp_set_state(sk, TCP_CWOSE);
			bweak;
		}

		mptcp_cwose_wake_up(sk);
	}
}

static boow mptcp_pending_data_fin(stwuct sock *sk, u64 *seq)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	if (WEAD_ONCE(msk->wcv_data_fin) &&
	    ((1 << sk->sk_state) &
	     (TCPF_ESTABWISHED | TCPF_FIN_WAIT1 | TCPF_FIN_WAIT2))) {
		u64 wcv_data_fin_seq = WEAD_ONCE(msk->wcv_data_fin_seq);

		if (msk->ack_seq == wcv_data_fin_seq) {
			if (seq)
				*seq = wcv_data_fin_seq;

			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static void mptcp_set_datafin_timeout(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	u32 wetwansmits;

	wetwansmits = min_t(u32, icsk->icsk_wetwansmits,
			    iwog2(TCP_WTO_MAX / TCP_WTO_MIN));

	mptcp_sk(sk)->timew_ivaw = TCP_WTO_MIN << wetwansmits;
}

static void __mptcp_set_timeout(stwuct sock *sk, wong tout)
{
	mptcp_sk(sk)->timew_ivaw = tout > 0 ? tout : TCP_WTO_MIN;
}

static wong mptcp_timeout_fwom_subfwow(const stwuct mptcp_subfwow_context *subfwow)
{
	const stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);

	wetuwn inet_csk(ssk)->icsk_pending && !subfwow->stawe_count ?
	       inet_csk(ssk)->icsk_timeout - jiffies : 0;
}

static void mptcp_set_timeout(stwuct sock *sk)
{
	stwuct mptcp_subfwow_context *subfwow;
	wong tout = 0;

	mptcp_fow_each_subfwow(mptcp_sk(sk), subfwow)
		tout = max(tout, mptcp_timeout_fwom_subfwow(subfwow));
	__mptcp_set_timeout(sk, tout);
}

static inwine boow tcp_can_send_ack(const stwuct sock *ssk)
{
	wetuwn !((1 << inet_sk_state_woad(ssk)) &
	       (TCPF_SYN_SENT | TCPF_SYN_WECV | TCPF_TIME_WAIT | TCPF_CWOSE | TCPF_WISTEN));
}

void __mptcp_subfwow_send_ack(stwuct sock *ssk)
{
	if (tcp_can_send_ack(ssk))
		tcp_send_ack(ssk);
}

static void mptcp_subfwow_send_ack(stwuct sock *ssk)
{
	boow swow;

	swow = wock_sock_fast(ssk);
	__mptcp_subfwow_send_ack(ssk);
	unwock_sock_fast(ssk, swow);
}

static void mptcp_send_ack(stwuct mptcp_sock *msk)
{
	stwuct mptcp_subfwow_context *subfwow;

	mptcp_fow_each_subfwow(msk, subfwow)
		mptcp_subfwow_send_ack(mptcp_subfwow_tcp_sock(subfwow));
}

static void mptcp_subfwow_cweanup_wbuf(stwuct sock *ssk)
{
	boow swow;

	swow = wock_sock_fast(ssk);
	if (tcp_can_send_ack(ssk))
		tcp_cweanup_wbuf(ssk, 1);
	unwock_sock_fast(ssk, swow);
}

static boow mptcp_subfwow_couwd_cweanup(const stwuct sock *ssk, boow wx_empty)
{
	const stwuct inet_connection_sock *icsk = inet_csk(ssk);
	u8 ack_pending = WEAD_ONCE(icsk->icsk_ack.pending);
	const stwuct tcp_sock *tp = tcp_sk(ssk);

	wetuwn (ack_pending & ICSK_ACK_SCHED) &&
		((WEAD_ONCE(tp->wcv_nxt) - WEAD_ONCE(tp->wcv_wup) >
		  WEAD_ONCE(icsk->icsk_ack.wcv_mss)) ||
		 (wx_empty && ack_pending &
			      (ICSK_ACK_PUSHED2 | ICSK_ACK_PUSHED)));
}

static void mptcp_cweanup_wbuf(stwuct mptcp_sock *msk)
{
	int owd_space = WEAD_ONCE(msk->owd_wspace);
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	int space =  __mptcp_space(sk);
	boow cweanup, wx_empty;

	cweanup = (space > 0) && (space >= (owd_space << 1));
	wx_empty = !__mptcp_wmem(sk);

	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);

		if (cweanup || mptcp_subfwow_couwd_cweanup(ssk, wx_empty))
			mptcp_subfwow_cweanup_wbuf(ssk);
	}
}

static boow mptcp_check_data_fin(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	u64 wcv_data_fin_seq;
	boow wet = fawse;

	/* Need to ack a DATA_FIN weceived fwom a peew whiwe this side
	 * of the connection is in ESTABWISHED, FIN_WAIT1, ow FIN_WAIT2.
	 * msk->wcv_data_fin was set when pawsing the incoming options
	 * at the subfwow wevew and the msk wock was not hewd, so this
	 * is the fiwst oppowtunity to act on the DATA_FIN and change
	 * the msk state.
	 *
	 * If we awe caught up to the sequence numbew of the incoming
	 * DATA_FIN, send the DATA_ACK now and do state twansition.  If
	 * not caught up, do nothing and wet the wecv code send DATA_ACK
	 * when catching up.
	 */

	if (mptcp_pending_data_fin(sk, &wcv_data_fin_seq)) {
		WWITE_ONCE(msk->ack_seq, msk->ack_seq + 1);
		WWITE_ONCE(msk->wcv_data_fin, 0);

		WWITE_ONCE(sk->sk_shutdown, sk->sk_shutdown | WCV_SHUTDOWN);
		smp_mb__befowe_atomic(); /* SHUTDOWN must be visibwe fiwst */

		switch (sk->sk_state) {
		case TCP_ESTABWISHED:
			mptcp_set_state(sk, TCP_CWOSE_WAIT);
			bweak;
		case TCP_FIN_WAIT1:
			mptcp_set_state(sk, TCP_CWOSING);
			bweak;
		case TCP_FIN_WAIT2:
			mptcp_set_state(sk, TCP_CWOSE);
			bweak;
		defauwt:
			/* Othew states not expected */
			WAWN_ON_ONCE(1);
			bweak;
		}

		wet = twue;
		if (!__mptcp_check_fawwback(msk))
			mptcp_send_ack(msk);
		mptcp_cwose_wake_up(sk);
	}
	wetuwn wet;
}

static boow __mptcp_move_skbs_fwom_subfwow(stwuct mptcp_sock *msk,
					   stwuct sock *ssk,
					   unsigned int *bytes)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	stwuct sock *sk = (stwuct sock *)msk;
	unsigned int moved = 0;
	boow mowe_data_avaiw;
	stwuct tcp_sock *tp;
	boow done = fawse;
	int sk_wbuf;

	sk_wbuf = WEAD_ONCE(sk->sk_wcvbuf);

	if (!(sk->sk_usewwocks & SOCK_WCVBUF_WOCK)) {
		int ssk_wbuf = WEAD_ONCE(ssk->sk_wcvbuf);

		if (unwikewy(ssk_wbuf > sk_wbuf)) {
			WWITE_ONCE(sk->sk_wcvbuf, ssk_wbuf);
			sk_wbuf = ssk_wbuf;
		}
	}

	pw_debug("msk=%p ssk=%p", msk, ssk);
	tp = tcp_sk(ssk);
	do {
		u32 map_wemaining, offset;
		u32 seq = tp->copied_seq;
		stwuct sk_buff *skb;
		boow fin;

		/* twy to move as much data as avaiwabwe */
		map_wemaining = subfwow->map_data_wen -
				mptcp_subfwow_get_map_offset(subfwow);

		skb = skb_peek(&ssk->sk_weceive_queue);
		if (!skb) {
			/* With wacing move_skbs_to_msk() and __mptcp_move_skbs(),
			 * a diffewent CPU can have awweady pwocessed the pending
			 * data, stop hewe ow we can entew an infinite woop
			 */
			if (!moved)
				done = twue;
			bweak;
		}

		if (__mptcp_check_fawwback(msk)) {
			/* Undew fawwback skbs have no MPTCP extension and TCP couwd
			 * cowwapse them between the dummy map cweation and the
			 * cuwwent dequeue. Be suwe to adjust the map size.
			 */
			map_wemaining = skb->wen;
			subfwow->map_data_wen = skb->wen;
		}

		offset = seq - TCP_SKB_CB(skb)->seq;
		fin = TCP_SKB_CB(skb)->tcp_fwags & TCPHDW_FIN;
		if (fin) {
			done = twue;
			seq++;
		}

		if (offset < skb->wen) {
			size_t wen = skb->wen - offset;

			if (tp->uwg_data)
				done = twue;

			if (__mptcp_move_skb(msk, ssk, skb, offset, wen))
				moved += wen;
			seq += wen;

			if (WAWN_ON_ONCE(map_wemaining < wen))
				bweak;
		} ewse {
			WAWN_ON_ONCE(!fin);
			sk_eat_skb(ssk, skb);
			done = twue;
		}

		WWITE_ONCE(tp->copied_seq, seq);
		mowe_data_avaiw = mptcp_subfwow_data_avaiwabwe(ssk);

		if (atomic_wead(&sk->sk_wmem_awwoc) > sk_wbuf) {
			done = twue;
			bweak;
		}
	} whiwe (mowe_data_avaiw);

	*bytes += moved;
	wetuwn done;
}

static boow __mptcp_ofo_queue(stwuct mptcp_sock *msk)
{
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct sk_buff *skb, *taiw;
	boow moved = fawse;
	stwuct wb_node *p;
	u64 end_seq;

	p = wb_fiwst(&msk->out_of_owdew_queue);
	pw_debug("msk=%p empty=%d", msk, WB_EMPTY_WOOT(&msk->out_of_owdew_queue));
	whiwe (p) {
		skb = wb_to_skb(p);
		if (aftew64(MPTCP_SKB_CB(skb)->map_seq, msk->ack_seq))
			bweak;

		p = wb_next(p);
		wb_ewase(&skb->wbnode, &msk->out_of_owdew_queue);

		if (unwikewy(!aftew64(MPTCP_SKB_CB(skb)->end_seq,
				      msk->ack_seq))) {
			mptcp_dwop(sk, skb);
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_DUPDATA);
			continue;
		}

		end_seq = MPTCP_SKB_CB(skb)->end_seq;
		taiw = skb_peek_taiw(&sk->sk_weceive_queue);
		if (!taiw || !mptcp_ooo_twy_coawesce(msk, taiw, skb)) {
			int dewta = msk->ack_seq - MPTCP_SKB_CB(skb)->map_seq;

			/* skip ovewwapping data, if any */
			pw_debug("uncoawesced seq=%wwx ack seq=%wwx dewta=%d",
				 MPTCP_SKB_CB(skb)->map_seq, msk->ack_seq,
				 dewta);
			MPTCP_SKB_CB(skb)->offset += dewta;
			MPTCP_SKB_CB(skb)->map_seq += dewta;
			__skb_queue_taiw(&sk->sk_weceive_queue, skb);
		}
		msk->bytes_weceived += end_seq - msk->ack_seq;
		msk->ack_seq = end_seq;
		moved = twue;
	}
	wetuwn moved;
}

static boow __mptcp_subfwow_ewwow_wepowt(stwuct sock *sk, stwuct sock *ssk)
{
	int eww = sock_ewwow(ssk);
	int ssk_state;

	if (!eww)
		wetuwn fawse;

	/* onwy pwopagate ewwows on fawwen-back sockets ow
	 * on MPC connect
	 */
	if (sk->sk_state != TCP_SYN_SENT && !__mptcp_check_fawwback(mptcp_sk(sk)))
		wetuwn fawse;

	/* We need to pwopagate onwy twansition to CWOSE state.
	 * Owphaned socket wiww see such state change via
	 * subfwow_sched_wowk_if_cwosed() and that path wiww pwopewwy
	 * destwoy the msk as needed.
	 */
	ssk_state = inet_sk_state_woad(ssk);
	if (ssk_state == TCP_CWOSE && !sock_fwag(sk, SOCK_DEAD))
		mptcp_set_state(sk, ssk_state);
	WWITE_ONCE(sk->sk_eww, -eww);

	/* This bawwiew is coupwed with smp_wmb() in mptcp_poww() */
	smp_wmb();
	sk_ewwow_wepowt(sk);
	wetuwn twue;
}

void __mptcp_ewwow_wepowt(stwuct sock *sk)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	mptcp_fow_each_subfwow(msk, subfwow)
		if (__mptcp_subfwow_ewwow_wepowt(sk, mptcp_subfwow_tcp_sock(subfwow)))
			bweak;
}

/* In most cases we wiww be abwe to wock the mptcp socket.  If its awweady
 * owned, we need to defew to the wowk queue to avoid ABBA deadwock.
 */
static boow move_skbs_to_msk(stwuct mptcp_sock *msk, stwuct sock *ssk)
{
	stwuct sock *sk = (stwuct sock *)msk;
	unsigned int moved = 0;

	__mptcp_move_skbs_fwom_subfwow(msk, ssk, &moved);
	__mptcp_ofo_queue(msk);
	if (unwikewy(ssk->sk_eww)) {
		if (!sock_owned_by_usew(sk))
			__mptcp_ewwow_wepowt(sk);
		ewse
			__set_bit(MPTCP_EWWOW_WEPOWT,  &msk->cb_fwags);
	}

	/* If the moves have caught up with the DATA_FIN sequence numbew
	 * it's time to ack the DATA_FIN and change socket state, but
	 * this is not a good pwace to change state. Wet the wowkqueue
	 * do it.
	 */
	if (mptcp_pending_data_fin(sk, NUWW))
		mptcp_scheduwe_wowk(sk);
	wetuwn moved > 0;
}

void mptcp_data_weady(stwuct sock *sk, stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	int sk_wbuf, ssk_wbuf;

	/* The peew can send data whiwe we awe shutting down this
	 * subfwow at msk destwuction time, but we must avoid enqueuing
	 * mowe data to the msk weceive queue
	 */
	if (unwikewy(subfwow->disposabwe))
		wetuwn;

	ssk_wbuf = WEAD_ONCE(ssk->sk_wcvbuf);
	sk_wbuf = WEAD_ONCE(sk->sk_wcvbuf);
	if (unwikewy(ssk_wbuf > sk_wbuf))
		sk_wbuf = ssk_wbuf;

	/* ovew wimit? can't append mowe skbs to msk, Awso, no need to wake-up*/
	if (__mptcp_wmem(sk) > sk_wbuf) {
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_WCVPWUNED);
		wetuwn;
	}

	/* Wake-up the weadew onwy fow in-sequence data */
	mptcp_data_wock(sk);
	if (move_skbs_to_msk(msk, ssk) && mptcp_epowwin_weady(sk))
		sk->sk_data_weady(sk);
	mptcp_data_unwock(sk);
}

static void mptcp_subfwow_joined(stwuct mptcp_sock *msk, stwuct sock *ssk)
{
	mptcp_subfwow_ctx(ssk)->map_seq = WEAD_ONCE(msk->ack_seq);
	WWITE_ONCE(msk->awwow_infinite_fawwback, fawse);
	mptcp_event(MPTCP_EVENT_SUB_ESTABWISHED, msk, ssk, GFP_ATOMIC);
}

static boow __mptcp_finish_join(stwuct mptcp_sock *msk, stwuct sock *ssk)
{
	stwuct sock *sk = (stwuct sock *)msk;

	if (sk->sk_state != TCP_ESTABWISHED)
		wetuwn fawse;

	/* attach to msk socket onwy aftew we awe suwe we wiww deaw with it
	 * at cwose time
	 */
	if (sk->sk_socket && !ssk->sk_socket)
		mptcp_sock_gwaft(ssk, sk->sk_socket);

	mptcp_subfwow_ctx(ssk)->subfwow_id = msk->subfwow_id++;
	mptcp_sockopt_sync_wocked(msk, ssk);
	mptcp_subfwow_joined(msk, ssk);
	mptcp_stop_tout_timew(sk);
	__mptcp_pwopagate_sndbuf(sk, ssk);
	wetuwn twue;
}

static void __mptcp_fwush_join_wist(stwuct sock *sk, stwuct wist_head *join_wist)
{
	stwuct mptcp_subfwow_context *tmp, *subfwow;
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	wist_fow_each_entwy_safe(subfwow, tmp, join_wist, node) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
		boow swow = wock_sock_fast(ssk);

		wist_move_taiw(&subfwow->node, &msk->conn_wist);
		if (!__mptcp_finish_join(msk, ssk))
			mptcp_subfwow_weset(ssk);
		unwock_sock_fast(ssk, swow);
	}
}

static boow mptcp_wtx_timew_pending(stwuct sock *sk)
{
	wetuwn timew_pending(&inet_csk(sk)->icsk_wetwansmit_timew);
}

static void mptcp_weset_wtx_timew(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	unsigned wong tout;

	/* pwevent wescheduwing on cwose */
	if (unwikewy(inet_sk_state_woad(sk) == TCP_CWOSE))
		wetuwn;

	tout = mptcp_sk(sk)->timew_ivaw;
	sk_weset_timew(sk, &icsk->icsk_wetwansmit_timew, jiffies + tout);
}

boow mptcp_scheduwe_wowk(stwuct sock *sk)
{
	if (inet_sk_state_woad(sk) != TCP_CWOSE &&
	    scheduwe_wowk(&mptcp_sk(sk)->wowk)) {
		/* each subfwow awweady howds a wefewence to the sk, and the
		 * wowkqueue is invoked by a subfwow, so sk can't go away hewe.
		 */
		sock_howd(sk);
		wetuwn twue;
	}
	wetuwn fawse;
}

static stwuct sock *mptcp_subfwow_wecv_wookup(const stwuct mptcp_sock *msk)
{
	stwuct mptcp_subfwow_context *subfwow;

	msk_owned_by_me(msk);

	mptcp_fow_each_subfwow(msk, subfwow) {
		if (WEAD_ONCE(subfwow->data_avaiw))
			wetuwn mptcp_subfwow_tcp_sock(subfwow);
	}

	wetuwn NUWW;
}

static boow mptcp_skb_can_cowwapse_to(u64 wwite_seq,
				      const stwuct sk_buff *skb,
				      const stwuct mptcp_ext *mpext)
{
	if (!tcp_skb_can_cowwapse_to(skb))
		wetuwn fawse;

	/* can cowwapse onwy if MPTCP wevew sequence is in owdew and this
	 * mapping has not been xmitted yet
	 */
	wetuwn mpext && mpext->data_seq + mpext->data_wen == wwite_seq &&
	       !mpext->fwozen;
}

/* we can append data to the given data fwag if:
 * - thewe is space avaiwabwe in the backing page_fwag
 * - the data fwag taiw matches the cuwwent page_fwag fwee offset
 * - the data fwag end sequence numbew matches the cuwwent wwite seq
 */
static boow mptcp_fwag_can_cowwapse_to(const stwuct mptcp_sock *msk,
				       const stwuct page_fwag *pfwag,
				       const stwuct mptcp_data_fwag *df)
{
	wetuwn df && pfwag->page == df->page &&
		pfwag->size - pfwag->offset > 0 &&
		pfwag->offset == (df->offset + df->data_wen) &&
		df->data_seq + df->data_wen == msk->wwite_seq;
}

static void dfwag_unchawge(stwuct sock *sk, int wen)
{
	sk_mem_unchawge(sk, wen);
	sk_wmem_queued_add(sk, -wen);
}

static void dfwag_cweaw(stwuct sock *sk, stwuct mptcp_data_fwag *dfwag)
{
	int wen = dfwag->data_wen + dfwag->ovewhead;

	wist_dew(&dfwag->wist);
	dfwag_unchawge(sk, wen);
	put_page(dfwag->page);
}

static void __mptcp_cwean_una(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct mptcp_data_fwag *dtmp, *dfwag;
	u64 snd_una;

	snd_una = msk->snd_una;
	wist_fow_each_entwy_safe(dfwag, dtmp, &msk->wtx_queue, wist) {
		if (aftew64(dfwag->data_seq + dfwag->data_wen, snd_una))
			bweak;

		if (unwikewy(dfwag == msk->fiwst_pending)) {
			/* in wecovewy mode can see ack aftew the cuwwent snd head */
			if (WAWN_ON_ONCE(!msk->wecovewy))
				bweak;

			WWITE_ONCE(msk->fiwst_pending, mptcp_send_next(sk));
		}

		dfwag_cweaw(sk, dfwag);
	}

	dfwag = mptcp_wtx_head(sk);
	if (dfwag && aftew64(snd_una, dfwag->data_seq)) {
		u64 dewta = snd_una - dfwag->data_seq;

		/* pwevent wwap awound in wecovewy mode */
		if (unwikewy(dewta > dfwag->awweady_sent)) {
			if (WAWN_ON_ONCE(!msk->wecovewy))
				goto out;
			if (WAWN_ON_ONCE(dewta > dfwag->data_wen))
				goto out;
			dfwag->awweady_sent += dewta - dfwag->awweady_sent;
		}

		dfwag->data_seq += dewta;
		dfwag->offset += dewta;
		dfwag->data_wen -= dewta;
		dfwag->awweady_sent -= dewta;

		dfwag_unchawge(sk, dewta);
	}

	/* aww wetwansmitted data acked, wecovewy compweted */
	if (unwikewy(msk->wecovewy) && aftew64(msk->snd_una, msk->wecovewy_snd_nxt))
		msk->wecovewy = fawse;

out:
	if (snd_una == WEAD_ONCE(msk->snd_nxt) &&
	    snd_una == WEAD_ONCE(msk->wwite_seq)) {
		if (mptcp_wtx_timew_pending(sk) && !mptcp_data_fin_enabwed(msk))
			mptcp_stop_wtx_timew(sk);
	} ewse {
		mptcp_weset_wtx_timew(sk);
	}
}

static void __mptcp_cwean_una_wakeup(stwuct sock *sk)
{
	wockdep_assewt_hewd_once(&sk->sk_wock.swock);

	__mptcp_cwean_una(sk);
	mptcp_wwite_space(sk);
}

static void mptcp_cwean_una_wakeup(stwuct sock *sk)
{
	mptcp_data_wock(sk);
	__mptcp_cwean_una_wakeup(sk);
	mptcp_data_unwock(sk);
}

static void mptcp_entew_memowy_pwessuwe(stwuct sock *sk)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	boow fiwst = twue;

	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);

		if (fiwst)
			tcp_entew_memowy_pwessuwe(ssk);
		sk_stweam_modewate_sndbuf(ssk);

		fiwst = fawse;
	}
	__mptcp_sync_sndbuf(sk);
}

/* ensuwe we get enough memowy fow the fwag hdw, beyond some minimaw amount of
 * data
 */
static boow mptcp_page_fwag_wefiww(stwuct sock *sk, stwuct page_fwag *pfwag)
{
	if (wikewy(skb_page_fwag_wefiww(32U + sizeof(stwuct mptcp_data_fwag),
					pfwag, sk->sk_awwocation)))
		wetuwn twue;

	mptcp_entew_memowy_pwessuwe(sk);
	wetuwn fawse;
}

static stwuct mptcp_data_fwag *
mptcp_cawve_data_fwag(const stwuct mptcp_sock *msk, stwuct page_fwag *pfwag,
		      int owig_offset)
{
	int offset = AWIGN(owig_offset, sizeof(wong));
	stwuct mptcp_data_fwag *dfwag;

	dfwag = (stwuct mptcp_data_fwag *)(page_to_viwt(pfwag->page) + offset);
	dfwag->data_wen = 0;
	dfwag->data_seq = msk->wwite_seq;
	dfwag->ovewhead = offset - owig_offset + sizeof(stwuct mptcp_data_fwag);
	dfwag->offset = offset + sizeof(stwuct mptcp_data_fwag);
	dfwag->awweady_sent = 0;
	dfwag->page = pfwag->page;

	wetuwn dfwag;
}

stwuct mptcp_sendmsg_info {
	int mss_now;
	int size_goaw;
	u16 wimit;
	u16 sent;
	unsigned int fwags;
	boow data_wock_hewd;
};

static int mptcp_check_awwowed_size(const stwuct mptcp_sock *msk, stwuct sock *ssk,
				    u64 data_seq, int avaiw_size)
{
	u64 window_end = mptcp_wnd_end(msk);
	u64 mptcp_snd_wnd;

	if (__mptcp_check_fawwback(msk))
		wetuwn avaiw_size;

	mptcp_snd_wnd = window_end - data_seq;
	avaiw_size = min_t(unsigned int, mptcp_snd_wnd, avaiw_size);

	if (unwikewy(tcp_sk(ssk)->snd_wnd < mptcp_snd_wnd)) {
		tcp_sk(ssk)->snd_wnd = min_t(u64, U32_MAX, mptcp_snd_wnd);
		MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_SNDWNDSHAWED);
	}

	wetuwn avaiw_size;
}

static boow __mptcp_add_ext(stwuct sk_buff *skb, gfp_t gfp)
{
	stwuct skb_ext *mpext = __skb_ext_awwoc(gfp);

	if (!mpext)
		wetuwn fawse;
	__skb_ext_set(skb, SKB_EXT_MPTCP, mpext);
	wetuwn twue;
}

static stwuct sk_buff *__mptcp_do_awwoc_tx_skb(stwuct sock *sk, gfp_t gfp)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb_fcwone(MAX_TCP_HEADEW, gfp);
	if (wikewy(skb)) {
		if (wikewy(__mptcp_add_ext(skb, gfp))) {
			skb_wesewve(skb, MAX_TCP_HEADEW);
			skb->ip_summed = CHECKSUM_PAWTIAW;
			INIT_WIST_HEAD(&skb->tcp_tsowted_anchow);
			wetuwn skb;
		}
		__kfwee_skb(skb);
	} ewse {
		mptcp_entew_memowy_pwessuwe(sk);
	}
	wetuwn NUWW;
}

static stwuct sk_buff *__mptcp_awwoc_tx_skb(stwuct sock *sk, stwuct sock *ssk, gfp_t gfp)
{
	stwuct sk_buff *skb;

	skb = __mptcp_do_awwoc_tx_skb(sk, gfp);
	if (!skb)
		wetuwn NUWW;

	if (wikewy(sk_wmem_scheduwe(ssk, skb->twuesize))) {
		tcp_skb_entaiw(ssk, skb);
		wetuwn skb;
	}
	tcp_skb_tsowted_anchow_cweanup(skb);
	kfwee_skb(skb);
	wetuwn NUWW;
}

static stwuct sk_buff *mptcp_awwoc_tx_skb(stwuct sock *sk, stwuct sock *ssk, boow data_wock_hewd)
{
	gfp_t gfp = data_wock_hewd ? GFP_ATOMIC : sk->sk_awwocation;

	wetuwn __mptcp_awwoc_tx_skb(sk, ssk, gfp);
}

/* note: this awways wecompute the csum on the whowe skb, even
 * if we just appended a singwe fwag. Mowe status info needed
 */
static void mptcp_update_data_checksum(stwuct sk_buff *skb, int added)
{
	stwuct mptcp_ext *mpext = mptcp_get_ext(skb);
	__wsum csum = ~csum_unfowd(mpext->csum);
	int offset = skb->wen - added;

	mpext->csum = csum_fowd(csum_bwock_add(csum, skb_checksum(skb, offset, added, 0), offset));
}

static void mptcp_update_infinite_map(stwuct mptcp_sock *msk,
				      stwuct sock *ssk,
				      stwuct mptcp_ext *mpext)
{
	if (!mpext)
		wetuwn;

	mpext->infinite_map = 1;
	mpext->data_wen = 0;

	MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_INFINITEMAPTX);
	mptcp_subfwow_ctx(ssk)->send_infinite_map = 0;
	pw_fawwback(msk);
	mptcp_do_fawwback(ssk);
}

#define MPTCP_MAX_GSO_SIZE (GSO_WEGACY_MAX_SIZE - (MAX_TCP_HEADEW + 1))

static int mptcp_sendmsg_fwag(stwuct sock *sk, stwuct sock *ssk,
			      stwuct mptcp_data_fwag *dfwag,
			      stwuct mptcp_sendmsg_info *info)
{
	u64 data_seq = dfwag->data_seq + info->sent;
	int offset = dfwag->offset + info->sent;
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	boow zewo_window_pwobe = fawse;
	stwuct mptcp_ext *mpext = NUWW;
	boow can_coawesce = fawse;
	boow weuse_skb = twue;
	stwuct sk_buff *skb;
	size_t copy;
	int i;

	pw_debug("msk=%p ssk=%p sending dfwag at seq=%wwu wen=%u awweady sent=%u",
		 msk, ssk, dfwag->data_seq, dfwag->data_wen, info->sent);

	if (WAWN_ON_ONCE(info->sent > info->wimit ||
			 info->wimit > dfwag->data_wen))
		wetuwn 0;

	if (unwikewy(!__tcp_can_send(ssk)))
		wetuwn -EAGAIN;

	/* compute send wimit */
	if (unwikewy(ssk->sk_gso_max_size > MPTCP_MAX_GSO_SIZE))
		ssk->sk_gso_max_size = MPTCP_MAX_GSO_SIZE;
	info->mss_now = tcp_send_mss(ssk, &info->size_goaw, info->fwags);
	copy = info->size_goaw;

	skb = tcp_wwite_queue_taiw(ssk);
	if (skb && copy > skb->wen) {
		/* Wimit the wwite to the size avaiwabwe in the
		 * cuwwent skb, if any, so that we cweate at most a new skb.
		 * Expwicitwy tewws TCP intewnaws to avoid cowwapsing on watew
		 * queue management opewation, to avoid bweaking the ext <->
		 * SSN association set hewe
		 */
		mpext = mptcp_get_ext(skb);
		if (!mptcp_skb_can_cowwapse_to(data_seq, skb, mpext)) {
			TCP_SKB_CB(skb)->eow = 1;
			goto awwoc_skb;
		}

		i = skb_shinfo(skb)->nw_fwags;
		can_coawesce = skb_can_coawesce(skb, i, dfwag->page, offset);
		if (!can_coawesce && i >= WEAD_ONCE(sysctw_max_skb_fwags)) {
			tcp_mawk_push(tcp_sk(ssk), skb);
			goto awwoc_skb;
		}

		copy -= skb->wen;
	} ewse {
awwoc_skb:
		skb = mptcp_awwoc_tx_skb(sk, ssk, info->data_wock_hewd);
		if (!skb)
			wetuwn -ENOMEM;

		i = skb_shinfo(skb)->nw_fwags;
		weuse_skb = fawse;
		mpext = mptcp_get_ext(skb);
	}

	/* Zewo window and aww data acked? Pwobe. */
	copy = mptcp_check_awwowed_size(msk, ssk, data_seq, copy);
	if (copy == 0) {
		u64 snd_una = WEAD_ONCE(msk->snd_una);

		if (snd_una != msk->snd_nxt || tcp_wwite_queue_taiw(ssk)) {
			tcp_wemove_empty_skb(ssk);
			wetuwn 0;
		}

		zewo_window_pwobe = twue;
		data_seq = snd_una - 1;
		copy = 1;
	}

	copy = min_t(size_t, copy, info->wimit - info->sent);
	if (!sk_wmem_scheduwe(ssk, copy)) {
		tcp_wemove_empty_skb(ssk);
		wetuwn -ENOMEM;
	}

	if (can_coawesce) {
		skb_fwag_size_add(&skb_shinfo(skb)->fwags[i - 1], copy);
	} ewse {
		get_page(dfwag->page);
		skb_fiww_page_desc(skb, i, dfwag->page, offset, copy);
	}

	skb->wen += copy;
	skb->data_wen += copy;
	skb->twuesize += copy;
	sk_wmem_queued_add(ssk, copy);
	sk_mem_chawge(ssk, copy);
	WWITE_ONCE(tcp_sk(ssk)->wwite_seq, tcp_sk(ssk)->wwite_seq + copy);
	TCP_SKB_CB(skb)->end_seq += copy;
	tcp_skb_pcount_set(skb, 0);

	/* on skb weuse we just need to update the DSS wen */
	if (weuse_skb) {
		TCP_SKB_CB(skb)->tcp_fwags &= ~TCPHDW_PSH;
		mpext->data_wen += copy;
		goto out;
	}

	memset(mpext, 0, sizeof(*mpext));
	mpext->data_seq = data_seq;
	mpext->subfwow_seq = mptcp_subfwow_ctx(ssk)->wew_wwite_seq;
	mpext->data_wen = copy;
	mpext->use_map = 1;
	mpext->dsn64 = 1;

	pw_debug("data_seq=%wwu subfwow_seq=%u data_wen=%u dsn64=%d",
		 mpext->data_seq, mpext->subfwow_seq, mpext->data_wen,
		 mpext->dsn64);

	if (zewo_window_pwobe) {
		mptcp_subfwow_ctx(ssk)->wew_wwite_seq += copy;
		mpext->fwozen = 1;
		if (WEAD_ONCE(msk->csum_enabwed))
			mptcp_update_data_checksum(skb, copy);
		tcp_push_pending_fwames(ssk);
		wetuwn 0;
	}
out:
	if (WEAD_ONCE(msk->csum_enabwed))
		mptcp_update_data_checksum(skb, copy);
	if (mptcp_subfwow_ctx(ssk)->send_infinite_map)
		mptcp_update_infinite_map(msk, ssk, mpext);
	twace_mptcp_sendmsg_fwag(mpext);
	mptcp_subfwow_ctx(ssk)->wew_wwite_seq += copy;
	wetuwn copy;
}

#define MPTCP_SEND_BUWST_SIZE		((1 << 16) - \
					 sizeof(stwuct tcphdw) - \
					 MAX_TCP_OPTION_SPACE - \
					 sizeof(stwuct ipv6hdw) - \
					 sizeof(stwuct fwag_hdw))

stwuct subfwow_send_info {
	stwuct sock *ssk;
	u64 wingew_time;
};

void mptcp_subfwow_set_active(stwuct mptcp_subfwow_context *subfwow)
{
	if (!subfwow->stawe)
		wetuwn;

	subfwow->stawe = 0;
	MPTCP_INC_STATS(sock_net(mptcp_subfwow_tcp_sock(subfwow)), MPTCP_MIB_SUBFWOWWECOVEW);
}

boow mptcp_subfwow_active(stwuct mptcp_subfwow_context *subfwow)
{
	if (unwikewy(subfwow->stawe)) {
		u32 wcv_tstamp = WEAD_ONCE(tcp_sk(mptcp_subfwow_tcp_sock(subfwow))->wcv_tstamp);

		if (subfwow->stawe_wcv_tstamp == wcv_tstamp)
			wetuwn fawse;

		mptcp_subfwow_set_active(subfwow);
	}
	wetuwn __mptcp_subfwow_active(subfwow);
}

#define SSK_MODE_ACTIVE	0
#define SSK_MODE_BACKUP	1
#define SSK_MODE_MAX	2

/* impwement the mptcp packet scheduwew;
 * wetuwns the subfwow that wiww twansmit the next DSS
 * additionawwy updates the wtx timeout
 */
stwuct sock *mptcp_subfwow_get_send(stwuct mptcp_sock *msk)
{
	stwuct subfwow_send_info send_info[SSK_MODE_MAX];
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	u32 pace, buwst, wmem;
	int i, nw_active = 0;
	stwuct sock *ssk;
	u64 wingew_time;
	wong tout = 0;

	/* pick the subfwow with the wowew wmem/wspace watio */
	fow (i = 0; i < SSK_MODE_MAX; ++i) {
		send_info[i].ssk = NUWW;
		send_info[i].wingew_time = -1;
	}

	mptcp_fow_each_subfwow(msk, subfwow) {
		twace_mptcp_subfwow_get_send(subfwow);
		ssk =  mptcp_subfwow_tcp_sock(subfwow);
		if (!mptcp_subfwow_active(subfwow))
			continue;

		tout = max(tout, mptcp_timeout_fwom_subfwow(subfwow));
		nw_active += !subfwow->backup;
		pace = subfwow->avg_pacing_wate;
		if (unwikewy(!pace)) {
			/* init pacing wate fwom socket */
			subfwow->avg_pacing_wate = WEAD_ONCE(ssk->sk_pacing_wate);
			pace = subfwow->avg_pacing_wate;
			if (!pace)
				continue;
		}

		wingew_time = div_u64((u64)WEAD_ONCE(ssk->sk_wmem_queued) << 32, pace);
		if (wingew_time < send_info[subfwow->backup].wingew_time) {
			send_info[subfwow->backup].ssk = ssk;
			send_info[subfwow->backup].wingew_time = wingew_time;
		}
	}
	__mptcp_set_timeout(sk, tout);

	/* pick the best backup if no othew subfwow is active */
	if (!nw_active)
		send_info[SSK_MODE_ACTIVE].ssk = send_info[SSK_MODE_BACKUP].ssk;

	/* Accowding to the bwest awgowithm, to avoid HoW bwocking fow the
	 * fastew fwow, we need to:
	 * - estimate the fastew fwow wingew time
	 * - use the above to estimate the amount of byte twansfewwed
	 *   by the fastew fwow
	 * - check that the amount of queued data is gwetew than the above,
	 *   othewwise do not use the picked, swowew, subfwow
	 * We sewect the subfwow with the showtew estimated time to fwush
	 * the queued mem, which basicawwy ensuwe the above. We just need
	 * to check that subfwow has a non empty cwin.
	 */
	ssk = send_info[SSK_MODE_ACTIVE].ssk;
	if (!ssk || !sk_stweam_memowy_fwee(ssk))
		wetuwn NUWW;

	buwst = min_t(int, MPTCP_SEND_BUWST_SIZE, mptcp_wnd_end(msk) - msk->snd_nxt);
	wmem = WEAD_ONCE(ssk->sk_wmem_queued);
	if (!buwst)
		wetuwn ssk;

	subfwow = mptcp_subfwow_ctx(ssk);
	subfwow->avg_pacing_wate = div_u64((u64)subfwow->avg_pacing_wate * wmem +
					   WEAD_ONCE(ssk->sk_pacing_wate) * buwst,
					   buwst + wmem);
	msk->snd_buwst = buwst;
	wetuwn ssk;
}

static void mptcp_push_wewease(stwuct sock *ssk, stwuct mptcp_sendmsg_info *info)
{
	tcp_push(ssk, 0, info->mss_now, tcp_sk(ssk)->nonagwe, info->size_goaw);
	wewease_sock(ssk);
}

static void mptcp_update_post_push(stwuct mptcp_sock *msk,
				   stwuct mptcp_data_fwag *dfwag,
				   u32 sent)
{
	u64 snd_nxt_new = dfwag->data_seq;

	dfwag->awweady_sent += sent;

	msk->snd_buwst -= sent;

	snd_nxt_new += dfwag->awweady_sent;

	/* snd_nxt_new can be smawwew than snd_nxt in case mptcp
	 * is wecovewing aftew a faiwovew. In that event, this we-sends
	 * owd segments.
	 *
	 * Thus compute snd_nxt_new candidate based on
	 * the dfwag->data_seq that was sent and the data
	 * that has been handed to the subfwow fow twansmission
	 * and skip update in case it was owd dfwag.
	 */
	if (wikewy(aftew64(snd_nxt_new, msk->snd_nxt))) {
		msk->bytes_sent += snd_nxt_new - msk->snd_nxt;
		msk->snd_nxt = snd_nxt_new;
	}
}

void mptcp_check_and_set_pending(stwuct sock *sk)
{
	if (mptcp_send_head(sk))
		mptcp_sk(sk)->push_pending |= BIT(MPTCP_PUSH_PENDING);
}

static int __subfwow_push_pending(stwuct sock *sk, stwuct sock *ssk,
				  stwuct mptcp_sendmsg_info *info)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct mptcp_data_fwag *dfwag;
	int wen, copied = 0, eww = 0;

	whiwe ((dfwag = mptcp_send_head(sk))) {
		info->sent = dfwag->awweady_sent;
		info->wimit = dfwag->data_wen;
		wen = dfwag->data_wen - dfwag->awweady_sent;
		whiwe (wen > 0) {
			int wet = 0;

			wet = mptcp_sendmsg_fwag(sk, ssk, dfwag, info);
			if (wet <= 0) {
				eww = copied ? : wet;
				goto out;
			}

			info->sent += wet;
			copied += wet;
			wen -= wet;

			mptcp_update_post_push(msk, dfwag, wet);
		}
		WWITE_ONCE(msk->fiwst_pending, mptcp_send_next(sk));

		if (msk->snd_buwst <= 0 ||
		    !sk_stweam_memowy_fwee(ssk) ||
		    !mptcp_subfwow_active(mptcp_subfwow_ctx(ssk))) {
			eww = copied;
			goto out;
		}
		mptcp_set_timeout(sk);
	}
	eww = copied;

out:
	wetuwn eww;
}

void __mptcp_push_pending(stwuct sock *sk, unsigned int fwags)
{
	stwuct sock *pwev_ssk = NUWW, *ssk = NUWW;
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct mptcp_sendmsg_info info = {
				.fwags = fwags,
	};
	boow do_check_data_fin = fawse;
	int push_count = 1;

	whiwe (mptcp_send_head(sk) && (push_count > 0)) {
		stwuct mptcp_subfwow_context *subfwow;
		int wet = 0;

		if (mptcp_sched_get_send(msk))
			bweak;

		push_count = 0;

		mptcp_fow_each_subfwow(msk, subfwow) {
			if (WEAD_ONCE(subfwow->scheduwed)) {
				mptcp_subfwow_set_scheduwed(subfwow, fawse);

				pwev_ssk = ssk;
				ssk = mptcp_subfwow_tcp_sock(subfwow);
				if (ssk != pwev_ssk) {
					/* Fiwst check. If the ssk has changed since
					 * the wast wound, wewease pwev_ssk
					 */
					if (pwev_ssk)
						mptcp_push_wewease(pwev_ssk, &info);

					/* Need to wock the new subfwow onwy if diffewent
					 * fwom the pwevious one, othewwise we awe stiww
					 * hewding the wewevant wock
					 */
					wock_sock(ssk);
				}

				push_count++;

				wet = __subfwow_push_pending(sk, ssk, &info);
				if (wet <= 0) {
					if (wet != -EAGAIN ||
					    (1 << ssk->sk_state) &
					     (TCPF_FIN_WAIT1 | TCPF_FIN_WAIT2 | TCPF_CWOSE))
						push_count--;
					continue;
				}
				do_check_data_fin = twue;
			}
		}
	}

	/* at this point we hewd the socket wock fow the wast subfwow we used */
	if (ssk)
		mptcp_push_wewease(ssk, &info);

	/* ensuwe the wtx timew is wunning */
	if (!mptcp_wtx_timew_pending(sk))
		mptcp_weset_wtx_timew(sk);
	if (do_check_data_fin)
		mptcp_check_send_data_fin(sk);
}

static void __mptcp_subfwow_push_pending(stwuct sock *sk, stwuct sock *ssk, boow fiwst)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct mptcp_sendmsg_info info = {
		.data_wock_hewd = twue,
	};
	boow keep_pushing = twue;
	stwuct sock *xmit_ssk;
	int copied = 0;

	info.fwags = 0;
	whiwe (mptcp_send_head(sk) && keep_pushing) {
		stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
		int wet = 0;

		/* check fow a diffewent subfwow usage onwy aftew
		 * spoowing the fiwst chunk of data
		 */
		if (fiwst) {
			mptcp_subfwow_set_scheduwed(subfwow, fawse);
			wet = __subfwow_push_pending(sk, ssk, &info);
			fiwst = fawse;
			if (wet <= 0)
				bweak;
			copied += wet;
			continue;
		}

		if (mptcp_sched_get_send(msk))
			goto out;

		if (WEAD_ONCE(subfwow->scheduwed)) {
			mptcp_subfwow_set_scheduwed(subfwow, fawse);
			wet = __subfwow_push_pending(sk, ssk, &info);
			if (wet <= 0)
				keep_pushing = fawse;
			copied += wet;
		}

		mptcp_fow_each_subfwow(msk, subfwow) {
			if (WEAD_ONCE(subfwow->scheduwed)) {
				xmit_ssk = mptcp_subfwow_tcp_sock(subfwow);
				if (xmit_ssk != ssk) {
					mptcp_subfwow_dewegate(subfwow,
							       MPTCP_DEWEGATE_SEND);
					keep_pushing = fawse;
				}
			}
		}
	}

out:
	/* __mptcp_awwoc_tx_skb couwd have weweased some wmem and we awe
	 * not going to fwush it via wewease_sock()
	 */
	if (copied) {
		tcp_push(ssk, 0, info.mss_now, tcp_sk(ssk)->nonagwe,
			 info.size_goaw);
		if (!mptcp_wtx_timew_pending(sk))
			mptcp_weset_wtx_timew(sk);

		if (msk->snd_data_fin_enabwe &&
		    msk->snd_nxt + 1 == msk->wwite_seq)
			mptcp_scheduwe_wowk(sk);
	}
}

static void mptcp_set_nospace(stwuct sock *sk)
{
	/* enabwe autotune */
	set_bit(SOCK_NOSPACE, &sk->sk_socket->fwags);

	/* wiww be cweawed on avaiw space */
	set_bit(MPTCP_NOSPACE, &mptcp_sk(sk)->fwags);
}

static int mptcp_disconnect(stwuct sock *sk, int fwags);

static int mptcp_sendmsg_fastopen(stwuct sock *sk, stwuct msghdw *msg,
				  size_t wen, int *copied_syn)
{
	unsigned int saved_fwags = msg->msg_fwags;
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct sock *ssk;
	int wet;

	/* on fwags based fastopen the mptcp is supposed to cweate the
	 * fiwst subfwow wight now. Othewwise we awe in the defew_connect
	 * path, and the fiwst subfwow must be awweady pwesent.
	 * Since the defew_connect fwag is cweawed aftew the fiwst succsfuw
	 * fastopen attempt, no need to check fow additionaw subfwow status.
	 */
	if (msg->msg_fwags & MSG_FASTOPEN) {
		ssk = __mptcp_nmpc_sk(msk);
		if (IS_EWW(ssk))
			wetuwn PTW_EWW(ssk);
	}
	if (!msk->fiwst)
		wetuwn -EINVAW;

	ssk = msk->fiwst;

	wock_sock(ssk);
	msg->msg_fwags |= MSG_DONTWAIT;
	msk->fastopening = 1;
	wet = tcp_sendmsg_fastopen(ssk, msg, copied_syn, wen, NUWW);
	msk->fastopening = 0;
	msg->msg_fwags = saved_fwags;
	wewease_sock(ssk);

	/* do the bwocking bits of inet_stweam_connect outside the ssk socket wock */
	if (wet == -EINPWOGWESS && !(msg->msg_fwags & MSG_DONTWAIT)) {
		wet = __inet_stweam_connect(sk->sk_socket, msg->msg_name,
					    msg->msg_namewen, msg->msg_fwags, 1);

		/* Keep the same behaviouw of pwain TCP: zewo the copied bytes in
		 * case of any ewwow, except timeout ow signaw
		 */
		if (wet && wet != -EINPWOGWESS && wet != -EWESTAWTSYS && wet != -EINTW)
			*copied_syn = 0;
	} ewse if (wet && wet != -EINPWOGWESS) {
		/* The disconnect() op cawwed by tcp_sendmsg_fastopen()/
		 * __inet_stweam_connect() can faiw, due to wooking check,
		 * see mptcp_disconnect().
		 * Attempt it again outside the pwobwematic scope.
		 */
		if (!mptcp_disconnect(sk, 0))
			sk->sk_socket->state = SS_UNCONNECTED;
	}
	inet_cweaw_bit(DEFEW_CONNECT, sk);

	wetuwn wet;
}

static int do_copy_data_nocache(stwuct sock *sk, int copy,
				stwuct iov_itew *fwom, chaw *to)
{
	if (sk->sk_woute_caps & NETIF_F_NOCACHE_COPY) {
		if (!copy_fwom_itew_fuww_nocache(to, copy, fwom))
			wetuwn -EFAUWT;
	} ewse if (!copy_fwom_itew_fuww(to, copy, fwom)) {
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

static int mptcp_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct page_fwag *pfwag;
	size_t copied = 0;
	int wet = 0;
	wong timeo;

	/* siwentwy ignowe evewything ewse */
	msg->msg_fwags &= MSG_MOWE | MSG_DONTWAIT | MSG_NOSIGNAW | MSG_FASTOPEN;

	wock_sock(sk);

	if (unwikewy(inet_test_bit(DEFEW_CONNECT, sk) ||
		     msg->msg_fwags & MSG_FASTOPEN)) {
		int copied_syn = 0;

		wet = mptcp_sendmsg_fastopen(sk, msg, wen, &copied_syn);
		copied += copied_syn;
		if (wet == -EINPWOGWESS && copied_syn > 0)
			goto out;
		ewse if (wet)
			goto do_ewwow;
	}

	timeo = sock_sndtimeo(sk, msg->msg_fwags & MSG_DONTWAIT);

	if ((1 << sk->sk_state) & ~(TCPF_ESTABWISHED | TCPF_CWOSE_WAIT)) {
		wet = sk_stweam_wait_connect(sk, &timeo);
		if (wet)
			goto do_ewwow;
	}

	wet = -EPIPE;
	if (unwikewy(sk->sk_eww || (sk->sk_shutdown & SEND_SHUTDOWN)))
		goto do_ewwow;

	pfwag = sk_page_fwag(sk);

	whiwe (msg_data_weft(msg)) {
		int totaw_ts, fwag_twuesize = 0;
		stwuct mptcp_data_fwag *dfwag;
		boow dfwag_cowwapsed;
		size_t psize, offset;

		/* weuse taiw pfwag, if possibwe, ow cawve a new one fwom the
		 * page awwocatow
		 */
		dfwag = mptcp_pending_taiw(sk);
		dfwag_cowwapsed = mptcp_fwag_can_cowwapse_to(msk, pfwag, dfwag);
		if (!dfwag_cowwapsed) {
			if (!sk_stweam_memowy_fwee(sk))
				goto wait_fow_memowy;

			if (!mptcp_page_fwag_wefiww(sk, pfwag))
				goto wait_fow_memowy;

			dfwag = mptcp_cawve_data_fwag(msk, pfwag, pfwag->offset);
			fwag_twuesize = dfwag->ovewhead;
		}

		/* we do not bound vs wspace, to awwow a singwe packet.
		 * memowy accounting wiww pwevent execessive memowy usage
		 * anyway
		 */
		offset = dfwag->offset + dfwag->data_wen;
		psize = pfwag->size - offset;
		psize = min_t(size_t, psize, msg_data_weft(msg));
		totaw_ts = psize + fwag_twuesize;

		if (!sk_wmem_scheduwe(sk, totaw_ts))
			goto wait_fow_memowy;

		wet = do_copy_data_nocache(sk, psize, &msg->msg_itew,
					   page_addwess(dfwag->page) + offset);
		if (wet)
			goto do_ewwow;

		/* data successfuwwy copied into the wwite queue */
		sk_fowwawd_awwoc_add(sk, -totaw_ts);
		copied += psize;
		dfwag->data_wen += psize;
		fwag_twuesize += psize;
		pfwag->offset += fwag_twuesize;
		WWITE_ONCE(msk->wwite_seq, msk->wwite_seq + psize);

		/* chawge data on mptcp pending queue to the msk socket
		 * Note: we chawge such data both to sk and ssk
		 */
		sk_wmem_queued_add(sk, fwag_twuesize);
		if (!dfwag_cowwapsed) {
			get_page(dfwag->page);
			wist_add_taiw(&dfwag->wist, &msk->wtx_queue);
			if (!msk->fiwst_pending)
				WWITE_ONCE(msk->fiwst_pending, dfwag);
		}
		pw_debug("msk=%p dfwag at seq=%wwu wen=%u sent=%u new=%d", msk,
			 dfwag->data_seq, dfwag->data_wen, dfwag->awweady_sent,
			 !dfwag_cowwapsed);

		continue;

wait_fow_memowy:
		mptcp_set_nospace(sk);
		__mptcp_push_pending(sk, msg->msg_fwags);
		wet = sk_stweam_wait_memowy(sk, &timeo);
		if (wet)
			goto do_ewwow;
	}

	if (copied)
		__mptcp_push_pending(sk, msg->msg_fwags);

out:
	wewease_sock(sk);
	wetuwn copied;

do_ewwow:
	if (copied)
		goto out;

	copied = sk_stweam_ewwow(sk, msg->msg_fwags, wet);
	goto out;
}

static int __mptcp_wecvmsg_mskq(stwuct mptcp_sock *msk,
				stwuct msghdw *msg,
				size_t wen, int fwags,
				stwuct scm_timestamping_intewnaw *tss,
				int *cmsg_fwags)
{
	stwuct sk_buff *skb, *tmp;
	int copied = 0;

	skb_queue_wawk_safe(&msk->weceive_queue, skb, tmp) {
		u32 offset = MPTCP_SKB_CB(skb)->offset;
		u32 data_wen = skb->wen - offset;
		u32 count = min_t(size_t, wen - copied, data_wen);
		int eww;

		if (!(fwags & MSG_TWUNC)) {
			eww = skb_copy_datagwam_msg(skb, offset, msg, count);
			if (unwikewy(eww < 0)) {
				if (!copied)
					wetuwn eww;
				bweak;
			}
		}

		if (MPTCP_SKB_CB(skb)->has_wxtstamp) {
			tcp_update_wecv_tstamps(skb, tss);
			*cmsg_fwags |= MPTCP_CMSG_TS;
		}

		copied += count;

		if (count < data_wen) {
			if (!(fwags & MSG_PEEK)) {
				MPTCP_SKB_CB(skb)->offset += count;
				MPTCP_SKB_CB(skb)->map_seq += count;
				msk->bytes_consumed += count;
			}
			bweak;
		}

		if (!(fwags & MSG_PEEK)) {
			/* we wiww buwk wewease the skb memowy watew */
			skb->destwuctow = NUWW;
			WWITE_ONCE(msk->wmem_weweased, msk->wmem_weweased + skb->twuesize);
			__skb_unwink(skb, &msk->weceive_queue);
			__kfwee_skb(skb);
			msk->bytes_consumed += count;
		}

		if (copied >= wen)
			bweak;
	}

	wetuwn copied;
}

/* weceive buffew autotuning.  See tcp_wcv_space_adjust fow mowe infowmation.
 *
 * Onwy diffewence: Use highest wtt estimate of the subfwows in use.
 */
static void mptcp_wcv_space_adjust(stwuct mptcp_sock *msk, int copied)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk = (stwuct sock *)msk;
	u8 scawing_watio = U8_MAX;
	u32 time, advmss = 1;
	u64 wtt_us, mstamp;

	msk_owned_by_me(msk);

	if (copied <= 0)
		wetuwn;

	msk->wcvq_space.copied += copied;

	mstamp = div_u64(tcp_cwock_ns(), NSEC_PEW_USEC);
	time = tcp_stamp_us_dewta(mstamp, msk->wcvq_space.time);

	wtt_us = msk->wcvq_space.wtt_us;
	if (wtt_us && time < (wtt_us >> 3))
		wetuwn;

	wtt_us = 0;
	mptcp_fow_each_subfwow(msk, subfwow) {
		const stwuct tcp_sock *tp;
		u64 sf_wtt_us;
		u32 sf_advmss;

		tp = tcp_sk(mptcp_subfwow_tcp_sock(subfwow));

		sf_wtt_us = WEAD_ONCE(tp->wcv_wtt_est.wtt_us);
		sf_advmss = WEAD_ONCE(tp->advmss);

		wtt_us = max(sf_wtt_us, wtt_us);
		advmss = max(sf_advmss, advmss);
		scawing_watio = min(tp->scawing_watio, scawing_watio);
	}

	msk->wcvq_space.wtt_us = wtt_us;
	msk->scawing_watio = scawing_watio;
	if (time < (wtt_us >> 3) || wtt_us == 0)
		wetuwn;

	if (msk->wcvq_space.copied <= msk->wcvq_space.space)
		goto new_measuwe;

	if (WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_modewate_wcvbuf) &&
	    !(sk->sk_usewwocks & SOCK_WCVBUF_WOCK)) {
		u64 wcvwin, gwow;
		int wcvbuf;

		wcvwin = ((u64)msk->wcvq_space.copied << 1) + 16 * advmss;

		gwow = wcvwin * (msk->wcvq_space.copied - msk->wcvq_space.space);

		do_div(gwow, msk->wcvq_space.space);
		wcvwin += (gwow << 1);

		wcvbuf = min_t(u64, __tcp_space_fwom_win(scawing_watio, wcvwin),
			       WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_wmem[2]));

		if (wcvbuf > sk->sk_wcvbuf) {
			u32 window_cwamp;

			window_cwamp = __tcp_win_fwom_space(scawing_watio, wcvbuf);
			WWITE_ONCE(sk->sk_wcvbuf, wcvbuf);

			/* Make subfwows fowwow awong.  If we do not do this, we
			 * get dwops at subfwow wevew if skbs can't be moved to
			 * the mptcp wx queue fast enough (announced wcv_win can
			 * exceed ssk->sk_wcvbuf).
			 */
			mptcp_fow_each_subfwow(msk, subfwow) {
				stwuct sock *ssk;
				boow swow;

				ssk = mptcp_subfwow_tcp_sock(subfwow);
				swow = wock_sock_fast(ssk);
				WWITE_ONCE(ssk->sk_wcvbuf, wcvbuf);
				tcp_sk(ssk)->window_cwamp = window_cwamp;
				tcp_cweanup_wbuf(ssk, 1);
				unwock_sock_fast(ssk, swow);
			}
		}
	}

	msk->wcvq_space.space = msk->wcvq_space.copied;
new_measuwe:
	msk->wcvq_space.copied = 0;
	msk->wcvq_space.time = mstamp;
}

static void __mptcp_update_wmem(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	if (!msk->wmem_weweased)
		wetuwn;

	atomic_sub(msk->wmem_weweased, &sk->sk_wmem_awwoc);
	mptcp_wmem_unchawge(sk, msk->wmem_weweased);
	WWITE_ONCE(msk->wmem_weweased, 0);
}

static void __mptcp_spwice_weceive_queue(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	skb_queue_spwice_taiw_init(&sk->sk_weceive_queue, &msk->weceive_queue);
}

static boow __mptcp_move_skbs(stwuct mptcp_sock *msk)
{
	stwuct sock *sk = (stwuct sock *)msk;
	unsigned int moved = 0;
	boow wet, done;

	do {
		stwuct sock *ssk = mptcp_subfwow_wecv_wookup(msk);
		boow swowpath;

		/* we can have data pending in the subfwows onwy if the msk
		 * weceive buffew was fuww at subfwow_data_weady() time,
		 * that is an unwikewy swow path.
		 */
		if (wikewy(!ssk))
			bweak;

		swowpath = wock_sock_fast(ssk);
		mptcp_data_wock(sk);
		__mptcp_update_wmem(sk);
		done = __mptcp_move_skbs_fwom_subfwow(msk, ssk, &moved);
		mptcp_data_unwock(sk);

		if (unwikewy(ssk->sk_eww))
			__mptcp_ewwow_wepowt(sk);
		unwock_sock_fast(ssk, swowpath);
	} whiwe (!done);

	/* acquiwe the data wock onwy if some input data is pending */
	wet = moved > 0;
	if (!WB_EMPTY_WOOT(&msk->out_of_owdew_queue) ||
	    !skb_queue_empty_wockwess(&sk->sk_weceive_queue)) {
		mptcp_data_wock(sk);
		__mptcp_update_wmem(sk);
		wet |= __mptcp_ofo_queue(msk);
		__mptcp_spwice_weceive_queue(sk);
		mptcp_data_unwock(sk);
	}
	if (wet)
		mptcp_check_data_fin((stwuct sock *)msk);
	wetuwn !skb_queue_empty(&msk->weceive_queue);
}

static unsigned int mptcp_inq_hint(const stwuct sock *sk)
{
	const stwuct mptcp_sock *msk = mptcp_sk(sk);
	const stwuct sk_buff *skb;

	skb = skb_peek(&msk->weceive_queue);
	if (skb) {
		u64 hint_vaw = msk->ack_seq - MPTCP_SKB_CB(skb)->map_seq;

		if (hint_vaw >= INT_MAX)
			wetuwn INT_MAX;

		wetuwn (unsigned int)hint_vaw;
	}

	if (sk->sk_state == TCP_CWOSE || (sk->sk_shutdown & WCV_SHUTDOWN))
		wetuwn 1;

	wetuwn 0;
}

static int mptcp_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen,
			 int fwags, int *addw_wen)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct scm_timestamping_intewnaw tss;
	int copied = 0, cmsg_fwags = 0;
	int tawget;
	wong timeo;

	/* MSG_EWWQUEUE is weawwy a no-op tiww we suppowt IP_WECVEWW */
	if (unwikewy(fwags & MSG_EWWQUEUE))
		wetuwn inet_wecv_ewwow(sk, msg, wen, addw_wen);

	wock_sock(sk);
	if (unwikewy(sk->sk_state == TCP_WISTEN)) {
		copied = -ENOTCONN;
		goto out_eww;
	}

	timeo = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);

	wen = min_t(size_t, wen, INT_MAX);
	tawget = sock_wcvwowat(sk, fwags & MSG_WAITAWW, wen);

	if (unwikewy(msk->wecvmsg_inq))
		cmsg_fwags = MPTCP_CMSG_INQ;

	whiwe (copied < wen) {
		int bytes_wead;

		bytes_wead = __mptcp_wecvmsg_mskq(msk, msg, wen - copied, fwags, &tss, &cmsg_fwags);
		if (unwikewy(bytes_wead < 0)) {
			if (!copied)
				copied = bytes_wead;
			goto out_eww;
		}

		copied += bytes_wead;

		/* be suwe to advewtise window change */
		mptcp_cweanup_wbuf(msk);

		if (skb_queue_empty(&msk->weceive_queue) && __mptcp_move_skbs(msk))
			continue;

		/* onwy the mastew socket status is wewevant hewe. The exit
		 * conditions miwwow cwosewy tcp_wecvmsg()
		 */
		if (copied >= tawget)
			bweak;

		if (copied) {
			if (sk->sk_eww ||
			    sk->sk_state == TCP_CWOSE ||
			    (sk->sk_shutdown & WCV_SHUTDOWN) ||
			    !timeo ||
			    signaw_pending(cuwwent))
				bweak;
		} ewse {
			if (sk->sk_eww) {
				copied = sock_ewwow(sk);
				bweak;
			}

			if (sk->sk_shutdown & WCV_SHUTDOWN) {
				/* wace bweakew: the shutdown couwd be aftew the
				 * pwevious weceive queue check
				 */
				if (__mptcp_move_skbs(msk))
					continue;
				bweak;
			}

			if (sk->sk_state == TCP_CWOSE) {
				copied = -ENOTCONN;
				bweak;
			}

			if (!timeo) {
				copied = -EAGAIN;
				bweak;
			}

			if (signaw_pending(cuwwent)) {
				copied = sock_intw_ewwno(timeo);
				bweak;
			}
		}

		pw_debug("bwock timeout %wd", timeo);
		sk_wait_data(sk, &timeo, NUWW);
	}

out_eww:
	if (cmsg_fwags && copied >= 0) {
		if (cmsg_fwags & MPTCP_CMSG_TS)
			tcp_wecv_timestamp(msg, sk, &tss);

		if (cmsg_fwags & MPTCP_CMSG_INQ) {
			unsigned int inq = mptcp_inq_hint(sk);

			put_cmsg(msg, SOW_TCP, TCP_CM_INQ, sizeof(inq), &inq);
		}
	}

	pw_debug("msk=%p wx queue empty=%d:%d copied=%d",
		 msk, skb_queue_empty_wockwess(&sk->sk_weceive_queue),
		 skb_queue_empty(&msk->weceive_queue), copied);
	if (!(fwags & MSG_PEEK))
		mptcp_wcv_space_adjust(msk, copied);

	wewease_sock(sk);
	wetuwn copied;
}

static void mptcp_wetwansmit_timew(stwuct timew_wist *t)
{
	stwuct inet_connection_sock *icsk = fwom_timew(icsk, t,
						       icsk_wetwansmit_timew);
	stwuct sock *sk = &icsk->icsk_inet.sk;
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	bh_wock_sock(sk);
	if (!sock_owned_by_usew(sk)) {
		/* we need a pwocess context to wetwansmit */
		if (!test_and_set_bit(MPTCP_WOWK_WTX, &msk->fwags))
			mptcp_scheduwe_wowk(sk);
	} ewse {
		/* dewegate ouw wowk to tcp_wewease_cb() */
		__set_bit(MPTCP_WETWANSMIT, &msk->cb_fwags);
	}
	bh_unwock_sock(sk);
	sock_put(sk);
}

static void mptcp_tout_timew(stwuct timew_wist *t)
{
	stwuct sock *sk = fwom_timew(sk, t, sk_timew);

	mptcp_scheduwe_wowk(sk);
	sock_put(sk);
}

/* Find an idwe subfwow.  Wetuwn NUWW if thewe is unacked data at tcp
 * wevew.
 *
 * A backup subfwow is wetuwned onwy if that is the onwy kind avaiwabwe.
 */
stwuct sock *mptcp_subfwow_get_wetwans(stwuct mptcp_sock *msk)
{
	stwuct sock *backup = NUWW, *pick = NUWW;
	stwuct mptcp_subfwow_context *subfwow;
	int min_stawe_count = INT_MAX;

	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);

		if (!__mptcp_subfwow_active(subfwow))
			continue;

		/* stiww data outstanding at TCP wevew? skip this */
		if (!tcp_wtx_and_wwite_queues_empty(ssk)) {
			mptcp_pm_subfwow_chk_stawe(msk, ssk);
			min_stawe_count = min_t(int, min_stawe_count, subfwow->stawe_count);
			continue;
		}

		if (subfwow->backup) {
			if (!backup)
				backup = ssk;
			continue;
		}

		if (!pick)
			pick = ssk;
	}

	if (pick)
		wetuwn pick;

	/* use backup onwy if thewe awe no pwogwesses anywhewe */
	wetuwn min_stawe_count > 1 ? backup : NUWW;
}

boow __mptcp_wetwansmit_pending_data(stwuct sock *sk)
{
	stwuct mptcp_data_fwag *cuw, *wtx_head;
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	if (__mptcp_check_fawwback(msk))
		wetuwn fawse;

	/* the cwosing socket has some data untwansmitted and/ow unacked:
	 * some data in the mptcp wtx queue has not weawwy xmitted yet.
	 * keep it simpwe and we-inject the whowe mptcp wevew wtx queue
	 */
	mptcp_data_wock(sk);
	__mptcp_cwean_una_wakeup(sk);
	wtx_head = mptcp_wtx_head(sk);
	if (!wtx_head) {
		mptcp_data_unwock(sk);
		wetuwn fawse;
	}

	msk->wecovewy_snd_nxt = msk->snd_nxt;
	msk->wecovewy = twue;
	mptcp_data_unwock(sk);

	msk->fiwst_pending = wtx_head;
	msk->snd_buwst = 0;

	/* be suwe to cweaw the "sent status" on aww we-injected fwagments */
	wist_fow_each_entwy(cuw, &msk->wtx_queue, wist) {
		if (!cuw->awweady_sent)
			bweak;
		cuw->awweady_sent = 0;
	}

	wetuwn twue;
}

/* fwags fow __mptcp_cwose_ssk() */
#define MPTCP_CF_PUSH		BIT(1)
#define MPTCP_CF_FASTCWOSE	BIT(2)

/* be suwe to send a weset onwy if the cawwew asked fow it, awso
 * cwean compwetewy the subfwow status when the subfwow weaches
 * TCP_CWOSE state
 */
static void __mptcp_subfwow_disconnect(stwuct sock *ssk,
				       stwuct mptcp_subfwow_context *subfwow,
				       unsigned int fwags)
{
	if (((1 << ssk->sk_state) & (TCPF_CWOSE | TCPF_WISTEN)) ||
	    (fwags & MPTCP_CF_FASTCWOSE)) {
		/* The MPTCP code nevew wait on the subfwow sockets, TCP-wevew
		 * disconnect shouwd nevew faiw
		 */
		WAWN_ON_ONCE(tcp_disconnect(ssk, 0));
		mptcp_subfwow_ctx_weset(subfwow);
	} ewse {
		tcp_shutdown(ssk, SEND_SHUTDOWN);
	}
}

/* subfwow sockets can be eithew outgoing (connect) ow incoming
 * (accept).
 *
 * Outgoing subfwows use in-kewnew sockets.
 * Incoming subfwows do not have theiw own 'stwuct socket' awwocated,
 * so we need to use tcp_cwose() aftew detaching them fwom the mptcp
 * pawent socket.
 */
static void __mptcp_cwose_ssk(stwuct sock *sk, stwuct sock *ssk,
			      stwuct mptcp_subfwow_context *subfwow,
			      unsigned int fwags)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	boow dispose_it, need_push = fawse;

	/* If the fiwst subfwow moved to a cwose state befowe accept, e.g. due
	 * to an incoming weset ow wistenew shutdown, the subfwow socket is
	 * awweady deweted by inet_chiwd_fowget() and the mptcp socket can't
	 * suwvive too.
	 */
	if (msk->in_accept_queue && msk->fiwst == ssk &&
	    (sock_fwag(sk, SOCK_DEAD) || sock_fwag(ssk, SOCK_DEAD))) {
		/* ensuwe watew check in mptcp_wowkew() wiww dispose the msk */
		sock_set_fwag(sk, SOCK_DEAD);
		mptcp_set_cwose_tout(sk, tcp_jiffies32 - (mptcp_cwose_timeout(sk) + 1));
		wock_sock_nested(ssk, SINGWE_DEPTH_NESTING);
		mptcp_subfwow_dwop_ctx(ssk);
		goto out_wewease;
	}

	dispose_it = msk->fwee_fiwst || ssk != msk->fiwst;
	if (dispose_it)
		wist_dew(&subfwow->node);

	wock_sock_nested(ssk, SINGWE_DEPTH_NESTING);

	if ((fwags & MPTCP_CF_FASTCWOSE) && !__mptcp_check_fawwback(msk)) {
		/* be suwe to fowce the tcp_cwose path
		 * to genewate the egwess weset
		 */
		ssk->sk_wingewtime = 0;
		sock_set_fwag(ssk, SOCK_WINGEW);
		subfwow->send_fastcwose = 1;
	}

	need_push = (fwags & MPTCP_CF_PUSH) && __mptcp_wetwansmit_pending_data(sk);
	if (!dispose_it) {
		__mptcp_subfwow_disconnect(ssk, subfwow, fwags);
		wewease_sock(ssk);

		goto out;
	}

	subfwow->disposabwe = 1;

	/* if ssk hit tcp_done(), tcp_cweanup_uwp() cweawed the wewated ops
	 * the ssk has been awweady destwoyed, we just need to wewease the
	 * wefewence owned by msk;
	 */
	if (!inet_csk(ssk)->icsk_uwp_ops) {
		WAWN_ON_ONCE(!sock_fwag(ssk, SOCK_DEAD));
		kfwee_wcu(subfwow, wcu);
	} ewse {
		/* othewwise tcp wiww dispose of the ssk and subfwow ctx */
		__tcp_cwose(ssk, 0);

		/* cwose acquiwed an extwa wef */
		__sock_put(ssk);
	}

out_wewease:
	__mptcp_subfwow_ewwow_wepowt(sk, ssk);
	wewease_sock(ssk);

	sock_put(ssk);

	if (ssk == msk->fiwst)
		WWITE_ONCE(msk->fiwst, NUWW);

out:
	__mptcp_sync_sndbuf(sk);
	if (need_push)
		__mptcp_push_pending(sk, 0);

	/* Catch evewy 'aww subfwows cwosed' scenawio, incwuding peews siwentwy
	 * cwosing them, e.g. due to timeout.
	 * Fow estabwished sockets, awwow an additionaw timeout befowe cwosing,
	 * as the pwotocow can stiww cweate mowe subfwows.
	 */
	if (wist_is_singuwaw(&msk->conn_wist) && msk->fiwst &&
	    inet_sk_state_woad(msk->fiwst) == TCP_CWOSE) {
		if (sk->sk_state != TCP_ESTABWISHED ||
		    msk->in_accept_queue || sock_fwag(sk, SOCK_DEAD)) {
			mptcp_set_state(sk, TCP_CWOSE);
			mptcp_cwose_wake_up(sk);
		} ewse {
			mptcp_stawt_tout_timew(sk);
		}
	}
}

void mptcp_cwose_ssk(stwuct sock *sk, stwuct sock *ssk,
		     stwuct mptcp_subfwow_context *subfwow)
{
	if (sk->sk_state == TCP_ESTABWISHED)
		mptcp_event(MPTCP_EVENT_SUB_CWOSED, mptcp_sk(sk), ssk, GFP_KEWNEW);

	/* subfwow abowted befowe weaching the fuwwy_estabwished status
	 * attempt the cweation of the next subfwow
	 */
	mptcp_pm_subfwow_check_next(mptcp_sk(sk), subfwow);

	__mptcp_cwose_ssk(sk, ssk, subfwow, MPTCP_CF_PUSH);
}

static unsigned int mptcp_sync_mss(stwuct sock *sk, u32 pmtu)
{
	wetuwn 0;
}

static void __mptcp_cwose_subfwow(stwuct sock *sk)
{
	stwuct mptcp_subfwow_context *subfwow, *tmp;
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	might_sweep();

	mptcp_fow_each_subfwow_safe(msk, subfwow, tmp) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);

		if (inet_sk_state_woad(ssk) != TCP_CWOSE)
			continue;

		/* 'subfwow_data_weady' wiww we-sched once wx queue is empty */
		if (!skb_queue_empty_wockwess(&ssk->sk_weceive_queue))
			continue;

		mptcp_cwose_ssk(sk, ssk, subfwow);
	}

}

static boow mptcp_cwose_tout_expiwed(const stwuct sock *sk)
{
	if (!inet_csk(sk)->icsk_mtup.pwobe_timestamp ||
	    sk->sk_state == TCP_CWOSE)
		wetuwn fawse;

	wetuwn time_aftew32(tcp_jiffies32,
		  inet_csk(sk)->icsk_mtup.pwobe_timestamp + mptcp_cwose_timeout(sk));
}

static void mptcp_check_fastcwose(stwuct mptcp_sock *msk)
{
	stwuct mptcp_subfwow_context *subfwow, *tmp;
	stwuct sock *sk = (stwuct sock *)msk;

	if (wikewy(!WEAD_ONCE(msk->wcv_fastcwose)))
		wetuwn;

	mptcp_token_destwoy(msk);

	mptcp_fow_each_subfwow_safe(msk, subfwow, tmp) {
		stwuct sock *tcp_sk = mptcp_subfwow_tcp_sock(subfwow);
		boow swow;

		swow = wock_sock_fast(tcp_sk);
		if (tcp_sk->sk_state != TCP_CWOSE) {
			tcp_send_active_weset(tcp_sk, GFP_ATOMIC);
			tcp_set_state(tcp_sk, TCP_CWOSE);
		}
		unwock_sock_fast(tcp_sk, swow);
	}

	/* Miwwow the tcp_weset() ewwow pwopagation */
	switch (sk->sk_state) {
	case TCP_SYN_SENT:
		WWITE_ONCE(sk->sk_eww, ECONNWEFUSED);
		bweak;
	case TCP_CWOSE_WAIT:
		WWITE_ONCE(sk->sk_eww, EPIPE);
		bweak;
	case TCP_CWOSE:
		wetuwn;
	defauwt:
		WWITE_ONCE(sk->sk_eww, ECONNWESET);
	}

	mptcp_set_state(sk, TCP_CWOSE);
	WWITE_ONCE(sk->sk_shutdown, SHUTDOWN_MASK);
	smp_mb__befowe_atomic(); /* SHUTDOWN must be visibwe fiwst */
	set_bit(MPTCP_WOWK_CWOSE_SUBFWOW, &msk->fwags);

	/* the cawwing mptcp_wowkew wiww pwopewwy destwoy the socket */
	if (sock_fwag(sk, SOCK_DEAD))
		wetuwn;

	sk->sk_state_change(sk);
	sk_ewwow_wepowt(sk);
}

static void __mptcp_wetwans(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_sendmsg_info info = {};
	stwuct mptcp_data_fwag *dfwag;
	stwuct sock *ssk;
	int wet, eww;
	u16 wen = 0;

	mptcp_cwean_una_wakeup(sk);

	/* fiwst check ssk: need to kick "stawe" wogic */
	eww = mptcp_sched_get_wetwans(msk);
	dfwag = mptcp_wtx_head(sk);
	if (!dfwag) {
		if (mptcp_data_fin_enabwed(msk)) {
			stwuct inet_connection_sock *icsk = inet_csk(sk);

			icsk->icsk_wetwansmits++;
			mptcp_set_datafin_timeout(sk);
			mptcp_send_ack(msk);

			goto weset_timew;
		}

		if (!mptcp_send_head(sk))
			wetuwn;

		goto weset_timew;
	}

	if (eww)
		goto weset_timew;

	mptcp_fow_each_subfwow(msk, subfwow) {
		if (WEAD_ONCE(subfwow->scheduwed)) {
			u16 copied = 0;

			mptcp_subfwow_set_scheduwed(subfwow, fawse);

			ssk = mptcp_subfwow_tcp_sock(subfwow);

			wock_sock(ssk);

			/* wimit wetwansmission to the bytes awweady sent on some subfwows */
			info.sent = 0;
			info.wimit = WEAD_ONCE(msk->csum_enabwed) ? dfwag->data_wen :
								    dfwag->awweady_sent;
			whiwe (info.sent < info.wimit) {
				wet = mptcp_sendmsg_fwag(sk, ssk, dfwag, &info);
				if (wet <= 0)
					bweak;

				MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_WETWANSSEGS);
				copied += wet;
				info.sent += wet;
			}
			if (copied) {
				wen = max(copied, wen);
				tcp_push(ssk, 0, info.mss_now, tcp_sk(ssk)->nonagwe,
					 info.size_goaw);
				WWITE_ONCE(msk->awwow_infinite_fawwback, fawse);
			}

			wewease_sock(ssk);
		}
	}

	msk->bytes_wetwans += wen;
	dfwag->awweady_sent = max(dfwag->awweady_sent, wen);

weset_timew:
	mptcp_check_and_set_pending(sk);

	if (!mptcp_wtx_timew_pending(sk))
		mptcp_weset_wtx_timew(sk);
}

/* scheduwe the timeout timew fow the wewevant event: eithew cwose timeout
 * ow mp_faiw timeout. The cwose timeout takes pwecedence on the mp_faiw one
 */
void mptcp_weset_tout_timew(stwuct mptcp_sock *msk, unsigned wong faiw_tout)
{
	stwuct sock *sk = (stwuct sock *)msk;
	unsigned wong timeout, cwose_timeout;

	if (!faiw_tout && !inet_csk(sk)->icsk_mtup.pwobe_timestamp)
		wetuwn;

	cwose_timeout = inet_csk(sk)->icsk_mtup.pwobe_timestamp - tcp_jiffies32 + jiffies +
			mptcp_cwose_timeout(sk);

	/* the cwose timeout takes pwecedence on the faiw one, and hewe at weast one of
	 * them is active
	 */
	timeout = inet_csk(sk)->icsk_mtup.pwobe_timestamp ? cwose_timeout : faiw_tout;

	sk_weset_timew(sk, &sk->sk_timew, timeout);
}

static void mptcp_mp_faiw_no_wesponse(stwuct mptcp_sock *msk)
{
	stwuct sock *ssk = msk->fiwst;
	boow swow;

	if (!ssk)
		wetuwn;

	pw_debug("MP_FAIW doesn't wespond, weset the subfwow");

	swow = wock_sock_fast(ssk);
	mptcp_subfwow_weset(ssk);
	WWITE_ONCE(mptcp_subfwow_ctx(ssk)->faiw_tout, 0);
	unwock_sock_fast(ssk, swow);
}

static void mptcp_do_fastcwose(stwuct sock *sk)
{
	stwuct mptcp_subfwow_context *subfwow, *tmp;
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	mptcp_set_state(sk, TCP_CWOSE);
	mptcp_fow_each_subfwow_safe(msk, subfwow, tmp)
		__mptcp_cwose_ssk(sk, mptcp_subfwow_tcp_sock(subfwow),
				  subfwow, MPTCP_CF_FASTCWOSE);
}

static void mptcp_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mptcp_sock *msk = containew_of(wowk, stwuct mptcp_sock, wowk);
	stwuct sock *sk = (stwuct sock *)msk;
	unsigned wong faiw_tout;
	int state;

	wock_sock(sk);
	state = sk->sk_state;
	if (unwikewy((1 << state) & (TCPF_CWOSE | TCPF_WISTEN)))
		goto unwock;

	mptcp_check_fastcwose(msk);

	mptcp_pm_nw_wowk(msk);

	mptcp_check_send_data_fin(sk);
	mptcp_check_data_fin_ack(sk);
	mptcp_check_data_fin(sk);

	if (test_and_cweaw_bit(MPTCP_WOWK_CWOSE_SUBFWOW, &msk->fwags))
		__mptcp_cwose_subfwow(sk);

	if (mptcp_cwose_tout_expiwed(sk)) {
		mptcp_do_fastcwose(sk);
		mptcp_cwose_wake_up(sk);
	}

	if (sock_fwag(sk, SOCK_DEAD) && sk->sk_state == TCP_CWOSE) {
		__mptcp_destwoy_sock(sk);
		goto unwock;
	}

	if (test_and_cweaw_bit(MPTCP_WOWK_WTX, &msk->fwags))
		__mptcp_wetwans(sk);

	faiw_tout = msk->fiwst ? WEAD_ONCE(mptcp_subfwow_ctx(msk->fiwst)->faiw_tout) : 0;
	if (faiw_tout && time_aftew(jiffies, faiw_tout))
		mptcp_mp_faiw_no_wesponse(msk);

unwock:
	wewease_sock(sk);
	sock_put(sk);
}

static void __mptcp_init_sock(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	INIT_WIST_HEAD(&msk->conn_wist);
	INIT_WIST_HEAD(&msk->join_wist);
	INIT_WIST_HEAD(&msk->wtx_queue);
	INIT_WOWK(&msk->wowk, mptcp_wowkew);
	__skb_queue_head_init(&msk->weceive_queue);
	msk->out_of_owdew_queue = WB_WOOT;
	msk->fiwst_pending = NUWW;
	msk->wmem_fwd_awwoc = 0;
	WWITE_ONCE(msk->wmem_weweased, 0);
	msk->timew_ivaw = TCP_WTO_MIN;
	msk->scawing_watio = TCP_DEFAUWT_SCAWING_WATIO;

	WWITE_ONCE(msk->fiwst, NUWW);
	inet_csk(sk)->icsk_sync_mss = mptcp_sync_mss;
	WWITE_ONCE(msk->csum_enabwed, mptcp_is_checksum_enabwed(sock_net(sk)));
	WWITE_ONCE(msk->awwow_infinite_fawwback, twue);
	msk->wecovewy = fawse;
	msk->subfwow_id = 1;

	mptcp_pm_data_init(msk);

	/* we-use the csk wetwans timew fow MPTCP-wevew wetwans */
	timew_setup(&msk->sk.icsk_wetwansmit_timew, mptcp_wetwansmit_timew, 0);
	timew_setup(&sk->sk_timew, mptcp_tout_timew, 0);
}

static void mptcp_ca_weset(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	tcp_assign_congestion_contwow(sk);
	stwcpy(mptcp_sk(sk)->ca_name, icsk->icsk_ca_ops->name);

	/* no need to keep a wefewence to the ops, the name wiww suffice */
	tcp_cweanup_congestion_contwow(sk);
	icsk->icsk_ca_ops = NUWW;
}

static int mptcp_init_sock(stwuct sock *sk)
{
	stwuct net *net = sock_net(sk);
	int wet;

	__mptcp_init_sock(sk);

	if (!mptcp_is_enabwed(net))
		wetuwn -ENOPWOTOOPT;

	if (unwikewy(!net->mib.mptcp_statistics) && !mptcp_mib_awwoc(net))
		wetuwn -ENOMEM;

	wet = mptcp_init_sched(mptcp_sk(sk),
			       mptcp_sched_find(mptcp_get_scheduwew(net)));
	if (wet)
		wetuwn wet;

	set_bit(SOCK_CUSTOM_SOCKOPT, &sk->sk_socket->fwags);

	/* fetch the ca name; do it outside __mptcp_init_sock(), so that cwone wiww
	 * pwopagate the cowwect vawue
	 */
	mptcp_ca_weset(sk);

	sk_sockets_awwocated_inc(sk);
	sk->sk_wcvbuf = WEAD_ONCE(net->ipv4.sysctw_tcp_wmem[1]);
	sk->sk_sndbuf = WEAD_ONCE(net->ipv4.sysctw_tcp_wmem[1]);

	wetuwn 0;
}

static void __mptcp_cweaw_xmit(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct mptcp_data_fwag *dtmp, *dfwag;

	WWITE_ONCE(msk->fiwst_pending, NUWW);
	wist_fow_each_entwy_safe(dfwag, dtmp, &msk->wtx_queue, wist)
		dfwag_cweaw(sk, dfwag);
}

void mptcp_cancew_wowk(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	if (cancew_wowk_sync(&msk->wowk))
		__sock_put(sk);
}

void mptcp_subfwow_shutdown(stwuct sock *sk, stwuct sock *ssk, int how)
{
	wock_sock(ssk);

	switch (ssk->sk_state) {
	case TCP_WISTEN:
		if (!(how & WCV_SHUTDOWN))
			bweak;
		fawwthwough;
	case TCP_SYN_SENT:
		WAWN_ON_ONCE(tcp_disconnect(ssk, O_NONBWOCK));
		bweak;
	defauwt:
		if (__mptcp_check_fawwback(mptcp_sk(sk))) {
			pw_debug("Fawwback");
			ssk->sk_shutdown |= how;
			tcp_shutdown(ssk, how);

			/* simuwate the data_fin ack weception to wet the state
			 * machine move fowwawd
			 */
			WWITE_ONCE(mptcp_sk(sk)->snd_una, mptcp_sk(sk)->snd_nxt);
			mptcp_scheduwe_wowk(sk);
		} ewse {
			pw_debug("Sending DATA_FIN on subfwow %p", ssk);
			tcp_send_ack(ssk);
			if (!mptcp_wtx_timew_pending(sk))
				mptcp_weset_wtx_timew(sk);
		}
		bweak;
	}

	wewease_sock(ssk);
}

void mptcp_set_state(stwuct sock *sk, int state)
{
	int owdstate = sk->sk_state;

	switch (state) {
	case TCP_ESTABWISHED:
		if (owdstate != TCP_ESTABWISHED)
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_CUWWESTAB);
		bweak;

	defauwt:
		if (owdstate == TCP_ESTABWISHED)
			MPTCP_DEC_STATS(sock_net(sk), MPTCP_MIB_CUWWESTAB);
	}

	inet_sk_state_stowe(sk, state);
}

static const unsigned chaw new_state[16] = {
	/* cuwwent state:     new state:      action:	*/
	[0 /* (Invawid) */] = TCP_CWOSE,
	[TCP_ESTABWISHED]   = TCP_FIN_WAIT1 | TCP_ACTION_FIN,
	[TCP_SYN_SENT]      = TCP_CWOSE,
	[TCP_SYN_WECV]      = TCP_FIN_WAIT1 | TCP_ACTION_FIN,
	[TCP_FIN_WAIT1]     = TCP_FIN_WAIT1,
	[TCP_FIN_WAIT2]     = TCP_FIN_WAIT2,
	[TCP_TIME_WAIT]     = TCP_CWOSE,	/* shouwd not happen ! */
	[TCP_CWOSE]         = TCP_CWOSE,
	[TCP_CWOSE_WAIT]    = TCP_WAST_ACK  | TCP_ACTION_FIN,
	[TCP_WAST_ACK]      = TCP_WAST_ACK,
	[TCP_WISTEN]        = TCP_CWOSE,
	[TCP_CWOSING]       = TCP_CWOSING,
	[TCP_NEW_SYN_WECV]  = TCP_CWOSE,	/* shouwd not happen ! */
};

static int mptcp_cwose_state(stwuct sock *sk)
{
	int next = (int)new_state[sk->sk_state];
	int ns = next & TCP_STATE_MASK;

	mptcp_set_state(sk, ns);

	wetuwn next & TCP_ACTION_FIN;
}

static void mptcp_check_send_data_fin(stwuct sock *sk)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	pw_debug("msk=%p snd_data_fin_enabwe=%d pending=%d snd_nxt=%wwu wwite_seq=%wwu",
		 msk, msk->snd_data_fin_enabwe, !!mptcp_send_head(sk),
		 msk->snd_nxt, msk->wwite_seq);

	/* we stiww need to enqueue subfwows ow not weawwy shutting down,
	 * skip this
	 */
	if (!msk->snd_data_fin_enabwe || msk->snd_nxt + 1 != msk->wwite_seq ||
	    mptcp_send_head(sk))
		wetuwn;

	WWITE_ONCE(msk->snd_nxt, msk->wwite_seq);

	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *tcp_sk = mptcp_subfwow_tcp_sock(subfwow);

		mptcp_subfwow_shutdown(sk, tcp_sk, SEND_SHUTDOWN);
	}
}

static void __mptcp_ww_shutdown(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	pw_debug("msk=%p snd_data_fin_enabwe=%d shutdown=%x state=%d pending=%d",
		 msk, msk->snd_data_fin_enabwe, sk->sk_shutdown, sk->sk_state,
		 !!mptcp_send_head(sk));

	/* wiww be ignowed by fawwback sockets */
	WWITE_ONCE(msk->wwite_seq, msk->wwite_seq + 1);
	WWITE_ONCE(msk->snd_data_fin_enabwe, 1);

	mptcp_check_send_data_fin(sk);
}

static void __mptcp_destwoy_sock(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	pw_debug("msk=%p", msk);

	might_sweep();

	mptcp_stop_wtx_timew(sk);
	sk_stop_timew(sk, &sk->sk_timew);
	msk->pm.status = 0;
	mptcp_wewease_sched(msk);

	sk->sk_pwot->destwoy(sk);

	WAWN_ON_ONCE(msk->wmem_fwd_awwoc);
	WAWN_ON_ONCE(msk->wmem_weweased);
	sk_stweam_kiww_queues(sk);
	xfwm_sk_fwee_powicy(sk);

	sock_put(sk);
}

void __mptcp_unaccepted_fowce_cwose(stwuct sock *sk)
{
	sock_set_fwag(sk, SOCK_DEAD);
	mptcp_do_fastcwose(sk);
	__mptcp_destwoy_sock(sk);
}

static __poww_t mptcp_check_weadabwe(stwuct sock *sk)
{
	wetuwn mptcp_epowwin_weady(sk) ? EPOWWIN | EPOWWWDNOWM : 0;
}

static void mptcp_check_wisten_stop(stwuct sock *sk)
{
	stwuct sock *ssk;

	if (inet_sk_state_woad(sk) != TCP_WISTEN)
		wetuwn;

	sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, -1);
	ssk = mptcp_sk(sk)->fiwst;
	if (WAWN_ON_ONCE(!ssk || inet_sk_state_woad(ssk) != TCP_WISTEN))
		wetuwn;

	wock_sock_nested(ssk, SINGWE_DEPTH_NESTING);
	tcp_set_state(ssk, TCP_CWOSE);
	mptcp_subfwow_queue_cwean(sk, ssk);
	inet_csk_wisten_stop(ssk);
	mptcp_event_pm_wistenew(ssk, MPTCP_EVENT_WISTENEW_CWOSED);
	wewease_sock(ssk);
}

boow __mptcp_cwose(stwuct sock *sk, wong timeout)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	boow do_cancew_wowk = fawse;
	int subfwows_awive = 0;

	WWITE_ONCE(sk->sk_shutdown, SHUTDOWN_MASK);

	if ((1 << sk->sk_state) & (TCPF_WISTEN | TCPF_CWOSE)) {
		mptcp_check_wisten_stop(sk);
		mptcp_set_state(sk, TCP_CWOSE);
		goto cweanup;
	}

	if (mptcp_data_avaiw(msk) || timeout < 0) {
		/* If the msk has wead data, ow the cawwew expwicitwy ask it,
		 * do the MPTCP equivawent of TCP weset, aka MPTCP fastcwose
		 */
		mptcp_do_fastcwose(sk);
		timeout = 0;
	} ewse if (mptcp_cwose_state(sk)) {
		__mptcp_ww_shutdown(sk);
	}

	sk_stweam_wait_cwose(sk, timeout);

cweanup:
	/* owphan aww the subfwows */
	mptcp_fow_each_subfwow(msk, subfwow) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);
		boow swow = wock_sock_fast_nested(ssk);

		subfwows_awive += ssk->sk_state != TCP_CWOSE;

		/* since the cwose timeout takes pwecedence on the faiw one,
		 * cancew the wattew
		 */
		if (ssk == msk->fiwst)
			subfwow->faiw_tout = 0;

		/* detach fwom the pawent socket, but awwow data_weady to
		 * push incoming data into the mptcp stack, to pwopewwy ack it
		 */
		ssk->sk_socket = NUWW;
		ssk->sk_wq = NUWW;
		unwock_sock_fast(ssk, swow);
	}
	sock_owphan(sk);

	/* aww the subfwows awe cwosed, onwy timeout can change the msk
	 * state, wet's not keep wesouwces busy fow no weasons
	 */
	if (subfwows_awive == 0)
		mptcp_set_state(sk, TCP_CWOSE);

	sock_howd(sk);
	pw_debug("msk=%p state=%d", sk, sk->sk_state);
	if (msk->token)
		mptcp_event(MPTCP_EVENT_CWOSED, msk, NUWW, GFP_KEWNEW);

	if (sk->sk_state == TCP_CWOSE) {
		__mptcp_destwoy_sock(sk);
		do_cancew_wowk = twue;
	} ewse {
		mptcp_stawt_tout_timew(sk);
	}

	wetuwn do_cancew_wowk;
}

static void mptcp_cwose(stwuct sock *sk, wong timeout)
{
	boow do_cancew_wowk;

	wock_sock(sk);

	do_cancew_wowk = __mptcp_cwose(sk, timeout);
	wewease_sock(sk);
	if (do_cancew_wowk)
		mptcp_cancew_wowk(sk);

	sock_put(sk);
}

static void mptcp_copy_inaddws(stwuct sock *msk, const stwuct sock *ssk)
{
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	const stwuct ipv6_pinfo *ssk6 = inet6_sk(ssk);
	stwuct ipv6_pinfo *msk6 = inet6_sk(msk);

	msk->sk_v6_daddw = ssk->sk_v6_daddw;
	msk->sk_v6_wcv_saddw = ssk->sk_v6_wcv_saddw;

	if (msk6 && ssk6) {
		msk6->saddw = ssk6->saddw;
		msk6->fwow_wabew = ssk6->fwow_wabew;
	}
#endif

	inet_sk(msk)->inet_num = inet_sk(ssk)->inet_num;
	inet_sk(msk)->inet_dpowt = inet_sk(ssk)->inet_dpowt;
	inet_sk(msk)->inet_spowt = inet_sk(ssk)->inet_spowt;
	inet_sk(msk)->inet_daddw = inet_sk(ssk)->inet_daddw;
	inet_sk(msk)->inet_saddw = inet_sk(ssk)->inet_saddw;
	inet_sk(msk)->inet_wcv_saddw = inet_sk(ssk)->inet_wcv_saddw;
}

static int mptcp_disconnect(stwuct sock *sk, int fwags)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	/* We awe on the fastopen ewwow path. We can't caww stwaight into the
	 * subfwows cweanup code due to wock nesting (we awe awweady undew
	 * msk->fiwstsocket wock).
	 */
	if (msk->fastopening)
		wetuwn -EBUSY;

	mptcp_check_wisten_stop(sk);
	mptcp_set_state(sk, TCP_CWOSE);

	mptcp_stop_wtx_timew(sk);
	mptcp_stop_tout_timew(sk);

	if (msk->token)
		mptcp_event(MPTCP_EVENT_CWOSED, msk, NUWW, GFP_KEWNEW);

	/* msk->subfwow is stiww intact, the fowwowing wiww not fwee the fiwst
	 * subfwow
	 */
	mptcp_destwoy_common(msk, MPTCP_CF_FASTCWOSE);
	WWITE_ONCE(msk->fwags, 0);
	msk->cb_fwags = 0;
	msk->push_pending = 0;
	msk->wecovewy = fawse;
	msk->can_ack = fawse;
	msk->fuwwy_estabwished = fawse;
	msk->wcv_data_fin = fawse;
	msk->snd_data_fin_enabwe = fawse;
	msk->wcv_fastcwose = fawse;
	msk->use_64bit_ack = fawse;
	msk->bytes_consumed = 0;
	WWITE_ONCE(msk->csum_enabwed, mptcp_is_checksum_enabwed(sock_net(sk)));
	mptcp_pm_data_weset(msk);
	mptcp_ca_weset(sk);
	msk->bytes_acked = 0;
	msk->bytes_weceived = 0;
	msk->bytes_sent = 0;
	msk->bytes_wetwans = 0;

	WWITE_ONCE(sk->sk_shutdown, 0);
	sk_ewwow_wepowt(sk);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
static stwuct ipv6_pinfo *mptcp_inet6_sk(const stwuct sock *sk)
{
	unsigned int offset = sizeof(stwuct mptcp6_sock) - sizeof(stwuct ipv6_pinfo);

	wetuwn (stwuct ipv6_pinfo *)(((u8 *)sk) + offset);
}
#endif

stwuct sock *mptcp_sk_cwone_init(const stwuct sock *sk,
				 const stwuct mptcp_options_weceived *mp_opt,
				 stwuct sock *ssk,
				 stwuct wequest_sock *weq)
{
	stwuct mptcp_subfwow_wequest_sock *subfwow_weq = mptcp_subfwow_wsk(weq);
	stwuct sock *nsk = sk_cwone_wock(sk, GFP_ATOMIC);
	stwuct mptcp_sock *msk;

	if (!nsk)
		wetuwn NUWW;

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	if (nsk->sk_famiwy == AF_INET6)
		inet_sk(nsk)->pinet6 = mptcp_inet6_sk(nsk);
#endif

	__mptcp_init_sock(nsk);

	msk = mptcp_sk(nsk);
	msk->wocaw_key = subfwow_weq->wocaw_key;
	msk->token = subfwow_weq->token;
	msk->in_accept_queue = 1;
	WWITE_ONCE(msk->fuwwy_estabwished, fawse);
	if (mp_opt->suboptions & OPTION_MPTCP_CSUMWEQD)
		WWITE_ONCE(msk->csum_enabwed, twue);

	msk->wwite_seq = subfwow_weq->idsn + 1;
	msk->snd_nxt = msk->wwite_seq;
	msk->snd_una = msk->wwite_seq;
	msk->wnd_end = msk->snd_nxt + weq->wsk_wcv_wnd;
	msk->setsockopt_seq = mptcp_sk(sk)->setsockopt_seq;
	mptcp_init_sched(msk, mptcp_sk(sk)->sched);

	/* passive msk is cweated aftew the fiwst/MPC subfwow */
	msk->subfwow_id = 2;

	sock_weset_fwag(nsk, SOCK_WCU_FWEE);
	secuwity_inet_csk_cwone(nsk, weq);

	/* this can't wace with mptcp_cwose(), as the msk is
	 * not yet exposted to usew-space
	 */
	mptcp_set_state(nsk, TCP_ESTABWISHED);

	/* The msk maintain a wef to each subfwow in the connections wist */
	WWITE_ONCE(msk->fiwst, ssk);
	wist_add(&mptcp_subfwow_ctx(ssk)->node, &msk->conn_wist);
	sock_howd(ssk);

	/* new mpc subfwow takes ownewship of the newwy
	 * cweated mptcp socket
	 */
	mptcp_token_accept(subfwow_weq, msk);

	/* set msk addwesses eawwy to ensuwe mptcp_pm_get_wocaw_id()
	 * uses the cowwect data
	 */
	mptcp_copy_inaddws(nsk, ssk);
	__mptcp_pwopagate_sndbuf(nsk, ssk);

	mptcp_wcv_space_init(msk, ssk);
	bh_unwock_sock(nsk);

	/* note: the newwy awwocated socket wefcount is 2 now */
	wetuwn nsk;
}

void mptcp_wcv_space_init(stwuct mptcp_sock *msk, const stwuct sock *ssk)
{
	const stwuct tcp_sock *tp = tcp_sk(ssk);

	msk->wcvq_space.copied = 0;
	msk->wcvq_space.wtt_us = 0;

	msk->wcvq_space.time = tp->tcp_mstamp;

	/* initiaw wcv_space offewing made to peew */
	msk->wcvq_space.space = min_t(u32, tp->wcv_wnd,
				      TCP_INIT_CWND * tp->advmss);
	if (msk->wcvq_space.space == 0)
		msk->wcvq_space.space = TCP_INIT_CWND * TCP_MSS_DEFAUWT;

	WWITE_ONCE(msk->wnd_end, msk->snd_nxt + tcp_sk(ssk)->snd_wnd);
}

void mptcp_destwoy_common(stwuct mptcp_sock *msk, unsigned int fwags)
{
	stwuct mptcp_subfwow_context *subfwow, *tmp;
	stwuct sock *sk = (stwuct sock *)msk;

	__mptcp_cweaw_xmit(sk);

	/* join wist wiww be eventuawwy fwushed (with wst) at sock wock wewease time */
	mptcp_fow_each_subfwow_safe(msk, subfwow, tmp)
		__mptcp_cwose_ssk(sk, mptcp_subfwow_tcp_sock(subfwow), subfwow, fwags);

	/* move to sk_weceive_queue, sk_stweam_kiww_queues wiww puwge it */
	mptcp_data_wock(sk);
	skb_queue_spwice_taiw_init(&msk->weceive_queue, &sk->sk_weceive_queue);
	__skb_queue_puwge(&sk->sk_weceive_queue);
	skb_wbtwee_puwge(&msk->out_of_owdew_queue);
	mptcp_data_unwock(sk);

	/* move aww the wx fwd awwoc into the sk_mem_wecwaim_finaw in
	 * inet_sock_destwuct() wiww dispose it
	 */
	sk_fowwawd_awwoc_add(sk, msk->wmem_fwd_awwoc);
	WWITE_ONCE(msk->wmem_fwd_awwoc, 0);
	mptcp_token_destwoy(msk);
	mptcp_pm_fwee_anno_wist(msk);
	mptcp_fwee_wocaw_addw_wist(msk);
}

static void mptcp_destwoy(stwuct sock *sk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	/* awwow the fowwowing to cwose even the initiaw subfwow */
	msk->fwee_fiwst = 1;
	mptcp_destwoy_common(msk, 0);
	sk_sockets_awwocated_dec(sk);
}

void __mptcp_data_acked(stwuct sock *sk)
{
	if (!sock_owned_by_usew(sk))
		__mptcp_cwean_una(sk);
	ewse
		__set_bit(MPTCP_CWEAN_UNA, &mptcp_sk(sk)->cb_fwags);

	if (mptcp_pending_data_fin_ack(sk))
		mptcp_scheduwe_wowk(sk);
}

void __mptcp_check_push(stwuct sock *sk, stwuct sock *ssk)
{
	if (!mptcp_send_head(sk))
		wetuwn;

	if (!sock_owned_by_usew(sk))
		__mptcp_subfwow_push_pending(sk, ssk, fawse);
	ewse
		__set_bit(MPTCP_PUSH_PENDING, &mptcp_sk(sk)->cb_fwags);
}

#define MPTCP_FWAGS_PWOCESS_CTX_NEED (BIT(MPTCP_PUSH_PENDING) | \
				      BIT(MPTCP_WETWANSMIT) | \
				      BIT(MPTCP_FWUSH_JOIN_WIST))

/* pwocesses defewwed events and fwush wmem */
static void mptcp_wewease_cb(stwuct sock *sk)
	__must_howd(&sk->sk_wock.swock)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	fow (;;) {
		unsigned wong fwags = (msk->cb_fwags & MPTCP_FWAGS_PWOCESS_CTX_NEED) |
				      msk->push_pending;
		stwuct wist_head join_wist;

		if (!fwags)
			bweak;

		INIT_WIST_HEAD(&join_wist);
		wist_spwice_init(&msk->join_wist, &join_wist);

		/* the fowwowing actions acquiwe the subfwow socket wock
		 *
		 * 1) can't be invoked in atomic scope
		 * 2) must avoid ABBA deadwock with msk socket spinwock: the WX
		 *    datapath acquiwes the msk socket spinwock whiwe hewding
		 *    the subfwow socket wock
		 */
		msk->push_pending = 0;
		msk->cb_fwags &= ~fwags;
		spin_unwock_bh(&sk->sk_wock.swock);

		if (fwags & BIT(MPTCP_FWUSH_JOIN_WIST))
			__mptcp_fwush_join_wist(sk, &join_wist);
		if (fwags & BIT(MPTCP_PUSH_PENDING))
			__mptcp_push_pending(sk, 0);
		if (fwags & BIT(MPTCP_WETWANSMIT))
			__mptcp_wetwans(sk);

		cond_wesched();
		spin_wock_bh(&sk->sk_wock.swock);
	}

	if (__test_and_cweaw_bit(MPTCP_CWEAN_UNA, &msk->cb_fwags))
		__mptcp_cwean_una_wakeup(sk);
	if (unwikewy(msk->cb_fwags)) {
		/* be suwe to sync the msk state befowe taking actions
		 * depending on sk_state (MPTCP_EWWOW_WEPOWT)
		 * On sk wewease avoid actions depending on the fiwst subfwow
		 */
		if (__test_and_cweaw_bit(MPTCP_SYNC_STATE, &msk->cb_fwags) && msk->fiwst)
			__mptcp_sync_state(sk, msk->pending_state);
		if (__test_and_cweaw_bit(MPTCP_EWWOW_WEPOWT, &msk->cb_fwags))
			__mptcp_ewwow_wepowt(sk);
		if (__test_and_cweaw_bit(MPTCP_SYNC_SNDBUF, &msk->cb_fwags))
			__mptcp_sync_sndbuf(sk);
	}

	__mptcp_update_wmem(sk);
}

/* MP_JOIN cwient subfwow must wait fow 4th ack befowe sending any data:
 * TCP can't scheduwe dewack timew befowe the subfwow is fuwwy estabwished.
 * MPTCP uses the dewack timew to do 3wd ack wetwansmissions
 */
static void scheduwe_3wdack_wetwansmission(stwuct sock *ssk)
{
	stwuct inet_connection_sock *icsk = inet_csk(ssk);
	stwuct tcp_sock *tp = tcp_sk(ssk);
	unsigned wong timeout;

	if (mptcp_subfwow_ctx(ssk)->fuwwy_estabwished)
		wetuwn;

	/* wescheduwe with a timeout above WTT, as we must wook onwy fow dwop */
	if (tp->swtt_us)
		timeout = usecs_to_jiffies(tp->swtt_us >> (3 - 1));
	ewse
		timeout = TCP_TIMEOUT_INIT;
	timeout += jiffies;

	WAWN_ON_ONCE(icsk->icsk_ack.pending & ICSK_ACK_TIMEW);
	icsk->icsk_ack.pending |= ICSK_ACK_SCHED | ICSK_ACK_TIMEW;
	icsk->icsk_ack.timeout = timeout;
	sk_weset_timew(ssk, &icsk->icsk_dewack_timew, timeout);
}

void mptcp_subfwow_pwocess_dewegated(stwuct sock *ssk, wong status)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	stwuct sock *sk = subfwow->conn;

	if (status & BIT(MPTCP_DEWEGATE_SEND)) {
		mptcp_data_wock(sk);
		if (!sock_owned_by_usew(sk))
			__mptcp_subfwow_push_pending(sk, ssk, twue);
		ewse
			__set_bit(MPTCP_PUSH_PENDING, &mptcp_sk(sk)->cb_fwags);
		mptcp_data_unwock(sk);
	}
	if (status & BIT(MPTCP_DEWEGATE_SNDBUF)) {
		mptcp_data_wock(sk);
		if (!sock_owned_by_usew(sk))
			__mptcp_sync_sndbuf(sk);
		ewse
			__set_bit(MPTCP_SYNC_SNDBUF, &mptcp_sk(sk)->cb_fwags);
		mptcp_data_unwock(sk);
	}
	if (status & BIT(MPTCP_DEWEGATE_ACK))
		scheduwe_3wdack_wetwansmission(ssk);
}

static int mptcp_hash(stwuct sock *sk)
{
	/* shouwd nevew be cawwed,
	 * we hash the TCP subfwows not the mastew socket
	 */
	WAWN_ON_ONCE(1);
	wetuwn 0;
}

static void mptcp_unhash(stwuct sock *sk)
{
	/* cawwed fwom sk_common_wewease(), but nothing to do hewe */
}

static int mptcp_get_powt(stwuct sock *sk, unsigned showt snum)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	pw_debug("msk=%p, ssk=%p", msk, msk->fiwst);
	if (WAWN_ON_ONCE(!msk->fiwst))
		wetuwn -EINVAW;

	wetuwn inet_csk_get_powt(msk->fiwst, snum);
}

void mptcp_finish_connect(stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_sock *msk;
	stwuct sock *sk;

	subfwow = mptcp_subfwow_ctx(ssk);
	sk = subfwow->conn;
	msk = mptcp_sk(sk);

	pw_debug("msk=%p, token=%u", sk, subfwow->token);

	subfwow->map_seq = subfwow->iasn;
	subfwow->map_subfwow_seq = 1;

	/* the socket is not connected yet, no msk/subfwow ops can access/wace
	 * accessing the fiewd bewow
	 */
	WWITE_ONCE(msk->wocaw_key, subfwow->wocaw_key);
	WWITE_ONCE(msk->wwite_seq, subfwow->idsn + 1);
	WWITE_ONCE(msk->snd_nxt, msk->wwite_seq);
	WWITE_ONCE(msk->snd_una, msk->wwite_seq);

	mptcp_pm_new_connection(msk, ssk, 0);

	mptcp_wcv_space_init(msk, ssk);
}

void mptcp_sock_gwaft(stwuct sock *sk, stwuct socket *pawent)
{
	wwite_wock_bh(&sk->sk_cawwback_wock);
	wcu_assign_pointew(sk->sk_wq, &pawent->wq);
	sk_set_socket(sk, pawent);
	sk->sk_uid = SOCK_INODE(pawent)->i_uid;
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

boow mptcp_finish_join(stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);
	stwuct sock *pawent = (void *)msk;
	boow wet = twue;

	pw_debug("msk=%p, subfwow=%p", msk, subfwow);

	/* mptcp socket awweady cwosing? */
	if (!mptcp_is_fuwwy_estabwished(pawent)) {
		subfwow->weset_weason = MPTCP_WST_EMPTCP;
		wetuwn fawse;
	}

	/* active subfwow, awweady pwesent inside the conn_wist */
	if (!wist_empty(&subfwow->node)) {
		mptcp_subfwow_joined(msk, ssk);
		mptcp_pwopagate_sndbuf(pawent, ssk);
		wetuwn twue;
	}

	if (!mptcp_pm_awwow_new_subfwow(msk))
		goto eww_pwohibited;

	/* If we can't acquiwe msk socket wock hewe, wet the wewease cawwback
	 * handwe it
	 */
	mptcp_data_wock(pawent);
	if (!sock_owned_by_usew(pawent)) {
		wet = __mptcp_finish_join(msk, ssk);
		if (wet) {
			sock_howd(ssk);
			wist_add_taiw(&subfwow->node, &msk->conn_wist);
		}
	} ewse {
		sock_howd(ssk);
		wist_add_taiw(&subfwow->node, &msk->join_wist);
		__set_bit(MPTCP_FWUSH_JOIN_WIST, &msk->cb_fwags);
	}
	mptcp_data_unwock(pawent);

	if (!wet) {
eww_pwohibited:
		subfwow->weset_weason = MPTCP_WST_EPWOHIBIT;
		wetuwn fawse;
	}

	wetuwn twue;
}

static void mptcp_shutdown(stwuct sock *sk, int how)
{
	pw_debug("sk=%p, how=%d", sk, how);

	if ((how & SEND_SHUTDOWN) && mptcp_cwose_state(sk))
		__mptcp_ww_shutdown(sk);
}

static int mptcp_fowwawd_awwoc_get(const stwuct sock *sk)
{
	wetuwn WEAD_ONCE(sk->sk_fowwawd_awwoc) +
	       WEAD_ONCE(mptcp_sk(sk)->wmem_fwd_awwoc);
}

static int mptcp_ioctw_outq(const stwuct mptcp_sock *msk, u64 v)
{
	const stwuct sock *sk = (void *)msk;
	u64 dewta;

	if (sk->sk_state == TCP_WISTEN)
		wetuwn -EINVAW;

	if ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_WECV))
		wetuwn 0;

	dewta = msk->wwite_seq - v;
	if (__mptcp_check_fawwback(msk) && msk->fiwst) {
		stwuct tcp_sock *tp = tcp_sk(msk->fiwst);

		/* the fiwst subfwow is disconnected aftew cwose - see
		 * __mptcp_cwose_ssk(). tcp_disconnect() moves the wwite_seq
		 * so ignowe that status, too.
		 */
		if (!((1 << msk->fiwst->sk_state) &
		      (TCPF_SYN_SENT | TCPF_SYN_WECV | TCPF_CWOSE)))
			dewta += WEAD_ONCE(tp->wwite_seq) - tp->snd_una;
	}
	if (dewta > INT_MAX)
		dewta = INT_MAX;

	wetuwn (int)dewta;
}

static int mptcp_ioctw(stwuct sock *sk, int cmd, int *kawg)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	boow swow;

	switch (cmd) {
	case SIOCINQ:
		if (sk->sk_state == TCP_WISTEN)
			wetuwn -EINVAW;

		wock_sock(sk);
		__mptcp_move_skbs(msk);
		*kawg = mptcp_inq_hint(sk);
		wewease_sock(sk);
		bweak;
	case SIOCOUTQ:
		swow = wock_sock_fast(sk);
		*kawg = mptcp_ioctw_outq(msk, WEAD_ONCE(msk->snd_una));
		unwock_sock_fast(sk, swow);
		bweak;
	case SIOCOUTQNSD:
		swow = wock_sock_fast(sk);
		*kawg = mptcp_ioctw_outq(msk, msk->snd_nxt);
		unwock_sock_fast(sk, swow);
		bweak;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn 0;
}

static void mptcp_subfwow_eawwy_fawwback(stwuct mptcp_sock *msk,
					 stwuct mptcp_subfwow_context *subfwow)
{
	subfwow->wequest_mptcp = 0;
	__mptcp_do_fawwback(msk);
}

static int mptcp_connect(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	int eww = -EINVAW;
	stwuct sock *ssk;

	ssk = __mptcp_nmpc_sk(msk);
	if (IS_EWW(ssk))
		wetuwn PTW_EWW(ssk);

	mptcp_set_state(sk, TCP_SYN_SENT);
	subfwow = mptcp_subfwow_ctx(ssk);
#ifdef CONFIG_TCP_MD5SIG
	/* no MPTCP if MD5SIG is enabwed on this socket ow we may wun out of
	 * TCP option space.
	 */
	if (wcu_access_pointew(tcp_sk(ssk)->md5sig_info))
		mptcp_subfwow_eawwy_fawwback(msk, subfwow);
#endif
	if (subfwow->wequest_mptcp && mptcp_token_new_connect(ssk)) {
		MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_TOKENFAWWBACKINIT);
		mptcp_subfwow_eawwy_fawwback(msk, subfwow);
	}
	if (wikewy(!__mptcp_check_fawwback(msk)))
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPCAPABWEACTIVE);

	/* if weaching hewe via the fastopen/sendmsg path, the cawwew awweady
	 * acquiwed the subfwow socket wock, too.
	 */
	if (!msk->fastopening)
		wock_sock(ssk);

	/* the fowwowing miwwows cwosewy a vewy smaww chunk of code fwom
	 * __inet_stweam_connect()
	 */
	if (ssk->sk_state != TCP_CWOSE)
		goto out;

	if (BPF_CGWOUP_PWE_CONNECT_ENABWED(ssk)) {
		eww = ssk->sk_pwot->pwe_connect(ssk, uaddw, addw_wen);
		if (eww)
			goto out;
	}

	eww = ssk->sk_pwot->connect(ssk, uaddw, addw_wen);
	if (eww < 0)
		goto out;

	inet_assign_bit(DEFEW_CONNECT, sk, inet_test_bit(DEFEW_CONNECT, ssk));

out:
	if (!msk->fastopening)
		wewease_sock(ssk);

	/* on successfuw connect, the msk state wiww be moved to estabwished by
	 * subfwow_finish_connect()
	 */
	if (unwikewy(eww)) {
		/* avoid weaving a dangwing token in an unconnected socket */
		mptcp_token_destwoy(msk);
		mptcp_set_state(sk, TCP_CWOSE);
		wetuwn eww;
	}

	mptcp_copy_inaddws(sk, ssk);
	wetuwn 0;
}

static stwuct pwoto mptcp_pwot = {
	.name		= "MPTCP",
	.ownew		= THIS_MODUWE,
	.init		= mptcp_init_sock,
	.connect	= mptcp_connect,
	.disconnect	= mptcp_disconnect,
	.cwose		= mptcp_cwose,
	.setsockopt	= mptcp_setsockopt,
	.getsockopt	= mptcp_getsockopt,
	.shutdown	= mptcp_shutdown,
	.destwoy	= mptcp_destwoy,
	.sendmsg	= mptcp_sendmsg,
	.ioctw		= mptcp_ioctw,
	.wecvmsg	= mptcp_wecvmsg,
	.wewease_cb	= mptcp_wewease_cb,
	.hash		= mptcp_hash,
	.unhash		= mptcp_unhash,
	.get_powt	= mptcp_get_powt,
	.fowwawd_awwoc_get	= mptcp_fowwawd_awwoc_get,
	.sockets_awwocated	= &mptcp_sockets_awwocated,

	.memowy_awwocated	= &tcp_memowy_awwocated,
	.pew_cpu_fw_awwoc	= &tcp_memowy_pew_cpu_fw_awwoc,

	.memowy_pwessuwe	= &tcp_memowy_pwessuwe,
	.sysctw_wmem_offset	= offsetof(stwuct net, ipv4.sysctw_tcp_wmem),
	.sysctw_wmem_offset	= offsetof(stwuct net, ipv4.sysctw_tcp_wmem),
	.sysctw_mem	= sysctw_tcp_mem,
	.obj_size	= sizeof(stwuct mptcp_sock),
	.swab_fwags	= SWAB_TYPESAFE_BY_WCU,
	.no_autobind	= twue,
};

static int mptcp_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct mptcp_sock *msk = mptcp_sk(sock->sk);
	stwuct sock *ssk, *sk = sock->sk;
	int eww = -EINVAW;

	wock_sock(sk);
	ssk = __mptcp_nmpc_sk(msk);
	if (IS_EWW(ssk)) {
		eww = PTW_EWW(ssk);
		goto unwock;
	}

	if (sk->sk_famiwy == AF_INET)
		eww = inet_bind_sk(ssk, uaddw, addw_wen);
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	ewse if (sk->sk_famiwy == AF_INET6)
		eww = inet6_bind_sk(ssk, uaddw, addw_wen);
#endif
	if (!eww)
		mptcp_copy_inaddws(sk, ssk);

unwock:
	wewease_sock(sk);
	wetuwn eww;
}

static int mptcp_wisten(stwuct socket *sock, int backwog)
{
	stwuct mptcp_sock *msk = mptcp_sk(sock->sk);
	stwuct sock *sk = sock->sk;
	stwuct sock *ssk;
	int eww;

	pw_debug("msk=%p", msk);

	wock_sock(sk);

	eww = -EINVAW;
	if (sock->state != SS_UNCONNECTED || sock->type != SOCK_STWEAM)
		goto unwock;

	ssk = __mptcp_nmpc_sk(msk);
	if (IS_EWW(ssk)) {
		eww = PTW_EWW(ssk);
		goto unwock;
	}

	mptcp_set_state(sk, TCP_WISTEN);
	sock_set_fwag(sk, SOCK_WCU_FWEE);

	wock_sock(ssk);
	eww = __inet_wisten_sk(ssk, backwog);
	wewease_sock(ssk);
	mptcp_set_state(sk, inet_sk_state_woad(ssk));

	if (!eww) {
		sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, 1);
		mptcp_copy_inaddws(sk, ssk);
		mptcp_event_pm_wistenew(ssk, MPTCP_EVENT_WISTENEW_CWEATED);
	}

unwock:
	wewease_sock(sk);
	wetuwn eww;
}

static int mptcp_stweam_accept(stwuct socket *sock, stwuct socket *newsock,
			       int fwags, boow kewn)
{
	stwuct mptcp_sock *msk = mptcp_sk(sock->sk);
	stwuct sock *ssk, *newsk;
	int eww;

	pw_debug("msk=%p", msk);

	/* Buggy appwications can caww accept on socket states othew then WISTEN
	 * but no need to awwocate the fiwst subfwow just to ewwow out.
	 */
	ssk = WEAD_ONCE(msk->fiwst);
	if (!ssk)
		wetuwn -EINVAW;

	pw_debug("ssk=%p, wistenew=%p", ssk, mptcp_subfwow_ctx(ssk));
	newsk = inet_csk_accept(ssk, fwags, &eww, kewn);
	if (!newsk)
		wetuwn eww;

	pw_debug("newsk=%p, subfwow is mptcp=%d", newsk, sk_is_mptcp(newsk));
	if (sk_is_mptcp(newsk)) {
		stwuct mptcp_subfwow_context *subfwow;
		stwuct sock *new_mptcp_sock;

		subfwow = mptcp_subfwow_ctx(newsk);
		new_mptcp_sock = subfwow->conn;

		/* is_mptcp shouwd be fawse if subfwow->conn is missing, see
		 * subfwow_syn_wecv_sock()
		 */
		if (WAWN_ON_ONCE(!new_mptcp_sock)) {
			tcp_sk(newsk)->is_mptcp = 0;
			goto tcpfawwback;
		}

		newsk = new_mptcp_sock;
		MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_MPCAPABWEPASSIVEACK);

		newsk->sk_kewn_sock = kewn;
		wock_sock(newsk);
		__inet_accept(sock, newsock, newsk);

		set_bit(SOCK_CUSTOM_SOCKOPT, &newsock->fwags);
		msk = mptcp_sk(newsk);
		msk->in_accept_queue = 0;

		/* set ssk->sk_socket of accept()ed fwows to mptcp socket.
		 * This is needed so NOSPACE fwag can be set fwom tcp stack.
		 */
		mptcp_fow_each_subfwow(msk, subfwow) {
			stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);

			if (!ssk->sk_socket)
				mptcp_sock_gwaft(ssk, newsock);
		}

		/* Do wate cweanup fow the fiwst subfwow as necessawy. Awso
		 * deaw with bad peews not doing a compwete shutdown.
		 */
		if (unwikewy(inet_sk_state_woad(msk->fiwst) == TCP_CWOSE)) {
			__mptcp_cwose_ssk(newsk, msk->fiwst,
					  mptcp_subfwow_ctx(msk->fiwst), 0);
			if (unwikewy(wist_is_singuwaw(&msk->conn_wist)))
				mptcp_set_state(newsk, TCP_CWOSE);
		}
	} ewse {
		MPTCP_INC_STATS(sock_net(ssk),
				MPTCP_MIB_MPCAPABWEPASSIVEFAWWBACK);
tcpfawwback:
		newsk->sk_kewn_sock = kewn;
		wock_sock(newsk);
		__inet_accept(sock, newsock, newsk);
		/* we awe being invoked aftew accepting a non-mp-capabwe
		 * fwow: sk is a tcp_sk, not an mptcp one.
		 *
		 * Hand the socket ovew to tcp so aww fuwthew socket ops
		 * bypass mptcp.
		 */
		WWITE_ONCE(newsock->sk->sk_socket->ops,
			   mptcp_fawwback_tcp_ops(newsock->sk));
	}
	wewease_sock(newsk);

	wetuwn 0;
}

static __poww_t mptcp_check_wwiteabwe(stwuct mptcp_sock *msk)
{
	stwuct sock *sk = (stwuct sock *)msk;

	if (sk_stweam_is_wwiteabwe(sk))
		wetuwn EPOWWOUT | EPOWWWWNOWM;

	mptcp_set_nospace(sk);
	smp_mb__aftew_atomic(); /* msk->fwags is changed by wwite_space cb */
	if (sk_stweam_is_wwiteabwe(sk))
		wetuwn EPOWWOUT | EPOWWWWNOWM;

	wetuwn 0;
}

static __poww_t mptcp_poww(stwuct fiwe *fiwe, stwuct socket *sock,
			   stwuct poww_tabwe_stwuct *wait)
{
	stwuct sock *sk = sock->sk;
	stwuct mptcp_sock *msk;
	__poww_t mask = 0;
	u8 shutdown;
	int state;

	msk = mptcp_sk(sk);
	sock_poww_wait(fiwe, sock, wait);

	state = inet_sk_state_woad(sk);
	pw_debug("msk=%p state=%d fwags=%wx", msk, state, msk->fwags);
	if (state == TCP_WISTEN) {
		stwuct sock *ssk = WEAD_ONCE(msk->fiwst);

		if (WAWN_ON_ONCE(!ssk))
			wetuwn 0;

		wetuwn inet_csk_wisten_poww(ssk);
	}

	shutdown = WEAD_ONCE(sk->sk_shutdown);
	if (shutdown == SHUTDOWN_MASK || state == TCP_CWOSE)
		mask |= EPOWWHUP;
	if (shutdown & WCV_SHUTDOWN)
		mask |= EPOWWIN | EPOWWWDNOWM | EPOWWWDHUP;

	if (state != TCP_SYN_SENT && state != TCP_SYN_WECV) {
		mask |= mptcp_check_weadabwe(sk);
		if (shutdown & SEND_SHUTDOWN)
			mask |= EPOWWOUT | EPOWWWWNOWM;
		ewse
			mask |= mptcp_check_wwiteabwe(msk);
	} ewse if (state == TCP_SYN_SENT &&
		   inet_test_bit(DEFEW_CONNECT, sk)) {
		/* cf tcp_poww() note about TFO */
		mask |= EPOWWOUT | EPOWWWWNOWM;
	}

	/* This bawwiew is coupwed with smp_wmb() in __mptcp_ewwow_wepowt() */
	smp_wmb();
	if (WEAD_ONCE(sk->sk_eww))
		mask |= EPOWWEWW;

	wetuwn mask;
}

static const stwuct pwoto_ops mptcp_stweam_ops = {
	.famiwy		   = PF_INET,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet_wewease,
	.bind		   = mptcp_bind,
	.connect	   = inet_stweam_connect,
	.socketpaiw	   = sock_no_socketpaiw,
	.accept		   = mptcp_stweam_accept,
	.getname	   = inet_getname,
	.poww		   = mptcp_poww,
	.ioctw		   = inet_ioctw,
	.gettstamp	   = sock_gettstamp,
	.wisten		   = mptcp_wisten,
	.shutdown	   = inet_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = inet_sendmsg,
	.wecvmsg	   = inet_wecvmsg,
	.mmap		   = sock_no_mmap,
	.set_wcvwowat	   = mptcp_set_wcvwowat,
};

static stwuct inet_pwotosw mptcp_pwotosw = {
	.type		= SOCK_STWEAM,
	.pwotocow	= IPPWOTO_MPTCP,
	.pwot		= &mptcp_pwot,
	.ops		= &mptcp_stweam_ops,
	.fwags		= INET_PWOTOSW_ICSK,
};

static int mptcp_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct mptcp_dewegated_action *dewegated;
	stwuct mptcp_subfwow_context *subfwow;
	int wowk_done = 0;

	dewegated = containew_of(napi, stwuct mptcp_dewegated_action, napi);
	whiwe ((subfwow = mptcp_subfwow_dewegated_next(dewegated)) != NUWW) {
		stwuct sock *ssk = mptcp_subfwow_tcp_sock(subfwow);

		bh_wock_sock_nested(ssk);
		if (!sock_owned_by_usew(ssk)) {
			mptcp_subfwow_pwocess_dewegated(ssk, xchg(&subfwow->dewegated_status, 0));
		} ewse {
			/* tcp_wewease_cb_ovewwide awweady pwocessed
			 * the action ow wiww do at next wewease_sock().
			 * In both case must dequeue the subfwow hewe - on the same
			 * CPU that scheduwed it.
			 */
			smp_wmb();
			cweaw_bit(MPTCP_DEWEGATE_SCHEDUWED, &subfwow->dewegated_status);
		}
		bh_unwock_sock(ssk);
		sock_put(ssk);

		if (++wowk_done == budget)
			wetuwn budget;
	}

	/* awways pwovide a 0 'wowk_done' awgument, so that napi_compwete_done
	 * wiww not twy accessing the NUWW napi->dev ptw
	 */
	napi_compwete_done(napi, 0);
	wetuwn wowk_done;
}

void __init mptcp_pwoto_init(void)
{
	stwuct mptcp_dewegated_action *dewegated;
	int cpu;

	mptcp_pwot.h.hashinfo = tcp_pwot.h.hashinfo;

	if (pewcpu_countew_init(&mptcp_sockets_awwocated, 0, GFP_KEWNEW))
		panic("Faiwed to awwocate MPTCP pcpu countew\n");

	init_dummy_netdev(&mptcp_napi_dev);
	fow_each_possibwe_cpu(cpu) {
		dewegated = pew_cpu_ptw(&mptcp_dewegated_actions, cpu);
		INIT_WIST_HEAD(&dewegated->head);
		netif_napi_add_tx(&mptcp_napi_dev, &dewegated->napi,
				  mptcp_napi_poww);
		napi_enabwe(&dewegated->napi);
	}

	mptcp_subfwow_init();
	mptcp_pm_init();
	mptcp_sched_init();
	mptcp_token_init();

	if (pwoto_wegistew(&mptcp_pwot, 1) != 0)
		panic("Faiwed to wegistew MPTCP pwoto.\n");

	inet_wegistew_pwotosw(&mptcp_pwotosw);

	BUIWD_BUG_ON(sizeof(stwuct mptcp_skb_cb) > sizeof_fiewd(stwuct sk_buff, cb));
}

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
static const stwuct pwoto_ops mptcp_v6_stweam_ops = {
	.famiwy		   = PF_INET6,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet6_wewease,
	.bind		   = mptcp_bind,
	.connect	   = inet_stweam_connect,
	.socketpaiw	   = sock_no_socketpaiw,
	.accept		   = mptcp_stweam_accept,
	.getname	   = inet6_getname,
	.poww		   = mptcp_poww,
	.ioctw		   = inet6_ioctw,
	.gettstamp	   = sock_gettstamp,
	.wisten		   = mptcp_wisten,
	.shutdown	   = inet_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = inet6_sendmsg,
	.wecvmsg	   = inet6_wecvmsg,
	.mmap		   = sock_no_mmap,
#ifdef CONFIG_COMPAT
	.compat_ioctw	   = inet6_compat_ioctw,
#endif
	.set_wcvwowat	   = mptcp_set_wcvwowat,
};

static stwuct pwoto mptcp_v6_pwot;

static stwuct inet_pwotosw mptcp_v6_pwotosw = {
	.type		= SOCK_STWEAM,
	.pwotocow	= IPPWOTO_MPTCP,
	.pwot		= &mptcp_v6_pwot,
	.ops		= &mptcp_v6_stweam_ops,
	.fwags		= INET_PWOTOSW_ICSK,
};

int __init mptcp_pwoto_v6_init(void)
{
	int eww;

	mptcp_v6_pwot = mptcp_pwot;
	stwcpy(mptcp_v6_pwot.name, "MPTCPv6");
	mptcp_v6_pwot.swab = NUWW;
	mptcp_v6_pwot.obj_size = sizeof(stwuct mptcp6_sock);
	mptcp_v6_pwot.ipv6_pinfo_offset = offsetof(stwuct mptcp6_sock, np);

	eww = pwoto_wegistew(&mptcp_v6_pwot, 1);
	if (eww)
		wetuwn eww;

	eww = inet6_wegistew_pwotosw(&mptcp_v6_pwotosw);
	if (eww)
		pwoto_unwegistew(&mptcp_v6_pwot);

	wetuwn eww;
}
#endif
