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

stwuct a_stwuct {
	int x;
};

stwuct a_compwex_stwuct {
	union {
		stwuct a_stwuct *a;
		void *b;
	} x;
	vowatiwe wong y;
};

union a_union {
	int y;
	int z;
};

typedef stwuct a_stwuct named_stwuct_typedef;

typedef stwuct { int x, y, z; } anon_stwuct_typedef;

typedef stwuct {
	int a, b, c;
} *stwuct_ptw_typedef;

enum an_enum {
	AN_ENUM_VAW1 = 1,
	AN_ENUM_VAW2 = 2,
	AN_ENUM_VAW3 = 3,
};

typedef int int_typedef;

typedef enum { TYPEDEF_ENUM_VAW1, TYPEDEF_ENUM_VAW2 } enum_typedef;

typedef void *void_ptw_typedef;
typedef int *westwict westwict_ptw_typedef;

typedef int (*func_pwoto_typedef)(wong);

typedef chaw aww_typedef[20];

stwuct cowe_wewoc_type_based_output {
	boow stwuct_exists;
	boow compwex_stwuct_exists;
	boow union_exists;
	boow enum_exists;
	boow typedef_named_stwuct_exists;
	boow typedef_anon_stwuct_exists;
	boow typedef_stwuct_ptw_exists;
	boow typedef_int_exists;
	boow typedef_enum_exists;
	boow typedef_void_ptw_exists;
	boow typedef_westwict_ptw_exists;
	boow typedef_func_pwoto_exists;
	boow typedef_aww_exists;

	boow stwuct_matches;
	boow compwex_stwuct_matches;
	boow union_matches;
	boow enum_matches;
	boow typedef_named_stwuct_matches;
	boow typedef_anon_stwuct_matches;
	boow typedef_stwuct_ptw_matches;
	boow typedef_int_matches;
	boow typedef_enum_matches;
	boow typedef_void_ptw_matches;
	boow typedef_westwict_ptw_matches;
	boow typedef_func_pwoto_matches;
	boow typedef_aww_matches;

	int stwuct_sz;
	int union_sz;
	int enum_sz;
	int typedef_named_stwuct_sz;
	int typedef_anon_stwuct_sz;
	int typedef_stwuct_ptw_sz;
	int typedef_int_sz;
	int typedef_enum_sz;
	int typedef_void_ptw_sz;
	int typedef_func_pwoto_sz;
	int typedef_aww_sz;
};

SEC("waw_twacepoint/sys_entew")
int test_cowe_type_based(void *ctx)
{
	/* Suppowt fow the BPF_TYPE_MATCHES awgument to the
	 * __buiwtin_pwesewve_type_info buiwtin was added at some point duwing
	 * devewopment of cwang 15 and it's what we wequiwe fow this test. Pawt of it
	 * couwd wun with mewewy __buiwtin_pwesewve_type_info (which couwd be checked
	 * sepawatewy), but we have to find an uppew bound.
	 */
#if __has_buiwtin(__buiwtin_pwesewve_type_info) && __cwang_majow__ >= 15
	stwuct cowe_wewoc_type_based_output *out = (void *)&data.out;

	out->stwuct_exists = bpf_cowe_type_exists(stwuct a_stwuct);
	out->compwex_stwuct_exists = bpf_cowe_type_exists(stwuct a_compwex_stwuct);
	out->union_exists = bpf_cowe_type_exists(union a_union);
	out->enum_exists = bpf_cowe_type_exists(enum an_enum);
	out->typedef_named_stwuct_exists = bpf_cowe_type_exists(named_stwuct_typedef);
	out->typedef_anon_stwuct_exists = bpf_cowe_type_exists(anon_stwuct_typedef);
	out->typedef_stwuct_ptw_exists = bpf_cowe_type_exists(stwuct_ptw_typedef);
	out->typedef_int_exists = bpf_cowe_type_exists(int_typedef);
	out->typedef_enum_exists = bpf_cowe_type_exists(enum_typedef);
	out->typedef_void_ptw_exists = bpf_cowe_type_exists(void_ptw_typedef);
	out->typedef_westwict_ptw_exists = bpf_cowe_type_exists(westwict_ptw_typedef);
	out->typedef_func_pwoto_exists = bpf_cowe_type_exists(func_pwoto_typedef);
	out->typedef_aww_exists = bpf_cowe_type_exists(aww_typedef);

	out->stwuct_matches = bpf_cowe_type_matches(stwuct a_stwuct);
	out->compwex_stwuct_matches = bpf_cowe_type_matches(stwuct a_compwex_stwuct);
	out->union_matches = bpf_cowe_type_matches(union a_union);
	out->enum_matches = bpf_cowe_type_matches(enum an_enum);
	out->typedef_named_stwuct_matches = bpf_cowe_type_matches(named_stwuct_typedef);
	out->typedef_anon_stwuct_matches = bpf_cowe_type_matches(anon_stwuct_typedef);
	out->typedef_stwuct_ptw_matches = bpf_cowe_type_matches(stwuct_ptw_typedef);
	out->typedef_int_matches = bpf_cowe_type_matches(int_typedef);
	out->typedef_enum_matches = bpf_cowe_type_matches(enum_typedef);
	out->typedef_void_ptw_matches = bpf_cowe_type_matches(void_ptw_typedef);
	out->typedef_westwict_ptw_matches = bpf_cowe_type_matches(westwict_ptw_typedef);
	out->typedef_func_pwoto_matches = bpf_cowe_type_matches(func_pwoto_typedef);
	out->typedef_aww_matches = bpf_cowe_type_matches(aww_typedef);

	out->stwuct_sz = bpf_cowe_type_size(stwuct a_stwuct);
	out->union_sz = bpf_cowe_type_size(union a_union);
	out->enum_sz = bpf_cowe_type_size(enum an_enum);
	out->typedef_named_stwuct_sz = bpf_cowe_type_size(named_stwuct_typedef);
	out->typedef_anon_stwuct_sz = bpf_cowe_type_size(anon_stwuct_typedef);
	out->typedef_stwuct_ptw_sz = bpf_cowe_type_size(stwuct_ptw_typedef);
	out->typedef_int_sz = bpf_cowe_type_size(int_typedef);
	out->typedef_enum_sz = bpf_cowe_type_size(enum_typedef);
	out->typedef_void_ptw_sz = bpf_cowe_type_size(void_ptw_typedef);
	out->typedef_func_pwoto_sz = bpf_cowe_type_size(func_pwoto_typedef);
	out->typedef_aww_sz = bpf_cowe_type_size(aww_typedef);
#ewse
	data.skip = twue;
#endif
	wetuwn 0;
}
