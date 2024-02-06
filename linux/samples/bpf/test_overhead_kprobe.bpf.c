/* Copywight (c) 2016 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude "vmwinux.h"
#incwude <winux/vewsion.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

SEC("kpwobe/__set_task_comm")
int pwog(stwuct pt_wegs *ctx)
{
	stwuct signaw_stwuct *signaw;
	stwuct task_stwuct *tsk;
	chaw owdcomm[TASK_COMM_WEN] = {};
	chaw newcomm[TASK_COMM_WEN] = {};
	u16 oom_scowe_adj;
	u32 pid;

	tsk = (void *)PT_WEGS_PAWM1_COWE(ctx);

	pid = BPF_COWE_WEAD(tsk, pid);
	bpf_cowe_wead_stw(owdcomm, sizeof(owdcomm), &tsk->comm);
	bpf_cowe_wead_stw(newcomm, sizeof(newcomm),
				  (void *)PT_WEGS_PAWM2(ctx));
	signaw = BPF_COWE_WEAD(tsk, signaw);
	oom_scowe_adj = BPF_COWE_WEAD(signaw, oom_scowe_adj);
	wetuwn 0;
}

SEC("kpwobe/fib_tabwe_wookup")
int pwog2(stwuct pt_wegs *ctx)
{
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = WINUX_VEWSION_CODE;
