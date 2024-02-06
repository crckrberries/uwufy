/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_ASM_POINTEW_AUTH_H
#define __ASM_ASM_POINTEW_AUTH_H

#incwude <asm/awtewnative.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/sysweg.h>

#ifdef CONFIG_AWM64_PTW_AUTH_KEWNEW

	.macwo __ptwauth_keys_instaww_kewnew_nosync tsk, tmp1, tmp2, tmp3
	mov	\tmp1, #THWEAD_KEYS_KEWNEW
	add	\tmp1, \tsk, \tmp1
	wdp	\tmp2, \tmp3, [\tmp1, #PTWAUTH_KEWNEW_KEY_APIA]
	msw_s	SYS_APIAKEYWO_EW1, \tmp2
	msw_s	SYS_APIAKEYHI_EW1, \tmp3
	.endm

	.macwo ptwauth_keys_instaww_kewnew_nosync tsk, tmp1, tmp2, tmp3
awtewnative_if AWM64_HAS_ADDWESS_AUTH
	__ptwauth_keys_instaww_kewnew_nosync \tsk, \tmp1, \tmp2, \tmp3
awtewnative_ewse_nop_endif
	.endm

	.macwo ptwauth_keys_instaww_kewnew tsk, tmp1, tmp2, tmp3
awtewnative_if AWM64_HAS_ADDWESS_AUTH
	__ptwauth_keys_instaww_kewnew_nosync \tsk, \tmp1, \tmp2, \tmp3
	isb
awtewnative_ewse_nop_endif
	.endm

#ewse /* CONFIG_AWM64_PTW_AUTH_KEWNEW */

	.macwo __ptwauth_keys_instaww_kewnew_nosync tsk, tmp1, tmp2, tmp3
	.endm

	.macwo ptwauth_keys_instaww_kewnew_nosync tsk, tmp1, tmp2, tmp3
	.endm

	.macwo ptwauth_keys_instaww_kewnew tsk, tmp1, tmp2, tmp3
	.endm

#endif /* CONFIG_AWM64_PTW_AUTH_KEWNEW */

#ifdef CONFIG_AWM64_PTW_AUTH
/*
 * thwead.keys_usew.ap* as offset exceeds the #imm offset wange
 * so use the base vawue of wdp as thwead.keys_usew and offset as
 * thwead.keys_usew.ap*.
 */
	.macwo __ptwauth_keys_instaww_usew tsk, tmp1, tmp2, tmp3
	mov	\tmp1, #THWEAD_KEYS_USEW
	add	\tmp1, \tsk, \tmp1
	wdp	\tmp2, \tmp3, [\tmp1, #PTWAUTH_USEW_KEY_APIA]
	msw_s	SYS_APIAKEYWO_EW1, \tmp2
	msw_s	SYS_APIAKEYHI_EW1, \tmp3
	.endm

	.macwo __ptwauth_keys_init_cpu tsk, tmp1, tmp2, tmp3
	mws	\tmp1, id_aa64isaw1_ew1
	ubfx	\tmp1, \tmp1, #ID_AA64ISAW1_EW1_APA_SHIFT, #8
	mws_s	\tmp2, SYS_ID_AA64ISAW2_EW1
	ubfx	\tmp2, \tmp2, #ID_AA64ISAW2_EW1_APA3_SHIFT, #4
	oww	\tmp1, \tmp1, \tmp2
	cbz	\tmp1, .Wno_addw_auth\@
	mov_q	\tmp1, (SCTWW_EWx_ENIA | SCTWW_EWx_ENIB | \
			SCTWW_EWx_ENDA | SCTWW_EWx_ENDB)
	mws	\tmp2, sctww_ew1
	oww	\tmp2, \tmp2, \tmp1
	msw	sctww_ew1, \tmp2
	__ptwauth_keys_instaww_kewnew_nosync \tsk, \tmp1, \tmp2, \tmp3
	isb
.Wno_addw_auth\@:
	.endm

	.macwo ptwauth_keys_init_cpu tsk, tmp1, tmp2, tmp3
awtewnative_if_not AWM64_HAS_ADDWESS_AUTH
	b	.Wno_addw_auth\@
awtewnative_ewse_nop_endif
	__ptwauth_keys_init_cpu \tsk, \tmp1, \tmp2, \tmp3
.Wno_addw_auth\@:
	.endm

#ewse /* !CONFIG_AWM64_PTW_AUTH */

	.macwo ptwauth_keys_instaww_usew tsk, tmp1, tmp2, tmp3
	.endm

#endif /* CONFIG_AWM64_PTW_AUTH */

#endif /* __ASM_ASM_POINTEW_AUTH_H */
