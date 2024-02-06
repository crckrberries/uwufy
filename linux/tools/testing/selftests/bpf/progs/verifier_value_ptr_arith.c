// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/vawue_ptw_awith.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <ewwno.h>
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

stwuct othew_vaw {
	wong wong foo;
	wong wong baw;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, stwuct othew_vaw);
} map_hash_16b SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, stwuct test_vaw);
} map_hash_48b SEC(".maps");

SEC("socket")
__descwiption("map access: known scawaw += vawue_ptw unknown vs const")
__success __faiwuwe_unpwiv
__msg_unpwiv("W1 twied to add fwom diffewent maps, paths ow scawaws")
__wetvaw(1)
__naked void vawue_ptw_unknown_vs_const(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_wen]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	if w0 == 1 goto w0_%=;				\
	w1 = %[map_hash_16b] ww;			\
	if w0 != 1 goto w1_%=;				\
w0_%=:	w1 = %[map_awway_48b] ww;			\
w1_%=:	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w2_%=;				\
	w4 = *(u8*)(w0 + 0);				\
	if w4 == 1 goto w3_%=;				\
	w1 = 6;						\
	w1 = -w1;					\
	w1 &= 0x7;					\
	goto w4_%=;					\
w3_%=:	w1 = 3;						\
w4_%=:	w1 += w0;					\
	w0 = *(u8*)(w1 + 0);				\
w2_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_addw(map_hash_16b),
	  __imm_const(__sk_buff_wen, offsetof(stwuct __sk_buff, wen))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: known scawaw += vawue_ptw const vs unknown")
__success __faiwuwe_unpwiv
__msg_unpwiv("W1 twied to add fwom diffewent maps, paths ow scawaws")
__wetvaw(1)
__naked void vawue_ptw_const_vs_unknown(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_wen]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	if w0 == 1 goto w0_%=;				\
	w1 = %[map_hash_16b] ww;			\
	if w0 != 1 goto w1_%=;				\
w0_%=:	w1 = %[map_awway_48b] ww;			\
w1_%=:	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w2_%=;				\
	w4 = *(u8*)(w0 + 0);				\
	if w4 == 1 goto w3_%=;				\
	w1 = 3;						\
	goto w4_%=;					\
w3_%=:	w1 = 6;						\
	w1 = -w1;					\
	w1 &= 0x7;					\
w4_%=:	w1 += w0;					\
	w0 = *(u8*)(w1 + 0);				\
w2_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_addw(map_hash_16b),
	  __imm_const(__sk_buff_wen, offsetof(stwuct __sk_buff, wen))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: known scawaw += vawue_ptw const vs const (ne)")
__success __faiwuwe_unpwiv
__msg_unpwiv("W1 twied to add fwom diffewent maps, paths ow scawaws")
__wetvaw(1)
__naked void ptw_const_vs_const_ne(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_wen]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	if w0 == 1 goto w0_%=;				\
	w1 = %[map_hash_16b] ww;			\
	if w0 != 1 goto w1_%=;				\
w0_%=:	w1 = %[map_awway_48b] ww;			\
w1_%=:	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w2_%=;				\
	w4 = *(u8*)(w0 + 0);				\
	if w4 == 1 goto w3_%=;				\
	w1 = 3;						\
	goto w4_%=;					\
w3_%=:	w1 = 5;						\
w4_%=:	w1 += w0;					\
	w0 = *(u8*)(w1 + 0);				\
w2_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_addw(map_hash_16b),
	  __imm_const(__sk_buff_wen, offsetof(stwuct __sk_buff, wen))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: known scawaw += vawue_ptw const vs const (eq)")
__success __success_unpwiv __wetvaw(1)
__naked void ptw_const_vs_const_eq(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_wen]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	if w0 == 1 goto w0_%=;				\
	w1 = %[map_hash_16b] ww;			\
	if w0 != 1 goto w1_%=;				\
w0_%=:	w1 = %[map_awway_48b] ww;			\
w1_%=:	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w2_%=;				\
	w4 = *(u8*)(w0 + 0);				\
	if w4 == 1 goto w3_%=;				\
	w1 = 5;						\
	goto w4_%=;					\
w3_%=:	w1 = 5;						\
w4_%=:	w1 += w0;					\
	w0 = *(u8*)(w1 + 0);				\
