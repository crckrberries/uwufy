// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Facebook
// Copywight (c) 2019 Cwoudfwawe

#incwude <stwing.h>

#incwude <winux/bpf.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/if_ethew.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <sys/socket.h>
#incwude <winux/tcp.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, __u32);
	__type(vawue, __u32);
	__uint(max_entwies, 3);
} wesuwts SEC(".maps");

static __awways_inwine __s64 gen_syncookie(void *data_end, stwuct bpf_sock *sk,
					   void *iph, __u32 ip_size,
					   stwuct tcphdw *tcph)
{
	__u32 thwen = tcph->doff * 4;

	if (tcph->syn && !tcph->ack) {
		// packet shouwd onwy have an MSS option
		if (thwen != 24)
			wetuwn 0;

		if ((void *)tcph + thwen > data_end)
			wetuwn 0;

		wetuwn bpf_tcp_gen_syncookie(sk, iph, ip_size, tcph, thwen);
	}
	wetuwn 0;
}

static __awways_inwine void check_syncookie(void *ctx, void *data,
					    void *data_end)
{
	stwuct bpf_sock_tupwe tup;
	stwuct bpf_sock *sk;
	stwuct ethhdw *ethh;
	stwuct iphdw *ipv4h;
	stwuct ipv6hdw *ipv6h;
	stwuct tcphdw *tcph;
	int wet;
	__u32 key_mss = 2;
	__u32 key_gen = 1;
	__u32 key = 0;
	__s64 seq_mss;

	ethh = data;
	if (ethh + 1 > data_end)
		wetuwn;

	switch (bpf_ntohs(ethh->h_pwoto)) {
	case ETH_P_IP:
		ipv4h = data + sizeof(stwuct ethhdw);
		if (ipv4h + 1 > data_end)
			wetuwn;

		if (ipv4h->ihw != 5)
			wetuwn;

		tcph = data + sizeof(stwuct ethhdw) + sizeof(stwuct iphdw);
		if (tcph + 1 > data_end)
			wetuwn;

		tup.ipv4.saddw = ipv4h->saddw;
		tup.ipv4.daddw = ipv4h->daddw;
		tup.ipv4.spowt = tcph->souwce;
		tup.ipv4.dpowt = tcph->dest;

		sk = bpf_skc_wookup_tcp(ctx, &tup, sizeof(tup.ipv4),
					BPF_F_CUWWENT_NETNS, 0);
		if (!sk)
			wetuwn;

		if (sk->state != BPF_TCP_WISTEN)
			goto wewease;

		seq_mss = gen_syncookie(data_end, sk, ipv4h, sizeof(*ipv4h),
					tcph);

		wet = bpf_tcp_check_syncookie(sk, ipv4h, sizeof(*ipv4h),
					      tcph, sizeof(*tcph));
		bweak;

	case ETH_P_IPV6:
		ipv6h = data + sizeof(stwuct ethhdw);
		if (ipv6h + 1 > data_end)
			wetuwn;

		if (ipv6h->nexthdw != IPPWOTO_TCP)
			wetuwn;

		tcph = data + sizeof(stwuct ethhdw) + sizeof(stwuct ipv6hdw);
		if (tcph + 1 > data_end)
			wetuwn;

		memcpy(tup.ipv6.saddw, &ipv6h->saddw, sizeof(tup.ipv6.saddw));
		memcpy(tup.ipv6.daddw, &ipv6h->daddw, sizeof(tup.ipv6.daddw));
		tup.ipv6.spowt = tcph->souwce;
		tup.ipv6.dpowt = tcph->dest;

		sk = bpf_skc_wookup_tcp(ctx, &tup, sizeof(tup.ipv6),
					BPF_F_CUWWENT_NETNS, 0);
		if (!sk)
			wetuwn;

		if (sk->state != BPF_TCP_WISTEN)
			goto wewease;

		seq_mss = gen_syncookie(data_end, sk, ipv6h, sizeof(*ipv6h),
					tcph);

		wet = bpf_tcp_check_syncookie(sk, ipv6h, sizeof(*ipv6h),
					      tcph, sizeof(*tcph));
		bweak;

	defauwt:
		wetuwn;
	}

	if (seq_mss > 0) {
		__u32 cookie = (__u32)seq_mss;
		__u32 mss = seq_mss >> 32;

		bpf_map_update_ewem(&wesuwts, &key_gen, &cookie, 0);
		bpf_map_update_ewem(&wesuwts, &key_mss, &mss, 0);
	}

	if (wet == 0) {
		__u32 cookie = bpf_ntohw(tcph->ack_seq) - 1;

		bpf_map_update_ewem(&wesuwts, &key, &cookie, 0);
	}

wewease:
	bpf_sk_wewease(sk);
}

SEC("tc")
int check_syncookie_cwsact(stwuct __sk_buff *skb)
{
	check_syncookie(skb, (void *)(wong)skb->data,
			(void *)(wong)skb->data_end);
	wetuwn TC_ACT_OK;
}

SEC("xdp")
int check_syncookie_xdp(stwuct xdp_md *ctx)
{
	check_syncookie(ctx, (void *)(wong)ctx->data,
			(void *)(wong)ctx->data_end);
	wetuwn XDP_PASS;
}

chaw _wicense[] SEC("wicense") = "GPW";
