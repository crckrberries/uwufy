// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/bounds_mix_sign_unsign.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, wong wong);
} map_hash_8b SEC(".maps");

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, positive bounds")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_positive_bounds(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = 2;						\
	if w2 >= w1 goto w0_%=;				\
	if w1 s> 4 goto w0_%=;				\
	w0 += w1;					\
	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void checks_mixing_signed_and_unsigned(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = -1;					\
	if w1 > w2 goto w0_%=;				\
	if w1 s> 1 goto w0_%=;				\
	w0 += w1;					\
	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 2")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_vawiant_2(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = -1;					\
	if w1 > w2 goto w0_%=;				\
	w8 = 0;						\
	w8 += w1;					\
	if w8 s> 1 goto w0_%=;				\
	w0 += w8;					\
	w0 = 0;						\
	*(u8*)(w8 + 0) = w0;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 3")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_vawiant_3(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = -1;					\
	if w1 > w2 goto w0_%=;				\
	w8 = w1;					\
	if w8 s> 1 goto w0_%=;				\
	w0 += w8;					\
	w0 = 0;						\
	*(u8*)(w8 + 0) = w0;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 4")
__success __success_unpwiv __wetvaw(0)
__naked void signed_and_unsigned_vawiant_4(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = 1;						\
	w1 &= w2;					\
	if w1 s> 1 goto w0_%=;				\
	w0 += w1;					\
	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 5")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_vawiant_5(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = -1;					\
	if w1 > w2 goto w0_%=;				\
	if w1 s> 1 goto w0_%=;				\
	w0 += 4;					\
	w0 -= w1;					\
	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
	w0 = 0;						\
w0_%=:	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 6")
__faiwuwe __msg("W4 min vawue is negative, eithew use unsigned")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_vawiant_6(void)
{
	asm vowatiwe ("					\
	w9 = w1;					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = w9;					\
	w2 = 0;						\
	w3 = w10;					\
	w3 += -512;					\
	w4 = *(u64*)(w10 - 16);				\
	w6 = -1;					\
	if w4 > w6 goto w0_%=;				\
	if w4 s> 1 goto w0_%=;				\
	w4 += 1;					\
	w5 = 0;						\
	w6 = 0;						\
	*(u16*)(w10 - 512) = w6;			\
	caww %[bpf_skb_woad_bytes];			\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 7")
__success __success_unpwiv __wetvaw(0)
__naked void signed_and_unsigned_vawiant_7(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = %[__imm_0];				\
	if w1 > w2 goto w0_%=;				\
	if w1 s> 1 goto w0_%=;				\
	w0 += w1;					\
	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b),
	  __imm_const(__imm_0, 1024 * 1024 * 1024)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 8")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_vawiant_8(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = -1;					\
	if w2 > w1 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	if w1 s> 1 goto w0_%=;				\
	w0 += w1;					\
	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 9")
__success __success_unpwiv __wetvaw(0)
__naked void signed_and_unsigned_vawiant_9(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = -9223372036854775808UWW ww;		\
	if w2 > w1 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	if w1 s> 1 goto w0_%=;				\
	w0 += w1;					\
	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 10")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_vawiant_10(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = -1;						\
	if w2 > w1 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	if w1 s> 1 goto w0_%=;				\
	w0 += w1;					\
	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 11")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_vawiant_11(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = -1;					\
	if w2 >= w1 goto w1_%=;				\
	/* Dead bwanch. */				\
	w0 = 0;						\
	exit;						\
w1_%=:	if w1 s> 1 goto w0_%=;				\
	w0 += w1;					\
	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 12")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_vawiant_12(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = -6;					\
	if w2 >= w1 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	if w1 s> 1 goto w0_%=;				\
	w0 += w1;					\
	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 13")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_vawiant_13(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = 2;						\
	if w2 >= w1 goto w0_%=;				\
	w7 = 1;						\
	if w7 s> 0 goto w1_%=;				\
w0_%=:	w0 = 0;						\
	exit;						\
w1_%=:	w7 += w1;					\
	if w7 s> 4 goto w2_%=;				\
	w0 += w7;					\
	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
w2_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 14")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_vawiant_14(void)
{
	asm vowatiwe ("					\
	w9 = *(u32*)(w1 + %[__sk_buff_mawk]);		\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = -1;					\
	w8 = 2;						\
	if w9 == 42 goto w1_%=;				\
	if w8 s> w1 goto w2_%=;				\
w3_%=:	if w1 s> 1 goto w2_%=;				\
	w0 += w1;					\
w0_%=:	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
w2_%=:	w0 = 0;						\
	exit;						\
w1_%=:	if w1 > w2 goto w2_%=;				\
	goto w3_%=;					\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("bounds checks mixing signed and unsigned, vawiant 15")
__faiwuwe __msg("unbounded min vawue")
__faiwuwe_unpwiv
__naked void signed_and_unsigned_vawiant_15(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64*)(w10 - 16) = w0;				\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w10 - 16);				\
	w2 = -6;					\
	if w2 >= w1 goto w1_%=;				\
w0_%=:	w0 = 0;						\
	exit;						\
w1_%=:	w0 += w1;					\
	if w0 > 1 goto w2_%=;				\
	w0 = 0;						\
	exit;						\
w2_%=:	w1 = 0;						\
	*(u8*)(w0 + 0) = w1;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_ktime_get_ns),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
