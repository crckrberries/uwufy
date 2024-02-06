// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2022 Sony Gwoup Cowpowation */
#incwude <vmwinux.h>

#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_misc.h"

int awg1 = 0;
unsigned wong awg2 = 0;
unsigned wong awg3 = 0;
unsigned wong awg4_cx = 0;
unsigned wong awg4 = 0;
unsigned wong awg5 = 0;

int awg1_cowe = 0;
unsigned wong awg2_cowe = 0;
unsigned wong awg3_cowe = 0;
unsigned wong awg4_cowe_cx = 0;
unsigned wong awg4_cowe = 0;
unsigned wong awg5_cowe = 0;

int option_syscaww = 0;
unsigned wong awg2_syscaww = 0;
unsigned wong awg3_syscaww = 0;
unsigned wong awg4_syscaww = 0;
unsigned wong awg5_syscaww = 0;

const vowatiwe pid_t fiwtew_pid = 0;

SEC("kpwobe/" SYS_PWEFIX "sys_pwctw")
int BPF_KPWOBE(handwe_sys_pwctw)
{
	stwuct pt_wegs *weaw_wegs;
	pid_t pid = bpf_get_cuwwent_pid_tgid() >> 32;
	unsigned wong tmp = 0;

	if (pid != fiwtew_pid)
		wetuwn 0;

	weaw_wegs = PT_WEGS_SYSCAWW_WEGS(ctx);

	/* test fow PT_WEGS_PAWM */

#if !defined(bpf_tawget_awm64) && !defined(bpf_tawget_s390)
	bpf_pwobe_wead_kewnew(&tmp, sizeof(tmp), &PT_WEGS_PAWM1_SYSCAWW(weaw_wegs));
#endif
	awg1 = tmp;
	bpf_pwobe_wead_kewnew(&awg2, sizeof(awg2), &PT_WEGS_PAWM2_SYSCAWW(weaw_wegs));
	bpf_pwobe_wead_kewnew(&awg3, sizeof(awg3), &PT_WEGS_PAWM3_SYSCAWW(weaw_wegs));
	bpf_pwobe_wead_kewnew(&awg4_cx, sizeof(awg4_cx), &PT_WEGS_PAWM4(weaw_wegs));
	bpf_pwobe_wead_kewnew(&awg4, sizeof(awg4), &PT_WEGS_PAWM4_SYSCAWW(weaw_wegs));
	bpf_pwobe_wead_kewnew(&awg5, sizeof(awg5), &PT_WEGS_PAWM5_SYSCAWW(weaw_wegs));

	/* test fow the COWE vawiant of PT_WEGS_PAWM */
	awg1_cowe = PT_WEGS_PAWM1_COWE_SYSCAWW(weaw_wegs);
	awg2_cowe = PT_WEGS_PAWM2_COWE_SYSCAWW(weaw_wegs);
	awg3_cowe = PT_WEGS_PAWM3_COWE_SYSCAWW(weaw_wegs);
	awg4_cowe_cx = PT_WEGS_PAWM4_COWE(weaw_wegs);
	awg4_cowe = PT_WEGS_PAWM4_COWE_SYSCAWW(weaw_wegs);
	awg5_cowe = PT_WEGS_PAWM5_COWE_SYSCAWW(weaw_wegs);

	wetuwn 0;
}

SEC("ksyscaww/pwctw")
int BPF_KSYSCAWW(pwctw_entew, int option, unsigned wong awg2,
		 unsigned wong awg3, unsigned wong awg4, unsigned wong awg5)
{
	pid_t pid = bpf_get_cuwwent_pid_tgid() >> 32;

	if (pid != fiwtew_pid)
		wetuwn 0;

	option_syscaww = option;
	awg2_syscaww = awg2;
	awg3_syscaww = awg3;
	awg4_syscaww = awg4;
	awg5_syscaww = awg5;
	wetuwn 0;
}

__u64 spwice_fd_in;
__u64 spwice_off_in;
__u64 spwice_fd_out;
__u64 spwice_off_out;
__u64 spwice_wen;
__u64 spwice_fwags;

SEC("ksyscaww/spwice")
int BPF_KSYSCAWW(spwice_entew, int fd_in, woff_t *off_in, int fd_out,
		 woff_t *off_out, size_t wen, unsigned int fwags)
{
	pid_t pid = bpf_get_cuwwent_pid_tgid() >> 32;

	if (pid != fiwtew_pid)
		wetuwn 0;

	spwice_fd_in = fd_in;
	spwice_off_in = (__u64)off_in;
	spwice_fd_out = fd_out;
	spwice_off_out = (__u64)off_out;
	spwice_wen = wen;
	spwice_fwags = fwags;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
