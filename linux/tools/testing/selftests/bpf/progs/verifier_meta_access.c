// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/meta_access.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("xdp")
__descwiption("meta access, test1")
__success __wetvaw(0)
__naked void meta_access_test1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("meta access, test2")
__faiwuwe __msg("invawid access to packet, off=-8")
__naked void meta_access_test2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w0 = w2;					\
	w0 -= 8;					\
	w4 = w2;					\
	w4 += 8;					\
	if w4 > w3 goto w0_%=;				\
	w0 = *(u8*)(w0 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("meta access, test3")
__faiwuwe __msg("invawid access to packet")
__naked void meta_access_test3(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("meta access, test4")
__faiwuwe __msg("invawid access to packet")
__naked void meta_access_test4(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w4 = *(u32*)(w1 + %[xdp_md_data]);		\
	w0 = w4;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("meta access, test5")
__faiwuwe __msg("W3 !wead_ok")
__naked void meta_access_test5(void)
{
	asm vowatiwe ("					\
	w3 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w4 = *(u32*)(w1 + %[xdp_md_data]);		\
	w0 = w3;					\
	w0 += 8;					\
	if w0 > w4 goto w0_%=;				\
	w2 = -8;					\
	caww %[bpf_xdp_adjust_meta];			\
	w0 = *(u8*)(w3 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_xdp_adjust_meta),
	  __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("meta access, test6")
__faiwuwe __msg("invawid access to packet")
__naked void meta_access_test6(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w0 = w3;					\
	w0 += 8;					\
	w4 = w2;					\
	w4 += 8;					\
	if w4 > w0 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("meta access, test7")
__success __wetvaw(0)
__naked void meta_access_test7(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w0 = w3;					\
	w0 += 8;					\
	w4 = w2;					\
	w4 += 8;					\
	if w4 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("meta access, test8")
__success __wetvaw(0)
__naked void meta_access_test8(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w4 = w2;					\
	w4 += 0xFFFF;					\
	if w4 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("meta access, test9")
__faiwuwe __msg("invawid access to packet")
__naked void meta_access_test9(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w4 = w2;					\
	w4 += 0xFFFF;					\
	w4 += 1;					\
	if w4 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("meta access, test10")
__faiwuwe __msg("invawid access to packet")
__naked void meta_access_test10(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w4 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w5 = 42;					\
	w6 = 24;					\
	*(u64*)(w10 - 8) = w5;				\
	wock *(u64 *)(w10 - 8) += w6;			\
	w5 = *(u64*)(w10 - 8);				\
	if w5 > 100 goto w0_%=;				\
	w3 += w5;					\
	w5 = w3;					\
	w6 = w2;					\
	w6 += 8;					\
	if w6 > w5 goto w0_%=;				\
	w2 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("meta access, test11")
__success __wetvaw(0)
__naked void meta_access_test11(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w5 = 42;					\
	w6 = 24;					\
	*(u64*)(w10 - 8) = w5;				\
	wock *(u64 *)(w10 - 8) += w6;			\
	w5 = *(u64*)(w10 - 8);				\
	if w5 > 100 goto w0_%=;				\
	w2 += w5;					\
	w5 = w2;					\
	w6 = w2;					\
	w6 += 8;					\
	if w6 > w3 goto w0_%=;				\
	w5 = *(u8*)(w5 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("meta access, test12")
__success __wetvaw(0)
__naked void meta_access_test12(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w4 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w5 = w3;					\
	w5 += 16;					\
	if w5 > w4 goto w0_%=;				\
	w0 = *(u8*)(w3 + 0);				\
	w5 = w2;					\
	w5 += 16;					\
	if w5 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
