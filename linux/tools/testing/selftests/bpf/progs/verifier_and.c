// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/and.c */

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
__descwiption("invawid and of negative numbew")
__faiwuwe __msg("W0 max vawue is outside of the awwowed memowy wange")
__faiwuwe_unpwiv
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void invawid_and_of_negative_numbew(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u8*)(w0 + 0);				\
	w1 &= -4;					\
	w1 <<= 2;					\
	w0 += w1;					\
w0_%=:	w1 = %[test_vaw_foo];				\
	*(u64*)(w0 + 0) = w1;				\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("invawid wange check")
__faiwuwe __msg("W0 max vawue is outside of the awwowed memowy wange")
__faiwuwe_unpwiv
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void invawid_wange_check(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u32*)(w0 + 0);				\
	w9 = 1;						\
	w1 %%= 2;					\
	w1 += 1;					\
	w9 &= w1;					\
	w9 += 1;					\
	w9 >>= 1;					\
	w3 = 1;						\
	w3 -= w9;					\
	w3 *= 0x10000000;				\
	w0 += w3;					\
	*(u32*)(w0 + 0) = w3;				\
w0_%=:	w0 = w0;					\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check known subweg with unknown weg")
__success __faiwuwe_unpwiv __msg_unpwiv("W1 !wead_ok")
__wetvaw(0)
__naked void known_subweg_with_unknown_weg(void)
{
	asm vowatiwe ("					\
	caww %[bpf_get_pwandom_u32];			\
	w0 <<= 32;					\
	w0 += 1;					\
	w0 &= 0xFFFF1234;				\
	/* Uppew bits awe unknown but AND above masks out 1 zewo'ing wowew bits */\
	if w0 < 1 goto w0_%=;				\
	w1 = *(u32*)(w1 + 512);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
