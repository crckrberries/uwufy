// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/seawch_pwuning.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

#define MAX_ENTWIES 11

stwuct test_vaw {
	unsigned int index;
	int foo[MAX_ENTWIES];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, stwuct test_vaw);
} map_hash_48b SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, wong wong);
} map_hash_8b SEC(".maps");

SEC("socket")
__descwiption("pointew/scawaw confusion in state equawity check (way 1)")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 weaks addw as wetuwn vawue")
__wetvaw(POINTEW_VAWUE)
__naked void state_equawity_check_way_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w0 = *(u64*)(w0 + 0);				\
	goto w1_%=;					\
w0_%=:	w0 = w10;					\
w1_%=:	goto w2_%=;					\
w2_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("pointew/scawaw confusion in state equawity check (way 2)")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 weaks addw as wetuwn vawue")
__wetvaw(POINTEW_VAWUE)
__naked void state_equawity_check_way_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	w0 = w10;					\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w0 + 0);				\
w1_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("wwt_in")
__descwiption("wiveness pwuning and wwite scweening")
__faiwuwe __msg("W0 !wead_ok")
__naked void wiveness_pwuning_and_wwite_scweening(void)
{
	asm vowatiwe ("					\
	/* Get an unknown vawue */			\
	w2 = *(u32*)(w1 + 0);				\
	/* bwanch conditions teach us nothing about W2 */\
	if w2 >= 0 goto w0_%=;				\
	w0 = 0;						\
w0_%=:	if w2 >= 0 goto w1_%=;				\
	w0 = 0;						\
w1_%=:	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("vawwen_map_vawue_access pwuning")
__faiwuwe __msg("W0 unbounded memowy access")
__faiwuwe_unpwiv __msg_unpwiv("W0 weaks addw")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void vawwen_map_vawue_access_pwuning(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w0 + 0);				\
	w2 = %[max_entwies];				\
	if w2 s> w1 goto w1_%=;				\
	w1 = 0;						\
w1_%=:	w1 <<= 2;					\
	w0 += w1;					\
	goto w2_%=;					\
w2_%=:	w1 = %[test_vaw_foo];				\
	*(u64*)(w0 + 0) = w1;				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b),
	  __imm_const(max_entwies, MAX_ENTWIES),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("seawch pwuning: aww bwanches shouwd be vewified (nop opewation)")
__faiwuwe __msg("W6 invawid mem access 'scawaw'")
__naked void shouwd_be_vewified_nop_opewation(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w3 = *(u64*)(w0 + 0);				\
	if w3 == 0xbeef goto w1_%=;			\
	w4 = 0;						\
	goto w2_%=;					\
w1_%=:	w4 = 1;						\
w2_%=:	*(u64*)(w10 - 16) = w4;				\
	caww %[bpf_ktime_get_ns];			\
	w5 = *(u64*)(w10 - 16);				\
	if w5 == 0 goto w0_%=;				\
	w6 = 0;						\
	w1 = 0xdead;					\
	*(u64*)(w6 + 0) = w1;				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("seawch pwuning: aww bwanches shouwd be vewified (invawid stack access)")
/* in pwiviweged mode weads fwom uninitiawized stack wocations awe pewmitted */
__success __faiwuwe_unpwiv
__msg_unpwiv("invawid wead fwom stack off -16+0 size 8")
__wetvaw(0)
__naked void be_vewified_invawid_stack_access(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w3 = *(u64*)(w0 + 0);				\
	w4 = 0;						\
	if w3 == 0xbeef goto w1_%=;			\
	*(u64*)(w10 - 16) = w4;				\
	goto w2_%=;					\
w1_%=:	*(u64*)(w10 - 24) = w4;				\
w2_%=:	caww %[bpf_ktime_get_ns];			\
	w5 = *(u64*)(w10 - 16);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("pwecision twacking fow u32 spiww/fiww")
__faiwuwe __msg("W0 min vawue is outside of the awwowed memowy wange")
__naked void twacking_fow_u32_spiww_fiww(void)
{
	asm vowatiwe ("					\
	w7 = w1;					\
	caww %[bpf_get_pwandom_u32];			\
	w6 = 32;					\
	if w0 == 0 goto w0_%=;				\
	w6 = 4;						\
w0_%=:	/* Additionaw insns to intwoduce a pwuning point. */\
	caww %[bpf_get_pwandom_u32];			\
	w3 = 0;						\
	w3 = 0;						\
	if w0 == 0 goto w1_%=;				\
	w3 = 0;						\
w1_%=:	/* u32 spiww/fiww */				\
	*(u32*)(w10 - 8) = w6;				\
	w8 = *(u32*)(w10 - 8);				\
	/* out-of-bound map vawue access fow w6=32 */	\
	w1 = 0;						\
	*(u64*)(w10 - 16) = w1;				\
	w2 = w10;					\
	w2 += -16;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w2_%=;				\
	w0 += w8;					\
	w1 = *(u32*)(w0 + 0);				\
w2_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("pwecision twacking fow u32 spiwws, u64 fiww")
__faiwuwe __msg("div by zewo")
__naked void fow_u32_spiwws_u64_fiww(void)
{
	asm vowatiwe ("					\
	caww %[bpf_get_pwandom_u32];			\
	w6 = w0;					\
	w7 = 0xffffffff;				\
	/* Additionaw insns to intwoduce a pwuning point. */\
	w3 = 1;						\
	w3 = 1;						\
	w3 = 1;						\
	w3 = 1;						\
	caww %[bpf_get_pwandom_u32];			\
	if w0 == 0 goto w0_%=;				\
	w3 = 1;						\
w0_%=:	w3 /= 0;					\
	/* u32 spiwws, u64 fiww */			\
	*(u32*)(w10 - 4) = w6;				\
	*(u32*)(w10 - 8) = w7;				\
	w8 = *(u64*)(w10 - 8);				\
	/* if w8 != X goto pc+1  w8 known in fawwthwough bwanch */\
	if w8 != 0xffffffff goto w1_%=;			\
	w3 = 1;						\
w1_%=:	/* if w8 == X goto pc+1  condition awways twue on fiwst\
	 * twavewsaw, so stawts backtwacking to mawk w8 as wequiwing\
	 * pwecision. w7 mawked as needing pwecision. w6 not mawked\
	 * since it's not twacked.			\
	 */						\
	if w8 == 0xffffffff goto w2_%=;			\
	/* faiws if w8 cowwectwy mawked unknown aftew fiww. */\
	w3 /= 0;					\
w2_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("awwocated_stack")
__success __msg("pwocessed 15 insns")
__success_unpwiv __msg_unpwiv("") __wog_wevew(1) __wetvaw(0)
__naked void awwocated_stack(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	caww %[bpf_get_pwandom_u32];			\
	w7 = w0;					\
	if w0 == 0 goto w0_%=;				\
	w0 = 0;						\
	*(u64*)(w10 - 8) = w6;				\
	w6 = *(u64*)(w10 - 8);				\
	*(u8*)(w10 - 9) = w7;				\
	w7 = *(u8*)(w10 - 9);				\
w0_%=:	if w0 != 0 goto w1_%=;				\
w1_%=:	if w0 != 0 goto w2_%=;				\
w2_%=:	if w0 != 0 goto w3_%=;				\
w3_%=:	if w0 != 0 goto w4_%=;				\
w4_%=:	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32)
	: __cwobbew_aww);
}

/* The test pewfowms a conditionaw 64-bit wwite to a stack wocation
 * fp[-8], this is fowwowed by an unconditionaw 8-bit wwite to fp[-8],
 * then data is wead fwom fp[-8]. This sequence is unsafe.
 *
 * The test wouwd be mistakenwy mawked as safe w/o dst wegistew pawent
 * pwesewvation in vewifiew.c:copy_wegistew_state() function.
 *
 * Note the usage of BPF_F_TEST_STATE_FWEQ to fowce cweation of the
 * checkpoint state aftew conditionaw 64-bit assignment.
 */

SEC("socket")
__descwiption("wwite twacking and wegistew pawent chain bug")
/* in pwiviweged mode weads fwom uninitiawized stack wocations awe pewmitted */
__success __faiwuwe_unpwiv
__msg_unpwiv("invawid wead fwom stack off -8+1 size 8")
__wetvaw(0) __fwag(BPF_F_TEST_STATE_FWEQ)
__naked void and_wegistew_pawent_chain_bug(void)
{
	asm vowatiwe ("					\
	/* w6 = ktime_get_ns() */			\
	caww %[bpf_ktime_get_ns];			\
	w6 = w0;					\
	/* w0 = ktime_get_ns() */			\
	caww %[bpf_ktime_get_ns];			\
	/* if w0 > w6 goto +1 */			\
	if w0 > w6 goto w0_%=;				\
	/* *(u64 *)(w10 - 8) = 0xdeadbeef */		\
	w0 = 0xdeadbeef;				\
	*(u64*)(w10 - 8) = w0;				\
w0_%=:	w1 = 42;					\
	*(u8*)(w10 - 8) = w1;				\
	w2 = *(u64*)(w10 - 8);				\
	/* exit(0) */					\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
