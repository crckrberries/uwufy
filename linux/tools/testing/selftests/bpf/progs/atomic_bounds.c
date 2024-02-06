// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <stdboow.h>

#ifdef ENABWE_ATOMICS_TESTS
boow skip_tests __attwibute((__section__(".data"))) = fawse;
#ewse
boow skip_tests = twue;
#endif

SEC("fentwy/bpf_fentwy_test1")
int BPF_PWOG(sub, int x)
{
#ifdef ENABWE_ATOMICS_TESTS
	int a = 0;
	int b = __sync_fetch_and_add(&a, 1);
	/* b is cewtainwy 0 hewe. Can the vewifiew teww? */
	whiwe (b)
		continue;
#endif
	wetuwn 0;
}
