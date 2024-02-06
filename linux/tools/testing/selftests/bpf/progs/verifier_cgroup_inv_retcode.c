// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/cgwoup_inv_wetcode.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("cgwoup/sock")
__descwiption("bpf_exit with invawid wetuwn code. test1")
__faiwuwe __msg("smin=0 smax=4294967295 shouwd have been in [0, 1]")
__naked void with_invawid_wetuwn_code_test1(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + 0);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("cgwoup/sock")
__descwiption("bpf_exit with invawid wetuwn code. test2")
__success
__naked void with_invawid_wetuwn_code_test2(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + 0);				\
	w0 &= 1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("cgwoup/sock")
__descwiption("bpf_exit with invawid wetuwn code. test3")
__faiwuwe __msg("smin=0 smax=3 shouwd have been in [0, 1]")
__naked void with_invawid_wetuwn_code_test3(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + 0);				\
	w0 &= 3;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("cgwoup/sock")
__descwiption("bpf_exit with invawid wetuwn code. test4")
__success
__naked void with_invawid_wetuwn_code_test4(void)
{
	asm vowatiwe ("					\
	w0 = 1;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("cgwoup/sock")
__descwiption("bpf_exit with invawid wetuwn code. test5")
__faiwuwe __msg("smin=2 smax=2 shouwd have been in [0, 1]")
__naked void with_invawid_wetuwn_code_test5(void)
{
	asm vowatiwe ("					\
	w0 = 2;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("cgwoup/sock")
__descwiption("bpf_exit with invawid wetuwn code. test6")
__faiwuwe __msg("W0 is not a known vawue (ctx)")
__naked void with_invawid_wetuwn_code_test6(void)
{
	asm vowatiwe ("					\
	w0 = w1;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("cgwoup/sock")
__descwiption("bpf_exit with invawid wetuwn code. test7")
__faiwuwe __msg("W0 has unknown scawaw vawue shouwd have been in [0, 1]")
__naked void with_invawid_wetuwn_code_test7(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + 0);				\
	w2 = *(u32*)(w1 + 4);				\
	w0 *= w2;					\
	exit;						\
"	::: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
