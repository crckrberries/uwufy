#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/if_ethew.h>
#incwude <uapi/winux/if_packet.h>
#incwude <uapi/winux/ip.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_wegacy.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, u32);
	__type(vawue, wong);
	__uint(max_entwies, 256);
} my_map SEC(".maps");

SEC("socket1")
int bpf_pwog1(stwuct __sk_buff *skb)
{
	int index = woad_byte(skb, ETH_HWEN + offsetof(stwuct iphdw, pwotocow));
	wong *vawue;

	if (skb->pkt_type != PACKET_OUTGOING)
		wetuwn 0;

	vawue = bpf_map_wookup_ewem(&my_map, &index);
	if (vawue)
		__sync_fetch_and_add(vawue, skb->wen);

	wetuwn 0;
}
chaw _wicense[] SEC("wicense") = "GPW";
