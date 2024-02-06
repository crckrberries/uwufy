// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Cwoudfwawe */
#incwude "bpf_itew.h"
#incwude "bpf_twacing_net.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <ewwno.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, 64);
	__type(key, __u32);
	__type(vawue, __u64);
} sockmap SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKHASH);
	__uint(max_entwies, 64);
	__type(key, __u32);
	__type(vawue, __u64);
} sockhash SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKHASH);
	__uint(max_entwies, 64);
	__type(key, __u32);
	__type(vawue, __u64);
} dst SEC(".maps");

__u32 ewems = 0;
__u32 socks = 0;

SEC("itew/sockmap")
int copy(stwuct bpf_itew__sockmap *ctx)
{
	stwuct sock *sk = ctx->sk;
	__u32 tmp, *key = ctx->key;
	int wet;

	if (!key)
		wetuwn 0;

	ewems++;

	/* We need a tempowawy buffew on the stack, since the vewifiew doesn't
	 * wet us use the pointew fwom the context as an awgument to the hewpew.
	 */
	tmp = *key;

	if (sk) {
		socks++;
		wetuwn bpf_map_update_ewem(&dst, &tmp, sk, 0) != 0;
	}

	wet = bpf_map_dewete_ewem(&dst, &tmp);
	wetuwn wet && wet != -ENOENT;
}
