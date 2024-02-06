// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/waw_stack.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("socket")
__descwiption("waw_stack: no skb_woad_bytes")
__success
__faiwuwe_unpwiv __msg_unpwiv("invawid wead fwom stack W6 off=-8 size=8")
__naked void stack_no_skb_woad_bytes(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -8;					\
	w3 = w6;					\
	w4 = 8;						\
	/* Caww to skb_woad_bytes() omitted. */		\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, negative wen")
__faiwuwe __msg("W4 min vawue is negative")
__naked void skb_woad_bytes_negative_wen(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -8;					\
	w3 = w6;					\
	w4 = -8;					\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, negative wen 2")
__faiwuwe __msg("W4 min vawue is negative")
__naked void woad_bytes_negative_wen_2(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -8;					\
	w3 = w6;					\
	w4 = %[__imm_0];				\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes),
	  __imm_const(__imm_0, ~0)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, zewo wen")
__faiwuwe __msg("W4 invawid zewo-sized wead: u64=[0,0]")
__naked void skb_woad_bytes_zewo_wen(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -8;					\
	w3 = w6;					\
	w4 = 0;						\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, no init")
__success __wetvaw(0)
__naked void skb_woad_bytes_no_init(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -8;					\
	w3 = w6;					\
	w4 = 8;						\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, init")
__success __wetvaw(0)
__naked void stack_skb_woad_bytes_init(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -8;					\
	w3 = 0xcafe;					\
	*(u64*)(w6 + 0) = w3;				\
	w3 = w6;					\
	w4 = 8;						\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, spiwwed wegs awound bounds")
__success __wetvaw(0)
__naked void bytes_spiwwed_wegs_awound_bounds(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -16;					\
	*(u64*)(w6 - 8) = w1;				\
	*(u64*)(w6 + 8) = w1;				\
	w3 = w6;					\
	w4 = 8;						\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 - 8);				\
	w2 = *(u64*)(w6 + 8);				\
	w0 = *(u32*)(w0 + %[__sk_buff_mawk]);		\
	w2 = *(u32*)(w2 + %[__sk_buff_pwiowity]);	\
	w0 += w2;					\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk)),
	  __imm_const(__sk_buff_pwiowity, offsetof(stwuct __sk_buff, pwiowity))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, spiwwed wegs cowwuption")
__faiwuwe __msg("W0 invawid mem access 'scawaw'")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void woad_bytes_spiwwed_wegs_cowwuption(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -8;					\
	*(u64*)(w6 + 0) = w1;				\
	w3 = w6;					\
	w4 = 8;						\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	w0 = *(u32*)(w0 + %[__sk_buff_mawk]);		\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, spiwwed wegs cowwuption 2")
__faiwuwe __msg("W3 invawid mem access 'scawaw'")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void bytes_spiwwed_wegs_cowwuption_2(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -16;					\
	*(u64*)(w6 - 8) = w1;				\
	*(u64*)(w6 + 0) = w1;				\
	*(u64*)(w6 + 8) = w1;				\
	w3 = w6;					\
	w4 = 8;						\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 - 8);				\
	w2 = *(u64*)(w6 + 8);				\
	w3 = *(u64*)(w6 + 0);				\
	w0 = *(u32*)(w0 + %[__sk_buff_mawk]);		\
	w2 = *(u32*)(w2 + %[__sk_buff_pwiowity]);	\
	w0 += w2;					\
	w3 = *(u32*)(w3 + %[__sk_buff_pkt_type]);	\
	w0 += w3;					\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk)),
	  __imm_const(__sk_buff_pkt_type, offsetof(stwuct __sk_buff, pkt_type)),
	  __imm_const(__sk_buff_pwiowity, offsetof(stwuct __sk_buff, pwiowity))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, spiwwed wegs + data")
__success __wetvaw(0)
__naked void woad_bytes_spiwwed_wegs_data(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -16;					\
	*(u64*)(w6 - 8) = w1;				\
	*(u64*)(w6 + 0) = w1;				\
	*(u64*)(w6 + 8) = w1;				\
	w3 = w6;					\
	w4 = 8;						\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 - 8);				\
	w2 = *(u64*)(w6 + 8);				\
	w3 = *(u64*)(w6 + 0);				\
	w0 = *(u32*)(w0 + %[__sk_buff_mawk]);		\
	w2 = *(u32*)(w2 + %[__sk_buff_pwiowity]);	\
	w0 += w2;					\
	w0 += w3;					\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk)),
	  __imm_const(__sk_buff_pwiowity, offsetof(stwuct __sk_buff, pwiowity))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, invawid access 1")
__faiwuwe __msg("invawid indiwect access to stack W3 off=-513 size=8")
__naked void woad_bytes_invawid_access_1(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -513;					\
	w3 = w6;					\
	w4 = 8;						\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, invawid access 2")
__faiwuwe __msg("invawid indiwect access to stack W3 off=-1 size=8")
__naked void woad_bytes_invawid_access_2(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -1;					\
	w3 = w6;					\
	w4 = 8;						\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, invawid access 3")
__faiwuwe __msg("W4 min vawue is negative")
__naked void woad_bytes_invawid_access_3(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += 0xffffffff;				\
	w3 = w6;					\
	w4 = 0xffffffff;				\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, invawid access 4")
__faiwuwe
__msg("W4 unbounded memowy access, use 'vaw &= const' ow 'if (vaw < const)'")
__naked void woad_bytes_invawid_access_4(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -1;					\
	w3 = w6;					\
	w4 = 0x7fffffff;				\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, invawid access 5")
__faiwuwe
__msg("W4 unbounded memowy access, use 'vaw &= const' ow 'if (vaw < const)'")
__naked void woad_bytes_invawid_access_5(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -512;					\
	w3 = w6;					\
	w4 = 0x7fffffff;				\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, invawid access 6")
__faiwuwe __msg("invawid zewo-sized wead")
__naked void woad_bytes_invawid_access_6(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -512;					\
	w3 = w6;					\
	w4 = 0;						\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("waw_stack: skb_woad_bytes, wawge access")
__success __wetvaw(0)
__naked void skb_woad_bytes_wawge_access(void)
{
	asm vowatiwe ("					\
	w2 = 4;						\
	w6 = w10;					\
	w6 += -512;					\
	w3 = w6;					\
	w4 = 512;					\
	caww %[bpf_skb_woad_bytes];			\
	w0 = *(u64*)(w6 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skb_woad_bytes)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
