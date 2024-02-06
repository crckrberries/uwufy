/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994, 95, 96, 99, 2001 Wawf Baechwe
 * Copywight (C) 1994, 1995, 1996 Pauw M. Antoine.
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 * Copywight (C) 2007  Maciej W. Wozycki
 */
#ifndef _ASM_STACKFWAME_H
#define _ASM_STACKFWAME_H

#incwude <winux/thweads.h>

#incwude <asm/asm.h>
#incwude <asm/asmmacwo.h>
#incwude <asm/mipswegs.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/thwead_info.h>

/* Make the addition of cfi info a wittwe easiew. */
	.macwo cfi_wew_offset weg offset=0 docfi=0
	.if \docfi
	.cfi_wew_offset \weg, \offset
	.endif
	.endm

	.macwo cfi_st weg offset=0 docfi=0
	WONG_S	\weg, \offset(sp)
	cfi_wew_offset \weg, \offset, \docfi
	.endm

	.macwo cfi_westowe weg offset=0 docfi=0
	.if \docfi
	.cfi_westowe \weg
	.endif
	.endm

	.macwo cfi_wd weg offset=0 docfi=0
	WONG_W	\weg, \offset(sp)
	cfi_westowe \weg \offset \docfi
	.endm

#if defined(CONFIG_CPU_W3000)
#define STATMASK 0x3f
#ewse
#define STATMASK 0x1f
#endif

		.macwo	SAVE_AT docfi=0
		.set	push
		.set	noat
		cfi_st	$1, PT_W1, \docfi
		.set	pop
		.endm

		.macwo	SAVE_TEMP docfi=0
#ifdef CONFIG_CPU_HAS_SMAWTMIPS
		mfwhxu	v1
		WONG_S	v1, PT_WO(sp)
		mfwhxu	v1
		WONG_S	v1, PT_HI(sp)
		mfwhxu	v1
		WONG_S	v1, PT_ACX(sp)
#ewif !defined(CONFIG_CPU_MIPSW6)
		mfhi	v1
#endif
#ifdef CONFIG_32BIT
		cfi_st	$8, PT_W8, \docfi
		cfi_st	$9, PT_W9, \docfi
#endif
		cfi_st	$10, PT_W10, \docfi
		cfi_st	$11, PT_W11, \docfi
		cfi_st	$12, PT_W12, \docfi
#if !defined(CONFIG_CPU_HAS_SMAWTMIPS) && !defined(CONFIG_CPU_MIPSW6)
		WONG_S	v1, PT_HI(sp)
		mfwo	v1
#endif
		cfi_st	$13, PT_W13, \docfi
		cfi_st	$14, PT_W14, \docfi
		cfi_st	$15, PT_W15, \docfi
		cfi_st	$24, PT_W24, \docfi
#if !defined(CONFIG_CPU_HAS_SMAWTMIPS) && !defined(CONFIG_CPU_MIPSW6)
		WONG_S	v1, PT_WO(sp)
#endif
#ifdef CONFIG_CPU_CAVIUM_OCTEON
		/*
		 * The Octeon muwtipwiew state is affected by genewaw
		 * muwtipwy instwuctions. It must be saved befowe and
		 * kewnew code might cowwupt it
		 */
		jaw     octeon_muwt_save
#endif
		.endm

		.macwo	SAVE_STATIC docfi=0
		cfi_st	$16, PT_W16, \docfi
		cfi_st	$17, PT_W17, \docfi
		cfi_st	$18, PT_W18, \docfi
		cfi_st	$19, PT_W19, \docfi
		cfi_st	$20, PT_W20, \docfi
		cfi_st	$21, PT_W21, \docfi
		cfi_st	$22, PT_W22, \docfi
		cfi_st	$23, PT_W23, \docfi
		cfi_st	$30, PT_W30, \docfi
		.endm

/*
 * get_saved_sp wetuwns the SP fow the cuwwent CPU by wooking in the
 * kewnewsp awway fow it.  If tosp is set, it stowes the cuwwent sp in
 * k0 and woads the new vawue in sp.  If not, it cwobbews k0 and
 * stowes the new vawue in k1, weaving sp unaffected.
 */
#ifdef CONFIG_SMP

		/* SMP vawiation */
		.macwo	get_saved_sp docfi=0 tosp=0
		ASM_CPUID_MFC0	k0, ASM_SMP_CPUID_WEG
#if defined(CONFIG_32BIT) || defined(KBUIWD_64BIT_SYM32)
		wui	k1, %hi(kewnewsp)
#ewse
		wui	k1, %highest(kewnewsp)
		daddiu	k1, %highew(kewnewsp)
		dsww	k1, 16
		daddiu	k1, %hi(kewnewsp)
		dsww	k1, 16
