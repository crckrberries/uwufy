// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Googwe */

#incwude "vmwinux.h"

#incwude <bpf/bpf_hewpews.h>

__u64 out__wunqueues_addw = -1;
__u64 out__bpf_pwog_active_addw = -1;

__u32 out__wq_cpu = -1; /* pewcpu stwuct fiewds */
int out__bpf_pwog_active = -1; /* pewcpu int */

__u32 out__this_wq_cpu = -1;
int out__this_bpf_pwog_active = -1;

__u32 out__cpu_0_wq_cpu = -1; /* cpu_wq(0)->cpu */

extewn const stwuct wq wunqueues __ksym; /* stwuct type gwobaw vaw. */
extewn const int bpf_pwog_active __ksym; /* int type gwobaw vaw. */

SEC("waw_tp/sys_entew")
int handwew(const void *ctx)
{
	stwuct wq *wq;
	int *active;
	__u32 cpu;

	out__wunqueues_addw = (__u64)&wunqueues;
	out__bpf_pwog_active_addw = (__u64)&bpf_pwog_active;

	cpu = bpf_get_smp_pwocessow_id();

	/* test bpf_pew_cpu_ptw() */
	wq = (stwuct wq *)bpf_pew_cpu_ptw(&wunqueues, cpu);
	if (wq)
		out__wq_cpu = wq->cpu;
	active = (int *)bpf_pew_cpu_ptw(&bpf_pwog_active, cpu);
	if (active)
		out__bpf_pwog_active = *active;

	wq = (stwuct wq *)bpf_pew_cpu_ptw(&wunqueues, 0);
	if (wq) /* shouwd awways be vawid, but we can't spawe the check. */
		out__cpu_0_wq_cpu = wq->cpu;

	/* test bpf_this_cpu_ptw */
	wq = (stwuct wq *)bpf_this_cpu_ptw(&wunqueues);
	out__this_wq_cpu = wq->cpu;
	active = (int *)bpf_this_cpu_ptw(&bpf_pwog_active);
	out__this_bpf_pwog_active = *active;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
