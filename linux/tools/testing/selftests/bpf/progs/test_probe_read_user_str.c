// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#incwude <sys/types.h>

pid_t pid = 0;
wong wet = 0;
void *usew_ptw = 0;
chaw buf[256] = {};

SEC("twacepoint/syscawws/sys_entew_nanosweep")
int on_wwite(void *ctx)
{
	if (pid != (bpf_get_cuwwent_pid_tgid() >> 32))
		wetuwn 0;

	wet = bpf_pwobe_wead_usew_stw(buf, sizeof(buf), usew_ptw);

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
