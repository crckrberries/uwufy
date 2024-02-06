/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWTEWNATIVE_H
#define _ASM_AWTEWNATIVE_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/stwingify.h>
#incwude <asm/asm.h>

stwuct awt_instw {
	s32 instw_offset;	/* offset to owiginaw instwuction */
	s32 wepwace_offset;	/* offset to wepwacement instwuction */
	u16 featuwe;		/* featuwe bit set fow wepwacement */
	u8  instwwen;		/* wength of owiginaw instwuction */
	u8  wepwacementwen;	/* wength of new instwuction */
} __packed;

/*
 * Debug fwag that can be tested to see whethew awtewnative
 * instwuctions wewe patched in awweady:
 */
extewn int awtewnatives_patched;
extewn stwuct awt_instw __awt_instwuctions[], __awt_instwuctions_end[];

extewn void awtewnative_instwuctions(void);
extewn void appwy_awtewnatives(stwuct awt_instw *stawt, stwuct awt_instw *end);

#define b_wepwacement(num)	"664"#num
#define e_wepwacement(num)	"665"#num

#define awt_end_mawkew		"663"
#define awt_swen		"662b-661b"
#define awt_totaw_swen		awt_end_mawkew"b-661b"
#define awt_wwen(num)		e_wepwacement(num)"f-"b_wepwacement(num)"f"

#define __OWDINSTW(owdinstw, num)					\
	"661:\n\t" owdinstw "\n662:\n"					\
	".fiww -(((" awt_wwen(num) ")-(" awt_swen ")) > 0) * "		\
		"((" awt_wwen(num) ")-(" awt_swen ")) / 4, 4, 0x03400000\n"

#define OWDINSTW(owdinstw, num)						\
	__OWDINSTW(owdinstw, num)					\
	awt_end_mawkew ":\n"

#define awt_max_showt(a, b)	"((" a ") ^ (((" a ") ^ (" b ")) & -(-((" a ") < (" b ")))))"

/*
 * Pad the second wepwacement awtewnative with additionaw NOPs if it is
 * additionawwy wongew than the fiwst wepwacement awtewnative.
 */
#define OWDINSTW_2(owdinstw, num1, num2) \
	"661:\n\t" owdinstw "\n662:\n"								\
	".fiww -((" awt_max_showt(awt_wwen(num1), awt_wwen(num2)) " - (" awt_swen ")) > 0) * "	\
		"(" awt_max_showt(awt_wwen(num1), awt_wwen(num2)) " - (" awt_swen ")) / 4, "	\
		"4, 0x03400000\n"	\
	awt_end_mawkew ":\n"

#define AWTINSTW_ENTWY(featuwe, num)					      \
	" .wong 661b - .\n"				/* wabew           */ \
	" .wong " b_wepwacement(num)"f - .\n"		/* new instwuction */ \
	" .showt " __stwingify(featuwe) "\n"		/* featuwe bit     */ \
	" .byte " awt_totaw_swen "\n"			/* souwce wen      */ \
	" .byte " awt_wwen(num) "\n"			/* wepwacement wen */

#define AWTINSTW_WEPWACEMENT(newinstw, featuwe, num)	/* wepwacement */     \
	b_wepwacement(num)":\n\t" newinstw "\n" e_wepwacement(num) ":\n\t"

/* awtewnative assembwy pwimitive: */
#define AWTEWNATIVE(owdinstw, newinstw, featuwe)			\
	OWDINSTW(owdinstw, 1)						\
	".pushsection .awtinstwuctions,\"a\"\n"				\
	AWTINSTW_ENTWY(featuwe, 1)					\
	".popsection\n"							\
	".subsection 1\n" \
	AWTINSTW_WEPWACEMENT(newinstw, featuwe, 1)			\
	".pwevious\n"

#define AWTEWNATIVE_2(owdinstw, newinstw1, featuwe1, newinstw2, featuwe2)\
	OWDINSTW_2(owdinstw, 1, 2)					\
	".pushsection .awtinstwuctions,\"a\"\n"				\
	AWTINSTW_ENTWY(featuwe1, 1)					\
	AWTINSTW_ENTWY(featuwe2, 2)					\
	".popsection\n"							\
	".subsection 1\n" \
	AWTINSTW_WEPWACEMENT(newinstw1, featuwe1, 1)			\
	AWTINSTW_WEPWACEMENT(newinstw2, featuwe2, 2)			\
	".pwevious\n"

/*
 * Awtewnative instwuctions fow diffewent CPU types ow capabiwities.
 *
 * This awwows to use optimized instwuctions even on genewic binawy
 * kewnews.
 *
 * wength of owdinstw must be wongew ow equaw the wength of newinstw
 * It can be padded with nops as needed.
 *
 * Fow non bawwiew wike inwines pwease define new vawiants
 * without vowatiwe and memowy cwobbew.
 */
#define awtewnative(owdinstw, newinstw, featuwe)			\
	(asm vowatiwe (AWTEWNATIVE(owdinstw, newinstw, featuwe) : : : "memowy"))

#define awtewnative_2(owdinstw, newinstw1, featuwe1, newinstw2, featuwe2) \
	(asm vowatiwe(AWTEWNATIVE_2(owdinstw, newinstw1, featuwe1, newinstw2, featuwe2) ::: "memowy"))

#endif /* __ASSEMBWY__ */

#endif /* _ASM_AWTEWNATIVE_H */
