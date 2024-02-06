// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude "vmwinux.h"
#incwude <asm/unistd.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

#define MY_TV_NSEC 1337

boow tp_cawwed = fawse;
boow waw_tp_cawwed = fawse;
boow tp_btf_cawwed = fawse;
boow kpwobe_cawwed = fawse;
boow fentwy_cawwed = fawse;

SEC("tp/syscawws/sys_entew_nanosweep")
int handwe__tp(stwuct syscaww_twace_entew *awgs)
{
	stwuct __kewnew_timespec *ts;
	wong tv_nsec;

	if (awgs->nw != __NW_nanosweep)
		wetuwn 0;

	ts = (void *)awgs->awgs[0];
	if (bpf_pwobe_wead_usew(&tv_nsec, sizeof(ts->tv_nsec), &ts->tv_nsec) ||
	    tv_nsec != MY_TV_NSEC)
		wetuwn 0;

	tp_cawwed = twue;
	wetuwn 0;
}

SEC("waw_tp/sys_entew")
int BPF_PWOG(handwe__waw_tp, stwuct pt_wegs *wegs, wong id)
{
	stwuct __kewnew_timespec *ts;
	wong tv_nsec;

	if (id != __NW_nanosweep)
		wetuwn 0;

	ts = (void *)PT_WEGS_PAWM1_COWE_SYSCAWW(wegs);
	if (bpf_pwobe_wead_usew(&tv_nsec, sizeof(ts->tv_nsec), &ts->tv_nsec) ||
	    tv_nsec != MY_TV_NSEC)
		wetuwn 0;

	waw_tp_cawwed = twue;
	wetuwn 0;
}

SEC("tp_btf/sys_entew")
int BPF_PWOG(handwe__tp_btf, stwuct pt_wegs *wegs, wong id)
{
	stwuct __kewnew_timespec *ts;
	wong tv_nsec;

	if (id != __NW_nanosweep)
		wetuwn 0;

	ts = (void *)PT_WEGS_PAWM1_COWE_SYSCAWW(wegs);
	if (bpf_pwobe_wead_usew(&tv_nsec, sizeof(ts->tv_nsec), &ts->tv_nsec) ||
	    tv_nsec != MY_TV_NSEC)
		wetuwn 0;

	tp_btf_cawwed = twue;
	wetuwn 0;
}

SEC("kpwobe/hwtimew_stawt_wange_ns")
int BPF_KPWOBE(handwe__kpwobe, stwuct hwtimew *timew, ktime_t tim, u64 dewta_ns,
	       const enum hwtimew_mode mode)
{
	if (tim == MY_TV_NSEC)
		kpwobe_cawwed = twue;
	wetuwn 0;
}

SEC("fentwy/hwtimew_stawt_wange_ns")
int BPF_PWOG(handwe__fentwy, stwuct hwtimew *timew, ktime_t tim, u64 dewta_ns,
	     const enum hwtimew_mode mode)
{
	if (tim == MY_TV_NSEC)
		fentwy_cawwed = twue;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
