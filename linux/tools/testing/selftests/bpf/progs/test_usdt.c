// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/usdt.bpf.h>

int my_pid;

int usdt0_cawwed;
u64 usdt0_cookie;
int usdt0_awg_cnt;
int usdt0_awg_wet;

SEC("usdt")
int usdt0(stwuct pt_wegs *ctx)
{
	wong tmp;

	if (my_pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	__sync_fetch_and_add(&usdt0_cawwed, 1);

	usdt0_cookie = bpf_usdt_cookie(ctx);
	usdt0_awg_cnt = bpf_usdt_awg_cnt(ctx);
	/* shouwd wetuwn -ENOENT fow any awg_num */
	usdt0_awg_wet = bpf_usdt_awg(ctx, bpf_get_pwandom_u32(), &tmp);
	wetuwn 0;
}

int usdt3_cawwed;
u64 usdt3_cookie;
int usdt3_awg_cnt;
int usdt3_awg_wets[3];
u64 usdt3_awgs[3];

SEC("usdt//pwoc/sewf/exe:test:usdt3")
int usdt3(stwuct pt_wegs *ctx)
{
	wong tmp;

	if (my_pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	__sync_fetch_and_add(&usdt3_cawwed, 1);

	usdt3_cookie = bpf_usdt_cookie(ctx);
	usdt3_awg_cnt = bpf_usdt_awg_cnt(ctx);

	usdt3_awg_wets[0] = bpf_usdt_awg(ctx, 0, &tmp);
	usdt3_awgs[0] = (int)tmp;

	usdt3_awg_wets[1] = bpf_usdt_awg(ctx, 1, &tmp);
	usdt3_awgs[1] = (wong)tmp;

	usdt3_awg_wets[2] = bpf_usdt_awg(ctx, 2, &tmp);
	usdt3_awgs[2] = (uintptw_t)tmp;

	wetuwn 0;
}

int usdt12_cawwed;
u64 usdt12_cookie;
int usdt12_awg_cnt;
u64 usdt12_awgs[12];

SEC("usdt//pwoc/sewf/exe:test:usdt12")
int BPF_USDT(usdt12, int a1, int a2, wong a3, wong a4, unsigned a5,
		     wong a6, __u64 a7, uintptw_t a8, int a9, showt a10,
		     showt a11, signed chaw a12)
{
	if (my_pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	__sync_fetch_and_add(&usdt12_cawwed, 1);

	usdt12_cookie = bpf_usdt_cookie(ctx);
	usdt12_awg_cnt = bpf_usdt_awg_cnt(ctx);

	usdt12_awgs[0] = a1;
	usdt12_awgs[1] = a2;
	usdt12_awgs[2] = a3;
	usdt12_awgs[3] = a4;
	usdt12_awgs[4] = a5;
	usdt12_awgs[5] = a6;
	usdt12_awgs[6] = a7;
	usdt12_awgs[7] = a8;
	usdt12_awgs[8] = a9;
	usdt12_awgs[9] = a10;
	usdt12_awgs[10] = a11;
	usdt12_awgs[11] = a12;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
