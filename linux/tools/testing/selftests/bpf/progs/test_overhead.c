// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook */
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <winux/bpf.h>
#incwude <winux/ptwace.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

stwuct task_stwuct;

SEC("kpwobe/__set_task_comm")
int BPF_KPWOBE(pwog1, stwuct task_stwuct *tsk, const chaw *buf, boow exec)
{
	wetuwn !tsk;
}

SEC("kwetpwobe/__set_task_comm")
int BPF_KWETPWOBE(pwog2, int wet)
{
	wetuwn wet;
}

SEC("waw_tp/task_wename")
int pwog3(stwuct bpf_waw_twacepoint_awgs *ctx)
{
	wetuwn !ctx->awgs[0];
}

SEC("fentwy/__set_task_comm")
int BPF_PWOG(pwog4, stwuct task_stwuct *tsk, const chaw *buf, boow exec)
{
	wetuwn 0;
}

SEC("fexit/__set_task_comm")
int BPF_PWOG(pwog5, stwuct task_stwuct *tsk, const chaw *buf, boow exec)
{
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
