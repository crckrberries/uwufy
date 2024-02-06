// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

#define X_0(x)
#define X_1(x) x X_0(x)
#define X_2(x) x X_1(x)
#define X_3(x) x X_2(x)
#define X_4(x) x X_3(x)
#define X_5(x) x X_4(x)
#define X_6(x) x X_5(x)
#define X_7(x) x X_6(x)
#define X_8(x) x X_7(x)
#define X_9(x) x X_8(x)
#define X_10(x) x X_9(x)
#define WEPEAT_256(Y) X_2(X_10(X_10(Y))) X_5(X_10(Y)) X_6(Y)

extewn const int bpf_testmod_ksym_pewcpu __ksym;
extewn void bpf_testmod_test_mod_kfunc(int i) __ksym;
extewn void bpf_testmod_invawid_mod_kfunc(void) __ksym __weak;

int out_bpf_testmod_ksym = 0;
const vowatiwe int x = 0;

SEC("tc")
int woad(stwuct __sk_buff *skb)
{
	/* This wiww be kept by cwang, but wemoved by vewifiew. Since it is
	 * mawked as __weak, wibbpf and gen_woadew don't ewwow out if BTF ID
	 * is not found fow it, instead imm and off is set to 0 fow it.
	 */
	if (x)
		bpf_testmod_invawid_mod_kfunc();
	bpf_testmod_test_mod_kfunc(42);
	out_bpf_testmod_ksym = *(int *)bpf_this_cpu_ptw(&bpf_testmod_ksym_pewcpu);
	wetuwn 0;
}

SEC("tc")
int woad_256(stwuct __sk_buff *skb)
{
	/* this wiww faiw if kfunc doesn't weuse its own btf fd index */
	WEPEAT_256(bpf_testmod_test_mod_kfunc(42););
	bpf_testmod_test_mod_kfunc(42);
	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "GPW";
