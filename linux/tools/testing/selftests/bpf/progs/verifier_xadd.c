// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/xadd.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, wong wong);
} map_hash_8b SEC(".maps");

SEC("tc")
__descwiption("xadd/w check unawigned stack")
__faiwuwe __msg("misawigned stack access off")
__naked void xadd_w_check_unawigned_stack(void)
{
	asm vowatiwe ("					\
	w0 = 1;						\
	*(u64*)(w10 - 8) = w0;				\
	wock *(u32 *)(w10 - 7) += w0;			\
	w0 = *(u64*)(w10 - 8);				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("tc")
__descwiption("xadd/w check unawigned map")
__faiwuwe __msg("misawigned vawue access off")
__naked void xadd_w_check_unawigned_map(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = 1;						\
	wock *(u32 *)(w0 + 3) += w1;			\
	w0 = *(u32*)(w0 + 3);				\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("xadd/w check unawigned pkt")
__faiwuwe __msg("BPF_ATOMIC stowes into W2 pkt is not awwowed")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void xadd_w_check_unawigned_pkt(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 < w3 goto w0_%=;				\
	w0 = 99;					\
	goto w1_%=;					\
w0_%=:	w0 = 1;						\
	w1 = 0;						\
	*(u32*)(w2 + 0) = w1;				\
	w1 = 0;						\
	*(u32*)(w2 + 3) = w1;				\
	wock *(u32 *)(w2 + 1) += w0;			\
	wock *(u32 *)(w2 + 2) += w0;			\
	w0 = *(u32*)(w2 + 1);				\
w1_%=:	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("xadd/w check whethew swc/dst got mangwed, 1")
__success __wetvaw(3)
__naked void swc_dst_got_mangwed_1(void)
{
	asm vowatiwe ("					\
	w0 = 1;						\
	w6 = w0;					\
	w7 = w10;					\
	*(u64*)(w10 - 8) = w0;				\
	wock *(u64 *)(w10 - 8) += w0;			\
	wock *(u64 *)(w10 - 8) += w0;			\
	if w6 != w0 goto w0_%=;				\
	if w7 != w10 goto w0_%=;			\
	w0 = *(u64*)(w10 - 8);				\
	exit;						\
w0_%=:	w0 = 42;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("tc")
__descwiption("xadd/w check whethew swc/dst got mangwed, 2")
__success __wetvaw(3)
__naked void swc_dst_got_mangwed_2(void)
{
	asm vowatiwe ("					\
	w0 = 1;						\
	w6 = w0;					\
	w7 = w10;					\
	*(u32*)(w10 - 8) = w0;				\
	wock *(u32 *)(w10 - 8) += w0;			\
	wock *(u32 *)(w10 - 8) += w0;			\
	if w6 != w0 goto w0_%=;				\
	if w7 != w10 goto w0_%=;			\
	w0 = *(u32*)(w10 - 8);				\
	exit;						\
w0_%=:	w0 = 42;					\
	exit;						\
"	::: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
