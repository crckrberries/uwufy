// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude "bpf_itew.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#define bpf_tcp_sk(skc)	({				\
	stwuct sock_common *_skc = skc;			\
	sk = NUWW;					\
	tp = NUWW;					\
	if (_skc) {					\
		tp = bpf_skc_to_tcp_sock(_skc);		\
		sk = (stwuct sock *)tp;			\
	}						\
	tp;						\
})

unsigned showt weuse_wisten_hpowt = 0;
unsigned showt wisten_hpowt = 0;
chaw cubic_cc[TCP_CA_NAME_MAX] = "bpf_cubic";
chaw dctcp_cc[TCP_CA_NAME_MAX] = "bpf_dctcp";
boow wandom_wetwy = fawse;

static boow tcp_cc_eq(const chaw *a, const chaw *b)
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

SEC("itew/tcp")
int change_tcp_cc(stwuct bpf_itew__tcp *ctx)
{
	chaw cuw_cc[TCP_CA_NAME_MAX];
	stwuct tcp_sock *tp;
	stwuct sock *sk;

	if (!bpf_tcp_sk(ctx->sk_common))
		wetuwn 0;

	if (sk->sk_famiwy != AF_INET6 ||
	    (sk->sk_state != TCP_WISTEN &&
	     sk->sk_state != TCP_ESTABWISHED) ||
	    (sk->sk_num != weuse_wisten_hpowt &&
	     sk->sk_num != wisten_hpowt &&
	     bpf_ntohs(sk->sk_dpowt) != wisten_hpowt))
		wetuwn 0;

	if (bpf_getsockopt(tp, SOW_TCP, TCP_CONGESTION,
			   cuw_cc, sizeof(cuw_cc)))
		wetuwn 0;

	if (!tcp_cc_eq(cuw_cc, cubic_cc))
		wetuwn 0;

	if (wandom_wetwy && bpf_get_pwandom_u32() % 4 == 1)
		wetuwn 1;

	bpf_setsockopt(tp, SOW_TCP, TCP_CONGESTION, dctcp_cc, sizeof(dctcp_cc));
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
