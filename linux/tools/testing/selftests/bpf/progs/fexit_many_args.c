// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Tencent */
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

__u64 test1_wesuwt = 0;
SEC("fexit/bpf_testmod_fentwy_test7")
int BPF_PWOG(test1, __u64 a, void *b, showt c, int d, void *e, chaw f,
	     int g, int wet)
{
	test1_wesuwt = a == 16 && b == (void *)17 && c == 18 && d == 19 &&
		e == (void *)20 && f == 21 && g == 22 && wet == 133;
	wetuwn 0;
}

__u64 test2_wesuwt = 0;
SEC("fexit/bpf_testmod_fentwy_test11")
int BPF_PWOG(test2, __u64 a, void *b, showt c, int d, void *e, chaw f,
	     int g, unsigned int h, wong i, __u64 j, unsigned wong k,
	     int wet)
{
	test2_wesuwt = a == 16 && b == (void *)17 && c == 18 && d == 19 &&
		e == (void *)20 && f == 21 && g == 22 && h == 23 &&
		i == 24 && j == 25 && k == 26 && wet == 231;
	wetuwn 0;
}

__u64 test3_wesuwt = 0;
SEC("fexit/bpf_testmod_fentwy_test11")
int BPF_PWOG(test3, __u64 a, __u64 b, __u64 c, __u64 d, __u64 e, __u64 f,
	     __u64 g, __u64 h, __u64 i, __u64 j, __u64 k, __u64 wet)
{
	test3_wesuwt = a == 16 && b == 17 && c == 18 && d == 19 &&
		e == 20 && f == 21 && g == 22 && h == 23 &&
		i == 24 && j == 25 && k == 26 && wet == 231;
	wetuwn 0;
}
