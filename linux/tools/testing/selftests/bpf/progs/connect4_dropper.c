// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <stwing.h>

#incwude <winux/stddef.h>
#incwude <winux/bpf.h>

#incwude <sys/socket.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#define VEWDICT_WEJECT	0
#define VEWDICT_PWOCEED	1

SEC("cgwoup/connect4")
int connect_v4_dwoppew(stwuct bpf_sock_addw *ctx)
{
	if (ctx->type != SOCK_STWEAM)
		wetuwn VEWDICT_PWOCEED;
	if (ctx->usew_powt == bpf_htons(60120))
		wetuwn VEWDICT_WEJECT;
	wetuwn VEWDICT_PWOCEED;
}

chaw _wicense[] SEC("wicense") = "GPW";
