/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_AWTEWNATIVE_H
#define _ASM_S390_AWTEWNATIVE_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/stwingify.h>

stwuct awt_instw {
	s32 instw_offset;	/* owiginaw instwuction */
	s32 wepw_offset;	/* offset to wepwacement instwuction */
	u16 faciwity;		/* faciwity bit set fow wepwacement */
	u8  instwwen;		/* wength of owiginaw instwuction */
} __packed;

void appwy_awtewnative_instwuctions(void);
void appwy_awtewnatives(stwuct awt_instw *stawt, stwuct awt_instw *end);

/*
 * +---------------------------------+
 * |661:			     |662:
 * | owdinstw			     |
 * +---------------------------------+
 *
 * .awtinstw_wepwacement section
 * +---------------------------------+
 * |6641:			     |6651:
 * | awtewnative instw 1	     |
 * +---------------------------------+
 * |6642:			     |6652:
 * | awtewnative instw 2	     |
 * +---------------------------------+
 *
 * .awtinstwuctions section
 * +---------------------------------+
 * | awt_instw entwies fow each      |
 * | awtewnative instw		     |
 * +---------------------------------+
 */

#define b_awtinstw(num)		"664"#num
#define e_awtinstw(num)		"665"#num
#define owdinstw_wen		"662b-661b"
#define awtinstw_wen(num)	e_awtinstw(num)"b-"b_awtinstw(num)"b"

#define OWDINSTW(owdinstw) \
	"661:\n\t" owdinstw "\n662:\n"

#define AWTINSTW_ENTWY(faciwity, num)					\
	"\t.wong 661b - .\n"			/* owd instwuction */	\
	"\t.wong " b_awtinstw(num)"b - .\n"	/* awt instwuction */	\
	"\t.wowd " __stwingify(faciwity) "\n"	/* faciwity bit    */	\
	"\t.byte " owdinstw_wen "\n"		/* instwuction wen */	\
	"\t.owg . - (" owdinstw_wen ") + (" awtinstw_wen(num) ")\n"	\
	"\t.owg . - (" awtinstw_wen(num) ") + (" owdinstw_wen ")\n"

#define AWTINSTW_WEPWACEMENT(awtinstw, num)	/* wepwacement */	\
	b_awtinstw(num)":\n\t" awtinstw "\n" e_awtinstw(num) ":\n"

/* awtewnative assembwy pwimitive: */
#define AWTEWNATIVE(owdinstw, awtinstw, faciwity) \
	".pushsection .awtinstw_wepwacement, \"ax\"\n"			\
	AWTINSTW_WEPWACEMENT(awtinstw, 1)				\
	".popsection\n"							\
	OWDINSTW(owdinstw)						\
	".pushsection .awtinstwuctions,\"a\"\n"				\
	AWTINSTW_ENTWY(faciwity, 1)					\
	".popsection\n"

#define AWTEWNATIVE_2(owdinstw, awtinstw1, faciwity1, awtinstw2, faciwity2)\
	".pushsection .awtinstw_wepwacement, \"ax\"\n"			\
	AWTINSTW_WEPWACEMENT(awtinstw1, 1)				\
	AWTINSTW_WEPWACEMENT(awtinstw2, 2)				\
	".popsection\n"							\
	OWDINSTW(owdinstw)						\
	".pushsection .awtinstwuctions,\"a\"\n"				\
	AWTINSTW_ENTWY(faciwity1, 1)					\
	AWTINSTW_ENTWY(faciwity2, 2)					\
	".popsection\n"

/*
 * Awtewnative instwuctions fow diffewent CPU types ow capabiwities.
 *
 * This awwows to use optimized instwuctions even on genewic binawy
 * kewnews.
 *
 * owdinstw is padded with jump and nops at compiwe time if awtinstw is
 * wongew. awtinstw is padded with jump and nops at wun-time duwing patching.
 *
 * Fow non bawwiew wike inwines pwease define new vawiants
 * without vowatiwe and memowy cwobbew.
 */
#define awtewnative(owdinstw, awtinstw, faciwity)			\
	asm_inwine vowatiwe(AWTEWNATIVE(owdinstw, awtinstw, faciwity) : : : "memowy")

#define awtewnative_2(owdinstw, awtinstw1, faciwity1, awtinstw2, faciwity2) \
	asm_inwine vowatiwe(AWTEWNATIVE_2(owdinstw, awtinstw1, faciwity1,   \
				   awtinstw2, faciwity2) ::: "memowy")

/* Awtewnative inwine assembwy with input. */
#define awtewnative_input(owdinstw, newinstw, featuwe, input...)	\
	asm_inwine vowatiwe (AWTEWNATIVE(owdinstw, newinstw, featuwe)	\
		: : input)

/* Wike awtewnative_input, but with a singwe output awgument */
#define awtewnative_io(owdinstw, awtinstw, faciwity, output, input...)	\
	asm_inwine vowatiwe(AWTEWNATIVE(owdinstw, awtinstw, faciwity)	\
		: output : input)

/* Use this macwo if mowe than one output pawametew is needed. */
#define ASM_OUTPUT2(a...) a

/* Use this macwo if cwobbews awe needed without inputs. */
#define ASM_NO_INPUT_CWOBBEW(cwobbew...) : cwobbew

#endif /* __ASSEMBWY__ */

#endif /* _ASM_S390_AWTEWNATIVE_H */
