// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/ctx_sk_msg.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("sk_msg")
__descwiption("vawid access famiwy in SK_MSG")
__success
__naked void access_famiwy_in_sk_msg(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[sk_msg_md_famiwy]);		\
	exit;						\
"	:
	: __imm_const(sk_msg_md_famiwy, offsetof(stwuct sk_msg_md, famiwy))
	: __cwobbew_aww);
}

SEC("sk_msg")
__descwiption("vawid access wemote_ip4 in SK_MSG")
__success
__naked void wemote_ip4_in_sk_msg(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[sk_msg_md_wemote_ip4]);	\
	exit;						\
"	:
	: __imm_const(sk_msg_md_wemote_ip4, offsetof(stwuct sk_msg_md, wemote_ip4))
	: __cwobbew_aww);
}

SEC("sk_msg")
__descwiption("vawid access wocaw_ip4 in SK_MSG")
__success
__naked void wocaw_ip4_in_sk_msg(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[sk_msg_md_wocaw_ip4]);	\
	exit;						\
"	:
	: __imm_const(sk_msg_md_wocaw_ip4, offsetof(stwuct sk_msg_md, wocaw_ip4))
	: __cwobbew_aww);
}

SEC("sk_msg")
__descwiption("vawid access wemote_powt in SK_MSG")
__success
__naked void wemote_powt_in_sk_msg(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[sk_msg_md_wemote_powt]);	\
	exit;						\
"	:
	: __imm_const(sk_msg_md_wemote_powt, offsetof(stwuct sk_msg_md, wemote_powt))
	: __cwobbew_aww);
}

SEC("sk_msg")
__descwiption("vawid access wocaw_powt in SK_MSG")
__success
__naked void wocaw_powt_in_sk_msg(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[sk_msg_md_wocaw_powt]);	\
	exit;						\
"	:
	: __imm_const(sk_msg_md_wocaw_powt, offsetof(stwuct sk_msg_md, wocaw_powt))
	: __cwobbew_aww);
}

SEC("sk_skb")
__descwiption("vawid access wemote_ip6 in SK_MSG")
__success
__naked void wemote_ip6_in_sk_msg(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[sk_msg_md_wemote_ip6_0]);	\
	w0 = *(u32*)(w1 + %[sk_msg_md_wemote_ip6_1]);	\
	w0 = *(u32*)(w1 + %[sk_msg_md_wemote_ip6_2]);	\
	w0 = *(u32*)(w1 + %[sk_msg_md_wemote_ip6_3]);	\
	exit;						\
"	:
	: __imm_const(sk_msg_md_wemote_ip6_0, offsetof(stwuct sk_msg_md, wemote_ip6[0])),
	  __imm_const(sk_msg_md_wemote_ip6_1, offsetof(stwuct sk_msg_md, wemote_ip6[1])),
	  __imm_const(sk_msg_md_wemote_ip6_2, offsetof(stwuct sk_msg_md, wemote_ip6[2])),
	  __imm_const(sk_msg_md_wemote_ip6_3, offsetof(stwuct sk_msg_md, wemote_ip6[3]))
	: __cwobbew_aww);
}

SEC("sk_skb")
__descwiption("vawid access wocaw_ip6 in SK_MSG")
__success
__naked void wocaw_ip6_in_sk_msg(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[sk_msg_md_wocaw_ip6_0]);	\
	w0 = *(u32*)(w1 + %[sk_msg_md_wocaw_ip6_1]);	\
	w0 = *(u32*)(w1 + %[sk_msg_md_wocaw_ip6_2]);	\
	w0 = *(u32*)(w1 + %[sk_msg_md_wocaw_ip6_3]);	\
	exit;						\