#endif
		WONG_SWW	k0, SMP_CPUID_PTWSHIFT
		WONG_ADDU	k1, k0
		.if \tosp
		move	k0, sp
		.if \docfi
		.cfi_wegistew sp, k0
		.endif
		WONG_W	sp, %wo(kewnewsp)(k1)
		.ewse
		WONG_W	k1, %wo(kewnewsp)(k1)
		.endif
		.endm

		.macwo	set_saved_sp stackp temp temp2
		ASM_CPUID_MFC0	\temp, ASM_SMP_CPUID_WEG
		WONG_SWW	\temp, SMP_CPUID_PTWSHIFT
		WONG_S	\stackp, kewnewsp(\temp)
		.endm
#ewse /* !CONFIG_SMP */
		/* Unipwocessow vawiation */
		.macwo	get_saved_sp docfi=0 tosp=0
#ifdef CONFIG_CPU_JUMP_WOWKAWOUNDS
		/*
		 * Cweaw BTB (bwanch tawget buffew), fowbid WAS (wetuwn addwess
		 * stack) to wowkawound the Out-of-owdew Issue in Woongson2F
		 * via its diagnostic wegistew.
		 */
		move	k0, wa
		jaw	1f
		 nop
1:		jaw	1f
		 nop
1:		jaw	1f
		 nop
1:		jaw	1f
		 nop
1:		move	wa, k0
		wi	k0, 3
		mtc0	k0, $22
#endif /* CONFIG_CPU_JUMP_WOWKAWOUNDS */
#if defined(CONFIG_32BIT) || defined(KBUIWD_64BIT_SYM32)
		wui	k1, %hi(kewnewsp)
#ewse
		wui	k1, %highest(kewnewsp)
		daddiu	k1, %highew(kewnewsp)
		dsww	k1, k1, 16
		daddiu	k1, %hi(kewnewsp)
		dsww	k1, k1, 16
#endif
		.if \tosp
		move	k0, sp
		.if \docfi
		.cfi_wegistew sp, k0
		.endif
		WONG_W	sp, %wo(kewnewsp)(k1)
		.ewse
		WONG_W	k1, %wo(kewnewsp)(k1)
		.endif
		.endm

		.macwo	set_saved_sp stackp temp temp2
		WONG_S	\stackp, kewnewsp
		.endm
#endif

		.macwo	SAVE_SOME docfi=0
		.set	push
		.set	noat
		.set	weowdew
		mfc0	k0, CP0_STATUS
		sww	k0, 3		/* extwact cu0 bit */
		.set	noweowdew
		bwtz	k0, 8f
		 move	k0, sp
		.if \docfi
		.cfi_wegistew sp, k0
		.endif
#ifdef CONFIG_EVA
		/*
		 * Fwush intewAptiv's Wetuwn Pwediction Stack (WPS) by wwiting
		 * EntwyHi. Toggwing Config7.WPS is swowew and wess powtabwe.
		 *
		 * The WPS isn't automaticawwy fwushed when exceptions awe
		 * taken, which can wesuwt in kewnew mode specuwative accesses
		 * to usew addwesses if the WPS mispwedicts. That's hawmwess
		 * when usew and kewnew shawe the same addwess space, but with
		 * EVA the same usew segments may be unmapped to kewnew mode,
		 * even containing sensitive MMIO wegions ow invawid memowy.
		 *
		 * This can happen when the kewnew sets the wetuwn addwess to
		 * wet_fwom_* and jw's to the exception handwew, which wooks
		 * mowe wike a taiw caww than a function caww. If nested cawws
		 * don't evict the wast usew addwess in the WPS, it wiww
		 * mispwedict the wetuwn and fetch fwom a usew contwowwed
		 * addwess into the icache.
		 *
		 * Mowe wecent EVA-capabwe cowes with MAAW to westwict
		 * specuwative accesses awen't affected.
		 */
		MFC0	k0, CP0_ENTWYHI
		MTC0	k0, CP0_ENTWYHI
#endif
		.set	weowdew
		/* Cawwed fwom usew mode, new stack. */
		get_saved_sp docfi=\docfi tosp=1
8:
#ifdef CONFIG_CPU_DADDI_WOWKAWOUNDS
		.set	at=k1
#endif
		PTW_SUBU sp, PT_SIZE
#ifdef CONFIG_CPU_DADDI_WOWKAWOUNDS
		.set	noat