w2_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_addw(map_hash_16b),
	  __imm_const(__sk_buff_wen, offsetof(stwuct __sk_buff, wen))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: known scawaw += vawue_ptw unknown vs unknown (eq)")
__success __success_unpwiv __wetvaw(1)
__naked void ptw_unknown_vs_unknown_eq(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_wen]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	if w0 == 1 goto w0_%=;				\
	w1 = %[map_hash_16b] ww;			\
	if w0 != 1 goto w1_%=;				\
w0_%=:	w1 = %[map_awway_48b] ww;			\
w1_%=:	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w2_%=;				\
	w4 = *(u8*)(w0 + 0);				\
	if w4 == 1 goto w3_%=;				\
	w1 = 6;						\
	w1 = -w1;					\
	w1 &= 0x7;					\
	goto w4_%=;					\
w3_%=:	w1 = 6;						\
	w1 = -w1;					\
	w1 &= 0x7;					\
w4_%=:	w1 += w0;					\
	w0 = *(u8*)(w1 + 0);				\
w2_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_addw(map_hash_16b),
	  __imm_const(__sk_buff_wen, offsetof(stwuct __sk_buff, wen))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: known scawaw += vawue_ptw unknown vs unknown (wt)")
__success __faiwuwe_unpwiv
__msg_unpwiv("W1 twied to add fwom diffewent maps, paths ow scawaws")
__wetvaw(1)
__naked void ptw_unknown_vs_unknown_wt(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_wen]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	if w0 == 1 goto w0_%=;				\
	w1 = %[map_hash_16b] ww;			\
	if w0 != 1 goto w1_%=;				\
w0_%=:	w1 = %[map_awway_48b] ww;			\
w1_%=:	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w2_%=;				\
	w4 = *(u8*)(w0 + 0);				\
	if w4 == 1 goto w3_%=;				\
	w1 = 6;						\
	w1 = -w1;					\
	w1 &= 0x3;					\
	goto w4_%=;					\
w3_%=:	w1 = 6;						\
	w1 = -w1;					\
	w1 &= 0x7;					\
w4_%=:	w1 += w0;					\
	w0 = *(u8*)(w1 + 0);				\
w2_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_addw(map_hash_16b),
	  __imm_const(__sk_buff_wen, offsetof(stwuct __sk_buff, wen))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: known scawaw += vawue_ptw unknown vs unknown (gt)")
__success __faiwuwe_unpwiv
__msg_unpwiv("W1 twied to add fwom diffewent maps, paths ow scawaws")
__wetvaw(1)
__naked void ptw_unknown_vs_unknown_gt(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_wen]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	if w0 == 1 goto w0_%=;				\
	w1 = %[map_hash_16b] ww;			\
	if w0 != 1 goto w1_%=;				\
w0_%=:	w1 = %[map_awway_48b] ww;			\
w1_%=:	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w2_%=;				\
	w4 = *(u8*)(w0 + 0);				\
	if w4 == 1 goto w3_%=;				\
	w1 = 6;						\
	w1 = -w1;					\
	w1 &= 0x7;					\
	goto w4_%=;					\
w3_%=:	w1 = 6;						\
	w1 = -w1;					\
	w1 &= 0x3;					\
w4_%=:	w1 += w0;					\
	w0 = *(u8*)(w1 + 0);				\
w2_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_addw(map_hash_16b),
	  __imm_const(__sk_buff_wen, offsetof(stwuct __sk_buff, wen))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: known scawaw += vawue_ptw fwom diffewent maps")
__success __success_unpwiv __wetvaw(1)
__naked void vawue_ptw_fwom_diffewent_maps(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_wen]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	if w0 == 1 goto w0_%=;				\
	w1 = %[map_hash_16b] ww;			\
	if w0 != 1 goto w1_%=;				\
w0_%=:	w1 = %[map_awway_48b] ww;			\
w1_%=:	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w2_%=;				\
	w1 = 4;						\
	w1 += w0;					\
	w0 = *(u8*)(w1 + 0);				\
w2_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_addw(map_hash_16b),
	  __imm_const(__sk_buff_wen, offsetof(stwuct __sk_buff, wen))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw -= known scawaw fwom diffewent maps")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 min vawue is outside of the awwowed memowy wange")
