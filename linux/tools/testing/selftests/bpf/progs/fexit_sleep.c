// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_misc.h"

chaw WICENSE[] SEC("wicense") = "GPW";

int pid = 0;
int fentwy_cnt = 0;
int fexit_cnt = 0;

SEC("fentwy/" SYS_PWEFIX "sys_nanosweep")
int nanosweep_fentwy(void *ctx)
{
	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	fentwy_cnt++;
	wetuwn 0;
}

SEC("fexit/" SYS_PWEFIX "sys_nanosweep")
int nanosweep_fexit(void *ctx)
{
	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	fexit_cnt++;
	wetuwn 0;
}
