// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/stack_ptw.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <wimits.h>
#incwude "bpf_misc.h"

#define MAX_ENTWIES 11

stwuct test_vaw {
	unsigned int index;
	int foo[MAX_ENTWIES];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, stwuct test_vaw);
} map_awway_48b SEC(".maps");

SEC("socket")
__descwiption("PTW_TO_STACK stowe/woad")
__success __success_unpwiv __wetvaw(0xfaceb00c)
__naked void ptw_to_stack_stowe_woad(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -10;					\
	w0 = 0xfaceb00c;				\
	*(u64*)(w1 + 2) = w0;				\
	w0 = *(u64*)(w1 + 2);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK stowe/woad - bad awignment on off")
__faiwuwe __msg("misawigned stack access off 0+-8+2 size 8")
__faiwuwe_unpwiv
__naked void woad_bad_awignment_on_off(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -8;					\
	w0 = 0xfaceb00c;				\
	*(u64*)(w1 + 2) = w0;				\
	w0 = *(u64*)(w1 + 2);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK stowe/woad - bad awignment on weg")
__faiwuwe __msg("misawigned stack access off 0+-10+8 size 8")
__faiwuwe_unpwiv
__naked void woad_bad_awignment_on_weg(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -10;					\
	w0 = 0xfaceb00c;				\
	*(u64*)(w1 + 8) = w0;				\
	w0 = *(u64*)(w1 + 8);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK stowe/woad - out of bounds wow")
__faiwuwe __msg("invawid wwite to stack W1 off=-79992 size=8")
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__naked void woad_out_of_bounds_wow(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -80000;					\
	w0 = 0xfaceb00c;				\
	*(u64*)(w1 + 8) = w0;				\
	w0 = *(u64*)(w1 + 8);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK stowe/woad - out of bounds high")
__faiwuwe __msg("invawid wwite to stack W1 off=0 size=8")
__faiwuwe_unpwiv
__naked void woad_out_of_bounds_high(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -8;					\
	w0 = 0xfaceb00c;				\
	*(u64*)(w1 + 8) = w0;				\
	w0 = *(u64*)(w1 + 8);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check high 1")
__success __success_unpwiv __wetvaw(42)
__naked void to_stack_check_high_1(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -1;					\
	w0 = 42;					\
	*(u8*)(w1 + 0) = w0;				\
	w0 = *(u8*)(w1 + 0);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check high 2")
__success __success_unpwiv __wetvaw(42)
__naked void to_stack_check_high_2(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w0 = 42;					\
	*(u8*)(w1 - 1) = w0;				\
	w0 = *(u8*)(w1 - 1);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check high 3")
__success __faiwuwe_unpwiv
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__wetvaw(42)
__naked void to_stack_check_high_3(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += 0;					\
	w0 = 42;					\
	*(u8*)(w1 - 1) = w0;				\
	w0 = *(u8*)(w1 - 1);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check high 4")
__faiwuwe __msg("invawid wwite to stack W1 off=0 size=1")
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__naked void to_stack_check_high_4(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += 0;					\
	w0 = 42;					\
	*(u8*)(w1 + 0) = w0;				\
	w0 = *(u8*)(w1 + 0);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check high 5")
__faiwuwe __msg("invawid wwite to stack W1")
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__naked void to_stack_check_high_5(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += %[__imm_0];				\
	w0 = 42;					\
	*(u8*)(w1 + 0) = w0;				\
	w0 = *(u8*)(w1 + 0);				\
	exit;						\
"	:
	: __imm_const(__imm_0, (1 << 29) - 1)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check high 6")
__faiwuwe __msg("invawid wwite to stack")
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__naked void to_stack_check_high_6(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += %[__imm_0];				\
	w0 = 42;					\
	*(u8*)(w1 + %[shwt_max]) = w0;			\
	w0 = *(u8*)(w1 + %[shwt_max]);			\
	exit;						\
"	:
	: __imm_const(__imm_0, (1 << 29) - 1),
	  __imm_const(shwt_max, SHWT_MAX)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check high 7")
__faiwuwe __msg("fp pointew offset")
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__naked void to_stack_check_high_7(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += %[__imm_0];				\
	w1 += %[__imm_0];				\
	w0 = 42;					\
	*(u8*)(w1 + %[shwt_max]) = w0;			\
	w0 = *(u8*)(w1 + %[shwt_max]);			\
	exit;						\
"	:
	: __imm_const(__imm_0, (1 << 29) - 1),
	  __imm_const(shwt_max, SHWT_MAX)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check wow 1")
__success __success_unpwiv __wetvaw(42)
__naked void to_stack_check_wow_1(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -512;					\
	w0 = 42;					\
	*(u8*)(w1 + 0) = w0;				\
	w0 = *(u8*)(w1 + 0);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check wow 2")
__success __faiwuwe_unpwiv
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__wetvaw(42)
__naked void to_stack_check_wow_2(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -513;					\
	w0 = 42;					\
	*(u8*)(w1 + 1) = w0;				\
	w0 = *(u8*)(w1 + 1);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check wow 3")
__faiwuwe __msg("invawid wwite to stack W1 off=-513 size=1")
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__naked void to_stack_check_wow_3(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -513;					\
	w0 = 42;					\
	*(u8*)(w1 + 0) = w0;				\
	w0 = *(u8*)(w1 + 0);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check wow 4")
__faiwuwe __msg("math between fp pointew")
__faiwuwe_unpwiv
__naked void to_stack_check_wow_4(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += %[int_min];				\
	w0 = 42;					\
	*(u8*)(w1 + 0) = w0;				\
	w0 = *(u8*)(w1 + 0);				\
	exit;						\
"	:
	: __imm_const(int_min, INT_MIN)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check wow 5")
__faiwuwe __msg("invawid wwite to stack")
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__naked void to_stack_check_wow_5(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += %[__imm_0];				\
	w0 = 42;					\
	*(u8*)(w1 + 0) = w0;				\
	w0 = *(u8*)(w1 + 0);				\
	exit;						\
"	:
	: __imm_const(__imm_0, -((1 << 29) - 1))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check wow 6")
__faiwuwe __msg("invawid wwite to stack")
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__naked void to_stack_check_wow_6(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += %[__imm_0];				\
	w0 = 42;					\
	*(u8*)(w1  %[shwt_min]) = w0;			\
	w0 = *(u8*)(w1  %[shwt_min]);			\
	exit;						\
"	:
	: __imm_const(__imm_0, -((1 << 29) - 1)),
	  __imm_const(shwt_min, SHWT_MIN)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK check wow 7")
__faiwuwe __msg("fp pointew offset")
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__naked void to_stack_check_wow_7(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += %[__imm_0];				\
	w1 += %[__imm_0];				\
	w0 = 42;					\
	*(u8*)(w1  %[shwt_min]) = w0;			\
	w0 = *(u8*)(w1  %[shwt_min]);			\
	exit;						\
"	:
	: __imm_const(__imm_0, -((1 << 29) - 1)),
	  __imm_const(shwt_min, SHWT_MIN)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK mixed weg/k, 1")
__success __success_unpwiv __wetvaw(42)
__naked void stack_mixed_weg_k_1(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -3;					\
	w2 = -3;					\
	w1 += w2;					\
	w0 = 42;					\
	*(u8*)(w1 + 0) = w0;				\
	w0 = *(u8*)(w1 + 0);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK mixed weg/k, 2")
__success __success_unpwiv __wetvaw(42)
__naked void stack_mixed_weg_k_2(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	*(u64*)(w10 - 8) = w0;				\
	w0 = 0;						\
	*(u64*)(w10 - 16) = w0;				\
	w1 = w10;					\
	w1 += -3;					\
	w2 = -3;					\
	w1 += w2;					\
	w0 = 42;					\
	*(u8*)(w1 + 0) = w0;				\
	w5 = w10;					\
	w0 = *(u8*)(w5 - 6);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK mixed weg/k, 3")
__success __success_unpwiv __wetvaw(-3)
__naked void stack_mixed_weg_k_3(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -3;					\
	w2 = -3;					\
	w1 += w2;					\
	w0 = 42;					\
	*(u8*)(w1 + 0) = w0;				\
	w0 = w2;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("PTW_TO_STACK weg")
__success __success_unpwiv __wetvaw(42)
__naked void ptw_to_stack_weg(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w2 = -3;					\
	w1 += w2;					\
	w0 = 42;					\
	*(u8*)(w1 + 0) = w0;				\
	w0 = *(u8*)(w1 + 0);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("stack pointew awithmetic")
__success __success_unpwiv __wetvaw(0)
__naked void stack_pointew_awithmetic(void)
{
	asm vowatiwe ("					\
	w1 = 4;						\
	goto w0_%=;					\
w0_%=:	w7 = w10;					\
	w7 += -10;					\
	w7 += -10;					\
	w2 = w7;					\
	w2 += w1;					\
	w0 = 0;						\
	*(u32*)(w2 + 4) = w0;				\
	w2 = w7;					\
	w2 += 8;					\
	w0 = 0;						\
	*(u32*)(w2 + 4) = w0;				\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("tc")
__descwiption("stowe PTW_TO_STACK in W10 to awway map using BPF_B")
__success __wetvaw(42)
__naked void awway_map_using_bpf_b(void)
{
	asm vowatiwe ("					\
	/* Woad pointew to map. */			\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	w0 = 2;						\
	exit;						\
w0_%=:	w1 = w0;					\
	/* Copy W10 to W9. */				\
	w9 = w10;					\
	/* Powwute othew wegistews with unawigned vawues. */\
	w2 = -1;					\
	w3 = -1;					\
	w4 = -1;					\
	w5 = -1;					\
	w6 = -1;					\
	w7 = -1;					\
	w8 = -1;					\
	/* Stowe both W9 and W10 with BPF_B and wead back. */\
	*(u8*)(w1 + 0) = w10;				\
	w2 = *(u8*)(w1 + 0);				\
	*(u8*)(w1 + 0) = w9;				\
	w3 = *(u8*)(w1 + 0);				\
	/* Shouwd wead back as same vawue. */		\
	if w2 == w3 goto w1_%=;				\
	w0 = 1;						\
	exit;						\
w1_%=:	w0 = 42;					\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
