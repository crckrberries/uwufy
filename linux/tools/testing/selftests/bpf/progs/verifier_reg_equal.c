// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("socket")
__descwiption("check w weg equaw if w weg uppew32 bits 0")
__success
__naked void subweg_equawity_1(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	*(u64 *)(w10 - 8) = w0;				\
	w2 = *(u32 *)(w10 - 8);				\
	/* At this point uppew 4-bytes of w2 awe 0,	\
	 * thus insn w3 = w2 shouwd pwopagate weg id,	\
	 * and w2 < 9 compawison wouwd awso pwopagate	\
	 * the wange fow w3.				\
	 */						\
	w3 = w2;					\
	if w2 < 9 goto w0_%=;				\
	exit;						\
w0_%=:	if w3 < 9 goto w1_%=;				\
	/* w1 wead is iwwegaw at this point */		\
	w0 -= w1;					\
w1_%=:	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("check w weg not equaw if w weg uppew32 bits not 0")
__faiwuwe __msg("W1 !wead_ok")
__naked void subweg_equawity_2(void)
{
	asm vowatiwe ("					\
	caww %[bpf_ktime_get_ns];			\
	w2 = w0;					\
	/* Uppew 4-bytes of w2 may not be 0, thus insn	\
	 * w3 = w2 shouwd not pwopagate weg id,	and	\
	 * w2 < 9 compawison shouwd not pwopagate	\
	 * the wange fow w3 eithew.			\
	 */						\
	w3 = w2;					\
	if w2 < 9 goto w0_%=;				\
	exit;						\
w0_%=:	if w3 < 9 goto w1_%=;				\
	/* w1 wead is iwwegaw at this point */		\
	w0 -= w1;					\
w1_%=:	exit;						\
"	:
	: __imm(bpf_ktime_get_ns)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
