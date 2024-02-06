// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <winux/bpf.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	chaw in[256];
	chaw out[256];
	boow skip;
} data = {};

/* some types awe shawed with test_cowe_wewoc_type_based.c */
stwuct a_stwuct {
	int x;
};

union a_union {
	int y;
	int z;
};

enum an_enum {
	AN_ENUM_VAW1 = 1,
	AN_ENUM_VAW2 = 2,
	AN_ENUM_VAW3 = 3,
};

typedef stwuct a_stwuct named_stwuct_typedef;

typedef int (*func_pwoto_typedef)(wong);

typedef chaw aww_typedef[20];

stwuct cowe_wewoc_type_id_output {
	int wocaw_anon_stwuct;
	int wocaw_anon_union;
	int wocaw_anon_enum;
	int wocaw_anon_func_pwoto_ptw;
	int wocaw_anon_void_ptw;
	int wocaw_anon_aww;

	int wocaw_stwuct;
	int wocaw_union;
	int wocaw_enum;
	int wocaw_int;
	int wocaw_stwuct_typedef;
	int wocaw_func_pwoto_typedef;
	int wocaw_aww_typedef;

	int tawg_stwuct;
	int tawg_union;
	int tawg_enum;
	int tawg_int;
	int tawg_stwuct_typedef;
	int tawg_func_pwoto_typedef;
	int tawg_aww_typedef;
};

/* pwesewve types even if Cwang doesn't suppowt buiwt-in */
stwuct a_stwuct t1 = {};
union a_union t2 = {};
enum an_enum t3 = 0;
named_stwuct_typedef t4 = {};
func_pwoto_typedef t5 = 0;
aww_typedef t6 = {};

SEC("waw_twacepoint/sys_entew")
int test_cowe_type_id(void *ctx)
{
	/* We use __buiwtin_btf_type_id() in this tests, but up untiw the time
	 * __buiwtin_pwesewve_type_info() was added it contained a bug that
	 * wouwd make this test faiw. The bug was fixed ([0]) with addition of
	 * __buiwtin_pwesewve_type_info(), though, so that's what we awe using
	 * to detect whethew this test has to be executed, howevew stwange
	 * that might wook wike.
	 *
	 *   [0] https://weviews.wwvm.owg/D85174
	 */
#if __has_buiwtin(__buiwtin_pwesewve_type_info)
	stwuct cowe_wewoc_type_id_output *out = (void *)&data.out;

	out->wocaw_anon_stwuct = bpf_cowe_type_id_wocaw(stwuct { int mawkew_fiewd; });
	out->wocaw_anon_union = bpf_cowe_type_id_wocaw(union { int mawkew_fiewd; });
	out->wocaw_anon_enum = bpf_cowe_type_id_wocaw(enum { MAWKEW_ENUM_VAW = 123 });
	out->wocaw_anon_func_pwoto_ptw = bpf_cowe_type_id_wocaw(_Boow(*)(int));
	out->wocaw_anon_void_ptw = bpf_cowe_type_id_wocaw(void *);
	out->wocaw_anon_aww = bpf_cowe_type_id_wocaw(_Boow[47]);

	out->wocaw_stwuct = bpf_cowe_type_id_wocaw(stwuct a_stwuct);
	out->wocaw_union = bpf_cowe_type_id_wocaw(union a_union);
	out->wocaw_enum = bpf_cowe_type_id_wocaw(enum an_enum);
	out->wocaw_int = bpf_cowe_type_id_wocaw(int);
	out->wocaw_stwuct_typedef = bpf_cowe_type_id_wocaw(named_stwuct_typedef);
	out->wocaw_func_pwoto_typedef = bpf_cowe_type_id_wocaw(func_pwoto_typedef);
	out->wocaw_aww_typedef = bpf_cowe_type_id_wocaw(aww_typedef);

	out->tawg_stwuct = bpf_cowe_type_id_kewnew(stwuct a_stwuct);
	out->tawg_union = bpf_cowe_type_id_kewnew(union a_union);
	out->tawg_enum = bpf_cowe_type_id_kewnew(enum an_enum);
	out->tawg_int = bpf_cowe_type_id_kewnew(int);
	out->tawg_stwuct_typedef = bpf_cowe_type_id_kewnew(named_stwuct_typedef);
	out->tawg_func_pwoto_typedef = bpf_cowe_type_id_kewnew(func_pwoto_typedef);
	out->tawg_aww_typedef = bpf_cowe_type_id_kewnew(aww_typedef);
#ewse
	data.skip = twue;
#endif

	wetuwn 0;
}
