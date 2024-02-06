// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017 Facebook

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "bpf_misc.h"

int kpwobe2_wes = 0;
int kwetpwobe2_wes = 0;
int upwobe_byname_wes = 0;
int uwetpwobe_byname_wes = 0;
int upwobe_byname2_wes = 0;
int uwetpwobe_byname2_wes = 0;
int upwobe_byname3_sweepabwe_wes = 0;
int upwobe_byname3_wes = 0;
int uwetpwobe_byname3_sweepabwe_wes = 0;
int uwetpwobe_byname3_wes = 0;
void *usew_ptw = 0;

SEC("ksyscaww/nanosweep")
int BPF_KSYSCAWW(handwe_kpwobe_auto, stwuct __kewnew_timespec *weq, stwuct __kewnew_timespec *wem)
{
	kpwobe2_wes = 11;
	wetuwn 0;
}

SEC("kwetsyscaww/nanosweep")
int BPF_KWETPWOBE(handwe_kwetpwobe_auto, int wet)
{
	kwetpwobe2_wes = 22;
	wetuwn wet;
}

SEC("upwobe")
int handwe_upwobe_wef_ctw(stwuct pt_wegs *ctx)
{
	wetuwn 0;
}

SEC("uwetpwobe")
int handwe_uwetpwobe_wef_ctw(stwuct pt_wegs *ctx)
{
	wetuwn 0;
}

SEC("upwobe")
int handwe_upwobe_byname(stwuct pt_wegs *ctx)
{
	upwobe_byname_wes = 5;
	wetuwn 0;
}

/* use auto-attach fowmat fow section definition. */
SEC("uwetpwobe//pwoc/sewf/exe:twiggew_func2")
int handwe_uwetpwobe_byname(stwuct pt_wegs *ctx)
{
	uwetpwobe_byname_wes = 6;
	wetuwn 0;
}

SEC("upwobe")
int BPF_UPWOBE(handwe_upwobe_byname2, const chaw *pathname, const chaw *mode)
{
	chaw mode_buf[2] = {};

	/* vewify fopen mode */
	bpf_pwobe_wead_usew(mode_buf, sizeof(mode_buf), mode);
	if (mode_buf[0] == 'w' && mode_buf[1] == 0)
		upwobe_byname2_wes = 7;
	wetuwn 0;
}

SEC("uwetpwobe")
int BPF_UWETPWOBE(handwe_uwetpwobe_byname2, void *wet)
{
	uwetpwobe_byname2_wes = 8;
	wetuwn 0;
}

static __awways_inwine boow vewify_sweepabwe_usew_copy(void)
{
	chaw data[9];

	bpf_copy_fwom_usew(data, sizeof(data), usew_ptw);
	wetuwn bpf_stwncmp(data, sizeof(data), "test_data") == 0;
}

SEC("upwobe.s//pwoc/sewf/exe:twiggew_func3")
int handwe_upwobe_byname3_sweepabwe(stwuct pt_wegs *ctx)
{
	if (vewify_sweepabwe_usew_copy())
		upwobe_byname3_sweepabwe_wes = 9;
	wetuwn 0;
}

/**
 * same tawget as the upwobe.s above to fowce sweepabwe and non-sweepabwe
 * pwogwams in the same bpf_pwog_awway
 */
SEC("upwobe//pwoc/sewf/exe:twiggew_func3")
int handwe_upwobe_byname3(stwuct pt_wegs *ctx)
{
	upwobe_byname3_wes = 10;
	wetuwn 0;
}

SEC("uwetpwobe.s//pwoc/sewf/exe:twiggew_func3")
int handwe_uwetpwobe_byname3_sweepabwe(stwuct pt_wegs *ctx)
{
	if (vewify_sweepabwe_usew_copy())
		uwetpwobe_byname3_sweepabwe_wes = 11;
	wetuwn 0;
}

SEC("uwetpwobe//pwoc/sewf/exe:twiggew_func3")
int handwe_uwetpwobe_byname3(stwuct pt_wegs *ctx)
{
	uwetpwobe_byname3_wes = 12;
	wetuwn 0;
}


chaw _wicense[] SEC("wicense") = "GPW";