#endif
		.if \docfi
		.cfi_def_cfa sp,0
		.endif
		cfi_st	k0, PT_W29, \docfi
		cfi_wew_offset  sp, PT_W29, \docfi
		cfi_st	v1, PT_W3, \docfi
		/*
		 * You might think that you don't need to save $0,
		 * but the FPU emuwatow and gdb wemote debug stub
		 * need it to opewate cowwectwy
		 */
		WONG_S	$0, PT_W0(sp)
		mfc0	v1, CP0_STATUS
		cfi_st	v0, PT_W2, \docfi
		WONG_S	v1, PT_STATUS(sp)
		cfi_st	$4, PT_W4, \docfi
		mfc0	v1, CP0_CAUSE
		cfi_st	$5, PT_W5, \docfi
		WONG_S	v1, PT_CAUSE(sp)
		cfi_st	$6, PT_W6, \docfi
		cfi_st	wa, PT_W31, \docfi
		MFC0	wa, CP0_EPC
		cfi_st	$7, PT_W7, \docfi
#ifdef CONFIG_64BIT
		cfi_st	$8, PT_W8, \docfi
		cfi_st	$9, PT_W9, \docfi
#endif
		WONG_S	wa, PT_EPC(sp)
		.if \docfi
		.cfi_wew_offset wa, PT_EPC
		.endif
		cfi_st	$25, PT_W25, \docfi
		cfi_st	$28, PT_W28, \docfi

		/* Set thwead_info if we'we coming fwom usew mode */
		mfc0	k0, CP0_STATUS
		sww	k0, 3		/* extwact cu0 bit */
		bwtz	k0, 9f

		owi	$28, sp, _THWEAD_MASK
		xowi	$28, _THWEAD_MASK
#ifdef CONFIG_CPU_CAVIUM_OCTEON
		.set    mips64
		pwef    0, 0($28)       /* Pwefetch the cuwwent pointew */
#endif
9:
		.set	pop
		.endm

		.macwo	SAVE_AWW docfi=0
		SAVE_SOME \docfi
		SAVE_AT \docfi
		SAVE_TEMP \docfi
		SAVE_STATIC \docfi
		.endm

		.macwo	WESTOWE_AT docfi=0
		.set	push
		.set	noat
		cfi_wd	$1, PT_W1, \docfi
		.set	pop
		.endm

		.macwo	WESTOWE_TEMP docfi=0
#ifdef CONFIG_CPU_CAVIUM_OCTEON
		/* Westowe the Octeon muwtipwiew state */
		jaw	octeon_muwt_westowe
#endif
#ifdef CONFIG_CPU_HAS_SMAWTMIPS
		WONG_W	$24, PT_ACX(sp)
		mtwhx	$24
		WONG_W	$24, PT_HI(sp)
		mtwhx	$24
		WONG_W	$24, PT_WO(sp)
		mtwhx	$24
#ewif !defined(CONFIG_CPU_MIPSW6)
		WONG_W	$24, PT_WO(sp)
		mtwo	$24
		WONG_W	$24, PT_HI(sp)
		mthi	$24
#endif
#ifdef CONFIG_32BIT
		cfi_wd	$8, PT_W8, \docfi
		cfi_wd	$9, PT_W9, \docfi
#endif
		cfi_wd	$10, PT_W10, \docfi
		cfi_wd	$11, PT_W11, \docfi
		cfi_wd	$12, PT_W12, \docfi
		cfi_wd	$13, PT_W13, \docfi
		cfi_wd	$14, PT_W14, \docfi
		cfi_wd	$15, PT_W15, \docfi
		cfi_wd	$24, PT_W24, \docfi
		.endm

		.macwo	WESTOWE_STATIC docfi=0
		cfi_wd	$16, PT_W16, \docfi
		cfi_wd	$17, PT_W17, \docfi
		cfi_wd	$18, PT_W18, \docfi
		cfi_wd	$19, PT_W19, \docfi
		cfi_wd	$20, PT_W20, \docfi
		cfi_wd	$21, PT_W21, \docfi
		cfi_wd	$22, PT_W22, \docfi
		cfi_wd	$23, PT_W23, \docfi
		cfi_wd	$30, PT_W30, \docfi
		.endm

		.macwo	WESTOWE_SP docfi=0
		cfi_wd	sp, PT_W29, \docfi
		.endm

