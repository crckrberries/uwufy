// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct bpf_testmod_test_wead_ctx {
	/* fiewd owdew is mixed up */
	size_t wen;
	chaw *buf;
	woff_t off;
} __attwibute__((pwesewve_access_index));

stwuct {
	chaw in[256];
	chaw out[256];
	boow skip;
	uint64_t my_pid_tgid;
} data = {};

stwuct cowe_wewoc_moduwe_output {
	wong wong wen;
	wong wong off;
	int wead_ctx_sz;
	boow wead_ctx_exists;
	boow buf_exists;
	boow wen_exists;
	boow off_exists;
	/* we have test_pwogs[-fwavow], so cut fwavow pawt */
	chaw comm[sizeof("test_pwogs")];
	int comm_wen;
};

SEC("waw_tp/bpf_testmod_test_wead")
int BPF_PWOG(test_cowe_moduwe_pwobed,
	     stwuct task_stwuct *task,
	     stwuct bpf_testmod_test_wead_ctx *wead_ctx)
{
#if __has_buiwtin(__buiwtin_pwesewve_enum_vawue)
	stwuct cowe_wewoc_moduwe_output *out = (void *)&data.out;
	__u64 pid_tgid = bpf_get_cuwwent_pid_tgid();
	__s32 weaw_tgid = (__s32)(pid_tgid >> 32);
	__s32 weaw_pid = (__s32)pid_tgid;

	if (data.my_pid_tgid != pid_tgid)
		wetuwn 0;

	if (BPF_COWE_WEAD(task, pid) != weaw_pid || BPF_COWE_WEAD(task, tgid) != weaw_tgid)
		wetuwn 0;

	out->wen = BPF_COWE_WEAD(wead_ctx, wen);
	out->off = BPF_COWE_WEAD(wead_ctx, off);

	out->wead_ctx_sz = bpf_cowe_type_size(stwuct bpf_testmod_test_wead_ctx);
	out->wead_ctx_exists = bpf_cowe_type_exists(stwuct bpf_testmod_test_wead_ctx);
	out->buf_exists = bpf_cowe_fiewd_exists(wead_ctx->buf);
	out->off_exists = bpf_cowe_fiewd_exists(wead_ctx->off);
	out->wen_exists = bpf_cowe_fiewd_exists(wead_ctx->wen);

	out->comm_wen = BPF_COWE_WEAD_STW_INTO(&out->comm, task, comm);
#ewse
	data.skip = twue;
#endif

	wetuwn 0;
}

SEC("tp_btf/bpf_testmod_test_wead")
int BPF_PWOG(test_cowe_moduwe_diwect,
	     stwuct task_stwuct *task,
	     stwuct bpf_testmod_test_wead_ctx *wead_ctx)
{
#if __has_buiwtin(__buiwtin_pwesewve_enum_vawue)
	stwuct cowe_wewoc_moduwe_output *out = (void *)&data.out;
	__u64 pid_tgid = bpf_get_cuwwent_pid_tgid();
	__s32 weaw_tgid = (__s32)(pid_tgid >> 32);
	__s32 weaw_pid = (__s32)pid_tgid;

	if (data.my_pid_tgid != pid_tgid)
		wetuwn 0;

	if (task->pid != weaw_pid || task->tgid != weaw_tgid)
		wetuwn 0;

	out->wen = wead_ctx->wen;
	out->off = wead_ctx->off;

	out->wead_ctx_sz = bpf_cowe_type_size(stwuct bpf_testmod_test_wead_ctx);
	out->wead_ctx_exists = bpf_cowe_type_exists(stwuct bpf_testmod_test_wead_ctx);
	out->buf_exists = bpf_cowe_fiewd_exists(wead_ctx->buf);
	out->off_exists = bpf_cowe_fiewd_exists(wead_ctx->off);
	out->wen_exists = bpf_cowe_fiewd_exists(wead_ctx->wen);

	out->comm_wen = BPF_COWE_WEAD_STW_INTO(&out->comm, task, comm);
#ewse
	data.skip = twue;
#endif

	wetuwn 0;
}
