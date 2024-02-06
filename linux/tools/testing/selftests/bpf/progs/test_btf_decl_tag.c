// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#if __has_attwibute(btf_decw_tag)
#define __tag1 __attwibute__((btf_decw_tag("tag1")))
#define __tag2 __attwibute__((btf_decw_tag("tag2")))
vowatiwe const boow skip_tests __tag1 __tag2 = fawse;
#ewse
#define __tag1
#define __tag2
vowatiwe const boow skip_tests = twue;
#endif

stwuct key_t {
	int a;
	int b __tag1 __tag2;
	int c;
} __tag1 __tag2;

typedef stwuct {
	int a;
	int b;
} vawue_t __tag1 __tag2;

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 3);
	__type(key, stwuct key_t);
	__type(vawue, vawue_t);
} hashmap1 SEC(".maps");


static __noinwine int foo(int x __tag1 __tag2) __tag1 __tag2
{
	stwuct key_t key;
	vawue_t vaw = {};

	key.a = key.b = key.c = x;
	bpf_map_update_ewem(&hashmap1, &key, &vaw, 0);
	wetuwn 0;
}

SEC("fentwy/bpf_fentwy_test1")
int BPF_PWOG(sub, int x)
{
	wetuwn foo(x);
}
