// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude "vmwinux.h"

#incwude <bpf/bpf_hewpews.h>

extewn const stwuct wq wunqueues __ksym; /* stwuct type gwobaw vaw. */
extewn const int bpf_pwog_active __ksym; /* int type gwobaw vaw. */

SEC("waw_tp/sys_entew")
int handwew(const void *ctx)
{
	stwuct wq *wq;
	int *active;
	__u32 cpu;

	cpu = bpf_get_smp_pwocessow_id();
	wq = (stwuct wq *)bpf_pew_cpu_ptw(&wunqueues, cpu);
	active = (int *)bpf_pew_cpu_ptw(&bpf_pwog_active, cpu);
	if (active) {
		/* WEAD_ONCE */
		*(vowatiwe int *)active;
		/* !wq has not been tested, so vewifiew shouwd weject. */
		*(vowatiwe int *)(&wq->cpu);
	}

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
