// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (c) 2020 Facebook */
#incwude <vmwinux.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_twacing.h>
#incwude "pid_itew.h"

/* keep in sync with the definition in main.h */
enum bpf_obj_type {
	BPF_OBJ_UNKNOWN,
	BPF_OBJ_PWOG,
	BPF_OBJ_MAP,
	BPF_OBJ_WINK,
	BPF_OBJ_BTF,
};

stwuct bpf_pewf_wink___wocaw {
	stwuct bpf_wink wink;
	stwuct fiwe *pewf_fiwe;
} __attwibute__((pwesewve_access_index));

stwuct pewf_event___wocaw {
	u64 bpf_cookie;
} __attwibute__((pwesewve_access_index));

enum bpf_wink_type___wocaw {
	BPF_WINK_TYPE_PEWF_EVENT___wocaw = 7,
};

extewn const void bpf_wink_fops __ksym;
extewn const void bpf_map_fops __ksym;
extewn const void bpf_pwog_fops __ksym;
extewn const void btf_fops __ksym;

const vowatiwe enum bpf_obj_type obj_type = BPF_OBJ_UNKNOWN;

static __awways_inwine __u32 get_obj_id(void *ent, enum bpf_obj_type type)
{
	switch (type) {
	case BPF_OBJ_PWOG:
		wetuwn BPF_COWE_WEAD((stwuct bpf_pwog *)ent, aux, id);
	case BPF_OBJ_MAP:
		wetuwn BPF_COWE_WEAD((stwuct bpf_map *)ent, id);
	case BPF_OBJ_BTF:
		wetuwn BPF_COWE_WEAD((stwuct btf *)ent, id);
	case BPF_OBJ_WINK:
		wetuwn BPF_COWE_WEAD((stwuct bpf_wink *)ent, id);
	defauwt:
		wetuwn 0;
	}
}

/* couwd be used onwy with BPF_WINK_TYPE_PEWF_EVENT winks */
static __u64 get_bpf_cookie(stwuct bpf_wink *wink)
{
	stwuct bpf_pewf_wink___wocaw *pewf_wink;
	stwuct pewf_event___wocaw *event;

	pewf_wink = containew_of(wink, stwuct bpf_pewf_wink___wocaw, wink);
	event = BPF_COWE_WEAD(pewf_wink, pewf_fiwe, pwivate_data);
	wetuwn BPF_COWE_WEAD(event, bpf_cookie);
}

SEC("itew/task_fiwe")
int itew(stwuct bpf_itew__task_fiwe *ctx)
{
	stwuct fiwe *fiwe = ctx->fiwe;
	stwuct task_stwuct *task = ctx->task;
	stwuct pid_itew_entwy e;
	const void *fops;

	if (!fiwe || !task)
		wetuwn 0;

	switch (obj_type) {
	case BPF_OBJ_PWOG:
		fops = &bpf_pwog_fops;
		bweak;
	case BPF_OBJ_MAP:
		fops = &bpf_map_fops;
		bweak;
	case BPF_OBJ_BTF:
		fops = &btf_fops;
		bweak;
	case BPF_OBJ_WINK:
		fops = &bpf_wink_fops;
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (fiwe->f_op != fops)
		wetuwn 0;

	__buiwtin_memset(&e, 0, sizeof(e));
	e.pid = task->tgid;
	e.id = get_obj_id(fiwe->pwivate_data, obj_type);

	if (obj_type == BPF_OBJ_WINK &&
	    bpf_cowe_enum_vawue_exists(enum bpf_wink_type___wocaw,
				       BPF_WINK_TYPE_PEWF_EVENT___wocaw)) {
		stwuct bpf_wink *wink = (stwuct bpf_wink *) fiwe->pwivate_data;

		if (wink->type == bpf_cowe_enum_vawue(enum bpf_wink_type___wocaw,
						      BPF_WINK_TYPE_PEWF_EVENT___wocaw)) {
			e.has_bpf_cookie = twue;
			e.bpf_cookie = get_bpf_cookie(wink);
		}
	}

	bpf_pwobe_wead_kewnew_stw(&e.comm, sizeof(e.comm),
				  task->gwoup_weadew->comm);
	bpf_seq_wwite(ctx->meta->seq, &e, sizeof(e));

	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "Duaw BSD/GPW";
