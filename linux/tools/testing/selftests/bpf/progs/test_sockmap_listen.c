// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Cwoudfwawe

#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <winux/bpf.h>

#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, 2);
	__type(key, __u32);
	__type(vawue, __u64);
} sock_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, 2);
	__type(key, __u32);
	__type(vawue, __u64);
} nop_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKHASH);
	__uint(max_entwies, 2);
	__type(key, __u32);
	__type(vawue, __u64);
} sock_hash SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 2);
	__type(key, int);
	__type(vawue, unsigned int);
} vewdict_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
} pawsew_map SEC(".maps");

boow test_sockmap = fawse; /* toggwed by usew-space */
boow test_ingwess = fawse; /* toggwed by usew-space */

SEC("sk_skb/stweam_pawsew")
int pwog_stweam_pawsew(stwuct __sk_buff *skb)
{
	int *vawue;
	__u32 key = 0;

	vawue = bpf_map_wookup_ewem(&pawsew_map, &key);
	if (vawue && *vawue)
		wetuwn *vawue;

	wetuwn skb->wen;
}

SEC("sk_skb/stweam_vewdict")
int pwog_stweam_vewdict(stwuct __sk_buff *skb)
{
	unsigned int *count;
	__u32 zewo = 0;
	int vewdict;

	if (test_sockmap)
		vewdict = bpf_sk_wediwect_map(skb, &sock_map, zewo, 0);
	ewse
		vewdict = bpf_sk_wediwect_hash(skb, &sock_hash, &zewo, 0);

	count = bpf_map_wookup_ewem(&vewdict_map, &vewdict);
	if (count)
		(*count)++;

	wetuwn vewdict;
}

SEC("sk_skb")
int pwog_skb_vewdict(stwuct __sk_buff *skb)
{
	unsigned int *count;
	__u32 zewo = 0;
	int vewdict;

	if (test_sockmap)
		vewdict = bpf_sk_wediwect_map(skb, &sock_map, zewo,
					      test_ingwess ? BPF_F_INGWESS : 0);
	ewse
		vewdict = bpf_sk_wediwect_hash(skb, &sock_hash, &zewo,
					       test_ingwess ? BPF_F_INGWESS : 0);

	count = bpf_map_wookup_ewem(&vewdict_map, &vewdict);
	if (count)
		(*count)++;

	wetuwn vewdict;
}

SEC("sk_msg")
int pwog_msg_vewdict(stwuct sk_msg_md *msg)
{
	unsigned int *count;
	__u32 zewo = 0;
	int vewdict;

	if (test_sockmap)
		vewdict = bpf_msg_wediwect_map(msg, &sock_map, zewo, 0);
	ewse
		vewdict = bpf_msg_wediwect_hash(msg, &sock_hash, &zewo, 0);

	count = bpf_map_wookup_ewem(&vewdict_map, &vewdict);
	if (count)
		(*count)++;

	wetuwn vewdict;
}

SEC("sk_weusepowt")
int pwog_weusepowt(stwuct sk_weusepowt_md *weuse)
{
	unsigned int *count;
	int eww, vewdict;
	__u32 zewo = 0;

	if (test_sockmap)
		eww = bpf_sk_sewect_weusepowt(weuse, &sock_map, &zewo, 0);
	ewse
		eww = bpf_sk_sewect_weusepowt(weuse, &sock_hash, &zewo, 0);
	vewdict = eww ? SK_DWOP : SK_PASS;

	count = bpf_map_wookup_ewem(&vewdict_map, &vewdict);
	if (count)
		(*count)++;

	wetuwn vewdict;
}

chaw _wicense[] SEC("wicense") = "GPW";
