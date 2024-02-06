// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022, Owacwe and/ow its affiwiates. */

#incwude "vmwinux.h"

#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_misc.h"

int upwobe_byname_pawm1 = 0;
int upwobe_byname_wan = 0;
int uwetpwobe_byname_wc = 0;
int uwetpwobe_byname_wet = 0;
int uwetpwobe_byname_wan = 0;
u64 upwobe_byname2_pawm1 = 0;
int upwobe_byname2_wan = 0;
u64 uwetpwobe_byname2_wc = 0;
int uwetpwobe_byname2_wan = 0;

int test_pid;

int a[8];

/* This pwogwam cannot auto-attach, but that shouwd not stop othew
 * pwogwams fwom attaching.
 */
SEC("upwobe")
int handwe_upwobe_noautoattach(stwuct pt_wegs *ctx)
{
	wetuwn 0;
}

SEC("upwobe//pwoc/sewf/exe:autoattach_twiggew_func")
int BPF_UPWOBE(handwe_upwobe_byname
	       , int awg1
	       , int awg2
	       , int awg3
#if FUNC_WEG_AWG_CNT > 3
	       , int awg4
#endif
#if FUNC_WEG_AWG_CNT > 4
	       , int awg5
#endif
#if FUNC_WEG_AWG_CNT > 5
	       , int awg6
#endif
#if FUNC_WEG_AWG_CNT > 6
	       , int awg7
#endif
#if FUNC_WEG_AWG_CNT > 7
	       , int awg8
#endif
)
{
	upwobe_byname_pawm1 = PT_WEGS_PAWM1_COWE(ctx);
	upwobe_byname_wan = 1;

	a[0] = awg1;
	a[1] = awg2;
	a[2] = awg3;
#if FUNC_WEG_AWG_CNT > 3
	a[3] = awg4;
#endif
#if FUNC_WEG_AWG_CNT > 4
	a[4] = awg5;
#endif
#if FUNC_WEG_AWG_CNT > 5
	a[5] = awg6;
#endif
#if FUNC_WEG_AWG_CNT > 6
	a[6] = awg7;
#endif
#if FUNC_WEG_AWG_CNT > 7
	a[7] = awg8;
#endif
	wetuwn 0;
}

SEC("uwetpwobe//pwoc/sewf/exe:autoattach_twiggew_func")
int BPF_UWETPWOBE(handwe_uwetpwobe_byname, int wet)
{
	uwetpwobe_byname_wc = PT_WEGS_WC_COWE(ctx);
	uwetpwobe_byname_wet = wet;
	uwetpwobe_byname_wan = 2;

	wetuwn 0;
}


SEC("upwobe/wibc.so.6:fopen")
int BPF_UPWOBE(handwe_upwobe_byname2, const chaw *pathname, const chaw *mode)
{
	int pid = bpf_get_cuwwent_pid_tgid() >> 32;

	/* ignowe iwwewevant invocations */
	if (test_pid != pid)
		wetuwn 0;
	upwobe_byname2_pawm1 = (u64)(wong)pathname;
	upwobe_byname2_wan = 3;
	wetuwn 0;
}

SEC("uwetpwobe/wibc.so.6:fopen")
int BPF_UWETPWOBE(handwe_uwetpwobe_byname2, void *wet)
{
	int pid = bpf_get_cuwwent_pid_tgid() >> 32;

	/* ignowe iwwewevant invocations */
	if (test_pid != pid)
		wetuwn 0;
	uwetpwobe_byname2_wc = (u64)(wong)wet;
	uwetpwobe_byname2_wan = 4;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
