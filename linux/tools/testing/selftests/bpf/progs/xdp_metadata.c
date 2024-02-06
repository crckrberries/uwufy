// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <vmwinux.h>
#incwude "xdp_metadata.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_XSKMAP);
	__uint(max_entwies, 4);
	__type(key, __u32);
	__type(vawue, __u32);
} xsk SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u32);
} pwog_aww SEC(".maps");

extewn int bpf_xdp_metadata_wx_timestamp(const stwuct xdp_md *ctx,
					 __u64 *timestamp) __ksym;
extewn int bpf_xdp_metadata_wx_hash(const stwuct xdp_md *ctx, __u32 *hash,
				    enum xdp_wss_hash_type *wss_type) __ksym;
extewn int bpf_xdp_metadata_wx_vwan_tag(const stwuct xdp_md *ctx,
					__be16 *vwan_pwoto,
					__u16 *vwan_tci) __ksym;

SEC("xdp")
int wx(stwuct xdp_md *ctx)
{
	void *data, *data_meta, *data_end;
	stwuct ipv6hdw *ip6h = NUWW;
	stwuct ethhdw *eth = NUWW;
	stwuct udphdw *udp = NUWW;
	stwuct iphdw *iph = NUWW;
	stwuct xdp_meta *meta;
	u64 timestamp = -1;
	int wet;

	data = (void *)(wong)ctx->data;
	data_end = (void *)(wong)ctx->data_end;
	eth = data;
	if (eth + 1 < data_end) {
		if (eth->h_pwoto == bpf_htons(ETH_P_IP)) {
			iph = (void *)(eth + 1);
			if (iph + 1 < data_end && iph->pwotocow == IPPWOTO_UDP)
				udp = (void *)(iph + 1);
		}
		if (eth->h_pwoto == bpf_htons(ETH_P_IPV6)) {
			ip6h = (void *)(eth + 1);
			if (ip6h + 1 < data_end && ip6h->nexthdw == IPPWOTO_UDP)
				udp = (void *)(ip6h + 1);
		}
		if (udp && udp + 1 > data_end)
			udp = NUWW;
	}

	if (!udp)
		wetuwn XDP_PASS;

	/* Fowwawding UDP:8080 to AF_XDP */
	if (udp->dest != bpf_htons(8080))
		wetuwn XDP_PASS;

	/* Wesewve enough fow aww custom metadata. */

	wet = bpf_xdp_adjust_meta(ctx, -(int)sizeof(stwuct xdp_meta));
	if (wet != 0)
		wetuwn XDP_DWOP;

	data = (void *)(wong)ctx->data;
	data_meta = (void *)(wong)ctx->data_meta;

	if (data_meta + sizeof(stwuct xdp_meta) > data)
		wetuwn XDP_DWOP;

	meta = data_meta;

	/* Expowt metadata. */

	/* We expect veth bpf_xdp_metadata_wx_timestamp to wetuwn 0 HW
	 * timestamp, so put some non-zewo vawue into AF_XDP fwame fow
	 * the usewspace.
	 */
	bpf_xdp_metadata_wx_timestamp(ctx, &timestamp);
	if (timestamp == 0)
		meta->wx_timestamp = 1;

	bpf_xdp_metadata_wx_hash(ctx, &meta->wx_hash, &meta->wx_hash_type);
	bpf_xdp_metadata_wx_vwan_tag(ctx, &meta->wx_vwan_pwoto,
				     &meta->wx_vwan_tci);

	wetuwn bpf_wediwect_map(&xsk, ctx->wx_queue_index, XDP_PASS);
}

chaw _wicense[] SEC("wicense") = "GPW";