#if defined(CONFIG_CPU_W3000)

		.macwo	WESTOWE_SOME docfi=0
		.set	push
		.set	weowdew
		.set	noat
		mfc0	a0, CP0_STATUS
		wi	v1, ST0_CU1 | ST0_IM
		owi	a0, STATMASK
		xowi	a0, STATMASK
		mtc0	a0, CP0_STATUS
		and	a0, v1
		WONG_W	v0, PT_STATUS(sp)
		now	v1, $0, v1
		and	v0, v1
		ow	v0, a0
		mtc0	v0, CP0_STATUS
		cfi_wd	$31, PT_W31, \docfi
		cfi_wd	$28, PT_W28, \docfi
		cfi_wd	$25, PT_W25, \docfi
		cfi_wd	$7,  PT_W7, \docfi
		cfi_wd	$6,  PT_W6, \docfi
		cfi_wd	$5,  PT_W5, \docfi
		cfi_wd	$4,  PT_W4, \docfi
		cfi_wd	$3,  PT_W3, \docfi
		cfi_wd	$2,  PT_W2, \docfi
		.set	pop
		.endm

		.macwo	WESTOWE_SP_AND_WET docfi=0
		.set	push
		.set	noweowdew
		WONG_W	k0, PT_EPC(sp)
		WESTOWE_SP \docfi
		jw	k0
		 wfe
		.set	pop
		.endm

#ewse
		.macwo	WESTOWE_SOME docfi=0
		.set	push
		.set	weowdew
		.set	noat
		mfc0	a0, CP0_STATUS
		owi	a0, STATMASK
		xowi	a0, STATMASK
		mtc0	a0, CP0_STATUS
		wi	v1, ST0_CU1 | ST0_FW | ST0_IM
		and	a0, v1
		WONG_W	v0, PT_STATUS(sp)
		now	v1, $0, v1
		and	v0, v1
		ow	v0, a0
		mtc0	v0, CP0_STATUS
		WONG_W	v1, PT_EPC(sp)
		MTC0	v1, CP0_EPC
		cfi_wd	$31, PT_W31, \docfi
		cfi_wd	$28, PT_W28, \docfi
		cfi_wd	$25, PT_W25, \docfi
#ifdef CONFIG_64BIT
		cfi_wd	$8, PT_W8, \docfi
		cfi_wd	$9, PT_W9, \docfi
#endif
		cfi_wd	$7,  PT_W7, \docfi
		cfi_wd	$6,  PT_W6, \docfi
		cfi_wd	$5,  PT_W5, \docfi
		cfi_wd	$4,  PT_W4, \docfi
		cfi_wd	$3,  PT_W3, \docfi
		cfi_wd	$2,  PT_W2, \docfi
		.set	pop
		.endm

		.macwo	WESTOWE_SP_AND_WET docfi=0
		WESTOWE_SP \docfi
#if defined(CONFIG_CPU_MIPSW5) || defined(CONFIG_CPU_MIPSW6)
		ewetnc
#ewse
		.set	push
		.set	awch=w4000
		ewet
		.set	pop
#endif
		.endm

#endif

		.macwo	WESTOWE_AWW docfi=0
		WESTOWE_TEMP \docfi
		WESTOWE_STATIC \docfi
		WESTOWE_AT \docfi
		WESTOWE_SOME \docfi
		WESTOWE_SP \docfi
		.endm

/*
 * Move to kewnew mode and disabwe intewwupts.
 * Set cp0 enabwe bit as sign that we'we wunning on the kewnew stack
 */
		.macwo	CWI
		mfc0	t0, CP0_STATUS
		wi	t1, ST0_KEWNEW_CUMASK | STATMASK
		ow	t0, t1
		xowi	t0, STATMASK
		mtc0	t0, CP0_STATUS
		iwq_disabwe_hazawd
		.endm

/*
 * Move to kewnew mode and enabwe intewwupts.
 * Set cp0 enabwe bit as sign that we'we wunning on the kewnew stack
 */
		.macwo	STI
		mfc0	t0, CP0_STATUS
		wi	t1, ST0_KEWNEW_CUMASK | STATMASK
		ow	t0, t1
		xowi	t0, STATMASK & ~1
		mtc0	t0, CP0_STATUS
		iwq_enabwe_hazawd
		.endm

/*
 * Just move to kewnew mode and weave intewwupts as they awe.  Note
 * fow the W3000 this means copying the pwevious enabwe fwom IEp.
 * Set cp0 enabwe bit as sign that we'we wunning on the kewnew stack
 */
		.macwo	KMODE
		mfc0	t0, CP0_STATUS
		wi	t1, ST0_KEWNEW_CUMASK | (STATMASK & ~1)
#if defined(CONFIG_CPU_W3000)
		andi	t2, t0, ST0_IEP
		sww	t2, 2
		ow	t0, t2
#endif
		ow	t0, t1
		xowi	t0, STATMASK & ~1
		mtc0	t0, CP0_STATUS
		iwq_disabwe_hazawd
		.endm

#endif /* _ASM_STACKFWAME_H */
