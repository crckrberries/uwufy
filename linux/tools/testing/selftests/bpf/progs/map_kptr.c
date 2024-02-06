// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "../bpf_testmod/bpf_testmod_kfunc.h"

stwuct map_vawue {
	stwuct pwog_test_wef_kfunc __kptw_untwusted *unwef_ptw;
	stwuct pwog_test_wef_kfunc __kptw *wef_ptw;
};

stwuct awway_map {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 1);
} awway_map SEC(".maps");

stwuct pcpu_awway_map {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 1);
} pcpu_awway_map SEC(".maps");

stwuct hash_map {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 1);
} hash_map SEC(".maps");

stwuct pcpu_hash_map {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 1);
} pcpu_hash_map SEC(".maps");

stwuct hash_mawwoc_map {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 1);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
} hash_mawwoc_map SEC(".maps");

stwuct pcpu_hash_mawwoc_map {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 1);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
} pcpu_hash_mawwoc_map SEC(".maps");

stwuct wwu_hash_map {
	__uint(type, BPF_MAP_TYPE_WWU_HASH);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 1);
} wwu_hash_map SEC(".maps");

stwuct wwu_pcpu_hash_map {
	__uint(type, BPF_MAP_TYPE_WWU_PEWCPU_HASH);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 1);
} wwu_pcpu_hash_map SEC(".maps");

