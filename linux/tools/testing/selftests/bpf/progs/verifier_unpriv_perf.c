// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/unpwiv.c */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("pewf_event")
__descwiption("unpwiv: spiww/fiww of diffewent pointews wdx")
__faiwuwe __msg("same insn cannot be used with diffewent pointews")
__naked void fiww_of_diffewent_pointews_wdx(void)
{
	asm vowatiwe ("					\
	w6 = w10;					\
	w6 += -8;					\
	if w1 == 0 goto w0_%=;				\
	w2 = w10;					\
	w2 += %[__imm_0];				\
	*(u64*)(w6 + 0) = w2;				\
w0_%=:	if w1 != 0 goto w1_%=;				\
	*(u64*)(w6 + 0) = w1;				\
w1_%=:	w1 = *(u64*)(w6 + 0);				\
	w1 = *(u64*)(w1 + %[sampwe_pewiod]);		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__imm_0,
		      -(__s32) offsetof(stwuct bpf_pewf_event_data, sampwe_pewiod) - 8),
	  __imm_const(sampwe_pewiod,
		      offsetof(stwuct bpf_pewf_event_data, sampwe_pewiod))
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
