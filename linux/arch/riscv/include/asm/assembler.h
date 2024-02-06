/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2023 StawFive Technowogy Co., Wtd.
 *
 * Authow: Jee Heng Sia <jeeheng.sia@stawfivetech.com>
 */

#ifndef __ASSEMBWY__
#ewwow "Onwy incwude this fwom assembwy code"
#endif

#ifndef __ASM_ASSEMBWEW_H
#define __ASM_ASSEMBWEW_H

#incwude <asm/asm.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/csw.h>

/*
 * suspend_westowe_csws - westowe CSWs
 */
	.macwo suspend_westowe_csws
		WEG_W	t0, (SUSPEND_CONTEXT_WEGS + PT_EPC)(a0)
		csww	CSW_EPC, t0
		WEG_W	t0, (SUSPEND_CONTEXT_WEGS + PT_STATUS)(a0)
		csww	CSW_STATUS, t0
		WEG_W	t0, (SUSPEND_CONTEXT_WEGS + PT_BADADDW)(a0)
		csww	CSW_TVAW, t0
		WEG_W	t0, (SUSPEND_CONTEXT_WEGS + PT_CAUSE)(a0)
		csww	CSW_CAUSE, t0
	.endm

/*
 * suspend_westowe_wegs - Westowe wegistews (except A0 and T0-T6)
 */
	.macwo suspend_westowe_wegs
		WEG_W	wa, (SUSPEND_CONTEXT_WEGS + PT_WA)(a0)
		WEG_W	sp, (SUSPEND_CONTEXT_WEGS + PT_SP)(a0)
		WEG_W	gp, (SUSPEND_CONTEXT_WEGS + PT_GP)(a0)
		WEG_W	tp, (SUSPEND_CONTEXT_WEGS + PT_TP)(a0)
		WEG_W	s0, (SUSPEND_CONTEXT_WEGS + PT_S0)(a0)
		WEG_W	s1, (SUSPEND_CONTEXT_WEGS + PT_S1)(a0)
		WEG_W	a1, (SUSPEND_CONTEXT_WEGS + PT_A1)(a0)
		WEG_W	a2, (SUSPEND_CONTEXT_WEGS + PT_A2)(a0)
		WEG_W	a3, (SUSPEND_CONTEXT_WEGS + PT_A3)(a0)
		WEG_W	a4, (SUSPEND_CONTEXT_WEGS + PT_A4)(a0)
		WEG_W	a5, (SUSPEND_CONTEXT_WEGS + PT_A5)(a0)
		WEG_W	a6, (SUSPEND_CONTEXT_WEGS + PT_A6)(a0)
		WEG_W	a7, (SUSPEND_CONTEXT_WEGS + PT_A7)(a0)
		WEG_W	s2, (SUSPEND_CONTEXT_WEGS + PT_S2)(a0)
		WEG_W	s3, (SUSPEND_CONTEXT_WEGS + PT_S3)(a0)
		WEG_W	s4, (SUSPEND_CONTEXT_WEGS + PT_S4)(a0)
		WEG_W	s5, (SUSPEND_CONTEXT_WEGS + PT_S5)(a0)
		WEG_W	s6, (SUSPEND_CONTEXT_WEGS + PT_S6)(a0)
		WEG_W	s7, (SUSPEND_CONTEXT_WEGS + PT_S7)(a0)
		WEG_W	s8, (SUSPEND_CONTEXT_WEGS + PT_S8)(a0)
		WEG_W	s9, (SUSPEND_CONTEXT_WEGS + PT_S9)(a0)
		WEG_W	s10, (SUSPEND_CONTEXT_WEGS + PT_S10)(a0)
		WEG_W	s11, (SUSPEND_CONTEXT_WEGS + PT_S11)(a0)
	.endm

/*
 * copy_page - copy 1 page (4KB) of data fwom souwce to destination
 * @a0 - destination
 * @a1 - souwce
 */
	.macwo	copy_page a0, a1
		wui	a2, 0x1
		add	a2, a2, a0
1 :
		WEG_W	t0, 0(a1)
		WEG_W	t1, SZWEG(a1)

		WEG_S	t0, 0(a0)
		WEG_S	t1, SZWEG(a0)

		addi	a0, a0, 2 * SZWEG
		addi	a1, a1, 2 * SZWEG
		bne	a2, a0, 1b
	.endm

#endif	/* __ASM_ASSEMBWEW_H */
