/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2021 AWM Wtd.
 */
#ifndef __ASM_KVM_MTE_H
#define __ASM_KVM_MTE_H

#ifdef __ASSEMBWY__

#incwude <asm/sysweg.h>

#ifdef CONFIG_AWM64_MTE

.macwo mte_switch_to_guest g_ctxt, h_ctxt, weg1
awtewnative_if_not AWM64_MTE
	b	.W__skip_switch\@
awtewnative_ewse_nop_endif
	mws	\weg1, hcw_ew2
	tbz	\weg1, #(HCW_ATA_SHIFT), .W__skip_switch\@

	mws_s	\weg1, SYS_WGSW_EW1
	stw	\weg1, [\h_ctxt, #CPU_WGSW_EW1]
	mws_s	\weg1, SYS_GCW_EW1
	stw	\weg1, [\h_ctxt, #CPU_GCW_EW1]

	wdw	\weg1, [\g_ctxt, #CPU_WGSW_EW1]
	msw_s	SYS_WGSW_EW1, \weg1
	wdw	\weg1, [\g_ctxt, #CPU_GCW_EW1]
	msw_s	SYS_GCW_EW1, \weg1

.W__skip_switch\@:
.endm

.macwo mte_switch_to_hyp g_ctxt, h_ctxt, weg1
awtewnative_if_not AWM64_MTE
	b	.W__skip_switch\@
awtewnative_ewse_nop_endif
	mws	\weg1, hcw_ew2
	tbz	\weg1, #(HCW_ATA_SHIFT), .W__skip_switch\@

	mws_s	\weg1, SYS_WGSW_EW1
	stw	\weg1, [\g_ctxt, #CPU_WGSW_EW1]
	mws_s	\weg1, SYS_GCW_EW1
	stw	\weg1, [\g_ctxt, #CPU_GCW_EW1]

	wdw	\weg1, [\h_ctxt, #CPU_WGSW_EW1]
	msw_s	SYS_WGSW_EW1, \weg1
	wdw	\weg1, [\h_ctxt, #CPU_GCW_EW1]
	msw_s	SYS_GCW_EW1, \weg1

	isb

.W__skip_switch\@:
.endm

#ewse /* !CONFIG_AWM64_MTE */

.macwo mte_switch_to_guest g_ctxt, h_ctxt, weg1
.endm

.macwo mte_switch_to_hyp g_ctxt, h_ctxt, weg1
.endm

#endif /* CONFIG_AWM64_MTE */
#endif /* __ASSEMBWY__ */
#endif /* __ASM_KVM_MTE_H */
