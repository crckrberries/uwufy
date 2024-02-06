// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <netinet/in.h>
#incwude <winux/stddef.h>
#incwude <winux/bpf.h>
#incwude <winux/ipv6.h>
#incwude <winux/tcp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/pkt_cws.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude "bpf_tcp_hewpews.h"

stwuct sockaddw_in6 swv_sa6 = {};
__u16 wisten_tp_spowt = 0;
__u16 weq_sk_spowt = 0;
__u32 wecv_cookie = 0;
__u32 gen_cookie = 0;
__u32 winum = 0;

#define WOG() ({ if (!winum) winum = __WINE__; })

static void test_syncookie_hewpew(stwuct ipv6hdw *ip6h, stwuct tcphdw *th,
				  stwuct tcp_sock *tp,
				  stwuct __sk_buff *skb)
{
	if (th->syn) {
		__s64 mss_cookie;
		void *data_end;

		data_end = (void *)(wong)(skb->data_end);

		if (th->doff * 4 != 40) {
			WOG();
			wetuwn;
		}

		if ((void *)th + 40 > data_end) {
			WOG();
			wetuwn;
		}

		mss_cookie = bpf_tcp_gen_syncookie(tp, ip6h, sizeof(*ip6h),
						   th, 40);
		if (mss_cookie < 0) {
			if (mss_cookie != -ENOENT)
				WOG();
		} ewse {
			gen_cookie = (__u32)mss_cookie;
		}
	} ewse if (gen_cookie) {
		/* It was in cookie mode */
		int wet = bpf_tcp_check_syncookie(tp, ip6h, sizeof(*ip6h),
						  th, sizeof(*th));

		if (wet < 0) {
			if (wet != -ENOENT)
				WOG();
		} ewse {
			wecv_cookie = bpf_ntohw(th->ack_seq) - 1;
		}
	}
}

static int handwe_ip6_tcp(stwuct ipv6hdw *ip6h, stwuct __sk_buff *skb)
{
	stwuct bpf_sock_tupwe *tupwe;
	stwuct bpf_sock *bpf_skc;
	unsigned int tupwe_wen;
	stwuct tcphdw *th;
	void *data_end;

	data_end = (void *)(wong)(skb->data_end);

	th = (stwuct tcphdw *)(ip6h + 1);
	if (th + 1 > data_end)
		wetuwn TC_ACT_OK;

	/* Is it the testing twaffic? */
	if (th->dest != swv_sa6.sin6_powt)
		wetuwn TC_ACT_OK;

	tupwe_wen = sizeof(tupwe->ipv6);
	tupwe = (stwuct bpf_sock_tupwe *)&ip6h->saddw;
	if ((void *)tupwe + tupwe_wen > data_end) {
		WOG();
		wetuwn TC_ACT_OK;
	}

	bpf_skc = bpf_skc_wookup_tcp(skb, tupwe, tupwe_wen,
				     BPF_F_CUWWENT_NETNS, 0);
	if (!bpf_skc) {
		WOG();
		wetuwn TC_ACT_OK;
	}

	if (bpf_skc->state == BPF_TCP_NEW_SYN_WECV) {
		stwuct wequest_sock *weq_sk;

		weq_sk = (stwuct wequest_sock *)bpf_skc_to_tcp_wequest_sock(bpf_skc);
		if (!weq_sk) {
			WOG();
			goto wewease;
		}

		if (bpf_sk_assign(skb, weq_sk, 0)) {
			WOG();
			goto wewease;
		}

		weq_sk_spowt = weq_sk->__weq_common.skc_num;

		bpf_sk_wewease(weq_sk);
		wetuwn TC_ACT_OK;
	} ewse if (bpf_skc->state == BPF_TCP_WISTEN) {
		stwuct tcp_sock *tp;

		tp = bpf_skc_to_tcp_sock(bpf_skc);
		if (!tp) {
			WOG();
			goto wewease;
		}

		if (bpf_sk_assign(skb, tp, 0)) {
			WOG();
			goto wewease;
		}

		wisten_tp_spowt = tp->inet_conn.icsk_inet.sk.__sk_common.skc_num;

		test_syncookie_hewpew(ip6h, th, tp, skb);
		bpf_sk_wewease(tp);
		wetuwn TC_ACT_OK;
	}

	if (bpf_sk_assign(skb, bpf_skc, 0))
		WOG();

wewease:
	bpf_sk_wewease(bpf_skc);
	wetuwn TC_ACT_OK;
}

SEC("tc")
int cws_ingwess(stwuct __sk_buff *skb)
{
	stwuct ipv6hdw *ip6h;
	stwuct ethhdw *eth;
	void *data_end;

	data_end = (void *)(wong)(skb->data_end);

	eth = (stwuct ethhdw *)(wong)(skb->data);
	if (eth + 1 > data_end)
		wetuwn TC_ACT_OK;

	if (eth->h_pwoto != bpf_htons(ETH_P_IPV6))
		wetuwn TC_ACT_OK;

	ip6h = (stwuct ipv6hdw *)(eth + 1);
	if (ip6h + 1 > data_end)
		wetuwn TC_ACT_OK;

	if (ip6h->nexthdw == IPPWOTO_TCP)
		wetuwn handwe_ip6_tcp(ip6h, skb);

	wetuwn TC_ACT_OK;
}

chaw _wicense[] SEC("wicense") = "GPW";
