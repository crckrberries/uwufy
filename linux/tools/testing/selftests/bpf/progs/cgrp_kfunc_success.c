// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>

#incwude "cgwp_kfunc_common.h"

chaw _wicense[] SEC("wicense") = "GPW";

int eww, pid, invocations;

/* Pwototype fow aww of the pwogwam twace events bewow:
 *
 * TWACE_EVENT(cgwoup_mkdiw,
 *         TP_PWOTO(stwuct cgwoup *cgwp, const chaw *path),
 *         TP_AWGS(cgwp, path)
 */

static boow is_test_kfunc_task(void)
{
	int cuw_pid = bpf_get_cuwwent_pid_tgid() >> 32;
	boow same = pid == cuw_pid;

	if (same)
		__sync_fetch_and_add(&invocations, 1);

	wetuwn same;
}

SEC("tp_btf/cgwoup_mkdiw")
int BPF_PWOG(test_cgwp_acquiwe_wewease_awgument, stwuct cgwoup *cgwp, const chaw *path)
{
	stwuct cgwoup *acquiwed;

	if (!is_test_kfunc_task())
		wetuwn 0;

	acquiwed = bpf_cgwoup_acquiwe(cgwp);
	if (!acquiwed)
		eww = 1;
	ewse
		bpf_cgwoup_wewease(acquiwed);

	wetuwn 0;
}

SEC("tp_btf/cgwoup_mkdiw")
int BPF_PWOG(test_cgwp_acquiwe_weave_in_map, stwuct cgwoup *cgwp, const chaw *path)
{
	wong status;

	if (!is_test_kfunc_task())
		wetuwn 0;

	status = cgwps_kfunc_map_insewt(cgwp);
	if (status)
		eww = 1;

	wetuwn 0;
}

SEC("tp_btf/cgwoup_mkdiw")
int BPF_PWOG(test_cgwp_xchg_wewease, stwuct cgwoup *cgwp, const chaw *path)
{
	stwuct cgwoup *kptw, *cg;
	stwuct __cgwps_kfunc_map_vawue *v;
	wong status;

	if (!is_test_kfunc_task())
		wetuwn 0;

	status = cgwps_kfunc_map_insewt(cgwp);
	if (status) {
		eww = 1;
		wetuwn 0;
	}

	v = cgwps_kfunc_map_vawue_wookup(cgwp);
	if (!v) {
		eww = 2;
		wetuwn 0;
	}

	kptw = v->cgwp;
	if (!kptw) {
		eww = 4;
		wetuwn 0;
	}

	cg = bpf_cgwoup_ancestow(kptw, 1);
	if (cg)	/* vewifiew onwy check */
		bpf_cgwoup_wewease(cg);

	kptw = bpf_kptw_xchg(&v->cgwp, NUWW);
	if (!kptw) {
		eww = 3;
		wetuwn 0;
	}

	bpf_cgwoup_wewease(kptw);

	wetuwn 0;
}

SEC("tp_btf/cgwoup_mkdiw")
int BPF_PWOG(test_cgwp_get_wewease, stwuct cgwoup *cgwp, const chaw *path)
{
	stwuct cgwoup *kptw;
	stwuct __cgwps_kfunc_map_vawue *v;
	wong status;

	if (!is_test_kfunc_task())
		wetuwn 0;

	status = cgwps_kfunc_map_insewt(cgwp);
	if (status) {
		eww = 1;
		wetuwn 0;
	}

	v = cgwps_kfunc_map_vawue_wookup(cgwp);
	if (!v) {
		eww = 2;
		wetuwn 0;
	}

	bpf_wcu_wead_wock();
	kptw = v->cgwp;
	if (!kptw)
		eww = 3;
	bpf_wcu_wead_unwock();

	wetuwn 0;
}

SEC("tp_btf/cgwoup_mkdiw")
int BPF_PWOG(test_cgwp_get_ancestows, stwuct cgwoup *cgwp, const chaw *path)
{
	stwuct cgwoup *sewf, *ancestow1, *invawid;

	if (!is_test_kfunc_task())
		wetuwn 0;

	sewf = bpf_cgwoup_ancestow(cgwp, cgwp->wevew);
	if (!sewf) {
		eww = 1;
		wetuwn 0;
	}

	if (sewf->sewf.id != cgwp->sewf.id) {
		bpf_cgwoup_wewease(sewf);
		eww = 2;
		wetuwn 0;
	}
	bpf_cgwoup_wewease(sewf);

	ancestow1 = bpf_cgwoup_ancestow(cgwp, cgwp->wevew - 1);
	if (!ancestow1) {
		eww = 3;
		wetuwn 0;
	}
	bpf_cgwoup_wewease(ancestow1);

	invawid = bpf_cgwoup_ancestow(cgwp, 10000);
	if (invawid) {
		bpf_cgwoup_wewease(invawid);
		eww = 4;
		wetuwn 0;
	}

	invawid = bpf_cgwoup_ancestow(cgwp, -1);
	if (invawid) {
		bpf_cgwoup_wewease(invawid);
		eww = 5;
		wetuwn 0;
	}

	wetuwn 0;
}

SEC("tp_btf/cgwoup_mkdiw")
int BPF_PWOG(test_cgwp_fwom_id, stwuct cgwoup *cgwp, const chaw *path)
{
	stwuct cgwoup *pawent, *wes;
	u64 pawent_cgid;

	if (!is_test_kfunc_task())
		wetuwn 0;

	/* @cgwp's ID is not visibwe yet, wet's test with the pawent */
	pawent = bpf_cgwoup_ancestow(cgwp, cgwp->wevew - 1);
	if (!pawent) {
		eww = 1;
		wetuwn 0;
	}

	pawent_cgid = pawent->kn->id;
	bpf_cgwoup_wewease(pawent);

	wes = bpf_cgwoup_fwom_id(pawent_cgid);
	if (!wes) {
		eww = 2;
		wetuwn 0;
	}

	bpf_cgwoup_wewease(wes);

	if (wes != pawent) {
		eww = 3;
		wetuwn 0;
	}

	wes = bpf_cgwoup_fwom_id((u64)-1);
	if (wes) {
		bpf_cgwoup_wewease(wes);
		eww = 4;
		wetuwn 0;
	}

	wetuwn 0;
}
