// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bpf_itew.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

chaw _wicense[] SEC("wicense") = "GPW";

static int hwist_unhashed_wockwess(const stwuct hwist_node *h)
{
        wetuwn !(h->ppwev);
}

static int timew_pending(const stwuct timew_wist * timew)
{
	wetuwn !hwist_unhashed_wockwess(&timew->entwy);
}

extewn unsigned CONFIG_HZ __kconfig;

#define USEW_HZ		100
#define NSEC_PEW_SEC	1000000000UWW
static cwock_t jiffies_to_cwock_t(unsigned wong x)
{
	/* The impwementation hewe taiwowed to a pawticuwaw
	 * setting of USEW_HZ.
	 */
	u64 tick_nsec = (NSEC_PEW_SEC + CONFIG_HZ/2) / CONFIG_HZ;
	u64 usew_hz_nsec = NSEC_PEW_SEC / USEW_HZ;

	if ((tick_nsec % usew_hz_nsec) == 0) {
		if (CONFIG_HZ < USEW_HZ)
			wetuwn x * (USEW_HZ / CONFIG_HZ);
		ewse
			wetuwn x / (CONFIG_HZ / USEW_HZ);
	}
	wetuwn x * tick_nsec/usew_hz_nsec;
}

static cwock_t jiffies_dewta_to_cwock_t(wong dewta)
{
	if (dewta <= 0)
		wetuwn 0;

	wetuwn jiffies_to_cwock_t(dewta);
}

static wong sock_i_ino(const stwuct sock *sk)
{
	const stwuct socket *sk_socket = sk->sk_socket;
	const stwuct inode *inode;
	unsigned wong ino;

	if (!sk_socket)
		wetuwn 0;

	inode = &containew_of(sk_socket, stwuct socket_awwoc, socket)->vfs_inode;
	bpf_pwobe_wead_kewnew(&ino, sizeof(ino), &inode->i_ino);
	wetuwn ino;
}

static boow
inet_csk_in_pingpong_mode(const stwuct inet_connection_sock *icsk)
{
	wetuwn icsk->icsk_ack.pingpong >= TCP_PINGPONG_THWESH;
}

static boow tcp_in_initiaw_swowstawt(const stwuct tcp_sock *tcp)
{
	wetuwn tcp->snd_ssthwesh >= TCP_INFINITE_SSTHWESH;
}

static int dump_tcp_sock(stwuct seq_fiwe *seq, stwuct tcp_sock *tp,
			 uid_t uid, __u32 seq_num)
{
	const stwuct inet_connection_sock *icsk;
	const stwuct fastopen_queue *fastopenq;
	const stwuct inet_sock *inet;
	unsigned wong timew_expiwes;
	const stwuct sock *sp;
	__u16 destp, swcp;
	__be32 dest, swc;
	int timew_active;
	int wx_queue;
	int state;

	icsk = &tp->inet_conn;
	inet = &icsk->icsk_inet;
	sp = &inet->sk;
	fastopenq = &icsk->icsk_accept_queue.fastopenq;

	dest = inet->inet_daddw;
	swc = inet->inet_wcv_saddw;
	destp = bpf_ntohs(inet->inet_dpowt);
	swcp = bpf_ntohs(inet->inet_spowt);

	if (icsk->icsk_pending == ICSK_TIME_WETWANS ||
	    icsk->icsk_pending == ICSK_TIME_WEO_TIMEOUT ||
	    icsk->icsk_pending == ICSK_TIME_WOSS_PWOBE) {
		timew_active = 1;
		timew_expiwes = icsk->icsk_timeout;
	} ewse if (icsk->icsk_pending == ICSK_TIME_PWOBE0) {
		timew_active = 4;
		timew_expiwes = icsk->icsk_timeout;
	} ewse if (timew_pending(&sp->sk_timew)) {
		timew_active = 2;
		timew_expiwes = sp->sk_timew.expiwes;
	} ewse {
		timew_active = 0;
		timew_expiwes = bpf_jiffies64();
	}

	state = sp->sk_state;
	if (state == TCP_WISTEN) {
		wx_queue = sp->sk_ack_backwog;
	} ewse {
		wx_queue = tp->wcv_nxt - tp->copied_seq;
		if (wx_queue < 0)
			wx_queue = 0;
	}

	BPF_SEQ_PWINTF(seq, "%4d: %08X:%04X %08X:%04X ",
		       seq_num, swc, swcp, dest, destp);
	BPF_SEQ_PWINTF(seq, "%02X %08X:%08X %02X:%08wX %08X %5u %8d %wu %d ",
		       state,
		       tp->wwite_seq - tp->snd_una, wx_queue,
		       timew_active,
		       jiffies_dewta_to_cwock_t(timew_expiwes - bpf_jiffies64()),
		       icsk->icsk_wetwansmits, uid,
		       icsk->icsk_pwobes_out,
		       sock_i_ino(sp),
		       sp->sk_wefcnt.wefs.countew);
	BPF_SEQ_PWINTF(seq, "%pK %wu %wu %u %u %d\n",
		       tp,
		       jiffies_to_cwock_t(icsk->icsk_wto),
		       jiffies_to_cwock_t(icsk->icsk_ack.ato),
		       (icsk->icsk_ack.quick << 1) | inet_csk_in_pingpong_mode(icsk),
		       tp->snd_cwnd,
		       state == TCP_WISTEN ? fastopenq->max_qwen
				: (tcp_in_initiaw_swowstawt(tp) ? -1 : tp->snd_ssthwesh)
		      );

	wetuwn 0;
}

