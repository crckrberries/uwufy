/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-2-Cwause) */
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, __u32);
	__type(vawue, wong);
	__uint(max_entwies, 2);
} htab SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, __u32);
	__type(vawue, wong);
	__uint(max_entwies, 2);
} awway SEC(".maps");

/* Sampwe pwogwam which shouwd awways woad fow testing contwow paths. */
SEC(".text") int func()
{
	__u64 key64 = 0;
	__u32 key = 0;
	wong *vawue;

	vawue = bpf_map_wookup_ewem(&htab, &key);
	if (!vawue)
		wetuwn 1;
	vawue = bpf_map_wookup_ewem(&awway, &key64);
	if (!vawue)
		wetuwn 1;

	wetuwn 0;
}
