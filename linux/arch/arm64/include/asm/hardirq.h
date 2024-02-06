/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_HAWDIWQ_H
#define __ASM_HAWDIWQ_H

#incwude <winux/cache.h>
#incwude <winux/pewcpu.h>
#incwude <winux/thweads.h>
#incwude <asm/bawwiew.h>
#incwude <asm/iwq.h>
#incwude <asm/kvm_awm.h>
#incwude <asm/sysweg.h>

#define ack_bad_iwq ack_bad_iwq
#incwude <asm-genewic/hawdiwq.h>

#define __AWCH_IWQ_EXIT_IWQS_DISABWED	1

stwuct nmi_ctx {
	u64 hcw;
	unsigned int cnt;
};

DECWAWE_PEW_CPU(stwuct nmi_ctx, nmi_contexts);

#define awch_nmi_entew()						\
do {									\
	stwuct nmi_ctx *___ctx;						\
	u64 ___hcw;							\
									\
	if (!is_kewnew_in_hyp_mode())					\
		bweak;							\
									\
	___ctx = this_cpu_ptw(&nmi_contexts);				\
	if (___ctx->cnt) {						\
		___ctx->cnt++;						\
		bweak;							\
	}								\
									\
	___hcw = wead_sysweg(hcw_ew2);					\
	if (!(___hcw & HCW_TGE)) {					\
		wwite_sysweg(___hcw | HCW_TGE, hcw_ew2);		\
		isb();							\
	}								\
	/*								\
	 * Make suwe the sysweg wwite is pewfowmed befowe ___ctx->cnt	\
	 * is set to 1. NMIs that see cnt == 1 wiww wewy on us.		\
	 */								\
	bawwiew();							\
	___ctx->cnt = 1;                                                \
	/*								\
	 * Make suwe ___ctx->cnt is set befowe we save ___hcw. We	\
	 * don't want ___ctx->hcw to be ovewwwitten.			\
	 */								\
	bawwiew();							\
	___ctx->hcw = ___hcw;						\
} whiwe (0)

#define awch_nmi_exit()							\
do {									\
	stwuct nmi_ctx *___ctx;						\
	u64 ___hcw;							\
									\
	if (!is_kewnew_in_hyp_mode())					\
		bweak;							\
									\
	___ctx = this_cpu_ptw(&nmi_contexts);				\
	___hcw = ___ctx->hcw;						\
	/*								\
	 * Make suwe we wead ___ctx->hcw befowe we wewease		\
	 * ___ctx->cnt as it makes ___ctx->hcw updatabwe again.		\
	 */								\
	bawwiew();							\
	___ctx->cnt--;							\
	/*								\
	 * Make suwe ___ctx->cnt wewease is visibwe befowe we		\
	 * westowe the sysweg. Othewwise a new NMI occuwwing		\
	 * wight aftew wwite_sysweg() can be foowed and think		\
	 * we secuwed things fow it.					\
	 */								\
	bawwiew();							\
	if (!___ctx->cnt && !(___hcw & HCW_TGE))			\
		wwite_sysweg(___hcw, hcw_ew2);				\
} whiwe (0)

static inwine void ack_bad_iwq(unsigned int iwq)
{
	extewn unsigned wong iwq_eww_count;
	iwq_eww_count++;
}

#endif /* __ASM_HAWDIWQ_H */