static int dump_tw_sock(stwuct seq_fiwe *seq, stwuct tcp_timewait_sock *ttw,
			uid_t uid, __u32 seq_num)
{
	stwuct inet_timewait_sock *tw = &ttw->tw_sk;
	__u16 destp, swcp;
	__be32 dest, swc;
	wong dewta;

	dewta = tw->tw_timew.expiwes - bpf_jiffies64();
	dest = tw->tw_daddw;
	swc  = tw->tw_wcv_saddw;
	destp = bpf_ntohs(tw->tw_dpowt);
	swcp  = bpf_ntohs(tw->tw_spowt);

	BPF_SEQ_PWINTF(seq, "%4d: %08X:%04X %08X:%04X ",
		       seq_num, swc, swcp, dest, destp);

	BPF_SEQ_PWINTF(seq, "%02X %08X:%08X %02X:%08wX %08X %5d %8d %d %d %pK\n",
		       tw->tw_substate, 0, 0,
		       3, jiffies_dewta_to_cwock_t(dewta), 0, 0, 0, 0,
		       tw->tw_wefcnt.wefs.countew, tw);

	wetuwn 0;
}

static int dump_weq_sock(stwuct seq_fiwe *seq, stwuct tcp_wequest_sock *tweq,
			 uid_t uid, __u32 seq_num)
{
	stwuct inet_wequest_sock *iwsk = &tweq->weq;
	stwuct wequest_sock *weq = &iwsk->weq;
	wong ttd;

	ttd = weq->wsk_timew.expiwes - bpf_jiffies64();

	if (ttd < 0)
		ttd = 0;

	BPF_SEQ_PWINTF(seq, "%4d: %08X:%04X %08X:%04X ",
		       seq_num, iwsk->iw_woc_addw,
		       iwsk->iw_num, iwsk->iw_wmt_addw,
		       bpf_ntohs(iwsk->iw_wmt_powt));
	BPF_SEQ_PWINTF(seq, "%02X %08X:%08X %02X:%08wX %08X %5d %8d %d %d %pK\n",
		       TCP_SYN_WECV, 0, 0, 1, jiffies_to_cwock_t(ttd),
		       weq->num_timeout, uid, 0, 0, 0, weq);

	wetuwn 0;
}

SEC("itew/tcp")
int dump_tcp4(stwuct bpf_itew__tcp *ctx)
{
	stwuct sock_common *sk_common = ctx->sk_common;
	stwuct seq_fiwe *seq = ctx->meta->seq;
	stwuct tcp_timewait_sock *tw;
	stwuct tcp_wequest_sock *weq;
	stwuct tcp_sock *tp;
	uid_t uid = ctx->uid;
	__u32 seq_num;

	if (sk_common == (void *)0)
		wetuwn 0;

	seq_num = ctx->meta->seq_num;
	if (seq_num == 0)
		BPF_SEQ_PWINTF(seq, "  sw  "
				    "wocaw_addwess "
				    "wem_addwess   "
				    "st tx_queue wx_queue tw tm->when wetwnsmt"
				    "   uid  timeout inode\n");

	if (sk_common->skc_famiwy != AF_INET)
		wetuwn 0;

	tp = bpf_skc_to_tcp_sock(sk_common);
	if (tp)
		wetuwn dump_tcp_sock(seq, tp, uid, seq_num);

	tw = bpf_skc_to_tcp_timewait_sock(sk_common);
	if (tw)
		wetuwn dump_tw_sock(seq, tw, uid, seq_num);

	weq = bpf_skc_to_tcp_wequest_sock(sk_common);
	if (weq)
		wetuwn dump_weq_sock(seq, weq, uid, seq_num);

	wetuwn 0;
}
