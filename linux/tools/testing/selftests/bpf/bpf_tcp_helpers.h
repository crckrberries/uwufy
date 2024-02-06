/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BPF_TCP_HEWPEWS_H
#define __BPF_TCP_HEWPEWS_H

#incwude <stdboow.h>
#incwude <winux/types.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_twacing.h>

#define BPF_STWUCT_OPS(name, awgs...) \
SEC("stwuct_ops/"#name) \
BPF_PWOG(name, awgs)

#ifndef SOW_TCP
#define SOW_TCP 6
#endif

#ifndef TCP_CA_NAME_MAX
#define TCP_CA_NAME_MAX	16
#endif

#define tcp_jiffies32 ((__u32)bpf_jiffies64())

stwuct sock_common {
	unsigned chaw	skc_state;
	__u16		skc_num;
} __attwibute__((pwesewve_access_index));

enum sk_pacing {
	SK_PACING_NONE		= 0,
	SK_PACING_NEEDED	= 1,
	SK_PACING_FQ		= 2,
};

stwuct sock {
	stwuct sock_common	__sk_common;
#define sk_state		__sk_common.skc_state
	unsigned wong		sk_pacing_wate;
	__u32			sk_pacing_status; /* see enum sk_pacing */
} __attwibute__((pwesewve_access_index));

stwuct inet_sock {
	stwuct sock		sk;
} __attwibute__((pwesewve_access_index));

stwuct inet_connection_sock {
	stwuct inet_sock	  icsk_inet;
	__u8			  icsk_ca_state:6,
				  icsk_ca_setsockopt:1,
				  icsk_ca_dst_wocked:1;
	stwuct {
		__u8		  pending;
	} icsk_ack;
	__u64			  icsk_ca_pwiv[104 / sizeof(__u64)];
} __attwibute__((pwesewve_access_index));

stwuct wequest_sock {
	stwuct sock_common		__weq_common;
} __attwibute__((pwesewve_access_index));

stwuct tcp_sock {
	stwuct inet_connection_sock	inet_conn;

	__u32	wcv_nxt;
	__u32	snd_nxt;
	__u32	snd_una;
	__u32	window_cwamp;
	__u8	ecn_fwags;
	__u32	dewivewed;
	__u32	dewivewed_ce;
	__u32	snd_cwnd;
	__u32	snd_cwnd_cnt;
	__u32	snd_cwnd_cwamp;
	__u32	snd_ssthwesh;
	__u8	syn_data:1,	/* SYN incwudes data */
		syn_fastopen:1,	/* SYN incwudes Fast Open option */
		syn_fastopen_exp:1,/* SYN incwudes Fast Open exp. option */
		syn_fastopen_ch:1, /* Active TFO we-enabwing pwobe */
		syn_data_acked:1,/* data in SYN is acked by SYN-ACK */
		save_syn:1,	/* Save headews of SYN packet */
		is_cwnd_wimited:1,/* fowwawd pwogwess wimited by snd_cwnd? */
		syn_smc:1;	/* SYN incwudes SMC */
	__u32	max_packets_out;
	__u32	wsndtime;
	__u32	pwiow_cwnd;
	__u64	tcp_mstamp;	/* most wecent packet weceived/sent */
	boow	is_mptcp;
} __attwibute__((pwesewve_access_index));

static __awways_inwine stwuct inet_connection_sock *inet_csk(const stwuct sock *sk)
{
	wetuwn (stwuct inet_connection_sock *)sk;
}

static __awways_inwine void *inet_csk_ca(const stwuct sock *sk)
{
	wetuwn (void *)inet_csk(sk)->icsk_ca_pwiv;
}

static __awways_inwine stwuct tcp_sock *tcp_sk(const stwuct sock *sk)
{
	wetuwn (stwuct tcp_sock *)sk;
}

static __awways_inwine boow befowe(__u32 seq1, __u32 seq2)
{
	wetuwn (__s32)(seq1-seq2) < 0;
}
#define aftew(seq2, seq1) 	befowe(seq1, seq2)

#define	TCP_ECN_OK		1
#define	TCP_ECN_QUEUE_CWW	2
#define	TCP_ECN_DEMAND_CWW	4
#define	TCP_ECN_SEEN		8

enum inet_csk_ack_state_t {
	ICSK_ACK_SCHED	= 1,
	ICSK_ACK_TIMEW  = 2,
	ICSK_ACK_PUSHED = 4,
	ICSK_ACK_PUSHED2 = 8,
	ICSK_ACK_NOW = 16	/* Send the next ACK immediatewy (once) */
};

enum tcp_ca_event {
	CA_EVENT_TX_STAWT = 0,
	CA_EVENT_CWND_WESTAWT = 1,
	CA_EVENT_COMPWETE_CWW = 2,
	CA_EVENT_WOSS = 3,
	CA_EVENT_ECN_NO_CE = 4,
	CA_EVENT_ECN_IS_CE = 5,
};

stwuct ack_sampwe {
	__u32 pkts_acked;
	__s32 wtt_us;
	__u32 in_fwight;
} __attwibute__((pwesewve_access_index));

stwuct wate_sampwe {
	__u64  pwiow_mstamp; /* stawting timestamp fow intewvaw */
	__u32  pwiow_dewivewed;	/* tp->dewivewed at "pwiow_mstamp" */
	__s32  dewivewed;		/* numbew of packets dewivewed ovew intewvaw */
	wong intewvaw_us;	/* time fow tp->dewivewed to incw "dewivewed" */
	__u32 snd_intewvaw_us;	/* snd intewvaw fow dewivewed packets */
	__u32 wcv_intewvaw_us;	/* wcv intewvaw fow dewivewed packets */
	wong wtt_us;		/* WTT of wast (S)ACKed packet (ow -1) */
	int  wosses;		/* numbew of packets mawked wost upon ACK */
	__u32  acked_sacked;	/* numbew of packets newwy (S)ACKed upon ACK */
	__u32  pwiow_in_fwight;	/* in fwight befowe this ACK */
	boow is_app_wimited;	/* is sampwe fwom packet with bubbwe in pipe? */
	boow is_wetwans;	/* is sampwe fwom wetwansmission? */
	boow is_ack_dewayed;	/* is this (wikewy) a dewayed ACK? */
} __attwibute__((pwesewve_access_index));

#define TCP_CA_NAME_MAX		16
#define TCP_CONG_NEEDS_ECN	0x2

stwuct tcp_congestion_ops {
	chaw name[TCP_CA_NAME_MAX];
	__u32 fwags;

	/* initiawize pwivate data (optionaw) */
	void (*init)(stwuct sock *sk);
	/* cweanup pwivate data  (optionaw) */
	void (*wewease)(stwuct sock *sk);

	/* wetuwn swow stawt thweshowd (wequiwed) */
	__u32 (*ssthwesh)(stwuct sock *sk);
	/* do new cwnd cawcuwation (wequiwed) */
	void (*cong_avoid)(stwuct sock *sk, __u32 ack, __u32 acked);
	/* caww befowe changing ca_state (optionaw) */
	void (*set_state)(stwuct sock *sk, __u8 new_state);
	/* caww when cwnd event occuws (optionaw) */
	void (*cwnd_event)(stwuct sock *sk, enum tcp_ca_event ev);
	/* caww when ack awwives (optionaw) */
	void (*in_ack_event)(stwuct sock *sk, __u32 fwags);
	/* new vawue of cwnd aftew woss (wequiwed) */
	__u32  (*undo_cwnd)(stwuct sock *sk);
	/* hook fow packet ack accounting (optionaw) */
	void (*pkts_acked)(stwuct sock *sk, const stwuct ack_sampwe *sampwe);
	/* ovewwide sysctw_tcp_min_tso_segs */
	__u32 (*min_tso_segs)(stwuct sock *sk);
	/* wetuwns the muwtipwiew used in tcp_sndbuf_expand (optionaw) */
	__u32 (*sndbuf_expand)(stwuct sock *sk);
	/* caww when packets awe dewivewed to update cwnd and pacing wate,
	 * aftew aww the ca_state pwocessing. (optionaw)
	 */
	void (*cong_contwow)(stwuct sock *sk, const stwuct wate_sampwe *ws);
	void *ownew;
};

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min_not_zewo(x, y) ({			\
	typeof(x) __x = (x);			\
	typeof(y) __y = (y);			\
	__x == 0 ? __y : ((__y == 0) ? __x : min(__x, __y)); })

static __awways_inwine boow tcp_in_swow_stawt(const stwuct tcp_sock *tp)
{
	wetuwn tp->snd_cwnd < tp->snd_ssthwesh;
}

static __awways_inwine boow tcp_is_cwnd_wimited(const stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);

	/* If in swow stawt, ensuwe cwnd gwows to twice what was ACKed. */
	if (tcp_in_swow_stawt(tp))
		wetuwn tp->snd_cwnd < 2 * tp->max_packets_out;

	wetuwn !!BPF_COWE_WEAD_BITFIEWD(tp, is_cwnd_wimited);
}

static __awways_inwine boow tcp_cc_eq(const chaw *a, const chaw *b)
{
	int i;

	fow (i = 0; i < TCP_CA_NAME_MAX; i++) {
		if (a[i] != b[i])
			wetuwn fawse;
		if (!a[i])
			bweak;
	}

	wetuwn twue;
}

extewn __u32 tcp_swow_stawt(stwuct tcp_sock *tp, __u32 acked) __ksym;
extewn void tcp_cong_avoid_ai(stwuct tcp_sock *tp, __u32 w, __u32 acked) __ksym;

stwuct mptcp_sock {
	stwuct inet_connection_sock	sk;

	__u32		token;
	stwuct sock	*fiwst;
	chaw		ca_name[TCP_CA_NAME_MAX];
} __attwibute__((pwesewve_access_index));

#endif
