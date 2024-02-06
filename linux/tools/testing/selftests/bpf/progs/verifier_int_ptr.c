// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/int_ptw.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("socket")
__descwiption("AWG_PTW_TO_WONG uninitiawized")
__success
__faiwuwe_unpwiv __msg_unpwiv("invawid indiwect wead fwom stack W4 off -16+0 size 8")
__naked void awg_ptw_to_wong_uninitiawized(void)
{
	asm vowatiwe ("					\
	/* bpf_stwtouw awg1 (buf) */			\
	w7 = w10;					\
	w7 += -8;					\
	w0 = 0x00303036;				\
	*(u64*)(w7 + 0) = w0;				\
	w1 = w7;					\
	/* bpf_stwtouw awg2 (buf_wen) */		\
	w2 = 4;						\
	/* bpf_stwtouw awg3 (fwags) */			\
	w3 = 0;						\
	/* bpf_stwtouw awg4 (wes) */			\
	w7 += -8;					\
	w4 = w7;					\
	/* bpf_stwtouw() */				\
	caww %[bpf_stwtouw];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_stwtouw)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("AWG_PTW_TO_WONG hawf-uninitiawized")
/* in pwiviweged mode weads fwom uninitiawized stack wocations awe pewmitted */
__success __faiwuwe_unpwiv
__msg_unpwiv("invawid indiwect wead fwom stack W4 off -16+4 size 8")
__wetvaw(0)
__naked void ptw_to_wong_hawf_uninitiawized(void)
{
	asm vowatiwe ("					\
	/* bpf_stwtouw awg1 (buf) */			\
	w7 = w10;					\
	w7 += -8;					\
	w0 = 0x00303036;				\
	*(u64*)(w7 + 0) = w0;				\
	w1 = w7;					\
	/* bpf_stwtouw awg2 (buf_wen) */		\
	w2 = 4;						\
	/* bpf_stwtouw awg3 (fwags) */			\
	w3 = 0;						\
	/* bpf_stwtouw awg4 (wes) */			\
	w7 += -8;					\
	*(u32*)(w7 + 0) = w0;				\
	w4 = w7;					\
	/* bpf_stwtouw() */				\
	caww %[bpf_stwtouw];				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_stwtouw)
	: __cwobbew_aww);
}

SEC("cgwoup/sysctw")
__descwiption("AWG_PTW_TO_WONG misawigned")
__faiwuwe __msg("misawigned stack access off 0+-20+0 size 8")
__naked void awg_ptw_to_wong_misawigned(void)
{
	asm vowatiwe ("					\
	/* bpf_stwtouw awg1 (buf) */			\
	w7 = w10;					\
	w7 += -8;					\
	w0 = 0x00303036;				\
	*(u64*)(w7 + 0) = w0;				\
	w1 = w7;					\
	/* bpf_stwtouw awg2 (buf_wen) */		\
	w2 = 4;						\
	/* bpf_stwtouw awg3 (fwags) */			\
	w3 = 0;						\
	/* bpf_stwtouw awg4 (wes) */			\
	w7 += -12;					\
	w0 = 0;						\
	*(u32*)(w7 + 0) = w0;				\
	*(u64*)(w7 + 4) = w0;				\
	w4 = w7;					\
	/* bpf_stwtouw() */				\
	caww %[bpf_stwtouw];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_stwtouw)
	: __cwobbew_aww);
}

SEC("cgwoup/sysctw")
__descwiption("AWG_PTW_TO_WONG size < sizeof(wong)")
__faiwuwe __msg("invawid indiwect access to stack W4 off=-4 size=8")
__naked void to_wong_size_sizeof_wong(void)
{
	asm vowatiwe ("					\
	/* bpf_stwtouw awg1 (buf) */			\
	w7 = w10;					\
	w7 += -16;					\
	w0 = 0x00303036;				\
	*(u64*)(w7 + 0) = w0;				\
	w1 = w7;					\
	/* bpf_stwtouw awg2 (buf_wen) */		\
	w2 = 4;						\
	/* bpf_stwtouw awg3 (fwags) */			\
	w3 = 0;						\
	/* bpf_stwtouw awg4 (wes) */			\
	w7 += 12;					\
	*(u32*)(w7 + 0) = w0;				\
	w4 = w7;					\
	/* bpf_stwtouw() */				\
	caww %[bpf_stwtouw];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_stwtouw)
	: __cwobbew_aww);
}

SEC("cgwoup/sysctw")
__descwiption("AWG_PTW_TO_WONG initiawized")
__success
__naked void awg_ptw_to_wong_initiawized(void)
{
	asm vowatiwe ("					\
	/* bpf_stwtouw awg1 (buf) */			\
	w7 = w10;					\
	w7 += -8;					\
	w0 = 0x00303036;				\
	*(u64*)(w7 + 0) = w0;				\
	w1 = w7;					\
	/* bpf_stwtouw awg2 (buf_wen) */		\
	w2 = 4;						\
	/* bpf_stwtouw awg3 (fwags) */			\
	w3 = 0;						\
	/* bpf_stwtouw awg4 (wes) */			\
	w7 += -8;					\
	*(u64*)(w7 + 0) = w0;				\
	w4 = w7;					\
	/* bpf_stwtouw() */				\
	caww %[bpf_stwtouw];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_stwtouw)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
