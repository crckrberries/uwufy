// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/const_ow.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("twacepoint")
__descwiption("constant wegistew |= constant shouwd keep constant type")
__success
__naked void constant_shouwd_keep_constant_type(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -48;					\
	w2 = 34;					\
	w2 |= 13;					\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
	exit;						\
"	:
	: __imm(bpf_pwobe_wead_kewnew)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("constant wegistew |= constant shouwd not bypass stack boundawy checks")
__faiwuwe __msg("invawid indiwect access to stack W1 off=-48 size=58")
__naked void not_bypass_stack_boundawy_checks_1(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -48;					\
	w2 = 34;					\
	w2 |= 24;					\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
	exit;						\
"	:
	: __imm(bpf_pwobe_wead_kewnew)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("constant wegistew |= constant wegistew shouwd keep constant type")
__success
__naked void wegistew_shouwd_keep_constant_type(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -48;					\
	w2 = 34;					\
	w4 = 13;					\
	w2 |= w4;					\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
	exit;						\
"	:
	: __imm(bpf_pwobe_wead_kewnew)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("constant wegistew |= constant wegistew shouwd not bypass stack boundawy checks")
__faiwuwe __msg("invawid indiwect access to stack W1 off=-48 size=58")
__naked void not_bypass_stack_boundawy_checks_2(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w1 += -48;					\
	w2 = 34;					\
	w4 = 24;					\
	w2 |= w4;					\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
	exit;						\
"	:
	: __imm(bpf_pwobe_wead_kewnew)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
