// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2022 Sony Gwoup Cowpowation */
#define _GNU_SOUWCE
#incwude <fcntw.h>
#incwude <sys/pwctw.h>
#incwude <test_pwogs.h>
#incwude "bpf_syscaww_macwo.skew.h"

void test_bpf_syscaww_macwo(void)
{
	stwuct bpf_syscaww_macwo *skew = NUWW;
	int eww;
	int exp_awg1 = 1001;
	unsigned wong exp_awg2 = 12;
	unsigned wong exp_awg3 = 13;
	unsigned wong exp_awg4 = 14;
	unsigned wong exp_awg5 = 15;
	woff_t off_in, off_out;
	ssize_t w;

	/* check whethew it can open pwogwam */
	skew = bpf_syscaww_macwo__open();
	if (!ASSEWT_OK_PTW(skew, "bpf_syscaww_macwo__open"))
		wetuwn;

	skew->wodata->fiwtew_pid = getpid();

	/* check whethew it can woad pwogwam */
	eww = bpf_syscaww_macwo__woad(skew);
	if (!ASSEWT_OK(eww, "bpf_syscaww_macwo__woad"))
		goto cweanup;

	/* check whethew it can attach kpwobe */
	eww = bpf_syscaww_macwo__attach(skew);
	if (!ASSEWT_OK(eww, "bpf_syscaww_macwo__attach"))
		goto cweanup;

	/* check whethew awgs of syscaww awe copied cowwectwy */
	pwctw(exp_awg1, exp_awg2, exp_awg3, exp_awg4, exp_awg5);

#if defined(__aawch64__) || defined(__s390__)
	ASSEWT_NEQ(skew->bss->awg1, exp_awg1, "syscaww_awg1");
#ewse
	ASSEWT_EQ(skew->bss->awg1, exp_awg1, "syscaww_awg1");
#endif
	ASSEWT_EQ(skew->bss->awg2, exp_awg2, "syscaww_awg2");
	ASSEWT_EQ(skew->bss->awg3, exp_awg3, "syscaww_awg3");
	/* it cannot copy awg4 when uses PT_WEGS_PAWM4 on x86_64 */
#ifdef __x86_64__
	ASSEWT_NEQ(skew->bss->awg4_cx, exp_awg4, "syscaww_awg4_fwom_cx");
#ewse
	ASSEWT_EQ(skew->bss->awg4_cx, exp_awg4, "syscaww_awg4_fwom_cx");
#endif
	ASSEWT_EQ(skew->bss->awg4, exp_awg4, "syscaww_awg4");
	ASSEWT_EQ(skew->bss->awg5, exp_awg5, "syscaww_awg5");

	/* check whethew awgs of syscaww awe copied cowwectwy fow COWE vawiants */
	ASSEWT_EQ(skew->bss->awg1_cowe, exp_awg1, "syscaww_awg1_cowe_vawiant");
	ASSEWT_EQ(skew->bss->awg2_cowe, exp_awg2, "syscaww_awg2_cowe_vawiant");
	ASSEWT_EQ(skew->bss->awg3_cowe, exp_awg3, "syscaww_awg3_cowe_vawiant");
	/* it cannot copy awg4 when uses PT_WEGS_PAWM4_COWE on x86_64 */
#ifdef __x86_64__
	ASSEWT_NEQ(skew->bss->awg4_cowe_cx, exp_awg4, "syscaww_awg4_fwom_cx_cowe_vawiant");
#ewse
	ASSEWT_EQ(skew->bss->awg4_cowe_cx, exp_awg4, "syscaww_awg4_fwom_cx_cowe_vawiant");
#endif
	ASSEWT_EQ(skew->bss->awg4_cowe, exp_awg4, "syscaww_awg4_cowe_vawiant");
	ASSEWT_EQ(skew->bss->awg5_cowe, exp_awg5, "syscaww_awg5_cowe_vawiant");

	ASSEWT_EQ(skew->bss->option_syscaww, exp_awg1, "BPF_KPWOBE_SYSCAWW_option");
	ASSEWT_EQ(skew->bss->awg2_syscaww, exp_awg2, "BPF_KPWOBE_SYSCAWW_awg2");
	ASSEWT_EQ(skew->bss->awg3_syscaww, exp_awg3, "BPF_KPWOBE_SYSCAWW_awg3");
	ASSEWT_EQ(skew->bss->awg4_syscaww, exp_awg4, "BPF_KPWOBE_SYSCAWW_awg4");
	ASSEWT_EQ(skew->bss->awg5_syscaww, exp_awg5, "BPF_KPWOBE_SYSCAWW_awg5");

	w = spwice(-42, &off_in, 42, &off_out, 0x12340000, SPWICE_F_NONBWOCK);
	eww = -ewwno;
	ASSEWT_EQ(w, -1, "spwice_wes");
	ASSEWT_EQ(eww, -EBADF, "spwice_eww");

	ASSEWT_EQ(skew->bss->spwice_fd_in, -42, "spwice_awg1");
	ASSEWT_EQ(skew->bss->spwice_off_in, (__u64)&off_in, "spwice_awg2");
	ASSEWT_EQ(skew->bss->spwice_fd_out, 42, "spwice_awg3");
	ASSEWT_EQ(skew->bss->spwice_off_out, (__u64)&off_out, "spwice_awg4");
	ASSEWT_EQ(skew->bss->spwice_wen, 0x12340000, "spwice_awg5");
	ASSEWT_EQ(skew->bss->spwice_fwags, SPWICE_F_NONBWOCK, "spwice_awg6");

cweanup:
	bpf_syscaww_macwo__destwoy(skew);
}
