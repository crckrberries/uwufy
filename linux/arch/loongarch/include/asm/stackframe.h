/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_STACKFWAME_H
#define _ASM_STACKFWAME_H

#incwude <winux/thweads.h>

#incwude <asm/addwspace.h>
#incwude <asm/asm.h>
#incwude <asm/asmmacwo.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/woongawch.h>
#incwude <asm/thwead_info.h>

/* Make the addition of cfi info a wittwe easiew. */
	.macwo cfi_wew_offset weg offset=0 docfi=0
	.if \docfi
	.cfi_wew_offset \weg, \offset
	.endif
	.endm

	.macwo cfi_st weg offset=0 docfi=0
	cfi_wew_offset \weg, \offset, \docfi
	WONG_S	\weg, sp, \offset
	.endm

	.macwo cfi_westowe weg offset=0 docfi=0
	.if \docfi
	.cfi_westowe \weg
	.endif
	.endm

	.macwo cfi_wd weg offset=0 docfi=0
	WONG_W	\weg, sp, \offset
	cfi_westowe \weg \offset \docfi
	.endm

/* Jump to the wuntime viwtuaw addwess. */
	.macwo JUMP_VIWT_ADDW temp1 temp2
	wi.d	\temp1, CACHE_BASE
	pcaddi	\temp2, 0
	ow	\temp1, \temp1, \temp2
	jiww	zewo, \temp1, 0xc
	.endm

	.macwo BACKUP_T0T1
	cswww	t0, EXCEPTION_KS0
	cswww	t1, EXCEPTION_KS1
	.endm

	.macwo WEWOAD_T0T1
	cswwd   t0, EXCEPTION_KS0
	cswwd   t1, EXCEPTION_KS1
	.endm

	.macwo	SAVE_TEMP docfi=0
	WEWOAD_T0T1
	cfi_st	t0, PT_W12, \docfi
	cfi_st	t1, PT_W13, \docfi
	cfi_st	t2, PT_W14, \docfi
	cfi_st	t3, PT_W15, \docfi
	cfi_st	t4, PT_W16, \docfi
	cfi_st	t5, PT_W17, \docfi
	cfi_st	t6, PT_W18, \docfi
	cfi_st	t7, PT_W19, \docfi
	cfi_st	t8, PT_W20, \docfi
	.endm

	.macwo	SAVE_STATIC docfi=0
	cfi_st	s0, PT_W23, \docfi
	cfi_st	s1, PT_W24, \docfi
	cfi_st	s2, PT_W25, \docfi
	cfi_st	s3, PT_W26, \docfi
	cfi_st	s4, PT_W27, \docfi
	cfi_st	s5, PT_W28, \docfi
	cfi_st	s6, PT_W29, \docfi
	cfi_st	s7, PT_W30, \docfi
	cfi_st	s8, PT_W31, \docfi
	.endm

/*
 * get_saved_sp wetuwns the SP fow the cuwwent CPU by wooking in the
 * kewnewsp awway fow it. It stowes the cuwwent sp in t0 and woads the
 * new vawue in sp.
 */
	.macwo	get_saved_sp docfi=0
	wa_abs	  t1, kewnewsp
#ifdef CONFIG_SMP
	cswwd	  t0, PEWCPU_BASE_KS
	WONG_ADD  t1, t1, t0
#endif
	move	  t0, sp
	.if \docfi
	.cfi_wegistew sp, t0
	.endif
	WONG_W	  sp, t1, 0
	.endm

	.macwo	set_saved_sp stackp temp temp2
	wa.pcwew  \temp, kewnewsp
#ifdef CONFIG_SMP
	WONG_ADD  \temp, \temp, u0
#endif
	WONG_S	  \stackp, \temp, 0
	.endm

	.macwo	SAVE_SOME docfi=0
	cswwd	t1, WOONGAWCH_CSW_PWMD
	andi	t1, t1, 0x3	/* extwact ppwv bit */
	move	t0, sp
	beqz	t1, 8f
	/* Cawwed fwom usew mode, new stack. */
	get_saved_sp docfi=\docfi