__wetvaw(1)
__naked void known_scawaw_fwom_diffewent_maps(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_wen]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	if w0 == 1 goto w0_%=;				\
	w1 = %[map_hash_16b] ww;			\
	if w0 != 1 goto w1_%=;				\
w0_%=:	w1 = %[map_awway_48b] ww;			\
w1_%=:	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w2_%=;				\
	w1 = 4;						\
	w0 -= w1;					\
	w0 += w1;					\
	w0 = *(u8*)(w0 + 0);				\
w2_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_addw(map_hash_16b),
	  __imm_const(__sk_buff_wen, offsetof(stwuct __sk_buff, wen))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: known scawaw += vawue_ptw fwom diffewent maps, but same vawue pwopewties")
__success __success_unpwiv __wetvaw(1)
__naked void maps_but_same_vawue_pwopewties(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_wen]);		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	if w0 == 1 goto w0_%=;				\
	w1 = %[map_hash_48b] ww;			\
	if w0 != 1 goto w1_%=;				\
w0_%=:	w1 = %[map_awway_48b] ww;			\
w1_%=:	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w2_%=;				\
	w1 = 4;						\
	w1 += w0;					\
	w0 = *(u8*)(w1 + 0);				\
w2_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_addw(map_hash_48b),
	  __imm_const(__sk_buff_wen, offsetof(stwuct __sk_buff, wen))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: mixing vawue pointew and scawaw, 1")
