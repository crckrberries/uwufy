// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/xdp_diwect_packet_access.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end mangwing, bad access 1")
__faiwuwe __msg("W3 pointew awithmetic on pkt_end")
__naked void end_mangwing_bad_access_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	w3 += 8;					\
	if w1 > w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end mangwing, bad access 2")
__faiwuwe __msg("W3 pointew awithmetic on pkt_end")
__naked void end_mangwing_bad_access_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	w3 -= 8;					\
	if w1 > w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' > pkt_end, cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void end_cownew_case_good_access_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 > w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' > pkt_end, bad access 1")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_end_bad_access_1_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 > w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 4);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' > pkt_end, bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_end_bad_access_2_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 > w3 goto w0_%=;				\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' > pkt_end, cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 9;					\
	if w1 > w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 9);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' > pkt_end, cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w1 > w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 7);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end > pkt_data', good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void end_pkt_data_good_access_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 > w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u32*)(w1 - 5);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end > pkt_data', cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 6;					\
	if w3 > w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 6);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end > pkt_data', bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_2_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 > w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end > pkt_data', cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_cownew_case_good_access_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w3 > w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 7);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end > pkt_data', cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 > w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' < pkt_end, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_pkt_end_good_access_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 < w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u32*)(w1 - 5);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' < pkt_end, cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_3(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 6;					\
	if w1 < w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 6);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' < pkt_end, bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_end_bad_access_2_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 < w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' < pkt_end, cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void end_cownew_case_good_access_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w1 < w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 7);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' < pkt_end, cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_3(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 < w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end < pkt_data', cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_cownew_case_good_access_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 < w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end < pkt_data', bad access 1")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_1_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 < w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 4);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end < pkt_data', bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_2_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 < w1 goto w0_%=;				\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end < pkt_data', cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_4(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 9;					\
	if w3 < w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 9);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end < pkt_data', cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_4(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w3 < w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 7);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' >= pkt_end, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_pkt_end_good_access_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 >= w3 goto w0_%=;				\
	w0 = *(u32*)(w1 - 5);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' >= pkt_end, cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_5(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 6;					\
	if w1 >= w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 6);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' >= pkt_end, bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_end_bad_access_2_3(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 >= w3 goto w0_%=;				\
w0_%=:	w0 = *(u32*)(w1 - 5);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' >= pkt_end, cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void end_cownew_case_good_access_3(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w1 >= w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 7);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' >= pkt_end, cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_5(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 >= w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end >= pkt_data', cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_cownew_case_good_access_3(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 >= w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end >= pkt_data', bad access 1")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_1_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 >= w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 4);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end >= pkt_data', bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_2_3(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 >= w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end >= pkt_data', cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_6(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 9;					\
	if w3 >= w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 9);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end >= pkt_data', cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_6(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w3 >= w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 7);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' <= pkt_end, cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void end_cownew_case_good_access_4(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 <= w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' <= pkt_end, bad access 1")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_end_bad_access_1_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 <= w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 4);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' <= pkt_end, bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_end_bad_access_2_4(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 <= w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' <= pkt_end, cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_7(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 9;					\
	if w1 <= w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 9);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data' <= pkt_end, cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_7(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w1 <= w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 7);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end <= pkt_data', good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void end_pkt_data_good_access_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 <= w1 goto w0_%=;				\
	w0 = *(u32*)(w1 - 5);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end <= pkt_data', cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_8(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 6;					\
	if w3 <= w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 6);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end <= pkt_data', bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_2_4(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 <= w1 goto w0_%=;				\
w0_%=:	w0 = *(u32*)(w1 - 5);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end <= pkt_data', cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_cownew_case_good_access_4(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w3 <= w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 7);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_end <= pkt_data', cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_8(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data_end]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 <= w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_end, offsetof(stwuct xdp_md, data_end))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' > pkt_data, cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_cownew_case_good_access_5(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 > w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' > pkt_data, bad access 1")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_1_3(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 > w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 4);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' > pkt_data, bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_2_5(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 > w3 goto w0_%=;				\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' > pkt_data, cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_9(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 9;					\
	if w1 > w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 9);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' > pkt_data, cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_9(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w1 > w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 7);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data > pkt_meta', good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_pkt_meta_good_access_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 > w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u32*)(w1 - 5);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data > pkt_meta', cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_10(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 6;					\
	if w3 > w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 6);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data > pkt_meta', bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_meta_bad_access_2_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 > w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data > pkt_meta', cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void meta_cownew_case_good_access_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w3 > w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 7);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data > pkt_meta', cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_10(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 > w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' < pkt_data, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void meta_pkt_data_good_access_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 < w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u32*)(w1 - 5);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' < pkt_data, cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_11(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 6;					\
	if w1 < w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 6);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' < pkt_data, bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_2_6(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 < w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' < pkt_data, cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_cownew_case_good_access_6(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w1 < w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 7);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' < pkt_data, cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_11(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 < w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data < pkt_meta', cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void meta_cownew_case_good_access_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 < w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data < pkt_meta', bad access 1")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_meta_bad_access_1_1(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 < w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 4);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data < pkt_meta', bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_meta_bad_access_2_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 < w1 goto w0_%=;				\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data < pkt_meta', cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_12(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 9;					\
	if w3 < w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 9);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data < pkt_meta', cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_12(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w3 < w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 7);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' >= pkt_data, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void meta_pkt_data_good_access_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 >= w3 goto w0_%=;				\
	w0 = *(u32*)(w1 - 5);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' >= pkt_data, cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_13(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 6;					\
	if w1 >= w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 6);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' >= pkt_data, bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_2_7(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 >= w3 goto w0_%=;				\
w0_%=:	w0 = *(u32*)(w1 - 5);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' >= pkt_data, cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_cownew_case_good_access_7(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w1 >= w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 7);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' >= pkt_data, cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_13(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 >= w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data >= pkt_meta', cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void meta_cownew_case_good_access_3(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 >= w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data >= pkt_meta', bad access 1")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_meta_bad_access_1_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 >= w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 4);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data >= pkt_meta', bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_meta_bad_access_2_3(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 >= w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data >= pkt_meta', cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_14(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 9;					\
	if w3 >= w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 9);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data >= pkt_meta', cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_14(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w3 >= w1 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 7);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' <= pkt_data, cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_cownew_case_good_access_8(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 <= w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 8);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' <= pkt_data, bad access 1")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_1_4(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 <= w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 4);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' <= pkt_data, bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_data_bad_access_2_8(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w1 <= w3 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' <= pkt_data, cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_15(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 9;					\
	if w1 <= w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 9);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_meta' <= pkt_data, cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_15(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w1 <= w3 goto w0_%=;				\
	goto w1_%=;					\
w0_%=:	w0 = *(u64*)(w1 - 7);				\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data <= pkt_meta', good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void data_pkt_meta_good_access_2(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 <= w1 goto w0_%=;				\
	w0 = *(u32*)(w1 - 5);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data <= pkt_meta', cownew case -1, bad access")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_bad_access_16(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 6;					\
	if w3 <= w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 6);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data <= pkt_meta', bad access 2")
__faiwuwe __msg("W1 offset is outside of the packet")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void pkt_meta_bad_access_2_4(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 <= w1 goto w0_%=;				\
w0_%=:	w0 = *(u32*)(w1 - 5);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data <= pkt_meta', cownew case, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void meta_cownew_case_good_access_4(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 7;					\
	if w3 <= w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 7);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("XDP pkt wead, pkt_data <= pkt_meta', cownew case +1, good access")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void cownew_case_1_good_access_16(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[xdp_md_data_meta]);		\
	w3 = *(u32*)(w1 + %[xdp_md_data]);		\
	w1 = w2;					\
	w1 += 8;					\
	if w3 <= w1 goto w0_%=;				\
	w0 = *(u64*)(w1 - 8);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(xdp_md_data, offsetof(stwuct xdp_md, data)),
	  __imm_const(xdp_md_data_meta, offsetof(stwuct xdp_md, data_meta))
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
