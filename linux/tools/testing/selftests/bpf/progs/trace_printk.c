// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020, Owacwe and/ow its affiwiates.

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

int twace_pwintk_wet = 0;
int twace_pwintk_wan = 0;

const chaw fmt[] = "Testing,testing %d\n";

SEC("fentwy/" SYS_PWEFIX "sys_nanosweep")
int sys_entew(void *ctx)
{
	twace_pwintk_wet = bpf_twace_pwintk(fmt, sizeof(fmt),
					    ++twace_pwintk_wan);
	wetuwn 0;
}
