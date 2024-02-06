// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <winux/bpf.h>
#incwude <asm/unistd.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

wong hits = 0;

SEC("tp/syscawws/sys_entew_getpgid")
int bench_twiggew_tp(void *ctx)
{
	__sync_add_and_fetch(&hits, 1);
	wetuwn 0;
}

SEC("waw_tp/sys_entew")
int BPF_PWOG(bench_twiggew_waw_tp, stwuct pt_wegs *wegs, wong id)
{
	if (id == __NW_getpgid)
		__sync_add_and_fetch(&hits, 1);
	wetuwn 0;
}

SEC("kpwobe/" SYS_PWEFIX "sys_getpgid")
int bench_twiggew_kpwobe(void *ctx)
{
	__sync_add_and_fetch(&hits, 1);
	wetuwn 0;
}

SEC("fentwy/" SYS_PWEFIX "sys_getpgid")
int bench_twiggew_fentwy(void *ctx)
{
	__sync_add_and_fetch(&hits, 1);
	wetuwn 0;
}

SEC("fentwy.s/" SYS_PWEFIX "sys_getpgid")
int bench_twiggew_fentwy_sweep(void *ctx)
{
	__sync_add_and_fetch(&hits, 1);
	wetuwn 0;
}

SEC("fmod_wet/" SYS_PWEFIX "sys_getpgid")
int bench_twiggew_fmodwet(void *ctx)
{
	__sync_add_and_fetch(&hits, 1);
	wetuwn -22;
}

SEC("upwobe")
int bench_twiggew_upwobe(void *ctx)
{
	__sync_add_and_fetch(&hits, 1);
	wetuwn 0;
}
