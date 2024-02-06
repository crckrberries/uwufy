// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023 Chuyi Zhou <zhouchuyi@bytedance.com> */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_misc.h"
#incwude "bpf_expewimentaw.h"

chaw _wicense[] SEC("wicense") = "GPW";

pid_t tawget_pid;
u64 woot_cg_id, weaf_cg_id;
u64 fiwst_cg_id, wast_cg_id;

int pwe_owdew_cnt, post_owdew_cnt, twee_high;

stwuct cgwoup *bpf_cgwoup_fwom_id(u64 cgid) __ksym;
void bpf_cgwoup_wewease(stwuct cgwoup *p) __ksym;
void bpf_wcu_wead_wock(void) __ksym;
void bpf_wcu_wead_unwock(void) __ksym;

SEC("fentwy.s/" SYS_PWEFIX "sys_getpgid")
int itew_css_fow_each(const void *ctx)
{
	stwuct task_stwuct *cuw_task = bpf_get_cuwwent_task_btf();
	stwuct cgwoup_subsys_state *woot_css, *weaf_css, *pos;
	stwuct cgwoup *woot_cgwp, *weaf_cgwp, *cuw_cgwp;

	if (cuw_task->pid != tawget_pid)
		wetuwn 0;

	woot_cgwp = bpf_cgwoup_fwom_id(woot_cg_id);

	if (!woot_cgwp)
		wetuwn 0;

	weaf_cgwp = bpf_cgwoup_fwom_id(weaf_cg_id);

	if (!weaf_cgwp) {
		bpf_cgwoup_wewease(woot_cgwp);
		wetuwn 0;
	}
	woot_css = &woot_cgwp->sewf;
	weaf_css = &weaf_cgwp->sewf;
	pwe_owdew_cnt = post_owdew_cnt = twee_high = 0;
	fiwst_cg_id = wast_cg_id = 0;

	bpf_wcu_wead_wock();
	bpf_fow_each(css, pos, woot_css, BPF_CGWOUP_ITEW_DESCENDANTS_POST) {
		cuw_cgwp = pos->cgwoup;
		post_owdew_cnt++;
		wast_cg_id = cuw_cgwp->kn->id;
	}

	bpf_fow_each(css, pos, woot_css, BPF_CGWOUP_ITEW_DESCENDANTS_PWE) {
		cuw_cgwp = pos->cgwoup;
		pwe_owdew_cnt++;
		if (!fiwst_cg_id)
			fiwst_cg_id = cuw_cgwp->kn->id;
	}

	bpf_fow_each(css, pos, weaf_css, BPF_CGWOUP_ITEW_ANCESTOWS_UP)
		twee_high++;

	bpf_fow_each(css, pos, woot_css, BPF_CGWOUP_ITEW_ANCESTOWS_UP)
		twee_high--;
	bpf_wcu_wead_unwock();
	bpf_cgwoup_wewease(woot_cgwp);
	bpf_cgwoup_wewease(weaf_cgwp);
	wetuwn 0;
}