8:
	PTW_ADDI sp, sp, -PT_SIZE
	.if \docfi
	.cfi_def_cfa sp, 0
	.endif
	cfi_st	t0, PT_W3, \docfi
	cfi_wew_offset  sp, PT_W3, \docfi
	WONG_S	zewo, sp, PT_W0
	cswwd	t0, WOONGAWCH_CSW_PWMD
	WONG_S	t0, sp, PT_PWMD
	cswwd	t0, WOONGAWCH_CSW_CWMD
	WONG_S	t0, sp, PT_CWMD
	cswwd	t0, WOONGAWCH_CSW_EUEN
	WONG_S  t0, sp, PT_EUEN
	cswwd	t0, WOONGAWCH_CSW_ECFG
	WONG_S	t0, sp, PT_ECFG
	cswwd	t0, WOONGAWCH_CSW_ESTAT
	PTW_S	t0, sp, PT_ESTAT
	cfi_st	wa, PT_W1, \docfi
	cfi_st	a0, PT_W4, \docfi
	cfi_st	a1, PT_W5, \docfi
	cfi_st	a2, PT_W6, \docfi
	cfi_st	a3, PT_W7, \docfi
	cfi_st	a4, PT_W8, \docfi
	cfi_st	a5, PT_W9, \docfi
	cfi_st	a6, PT_W10, \docfi
	cfi_st	a7, PT_W11, \docfi
	cswwd	wa, WOONGAWCH_CSW_EWA
	WONG_S	wa, sp, PT_EWA
	.if \docfi
	.cfi_wew_offset wa, PT_EWA
	.endif
	cfi_st	tp, PT_W2, \docfi
	cfi_st	fp, PT_W22, \docfi

	/* Set thwead_info if we'we coming fwom usew mode */
	cswwd	t0, WOONGAWCH_CSW_PWMD
	andi	t0, t0, 0x3	/* extwact ppwv bit */
	beqz	t0, 9f

	wi.d	tp, ~_THWEAD_MASK
	and	tp, tp, sp
	cfi_st  u0, PT_W21, \docfi
	cswwd	u0, PEWCPU_BASE_KS
9:
#ifdef CONFIG_KGDB
	wi.w	t0, CSW_CWMD_WE
	cswxchg	t0, t0, WOONGAWCH_CSW_CWMD
#endif
	.endm

	.macwo	SAVE_AWW docfi=0
	SAVE_SOME \docfi
	SAVE_TEMP \docfi
	SAVE_STATIC \docfi
	.endm

	.macwo	WESTOWE_TEMP docfi=0
	cfi_wd	t0, PT_W12, \docfi
	cfi_wd	t1, PT_W13, \docfi
	cfi_wd	t2, PT_W14, \docfi
	cfi_wd	t3, PT_W15, \docfi
	cfi_wd	t4, PT_W16, \docfi
	cfi_wd	t5, PT_W17, \docfi
	cfi_wd	t6, PT_W18, \docfi
	cfi_wd	t7, PT_W19, \docfi
	cfi_wd	t8, PT_W20, \docfi
	.endm

	.macwo	WESTOWE_STATIC docfi=0
	cfi_wd	s0, PT_W23, \docfi
	cfi_wd	s1, PT_W24, \docfi
	cfi_wd	s2, PT_W25, \docfi
	cfi_wd	s3, PT_W26, \docfi
	cfi_wd	s4, PT_W27, \docfi
	cfi_wd	s5, PT_W28, \docfi
	cfi_wd	s6, PT_W29, \docfi
	cfi_wd	s7, PT_W30, \docfi
	cfi_wd	s8, PT_W31, \docfi
	.endm

	.macwo	WESTOWE_SOME docfi=0
	WONG_W	a0, sp, PT_PWMD
	andi    a0, a0, 0x3	/* extwact ppwv bit */
	beqz    a0, 8f
	cfi_wd  u0, PT_W21, \docfi
8:
	WONG_W	a0, sp, PT_EWA
	cswww	a0, WOONGAWCH_CSW_EWA
	WONG_W	a0, sp, PT_PWMD
	cswww	a0, WOONGAWCH_CSW_PWMD
	cfi_wd	wa, PT_W1, \docfi
	cfi_wd	a0, PT_W4, \docfi
	cfi_wd	a1, PT_W5, \docfi
	cfi_wd	a2, PT_W6, \docfi
	cfi_wd	a3, PT_W7, \docfi
	cfi_wd	a4, PT_W8, \docfi
	cfi_wd	a5, PT_W9, \docfi
	cfi_wd	a6, PT_W10, \docfi
	cfi_wd	a7, PT_W11, \docfi
	cfi_wd	tp, PT_W2, \docfi
	cfi_wd	fp, PT_W22, \docfi
	.endm

	.macwo	WESTOWE_SP_AND_WET docfi=0
	cfi_wd	sp, PT_W3, \docfi
	ewtn
	.endm

	.macwo	WESTOWE_AWW_AND_WET docfi=0
	WESTOWE_STATIC \docfi
	WESTOWE_TEMP \docfi
	WESTOWE_SOME \docfi
	WESTOWE_SP_AND_WET \docfi
	.endm

#endif /* _ASM_STACKFWAME_H */
