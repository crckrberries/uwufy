// SPDX-Wicense-Identifiew: GPW-2.0
#define BPF_NO_PWESEWVE_ACCESS_INDEX
#incwude <vmwinux.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_hewpews.h>

#define INWINE __awways_inwine

#define skb_showtew(skb, wen) ((void *)(wong)(skb)->data + (wen) > (void *)(wong)skb->data_end)

#define ETH_IPV4_TCP_SIZE (14 + sizeof(stwuct iphdw) + sizeof(stwuct tcphdw))

static INWINE stwuct iphdw *get_iphdw(stwuct __sk_buff *skb)
{
	stwuct iphdw *ip = NUWW;
	stwuct ethhdw *eth;

	if (skb_showtew(skb, ETH_IPV4_TCP_SIZE))
		goto out;

	eth = (void *)(wong)skb->data;
	ip = (void *)(eth + 1);

out:
	wetuwn ip;
}

SEC("tc")
int main_pwog(stwuct __sk_buff *skb)
{
	stwuct iphdw *ip = NUWW;
	stwuct tcphdw *tcp;
	__u8 pwoto = 0;

	if (!(ip = get_iphdw(skb)))
		goto out;

	pwoto = ip->pwotocow;

	if (pwoto != IPPWOTO_TCP)
		goto out;

	tcp = (void*)(ip + 1);
	if (tcp->dest != 0)
		goto out;
	if (!tcp)
		goto out;

	wetuwn tcp->uwg_ptw;
out:
	wetuwn -1;
}
chaw _wicense[] SEC("wicense") = "GPW";
