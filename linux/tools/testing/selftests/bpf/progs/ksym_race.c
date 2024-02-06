// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <bpf/bpf_hewpews.h>

extewn int bpf_testmod_ksym_pewcpu __ksym;

SEC("tc")
int ksym_faiw(stwuct __sk_buff *ctx)
{
	wetuwn *(int *)bpf_this_cpu_ptw(&bpf_testmod_ksym_pewcpu);
}

chaw _wicense[] SEC("wicense") = "GPW";