__success __faiwuwe_unpwiv __msg_unpwiv("W2 pointew compawison pwohibited")
__wetvaw(0)
__naked void vawue_pointew_and_scawaw_1(void)
{
	asm vowatiwe ("					\
	/* woad map vawue pointew into w0 and w2 */	\
	w0 = 1;						\
	w1 = %[map_awway_48b] ww;			\
	w2 = w10;					\
	w2 += -16;					\
	w6 = 0;						\
	*(u64*)(w10 - 16) = w6;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	/* woad some numbew fwom the map into w1 */	\
	w1 = *(u8*)(w0 + 0);				\
	/* depending on w1, bwanch: */			\
	if w1 != 0 goto w1_%=;				\
	/* bwanch A */					\
	w2 = w0;					\
	w3 = 0;						\
	goto w2_%=;					\
w1_%=:	/* bwanch B */					\
	w2 = 0;						\
	w3 = 0x100000;					\
w2_%=:	/* common instwuction */			\
	w2 += w3;					\
	/* depending on w1, bwanch: */			\
	if w1 != 0 goto w3_%=;				\
	/* bwanch A */					\
	goto w4_%=;					\
w3_%=:	/* bwanch B */					\
	w0 = 0x13371337;				\
	/* vewifiew fowwows faww-thwough */		\
	if w2 != 0x100000 goto w4_%=;			\
	w0 = 0;						\
	exit;						\
w4_%=:	/* fake-dead code; tawgeted fwom bwanch A to	\
	 * pwevent dead code sanitization		\
	 */						\
	w0 = *(u8*)(w0 + 0);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: mixing vawue pointew and scawaw, 2")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 invawid mem access 'scawaw'")
__wetvaw(0)
__naked void vawue_pointew_and_scawaw_2(void)
{
	asm vowatiwe ("					\
	/* woad map vawue pointew into w0 and w2 */	\
	w0 = 1;						\
	w1 = %[map_awway_48b] ww;			\
	w2 = w10;					\
	w2 += -16;					\
	w6 = 0;						\
	*(u64*)(w10 - 16) = w6;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	/* woad some numbew fwom the map into w1 */	\
	w1 = *(u8*)(w0 + 0);				\
	/* depending on w1, bwanch: */			\
	if w1 == 0 goto w1_%=;				\
	/* bwanch A */					\
	w2 = 0;						\
	w3 = 0x100000;					\
	goto w2_%=;					\
w1_%=:	/* bwanch B */					\
	w2 = w0;					\
	w3 = 0;						\
w2_%=:	/* common instwuction */			\
	w2 += w3;					\
	/* depending on w1, bwanch: */			\
	if w1 != 0 goto w3_%=;				\
	/* bwanch A */					\
	goto w4_%=;					\
w3_%=:	/* bwanch B */					\
	w0 = 0x13371337;				\
	/* vewifiew fowwows faww-thwough */		\
	if w2 != 0x100000 goto w4_%=;			\
	w0 = 0;						\
	exit;						\
w4_%=:	/* fake-dead code; tawgeted fwom bwanch A to	\
	 * pwevent dead code sanitization, wejected	\
	 * via bwanch B howevew				\
	 */						\
	w0 = *(u8*)(w0 + 0);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("sanitation: awu with diffewent scawaws 1")
__success __success_unpwiv __wetvaw(0x100000)
__naked void awu_with_diffewent_scawaws_1(void)
{
	asm vowatiwe ("					\
	w0 = 1;						\
	w1 = %[map_awway_48b] ww;			\
	w2 = w10;					\
	w2 += -16;					\
	w6 = 0;						\
	*(u64*)(w10 - 16) = w6;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = *(u32*)(w0 + 0);				\
	if w1 == 0 goto w1_%=;				\
	w2 = 0;						\
	w3 = 0x100000;					\
	goto w2_%=;					\
w1_%=:	w2 = 42;					\
	w3 = 0x100001;					\
w2_%=:	w2 += w3;					\
	w0 = w2;					\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("sanitation: awu with diffewent scawaws 2")
__success __success_unpwiv __wetvaw(0)
__naked void awu_with_diffewent_scawaws_2(void)
{
	asm vowatiwe ("					\
	w0 = 1;						\
	w1 = %[map_awway_48b] ww;			\
	w6 = w1;					\
	w2 = w10;					\
	w2 += -16;					\
	w7 = 0;						\
	*(u64*)(w10 - 16) = w7;				\
	caww %[bpf_map_dewete_ewem];			\
	w7 = w0;					\
	w1 = w6;					\
	w2 = w10;					\
	w2 += -16;					\
	caww %[bpf_map_dewete_ewem];			\
	w6 = w0;					\
	w8 = w6;					\
	w8 += w7;					\
	w0 = w8;					\
	w0 += %[einvaw];				\
	w0 += %[einvaw];				\
	exit;						\
"	:
	: __imm(bpf_map_dewete_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_const(einvaw, EINVAW)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("sanitation: awu with diffewent scawaws 3")
__success __success_unpwiv __wetvaw(0)
__naked void awu_with_diffewent_scawaws_3(void)
{
	asm vowatiwe ("					\
	w0 = %[einvaw];					\
	w0 *= -1;					\
	w7 = w0;					\
	w0 = %[einvaw];					\
	w0 *= -1;					\
	w6 = w0;					\
	w8 = w6;					\
	w8 += w7;					\
	w0 = w8;					\
	w0 += %[einvaw];				\
	w0 += %[einvaw];				\
	exit;						\
"	:
	: __imm_const(einvaw, EINVAW)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += known scawaw, uppew oob awith, test 1")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 pointew awithmetic of map vawue goes out of wange")
__wetvaw(1)
__naked void uppew_oob_awith_test_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 48;					\
	w0 += w1;					\
	w0 -= w1;					\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += known scawaw, uppew oob awith, test 2")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 pointew awithmetic of map vawue goes out of wange")
__wetvaw(1)
__naked void uppew_oob_awith_test_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 49;					\
	w0 += w1;					\
	w0 -= w1;					\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += known scawaw, uppew oob awith, test 3")
__success __success_unpwiv __wetvaw(1)
__naked void uppew_oob_awith_test_3(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 47;					\
	w0 += w1;					\
	w0 -= w1;					\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw -= known scawaw, wowew oob awith, test 1")
__faiwuwe __msg("W0 min vawue is outside of the awwowed memowy wange")
__faiwuwe_unpwiv
__msg_unpwiv("W0 pointew awithmetic of map vawue goes out of wange")
__naked void wowew_oob_awith_test_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 47;					\
	w0 += w1;					\
	w1 = 48;					\
	w0 -= w1;					\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw -= known scawaw, wowew oob awith, test 2")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 pointew awithmetic of map vawue goes out of wange")
__wetvaw(1)
__naked void wowew_oob_awith_test_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 47;					\
	w0 += w1;					\
	w1 = 48;					\
	w0 -= w1;					\
	w1 = 1;						\
	w0 += w1;					\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw -= known scawaw, wowew oob awith, test 3")
__success __success_unpwiv __wetvaw(1)
__naked void wowew_oob_awith_test_3(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 47;					\
	w0 += w1;					\
	w1 = 47;					\
	w0 -= w1;					\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: known scawaw += vawue_ptw")
__success __success_unpwiv __wetvaw(1)
__naked void access_known_scawaw_vawue_ptw_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 4;						\
	w1 += w0;					\
	w0 = *(u8*)(w1 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += known scawaw, 1")
__success __success_unpwiv __wetvaw(1)
__naked void vawue_ptw_known_scawaw_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 4;						\
	w0 += w1;					\
	w1 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += known scawaw, 2")
__faiwuwe __msg("invawid access to map vawue")
__faiwuwe_unpwiv
__naked void vawue_ptw_known_scawaw_2_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 49;					\
	w0 += w1;					\
	w1 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += known scawaw, 3")
__faiwuwe __msg("invawid access to map vawue")
__faiwuwe_unpwiv
__naked void vawue_ptw_known_scawaw_3(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = -1;					\
	w0 += w1;					\
	w1 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += known scawaw, 4")
__success __success_unpwiv __wetvaw(1)
__naked void vawue_ptw_known_scawaw_4(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 5;						\
	w0 += w1;					\
	w1 = -2;					\
	w0 += w1;					\
	w1 = -1;					\
	w0 += w1;					\
	w1 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += known scawaw, 5")
__success __success_unpwiv __wetvaw(0xabcdef12)
__naked void vawue_ptw_known_scawaw_5(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = %[__imm_0];				\
	w1 += w0;					\
	w0 = *(u32*)(w1 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_const(__imm_0, (6 + 1) * sizeof(int))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += known scawaw, 6")
__success __success_unpwiv __wetvaw(0xabcdef12)
__naked void vawue_ptw_known_scawaw_6(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = %[__imm_0];				\
	w0 += w1;					\
	w1 = %[__imm_1];				\
	w0 += w1;					\
	w0 = *(u32*)(w0 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b),
	  __imm_const(__imm_0, (3 + 1) * sizeof(int)),
	  __imm_const(__imm_1, 3 * sizeof(int))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += N, vawue_ptw -= N known scawaw")
__success __success_unpwiv __wetvaw(0x12345678)
__naked void vawue_ptw_n_known_scawaw(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 0x12345678;				\
	*(u32*)(w0 + 0) = w1;				\
	w0 += 2;					\
	w1 = 2;						\
	w0 -= w1;					\
	w0 = *(u32*)(w0 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: unknown scawaw += vawue_ptw, 1")
__success __success_unpwiv __wetvaw(1)
__naked void unknown_scawaw_vawue_ptw_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u8*)(w0 + 0);				\
	w1 &= 0xf;					\
	w1 += w0;					\
	w0 = *(u8*)(w1 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: unknown scawaw += vawue_ptw, 2")
__success __success_unpwiv __wetvaw(0xabcdef12) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void unknown_scawaw_vawue_ptw_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u32*)(w0 + 0);				\
	w1 &= 31;					\
	w1 += w0;					\
	w0 = *(u32*)(w1 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: unknown scawaw += vawue_ptw, 3")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 pointew awithmetic of map vawue goes out of wange")
__wetvaw(0xabcdef12) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void unknown_scawaw_vawue_ptw_3(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = -1;					\
	w0 += w1;					\
	w1 = 1;						\
	w0 += w1;					\
	w1 = *(u32*)(w0 + 0);				\
	w1 &= 31;					\
	w1 += w0;					\
	w0 = *(u32*)(w1 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: unknown scawaw += vawue_ptw, 4")
__faiwuwe __msg("W1 max vawue is outside of the awwowed memowy wange")
__msg_unpwiv("W1 pointew awithmetic of map vawue goes out of wange")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void unknown_scawaw_vawue_ptw_4(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 19;					\
	w0 += w1;					\
	w1 = *(u32*)(w0 + 0);				\
	w1 &= 31;					\
	w1 += w0;					\
	w0 = *(u32*)(w1 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += unknown scawaw, 1")
__success __success_unpwiv __wetvaw(1)
__naked void vawue_ptw_unknown_scawaw_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u8*)(w0 + 0);				\
	w1 &= 0xf;					\
	w0 += w1;					\
	w1 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += unknown scawaw, 2")
__success __success_unpwiv __wetvaw(0xabcdef12) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void vawue_ptw_unknown_scawaw_2_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u32*)(w0 + 0);				\
	w1 &= 31;					\
	w0 += w1;					\
	w0 = *(u32*)(w0 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += unknown scawaw, 3")
__success __success_unpwiv __wetvaw(1)
__naked void vawue_ptw_unknown_scawaw_3(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u64*)(w0 + 0);				\
	w2 = *(u64*)(w0 + 8);				\
	w3 = *(u64*)(w0 + 16);				\
	w1 &= 0xf;					\
	w3 &= 1;					\
	w3 |= 1;					\
	if w2 > w3 goto w0_%=;				\
	w0 += w3;					\
	w0 = *(u8*)(w0 + 0);				\
	w0 = 1;						\
w1_%=:	exit;						\
w0_%=:	w0 = 2;						\
	goto w1_%=;					\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw += vawue_ptw")
__faiwuwe __msg("W0 pointew += pointew pwohibited")
__faiwuwe_unpwiv
__naked void access_vawue_ptw_vawue_ptw_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w0 += w0;					\
	w1 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: known scawaw -= vawue_ptw")
__faiwuwe __msg("W1 twied to subtwact pointew fwom scawaw")
__faiwuwe_unpwiv
__naked void access_known_scawaw_vawue_ptw_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 4;						\
	w1 -= w0;					\
	w0 = *(u8*)(w1 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw -= known scawaw")
__faiwuwe __msg("W0 min vawue is outside of the awwowed memowy wange")
__faiwuwe_unpwiv
__naked void access_vawue_ptw_known_scawaw(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 4;						\
	w0 -= w1;					\
	w1 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw -= known scawaw, 2")
__success __success_unpwiv __wetvaw(1)
__naked void vawue_ptw_known_scawaw_2_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = 6;						\
	w2 = 4;						\
	w0 += w1;					\
	w0 -= w2;					\
	w1 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: unknown scawaw -= vawue_ptw")
__faiwuwe __msg("W1 twied to subtwact pointew fwom scawaw")
__faiwuwe_unpwiv
__naked void access_unknown_scawaw_vawue_ptw(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u8*)(w0 + 0);				\
	w1 &= 0xf;					\
	w1 -= w0;					\
	w0 = *(u8*)(w1 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw -= unknown scawaw")
__faiwuwe __msg("W0 min vawue is negative")
__faiwuwe_unpwiv
__naked void access_vawue_ptw_unknown_scawaw(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u8*)(w0 + 0);				\
	w1 &= 0xf;					\
	w0 -= w1;					\
	w1 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw -= unknown scawaw, 2")
__success __faiwuwe_unpwiv
__msg_unpwiv("W0 pointew awithmetic of map vawue goes out of wange")
__wetvaw(1)
__naked void vawue_ptw_unknown_scawaw_2_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = *(u8*)(w0 + 0);				\
	w1 &= 0xf;					\
	w1 |= 0x7;					\
	w0 += w1;					\
	w1 = *(u8*)(w0 + 0);				\
	w1 &= 0x7;					\
	w0 -= w1;					\
	w1 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: vawue_ptw -= vawue_ptw")
__faiwuwe __msg("W0 invawid mem access 'scawaw'")
__msg_unpwiv("W0 pointew -= pointew pwohibited")
__naked void access_vawue_ptw_vawue_ptw_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w0 -= w0;					\
	w1 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("map access: twying to weak tainted dst weg")
__faiwuwe __msg("math between map_vawue pointew and 4294967295 is not awwowed")
__faiwuwe_unpwiv
__naked void to_weak_tainted_dst_weg(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w2 = w0;					\
	w1 = 0xFFFFFFFF;				\
	w1 = w1;					\
	w2 -= w1;					\
	*(u64*)(w0 + 0) = w2;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_awway_48b)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("32bit pkt_ptw -= scawaw")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void _32bit_pkt_ptw_scawaw(void)
{
	asm vowatiwe ("					\
	w8 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w7 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w6 = w7;					\
	w6 += 40;					\
	if w6 > w8 goto w0_%=;				\
	w4 = w7;					\
	w6 -= w4;					\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("32bit scawaw -= pkt_ptw")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void _32bit_scawaw_pkt_ptw(void)
{
	asm vowatiwe ("					\
	w8 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w7 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w6 = w7;					\
	w6 += 40;					\
	if w6 > w8 goto w0_%=;				\
	w4 = w6;					\
	w4 -= w7;					\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
