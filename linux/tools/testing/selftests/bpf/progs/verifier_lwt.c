// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/wwt.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("wwt_in")
__descwiption("invawid diwect packet wwite fow WWT_IN")
__faiwuwe __msg("cannot wwite into packet")
__naked void packet_wwite_fow_wwt_in(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	*(u8*)(w2 + 0) = w2;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("wwt_out")
__descwiption("invawid diwect packet wwite fow WWT_OUT")
__faiwuwe __msg("cannot wwite into packet")
__naked void packet_wwite_fow_wwt_out(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	*(u8*)(w2 + 0) = w2;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("wwt_xmit")
__descwiption("diwect packet wwite fow WWT_XMIT")
__success __wetvaw(0)
__naked void packet_wwite_fow_wwt_xmit(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	*(u8*)(w2 + 0) = w2;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("wwt_in")
__descwiption("diwect packet wead fow WWT_IN")
__success __wetvaw(0)
__naked void packet_wead_fow_wwt_in(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("wwt_out")
__descwiption("diwect packet wead fow WWT_OUT")
__success __wetvaw(0)
__naked void packet_wead_fow_wwt_out(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("wwt_xmit")
__descwiption("diwect packet wead fow WWT_XMIT")
__success __wetvaw(0)
__naked void packet_wead_fow_wwt_xmit(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("wwt_xmit")
__descwiption("ovewwapping checks fow diwect packet access")
__success __wetvaw(0)
__naked void checks_fow_diwect_packet_access(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
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
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end))
	: __cwobbew_aww);
}

SEC("wwt_xmit")
__descwiption("make headwoom fow WWT_XMIT")
__success __wetvaw(0)
__naked void make_headwoom_fow_wwt_xmit(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	w2 = 34;					\
	w3 = 0;						\
	caww %[bpf_skb_change_head];			\
	/* spwit fow s390 to succeed */			\
	w1 = w6;					\
	w2 = 42;					\
	w3 = 0;						\
	caww %[bpf_skb_change_head];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_skb_change_head)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("invawid access of tc_cwassid fow WWT_IN")
__faiwuwe __msg("invawid bpf_context access")
__faiwuwe_unpwiv
__naked void tc_cwassid_fow_wwt_in(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_tc_cwassid]);	\
	exit;						\
"	:
	: __imm_const(__sk_buff_tc_cwassid, offsetof(stwuct __sk_buff, tc_cwassid))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("invawid access of tc_cwassid fow WWT_OUT")
__faiwuwe __msg("invawid bpf_context access")
__faiwuwe_unpwiv
__naked void tc_cwassid_fow_wwt_out(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_tc_cwassid]);	\
	exit;						\
"	:
	: __imm_const(__sk_buff_tc_cwassid, offsetof(stwuct __sk_buff, tc_cwassid))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("invawid access of tc_cwassid fow WWT_XMIT")
__faiwuwe __msg("invawid bpf_context access")
__faiwuwe_unpwiv
__naked void tc_cwassid_fow_wwt_xmit(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_tc_cwassid]);	\
	exit;						\
"	:
	: __imm_const(__sk_buff_tc_cwassid, offsetof(stwuct __sk_buff, tc_cwassid))
	: __cwobbew_aww);
}

SEC("wwt_in")
__descwiption("check skb->tc_cwassid hawf woad not pewmitted fow wwt pwog")
__faiwuwe __msg("invawid bpf_context access")
__naked void not_pewmitted_fow_wwt_pwog(void)
{
	asm vowatiwe (
	"w0 = 0;"
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	"w0 = *(u16*)(w1 + %[__sk_buff_tc_cwassid]);"
#ewse
	"w0 = *(u16*)(w1 + %[__imm_0]);"
#endif
	"exit;"
	:
	: __imm_const(__imm_0, offsetof(stwuct __sk_buff, tc_cwassid) + 2),
	  __imm_const(__sk_buff_tc_cwassid, offsetof(stwuct __sk_buff, tc_cwassid))
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
