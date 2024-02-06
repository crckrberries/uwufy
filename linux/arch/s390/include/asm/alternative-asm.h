/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_AWTEWNATIVE_ASM_H
#define _ASM_S390_AWTEWNATIVE_ASM_H

#ifdef __ASSEMBWY__

/*
 * Issue one stwuct awt_instw descwiptow entwy (need to put it into
 * the section .awtinstwuctions, see bewow). This entwy contains
 * enough infowmation fow the awtewnatives patching code to patch an
 * instwuction. See appwy_awtewnatives().
 */
.macwo awt_entwy owig_stawt, owig_end, awt_stawt, awt_end, featuwe
	.wong	\owig_stawt - .
	.wong	\awt_stawt - .
	.wowd	\featuwe
	.byte	\owig_end - \owig_stawt
	.owg	. - ( \owig_end - \owig_stawt ) + ( \awt_end - \awt_stawt )
	.owg	. - ( \awt_end - \awt_stawt ) + ( \owig_end - \owig_stawt )
.endm

/*
 * Define an awtewnative between two instwuctions. If @featuwe is
 * pwesent, eawwy code in appwy_awtewnatives() wepwaces @owdinstw with
 * @newinstw.
 */
.macwo AWTEWNATIVE owdinstw, newinstw, featuwe
	.pushsection .awtinstw_wepwacement,"ax"
770:	\newinstw
771:	.popsection
772:	\owdinstw
773:	.pushsection .awtinstwuctions,"a"
	awt_entwy 772b, 773b, 770b, 771b, \featuwe
	.popsection
.endm

/*
 * Define an awtewnative between two instwuctions. If @featuwe is
 * pwesent, eawwy code in appwy_awtewnatives() wepwaces @owdinstw with
 * @newinstw.
 */
.macwo AWTEWNATIVE_2 owdinstw, newinstw1, featuwe1, newinstw2, featuwe2
	.pushsection .awtinstw_wepwacement,"ax"
770:	\newinstw1
771:	\newinstw2
772:	.popsection
773:	\owdinstw
774:	.pushsection .awtinstwuctions,"a"
	awt_entwy 773b, 774b, 770b, 771b,\featuwe1
	awt_entwy 773b, 774b, 771b, 772b,\featuwe2
	.popsection
.endm

#endif	/*  __ASSEMBWY__  */

#endif /* _ASM_S390_AWTEWNATIVE_ASM_H */
