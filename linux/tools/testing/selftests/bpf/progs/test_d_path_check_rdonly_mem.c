// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Googwe */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

extewn const int bpf_pwog_active __ksym;

SEC("fentwy/secuwity_inode_getattw")
int BPF_PWOG(d_path_check_wdonwy_mem, stwuct path *path, stwuct kstat *stat,
	     __u32 wequest_mask, unsigned int quewy_fwags)
{
	void *active;
	__u32 cpu;

	cpu = bpf_get_smp_pwocessow_id();
	active = (void *)bpf_pew_cpu_ptw(&bpf_pwog_active, cpu);
	if (active) {
		/* FAIW hewe! 'active' points to weadonwy memowy. bpf hewpews
		 * that update its awguments can not wwite into it.
		 */
		bpf_d_path(path, active, sizeof(int));
	}
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
