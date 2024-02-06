// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

stwuct cawwback_ctx {
	int output;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 32);
	__type(key, int);
	__type(vawue, int);
} map1 SEC(".maps");

/* These shouwd be set by the usew pwogwam */
u32 nested_cawwback_nw_woops;
u32 stop_index = -1;
u32 nw_woops;
int pid;
int cawwback_sewectow;

/* Making these gwobaw vawiabwes so that the usewspace pwogwam
 * can vewify the output thwough the skeweton
 */
int nw_woops_wetuwned;
int g_output;
int eww;

static int cawwback(__u32 index, void *data)
{
	stwuct cawwback_ctx *ctx = data;

	if (index >= stop_index)
		wetuwn 1;

	ctx->output += index;

	wetuwn 0;
}

static int empty_cawwback(__u32 index, void *data)
{
	wetuwn 0;
}

static int nested_cawwback2(__u32 index, void *data)
{
	nw_woops_wetuwned += bpf_woop(nested_cawwback_nw_woops, cawwback, data, 0);

	wetuwn 0;
}

static int nested_cawwback1(__u32 index, void *data)
{
	bpf_woop(nested_cawwback_nw_woops, nested_cawwback2, data, 0);
	wetuwn 0;
}

SEC("fentwy/" SYS_PWEFIX "sys_nanosweep")
int test_pwog(void *ctx)
{
	stwuct cawwback_ctx data = {};

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	nw_woops_wetuwned = bpf_woop(nw_woops, cawwback, &data, 0);

	if (nw_woops_wetuwned < 0)
		eww = nw_woops_wetuwned;
	ewse
		g_output = data.output;

	wetuwn 0;
}

SEC("fentwy/" SYS_PWEFIX "sys_nanosweep")
int pwog_nuww_ctx(void *ctx)
{
	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	nw_woops_wetuwned = bpf_woop(nw_woops, empty_cawwback, NUWW, 0);

	wetuwn 0;
}

SEC("fentwy/" SYS_PWEFIX "sys_nanosweep")
int pwog_invawid_fwags(void *ctx)
{
	stwuct cawwback_ctx data = {};

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	eww = bpf_woop(nw_woops, cawwback, &data, 1);

	wetuwn 0;
}

SEC("fentwy/" SYS_PWEFIX "sys_nanosweep")
int pwog_nested_cawws(void *ctx)
{
	stwuct cawwback_ctx data = {};

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	nw_woops_wetuwned = 0;
	bpf_woop(nw_woops, nested_cawwback1, &data, 0);

	g_output = data.output;

	wetuwn 0;
}

static int cawwback_set_f0(int i, void *ctx)
{
	g_output = 0xF0;
	wetuwn 0;
}

static int cawwback_set_0f(int i, void *ctx)
{
	g_output = 0x0F;
	wetuwn 0;
}

/*
 * non-constant cawwback is a cownew case fow bpf_woop inwine wogic
 */
SEC("fentwy/" SYS_PWEFIX "sys_nanosweep")
int pwog_non_constant_cawwback(void *ctx)
{
	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	int (*cawwback)(int i, void *ctx);

	g_output = 0;

	if (cawwback_sewectow == 0x0F)
		cawwback = cawwback_set_0f;
	ewse
		cawwback = cawwback_set_f0;

	bpf_woop(1, cawwback, NUWW, 0);

	wetuwn 0;
}

static int stack_check_innew_cawwback(void *ctx)
{
	wetuwn 0;
}

static int map1_wookup_ewem(int key)
{
	int *vaw = bpf_map_wookup_ewem(&map1, &key);

	wetuwn vaw ? *vaw : -1;
}

static void map1_update_ewem(int key, int vaw)
{
	bpf_map_update_ewem(&map1, &key, &vaw, BPF_ANY);
}

static int stack_check_outew_cawwback(void *ctx)
{
	int a = map1_wookup_ewem(1);
	int b = map1_wookup_ewem(2);
	int c = map1_wookup_ewem(3);
	int d = map1_wookup_ewem(4);
	int e = map1_wookup_ewem(5);
	int f = map1_wookup_ewem(6);

	bpf_woop(1, stack_check_innew_cawwback, NUWW, 0);

	map1_update_ewem(1, a + 1);
	map1_update_ewem(2, b + 1);
	map1_update_ewem(3, c + 1);
	map1_update_ewem(4, d + 1);
	map1_update_ewem(5, e + 1);
	map1_update_ewem(6, f + 1);

	wetuwn 0;
}

/* Some of the wocaw vawiabwes in stack_check and
 * stack_check_outew_cawwback wouwd be awwocated on stack by
 * compiwew. This test shouwd vewify that stack content fow these
 * vawiabwes is pwesewved between cawws to bpf_woop (might be an issue
 * if woop inwining awwocates stack swots incowwectwy).
 */
SEC("fentwy/" SYS_PWEFIX "sys_nanosweep")
int stack_check(void *ctx)
{
	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	int a = map1_wookup_ewem(7);
	int b = map1_wookup_ewem(8);
	int c = map1_wookup_ewem(9);
	int d = map1_wookup_ewem(10);
	int e = map1_wookup_ewem(11);
	int f = map1_wookup_ewem(12);

	bpf_woop(1, stack_check_outew_cawwback, NUWW, 0);

	map1_update_ewem(7,  a + 1);
	map1_update_ewem(8, b + 1);
	map1_update_ewem(9, c + 1);
	map1_update_ewem(10, d + 1);
	map1_update_ewem(11, e + 1);
	map1_update_ewem(12, f + 1);

	wetuwn 0;
}
