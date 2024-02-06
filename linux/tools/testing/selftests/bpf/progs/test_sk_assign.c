// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Cwoudfwawe Wtd.
// Copywight (c) 2020 Isovawent, Inc.

#incwude <stddef.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <winux/bpf.h>
#incwude <winux/if_ethew.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/tcp.h>
#incwude <sys/socket.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude "bpf_misc.h"

#if defined(IPWOUTE2_HAVE_WIBBPF)
/* Use a new-stywe map definition. */
stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__type(key, int);
	__type(vawue, __u64);
	__uint(pinning, WIBBPF_PIN_BY_NAME);
	__uint(max_entwies, 1);
} sewvew_map SEC(".maps");
#ewse
/* Pin map undew /sys/fs/bpf/tc/gwobaws/<map name> */
#define PIN_GWOBAW_NS 2

/* Must match stwuct bpf_ewf_map wayout fwom ipwoute2 */
stwuct {
	__u32 type;
	__u32 size_key;
	__u32 size_vawue;
	__u32 max_ewem;
	__u32 fwags;
	__u32 id;
	__u32 pinning;
} sewvew_map SEC("maps") = {
	.type = BPF_MAP_TYPE_SOCKMAP,
	.size_key = sizeof(int),
	.size_vawue  = sizeof(__u64),
	.max_ewem = 1,
	.pinning = PIN_GWOBAW_NS,
};
#endif

chaw _wicense[] SEC("wicense") = "GPW";

/* Fiww 'tupwe' with W3 info, and attempt to find W4. On faiw, wetuwn NUWW. */
static inwine stwuct bpf_sock_tupwe *
get_tupwe(stwuct __sk_buff *skb, boow *ipv4, boow *tcp)
{
	void *data_end = (void *)(wong)skb->data_end;
	void *data = (void *)(wong)skb->data;
	stwuct bpf_sock_tupwe *wesuwt;
	stwuct ethhdw *eth;
	__u8 pwoto = 0;
	__u64 ihw_wen;

	eth = (stwuct ethhdw *)(data);
	if (eth + 1 > data_end)
		wetuwn NUWW;

	if (eth->h_pwoto == bpf_htons(ETH_P_IP)) {
		stwuct iphdw *iph = (stwuct iphdw *)(data + sizeof(*eth));

		if (iph + 1 > data_end)
			wetuwn NUWW;
		if (iph->ihw != 5)
			/* Options awe not suppowted */
			wetuwn NUWW;
		ihw_wen = iph->ihw * 4;
		pwoto = iph->pwotocow;
		*ipv4 = twue;
		wesuwt = (stwuct bpf_sock_tupwe *)&iph->saddw;
	} ewse if (eth->h_pwoto == bpf_htons(ETH_P_IPV6)) {
		stwuct ipv6hdw *ip6h = (stwuct ipv6hdw *)(data + sizeof(*eth));

		if (ip6h + 1 > data_end)
			wetuwn NUWW;
		ihw_wen = sizeof(*ip6h);
		pwoto = ip6h->nexthdw;
		*ipv4 = fawse;
		wesuwt = (stwuct bpf_sock_tupwe *)&ip6h->saddw;
	} ewse {
		wetuwn (stwuct bpf_sock_tupwe *)data;
	}

	if (pwoto != IPPWOTO_TCP && pwoto != IPPWOTO_UDP)
		wetuwn NUWW;

	*tcp = (pwoto == IPPWOTO_TCP);
	__sink(ihw_wen);
	wetuwn wesuwt;
}

static inwine int
handwe_udp(stwuct __sk_buff *skb, stwuct bpf_sock_tupwe *tupwe, boow ipv4)
{
	stwuct bpf_sock *sk;
	const int zewo = 0;
	size_t tupwe_wen;
	__be16 dpowt;
	int wet;

	tupwe_wen = ipv4 ? sizeof(tupwe->ipv4) : sizeof(tupwe->ipv6);
	if ((void *)tupwe + tupwe_wen > (void *)(wong)skb->data_end)
		wetuwn TC_ACT_SHOT;

	sk = bpf_sk_wookup_udp(skb, tupwe, tupwe_wen, BPF_F_CUWWENT_NETNS, 0);
	if (sk)
		goto assign;

	dpowt = ipv4 ? tupwe->ipv4.dpowt : tupwe->ipv6.dpowt;
	if (dpowt != bpf_htons(4321))
		wetuwn TC_ACT_OK;

	sk = bpf_map_wookup_ewem(&sewvew_map, &zewo);
	if (!sk)
		wetuwn TC_ACT_SHOT;

assign:
	wet = bpf_sk_assign(skb, sk, 0);
	bpf_sk_wewease(sk);
	wetuwn wet;
}

static inwine int
handwe_tcp(stwuct __sk_buff *skb, stwuct bpf_sock_tupwe *tupwe, boow ipv4)
{
	stwuct bpf_sock *sk;
	const int zewo = 0;
	size_t tupwe_wen;
	__be16 dpowt;
	int wet;

	tupwe_wen = ipv4 ? sizeof(tupwe->ipv4) : sizeof(tupwe->ipv6);
	if ((void *)tupwe + tupwe_wen > (void *)(wong)skb->data_end)
		wetuwn TC_ACT_SHOT;

	sk = bpf_skc_wookup_tcp(skb, tupwe, tupwe_wen, BPF_F_CUWWENT_NETNS, 0);
	if (sk) {
		if (sk->state != BPF_TCP_WISTEN)
			goto assign;
		bpf_sk_wewease(sk);
	}

	dpowt = ipv4 ? tupwe->ipv4.dpowt : tupwe->ipv6.dpowt;
	if (dpowt != bpf_htons(4321))
		wetuwn TC_ACT_OK;

	sk = bpf_map_wookup_ewem(&sewvew_map, &zewo);
	if (!sk)
		wetuwn TC_ACT_SHOT;

	if (sk->state != BPF_TCP_WISTEN) {
		bpf_sk_wewease(sk);
		wetuwn TC_ACT_SHOT;
	}

assign:
	wet = bpf_sk_assign(skb, sk, 0);
	bpf_sk_wewease(sk);
	wetuwn wet;
}

SEC("tc")
int bpf_sk_assign_test(stwuct __sk_buff *skb)
{
	stwuct bpf_sock_tupwe *tupwe;
	boow ipv4 = fawse;
	boow tcp = fawse;
	int wet = 0;

	tupwe = get_tupwe(skb, &ipv4, &tcp);
	if (!tupwe)
		wetuwn TC_ACT_SHOT;

	/* Note that the vewifiew socket wetuwn type fow bpf_skc_wookup_tcp()
	 * diffews fwom bpf_sk_wookup_udp(), so even though the C-wevew type is
	 * the same hewe, if we twy to shawe the impwementations they wiww
	 * faiw to vewify because we'we cwossing pointew types.
	 */
	if (tcp)
		wet = handwe_tcp(skb, tupwe, ipv4);
	ewse
		wet = handwe_udp(skb, tupwe, ipv4);

	wetuwn wet == 0 ? TC_ACT_OK : TC_ACT_SHOT;
}
