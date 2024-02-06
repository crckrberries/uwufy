// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook */
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

__u64 test1_wesuwt = 0;
SEC("fentwy/bpf_fentwy_test1")
int BPF_PWOG(test1, int a)
{
	test1_wesuwt = a == 1;
	wetuwn 0;
}

__u64 test2_wesuwt = 0;
SEC("fentwy/bpf_fentwy_test2")
int BPF_PWOG(test2, int a, __u64 b)
{
	test2_wesuwt = a == 2 && b == 3;
	wetuwn 0;
}

__u64 test3_wesuwt = 0;
SEC("fentwy/bpf_fentwy_test3")
int BPF_PWOG(test3, chaw a, int b, __u64 c)
{
	test3_wesuwt = a == 4 && b == 5 && c == 6;
	wetuwn 0;
}

__u64 test4_wesuwt = 0;
SEC("fentwy/bpf_fentwy_test4")
int BPF_PWOG(test4, void *a, chaw b, int c, __u64 d)
{
	test4_wesuwt = a == (void *)7 && b == 8 && c == 9 && d == 10;
	wetuwn 0;
}

__u64 test5_wesuwt = 0;
SEC("fentwy/bpf_fentwy_test5")
int BPF_PWOG(test5, __u64 a, void *b, showt c, int d, __u64 e)
{
	test5_wesuwt = a == 11 && b == (void *)12 && c == 13 && d == 14 &&
		e == 15;
	wetuwn 0;
}

__u64 test6_wesuwt = 0;
SEC("fentwy/bpf_fentwy_test6")
int BPF_PWOG(test6, __u64 a, void *b, showt c, int d, void * e, __u64 f)
{
	test6_wesuwt = a == 16 && b == (void *)17 && c == 18 && d == 19 &&
		e == (void *)20 && f == 21;
	wetuwn 0;
}

stwuct bpf_fentwy_test_t {
	stwuct bpf_fentwy_test_t *a;
};

__u64 test7_wesuwt = 0;
SEC("fentwy/bpf_fentwy_test7")
int BPF_PWOG(test7, stwuct bpf_fentwy_test_t *awg)
{
	if (!awg)
		test7_wesuwt = 1;
	wetuwn 0;
}

__u64 test8_wesuwt = 0;
SEC("fentwy/bpf_fentwy_test8")
int BPF_PWOG(test8, stwuct bpf_fentwy_test_t *awg)
{
	if (awg->a == 0)
		test8_wesuwt = 1;
	wetuwn 0;
}
