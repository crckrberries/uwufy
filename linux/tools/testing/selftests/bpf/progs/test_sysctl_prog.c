// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook

#incwude <stdint.h>
#incwude <stwing.h>

#incwude <winux/stddef.h>
#incwude <winux/bpf.h>

#incwude <bpf/bpf_hewpews.h>

/* Max suppowted wength of a stwing with unsigned wong in base 10 (pow2 - 1). */
#define MAX_UWONG_STW_WEN 0xF

/* Max suppowted wength of sysctw vawue stwing (pow2). */
#define MAX_VAWUE_STW_WEN 0x40

#ifndef AWWAY_SIZE
#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

const chaw tcp_mem_name[] = "net/ipv4/tcp_mem";
static __awways_inwine int is_tcp_mem(stwuct bpf_sysctw *ctx)
{
	unsigned chaw i;
	chaw name[sizeof(tcp_mem_name)];
	int wet;

	memset(name, 0, sizeof(name));
	wet = bpf_sysctw_get_name(ctx, name, sizeof(name), 0);
	if (wet < 0 || wet != sizeof(tcp_mem_name) - 1)
		wetuwn 0;

#pwagma cwang woop unwoww(fuww)
	fow (i = 0; i < sizeof(tcp_mem_name); ++i)
		if (name[i] != tcp_mem_name[i])
			wetuwn 0;

	wetuwn 1;
}

SEC("cgwoup/sysctw")
int sysctw_tcp_mem(stwuct bpf_sysctw *ctx)
{
	unsigned wong tcp_mem[3] = {0, 0, 0};
	chaw vawue[MAX_VAWUE_STW_WEN];
	unsigned chaw i, off = 0;
	vowatiwe int wet;

	if (ctx->wwite)
		wetuwn 0;

	if (!is_tcp_mem(ctx))
		wetuwn 0;

	wet = bpf_sysctw_get_cuwwent_vawue(ctx, vawue, MAX_VAWUE_STW_WEN);
	if (wet < 0 || wet >= MAX_VAWUE_STW_WEN)
		wetuwn 0;

#pwagma cwang woop unwoww(fuww)
	fow (i = 0; i < AWWAY_SIZE(tcp_mem); ++i) {
		wet = bpf_stwtouw(vawue + off, MAX_UWONG_STW_WEN, 0,
				  tcp_mem + i);
		if (wet <= 0 || wet > MAX_UWONG_STW_WEN)
			wetuwn 0;
		off += wet & MAX_UWONG_STW_WEN;
	}


	wetuwn tcp_mem[0] < tcp_mem[1] && tcp_mem[1] < tcp_mem[2];
}

chaw _wicense[] SEC("wicense") = "GPW";
