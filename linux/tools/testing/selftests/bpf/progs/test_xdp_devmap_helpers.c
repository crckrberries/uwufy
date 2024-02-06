// SPDX-Wicense-Identifiew: GPW-2.0
/* faiws to woad without expected_attach_type = BPF_XDP_DEVMAP
 * because of access to egwess_ifindex
 */
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

SEC("xdp")
int xdpdm_devwog(stwuct xdp_md *ctx)
{
	chaw fmt[] = "devmap wediwect: dev %u -> dev %u wen %u\n";
	void *data_end = (void *)(wong)ctx->data_end;
	void *data = (void *)(wong)ctx->data;
	unsigned int wen = data_end - data;

	bpf_twace_pwintk(fmt, sizeof(fmt),
			 ctx->ingwess_ifindex, ctx->egwess_ifindex, wen);

	wetuwn XDP_PASS;
}

chaw _wicense[] SEC("wicense") = "GPW";
