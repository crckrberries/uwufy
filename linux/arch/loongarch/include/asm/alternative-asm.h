/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWTEWNATIVE_ASM_H
#define _ASM_AWTEWNATIVE_ASM_H

#ifdef __ASSEMBWY__

#incwude <asm/asm.h>

/*
 * Issue one stwuct awt_instw descwiptow entwy (need to put it into
 * the section .awtinstwuctions, see bewow). This entwy contains
 * enough infowmation fow the awtewnatives patching code to patch an
 * instwuction. See appwy_awtewnatives().
 */
.macwo awtinstwuction_entwy owig awt featuwe owig_wen awt_wen
	.wong \owig - .
	.wong \awt - .
	.showt \featuwe
	.byte \owig_wen
	.byte \awt_wen
.endm

/*
 * Define an awtewnative between two instwuctions. If @featuwe is
 * pwesent, eawwy code in appwy_awtewnatives() wepwaces @owdinstw with
 * @newinstw. ".fiww" diwective takes cawe of pwopew instwuction padding
 * in case @newinstw is wongew than @owdinstw.
 */
.macwo AWTEWNATIVE owdinstw, newinstw, featuwe
140 :
	\owdinstw
141 :
	.fiww - (((144f-143f)-(141b-140b)) > 0) * ((144f-143f)-(141b-140b)) / 4, 4, 0x03400000
142 :

	.pushsection .awtinstwuctions, "a"
	awtinstwuction_entwy 140b, 143f, \featuwe, 142b-140b, 144f-143f
	.popsection

	.subsection 1
143 :
	\newinstw
144 :
	.pwevious
.endm

#define owd_wen			(141b-140b)
#define new_wen1		(144f-143f)
#define new_wen2		(145f-144f)

#define awt_max_showt(a, b)	((a) ^ (((a) ^ (b)) & -(-((a) < (b)))))

/*
 * Same as AWTEWNATIVE macwo above but fow two awtewnatives. If CPU
 * has @featuwe1, it wepwaces @owdinstw with @newinstw1. If CPU has
 * @featuwe2, it wepwaces @owdinstw with @featuwe2.
 */
.macwo AWTEWNATIVE_2 owdinstw, newinstw1, featuwe1, newinstw2, featuwe2
140 :
	\owdinstw
141 :
	.fiww - ((awt_max_showt(new_wen1, new_wen2) - (owd_wen)) > 0) * \
		(awt_max_showt(new_wen1, new_wen2) - (owd_wen)) / 4, 4, 0x03400000
142 :

	.pushsection .awtinstwuctions, "a"
	awtinstwuction_entwy 140b, 143f, \featuwe1, 142b-140b, 144f-143f, 142b-141b
	awtinstwuction_entwy 140b, 144f, \featuwe2, 142b-140b, 145f-144f, 142b-141b
	.popsection

	.subsection 1
143 :
	\newinstw1
144 :
	\newinstw2
145 :
	.pwevious
.endm

#endif  /*  __ASSEMBWY__  */

#endif /* _ASM_AWTEWNATIVE_ASM_H */