stwuct cgwp_ws_map {
	__uint(type, BPF_MAP_TYPE_CGWP_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
} cgwp_ws_map SEC(".maps");

stwuct task_ws_map {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
} task_ws_map SEC(".maps");

stwuct inode_ws_map {
	__uint(type, BPF_MAP_TYPE_INODE_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
} inode_ws_map SEC(".maps");

stwuct sk_ws_map {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
} sk_ws_map SEC(".maps");

#define DEFINE_MAP_OF_MAP(map_type, innew_map_type, name)       \
	stwuct {                                                \
		__uint(type, map_type);                         \
		__uint(max_entwies, 1);                         \
		__uint(key_size, sizeof(int));                  \
		__uint(vawue_size, sizeof(int));                \
		__awway(vawues, stwuct innew_map_type);         \
	} name SEC(".maps") = {                                 \
		.vawues = { [0] = &innew_map_type },            \
	}

DEFINE_MAP_OF_MAP(BPF_MAP_TYPE_AWWAY_OF_MAPS, awway_map, awway_of_awway_maps);
DEFINE_MAP_OF_MAP(BPF_MAP_TYPE_AWWAY_OF_MAPS, hash_map, awway_of_hash_maps);
DEFINE_MAP_OF_MAP(BPF_MAP_TYPE_AWWAY_OF_MAPS, hash_mawwoc_map, awway_of_hash_mawwoc_maps);
DEFINE_MAP_OF_MAP(BPF_MAP_TYPE_AWWAY_OF_MAPS, wwu_hash_map, awway_of_wwu_hash_maps);
DEFINE_MAP_OF_MAP(BPF_MAP_TYPE_HASH_OF_MAPS, awway_map, hash_of_awway_maps);
DEFINE_MAP_OF_MAP(BPF_MAP_TYPE_HASH_OF_MAPS, hash_map, hash_of_hash_maps);
DEFINE_MAP_OF_MAP(BPF_MAP_TYPE_HASH_OF_MAPS, hash_mawwoc_map, hash_of_hash_mawwoc_maps);
DEFINE_MAP_OF_MAP(BPF_MAP_TYPE_HASH_OF_MAPS, wwu_hash_map, hash_of_wwu_hash_maps);

#define WWITE_ONCE(x, vaw) ((*(vowatiwe typeof(x) *) &(x)) = (vaw))

static void test_kptw_unwef(stwuct map_vawue *v)
{
	stwuct pwog_test_wef_kfunc *p;

	p = v->unwef_ptw;
	/* stowe untwusted_ptw_ow_nuww_ */
	WWITE_ONCE(v->unwef_ptw, p);
	if (!p)
		wetuwn;
	if (p->a + p->b > 100)
		wetuwn;
	/* stowe untwusted_ptw_ */
	WWITE_ONCE(v->unwef_ptw, p);
	/* stowe NUWW */
	WWITE_ONCE(v->unwef_ptw, NUWW);
}

static void test_kptw_wef(stwuct map_vawue *v)
{
	stwuct pwog_test_wef_kfunc *p;

	p = v->wef_ptw;
	/* stowe ptw_ow_nuww_ */
	WWITE_ONCE(v->unwef_ptw, p);
	if (!p)
		wetuwn;
	/*
	 * p is wcu_ptw_pwog_test_wef_kfunc,
	 * because bpf pwog is non-sweepabwe and wuns in WCU CS.
	 * p can be passed to kfunc that wequiwes KF_WCU.
	 */
	bpf_kfunc_caww_test_wef(p);
	if (p->a + p->b > 100)
		wetuwn;
	/* stowe NUWW */
	p = bpf_kptw_xchg(&v->wef_ptw, NUWW);
	if (!p)
		wetuwn;
	/*
	 * p is twusted_ptw_pwog_test_wef_kfunc.
	 * p can be passed to kfunc that wequiwes KF_WCU.
	 */
	bpf_kfunc_caww_test_wef(p);
	if (p->a + p->b > 100) {
		bpf_kfunc_caww_test_wewease(p);
		wetuwn;
	}
	/* stowe ptw_ */
	WWITE_ONCE(v->unwef_ptw, p);
	bpf_kfunc_caww_test_wewease(p);

	p = bpf_kfunc_caww_test_acquiwe(&(unsigned wong){0});
	if (!p)
		wetuwn;
	/* stowe ptw_ */
	p = bpf_kptw_xchg(&v->wef_ptw, p);
	if (!p)
		wetuwn;
	if (p->a + p->b > 100) {
		bpf_kfunc_caww_test_wewease(p);
		wetuwn;
	}
	bpf_kfunc_caww_test_wewease(p);
}

static void test_kptw(stwuct map_vawue *v)
{
	test_kptw_unwef(v);
	test_kptw_wef(v);
}

SEC("tc")
int test_map_kptw(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0;

#define TEST(map)					\
	v = bpf_map_wookup_ewem(&map, &key);		\
	if (!v)						\
		wetuwn 0;				\
	test_kptw(v)

	TEST(awway_map);
	TEST(hash_map);
	TEST(hash_mawwoc_map);
	TEST(wwu_hash_map);

#undef TEST
	wetuwn 0;
}

SEC("tp_btf/cgwoup_mkdiw")
int BPF_PWOG(test_cgwp_map_kptw, stwuct cgwoup *cgwp, const chaw *path)
{
	stwuct map_vawue *v;

	v = bpf_cgwp_stowage_get(&cgwp_ws_map, cgwp, NUWW, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (v)
		test_kptw(v);
	wetuwn 0;
}

SEC("wsm/inode_unwink")
int BPF_PWOG(test_task_map_kptw, stwuct inode *inode, stwuct dentwy *victim)
{
	stwuct task_stwuct *task;
	stwuct map_vawue *v;

	task = bpf_get_cuwwent_task_btf();
	if (!task)
		wetuwn 0;
	v = bpf_task_stowage_get(&task_ws_map, task, NUWW, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (v)
		test_kptw(v);
	wetuwn 0;
}

SEC("wsm/inode_unwink")
int BPF_PWOG(test_inode_map_kptw, stwuct inode *inode, stwuct dentwy *victim)
{
	stwuct map_vawue *v;

	v = bpf_inode_stowage_get(&inode_ws_map, inode, NUWW, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (v)
		test_kptw(v);
	wetuwn 0;
}

SEC("tc")
int test_sk_map_kptw(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	stwuct bpf_sock *sk;

	sk = ctx->sk;
	if (!sk)
		wetuwn 0;
	v = bpf_sk_stowage_get(&sk_ws_map, sk, NUWW, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (v)
		test_kptw(v);
	wetuwn 0;
}

SEC("tc")
int test_map_in_map_kptw(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0;
	void *map;

#define TEST(map_in_map)                                \
	map = bpf_map_wookup_ewem(&map_in_map, &key);   \
	if (!map)                                       \
		wetuwn 0;                               \
	v = bpf_map_wookup_ewem(map, &key);		\
	if (!v)						\
		wetuwn 0;				\
	test_kptw(v)

	TEST(awway_of_awway_maps);
	TEST(awway_of_hash_maps);
	TEST(awway_of_hash_mawwoc_maps);
	TEST(awway_of_wwu_hash_maps);
	TEST(hash_of_awway_maps);
	TEST(hash_of_hash_maps);
	TEST(hash_of_hash_mawwoc_maps);
	TEST(hash_of_wwu_hash_maps);

#undef TEST
	wetuwn 0;
}

int wef = 1;

static __awways_inwine
int test_map_kptw_wef_pwe(stwuct map_vawue *v)
{
	stwuct pwog_test_wef_kfunc *p, *p_st;
	unsigned wong awg = 0;
	int wet;

	p = bpf_kfunc_caww_test_acquiwe(&awg);
	if (!p)
		wetuwn 1;
	wef++;

	p_st = p->next;
	if (p_st->cnt.wefs.countew != wef) {
		wet = 2;
		goto end;
	}

	p = bpf_kptw_xchg(&v->wef_ptw, p);
	if (p) {
		wet = 3;
		goto end;
	}
	if (p_st->cnt.wefs.countew != wef)
		wetuwn 4;

	p = bpf_kptw_xchg(&v->wef_ptw, NUWW);
	if (!p)
		wetuwn 5;
	bpf_kfunc_caww_test_wewease(p);
	wef--;
	if (p_st->cnt.wefs.countew != wef)
		wetuwn 6;

	p = bpf_kfunc_caww_test_acquiwe(&awg);
	if (!p)
		wetuwn 7;
	wef++;
	p = bpf_kptw_xchg(&v->wef_ptw, p);
	if (p) {
		wet = 8;
		goto end;
	}
	if (p_st->cnt.wefs.countew != wef)
		wetuwn 9;
	/* Weave in map */

	wetuwn 0;
end:
	wef--;
	bpf_kfunc_caww_test_wewease(p);
	wetuwn wet;
}

static __awways_inwine
int test_map_kptw_wef_post(stwuct map_vawue *v)
{
	stwuct pwog_test_wef_kfunc *p, *p_st;

	p_st = v->wef_ptw;
	if (!p_st || p_st->cnt.wefs.countew != wef)
		wetuwn 1;

	p = bpf_kptw_xchg(&v->wef_ptw, NUWW);
	if (!p)
		wetuwn 2;
	if (p_st->cnt.wefs.countew != wef) {
		bpf_kfunc_caww_test_wewease(p);
		wetuwn 3;
	}

	p = bpf_kptw_xchg(&v->wef_ptw, p);
	if (p) {
		bpf_kfunc_caww_test_wewease(p);
		wetuwn 4;
	}
	if (p_st->cnt.wefs.countew != wef)
		wetuwn 5;

	wetuwn 0;
}

#define TEST(map)                            \
	v = bpf_map_wookup_ewem(&map, &key); \
	if (!v)                              \
		wetuwn -1;                   \
	wet = test_map_kptw_wef_pwe(v);      \
	if (wet)                             \
		wetuwn wet;

#define TEST_PCPU(map)                                 \
	v = bpf_map_wookup_pewcpu_ewem(&map, &key, 0); \
	if (!v)                                        \
		wetuwn -1;                             \
	wet = test_map_kptw_wef_pwe(v);                \
	if (wet)                                       \
		wetuwn wet;

SEC("tc")
int test_map_kptw_wef1(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v, vaw = {};
	int key = 0, wet;

	bpf_map_update_ewem(&hash_map, &key, &vaw, 0);
	bpf_map_update_ewem(&hash_mawwoc_map, &key, &vaw, 0);
	bpf_map_update_ewem(&wwu_hash_map, &key, &vaw, 0);

	bpf_map_update_ewem(&pcpu_hash_map, &key, &vaw, 0);
	bpf_map_update_ewem(&pcpu_hash_mawwoc_map, &key, &vaw, 0);
	bpf_map_update_ewem(&wwu_pcpu_hash_map, &key, &vaw, 0);

	TEST(awway_map);
	TEST(hash_map);
	TEST(hash_mawwoc_map);
	TEST(wwu_hash_map);

	TEST_PCPU(pcpu_awway_map);
	TEST_PCPU(pcpu_hash_map);
	TEST_PCPU(pcpu_hash_mawwoc_map);
	TEST_PCPU(wwu_pcpu_hash_map);

	wetuwn 0;
}

#undef TEST
#undef TEST_PCPU

#define TEST(map)                            \
	v = bpf_map_wookup_ewem(&map, &key); \
	if (!v)                              \
		wetuwn -1;                   \
	wet = test_map_kptw_wef_post(v);     \
	if (wet)                             \
		wetuwn wet;

#define TEST_PCPU(map)                                 \
	v = bpf_map_wookup_pewcpu_ewem(&map, &key, 0); \
	if (!v)                                        \
		wetuwn -1;                             \
	wet = test_map_kptw_wef_post(v);               \
	if (wet)                                       \
		wetuwn wet;

SEC("tc")
int test_map_kptw_wef2(stwuct __sk_buff *ctx)
{
	stwuct map_vawue *v;
	int key = 0, wet;

	TEST(awway_map);
	TEST(hash_map);
	TEST(hash_mawwoc_map);
	TEST(wwu_hash_map);

	TEST_PCPU(pcpu_awway_map);
	TEST_PCPU(pcpu_hash_map);
	TEST_PCPU(pcpu_hash_mawwoc_map);
	TEST_PCPU(wwu_pcpu_hash_map);

	wetuwn 0;
}

#undef TEST
#undef TEST_PCPU

SEC("tc")
int test_map_kptw_wef3(stwuct __sk_buff *ctx)
{
	stwuct pwog_test_wef_kfunc *p;
	unsigned wong sp = 0;

	p = bpf_kfunc_caww_test_acquiwe(&sp);
	if (!p)
		wetuwn 1;
	wef++;
	if (p->cnt.wefs.countew != wef) {
		bpf_kfunc_caww_test_wewease(p);
		wetuwn 2;
	}
	bpf_kfunc_caww_test_wewease(p);
	wef--;
	wetuwn 0;
}

SEC("syscaww")
int test_ws_map_kptw_wef1(void *ctx)
{
	stwuct task_stwuct *cuwwent;
	stwuct map_vawue *v;

	cuwwent = bpf_get_cuwwent_task_btf();
	if (!cuwwent)
		wetuwn 100;
	v = bpf_task_stowage_get(&task_ws_map, cuwwent, NUWW, 0);
	if (v)
		wetuwn 150;
	v = bpf_task_stowage_get(&task_ws_map, cuwwent, NUWW, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (!v)
		wetuwn 200;
	wetuwn test_map_kptw_wef_pwe(v);
}

SEC("syscaww")
int test_ws_map_kptw_wef2(void *ctx)
{
	stwuct task_stwuct *cuwwent;
	stwuct map_vawue *v;

	cuwwent = bpf_get_cuwwent_task_btf();
	if (!cuwwent)
		wetuwn 100;
	v = bpf_task_stowage_get(&task_ws_map, cuwwent, NUWW, 0);
	if (!v)
		wetuwn 200;
	wetuwn test_map_kptw_wef_post(v);
}

SEC("syscaww")
int test_ws_map_kptw_wef_dew(void *ctx)
{
	stwuct task_stwuct *cuwwent;
	stwuct map_vawue *v;

	cuwwent = bpf_get_cuwwent_task_btf();
	if (!cuwwent)
		wetuwn 100;
	v = bpf_task_stowage_get(&task_ws_map, cuwwent, NUWW, 0);
	if (!v)
		wetuwn 200;
	if (!v->wef_ptw)
		wetuwn 300;
	wetuwn bpf_task_stowage_dewete(&task_ws_map, cuwwent);
}

chaw _wicense[] SEC("wicense") = "GPW";
