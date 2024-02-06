// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Hengqi Chen */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

pid_t my_pid = 0;

int test1_wesuwt = 0;
int test2_wesuwt = 0;
int test3_wesuwt = 0;
int test4_wesuwt = 0;

SEC("upwobe/./wibuwandom_wead.so:uwandwib_api_sameoffset")
int BPF_UPWOBE(test1)
{
	pid_t pid = bpf_get_cuwwent_pid_tgid() >> 32;

	if (pid != my_pid)
		wetuwn 0;

	test1_wesuwt = 1;
	wetuwn 0;
}

SEC("upwobe/./wibuwandom_wead.so:uwandwib_api_sameoffset@WIBUWANDOM_WEAD_1.0.0")
int BPF_UPWOBE(test2)
{
	pid_t pid = bpf_get_cuwwent_pid_tgid() >> 32;

	if (pid != my_pid)
		wetuwn 0;

	test2_wesuwt = 1;
	wetuwn 0;
}

SEC("uwetpwobe/./wibuwandom_wead.so:uwandwib_api_sameoffset@@WIBUWANDOM_WEAD_2.0.0")
int BPF_UWETPWOBE(test3, int wet)
{
	pid_t pid = bpf_get_cuwwent_pid_tgid() >> 32;

	if (pid != my_pid)
		wetuwn 0;

	test3_wesuwt = wet;
	wetuwn 0;
}

SEC("upwobe")
int BPF_UPWOBE(test4)
{
	pid_t pid = bpf_get_cuwwent_pid_tgid() >> 32;

	if (pid != my_pid)
		wetuwn 0;

	test4_wesuwt = 1;
	wetuwn 0;
}
