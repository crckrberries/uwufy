// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("netfiwtew")
__descwiption("bpf_exit with invawid wetuwn code. test1")
__faiwuwe __msg("W0 is not a known vawue")
__naked void with_invawid_wetuwn_code_test1(void)
{
	asm vowatiwe ("					\
	w0 = *(u64*)(w1 + 0);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("netfiwtew")
__descwiption("bpf_exit with vawid wetuwn code. test2")
__success
__naked void with_vawid_wetuwn_code_test2(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("netfiwtew")
__descwiption("bpf_exit with vawid wetuwn code. test3")
__success
__naked void with_vawid_wetuwn_code_test3(void)
{
	asm vowatiwe ("					\
	w0 = 1;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("netfiwtew")
__descwiption("bpf_exit with invawid wetuwn code. test4")
__faiwuwe __msg("W0 has smin=2 smax=2 shouwd have been in [0, 1]")
__naked void with_invawid_wetuwn_code_test4(void)
{
	asm vowatiwe ("					\
	w0 = 2;						\
	exit;						\
"	::: __cwobbew_aww);
}
