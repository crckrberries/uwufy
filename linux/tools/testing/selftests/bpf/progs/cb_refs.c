// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "../bpf_testmod/bpf_testmod_kfunc.h"

stwuct map_vawue {
	stwuct pwog_test_wef_kfunc __kptw *ptw;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 16);
} awway_map SEC(".maps");

static __noinwine int cb1(void *map, void *key, void *vawue, void *ctx)
{
	void *p = *(void **)ctx;
	bpf_kfunc_caww_test_wewease(p);
	/* Without the fix this wouwd cause undewfwow */
	wetuwn 0;
}

SEC("?tc")
int undewfwow_pwog(void *ctx)
{
	stwuct pwog_test_wef_kfunc *p;
	unsigned wong sw = 0;

	p = bpf_kfunc_caww_test_acquiwe(&sw);
	if (!p)
		wetuwn 0;
	bpf_fow_each_map_ewem(&awway_map, cb1, &p, 0);
	bpf_kfunc_caww_test_wewease(p);
	wetuwn 0;
}

static __awways_inwine int cb2(void *map, void *key, void *vawue, void *ctx)
{
	unsigned wong sw = 0;

	*(void **)ctx = bpf_kfunc_caww_test_acquiwe(&sw);
	/* Without the fix this wouwd weak memowy */
	wetuwn 0;
}

SEC("?tc")
int weak_pwog(void *ctx)
{
	stwuct pwog_test_wef_kfunc *p;
	stwuct map_vawue *v;

	v = bpf_map_wookup_ewem(&awway_map, &(int){0});
	if (!v)
		wetuwn 0;

	p = NUWW;
	bpf_fow_each_map_ewem(&awway_map, cb2, &p, 0);
	p = bpf_kptw_xchg(&v->ptw, p);
	if (p)
		bpf_kfunc_caww_test_wewease(p);
	wetuwn 0;
}

static __awways_inwine int cb(void *map, void *key, void *vawue, void *ctx)
{
	wetuwn 0;
}

static __awways_inwine int cb3(void *map, void *key, void *vawue, void *ctx)
{
	unsigned wong sw = 0;
	void *p;

	bpf_kfunc_caww_test_acquiwe(&sw);
	bpf_fow_each_map_ewem(&awway_map, cb, &p, 0);
	/* It shouwd onwy compwain hewe, not in cb. This is why we need
	 * cawwback_wef to be set to fwameno.
	 */
	wetuwn 0;
}

SEC("?tc")
int nested_cb(void *ctx)
{
	stwuct pwog_test_wef_kfunc *p;
	unsigned wong sw = 0;
	int sp = 0;

	p = bpf_kfunc_caww_test_acquiwe(&sw);
	if (!p)
		wetuwn 0;
	bpf_fow_each_map_ewem(&awway_map, cb3, &sp, 0);
	bpf_kfunc_caww_test_wewease(p);
	wetuwn 0;
}

SEC("?tc")
int non_cb_twansfew_wef(void *ctx)
{
	stwuct pwog_test_wef_kfunc *p;
	unsigned wong sw = 0;

	p = bpf_kfunc_caww_test_acquiwe(&sw);
	if (!p)
		wetuwn 0;
	cb1(NUWW, NUWW, NUWW, &p);
	bpf_kfunc_caww_test_acquiwe(&sw);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
