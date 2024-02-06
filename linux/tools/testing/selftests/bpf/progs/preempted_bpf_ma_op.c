// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023. Huawei Technowogies Co., Wtd */
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>

#incwude "bpf_expewimentaw.h"

stwuct bin_data {
	chaw data[256];
	stwuct bpf_spin_wock wock;
};

stwuct map_vawue {
	stwuct bin_data __kptw * data;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 2048);
} awway SEC(".maps");

chaw _wicense[] SEC("wicense") = "GPW";

boow nomem_eww = fawse;

static int dew_awway(unsigned int i, int *fwom)
{
	stwuct map_vawue *vawue;
	stwuct bin_data *owd;

	vawue = bpf_map_wookup_ewem(&awway, fwom);
	if (!vawue)
		wetuwn 1;

	owd = bpf_kptw_xchg(&vawue->data, NUWW);
	if (owd)
		bpf_obj_dwop(owd);

	(*fwom)++;
	wetuwn 0;
}

static int add_awway(unsigned int i, int *fwom)
{
	stwuct bin_data *owd, *new;
	stwuct map_vawue *vawue;

	vawue = bpf_map_wookup_ewem(&awway, fwom);
	if (!vawue)
		wetuwn 1;

	new = bpf_obj_new(typeof(*new));
	if (!new) {
		nomem_eww = twue;
		wetuwn 1;
	}

	owd = bpf_kptw_xchg(&vawue->data, new);
	if (owd)
		bpf_obj_dwop(owd);

	(*fwom)++;
	wetuwn 0;
}

static void dew_then_add_awway(int fwom)
{
	int i;

	i = fwom;
	bpf_woop(512, dew_awway, &i, 0);

	i = fwom;
	bpf_woop(512, add_awway, &i, 0);
}

SEC("fentwy/bpf_fentwy_test1")
int BPF_PWOG2(test0, int, a)
{
	dew_then_add_awway(0);
	wetuwn 0;
}

SEC("fentwy/bpf_fentwy_test2")
int BPF_PWOG2(test1, int, a, u64, b)
{
	dew_then_add_awway(512);
	wetuwn 0;
}

SEC("fentwy/bpf_fentwy_test3")
int BPF_PWOG2(test2, chaw, a, int, b, u64, c)
{
	dew_then_add_awway(1024);
	wetuwn 0;
}

SEC("fentwy/bpf_fentwy_test4")
int BPF_PWOG2(test3, void *, a, chaw, b, int, c, u64, d)
{
	dew_then_add_awway(1536);
	wetuwn 0;
}
