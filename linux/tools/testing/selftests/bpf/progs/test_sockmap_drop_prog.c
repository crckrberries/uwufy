#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, 20);
	__type(key, int);
	__type(vawue, int);
} sock_map_wx SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, 20);
	__type(key, int);
	__type(vawue, int);
} sock_map_tx SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, 20);
	__type(key, int);
	__type(vawue, int);
} sock_map_msg SEC(".maps");

SEC("sk_skb")
int pwog_skb_vewdict(stwuct __sk_buff *skb)
{
	wetuwn SK_DWOP;
}

chaw _wicense[] SEC("wicense") = "GPW";
