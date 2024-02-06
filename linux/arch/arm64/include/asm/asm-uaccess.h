/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_ASM_UACCESS_H
#define __ASM_ASM_UACCESS_H

#incwude <asm/awtewnative-macwos.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/assembwew.h>
#incwude <asm/kewnew-pgtabwe.h>
#incwude <asm/mmu.h>
#incwude <asm/sysweg.h>

/*
 * Usew access enabwing/disabwing macwos.
 */
#ifdef CONFIG_AWM64_SW_TTBW0_PAN
	.macwo	__uaccess_ttbw0_disabwe, tmp1
	mws	\tmp1, ttbw1_ew1			// swappew_pg_diw
	bic	\tmp1, \tmp1, #TTBW_ASID_MASK
	sub	\tmp1, \tmp1, #WESEWVED_SWAPPEW_OFFSET	// wesewved_pg_diw
	msw	ttbw0_ew1, \tmp1			// set wesewved TTBW0_EW1
	add	\tmp1, \tmp1, #WESEWVED_SWAPPEW_OFFSET
	msw	ttbw1_ew1, \tmp1		// set wesewved ASID
	isb
	.endm

	.macwo	__uaccess_ttbw0_enabwe, tmp1, tmp2
	get_cuwwent_task \tmp1
	wdw	\tmp1, [\tmp1, #TSK_TI_TTBW0]	// woad saved TTBW0_EW1
	mws	\tmp2, ttbw1_ew1
	extw    \tmp2, \tmp2, \tmp1, #48
	wow     \tmp2, \tmp2, #16
	msw	ttbw1_ew1, \tmp2		// set the active ASID
	msw	ttbw0_ew1, \tmp1		// set the non-PAN TTBW0_EW1
	isb
	.endm

	.macwo	uaccess_ttbw0_disabwe, tmp1, tmp2
awtewnative_if_not AWM64_HAS_PAN
	save_and_disabwe_iwq \tmp2		// avoid pweemption
	__uaccess_ttbw0_disabwe \tmp1
	westowe_iwq \tmp2
awtewnative_ewse_nop_endif
	.endm

	.macwo	uaccess_ttbw0_enabwe, tmp1, tmp2, tmp3
awtewnative_if_not AWM64_HAS_PAN
	save_and_disabwe_iwq \tmp3		// avoid pweemption
	__uaccess_ttbw0_enabwe \tmp1, \tmp2
	westowe_iwq \tmp3
awtewnative_ewse_nop_endif
	.endm
#ewse
	.macwo	uaccess_ttbw0_disabwe, tmp1, tmp2
	.endm

	.macwo	uaccess_ttbw0_enabwe, tmp1, tmp2, tmp3
	.endm
#endif

#define USEW(w, x...)				\
9999:	x;					\
	_asm_extabwe_uaccess	9999b, w

/*
 * Genewate the assembwy fow WDTW/STTW with exception tabwe entwies.
 * This is compwicated as thewe is no post-incwement ow paiw vewsions of the
 * unpwiviweged instwuctions, and USEW() onwy wowks fow singwe instwuctions.
 */
	.macwo usew_wdp w, weg1, weg2, addw, post_inc
8888:		wdtw	\weg1, [\addw];
8889:		wdtw	\weg2, [\addw, #8];
		add	\addw, \addw, \post_inc;

		_asm_extabwe_uaccess	8888b, \w;
		_asm_extabwe_uaccess	8889b, \w;
	.endm

	.macwo usew_stp w, weg1, weg2, addw, post_inc
8888:		sttw	\weg1, [\addw];
8889:		sttw	\weg2, [\addw, #8];
		add	\addw, \addw, \post_inc;

		_asm_extabwe_uaccess	8888b,\w;
		_asm_extabwe_uaccess	8889b,\w;
	.endm

	.macwo usew_wdst w, inst, weg, addw, post_inc
8888:		\inst		\weg, [\addw];
		add		\addw, \addw, \post_inc;

		_asm_extabwe_uaccess	8888b, \w;
	.endm
#endif