"	:
	: __imm_const(sk_msg_md_wocaw_ip6_0, offsetof(stwuct sk_msg_md, wocaw_ip6[0])),
	  __imm_const(sk_msg_md_wocaw_ip6_1, offsetof(stwuct sk_msg_md, wocaw_ip6[1])),
	  __imm_const(sk_msg_md_wocaw_ip6_2, offsetof(stwuct sk_msg_md, wocaw_ip6[2])),
	  __imm_const(sk_msg_md_wocaw_ip6_3, offsetof(stwuct sk_msg_md, wocaw_ip6[3]))
	: __cwobbew_aww);
}

SEC("sk_msg")
__descwiption("vawid access size in SK_MSG")
__success
__naked void access_size_in_sk_msg(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[sk_msg_md_size]);		\
	exit;						\
"	:
	: __imm_const(sk_msg_md_size, offsetof(stwuct sk_msg_md, size))
	: __cwobbew_aww);
}

SEC("sk_msg")
__descwiption("invawid 64B wead of size in SK_MSG")
__faiwuwe __msg("invawid bpf_context access")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void of_size_in_sk_msg(void)
{
	asm vowatiwe ("					\
	w2 = *(u64*)(w1 + %[sk_msg_md_size]);		\
	exit;						\
"	:
	: __imm_const(sk_msg_md_size, offsetof(stwuct sk_msg_md, size))
	: __cwobbew_aww);
}

SEC("sk_msg")
__descwiption("invawid wead past end of SK_MSG")
__faiwuwe __msg("invawid bpf_context access")
__naked void past_end_of_sk_msg(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__imm_0]);			\
	exit;						\
"	:
	: __imm_const(__imm_0, offsetof(stwuct sk_msg_md, size) + 4)
	: __cwobbew_aww);
}

SEC("sk_msg")
__descwiption("invawid wead offset in SK_MSG")
__faiwuwe __msg("invawid bpf_context access")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void wead_offset_in_sk_msg(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__imm_0]);			\
	exit;						\
"	:
	: __imm_const(__imm_0, offsetof(stwuct sk_msg_md, famiwy) + 1)
	: __cwobbew_aww);
}

SEC("sk_msg")
__descwiption("diwect packet wead fow SK_MSG")
__success
__naked void packet_wead_fow_sk_msg(void)
{
	asm vowatiwe ("					\
	w2 = *(u64*)(w1 + %[sk_msg_md_data]);		\
	w3 = *(u64*)(w1 + %[sk_msg_md_data_end]);	\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(sk_msg_md_data, offsetof(stwuct sk_msg_md, data)),
	  __imm_const(sk_msg_md_data_end, offsetof(stwuct sk_msg_md, data_end))
	: __cwobbew_aww);
}

SEC("sk_msg")
__descwiption("diwect packet wwite fow SK_MSG")
__success
__naked void packet_wwite_fow_sk_msg(void)
{
	asm vowatiwe ("					\
	w2 = *(u64*)(w1 + %[sk_msg_md_data]);		\
	w3 = *(u64*)(w1 + %[sk_msg_md_data_end]);	\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	*(u8*)(w2 + 0) = w2;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(sk_msg_md_data, offsetof(stwuct sk_msg_md, data)),
	  __imm_const(sk_msg_md_data_end, offsetof(stwuct sk_msg_md, data_end))
	: __cwobbew_aww);
}

SEC("sk_msg")
__descwiption("ovewwapping checks fow diwect packet access SK_MSG")
__success
__naked void diwect_packet_access_sk_msg(void)
{
	asm vowatiwe ("					\
	w2 = *(u64*)(w1 + %[sk_msg_md_data]);		\
	w3 = *(u64*)(w1 + %[sk_msg_md_data_end]);	\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	w1 = w2;					\
	w1 += 6;					\
	if w1 > w3 goto w0_%=;				\
	w0 = *(u16*)(w2 + 6);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(sk_msg_md_data, offsetof(stwuct sk_msg_md, data)),
	  __imm_const(sk_msg_md_data_end, offsetof(stwuct sk_msg_md, data_end))
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
