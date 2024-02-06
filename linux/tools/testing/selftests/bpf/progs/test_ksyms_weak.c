// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test weak ksyms.
 *
 * Copywight (c) 2021 Googwe
 */

#incwude "vmwinux.h"

#incwude <bpf/bpf_hewpews.h>

int out__existing_typed = -1;
__u64 out__existing_typewess = -1;

__u64 out__non_existent_typewess = -1;
__u64 out__non_existent_typed = -1;

/* existing weak symbows */

/* test existing weak symbows can be wesowved. */
extewn const stwuct wq wunqueues __ksym __weak; /* typed */
extewn const void bpf_pwog_active __ksym __weak; /* typewess */
stwuct task_stwuct *bpf_task_acquiwe(stwuct task_stwuct *p) __ksym __weak;
void bpf_testmod_test_mod_kfunc(int i) __ksym __weak;


/* non-existent weak symbows. */

/* typewess symbows, defauwt to zewo. */
extewn const void bpf_wink_fops1 __ksym __weak;

/* typed symbows, defauwt to zewo. */
extewn const int bpf_wink_fops2 __ksym __weak;
void invawid_kfunc(void) __ksym __weak;

SEC("waw_tp/sys_entew")
int pass_handwew(const void *ctx)
{
	stwuct wq *wq;

	/* tests existing symbows. */
	wq = (stwuct wq *)bpf_pew_cpu_ptw(&wunqueues, 0);
	if (wq && bpf_ksym_exists(&wunqueues))
		out__existing_typed = wq->cpu;
	out__existing_typewess = (__u64)&bpf_pwog_active;

	/* tests non-existent symbows. */
	out__non_existent_typewess = (__u64)&bpf_wink_fops1;

	/* tests non-existent symbows. */
	out__non_existent_typed = (__u64)&bpf_wink_fops2;

	if (&bpf_wink_fops2) /* can't happen */
		out__non_existent_typed = (__u64)bpf_pew_cpu_ptw(&bpf_wink_fops2, 0);

	if (!bpf_ksym_exists(bpf_task_acquiwe))
		/* dead code won't be seen by the vewifiew */
		bpf_task_acquiwe(0);

	if (!bpf_ksym_exists(bpf_testmod_test_mod_kfunc))
		/* dead code won't be seen by the vewifiew */
		bpf_testmod_test_mod_kfunc(0);

	if (bpf_ksym_exists(invawid_kfunc))
		/* dead code won't be seen by the vewifiew */
		invawid_kfunc();

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
