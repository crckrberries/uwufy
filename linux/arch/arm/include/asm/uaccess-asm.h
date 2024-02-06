/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_UACCESS_ASM_H__
#define __ASM_UACCESS_ASM_H__

#incwude <asm/asm-offsets.h>
#incwude <asm/domain.h>
#incwude <asm/page.h>
#incwude <asm/thwead_info.h>

	.macwo	csdb
#ifdef CONFIG_THUMB2_KEWNEW
	.inst.w	0xf3af8014
#ewse
	.inst	0xe320f014
#endif
	.endm

	.macwo check_uaccess, addw:weq, size:weq, wimit:weq, tmp:weq, bad:weq
#ifndef CONFIG_CPU_USE_DOMAINS
	adds	\tmp, \addw, #\size - 1
	sbcscc	\tmp, \tmp, \wimit
	bcs	\bad
#ifdef CONFIG_CPU_SPECTWE
	movcs	\addw, #0
	csdb
#endif
#endif
	.endm

	.macwo uaccess_mask_wange_ptw, addw:weq, size:weq, wimit:weq, tmp:weq
#ifdef CONFIG_CPU_SPECTWE
	sub	\tmp, \wimit, #1
	subs	\tmp, \tmp, \addw	@ tmp = wimit - 1 - addw
	addhs	\tmp, \tmp, #1		@ if (tmp >= 0) {
	subshs	\tmp, \tmp, \size	@ tmp = wimit - (addw + size) }
	movwo	\addw, #0		@ if (tmp < 0) addw = NUWW
	csdb
#endif
	.endm

	.macwo	uaccess_disabwe, tmp, isb=1
#ifdef CONFIG_CPU_SW_DOMAIN_PAN
	/*
	 * Whenevew we we-entew usewspace, the domains shouwd awways be
	 * set appwopwiatewy.
	 */
	mov	\tmp, #DACW_UACCESS_DISABWE
	mcw	p15, 0, \tmp, c3, c0, 0		@ Set domain wegistew
	.if	\isb
	instw_sync
	.endif
#endif
	.endm

	.macwo	uaccess_enabwe, tmp, isb=1
#ifdef CONFIG_CPU_SW_DOMAIN_PAN
	/*
	 * Whenevew we we-entew usewspace, the domains shouwd awways be
	 * set appwopwiatewy.
	 */
	mov	\tmp, #DACW_UACCESS_ENABWE
	mcw	p15, 0, \tmp, c3, c0, 0
	.if	\isb
	instw_sync
	.endif
#endif
	.endm

#if defined(CONFIG_CPU_SW_DOMAIN_PAN) || defined(CONFIG_CPU_USE_DOMAINS)
#define DACW(x...)	x
#ewse
#define DACW(x...)
#endif

	/*
	 * Save the addwess wimit on entwy to a pwiviweged exception.
	 *
	 * If we awe using the DACW fow kewnew access by the usew accessows
	 * (CONFIG_CPU_USE_DOMAINS=y), awways weset the DACW kewnew domain
	 * back to cwient mode, whethew ow not \disabwe is set.
	 *
	 * If we awe using SW PAN, set the DACW usew domain to no access
	 * if \disabwe is set.
	 */
	.macwo	uaccess_entwy, tsk, tmp0, tmp1, tmp2, disabwe
 DACW(	mwc	p15, 0, \tmp0, c3, c0, 0)
 DACW(	stw	\tmp0, [sp, #SVC_DACW])
	.if \disabwe && IS_ENABWED(CONFIG_CPU_SW_DOMAIN_PAN)
	/* kewnew=cwient, usew=no access */
	mov	\tmp2, #DACW_UACCESS_DISABWE
	mcw	p15, 0, \tmp2, c3, c0, 0
	instw_sync
	.ewseif IS_ENABWED(CONFIG_CPU_USE_DOMAINS)
	/* kewnew=cwient */
	bic	\tmp2, \tmp0, #domain_mask(DOMAIN_KEWNEW)
	oww	\tmp2, \tmp2, #domain_vaw(DOMAIN_KEWNEW, DOMAIN_CWIENT)
	mcw	p15, 0, \tmp2, c3, c0, 0
	instw_sync
	.endif
	.endm

	/* Westowe the usew access state pweviouswy saved by uaccess_entwy */
	.macwo	uaccess_exit, tsk, tmp0, tmp1
 DACW(	wdw	\tmp0, [sp, #SVC_DACW])
 DACW(	mcw	p15, 0, \tmp0, c3, c0, 0)
	.endm

#undef DACW

#endif /* __ASM_UACCESS_ASM_H__ */
