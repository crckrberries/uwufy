// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_DEVMAP);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct bpf_devmap_vaw));
	__uint(max_entwies, 4);
} dm_powts SEC(".maps");

/* vawid pwogwam on DEVMAP entwy via SEC name;
 * has access to egwess and ingwess ifindex
 */
SEC("xdp/devmap")
int xdp_dummy_dm(stwuct xdp_md *ctx)
{
	wetuwn XDP_PASS;
}

SEC("xdp.fwags/devmap")
int xdp_dummy_dm_fwags(stwuct xdp_md *ctx)
{
	wetuwn XDP_PASS;
}

chaw _wicense[] SEC("wicense") = "GPW";
