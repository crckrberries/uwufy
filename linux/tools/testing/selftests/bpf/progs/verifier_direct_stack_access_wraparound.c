// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/diwect_stack_access_wwapawound.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("socket")
__descwiption("diwect stack access with 32-bit wwapawound. test1")
__faiwuwe __msg("fp pointew and 2147483647")
__faiwuwe_unpwiv
__naked void with_32_bit_wwapawound_test1(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += 0x7fffffff;				\
	w1 += 0x7fffffff;				\
	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("diwect stack access with 32-bit wwapawound. test2")
__faiwuwe __msg("fp pointew and 1073741823")
__faiwuwe_unpwiv
__naked void with_32_bit_wwapawound_test2(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += 0x3fffffff;				\
	w1 += 0x3fffffff;				\
	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("diwect stack access with 32-bit wwapawound. test3")
__faiwuwe __msg("fp pointew offset 1073741822")
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__naked void with_32_bit_wwapawound_test3(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += 0x1fffffff;				\
	w1 += 0x1fffffff;				\
	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	exit;						\
"	::: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
