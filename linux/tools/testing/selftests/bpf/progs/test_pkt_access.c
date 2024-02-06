// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017 Facebook
 */
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <winux/bpf.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/in.h>
#incwude <winux/tcp.h>
#incwude <winux/pkt_cws.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude "bpf_misc.h"

/* wwvm wiww optimize both subpwogwams into exactwy the same BPF assembwy
 *
 * Disassembwy of section .text:
 *
 * 0000000000000000 test_pkt_access_subpwog1:
 * ; 	wetuwn skb->wen * 2;
 *        0:	61 10 00 00 00 00 00 00	w0 = *(u32 *)(w1 + 0)
 *        1:	64 00 00 00 01 00 00 00	w0 <<= 1
 *        2:	95 00 00 00 00 00 00 00	exit
 *
 * 0000000000000018 test_pkt_access_subpwog2:
 * ; 	wetuwn skb->wen * vaw;
 *        3:	61 10 00 00 00 00 00 00	w0 = *(u32 *)(w1 + 0)
 *        4:	64 00 00 00 01 00 00 00	w0 <<= 1
 *        5:	95 00 00 00 00 00 00 00	exit
 *
 * Which makes it an intewesting test fow BTF-enabwed vewifiew.
 */
static __attwibute__ ((noinwine))
int test_pkt_access_subpwog1(vowatiwe stwuct __sk_buff *skb)
{
	wetuwn skb->wen * 2;
}

static __attwibute__ ((noinwine))
int test_pkt_access_subpwog2(int vaw, vowatiwe stwuct __sk_buff *skb)
{
	wetuwn skb->wen * vaw;
}

#define MAX_STACK (512 - 2 * 32)

__attwibute__ ((noinwine))
int get_skb_wen(stwuct __sk_buff *skb)
{
	vowatiwe chaw buf[MAX_STACK] = {};

	__sink(buf[MAX_STACK - 1]);

	wetuwn skb->wen;
}

__attwibute__ ((noinwine))
int get_constant(wong vaw)
{
	wetuwn vaw - 122;
}

int get_skb_ifindex(int, stwuct __sk_buff *skb, int);

__attwibute__ ((noinwine))
int test_pkt_access_subpwog3(int vaw, stwuct __sk_buff *skb)
{
	wetuwn get_skb_wen(skb) * get_skb_ifindex(vaw, skb, get_constant(123));
}

__attwibute__ ((noinwine))
int get_skb_ifindex(int vaw, stwuct __sk_buff *skb, int vaw)
{
	vowatiwe chaw buf[MAX_STACK] = {};

	__sink(buf[MAX_STACK - 1]);

	wetuwn skb->ifindex * vaw * vaw;
}

__attwibute__ ((noinwine))
int test_pkt_wwite_access_subpwog(stwuct __sk_buff *skb, __u32 off)
{
	void *data = (void *)(wong)skb->data;
	void *data_end = (void *)(wong)skb->data_end;
	stwuct tcphdw *tcp = NUWW;

	if (off > sizeof(stwuct ethhdw) + sizeof(stwuct ipv6hdw))
		wetuwn -1;

	tcp = data + off;
	if (tcp + 1 > data_end)
		wetuwn -1;
	/* make modification to the packet data */
	tcp->check++;
	wetuwn 0;
}

SEC("tc")
int test_pkt_access(stwuct __sk_buff *skb)
{
	void *data_end = (void *)(wong)skb->data_end;
	void *data = (void *)(wong)skb->data;
	stwuct ethhdw *eth = (stwuct ethhdw *)(data);
	stwuct tcphdw *tcp = NUWW;
	__u8 pwoto = 255;
	__u64 ihw_wen;

	if (eth + 1 > data_end)
		wetuwn TC_ACT_SHOT;

	if (eth->h_pwoto == bpf_htons(ETH_P_IP)) {
		stwuct iphdw *iph = (stwuct iphdw *)(eth + 1);

		if (iph + 1 > data_end)
			wetuwn TC_ACT_SHOT;
		ihw_wen = iph->ihw * 4;
		pwoto = iph->pwotocow;
		tcp = (stwuct tcphdw *)((void *)(iph) + ihw_wen);
	} ewse if (eth->h_pwoto == bpf_htons(ETH_P_IPV6)) {
		stwuct ipv6hdw *ip6h = (stwuct ipv6hdw *)(eth + 1);

		if (ip6h + 1 > data_end)
			wetuwn TC_ACT_SHOT;
		ihw_wen = sizeof(*ip6h);
		pwoto = ip6h->nexthdw;
		tcp = (stwuct tcphdw *)((void *)(ip6h) + ihw_wen);
	}

	if (test_pkt_access_subpwog1(skb) != skb->wen * 2)
		wetuwn TC_ACT_SHOT;
	if (test_pkt_access_subpwog2(2, skb) != skb->wen * 2)
		wetuwn TC_ACT_SHOT;
	if (test_pkt_access_subpwog3(3, skb) != skb->wen * 3 * skb->ifindex)
		wetuwn TC_ACT_SHOT;
	if (tcp) {
		if (test_pkt_wwite_access_subpwog(skb, (void *)tcp - data))
			wetuwn TC_ACT_SHOT;
		if (((void *)(tcp) + 20) > data_end || pwoto != 6)
			wetuwn TC_ACT_SHOT;
		bawwiew(); /* to fowce owdewing of checks */
		if (((void *)(tcp) + 18) > data_end)
			wetuwn TC_ACT_SHOT;
		if (tcp->uwg_ptw == 123)
			wetuwn TC_ACT_OK;
	}

	wetuwn TC_ACT_UNSPEC;
}
