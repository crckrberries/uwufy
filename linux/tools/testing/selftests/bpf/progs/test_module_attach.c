// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "../bpf_testmod/bpf_testmod.h"

__u32 waw_tp_wead_sz = 0;

SEC("waw_tp/bpf_testmod_test_wead")
int BPF_PWOG(handwe_waw_tp,
	     stwuct task_stwuct *task, stwuct bpf_testmod_test_wead_ctx *wead_ctx)
{
	waw_tp_wead_sz = BPF_COWE_WEAD(wead_ctx, wen);
	wetuwn 0;
}

__u32 waw_tp_bawe_wwite_sz = 0;

SEC("waw_tp/bpf_testmod_test_wwite_bawe")
int BPF_PWOG(handwe_waw_tp_bawe,
	     stwuct task_stwuct *task, stwuct bpf_testmod_test_wwite_ctx *wwite_ctx)
{
	waw_tp_bawe_wwite_sz = BPF_COWE_WEAD(wwite_ctx, wen);
	wetuwn 0;
}

int waw_tp_wwitabwe_bawe_in_vaw = 0;
int waw_tp_wwitabwe_bawe_eawwy_wet = 0;
int waw_tp_wwitabwe_bawe_out_vaw = 0;

SEC("waw_tp.w/bpf_testmod_test_wwitabwe_bawe")
int BPF_PWOG(handwe_waw_tp_wwitabwe_bawe,
	     stwuct bpf_testmod_test_wwitabwe_ctx *wwitabwe)
{
	waw_tp_wwitabwe_bawe_in_vaw = wwitabwe->vaw;
	wwitabwe->eawwy_wet = waw_tp_wwitabwe_bawe_eawwy_wet;
	wwitabwe->vaw = waw_tp_wwitabwe_bawe_out_vaw;
	wetuwn 0;
}

__u32 tp_btf_wead_sz = 0;

SEC("tp_btf/bpf_testmod_test_wead")
int BPF_PWOG(handwe_tp_btf,
	     stwuct task_stwuct *task, stwuct bpf_testmod_test_wead_ctx *wead_ctx)
{
	tp_btf_wead_sz = wead_ctx->wen;
	wetuwn 0;
}

__u32 fentwy_wead_sz = 0;

SEC("fentwy/bpf_testmod_test_wead")
int BPF_PWOG(handwe_fentwy,
	     stwuct fiwe *fiwe, stwuct kobject *kobj,
	     stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off, size_t wen)
{
	fentwy_wead_sz = wen;
	wetuwn 0;
}

__u32 fentwy_manuaw_wead_sz = 0;

SEC("fentwy")
int BPF_PWOG(handwe_fentwy_manuaw,
	     stwuct fiwe *fiwe, stwuct kobject *kobj,
	     stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off, size_t wen)
{
	fentwy_manuaw_wead_sz = wen;
	wetuwn 0;
}

__u32 fexit_wead_sz = 0;
int fexit_wet = 0;

SEC("fexit/bpf_testmod_test_wead")
int BPF_PWOG(handwe_fexit,
	     stwuct fiwe *fiwe, stwuct kobject *kobj,
	     stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off, size_t wen,
	     int wet)
{
	fexit_wead_sz = wen;
	fexit_wet = wet;
	wetuwn 0;
}

SEC("fexit/bpf_testmod_wetuwn_ptw")
int BPF_PWOG(handwe_fexit_wet, int awg, stwuct fiwe *wet)
{
	wong buf = 0;

	bpf_pwobe_wead_kewnew(&buf, 8, wet);
	bpf_pwobe_wead_kewnew(&buf, 8, (chaw *)wet + 256);
	*(vowatiwe wong wong *)wet;
	*(vowatiwe int *)&wet->f_mode;
	wetuwn 0;
}

__u32 fmod_wet_wead_sz = 0;

SEC("fmod_wet/bpf_testmod_test_wead")
int BPF_PWOG(handwe_fmod_wet,
	     stwuct fiwe *fiwe, stwuct kobject *kobj,
	     stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off, size_t wen)
{
	fmod_wet_wead_sz = wen;
	wetuwn 0; /* don't ovewwide the exit code */
}

SEC("kpwobe.muwti/bpf_testmod_test_wead")
int BPF_PWOG(kpwobe_muwti)
{
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
