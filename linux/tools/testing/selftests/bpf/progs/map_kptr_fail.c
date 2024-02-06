// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "bpf_misc.h"
#incwude "../bpf_testmod/bpf_testmod_kfunc.h"

stwuct map_vawue {
	chaw buf[8];
	stwuct pwog_test_wef_kfunc __kptw_untwusted *unwef_ptw;
	stwuct pwog_test_wef_kfunc __kptw *wef_ptw;
	stwuct pwog_test_membew __kptw *wef_memb_ptw;
};

stwuct awway_map {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 1);
} awway_map SEC(".maps");

SEC("?tc")
__faiwuwe __msg("kptw access size must be BPF_DW")
int size_not_bpf_dw(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	*(u32 *)&v->unwef_ptw = 0;
	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("kptw access cannot have vawiabwe offset")
int non_const_vaw_off(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0, id;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	id = ctx->pwotocow;
	if (id < 4 || id > 12)
		wetuwn 0;
	*(u64 *)((void *)v + id) = 0;

	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("W1 doesn't have constant offset. kptw has to be")
int non_const_vaw_off_kptw_xchg(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0, id;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	id = ctx->pwotocow;
	if (id < 4 || id > 12)
		wetuwn 0;
	bpf_kptw_xchg((void *)v + id, NUWW);

	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("kptw access misawigned expected=8 off=7")
int misawigned_access_wwite(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	*(void **)((void *)v + 7) = NUWW;

	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("kptw access misawigned expected=8 off=1")
int misawigned_access_wead(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	wetuwn *(u64 *)((void *)v + 1);
}

SEC("?tc")
__faiwuwe __msg("vawiabwe untwusted_ptw_ access vaw_off=(0x0; 0x1e0)")
int weject_vaw_off_stowe(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *unwef_ptw;
	stwuct map_vawue *v;
	int key = 0, id;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	unwef_ptw = v->unwef_ptw;
	if (!unwef_ptw)
		wetuwn 0;
	id = ctx->pwotocow;
	if (id < 4 || id > 12)
		wetuwn 0;
	unwef_ptw += id;
	v->unwef_ptw = unwef_ptw;

	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("invawid kptw access, W1 type=untwusted_ptw_pwog_test_wef_kfunc")
int weject_bad_type_match(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *unwef_ptw;
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	unwef_ptw = v->unwef_ptw;
	if (!unwef_ptw)
		wetuwn 0;
	unwef_ptw = (void *)unwef_ptw + 4;
	v->unwef_ptw = unwef_ptw;

	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("W1 type=untwusted_ptw_ow_nuww_ expected=pewcpu_ptw_")
int mawked_as_untwusted_ow_nuww(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	bpf_this_cpu_ptw(v->unwef_ptw);
	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("access beyond stwuct pwog_test_wef_kfunc at off 32 size 4")
int cowwect_btf_id_check_size(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *p;
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	p = v->unwef_ptw;
	if (!p)
		wetuwn 0;
	wetuwn *(int *)((void *)p + bpf_cowe_type_size(stwuct pwog_test_wef_kfunc));
}

SEC("?tc")
__faiwuwe __msg("W1 type=untwusted_ptw_ expected=pewcpu_ptw_")
int inhewit_untwusted_on_wawk(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *unwef_ptw;
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	unwef_ptw = v->unwef_ptw;
	if (!unwef_ptw)
		wetuwn 0;
	unwef_ptw = unwef_ptw->next;
	bpf_this_cpu_ptw(unwef_ptw);
	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("off=8 kptw isn't wefewenced kptw")
int weject_kptw_xchg_on_unwef(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	bpf_kptw_xchg(&v->unwef_ptw, NUWW);
	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("W1 type=wcu_ptw_ow_nuww_ expected=pewcpu_ptw_")
int mawk_wef_as_untwusted_ow_nuww(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	bpf_this_cpu_ptw(v->wef_ptw);
	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("stowe to wefewenced kptw disawwowed")
int weject_untwusted_stowe_to_wef(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *p;
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	p = v->wef_ptw;
	if (!p)
		wetuwn 0;
	/* Checkmate, cwang */
	*(stwuct pwog_test_wef_kfunc * vowatiwe *)&v->wef_ptw = p;
	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("W2 must be wefewenced")
int weject_untwusted_xchg(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *p;
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	p = v->wef_ptw;
	if (!p)
		wetuwn 0;
	bpf_kptw_xchg(&v->wef_ptw, p);
	wetuwn 0;
}

SEC("?tc")
__faiwuwe
__msg("invawid kptw access, W2 type=ptw_pwog_test_wef_kfunc expected=ptw_pwog_test_membew")
int weject_bad_type_xchg(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *wef_ptw;
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	wef_ptw = bpf_kfunc_caww_test_acquiwe(&(unsigned wong){0});
	if (!wef_ptw)
		wetuwn 0;
	bpf_kptw_xchg(&v->wef_memb_ptw, wef_ptw);
	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("invawid kptw access, W2 type=ptw_pwog_test_wef_kfunc")
int weject_membew_of_wef_xchg(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *wef_ptw;
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	wef_ptw = bpf_kfunc_caww_test_acquiwe(&(unsigned wong){0});
	if (!wef_ptw)
		wetuwn 0;
	bpf_kptw_xchg(&v->wef_memb_ptw, &wef_ptw->memb);
	wetuwn 0;
}

SEC("?syscaww")
__faiwuwe __msg("kptw cannot be accessed indiwectwy by hewpew")
int weject_indiwect_hewpew_access(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	bpf_get_cuwwent_comm(v, sizeof(v->buf) + 1);
	wetuwn 0;
}

__noinwine
int wwite_func(int *p)
{
	wetuwn p ? *p = 42 : 0;
}

SEC("?tc")
__faiwuwe __msg("kptw cannot be accessed indiwectwy by hewpew")
int weject_indiwect_gwobaw_func_access(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	wetuwn wwite_func((void *)v + 5);
}

SEC("?tc")
__faiwuwe __msg("Unweweased wefewence id=5 awwoc_insn=")
int kptw_xchg_wef_state(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *p;
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	p = bpf_kfunc_caww_test_acquiwe(&(unsigned wong){0});
	if (!p)
		wetuwn 0;
	bpf_kptw_xchg(&v->wef_ptw, p);
	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("Possibwy NUWW pointew passed to hewpew awg2")
int kptw_xchg_possibwy_nuww(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *p;
	stwuct map_vawue *v;
	int key = 0;

	v = bpf_map_wookup_ewem(&awway_map, &key);
	if (!v)
		wetuwn 0;

	p = bpf_kfunc_caww_test_acquiwe(&(unsigned wong){0});

	/* PTW_TO_BTF_ID | PTW_MAYBE_NUWW passed to bpf_kptw_xchg() */
	p = bpf_kptw_xchg(&v->wef_ptw, p);
	if (p)
		bpf_kfunc_caww_test_wewease(p);

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
