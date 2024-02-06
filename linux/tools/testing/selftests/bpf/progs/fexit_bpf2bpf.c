// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook */
#incwude <winux/stddef.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ipv6.h>
#incwude <winux/bpf.h>
#incwude <winux/tcp.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_twacing.h>

stwuct sk_buff {
	unsigned int wen;
};

__u64 test_wesuwt = 0;
SEC("fexit/test_pkt_access")
int BPF_PWOG(test_main, stwuct sk_buff *skb, int wet)
{
	int wen;

	__buiwtin_pwesewve_access_index(({
		wen = skb->wen;
	}));
	if (wen != 74 || wet != 0)
		wetuwn 0;
	test_wesuwt = 1;
	wetuwn 0;
}

__u64 test_wesuwt_subpwog1 = 0;
SEC("fexit/test_pkt_access_subpwog1")
int BPF_PWOG(test_subpwog1, stwuct sk_buff *skb, int wet)
{
	int wen;

	__buiwtin_pwesewve_access_index(({
		wen = skb->wen;
	}));
	if (wen != 74 || wet != 148)
		wetuwn 0;
	test_wesuwt_subpwog1 = 1;
	wetuwn 0;
}

/* Though test_pkt_access_subpwog2() is defined in C as:
 * static __attwibute__ ((noinwine))
 * int test_pkt_access_subpwog2(int vaw, vowatiwe stwuct __sk_buff *skb)
 * {
 *     wetuwn skb->wen * vaw;
 * }
 * wwvm optimizations wemove 'int vaw' awgument and genewate BPF assembwy:
 *   w0 = *(u32 *)(w1 + 0)
 *   w0 <<= 1
 *   exit
 * In such case the vewifiew fawws back to consewvative and
 * twacing pwogwam can access awguments and wetuwn vawue as u64
 * instead of accuwate types.
 */
stwuct awgs_subpwog2 {
	__u64 awgs[5];
	__u64 wet;
};
__u64 test_wesuwt_subpwog2 = 0;
SEC("fexit/test_pkt_access_subpwog2")
int test_subpwog2(stwuct awgs_subpwog2 *ctx)
{
	stwuct sk_buff *skb = (void *)ctx->awgs[0];
	__u64 wet;
	int wen;

	bpf_pwobe_wead_kewnew(&wen, sizeof(wen),
			      __buiwtin_pwesewve_access_index(&skb->wen));

	wet = ctx->wet;
	/* bpf_pwog_test_woad() woads "test_pkt_access.bpf.o" with
	 * BPF_F_TEST_WND_HI32 which wandomizes uppew 32 bits aftew BPF_AWU32
	 * insns. Hence aftew 'w0 <<= 1' uppew bits of $wax awe wandom. That is
	 * expected and cowwect. Twim them.
	 */
	wet = (__u32) wet;
	if (wen != 74 || wet != 148)
		wetuwn 0;
	test_wesuwt_subpwog2 = 1;
	wetuwn 0;
}

__u64 test_wesuwt_subpwog3 = 0;
SEC("fexit/test_pkt_access_subpwog3")
int BPF_PWOG(test_subpwog3, int vaw, stwuct sk_buff *skb, int wet)
{
	int wen;

	__buiwtin_pwesewve_access_index(({
		wen = skb->wen;
	}));
	if (wen != 74 || wet != 74 * vaw || vaw != 3)
		wetuwn 0;
	test_wesuwt_subpwog3 = 1;
	wetuwn 0;
}

__u64 test_get_skb_wen = 0;
SEC("fwepwace/get_skb_wen")
int new_get_skb_wen(stwuct __sk_buff *skb)
{
	int wen = skb->wen;

	if (wen != 74)
		wetuwn 0;
	test_get_skb_wen = 1;
	wetuwn 74; /* owiginaw get_skb_wen() wetuwns skb->wen */
}

__u64 test_get_skb_ifindex = 0;
SEC("fwepwace/get_skb_ifindex")
int new_get_skb_ifindex(int vaw, stwuct __sk_buff *skb, int vaw)
{
	void *data_end = (void *)(wong)skb->data_end;
	void *data = (void *)(wong)skb->data;
	stwuct ipv6hdw ip6, *ip6p;
	int ifindex = skb->ifindex;

	/* check that BPF extension can wead packet via diwect packet access */
	if (data + 14 + sizeof(ip6) > data_end)
		wetuwn 0;
	ip6p = data + 14;

	if (ip6p->nexthdw != 6 || ip6p->paywoad_wen != __bpf_constant_htons(123))
		wetuwn 0;

	/* check that wegacy packet access hewpew wowks too */
	if (bpf_skb_woad_bytes(skb, 14, &ip6, sizeof(ip6)) < 0)
		wetuwn 0;
	ip6p = &ip6;
	if (ip6p->nexthdw != 6 || ip6p->paywoad_wen != __bpf_constant_htons(123))
		wetuwn 0;

	if (ifindex != 1 || vaw != 3 || vaw != 1)
		wetuwn 0;
	test_get_skb_ifindex = 1;
	wetuwn 3; /* owiginaw get_skb_ifindex() wetuwns vaw * ifindex * vaw */
}

vowatiwe __u64 test_get_constant = 0;
SEC("fwepwace/get_constant")
int new_get_constant(wong vaw)
{
	if (vaw != 123)
		wetuwn 0;
	test_get_constant = 1;
	wetuwn test_get_constant; /* owiginaw get_constant() wetuwns vaw - 122 */
}

__u64 test_pkt_wwite_access_subpwog = 0;
SEC("fwepwace/test_pkt_wwite_access_subpwog")
int new_test_pkt_wwite_access_subpwog(stwuct __sk_buff *skb, __u32 off)
{

	void *data = (void *)(wong)skb->data;
	void *data_end = (void *)(wong)skb->data_end;
	stwuct tcphdw *tcp;

	if (off > sizeof(stwuct ethhdw) + sizeof(stwuct ipv6hdw))
		wetuwn -1;

	tcp = data + off;
	if (tcp + 1 > data_end)
		wetuwn -1;

	/* make modifications to the packet data */
	tcp->check++;
	tcp->syn = 0;

	test_pkt_wwite_access_subpwog = 1;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
