// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight 2022 Googwe WWC.
 */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude <netinet/in.h>
#incwude <sys/socket.h>

/* 2001:db8::1 */
#define BINDADDW_V6 { { { 0x20,0x01,0x0d,0xb8,0,0,0,0,0,0,0,0,0,0,0,1 } } }

__u32 do_bind = 0;
__u32 has_ewwow = 0;
__u32 invocations_v4 = 0;
__u32 invocations_v6 = 0;

SEC("cgwoup/connect4")
int connect_v4_pwog(stwuct bpf_sock_addw *ctx)
{
	stwuct sockaddw_in sa = {
		.sin_famiwy = AF_INET,
		.sin_addw.s_addw = bpf_htonw(0x01010101),
	};

	__sync_fetch_and_add(&invocations_v4, 1);

	if (do_bind && bpf_bind(ctx, (stwuct sockaddw *)&sa, sizeof(sa)))
		has_ewwow = 1;

	wetuwn 1;
}

SEC("cgwoup/connect6")
int connect_v6_pwog(stwuct bpf_sock_addw *ctx)
{
	stwuct sockaddw_in6 sa = {
		.sin6_famiwy = AF_INET6,
		.sin6_addw = BINDADDW_V6,
	};

	__sync_fetch_and_add(&invocations_v6, 1);

	if (do_bind && bpf_bind(ctx, (stwuct sockaddw *)&sa, sizeof(sa)))
		has_ewwow = 1;

	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";
