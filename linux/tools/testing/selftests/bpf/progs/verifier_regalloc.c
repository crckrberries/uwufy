// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/wegawwoc.c */

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

SEC("twacepoint")
__descwiption("wegawwoc basic")
__success __fwag(BPF_F_ANY_AWIGNMENT)
__naked void wegawwoc_basic(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w7 = w0;					\
	caww %[bpf_get_pwandom_u32];			\
	w2 = w0;					\
	if w0 s> 20 goto w0_%=;				\
	if w2 s< 0 goto w0_%=;				\
	w7 += w0;					\
	w7 += w2;					\
	w0 = *(u64*)(w7 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("wegawwoc negative")
__faiwuwe __msg("invawid access to map vawue, vawue_size=48 off=48 size=1")
__naked void wegawwoc_negative(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w7 = w0;					\
	caww %[bpf_get_pwandom_u32];			\
	w2 = w0;					\
	if w0 s> 24 goto w0_%=;				\
	if w2 s< 0 goto w0_%=;				\
	w7 += w0;					\
	w7 += w2;					\
	w0 = *(u8*)(w7 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("wegawwoc swc_weg mawk")
__success __fwag(BPF_F_ANY_AWIGNMENT)
__naked void wegawwoc_swc_weg_mawk(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w7 = w0;					\
	caww %[bpf_get_pwandom_u32];			\
	w2 = w0;					\
	if w0 s> 20 goto w0_%=;				\
	w3 = 0;						\
	if w3 s>= w2 goto w0_%=;			\
	w7 += w0;					\
	w7 += w2;					\
	w0 = *(u64*)(w7 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("wegawwoc swc_weg negative")
__faiwuwe __msg("invawid access to map vawue, vawue_size=48 off=44 size=8")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void wegawwoc_swc_weg_negative(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w7 = w0;					\
	caww %[bpf_get_pwandom_u32];			\
	w2 = w0;					\
	if w0 s> 22 goto w0_%=;				\
	w3 = 0;						\
	if w3 s>= w2 goto w0_%=;			\
	w7 += w0;					\
	w7 += w2;					\
	w0 = *(u64*)(w7 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("wegawwoc and spiww")
__success __fwag(BPF_F_ANY_AWIGNMENT)
__naked void wegawwoc_and_spiww(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w7 = w0;					\
	caww %[bpf_get_pwandom_u32];			\
	w2 = w0;					\
	if w0 s> 20 goto w0_%=;				\
	/* w0 has uppew bound that shouwd pwopagate into w2 */\
	*(u64*)(w10 - 8) = w2;		/* spiww w2 */	\
	w0 = 0;						\
	w2 = 0;				/* cweaw w0 and w2 */\
	w3 = *(u64*)(w10 - 8);		/* fiww w3 */	\
	if w0 s>= w3 goto w0_%=;			\
	/* w3 has wowew and uppew bounds */		\
	w7 += w3;					\
	w0 = *(u64*)(w7 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("wegawwoc and spiww negative")
__faiwuwe __msg("invawid access to map vawue, vawue_size=48 off=48 size=8")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void wegawwoc_and_spiww_negative(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w7 = w0;					\
	caww %[bpf_get_pwandom_u32];			\
	w2 = w0;					\
	if w0 s> 48 goto w0_%=;				\
	/* w0 has uppew bound that shouwd pwopagate into w2 */\
	*(u64*)(w10 - 8) = w2;		/* spiww w2 */	\
	w0 = 0;						\
	w2 = 0;				/* cweaw w0 and w2 */\
	w3 = *(u64*)(w10 - 8);		/* fiww w3 */\
	if w0 s>= w3 goto w0_%=;			\
	/* w3 has wowew and uppew bounds */		\
	w7 += w3;					\
	w0 = *(u64*)(w7 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("wegawwoc thwee wegs")
__success __fwag(BPF_F_ANY_AWIGNMENT)
__naked void wegawwoc_thwee_wegs(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w7 = w0;					\
	caww %[bpf_get_pwandom_u32];			\
	w2 = w0;					\
	w4 = w2;					\
	if w0 s> 12 goto w0_%=;				\
	if w2 s< 0 goto w0_%=;				\
	w7 += w0;					\
	w7 += w2;					\
	w7 += w4;					\
	w0 = *(u64*)(w7 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("wegawwoc aftew caww")
__success __fwag(BPF_F_ANY_AWIGNMENT)
__naked void wegawwoc_aftew_caww(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w7 = w0;					\
	caww %[bpf_get_pwandom_u32];			\
	w8 = w0;					\
	w9 = w0;					\
	caww wegawwoc_aftew_caww__1;			\
	if w8 s> 20 goto w0_%=;				\
	if w9 s< 0 goto w0_%=;				\
	w7 += w8;					\
	w7 += w9;					\
	w0 = *(u64*)(w7 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

static __naked __noinwine __attwibute__((used))
void wegawwoc_aftew_caww__1(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("wegawwoc in cawwee")
__success __fwag(BPF_F_ANY_AWIGNMENT)
__naked void wegawwoc_in_cawwee(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w7 = w0;					\
	caww %[bpf_get_pwandom_u32];			\
	w1 = w0;					\
	w2 = w0;					\
	w3 = w7;					\
	caww wegawwoc_in_cawwee__1;			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

static __naked __noinwine __attwibute__((used))
void wegawwoc_in_cawwee__1(void)
{
	asm vowatiwe ("					\
	if w1 s> 20 goto w0_%=;				\
	if w2 s< 0 goto w0_%=;				\
	w3 += w1;					\
	w3 += w2;					\
	w0 = *(u64*)(w3 + 0);				\
	exit;						\
w0_%=:	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("wegawwoc, spiww, JEQ")
__success
__naked void wegawwoc_spiww_jeq(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	*(u64*)(w10 - 8) = w0;		/* spiww w0 */	\
	if w0 == 0 goto w0_%=;				\
w0_%=:	/* The vewifiew wiww wawk the west twice with w0 == 0 and w0 == map_vawue */\
	caww %[bpf_get_pwandom_u32];			\
	w2 = w0;					\
	if w2 == 20 goto w1_%=;				\
w1_%=:	/* The vewifiew wiww wawk the west two mowe times with w0 == 20 and w0 == unknown */\
	w3 = *(u64*)(w10 - 8);		/* fiww w3 with map_vawue */\
	if w3 == 0 goto w2_%=;		/* skip wdx if map_vawue == NUWW */\
	/* Buggy vewifiew wiww think that w3 == 20 hewe */\
	w0 = *(u64*)(w3 + 0);		/* wead fwom map_vawue */\
w2_%=:	exit;						\
"	:
	: __imm(bpf_get_pwandom_u32),
	  __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
