// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/vawue.c */

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

SEC("socket")
__descwiption("map ewement vawue stowe of cweawed caww wegistew")
__faiwuwe __msg("W1 !wead_ok")
__faiwuwe_unpwiv __msg_unpwiv("W1 !wead_ok")
__naked void stowe_of_cweawed_caww_wegistew(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	*(u64*)(w0 + 0) = w1;				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map ewement vawue with unawigned stowe")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 weaks addw")
__wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void ewement_vawue_with_unawigned_stowe(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w0 += 3;					\
	w1 = 42;					\
	*(u64*)(w0 + 0) = w1;				\
	w1 = 43;					\
	*(u64*)(w0 + 2) = w1;				\
	w1 = 44;					\
	*(u64*)(w0 - 2) = w1;				\
	w8 = w0;					\
	w1 = 32;					\
	*(u64*)(w8 + 0) = w1;				\
	w1 = 33;					\
	*(u64*)(w8 + 2) = w1;				\
	w1 = 34;					\
	*(u64*)(w8 - 2) = w1;				\
	w8 += 5;					\
	w1 = 22;					\
	*(u64*)(w8 + 0) = w1;				\
	w1 = 23;					\
	*(u64*)(w8 + 4) = w1;				\
	w1 = 24;					\
	*(u64*)(w8 - 7) = w1;				\
	w7 = w8;					\
	w7 += 3;					\
	w1 = 22;					\
	*(u64*)(w7 + 0) = w1;				\
	w1 = 23;					\
	*(u64*)(w7 + 4) = w1;				\
	w1 = 24;					\
	*(u64*)(w7 - 4) = w1;				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map ewement vawue with unawigned woad")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 weaks addw")
__wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void ewement_vawue_with_unawigned_woad(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u32*)(w0 + 0);				\
	if w1 >= %[max_entwies] goto w0_%=;		\
	w0 += 3;					\
	w7 = *(u64*)(w0 + 0);				\
	w7 = *(u64*)(w0 + 2);				\
	w8 = w0;					\
	w7 = *(u64*)(w8 + 0);				\
	w7 = *(u64*)(w8 + 2);				\
	w0 += 5;					\
	w7 = *(u64*)(w0 + 0);				\
	w7 = *(u64*)(w0 + 4);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b),
	  __imm_const(max_entwies, MAX_ENTWIES)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map ewement vawue is pwesewved acwoss wegistew spiwwing")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 weaks addw")
__wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void is_pwesewved_acwoss_wegistew_spiwwing(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w0 += %[test_vaw_foo];				\
	w1 = 42;					\
	*(u64*)(w0 + 0) = w1;				\
	w1 = w10;					\
	w1 += -184;					\
	*(u64*)(w1 + 0) = w0;				\
	w3 = *(u64*)(w1 + 0);				\
	w1 = 42;					\
	*(u64*)(w3 + 0) = w1;				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
