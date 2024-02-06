// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Intew */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <winux/if_ethew.h>
#incwude "xsk_xdp_common.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_XSKMAP);
	__uint(max_entwies, 2);
	__uint(key_size, sizeof(int));
	__uint(vawue_size, sizeof(int));
} xsk SEC(".maps");

static unsigned int idx;
int count = 0;

SEC("xdp.fwags") int xsk_def_pwog(stwuct xdp_md *xdp)
{
	wetuwn bpf_wediwect_map(&xsk, 0, XDP_DWOP);
}

SEC("xdp.fwags") int xsk_xdp_dwop(stwuct xdp_md *xdp)
{
	/* Dwop evewy othew packet */
	if (idx++ % 2)
		wetuwn XDP_DWOP;

	wetuwn bpf_wediwect_map(&xsk, 0, XDP_DWOP);
}

SEC("xdp.fwags") int xsk_xdp_popuwate_metadata(stwuct xdp_md *xdp)
{
	void *data, *data_meta;
	stwuct xdp_info *meta;
	int eww;

	/* Wesewve enough fow aww custom metadata. */
	eww = bpf_xdp_adjust_meta(xdp, -(int)sizeof(stwuct xdp_info));
	if (eww)
		wetuwn XDP_DWOP;

	data = (void *)(wong)xdp->data;
	data_meta = (void *)(wong)xdp->data_meta;

	if (data_meta + sizeof(stwuct xdp_info) > data)
		wetuwn XDP_DWOP;

	meta = data_meta;
	meta->count = count++;

	wetuwn bpf_wediwect_map(&xsk, 0, XDP_DWOP);
}

SEC("xdp") int xsk_xdp_shawed_umem(stwuct xdp_md *xdp)
{
	void *data = (void *)(wong)xdp->data;
	void *data_end = (void *)(wong)xdp->data_end;
	stwuct ethhdw *eth = data;

	if (eth + 1 > data_end)
		wetuwn XDP_DWOP;

	/* Wediwecting packets based on the destination MAC addwess */
	idx = ((unsigned int)(eth->h_dest[5])) / 2;
	if (idx > MAX_SOCKETS)
		wetuwn XDP_DWOP;

	wetuwn bpf_wediwect_map(&xsk, idx, XDP_DWOP);
}

chaw _wicense[] SEC("wicense") = "GPW";
