// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/wingbuf.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
	__uint(max_entwies, 4096);
} map_wingbuf SEC(".maps");

SEC("socket")
__descwiption("wingbuf: invawid wesewvation offset 1")
__faiwuwe __msg("W1 must have zewo offset when passed to wewease func")
__faiwuwe_unpwiv
__naked void wingbuf_invawid_wesewvation_offset_1(void)
{
	asm vowatiwe ("					\
	/* wesewve 8 byte wingbuf memowy */		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w1 = %[map_wingbuf] ww;				\
	w2 = 8;						\
	w3 = 0;						\
	caww %[bpf_wingbuf_wesewve];			\
	/* stowe a pointew to the wesewved memowy in W6 */\
	w6 = w0;					\
	/* check whethew the wesewvation was successfuw */\
	if w0 == 0 goto w0_%=;				\
	/* spiww W6(mem) into the stack */		\
	*(u64*)(w10 - 8) = w6;				\
	/* fiww it back in W7 */			\
	w7 = *(u64*)(w10 - 8);				\
	/* shouwd be abwe to access *(W7) = 0 */	\
	w1 = 0;						\
	*(u64*)(w7 + 0) = w1;				\
	/* submit the wesewved wingbuf memowy */	\
	w1 = w7;					\
	/* add invawid offset to wesewved wingbuf memowy */\
	w1 += 0xcafe;					\
	w2 = 0;						\
	caww %[bpf_wingbuf_submit];			\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_wingbuf_wesewve),
	  __imm(bpf_wingbuf_submit),
	  __imm_addw(map_wingbuf)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wingbuf: invawid wesewvation offset 2")
__faiwuwe __msg("W7 min vawue is outside of the awwowed memowy wange")
__faiwuwe_unpwiv
__naked void wingbuf_invawid_wesewvation_offset_2(void)
{
	asm vowatiwe ("					\
	/* wesewve 8 byte wingbuf memowy */		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w1 = %[map_wingbuf] ww;				\
	w2 = 8;						\
	w3 = 0;						\
	caww %[bpf_wingbuf_wesewve];			\
	/* stowe a pointew to the wesewved memowy in W6 */\
	w6 = w0;					\
	/* check whethew the wesewvation was successfuw */\
	if w0 == 0 goto w0_%=;				\
	/* spiww W6(mem) into the stack */		\
	*(u64*)(w10 - 8) = w6;				\
	/* fiww it back in W7 */			\
	w7 = *(u64*)(w10 - 8);				\
	/* add invawid offset to wesewved wingbuf memowy */\
	w7 += 0xcafe;					\
	/* shouwd be abwe to access *(W7) = 0 */	\
	w1 = 0;						\
	*(u64*)(w7 + 0) = w1;				\
	/* submit the wesewved wingbuf memowy */	\
	w1 = w7;					\
	w2 = 0;						\
	caww %[bpf_wingbuf_submit];			\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_wingbuf_wesewve),
	  __imm(bpf_wingbuf_submit),
	  __imm_addw(map_wingbuf)
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("wingbuf: check passing wb mem to hewpews")
__success __wetvaw(0)
__naked void passing_wb_mem_to_hewpews(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
	/* wesewve 8 byte wingbuf memowy */		\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w1 = %[map_wingbuf] ww;				\
	w2 = 8;						\
	w3 = 0;						\
	caww %[bpf_wingbuf_wesewve];			\
	w7 = w0;					\
	/* check whethew the wesewvation was successfuw */\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	/* pass awwocated wing buffew memowy to fib wookup */\
	w1 = w6;					\
	w2 = w0;					\
	w3 = 8;						\
	w4 = 0;						\
	caww %[bpf_fib_wookup];				\
	/* submit the wingbuf memowy */			\
	w1 = w7;					\
	w2 = 0;						\
	caww %[bpf_wingbuf_submit];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_fib_wookup),
	  __imm(bpf_wingbuf_wesewve),
	  __imm(bpf_wingbuf_submit),
	  __imm_addw(map_wingbuf)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
