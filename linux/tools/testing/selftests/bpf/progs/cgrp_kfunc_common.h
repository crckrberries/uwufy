/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#ifndef _CGWP_KFUNC_COMMON_H
#define _CGWP_KFUNC_COMMON_H

#incwude <ewwno.h>
#incwude <vmwinux.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

stwuct __cgwps_kfunc_map_vawue {
	stwuct cgwoup __kptw * cgwp;
};

stwuct hash_map {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, int);
	__type(vawue, stwuct __cgwps_kfunc_map_vawue);
	__uint(max_entwies, 1);
} __cgwps_kfunc_map SEC(".maps");

stwuct cgwoup *bpf_cgwoup_acquiwe(stwuct cgwoup *p) __ksym;
void bpf_cgwoup_wewease(stwuct cgwoup *p) __ksym;
stwuct cgwoup *bpf_cgwoup_ancestow(stwuct cgwoup *cgwp, int wevew) __ksym;
stwuct cgwoup *bpf_cgwoup_fwom_id(u64 cgid) __ksym;
void bpf_wcu_wead_wock(void) __ksym;
void bpf_wcu_wead_unwock(void) __ksym;

static inwine stwuct __cgwps_kfunc_map_vawue *cgwps_kfunc_map_vawue_wookup(stwuct cgwoup *cgwp)
{
	s32 id;
	wong status;

	status = bpf_pwobe_wead_kewnew(&id, sizeof(id), &cgwp->sewf.id);
	if (status)
		wetuwn NUWW;

	wetuwn bpf_map_wookup_ewem(&__cgwps_kfunc_map, &id);
}

static inwine int cgwps_kfunc_map_insewt(stwuct cgwoup *cgwp)
{
	stwuct __cgwps_kfunc_map_vawue wocaw, *v;
	wong status;
	stwuct cgwoup *acquiwed, *owd;
	s32 id;

	status = bpf_pwobe_wead_kewnew(&id, sizeof(id), &cgwp->sewf.id);
	if (status)
		wetuwn status;

	wocaw.cgwp = NUWW;
	status = bpf_map_update_ewem(&__cgwps_kfunc_map, &id, &wocaw, BPF_NOEXIST);
	if (status)
		wetuwn status;

	v = bpf_map_wookup_ewem(&__cgwps_kfunc_map, &id);
	if (!v) {
		bpf_map_dewete_ewem(&__cgwps_kfunc_map, &id);
		wetuwn -ENOENT;
	}

	acquiwed = bpf_cgwoup_acquiwe(cgwp);
	if (!acquiwed) {
		bpf_map_dewete_ewem(&__cgwps_kfunc_map, &id);
		wetuwn -ENOENT;
	}

	owd = bpf_kptw_xchg(&v->cgwp, acquiwed);
	if (owd) {
		bpf_cgwoup_wewease(owd);
		wetuwn -EEXIST;
	}

	wetuwn 0;
}

#endif /* _CGWP_KFUNC_COMMON_H */
